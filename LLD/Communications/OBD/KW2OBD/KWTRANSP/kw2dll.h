#ifndef KW2DLL_H
#define KW2DLL_H
/* ============================================================================ *\
 * kw2dll.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2dll.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:55 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 driver module.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "kw2type.h"
#include "t_base.h"
#include "obdlfsrv.h"

/*--- "COMMUNICATION LAYER" Service Id Requests
                              Implemented? --*/
#define sirStartCommunication                          (0x81) /* YES */
#define sirStopCommunication                           (0x82) /* YES */
#define sirAccessCommunicationParameters               (0x83) /* YES */

/*--- Responses ---*/
#define NegativeResponse                               (0x7F)
#define PositiveResponseOffset                         (0x40)
#define EscapeCode                                     (0x80)

/*--- Negative Response Codes ---*/
#define nrcNone                                        (0x00)

 /*--- for internal use ---*/
#define nrcGeneralReject                               (0x10)
#define nrcServiceNotSupported                         (0x11)
#define nrcSubFunctionNotSupported_InvalidFormat       (0x12)
#define nrcBusy_RepeatRequest                          (0x21)
#define nrcConditionsNotCorrect_RequestSequenceError   (0x22)
#define nrcRoutineNotComplete                          (0x23)
#define nrcRequestOutOfRange                           (0x31)
#define nrcSecurityAccessDenied_SecurityAccessRequested (0x33)
#define nrcInvalidKey                                  (0x35)
#define nrcExceedNumberOfAttempts                      (0x36)
#define nrcRequiredTimeDelayNotExpired                 (0x37)
#define nrcDownloadNotAccepted                         (0x40)
#define nrcImproperDownloadType                        (0x41)
#define nrcCanNotDownloadToSpecifiedAddress            (0x42)
#define nrcCanNotDownloadNumberOfBytesRequested        (0x43)
#define nrcUploadNotAccepted                           (0x50)
#define nrcImproperUploadType                          (0x51)
#define nrcCanNotUploadfromSpecifiedAddress            (0x52)
#define nrcCanNotUploadNumberOfBytesRequested          (0x53)
#define nrcTransferSuspended                           (0x71)
#define nrcTransferAborted                             (0x72)
#define nrcIllegalAddressInBlockTransfer               (0x74)
#define nrcIllegalByteCountInBlockTransfer             (0x75)
#define nrcIllegalBlockTransferType                    (0x76)
#define nrcBlockTransferDataChecksumError              (0x77)
#define nrcRequestCorrectlyReceived_ResponsePending    (0x78)
#define nrcIncorrectByteCountDuringBlockTransfer       (0x79)
#define nrcServiceNotSupportedInActiveDiagnosticMode   (0x80)

/*--- Positive Response Codes ---*/
#define prcSecurityAccessAllowed                       (0x34)


typedef enum
{
    k2sWaitingTIdleSynch,         /* Waiting for TIdle idle condition.*/
    k2sScanningHighToLowEdgeSynch,/*Awaiting idles followed by 1 brk.*/
    k2sWaiting25msLowSynch,       /* Waiting 3 or 4 RTI with break */
                                  /* followed by one RTI with idle.*/
    k2sWaiting25msHighSynch,      /* Waiting 1 RTI with idle.*/
    k2sWaitingInitializing,
    k2sLostCommunication,
    k2sAwaitingMessage,           /* Scanning a byte within
                                     TimoutDelay.*/
    k2sReceivingMessage,          /* Schedule message reception.*/
    k2sExecuteService,            /* Execute low level services and
                                     warn*/
                                  /*   application for others.*/
    k2sWaitingAppLvlServiceExec,  /* Waiting for app.level service
                                     exec*/
    k2sWaitingP2MinBeforeAnswer,  /* Waiting minimum P2 Time just
                                     before*/
    k2sWaitingP3MinBeforeSend,
                                  /*   sending the answer.*/
    k2sWaitingP4MinBeforeSend,
    k2sSendingMessage,            /* Schedule message transmission.*/
    k2sScanningLowToHighEdge,     /* Awaiting 4 or less RTI with break*/
                                  /*   followed by one RTI with idle.*/
    k2sErrorRead                  /* Handle errors
                                                (goto wait new msg.).*/
}Kw2000StateType;


typedef enum
{
    mrsWaitingFormat,
    mrsWaitingTgtAddr,
    mrsWaitingSrcAddr,
    mrsWaitingLength,
    mrsLoadingData,
    mrsWaitingCheckSum
}Kw2MsgRxStateType;


typedef enum
{
    ktsSendingFormat,
    ktsSendingTgtAddr,
    ktsSendingSrcAddr,
    ktsSendingLength,
    ktsSendingData,
    ktsSendingCheckSum
}Kw2MsgTxStateType;

typedef enum
{
    KW2000_Tester,
    KW2000_Responder
}KW2000CommunicationType;

typedef uint8_t   Timer0p5msInMs;
typedef uint16_t  Timer0p5msInMs_W;

#define Prec_Timer0p5msInMs (0)
#define Max_Timer0p5msInMs  (255)

typedef uint8_t   Timer25msInMs;
typedef uint8_t   Timer25msInMs_W;

#define Prec_Timer25msInMs (25)
#define Max_Timer25msInMs  (255)
#define Max_Timer25msInMs_W  (65535)

typedef uint8_t   Timer250msInMs;
typedef uint16_t  Timer250msInMs_W;

#define Prec_Timer250msInMs (250)
#define Max_Timer250msInMs  (255)
#define Max_Timer250msInMs_W  (65535)


#define MaxiServiceDataSize (255)

/*--- General Kw2000 communication constants ---*/
#define Kw2000BaudRate   (10400)

/* This defines the max number of byte that can loaded into the
   Trans/Rec Buffer.
 */
#define CyMaxMemSize  (MaxiServiceDataSize - 1)

/* Define for immobilizer */
#define SyIMM_SER_ID_LOCATION   (0)

/*************************************************************/
#define KB1 (0xEF)
/* KB1 is the low byte of the key bytes described in "Keyword
   Protocol 2000 - Part 2: Data Link Layer", section 5.1.5.1.

   P   == 1 => parity bit is on,
   TP1 == 1 => normal timing parameter set,
   TP0 == 0 => extended timing parameter NOT set,
   HB1 == 1 => target/source address in header supported,
   HB0 == 1 => 1 byte header supported,
   AL1 == 1 => additional length byte supported,
   AL0 == 1 => length information in format byte supported
*/
#define KB2 (0x8F)
#define ReadComParamLimits       (0x00)
#define SetComParamToDefaultVals (0x01)
#define ReadComParamCurrentVals  (0x02)
#define SetComParamToNewVals     (0x03)

#define P2MinLimit      (0)
#define P2MaxLimit      (Max_Timer25msInMs)
#define P3MinLimit      (0)
#define P3MaxLimit      (Max_Timer250msInMs)
#define P4MinLimit      (0)
#define P2MaxBkpt       (0xF0)

#define P3MaxToP2MaxConv (10) /* Conversion factor for P3Max to P2Max:
                                 (250 / 25) */

#define init_Tx_Timer ( 2)

/*--- General Kw2000 communication constants ---*/
#define Kw2000BaudRate   (10400)

/*--- message formats ---*/
#define mfNoAddr    (0x00)
#define mfCARB      (0x40)
#define mfPhysAddr  (0x80)
#define mfFunctAddr (0xC0)
#define mfAuthenticationImmoAddr  (0x05)
#define mfAuthenticationECMAddr  (0x06)

#define k2mFmt(x) (x & 0xC0)
#define k2mLen(x) (x & 0x3F)

#define P1Min (0)   /*--- in ms ---*/
#define P1Max (2)  /*--- in ms ---*/

#define CySiemens_ImmoTargetAddress (0xC1)
/***************************************************************/

/*********************************************************************/
/*                  GLOBAL VARIABLES DECLARATIONS                    */
/*********************************************************************/

