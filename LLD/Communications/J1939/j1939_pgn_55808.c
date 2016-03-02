/******************************************************************************
*  Project       : J1939 - PGN Specific Configuration
*  Module        : Message Configurations
*  File          : j1939_pgn_55808.c
*  Creation date :
*-----------------------------------------------------------------------------
*  Description   :Remote Activation Message Implementation
*-----------------------------------------------------------------------------
*  History       :
*-----------------------------------------------------------------------------
* Copyright 2010 Delphi Technologies, Inc., All rights reserved
******************************************************************************/

#include  "j1939_pgn_55808.h"
#include  "j1939_app.h"
#include  "intr_ems.h"


static J1939_DATA_T  J1939_pgn_55808;


static bool Jumptokernel;

static uint8_t StartRoutineByIdentifier(void)
{
	if((GetVIOS_v_VehSpd() == V_KPH(0))
    && (GetVIOS_n_EngSpd() == V_RPM(0)))
	{
		//VbCopyAndExecuteKernelPending =true;
		return (0x00);
	}
	else
	{
		return (0x7f);
	}

 
  } /*** End of KwJ14230StopDiagnosticSession ***/
static void Build_PositiveResponse(void)
{

	J1939_pgn_55808.data[0]=0x04;
	J1939_pgn_55808.data[1]=0x71;
	J1939_pgn_55808.data[2]=0x01;
	J1939_pgn_55808.data[3]=0xf0;
	J1939_pgn_55808.data[4]=0x00;

}

static void Build_NegativeResponse(uint8_t Sid, uint8_t fail)
{

	J1939_pgn_55808.data[0]=0x03;
	J1939_pgn_55808.data[1]=NegativeResponseServiceIdentifier;
	J1939_pgn_55808.data[2]=0x31;
	J1939_pgn_55808.data[3]=Sid;

}
/******************************************************************************
* Function : Service_PGN_55808
* Description : Parse Data From Engine. If Raw data equals Enginnering data,
*               copy the data to application signal buffer without any change
******************************************************************************/
void J1939_Parse_pgn_55808(J1939_Receive_Message_Info_T *RxMsg)
{
	uint8_t index, return_b;
	bool    PgnFound;
	uint8_t SubFunction;

	SubFunction= RxMsg->Data[1];
	switch(SubFunction)
	{
	
		case SidInitiateDiagnosticOperation:
			
			if((RxMsg->Data[0]==SidInitiateDiagnostic_length))
			{
				J1939_pgn_55808.data[0]=0x06;
				J1939_pgn_55808.data[1]=0x50;
				J1939_pgn_55808.data[2]=RxMsg->Data[2];
				J1939_pgn_55808.data[3]=0x00;
				J1939_pgn_55808.data[4]=0x32;
				J1939_pgn_55808.data[5]=0x13;
				J1939_pgn_55808.data[6]=0x88;
			}
			else
			{
				Build_NegativeResponse(SidInitiateDiagnosticOperation,IncorrectMessageLength);
			}
			break;
			
		case SidSecurityAccess:
			
			if((RxMsg->Data[0]==SidSecurityAccess_length))
			{
				J1939_pgn_55808.data[0]=0x04;
				J1939_pgn_55808.data[1]=0x67;
				J1939_pgn_55808.data[2]=RxMsg->Data[2];
				J1939_pgn_55808.data[3]=0x00;
				J1939_pgn_55808.data[4]=0x00;

			}
			else
			{
				Build_NegativeResponse(SidSecurityAccess,IncorrectMessageLength);
			}
			break;
			
		case SidRoutineControl :
			
			if((RxMsg->Data[0]==SidRoutineControl_length))
			{
				if((RxMsg->Data[2]==0x01)\
					&&(RxMsg->Data[3]==0xf0)&&(RxMsg->Data[4]==0x00))
				{
					return_b = StartRoutineByIdentifier();
					//return_b =0;
					if(return_b !=0)
					{
						Build_NegativeResponse(SidRoutineControl,ConditionsNotCorrectOrRequestSequenceError);
						Jumptokernel =false;
					}
					else
					{
						Build_PositiveResponse();
						Jumptokernel =true;//to make sure jump to kernel was after response the service
					}
				}
				else
				{
					Build_NegativeResponse(SidRoutineControl,SubFunctionNotSupported_InvalidFormat);
					Jumptokernel =false;
				}
			}
			else
			{
				Build_NegativeResponse(SidRoutineControl,IncorrectMessageLength);
				Jumptokernel =false;
			}

			break;

		default:
			break;

		}


	for (index = 0; index < J1939_NO_OF_TRANSMIT_MESSAGES; index++)
	{
	  /* Check if message PGN matches the requested PGN and also check if */
	  /* the message has a valid service function (CCP2 entries may not)    */
		if ( J1939_PGN_55808_BASE_ID == 
		  (J1939_Message_Table[J1939_NO_OF_RECEIVE_MESSAGES + index].message_ID ) )
		   // && (CAN_CkValidTxMsgServiceRoutine (Bus, Index))) 
		{
		     PgnFound = true;
		     J1939_RequestTxMsgService (index, J1939_GET_SRC_ADDR(RxMsg->ID));
		     J1939_Trigger_Transmit_Message_Service ( (uint8_t) index);
		     break;
		}
	}
	/* If requested PGN not supported then return NEG ACK */
	if ( (! PgnFound) &&
	    (J1939_GET_DEST_ADDR (RxMsg->ID) != J1939_GLOBAL_DEST_ADDR))
	{
	  J1939_SendUnmanagedAcknowledgement (NegAck, J1939_PGN_55808_BASE_ID);
	}

}

