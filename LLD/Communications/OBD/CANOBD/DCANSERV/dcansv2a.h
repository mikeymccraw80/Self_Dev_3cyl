#ifndef DCANSV2A_H
#define DCANSV2A_H
/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
*  ALL RIGHTS RESERVED                                                 *
*  This program may not be reproduced, in whole or in part in any form *
*  or by any means whatsoever without the written permission of:       *
*                                                                      *
*         DELCO ELECTRONICS CORPORATION                                *
*         One Corporate Center                                         *
*         Kokomo, Indiana  46904-9005                                  *
*         USA                                                          *
*                                                                      *
************************************************************************
* Filename     : dcansv2a.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : CANOBD                                *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 10 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the extern and inline functions  *
*                related to the Keyword 2000 Diagnostic Service 10     *
*                as defined by the above applicable doc.               *
*                                                                      *
* $Source: ems_project@bright...:daewoo_2002:kw2srv10.h $              *
* $Revision: 1.1 $                                                     *
* $Author: brighton.tcb:/users/sa...o_2002_MathLib:safayyad $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-16-98  JZha    Initial file creation                        *
* 1.4   01-25-99  JZha    Standardized this file.                      *
* 1.5   10-07-99  IAJ     Chnaged the callback function name in the    *
*                         extern declaration.                          *
************************************************************************
* Functions in this file:                                              *
************************************************************************
* extern:                                                              *
*        void LnDiagnosticSessionControl (void);                  *
* Inline:                                                              *

***********************************************************************/
#include "dcanpcfg.h"
#include "obdsbase.h"
/*********************************************************************/
/*          GLOBAL FUNCTION PROTOTYPES                               */
/*********************************************************************/
extern void DefineOSTK_EmptyFunction(void);

#if (XeDCAN_SID_2A_Supported == CeDCAN_Supported)
#define PIDDUMMY     0x0000

#define Dpid01  (0x01)
#define Dpid02  (0x02)
#define Dpid03  (0x03)
#define Dpid04  (0x04)
#define Dpid05  (0x05)
#define Dpid06  (0x06)
#define Dpid07  (0x07)
#define Dpid08  (0x08)
#define Dpid09  (0x09)
#define Dpid0A  (0x0A)

/*--- Sub-functions parameter definition ---*/
#define StopSending           (0x04)
#define ScheduleAtSlowRate    (0x01)
#define ScheduleAtMediumRate  (0x02)
#define ScheduleAtFastRate    (0x03)

/*-----------------------------------------------*/
/*--- RECEIVE / TRANSMIT BUFFERS DISTRIBUTION ---*/
/*-----------------------------------------------*/
#define TX_MSG_BUFFER_NUMBER      (18)
   /* effective number of Tx msg allocated */

typedef uint8_t DataPacketIdentifierType;
typedef uint16_t Array7PidType [7];

extern const uint8_t DpidNumberTab [];
extern Array7PidType LnDpidsTxDefinitionArray[];
void ClearAndDisableAllDpids (void);
void UpdateReadDataByPacketIdentifier (void);
void LnReadDataByPacketIdentifier (void);

#else /* SID_2A not Supported */

#define LnReadDataByPacketIdentifier        ServiceNotSupported_DCAN
#define ClearAndDisableAllDpids             DefineOSTK_EmptyFunction
#define UpdateReadDataByPacketIdentifier    DefineOSTK_EmptyFunction

#endif /* (XeDCAN_SID_2A_Supported == CeDCAN_Supported) */

#endif
