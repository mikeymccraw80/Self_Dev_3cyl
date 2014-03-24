/******************************************************************************
 *
 * Filename:          condcald.c
 *
 * Description:       Process Sequence Diagnostic for Master CPU
 *                    Calibration definitions
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
 * Copyright 1999-2007, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#3/csrc/condcald.c/5 %
 * %date_created:  Mon Aug 31 15:49:33 2009 %
 * %version:       5 %
 * %derived_by:    wzmkk7 %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Include Files                                                            *
 *****************************************************************************/
#include "condcald.h" /* For Generic data types                            */

/*
*| condcald.{
*|   KfCOND_U_SystemThrshHi {
*|     : is_calconst;
*|     : description ="System voltage high threshold below which the diagnostic "
*| "test will be disabled";
*|     : type = fixed.t_voltb;
*|     : units = "volts";
*|   }
*| }
*/
const T_VOLTb KfCOND_U_SystemThrshHi = V_VOLTb(16.0);

/*
*| condcald.{
*|   KfCOND_U_SystemThrshLo {
*|     : is_calconst;
*|     : description ="System voltage low threshold below which the diagnostic "
*| "test will be disabled";
*|     : type = fixed.t_voltb;
*|     : units = "volts";
*|   }
*| }
*/
const T_VOLTb KfCOND_U_SystemThrshLo = V_VOLTb(11.0);


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
