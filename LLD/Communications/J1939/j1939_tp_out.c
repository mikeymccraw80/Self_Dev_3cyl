/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: CNG E483                                                         *
* File Name:  j1939_tp_out.c                                                *
* File Description:                                                         *
* J1939 RX transport protocol manager                                       *
*****************************************************************************/
#include "j1939_pgn_config.h"
#include "j1939_tp_out.h"/* For TpOutStateType*/

#define J1939_PUT_SRC_ADDR_TP_OUT(id,addr)  (((uint32_t)(id) & 0xFFFFFF00) | (uint32_t)(addr))
#define J1939_PUT_DEST_ADDR_TP_OUT(id,addr)  (((uint32_t)(id) & 0xFFFF00FF) | (uint32_t)((addr) << 8))
#define J1939_ADD_THIS_SRC_ADDR_TP_OUT(id)  (((uint32_t)(id) & 0xFFFFFF00) | (uint32_t)(KfHWIO_J193973_SA))

static can_boolean_t CkActiveTpOutConnectionToDevice (uint8_t Addr_B,
                                                      uint8_t *Index);
static can_boolean_t LoadTransportOut (uint8_t Addr_B, uint32_t NumDataBytes_W,
                                       uint32_t Pgn_L,
                                       can_boolean_t (*ServiceRoutine) (TpOutStateType State,
                                                                        J1939_Transmit_Message_Info_T *TxMsgPtr));
static can_boolean_t InitiateTpOutConnection (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr);
static can_boolean_t WaitingForTpOutAcceptance (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr);
static can_boolean_t TransmitTpOutData (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr);
static void ExternalAbortTpOutConnection (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr);
static can_boolean_t WaitingForTpOutClosure (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr);
static can_boolean_t TpOutComplete (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr);
static can_boolean_t ServiceTransportOutMessage (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr);
static can_boolean_t ServiceTransportOut_0 (J1939_Transmit_Message_Info_T *TxMsgPtr);

