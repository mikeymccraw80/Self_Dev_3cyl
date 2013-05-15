/* ============================================================================ *\
 * kw2srv14.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv14.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:12:12 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $14 - Clear Diagnostics Information
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#if 0

#include "kw2type.h"
#include "kw2dll.h"
#include "kw2app.h"
#include "kw2api.h"

#include "kw2srv14.h"

#include "dg_malf.h" /* For ClearAllMalfLogged() */

#define MODE_14_MSG_LENGTH       (3)
#define MODE_14_RESP_MSG_LENGTH  (3)

#define IdxGroupMSB              (1)
#define IdxGroupLSB              (2)


/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230ErrorCodeClearRequest                     *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 14 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/
void KwJ14230ErrorCodeClearRequest( void )
{
   uint16_t    group;

   group = (( GetKw2000ServiceData( IdxGroupMSB ) * 256) | GetKw2000ServiceData( IdxGroupLSB ));

   if (   (MODE_14_MSG_LENGTH != GetKeyword2000ServiceDataLength () )
       || ( (group != dgPowertrainGroup) && (group != dgAllGroup)))
   {
      /* Invalid Message format */
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat  ) ;
   }
   else
   {
      /*  Valid diagnostics clear command */
      ClearAllMalfLogged();
      WrtKw2000ServiceData( Hi8Of16(group), IdxGroupMSB);
      WrtKw2000ServiceData( Lo8Of16(group), IdxGroupLSB);
      SendStandardPositiveAnswer( MODE_14_RESP_MSG_LENGTH );
   }
}


#endif

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 26/05/03     wxhe        120
 * + KWP2000 error.
 *
\* ============================================================================ */
