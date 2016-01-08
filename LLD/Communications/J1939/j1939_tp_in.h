/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: CNG E483                                                         *
* File Name:  j1939_tp_in.h                                                 *
* File Description:                                                         *
* J1939 RX transport protocol manager                                       *
*****************************************************************************/
#ifndef J1939_TP_IN_DEF
#define J1939_TP_IN_DEF
#include "j1939_tp.h"

/************************************************************************/
/* DEFINE: TpInBuffCmdType                                              */
/* Description: Reflects commands to be processed by the BufferMgrRtn   */
/************************************************************************/
typedef enum
{
   TP_IN_LOCK_BUFF,
   TP_IN_PUT_DATA,
   TP_IN_UNLOCK_INVALID_BUFF,
   TP_IN_UNLOCK_VALID_BUFF
} TpInBuffMgrCmdType;

/* Functions from j1939_tp_in */
extern void ParseTransportIn_RTS (J1939_Receive_Message_Info_T *RxMsg);
extern void ParseTransportIn_Abort (J1939_Receive_Message_Info_T *RxMsg);

/*******************************************************************************
 *                       REVISION HISTORY                                      *
 *******************************************************************************
 * Rev   Date      S/W Engineer                Description                     *
 * ===  ========  =============    ====================================        *
 * 1   08-Apr-10   Mehak           CNG E483 first release                      *
 ******************************************************************************/
#endif
