#ifndef IMMO_CAL_H
#define IMMO_CAL_H
/* ============================================================================ *\
 * immo_cal.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       immo_cal.h-2:incl:mt20a#1
 * Revision:        2
 * Creation date:   Tuesday, June 18, 2002 4:50:14 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the immobilizer calibration.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "io_type.h"
#include "intr_ems.h"
#include "lux_type.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
/*  none  */

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
//extern const Every_4th_Loop_Sec_W  K_ImmoDeactivateOnSec;
extern const FuelPump_Channel_T    K_Immo_FuelPump_channel;
extern const Immo_Option_T         K_Immo_option;
extern const Every_Loop_Sec_B      K_SingleAuthenticationMaxTime;
extern const Every_Loop_Sec_W      K_ImmoAuthenticationClearTime;
extern const EOBD_KPH              K_ImmoByPassVSS;
extern const Every_16th_Loop_Sec_W K_ImmoNoAuthLimit;
extern const uint8_t               KcMyImmoSourceAddr;
extern const uint16_t              KwIMMO_SiemensPreReleaseTime;/* for Siemens Immo*/
extern const uint8_t               KaIMMO_CustomerID[4];
extern const Every_Loop_Sec_W      K_Immo_ECMDelayTime;
/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
\* ============================================================================ */
#endif /* IMMO_CAL_H */
