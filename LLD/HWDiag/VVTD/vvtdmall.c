/*****************************************************************************
* Filename:                   prgdmall.c
*
* Description:                Purge Output Diagnostics
*
* List of functions:          void InitPRGD_Purge_RstToKeyOn(void)
*                             void InitPRGD_Purge_OFVC_Clear (void)
*                             void MngPRGD_Purge_125msTasks(void)
*
* C Software Project FORWARD EMS
* (c) Copyright Delco Electronics  1999
*****************************************************************************/

/******************************************************************************
*  Include Files
*****************************************************************************/
#include "vvtdcald.h"   /* For Definition-Declaration check   */
#include "vvtdpapi.h"   /* For Definition-Declaration check   */
#include "mall_lib.h"
#include "timclib.h"
#include "intr_ems.h"
#include "hal_diag.h"
#include "v_power.h"

/*****************************************************************************
 *  Constant Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Local Variable Definitions
 *****************************************************************************/
 TbBOOLEAN            SbVVTD_DisableFltPresent;
 TbBOOLEAN            SbVVTD_EnblCritMet;
 
 /* for vvt1 output channel */
 TbBOOLEAN            SbVVTD_VVT1_FailCritMet;
 T_COUNT_WORD         ScVVTD_VVT1_FailCntr;
 T_COUNT_WORD         ScVVTD_VVT1_SampleCntr;
 TbBOOLEAN            SbVVTD_VVT1_TestComplete;
 TbBOOLEAN            SbVVTD_VVT1_TestComplete_Internal;
 TbBOOLEAN            SbVVTD_VVT1_ShortLoCritMet;
 TbBOOLEAN            SbVVTD_VVT1_ShortHiCritMet;

 /* for vvt2 output channel */
 TbBOOLEAN            SbVVTD_VVT2_FailCritMet;
 T_COUNT_WORD         ScVVTD_VVT2_FailCntr;
 T_COUNT_WORD         ScVVTD_VVT2_SampleCntr;
 TbBOOLEAN            SbVVTD_VVT2_TestComplete;
 TbBOOLEAN            SbVVTD_VVT2_TestComplete_Internal;
 TbBOOLEAN            SbVVTD_VVT2_ShortLoCritMet;
 TbBOOLEAN            SbVVTD_VVT2_ShortHiCritMet;
 
 #pragma section DATA " " ".nc_nvram"
 TbBOOLEAN            SbVVTD_VVT1_TestFailed;
 TbBOOLEAN            SbVVTD_VVT1_TestFailedHi;
 TbBOOLEAN            SbVVTD_VVT1_TestFailedLo;

 TbBOOLEAN            SbVVTD_VVT2_TestFailed;
 TbBOOLEAN            SbVVTD_VVT2_TestFailedHi;
 TbBOOLEAN            SbVVTD_VVT2_TestFailedLo;
 #pragma section DATA " " ".bss"

/*****************************************************************************
 *
 * Function:           InitPRGD_Purge_RstToKeyOn
 * Description:        This process will Initialize the Purge Solenoid
 *                     diagnostic variables on
 *                     (pspec: CONTROLLER_RESET_COMPLETE_To_KEY_ON)
 *
 * Parameters:         None
 * Return:             None
 *****************************************************************************/
#if 1
void InitVVTD_RstToKeyOn(void)
{
  SbVVTD_DisableFltPresent = CbFALSE;
  SbVVTD_EnblCritMet = CbFALSE;
  
  SbVVTD_VVT1_FailCritMet = CbFALSE;
  SbVVTD_VVT1_ShortLoCritMet = CbFALSE;
  SbVVTD_VVT1_ShortHiCritMet= CbFALSE;
  ScVVTD_VVT1_FailCntr = V_COUNT_WORD(0);
  ScVVTD_VVT1_SampleCntr = V_COUNT_WORD(0);
 // SbVVTD_VVT1_TestFailed = CbFALSE;
  SbVVTD_VVT1_TestComplete_Internal = CbFALSE;
  SbVVTD_VVT1_TestComplete = CbFALSE;
  
  SbVVTD_VVT2_FailCritMet = CbFALSE;
  SbVVTD_VVT2_ShortLoCritMet = CbFALSE;
  SbVVTD_VVT2_ShortHiCritMet= CbFALSE;
  ScVVTD_VVT2_FailCntr = V_COUNT_WORD(0);
  ScVVTD_VVT2_SampleCntr = V_COUNT_WORD(0);
 // SbVVTD_VVT2_TestFailed = CbFALSE;
  SbVVTD_VVT2_TestComplete_Internal = CbFALSE;
 SbVVTD_VVT2_TestComplete = CbFALSE;
}

#endif