/******************************************************************************
* Function : Service_PGN_55808
* Description : Service PGN
******************************************************************************/
static bool Service_PGN_55808(J1939_Transmit_Message_Info_T *tx_msg_ptr)
{
    J1939_DATA_T *jd = (J1939_DATA_T *)&J1939_pgn_55808;
    uint8_t i;
    tx_msg_ptr->ID                 = J1939_ADD_THIS_SRC_ADDR((uint16_t)((tx_msg_ptr->Requester)<<8)|J1939_PGN_55808_BASE_ID);
    tx_msg_ptr->Length             = J1939_PGN_55808_LENGTH;
    tx_msg_ptr->Data[0]            = jd->data[0];
    tx_msg_ptr->Data[1]            = jd->data[1];
    tx_msg_ptr->Data[2]            = jd->data[2];
    tx_msg_ptr->Data[3]            = jd->data[3];
    tx_msg_ptr->Data[4]            = jd->data[4];
    tx_msg_ptr->Data[5]            = jd->data[5];
    tx_msg_ptr->Data[6]            = jd->data[6];
    tx_msg_ptr->Data[7]            = jd->data[7];
    tx_msg_ptr->Callback_Time_W    = J1939_PGN_55808_FREQ;
    tx_msg_ptr->Callback_Timeout_W = J1939_PGN_55808_TIMEOUT;
	
	if(Jumptokernel)
	{
		VbCopyAndExecuteKernelPending =true;
		Jumptokernel =false;
	}
	else
	{
		VbCopyAndExecuteKernelPending =false;
	}
	
    return(true);
}

/******************************************************************************
* Function : J1939_RxInit_PGN_55808
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_RxInit_PGN_55808(J1939_Receive_Message_Control_T * rx_msg_ctrl_ptr)
{
   rx_msg_ctrl_ptr->Parse_Routine             = J1939_Parse_pgn_55808;
   rx_msg_ctrl_ptr->Message_Lost_Timeout_W    = J1939_PGN_55808_TIMEOUT; //Message loss timeout setting
   rx_msg_ctrl_ptr->Message_Lost_Timer_W      = rx_msg_ctrl_ptr->Message_Lost_Timeout_W; // software timer for monitoring Message loss
   rx_msg_ctrl_ptr->Message_Lost_Routine      = NULL;
   rx_msg_ctrl_ptr->Message_Lost              = 0x00;
   rx_msg_ctrl_ptr->Message_Lost_Action_Taken = 0x00;

}

/******************************************************************************
* Function : J1939_TxInit_PGN_55808
* Description : Initialize hooks to can manager
******************************************************************************/
void J1939_TxInit_PGN_55808(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr) 
{
    tx_msg_ctrl_ptr->Service_Routine        = Service_PGN_55808 ;
    tx_msg_ctrl_ptr->Time_To_Service        = 0x00;
    tx_msg_ctrl_ptr->Time_To_Next_Service_W = J1939_PGN_55808_FREQ;
    tx_msg_ctrl_ptr->Tx_Timeout             = 0x00;
    tx_msg_ctrl_ptr->Tx_Timeout_Timer_W     = J1939_PGN_55808_TIMEOUT;
}
/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/

