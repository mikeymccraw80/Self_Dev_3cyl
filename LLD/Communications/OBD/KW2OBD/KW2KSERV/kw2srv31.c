/* ============================================================================ *\
 * kw2srv31.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv31.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:45 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $31 - Start routine by local ID
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
#include "kw2cfg.h"
#include "kw2srv1a.h"
#include "hal_eng.h"
#include "id.h"
#include "hls.h"
#include "hal_gpio.h"
#include "id_cald.h"
#include "hal_gpio.h"
#include "immo_cal.h"

#define CyKW2K_NVM_Reset_MsgSize            2
#define MODE_1A_MSG_LENGTH                  2
#define CyLocalId                           1
#define CyKW2K_Mode31Msg_Offset            (2)
#define CyKW2K_JumpToBootMsgSize           (2)
#define KHI_ACTUATOR_TEST_MsgSize           3
#define CyKHIActuatorTestLocalId            2
#define SyFuelCalDataLength                 3
#define SyFuelCalHighBytePosition           1
#define SyFuelCalLowBytePosition            2

#define srliActivateSecurityAccess         (0x08)
#define srliCheckFlashEnvironment          (0x09)
#define srliDeactivateSecurityAccess       (0xFE)
#define CyKW2K_NVM_Reset                   (0xAA)
#define CyKW2K_CopyKernelToRAM             (0xFD)
#define KHI_ACTUATOR_TEST                  (0x81)
#define srliFuelCalHighByte                (0x7F)
#define srliFuelCalLowByte                 (0x00)

/* khi actuator test id */
#define KHI_SUPPORT_FLAG_C0                 (0xC0)
#define KHI_SUPPORT_FLAG_E0                 (0xE0)
#define KHI_INJ0_Request                    (0xCC)
#define KHI_INJ1_Request                    (0xCD)
#define KHI_INJ2_Request                    (0xCE)
#define KHI_INJ3_Request                    (0xCF)
#define KHI_FuelPump_Request                (0xD4)
#define KHI_MIL_Request                     (0xD5)
#define KHI_SVS_Request                     (0xD6)
#define KHI_Fan1_Request                    (0xE5)
#define KHI_Fan2_Request                    (0xE6)
#define KHI_CpgV_Request                    (0xE8)

extern TbBOOLEAN     SaINJD_CktTestFailed[4];
extern TbBOOLEAN     SbEMSD_FPRDShortHiTestFailed;
extern TbBOOLEAN     SbEMSD_FPRDShortLoTestFailed;
/******************************************************************************
 *  Global NVM Definitions
 *****************************************************************************/
// #pragma section [nvram]
bool   NbFILE_NVM_Reset_RequestFromSerial;
// #pragma section []

uint8_t khi_last_test;
bool    KW31_EndofLine_FuelAdjustMode;

uint16_t    KW_EOL_CounterFreeRunning0;
uint16_t    KW_EOL_CounterFreeRunning1;
uint16_t    KW_EOL_CounterFreeRunning2;

uint8_t     KW_EOL_initialization;

bool Pb_FuelInjAdjust;
//bool Pb_FuelPumpAdjust;
bool Pb_FuelInjAdjust_stop;
bool Pb_FuelPumpAdjust_stop;
bool Pb_FuelPumpPreWork;
bool Pb_EOL_Fueladjust;

