#ifndef KW2SRV18_H
#define KW2SRV18_H
/* ============================================================================ *\
 * kw2srv18.h
 * ============================================================================
 * Copyright 1999,2002 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv18.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:12:33 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $18 - Read Diagnostic Code by status
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "t_base.h"

BYTE NumberOfDTC;
void KwJ14230ReadDiagnosticTroubleCodesByStatus( void ) ;


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 14/06/02     ndboer      28
 * + Baseline - Kokomo re-useable KW2000 module.
 *
 * 12/04/05     Q.W
 * + Add four KW2000 SIDs: 04,12,14,19
 *   -Add Variable: NumberOfDTC declaration.
\* ============================================================================ */
#endif