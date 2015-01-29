/*****************************************************************************
* Filename:  estdmall.c
*                                                                           
* Description:   Electronic Spark Timing Fault Diagnostic
*
* List of functions:
*               InitESTD_RstToKeyOn()
*               InitESTD_OFVC_Clear()
*               MngESTD_CylEventTasks()
*               InitESTD_ShutdownToProgToKeyOn()
*               EvalESTD_EnableCriteria()
*               DtrmnESTD_EST_OutputNumber()
*               CheckESTD_FaultStatus()
*               UpdateESTD_FaultCounters()
*               PerfmESTD_CounterEvaluation()
*               ReportESTD_FaultTestResults()
*               InitESTD_Common()
*
* List of inlines:    
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics 1997
*****************************************************************************/

/******************************************************************************
*  Global Data Type Include Files
******************************************************************************/
#include "estdpapi.h" /* For Declaration-Definition Check */
#include "estdcald.h" /* For Declaration-Definition Check */
#include "mall_lib.h"
#include "timclib.h"
#include "intr_ems.h"
#include "v_power.h"
#include "hal_eng.h"

#define CcSYST_NUM_OF_EST_OUTPUTS 4

/******************************************************************************
*  Type declaration
*****************************************************************************/
enum /* ESTD steady state timers */
{
	CeESTD_FaultEnblDlyTmr,
	CcESTD_Num7p8Tmrs
};

/*****************************************************************************
 *  Global Data Define
 *****************************************************************************/
DefTIMC_StopWatches16(VaESTD_t_7p8msTimerArray,
                      VaESTD_7p8msTimerEnbl,
                      R7p8125ms,
                      CcESTD_Num7p8Tmrs);



/******************************************************************************
*  Static Data Define
******************************************************************************/
//TbBOOLEAN     VaESTD_FailCriteriaMet[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     VaESTD_STBFailCriteriaMet[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     VaESTD_STGFailCriteriaMet[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     VaESTD_OpenFailCriteriaMet[CcSYST_NUM_OF_EST_OUTPUTS];

TbBOOLEAN     SbESTD_FaultEnblCriteriaMet;

//T_COUNT_BYTE  SaESTD_FaultFailureCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_STBFaultFailureCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_STGFaultFailureCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_OpenFaultFailureCounter[CcSYST_NUM_OF_EST_OUTPUTS];

//T_COUNT_BYTE  SaESTD_FaultSampleCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_STBFaultSampleCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_STGFaultSampleCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_OpenFaultSampleCounter[CcSYST_NUM_OF_EST_OUTPUTS];

