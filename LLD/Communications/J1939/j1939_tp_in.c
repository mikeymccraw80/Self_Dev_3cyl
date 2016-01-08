/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: CNG E483                                                         *
* File Name:  j1939_tp_in.c                                                 *
* File Description:                                                         *
* J1939 RX transport protocol manager                                       *
*****************************************************************************/
#include "j1939_tp_in.h"
#include "j1939_tp.h"

/* System is limited to this number of active data-in transports */
typedef enum
{
   C_TpInConnection_0 = 0,
   C_TpInConnection_1,
   C_TpInConnection_2,
   C_MaxTpInConnections
} TpInConnectionIndex;

typedef enum
{
   TP_IN_INACTIVE = 0,
   TP_IN_CLEAR_TO_SEND,
   TP_IN_DATA_RECEPTION,
   TP_IN_ACK_MSG_END,
   TP_IN_INTERNAL_ABORT,
   TP_IN_EXTERNAL_ABORT
} TpInStateType;

typedef struct
{
   TpInStateType State;
   uint8_t Addr_B;
   uint32_t Pgn_L;
   uint16_t TotalNumDataBytes_W;
   uint8_t TotalNumPackets_B;
   uint8_t MaxNumPacketsPerCts_B;
   can_boolean_t (*BuffMgrRoutine) (TpInBuffMgrCmdType Cmd, uint16_t ByteLoc_W,
                                    uint16_t NumBytes_W, uint8_t *DataPtr);
   uint8_t NumPacketsInCts_B;
   uint8_t LastPacketInCts_B;
   uint8_t NextSequenceNum_B;
   can_boolean_t DataPacketReceivedFlag;
} TpInType;

TpInType TpIn[C_MaxTpInConnections];

/***************************************************************************/
/* FUNCTION: FixMin - Returns Min among the passed parameters              */
/***************************************************************************/
static uint8_t FixMin (uint8_t parameter1, uint8_t parameter2)
{
   uint8_t return_value;

   if (parameter1 <= parameter2)
   {
      return_value = parameter1;
   }
   else
   {
      return_value = parameter2;
   }

   return (return_value);
}

/***************************************************************************/
/* FUNCTION: TpInClearToSend                                               */
/***************************************************************************/
static can_boolean_t TpInClearToSend (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   PreparePgn60416Msg (TxMsgPtr, TpIn[Index].Addr_B, TpIn[Index].Pgn_L);
   TxMsgPtr->Data[0] = J1939_TP_CM_CTS;
   TxMsgPtr->Data[1] = TpIn[Index].NumPacketsInCts_B;
   TxMsgPtr->Data[2] = TpIn[Index].NextSequenceNum_B;
   TxMsgPtr->Data[3] = J1939_DATA_NOT_AVAILABLE;
   TxMsgPtr->Data[4] = J1939_DATA_NOT_AVAILABLE;
   TpIn[Index].DataPacketReceivedFlag = CAN_cbFALSE;
   TpIn[Index].State = TP_IN_DATA_RECEPTION;
   TxMsgPtr->Callback_Time_W = J1939_TP_POST_CTS_TIMEOUT;
   return (CAN_cbTRUE);
}


/***************************************************************************/
/* FUNCTION: WaitingForTpInDataPackets                                     */
/* If we got to this routine without receiving new data packets then       */
/* must have lost connection                                               */
/***************************************************************************/
static can_boolean_t WaitingForTpInDataPackets (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   can_boolean_t MsgToSend;

   if (TpIn[Index].DataPacketReceivedFlag)
   {
      MsgToSend = CAN_cbFALSE;
      TpIn[Index].DataPacketReceivedFlag = CAN_cbFALSE;
      TxMsgPtr->Callback_Time_W = J1939_TP_DATA_TIMEOUT;
   }
   else
   {
      TpIn[Index].State = TP_IN_INACTIVE;
      MsgToSend = CAN_cbTRUE;
      (void) (*TpIn[Index].BuffMgrRoutine) (TP_IN_UNLOCK_INVALID_BUFF, 0, 0, NULL);
      BuildTpAbortMsg (TxMsgPtr, TpIn[Index].Addr_B, TpIn[Index].Pgn_L,
                       J1939_TP_CM_ABORT_BECAUSE_TIMEOUT);
      TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   }

   return (MsgToSend);
}


/***************************************************************************/
/* FUNCTION: CloseTpInConnection                                           */
/***************************************************************************/
static can_boolean_t CloseTpInConnection (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   PreparePgn60416Msg (TxMsgPtr, TpIn[Index].Addr_B, TpIn[Index].Pgn_L);
   TxMsgPtr->Data[0] = J1939_TP_CM_END_ACK;
   TxMsgPtr->Data[1] = (uint8_t) (TpIn[Index].TotalNumDataBytes_W & 0x00FF);
   TxMsgPtr->Data[2] = (uint8_t) ( (TpIn[Index].TotalNumDataBytes_W & 0xFF00) >> 8);
   TxMsgPtr->Data[3] = (uint8_t) (TpIn[Index].TotalNumPackets_B);
   TxMsgPtr->Data[4] = J1939_DATA_NOT_AVAILABLE;
   TpIn[Index].State = TP_IN_INACTIVE;
   TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   return (CAN_cbTRUE);
}


/***************************************************************************/
/* FUNCTION: InternalAbortTpInConnection                                   */
/* If we got to this routine then this device has requested connection be  */
/* broken                                                                  */
/***************************************************************************/
static can_boolean_t InternalAbortTpInConnection (uint8_t Index,
                                                  J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   BuildTpAbortMsg (TxMsgPtr, TpIn[Index].Addr_B, TpIn[Index].Pgn_L,
                    J1939_TP_CM_ABORT_BECAUSE_RESOURCE_ISSUE);
   TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   TpIn[Index].State = TP_IN_INACTIVE;
   return (CAN_cbTRUE);
}


/***************************************************************************/
/* FUNCTION: ExternalAbortTpInConnection                                   */
/* If we got to this routine then the dest device must have sent a         */
/* request to abort message                                                */
/***************************************************************************/
static void ExternalAbortTpInConnection (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   TxMsgPtr->Callback_Time_W = CAN_NO_PERIODIC_SERVICE;
   TpIn[Index].State = TP_IN_INACTIVE;
}

/***************************************************************************/
/* FUNCTION: ServiceTransportInMessage                                     */
/***************************************************************************/
static can_boolean_t ServiceTransportInMessage (uint8_t Index, J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   can_boolean_t MsgToSend;
   MsgToSend = CAN_cbFALSE;

   switch (TpIn[Index].State)
   {
      case TP_IN_CLEAR_TO_SEND :
         MsgToSend = TpInClearToSend (Index, TxMsgPtr);
         break;

      case TP_IN_DATA_RECEPTION :
         MsgToSend = WaitingForTpInDataPackets (Index, TxMsgPtr);
         break;

      case TP_IN_ACK_MSG_END :
         MsgToSend = CloseTpInConnection (Index, TxMsgPtr);
         break;

      case TP_IN_INTERNAL_ABORT :
         MsgToSend = InternalAbortTpInConnection (Index, TxMsgPtr);
         break;

      case TP_IN_EXTERNAL_ABORT :
         ExternalAbortTpInConnection (Index, TxMsgPtr);
         break;

      case TP_IN_INACTIVE :
         break;

      default :
         break;
   }

   return (MsgToSend);
}


/***************************************************************************/
/* FUNCTION: ServiceTransportIn_X                                          */
/***************************************************************************/
static can_boolean_t ServiceTransportIn_0 (J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   return (ServiceTransportInMessage (0, TxMsgPtr));
}
static can_boolean_t ServiceTransportIn_1 (J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   return (ServiceTransportInMessage (1, TxMsgPtr));
}
static can_boolean_t ServiceTransportIn_2 (J1939_Transmit_Message_Info_T *TxMsgPtr)
{
   return (ServiceTransportInMessage (2, TxMsgPtr));
}


/***************************************************************************/
/* FUNCTION: CkActiveTpInConnectionToDevice                                */
/***************************************************************************/
static can_boolean_t CkActiveTpInConnectionToDevice (uint8_t Addr_B,
                                                     uint8_t *Index)
{
   uint8_t i;

   for (i = 0; ( (i < C_MaxTpInConnections) &&
                 ( (TpIn[i].Addr_B != Addr_B) || (TpIn[i].State == TP_IN_INACTIVE))); i++)
   {
      ;
   }

   *Index = i;
   return ( (i < C_MaxTpInConnections) ? CAN_cbTRUE : CAN_cbFALSE);
}


/***************************************************************************/
/* FUNCTION: SetCtsParameters                                              */
/***************************************************************************/
static void SetCtsParameters (uint8_t Index)
{
   uint8_t StartPacket_B, Packets_B;
   StartPacket_B = TpIn[Index].NextSequenceNum_B;
   Packets_B = TpIn[Index].TotalNumPackets_B - StartPacket_B + 1;
   Packets_B = FixMin (Packets_B, TpIn[Index].MaxNumPacketsPerCts_B);
   TpIn[Index].NumPacketsInCts_B = Packets_B;
   TpIn[Index].LastPacketInCts_B = StartPacket_B + Packets_B - 1;
}

/***************************************************************************/
/* FUNCTION: LoadTransportIn                                               */
/*  Returns Pointer to TpIn element fi connection available and loaded     */
/***************************************************************************/
static can_boolean_t LoadTransportIn (uint8_t Addr_B, uint16_t
                                      TotalNumDataBytes_W, uint8_t TotalNumPackets_B, uint8_t MaxNumPacketsPerCts_B,
                                      uint32_t Pgn_L)
{
   can_boolean_t (*BuffMgrRoutine) (TpInBuffMgrCmdType Cmd, uint16_t ByteLoc_W,
                                    uint16_t NumBytes_W, uint8_t * DataPtr);
   uint8_t Index;
   can_boolean_t Loaded;
   Loaded = CAN_cbFALSE;

   switch (Pgn_L)
   {
         //case 65291 : BuffMgrRoutine = Pgn65291TpInBuffMgr; break;
      case 65291 :
         BuffMgrRoutine = NULL;
         break;

      default     :
         BuffMgrRoutine = NULL;
         break;
   }

   if (BuffMgrRoutine)
   {
      /* Find Inactive Channel */
      for (Index = 0; ( (TpIn[Index].State != TP_IN_INACTIVE)
                        && (++Index < C_MaxTpInConnections));)
      {
         ;
      }

      if ( (Index < C_MaxTpInConnections)
           && (BuffMgrRoutine (TP_IN_LOCK_BUFF, 0, TotalNumDataBytes_W, NULL)))
      {
         TpIn[Index].BuffMgrRoutine = BuffMgrRoutine;
         TpIn[Index].Addr_B = Addr_B;
         TpIn[Index].Pgn_L = Pgn_L;
         TpIn[Index].TotalNumDataBytes_W = TotalNumDataBytes_W;
         TpIn[Index].TotalNumPackets_B = TotalNumPackets_B;
         TpIn[Index].MaxNumPacketsPerCts_B = MaxNumPacketsPerCts_B;
         TpIn[Index].NextSequenceNum_B = 1;
         SetCtsParameters (Index);
         TpIn[Index].State = TP_IN_CLEAR_TO_SEND;
         J1939_Trigger_Transmit_Message_Service (0x03 + Index);
         Loaded = CAN_cbTRUE;
      }
   }

   return (Loaded);
}

