/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: CNG E483                                                         *
* File Name:  j1939_tp.c                                                    *
* File Description:                                                         *
* J1939 transport protocol manager                                          *
*****************************************************************************/

#ifndef J1939_TP_DEF
#define J1939_TP_DEF

#include "j1939_pgn_config.h"
#include "j1939_tp_in.h"
#include "j1939_tp_out.h"

/***********************************************************************/
/* 60416 Transport Protocol connection Management                      */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 60416)                               */
/*  |  |   | | PGN (PF = 236, PS = DA => PGN = 60416 + yy)             */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1100 yyyy yyyy,xxxx xxxx y = destination address   */
/* 0001/1000/1110/1100/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_60416_BASE_ID (0x18EC0000) /*0xECyy=60416 + yy */
#define J1939_PGN_60416_LENGTH  (8)


/***********************************************************************/
/* 60160 Transport Protocol data Transfer                              */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 60160)                               */
/*  |  |   | | PGN (PF = 235, PS = DA => PGN = 60160 + yy              */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1011 yyyy yyyy,xxxx xxxx                           */
/* 0001/1000/1110/1011/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_60160_BASE_ID (0x18EB0000) /*0xEByy=60160 + yy */
#define J1939_PGN_60160_LENGTH  (8)


/************************************************************************/
/* DEFINE: J1939_TP_CM_xxx                                              */
/* Description: PGN 60416 Control Byte values                           */
/************************************************************************/
#define J1939_TP_CM_RTS      (16)
#define J1939_TP_CM_CTS      (17)
#define J1939_TP_CM_END_ACK  (19)
#define J1939_TP_CM_BAM      (32)
#define J1939_TP_CM_ABORT    (255)

/************************************************************************/
/* DEFINE: J1939_TP_CM_ABORT_BECAUSE_XXX                                */
/* Description: PGN 60416 Reason for aborting                           */
/************************************************************************/
#define J1939_TP_CM_NO_ABORT (0)
#define J1939_TP_CM_ABORT_BECAUSE_ALREADY_IN_SESSION_WITH_DEVICE (1)
#define J1939_TP_CM_ABORT_BECAUSE_RESOURCE_ISSUE (2)
#define J1939_TP_CM_ABORT_BECAUSE_TIMEOUT (3)

/* Functions from j1939_tp */
extern void TpParseSrcAndPgn (J1939_Receive_Message_Info_T *RxMsg, uint8_t *SrcPtr, uint32_t *PgnPtr);
extern void PreparePgn60416Msg (J1939_Transmit_Message_Info_T *TxMsgPtr, uint8_t DestAddr_B, uint32_t Pgn_L);
extern void BuildTpAbortMsg (J1939_Transmit_Message_Info_T *TxMsgPtr, uint8_t DestAddr_B, uint32_t Pgn_L,
                             uint8_t AbortReason_B);
extern void J1939_RxInit_PGN_60416 (J1939_Receive_Message_Control_T *MsgCtrl);

extern void J1939_RxInit_PGN_60160 (J1939_Receive_Message_Control_T *MsgCtrl);

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/
#endif
