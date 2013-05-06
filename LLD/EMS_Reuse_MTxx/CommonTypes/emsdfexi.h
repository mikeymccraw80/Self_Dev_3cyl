#ifndef EMSDFEXI_H
#define EMSDFEXI_H
/******************************************************************************
 *
 * Filename:          emsdfexi.h
 *
 * Description:       This header file defines all necessary input resources
 *                    for EMSD subsystem. In order to prevent private subsystem
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
 * Copyright 2005 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/incl/emsdfexi.h/2 %
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

/******************************************************************************
 *  Library Include Files
 *****************************************************************************/
#include "mall_lib.h"
/*****************************************************************************
 *  Application Include Files
 *****************************************************************************/
#include "intr_ems.h"
#include "dd_boot.h" /* for BootLoaderFlag.FlashEepromCorrupted */
#include "v_mpr.h"

/******************************************************************************
* Global Data
******************************************************************************/
/*****************************************************************************
 *  Global Data Define
 *****************************************************************************/

/******************************************************************************
* Compiler option used to support linking of EMSD without EMS. This section
* defines interfaces with default value
* By Default disable the option is disabled.
* For Interface not existing in EMS move definition in else part of
* EOBD_NON_EMS_BUILD compiler option.
******************************************************************************/
#define EOBD_NON_EMS_BUILD_ACCD
#ifdef  EOBD_NON_EMS_BUILD_ACCD

#define GEAR_SEL_ETCU_FAULT   ( 6 )

#define GetVIOS_t_IgnOnTime()                 (IgnitionOn_Time_)
#define GetVIOS_MainPwrRly_Status()           (IsMPRPresent() ? CbTRUE : CbTRUE)
/******************************************************************************
 * ATD  reading for font AC Evaporator diagnostic 
 ******************************************************************************/
#define GetVIOS_FrntACEVT_Presnt()           (true)          
#define GetVIOS_Pct_RawFrntACEVTIn()         (ATD_buffer[AD_FRONT_EVAP_TEMPERATURE_TYPE])
/******************************************************************************
 * ATD  reading for rear AC Evaporator diagnostic 
 ******************************************************************************/
#define GetVIOS_RearACEVT_Presnt()           (true)          
#define GetVIOS_Pct_RawRearACEVTIn()         (ATD_buffer[AD_REAR_EVAP_TEMPERATURE_TYPE])

#endif
#endif /* EOSDFEXI_H */
