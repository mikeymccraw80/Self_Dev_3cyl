#ifndef EOSDCALD_H
#define EOSDCALD_H
/******************************************************************************
 *
 * Filename:          eosdcald.h
 *
 * Description:       This is the calibration data header file
 *                    for the Exhaust Oxygen Sensor Diagnostic
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
 * Copyright 1997-2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#8/incl/eosdcald.h/1 %
 * %date_created:  Wed Mar 19 10:10:17 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "t_gentypes.h"


/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/

/* ==========================================================================
 * Calibration declarations for Oxygen Sensor Heater Diagnostic bank1 sensor1
 * ==========================================================================*/
extern const T_COUNT_WORD        KcEOSD_11_HtrShortLowFailThrsh;
extern const T_COUNT_WORD        KcEOSD_11_HtrShortHiFailThrsh;
extern const T_COUNT_WORD        KcEOSD_11_HtrSmplThrsh;
extern const T_COUNT_WORD        KfEOSD_t_11_HtrEngRunThrsh;


/* ==========================================================================
 * Calibration declarations for Oxygen Sensor Heater Diagnostic bank1 sensor2
 * ==========================================================================*/

extern const T_COUNT_WORD        KcEOSD_12_HtrShortLowFailThrsh;
extern const T_COUNT_WORD        KcEOSD_12_HtrShortHiFailThrsh;
extern const T_COUNT_WORD        KcEOSD_12_HtrSmplThrsh;
extern const T_COUNT_WORD        KfEOSD_t_12_HtrEngRunThrsh;


/*****************************************************************************
 *  Function Exports
 *****************************************************************************/

/*****************************************************************************
 *  Function Prototype
 *****************************************************************************/

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
*
******************************************************************************/
