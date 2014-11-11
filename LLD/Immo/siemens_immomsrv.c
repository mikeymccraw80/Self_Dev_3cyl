/******************************************************************************
 *
 * Filename:          Siemens_immomsrv.c
 *
 * Description:       This module contains the dll functions used by 
 *                    Siemens immobilizer authentication
 *
 * Global Functions Defined:
 *                    SiemensImmo_BldChallengeRspMsgFrame
 *                    SiemensImmo_BldCodeRspMsgFrame
 *                    SiemensImmo_AuthResultLostService
 *                    SiemensImmo_PrepareAuthenData
 *                    SiemensImmo_Initializing
 *                    SiemensImmo_UpdateStateMachine
 *                    SiemensImmo_P3MaxOvertime
 * Static Functions Defined:
 *                    SiemensImmo_CntrlRLineSignal
 *                    SiemensImmo_CntrlPreEnableTime
 *                    SiemensImmo_CntrlIMMOKWTime
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
#include "siemens_immosenc.h"
#include "siemens_immossrv.h"
#include "siemens_immosaut.h"

#include "kw2dll.h"
#include "kw2dllcf.h"
#include "immo_exec.h"
#include "kw2exec.h" 
#include "immo.h"
#include "immo_encrypt.h"
// #include "tecdfexi.h"
#include "immo_fexi.h"
#include "v_immo.h"
#include "immo_cal.h"
#include "intr_ems.h"
#include "kw2srv27.h"
#include "kw2srv30.h"
#include "hal_analog.h"
#include "hal_eng.h"
#include "hal_gpio.h"

#define CySiemens_ChallengeRspLength            (0x07)
#define CySiemens_CodeRspLength                 (0x01)

#define CwSiemens_IMMOKWEnblTimerCnt7p8ms       ( V_COUNT_WORD(512) ) /* 512*7p8125ms = 4s */
#define CySiemens_RLineTimerCnt7p8ms            ( V_COUNT_BYTE(16) )  /* 16*7p8125ms = 125ms */

#define PowerUpDelayTiniTime                 (20)
/*****************************************************************************
 * Volatile RAM Variable Declarations
 *****************************************************************************/
TbBOOLEAN             VbSiemens_ImmoFuncNotProgrammed;
TbBOOLEAN             VbSiemens_ECUPreEnable;
T_COUNT_BYTE          VySiemens_P3MaxOvertimeCntr;
T_COUNT_BYTE          PowerUpDelayTiniCntr;

static TbBOOLEAN      SbSiemens_RLineTriggerEnbl; 
static TbON           SbSiemens_RLineStatus;
static T_COUNT_BYTE   SySiemens_RLineTimerCntr;
static TbBOOLEAN      SbSiemens_IMMOKWEnable;
static T_COUNT_WORD   SwSiemens_IMMOKWEnblTimerCntr;
static T_COUNT_WORD   SwSiemens_PreEnblTimerCntr; 

T_COUNT_WORD ECMLearnedDelayTime; 
T_COUNT_WORD ECMResetToDeliveryDlayTime; 
bool R_LineSignalGenerate;
bool ECMLearnedDelayTime_En;
bool ECMResetToDeliveryDlayTime_En;

/******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/
static void SiemensImmo_CntrlRLineSignal (void);
static void SiemensImmo_CntrlPreEnableTime(void);
static void SiemensImmo_CntrlIMMOKWTime(void);
static void ImmoECMRunningResetCheck(void);
/******************************************************************************
 * Global Function
 ******************************************************************************/

/*****************************************************************************
*                                                                            *
* Function:          SiemensImmo_BldChallengeRspMsgFrame                        *
* Description:       Build Immo challenge response Msg and trigger sending   *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
void SiemensImmo_BldChallengeRspMsgFrame (void)
{
	BYTE SidIdx = 1;
	BYTE LyIndex;

	/* P2 Timer - already one loop passed since immo request received */

	P2MinTimer++;
	if(VbSiemens_ImmoFuncNotProgrammed) {
		SendStandardNegativeAnswer(CySiemens_nrcImmoFunctionNotProgrammed);
	} else if (VbSiemens_IllegalMsgReceived) {
		SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	} else if(VbSiemens_MsgSeqError) {
		SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
	} else {
		/* data->Tx.Data[0] is set as data->Rx.Data[0] + PositiveResponseOffset in SendStandardPositiveAnswer */ 
		/* challenge response: 6 bytes random number */
		for (LyIndex = 0; LyIndex < (CySiemens_ChallengeRspLength - 1); LyIndex++) {
			WrtKw2000ServiceData ( VaSiemens_RandomNum[LyIndex], SidIdx++);
		}

		/* standard KW handler, wait P2min before send */
		SendStandardPositiveAnswer(SidIdx);
	}
}

