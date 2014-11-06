#ifndef KW2CAL_H
#define KW2CAL_H
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
* FILE NAME:   : kw2cal.h                                              *
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
* $Source: ems_project@brighton.tcb:daewoo_2004:kw2cal.h $
* $Revision: 1.1 $
* $Author: brighton $
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
************************************************************************
* Daewoo 2004 Node and Partition                                       *
************************************************************************
* 1.1   030616 kmf 2835 Change PIDs supported under service mode $02   *
*                       (Ka1979_M2_PID_Supported) for CARB compliance. *
***********************************************************************/
#include "t_base.h"
#include "t_custom.h"
/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/

#define Cy1979_Mode09_MaxCalChar     16
#define Cy1979_MaxCalIDs             1
#if 0
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

/* this defines the supported info types in case of mode 9 J1979     */
/* message.bit 7 corresponds to info type 9 and bit 0 corresponds to */
/* info type 16.0 = info type not supported and 1 = info type        */
/* supported.                                                        */
extern const BYTE Ky1979_Mode_09_Info_09_To_16;

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

/* Added for mode 1 and mode 2*/
extern const BYTE Ka1979_M1_PID_Supported[];
extern const BYTE Ka1979_M2_PID_Supported[];

/* Added for Mode 08                                                  */
/* Test Range currently supported is 0x00, therefore all are          */
/* initialized to 0x00                                                */
extern const BYTE Ka1979_M8_TID_Supported[];

/* This gives the o2 sensors supported by the application as          */
/* such. This is required for mode 5 and this is irrespective of the  */
/* mode 5, test IDs supported. Currently Isuzu2000 supports           */
/* Bank1Sensor1 and Bank2Sensor1.                                     */
/* Bit 0 - Bank1Sensor1; Bit 1 - Bank1Sensor2; Bit 2 - Bank1Sensor3   */
/* Bit 3 - Bank1Sensor4; Bit 4 - Bank2Sensor1; Bit 5 - Bank2Sensor2   */
/* Bit 6 - Bank2Sensor3; Bit 7 - Bank2Sensor4;                        */
extern const BYTE KyC2AP_O2Snsrs_Supported;

/* Update Mode 6 supported test for T-150 spec. 1.7. bdt 3-31-00      */
/* This calibration array contains calibration data to indicate       */
/* support or nonsupport of a Test ID for Mode 06.                    */
/* Data A - Bit 7; 1= Test ID[Test Range +01] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +08] supported; 0 = not sup. */
/* Data B - Bit 7; 1= Test ID[Test Range +09] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +10] supported; 0 = not sup. */
/* Data C - Bit 7; 1= Test ID[Test Range +11] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +18] supported; 0 = not sup. */
/* Data D - Bit 7; 1= Test ID[Test Range +19] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +20] supported; 0 = not sup. */
extern const BYTE Ka1979_M6_TestRange_TestID_Supp[];

/* Following is a calibration parameter such that each bit indicates  */
/* support or non-support of a PID by the Powertrain controller       */
/* 0 = PID not supported and 1 = PID supported                        */
/* 0th Byte(bit 7) corresponds to PID 21                              */
/* 3rd Byte(bit 0) corresponds to PID 40                              */
extern const BYTE Ka1979_M1_PID20_Thru40_Supp[];

/* Following is a calibration parameter such that each bit indicates  */
/* support or non-support of a PID by the Powertrain controller       */
/* 0 = PID not supported and 1 = PID supported                        */
/* 0th Byte(bit 7) corresponds to PID 41                              */
/* 3rd Byte(bit 0) corresponds to PID 60                              */
extern const BYTE Ka1979_M1_PID40_Thru60_Supp[];

/* Following is a calibration parameter such that each bit indicates  */
/* support or non-support of a PID by the Powertrain controller       */
/* 0 = PID not supported and 1 = PID supported                        */
/* 0th Byte(bit 7) corresponds to PID 21                              */
/* 3rd Byte(bit 0) corresponds to PID 40                              */
extern const BYTE Ka1979_M2_PID20_Thru40_Supp[];

/* Following is a calibration parameter such that each bit indicates  */
/* support or non-support of a PID by the Powertrain controller       */
/* 0 = PID not supported and 1 = PID supported                        */
/* 0th Byte(bit 7) corresponds to PID 41                              */
/* 3rd Byte(bit 0) corresponds to PID 60                              */
extern const BYTE Ka1979_M2_PID40_Thru60_Supp[];

/* Following cals are for Mode 5, to indicate the supported Test ID's */
/* For given Test Range. Rroup of four bytes are encoded as follows   */
/* Data A - Bit 7; 1= Test ID[Test Range +01] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +08] supported; 0 = not sup. */
/* Data B - Bit 7; 1= Test ID[Test Range +09] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +10] supported; 0 = not sup. */
/* Data C - Bit 7; 1= Test ID[Test Range +11] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +18] supported; 0 = not sup. */
/* Data D - Bit 7; 1= Test ID[Test Range +19] supported; 0 = not sup. */
/*          ....                                                      */
/*          Bit 0; 1= Test ID[Test Range +20] supported; 0 = not sup. */
extern const BYTE Ka1979_M5_TestRange_00Thru80[];

/******************************************************************************
 *  Global Constant Declarations for Cal Form
 *****************************************************************************/
extern const T_COUNT_BYTE KySYST_CALIBRATION_FILE_PART_NR[] ;
#endif

#endif

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 12/04/05     Q.W         294
 * + Baseline - Created for the U2 program.
 *
 * 12/09/05     LShoujun    mt20u2#25 
 *  + Updated i6lgen.exe to version 3.3
 *    - Removed GetSupportedPID() to cmnpidapi.c
 *    - Added CAL comments coming from kw2cal.c
 *
 * March/09/2006 Q.W     mt20u2#47
 * + Support SAE J1979 kw2000 modes
 *  -Add new cal KySYST_CALIBRATION_FILE_PART_NR for J1979 mode 09 support.
\* ============================================================================ */