/***************************************************************************/
/* FUNCTION: ParseTransportIn_RTS                                          */
/***************************************************************************/
void ParseTransportIn_RTS (J1939_Receive_Message_Info_T *RxMsg)
{
   J1939_Transmit_Message_Info_T TxMsg;
   uint32_t Pgn_L;
   uint16_t TotalNumDataBytes_W;
   uint8_t Addr_B, TotalNumPackets_B, MaxNumPacketsPerCts_B, Index;
   uint8_t AbortReason_B;
   TpParseSrcAndPgn (RxMsg, &Addr_B, &Pgn_L);
   TotalNumDataBytes_W = (uint16_t) RxMsg->Data[1] + ( (uint16_t) RxMsg->Data[2] << 8);
   TotalNumPackets_B = RxMsg->Data[3];
   MaxNumPacketsPerCts_B = RxMsg->Data[4];
   AbortReason_B = J1939_TP_CM_NO_ABORT;

   /* Check for bad data in RTS */
   if ( (TotalNumDataBytes_W == 0)
        || (TotalNumPackets_B == 0)
        || (MaxNumPacketsPerCts_B == 0)
        || (TotalNumPackets_B != (TotalNumDataBytes_W + 6) / 7))
   {
      /* Assign abort reason to resource because no abort reason applies */
      AbortReason_B = J1939_TP_CM_ABORT_BECAUSE_RESOURCE_ISSUE;
   }
   else if (CkActiveTpInConnectionToDevice (Addr_B, &Index))
   {
      AbortReason_B = J1939_TP_CM_ABORT_BECAUSE_ALREADY_IN_SESSION_WITH_DEVICE;
   }
   else if (! LoadTransportIn (Addr_B, TotalNumDataBytes_W,
                               TotalNumPackets_B, MaxNumPacketsPerCts_B, Pgn_L))
   {
      AbortReason_B = J1939_TP_CM_ABORT_BECAUSE_RESOURCE_ISSUE;
   }
   else
   {
   }

   if (AbortReason_B != J1939_TP_CM_NO_ABORT)
   {
      BuildTpAbortMsg (&TxMsg, Addr_B, Pgn_L, AbortReason_B);
      //(void)
      J1939_Transmit_Unmanaged_Message (&TxMsg); //CAN_TransmitUnmanagedMessage (&TxMsg);
   }
}


/***************************************************************************/
/* FUNCTION: Parse_PGN_60160                                               */
/* Description: Transport protocol management connection to CAN manager    */
/***************************************************************************/
static void Parse_PGN_60160 (J1939_Receive_Message_Info_T *RxMsg)
{
   uint16_t ByteLoc_W, NumBytes_W;
   uint8_t Addr_B, SequenceNum_B, Index;
   can_boolean_t KeepConnection;
   KeepConnection = CAN_cbTRUE;
   /* Just ignore if connection not established with sender of this data */
   Addr_B = J1939_GET_SRC_ADDR (RxMsg->ID);

   if ( (CkActiveTpInConnectionToDevice (Addr_B, &Index))
        && (TpIn[Index].State == TP_IN_DATA_RECEPTION))
   {
      /* Flag data received to avoid timeout */
      TpIn[Index].DataPacketReceivedFlag = CAN_cbTRUE;
      /* If sequence number as expected, copy data into buffer and inc seq num */
      SequenceNum_B = RxMsg->Data[0];

      if (SequenceNum_B == TpIn[Index].NextSequenceNum_B)
      {
         ByteLoc_W = (SequenceNum_B - 1) * 7;
         /* Cheap insurance for a bad RTS data */
         ByteLoc_W = FixMin (ByteLoc_W, TpIn[Index].TotalNumDataBytes_W);
         NumBytes_W = (SequenceNum_B < TpIn[Index].TotalNumPackets_B) ? 7 :
                      TpIn[Index].TotalNumDataBytes_W - ByteLoc_W;
         KeepConnection = (*TpIn[Index].BuffMgrRoutine) (TP_IN_PUT_DATA, ByteLoc_W,
                                                         NumBytes_W, &RxMsg->Data[1]);
         TpIn[Index].NextSequenceNum_B++;
      }

      if (! KeepConnection)
      {
         (void) (*TpIn[Index].BuffMgrRoutine) (TP_IN_UNLOCK_INVALID_BUFF, 0, 0, NULL);
         TpIn[Index].State = TP_IN_INTERNAL_ABORT;
      }
      else if (SequenceNum_B >= TpIn[Index].TotalNumPackets_B)
      {
         /* If at end of data then ACK end of msg */
         TpIn[Index].State = TP_IN_ACK_MSG_END;
         (void) (*TpIn[Index].BuffMgrRoutine) (TP_IN_UNLOCK_VALID_BUFF, 0, 0, NULL);
      }
      else if (SequenceNum_B >= TpIn[Index].LastPacketInCts_B)
      {
         /* If last CTS num packets met then send another CTS */
         SetCtsParameters (Index);
         TpIn[Index].State = TP_IN_CLEAR_TO_SEND;
      }
      else
      {
      }

      if (TpIn[Index].State != TP_IN_DATA_RECEPTION)
      {
         /* If state has changed then trigger msg to be sent */
         J1939_Trigger_Transmit_Message_Service (0x03 + Index);
      }
   }
}


