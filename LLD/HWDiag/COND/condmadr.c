/******************************************************************************
 *
 * Filename:          condmadr.c
 *
 * Description:       Analog to Digital Input Response Diagnostics
 *
 * Global Functions Defined:
 *                    InitCOND_AD_InputRespRstKeyOn
 *                    InitCOND_AD_InputRespOFVC_Clear
 *                    MngCOND_AD_InputResp15p6msTasksA
 *                    MngCOND_AD_InputResp15p6msTasksB
 *                    GetCOND_AD_RespTstFld
 *                    GetCOND_AD_RespETC_LrnDwnDsblCritMet
 *                    GetCOND_AD_RespETC_DoNotUseAPS_Data
 * Static Functions Defined:
 *                    InitCOND_ADR_CommonZero
 *                    InitCOND_ADR_CommonNonZero
 *                    CalcCOND_AD_RespTimeDelt
 *                    PerfmCOND_AD_InputRespCntrlTestSteps
 * Inline Functions Defined:
 *                    EvalCOND_AD_InputRespEnblCritMet
 *                    EvalCOND_AD_InputRespTestData
 *
 * Forward Engine Management Systems
 *
 * Copyright 2007-2012, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tcb_pt1#1/csrc/condmadr.c/tci_pt3#6 %
 * %date_created:  Thu Feb 02 10:48:14 2012 %
 * %version:       tci_pt3#6 %
 * %derived_by:    mz1hwn %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Include Files                                                            *
 *****************************************************************************/
#include "condcald.h"   /* For COND Local Configuration       */
#include "intr_ems.h"
#include "hal_eng.h"
#include "hal_analog.h"
#include "condpapi.h"

typedef enum
{
  CeCOND_AD_RESP_STEP_DISABLED,    /* 0 */
  CeCOND_AD_RESP_STEP_PRE_SHORT,   /* 1 */
  CeCOND_AD_RESP_STEP_SHORTED,     /* 2 */
  CeCOND_AD_RESP_STEP_POST_SHORT   /* 3 */
} TeCOND_AD_RESP_STEPS;

typedef struct
{
  T_COUNT_WORD          FailCntr;
  T_COUNT_WORD          SampleCntr;
  WORD                  Unused      : 1;  /* available for future use */
  WORD                  PassBlocker : 1;  /* TbBOOLEAN                */
  WORD                  EnblCritMet : 1;  /* TbBOOLEAN                */
  WORD                  FailCritMet : 1;  /* TbBOOLEAN                */
  WORD                  TstComplete : 1;  /* TbBOOLEAN                */
  WORD                  TstFailed   : 1;  /* TbBOOLEAN                */
  WORD                  TstStRpt    : 2;  /* TeSINGLE_TEST_STATUS     */
} TsOBDU_DiagTstData;

typedef T_W_RANGE_0_16                   T_COND_TIME_SEC_0_16;
#define V_COND_TIME_SEC_0_16(val)        V_W_RANGE_0_16(val)
#define S_COND_TIME_SEC_0_16             S_W_RANGE_0_16
/******************************************************************************
 *  Global/Public Variable Definitions
 *****************************************************************************/
TbBOOLEAN  VbCOND_AD_RespAPS1_SlowRec;
TbBOOLEAN  VbCOND_AD_RespAPS_ShortTogether;

/******************************************************************************
 *  Preprocessor Definitions
 *****************************************************************************/
#define CfCOND_TIME_SEC_MAX        ((T_COND_TIME_SEC_0_16 )0xFFFF)
#define GetETCI_Pct_BuffRawAPS_1() (HAL_Analog_Get_PPS1VI_Value()<<1)
#define GetETCI_Pct_BuffRawAPS_2() (HAL_Analog_Get_PPS2VI_Value()<<1)

/******************************************************************************
 *  Local Variable Definitions
 *****************************************************************************/
static TbBOOLEAN             SbCOND_AD_RespFltTypeDsbl;
                            
static TeCOND_AD_RESP_STEPS  SeCOND_AD_RespTestStep;
static TbBOOLEAN             SbCOND_ETC_DoNotUseAPS_Data;
                            
