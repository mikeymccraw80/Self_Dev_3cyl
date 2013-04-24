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
extern uint32_t rolling_counter_vehicle;
#pragma section DATA " " ".bss"

#endif /* HAL_EMULATED_NVM_H */

