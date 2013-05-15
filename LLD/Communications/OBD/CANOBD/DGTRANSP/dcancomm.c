/*-------------------------------------------------------------------*/
/* filename -  DCANCOM.C                                             */
/*                                                                   */
/* purpose:                                                          */
/*    This module is application layer of the Delco Electronics      */
/*    engine control s/w, where the Rx Tx functions and the          */
/*    communication state machine needed for GMLAN diagnostics       */
/*    services are defined.                                          */
/*                                                                   */
/*    LN stands for Local Network of GMLAN                           */
/*                                                                   */
/*                                                                   */
/* list of function(s):                                              */
/*  InLine:                                                          */
/*          GoToStandardP2cMax                                       */
/*          InitializeLnCommunicationTimingParameters                */
/*          InitializeLnDiagSvCommunicState                          */
/*          InitializeLnNodeManagementState                          */
/*          UpdateLnCommunicationTimingParameters                    */
/*          UpdateP2cMaxWaitingLoop                                  */
/*          UpdateDiagComActiveTimer                                 */
/*  Implem:                                                          */
/*          LnAnswer                                                 */
/*          LnGoToDiagnosticComNotActive                             */
/*          LnGoToRxCompleteWaitingAppToRespond                      */
/*          LnGoToSendingAnswer                                      */
/*          LnGoToWaitingP2cMinBeforeAnswer                          */
/*          LnGoToWaitingRequest                                     */
/*          LnGoToWaitingReqstRxStrtdApplCanStart                    */
/*          LnEventFrameTransmitted                   -h-            */
/*          LnEventReceptionCompleteMsgWaiting                       */
/*          LnEventRxWaitingAppToEmptyRingBuffer                     */
/*          LnWaitingP2cMinBeforeAnswerState                         */
/*          AcknoledgeLnRequestWithoutResponse        -h-            */
/*          SendLnNegativeAnswerRoutNotComplete       -h-            */
/*          SendLnStandardNegativeAnswer              -h-            */
/*          SendLnStandardPositiveAnswer              -h-            */
/*          SendLnUudtAnswer                          -h-            */
/*          UpdateLnDiagSvCommunication               -h-            */
/*                                                                   */
/*          InitializeLnDiagSvCommunication           -h-            */
/*                                                                   */
/*-------------------------------------------------------------------*/
/* DELPHI Delco Luxembourg C Engine Management Software              */
/* (c) Copyright DELPHI Delco Electronics System 2001                */
/*-------------------------------------------------------------------*/

 /****************************************************************************
 *
 * Current Module Info:
 * %full_name:      lux_pt1#1/csrc/lndgcom.c/1 %
 * %date_created:   Wed Feb 15 18:20:47 2006 %
 * %version:        1 %
 * %derived_by:     c23cr %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/

/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanserv.h"/*ChangeSession()*/
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"   /* for ...    */
//#include "dcantran.h"/*for LnGoToWaitingForRxFirstOrSingleFrame()*/
/******************************************************************************
*OBD Lib Service Include Files
******************************************************************************/
//#include "obdlserv.h"/*PositiveResponseOffset */
/******************************************************************************
 *  Global Variables
 *****************************************************************************/
LnDiagSvCommunicationStateType  LnDiagSvCommunicationState;
/******************************************************************************
 * Static Variables
 *****************************************************************************/
static TwTIME_t_R7p8125ms P2cMinCounter;
static TwTIME_t_R7p8125ms P2cMin;
static TwTIME_t_R7p8125ms P2cMaxCounter;
static TwTIME_t_R7p8125ms P2cMax;
/*--- P3 = Time for TesterPresent requests must be received ---*/
static TwTIME_t_R7p8125ms DiagComActiveTimer;

/**********************************************************************/
/*** Function prototype                                             ***/
/**********************************************************************/
//void InitializeLnDiagSvCommunication (void);

/************************************************************/
/************************************************************/
/************************************************************/
/***                                                      ***/
/*** CANOBD DIAGNOSTIC SERVICE COMMUNICATION STATE MACHINE ***/
/***                                                      ***/
/*** This state machine controls the timing between the   ***/
/*** Reception and the transmission of the messages       ***/
/***                                                      ***/
/************************************************************/
/************************************************************/
/************************************************************/

