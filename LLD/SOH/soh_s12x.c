/*===========================================================================*\
 * FILE: soh_s12x.c
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh_s12x.c~11:csrc:mt20u2#1 %
 * %version: 11 %
 * %derived_by:  wzmkk7 %
 * %date_modified: %
 * $SOURCE: $
 * $REVISION: $
 * $AUTHOR: $
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *   ETC SOH building block software.
 *   (for Infineon TC1762, TC1765, TC1766, TC1775, TC1792, TC1796.)
 *   Used in conjunction with ASIC (VSEP, MIO) with state-of-health (SOH) logic.
 *
 *   This file contains all the microprocessor specific tests.
 *   Comment out #define SOH_STMTEST in file hal_soh.h if STM test is not 
 *   applicable.
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
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/
#include "soh_s12x.h"
#include "soh_common.h"


extern const uint16_t KfVIOS_f_ETCM_Frequency;

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/

/* SOH validation test error tolerance setting (in percentage) */
#define REFCLK_FREQ_ERR						( 0.10 )
#define SOHIRQTIME_ERR 						( 0.050 )
#define SOHSTMTIME_ERR 						( 0.050 )
#define SOHETCPWM_ERR 						( 0.10 )
#define SOH_IC_ERR						( 0.10 )

#define SOH_IC_COUNT						( 2 )

/* the following macros are expressed in engineering unit
 * e.g., XXX_MS is expressed in milliseconds
 *       XXX_US is expressed in microseconds
 *       XXX_HZ is expressed in Hertz
 */
#define SOH_RUNTEST_PERIOD_MS					( SOH_IRQ_PERIOD_MS * 2 )

/* the following macros are expressed in computer unit */
#define SOHSTMTEST_TCNT_PERIOD				( V_SOH_TMR_MSEC_T(SOH_RTI_PERIOD_MS) )
#define SOHSTMTIME_TCNT_PERIOD_HIGH			( (uint16_t)(SOHSTMTEST_TCNT_PERIOD * (1 + SOHSTMTIME_ERR)) )
#define SOHSTMTIME_TCNT_PERIOD_LOW			( (uint16_t)(SOHSTMTEST_TCNT_PERIOD * (1 - SOHSTMTIME_ERR)) )

#define SOHSTMTEST_PIT_PERIOD					( V_SOH_PIT_TMR_MSEC_T(SOH_RTI_PERIOD_MS) )
#define SOHSTMTIME_PIT_PERIOD_HIGH			( (uint16_t)(SOHSTMTEST_PIT_PERIOD * (1 + SOHSTMTIME_ERR)) )
#define SOHSTMTIME_PIT_PERIOD_LOW			( (uint16_t)(SOHSTMTEST_PIT_PERIOD * (1 - SOHSTMTIME_ERR)) )

#define REFCLK_FREQ_HIGH						( (uint16_t)(REFCLK_FREQ_HZ * (1 + REFCLK_FREQ_ERR)) )
#define REFCLK_FREQ_LOW 						( (uint16_t)(REFCLK_FREQ_HZ * (1 - REFCLK_FREQ_ERR)) )

#define SOHIRQTEST_PERIOD						( V_SOH_TMR_MSEC_T(SOH_RUNTEST_PERIOD_MS) )
#define SOHIRQTIME_PERIOD_HIGH				( (uint16_t)(SOHIRQTEST_PERIOD * (1 + SOHIRQTIME_ERR)) )
#define SOHIRQTIME_PERIOD_LOW					( (uint16_t)(SOHIRQTEST_PERIOD * (1 - SOHIRQTIME_ERR)) )

#define SOH_IC_LIMIT_HIGH						( (uint32_t)((1 + SOH_IC_ERR)*1000) )
#define SOH_IC_LIMIT_LOW						( (uint32_t)((1 - SOH_IC_ERR)*1000) )

#define ETCPWM_FREQ_LIMIT_HIGH				( (uint32_t)((1 + SOHETCPWM_ERR)*1000) )
#define ETCPWM_FREQ_LIMIT_LOW 				( (uint32_t)((1 - SOHETCPWM_ERR)*1000) )

