/******************************************************************************
 *
 * Filename:          condmain.c
 *
 * Description:       This is the source file for output IO diagnostic
 *                    subsystem.
 *
 * Global Functions Defined:
 *                    InitCOND_Variables
 *                    InitCOND_Variables_NVMdepend
 *                    InitCOND_Device_OFVC_Clear
 *                    GetCOND_IO_DevFailCntr
 *                    MngCOND_ADC0
 *                    MngCOND_ADC1
 *                    MngCOND_GPR
 *                    MngCOND_MainCPUClock
 *                    MngCOND_COP
 *                    MngCOND_SPRAM_Checksum
 * Static Functions Defined:
 *                    EvalCOND_ADC0_EnblCritMet
 *                    EvalCOND_ADC0_FailCritMet
 *                    EvalCOND_ADC1_EnblCritMet
 *                    EvalCOND_ADC1_FailCritMet
 *                    EvalCOND_GPR_EnblCritMet
 *                    EvalCOND_GPR_FailCritMet
 *                    EvalCOND_Clock_EnblCritMet
 *                    EvalCOND_Clock_FailCritMet
 *                    EvalCOND_COP_EnblCritMet
 *                    EvalCOND_COP_FailCritMet
 *                    InitCOND_SPRAM_Checksum 
 *                    PerfmCOND_SPRAM_Checksum
 *                    DtrmnCOND_SPRAM_ChecksumFault
 *                    ReportCOND_SPRAM_ChecksumTestResults
 * Inline Functions Defined:
 *                    None
 * Forward Engine Management Systems
 *
 * Copyright 2004-2011, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tcb_pt1#1/csrc/condmain.c/tci_pt3#12 %
 * %date_created:  Sat Oct 15 16:31:40 2011 %
 * %version:       tci_pt3#12 %
 * %derived_by:    xz04bb %
 *
 *****************************************************************************/

/*****************************************************************************
*  Include Files                                                            *
****************************************************************************/
#include "condcald.h"   /* For COND Local Configuration       */
#include "intr_ems.h"

typedef enum
{
  CeCOND_IO_DEVICE_ADC_0,      /*  1 */
  CeCOND_IO_DEVICE_ADC_1,      /*  2 */
  CeCOND_IO_DEVICE_GPR,        /*  3 */
  CeCOND_IO_DEVICE_CPU_CLOCK,  /*  4 */
  CeCOND_IO_DEVICE_COP,        /*  5 */
  CcCOND_NumOf_IO_Device
} TeCOND_IO_Device;

typedef enum
{
  CeCOND_ADC_InitialState,		  /* 0 */
  CeCOND_ADC_DiagTypeZ,			  /* 1 */
  CeCOND_ADC_IgnNotOn,			  /* 2 */
  CeCOND_ADC_IgnVoltNotInRange,	  /* 3 */
  CeCOND_ADC_NotTestedByHWIO,	  /* 4 */
  CeCOND_ADC_DelayTimerActive,	  /* 5 */
  CeCOND_ADC_EnblCritMet		  /* 6 */
} TeCOND_ADC_TstEnblStatus;

typedef enum
{
  CeCOND_Clock_InitialState,		  /* 0 */
  CeCOND_Clock_DiagTypeZ,			  /* 1 */
  CeCOND_Clock_TestComplete,          /* 2 */
  CeCOND_Clock_IgnNotOn,			  /* 3 */
  CeCOND_Clock_NotTestedByHWIO,	      /* 4 */
  CeCOND_Clock_DelayTimerActive,	  /* 5 */
  CeCOND_Clock_EnblCritMet		      /* 6 */
} TeCOND_MainCPUClock_TstEnblStatus;

typedef enum
{
  CeCOND_COP_InitialState,		     /* 0 */
  CeCOND_COP_DiagTypeZ,			     /* 1 */
  CeCOND_COP_TestComplete,			 /* 2 */
  CeCOND_COP_IgnNotOn,			     /* 3 */
  CeCOND_COP_NotTestedByHWIO,	     /* 4 */
  CeCOND_COP_NVMFailure,	         /* 5 */
  CeCOND_COP_RunningReset,	         /* 6 */
  CeCOND_COP_DelayTimerActive,	     /* 7 */
  CeCOND_COP_EnblCritMet		     /* 8 */
} TeCOND_COP_TstEnblStatus;

/*****************************************************************************
 *  Gloabl Variable declarations
 *****************************************************************************/
#if 0
TbBOOLEAN VOL0ADDR  VbCOND_MainCPU_AD_TestFailed;
TbBOOLEAN VOL0ADDR  VbCOND_MainCPU_ClockPerfTestFailed;
TbBOOLEAN VOL0ADDR  VbCOND_ComputerOperatingProperlyFailed;

TbBOOLEAN VOL0ADDR  VbCOND_HWIO_COPFailed;
TbBOOLEAN VOL0ADDR  VbCOND_HWIO_COPTested;
#endif

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN    VbCOND_HWIO_ClockFailed;
#pragma section DATA " " ".bss"
TbBOOLEAN    VbCOND_HWIO_ClockTstComplete;
TbBOOLEAN    VbCOND_HWIO_ClockTested;
TbBOOLEAN    VbCOND_HWIO_ClockEnblCritMet;
TbBOOLEAN    VbCOND_HWIO_ClockFailCritMet;

static TeCOND_MainCPUClock_TstEnblStatus  SeCOND_Clock_EnblStatus;
static TwTIME_t_R125ms                    SfCOND_t_ClockEnblDlyTmr;
static TbBOOLEAN                          SbCOND_Clock_OneTimeTstCmpt;

#pragma section DATA " " ".nc_nvram"
TbBOOLEAN    VbCOND_HWIO_ADC0Failed;
#pragma section DATA " " ".bss"
TbBOOLEAN    VbCOND_HWIO_ADC0TstComplete;
TbBOOLEAN    VbCOND_HWIO_ADC0Tested;
TbBOOLEAN    VbCOND_HWIO_ADC0EnblCritMet;
TbBOOLEAN    VbCOND_HWIO_ADC0FailCritMet;

static TeCOND_ADC_TstEnblStatus  SeCOND_ADC0_EnblStatus;
static TwTIME_t_R125ms           SfCOND_t_ADC0EnblDlyTmr;


/*****************************************************************************
 *  Static Variable declarations
 *****************************************************************************/

static TeCOND_COP_TstEnblStatus    SeCOND_COP_EnblStatus;
static TbBOOLEAN SbCOND_COP_OneTimeTstCmpt;

/*****************************************************************************
 *  Static Function declarations
 *****************************************************************************/
static void EvalCOND_ADC0_EnblCritMet(void);
static void EvalCOND_ADC0_FailCritMet(void);
static void EvalCOND_ADC1_EnblCritMet(void);
static void EvalCOND_ADC1_FailCritMet(void);
static void EvalCOND_Clock_EnblCritMet(void);
static void EvalCOND_Clock_FailCritMet(void);
static void EvalCOND_COP_EnblCritMet(void);
static void EvalCOND_COP_FailCritMet(void);

/********************************************************************
 *   Module Function Definitions
 ********************************************************************/


/*****************************************************************************
 * Function:          InitCOND_Variables
 * Description:       This function resets all variables for IO diagnostics.
 *****************************************************************************/
void InitCOND_Variables(void)
{
  //VbCOND_HWIO_ADC0Failed      = CbFALSE;
  VbCOND_HWIO_ADC0Tested      = CbFALSE;
  VbCOND_HWIO_ADC0EnblCritMet = CbFALSE;
  VbCOND_HWIO_ADC0FailCritMet = CbFALSE;
  VbCOND_HWIO_ADC0TstComplete = CbFALSE;
  SeCOND_ADC0_EnblStatus      = CeCOND_ADC_InitialState;
  SfCOND_t_ADC0EnblDlyTmr     = C_R125ms16(0);

  //VbCOND_HWIO_ClockFailed     = CbFALSE;
  VbCOND_HWIO_ClockTstComplete= CbFALSE;
  VbCOND_HWIO_ClockTested     = CbFALSE;
  VbCOND_HWIO_ClockEnblCritMet= CbFALSE;
  VbCOND_HWIO_ClockFailCritMet= CbFALSE;
  SeCOND_Clock_EnblStatus     = CeCOND_Clock_InitialState;
  SfCOND_t_ClockEnblDlyTmr    = C_R125ms16(0);
  SbCOND_Clock_OneTimeTstCmpt = CbFALSE;
  
#if 0
  SeCOND_COP_EnblStatus = CeCOND_COP_InitialState;
  NsCOND_COPTstData.TstStRpt = CeSINGLE_NULL;
  NfCOND_t_COPEnblDlyTmr = V_TIME_SEC_P125(0);
  VbCOND_HWIO_COPFailed = CbFALSE;
  VbCOND_HWIO_COPTested = CbFALSE;
  VbCOND_HWIO_ClockFailed = CbFALSE;
  VbCOND_HWIO_ClockTested = CbFALSE;
#endif
}

/*****************************************************************************
 * Function:          InitCOND_Variables_NVMdepend
 * Description:       This function resets variables for IO diagnostics.
 *****************************************************************************/
void InitCOND_Variables_NVMdepend(void)
{
#if 0
  NsCOND_ClockTstData.EnblCritMet = CbFALSE;
  NsCOND_ClockTstData.FailCritMet = CbFALSE;
  NsCOND_ClockTstData.TstComplete = CbFALSE;
  NsCOND_ClockTstData.FailCntr = V_COUNT_WORD(0); 
  NsCOND_ClockTstData.SampleCntr = V_COUNT_WORD(0);
   
  NsCOND_COPTstData.EnblCritMet = CbFALSE;
  NsCOND_COPTstData.FailCritMet = CbFALSE;
  NsCOND_COPTstData.TstComplete = CbFALSE;
  NsCOND_COPTstData.TstFailed = CbFALSE;
  NsCOND_COPTstData.FailCntr = V_COUNT_WORD(0);
  NsCOND_COPTstData.SampleCntr = V_COUNT_WORD(0);
#endif
}

/*****************************************************************************
 * Function:          InitCOND_Device_OFVC_Clear
 * Description:       This function initializes the COND I/O device diagnostic variables
 *                    when a device clear request is received.
 *****************************************************************************/
void InitCOND_Device_OFVC_Clear(void)
{
    InitCOND_Variables();
    InitCOND_Variables_NVMdepend();
}

/******************************************************************************
 *
 * Function:    InitCOND_Device_OFVC_RstKeyOn
 * Description: 
 *
 * Parameters:  None
 * Return:      None
 *****************************************************************************/
void InitCOND_Device_OFVC_RstKeyOn(void)
{
    InitCOND_Variables();
}
/*****************************************************************************
 * Function:        MngCOND_ADC0
 * Description:     This function is called at 125ms rate for ADC0 diagnostics.
 * Parameters:      None
 * Return:          None
 *****************************************************************************/

void MngCOND_ADC0(void)
{
    /* Read THE HWIO Tested and Failed Flags */
    VbCOND_HWIO_ADC0Failed =  Get_IO_Discrete_Diag_ADC_0(OUTPUT_GEN_FLT_PRESENT);
    VbCOND_HWIO_ADC0Tested =  Get_IO_Discrete_Diag_ADC_0(OUTPUT_GEN_FLT_TESTED);

    /* eval the enable criteria met */
    if(CeIGN_ON == GetVIOS_IgnSt())
    {
       if(VbCOND_HWIO_ADC0Tested)
       {
          if(SfCOND_t_ADC0EnblDlyTmr >= KfCOND_t_ADC0EnblDlyTmrThrsh)
          {
             VbCOND_HWIO_ADC0EnblCritMet = CbTRUE;
             SeCOND_ADC0_EnblStatus = CeCOND_ADC_EnblCritMet;
          }
          else
          {
             SeCOND_ADC0_EnblStatus = CeCOND_ADC_DelayTimerActive;
             SfCOND_t_ADC0EnblDlyTmr = Inc(SfCOND_t_ADC0EnblDlyTmr);
             VbCOND_HWIO_ADC0EnblCritMet = CbFALSE;
          }
       }
       else
       {
          SeCOND_ADC0_EnblStatus = CeCOND_ADC_NotTestedByHWIO;
          VbCOND_HWIO_ADC0EnblCritMet = CbFALSE;
          SfCOND_t_ADC0EnblDlyTmr = C_R125ms16(0); 
       }
    }
    else
    {
       SeCOND_ADC0_EnblStatus = CeCOND_ADC_IgnNotOn;
       VbCOND_HWIO_ADC0EnblCritMet = CbFALSE;
       SfCOND_t_ADC0EnblDlyTmr = C_R125ms16(0);
    }

    /* eval fail condition */
    if(VbCOND_HWIO_ADC0EnblCritMet)
    {
       VbCOND_HWIO_ADC0TstComplete = VbCOND_HWIO_ADC0Tested;

        /* CLEAR HWIO FLAGS */
       Clear_IO_Discrete_Diag_ADC_0(OUTPUT_GEN_FLT_PRESENT);
       Clear_IO_Discrete_Diag_ADC_0(OUTPUT_GEN_FLT_TESTED);
    }
}

/*****************************************************************************
 * Function:        MngCOND_MainCPUClock
 * Description:     This function is called at 125ms rate for Main CPU Clock diagnostics.
 * Parameters:      None
 * Return:          None
 *****************************************************************************/

void MngCOND_MainCPUClock(void)
{

    /* Read THE HWIO Tested and Failed Flags */
    VbCOND_HWIO_ClockFailed =  Get_IO_Discrete_Diag_CPU_Clock(OUTPUT_GEN_FLT_PRESENT);
    VbCOND_HWIO_ClockTested =  Get_IO_Discrete_Diag_CPU_Clock(OUTPUT_GEN_FLT_TESTED);

   /* Eval enable criteria */
    if(!SbCOND_Clock_OneTimeTstCmpt) {
        if(CeIGN_ON == GetVIOS_IgnSt()) {
            if(VbCOND_HWIO_ClockTested) {
                 if(SfCOND_t_ClockEnblDlyTmr >= KfCOND_t_ClockEnblDlyTmrThrsh) {
                    VbCOND_HWIO_ClockEnblCritMet = CbTRUE;
                    SeCOND_Clock_EnblStatus = CeCOND_Clock_EnblCritMet;
                 } else {
                    SeCOND_Clock_EnblStatus = CeCOND_Clock_DelayTimerActive;
                    SfCOND_t_ClockEnblDlyTmr = Inc(SfCOND_t_ClockEnblDlyTmr);
                    VbCOND_HWIO_ClockEnblCritMet = CbFALSE;
                 }
             } else {
                    SeCOND_Clock_EnblStatus = CeCOND_Clock_NotTestedByHWIO;
                    VbCOND_HWIO_ClockEnblCritMet = CbFALSE;
                    SfCOND_t_ClockEnblDlyTmr = C_R125ms16(0); 
            }
        } else {
            SeCOND_Clock_EnblStatus = CeCOND_Clock_IgnNotOn;
            VbCOND_HWIO_ClockEnblCritMet = CbFALSE;
            SfCOND_t_ClockEnblDlyTmr = C_R125ms16(0);
        }
    } else {
        SeCOND_Clock_EnblStatus = CeCOND_Clock_TestComplete;
        VbCOND_HWIO_ClockEnblCritMet = CbFALSE;
        SfCOND_t_ClockEnblDlyTmr = C_R125ms16(0);
    }

    if(VbCOND_HWIO_ClockEnblCritMet) {
        SbCOND_Clock_OneTimeTstCmpt = CbTRUE;

        /* RESET THE HWIO TESTED AND FAILED FLAGS*/
        VbCOND_HWIO_ClockTstComplete = VbCOND_HWIO_ClockTested;
        
        /* CLEAR HWIO FLAGS */
       Clear_IO_Discrete_Diag_CPU_Clock(OUTPUT_GEN_FLT_PRESENT);
       Clear_IO_Discrete_Diag_CPU_Clock(OUTPUT_GEN_FLT_TESTED);
    }
}


#if 0
/*****************************************************************************
 * Function:        MngCOND_MainCPUClock
 * Description:     This function is called at 125ms rate for Watchdog Timer(COP)
 *                  diagnostics.
 * Parameters:      None
 * Return:          None
 *****************************************************************************/

void MngCOND_COP(void)
{
    /* Read THE HWIO Tested and Failed Flags */
    VbCOND_HWIO_COPFailed =  GetIO_DiscreteOutputDiagStatus(DEVICE_CPU_WATCHDOG_TIMER, OUTPUT_GEN_FLT_PRESENT);
    VbCOND_HWIO_COPTested =  GetIO_DiscreteOutputDiagStatus(DEVICE_CPU_WATCHDOG_TIMER, OUTPUT_GEN_FLT_TESTED);

    EvalCOND_COP_EnblCritMet();

    if(NsCOND_COPTstData.EnblCritMet)
    {
       EvalCOND_COP_FailCritMet();
       SbCOND_COP_OneTimeTstCmpt = CbTRUE;
       ProcessOBDU_StandardAlgorithm (CeDGDM_COND_COPFault,
                                   &NsCOND_COPTstData,
                                   &KaCOND_COPSampleFailCtrThrsh,
                                   CbTRUE);
       /* RESET THE HWIO TESTED AND FAILED FLAGS*/
       VbCOND_HWIO_COPFailed = CbFALSE;
       VbCOND_HWIO_COPTested = CbFALSE;
        
        /* CLEAR HWIO FLAGS */
       ClearIO_DiscreteOutputDiagStatus(DEVICE_CPU_WATCHDOG_TIMER, OUTPUT_GEN_FLT_PRESENT);
       ClearIO_DiscreteOutputDiagStatus(DEVICE_CPU_WATCHDOG_TIMER, OUTPUT_GEN_FLT_TESTED);
       VbCOND_ComputerOperatingProperlyFailed = (TbBOOLEAN)(NsCOND_COPTstData.TstFailed);
    }

}

