//=============================================================================
//       COPYRIGHT 2005, Delphi Technologies, Inc. All Rights reserved
//                             Delphi Confidential
//
// --------------------------------------------------------------------------
// %name:            dd_flexcan_error.c %
//
// created_by:
//
// date_created:     Wed. Mar. 2 2005
//
// %derived_by:      zzrfyj %
//
// %date_modified:    %
//
// %version:         ctc_pt3#9 %
//
// DESCRIPTION:   This file contains CAN interrupt routines and message
//                transmis/receive handlers.
//
//=============================================================================

//=============================================================================
//  Include Files
//=============================================================================
#include "dd_flexcan.h"
#include "dd_flexcan_error.h"

//============================================================================
// FlexCAN_Error_Handler
//============================================================================
void FlexCAN_Error_Handler (
   FlexCAN_Index_T in_FlexCAN)
{
   uint32_t                 reg_value;
   IO_Configuration_T       config  = FlexCAN_Set_Index(0, in_FlexCAN);

   FLEXCAN_T * pFlexCAN;


   pFlexCAN = FlexCAN_Get_Device(config);

   if (pFlexCAN->ESR.F.BOFFINT == (uint32_t)1)
   {
      //Clear Interrupt
      reg_value = pFlexCAN->ESR.U32;
      reg_value = (reg_value & CAN_ESR_BOFF_CLEAR_MASK);
      pFlexCAN->ESR.U32 = reg_value;
   }
   else if (pFlexCAN->ESR.F.ERRINT == (uint32_t)1)
   {
      //Clear Interrupt
      reg_value = pFlexCAN->ESR.U32;
      reg_value = (reg_value & CAN_ESR_ERR_CLEAR_MASK);
      pFlexCAN->ESR.U32 = reg_value;
   }
   else
   {
      // do nothing
   }

   if( FLEXCAN_ERROR_CALLBACK[in_FlexCAN] != NULL)
   {
      (*(FLEXCAN_ERROR_CALLBACK[in_FlexCAN]))();
   }
}

//============================================================================
// FlexCAN_Get_Rx_Error_Counter 
//============================================================================
uint8_t FlexCAN_Get_Rx_Error_Counter (
   FlexCAN_Index_T in_FlexCAN)
{
   uint8_t                  reg_value;
   IO_Configuration_T       config  = FlexCAN_Set_Index(0, in_FlexCAN);

   FLEXCAN_T * pFlexCAN;


   pFlexCAN = FlexCAN_Get_Device(config);

   reg_value = (uint8_t)(((pFlexCAN->ECR.U32)>>8)&0xFF);
   return reg_value;
}

//============================================================================
// FlexCAN_Get_Tx_Error_Counter 
//============================================================================
uint8_t FlexCAN_Get_Tx_Error_Counter (
   FlexCAN_Index_T in_FlexCAN)
{
   uint8_t                  reg_value;
   IO_Configuration_T       config  = FlexCAN_Set_Index(0, in_FlexCAN);

   FLEXCAN_T * pFlexCAN;


   pFlexCAN = FlexCAN_Get_Device(config);

   reg_value = (uint8_t)((pFlexCAN->ECR.U32)&0xFF);
   return reg_value;
}

//============================================================================
// FlexCAN_Get_Error_Status 
//============================================================================
bool FlexCAN_Get_Error_Status (
   FlexCAN_Index_T in_FlexCAN, FLEXCAN_ERROR_CHANNEL_T in_channel)
{
   bool                     return_code;
   IO_Configuration_T       config  = FlexCAN_Set_Index(0, in_FlexCAN);

   FLEXCAN_T * pFlexCAN;

   pFlexCAN = FlexCAN_Get_Device(config);

   switch(in_channel)
   {
      case FLEXCAN_ERROR_CHANNEL_BIT1ERR:
         return_code = (bool)pFlexCAN->ESR.F.BIT1ERR;
         break;
      case FLEXCAN_ERROR_CHANNEL_BIT0ERR:
         return_code = (bool)pFlexCAN->ESR.F.BIT0ERR;
         break;
      case FLEXCAN_ERROR_CHANNEL_ACKERR:
         return_code = (bool)pFlexCAN->ESR.F.ACKERR;
         break;
      case FLEXCAN_ERROR_CHANNEL_CRCERR:
         return_code = (bool)pFlexCAN->ESR.F.CRCERR;
         break;
      case FLEXCAN_ERROR_CHANNEL_FRMERR:
         return_code = (bool)pFlexCAN->ESR.F.FRMERR;
         break;
      case FLEXCAN_ERROR_CHANNEL_STFERR:
         return_code = (bool)pFlexCAN->ESR.F.STFERR;
         break;
      default:
         return_code = false;
         break;
   }

   return return_code;
}

//============================================================================
// FlexCAN_Set_Busoff_Recovery_Auto_Enable
//============================================================================
void FlexCAN_Set_Busoff_Recovery_Auto_Enable(
   FlexCAN_Index_T in_FlexCAN, bool in_enable)
{
   IO_Configuration_T       config  = FlexCAN_Set_Index(0, in_FlexCAN);

   FLEXCAN_T * pFlexCAN;


   pFlexCAN = FlexCAN_Get_Device(config);

   pFlexCAN->CR.F.BOFFREC = (bool)(!in_enable);
}

FLEXCAN_FLT_CONF_ERR_T FlexCAN_Get_Fault_Confinement_State(
      FlexCAN_Index_T in_FlexCAN)
{
   FLEXCAN_FLT_CONF_ERR_T   return_code;
   IO_Configuration_T       config  = FlexCAN_Set_Index(0, in_FlexCAN);

   FLEXCAN_T * pFlexCAN;


   pFlexCAN = FlexCAN_Get_Device(config);

   if ((pFlexCAN->ESR.F.FLT_CONF) == 0) 
   {
      return_code = FLEXCAN_FLT_CONF_ERR_ACTIVE;
   }
   else if ((pFlexCAN->ESR.F.FLT_CONF) == 1) 
   {
      return_code = FLEXCAN_FLT_CONF_ERR_PASSTIVE;
   }
   else 
   {
      return_code = FLEXCAN_FLT_CONF_ERR_BUSOFF;
   }
   return return_code;
}
