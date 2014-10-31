/*===========================================================================*/
/* FILE: immo_comu.c                                                         */
/*===========================================================================*/
/* COPYRIGHT, 2004, DELPHI ELECTRONICS & SAFETY SYSTEMS, All Rights reserved */
/* Delphi Confidential                                                       */
/*===========================================================================*/
/* %name:             immo_comu.c %                                          */
/*                                                                           */
/* created_by:       Liu Zheng                                                */
/*                                                                           */
/* date_created:     26 Feb 2005                                              */
/*                                                                           */
/* %derived_by:       vzp48z %                                               */
/*                                                                           */
/* %date_modified:   %                                                       */
/*                                                                           */
/* %version:         5 %                                                     */
/*                                                                           */
/*===========================================================================*/
/* DESCRIPTION:                                                              */
/*   This file contains executive called during power On for Immobiliser.    */
/*                                                                           */
/* ABBREVIATIONS:                                                            */
/* None.                                                                     */
/*                                                                           */
/* TRACEABILITY INFO:                                                        */
/*   Design Document:                                                        */
/*                                                                           */
/*   Requirements Document(s):                                               */
/*                                                                           */
/*   Applicable Standards:                                                   */
/*   C Coding Standards:        SW_REF 264.15D.                              */
/*                                                                           */
/* DEVIATIONS FROM STANDARDS:                                                */
/* None.                                                                     */
/*                                                                           */
/*===========================================================================*/
/* REUSE: DO NOT MODIFY THIS FILE.                                           */
/* Co-ordinate any desired changes with the Software Forward Engineering and */
/* Building Blocks group                                                     */
/*===========================================================================*/
#include "io_type.h"


/* ========================================================================== *\
 * Other header files.
\* ========================================================================== */
#include "immo.h"
#include "immo_exec.h"
#include "immo_encrypt.h"
#include "immo_fexi.h"
#include "kw2app.h"
#include "kw2dll.h"
#include "kw2dllcf.h"
#include "kw2exec.h"

/*for Siemens immo*/
#include "siemens_immossrv.h"
#include "kw2srv27.h"
/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
extern void ImmoEndService(void);
//extern FAR_COS void GoToEndTesterState(void);
extern void GoToEndResponderState(void);
/* ========================================================================== *\
 * Global variables.
\* ========================================================================== */
bool ImmoNoResponseDetected;
bool ImmoAuthenErrorDetected;
bool Immo_KLineDisconnected;

/*Added newly for Siemens Immo*/

TeIMMO_ActReason        VeSiemens_ActReason;
TeSiemens_ECM_Relation  VeSiemens_ECMImmoRelation;
TeIMMO_DLL_STATUS       VeSiemens_DLL_State;
TbBOOLEAN               VbSiemens_StartCommReceived;
TbBOOLEAN               VbSiemens_StopCommReceived;

  //uint16_t  Level2SecurityTimer_Temp;
uint16_t L2SecurityTmrCoefficient;
/* ========================================================================== *\
 * Local Macro definitions
\* ========================================================================== */
#define SINGLEAUTHENMAXTIME_TIMES2         ( K_SingleAuthenticationMaxTime * 2 )
#define Delay2ms          FixDefConst(2000.0, MicroSec_HighRes_Type)
#define Delay4ms          FixDefConst(4000.0, MicroSec_HighRes_Type)
/*for Siemens immo */
/* Time counter for CeIMMO_SendingRequestMsg state. 7.8125ms per count */
static Every_Loop_Sec_B SyIMMO_SendReqMsgTimeCntr;
/*for Siemens immo */
/* Time counter for CeIMMO_WaitICUResponse state. 7.8125ms per count */
static Every_Loop_Sec_B     SyIMMO_SingleAuthCntr;

/* ========================================================================== *\
 * Local funcs declaration
\* ========================================================================== */
/*for Siemens Immo*/
//static void CntrlIMMO_WaitTinitime(void);
/*for Siemens Immo*/
static void CntrlIMMO_PrepareResponseMessage(void);
/*for Siemens Immo*/
static void DtrmnIMMO_BuildKW2000Response(void);
/*for Siemens Immo*/
static void CntrlIMMO_SendingResponseMsg(void);
/*for Siemens Immo*/
static TbBOOLEAN CheckIMMO_ReqIsSentOut(void);
/*for Siemens Immo*/
static void CntrlIMMO_InitSCIRcvStatus(void);
/*for Siemens Immo*/
static void CntrlIMMO_WaitICURequest(void);
/*for Siemens Immo*/
static TbBOOLEAN CheckIMMO_GotICURequest(void);
/*for Siemens Immo*/
static void CheckIMMO_SingleAuthOvertime(void);
/*for Siemens Immo*/
static void DtrmnIMMO_LostCommService(void);
/*for Siemens Immo*/
static void DtrmnIMMO_ReAuthentication(void);
/*for Siemens Immo*/
static void DtrmnIMMO_ReAcknowldge(void);

const T_COUNT_WORD    CaSiemens_L2WrongAttemptDelay[10] = {1, 1, 60, 120, 240, 480,960, 1920, 3840, 7680};// 10s/count

/*****************************************************************************
 *
 * Function:           ImmoEndService
 * Description:        Handle exit service to end immo communication.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void ImmoEndService(void)
{
	/* Change ECM from KW2000 tester to KW2000 responder. */
	ECMImmoRelation=NO_Relation;
	VeSiemens_ECMImmoRelation=CeSiemens_NoRelation;
	/* For normal KW2000 slave service, initialize KW2000. */
	KW2000CommuState=KW2000_Responder;

	if(GetMultiRespInProgress()) {
		/* For matching process, back to waitingmessage state to send response. */
		SetTimingParameterToDefault ();
		GoToAwaitingMessageK2State (TRUE);
	} else {
		if (GetImmoAuthenticationResult()) {
			ImmoEnableEngine();
			SbImmo_NoResponseTestComplete = CbTRUE;
			SbImmo_NoResponseTestFailed = CbFALSE;
			SbImmo_AuthenErrorTestComplete = CbTRUE;
			SbImmo_AuthenErrorTestFailed = CbFALSE;
			// if (GetDGDM_DTC_FaultType (CeDGDM_ImmoNoResponse) != CeDGDM_FAULT_TYPE_Z)
			// {
			//    PerfmDGDM_ProcessPassReport(CeDGDM_ImmoNoResponse);
			// }
			// if (GetDGDM_DTC_FaultType (CeDGDM_ImmoAuthenError) != CeDGDM_FAULT_TYPE_Z)
			// {
			//    PerfmDGDM_ProcessPassReport(CeDGDM_ImmoAuthenError);
			// }
		} else {
			//  if ((!ImmoPassThisKeyon )||
			// ((!GetDGDM_FaultActive(CeDGDM_VSS_NoSignal) &&(EOBD_VehSpd <= K_ImmoByPassVSS)) || 
			//   ((!GetEngineTurning()) &&(GetDGDM_FaultActive(CeDGDM_VSS_NoSignal)))))
			if (!ImmoPassThisKeyon || (EOBD_VehSpd <= K_ImmoByPassVSS) || !GetEngineTurning()) {
				ImmoDisableEngine();
			}

			if (ImmoAuthenErrorDetected)
			{
				SbImmo_NoResponseTestComplete = CbTRUE;
				SbImmo_NoResponseTestFailed = CbFALSE;
				SbImmo_AuthenErrorTestComplete = CbTRUE;
				SbImmo_AuthenErrorTestFailed = CbTRUE;
				//    if(GetDGDM_DTC_FaultType (CeDGDM_ImmoAuthenError) != CeDGDM_FAULT_TYPE_Z)
				//    {
				//        PerfmDGDM_ProcessFailReport(CeDGDM_ImmoAuthenError);
				//    }
				//    if (GetDGDM_DTC_FaultType (CeDGDM_ImmoNoResponse) != CeDGDM_FAULT_TYPE_Z)
				//    {
				//        PerfmDGDM_ProcessPassReport(CeDGDM_ImmoNoResponse);
				//    }
			}
			// else if (ImmoNoResponseDetected && GetDGDM_DTC_FaultType (CeDGDM_ImmoNoResponse) != CeDGDM_FAULT_TYPE_Z)
			else if (ImmoNoResponseDetected)
			{
				SbImmo_NoResponseTestComplete = CbTRUE;
				SbImmo_NoResponseTestFailed = CbTRUE;
				//    PerfmDGDM_ProcessFailReport(CeDGDM_ImmoNoResponse);
			}
			else
			{
				/* do nothing */
			}
		}
		KeywordExecutive( CwKW2000_Initializes ) ;
		L2_WrongAttemptTry=0;
	}
}/*** End of ImmoEndService ***/

/*****************************************************************************
 *
 * Function:           Update_IMMO_DLL_Service
 * Description:        change KW2000 service state.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void Update_IMMO_DLL_Service(void) 
{
	if (Chk_SiemensImmo_Enabled()) {
		switch (VeSiemens_DLL_State) {
			case CeIMMO_WaitTiniTime:
			{
				//CntrlIMMO_WaitTinitime();
				break;
			}
			case CeIMMO_SendingWup:
			{
				CntrlIMMO_PrepareResponseMessage();
				break;
			}
			case CeIMMO_SendingResponseMsg:
			{
				CntrlIMMO_SendingResponseMsg ();
				break;
			}
			case CeIMMO_WaitICURequest:
			{
				CntrlIMMO_WaitICURequest();
				break;
			}
			case CeIMMO_IdleState:
			{
				break;
			}
			default:
			{
				break;
			}
		}
		CheckIMMO_SingleAuthOvertime();
	}
}

/* for Siemens Immo*/
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_WaitTinitime                                  *
* Description:       Wait Tini time elasped                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
#if 0
static void CntrlIMMO_WaitTinitime(void)
{
  if (PowerUpDelayTiniCntr)
  {
    PowerUpDelayTiniCntr--;
  }
  else
  {
    SetSiemens_DLLStateToSendingWup ();
  }
}
/* for Siemens Immo */

#endif
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_PrepareRequestMessage                                  *
* Description:       Immo Prepare request message                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_PrepareResponseMessage(void)
{
	/*----- build frame and trigger sending  ----*/
	DtrmnIMMO_BuildKW2000Response();
	/* Siemens: P2Max Timer */
	SyIMMO_SendReqMsgTimeCntr = 0;
	//  Kw2000State=k2sSendingMessage;/* this is for test generateing response with random, but it is not correct*/

	SetSiemens_DLLStateToSendingResponseMsg ();
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          DtrmnIMMO_BuildKW2000Request                                  *
* Description:       Immo Prepare request message                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void DtrmnIMMO_BuildKW2000Response(void)
{
	/* Prepare Request message. */	
	switch(VeSiemens_ECMImmoRelation)
	{
		case CeSiemens_Authentication:
		{
			SiemensImmo_BldChallengeRspMsgFrame();
			break;
		}
		case CeSiemens_FeedbackAuthentication:
		{
			SiemensImmo_BldCodeRspMsgFrame();
			break;
		}
		case CeSiemens_StartCommunication:
		case CeSiemens_StopCommunication:
		{
				break;
		}
		case CeSiemens_NoRelation:
		case CeSiemens_EndAuthentication:

		default:
		{
			GoToEndResponderState();
			break;
		}
	}
}
/* For Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_SendingResponseMsg                             *
* Description:       Waiting for response being sent out.                    *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_SendingResponseMsg(void)
{
	/* Siemens IMMO use SendStandardNegativeAnswer() and SendStandardPositiveAnswer()
	 in standard KW commuication, so here we have to run the KW DLL machine to update
	 P2 timer logic before go to sending message */

	UpdateKeyword2000VIO();

	if (CheckIMMO_ReqIsSentOut()) {
		/* directly set KW state to KW2000_STATE_RECEIVING_MESSAGE
		skip any initialization phase, prepare for receiving Response */

		CntrlIMMO_InitSCIRcvStatus();
		SyIMMO_SingleAuthCntr = 0;
		SetSiemens_DLLStateToWaitICURequest ();

		/* A round of ICU-ECU communication has finished here.
		Run state machine actively. */
		switch(VeSiemens_ECMImmoRelation) {
			case CeSiemens_Authentication:
			{
				/* Go to Immo Code service loop */
				VeSiemens_ECMImmoRelation = CeSiemens_FeedbackAuthentication;
				break;
			}
			case CeSiemens_FeedbackAuthentication:
			{
				if(ImmoAuthenticationResultPass()) {
					/* Authentication success, go to stop communication status
					wait immo to send stop communication request*/
					VeSiemens_ECMImmoRelation = CeSiemens_StopCommunication; 
				} else {
					/* Redirect workflow to wait IMMO to send a new round 
						challenge request until pre-release time elapsed. */
					VeSiemens_ECMImmoRelation = CeSiemens_Authentication;
				}
				break;
			}
			case CeSiemens_NoRelation:
			case CeSiemens_StartCommunication: /* handled below */
			case CeSiemens_StopCommunication: /* handled below */
			case CeSiemens_EndAuthentication:
			default:
			{
				break;
			}
		}

		if(VbSiemens_StartCommReceived) {
			/* In case IMMO send start communication request out of state 
			machine transition control. Go to authentication state. */
			VeSiemens_ECMImmoRelation = CeSiemens_Authentication;
			VbSiemens_StartCommReceived = CbFALSE;
		} else if(VbSiemens_StopCommReceived) {
			/* In case IMMO send stop communication request out of state 
			machine transition control. End immediately. */
			GoToEndResponderState();        
			VbSiemens_StopCommReceived = CbFALSE;
		}
	} else if (SyIMMO_SendReqMsgTimeCntr >= (K_SingleAuthenticationMaxTime * 2) ) {
		VeSiemens_ActReason = CeIMMO_ECURespTimeOut;
		/* Siemens:   P2Max Timer (slave) expired */

		/* Failed to send message within P2Max. Redirect DLL state machine to wait 
		ICU's new round of challenge instead of ending up authentication */
		SetSiemens_DLLStateToWaitICURequest();
	} else {
		SyIMMO_SendReqMsgTimeCntr++;
	}
}

/* for Siemens Immo */   //TBD:
/*****************************************************************************
 *
 * Function:           GotoEndTesterState
 * Description:        Goto EndResponder state.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void GoToEndResponderState (void)
{
	SyIMMO_SingleAuthCntr = 0;
	VeSiemens_ECMImmoRelation = CeSiemens_EndAuthentication;
	SetSiemens_DLLStateToIdleState();
} /*** End of GotoEndResponderState ***/

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CheckIMMO_ReqIsSentOut                                  *
* Description:       This procedure will determine if the request message is *
*                    currently being sent.                                   *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            CbTRUE: request message has been sent                   *
*                    CbFALSE: request message is still being sent            *
*                                                                            *
*****************************************************************************/
static TbBOOLEAN CheckIMMO_ReqIsSentOut (void)
{
	TbBOOLEAN LbSentOut;

	/* Siemens IMMO use SendStandardNegativeAnswer() and SendStandardPositiveAnswer()
	in standard KW handler, so here we reuse the standard interface */
	if(Keyword2000AnswerStillBeingSent()) {
		LbSentOut = CbFALSE;      
	} else {
		LbSentOut = CbTRUE;
	}
	return LbSentOut;
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_InitSCIRcvStatus                              *
* Description:       This procedure will set states to receiving data from   *
*                    ICU                                                     *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_InitSCIRcvStatus (void)
{
	GoToAwaitingMessageK2State (TRUE);
	/* Here we leaped over the Awaiting Message state,
	then P3Max could not be checked. */
	GoToReceivingMessageK2State ();
	ClearSCIRespReceivedFlag();
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_WaitICURequest                               *
* Description:       Wait response from ICU.                                 *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_WaitICURequest(void)
{
	/* Currently KW is in IMMO authentication state,KeywordMode is false. 
	The KW task is different with the one in MngOSTK_7p82msGenericTasks which
	is disabled now */
	UpdateKeyword2000VIO() ;

	if (CheckIMMO_GotICURequest()) {
		/* Set the response receive flag which is to trigger APP Service Table */
		SetSCIRespReceivedFlag();
		SetSiemens_DLLStateToIdleState ();
	}
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CheckIMMO_GotICURequest                                *
* Description:       This procedure will determine if a message has been     *
*                    recieved from the ICU.                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            CbTRUE: Response recieved; CbFALSE: no response yet     *
*                                                                            *
*****************************************************************************/
static TbBOOLEAN CheckIMMO_GotICURequest(void)
{
	TbBOOLEAN LbGotResponse;
	LbGotResponse = CbFALSE;

	if(Chk_SiemensImmo_Enabled()) {
		/* communication established, here dealing the app level services */
		if( Kw2000State == k2sWaitingAppLvlServiceExec) {
			LbGotResponse = CbTRUE;      
		}
	}

	if ( Kw2000State == k2sErrorRead ) {
		/* received an error frame, try again. */
		CntrlIMMO_InitSCIRcvStatus();
	}

	return LbGotResponse;
}

/* for Siemens Immo */
/*****************************************************************************
 *
 * Function:           CheckIMMO_SingleAuthOvertime
 * Description:        Check Single Authentication Time
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
static void CheckIMMO_SingleAuthOvertime(void)
{
	if (CeIMMO_WaitICURequest== VeSiemens_DLL_State) {
		if (DtrmnIMMO_SingleAuthTimeOvertime(SyIMMO_SingleAuthCntr) ) {
			SyIMMO_SingleAuthCntr = 0;
			DtrmnIMMO_LostCommService();
			//VbIMMO_RprtNoICUResponse = CbTRUE;
			ImmoNoResponseDetected = true;
		} else {
			SyIMMO_SingleAuthCntr++;
		}
	}
}

/* for Siemens immo*/
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_SingleAuthTimeOvertime
 *
 * Description:        Check if single authentication counter overflow
 *
 * Parameters:         authentication counter
 *
 * Return:             TRUE - counter overflow
 *                     FALSE - counter doesn't overflow
 *
 *****************************************************************************/
TbBOOLEAN DtrmnIMMO_SingleAuthTimeOvertime(Every_Loop_Sec_B counter)
{
	TbBOOLEAN result = CbFALSE;

	/* This will take care of the P3Max Timing check of Siemens */
	if(Chk_SiemensImmo_Enabled() )  {
		if( (CeSiemens_FeedbackAuthentication == VeSiemens_ECMImmoRelation)
		&& (counter >= K_SingleAuthenticationMaxTime * 4) )/*4*/
		{
			/* P3_la max timer (270ms). Waiting for immoCode request msg */
			result = CbTRUE;
		}
		else if( ( (CeSiemens_Authentication == VeSiemens_ECMImmoRelation) 
		|| (CeSiemens_StopCommunication == VeSiemens_ECMImmoRelation) )
		&& (counter >= K_SingleAuthenticationMaxTime) )/*Added /2 */
		{
			/* P3_lb max timer (60ms) */
			result = CbTRUE;
		}
		else if( (CeSiemens_StartCommunication== VeSiemens_ECMImmoRelation) 
		&& (counter >= K_SingleAuthenticationMaxTime * 10) )/*10*/
		{
			/* max timer of waiting for start communication request (600ms) */
			result = CbTRUE;
		}
	}

	return result;
}

/* for Siemens immo */
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_LostCommService
 * Description:        Handle lost communication error.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
static void DtrmnIMMO_LostCommService(void)
{
	VeSiemens_ActReason = CeIMMO_ICURespTimeOut;

	switch(VeSiemens_ECMImmoRelation) {
		case CeSiemens_Authentication:
		{
			DtrmnIMMO_ReAuthentication();
			break;
		}
		case CeSiemens_FeedbackAuthentication:
		{
			DtrmnIMMO_ReAcknowldge();
			break;
		}
		case CeSiemens_StartCommunication:
		case CeSiemens_StopCommunication:
			break;
		case CeSiemens_NoRelation:
		case CeSiemens_EndAuthentication:
		default:
		{
			/* Save Erro code and Go to End Service in next loop. */
			ClearImmoAuthenticationResult();
			GoToEndResponderState();
			break;
		}
	}
}

/*for Siemens Immo*/
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_ReAuthentication
 *
 * Description:        Handle authorization service overtime operation:
 *                     If ECM does not receive postive response after sending out A0 request,
 *                     DtrmnIMMO_ReAuthentication is called to re-direct work flow.
 *
 * Parameters:         None
 *
 * Return:             None
 *
 *****************************************************************************/
static void DtrmnIMMO_ReAuthentication(void)
{
	if ( Chk_SiemensImmo_Enabled() ) {
		SiemensImmo_P3MaxOvertime();
	}
}

/*for Siemens Immo*/
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_ReAcknowldge
 *
 * Description:        Handle Feed back authorization result service overtime operation.
 *                     If ECM does not receive postive response after sending out A1 request,
 *                     DtrmnIMMO_ReAcknowldge is called to re-direct work flow.
 *
 * Parameters:         None
 *
 * Return:             None
 *
 *****************************************************************************/
static void DtrmnIMMO_ReAcknowldge(void)
{
	if ( Chk_SiemensImmo_Enabled() ) {
		SiemensImmo_P3MaxOvertime();
	}
}

/**********************************************************************/
/***    Load the level 2 security timer                             ***/
/**********************************************************************/
void TriggerL2SecurityTiming (void)
{
	if(Chk_SiemensImmo_Enabled() ) {
		/* count the number of incorrect securityCode entries and 
		insert the respective locking periods */
		if(L2_WrongAttemptTry < 10) {
			L2_WrongAttemptTry++;
		}

		Level2SecurityTimer = CaSiemens_L2WrongAttemptDelay[L2_WrongAttemptTry - 1];
		L2SecurityTmrCoefficient=1250;
	}
}

/*****************************************************************************
 *
 * Function:           LearnSKandPINService
 * Description:       Mulresp service of learning process.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
void LearnSKandPINService(void)
{
	if (LearnSKandPINState==CbTRUE) {
		/* ECM can switch to tester only after sending $78 response. */
		if (!Keyword2000AnswerStillBeingSent()) {
			if (SKPIN_LearnMode==0x0A) GoToECMLearnFromImmoState();
			if (SKPIN_LearnMode==0x0B) GoToImmoLearnFromECMState();
			LearnSKandPINState=CbFALSE;
		}
	} else {
		/* Back from tester to responder, recover header message. */
		RxFormatByte=RxFormatByte_Responder;
		RxSourceAddress=RxSourceAddress_Responder;
		/* Send response according to Immo_Erro_Code. */
		if(Immo_Erro_Code==NO_IMMO_ERROR) {
			TxServiceData[0]=0x70;
			TxServiceData[1]=0x62;
			TxServiceData[2]=SKPIN_LearnMode;
			RxServiceData[0]=0x30;
			SendStandardPositiveAnswer(3);
		} else {
			RxServiceData[0]=0x30;
			SendStandardNegativeAnswer(Immo_Erro_Code);
		}
		/* Clear MultiResp flag. */
		WrtMultiRespInProgress( CbFALSE  ) ;
		SKPIN_LearnMode=0;
	}
}/*** End of LearnSKandPINService ***/

/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/*
/* ===========================================================================*/


