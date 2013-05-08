/*****************************************************************************
* Filename:             injdmall.c
*                                                                           
* Description:          Injector Circuits Fault Diagnostic
*
* List of functions:    InitINJD_RstToKeyOn()
*                       InitINJD_OFVC_Clear()
*                       MngINJD_125msTasks()
*                       EvalINJD_EnblCriteria()
*                       CheckINJD_CircuitStatus()
*                       UpdateINJD_CircuitsTimer()
*                       PerfmINJD_CircuitsTimerEval()
*                       DtrmnINJD_IfAllCircuitsAreFltd()
*                       ReportINJD_CircuitsTestResults()
*
* List of inlines:    
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics 1997
*****************************************************************************/

/******************************************************************************
*  Include Files 
*****************************************************************************/ 
#include "injdfexi.h"   /* For global resources definitions   */
#include "injdcald.h"   /* For Definition-Declaration check   */
#include "injdpapi.h"   /* For Definition-Declaration check   */


/***************************************************************************** 
*  Type declaration
******************************************************************************/
typedef enum
{
  CeINJD_InjCircuit1_FaultTimer,
  CeINJD_InjCircuit2_FaultTimer,
  CeINJD_InjCircuit3_FaultTimer,
  CeINJD_InjCircuit4_FaultTimer,
  CeINJD_125msNmbrOfTimers
};


/*****************************************************************************
 *  Global Data Define
 *****************************************************************************/
/* The 125 ms timer calls would be made from the operating system */
DefTIMC_StopWatches8(VaINJD_t_125TimerArray, 
                     VaINJD_125TimerEnbl,
                     R125ms, 
                     CeINJD_125msNmbrOfTimers);

TbBOOLEAN  VaINJD_FailCriteriaMet[CcSYST_NUM_OF_INJECTORS];
TbBOOLEAN  VbINJD_CircuitsHW_ResetReq;
TbBOOLEAN  VbINJD_InjectorsAllFaulted;


/*****************************************************************************/

/******************************************************************************
*  Static Data Define
******************************************************************************/
 TbBOOLEAN     SbINJD_InjCktEnblCriteriaMet;
 TbBOOLEAN     SaINJD_CktTestComplete[CcSYST_NUM_OF_INJECTORS];
 TbBOOLEAN     SaINJD_CktTestComplete_Internal[CcSYST_NUM_OF_INJECTORS];
 #pragma section [nvram] 
 TbBOOLEAN     SaINJD_CktTestFailed[CcSYST_NUM_OF_INJECTORS];
 #pragma section [] 
/*****************************************************************************/

/******************************************************************************
*  Local Function declarations
******************************************************************************/
static void EvalINJD_EnblCriteria(void);
static void CheckINJD_CircuitStatus (void);
static void UpdateINJD_CircuitsTimer (void);
static void PerfmINJD_CircuitsTimerEval (void);
static void DtrmnINJD_IfAllCircuitsAreFltd (void);
static void ReportINJD_CircuitsTestResults (void);
/*****************************************************************************/
#if 0
/*****************************************************************************
 *
 * Function:            InitINJD_RstToKeyOn
 *
 * Description:         This process initializes injector diagnostic variables
 *                      during controller reset to key on state.
 *
 * Parameters:          None
 * Return:              None
 *****************************************************************************/
FAR_COS void InitINJD_RstToKeyOff(void)
{
  BYTE LcINJD_InjectorCount;


  SbINJD_InjCktEnblCriteriaMet = CbFALSE;
  VbINJD_CircuitsHW_ResetReq = CbFALSE;

  for (LcINJD_InjectorCount = 0;
       LcINJD_InjectorCount < CcSYST_NUM_OF_INJECTORS;
       LcINJD_InjectorCount++)
  {
    HaltTIMC_StopWatch(VaINJD_125TimerEnbl, LcINJD_InjectorCount);
    SetTIMC_StopWatch8(VaINJD_t_125TimerArray, LcINJD_InjectorCount, 0);
    VaINJD_FailCriteriaMet[LcINJD_InjectorCount] = CbFALSE;
    SaINJD_CktTestFailed[LcINJD_InjectorCount] = CbFALSE;
    SaINJD_CktTestComplete_Internal[LcINJD_InjectorCount] = CbFALSE;
  }
  VbINJD_InjectorsAllFaulted = CbFALSE;

}

