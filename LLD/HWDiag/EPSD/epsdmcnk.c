/******************************************************************************
 *
 * Filename:          epsdmcnk.c
 *
 * Description:       OBDII program to process crank diagnostic
 *
 * Global Functions Defined:
 *                    InitEPSD_CrankRstToKeyOn
 *                    InitEPSD_CrankCrankToStall
 *                    InitEPSD_CrankRunToPowerOffDelay
 *                    InitEPSD_CrankOFVC_Clear
 *                    MngEPSD_CrankEventTasks
 *                    MngEPSD_Crank7p81msTasks
 * Static Functions Defined:
 *                    InitEPSD_CrankComParms
 *                    ProcessEPSD_CrankNoSigEnblCriteria
 *                    ProcessEPSD_CrankNoisySigEnblCriteria
 *                    ProcessEPSD_CrankNoSigFaultTmrEval
 *                    ProcessEPSD_CrankNoisySigFaultCntrEval
 *                    PerformEPSD_CrankNoisySigXofYEval
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 1996-2003, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#14/csrc/epsdmcnk.c/1 %
 * %date_created:   Tue Nov 30 09:19:19 2010 %
 * %version:        1 %
 * %derived_by:     zzh8nc %
 *
 *****************************************************************************/

/******************************************************************************
*  Include Files
******************************************************************************/
#include "epsdpapi.h"  /* For EPSD Declration-Definition Check */
#include "epsdcald.h"  /* For EPSD Calibration File */
#include "hal_cam.h"
#include "intr_ems.h"
#include "dd_crank_interface.h"

/*****************************************************************************
*  Type declaration
******************************************************************************/
enum {
	CeEPSD_CrankNoSigTimer,
	CeEPSD_CrankNoSigResetTimer,
	CeEPSD_Num7p8Timers
};

/*****************************************************************************
 *  Global Data Define
 *****************************************************************************/
/* The 7.81 msec timer calls would be made from the operating system */
DefTIMC_StopWatches16(VaEPSD_t_7p8TimerArray,
                      VaEPSD_7p8TimerEnbl,
                      R7p8125ms,
                      CeEPSD_Num7p8Timers);

/******************************************************************************
*  Static Data Define
******************************************************************************/
TbBOOLEAN  VbEPSD_CrankNoisySigFailCriteriaMet;
TbBOOLEAN  SbEPSD_CrankNoisySigEnblCriteriaMet;
TbBOOLEAN  SbEPSD_CrankNoisySigTestComplete;
TbBOOLEAN  SbEPSD_CrankNoisySigTestComplete_Internal;
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN  SbEPSD_CrankNoisySigTestFailed;
TbBOOLEAN  SbEPSD_CrankNoSigTestFailed;
#pragma section DATA " " ".bss"
TbBOOLEAN  VbEPSD_CrankNoSigFailCriteriaMet;
TbBOOLEAN  SbEPSD_CrankNoSigEnblCriteriaMet;
TbBOOLEAN  SbEPSD_CrankNoSigTestComplete;
TbBOOLEAN  SbEPSD_CrankNoSigTestComplete_Internal;

T_COUNT_BYTE  ScEPSD_CrankCylEventEnblCntr;
T_COUNT_WORD  ScEPSD_CrankNoisySigSampleCntr;
T_COUNT_WORD  ScEPSD_CrankNoisySigFailCntr;
TbON  SeEPSD_CamPrevState;        /* Should be TbHIGH per DDE */
T_COUNT_WORD  SfEPSD_CrankRefToothErrCnt;
T_KPAa  SfEPSD_MnfdPresAtKeyOn;

/******************************************************************************
*  Local Function declarations
******************************************************************************/
static void InitEPSD_CrankComParms(void);
static void ProcessEPSD_CrankNoSigEnblCriteria(void);
static void ProcessEPSD_CrankNoisySigEnblCriteria(void);
static void ProcessEPSD_CrankNoSigFaultTmrEval(void);
static void ProcessEPSD_CrankNoisySigFaultCntrEval(void);
static void PerformEPSD_CrankNoisySigXofYEval(void);

/*****************************************************************************
 *
 * Function:            InitEPSD_CrankRstToKeyOn
 * Description:         Initialization functions.
 *
 *                      DtrmnOBDU_DoubleFaultTypeZ :
 *                              (Examine_Crank_Fault_Type_Disable)
 *                      This process will look at Crank_No_Signal and
 *                      Crank_Noisy_Signal fault types, and disable the Crank
 *                      Fault Diagnostics if either is declared as type Z.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void InitEPSD_CrankRstToKeyOn(void)
{
	SeEPSD_CamPrevState = HAL_Get_CAM_Level(CAM1);
	SfEPSD_MnfdPresAtKeyOn = GetVIOS_p_MnfdPresFiltd();
}

/*****************************************************************************
 *
 * Function:            InitEPSD_CrankCrankToStall
 * Description:         Initialization functions CRANK_To_STALL
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void InitEPSD_CrankCrankToStall(void)
{
	InitEPSD_CrankComParms();

	HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl,CeEPSD_CrankNoSigTimer);
	SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray,
						CeEPSD_CrankNoSigTimer,C_R7p8125ms16(0));
	HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl,CeEPSD_CrankNoSigResetTimer);
	SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray,
						CeEPSD_CrankNoSigResetTimer,C_R7p8125ms16(0));
}

/*****************************************************************************
 *
 * Function:            InitEPSD_CrankRunToPowerOffDelay
 * Description:         Initialization functions RUN_To_POWER_OFF_DELAY
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void InitEPSD_CrankRunToPowerOffDelay(void)
{
	SbEPSD_CrankNoSigTestComplete = CbFALSE; //changed by daowei
	SbEPSD_CrankNoSigTestComplete_Internal = CbFALSE;
	HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl,CeEPSD_CrankNoSigTimer);
	SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray,
						CeEPSD_CrankNoSigTimer,C_R7p8125ms16(0));
	HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl,CeEPSD_CrankNoSigResetTimer);
	SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray,
						CeEPSD_CrankNoSigResetTimer,C_R7p8125ms16(0));

	InitEPSD_CrankComParms();
}

/*****************************************************************************
 *
 * Function:            InitEPSD_CrankOFVC_Clear
 * Description:         Initialization functions OFVC_DIAG_CLEAR_EVENT
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void InitEPSD_CrankRstTo_Keyoff(void)
{
	SbEPSD_CrankNoSigTestComplete = CbFALSE;
	SbEPSD_CrankNoSigTestComplete_Internal = CbFALSE;
	HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl,CeEPSD_CrankNoSigTimer);
	SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray,
						CeEPSD_CrankNoSigTimer,C_R7p8125ms16(0));
	HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl,CeEPSD_CrankNoSigResetTimer);
	SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray,
						CeEPSD_CrankNoSigResetTimer,C_R7p8125ms16(0));

	InitEPSD_CrankComParms();
}

/*****************************************************************************
 *
 * Function:             InitEPSD_CrankComParms
 * Description:          Initialization function for common parameters.
 *
 * Parameters:                None
 * Return:                None
 *****************************************************************************/
static void InitEPSD_CrankComParms(void)
{
	SbEPSD_CrankNoisySigEnblCriteriaMet = CbFALSE;
	VbEPSD_CrankNoisySigFailCriteriaMet = CbFALSE;
	SbEPSD_CrankNoisySigTestComplete_Internal = CbFALSE;
	SbEPSD_CrankNoisySigTestComplete = CbFALSE;

	ScEPSD_CrankNoisySigSampleCntr = V_COUNT_WORD(0);
	ScEPSD_CrankNoisySigFailCntr   = V_COUNT_WORD(0);
	ScEPSD_CrankCylEventEnblCntr   = V_COUNT_BYTE(0);
}

#if 0
/*****************************************************************************
 *
 * Function:            MngEPSD_CrankEventTasks
 * Description:         This procedure will be called by the operating system
 *                      during every 2X/3X event. The procedure includes
 *                      calls to all 2X/3X event triggered functions.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void MngEPSD_CrankEventTasks(void)
{
	if (GetVIOS_CrankRefToothErrCnt() > SfEPSD_CrankRefToothErrCnt)
		SfEPSD_CrankRefToothErrCnt = GetVIOS_CrankRefToothErrCnt();

	ProcessEPSD_CrankNoisySigEnblCriteria();
	ProcessEPSD_CrankNoisySigFaultCntrEval();
	PerformEPSD_CrankNoisySigXofYEval();
	SbEPSD_CrankNoisySigTestComplete |= SbEPSD_CrankNoisySigTestComplete_Internal;

	if ((SbEPSD_CrankNoisySigEnblCriteriaMet)
	&& (SfEPSD_CrankRefToothErrCnt != V_COUNT_WORD(0) ) )
	{
		ClrVIOS_CrankRefToothErrCnt();
		SfEPSD_CrankRefToothErrCnt = V_COUNT_WORD(0);
	}
}

#endif

/*****************************************************************************
 *
 * Function:            MngEPSD_Crank7p81msTasks
 * Description:         This procedure will be called by the operating system
 *                      during every 7.81 msec timer event. The procedure
 *                      includes calls to all timer triggered functions.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void MngEPSD_Crank7p81msTasks(void)
{
	UpdateTIMC_StopWatchesUp16(VaEPSD_t_7p8TimerArray,
							   VaEPSD_7p8TimerEnbl,
							   CeEPSD_Num7p8Timers);
	ProcessEPSD_CrankNoSigEnblCriteria();
	ProcessEPSD_CrankNoSigFaultTmrEval();
	SbEPSD_CrankNoSigTestComplete |= SbEPSD_CrankNoSigTestComplete_Internal;
}

/*****************************************************************************
 *
 * Function:            ProcessEPSD_CrankNoSigEnblCriteria
 * Description:         Process_Crank_No_Signal_Enable_Criteria.
 *                      This process determines whether to enable the
 *                      Crank_No_Signal test for a Cam sensor based system
 *                      or a MAP based system.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void ProcessEPSD_CrankNoSigEnblCriteria(void)
{
/* Please note that the calibration values
   KfEPSD_p_CrankDeltaMAP_Thrsh and KfEPSD_U_CrankDeltaIgnThrsh
   can have only positive values. Hence the two subtractions below
   are of the kind usSUB_us_usp. */

	if ((((GetVIOS_EngSt() == CeENG_KEYON)
			|| (GetVIOS_EngSt() == CeENG_STALL)
			|| (GetVIOS_EngSt() == CeENG_CRANK)
			|| (CRANK_Get_Flag(CRANK_FLAG_CAM_BACKUP) == true) )
			&& (HAL_Get_CAM_Level(CAM1) != SeEPSD_CamPrevState))
		|| \
		(((GetVIOS_EngSt() == CeENG_KEYON) || (GetVIOS_EngSt() == CeENG_CRANK) || (CRANK_Get_Flag(CRANK_FLAG_CAM_BACKUP) == true))
			&& (FixSubAbs(SfEPSD_MnfdPresAtKeyOn, GetVIOS_p_MnfdPresFiltd(), EOBD_KPAa)
				> KfEPSD_p_CrankDeltaMAP_Thrsh)
			&& (FixSubAbs(GetVIOS_U_IgnVoltageAtKeyOn(), GetVIOS_U_IgnVolt(), EOBD_VOLTb)
				> KfEPSD_U_CrankDeltaIgnThrsh)))
	{
		SbEPSD_CrankNoSigEnblCriteriaMet = CbTRUE;
	}
	else
	{
		SbEPSD_CrankNoSigEnblCriteriaMet = CbFALSE;
	}

	SeEPSD_CamPrevState = HAL_Get_CAM_Level(CAM1);
}


