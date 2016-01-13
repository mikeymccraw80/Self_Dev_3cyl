/*****************************************************************************
 * Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
 * AUTHORS: Sandeep, Prakash, Mehak                                          *
 * Project: CNG E483                                                         *
 * File Name:  j1939_73_dm12.c                                               *
 * File Description:                                                         *
 * Diagnostic Message 12 Implementation                                      *
 *****************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"
#include "j1939_app.h"

static void BuildPgn65236OnePacket (J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t ServiceDm12TransportOut (TpOutStateType State,
                                              J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t Service_PGN_65236 (J1939_Transmit_Message_Info_T *TxMsg);

/************************************************************************/
/* Global Variables                                                     */
/************************************************************************/
static uint8_t J1939_DM12_Msg_Snapshot[J1939_DM12_BUFFER_SIZE];
static uint16_t NumOfEmissionActiveDTCs;
static uint16_t NumOfEmissionActiveDTCBytes;

/***************************************************************************/
/* FUNCTION: BuildPgn65226OnePacket                                        */
/***************************************************************************/
static void BuildPgn65236OnePacket (J1939_Transmit_Message_Info_T *TxMsg)
{
   uint8_t NumPacked;
   TxMsg->Extended_ID = CAN_cbTRUE;
   TxMsg->ID = J1939_ADD_THIS_SRC_ADDR (J193973_PGN_65236_BASE_ID);
   TxMsg->Length = J193973_PGN_65236_LENGTH;
   TxMsg->Data[0] = J1939_DM12_Msg_Snapshot[0];
   TxMsg->Data[1] = J1939_DM12_Msg_Snapshot[1];
   NumPacked = 2;  /* 2 bytes for lamps */

   if (NumOfEmissionActiveDTCs == 0)
   {
      /* If no codes set then first force first DTC in message to 0x0000 */
      /* Per latest J1939/73 requirements */
      TxMsg->Data[NumPacked++] = 0x00;
      TxMsg->Data[NumPacked++] = 0x00;
      TxMsg->Data[NumPacked++] = 0x00;
      TxMsg->Data[NumPacked++] = 0x00;
   }

   while (NumPacked < 8)
   {
      if (NumPacked >= NumOfEmissionActiveDTCBytes)
      {
         TxMsg->Data[NumPacked] = 0xFF;
      }
      else
      {
         TxMsg->Data[NumPacked] = J1939_DM12_Msg_Snapshot[NumPacked];
      }

      NumPacked++;
   }
}


/***************************************************************************/
/* FUNCTION: ServiceDm1TransportOut                                        */
/*  Returns : True if connection to be closed                              */
/***************************************************************************/
static can_boolean_t ServiceDm12TransportOut (TpOutStateType State,
                                              J1939_Transmit_Message_Info_T *TxMsg)
{
   uint8_t DataByteLocation, DtcOffset, NumPacked;

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

      if (DataByteLocation == 0)
      {
         /* First 2 data bytes are Lamp status */
         TxMsg->Data[1] = J1939_DM12_Msg_Snapshot[0];
         TxMsg->Data[2] = J1939_DM12_Msg_Snapshot[1];
         NumPacked += 2; /* 2 bytes for lamp status */
         DtcOffset = 2;
      }
      else
      {
         DtcOffset = DataByteLocation; /* subtract lamp status bytes */
      }

      while (NumPacked < 8)
      {
         if (DtcOffset < NumOfEmissionActiveDTCBytes)
         {
            TxMsg->Data[NumPacked++] = J1939_DM12_Msg_Snapshot[DtcOffset++];
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
/* FUNCTION: Service_PGN_65227                                             */
/* Description: Previously active DTCs  : DM2                              */
/* If more than 1 code then transport protocol is required                 */
/***************************************************************************/
static can_boolean_t Service_PGN_65236 (J1939_Transmit_Message_Info_T *TxMsg)
{
   can_boolean_t MsgToSend, ProcessingError;
   ProcessingError = CAN_cbTRUE; /* Assume some reason msg could not be sent */
   MsgToSend = CAN_cbFALSE; /* Assume no message to send */
   TxMsg->Callback_Time_W = J193973_PGN_65236_FREQ;
   /* If previous DM2 still being transported then ignore this req */
   if (! J1939_CkPgnCurrentlyInTransportOut (J193973_PGN_65236))
   {
      NumOfEmissionActiveDTCs = GetJ1939_DM12_EmissionsRelated_ActiveDTCs_Number();
      /* NumOfEmissionActiveDTCBytes = 2 for lamp status + 4 for each code */
      NumOfEmissionActiveDTCBytes = (uint16_t) (2 + (NumOfEmissionActiveDTCs * 4));
      J1939_Message_SnapShot (GetJ1939_DM12_MsgPtr(), J1939_DM12_Msg_Snapshot, NumOfEmissionActiveDTCBytes);

      /* If one packet will do then send the packet */
      if (NumOfEmissionActiveDTCs <= 1)
      {
         BuildPgn65236OnePacket (TxMsg);
         ProcessingError = CAN_cbFALSE;
         MsgToSend = CAN_cbTRUE;
      }
      else
      {
         /* When TP required respond back with using requester addr as dest */
         if (J1939_RequestTransportOutManagement (TxMsg->Requester,
                                                  NumOfEmissionActiveDTCBytes, J193973_PGN_65236, ServiceDm12TransportOut))
         {
            ProcessingError = CAN_cbFALSE;
         }
      }
   }
   /* If DM2 transmission already in progress or */
   /* if Transport to destination already in use or if TP buffers full */
   /* then send Busy ACK (assumes this msg by request only) */
   if (ProcessingError)
   {
      J1939_SendUnmanagedAcknowledgement (BusyAck, J193973_PGN_65236);
   }

   return (MsgToSend);
}


/***************************************************************************/
/* FUNCTION: J1939_TxInit_PGN_65226                                        */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J193973_TxInit_PGN_65236 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = Service_PGN_65236;
   MsgCtrl->Time_To_Service        = 0x00;
   MsgCtrl->Tx_Timeout             = 0x00;
   MsgCtrl->Time_To_Next_Service_W = J193973_PGN_65236_FREQ;
   MsgCtrl->Tx_Timeout_Timer_W     = J1939_PGN_65236_TIMEOUT;
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Oct-16   cjqq             Add DM2                                    *
 ******************************************************************************/
