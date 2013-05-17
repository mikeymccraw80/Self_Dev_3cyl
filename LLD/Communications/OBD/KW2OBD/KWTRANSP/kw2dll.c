/* ============================================================================ *\
 * kw2dll.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2dll.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:49 PM
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
#incldue "dd_sci_interface.h"
#include "kw2dllcf.h"
#include "kw2dll.h"
#include "kw2api.h"
#include "obdlfsrv.h"
// #include "immo.h"
// #include "immo_exec.h"


/* local function prototype */
static void BuildKw2000Answer (uint8_t);
static void GoToErrorReadK2State (void);
static void SendKw2000ByteToSerial (void);
static void GoToLoadingDataMRState (void);
static void UpdateP2MinWaitingLoop (void);
static void UpdateP2MaxWaitingLoop (void);
static void UpdateP3MaxWaitingLoop (void);
static void InitializeKW2000InputBuffer (void);
static void GoToWaitingTIdleSynchK2State (uint8_t);
static void GoToWaitingP2MinBeforeAnswerK2State (void);
static void GoToWaiting25msLowSynchK2State (void);
static void GoToWaiting25msHighSynchK2State (void);
static void GoToScanningHighToLowEdgeSynchK2State (void);
static void GoToWaitingAppLvlServiceExecK2State (void);
static void SendNowStandardNegativeAnswer (uint8_t);
static void PutDataInKw2000InputBuffer (uint8_t DataIn);
static bool GetDataFromKw2000InputBuffer (uint8_t*);
static bool SerialEventReceived (void);
static void WaitingTIdleSynchKw2000State (void);
static void ScanningHighToLowEdgeSynchKw2000State (void);
static void Waiting25msLowSynchKw2000State (void);
static void Waiting25msHighSynchKw2000State (void);
static void AwaitingMessageKw2000State (void);
static void ExecuteServiceKw2000State (void);
static void WaitingAppLvlServiceExecKw2000State (void);
static void WaitingP2MinBeforeAnswerKw2000State (void);
static void SendingMessageKw2000State (void);
static void ErrorReadKw2000State (void);

/* local private variables */
static const sci_bus_t * kline = &scib;
static uint8_t       EventCounter;

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

/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */

uint32_t             BaudRateValueSrv10 ;
bool                 BaudRateChangedSrv10 ;
Kw2000StateType      Kw2000State;
Kw2MsgRxStateType    Kw2MsgRxState;
Kw2MsgTxStateType    Kw2MsgTxState;
uint8_t              IdleTimer;
uint8_t              TIdle;
uint16_t             TimerBeforeNewMsgRx; /* 0xFFFF == infinite */
uint16_t             TimerBeforeAnswerTx; /* 0xFFFF == infinite */
WORD              P1Timout;
WORD              P2MinTimer;
WORD              P3MinTimer;
WORD              P4Timout;
WORD              P2MinWL;
WORD              P2MaxWL; /* 0xFFFF == infinite */
WORD              P3MinWL;
WORD              P3MaxWL; /* 0xFFFF == infinite */
WORD              P4MinWL;
bool                 NewTiming;
bool                 AfterFastSynchroFlag;
uint8_t              PendingNegativeAnswer;
uint8_t              VyMyPhysicalAddr ;
bool                 VbECUResetPending ;

/* WARNING: The size of the buffer should be high enough in the     */
/* production version to avoid a buffer full (with DEBUG_OFF, there */
/* is no checking logic on the buffer overflow!).                   */


uint8_t              KW2000InputBuffer [KW2000InputBufferSize];
uint8_t              KW2000InputBufferInPointer;
uint8_t              KW2000InputBufferOutPointer;

bool                 CommunicationEstablishedState;

/* State information for a receive message. */
uint8_t              RxFormatByte;
uint8_t              RxTargetAddress;
uint8_t              RxSourceAddress;
uint8_t              RxMsgDataLength;
uint8_t              RxCalcCheckSum;
uint8_t              RxDataIndex;
uint8_t              RxServiceData [MaxiServiceDataSize];

/* State information for a transmit message. */
uint8_t              TxFormatByte;
uint8_t              TxTargetAddress;
uint8_t              TxSourceAddress;
uint8_t              TxMsgDataLength;
uint8_t              TxCalcCheckSum;
uint8_t              TxDataIndex;
uint8_t              TxServiceData [MaxiServiceDataSize];

/*  This flag is set to true if multiple messages are to be
    transmitted.   */
uint8_t              VyMultiRespInProgress;

bool                 EchoErrorOrBreakOccured;
uint16_t             SlowTableIdx;

uint8_t              DataByte ;

bool          SbPosResponsePending;

BYTE                 RxFormatByte_Responder;
BYTE                 RxSourceAddress_Responder;

/*--- P2 = Time between tester request and ECU response ---*/
/*---      or two ECU responses                         ---*/
Timer0p5msInMs       P2Min;
Timer0p5msInMs       NewP2Min;
Timer25msInMs        P2Max;
Timer25msInMs        NewP2Max; /*--- 0xFF == infinite ---*/
/*--- P3 = Time between ECU response and new tester request ---*/
Timer0p5msInMs       P3Min;
Timer0p5msInMs       NewP3Min;
Timer250msInMs       P3Max;
Timer250msInMs       NewP3Max; /*--- 0xFF == infinite ---*/
/*--- P4 = Inter byte time for tester request ---*/
Timer0p5msInMs       P4Min;
Timer0p5msInMs       NewP4Min;

Timer25msInMs        Saved_P2Max;
bool                 FunctionalAddressActive ;
KW2000CommunicationType       KW2000CommuState;



const uint8_t  Siemens_KW2_Start_Communication_KB1 = 0xEF;
const uint8_t  Siemens_KW2_Start_Communication_KB2 = 0x8F;

//VehicleInformation scnVehInfo;
//ECU_Identification scnEcuId;
/* ============================================================================ *\
 * Local Macro.
\* ============================================================================ */

/*--- P1 = Inter byte time for ECU response ---*/
#define P1Min (0)   /*--- in ms ---*/
#define P1Max (2)  /*--- in ms ---*/

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



/* Exported for immobilizer */

/*********************************************************************/
/*** Initialize Kw2000 Timing Parameters to given values.          ***/
/*********************************************************************/
/* Added for immobilizer.                                            */

