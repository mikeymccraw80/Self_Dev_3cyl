#ifndef CONDCALD_H
#define CONDCALD_H
/******************************************************************************
 *
 * Filename:          condcald.h
 *
 * Description:       Process Sequence Diagnostic for Master CPU
 *                    and software version check Calibration declarations.
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
 * Copyright 1999-2007, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#7/incl/condcald.h/1 %
 * %date_created:  Mon Dec 13 16:16:09 2010 %
 * %version:       1 %
 * %derived_by:    vzd0pc %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Include Files                                                            *
 *****************************************************************************/
#include "condfcfg.h"   /* For COND Local Configuration       */
#include "condfexi.h"   /* For global inputs                  */
#include "condstyp.h"   /* For COND Local type definitions    */
#include "condptyp.h"   /* For global type definitions        */

#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
#pragma section const {CAL_COND}
#endif


/******************************************************************************
* Calibration definitions for condcald.c
******************************************************************************/
#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_TORQUE
extern const T_COUNT_WORD    CAL0ADDR KcCOND_SequencingCntUp;
extern const T_COUNT_WORD    CAL0ADDR KcCOND_SequencingFailThrsh;
extern const TwTIME_t_R125ms CAL0ADDR KfCOND_t_SequencingDecTim;
#endif

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT
#if XeSYST_ETC_WatchdogCPU_HW == CeSYST_ETC_WatchdogCPU_Present
/******************************************************************************
* Calibration definitions for WD throttle circuit diagnostic (condmwdt.c)
******************************************************************************/
extern const T_COUNT_BYTE CAL0ADDR KcCOND_ThrotCircuitFailThrsh;
extern const T_COUNT_BYTE CAL0ADDR KcCOND_ThrotCircuitSampleThrsh;

extern const T_COUNT_BYTE CAL0ADDR KcCOND_DsblThrotCirFailThrsh;
extern const T_COUNT_BYTE CAL0ADDR KcCOND_DsblThrotCirSampleThrsh;
#endif /* XeSYST_ETC_WatchdogCPU_HW */

#endif /* XeSYST_LOAD_CNTRL_TYPE */

/******************************************************************************
* Calibration definitions for software version diagnostic (condmswv.c)
******************************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
extern const T_COUNT_BYTE CAL0ADDR KyCOND_ETC_CheckSW_Version1;
extern const T_COUNT_BYTE CAL0ADDR KyCOND_ETC_CheckSW_Version2;
extern const T_COUNT_BYTE CAL0ADDR KyCOND_ETC_CheckSW_Version3;
#endif /* XeCOND_ETC_CHECKING_CPU_TYPE */

#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_CORRELATION
extern const T_COUNT_WORD         CAL0ADDR  KcCOND_AD_CorrCntDwn;
extern const T_COUNT_WORD         CAL0ADDR  KcCOND_AD_CorrCntUp;
extern const T_VOLTb              CAL0ADDR  KfCOND_U_AD_CorrIgnLoDisable;
extern const T_VOLTb              CAL0ADDR  KfCOND_U_AD_CorrIgnHiDisable;
extern const T_PERCENTa           CAL0ADDR  KaCOND_Pct_AD_CorrThrshStdy[2];
extern const T_PERCENTa           CAL0ADDR  KaCOND_K_AD_CorrDynamicGain[2];
extern const T_PERCENTa           CAL0ADDR  KaCOND_Pct_AD_CorrDecayDelt[2];
extern const T_COUNT_WORD         CAL0ADDR  KcCOND_AD_CorrSampleThrsh;
extern const T_COUNT_WORD         CAL0ADDR  KaCOND_AD_CorrCountMaxAnlg[2];
#elif XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
extern const T_VOLTb              CAL0ADDR  KfCOND_U_AD_RespIgnLoDsbl;
extern const T_VOLTb              CAL0ADDR  KfCOND_U_AD_RespIgnHiDsbl;
extern const T_PERCENTa           CAL0ADDR  KfCOND_Pct_AD_RespAPS_PreShortMin;
extern const T_PERCENTa           CAL0ADDR  KfCOND_Pct_AD_RespAPS_ShortedMax;
extern const T_PERCENTa           CAL0ADDR  KfCOND_Pct_AD_RespRecDeltaAPS1_Max;
extern const T_PERCENTa           CAL0ADDR  KfCOND_Pct_AD_RespRecDeltaAPS2_Max;
extern const T_PERCENTa           CAL0ADDR  KfCOND_Pct_AD_RespDeltaAPS2_Max;
extern const T_COND_TIME_SEC_0_16 CAL0ADDR  KfCOND_t_AD_RespTstInterval;
extern const T_COND_TIME_SEC_0_16 CAL0ADDR  KfCOND_t_AD_RespShortSettleMin;
extern const T_COND_TIME_SEC_0_16 CAL0ADDR  KfCOND_t_AD_RespRecSettleMin;
extern const TsOBDU_DiagTstCals   CAL0ADDR  KsCOND_AD_RespTstCals;
#endif /* XeCOND_AD_INPUT_VALIDATION_METHOD */

