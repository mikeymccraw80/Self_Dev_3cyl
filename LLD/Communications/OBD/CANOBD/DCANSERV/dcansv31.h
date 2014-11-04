#ifndef DCANSV31_H
#define DCANSV31_H
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
* Filename     : dcansv31.h                                            *
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
* 4     07-31-12  azh     Add Kostal PEPS IMMO interface               *
************************************************************************
* Functions in this file:                                              *
************************************************************************
* extern:                                                              *
*        void LnDiagnosticSessionControl (void);                  *
* Inline:                                                              *

***********************************************************************/
#include "dcanpcfg.h"
#include "obdsbase.h"

#if (XeDCAN_SID_31_Supported == CeDCAN_Supported)

typedef uint8_t  (* DS_RC_HNDL_FUNC)(uint8_t type);

typedef struct
{
    uint16_t Identifier;
    bool Protected;
    DS_RC_HNDL_FUNC HandlerFunc;
}DS_ROUTINE_CTRL;

extern uint8_t VyDCAN_SRV31_PosRespLength;
#define SetDCAN_SRV31_PosRespLength(x) (VyDCAN_SRV31_PosRespLength = x)

void LnRoutineControl(void);
#else /* SID_31 not Supported */

#define LnRoutineControl        ServiceNotSupported_DCAN

#endif /* (XeDCAN_SID_31_Supported == CeDCAN_Supported) */

#endif
