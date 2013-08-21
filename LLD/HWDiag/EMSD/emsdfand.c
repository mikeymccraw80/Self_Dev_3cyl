/*****************************************************************************
* Filename:             emsdfand.c
*
* Description:          OBDII program to process Fanx Hardware
*                       Diagnostic
*
* List of functions:    InitEMSD_FanAOFVC_Clear ()
*                       InitEMSD_FanBOFVC_Clear ()
*                       InitEMSD_FanCOFVC_Clear ()
*                       InitEMSD_FanPWMOFVC_Clear ()
*                       InitEMSD_FanxRstToKeyOn ()
*                       MngEMSD_FanA125msTasks ()
*                       MngEMSD_FanB125msTasks ()
*                       MngEMSD_FanC125msTasks ()
*                       MngEMSD_FanPWM125msTasks ()
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

/*
 *
 * FAN1
 */
TbBOOLEAN        SbEMSD_FANAEnblCriteriaMet ;
TbBOOLEAN        SbEMSD_FANAShortHiFailCriteriaMet ;
TbBOOLEAN        SbEMSD_FANAShortLoFailCriteriaMet ;
TbBOOLEAN        SbEMSD_FANATestComplete ;
T_COUNT_WORD     ScEMSD_FANAShortHiFailCntr ;
T_COUNT_WORD     ScEMSD_FANAShortLoFailCntr ;
T_COUNT_WORD             VcEMSD_FANASampleCntr ;
TbBOOLEAN        SbEMSD_FANATestComplete_Internal;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEMSD_FANAShortHiTestFailed ;
TbBOOLEAN        SbEMSD_FANAShortLoTestFailed ;
#pragma section DATA " " ".bss"

/*
 *
 * FAN2
 */
TbBOOLEAN        SbEMSD_FANBEnblCriteriaMet ;
TbBOOLEAN        SbEMSD_FANBShortHiFailCriteriaMet ;
TbBOOLEAN        SbEMSD_FANBShortLoFailCriteriaMet ;
TbBOOLEAN        SbEMSD_FANBTestComplete ;
T_COUNT_WORD     ScEMSD_FANBShortHiFailCntr ;
T_COUNT_WORD     ScEMSD_FANBShortLoFailCntr ;
T_COUNT_WORD     VcEMSD_FANBSampleCntr ;
TbBOOLEAN        SbEMSD_FANBTestComplete_Internal;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEMSD_FANBShortHiTestFailed ;
TbBOOLEAN        SbEMSD_FANBShortLoTestFailed ;
#pragma section DATA " " ".bss"
/*****************************************************************************
 *  Function definition
 ******************************************************************************/
