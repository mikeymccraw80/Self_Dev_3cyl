#ifndef ID_H
#define ID_H
/* ============================================================================ *\
 * id.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       id.h-5:incl:2
 * Revision:        5
 * Creation date:   Tuesday, June 04, 2002 2:03:00 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the program id
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "reuse.h"

/*************************** defines **************/

#define SoftwareNameSize                  (10)
#define CopyrightNoticeSize               (80)
#define SoftwareLevelSize                  (8)
/*************************** externs **************/

extern const char  SoftwareName[SoftwareNameSize];
extern const char  CopyrightNotice[CopyrightNoticeSize];
extern const uint8_t ProductionProgramId;
extern const char  SoftwareLevel[SoftwareLevelSize];


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 14/05/03     tmhau       -
 * + Baseline - Created for MT20U2 EOBD.
\* ============================================================================ */
#endif /* ID_H */

