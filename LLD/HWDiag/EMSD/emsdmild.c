/*****************************************************************************
* Filename:             emsdmild.c
*
* Description:          OBDII program to process MIL Hardware
*                       Diagnostic
*
* List of functions:    InitEMSD_MILOFVC_Clear ()
*                       InitEMSD_MILRstToKeyOn ()
*                       MngEMSD_MIL125msTasks ()
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

  TbBOOLEAN        SbEMSD_MILDEnblCriteriaMet ;


  TbBOOLEAN        SbEMSD_MILDShortHiFailCriteriaMet ;
  TbBOOLEAN        SbEMSD_MILDShortLoFailCriteriaMet ;

  TbBOOLEAN        SbEMSD_MILDTestComplete ;
#pragma section [nvram] 
  TbBOOLEAN        SbEMSD_MILDShortHiTestFailed ;

  TbBOOLEAN        SbEMSD_MILDShortLoTestFailed ;
#pragma section [] 
  T_COUNT_WORD     ScEMSD_MILDShortHiFailCntr ;
  T_COUNT_WORD     ScEMSD_MILDShortLoFailCntr ;


T_COUNT_WORD             VcEMSD_MILDSampleCntr ;
TbBOOLEAN        SbEMSD_MILDTestComplete_Internal ;


/*****************************************************************************
 *  Function definition
 ******************************************************************************/
#if 0
/*****************************************************************************
 *
 * Function:     InitEMSD_MILRstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void InitEMSD_MILRstToKeyOff(void)
{

  SbEMSD_MILDEnblCriteriaMet = CbFALSE ;
  SbEMSD_MILDShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_MILDShortLoFailCriteriaMet = CbFALSE ;
  //SbEMSD_MILDTestComplete = CbFALSE ;
  SbEMSD_MILDTestComplete_Internal = CbFALSE;
  //SbEMSD_MILDShortHiTestFailed = CbFALSE ;
  //SbEMSD_MILDShortLoTestFailed = CbFALSE ;
  ScEMSD_MILDShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_MILDShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_MILDSampleCntr = V_COUNT_WORD (0) ;

}
#endif
 /*****************************************************************************
 *
 * Function:     MngEMSD_MIL125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void MngEMSD_MIL125msTasks (void)
{

 /* Evaluate_FrontACEVT_Enable_Criteria */
  EvaluateEMSD_MILDEnblCriteria ( KfEMSD_t_IgnitionOnDelay, 
                                  &SbEMSD_MILDEnblCriteriaMet) ;

  

  SbEMSD_MILDShortHiFailCriteriaMet =
         ChkEMSD_GetPSVIorTPICFault (SbEMSD_MILDEnblCriteriaMet,
                                     GetVIOS_MILD_FaultShortHi()
                                        ) ;
  SbEMSD_MILDShortLoFailCriteriaMet =
         ChkEMSD_GetPSVIorTPICFault (SbEMSD_MILDEnblCriteriaMet,
                                     GetVIOS_MILD_FaultShortLo()
                                        ) ;


  /*    Update_MILD_Test_Counters
   *    ========================================
   *    This process updates the MIL diagnostic
   *    test counters. */

  UpdateOBDU_DoubleTestCntrs (SbEMSD_MILDTestComplete_Internal,
                              SbEMSD_MILDEnblCriteriaMet,
                              SbEMSD_MILDShortHiFailCriteriaMet,
                              SbEMSD_MILDShortLoFailCriteriaMet, 
                              &ScEMSD_MILDShortHiFailCntr,
                              &ScEMSD_MILDShortLoFailCntr,
                              &VcEMSD_MILDSampleCntr) ;


  /*    Perform_MIL_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

  EvalOBDU_DoubleXofY (ScEMSD_MILDShortHiFailCntr,
                       ScEMSD_MILDShortLoFailCntr,
                       VcEMSD_MILDSampleCntr,
                       KcEMSD_MILDShortHiFailThrsh,
                       KcEMSD_MILDShortLoFailThrsh,
                       KcEMSD_MILDShortSmplThrsh,
                       &SbEMSD_MILDTestComplete_Internal,
                       &SbEMSD_MILDShortHiTestFailed,
                       &SbEMSD_MILDShortLoTestFailed) ;

  SbEMSD_MILDTestComplete |= SbEMSD_MILDTestComplete_Internal;

}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */






