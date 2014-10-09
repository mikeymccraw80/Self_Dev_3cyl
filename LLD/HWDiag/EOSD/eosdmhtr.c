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
 *  Include Files
 *****************************************************************************/
#include "eosdpapi.h" /* For forced declaration definition check */
#include "eosdcald.h"
#include "mall_lib.h"
#include "timclib.h"
#include "intr_ems.h"
#include "v_power.h"

/******************************************************************************
*   Data Define
******************************************************************************/
/*  =========================================================================
 *   Data for Oxygen Sensor Heater Diagnostics Bank 1 Sensor 1
 *  =========================================================================*/

TbBOOLEAN        SbEOSD_O2_11_HtrEnblCriteriaMet ;
// TbBOOLEAN        SbEOSD_O2_11_HtrFailCriteriaMet ;
TbBOOLEAN        SbEOSD_O2_11_HtrShortLowFailCriteriaMet ;
TbBOOLEAN        SbEOSD_O2_11_HtrShortHiFailCriteriaMet ;
TbBOOLEAN        SbEOSD_O2_11_HtrTestComplete ;
TbBOOLEAN        SbEOSD_O2_11_HtrTestComplete_Internal ;
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEOSD_O2_11_HtrShortLowTestFailed ;
TbBOOLEAN        SbEOSD_O2_11_HtrShortHiTestFailed ;
#pragma section DATA " " ".bss"
T_COUNT_WORD     ScEOSD_O2_11_HtrShortLowFailCntr ;
T_COUNT_WORD     ScEOSD_O2_11_HtrShortHiFailCntr ;
T_COUNT_WORD     VcEOSD_O2_11_HtrSampleCntr ;

TbBOOLEAN        SbEOSD_O2_12_HtrEnblCriteriaMet ;
//TbBOOLEAN        SbEOSD_O2_12_HtrFailCriteriaMet ;
TbBOOLEAN        SbEOSD_O2_12_HtrShortLowFailCriteriaMet ;
TbBOOLEAN        SbEOSD_O2_12_HtrShortHiFailCriteriaMet ;
TbBOOLEAN        SbEOSD_O2_12_HtrTestComplete ;
TbBOOLEAN        SbEOSD_O2_12_HtrTestComplete_Internal ;
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEOSD_O2_12_HtrShortLowTestFailed ;
TbBOOLEAN        SbEOSD_O2_12_HtrShortHiTestFailed ;
#pragma section DATA " " ".bss"
T_COUNT_WORD     ScEOSD_O2_12_HtrShortLowFailCntr ;
T_COUNT_WORD     ScEOSD_O2_12_HtrShortHiFailCntr ;
T_COUNT_WORD     VcEOSD_O2_12_HtrSampleCntr ;
T_AMPSa          SfEOSD_O2_12_FltdHtrCurrent;

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
void MngEOSD_O2_11_Htr10msTasks (void)
{
	if ( GetVIOS_O2HEATER_PowerOK() )
	{
		SbEOSD_O2_11_HtrShortLowFailCriteriaMet = \
			ChkEOSD_O2_xx_Htr_GetPSVIFault (SbEOSD_O2_11_HtrEnblCriteriaMet,GetVIOS_O2_11_Htr_PSVIFaultShortLow());
	}
	else
	{
		/* do nothing */
	}

	SbEOSD_O2_11_HtrShortHiFailCriteriaMet = \
		ChkEOSD_O2_xx_Htr_GetPSVIFault(SbEOSD_O2_11_HtrEnblCriteriaMet, GetVIOS_O2_11_Htr_PSVIFaultShortHi());
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
void MngEOSD_O2_12_Htr10msTasks (void)
{
	if ( GetVIOS_O2HEATER_PowerOK() )
	{
		SbEOSD_O2_12_HtrShortLowFailCriteriaMet = \
			ChkEOSD_O2_xx_Htr_GetPSVIFault(SbEOSD_O2_12_HtrEnblCriteriaMet, GetVIOS_O2_12_Htr_PSVIFaultShortLow());
	}
	else
	{
		 /* do nothing */
	}
	SbEOSD_O2_12_HtrShortHiFailCriteriaMet = \
		 ChkEOSD_O2_xx_Htr_GetPSVIFault(SbEOSD_O2_12_HtrEnblCriteriaMet, GetVIOS_O2_12_Htr_PSVIFaultShortHi());
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
void MngEOSD_O2_11_Htr125msTasks (void)
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

void MngEOSD_O2_12_Htr125msTasks (void)
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
			   KcEOSD_12_HtrSmplThrsh,
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
