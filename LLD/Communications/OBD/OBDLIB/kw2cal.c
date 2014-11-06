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
*         USA                                                        *
*                                                                      *
************************************************************************
* FILE NAME:   : kw2cal.c                                              *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents                                                            *
* Version      : 1.0                                                   *
* Date         : July 10 1998.                                         *
*                                                                      *
* Purpose      : Keyword 2000 serial communication services            *
*                                                                      *
* Description  :  This file contains calibration data for kw2000       *
*                                                                      *
* $Source: ems_project@brighton.tcb:daewoo_2004:kw2cal.c $
* $Revision: 1.2 $
* $Author: brighton $
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.0   09-11-98  cwe     Initial file creation                        *
* 1.1   10-15-98  cdw     New version created from Daewoo delivery     *
* 1.5   07-27-99  HFU     Fixed modes 2 and 6.                         *
* 1.6   09-22-99  HFU     Change SID 05 Test Range to remove Test ID   *
*                         01, 02 in Daewoo Project                     *
* 1.7   11-08-99  HFU     Delete unused definitions                    *
* 1.8   03-31-00  bdt     Update Ka1979_M6_TestRange_TestID_Supp to    *
*                         SID 6 T-150 1.7 spec.                        *
* 1.9   04-07-00  bdt     Update Ka1979_M1_PID20_Thru40_Supp for       *
*                         SID 01 20 T-150 1.7 spec.                    *
* 1.10  04-07-00  bdt     Remove unused K_C2_Vulnerability_Flag        *
* 1.11  05-18-00  hfu     Remove unused const Kl1979_CalID.            *
************************************************************************
* Daewoo 2004 Node and Partition
************************************************************************
* 1.1   030616 kmf 2835 Change PIDs supported under service mode $02
*                       (Ka1979_M2_PID_Supported) for CARB compliance.
************************************************************************
*                                                                      *
* External variables and constants referenced, and why:                *
*          NAME                DECLARED IN     REASON/PURPOSE          *
*                                                                      *
***********************************************************************/

/*********************************************************************/
/*            INCLUDE FILES                                          */
/*********************************************************************/
#include "kw2type.h"        /* Data structure declarations.  */
#include "j1979.h"
#include "kw2cal.h"


/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/
#define Cy1979_Mode_8_TIDs_Sup       0x04
#define Cy1979_Mode_6_TestRange      0x04
#define Cy1979_PID20_Thru40          0x04
#define Cy1979_PID40_Thru60          0x04
#define Cy1979_Mode_5_TestRange      0x14
#if 0
/*********************************************************************/
/*            TYPEDEFS AND STRUCTURE DECLARATIONS                    */
/*********************************************************************/
/* none                                                              */
/*********************************************************************/
/*            GLOBAL CONSTANT VARIABLES                              */
/*********************************************************************/
/*
*| kw2cal. {
*|    Ky1979_Mode_09_Info_01_To_08 {
*|    : units       = "Bit-Encoded";
*|    : description = "J1979 Mode_09 supported info types. "
*|      "Bit 7 corresponds to info type 1 and bit 0 corresponds to "
*|      "info type 8. 0 = info type not supported and 1 = info type "
*|      "supported." ;
*|    : is_calconst;
*|    : type = cl2_fixed.t_byte; 
*|    }
*/
const BYTE Ky1979_Mode_09_Info_01_To_08 = 0xf0;

/*
*|    Ky1979_Mode_09_Info_09_To_16 {
*|    : units       = "Bit-Encoded";
*|    : description = "J1979 Mode_09 supported info types. "
*|      "Bit 7 corresponds to info type 9 and bit 0 corresponds to "
*|      "info type 16. 0 = info type not supported and 1 = info type "
*|      "supported." ;
*|    : is_calconst;
*|    : type = cl2_fixed.t_byte;
*|    }
*/
const BYTE Ky1979_Mode_09_Info_09_To_16 = 0x0;


/*
*|    Ky1979_Mode_09_Info_17_To_24 {
*|    : units       = "Bit-Encoded";
*|    : description = "J1979 Mode_09 supported info types. "
*|      "Bit 7 corresponds to info type 17 and bit 0 corresponds to "
*|      "info type 24. 0 = info type not supported and 1 = info type "
*|      "supported." ;
*|    : is_calconst;
*|    : type = cl2_fixed.t_byte;
*|    }
*/
const BYTE Ky1979_Mode_09_Info_17_To_24 = 0x0;

/*
*|    Ky1979_Mode_09_Info_25_To_32 {
*|    : is_calconst;
*|    : description = "J1979 Mode_09 supported info types. "
*|      "Bit 7 corresponds to info type 25 and bit 0 corresponds to "
*|      "info type 32. 0 = info type not supported and 1 = info type "
*|      "supported." ;
*|    : type = cl2_fixed.t_byte; 
*|    : units       = "Bit-Encoded";
*|    }
*/
const BYTE Ky1979_Mode_09_Info_25_To_32 = 0x0;


#pragma section const {SHARED_CAL}

/*
*|    Ka1979_M1_PID_Supported {
*|    : units       = "Bit-Encoded";
*|    : description = "J1979 Mode_09 supported info types. "
*|      "Bit 7 corresponds to info type 25 and bit 0 corresponds to "
*|      "info type 32. 0 = info type not supported and 1 = info type "
*|      "supported." ;
*|    : is_calconst;
*|    : type = cl2_fixed.t_byte;
*|    }
*/
const BYTE Ka1979_M1_PID_Supported[4] = {0xbe, 0x3e, 0xb8, 0x13};

/*
*|    Ka1979_M2_PID_Supported {
*|    : description = "Mode_01 Pids supported ";
*|    : is_calconst;
*|    : elements:units  = "Bit-Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_02_pids;
*|    }
*/
const BYTE Ka1979_M2_PID_Supported[4] = {0x7e, 0x3e, 0x80, 0x01};
#pragma section const {}

/*
*|    Ka1979_M8_TID_Supported {
*|    : description = "Currently supported Test Range for Mode 8 ";
*|    : is_calconst;
*|    : elements:units  = "Bit-Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_08_testRange;
*|    }
*/
const BYTE Ka1979_M8_TID_Supported[Cy1979_Mode_8_TIDs_Sup] =
                 {0x80,0x00,0x00,0x00};

/*
*|    KyC2AP_O2Snsrs_Supported {
*|    : units       = "Bit-Encoded";
*|    : description = " Bit 0 - Bank1Sensor1 "
*|      "Bit 1 - Bank1Sensor2 Bit 2 - Bank1Sensor3 Bit 3 - Bank1Sensor4 "
*|      "Bit 4 - Bank2Sensor1 Bit 5 - Bank2Sensor2 Bit 6 - Bank2Sensor3 "
*|      "Bit 7 - Bank2Sensor4 ";
*|    : is_calconst;
*|    : type = cl2_fixed.t_byte;
*|    }
*/
const BYTE KyC2AP_O2Snsrs_Supported = 0x03;

/*
*|    Ka1979_M6_TestRange_TestID_Supp {
*|    : description = "Calibration data to indicate supporrt or "
*|      "nonsupport of a Test ID ";
*|    : is_calconst;
*|    : elements:units = "Bit-Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_06_TestRange;
*|    }
*/
const BYTE Ka1979_M6_TestRange_TestID_Supp[Cy1979_Mode_6_TestRange] =
                 {0x11, 0x20, 0x00, 0x00};

#pragma section const {SHARED_CAL}

/*
*|    Ka1979_M1_PID20_Thru40_Supp {
*|    : description = " Calibration data to indicate supporrt or "
*|      "nonsupport of a PID by the Powertrain controller "
*|      "0 = PID not supported and 1 = PID supported "
*|      "0th Byte(bit 7) corresponds to PID 21 "
*|      "3rd Byte(bit 0) corresponds to PID 40 ";
*|    : is_calconst;
*|    : elements:units = "Bit-Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_01_PID20_Thru40;
*|    }
*/
const BYTE Ka1979_M1_PID20_Thru40_Supp[Cy1979_PID20_Thru40] =
                 {0x80, 0x07, 0x20, 0x11};

/*
*|    Ka1979_M1_PID40_Thru60_Supp {
*|    : description = " Calibration data to indicate supporrt or "
*|      "nonsupport of a PID by the Powertrain controller "
*|      "0 = PID not supported and 1 = PID supported "
*|      "0th Byte(bit 7) corresponds to PID 41 "
*|      "3rd Byte(bit 0) corresponds to PID 60 ";
*|    : is_calconst;
*|    : elements:units = "Bit-Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_01_PID40_Thru60;
*|    }
*/
const BYTE Ka1979_M1_PID40_Thru60_Supp[Cy1979_PID40_Thru60] =
                 {0x44, 0x00, 0x00, 0x00};

/*
*|    Ka1979_M2_PID20_Thru40_Supp {
*|    : description = " Calibration data to indicate supporrt or "
*|      "nonsupport of a PID by the Powertrain controller "
*|      "0 = PID not supported and 1 = PID supported "
*|      "0th Byte(bit 7) corresponds to PID 21 "
*|      "3rd Byte(bit 0) corresponds to PID 40 ";
*|    : is_calconst;
*|    : elements:units = "Bit-Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_02_PID20_Thru40;
*|    }
*/
const BYTE Ka1979_M2_PID20_Thru40_Supp[Cy1979_PID20_Thru40] =
                 {0x80, 0x00, 0x00, 0x01};
                 
/*
*|    Ka1979_M2_PID40_Thru60_Supp {
*|    : description = " Calibration data to indicate supporrt or "
*|      "nonsupport of a PID by the Powertrain controller "
*|      "0 = PID not supported and 1 = PID supported "
*|      "0th Byte(bit 7) corresponds to PID 41 "
*|      "3rd Byte(bit 0) corresponds to PID 60 ";
*|    : is_calconst;
*|    : elements:units = "Bit-Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_02_PID40_Thru60;
*|    }
*/
const BYTE Ka1979_M2_PID40_Thru60_Supp[Cy1979_PID40_Thru60] =
                 {0x40, 0x00, 0x00, 0x00};


#pragma section const {}

/*
*|   KySYST_CALIBRATION_FILE_PART_NR {
*|     : is_calconst;
*|     : description =" This is the production part number for "
*| "the calibation part. "
*| "Value To Calibrate Out: not applicable "
*| "Engineering Range: any hex value; enter the ASCII code for any values "
*| "which must appear as  ASCII in the keyword mode 09 ID 04 message "
*| "Resolution: na ";
*|     : type = cl2_fixed.t_ubyte;
*|     : units = "count";
*|   }
*| 
*/

const T_COUNT_BYTE KySYST_CALIBRATION_FILE_PART_NR[] =
                   {0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38};



#pragma section const {SHARED_CAL}
/*
*|    Ka1979_M5_TestRange_00Thru80 {
*|    : description = " Calibration data to indicate support or "
*|      "non support of Test ID's in the give test Range. The test ranges "
*|      "supported are 0x00, 0x20, 0x40, 0x60 & 0x80, each group of four "
*|      "bytes of calibration data represent supported Test ID's in the "
*|      "given range respectively. ";
*|    : is_calconst;
*|    : elements:units = "Bit_Encoded";
*|    : elements:type = cl2_fixed.t_byte;
*|    : annotation = cl2_anns.mode_05_TestID_Supported;
*|    }
*| }
*/

const BYTE Ka1979_M5_TestRange_00Thru80[Cy1979_Mode_5_TestRange] =
                 {0x3C, 0x00, 0x00, 0x01, /* Test Range 0x00          */
                  0x00, 0x00, 0x00, 0x01, /* Test Range 0x20          */
                  0x00, 0x00, 0x00, 0x01, /* Test Range 0x40          */
                  0x00, 0x01, 0x80, 0x01, /* Test Range 0x60          */
                  0x80, 0x00, 0x00, 0x00};/* Test Range 0x80          */

#pragma section const {}
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
 *    - Changed the CALDEF for the CALs in kw2cal
 *
 * March/09/2006 Q.W     mt20u2#47
 * + Support SAE J1979 kw2000 modes
 *  -Add new cal KySYST_CALIBRATION_FILE_PART_NR for J1979 mode 09 support.
 *
 * Agu/18/2006   Jerry.Wu    
 * + error fix
 *  - Change Ka1979_M2_PID_Supported.
 *
\* ============================================================================ */

