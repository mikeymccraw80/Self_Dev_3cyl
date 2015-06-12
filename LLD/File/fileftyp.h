#ifndef FILEFTYP_H
#define FILEFTYP_H
/******************************************************************************
 *
 * Filename:          fileftyp.h
 *
 * Description:       The header for the FILE sub-system global types.
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
 * Copyright 2003-2011, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tcb_pt1#1/incl/fileftyp.h/kok_pt2#17 %
 * %date_created:  Wed Apr 18 13:44:07 2012 %
 * %version:       kok_pt2#17 %
 * %derived_by:    zzmkdw %
 *
 *****************************************************************************/

/******************************************************************************
 *  System Include Files
 *****************************************************************************/
#include "io_type.h"  /* XeSYST_FLIGHT_RECORDER_OPTION */
#include "t_gentypes.h"


/******************************************************************************
 *  Global Config Type Include File
 *****************************************************************************/
#include "filepcfg.h"

/******************************************************************************
 * Global Constant and Macros
 *****************************************************************************/
#define GetFILE_VarSizeInBytes(x)    (sizeof(x))
#define CpFILE_EEPROM_END_OF_LIST    ((void *) 0)
#define CcFILE_CAL_ID_SIZE           16

/******************************************************************************
 *  Sub-system Private Constants
 *****************************************************************************/
#define CwFILE_EE_SWCALPN_Size     (8)

/******************************************************************************
 *  Tasking complier 2.X specific Byte Alignment
 *****************************************************************************/
// #if ( config_Compiler_Vendor == option_TASKING_2_0)
// #define PROCALGN __align(1)
// #else
#define PROCALGN 
// #endif

/******************************************************************************
 * Global Enums and Types
 *****************************************************************************/
typedef enum
{
  CeFILE_EE_Block_Status,
  CeFILE_EE_HexBaseModelNumber,
  CeFILE_EE_HexEndModelNumber,
  CeFILE_EE_Broadcast_Code,
  CeFILE_EE_VehMfgCalIdentityNumber,
  CeFILE_EE_CalibrationRepairShopCode,
  CeFILE_EE_CalibrationProgrammingDate,
  CeFILE_EE_ReservedCalProgrammingDate,
  CeFILE_EE_SupplHexEndModelNumber,
  CeFILE_EE_VIN,
  CeFILE_EE_VIN_Expansion,
  CeFILE_EE_VehMfgHardwareNumber,
  CeFILE_EE_SupplECU_HardwareNumber,
  CeFILE_EE_SystemNameOrVehEngType,
  CeFILE_EE_RepairShopCode,
  CeFILE_EE_ProgrammingDate,
  CeFILE_EE_InstrumentationDatasetID,
  CeFILE_EE_Odometer_Update_Locked,
  CeFILE_EE_Seed,
  CeFILE_EE_Key,
  CeFILE_EE_ManufacturesEnableCounter,
  CeFILE_EE_CrankShaftAdaptive,
  CeFILE_EE_CrankShaftAdaptiveCntr,
  CeFILE_EE_Mfg_Traceability,
  CeFILE_EE_Auto_Detect_DWMC_Immo,
  CeFILE_EE_PIC_Immo_VIN,
  CeFILE_EE_PIC_Immo_Status,
  CeFILE_EE_Vehicle_Specific_Data,
  CeFILE_EE_User_Password,
  CeFILE_EE_Key_1_IDE,
  CeFILE_EE_Key_2_IDE,
  CeFILE_EE_Key_3_IDE,
  CeFILE_EE_Key_4_IDE,
  CeFILE_EE_LimpHome_Starts_Tester,
  CeFILE_EE_Twice_Ign_Seq,
  CeFILE_EE_Key_Learnt,
  CeFILE_EE_Transponder_Fault,
  CeFILE_EE_Immob_EMS_Status,
  CeFILE_EE_Password_Status,
  CeFILE_EE_LockByTimer,
  CeFILE_EE_Wrong_Inputs_Passwd_Teach,
  CeFILE_EE_Wrong_VSD_Key_Teach,
  CeFILE_EE_Wrong_PassWord_LimpHome,
  CeFILE_EE_Wrong_VSD_Neutral,
  CeFILE_EE_Auto_Detect_DWMC_ABS,
  CeFILE_EE_VIN_HighByte,
  CeFILE_EE_VIN_LowByte,
  CeFILE_EE_VTDS_Config,
  CeFILE_EE_VTDS_Last_RandomNumber,
  CeFILE_EE_VTDS_Polynomial_AsLongword,
  CeFILE_EE_COA_Factor,
  CeFILE_EE_RandomNumberPolynomial,
  CeFILE_EE_SecurityCode,
  CeFILE_EE_RandomNumberBuffer,
  CeFILE_EE_SecretKey,
  CeFILE_EE_New_Vehicle_Start_Cntr,
  CeFILE_EE_SecCodeEntryCntr,
  CeFILE_EE_SecurityBlockAccess,
  CeFILE_EE_Dynamic_Status,
  CeFILE_EE_XmsnOilLifeMonitor,
  CeFILE_EE_AutoLearnVSS,
  CeFILE_EE_AutoLearnPSS,
  CeFILE_EE_AutoLearnChassisCtrl,
  CeFILE_EE_AutoLearnCruz,
  CeFILE_EE_VIN_Update,
  CeFILE_EE_DriveLineType,
  CeFILE_EE_DriveLineTypeLrnd,
  CeFILE_EE_Smartra3_Status,
  CeFILE_EE_Key_5_IDE,
  CeFILE_EE_Key_6_IDE,
  CeFILE_EE_Key_7_IDE,
  CeFILE_EE_Key_8_IDE,
  CeFILE_EE_Smartra3_SEK,
  CeFILE_EE_GMTargetVehicle,
  CeFILE_EE_DynamTireCirc,
  CeFILE_EE_OctSelSwitch,
  CeFILE_EE_EngPerfIdent,
  CeFILE_EE_FuelConsCalcCorrFctr,
  CeFILE_EE_VehCANConfig,
  CeFILE_EE_XMLDataFilePN,
  CeFILE_EE_XMLDataFileAC,
  CeFILE_EE_BootSWPNAC,
  CeFILE_EE_XMLConfCompIdent,
  CeFILE_EE_SWModIdent2AC,
  CeFILE_EE_EndModelPNAC,
  CeFILE_EE_BaseModelPNAC,
  CeFILE_EE_ImmoPtPreRelease,
  CeFILE_EE_ImmoPtSecretKey,
  CeFILE_EE_ImmoPtGenericInfo,
  CeFILE_EE_ImmoSecretInfo,
  CeFILE_EE_ImmoSecureCode,
  CeFILE_EE_ImmoSecureCodeCtr,
  CeFILE_EE_ImmoSecureCodeRstCtr,
  CeFILE_EE_OdoVINvalue,
  CeFILE_EE_OdoVINwritten,
  CeFILE_EE_NumberOfWarmupCycles,
  CeFILE_EE_VINWrittenCount,
  CeFILE_EE_PrevRepairShopCode,
  CeFILE_EE_GreenEngCompComplete,
  CeFILE_EE_TDC_CrankShaftAdaptive,
  CeFILE_EE_EntryMax
}  TeFILE_EE_ManufactDataEntry;