/*****************************************************************************
*                                                                            *
* Function:          SiemensImmo_BldCodeRspMsgFrame                             *
* Description:       Build Immo code response Msg and trigger sending        *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
void SiemensImmo_BldCodeRspMsgFrame (void)
{
	/* P2 Timer - already one loop passed since immo request received */
	// P2Min++;
	P2MinTimer++;
	if(!VbSiemens_ECUPreEnable) {
		SendStandardNegativeAnswer(CySiemens_nrcPreReleaseTimeExpired);    
	} else if(VbSiemens_ImmoFuncNotProgrammed) {
		SendStandardNegativeAnswer(CySiemens_nrcImmoFunctionNotProgrammed);
	} else if(VbSiemens_IllegalMsgReceived) {
		SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
	} else if(VbSiemens_MsgSeqError) {
		SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
	} else {
		/* IMMO Code Response. */
		if (ImmoAuthenticationResultPass()) {
			SendStandardPositiveAnswer(CySiemens_CodeRspLength);
		} else {
			SendStandardNegativeAnswer(CySiemens_nrcTranspResponseIncorrect);
		}
	}
}


/*****************************************************************************
 *
 * Function:           SiemensImmo_AuthResultLostService
 * Description:        Authentication Result will be lost during ING OFF.  
 *                     ECM will re-authoriztion after Authentication Result Lost.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void SiemensImmo_AuthResultLostService(void) 
{
	ImmoEngineStallCheck();
	ImmoIGNOffCheck();
	ImmoECMRunningResetCheck();
	if(R_LineEnable&&((!ECMLearnedDelayTime)||(!ECMResetToDeliveryDlayTime))) {
		R_LineSignalGenerate = true;
		R_LineEnable = false;
	} else {
		R_LineSignalGenerate = false;
		if (ECMLearnedDelayTime_En) {
			if(ECMLearnedDelayTime==0) {
				ECMLearnedDelayTime_En=false;
			} else {
				ECMLearnedDelayTime--;
			}
			ECMResetToDeliveryDlayTime=V_COUNT_WORD(320);
			ECMResetToDeliveryDlayTime_En = false;
		} else if(ECMResetToDeliveryDlayTime_En) {
			if(ECMResetToDeliveryDlayTime==0) {
				ECMResetToDeliveryDlayTime_En=false;
			} else {
				ECMResetToDeliveryDlayTime--;
			}
			ECMLearnedDelayTime = V_COUNT_WORD(320);
			ECMLearnedDelayTime_En = false;
		}
	}

	if (GetVIOS_VehInMfgPlant() )
	{
		/* Bypass authentication if in plant mode */
		ImmoEnableEngine();
		ValidateAuthenticationResult();
		SetImmoAuthenticationResult(CbTRUE);
		ImmoPassThisKeyon = CbTRUE;
	} else {
		/* Start Immobilizer routine while condition met. */
		if (((AuthenticationResultLost() )
				&& (GetVIOS_IgnSt() == CeIGN_ON)
				&& (!( (GetFUEL_DFCO_Enabled()) && (ImmoAuthenticationResultPass()) && (GetEngineTurning()))))
			||R_LineSignalGenerate)
		{
			SiemensImmo_Initializing();
			R_LineSignalGenerate=false;
		}

		/* Total authentication time limit till authentication pass */
		ImmoEngineRunLimit();
		if (!GetNormalKeywordMode()) {
			/* Limit ECU Pre-Enable time */
			SiemensImmo_CntrlPreEnableTime();
			/* Limit KW Communication Time under IMMO mode */
			SiemensImmo_CntrlIMMOKWTime();
			/* Update RLine state */
			SiemensImmo_CntrlRLineSignal();
		}
	}
}

/*****************************************************************************
 *
 * Function:           SiemensImmo_PrepareAuthenData
 * Description:        Generate 6 bytes challenge data.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void SiemensImmo_PrepareAuthenData(void)
{
	BYTE ByteIndex;
	VaSiemens_RandomNum[0]=CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0090);
	VaSiemens_RandomNum[1]=CalculateChecksum((uint8_t*) 0x3FA0, (BYTE*) 0x3FB7)\
						+CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0050)+(BYTE)HAL_Analog_Get_IGNVI_Value();
	VaSiemens_RandomNum[2]=CalculateChecksum((uint8_t*) 0x3FB8, (BYTE*) 0x3FCF)\
						+CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0060)+(BYTE)HAL_Analog_Get_MAPVI_Value();
	VaSiemens_RandomNum[3]=CalculateChecksum((uint8_t*) 0x3FD0, (BYTE*) 0x3FE7)\
						+CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0070);
	VaSiemens_RandomNum[4]=CalculateChecksum((uint8_t*) 0x3FE8, (BYTE*) 0x3FFF)\
						+CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0080);
	VaSiemens_RandomNum[5]=CalculateChecksum((uint8_t*) 0x4000, (BYTE*) 0x4017)\
						+CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0090);
}

/*****************************************************************************
 *
 * Function:           SiemensImmo_Initializing
 * Description:        Initialize Siemens generic immobilizer
 * Execution Rate:     Power-on & COP timeout initialization                
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void SiemensImmo_Initializing(void)
{
	if (CheckIMMO_ECMNotLearned() ) {
		ImmoDisableEngine();
		VbSiemens_ImmoFuncNotProgrammed = CbTRUE;
		SbImmo_KeyCodeNotPgmdTestComplete = CbTRUE;
		SbImmo_KeyCodeNotPgmdTestFailed = CbTRUE;
		VeSiemens_ActReason = CeIMMO_ECUInVirgin;
	} else {
		VbSiemens_ImmoFuncNotProgrammed = CbFALSE;
		SbImmo_KeyCodeNotPgmdTestComplete = CbTRUE;
		SbImmo_KeyCodeNotPgmdTestFailed = CbFALSE;
	}

	/* ECU Pre-Enable */
	VbSiemens_ECUPreEnable = CbTRUE;
	SwSiemens_PreEnblTimerCntr = 0;

	/* Before authentication, allow engine, but result in NVRAM set to invalid.
	It will be updated after authentication ends. */
	ImmoEnableEngine();
	/* Trigger RLine Request */
	if(IGNOffModeTimeOut) {
		/* If fast ignition off/on happened, leave 150ms delay per immo spec */
		PowerUpDelayTiniCntr = PowerUpDelayTiniTime;
		IGNOffModeTimeOut = false;
	}

	SbSiemens_RLineTriggerEnbl = CbTRUE;
	SbSiemens_RLineStatus = CbON;
	SySiemens_RLineTimerCntr = V_COUNT_BYTE(0);
	
	/* IMMO KW Enable */    
	SbSiemens_IMMOKWEnable = CbTRUE;
	SwSiemens_IMMOKWEnblTimerCntr = V_COUNT_WORD(0);
	
	/*--- Initialize Functionalities ---*/
	VeSiemens_ECMImmoRelation = CeSiemens_StartCommunication;
	/* Set Immo_DLL_State <-- CeIMMO_WaitICUResponse */
	SetSiemens_DLLStateToWaitICURequest();
	ValidateAuthenticationResult();
	ClearImmoAuthenticationResult();
}

/*****************************************************************************
*                                                                            *
* Function:          SiemensImmo_P3MaxOvertime                                  *
* Description:       P3Max(time to wait icu request) overtime handler        *
*                                                                            *
* Execution Rate:    Ignition-on initialization                              *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
void SiemensImmo_P3MaxOvertime(void)
{
	if (VySiemens_P3MaxOvertimeCntr < 3) {
		/* Leave enough time for immobilizer to retry last request message 
		If immobilizer has tried 3 times, then it'll restart communication */
		VySiemens_P3MaxOvertimeCntr++;
	} else {
		/* Switch to Keyword TIDLE state here. Because P3Max check is bypassed in 
		CntrlIMMO_InitSCIRcvStatus() after first ECM response sent. */
		VySiemens_P3MaxOvertimeCntr = 0;
		/* Same as P3Max timeout in KW2000_Port_State_Awaiting_Message() */
		/* After stopping communication by time-out P3max: TIdle >= 0 ms */
		Kw2000State = k2sWaitingTIdleSynch;
	}
}

/******************************************************************************
 * Local Function
 ******************************************************************************/

/*****************************************************************************
 *                                                                           *
 * Function:            SiemensImmo_CntrlRLineSignal                            *
 * Description:         This procedure update timer and toggle pin           *
 *                      every 7p8ms until timer expired                      *
 *                                                                           *
 * Parameters:          None                                                 *
 * Return:              None                                                 *
 *****************************************************************************/
