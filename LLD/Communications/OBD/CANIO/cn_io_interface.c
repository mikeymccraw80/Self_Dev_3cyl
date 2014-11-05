/******************************************************************************
 *
 * Filename:          cn_io_interface.c
 *
 * Description:       This file contains CAN interrupt routines and message
 *                    transmis/receive handlers.
 *
 * Global Functions Defined:
 *                    Hw_Transmit_Message()
 *                    CAN_Receive_Callback()
 *                    CAN_Transmit_Callback()
 *                    CAN_Error_Handler()
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

//=============================================================================
// Include Files
//=============================================================================
#include "t_base.h"
#include "cn_io_fexi.h"

#include "cn_io_interface.h"
#include "cn_io_transfer.h"
#include "cn_io_diagnostic.h"

#include "dd_flexcan_common.h"

#define MILLISECOND_RESOLUTION (3)
//=============================================================================
//  Global Data
//=============================================================================
uint8_t          CANMsg_Buffer_DLC;


//============================================================================
// Name:  CAN_Receive_Callback
//
// Description: This function save a received message
//
// Warning: This procedure is called by the receive interrupt service routine.
//
// Shared Variables: Message_Buffer_Ctl_Ptr, CAN_Message_Parameter_Table_Ptr
//
// Parameters: CAN_receive_message_number, in_rx_data, message_length
//
// Return Value: none
//
//============================================================================
void CAN_Receive_Callback( uint8_t CAN_receive_message_number, uint8_t* in_rx_data, uint8_t message_length )
{
   uint8_t idx;
   uint8_t temp_length;
   uint8_t * tmp_ptr; 
   CANMsg_Buffer_DLC = message_length;
   temp_length = (CAN_Message_Parameter_Table_Ptr + CAN_receive_message_number)->CAN_message_length;
   if( message_length <  temp_length )
      {
            // Call the diagnostic routine.
         Set_Message_Length_Mismatch();
      }
   tmp_ptr = (CAN_Message_Parameter_Table_Ptr + CAN_receive_message_number)->CAN_buffer_ptr;
   for (idx = 0; idx < message_length; idx++) 
   {
      *tmp_ptr++ = *in_rx_data++;
   }
   if( (CAN_Message_Parameter_Table_Ptr+CAN_receive_message_number)->callback )
   {
      // call notifier function
      ( *((CAN_Message_Parameter_Table_Ptr+CAN_receive_message_number)->callback) )((CAN_Message_Parameter_Table_Ptr+CAN_receive_message_number)->CAN_message_ID);
   }
   Clear_Message_Length_Mismatch();
}
//============================================================================
// Name:  CAN_Transmit_Callback
//
// Description: This function handle a transmit interrupt.
//
// Warning: This procedure is called by the transmit interrupt service routine.
//
// Shared Variables: Message_Buffer_Ctl_Ptr, CAN_Message_Parameter_Table_Ptr
//
// Parameters: msg_obj
//
// Return Value: none
//
//============================================================================
void CAN_Transmit_Callback( uint32_t msg_obj )
{
   if( NULL != (CAN_Message_Parameter_Table_Ptr+msg_obj)->callback)
   {
      // call notifier function if data buffer is empty
      ( *((CAN_Message_Parameter_Table_Ptr+msg_obj)->callback) )((CAN_Message_Parameter_Table_Ptr+msg_obj)->CAN_message_ID);
   }
   else
   {
      //do nothing
   }
}

//============================================================================
// Name:  Disable_CANH_Device
//
// Description: Disable the CAN node A  
//
// Shared Variables: none
//
// Parameters: none
//
// Return Value: none
//
//============================================================================
void Disable_CANH_Device(void)
{
   //stubed
}

//============================================================================
// Name:  Enable_CANH_Device
//
// Description: Enable the CAN node A  
//
// Shared Variables: none
//
// Parameters: none
//
// Return Value: none
//
//============================================================================
void Enable_CANH_Device(void)
{
   //stubed
}

/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     090416 yrw xxxx Initial version
* 2     101102 sh  SCR_CTC_578 Add data length check when a Msg is received
* 3     101221 sh  SCR_CTC_600 Update the DLC check logic
* 4.1   110516 sh  SCR_CTC_620 Change MAX_MESSAGES_NUM_OF_VEHICLE_CAN to NumOfMSGs,
* ----- ------ --- ---- -------------------------------------------------------
* 3     130710 lj  RSM10647    Added Disable_CANH_Device()
******************************************************************************/