extern uint32_t            BaudRateValueSrv10 ;
extern bool                BaudRateChangedSrv10 ;

extern uint8_t             RxServiceData [MaxiServiceDataSize];
extern uint8_t             TxServiceData [MaxiServiceDataSize];
extern uint8_t             TxMsgDataLength;
extern uint8_t             RxMsgDataLength;
extern Kw2000StateType     Kw2000State;
extern Kw2MsgRxStateType   Kw2MsgRxState;
extern Kw2MsgTxStateType   Kw2MsgTxState;
extern uint8_t             RxSourceAddress;
extern bool                CommunicationEstablishedState;
extern uint8_t              DataByte;
extern KW2000CommunicationType       KW2000CommuState;


/*  This flag is set to true if multiple messages are to be transmitted. */
extern uint8_t             VyMultiRespInProgress;

extern bool                VbECUResetPending ;

/* exported for immobilizer DLL funtions */
extern uint8_t             TxFormatByte;
extern uint8_t             TxTargetAddress;
extern uint8_t             TxSourceAddress;
extern uint8_t             VyMyPhysicalAddr ;

extern Timer25msInMs       Saved_P2Max;

extern WORD              P1Timout;
extern WORD              P2MinTimer;
extern WORD              P3MinTimer;
extern WORD              P4Timout;
extern WORD              P2MinWL;
extern WORD              P2MaxWL; /* 0xFFFF == infinite */
extern WORD              P3MinWL;
extern WORD              P3MaxWL; /* 0xFFFF == infinite */
extern WORD              P4MinWL;
extern uint8_t           RxFormatByte;
extern BYTE              RxFormatByte_Responder;
extern BYTE              RxSourceAddress_Responder;
extern Timer0p5msInMs P2Min;
extern bool          SbPosResponsePending;
extern bool                 NewTiming;
extern Timer0p5msInMs       NewP4Min;
extern Timer250msInMs       NewP3Max;
extern Timer0p5msInMs       NewP3Min;
extern Timer25msInMs        NewP2Max;
extern Timer0p5msInMs       NewP2Min;
extern Timer0p5msInMs       P4Min;
extern Timer250msInMs       P3Max;
extern Timer0p5msInMs       P3Min;
extern Timer25msInMs         P2Max;
extern bool                 FunctionalAddressActive;
extern uint8_t              RxCalcCheckSum;
extern uint8_t              RxDataIndex;
extern uint8_t              RxTargetAddress;
/*********************************************************************/
/*                  EXTERN FUNCTION DECLARATIONS                     */
/*********************************************************************/

/*********************************************************************/
/*** Serial communication Receive ISR                              ***/
/*********************************************************************/
FAR_COS extern void SerialcomReceiveInt (void); /*<<< HANDLER >>>*/


/*********************************************************************/
/*** Serial communication Transmit ISR                             ***/
/*********************************************************************/
FAR_COS extern void SerialcomTransmitInt (void); /*<<< HANDLER >>>*/

/*********************************************************************/
/*** Periodic Keyword 2000 VIO logic (@ 7.81 ms)                   ***/
/*********************************************************************/
extern void UpdateKeyword2000VIO (void);

/************************************************/
/*** Initialize Kw2000 Virtual I.O:           ***/
/*** Set Serial parameters (baud rate, parity,***/
/*** char.length, Stopbits,...), reset        ***/
/*** kw2000 serial com. layer state machine.  ***/
/************************************************/
extern FAR_COS void InitializeKw2000VIO (void);
extern FAR_COS void ReceivingMessageKw2000State (void);
extern FAR_COS void SendKw2000ByteToSerial ( void );
extern FAR_COS void GoToErrorReadK2State (void);

/*********************************************************************/
/*** Builds a standard kw2000 negative answer                      ***/
/*********************************************************************/
extern FAR_COS  void KW2K_SendStandardNegativeAnswer (uint8_t NegRespCode);


/********************************************************************/
/*** Builds a standard kw2000 positive answer                     ***/
/********************************************************************/
extern FAR_COS void KW2K_SendStandardPositiveAnswer (uint8_t MsgSize);

/********************************************************************/
/*** Builds a standard kw2000 Escape Code                         ***/
/********************************************************************/
extern void SendEscapeCode (uint8_t MsgSize);

/***********************************************/
/*** Copy New Timing parameters to current.  ***/
/***********************************************/
extern void CopyNewTimingParametersToCurrents (void);

/*********************************************************************/
/*** Set Kw2000 state machine to ExecuteService                    ***/
/*********************************************************************/
/* It was changed to gobal for immobilizer */

extern void GoToExecuteServiceK2State (void);

/*********************************************************************/
/*** Initialize Kw2000 Timing Parameters to given values.          ***/
/*********************************************************************/
extern void SetDLLTimingsParameters (Timer0p5msInMs ,
                                     Timer25msInMs  ,
                                     Timer0p5msInMs ,
                                     Timer250msInMs ,
                                     Timer0p5msInMs  );

extern void SCI0ReceiverReset (void) ;

/*********************************************************************/
/*** Sests the P2Max value to the P3Max value.                     ***/
/*********************************************************************/
extern void SetP2TimingsForPendingProcess (void) ;

/*********************************************************************/
/*** Set new timing parameter P2Max (at next message reception).   ***/
/*********************************************************************/

extern void SetNewP2Max (Timer25msInMs NextP2Max) ;

/*==================================================================*/
/*   Exported functions for immobilizer rountines                   */
/*                                                                  */
/*==================================================================*/
void GoToSendingMessageK2State (void);
void GoToAwaitingMessageK2State (bool AfterFastSynchro);
void GoToReceivingMessageK2State (void);
extern FAR_COS void SetTimingParameterToDefault (void);

extern FAR_COS void WaitingP3MinBeforeSendRequest (void);
extern FAR_COS void GoToWaitingInitializingOrP3MinState(void);
extern FAR_COS void WaitingP4MinBeforeSendRequest(void);
extern FAR_COS void GoToLostCommunicationState(void);
extern FAR_COS void GoToWaitingP3MinBeforeSendingRequest  (void);
extern FAR_COS void GoToWaitingP4MinBeforeSendingRequest(void);
extern FAR_COS void CheckKW2000LineState(void);
extern FAR_COS void BuildKw2000Request (BYTE TxMsgSize);

/*********************************************************************/
/*                  INLINE FUNCTION DECLARATIONS                     */
/*********************************************************************/

/*********************************************************************/
/***  Return the multiple response  flag value                     ***/
/*********************************************************************/
#define GetMultiRespInProgress()                ((uint8_t) VyMultiRespInProgress)

/*********************************************************************/
/***  Set multiple response flag                                   ***/
/*********************************************************************/
#define WrtMultiRespInProgress(lyMsgResponce)   (VyMultiRespInProgress = (uint8_t) lyMsgResponce)

/*********************************************************************/
/***   return the transmit buffer addr. pointer                    ***/
/*********************************************************************/
#define GetWrtbufferAddr()                      ((uint8_t*)  &TxServiceData[0])

/*********************************************************************/
/***   return the Receive buffer addr. pointer                    ***/
/*********************************************************************/
#define GetKw2000ServiceDataAddr()              ((uint8_t*) &RxServiceData[0])

/*********************************************************************/
/***  write TxFormatByte                                           ***/
/*********************************************************************/
#define WrtKw2000TxFormatByte(lyTxFormatByte)   (TxFormatByte = lyTxFormatByte)

/*********************************************************************/
/***  write TxSourceAddress                                        ***/
/*********************************************************************/
#define WrtKw2000TxTargetAddress(lyTxTargetAddress)     (TxTargetAddress = lyTxTargetAddress)

/*********************************************************************/
/***  write TxSourceAddress                                        ***/
/*********************************************************************/
#define WrtKw2000TxSourceAddress(lyTxSourceAddress)     (TxSourceAddress = lyTxSourceAddress)

