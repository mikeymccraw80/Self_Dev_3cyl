//=============================================================================
//
//       COPYRIGHT, 2005, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_flexcan_common.c~ctc_pt3#12:csrc:kok_toy#2 %
//
// created_by:       gzdmlz
//
// date_created:     Fri Jan 13 22:58:26 2006
//
// %derived_by:      zzrfyj %
//
// %date_modified:    %
//
// %version:         ctc_pt3#12 %
//
//=============================================================================
#include "dd_flexcan.h"
#include "dd_flexcan_interrupt.h"

//=============================================================================
// FlexCAN_Initialize_Message_Buffer
//=============================================================================
void FlexCAN_Initialize_Message_Object(
   IO_Configuration_T in_configuration, 
   uint32_t                 message_id)
{
   FlexCAN_MSGOBJ_INDEX_T msg_obj = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T*             pFlexCAN= FlexCAN_Get_Device( in_configuration );
   bool interrupt_state = FlexCAN_MSGOBJ_Get_Interrupt(in_configuration);

   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.IDE    = FlexCAN_MSGOBJ_Get_ID_Length(in_configuration);
   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.LENGTH = FlexCAN_MSGOBJ_Get_Data_Length(in_configuration);
   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.RTR    = FlexCAN_MSGOBJ_Get_RTR(in_configuration);
   pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.SRR    = FlexCAN_MSGOBJ_Get_SRR(in_configuration);
   //Clear Message Buffer
   pFlexCAN->MSGBUF[msg_obj].F.DATA.U32[0] = 0;
   pFlexCAN->MSGBUF[msg_obj].F.DATA.U32[1] = 0;
   FLEXCAN_Set_Msg_ID(pFlexCAN, msg_obj, message_id);
   
   if(FlexCAN_MSGOBJ_Get_Direction(in_configuration) == FLEXCAN_MSGOBJ_DIR_TX)
   {
      pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_TX_INACTIVE;
   }
   else
   {
      pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_EMPTY;
   }

   // FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(in_configuration, interrupt_state);
   FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(pFlexCAN, msg_obj, interrupt_state);

}

//=============================================================================
//  FLEXCAN_Get_Free_Running_Timer
//============================================================================
uint16_t FLEXCAN_Get_Free_Running_Timer(
   const FLEXCAN_T* in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T  in_msgobj)
{
   return ((uint16_t)(in_pFlexCAN->TIMER));
}
//=============================================================================
//  FLEXCAN_MSGOBJ_Configure_For_Transmit
//============================================================================
void FLEXCAN_MSGOBJ_Configure_For_Transmit(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_TX_INACTIVE; 
}
//=============================================================================
//  FLEXCAN_MSGOBJ_ConfigureForRecieve
//============================================================================
void FLEXCAN_MSGOBJ_Configure_For_Recieve(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_INACTIVE;
}
//=============================================================================
//  FLEXCAN_MSGOBJ_Write_Data
//============================================================================
void FLEXCAN_MSGOBJ_Write_Data(
   FLEXCAN_T *                  in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T       in_msgobj,
   const uint8_t *              in_buffer,
   FlexCAN_MSGOBJ_Data_Length_T in_length)
{
   uint8_t data_index;
   for (data_index = 0; data_index < in_length; data_index++)
   {
      in_pFlexCAN->MSGBUF[in_msgobj].F.DATA.U8[data_index]= in_buffer[data_index];
   }
}
//=============================================================================
//  FLEXCAN_MSGOBJ_Get_Data
//============================================================================
void FLEXCAN_MSGOBJ_Get_Data(
   const FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj,
   uint8_t *              in_buffer,
   uint8_t                in_length)
{
   uint8_t data_index;               
   for (data_index = 0; data_index < in_length; data_index++)
   {
      in_buffer[data_index] = in_pFlexCAN->MSGBUF[in_msgobj].F.DATA.U8[data_index];
   }
}
//=============================================================================
//  FlexCAN_MSGOBJ_Get_Interrupt_Direction
//============================================================================
FlexCAN_MSGOBJ_DIR_T FlexCAN_Interrupt_Get_Direction(
   IO_Configuration_T in_configuration )
{
   FlexCAN_MSGOBJ_DIR_T direction;
   FlexCAN_MSGOBJ_INDEX_T msg_obj = FlexCAN_MSGOBJ_Get_Index(in_configuration);
   FLEXCAN_T *            pFlexCAN    = FlexCAN_Get_Device( in_configuration );
   FlexCAN_Msg_Code_T     message_code;

   message_code = (FlexCAN_Msg_Code_T)pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE; 

   if( (message_code == FLEXCAN_MSGOBJ_TX_INACTIVE) ||
       (message_code == FLEXCAN_MSGOBJ_TX_REMOTE) ||
       (message_code == FLEXCAN_MSGOBJ_TX_UNCONDITIONAL) ||
       (message_code == FLEXCAN_MSGOBJ_TX_REMOTE_MATCH)
     )
   {
      direction = FLEXCAN_MSGOBJ_DIR_TX;
   }
   else
   {
      direction = FLEXCAN_MSGOBJ_DIR_RX;
   }
       
   return direction;
}
//=============================================================================
// FLEXCAN_Set_Bit_Rate
//=============================================================================
void FLEXCAN_Set_Bit_Rate(
   FLEXCAN_T *      in_pFlexCAN,
   uint8_t          in_time_quanta,
   uint32_t         in_bit_rate)
{
   uint8_t prescale_div = 
           (uint8_t)((FLEXCAN_FREQUENCY_HZ / (in_time_quanta * in_bit_rate)) - 1);
   in_pFlexCAN->CR.F.PRESDIV = prescale_div;
}
//=============================================================================
// FLEXCAN_Get_Msg_ID
//=============================================================================
uint32_t FLEXCAN_Get_Msg_ID(
   const FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj)
{
   uint32_t  msg_id;
   if (FLEXCAN_MSGOBJ_ID_STD == in_pFlexCAN->MSGBUF[in_msgobj].F.CTRSTS.F.IDE)
   {
      msg_id = in_pFlexCAN->MSGBUF[in_msgobj].F.ID.U32 >> FLEXCAN_STD_ID_SHIFT;
   }
   else
   {
      msg_id = in_pFlexCAN->MSGBUF[in_msgobj].F.ID.U32;
   }
   return(msg_id);
}
//=============================================================================
// FLEXCAN_Set_Msg_ID
//=============================================================================
void FLEXCAN_Set_Msg_ID(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj,
   uint32_t in_message_id)
{
   uint32_t  msg_id;
   if (FLEXCAN_MSGOBJ_ID_STD == in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.IDE)
   {
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.F.STD_EXT = in_message_id;
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.F.EXTENDED = 0;
   }
   else
   {
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.U32 = in_message_id;
   }
}
//=============================================================================
// FLEXCAN_Set_Individual_Ext_Mask
//=============================================================================
void FLEXCAN_Set_Individual_Ext_Mask(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj,
   uint32_t               in_msg_mask)
{
   
   if (in_msgobj == FLEXCAN_MSG_OBJ_14)
   {
      in_pFlexCAN->RX14MASK.U32 = in_msg_mask;
   }
   else if (in_msgobj == FLEXCAN_MSG_OBJ_15)
   {
      in_pFlexCAN->RX15MASK.U32 = in_msg_mask;
   }
   else
   {
      // Do nothing
   }
}