/***************************************************************************/
/* FUNCTION: ParseTransportIn_Abort                                        */
/***************************************************************************/
void ParseTransportIn_Abort (J1939_Receive_Message_Info_T *RxMsg)
{
   uint8_t Addr_B;
   uint8_t Index;
   uint32_t Pgn_L;
   TpParseSrcAndPgn (RxMsg, &Addr_B, &Pgn_L);

   /* Is there currently an active connection to this device, does the */
   /* PGN match, and is it in the correct state */
   if ( (CkActiveTpInConnectionToDevice (Addr_B, &Index)) &&
        (TpIn[Index].Pgn_L == Pgn_L))
   {
      (void) (*TpIn[Index].BuffMgrRoutine) (TP_IN_UNLOCK_INVALID_BUFF, 0, 0, NULL);
      TpIn[Index].State = TP_IN_EXTERNAL_ABORT;
      /* Trigger can bus manager that this transport connection needs service */
      J1939_Trigger_Transmit_Message_Service (Index);  // TP out index
   }
}


/***************************************************************************/
/* FUNCTION: J1939_TxInit_TranportIn_X                                     */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J1939_TxInit_TransportIn_0 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = ServiceTransportIn_0;
   MsgCtrl->Time_To_Service = 0x00;
   MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE; //Non periodic message
   MsgCtrl->Tx_Timeout = 0x00;
   MsgCtrl->Tx_Timeout_Timer_W = 0x00;
   TpIn[0].State = TP_IN_INACTIVE; /* Cheap Insurance */
}

void J1939_TxInit_TransportIn_1 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = ServiceTransportIn_1;
   MsgCtrl->Time_To_Service = 0x00;
   MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE; //Non periodic message
   MsgCtrl->Tx_Timeout = 0x00;
   MsgCtrl->Tx_Timeout_Timer_W = 0x00;
   TpIn[1].State = TP_IN_INACTIVE; /* Cheap Insurance */
}

void J1939_TxInit_TransportIn_2 (J1939_Transmit_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Service_Routine = ServiceTransportIn_2;
   MsgCtrl->Time_To_Service = 0x00;
   MsgCtrl->Time_To_Next_Service_W = CAN_NO_PERIODIC_SERVICE; //Non periodic message
   MsgCtrl->Tx_Timeout = 0x00;
   MsgCtrl->Tx_Timeout_Timer_W = 0x00;
   TpIn[2].State = TP_IN_INACTIVE; /* Cheap Insurance */
}

/***************************************************************************/
/* FUNCTION: J1939_RxInit_PGN_60160                                        */
/* Description: Initialize hooks to can manager                            */
/***************************************************************************/
void J1939_RxInit_PGN_60160 (J1939_Receive_Message_Control_T *MsgCtrl)
{
   MsgCtrl->Parse_Routine = Parse_PGN_60160;
   MsgCtrl->Message_Lost = 0x00;
   MsgCtrl->Message_Lost_Action_Taken = 0x00;
   MsgCtrl->Message_Lost_Timeout_W = CAN_NO_LOST_TIMER;
   MsgCtrl->Message_Lost_Timer_W = MsgCtrl->Message_Lost_Timeout_W;
}