typedef enum
{
  CeFILE_NVM_NoAction,
  CeFILE_NVM_Read,
  CeFILE_NVM_Write,
  CeFILE_NVM_ReadWrite
} TeFILE_STORAGE_TYPE;

typedef struct
{
  void                *SpFILE_EEPROM_StartOfData;
  WORD                SwFILE_EEPROM_SizeOfData;
  TeFILE_STORAGE_TYPE SeFILE_EEPROM_StorageType;
} TsFILE_EEPROM;
typedef TsFILE_EEPROM TsFILE_EEPROM_T;

typedef struct
{
  TsFILE_EEPROM *SaFILE_EEPROM_List;
  TbBOOLEAN     SbFILE_EEPROM_Update;
} TsFILE_HEEPROM;
typedef TsFILE_HEEPROM TsFILE_HEEPROM_T;

typedef enum
{
  CeFILE_NVM_BadAddrReadEEP,
  CeFILE_NVM_NoFailOfReadEEP,
  CeFILE_NVM_BadChkSumReadEEP,
  CeFILE_NVM_UnknownErrReadEEP
} TsFILE_MEM_ERR;


/* Note: This structure contains the outline of what is stored to emulated EEPROM
 *       or power of store EEPROM.  The order is unimportant, except for the checksum
 *       being at the end only for consistency.  Within the file filepcfg.h the size
 *       of each array is defined and if the constant macro is 0 the corresponding
 *       structure field will be compiled-out, the code within the function
 *       SelectFILE_EE_ManufactEntry locate within filemeei.c will also be compiled-out
 */


