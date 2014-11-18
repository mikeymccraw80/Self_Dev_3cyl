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

#define rdli_PID0100                      (0x0100)
#define rdli_PID0101                      (0x0101)
#define rdli_PID0102                      (0x0102)
#define rdli_PID0103                      (0x0103)
#define rdli_PID0104                      (0x0104)
#define rdli_PID0105                      (0x0105)
#define rdli_PID0106                      (0x0106)
#define rdli_PID0107                      (0x0107)
#define rdli_PID0108                      (0x0108)
#define rdli_PID0109                      (0x0109)
#define rdli_PID010A                      (0x010A)
#define rdli_PID010B                      (0x010B)
#define rdli_PID010C                      (0x010C)
#define rdli_PID010D                      (0x010D)
#define rdli_PID010E                      (0x010E)
#define rdli_PID0110                      (0x0110)
#define rdli_PID0111                      (0x0111)
#define rdli_PID0120                      (0x0120)
#define rdli_PID0125                      (0x0125)
#define rdli_PID0129                      (0x0129)
#define rdli_PID012C                      (0x012C)
#define rdli_PID012D                      (0x012D)
#define rdli_PID012F                      (0x012F)
#define rdli_PID0131                      (0x0131)
#define rdli_PID0132                      (0x0132)
#define rdli_PID0136                      (0x0136)
#define rdli_PID013A                      (0x013A)
#define rdli_PID013B                      (0x013B)
#define rdli_PID013C                      (0x013C)
#define rdli_PID013D                      (0x013D)
#define rdli_PID013F                      (0x013F)
#define rdli_PID0140                      (0x0140)
#define rdli_PID0141                      (0x0141)
#define rdli_PID0145                      (0x0145)
#define rdli_PID0147                      (0x0147)
#define rdli_PID0152                      (0x0152)
#define rdli_PID0154                      (0x0154)
#define rdli_PID0156                      (0x0156)
#define rdli_PID0157                      (0x0157)
#define rdli_PID0158                      (0x0158)
#define rdli_PID015B                      (0x015B)
#define rdli_PID015C                      (0x015C)
#define rdli_PID0162                      (0x0162)
#define rdli_PID0163                      (0x0163)
#define rdli_PID0164                      (0x0164)
#define rdli_PID0166                      (0x0166)
#define rdli_PID016D                      (0x016D)
#define rdli_PID016E                      (0x016E)
#define rdli_PID0170                      (0x0170)
#define rdli_PID0171                      (0x0171)
#define rdli_PID0172                      (0x0172)
#define rdli_PID0173                      (0x0173)
#define rdli_PID017C                      (0x017C)
#define rdli_PID017D                      (0x017D)
#define rdli_PID017F                      (0x017F)
#define rdli_PID0180                      (0x0180)
#define rdli_PID0181                      (0x0181)
#define rdli_PID0182                      (0x0182)
#define rdli_PID0183                      (0x0183)
#define rdli_PID0189                      (0x0189)
#define rdli_PID0194                      (0x0194)
#define rdli_PID01A0                      (0x01A0)
#define rdli_PID01A1                      (0x01A1)
#define rdli_PID01A2                      (0x01A2)
#define rdli_PID01A3                      (0x01A3)
#define rdli_PID01A7                      (0x01A7)
#define rdli_PID01A8                      (0x01A8)
#define rdli_PID01A9                      (0x01A9)
#define rdli_PID01AA                      (0x01AA)
#define rdli_PID01AB                      (0x01AB)
#define rdli_PID01AC                      (0x01AC)
#define rdli_PID01AD                      (0x01AD)
#define rdli_PID01AE                      (0x01AE)
#define rdli_PID01B0                      (0x01B0)
#define rdli_PID01B1                      (0x01B1)
#define rdli_PID01B2                      (0x01B2)
#define rdli_PID01B3                      (0x01B3)
#define rdli_PID01B4                      (0x01B4)
#define rdli_PID01B5                      (0x01B5)
#define rdli_PID01B6                      (0x01B6)
#define rdli_PID01B7                      (0x01B7)
#define rdli_PID01B8                      (0x01B8)
#define rdli_PID01B9                      (0x01B9)
#define rdli_PID01BA                      (0x01BA)
#define rdli_PID01BB                      (0x01BB)
#define rdli_PID01BC                      (0x01BC)
#define rdli_PID01BD                      (0x01BD)
#define rdli_PIDF120                      (0xF120)
#define rdli_PIDF121                      (0xF121)
#define rdli_PIDF122                      (0xF122)
#define rdli_PIDF123                      (0xF123)
#define rdli_PIDF124                      (0xF124)
#define rdli_PIDF125                      (0xF125)
#define rdli_PIDF126                      (0xF126)




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
	uint16_t ParamID;
	uint8_t msglength;
	uint8_t Idx ;
	uint8_t *LpKW2000_DelphiBaseModelPN_Ptr;

	if(GetLnServiceDataLength () != 3) {
		/* Request should be atleast 3 bytes long */
		SendLnStandardNegativeAnswer (IncorrectMessageLength);
	} else  {
		/* Prepare response */
		msglength = 1;
		ParamID = (uint16_t) (((GetLnServiceData ())[1]<<8) +(GetLnServiceData ())[2]);

		switch(ParamID) {

        case rdli_PID0100:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TqiMx), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TqiMx), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID0101:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TqiDsr), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TqiDsr), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
			
		case rdli_PID0102:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TqiAct), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TqiAct), msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;

		case rdli_PID0103:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Tm, msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
			
        case rdli_PID0104:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(N), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(N), msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;

		case rdli_PID0105:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(tStaEndL), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(tStaEndL), msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;

		case rdli_PID0108:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(Vsp), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Vsp), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID0109:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(Pam), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Pam), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID010A:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Ub_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID010B:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TpPos), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TpPos), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID010D:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Ta, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID010E:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Tam, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID0110:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(PedPos), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(PedPos), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID0111:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(FlVofLS), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FlVofLS), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID0120:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Maf_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID0125:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Ld_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID0129:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TqActRespEtsm, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID012C:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TpPosDsr_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;

		case rdli_PID012D:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TcatInPre_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
		
		case rdli_PID012F:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TmLin, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
				
		case rdli_PID0131:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TqActEtsm, msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
							
		case rdli_PID0132:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Gr, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
										
		case rdli_PID0136:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( IgaOut, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
													
		case rdli_PID013A:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TpPos1), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TpPos1), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																
		case rdli_PID013B:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TpPos2), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TpPos2), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																			
		case rdli_PID013C:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(dpcpids), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dpcpids), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
										
		case rdli_PID013D:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TpPosNlp_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																						
		case rdli_PID013F:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uTpNlp1), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTpNlp1), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
													
		case rdli_PID0140:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( uTp1Lw_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																
		case rdli_PID0141:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Acl_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																									
		case rdli_PID0145:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(Pim), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Pim), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																			
		case rdli_PID0147:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TaLin, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																											
		case rdli_PID0152:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(AngVlvInOp1), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(AngVlvInOp1), msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
																												
		case rdli_PID0154:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(AngDsrVlvOpIn), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(AngDsrVlvOpIn), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																															
		case rdli_PID0156:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(ToileKel), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(ToileKel), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																		
		case rdli_PID0157:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(fLc), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fLc), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																					
		case rdli_PID0158:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(fLcAd), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fLcAd), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																								
		case rdli_PID015B:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uTp1), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTp1), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																											
		case rdli_PID015C:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uTp2), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uTp2), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																														
		case rdli_PID0162:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uPed1), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uPed1), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																	
		case rdli_PID0163:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uPed2), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uPed2), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																				
		case rdli_PID0164:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uPed2Dble), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uPed2Dble), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																							
		case rdli_PID0166:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TexBfPreCat), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TexBfPreCat), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																							
		case rdli_PID016D:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(Hi16Of32(Ti)), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Hi16Of32(Ti)), msglength++);
			WrtDCAN_ServiceData( Hi8Of16(Lo16Of32(Ti)), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Lo16Of32(Ti)), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																			
		case rdli_PID016E:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Nstat, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																			
		case rdli_PID0170:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( dIgaKnc[0], msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																			
		case rdli_PID0171:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( dIgaKnc[1], msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																						
		case rdli_PID0172:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( dIgaKnc[2], msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																						
		case rdli_PID0173:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( dIgaKnc[3], msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																								
		case rdli_PID017C:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( TmSta, msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
																																																										
		case rdli_PID017D:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(MafPcv), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(MafPcv), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																													
		case rdli_PID017F:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(FtCntEmis), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmis), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																
		case rdli_PID0180:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl_[0]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl_[0]), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																			
		case rdli_PID0181:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl_[1]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl_[1]), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																			
		case rdli_PID0182:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl_[2]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl_[2]), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																			
		case rdli_PID0183:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(FtCntEmisCyl_[3]), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FtCntEmisCyl_[3]), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																			
		case rdli_PID0189:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(dTqIdcPD), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dTqIdcPD), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																						
		case rdli_PID0194:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(dTqLosAd), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dTqLosAd), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																								
		case rdli_PID01A0:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uLsbAdc), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uLsbAdc), msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
																																																																											
		case rdli_PID01A1:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uLsaAdc), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uLsaAdc), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																													
		case rdli_PID01A2:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(uPmap), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(uPmap), msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
																																																																																
		case rdli_PID01A3:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(Pmap), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(Pmap), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																											
		case rdli_PID01A7:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( B_Vis, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																			
		case rdli_PID01A8:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(DuCyPgOut), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(DuCyPgOut), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																														
		case rdli_PID01A9:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( B_Pmp, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																	
		case rdli_PID01AA:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( B_Fan1, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																	
		case rdli_PID01AB:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( B_Fan2, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																						
		case rdli_PID01AC:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(TpPosDpc), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(TpPosDpc), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																									
		case rdli_PID01AD:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(DyCyPsIn), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(DyCyPsIn), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																												
		case rdli_PID01AE:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(DyCyPsOut), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(DyCyPsOut), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																															
		case rdli_PID01B0:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(AngCamOvlapAdj), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(AngCamOvlapAdj), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																				
		case rdli_PID01B1:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( fctCamOvlapIn_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																							
		case rdli_PID01B2:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( fctCamOvlapOut_b, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																																		
		case rdli_PID01B3:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(RounFon), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(RounFon), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																																					
		case rdli_PID01B4:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(fAlt), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(fAlt), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																																								
		case rdli_PID01B5:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(dN), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(dN), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																																										
		case rdli_PID01B6:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( Hi8Of16(FlPg), msglength++);
			WrtDCAN_ServiceData( Lo8Of16(FlPg), msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
																																																																																																													
		case rdli_PID01B7:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( StcEtcAdpt, msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
			
		case rdli_PID01B8:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( ScSpr, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
						
		case rdli_PID01B9:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( ScAntiIce, msglength++);
			SendLnStandardPositiveAnswer( msglength );	
			break;
			
		case rdli_PID01BA:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( ScLrn, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
						
		case rdli_PID01BB:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( B_LrnSuc, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
									
		case rdli_PID01BC:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( FrBitsEtsm, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
												
		case rdli_PID01BD:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
            WrtDCAN_ServiceData( B_FofEtsm, msglength++);
			SendLnStandardPositiveAnswer( msglength );
			break;
															
		case rdli_PIDF120:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);

			for(Idx = 0; Idx < SCN_ECUID_SWVERNUM_LENGHT; Idx++)
				
                WrtDCAN_ServiceData( scnEcuId.SwVerNum[Idx], msglength++);
			
			SendLnStandardPositiveAnswer( msglength );
			break;
																		
		case rdli_PIDF121:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);
			
			for(Idx = 0; Idx < SCN_ECUID_HWVERNUM_LENGHT; Idx++)

			    WrtDCAN_ServiceData( scnEcuId.HwVerNum[Idx], msglength++);
			
			SendLnStandardPositiveAnswer( msglength );
			break;
																					
		case rdli_PIDF122:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);

			for(Idx = 0; Idx < SCN_ECUID_MDLSERNUM_LENGHT; Idx++)

			   WrtDCAN_ServiceData( scnEcuId.MdlSerNum[Idx], msglength++);
			
			SendLnStandardPositiveAnswer( msglength );
			break;
																								
		case rdli_PIDF123:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);

			for(Idx = 0; Idx < SCN_ECUID_PRGINF_LENGHT; Idx++)

			   WrtDCAN_ServiceData( scnEcuId.PrgInf_Original[Idx], msglength++);
			
			SendLnStandardPositiveAnswer( msglength );
			break;
																											
		case rdli_PIDF124:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);

			for(Idx = 0; Idx < SCN_ECUID_PRGINF_LENGHT; Idx++)

			   WrtDCAN_ServiceData( scnEcuId.PrgInf_No1[Idx], msglength++);
			
			SendLnStandardPositiveAnswer( msglength );
			break;
																														
		case rdli_PIDF125:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);

			for(Idx = 0; Idx < SCN_ECUID_PRGINF_LENGHT; Idx++)

			   WrtDCAN_ServiceData( scnEcuId.PrgInf_No2[Idx], msglength++);
			
			SendLnStandardPositiveAnswer( msglength );
			break;
																														
		case rdli_PIDF126:
			
			WrtDCAN_ServiceData(Hi8Of16(ParamID), msglength++);
			WrtDCAN_ServiceData(Lo8Of16(ParamID), msglength++);

			for(Idx = 0; Idx < SCN_ECUID_PRGINF_LENGHT; Idx++)

			   WrtDCAN_ServiceData( scnEcuId.PrgInf_No3[Idx], msglength++);
			
			SendLnStandardPositiveAnswer( msglength );
			break;
			
		default :
			SendLnStandardNegativeAnswer( RequestOutOfRange ) ;
			break ;
		}
	}
} /*** End of LnReadDataByCommonIdentifier ***/

#endif




