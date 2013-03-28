#ifndef SOH_COMMON_H /* { */
#define SOH_COMMON_H
/*===========================================================================*\
 * FILE: soh_common.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh_common.h~4:incl:mt20u2#1 %
 * %version: 4 %
 * %derived_by:wzmkk7 %
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
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"


/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/* ETC SOH key working parameters */

/* the following macros are expressed in engineering unit
 * e.g., XXX_MS is expressed in milliseconds
 *       XXX_US is expressed in microseconds
 *       XXX_HZ is expressed in Hertz
 */
#define SOH_IRQ_PERIOD_MS						( 15.625 )
#define SOH_RTI_PERIOD_MS						( 8.0 )
#define SOH_SHUTOFF_PERIOD_MS					( 187.50 )
#define REFCLK_FREQ_HZ							( 818UL )


/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/* data type for time variables */

typedef uint16_t								SOH_TMR_MSEC_T;
#define V_SOH_TMR_MSEC_T(val) 				((uint16_t)(val * 1000000 / (uint32_t)(TIM_PERIOD_US * 1000UL)) ) //mz38cg: Need to review it


#define PIT_TIM_PERIOD_US	( 1000000UL / MICROTIMER1_FREQUENCY_HZ )//PIT Timer: 5us @40MHz bus clock

typedef uint16_t								SOH_PIT_TMR_MSEC_T;
#define V_SOH_PIT_TMR_MSEC_T(val) 			((uint16_t)(val * 1000000UL / (uint32_t)(PIT_TIM_PERIOD_US * 1000UL)) ) //mz38cg: Need to review it


#define Convert_PITTMR_to_TCNTTMT(count)	((uint16_t)(count * (uint32_t)(PIT_TIM_PERIOD_US * 1000) / (uint32_t)(TIM_PERIOD_US * 1000)) )


typedef union Soh_Fault_Log_Tag
{
	uint16_t Word; /* ETC SOH fault code */
	struct
	{
		uint8_t LoByte;
		uint8_t HiByte;
	} Bytes;
	struct
	{
		bitfield8_t	W01					: 1; /* System clock frequency error */
		bitfield8_t	W02					: 1; /* Interrupt source error */
		bitfield8_t	W03					: 1; /* System timer error */
		bitfield8_t	W04					: 1; /* Test sequence error */
		bitfield8_t	W05					: 1; /* RTI frequency error */
		bitfield8_t	W06					: 1; /* CPU loop sequence error */
		bitfield8_t	W07					: 1; /* SOH C&R counter value low */
		bitfield8_t	W08					: 1; /* ECT PWM frequecy error */
		bitfield8_t	W09					: 1; /* SPI error */
		bitfield8_t	W10					: 1; /* SPI communication error */
		bitfield8_t	W11					: 1; /* SOH C&R disarmed */
		bitfield8_t	W12					: 1; /* SOH C&R timeout */
		bitfield8_t	W13					: 1; /* SOH C&R counter value zero */
		bitfield8_t	W14					: 1; /* Shutoff timer expired */
		bitfield8_t	Unused					: 2;
	} Bits;
} Soh_Fault_Log_T;


typedef union Soh_Test_Completion_Tag
{
	uint8_t Byte; /* 0 - test not complete, 1 - test completed */
	struct
	{
		bitfield8_t		SysClk 			: 1; /* System clock frequency */
		bitfield8_t 		SohIrq 			: 1; /* ETC SOH interrupt frequency */
		bitfield8_t		SysTmr			: 1; /* System timer */
		bitfield8_t		CpuOpsCR		: 1; /* Fundamental CPU operation C&R */
		bitfield8_t		RtiFreq			: 1; /* RTI frequency */
		bitfield8_t		LoopSeq			: 1; /* CPU loop sequence */
		bitfield8_t		CpuOpsResult	: 1; /* Fundamental CPU operation check result */
		bitfield8_t		ETCPWM			: 1; /* ETC PWM frequency */
	} Bits;
} Soh_Test_Completion_T;


typedef union Soh_Test_Result_Tag
{
	uint8_t Byte; /* 0 - test pass, 1 - test fail */
	struct
	{
		bitfield8_t		SysClkFail 		: 1; /* System clock frequency failure */
		bitfield8_t 		SohIrqFail 		: 1; /* ETC SOH interrupt frequency failure */
		bitfield8_t		SysTmrFail		: 1; /* System timer failure */
		bitfield8_t		CpuOpsCRFail		: 1; 
		bitfield8_t		RtiFreqFail		: 1; /* RTI frequency failure */
		bitfield8_t		LoopSeqFail		: 1; /* CPU loop sequence failure */
		bitfield8_t		CpuOpsResultFail	: 1; 
		bitfield8_t		ETCPWMFail		: 1; /* ETC PWM frequency failure */
	} Bits;
} Soh_Test_Result_T;


typedef union Soh_CnR_Value_Tag
{
	uint16_t Word;  /* SOH challenge and response and FSE disable request */
	struct
	{
		uint8_t LoByte;
		uint8_t HiByte;
	} Bytes;
	struct
	{
		bitfield8_t	Challenge			: 6; /* C&R challenge value */
		bitfield8_t  						: 2;
		bitfield8_t	Response			: 6; /* C&R response value */
		bitfield8_t	FSE_DisReq			: 1; /*	1: request disable fuel, spark and ETC
												0: no control */
		bitfield8_t						: 1;
	} Bits;
} Soh_CnR_Value_T;


typedef union Soh_CnR_Status_Tag
{
	uint16_t Word; /* SOH challenge and response and other status */
	struct
	{
		uint8_t LoByte;
		uint8_t HiByte;
	} Bytes;
	struct
	{
		bitfield8_t	CRTimeout			: 1; /*	0: no timeout occurred
												1: timeout occurred (48 ms expired) or
												   	communication error */
		bitfield8_t 						: 7;
		bitfield8_t	Respcount			: 5; /* C&R counter value */
		bitfield8_t	CRDisarm_Stat		: 1; /*	0: ETC SOH C&R logic not disabled
												1: ETC SOH C&R logic disabled */
		bitfield8_t	FSE_En_Stat			: 1; /*	0: FSE_Enable pin at low level
												1: FSE_Enable pin at high level or
												   	communication error */
		bitfield8_t	GEN_Stat			: 1; /*	0: GEN input at low level
												1: GEN input at high level */
	} Bits;
} Soh_CnR_Status_T;

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/
extern Soh_Test_Completion_T Soh_TestComp;
extern Soh_Test_Result_T Soh_TestResult;
extern Soh_Fault_Log_T Soh_FaultLogNVM;

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

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
#endif /* } SOH_COMMON_H */
