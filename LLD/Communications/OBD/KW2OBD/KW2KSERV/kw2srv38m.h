#ifndef KW2SRV38M_H
#define KW2SRV38M_H
/* ============================================================================ *\
 * kw2srv38m.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv38m.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, March 20, 2003 11:25:02 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $38 - Start routine by address (Minimized)
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

void KwJ14230MiniStartRoutineByAddr( void ) ;
void ExecuteStartRoutineByAddressFunction ( void ) ;


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *   - Added minimized KWP2000 Start routine by address (0x38) service. With no
 *     engine condition checks.
 *
\* ============================================================================ */
#endif
