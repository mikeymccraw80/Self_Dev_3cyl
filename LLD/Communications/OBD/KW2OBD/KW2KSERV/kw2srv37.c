/* ============================================================================ *\
 * kw2srv37.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv37.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 9:56:47 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $37 - Request transfer exit
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
#include "kw2srv37.h"
#include "kw2srv36.h"
#include "kw2srv10m.h"


#define      Sy14230_SERVICE_37_MSG_LENGTH        (1)
#define      CyTRANSMIT_DATA_SIZE                 (1)

/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230RequestTransferExit                       *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 37 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
************************************************************************/
void KwJ14230RequestTransferExit( void )
{
   if (GetKeyword2000ServiceDataLength() != Sy14230_SERVICE_37_MSG_LENGTH)
   {
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
   }
   else if (! CheckProgrammingState())
   {
      SendStandardNegativeAnswer( nrcServiceNotSupportedInActiveDiagnosticMode );
   }
   else if ( CheckIfDataTransferNotInProgress ())
   {
      SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError );
   }
   else
   {
      SendStandardPositiveAnswer(CyTRANSMIT_DATA_SIZE);
      SetTransferStateToNotTransfering ();
   }
} /*** End of KwJ14230RequestTransferExit ***/




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
 *   - added header kw2srv10m.h.
 *
\* ============================================================================ */
