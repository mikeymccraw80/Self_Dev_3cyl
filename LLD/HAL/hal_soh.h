#ifndef SOH_HAL_H
#define SOH_HAL_H
/*===========================================================================*\
 * FILE: soh_hal.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec: hal_soh.h~4:incl:ctc_pt3#1 %
 * %version: 4 %
 * %derived_by: zzrfyj %
 * %date_modified:      %
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
//#include "io_scale.h"
//#include "io_discrete.h"


/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/* comment out the following line if STM test is not applicable */
#define SOH_STMTEST			1

/* This macro shall return the number of major loops in the application software */
#define HAL_SOH_APP_Get_Number_Major_Loop()			( 16 )

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
extern bool HAL_SOH_SPI_Get_Error_Status(void);
extern bool HAL_SOH_VsepSPI_High_Low_Error(bool unbuffered);
void HAL_SOH_Update_Loop_Sequence_10MS(void);

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