TbBOOLEAN     SaESTD_FaultTestComplete[CcSYST_NUM_OF_EST_OUTPUTS];
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN     SaESTD_STBFaultTestFailed[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     SaESTD_STGFaultTestFailed[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     SaESTD_OpenFaultTestFailed[CcSYST_NUM_OF_EST_OUTPUTS];
#pragma section DATA " " ".bss"
T_COUNT_BYTE  ScESTD_EST_OutputNumber;
TbBOOLEAN     SbESTD_EST_FaultResetRequest;
TbBOOLEAN     SaESTD_STBFaultTestComplete_Internal[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     SaESTD_STGFaultTestComplete_Internal[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     SaESTD_OpenFaultTestComplete_Internal[CcSYST_NUM_OF_EST_OUTPUTS];
/*****************************************************************************/

/******************************************************************************
*  Local Function declarations
******************************************************************************/
static void EvalESTD_EnableCriteria(void);
static void DtrmnESTD_EST_OutputNumber(void);
static void CheckESTD_FaultStatus(void);
static void UpdateESTD_FaultCounters(void);
static void PerfmESTD_CounterEvaluation(void);
static void InitESTD_Common(void);


/*****************************************************************************
 *
 * Function:           InitESTD_ShutdownInProgToKeyOn
 * Type:
 * Description:        This process runs the Controller Diagnostic shutdown
 *                     in progress to key on.
 *
 * Parameters:         None
 * Return:             None
 *****************************************************************************/

void InitESTD_ShutdownInProgToKeyOn (void)
{
  InitESTD_Common();
}

/*****************************************************************************
 *
 * Function:           InitESTD_ShutdownInProgToKeyOn
 * Type:
 * Description:        This process runs the Controller Diagnostic shutdown
 *                     in progress to key on.
 *
 * Parameters:         None
 * Return:             None
 *****************************************************************************/

//FAR_COS void InitESTD_RstToKeyOff (void)
//{
//  InitESTD_Common();
//}

/*****************************************************************************
 *
 * Function:           InitESTD_Common
 * Type:
 * Description:        This process initializes ESTD variables 
 *                     
 * Parameters:         None
 * Return:             None
 *****************************************************************************/
static void InitESTD_Common(void)
{
	BYTE LcESTD_EST_Count;

	SbESTD_FaultEnblCriteriaMet = CbFALSE;
	ScESTD_EST_OutputNumber = V_COUNT_BYTE(0);

	HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_FaultEnblDlyTmr);
	SetTIMC_StopWatch16 (VaESTD_t_7p8msTimerArray,CeESTD_FaultEnblDlyTmr, C_R7p8125ms16(0));

	for (LcESTD_EST_Count = 0;
		LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
		LcESTD_EST_Count++)
	{
		VaESTD_STBFailCriteriaMet[LcESTD_EST_Count] = CbFALSE;
		VaESTD_STGFailCriteriaMet[LcESTD_EST_Count] = CbFALSE;
		VaESTD_OpenFailCriteriaMet[LcESTD_EST_Count] = CbFALSE;
		
		SaESTD_STBFaultFailureCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		SaESTD_STGFaultFailureCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		SaESTD_OpenFaultFailureCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		
		SaESTD_STBFaultSampleCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		SaESTD_STGFaultSampleCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
        SaESTD_OpenFaultSampleCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		
		//SaESTD_FaultTestComplete[LcESTD_EST_Count] = CbFALSE;
		SaESTD_STBFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
		SaESTD_STBFaultTestFailed[LcESTD_EST_Count] = CbFALSE;
		
		SaESTD_STGFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
		SaESTD_STGFaultTestFailed[LcESTD_EST_Count] = CbFALSE;
		
		SaESTD_OpenFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
		SaESTD_OpenFaultTestFailed[LcESTD_EST_Count] = CbFALSE;
		
	}
}

/*****************************************************************************
 *
 * Function:        MngESTD_RefEventTasks
 *
 * Description:     This procedure will be called by the operating system
 *                  during every 2X/3X Cylinder Reference event. The procedure
 *                  includes calls to all Reference event functions.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
void MngESTD_RefEventTasks(void)
{
/*  UpdateTIMC_StopWatchesUp16(VaESTD_t_7p8msTimerArray,
                             VaESTD_7p8msTimerEnbl,
                             CcESTD_Num7p8Tmrs);*/
	BYTE LcESTD_EST_Count;
	EvalESTD_EnableCriteria();
	DtrmnESTD_EST_OutputNumber();
	/* Execute EST Circuits Fail Pass Evaluation */
	CheckESTD_FaultStatus();

	UpdateESTD_FaultCounters();
	PerfmESTD_CounterEvaluation();

	for (LcESTD_EST_Count = 0; LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS; LcESTD_EST_Count++) {
		SaESTD_FaultTestComplete[LcESTD_EST_Count] |= \
			SaESTD_STBFaultTestComplete_Internal[LcESTD_EST_Count]\
			|SaESTD_STGFaultTestComplete_Internal[LcESTD_EST_Count]\
			|SaESTD_OpenFaultTestComplete_Internal[LcESTD_EST_Count];
	}
}

/*****************************************************************************
 * Function:           MngESTD_7p81msTasks
 * Description:        This process will update
 *                     CeESTD_FaultEnblDlyTmr.
 *
 * Parameters:         None
 * Return:             None
 *****************************************************************************/
void MngESTD_7p81msTasks (void)
{
	/*  update CeESTD_FaultEnblDlyTmr every 7.8125ms  */
	UpdateTIMC_StopWatchesUp16(VaESTD_t_7p8msTimerArray,
							 VaESTD_7p8msTimerEnbl,
							 CcESTD_Num7p8Tmrs);
}

/*****************************************************************************
 *
 * Function:        EvalESTD_EnableCriteria
 *
 * Description:     This process examines all the enable criteria for the
 *                  EST diagnostics. An enable delay timer has been added
 *                  to address hardware performance on the MR-140 controller,
 *                  with EST through a PSVI; this configuration exhibits 
 *                  temporary failure condition on the EST Failure register
 *                  bits up to a maximum duration of 500ms.
 * Parameters:      None
 * Return:          None
 *****************************************************************************/
static void EvalESTD_EnableCriteria(void)
{
	if( GetVIOS_U_IgnVolt() < KfESTD_U_IgnVoltResetThrsh)
	{
		SbESTD_FaultEnblCriteriaMet = CbFALSE;
		HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_FaultEnblDlyTmr);
		SetTIMC_StopWatch16 (VaESTD_t_7p8msTimerArray,CeESTD_FaultEnblDlyTmr,
						  C_R7p8125ms16(0));
		SbESTD_EST_FaultResetRequest = CbTRUE;
	}
	else
	{
		SbESTD_EST_FaultResetRequest = CbFALSE;
	}
	if ( (GetVIOS_IgnSt() == CeIGN_ON))
		// && (GetVIOS_FirstValidCrankTooth()) )
	{
		if(GetTIMC_t_StopWatch16(VaESTD_t_7p8msTimerArray,CeESTD_FaultEnblDlyTmr)
							  >= KfESTD_t_EnableDelayTime )
		{
			SbESTD_FaultEnblCriteriaMet = CbTRUE;
			HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_FaultEnblDlyTmr);
		}
		else
		{
			SbESTD_FaultEnblCriteriaMet = CbFALSE;
			ResumeTIMC_StopWatch(VaESTD_7p8msTimerEnbl,CeESTD_FaultEnblDlyTmr);
		}
	}
	else
	{
		SbESTD_FaultEnblCriteriaMet = CbFALSE;
	}
}

