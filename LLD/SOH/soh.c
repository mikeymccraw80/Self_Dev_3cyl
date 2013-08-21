/*===========================================================================*\
 * FILE: soh.c
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh.c~7:csrc:mt20u2#1 %
 * %version: 7 %
 * %derived_by:  wzmkk7 %
 * %date_modified: %
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

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
#include "soh.h"
#include "soh_s12x.h"
#include "vsepcald.h"
#include "hal_soh.h"


/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/
/* the following macros are expressed in engineering unit
 * e.g., XXX_MS is expressed in milliseconds
 *       XXX_US is expressed in microseconds
 *       XXX_HZ is expressed in Hertz
 */

#define SOH_NUM_MINORLOOP_PERCYCLE			(uint8_t)( HAL_SOH_APP_Get_Number_Major_Loop() * \
															HAL_SOH_APP_Get_Major_Loop_Time_MS() / \
															HAL_SOH_APP_Get_Minor_Loop_Time_MS() )

#define SOH_RUNTEST_PERIOD_MS					( SOH_IRQ_PERIOD_MS * 2 )

#define MAJLOOPTIME_TYPICAL                                	( (SOH_NUM_MINORLOOP_PERCYCLE * \
															HAL_SOH_APP_Get_Minor_Loop_Time_MS()) )

/* the following macros convert engineering unit to computer unit */

#define MAJLOOPTIME_HIGH						( V_SOH_PIT_TMR_MSEC_T(MAJLOOPTIME_TYPICAL) + KSOHRTITH)
#define MAJLOOPTIME_LOW						( V_SOH_PIT_TMR_MSEC_T(MAJLOOPTIME_TYPICAL) - KSOHRTITH)

#define SOH_SHUTOFFTIME		  				( (uint8_t)( SOH_SHUTOFF_PERIOD_MS / SOH_IRQ_PERIOD_MS ) )

#define SOH_RTI_PERIOD							( V_SOH_PIT_TMR_MSEC_T(HAL_SOH_APP_Get_Minor_Loop_Time_MS()) )

#define SOH_RTIBUFSZ							(uint8_t)( SOH_NUM_MINORLOOP_PERCYCLE + 2 )
#define SOH_LOOPSEQBUFSZ						(uint8_t)( SOH_RUNTEST_PERIOD_MS / \
															HAL_SOH_APP_Get_Major_Loop_Time_MS() + 1 )

/* SOH test error counter increment step size */
#define SOH_ERRCOUNT_INC						( 5 )

/* SOH test error counter decrement step size */
#define SOH_ERRCOUNT_DEC						( 1 )

/* SOH Interrupt Offset*/
#define SOH_ETC_ISR_Offset						( 1 )

/* test no errors */
#define SOH_TEST_NO_ERR					   	( 0x0000 )

#define IsEven(number)							( ((number) & 0x01) == 0 )
#define IsOdd(number)							( ((number) & 0x01) == 1 )

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Definitions
\*===========================================================================*/
/* SOH test complete flag */
Soh_Test_Completion_T Soh_TestComp;
/* SOH current test result */
Soh_Test_Result_T Soh_TestResult;

/* SOH recovery bit */
bool Soh_RecoverMode; /*	0: ETC SOH recovery completed or not in recovery mode
							1: start ETC SOH recovery */

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/* SOH arrays and variables */
static uint8_t Soh_LoopSeq[SOH_LOOPSEQBUFSZ]; /* Store major loop sequence ID tag */
static SOH_PIT_TMR_MSEC_T Soh_RtiLoopTime[SOH_RTIBUFSZ]; /* Store time of occurrence of RTI loop */
static uint8_t Soh_RtiCirBufIdx;  /* RTI loop time array index */
static uint8_t Soh_LstRtiCirBufIdx; /* Last RTI loop time array index */
static uint8_t Soh_SchdLoopSeqIdx; /* Major loop sequence array index - application */
static uint8_t Soh_IrqLoopSeqIdx; /* Major loop sequence array index - ETC SOH */
static uint8_t Soh_LoopCnt; /* SOH loop counter used to identify odd or even loop */

/* next expected ID tag */
static uint8_t Soh_IdTagExpect;
/* SOH test error counters */
static uint8_t Soh_OddErrCnt;
static uint8_t Soh_EvenErrCnt;
/* SOH shutoff timers */
static uint8_t Soh_ShutOffUpTimer;
static uint8_t Soh_ShutOffDnTimer;

/* SOH test result history */
static Soh_Test_Result_T Soh_TestErr;

/* SOH boolean, bitfield and flags */

/* ASIC SOH challenge, response value and status bits */
static Soh_CnR_Value_T Soh_CnRValue;
static Soh_CnR_Status_T Soh_CnRStatus;


uint8_t Temp_SOH_Debug_ID;


/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/
static void EtcSohRecovery(void);
static void ValidateRtiFreq(void);
static void ValidateCpuLoopSeq(void);
static void ValidateCpuOperation(void);
static void ProcessTestResult(void);
static void ProcessShutOffTimer(void);
static void EtcSohErrorHandler(void);
static void CpuOperatingErrHandler(void);
static uint8_t CalcSohResponse(uint8_t challenge);

/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/
#define DecCirBuffIdx(idx, arraysize)			( (idx) > 0 ? (idx) - 1: (arraysize) - 1)
#define IncCirBuffIdx(idx, arraysize)			( (idx) >= (arraysize) - 1 ? 0 : (idx) + 1)
#define ShiftBitLeft(data, nbits)				( data << nbits )
#define ShiftBitRight(data, nbits)				( data >> nbits )
#define Bit_ZeroOneThreeFour(bitpos)			( ( ((bitpos) >= 0x01) && ((bitpos) <  0x4)) || \
									   		  	  		  ( ((bitpos) >  0x07) && ((bitpos) <= 0x10) ) )
