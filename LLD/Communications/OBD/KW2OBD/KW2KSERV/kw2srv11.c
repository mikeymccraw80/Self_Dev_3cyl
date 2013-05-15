/* ============================================================================ *\
 * kw2srv11.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv11.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:12:00 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $11 -  ECU reset
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
#include "kw2srv10.h"
#include "kw2srv20.h"
#include "kw2api.h"

#define MODE_11_MSG_LENGTH       (2)
#define MODE_11_RESP_MSG_LENGTH  (1)
#define IdxResetMode             (1)
#define rmPowerOn                (0x01)
#define CyId                     (1)

/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230EcuReset                                  *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 11 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/

void KwJ14230EcuReset( void )
{
   uint8_t     TrBytes;
   if ( MODE_11_MSG_LENGTH != GetKeyword2000ServiceDataLength () )
   {
      /* Invalid Message format */
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat  ) ;
   }
   else
   {
      /* If in default diagnostic state, reset all the actuators
         which are activated.
       */
      if ( GetKw2000ServiceData( IdxResetMode ) == rmPowerOn )
      {
         /* If the security access is unlocked, then allow reset */
         if ( true == GetVulnerabilityState ())
         {
            TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );
            SendStandardPositiveAnswer ( TrBytes );
            SetECUResetPending( true );
         }
         else
         {
            SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested  ) ;
         }
      }
      else
      {
         SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat  ) ;
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
 * 05/June/06	Jerry.Wu   mt20u2#51
 * + update kword 11 module according to spec.
 *  - Modify function KwJ14230EcuReset
 *
\* ============================================================================ */
