/*****************************************************************************
* Filename:             eosdmhtr.c
*
* Description:          OBDII program to process Exhaust Oxygen Sensor
*           Heater Diagnostic
*
* List of functions:    InitEOSD_O2_11_HtrOFVC_Clear ()
*                       InitEOSD_O2_11_HtrRstToKeyOn ()
*                       MngEOSD_O2_11_Htr1secTasks ()
*
* List of inlines:
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics 1999
*****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "eosdfexi.h" /* For external interfaces              */
#include "eosdpapi.h" /* For forced declaration definition check */
#include "eosdcald.h" /* For local calibrations               */

/*****************************************************************************
 *  Local Include Files
 *****************************************************************************/
#include "eosdcald.h"

/*****************************************************************************
*   Local Function Declarations
******************************************************************************/


/******************************************************************************
*   Data Define
******************************************************************************/
/*  =========================================================================
 *   Data for Oxygen Sensor Heater Diagnostics Bank 1 Sensor 1
 *  =========================================================================*/

/* (O2_11_Heater_Enable_Criteria_Met)
 * Flag that indicates the O2 Heater diagnostic has met all enable
 * criteria and will begin fault processing ; */
  TbBOOLEAN        SbEOSD_O2_11_HtrEnblCriteriaMet ;

/* (O2_11_Heater_Fail_Criteria_Met)
 * Indicates that the O2 Heater current sample is below the range expected
 * for normal operation.; */
 // TbBOOLEAN        SbEOSD_O2_11_HtrFailCriteriaMet ;

//#if XeSYST_EOSD_11_HEATER_MALF==CeSYST_EOSD_HEATER_MALF_SEPERATE
/*
 * O2_11_Heater_ShortLowFail_Criteria_Met
 */
  TbBOOLEAN        SbEOSD_O2_11_HtrShortLowFailCriteriaMet ;

/*
 * O2_11_Heater_ShortHiFail_Criteria_Met
 */
  TbBOOLEAN        SbEOSD_O2_11_HtrShortHiFailCriteriaMet ;

//#endif

/* (O2_11_Heater_Test_Complete)
 * Flag to indicate that the O2 Heater current test has completed a
 * test and reported the results to the Data Manager; */
  TbBOOLEAN        SbEOSD_O2_11_HtrTestComplete ;

  TbBOOLEAN        SbEOSD_O2_11_HtrTestComplete_Internal ;

/* (O2_11_Heater_Test_Failed)
 * Flag to indicate that the O2 Heater current diagnostic test has failed; */
#pragma section [nvram] 
/* (O2_11_HeaterShortLow_Test_Failed)
 *
 */
  TbBOOLEAN        SbEOSD_O2_11_HtrShortLowTestFailed ;

/* (O2_11_HeaterShortHi_Test_Failed)
 *
 */
  TbBOOLEAN        SbEOSD_O2_11_HtrShortHiTestFailed ;
#pragma section [] 
/* (O2_11_Heater_Fail_Counter)
 * Number of O2 Heater current samples that are below the required current
 * level. */

/*
 * O2_11_HeaterShortLow_Fail_Counter
 */
  T_COUNT_WORD     ScEOSD_O2_11_HtrShortLowFailCntr ;

/*
 * O2_11_HeaterShortHi_Fail_Counter
 */
  T_COUNT_WORD     ScEOSD_O2_11_HtrShortHiFailCntr ;


/* (O2_11_Heater_Sample_Counter)
 * Number of O2 Heater current samples used in the pass/fail test
 * determination. */
T_COUNT_WORD                VcEOSD_O2_11_HtrSampleCntr ;



/*  =========================================================================
 *   Data for Oxygen Sensor Heater Diagnostics Bank 1 Sensor 2
 *  =========================================================================*/

/* (O2_12_Heater_Enable_Criteria_Met)
 * Flag that indicates the O2 Heater diagnostic has met all enable
 * criteria and will begin fault processing ; */
 TbBOOLEAN        SbEOSD_O2_12_HtrEnblCriteriaMet ;

/* (O2_12_Heater_Fail_Criteria_Met)
 * Indicates that the O2 Heater current sample is below the range expected
 * for normal operation.; */
 //TbBOOLEAN        SbEOSD_O2_12_HtrFailCriteriaMet ;

//#if XeSYST_EOSD_12_HEATER_MALF==CeSYST_EOSD_HEATER_MALF_SEPERATE
/*
 * O2_12_Heater_ShortLowFail_Criteria_Met
 */
 TbBOOLEAN        SbEOSD_O2_12_HtrShortLowFailCriteriaMet ;

/*
 * O2_12_Heater_ShortHiFail_Criteria_Met
 */
 TbBOOLEAN        SbEOSD_O2_12_HtrShortHiFailCriteriaMet ;

//#endif

/* (O2_12_Heater_Test_Complete)
 * Flag to indicate that the O2 Heater current test has completed a
 * test and reported the results to the Data Manager; */
 TbBOOLEAN        SbEOSD_O2_12_HtrTestComplete ;

 TbBOOLEAN        SbEOSD_O2_12_HtrTestComplete_Internal ;

 #pragma section [nvram] 