static can_boolean_t ServiceTransportOut_0 (J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t ServiceTransportOut_1 (J1939_Transmit_Message_Info_T *TxMsg);
static can_boolean_t ServiceTransportOut_2 (J1939_Transmit_Message_Info_T *TxMsg);

TpOutType TpOut[C_MaxTpOutConnections];

/***************************************************************************/
/* FUNCTION: CkActiveTpOutConnectionToDevice                               */
/***************************************************************************/
static can_boolean_t CkActiveTpOutConnectionToDevice (uint8_t Addr_B,
                                                      uint8_t *Index)
{
   uint8_t i;

   for (i = 0; ( (i < C_MaxTpOutConnections) &&
                 ( (TpOut[i].Addr_B != Addr_B) || (TpOut[i].State == TP_OUT_INACTIVE)));
        i++)
   {
      ;
   }

   *Index = i;
   return ( (i < C_MaxTpOutConnections) ? CAN_cbTRUE : CAN_cbFALSE);
}



/***************************************************************************/
/* FUNCTION: LoadTransportOut                                              */
/*  Returns TRUE if Transport Connection available and loaded              */
/***************************************************************************/
static can_boolean_t LoadTransportOut (uint8_t Addr_B, uint32_t NumDataBytes_W,
                                       uint32_t Pgn_L,
                                       can_boolean_t (*ServiceRoutine) (TpOutStateType State,
                                                                        J1939_Transmit_Message_Info_T *TxMsgPtr))
{
   uint8_t i;

   /* Find Inactive Channel */
   for (i = 0; ( (TpOut[i].State != TP_OUT_INACTIVE)
                 && (++i < C_MaxTpOutConnections));)
   {
      ;
   }

   if (i < C_MaxTpOutConnections)
   {
      TpOut[i].State = TP_OUT_REQUEST_TO_SEND;  /* Locks this transport */
      TpOut[i].NextSequenceNum_B = 0x01;
      TpOut[i].Addr_B = Addr_B;
      TpOut[i].Pgn_L = Pgn_L;
      TpOut[i].NumDataBytes_W = NumDataBytes_W;
      TpOut[i].NumDataPackets_B = ( (NumDataBytes_W + 6) / 7);
      TpOut[i].AllPacketsSent = CAN_cbFALSE;
      TpOut[i].ServiceRoutine = ServiceRoutine;
      /* Trigger can bus manager that this transport connection has a msg */
      J1939_Trigger_Transmit_Message_Service (i);
   }

   return ( (i < C_MaxTpOutConnections) ? CAN_cbTRUE : CAN_cbFALSE);
}


/***************************************************************************/
/* FUNCTION: InitiateTpOutConnection                                       */
/***************************************************************************/
static can_boolean_t InitiateTpOutConnection (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   can_boolean_t GlobalDest;
   PreparePgn60416Msg (TxMsgPtr, TpOut[Index].Addr_B, TpOut[Index].Pgn_L);
   GlobalDest = (TpOut[Index].Addr_B == J1939_GLOBAL_DEST_ADDR) ?
                CAN_cbTRUE : CAN_cbFALSE;
   /* Assign Byte 1 - Control Byte */
   TxMsgPtr->Data[0] = (uint8_t) ( (GlobalDest) ? J1939_TP_CM_BAM : J1939_TP_CM_RTS);
   /* Assign Byte 2 - Total Number of Bytes MSB */
   /* Assign Byte 3 - Total Number of Bytes LSB */
   TxMsgPtr->Data[1] = (uint8_t) (TpOut[Index].NumDataBytes_W & 0x00FF);
   TxMsgPtr->Data[2] = (uint8_t) ((TpOut[Index].NumDataBytes_W & 0xFF00) >> 8);
   /* Assign Byte 4 - Total Number of packets */
   /* 7 data bytes per packet. Round up packets via add 6 */
   TxMsgPtr->Data[3] = TpOut[Index].NumDataPackets_B;
   /* Assign Byte 5 - Reserved */
   TxMsgPtr->Data[4] = J1939_DATA_NOT_AVAILABLE;
   TpOut[Index].NextSequenceNum_B = 0x01;

   if (GlobalDest)
   {
      TpOut[Index].ClearToSend_B = TpOut[Index].NumDataPackets_B;
      TpOut[Index].State = TP_OUT_DATA_TRANSPORT;
      TxMsgPtr->Callback_Time_W = J1939_TP_BROADCAST_DELAY_TIME;
   }
   else
   {
      TpOut[Index].ClearToSend_B = 0x00;
      TpOut[Index].State = TP_OUT_WAIT_FOR_CLEAR_TO_SEND;
      TxMsgPtr->Callback_Time_W = J1939_TP_MISSING_CTS_ACK_TIMEOUT;
   }

   return (CAN_cbTRUE);
}


/***************************************************************************/
/* FUNCTION: WaitingForTpOutAcceptance                                     */
/* If we got to this routine then we must have timed out waiting for       */
/* a Clear to Send;                                                        */
/***************************************************************************/
static can_boolean_t WaitingForTpOutAcceptance (uint8_t Index, J1939_Transmit_Message_Info_T
                                                *TxMsgPtr)
{
   TpOut[Index].State = TP_OUT_INACTIVE;
   (void) (*TpOut[Index].ServiceRoutine) (TP_OUT_INTERNAL_ABORT, TxMsgPtr);
   BuildTpAbortMsg (TxMsgPtr, TpOut[Index].Addr_B, TpOut[Index].Pgn_L,
                    J1939_TP_CM_ABORT_BECAUSE_TIMEOUT);
   TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   return (CAN_cbTRUE);
}


/***************************************************************************/
/* FUNCTION: TransmitTpOutData                                             */
/***************************************************************************/
static can_boolean_t TransmitTpOutData (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   can_boolean_t MsgToSend, CloseConnection, GlobalDest;
   uint32_t Id;
   //uint8_t  NumDataPackets;
   //uint8_t  Reserved_B;
   //uint8_t  LatestPackageBytes;
   MsgToSend = CAN_cbFALSE;
   GlobalDest = (TpOut[Index].Addr_B == J1939_GLOBAL_DEST_ADDR) ?
                CAN_cbTRUE : CAN_cbFALSE;

   /* Check if clear to send more data */
   /* A request to suspend transmission (ClearToSend_B = 0) may have occurred */
   /* Illegal requests also trapped here */
   if ( (TpOut[Index].ClearToSend_B == 0x00) ||
        ( (uint16_t) TpOut[Index].NextSequenceNum_B +
          (uint16_t) TpOut[Index].ClearToSend_B) >
        ( (uint16_t) TpOut[Index].NumDataPackets_B + 1))
   {
      TxMsgPtr->Callback_Time_W = J1939_TP_MISSING_CTS_ACK_TIMEOUT;
      TpOut[Index].State = TP_OUT_WAIT_FOR_CLEAR_TO_SEND;
   }
   else
   {
      //TxMsgPtr->ExtendedId = CAN_cbTRUE;
      //TxMsgPtr->Id = 0x18EBFF2Aul;
      Id = J1939_PUT_DEST_ADDR (J1939_PGN_60160_BASE_ID, TpOut[Index].Addr_B);
      TxMsgPtr->ID = J1939_ADD_THIS_SRC_ADDR (Id);
      TxMsgPtr->Length = J1939_PGN_60160_LENGTH;
      /* Assign Byte 1 - Sequence Number */
      TxMsgPtr->Data[0] = TpOut[Index].NextSequenceNum_B;
      //NumDataPackets = TpOut[Index].NumDataPackets_B;
      //Reserved_B = (uint8_t)( (uint16_t)(NumDataPackets *7) - TpOut[Index].NumDataBytes_W);
      //LatestPackageBytes = 7 - Reserved_B;
      /* Bytes 2 - 8 populated by requester of this transport management */
      /* This service handler will look at sequence number stored in [0] */
      /* This service handler may request the connection to be closed */
      CloseConnection =
         (*TpOut[Index].ServiceRoutine) (TP_OUT_DATA_TRANSPORT, TxMsgPtr);

      /* Ck if srv function for some reason decided to close the connection */
      if (CloseConnection)
      {
         MsgToSend = CAN_cbTRUE;
         TpOut[Index].State = TP_OUT_INACTIVE;
         TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
         BuildTpAbortMsg (TxMsgPtr, TpOut[Index].Addr_B, TpOut[Index].Pgn_L,
                          J1939_TP_CM_ABORT_BECAUSE_RESOURCE_ISSUE);
      }
      else
      {
         MsgToSend = CAN_cbTRUE;
         TpOut[Index].NextSequenceNum_B++;
         TpOut[Index].ClearToSend_B--;

         /* Latch a flag when all packets have been sent aleast once */
         /* Assume TP.CTS will request packets in numeric order */
         if (TpOut[Index].NextSequenceNum_B > TpOut[Index].NumDataPackets_B)
         {
            TpOut[Index].AllPacketsSent = CAN_cbTRUE;
         }

         /* Determine CallBackTime and possible State change */
         if (TpOut[Index].ClearToSend_B > 0x00)
         {
            /* More packets to send from last TP.CTS */
            if (GlobalDest)
            {
               TxMsgPtr->Callback_Time_W = J1939_TP_BROADCAST_DELAY_TIME;
            }
            else
            {
               TxMsgPtr->Callback_Time_W = J1939_TP_DEST_SPECIFIC_DELAY_TIME;
            }
         }
         else if (! TpOut[Index].AllPacketsSent)
         {
            /* Expect another TP.CTS to obtain remaining data */
            TpOut[Index].State = TP_OUT_WAIT_FOR_CLEAR_TO_SEND;
            TxMsgPtr->Callback_Time_W = J1939_TP_MISSING_CTS_ACK_TIMEOUT;
         }
         else
         {
            /* All packets have been sent at least once */
            if (GlobalDest)
            {
               /* Global dest; No EndMsgACK */
               TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
               TpOut[Index].State = TP_OUT_INACTIVE;
            }
            else
            {
               /* Wait for EndMsgAck, will accept another TP.CTS to repeat packets */
               TxMsgPtr->Callback_Time_W = J1939_TP_MISSING_CTS_ACK_TIMEOUT;
               TpOut[Index].State = TP_OUT_WAIT_FOR_END_ACK;
            }
         }
      }
   }

   return (MsgToSend);
}


/***************************************************************************/
/* FUNCTION: ExternalAbortTpOutConnection                                  */
/* If we got to this routine then the dest device must have sent a         */
/* request to abort message                                                */
/***************************************************************************/
static void ExternalAbortTpOutConnection (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   (void) (*TpOut[Index].ServiceRoutine) (TP_OUT_EXTERNAL_ABORT, TxMsgPtr);
   TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   TpOut[Index].State = TP_OUT_INACTIVE;
}


/***************************************************************************/
/* FUNCTION: WaitingForTpOutClosure                                        */
/* Must have timed out waiting on an end of message ACK                    */
/***************************************************************************/
static can_boolean_t WaitingForTpOutClosure (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   TpOut[Index].State = TP_OUT_INACTIVE;
   (void) (*TpOut[Index].ServiceRoutine) (TP_OUT_INTERNAL_ABORT, TxMsgPtr);
   BuildTpAbortMsg (TxMsgPtr, TpOut[Index].Addr_B, TpOut[Index].Pgn_L,
                    J1939_TP_CM_ABORT_BECAUSE_TIMEOUT);
   TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   return (CAN_cbTRUE);
}


/***************************************************************************/
/* FUNCTION: TpOutComplete                                                 */
/* Must have received and EndAck from receiver                             */
/***************************************************************************/
static can_boolean_t TpOutComplete (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   (void) (*TpOut[Index].ServiceRoutine) (TP_OUT_END_ACK, TxMsgPtr);
   TpOut[Index].State = TP_OUT_INACTIVE;
   TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   return (CAN_cbFALSE);
}

/***************************************************************************/
/* FUNCTION: ServiceTransportOutMessage                                    */
/***************************************************************************/
static can_boolean_t ServiceTransportOutMessage (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   can_boolean_t MsgToSend;
   MsgToSend = CAN_cbFALSE;

   switch (TpOut[Index].State)
   {
      case TP_OUT_REQUEST_TO_SEND :
         MsgToSend = InitiateTpOutConnection (Index, TxMsgPtr);
         break;

      case TP_OUT_WAIT_FOR_CLEAR_TO_SEND :
         MsgToSend = WaitingForTpOutAcceptance (Index, TxMsgPtr);
         break;

      case TP_OUT_DATA_TRANSPORT :
         MsgToSend = TransmitTpOutData (Index, TxMsgPtr);
         break;

      case TP_OUT_WAIT_FOR_END_ACK :
         MsgToSend = WaitingForTpOutClosure (Index, TxMsgPtr);
         break;

      case TP_OUT_END_ACK :
         MsgToSend = TpOutComplete (Index, TxMsgPtr);
         break;

      case TP_OUT_EXTERNAL_ABORT :
         ExternalAbortTpOutConnection (Index, TxMsgPtr);
         break;

      case TP_OUT_INACTIVE :
         break;

      default :
         break;
   }

   return (MsgToSend);
}


/***************************************************************************/
/* FUNCTION: J1939_CkPgnCurrentlyInTransportOut                            */
/***************************************************************************/
can_boolean_t J1939_CkPgnCurrentlyInTransportOut (uint32_t Pgn_L)
{
   uint8_t i;

   for (i = 0; ( (i < C_MaxTpOutConnections) &&
                 ( (TpOut[i].Pgn_L != Pgn_L) || (TpOut[i].State == TP_OUT_INACTIVE)));
        i++)
   {
      ;
   }

   return ( (i < C_MaxTpOutConnections) ? CAN_cbTRUE : CAN_cbFALSE);
}



/***************************************************************************/
/* FUNCTION: ServiceTransportOut_X                                         */
/***************************************************************************/
static can_boolean_t ServiceTransportOut_0 (J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   return (ServiceTransportOutMessage (0, TxMsgPtr));
}
static can_boolean_t ServiceTransportOut_1 (J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   return (ServiceTransportOutMessage (1, TxMsgPtr));
}
static can_boolean_t ServiceTransportOut_2 (J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   return (ServiceTransportOutMessage (2, TxMsgPtr));
}


/***************************************************************************/
/* FUNCTION: J1939_TxInit_Tranportout_X                                    */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J1939_TxInit_TransportOut_0 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = ServiceTransportOut_0;
   MsgCtrl->Time_To_Service = 0x00;
   MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE; //Non periodic message
   MsgCtrl->Tx_Timeout = 0x00;
   MsgCtrl->Tx_Timeout_Timer_W = 0x00;
   TpOut[0].State = TP_OUT_INACTIVE; /* Cheap Insurance */
   //TpOut[0].State = TP_OUT_REQUEST_TO_SEND;
   //TpOut[0].Addr_B = J1939_GLOBAL_DEST_ADDR;
   //TpOut[0].Pgn_L = 0x00FECA;   /* PGN65226*/
   //TpOut[0].NumDataPackets_B = 0x03;
}

void J1939_TxInit_TransportOut_1 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = ServiceTransportOut_1;
   MsgCtrl->Time_To_Service = 0x00;
   MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE; //Non periodic message
   MsgCtrl->Tx_Timeout = 0x00;
   MsgCtrl->Tx_Timeout_Timer_W = 0x00;
   TpOut[1].State = TP_OUT_INACTIVE; /* Cheap Insurance */
}

void J1939_TxInit_TransportOut_2 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = ServiceTransportOut_2;
   MsgCtrl->Time_To_Service = 0x00;
   MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE; //Non periodic message
   MsgCtrl->Tx_Timeout = 0x00;
   MsgCtrl->Tx_Timeout_Timer_W = 0x00;
   TpOut[2].State = TP_OUT_INACTIVE; /* Cheap Insurance */
}


/***************************************************************************/
/* FUNCTION: ParseTransportOut_CTS                                         */
/***************************************************************************/
void ParseTransportOut_CTS (J1939_Receive_Message_Info_T *RxMsg)
{
   uint8_t SrcAddr_B, ReqNextSeq_B, ReqNumPackets_B;
   uint8_t Index;
   uint32_t Pgn_L;
   TpParseSrcAndPgn (RxMsg, &SrcAddr_B, &Pgn_L);
   ReqNumPackets_B = RxMsg->Data[1];
   ReqNextSeq_B = RxMsg->Data[2];

   /* Is there currently an active connection to this device, does the */
   /* PGN match, and is it in the correct state */
   /* Is the Seq and num to send reqest valid */
   if ( (CkActiveTpOutConnectionToDevice (SrcAddr_B, &Index))
        && (TpOut[Index].Pgn_L == Pgn_L)
        && ( (TpOut[Index].State == TP_OUT_WAIT_FOR_CLEAR_TO_SEND)
             || (TpOut[Index].State == TP_OUT_WAIT_FOR_END_ACK))
        && (ReqNextSeq_B >= 1)
        && ( ( (uint16_t) ReqNextSeq_B + (uint16_t) ReqNumPackets_B) <=
             ( (uint16_t) TpOut[Index].NumDataPackets_B + 1)))
   {
      TpOut[Index].ClearToSend_B = ReqNumPackets_B;
      TpOut[Index].NextSequenceNum_B = ReqNextSeq_B;
      TpOut[Index].State = TP_OUT_DATA_TRANSPORT;
      /* Trigger can bus manager that this transport connection needs service */
      J1939_Trigger_Transmit_Message_Service (Index);
   }
}


