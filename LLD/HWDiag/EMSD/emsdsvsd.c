/*****************************************************************************
* Filename:             emsdsvsd.c
*
* Description:          OBDII program to process SVS Hardware
*                       Diagnostic
*
* List of functions:    InitEMSD_SVSOFVC_Clear ()
*                       InitEMSD_SVSRstToKeyOn ()
*                       MngEMSD_SVS125msTasks ()
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

TbBOOLEAN        SbEMSD_SVSDEnblCriteriaMet ;
TbBOOLEAN        SbEMSD_SVSDShortHiFailCriteriaMet ;
TbBOOLEAN        SbEMSD_SVSDShortLoFailCriteriaMet ;
TbBOOLEAN        SbEMSD_SVSDTestComplete ;

T_COUNT_WORD     ScEMSD_SVSDShortHiFailCntr ;
T_COUNT_WORD     ScEMSD_SVSDShortLoFailCntr ;
T_COUNT_WORD             VcEMSD_SVSDSampleCntr ;
TbBOOLEAN        SbEMSD_SVSDTestComplete_Internal ;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEMSD_SVSDShortHiTestFailed ;
TbBOOLEAN        SbEMSD_SVSDShortLoTestFailed ;
#pragma section DATA " " ".bss"

/*****************************************************************************
 *  Function definition
 ******************************************************************************/
#if 1
/*****************************************************************************
 *
 * Function:     InitEMSD_SVSRstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
 void InitEMSD_SVSRstToKeyOn(void)
{

  SbEMSD_SVSDEnblCriteriaMet = CbFALSE ;
  SbEMSD_SVSDShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_SVSDShortLoFailCriteriaMet = CbFALSE ;
  SbEMSD_SVSDTestComplete = CbFALSE ;
  SbEMSD_SVSDTestComplete_Internal = CbFALSE;
  //SbEMSD_SVSDShortHiTestFailed = CbFALSE ;
  //SbEMSD_SVSDShortLoTestFailed = CbFALSE ;
  ScEMSD_SVSDShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_SVSDShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_SVSDSampleCntr = V_COUNT_WORD (0) ;

}
#endif
 /*****************************************************************************
 *
 * Function:     MngEMSD_SVS125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_SVS200msTasks (void)
{

	/* Evaluate_FrontACEVT_Enable_Criteria */
	EvaluateEMSD_MILDEnblCriteria ( KfEMSD_t_IgnitionOnDelay, &SbEMSD_SVSDEnblCriteriaMet);

	SbEMSD_SVSDShortHiFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault(SbEMSD_SVSDEnblCriteriaMet, GetVIOS_SVSD_FaultShortHi());
	SbEMSD_SVSDShortLoFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault(SbEMSD_SVSDEnblCriteriaMet, GetVIOS_SVSD_FaultShortLo());


	/*    Update_SVSD_Test_Counters
	*    ========================================
	*    This process updates the SVS diagnostic
	*    test counters. */

	UpdateOBDU_DoubleTestCntrs (SbEMSD_SVSDTestComplete_Internal,
							  SbEMSD_SVSDEnblCriteriaMet,
							  SbEMSD_SVSDShortHiFailCriteriaMet,
							  SbEMSD_SVSDShortLoFailCriteriaMet, 
							  &ScEMSD_SVSDShortHiFailCntr,
							  &ScEMSD_SVSDShortLoFailCntr,
							  &VcEMSD_SVSDSampleCntr) ;


	/*    Perform_SVS_XofY_Evaluations
	*    ============================================
	*    If the failure count threshold is reached before the
	*    sample count threshold is reached then the test is
	*    complete and a failure is reported. If the sample
	*    count threshold is reached before the failure count
	*    threshold then the test is complete and a pass is
	*    reported. Reset the test complete flag if the test
	*    was complete the last loop. */

	EvalOBDU_DoubleXofY (ScEMSD_SVSDShortHiFailCntr,
					   ScEMSD_SVSDShortLoFailCntr,
					   VcEMSD_SVSDSampleCntr,
					   KcEMSD_SVSDShortHiFailThrsh,
					   KcEMSD_SVSDShortLoFailThrsh,
					   KcEMSD_SVSDShortSmplThrsh,
					   &SbEMSD_SVSDTestComplete_Internal,
					   &SbEMSD_SVSDShortHiTestFailed,
					   &SbEMSD_SVSDShortLoTestFailed) ;

	SbEMSD_SVSDTestComplete |= SbEMSD_SVSDTestComplete_Internal;
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */






