/*****************************************************************************
* Filename:             emsdsmrd.c
*
* Description:          OBDII program to process Smr Hardware
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
*   Gloabol Function Declarations
******************************************************************************/
extern uint8_t SMR_Enable_State;
/*****************************************************************************
 *  Static Data Define
 *****************************************************************************/

/*
 *
 * SMR
 */
TbBOOLEAN        SbEMSD_SMREnblCriteriaMet ;
TbBOOLEAN        SbEMSD_SMRShortHiFailCriteriaMet ;
TbBOOLEAN        SbEMSD_SMRTestComplete ;
T_COUNT_WORD     ScEMSD_SMRShortHiFailCntr ;
T_COUNT_WORD     VcEMSD_SMRSampleCntr ;
TbBOOLEAN        SbEMSD_SMRTestComplete_Internal;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN        SbEMSD_SMRShortHiTestFailed ;
#pragma section DATA " " ".bss"


/*****************************************************************************
 *  Function definition
 ******************************************************************************/
#if 1
/*****************************************************************************
 *
 * Function:     InitEMSD_SMRRstToKeyOn
 * Description:  Initialization functions
 *               ( CONTROLLER_RESET_COMPLETE_TO_KEY_ON)
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void InitEMSD_SmrRstToKeyOn(void)
{  
  
  SbEMSD_SMREnblCriteriaMet = CbFALSE ;
  SbEMSD_SMRShortHiFailCriteriaMet = CbFALSE ;
  SbEMSD_SMRTestComplete = CbFALSE ;
  SbEMSD_SMRTestComplete_Internal = CbFALSE;
 // SbEMSD_FANAShortHiTestFailed = CbFALSE ;
 // SbEMSD_FANAShortLoTestFailed = CbFALSE ;
  ScEMSD_SMRShortHiFailCntr = V_COUNT_WORD (0) ;
  VcEMSD_SMRSampleCntr = V_COUNT_WORD (0) ;

}
#endif
 /*****************************************************************************
 *
 * Function:     MngEMSD_SMR200msTasks
 * Description:  This procedure will be called by the operating system
 *               during every 200ms timer event. The procedure
 *               includes calls to all timer triggered functions.
 *
 * Parameters:   None
 * Return:       None
 *****************************************************************************/
void MngEMSD_SMR200msTasks (void)
{
	/* Evaluate_SMR_Enable_Criteria */
	EvaluateEMSD_SMREnblCriteria ( KfEMSD_t_IgnitionOnDelay, &SbEMSD_SMREnblCriteriaMet);

    if(SMR_Enable_State ==true){ 
		SbEMSD_SMRShortHiFailCriteriaMet =\
			 ChkEMSD_GetPSVIorTPICFault (SbEMSD_SMREnblCriteriaMet, GetVIOS_SMR_FaultShortHi());
    }

  /*    Update_SMR_Test_Counters
   *    ========================================
   *    This process updates the fan1 diagnostic
   *    test counters. */

  if ( SbEMSD_SMRTestComplete_Internal )

  {

    ScEMSD_SMRShortHiFailCntr = V_COUNT_WORD(0);

    VcEMSD_SMRSampleCntr     = V_COUNT_WORD(0);

  }

  /* update appropriate counters */

  if ( SbEMSD_SMREnblCriteriaMet )

  {

    /* update sample counter*/

    VcEMSD_SMRSampleCntr++;

    if ( SbEMSD_SMRShortHiFailCriteriaMet )

    {

      ScEMSD_SMRShortHiFailCntr++;

    }

  }

  /*    Perform_SMR_XofY_Evaluations
   *    ============================================
   *    If the failure count threshold is reached before the
   *    sample count threshold is reached then the test is
   *    complete and a failure is reported. If the sample
   *    count threshold is reached before the failure count
   *    threshold then the test is complete and a pass is
   *    reported. Reset the test complete flag if the test
   *    was complete the last loop. */

	if ( ScEMSD_SMRShortHiFailCntr >= KcEMSD_SMRShortHiFailThrsh )

	  {

	    SbEMSD_SMRShortHiTestFailed = CbTRUE;

	    SbEMSD_SMRTestComplete_Internal = CbTRUE;

	  }


	  else if ( VcEMSD_SMRSampleCntr >= KcEMSD_SMRShortSmplThrsh )

	  {

	    SbEMSD_SMRShortHiTestFailed = CbFALSE;

	    SbEMSD_SMRTestComplete_Internal = CbTRUE;

	  }

	  else

	  {

	    SbEMSD_SMRTestComplete_Internal = CbFALSE;

	  }
  
	SbEMSD_SMRTestComplete |=SbEMSD_SMRTestComplete_Internal;
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
