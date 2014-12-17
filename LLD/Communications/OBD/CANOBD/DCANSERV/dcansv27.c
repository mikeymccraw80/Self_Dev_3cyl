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
* Filename     : dcansv27.c                                            *
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
* 2     03-07-12  cjqq    Add GetLnServiceDataLength  condition        *
* 3     04-09-12  cjqq    Update the CANOBD per customer requirement   *
* 4     07-31-12  azh     Add Kostal PEPS IMMO interface               *
* 4     09-10-12  cjqq    Updated NRC=24 when request sequence error   *
* 6     10-17-12  xll     set limit for LnReceivedSeed                 *
* 7     02-05-13  azh     Remove length check in LnSecurityAccess      *
* 9     07-25-13  xll     SCR#1169 New CAN requirement from JAC        *
*                         GDI application                              *
* 10    11-21-13  xll     SCR1309 Modified SequenceNumberoffset to 16  *
* 11    14-01-24  XLL     SCR1428 fix issue that NRC is wrong when send*
*                         message's length is smaller than 2.          *
* 13    14-04-03  tz9dw1  RSM8282 Modified dcansv22 for implementing   *
*                         TTE CAN IMMO into MT62p1                     *
* 17    14-07-01  xll     SCR1581 Added compile option COMPILE_SID27_GWM_CHK011 *
*                         and COMPILE_SID27_JAC_SII
***********************************************************************/
#include "dcansv27.h"
#if (XeDCAN_SID_27_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "obdsfapp.h" /* For IMMO configuration */
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlfsrv.h"/*IsDevelopmentOrManfModeActive()*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcanserv.h"
#include "obdlcald.h" /*KeDCANCORE_Security_Algorithm*/
#include "dcancomm.h"
// #include "obdspcfg.h"
#include "kw2app.h"
#include "kw2api.h"
#include "kw2srv10m.h"
#include "dcantran.h"

/***********************************************************************
* Functions in this file:                                              *
************************************************************************
* void KwJ14230StartDiagnosticSession( void );                         *
* void KwJ14230ExecuteService10NextResponse( void );                   *
***********************************************************************/
   
#define SequenceNumData_Size (4)
#define SequenceNumberoffset (16)

static uint32_t  LnReceivedSeed;
static uint32_t  LnReceivedKey;
BYTE KW2SequenceNumData [SequenceNumData_Size];

/**********************************************************************/
/*** LnDiag service: SecurityAccess    (SID27)                             ***/
/**********************************************************************/
void LnSecurityAccess (void)
{
	uint8_t   SecurityAccessSubFunction;
	uint16_t  ReceivedKey;
	uint8_t   meslegth;
	uint8_t   DataLength_ReqSeed;
	uint8_t   DataLength_ReqKey;
	bool      PostiveResponse;
	uint8_t   num_rounds;

	PostiveResponse = false;
	SecurityAccessSubFunction = (GetLnServiceData())[1];
	meslegth = 2;
	num_rounds = 2;

	switch( KeDCANOBD_Security_Algorithm ){
	case CeDelphi_Generic_Static:
		DataLength_ReqKey = SID27_MSG02_LENGTH;
		break;
	case CePML_2Sd4Key:
	case CePML_4Sd4Key:
		DataLength_ReqKey = SID27_MSG02_DelphiGeneric_4KyLENGTH;
		break;
	default:
		DataLength_ReqKey = 0;
		break;
	}

	if(GetLnServiceDataLength() < 2) {
		SendLnStandardNegativeAnswer (IncorrectMessageLength);
	} else {
		if((SecurityAccessSubFunction == SubFuncRequestSeed)||
		   (SecurityAccessSubFunction == SubFuncRequestSeed_Ext)) {
			if (GetLnServiceDataLength() != SID27_MSG01_LENGTH) {
				SendLnStandardNegativeAnswer (IncorrectMessageLength);
			} else {
				if (CheckProgrammingState() || GetLnVulnerabilityState()) {
					switch( KeDCANOBD_Security_Algorithm ) {
					case CeDelphi_Generic_Static:
						WrtDCAN_ServiceData(0x00, meslegth++);
						WrtDCAN_ServiceData(0x00, meslegth++);
						break;
					case CePML_2Sd4Key:
						WrtDCAN_ServiceData(0x00, meslegth++);
						WrtDCAN_ServiceData(0x00, meslegth++);
						break; 
					case CePML_4Sd4Key:
						WrtDCAN_ServiceData(0x00, meslegth++);
						WrtDCAN_ServiceData(0x00, meslegth++);
						WrtDCAN_ServiceData(0x00, meslegth++);
						WrtDCAN_ServiceData(0x00, meslegth++);
						break;
					default:
						break;
					}
					UnlockSecurityAccess_DCAN ();
					SendLnStandardPositiveAnswer (meslegth);
				} else {
					if (LnDiagSecurityDelayTimer) {
						SendLnStandardNegativeAnswer (RequiredTimeDelayNotExpired);
					} else {
						SPS_Security_Key_Allowed = CbTRUE; 
						switch( KeDCANOBD_Security_Algorithm ) {
						case CeDelphi_Generic_Static:
							WrtDCAN_ServiceData(((uint8_t) (Get_Security_Seed_Data() >> 8)), meslegth++);
							WrtDCAN_ServiceData(((uint8_t) Get_Security_Seed_Data()), meslegth++);
							break;
						case CePML_2Sd4Key:
							WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 8)), meslegth++);
							WrtDCAN_ServiceData(((uint8_t) GetOBD_4ByteSeed()), meslegth++); 
							break;
						case CePML_4Sd4Key:
							WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 24)), meslegth++);
							WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 16)), meslegth++);
							WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 8)), meslegth++);
							WrtDCAN_ServiceData(((uint8_t) GetOBD_4ByteSeed()), meslegth++); 
							break;
						default:
							break;
						}
						SendLnStandardPositiveAnswer (meslegth);
					}
				}
			}
		} else if((SubFuncSendKey == SecurityAccessSubFunction)||
		          (SubFuncSendKey_Ext == SecurityAccessSubFunction)) {
			if (LnDiagSecurityDelayTimer) {
				SendLnStandardNegativeAnswer (RequiredTimeDelayNotExpired);
			} else {
				if (LnServiceDataFrame.DataLength != DataLength_ReqKey) {
					SendLnStandardNegativeAnswer (IncorrectMessageLength);
				} else {
					if (SPS_Security_Key_Allowed) {
						SPS_Security_Key_Allowed = CbFALSE;
						switch( KeDCANOBD_Security_Algorithm ) {
						case CeDelphi_Generic_Static:
							ReceivedKey = ((GetLnServiceData ()) [2] << 8) + (GetLnServiceData ()) [3];
							if((ReceivedKey == Get_Key())) {
								PostiveResponse = true;
							} else {
								PostiveResponse = false;
							}
							break;
						case CePML_2Sd4Key:
						case CePML_4Sd4Key:
							LnReceivedKey =  ((GetLnServiceData ()) [2] <<24) 
											+ ((GetLnServiceData ()) [3] <<16) 
											+ ((GetLnServiceData ()) [4] << 8) 
											+ (GetLnServiceData ()) [5];
							if((LnReceivedKey == GetOBD_4ByteKey())) {
								PostiveResponse = true;
							}  else {
								PostiveResponse = false; 
							}
							break;
						default:
							break;
						}
						if (true == PostiveResponse) {
							UnlockSecurityAccess_DCAN ();
							LnDgSecAccessSpsBadKeyCounter = 0;
							SendLnStandardPositiveAnswer (2);
						} else {
							LnDgSecAccessSpsBadKeyCounter ++;
							if (LnDgSecAccessSpsBadKeyCounter == 2) {
								SendLnStandardNegativeAnswer (ExceedNumberOfAttempts);
								TriggerSecurityAccessTiming ();
							} else {
								SendLnStandardNegativeAnswer (InvalidKey);
							}
						}
					} else {
						SendLnStandardNegativeAnswer (RequestSequenceError);
					}
				}
			}
		} else {
			if(GetLnServReqMsgAddressingMode () == FunctionalAddressing) {
				PfrmDCAN_AckReqWithoutResponse ();
			} else {
				SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
			}
		}
	}
} /*** End of LnSecurityAccess ***/

#endif


