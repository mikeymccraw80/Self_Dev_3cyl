//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_init.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:        %
//
// %version:         1.1.1 %
//
//=============================================================================
#include "io_config.h"
#include "dd_kp254.h"
#include "dd_kp254_init.h"

//=============================================================================
// @KP254 Tx and Rx buffer definition
//=============================================================================
uint16_t  KP254_ACQ_Pressure_Txd[NUMBER_OF_KP254];        // Acquire pressure command
uint16_t  KP254_ACQ_Temperature_Txd[NUMBER_OF_KP254];     // Acquire temperature command
uint16_t  KP254_Trigger_DIAG_Txd[NUMBER_OF_KP254];        // Trigger diagnosis command
uint16_t  KP254_ACQ_ID_Txd[NUMBER_OF_KP254];              // Acquire identifier command 

uint16_t  KP254_Pressure_Rxd[NUMBER_OF_KP254];            // Pressure rxd buffer (With out of range diag)
uint16_t  KP254_Temperature_Rxd[NUMBER_OF_KP254];         // Temperature rxd buffer(With out of range diag)
uint16_t  KP254_DIAG_Rxd[NUMBER_OF_KP254];                // full diagnosis codes
uint16_t  KP254_ID_Rxd[NUMBER_OF_KP254];                  // identifier rxd buffer

//=============================================================================
// @KP254 fault log definition
//=============================================================================
uint8_t KP254_Fault_Log[NUMBER_OF_KP254];

