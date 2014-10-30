#ifndef HAL_EEPROM_NVM_H
#define HAL_EEPROM_NVM_H

//=============================================================================
//
//       COPYRIGHT, 2010, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   hal_eeprom_nvm.h~2:incl:ctc_pt3#2 %
//
// created_by:       bzfnb6
//
// date_created:     Tuesday, January 05, 2010 2:48:49 PM
//
// %derived_by:      zzrfyj %
//
// %date_modified:     %
//
// %version:         2 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================

#include "reuse.h"
//#include "hal_diag.h"

#define  EEFixedBlockSize                (0x32)
#define  ImmobiliserSize                 (7)
#define  VehicleIdentificationNumberSize (17)
#define  DtcDisableMaskSize              (32)
#define  HistoryTableSize                (8)
#define  ManufacturesEnableCounter_Size  (1)
#define  CrankShaftAdaptive_Size         (CcSYST_NUM_OF_CYLINDERS*4)
#define  CrankShaftAdaptiveCntr_Size     (1)
#define  M4EepBaudRateSize               (2)
#define  RepairShopCodeSize              (10)
#define  ProgrammingDateSize             (4)
#define  Const_CrankShaftAdaptive_Size   (24) /* max size in case of 6 cyl, keep EEPROM fix size */
#define  Kw2000Level2KeySize             (2)
#define  SK_LowBytesLength               (4)
#define  SK_Length                       (12)
#define  Siemens_SK_Length               (16) 
#define  SecretKEYSize                   (12)
#define  SecretCodeSize                  (2)
#define  EEImmoBlockSize                 (0x20)

#define NoMileageCells                   (16)

/*===========================================================================*\
 *  Data Structure Definitions
\*===========================================================================*/
typedef struct Backup_Disrupted_Tag
{
   uint16_t Bank0_Corrupted;
   uint16_t Bank1_Corrupted;

} Backup_Disrupted_T;

/*===========================================================================*\
 *  Variables Definitions
\*===========================================================================*/
// FIXME - A... temply comment out for NV test
#if 0
extern uint8_t            MFG_Data_Before_Backup_Debug_Counter;
extern uint8_t            MFG_Data_After_Backup_Debug_Counter;
extern MFG_Data_Debug_T   MFG_Data_Before_Backup[NUMBER_OF_DEBUG_DATA_SET];
extern MFG_Data_Debug_T   MFG_Data_After_Backup[NUMBER_OF_DEBUG_DATA_SET];
#endif
#pragma section DATA " " ".nc_nvram"
extern Backup_Disrupted_T Backup_Disrupted;
// FIXME - A... for test
extern uint32_t    rolling_counter_vehicle;

#pragma section DATA " " ".bss"

#endif /* HAL_EMULATED_NVM_H */

