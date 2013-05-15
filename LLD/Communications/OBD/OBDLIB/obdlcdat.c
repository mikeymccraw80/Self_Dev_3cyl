/******************************************************************************
 *
 * Filename:          obdlcdat.c
 *
 * Description:       Private constant definitions file
 *                    for OBDL subsystem.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 9999-2008 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#1/csrc/obdlcdat.c/1 %
 * %date_created:  Fri Sep 10 14:29:48 2010 %
 * %version:       1 %
 * %derived_by:    pz0vmh %
 *
 *****************************************************************************/
/******************************************************************************
 *  OBD Lib Service Include Files
 *****************************************************************************/
#include "obdlcdat.h"

/*********************************************************************/

/*            TYPEDEFS AND STRUCTURE DECLARATIONS                    */

/*********************************************************************/


/*********************************************************************/

/*            GLOBAL CONSTANT VARIABLES                              */

/*********************************************************************/

/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 1 and bit 0 corresponds to */

/* info type 8.0 = info type not supported and 1 = info type         */

/* supported.                                                        */

//const BYTE Ky1979_Mode_09_Info_01_To_08 = 0xff;

const BYTE KyDCAN_Mode_09_Info_01_To_08 = 0x55;

/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 9 and bit 0 corresponds to */

/* info type 16.0 = info type not supported and 1 = info type        */

/* supported.                                                        */

//const BYTE Ky1979_Mode_09_Info_09_To_16 = 0x40;

/* ECU NAME: ECM -Engine Control */
const BYTE KyDCAN_ECM_EcuName[ECU_NAME_Size] = { 0x45, 0x43, 0x4D, 0x00,
                                                 0x2D, 0x45, 0x6E, 0x67,
                                                 0x69, 0x6E, 0x65, 0x20,
                                                 0x43, 0x6F, 0x6E, 0x74, 
                                                 0x72, 0x6F, 0x6C, 0x00 };
/* ECU NAME: PCM -Powertrain Crtl */
const BYTE KyDCAN_PCM_EcuName[ECU_NAME_Size] = { 0x50, 0x43, 0x4D, 0x00,
                                                 0x2D, 0x50, 0x6F, 0x77,
                                                 0x65, 0x72, 0x74, 0x72,
                                                 0x61, 0x69, 0x6E, 0x20,
                                                 0x43, 0x74, 0x72, 0x6C };

/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 17 and bit 0 corresponds to*/

/* info type 24.0 = info type not supported and 1 = info type        */

/* supported.                                                        */

//const BYTE Ky1979_Mode_09_Info_17_To_24 = 0x0;



/* this defines the supported info types in case of mode 9 J1979     */

/* message.bit 7 corresponds to info type 25 and bit 0 corresponds to*/

/* info type 32.0 = info type not supported and 1 = info type        */

/* supported.                                                        */

//const BYTE Ky1979_Mode_09_Info_25_To_32 = 0x0;


/* Added for Mode 08                                                  */

/* Test Range currently supported is 0x00, therefore all are          */

/* initialized to 0x00                                                */
#if 0
const BYTE Ka1979_M8_TID_Supported[Cy1979_Mode_8_TIDs_Sup] =

                 {0x80,0x00,0x00,0x00};
#endif
/* This gives the o2 sensors supported by the application as          */

/* such. This is required for mode 5 and this is irrespective of the  */

/* mode 5, test IDs supported. Currently Isuzu2000 supports           */

/* Bank1Sensor1 and Bank2Sensor1.                                     */

/* Bit 0 - Bank1Sensor1; Bit 1 - Bank1Sensor2; Bit 2 - Bank1Sensor3   */

/* Bit 3 - Bank1Sensor4; Bit 4 - Bank2Sensor1; Bit 5 - Bank2Sensor2   */

/* Bit 6 - Bank2Sensor3; Bit 7 - Bank2Sensor4;                        */
#if 0
const BYTE KyC2AP_O2Snsrs_Supported = 0x03; /*not used*/

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

const BYTE Ka1979_M6_TestRange_TestID_Supp[Cy1979_Mode_6_TestRange] =

                 {0x12, 0x40, 0x00, 0x00};

/* Added for mode 1 and mode 2*/
/* Following is a calibration parameter such that each bit indicates  */
/* support or non-support of a PID by the Powertrain controller       */
/* 0 = PID not supported and 1 = PID supported                        */
/* 0th Byte(bit 7) corresponds to PID 21                              */
/* 3rd Byte(bit 0) corresponds to PID 40                              */
const BYTE Ka1979_M1_PID_Supported[Cy1979_PID01_Thru20] = 
                 {0xFE, 0x3E, 0xB8, 0x13};

const BYTE Ka1979_M2_PID_Supported[Cy1979_PID01_Thru20] = 
	          {0x7E, 0x3E, 0x80, 0x01};

const BYTE Ka1979_M1_PID20_Thru40_Supp[Cy1979_PID21_Thru40] =
                 {0x80, 0x07, 0xA0, 0x11};

const BYTE Ka1979_M1_PID40_Thru60_Supp[Cy1979_PID21_Thru40] =
                 {0xFA, 0xD8, 0x00, 0x00};

const BYTE Ka1979_M2_PID20_Thru40_Supp[Cy1979_PID21_Thru40] =
                 {0x00, 0x04, 0x20, 0x01};

const BYTE Ka1979_M2_PID40_Thru60_Supp[Cy1979_PID21_Thru40] =
                 {0x7A, 0xD0, 0x00, 0x00};

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

const BYTE Ka1979_M5_TestRange_00Thru80[Cy1979_Mode_5_TestRange] =

                 {0x3C, 0x00, 0x00, 0x01, /* Test Range 0x00          */
                  0x00, 0x00, 0x00, 0x01, /* Test Range 0x20          */
                  0x00, 0x00, 0x00, 0x01, /* Test Range 0x40          */
                  0x00, 0x01, 0x80, 0x01, /* Test Range 0x60          */
                  0x80, 0x00, 0x00, 0x00};/* Test Range 0x80          */

#endif
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* tci_pt3#1.1.1
*       080110 VP  6563 Added CsDCAN_ETCI_Pct_PERCENTa
*                             CsDCAN_ETCI_Pct_PERCENT_MULTb.
*                       Changed CsC2SC_MAP256_U_Sensor_O2_VOLT 
*                       higher limit of range from 1.11 to 5
* tci_pt3#1.1.2
*      080403  VP  6833 Added CsDCAN_MAP256_AIRFUELRATIO.
*                       Changed CsC2SC_MAP256_Pct_EGR_DutyCycle_PERCENTa 
*                       higher limit of range from 100 to 99.609375
*
*******************************************************************************/
