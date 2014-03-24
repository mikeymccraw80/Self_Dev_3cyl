/******************************************************************************
 *
 * Filename:          condmcpu.c
 *
 * Description:       This file contains the Controller Diagnostic algorithm
 *                    for CPU checking.
 *
 * Global Functions Defined:
 *                    PerformCOND_CheckCPU_ResetKeyOn
 *                    PerformCOND_CheckCPU_PwrdnDlyToKeyOn
 *                    PerformCOND_CheckCPU_ShutDnToKeyOn
 *                    PerformCOND_CheckCPU_OFVC_Clear
 *                    MngCOND_CheckCPU_15p6Tasks
 *                    MngCOND_CheckCPU_31p2Tasks
 *                    MngCOND_CheckCPU_125Tasks
 * Static Functions Defined:
 *                    DtrmnCOND_CPU_DiagFaultPresent
 *                    PerformCOND_CPU_ReInitOfCommsWithPIC
 *                    DtrmnCOND_CPU_PIC_CommsVltgStabInitDelay
 *                    PerformCOND_CPU_PIC_DataProcessing
 *                    DtrmnCOND_CPU_PIC_ProblemDetected
 *                    PerformCOND_CheckCPU_PIC_ResetKeyOn
 *                    PerformCOND_CheckCPU_PIC_PwrdnDlyToKeyOn
 *                    PerformCOND_CheckCPU_PIC_ShutDnToKeyOn
 *                    PerformCOND_CheckCPU_PIC_OFVC_Clear
 *                    PerformCOND_CPU_SOH_DataProcessing
 *                    DtrmnCOND_CPU_SOH_ProblemDetected
 *                    InitCOND_CheckCPU_SOH_CommonZero
 *                    PerformCOND_CheckCPU_SOH_ResetKeyOn
 *                    PerformCOND_CheckCPU_SOH_PwrdnDlyToKeyOn
 *                    PerformCOND_CheckCPU_SOH_ShutDnToKeyOn
 *                    PerformCOND_CheckCPU_SOH_OFVC_Clear
 * Inline Functions Defined:
 *                    InitCOND_CheckCPU_SOH_CommonNonZero
 *
 * Forward Engine Management Systems
 *
 * Copyright 2004-2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#3/csrc/condmcpu.c/4 %
 * %date_created:  Wed Feb 21 10:40:51 2007 %
 * %version:       4.1.2 %
 * %derived_by:    pzb6v4 %
 *
 *****************************************************************************/

/*****************************************************************************
*  Include Files                                                            *
****************************************************************************/
#include "condfcfg.h"   /* For COND Local Configuration       */

#if XeCOND_ETC_CHECKING_CPU_TYPE != CeCOND_ETC_CHECKING_CPU_IS_NONE

#include "condfexi.h"   /* For global inputs                  */
#include "condcald.h"   /* For local calibration declarations */
#include "condpapi.h"   /* For Definition-Declaration check   */
#include "condstyp.h"   /* For local type definitions         */
#include "condptyp.h"   /* For global type definitions        */
#include "condnvmd.h"   /* For local NVM declarations         */
#include "soh.h"        /* For SOH_ETC_Clear_Fault_Log()      */

/**********************************************************************/
/* Private Macro and Constant Definitions                             */
/**********************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
 #define CcCOND_cnt_SU_BattVltgStblDelay V_COUNT_WORD(0x60)
#endif

/**********************************************************************/
/* Global Variable Definitions                                        */
/**********************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
TbBOOLEAN                VOL0ADDR VbCOND_MainCPU_FltByCheckTstFld;
TbBOOLEAN                VOL0ADDR VbCOND_MainCPU_FltByCheckTstCmp;
TbBOOLEAN                VOL0ADDR VbCOND_CheckCPU_FltByMainTstFld;
TbBOOLEAN                VOL0ADDR VbCOND_CheckCPU_FltByMainTstCmp;
TeSINGLE_TEST_STATUS     VOL0ADDR VeCOND_MainCPU_FltByCkTstStRpt;
TeSINGLE_TEST_STATUS     VOL0ADDR VeCOND_CheckCPU_FltByMnTstStRpt;
TsCOND_CheckCPU_Status   VOL0ADDR VsCOND_CheckCPU_Status;
TeCOND_CHECKCPU_OPSTATUS VOL0ADDR VeCOND_CheckCPU_OpStatus;
#endif

/**********************************************************************/
/* Private Variable Definitions                                        */
/**********************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
static T_COUNT_WORD          VOL0ADDR ScCOND_SU_BattVltgStabilizedCntr;
#elif XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_MainCPU_Flt;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_CommFlt;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_CheckingCPU_Flt;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_FltPrsnt;

static TbBOOLEAN             VOL0ADDR SbCOND_SOH_MainCPU_TstFld;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_MainCPU_TstCmp;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_CommTstFld;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_CommTstCmp;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_CheckingCPU_TstFld;
static TbBOOLEAN             VOL0ADDR SbCOND_SOH_CheckingCPU_TstCmp;

static TeSINGLE_TEST_STATUS  VOL0ADDR SeCOND_SOH_MainCPU_TstStRpt;
static TeSINGLE_TEST_STATUS  VOL0ADDR SeCOND_SOH_CommTstStRpt;
static TeSINGLE_TEST_STATUS  VOL0ADDR SeCOND_SOH_CheckingCPU_TstStRpt;
#endif

/**********************************************************************/
/* Private Variable Definitions                                       */
/**********************************************************************/

/**********************************************************************/
/* Private Constant Definitions                                       */
/**********************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
/* Desired Reset to KeyOn clear status of flags */
static const TsCOND_CheckCPU_Status CsCOND_CheckCPU_ResetToKeyOnStatusFlags =
 {CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE,
  CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE,
  CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbTRUE };

 /* MASK for flags when OFVC clear Init */
static const TsCOND_CheckCPU_Status CsCOND_CheckCPU_OFVC_ClearStatusFlags =
 {CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE,
  CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE,
  CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbTRUE };


/* MASK for flags when power down delay  criteria met */
static const TsCOND_CheckCPU_Status CsCOND_CheckCPU_PwrDnMaskOfStatusFlags =
 {CbTRUE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE,
  CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE,
  CbFALSE, CbFALSE, CbFALSE, CbTRUE, CbTRUE };

/* MASK for flags when transition from normal to Init message */
static const TsCOND_CheckCPU_Status CsCOND_CheckCPU_FromNormalToInitMsgStatusFlags =
{
  CbTRUE,  CbTRUE,  CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE,
  CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbFALSE, CbTRUE,
  CbTRUE,  CbTRUE,  CbTRUE,  CbTRUE, CbTRUE };
#endif

/**********************************************************************/
/* Private Function Declarations                                      */
/**********************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
static void PerformCOND_CPU_PIC_DataProcessing(void);
static void DtrmnCOND_CPU_PIC_ProblemDetected(void);
static void PerformCOND_CPU_ReInitOfCommsWithPIC(void);
static void DtrmnCOND_CPU_PIC_CommsVltgStabInitDelay(void);
#endif

/**********************************************************************/
/* Function Definitions                                               */
/**********************************************************************/

/******************************************************************************
 *
 * Function:    DtrmnCOND_CPU_DiagFaultPresent
 * Description: This function performs common diagnostic reporting
 *               for all CPU faults.
 *
 * Parameters:  TbBOOLEAN               *LbCOND_CPU_FltByCheckTstFld (input/output)
 *              TbBOOLEAN               *LbCOND_CPU_FltByCheckTstCmp (output)
 *              TeSINGLE_TEST_STATUS    *LbCOND_CPU_FltByCkTstStRpt (output)
 *              TbBOOLEAN               LbCOND_CPU_FaultFlag (input)
 *              TeDGDM_DIAGNOSTIC_TESTS LeCOND_CPU_DTC (input)
 * Return:      None
 *****************************************************************************/
static void DtrmnCOND_CPU_DiagFaultPresent(
                          TbBOOLEAN               *LbCOND_CPU_FltByCheckTstFld,
                          TbBOOLEAN               *LbCOND_CPU_FltByCheckTstCmp,
                          TeSINGLE_TEST_STATUS    *LbCOND_CPU_FltByCkTstStRpt,
                          TbBOOLEAN               LbCOND_CPU_FaultFlag,
                          TeDGDM_DIAGNOSTIC_TESTS LeCOND_CPU_DTC)
{
  if ( (!(*LbCOND_CPU_FltByCheckTstFld))
     &&(LbCOND_CPU_FaultFlag) )
  {
    *LbCOND_CPU_FltByCheckTstFld = CbTRUE;
    *LbCOND_CPU_FltByCheckTstCmp = CbTRUE;
  }
  else if (GetVIOS_t_EngRunTime() > GetETCD_t_PassReportThresh())
  {
    *LbCOND_CPU_FltByCheckTstCmp = CbTRUE;
  }

  if ( *LbCOND_CPU_FltByCheckTstCmp )
  {
    if ( (CeSINGLE_FAIL != *LbCOND_CPU_FltByCkTstStRpt)
       &&(*LbCOND_CPU_FltByCheckTstFld) )
    {
      PerfmDGDM_ProcessFailReport(LeCOND_CPU_DTC);
      *LbCOND_CPU_FltByCkTstStRpt = CeSINGLE_FAIL;
    }
    else if ( (CeSINGLE_PASS != *LbCOND_CPU_FltByCkTstStRpt)
            &&(!(*LbCOND_CPU_FltByCheckTstFld)) )
    {
      PerfmDGDM_ProcessPassReport(LeCOND_CPU_DTC);
      *LbCOND_CPU_FltByCkTstStRpt = CeSINGLE_PASS;
    }
    /* else do nothing */
  }
  /* else do nothing - test not complete */
}

#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
/******************************************************************************
 * Function:    PerformCOND_CPU_ReInitOfCommsWithPIC                          *
 *                                                                            *
 * Description: This function performs PIC communications intialization, if   *
 *              required.                                                     *
 *                                                                            *
 * Parameters:  None                                                          *
 *                                                                            *
 * Return:      None                                                          *
 *                                                                            *
 ******************************************************************************/
