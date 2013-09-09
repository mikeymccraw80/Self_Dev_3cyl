/*===========================================================================*\
 * FILE: soh.c
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh.c~3:csrc:ctc_pt3#2 %
 * %version: 3 %
 * %derived_by:  zzrfyj %
 * %date_modified:    %
 * $SOURCE: $
 * $REVISION: $
 * $AUTHOR: $
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *   ETC SOH building block software.
 *   Used in conjunction with ASIC (VSEP, MIO) with state-of-health (SOH) logic.
 *
 *   The SOH tests consists of two parts:
 *      1) Generic tests - in file soh.c
 *      2) Microprocessor specific tests - in file soh_tc17xx.c
 *   (for Infineon TC1762, TC1765, TC1766, TC1775, TC1792, TC1796.)
 *
 * ABBREVIATIONS:
 *   Documented in the design and requirement documents.
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     SDD_10012894_002_xxx.doc
 *
 *   Requirements Document(s):
 *     REQ_10012894_002_xxx.doc
 *
 *   Applicable Standards (in order of precedence: highest first):
 *     SW REF 264.15D "Delphi C Coding Standards" [23-Dec-2001]
 *
 * DEVIATIONS FROM STANDARDS:
 *   [C163] DEVIATION: MULTIPLE RETURN VALUES!
 *
 \*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
 \*===========================================================================*/
#include "soh_common.h"
//#include "io_scale.h"
#include "io_config_tpu.h"
#include "soh_mpc56xx.h"
#include "soh_cald.h"
#include "io_conversion.h"
#include "soh.h"
#include "dd_dma.h"
#include "dd_VSEP_soh.h"
#include "soh_nvm.h"
#include "hal_soh.h"
#include "io_config_siu.h"
#include "dd_siu.h"


/*===========================================================================*\
 * Cofingrable Marcos
 \*===========================================================================*/
#define REFCLK_FREQ_ERR                         ( 0.075 )
#define SOHIRQTIME_ERR                          ( 0.100 )
#define SOH_SHUTOFF_PERIOD_MS					( 187.50 )

/* the following macros are expressed in computer unit */
#define REFCLK_FREQ_HIGH						( (uint16_t)(REFCLK_FREQ_HZ * (1 + REFCLK_FREQ_ERR)) )
#define REFCLK_FREQ_LOW 						( (uint16_t)(REFCLK_FREQ_HZ * (1 - REFCLK_FREQ_ERR)) )

#define SOHIRQTEST_PERIOD						( V_SOH_TMR_MSEC_T(SOH_RUNTEST_PERIOD_MS) )
#define SOHIRQTIME_PERIOD_HIGH					( (uint16_t)(SOHIRQTEST_PERIOD * (1 + SOHIRQTIME_ERR)) )
#define SOHIRQTIME_PERIOD_LOW					( (uint16_t)(SOHIRQTEST_PERIOD * (1 - SOHIRQTIME_ERR)) )

#define MAJLOOPTIME_HIGH						( V_SOH_TMR_MSEC_T(MAJLOOPTIME_TYPICAL) + KSOHRTITH)
#define MAJLOOPTIME_LOW							( V_SOH_TMR_MSEC_T(MAJLOOPTIME_TYPICAL) - KSOHRTITH)

#define SOH_SHUTOFFTIME		  					( (uint8_t)( SOH_SHUTOFF_PERIOD_MS / SOH_IRQ_PERIOD_MS ) )

#define SOH_RTI_PERIOD							( V_SOH_TMR_MSEC_T(Base_Loop_Time_mS) )

#define IsEven(number)							( ((number) & 0x01) == 0 )
#define IsOdd(number)							( ((number) & 0x01) == 1 )

#define SOH_ERRCOUNT_INC						( 5 )   /* SOH test error counter increment step size */
#define SOH_ERRCOUNT_DEC						( 1 )   /* SOH test error counter decrement step size */

#define SOH_TEST_NO_ERR					   	    ( 0x0000 )


Soh_Test_Result_T        Soh_TestResult;
Soh_Test_Result_T        Soh_TestErr;
Soh_Test_Completion_T    Soh_TestComp;
Soh_CnR_Value_T          Soh_CnRValue;
Soh_CnR_Status_T         Soh_CnRStatus;
Soh_Fault_Log_T          Soh_FaultLog;
bool                     Soh_RecoverMode;  /* 0: ETC SOH recovery completed or not in recovery mode
                                              1: start ETC SOH recovery */


static uint8_t        Soh_LoopCnt; /* SOH loop counter used to identify odd or even loop */
static uint8_t        Soh_LoopSeq[SOH_LOOPSEQBUFSZ]; /* Store major loop sequence ID tag */
static uint8_t        Soh_SchdLoopSeqIdx; /* Major loop sequence array index - application */
static uint8_t        Soh_IrqLoopSeqIdx; /* Major loop sequence array index - ETC SOH */
static uint8_t        Soh_IdTagExpect;
static uint8_t        Soh_OddErrCnt;
static uint8_t        Soh_EvenErrCnt;
static uint8_t        Soh_ShutOffUpTimer;
static uint8_t        Soh_ShutOffDnTimer;
static SOH_TMR_MSEC_T Soh_RtiLoopTime[SOH_RTIBUFSZ]; /* Store time of occurrence of RTI loop */
static uint8_t        Soh_RtiCirBufIdx;  /* RTI loop time array index */
static uint8_t        Soh_LstRtiCirBufIdx; /* Last RTI loop time array index */
static uint32_t       Soh_LstIrq_Time;
bool VbHWIO_SOH_Running;
bool VbHWIO_VSEP_Initialized;

