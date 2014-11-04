#ifndef OBDLCDAT_H
#define OBDLCDAT_H

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

* FILE NAME:   : obdlcdat.h                                              *

* Project Name : Reusable KW2K                                         *

*                                                                      *

* Applicable   : Keyword Protocol 2000                                 *

* Documents                                                            *

* Version      : 1.0                                                   *

* Date         : July 10 1998.                                         *

*                                                                      *

* Purpose      : Keyword 2000 serial communication services            *

*                                                                      *

* Description  : This file contains the prototypes/declarations for all*

*                global constant variables and constant arrays.        *

*                                                                      *

* $Source: ems_project@brighton.tcb:daewoo_2002:obd_cal.h $

* $Revision: 1.1 $

* $Author: brighton.tcb:/users/safayya...aewoo_2002_MathLib:safayyad $

* Creation Date: MAY 5th 1997                                          *

*                                                                      *

************************************************************************

*                                                                      *

* Change Log:                                                          *

*                                                                      *

* Rev.    Date    User    Description of Changes                       *

* ----  --------  ----    ---------------------------------------------*

* 1.0   09-11-98  cwe     Initial file creation                        *

* 1.1   10-15-98  cdw     New version created from Daewoo delivery     *

* 1.3   07-15-98  cdw     Fixed cals for mode 1,2                      *

* 1.4   11-08-99  hfu     Delete unused definitions                    *

* 1.5   04-20-00  bdt     Delete unused K_C2_Vulnerability_Flag.       *
* 1.6   05-18-00  hfu     Remove unused const Kl1979_CalID.            *
* 1.7   08-04-03  ban RSM#2648                                         *
*                         Added Ka1979_M2_PID20_Thru40_Supp            *
*                         and Ka1979_M2_PID40_Thru60_Supp              *
* tci_pt3#4                                                            *
*       11-03-03  ban 3352  Added the following                        *
*                              Cy1979_Mode09_MaxCalCharPCM             *
*                              Cy1979_MaxCalIDsPCM                     *
*                              Cy1979_EngCalIDSize                     *
*                              Cy1979_TrnCalIDSize                     *
* tci_pt3#3.1.1                                                        *
*       11-14-03  ban 3312 Added Cy1979_MaxCVNIDs                      *
*                                Cy1979_MaxCVNIDsPCM                   *
***********************************************************************/
#include "obdltype.h"

/*********************************************************************/

/*            EQUATES                                                */

/*********************************************************************/
#define Cy1979_Mode_8_TIDs_Sup       0x04
#define Cy1979_Mode_6_TestRange      0x04
#define Cy1979_Mode_5_TestRange      0x14

#define Cy1979_PID01_Thru20          0x04
#define Cy1979_PID21_Thru40          0x04

#define ECU_NAME_Size  20

/*********************************************************************/

/*            TYPEDEFS AND STRUCTURE DECLARATIONS                    */

/*********************************************************************/

/* none                                                              */



/*********************************************************************/

/*          EXTERNED GLOBAL VARIABLES                                */

/*********************************************************************/

/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 1 and bit 0 corresponds to */

/* info type 8.0 = info type not supported and 1 = info type         */

/* supported.                                                        */

extern const BYTE Ky1979_Mode_09_Info_01_To_08;

extern const BYTE KyDCAN_Mode_09_Info_01_To_08;

/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 9 and bit 0 corresponds to */

/* info type 16.0 = info type not supported and 1 = info type        */

/* supported.                                                        */

extern const BYTE Ky1979_Mode_09_Info_09_To_16;

/* ECU NAME: ECM -Engine Control */
extern const BYTE KyDCAN_ECM_EcuName[];

/* ECU NAME: PCM -Powertrain Crtl */
extern const BYTE KyDCAN_PCM_EcuName[];

/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 17 and bit 0 corresponds to*/

/* info type 24.0 = info type not supported and 1 = info type        */

/* supported.                                                        */

extern const BYTE Ky1979_Mode_09_Info_17_To_24;



/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 25 and bit 0 corresponds to*/

/* info type 32.0 = info type not supported and 1 = info type        */

/* supported.                                                        */

extern const BYTE Ky1979_Mode_09_Info_25_To_32;



/* Added for mode 1 and mode 2 */

extern const BYTE Ka1979_M1_PID_Supported[];
extern const BYTE Ka1979_M2_PID_Supported[];
extern const BYTE Ka1979_M1_PID20_Thru40_Supp[];
extern const BYTE Ka1979_M1_PID40_Thru60_Supp[];
extern const BYTE Ka1979_M2_PID20_Thru40_Supp[];
extern const BYTE Ka1979_M2_PID40_Thru60_Supp[];

extern const BYTE Ka1979_M6_TestRange_TestID_Supp[];
extern const BYTE Ka1979_M5_TestRange_00Thru80[];
extern const BYTE Ka1979_M8_TID_Supported[];

extern const BYTE KyC2AP_O2Snsrs_Supported;

#endif


