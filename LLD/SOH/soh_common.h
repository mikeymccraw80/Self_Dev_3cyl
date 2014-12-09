#ifndef SOH_COMMON_H /* { */
#define SOH_COMMON_H
/*===========================================================================*\
 * FILE: soh_common.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh_common.h~1:incl:ctc_pt3#1 %
 * %version: 1 %
 * %derived_by:rz65p6 %
 * %date_modified:  %
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
//#include "os_loop_scheduler.h"
#include "hal_soh.h"

#include "dd_tpu.h"
//#include "dd_tpu_timer.h"

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/* ETC SOH key working parameters */

/* the following macros are expressed in engineering unit
 * e.g., XXX_MS is expressed in milliseconds
 *       XXX_US is expressed in microseconds
 *       XXX_HZ is expressed in Hertz
 */
#define Main_Loop_Time_mS 10
#define Base_Loop_Time_mS 1.0
#define SOH_IRQ_PERIOD_MS						     ( 2 * Main_Loop_Time_mS )
#define REFCLK_FREQ_HZ							     ( 818UL )
#define SOH_RUNTEST_PERIOD_MS					     ( SOH_IRQ_PERIOD_MS * 2 )

#define SOH_LOOPSEQBUFSZ						     (uint8_t)( (SOH_RUNTEST_PERIOD_MS / Main_Loop_Time_mS)*SOH_10ms_loop_funciotn_NUM + 10 )

#define SOH_10ms_loop_funciotn_NUM  4
// This is the time base for SOH function, used to validate external frequency in and interrupt
//#define SOH_INTERNAL_TIME_BASE_CONFIG                TPU_CHANNEL_Set_TCR_Time_Base(0,TPU_TCR1_TIME_BASE)
//ETPUA0 - EPPwMT





#define SOH_INTERNAL_TIME_BASE_OVERFLOW_VALUE        0xFFFFFF

#define SOH_NUM_MINORLOOP_PERCYCLE			        (uint8_t)( HAL_SOH_APP_Get_Number_Major_Loop() * Main_Loop_Time_mS / Base_Loop_Time_mS)

#define MAJLOOPTIME_TYPICAL					        ( SOH_NUM_MINORLOOP_PERCYCLE * Base_Loop_Time_mS )

#define SOH_RTIBUFSZ								(uint8_t)( SOH_NUM_MINORLOOP_PERCYCLE + 2 )

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
typedef union Soh_Test_Result_Tag
{
	uint8_t Byte; /* 0 - test pass, 1 - test fail */
	struct
	{
		bitfield8_t		SysClkFail 		: 1; /* System clock frequency failure */
		bitfield8_t 	SohIrqFail 		: 1; /* ETC SOH interrupt frequency failure */
		bitfield8_t		SysTmrFail		: 1; /* System timer failure */
		bitfield8_t						: 1;
		bitfield8_t		RtiFreqFail		: 1; /* RTI frequency failure */
		bitfield8_t		LoopSeqFail		: 1; /* CPU loop sequence failure */
		bitfield8_t						: 2;
	} Bits;
} Soh_Test_Result_T;

typedef union Soh_Test_Completion_Tag
{
	uint8_t Byte; /* 0 - test not complete, 1 - test completed */
	struct
	{
		bitfield8_t		SysClk 			: 1; /* System clock frequency */
		bitfield8_t 	SohIrq 			: 1; /* ETC SOH interrupt frequency */
		bitfield8_t		SysTmr			: 1; /* System timer */
		bitfield8_t		CpuOpsCR		: 1; /* Fundamental CPU operation C&R */
		bitfield8_t		RtiFreq			: 1; /* RTI frequency */
		bitfield8_t		LoopSeq			: 1; /* CPU loop sequence */
		bitfield8_t		CpuOpsResult	: 1; /* Fundamental CPU operation check result */
		bitfield8_t						: 1;
	} Bits;
} Soh_Test_Completion_T;

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
		bitfield8_t  					: 2;
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
									                      1: timeout occurred (48 ms expired) or communication error */
	//	bitfield8_t SPIFail     		: 1; /* 0: No SPI  error   
//																				1: SPI  error  */																			
		bitfield8_t 		            : 7;
		bitfield8_t	Respcount			: 5; /* C&R counter value */
		bitfield8_t	CRDisarm_Stat	: 1; /*	0: ETC SOH C&R logic not disabled
												                1: ETC SOH C&R logic disabled */
		bitfield8_t	FSE_En_Stat		: 1; /*	0: FSE_Enable pin at low level
												                1: FSE_Enable pin at high level or communication error */
		bitfield8_t	GEN_Stat			  : 1; /*	0: GEN input at low level
												                1: GEN input at high level */
	} Bits;
} Soh_CnR_Status_T;

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
		bitfield8_t	SysClkFail 		    : 1; /* System clock frequency error */
		bitfield8_t	SohIrqSrcFail       : 1; /* Interrupt source error */
		bitfield8_t	SysTmrFail		    : 1; /* System timer error */
		bitfield8_t	SohSeqFail          : 1; /* Test sequence error */
		bitfield8_t	RtiFreqFail         : 1; /* RTI frequency error */
		bitfield8_t	LoopSeqFail		    : 1; /* CPU loop sequence error */
		bitfield8_t	CRCounterLow        : 1; /* SOH C&R counter value low */
		bitfield8_t	ShutOffTimeExpire   : 1; /* Shutoff timer expired */
		bitfield8_t	SPIFail             : 1; /* SPI error */
		bitfield8_t	SPICommFail         : 1; /* SPI communication error */
		bitfield8_t	CRDisarmed          : 1; /* SOH C&R disarmed */
		bitfield8_t	CRTimeoutFail       : 1; /* SOH C&R timeout */
		bitfield8_t	CRCounterFail	    : 1; /* SOH C&R counter value zero */
		bitfield8_t						: 3;
	} Bits;
} Soh_Fault_Log_T;




/* data type for time variables */
typedef uint32_t								SOH_TMR_MSEC_T;
#define V_SOH_TMR_MSEC_T(val) 					(uint32_t)((val)*64)
#define S_SOH_TMR_MSEC_T         				( 6 )

#define DecCirBuffIdx(idx, arraysize)			( (idx) > 0 ? (idx) - 1: (arraysize) - 1)
#define IncCirBuffIdx(idx, arraysize)			( (idx) >= (arraysize) - 1 ? 0 : (idx) + 1)

#endif /* } SOH_COMMON_H */