/*****************************************************************************
 *
 * Function:            ProcessEPSD_CrankNoSigFaultTmrEval
 * Description:         This procedure is a combination of two pspec bubbles:
 *                      (1) Process_Crank_No_Signal_Fault_Evaluation
 *              and     (2) Process_Crank_No_Signal_Timer_Evaluation
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void ProcessEPSD_CrankNoSigFaultTmrEval(void)
{
/*      Process_Crank_No_Signal_Fault_Evaluation
 *      ========================================
 *      This process determines if a Crank_No_Signal fault
 *      exists. A fail condition exists when the diagnostic
 *      is enabled but no crankshaft teeth have been seen.
 *      Note: OBD_EngTurning is TRUE as long as
 *      crankshaft teeth are detected by hardware. */

	if ( (SbEPSD_CrankNoSigEnblCriteriaMet)
		 && (( GetVIOS_n_EngSpd() <= V_RPMa(EMS_ZERO_RPM) )||
			   crank_sig.crank_status.B_crank_failed))
	{
		VbEPSD_CrankNoSigFailCriteriaMet = CbTRUE;
	}
	else
	{
		VbEPSD_CrankNoSigFailCriteriaMet = CbFALSE;
	}

	/*      Process_Crank_No_Signal_Timer_Evaluation
	 *      ========================================
	 *      This process will evaluate how long the
	 *      Crank_No_Signal conditions have been met and will fail
	 *      the test if the conditions exceed a time threshold. */
	if(SbEPSD_CrankNoSigTestComplete_Internal)
		SbEPSD_CrankNoSigTestComplete_Internal = CbFALSE;

	if (SbEPSD_CrankNoSigEnblCriteriaMet) {
		HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigResetTimer);
		SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray, CeEPSD_CrankNoSigResetTimer, C_R7p8125ms16(0));
		if (VbEPSD_CrankNoSigFailCriteriaMet) {
			if (GetTIMC_t_StopWatch16(VaEPSD_t_7p8TimerArray,CeEPSD_CrankNoSigTimer)
							>= KfEPSD_t_CrankNoSignalTmr) {
				SbEPSD_CrankNoSigTestFailed = CbTRUE;
				SbEPSD_CrankNoSigTestComplete_Internal = CbTRUE;
				HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigTimer);
				SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray, CeEPSD_CrankNoSigTimer, C_R7p8125ms16(0));
			} else {
				ResumeTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigTimer);
			}
		} else {
			SbEPSD_CrankNoSigTestFailed = CbFALSE;
			SbEPSD_CrankNoSigTestComplete_Internal = CbTRUE;
			HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigTimer);
			SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray, CeEPSD_CrankNoSigTimer, C_R7p8125ms16(0));
		}
	} else {
		if (GetTIMC_t_StopWatch16(VaEPSD_t_7p8TimerArray, CeEPSD_CrankNoSigResetTimer)
						>= KfEPSD_t_CrankNoSignalResetThrs) {
			if (CRANK_Get_Flag(CRANK_FLAG_CAM_BACKUP) != true) {
				if (GetVIOS_EngSt() == CeENG_RUN) //added by daowei
					SbEPSD_CrankNoSigTestFailed = CbFALSE; //added by daowei
			}
			SbEPSD_CrankNoSigTestComplete_Internal = CbFALSE;
			
			/* stop and reset no signal timer */
			// HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigTimer);
			SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray, CeEPSD_CrankNoSigTimer, C_R7p8125ms16(0));
			
			/* stop and reset reset timer */
			HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigResetTimer);
			SetTIMC_StopWatch16(VaEPSD_t_7p8TimerArray, CeEPSD_CrankNoSigResetTimer, C_R7p8125ms16(0));
		} else {
			ResumeTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigResetTimer);
		}
		/* stop no signal timer increase */
		HaltTIMC_StopWatch(VaEPSD_7p8TimerEnbl, CeEPSD_CrankNoSigTimer);
	}
}

