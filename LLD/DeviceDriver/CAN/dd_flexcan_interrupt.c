//=============================================================================
//
//       COPYRIGHT, 2005, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_flexcan_interrupt.c~kok_pt2#9.1.1:csrc:kok_toy#1 %
//
// created_by:       gzdmlz
//
// date_created:     Fri Jan 13 22:58:26 2006
//
// %derived_by:      dz48hg %
//
// %date_modified:   Tue Mar 13 06:04:53 2012 %
//
// %version:         kok_pt2#9.1.1 %
//
//=============================================================================
#include "dd_flexcan.h"
#include "dd_flexcan_interrupt.h"

#define Parameter_Not_Used( not_used ) (not_used)

//=============================================================================
//    FLEXCAN_MSGOBJ_INTERRUPT_Initialize
//============================================================================
void FLEXCAN_MSGOBJ_INTERRUPT_Initialize(
   IO_Configuration_T in_configuration,
   uint8_t              in_vector,
   const IO_Callback_T  in_callback,
   IO_TOS_T             in_tos )
{
   Parameter_Not_Used(in_configuration);
   Parameter_Not_Used(in_vector);
   Parameter_Not_Used(in_callback);
   Parameter_Not_Used(in_tos);
}


//=============================================================================
//  FLEXCAN_MSGOBJ_INTERRUPT_Clear
//============================================================================
void FLEXCAN_MSGOBJ_INTERRUPT_Clear(
   IO_Configuration_T in_configuration  )
{
//   FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(in_configuration, false);
//   FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending(in_configuration);      
}

//=============================================================================
//    FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable
//============================================================================
#if 0
void FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
   IO_Configuration_T in_configuration,
   bool in_enable )
{
   FlexCAN_MSGOBJ_INDEX_T index = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T          *pFlexCAN = FlexCAN_Get_Device( in_configuration );

   if( pFlexCAN )
   {
      if( index < FLEXCAN_MSG_OBJ_32)
      {
         // Insert_Bits(old_value,value,position,width) 
         pFlexCAN->IMRL.U32 = Insert_Bits(pFlexCAN->IMRL.U32,in_enable,index,BIT_1);
      }
      else
      {
         index   -= FLEXCAN_MSG_OBJ_32;
         // Insert_Bits(old_value,value,position,width)
         pFlexCAN->IMRH.U32 = Insert_Bits(pFlexCAN->IMRH.U32,in_enable,index,BIT_1);
      }
   }
}
#endif

//=============================================================================
//  FLEXCAN_MSGOBJ_INTERRUPT_Get_Enable
//============================================================================
bool FLEXCAN_MSGOBJ_INTERRUPT_Get_Enable(
   IO_Configuration_T in_configuration )
{
   FlexCAN_MSGOBJ_INDEX_T index = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T          *pFlexCAN = FlexCAN_Get_Device( in_configuration );
   uint32_t* pInterrupt_Mask;
   bool status = false;

   if( pFlexCAN )
   {
      if( index < FLEXCAN_MSG_OBJ_32)
      {
         pInterrupt_Mask = (uint32_t *)&(pFlexCAN->IMRL.U32);
      }
      else
      {
         index   -= FLEXCAN_MSG_OBJ_32;
         pInterrupt_Mask = (uint32_t *)&(pFlexCAN->IMRH.U32);
      }
      status = FlexCAN_Get_Interrupt_Enable_Mask(*pInterrupt_Mask, index);
   }
   return status;   
}


//=============================================================================
//  FLEXCAN_MSGOBJ_INTERRUPT_Get_Status
//============================================================================
bool FLEXCAN_MSGOBJ_INTERRUPT_Get_Status(
   IO_Configuration_T in_configuration )
{
   FlexCAN_MSGOBJ_INDEX_T  index = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T           *pFlexCAN = FlexCAN_Get_Device( in_configuration );
   uint32_t* pInterrupt_Flag;
   bool status = false;

   if( pFlexCAN )
   {
      if( index < FLEXCAN_MSG_OBJ_32)
      {
         pInterrupt_Flag = (uint32_t *)&(pFlexCAN->IFRL.U32);
      }
      else
      {
         index   -= FLEXCAN_MSG_OBJ_32;
         pInterrupt_Flag = (uint32_t *)&(pFlexCAN->IFRH.U32);
      }
      status = FlexCAN_Get_Interrupt_Status(*pInterrupt_Flag, index);
   }
   return status;   
}

//=============================================================================
//  FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending
//============================================================================
void FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending(
   IO_Configuration_T in_configuration  )
{
   FlexCAN_MSGOBJ_INDEX_T  index = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T * pFlexCAN    = FlexCAN_Get_Device( in_configuration );

   if( pFlexCAN )
   {
      if( index < FLEXCAN_MSG_OBJ_32)
      {
         pFlexCAN->IFRL.U32 &= (1 << index);
      }
      else
      {
         index   -= FLEXCAN_MSG_OBJ_32;
         pFlexCAN->IFRH.U32 &= (1 << index);
      }
   }
}

//=============================================================================
//    FLEXCAN_INTERRUPT_Initialize
//============================================================================
void FLEXCAN_INTERRUPT_Initialize(
   IO_Configuration_T in_configuration,
   uint8_t              in_vector,
   const IO_Callback_T  in_callback,
   IO_TOS_T             in_tos )
{
   Parameter_Not_Used(in_configuration);
   Parameter_Not_Used(in_vector);
   Parameter_Not_Used(in_callback);
   Parameter_Not_Used(in_tos);
}

//=============================================================================
//  FLEXCAN_INTERRUPT_Clear
//============================================================================
void FLEXCAN_INTERRUPT_Clear(
   IO_Configuration_T in_configuration  )
{ 
   FLEXCAN_INTERRUPT_Clear_Pending(in_configuration);
}

//=============================================================================
//  FLEXCAN_INTERRUPT_Set_Enable
//============================================================================
void FLEXCAN_INTERRUPT_Set_Enable(
   IO_Configuration_T in_configuration,
   bool status)
{
   FlexCAN_Interrupt_Type_T type    = FlexCAN_Get_Interrupt_Type(in_configuration);
   FLEXCAN_T * pFlexCAN             = FlexCAN_Get_Device( in_configuration );

   if (type == FLEXCAN_BUSOFF_INTERRUPT)
   {
      pFlexCAN->CR.F.BOFFMSK = status;
   }
   else if (type == FLEXCAN_ERROR_INTERRUPT)
   {
      pFlexCAN->CR.F.ERRMSK = status;
   }
   else
   {
      //Do Nothing
   }
}

//=============================================================================
//  FLEXCAN_INTERRUPT_Get_Enable
//============================================================================
bool FLEXCAN_INTERRUPT_Get_Enable(
   IO_Configuration_T in_configuration  )
{
   FlexCAN_Interrupt_Type_T type    = FlexCAN_Get_Interrupt_Type(in_configuration);
   FLEXCAN_T * pFlexCAN             = FlexCAN_Get_Device( in_configuration );
   bool status = false;

   if (type == FLEXCAN_BUSOFF_INTERRUPT)
   {
      status = ((pFlexCAN->CR.F.BOFFMSK == (uint32_t)1) ? true : false);
   }
   else if (type == FLEXCAN_ERROR_INTERRUPT)
   {
      status = ((pFlexCAN->CR.F.ERRMSK == (uint32_t)1) ? true : false);
   }
   else
   {
      //Do Nothing
   }
   return status;
}

//=============================================================================
//  FLEXCAN_INTERRUPT_Get_Status
//============================================================================
bool FLEXCAN_INTERRUPT_Get_Status(
   IO_Configuration_T in_configuration  )
{
   FlexCAN_Interrupt_Type_T type    = FlexCAN_Get_Interrupt_Type(in_configuration);
   FLEXCAN_T * pFlexCAN             = FlexCAN_Get_Device( in_configuration );
   bool status = false;

   if (type == FLEXCAN_BUSOFF_INTERRUPT)
   {
      status = ((pFlexCAN->ESR.F.BOFFINT == (uint32_t)1) ? true : false);
   }
   else if (type == FLEXCAN_ERROR_INTERRUPT)
   {
      status = ((pFlexCAN->ESR.F.ERRINT == (uint32_t)1) ? true : false);
   }
   else
   {
      //Do Nothing
   }
   return status;
}
 
//=============================================================================
//  FLEXCAN_INTERRUPT_Clear_Pending
//============================================================================
void FLEXCAN_INTERRUPT_Clear_Pending(
   IO_Configuration_T in_configuration  )
{
   FlexCAN_Interrupt_Type_T type    = FlexCAN_Get_Interrupt_Type(in_configuration);
   FLEXCAN_T * pFlexCAN    = FlexCAN_Get_Device( in_configuration );
   uint32_t  reg_value;
   
   //Writing 1 clears the interrupt
   if (type == FLEXCAN_BUSOFF_INTERRUPT)
   {
      reg_value = pFlexCAN->ESR.U32;
      reg_value = (reg_value & CAN_ESR_BOFF_CLEAR_MASK);
      pFlexCAN->ESR.U32 = reg_value;
   }
   else if (type == FLEXCAN_ERROR_INTERRUPT)
   {
      reg_value = pFlexCAN->ESR.U32;
      reg_value = (reg_value & CAN_ESR_ERR_CLEAR_MASK);
      pFlexCAN->ESR.U32 = reg_value;
   }
   else
   {
      //Do Nothing
   }
}
 
