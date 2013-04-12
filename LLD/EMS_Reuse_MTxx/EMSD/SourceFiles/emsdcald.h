#ifndef EMSDCALD_H
#define EMSDCALD_H
/******************************************************************************
 *
 * Filename:          emsdcald.h
 *
 * Description:       This is the calibration data header file
 *                    for the ems side I/O hardware Diagnostic
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
 * Copyright 1997-2005 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/incl/emsdcald.h/1 %
 * %date_created:  Wed Mar 19 10:10:01 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "emsdfexi.h" /* For external interfaces              */


/* ==========================================================================
 * Calibration declarations for ems side I/O hardware Diagnostic
 * ==========================================================================*/
/* ===========================================================================
 * common diagnostic enable criteria : ignition on time
 * ==========================================================================*/
extern const T_SECONDS        CAL0ADDR    KfEMSD_t_IgnitionOnDelay;
extern const T_SECONDS        CAL0ADDR    KfEMSD_t_MPRDIgnitionOnDelay;

/* ===========================================================================
 * AC Clutch Relay sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_ACCDShortHiFailThrsh;
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_ACCDShortLoFailThrsh;

extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_ACCDShortSmplThrsh;

/* ===========================================================================
 * Main Power Relay sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_MPRDShortHiFailThrsh;
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_MPRDShortLoFailThrsh;

extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_MPRDShortSmplThrsh;
/* ===========================================================================
 * Fuel Pump Relay sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FPRDShortHiFailThrsh;
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FPRDShortLoFailThrsh;

extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FPRDShortSmplThrsh;

/* ===========================================================================
 * MIL sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_MILDShortHiFailThrsh;
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_MILDShortLoFailThrsh;

extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_MILDShortSmplThrsh;


/* ===========================================================================
 * Fanx sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FANAShortHiFailThrsh;
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FANAShortLoFailThrsh;

extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FANAShortSmplThrsh;

extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FANBShortHiFailThrsh;
extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FANBShortLoFailThrsh;

extern const T_COUNT_WORD     CAL0ADDR    KcEMSD_FANBShortSmplThrsh;

/*****************************************************************************
 *  Function Exports
 *****************************************************************************/

#endif

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *		  
\* ============================================================================ */

