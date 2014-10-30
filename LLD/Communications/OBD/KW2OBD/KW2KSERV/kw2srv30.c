/* ============================================================================ *\
 * kw2srv30.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv30.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:34 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $30 - Input/output control by local identifier
 *   
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "kw2srv30.h"
#include "kw2dll.h"
#include "kw2app.h"
#include "kw2cfg.h"
#include "kw2srv10m.h"
#include "kw2srv30.h"
#include "hal_eeprom_mfg.h"
#include "immo_exec.h"
#include "immo.h"

/*for Siemens immo*/
#include "kw2srv27.h"
#include "siemens_immossrv.h"
/*****************************************************************************
 *  Local Define
 *****************************************************************************/

/* define the offsets within tx buffer for bytes we want to stuff */
#define CyOFVC_KW_MODE	  0
#define CyOFVC_KW_DATA1   1
#define CyOFVC_KW_DATA2   2
#define CyOFVC_KW_DATA3   3
#define CyOFVC_KW_DATA4   4

#define CyOFVC_SUCCESSFUL             0x00
#define CyOFVC_VentVacuumTooHigh      0x01
#define CyOFVC_AC_PressureNotInRange  0x03
#define CyOFVC_EngSpdTooHigh          0x05
#define CyOFVC_VSS_Fault              0x02
#define CyOFVC_VSS_Not_Zero           0x01
#define CyOFVC_RPM_Not_Zero           0x01
#define CyOFVC_InjFlowTestInProgress  0x04
#define CyOFVC_InjTestLimitExceeded   0x02
#define CyOFVC_InjAlreadyTested       0x05
#define CyOFVC_PurgeVacuumTooHi       0x01
#define CyOFVC_SparkRqstOutOfRange    0x01
#define CyOFVC_InvalidInjectorNum     0x03
#define CyOFVC_Eng_RUN_Evap_SerBay    0x03
#define CyOFVC_Transmission_in_Gear     	0x02
#define CyOFVC_AutoTransLoad_NotInPark		0x01
#define CyOFVC_AutoTransLoad_EngineRunning      0x02



#define CySiemens_SKLocalID                   (0x61)
#define CySiemens_SCLocalID                   (0x62)
#define CySiemens_SKAndSCLocalID              (0x63)

#define CySiemens_CntrlECMLrnSKAndSC          (0x0A)
#define CySiemens_CntrlECMRptSK               (0x0C)
#define CySiemens_RstECMToDelivery            (0x0E)

#define ECMlearnImmoMsg_Datalength  (23)
#define ImmoLrnECMandECMRst_Datalength  (5)


#define CyOFVC_MAX_NUM_RESPONSES 20
/*****************************************************************************
 *  Global Data Define
 *****************************************************************************/
TsOFVC_OvrdMessage VsOFVC_OvrdRqstStruct;
bool R_LineEnable;

/*****************************************************************************
 *  Local Define
 *****************************************************************************/

/* standard outgoing message length for transmitted device control response */
#define CyOFVC_DevCntrlStdTXMsgLength 4
#define CyOFVC_RETURN_CTRL_TO_ECU     3
#define nrcSubFunctionNotSupported_OutOfRange       (0x31)

/**************************************************************************/
/*                                                                        */
/* FUNCTION: PerfmBRIL_ECMLearnImmo                               */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: ECM learn SK and SC from Immo for Siemens customer */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
static void PerfmSiemens_ECMLearnImmo( uint8_t IOCtrl )
{
	BYTE LySiemens_Index;
	BYTE LySiemens_SidIdx = 3;
	WORD LwSiemens_Checksum = 0;
	WORD LwSiemens_Checksum_V;
	BYTE LaSiemens_SK[16];
	BYTE LaSiemens_SC[2];
	BYTE *EE_SiemensSK = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecretKey;
	BYTE *EE_PIN = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecurityCode;


	//case (ECMlearnImmoMsg_Datalength):
	/* ECM learns sk and sc from Siemens immo */
	if((IOCtrl == CySiemens_CntrlECMLrnSKAndSC) && (GetKeyword2000ServiceDataLength() == ECMlearnImmoMsg_Datalength))
	{
		if(!Chk_SiemensImmo_Enabled()) {
			SendStandardNegativeAnswer(nrcServiceNotSupported);
		} else if(!CheckIMMO_ECMNotLearned()) {
			SendStandardNegativeAnswer(CySiemens_nrcSystemNotInDeliveryMode);
		} else {
			for (LySiemens_Index = 0; LySiemens_Index < SiemensImmoSecretKeySize; LySiemens_Index++) {
				LaSiemens_SK[LySiemens_Index] = GetKw2000ServiceData(LySiemens_SidIdx++);
				EE_SiemensSK[LySiemens_Index] = LaSiemens_SK[LySiemens_Index];
				LwSiemens_Checksum = LwSiemens_Checksum + LaSiemens_SK[LySiemens_Index];
			}
			for (LySiemens_Index = 0; LySiemens_Index < SecurityAccessLevel2KeySize; LySiemens_Index++) {
				LaSiemens_SC[LySiemens_Index] = GetKw2000ServiceData(LySiemens_SidIdx++);
				EE_PIN[LySiemens_Index] = LaSiemens_SC[LySiemens_Index];
				LwSiemens_Checksum = LwSiemens_Checksum + LaSiemens_SC[LySiemens_Index];
			} 
			LwSiemens_Checksum_V = ( (GetKw2000ServiceData(LySiemens_SidIdx) ) << 8) + GetKw2000ServiceData(LySiemens_SidIdx + 1);
			if(LwSiemens_Checksum == LwSiemens_Checksum_V) {
				// EEPROMWrite(LaSiemens_SK,EE_SiemensSK,SiemensImmoSecretKeySize);
				// EEPROMWrite(LaSiemens_SC,EE_PIN,SecurityAccessLevel2KeySize);
				WrtKw2000ServiceData(GetKw2000ServiceData(1), 1);
				WrtKw2000ServiceData(GetKw2000ServiceData(2), 2);
				SendStandardPositiveAnswer (3);  
				R_LineEnable = true;
				//delay 2.5s after ECM learning is finished.			 
				ECMLearnedDelayTime =V_COUNT_WORD(320);
				ECMResetToDeliveryDlayTime=V_COUNT_WORD(320);
				ECMLearnedDelayTime_En = true;
				ECMResetToDeliveryDlayTime_En = false;
			} else {
				SendStandardNegativeAnswer(CySiemens_nrcDownloadNotAccepted);
			}
		}
	} else {
		SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	}
}