const TPU_CHANNEL_Configuration_T   SOH_INTERNAL_TIME_BASE_CONFIG =
{
   0,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   0,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   0,  //1  //Interrupt Request Enable
   0,   //Transfer Request Enable
   0,  // Channel Priority Index
   0,  //    Active state of channel
   0,            //       8   Output Disable
   0,                 //   Host Service Request Type
   0          //   TPU Primitives or Channel function Select
  
};


void RequestIO_Software_Reset( void )
{
   INTC_EXCEPTION_Halt();
}

/*=============================================================================
 * ValidateSysClkFreq
 * @func This function validates the system clock by comparing the external 32khz
 *       clock with TPU TCR1 timer 
 * @parm  
 * @rdesc  
 *===========================================================================*/
static void ValidateSysClkFreq(void)
{
	uint32_t s_time_stamp,e_time_stamp;
	uint32_t soh_ref_freq;
	
	uint8_t current_dma_idx;
	uint8_t start_dma_idx;

   SOH_Enter_Critical_Section();

    current_dma_idx = Get_Current_DMA_idx(DMA_A.TCD[0x18].F.F_6.F.CITER);
    start_dma_idx = Get_Start_DMA_idx(current_dma_idx);

    e_time_stamp = SOH_DMA_External_Ref_Time[current_dma_idx];
    s_time_stamp = SOH_DMA_External_Ref_Time[start_dma_idx];

    if (e_time_stamp >= s_time_stamp) 
    {
        soh_ref_freq = (NUMBER_OF_SAMPLE_POINT - 1) * TPU_A_TCR1_CLOCK_FREQ/(e_time_stamp - s_time_stamp);
    }
    else 
    {
        soh_ref_freq = (NUMBER_OF_SAMPLE_POINT - 1) * TPU_A_TCR1_CLOCK_FREQ/(SOH_INTERNAL_TIME_BASE_OVERFLOW_VALUE - s_time_stamp + e_time_stamp);
    }

    SOH_Leave_Critical_Section();

    if ( (soh_ref_freq >= REFCLK_FREQ_LOW) && (soh_ref_freq <= REFCLK_FREQ_HIGH))
    {
        /* test passed */
        Soh_TestResult.Bits.SysClkFail = false;
    }
    else
    {
        /* test failed */
        Soh_TestResult.Bits.SysClkFail = true;
    }
    Soh_TestComp.Bits.SysClk = true;
}

/*===========================================================================*\
 * FUNCTION: ValidateEtcSohIrqFreq
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs the validate ETC SOH interrupt frequency test.
 *
 * The ETC SOH interrupt period is calculated as follows:
 *
 * ETC SOH interrupt period = Global Timer (current) - Global Timer (previous)
 *
 * The test passed if the calculated period is in the range between
 * SOHIRQTIME_PERIOD_LOW and SOHIRQTIME_PERIOD_HIGH.
 *
 * The test complete flag is set at the end of the function.
 \*===========================================================================*/

static void ValidateEtcSohIrqFreq(void)
{
  uint32_t        soh_CurIrq_Time, timediff;
  SOH_TMR_MSEC_T  delta_time;

    soh_CurIrq_Time = TPU_TIMER_Get_Value(0,SOH_INTERNAL_TIME_BASE_CONFIG);
    if (soh_CurIrq_Time >= Soh_LstIrq_Time) 
    {
        timediff = soh_CurIrq_Time - Soh_LstIrq_Time;
    }
    else 
    {
        timediff = (SOH_INTERNAL_TIME_BASE_OVERFLOW_VALUE - Soh_LstIrq_Time + soh_CurIrq_Time + 1);
    }
    Soh_LstIrq_Time = soh_CurIrq_Time;

    delta_time = IO_Convert_Count_To_Time(timediff,TPU_A_TCR1_CLOCK_FREQ, S_SOH_TMR_MSEC_T,MILLISECOND_RESOLUTION);

    if ((delta_time >= SOHIRQTIME_PERIOD_LOW) && (delta_time <= SOHIRQTIME_PERIOD_HIGH))
    {
        /* test passed */
        Soh_TestResult.Bits.SohIrqFail = false;
    }
    else
    {
        /* test failed */
        Soh_TestResult.Bits.SohIrqFail = true;
    }
    Soh_TestComp.Bits.SohIrq = true;
}

/*===========================================================================*\
 * FUNCTION: ValidateCpuLoopSeq
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs the validate CPU loop sequence test.
 *
 * The function compares the loop sequence array entries against the expected
 * ID tag sequence. Two array indexes are used, one by the ETC SOH interrupt
 * and the other by the cyclic executive.  The comparison stops when the ETC
 * SOH interrupt index is the same as the cyclic executive's.
 *
 * The test passed if the entries in the array are in the expected sequence.
 * When the test failed, the current value in the array is made the expected
 * ID tag.
 *
 * The maximum value of expected ID tag is the maximum number of major loops
 * in the cyclic executive.
 *
 * The test complete flag is set at the end of the function.
 \*===========================================================================*/
 bool enable_loop;