#if 0
/*****************************************************************************
 *
 * Function:     InitEMSD_FanxRstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void InitEMSD_FanxRstToKeyOff(void)
{  
  
  SbEMSD_FANAEnblCriteriaMet = CbFALSE ;
  SbEMSD_FANAShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_FANAShortLoFailCriteriaMet = CbFALSE ;
  //SbEMSD_FANATestComplete = CbFALSE ;
  SbEMSD_FANATestComplete_Internal = CbFALSE;
 // SbEMSD_FANAShortHiTestFailed = CbFALSE ;
 // SbEMSD_FANAShortLoTestFailed = CbFALSE ;
  ScEMSD_FANAShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_FANAShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_FANASampleCntr = V_COUNT_WORD (0) ;
  SbEMSD_FANBEnblCriteriaMet = CbFALSE ;
  SbEMSD_FANBShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_FANBShortLoFailCriteriaMet = CbFALSE ;
  //SbEMSD_FANBTestComplete = CbFALSE ;
  SbEMSD_FANBTestComplete_Internal = CbFALSE;
 // SbEMSD_FANBShortHiTestFailed = CbFALSE ;
  //SbEMSD_FANBShortLoTestFailed = CbFALSE ;
  ScEMSD_FANBShortHiFailCntr = V_COUNT_WORD (0) ;
  ScEMSD_FANBShortLoFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_FANBSampleCntr = V_COUNT_WORD (0) ;

}
#endif
 /*****************************************************************************
 *
 * Function:     MngEMSD_FanA125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 125ms timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_FanA200msTasks (void)
{
	/* Evaluate_Fan1_Enable_Criteria */
	EvaluateEMSD_FANAEnblCriteria ( KfEMSD_t_IgnitionOnDelay, &SbEMSD_FANAEnblCriteriaMet);

	SbEMSD_FANAShortHiFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault (SbEMSD_FANAEnblCriteriaMet, GetVIOS_FANA_FaultShortHi());

	if ( GetVIOS_FANA_PowerOK() ) {
		SbEMSD_FANAShortLoFailCriteriaMet = \
			ChkEMSD_GetPSVIorTPICFault (SbEMSD_FANAEnblCriteriaMet, GetVIOS_FANA_FaultShortLo());
	} else {
		/*  do nothing  */
	}

  /*    Update_FANA_Test_Counters
   *    ========================================
   *    This process updates the fan1 diagnostic
   *    test counters. */

	UpdateOBDU_DoubleTestCntrs (SbEMSD_FANATestComplete_Internal,
							  SbEMSD_FANAEnblCriteriaMet,
							  SbEMSD_FANAShortHiFailCriteriaMet,
							  SbEMSD_FANAShortLoFailCriteriaMet, 
							  &ScEMSD_FANAShortHiFailCntr,
							  &ScEMSD_FANAShortLoFailCntr,
							  &VcEMSD_FANASampleCntr) ;


  /*    Perform_fan1_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

	EvalOBDU_DoubleXofY (ScEMSD_FANAShortHiFailCntr,
					   ScEMSD_FANAShortLoFailCntr,
					   VcEMSD_FANASampleCntr,
					   KcEMSD_FANAShortHiFailThrsh,
					   KcEMSD_FANAShortLoFailThrsh,
					   KcEMSD_FANAShortSmplThrsh,
					   &SbEMSD_FANATestComplete_Internal,
					   &SbEMSD_FANAShortHiTestFailed,
					   &SbEMSD_FANAShortLoTestFailed) ;

	SbEMSD_FANATestComplete |=SbEMSD_FANATestComplete_Internal;
}

 /*****************************************************************************
 *
 * Function:     MngEMSD_FanB125msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 125ms timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_FanB200msTasks (void)
{

	/* Evaluate_Fan2_Enable_Criteria */
	EvaluateEMSD_FANBEnblCriteria ( KfEMSD_t_IgnitionOnDelay, &SbEMSD_FANBEnblCriteriaMet);

	SbEMSD_FANBShortHiFailCriteriaMet = \
		 ChkEMSD_GetPSVIorTPICFault (SbEMSD_FANBEnblCriteriaMet, GetVIOS_FANB_FaultShortHi());

	if ( GetVIOS_FANB_PowerOK()) {
		SbEMSD_FANBShortLoFailCriteriaMet =\
			ChkEMSD_GetPSVIorTPICFault (SbEMSD_FANBEnblCriteriaMet, GetVIOS_FANB_FaultShortLo());
	} else {
	/*  do nothing  */
	}

  /*    Update_FANB_Test_Counters
   *    ========================================
   *    This process updates the fan2 diagnostic
   *    test counters. */

	UpdateOBDU_DoubleTestCntrs (SbEMSD_FANBTestComplete_Internal,
							  SbEMSD_FANBEnblCriteriaMet,
							  SbEMSD_FANBShortHiFailCriteriaMet,
							  SbEMSD_FANBShortLoFailCriteriaMet, 
							  &ScEMSD_FANBShortHiFailCntr,
							  &ScEMSD_FANBShortLoFailCntr,
							  &VcEMSD_FANBSampleCntr) ;

  /*    Perform_fan2_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

	EvalOBDU_DoubleXofY (ScEMSD_FANBShortHiFailCntr,
					   ScEMSD_FANBShortLoFailCntr,
					   VcEMSD_FANBSampleCntr,
					   KcEMSD_FANBShortHiFailThrsh,
					   KcEMSD_FANBShortLoFailThrsh,
					   KcEMSD_FANBShortSmplThrsh,
					   &SbEMSD_FANBTestComplete_Internal,
					   &SbEMSD_FANBShortHiTestFailed,
					   &SbEMSD_FANBShortLoTestFailed) ;

	SbEMSD_FANBTestComplete |=SbEMSD_FANBTestComplete_Internal;
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
