/******************************************************************************
 *
 * Filename:          filenvmd.c
 *
 * Description:       This file contains all NV RAM variable definitions for
 *                    FILE system.
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
 * Copyright 1998-2012, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tcb_pt1#4/csrc/filenvmd.c/kok_pt2#20.1.1.1.1.1.1 %
 * %date_created:  Fri Jun  1 13:53:39 2012 %
 * %version:       kok_pt2#20.1.1.1.1.1.1 %
 * %derived_by:    pz87t9 %
 *
 *****************************************************************************/

/*****************************************************************************
 *  System Config Include Files
 *****************************************************************************/
#include "io_type.h"
#include "fileftyp.h"

/*****************************************************************************
 *  Sub System Include Files
 *****************************************************************************/
#include "filenvmd.h"


#pragma section DATA " " ".nc_nvram"

/******************************************************************************
*  Variable Definitions
*******************************************************************************/


volatile BYTE NcFILE_FLASH_VIN_Update;
#if CcFILE_EE_VIN_Size > 0
BYTE NaFILE_FLASH_VIN[CcFILE_EE_VIN_Size];
#endif

#pragma section DATA " " ".mfg"
TsFILE_EE_ManufactData NsFILE_NVM_EE_ManufactData;

#pragma section DATA " " ".bss"

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.2   980511 sn  0318 Created module.
* 1.2   980511 blt 0486 Merge offline partition node 024 into Lecc node 278
* 1.3   980528 sn  0529 Moved NbFILE_NVM_OrderlyShtdwnOccurred to filenvmc.c.
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   000714 woz 0883 Merged modifications implemented between Core (EMSDC1a)
*                        nodes 32 and 53:
*       000323 kan 0678 Merge Daewoo RSM's. TEMPORARY NVM variables placed
*                        here for EEPROM emulation
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
* 4.1.1 031107 jyz 3312 Added NuFILE_CVN_TRN, NbFILE_CVN_TRN_Available
* 6.0   031210 caw 3138 Merged objects.
* 7.0   040314 caw 3759 Added: NcFILE_FLASH_VIN_Update
*                              NaFILE_FLASH_VIN
* 8.0   040604 rag GMDT Modified to eliminate CcFILE_EE_VIN_Size == 0 error
* 7.1.1
*       040612  pd 3927 Making Code Cosmic Compatible
* 9.0   040701 caw -BM- Merged
* 10.0  041117 kan -BM- Merge versions:
*                        9.0
*                        tci_pt3#9
* 9.1.1 041202 jyz 4612 Added NySYST_MainSW_Cal_ID
* 11    041206 wei -BM- Merged 'filenvmd.c-10' with 'filenvmd.c-9.1.1'.
* 12    050124 jyz 4681 Added NsFILE_SCU_Cause_Of_Reset
*                             NyFILE_SCU_Cause_Of_Reset_Address
*                             NwFILE_SCU_Reset_Counter
*                             NyFILE_SCU_Reset_Register_Copy
* 13.0  060327 caw 5606 Added: NsFILE_EE_ID
* 14    070326 as  6243 Included TsFILE_EE_ManufactData NsFILE_NVM_EE_ManufactData
*                       in SECTION_NVM_DATA
* 17    080320 tjd 6560 Added: NbFILE_TriggerOccured
*                              NbFILE_RPM_ShootUpOccured
* kok_pt2#19
*       090602 woz 7672 Removed obsolete SECTION_NVM_DATA / SECTION_END
*                        definitions from around NsFILE_NVM_EE_ManufactData.
* kok_pt2#20
*       090617 woz 7672 Restored SECTION_NVM_DATA / SECTION_END definitions
*                        around NsFILE_NVM_EE_ManufactData.
* tci_pt3#20.1.1
*       100720 SMM 7107 Deleted the variables under the compiler switch
*                       'XeCOND_SYST_CONTROLLER_DIAG_TYPE'.
* tci_pt3#20.1.1.1.1
*       110624 SMM 9565 Removed the volatile qualifier for the variables
*                       'NaFILE_FLASH_VIN', 'NsFILE_NVM_EE_ManufactData',
*                       'NsFILE_EE_ID' and 'NwFILE_NVM_Checksum'.
* kok_pt2#20.1.1.1.1.1.1
*       120524 cjk 0081 Update includes.
*******************************************************************************/