/*
*- j1939_tp_in.TpIn[0].State {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[0]State";
*-   variable_location.symbol = j1939_tp_in.TpIn[0].State;
*-   description              = "J1939 Transport In Channel 0 State";
*-   }

*- j1939_tp_in.TpIn[0].Addr_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[0]Addr_B";
*-   variable_location.symbol = j1939_tp_in.TpIn[0].Addr_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport In Channel 0 address of sender of RTS";
*-   }

*- j1939_tp_in.TpIn[0].Pgn_L {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[0]Pgn_L";
*-   variable_location.symbol = j1939_tp_in.TpIn[0].Pgn_L;
*-   ds_precision             = ds_precision_UINT32;
*-   ds_scaling_mode          = ds_scaling_mode_UINT32;
*-   ds_const_a               = ds_const_a_UINT32;
*-   ds_const_b               = ds_const_b_UINT32;
*-   ds_scaling_unit          = ds_scaling_unit_UINT32;
*-   description              = "J1939 Transport In Channel 0 PGN of data packet to be sent to this device";
*-   }

*- j1939_tp_in.TpIn[0].NextSequenceNum_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[0]NextSequenceNum_B";
*-   variable_location.symbol = j1939_tp_in.TpIn[0].NextSequenceNum_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport In Channel 0 next data packet to be received";
*-   }
*****************************************************************************

*- j1939_tp_in.TpIn[1].State {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[1]State";
*-   variable_location.symbol = j1939_tp_in.TpIn[1].State;
*-   description              = "J1939 Transport In Channel 1 State";
*-   }

*- j1939_tp_in.TpIn[1].Addr_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[1]Addr_B";
*-   variable_location.symbol = j1939_tp_in.TpIn[1].Addr_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport In Channel 1 address of sender of RTS";
*-   }

*- j1939_tp_in.TpIn[1].Pgn_L {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[1]Pgn_L";
*-   variable_location.symbol = j1939_tp_in.TpIn[1].Pgn_L;
*-   ds_precision             = ds_precision_UINT32;
*-   ds_scaling_mode          = ds_scaling_mode_UINT32;
*-   ds_const_a               = ds_const_a_UINT32;
*-   ds_const_b               = ds_const_b_UINT32;
*-   ds_scaling_unit          = ds_scaling_unit_UINT32;
*-   description              = "J1939 Transport In Channel 1 PGN of data packet to be sent to this device";
*-   }

*- j1939_tp_in.TpIn[1].NextSequenceNum_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[1]NextSequenceNum_B";
*-   variable_location.symbol = j1939_tp_in.TpIn[1].NextSequenceNum_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport In Channel 1 next data packet to be received";
*-   }
*****************************************************************************

*- j1939_tp_in.TpIn[2].State {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[2]State";
*-   variable_location.symbol = j1939_tp_in.TpIn[2].State;
*-   description              = "J1939 Transport In Channel 2 State";
*-   }

*- j1939_tp_in.TpIn[2].Addr_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[2]Addr_B";
*-   variable_location.symbol = j1939_tp_in.TpIn[2].Addr_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport In Channel 2 address of sender of RTS";
*-   }

*- j1939_tp_in.TpIn[2].Pgn_L {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[2]Pgn_L";
*-   variable_location.symbol = j1939_tp_in.TpIn[2].Pgn_L;
*-   ds_precision             = ds_precision_UINT32;
*-   ds_scaling_mode          = ds_scaling_mode_UINT32;
*-   ds_const_a               = ds_const_a_UINT32;
*-   ds_const_b               = ds_const_b_UINT32;
*-   ds_scaling_unit          = ds_scaling_unit_UINT32;
*-   description              = "J1939 Transport In Channel 2 PGN of data packet to be sent to this device";
*-   }

*- j1939_tp_in.TpIn[2].NextSequenceNum_B {
*-   OBJECTS_CLASS: parameter_es_class;
*-   label                    = "Can.TpIn.TpIn[2]NextSequenceNum_B";
*-   variable_location.symbol = j1939_tp_in.TpIn[2].NextSequenceNum_B;
*-   ds_precision             = ds_precision_Int_0to255_B;
*-   ds_scaling_mode          = ds_scaling_mode_Int_0to255_B;
*-   ds_const_a               = ds_const_a_Int_0to255_B;
*-   ds_const_b               = ds_const_b_Int_0to255_B;
*-   ds_scaling_unit          = ds_scaling_unit_Int_0to255_B;
*-   description              = "J1939 Transport In Channel 2 next data packet to be received";
*-   }
*/

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/
