/******************************************************************************
 *
 * Filename:         Siemens_immomaut.c
 *
 * Description:       This module contains the authentication services of 
 *                    Siemens Immobilizer 
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    SiemensImmo_Authentication_Service
 *                    SiemensImmo_ACK_Service
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/******************************************************************************
 *  Include Files
 *****************************************************************************/
#include "io_type.h"


/* ========================================================================== *\
 * Other header files.
\* ========================================================================== */

#include "immo.h"
#include "kw2dll.h"
#include "immo_fexi.h"
#include "v_immo.h"
#include "immo_cal.h"
#include "intr_ems.h"
#include "siemens_immosaut.h"
#include "siemens_immosenc.h"
#include "siemens_immossrv.h"
#include "kw2app.h"
#include "t_base.h"
#include "hal_eeprom_nvm.h"
#include "hal_eeprom_mfg.h"

#define CySiemens_ChallengeServiceID                 (0xA0)
#define CySiemens_ChallengeMSGLength                 (0x01)
#define CySiemens_CodeServiceID                      (0xA1)
#define CySiemens_CodeMSGLength                      (0x07)

 

/******************************************************************************
 *  Module function prototypes.
 *****************************************************************************/
static void SiemensImmo_Authentication_Service(void);
static void SiemensImmo_ACK_Service(void);

/*****************************************************************************
*  Variable Declarations
*****************************************************************************/
const KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE CaSiemensServiceDefinition[ ] =
{
  /* IMMO Challenge Service */
  {
    CeSiemens_Authentication,
    SiemensImmo_Authentication_Service
  },
  /* IMMO Code Service */
  {
    CeSiemens_FeedbackAuthentication,
    SiemensImmo_ACK_Service
  },
};

/*
 * This constant defines the sizeof the supported service table
 * length. This size is calculated at compile time and is used
 * by the Update Service routine in file immo_comu.c to search the service
 * table.
 */
const uint8_t  CyKW2SiemensMaxServiceDefTableEntrys  =
     (sizeof( CaSiemensServiceDefinition )/
     sizeof( KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE ));   

TbBOOLEAN VbSiemens_IllegalMsgReceived;
TbBOOLEAN VbSiemens_MsgSeqError;


/******************************************************************************
 * Local Functions
 ******************************************************************************/

/*****************************************************************************
 *
 * Function:           SiemensImmo_Authentication_Service
 * Description:        Handle authorization operation between ECM and immobilizer.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
static void SiemensImmo_Authentication_Service(void) 
{
	uint8_t *EE_SiemensSK = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecretKey;
	/* Put data preparation and authentication together here */

	/* Prepare for 6 bytes challenge */
	SiemensImmo_PrepareAuthenData();  

	/* Based on the three input variables Challenge, Secret Key and Transp_ID, the transponder calculates
	an output variable, i.e. "Response", via a cryptologic algorithm. The Response is received by
	the immobiliser and transferred to the engine control unit. */

	if (CeImmo_STEC == K_Immo_option) {
		CalcSiem_Encrypt( (BYTE*)VaSiemens_RandomNum, (BYTE*)KaIMMO_CustomerID, (uint8_t*)EE_SiemensSK, (BYTE*)VaSiemens_RefResponse);
	} else {
		//some unexpected error happened
	}
	ImmoNoResponseDetected = false;
}


/*****************************************************************************
 *
 * Function:           SiemensImmo_ACK_Service
 * Description:        Handle feedback authorization result operation 
 *                     between ECM and immobilizer.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
static void SiemensImmo_ACK_Service(void)
{
	if(!VbSiemens_ECUPreEnable)
	{
		/* Bypass compare if per-release time expired */
		ClearImmoAuthenticationResult();
		ImmoAuthenErrorDetected = true;
	}
	else if( (GetKw2000ServiceData(1) == VaSiemens_RefResponse[0])
		  && (GetKw2000ServiceData(2) == VaSiemens_RefResponse[1])
		  && (GetKw2000ServiceData(3) == VaSiemens_RefResponse[2])
		  && (GetKw2000ServiceData(4) == VaSiemens_RefResponse[3])
		  && (GetKw2000ServiceData(5) == VaSiemens_RefResponse[4])
		  && (GetKw2000ServiceData(6) == VaSiemens_RefResponse[5]) )
	{
		SetImmoAuthenticationResult(CbTRUE);
		ImmoPassThisKeyon = CbTRUE;
		VeSiemens_ActReason = CeIMMO_NoError;
		ImmoAuthenErrorDetected = false;
	}
	else if( (!VbSiemens_ImmoFuncNotProgrammed) 
		&& ( (GetKw2000ServiceData(1) == 0x00)
		    && (GetKw2000ServiceData(2) == 0x00)
		    && (GetKw2000ServiceData(3) == 0x00)
		    && (GetKw2000ServiceData(4) == 0x00)
		    && (GetKw2000ServiceData(5) == 0x00)
		    && (GetKw2000ServiceData(6) == 0x00) ) )
	{
			/* transponderResponse in the immoCode request message are
			   set to value 00H. this is an information that icu not programmed
			   or wrong transponder fixcode */
		ClearImmoAuthenticationResult();
		VeSiemens_ActReason = CeIMMO_ICUInVirginOrWrgTXP;
		ImmoAuthenErrorDetected = true;
	}
	else
	{
		ClearImmoAuthenticationResult();
		VeSiemens_ActReason = CeIMMO_ICURespNG;
		ImmoAuthenErrorDetected = true;
	}
	ImmoNoResponseDetected = false;
}



