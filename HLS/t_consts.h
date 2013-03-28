#ifndef T_CONSTS_H
#define T_CONSTS_H

/*****************************************************************************
* Filename:           t_consts.h
*
* Description:        This is the public header file for global constants
*
* List of function(s):
*
* List of Inlines:
*
* C Software Project FEMS
* (c) Copyright Delco Electronics  1996
*****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"
#include "t_fixed.h"
#include "t_scaled.h"
#include "t_tables.h"
#include "t_user.h"

/*****************************************************************************
 *  GMPT Library Include Files
 *****************************************************************************/

/*****************************************************************************
 *  Global Constants
 *****************************************************************************/
#define CwENGN_AbsTempConst     273
#define CfENGN_GasConstForAir   0.2870
#define CwONE_HUNDRED_PCT       99.99
#define CwINT_DELAY_PARAM       4

#define CwONE                   1
#define CwTWO                   2
#define CwEIGHT                 8
#define CwEIGHTY               80
#define CwNINETY_FIVE          95
#define CwONE_HUNDRED         100
#define CwONE_THOUSAND       1000

#define CwINT_DELAY_PARAM       4    /* integrator delay parameter  */
#define CwIDLE_CL_FLOW         150   /* Closed loop flow when idle  */
#define CwCL_FLOW_MAX          100   /* Closed loop flow maximum value */

#define CwCCP_MinOutFreq      10.5   /* Canister Purge output frequency */
#define CwCCP_DC_ActFreq       16    /* Canister Purge Activation Frequency
                                        which is the inverse of the Activation
                                        rate(62.5ms) */

#define PI            V_UW_14(3.14161)

#define CbHWIO_InDscrt_CruiseCancelActive CbTRUE /* HWIO cruise cancel active
                                                    dummy */

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 0.1   960514 sai      Created module
* 1.1   971104 blt 0249 API cleanup
* 1.18  980112 pdb 0345 Implement Crankshaft Misfire Diagnostic
*                        -Changed Max number of cylinders to 8 for misfire
*                         and tooth error correction diagnostics
* 1.20  980218 raw 0409 Add 8 cyl capability
* 1.20  980511 blt 0486 Merge offline partition node 024 into Lecc node 278
*
* -- Core Revision History: --
*
* 1.3   980720 arr 0005 Removed CwMAX_CYL as CcSYST_MAXCYLS will be used
*                       through-out the code instead.
*
* (Merge in lecc node 326)
*
* 1.4   980720 lq  0598 Added CwCCP_MinOutFreq and CwCCP_DC_ActFreq
*
* (End merge)
*
* 1.5   990204 arr 0149 Merged in LECC node 375 containing the following
*                       change(s):
*       981013 blt 0707 Added HWIO call for Cruise Input Diagnostic
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   010312 woz 1228 Moved PI definition here from torqmdes.c.
* 1.3   010831 caw 1248 Changed CwIDLE_CL_FLOW from 96 to 150.
*                       Changed CwCL_FLOW_MAX from 80 to 100.
* 1.4 011203 mhb 1527   Added CwRO2_MODE_NUM = 6
*  
******************************************************************************/
/*
* $Source: common@brighton.tcb:core_dc2:t_consts.h $
* $Revision: 1.4 $
* $Author: brighton.tcb:/users/c23mhb/dsds/current_core:c23mhb $
*/

