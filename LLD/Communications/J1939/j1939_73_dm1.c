/*****************************************************************************
 * Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
 * AUTHORS: Sandeep, Prakash, Mehak                                          *
 * Project: CNG E483                                                         *
 * File Name:  j1939_73_dm1.c                                                *
 * File Description:                                                         *
 * Diagnostic Message 1 Implementation                                       *
 *****************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"
#include "j1939_app.h"


#define NUM_ALL_CLEAR_TO_SEND (3)

#define J1939_DM1_TIMEOUT ( 1000/(J193973_PGN_65226_FREQ*J1939_BASE_LOOP))

static void BuildPgn65226OnePacket (J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t ServiceDm1TransportOut (TpOutStateType State,
                                             J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t Service_PGN_65226 (J1939_Transmit_Message_Info_T *TxMsg);

/************************************************************************/
/* Global Variables                                                     */
/************************************************************************/
static uint8_t J1939_DM1_Msg_Snapshot[J1939_DM1_BUFFER_SIZE];
static uint16_t NumOfDTCs;
static uint16_t NumOfDTCBytes;

/***************************************************************************/
/* FUNCTION: BuildPgn65226OnePacket                                        */
/***************************************************************************/
static void BuildPgn65226OnePacket (J1939_Transmit_Message_Info_T *TxMsg)
{
   uint8_t NumPacked;
   TxMsg->Extended_ID = CAN_cbTRUE;
   TxMsg->ID = J1939_ADD_THIS_SRC_ADDR (J193973_PGN_65226_BASE_ID);
   TxMsg->Length = J193973_PGN_65226_LENGTH;
   TxMsg->Data[0] = J1939_DM1_Msg_Snapshot[0];
   TxMsg->Data[1] = J1939_DM1_Msg_Snapshot[1];
   NumPacked = 2;  /* 2 bytes for lamps */

   if (NumOfDTCs == 0)
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
      if (NumPacked >= NumOfDTCBytes)
      {
         TxMsg->Data[NumPacked] = 0xFF;
      }
      else
      {
         TxMsg->Data[NumPacked] = J1939_DM1_Msg_Snapshot[NumPacked];
      }

      NumPacked++;
   }
}

/***************************************************************************/
/* FUNCTION: ServiceDm1TransportOut                                        */
/*  Returns : True if connection to be closed                              */
/***************************************************************************/
static can_boolean_t ServiceDm1TransportOut (TpOutStateType State,
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
         TxMsg->Data[1] = J1939_DM1_Msg_Snapshot[0];
         TxMsg->Data[2] = J1939_DM1_Msg_Snapshot[1];
         NumPacked += 2; /* 2 bytes for lamp status */
         DtcOffset = 2;  /* Then first byte of DTCs */
      }
      else
      {
         DtcOffset = DataByteLocation; /* subtract lamp status bytes */
      }

      while (NumPacked < 8)
      {
         if (DtcOffset < NumOfDTCBytes)
         {
            TxMsg->Data[NumPacked++] = J1939_DM1_Msg_Snapshot[DtcOffset++];
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
/* FUNCTION: Service_PGN_65226                                             */
/* Description: Active Diagnostic Trouble Dtcs : DM1                       */
/* If more than 1 code then transport protocol is required                 */
/***************************************************************************/
static can_boolean_t Service_PGN_65226 (J1939_Transmit_Message_Info_T *TxMsg)
{
   //static uint8_t NumAllClearMessagesPending_B;
   can_boolean_t DataToSendWithoutTransport;
   //DataToSend = CAN_cbFALSE;
   DataToSendWithoutTransport = CAN_cbFALSE;
   TxMsg->Callback_Time_W = J193973_PGN_65226_FREQ;
   /* If previous DM1 still being transported then do not send another */
   if (J1939_CkPgnCurrentlyInTransportOut (J193973_PGN_65226))
   {
      /* If DM1 transmission already in progress then send Busy ACK if this
       * message was requested */
      if (TxMsg->Requested)
      {
         J1939_SendUnmanagedAcknowledgement (BusyAck, J193973_PGN_65226);
      }
   }
   else
   {
      NumOfDTCs = GetJ1939_DM1_ActiveDTC_NUMBER();
      NumOfDTCBytes = NumOfDTCs * 4 + 2;
      J1939_Message_SnapShot (GetJ1939_DM1_MsgPtr(), J1939_DM1_Msg_Snapshot, NumOfDTCBytes);

      /* If one packet will do then send the packet */
      if (NumOfDTCs <= 1)
      {
         DataToSendWithoutTransport = CAN_cbTRUE;
         BuildPgn65226OnePacket (TxMsg);
      }
      else
      {
         /* Else request support from transport management */
         /* When TP required respond back with using requester addr as dest */
         if (! TxMsg->Requested)
         {
            /* If self-triggered message then attempt to send until it is sent */
            if (! J1939_RequestTransportOutManagement (J1939_GLOBAL_DEST_ADDR,
                                                       NumOfDTCBytes, J193973_PGN_65226, ServiceDm1TransportOut))
            {
               /* Callback every loop until TP available */
               TxMsg->Callback_Time_W = CAN_FASTEST_PERIODIC_SERVICE;
            }
         }
         else
         {
            /* Respond with requester addr as desination */
            if (! J1939_RequestTransportOutManagement (TxMsg->Requester,
                                                       NumOfDTCBytes, J193973_PGN_65226, ServiceDm1TransportOut))
            {
               /* If Transport to destination already in use or if TP buffers
                * full then send Busy ACK if this message was requested */
               J1939_SendUnmanagedAcknowledgement (BusyAck, J193973_PGN_65226);
            }
            else
            {
               //do nothing
            }
         }
      }
   }
   return (DataToSendWithoutTransport);
}

/***************************************************************************/
/* FUNCTION: J1939_TxInit_PGN_65226                                        */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J193973_TxInit_PGN_65226 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = Service_PGN_65226;
   MsgCtrl->Time_To_Service       = 0x00;
   MsgCtrl->Tx_Timeout           = 0x00;
   MsgCtrl->Time_To_Next_Service_W = J193973_PGN_65226_FREQ;
   MsgCtrl->Tx_Timeout_Timer_W    = J1939_PGN_65226_TIMEOUT;
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   12-Sep-6   cjqq             Add DM1                                     *
 ******************************************************************************/
