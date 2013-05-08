#ifndef INJDCALD_H
#define INJDCALD_H
/******************************************************************************
 *
 * Filename:          injdcald.h
 *
 * Description:       Calibration declaration file for Injector Circuits 
 *                    Diagnostic subsystem.
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
 * Copyright 2001-2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#5/incl/injdcald.h/1 %
 * %date_created:   Wed Mar 19 10:11:32 2008 %
 * %version:        1 %
 * %derived_by:     vzp48z %
 *
 *****************************************************************************/

/****************************************************************************** 
*  Include Files 
*****************************************************************************/ 
#include "t_gentypes.h"
#include "timepcvc.h"

/******************************************************************************
*  Calibration Variables
******************************************************************************/
extern const T_RPMa           KfINJD_n_EngSpdThrshLo;
extern const TyTIME_t_R125ms  KfINJD_t_InjCircuitFailThrsh;

#endif 

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