/***************************************************************************/
/* FUNCTION: ParseTransportOut_Abort                                       */
/***************************************************************************/
void ParseTransportOut_Abort (J1939_Receive_Message_Info_T *RxMsg)
{
   uint8_t SrcAddr_B;
   uint8_t Index;
   uint32_t Pgn_L;
   TpParseSrcAndPgn (RxMsg, &SrcAddr_B, &Pgn_L);

   /* Is there currently an active connection to this device, does the */
   /* PGN match, and is it in the correct state */
   if ( (CkActiveTpOutConnectionToDevice (SrcAddr_B, &Index)) &&
        (TpOut[Index].Pgn_L == Pgn_L))
   {
      TpOut[Index].State = TP_OUT_EXTERNAL_ABORT;
      /* Trigger can bus manager that this transport connection needs service */
      J1939_Trigger_Transmit_Message_Service (Index);
   }
}


/***************************************************************************/
/* FUNCTION: ParseTransportOut_EndACK                                      */
/***************************************************************************/
void ParseTransportOut_EndAck (J1939_Receive_Message_Info_T *RxMsg)
{
   uint8_t SrcAddr_B;
   uint8_t Index;
   uint32_t Pgn_L;
   TpParseSrcAndPgn (RxMsg, &SrcAddr_B, &Pgn_L);

   /* Is there currently an active connection to this device, does the */
   /* PGN match, and is it in the correct state */
   if ( (CkActiveTpOutConnectionToDevice (SrcAddr_B, &Index)) &&
        (TpOut[Index].Pgn_L == Pgn_L) &&
        (TpOut[Index].State == TP_OUT_WAIT_FOR_END_ACK))
   {
      TpOut[Index].State = TP_OUT_END_ACK;
      /* Trigger can bus manager that this transport connection needs service */
      J1939_Trigger_Transmit_Message_Service (Index);
   }
}