/******************************/
/*** Go To Enhanced P2c Max ***/
/******************************/
void GoToEnhancedP2cMax (void)
{
   P2cMax = C_R7p8125ms16 (EnhancedP2cMaxInMs / 1000.0);
} /*** End of GoToEnhancedP2cMax ***/

/******************************/
/*** Go To Standard P2c Max ***/
/******************************/
 void GoToStandardP2cMax (void)
{
   P2cMax = C_R7p8125ms16 (DefaultP2cMaxInMs / 1000.0);
} /*** End of GoToStandardP2cMax ***/

/************************************/
/*** LnGoToDiagnosticComNotActive ***/
/************************************/
void LnGoToDiagnosticComNotActive (void)
{
   LnDiagSvCommunicationState = DiagnosticComNotActive;
} /*** End of LnGoToDiagnosticComNotActive ***/

/****************************/
/*** LnGoToWaitingRequest ***/
/****************************/
void LnGoToWaitingRequest (void)
{
    DiagComActiveTimer = 0;
   LnDiagSvCommunicationState = WaitingRequest;
} /*** End of LnGoToWaitingRequest ***/
  
/************************************************************/
/*** Acknoledge Ln Request Without Response               ***/
/*** for functional request that do not send any response ***/
/************************************************************/
void AcknoledgeLnRequestWithoutResponse (void)
{
   LnGoToWaitingForRxFirstOrSingleFrame ();
   LnGoToWaitingRequest ();
} /*** End of AcknoledgeLnRequestWithoutResponse ***/ 

/*******************************/
/*** LnEventFrameTransmitted ***/
/*******************************/
void LnEventFrameTransmitted (void)
{
   LnGoToWaitingRequest ();
} /*** End of LnEventFrameTransmitted ***/

/********************************/
/*** LnSignalTranspErrorEvent ***/
/********************************/
void LnSignalTranspErrorEvent (LnTrspTimeOutErrorType LnTrspTimeOutError)
{
   //PARAM_NOT_USED (LnTrspTimeOutError);
   switch (LnDiagSvCommunicationState)
   {
      case DiagnosticComNotActive:
      case WaitingRequest:
      case WaitingReqstRxStrtdApplCanStart:
      case RxCompleteWaitingAppToRespond:
      case WaitingP2cMinBeforeAnswer:
      case SendingAnswer:
      default:
         LnGoToWaitingRequest ();
      break;
   }  
} /*** End of LnSignalTranspErrorEvent ***/

/*********************************************/
/*** LnGoToWaitingReqstRxStrtdApplCanStart ***/
/*********************************************/
void LnGoToWaitingReqstRxStrtdApplCanStart (void)
{
   LnDiagSvCommunicationState = WaitingReqstRxStrtdApplCanStart;
} /*** End of LnGoToWaitingReqstRxStrtdApplCanStart ***/

/*******************************************/
/*** LnGoToRxCompleteWaitingAppToRespond ***/
/*******************************************/
void LnGoToRxCompleteWaitingAppToRespond (void)
{ 
   P2cMaxCounter = 0;
   LnDiagSvCommunicationState = RxCompleteWaitingAppToRespond;
} /*** End of LnGoToRxCompleteWaitingAppToRespond ***/

/***************************************/
/*** LnGoToWaitingP2cMinBeforeAnswer ***/
/***************************************/
void LnGoToWaitingP2cMinBeforeAnswer (void)
{
   P2cMinCounter = 0;
   LnDiagSvCommunicationState = WaitingP2cMinBeforeAnswer;
} /*** End of LnGoToWaitingP2cMinBeforeAnswer ***/

/***************************/
/*** LnGoToSendingAnswer ***/
/***************************/
void LnGoToSendingAnswer (void)
{
   LnDiagSvCommunicationState = SendingAnswer;
   LnSendMessage ();
} /*** End of LnGoToSendingAnswer ***/

#if 0
/************************/
/*** SendLnUudtAnswer ***/
/************************/
void SendLnUudtAnswer (Can8DataBytesArrayType *Can8DataBytesArrayPtr, uint8_t NbBytesToTransmit)
{
   LnSendUudtMessage (Can8DataBytesArrayPtr, NbBytesToTransmit);
 } /*** End of SendLnUudtAnswer ***/
#endif 
/**************************************************************************/
/*** Update P2cMax Waiting Loop.                called Every Loop       ***/
/**************************************************************************/
INLINE void UpdateP2cMaxWaitingLoop (void)
{
   if (P2cMax != 0 && P2cMaxCounter < P2cMax)
   {
      P2cMaxCounter++;
   }
} /*** End of UpdateP2cMaxWaitingLoop ***/

