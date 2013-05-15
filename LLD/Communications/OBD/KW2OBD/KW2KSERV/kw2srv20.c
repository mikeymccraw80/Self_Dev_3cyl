/* ============================================================================ *\
 * kw2srv20.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv20.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, June 18, 2002 9:01:38 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $20 -  stop diagnostics
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */



#include "kw2type.h"
#include "kw2dll.h"
#include "kw2app.h"
#include "kw2srv10m.h"
#include "kw2srv20.h"
#include "kw2api.h"

#define Cy14230_MODE_20_MSG_LENGTH      (1)
#define Cy14230_MODE_20_RESP_MSG_LENGTH (1)


/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230StopDiagnosticSession                     *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 20 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/

void KwJ14230StopDiagnosticSession( void )
{

   if ( Cy14230_MODE_20_MSG_LENGTH !=
         GetKeyword2000ServiceDataLength ())
   {
    /* Invalid Message format */
    SendStandardNegativeAnswer(
                       nrcSubFunctionNotSupported_InvalidFormat  ) ;
   }
   else
   {

     /* If in default diagnostic state, reset all the actuators
        which are activated.
      */

      if ( CheckStandardDiagnosticState () )
      {
         /* If the security access is unlocked, than lock it */
         if ( true == GetVulnerabilityState ())
         {
           lockSecurityAccess ();

         }
        ResetActuatorsIfActivated ();
        SendStandardPositiveAnswer ( Cy14230_MODE_20_RESP_MSG_LENGTH );
      }
      else if ( CheckProgrammingState() )
      {
         SendStandardPositiveAnswer ( Cy14230_MODE_20_RESP_MSG_LENGTH );
         /* Reset the processor to change to DiagnosticMode. */
         SetECUResetPending(true) ;

      }
   }
}




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
