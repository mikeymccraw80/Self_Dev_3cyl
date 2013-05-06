#ifndef EPSDFEXI_H
#define EPSDFEXI_H
/******************************************************************************
 *
 * Filename:          epsdfexi.h
 *
 * Description:       This header file defines all necessary input resources
 *                    for EPSD subsystem. In order to prevent private subsystem
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
 * Copyright 2003, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#7/incl/epsdfexi.h/2 %
 * %date_created:  Wed Mar 19 10:16:49 2008 %
 * %version:        2 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
 *  System Include Files
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h"

/*****************************************************************************
 *  Utility Include Files
 *****************************************************************************/
#include "timclib.h"  /* DefTIMC_StopWatches16                       */

/******************************************************************************
 *  Library Include Files
 *****************************************************************************/
#include "intr_ems.h"

/*****************************************************************************
 *  Application Include Files
 *****************************************************************************/

/*****************************************************************************
 *  Global external Data
 *****************************************************************************/

/******************************************************************************
* Compiler option used to support linking of EOBD without EMS. This section
* defines interfaces with default value
* By Default disable the option is disabled.
* For Interface not existing in EMS move definition in else part of
* EOBD_NON_EMS_BUILD compiler option.
******************************************************************************/
#define GetBNDL_DiagCamActFaultPresent() (CbFALSE)
#define GetVIOS_CAM_CrankBackupActive() (CbFALSE)

#endif /* ECTDFEXI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