/*****************************************************************************
 *
 * Function:            ProcessEPSD_CrankNoisySigEnblCriteria
 * Description:         Process_Crank_Noisy_Signal_Enable_Criteria.
 *                      This process determines whether or not to enable the
 *                      Crank_Noisy_Signal test. The Crank_Noisy_Signal
 *                      test will be enabled once per crank revolution and
 *                      will look for the number of extra or missing crank
 *                      teeth per revolution.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
 #if 0
static void ProcessEPSD_CrankNoisySigEnblCriteria(void)
{
	if ( (GetVIOS_EngSt() == CeENG_RUN)
	&&(!GetVIOS_CAM_CrankBackupActive()) )
	{
		ScEPSD_CrankCylEventEnblCntr++;
		if (ScEPSD_CrankCylEventEnblCntr == ((CcSYST_NUM_OF_CYLINDERS) >> 1)) {
			SbEPSD_CrankNoisySigEnblCriteriaMet = CbTRUE;
			ScEPSD_CrankCylEventEnblCntr = V_COUNT_BYTE(0);
		} else {
			SbEPSD_CrankNoisySigEnblCriteriaMet = CbFALSE;
		}
	}
	else
	{
		SbEPSD_CrankNoisySigEnblCriteriaMet = CbFALSE;
	}
}

/*****************************************************************************
 *
 * Function:            ProcessEPSD_CrankNoisySigFaultCntrEval
 * Description:         This procedure is a combination of two pspec bubbles:
 *                      (1) Process_Crank_Noisy_Signal_Fault_Evaluation
 *              and     (2) Process_Crank_Noisy_Signal_Counter_Evaluation
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void ProcessEPSD_CrankNoisySigFaultCntrEval(void)
{
/*      Process_Crank_Noisy_Signal_Fault_Evaluation
 *      ===========================================
 *      This process will determine if a Crank_Noisy_Signal
 *      is present by looking at the Crank tooth error
 *      counter provided by Hardware I/O. If this counter is
 *      equal to zero, then no faults were seen. If this
 *      counter is less than zero then the value is the number
 *      of missing teeth. If the counter is more than zero
 *      then the value is the number of extra teeth. */

	if ( (SbEPSD_CrankNoisySigEnblCriteriaMet)
	 && (SfEPSD_CrankRefToothErrCnt >=
		 KcEPSD_CrankToothErrFailThrsh) )
	{
		VbEPSD_CrankNoisySigFailCriteriaMet = CbTRUE;
	}
	else
	{
		VbEPSD_CrankNoisySigFailCriteriaMet = CbFALSE;
	}
}

/*****************************************************************************
 *
 * Function:            PerformEPSD_CrankNoisySigXofYEval
 * Description:         Perform_Crank_Noisy_Signal X_of_Y Evaluation.
 *                      This process determines if the Crank_Noisy_Signal
 *                      Diagnostic has met either the pass or fail criteria
 *                      and outputs the appropriate results. The pass criteria
 *                      will be met when a calibrated number of good samples
 *                      have occurred. The fail criteria will be met when one
 *                      sample falls outside the error band.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void PerformEPSD_CrankNoisySigXofYEval(void)
{
	if (SbEPSD_CrankNoisySigEnblCriteriaMet) {
		if (SbEPSD_CrankNoisySigTestComplete_Internal)
			SbEPSD_CrankNoisySigTestComplete_Internal = CbFALSE;
		if (ScEPSD_CrankNoisySigFailCntr >= KcEPSD_CrankNoisySigFailThrsh) {
			SbEPSD_CrankNoisySigTestFailed = CbTRUE;
			SbEPSD_CrankNoisySigTestComplete_Internal = CbTRUE;
		} else if (ScEPSD_CrankNoisySigSampleCntr >= KcEPSD_CrankNoisySigSampleThrsh) {
			SbEPSD_CrankNoisySigTestFailed = CbFALSE;
			SbEPSD_CrankNoisySigTestComplete_Internal = CbTRUE;
		}
	}
}
#endif
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
*
******************************************************************************/