#define GetETCPWMDutyZeroPercent				(PWMDTY23 == 0)
#define GetETCPWMDutyFullPercent				(PWMDTY23 == PWMPER23)

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

 extern unsigned int C58x_ToothTime[16];		
 extern unsigned int C58x_ToothTime_PIT[16];		
 extern unsigned char C58x_Xcount;


/*===========================================================================*\
 * Exported Object Definitions
\*===========================================================================*/

/*  refer to s12_xgate_var.c for shared data prototypes */
/* for systerm clock validation */
extern unsigned char Soh_RefClkEdgeCnt; /* Counter of reference clock pulses */
extern unsigned int Soh_FirstRefClkEdgeTime; /* First time of occurrence of reference clock falling edge */
extern unsigned int Soh_lastRefClkEdgeTime; /* Last time of occurrence of reference clock falling edge */
extern unsigned int CurrentTime; 

/* for system timer validation */
extern unsigned int Soh_CurrentRtiTime; /* Current time of occurrence RTI interrupt */
extern unsigned int Soh_PreviousRtiTime; /* Previous time of occurrence of RTI interrupt */
extern unsigned int Soh_CurrentRtiTime_PIT; /* Current time of occurrence RTI interrupt */
extern unsigned int Soh_PreviousRtiTime_PIT; /* Previous time of occurrence of RTI interrupt */
extern unsigned char Soh_InputCapture_Required_Cnt; /* Counter of input capture of 58x required by SOH */

/* for ETC PWM frequency validation*/
extern unsigned char Soh_ETCPWMEdgeCnt; /* Counter of ETC PWM output falling edges */
extern unsigned int Soh_FirstETCPWMEdgeTime; /* First time of occurrence of ETC PWM output falling edge */
extern unsigned int Soh_lastETCPWMEdgeTime; /* Last time of occurrence of ETC PWM output falling edge */


/* SOH global variables use only by HC12 */
unsigned int Soh_LstIrqTime; /* Last time of occurrence of ETC SOH interrupt request */
bool Soh_ValidateETCPWMFreq_Condition_Met;
bool Soh_ValidateInputCapture_Condition_Met;

#if 0
/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/


/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/


/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/* This macro calculates frequency (in Hz).
 * Argument "time" should be scaled to SOH_TMR_MSEC_T
 */
#define Calc_Frequency_Per_SOH_TMR_MSEC(count, time)	((uint16_t)((uint32_t)(1000000/TIM_PERIOD_US)*count / time))


/*===========================================================================*\
 * Function Definitions
\*===========================================================================*/