static void ValidateCpuLoopSeq(void)
{
    /* set test passed on entrance */
    Soh_TestResult.Bits.LoopSeqFail = false;
    do
    {
        /* compare array entry with expected ID tag */
        if (Soh_LoopSeq[Soh_IrqLoopSeqIdx] != Soh_IdTagExpect)
        {
            /* test failed */
            Soh_TestResult.Bits.LoopSeqFail = true;
            /* make current value in array as expected ID tag */
            Soh_IdTagExpect = Soh_LoopSeq[Soh_IrqLoopSeqIdx];
        }

        /* point to next entry */
        Soh_IrqLoopSeqIdx = IncCirBuffIdx(Soh_IrqLoopSeqIdx, SOH_LOOPSEQBUFSZ);

        /* get next expected tag */
        Soh_IdTagExpect = IncCirBuffIdx(Soh_IdTagExpect, HAL_SOH_APP_Get_Number_Major_Loop());
    } while (Soh_IrqLoopSeqIdx != Soh_SchdLoopSeqIdx);
    /* set test complete flag */
    Soh_TestComp.Bits.LoopSeq = true;
}


/*=============================================================================
 * IsLoopTestComp
 * @func  
 * @parm  
 * @rdesc  
 *===========================================================================*/
static bool IsLoopTestComp(bool even)
{
    bool return_code;
    if (even) 
    {
        return_code = (Soh_TestComp.Bits.SysClk && Soh_TestComp.Bits.SohIrq && Soh_TestComp.Bits.RtiFreq)?true:false;
    }
    else 
    {
        return_code = (Soh_TestComp.Bits.LoopSeq && Soh_TestComp.Bits.CpuOpsCR)?true:false;
    }
    return return_code;
}

/*=============================================================================
 * SetLoopTestComp
 * @func  
 * @parm  
 * @rdesc  
 *===========================================================================*/
INLINE void SetLoopTestComp(bool even)
{
    if (even) 
    {
        Soh_TestComp.Bits.SysClk = 1;
        Soh_TestComp.Bits.SohIrq = 1;
        Soh_TestComp.Bits.RtiFreq = 1;
    }
    else 
    {
        Soh_TestComp.Bits.LoopSeq = 1;
        Soh_TestComp.Bits.CpuOpsCR = 1;
    }
}

/*=============================================================================
 * IsLoopTestResultFail
 * @func  
 * @parm  
 * @rdesc  
 *===========================================================================*/
static bool IsLoopTestResultFail(bool even)
{
    bool return_code;
    if (even) 
    {
        return_code = (Soh_TestResult.Bits.SysClkFail || Soh_TestResult.Bits.SohIrqFail || Soh_TestResult.Bits.RtiFreqFail)?true:false;
    }
    else 
    {
        return_code = Soh_TestResult.Bits.LoopSeqFail;
    }
    return return_code;
}

/*=============================================================================
 * ClearLoopTestErr
 * @func  
 * @parm  
 * @rdesc  
 *===========================================================================*/
INLINE void ClearLoopTestErr(bool even)
{
    if (even) 
    {
        Soh_TestErr.Bits.SysClkFail = 0;
        Soh_TestErr.Bits.SohIrqFail = 0;
        Soh_TestErr.Bits.RtiFreqFail = 0;
    }
    else 
    {
        Soh_TestErr.Bits.LoopSeqFail = 0;
    }
}


/*===========================================================================*\
 * FUNCTION: ValidateCpuOperation
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs the validate CPU operating test.
 *
 * The function computes and sends the response value.  Fuel, spark and ETC
 * are enabled.
 *
 * The test complete flag is set at the end of the function.
 \*===========================================================================*/
static void ValidateCpuOperation(void)
{
    Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response( Soh_CnRValue.Bits.Challenge );
    VSEP_SOH_Set_Response(0, Soh_CnRValue.Bits.Response);
		
    /* set test complete flag */
    Soh_TestComp.Bits.CpuOpsCR = TRUE;
}

/*===========================================================================*\
 * FUNCTION: CpuOperatingErrHandler
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs error handling for the CPU operating test.
 * The function also read the status & the next challenge value from the
 * SOH ASIC.
 *
 * The function set a fault code depending on the type of SOH C&R errors and
 * the state of the ETC SOH recovery flag (Soh_RecoverMode).
 *
 * The test complete flag is set at the end of the function.
 \*===========================================================================*/
static void	CpuOperatingErrHandler(void)
{
		// Get challenge
    Soh_CnRValue.Bits.Challenge	= HAL_SOH_CnR_Get_Challenge();
    // Get status
		Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(false);

		if (TRUE == Soh_CnRStatus.Bits.CRDisarm_Stat)
    {
        Soh_FaultLog.Bits.CRDisarmed = TRUE;
    }
    else if (1 == Soh_CnRStatus.Bits.CRTimeout)
    {
        Soh_FaultLog.Bits.CRTimeoutFail = TRUE;
    }
    else if (0 == Soh_CnRStatus.Bits.Respcount)
    {
        Soh_FaultLog.Bits.CRCounterFail	= TRUE;
    }
    else if (Soh_CnRStatus.Bits.Respcount <= KSOHCRTH)
    {
        /* do not set fault in recovery mode */
        if (TRUE == Soh_RecoverMode)
        {
            /* do nothing */
        }
        else
        {
            Soh_FaultLog.Bits.CRCounterLow = TRUE;
        }
    }//else if(true==Soh_CnRStatus.Bits.SPIFail)
  //  {
 //       Soh_FaultLog.Bits.SPIFail = TRUE;
	//	}
    else
    {
        Soh_RecoverMode = FALSE;
    }

    /* set test complete flag */
    Soh_TestComp.Bits.CpuOpsResult = TRUE;
}

