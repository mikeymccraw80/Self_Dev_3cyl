#ifndef SOH_MPC56XX_H /* { */
#define SOH_MPC56XX_H
/*===========================================================================*\
 * FILE: soh_mpc56xx.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh_mpc56xx.h~1:incl:ctc_pt3#1 %
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
#include "hal_soh.h"

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
#define SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE  12//818HZ 
//#define SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE  32

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/
extern uint32_t SOH_DMA_External_Ref_Time[SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE];

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
#define Get_Current_DMA_idx(citer) \
    ( (SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE - citer == 0) ? \
      (SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE - 1):(SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE - citer - 1))

#define NUMBER_OF_SAMPLE_POINT SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE - 2 

#define Get_Start_DMA_idx(current_idx) \
   ( ((current_idx - (NUMBER_OF_SAMPLE_POINT - 1)) < 0) ? \
     (current_idx - (NUMBER_OF_SAMPLE_POINT - 1) + SOH_EXTERNAL_REF_TIME_DMA_BUFFER_SIZE ):(current_idx - (NUMBER_OF_SAMPLE_POINT - 1)) )


void Initialize_SOH_HardwareRegister(void);
void SOH_Start_DMA_For_External_Ref(void);
void SOH_Enter_Critical_Section(void);
void SOH_Leave_Critical_Section(void);
void SOH_Service_Watchdog(bool iseven);

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date        userid    (Description on following lines: SCR #, etc.)
 * ----------- --------
 *
\*===========================================================================*/
#endif /* } SOH_MPC56XX_H */

