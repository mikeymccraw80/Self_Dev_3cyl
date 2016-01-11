/*****************************************************************************
 * Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
 * AUTHORS: Sandeep, Prakash, Mehak                                          *
 * Project: CNG E483                                                         *
 * File Name:  j1939_73_dm4.c                                                *
 * File Description:                                                         *
 * Diagnostic Message 4 Implementation                                       *
 *****************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"


static void BuildPgn65229NoDtcPacket (J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t ServiceDm4TransportOut (TpOutStateType State,
                                             J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t Service_PGN_65229 (J1939_Transmit_Message_Info_T *TxMsg);
/************************************************************************/
/* Global Variables                                                     */
/************************************************************************/
static uint8_t J1939_DM4_Msg_Snapshot[J1939_DM4_BUFFER_SIZE];
static uint16_t NumOfFreezeFrameBytes;

/***************************************************************************/
/* FUNCTION: BuildPgn65229NoDtcPacket                                      */
/***************************************************************************/
static void BuildPgn65229NoDtcPacket (J1939_Transmit_Message_Info_T *TxMsg)
{
   TxMsg->Extended_ID = CAN_cbTRUE;
   TxMsg->ID = J1939_ADD_THIS_SRC_ADDR (J193973_PGN_65229_BASE_ID);
   TxMsg->Length = J193973_PGN_65229_LENGTH;
   TxMsg->Data[0] = 0x00; /* Frz Frm Length */
   TxMsg->Data[1] = 0x00; /* Troble code of 0x00000000 */
   TxMsg->Data[2] = 0x00;
   TxMsg->Data[3] = 0x00;
   TxMsg->Data[4] = 0x00;
   TxMsg->Data[5] = 0xFF;
   TxMsg->Data[6] = 0xFF;
   TxMsg->Data[7] = 0xFF;
}

/***************************************************************************/
/* FUNCTION: ServiceDm4TransportOut                                        */
/*  Returns : True if connection to be closed                              */
/***************************************************************************/
static can_boolean_t ServiceDm4TransportOut (TpOutStateType State,
                                             J1939_Transmit_Message_Info_T *TxMsg)
{
   uint8_t DataByteLocation, NumPacked;

   /* Check if in Data transport mode */
   if (State != TP_OUT_DATA_TRANSPORT)
   {
      /* No special action when connection is closed */
   }
   else
   {
      /* TxMsg[0] pre-packed with sequence number vi TP Management */
      /* A seq num of 1 indicates first data packet */
      /* 7 data bytes per packet */
      DataByteLocation = (TxMsg->Data[0] - 1) * 7;
      NumPacked = 1; /* Seq number already packed */

      while (NumPacked < 8)
      {
         if (DataByteLocation <= NumOfFreezeFrameBytes)
         {
            TxMsg->Data[NumPacked++] = J1939_DM4_Msg_Snapshot[DataByteLocation++];
         }
         else
         {
            TxMsg->Data[NumPacked++] = 0xFF;
         }
      }
   }

   /* This routine never requests the connection to be closed */
   return (CAN_cbFALSE);
}


/***************************************************************************/
/* FUNCTION: Service_PGN_65229                                             */
/* Description: Previously active DTCs  : DM4                              */
/* If more than 1 code then transport protocol is required                 */
/***************************************************************************/
static can_boolean_t Service_PGN_65229 (J1939_Transmit_Message_Info_T *TxMsg)
{
   can_boolean_t MsgToSend, ProcessingError;
   uint8_t *DM4_Msg;
   ProcessingError = CAN_cbTRUE; /* Assume some reason msg could not be sent */
   MsgToSend = CAN_cbFALSE; /* Assume no message to send */
   TxMsg->Callback_Time_W = J193973_PGN_65229_FREQ;
#if 0
   /* If previous DM2 still being transported then ignore this req */
   if (! J1939_CkPgnCurrentlyInTransportOut (J193973_PGN_65229))
   {
      DM4_Msg = GetJ1939_DM4_MsgPtr();
      NumOfFreezeFrameBytes = DM4_Msg[0];
      J1939_Message_SnapShot (DM4_Msg, J1939_DM4_Msg_Snapshot, NumOfFreezeFrameBytes+1);

      /* If one packet will do then send the packet */
      if (NumOfFreezeFrameBytes < 8)
      {
         BuildPgn65229NoDtcPacket (TxMsg);
         ProcessingError = CAN_cbFALSE;
         MsgToSend = CAN_cbTRUE;
      }
      else
      {
         /* When TP required respond back with using requester addr as dest */
         if (J1939_RequestTransportOutManagement (TxMsg->Requester,
                                                  NumOfFreezeFrameBytes, J193973_PGN_65229, ServiceDm4TransportOut))
         {
            ProcessingError = CAN_cbFALSE;
         }
      }
   }
#endif
   /* If DM2 transmission already in progress or */
   /* if Transport to destination already in use or if TP buffers full */
   /* then send Busy ACK (assumes this msg by request only) */
   if (ProcessingError)
   {
      J1939_SendUnmanagedAcknowledgement (BusyAck, J193973_PGN_65229);
   }

   return (MsgToSend);
}


/***************************************************************************/
/* FUNCTION: J1939_TxInit_PGN_65229                                        */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J193973_TxInit_PGN_65229 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = Service_PGN_65229;
   MsgCtrl->Time_To_Service        = 0x00;
   MsgCtrl->Tx_Timeout             = 0x00;
   MsgCtrl->Time_To_Next_Service_W = J193973_PGN_65229_FREQ;
   MsgCtrl->Tx_Timeout_Timer_W     = J1939_PGN_65229_TIMEOUT;
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Oct-16   cjqq             Add DM4                                    *
 ******************************************************************************/
