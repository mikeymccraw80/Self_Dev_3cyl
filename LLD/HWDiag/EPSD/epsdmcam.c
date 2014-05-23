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
#include "dd_cam_interface.h"

#define CcSYST_NUM_OF_CYLINDERS 4
/******************************************************************************
 *  Global Data Define
 *****************************************************************************/
TbBOOLEAN  VbEPSD_Cam1NoSigFailCriteriaMet;
TbBOOLEAN  VbEPSD_Cam2NoSigFailCriteriaMet;
TbBOOLEAN  VbEPSD_Cam1RatnlyFailCriteriaMet;
TbBOOLEAN  VbEPSD_Cam2RatnlyFailCriteriaMet;
T_COUNT_BYTE  VcEPSD_Cam1CylEventCntr;
T_COUNT_BYTE  VcEPSD_Cam2CylEventCntr;

/******************************************************************************
*  Static Data Define
******************************************************************************/
TbBOOLEAN  SbEPSD_CamNoSigEnblCriteriaMet;
TbBOOLEAN  SbEPSD_Cam1NoSigTestComplete;
TbBOOLEAN  SbEPSD_Cam2NoSigTestComplete;

TbBOOLEAN  SbEPSD_Cam1RatnlyEnblCriteriaMet;
TbBOOLEAN  SbEPSD_Cam2RatnlyEnblCriteriaMet;
TbBOOLEAN  SbEPSD_Cam1RatnlyTestComplete;
TbBOOLEAN  SbEPSD_Cam2RatnlyTestComplete;
T_COUNT_WORD  ScEPSD_Cam1NoSigCylEventCntr;
T_COUNT_WORD  ScEPSD_Cam2NoSigCylEventCntr;
T_COUNT_WORD  ScEPSD_Cam1RatnlyFailCntr;
T_COUNT_WORD  ScEPSD_Cam2RatnlyFailCntr;
T_COUNT_WORD  ScEPSD_Cam1RatnlyPassCntr;
T_COUNT_WORD  ScEPSD_Cam2RatnlyPassCntr;
TbBOOLEAN  SbEPSD_Cam1NoSigTestComplete_Internal;
TbBOOLEAN  SbEPSD_Cam2NoSigTestComplete_Internal;
TbBOOLEAN  SbEPSD_Cam1RatnlyTestComplete_Internal;
TbBOOLEAN  SbEPSD_Cam2RatnlyTestComplete_Internal;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN  SbEPSD_Cam1RatnlyTestFailed;
TbBOOLEAN  SbEPSD_Cam1NoSigTestFailed;
TbBOOLEAN  SbEPSD_Cam2RatnlyTestFailed;
TbBOOLEAN  SbEPSD_Cam2NoSigTestFailed;
#pragma section DATA " " ".bss"

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
	SbEPSD_Cam1NoSigTestComplete_Internal = CbFALSE;
	SbEPSD_Cam2NoSigTestComplete_Internal = CbFALSE;
	VbEPSD_Cam1NoSigFailCriteriaMet = CbFALSE;
	VbEPSD_Cam2NoSigFailCriteriaMet = CbFALSE;

	ScEPSD_Cam1NoSigCylEventCntr = V_COUNT_WORD(0);
	ScEPSD_Cam2NoSigCylEventCntr = V_COUNT_WORD(0);
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
	SbEPSD_Cam1RatnlyEnblCriteriaMet = CbFALSE;
	VbEPSD_Cam1RatnlyFailCriteriaMet = CbFALSE;
	SbEPSD_Cam1RatnlyTestComplete    = CbFALSE;
	SbEPSD_Cam1NoSigTestComplete = CbFALSE;
	SbEPSD_Cam1RatnlyTestComplete_Internal = CbFALSE;

	SbEPSD_Cam2RatnlyEnblCriteriaMet = CbFALSE;
	VbEPSD_Cam2RatnlyFailCriteriaMet = CbFALSE;
	SbEPSD_Cam2RatnlyTestComplete    = CbFALSE;
	SbEPSD_Cam2NoSigTestComplete = CbFALSE;
	SbEPSD_Cam2RatnlyTestComplete_Internal = CbFALSE;

	ScEPSD_Cam1RatnlyFailCntr = V_COUNT_WORD(0);
	ScEPSD_Cam1RatnlyPassCntr = V_COUNT_WORD(0);
	VcEPSD_Cam1CylEventCntr   = V_COUNT_BYTE(0);
	ScEPSD_Cam2RatnlyFailCntr = V_COUNT_WORD(0);
	ScEPSD_Cam2RatnlyPassCntr = V_COUNT_WORD(0);
	VcEPSD_Cam2CylEventCntr   = V_COUNT_BYTE(0);
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
	SbEPSD_Cam1NoSigTestComplete |=SbEPSD_Cam1NoSigTestComplete_Internal;
	SbEPSD_Cam2NoSigTestComplete |=SbEPSD_Cam2NoSigTestComplete_Internal;
	ProcessEPSD_CamRatnlyFaultEval();
	ProcessEPSD_CamRatnlyCntrEval();
	SbEPSD_Cam1RatnlyTestComplete |= SbEPSD_Cam1RatnlyTestComplete_Internal;
	SbEPSD_Cam2RatnlyTestComplete |= SbEPSD_Cam2RatnlyTestComplete_Internal;
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
		if (SbEPSD_Cam1NoSigTestFailed == CbFALSE)
		{
			SbEPSD_Cam1RatnlyEnblCriteriaMet = CbTRUE;
		}
		else
		{
			SbEPSD_Cam1RatnlyEnblCriteriaMet = CbFALSE;
		}
	}
	else
	{
		SbEPSD_CamNoSigEnblCriteriaMet = CbFALSE;
		SbEPSD_Cam1RatnlyEnblCriteriaMet = CbFALSE;
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

	if (SbEPSD_CamNoSigEnblCriteriaMet && GetVIOS_Cam1Stuck())
	{
		VbEPSD_Cam1NoSigFailCriteriaMet = CbTRUE;
	}
	else
	{
		VbEPSD_Cam1NoSigFailCriteriaMet = CbFALSE;
	}

	if (SbEPSD_CamNoSigEnblCriteriaMet && GetVIOS_Cam2Stuck())
	{
		VbEPSD_Cam2NoSigFailCriteriaMet = CbTRUE;
	}
	else
	{
		VbEPSD_Cam2NoSigFailCriteriaMet = CbFALSE;
	}

/*      Process_Cam_No_Signal_Counter_Evaluation
 *      ========================================
 *      This process will activate an event counter and
 *      check to see if the counter exceeds the failure
 *      threshold for the Cam_No_Signal fault. */

	if (VbEPSD_Cam1NoSigFailCriteriaMet)
	{
		ScEPSD_Cam1NoSigCylEventCntr++;
		if (ScEPSD_Cam1NoSigCylEventCntr >= KcEPSD_CamNoSignalCylEvent)
		{
			SbEPSD_Cam1NoSigTestFailed = CbTRUE;
			SbEPSD_Cam1NoSigTestComplete_Internal = CbTRUE;
			ScEPSD_Cam1NoSigCylEventCntr = V_COUNT_WORD(0);
		}
		else
		{
			SbEPSD_Cam1NoSigTestComplete_Internal = CbFALSE;
		}
	}
	else if (SbEPSD_CamNoSigEnblCriteriaMet)
	{
		SbEPSD_Cam1NoSigTestFailed = CbFALSE;
		SbEPSD_Cam1NoSigTestComplete_Internal = CbTRUE;
		ScEPSD_Cam1NoSigCylEventCntr = V_COUNT_WORD(0);
	}
	else
	{
		SbEPSD_Cam1NoSigTestComplete_Internal = CbFALSE;
	}

	if (VbEPSD_Cam2NoSigFailCriteriaMet)
	{
		ScEPSD_Cam2NoSigCylEventCntr++;
		if (ScEPSD_Cam2NoSigCylEventCntr >= KcEPSD_CamNoSignalCylEvent)
		{
			SbEPSD_Cam2NoSigTestFailed = CbTRUE;
			SbEPSD_Cam2NoSigTestComplete_Internal = CbTRUE;
			ScEPSD_Cam2NoSigCylEventCntr = V_COUNT_WORD(0);
		}
		else
		{
			SbEPSD_Cam2NoSigTestComplete_Internal = CbFALSE;
		}
	}
	else if (SbEPSD_CamNoSigEnblCriteriaMet)
	{
		SbEPSD_Cam2NoSigTestFailed = CbFALSE;
		SbEPSD_Cam2NoSigTestComplete_Internal = CbTRUE;
		ScEPSD_Cam2NoSigCylEventCntr = V_COUNT_WORD(0);
	}
	else
	{
		SbEPSD_Cam2NoSigTestComplete_Internal = CbFALSE;
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
	if (SbEPSD_Cam1RatnlyEnblCriteriaMet)
	{
		VcEPSD_Cam1CylEventCntr++;
		if (CAM_Get_State_Change_Occurred(CAM1))
		{
			if (VcEPSD_Cam1CylEventCntr == CcSYST_NUM_OF_CYLINDERS )
			{
				VbEPSD_Cam1RatnlyFailCriteriaMet = CbFALSE;
				VcEPSD_Cam1CylEventCntr = V_COUNT_BYTE(0);
			}
			else
			{
				VbEPSD_Cam1RatnlyFailCriteriaMet = CbTRUE;
				VcEPSD_Cam1CylEventCntr = V_COUNT_BYTE(0);
			}
		}
		else if (VcEPSD_Cam1CylEventCntr == CcSYST_NUM_OF_CYLINDERS )
		{
			VcEPSD_Cam1CylEventCntr = V_COUNT_BYTE(0);
			VbEPSD_Cam1RatnlyFailCriteriaMet = CbTRUE;
		}
		else
		{
		   VbEPSD_Cam1RatnlyFailCriteriaMet = CbFALSE;
		}
	}
	else
	{
		VbEPSD_Cam1RatnlyFailCriteriaMet = CbFALSE;
		VcEPSD_Cam1CylEventCntr = V_COUNT_BYTE(0);
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
	if (SbEPSD_Cam1RatnlyTestComplete_Internal)
	{
		//SbEPSD_Cam1RatnlyTestFailed = CbFALSE;
		SbEPSD_Cam1RatnlyTestComplete_Internal = CbFALSE;
		ScEPSD_Cam1RatnlyFailCntr = V_COUNT_WORD(0);
		ScEPSD_Cam1RatnlyPassCntr = V_COUNT_WORD(0);
	}

	if (VbEPSD_Cam1RatnlyFailCriteriaMet)
	{
		ScEPSD_Cam1RatnlyFailCntr++;

		if (ScEPSD_Cam1RatnlyFailCntr >= KcEPSD_CamRationalityFailThrsh)
		{
			SbEPSD_Cam1RatnlyTestFailed = CbTRUE;
			SbEPSD_Cam1RatnlyTestComplete_Internal = CbTRUE;
		}
		else
		{
			SbEPSD_Cam1RatnlyTestComplete_Internal = CbFALSE;
		}
	}
	else if (SbEPSD_Cam1RatnlyEnblCriteriaMet)
	{
		ScEPSD_Cam1RatnlyPassCntr++;
		if (ScEPSD_Cam1RatnlyPassCntr >= KcEPSD_CamRationalityPassThrsh)
		{
			SbEPSD_Cam1RatnlyTestFailed = CbFALSE;
			SbEPSD_Cam1RatnlyTestComplete_Internal = CbTRUE;
		}
		else
		{
			SbEPSD_Cam1RatnlyTestComplete_Internal = CbFALSE;
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