static void PerformCOND_CPU_ReInitOfCommsWithPIC(void)
{
  if ( (ScCOND_SU_BattVltgStabilizedCntr < CcCOND_cnt_SU_BattVltgStblDelay)
     &&( (VsCOND_CheckCPU_Status.flags.VbCOND_PIC_MsgError)
       ||(GetCOND_MainToWD_SoftwareVerFailCritMet()) )
     &&(!VsCOND_CheckCPU_Status.flags.VbCOND_CommsReinitPending) )
  {
    SetHWIO_ETC_Check_Reinitialize();
    VsCOND_CheckCPU_Status.flags.VbCOND_CommsReinitPending = CbTRUE;
    VsCOND_CheckCPU_Status.flags.VbCOND_InitMsgRcvdPrev = CbFALSE;
  }
  else if (VsCOND_CheckCPU_Status.flags.VbCOND_PIC_InitMsg)
  {
    VsCOND_CheckCPU_Status.flags.VbCOND_CommsReinitPending = CbFALSE;
  }
}

/******************************************************************************
 * Function:    DtrmnCOND_CPU_PIC_CommsVltgStabInitDelay                      *
 *                                                                            *
 * Description: This function determine if the delay for voltage stability    *
 *              for Main CPU and PIC communications fault acknowledgement is  *
 *              complete.                                                     *
 *                                                                            *
 * Parameters:  None                                                          *
 *                                                                            *
 * Return:      None                                                          *
 *                                                                            *
 ******************************************************************************/
static void DtrmnCOND_CPU_PIC_CommsVltgStabInitDelay(void)
{
  VsCOND_CheckCPU_Status.flags.VbCOND_SU_BatVltgStabDelayActv =
         (ScCOND_SU_BattVltgStabilizedCntr <= CcCOND_cnt_SU_BattVltgStblDelay);
  if (VsCOND_CheckCPU_Status.flags.VbCOND_SU_BatVltgStabDelayActv)
  {
    ScCOND_SU_BattVltgStabilizedCntr = INCusp(ScCOND_SU_BattVltgStabilizedCntr);
  }
}

