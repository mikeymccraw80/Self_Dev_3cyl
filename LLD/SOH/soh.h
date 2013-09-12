#ifndef SOH_H /* { */
#define SOH_H
/*===========================================================================*\
 * FILE: soh.h
 *===========================================================================
 * Copyright 2005 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh.h~1:incl:ctc_pt3#1 %
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
#include "soh_common.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/
extern bool Soh_RecoverMode;
extern bool VbHWIO_SOH_Running;
extern bool VbHWIO_VSEP_Initialized;

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
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
\*===========================================================================*/
#define SOH_ETC_Invoke_Recovery()				( Soh_RecoverMode = TRUE )


/*===========================================================================*\
 * MACRO: SOH_ETC_Get_Recovery_Status
 *===========================================================================
 * RETURN VALUE:
 * bool soh_recovery_status : ETC SOH recovery mode status.
 *
 * PARAMETERS:
 * None.
 *
 * --------------------------------------------------------------------------
 * ABSTRACT:
 * --------------------------------------------------------------------------
 * This macro return the ETC SOH recovery status.
\*===========================================================================*/
#define SOH_ETC_Get_Recovery_Status()			( (bool)Soh_RecoverMode )

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
#define SOH_Set_FSE_Enable_Request(fse_en_req)	SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_FSE_ENABLE_CHANNEL,fse_en_req)

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
#define SOH_Set_GEN_Enable_Request(gen_en_req)	SIU_GPIO_DISCRETE_Set_State(HAL_GPIO_GEN_ENABLE_CHANNEL,gen_en_req)
	//mz38cg

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
extern void SOH_ETC_Initialize(bool power_on_reset_status);
extern void SOH_ETC_ISR(void);
extern void SOH_ETC_Update_Loop_Sequence_Array(const uint8_t ID_tag);
extern uint16_t SOH_ETC_Get_Fault_Log(void);

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

#endif /* } SOH_H */