#define CheckBit( modeword, bit )      ( ( ( modeword ) & ( bit ) ) != 0 )
#define BitIsClear( modeword, bit )    ( !CheckBit( modeword, bit ) )
/*===========================================================================*\
 * Function Definitions
\*===========================================================================*/




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
#if 0
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
	SOH_TMR_MSEC_T sliding_window_time;
	unsigned char idx_curcycle, idx_lstcycle;

	/* set test failed on entrance */
	Soh_TestResult.Bits.RtiFreqFail = true;

	if (Soh_LstRtiCirBufIdx != Soh_RtiCirBufIdx)
	{
		idx_curcycle = DecCirBuffIdx(Soh_RtiCirBufIdx, SOH_RTIBUFSZ);
		idx_lstcycle = IncCirBuffIdx(Soh_RtiCirBufIdx, SOH_RTIBUFSZ);

		sliding_window_time = Soh_RtiLoopTime[idx_curcycle] - Soh_RtiLoopTime[idx_lstcycle];
		
		if (  (sliding_window_time >= MAJLOOPTIME_LOW) && (sliding_window_time <= MAJLOOPTIME_HIGH) )
		{
			/* test passed */
			Soh_TestResult.Bits.RtiFreqFail = false;
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
static void ValidateCpuLoopSeq(void)
{
	/* set test passed on entrance */
	Soh_TestResult.Bits.LoopSeqFail = FALSE;

	do
	{
		/* compare array entry with expected ID tag */
		if (Soh_LoopSeq[Soh_IrqLoopSeqIdx] != Soh_IdTagExpect)
		{
			/* test failed */
			Soh_TestResult.Bits.LoopSeqFail = TRUE;

			/* make current value in array as expected ID tag */
			Soh_IdTagExpect = Soh_LoopSeq[Soh_IrqLoopSeqIdx];
		}

		/* point to next entry */
		Soh_IrqLoopSeqIdx = IncCirBuffIdx(Soh_IrqLoopSeqIdx, SOH_LOOPSEQBUFSZ);

		/* get next expected tag */
		Soh_IdTagExpect = IncCirBuffIdx(Soh_IdTagExpect, HAL_SOH_APP_Get_Number_Major_Loop());
	} while (Soh_IrqLoopSeqIdx != Soh_SchdLoopSeqIdx);

	/* set test complete flag */
	Soh_TestComp.Bits.LoopSeq = TRUE;
}
#endif
/*===========================================================================*\
 * FUNCTION: CalcSohResponse
 *===========================================================================
 * RETURN VALUE:
 * uint8_t response : calculated SOH "Response" value.
 *
 * PARAMETERS:
 * uint8_t challenge : SOH "Challenge" value.
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
 *	This function manipulates the challenge value to calculate the response value.
 *
 *  DO NOT optimize the following code in any way.
 *
 *  This function checks the arithmetic and logical operations of the MCU. So as
 *  many as possible arithmetic and logical operations are used in calculating
 *  the response value.
\*===========================================================================*/
static uint8_t CalcSohResponse(uint8_t challenge)
{
	volatile uint8_t bitmsk;
	uint8_t temp, response;

	/* response.b[5:1] = challenge.b[4:0] */
	temp = (9 * challenge) / 3;
	response = (temp + (temp % 3) - challenge) & 0x3E;

	/* response.b0 = challenge.b4 & challenge.b3 & challenge.b2 & challenge.b1 & challenge.b0 */
	bitmsk = 0x80;
	while (bitmsk > 0)
	{
		/* quit while loop if "shift left 1-bit" operator failure */
		if	(bitmsk == (bitmsk >> 1))
		{
			bitmsk = 0;
		}
		else if (Bit_ZeroOneThreeFour(bitmsk))
		{
			response = response & (CheckBit(challenge, bitmsk) | 0x3E);
			bitmsk = bitmsk >> 1;
		}
		else if (0x04 == bitmsk)
		{
			if (BitIsClear(challenge, bitmsk))
			{
				response = response & 0x3E;
			}
			bitmsk = bitmsk >> 1;
		}
		else
		{
			response = response | 0x01;
			bitmsk = 0x10;
		}
	} /* end while */
		
	/* temp.b7 = challenge.b5 ~^ challenge.b4 */
	temp = ~( ShiftBitLeft(challenge, 2) ^ ShiftBitLeft(challenge, 3) );
	temp = temp & 0x80;

	/* response.b0 = response.b0 ^ temp.b7 */
	response = response ^ (uint8_t)CheckBit(temp, 0x80);

	return response;
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
	/* calculates response value */
	Soh_CnRValue.Bits.Response = CalcSohResponse(Soh_CnRValue.Bits.Challenge);

	/* send response value, enable fuel, spark and ETC */
	HAL_SOH_CnR_Set_Response(Soh_CnRValue.Bits.FSE_DisReq, Soh_CnRValue.Bits.Response);

	/* set test complete flag */
	Soh_TestComp.Bits.CpuOpsCR = TRUE;

	//test code
	//PORTK_PK6 = !PORTK_PK6;
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
		if (SOH_TEST_NO_ERR == (Soh_TestResult.Byte & SOH_ODDTSTMSK))
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
				Soh_TestErr.Byte = Soh_TestErr.Byte & (~SOH_ODDTSTMSK);
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
		if (SOH_TEST_NO_ERR == (Soh_TestResult.Byte & SOH_EVENTSTMSK))
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
				Soh_TestErr.Byte = Soh_TestErr.Byte & (~SOH_EVENTSTMSK);
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
			Soh_FaultLogNVM.Bytes.LoByte = Soh_FaultLogNVM.Bytes.LoByte | Soh_TestErr.Byte;
			/* log shutoff timer expired fault */
			Soh_FaultLogNVM.Bits.W14 = TRUE;
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
 *    - set the corresponding fault code (Soh_FaultLogNVM).
 *    - set the shutoff timer expired fault code.
 *
 * Shutoff timers Soh_ShutOffUpTimer counts up, Soh_ShutOffDnTimer counts down.
 * The two shutdown timers backing up each other in case there is a RAM error.
 *
\*===========================================================================*/
static void	EtcSohErrorHandler(void)
{
	/* Part 1 : process test results */
	ProcessTestResult();

	/* Part 2 : process shutoff timers */
	ProcessShutOffTimer();

	/* Part 3 : disable outputs control */
	if (Soh_FaultLogNVM.Word != SOH_TEST_NO_ERR)
	{
		/* fault logged */

		/* SOH CnR SPI exchange */

		/* send updated response, disable fuel, spark and ETC */
		Soh_CnRValue.Bits.Response = CalcSohResponse(Soh_CnRValue.Bits.Challenge);
		Soh_CnRValue.Bits.FSE_DisReq = true;
		HAL_SOH_CnR_Set_Response(Soh_CnRValue.Bits.FSE_DisReq, Soh_CnRValue.Bits.Response);

		Soh_CnRValue.Bits.Challenge = HAL_SOH_CnR_Get_Challenge();
	}
	else
	{
		/* do nothing */
	}
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
	/* SOH C&R SPI exchange */
	/* receive next challenge value and status */
	Soh_CnRValue.Bits.Challenge = HAL_SOH_CnR_Get_Challenge();
	Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(false);

	 if (TRUE == Soh_CnRStatus.Bits.CRDisarm_Stat)
	{
		Soh_FaultLogNVM.Bits.W11 = TRUE;
	}
	else if (TRUE == Soh_CnRStatus.Bits.CRTimeout)
	{
		Soh_FaultLogNVM.Bits.W12 = TRUE;
	}
	else if (0 == Soh_CnRStatus.Bits.Respcount)
	{
		Soh_FaultLogNVM.Bits.W13 = TRUE;
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
			Soh_FaultLogNVM.Bits.W07 = TRUE;
		}
	}
	else
	{
		Soh_RecoverMode = FALSE;
	}
	
	/* set test complete flag */
	Soh_TestComp.Bits.CpuOpsResult = TRUE;
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
 *
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
			Soh_TestErr.Byte = 0;
			Soh_TestResult.Byte = 0;
			Soh_FaultLogNVM.Word = 0;
			Soh_ShutOffUpTimer = 0;
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
			if (0 == Soh_CnRStatus.Bits.Respcount)
			{
				/* toggle the IOEN signal */
				SOH_Set_GEN_Enable_Request(false);		//mz38cg
				SOH_Set_GEN_Enable_Request(true);		//mz38cg
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

			/* re-initialize microprocessor specific variables */
			SOH_Initialize_MCU_Specific_Variables();	//mz38cg: need recover
		}
	}
	else
	{
		/* do nothing */
	}
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
 * The ETC SOH interrupt is setup to occur every 15.625 ms. So each loop is
 * to run every 31.25 ms.
 *
 * The interrupt is setup in one-shot mode to ensure itself is being executed,
 * failing which the watchdog timer will timeout and trigger a watchdog reset.
\*===========================================================================*/
void SOH_ETC_ISR(void)
{

	SOH_PIT_TMR_MSEC_T SOH_ETC_ISR_Time;

	//SOH_ETC_ISR_Time = Read_TCNT_TMR();
	Soh_LoopCnt++;

	if (SOH_TEST_NO_ERR == Soh_FaultLogNVM.Word)
	{
		/* no fault logged */
		if (IsOdd(Soh_LoopCnt))
		{
			/* odd loop */
			//ValidateCpuLoopSeq();	//mz38cg
			ValidateCpuOperation();	//mz38cg
			//ValidateETCPWMFreq();	//mz38cg
		}
		else
		{
			/* even loop */
			//ValidateSysTimer();
			//ValidateSysClkFreq();
			//ValidateEtcSohIrqFreq();
			//ValidateRtiFreq();	//mz38cg
			CpuOperatingErrHandler();	//mz38cg
		}
				
		/* ETC SOH error handling */
		//EtcSohErrorHandler();	//mz38cg: block for debug
	}
	else
	{		
		/* fault logged */
		/* read SOH C&R status */
#if 0
		Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(true);	//mz38cg
		if (FALSE == Soh_CnRStatus.Bits.FSE_En_Stat)
		{
			/* do nothing */
		}
		else
		{
			if (HAL_SOH_SPI_Get_Error_Status() == FALSE)
			{
				/* SPI transmit queue empty */
				if (TRUE == Soh_FaultLogNVM.Bits.W10)
				{
					/* stop servicing internal COP */
					return; /* [C163] DEVIATION: MULTIPLE RETURN VALUES! */
				}
				else
				{
					 Soh_FaultLogNVM.Bits.W10 = TRUE;	//mz38cg
				}
			}
			else
			{
				/* SPI message not send */
				Soh_FaultLogNVM.Bits.W09 = TRUE;
			}
		}
		
		/* ETC SOH error recovery */
		EtcSohRecovery();

		/* set odd/even loop test complete flag */
		Soh_TestComp.Byte = IsOdd(Soh_LoopCnt) ? SOH_ODDTSTMSK : SOH_EVENTSTMSK;
		#endif
	}


	/* validate ETC SOH test sequence */
	//ValidateEtcSohTestSeq(IsOdd(Soh_LoopCnt));

	/* setup next ETC SOH interrupt */
	//SOH_Setup_Interrupt( V_SOH_TMR_MSEC_T(SOH_IRQ_PERIOD_MS) -
       //                      (uint16_t)(Read_TCNT_TMR() - SOH_ETC_ISR_Time) -
        //                     SOH_ETC_ISR_Offset );
//
	/* [C163] DEVIATION: MULTIPLE RETURN VALUES! */
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
 *
\*===========================================================================*/
void SOH_ETC_Initialize(bool power_on_reset_status)
{
	uint8_t i;
	SOH_TMR_MSEC_T time;

	//SOH_Initialize_MCU_Hardware();

	/* enable GEN signal */
	SOH_Set_GEN_Enable_Request(true);	//mz38cg
	/* request enable of fuel, spark and ETC */
	SOH_Set_FSE_Enable_Request(true);	//mz38cg
#if 0
	/* initialise SOH variables */
	Soh_SchdLoopSeqIdx = 0;
	Soh_IrqLoopSeqIdx = 0;
	Soh_RtiCirBufIdx = 0;
	Soh_LstRtiCirBufIdx = 0;
	Soh_IdTagExpect = 0;

	/* prefill RTI loop time arrays */
	//time = SOH_Convert_PIT_TMR(Read_PIT_TMR(PIT_CHANNEL3));
	//for (i = SOH_RTIBUFSZ - 1; i > 0; i--)
	//{
	//	Soh_RtiLoopTime[i] = time;
	//	time = time - SOH_RTI_PERIOD;
	//}

	/* clear only if cause of reset is due to power-on reset */
	if (true == power_on_reset_status)
	{
		Soh_FaultLogNVM.Word = 0;
	}
	Soh_TestErr.Byte = 0;
	Soh_TestResult.Byte = 0;
	Soh_TestComp.Byte = 0;
	Soh_ShutOffUpTimer = 0;
	Soh_RecoverMode = FALSE;

	Soh_LoopCnt = 0;
	Soh_OddErrCnt = 0;
	Soh_EvenErrCnt = 0;
	Soh_ShutOffDnTimer = SOH_SHUTOFFTIME;
#endif
	/* SOH C&R SPI exchange */
	/* receive next challenge value and status */
	Soh_CnRValue.Word = 0;
	
	/* do not clear SOH C&R timeout fault bit (buffered output) */
	HAL_SOH_CnR_Clear_Timeout_Fault(false);
	Soh_CnRValue.Bits.Challenge = HAL_SOH_CnR_Get_Challenge();
	Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(false);

	//test code
	//PORTK_PK6 = !PORTK_PK6;

	/* disable fuel, spark and ETC if fault is present */
	//if (Soh_FaultLogNVM.Word != SOH_TEST_NO_ERR)
	//{
		/* SOH CnR SPI exchange */
		/* send updated response, disable fuel, spark and ETC */
	//	Soh_CnRValue.Bits.Response = CalcSohResponse(Soh_CnRValue.Bits.Challenge);
	//	Soh_CnRValue.Bits.FSE_DisReq = true;
	//	HAL_SOH_CnR_Set_Response(Soh_CnRValue.Bits.FSE_DisReq, Soh_CnRValue.Bits.Response);
	//}

	//SOH_Initialize_MCU_Specific_Variables();

	//Enable_EXTCLK_INT(); 
	//
	//Enable_ETCPWM_INT();

	//OS_COPClear();

	/* setup ETC SOH interrupt */
	//SOH_Setup_Interrupt(V_SOH_TMR_MSEC_T(SOH_IRQ_PERIOD_MS));
}


/*===========================================================================*\
 * FUNCTION: SOH_ETC_Get_Test_Result
 *===========================================================================
 * RETURN VALUE:
 * uint8_t test_result   : most recent ETC SOH test result.
 *
 * +----------+-----------------------------------------------+
 * | Bit      | Description                                   |
 * | Position | (0 - test passed, 1 - test failed)            |
 * +----------+-----------------------------------------------+
 * |      0   | System clock frequency failure                |
 * +----------+-----------------------------------------------+
 * |      1   | ETC SOH interrupt frequency failure           |
 * +----------+-----------------------------------------------+
 * |      2   | System Timer failure                          |
 * +----------+-----------------------------------------------+
 * |      3   | Not used                                      |
 * +----------+-----------------------------------------------+
 * |      4   | RTI frequency failure                         |
 * +----------+-----------------------------------------------+
 * |      5   | CPU Loop sequence failure                     |
 * +----------+-----------------------------------------------+
 * |      6   | Not used                                      |
 * +----------+-----------------------------------------------+
 * |      7   | Not used                                      |
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
 * This function returns the most recent ETC SOH test result.
 *
\*===========================================================================*/
uint8_t SOH_ETC_Get_Test_Result(void)
{
	return Soh_TestResult.Byte;
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
 * This function returns the ETC SOH fault logged.
 *
\*===========================================================================*/
uint16_t SOH_ETC_Get_Fault_Log(void)
{
	return (uint16_t)Soh_FaultLogNVM.Word;
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
	Soh_CnRValue.Bits.Response = CalcSohResponse(Soh_CnRValue.Bits.Challenge);
	HAL_SOH_CnR_Clear_Timeout_Fault(false);
	HAL_SOH_CnR_Set_Response(Soh_CnRValue.Bits.FSE_DisReq, Soh_CnRValue.Bits.Response);
	Soh_CnRStatus.Word = HAL_SOH_CnR_Get_Status(false);
	//PORTK_PK6 = !PORTK_PK6;
}

/*===========================================================================*\
 * FUNCTION: SOH_Logic_Debug_and_Test
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
void SOH_Logic_Debug_and_Test(void)
{
	switch(Temp_SOH_Debug_ID)
	{
		case 1:

			break;
			
		case 2:
			
			break;

		default:
			
			break;			
				
	}
}


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date        userid    (Description on following lines: SCR #, etc.)
 * ----------- --------
 * 01 June 05  sgchia
 * + Created initial file.
 *
\*===========================================================================*/
