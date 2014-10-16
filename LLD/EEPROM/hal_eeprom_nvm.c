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

//for immo develop
/***********************************************************************************/
//#pragma section [eeprom_immo]
/***********************************************************************************/
/* 
 * a 16 bytes block of [0x544 ~ 0x553] is reserved in case 
 * new EE vars to be defined into eeprom_immo in future   
 */
// uint8_t     EE_Immo_Block[EEImmoBlockSize]       _EE(0x144); 

/*Below EE for Siemens immo sk with 16bytes*/
uint8_t     EE_SiemensSK[Siemens_SK_Length];
/* 
 * EE_Immobiliser is defined for old immobilizer, shared
 * same EE memory with new generic immobilizer since the
 * two types of immo will not be used both in one application
 */
// uint8_t     EE_Immobiliser[ImmobiliserSize]  _EE(0x154); 

/*
 * Below EE vars are defined for new generic immobilizer
 */
uint8_t     EE_Immo_option;
uint8_t     EE_SK[SK_Length];
// uint32_t    EE_SK_L                          _EE(0x155); /* Lowest 4 bytes of EE_SK */
// uint16_t    EE_SK_H                          _EE(0x159);
/*
 *Below EE vars are define for jicheng immobilizer
 */


#pragma section DATA " " ".bss"


