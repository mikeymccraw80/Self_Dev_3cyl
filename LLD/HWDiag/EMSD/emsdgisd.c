/*****************************************************************************
* Filename:             emsdvgid.c
*
* Description:          OBDII program to process VGIS(DO) Hardware
*                       Diagnostic
*
* List of functions:    InitEMSD_GISOFVC_Clear ()
*                       InitEMSD_GISRstToKeyOn ()
*                       MngEMSD_GIS125msTasks ()
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

TbBOOLEAN        SbEMSD_GISDEnblCriteriaMet ;
TbBOOLEAN        SbEMSD_GISDShortHiFailCriteriaMet ;
TbBOOLEAN        SbEMSD_GISDShortLoFailCriteriaMet ;
TbBOOLEAN        SbEMSD_GISDTestComplete ;

T_COUNT_WORD     ScEMSD_GISDShortHiFailCntr ;
T_COUNT_WORD     ScEMSD_GISDShortLoFailCntr ;
T_COUNT_WORD     VcEMSD_GISDSampleCntr ;
TbBOOLEAN        SbEMSD_GISDTestComplete_Internal ;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEMSD_GISDShortHiTestFailed ;
TbBOOLEAN        SbEMSD_GISDShortLoTestFailed ;
#pragma section DATA " " ".bss"

/*****************************************************************************
 *  Function definition
 ******************************************************************************/
#if 0
/*****************************************************************************
 *
 * Function:     InitEMSD_GISRstToKeyOff
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
FAR_COS void InitEMSD_GISRstToKeyOff(void)
{

  SbEMSD_GISDEnblCriteriaMet = CbFALSE ;
  SbEMSD_GISDShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_GISDShortLoFailCriteriaMet = CbFALSE ;
  //SbEMSD_GISDTestComplete = CbFALSE ;
  SbEMSD_GISDTestComplete_Internal = CbFALSE;
  //SbEMSD_GISDShortHiTestFailed = CbFALSE ;
  //SbEMSD_GISDShortLoTestFailed = CbFALSE ;
  ScEMSD_GISDShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_GISDShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_GISDSampleCntr = V_COUNT_WORD (0) ;

}
#endif
 /*****************************************************************************
 *
 * Function:     MngEMSD_GIS200msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 1 sec timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_GIS200msTasks (void)
{

	/* Evaluate_FrontACEVT_Enable_Criteria */
	EvaluateEMSD_MILDEnblCriteria ( KfEMSD_t_IgnitionOnDelay, &SbEMSD_GISDEnblCriteriaMet);

	SbEMSD_GISDShortHiFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault(SbEMSD_GISDEnblCriteriaMet, GetVIOS_GISD_FaultShortHi());
	SbEMSD_GISDShortLoFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault(SbEMSD_GISDEnblCriteriaMet, GetVIOS_GISD_FaultShortLo());


	/*    Update_MILD_Test_Counters
	*    ========================================
	*    This process updates the MIL diagnostic
	*    test counters. */

	UpdateOBDU_DoubleTestCntrs (SbEMSD_GISDTestComplete_Internal,
							  SbEMSD_GISDEnblCriteriaMet,
							  SbEMSD_GISDShortHiFailCriteriaMet,
							  SbEMSD_GISDShortLoFailCriteriaMet, 
							  &ScEMSD_GISDShortHiFailCntr,
							  &ScEMSD_GISDShortLoFailCntr,
							  &VcEMSD_GISDSampleCntr) ;


	/*    Perform_MIL_XofY_Evaluations
	*    ============================================
	*    If the failure count threshold is reached before the
	*    sample count threshold is reached then the test is
	*    complete and a failure is reported. If the sample
	*    count threshold is reached before the failure count
	*    threshold then the test is complete and a pass is
	*    reported. Reset the test complete flag if the test
	*    was complete the last loop. */

	EvalOBDU_DoubleXofY (ScEMSD_GISDShortHiFailCntr,
					   ScEMSD_GISDShortLoFailCntr,
					   VcEMSD_GISDSampleCntr,
					   KcEMSD_GISDShortHiFailThrsh,
					   KcEMSD_GISDShortLoFailThrsh,
					   KcEMSD_GISDShortSmplThrsh,
					   &SbEMSD_GISDTestComplete_Internal,
					   &SbEMSD_GISDShortHiTestFailed,
					   &SbEMSD_GISDShortLoTestFailed) ;

	SbEMSD_GISDTestComplete |= SbEMSD_GISDTestComplete_Internal;
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */






