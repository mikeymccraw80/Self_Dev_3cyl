#ifndef DCANCOMM_H
#define DCANCOMM_H
/*-------------------------------------------------------------------*/
/* filename -  DCANCOMM.H                                             */
/*                                                                   */
/*    This module is application layer of the Delco Electronics      */
/*    engine control s/w, where the Rx Tx functions and the          */
/*    communication state machine needed for GMLAN diagnostics       */
/*    services are definied.                                         */
/*                                                                   */
/*    LN stands for Local Network of GMLAN                           */
/*                                                                   */
/* Usage:                                                            */
/*                                                                   */
/* list of function(s):                                              */
/*  Proto:  AcknoledgeLnRequestWithoutResponse                       */
/*          InitializeLnDiagSvCommunication                          */
/*          UpdateLnDiagSvCommunication                              */
/*          SendLnStandardNegativeAnswer                             */
/*          SendLnUudtAnswer                                         */
/*          SendLnStandardPositiveAnswer                             */
/*          GetLnCommunicationEnabledState                           */
/*          GetLnRxCompleteWaitingAppToRespond   tell if service is  */
/*                                               completly received  */
/*          GetLnWaitingReqstRxStrtdApplCanStart if service not      */
/*                                            completly received yet */
/*          GetLnEcuSendingAnswer                                    */
/*          GoToEnhancedP2cMax                                       */
/*          LnEventFrameTransmitted                                  */
/*                                                                   */
/*  Inline:                                                          */
/*          GetLnDiagCommunicationActiveState                        */
/*                                                                   */
/*  Inline from transport layer (dcantran.h):                        */
/*          GetLnServiceData                                         */
/*          GetLnServiceDataByIndex                                  */
/*          GetLnServiceCurrentDataLength if service not completly   */
/*                                        received yet               */
/*          GetLnServiceDataLength                                   */
/*          GetLnServiceSourceCanId                                  */
/*          WriteLnMessageDataLength  if service completly received  */
/*          GetLnServReqMsgAddressingMode  (Functional or Phys.)     */
/*          GetLnIndexOfFirstFreeDataForWrite                        */
/*          GetLnServNbOfFreeBytesInRingBuffer                       */
/*          GetLnServNbOfUsedBytesInRingBuffer                       */
/*          RetrieveLnServNbBytesFromRingBuffer                      */
/*          StoreLnServNbBytesInRingBuffer                           */
/*                                                                   */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* DELPHI Delco Luxembourg C Engine Management Software              */
/* (c) Copyright DELPHI Delco Electronics System 2001                */
/*-------------------------------------------------------------------*/

 /****************************************************************************
 *
 * Current Module Info:
 * %full_name:      lux_pt1#1/incl/dcancomm.h/1 %
 * %date_created:   Wed Feb 15 18:20:47 2006 %
 * %version:        1 %
 * %derived_by:     c23cr %
 *
 *****************************************************************************/
/******************************************************************************
 *  Global Application Data Type Include Files
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
//#include "obdltype.h"
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcantran.h"

typedef 
  enum 
    { 
    DiagnosticComNotActive, 
    WaitingRequest, 
    WaitingReqstRxStrtdApplCanStart, 
/**************************************************************************************/
/*** The state WaitingReqstRxStrtdApplCanStart is needed to prevent the reception   ***/
/*** to be locked for ever by Control Flow WAIT.                                    ***/
/*** The state WaitingReqstRxStrtdApplCanStart is the same as WaitingReqst...       ***/
/*** but the application can already start to use the received data, even if the    ***/
/*** reception of all the data is not complete yet                                  ***/
/***                                                                                ***/
/*** How could the reception mechanism be locked in the state Control Flow Wait?    ***/
/*** The use of the ring buffer mechanism is needed for the case of a reception of  ***/
/*** a request with a data size too big to fit in the receive buffer.               ***/
/*** After the reception has started, the application must start to retrieve the    ***/
/*** received data bytes to release some bytes in the ring buffer. Otherwise, the   ***/
/*** receive buffer can be full and the tester transmission stopped by Control Flow ***/
/*** WAIT. The tester never send the end of the data of the current request.        ***/
/**************************************************************************************/
    RxCompleteWaitingAppToRespond,
    WaitingP2cMinBeforeAnswer, 
    SendingAnswer 
    } 
  LnDiagSvCommunicationStateType;

  
/*------------------------------------------------------------------------------------*/
/*--- definition of data needed for Application Messages Rx Tx Timing verification ---*/
/*------------------------------------------------------------------------------------*/
/*--- P2 = Time between tester request and ECU response ---*/
/*---      or two ECU responses                         ---*/
#define DefaultP2cMinInMs (0.0)
#define DefaultP2cMaxInMs (100.0)
#define EnhancedP2cMaxInMs (5000.0)
#define DiagComDeactivationTimeInSec (8.0)


/*--- CANOBD negative Response Return Code Definition (after $7F) ---*/
/*------------------------------------------------------------------*/
#define NegativeResponseServiceIdentifier           (0x7F)