/******************************************************************************
 *
 * Function:    PerformCOND_CPU_PIC_DataProcessing
 * Description: This function checks the CPU and PIC communication flags.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CPU_PIC_DataProcessing(void)
{
  TbBOOLEAN              LbCOND_CheckCPU_RcvMsgError;
  TbBOOLEAN              LbCOND_NoDelayCommFaultByMain;
  LONGWORD               LgCOND_CheckCPU_LastMsgRcvd;
  LONGWORD               LgCOND_CheckCPU_StatusRegisterCopy;
  TsCOND_CheckCPU_Status LsCOND_CheckCPU_TempStatus;

  /*--- Disable interrupts "Atomic Section" from background      ---*/
  LgCOND_CheckCPU_StatusRegisterCopy = StartOSTK_CriticalSection();

  /*
   * Get copy of flags at start, previous flags represent current working state
   * to be saved at end of loop
   */
  LsCOND_CheckCPU_TempStatus.data = VsCOND_CheckCPU_Status.data;
  if ( (GetVIOS_EngSt_PwrOffDly())
     &&(GetHWIO_ControllerVersion() != CeHWIO_MT38_PROTO_B)
     &&(GetVIOS_PwrdownDelayTimer() > KfCOND_t_PwrDwnClr) )
  {
    /* MASK structure that clears all flags except VbCOND_InitMsgRcvdPrev */
    LsCOND_CheckCPU_TempStatus.data &= CsCOND_CheckCPU_PwrDnMaskOfStatusFlags.data;
    SetIO_PIC_Rx_Faulted(CbFALSE);
  }

  if ( (GetIO_PIC_Msg_Ready())
     &&(GetHWIO_ControllerVersion() != CeHWIO_MT38_PROTO_B) )
  {
    /* These flags should be set to False at the start of the loop */
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_LastNormPIC_MsgOK   = CbFALSE;
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_MsgError        = CbFALSE;
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_DisabledOutputsPrev = CbFALSE;
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_PauseSeqFaultPrev   = CbFALSE;
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_ShutTmrPrev         = CbFALSE;
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByPIC_Prev = CbFALSE;
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_PWM_FaultPrev       = CbFALSE;
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_PICLK_FaultPrev     = CbFALSE;

    LbCOND_CheckCPU_RcvMsgError = GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_RECEIVE_ERROR);
    LgCOND_CheckCPU_LastMsgRcvd = GetIO_PIC_Last_Message_Rcvd();
    LsCOND_CheckCPU_TempStatus.flags.VbCOND_InitMsgRcvdPrev = GetIO_PIC_Init_Msg_Rcvd();

    LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_InitMsg =
           ( (!VsCOND_CheckCPU_Status.flags.VbCOND_InitMsgRcvdPrev)
           &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_InitMsgRcvdPrev) );
    if (LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_InitMsg) /* Init */
    {
      LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByMainPrev =
        GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_RX_CHECKSUM_ERROR);
      if (LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByMainPrev)
      {
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_MsgError = CbTRUE;
        NcCOND_CPU_InitMsgBadCount = INCusp(NcCOND_CPU_InitMsgBadCount);
      }
      LsCOND_CheckCPU_TempStatus.data &= CsCOND_CheckCPU_FromNormalToInitMsgStatusFlags.data;
    }
    else /* Normal */
    {
      LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_InitMsg = CbFALSE;
      LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByMainPrev =
        ( (GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_RX_CHECKSUM_ERROR))
        ||(GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_RX_INVALID_ERROR)) );
      if (!LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByMainPrev)
      {
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_DisabledOutputsPrev =
          GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_DISABLED_OUTPUTS);
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_PauseSeqFaultPrev   =
          GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_PAUSE_SEQUENCE_ERROR);
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_ShutTmrPrev         =
          GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_SHUTOFF_TIMER_ACTIVE);
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByPIC_Prev =
          GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_TRANSMIT_ERROR);
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_PWM_FaultPrev       =
          GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_PWM_ERROR);
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_PICLK_FaultPrev     =
          GetHWIO_ETC_Check_Fault_Active(HWIO_ETC_CHECK_PICLK_ERROR);

        if (!VsCOND_CheckCPU_Status.flags.VbCOND_SU_BatVltgStabDelayActv)
        {
          LsCOND_CheckCPU_TempStatus.flags.VbCOND_DisabledOutputs |=
            ( (VsCOND_CheckCPU_Status.flags.VbCOND_DisabledOutputsPrev)
            &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_DisabledOutputsPrev) );

          LsCOND_CheckCPU_TempStatus.flags.VbCOND_PauseSeqFault |=
            ( (VsCOND_CheckCPU_Status.flags.VbCOND_PauseSeqFaultPrev)
            &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_PauseSeqFaultPrev) );

          LsCOND_CheckCPU_TempStatus.flags.VbCOND_ShutTmr |=
            ( (VsCOND_CheckCPU_Status.flags.VbCOND_ShutTmrPrev)
            &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_ShutTmrPrev) );

          LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByPIC |=
            ( (VsCOND_CheckCPU_Status.flags.VbCOND_CommFaultByPIC_Prev)
            &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByPIC_Prev) );

          LsCOND_CheckCPU_TempStatus.flags.VbCOND_PWM_Fault |=
            ( (VsCOND_CheckCPU_Status.flags.VbCOND_PWM_FaultPrev)
            &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_PWM_FaultPrev) );

          LsCOND_CheckCPU_TempStatus.flags.VbCOND_PICLK_Fault |=
            ( (VsCOND_CheckCPU_Status.flags.VbCOND_PICLK_FaultPrev)
            &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_PICLK_FaultPrev) );
        }

        if ( (!LsCOND_CheckCPU_TempStatus.flags.VbCOND_DisabledOutputsPrev)
           &&(!LsCOND_CheckCPU_TempStatus.flags.VbCOND_PauseSeqFaultPrev)
           &&(!LsCOND_CheckCPU_TempStatus.flags.VbCOND_ShutTmrPrev)
           &&(!LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByPIC_Prev)
           &&(!LsCOND_CheckCPU_TempStatus.flags.VbCOND_PWM_FaultPrev)
           &&(!LsCOND_CheckCPU_TempStatus.flags.VbCOND_PICLK_FaultPrev) )
        {
          LsCOND_CheckCPU_TempStatus.flags.VbCOND_LastNormPIC_MsgOK = CbTRUE;
        }
        else
        {
          LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_MsgError = CbTRUE;
          NcCOND_CPU_NormMsgBadCount = INCusp(NcCOND_CPU_NormMsgBadCount);
        }
      }
      else
      {
        LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_MsgError = CbTRUE;
        NcCOND_CPU_NormMsgBadCount = INCusp(NcCOND_CPU_NormMsgBadCount);
      }
    }

    LbCOND_NoDelayCommFaultByMain =
       ( ( (LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByMainPrev)
         &&(VsCOND_CheckCPU_Status.flags.VbCOND_CommFaultByMainPrev) )
       ||(LbCOND_CheckCPU_RcvMsgError) );
    if ( (!VsCOND_CheckCPU_Status.flags.VbCOND_SU_BatVltgStabDelayActv)
       &&(LbCOND_NoDelayCommFaultByMain) )
    {
      LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByMain = CbTRUE;
    }

    if ( ( (LsCOND_CheckCPU_TempStatus.flags.VbCOND_DisabledOutputs)
         ||(LsCOND_CheckCPU_TempStatus.flags.VbCOND_CommFaultByMain) )
       &&(!NbCOND_CPU_OutputDsbldSinceNVM_Clear) )
    {
      NgCOND_CPU_MsgRcvWhenOutputDsbld     = LgCOND_CheckCPU_LastMsgRcvd;
      NbCOND_CPU_OutputDsbldSinceNVM_Clear = CbTRUE;
    }

    if ( ( (VsCOND_CheckCPU_Status.flags.VbCOND_DisabledOutputsPrev)
         &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_DisabledOutputsPrev) )
       ||(LbCOND_NoDelayCommFaultByMain) )
    {
      VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_FAIL;
    }
    else if ( (VsCOND_CheckCPU_Status.flags.VbCOND_LastNormPIC_MsgOK)
            &&(LsCOND_CheckCPU_TempStatus.flags.VbCOND_LastNormPIC_MsgOK) )
    {
      VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_OK;
    }
    else if (LsCOND_CheckCPU_TempStatus.flags.VbCOND_PIC_MsgError)
    {
      VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_PENDING;
    }
  }
  /* Update flags with final values from temporary copy */
  VsCOND_CheckCPU_Status.data = LsCOND_CheckCPU_TempStatus.data;
  /* Yes, I meant to put this here */
  /*--- Enable interrupts "Atomic Section Complete"          ---*/
  EndOSTK_CriticalSection(LgCOND_CheckCPU_StatusRegisterCopy);
}

