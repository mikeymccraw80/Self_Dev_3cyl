/******************************************************************************
 *
 * Filename:          emsdmlib.c
 *
 * Description:       Common routines of OBDII program to process EMS
 *                    side I/O hardware Diagnostic (EMSD).
 *
 * Global Functions Defined:
 *                    EvaluateEMSD_FrontACEVTEnblCriteria
 *                    
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 1997-2005 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/csrc/emsdmlib.c/1 %
 * %date_created:  Wed Mar 19 10:10:09 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "intr_ems.h"
#include "t_gentypes.h"


/******************************************************************************
 *  Function Exports
 *****************************************************************************/
/*****************************************************************************
 *
 * Function:     ChkEMSD_GetPSVIorTPICFault
 * Description:  (Check_GetPSVI_TPICfault)
 *       Determine if  Fault is  existing on TPIC or PSVI fault buffer
 *
 * Parameters:
 *    TbBOOLEAN                 LbEMSD_xxxxEnblCriteriaMet         (input)
 *    TbBOOLEAN                 LbOBD_PSVI_TPICFault               (input)
 * Return:
 *    TbBOOLEAN                 LbEMSD_xxxxEnblCriteriaMet        (output)
 *****************************************************************************/
 TbBOOLEAN ChkEMSD_GetPSVIorTPICFault (
            TbBOOLEAN            LbEMSD_xxxxEnblCriteriaMet,
            TbBOOLEAN            LbOBD_PSVI_TPICFault
                                          )
{
  /* Return value */
  TbBOOLEAN          LbEMSD_xxxxFailCriteriaMet ;


  if ( (LbEMSD_xxxxEnblCriteriaMet != CbFALSE)
       && (LbOBD_PSVI_TPICFault) )
    {
      LbEMSD_xxxxFailCriteriaMet = CbTRUE ;
    }
  else
    {
      LbEMSD_xxxxFailCriteriaMet = CbFALSE ;
    }

  return (LbEMSD_xxxxFailCriteriaMet) ;

}
 

/*  =========================================================================
 *  Functions for AC Clutch Relay Diagnostic
 *  =========================================================================*/
/******************************************************************************
 *
 * Function:     EvaluateEMSD_ACCDEnblCriteria
 * Description:  (Evaluate_ACCD_Enable_Criteria)
 *               This process will enable the  AC Clutch relay Hardware diagnostic
 *               if the enable conditions are met.
 *
 * Parameters:
 *    T_COUNT_WORD              KfEMSD_t_IgnitionOnDelay               (input)
 *    TbBOOLEAN                 *LbEMSD_ACCDEnblCriteriaMet      (output)
 * Return:
 *    Nil
 *
 *****************************************************************************/
 void EvaluateEMSD_ACCDEnblCriteria (
            T_SECONDS        KfEMSD_t_IgnitionOnDelay,
            TbBOOLEAN        *LbEMSD_ACCDEnblCriteriaMet)
{


  if ( (GetVIOS_IgnSt() == CeIGN_ON)
       && (GetVIOS_t_IgnOnTime() >= KfEMSD_t_IgnitionOnDelay)
       && (GetVIOS_ACCD_Presnt())
      )                           /* some relevant conditions can be added here for enable criteria */
    {
      *LbEMSD_ACCDEnblCriteriaMet = CbTRUE ;
    }
  else
    {
      *LbEMSD_ACCDEnblCriteriaMet = CbFALSE ;
    }


} 

/*  =========================================================================
 *  Functions for Main Power Relay Diagnostic
 *  =========================================================================*/
/******************************************************************************
 *
 * Function:     EvaluateEMSD_MPRDEnblCriteria
 * Description:  (Evaluate_MPRD_Enable_Criteria)
 *               This process will enable the  Main Power relay Hardware diagnostic
 *               if the enable conditions are met.
 *
 * Parameters:
 *    T_COUNT_WORD              KfEMSD_t_IgnitionOnDelay               (input)
 *    TbBOOLEAN                 *LbEMSD_MPRDEnblCriteriaMet      (output)
 * Return:
 *    Nil
 *
 *****************************************************************************/
 void EvaluateEMSD_MPRDEnblCriteria (
            T_SECONDS        KfEMSD_t_MPRDIgnitionOnDelay,
            TbBOOLEAN        *LbEMSD_MPRDEnblCriteriaMet)
{


  if ( (GetVIOS_IgnSt() == CeIGN_ON)
  	&&(GetVIOS_t_IgnOnTime() >= KfEMSD_t_MPRDIgnitionOnDelay)
       && (GetVIOS_MPRD_Presnt())
      )                           /* some relevant conditions can be added here for enable criteria */
    {
      *LbEMSD_MPRDEnblCriteriaMet = CbTRUE ;
    }
  else
    {
      *LbEMSD_MPRDEnblCriteriaMet = CbFALSE ;
    }


} 

/*  =========================================================================
 *  Functions for MIL Diagnostic
 *  =========================================================================*/
/******************************************************************************
 *
 * Function:     EvaluateEMSD_MILDEnblCriteria
 * Description:  (Evaluate_MILD_Enable_Criteria)
 *               This process will enable the  MIL Hardware diagnostic
 *               if the enable conditions are met.
 *
 * Parameters:
 *    T_COUNT_WORD              KfEMSD_t_IgnitionOnDelay               (input)
 *    TbBOOLEAN                 *LbEMSD_MILDEnblCriteriaMet      (output)
 * Return:
 *    Nil
 *
 *****************************************************************************/
 void EvaluateEMSD_MILDEnblCriteria (
            T_SECONDS        KfEMSD_t_IgnitionOnDelay,
            TbBOOLEAN        *LbEMSD_MILDEnblCriteriaMet)
{


  if ( (GetVIOS_IgnSt() == CeIGN_ON)
       && (GetVIOS_t_IgnOnTime() >= KfEMSD_t_IgnitionOnDelay)
       && (GetVIOS_MainPwrRly_Status())
      )                           /* some relevant conditions can be added here for enable criteria */
    {
      *LbEMSD_MILDEnblCriteriaMet = CbTRUE ;
    }
  else
    {
      *LbEMSD_MILDEnblCriteriaMet = CbFALSE ;
    }


}


/*  =========================================================================
 *  Functions for Fuel Pump Relay Diagnostic
 *  =========================================================================*/
/******************************************************************************
 *
 * Function:     EvaluateEMSD_FPRDEnblCriteria
 * Description:  (Evaluate_FPRD_Enable_Criteria)
 *               This process will enable the  Fuel Pump relay Hardware diagnostic
 *               if the enable conditions are met.
 *
 * Parameters:
 *    T_COUNT_WORD              KfEMSD_t_IgnitionOnDelay               (input)
 *    TbBOOLEAN                 *LbEMSD_FPRDEnblCriteriaMet      (output)
 * Return:
 *    Nil
 *
 *****************************************************************************/
 void EvaluateEMSD_FPRDEnblCriteria (
            T_SECONDS        KfEMSD_t_IgnitionOnDelay,
            TbBOOLEAN        *LbEMSD_FPRDEnblCriteriaMet)
{


  if ( (GetVIOS_IgnSt() == CeIGN_ON)
       && (GetVIOS_t_IgnOnTime() >= KfEMSD_t_IgnitionOnDelay)
      )                           /* some relevant conditions can be added here for enable criteria */
    {
      *LbEMSD_FPRDEnblCriteriaMet = CbTRUE ;
    }
  else
    {
      *LbEMSD_FPRDEnblCriteriaMet = CbFALSE ;
    }


} 


/*  =========================================================================
 *  Functions for Fanx Diagnostic
 *  =========================================================================*/
/******************************************************************************
 *
 * Function:     EvaluateEMSD_FANAEnblCriteria
 * Description:  (Evaluate_Fan1_Enable_Criteria)
 *               This process will enable the  fan1 Hardware diagnostic
 *               if the enable conditions are met.
 *
 * Parameters:
 *    T_COUNT_WORD              KfEMSD_t_IgnitionOnDelay               (input)
 *    TbBOOLEAN                 *LbEMSD_FANAEnblCriteriaMet      (output)
 * Return:
 *    Nil
 *
 *****************************************************************************/
 void EvaluateEMSD_FANAEnblCriteria (
            T_SECONDS        KfEMSD_t_IgnitionOnDelay,
            TbBOOLEAN        *LbEMSD_FANAEnblCriteriaMet)
{


  if ( (GetVIOS_IgnSt() == CeIGN_ON)
       && (GetVIOS_t_IgnOnTime() >= KfEMSD_t_IgnitionOnDelay)
       && (GetVIOS_FANA_Presnt())
      )                           /* some relevant conditions can be added here for enable criteria */
    {
      *LbEMSD_FANAEnblCriteriaMet = CbTRUE ;
    }
  else
    {
      *LbEMSD_FANAEnblCriteriaMet = CbFALSE ;
    }


} 

/******************************************************************************
 *
 * Function:     EvaluateEMSD_FANBEnblCriteria
 * Description:  (Evaluate_Fan2_Enable_Criteria)
 *               This process will enable the  fan2 Hardware diagnostic
 *               if the enable conditions are met.
 *
 * Parameters:
 *    T_COUNT_WORD              KfEMSD_t_IgnitionOnDelay               (input)
 *    TbBOOLEAN                 *LbEMSD_FANBEnblCriteriaMet      (output)
 * Return:
 *    Nil
 *
 *****************************************************************************/
 void EvaluateEMSD_FANBEnblCriteria (
            T_SECONDS        KfEMSD_t_IgnitionOnDelay,
            TbBOOLEAN        *LbEMSD_FANBEnblCriteriaMet)
{


  if ( (GetVIOS_IgnSt() == CeIGN_ON)
       && (GetVIOS_t_IgnOnTime() >= KfEMSD_t_IgnitionOnDelay)
       && (GetVIOS_FANB_Presnt())
      )                           /* some relevant conditions can be added here for enable criteria */
    {
      *LbEMSD_FANBEnblCriteriaMet = CbTRUE ;
    }
  else
    {
      *LbEMSD_FANBEnblCriteriaMet = CbFALSE ;
    }


}

///*  =========================================================================
// *  Functions for Oxygen Sensor Heater Diagnostic
// *  =========================================================================*/
///******************************************************************************
// *
// * Function:     EvaluateEOSD_O2_xx_HtrEnblCriteria
// * Description:  (Pspec :Evaluate_O2_xx_Heater_Enable_Criteria)
// *               This process will enable the O2 Heater diagnostic
// *               if the enable conditions are met.
// *
// * Parameters:
// *    T_COUNT_WORD              KfEOSD_t_xx_HtrEngRunThrsh              (input)
// * Return:
// *    TbBOOLEAN                 LbEOSD_O2_xx_HtrEnblCriteriaMet        (output)
// *
// *****************************************************************************/

TbBOOLEAN EvaluateEOSD_O2_xx_HtrEnblCriteria (
            T_COUNT_WORD     KfEOSD_t_xx_HtrEngRunThrsh )
{
  /* Return value */
  TbBOOLEAN        LbEOSD_O2_xx_HtrEnblCriteriaMet ;

  if ( (GetVIOS_IgnSt () == CeIGN_ON)
       && (GetVIOS_t_EngRunTime () >= KfEOSD_t_xx_HtrEngRunThrsh)
       && (GetOSSP_O2_DiagCntrDsbl() == CbFALSE) )
    {
      LbEOSD_O2_xx_HtrEnblCriteriaMet = CbTRUE ;
    }
  else
    {
      LbEOSD_O2_xx_HtrEnblCriteriaMet = CbFALSE ;
    }

  return (LbEOSD_O2_xx_HtrEnblCriteriaMet) ;
}



/*****************************************************************************
 *
 * Function:     ChkEOSD_O2_xx_HtrCurrentRange
 * Description:  (Pspec :Check_O2_xx_Heater_Current_Range)
 *		 Determine if the O2 Heater current is sufficient for
 *               operation.
 *
 * Parameters:
 *    TbBOOLEAN                 LbEOSD_O2_xx_HtrEnblCriteriaMet         (input)
 *    T_AMPSa                   LfOBD_O2_xx_Heater_Current              (input)
 *    T_AMPSa                   KfEOSD_I_xx_HtrCurrThrs                 (input)
 *
 * Return:
 *    TbBOOLEAN                 LbEOSD_O2_xx_HtrEnblCriteriaMet        (output)
 *
 *****************************************************************************/
TbBOOLEAN ChkEOSD_O2_xx_Htr_GetPSVIFault (
            TbBOOLEAN            LbEOSD_O2_xx_HtrEnblCriteriaMet,
            TbBOOLEAN            LbOBD_O2_xx_Htr_PSVIFault
                                          )
{
  /* Return value */
  TbBOOLEAN          LbEOSD_O2_xx_HtrFailCriteriaMet ;


  if ( (LbEOSD_O2_xx_HtrEnblCriteriaMet != CbFALSE)
       && (LbOBD_O2_xx_Htr_PSVIFault) )
    {
      LbEOSD_O2_xx_HtrFailCriteriaMet = CbTRUE ;
    }
  else
    {
      LbEOSD_O2_xx_HtrFailCriteriaMet = CbFALSE ;
    }

  return (LbEOSD_O2_xx_HtrFailCriteriaMet) ;

}