/**************************************************************************/
/*                                                                        */
/* FUNCTION: PerfmSiemens_ImmoLearnECM                               */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: Immo learn SK from ECM for Siemens customer */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
static void PerfmSiemens_ImmoLearnECM( uint8_t IOCtrl )
{
	BYTE LySiemens_Index;
	BYTE LySiemens_SidIdx = 3;
	WORD LwSiemens_Checksum = 0;
	WORD LwSiemens_Checksum_V;
	BYTE *EE_SiemensSK = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecretKey;
	BYTE *EE_PIN = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecurityCode;

	/* Immo learns sk and sc from Siemens ECM */
	if( (IOCtrl == CySiemens_CntrlECMRptSK) && (GetKeyword2000ServiceDataLength() == ImmoLrnECMandECMRst_Datalength) ) {
		/* ECM reports sk to Siemens immo */
		if (!Chk_SiemensImmo_Enabled() ) {
			SendStandardNegativeAnswer(nrcServiceNotSupported);
		} else if (!CheckIfL2SecurityTimerIsZero())  {
			/* if the timer not expired, send negative response */
			SendStandardNegativeAnswer(nrcRequiredTimeDelayNotExpired);
		} else if(CheckIMMO_ECMNotLearned() ) {
			SendStandardNegativeAnswer(CySiemens_nrcImmoFunctionNotProgrammed);              
		} else {
			if( (GetKw2000ServiceData(3) == EE_PIN[0]) && (GetKw2000ServiceData(4) == EE_PIN[1]) ) {
				UnlockL2SecurityAccess();

				/* Reset Wrong Attempt counter */
				// NyIMMO_L2WrongAttemptTryCntr = 0;
				L2_WrongAttemptTry = 0;
				/**************************************************/

				WrtKw2000ServiceData(GetKw2000ServiceData(1), 1);
				WrtKw2000ServiceData(GetKw2000ServiceData(2), 2);
				for (LySiemens_Index = 0; LySiemens_Index < SiemensImmoSecretKeySize; LySiemens_Index++)
				{
					WrtKw2000ServiceData(EE_SiemensSK[LySiemens_Index], LySiemens_SidIdx++);
					LwSiemens_Checksum = LwSiemens_Checksum + EE_SiemensSK[LySiemens_Index];
				}
				WrtKw2000ServiceData(Hi8Of16(LwSiemens_Checksum), LySiemens_SidIdx++);
				WrtKw2000ServiceData(Lo8Of16(LwSiemens_Checksum), LySiemens_SidIdx++);
				SendStandardPositiveAnswer (LySiemens_SidIdx);               
			} else {
				TriggerL2SecurityTiming();
				SendStandardNegativeAnswer(CySiemens_nrcIncorrectSecurityCode);
			}
		}
	} else {
		SendStandardNegativeAnswer (nrcSubFunctionNotSupported_InvalidFormat);
	} 
}