static void SiemensImmo_CntrlRLineSignal (void)
{
	/* R-Line Request:
	a rectangular signal with a period between 10 and 30 ms 
	(edge distance 5 to 15 ms) and a duration of 100 to 130 ms.

	Toggle a discrete output pin every 7.81ms to make a rectangular signal 
	with a period of 15.6ms (edge distance 7.81ms). 
	After 8 cycles, the duration will be 125ms.

	RLine output pin need to be initialized to low at start?
	*/
	if (PowerUpDelayTiniCntr) {
		PowerUpDelayTiniCntr--;
	} else {
		if ( (SbSiemens_RLineTriggerEnbl) && (SySiemens_RLineTimerCntr < CySiemens_RLineTimerCnt7p8ms )) {
			/* 16*7p8125ms = 125ms */
			if(CbON == SbSiemens_RLineStatus) {
				/* Low Side Driver */
				// DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, TRUE);
				HAL_GPIO_SET_IMMOREQ_Enable(true);
				SbSiemens_RLineStatus = CbOFF;
			} else if(CbOFF == SbSiemens_RLineStatus) {
				// DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, FALSE);
				HAL_GPIO_SET_IMMOREQ_Enable(false);
				SbSiemens_RLineStatus = CbON;
			}
			SySiemens_RLineTimerCntr++;
		} else {
			// DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, FALSE);
			HAL_GPIO_SET_IMMOREQ_Enable(false);
			SbSiemens_RLineStatus = CbOFF;
			SbSiemens_RLineTriggerEnbl = CbFALSE;
		}
	}
}

/*****************************************************************************
 *
 * Fuction:           SiemensImmo_CntrlPreEnableTime
 *
 * Description:       Control ECU Pre-Enable Time.
 *
 * Execution Rate:    7.81 ms
 *
 * Parameters:        None
 *
 * Return:            None
 *
 *****************************************************************************/
static void SiemensImmo_CntrlPreEnableTime(void)
{
	if ( (VbSiemens_ECUPreEnable) && (SwSiemens_PreEnblTimerCntr < KwIMMO_SiemensPreReleaseTime ) ) {
		/* This 1p8s timer will limit the engine Pre-release time. */
		SwSiemens_PreEnblTimerCntr++;
	} else {
		VbSiemens_ECUPreEnable = CbFALSE;

		/* disable engine now if authentication still not pass,
		let the authentication progress keep going on */
		if (ImmoAuthenticationResultPass() ) {
			ImmoEnableEngine();
		} else {
			// if ( (!ImmoPassThisKeyon)
			//    || ( ( (EOBD_VehSpd < K_ImmoByPassVSS)&& 
			//          (!GetDGDM_FaultActive(CeDGDM_VSS_NoSignal) ) 
			//          )
			//       || ( (GetDGDM_FaultActive(CeDGDM_VSS_NoSignal) )
			//          && (!GetVIOS_EngSt_Run() ) ) ) )
			if ( !ImmoPassThisKeyon || (EOBD_VehSpd < K_ImmoByPassVSS) || !GetVIOS_EngSt_Run()) {
				/* When authentication failed, disable the engine only if following 
				conditions met, else bypass the authentication result:
				i) Nb_ImmoPassThisKeyon is not set to True;
				- or -
				ii) VSS fault is not present and vehicle speed is less than or equal 
				to K_ImmoBypassVSS;
				- or -
				iii) VSS fault is present and engine state is Stall; */
				ImmoDisableEngine();
			}
		}
	}
}


/*****************************************************************************
 *
 * Fuction:           SiemensImmo_CntrlIMMOKWTime
 *
 * Description:       Limit KW Communication Time under IMMO mode.
 *
 * Execution Rate:    7.81 ms
 *
 * Parameters:        None
 *
 * Return:            None
 *
 *****************************************************************************/
static void SiemensImmo_CntrlIMMOKWTime(void)
{
	if ( (SbSiemens_IMMOKWEnable) && (SwSiemens_IMMOKWEnblTimerCntr < CwSiemens_IMMOKWEnblTimerCnt7p8ms) )
	{
		/* This 4s timer will limit the total time of waiting IMMO's 
		communication request. Go to EndAuthentication state.*/
		SwSiemens_IMMOKWEnblTimerCntr++;
	} else {
		GoToEndResponderState();
		SbSiemens_IMMOKWEnable = CbFALSE;
	}
}
/*****************************************************************************
 *
 * Function:           IMMOECMRunningReset
 * Description:        Check ECM running reset state
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
static void ImmoECMRunningResetCheck(void)
{
	if (//Running_Reset_Occurred()&&
	(!GetFILE_NVM_Failure() ) 
	&& (AuthenticationResultLost() ) )
	{
		if (AuthenticationResult == CbTRUE) {
			ImmoEnableEngine();
			SetImmoAuthenticationResult(CbTRUE);
			ValidateAuthenticationResult();      
		}
	}
}
/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