void KwJ14230StartRoutineByLocalIdentifier( void )
{
	uint8_t local_id;
	uint8_t new_flag;
	uint8_t TrBytes;
	uint8_t khi_local_id;
	bool    result;

	/*check the data length */
	if ( GetKeyword2000ServiceDataLength() < 2) {
		SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
	}

	switch (GetKw2000ServiceData(CyLocalId)) {
	case CyKW2K_NVM_Reset :
		if (Get_EngineTurning()) {
			SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
		} else {
			/* write local id to response data frame */
			WrtKw2000ServiceData(GetKw2000ServiceData (CyLocalId), 1 );
			if( GetKeyword2000ServiceDataLength() != CyKW2K_NVM_Reset_MsgSize ) {
				/* Invalid Message format */
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
			} else if ( !GetVulnerabilityState() ) {
				SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
			} else {
				NbFILE_NVM_Reset_RequestFromSerial = true;
				SendStandardPositiveAnswer( CyKW2K_Mode31Msg_Offset );
			}
		}
		break;

	case CyKW2K_CopyKernelToRAM :
		if (Get_EngineTurning()) {
			SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
		} else {
			/* write local id to response data frame */
			WrtKw2000ServiceData(GetKw2000ServiceData (CyLocalId), 1 );
			if( GetKeyword2000ServiceDataLength() != CyKW2K_JumpToBootMsgSize ) {
				/* Invalid Message format */
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat  ) ;
			} else if ( !GetVulnerabilityState() ) {
				SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
			} else {   
				SendStandardPositiveAnswer(CyKW2K_Mode31Msg_Offset);
				SetCopyAndExecuteKernelPending(CbTRUE);
			}
		}
		break;

	case srliFuelCalHighByte:
		/*check the data length */
		if ( GetKeyword2000ServiceDataLength() != 3) {
			SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat );
			break;
		}
		if ( GetKw2000ServiceData(SyFuelCalLowBytePosition) != srliFuelCalLowByte) {
			SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat );
			break;
		}

		if (KbCAN_CHERY_Fuel_Adjust_Enable) {
			if (!KW31_EndofLine_FuelAdjustMode) {
				/* check the injector error */
				result = (SaINJD_CktTestFailed[0] || SaINJD_CktTestFailed[1] || \
				           SaINJD_CktTestFailed[2] || SaINJD_CktTestFailed[3]);
				/* check the fuel pump error */
				result = (result || SbEMSD_FPRDShortHiTestFailed || SbEMSD_FPRDShortLoTestFailed);
				/* check the engine turning flag */
				result = (result || GetEngineTurning());

				if ((!result) && (GetVIOS_EngSt() == CeENG_KEYON)) { 
					/*adjust the injector port to GPIO Mode*/
					HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(true);
					/* shut down the GPIO output */
					HAL_GPIO_SET_INJECTION_Enable(false);
					B_EOL_FuelAdjust = true ;
					E_EOL_FuelAdjust = false ;
					KW31_EndofLine_FuelAdjustMode = true;
					TrBytes = 1;
					WrtKw2000ServiceData(0x7F, TrBytes++);
					WrtKw2000ServiceData(0x01, TrBytes++);
					SendStandardPositiveAnswer(TrBytes); 
				} else {
					B_EOL_FuelAdjust = false ;
					E_EOL_FuelAdjust = true ;
					/* shut down the GPIO output */
					HAL_GPIO_SET_INJECTION_Enable(false);
					/*adjust the injector port back to tpu*/
					HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(false);
					SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError2 );
				}
			} else {
				SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError3);
			}
		} else {
			SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
		}
		break;

	case KHI_ACTUATOR_TEST:
		/* write local id to response data frame */
		WrtKw2000ServiceData(GetKw2000ServiceData (CyLocalId), 1 );
		if( GetKeyword2000ServiceDataLength() != KHI_ACTUATOR_TEST_MsgSize ) {
			SendStandardNegativeAnswer(nrcGeneralReject);
		} else {
			TrBytes = 2;
			khi_local_id = GetKw2000ServiceData(CyKHIActuatorTestLocalId);
			switch(khi_local_id) {
			case KHI_INJ0_Request:
				B_Inj0Req = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_INJ1_Request:
				B_Inj1Req = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_INJ2_Request:
				B_Inj2Req = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_INJ3_Request:
				B_Inj3Req = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_FuelPump_Request:
				B_FulPReq = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_MIL_Request:
				B_MILReq = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_SVS_Request:
				B_SVSReq = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_Fan1_Request:
				B_Fan1Req = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_Fan2_Request:
				B_Fan2Req = 1;
				khi_last_test = khi_local_id;
				break;
			case KHI_CpgV_Request:
				B_CpgVReq = 1;
				khi_last_test = khi_local_id;
				break;
			default:
				SendStandardNegativeAnswer(nrcGeneralReject);
				return;
			}
			SendStandardPositiveAnswer(TrBytes);
		}
		break;

	default :
		SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;
		break ;
	}
}

