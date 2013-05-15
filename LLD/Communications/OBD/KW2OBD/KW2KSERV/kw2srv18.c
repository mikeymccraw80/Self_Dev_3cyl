/* ============================================================================ *\
 * kw2srv14.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv18.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:12:25 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $18 - Read Diagnostic Code by status
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
#include "kw2api.h"

#include "kw2srv18.h"


#define MODE_18_MSG_LENGTH       (4)

#define IdxMask                  (1)
#define IdxGroupMSB              (2)
#define IdxGroupLSB              (3)

#define smAllDTC                 (0)
#define MaxNumOfDTCReturned      (8)

BYTE NumberOfDTC;            /* Although DTC number is over 256, the faults is less than 255 */
/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230ReadDiagnosticTroubleCodesByStatus        *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 18 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/

void KwJ14230ReadDiagnosticTroubleCodesByStatus( void )
{
/*
   uint8_t                 status_mask ;
   uint16_t                group ;
   uint8_t                 num_dtc_on ;
   MalfHistoryIndexType    i ;
   uint8_t                 TrByteCount ;
   kw2DtcInfoType          dtc_rec ;

   status_mask = GetKw2000ServiceData(IdxMask) ;
   group = ( (GetKw2000ServiceData(IdxGroupMSB) * 256)  | GetKw2000ServiceData(IdxGroupLSB) ) ;

   if ( ( GetKeyword2000ServiceDataLength() != MODE_18_MSG_LENGTH ) ||
        ( status_mask != smAllDTC ) ||
        ( (group != dgPowertrainGroup ) && ( group != dgAllGroup ) ) )
   {
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
   }
   else
   {
//      Diag group is PowerTrain or All and StatusMask is all
      num_dtc_on = Min( GetNumberOfMalfsLogged(), MaxNumOfDTCReturned ) ;
      TrByteCount = 1;
      WrtKw2000ServiceData( num_dtc_on, TrByteCount++);
      i = 0 ;
      while ( i < num_dtc_on )
      {
         GetIdAndStatusOfDTCSet( i++, &dtc_rec ) ;
         WrtKw2000ServiceData( Hi8Of16( (uint16_t)dtc_rec.DtcIdCode ), TrByteCount++);
         WrtKw2000ServiceData( Lo8Of16( (uint16_t)dtc_rec.DtcIdCode ), TrByteCount++);
         WrtKw2000ServiceData( dtc_rec.DtcStatus, TrByteCount++);
      }
      SendStandardPositiveAnswer (TrByteCount);
   }
*/
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
 * 12/04/05     Q.W
 * + Add four KW2000 SIDs: 04,12,14,19
 *   -Add Variable: NumberOfDTC definition.
\* ============================================================================ */
