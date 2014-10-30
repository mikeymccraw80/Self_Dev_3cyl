//=============================================================================
//
//       COPYRIGHT, 2010, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   hal_eeprom_nvm.c~2:csrc:ctc_pt3#2 %
//
// created_by:       bzfnb6
//
// date_created:     Wednesday, January 06, 2010 9:02:19 AM
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
#include "hal_eeprom_nvm.h"

/*===========================================================================*\
 *  Variables Definitions
\*===========================================================================*/
// FIXME - A... temply comment out for NV test
#if 0
uint8_t            MFG_Data_Before_Backup_Debug_Counter;
uint8_t            MFG_Data_After_Backup_Debug_Counter;
MFG_Data_Debug_T   MFG_Data_Before_Backup[NUMBER_OF_DEBUG_DATA_SET];
MFG_Data_Debug_T   MFG_Data_After_Backup[NUMBER_OF_DEBUG_DATA_SET];
#endif
#pragma section DATA " " ".nc_nvram"
Backup_Disrupted_T Backup_Disrupted;
uint32_t rolling_counter_vehicle;

#pragma section DATA " " ".bss"


