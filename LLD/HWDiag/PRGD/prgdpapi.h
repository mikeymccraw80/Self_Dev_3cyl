#ifndef PRGDPAPI_H
#define PRGDPAPI_H
/******************************************************************************
 *
 * Filename:          prgdpapi.h
 *
 * Description:       AC Pressure Short Diagnostic Diagnostic subsystem
 *                    API interface  file
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    GetPRGD_AC_PresShortTestStatReported
 *
 * Forward Engine Management Systems
 *
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#5/incl/prgdpapi.h/1 %
 * %date_created:   Wed Mar 19 10:12:12 2008 %
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

void MngPRGD_Purge_125msTasks(void);
void InitPRGD_Purge_RstToKeyOff(void);


#endif /*PRGDPAPI_H*/

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
