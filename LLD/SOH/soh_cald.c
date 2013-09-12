//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            soh_cald.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      zzrfyj %
//
// %date_modified:        %
//
// %version:         2 %
//
//=============================================================================
#include "reuse.h"
#include "soh_cald.h"
#include "soh_common.h"

/*===========================================================================*\
 * Calibrations
\*===========================================================================*/
/*
*| soh_cald.{
*|   t_soh_0_14_ubyte
*|   {
*|     : kind = fixed;
*|     : precision = 1;
*|     : range = 0 TO <15;
*|   }
*|   KSOHCRTH {
*|     : is_calconst;
*|     : is_coordinated;
*|     : description = "SOH challenge and response counter threshold "
*| "below which fuel, spark and ETC outputs are disabled. "
*| "Count should be less than 15";
*|     : type = soh_cald.t_soh_0_14_ubyte;
*|     : units = "count";
*|   }
*| }
*/
const uint8_t KSOHCRTH = 10;

/*
*| soh_cald.{
*|   t_soh_long
*|   {
*|      :kind = fixed;
*|      :precision = 1/64; 
*|      :range = 0 TO <67108864;
*|   }
*|   KSOHRTITH {
*|     : is_calconst;
*|     : is_coordinated;
*|     : description = "Real time interrupt test tolerance threshold "
*| "above which the test is considered failed. ";
*|     : type = soh_cald.t_soh_long;
*|     : units = "milliseconds";
*|   }
*| }
*/
const SOH_TMR_MSEC_T KSOHRTITH = V_SOH_TMR_MSEC_T(8.0000);

