/******************************************************************************
 *
 * Filename:          epsdmcam.c
 *
 * Description:       OBDII program to process cam diagnostic
 *
 * Global Functions Defined:
 *                    InitEPSD_CamRstToKeyOn
 *                    InitEPSD_CamCrankToStall
 *                    InitEPSD_CamRunToPowerOffDelay
 *                    InitEPSD_CamOFVC_Clear
 *                    MngEPSD_CamEventTasks
 * Static Functions Defined:
 *                    InitEPSD_CamComParms
 *                    ProcessEPSD_CamFaultsEnblCriteria
 *                    ProcessEPSD_CamNoSigFaultCntrEval
 *                    ProcessEPSD_CamRatnlyFaultEval
 *                    ProcessEPSD_CamRatnlyCntrEval
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
 * %full_name:     mt20u2#14/csrc/epsdmcam.c/1 %
 * %date_created:  Tue Nov 30 09:19:09 2010 %
 * %version:       1 %
 * %derived_by:    zzh8nc %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Include Files
 *****************************************************************************/
#include "epsdpapi.h"  /* For EPSD Declration-Definition Check */
#include "epsdcald.h"  /* For EPSD Calibration File */
#include "mall_lib.h"
#include "timclib.h"
#include "intr_ems.h"
#include "v_power.h"

#define CcSYST_NUM_OF_CYLINDERS 4
/******************************************************************************
 *  Global Data Define
 *****************************************************************************/
TbBOOLEAN  VbEPSD_CamNoSigFailCriteriaMet;
TbBOOLEAN  VbEPSD_CamRatnlyFailCriteriaMet;
T_COUNT_BYTE  VcEPSD_CamCylEventCntr;

/******************************************************************************
*  Static Data Define
******************************************************************************/
TbBOOLEAN  SbEPSD_CamNoSigEnblCriteriaMet;
TbBOOLEAN  SbEPSD_CamNoSigTestComplete;
// #pragma section [nvram] 
TbBOOLEAN  SbEPSD_CamNoSigTestFailed;
// #pragma section [] 
TbBOOLEAN  SbEPSD_CamRatnlyEnblCriteriaMet;
TbBOOLEAN  SbEPSD_CamRatnlyTestComplete;
// #pragma section [nvram] 
TbBOOLEAN  SbEPSD_CamRatnlyTestFailed;
// #pragma section [] 
T_COUNT_WORD  ScEPSD_CamNoSigCylEventCntr;
T_COUNT_WORD  ScEPSD_CamRatnlyFailCntr;
T_COUNT_WORD  ScEPSD_CamRatnlyPassCntr;
TbBOOLEAN  SbEPSD_CamNoSigTestComplete_Internal;
TbBOOLEAN  SbEPSD_CamRatnlyTestComplete_Internal;

/******************************************************************************
*  Local Function declarations
******************************************************************************/
static void InitEPSD_CamComParms(void);
static void ProcessEPSD_CamFaultsEnblCriteria(void);
static void ProcessEPSD_CamNoSigFaultCntrEval(void);
static void ProcessEPSD_CamRatnlyFaultEval(void);
static void ProcessEPSD_CamRatnlyCntrEval(void);

/*****************************************************************************
 *
 * Function:            InitEPSD_CamRstToKeyOn
 * Description:         Initialization functions
 *                              (CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 *                      DtrmnOBDU_DoubleFaultTypeZ :
 *                              (Examine_Cam_Fault_Type_Disable)
 *                      This procedure will look at Cam_No_Signal and
 *                      Cam_Rationality fault types and disable the Cam
 *                      Diagnostics if either is declared as type Z.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
//FAR_COS void InitEPSD_CamRstToKeyOn(void)
//{
  //  InitEPSD_CamComParms();
//}

/*****************************************************************************
 *
 * Function:            InitEPSD_CamCrankToStall
 * Description:         Initialization functions CRANK_TO_STALL
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void InitEPSD_CamCrankToStall(void)
{
	InitEPSD_CamComParms();
	SbEPSD_CamNoSigTestComplete_Internal = CbFALSE;
	// SbEPSD_CamNoSigTestFailed = CbFALSE;
	VbEPSD_CamNoSigFailCriteriaMet = CbFALSE;

	ScEPSD_CamNoSigCylEventCntr = V_COUNT_WORD(0);
}

/*****************************************************************************
 *
 * Function:            InitEPSD_CamRunToPowerOffDelay
 * Description:         Initialization functions RUN_TO_POWER_OFF_DELAY
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void InitEPSD_CamRunToPowerOffDelay(void)
{
	InitEPSD_CamComParms();
}
#if 0
/*****************************************************************************
 *
 * Function:            InitEPSD_CamOFVC_Clear
 * Description:         Initialization functions OFVC_DIAG_CLEAR_EVENT
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
FAR_COS void InitEPSD_CamRstTo_Keyoff(void)
{
    SbEPSD_CamNoSigTestComplete_Internal = CbFALSE;
   // SbEPSD_CamNoSigTestFailed = CbFALSE;
   // SbEPSD_CamRatnlyTestComplete = CbFALSE;
    SbEPSD_CamRatnlyTestComplete_Internal = CbFALSE;
   // SbEPSD_CamRatnlyTestFailed = CbFALSE;

    ScEPSD_CamNoSigCylEventCntr = V_COUNT_WORD(0);
    ScEPSD_CamRatnlyFailCntr = V_COUNT_WORD(0);
    ScEPSD_CamRatnlyPassCntr = V_COUNT_WORD(0);

}
#endif
/*****************************************************************************
 *
 * Function:                InitEPSD_CamComParms
 * Description:          Initialization functions for common parameters.
 *
 * Parameters:                None
 * Return:                None
 *****************************************************************************/
