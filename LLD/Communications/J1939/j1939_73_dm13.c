/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_73_dm13.c
*  Creation date :
*  Description   :Alarm Message Implementation
*  History       :
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"
#include "j1939_app.h"
#include "j1939_communication_manager.h"
#include "HLS.h"
#include "lux_type.h"

#define STOP_Broadcast   0
#define START_Broadcast  1
J1939_DM13_Message_Control_T J1939_dm13_Control;



/******************************************************************************
* Function : Service_PGN_57088
* Description : Service PGN
******************************************************************************/
static void Service_PGN_57088(J1939_Receive_Message_Info_T *rx_msg_ptr)
{
    uint8_t index;
    uint8_t Broadcast_temp;

    //only receive the message at the target adress was matched on the source adress or it was global adress
	if((J1939_GET_DEST_ADDR(rx_msg_ptr->ID)!=J1939_GLOBAL_DEST_ADDR)&&
	   (J1939_GET_DEST_ADDR(rx_msg_ptr->ID)!=KfHWIO_J193973_SA))
		return;
	if(crank_sig.engine_rpm >FixDefConst(100,RPM_W_Chery))
		return;
	
	for(index =0; index <rx_msg_ptr->Length; index ++)

	   J1939_73_dm13.Data[index]=  rx_msg_ptr->Data[index];
	 
	if(J1939_dm13_Control.Broadcast_State.Setup ==true)
	{
	   /**********************************************/
	   /*****************hold************************/
	   if(J1939_73_dm13.spn.byte4.spn_1236 ==0) //hold all device
	   {
	      J1939_dm13_Control.Broadcast_State.Hold =true;
		  J1939_dm13_Control.Timer =J1939_Update_Timer;

	   }else if(J1939_73_dm13.spn.byte4.spn_1236 ==1) //hold the device what the state been modified
	   {

		  if(J1939_dm13_Control.Broadcast_State.State_modified)
		  {	
		     J1939_dm13_Control.Broadcast_State.Hold =true;
		     J1939_dm13_Control.Timer =J1939_Update_Timer;
		  }else
		  {
		  //do nothing
		  }
		 
	   }else
	   {
	       //do nothing
	   }
	   /**********************************************/
	   /*****************Suspend**********************/
	   if((J1939_73_dm13.spn.byte4.spn_2618 ==0x00)||(J1939_73_dm13.spn.byte4.spn_2618 ==0x01))//Indefinite Suspend all or some broadcast message
	   {
	      J1939_dm13_Control.Broadcast_State.Suspend =Indefinite;
		  J1939_dm13_Control.Broadcast_State.Setup =false;
	      J1939_dm13_Control.Broadcast_State.Broadcast_state =STOP_BROADCAST;
	   }else if((J1939_73_dm13.spn.byte4.spn_2618 ==0x02)||(J1939_73_dm13.spn.byte4.spn_2618 ==0x03))//Temporary Suspend all or some broadcast message
	   {
	      J1939_dm13_Control.Broadcast_State.Suspend =Temporary;
		  J1939_dm13_Control.Suspend_t =J1939_73_dm13.spn.byte56.spn_2619;
		  J1939_dm13_Control.Timer =J1939_Update_Timer;
		  J1939_dm13_Control.Broadcast_State.Setup =false;
		  J1939_dm13_Control.Broadcast_State.Broadcast_state =STOP_BROADCAST;
	   }else if(J1939_73_dm13.spn.byte4.spn_2618 ==0x0E) //the broadcast message recover to normal mode
	   {
	      J1939_dm13_Control.Broadcast_State.Suspend =Normally;
		  J1939_dm13_Control.Broadcast_State.Setup =false;
		  J1939_dm13_Control.Broadcast_State.Broadcast_state =START_BROADCAST;
		  J1939_dm13_Control.Broadcast_State.State_modified =false;

	   }
	   
	}
	
	if(J1939_73_dm13.Data[4]==0xff&&J1939_73_dm13.spn.byte56.spn_2619 ==0xffff
		&&J1939_73_dm13.spn.byte78.spn_res ==0xffff)		   
	{
		if(J1939_73_dm13.spn.byte1.spn_639 <2)//action =stop or start broadcast
		{
			
			J1939_dm13_Control.Broadcast_State.State_modified =true; // the broadcast state was been modified
			J1939_dm13_Control.Broadcast_State.Setup =true;
			J1939_dm13_Control.Broadcast_State.Broadcast_state =J1939_73_dm13.spn.byte1.spn_639;
			J1939_dm13_Control.Timer =J1939_Update_Timer;

		}
		else if(J1939_73_dm13.spn.byte1.spn_1230 <2)//action =stop or start broadcast
		{	 

			J1939_dm13_Control.Broadcast_State.State_modified =true; // the broadcast state was been modified
			J1939_dm13_Control.Broadcast_State.Setup =true;
			J1939_dm13_Control.Broadcast_State.Broadcast_state =J1939_73_dm13.spn.byte1.spn_1230;
			J1939_dm13_Control.Timer =J1939_Update_Timer;
		}
	}	
}
/******************************************************************************
* Function : J1939_Receive_Initialize_73_dm13
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_Receive_Initialize_73_dm13(J1939_Receive_Message_Control_T * rx_msg_ctrl_ptr) 
{
	rx_msg_ctrl_ptr->Parse_Routine             = Service_PGN_57088;
	rx_msg_ctrl_ptr->Message_Lost_Timeout_W    = J1939_PGN_57088_TIMEOUT; //Message loss timeout setting
	rx_msg_ctrl_ptr->Message_Lost_Timer_W      = rx_msg_ctrl_ptr->Message_Lost_Timeout_W; // software timer for monitoring Message loss
	rx_msg_ctrl_ptr->Message_Lost_Routine      = NULL;
	rx_msg_ctrl_ptr->Message_Lost              = 0x00;
	rx_msg_ctrl_ptr->Message_Lost_Action_Taken = 0x00;
	J1939_73_dm13.spn.byte1.spn_1230 = START_BROADCAST;
	J1939_73_dm13.spn.byte1.spn_639  = START_BROADCAST;
	J1939_dm13_Control.Broadcast_State.Broadcast_state = START_BROADCAST;
	J1939_dm13_Control.Broadcast_State.Suspend =Normally;
	J1939_dm13_Control.Broadcast_State.Hold =false;
}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/