/*===========================================================================*\
 * FUNCTION: ProcessTestResult
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function is used by function EtcSohErrorHandler() to process the
 * the ETC SOH test results.
 *
 * Function EtcSohErrorHandler() contains the details.
 \*===========================================================================*/
static void ProcessTestResult(void)
{
    if (IsOdd(Soh_LoopCnt))
    {
        /* odd loop */
        if (!IsLoopTestResultFail(0))
        {
            /* all tests passed */
            if (Soh_OddErrCnt > 0)
            {
                /* decrement error count */
                Soh_OddErrCnt = Soh_OddErrCnt - SOH_ERRCOUNT_DEC;
            }
            else
            {
                /* clear error history */
                ClearLoopTestErr(0);
            }
        }
        else
        {
            /* not all tests passed */
            /* increment error count */
            Soh_OddErrCnt = Soh_OddErrCnt + SOH_ERRCOUNT_INC;
        }
    }
    else
    {
        /* even loop */
        if (!IsLoopTestResultFail(1))
        {
            /* all tests passed */
            if (Soh_EvenErrCnt > 0)
            {
                /* decrement error count */
                Soh_EvenErrCnt = Soh_EvenErrCnt - SOH_ERRCOUNT_DEC;
            }
            else
            {
                /* clear error history */
                ClearLoopTestErr(1);
            }
        }
        else
        {
            /* not all tests passed */
            /* increment error count */
            Soh_EvenErrCnt = Soh_EvenErrCnt + SOH_ERRCOUNT_INC;
        }
    }
}

/*===========================================================================*\
 * FUNCTION: ProcessShutOffTimer
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function is used by function EtcSohErrorHandler() to process the
 * shutoff timer.
 *
 * Function EtcSohErrorHandler() contains the details.
 \*===========================================================================*/
static void ProcessShutOffTimer(void)
{
    if ((Soh_OddErrCnt + Soh_EvenErrCnt) > 0)
    {
        /* update test errors */
        Soh_TestErr.Byte = Soh_TestErr.Byte | Soh_TestResult.Byte;

        if ((Soh_ShutOffUpTimer >= SOH_SHUTOFFTIME) || (Soh_ShutOffDnTimer < 1))
        {
            /* shutoff timer expired */
            /* log fault */
            Soh_FaultLog.Bytes.LoByte = Soh_FaultLog.Bytes.LoByte | Soh_TestErr.Byte;
            /* log shutoff timer expired fault */
            Soh_FaultLog.Bits.ShutOffTimeExpire = TRUE;
        }
        else
        {
            /* continue shutoff timers count up/down */
            Soh_ShutOffUpTimer = Soh_ShutOffUpTimer + 1;
            Soh_ShutOffDnTimer = Soh_ShutOffDnTimer - 1;
        }
    }
    else
    {
        Soh_ShutOffUpTimer = 0;
        Soh_ShutOffDnTimer = SOH_SHUTOFFTIME;
    }
}



/*===========================================================================*\
 * FUNCTION: EtcSohErrorHandler
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs error handling for the following ETC SOH tests.
 *  - ValidateSysClkFreq
 *  - ValidateEtcSohIrqFreq
 *  - ValidateSysTimer
 *  - ValidateRtiFreq
 *  - ValidateCpuLoopSeq
 *
 * The test errors are handled as follows:
 * If any tests failed in this odd/even loop (a bit is set in Soh_TestResult):
 *    - increments the error counter (Soh_OddErrCnt or Soh_EvenErrCnt) by SOH_ERRCOUNT_INC.
 *    - starts the shutoff timers (Soh_ShutOffUpTimer and Soh_ShutOffDnTimer).
 *    - set the corresponding odd/even error flag (Soh_TestErr).
 *
 * If all tests passed in this odd/even loop (no bit is set in Soh_TestResult):
 *    - if error counter > 0 : decremented (Soh_OddErrCnt or Soh_EvenErrCnt) by SOH_ERRCOUNT_DEC.
 *    - if error counter = 0 : clear the odd/even error flag (Soh_TestErr).
 *    - if both error counters = 0,
 *      reset the two shutoff timers (Soh_ShutOffUpTimer and Soh_ShutOffDnTimer).
 *
 * If any Shutoff timers (Soh_ShutOffUpTimer or Soh_ShutOffDnTimer) expires:
 *    - disable fuel, spark and ETC.
 *    - set the corresponding fault code (Soh_FaultLog).
 *    - set the shutoff timer expired fault code.
 *
 * Shutoff timers Soh_ShutOffUpTimer counts up, Soh_ShutOffDnTimer counts down.
 * The two shutdown timers backing up each other in case there is a RAM error.
 \*===========================================================================*/
