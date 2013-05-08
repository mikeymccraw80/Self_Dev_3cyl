#ifndef EMSDMFPE_H
#define EMSDMFPE_H
/******************************************************************************
 *
 * Filename:          emsdmlib.h
 *
 * Description:                  This is the public header file for
 *                               the ems side I/O hardware diagnostic
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
 * Copyright 2003-2005 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/incl/emsdmlib.h/1 %
 * %date_created:  Wed Mar 19 10:10:09 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/
/******************************************************************************
*   Include Files
******************************************************************************/
#include "intr_ems.h"
#include "t_gentypes.h"

/*=========================================================================
 *  Function Prototypes for EMSD Diagnostic
 *=========================================================================*/

TbBOOLEAN ChkEMSD_GetPSVIorTPICFault ( 
              TbBOOLEAN          LbEMSD_xxxxEnblCriteriaMet,
              TbBOOLEAN          LbOBD_PSVI_TPICFault );


/*==========================================================================
 *           AcClutch Relay
 *=========================================================================*/

void EvaluateEMSD_ACCDEnblCriteria (
              T_SECONDS        KfEMSD_t_IgnitionOnDelay,
              TbBOOLEAN        *LbEMSD_ACCDEnblCriteriaMet);
              
/*==========================================================================
 *           Main Power Relay
 *=========================================================================*/
void EvaluateEMSD_MPRDEnblCriteria (
              T_SECONDS        KfEMSD_t_MPRDIgnitionOnDelay,
              TbBOOLEAN        *LbEMSD_MPRDEnblCriteriaMet);
                
/*==========================================================================
 *           FANx  Diagnostic
 *=========================================================================*/
void EvaluateEMSD_FANAEnblCriteria (
              T_SECONDS        KfEMSD_t_IgnitionOnDelay,
              TbBOOLEAN        *LbEMSD_FANAEnblCriteriaMet);
void EvaluateEMSD_FANBEnblCriteria (
              T_SECONDS        KfEMSD_t_IgnitionOnDelay,
              TbBOOLEAN        *LbEMSD_FANBEnblCriteriaMet);

/*==========================================================================
 *           Fuel Pump Relay
 *=========================================================================*/
void EvaluateEMSD_FPRDEnblCriteria (
              T_SECONDS        KfEMSD_t_IgnitionOnDelay,
              TbBOOLEAN        *LbEMSD_FPRDEnblCriteriaMet);
     
/*==========================================================================
 *           MIL  Hardware dianostic
 *=========================================================================*/
void EvaluateEMSD_MILDEnblCriteria (
              T_SECONDS        KfEMSD_t_IgnitionOnDelay,
              TbBOOLEAN        *LbEMSD_MILDEnblCriteriaMet);

/*=========================================================================
 *  Function Prototypes for Oxygen Sensor Heater Diagnostic
 *=========================================================================*/

      
TbBOOLEAN ChkEOSD_O2_xx_Htr_GetPSVIFault (
            TbBOOLEAN          LbEOSD_O2_xx_HtrEnblCriteriaMet,
            TbBOOLEAN          LbOBD_O2_xx_Htr_PSVIFault
                                          );

TbBOOLEAN EvaluateEOSD_O2_xx_HtrEnblCriteria (
            T_COUNT_WORD     KfEOSD_t_xx_HtrEngRunThrsh );


void EvalOBDU_DoubleXofY(
         T_COUNT_WORD LcOBDU_TestA_FailCntr,
         T_COUNT_WORD LcOBDU_TestB_FailCntr,
         T_COUNT_WORD LcOBDU_SampleCntr,
         T_COUNT_WORD KcOBDU_TestA_FailThrsh,
         T_COUNT_WORD KcOBDU_TestB_FailThrsh,
         T_COUNT_WORD KcOBDU_SampleThrsh,
         TbBOOLEAN    *LbOBDU_TestComplete,
         TbBOOLEAN    *LbOBDU_TestA_Failed,
         TbBOOLEAN    *LbOBDU_TestB_Failed );

void UpdateOBDU_DoubleTestCntrs(
         TbBOOLEAN    LbOBDU_TestComplete,
         TbBOOLEAN    LbOBDU_TestEnblCriteriaMet,
         TbBOOLEAN    LbOBDU_TestA_FailCriteriaMet,
         TbBOOLEAN    LbOBDU_TestB_FailCriteriaMet,
         T_COUNT_WORD *LcOBDU_TestA_FailCntr,
         T_COUNT_WORD *LcOBDU_TestB_FailCntr,
         T_COUNT_WORD *LcOBDU_SampleCntr );

void EvalOBDU_SingleXofY(
         T_COUNT_WORD LcOBDU_FailCntr,
         T_COUNT_WORD LcOBDU_SampleCntr,
         T_COUNT_WORD KcOBDU_FailThrsh,
         T_COUNT_WORD KcOBDU_SampleThrsh,
         TbBOOLEAN    *LbOBDU_TestComplete,
         TbBOOLEAN    *LbOBDU_TestFailed );

void UpdateOBDU_SingleTestCntrs(
         TbBOOLEAN    LbOBDU_TestComplete,
         TbBOOLEAN    LbOBDU_TestEnblCriteriaMet,
         TbBOOLEAN    LbOBDU_TestFailCriteriaMet,
         T_COUNT_WORD *LcOBDU_FailCntr,
         T_COUNT_WORD *LcOBDU_SampleCntr );

#endif

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
\* ============================================================================ */
 
