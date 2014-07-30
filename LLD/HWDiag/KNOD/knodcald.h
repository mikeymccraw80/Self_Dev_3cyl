#ifndef KNKDCALD_H
#define KNKDCALD_H
/******************************************************************************
 *
 * Filename:          knodcald.h
 *
 *  Description:         OBDII Knock Sensor Circuit and DSNEF Calibration 
 *                       export header file.
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
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#8/incl/knodcald.h/1 %
 * %date_created:  Wed Mar 19 10:11:39 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
*  Include Files 
*****************************************************************************/ 
#include "t_gentypes.h"
#include "intr_ems.h"

extern const T_COUNT_BYTE KcKNKD_SystemFailLoThrsh;

extern const T_COUNT_BYTE KcKNKD_SystemFailHiThrsh;

extern const T_COUNT_BYTE KcKNKD_SystemSampleThrsh;

extern const T_COUNT_BYTE KcKNKD_SensorFailThrsh;

extern const T_COUNT_BYTE KcKNKD_SensorSampleThrsh;

extern const T_PERCENTa   KfKNKD_Pct_SystemIntensThrshLo;

extern const T_PERCENTa   KfKNKD_Pct_SystemIntnsAvThrshHi;

extern const T_PERCENTa   KfKNKD_Pct_SensorIntnsDeltThrsh;

extern const T_RPMa       KfKNKD_n_EngSpdSystemEnblThrsh;

extern const T_RPMa       KfKNKD_n_EngSpdSensorEnblThrsh;

extern const kPa_W_EOBD      KtKNKD_p_EngVacThrsh[9];
#endif

/******************************************************************************
*
* Revision history: 
*
* Rev.  YYMMDD Who RSM# Changes                                       
* ----- ------ --- ---- -------------------------------------------------------
* 
*******************************************************************************/
