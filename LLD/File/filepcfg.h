#ifndef FILEPCFG_H
#define FILEPCFG_H
/******************************************************************************
 *
 * Filename:          filepcfg.h
 *
 * Description:       This file contains internal FILE configuration definitions.
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
 * Copyright 2003-2012, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     ctc_pt3#41/incl/filepcfg.h/5 %
 * %date_created:  Fri Apr 25 14:33:28 2014 %
 * %version:       5 %
 * %derived_by:    dzrpmq %
 *
 *****************************************************************************/

/******************************************************************************
 *  System Include Files
 *****************************************************************************/
#include "io_type.h"

/******************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h"

/******************************************************************************
 *  FILE Hardware Specific Switches (user configurable)
 *****************************************************************************/
#define CeFILE_SYST_ACTUAL_EE     0
#define CeFILE_SYST_EMULATED_EE   1

#define CeHWIO_NVRAM_BATTERY_BACKED   0
#define CeHWIO_NVRAM_EMULATED_EEPROM  1

#define XeHWIO_NVRAM_TYPE CeHWIO_NVRAM_EMULATED_EEPROM

#define XeFILE_SYST_EEPROM_TYPE   CeFILE_SYST_EMULATED_EE

/******************************************************************************
 *  FILE Mode Specific Switches (user configurable)
 *****************************************************************************/
/* Settings for VIN diagnostic enablement */
#define CeFILE_VIN_DIAG_NOT_ACTIVE 0
#define CeFILE_VIN_DIAG_ACTIVE     1

#define XeFILE_SUBS_EMUL_EE_VIN_DIAG CeFILE_VIN_DIAG_NOT_ACTIVE

/* Settings for VIN writing enablement */
#define CeFILE_WRITE_VIN_MANY 0
#define CeFILE_WRITE_VIN_ONCE 1

/* Settings for CMC 2nd VIN */
#define CeFILE_USE_CMC_2nd_Set_VIN 1

#define XeFILE_SUBS_EMUL_EE_VIN_WRITE CeFILE_WRITE_VIN_MANY

/* Settings for calibration options */
#define XeFILE_SYST_CAL_BOOT_BRAINDEAD_OPT CeSYST_AVAILABLE
#define XeFILE_SYST_CAL_DIAG_DATA_ID_OPT   CeSYST_AVAILABLE
#define XeFILE_SYST_CAL_SYSTEM_NAME_OPT    CeSYST_AVAILABLE

/******************************************************************************
 *  Subsystem Specific defines (user configurable)
 *****************************************************************************/
