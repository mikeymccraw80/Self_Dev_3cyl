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
	CeESTD_ShortFaultEnblDlyTmr,
	CeESTD_OpenFaultEnblDlyTmr,
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
TbBOOLEAN     VaESTD_ShortFailCriteriaMet[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     VaESTD_OpenFailCriteriaMet[CcSYST_NUM_OF_EST_OUTPUTS];

TbBOOLEAN     SbESTD_ShortFaultEnblCriteriaMet;
TbBOOLEAN     SbESTD_OpenFaultEnblCriteriaMet;

//T_COUNT_BYTE  SaESTD_FaultFailureCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_ShortFaultFailureCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_OpenFaultFailureCounter[CcSYST_NUM_OF_EST_OUTPUTS];

//T_COUNT_BYTE  SaESTD_FaultSampleCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_ShortFaultSampleCounter[CcSYST_NUM_OF_EST_OUTPUTS];
T_COUNT_BYTE  SaESTD_OpenFaultSampleCounter[CcSYST_NUM_OF_EST_OUTPUTS];

TbBOOLEAN     SaESTD_FaultTestComplete[CcSYST_NUM_OF_EST_OUTPUTS];
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN     SaESTD_ShortFaultTestFailed[CcSYST_NUM_OF_EST_OUTPUTS];
TbBOOLEAN     SaESTD_OpenFaultTestFailed[CcSYST_NUM_OF_EST_OUTPUTS];
#pragma section DATA " " ".bss"
T_COUNT_BYTE  ScESTD_EST_OutputNumber;
TbBOOLEAN     SbESTD_EST_ShortFaultResetRequest;
TbBOOLEAN     SbESTD_EST_OpenFaultResetRequest;
TbBOOLEAN     SaESTD_ShortFaultTestComplete_Internal[CcSYST_NUM_OF_EST_OUTPUTS];
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

	SbESTD_ShortFaultEnblCriteriaMet = CbFALSE;
	SbESTD_OpenFaultEnblCriteriaMet = CbFALSE;
	ScESTD_EST_OutputNumber = V_COUNT_BYTE(0);

	HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_ShortFaultEnblDlyTmr);
	HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_OpenFaultEnblDlyTmr);
	SetTIMC_StopWatch16 (VaESTD_t_7p8msTimerArray,CeESTD_ShortFaultEnblDlyTmr, C_R7p8125ms16(0));
	SetTIMC_StopWatch16 (VaESTD_t_7p8msTimerArray,CeESTD_OpenFaultEnblDlyTmr, C_R7p8125ms16(0));

	for (LcESTD_EST_Count = 0;
		LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
		LcESTD_EST_Count++)
	{
		VaESTD_ShortFailCriteriaMet[LcESTD_EST_Count] = CbFALSE;
		VaESTD_OpenFailCriteriaMet[LcESTD_EST_Count] = CbFALSE;
		
		SaESTD_ShortFaultFailureCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		SaESTD_OpenFaultFailureCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		
		SaESTD_ShortFaultSampleCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
        SaESTD_OpenFaultSampleCounter[LcESTD_EST_Count] = V_COUNT_BYTE(0);
		
		//SaESTD_FaultTestComplete[LcESTD_EST_Count] = CbFALSE;
		SaESTD_ShortFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
		SaESTD_ShortFaultTestFailed[LcESTD_EST_Count] = CbFALSE;
			
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
			SaESTD_ShortFaultTestComplete_Internal[LcESTD_EST_Count]\
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
    //Short to battery
	if( GetVIOS_U_IgnVolt() < KfESTD_U_ShortIgnVoltResetThrsh)
	{
		SbESTD_ShortFaultEnblCriteriaMet = CbFALSE;
		HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_ShortFaultEnblDlyTmr);
		SetTIMC_StopWatch16 (VaESTD_t_7p8msTimerArray,CeESTD_ShortFaultEnblDlyTmr,
						  C_R7p8125ms16(0));
		SbESTD_EST_ShortFaultResetRequest = CbTRUE;
	}
	else
	{
		SbESTD_EST_ShortFaultResetRequest = CbFALSE;
	}
    //Short to ground & Open
	if( GetVIOS_U_IgnVolt() < KfESTD_U_OpenIgnVoltResetThrsh)
	{
		SbESTD_OpenFaultEnblCriteriaMet = CbFALSE;
		HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_OpenFaultEnblDlyTmr);
		SetTIMC_StopWatch16 (VaESTD_t_7p8msTimerArray,CeESTD_OpenFaultEnblDlyTmr,
						  C_R7p8125ms16(0));
		SbESTD_EST_OpenFaultResetRequest = CbTRUE;
	}
	else
	{
		SbESTD_EST_OpenFaultResetRequest = CbFALSE;
	}

	
	if ( (GetVIOS_IgnSt() == CeIGN_ON))
		// && (GetVIOS_FirstValidCrankTooth()) )
	{   
	    //Short to battery
		if(GetTIMC_t_StopWatch16(VaESTD_t_7p8msTimerArray,CeESTD_ShortFaultEnblDlyTmr)
							  >= KfESTD_t_EnableDelayTime )
		{
			SbESTD_ShortFaultEnblCriteriaMet = CbTRUE;
			HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_ShortFaultEnblDlyTmr);
		}
		else
		{
			SbESTD_ShortFaultEnblCriteriaMet = CbFALSE;
			ResumeTIMC_StopWatch(VaESTD_7p8msTimerEnbl,CeESTD_ShortFaultEnblDlyTmr);
		}
        //Short to ground & Open
		if(GetTIMC_t_StopWatch16(VaESTD_t_7p8msTimerArray,CeESTD_OpenFaultEnblDlyTmr)
							  >= KfESTD_t_EnableDelayTime )
		{
			SbESTD_OpenFaultEnblCriteriaMet = CbTRUE;
			HaltTIMC_StopWatch (VaESTD_7p8msTimerEnbl, CeESTD_OpenFaultEnblDlyTmr);
		}
		else
		{
			SbESTD_OpenFaultEnblCriteriaMet = CbFALSE;
			ResumeTIMC_StopWatch(VaESTD_7p8msTimerEnbl,CeESTD_OpenFaultEnblDlyTmr);
		}
	}
	else
	{
		SbESTD_ShortFaultEnblCriteriaMet = CbFALSE;
		SbESTD_OpenFaultEnblCriteriaMet = CbFALSE;
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
    //Short to battery
	if (SbESTD_ShortFaultEnblCriteriaMet != CbFALSE)
	{

		if (GetAPI_EST_CircuitState(ScESTD_EST_OutputNumber,CeEST_ShortFAULT) == CeEST_FAULTED)
		{
			VaESTD_ShortFailCriteriaMet[ScESTD_EST_OutputNumber] = CbTRUE;
		}
		else
		{
			VaESTD_ShortFailCriteriaMet[ScESTD_EST_OutputNumber] = CbFALSE;
		}
	}
    //short to ground & Open
	if (SbESTD_OpenFaultEnblCriteriaMet != CbFALSE)
	{

		if (GetAPI_EST_CircuitState(ScESTD_EST_OutputNumber,CeEST_OpenFAULT) == CeEST_FAULTED)
		{
			VaESTD_OpenFailCriteriaMet[ScESTD_EST_OutputNumber] = CbTRUE;
		}
		else
		{
			VaESTD_OpenFailCriteriaMet[ScESTD_EST_OutputNumber] = CbFALSE;
		}
	}/* END IF Enable Criteria Met = TRUE */
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

	if(SbESTD_EST_ShortFaultResetRequest)
	{
		for (LcESTD_EST_Count = 0;
			 LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
			 LcESTD_EST_Count++)
		{

			SaESTD_ShortFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_ShortFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		}
	}
	
	if(SbESTD_EST_OpenFaultResetRequest)
	{
		for (LcESTD_EST_Count = 0;
			 LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
			 LcESTD_EST_Count++)
		{

			SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		}
	}
	//Short to battery
	if (SbESTD_ShortFaultEnblCriteriaMet != CbFALSE)
	{
		if (SaESTD_ShortFaultTestComplete_Internal[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_ShortFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_ShortFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		}

		SaESTD_ShortFaultSampleCounter[ScESTD_EST_OutputNumber]++;
		
		if (VaESTD_ShortFailCriteriaMet[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_ShortFaultFailureCounter[ScESTD_EST_OutputNumber]++;
		}

	}
	else 
	{
		SaESTD_ShortFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		SaESTD_ShortFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
		
	}
    //short to ground&Open
	if (SbESTD_OpenFaultEnblCriteriaMet != CbFALSE)
	{
		if (SaESTD_OpenFaultTestComplete_Internal[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);
			SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber] = V_COUNT_BYTE(0);

		}

		SaESTD_OpenFaultSampleCounter[ScESTD_EST_OutputNumber]++;
		
		if (VaESTD_OpenFailCriteriaMet[ScESTD_EST_OutputNumber] != CbFALSE)
		{
			SaESTD_OpenFaultFailureCounter[ScESTD_EST_OutputNumber]++;
		}
	}
	else 
	{

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

	if(SbESTD_EST_ShortFaultResetRequest)
	{
		for (LcESTD_EST_Count = 0;
		LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
		LcESTD_EST_Count++)
		{
			SaESTD_ShortFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
			//SaESTD_ShortFaultTestFailed[LcESTD_EST_Count] = CbFALSE; 
		}
	}

	if(SbESTD_EST_OpenFaultResetRequest)
	{
		for (LcESTD_EST_Count = 0;
		LcESTD_EST_Count < CcSYST_NUM_OF_EST_OUTPUTS;
		LcESTD_EST_Count++)
		{
			SaESTD_OpenFaultTestComplete_Internal[LcESTD_EST_Count] = CbFALSE;
			//SaESTD_OpenFaultTestFailed[LcESTD_EST_Count] = CbFALSE; 
		}
	}
    //short to battery
	if(SaESTD_ShortFaultTestComplete_Internal[ScESTD_EST_OutputNumber])
	{
		SaESTD_ShortFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbFALSE;
	}

	if (SaESTD_ShortFaultFailureCounter[ScESTD_EST_OutputNumber] >= KcESTD_FailThrsh)
	{
		SaESTD_ShortFaultTestFailed[ScESTD_EST_OutputNumber] = CbTRUE;
		SaESTD_ShortFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
	else if (SaESTD_ShortFaultSampleCounter[ScESTD_EST_OutputNumber] >= 
			KcESTD_SampleThrsh)
	{
		SaESTD_ShortFaultTestFailed[ScESTD_EST_OutputNumber] = CbFALSE;
		SaESTD_ShortFaultTestComplete_Internal[ScESTD_EST_OutputNumber] = CbTRUE;
	}
    //short to ground & Open
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
