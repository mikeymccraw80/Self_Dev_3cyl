/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: CNG E483                                                  		 *
* File Name:  j1939_communication_manager.c                                 *
* File Description:                                                         *
* This module contains J1939 Communication manager routines.                *
*****************************************************************************/

//=============================================================================
// Include Files
//=============================================================================
#define XbCNIO_FEXI_INCLUDE_HAL_CAN
#define XbCNIO_FEXI_INCLUDE_CAN_PUBLIC_TYPE
#define XbCNIO_FEXI_INCLUDE_OBD_PUBLIC_TYPE
#define XbCNIO_FEXI_INCLUDE_CAN_INTERFACE
#define XbCNIO_FEXI_INCLUDE_IMMO_INTERFACE

#include "cn_io_transfer.h"
#include "cn_io_interface.h"
#include "cn_io_diagnostic.h"
#include "dd_flexcan_common.h"
#include "io_dcan_config.h"
#include "dd_flexcan.h"
#include "obdlcald.h"

#include "j1939_communication_manager.h"
#include "j1939_PGN_config.h"

static J1939_Transmit_Message_Control_T  J1939_Transmit_Message_Control[40];
static J1939_Receive_Message_Buffer_T    J1939_Receive_Message_Buffer [24];
static J1939_Receive_Message_Control_T   J1939_Receive_Message_Control_Channel_0[24];
static J1939_Receive_Message_Control_T   J1939_Receive_Message_Control_Channel_1[24];

static uint8_t J1939_No_Of_Receive_Messages[2];
static uint8_t J1939_No_Of_Transmit_Messages[2];
static uint8_t J1939_Transmit_Enable[2];
static uint8_t J1939_Receive_Enable[2];

static J1939_Receive_Message_Control_T *J1939_Receive_Message_Control[2] =
{
   J1939_Receive_Message_Control_Channel_0,
   J1939_Receive_Message_Control_Channel_1,
};


uint8_t  J1939_MESSAGE_RX_OFFSET;
uint8_t  J1939_MESSAGE_TX_OFFSET;

uint8_t  J1939_MESSAGE_RX_OFFSET;
uint8_t  J1939_MESSAGE_TX_OFFSET;

static void J1939_Initialize_Receive_Manager (J1939_Channel_T  channel_num);
static void J1939_Initialize_Transmit_Manager (J1939_Channel_T  channel_num);
static void J1939_Manager (J1939_Channel_T  channel_num);
static void J1939_Update_Receive_Timers (J1939_Channel_T  channel_num);
static void J1939_Update_Transmit_Timers (J1939_Channel_T  channel_num);
static void J1939_Schedule_Transmit_Messages (J1939_Channel_T  channel_num);
static void J1939_Process_Receive_Messages (J1939_Channel_T  channel_num);
J1939_New_Message_Status_T J1939_Is_New_Message_Received (uint8_t in_msg_obj,
                                                          J1939_Receive_Message_Info_T    *rx_msg);
bool J1939_Transmit_Message (uint8_t n_msg_obj, J1939_Transmit_Message_Info_T     *tx_msg);
//=============================================================================
// Name: J1939_Initialize_Communication_Manager
//
// Description:
//     Initializes J1939 communication manager
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none.
//
//=============================================================================
void J1939_Initialize_Communication_Manager (J1939_Channel_T  channel_num)
{
   J1939_Receive_Enable[channel_num]  = true;
   J1939_Transmit_Enable[channel_num] = true;

   J1939_No_Of_Receive_Messages[0] = J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_0;
   J1939_No_Of_Receive_Messages[1] = J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_1;

   J1939_No_Of_Transmit_Messages[0]= J1939_NO_OF_TRANSMIT_MESSAGES_CHANNEL_0;
   J1939_No_Of_Transmit_Messages[1]= J1939_NO_OF_TRANSMIT_MESSAGES_CHANNEL_1;
   
   J1939_Initialize_Transmit_Manager (channel_num);
   J1939_Initialize_Receive_Manager (channel_num);
}


//=============================================================================
// Name: J1939_Initialize_Transmit_Manager
//
// Description:
//     Initializes J1939 transmit messages
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none.
//
//=============================================================================