/*****************************************************************************
 *
 * Function:    MngVVTD_125msTasks
 * Description: This process will execute VVT diagnostic at
 *              125 ms loop
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void MngVVTD_125msTasks(void)
{
	/* Determine_VVT_Output_Enable_Criteria_Met */
	if ((GetVIOS_EngSt() == CeENG_RUN) && (GetVIOS_U_IgnVolt() > KfVVTD_U_SystemThrshLo)) {
		SbVVTD_EnblCritMet = CbTRUE;
	} else {
		SbVVTD_EnblCritMet = CbFALSE;
	}

	/* Check_VVT1_Output_Status */
	if ( SbVVTD_EnblCritMet != CbFALSE ) {
		if ( GetHWIO_VVT1OutputFaultShortHi() ) {
			SbVVTD_VVT1_ShortHiCritMet = CbTRUE;
		} else {
			SbVVTD_VVT1_ShortHiCritMet = CbFALSE;
		}

		if ( GetHWIO_VVT1OutputFaultShortLo() && GetVIOS_CCP_PowerOK() ) {
			SbVVTD_VVT1_ShortLoCritMet = CbTRUE;
		} else if ( GetVIOS_CCP_PowerOK() ) {
			SbVVTD_VVT1_ShortLoCritMet = CbFALSE;
		} else {
			/* do nothing */
		}

		if ( SbVVTD_VVT1_ShortHiCritMet || SbVVTD_VVT1_ShortLoCritMet ) {
			SbVVTD_VVT1_FailCritMet = CbTRUE;
		} else {
			SbVVTD_VVT1_FailCritMet = CbFALSE;
		}
	}

	/* Check_VVT2_Output_Status */
	if ( SbVVTD_EnblCritMet != CbFALSE ) {
		if ( GetHWIO_VVT2OutputFaultShortHi() ) {
			SbVVTD_VVT2_ShortHiCritMet = CbTRUE;
		} else {
			SbVVTD_VVT2_ShortHiCritMet = CbFALSE;
		}

		if ( GetHWIO_VVT2OutputFaultShortLo() && GetVIOS_CCP_PowerOK() ) {
			SbVVTD_VVT2_ShortLoCritMet = CbTRUE;
		} else if ( GetVIOS_CCP_PowerOK() ) {
			SbVVTD_VVT2_ShortLoCritMet = CbFALSE;
		} else {
			/* do nothing */
		}

		if ( SbVVTD_VVT2_ShortLoCritMet || SbVVTD_VVT2_ShortHiCritMet ) {
			SbVVTD_VVT2_FailCritMet = CbTRUE;
		} else {
			SbVVTD_VVT2_FailCritMet = CbFALSE;
		}
	}

	/* Check_VVT1_Output_Counters */
	UpdateOBDU_SingleTestCntrs( SbVVTD_VVT1_TestComplete_Internal,
							   SbVVTD_EnblCritMet,
							   SbVVTD_VVT1_FailCritMet,
							   &ScVVTD_VVT1_FailCntr,
							   &ScVVTD_VVT1_SampleCntr );

	/* Check_VVT2_Output_Counters */
	UpdateOBDU_SingleTestCntrs( SbVVTD_VVT2_TestComplete_Internal,
							   SbVVTD_EnblCritMet,
							   SbVVTD_VVT2_FailCritMet,
							   &ScVVTD_VVT2_FailCntr,
							   &ScVVTD_VVT2_SampleCntr );

	/* Perform_VVT1_Output_Cntr_Evaluation */
	if ( SbVVTD_VVT1_TestComplete_Internal != CbFALSE ) {
		SbVVTD_VVT1_TestComplete_Internal = CbFALSE;
	}

	if ( ScVVTD_VVT1_FailCntr >= KcVVTD_VVT1OutFailThrsh )
	{
		SbVVTD_VVT1_TestFailed = CbTRUE;
		if (SbVVTD_VVT1_ShortHiCritMet) {
			SbVVTD_VVT1_TestFailedHi = CbTRUE;
		} else {
			SbVVTD_VVT1_TestFailedLo = CbTRUE;
		}
		SbVVTD_VVT1_TestComplete_Internal = CbTRUE;
	}
	else if ( ( ScVVTD_VVT1_SampleCntr >= KcVVTD_VVT1OutSampleThrsh )
		   && ( SbVVTD_VVT1_FailCritMet == CbFALSE ) )
	{
		SbVVTD_VVT1_TestFailed = CbFALSE;
		SbVVTD_VVT1_TestFailedHi = CbFALSE;
		SbVVTD_VVT1_TestFailedLo = CbFALSE;
		SbVVTD_VVT1_TestComplete_Internal = CbTRUE;
	}

	SbVVTD_VVT1_TestComplete |= SbVVTD_VVT1_TestComplete_Internal;
	
	/* Perform_VVT2_Output_Cntr_Evaluation */
	if ( SbVVTD_VVT2_TestComplete_Internal != CbFALSE ) {
		SbVVTD_VVT2_TestComplete_Internal = CbFALSE;
	}

	if ( ScVVTD_VVT2_FailCntr >= KcVVTD_VVT2OutFailThrsh )
	{
		SbVVTD_VVT2_TestFailed = CbTRUE;
		if (SbVVTD_VVT2_ShortHiCritMet) {
			SbVVTD_VVT2_TestFailedHi = CbTRUE;
		} else {
			SbVVTD_VVT2_TestFailedLo = CbTRUE;
		}
		SbVVTD_VVT2_TestComplete_Internal = CbTRUE;
	}
	else if ( ( ScVVTD_VVT2_SampleCntr >= KcVVTD_VVT1OutSampleThrsh )
		   && ( SbVVTD_VVT2_FailCritMet == CbFALSE ) )
	{
		SbVVTD_VVT2_TestFailed = CbFALSE;
		SbVVTD_VVT2_TestFailedHi = CbFALSE;
		SbVVTD_VVT2_TestFailedLo = CbFALSE;
		SbVVTD_VVT2_TestComplete_Internal = CbTRUE;
	}

	SbVVTD_VVT2_TestComplete |= SbVVTD_VVT2_TestComplete_Internal;
}


/*****************************************************************************
* DD/MM/YY     Who         SCR#
* 
******************************************************************************/