/*===========================================================================*\
 * FUNCTION: ValidateSysTimer
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
 * This function performs the validate system timer test.
 *
 * The system timer period is calculated as follows:
 *
 * system timer period = STM Timer (current) - STM Timer (previous)
 *
 * The test passed if the calculated period is in the range between
 * SOHSTMTIME_PERIOD_LOW and SOHSTMTIME_PERIOD_HIGH.
 *
 * The test complete flag is set at the end of the function.
\*===========================================================================*/
void ValidateSysTimer(void)
{
	SOH_TMR_MSEC_T delta_time;
	SOH_PIT_TMR_MSEC_T delta_time_pit;

	SOH_TMR_MSEC_T ic_delta_time;
	SOH_PIT_TMR_MSEC_T ic_delta_time_pit;
	uint8_t ic_index;
	
	

	/* Set the Semaphore for Xgate */
	while(!Check_SeamphoreSet(SEMAPHORE_2))
	{Set_Seamphore(SEMAPHORE_2);}	

	//RTI time based on TCNT timer
	delta_time = Soh_CurrentRtiTime - Soh_PreviousRtiTime;

	Soh_PreviousRtiTime = 0;
	Soh_CurrentRtiTime = 0;

	//RTI time based on PIT timer
	delta_time_pit = Soh_CurrentRtiTime_PIT - Soh_PreviousRtiTime_PIT;

	Soh_PreviousRtiTime_PIT = 0;
	Soh_CurrentRtiTime_PIT = 0;

	/* Clear the Semaphore for Xgate */
	Release_Seamphore(SEMAPHORE_2);

	if(Soh_InputCapture_Required_Cnt == 0)
	{
		Soh_ValidateInputCapture_Condition_Met = 1;
			
		ic_index = C58x_Xcount - 2;

		ic_delta_time = C58x_ToothTime[ic_index&0x0F] - C58x_ToothTime[(ic_index-SOH_IC_COUNT)&0x0F];

		ic_delta_time_pit = C58x_ToothTime_PIT[ic_index&0x0F] - C58x_ToothTime_PIT[(ic_index-SOH_IC_COUNT)&0x0F];

	}
	else
	{
		Soh_ValidateInputCapture_Condition_Met = 0;
	}


	/* Set the Semaphore for Xgate */
	//Set_Seamphore(SEMAPHORE_0);   	//needed? review with shoujun
	while(!Check_SeamphoreSet(SEMAPHORE_0))
	{Set_Seamphore(SEMAPHORE_0);}		
	Soh_InputCapture_Required_Cnt = SOH_IC_COUNT + 2;
	/* Clear the Semaphore for Xgate */
	Release_Seamphore(SEMAPHORE_0);

	if (((delta_time >= SOHSTMTIME_TCNT_PERIOD_LOW) && (delta_time <= SOHSTMTIME_TCNT_PERIOD_HIGH)) &&\
		((delta_time_pit >= SOHSTMTIME_PIT_PERIOD_LOW) && (delta_time_pit <= SOHSTMTIME_PIT_PERIOD_HIGH))&&\
		((!Soh_ValidateInputCapture_Condition_Met)||\
		((ic_delta_time >= (uint16_t)(Convert_PITTMR_to_TCNTTMT(ic_delta_time_pit)*SOH_IC_LIMIT_LOW/1000))&&\
		(ic_delta_time <= (uint16_t)(Convert_PITTMR_to_TCNTTMT(ic_delta_time_pit)*SOH_IC_LIMIT_HIGH/1000)))) )
	{
		/* test passed */
		Soh_TestResult.Bits.SysTmrFail = FALSE;
	}
	else
	{
		/* test failed */
		Soh_TestResult.Bits.SysTmrFail = TRUE;
	}

	/* set test complete flag */
	Soh_TestComp.Bits.SysTmr = TRUE;
}


