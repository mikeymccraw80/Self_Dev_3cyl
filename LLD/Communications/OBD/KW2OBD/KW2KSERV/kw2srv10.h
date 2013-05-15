#ifndef KW2SRV10_H
#define KW2SRV10_H
/* ============================================================================ *\
 * kw2srv10.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv10.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, June 18, 2002 9:01:31 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $10 -  start diagnostic session
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
extern bool   Utility_Download_Flag;

/*********************************************************************/
/*                  EXTERN FUNCTION DECLARATIONS                     */
/*********************************************************************/
extern void KwJ14230StartDiagnosticSession( void );
extern void KwJ14230ExecuteService10NextResponse( void );
extern  FAR_COS void InitKwJ14230StartDiagnosticSession( void );

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
 *   - Moved common definition to kw2srv10m.h.
 *
 * 08/07/05     Shoujun     mt20u2#1
 * + Reuse torque module from MT20 
 *   - Declared Utility_Download_Flag.
 *
\* ============================================================================ */
#endif
