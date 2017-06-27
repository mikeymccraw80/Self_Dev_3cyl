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

#define second_to_10ms  100
extern J1939_DM13_Message_Control_T J1939_dm13_Control;
static J1939_Transmit_Message_Control_T  J1939_Transmit_Message_Control[32];
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
uint32_t J1939_Update_Timer;

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
   J1939_Update_Timer =0;

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
static void J1939_Initialize_Transmit_Manager (J1939_Channel_T  channel_num)
{
   uint8_t index;

   for (index = 0; index < J1939_No_Of_Transmit_Messages[channel_num]; index++)
   {
      //Specific routines for each transmit message
      (*J1939_Transmit_Initialize[index]) (&J1939_Transmit_Message_Control[index]);
   }
}

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
static void J1939_Initialize_Receive_Manager (J1939_Channel_T  channel_num)
{
   uint8_t index;

   switch (channel_num)
   {
#ifdef J1939_CH0_SELECTED

      case J1939_CHANNEL_0:
         for (index = 0; index < J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_0; index++)
         {
            //Specific routines for each RX message
            (*J1939_Receive_Initialize_Channel_0[index]) (&J1939_Receive_Message_Control[channel_num][index]);
         }

         break;
#endif
      default:
         break;
   }
}


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
static void J1939_Update_Receive_Timers (J1939_Channel_T  channel_num)
{
   uint8_t                                      index;
   J1939_Receive_Message_Control_T   *rx_msg_ctrl_ptr;

   for (index = 0; index < J1939_No_Of_Receive_Messages[channel_num]; index++)
   {
      rx_msg_ctrl_ptr = &J1939_Receive_Message_Control[channel_num][index];

      if (rx_msg_ctrl_ptr->Message_Lost_Timer_W > 0)
      {
         rx_msg_ctrl_ptr->Message_Lost_Timer_W--;
         rx_msg_ctrl_ptr->Message_Lost = ( (0 == rx_msg_ctrl_ptr->Message_Lost_Timer_W) ? true : false);
      }
   }
}

