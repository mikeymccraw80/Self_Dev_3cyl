/* ============================================================================ *\
 * kw2srv21.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv21.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Wednesday, June 19, 2002 2:12:40 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $21 - Read data by local identifier
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */


#include "reuse.h"
#include "kw2type.h"
#include "kw2dll.h"
#include "kw2app.h"
#include "kw2api.h"
// #include "kw2dynsh.h"
#include "kw2srv21.h"
#include "HLS.h"
#include "id_cald.h"
// #include "hal_esc.h"
// #include "hal_mileage.h"



#define Cy14230_MODE_21_MSG_LENGTH      (2)

#define IdxLocalIdentifier              (1)

#define rdliSnapshot                      (0x01)
#define rdliEndModelNumber		  (0x03)
#define rdliBaswModelNumber		  (0x04)
#define rdliBCCNumber			  (0x05)
#define rdliBLMCells			  (0x09)
#define rdliCrankShaftAdaptiveCylinder	  (0x0A)
#define rdliTECDSampleCounter		  (0x0B)
#define rdliMECCounter			  (0xA0)
#define rdliVIN                           (0x90)
#define rdliMileage                       (0xC0)
#define rdliEngRuntime                    (0xA1)

#define rdliAddressTableSnapshot1         (0x11)
#define rdliAddressTableSnapshot2         (0x12)
#define rdliAddressTableSnapshot3         (0x13)
#define rdliAddressTableSnapshot4         (0x14)
#define rdliAddressTableSnapshot5         (0x15)
#define rdliAddressTableSnapshot6         (0x16)
#define rdliAddressTableSnapshot7         (0x17)
#define rdliAddressTableSnapshot8         (0x18)
#define rdliAddressTableSnapshot9         (0x19)

#define RESEVEDBYTE			  (0x00)
#define EndModelSize		  	  (8)

#define rdliSecretKey                  (0x10)
#define rdliSecurityCode               (0x20)
#define rdliEe_immo_option             (0x30)