/*****************************************************************************

 * Function:           UpdateOBDU_DoubleTestCntrs

 * Description:        This process updates the OBDII diagnostic counters for

 *                     a pair of tests (2). The counters will be reset when

 *                     tests were completed. The sample counters will be

 *                     updated every time called, while the failure counters

 *                     are only updated when failures occur.

 * Parameters:

 *                     TbBOOLEAN LbOBDU_TestComplete          (input)

 *                     TbBOOLEAN LbOBDU_TestEnblCriteriaMet   (input)

 *                     TbBOOLEAN LbOBDU_TestA_FailCriteriaMet (input)

 *                     TbBOOLEAN LbOBDU_TestB_FailCriteriaMet (input)

 *                     T_COUNT_WORD *LcOBDU_TestA_FailCntr    (output)

 *                     T_COUNT_WORD *LcOBDU_TestB_FailCntr    (output)

 *                     T_COUNT_WORD *LcOBDU_SampleCntr        (output)

 * Return:             None

 *****************************************************************************/

 void UpdateOBDU_DoubleTestCntrs(

                TbBOOLEAN    LbOBDU_TestComplete,

                TbBOOLEAN    LbOBDU_TestEnblCriteriaMet,

                TbBOOLEAN    LbOBDU_TestA_FailCriteriaMet,

                TbBOOLEAN    LbOBDU_TestB_FailCriteriaMet,

                T_COUNT_WORD *LcOBDU_TestA_FailCntr,

                T_COUNT_WORD *LcOBDU_TestB_FailCntr,

                T_COUNT_WORD *LcOBDU_SampleCntr )

{

  /* Reset counters if the test was completed in the previous loop */

  if ( LbOBDU_TestComplete )

  {

    *LcOBDU_TestA_FailCntr = V_COUNT_WORD(0);

    *LcOBDU_TestB_FailCntr = V_COUNT_WORD(0);

    *LcOBDU_SampleCntr     = V_COUNT_WORD(0);

  }

  /* update appropriate counters */

  if ( LbOBDU_TestEnblCriteriaMet )

  {

    /* update sample counter*/

    (*LcOBDU_SampleCntr)++;

    if ( LbOBDU_TestA_FailCriteriaMet )

    {

      (*LcOBDU_TestA_FailCntr)++;

    }

    else if ( LbOBDU_TestB_FailCriteriaMet )

    {

      (*LcOBDU_TestB_FailCntr)++;

    }

  }

}

/******************************************************************************

 *  Function:     EvalOBDU_DoubleXofY

 *  Description:  This process compares the numbers of failures/samples

 *                of a couple of (2) tests to

 *                calibration thresholds. If the number of failures reaches the

 *                fail threshold before the number of samples reaches the

 *                sample threshold, then the test is complete and a fail is

 *                reported. If the sample threshold is reached first, then the

 *                test is complete and a pass is reported. If neither

 *                threshold has been reached, then the test is not complete.

 *  Parameters:   T_COUNT_WORD LcOBDU_TestA_FailCntr     (input)

 *                T_COUNT_WORD LcOBDU_TestB_FailCntr     (input)

 *                T_COUNT_WORD LcOBDU_SampleCntr         (input)

 *                T_COUNT_WORD KcOBDU_TestA_FailThrsh    (input)

 *                T_COUNT_WORD KcOBDU_TestB_FailThrsh    (input)

 *                T_COUNT_WORD KcOBDU_SampleThrsh        (input)

 *                TbBOOLEAN    *LbOBDU_TestComplete      (output)

 *                TbBOOLEAN    *LbOBDU_TestA_Failed      (output)

 *                TbBOOLEAN    *LbOBDU_TestB_Failed      (output)

 *

 *  Returns:      None

 ******************************************************************************/

 void EvalOBDU_DoubleXofY(

              T_COUNT_WORD LcOBDU_TestA_FailCntr,

              T_COUNT_WORD LcOBDU_TestB_FailCntr,

              T_COUNT_WORD LcOBDU_SampleCntr,

              T_COUNT_WORD KcOBDU_TestA_FailThrsh,

              T_COUNT_WORD KcOBDU_TestB_FailThrsh,

              T_COUNT_WORD KcOBDU_SampleThrsh,

              TbBOOLEAN    *LbOBDU_TestComplete,

              TbBOOLEAN    *LbOBDU_TestA_Failed,

              TbBOOLEAN    *LbOBDU_TestB_Failed )

