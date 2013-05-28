#ifndef V_KWEXEC_H
#define V_KWEXEC_H
/* ============================================================================ *\
 * kw2exec.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2exec.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:10:11 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 executive.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/***********************LOCAL DEFINITIONS:*****************************/
#include "kw2dll.h"

typedef enum {
	CwKW2000_Initializes,
	CwKW2000_RunMode,
	CwImmoTester_RunMode
} KW2000_Status_T;

void KeywordExecutive(KW2000_Status_T);


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - Changed to support generic immo
\* ============================================================================ */
#endif