/*****************************************************************************
 *
 * Function:	    DtrmnESTD_EST_OutputNumber
 *
 * Description:	    This process will convert the cylinder number for the
 *		    cylinder currently indicated by the input flow into the
 *		    corresponding EST line number that fires that particular
 *		    cylinder.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
static void DtrmnESTD_EST_OutputNumber(void)
{
	ScESTD_EST_OutputNumber = HAL_Eng_Get_Cyl_Number();
}


/*****************************************************************************
 *
 * Function:	    CheckESTD_FaultStatus
 *
 * Description:	    This process will use the input from the self-diagnosing
 *                  hardware to set flags indicating the current fail or pass
 *                  status of each EST output.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
static void CheckESTD_FaultStatus(void)
{
	if (SbESTD_FaultEnblCriteriaMet != CbFALSE)
	{
	   // short to battery
		if (GetAPI_EST_CircuitState(ScESTD_EST_OutputNumber,CeEST_STBFAULT) == CeEST_FAULTED)
		{
			VaESTD_STBFailCriteriaMet[ScESTD_EST_OutputNumber] = CbTRUE;
		}
		else
		{
			VaESTD_STBFailCriteriaMet[ScESTD_EST_OutputNumber] = CbFALSE;
		}
       // short to groud
		if (GetAPI_EST_CircuitState(ScESTD_EST_OutputNumber,CeEST_STGFAULT) == CeEST_FAULTED)
		{
			VaESTD_STGFailCriteriaMet[ScESTD_EST_OutputNumber] = CbTRUE;
		}
		else
		{
			VaESTD_STGFailCriteriaMet[ScESTD_EST_OutputNumber] = CbFALSE;
		}
       // open
		if (GetAPI_EST_CircuitState(ScESTD_EST_OutputNumber,CeEST_OpenFAULT) == CeEST_FAULTED)
		{
			VaESTD_OpenFailCriteriaMet[ScESTD_EST_OutputNumber] = CbTRUE;
		}
		else
		{
			VaESTD_OpenFailCriteriaMet[ScESTD_EST_OutputNumber] = CbFALSE;
		}
	}    /* END IF Enable Criteria Met = TRUE */
}