{

  if ( LcOBDU_TestA_FailCntr >= KcOBDU_TestA_FailThrsh )

  {

    *LbOBDU_TestA_Failed = CbTRUE;

    *LbOBDU_TestB_Failed = CbFALSE;

    *LbOBDU_TestComplete = CbTRUE;

  }

  else if ( LcOBDU_TestB_FailCntr >= KcOBDU_TestB_FailThrsh )

  {

    *LbOBDU_TestA_Failed = CbFALSE;

    *LbOBDU_TestB_Failed = CbTRUE;

    *LbOBDU_TestComplete = CbTRUE;

  }

  else if ( LcOBDU_SampleCntr >= KcOBDU_SampleThrsh )

  {

    *LbOBDU_TestA_Failed = CbFALSE;

    *LbOBDU_TestB_Failed = CbFALSE;

    *LbOBDU_TestComplete = CbTRUE;

  }

  else

  {

    *LbOBDU_TestComplete = CbFALSE;

  }

}

/******************************************************************************

 *  Function:     EvalOBDU_SingleXofY

 *  Description:  This process compares the number of failures/samples

 *                of single test to

 *                calibration thresholds. If the number of failures reaches the

 *                fail threshold before the number of samples reaches the

 *                sample threshold, then the test is complete and a fail is

 *                reported. If the sample threshold is reached first, then the

 *                test is complete and a pass is reported. If neither

 *                threshold has been reached, then the test is not complete.

 *  Parameters:   T_COUNT_WORD  LcOBDU_FailCntr       (input)

 *                T_COUNT_WORD  LcOBDU_SampleCntr     (input)

 *                T_COUNT_WORD  KcOBDU_FailThrsh      (input)

 *                T_COUNT_WORD  KcOBDU_SampleThrsh    (input)

 *                TbBOOLEAN     *LbOBDU_TestComplete  (output)

 *                TbBOOLEAN     *LbOBDU_TestFailed    (output)

 *  Returns:      None

 ******************************************************************************/

 void EvalOBDU_SingleXofY(

              T_COUNT_WORD LcOBDU_FailCntr,

              T_COUNT_WORD LcOBDU_SampleCntr,

              T_COUNT_WORD KcOBDU_FailThrsh,

              T_COUNT_WORD KcOBDU_SampleThrsh,

              TbBOOLEAN    *LbOBDU_TestComplete,

              TbBOOLEAN    *LbOBDU_TestFailed )

{

  if ( LcOBDU_FailCntr >= KcOBDU_FailThrsh )

  {

    *LbOBDU_TestFailed   = CbTRUE;

    *LbOBDU_TestComplete = CbTRUE;

  }

  else if ( LcOBDU_SampleCntr >= KcOBDU_SampleThrsh )

  {

    *LbOBDU_TestFailed   = CbFALSE;

    *LbOBDU_TestComplete = CbTRUE;

  }

  else

  {

    *LbOBDU_TestComplete = CbFALSE;

  }

}

/*****************************************************************************

 * Function:           UpdateOBDU_SingleTestCntrs

 * Description:        This process updates the OBDII diagnostic counters for

 *                     single test. The counters will be reset when test was

 *                     completed.  The sample counter will be updated every

 *                     time called, while the failure counter is only updated

 *                     when failure occurs.

 * Parameters:

 *                     TbBOOLEAN    LbOBDU_TestComplete          (input)

 *                     TbBOOLEAN    LbOBDU_TestEnblCriteriaMet   (input)

 *                     TbBOOLEAN    LbOBDU_TestFailCriteriaMet   (input)

 *                     T_COUNT_WORD *LcOBDU_FailCntr             (output)

 *                     T_COUNT_WORD *LcOBDU_SampleCntr           (output)

 * Return:             None

 *****************************************************************************/

 void UpdateOBDU_SingleTestCntrs(

                TbBOOLEAN    LbOBDU_TestComplete,

                TbBOOLEAN    LbOBDU_TestEnblCriteriaMet,

                TbBOOLEAN    LbOBDU_TestFailCriteriaMet,

                T_COUNT_WORD *LcOBDU_FailCntr,

                T_COUNT_WORD *LcOBDU_SampleCntr )

{

  /* Reset counters if the test was completed in the previous loop */

  if ( LbOBDU_TestComplete )

  {

    *LcOBDU_FailCntr   = V_COUNT_WORD(0);

    *LcOBDU_SampleCntr = V_COUNT_WORD(0);

  }

  /* update appropriate counters */

  if ( LbOBDU_TestEnblCriteriaMet )

  {

    /* update sample counter */

    (*LcOBDU_SampleCntr)++;

    if ( LbOBDU_TestFailCriteriaMet )

    {

      (*LcOBDU_FailCntr)++;

    }

  }

}



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
\* ============================================================================ */