typedef __packed__ struct
{
#if CcFILE_EE_Block_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Block_Status[CcFILE_EE_Block_Status_Size];
#endif

#if CcFILE_EE_HexBaseModelNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_HexBaseModelNumber[CcFILE_EE_HexBaseModelNumber_Size];
#endif

#if CcFILE_EE_HexEndModelNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_HexEndModelNumber[CcFILE_EE_HexEndModelNumber_Size];
#endif

#if CcFILE_EE_Broadcast_Code_Size > 0
  BYTE PROCALGN VaFILE_EE_Broadcast_Code[CcFILE_EE_Broadcast_Code_Size];
#endif

#if CcFILE_EE_VehMfgCalIdentityNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_VehMfgCalIdentityNumber[CcFILE_EE_VehMfgCalIdentityNumber_Size];
#endif

#if CcFILE_EE_CalibrationRepairShopCode_Size > 0
  BYTE PROCALGN VaFILE_EE_CalibrationRepairShopCode[CcFILE_EE_CalibrationRepairShopCode_Size];
#endif

#if CcFILE_EE_CalibrationProgrammingDate_Size > 0
  BYTE PROCALGN VaFILE_EE_CalibrationProgrammingDate[CcFILE_EE_CalibrationProgrammingDate_Size];
#endif

#if CcFILE_EE_ReservedCalProgrammingDate_Size > 0
  BYTE PROCALGN VaFILE_EE_ReservedCalProgrammingDate[CcFILE_EE_ReservedCalProgrammingDate_Size];
#endif

#if CcFILE_EE_SupplHexEndModelNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_SupplHexEndModelNumber[CcFILE_EE_SupplHexEndModelNumber_Size];
#endif

#if CcFILE_EE_VIN_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN[CcFILE_EE_VIN_Size];
#endif

#if CcFILE_EE_VIN_Expansion_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_Expansion[CcFILE_EE_VIN_Expansion_Size];
#endif

#if CcFILE_EE_VehMfgHardwareNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_VehMfgHardwareNumber[CcFILE_EE_VehMfgHardwareNumber_Size];
#endif

#if CcFILE_EE_SupplECU_HardwareNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_SupplECU_HardwareNumber[CcFILE_EE_SupplECU_HardwareNumber_Size];
#endif

#if CcFILE_EE_SystemNameOrVehEngType_Size > 0
  BYTE PROCALGN VaFILE_EE_SystemNameOrVehEngType[CcFILE_EE_SystemNameOrVehEngType_Size];
#endif

#if CcFILE_EE_RepairShopCode_Size > 0
  BYTE PROCALGN VaFILE_EE_RepairShopCode[CcFILE_EE_RepairShopCode_Size];
#endif

#if CcFILE_EE_ProgrammingDate_Size > 0
  BYTE PROCALGN VaFILE_EE_ProgrammingDate[CcFILE_EE_ProgrammingDate_Size];
#endif

#if CcFILE_EE_InstrumentationDatasetID_Size > 0
  BYTE PROCALGN VaFILE_EE_InstrumentationDatasetID[CcFILE_EE_InstrumentationDatasetID_Size];
#endif

#if CcFILE_EE_Odometer_Update_Locked_Size> 0
  BYTE PROCALGN VaFILE_EE_Odometer_Update_Locked[CcFILE_EE_Odometer_Update_Locked_Size];
#endif

#if CcFILE_EE_Seed_Size > 0
  BYTE PROCALGN VaFILE_EE_Seed[CcFILE_EE_Seed_Size];
#endif

#if CcFILE_EE_Key_Size > 0
  BYTE PROCALGN VaFILE_EE_Key[CcFILE_EE_Key_Size];
#endif

#if CcFILE_EE_ManufacturesEnableCounter_Size > 0
  BYTE PROCALGN VaFILE_EE_ManufacturesEnableCounter[CcFILE_EE_ManufacturesEnableCounter_Size];
#endif

#if CcFILE_EE_CrankShaftAdaptive_Size > 0
  BYTE PROCALGN VaFILE_EE_CrankShaftAdaptive[CcFILE_EE_CrankShaftAdaptive_Size];
#endif

#if CcFILE_EE_CrankShaftAdaptiveCntr_Size > 0
  BYTE PROCALGN VaFILE_EE_CrankShaftAdaptiveCntr[CcFILE_EE_CrankShaftAdaptiveCntr_Size];
#endif

#if CcFILE_EE_Mfg_Traceability_Size > 0
  BYTE PROCALGN VaFILE_EE_Mfg_Traceability[CcFILE_EE_Mfg_Traceability_Size];
#endif

#if CcFILE_EE_Auto_Detect_DWMC_Immo_Size > 0
  BYTE PROCALGN VaFILE_EE_Auto_Detect_DWMC_Immo[CcFILE_EE_Auto_Detect_DWMC_Immo_Size];
#endif

#if CcFILE_EE_PIC_Immo_VIN_Size > 0
  BYTE PROCALGN VaFILE_EE_PIC_Immo_VIN[CcFILE_EE_PIC_Immo_VIN_Size];
#endif

#if CcFILE_EE_PIC_Immo_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_PIC_Immo_Status[CcFILE_EE_PIC_Immo_Status_Size];
#endif

#if CcFILE_EE_Vehicle_Specific_Data_Size > 0
  BYTE PROCALGN VaFILE_EE_Vehicle_Specific_Data[CcFILE_EE_Vehicle_Specific_Data_Size];
#endif

#if CcFILE_EE_User_Password_Size > 0
  BYTE PROCALGN VaFILE_EE_User_Password[CcFILE_EE_User_Password_Size];
#endif

#if CcFILE_EE_Key_1_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_1_IDE[CcFILE_EE_Key_1_IDE_Size];
#endif

#if CcFILE_EE_Key_2_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_2_IDE[CcFILE_EE_Key_2_IDE_Size];
#endif

#if CcFILE_EE_Key_3_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_3_IDE[CcFILE_EE_Key_3_IDE_Size];
#endif

#if CcFILE_EE_Key_4_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_4_IDE[CcFILE_EE_Key_4_IDE_Size];
#endif

#if CcFILE_EE_LimpHome_Starts_Tester_Size > 0
  BYTE PROCALGN VaFILE_EE_LimpHome_Starts_Tester[CcFILE_EE_LimpHome_Starts_Tester_Size];
#endif

#if CcFILE_EE_Twice_Ign_Seq_Size > 0
  BYTE PROCALGN VaFILE_EE_Twice_Ign_Seq[CcFILE_EE_Twice_Ign_Seq_Size];
#endif

#if CcFILE_EE_Key_Learnt_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_Learnt[CcFILE_EE_Key_Learnt_Size];
#endif

#if CcFILE_EE_Transponder_Fault_Size > 0
  BYTE PROCALGN VaFILE_EE_Transponder_Fault[CcFILE_EE_Transponder_Fault_Size];
#endif

#if CcFILE_EE_Immob_EMS_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Immob_EMS_Status[CcFILE_EE_Immob_EMS_Status_Size];
#endif

#if CcFILE_EE_Password_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Password_Status[CcFILE_EE_Password_Status_Size];
#endif

#if CcFILE_EE_LockByTimer_Size > 0
  BYTE PROCALGN VaFILE_EE_LockByTimer[CcFILE_EE_LockByTimer_Size];
#endif

#if CcFILE_EE_Wrong_Inputs_Passwd_Teach_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_Inputs_Passwd_Teach[CcFILE_EE_Wrong_Inputs_Passwd_Teach_Size];
#endif

#if CcFILE_EE_Wrong_VSD_Key_Teach_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_VSD_Key_Teach[CcFILE_EE_Wrong_VSD_Key_Teach_Size];
#endif

#if CcFILE_EE_Wrong_PassWord_LimpHome_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_PassWord_LimpHome[CcFILE_EE_Wrong_PassWord_LimpHome_Size];
#endif

#if CcFILE_EE_Wrong_VSD_Neutral_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_VSD_Neutral[CcFILE_EE_Wrong_VSD_Neutral_Size];
#endif

#if CcFILE_EE_Auto_Detect_DWMC_ABS_Size > 0
  BYTE PROCALGN VaFILE_EE_Auto_Detect_DWMC_ABS[CcFILE_EE_Auto_Detect_DWMC_ABS_Size];
#endif

#if CcFILE_EE_VIN_HighByte_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_HighByte[CcFILE_EE_VIN_HighByte_Size];
#endif

#if CcFILE_EE_VIN_LowByte_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_LowByte[CcFILE_EE_VIN_LowByte_Size];
#endif

#if CcFILE_EE_VTDS_Config_Size > 0
  BYTE PROCALGN VaFILE_EE_VTDS_Config[CcFILE_EE_VTDS_Config_Size];
#endif

#if CcFILE_EE_VTDS_Last_RandomNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_VTDS_Last_RandomNumber[CcFILE_EE_VTDS_Last_RandomNumber_Size];
#endif

#if CcFILE_EE_VTDS_Polynomial_AsLongword_Size > 0
  BYTE PROCALGN VaFILE_EE_VTDS_Polynomial_AsLongword[CcFILE_EE_VTDS_Polynomial_AsLongword_Size];
#endif

#if CcFILE_EE_COA_Factor_Size > 0
  BYTE PROCALGN VaFILE_EE_COA_Factor[CcFILE_EE_COA_Factor_Size];
#endif

#if CcFILE_EE_RandomNumberPolynomial_Size > 0
  BYTE PROCALGN VaFILE_EE_RandomNumberPolynomial[CcFILE_EE_RandomNumberPolynomial_Size];
#endif

#if CcFILE_EE_SecurityCode_Size > 0
  BYTE PROCALGN VaFILE_EE_SecurityCode[CcFILE_EE_SecurityCode_Size];
#endif

#if CcFILE_EE_RandomNumberBuffer_Size > 0
  BYTE PROCALGN VaFILE_EE_RandomNumberBuffer[CcFILE_EE_RandomNumberBuffer_Size];
#endif

#if CcFILE_EE_SecretKey_Size > 0
  BYTE PROCALGN VaFILE_EE_SecretKey[CcFILE_EE_SecretKey_Size];
#endif

#if CcFILE_EE_New_Vehicle_Start_Cntr_Size > 0
  BYTE PROCALGN VaFILE_EE_New_Vehicle_Start_Cntr[CcFILE_EE_New_Vehicle_Start_Cntr_Size];
#endif

#if CcFILE_EE_SecCodeEntryCntr_Size > 0
  BYTE PROCALGN VaFILE_EE_SecCodeEntryCntr[CcFILE_EE_SecCodeEntryCntr_Size];
#endif

#if CcFILE_EE_SecurityBlockAccess_Size > 0
  BYTE PROCALGN VaFILE_EE_SecurityBlockAccess[CcFILE_EE_SecurityBlockAccess_Size];
#endif

#if CcFILE_EE_Dynamic_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Dynamic_Status[CcFILE_EE_Dynamic_Status_Size];
#endif

#if CcFILE_EE_XmsnOilLifeMonitor_Size > 0
  BYTE PROCALGN VaFILE_EE_XmsnOilLifeMonitor[CcFILE_EE_XmsnOilLifeMonitor_Size];
#endif

#if CcFILE_EE_AutoLearnVSS_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnVSSType[CcFILE_EE_AutoLearnVSS_Size];
#endif

#if CcFILE_EE_AutoLearnPSS_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnPSSType[CcFILE_EE_AutoLearnPSS_Size];
#endif

#if CcFILE_EE_AutoLearnChassisCtrl_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnChassisCtrlType[CcFILE_EE_AutoLearnChassisCtrl_Size];
#endif

#if CcFILE_EE_AutoLearnCruz_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnCruzCtlType[CcFILE_EE_AutoLearnCruz_Size];
#endif

#if CcFILE_EE_VIN_Update_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_Update[CcFILE_EE_VIN_Update_Size];
#endif

#if CcFILE_EE_DriveLineType_Size > 0
  BYTE PROCALGN VaFILE_EE_DriveLineType[CcFILE_EE_DriveLineType_Size];
#endif

#if CcFILE_EE_DriveLineTypeLrnd_Size > 0
  BYTE PROCALGN VaFILE_EE_DriveLineTypeLrnd[CcFILE_EE_DriveLineTypeLrnd_Size];
#endif

#if CcFILE_EE_Smartra3_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Smartra3_Status[CcFILE_EE_Smartra3_Status_Size];
#endif

#if CcFILE_EE_Key_5_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_5_IDE[CcFILE_EE_Key_5_IDE_Size];
#endif

#if CcFILE_EE_Key_6_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_6_IDE[CcFILE_EE_Key_6_IDE_Size];
#endif

#if CcFILE_EE_Key_7_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_7_IDE[CcFILE_EE_Key_7_IDE_Size];
#endif

#if CcFILE_EE_Key_8_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_8_IDE[CcFILE_EE_Key_8_IDE_Size];
#endif

#if CcFILE_EE_Smartra3_SEK_Size > 0
  BYTE PROCALGN VaFILE_EE_Smartra3_SEK[CcFILE_EE_Smartra3_SEK_Size];
#endif

#if CcFILE_EE_GMTargetVehicle_Size > 0
  BYTE PROCALGN VaFILE_EE_GMTargetVehicle[CcFILE_EE_GMTargetVehicle_Size];
#endif

#if CcFILE_EE_DynamTireCirc_Size > 0
  BYTE PROCALGN VaFILE_EE_DynamTireCirc[CcFILE_EE_DynamTireCirc_Size];
#endif

#if CcFILE_EE_OctSelSwitch_Size > 0
  BYTE PROCALGN VaFILE_EE_OctSelSwitch[CcFILE_EE_OctSelSwitch_Size];
#endif

#if CcFILE_EE_EngPerfIdent_Size > 0
  BYTE PROCALGN VaFILE_EE_EngPerfIdent[CcFILE_EE_EngPerfIdent_Size];
#endif

#if CcFILE_EE_FuelConsCalcCorrFctr_Size > 0
  BYTE PROCALGN VaFILE_EE_FuelConsCalcCorrFctr[CcFILE_EE_FuelConsCalcCorrFctr_Size];
#endif

#if CcFILE_EE_VehCANConfig_Size > 0
  BYTE PROCALGN VaFILE_EE_VehCANConfig[CcFILE_EE_VehCANConfig_Size];
#endif

#if CcFILE_EE_XMLDataFilePN_Size > 0
  BYTE PROCALGN VaFILE_EE_XMLDataFilePN[CcFILE_EE_XMLDataFilePN_Size];
#endif

#if CcFILE_EE_XMLDataFileAC_Size > 0
  BYTE PROCALGN VaFILE_EE_XMLDataFileAC[CcFILE_EE_XMLDataFileAC_Size];
#endif

#if CcFILE_EE_BootSWPNAC_Size > 0
  BYTE PROCALGN VaFILE_EE_BootSWPNAC[CcFILE_EE_BootSWPNAC_Size];
#endif

#if CcFILE_EE_XMLConfCompIdent_Size > 0
  BYTE PROCALGN VaFILE_EE_XMLConfCompIdent[CcFILE_EE_XMLConfCompIdent_Size];
#endif

#if CcFILE_EE_SWModIdent2AC_Size > 0
  BYTE PROCALGN VaFILE_EE_SWModIdent2AC[CcFILE_EE_SWModIdent2AC_Size];
#endif

#if CcFILE_EE_EndModelPNAC_Size > 0
  BYTE PROCALGN VaFILE_EE_EndModelPNAC[CcFILE_EE_EndModelPNAC_Size];
#endif

#if CcFILE_EE_BaseModelPNAC_Size > 0
  BYTE PROCALGN VaFILE_EE_BaseModelPNAC[CcFILE_EE_BaseModelPNAC_Size];
#endif

#if CcFILE_EE_ImmoPtPreRelease_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoPtPreRelease[CcFILE_EE_ImmoPtPreRelease_Size];
#endif

#if CcFILE_EE_ImmoPtSecretKey_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoPtSecretKey[CcFILE_EE_ImmoPtSecretKey_Size];
#endif

#if CcFILE_EE_ImmoPtGenericInfo_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoPtGenericInfo[CcFILE_EE_ImmoPtGenericInfo_Size];
#endif

#if CcFILE_EE_ImmoSecretInfo_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecretInfo[CcFILE_EE_ImmoSecretInfo_Size];
#endif

#if CcFILE_EE_ImmoSecureCode_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecureCode[CcFILE_EE_ImmoSecureCode_Size];
#endif

#if CcFILE_EE_ImmoSecureCodeCtr_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecureCodeCtr[CcFILE_EE_ImmoSecureCodeCtr_Size];
#endif

#if CcFILE_EE_ImmoSecureCodeRstCtr_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecureCodeRstCtr[CcFILE_EE_ImmoSecureCodeRstCtr_Size];
#endif

#if CcFILE_EE_OdoVINvalue_Size > 0
  BYTE PROCALGN VaFILE_EE_OdoVINvalue[CcFILE_EE_OdoVINvalue_Size];
#endif

#if CcFILE_EE_OdoVINwritten_Size > 0
  BYTE PROCALGN VaFILE_EE_OdoVINwritten[CcFILE_EE_OdoVINwritten_Size];
#endif

#if CcFILE_EE_NumberOfWarmupCycles_Size > 0
  BYTE PROCALGN VaFILE_EE_NumberOfWarmupCycles[CcFILE_EE_NumberOfWarmupCycles_Size];
#endif

#if CcFILE_EE_VINWrittenCount_Size > 0
  BYTE PROCALGN VaFILE_EE_VINWrittenCount[CcFILE_EE_VINWrittenCount_Size];
#endif

#if CcFILE_EE_PrevRepairShopCode_Size > 0
  BYTE PROCALGN VaFILE_EE_PrevRepairShopCode[CcFILE_EE_PrevRepairShopCode_Size];
#endif

#if CcFILE_EE_GreenEngCompComplete_Size > 0
  BYTE PROCALGN VaFILE_EE_GreenEngCompComplete[CcFILE_EE_GreenEngCompComplete_Size];
#endif

#if CcFILE_EE_TDC_CrankShaftAdaptive_Size > 0
  BYTE PROCALGN VaFILE_EE_TDC_CrankShaftAdaptive[CcFILE_EE_TDC_CrankShaftAdaptive_Size];
#endif

#if CcFILE_EE_Odometer_Size > 0
  BYTE PROCALGN VaFILE_EE_Odometer[CcFILE_EE_Odometer_Size];
#endif

#if CcFILE_EE_ReservedForCustomer_Size > 0
  BYTE PROCALGN VaFILE_EE_ReservedForCustomer[CcFILE_EE_ReservedForCustomer_Size];
#endif

#if CcFILE_EE_Calibration_Size > 0
  BYTE PROCALGN VaFILE_EE_CalibrationData[CcFILE_EE_Calibration_Size];
#endif
  volatile WORD VaFILE_EE_Checksum;
} TsFILE_EE_ManufactData_Pre;