static void InitEPSD_CamComParms(void)
{
	SbEPSD_CamNoSigEnblCriteriaMet  = CbFALSE;
	SbEPSD_CamRatnlyEnblCriteriaMet = CbFALSE;
	VbEPSD_CamRatnlyFailCriteriaMet = CbFALSE;
	SbEPSD_CamRatnlyTestComplete    = CbFALSE;
	SbEPSD_CamNoSigTestComplete = CbFALSE;
	SbEPSD_CamRatnlyTestComplete_Internal = CbFALSE;
	// SbEPSD_CamRatnlyTestFailed      = CbFALSE;

	ScEPSD_CamRatnlyFailCntr = V_COUNT_WORD(0);
	ScEPSD_CamRatnlyPassCntr = V_COUNT_WORD(0);
	VcEPSD_CamCylEventCntr   = V_COUNT_BYTE(0);
}

/*****************************************************************************
 *
 * Function:            MngEPSD_CamEventTasks
 * Description:         This procedure will be called by the operating system
 *                      during every 2X/3X event. The procedure includes
 *                      calls to all 2X/3X event triggered functions.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
void MngEPSD_CamEventTasks(void)
{
	ProcessEPSD_CamFaultsEnblCriteria();
	ProcessEPSD_CamNoSigFaultCntrEval();
	SbEPSD_CamNoSigTestComplete |=SbEPSD_CamNoSigTestComplete_Internal;
	ProcessEPSD_CamRatnlyFaultEval();
	ProcessEPSD_CamRatnlyCntrEval();
	SbEPSD_CamRatnlyTestComplete |= SbEPSD_CamRatnlyTestComplete_Internal;
}

/*****************************************************************************
 *
 * Function:            ProcessEPSD_CamFaultsEnblCriteria
 * Description:         Process_Cam_Faults_Enable_Criteria.
 *                      This process will determine if the Cam_No_Signal
 *                      and the Cam_Rationality enable conditions are met.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void ProcessEPSD_CamFaultsEnblCriteria(void)
{

/* check Cam_No_Signal enable conditions for the first
   cylinder event after a change of Cam state */
	if (GetVIOS_EngSt() == CeENG_RUN)
	{
		if ( GetVIOS_CylNum() == V_COUNT_BYTE (1) )
		{
			SbEPSD_CamNoSigEnblCriteriaMet = CbTRUE;
		}
		else
		{
			SbEPSD_CamNoSigEnblCriteriaMet = CbFALSE;
		}

/* check Cam_Rationality enable conditions */
		if (SbEPSD_CamNoSigTestFailed == CbFALSE)
		{
			SbEPSD_CamRatnlyEnblCriteriaMet = CbTRUE;
		}
		else
		{
			SbEPSD_CamRatnlyEnblCriteriaMet = CbFALSE;
		}
	}
	else
	{
		SbEPSD_CamNoSigEnblCriteriaMet = CbFALSE;
		SbEPSD_CamRatnlyEnblCriteriaMet = CbFALSE;
	}
}

/*****************************************************************************
 *
 * Function:            ProcessEPSD_CamNoSigFaultCntrEval
 * Description:         This procedure is a combination of two pspec bubbles:
 *                      (1) Process_Cam_No_Signal_Fault_Evaluation
 *              and     (2) Process_Cam_No_Signal_Counter_Evaluation
 *
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void ProcessEPSD_CamNoSigFaultCntrEval(void)
{
/*      Process_Cam_No_Signal_Fault_Evaluation
 *      ======================================
 *      This process will determine if a Cam signal is
 *      present. The Cam stuck flag (provided by HWIO) is
 *      used which indicates that the Cam signal was found
 *      to be in the same state (either high or low) on two
 *      successive synchronization checks, therefore the Cam
 *      would have had no signal for two revolutions. */

	if ( (SbEPSD_CamNoSigEnblCriteriaMet))
		 // && (GetVIOS_CamStuck()) )
	{
		VbEPSD_CamNoSigFailCriteriaMet = CbTRUE;
	}
	else
	{
		VbEPSD_CamNoSigFailCriteriaMet = CbFALSE;
	}

