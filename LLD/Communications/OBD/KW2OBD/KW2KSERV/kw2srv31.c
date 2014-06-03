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


#define CyKW2K_NVM_Reset_MsgSize            2
#define MODE_1A_MSG_LENGTH                  2
#define CyLocalId                           1
#define CyKW2K_Mode31Msg_Offset            (2)
#define CyKW2K_JumpToBootMsgSize           (2)
#define KHI_ACTUATOR_TEST_MsgSize           3
#define CyKHIActuatorTestLocalId            2

#define srliActivateSecurityAccess         (0x08)
#define srliCheckFlashEnvironment          (0x09)
#define srliDeactivateSecurityAccess       (0xFE)
#define CyKW2K_NVM_Reset                   (0xAA)
#define CyKW2K_CopyKernelToRAM             (0xFD)
#define KHI_ACTUATOR_TEST                  (0x81)

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


/******************************************************************************
 *  Global NVM Definitions
 *****************************************************************************/
// #pragma section [nvram]
bool   NbFILE_NVM_Reset_RequestFromSerial;
// #pragma section []

uint8_t khi_last_test;

void KwJ14230StartRoutineByLocalIdentifier( void )
{
	uint8_t local_id;
	uint8_t new_flag;
	uint8_t TrBytes;
	uint8_t khi_local_id;

	if (Get_EngineTurning()) {
		SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
	} else {
		/* write local id to response data frame */
		WrtKw2000ServiceData(GetKw2000ServiceData (CyLocalId), 1 );

		switch (GetKw2000ServiceData(CyLocalId)) {
		case CyKW2K_NVM_Reset :
			if( GetKeyword2000ServiceDataLength() != CyKW2K_NVM_Reset_MsgSize ) {
				/* Invalid Message format */
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
			} else if ( !GetVulnerabilityState() ) {
				SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
			} else {
				NbFILE_NVM_Reset_RequestFromSerial = true;
				SendStandardPositiveAnswer( CyKW2K_Mode31Msg_Offset );
			}
			break;

		case CyKW2K_CopyKernelToRAM :
			if( GetKeyword2000ServiceDataLength() != CyKW2K_JumpToBootMsgSize ) {
				/* Invalid Message format */
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat  ) ;
			} else if ( !GetVulnerabilityState() ) {
				SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested ) ;
			} else {   
				SendStandardPositiveAnswer(CyKW2K_Mode31Msg_Offset);
				SetCopyAndExecuteKernelPending(CbTRUE);
			}
			break;

		case KHI_ACTUATOR_TEST:
			if( GetKeyword2000ServiceDataLength() != KHI_ACTUATOR_TEST_MsgSize ) {
				SendStandardNegativeAnswer(nrcGeneralReject);
			} else {
				TrBytes = 2;
				// WrtKw2000ServiceData(GetKw2000ServiceData (CyLocalId), 1 );
				// khi_last_test = GetKw2000ServiceData(CyKHIActuatorTestLocalId);
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
				// case KHI_IGN0_Request:
					// B_Ign0Req = 1;
					// khi_last_test = khi_local_id;
					// break;
				// case KHI_IGN1_Request:
					// B_Ign1Req = 1;
					// khi_last_test = khi_local_id;
					// break;
				// case KHI_IGN2_Request:
					// B_Ign2Req = 1;
					// khi_last_test = khi_local_id;
					// break;
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
				// case KHI_ISC_Request:  //stepper motor self study
					// B_ISCReq = 1;
					// khi_last_test = khi_local_id;
					// break;
				// case KHI_SUPPORT_FLAG_C0:
					// WrtKw2000ServiceData(SupFlagC0[0], TrBytes++);
					// WrtKw2000ServiceData(SupFlagC0[1], TrBytes++);
					// WrtKw2000ServiceData(SupFlagC0[2], TrBytes++);
					// WrtKw2000ServiceData(SupFlagC0[3], TrBytes++);
					// break;
				// case KHI_SUPPORT_FLAG_E0:
					// WrtKw2000ServiceData(SupFlagE0[0], TrBytes++);
					// WrtKw2000ServiceData(SupFlagE0[1], TrBytes++);
					// WrtKw2000ServiceData(SupFlagE0[2], TrBytes++);
					// WrtKw2000ServiceData(SupFlagE0[3], TrBytes++);
					// break;
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