typedef __packed__ struct
{
#if CcFILE_EE_Block_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Block_Status[CcFILE_EE_Block_Status_Size];
#endif

#if CcFILE_EE_HexBaseModelNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_HexBaseModelNumber[CcFILE_EE_HexBaseModelNumber_Size];
#endif

#if CcFILE_EE_HexEndModelNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_HexEndModelNumber[CcFILE_EE_HexEndModelNumber_Size];
#endif

#if CcFILE_EE_Broadcast_Code_Size > 0
  BYTE PROCALGN VaFILE_EE_Broadcast_Code[CcFILE_EE_Broadcast_Code_Size];
#endif

#if CcFILE_EE_VehMfgCalIdentityNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_VehMfgCalIdentityNumber[CcFILE_EE_VehMfgCalIdentityNumber_Size];
#endif

#if CcFILE_EE_CalibrationRepairShopCode_Size > 0
  BYTE PROCALGN VaFILE_EE_CalibrationRepairShopCode[CcFILE_EE_CalibrationRepairShopCode_Size];
#endif

#if CcFILE_EE_CalibrationProgrammingDate_Size > 0
  BYTE PROCALGN VaFILE_EE_CalibrationProgrammingDate[CcFILE_EE_CalibrationProgrammingDate_Size];
#endif

#if CcFILE_EE_ReservedCalProgrammingDate_Size > 0
  BYTE PROCALGN VaFILE_EE_ReservedCalProgrammingDate[CcFILE_EE_ReservedCalProgrammingDate_Size];
#endif

#if CcFILE_EE_SupplHexEndModelNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_SupplHexEndModelNumber[CcFILE_EE_SupplHexEndModelNumber_Size];
#endif

#if CcFILE_EE_VIN_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN[CcFILE_EE_VIN_Size];
#endif

#if CcFILE_EE_VIN_Expansion_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_Expansion[CcFILE_EE_VIN_Expansion_Size];
#endif

#if CcFILE_EE_VehMfgHardwareNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_VehMfgHardwareNumber[CcFILE_EE_VehMfgHardwareNumber_Size];
#endif

#if CcFILE_EE_SupplECU_HardwareNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_SupplECU_HardwareNumber[CcFILE_EE_SupplECU_HardwareNumber_Size];
#endif

#if CcFILE_EE_SystemNameOrVehEngType_Size > 0
  BYTE PROCALGN VaFILE_EE_SystemNameOrVehEngType[CcFILE_EE_SystemNameOrVehEngType_Size];
#endif

#if CcFILE_EE_RepairShopCode_Size > 0
  BYTE PROCALGN VaFILE_EE_RepairShopCode[CcFILE_EE_RepairShopCode_Size];
#endif

#if CcFILE_EE_ProgrammingDate_Size > 0
  BYTE PROCALGN VaFILE_EE_ProgrammingDate[CcFILE_EE_ProgrammingDate_Size];
#endif

#if CcFILE_EE_InstrumentationDatasetID_Size > 0
  BYTE PROCALGN VaFILE_EE_InstrumentationDatasetID[CcFILE_EE_InstrumentationDatasetID_Size];
#endif

#if CcFILE_EE_Odometer_Update_Locked_Size> 0
  BYTE PROCALGN VaFILE_EE_Odometer_Update_Locked[CcFILE_EE_Odometer_Update_Locked_Size];
#endif

#if CcFILE_EE_Seed_Size > 0
  BYTE PROCALGN VaFILE_EE_Seed[CcFILE_EE_Seed_Size];
#endif

#if CcFILE_EE_Key_Size > 0
  BYTE PROCALGN VaFILE_EE_Key[CcFILE_EE_Key_Size];
#endif

#if CcFILE_EE_ManufacturesEnableCounter_Size > 0
  BYTE PROCALGN VaFILE_EE_ManufacturesEnableCounter[CcFILE_EE_ManufacturesEnableCounter_Size];
#endif

#if CcFILE_EE_CrankShaftAdaptive_Size > 0
  BYTE PROCALGN VaFILE_EE_CrankShaftAdaptive[CcFILE_EE_CrankShaftAdaptive_Size];
#endif

#if CcFILE_EE_CrankShaftAdaptiveCntr_Size > 0
  BYTE PROCALGN VaFILE_EE_CrankShaftAdaptiveCntr[CcFILE_EE_CrankShaftAdaptiveCntr_Size];
#endif

#if CcFILE_EE_Mfg_Traceability_Size > 0
  BYTE PROCALGN VaFILE_EE_Mfg_Traceability[CcFILE_EE_Mfg_Traceability_Size];
#endif

#if CcFILE_EE_Auto_Detect_DWMC_Immo_Size > 0
  BYTE PROCALGN VaFILE_EE_Auto_Detect_DWMC_Immo[CcFILE_EE_Auto_Detect_DWMC_Immo_Size];
#endif

#if CcFILE_EE_PIC_Immo_VIN_Size > 0
  BYTE PROCALGN VaFILE_EE_PIC_Immo_VIN[CcFILE_EE_PIC_Immo_VIN_Size];
#endif

#if CcFILE_EE_PIC_Immo_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_PIC_Immo_Status[CcFILE_EE_PIC_Immo_Status_Size];
#endif

#if CcFILE_EE_Vehicle_Specific_Data_Size > 0
  BYTE PROCALGN VaFILE_EE_Vehicle_Specific_Data[CcFILE_EE_Vehicle_Specific_Data_Size];
#endif

#if CcFILE_EE_User_Password_Size > 0
  BYTE PROCALGN VaFILE_EE_User_Password[CcFILE_EE_User_Password_Size];
#endif

#if CcFILE_EE_Key_1_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_1_IDE[CcFILE_EE_Key_1_IDE_Size];
#endif

#if CcFILE_EE_Key_2_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_2_IDE[CcFILE_EE_Key_2_IDE_Size];
#endif

#if CcFILE_EE_Key_3_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_3_IDE[CcFILE_EE_Key_3_IDE_Size];
#endif

#if CcFILE_EE_Key_4_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_4_IDE[CcFILE_EE_Key_4_IDE_Size];
#endif

#if CcFILE_EE_LimpHome_Starts_Tester_Size > 0
  BYTE PROCALGN VaFILE_EE_LimpHome_Starts_Tester[CcFILE_EE_LimpHome_Starts_Tester_Size];
#endif

#if CcFILE_EE_Twice_Ign_Seq_Size > 0
  BYTE PROCALGN VaFILE_EE_Twice_Ign_Seq[CcFILE_EE_Twice_Ign_Seq_Size];
#endif

#if CcFILE_EE_Key_Learnt_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_Learnt[CcFILE_EE_Key_Learnt_Size];
#endif

#if CcFILE_EE_Transponder_Fault_Size > 0
  BYTE PROCALGN VaFILE_EE_Transponder_Fault[CcFILE_EE_Transponder_Fault_Size];
#endif

#if CcFILE_EE_Immob_EMS_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Immob_EMS_Status[CcFILE_EE_Immob_EMS_Status_Size];
#endif

#if CcFILE_EE_Password_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Password_Status[CcFILE_EE_Password_Status_Size];
#endif

#if CcFILE_EE_LockByTimer_Size > 0
  BYTE PROCALGN VaFILE_EE_LockByTimer[CcFILE_EE_LockByTimer_Size];
#endif

#if CcFILE_EE_Wrong_Inputs_Passwd_Teach_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_Inputs_Passwd_Teach[CcFILE_EE_Wrong_Inputs_Passwd_Teach_Size];
#endif

#if CcFILE_EE_Wrong_VSD_Key_Teach_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_VSD_Key_Teach[CcFILE_EE_Wrong_VSD_Key_Teach_Size];
#endif

#if CcFILE_EE_Wrong_PassWord_LimpHome_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_PassWord_LimpHome[CcFILE_EE_Wrong_PassWord_LimpHome_Size];
#endif

#if CcFILE_EE_Wrong_VSD_Neutral_Size > 0
  BYTE PROCALGN VaFILE_EE_Wrong_VSD_Neutral[CcFILE_EE_Wrong_VSD_Neutral_Size];
#endif

#if CcFILE_EE_Auto_Detect_DWMC_ABS_Size > 0
  BYTE PROCALGN VaFILE_EE_Auto_Detect_DWMC_ABS[CcFILE_EE_Auto_Detect_DWMC_ABS_Size];
#endif

#if CcFILE_EE_VIN_HighByte_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_HighByte[CcFILE_EE_VIN_HighByte_Size];
#endif

#if CcFILE_EE_VIN_LowByte_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_LowByte[CcFILE_EE_VIN_LowByte_Size];
#endif

#if CcFILE_EE_VTDS_Config_Size > 0
  BYTE PROCALGN VaFILE_EE_VTDS_Config[CcFILE_EE_VTDS_Config_Size];
#endif

#if CcFILE_EE_VTDS_Last_RandomNumber_Size > 0
  BYTE PROCALGN VaFILE_EE_VTDS_Last_RandomNumber[CcFILE_EE_VTDS_Last_RandomNumber_Size];
#endif

#if CcFILE_EE_VTDS_Polynomial_AsLongword_Size > 0
  BYTE PROCALGN VaFILE_EE_VTDS_Polynomial_AsLongword[CcFILE_EE_VTDS_Polynomial_AsLongword_Size];
#endif

#if CcFILE_EE_COA_Factor_Size > 0
  BYTE PROCALGN VaFILE_EE_COA_Factor[CcFILE_EE_COA_Factor_Size];
#endif

#if CcFILE_EE_RandomNumberPolynomial_Size > 0
  BYTE PROCALGN VaFILE_EE_RandomNumberPolynomial[CcFILE_EE_RandomNumberPolynomial_Size];
#endif

#if CcFILE_EE_SecurityCode_Size > 0
  BYTE PROCALGN VaFILE_EE_SecurityCode[CcFILE_EE_SecurityCode_Size];
#endif

#if CcFILE_EE_RandomNumberBuffer_Size > 0
  BYTE PROCALGN VaFILE_EE_RandomNumberBuffer[CcFILE_EE_RandomNumberBuffer_Size];
#endif

#if CcFILE_EE_SecretKey_Size > 0
  BYTE PROCALGN VaFILE_EE_SecretKey[CcFILE_EE_SecretKey_Size];
#endif

#if CcFILE_EE_New_Vehicle_Start_Cntr_Size > 0
  BYTE PROCALGN VaFILE_EE_New_Vehicle_Start_Cntr[CcFILE_EE_New_Vehicle_Start_Cntr_Size];
#endif

#if CcFILE_EE_SecCodeEntryCntr_Size > 0
  BYTE PROCALGN VaFILE_EE_SecCodeEntryCntr[CcFILE_EE_SecCodeEntryCntr_Size];
#endif

#if CcFILE_EE_SecurityBlockAccess_Size > 0
  BYTE PROCALGN VaFILE_EE_SecurityBlockAccess[CcFILE_EE_SecurityBlockAccess_Size];
#endif

#if CcFILE_EE_Dynamic_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Dynamic_Status[CcFILE_EE_Dynamic_Status_Size];
#endif

#if CcFILE_EE_XmsnOilLifeMonitor_Size > 0
  BYTE PROCALGN VaFILE_EE_XmsnOilLifeMonitor[CcFILE_EE_XmsnOilLifeMonitor_Size];
#endif

#if CcFILE_EE_AutoLearnVSS_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnVSSType[CcFILE_EE_AutoLearnVSS_Size];
#endif

#if CcFILE_EE_AutoLearnPSS_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnPSSType[CcFILE_EE_AutoLearnPSS_Size];
#endif

#if CcFILE_EE_AutoLearnChassisCtrl_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnChassisCtrlType[CcFILE_EE_AutoLearnChassisCtrl_Size];
#endif

#if CcFILE_EE_AutoLearnCruz_Size > 0
  BYTE PROCALGN VaFILE_EE_AutoLearnCruzCtlType[CcFILE_EE_AutoLearnCruz_Size];
#endif

#if CcFILE_EE_VIN_Update_Size > 0
  BYTE PROCALGN VaFILE_EE_VIN_Update[CcFILE_EE_VIN_Update_Size];
#endif

#if CcFILE_EE_DriveLineType_Size > 0
  BYTE PROCALGN VaFILE_EE_DriveLineType[CcFILE_EE_DriveLineType_Size];
#endif

#if CcFILE_EE_DriveLineTypeLrnd_Size > 0
  BYTE PROCALGN VaFILE_EE_DriveLineTypeLrnd[CcFILE_EE_DriveLineTypeLrnd_Size];
#endif

#if CcFILE_EE_Smartra3_Status_Size > 0
  BYTE PROCALGN VaFILE_EE_Smartra3_Status[CcFILE_EE_Smartra3_Status_Size];
#endif

#if CcFILE_EE_Key_5_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_5_IDE[CcFILE_EE_Key_5_IDE_Size];
#endif

#if CcFILE_EE_Key_6_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_6_IDE[CcFILE_EE_Key_6_IDE_Size];
#endif

#if CcFILE_EE_Key_7_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_7_IDE[CcFILE_EE_Key_7_IDE_Size];
#endif

#if CcFILE_EE_Key_8_IDE_Size > 0
  BYTE PROCALGN VaFILE_EE_Key_8_IDE[CcFILE_EE_Key_8_IDE_Size];
#endif

#if CcFILE_EE_Smartra3_SEK_Size > 0
  BYTE PROCALGN VaFILE_EE_Smartra3_SEK[CcFILE_EE_Smartra3_SEK_Size];
#endif

#if CcFILE_EE_GMTargetVehicle_Size > 0
  BYTE PROCALGN VaFILE_EE_GMTargetVehicle[CcFILE_EE_GMTargetVehicle_Size];
#endif

#if CcFILE_EE_DynamTireCirc_Size > 0
  BYTE PROCALGN VaFILE_EE_DynamTireCirc[CcFILE_EE_DynamTireCirc_Size];
#endif

#if CcFILE_EE_OctSelSwitch_Size > 0
  BYTE PROCALGN VaFILE_EE_OctSelSwitch[CcFILE_EE_OctSelSwitch_Size];
#endif

#if CcFILE_EE_EngPerfIdent_Size > 0
  BYTE PROCALGN VaFILE_EE_EngPerfIdent[CcFILE_EE_EngPerfIdent_Size];
#endif

#if CcFILE_EE_FuelConsCalcCorrFctr_Size > 0
  BYTE PROCALGN VaFILE_EE_FuelConsCalcCorrFctr[CcFILE_EE_FuelConsCalcCorrFctr_Size];
#endif

#if CcFILE_EE_VehCANConfig_Size > 0
  BYTE PROCALGN VaFILE_EE_VehCANConfig[CcFILE_EE_VehCANConfig_Size];
#endif

#if CcFILE_EE_XMLDataFilePN_Size > 0
  BYTE PROCALGN VaFILE_EE_XMLDataFilePN[CcFILE_EE_XMLDataFilePN_Size];
#endif

#if CcFILE_EE_XMLDataFileAC_Size > 0
  BYTE PROCALGN VaFILE_EE_XMLDataFileAC[CcFILE_EE_XMLDataFileAC_Size];
#endif

#if CcFILE_EE_BootSWPNAC_Size > 0
  BYTE PROCALGN VaFILE_EE_BootSWPNAC[CcFILE_EE_BootSWPNAC_Size];
#endif

#if CcFILE_EE_XMLConfCompIdent_Size > 0
  BYTE PROCALGN VaFILE_EE_XMLConfCompIdent[CcFILE_EE_XMLConfCompIdent_Size];
#endif

#if CcFILE_EE_SWModIdent2AC_Size > 0
  BYTE PROCALGN VaFILE_EE_SWModIdent2AC[CcFILE_EE_SWModIdent2AC_Size];
#endif

#if CcFILE_EE_EndModelPNAC_Size > 0
  BYTE PROCALGN VaFILE_EE_EndModelPNAC[CcFILE_EE_EndModelPNAC_Size];
#endif

#if CcFILE_EE_BaseModelPNAC_Size > 0
  BYTE PROCALGN VaFILE_EE_BaseModelPNAC[CcFILE_EE_BaseModelPNAC_Size];
#endif

#if CcFILE_EE_ImmoPtPreRelease_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoPtPreRelease[CcFILE_EE_ImmoPtPreRelease_Size];
#endif

#if CcFILE_EE_ImmoPtSecretKey_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoPtSecretKey[CcFILE_EE_ImmoPtSecretKey_Size];
#endif

#if CcFILE_EE_ImmoPtGenericInfo_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoPtGenericInfo[CcFILE_EE_ImmoPtGenericInfo_Size];
#endif

#if CcFILE_EE_ImmoSecretInfo_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecretInfo[CcFILE_EE_ImmoSecretInfo_Size];
#endif

#if CcFILE_EE_ImmoSecureCode_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecureCode[CcFILE_EE_ImmoSecureCode_Size];
#endif

#if CcFILE_EE_ImmoSecureCodeCtr_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecureCodeCtr[CcFILE_EE_ImmoSecureCodeCtr_Size];
#endif

#if CcFILE_EE_ImmoSecureCodeRstCtr_Size > 0
  BYTE PROCALGN VaFILE_EE_ImmoSecureCodeRstCtr[CcFILE_EE_ImmoSecureCodeRstCtr_Size];
#endif

#if CcFILE_EE_OdoVINvalue_Size > 0
  BYTE PROCALGN VaFILE_EE_OdoVINvalue[CcFILE_EE_OdoVINvalue_Size];
#endif

#if CcFILE_EE_OdoVINwritten_Size > 0
  BYTE PROCALGN VaFILE_EE_OdoVINwritten[CcFILE_EE_OdoVINwritten_Size];
#endif

#if CcFILE_EE_NumberOfWarmupCycles_Size > 0
  BYTE PROCALGN VaFILE_EE_NumberOfWarmupCycles[CcFILE_EE_NumberOfWarmupCycles_Size];
#endif

#if CcFILE_EE_VINWrittenCount_Size > 0
  BYTE PROCALGN VaFILE_EE_VINWrittenCount[CcFILE_EE_VINWrittenCount_Size];
#endif

#if CcFILE_EE_PrevRepairShopCode_Size > 0
  BYTE PROCALGN VaFILE_EE_PrevRepairShopCode[CcFILE_EE_PrevRepairShopCode_Size];
#endif

#if CcFILE_EE_GreenEngCompComplete_Size > 0
  BYTE PROCALGN VaFILE_EE_GreenEngCompComplete[CcFILE_EE_GreenEngCompComplete_Size];
#endif

#if CcFILE_EE_TDC_CrankShaftAdaptive_Size > 0
  BYTE PROCALGN VaFILE_EE_TDC_CrankShaftAdaptive[CcFILE_EE_TDC_CrankShaftAdaptive_Size];
#endif

#if CcFILE_EE_Odometer_Size > 0
  BYTE PROCALGN VaFILE_EE_Odometer[CcFILE_EE_Odometer_Size];
#endif

 /* calculate the reserved size, 0x17a - sizeof(TsFILE_EE_ManufactData_Pre)*/
  BYTE PROCALGN VaFILE_EE_Reserved1Data[0x17a - sizeof(TsFILE_EE_ManufactData_Pre)];

#if CcFILE_EE_ReservedForCustomer_Size > 0
  BYTE PROCALGN VaFILE_EE_ReservedForCustomer[CcFILE_EE_ReservedForCustomer_Size];
#endif

#if CcFILE_EE_Calibration_Size > 0
  BYTE PROCALGN VaFILE_EE_CalibrationData[CcFILE_EE_Calibration_Size];
#endif
  volatile WORD VaFILE_EE_Checksum;
} TsFILE_EE_ManufactData;

#endif  /* FILEFTYP_H */

/******************************************************************************
*
* Revision history:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   030829 rmn 3070 Created module.
* 2.0   030814 caw 3137 Added emulated EE support.
*                        TsFILE_MEM_ERR
*                        TsFILE_EEPROM
*                        TsFILE_HEEPROM
*                        TeFILE_STORAGE_TYPE
* 3.0   031022 caw 3138 Added: TeFILE_EE_ManufactDataEntry
* 4.0   031210 caw 3441 Added: CeFILE_EE_AutoLearnCruz
* 5.0   031211 caw 3221 Added: TsFILE_HEEPROM_T
* 6.0   040227 caw 3759 Added new immobilizer parameters to EMS Mnufacturing
*                        EEPROM: CeFILE_EE_PIC_Immo_VIN
*                                CeFILE_EE_PIC_Immo_Status
*                                CeFILE_EE_Vehicle_Specific_Data
*                                CeFILE_EE_User_Password
*                                CeFILE_EE_Key_1_IDE
*                                CeFILE_EE_Key_2_IDE
*                                CeFILE_EE_Key_3_IDE
*                                CeFILE_EE_Key_4_IDE
*                                CeFILE_EE_LimpHome_Starts_Tester
*                                CeFILE_EE_Twice_Ign_Seq
*                                CeFILE_EE_Key_Learnt
*                                CeFILE_EE_Transponder_Fault
*                                CeFILE_EE_Immob_EMS_Status
*                                CeFILE_EE_Password_Status
*                                CeFILE_EE_LockByTimer
*                                CeFILE_EE_Wrong_Inputs_Passwd_Teach
*                                CeFILE_EE_Wrong_VSD_Key_Teach
*                                CeFILE_EE_Wrong_PassWord_LimpHome
*                                CeFILE_EE_Wrong_VSD_Neutral
*                       Added new manufacturing data interfaces to EMS
*                        Manufacturing EEPROM:
*                                CeFILE_EE_VehMfgCalIdentityNumber
*                                CeFILE_EE_SupplHexEndModelNumber
*                                CeFILE_EE_VehMfgHardwareNumber
*                                CeFILE_EE_SupplECU_HardwareNumber
*                                CeFILE_EE_SystemNameOrVehEngType
*                                CeFILE_EE_InstrumentationDatasetID
*                                CeFILE_EE_VIN_Update
* 7     040416 as  -BM- Merged 'fileftyp.h-6' with 'fileftyp.h-kok_pt1#6'
* 6.1.1 040421 caw 3922 Added new immobilizer parameters to EMS Mnufacturing
*                        EEPROM: CeFILE_EE_DriveLineType
*                                CeFILE_EE_DriveLineTypeLrnd
* 8.0   040428 caw BM   Merged files for release.
* 9     040827 rmn 4391 Added more elements to the structure TsFILE_FR_Data
* 9.1   040913 ksr -BM- Build Error.
* 11    041202 jyz 4612 Added CcFILE_CAL_ID_SIZE
* 12    050124 jyz 4961 Added TsFILE_SCU_Type
* 13    050215 at  -BM- Fixed build error for GMDAT
* 14.0  060209 caw 5519 Added: CeFILE_EE_CalibrationRepairShopCode
*                              CeFILE_EE_CalibrationProgrammingDate
* 14.1.1
*       070130 gps -BM- CORE : Include Header Files Optimization.
*                       Installed non-functional changes.
* 15.0  061117 sm  5850 Added SMARTRA3 nvm variables.
* 16.0  071116 caw -BM- Per SQ and PM changed number of FLR buffer entries
*                        to gain NVM memory.
* 17.0  080130 grb 6621 changed the type of f_Pct_IDLE_Airflow from
*                       T_PERCENTb -> T_PERCENT_DIFFb
* tci_pt3#14.1.2.1.2
*       080116 VP  6563 Added CeFILE_EE_GMTargetVehicle,
*                             CeFILE_EE_DynamTireCirc,
*                             CeFILE_EE_OctSelSwitch,
*                             CeFILE_EE_EngPerfIdent,
*                             CeFILE_EE_FuelConsCalcCorrFctr.
* 14.1.2.1.1.1.2
*       080221  mt -BM- Merged 'fileftyp.h~14.1.2.1.1.1.1' with
*                              'fileftyp.h~tci_pt3#14.1.2.1.2'.
* tci_pt3#14.1.2.1.1.1.3
*       080401  VP 6833 Added CeFILE_EE_VehCANConfig,
*                             CeFILE_EE_XMLDataFilePN,
*                             CeFILE_EE_XMLDataFileAC,
*                             CeFILE_EE_BootSWPNAC,
*                             CeFILE_EE_SWModIdent1AC,
*                             CeFILE_EE_SWModIdent2AC,
*                             CeFILE_EE_EndModelPNAC,
*                             CeFILE_EE_BaseModelPNAC,
*                             CeFILE_EE_ImmoPtPreRelease,
*                             CeFILE_EE_ImmoPtSecretKey,
*                             CeFILE_EE_ImmoPtGenericInfo,
*                             CeFILE_EE_ImmoSecretInfo,
*                             CeFILE_EE_ImmoSecureCode,
*                             CeFILE_EE_ImmoSecureCodeCtr,
*                             CeFILE_EE_ImmoSecureCodeRstCtr.
* tci_pt3#14.1.2.1.1.1.4
*      080507  VP  6834  Added CeFILE_EE_OdoVINvalue,
*                              CeFILE_EE_OdoVINwritten.
* 14.1.2.1.1.1.4
*       080606 KN  7052 Added  CeFILE_EE_NumberOfWarmupCycles
* 14.1.2.1.1.1.5
*       080806 KN  ---  Merged from 'fileftyp.h~14.1.2.1.1.1.4:incl:tcb_pt1#1'
*                       and 'fileftyp.h~tci_pt3#14.1.2.1.1.1.4:incl:tcb_pt1#1'
* tci_pt3#14.1.2.1.1.1.5
*      080609  VP  7111  Added CeFILE_EE_VINWrittenCount,
*                              CeFILE_EE_PrevRepairShopCode.
*                       Replaced EEPROM interface for SWModIdent1AC by
*                       XMLConfCompIdent.
* 14.1.2.1.1.1.6
*       080810 me  7269 T300-J300 GMLAN Commonization: Updated CORE with all
*                       GMLAN related changes from Offline J300 Project
* 14.1.2.1.1.1.5.1.2
*       090807 rbg 8125 Added CeFILE_EE_GreenEngCompComplete
*
*tci_pt3#14.1.2.1.1.1.5.1.3
*       091120 ng  8442 QAC fix 5.3: Added struct TsFILE_EE_ManufactData 
*                       and TsFILE_EE_SW_INFO. Along with subsystem private
*                        constants.
*                       Included header file filepcfg.h  and trvspcfg.h 
* kok_pt2#15
*       100802 JP  8899 Added a new EE section for MISF TDC window data
* tci_pt3#16
*       110131 nag 9008 Modified data type of f_m_DesiredAirMass
* kok_pt2#
*       120418 me  9530 MT92 specific tasking 2.5 byte alignment changes
*
******************************************************************************/