/* (O2_12_HeaterShortLow_Test_Failed)
 *
 */
 TbBOOLEAN        SbEOSD_O2_12_HtrShortLowTestFailed ;

/* (O2_12_HeaterShortHi_Test_Failed)
 *
 */
 TbBOOLEAN        SbEOSD_O2_12_HtrShortHiTestFailed ;
#pragma section [] 


/* (O2_12_Heater_Fail_Counter)
 * Number of O2 Heater current samples that are below the required current
 * level. */

/*
 * O2_12_HeaterShortLow_Fail_Counter
 */
 T_COUNT_WORD     ScEOSD_O2_12_HtrShortLowFailCntr ;

/*
 * O2_12_HeaterShortHi_Fail_Counter
 */
 T_COUNT_WORD     ScEOSD_O2_12_HtrShortHiFailCntr ;

/* (O2_12_Heater_Sample_Counter)
 * Number of O2 Heater current samples used in the pass/fail test
 * determination. */
T_COUNT_WORD                VcEOSD_O2_12_HtrSampleCntr ;

/*
 * O2 heater Bank1 rear heater current filter
 */
 T_AMPSa  SfEOSD_O2_12_FltdHtrCurrent;



/******************************************************************************
*  Local Functions definitions
******************************************************************************/
#if 0

