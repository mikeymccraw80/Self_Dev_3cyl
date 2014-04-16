#ifndef CONDPTYP_H
#define CONDPTYP_H
/******************************************************************************
 *
 * Filename:          condptyp.h
 *
 * Description:       This is the public type hearder file for
 *                    Controller Diagnostic Sybsystem.
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
 * Copyright 2004-2011, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tci_pt3#1/incl/condptyp.h/kok_pt2#4.8 %
 * %date_created:  Mon Jun 20 15:27:27 2011 %
 * %version:       kok_pt2#4.8 %
 * %derived_by:    xzw1q8 %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Type defines                                                             *
 *****************************************************************************/

/******************************************************************************
 *  Configuration Include File
 *****************************************************************************/
#include "t_gentypes.h" /* For Generic data types                            */

/*****************************************************************************
 * Fixed Point Type Definitions
 ****************************************************************************/
/* Res:   0.0002441406250           */
/* Range: [0, 16)                   */
/* Size:  2B                        */
typedef T_W_RANGE_0_16                   T_COND_TIME_SEC_0_16;
#define V_COND_TIME_SEC_0_16(val)        V_W_RANGE_0_16(val)
#define S_COND_TIME_SEC_0_16             S_W_RANGE_0_16

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   040727 akk 4073 Created file for modularisation of COND sub system.
*                       Derived from condstyp.h
* 2     041007 jyz 4515 Remove entry CeCOND_IO_DEVICE_MFDS_0
* tcb_pt1#3
*       041124 woz 4538 Removed CeCOND_IO_DEVICE_MLRE_0 from TeCOND_IO_Device.
* 4.0   050324 caw 4909 Removed: VbCOND_FuelETC_Disabled
*                       Added: VbCOND_Unused
*                              TeCOND_CHECKCPU_OPSTATUS
*                              VbCOND_LastNormPIC_MsgOK
*                              VbCOND_PIC_MsgOK
*                              VbCOND_PIC_InitMsg
*                              VbCOND_CommsReinitPending
*                              VbCOND_SU_BatVltgStabDelayActv
* 4.2.1 070108 MCB 5340 Changed XeSYST_LOAD_CNTRL_TYPE && CeSYST_MECHANICAL_THROT
*                        to XeCOND_ETC_CHECKING_CPU_TYPE
* 4.2.2 070206 MCB 5340 Added config file include
* tcb_pt1#4.3.1
*       070130 gps -BM- CORE : Include Header Files Optimization.
*                       Installed non-functional changes.
* 4.4   070219 mcb -BM- Merged condptyp.h-tcb_pt1#4.3.1 with condptyp.h-tcb_pt1#4.2.2
* tcb_pt1#4.2.3
*       070305 gps 5202 COND: Validate APS Inputs Using Short to Ground Method.
*                       api-file cleanup.
* tcb_pt1#4.5
*       070425 gps -BM- Merged 'condptyp.h-tcb_pt1#4.4' with 'condptyp.h-tcb_pt1#4.2.3'.
* 4.6	100218 sat 8239 Modified TeCOND_IO_Device.
* kok_pt2#4.7
*       100701 aq  8367 Add: CeCOND_Copy_Table_Types_T.
* kok_pt2#4.8
*       110621 me  9537 Data type changes for tasking 2.5 build to generate
*                        correct a2l.
*
******************************************************************************/
