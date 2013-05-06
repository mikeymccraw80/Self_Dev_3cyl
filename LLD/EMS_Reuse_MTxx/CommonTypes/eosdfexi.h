#ifndef EOSDFEXI_H
#define EOSDFEXI_H
/******************************************************************************
 *
 * Filename:          eosdfexi.h
 *
 * Description:       This header file defines all necessary input resources
 *                    for EOSD subsystem. In order to prevent private subsystem
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
 * %full_name:     mt20u2#8/incl/eosdfexi.h/2 %
 * %date_created:  Wed Mar 19 10:16:48 2008 %
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
#include "timepcvc.h" /* R500ms, TwTIME_t_R500ms                     */
#include "bit_lib.h"  /* GetBIT_InArry, SetBIT_InArry, ClrBIT_InArry */

/******************************************************************************
 *  Library Include Files
 *****************************************************************************/
#include "mall_lib.h"

/*****************************************************************************
 *  Application Include Files
 *****************************************************************************/

#include "intr_ems.h"


/******************************************************************************
* Global Data
******************************************************************************/



/******************************************************************************
* Compiler option used to support linking of EOBD without EMS. This section
* defines interfaces with default value
* By Default disable the option is disabled.
* For Interface not existing in EMS move definition in else part of
* EOBD_NON_EMS_BUILD compiler option.
******************************************************************************/
#define GetOSSP_O2_DiagCntrDsbl()        (CbFALSE)
#define GetVIOS_O2HEATER_PowerOK()       (GetPowerOK(O2Heater))


#endif /* EOSDFEXI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
