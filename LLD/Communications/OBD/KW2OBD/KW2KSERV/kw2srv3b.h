#ifndef KW2SRV3B_H
#define KW2SRV3B_H
/* ============================================================================ *\
 * kw2srv18.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv3b.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:13:37 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $3B - Write data by local identifier.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

extern void KwJ14230WriteDataByLocalIdentifier( void ) ;
//extern void ModifyEepromData( void );



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 12/03/07     LShoujun    mt20u2#79    
 * + new generic immo requirement change after P3 
 *   - Declared ModifyEepromData()
 *
\* ============================================================================ */
#endif