/*===========================================================================*\
 * FUNCTION: ValidateSysClkFreq
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
 * This function performs the validate system clock frequency test.
 *
 * The reference clock frequency is calculated as follows:
 *
 *                             delta edge count      LTC (current) - LTC (previous)
 * reference clock frequency = ------------------ =  ------------------------------
 *                             delta edge time       GTC (current) - GTC (previous)
 *
 * The LTC counts the number of edge.
 * The GTC captures the edge occurrence time.
 *
 * The test passed if the calculated frequency is in the range between
 * REFCLK_FREQ_LOW and REFCLK_FREQ_HIGH.
 *
 * The test complete flag is set at the end of the function.
\*===========================================================================*/
void ValidateSysClkFreq(void)
{
	SOH_TMR_MSEC_T delta_time;
	uint16_t freq_refclk;
	uint8_t delta_count;

	/* Set the Semaphore for Xgate */
	//add here...
	
	delta_time = Soh_lastRefClkEdgeTime - Soh_FirstRefClkEdgeTime;

	delta_count = Soh_RefClkEdgeCnt-1;

	/* clear the clock edge time and count for next iteration */
	Soh_RefClkEdgeCnt = 0;
	Soh_FirstRefClkEdgeTime = 0;
	Soh_lastRefClkEdgeTime = 0;
	Enable_EXTCLK_INT();
	
	/* Clear the Semaphore for Xgate */
	//add here...

	/* calculate frequency */
	if ((delta_time > 0)&&(delta_count >0))
	{
		freq_refclk = Calc_Frequency_Per_SOH_TMR_MSEC(delta_count, delta_time);
	}
	else
	{
		freq_refclk = 0;
	}

	if ((freq_refclk >= REFCLK_FREQ_LOW) && (freq_refclk <= REFCLK_FREQ_HIGH)) 
	{
		/* test passed */
		Soh_TestResult.Bits.SysClkFail = FALSE;
	}
	else
	{
		/* test failed */
		Soh_TestResult.Bits.SysClkFail = TRUE;
	}

	/* set test complete flag */
	Soh_TestComp.Bits.SysClk = TRUE;

	
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
void ValidateEtcSohIrqFreq(void)
{
	SOH_TMR_MSEC_T soh_curirqtime, delta_time;

	/* read current Global timer time */
	soh_curirqtime = Read_TCNT_TMR();

	delta_time = soh_curirqtime - Soh_LstIrqTime;

	/* store time for next iteration */
	Soh_LstIrqTime = soh_curirqtime;
	
	if ((delta_time >= SOHIRQTIME_PERIOD_LOW) && (delta_time <= SOHIRQTIME_PERIOD_HIGH))
	{
		/* test passed */
		Soh_TestResult.Bits.SohIrqFail = FALSE;
	}
	else
	{
		/* test failed */
		Soh_TestResult.Bits.SohIrqFail = TRUE;
	}

	/* set test complete flag */
	Soh_TestComp.Bits.SohIrq = TRUE;
}


/*===========================================================================*\
 * FUNCTION: ValidateETCPWMFreq
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
 * This function performs the validate system clock frequency test.
 *
 * The reference clock frequency is calculated as follows:
 *
 *                             delta edge count      LTC (current) - LTC (previous)
 * reference clock frequency = ------------------ =  ------------------------------
 *                             delta edge time       GTC (current) - GTC (previous)
 *
 * The LTC counts the number of edge.
 * The GTC captures the edge occurrence time.
 *
 * The test passed if the calculated frequency is in the range between
 * REFCLK_FREQ_LOW and REFCLK_FREQ_HIGH.
 *
 * The test complete flag is set at the end of the function.
\*===========================================================================*/
void ValidateETCPWMFreq(void)
{
	SOH_TMR_MSEC_T delta_time;
	uint16_t freq_etcpwm;
	uint8_t delta_count;
	
	delta_time = Soh_lastETCPWMEdgeTime - Soh_FirstETCPWMEdgeTime;

	if ( Soh_ETCPWMEdgeCnt == 5 ) // refer to SOH_ETCPWM_CNT_MAX
	{
	    delta_count = Soh_ETCPWMEdgeCnt-1;
	}
	else
	{
	    delta_count = 0;
	}

	/* clear the clock edge time and count for next iteration */
	Soh_ETCPWMEdgeCnt = 0;
	Soh_FirstETCPWMEdgeTime = 0;
	Soh_lastETCPWMEdgeTime = 0;
	Enable_ETCPWM_INT();

	/* calculate frequency */
	if ((delta_time > 0)&&(delta_count >0))
	{
		freq_etcpwm = Calc_Frequency_Per_SOH_TMR_MSEC(delta_count, delta_time);
	}
	else
	{
		freq_etcpwm = 0;
	}

	if ( ( !Soh_ValidateETCPWMFreq_Condition_Met ) ||
	     ( freq_etcpwm == 0 ) ||
	     ((freq_etcpwm >= KfVIOS_f_ETCM_Frequency*ETCPWM_FREQ_LIMIT_LOW/4000) &&
	      (freq_etcpwm <= KfVIOS_f_ETCM_Frequency*ETCPWM_FREQ_LIMIT_HIGH/4000)) )
	{
		/* test passed */
		Soh_TestResult.Bits.ETCPWMFail = FALSE;
	}
	else
	{
		/* test failed */
		Soh_TestResult.Bits.ETCPWMFail = TRUE;	
	}
	
	Soh_ValidateETCPWMFreq_Condition_Met = true;

	/* set test complete flag */
	Soh_TestComp.Bits.ETCPWM = TRUE;
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
 * This function performs the validate ETC SOH test sequence test.
 *
 * The function services the MCU watchdog (internal COP) using the proprietary
 * password scheme.  The password is changed to EVEN and ODD alternately depending
 * on the loop counter value is an odd or even number.
 * The watchdog is serviced in two write accesses. The first access (known as
 * password access) unlocks the watchdog registers. The second access (known as
 * modifying access) changes the password and automatically locked the
 * registers after the write.
 *
 * An watchdog error occurs when:
 * 1) an incorrect access to the watchdog register was attempted.
 * 2) watchdog timer overflow.
 * In all error cases, the watchdog timer generates an NMI trap request and the
 * MCU enters the reset pre-warning mode.
 *
 * The test passed if the watchdog is serviced without any error.
 *
 * The SOH test complete flags (a byte) is used as the password (a byte).
 * The odd loop password is ODDLOOP_PASSWD.
 * The even loop password is EVENLOOP_PASSWD.
