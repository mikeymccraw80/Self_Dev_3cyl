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
#include "condfcfg.h"   /* For COND Local Configuration       */
#include "condfexi.h"   /* For global inputs                  */
#include "condcald.h"   /* For Definition-Declaration check   */
#include "condstyp.h"   /* For COND Local type definitions    */
#include "condptyp.h"   /* For global type definitions        */


#if XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE
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
const T_VOLTb CAL0ADDR KfCOND_U_SystemThrshHi = V_VOLTb(16.0);

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
const T_VOLTb CAL0ADDR KfCOND_U_SystemThrshLo = V_VOLTb(11.0);

/*
*| condcald.{
*|   KaCOND_t_EnableDelayTime {
*|     : is_calconst;
*|     : description = "Time threshold used to indicate sufficient time to "
*| "enable a diagnostic";
*|     : annotation = anns.io_device;
*|     : type = array.array_dim10_seconds;
*|     : units = "milliseconds";
*|   }
*| }
*/
const T_SECONDS CAL0ADDR KaCOND_t_EnableDelayTime[CcCOND_NumOf_IO_Device] =
{

  V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5),
  V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5)
  };

/*
*| condcald.{
*|   KaCOND_Cnt_FailThrsh {
*|     : is_calconst;
*|     : description ="COND fail counter threshold equal to or above "
*| "which a fail is reported to the Data Manager "
*| "Engineering Range: 0 to 255 Resolution: 1 / Count ";
*|     : annotation = anns.io_device;
*|     : type = array.array_dim10_count_byte;
*|     : units = "";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KaCOND_Cnt_FailThrsh[CcCOND_NumOf_IO_Device] =
{
  V_COUNT_BYTE(1), V_COUNT_BYTE(1), V_COUNT_BYTE(1), V_COUNT_BYTE(40), V_COUNT_BYTE(40),
  V_COUNT_BYTE(40), V_COUNT_BYTE(40), V_COUNT_BYTE(40), V_COUNT_BYTE(40),  V_COUNT_BYTE(1)
};

/*
*| condcald.{
*|   KaCOND_Cnt_SampleThrsh {
*|     : is_calconst;
*|     : description ="COND sample counter threshold equal to or above"
*| "which a fail is reported to the Data Manager "
*| "Engineering Range: 0 to 255 Resolution: 1 / Count ";
*|     : annotation = anns.io_device;
*|     : type = array.array_dim10_count_byte;
*|     : units = "";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KaCOND_Cnt_SampleThrsh[CcCOND_NumOf_IO_Device] =
{
  V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80),
  V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80),  V_COUNT_BYTE(80)
};

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