void SetDLLTimingsParameters (Timer0p5msInMs ImmP2MinVal,
                              Timer25msInMs  ImmP2MaxVal,
                              Timer0p5msInMs ImmP3MinVal,
                              Timer250msInMs ImmP3MaxVal,
                              Timer0p5msInMs ImmP4MinVal )
{
	NewP2Min =  ImmP2MinVal;
	NewP2Max =  ImmP2MaxVal;
	NewP3Min =  ImmP3MinVal;
	NewP3Max =  ImmP3MaxVal;
	NewP4Min =  ImmP4MinVal;
	NewTiming = true;
}

/***********************************************/
/*** Initialize Kw2000 Timing Parameters.    ***/
/***********************************************/

void SetTimingParameterToDefault (void)
{
      NewP2Min =  DefaultP2Min;
      NewP2Max =  DefaultP2Max;
      NewP3Min =  DefaultP3Min;
      NewP3Max =  DefaultP3Max;
      NewP4Min =  DefaultP4Min;
   NewTiming = true;
} /*** End of SetTimingParameterToDefault ***/

/*********************************************************************/
/*** Sests the P2Max value to the P3Max value.                     ***/
/*********************************************************************/
void SetP2TimingsForPendingProcess (void)
{
  uint16_t p2max25ms;

  /* Save P2 timing parameter and temporarily set to P3Max. */
  Saved_P2Max = P2Max ;
  p2max25ms = ( P3Max * P3MaxToP2MaxConv );
  if ( P2MaxBkpt < p2max25ms ) {
    p2max25ms = (p2max25ms/256) + P2MaxBkpt;
  }
  NewP2Max = (Timer25msInMs) p2max25ms;
  NewTiming = true;
  CopyNewTimingParametersToCurrents();

  /* Set this variable to indicate whether to go to wait state */
  PendingNegativeAnswer = nrcRequestCorrectlyReceived_ResponsePending;
}

/*********************************************************************/
/*** Set new timing parameter P2Max (at next message reception).   ***/
/*********************************************************************/

void SetNewP2Max (Timer25msInMs NextP2Max)
{
	NewP2Max = NextP2Max;
	NewTiming = true;
} /*** End of SetNewP2Max ***/

/*********************************************************************/
/*** Update P2Min Waiting Loop.                                    ***/
/*********************************************************************/

static void UpdateP2MinWaitingLoop (void)
{
	P2MinWL = P2MinLoopCountVal(P2Min) ;
} /*** End of UpdateP2MinWaitingLoop ***/


/*********************************************************************/
/*** Update P2Max Waiting Loop.                                    ***/
/*********************************************************************/

static void UpdateP2MaxWaitingLoop (void)
{
	uint16_t p2max25ms = P2Max;
	if ( P2MaxBkpt < p2max25ms )
	{
		p2max25ms = (p2max25ms - P2MaxBkpt) * 256;
	}
	P2MaxWL = p2max25ms * P2MaxLoopCountVal ;
} /*** End of UpdateP2MaxWaitingLoop ***/

/*********************************************************************/
/*** Update P3Min Waiting Loop.                                    ***/
/*********************************************************************/

static void UpdateP3MinWaitingLoop (void)
{
	/*--- (P3MinWL >= (P3Min + 1ms) /2/ 7.81ms) ---*/
	P3MinWL = ((P3Min + 15) / 16);
} /*** End of UpdateP3MinWaitingLoop ***/

/*********************************************************************/
/*** Update P3Max Waiting Loop.                                    ***/
/*********************************************************************/

static void UpdateP3MaxWaitingLoop (void)
{
	/*--- P3MaxWL >= (P3Max + 1ms / 7.81ms) ---*/
	Timer250msInMs_W DW;

	if (P3Max == Max_Timer250msInMs)
	/*--- P3Max infinite ---*/
	{
		P3MaxWL = Max_Timer250msInMs_W;
	}
	else
	{
		DW = (Timer250msInMs_W) P3Max;
		P3MaxWL = (DW * P3MaxLoopCountVal) ;
		/* (P3Max) * 32 */
	}
} /*** End of UpdateP3MaxWaitingLoop ***/

/*********************************************************************/
/*** Update P4Min Waiting Loop.                                    ***/
/*********************************************************************/

static void UpdateP4MinWaitingLoop (void)

  {
  /*--- (P4MinWL >= (P4Min + 1ms) /2/ 7.81ms) ---*/
  P4MinWL = ((P4Min + 15) / 16);
  } /*** End of UpdateP4MinWaitingLoop ***/

/*********************************************************************/
/*** Change kw2000 state to waiting P3min.                                    ***/
/*********************************************************************/

void GoToWaitingP3MinBeforeSendingRequest  (void)

  {
  Kw2000State = k2sWaitingP3MinBeforeSend;
  } /*** End of GoToWaitingP3MinBeforeSendingRequest ***/

/*********************************************************************/
/*** Change kw2000 state to waiting P4min.                                    ***/
/*********************************************************************/

void GoToWaitingP4MinBeforeSendingRequest(void)

{
   Kw2000State=k2sWaitingP4MinBeforeSend;
}

/*********************************************************************/
/*** Change kw2000 state to lost communication.                                    ***/
/*********************************************************************/

void  GoToLostCommunicationState(void)

{
   Kw2000State=k2sLostCommunication;
   ImmoServiceState=NoResponse;
} /*** End of GoToLostCommunicationState ***/


/***********************************************/
/*** Copy New Timing parameters to current.  ***/
/***********************************************/
/* Changed to global for immobilizer */

void CopyNewTimingParametersToCurrents (void)

{
   P2Min = NewP2Min;
   P2Max = NewP2Max;
   P3Min = NewP3Min;
   P3Max = NewP3Max;
   P4Min = NewP4Min;
   UpdateP2MinWaitingLoop();
   UpdateP2MaxWaitingLoop();
   UpdateP3MinWaitingLoop();
   UpdateP3MaxWaitingLoop();
   UpdateP4MinWaitingLoop();
   NewTiming = false;
} /*** End of CopyNewTimingParametersToCurrents ***/

static void InitializeKW2000InputBuffer (void)

  {
  KW2000InputBufferInPointer = 0;
  KW2000InputBufferOutPointer = 0;
  } /*** End of InitializeKW2000InputBuffer ***/


/*********************************************************************/
/*** Set Kw2000 state machine to WaitingTIdleSynch                 ***/
/*********************************************************************/

static void GoToWaitingTIdleSynchK2State (uint8_t NewTIdle)
{
	TIdle = NewTIdle;
	CommunicationEstablishedState = false;
	kline->reset();
	// SCI0ReceiverReset ();
	IdleTimer = 0;
	Kw2000State = k2sWaitingTIdleSynch;
	/* Disable the receive interrupt. Enable it
	 after fast initialization.
	 */
	kline->RxIntDisable();
	// EnableSCI0ReceiverInterrupt ( false );

} /*** End of GoToWaitingTIdleSynchK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to ErrorRead                         ***/
/*********************************************************************/