static void	EtcSohErrorHandler(void)
{
    /* Part 1 : process test results */
    ProcessTestResult();

    /* Part 2 : process shutoff timers */
    ProcessShutOffTimer();

    /* Part 3 : disable outputs control */
    if (Soh_FaultLog.Word != SOH_TEST_NO_ERR)
    {
        /* fault logged */

        /* SOH CnR SPI exchange */
        /* send updated response, disable fuel, spark and ETC */
        Soh_CnRValue.Bits.FSE_DisReq = true;
        Soh_CnRValue.Bits.Challenge	= HAL_SOH_CnR_Get_Challenge();
        Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response( Soh_CnRValue.Bits.Challenge );

				HAL_SOH_CnR_Set_Response(Soh_CnRValue.Bits.FSE_DisReq, Soh_CnRValue.Bits.Response);
    }
    else
    {
        /* do nothing */
    }
}

/*===========================================================================*\
 * FUNCTION: ValidateEtcSohTestSeq
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * bool odd_even : odd/even loop identifier
 *			          0	- even loop
 *			          1	- odd loop
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs the validate ETC SOH test sequence test and controls the 
 * servicing of the external COP.
 *
 \*===========================================================================*/
static void ValidateEtcSohTestSeq(bool even)
{
    if (IsLoopTestComp(even)) 
    {
        SOH_Service_Watchdog(even);
    }
    else
    {
        Soh_FaultLog.Bits.SohSeqFail = TRUE;
        // Iusse software reset
        RequestIO_Software_Reset();
    }
    Soh_TestComp.Byte = 0;
}

/*===========================================================================*\
 * FUNCTION: EtcSohRecovery
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs the ETC SOH error recovery.
 *
 * The function initializes and pre-fill the ETC SOH arrays and variables so
 * that no false errors are reported when the SOH tests resumes. The purpose
 * is the same as the initialization routine.
 *
 * Additionally, for recovering when disabled is due to SOH C&R timeout:
 *  The CRTOCLR bit in the SOH SPI control word must be cleared.
 *
 * Additionally, for recovering from C&R counter value RESPCOUNT = 0:
 *  The IOEN signal to the SOH ASIC must be toggled.
 *
 * The function is executed when the ETC SOH software is in recovery mode and
 * the loop counter is even.
\*===========================================================================*/
static void EtcSohRecovery(void)
{
    if 	(TRUE == Soh_RecoverMode)
    {
        if (IsOdd(Soh_LoopCnt))
        {
            /* odd loop - do nothing */
        }
        else
        {
            /* even loop */
            /* re-initialize generic variables */
            Soh_LoopCnt = 0;
            /* initialise SOH variables */
            Soh_SchdLoopSeqIdx = 0;
            Soh_IrqLoopSeqIdx = 0;
            Soh_IdTagExpect = 0;

            /* clear Soh_FaultLog when any reset occurs; Soh_FaultLogNVM will record history */
            Soh_FaultLog.Word = 0;

            Soh_TestErr.Byte = 0;
            Soh_TestResult.Byte = 0;
            Soh_TestComp.Byte = 0;
            Soh_ShutOffUpTimer = 0;
            Soh_RecoverMode = FALSE;

            Soh_OddErrCnt = 0;
            Soh_EvenErrCnt = 0;
            Soh_ShutOffDnTimer = SOH_SHUTOFFTIME;
						
						Soh_LstRtiCirBufIdx = Soh_RtiCirBufIdx;
						Soh_IrqLoopSeqIdx = Soh_SchdLoopSeqIdx;
						Soh_IdTagExpect = IncCirBuffIdx(
											Soh_LoopSeq[DecCirBuffIdx(Soh_SchdLoopSeqIdx, SOH_LOOPSEQBUFSZ)], 
											HAL_SOH_APP_Get_Number_Major_Loop()
											);

            /* additional steps when recovering from C&R timeout or RESPCOUNT = 0 */
           /* if (0 == Soh_CnRStatus.Bits.Respcount)
            {
                Soh_CnRValue.Bits.FSE_DisReq = false;
                IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_FSE_ENABLE_REQ,false);

                Soh_CnRValue.Bits.Challenge	= VSEP_SOH_Get_Challenge(0);
                Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response( Soh_CnRValue.Bits.Challenge );
                VSEP_SOH_Set_Disable_Request(0,Soh_CnRValue.Bits.FSE_DisReq);
                VSEP_SOH_Set_Response(0, Soh_CnRValue.Bits.Response);

                Soh_CnRValue.Bits.Challenge	= VSEP_SOH_Get_Challenge(0);
                Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response( Soh_CnRValue.Bits.Challenge );
                VSEP_SOH_Set_Disable_Request(0,0);
                VSEP_SOH_Set_Response(0, Soh_CnRValue.Bits.Response);

                IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_FSE_ENABLE_REQ,true);
            }
            else if (TRUE == Soh_CnRStatus.Bits.CRTimeout)
            {
                Soh_CnRValue.Bits.FSE_DisReq = false;
                IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_FSE_ENABLE_REQ,false);
               // clear SOH C&R timeout fault bit (buffered output)
                VSEP_SOH_Set_Timeout_Fault(0,true);

                Soh_CnRValue.Bits.Challenge	= VSEP_SOH_Get_Challenge(0);
                Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response( Soh_CnRValue.Bits.Challenge );
                VSEP_SOH_Set_Disable_Request(0,Soh_CnRValue.Bits.FSE_DisReq);
                VSEP_SOH_Set_Response(0, Soh_CnRValue.Bits.Response);

                Soh_CnRValue.Bits.Challenge	= VSEP_SOH_Get_Challenge(0);
                Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response( Soh_CnRValue.Bits.Challenge );
                VSEP_SOH_Set_Disable_Request(0,0);
                VSEP_SOH_Set_Response(0, Soh_CnRValue.Bits.Response);

                IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_FSE_ENABLE_REQ,true);

            }*/
							/* additional steps when recovering from C&R timeout or RESPCOUNT = 0 */
							if (0 == Soh_CnRStatus.Bits.Respcount)
							{
								/* toggle the IOEN signal */
								SOH_Set_GEN_Enable_Request(false);		//mz38cg
								SOH_Set_GEN_Enable_Request(true); 	//mz38cg
							}
							else if (TRUE == Soh_CnRStatus.Bits.CRTimeout)
							{
								/* clear SOH C&R timeout fault bit (buffered output) */
								HAL_SOH_CnR_Clear_Timeout_Fault(true);
							}

            Soh_CnRValue.Word = 0;
						
						/* SOH C&R SPI exchange */
						/* receive next challenge value */
						Soh_CnRValue.Bits.Challenge = HAL_SOH_CnR_Get_Challenge();

						/* do not clear SOH C&R timeout fault bit (buffered output) */
						HAL_SOH_CnR_Clear_Timeout_Fault(false);
			
        }
    }
    else
    {
        /* do nothing */
    }
}

