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
#include "hal_eng.h"

/**********************************************************************/
/* Global Variable Definitions                                        */
/**********************************************************************/
#pragma section DATA " " ".nc_nvram"
WORD         NwCOND_SOH_FltLongTermHist;
T_COUNT_WORD NcCOND_SOH_FltCntLongTerm;

TbBOOLEAN    SbCOND_SOH_MainCPU_Flt;
TbBOOLEAN    SbCOND_SOH_CommFlt;
TbBOOLEAN    SbCOND_SOH_CheckingCPU_Flt;
TbBOOLEAN    SbCOND_SOH_FltPrsnt;
#pragma section DATA " " ".bss"

TbBOOLEAN    SbCOND_SOH_MainCPU_TstCmp;
TbBOOLEAN    SbCOND_SOH_CommTstCmp;
TbBOOLEAN    SbCOND_SOH_CheckingCPU_TstCmp;

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

  if (VeVIOS_EngSt == CeENG_POWEROFFDELAY)
  {
    SbCOND_SOH_MainCPU_Flt     = CbFALSE;
    SbCOND_SOH_CommFlt         = CbFALSE;
    SbCOND_SOH_CheckingCPU_Flt = CbFALSE;
    
    SOH_ETC_Clear_Fault_Log(); 	 /* to clear Soh_FaultLogNVM */
  }
  else if ( GetHWIO_ETC_SOH_FltActnTaken(LwCOND_ETC_SOH_FltLog) )
  {
    if ( GetHWIO_ETC_SOH_MainCPU_FltPrsnt(LwCOND_ETC_SOH_FltLog) )
    {
      SbCOND_SOH_MainCPU_Flt = CbTRUE;
    }
    /* else do nothing - keep previous values */
  }
  else if ( GetHWIO_ETC_SOH_Comm_FltPrsnt(LwCOND_ETC_SOH_FltLog)
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
  else 
  {
  }
  /* else do nothing - keep previous values */

  /* Update long term history for validation purposes */

  if ( GetHWIO_ETC_SOH_FltPrsnt(LwCOND_ETC_SOH_FltLog) )
  {
    NwCOND_SOH_FltLongTermHist |= LwCOND_ETC_SOH_FltLog;

    if ( ! SbCOND_SOH_FltPrsnt )
    {
      NcCOND_SOH_FltCntLongTerm ++;
    }

    SbCOND_SOH_FltPrsnt = CbTRUE;
  }
  else
  {
    SbCOND_SOH_FltPrsnt = CbFALSE;
  }

  SbCOND_SOH_MainCPU_TstCmp    = CbTRUE;
  SbCOND_SOH_CommTstCmp   = CbTRUE;
  SbCOND_SOH_CheckingCPU_TstCmp   = CbTRUE;
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
  // SbCOND_SOH_MainCPU_Flt       = CbFALSE;
  SbCOND_SOH_MainCPU_TstCmp    = CbFALSE;
  // SbCOND_SOH_CommFlt      = CbFALSE;
  SbCOND_SOH_CommTstCmp   = CbFALSE;
  // SbCOND_SOH_CheckingCPU_Flt      = CbFALSE;
  SbCOND_SOH_CheckingCPU_TstCmp   = CbFALSE;
  // SbCOND_SOH_FltPrsnt = CbFALSE;
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
void PerformCOND_CheckCPU_SOH_ResetKeyOn(void)
{
  InitCOND_CheckCPU_SOH_CommonZero();

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
void PerformCOND_CheckCPU_SOH_PwrdnDlyToKeyOn(void)
{
  InitCOND_CheckCPU_SOH_CommonZero();
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
void PerformCOND_CheckCPU_SOH_ShutDnToKeyOn(void)
{
  InitCOND_CheckCPU_SOH_CommonZero();
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
void PerformCOND_CheckCPU_SOH_OFVC_Clear(void)
{
  InitCOND_CheckCPU_SOH_CommonZero();
  
  SOH_ETC_Clear_Fault_Log(); 	 /* to clear Soh_FaultLogNVM */
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
  PerformCOND_CPU_SOH_DataProcessing();
}

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/