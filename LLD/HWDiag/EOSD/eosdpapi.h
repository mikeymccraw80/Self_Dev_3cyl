#ifndef EOSDPAPI_H
#define EOSDPAPI_H
/******************************************************************************
 *
 * Filename:          eosdpapi.h
 *
 * Description:       This is the public header file for
 *                    the Oxygen Sensor diagnostics.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 * 
 *
 * Forward Engine Management Systems
 *
 * Copyright 1997-2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     %
 * %date_created:  %
 * %version:       %
 * %derived_by:    %
 *
 *****************************************************************************/

/******************************************************************************
 *  Include Files
 *****************************************************************************/

/******************************************************************************
 * Include Files
 *****************************************************************************/
#include "t_gentypes.h" /* For global data types            */

/******************************************************************************
 *  Function Exports
 *****************************************************************************/


/******************************************************************************
 *  Function Prototype
 *****************************************************************************/


void MngEOSD_O2_11_Htr781msTasks (void);
void MngEOSD_O2_11_Htr125msTasks (void);

void MngEOSD_O2_12_Htr781msTasks (void);
void MngEOSD_O2_12_Htr125msTasks (void);

void InitEOSD_O2_11_HtrRstToKeyOff (void);
void InitEOSD_O2_12_HtrRstToKeyOff (void);


#endif    /* #define EOSDPAPI_H                       */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