/*===========================================================================*\
 * FUNCTION: SOH_SPI_Get_Error_Status
 *===========================================================================
 * RETURN VALUE:
 * bool spi_status    : 0 - SPI transmit queue is empty.
 *                      1 - SPI transmit queue is not empty (error).
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function reads the MCU SPI error status.
\*===========================================================================*/
bool SOH_SPI_Get_Error_Status(void)
{
	return false;
}

/*===========================================================================*\
 * FUNCTION: ValidateRtiFreq
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function performs the validate RTI frequency test.
 *
 * The sliding window time is calculated as follows:
 *
 * sliding window time = Soh_RtiLoopTime[current] -
 *            Soh_RtiLoopTime[current - total number of minor loops before]
 *
 * The test passed if the sliding window time is in the range between
 * MAJLOOPTIME_LOW and MAJLOOPTIME_HIGH.
 *
 * The array pointer value is saved after the test.  If the array pointer value
 * is the same the next time the function is run, the test is deemed failed.
 *
 * The test complete flag is set at the end of the function.
\*===========================================================================*/
static void ValidateRtiFreq(void)
{
    uint32_t delta_time;
    SOH_TMR_MSEC_T sliding_window_time;
    unsigned char idx_curcycle, idx_lstcycle;

    /* set test failed on entrance */
    Soh_TestResult.Bits.RtiFreqFail = TRUE;

    if (Soh_LstRtiCirBufIdx != Soh_RtiCirBufIdx)
    {
        idx_curcycle = DecCirBuffIdx(Soh_RtiCirBufIdx, SOH_RTIBUFSZ);
        idx_lstcycle = IncCirBuffIdx(Soh_RtiCirBufIdx, SOH_RTIBUFSZ);

        if (Soh_RtiLoopTime[idx_curcycle] >= Soh_RtiLoopTime[idx_lstcycle])
        {
            delta_time = Soh_RtiLoopTime[idx_curcycle] - Soh_RtiLoopTime[idx_lstcycle];
        }
        else
        {
            delta_time = (SOH_INTERNAL_TIME_BASE_OVERFLOW_VALUE - Soh_RtiLoopTime[idx_lstcycle] + 1) + Soh_RtiLoopTime[idx_curcycle];
        }

        sliding_window_time = IO_Convert_Count_To_Time(delta_time,TPU_A_TCR1_CLOCK_FREQ, S_SOH_TMR_MSEC_T,MILLISECOND_RESOLUTION);

        if (  (sliding_window_time >= MAJLOOPTIME_LOW) && (sliding_window_time <= MAJLOOPTIME_HIGH) )
        {
            /* test passed */
            Soh_TestResult.Bits.RtiFreqFail = FALSE;
        }
        else
        {
            Soh_TestResult.Bits.RtiFreqFail = TRUE;
        }

        /* save array pointer value */
        Soh_LstRtiCirBufIdx = Soh_RtiCirBufIdx;
    }
    else
    {
        /* do nothing */
    }

    /* set test complete flag */
    Soh_TestComp.Bits.RtiFreq = TRUE;
}

/*===========================================================================*\
 * FUNCTION: SOH_ETC_ISR
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function is the ETC SOH interrupt service routine.
 *
 * The function run all the ETC SOH tests.   ETC SOH tests are stopped when
 * any errors is logged.  The function also handles the failure recovery mode
 * and SPI communication error.
 *
 * The ETC SOH tests are divided between the two loops (odd and even).
 * The purpose is to balance and reduce the overall execution time of the tests.
 *
 * The ETC SOH interrupt is setup to occur every 20 ms. So each loop is
 * to run every 40 ms.
 *
 * The interrupt is setup in one-shot mode to ensure itself is being executed,
 * failing which the watchdog timer will timeout and trigger a watchdog reset.
 \*===========================================================================*/
