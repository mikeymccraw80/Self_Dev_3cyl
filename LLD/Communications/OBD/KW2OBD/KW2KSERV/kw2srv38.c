/* ============================================================================ *\
 * kw2srv38.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv38.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 9:56:57 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $38 - Start routine by address
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "kw2dll.h"
#include "kw2api.h"
#include "kw2srv38.h"
#include "kw2srv38m.h"

/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230StartRoutineByAddress                     *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 38 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/
void KwJ14230StartRoutineByAddress( void )
{
   if ( Get_EngineTurning() )
   {
      SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError );
   }
   else
   {
      KwJ14230MiniStartRoutineByAddr();
   }
} /*** End of KwJ14230StartRoutineByAddress ***/




/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */
