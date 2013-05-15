/******************************************************************************
 *
 * Filename:          dcancreuse.c
 *
 * Description:       Calibration file for the Reuse CAN sybsystem (DCAN)
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
 * Copyright 2007, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#1/csrc/dcancreuse.c/2 %
 * %date_created:  Mon Jun 16 13:11:29 2008 %
 * %version:       2 %
 * %derived_by:    wzmkk7 %
 *
 *****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/

#include "dcancreuse.h"   /* for definition checking                  */

/* ==========================================================================
 * Calibration declarations for CAN
 * ==========================================================================*/
/*
*| dcancreuse.{
*| KbDCANCORE_MODE4_With_EngRUN {
*|     : is_calconst;
*|     : description = "If KbDCANCORE_MODE4_With_EngRUN = True, then "
*|                     "Mode-0x04 Code Clear in Engine State = Run. "
*|                     "If KbDCANCORE_MODE4_With_EngRUN = False, Mode-0x04 "
*|                     "Code Clear is not allowed in Engine State = Run. "
*|                     "Mode-0x04 Code Clear is always allowed when Engine "
*|                     "State <> Run.";
*|     : type = enum.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const TbBOOLEAN   CAL0ADDR KbDCANCORE_MODE4_With_EngRUN = CbTRUE;


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*  1    070611 hdb 6346 Created module.
*
******************************************************************************/