void SOH_ETC_ISR(void)
{		
	Soh_LoopCnt++;
	if (SOH_TEST_NO_ERR == Soh_FaultLog.Word)
	{
		 if (IsOdd(Soh_LoopCnt))
		 {
		    // /* odd loop */
		    ValidateCpuLoopSeq();
		    ValidateCpuOperation();
				SIU.GPDO[129].F.PDO =0;
		 }
		 else
		 {
		     /* even loop */
		     ValidateSysClkFreq();
		     ValidateEtcSohIrqFreq();						 
				 SIU.GPDO[129].F.PDO =1;
		     CpuOperatingErrHandler(); 
		     ValidateRtiFreq();
		 }
		 EtcSohErrorHandler();
	 }
	 else
	 {
		 // read out all VSEP fualts
		 Soh_CnRValue.Bits.Challenge	= VSEP_SOH_Get_Challenge(0);
		 Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response( Soh_CnRValue.Bits.Challenge );
		 VSEP_SOH_Set_Response(0, Soh_CnRValue.Bits.Response);        
		 Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(true);	

		 // FSE is not disbale as expected
		 if (FALSE == Soh_CnRStatus.Bits.FSE_En_Stat)
		 {
		     /* do nothing */
		 }
		 else
		 {
		   if (SOH_SPI_Get_Error_Status() == FALSE)
	     {
         /* SPI transmit queue empty */
         if (TRUE == Soh_FaultLog.Bits.SPICommFail)
         {
             /* stop servicing internal COP */
             return; /* [C163] DEVIATION: MULTIPLE RETURN VALUES! */
         }
         else
         {
             Soh_FaultLog.Bits.SPICommFail = TRUE;
         }
		   }
	     else
	     {
         /* SPI message not send */
         Soh_FaultLog.Bits.SPIFail = TRUE;
	     }
		 }
		// EtcSohRecovery();
	SetLoopTestComp(IsEven(Soh_LoopCnt));
	 }

	ValidateEtcSohTestSeq(IsEven(Soh_LoopCnt));
	//	SOH_VSEP_CR_Service();


	HAL_SOH_Setup_Interrupt(V_SOH_TMR_MSEC_T(SOH_IRQ_PERIOD_MS));
	/* save fault to fault log history */
	Soh_FaultLogNVM.Word = Soh_FaultLogNVM.Word | Soh_FaultLog.Word;
}

/*===========================================================================*\
 * FUNCTION: SOH_ETC_Initialize
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * bool power_on_reset_status : Power-on reset status.
 *                              0 - cause of reset is other types of reset.
 *                              1 - cause of reset is power-on reset.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function initializes the ETC SOH logic and variables.
 *
 * The function prepares the software so that the first and subsequent ETC SOH
 * interrupts could run the same code.  Arrays and variables are initialized and
 * pre-filled so that no tests failed the first time the ETC SOH interrupt
 * handler is executed.
 *
 * This function is to be called just before the global interrupt is enabled
 * and before the cyclic executive is started.
 \*===========================================================================*/
void SOH_ETC_Initialize(bool power_on_reset_status)
{
	uint8_t i;
    static uint32_t time,RTI_Period;
		
		if(VbHWIO_VSEP_Initialized)  //Do not set GEN and FSE_EN when VSEP initialize fail
		{
		/* enable GEN signal */
		SOH_Set_GEN_Enable_Request(true); //mz38cg
		/* request enable of fuel, spark and ETC */
		SOH_Set_FSE_Enable_Request(true); //mz38cg
		}
		else
		{ 
			 /*do nothing*/
		}

    Soh_LoopCnt = 0;
	/* initialise SOH variables */
	Soh_SchdLoopSeqIdx = 0;
	Soh_IrqLoopSeqIdx = 0;
	Soh_IdTagExpect = 0;

	/* clear Soh_FaultLog when any reset occurs; Soh_FaultLogNVM will record history */
	Soh_FaultLog.Word = 0;

	Soh_TestErr.Byte = 0;
	Soh_TestResult.Byte = 0;
	Soh_TestComp.Byte = 0;
	Soh_ShutOffUpTimer = 0;
	Soh_RecoverMode = FALSE;

	Soh_OddErrCnt = 0;
	Soh_EvenErrCnt = 0;
	Soh_ShutOffDnTimer = SOH_SHUTOFFTIME;
	
	/* SOH C&R SPI exchange */
	/* receive next challenge value and status */
	Soh_CnRValue.Word = 0;
	
	// /* do not clear SOH C&R timeout fault bit (buffered output) */
	HAL_SOH_CnR_Clear_Timeout_Fault(false);
	Soh_CnRValue.Bits.Challenge = HAL_SOH_CnR_Get_Challenge();
	Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(false);
	SIU.GPDO[129].F.PDO =1;

	// /* disable fuel, spark and ETC if fault is present */
		 if (Soh_FaultLogNVM.Word != SOH_TEST_NO_ERR)
		 {
			// /* SOH CnR SPI exchange */
			// /* send updated response, disable fuel, spark and ETC */
			 Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response(Soh_CnRValue.Bits.Challenge);
			 Soh_CnRValue.Bits.FSE_DisReq = true;
			 HAL_SOH_CnR_Set_Response(Soh_CnRValue.Bits.FSE_DisReq, Soh_CnRValue.Bits.Response);
		 }

	time = TPU_TIMER_Get_Value(0,SOH_INTERNAL_TIME_BASE_CONFIG);
	Soh_LstIrq_Time = time; 

    RTI_Period = IO_Convert_Time_To_Count(SOH_RTI_PERIOD,TPU_A_TCR1_CLOCK_FREQ,S_SOH_TMR_MSEC_T,MILLISECOND_RESOLUTION);
	for (i = SOH_RTIBUFSZ - 1; i > 0; i--)
	{
		Soh_RtiLoopTime[i] = time;
		if (time < RTI_Period)
		{
			time = SOH_INTERNAL_TIME_BASE_OVERFLOW_VALUE + 1 - RTI_Period + time;
		}
		else
		{
			time = time - RTI_Period;
		}	
	}	


    /* setup ETC SOH interrupt */
   HAL_SOH_Setup_Interrupt(V_SOH_TMR_MSEC_T(SOH_IRQ_PERIOD_MS));
   SOH_Start_DMA_For_External_Ref();
	 
}

