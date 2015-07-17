#ifndef KNODPAPI_H
#define KNODPAPI_H
/******************************************************************************
 *
 * Filename:          knodpapi.h
 *
 * Description:       AC Pressure Short Diagnostic Diagnostic subsystem
 *                    API interface  file
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    GetKNOD_AC_PresShortTestStatReported
 *
 * Forward Engine Management Systems
 *
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#8/incl/knodpapi.h/1 %
 * %date_created:   Wed Mar 19 10:11:41 2008 %
 * %version:        1 %
 * %derived_by:     vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
Include Files
 *****************************************************************************/

/******************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h" /* For Global Data Type Information */

/*********************************************************************
* exported functions
**********************************************************************/
void MngKNKD_125msTasks(void);
void MngKNKD_CylEventTasks(void);
 void InitKNKD_RstToKeyOn(void);

/*********************************************************************
* Exports
*********************************************************************/


#endif /*KNODPAPI_H*/

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
