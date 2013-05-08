#ifndef PRGDCALD_H
#define PRGDCALD_H
/******************************************************************************
 *
 * Filename:          prgdcald.h
 *
 * Description:       Calibration declaration file for Canister Purge 
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

extern const T_PERCENTa    KfPRGD_HiBandDCThrsh;
extern const T_PERCENTa    KfPRGD_LoBandDCThrsh;
extern const T_COUNT_WORD  KcPRGD_PurgeOutFailThrsh;
extern const T_COUNT_WORD  KcPRGD_PurgeOutSampleThrsh;
extern const T_VOLTb       KfPRGD_U_SystemThrshLo;


#endif 

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