#endif
/*****************************************************************************
 *
 * Function:        MngINJD_125msTasks
 *
 * Description:     This procedure will be called by the operating system
 *                  during every 125 ms timer event. The procedure
 *                  includes calls to all timer triggered functions.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
void MngINJD_125msTasks(void)
{
  BYTE LcINJD_InjectorCount;
  UpdateTIMC_StopWatchesUp8(VaINJD_t_125TimerArray,
                            VaINJD_125TimerEnbl,
                            CeINJD_125msNmbrOfTimers);

  EvalINJD_EnblCriteria ();
  /* Execute Injector Circuits Fail Pass Evaluation */
  CheckINJD_CircuitStatus ();
  UpdateINJD_CircuitsTimer ();
  PerfmINJD_CircuitsTimerEval ();
  DtrmnINJD_IfAllCircuitsAreFltd ();
  
  for (LcINJD_InjectorCount = 0;
       LcINJD_InjectorCount < CcSYST_NUM_OF_CYLINDERS;
       LcINJD_InjectorCount++)
  {
      SaINJD_CktTestComplete[LcINJD_InjectorCount] |=
	  	SaINJD_CktTestComplete_Internal[LcINJD_InjectorCount] ;
  }
}

/*****************************************************************************
 *
 * Function:	    EvalINJD_EnblCriteria
 *
 * Description:	    This process examines all the enable criteria for the 
 *                  injector diagnostics.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
static void EvalINJD_EnblCriteria(void)
{
  if ( (GetAPI_InjHW_EnblCondMet() != CbFALSE)
       && (GetVIOS_IgnSt() == CeIGN_ON )
       && (GetVIOS_n_EngSpd() >= KfINJD_n_EngSpdThrshLo) )
  {
    SbINJD_InjCktEnblCriteriaMet = CbTRUE;
  }
  else
  {
    SbINJD_InjCktEnblCriteriaMet = CbFALSE;
  }
}

/*****************************************************************************
 *
 * Function:	    CheckINJD_CircuitStatus
 *
 * Description:	    This process will use the input from the self-diagnosing
 *                  hardware to set flags indicating the current fail or pass
 *                  status of each injector.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
static void CheckINJD_CircuitStatus (void)
{
  BYTE LcINJD_InjectorCount;
  TbBOOLEAN LbINJD_HW_ResetRequest = CbFALSE;
  
  for (LcINJD_InjectorCount = 0;
       LcINJD_InjectorCount < CcSYST_NUM_OF_CYLINDERS;
       LcINJD_InjectorCount++)
  {
    if (GetAPI_InjCktState(LcINJD_InjectorCount) == CeINJ_FAILED)
    {
      VaINJD_FailCriteriaMet[LcINJD_InjectorCount] = CbTRUE;
      LbINJD_HW_ResetRequest = CbTRUE;
    }
    else
    {
      VaINJD_FailCriteriaMet[LcINJD_InjectorCount] = CbFALSE;
    }
  }  /* END FOR LOOP */
  VbINJD_CircuitsHW_ResetReq = LbINJD_HW_ResetRequest;
}

/*****************************************************************************
 *
 * Function:	    UpdateINJD_CircuitsTimer
 *
 * Description:	    This process will determine if any injector is currently 
 *                  failing and if so it will enable a timer for that specific
 *                  injector to monitor the length of time the failure is
 *                  observed. If an injector is not failing, then the timer is 
 *                  reset to zero. If the injector completed a test in the 
 *                  previous execution loop, then the timer is reset before
 *                  checking the current state.
 *
 * Parameters:	    None
 * Return:          None
 *****************************************************************************/
