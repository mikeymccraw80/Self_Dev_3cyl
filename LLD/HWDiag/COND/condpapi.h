#ifndef CONDPAPI_H
#define CONDPAPI_H
/******************************************************************************
 *
 * Filename:          condpapi.h
 *
 * Description:       Public output header file for COND
 *                    (Controller Diagnostic) subsystem
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
 * Copyright 2004-2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#7/incl/condpapi.h/1 %
 * %date_created:  Mon Dec 13 16:16:11 2010 %
 * %version:       1 %
 * %derived_by:    vzd0pc %
 *
 *****************************************************************************/

/******************************************************************************
 *  Global Application Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h" /* For Generic data types                            */

/*****************************************************************************
 *  Function Prototypes
 *****************************************************************************/
void MngCOND_CheckCPU_31p2Tasks(void);
void MngCOND_ADC0(void);

/*****************************************************************************
 *  Variable/Calibration Exports
 *****************************************************************************/
extern WORD         NwCOND_SOH_FltLongTermHist;
extern T_COUNT_WORD NcCOND_SOH_FltCntLongTerm;
extern TbBOOLEAN    SbCOND_SOH_MainCPU_Flt;
extern TbBOOLEAN    SbCOND_SOH_CommFlt;
extern TbBOOLEAN    SbCOND_SOH_CheckingCPU_Flt;
extern TbBOOLEAN    SbCOND_SOH_FltPrsnt;
extern TbBOOLEAN    SbCOND_SOH_MainCPU_TstCmp;
extern TbBOOLEAN    SbCOND_SOH_CommTstCmp;
extern TbBOOLEAN    SbCOND_SOH_CheckingCPU_TstCmp;

extern TbBOOLEAN    VbCOND_HWIO_ClockFailed;
#define GetCOND_MainCPU_ClockPerfTestFailed() (VbCOND_HWIO_ClockFailed)

#endif /* CONDPAPI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
