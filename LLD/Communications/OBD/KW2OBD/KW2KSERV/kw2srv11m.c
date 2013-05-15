/* ============================================================================ *\
 * kw2srv11m.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv11m.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, March 20, 2003 11:22:07 AM
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
#include "kw2srv11m.h"
//#include "kw2app.h"
//#include "kw2srv10.h"
//#include "kw2srv20.h"
//#include "kw2api.h"

#define MODE_11_MSG_LENGTH       (2)
#define MODE_11_RESP_MSG_LENGTH  (1)
#define IdxResetMode             (1)
#define rmPowerOn                (0x01)


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

FAR_COS void KwJ14230MiniEcuReset( void )
{
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
         SetECUResetPending( true );
         SendStandardPositiveAnswer ( MODE_11_RESP_MSG_LENGTH );
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
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *
\* ============================================================================ */
