#ifndef INJDPAPI_H
#define INJDPAPI_H
/******************************************************************************
 *
 * Filename:          injdpapi.h
 *
 * Description:       Injector Circuits Diagnostic subsystem
 *                    API interface  file
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *
 *
 * Forward Engine Management Systems
 *
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:       mt20u2#5/incl/injdpapi.h/1 %
 * %date_created:    Wed Mar 19 10:11:35 2008 %
 * %version:         1 %
 * %derived_by:      vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
Include Files
 *****************************************************************************/

/******************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/

/******************************************************************************
 *  Diagnostic Execution ID Definitions (used by DDMS)
 *****************************************************************************/
void MngINJD_125msTasks(void);
void InitINJD_RstToKeyOn(void);


/*****************************************************************************
 *  Function Exports
 *****************************************************************************/


#endif /*INJDPAPI_H*/

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/