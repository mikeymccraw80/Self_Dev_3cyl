/*****************************************************************************
* Filename:             emsdmprd.c
*
* Description:          OBDII program to process Main Power Relay Hardware
*                       Diagnostic
*
* List of functions:    InitEMSD_MainRelayOFVC_Clear ()
*                       InitEMSD_MainRelayRstToKeyOn ()
*                       MngEMSD_MainRelay125msTasks ()
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
 *  Local Include Files
 *****************************************************************************/

/*****************************************************************************
*   Local Function Declarations
******************************************************************************/

/*****************************************************************************
 *  Static Data Define
 *****************************************************************************/

TbBOOLEAN        SbEMSD_MPRDEnblCriteriaMet;
TbBOOLEAN        SbEMSD_MPRDShortHiFailCriteriaMet;
TbBOOLEAN        SbEMSD_MPRDShortLoFailCriteriaMet;
TbBOOLEAN        SbEMSD_MPRDTestComplete ;
T_COUNT_WORD     ScEMSD_MPRDShortHiFailCntr ;
T_COUNT_WORD     ScEMSD_MPRDShortLoFailCntr ;
T_COUNT_WORD     VcEMSD_MPRDSampleCntr ;
TbBOOLEAN        SbEMSD_MPRDTestComplete_Internal ;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEMSD_MPRDShortHiTestFailed ;
TbBOOLEAN        SbEMSD_MPRDShortLoTestFailed ;
#pragma section DATA " " ".bss"

/*****************************************************************************
 *  Function definition
 ******************************************************************************/
#if 0
/*****************************************************************************
 *
 * Function:     InitEMSD_MainRelayRstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void InitEMSD_MainRelayRstToKeyOff(void)
{

  SbEMSD_MPRDEnblCriteriaMet = CbFALSE ;
  SbEMSD_MPRDShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_MPRDShortLoFailCriteriaMet = CbFALSE ;
  //SbEMSD_MPRDTestComplete = CbFALSE ;
  SbEMSD_MPRDTestComplete_Internal = CbFALSE;
  //SbEMSD_MPRDShortHiTestFailed = CbFALSE ;
  //SbEMSD_MPRDShortLoTestFailed = CbFALSE ;
  ScEMSD_MPRDShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_MPRDShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_MPRDSampleCntr = V_COUNT_WORD (0) ;

}
#endif

 /*****************************************************************************
 *
 * Function:     MngEMSD_MainRelay125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_MainRelay200msTasks (void)
{
	/* Evaluate_FrontACEVT_Enable_Criteria */
	EvaluateEMSD_MPRDEnblCriteria ( KfEMSD_t_IgnitionOnDelay, &SbEMSD_MPRDEnblCriteriaMet);

	SbEMSD_MPRDShortHiFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault (SbEMSD_MPRDEnblCriteriaMet, GetVIOS_MPRD_FaultShortHi());

	SbEMSD_MPRDShortLoFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault (SbEMSD_MPRDEnblCriteriaMet, GetVIOS_MPRD_FaultShortLo());


	/*    Update_MPRD_Test_Counters
	*    ========================================
	*    This process updates the MainRelay diagnostic
	*    test counters. */

	UpdateOBDU_DoubleTestCntrs (SbEMSD_MPRDTestComplete_Internal,
							  SbEMSD_MPRDEnblCriteriaMet,
							  SbEMSD_MPRDShortHiFailCriteriaMet,
							  SbEMSD_MPRDShortLoFailCriteriaMet, 
							  &ScEMSD_MPRDShortHiFailCntr,
							  &ScEMSD_MPRDShortLoFailCntr,
							  &VcEMSD_MPRDSampleCntr) ;


	/*    Perform_MainRelay_XofY_Evaluations
	*    ============================================
	*    If the failure count threshold is reached before the
	*    sample count threshold is reached then the test is
	*    complete and a failure is reported. If the sample
	*    count threshold is reached before the failure count
	*    threshold then the test is complete and a pass is
	*    reported. Reset the test complete flag if the test
	*    was complete the last loop. */

	EvalOBDU_DoubleXofY (ScEMSD_MPRDShortHiFailCntr,
					   ScEMSD_MPRDShortLoFailCntr,
					   VcEMSD_MPRDSampleCntr,
					   KcEMSD_MPRDShortHiFailThrsh,
					   KcEMSD_MPRDShortLoFailThrsh,
					   KcEMSD_MPRDShortSmplThrsh,
					   &SbEMSD_MPRDTestComplete_Internal,
					   &SbEMSD_MPRDShortHiTestFailed,
					   &SbEMSD_MPRDShortLoTestFailed) ;

	SbEMSD_MPRDTestComplete |= SbEMSD_MPRDTestComplete_Internal;
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */






