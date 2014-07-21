/*****************************************************************************
* Filename:                   prgdmall.c
*
* Description:                Purge Output Diagnostics
*
* List of functions:          void InitETCD_Purge_RstToKeyOn(void)
*                             void InitETCD_Purge_OFVC_Clear (void)
*                             void MngETCD_Purge_125msTasks(void)
*
* C Software Project FORWARD EMS
* (c) Copyright Delco Electronics  1999
*****************************************************************************/

/******************************************************************************
*  Include Files
*****************************************************************************/
#include "etcdcald.h"   /* For Definition-Declaration check   */
#include "etcdpapi.h"   /* For Definition-Declaration check   */
#include "mall_lib.h"
#include "timclib.h"
#include "v_power.h"
#include "intr_ems.h"
#include "dd_l9958_interface.h"

/*****************************************************************************
 *  Constant Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Local Variable Definitions
 *****************************************************************************/
 TbBOOLEAN            SbETCD_DisableFltPresent;
 TbBOOLEAN            SbETCD_EnblCritMet;
 
 /* for vvt1 output channel */
 TbBOOLEAN            SbETCD_FailCritMet;
 T_COUNT_WORD         ScETCD_FailCntr;
 T_COUNT_WORD         ScETCD_SampleCntr;
 TbBOOLEAN            SbETCD_TestComplete;
 TbBOOLEAN            SbETCD_TestComplete_Internal;
 TbBOOLEAN            SbETCD_ShortLoCritMet;
 TbBOOLEAN            SbETCD_ShortHiCritMet;

 #pragma section DATA " " ".nc_nvram"
 TbBOOLEAN            SbETCD_TestFailed;
 TbBOOLEAN            SbETCD_TestFailedHi;
 TbBOOLEAN            SbETCD_TestFailedLo;
 #pragma section DATA " " ".bss"

/*****************************************************************************
 *
 * Function:           InitETCD_Purge_RstToKeyOn
 * Description:        This process will Initialize the Purge Solenoid
 *                     diagnostic variables on
 *                     (pspec: CONTROLLER_RESET_COMPLETE_To_KEY_ON)
 *
 * Parameters:         None
 * Return:             None
 *****************************************************************************/
#if 0
void InitETCD_RstToKeyOff(void)
{
  SbETCD_DisableFltPresent = CbFALSE;
  SbETCD_EnblCritMet       = CbFALSE;
                          
  SbETCD_FailCritMet       = CbFALSE;
  SbETCD_ShortLoCritMet    = CbFALSE;
  SbETCD_ShortHiCritMet    = CbFALSE;
  ScETCD_FailCntr          = V_COUNT_WORD(0);
  ScETCD_SampleCntr        = V_COUNT_WORD(0);
 // SbETCD_TestFailed = CbFALSE;
  SbETCD_TestComplete_Internal = CbFALSE;
}
#endif

/*****************************************************************************
 *
 * Function:    MngETCD_125msTasks
 * Description: This process will execute VVT diagnostic at
 *              125 ms loop
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void MngETCD_125msTasks(void)
{
	/* Determine_ETCD_Output_Enable_Criteria_Met */
	if ((GetVIOS_IgnSt() == CeIGN_ON) && (GetVIOS_U_IgnVolt() > KfETCD_U_SystemThrshLo)) {
		SbETCD_EnblCritMet = CbTRUE;
	} else {
		SbETCD_EnblCritMet = CbFALSE;
	}

	/* Check_Output_Status */
	if ( SbETCD_EnblCritMet != CbFALSE ) {
		if ( L9958_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(L9958_Fault_Log) && GetVIOS_ETC_PowerOK() ) {
			SbETCD_ShortHiCritMet = CbTRUE;
		} else {
			SbETCD_ShortHiCritMet = CbFALSE;
		}

		// if ( L9958_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(L9958_Fault_Log) && GetVIOS_ETC_PowerOK() ) {
			// SbETCD_ShortLoCritMet = CbTRUE;
		// } else if ( GetVIOS_ETC_PowerOK() ) {
			// SbETCD_ShortLoCritMet = CbFALSE;
		// } else {
			// /* do nothing */
		// }

		/* Note, l9958 OL_ON may report OpenLoad by mistake when the DC is low, so we should add lowest limitation */
		if ((FAULT_Get_Occured_Short_To_Ground(L9958_Fault_Log) && GetVIOS_ETC_PowerOK()) ||
			(L9958_Msg_Get_OL_OFF(L9958_HWDIAG_STATUS) && GetVIOS_ETC_PowerOK()) || 
			(L9958_Msg_Get_OL_ON(L9958_HWDIAG_STATUS) && (GetEVAP_ETC_DutyCycle() > KfETCD_LoBandDCThrsh)) )
		{
			SbETCD_ShortLoCritMet = CbTRUE;
		} 
		else if ( GetVIOS_ETC_PowerOK() )
		{
			SbETCD_ShortLoCritMet = CbFALSE;
		}
		else
		{
			/* do nothing */
		}

		if ( SbETCD_ShortHiCritMet || SbETCD_ShortLoCritMet ) {
			SbETCD_FailCritMet = CbTRUE;
		} else {
			SbETCD_FailCritMet = CbFALSE;
		}
	}

	/* Check_Output_Counters */
	UpdateOBDU_SingleTestCntrs( SbETCD_TestComplete_Internal,
							   SbETCD_EnblCritMet,
							   SbETCD_FailCritMet,
							   &ScETCD_FailCntr,
							   &ScETCD_SampleCntr );

	/* Perform_Output_Cntr_Evaluation */
	if ( SbETCD_TestComplete_Internal != CbFALSE ) {
		SbETCD_TestComplete_Internal = CbFALSE;
	}

	if ( ScETCD_FailCntr >= KcETCD_OutFailThrsh )
	{
		SbETCD_TestFailed = CbTRUE;
		if (SbETCD_ShortHiCritMet) {
			SbETCD_TestFailedHi = CbTRUE;
		} else {
			SbETCD_TestFailedLo = CbTRUE;
		}
		SbETCD_TestComplete_Internal = CbTRUE;
	}
	else if ( ( ScETCD_SampleCntr >= KcETCD_OutSampleThrsh )
		   && ( SbETCD_FailCritMet == CbFALSE ) )
	{
		SbETCD_TestFailed = CbFALSE;
		SbETCD_TestFailedHi = CbFALSE;
		SbETCD_TestFailedLo = CbFALSE;
		SbETCD_TestComplete_Internal = CbTRUE;
	}

	SbETCD_TestComplete |= SbETCD_TestComplete_Internal;
}


/*****************************************************************************
* DD/MM/YY     Who         SCR#
* 
******************************************************************************/