/*********************************************************************/
/***  write TxP2MinTimer                                           ***/
/*********************************************************************/
#define WrtKw2000P2MinTimer(lyP2MinTimer)       (P2MinTimer = lyP2MinTimer)

/*********************************************************************/
/*** Read a data in the Recieved Data Buffer                       ***/
/*********************************************************************/
#define GetKw2000ServiceData(location)          ((uint8_t) RxServiceData[location])

/*********************************************************************/
/*** Load a data to a location of  the transmit data buffer        ***/
/*********************************************************************/
#define WrtKw2000ServiceData(data,location)     (TxServiceData[location] = data)

/*********************************************************************/
/*** Keyword 2000 Answer still being sent.                         ***/
/*********************************************************************/
#define Keyword2000AnswerStillBeingSent()       ((bool) ((Kw2000State == k2sSendingMessage) || \
                                                 (Kw2000State == k2sWaitingP2MinBeforeAnswer)))

/*********************************************************************/
/*** Get Communication Established Status.                         ***/
/*********************************************************************/
#define  KW2K_GetCommunicationActiveState()      ((bool)CommunicationEstablishedState)

/*********************************************************************/
/*** Application Level Keyword 2000 Service is pending.            ***/
/*********************************************************************/
#define ApplicationLevelKeyword2000ServicePending()     ((bool) (Kw2000State == k2sWaitingAppLvlServiceExec))

/*********************************************************************/
/*** Application Level Keyword 2000 Receive is pending.            ***/
/*********************************************************************/
 #define Keyword2000ReceivePending()            ((bool)   (Kw2000State >= k2sReceivingMessage) )

/*********************************************************************/
/*** Get Keyword 2000 Service Data field Length (in bytes)         ***/
/*********************************************************************/
#define GetKeyword2000ServiceDataLength()       ((uint8_t) RxMsgDataLength)

/*********************************************************************/
/*** Get the saved P2Max value.                                    ***/
/*********************************************************************/
#define GetSavedP2Max()                         ((Timer25msInMs) Saved_P2Max)

/*********************************************************************/
/*** ------------IMMOBILIZER DEFINITIONS----------------           ***/
/*********************************************************************/

/*********************************************************************/
/*** Initialize the recieve buffer with the given service Id.      ***/
/*********************************************************************/

#define InitializeReceiveBufferWithId()         (RxServiceData[SyIMM_SER_ID_LOCATION] = ImmServiceId)

/*********************************************************************/
/* Sets the communication established state flag to the boolean value*/
/*********************************************************************/
#define SetCommunicationEstablishedFlag(FlagValue)      (CommunicationEstablishedState = FlagValue)

/*********************************************************************/
/* Sets the Keyword ID                                               */
/*********************************************************************/
#define SetMyPhysicalAddr(MyAddr)               (VyMyPhysicalAddr = MyAddr)

/*********************************************************************/
/* Sets the baud rate to the new value.                              */
/*********************************************************************/
#define SetBaudRateValue(NewBaud)               (BaudRateValueSrv10 = NewBaud)

/*********************************************************************/
/* Sets the value of the boolean variable.                           */
/*********************************************************************/
#define SetBaudRateChangedFlag(Status)          (BaudRateChangedSrv10 = Status)

/*********************************************************************/
/***    Get the ECU Reset Pending flag                             ***/
/*********************************************************************/
#define GetECUResetPending()                    ((bool) VbECUResetPending)

/*********************************************************************/
/***    Set the ECU Reset Pending flag                             ***/
/*********************************************************************/
#define SetECUResetPending(LyECUReset)          (VbECUResetPending = LyECUReset)



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
 *   - Changed to support KWP2000 master mode for generic immo
 *
 * 22/11/07	   Yu Runwu    mt20u2#194
 * + Implement CJAE Immobilizer and Remove Old Immobilizer
 *   - Add CJAE immobilizer logic on KWP2000. 
\* ============================================================================ */
#endif