void LLD_Update_FuelCorrect_Model(void)
{
	bool    result;
		/* check the injector error */
	result = (SaINJD_CktTestFailed[0] || SaINJD_CktTestFailed[1] || \
	           SaINJD_CktTestFailed[2] || SaINJD_CktTestFailed[3]);
	/* check the fuel pump error */
	result = (result || SbEMSD_FPRDShortHiTestFailed || SbEMSD_FPRDShortLoTestFailed);
	/* check the engine turning flag */
	result = (result || GetEngineTurning());
	/* check the crank sig sync state */
	result = (result || crank_sig.crank_status.B_crank_sync);

	if (result || (GetVIOS_EngSt() != CeENG_KEYON) || (B_EOL_FuelAdjust == false)) {
		KW31_EndofLine_FuelAdjustMode = false;
		B_EOL_FuelAdjust = false;
		E_EOL_FuelAdjust = true;
		/* shut down the GPIO output */
		HAL_GPIO_SET_INJECTION_Enable(false);
		/*adjust the injector port back to tpu*/
		HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(false);
	} else {

		if(((KW_EOL_initialization == 0) || ( KKPgmId != ProductionProgramId ))
			&& (Pb_EOL_Fueladjust == false)
			&& (Pb_FuelPumpAdjust_stop == false))
		{
			if (K_Immo_FuelPump_channel==CeFuelPumpPin) {
				HAL_GPIO_SET_FPR_Enable(true);
			} else {
				HAL_GPIO_SET_ACClutch_Enable(true);
			}

			KW_EOL_initialization = 0xAA;
			Pb_FuelPumpPreWork = true;
			Pb_EOL_Fueladjust = true;
		}
		if( Pb_FuelPumpPreWork == true ) {
			KW_EOL_CounterFreeRunning0++;
		}
		if(KW_EOL_CounterFreeRunning0 >= K_VAL_tFuelPumpPreWork) {
			Pb_FuelInjAdjust = true;
			Pb_FuelPumpPreWork = false;
			KW_EOL_CounterFreeRunning0 = 0;
		}
		if(Pb_FuelInjAdjust == true) {
			if(Pb_FuelInjAdjust_stop == false) {
				KW_EOL_CounterFreeRunning1++;
				/* open the GPIO output */
				HAL_GPIO_SET_INJECTION_Enable(true);
			}
			if(Pb_FuelPumpAdjust_stop == false) {
				KW_EOL_CounterFreeRunning2++;
			}
			if(KW_EOL_CounterFreeRunning1 == K_VAL_tFuelInjAdjust) {
				/* shut down the GPIO output */
				HAL_GPIO_SET_INJECTION_Enable(false);
				Pb_FuelInjAdjust_stop = true;
				KW_EOL_CounterFreeRunning1 = 0;
			}
			if(KW_EOL_CounterFreeRunning2 == K_VAL_tFuelPumpAdjust) {
				if (K_Immo_FuelPump_channel==CeFuelPumpPin) {
					HAL_GPIO_SET_FPR_Enable(false);
				} else {
					HAL_GPIO_SET_ACClutch_Enable(false);
				}
				Pb_FuelPumpAdjust_stop = true;
				KW_EOL_CounterFreeRunning2 = 0;
			}
			if(Pb_FuelInjAdjust_stop && Pb_FuelPumpAdjust_stop) {
				Pb_FuelInjAdjust = false;
			}
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
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - Changed to support generic immo
 *
 * 29/01/07     LShoujun    mt20u2#76
 * + Clear nvram area after re-programming with KWP2000
 *   - Added logic for ID of CyKW2K_NVM_Reset
\* ============================================================================ */
