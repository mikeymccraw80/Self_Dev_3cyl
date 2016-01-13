/*****************************************************************************
 * Copyright 2014 Delphi Technologies, Inc., All Rights Reserved             *
 * AUTHORS: Xi Yanpeng                                                       *
 * Project: 10027185_HPDI                                                    *
 * File Name:  j1939_pgn_65249.c                                             *
 * File Description:                                                         *                                    *
 *****************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp.h"
#include "j1939_tp_out.h"
#include "j1939_73.h"
#include "j1939_app.h"

static void BuildPgn65249OnePacket (J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t Service_PGN_65249_TransportOut (TpOutStateType State,
                                             J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t Service_PGN_65249 (J1939_Transmit_Message_Info_T *TxMsg);

/************************************************************************/
/* Global Variables                                                     */
/************************************************************************/
static uint8_t J1939_PGN_65249_Msg_Snapshot[J1939_PGN_65249_BUFFER_SIZE];
static uint16_t NumOfBytes_PGN_65249;


/***************************************************************************/
/* FUNCTION: BuildPgn65249OnePacket                                        */
/***************************************************************************/
static void BuildPgn65249OnePacket (J1939_Transmit_Message_Info_T *TxMsg)
{
   uint8_t NumPacked=0;
   TxMsg->Extended_ID = CAN_cbTRUE;
   TxMsg->ID = J1939_ADD_THIS_SRC_ADDR (J193973_PGN_65249_BASE_ID);
   TxMsg->Length = J193973_PGN_65249_LENGTH;

   while (NumPacked < 8)
   {
      if (NumPacked >= NumOfBytes_PGN_65249)
      {
         TxMsg->Data[NumPacked] = 0xFF;
      }
      else
      {
         TxMsg->Data[NumPacked] = J1939_PGN_65249_Msg_Snapshot[NumPacked];
      }

      NumPacked++;
   }
}

/***************************************************************************/
/* FUNCTION: Service_PGN_65249_TransportOut                                */
/*  Returns : True if connection to be closed                              */
/***************************************************************************/
static can_boolean_t Service_PGN_65249_TransportOut (TpOutStateType State,
                                             J1939_Transmit_Message_Info_T *TxMsg)
{
   uint8_t DataByteLocation, DtcOffset, NumPacked;
   
      /* TxMsg[0] pre-packed with sequence number vi TP Management */
      /* A seq num of 1 indicates first data packet */
      /* 7 data bytes per packet */
      DataByteLocation = (TxMsg->Data[0] - 1) * 7;
      NumPacked = 1; /* Seq number already packed */
	  
      DtcOffset = DataByteLocation; 

      while (NumPacked < 8)
      {
         if (DtcOffset < NumOfBytes_PGN_65249)
         {
            TxMsg->Data[NumPacked++] = J1939_PGN_65249_Msg_Snapshot[DtcOffset++];
         }
         else
         {
            TxMsg->Data[NumPacked++] = 0xFF;
         }
      } 

   /* This routine never requests the connection to be closed */
   return (CAN_cbFALSE);
}

/***************************************************************************/
/* FUNCTION: Service_PGN_65249                                           */
/* If more than 1 code then transport protocol is required                 */
/***************************************************************************/
static can_boolean_t Service_PGN_65249 (J1939_Transmit_Message_Info_T *TxMsg)
{
   can_boolean_t DataToSendWithoutTransport;
   /*DataToSend = CAN_cbFALSE;*/
   DataToSendWithoutTransport = CAN_cbFALSE;
   TxMsg->Callback_Time_W = J193973_PGN_65249_FREQ;

   /* If previous PGN65249 still being transported then do not send another */
   if (J1939_CkPgnCurrentlyInTransportOut (J193973_PGN_65249))
   {
      /* If PGN 65249 transmission already in progress then send Busy ACK if this
       * message was requested */
      if (TxMsg->Requested)
      {
         J1939_SendUnmanagedAcknowledgement (BusyAck, J193973_PGN_65249);
      }
   }
   else
   {
       NumOfBytes_PGN_65249 = GetJ1939_PGN_65249_BYTE_NUMBER();

      J1939_Message_SnapShot (GetJ1939_PGN_65249_MsgPtr(), J1939_PGN_65249_Msg_Snapshot, NumOfBytes_PGN_65249);

      /* If one packet will do then send the packet */
      if (NumOfBytes_PGN_65249 <= 8)
      {
         DataToSendWithoutTransport = CAN_cbTRUE;
         BuildPgn65249OnePacket (TxMsg);
      }
      else
      {
         /* Else request support from transport management */
         /* When TP required respond back with using requester addr as dest */
         if (! TxMsg->Requested)
         {
            /* If self-triggered message then attempt to send until it is sent */
            if (! J1939_RequestTransportOutManagement (J1939_GLOBAL_DEST_ADDR,
                                                       NumOfBytes_PGN_65249, J193973_PGN_65249, Service_PGN_65249_TransportOut))
            {   //J1939_GLOBAL_DEST_ADDR
               /* Callback every loop until TP available */
               TxMsg->Callback_Time_W = CAN_FASTEST_PERIODIC_SERVICE;
            }
         }
         else
         {
            /* Respond with requester addr as desination */
            if (! J1939_RequestTransportOutManagement (TxMsg->Requester,
                                                       NumOfBytes_PGN_65249, J193973_PGN_65249, Service_PGN_65249_TransportOut))
            {
               /* If Transport to destination already in use or if TP buffers
                * full then send Busy ACK if this message was requested */
               J1939_SendUnmanagedAcknowledgement (BusyAck, J193973_PGN_65249);
            }
            else
            {
              /* do nothing */
            }
         }
      }
   }

   return (DataToSendWithoutTransport);
}

/***************************************************************************/
/* FUNCTION: J1939_TxInit_PGN_65249                                       */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J193973_TxInit_PGN_65249 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = Service_PGN_65249;
   MsgCtrl->Time_To_Service      = 0x00;
   MsgCtrl->Tx_Timeout           = 0x00;
   MsgCtrl->Time_To_Next_Service_W = J193973_PGN_65249_FREQ;
   MsgCtrl->Tx_Timeout_Timer_W    = J1939_PGN_65249_TIMEOUT;
}

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 ******************************************************************************/

