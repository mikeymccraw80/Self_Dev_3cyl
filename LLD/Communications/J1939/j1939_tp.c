/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: CNG E483                                                         *
* File Name:  j1939_tp.c                                                    *
* File Description:                                                         *
* J1939 Transport Protocol Manager                                          *
*****************************************************************************/
#include "j1939_tp.h"
#include "j1939_pgn_config.h"

static void Parse_PGN_60416 (J1939_Receive_Message_Info_T *RxMsg);
/***************************************************************************/
/* FUNCTION: Parse_PGN_60416                                               */
/* Description: Transport protocol management connection to CAN manager    */
/***************************************************************************/
static void Parse_PGN_60416 (J1939_Receive_Message_Info_T *RxMsg)
{
   switch (RxMsg->Data[0])
   {
      case J1939_TP_CM_RTS :
         ParseTransportIn_RTS (RxMsg);
         break;

      case J1939_TP_CM_CTS :
         ParseTransportOut_CTS (RxMsg);
         break;

      case J1939_TP_CM_ABORT :
         /* Can be data sender or data receiver */
         ParseTransportOut_Abort (RxMsg);
         ParseTransportIn_Abort (RxMsg);
         break;

      case J1939_TP_CM_END_ACK :
         ParseTransportOut_EndAck (RxMsg);
         break;

      case J1939_TP_CM_BAM :  /* invalid because dest addr should be gobal */
      default :
         break;
   }
}

/***************************************************************************/
/* FUNCTION: TpParseSrcAndPgn                                              */
/***************************************************************************/
void TpParseSrcAndPgn (J1939_Receive_Message_Info_T *RxMsg, uint8_t *SrcPtr,
                       uint32_t *PgnPtr)
{
   *SrcPtr = (uint8_t) J1939_GET_SRC_ADDR (RxMsg->ID);
   /* Byte 5 - Parameter Group Number Bits 23-16 */
   /* Byte 6 - Parameter Group Number Bits 15-8 */
   /* Byte 7 - Parameter Group Number Bits 7-0 */
   *PgnPtr = ( (uint32_t) RxMsg->Data[7] << 16);
   *PgnPtr |= ( (uint32_t) RxMsg->Data[6] << 8);
   *PgnPtr |= (uint32_t) RxMsg->Data[5];
}


/***************************************************************************/
/* FUNCTION: PreparePgn60416Msg                                          */
/***************************************************************************/
void PreparePgn60416Msg (J1939_Transmit_Message_Info_T *TxMsgPtr, uint8_t DestAddr_B, uint32_t Pgn_L)
{
   uint32_t Id;
   //TxMsgPtr->ExtendedId = 0x01;
   Id = J1939_PUT_DEST_ADDR (J1939_PGN_60416_BASE_ID, DestAddr_B);
   TxMsgPtr->ID = J1939_ADD_THIS_SRC_ADDR (Id);
   TxMsgPtr->Length = J1939_PGN_60416_LENGTH;
   /* Assign Byte 7 - Parameter Group Number Bits 23-16 */
   /* Assign Byte 6 - Parameter Group Number Bits 15-8 */
   /* Assign Byte 5 - Parameter Group Number Bits 7-0 */
   TxMsgPtr->Data[5] = (uint8_t) (Pgn_L & 0x0000FF);
   TxMsgPtr->Data[6] = (uint8_t) ((Pgn_L & 0x00FF00) >> 8);
   TxMsgPtr->Data[7] = (uint8_t) ((Pgn_L & 0xFF0000) >> 16);   
}


/***************************************************************************/
/* FUNCTION: BuildTpAbortMsg                                               */
/***************************************************************************/
void BuildTpAbortMsg (J1939_Transmit_Message_Info_T *TxMsgPtr, uint8_t DestAddr_B,
                      uint32_t Pgn_L, uint8_t AbortReason_B)
{
   PreparePgn60416Msg (TxMsgPtr, DestAddr_B, Pgn_L);
   TxMsgPtr->Data[0] = J1939_TP_CM_ABORT;
   TxMsgPtr->Data[1] = AbortReason_B;
   TxMsgPtr->Data[2] = J1939_DATA_NOT_AVAILABLE;
   TxMsgPtr->Data[3] = J1939_DATA_NOT_AVAILABLE;
   TxMsgPtr->Data[4] = J1939_DATA_NOT_AVAILABLE;
}

/***************************************************************************/
/* FUNCTION: J1939_RxInit_PGN_60416                                        */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J1939_RxInit_PGN_60416 (J1939_Receive_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Parse_Routine = Parse_PGN_60416;
   MsgCtrl->Message_Lost = 0x00;
   MsgCtrl->Message_Lost_Action_Taken = 0x00;
   MsgCtrl->Message_Lost_Timeout_W = CAN_NO_LOST_TIMER;
   MsgCtrl->Message_Lost_Timer_W = MsgCtrl->Message_Lost_Timeout_W;
}
/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/