//=============================================================================
// Name: J1939_Initialize_Receive_Manager
//
// Description:
//     Initializes J1939 receive messages
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none.
//
//=============================================================================


//=============================================================================
// Name: J1939_Update_Receive_Timers
//
// Description:
//     Updates J1939 RX message timers
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none.
//
//=============================================================================



//=============================================================================
// Name: J1939_Update_Transmit_Timers
//
// Description:
//     Updates J1939 TX message timers
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none.
//
//=============================================================================

//=============================================================================
// Name: J1939_Manager
//
// Description:
//    This function would be called by OS executive
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none
//
//=============================================================================

//=============================================================================
// Name: J1939_Handler_Timer_Task
//
// Description:
//    This function would be called by application to run the
//    J1939 Timer handler in the required OS Periodic loop
//
// Parameters: none
//
// Return Value: none
//
//=============================================================================


//=============================================================================
// Name: J1939_Handler_Periodic_Task
//
// Description:
//    This function would be called by application to run the
//    CAN handler in the required OS Periodic loop
//
// Parameters: none
//
// Return Value: none
//
//=============================================================================


//=============================================================================
// Name: J1939_Transmit_Unmanaged_Message
//
// Description:
//    Sends an unmanaged acknowledgment
//
// Parameters: J1939_Transmit_Message_Info_T  tx_message
//
// Return Value: none
//
//=============================================================================

//=============================================================================
// Name: J1939_RequestTxMsgService
//
// Description:
//
//
// Parameters: uint8_t index
//
// Return Value: none
//
//=============================================================================

//=============================================================================
// Name: J1939_Trigger_Transmit_Message_Service
//
// Description:
//    Call this API for self activated PGN Request from application
//
// Parameters: uint8_t index
//
// Return Value: none
//
//=============================================================================

//=============================================================================
// Name: J1939_Event_Trigger_Transmit
//
// Description:
//    Call this API for self activated PGN Request from application
//
// Parameters: uint8_t index
//
// Return Value: none
//
//=============================================================================

//=============================================================================
// Name: J1939_Disable_Transmit_Message_Service
//
// Description:
//    Call this API to disable J1939 TX messages for a particular channel
//
// Parameters: J1939_Channel_T  channel_num
//
// Return Value: none
//
//=============================================================================


//=============================================================================
// Name: J1939_Enable_Transmit_Message_Service
//
// Description:
//    Call this API to enable J1939 TX messages for a particular channel
//
// Parameters: J1939_Channel_T  channel_num
//
// Return Value: none
//
//=============================================================================

//=============================================================================
// Name: J1939_Disable_Receive_Message_Process
//
// Description:
//    Call this API to disable J1939 RX messages for a particular channel
//
// Parameters: J1939_Channel_T  channel_num
//
// Return Value: none
//
//=============================================================================


//=============================================================================
// Name: J1939_Enable_Receive_Message_Process
//
// Description:
//    Call this API to enable J1939 RX messages for a particular channel
//
// Parameters: J1939_Channel_T  channel_num
//
// Return Value: none
//
//=============================================================================


//=============================================================================
// Name: J1939_Transmit_Message_Confirmation
//
// Description:
//    Shall be called on successful message transmission
//
// Parameters: uint8_t  index
//
// Return Value: none
//
//=============================================================================


//=============================================================================
// Name: J1939_Is_New_Message_Received
//
// Description:
//    Facilitates the copy of message details in the rx buffer to the input
//    CanRxMsgType parameter and returns the new message status attribute of
//    J1939_msg_handler receive buffers if a new message is received
//
// Parameters: uint8_t                      | msg_obj
//             J1939_Receive_Message_Info_T |*rx_msg
//
// Return Value: J1939_New_Message_Status_T | new_message_status
//
//=============================================================================

