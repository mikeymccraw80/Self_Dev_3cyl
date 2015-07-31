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
#include "t_gentypes.h"


/* ==========================================================================
 * Calibration declarations for ems side I/O hardware Diagnostic
 * ==========================================================================*/
/* ===========================================================================
 * common diagnostic enable criteria : ignition on time
 * ==========================================================================*/
extern const T_SECONDS            KfEMSD_t_IgnitionOnDelay;
extern const T_SECONDS            KfEMSD_t_MPRDIgnitionOnDelay;

/* ===========================================================================
 * AC Clutch Relay sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_ACCDShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_ACCDShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_ACCDShortSmplThrsh;

/* ===========================================================================
 * Main Power Relay sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_MPRDShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_MPRDShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_MPRDShortSmplThrsh;
/* ===========================================================================
 * Fuel Pump Relay sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_FPRDShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_FPRDShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_FPRDShortSmplThrsh;

/* ===========================================================================
 * MIL sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_MILDShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_MILDShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_MILDShortSmplThrsh;

/* ===========================================================================
 * SVS sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_SVSDShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_SVSDShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_SVSDShortSmplThrsh;

/* ===========================================================================
 * SVS sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_SVSDShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_SVSDShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_SVSDShortSmplThrsh;

/* ===========================================================================
 * GIS sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_GISDShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_GISDShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_GISDShortSmplThrsh;

/* ===========================================================================
 * Fanx sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_FANAShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_FANAShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_FANAShortSmplThrsh;

extern const T_COUNT_WORD         KcEMSD_FANBShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_FANBShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_FANBShortSmplThrsh;

/* ===========================================================================
 * SMR sub-subsystem calibrations export 
 * ==========================================================================*/
extern const T_COUNT_WORD         KcEMSD_SMRShortHiFailThrsh;
extern const T_COUNT_WORD         KcEMSD_SMRShortLoFailThrsh;

extern const T_COUNT_WORD         KcEMSD_SMRShortSmplThrsh;
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