static T_MICROSECONDS        SfCOND_t_APS_ShortToGndTime;
static T_MICROSECONDS        SfCOND_t_APS_NotShortTime;
static T_COND_TIME_SEC_0_16  SfCOND_dt_AD_RespTstIntervalTime;
static T_COND_TIME_SEC_0_16  SfCOND_dt_APS_ShortSettlingTime;
static T_COND_TIME_SEC_0_16  SfCOND_dt_APS_NotShortSettlingTime;
                            
static T_PERCENTa            SfCOND_Pct_APS1_PreShort;
static T_PERCENTa            SfCOND_Pct_APS2_PreShort;
static T_PERCENTa            SfCOND_Pct_APS1_Shorted;
static T_PERCENTa            SfCOND_Pct_APS2_Shorted;
static T_PERCENTa            SfCOND_Pct_APS1_PostShort;
static T_PERCENTa            SfCOND_Pct_APS2_PostShort;
                            
// static TsOBDU_DiagTstData    SsCOND_AD_RespTstData;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN    VbCOND_AD_RespFailed;
TbBOOLEAN    VbCOND_AD_RespTstComplete;
#pragma section DATA " " ".bss"
TbBOOLEAN    VbCOND_AD_RespTested;
TbBOOLEAN    VbCOND_AD_RespEnblCritMet;
TbBOOLEAN    VbCOND_AD_RespFailCritMet;

static T_MICROSECONDS        SfCOND_t_AD_FreeRunningTimerOld;

/*****************************************************************************
*  Local Function Declarations
*****************************************************************************/
static void InitCOND_ADR_CommonZero(void);
static void InitCOND_ADR_CommonNonZero(void);
static T_COND_TIME_SEC_0_16 CalcCOND_AD_RespTimeDelt(T_MICROSECONDS , T_MICROSECONDS);
static TeCOND_AD_RESP_STEPS PerfmCOND_AD_InputRespCntrlTestSteps(void);


/******************************************************************************
 *  Function Definitions
 *****************************************************************************/

/******************************************************************************
 *
 * Function:    InitCOND_ADR_CommonZero
 * Description: This function contains common COND AD Input Response code
 *               for zero-initializations.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void InitCOND_ADR_CommonZero(void)
{
  VbCOND_AD_RespEnblCritMet = CbFALSE;
  SbCOND_AD_RespFltTypeDsbl = CbFALSE;

  SbCOND_ETC_DoNotUseAPS_Data = CbFALSE;

  SfCOND_t_APS_ShortToGndTime        = V_MICROSECONDS(0);
  SfCOND_t_APS_NotShortTime          = V_MICROSECONDS(0);
  SfCOND_dt_APS_ShortSettlingTime    = V_COND_TIME_SEC_0_16(0);
  SfCOND_dt_APS_NotShortSettlingTime = V_COND_TIME_SEC_0_16(0);

  SfCOND_Pct_APS1_PreShort  = V_PERCENTa(0);
  SfCOND_Pct_APS2_PreShort  = V_PERCENTa(0);
  SfCOND_Pct_APS1_Shorted   = V_PERCENTa(0);
  SfCOND_Pct_APS2_Shorted   = V_PERCENTa(0);
  SfCOND_Pct_APS1_PostShort = V_PERCENTa(0);
  SfCOND_Pct_APS2_PostShort = V_PERCENTa(0);

  VbCOND_AD_RespAPS1_SlowRec = CbFALSE;
  VbCOND_AD_RespAPS_ShortTogether = CbFALSE;

  VbCOND_AD_RespTested = CbFALSE;
  VbCOND_AD_RespEnblCritMet = CbFALSE;
  VbCOND_AD_RespFailCritMet = CbFALSE;
}

/******************************************************************************
 *
 * Function:    InitCOND_ADR_CommonNonZero
 * Description: This function contains common COND AD Input Response code
 *               for nonzero-initializations.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void InitCOND_ADR_CommonNonZero(void)
{
  SeCOND_AD_RespTestStep = CeCOND_AD_RESP_STEP_DISABLED;

  SfCOND_dt_AD_RespTstIntervalTime   = CfCOND_TIME_SEC_MAX;

  // SetIO_DiscreteOutputEnable( DISCRETE_OUT_APS1_DIAG );
  // SetIO_DirectDiscreteImmediate( DISCRETE_OUT_APS1_DIAG, CbDISABLED );

  SfCOND_t_AD_FreeRunningTimerOld = HAL_Eng_Get_Sys_Timer();
}

/******************************************************************************
 *
 * Function:    InitCOND_ADR_RstKeyOn
 * Description: This function defines COND AD Input Response
 *               CONTROLLER_RESET_COMPLETE_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void InitCOND_AD_InputRespRstKeyOn(void)
{
  InitCOND_ADR_CommonNonZero();
}

/******************************************************************************
 *
 * Function:    CalcCOND_AD_RespTimeDelt
 * Description: This function calculates time delta.
 *
 * Parameters:
 *     T_MICROSECONDS         LfCOND_t_Time (input)
 *     T_MICROSECONDS         LfCOND_t_TimeOld (input)
 * Return:
 *     T_COND_TIME_SEC_0_16   LfCOND_AD_RespTimeDelt (output)
 *****************************************************************************/