//=============================================================================
// Name: J1939_Process_Receive_Messages
//
// Description:
//     Processes received J1939 messages
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none.
//
//=============================================================================
static void J1939_Process_Receive_Messages (J1939_Channel_T  channel_num)
{
   uint8_t                                        index;
   J1939_New_Message_Status_T        new_message_status;
   J1939_Receive_Message_Info_T             rx_msg_info;
   J1939_Receive_Message_Control_T     *rx_msg_ctrl_ptr;

   for (index = 0; index < J1939_No_Of_Receive_Messages[channel_num]; index++)
   {
      rx_msg_ctrl_ptr    = &J1939_Receive_Message_Control[channel_num][index];
      new_message_status = J1939_Is_New_Message_Received (index, &rx_msg_info);

      if (J1939_NEW_MESSAGE_AVAILABLE == new_message_status)
      {
         //Indicate message is not lost and reset timer
         rx_msg_ctrl_ptr->Message_Lost              = false;
         rx_msg_ctrl_ptr->Message_Lost_Action_Taken = false;
         rx_msg_ctrl_ptr->Message_Lost_Timer_W      = rx_msg_ctrl_ptr->Message_Lost_Timeout_W;
         //Call the parse routine
         (*rx_msg_ctrl_ptr->Parse_Routine) (&rx_msg_info);
      }
      else if ( (true  == rx_msg_ctrl_ptr->Message_Lost) &&
                (false == rx_msg_ctrl_ptr->Message_Lost_Action_Taken))
      {
         //Message not received
         rx_msg_ctrl_ptr->Message_Lost_Action_Taken = true;
         rx_msg_ctrl_ptr->Message_Lost_Routine();
      }
   }
}

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
static void J1939_Update_Transmit_Timers (J1939_Channel_T  channel_num)
{
   uint8_t                                       index;
   J1939_Transmit_Message_Control_T   *tx_msg_ctrl_ptr;

   for (index = 0; index < J1939_No_Of_Transmit_Messages[channel_num]; index++)
   {
      tx_msg_ctrl_ptr = &J1939_Transmit_Message_Control[index];
      if(index<5){
	      if (tx_msg_ctrl_ptr->Time_To_Next_Service_W > 0)
	      {
	         tx_msg_ctrl_ptr->Time_To_Next_Service_W--;
	         tx_msg_ctrl_ptr->Time_To_Service = ( (0 == tx_msg_ctrl_ptr->Time_To_Next_Service_W) ? true : false);
	      }

	      if (tx_msg_ctrl_ptr->Tx_Timeout_Timer_W > 0)
	      {
	         tx_msg_ctrl_ptr->Tx_Timeout_Timer_W--;
	         tx_msg_ctrl_ptr->Tx_Timeout = ( (0 == tx_msg_ctrl_ptr->Tx_Timeout_Timer_W) ? true : false);
	      }

	  }else{

	 /*******************************************************/
		  /*****update the j1939 broadcast state******************/
		  if((J1939_dm13_Control.Broadcast_State.Suspend ==Normally)&&
		  	 (J1939_dm13_Control.Broadcast_State.Hold ==false)&&
		  	 (J1939_dm13_Control.Broadcast_State.State_modified==true))
		  {
			if((J1939_Update_Timer - J1939_dm13_Control.Timer)>=(6*second_to_10ms))
			{	
				J1939_dm13_Control.Broadcast_State.State_modified =false;
				J1939_dm13_Control.Broadcast_State.Setup =false;
			    J1939_dm13_Control.Broadcast_State.Broadcast_state =\
					      (!J1939_dm13_Control.Broadcast_State.Broadcast_state);
			}
		  }
		  else
		  {
			  if(J1939_dm13_Control.Broadcast_State.Suspend!=Normally)
		      {
		          //at suspend temporary mode
	              if(J1939_dm13_Control.Broadcast_State.Suspend == Temporary)
	              {
					//if suspend time exceeded the experied time then the suspend state will be recovered to normal mode
					if((J1939_Update_Timer - J1939_dm13_Control.Timer)>=(J1939_dm13_Control.Suspend_t*second_to_10ms))
					{
						J1939_dm13_Control.Broadcast_State.Suspend = Normally;
						J1939_dm13_Control.Broadcast_State.State_modified =false;
						J1939_dm13_Control.Broadcast_State.Broadcast_state =START_BROADCAST;
					}
				  }
			  }
			  else
			  {
		          if(J1939_dm13_Control.Broadcast_State.Hold)
		          {   
		            //if the hold time exceeded 6 second then the hold state will be recovered normal mode
					if((J1939_Update_Timer - J1939_dm13_Control.Timer)>=(6*second_to_10ms))
					{
					  J1939_dm13_Control.Broadcast_State.Hold  =false;
					  J1939_dm13_Control.Broadcast_State.Setup =false;
					  J1939_dm13_Control.Broadcast_State.State_modified =false;
					  J1939_dm13_Control.Broadcast_State.Broadcast_state =\
					      (!J1939_dm13_Control.Broadcast_State.Broadcast_state);
					}
				  }
			  }
		  }
	      /*******************************************************/
		  /*****update the j1939 broadcast transmit timer*********/  
		 if(J1939_dm13_Control.Broadcast_State.Broadcast_state ==START_BROADCAST)
		  {
		      if (tx_msg_ctrl_ptr->Time_To_Next_Service_W > 0)
		      {
		         tx_msg_ctrl_ptr->Time_To_Next_Service_W--;
		         tx_msg_ctrl_ptr->Time_To_Service = ( (0 == tx_msg_ctrl_ptr->Time_To_Next_Service_W) ? true : false);
		      }

		      if (tx_msg_ctrl_ptr->Tx_Timeout_Timer_W > 0)
		      {
		         tx_msg_ctrl_ptr->Tx_Timeout_Timer_W--;
		         tx_msg_ctrl_ptr->Tx_Timeout = ( (0 == tx_msg_ctrl_ptr->Tx_Timeout_Timer_W) ? true : false);
		      }
		 }
   }
}

}
//=============================================================================
// Name: J1939_Update_timer
//
// Description:
//     Updates J1939 timer
//
// Parameters: none
//
// Return Value: none.
//
//=============================================================================
static void J1939_Update_timer(void)
{
  J1939_Update_Timer ++; 
}
//=============================================================================
// Name: J1939_Schedule_Transmit_Messages
//
// Description:
//    Checks to see if a J1939 TX message is ready to be sent and
//    sends it if it is ready
//
// Parameters: J1939_Channel_T | channel_num
//
// Return Value: none.
//
//=============================================================================
static void J1939_Schedule_Transmit_Messages (J1939_Channel_T  channel_num)
{
{
   bool                                  tx_msg_status = false;
   bool                                  tx_msg_status_send = false;
   uint8_t                                       index;
   J1939_Transmit_Message_Info_T           tx_msg_info;
   J1939_Transmit_Message_Control_T   *tx_msg_ctrl_ptr;

   for (index = 0; index < J1939_NO_OF_TRANSMIT_MESSAGES; index++)
   {
      tx_msg_ctrl_ptr = &J1939_Transmit_Message_Control[index];

      if (true == tx_msg_ctrl_ptr->Time_To_Service)
      {
         tx_msg_info.Requested = tx_msg_ctrl_ptr->Requested;
         tx_msg_info.Requester = tx_msg_ctrl_ptr->Requester;
         
         tx_msg_status_send = (*tx_msg_ctrl_ptr->Service_Routine) (&tx_msg_info);

         if (tx_msg_status_send)
         {
            tx_msg_status = J1939_Transmit_Message (index, &tx_msg_info);
         }

         if (tx_msg_ctrl_ptr->Time_To_Next_Service_W == 0)
         {
             if(true==tx_msg_ctrl_ptr->Event_Trigger_Flag)
		    {
		     /*Clear Trigger Flag*/
		     tx_msg_ctrl_ptr->Event_Trigger_Flag=false;
             tx_msg_ctrl_ptr->Time_To_Next_Service_W =tx_msg_ctrl_ptr->Event_Trigger_Service_Buffer-1;
			 
			}
			 else
			 {
			  tx_msg_ctrl_ptr->Time_To_Next_Service_W = tx_msg_info.Callback_Time_W;
			 }
            
         }

         //if TX fail then service again next loop, else update service time
         if (true == tx_msg_status)
         {
            //Update time to next service/transmit of this message
            tx_msg_ctrl_ptr->Tx_Timeout_Timer_W     = tx_msg_info.Callback_Timeout_W;
            tx_msg_ctrl_ptr->Time_To_Service        = false;
            tx_msg_ctrl_ptr->Requested              = false;
         }
      }

      if ( (true == tx_msg_ctrl_ptr->Tx_Timeout) && (false == tx_msg_status))
      {
         //Call the message timeout routine if one exists
         tx_msg_ctrl_ptr->Tx_Timeout = false;
      }
   }
}
}

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
static void J1939_Manager (J1939_Channel_T  channel_num)
{
      //Call these functions regardless, important info must be updated
   if (true == J1939_Receive_Enable[channel_num])
   {
      J1939_Process_Receive_Messages (channel_num);
   }

   if (true == J1939_Transmit_Enable[channel_num])
   {
      J1939_Schedule_Transmit_Messages (channel_num);
   }
}
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
void J1939_Handler_Timer_Task (void)
{
   J1939_Update_timer();
#ifdef J1939_CH0_SELECTED
   J1939_Update_Receive_Timers (J1939_CHANNEL_0);
   J1939_Update_Transmit_Timers (J1939_CHANNEL_0);
#endif
#ifdef J1939_CH1_SELECTED
   J1939_Update_Receive_Timers (J1939_CHANNEL_1);
   J1939_Update_Transmit_Timers (J1939_CHANNEL_1);
#endif
}

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
void J1939_Handler_Periodic_Task (void)
{
#ifndef J1939_HANDLER_TIMER_TASK_SUPPORTED
   J1939_Handler_Timer_Task();
#endif

   #ifdef J1939_TEST_STUB
   J1939_Transmit_Test_Task();
   #endif

   #ifdef J1939_CH0_SELECTED
   J1939_Manager(J1939_CHANNEL_0);
   #endif

   #ifdef J1939_CH1_SELECTED
   J1939_Manager(J1939_CHANNEL_1);
   #endif

   #ifdef J1939_TEST_STUB
   J1939_Receive_Test_Task();
   #endif
}

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
can_boolean_t J1939_Transmit_Unmanaged_Message (J1939_Transmit_Message_Info_T *tx_message)
{
   // Last index is reserved for Unmanaged response);
   return ( (can_boolean_t) J1939_Transmit_Message (J1939_TX_PGN_Denny_INDEX, tx_message));
}

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
void J1939_RequestTxMsgService (TxMsgIndexType index, uint8_t requester)
{
   J1939_Transmit_Message_Control[index].Requested = true;
   J1939_Transmit_Message_Control[index].Requester = requester;
}
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
void J1939_Trigger_Transmit_Message_Service (uint8_t index)
{
   J1939_Transmit_Message_Control[index].Time_To_Next_Service_W = 0;
   J1939_Transmit_Message_Control[index].Time_To_Service        = true;
}
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
void J1939_Event_Trigger_Transmit(uint8_t index)
{
  if((true!=J1939_Transmit_Message_Control[index].Time_To_Service)&& 
 	(J1939_Transmit_Message_Control[index].Time_To_Next_Service_W>1))
   	{
       J1939_Transmit_Message_Control[index].Event_Trigger_Flag=true;   
	   J1939_Transmit_Message_Control[index].Event_Trigger_Service_Buffer= J1939_Transmit_Message_Control[index].Time_To_Next_Service_W;
       J1939_Transmit_Message_Control[index].Time_To_Next_Service_W = 0;	   
       J1939_Transmit_Message_Control[index].Time_To_Service = true;
       
    }
}

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
J1939_New_Message_Status_T J1939_Is_New_Message_Received (
   uint8_t                       in_msg_obj,
   J1939_Receive_Message_Info_T    *rx_msg)
{
   uint8_t                      counter, msg_length;
   uint32_t                     msg_id;
   uint8_t                      *data_ptr;
   J1939_New_Message_Status_T   new_message_status = J1939_NEW_MESSAGE_UNAVAILABLE;

   if (in_msg_obj < J1939_NO_OF_RECEIVE_MESSAGES)
   {
      new_message_status = J1939_Receive_Message_Buffer[in_msg_obj].new_msg;
      msg_length         = J1939_Message_Table[in_msg_obj].message_length;
      msg_id               = J1939_Receive_Message_Buffer[in_msg_obj].msg_id;

      if (J1939_NEW_MESSAGE_AVAILABLE == new_message_status)
      {
         //rx_msg->ID     = J1939_Message_Table[in_msg_obj].message_ID;
         rx_msg->ID     = msg_id;		//msg-id is different from J1939_Message_Table.message_ID
         rx_msg->Length = msg_length;
         //The address of message data @ message buffer is stored in a temp pointer
         data_ptr       = (uint8_t *) &J1939_Receive_Message_Buffer[in_msg_obj].msg_data[0];

         for (counter = 0; counter < msg_length; counter++)
         {
            //Data from table is copied in to the APPL buffer
            rx_msg->Data[counter] = *data_ptr++;
         }

         //After data is copied, new message flag is updated to 'UNAVAILABLE' status
         J1939_Receive_Message_Buffer[in_msg_obj].new_msg = J1939_NEW_MESSAGE_UNAVAILABLE;
      }
   }

   return (new_message_status);
}
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

   J1939_MESSAGE_RX_OFFSET = 18; //Rx obj was scheduled from MB18
   J1939_MESSAGE_TX_OFFSET = (32 - J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_0);

   for (msg_obj = 0; msg_obj < J1939_NO_OF_RECEIVE_MESSAGES; msg_obj++)
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

      msg_obj_cmd.P_L_CAN_DEVICE_NUMBER = FLEXCAN_DEVICE_A;
      msg_obj_cmd.P_L_CAN_MSG_NUMBER = msg_obj + msg_obj_offset;
      msg_obj_cmd.P_L_CAN_MSG_ID = J1939_Message_Table[msg_obj].message_ID;
      //if(PDU1), Receice_PGN was masked by cal KfHWIO_J193973_SA
      if(msg_obj_cmd.P_L_CAN_MSG_ID<=0x18F00000){
         msg_obj_cmd.P_L_CAN_MSG_ID |= (KfHWIO_J193973_SA<<8);
      }
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
bool J1939_Transmit_Message (
   uint8_t                         in_msg_obj,
   J1939_Transmit_Message_Info_T     *tx_msg)
{
   bool    tx_status;

   tx_status = HAL_CAN_Transmit_Message(tx_msg->ID, tx_msg->Length, &tx_msg->Data[0]);	

   if(tx_status == true)
   {
      HAL_CAN_Err_Status[0] = CAN_PORT_ERROR_NONE;
   }

   return (tx_status);
}

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
   uint32_t   in_msg_id,
   uint8_t     *in_data_buff,
   uint8_t     in_data_length)
{
   uint8_t  j1939_rx_msg_obj, counter;
   uint8_t  *data_ptr;
   //in_msg_obj is the msg obj number in CAN hardware
   //(in_msg_obj - J1939_MESSAGE_OFFSET) gives the starting index
   //of receive message objects in the J1939 table
   j1939_rx_msg_obj = in_msg_obj - J1939_MESSAGE_RX_OFFSET;

   if (J1939_Message_Table[j1939_rx_msg_obj].message_length == in_data_length)
   {
      //The address of message data @ message buffer is stored in a temp pointer
      data_ptr = (uint8_t *) &J1939_Receive_Message_Buffer[j1939_rx_msg_obj].msg_data[0];

      for (counter = 0; counter < J1939_Message_Table[j1939_rx_msg_obj].message_length; counter++)
      {
         //Received data is copied in to the data buffer in the table
         *data_ptr++ = *in_data_buff++;
      }

      //New message flag is updated to 'AVAILABLE' status
      J1939_Receive_Message_Buffer[j1939_rx_msg_obj].new_msg = J1939_NEW_MESSAGE_AVAILABLE;
      J1939_Receive_Message_Buffer[j1939_rx_msg_obj].msg_id = in_msg_id;
   }

   HAL_CAN_Err_Status[0] = CAN_PORT_ERROR_NONE;
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
