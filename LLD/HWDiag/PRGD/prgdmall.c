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
#include "prgdcald.h"   /* For Definition-Declaration check   */
#include "prgdpapi.h"   /* For Definition-Declaration check   */
#include "mall_lib.h"
#include "timclib.h"
#include "intr_ems.h"
#include "v_power.h"

/*****************************************************************************
 *  Constant Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Local Variable Definitions
 *****************************************************************************/
 TbBOOLEAN            SbPRGD_Purge_DisableFltPresent;
 TbBOOLEAN            SbPRGD_Purge_EnblCritMet;
 TbBOOLEAN            SbPRGD_Purge_FailCritMet;
 TbBOOLEAN            SbPRGD_Purge_State1Set;
 TbBOOLEAN            SbPRGD_Purge_State2Set;
 T_COUNT_WORD         ScPRGD_Purge_FailCntr;
 T_COUNT_WORD         ScPRGD_Purge_SampleCntr;
 #pragma section DATA " " ".nc_nvram"
 TbBOOLEAN            SbPRGD_Purge_TestFailed;
 TbBOOLEAN            SbPRGD_Purge_TestFailedHi;
 TbBOOLEAN            SbPRGD_Purge_TestFailedLo;
 #pragma section DATA " " ".bss"
 TbBOOLEAN            SbPRGD_Purge_TestComplete;
 TbBOOLEAN            SbPRGD_Purge_TestComplete_Internal;
 TbBOOLEAN            SbPRGD_Purge_ShortLoCritMet;
 TbBOOLEAN            SbPRGD_Purge_ShortHiCritMet;

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
#if 0
FAR_COS  void InitPRGD_Purge_RstToKeyOff(void)
{

  SbPRGD_Purge_DisableFltPresent = CbFALSE;
  SbPRGD_Purge_EnblCritMet = CbFALSE;
  SbPRGD_Purge_FailCritMet = CbFALSE;
  SbPRGD_Purge_ShortLoCritMet = CbFALSE;
   SbPRGD_Purge_ShortHiCritMet= CbFALSE;
  SbPRGD_Purge_State1Set = CbFALSE;
  SbPRGD_Purge_State2Set = CbFALSE;
  ScPRGD_Purge_FailCntr = V_COUNT_WORD(0);
  ScPRGD_Purge_SampleCntr = V_COUNT_WORD(0);
 // SbPRGD_Purge_TestFailed = CbFALSE;
  SbPRGD_Purge_TestComplete_Internal = CbFALSE;

}

#endif

/*****************************************************************************
 *
 * Function:    MngPRGD_Purge_125msTasks
 * Description: This process will execute Purge Solenoid Output diagnostic at
 *              125 ms loop
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void MngPRGD_Purge_125msTasks(void)
{
	/* Determine_Purge_Solenoid_Output_Enable_Criteria_Met */
	if ((GetVIOS_EngSt() == CeENG_RUN) && (GetVIOS_U_IgnVolt() > KfPRGD_U_SystemThrshLo)) {
		SbPRGD_Purge_EnblCritMet = CbTRUE;
	} else {
		SbPRGD_Purge_EnblCritMet = CbFALSE;
	}

	/* Check_Purge_Solenoid_Output_Status */
	if ( SbPRGD_Purge_EnblCritMet != CbFALSE )
	{
		if ( GetHWIO_PurgeSolOutputFaultShortHi() ) {
			SbPRGD_Purge_ShortHiCritMet = CbTRUE;
		} else {
			SbPRGD_Purge_ShortHiCritMet = CbFALSE;
		}

		if ( GetHWIO_PurgeSolOutputFaultShortLo() && GetVIOS_CCP_PowerOK() ) {
			SbPRGD_Purge_ShortLoCritMet = CbTRUE;
		} else if ( GetVIOS_CCP_PowerOK() ) {
			SbPRGD_Purge_ShortLoCritMet = CbFALSE;
		} else {
			/* do nothing */
		}

		if ( SbPRGD_Purge_ShortHiCritMet ) {
			SbPRGD_Purge_FailCritMet = CbTRUE;
		} else if ( SbPRGD_Purge_ShortLoCritMet ) {
			SbPRGD_Purge_FailCritMet = CbTRUE;
		} else {
			SbPRGD_Purge_FailCritMet = CbFALSE;
		}
	}

	/* Check_Purge_Solenoid_Output_Counters */
	UpdateOBDU_SingleTestCntrs( SbPRGD_Purge_TestComplete_Internal,
							   SbPRGD_Purge_EnblCritMet,
							   SbPRGD_Purge_FailCritMet,
							   &ScPRGD_Purge_FailCntr,
							   &ScPRGD_Purge_SampleCntr );

	/* Perform_Purge_Solenoid_Output_Cntr_Evaluation */
	if ( SbPRGD_Purge_TestComplete_Internal != CbFALSE ) {
		SbPRGD_Purge_TestComplete_Internal = CbFALSE;
	}

	if ( ScPRGD_Purge_FailCntr >= KcPRGD_PurgeOutFailThrsh )
	{
		SbPRGD_Purge_TestFailed = CbTRUE;
		if (SbPRGD_Purge_ShortHiCritMet) {
			SbPRGD_Purge_TestFailedHi = CbTRUE;
		} else {
			SbPRGD_Purge_TestFailedLo = CbTRUE;
		}
		SbPRGD_Purge_TestComplete_Internal = CbTRUE;
	}
	else if ( ( ScPRGD_Purge_SampleCntr >= KcPRGD_PurgeOutSampleThrsh )
		   && ( SbPRGD_Purge_FailCritMet == CbFALSE ) )
	{
		SbPRGD_Purge_TestFailed = CbFALSE;
		SbPRGD_Purge_TestFailedHi = CbFALSE;
		SbPRGD_Purge_TestFailedLo = CbFALSE;
		SbPRGD_Purge_TestComplete_Internal = CbTRUE;
	}

	SbPRGD_Purge_TestComplete |= SbPRGD_Purge_TestComplete_Internal;
}


/*****************************************************************************
* DD/MM/YY     Who         SCR#
* 
******************************************************************************/