static void UpdateINJD_CircuitsTimer (void)
{
  BYTE LcINJD_InjectorCount;

  if (SbINJD_InjCktEnblCriteriaMet != CbFALSE)
  {
    for (LcINJD_InjectorCount = 0;
         LcINJD_InjectorCount < CcSYST_NUM_OF_CYLINDERS;
         LcINJD_InjectorCount++)
    {
      if (VaINJD_FailCriteriaMet[LcINJD_InjectorCount] == CbFALSE)
      {
        HaltTIMC_StopWatch(VaINJD_125TimerEnbl, LcINJD_InjectorCount);
        SetTIMC_StopWatch8(VaINJD_t_125TimerArray, LcINJD_InjectorCount, 0);
      }  /* END Fail Criteria Met = False LOOP */
      else  /* if Fail Criteria Met = TRUE */
      {
        if (SaINJD_CktTestComplete_Internal[LcINJD_InjectorCount] != CbFALSE)
        {
          HaltTIMC_StopWatch(VaINJD_125TimerEnbl, LcINJD_InjectorCount);
          SetTIMC_StopWatch8(VaINJD_t_125TimerArray, LcINJD_InjectorCount, 0);
        }
        ResumeTIMC_StopWatch(VaINJD_125TimerEnbl, LcINJD_InjectorCount);
      }  /* END Fail Criteria Met = True LOOP */
    }    /* END FOR LOOP */
  }      /* END Enable Criteria Met = True LOOP */
  else
  {
    for (LcINJD_InjectorCount = 0;
         LcINJD_InjectorCount < CcSYST_NUM_OF_CYLINDERS;
         LcINJD_InjectorCount++)
    {
      HaltTIMC_StopWatch(VaINJD_125TimerEnbl, LcINJD_InjectorCount);
      SetTIMC_StopWatch8(VaINJD_t_125TimerArray, LcINJD_InjectorCount, 0);
    }
  }    /* END Enable Criteria Met = False LOOP */
}

/*****************************************************************************
 *
 * Function:	   PerfmINJD_CircuitsTimerEval
 *
 * Description:	   This process will determine if the timer for any particular
 *                 injector has reached a sufficient value to report a fault.
 *                 An injector that has not set the Fail Criteria Met flag to
 *                 TRUE when the diagnostic is enabled is considered passing.  
 *                 If the timer is running but not greater than the calibration
 *                 then the test is not complete.
 *
 * Parameters:	   None
 * Return:         None
 *****************************************************************************/
static void PerfmINJD_CircuitsTimerEval (void)
{
  BYTE LcINJD_InjectorCount;

  if (SbINJD_InjCktEnblCriteriaMet != CbFALSE)
  {
    for (LcINJD_InjectorCount = 0;
         LcINJD_InjectorCount < CcSYST_NUM_OF_CYLINDERS;
         LcINJD_InjectorCount++)
    {
      SaINJD_CktTestComplete_Internal[LcINJD_InjectorCount] = CbFALSE;

      if (GetTIMC_t_StopWatch8(VaINJD_t_125TimerArray, LcINJD_InjectorCount)
                                     > KfINJD_t_InjCircuitFailThrsh)
      {
        SaINJD_CktTestFailed[LcINJD_InjectorCount] = CbTRUE;
        SaINJD_CktTestComplete_Internal[LcINJD_InjectorCount] = CbTRUE;
      }
      else if (VaINJD_FailCriteriaMet[LcINJD_InjectorCount] == CbFALSE)
      {
        SaINJD_CktTestFailed[LcINJD_InjectorCount] = CbFALSE;
        SaINJD_CktTestComplete_Internal[LcINJD_InjectorCount] = CbTRUE;
      }
    }  /* END FOR LOOP */
  }    /* END IF Enable Criteria Met = True LOOP */
}

/*****************************************************************************
 *
 * Function:	   DtrmnINJD_IfAllCircuitsAreFaulted
 *
 * Description:	   This process will determine whether all of the injectors 
 *                 are failing at the same time. If the overall system
 *                 mechanization allows, then this information may lead to a
 *                 single code for the fuel pump power system being set,rather
 *                 than setting all of the injector codes individually. If the
 *                 system has failed to this degree, the engine will not start.
 *
 * Parameters:	   None
 * Return:         None
 *****************************************************************************/
static void DtrmnINJD_IfAllCircuitsAreFltd (void)
{
  BYTE LcINJD_InjectorCount;
  TbBOOLEAN LbINJD_InjectorsAllFaulted = CbTRUE;

  for (LcINJD_InjectorCount = 0;
       LcINJD_InjectorCount < CcSYST_NUM_OF_CYLINDERS;
       LcINJD_InjectorCount++)
  {
    if (VaINJD_FailCriteriaMet[LcINJD_InjectorCount] == CbFALSE)
    {
      LbINJD_InjectorsAllFaulted = CbFALSE;
      break;
    }
  }
  VbINJD_InjectorsAllFaulted = LbINJD_InjectorsAllFaulted;
}


/*****************************************************************************
*
*****************************************************************************/