/***************************************************************************/
/* FUNCTION: J1939_RequestTransportOutManagement                           */
/*   Returns TRUE if RequestAccepted                                       */
/***************************************************************************/
can_boolean_t J1939_RequestTransportOutManagement (uint8_t Addr_B,
                                                   uint16_t NumDataBytes_W, uint32_t Pgn_L,
                                                   can_boolean_t (*ServiceRoutine) (TpOutStateType State, J1939_Transmit_Message_Info_T *TxMsgPtr))
{
   can_boolean_t Accepted;
   uint8_t Index;
   Accepted = CAN_cbFALSE;   /* Assume error */

   /* Check if transport for given destination already active */
   if (! CkActiveTpOutConnectionToDevice (Addr_B, &Index))
   {
      /* Request new transport to be managed -- if room in manager */
      if (LoadTransportOut (Addr_B, NumDataBytes_W, Pgn_L, ServiceRoutine))
      {
         Accepted = CAN_cbTRUE;
      }
   }

   return (Accepted);
}


/*
*- j1939_tp_out.TpOut[0].State {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[0]State";
*-   variable_location.symbol = j1939_tp_out.TpOut[0].State;
*-   description              = "J1939 Transport Out Channel 0 State";
*-   }

*- j1939_tp_out.TpOut[0].Addr_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[0]Addr_B";
*-   variable_location.symbol = j1939_tp_out.TpOut[0].Addr_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport Out Channel 0 address of destination for the data being transfered from this device";
*-   }

*- j1939_tp_out.TpOut[0].Pgn_L {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[0]Pgn_L";
*-   variable_location.symbol = j1939_tp_out.TpOut[0].Pgn_L;
*-   ds_precision             = ds_precision_UINT32;
*-   ds_scaling_mode          = ds_scaling_mode_UINT32;
*-   ds_const_a               = ds_const_a_UINT32;
*-   ds_const_b               = ds_const_b_UINT32;
*-   ds_scaling_unit          = ds_scaling_unit_UINT32;
*-   description              = "J1939 Transport Out Channel 0 PGN of data packet to be sent from this device";
*-   }

*- j1939_tp_out.TpOut[0].NextSequenceNum_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[0]NextSequenceNum_B";
*-   variable_location.symbol = j1939_tp_out.TpOut[0].NextSequenceNum_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport Out Channel 0 next data packet to be sent";
*-   }
*****************************************************************************

*- j1939_tp_out.TpOut[1].State {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[1]State";
*-   variable_location.symbol = j1939_tp_out.TpOut[1].State;
*-   description              = "J1939 Transport Out Channel 1 State";
*-   }

*- j1939_tp_out.TpOut[1].Addr_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[1]Addr_B";
*-   variable_location.symbol = j1939_tp_out.TpOut[1].Addr_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport Out Channel 1 address of destination for the data being transfered from this device";
*-   }

*- j1939_tp_out.TpOut[1].Pgn_L {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[1]Pgn_L";
*-   variable_location.symbol = j1939_tp_out.TpOut[1].Pgn_L;
*-   ds_precision             = ds_precision_UINT32;
*-   ds_scaling_mode          = ds_scaling_mode_UINT32;
*-   ds_const_a               = ds_const_a_UINT32;
*-   ds_const_b               = ds_const_b_UINT32;
*-   ds_scaling_unit          = ds_scaling_unit_UINT32;
*-   description              = "J1939 Transport Out Channel 1 PGN of data packet to be sent from this device";
*-   }

*- j1939_tp_out.TpOut[1].NextSequenceNum_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[1]NextSequenceNum_B";
*-   variable_location.symbol = j1939_tp_out.TpOut[1].NextSequenceNum_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport Out Channel 1 next data packet to be sent";
*-   }
*****************************************************************************

*- j1939_tp_out.TpOut[2].State {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[2]State";
*-   variable_location.symbol = j1939_tp_out.TpOut[2].State;
*-   description              = "J1939 Transport Out Channel 2 State";
*-   }

*- j1939_tp_out.TpOut[2].Addr_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[2]Addr_B";
*-   variable_location.symbol = j1939_tp_out.TpOut[2].Addr_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport Out Channel 2 address of destination for the data being transfered from this device";
*-   }

*- j1939_tp_out.TpOut[2].Pgn_L {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[2]Pgn_L";
*-   variable_location.symbol = j1939_tp_out.TpOut[2].Pgn_L;
*-   ds_precision             = ds_precision_UINT32;
*-   ds_scaling_mode          = ds_scaling_mode_UINT32;
*-   ds_const_a               = ds_const_a_UINT32;
*-   ds_const_b               = ds_const_b_UINT32;
*-   ds_scaling_unit          = ds_scaling_unit_UINT32;
*-   description              = "J1939 Transport Out Channel 2 PGN of data packet to be sent from this device";
*-   }

*- j1939_tp_out.TpOut[2].NextSequenceNum_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpOut.TpOut[2]NextSequenceNum_B";
*-   variable_location.symbol = j1939_tp_out.TpOut[2].NextSequenceNum_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport Out Channel 2 next data packet to be sent";
*-   }
*/


/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/
