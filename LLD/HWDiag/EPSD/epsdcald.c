/******************************************************************************
 *
 * Filename:          epsdcald.c
 *
 * Description:                Calibration file for Crank and Cam modules
 *                             of the Engine Performance Sensing Diagnostic
 *                             (EPSD) subsystem
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
 * Copyright 1996-2003, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#8/csrc/epsdcald.c/1 %
 * %date_created:   Wed Mar 19 10:10:28 2008 %
 * %version:        1 %
 * %derived_by:     vzp48z %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Include Files
 *****************************************************************************/
#include "epsdcald.h" /* For EPSD Calibration Definition-Declaration check */

/*****************************************************************************
 *   Crank Calibration module
 *****************************************************************************/
/*
*| epsdcald.{
*|   KcEPSD_CrankToothErrFailThrsh {
*|     : is_calconst;
*|     : description = "Number of missing or more teeth accepted without "
*| "setting an error flag "
*| "Engineering Range: 0 to 65535  Resolution: 1 count / Count";
*|     : type = fixed.epsd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcEPSD_CrankToothErrFailThrsh = V_COUNT_WORD (3);

/*
*| epsdcald.{
*|   KcEPSD_CrankNoisySigFailThrsh {
*|     : is_calconst;
*|     : description = "Number of Fails from noisy crank diagnostic "
*| "before failure is reported "
*| "Engineering Range: 0 to 65535  Resolution: 1 count / Count";
*|     : type = fixed.epsd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcEPSD_CrankNoisySigFailThrsh = V_COUNT_WORD(10);

/*
*| epsdcald.{
*|   KcEPSD_CrankNoisySigSampleThrsh {
*|     : is_calconst;
*|     : description = "Number of total revolutions for diagnostic "
*| "Engineering Range: 0 to 65535  Resolution: 1 count / Count";
*|     : type = fixed.epsd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcEPSD_CrankNoisySigSampleThrsh = V_COUNT_WORD(100);

/*
*| epsdcald.{
*|   KfEPSD_p_CrankDeltaMAP_Thrsh {
*|     : is_calconst;
*|     : description ="Delta MAP threshold to detect that you are cranking. "
*| "This is used as an enabling criteria for the Crank_No_Signal "
*| "test for appls without a CAM sensor ";
*|     : type = fixed.epsd_t_kpaa;
*|     : units = "kpa";
*|   }
*| }
*/
const T_KPAa  KfEPSD_p_CrankDeltaMAP_Thrsh = V_KPAa (10);

/*
*| epsdcald.{
*|   KfEPSD_t_CrankNoSignalTmr {
*|     : is_calconst;
*|     : description = "A Crank_No_Signal fault will be active for this "
*| "amount of time before reporting a failure to the Data Manager "
*| "Engineering Range: 0 to 511.99218750 s  Resolution: 0.0078125 s / Count ";
*|     : type = fixed.epsd_t_w_R7p8125ms;
*|     : units = "seconds";
*|   }
*| }
*/
const TwTIME_t_R7p8125ms  KfEPSD_t_CrankNoSignalTmr = C_R7p8125ms16 (0.0625);

/*
*| epsdcald.{
*|   KfEPSD_U_CrankDeltaIgnThrsh {
*|     : is_calconst;
*|     : description ="Delta ignition voltage threshold to detect "
*| "that you are cranking. This is used as an enabling criteria "
*| "for the Crank_No_Signal test for applications "
*| "without a CAM sensor "
*| "Engineering Range: 0 to 31.99951172 v  Resolution: 0.000488281 v / Count ";
*|     : type = fixed.epsd_t_voltb;
*|     : units = "volt";
*|   }
*| }
*/
const T_VOLTb  KfEPSD_U_CrankDeltaIgnThrsh = V_VOLTb (2);

/*****************************************************************************
 *   Cam Calibration module
 *****************************************************************************/
/*
*| epsdcald.{
*|   KcEPSD_CamNoSignalCylEvent {
*|     : is_calconst;
*|     : description = "Threshold for the number of cylinder events "
*| "without a Cam signal before reporting a failure to the Data Manager "
*| "Engineering Range: 0 to 65535  Resolution: 1 count / Count";
*|     : type = fixed.epsd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcEPSD_CamNoSignalCylEvent = V_COUNT_WORD (10);

/*
*| epsdcald.{
*|   KcEPSD_CamRationalityFailThrsh {
*|     : is_calconst;
*|     : description = "The number of cylinder events threshold "
*| "equal to or above which the Cam Rationality test will report "
*| "a failure to the Data Manager "
*| "Engineering Range: 0 to 65535  Resolution: 1 count / Count";
*|     : type = fixed.epsd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcEPSD_CamRationalityFailThrsh = V_COUNT_WORD (50);

/*
*| epsdcald.{
*|   KcEPSD_CamRationalityPassThrsh {
*|     : is_calconst;
*|     : description = "The number of cylinder events threshold "
*| "equal to or above which the Cam Rationality test will report "
*| "a pass to the Data Manager "
*| "Engineering Range: 0 to 65535  Resolution: 1 count / Count";
*|     : type = fixed.epsd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcEPSD_CamRationalityPassThrsh = V_COUNT_WORD (100);

/*
*| epsdcald.{
*|   KfEPSD_t_CrankNoSignalResetThrs {
*|     : is_calconst;
*|     : description = "Threshold for prevention of noise being detected"
*| "as a crank sensor fault during a long key-on without engine being started."
*| "Engineering Range: 0 to 511.99218750 s Resolution: 0.007812500 s / Count ";
*|     : type = fixed.epsd_t_w_R7p8125ms;
*|     : units = "seconds";
*|   }
*| }
*/
const TwTIME_t_R7p8125ms  KfEPSD_t_CrankNoSignalResetThrs = C_R7p8125ms16 (2.0);


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