static T_COND_TIME_SEC_0_16 CalcCOND_AD_RespTimeDelt(
                                T_MICROSECONDS LfCOND_t_Time,
                                T_MICROSECONDS LfCOND_t_TimeOld )
{
  T_COND_TIME_SEC_0_16  LfCOND_AD_RespTimeDelt;
  unsigned long         LgCOND_TmpTimeDelt;

  LgCOND_TmpTimeDelt = (unsigned long )LfCOND_t_Time - (unsigned long )LfCOND_t_TimeOld;

  LgCOND_TmpTimeDelt &= 0x0000FFFF;

  LgCOND_TmpTimeDelt = ((1 << S_COND_TIME_SEC_0_16) * LgCOND_TmpTimeDelt) / 1000000;

  LfCOND_AD_RespTimeDelt = (T_COND_TIME_SEC_0_16 )LgCOND_TmpTimeDelt;

  return LfCOND_AD_RespTimeDelt;
}

/*****************************************************************************
 *
 * Function:    EvalCOND_AD_InputRespEnblCritMet
 *
 * Description: This funtion performs the A/D input response diagnostic
 *              enable criteria evaluation.
 *
 * Parameters:  None
 * Return:      TbBOOLEAN  LbCOND_AD_RespEnblCritMet
 ******************************************************************************/
TbBOOLEAN EvalCOND_AD_InputRespEnblCritMet(void)
{
  TbBOOLEAN  LbCOND_AD_RespEnblCritMet;

  if ( (SfCOND_dt_AD_RespTstIntervalTime > KfCOND_t_AD_RespTstInterval)
    && (SeCOND_AD_RespTestStep == CeCOND_AD_RESP_STEP_DISABLED)
    && ( (GetVIOS_IgnSt() == CeIGN_ON)
      && (GetVIOS_U_IgnVolt() > KfCOND_U_AD_RespIgnLoDsbl)
      && (GetVIOS_U_IgnVolt() < KfCOND_U_AD_RespIgnHiDsbl) )
    && (GetETCI_Pct_BuffRawAPS_1() > KfCOND_Pct_AD_RespAPS_PreShortMin)
    && (! GetCOND_MainCPU_ClockTestFailed()) )
  {
    LbCOND_AD_RespEnblCritMet = CbTRUE;
  }
  else if ( SeCOND_AD_RespTestStep != CeCOND_AD_RESP_STEP_DISABLED )
  {
    LbCOND_AD_RespEnblCritMet = CbTRUE;
  }
  else
  {
    LbCOND_AD_RespEnblCritMet = CbFALSE;
  }

  return LbCOND_AD_RespEnblCritMet;
}

/*****************************************************************************
 *
 * Function:    PerfmCOND_AD_InputRespCntrlTestSteps
 *
 * Description: This process performes the steps needed to control
 *              the APS1 short to ground output and collect data without
 *              affecting the operation of the system.
 *
 *              The steps are to collect pre-short APS data, apply the short,
 *              collect shorted APS data, remove the short, and collect
 *              the post-short APS data. It takes 3 7.8 ms loops
 *              to complete the test. If timing works correctly,
 *              the APS data used for control and other diagnostics
 *              will not be affected by this test. If the timing does not work,
 *              the other logic will delay for 1 loop to avoid using
 *              APS data affected by the short to ground.
 *
 * Parameters:  None
 * Return:      TeCOND_AD_RESP_STEPS  LeCOND_AD_RespTestStep
 ******************************************************************************/
