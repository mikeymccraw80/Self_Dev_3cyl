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

/******************************************************************************
 *  Configuration Include File
 *****************************************************************************/
#include "condfcfg.h"   /* For COND configuration data                       */

#if XbCOND_SUBS_SELECT_FLAG == CbSUBS_ON

#include "condptyp.h"   /* For COND public type definitions                  */
#include "dgthpall.h"   /* For TeSINGLE_TEST_STATUS                          */
#include "systpcom.h"   /* For Application specific COND function exports    */
#include "viospwdi.h"   /* For GetVIOS_MainCPU_InvalidThrotCmdWD             */
                        /*     GetVIOS_MainCPU_FaultDetectedWD               */

/*****************************************************************************
 *  Function Prototypes
 *****************************************************************************/
FARFUNC void InitCOND_RstToKeyOn(void);
FARFUNC void InitCOND_PowerOfDelayToKeyOn(void);
FARFUNC void InitCOND_ShutdownInProgToKeyOn(void);
FARFUNC void InitCOND_OFVC_Clear(void);
FARFUNC void MngCOND_31p2msTasks(void);
FARFUNC void MngCOND_125msTasks(void);

#if XeCOND_ETC_CHECKING_CPU_TYPE != CeCOND_ETC_CHECKING_CPU_IS_NONE
FARFUNC void MngCOND_CheckCPU_15p6Tasks(void);
FARFUNC void MngCOND_CheckCPU_31p2Tasks(void);
FARFUNC void MngCOND_CheckCPU_125Tasks(void);
FARFUNC void PerformCOND_CheckCPU_ResetKeyOn(void);
FARFUNC void PerformCOND_CheckCPU_PwrdnDlyToKeyOn(void);
FARFUNC void PerformCOND_CheckCPU_ShutDnToKeyOn(void);
#else /* XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_NONE */
#define MngCOND_CheckCPU_15p6Tasks           DefineOSTK_EmptyFunction
#define MngCOND_CheckCPU_31p2Tasks           DefineOSTK_EmptyFunction
#define MngCOND_CheckCPU_125Tasks            DefineOSTK_EmptyFunction
#define PerformCOND_CheckCPU_ResetKeyOn      DefineOSTK_EmptyFunction
#define PerformCOND_CheckCPU_PwrdnDlyToKeyOn DefineOSTK_EmptyFunction
#define PerformCOND_CheckCPU_ShutDnToKeyOn   DefineOSTK_EmptyFunction
#endif /* XeCOND_ETC_CHECKING_CPU_TYPE */

#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
FARFUNC void MngCOND_AD_InputResp15p6msTasksA(void);
FARFUNC void MngCOND_AD_InputResp15p6msTasksB(void);
#else
INLINE void MngCOND_AD_InputResp15p6msTasksA(void) {}
INLINE void MngCOND_AD_InputResp15p6msTasksB(void) {}
#endif

#if XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE
FARFUNC void ProcessCOND_ADC_0_Output(void);
FARFUNC void ProcessCOND_ADC_1_Output(void);
FARFUNC void ProcessCOND_GPR_Output(void);
FARFUNC void ProcessCOND_TPIC6_0_Output(void);
FARFUNC void ProcessCOND_TPIC6_1_Output(void);
FARFUNC void ProcessCOND_TPIC6_2_Output(void);
FARFUNC void ProcessCOND_TPIC6_3_Output(void);
FARFUNC void ProcessCOND_LPC_ClockOutput(void);
FARFUNC void ProcessCOND_MainCPU_ClockFault(void);
FARFUNC void ProcessCOND_WDOG_TimerFault(void);
#else
#define ProcessCOND_ADC_0_Output             DefineOSTK_EmptyFunction
#define ProcessCOND_ADC_1_Output             DefineOSTK_EmptyFunction
#define ProcessCOND_GPR_Output               DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_0_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_1_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_2_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_3_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_LPC_ClockOutput          DefineOSTK_EmptyFunction
#define ProcessCOND_MainCPU_ClockFault       DefineOSTK_EmptyFunction
#define ProcessCOND_WDOG_TimerFault          DefineOSTK_EmptyFunction
#endif

/*****************************************************************************
 *  Variable/Calibration Exports
 *****************************************************************************/
extern WORD         NwCOND_SOH_FltLongTermHist;
extern T_COUNT_WORD NcCOND_SOH_FltCntLongTerm;



extern const T_VOLTb      CAL0ADDR KfCOND_U_LPI_IFB_CommSysThrshLo;
extern const T_COUNT_WORD CAL0ADDR KcCOND_ECM_LPI_IFB_FailThrsh;
extern const T_COUNT_WORD CAL0ADDR KcCOND_ECM_LPI_IFB_SmplThrsh;


#endif /* CONDPAPI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
