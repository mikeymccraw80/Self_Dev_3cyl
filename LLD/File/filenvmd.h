#ifndef FILENVMD_H
#define FILENVMD_H
/******************************************************************************
 *
 * Filename:          filenvmd.h
 *
 * Description:       This header file contains all public declarations for
 *                    module filenvmd.c.
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
 * Copyright 1998-2011, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tcb_pt1#4/incl/filenvmd.h/tci_pt3#10.6.1.2 %
 * %date_created:  Tue Jun 21 17:58:26 2011 %
 * %version:       tci_pt3#10.6.1.2 %
 * %derived_by:    fzdn3k %
 *
 *****************************************************************************/

/*****************************************************************************
 * System Include Files
 *****************************************************************************/
#include "io_type.h"
#include "fileftyp.h"


extern volatile BYTE NcFILE_FLASH_VIN_Update;
#if CcFILE_EE_VIN_Size > 0
extern BYTE NaFILE_FLASH_VIN[CcFILE_EE_VIN_Size];
#endif

#pragma section DATA " " ".mfg"
extern TsFILE_EE_ManufactData NsFILE_NVM_EE_ManufactData;

#pragma section DATA " " ".bss"

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.2   980511 sn  0318 Created module.
* 1.2   980511 blt 0486 Merge offline partition node 024 into Lecc node 278
* 1.3   980528 sn  0529 Moved NbFILE_NVM_OrderlyShtdwnOccurred to filenvmc.h.
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   000714 woz 0883 Merged modifications implemented between Core (EMSDC1a)
*                        nodes 32 and 53:
*       000323 kan 0678 Merge Daewoo RSM's. TEMPORARY NVM variables placed
*                        here for EEPROM emulation.
* 1.3   010723 jbn 1420 Replaced CcSYST_MAXCYLS,KyVIOS_NumberOfCylinders,
*                        and GetVIOS_NumberOfCylinders with
*                        CcSYST_NUM_OF_CYLINDERS
* 2.0   030825 jyz 3032 Added NuFILE_CVN
* 3.0   030903 jyz 3032 Added NbFILE_CVN_Available
* 4.0   030829 rmn 3070 Added NsFILE_FlightRecorderBuffer, NbFILE_StallOccured,
*                       NcFILE_AfterStallFrameCntr
* 5.0   031022 caw 3138 Removed: NcFILE_TECD_SampleCntr
*                                NaFILE_TECD_FactorTotals
*
* 4.1.1 031107 jyz 3312 Added NuFILE_CVN_TRN, NbFILE_CVN_Available_TRN
* 6.0   031210 caw 3138 Merged objects.
* 8.0
*       040612  pd 3927 Making Code Cosmic Compatible
* 9.0   041117 kan -BM- Merge versions:
*                        8.0
*                        tci_pt3#9
* 8.1.1 041202 jyz 4612 Added NySYST_MainSW_Cal_ID
* 10.1  041206 wei -BM- Merged 'filenvmd.h-9' with 'filenvmd.h-8.1.1'.
* 10.2  050124 jyz 4681 Added NsFILE_SCU_Cause_Of_Reset
*                             NyFILE_SCU_Cause_Of_Reset_Address
*                             NwFILE_SCU_Reset_Counter
*                             NyFILE_SCU_Reset_Register_Copy
* 10.3  070130 gps -BM- CORE : Include Header Files Optimization.
*                       Installed non-functional changes.
* 10.6  080320 tjd 6560 Added: NbFILE_TriggerOccured
*                              NbFILE_StallOccured
* tci_pt3#10.6.1.1
*       100720 SMM 7107 Deleted the variables under the compiler switch
*                       'XeCOND_SYST_CONTROLLER_DIAG_TYPE'.
* tci_pt3#10.6.1.2
*       100624 SMM 9565 Removed the volatile qualifier from the
*                       variable 'NwFILE_NVM_CheckSum'.
*
******************************************************************************/