/*===========================================================================*\
 * FUNCTION: SOH_ETC_Update_Loop_Sequence_Array
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * const uint8_t ID_tag : ID tag of the major loop.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function updates the state of health loop sequence array with a loop ID tag.
 * The array element pointer is incremented only after writing to the array.
 * The array is a circular buffer.
 * Updating stopped when any fault is logged.
 \*===========================================================================*/
void SOH_ETC_Update_Loop_Sequence_Array(const uint8_t ID_tag)
{
    Soh_LoopSeq[Soh_SchdLoopSeqIdx] = ID_tag;
    Soh_SchdLoopSeqIdx = IncCirBuffIdx(Soh_SchdLoopSeqIdx, SOH_LOOPSEQBUFSZ);
}

/*===========================================================================*\
 * FUNCTION: SOH_ETC_Update_RTI_Array
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function updates the state of health RTI array with the latest timestamp.
 * The array element pointer is incremented only after writing to the array.
 * The array is a circular buffer.
 * Updating stopped when any fault is logged.
\*===========================================================================*/
void SOH_ETC_Update_RTI_Array(void)
{
	Soh_RtiLoopTime[Soh_RtiCirBufIdx] = TPU_TIMER_Get_Value(0,SOH_INTERNAL_TIME_BASE_CONFIG);
	Soh_RtiCirBufIdx = IncCirBuffIdx(Soh_RtiCirBufIdx, SOH_RTIBUFSZ);
}

/*===========================================================================*\
 * FUNCTION: SOH_ETC_Get_Fault_Log
 *===========================================================================
 * RETURN VALUE:
 * uint16_t fault_log   : ETC SOH fault logged.
 *
 * +----------+-----------------------------------------------+
 * | Bit      | Description                                   |
 * | Position | (0 - no error, 1 - error logged)              |
 * +----------+-----------------------------------------------+
 * |      0   | System clock frequency error                  |
 * +----------+-----------------------------------------------+
 * |      1   | Interrupt source error                        |
 * +----------+-----------------------------------------------+
 * |      2   | System Timer error                            |
 * +----------+-----------------------------------------------+
 * |      3   | Test sequence error                           |
 * +----------+-----------------------------------------------+
 * |      4   | RTI frequency error                           |
 * +----------+-----------------------------------------------+
 * |      5   | CPU Loop sequence error                       |
 * +----------+-----------------------------------------------+
 * |      6   | SOH C&R counter value low                     |
 * +----------+-----------------------------------------------+
 * |      7   | Shutoff timer expired                         |
 * +----------+-----------------------------------------------+
 * |      8   | SPI error                                     |
 * +----------+-----------------------------------------------+
 * |      9   | SPI communication error                       |
 * +----------+-----------------------------------------------+
 * |     10   | SOH C&R disarmed                              |
 * +----------+-----------------------------------------------+
 * |     11   | SOH C&R timeout                               |
 * +----------+-----------------------------------------------+
 * |     12   | SOH C&R counter value zero                    |
 * +----------+-----------------------------------------------+
 * |     13   | Not used                                      |
 * +----------+-----------------------------------------------+
 * |     14   | Not used                                      |
 * +----------+-----------------------------------------------+
 * |     15   | Not used                                      |
 * +----------+-----------------------------------------------+
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function returns the history ETC SOH fault logged.
\*===========================================================================*/
uint16_t SOH_ETC_Get_Fault_Log(void)
{
	return (uint16_t)Soh_FaultLogNVM.Word;
}

/*===========================================================================*\
 * FUNCTION: SOH_ETC_Clear_Fault_Log
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 *  This function clears the history ETC SOH fault log.
\*===========================================================================*/
void SOH_ETC_Clear_Fault_Log(void)
{
	Soh_FaultLogNVM.Word = 0;
}

/*===========================================================================*\
 * FUNCTION: SOH_VSEP_CR_Service
 *===========================================================================
 * RETURN VALUE:
 * 
 * PARAMETERS:
 * None.
 *
 * EXTERNAL REFERENCES:
 * None.
 *
 * DEVIATIONS FROM STANDARDS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This function services VSEP challeng and response logic. It is just for SOH logic debug.
 *
\*===========================================================================*/
 void SOH_VSEP_CR_Service(void)
{
	HAL_SOH_CnR_Clear_Timeout_Fault(true);
	Soh_CnRValue.Bits.Challenge = HAL_SOH_CnR_Get_Challenge();
	Soh_CnRValue.Bits.Response = VSEP_SOH_Calculate_Response(Soh_CnRValue.Bits.Challenge);
	HAL_SOH_CnR_Clear_Timeout_Fault(false);
	HAL_SOH_CnR_Set_Response(Soh_CnRValue.Bits.FSE_DisReq, Soh_CnRValue.Bits.Response);
	Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(false);
//	PORTK_PK6 = !PORTK_PK6;
}





















