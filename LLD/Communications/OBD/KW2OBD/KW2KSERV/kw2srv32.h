#ifndef KW2SRV32_H
#define KW2SRV32_H
/* ============================================================================ *\
 * kw2srv31.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv31.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:50 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $31 - Start routine by local ID
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

void KwJ14230StopRoutineByLocalIdentifier( void );



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 29/01/07     LShoujun    mt20u2#76
 * + Clear nvram area after re-programming with KWP2000
 *   - Declared NbFILE_NVM_Reset_RequestFromSerial
 *
\* ============================================================================ */
#endif