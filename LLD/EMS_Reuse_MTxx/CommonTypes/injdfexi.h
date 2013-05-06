#ifndef INJDFEXI_H
#define INJDFEXI_H
/******************************************************************************
 *
 * Filename:          injdfexi.h
 *
 * Description:       This header file defines all necessary input resources
 *                    for INJD subsystem. In order to prevent private subsystem
 *                    files from modifications due to input name changes
 *                    all input remaping should be done solely in this file.
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
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/incl/injdfexi.h/2 %
 * %date_created:  Wed Mar 19 10:16:52 2008 %
 * %version:       2 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
 *  System Include Files
 *****************************************************************************/

#include "t_gentypes.h"


/*****************************************************************************
 *  Utility Include Files
 *****************************************************************************/
#include "timclib.h"  /* DefTIMC_StopWatches16                       */

/******************************************************************************
 *  Library Include Files
 *****************************************************************************/

/*****************************************************************************
 *  Application Include Files
 *****************************************************************************/
  #include "intr_ems.h"

/*****************************************************************************
 *  Global Data Define
 *****************************************************************************/


#define GetAPI_InjHW_EnblCondMet()  (CbTRUE)


#endif /* INJDFEXI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