//=============================================================================
// Name: J1939_Handler_Cold_Init
//
// Description:
//     Initializes J1939 message objects and enables the Vehicle [J1939] CAN Node
//
// Parameters: none.
//
// Return Value: none.
//
//=============================================================================
void J1939_Handler_Cold_Init (void)
{
   uint8_t                        msg_obj, counter, msg_length;
   CAN_Port_Message_Direction_T   message_dir;
   uint8_t                        *data_ptr;
   P_L_CAN_OBJECT_TYPE            msg_obj_cmd;
   int16_t                            msg_call_back;
   uint8_t                        msg_obj_offset;

   J1939_MESSAGE_RX_OFFSET = 0;
   J1939_MESSAGE_TX_OFFSET = (24 - J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_0);

   for (msg_obj = 0; msg_obj < J1939_NO_OF_MESSAGES; msg_obj++)
   {
      if (msg_obj < J1939_NO_OF_RECEIVE_MESSAGES)
      {
         msg_length = J1939_Message_Table[msg_obj].message_length;
         //The address of message data @ message buffer is stored in a temp pointer
         data_ptr   = (uint8_t *) &J1939_Receive_Message_Buffer[msg_obj].msg_data[0];
         J1939_Receive_Message_Buffer[msg_obj].new_msg = J1939_NEW_MESSAGE_UNAVAILABLE;

         for (counter = 0; counter < msg_length; counter++)
         {
            //Data buffer of receive messages in the table is cleared
            *data_ptr++ = 0;
         }

         message_dir = CAN_PORT_MSG_DIR_RECEIVE;
         msg_call_back = TRUE;
         msg_obj_offset = J1939_MESSAGE_RX_OFFSET;
      }
      else
      {
         msg_length = J1939_Message_Table[msg_obj].message_length;
         message_dir = CAN_PORT_MSG_DIR_TRANSMIT;
         msg_call_back = FALSE;
         msg_obj_offset = J1939_MESSAGE_TX_OFFSET;
      }

      msg_obj_cmd.P_L_CAN_DEVICE_NUMBER = FLEXCAN_DEVICE_A;
      msg_obj_cmd.P_L_CAN_MSG_NUMBER = msg_obj + msg_obj_offset;
      msg_obj_cmd.P_L_CAN_MSG_ID = J1939_Message_Table[msg_obj].message_ID;
      msg_obj_cmd.P_L_CAN_MSG_MASK = 0xFFFFFFFFUL;
      msg_obj_cmd.P_L_CAN_LENGTH = msg_length;
      msg_obj_cmd.P_L_CAN_TYPE = FLEXCAN_MSGOBJ_ID_EXT;
      msg_obj_cmd.P_L_CAN_DIRECTION = message_dir;
      msg_obj_cmd.P_L_CAN_CALLBACK_ENABLED = msg_call_back;
      hwi_can_configure_object (&msg_obj_cmd);
   }

#ifdef J1939_CH0_SELECTED
   J1939_Initialize_Communication_Manager (0);
#endif
   
}



//=============================================================================
// Name: J1939_Transmit_Message
//
// Description:
//     Initiates the transmission of a message.
//
// Parameters: uint8_t | in_j1939_msg_obj | message object to be transmitted
//                    CanTxMsgType* | tx_msg | CAN message to be transmitted.
//
// Return Value: bool   | true if transmit started.
//
//=============================================================================



//=============================================================================
// Name: Appl_Transmit_Message
//
// Description:
//     Application specific function to transmit J1939 message.
//
// Parameters: none.
//
// Return Value: none.
//
//=============================================================================



//=============================================================================
// Name: J1939_Message_Transmit_Callback
//
// Description:
//     This function is called upon the successful transmission of a J1939
//     message. The function in turn invokes J1939 notifier functions as
//     defined by the J1939 message table.
//
// Parameters: uint8_t | in_msg_obj | message object that was transmitted.
//
// Return Value: none
//
//=============================================================================


//=============================================================================
// Name: J1939_Message_Receive_Callback
//
// Description:
//     This function is called upon the successful reception of a J1939
//     message. The function in turn invokes J1939 notifier functions as
//     defined by the J1939 message table.
//
// Parameters: uint8_t | in_msg_obj | message object which was received
//
// Parameters: uint8_t* | in_data_buff | message buffer
//
// Parameters: uint8_t | in_data_length | message length
//
// Return Value: none
//
//=============================================================================
void J1939_Message_Receive_Callback (
   uint8_t     in_msg_obj,
   uint8_t     *in_data_buff,
   uint8_t     in_data_length)
{
   
}

CAN_Port_Error_T J1939_Get_BusOffState (void)
{

}




/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  =================     ==========================      *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release       *
* 2        02/03/2012    nz8l7x                code clean up                  *
******************************************************************************/