/**************************************************************************/
/*** Update Diagnostic Communication Active Timer    called Every Loop  ***/
/**************************************************************************/
INLINE void UpdateDiagComActiveTimer (void)
{
   if (DiagComActiveTimer < C_R7p8125ms16 (DiagComDeactivationTimeInSec))
   {
      DiagComActiveTimer++;
   }
} /*** End of UpdateDiagComActiveTimer ***/

/***********************************************************************/
/*** GMLAN State periodic operation: LnRxCompleteWaitingAppToRespond ***/
/*** ---> Waiting maximum P2c for the application to respond         ***/
/***********************************************************************/
void LnRxCompleteWaitingAppToRespond (void)
{
   if (P2cMaxCounter >= P2cMax)
   {
      InitializeLnDiagSvCommunication (); /*--- reinitialize all diag service binz ---*/
   }
} /*** End of LnRxCompleteWaitingAppToRespond ***/ 

/**************************************************************************/
/*** GMLAN State periodic operation: LnWaitingP2cMinBeforeAnswerState   ***/
/*** ---> Waiting minimum P2c Time just before sending the answer       ***/
/**************************************************************************/
void LnWaitingP2cMinBeforeAnswerState (void)
{
  /*--- Increment P2 Min Timer to P2cMin ---*/
   if (P2cMinCounter < P2cMin)
   {
      P2cMinCounter++;
   }

  /*--- Send message when P2Min delay is passed ---*/
  /*--- P2cMin is rounded by excess - above the real minimum ---*/
   if (P2cMinCounter >= P2cMin)
   {
      LnGoToSendingAnswer ();
   }
} /*** End of LnWaitingP2cMinBeforeAnswerState ***/

/******************************************************/
/*** Initialize Ln Communication Timing Parameters  ***/
/******************************************************/
INLINE void InitializeLnCommunicationTimingParameters (void)
{
   GoToStandardP2cMax ();
/*---  P2cMinCounter = 0; ---*/
/*---  P2cMaxCounter = 0; ---*/
} /*** End of InitializeLnCommunicationTimingParameters ***/

/*****************************************************/
/*** Initialize GMLAN Diag Sv Communication State  ***/
/*****************************************************/
INLINE void InitializeLnDiagSvCommunicState (void)
{
   InitializeLnCommunicationTimingParameters ();
   LnDiagSvCommunicationState = DiagnosticComNotActive;
} /*** End of InitializeLnDiagSvCommunicState ***/

/***********************************************/
/*** Initialize GMLAN Node Management State  ***/
/***********************************************/
INLINE void InitializeLnNodeManagementState (void)
{
} /*** End of InitializeLnNodeManagementState ***/

/**************************************************/
/*** Update Ln Communication Timing Parameters  ***/
/**************************************************/
INLINE void UpdateLnCommunicationTimingParameters (void)
{
   UpdateP2cMaxWaitingLoop ();
   UpdateDiagComActiveTimer ();
  
   switch (LnDiagSvCommunicationState)
   {
      case DiagnosticComNotActive:
      break;
      case WaitingRequest:
      case WaitingReqstRxStrtdApplCanStart:
      if (DiagComActiveTimer == C_R7p8125ms16 (DiagComDeactivationTimeInSec))
      {
         LnGoToDiagnosticComNotActive ();
      }
              /* Handle S3Server timeout */
      if(CurrentSessionIndex != 0)
      {
         if( S3ServerTimer ==C_R7p8125ms16(0))
         {
            ChangeSession(DefaultSession);
            CurrentSessionIndex = 0;
	     ExtendedDiagnosticSessionControl= false;
         }
      }
      break;
      case RxCompleteWaitingAppToRespond:
         LnRxCompleteWaitingAppToRespond ();
      break;
      case WaitingP2cMinBeforeAnswer:
         LnWaitingP2cMinBeforeAnswerState ();
      break;
      case SendingAnswer:
      break;
      default:
      break;
   }
} /*** End of UpdateLnCommunicationTimingParameters ***/

/************************************************************/
/************************************************************/
/************************************************************/
/***                                                      ***/
/***                      END OF                          ***/
/*** CANOBD DIAGNOSTIC SERVICE COMMUNICATION STATE MACHINE ***/
/***                                                      ***/
/************************************************************/
/************************************************************/
/************************************************************/


/*********************************************/
/*********************************************/
/*********************************************/
/***                                       ***/
/*** CANOBD RECEIVE AND TRANSMIT FUNCTIONS  ***/
/***                                       ***/
/*********************************************/
/*********************************************/
/*********************************************/


/******************************************/
/*** LnEventReceptionCompleteMsgWaiting ***/
/******************************************/
void LnEventReceptionCompleteMsgWaiting (void)
{
   LnGoToRxCompleteWaitingAppToRespond ();
} /*** End of LnEventReceptionCompleteMsgWaiting ***/

/********************************************/
/*** LnEventRxWaitingAppToEmptyRingBuffer ***/
/********************************************/
void LnEventRxWaitingAppToEmptyRingBuffer (void)
{
   LnGoToWaitingReqstRxStrtdApplCanStart ();
} /*** End of LnEventRxWaitingAppToEmptyRingBuffer ***/

/********************/
/*** CANOBD answer ***/ 
/********************/
void LnAnswer (uint16_t DataLength)
{
  /*--- response must be physical ---*/
   SetLnMessageAddressingMode (PhysicalAddressing);
   WriteLnMessageDataLength (DataLength);

   if (P2cMinCounter < P2cMin)
   {
      LnGoToWaitingP2cMinBeforeAnswer ();
   }
   else
   {
      LnGoToSendingAnswer ();
   }
} /*** End of LnAnswer ***/

/***********************************************/
/*** builds a standart CANOBD negative answer ***/
/***********************************************/
void SendLnStandardNegativeAnswer (uint8_t NegativeResponseCode)
{
   (GetLnServiceData (1))  = (GetLnServiceData (0)) ;
   (GetLnServiceData (0)) = NegativeResponseServiceIdentifier;
   (GetLnServiceData (2)) = NegativeResponseCode;
   LnAnswer (3);

   if (NegativeResponseCode == RequestCorrectlyReceivedResponsePending)
   {
      GoToEnhancedP2cMax ();
   }
   else
   {
      GoToStandardP2cMax ();
   }
} /*** End of SendLnStandardNegativeAnswer ***/
/*************************************************************/
/*** builds a standart Limit Exceed GMLAN negative answer ***/
/************************************************************/
void SendLimitExceedNegativeAnswer (uint8_t NegativeResponseCode)
{
   (GetLnServiceData (1)) = (GetLnServiceData (0)) ;
   (GetLnServiceData (0)) = NegativeResponseServiceIdentifier;
   (GetLnServiceData (2)) = NegativeResponseCode;
   LnAnswer (5);

   if (NegativeResponseCode == RequestCorrectlyReceivedResponsePending)
   {
      GoToEnhancedP2cMax ();
   }
   else
   {
      GoToStandardP2cMax ();
   }
} /*** End of SendLnStandardNegativeAnswer ***/

/*****************************************/
/*** Builds a standart positive answer ***/
/*****************************************/
void SendLnStandardPositiveAnswer (register uint16_t MsgSize)
{
   (GetLnServiceData (0)) = (GetLnServiceData (0)) + PositiveResponseOffset; 
   LnAnswer (MsgSize);
} /*** End of SendLnStandardPositiveAnswer ***/

/***************************************************************************/
/*** Periodic Diagnostic Service Communication Update logic (every loop) ***/
/***************************************************************************/
void UpdateLnDiagSvCommunication (void)
{
   UpdateLnCommunicationTimingParameters ();
} /*** End of UpdateLnDiagSvCommunication ***/

/*************************************************************************/
/*** Initialize LnDiag application Communication level service handler ***/
/*************************************************************************/
void InitializeLnDiagSvCommunication (void)
{
   InitializeLnTransportLayer (); 
   InitializeLnDiagSvCommunicState ();
   InitializeLnNodeManagementState ();
} /*** End of InitializeLnDiagSvCommunication ***/

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     060215 cr       Created from TCL version (archive cvs partition op36cm)
*                  
* tci_pt3#2
*       080411 abh 6832 Added SendLimitExceedNegativeAnswer
* tci_pt3#2.1.1
*      080924 VP  7329 Changes to support Customized TP for Immobilizer.
* 2.0  100906   xxx  hdg  Implemented CAN OBD in MT22.1 paltform. 
*
******************************************************************************/