#define CcFILE_EE_Block_Status_Size                 (0)
#define CcFILE_EE_HexBaseModelNumber_Size           (0)
#define CcFILE_EE_HexEndModelNumber_Size            (4)
#define CcFILE_EE_Broadcast_Code_Size               (4)
#define CcFILE_EE_VehMfgCalIdentityNumber_Size      (0)
#define CcFILE_EE_CalibrationRepairShopCode_Size    (0)
#define CcFILE_EE_CalibrationProgrammingDate_Size   (0)
#define CcFILE_EE_ReservedCalProgrammingDate_Size   (0)
#define CcFILE_EE_SupplHexEndModelNumber_Size       (0)
#define CcFILE_EE_VIN_Size                          (17)
#define CcFILE_EE_VIN_Expansion_Size                (12)
#define CcFILE_EE_SupplECU_HardwareNumber_Size      (0)
#define CcFILE_EE_SystemNameOrVehEngType_Size       (0)
#define CcFILE_EE_RepairShopCode_Size               (10)
#define CcFILE_EE_ProgrammingDate_Size              (4)
#define CcFILE_EE_InstrumentationDatasetID_Size     (0)
#define CcFILE_EE_Odometer_Update_Locked_Size       (1)
#define CcFILE_EE_Seed_Size                         (0)
#define CcFILE_EE_Key_Size                          (0)
#define CcFILE_EE_ManufacturesEnableCounter_Size    (1)
#define CcFILE_EE_CrankShaftAdaptive_Size           (16)
#define CcFILE_EE_CrankShaftAdaptiveCntr_Size       (1)
#define CcFILE_EE_Mfg_Traceability_Size             (0)
#define CcFILE_EE_Auto_Detect_DWMC_Immo_Size        (0)
#define CcFILE_EE_PIC_Immo_VIN_Size                 (0)
#define CcFILE_EE_PIC_Immo_Status_Size              (0)
#define CcFILE_EE_Vehicle_Specific_Data_Size        (0)
#define CcFILE_EE_User_Password_Size                (0)
#define CcFILE_EE_Key_1_IDE_Size                    (0)
#define CcFILE_EE_Key_2_IDE_Size                    (0)
#define CcFILE_EE_Key_3_IDE_Size                    (0)
#define CcFILE_EE_Key_4_IDE_Size                    (0)
#define CcFILE_EE_LimpHome_Starts_Tester_Size       (0)
#define CcFILE_EE_Twice_Ign_Seq_Size                (0)
#define CcFILE_EE_Key_Learnt_Size                   (0)
#define CcFILE_EE_Transponder_Fault_Size            (0)
#define CcFILE_EE_Immob_EMS_Status_Size             (0)
#define CcFILE_EE_Password_Status_Size              (0)
#define CcFILE_EE_LockByTimer_Size                  (0)
#define CcFILE_EE_Wrong_Inputs_Passwd_Teach_Size    (0)
#define CcFILE_EE_Wrong_VSD_Key_Teach_Size          (0)
#define CcFILE_EE_Wrong_PassWord_LimpHome_Size      (0)
#define CcFILE_EE_Wrong_VSD_Neutral_Size            (0)
#define CcFILE_EE_Auto_Detect_DWMC_ABS_Size         (0)
#define CcFILE_EE_VIN_HighByte_Size                 (0)
#define CcFILE_EE_VIN_LowByte_Size                  (0)
#define CcFILE_EE_VTDS_Config_Size                  (0)
#define CcFILE_EE_VTDS_Last_RandomNumber_Size       (0)
#define CcFILE_EE_VTDS_Polynomial_AsLongword_Size   (0)
#define CcFILE_EE_COA_Factor_Size                   (0)
#define CcFILE_EE_RandomNumberPolynomial_Size       (0)
#define CcFILE_EE_SecurityCode_Size                 (8)
#define CcFILE_EE_RandomNumberBuffer_Size           (0)
#define CcFILE_EE_SecretKey_Size                    (20)
#define CcFILE_EE_New_Vehicle_Start_Cntr_Size       (0)
#define CcFILE_EE_SecCodeEntryCntr_Size             (0)
#define CcFILE_EE_SecurityBlockAccess_Size          (0)
#define CcFILE_EE_Dynamic_Status_Size               (0)
#define CcFILE_EE_XmsnOilLifeMonitor_Size           (0)
#define CcFILE_EE_AutoLearnVSS_Size                 (0)
#define CcFILE_EE_AutoLearnPSS_Size                 (0)
#define CcFILE_EE_AutoLearnChassisCtrl_Size         (0)
#define CcFILE_EE_AutoLearnCruz_Size                (0)
#define CcFILE_EE_VIN_Update_Size                   (1)
#define CcFILE_EE_DriveLineType_Size                (0)
#define CcFILE_EE_DriveLineTypeLrnd_Size            (0)
#define CcFILE_EE_NumberOfWarmupCycles_Size         (0)
#define CcFILE_EE_GMTargetVehicle_Size              (0)
#define CcFILE_EE_DynamTireCirc_Size                (0)
#define CcFILE_EE_OctSelSwitch_Size                 (0)
#define CcFILE_EE_EngPerfIdent_Size                 (14)
#define CcFILE_EE_FuelConsCalcCorrFctr_Size         (0)
#define CcFILE_EE_VehCANConfig_Size                 (0)
#define CcFILE_EE_XMLDataFilePN_Size                (0)
#define CcFILE_EE_XMLDataFileAC_Size                (0)
#define CcFILE_EE_BootSWPNAC_Size                   (0)
#define CcFILE_EE_XMLConfCompIdent_Size             (0)
#define CcFILE_EE_SWModIdent2AC_Size                (0)
#define CcFILE_EE_EndModelPNAC_Size                 (0)
#define CcFILE_EE_BaseModelPNAC_Size                (0)
#define CcFILE_EE_ImmoPtPreRelease_Size             (0)
#define CcFILE_EE_ImmoPtSecretKey_Size              (0)
#define CcFILE_EE_ImmoPtGenericInfo_Size            (0)
#define CcFILE_EE_ImmoSecretInfo_Size               (0)
#define CcFILE_EE_ImmoSecureCode_Size               (0)
#define CcFILE_EE_ImmoSecureCodeCtr_Size            (0)
#define CcFILE_EE_ImmoSecureCodeRstCtr_Size         (0)
#define CcFILE_EE_OdoVINvalue_Size                  (17)
#define CcFILE_EE_OdoVINwritten_Size                (1)
#define CcFILE_EE_VINWrittenCount_Size              (0)
#define CcFILE_EE_PrevRepairShopCode_Size           (0)
#define CcFILE_EE_GreenEngCompComplete_Size         (0)
#define CcFILE_EE_CalibrationData_Size              (64)
#define CcFILE_EE_TDC_CrankShaftAdaptive_Size       (0)
#define CcFILE_EE_Odometer_Size                     (4)
#define CcFILE_EE_ReservedForCustomer_Size          (40)
#define CcFILE_EE_Reserved1_Size                    (181)  //Mfg Reserved Data
#define CcFILE_EE_Reserved2_Size                    (0)  //Mfg Reserved Data

#endif /* FILEPCFG_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
* 1.0   031022 caw 3138 Created file.
* 2.0   031210 caw 3138 Added: CcFILE_EE_AutoLearnCruz_Size
* 3.0   031211 caw 3262 Updated CcFILE_EE_COA_Factor_Size.
* 4.0   031212 caw 3262 Updated CcFILE_EE_CrankShaftAdaptiveCntr_Size
*
*******************************************************************************
* GMDAT Revision History
*
* 1.0   040319 kan -BM- GMDAT Configuration
* 1.1.1 041001 caw 4548 Added compile-time option for VIN diagnostic and
*                        VIN writing.
* 2.0   040923 caw -BM- Added configuration items for EEPROM:
*              caw 3759 Added new immobilizer parameters to EMS Mnufacturing
*                        EEPROM: CcFILE_EE_PIC_Immo_VIN_Size
*                                CcFILE_EE_PIC_Immo_Status_Size
*                                CcFILE_EE_Vehicle_Specific_Data_Size
*                                CcFILE_EE_User_Password_Size
*                                CcFILE_EE_Key_1_IDE_Size
*                                CcFILE_EE_Key_2_IDE_Size
*                                CcFILE_EE_Key_3_IDE_Size
*                                CcFILE_EE_Key_4_IDE_Size
*                                CcFILE_EE_LimpHome_Starts_Tester_Size
*                                CcFILE_EE_Twice_Ign_Seq_Size
*                                CcFILE_EE_Key_Learnt_Size
*                                CcFILE_EE_Transponder_Fault_Size
*                                CcFILE_EE_Immob_EMS_Status_Size
*                                CcFILE_EE_Password_Status_Size
*                                CcFILE_EE_LockByTimer_Size
*                                CcFILE_EE_Wrong_Inputs_Passwd_Teach_Size
*                                CcFILE_EE_Wrong_VSD_Key_Teach_Size
*                                CcFILE_EE_Wrong_PassWord_LimpHome_Size
*                                CcFILE_EE_Wrong_VSD_Neutral_Size
*                       Added new manufacturing data interfaces to EMS
*                        Manufacturing EEPROM:
*                                CeFILE_EE_VehMfgCalIdentityNumber
*                                CeFILE_EE_SupplHexEndModelNumber
*                                CeFILE_EE_VehMfgHardwareNumber
*                                CeFILE_EE_SupplECU_HardwareNumber
*                                CeFILE_EE_SystemNameOrVehEngType
*                                CeFILE_EE_InstrumentationDatasetID
*                                CeFILE_EE_VIN_Update
*              caw 3922 Added new manufacturing data parameters to EMS
*                        Manufacturing EEPROM:
*                                CeFILE_EE_DriveLineType
*                                CeFILE_EE_DriveLineTypeLrnd
*              caw 3922 Enabble drive line auto detects.
*              ban 4252 Modified size of CcFILE_EE_VehMfgCalIdentityNumber_Size
* 5.0   041101 caw 4523 Modified configuration items for GMDAT.
*                  4520 Added: XeFILE_SYST_CAL_BOOT_BRAINDEAD_OPT
*                              XeFILE_SYST_CAL_DIAG_DATA_ID_OPT
*                              XeFILE_SYST_CAL_SYSEM_NAME_OPT
* 6.0   041108 caw -BM- Merged 5 and 1.1.1
* 4.1.1 041101 caw 4520 Added: XeFILE_SYST_CAL_BOOT_BRAINDEAD_OPT
*                              XeFILE_SYST_CAL_DIAG_DATA_ID_OPT
*                              XeFILE_SYST_CAL_SYSTEM_NAME_OPT
* 7.0   041108 caw -BM- Merged 6 and 4.1.2
* 8.0   060209 caw 5519 Added: CcFILE_EE_CalibrationRepairShopCode_Size
*                              CcFILE_EE_CalibrationProgrammingDate_Size
* T300_ECM.1.1
*       080709 wj  7072 Added: XeHWIO_NVRAM_TYPE
* T300_ECM.2.0
*       080619 KN  7052 Added CcFILE_EE_NumberOfWarmupCycles_Size
* T300_ECM.3
*       080806 KN  ---- Merged from 'filepcfg.h~T300_ECM.2:incl:tcb_pt1#36'
*                       and 'filepcfg.h~T300_ECM.1.1:incl:tcb_pt1#36'
* 1.1.1 071101 mat 6189 Changed CcFILE_EE_VTDS_Last_RandomNumber_Size to (0) to
*                        eliminate it storage in manufacturing EEPROM.
* 1.1.2 071217 mat -BM- Changed CcFILE_EE_VTDS_Last_RandomNumber_Size to (4) to
*                        add the storage of Immob random key back into MFG EEPROM.
* tci_pt3#1.1.3
*       080116 VP  6563 Added CcFILE_EE_GMTargetVehicle_Size,
*                             CcFILE_EE_DynamTireCirc_Size,
*                             CcFILE_EE_OctSelSwitch,
*                             CcFILE_EE_EngPerfIdent_Size,
*                             CcFILE_EE_FuelConsCalcCorrFctr_Size.
*                       Modified CcFILE_EE_COA_Factor_Size to 1.
* tci_pt3#1.1.3.1.1
*      080411 abh 6832 Modified  CcFILE_EE_COA_Factor_Size to 2
* tci_pt3#1.1.4
*       080401 VP 6833 Added CcFILE_EE_VehCANConfig_Size
*                            CcFILE_EE_XMLDataFilePN_Size
*                            CcFILE_EE_XMLDataFileAC_Size
*                            CcFILE_EE_BootSWPNAC_Size
*                            CcFILE_EE_SWModIdent1AC_Size
*                            CcFILE_EE_SWModIdent2AC_Size
*                            CcFILE_EE_EndModelPNAC_Size
*                            CcFILE_EE_BaseModelPNAC_Size
*                            CcFILE_EE_ImmoPtPreRelease_Size
*                            CcFILE_EE_ImmoPtSecretKey_Size
*                            CcFILE_EE_ImmoPtGenericInfo_Size
*                            CcFILE_EE_ImmoSecretInfo_Size
*                            CcFILE_EE_ImmoSecureCode_Size
*                            CcFILE_EE_ImmoSecureCodeCtr_Size
*                            CcFILE_EE_ImmoSecureCodeRstCtr_Size
*                      Changed length of CcFILE_EE_COA_Factor_Size to 2 bytes.
* tci_pt3#1.1.3.1.3
*      080507 VP  6834 Added CcFILE_EE_OdoVINvalue_Size,
*                            CcFILE_EE_OdoVINwritten_Size.
* tci_pt3#1.1.3.1.4
*      080609 VP  7111 Added CcFILE_EE_VINWrittenCount_Size,
*                            CcFILE_EE_PrevRepairShopCode_Size.
*                      Replaced EEPROM interface for SWModIdent1AC by
*                      XMLConfCompIdent.
* T300_ECM.1.2
*       080810 me  7269 T300-J300 GMLAN Commonization: Updated CORE with all
*                       GMLAN related changes from Offline J300 Project
* kok_pt2#T300_ECM.5
*       090807 rbg 8125 Added #define CcFILE_EE_GreenEngCompComplete_Size
* kok_pt2#T300_ECM.6
*       100802  JP 8899 Added: CcFILE_EE_TDC_CrankShaftAdaptive_Size
*******************************************************************************
* Revision History (restart):
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* kok_pt2#MT62P1_NA.2
*       110626  me 9565 Created file for MT62P1_NA configuration.
*******************************************************************************
* Revision History (restart):
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     111105  me 9760 Created file for MT62P1_TURBO configuration.
* 2     120524 cjk 0081 Update includes.
*
******************************************************************************/