/******************************************************************************
 *
 * Function:    DtrmnCOND_CPU_PIC_ProblemDetected
 * Description: This function performs CPU PIC faults determinations.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void DtrmnCOND_CPU_PIC_ProblemDetected(void)
{
  if ( (GetVIOS_EngSt_PwrOffDly())
     &&(GetVIOS_PwrdownDelayTimer() > KfCOND_t_PwrDwnClr) )
  {
    VbCOND_MainCPU_FltByCheckTstFld = CbFALSE;
    VbCOND_MainCPU_FltByCheckTstCmp = CbFALSE;
    VbCOND_CheckCPU_FltByMainTstFld = CbFALSE;
    VbCOND_CheckCPU_FltByMainTstCmp = CbFALSE;
  }

  if (GetDGDM_DTC_FaultType(CeDGDM_COND_MainCPU_ByCheck) != CeDGDM_FAULT_TYPE_Z)
  {
    DtrmnCOND_CPU_DiagFaultPresent(&VbCOND_MainCPU_FltByCheckTstFld,
                                   &VbCOND_MainCPU_FltByCheckTstCmp,
                                   &VeCOND_MainCPU_FltByCkTstStRpt,
                                   VsCOND_CheckCPU_Status.flags.VbCOND_DisabledOutputs,
                                   CeDGDM_COND_MainCPU_ByCheck);
  }

  if (GetDGDM_DTC_FaultType(CeDGDM_COND_CheckCPU_ByMain) != CeDGDM_FAULT_TYPE_Z)
  {
    DtrmnCOND_CPU_DiagFaultPresent(&VbCOND_CheckCPU_FltByMainTstFld,
                                   &VbCOND_CheckCPU_FltByMainTstCmp,
                                   &VeCOND_CheckCPU_FltByMnTstStRpt,
                                   VsCOND_CheckCPU_Status.flags.VbCOND_CommFaultByMain,
                                   CeDGDM_COND_CheckCPU_ByMain);
  }
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_PIC_ResetKeyOn
 * Description: This function defines COND CheckCPU PIC
 *              CONTROLLER_RESET_COMPLETE_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_PIC_ResetKeyOn(void)
{
  if (GetFILE_NVM_LTM_Failure())
  {
    NcCOND_CPU_InitMsgBadCount = V_COUNT_WORD(0);
    NcCOND_CPU_NormMsgBadCount = V_COUNT_WORD(0);
    NgCOND_CPU_MsgRcvWhenOutputDsbld = 0;
  }

  if (GetFILE_NVM_Failure())
  {
    NbCOND_CPU_OutputDsbldSinceNVM_Clear = CbFALSE;
  }

#if XeSYST_RAM_CLEAR == CeSYST_RAM_CLEAR_UNAVAILABLE
  VsCOND_CheckCPU_Status.data = CsCOND_CheckCPU_ResetToKeyOnStatusFlags.data;
  VbCOND_MainCPU_FltByCheckTstFld = CbFALSE;
  VbCOND_MainCPU_FltByCheckTstCmp = CbFALSE;
  VeCOND_MainCPU_FltByCkTstStRpt  = CeSINGLE_NULL;
  VbCOND_CheckCPU_FltByMainTstFld = CbFALSE;
  VbCOND_CheckCPU_FltByMainTstCmp = CbFALSE;
  VeCOND_CheckCPU_FltByMnTstStRpt = CeSINGLE_NULL;
#endif
  SetHWIO_ETC_Check_Reinitialize(); /* Initialize PIC interfaces */
  ScCOND_SU_BattVltgStabilizedCntr = V_COUNT_WORD(0);

  if ( GetHWIO_ControllerVersion() != CeHWIO_MT38_PROTO_B )
  {
     VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_PENDING;
  }
  else
  {
     VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_OK;
  }
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_PIC_PwrdnDlyToKeyOn
 * Description: This function defines COND CheckCPU PIC
 *              POWER_OFF_DELAY_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_PIC_PwrdnDlyToKeyOn(void)
{
  SetHWIO_ETC_Check_Reinitialize(); /* Initialize PIC interfaces */
  ScCOND_SU_BattVltgStabilizedCntr = V_COUNT_WORD(0);
  VsCOND_CheckCPU_Status.flags.VbCOND_SU_BatVltgStabDelayActv = CbTRUE;
  VsCOND_CheckCPU_Status.flags.VbCOND_CommsReinitPending = CbFALSE;
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_PIC_ShutDnToKeyOn
 * Description: This function defines COND CheckCPU PIC
 *              SHUTDOWN_IN_PROGRESS_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_PIC_ShutDnToKeyOn(void)
{
  VbCOND_MainCPU_FltByCheckTstFld = CbFALSE;
  VbCOND_MainCPU_FltByCheckTstCmp = CbFALSE;
  VeCOND_MainCPU_FltByCkTstStRpt = CeSINGLE_NULL;
  VbCOND_CheckCPU_FltByMainTstFld = CbFALSE;
  VbCOND_CheckCPU_FltByMainTstCmp = CbFALSE;
  VeCOND_CheckCPU_FltByMnTstStRpt = CeSINGLE_NULL;
  SetHWIO_ETC_Check_Reinitialize(); /* Initialize PIC interfaces */
  ScCOND_SU_BattVltgStabilizedCntr = V_COUNT_WORD(0);
  VsCOND_CheckCPU_Status.flags.VbCOND_SU_BatVltgStabDelayActv = CbTRUE;
  VsCOND_CheckCPU_Status.flags.VbCOND_CommsReinitPending = CbFALSE;

  if ( GetHWIO_ControllerVersion() != CeHWIO_MT38_PROTO_B )
  {
     VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_PENDING;
  }
  else
  {
     VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_OK;
  }
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_PIC_OFVC_Clear
 * Description: This function defines COND CheckCPU PIC
 *              OFVC_CLEAR event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_PIC_OFVC_Clear(void)
{
  VsCOND_CheckCPU_Status.data &= CsCOND_CheckCPU_OFVC_ClearStatusFlags.data;
  VbCOND_MainCPU_FltByCheckTstFld = CbFALSE;
  VbCOND_MainCPU_FltByCheckTstCmp = CbFALSE;
  VeCOND_MainCPU_FltByCkTstStRpt  = CeSINGLE_NULL;
  VbCOND_CheckCPU_FltByMainTstFld = CbFALSE;
  VbCOND_CheckCPU_FltByMainTstCmp = CbFALSE;
  VeCOND_CheckCPU_FltByMnTstStRpt = CeSINGLE_NULL;
  SetHWIO_ETC_Check_Reinitialize(); /* Initialize PIC interfaces */

  if ( GetHWIO_ControllerVersion() != CeHWIO_MT38_PROTO_B )
  {
     VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_PENDING;
  }
  else
  {
     VeCOND_CheckCPU_OpStatus = CeCOND_CPU_OP_STAT_OK;
  }
}

#elif XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH

/******************************************************************************
 *
 * Function:    PerformCOND_CPU_SOH_DataProcessing
 * Description: This function performes ETC SOH output status read.
 *              The diagnostic status of the ETC State of Health checks
 *              is determined based on flags from ETC SOH HWIO and reported
 *              to the diagnostic manager later.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CPU_SOH_DataProcessing(void)
{
  WORD LwCOND_ETC_SOH_FltLog;

  /* due to high interrupt level of HWIO ETC SOH logic use local copy */
  /* of the HWIO ETC SOH fault data within the rest of the function   */
  LwCOND_ETC_SOH_FltLog = GetHWIO_ETC_SOH_Fault_Log();

  if ( GetVIOS_EngSt_PwrOffDly()
    && (GetVIOS_PwrdownDelayTimer() > KfCOND_t_PwrDwnClr) )
  {
    SbCOND_SOH_MainCPU_Flt     = CbFALSE;
    SbCOND_SOH_CommFlt         = CbFALSE;
    SbCOND_SOH_CheckingCPU_Flt = CbFALSE;
    
    SOH_ETC_Clear_Fault_Log(); 	 /* to clear Soh_FaultLogNVM */
  }
  else if ( GetHWIO_ETC_SOH_FltActnTaken(LwCOND_ETC_SOH_FltLog)
        && (! GetCOND_MainCPU_ClockPerfTestFailed()) )
  {
    if ( GetHWIO_ETC_SOH_Comm_FltPrsnt(LwCOND_ETC_SOH_FltLog)
      && (! SbCOND_SOH_MainCPU_Flt) )
    {
      SbCOND_SOH_CommFlt = CbTRUE;
    }
    else if ( GetHWIO_ETC_SOH_ChkngCPU_FltPrsnt(LwCOND_ETC_SOH_FltLog) )
    {
      if ( (! SbCOND_SOH_MainCPU_Flt) 
        && (! SbCOND_SOH_CommFlt) )
      {
        SbCOND_SOH_CheckingCPU_Flt = CbTRUE;
      }
      /* else do nothing - keep previous values */
    }
    else if ( GetHWIO_ETC_SOH_MainCPU_FltPrsnt(LwCOND_ETC_SOH_FltLog) )
    {
      SbCOND_SOH_MainCPU_Flt = CbTRUE;
    }
    /* else do nothing - keep previous values */
  }
  /* else do nothing - keep previous values */

  /* Update long term history for validation purposes */

  if ( GetHWIO_ETC_SOH_FltPrsnt(LwCOND_ETC_SOH_FltLog) )
  {
    NwCOND_SOH_FltLongTermHist |= LwCOND_ETC_SOH_FltLog;

    if ( ! SbCOND_SOH_FltPrsnt )
    {
      NcCOND_SOH_FltCntLongTerm = INCusp( NcCOND_SOH_FltCntLongTerm );
    }

    SbCOND_SOH_FltPrsnt = CbTRUE;
  }
  else
  {
    SbCOND_SOH_FltPrsnt = CbFALSE;
  }
}

/******************************************************************************
 *
 * Function:    DtrmnCOND_CPU_SOH_ProblemDetected
 * Description: This function performs CPU ETC SOH faults determinations.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void DtrmnCOND_CPU_SOH_ProblemDetected(void)
{
  if ( (GetVIOS_EngSt_PwrOffDly())
     &&(GetVIOS_PwrdownDelayTimer() > KfCOND_t_PwrDwnClr) )
  {
    SbCOND_SOH_MainCPU_TstFld     = CbFALSE;
    SbCOND_SOH_MainCPU_TstCmp     = CbFALSE;
    SbCOND_SOH_CommTstFld         = CbFALSE;
    SbCOND_SOH_CommTstCmp         = CbFALSE;
    SbCOND_SOH_CheckingCPU_TstFld = CbFALSE;
    SbCOND_SOH_CheckingCPU_TstCmp = CbFALSE;
  }

  if ( GetDGDM_DTC_FaultType(CeDGDM_COND_ETC_SOH_MainCPU) != CeDGDM_FAULT_TYPE_Z )
  {
    DtrmnCOND_CPU_DiagFaultPresent(
                            &SbCOND_SOH_MainCPU_TstFld,
                            &SbCOND_SOH_MainCPU_TstCmp,
                            &SeCOND_SOH_MainCPU_TstStRpt,
                            SbCOND_SOH_MainCPU_Flt,
                            CeDGDM_COND_ETC_SOH_MainCPU );
  }

  if ( GetDGDM_DTC_FaultType(CeDGDM_COND_ETC_SOH_Comm) != CeDGDM_FAULT_TYPE_Z )
  {
    DtrmnCOND_CPU_DiagFaultPresent(
                            &SbCOND_SOH_CommTstFld,
                            &SbCOND_SOH_CommTstCmp,
                            &SeCOND_SOH_CommTstStRpt,
                            SbCOND_SOH_CommFlt,
                            CeDGDM_COND_ETC_SOH_Comm );
  }

  if ( GetDGDM_DTC_FaultType(CeDGDM_COND_ETC_SOH_CheckingCPU) != CeDGDM_FAULT_TYPE_Z )
  {
    DtrmnCOND_CPU_DiagFaultPresent(
                            &SbCOND_SOH_CheckingCPU_TstFld,
                            &SbCOND_SOH_CheckingCPU_TstCmp,
                            &SeCOND_SOH_CheckingCPU_TstStRpt,
                            SbCOND_SOH_CheckingCPU_Flt,
                            CeDGDM_COND_ETC_SOH_CheckingCPU );
  }
}

/******************************************************************************
 *
 * Function:    InitCOND_CheckCPU_SOH_CommonZero
 * Description: This function contains common COND ETC SOH code
 *               for zero-initializations.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void InitCOND_CheckCPU_SOH_CommonZero(void)
{
  SbCOND_SOH_MainCPU_Flt       = CbFALSE;
  SbCOND_SOH_MainCPU_TstFld    = CbFALSE;
  SbCOND_SOH_MainCPU_TstCmp    = CbFALSE;
  SeCOND_SOH_MainCPU_TstStRpt  = CeSINGLE_NULL;

  SbCOND_SOH_CommFlt      = CbFALSE;
  SbCOND_SOH_CommTstFld   = CbFALSE;
  SbCOND_SOH_CommTstCmp   = CbFALSE;
  SeCOND_SOH_CommTstStRpt = CeSINGLE_NULL;

  SbCOND_SOH_CheckingCPU_Flt      = CbFALSE;
  SbCOND_SOH_CheckingCPU_TstFld   = CbFALSE;
  SbCOND_SOH_CheckingCPU_TstCmp   = CbFALSE;
  SeCOND_SOH_CheckingCPU_TstStRpt = CeSINGLE_NULL;

  SbCOND_SOH_FltPrsnt = CbFALSE;
}

/******************************************************************************
 *
 * Function:    InitCOND_CheckCPU_SOH_CommonNonZero
 * Description: This function contains common COND ETC SOH code
 *               for nonzero-initializations.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
INLINE void InitCOND_CheckCPU_SOH_CommonNonZero(void)
{
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_SOH_ResetKeyOn
 * Description: This function defines COND CheckCPU ETC SOH
 *               CONTROLLER_RESET_COMPLETE_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_SOH_ResetKeyOn(void)
{
 #if XeSYST_RAM_CLEAR == CeSYST_RAM_CLEAR_UNAVAILABLE
  InitCOND_CheckCPU_SOH_CommonZero();
 #endif
  InitCOND_CheckCPU_SOH_CommonNonZero();

  if ( GetFILE_NVM_LTM_Failure() && (!GetFILE_EMS_LrnRstRqst()))
  {
    NcCOND_SOH_FltCntLongTerm  = V_COUNT_WORD(0);
    NwCOND_SOH_FltLongTermHist = (WORD )0;
  }
  
  SOH_ETC_Clear_Fault_Log(); 	 /* to clear Soh_FaultLogNVM */
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_SOH_PwrdnDlyToKeyOn
 * Description: This function defines COND CheckCPU ETC SOH
 *               POWER_OFF_DELAY_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_SOH_PwrdnDlyToKeyOn(void)
{
  InitCOND_CheckCPU_SOH_CommonZero();
  InitCOND_CheckCPU_SOH_CommonNonZero();
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_SOH_ShutDnToKeyOn
 * Description:  This function defines COND CheckCPU ETC SOH
 *              SHUTDOWN_IN_PROGRESS_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_SOH_ShutDnToKeyOn(void)
{
  InitCOND_CheckCPU_SOH_CommonZero();
  InitCOND_CheckCPU_SOH_CommonNonZero();
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_SOH_OFVC_Clear
 * Description: This function defines COND CheckCPU ETC SOH
 *               OFVC_CLEAR event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
static void PerformCOND_CheckCPU_SOH_OFVC_Clear(void)
{
  InitCOND_CheckCPU_SOH_CommonZero();
  InitCOND_CheckCPU_SOH_CommonNonZero();
  
  SOH_ETC_Clear_Fault_Log(); 	 /* to clear Soh_FaultLogNVM */
}

#endif /* XeCOND_ETC_CHECKING_CPU_TYPE */

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_ResetKeyOn
 * Description: This function defines COND CheckCPU
 *               CONTROLLER_RESET_COMPLETE_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void PerformCOND_CheckCPU_ResetKeyOn(void)
{
 #if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
  PerformCOND_CheckCPU_PIC_ResetKeyOn();
 #elif XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH
  PerformCOND_CheckCPU_SOH_ResetKeyOn();
 #endif
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_PwrdnDlyToKeyOn
 * Description: This function defines COND CheckCPU
 *               POWER_OFF_DELAY_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void PerformCOND_CheckCPU_PwrdnDlyToKeyOn(void)
{
 #if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
  PerformCOND_CheckCPU_PIC_PwrdnDlyToKeyOn();
 #elif XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH
  PerformCOND_CheckCPU_SOH_PwrdnDlyToKeyOn();
 #endif
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_ShutDnToKeyOn
 * Description: This function defines COND CheckCPU
 *               SHUTDOWN_IN_PROGRESS_To_KEY_ON event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void PerformCOND_CheckCPU_ShutDnToKeyOn(void)
{
 #if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
  PerformCOND_CheckCPU_PIC_ShutDnToKeyOn();
 #elif XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH
  PerformCOND_CheckCPU_SOH_ShutDnToKeyOn();
 #endif
}

/******************************************************************************
 *
 * Function:    PerformCOND_CheckCPU_OFVC_Clear
 * Description: This function defines COND CheckCPU
 *               OFVC_CLEAR event handler.
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void PerformCOND_CheckCPU_OFVC_Clear(void)
{
 #if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
  PerformCOND_CheckCPU_PIC_OFVC_Clear();
 #elif XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH
  PerformCOND_CheckCPU_SOH_OFVC_Clear();
 #endif
}

/******************************************************************************
 *
 * Function:    MngCOND_CheckCPU_15p6Tasks
 * Description: This function manages COND CheckCPU 15.6 ms Tasks
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void MngCOND_CheckCPU_15p6Tasks(void)
{
 #if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
  DtrmnCOND_CPU_PIC_CommsVltgStabInitDelay();
  PerformCOND_CPU_ReInitOfCommsWithPIC();
  PerformCOND_CPU_PIC_DataProcessing();
 #endif
}

/******************************************************************************
 *
 * Function:    MngCOND_CheckCPU_31p2Tasks
 * Description: This function manages COND CheckCPU 31.25 ms Tasks
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void MngCOND_CheckCPU_31p2Tasks(void)
{
 #if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH
  PerformCOND_CPU_SOH_DataProcessing();
  DtrmnCOND_CPU_SOH_ProblemDetected();
 #endif
}

/******************************************************************************
 *
 * Function:    MngCOND_CheckCPU_125Tasks
 * Description: This function manages COND CheckCPU 125 ms Tasks
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void MngCOND_CheckCPU_125Tasks(void)
{
 #if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
  DtrmnCOND_CPU_PIC_ProblemDetected();
 #endif
}

#endif /* XeCOND_ETC_CHECKING_CPU_TYPE != CeCOND_ETC_CHECKING_CPU_IS_NONE */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   040520 caw 2853 Created Module.
* tci_pt3#2
*       040726 akk 4073 Changed includes for COND modularisation.
* 3.0   040324 caw 4909 Modified: PerformCOND_CPU_DataProcessing
*                                 MngCOND_CheckCPU_15p6Tasks
*                                 PerformCOND_CheckCPU_OFVC_Clear
*                                 PerformCOND_CheckCPU_ResetKeyOn
*                                 PerformCOND_CheckCPU_PwrdnDlyToKeyOn
*                                 PerformCOND_CheckCPU_ShutDnToKeyOn
*                       Added: DtrmnCOND_CPU_PIC_CommsVltgStabInitDelay
*                              PerformCOND_CPU_ReInitOfCommsWithPIC
*                       Added logic to corret low battery voltage failures
*                        of PIC and Main CPU communication failures.
* 4     050712 hdb 5250 ETC Checking CPU Throughput Robustness
*                       Modify PerformCOND_CheckCPU_ResetKeyOn to set
*                       VeCOND_CheckCPU_OpStatus = OK.
* 4.1.1 070108 MCB 5340 Changed XeCOND_SYST_CONTROLLER_DIAG_TYPE to
*                       XeCOND_ETC_CHECKING_CPU_TYPE
* 4.1.2 070219 gps 5481 COND: Support Gen 3 ETC Checking CPU (VSEP). CORE Part.
* tci_pt3#xxx
*       070517 PVD 4535 Used NbFILE_EMS_LrnRstRqst flag in RST_TO_KEYON to
*                       selectively retain NVM data.
* tci_pt3#4.1.4
*       080324 sat 6821 Added call SOH_ETC_Clear_Fault_Log() to clear HWIO 
* 						fault Log variable.
******************************************************************************/