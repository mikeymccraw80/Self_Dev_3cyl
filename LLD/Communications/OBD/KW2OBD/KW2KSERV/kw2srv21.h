#ifndef KW2SRV21_H
#define KW2SRV21_H
/* ============================================================================ *\
 * kw2srv21.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv21.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:12:50 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $21 - Read data by local identifier
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
//extern WORD      NaDGDM_DiagTestData_Status;
//extern WORD      FailRecord_DTC_ID;

extern void KwJ14230ReadDataByLocalIdentifier( void ) ;



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 05/30/05     Shoujun     303
 * + Update Snap Shot of PCHUD 
 *   - Declared NaDGDM_DiagTestData_Status and FailRecord_DTC_ID 
 *
\* ============================================================================ */
#endif
