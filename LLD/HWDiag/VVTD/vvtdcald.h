#ifndef VVTDCALD_H
#define VVTDCALD_H
/******************************************************************************
 *
 * Filename:          vvtdcald.h
 *
 * Description:       Calibration declaration file for VVT 
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
 * %full_name:      mt20u2#5/incl/prgdcald.h/1 %
 * %date_created:   Wed Mar 19 10:12:11 2008 %
 * %version:        1 %
 * %derived_by:     vzp48z %
 *
 *****************************************************************************/

/****************************************************************************** 
*  Include Files 
*****************************************************************************/ 
#include "t_gentypes.h"

extern const T_PERCENTa    KfVVTD_HiBandDCThrsh;
extern const T_PERCENTa    KfVVTD_LoBandDCThrsh;
extern const T_COUNT_WORD  KcVVTD_VVT1OutFailThrsh;
extern const T_COUNT_WORD  KcVVTD_VVT1OutSampleThrsh;
extern const T_COUNT_WORD  KcVVTD_VVT2OutFailThrsh;
extern const T_COUNT_WORD  KcVVTD_VVT2OutSampleThrsh;
extern const T_VOLTb       KfVVTD_U_SystemThrshLo;


#endif 

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