/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230ReadDataByLocalIdentifier                 *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 21 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/
void KwJ14230ReadDataByLocalIdentifier( void )
{
	uint8_t  TrByteCount,Idx,  siz, LyIdx1  ;
	uint8_t  TempData;
	uint32_t TempDataLong, TempDataForWrite;

	if ( Cy14230_MODE_21_MSG_LENGTH != GetKeyword2000ServiceDataLength () ) {
		/* Invalid Message format */
		SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
	} else {
		TrByteCount = 1;
		switch ( GetKw2000ServiceData(IdxLocalIdentifier) ) {
			case rdliSnapshot:
				WrtKw2000ServiceData( GetKw2000ServiceData(IdxLocalIdentifier), TrByteCount++);
				WrtKw2000ServiceData( 0x61, TrByteCount++); //Read Data By Local Identifier Positive Response
				WrtKw2000ServiceData( 0x01, TrByteCount++); //Record Local Identifier = snapshot
				WrtKw2000ServiceData( FCMEnd, TrByteCount++);
				WrtKw2000ServiceData( TmLin, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(fLc), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(fLc), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(fLcAd), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(fLcAd), TrByteCount++);
				WrtKw2000ServiceData( Pmap_b, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(N), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(N), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(VspRaw), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(VspRaw), TrByteCount++);
				WrtKw2000ServiceData( IgaOut, TrByteCount++);
				WrtKw2000ServiceData( TaLin, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(KmQ1Mil), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(KmQ1Mil), TrByteCount++);
				WrtKw2000ServiceData( Ub_b, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uTm), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uTm), TrByteCount++);
				WrtKw2000ServiceData( uTa, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uPmap), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uPmap), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(Fl), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(Fl), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(Hi16Of32(Ti)), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(Hi16Of32(Ti)), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(Lo16Of32(Ti)), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(Lo16Of32(Ti)), TrByteCount++);
				WrtKw2000ServiceData( Nstat, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(dN), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(dN), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(dTqLosAd), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(dTqLosAd), TrByteCount++);
				WrtKw2000ServiceData( dIgaKncDyn, TrByteCount++);
				WrtKw2000ServiceData( B_Knk, TrByteCount++);
				WrtKw2000ServiceData( Maf_b, TrByteCount++);
				WrtKw2000ServiceData( Ld_b, TrByteCount++);
				WrtKw2000ServiceData( Gr, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(fAlt), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(fAlt), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(dTqIdcP), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(dTqIdcP), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(dTqIdcI), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(dTqIdcI), TrByteCount++);
				WrtKw2000ServiceData( dIgaKnc[0], TrByteCount++);
				WrtKw2000ServiceData( dIgaKnc[1], TrByteCount++);
				WrtKw2000ServiceData( dIgaKnc[2], TrByteCount++);
				WrtKw2000ServiceData( dIgaKnc[3], TrByteCount++);
				WrtKw2000ServiceData( FtCntEmis, TrByteCount++);
				WrtKw2000ServiceData( FtCntEmisCyl[0], TrByteCount++);
				WrtKw2000ServiceData( FtCntEmisCyl[1], TrByteCount++);
				WrtKw2000ServiceData( FtCntEmisCyl[2], TrByteCount++);
				WrtKw2000ServiceData( FtCntEmisCyl[3], TrByteCount++);
				WrtKw2000ServiceData( RounFon, TrByteCount++);
				WrtKw2000ServiceData( B_Fan1, TrByteCount++);
				WrtKw2000ServiceData( B_Fan2, TrByteCount++);
				WrtKw2000ServiceData( B_AcOn, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uLsb), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uLsb), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uLsa), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uLsa), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(tLsbAfFlt), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(tLsbAfFlt), TrByteCount++);
				WrtKw2000ServiceData( IntLcDwnI, TrByteCount++);
				WrtKw2000ServiceData( SsCatDwnM, TrByteCount++);
				WrtKw2000ServiceData( MxGrdLsaFit_b, TrByteCount++);
				WrtKw2000ServiceData( B_LsaRdy, TrByteCount++);
				WrtKw2000ServiceData( Acl_b, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(TcatInPre), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(TcatInPre), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uTp1), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uTp1), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uTp2), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uTp2), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(TpPosDpc), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(TpPosDpc), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(TpPos), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(TpPos), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(dpcpids), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(dpcpids), TrByteCount++);
				WrtKw2000ServiceData( B_dpcPids, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uPed1), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uPed1), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uPed2), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uPed2), TrByteCount++);
				WrtKw2000ServiceData( PedPos_b, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(AngCamOvlapAdj), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(AngCamOvlapAdj), TrByteCount++);
				WrtKw2000ServiceData( fctCamOvlapIn_b, TrByteCount++);
				WrtKw2000ServiceData( fctCamOvlapOut_b, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(DyCyPsIn), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(DyCyPsIn), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(DyCyPsOut), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(DyCyPsOut), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(DuCyPgOut), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(DuCyPgOut), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(FlPg), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(FlPg), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(fPgRatDsr), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(fPgRatDsr), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(fPgAdp), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(fPgAdp), TrByteCount++);
				WrtKw2000ServiceData( Tam, TrByteCount++);
				WrtKw2000ServiceData( StcEtcAdpt, TrByteCount++);
				WrtKw2000ServiceData( ScSpr, TrByteCount++);
				WrtKw2000ServiceData( ScAntiIce, TrByteCount++);
				WrtKw2000ServiceData( ScLrn, TrByteCount++);
				WrtKw2000ServiceData( B_LrnSuc, TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uTp1Lw), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uTp1Lw), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(uTp2Lw), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(uTp2Lw), TrByteCount++);
				WrtKw2000ServiceData( Hi8Of16(TpPosNlp), TrByteCount++);
				WrtKw2000ServiceData( Lo8Of16(TpPosNlp), TrByteCount++);
				WrtKw2000ServiceData( FrBitsEtsm, TrByteCount++);
				WrtKw2000ServiceData( B_FofEtsm, TrByteCount++);
				SendStandardPositiveAnswer( TrByteCount ) ;
			break;

			case rdliEndModelNumber:
				WrtKw2000ServiceData( GetKw2000ServiceData(IdxLocalIdentifier), TrByteCount++);
				TempDataLong = 0;
				TempDataForWrite = 0;
				for ( Idx = 0 ; Idx < EndModelSize ; Idx++ ) {
					if(EndModelNumber[Idx] < 0x30 || EndModelNumber[Idx] > 0x39) {
						TempDataLong= 0;
					} else {
						TempDataLong = EndModelNumber[Idx] & 0x0f ;                  
					} 
					for( LyIdx1 = 0 ; LyIdx1 < (7-Idx) ; LyIdx1++ ) {
						TempDataLong = TempDataLong * 10;
					}
					TempDataForWrite += TempDataLong;
				}
				for(Idx = 0 ; Idx < (EndModelSize/2) ; Idx++ ) {
					TempData = ( (TempDataForWrite >> ((3-Idx)*8)) & 0xff);
					WrtKw2000ServiceData( TempData, TrByteCount++);
				}
				SendStandardPositiveAnswer( TrByteCount ) ;
			break ;

			case rdliBaswModelNumber:
				WrtKw2000ServiceData( GetKw2000ServiceData(IdxLocalIdentifier), TrByteCount++);
				TempDataLong= 0;
				TempDataForWrite = 0;
				for ( Idx = 0 ; Idx < sizeof(BaseModelNumber) ; Idx++ ) {
					if(BaseModelNumber[Idx] < 0x30 || BaseModelNumber[Idx] > 0x39) {
						TempDataLong= 0;
					}
					else {
						TempDataLong = BaseModelNumber[Idx] & 0x0f ;
					}
					for( LyIdx1 = 0 ; LyIdx1 < (7-Idx) ; LyIdx1++ ) {
						TempDataLong = TempDataLong * 10;
					}
				TempDataForWrite += TempDataLong;
				}
				for(Idx = 0 ; Idx < ((sizeof(BaseModelNumber))/2) ; Idx++ ) {
					TempData = ( (TempDataForWrite >> ((3-Idx)*8)) & 0xff);
					WrtKw2000ServiceData( TempData, TrByteCount++);
				}  
				SendStandardPositiveAnswer( TrByteCount ) ;
			break ;

			case rdliBCCNumber:
				WrtKw2000ServiceData( GetKw2000ServiceData(IdxLocalIdentifier), TrByteCount++);
				for ( Idx = 0 ; Idx < sizeof( DEBroadcastCode ) ; Idx++ ) {
					WrtKw2000ServiceData( DEBroadcastCode[Idx], TrByteCount++);
				}
				SendStandardPositiveAnswer( TrByteCount ) ;
			break ;

#if 0
       case rdliMileage:
            WrtKw2000ServiceData( GetKw2000ServiceData(IdxLocalIdentifier), TrByteCount++);

            /*--- Fill table with mileage accumulation ---*/
            WrtKw2000ServiceData( Hi8Of16( Hi16Of32( Mileage ) ), TrByteCount++);
            WrtKw2000ServiceData( Lo8Of16( Hi16Of32( Mileage ) ), TrByteCount++);
            WrtKw2000ServiceData( Hi8Of16( Lo16Of32( Mileage ) ), TrByteCount++);
            WrtKw2000ServiceData( Lo8Of16( Lo16Of32( Mileage ) ), TrByteCount++);
            SendStandardPositiveAnswer( TrByteCount ) ;
            break ;           
#endif

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
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
\* ============================================================================ */