/**************************************************************************/
/*                                                                        */
/* FUNCTION: PerfmSiemens_ResetECMDelivery                               */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    Kw2000 service IO Ctrl By Local ID: Reset ECM to delivery for Siemens customer */
/*                                                                        */
/* GLOBAL: GetKeyword2000ServiceData                                      */
/**************************************************************************/
static void PerfmSiemens_ResetECMDelivery( uint8_t IOCtrl )
{
	BYTE LySiemens_Index;
	BYTE LySiemens_SidIdx = 3;
	BYTE LaSiemens_SK[16];
	BYTE LaSiemens_SC[2];
	BYTE *EE_SiemensSK = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecretKey;
	BYTE *EE_PIN = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecurityCode;

	/* Immo learns sk and sc from Siemens ECM */
	if( (IOCtrl == CySiemens_RstECMToDelivery) && (GetKeyword2000ServiceDataLength() == ImmoLrnECMandECMRst_Datalength) ) {
		/* Set ECM to its delivery condition */
		if (!Chk_SiemensImmo_Enabled() ) {
			SendStandardNegativeAnswer(nrcServiceNotSupported);
		} else if (!CheckIfL2SecurityTimerIsZero()) {
			/* if the timer not expired, send negative response */
			SendStandardNegativeAnswer(nrcRequiredTimeDelayNotExpired);
		} else if(CheckIMMO_ECMNotLearned() ) {
			SendStandardNegativeAnswer(CySiemens_nrcImmoFunctionNotProgrammed);              
		} else {
			if( (GetKw2000ServiceData(3) == EE_PIN[0]) && (GetKw2000ServiceData(4) == EE_PIN[1]) ) {
				/**************************************************/
				UnlockL2SecurityAccess();
				/* Reset Wrong Attempt counter */
				L2_WrongAttemptTry = 0;
				/**************************************************/

				for (LySiemens_Index = 0; LySiemens_Index < SiemensImmoSecretKeySize; LySiemens_Index++) {
					LaSiemens_SK[LySiemens_Index] = 0;
					EE_SiemensSK[LySiemens_Index] =  LaSiemens_SK[LySiemens_Index] ;
				}
				for (LySiemens_Index = 0; LySiemens_Index < SecurityAccessLevel2KeySize; LySiemens_Index++) {
					EE_PIN[LySiemens_Index] = 0;
					LaSiemens_SC[LySiemens_Index] =LaSiemens_SC[LySiemens_Index];
				}

				WrtKw2000ServiceData(GetKw2000ServiceData(1), 1);
				WrtKw2000ServiceData(GetKw2000ServiceData(2), 2);
				SendStandardPositiveAnswer (3);

				R_LineEnable = true;
				//delay 2.5s after ECM learning is finished.			 
				ECMResetToDeliveryDlayTime =V_COUNT_WORD(320);
				ECMLearnedDelayTime =V_COUNT_WORD(320);
				ECMResetToDeliveryDlayTime_En = true;
				ECMLearnedDelayTime_En = false;
				// ImmoInhibitEngine = true;
			} else {
				TriggerL2SecurityTiming();
				SendStandardNegativeAnswer(CySiemens_nrcIncorrectSecurityCode);
			}
		}
	} else {
		SendStandardNegativeAnswer (nrcSubFunctionNotSupported_InvalidFormat);
	}

}

/*****************************************************************************
 *
 * Function:           KwJ14230InputOutputControlByLocalIdentifierII
 * Description:        Standard Service function for handling KW2000 device control
 *                     request.
 * 
 * Parameters:         None
 * Return:             None
 *****************************************************************************/
void KwJ14230InputOutputControlByLocalIdentifier (void)
{
	uint8_t  io_ctrl ;
	uint8_t  local_id ;
	uint8_t  i;

	local_id = GetKw2000ServiceData(1) ;
	io_ctrl = GetKw2000ServiceData(2) ;

	if ( Ignition_On() ) {
		/*  copy the received message bytes to the reply ..... */
		for ( i = 1; i <= GetKeyword2000ServiceDataLength(); i++ ) {
			WrtKw2000ServiceData( (GetKw2000ServiceData(i)), i );
		}

		switch ( local_id ) {

		case CySiemens_SKAndSCLocalID:
			if ( CheckProgrammingState () ) {
				SendStandardNegativeAnswer ( nrcConditionsNotCorrect_RequestSequenceError ) ;
			} else {
				PerfmSiemens_ECMLearnImmo(io_ctrl);
			}
			break;
		case CySiemens_SKLocalID:
			if ( CheckProgrammingState () ) {
				SendStandardNegativeAnswer ( nrcConditionsNotCorrect_RequestSequenceError ) ;
			} else {
				PerfmSiemens_ImmoLearnECM(io_ctrl);
			}
			break;  
		case CySiemens_SCLocalID:
			if ( CheckProgrammingState () ) {
				SendStandardNegativeAnswer ( nrcConditionsNotCorrect_RequestSequenceError ) ;
			} else {
				if (Chk_SiemensImmo_Enabled()) {
					PerfmSiemens_ResetECMDelivery(io_ctrl);
				}
			}
			break;
		default :
			SendStandardNegativeAnswer (nrcSubFunctionNotSupported_InvalidFormat) ;
		break ;
		}
	} else {
		SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
	}
}


void FormAndSendImmoData (void)
{
	LearnSKandPINService();
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 16/12/08     sjl      -
 * + Baseline - Created from MT22.1.
\* ============================================================================ */

