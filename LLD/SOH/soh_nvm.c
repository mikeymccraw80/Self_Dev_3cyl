/*===========================================================================*\
 * FILE: soh_nvm.c
 *===========================================================================
 * Copyright 2006 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *---------------------------------------------------------------------------
 * %full_filespec:  soh_nvm.c~2:csrc:mt20u2#1 %
 * %version:  2 %
 * %derived_by:  wzmkk7 %
 * %date_modified: %
 * $SOURCE: $
 * $REVISION: $
 * $AUTHOR: $
 *---------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *   ETC SOH building block software - non-volatile memory.
 *   Variables defined in this file shall be placed in non-volatile memory
 *   area of the microprocessor.
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
#include "soh_common.h"

/* ETC SOH fault log */
Soh_Fault_Log_T Soh_FaultLogNVM;



/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date        userid    (Description on following lines: SCR #, etc.)
 * ----------- --------
 * 26 Jan 06  qzc
 * + Created initial file.
 *
\*===========================================================================*/
