/* ============================================================================ *\
 * kw2srv1a.c
 * ============================================================================
 * Copyright 1999,2002 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv1a.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:09 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $1A - Read ECU identification
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "kw2api.h"
#include "kw2app.h"
#include "kw2dll.h"
#include "kw2app.h"
#include "kw2cfg.h"
#include "kw2srv1a.h"
#include "id.h"
#include "HLS.h"


#define MODE_1A_MSG_LENGTH                  2
#define CyId                                1


void KwJ14230ReadEcuIdentification( void )
{
   uint16_t    idx ;
   uint8_t     TrBytes;

   if ( GetKeyword2000ServiceDataLength() != MODE_1A_MSG_LENGTH )
   {
       SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
   }
   else
   {
      switch ( GetKw2000ServiceData (CyId) )
      {
      case ioReportCheryECUIdentificationSWname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_SWVERNUM_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.SwVerNum[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationHWname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_HWVERNUM_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.HwVerNum[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationSerialNumbername:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_MDLSERNUM_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.MdlSerNum[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationOrPrgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_Original[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	 case ioReportCheryECUIdentificationNO1Prgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_No1[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationNO2Prgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_No2[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportCheryECUIdentificationNO3Prgname:
	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         /*--- Move ECUIdScalingTable [0..n-1] to (GetKeyword2000ServiceData ()) [1..n] ---*/
         for ( idx = 0 ; idx < SCN_ECUID_PRGINF_LENGHT ; idx++ )
         {
            WrtKw2000ServiceData( scnEcuId.PrgInf_No3[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;

	case ioReportVIN:

	   TrBytes = 1 ;
	    WrtKw2000ServiceData( GetKw2000ServiceData (CyId), TrBytes++ );

         
         for ( idx = 0 ; idx < 17 ; idx++ )
         {
            WrtKw2000ServiceData( scnVehInfo.VIN[idx], TrBytes++);
         }
         SendStandardPositiveAnswer( TrBytes ) ;
         break ;
		 
      default :
         SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
         break ;
      }
   }
}


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 14/06/02     ndboer      28
 * + Baseline - Kokomo re-useable KW2000 module.
 *
 * 23/05/03     sgchia      118
 * + Kw2000 DE broadcast code reading.
 *
 * 09/06/06     Jerry.Wu    mt20u2#51
 * + Update kword spec
 *   - Change table ECUIdScalingTable and function KwJ14230ReadEcuIdentification
 *
\* ============================================================================ */
