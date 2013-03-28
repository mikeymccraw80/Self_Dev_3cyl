#ifndef SOH_HAL_H
#define SOH_HAL_H
/*===========================================================================*\
 * FILE: soh_hal.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec: hal_soh.h~1:incl:mt20u2#1 %
 * %version: 1 %
 * %derived_by: wzmkk7 %
 * %date_modified: Tue Nov  1 22:58:57 2005 %
 * $SOURCE: $
 * $REVISION: $
 * $AUTHOR: $
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *   ETC SOH building block software - HAL.
 *   (for Infineon TC1762, TC1765, TC1766, TC1775, TC1792, TC1796.)
 *   Used in conjunction with ASIC (VSEP, MIO) with state-of-health (SOH) logic.
 *
 *   Comment out #define SOH_STMTEST below if STM test is not applicable.
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




/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/* The following statement defines whether to enable/disable 
 * the SOH external hardware reset logic.
 * #define SOH_HWRESET_ENABLE		1	enable
 * #define SOH_HWRESET_ENABLE		0	disable
 */
#define SOH_HWRESET_ENABLE		0


/* the following macros are expressed in engineering unit
 * e.g., XXX_MS is expressed in milliseconds
 *       XXX_US is expressed in microseconds
 *       XXX_HZ is expressed in Hertz
 */

/* This macro shall return the application software minor loop time in milliseconds */
#define HAL_SOH_APP_Get_Minor_Loop_Time_MS()		( 3.90625 )

/* This macro shall return the application software major loop time in milliseconds */
#define HAL_SOH_APP_Get_Major_Loop_Time_MS()	   	( 7.8125 )

/* This macro shall return the number of major loops in the application software */
#define HAL_SOH_APP_Get_Number_Major_Loop()		( 16 )

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
extern void HAL_SOH_CnR_Clear_Timeout_Fault(bool cnr_timeout_fault);
extern void HAL_SOH_Set_HWReset_Enable_Request(bool extrn_reset_en);
extern uint8_t HAL_SOH_CnR_Get_Challenge(void);
extern uint16_t HAL_SOH_CnR_Get_Status(bool unbuffered);
extern void HAL_SOH_CnR_Set_Response(bool fse_disreq, uint8_t response);
extern bool HAL_SOH_SPI_Get_Error_Status(void);


/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date        userid    (Description on following lines: SCR #, etc.)
 * ----------- --------
 * 01 Nov 05  jay wyrick, sgchia
 * + Created initial file.
 *
\*===========================================================================*/
#endif // SOH_HAL_H