/*****************************************************************************
 *
 * Function:     InitEOSD_O2_11_HtrRstToKeyOn
 * Description:  Initialization functions
 *               (pspec: CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void InitEOSD_O2_11_HtrRstToKeyOff (void)
{


  SbEOSD_O2_11_HtrEnblCriteriaMet = CbFALSE ;
  SbEOSD_O2_11_HtrShortLowFailCriteriaMet = CbFALSE;
  SbEOSD_O2_11_HtrShortHiFailCriteriaMet = CbFALSE;

 // SbEOSD_O2_11_HtrTestComplete = CbFALSE ;
  SbEOSD_O2_11_HtrTestComplete_Internal = CbFALSE;

 // SbEOSD_O2_11_HtrShortLowTestFailed = CbFALSE ;
  //SbEOSD_O2_11_HtrShortHiTestFailed = CbFALSE ;

  ScEOSD_O2_11_HtrShortLowFailCntr = V_COUNT_WORD (0) ;
  ScEOSD_O2_11_HtrShortHiFailCntr = V_COUNT_WORD (0) ;


  VcEOSD_O2_11_HtrSampleCntr = V_COUNT_WORD (0) ;

}

/*****************************************************************************
 *
 * Function:     InitEOSD_O2_12_HtrRstToKeyOn
 * Description:  Initialization functions
 *               (pspec: CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void InitEOSD_O2_12_HtrRstToKeyOff(void)
{


  SbEOSD_O2_12_HtrEnblCriteriaMet = CbFALSE ;
  //SbEOSD_O2_12_HtrFailCriteriaMet = CbFALSE ;

  SbEOSD_O2_12_HtrShortLowFailCriteriaMet = CbFALSE ;
  SbEOSD_O2_12_HtrShortHiFailCriteriaMet = CbFALSE ;


  //SbEOSD_O2_12_HtrTestComplete = CbFALSE ;
  SbEOSD_O2_12_HtrTestComplete_Internal = CbFALSE;

//  SbEOSD_O2_12_HtrShortLowTestFailed = CbFALSE ;
 // SbEOSD_O2_12_HtrShortHiTestFailed = CbFALSE ;


  SfEOSD_O2_12_FltdHtrCurrent = V_AMPSa(0);

  ScEOSD_O2_12_HtrShortLowFailCntr = V_COUNT_WORD (0) ;
  ScEOSD_O2_12_HtrShortHiFailCntr = V_COUNT_WORD (0) ;


  VcEOSD_O2_12_HtrSampleCntr = V_COUNT_WORD (0) ;

}

#endif
/*****************************************************************************

 * Function:     MngEOSD_O2_11_Htr7p82msTasks
 * Description:  This procedure will be called by the operating system
 *               every 7p82 ms timer event.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void MngEOSD_O2_11_Htr781msTasks (void)
{

    if ( GetVIOS_O2HEATER_PowerOK() )
    {
    SbEOSD_O2_11_HtrShortLowFailCriteriaMet =
         ChkEOSD_O2_xx_Htr_GetPSVIFault (SbEOSD_O2_11_HtrEnblCriteriaMet,
                    GetVIOS_O2_11_Htr_PSVIFaultShortLow()
                       ) ;
    }
    else
    {
         /* do nothing */
    }

    SbEOSD_O2_11_HtrShortHiFailCriteriaMet =
         ChkEOSD_O2_xx_Htr_GetPSVIFault (SbEOSD_O2_11_HtrEnblCriteriaMet,
                    GetVIOS_O2_11_Htr_PSVIFaultShortHi()
                       ) ;

}
/*****************************************************************************
 *
 * Function:     MngEOSD_O2_12_Htr7p82msTasks
 * Description:  This procedure will be called by the operating system
 *               every 7p82 ms timer event.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void MngEOSD_O2_12_Htr781msTasks (void)
{

    if ( GetVIOS_O2HEATER_PowerOK() )
    {
    SbEOSD_O2_12_HtrShortLowFailCriteriaMet =
         ChkEOSD_O2_xx_Htr_GetPSVIFault (SbEOSD_O2_12_HtrEnblCriteriaMet,
                    GetVIOS_O2_12_Htr_PSVIFaultShortLow()
                       ) ;
    }
    else
    {
         /* do nothing */
    }
    SbEOSD_O2_12_HtrShortHiFailCriteriaMet =
         ChkEOSD_O2_xx_Htr_GetPSVIFault (SbEOSD_O2_12_HtrEnblCriteriaMet,
                    GetVIOS_O2_12_Htr_PSVIFaultShortHi()
                       ) ;


}
/*****************************************************************************
 *
 * Function:     MngEOSD_O2_11_Htr125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void MngEOSD_O2_11_Htr125msTasks (void)
{

  /*    Pspec :Evaluate_O2_11_Heater_Enable_Criteria */
  SbEOSD_O2_11_HtrEnblCriteriaMet =
         EvaluateEOSD_O2_xx_HtrEnblCriteria (KfEOSD_t_11_HtrEngRunThrsh ) ;

  /*    Pspec :Update_O2_11_Heater_Test_Counters
   *    ========================================
   *    This process updates the O2 Heater diagnostic
   *    test counters. */

  UpdateOBDU_DoubleTestCntrs (SbEOSD_O2_11_HtrTestComplete_Internal,
                  SbEOSD_O2_11_HtrEnblCriteriaMet,
                  SbEOSD_O2_11_HtrShortLowFailCriteriaMet,
                  SbEOSD_O2_11_HtrShortHiFailCriteriaMet,
                  &ScEOSD_O2_11_HtrShortLowFailCntr,
                  &ScEOSD_O2_11_HtrShortHiFailCntr,
                  &VcEOSD_O2_11_HtrSampleCntr) ;


  /*    Pspec :Perform_O2_11_Heater_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

  EvalOBDU_DoubleXofY (ScEOSD_O2_11_HtrShortLowFailCntr,
               ScEOSD_O2_11_HtrShortHiFailCntr,
               VcEOSD_O2_11_HtrSampleCntr,
               KcEOSD_11_HtrShortLowFailThrsh,
               KcEOSD_11_HtrShortHiFailThrsh,
               KcEOSD_11_HtrSmplThrsh,
               &SbEOSD_O2_11_HtrTestComplete_Internal,
               &SbEOSD_O2_11_HtrShortLowTestFailed,
               &SbEOSD_O2_11_HtrShortHiTestFailed) ;

SbEOSD_O2_11_HtrTestComplete |=SbEOSD_O2_11_HtrTestComplete_Internal;

}

/*****************************************************************************
 *
 * Function:     MngEOSD_O2_12_Htr125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/

FAR_COS void MngEOSD_O2_12_Htr125msTasks (void)
{

  /*    Pspec :Evaluate_O2_12_Heater_Enable_Criteria */
  SbEOSD_O2_12_HtrEnblCriteriaMet =
         EvaluateEOSD_O2_xx_HtrEnblCriteria (KfEOSD_t_12_HtrEngRunThrsh ) ;

  /*    Pspec :Update_O2_12_Heater_Test_Counters
   *    ========================================
   *    This process updates the O2 Heater diagnostic
   *    test counters. */

  UpdateOBDU_DoubleTestCntrs (SbEOSD_O2_12_HtrTestComplete_Internal,
                  SbEOSD_O2_12_HtrEnblCriteriaMet,
                  SbEOSD_O2_12_HtrShortLowFailCriteriaMet,
                  SbEOSD_O2_12_HtrShortHiFailCriteriaMet,
                  &ScEOSD_O2_12_HtrShortLowFailCntr,
                  &ScEOSD_O2_12_HtrShortHiFailCntr,
                  &VcEOSD_O2_12_HtrSampleCntr) ;


  /*    Pspec :Perform_O2_12_Heater_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

  EvalOBDU_DoubleXofY (ScEOSD_O2_12_HtrShortLowFailCntr,
               ScEOSD_O2_12_HtrShortHiFailCntr,
               VcEOSD_O2_12_HtrSampleCntr,
               KcEOSD_12_HtrShortLowFailThrsh,
               KcEOSD_12_HtrShortHiFailThrsh,
               KcEOSD_11_HtrSmplThrsh,
               &SbEOSD_O2_12_HtrTestComplete_Internal,
               &SbEOSD_O2_12_HtrShortLowTestFailed,
               &SbEOSD_O2_12_HtrShortHiTestFailed) ;

SbEOSD_O2_12_HtrTestComplete |=SbEOSD_O2_12_HtrTestComplete_Internal;
}





/*****************************************************************************
*
*
*  REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
*
******************************************************************************/
