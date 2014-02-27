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
#include "hal_eng.h"
#include "hls.h"

#define CyLocalId                           1
#define KHI_ACTUATOR_TEST                   (0x81)

/* khi actuator test id */
#define KHI_INJ0_Request                    (0xCC)
#define KHI_INJ1_Request                    (0xCD)
#define KHI_INJ2_Request                    (0xCE)
#define KHI_FuelPump_Request                (0xD4)
#define KHI_IGN0_Request                    (0xD5)
#define KHI_IGN1_Request                    (0xD6)
#define KHI_IGN2_Request                    (0xD7)
#define KHI_Fan1_Request                    (0xE5)
#define KHI_CpgV_Request                    (0xE8)
#define KHI_ISC_Request                     (0xDD)

/* global variable decaire */
extern uint8_t khi_last_test;

void KwJ14230StopRoutineByLocalIdentifier( void )
{
	if (GetEngineTurning() && (GetKw2000ServiceData(CyLocalId) != KHI_ACTUATOR_TEST)) {
		SendStandardNegativeAnswer(nrcGeneralReject) ;
	} else {
		/* write local id to response data frame */
		WrtKw2000ServiceData(GetKw2000ServiceData (CyLocalId), 1 );
		switch(GetKw2000ServiceData(CyLocalId)) {
		case KHI_ACTUATOR_TEST:
			switch(khi_last_test) {
			case KHI_INJ0_Request:
				B_Inj0Stp = 1;
				break;
			case KHI_INJ1_Request:
				B_Inj1Stp = 1;
				break;
			case KHI_INJ2_Request:
				B_Inj2Stp = 1;
				break;
			case KHI_FuelPump_Request:
				B_FulPStp = 1;
				break;
			case KHI_IGN0_Request:
				B_Ign0Stp = 1;
				break;
			case KHI_IGN1_Request:
				B_Ign1Stp = 1;
				break;
			case KHI_IGN2_Request:
				B_Ign2Stp = 1;
				break;
			case KHI_Fan1_Request:
				B_Fan1Stp = 1;
				break;
			case KHI_CpgV_Request:
				B_CpgVStp = 1;
				break;
			case KHI_ISC_Request:  //stepper motor self study
				if (B_ISCReq) {  // don't support this stop command
					SendStandardNegativeAnswer(nrcGeneralReject);
					return;
				}
				break;
			default:
				khi_last_test = 0;
				SendStandardNegativeAnswer(nrcGeneralReject);
				return;
			}
			khi_last_test = 0;
			SendStandardPositiveAnswer(2);
			break;

		default :
			SendStandardNegativeAnswer(nrcGeneralReject);
			break;
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