#define ServiceIdNotSupported                       (0x11)
#define SubFunctionNotSupported_InvalidFormat   (0x12)
#define IncorrectMessageLength       (0x13)
#define ConditionsNotCorrectOrRequestSequenceError  (0x22)
#define RequestOutOfRange                           (0x31)
#define SecurityAccessDenied                    (0x33)
#define InvalidKey                                  (0x35)
#define ExceedNumberOfAttempts                      (0x36)
#define RequiredTimeDelayNotExpired                 (0x37)
#define RequestCorrectlyReceivedResponsePending     (0x78)
#define SchedulerFull                               (0x81)
#define VoltageRangeFault                           (0x83)
#define ProgramFailure                              (0x85)
#define ReadyForDownloadDtcSored                    (0x99)
#define DeviceControlLimitsExceeded                 (0xE3)
#define DefaultSession       (0x01)

/*-----------------*/
/*--- Responses ---*/
/*-----------------*/
#define PositiveResponseOffset                      (0x40)

/******************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/
extern LnDiagSvCommunicationStateType  LnDiagSvCommunicationState;

/**********************************************************************/
/*** Function prototype                                             ***/
/**********************************************************************/
void GoToEnhancedP2cMax (void);
//void GoToNewP2cMax (uint16_t NewP2cMaxInMs);
void LnSignalTranspErrorEvent (LnTrspTimeOutErrorType LnTrspTimeOutError);
void LnEventRxWaitingAppToEmptyRingBuffer (void);
void LnGoToWaitingRequest (void);

/**********************************************************************/
/*** Builds a standart negative answer                              ***/
/*** this routine will send the answer with Data [0] = $3F followed ***/
/*** by Data [1] = service request and by Data [1] = NegRespCode    ***/
/**********************************************************************/
void SendLnStandardNegativeAnswer (uint8_t NegRespCode);
void SendLimitExceedNegativeAnswer (uint8_t NegRespCode);
#if 0
/**********************************************************************/
/*** Sends an answer using UUDT frame                               ***/
/**********************************************************************/
void SendLnUudtAnswer (Can8DataBytesArrayType *Can8DataBytesArrayPtr,
                       uint8_t NbBytesToTransmit);
#endif
/**********************************************************************/
/*** Sends a standart positive answer                               ***/
/*** this routine will send the answer with Data [0] added by $40   ***/
/*** Data [1,2,...] shall be written prior to calling               ***/
/*** SendStandardPositiveAnswer.                                    ***/
/**********************************************************************/
void SendLnStandardPositiveAnswer (register uint16_t MsgSize);

void LnEventReceptionCompleteMsgWaiting (void);

void LnEventFrameTransmitted (void);

/************************************************************/
/*** Acknoledge Ln Request Without Response               ***/
/*** for functional request that do not send any response ***/
/************************************************************/
void AcknoledgeLnRequestWithoutResponse (void);
/*********************************************************************/
/*** PfrmDCAN_AckReqWithoutResponse                                ***/
/*********************************************************************/
#define PfrmDCAN_AckReqWithoutResponse() AcknoledgeLnRequestWithoutResponse()

/***************************/
/*** Function prototypes ***/
/***************************/
void UpdateLnDiagSvCommunication (void);
void InitializeLnDiagSvCommunication (void);

/*********************************************/
/*** Get CANOBD Communication Active Status ***/
/*********************************************/
INLINE bool GetLnCommunicationActiveState (void)
{
   return (bool) (LnDiagSvCommunicationState != DiagnosticComNotActive);
} /*** End of GetLnCommunicationActiveState ***/

/******************************************/
/*** GetLnRxCompleteWaitingAppToRespond ***/
/*********************************************************************************/
/*** returns TRUE if message is completly received and then if the application ***/
/*** must respond                                                              ***/
/*********************************************************************************/
INLINE bool GetLnRxCompleteWaitingAppToRespond (void)
{
   return (bool ) (LnDiagSvCommunicationState == RxCompleteWaitingAppToRespond);
} /*** End of GetLnRxCompleteWaitingAppToRespond ***/

/*******************************************/
/*** GetLnWaitingReqstRxStrtdApplCanStart ***/
/*************************************************************************************/
/*** returns TRUE if a message being received can be used used by application even ***/
/*** if not completly received                                                     ***/
/*************************************************************************************/
INLINE bool GetLnWaitingReqstRxStrtdApplCanStart (void)
{
   return (bool ) (LnDiagSvCommunicationState == WaitingReqstRxStrtdApplCanStart);
} /*** End of GetLnWaitingReqstRxStrtdApplCanStart ***/

/*****************************/
/*** GetLnEcuSendingAnswer ***/
/***************************************************/
/*** returns TRUE if currently sending an answer ***/
/***************************************************/
INLINE bool GetLnEcuSendingAnswer (void)
{
   return (bool ) (LnDiagSvCommunicationState == SendingAnswer);
} /*** End of GetLnEcuSendingAnswer ***/

/*****************************/
/*** GetLnEcuWaitingP2cMinBeforeAns ***/
/****************************************************/
/*** returns TRUE if currently waiting for P2 min ***/
/****************************************************/
INLINE bool GetLnEcuWaitingP2cMinBeforeAns (void)
{
   return (bool ) (LnDiagSvCommunicationState == WaitingP2cMinBeforeAnswer);
} /*** End of GetLnEcuSendingAnswer ***/




/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     060215 cr       Created from TCL version (archive cvs partition op36cm)
*
* 2     070629 abh 6023 Modified to implement non legislative services for J300
* tci_pt3#3
*       080411 abh 6832 Added SendLimitExceedNegativeAnswer
* 3.0  100906   xxx  hdg  Implemented CAN OBD in MT22.1 paltform. 
******************************************************************************/

#endif


