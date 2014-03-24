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
#include "condcald.h"   /* For local calibration declarations */
#include "hal_soh.h"    /* For SOH_ETC_Clear_Fault_Log()      */
#include "soh.h"

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
/* Function Definitions                                               */
/**********************************************************************/

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
  LwCOND_ETC_SOH_FltLog = SOH_ETC_Get_Fault_Log();

  if ( GetVIOS_EngSt_PwrOffDly()
    && (GetVIOS_PwrdownDelayTimer() > KfCOND_t_PwrDwnClr) )
  {
    // SbCOND_SOH_MainCPU_Flt     = CbFALSE;
    // SbCOND_SOH_CommFlt         = CbFALSE;
    // SbCOND_SOH_CheckingCPU_Flt = CbFALSE;
    
    // SOH_ETC_Clear_Fault_Log(); 	 /* to clear Soh_FaultLogNVM */
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
*
******************************************************************************/