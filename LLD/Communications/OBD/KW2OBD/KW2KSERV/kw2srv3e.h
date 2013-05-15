#ifndef KW2SRV3E_H
#define KW2SRV3E_H
/* ============================================================================ *\
 * kw2srv3e.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv3e.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, June 18, 2002 9:01:12 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $3E - Tester present
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

extern uint16_t            TimerBeforeNewMsgRx; /* 0xFFFF == infinite */


extern void KwJ14230TesterPresent( void );




/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
\* ============================================================================ */
#endif