/*****************************************************************************
 *
 * Function:	    UpdateESTD_FaultCounters
 *
 * Description:	    This process will update the sample and failure counters
 *                  for the EST diagnostics. If the tests were completed during
 *                  the previous loop execution, then the counters will be
 *                  reset on the current execution.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
static void UpdateESTD_FaultCounters (void)
{
	BYTE LcESTD_EST_Count;

	if(SbESTD_EST_FaultResetRequest)
	{
		for (LcESTD_EST_Count = 0;
			 LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
			 LcESTD_EST_Count++)
		{
			SaESTD_STGFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_STGFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

			SaESTD_STBFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_STBFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

			SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		}
	}

	if (SbESTD_FaultEnblCriteriaMet != CbFALSE)
	{
		if (SaESTD_STBFaultTestComplete_Internal[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_STBFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_STBFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		}
		
		if (SaESTD_STGFaultTestComplete_Internal[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			
			SaESTD_STGFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_STGFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		}

		if (SaESTD_OpenFaultTestComplete_Internal[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			
			SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		}
		SaESTD_STBFaultSampleCounter[ScESTD_EST_OutputNumber]++;
		SaESTD_STGFaultSampleCounter[ScESTD_EST_OutputNumber]++;
		SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber]++;
		
		if (VaESTD_STBFailCriteriaMet[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_STBFaultFailureCounter[ScESTD_EST_OutputNumber]++;
		}

		if (VaESTD_STGFailCriteriaMet[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_STGFaultFailureCounter[ScESTD_EST_OutputNumber]++;
		}

		if (VaESTD_OpenFailCriteriaMet[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber]++;
		}
	}
	else 
	{
		SaESTD_STGFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		SaESTD_STGFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		SaESTD_STBFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		SaESTD_STBFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		
	}
}

/*****************************************************************************
 *
 * Function:        PerfmESTD_CounterEvaluation
 *
 * Description:     This process will examine the failure counter and the
 *                  sample counter for the EST diagnostics and indicate test
 *                  complete status for each EST individually. If a test was
 *                  competed in a previous loop, then that test complete flag
 *                  will be reset during the current loop.
 *
 * Parameters:      None
 * Return:          None
 *****************************************************************************/
static void PerfmESTD_CounterEvaluation (void)
{
	BYTE LcESTD_EST_Count;

	if(SbESTD_EST_FaultResetRequest)
	{
		for (LcESTD_EST_Count = 0;
		LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
		LcESTD_EST_Count++)
		{
			SaESTD_STBFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
			SaESTD_STBFaultTestFailed[LcESTD_EST_Count] = CbFALSE; 

			SaESTD_STGFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
			SaESTD_STGFaultTestFailed[LcESTD_EST_Count] = CbFALSE; 

			SaESTD_OpenFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
			SaESTD_OpenFaultTestFailed[LcESTD_EST_Count] = CbFALSE; 
		}
	}
    //short to battery
	if(SaESTD_STBFaultTestComplete_Internal[ScESTD_EST_OutputNumber])
	{
		SaESTD_STBFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbFALSE;
	}

	if (SaESTD_STBFaultFailureCounter[ScESTD_EST_OutputNumber] >= KcESTD_FailThrsh)
	{
		SaESTD_STBFaultTestFailed[ScESTD_EST_OutputNumber] = CbTRUE;
		SaESTD_STBFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
	else if (SaESTD_STBFaultSampleCounter[ScESTD_EST_OutputNumber] >= 
			KcESTD_SampleThrsh)
	{
		SaESTD_STBFaultTestFailed[ScESTD_EST_OutputNumber] = CbFALSE;
		SaESTD_STBFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
    //short to ground
	if(SaESTD_STGFaultTestComplete_Internal[ScESTD_EST_OutputNumber])
	{
		SaESTD_STGFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbFALSE;
	}

	if (SaESTD_STGFaultFailureCounter[ScESTD_EST_OutputNumber] >= KcESTD_FailThrsh)
	{
		SaESTD_STGFaultTestFailed[ScESTD_EST_OutputNumber] = CbTRUE;
		SaESTD_STGFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
	else if (SaESTD_STGFaultSampleCounter[ScESTD_EST_OutputNumber] >= 
			KcESTD_SampleThrsh)
	{
		SaESTD_STGFaultTestFailed[ScESTD_EST_OutputNumber] = CbFALSE;
		SaESTD_STGFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
    //Open
	if(SaESTD_OpenFaultTestComplete_Internal[ScESTD_EST_OutputNumber])
	{
		SaESTD_OpenFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbFALSE;
	}

	if (SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber] >= KcESTD_FailThrsh)
	{
		SaESTD_OpenFaultTestFailed[ScESTD_EST_OutputNumber] = CbTRUE;
		SaESTD_OpenFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
	else if (SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber] >= 
			KcESTD_SampleThrsh)
	{
		SaESTD_OpenFaultTestFailed[ScESTD_EST_OutputNumber] = CbFALSE;
		SaESTD_OpenFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
}



/******************************************************************************
* 
*****************************************************************************/
