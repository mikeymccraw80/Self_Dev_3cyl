#ifndef DCANSV27_H
#define DCANSV27_H
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
* Filename     : dcansv27.h                                            *
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
* 2     04-09-12  cjqq    Update the CANOBD per customer requirement   *
* 3     07-31-12  azh     Add Kostal PEPS IMMO interface               *
* 4     02-05-13  azh     Added LnSeedToKey                            *
* 5     07-25-13  xll     Added SID27_MSG02_JAC_LENGTH                 *
************************************************************************
* Functions in this file:                                              *
************************************************************************
* extern:                                                              *
*        void LnDiagnosticSessionControl (void);                  *
* Inline:                                                              *

***********************************************************************/
#include "t_gentypes.h"
#include "dcanpcfg.h"
#include "obdspcfg.h"
#if (XeDCAN_SID_27_Supported == CeDCAN_Supported)
#define SubFuncRequestSeed (0x01)
#define SubFuncSendKey     (0x02)
#define SubFuncRequestSeed_EOL (0x03) /* Kostal IMMO: Request SEED for EOL matching mode */
#define SubFuncSendKey_EOL     (0x04) /* Kostal IMMO: Request security access for EOL matching mode */
#define SubFuncRequestSeed_AS  (0x05) /* Kostal IMMO: Request SEED for after sales matching mode */
#define SubFuncSendKey_AS      (0x06) /* Kostal IMMO: Request security access for after sales matching mode */

#define SID27_MSG01_LENGTH (2)
#define SID27_MSG02_LENGTH (4)
#define SID27_MSG02_DelphiGeneric_4KyLENGTH (6)
#define SID27_MSG02_JAC_LENGTH  (6)
#define SID27_MSG02_CHK011_LENGTH (6)
#define CHK011_Mask        (0x2045434D)
uint32_t LnSeedToKey (uint32_t seed, uint32_t mask);
void LnSecurityAccess (void);

#else /* SID_27 not Supported */

#define LnSecurityAccess        ServiceNotSupported_DCAN

#endif /* (XeDCAN_SID_27_Supported == CeDCAN_Supported) */

#endif
