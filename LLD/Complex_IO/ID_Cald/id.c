/* ============================================================================ *\
 * id.c
 * ============================================================================
 * Copyright 1999,2002 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       id.c-5:csrc:2
 * Revision:        5
 * Creation date:   Tuesday, June 04, 2002 2:02:58 PM
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

#include "id.h"
#include "reuse.h"

#define COPYRIGHT_NOTICE            "Copyright \xA9 1999,2003 Delphi Technologies, Inc., All Rights Reserved"

const uint8_t ProductionProgramId = 0x08;

const char  SoftwareName[SoftwareNameSize] = "CEDBSO0000";

const char  CopyrightNotice[CopyrightNoticeSize] = COPYRIGHT_NOTICE;

const char  SoftwareLevel[SoftwareLevelSize] = "CDESSO00";
/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
 \* ============================================================================ */

