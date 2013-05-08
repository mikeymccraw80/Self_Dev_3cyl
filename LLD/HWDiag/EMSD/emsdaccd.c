/*****************************************************************************
* Filename:             emsdaccd.c
*
* Description:          OBDII program to process AC Clutch Hardware
*                       Diagnostic
*
* List of functions:    
*
* List of inlines:
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics 2005
*****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "emsdpapi.h" /* For forced declaration definition check */
#include "emsdcald.h" /* For local calibrations                  */
#include "mall_lib.h"
#include "intr_ems.h"
#include "v_power.h"


/*****************************************************************************
*   Local Function Declarations
******************************************************************************/

/*****************************************************************************
 *  Static Data Define
 *****************************************************************************/
TbBOOLEAN        SbEMSD_ACCDEnblCriteriaMet ;
TbBOOLEAN        SbEMSD_ACCDShortHiFailCriteriaMet ;
TbBOOLEAN        SbEMSD_ACCDShortLoFailCriteriaMet ;
TbBOOLEAN        SbEMSD_ACCDTestComplete ;
T_COUNT_WORD     ScEMSD_ACCDShortHiFailCntr ;
T_COUNT_WORD     ScEMSD_ACCDShortLoFailCntr ;
T_COUNT_WORD     VcEMSD_ACCDSampleCntr ;

// #pragma section [nvram] 
TbBOOLEAN        SbEMSD_ACCDShortHiTestFailed ;
TbBOOLEAN        SbEMSD_ACCDShortLoTestFailed ;
// #pragma section [] 

TbBOOLEAN        SbEMSD_ACCDTestComplete_Internal ;
/*****************************************************************************
 *  Function definition
 ******************************************************************************/

/*****************************************************************************
 *
 * Function:     InitEMSD_AcClutchRstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/

#if 0
void InitEMSD_AcClutchRstToKeyOff(void)
{

  SbEMSD_ACCDEnblCriteriaMet = CbFALSE ;
  SbEMSD_ACCDShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_ACCDShortLoFailCriteriaMet = CbFALSE ;
  SbEMSD_ACCDTestComplete_Internal = CbFALSE ;
  //SbEMSD_ACCDTestComplete = CbFALSE;
 // SbEMSD_ACCDShortHiTestFailed = CbFALSE ;
 // SbEMSD_ACCDShortLoTestFailed = CbFALSE ;
  ScEMSD_ACCDShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_ACCDShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_ACCDSampleCntr = V_COUNT_WORD (0) ;

}
#endif

 /*****************************************************************************
 *
 * Function:     MngEMSD_AcClutch1secTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_AcClutch125msTasks (void)
{

 /* Evaluate_FrontACEVT_Enable_Criteria */
  EvaluateEMSD_ACCDEnblCriteria ( KfEMSD_t_IgnitionOnDelay, 
                                  &SbEMSD_ACCDEnblCriteriaMet) ;

  

  SbEMSD_ACCDShortHiFailCriteriaMet =
         ChkEMSD_GetPSVIorTPICFault (SbEMSD_ACCDEnblCriteriaMet,
                                     GetVIOS_ACCD_FaultShortHi()
                                        ) ;
  if ( GetVIOS_ACCLUTCH_PowerOK() )
  {
  SbEMSD_ACCDShortLoFailCriteriaMet =
         ChkEMSD_GetPSVIorTPICFault (SbEMSD_ACCDEnblCriteriaMet,
                                     GetVIOS_ACCD_FaultShortLo()
                                        ) ;
  }
  else
  {
  /*  do nothing  */
  }


  /*    Update_ACCD_Test_Counters
   *    ========================================
   *    This process updates the AcClutch diagnostic
   *    test counters. */

  UpdateOBDU_DoubleTestCntrs (SbEMSD_ACCDTestComplete_Internal,
                              SbEMSD_ACCDEnblCriteriaMet,
                              SbEMSD_ACCDShortHiFailCriteriaMet,
                              SbEMSD_ACCDShortLoFailCriteriaMet, 
                              &ScEMSD_ACCDShortHiFailCntr,
                              &ScEMSD_ACCDShortLoFailCntr,
                              &VcEMSD_ACCDSampleCntr) ;


  /*    Perform_AcClutch_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

  EvalOBDU_DoubleXofY (ScEMSD_ACCDShortHiFailCntr,
                       ScEMSD_ACCDShortLoFailCntr,
                       VcEMSD_ACCDSampleCntr,
                       KcEMSD_ACCDShortHiFailThrsh,
                       KcEMSD_ACCDShortLoFailThrsh,
                       KcEMSD_ACCDShortSmplThrsh,
                       &SbEMSD_ACCDTestComplete_Internal,
                       &SbEMSD_ACCDShortHiTestFailed,
                       &SbEMSD_ACCDShortLoTestFailed) ;

  SbEMSD_ACCDTestComplete |= SbEMSD_ACCDTestComplete_Internal;
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
 *
\* ============================================================================ */
