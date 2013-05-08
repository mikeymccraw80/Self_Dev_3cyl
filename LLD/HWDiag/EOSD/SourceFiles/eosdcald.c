/******************************************************************************
 *
 * Filename:          eosdcald.c
 *
 * Description:       Calibration file for Exhaust Oxygen Sensor
 *                    Diagnostic (EOSD) subsystem
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
 * %full_name:     mt20u2#8/csrc/eosdcald.c/1 %
 * %date_created:  Wed Mar 19 10:10:17 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "eosdfexi.h" /* For external interfaces              */
#include "eosdcald.h" /* Forced declaration definition check  */




/*  =========================================================================
 *  Data for Oxygen Sensor Heater Diagnostic bank1 sensor1
 *  =========================================================================*/

/*===========================================================================*/

/* O2 Heater Current Fault sample determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| eosdcald.{
*|   KcEOSD_11_HtrShortLowFailThrsh {
*|     : is_calconst ;
*|     : description = "O2 Heater PSVI Fault sample determination "
*| "counter threshhold equal to or above which a failure is "
*| "reported to the Data Manager.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD     CAL0ADDR KcEOSD_11_HtrShortLowFailThrsh = V_COUNT_WORD (10) ;

/*===========================================================================*/

/* O2 Heater Current Fault sample determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| eosdcald.{
*|   KcEOSD_11_HtrShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "O2 Heater PSVI Fault sample determination "
*| "counter threshhold equal to or above which a failure is "
*| "reported to the Data Manager.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD     CAL0ADDR KcEOSD_11_HtrShortHiFailThrsh = V_COUNT_WORD (10) ;


/*===========================================================================*/

/* O2 Heater Current sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| eosdcald.{
*|   KcEOSD_11_HtrSmplThrsh {
*|     : is_calconst ;
*|     : description = "O2 Heater PSVI sample counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD   CAL0ADDR   KcEOSD_11_HtrSmplThrsh = V_COUNT_WORD (20) ;

/*===========================================================================*/

/* In normal operation, the heater current will decay to a steady
 * value and remain there if the heater is functioning properly.
 * This calibration is the engine run time required for the current
 * to reach a steady state. */
/*
*| eosdcald.{
*|   KfEOSD_t_11_HtrEngRunThrsh {
*|     : is_calconst ;
*|     : description = "In normal operation, the heater current will decay "
*| "to a steady value after initial heater power is on and remain there if the "
*| "heater is functioning properly. This calibration is the engine run time "
*| "required for the current to reach a steady state.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "seconds" ;
*|   }
*| }
*/
const T_COUNT_WORD  CAL0ADDR    KfEOSD_t_11_HtrEngRunThrsh = V_COUNT_WORD (10) ;


/*  =========================================================================
 *  Data for Oxygen Sensor Heater Diagnostic bank1 sensor2
 *  =========================================================================*/

/*===========================================================================*/
/* O2 Heater Current Fault sample determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| eosdcald.{
*|   KcEOSD_12_HtrShortLowFailThrsh {
*|     : is_calconst ;
*|     : description = "O2 Heater PSVI Fault sample determination "
*| "counter threshhold equal to or above which a failure is "
*| "reported to the Data Manager.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD   CAL0ADDR   KcEOSD_12_HtrShortLowFailThrsh = V_COUNT_WORD (10) ;

/*===========================================================================*/
/* O2 Heater Current Fault sample determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| eosdcald.{
*|   KcEOSD_12_HtrShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "O2 Heater PSVI Fault sample determination "
*| "counter threshhold equal to or above which a failure is "
*| "reported to the Data Manager.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD   CAL0ADDR   KcEOSD_12_HtrShortHiFailThrsh = V_COUNT_WORD (10) ;
/*===========================================================================*/

/* O2 Heater Current sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| eosdcald.{
*|   KcEOSD_12_HtrSmplThrsh {
*|     : is_calconst ;
*|     : description = "O2 Heater PSVI sample counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD  CAL0ADDR    KcEOSD_12_HtrSmplThrsh = V_COUNT_WORD (20) ;
/*===========================================================================*/

/* In normal operation, the heater current will decay to a steady
 * value and remain there if the heater is functioning properly.
 * This calibration is the engine run time required for the current
 * to reach a steady state. */
/*
*| eosdcald.{
*|   KfEOSD_t_12_HtrEngRunThrsh {
*|     : is_calconst ;
*|     : description = "In normal operation, the heater current will decay "
*| "to a steady value after power up and remain there if the heater is functioning "
*| "properly. This calibration is the engine run time required for "
*| "the current to reach a steady state.";
*|     : type = fixed.eosd_t_count_word ;
*|     : units = "seconds" ;
*|   }
*| }
*/
const T_COUNT_WORD   CAL0ADDR   KfEOSD_t_12_HtrEngRunThrsh = V_COUNT_WORD (10) ;



/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
*
******************************************************************************/
