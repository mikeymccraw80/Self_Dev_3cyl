/******************************************************************************
 *
 * Filename:          candcald.c
 *
 * Description:       CAN diagnostic calibration file
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
 * Copyright 2001-2002, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/******************************************************************************
 *  Subsystem Include Files
 *****************************************************************************/
#include "candcald.h"  /*  For force Def-Dec check  */
#include "candpapi.h"  /*  For force Def-Dec check  */


/*
*| candcald.{
*|   KcCAND_FailThrsh {
*|     : is_calconst;
*|     : description ="The number of samples that can register a failure\
*|  before a fault is set for the SIDM diagnostic.";
*|     : type = fixed.cand_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcCAND_FailThrsh = V_COUNT_WORD (20) ;

/*
*| candcald.{
*|   KcCAND_SampleThrsh {
*|     : is_calconst;
*|     : description ="The number of samples that are needed to register\
*|  a pass for the TCM ECM communication diagnostic.";
*|     : type = fixed.cand_t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD  KcCAND_SampleThrsh = V_COUNT_WORD (30) ;

/*
*| candcald.{
*|   KfCAND_t_CommEngRunThrsh {
*|     : is_calconst;
*|     : description ="Engine run time must be equal or greater than\
*|  this calibration to enable the ECM TCM communication diagnostic";
*|     : type = fixed.cand_t_count_word;
*|     : units = "seconds";
*|   }
*| }
*/
const T_COUNT_WORD  KfCAND_t_CommEngRunThrsh = V_COUNT_WORD(2.0);

/*
*| candcald.{
*|   KfCAND_U_CommSystemThrshLo {
*|     : is_calconst;
*|     : description ="This parameter indicates the threshold above which\
*|  the ignition voltage has to be in order to enable the ECM TCM diagnostic";
*|     : type = fixed.cand_t_voltb;
*|     : units = "volts";
*|   }
*| }
*/
const T_VOLTb  KfCAND_U_CommSystemThrshLo = V_VOLTb (11.0) ;