/******************************************************************************
 * Global Functions
 ******************************************************************************/

/*****************************************************************************
 *                                                                            *
 * Function:          SiemensImmo_UpdateStateMachine                             *
 * Description:       Update ECM immobilizer state machine                    *
 * Parameters:        none                                                    *
 * Return:            none                                                    *
 *                                                                            *
 *****************************************************************************/
void SiemensImmo_UpdateStateMachine (void)
{
	uint8_t counter;

	VbSiemens_IllegalMsgReceived = CbFALSE;
	VbSiemens_MsgSeqError = CbFALSE;

	/* Msg received. Clear P3Max Overtime Counter */
	VySiemens_P3MaxOvertimeCntr = 0;

	/* Redirect ECM-IMMO relation state machine with received 
	 service ID of immobilizer's challenge 
	 Acceptable cases:
	 Case 1: IMMO repeat its last request: redirect back 
	 Case 2: sequence ok */
	if( (CySiemens_ChallengeMSGLength == GetKeyword2000ServiceDataLength() )
	&& (CySiemens_ChallengeServiceID == GetKw2000ServiceData(0) ) )
	{
		/* IMMO Challenge Received */
		if(CeSiemens_Authentication == VeSiemens_ECMImmoRelation) {
			/* Fine, start immo challenge service */
		} else if(CeSiemens_FeedbackAuthentication == VeSiemens_ECMImmoRelation) {
			/* Received a challenge request again, redirect workflow */
			VeSiemens_ECMImmoRelation = CeSiemens_Authentication;     
		} else {
			/* Request sequence error. Ignore current message and wait for a 
			 new round of challenge. Send negative response. */
			VeSiemens_ECMImmoRelation = CeSiemens_Authentication;
			VbSiemens_MsgSeqError = CbTRUE;
			VeSiemens_ActReason = CeIMMO_ICUReqSeqError;
		}
	} else if( (CySiemens_CodeMSGLength == GetKeyword2000ServiceDataLength() )
			&& (CySiemens_CodeServiceID == GetKw2000ServiceData(0) ) )
	{
		/* IMMO Code Received */
		if(CeSiemens_FeedbackAuthentication == VeSiemens_ECMImmoRelation) {
			/* Fine, start immo code service */
		} else if(CeSiemens_StopCommunication == VeSiemens_ECMImmoRelation) {
			/* Received a code request again, redirect workflow over again */
			VeSiemens_ECMImmoRelation = CeSiemens_FeedbackAuthentication;
		} else {
			/* Request sequence error. Ignore current message and wait for a 
			new round of challenge. Send negative response. */
			VeSiemens_ECMImmoRelation = CeSiemens_Authentication;     
			VbSiemens_MsgSeqError = CbTRUE;
			VeSiemens_ActReason = CeIMMO_ICUReqSeqError;
		}
	} else {
		/* error, received a unknown message. Send negative response */
		VbSiemens_IllegalMsgReceived = CbTRUE;
		VeSiemens_ActReason = CeIMMO_ICUBadMsg;
	}

	/* immo service schedule */
	if( (!VbSiemens_IllegalMsgReceived) && (!VbSiemens_MsgSeqError) ) {
		for (counter=0; counter < CyKW2SiemensMaxServiceDefTableEntrys; counter++) {
			if (CaSiemensServiceDefinition[counter].ServiceID == VeSiemens_ECMImmoRelation) {
				CaSiemensServiceDefinition[counter].Service_Function();
				break;
			}
		}
	}
	SetSiemens_DLLStateToSendingWup();
}




/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
