/******************************************************************************
 *
 * Filename:          vvtdcald.c
 *
 * Description:       Calibration file for AC Pressure 
 *                    Short Diagnostic subsystem.
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
 * Copyright 1996-2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#5/csrc/prgdcald.c/1 %
 * %date_created:   Wed Mar 19 10:12:10 2008 %
 * %version:        1 %
 * %derived_by:     vzp48z %
 *
 *****************************************************************************/

/****************************************************************************** 
*  Include Files 
*****************************************************************************/ 
#include "vvtdcald.h"   /* For Definition-Declaration check   */

/*****************************************************************************
 *  Calibration declarations for Purge
 *****************************************************************************/
/*
*| vvtdcald.{
*|   KfVVTD_HiBandDCThrsh {
*|     : is_calconst;
*|     : description ="DC above which the diagnostic will be enabled and the"
*| "State 2 flag gets set";
*|     : type = fixed.vvtd_t_percenta;
*|     : units = "percent";
*|   }
*| }
*/
const T_PERCENTa  KfVVTD_HiBandDCThrsh = V_PERCENTa (100);

/*
*| vvtdcald.{
*|   KfVVTD_LoBandDCThrsh {
*|     : is_calconst;
*|     : description ="DC below which the diagnostic will be enabled and the"
*| "State 1 flag gets set";
*|     : type = fixed.vvtd_t_percenta;
*|     : units = "percent";
*|   }
*| }
*/
const T_PERCENTa  KfVVTD_LoBandDCThrsh = V_PERCENTa (0);

/*
*| vvtdcald.{
*|   KcVVTD_VVT1OutFailThrsh {
*|     : is_calconst;
*|     : description ="Indicates the number of samples that can register a"
*| "failure before a fault is set for the driver output";
*|     : type = fixed.vvtd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcVVTD_VVT1OutFailThrsh = V_COUNT_WORD (10);

/*
*| vvtdcald.{
*|   KcVVTD_VVT2OutFailThrsh {
*|     : is_calconst;
*|     : description ="Indicates the number of samples that can register a"
*| "failure before a fault is set for the driver output";
*|     : type = fixed.vvtd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcVVTD_VVT2OutFailThrsh = V_COUNT_WORD (10);

/*
*| vvtdcald.{
*|   KcVVTD_VVT1OutSampleThrsh {
*|     : is_calconst;
*|     : description ="Indicates the number of samples taken before a "
*| "passing result can be reported to the Data Manager";
*|     : type = fixed.vvtd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcVVTD_VVT1OutSampleThrsh = V_COUNT_WORD (20);

/*
*| vvtdcald.{
*|   KcVVTD_VVT2OutSampleThrsh {
*|     : is_calconst;
*|     : description ="Indicates the number of samples taken before a "
*| "passing result can be reported to the Data Manager";
*|     : type = fixed.vvtd_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcVVTD_VVT2OutSampleThrsh = V_COUNT_WORD (20);

/*
*| vvtdcald.{
*|   KfVVTD_U_SystemThrshLo {
*|     : is_calconst;
*|     : description ="This parameter indicates the threshold above which"
*| "the ignition voltage has to be in order to enable the diagnostic";
*|     : type = fixed.vvtd_t_voltb;
*|     : units = "count";
*|   }
*| }
*/
const T_VOLTb  KfVVTD_U_SystemThrshLo = V_VOLTb (11);

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