static TeCOND_AD_RESP_STEPS PerfmCOND_AD_InputRespCntrlTestSteps(void)
{
  TeCOND_AD_RESP_STEPS  LeCOND_AD_RespTestStep;
  uint32_t context;
  T_MICROSECONDS        LfCOND_t_AD_CnvrsnTime;
  T_MICROSECONDS        LfCOND_t_FreeRunningTmr;
  T_COND_TIME_SEC_0_16  LfCOND_dt_CyclTimeDelt;

  if ( VbCOND_AD_RespEnblCritMet )
  {
    LeCOND_AD_RespTestStep = SeCOND_AD_RespTestStep;

    if ( LeCOND_AD_RespTestStep == CeCOND_AD_RESP_STEP_DISABLED )
    {
      LeCOND_AD_RespTestStep = SeCOND_AD_RespTestStep;

      // SfCOND_Pct_APS1_PreShort = GetIO_Pct_BufferedAnalogValue( AD_PEDAL_POSITION_1 ) >> 1;
      // SfCOND_Pct_APS2_PreShort = GetIO_Pct_BufferedAnalogValue( AD_PEDAL_POSITION_2 ) >> 1;
      SfCOND_Pct_APS1_PreShort = GetETCI_Pct_BuffRawAPS_1();
      SfCOND_Pct_APS2_PreShort = GetETCI_Pct_BuffRawAPS_2();

      // SetIO_DiscreteOutputEnable( DISCRETE_OUT_APS1_DIAG );

      SfCOND_dt_AD_RespTstIntervalTime = V_COND_TIME_SEC_0_16(0);

      SbCOND_ETC_DoNotUseAPS_Data = CbTRUE;

      /* !!Disable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // LgCOND_StatRegrCopy = StartOSTK_CriticalSection();
      context = Enter_Critical_Section();
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

      // SetIO_DirectDiscreteImmediate( DISCRETE_OUT_APS1_DIAG, CbENABLED );
      QADC_Enable_APS1_Diag();
      SfCOND_t_APS_ShortToGndTime = HAL_Eng_Get_Sys_Timer();

      /* !!Enable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // EndOSTK_CriticalSection( LgCOND_StatRegrCopy );
      Leave_Critical_Section(context);
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    }
    else if ( LeCOND_AD_RespTestStep == CeCOND_AD_RESP_STEP_PRE_SHORT )
    {
      LeCOND_AD_RespTestStep  = CeCOND_AD_RESP_STEP_SHORTED;

      /* !!Disable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // LgCOND_StatRegrCopy = StartOSTK_CriticalSection();
      context = Enter_Critical_Section();
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

      // SfCOND_Pct_APS1_Shorted = GetIO_Pct_BufferedAnalogValue( AD_PEDAL_POSITION_1 ) >> 1;
      // SfCOND_Pct_APS2_Shorted = GetIO_Pct_BufferedAnalogValue( AD_PEDAL_POSITION_2 ) >> 1;
      // LfCOND_t_AD_CnvrsnTime  = GetHWIO_AD_CnvrsnTime();
      SfCOND_Pct_APS1_Shorted = GetETCI_Pct_BuffRawAPS_1();
      SfCOND_Pct_APS2_Shorted = GetETCI_Pct_BuffRawAPS_2();
      LfCOND_t_AD_CnvrsnTime = HAL_Eng_Get_Sys_Timer();

      /* !!Enable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // EndOSTK_CriticalSection( LgCOND_StatRegrCopy );
      Leave_Critical_Section(context);
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

      SfCOND_dt_APS_ShortSettlingTime =
                        CalcCOND_AD_RespTimeDelt(
                            LfCOND_t_AD_CnvrsnTime,
                            SfCOND_t_APS_ShortToGndTime );

      /* !!Disable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // LgCOND_StatRegrCopy = StartOSTK_CriticalSection();
      context = Enter_Critical_Section();
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

      // SetIO_DirectDiscreteImmediate( DISCRETE_OUT_APS1_DIAG, CbDISABLED );
      QADC_Disable_APS1_Diag();
      SfCOND_t_APS_NotShortTime = HAL_Eng_Get_Sys_Timer();

      /* !!Enable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // EndOSTK_CriticalSection( LgCOND_StatRegrCopy );
      Leave_Critical_Section(context);
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    }
    else if ( LeCOND_AD_RespTestStep == CeCOND_AD_RESP_STEP_SHORTED )
    {
      LeCOND_AD_RespTestStep    = CeCOND_AD_RESP_STEP_POST_SHORT;

      /* !!Disable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // LgCOND_StatRegrCopy = StartOSTK_CriticalSection();
      context = Enter_Critical_Section();
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

      // SfCOND_Pct_APS1_PostShort = GetIO_Pct_BufferedAnalogValue( AD_PEDAL_POSITION_1 ) >> 1;
      // SfCOND_Pct_APS2_PostShort = GetIO_Pct_BufferedAnalogValue( AD_PEDAL_POSITION_2 ) >> 1;
      // LfCOND_t_AD_CnvrsnTime    = GetHWIO_AD_CnvrsnTime();
      SfCOND_Pct_APS1_PostShort = GetETCI_Pct_BuffRawAPS_1();
      SfCOND_Pct_APS2_PostShort = GetETCI_Pct_BuffRawAPS_2();
      LfCOND_t_AD_CnvrsnTime = HAL_Eng_Get_Sys_Timer();

      /* !!Enable Interrupts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      // EndOSTK_CriticalSection( LgCOND_StatRegrCopy );
      Leave_Critical_Section(context);
      /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

      SfCOND_dt_APS_NotShortSettlingTime =
                        CalcCOND_AD_RespTimeDelt(
                            LfCOND_t_AD_CnvrsnTime,
                            SfCOND_t_APS_NotShortTime );

      // SetIO_DirectDiscreteImmediate( DISCRETE_OUT_APS1_DIAG, CbDISABLED );
      QADC_Disable_APS1_Diag();
    }
    else /* Post short or illegal value */
    {
      LeCOND_AD_RespTestStep = CeCOND_AD_RESP_STEP_DISABLED;

      // SetIO_DirectDiscreteImmediate( DISCRETE_OUT_APS1_DIAG, CbDISABLED );
      QADC_Disable_APS1_Diag();
    }
  }
  else /* not enabled */
  {
    LeCOND_AD_RespTestStep = SeCOND_AD_RespTestStep; // keep the old value

    // SetIO_DirectDiscreteImmediate( DISCRETE_OUT_APS1_DIAG, CbDISABLED );
    QADC_Disable_APS1_Diag();
  }

  LfCOND_t_FreeRunningTmr = HAL_Eng_Get_Sys_Timer();

  LfCOND_dt_CyclTimeDelt =
                    CalcCOND_AD_RespTimeDelt(
                        LfCOND_t_FreeRunningTmr,
                        SfCOND_t_AD_FreeRunningTimerOld );

  SfCOND_dt_AD_RespTstIntervalTime = SfCOND_dt_AD_RespTstIntervalTime + LfCOND_dt_CyclTimeDelt;

  SfCOND_t_AD_FreeRunningTimerOld = LfCOND_t_FreeRunningTmr;

  return LeCOND_AD_RespTestStep;
}

/*****************************************************************************
 *
 * Function:    EvalCOND_AD_InputRespTestData
 *
 * Description: This process evaluates the data recorded during the APS1
 *              short to ground applied by the A/D input response diagnostic.
 *
 *              Three specific responses are checked
 *               when the test step is "post-short":
 *
 *              1) APS1 when shorted is lower than the short threshold.
 *                 Sets fail criteria met unless settling time is too short.
 *                 If this fails, the A/D converter could be stuck.
 *              2) APS1 slow to recover from short to ground.
 *                 Sets slow recovery flag if value of APS1 after short
 *                 is removed is more than a cal lower than the pre short value
 *                 and the change in APS2 value is less than a cal.
 *                 If this fails, there could be a high source resistance
 *                 in the accel pedal sensor. The flag is passed
 *                 to the APS1 out of range diagnostic.
 *              3) APS2 changing value while APS1 is shorted to ground.
 *                 Sets APS shorted together flag if APS2
 *                 value drops when APS1 is shorted and increases
 *                 when the short is removed. The flag is passed
 *                 to the APS correlation diagnostic for consideration
 *                 as a correlation error.
 *
 * Parameters:  TbBOOLEAN  *LpCOND_RespFailCritMet (output)
 * Return:      TbBOOLEAN   LbCOND_SkipDiagTst
 ******************************************************************************/
TbBOOLEAN  EvalCOND_AD_InputRespTestData(
                            TbBOOLEAN  *LpCOND_RespFailCritMet )
{
  TbBOOLEAN  LbCOND_RespFailCritMet;
  TbBOOLEAN  LbCOND_SkipDiagTst;

  /* execution of the function only in case                   */
  /* SeCOND_AD_RespTestStep == CeCOND_AD_RESP_STEP_POST_SHORT */

  if ( SfCOND_Pct_APS1_Shorted < KfCOND_Pct_AD_RespAPS_ShortedMax )
  {
    LbCOND_RespFailCritMet = CbFALSE;
    LbCOND_SkipDiagTst     = CbFALSE;
  }
  else if ( SfCOND_dt_APS_ShortSettlingTime > KfCOND_t_AD_RespShortSettleMin )
  {
    LbCOND_RespFailCritMet = CbTRUE;
    LbCOND_SkipDiagTst     = CbFALSE;
  }
  else
  {
    LbCOND_RespFailCritMet = CbFALSE;
    LbCOND_SkipDiagTst     = CbTRUE;
  }

  if (  FixSubAbs(SfCOND_Pct_APS1_PreShort, KfCOND_Pct_AD_RespRecDeltaAPS1_Max, T_PERCENTa) < SfCOND_Pct_APS1_PostShort )
  {
    VbCOND_AD_RespAPS1_SlowRec = CbFALSE;
  }
  else if (( FixSubAbs(SfCOND_Pct_APS2_PostShort,SfCOND_Pct_APS2_PreShort,T_PERCENTa) < KfCOND_Pct_AD_RespRecDeltaAPS2_Max)
         && (SfCOND_dt_APS_NotShortSettlingTime > KfCOND_t_AD_RespRecSettleMin) )
  {
    VbCOND_AD_RespAPS1_SlowRec = CbTRUE;
  }
  else
  {
    VbCOND_AD_RespAPS1_SlowRec = CbFALSE;
  }

  if ( (FixSubAbs(SfCOND_Pct_APS2_PreShort, SfCOND_Pct_APS2_Shorted, T_PERCENTa) > KfCOND_Pct_AD_RespDeltaAPS2_Max)
    && (FixSubAbs(SfCOND_Pct_APS2_PostShort, SfCOND_Pct_APS2_Shorted, T_PERCENTa) > KfCOND_Pct_AD_RespDeltaAPS2_Max) )
  {
    VbCOND_AD_RespAPS_ShortTogether = CbTRUE;
  }
  else
  {
    VbCOND_AD_RespAPS_ShortTogether = CbFALSE;
  }

  *LpCOND_RespFailCritMet = LbCOND_RespFailCritMet;

  return LbCOND_SkipDiagTst;
}

/*****************************************************************************
 * Function:     MngCOND_AD_InputResp15p6msTasksA
 *
 * Description:  This process will execute the first group of 15.6 ms
 *               COND A/D input response diagnostic tasks.
 *
 * Parameters:   None
 * Return:       None
 ******************************************************************************/
void MngCOND_AD_InputResp15p6msTasksA(void)
{
  TbBOOLEAN  LbCOND_TstRstCondsMet;
  TbBOOLEAN  LbCOND_SkipDiagTst;
  TbBOOLEAN  LbCOND_FailCritMet;

    VbCOND_AD_RespEnblCritMet = EvalCOND_AD_InputRespEnblCritMet();

    SeCOND_AD_RespTestStep = PerfmCOND_AD_InputRespCntrlTestSteps();

    if ( VbCOND_AD_RespEnblCritMet
      && (SeCOND_AD_RespTestStep == CeCOND_AD_RESP_STEP_POST_SHORT) )
    {
      LbCOND_SkipDiagTst =
                    EvalCOND_AD_InputRespTestData(
                        &LbCOND_FailCritMet );

      VbCOND_AD_RespFailCritMet = LbCOND_FailCritMet;

      // if ( ! LbCOND_SkipDiagTst )
      // {
        // if ( GetVIOS_EngSt_PwrOffDly()
          // && (GetVIOS_PwrdownDelayTimer() > KfCOND_t_PwrDwnClr) )
        // {
          // LbCOND_TstRstCondsMet = CbTRUE;
        // }
        // else
        // {
          // LbCOND_TstRstCondsMet = CbFALSE;
        // }

        // ExecOBDU_UpdtEvalRprtDiagTst(
                      // CeDGDM_COND_AD_InputResp,
                      // LbCOND_TstRstCondsMet,
                      // &KsCOND_AD_RespTstCals,
                      // &SsCOND_AD_RespTstData );
      // }
      /* skip the diagnostic part */
    }
    /* else do nothing */
}

/*****************************************************************************
 * Function:     MngCOND_AD_InputResp15p6msTasksB
 *
 * Description:  This process will execute the second group of 15.6 ms
 *               COND A/D input response diagnostic tasks.
 *
 * Parameters:   None
 * Return:       None
 ******************************************************************************/
void MngCOND_AD_InputResp15p6msTasksB(void)
{
  if ( ! SbCOND_AD_RespFltTypeDsbl )
  {
    SeCOND_AD_RespTestStep = PerfmCOND_AD_InputRespCntrlTestSteps();
  }
  /* else do nothing */
}

/*****************************************************************************
 * Function:     GetCOND_AD_RespTstFld
 *
 * Description:  This function returns the A/D input response diagnostic
 *               test failed flag.
 *
 * Parameters:   None
 * Return:       SsCOND_AD_RespTstData.TstFailed
 ******************************************************************************/
TbBOOLEAN  GetCOND_AD_RespTstFld(void)
{
  return (TbBOOLEAN)VbCOND_AD_RespFailed;
}

/*****************************************************************************
 * Function:     GetCOND_AD_RespETC_LrnDwnDsblCritMet
 *
 * Description:  This function returns the A/D input response diagnostic
 *               ETC learing down disable criteria met flag.
 *
 * Parameters:   T_COND_TIME_SEC_0_16 LfCOND_t_ETC_APS_MinLrnDsblDly (input)
 * Return:       LbCOND_ETC_LrnDwnDsblCritMet
 ******************************************************************************/
TbBOOLEAN  GetCOND_AD_RespETC_LrnDwnDsblCritMet(
                       const T_COND_TIME_SEC_0_16 LfCOND_t_ETC_APS_MinLrnDsblDly )
{
  TbBOOLEAN  LbCOND_ETC_LrnDwnDsblCritMet;

  if ( (SeCOND_AD_RespTestStep == CeCOND_AD_RESP_STEP_DISABLED)
    && (SfCOND_dt_AD_RespTstIntervalTime > LfCOND_t_ETC_APS_MinLrnDsblDly))
    // && (! GetCOND_AD_RespTstFld())
    // && (! GetCOND_AD_RespAPS1_SlowRec())
    // && (! GetCOND_AD_RespAPS_ShortTogether()) )
  {
    LbCOND_ETC_LrnDwnDsblCritMet = CbFALSE;
  }
  else
  {
    LbCOND_ETC_LrnDwnDsblCritMet = CbTRUE;
  }

  return LbCOND_ETC_LrnDwnDsblCritMet;
}

/*****************************************************************************
 * Function:     GetCOND_AD_RespETC_DoNotUseAPS_Data
 *
 * Description:  This function returns the A/D input response diagnostic
 *               do not use APS data flag for ETC subsystem.
 *               Be aware that this code may be executed within interrupt
 *               critical section.
 *
 * Parameters:   T_COND_TIME_SEC_0_16 LfCOND_t_ETC_NotShortSettleMin (input)
 * Return:       SbCOND_ETC_DoNotUseAPS_Data
 ******************************************************************************/
TbBOOLEAN  GetCOND_AD_RespETC_DoNotUseAPS_Data(void)
{
  T_COND_TIME_SEC_0_16  LfCOND_dt_APS_TimeSinceShortRemoved;

  if ( SbCOND_ETC_DoNotUseAPS_Data
    && (SeCOND_AD_RespTestStep != CeCOND_AD_RESP_STEP_PRE_SHORT) )
  {
    LfCOND_dt_APS_TimeSinceShortRemoved =
                CalcCOND_AD_RespTimeDelt(
                    HAL_Eng_Get_Sys_Timer(),
                    SfCOND_t_APS_NotShortTime );

    if ( LfCOND_dt_APS_TimeSinceShortRemoved
       > KfETCI_t_AD_NotShortSettleMin )
    {
      SbCOND_ETC_DoNotUseAPS_Data = CbFALSE;
    }
  }

  return SbCOND_ETC_DoNotUseAPS_Data;
}

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