\*===========================================================================*/
void ValidateEtcSohTestSeq(bool odd_even)
{
	if ((odd_even == true)&&(Soh_TestComp.Byte == SOH_ODDTSTMSK ))
	{
		/* odd loop */
		OS_COPClear1st();               //ARMCOP = 0x55
	}
	else if ((odd_even == false)&&(Soh_TestComp.Byte == SOH_EVENTSTMSK ))
	{
		/* even loop */
		OS_COPClear2nd();              //ARMCOP = 0xAA
	}
	else
	{
		//do nothing...
	}

	/* clear test completion flag */
	Soh_TestComp.Byte = 0;
}


/*===========================================================================*\
 * FUNCTION: Initialize_MCU_Specific_Variables
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
 * This function is a child routine of the ETC SOH initialization & error
 * recovery.
 *
 * The function initializes and pre-fill microprocessor specific ETC SOH
 * arrays and variables.
 *
 * The function is called by SOH_ETC_Initialize() and EtcSohRecovery().
 *
\*===========================================================================*/
void SOH_Initialize_MCU_Hardware(void)
{
	/* initializer modulus timer for SOH interrupt */
	ECT_MCFLG_MCZF = 1;	//clear interrupt flag
	ECT_PTMCPSR = TIMER_0_PRESCALER_VALUE-1; //same scaler with ECT
	ECT_MCCTL = 0x84;	//* MCZI |MCEN */	
	
	/* initialize PIT3 for system timer validation */
	PITMUX_PMUX3 = 1;      //use macro timer 1 for PIT 3, 5us/count
	PITLD3   = 0xFFFF;	//set PIT3 free run
	PITTF = PITTF_PTF3_MASK; 		//clear  flag
	PITINTE_PINTE3 = 0;	//disable interupt
	PITCE_PCE3 = 1;		//enable PIT3

	PPSP_PPSP3 = 1; // configure to rising edge effective
}



/*===========================================================================*\
 * FUNCTION: Initialize_MCU_Specific_Variables
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
 * This function is a child routine of the ETC SOH initialization & error
 * recovery.
 *
 * The function initializes and pre-fill microprocessor specific ETC SOH
 * arrays and variables.
 *
 * The function is called by SOH_ETC_Initialize() and EtcSohRecovery().
 *
\*===========================================================================*/
void SOH_Initialize_MCU_Specific_Variables(void)
{
	//initialize for SOH interrupt frequency validation
	Soh_LstIrqTime = Read_TCNT_TMR();

	//initialize for system timer validation
	Soh_CurrentRtiTime = 0;
	Soh_PreviousRtiTime = 0;
	Soh_CurrentRtiTime_PIT = 0;
	Soh_PreviousRtiTime_PIT = 0;
	
	Soh_ValidateInputCapture_Condition_Met = 0;
	/* Set the Semaphore for Xgate */
	//Set_Seamphore(SEMAPHORE_0);   	//needed? review with shoujun
	while(!Check_SeamphoreSet(SEMAPHORE_0))
	{Set_Seamphore(SEMAPHORE_0);}		
	Soh_InputCapture_Required_Cnt = SOH_IC_COUNT + 2;
	/* Clear the Semaphore for Xgate */
	Release_Seamphore(SEMAPHORE_0);

	
	//initialize for system clock validation
	Soh_RefClkEdgeCnt = 0;
	Soh_FirstRefClkEdgeTime = 0;
	Soh_lastRefClkEdgeTime = 0;

	//initialize for ETC PWM frequency validation
	Soh_ETCPWMEdgeCnt = 0;
	Soh_FirstETCPWMEdgeTime = 0;
	Soh_lastETCPWMEdgeTime = 0;
	Soh_ValidateETCPWMFreq_Condition_Met = false;
}
		

/*===========================================================================*\
 * FUNCTION: SOH_Setup_Interrupt
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * SOH_TMR_MSEC_T irq_period : interrupt occurrence time scaled to SOH_TMR_MSEC_T.
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
 * This function setup an ETC SOH interrupt to occur in the specified time
 * in one-shot mode.
\*===========================================================================*/
void SOH_Setup_Interrupt(SOH_TMR_MSEC_T irq_period)
{
	Clear_SOH_INT_Flag();
	Set_SOH_INT_Period(irq_period);
}

#endif
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