#if XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE
extern const T_VOLTb      CAL0ADDR KfCOND_U_SystemThrshHi;
extern const T_VOLTb      CAL0ADDR KfCOND_U_SystemThrshLo;
extern const T_SECONDS    CAL0ADDR KaCOND_t_EnableDelayTime[CcCOND_NumOf_IO_Device];
extern const T_COUNT_BYTE CAL0ADDR KaCOND_Cnt_FailThrsh[CcCOND_NumOf_IO_Device];
extern const T_COUNT_BYTE CAL0ADDR KaCOND_Cnt_SampleThrsh[CcCOND_NumOf_IO_Device];
#endif /*XeSYST_CONTROLLER_DIAG */

#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
 #pragma section const {}
#endif

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.1   990204 as  0785 Created module.
* 1.2   990303 sai 0739 Add software version diagnostic
* 1.2   990303 sai 0862 Add watchdog CPU throttle disable diagnostic
*
* --- CORE REVISION HISTORY: ---
*
* 1.0   990825 wei 0303 Merged Proto2 package (cp2050f0) into core node 24
*              wei 0303 Added compilation switch XeSYST_ETC_WatchdogCPU_HW
*                        around ETC_Watchdog_CPU code.
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   010518 woz 0059 Reimplemented ETC conditional compile switches.
* 1.3   020920 woz 2152 Added CAL0ADDR storage specifiers. This allows use of
*                        indexed addressing mode for cals. (TriCore only)
* tci_pt3#2.1.1
*       030607  pd 2768 Added the calibrations :
*                        KfCOND_U_LPI_IFB_CommSysThrshLo,
*                        KcCOND_ECM_LPI_IFB_FailThrsh,
*                        KcCOND_ECM_LPI_IFB_SmplThrsh
* tci_pt3#2.1.2
*       031117 PVD 2063 Added CALS
*                       KcCOND_AD_CorrCntDwn,KcCOND_AD_CorrCntUp,
*                       KcCOND_AD_CorrSampleThrsh,KaCOND_AD_CorrCountMaxAnlg
*                       KfCOND_U_AD_CorrIgnLoDisable,KfCOND_U_AD_CorrIgnHiDisable
*                       KaCOND_Pct_AD_CorrThrshStdy[2]
*                       KaCOND_K_AD_CorrDynamicGain[2]
*                       KaCOND_Pct_AD_CorrDecayDelt[2]
*
* 2.1.3 040211 ses 2992 Added: KfCOND_U_SystemThrshHi, KfCOND_U_SystemThrshLo,
*                       KaCOND_t_EnableDelayTime, KaCOND_Cnt_FailThrsh,
*                       KaCOND_Cnt_SampleThrsh
*
* tci_pt3#2.1.3
*       040302 ban 3666 Added KcCOND_ECM_TRN_MIL_FailThrsh
*                             KcCOND_ECM_TRN_MIL_SmplThrsh
* 2.1.4.2.1
*       040428 wei 3339 Added KyCOND_ETC_CheckSW_Version1
*                             KyCOND_ETC_CheckSW_Version2
*                             KyCOND_ETC_CheckSW_Version3;
*                        removed KcCOND_MainSW_CalformID
*                              & KcCOND_ETC_CalibrationID
* 3.0   040601 caw  BM  Merge
* tci_pt3#3.1
*       040617  pd 3927 Making code Cosmic Compatible
* tci_pt3#3.0.1.1
*       040726 akk 4073 Changed includes for COND modularisation.
* tci_pt3#
*       040818  pd xxxx Merged parallel versions
* 3.1   040726 wei 3438 ETCD: Update process sequencing diagnostic.
* tci_pt3#3.2
*       040823  pd xxxx Merged parallel versions
*       050304 kan 4853 Removed XeSYST_CONTROLLER_ForETC
* 3.4   070305 gps 5202 COND: Validate APS Inputs Using Short to Ground Method.
*                       Added new set of calibrations.
*
******************************************************************************/
