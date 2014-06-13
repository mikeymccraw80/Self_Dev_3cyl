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
 * /-----------------------------------------------------------------------\
 * | ETC Check (SOH as watchdog of the ETC)
 * \-----------------------------------------------------------------------/
\*===========================================================================*/
typedef enum HWIO_ETC_SOH_FAULT_MASK_Tag
{
   CwHWIO_ETC_SOH_SYS_CLK_FREQ_FLT_MASK      = 0x8000,   /* System clock frequency error, main CPU      */
   CwHWIO_ETC_SOH_INTRT_SRC_FLT_MASK         = 0x4000,   /* Interrupt source error,       main CPU      */
   CwHWIO_ETC_SOH_SYS_TMR_FLT_MASK           = 0x2000,   /* System timer error,           main CPU      */
   CwHWIO_ETC_SOH_TST_SEQN_FLT_MASK          = 0x1000,   /* Test sequence error,          main CPU      */
   CwHWIO_ETC_SOH_RTI_FREQ_FLT_MASK          = 0x0800,   /* RTI frequency error,          main CPU      */
   CwHWIO_ETC_SOH_CPU_LOOP_SEQN_FLT_MASK     = 0x0400,   /* CPU loop sequence error,      main CPU      */
   CwHWIO_ETC_SOH_C_AND_R_CNTR_LOW_FLT_MASK  = 0x0200,   /* SOH C&R counter value low,    checking CPU  */
   CwHWIO_ETC_SOH_SHUTOFF_TMR_EXPRD_FLT_MASK = 0x0100,   /* Shutoff timer expired,        main CPU      */
   CwHWIO_ETC_SOH_SPI_FLT_MASK               = 0x0080,   /* SPI error,                    communication */
   CwHWIO_ETC_SOH_SPI_COMM_FLT_MASK          = 0x0040,   /* SPI communication error,      communication */
   CwHWIO_ETC_SOH_C_AND_R_DISARMD_FLT_MASK   = 0x0020,   /* SOH C&R disarmed,             checking CPU  */
   CwHWIO_ETC_SOH_C_AND_R_TMOUT_FLT_MASK     = 0x0010,   /* SOH C&R timeout,              checking CPU  */
   CwHWIO_ETC_SOH_C_AND_R_CNTR_ZERO_FLT_MASK = 0x0008,   /* SOH C&R counter value zero,   checking CPU  */

   CwHWIO_ETC_SOH_MAIN_CPU_FLTS_MASK =
                        CwHWIO_ETC_SOH_SYS_CLK_FREQ_FLT_MASK
                      | CwHWIO_ETC_SOH_INTRT_SRC_FLT_MASK
                      | CwHWIO_ETC_SOH_SYS_TMR_FLT_MASK
                      | CwHWIO_ETC_SOH_TST_SEQN_FLT_MASK
                      | CwHWIO_ETC_SOH_RTI_FREQ_FLT_MASK
                      | CwHWIO_ETC_SOH_CPU_LOOP_SEQN_FLT_MASK
                      | CwHWIO_ETC_SOH_SHUTOFF_TMR_EXPRD_FLT_MASK,
   CwHWIO_ETC_SOH_CHKNG_CPU_FLTS_MASK =
                        CwHWIO_ETC_SOH_C_AND_R_CNTR_LOW_FLT_MASK
                      | CwHWIO_ETC_SOH_C_AND_R_DISARMD_FLT_MASK
                      | CwHWIO_ETC_SOH_C_AND_R_TMOUT_FLT_MASK
                      | CwHWIO_ETC_SOH_C_AND_R_CNTR_ZERO_FLT_MASK,
   CwHWIO_ETC_SOH_COMM_FLTS_MASK =
                        CwHWIO_ETC_SOH_SPI_FLT_MASK
                      | CwHWIO_ETC_SOH_SPI_COMM_FLT_MASK,

   CwHWIO_ETC_SOH_ALL_FLTS_MASK =
                        CwHWIO_ETC_SOH_MAIN_CPU_FLTS_MASK
                      | CwHWIO_ETC_SOH_CHKNG_CPU_FLTS_MASK
                      | CwHWIO_ETC_SOH_COMM_FLTS_MASK

} TeHWIO_ETC_SOH_FAULT_MASK;

#define GetHWIO_ETC_SOH_FltVaMask(fault, mask) \
    ( ((TeHWIO_ETC_SOH_FAULT_MASK )fault & mask) ? CbTRUE : CbFALSE )

#define GetHWIO_ETC_SOH_FltActnTaken(fault) \
    GetHWIO_ETC_SOH_FltVaMask( fault, CwHWIO_ETC_SOH_SHUTOFF_TMR_EXPRD_FLT_MASK )

#define GetHWIO_ETC_SOH_MainCPU_FltPrsnt(fault) \
    GetHWIO_ETC_SOH_FltVaMask( fault, CwHWIO_ETC_SOH_MAIN_CPU_FLTS_MASK )

#define GetHWIO_ETC_SOH_ChkngCPU_FltPrsnt(fault) \
    GetHWIO_ETC_SOH_FltVaMask( fault, CwHWIO_ETC_SOH_CHKNG_CPU_FLTS_MASK )

#define GetHWIO_ETC_SOH_Comm_FltPrsnt(fault) \
    GetHWIO_ETC_SOH_FltVaMask( fault, CwHWIO_ETC_SOH_COMM_FLTS_MASK )

#define GetHWIO_ETC_SOH_FltPrsnt(fault) \
    GetHWIO_ETC_SOH_FltVaMask( fault, CwHWIO_ETC_SOH_ALL_FLTS_MASK )

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