/*      Process_Cam_No_Signal_Counter_Evaluation
 *      ========================================
 *      This process will activate an event counter and
 *      check to see if the counter exceeds the failure
 *      threshold for the Cam_No_Signal fault. */

	if (VbEPSD_CamNoSigFailCriteriaMet)
	{
		ScEPSD_CamNoSigCylEventCntr++;
		if (ScEPSD_CamNoSigCylEventCntr >= KcEPSD_CamNoSignalCylEvent)
		{
			SbEPSD_CamNoSigTestFailed = CbTRUE;
			SbEPSD_CamNoSigTestComplete_Internal = CbTRUE;
			ScEPSD_CamNoSigCylEventCntr = V_COUNT_WORD(0);
		}
		else
		{
			SbEPSD_CamNoSigTestComplete_Internal = CbFALSE;
		}
	}
	else if (SbEPSD_CamNoSigEnblCriteriaMet)
	{
		SbEPSD_CamNoSigTestFailed = CbFALSE;
		SbEPSD_CamNoSigTestComplete_Internal = CbTRUE;
		ScEPSD_CamNoSigCylEventCntr = V_COUNT_WORD(0);
	}
	else
	{
		SbEPSD_CamNoSigTestComplete_Internal = CbFALSE;
	}
}

/*****************************************************************************
 *
 * Function:            ProcessEPSD_CamRatnlyFaultEval
 * Description:         Process_Cam_Rationality_Fault_Evaluation.
 *                      This process will check to see if a Cam
 *                      synchronization has occurred between the appropriate
 *                      number of cylinder events.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void ProcessEPSD_CamRatnlyFaultEval(void)
{
	if (SbEPSD_CamRatnlyEnblCriteriaMet)
	{
		VcEPSD_CamCylEventCntr++;
		if (GetVIOS_CamOccurred())
		{
			if (VcEPSD_CamCylEventCntr == CcSYST_NUM_OF_CYLINDERS )
			{
				VbEPSD_CamRatnlyFailCriteriaMet = CbFALSE;
				VcEPSD_CamCylEventCntr = V_COUNT_BYTE(0);
			}
			else
			{
				VbEPSD_CamRatnlyFailCriteriaMet = CbTRUE;
				VcEPSD_CamCylEventCntr = V_COUNT_BYTE(0);
			}
		}
		else if (VcEPSD_CamCylEventCntr == CcSYST_NUM_OF_CYLINDERS )
		{
			VcEPSD_CamCylEventCntr = V_COUNT_BYTE(0);
			VbEPSD_CamRatnlyFailCriteriaMet = CbTRUE;
		}
		else
		{
		   VbEPSD_CamRatnlyFailCriteriaMet = CbFALSE;
		}
	}
	else
	{
		VbEPSD_CamRatnlyFailCriteriaMet = CbFALSE;
		VcEPSD_CamCylEventCntr = V_COUNT_BYTE(0);
	}
}

/*****************************************************************************
 *
 * Function:            ProcessEPSD_CamRatnlyCntrEval
 * Description:         Process_Cam_Rationality_Counter_Evaluation.
 *                      This process will update and evaluate the
 *                      Cam_Rationality fail/pass counters and determine
 *                      if a fail/pass has occurred. The pass counters are
 *                      incremented for consecutive pass occurrences and
 *                      reset for any fail occurrence. The fail counters are
 *                      incremented for any fail occurrence.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
static void ProcessEPSD_CamRatnlyCntrEval(void)
{
	if (SbEPSD_CamRatnlyTestComplete_Internal)
	{
		//SbEPSD_CamRatnlyTestFailed = CbFALSE;
		SbEPSD_CamRatnlyTestComplete_Internal = CbFALSE;
		ScEPSD_CamRatnlyFailCntr = V_COUNT_WORD(0);
		ScEPSD_CamRatnlyPassCntr = V_COUNT_WORD(0);
	}

	if (VbEPSD_CamRatnlyFailCriteriaMet)
	{
		ScEPSD_CamRatnlyFailCntr++;

		if (ScEPSD_CamRatnlyFailCntr >= KcEPSD_CamRationalityFailThrsh)
		{
			SbEPSD_CamRatnlyTestFailed = CbTRUE;
			SbEPSD_CamRatnlyTestComplete_Internal = CbTRUE;
		}
		else
		{
			SbEPSD_CamRatnlyTestComplete_Internal = CbFALSE;
		}
	}
	else if (SbEPSD_CamRatnlyEnblCriteriaMet)
	{
		ScEPSD_CamRatnlyPassCntr++;
		if (ScEPSD_CamRatnlyPassCntr >= KcEPSD_CamRationalityPassThrsh)
		{
			SbEPSD_CamRatnlyTestFailed = CbFALSE;
			SbEPSD_CamRatnlyTestComplete_Internal = CbTRUE;
		}
		else
		{
			SbEPSD_CamRatnlyTestComplete_Internal = CbFALSE;
		}
	}
}


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
*
******************************************************************************/
