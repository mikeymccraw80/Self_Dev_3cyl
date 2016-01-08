/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: CNG E483                                                         *
* File Name:  j1939_tp_out.h                                                *
* File Description:                                                         *
* J1939 RX transport protocol manager                                       *
*****************************************************************************/
#ifndef J1939_TP_OUT_DEF
#define J1939_TP_OUT_DEF
#include "j1939_tp.h"

/************************************************************************/
/* DEFINE: TpOutStateType                                               */
/* Description: Reflects the current state of an Transfer Out connection*/
/************************************************************************/
typedef enum
{
   TP_OUT_INACTIVE = 0,
   TP_OUT_REQUEST_TO_SEND,
   TP_OUT_WAIT_FOR_CLEAR_TO_SEND,
   TP_OUT_DATA_TRANSPORT,
   TP_OUT_WAIT_FOR_END_ACK,
   TP_OUT_END_ACK,
   TP_OUT_INTERNAL_ABORT,
   TP_OUT_EXTERNAL_ABORT
} TpOutStateType;

typedef enum
{
   C_TpOutConnection_0 = 0,
   C_TpOutConnection_1,
   C_TpOutConnection_2,
   C_MaxTpOutConnections
} TpOutConnectionIndex;

typedef struct
{
   TpOutStateType State;
   uint8_t Addr_B;
   uint32_t Pgn_L;
   uint16_t NumDataBytes_W;
   uint8_t NumDataPackets_B;
   uint8_t ClearToSend_B;
   can_boolean_t AllPacketsSent;
   can_boolean_t (*ServiceRoutine) (TpOutStateType State, J1939_Transmit_Message_Info_T *TxMsgPtr);
   uint8_t NextSequenceNum_B;
} TpOutType;

/***************************************************************************/
/* FUNCTION: J1939_TxInit_TransportOut_X                                   */
/* Description: Transport protocol management connection to can manager    */
/***************************************************************************/
extern void ParseTransportOut_CTS (J1939_Receive_Message_Info_T *RxMsg);
extern void ParseTransportOut_Abort (J1939_Receive_Message_Info_T *RxMsg);
extern void ParseTransportOut_EndAck (J1939_Receive_Message_Info_T *RxMsg);


/***************************************************************************/
/* FUNCTION: J1939_RequestTransportManagement                              */
/***************************************************************************/
extern can_boolean_t J1939_RequestTransportOutManagement (uint8_t DestAddr_B,
                                                          uint16_t NumDataBytes_W, uint32_t Pgn_L,
                                                          can_boolean_t (*ServiceProc) (TpOutStateType State, J1939_Transmit_Message_Info_T *TxMsg));

/***************************************************************************/
/* FUNCTION: J1939_CkMessageCurrentlyInTransport                         */
/***************************************************************************/
extern can_boolean_t J1939_CkPgnCurrentlyInTransportOut (uint32_t Pgn_L);


/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/
#endif
