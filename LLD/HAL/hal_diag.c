/* ============================================================================ *\
 * hal_diag.c
 * ============================================================================
 * Copyright 1999,2004 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       hal_diag.c
 * Revision:        1
 * Creation date:
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   Hardware test software - PSVI diagnostic test.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"
#include "hal_diag.h"
#include "dd_l9958_interface.h"

uint16_t HAL_Diag_Get_L9958_HWDiag_Status(void)
{
    return L9958_FAULT_Get_HWDiag_Status();
}


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *   110420   hzm   updated for StartStop Application
 *
\*===========================================================================*/
