/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_65296.c
*  Creation date :
*-----------------------------------------------------------------------------
*  Description   :Remote Activation Message Implementation
*-----------------------------------------------------------------------------
*  History       :
*-----------------------------------------------------------------------------
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"
#include "j1939_app.h"

/******************************************************************************
* Function : J1939_73_dm7
* Description : Remote Activation Message
* Start Posn      Length in bits      Parameter Name
* 1                 8          Operating_Cond_Update
* 2                 8          Service_Requested
* 3                 8          Desired_Output_Voltage
******************************************************************************/
static void J1939_Message_Lost_Routine_73_dm7(void);
static void J1939_Parse_73_dm7(J1939_Receive_Message_Info_T *rx_msg_ptr);

#define Injector1 1
#define Injector2 2
#define Injector3 3
#define fuelpump  4
#define igncoil1  5
#define igncoil2  6
#define igncoil3  7
#define iac       8
#define fan       9
#define CCP       10


static void J1939_Message_Lost_Routine_73_dm7(void)
{
   
}

/******************************************************************************
* Function : J1939_Parse_73_dm7
* Description : Parse Data From Engine. If Raw data equals Enginnering data,
*               copy the data to application signal buffer without any change
******************************************************************************/
static void J1939_Parse_73_dm7(J1939_Receive_Message_Info_T *rx_msg_ptr)
{
   uint8_t index, TestID, b_surpport;
   bool           PgnFound;
   uint32_t       checkPgn;

   
   /* Search for matching Tx message that is availble upon request */
   PgnFound = false;

   for( index =0; index<rx_msg_ptr->Length; index++ )
   {
        J1939_73_dm7.Buffer[index] = rx_msg_ptr->Data[index];  //Copy to Application Signal Buffer
   }
   TestID = J1939_73_dm7.bytes.spn_1224;
   if((TestID>0)&& (TestID<65))
   {

	  J1939_73_dm8.spn_1224 = TestID;
	  b_surpport =true;
      switch (TestID)
      {
         case Injector1:
            B_Inj0Req =1;
			break;
		 case Injector2:
            B_Inj1Req =1;
			break;
	     case Injector3:
            B_Inj2Req =1;
			break;
		 case fuelpump:
            B_FulPReq =1;
			break;
		 case igncoil1:
            B_Ign0Req =1;
			break;
		 case igncoil2:
            B_Ign1Req =1;
			break;
		 case igncoil3:
            B_Ign2Req =1;
			break;
		 case iac:
            b_surpport =false;
			break;
		 case fan:
            B_Fan1Req =1;
			break;
		 case CCP:
            b_surpport =false;
			break;
	     default :
            b_surpport =false;
            break;

	  }
      checkPgn      = J193973_PGN_65232_BASE_ID; //DM8
      if(b_surpport !=false)
      {
		  for (index = 0; index < J1939_NO_OF_TRANSMIT_MESSAGES; index++)
		  {
		      /* Check if message PGN matches the requested PGN and also check if */
		      /* the message has a valid service function (CCP2 entries may not)    */

		    if ( checkPgn == 
		      J1939_Message_Table[J1939_NO_OF_RECEIVE_MESSAGES + index].message_ID )
		       // && (CAN_CkValidTxMsgServiceRoutine (Bus, Index))) 
		      {
		         PgnFound = true;
		         J1939_RequestTxMsgService (index, J1939_GET_SRC_ADDR(rx_msg_ptr->ID));
		         J1939_Trigger_Transmit_Message_Service ( (uint8_t) index);
		         break;
		      }

		  }
      }
	  if(PgnFound !=true)
	     J1939_SendUnmanagedAcknowledgement (NegAck, J1939_73_dm7_BASE_ID);
   }else
   { /* If requested PGN not supported then return NEG ACK */
         J1939_SendUnmanagedAcknowledgement (NegAck, J1939_73_dm7_BASE_ID);
   }
   
}


/******************************************************************************
* Function : J1939_Receive_Initialize_PGN_58112
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_Receive_Initialize_73_dm7(J1939_Receive_Message_Control_T * rx_msg_ctrl_ptr)
{
   rx_msg_ctrl_ptr->Parse_Routine             = J1939_Parse_73_dm7;
   rx_msg_ctrl_ptr->Message_Lost_Timeout_W    = J1939_73_dm7_TIMEOUT; //Message loss timeout setting
   rx_msg_ctrl_ptr->Message_Lost_Timer_W      = rx_msg_ctrl_ptr->Message_Lost_Timeout_W; // software timer for monitoring Message loss
   rx_msg_ctrl_ptr->Message_Lost_Routine      = J1939_Message_Lost_Routine_73_dm7;
   rx_msg_ctrl_ptr->Message_Lost              = 0x00;
   rx_msg_ctrl_ptr->Message_Lost_Action_Taken = 0x00;

}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/

