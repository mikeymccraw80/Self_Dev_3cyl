/* ============================================================================ *\
 * kw2api.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2api.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:12 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 application interface.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "kw2api.h"

//typedef union
//{
//   uint8_t     ubyte;
 //  uint16_t    uword;
//} BYTEANDWORD1;


/*********************************************************************/
/* This parameter shall report reset status information.  It is the  */
/* vehicle manufacturer's responsibility to define the data value(s) */
/*********************************************************************/
const uint8_t ECUResetStatusTable [ ] =
{
   0x01
};

const uint8_t ECUResetStatusSize = sizeof (ECUResetStatusTable);



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
 *   - moved GetSrv10BaudRate() out of this file.
 *
 * March/09/2006 Q.W     mt20u2#47
 * + Support SAE J1979 kw2000 modes
 *   -delete redundant function define, remove constant define
\* ============================================================================ */