//=============================================================================
// FLEXCAN_Set_Global_Ext_Mask
//=============================================================================
void FLEXCAN_Set_Global_Ext_Mask(
   FLEXCAN_T *            in_pFlexCAN,
   uint32_t               in_msg_mask)
{
   in_pFlexCAN->RXGMASK.U32 = in_msg_mask;
}

//=============================================================================
//  FLEXCAN_MSGOBJ_Get_Status
//============================================================================
FlexCAN_Msg_Code_T FLEXCAN_MSGOBJ_Get_Status(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   return (FlexCAN_Msg_Code_T) (in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.CODE);
}

//=============================================================================
//  FLEXCAN_MSGOBJ_Get_Message_Length
//============================================================================
uint8_t FLEXCAN_MSGOBJ_Get_Message_Length(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj)
{
   return (uint8_t)(in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.LENGTH);
}

//=============================================================================
//  FLEXCAN_MSGOBJ_Set_Message_Length
//============================================================================
void FLEXCAN_MSGOBJ_Set_Message_Length(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj,
   uint8_t in_data_length)
{
   in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.LENGTH = in_data_length;
}


//=============================================================================
//  FLEXCAN_Unlock_Message_Buffer
//============================================================================
FLEXCAN_TIMER_T FLEXCAN_Unlock_Message_Buffer(
   FLEXCAN_T* in_pFlexCAN)
{
   return in_pFlexCAN->TIMER;
}

//=============================================================================
//  FLEXCAN_Enable_Communication
//============================================================================
void FLEXCAN_Enable_Communication(
   FLEXCAN_T* in_pFlexCAN)
{
   in_pFlexCAN->MCR.F.HALT = 0;
}

//=============================================================================
//  FLEXCAN_Disable_Communication
//============================================================================
void FLEXCAN_Disable_Communication(
   FLEXCAN_T* in_pFlexCAN)
{
   in_pFlexCAN->MCR.F.HALT = 1;
}

//=============================================================================
//  FLEXCAN_Get_Device_Freeze_Status
//============================================================================
bool FLEXCAN_Get_Device_Freeze_Status(
   FLEXCAN_T  *in_pFlexCAN)
{
   return((bool)(in_pFlexCAN->MCR.F.FRZACK));
}

//=============================================================================
// FlexCAN_Set_Device_Soft_Reset
//=============================================================================
void FlexCAN_Set_Device_Soft_Reset(
   IO_Configuration_T in_configuration)
{
   // Get the device address
   FLEXCAN_T              *pFlexCAN  = FlexCAN_Get_Device( in_configuration );

   // Set the SOFTRST bit
   pFlexCAN->MCR.F.SOFTRST = 1;
}

//=============================================================================
//  FLEXCAN_Get_Device_Soft_Reset_Status
//============================================================================
bool FLEXCAN_Get_Device_Soft_Reset_Status(
   IO_Configuration_T in_configuration)
{
   // Get the device address
   FLEXCAN_T              *pFlexCAN  = FlexCAN_Get_Device( in_configuration );

   return((bool)(pFlexCAN->MCR.F.SOFTRST));
}

//=============================================================================
//  FlexCAN_Enable_Device
//============================================================================
void FlexCAN_Enable_Device(
   IO_Configuration_T in_configuration, 
   bool in_enable)
{
   FLEXCAN_T        *pFlexCAN    = FlexCAN_Get_Device( in_configuration );

   pFlexCAN->MCR.F.MDIS = ~(in_enable);
}

//=============================================================================
//  FlexCAN_Get_Device_Status
//============================================================================
bool FlexCAN_Get_Device_Status(
   IO_Configuration_T in_configuration)
{
   FLEXCAN_T        *pFlexCAN    = FlexCAN_Get_Device( in_configuration );

   return ((bool)(pFlexCAN->MCR.F.MDISACK));
}
