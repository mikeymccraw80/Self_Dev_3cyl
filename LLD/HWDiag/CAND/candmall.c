/******************************************************************************
 *
 * Filename:          candmall.c
 *
 * Description:       CAN diagnostic for ECM to GCU communication
 *
 * Global Functions Defined:
 *                    InitCAND_RstToKeyOn
 *                    InitCAND_OFVC_Clear
 *                    MngCAND_31p2msTCU_Tasks
 * Static Functions Defined:
 *                    DtrmnCAND_CommEnblCrit
 * Inline Functions Defined:
 *                    DtrmnCAND_GCU_Msg_Received
 *
 * Forward Engine Management Systems
 *
 * Copyright 2001-2003, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      mt20u2#7/csrc/candmall.c/1 %
 * %date_created:   Wed Mar 19 09:46:28 2008 %
 * %version:        1 %
 * %derived_by:     vzp48z %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h"

/******************************************************************************
* System Include Files
******************************************************************************/


/*****************************************************************************
 *  Application Include Files
 *****************************************************************************/
#include "candpapi.h"   /* For Definition-Declaration check  */
#include "candcald.h"   /* For local calibration declaration */
#include "intr_ems.h"

/*****************************************************************************
 *  Local Variable Definitions
 *****************************************************************************/

TbBOOLEAN             SbCAND_GCU_CommFailCritMet;
TbBOOLEAN             SbCAND_GCU_CommEnblCritMet;
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN             SbCAND_GCU_CommTestFailed;
#pragma section DATA " " ".bss"
TbBOOLEAN             SbCAND_GCU_CommTestComplete;
TbBOOLEAN             SbCAND_GCU_CommTestComplete_Internal;
T_COUNT_WORD          ScCAND_GCU_CommFailCntr;
T_COUNT_WORD          ScCAND_GCU_CommSampleCntr;

/*****************************************************************************
 *
 * Function:           InitCAND_RstToKeyOn
 * Description:        This process will Initialize the CAN
 *                     Communication diagnostic variables on
 *                     CONTROLLER_RESET_COMPLETE_To_KEY_ON
 * Parameters:         None
 * Return:             None
 *****************************************************************************/
void InitCAND_RstToKeyOn(void)
{
  SbCAND_GCU_CommEnblCritMet = CbFALSE;  
  SbCAND_GCU_CommTestComplete_Internal = CbFALSE; 
  SbCAND_GCU_CommTestComplete = CbFALSE; 
  ScCAND_GCU_CommFailCntr = V_COUNT_WORD(0); 
  ScCAND_GCU_CommSampleCntr = V_COUNT_WORD(0);
}

#if 0
/*****************************************************************************
 *
 * Function:     InitCAND_OFVC_Clear
 * Description:  Initialization - Off Vehicle Communication via Class 2
 *               (pspec: OFVC_DIAG_CLEAR_EVENT)
 * Parameters:   None       
 * Return:       None
 *****************************************************************************/
void InitCAND_OFVC_Clear(void)
{
  SbCAND_GCU_CommTestComplete_Internal = CbFALSE;
  SbCAND_GCU_CommTestComplete = CbFALSE;
  SbCAND_GCU_CommTestFailed = CbFALSE; 
  ScCAND_GCU_CommFailCntr = V_COUNT_BYTE(0); 
  ScCAND_GCU_CommSampleCntr = V_COUNT_WORD(0);
  SeCAND_GCU_CommTestStatRpt = CeNULL;
}
#endif

/*****************************************************************************
 *
 * Function:    DtrmnCAND_CommEnblCrit
 * Description: This process determines whether or not the common enable
 *              criteria is met.
 * Parameters:  None
 * Return:      TbBOOLEAN
 *****************************************************************************/
static TbBOOLEAN DtrmnCAND_CommEnblCrit(void)
{
  TbBOOLEAN LbCAND_CommEnblCritMet;
  if ( ( GetVIOS_U_IgnVolt() > KfCAND_U_CommSystemThrshLo )
       && ( GetVIOS_t_EngRunTime() > KfCAND_t_CommEngRunThrsh )
       && ( GetVIOS_EngSt() == CeENG_RUN ) )
  {
    LbCAND_CommEnblCritMet = CbTRUE;  
  }
  else
  {
    LbCAND_CommEnblCritMet = CbFALSE;
  }
  return LbCAND_CommEnblCritMet;
}

/*****************************************************************************
 *
 * Function:    MngCAND_31p2msGCU_Tasks
 * Description: This process will execute CAN Communication diagnostic in the
 *              31.2 ms loop
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void MngCAND_31p2msTCU_Tasks(void)
{
  SbCAND_GCU_CommEnblCritMet = DtrmnCAND_CommEnblCrit();
  if ( SbCAND_GCU_CommEnblCritMet )
  {
     if ( ReadCANH_Msg_NotReceived() )
     {
       SbCAND_GCU_CommFailCritMet = CbTRUE;
     }
     else
     {
       SbCAND_GCU_CommFailCritMet = CbFALSE;
     }
   }
   else
   {
     SbCAND_GCU_CommFailCritMet = CbFALSE;   
   }
         
   UpdateOBDU_SingleTestCntrs( SbCAND_GCU_CommTestComplete_Internal,
                               SbCAND_GCU_CommEnblCritMet,
                               SbCAND_GCU_CommFailCritMet,
                               &ScCAND_GCU_CommFailCntr,
                              &ScCAND_GCU_CommSampleCntr );

  if ( SbCAND_GCU_CommEnblCritMet )
  {
    EvalOBDU_SingleXofY( ScCAND_GCU_CommFailCntr,
                         ScCAND_GCU_CommSampleCntr,
                         KcCAND_FailThrsh,
                         KcCAND_SampleThrsh,
                         &SbCAND_GCU_CommTestComplete_Internal,
                         &SbCAND_GCU_CommTestFailed );
  }
  SbCAND_GCU_CommTestComplete |= SbCAND_GCU_CommTestComplete_Internal;
}

