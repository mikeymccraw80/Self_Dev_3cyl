/*****************************************************************************
* Filename:             emsdfprd.c
*
* Description:          OBDII program to process fuel pump relay Hardware
*                       Diagnostic
*
* List of functions:    InitEMSD_FuelPumpOFVC_Clear ()
*                       InitEMSD_FuelPumpRstToKeyOn ()
*                       MngEMSD_FuelPump125msTasks ()
*
* List of inlines:
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics 2005
*****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "emsdfexi.h" /* For external interfaces                 */
#include "emsdpapi.h" /* For forced declaration definition check */
#include "emsdcald.h" /* For local calibrations                  */

/*****************************************************************************
 *  Local Include Files
 *****************************************************************************/



/*****************************************************************************
*   Local Function Declarations
******************************************************************************/

/*****************************************************************************
 *  Static Data Define
 *****************************************************************************/

  TbBOOLEAN        SbEMSD_FPRDEnblCriteriaMet ;


  TbBOOLEAN        SbEMSD_FPRDShortHiFailCriteriaMet ;
  TbBOOLEAN        SbEMSD_FPRDShortLoFailCriteriaMet ;

  TbBOOLEAN        SbEMSD_FPRDTestComplete ;
#pragma section [nvram] 
  TbBOOLEAN        SbEMSD_FPRDShortHiTestFailed ;

  TbBOOLEAN        SbEMSD_FPRDShortLoTestFailed ;
#pragma section [] 
  T_COUNT_WORD     ScEMSD_FPRDShortHiFailCntr ;
  T_COUNT_WORD     ScEMSD_FPRDShortLoFailCntr ;


T_COUNT_WORD             VcEMSD_FPRDSampleCntr ;

  TbBOOLEAN        SbEMSD_FPRDTestComplete_Internal ;
#if 0
/*****************************************************************************
 *
 * Function:     InitEMSD_FuelPumpRstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void InitEMSD_FuelPumpRstToKeyOff(void)
{

  SbEMSD_FPRDEnblCriteriaMet = CbFALSE ;
  SbEMSD_FPRDShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_FPRDShortLoFailCriteriaMet = CbFALSE ;
 // SbEMSD_FPRDTestComplete = CbFALSE ;
  SbEMSD_FPRDTestComplete_Internal = CbFALSE;
 // SbEMSD_FPRDShortHiTestFailed = CbFALSE ;
 // SbEMSD_FPRDShortLoTestFailed = CbFALSE ;
  ScEMSD_FPRDShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_FPRDShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_FPRDSampleCntr = V_COUNT_WORD (0) ;

}

#endif
 /*****************************************************************************
 *
 * Function:     MngEMSD_FuelPump125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void MngEMSD_FuelPump125msTasks (void)
{

 /* Evaluate_FrontACEVT_Enable_Criteria */
  EvaluateEMSD_FPRDEnblCriteria ( KfEMSD_t_IgnitionOnDelay, 
                                  &SbEMSD_FPRDEnblCriteriaMet) ;

  

  SbEMSD_FPRDShortHiFailCriteriaMet =
         ChkEMSD_GetPSVIorTPICFault (SbEMSD_FPRDEnblCriteriaMet,
                                     GetVIOS_FPRD_FaultShortHi()
                                        ) ;
  if ( GetVIOS_FPR_PowerOK() )
  {
  SbEMSD_FPRDShortLoFailCriteriaMet =
         ChkEMSD_GetPSVIorTPICFault (SbEMSD_FPRDEnblCriteriaMet,
                                     GetVIOS_FPRD_FaultShortLo()
                                        ) ;
  }
  else
  {
  /*  do nothing  */
  }

  /*    Update_FPRD_Test_Counters
   *    ========================================
   *    This process updates the FuelPumpRelay diagnostic
   *    test counters. */

  UpdateOBDU_DoubleTestCntrs (SbEMSD_FPRDTestComplete_Internal,
                              SbEMSD_FPRDEnblCriteriaMet,
                              SbEMSD_FPRDShortHiFailCriteriaMet,
                              SbEMSD_FPRDShortLoFailCriteriaMet, 
                              &ScEMSD_FPRDShortHiFailCntr,
                              &ScEMSD_FPRDShortLoFailCntr,
                              &VcEMSD_FPRDSampleCntr) ;


  /*    Perform_FuelPumpRelay_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

  EvalOBDU_DoubleXofY (ScEMSD_FPRDShortHiFailCntr,
                       ScEMSD_FPRDShortLoFailCntr,
                       VcEMSD_FPRDSampleCntr,
                       KcEMSD_FPRDShortHiFailThrsh,
                       KcEMSD_FPRDShortLoFailThrsh,
                       KcEMSD_FPRDShortSmplThrsh,
                       &SbEMSD_FPRDTestComplete_Internal,
                       &SbEMSD_FPRDShortHiTestFailed,
                       &SbEMSD_FPRDShortLoTestFailed) ;

SbEMSD_FPRDTestComplete |=SbEMSD_FPRDTestComplete_Internal;
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */