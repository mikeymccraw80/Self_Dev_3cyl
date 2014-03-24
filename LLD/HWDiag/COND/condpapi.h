#ifndef CONDPAPI_H
#define CONDPAPI_H
/******************************************************************************
 *
 * Filename:          condpapi.h
 *
 * Description:       Public output header file for COND
 *                    (Controller Diagnostic) subsystem
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2004-2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#7/incl/condpapi.h/1 %
 * %date_created:  Mon Dec 13 16:16:11 2010 %
 * %version:       1 %
 * %derived_by:    vzd0pc %
 *
 *****************************************************************************/

/******************************************************************************
 *  Global Application Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h" /* For Generic data types                            */

/******************************************************************************
 *  Configuration Include File
 *****************************************************************************/
#include "condfcfg.h"   /* For COND configuration data                       */

#if XbCOND_SUBS_SELECT_FLAG == CbSUBS_ON

#include "condptyp.h"   /* For COND public type definitions                  */
#include "dgthpall.h"   /* For TeSINGLE_TEST_STATUS                          */
#include "systpcom.h"   /* For Application specific COND function exports    */
#include "viospwdi.h"   /* For GetVIOS_MainCPU_InvalidThrotCmdWD             */
                        /*     GetVIOS_MainCPU_FaultDetectedWD               */

/*****************************************************************************
 *  Function Prototypes
 *****************************************************************************/
FARFUNC void InitCOND_RstToKeyOn(void);
FARFUNC void InitCOND_PowerOfDelayToKeyOn(void);
FARFUNC void InitCOND_ShutdownInProgToKeyOn(void);
FARFUNC void InitCOND_OFVC_Clear(void);
FARFUNC void MngCOND_31p2msTasks(void);
FARFUNC void MngCOND_125msTasks(void);

#if XeCOND_ETC_CHECKING_CPU_TYPE != CeCOND_ETC_CHECKING_CPU_IS_NONE
FARFUNC void MngCOND_CheckCPU_15p6Tasks(void);
FARFUNC void MngCOND_CheckCPU_31p2Tasks(void);
FARFUNC void MngCOND_CheckCPU_125Tasks(void);
FARFUNC void PerformCOND_CheckCPU_ResetKeyOn(void);
FARFUNC void PerformCOND_CheckCPU_PwrdnDlyToKeyOn(void);
FARFUNC void PerformCOND_CheckCPU_ShutDnToKeyOn(void);
#else /* XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_NONE */
#define MngCOND_CheckCPU_15p6Tasks           DefineOSTK_EmptyFunction
#define MngCOND_CheckCPU_31p2Tasks           DefineOSTK_EmptyFunction
#define MngCOND_CheckCPU_125Tasks            DefineOSTK_EmptyFunction
#define PerformCOND_CheckCPU_ResetKeyOn      DefineOSTK_EmptyFunction
#define PerformCOND_CheckCPU_PwrdnDlyToKeyOn DefineOSTK_EmptyFunction
#define PerformCOND_CheckCPU_ShutDnToKeyOn   DefineOSTK_EmptyFunction
#endif /* XeCOND_ETC_CHECKING_CPU_TYPE */

#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
FARFUNC void MngCOND_AD_InputResp15p6msTasksA(void);
FARFUNC void MngCOND_AD_InputResp15p6msTasksB(void);
#else
INLINE void MngCOND_AD_InputResp15p6msTasksA(void) {}
INLINE void MngCOND_AD_InputResp15p6msTasksB(void) {}
#endif

#if XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE
FARFUNC void ProcessCOND_ADC_0_Output(void);
FARFUNC void ProcessCOND_ADC_1_Output(void);
FARFUNC void ProcessCOND_GPR_Output(void);
FARFUNC void ProcessCOND_TPIC6_0_Output(void);
FARFUNC void ProcessCOND_TPIC6_1_Output(void);
FARFUNC void ProcessCOND_TPIC6_2_Output(void);
FARFUNC void ProcessCOND_TPIC6_3_Output(void);
FARFUNC void ProcessCOND_LPC_ClockOutput(void);
FARFUNC void ProcessCOND_MainCPU_ClockFault(void);
FARFUNC void ProcessCOND_WDOG_TimerFault(void);
#else
#define ProcessCOND_ADC_0_Output             DefineOSTK_EmptyFunction
#define ProcessCOND_ADC_1_Output             DefineOSTK_EmptyFunction
#define ProcessCOND_GPR_Output               DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_0_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_1_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_2_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_TPIC6_3_Output           DefineOSTK_EmptyFunction
#define ProcessCOND_LPC_ClockOutput          DefineOSTK_EmptyFunction
#define ProcessCOND_MainCPU_ClockFault       DefineOSTK_EmptyFunction
#define ProcessCOND_WDOG_TimerFault          DefineOSTK_EmptyFunction
#endif

/*****************************************************************************
 *  Variable/Calibration Exports
 *****************************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC

extern T_COUNT_WORD NcCOND_CPU_InitMsgBadCount;
extern T_COUNT_WORD NcCOND_CPU_NormMsgBadCount;
extern LONGWORD     NgCOND_CPU_MsgRcvWhenOutputDsbld;

#elif XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_SOH

extern WORD         NwCOND_SOH_FltLongTermHist;
extern T_COUNT_WORD NcCOND_SOH_FltCntLongTerm;

#endif

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_TORQUE
extern TbBOOLEAN        NbCOND_SequencingErrorOccThisReset;
#endif

extern const T_VOLTb      CAL0ADDR KfCOND_U_LPI_IFB_CommSysThrshLo;
extern const T_COUNT_WORD CAL0ADDR KcCOND_ECM_LPI_IFB_FailThrsh;
extern const T_COUNT_WORD CAL0ADDR KcCOND_ECM_LPI_IFB_SmplThrsh;


/****************************************************************************
* Function Name:           GetCOND_SequencingTestStatReport
* Description:             Provides Interface Get For
*                          VeCOND_SequencingTestStatReport.
* Input Parameters:        None
* Return Data:             VeCOND_SequencingTestStatReport
* Return Data Type:        TeSINGLE_TEST_STATUS
* Return Data Size:        4 bytes
* Return Data Resolution:  N/A
* Return Data Eng. Range:  ENUM
* Update Rate:             125ms
****************************************************************************/
#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_TORQUE
extern TeSINGLE_TEST_STATUS VOL0ADDR VeCOND_SequencingTestStatReport;
#define GetCOND_SequencingTestStatReport()\
    (VeCOND_SequencingTestStatReport)

#else
#define GetCOND_SequencingTestStatReport()\
    (CeSINGLE_NULL)
#endif

#if (XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT) \
 && (XeSYST_ETC_WatchdogCPU_HW == CeSYST_ETC_WatchdogCPU_Present)

/*This function is not used in API layer, compile out for WDOG not present*/

/****************************************************************************
* Function Name:           GetCOND_CmndThrotCircuitStateWD
* Description:             Provides Interface Get For
*                          VeCOND_CmndThrotCircuitStateWD.
* Input Parameters:        None
* Return Data:             VeCOND_CmndThrotCircuitStateWD
* Return Data Type:        TbENBL
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbDISABLED
*                          CbENABLED
* Update Rate:             125ms
****************************************************************************/
extern TbENBL    VOL0ADDR VeCOND_CmndThrotCircuitStateWD;
#define GetCOND_CmndThrotCircuitStateWD()\
    (VeCOND_CmndThrotCircuitStateWD)

/*This function is not used in API layer, compile out for WDOG not present*/

/****************************************************************************
* Function Name:           GetCOND_ThrotCirDsblTestInProgress
* Description:             Provides Interface Get For
*                          VbCOND_ThrotCirDsblTestInProgress.
* Input Parameters:        None
* Return Data:             VbCOND_ThrotCirDsblTestInProgress
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/
extern TbBOOLEAN VOL0ADDR VbCOND_ThrotCirDsblTestInProgress;
#define GetCOND_ThrotCirDsblTestInProgress()\
    (VbCOND_ThrotCirDsblTestInProgress)

#else

#define GetCOND_CmndThrotCircuitStateWD()\
    (CbFALSE)
#define GetCOND_ThrotCirDsblTestInProgress()\
    (CbFALSE)

#endif /* XeSYST_LOAD_CNTRL_TYPE, XeSYST_ETC_WatchdogCPU_HW */

/* STUB functions */
#define GetSTUB_COND_WD_CPU_InternalFaultPresent()\
    (CbFALSE)

#define GetSTUB_COND_MainCPU_AD_TestFailed()\
    (CbFALSE)

#define GetSTUB_COND_SPI_InterprocessorCommTestFailed()\
    (CbFALSE)

#define GetSTUB_HWIO_CPU_RegisterTestFailed()\
    (CbFALSE)

/* End of STUB functions */

/****************************************************************************
* Function Name:           GetCOND_MainCPU_AD_TestFailed
* Description:             Provides Interface Get For
*                          VbCOND_MainCPU_AD_TestFailed.
* Input Parameters:        None
* Return Data:             VbCOND_MainCPU_AD_TestFailed
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/
#if (XeSYST_LOAD_CNTRL_TYPE != CeSYST_MECHANICAL_THROT)
    #if (XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE)
        extern TbBOOLEAN VOL0ADDR  VbCOND_MainCPU_AD_TestFailed;
        #define GetCOND_MainCPU_AD_TestFailed() \
            (VbCOND_MainCPU_AD_TestFailed)
    #else
        #define GetCOND_MainCPU_AD_TestFailed() \
            (CbFALSE)
    #endif /* XeSYST_CONTROLLER_DIAG */
#else
    #define GetCOND_MainCPU_AD_TestFailed() \
        (CbFALSE)
#endif /* XeSYST_LOAD_CNTRL_TYPE */

/****************************************************************************
* Function Name:           GetCOND_MainCPU_AD_TestFailed
* Description:             Provides Interface Get For
*                          GetVIOS_MainCPU_FaultDetectedWD.
* Input Parameters:        None
* Return Data:             GetVIOS_MainCPU_FaultDetectedWD
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT
#define GetCOND_MainCPU_FaultDetectedWD() \
            (GetVIOS_MainCPU_FaultDetectedWD())
#else
#define GetCOND_MainCPU_FaultDetectedWD() (CbFALSE)
#endif /* XeSYST_LOAD_CNTRL_TYPE */

/* STUB functions */

#define GetCOND_MainCPUInstructionSetTestFailed()\
    (CbFALSE)

#define GetCOND_MainCPU_InterruptTestFailed()\
    (CbFALSE)

/* End of STUB functions */

/****************************************************************************
* Function Name:           GetCOND_MainCPU_InvalidThrotCmdWD
* Description:             Provides Interface Get For
*                          GetVIOS_MainCPU_InvalidThrotCmdWD.
* Input Parameters:        None
* Return Data:             GetVIOS_MainCPU_InvalidThrotCmdWD
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT
#define GetCOND_MainCPU_InvalidThrotCmdWD() \
            (GetVIOS_MainCPU_InvalidThrotCmdWD())
#else
#define GetCOND_MainCPU_InvalidThrotCmdWD() (CbFALSE)
#endif /* XeSYST_LOAD_CNTRL_TYPE */

/****************************************************************************
* Function Name:           GetCOND_MainCPU_RegisterTestFailed
* Description:             Provides Interface Get For
*                          VbCOND_MainCPU_RegisterTestFailed.
* Input Parameters:        None
* Return Data:             VbCOND_MainCPU_RegisterTestFailed
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/

extern TbBOOLEAN VOL0ADDR  VbCOND_MainCPU_RegisterTestFailed;

#if (XeSYST_LOAD_CNTRL_TYPE != CeSYST_MECHANICAL_THROT)
    #if (XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE)
      #define GetCOND_MainCPU_RegisterTestFailed() \
          (VbCOND_MainCPU_RegisterTestFailed)
   #else
      #define GetCOND_MainCPU_RegisterTestFailed() \
      (CbFALSE)
   #endif /* XeSYST_CONTROLLER_DIAG */
#else
     #define GetCOND_MainCPU_RegisterTestFailed() \
     (CbFALSE)
#endif /* XeSYST_LOAD_CNTRL_TYPE */

/****************************************************************************
* Function Name:           GetCOND_MainToWD_SoftwareVersionFault
* Description:             Provides Interface Get For
*                          VbCOND_SW_VersionTestFailed.
* Input Parameters:        None
* Return Data:             VbCOND_SW_VersionTestFailed
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/

#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
extern TbBOOLEAN  VOL0ADDR VbCOND_SW_VersionTestFailed;
#define GetCOND_MainToWD_SoftwareVersionFault() (VbCOND_SW_VersionTestFailed)
#else
#define GetCOND_MainToWD_SoftwareVersionFault() (CbFALSE)
#endif

/****************************************************************************
* Function Name:           GetCOND_MainToWD_SoftwareVerFailCritMet
* Description:             Provides Interface Get For
*                          VbCOND_SW_VersionFailCritMet.
* Input Parameters:        None
* Return Data:             VbCOND_SW_VersionFailCritMet
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
extern TbBOOLEAN  VOL0ADDR VbCOND_SW_VersionFailCritMet;
#define GetCOND_MainToWD_SoftwareVerFailCritMet() (VbCOND_SW_VersionFailCritMet)
#else
#define GetCOND_MainToWD_SoftwareVerFailCritMet() (CbFALSE)
#endif

/* STUB functions */

#define GetCOND_ETCDriverOutputTestFailed()\
    (CbFALSE)

#define GetCOND_OperatingSystemTestFailed()\
    (CbFALSE)

/* End of STUB functions */

/****************************************************************************
* Function Name:           GetCOND_ProcessSequencingTestFailed
* Description:             Provides Interface Get For
*                          NbCOND_SequencingTestFailed.
* Input Parameters:        None
* Return Data:             NbCOND_SequencingTestFailed
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/
extern TbBOOLEAN        NbCOND_SequencingTestFailed;
#if XeSYST_LOAD_CNTRL_TYPE != CeSYST_MECHANICAL_THROT
#define GetCOND_ProcessSequencingTestFailed() \
   (NbCOND_SequencingTestFailed)
#else
#define GetCOND_ProcessSequencingTestFailed() \
   (CbFALSE)
#endif

/****************************************************************************
* Function Name:           GetCOND_SPI_InterprocessorCommTestFailed
* Description:             Provides Interface Get For boolean indicating
*                          SPI Interprocessor Communication Test Failed.
* Input Parameters:        None
* Return Data:
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT
        #define GetCOND_SPI_InterprocessorCommTestFailed() \
            (GetSTUB_COND_SPI_InterprocessorCommTestFailed())
#else
    #define GetCOND_SPI_InterprocessorCommTestFailed() \
        (CbFALSE)
#endif /* XeSYST_LOAD_CNTRL_TYPE */

/* STUB function */
#define GetCOND_ThrotMotorDriveCircuitFault()\
    (CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_WD_CPU_InternalFaultPresent
* Description:             Provides Interface Get For
*                          VbCOND_WD_CPU_InternalFaultPresent.
* Input Parameters:        None
* Return Data:             VbCOND_WD_CPU_InternalFaultPresent
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             31.2ms
****************************************************************************/
#if XeSYST_ETC_WatchdogCPU_HW == CeSYST_ETC_WatchdogCPU_Present
extern TbBOOLEAN  VOL0ADDR VbCOND_WD_CPU_InternalFaultPresent;
#endif
#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT
  #if XeSYST_ETC_WatchdogCPU_HW == CeSYST_ETC_WatchdogCPU_Present
    #define  GetCOND_WD_CPU_InternalFaultPresent() \
        (VbCOND_WD_CPU_InternalFaultPresent)
  #else
       #define  GetCOND_WD_CPU_InternalFaultPresent() \
          (GetSTUB_COND_WD_CPU_InternalFaultPresent())
  #endif /* XeSYST_ETC_WatchdogCPU_HW */
#else
   #define  GetCOND_WD_CPU_InternalFaultPresent() \
        (CbFALSE)
#endif /* XeSYST_LOAD_CNTRL_TYPE */

/* STUB function */

#define GetCOND_WD_DetectsMainCPU_EngShutdown()\
    (CbFALSE)

#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
extern TsCOND_CheckCPU_Status   VOL0ADDR VsCOND_CheckCPU_Status;
extern TeCOND_CHECKCPU_OPSTATUS VOL0ADDR VeCOND_CheckCPU_OpStatus;

/* Begin COND PIC communications interface functions */

/****************************************************************************
* Function Name:           GetCOND_PIC_CommForMainCPU_OpStIsPending
* Description:             Returns boolean based on the evaluation of
*                          VeCOND_CheckCPU_OpStatus equal to
*                          CeCOND_CPU_OP_STAT_PENDING.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_CommForMainCPU_OpStIsPending()\
    (VeCOND_CheckCPU_OpStatus == CeCOND_CPU_OP_STAT_PENDING)

/****************************************************************************
* Function Name:           GetCOND_PIC_CommForMainCPU_OpStIsOk
* Description:             Returns boolean based on the evaluation of
*                          VeCOND_CheckCPU_OpStatus equal to
*                          CeCOND_CPU_OP_STAT_OK.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_CommForMainCPU_OpStIsOk()\
    (VeCOND_CheckCPU_OpStatus == CeCOND_CPU_OP_STAT_OK)

/****************************************************************************
* Function Name:           GetCOND_PIC_CommForMainCPU_OpStIsFail
* Description:             Returns boolean based on the evaluation of
*                          VeCOND_CheckCPU_OpStatus equal to
*                          CeCOND_CPU_OP_STAT_FAIL.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_CommForMainCPU_OpStIsFail()\
    (VeCOND_CheckCPU_OpStatus == CeCOND_CPU_OP_STAT_FAIL)

/****************************************************************************
* Function Name:           GetCOND_PIC_DisabledOutputs
* Description:             Returns boolean based on the value of
*                          VbCOND_DisabledOutputs.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_DisabledOutputs()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_DisabledOutputs != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_PauseSeqFault
* Description:             Returns boolean based on the value of
*                          VbCOND_PauseSeqFault.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_PauseSeqFault()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_PauseSeqFault != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_ShutOffTimerActive
* Description:             Returns boolean based on the value of
*                          VbCOND_ShutTmr.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_ShutOffTimerActive()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_ShutTmr != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_CommFaultByPIC
* Description:             Returns boolean based on the value of
*                          VbCOND_CommFaultByPIC.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_CommFaultByPIC()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_CommFaultByPIC != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_PWM_Fault
* Description:             Returns boolean based on the value of
*                          VbCOND_PWM_Fault.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_PWM_Fault()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_PWM_Fault != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_PICLK_Fault
* Description:             Returns boolean based on the value of
*                          VbCOND_PICLK_Fault.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_PICLK_Fault()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_PICLK_Fault != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_CommFaultByMain
* Description:             Returns boolean based on the value of
*                          VbCOND_CommFaultByMain.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/

#define GetCOND_PIC_CommFaultByMain()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_CommFaultByMain != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_LastNormPIC_MsgOK
* Description:             Returns boolean based on the value of
*                          VbCOND_LastNormPIC_MsgOK.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/
#define GetCOND_LastNormPIC_MsgOK()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_LastNormPIC_MsgOK != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_MsgError
* Description:             Returns boolean based on the value of
*                          VbCOND_PIC_MsgError.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/
#define GetCOND_PIC_MsgError()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_PIC_MsgError != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_PIC_InitMsg
* Description:             Returns boolean based on the value of
*                          VbCOND_PIC_InitMsg.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/
#define GetCOND_PIC_InitMsg()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_PIC_InitMsg != CbFALSE)

/****************************************************************************
* Function Name:           GetCOND_SU_BatVltgStabDelayActv
* Description:             Returns boolean based on the value of
*                          COND_SU_BatVltgStabDelayActv.
* Input Parameters:        None
* Return Data:             NA
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             NA
****************************************************************************/
#define GetCOND_SU_BatVltgStabDelayActv()\
    (VsCOND_CheckCPU_Status.flags.VbCOND_SU_BatVltgStabDelayActv != CbFALSE)

/* End COND PIC communications interface functions */

#else

/* Begin COND PIC communications dummy interface functions */

#define GetCOND_PIC_CommForMainCPU_OpStIsPending() (CbFALSE)
#define GetCOND_PIC_CommForMainCPU_OpStIsOk() (CbTRUE)
#define GetCOND_PIC_CommForMainCPU_OpStIsFail() (CbFALSE)
#define GetCOND_PIC_DisabledOutputs() (CbFALSE)
#define GetCOND_PIC_PauseSeqFault() (CbFALSE)
#define GetCOND_PIC_ShutOffTimerActive() (CbFALSE)
#define GetCOND_PIC_CommFaultByPIC() (CbFALSE)
#define GetCOND_PIC_PWM_Fault() (CbFALSE)
#define GetCOND_PIC_PICLK_Fault() (CbFALSE)
#define GetCOND_PIC_CommFaultByMain() (CbFALSE)
#define GetCOND_LastNormPIC_MsgOK() (CbFALSE)
#define GetCOND_PIC_MsgError() (CbFALSE)
#define GetCOND_PIC_InitMsg() (CbFALSE)
#define GetCOND_SU_BatVltgStabDelayActv() (CbFALSE)

#endif
/* End COND PIC communications dummy interface functions */

/****************************************************************************
* Function Name:           GetCOND_MainCPU_ClockPerfTestFailed
* Description:             Provides Interface Get For
*                          VbCOND_MainCPU_ClockPerfTestFailed.
* Input Parameters:        None
* Return Data:             VbCOND_MainCPU_ClockPerfTestFailed
* Return Data Type:        TbBOOLEAN
* Return Data Size:        1 byte
* Return Data Resolution:  1
* Return Data Eng. Range:  CbFALSE
*                          CbTRUE
* Update Rate:             125ms
****************************************************************************/

extern TbBOOLEAN VOL0ADDR  VbCOND_MainCPU_ClockPerfTestFailed;
#if (XeSYST_LOAD_CNTRL_TYPE != CeSYST_MECHANICAL_THROT)
    #if (XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE)
        #define GetCOND_MainCPU_ClockPerfTestFailed() \
            (VbCOND_MainCPU_ClockPerfTestFailed)
    #else
        #define GetCOND_MainCPU_ClockPerfTestFailed() \
            (CbFALSE)
    #endif
#else
    #define GetCOND_MainCPU_ClockPerfTestFailed() \
        (CbFALSE)
#endif

#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_CORRELATION
   extern TbBOOLEAN VaCOND_AD_InptCorrTestFailedAnlg[CcCOND_NumOfADC];
   #define GetCOND_AD_InptCorrTestFailedAnlg(LcCOND_TestIndex) \
      (VaCOND_AD_InptCorrTestFailedAnlg[LcCOND_TestIndex])
#else
   #define GetCOND_AD_InptCorrTestFailedAnlg(LcCOND_TestIndex) \
      (CbFALSE)
#endif

/******************************************************************************
 * Function Name:                  GetCOND_AD_RespAPS1_SlowRec
 * Description:                    A/D input response diagnostic indicates
 *                                 APS1 signal is slow to recover from short
 *                                 to ground.
 * Input Parameters:               None
 * Return Data:                    VbCOND_AD_RespAPS1_SlowRec
 * Return Data Type Name:          TbBOOLEAN
 * Return Data Size:               1B
 * Return Data Resoultion:         n/a
 * Return Data Eng. Range:         n/a
 * Update Rate:                    15.6 ms
 *****************************************************************************/
#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
   extern TbBOOLEAN VOL0ADDR  VbCOND_AD_RespAPS1_SlowRec;
   #define GetCOND_AD_RespAPS1_SlowRec() \
      (VbCOND_AD_RespAPS1_SlowRec)
#else
   #define GetCOND_AD_RespAPS1_SlowRec() \
      (CbFALSE)
#endif

/******************************************************************************
 * Function Name:                  GetCOND_AD_RespAPS_ShortTogether
 * Description:                    A/D input response diagnostic indicates
 *                                 APS1 and APS2 signals are electrically coupled.
 * Input Parameters:               None
 * Return Data:                    VbCOND_AD_RespAPS_ShortTogether
 * Return Data Type Name:          TbBOOLEAN
 * Return Data Size:               1B
 * Return Data Resoultion:         n/a
 * Return Data Eng. Range:         n/a
 * Update Rate:                    15.6 ms
 *****************************************************************************/
#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
   extern TbBOOLEAN VOL0ADDR  VbCOND_AD_RespAPS_ShortTogether;
   #define GetCOND_AD_RespAPS_ShortTogether() \
      (VbCOND_AD_RespAPS_ShortTogether)
#else
   #define GetCOND_AD_RespAPS_ShortTogether() \
      (CbFALSE)
#endif

/******************************************************************************
 * Function Name:                  GetCOND_AD_RespTstFld
 * Description:                    A/D input response diagnostic test failed.
 * Input Parameters:               None
 * Return Data:                    SsCOND_AD_RespTstData.TstFailed
 * Return Data Type Name:          TbBOOLEAN
 * Return Data Size:               1B
 * Return Data Resoultion:         n/a
 * Return Data Eng. Range:         n/a
 * Update Rate:                    n/a
 *****************************************************************************/
#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
   FARFUNC TbBOOLEAN  GetCOND_AD_RespTstFld(void);
#else
   #define GetCOND_AD_RespTstFld() \
      (CbFALSE)
#endif

/******************************************************************************
 * Function Name:                  GetCOND_AD_RespETC_LrnDwnDsblCritMet
 * Description:                    A/D input response diagnostic
 *                                 ETC learing down disable criteria met.
 * Input Parameters:               LfCOND_t_ETC_APS_MinLrnDsblDly
 * Return Data:                    n/a
 * Return Data Type Name:          TbBOOLEAN
 * Return Data Size:               1B
 * Return Data Resoultion:         n/a
 * Return Data Eng. Range:         n/a
 * Update Rate:                    n/a
 *****************************************************************************/
#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
   FARFUNC TbBOOLEAN  GetCOND_AD_RespETC_LrnDwnDsblCritMet(
                          const T_COND_TIME_SEC_0_16 LfCOND_t_ETC_APS_MinLrnDsblDly );
#else
   #define GetCOND_AD_RespETC_LrnDwnDsblCritMet(LfCOND_t_ETC_APS_MinLrnDsblDly) \
      (CbFALSE)
#endif

/******************************************************************************
 * Function Name:                  GetCOND_AD_RespETC_DoNotUseAPS_Data
 * Description:                    A/D input response diagnostic
 *                                 ETC "do not use APS data" indication.
 * Input Parameters:               LfCOND_t_ETC_NotShortSettleMin
 * Return Data:                    n/a
 * Return Data Type Name:          TbBOOLEAN
 * Return Data Size:               1B
 * Return Data Resoultion:         n/a
 * Return Data Eng. Range:         n/a
 * Update Rate:                    n/a
 *****************************************************************************/
#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
   FARFUNC TbBOOLEAN  GetCOND_AD_RespETC_DoNotUseAPS_Data(
                          const T_COND_TIME_SEC_0_16 LfCOND_t_ETC_NotShortSettleMin );
#else
   #define GetCOND_AD_RespETC_DoNotUseAPS_Data(LfCOND_t_ETC_NotShortSettleMin) \
      (CbFALSE)
#endif

/******************************************************************************
 * Function Name:                  GetCOND_IO_DevFailCntr
 * Description:                    This function returns IO DEVICE fail counter.
 * Input Parameters:               LeCOND_IO_Device IO DEVICE id
 * Return Data:                    COND_Cnt_FailCntr[LeCOND_IO_Device]
 * Return Data Type Name:          T_COUNT_WORD
 * Return Data Size:               2B
 * Return Data Resoultion:         1
 * Return Data Eng. Range:         0 to 65536
 * Update Rate:                    125 ms
 *****************************************************************************/
#if XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE
   FARFUNC T_COUNT_WORD GetCOND_IO_DevFailCntr( TeCOND_IO_Device LeCOND_IO_Device );
#else
   #define GetCOND_IO_DevFailCntr(LeCOND_IO_Device) \
      (V_COUNT_WORD(0))
#endif

#else /* Else of XbCOND_SUBS_SELECT_FLAG = CbSUBS_OFF */

/******************************************************************************
 *  Subsystem Default File
 *****************************************************************************/

#include "condfdfl.h"

#endif /* End of XbCOND_SUBS_SELECT_FLAG = CbSUBS_OFF */

#endif /* CONDPAPI_H */

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   040727 akk 4073 Created file for modularisation of COND sub system.
* tci_pt3#2
*       040913 spm 4396 Making Code Cosmic Compatible - second phase.
* tci_pt3#3
*       040927  pd xxxx Merged parallel versions
* tcb_pt1#4
*       041124 woz 4538 Removed ProcessCOND_MLRE_0_Output prototype.
*       050304 kan 4853 Removed XeSYST_CONTROLLER_ForETC
* 5.0   050324 caw 4909 Added: GetCOND_PIC_CommForMainCPU_OpStIsPending
*                              GetCOND_PIC_CommForMainCPU_OpStIsOk
*                              GetCOND_PIC_CommForMainCPU_OpStIsFail
*                              GetCOND_LastNormPIC_MsgOK
*                              GetCOND_PIC_MsgOK
*                              GetCOND_PIC_InitMsg
*                              GetCOND_SU_BatVltgStabDelayActv
*                              GetCOND_MainToWD_SoftwareVerFailCritMet
*                       Removed: GetCOND_PIC_FuelETC_Disabled
* tcb_pt1#5.1.1
*       050401 sai 5031 Included condstyp.h, externed
*                         VaCOND_AD_InptCorrTestFailedAnlg,
*                         Added GetCOND_AD_InptCorrTestFailedAnlg(x)
* 6.0 050405 at -BM- Merge
* 7.0 050405 at -BM- Merge
*       050415 sai 5031 Added GetCOND_AD_InptCorrTestFailedAnlg() and
*                         included condstyp.h
* 4.2.2.1.1
*       061010 kvm 5837 Removed declarations for KcCOND_ECM_TRN_MIL_FailThrsh
*                                                KcCOND_ECM_TRN_MIL_SmplThrsh
* 4.2.2.2.1
*       061026 hdb 5837 Move cals defined in COND to TRND subsystem:
*                         Moved and renamed KcCOND_ECM_TRN_MIL_FailThrsh
*                                           KcCOND_ECM_TRN_MIL_SmplThrsh
*                         to trndcald
* tcb_pt1#4.2.2.1.1.2.1
*       070130 gps -BM- CORE : Include Header Files Optimization.
*                       Installed non-functional changes.
* 4.2.2.1.3 070205 at  -BM- Merged compile time improvement
* 4.2.2.1.1.1.1
*       070108 MCB 5340 Changed XeSYST_LOAD_CNTRL_TYPE && CeSYST_MECHANICAL_THROT
*                       to XeCOND_ETC_CHECKING_CPU_TYPE.  Added to #conditional
*                       XeSYST_LOAD_CNTRL_TYPE the PIC controller
*                       XeCOND_ETC_CHECKING_CPU_TYPE ANDed to XeSYST_CONTROLLER_DIAG
*                       XeCOND_SYST_CONTROLLER_DIAG_TYPE, CeCOND_SYST_CONTROLLER_IS_MT34
* 4.2.2.1.1.1.2
*       070206 MCB 5340 Removed under #conditional of XeSYST_LOAD_CNTRL_TYPE
*                        the PIC controller XeCOND_ETC_CHECKING_CPU_TYPE
* 4.3   070219 mcb -BM- Merged condpapi.h-tcb_pt1#4.2.2.1.3
*                        with condpapi.h-tcb_pt1#4.2.2.1.1.1.2
* 4.2.2.1.1.1.3
*       070219 gps 5481 COND: Support Gen 3 ETC Checking CPU (VSEP). CORE Part.
*                       Added COND ETC SOH externals.
*                       Removed PerformCOND_CheckCPU_OFVC_Clear.
* tcb_pt1#4.4
*       070312 gps -BM- Merged 'condpapi.h-tcb_pt1#4.3'
*                        with 'condpapi.h-tcb_pt1#4.2.2.1.1.1.3'.
* tcb_pt1#4.2.2.1.1.1.4
*       070305 gps 5202 COND: Validate APS Inputs Using Short to Ground Method.
*                       Added new set of get-calls. Cleanup.
* tcb_pt1#4.5
*       070425 gps -BM- Merged 'condpapi.h-tcb_pt1#4.4'
*                        with 'condpapi.h-tcb_pt1#4.2.2.1.1.1.4'.
* 4.6
*       070427 at -BM- Fixed build error for RSM5202
* tcb_pt1#4.4.1
*       070610 me  6085 Added InitCOND_Device_OFVC_Clear.
* 4.7
*       070618 me  xxxx Merged from 'condpapi.h-tcb_pt1#4.6' and 
*                       'condpapi.h-tcb_pt1#4.4.1'.
* 4.5   070801 me  6250 Returned the correct value of 
*                       GetCOND_ProcessSequencingTestFailed 
*                       when load control type is not mechanical throttle.
* tcb_pt1#4.7.1.1
*       071204 gps 6703 ETCD, ETCI: TPS Noise Robustness, part 2.
* 4.6   080410 hdb 6464 Adjust for member name changes in TsOBDU_DiagTstData.
* 8     080416 hdb      Merge condpapi.h~tcb_pt1#4.8.1.1 with
*                             condpapi.h~tcb_pt1#4.10
*
******************************************************************************/
