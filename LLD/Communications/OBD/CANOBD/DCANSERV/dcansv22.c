/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
*  ALL RIGHTS RESERVED                                                 *
*  This program may not be reproduced, in whole or in part in any form *
*  or by any means whatsoever without the written permission of:       *
*                                                                      *
*         DELCO ELECTRONICS CORPORATION                                *
*         One Corporate Center                                         *
*         Kokomo, Indiana  46904-9005                                  *
*         USA                                                          *
*                                                                      *
************************************************************************
* Filename     : dcansv22.c                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : CANOBD                                *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 10 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 10 as the defined by the above applicable doc.*
*                                                                      *
*                Set the keyword 2000 diagnostic mode to be the        *
*                Standard Diagnostitic State or to be the              *
*                ECU Programming State by the request message.         *
*                In the ECU Programming State, this service can change *
*                the communication baud rate to be the desired baud    *
*                rate.                                                 *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2002:kw2srv10.c $              *
* $Revision$                                                     *
* $Author: brighton.tcb:/users/sa..._2002_MathLib:safayyad $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-12-98  JZha    Initial file creation                        *
* 3     13-08-30  xll     RCR1239 Modified LnReadDataByCommonIdentifier() *
* 5     14-04-03  tz9dw1  RSM8282 Modified dcansv22 for implementing   *
*                         TTE CAN IMMO into MT62p1                     *
* 6     14-04-23  tz9dw1  ctc_pt3#1529 Correct Conti IMMO security access *
*                                      delete TTEC_IMMO_ENABLED() and     *
*                                      TTE CAN IMMO compiler option       *
* 7     14-05-20  xll     RSM_CTC_8331_MT92_PCHUD_Function_Rev00_20140420.doc
******************************************************************************/
#include"dcansv22.h"
#if (XeDCAN_SID_22_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/

/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
// #include "obdlfpid.h"/*MaskMode_22*/
// #include "obdsfexi.h" //for IMMO include 
#include "dcanserv.h"
// #include "pchdpall.h"
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcancomm.h"
/***********************************************************************
* Functions in this file:                                              *
***********************************************************************/
#include "lux_type.h"
#include "filenvmd.h"
#include "id_cald.h"
#include "HLS.h"
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/

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
#define BaseModelSize		  	  (8)

#define rdliSecretKey                  (0x10)
#define rdliSecurityCode               (0x20)
#define rdliEe_immo_option             (0x30)

#define CgDelphiBaseModelPNAddr           (0x00000118)
#define CpDelphiBaseModelPNAddr_Ptr       (BYTE *) CgDelphiBaseModelPNAddr
extern T_COUNT_BYTE *const KW2000_DelphiBaseModelPN_Ptr;


#define CANPID_VALEO_READSC   (0x20B2)
#define CANPID_VALEO_DELIVERY (0x0300)
#define CANPID_CONTI_READSK   (0x0201)
#define CANPID_CONTI_READSC   (0x0206)
#define CANPID_HIRAIN_READSK_MTCHSTUS   (0x0202)
#define CANPID_HIRAIN_READSK            (0x0203)

#define  MaskMode_01 0x10
#define  MaskMode_02 0x20
#define  MaskMode_12 0x40
#define  MaskMode_22 0x80

#define  Mode_01 MaskMode_01
#define  Mode_02 MaskMode_02
#define  Mode_12 MaskMode_12 
#define  Mode_22 MaskMode_22 

#define EE_CalibrationData_Size             (96)