void GoToErrorReadK2State (void)
{
	kline->RxIntDisable();
	// EnableSCI0ReceiverInterrupt(false);
	// SCI0ReceiverReset ();
	kline->reset();
	Kw2000State = k2sErrorRead;
} /*** End of GoToErrorReadK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to WaitingP2MinBeforeAnswer          ***/
/*********************************************************************/

static void GoToWaitingP2MinBeforeAnswerK2State (void)
{
	Kw2000State = k2sWaitingP2MinBeforeAnswer;
} /*** End of GoToWaitingP2MinBeforeAnswerK2State ***/

/*********************************************************************/
/*** Set Kw2000 state machine to AwaitingMessage                   ***/
/*********************************************************************/

void GoToAwaitingMessageK2State (bool AfterFastSynchro)
{
	AfterFastSynchroFlag = AfterFastSynchro;
	TimerBeforeNewMsgRx = 0;
	if (NewTiming) {
		CopyNewTimingParametersToCurrents ();
	}
	Kw2000State = k2sAwaitingMessage;
	InitializeKW2000InputBuffer ();
	// EnableSCI0ReceiverInterrupt (true);
	kline->RxIntEnable();
} /*** End of GoToAwaitingMessageK2State ***/


/*********************************************************************/
/*** Send Byte To Serial transmitter buffer and add it to checksum ***/
/*********************************************************************/

void SendKw2000ByteToSerial(void)
{
	/* If the line is busy when transmitting format byte,
	reset the time and go to the waiting state.
	If the main keyword is not executing this check is
	not applied.
	*/
	if ((Kw2MsgTxState == ktsSendingFormat) &&
		// (SCI0ReceiverActiveDetected ())    &&
		(kline->GetActiveFlag())    &&
		(IfKeywordLogicIsActive ()))
	{
		if (KW2000CommuState == KW2000_Responder) {
			P2MinTimer = 0 ;
			GoToWaitingP2MinBeforeAnswerK2State();
		}
	}
	else
	{

			kline->write(DataByte);
			// SCI0_WriteSCITransmitterDataBufferRegister(DataByte);
			/*--- This addition MUST be done after the Write    ---*/
			/*--- for the case the checksum is sent itself.     ---*/
			TxCalcCheckSum += DataByte;
		
	}
} /*** End of SendKw2000ByteToSCI ***/


/*********************************************************************/
/*** Set Kw2000 state machine to SendingMessage                    ***/
/*********************************************************************/

void GoToSendingMessageK2State (void)
{
	Kw2000State = k2sSendingMessage;
	Kw2MsgTxState = ktsSendingFormat;
	TxCalcCheckSum = 0;
	DataByte = TxFormatByte ;
	SendKw2000ByteToSerial() ;
} /*** End of GoToSendingMessageK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to Waiting25msLowSynch               ***/
/*********************************************************************/

static void GoToWaiting25msLowSynchK2State (void)
{
	// SCI0ReceiverReset();
	kline->reset();
	EventCounter = 0;
	Kw2000State = k2sWaiting25msLowSynch;
} /*** End of GoToWaiting25msLowSynchK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to Waiting25msHighSynch              ***/
/*********************************************************************/

static void GoToWaiting25msHighSynchK2State (void)
{
	// SCI0ReceiverReset ();
	kline->reset();
	EventCounter = 0;
	Kw2000State = k2sWaiting25msHighSynch;
} /*** End of GoToWaiting25msHighSynchK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to ReceivingMessage                  ***/
/*********************************************************************/

void GoToReceivingMessageK2State (void)

  {
  if (KW2000_Responder==KW2000CommuState) P4Timout = 0;
  Kw2MsgRxState = mrsWaitingFormat;
  Kw2000State = k2sReceivingMessage;
  } /*** End of GoToReceivingMessageK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to ScanningHighToLowEdgeSynch        ***/
/*********************************************************************/

static void GoToScanningHighToLowEdgeSynchK2State (void)

  {
  Kw2000State = k2sScanningHighToLowEdgeSynch;
  } /*** End of GoToScanningHighToLowEdgeSynchK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to ExecuteService                    ***/
/*********************************************************************/
/* It was changed to gobal for immobilizer */

void GoToExecuteServiceK2State (void)

  {
  Kw2000State = k2sExecuteService;
  TimerBeforeAnswerTx = init_Tx_Timer;
  OBD_ByKW2000();
  } /*** End of GoToExecuteServiceK2State ***/


/*********************************************************************/
/*** Set Kw2000 state machine to WaitingAppLvlServiceExec          ***/
/*********************************************************************/

static void GoToWaitingAppLvlServiceExecK2State (void)

  {
  PendingNegativeAnswer = nrcNone;
  Kw2000State = k2sWaitingAppLvlServiceExec;
  } /*** End of GoToWaitingAppLvlServiceExecK2State ***/

/*********************************************************************/
/*** Build Keyword 2000 answer (and preset sending process).       ***/
/*********************************************************************/

void BuildKw2000Answer (uint8_t TxMsgSize)
{
	if (k2mFmt (RxFormatByte) == mfFunctAddr)
		/* A received message may use functional addressing, but we use
		 physical addressing for the response transmitted back. */
		TxFormatByte = mfPhysAddr;
	else
		TxFormatByte = k2mFmt (RxFormatByte);

	if (k2mLen (TxMsgSize) == TxMsgSize) {
		/* The size will fit in the length field of the transmit
		format byte. */
		TxFormatByte |= TxMsgSize;
	}

	TxMsgDataLength = TxMsgSize;
	if ((RxFormatByte & mfPhysAddr) || (RxFormatByte & mfFunctAddr)) {
		TxTargetAddress = RxSourceAddress;
		TxSourceAddress = MyPhysicalAddr;
	} else {
		TxTargetAddress = 0;
		TxSourceAddress = 0;
	}

	if (P2MinTimer < P2MinWL) {
		GoToWaitingP2MinBeforeAnswerK2State ();
	} else {
		GoToSendingMessageK2State ();
	}
} /*** End of BuildKw2000Answer ***/


/*********************************************************************/
/*** Immediatly builds a standard kw2000 negative answer           ***/
/*********************************************************************/

static void SendNowStandardNegativeAnswer (uint8_t NegRespCode)
{
	TxServiceData [1] = RxServiceData [0];
	TxServiceData [0] = NegativeResponse;
	TxServiceData [2] = NegRespCode;
	BuildKw2000Answer (3);
} /*** End of SendNowStandardNegativeAnswer ***/


/*********************************************************************/
/*** Builds a standard kw2000 negative answer                      ***/
/*********************************************************************/

void KW2K_SendStandardNegativeAnswer (uint8_t NegRespCode)
{
	if ((NegRespCode == nrcServiceNotSupported) ||
	  (NegRespCode == nrcSubFunctionNotSupported_InvalidFormat))
	{
		PendingNegativeAnswer = NegRespCode;
		Kw2000State = k2sWaitingP2MinBeforeAnswer;
		 /*k2sWaitingAppLvlServiceExec;*/
	} else {
		SendNowStandardNegativeAnswer (NegRespCode);
	}
} /*** End of SendStandardNegativeAnswer ***/


/*********************************************************************/
/*** Builds a standard kw2000 positive answer                      ***/
/*********************************************************************/
#define SyZERO_VALUE    (0)

void KW2K_SendStandardPositiveAnswer (uint8_t MsgSize)
{
	/* If the message size is zero, change the state to the
	k2sAwaitingMessage.  This ensures proper control sequence.
	*/

	if ( MsgSize != SyZERO_VALUE ) {
		TxServiceData[0] = (RxServiceData [0] + PositiveResponseOffset);
		BuildKw2000Answer (MsgSize);
	} else {
		GoToAwaitingMessageK2State (false);
	}
} /*** End of SendStandardPositiveAnswer ***/

void SendEscapeCode (uint8_t MsgSize)
{
  /* If the message size is zero, change the state to the
     k2sAwaitingMessage.  This ensures proper control sequence.
     */

	if (MsgSize != SyZERO_VALUE) {
		TxServiceData[0] = (EscapeCode);
		BuildKw2000Answer (MsgSize);
	} else {
		GoToAwaitingMessageK2State (false);
	}
} /*** End of SendStandardPositiveAnswer ***/


/*********************************************************************/
/*** Put data in the Kw2000 input buffer.                          ***/
/*********************************************************************/

static void PutDataInKw2000InputBuffer (uint8_t DataIn)
{
	KW2000InputBuffer [KW2000InputBufferInPointer++] = DataIn;
	if (KW2000InputBufferInPointer == KW2000InputBufferSize) {
		KW2000InputBufferInPointer = 0;
	}
} /*** End of PutDataInKw2000InputBuffer ***/


/*********************************************************************/
/*** Get data from the Kw2000 input buffer.                        ***/
/*********************************************************************/

static bool GetDataFromKw2000InputBuffer (uint8_t *DataOutPtr)
{
	if (KW2000InputBufferInPointer != KW2000InputBufferOutPointer) {
		*DataOutPtr = KW2000InputBuffer [KW2000InputBufferOutPointer++];
		if (KW2000InputBufferOutPointer == KW2000InputBufferSize) {
			KW2000InputBufferOutPointer = 0;
		}
		return true;
	} else {
		return false;
	}
} /*** End of GetDataFromKw2000InputBuffer ***/


/********************************************************************/
/*** Serial communication Receive ISR                             ***/
/********************************************************************/

void SerialcomReceiveInt (void)
{
	uint8_t EchoByte;

	switch (Kw2000State) {
	case k2sAwaitingMessage:
		/*--- Wait for a first byte within P3MaxWL or 16 ms if Fast synchro */
	case k2sReceivingMessage:
		// if (SCI0ReceiverErrorFlag ()) {
		if (kline->GetAllErrFlag()) {
			/*--- if error or break: ---*/
			GoToErrorReadK2State ();
		} else {
			// PutDataInKw2000InputBuffer(SCI0_ReadSCIReceiverDataRegister ());
			PutDataInKw2000InputBuffer((uint8_t)kline->read());
		}
		if (Kw2000State == k2sAwaitingMessage) {
			GoToReceivingMessageK2State ();
		}
		break;
	case  k2sSendingMessage:
       /* Transmit state */
       /* If the received byte is no equal to the sent byte OR
          a collision occurs, go to waiting state.
          */
		if (((!SCI0ReceiverErrorFlag ()) &&
			// (SCI0_ReadSCIReceiverDataRegister () == DataByte ))||
			((uint8_t)kline->read() == DataByte ))||
			(KW2000CommuState==KW2000_Tester))
		{
			switch (Kw2MsgTxState) {
			case ktsSendingFormat:
				TxDataIndex = 1;
				if (k2mFmt (TxFormatByte) == mfPhysAddr) 
				{
					Kw2MsgTxState = ktsSendingTgtAddr;
					DataByte = TxTargetAddress ;
					SendKw2000ByteToSerial ();
				} 
				else /*--- mfNoAddr ---*/
				{
					if (k2mLen (TxFormatByte))
					/*--- length already in format byte ---*/
					{
						Kw2MsgTxState = ktsSendingData;
						DataByte = TxServiceData [0] ;
						SendKw2000ByteToSerial ();
					}
					else
					 /*--- no: send it ---*/
					{
						Kw2MsgTxState = ktsSendingLength;
						DataByte = TxMsgDataLength ;
						SendKw2000ByteToSerial ();
					}
				}
				break;

			case ktsSendingTgtAddr:
				Kw2MsgTxState = ktsSendingSrcAddr ;
				DataByte = TxSourceAddress ;
				SendKw2000ByteToSerial () ;
				break;

			case ktsSendingSrcAddr:
				if (k2mLen (TxFormatByte))
				/*--- length already in format byte ---*/
				{
					Kw2MsgTxState = ktsSendingData ;
					DataByte = TxServiceData [0] ;
					SendKw2000ByteToSerial () ;
				}
				else
				/*--- no: send it ---*/
				{
					Kw2MsgTxState = ktsSendingLength ;
					DataByte = TxMsgDataLength ;
					SendKw2000ByteToSerial () ;
				}
				break;

			case ktsSendingLength:
				Kw2MsgTxState = ktsSendingData ;
				DataByte = TxServiceData [0] ;
				SendKw2000ByteToSerial () ;
				break;

			case ktsSendingData:
				if (TxDataIndex < TxMsgDataLength) {
					DataByte = TxServiceData [TxDataIndex] ;
					SendKw2000ByteToSerial ();
					TxDataIndex++;
				} else {
					Kw2MsgTxState = ktsSendingCheckSum ;
					DataByte = TxCalcCheckSum ;
					SendKw2000ByteToSerial () ;
				}
				break;

			case ktsSendingCheckSum:
				// SCI0ReceiverReset (); /*--- Cancel echo ---*/
				kline->reset();
				if (KW2000_Responder==KW2000CommuState) {
					P2MinTimer = 0;
					if (GetCommunicationEstablishedState()) {
						if ( GetMultiRespInProgress()) {
							SbPosResponsePending = true;
							GoToExecuteServiceK2State ();
						} else {
							/* If the preceeding command was service 10
							to change the baud rate than, it shoud be
							done now.  The baud rate is changed after
							sending the positive response.
							*/
							if (BaudRateChangedSrv10) {
								BaudRateChangedSrv10 = false ;
								SCI0_SetSCIBaudRate ( BaudRateValueSrv10 ) ;
							}
							GoToAwaitingMessageK2State (false);
							SbPosResponsePending = false;
						}
					} else {
						/*--- was an answer to a stop communication service ---*/
						GoToWaitingTIdleSynchK2State (TIdleStopCom);
					}
				}

				break;
			default:
				break;
			}
			if (KW2000_Tester==KW2000CommuState)
				P4Timout=0;
		}
		else
		{
			if (KW2000_Responder==KW2000CommuState)
			{
			P2MinTimer = 0 ;
			// SCI0ReceiverReset () ;
			kline->reset();
			GoToWaitingP2MinBeforeAnswerK2State () ;
			}
		}
		break ;

	case k2sWaitingP2MinBeforeAnswer:
	case k2sWaitingP3MinBeforeSend:
	case k2sWaitingP4MinBeforeSend:
	case k2sExecuteService          :
	case k2sWaitingAppLvlServiceExec:
	case k2sWaitingInitializing:
	case k2sLostCommunication:
	case k2sErrorRead:
		/* If bus activity during wait, reset the timer */
		if (KW2000_Responder==KW2000CommuState)  P2MinTimer = 0 ;
		if (KW2000_Tester==KW2000CommuState) P3MinTimer = 0;
		// SCI0ReceiverReset () ;
		kline->reset();
		break ;
	default:
		break;
	}
} /*** End of SerialcomReceiveInt ***/


/*********************************************************************/
/*** Serial communication Transmit ISR                             ***/
/*********************************************************************/

void SerialcomTransmitInt (void)
{
	/* Rev. 1.18 - Immobilizer interrupt logic added by KPB */
	/*SendingWakeUpTransmitComplete();*/

} /*** End of SerialcomTransmitInt ***/


/*********************************************************************/
/*** Returns if Event Received on Serial (new data or error / break)***/
/*********************************************************************/

static bool SerialEventReceived (void)
{
	// return (bool) (SCI0ReceiverReadyFlag () || SCI0ReceiverErrorFlag ());
	return (bool) (kline->poll() || kline->GetAllErrFlag());
} /*** End of SerialEventReceived ***/


/*******************************************************************/
/*** Keyword 2000 State periodic operation: k2sWaitingTIdleSynch ***/
/*** ---> Waiting for TIdle idle condition.                      ***/
/*******************************************************************/

static void WaitingTIdleSynchKw2000State (void)
{
	if (!SerialEventReceived ())
	/*--- if Idle... ---*/
	{
		IdleTimer++;
		if (IdleTimer >= TIdle)
		  /*--- ...for longer than TIdle: ---*/
		  {
			GoToScanningHighToLowEdgeSynchK2State ();
		  }
		}
	else
	/*--- if not Idle: ---*/
	{
		// SCI0ReceiverReset ();
		kline->reset();
		IdleTimer = 0;
		TIdle = 0;
	}
} /*** End of WaitingTIdleSynchKw2000State ***/


/*******************************************************************/
/*** KW 2000 State periodic oper.: k2sScanningHighToLowEdgeSynch ***/
/*** ---> Awaiting idles followed by 1 break or a data = 0.      ***/
/*******************************************************************/

static void ScanningHighToLowEdgeSynchKw2000State (void)
{
	if (SerialEventReceived ())
	/*--- if not Idle: ---*/
	{
		// if (SCI0ReceiverFramingErrorDetectedFlag () &&
		// (SCI0_ReadSCIReceiverDataRegister () == 0))
		if (kline->GetFrmErrFlag() &&
			(kline->read() == 0))
		/*--- if break: ---*/
		{
			GoToWaiting25msLowSynchK2State ();
		}
		else
		/*--- if not Idle nor break: ---*/
		{
			GoToWaitingTIdleSynchK2State (TIdleTimout);
		}
	}
    /* Still in Kw2000 communication mode: Do nothing. */
  } /*** End of ScanningHighToLowEdgeSynchKw2000State ***/


/********************************************************************/
/*** KW 2000 State periodic operation: k2sWaiting25msLowSynch     ***/
/*** Waiting 3 or 4 RTI with break followed by one RTI with idle. ***/
/********************************************************************/

static void Waiting25msLowSynchKw2000State (void)
{
	// if (SCI0ReceiverActiveDetected ())
	if (kline->GetActiveFlag())
	/*--- if break: ---*/
	{
		EventCounter++;
	}
	else
	/*--- if not break: ---*/
	/* After the break, SCI detected idle line and clear the flag RAF*/
	{
		if (EventCounter >= FastInitLogicMin)
		/*--- if (partial) idle after at least 3 breaks: ---*/
		{
			GoToWaiting25msHighSynchK2State ();
			return; /*--- Optimisation (EventCounter did not increase, so
			break) ---*/
		}
		else
		{
			GoToWaitingTIdleSynchK2State (TIdleTimout);
		}
	}
	if (EventCounter > ( FastInitLogicMax))
	/*--- if more than 4 breaks occured: ---*/
	{
		GoToWaitingTIdleSynchK2State (TIdleTimout);
	}
} /*** End of Waiting25msLowSynchKw2000State ***/

/*********************************************************************/
/*** Keyword 2000 State periodic operation: k2sWaiting25msHighSynch***/
/*** ---> Waiting 1 RTI with idle.                                 ***/
/*********************************************************************/
static void Waiting25msHighSynchKw2000State (void)
{
	if (!SerialEventReceived ())
	/*--- if idle: ---*/
	/*--- when 1 idle occured: ---*/
	{
		SetTimingParameterToDefault ();
		GoToAwaitingMessageK2State (true);
	}
	else
	/*--- if not idle: ---*/
	{
		GoToWaitingTIdleSynchK2State (TIdleTimout);
	}
} /*** End of Waiting25msHighSynchKw2000State ***/


/*********************************************************************/
/*** Keyword 2000 State periodic operation: k2sAwaitingMessage     ***/
/*** Scanning a first byte within P3MaxWL or 16 ms if fast synchro.***/
/*********************************************************************/
static void AwaitingMessageKw2000State (void)
{

  uint16_t TimeLimit;

  TimeLimit = (AfterFastSynchroFlag) ? (FastInitLogicHigh) : P3MaxWL;

  if (TimeLimit != 0xFFFF) /*--- infinite case ---*/
    {
    TimeLimit++;
    if (TimerBeforeNewMsgRx < TimeLimit)
      {
      TimerBeforeNewMsgRx++;
      }
    if (TimerBeforeNewMsgRx >= TimeLimit)
      /*--- Time is out (P3 Max expired): ---*/
      {
      GoToWaitingTIdleSynchK2State (TIdleTimout);  //debug
      }
    }
  else
    {
    if ((TimerBeforeNewMsgRx < 0xFFFF))
      {
      TimerBeforeNewMsgRx++;
      }
    }
} /*** End of AwaitingMessageKw2000State ***/

/*********************************************************************/
/*** Set MsgRx state machine to Loading Data                       ***/
/*********************************************************************/

void GoToLoadingDataMRState (void)
{
   RxDataIndex = 0;
   Kw2MsgRxState = mrsLoadingData;
} /*** End of GoToLoadingDataMRState ***/


/******************************************************************/
/*** Keyword 2000 State periodic operation: k2sReceivingMessage ***/
/*** ---> Schedule message reception.                           ***/
/******************************************************************/
void ReceivingMessageKw2000State (void)
{
	uint8_t DataRead;

	if (KW2000_Responder==KW2000CommuState)   P4Timout++;
	if (KW2000_Tester==KW2000CommuState)      P1Timout++;
	while (GetDataFromKw2000InputBuffer (&DataRead) && (Kw2000State == k2sReceivingMessage))
    /*--- Data is received and still in Receiving state ---*/
    {
		if (KW2000_Responder==KW2000CommuState)     P4Timout = 0; /* Reset timout */
		if (KW2000_Tester==KW2000CommuState)        P1Timout=0;

		RxCalcCheckSum += DataRead;
		switch (Kw2MsgRxState) {
		case mrsWaitingFormat:
			RxFormatByte = DataRead ;
			RxCalcCheckSum = RxFormatByte ;
			FunctionalAddressActive = false ;
			RxMsgDataLength = k2mLen (RxFormatByte) ;
			/*--- by default, store length in format byte ---*/
			switch (k2mFmt (RxFormatByte)) {
			case mfPhysAddr:
			case mfFunctAddr:
				Kw2MsgRxState = mrsWaitingTgtAddr;
				break;
			case mfNoAddr:
				if (GetCommunicationEstablishedState()) {
					if (1)
					{
						if (RxMsgDataLength) {   /*--- length already in format byte ---*/
							GoToLoadingDataMRState ();
						} else {   /*--- no: get it ---*/
							Kw2MsgRxState = mrsWaitingLength;
						}
					} else {
						GoToErrorReadK2State ();
					}
				} else {
					GoToErrorReadK2State ();
				}
				break;
			case mfCARB:
				GoToErrorReadK2State ();
				break;
			default:
				break;
			}
			break;

		case mrsWaitingTgtAddr:
			RxTargetAddress = DataRead ;
			if (((RxFormatByte & mfPhysAddr) &&
				(RxTargetAddress == MyPhysicalAddr)) ||
				((RxFormatByte & mfFunctAddr) &&
				(RxTargetAddress == MyFunctionalAddr)) ||
				((RxFormatByte & mfFunctAddr) &&
				(RxTargetAddress == MyFunctionalAddrNew)) ||
				((RxFormatByte & mfPhysAddr) &&
				(RxTargetAddress == MyImmoPhysicalAddr)) )
			{
				/* Target address is valid. */
				Kw2MsgRxState = mrsWaitingSrcAddr ;
				if ((( RxFormatByte & mfFunctAddr) &&
					(RxTargetAddress == MyFunctionalAddr)) ||
					((RxFormatByte & mfFunctAddr) &&
					(RxTargetAddress == MyFunctionalAddrNew )))
				FunctionalAddressActive = true ;
			} else {
				/* Target address is NOT valid. */
				GoToErrorReadK2State () ;
			}
			break;

		case mrsWaitingSrcAddr:
			RxSourceAddress = DataRead ;
			if ((RxSourceAddress == MySourceAddr0) ||
				(RxSourceAddress == MySourceAddr1) ||
				(RxSourceAddress == KcMyImmoSourceAddr)||
				(RxSourceAddress == CySiemens_ImmoTargetAddress))
			{
				if (RxMsgDataLength) {
					/*--- length already in format byte ---*/
					GoToLoadingDataMRState () ;
				} else {
					/*--- no: get it ---*/
					Kw2MsgRxState = mrsWaitingLength ;
				}
			} else {
				/* Source address is NOT valid. */
				GoToErrorReadK2State () ;
			}
			break;

		case mrsWaitingLength:
			if ((KW2000CommuState==KW2000_Tester)) {
				RxMsgDataLength = DataRead ;   
			} else {
				RxMsgDataLength = DataRead ;
			}
			/*--- length in format byte was null, get it now ---*/
			GoToLoadingDataMRState () ;
			break;

		case mrsLoadingData:
		RxServiceData [RxDataIndex] = DataRead;
		RxDataIndex++;
		if (RxDataIndex == RxMsgDataLength) {
			Kw2MsgRxState = mrsWaitingCheckSum;
		}
		break;

		case mrsWaitingCheckSum:
			/*when ECM is in slave mode and (RxCalcCheckSum - DataRead) != DataRead), error read*
				*  when ECM is in master mode, JiCheng immo is enabled, and (RxCalcCheckSum - DataRead) != DataRead), error read*/
			if (((uint8_t) (RxCalcCheckSum - DataRead) != DataRead)
				&&((KW2000CommuState==KW2000_Responder) ))
			{
				GoToErrorReadK2State ();
			} else {
                /* The Receiver interrupt need not be disabled.
                  The response bytes from other servers cause the
                  P2Min timer reset.
                */
				GoToExecuteServiceK2State();		
			}
			break;
		default:
			break;
		}
	}
	/*--- check if time out ---*/

	if (KW2000_Responder==KW2000CommuState) {
		if (P4Timout > P4Max) {
			GoToErrorReadK2State ();
		}
	}
} /*** End of ReceivingMessageKw2000State ***/


/*********************************************************************/
/*** Keyword 2000 State periodic operation: k2sExecuteService      ***/
/*** > Execute low level services and warn application for others. ***/
/*********************************************************************/

static void ExecuteServiceKw2000State (void)
{
	uint8_t ErrorValue ;

	if (GetCommunicationEstablishedState() || (RxServiceData [0] == sirStartCommunication)) {
		if (!SbPosResponsePending) {
			P2MinTimer = 1; /*--- Already one loop passed ---*/
		}
		switch (RxServiceData [0]) {
		case sirStartCommunication:
			if (RxMsgDataLength == 1) {
				if(0) {

				} else {
					TxServiceData [1] = KB1;
					TxServiceData [2] = KB2;
				}
				SendStandardPositiveAnswer (3);
				CommunicationEstablishedState = true;
			} else {
				if (GetCommunicationEstablishedState()) {
					SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
				} else {
					GoToWaitingTIdleSynchK2State (TIdleRestart);
				}
			}
			break;

		case sirStopCommunication:
			if (RxMsgDataLength == 1) {
				SendStandardPositiveAnswer (1) ;
				CommunicationEstablishedState = false ;
			} else {
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
			}
			break;

		case sirAccessCommunicationParameters:
			switch (RxServiceData [1]) {
			case ReadComParamLimits:
				if (RxMsgDataLength == 2) {
					TxServiceData [1] = RxServiceData [1];
					TxServiceData [2] = P2MinLimit;
					TxServiceData [3] = P2MaxLimit;
					TxServiceData [4] = P3MinLimit;
					TxServiceData [5] = P3MaxLimit;
					TxServiceData [6] = P4MinLimit;
					SendStandardPositiveAnswer (7);
				} else {
					SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
				}
				break;

			case SetComParamToDefaultVals:
				if (RxMsgDataLength == 2) {
					/*--- Change default values ---*/
					NewP2Min = DefaultP2Min;
					NewP2Max = DefaultP2Max;
					NewP3Min = DefaultP3Min;
					NewP3Max = DefaultP3Max;
					NewP4Min = DefaultP4Min;
					NewTiming = true;
					TxServiceData [1] = RxServiceData [1];
					SendStandardPositiveAnswer (2);
				} else {
					SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
				}
				break;

			case ReadComParamCurrentVals:
				if (RxMsgDataLength == 2) {
					TxServiceData [1] = RxServiceData [1];
					TxServiceData [2] = P2Min;
					TxServiceData [3] = P2Max;
					TxServiceData [4] = P3Min;
					TxServiceData [5] = P3Max;
					TxServiceData [6] = P4Min;
					SendStandardPositiveAnswer (7);
				} else {
					SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
				}
				break;

			case SetComParamToNewVals:
				if (RxMsgDataLength == 7) {
					/*--- Change "New" values ---*/
					NewP2Min = RxServiceData [2];
					NewP2Max = RxServiceData [3];
					NewP3Min = RxServiceData [4];
					NewP3Max = RxServiceData [5];
					NewP4Min = RxServiceData [6];
					NewTiming = true;
					TxServiceData [1] = RxServiceData[1];
					SendStandardPositiveAnswer (2);
				} else {
					if (FunctionalAddressActive)
						ErrorValue = nrcConditionsNotCorrect_RequestSequenceError;
					else
						ErrorValue = nrcSubFunctionNotSupported_InvalidFormat;
					SendStandardNegativeAnswer (ErrorValue);
				}
				break;

			default:
				SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
				break;
			}
			break;

		default:
			GoToWaitingAppLvlServiceExecK2State ();
			break;
		}
	} else {
		GoToWaitingTIdleSynchK2State (TIdleRestart);
	}
} /*** End of ExecuteServiceKw2000State ***/


/*********************************************************************/
/*** KW 2000 State periodic operation: k2sWaitingAppLvlServiceExec ***/
/*** ---> Waiting for application level service to end execution.  ***/
/*********************************************************************/

static void WaitingAppLvlServiceExecKw2000State (void)
{
	uint16_t  TimeLimit;

	/*--- Increment P2 Min Timer to P2MinWL ---*/
	if (P2MinTimer < P2MinWL) {
		P2MinTimer++;
	}

	TimeLimit = P2MaxWL;
	if (((uint16_t) TimeLimit) == 0xFFFF) /*--- infinite case ---*/
	{
		TimeLimit--;
	}

	/*--- Increment P2 Max Timer to P2MaxWL ---*/
	if (TimerBeforeAnswerTx < TimeLimit) {
		TimerBeforeAnswerTx++;
	}

	if (TimerBeforeAnswerTx >= TimeLimit)
	/*--- Time is nearly out: P2 Max is going to passed, */
	/*    Service Non Supported ---*/
	{
		GoToAwaitingMessageK2State (false);
	}
} /*** End of WaitingAppLvlServiceExecKw2000State ***/


/*********************************************************************/
/*** KW 2000 State periodic operation: k2sWaitingP2MinBeforeAnswer ***/
/*** ---> Waiting minimum P2 Time just before sending the answer.  ***/
/*********************************************************************/

static void WaitingP2MinBeforeAnswerKw2000State (void)

{

  /*--- Increment P2 Min Timer to P2MinWL ---*/
  if (P2MinTimer < P2MinWL)
    {
    P2MinTimer++;
    }

  /*--- Send message when P2Min delay is passed ---*/
  /*--- P2MinWL is rounded by excess - above the real minimum ---*/
  if (P2MinTimer >= P2MinWL)
  {
    if (PendingNegativeAnswer != nrcNone)
    {
        SendNowStandardNegativeAnswer (PendingNegativeAnswer);
        PendingNegativeAnswer = nrcNone;
     }
    else
     {
       GoToSendingMessageK2State ();
    }
  }
} /*** End of WaitingP2MinBeforeAnswerKw2000State ***/

void GoToWaitingInitializingK2State (void)
{
   Kw2000State = k2sWaitingInitializing;
} /*** End of GoToWaitingInitializingK2State ***/

/*********************************************************************/
/*** Change kw2000 state to initial or waiting P3min.                                    ***/
/*********************************************************************/
void GoToWaitingInitializingOrP3MinState(void)
{
   if (P3MinTimer<P3MinWL)
   {
      Kw2000State=k2sWaitingP3MinBeforeSend;
   }
   else
   {
      Kw2000State=k2sWaitingInitializing;
   }

}

/*********************************************************************/
/*** KW 2000 State periodic operation: k2sWaitingP3MinBeforeSendRequest ***/
/*** ---> Waiting minimum P3 Time just before sending the request.  ***/
/*********************************************************************/

void WaitingP3MinBeforeSendRequest (void)
{
     P3MinTimer++;
     /*--- Increment P3 Min Timer to P3MinWL ---*/
     if (P3MinTimer >= P3MinWL)
     {
        /*--- Send message when P2Min delay is passed ---*/
        /*--- P2MinWL is rounded by excess - above the real minimum ---*/       	
        GoToWaitingInitializingK2State ();

     }
} /*** End of WaitingP3MinBeforeSendRequest  ***/

/*********************************************************************/
/*** KW 2000 State periodic operation: WaitingP4MinBeforeSendRequest            ***/
/*** ---> Waiting minimum P4 Time just before sending the request.                 ***/
/*********************************************************************/
void WaitingP4MinBeforeSendRequest(void)
{
	P4Timout++;
	if (P4Timout>=P4MinWL) {
		Kw2000State=k2sSendingMessage;
		// EnableSCI0ReceiverInterrupt(TRUE);
		kline->RxIntEnable();
		SendKw2000ByteToSerial();
	}
}/*** End of WaitingP4MinBeforeSendRequest ***/

/****************************************************************/
/*** Keyword 2000 State periodic operation: k2sSendingMessage ***/
/*** ---> Schedule message transmission.                      ***/
/****************************************************************/

static void SendingMessageKw2000State (void)

  {
  /*--- the state machine is run on interrupt level ---*/
  } /*** End of SendingMessageKw2000State ***/

/***********************************************************/
/*** Keyword 2000 State periodic operation: k2sErrorRead ***/
/*** ---> Handle errors (go to wait new message block).  ***/
/***********************************************************/

static void ErrorReadKw2000State (void)

  {
  GoToAwaitingMessageK2State (false);
  } /*** End of ErrorReadKw2000State ***/


/*********************************************************************/
/*** Periodic Keyword 2000 VIO logic (@ 7.81 ms)                   ***/
/*********************************************************************/

void UpdateKeyword2000VIO (void)
{
	switch (Kw2000State) {
	case k2sWaitingTIdleSynch:
		/*--- Waiting for TIdle idle condition      ---*/
		WaitingTIdleSynchKw2000State ();
		break;
	case k2sScanningHighToLowEdgeSynch:
		/*--- Awaiting idles followed by 1 break    ---*/
		ScanningHighToLowEdgeSynchKw2000State ();
		break;
	case k2sWaiting25msLowSynch:
		/*--- Waiting 3 or 4 RTI with break         ---*/
		/*--- followed by one RTI with idle         ---*/
		Waiting25msLowSynchKw2000State ();
		break;
	case k2sWaiting25msHighSynch:
		/*--- Waiting 1 RTI with idle               ---*/
		Waiting25msHighSynchKw2000State ();
		break;
	case k2sAwaitingMessage:
		/*--- Scanning a byte within delay          ---*/
		AwaitingMessageKw2000State ();
		break;
	case k2sReceivingMessage:
		/*--- Schedule message reception            ---*/
		ReceivingMessageKw2000State ();
		break;
	case k2sExecuteService:
		/*--- Execute or trigger services           ---*/
		ExecuteServiceKw2000State ();
		break;
	case k2sWaitingAppLvlServiceExec:
		/*--- Waiting for app.level service exec    ---*/
		WaitingAppLvlServiceExecKw2000State ();
		break;
	case k2sWaitingP2MinBeforeAnswer:
		/*--- Waiting minimum P2 Time before answer ---*/
		WaitingP2MinBeforeAnswerKw2000State ();
		break;
	case k2sSendingMessage:
		/*--- Schedule message transmission         ---*/
		SendingMessageKw2000State ();
		break;
	case k2sErrorRead:
		ErrorReadKw2000State ();
		break;
	default:
		break;
	}
} /*** End of UpdateKeyword2000VIO ***/




/*********************************************************************/
/*** Build Keyword 2000 request (and preset sending process).                         ***/
/*********************************************************************/
void BuildKw2000Request (uint8_t TxMsgSize)
{
	if (P3MinTimer<P3MinWL)
	{
		GoToWaitingP3MinBeforeSendingRequest();
	}
	else
	{
		GoToSendingMessageK2State ();
	}
} /*** End of BuildKw2000Request ***/



/*****************************************************************************
 *
 * Function:           CheckKW2000LineState
 * Description:       Check KW2000 bus timing parameters.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
void CheckKW2000LineState(void)
{
   /* When waiting response, check P2. */
   if (P2MinTimer>=P2MaxWL)
   	{
   	Kw2000State=k2sLostCommunication;
   	P2MinTimer=0;
   	}
   P2MinTimer++;
}/*** End of CheckKW2000LineState ***/
    
/************************************************/
/*** Initialize Kw2000 Virtual I.O:           ***/
/*** Set Serial parameters (baud rate, parity,***/
/*** char.length, Stopbits,...), reset        ***/
/*** kw2000 serial com. layer state machine.  ***/
/************************************************/

void InitializeKw2000VIO (void)
{
	// SCI0_SetSCIBaudRate (Kw2000BaudRate);
	kline->setbaud(Kw2000BaudRate);
	GoToWaitingTIdleSynchK2State (TIdleInit);
} /*** End of InitializeKw2000VIO ***/

/*********************************************************************/
/*** Reset Serial - Cancel current Serial reception and            ***/
/***             transmission. Restart after a break.              ***/
/*********************************************************************/

void SCI0ReceiverReset (void)
{
	volatile uint8_t TempByte;
	/* Read the status register and the data register to clear the receive
	* flags.  Enable the SCI receiver.
	*/
	ClearSCIRespReceivedFlag();
	// TempByte = SCI0ReceiverErrorFlag ();
	// TempByte = SCI0_ReadSCIReceiverDataRegister ();
	// EnableSCI0Receiver (true);
	TempByte = kline->GetAllErrFlag();
	TempByte = kline->read();
	kline->RxIntEnable();
} /*** End of SCIReceiverReset ***/



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *   - moved all variables to section .nvram_boot.
 *
 * 26/05/03     wxhe        120
 * + KWP2000 error.
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - Changed to support KWP2000 master mode for generic immo
 *
 * 12/03/07     LShoujun    mt20u2#79    
 * + new generic immo requirement change after P3 
 *   - Separate P2MinTimer logic of multi-response message from others
 *
 * 22/11/07	   Yu Runwu    mt20u2#194
 * + Implement CJAE Immobilizer and Remove Old Immobilizer
 *   - Add CJAE immobilizer logic on KWP2000.
 *
 * 16/05/07     LShoujun    mt20u2#734(task)
 * + replace MCU of KG256 with xep100 - Step I
 *  - Changed compiler to Cosmic s12x
\* ============================================================================ */