/*****************************************************************************
 * Function:        EvalCOND_COP_EnblCritMet
 * Description:     This function checks if enable criteria met for Watchdog Timer(COP)
 *                  diagnostics.
 * Parameters:      None
 * Return:          None
 *****************************************************************************/
static void EvalCOND_COP_EnblCritMet(void)
{
   /* check if Diagnostic Type Z*/
   if(GetDGDM_DTC_FaultType(CeDGDM_COND_COPFault)!= CeDGDM_FAULT_TYPE_Z)
   {
       if(!SbCOND_COP_OneTimeTstCmpt)
       {
          if(CeIGN_ON == GetVIOS_IgnSt())
          {
              if(VbCOND_HWIO_COPTested)
              {
                 if(!GetFILE_NVM_Failure())
                 {
                    if(!GetFILE_RunningResetOccurred())
                    {  
                        if(NfCOND_t_COPEnblDlyTmr >= KfCOND_t_COPEnblDlyTmrThrsh)
                        {
                            NsCOND_COPTstData.EnblCritMet = CbTRUE;
                            SeCOND_COP_EnblStatus = CeCOND_COP_EnblCritMet;
                        }
                        else
                        {
                            SeCOND_COP_EnblStatus = CeCOND_COP_DelayTimerActive;
                            NfCOND_t_COPEnblDlyTmr = INCusp(NfCOND_t_COPEnblDlyTmr);
                            NsCOND_COPTstData.EnblCritMet = CbFALSE;
                        }
                    }
                    else
                    {
                        SeCOND_COP_EnblStatus =  CeCOND_COP_RunningReset;
                        NsCOND_COPTstData.EnblCritMet = CbFALSE;
                        NfCOND_t_COPEnblDlyTmr = V_TIME_SEC_P125(0);
                    }
                 }
                 else
                 {
                    SeCOND_COP_EnblStatus =  CeCOND_COP_NVMFailure;
                    NsCOND_COPTstData.EnblCritMet = CbFALSE;
                    NfCOND_t_COPEnblDlyTmr = V_TIME_SEC_P125(0);
                 }
              }
              else
              {
                 SeCOND_COP_EnblStatus = CeCOND_COP_NotTestedByHWIO;
                 NsCOND_ClockTstData.EnblCritMet = CbFALSE;
                 NfCOND_t_COPEnblDlyTmr = V_TIME_SEC_P125(0); 
              }
          }
          else
          {
              SeCOND_COP_EnblStatus = CeCOND_COP_IgnNotOn;
              NsCOND_COPTstData.EnblCritMet = CbFALSE;
              NfCOND_t_COPEnblDlyTmr = V_TIME_SEC_P125(0);
          }
       }
       else
       {
          SeCOND_COP_EnblStatus = CeCOND_COP_TestComplete;
          NsCOND_COPTstData.EnblCritMet = CbFALSE;
          NfCOND_t_COPEnblDlyTmr = V_TIME_SEC_P125(0);
       }
   }
   else
   {
       SeCOND_COP_EnblStatus = CeCOND_COP_DiagTypeZ;
       NsCOND_COPTstData.EnblCritMet = CbFALSE;
       NfCOND_t_COPEnblDlyTmr = V_TIME_SEC_P125(0);
   }
}

/*****************************************************************************
 * Function:        EvalCOND_COP_FailCritMet
 * Description:     This function checks if fail criteria met for Watchdog Timer(COP)
 *                  diagnostics.
 * Parameters:      None
 * Return:          None
 *****************************************************************************/
static void EvalCOND_COP_FailCritMet(void)
{
   NsCOND_COPTstData.FailCritMet = VbCOND_HWIO_COPFailed;
}

/*****************************************************************************
 * Function:        GetCOND_IO_DevFailCntr
 * Description:     This function returns IO DEVICE fail counter.
 * Parameters:      TeCOND_IO_Device
 * Return:          T_COUNT_WORD
 *****************************************************************************/
T_COUNT_WORD GetCOND_IO_DevFailCntr( TeCOND_IO_Device LeCOND_IO_Device )
{
   return( (T_COUNT_WORD )(NaCOND_Cnt_FailCntr[LeCOND_IO_Device]) );
}
#endif
/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
******************************************************************************/
