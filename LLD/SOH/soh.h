#ifndef SOH_H /* { */
#define SOH_H
/*===========================================================================*\
 * FILE: soh.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh.h~2:incl:mt20u2#1 %
 * %version: 2 %
 * %derived_by:wzmkk7 %
 * %date_modified: Mon Feb 19 13:58:46 2007 %
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
#include "io_type.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/
#define TRUE true
#define FALSE false
/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/
extern bool Soh_RecoverMode;

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
extern FAR_COS uint16_t SOH_ETC_Get_Fault_Log(void);
extern FAR_COS uint8_t  SOH_ETC_Get_Test_Result(void);
extern FAR_COS void SOH_ETC_ISR(void);
extern FAR_COS void SOH_ETC_Initialize(bool power_on_reset_status);
extern FAR_COS void SOH_ETC_Update_Loop_Sequence_Array(const uint8_t ID_tag);
extern FAR_COS void SOH_ETC_Update_RTI_Array(void);
extern FAR_COS void SOH_VSEP_CR_Service(void);			//just for debug and test
extern FAR_COS void SOH_Logic_Debug_and_Test(void);	//just for debug and test


/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * MACRO: SOH_ETC_Invoke_Recovery
 *===========================================================================
 * RETURN VALUE:
 * None.
 *
 * PARAMETERS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This macro invokes the ETC SOH recovery process.
 *
\*===========================================================================*/
#define SOH_ETC_Invoke_Recovery()				( Soh_RecoverMode = TRUE )


/*===========================================================================*\
 * MACRO: SOH_ETC_Get_Recovery_Status
 *===========================================================================
 * RETURN VALUE:
 * bool soh_recovery_status : 1 - ETC SOH in recovery mode.
 *                      	   0 - ETC SOH recovery completed or not in recovery mode.
 *
 * PARAMETERS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This macro return the ETC SOH recovery status.
 *
\*===========================================================================*/
#define SOH_ETC_Get_Recovery_Status()			(bool)( Soh_RecoverMode == TRUE)


/*===========================================================================*\
 * MACRO: SOH_Convert_PIT_TMR
 *===========================================================================
 * RETURN VALUE:
 * PIT 
 *
 * PARAMETERS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This convert PIT reg count by 0-value.
 *
\*===========================================================================*/
#define SOH_Convert_PIT_TMR(count)			(0-count)



/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date        userid    (Description on following lines: SCR #, etc.)
 * ----------- --------
 * 01 June 05  sgchia
 * + Created initial file.
 * 19 Febr 07  gpstep
 * + Corrected SOH_ETC_Get_Error_Log name (RSM #5481).
 *
\*===========================================================================*/
#endif /* } SOH_H */
