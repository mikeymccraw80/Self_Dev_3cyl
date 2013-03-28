#ifndef SOH_S12X_H /* { */
#define SOH_S12X_H
/*===========================================================================*\
 * FILE: soh_s12x.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh_s12x.h~6:incl:mt20u2#1 %
 * %version: 6 %
 * %derived_by:vzd0pc %
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
#include "reuse.h"
#include "soh_common.h"
#include "hal_gpio.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/* the following macros are expressed in engineering unit
 * e.g., XXX_MS is expressed in milliseconds
 *       XXX_US is expressed in microseconds
 *       XXX_HZ is expressed in Hertz
 */

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/* maximum TCNT timer value */
#define SOH_TCNT_MAXTIME		(0xFFFF)
#define SOH_PIT_MAXTIME			(0xFFFF)

//for ETC SOH Sequence Validation
#define OS_COPClear1st()               	(ARMCOP = 0x55)
#define OS_COPClear2nd()              	(ARMCOP = 0xAA)


#define SOH_ODDTSTMSK			( 0x15 )
#define SOH_EVENTSTMSK			( 0xEA )


#define Read_TCNT_TMR()      		(ECT_TCNT)

#define Enable_EXTCLK_INT()		PIFJ_PIFJ7 = 1;\
					PIEJ_PIEJ7 = 1

#define Enable_ETCPWM_INT()		PIFP_PIFP3 = 1;\
					PIEP_PIEP3 = 1

#define Disable_ETCPWM_INT()		(PIEP_PIEP3 = 0)


#define Clear_SOH_INT_Flag()		(ECT_MCFLG = ECT_MCFLG_MCZF_MASK)

#define Set_SOH_INT_Period(irq_period)	(ECT_MCCNT = irq_period)

#define Disable_SOH_Interrupt()     ( ECT_MCCTL_MCZI = 0)


/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
extern void ValidateSysTimer(void);
extern void ValidateSysClkFreq(void);
extern void ValidateEtcSohIrqFreq(void);
extern void ValidateETCPWMFreq(void);
extern void ValidateEtcSohTestSeq(bool odd_even);
extern void SOH_Initialize_MCU_Hardware(void);
extern void SOH_Initialize_MCU_Specific_Variables(void);
extern void SOH_Setup_Interrupt(SOH_TMR_MSEC_T irq_period);


/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/


/*===========================================================================*\
 * FUNCTION: SOH_Set_IO_Enable_Request
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * bool fse_en_req    : 1 - enable FSE_EN_REQ signal.
 *                   	0 - disable FSE_EN_REQ signal.
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
 * This macro enable/disable the FSE_EN_REQ signal.
\*===========================================================================*/
#define SOH_Set_FSE_Enable_Request(fse_en_req)	(HAL_GPIO_SET_FSE_Enable( fse_en_req))	//mz38cg


/*===========================================================================*\
 * FUNCTION: SOH_Set_IO_Enable_Request
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * bool io_en    : 1 - enable IOEN signal.
 *                 0 - disable IOEN signal.
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
 * This macro enable/disable the IOEN signal.
\*===========================================================================*/
#define SOH_Set_GEN_Enable_Request(gen_en_req)	(HAL_GPIO_SET_GEN_Enable( gen_en_req))	//mz38cg


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
#endif /* } SOH_S12X_H */

