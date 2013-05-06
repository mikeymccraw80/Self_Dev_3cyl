#ifndef KNODFEXI_H
#define KNODFEXI_H
/******************************************************************************
 *
 * Filename:          knodfexi.h
 *
 * Description:       This header file defines all necessary input resources
 *                    for KNOD subsystem. In order to prevent private subsystem
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
 * %full_name:     mt20u2#7/incl/knodfexi.h/2 %
 * %date_created:  Wed Mar 19 10:16:54 2008 %
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
#include "mall_lib.h"
/*****************************************************************************
 *  Application Include Files
 *****************************************************************************/

#include "intr_ems.h"

#include "lookup.h"

//#define GetVIOS_9a_RPM_Rescale() \
 //        ( usLookup_Rescale_xy_us ( &CsRSCL_MAP09_n_RPMa, \
 //                                   GetVIOS_n_EngSpd() ) )

#define GetVIOS_CylNumZeroBased()       (GetVIOS_CylNum())

#define GetVIOS_KNKD_Disable_Fault()            GetKNKD_Disable_Fault()
#define GetVIOS_CCESC_Enabled()            GetVIOS_CCESC_Enabled_EMS()

#define GetVIOS_Pct_CCESC_IntUnfilt(x)     GetVIOS_Pct_CCESC_IntUnfilt_EMS(x)
#define GetVIOS_Pct_CCESC_IntensAverage(x) GetVIOS_Pct_CCESC_IntensAverage_EMS(x)


/******************************************************************************
* GLobal Data 
******************************************************************************/


#endif /* KNODFEXI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