/*******************************************************************************/
/*** service: LnReadDataByCommonIdentifier      (SID22)                       ***/
/*** Reports the Diagnostic Data corresponding to the Parameter ID (2 bytes) ***/
/*******************************************************************************/
void LnReadDataByCommonIdentifier (void)
{
	uint8_t ParamID;
	uint8_t msglength;
	uint8_t Idx ;
	uint8_t *LpKW2000_DelphiBaseModelPN_Ptr;

	if(GetLnServiceDataLength () != 2) {
		/* Request should be atleast 2 bytes long */
		SendLnStandardNegativeAnswer (IncorrectMessageLength);
	} else  {
		/* Prepare response */
		msglength = 1;
		ParamID = (uint8_t) (GetLnServiceData ())[1];

		switch(ParamID) {
		case rdliSnapshot:
			WrtDCAN_ServiceData(ParamID, msglength++);
			WrtDCAN_ServiceData( FCMEnd, msglength++);
			WrtDCAN_ServiceData( MafTst, msglength++);
			WrtDCAN_ServiceData( TmLin, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(fLc), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fLc), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(fLcAd), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fLcAd), msglength++);
			WrtDCAN_ServiceData( Pmap_b, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(N), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(N), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(VspRaw), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(VspRaw), msglength++);
			WrtDCAN_ServiceData( IgaOut, msglength++);
			WrtDCAN_ServiceData( TaLin, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(KmQ1Mil), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(KmQ1Mil), msglength++);
			WrtDCAN_ServiceData( Ub_b, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uTm), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTm), msglength++);
			WrtDCAN_ServiceData( uTa, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uPmap), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uPmap), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(Fl), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Fl), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(Hi16Of32(Ti)), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Hi16Of32(Ti)), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(Lo16Of32(Ti)), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Lo16Of32(Ti)), msglength++);
			WrtDCAN_ServiceData( Nstat, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(dN), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dN), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(dTqLosAd), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dTqLosAd), msglength++);
			WrtDCAN_ServiceData( dIgaKncDyn, msglength++);
			WrtDCAN_ServiceData( B_Knk, msglength++);
			WrtDCAN_ServiceData( Maf_b, msglength++);
			WrtDCAN_ServiceData( Ld_b, msglength++);
			WrtDCAN_ServiceData( Gr, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(fAlt), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fAlt), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(dTqIdcP), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dTqIdcP), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(dTqIdcI), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dTqIdcI), msglength++);
			WrtDCAN_ServiceData( dIgaKnc[0], msglength++);
			WrtDCAN_ServiceData( dIgaKnc[1], msglength++);
			WrtDCAN_ServiceData( dIgaKnc[2], msglength++);
			WrtDCAN_ServiceData( dIgaKnc[3], msglength++);
			WrtDCAN_ServiceData( Hi8Of16(FtCntEmis), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmis), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl[0]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl[0]), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl[1]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl[1]), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl[2]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl[2]), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl[3]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl[3]), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(RounFon), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(RounFon), msglength++);
			WrtDCAN_ServiceData( B_Fan1, msglength++);
			WrtDCAN_ServiceData( B_Fan2, msglength++);
			WrtDCAN_ServiceData( B_AcOn, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uLsb), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uLsb), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uLsa), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uLsa), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(tLsbAfFlt), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(tLsbAfFlt), msglength++);
			WrtDCAN_ServiceData( IntLcDwnI, msglength++);
			WrtDCAN_ServiceData( SsCatDwnM, msglength++);
			WrtDCAN_ServiceData( MxGrdLsaFit_b, msglength++);
			WrtDCAN_ServiceData( B_LsaRdy, msglength++);
			WrtDCAN_ServiceData( Acl_b, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(TcatInPre), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TcatInPre), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uTp1), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTp1), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uTp2), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTp2), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(TpPosDpc), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TpPosDpc), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(TpPos), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TpPos), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(dpcpids), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dpcpids), msglength++);
			WrtDCAN_ServiceData( B_dpcPids, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uPed1), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uPed1), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uPed2), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uPed2), msglength++);
			WrtDCAN_ServiceData( PedPos_b, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(AngCamOvlapAdj), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(AngCamOvlapAdj), msglength++);
			WrtDCAN_ServiceData( fctCamOvlapIn_b, msglength++);
			WrtDCAN_ServiceData( fctCamOvlapOut_b, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(DyCyPsIn), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(DyCyPsIn), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(DyCyPsOut), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(DyCyPsOut), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(DuCyPgOut), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(DuCyPgOut), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(FlPg), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FlPg), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(fPgRatDsr), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fPgRatDsr), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(fPgAdp), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fPgAdp), msglength++);
			WrtDCAN_ServiceData( Tam, msglength++);
			WrtDCAN_ServiceData( StcEtcAdpt, msglength++);
			WrtDCAN_ServiceData( ScSpr, msglength++);
			WrtDCAN_ServiceData( ScAntiIce, msglength++);
			WrtDCAN_ServiceData( ScLrn, msglength++);
			WrtDCAN_ServiceData( B_LrnSuc, msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uTp1Lw), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTp1Lw), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(uTp2Lw), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTp2Lw), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(TpPosNlp), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TpPosNlp), msglength++);
			WrtDCAN_ServiceData( FrBitsEtsm, msglength++);
			WrtDCAN_ServiceData( B_FofEtsm, msglength++);
			SendLnStandardPositiveAnswer( msglength ) ;
		break;



		case rdliEndModelNumber:
			WrtDCAN_ServiceData(ParamID, msglength++);
			for(Idx = 0 ; Idx < (EndModelSize/2) ; Idx++ ) {
				WrtDCAN_ServiceData(NsFILE_NVM_EE_ManufactData.VaFILE_EE_HexEndModelNumber[Idx], msglength++);
			}
			SendLnStandardPositiveAnswer( msglength ) ;
		break ;

		case rdliBaswModelNumber:
			WrtDCAN_ServiceData(ParamID, msglength++);
			LpKW2000_DelphiBaseModelPN_Ptr = (uint8_t *)KW2000_DelphiBaseModelPN_Ptr;
			for(Idx = 0 ; Idx < (BaseModelSize/2) ; Idx++ ) {
				WrtDCAN_ServiceData(*LpKW2000_DelphiBaseModelPN_Ptr++, msglength++);
			}  
			SendLnStandardPositiveAnswer( msglength ) ;
		break ;

		case rdliBCCNumber:
			WrtDCAN_ServiceData(ParamID, msglength++);
			for ( Idx = 0 ; Idx < sizeof( DEBroadcastCode ) ; Idx++ ) {
				WrtDCAN_ServiceData( DEBroadcastCode[Idx], msglength++);
			}
			SendLnStandardPositiveAnswer( msglength ) ;
		break ;

		case rdliMileage:
			WrtDCAN_ServiceData(ParamID, msglength++);

			/*--- Fill table with mileage accumulation ---*/
			WrtDCAN_ServiceData(NsFILE_NVM_EE_ManufactData.VaFILE_EE_Odometer[0], msglength++);
			WrtDCAN_ServiceData(NsFILE_NVM_EE_ManufactData.VaFILE_EE_Odometer[1], msglength++);
			WrtDCAN_ServiceData(NsFILE_NVM_EE_ManufactData.VaFILE_EE_Odometer[2], msglength++);
			WrtDCAN_ServiceData(NsFILE_NVM_EE_ManufactData.VaFILE_EE_Odometer[3], msglength++);
			SendLnStandardPositiveAnswer( msglength ) ;
			break ;

		default :
			SendLnStandardNegativeAnswer( RequestOutOfRange ) ;
			break ;
		}
	}
} /*** End of LnReadDataByCommonIdentifier ***/

#endif




