/*-------------------------------------------------------------------*/
/* filename -  DCANTRAN.C                                            */
/*                                                                   */
/* PURPOSE:  Implementation of the CAN transport layer.              */
/*                                                                   */
/* Description: This file contains all the data/Functions necessary  */
/*              to interface the CAN application layer to the CAN    */
/*              data link layer.                                     */
/*                                                                   */
/* LIST OF FUNCTION(S):                                              */
/*  InLine:                                                          */
/*          InitializeLnAppServiceDataFrame                          */
/*          InitializeLnRingBuffer                                   */
/*          LnGoToSendingFlowControlCts                              */
/*                                                                   */
/*  Implem:                                                          */
/*          LnWriteNbBytesFromSourceToDest                           */
/*          GetLnServNbOfFreeBytesInRingBuffer                       */
/*          GetLnServNbOfUsedBytesInRingBuffer                       */
/*          StoreLnServNbBytesInRingBuffer                           */
/*          RetrieveLnServNbBytesFromRingBuffer                      */
/*          LnGoToWaitingForRxFirstOrSingleFrame  -h-                */
/*          InitializeLnMultipleFrameRxState                         */
/*          LnGoToReceivingBlockOfData                               */
/*          LnGoToWaitingForRxRingBufferNotFull                      */
/*          LnWaitingForRxFirstOrSingleFrame                         */
/*          LnReceivingBlockOfData                                   */
/*          LnWaitingRingBufferNotFull                               */
/*          SendFlowControl                                          */
/*          LnGoToNotSending                                         */
/*          LnGoToSendingFirstFrame                                  */
/*          LnGoToWaitingForRxFlowControl                            */
/*          LnGoToSendingBlockOfData                                 */
/*          InitializeLnMultipleFrameTxState                         */
/*          SendFirstFrame                                           */
/*          LnSendMessage                         -h-                */
/*          LnSendUudtMessage                     -h-                */
/*          LnWaitingForRxFlowControl                                */
/*          LnSendingBlockOfData                                     */
/*          WaitingDataForTxInRingBuffer                             */
/*          LnTrspCanId7e0RcvdEvent               -h-                */
/*          LnTrspCanId7e8RcvdEvent               -h-                */
/*          InitializeLnTransportLayer            -h-                */
/*          UpdateLnTransportLayer                -h-                */
/*                                                                   */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* DELPHI Delco Luxembourg C Engine Management Software              */
/* (c) Copyright DELPHI Delco Electronics Systems 2001               */
/*-------------------------------------------------------------------*/

 /****************************************************************************
 *
 * Current Module Info:
 * %full_name:      lux_pt1#1/csrc/lntransp.c/1 %
 * %date_created:   Wed Feb 15 18:20:47 2006 %
 * %version:        1 %
 * %derived_by:     c23cr %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "obdsfapp.h" /* Transmit_Message */
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
//#include "obdltype.h"
#include "dcancomm.h"/*LnSignalTranspErrorEvent()*/
#include "dcanserv.h"
#include "dd_flash.h"      
#include "mt2x_kernel.h"
#include "dd_can.h"
#include "hwiocald.h"
#include "intr_ems.h"
#include "dd_tle4471.h"
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/

/******************************************************************************
 *  Global Variables
 *****************************************************************************/
/*--- definition of data for application interface layer ---*/
LnServiceDataFrameType      LnServiceDataFrame;
uint16_t                   LnNbOfUsedBytesInRingBuffer;
bool                        LnServiceDataBeingInserted;
LnTrspTimeOutErrorType             LnTrspTimeOutError;
VioCanRxBufferStructType VioCanRxBuffer [RX_MSG_BUFFER_NUMBER];
/******************************************************************************
 * Static Variables
 *****************************************************************************/
/*--- definition of data for network layer multiple frame Rx Tx ---*/
static LnMultipleFrameRxStateType  LnMultipleFrameRxState;
static LnMultipleFrameTxStateType  LnMultipleFrameTxState;
static uint8_t                    *LnInPointer;
static uint8_t                    *LnOutPointer;
static CanIdType                   LnTranspRespUsdtFrameCanId;
static uint16_t                    NbOfBytesStillToTransmit;
static bool                        LnEvent2EmptyRingBuffTransmitted;
static uint8_t                     LnSequenceNumber;
static uint8_t                     LnSTmin;  /*--- min Separation Time between transmissions
                                                of 2 Consecutive Frames ---*/
static TyTIME_t_R7p8125ms          LnSTminInBaseLoopSecB; /*--- min Separation Time between
                                                             transmissions of 2 Consecutive Frames ---*/
static TwTIME_t_R7p8125ms          LnNetworkLayerWaitTimeCounter;
															 
//static uint8_t                   LnBSmax; /*unused code BSmax always = 0 in CANOBD 
                                /*--- Block Size max for Control Flow
                                           = max number of Consecutive Frame per Block
                                             without Flow Control frame ---*/
/* uint8_t                   LnNbConsecutiveFrameTransmitted; unused code BSmax always = 0 in GMLAN */
/* uint8_t                   LnNbConsFrameRcvdInCurrentBlock;  unused code BSmax always = 0 in GMLAN */

/* GMW-3110 V1.5 :                                  */
/*   1 ms per count for value between $00 and $7F   */
/*   100 us per count for value between $F1 and $F9 */
#define   OneMsMaxRange   (0x7F)
#define MaxTimeToWaitforRingBufferNotFullInMs (1000)  /*--- max time to wait for ring Buffer not full ---*/

#define LntranspEventFrameTransmitted (LnEventFrameTransmitted)
#define LntranspEventFunctionalRequest (LnEventFunctionalRequest)
#define LntranspEventResetToWaitingRequest (LnGoToWaitingRequest)
#define RequestCanToTransmit8Bytes RequestCanToTransmit
/**************************/
/*** Clear_Buffer ***/
/**************************/
INLINE void Clear_Buffer (uint8_t *buffer)
{
   uint8_t index;

   for(index = 0; index < 8; index++)
   {  *buffer = 0;
           buffer++;
   }
}

/**************************/
/*** LnTranspErrorEvent ***/
/**************************/
INLINE void LnTranspErrorEvent (LnTrspTimeOutErrorType LnTimeOutError)
{
   LnTrspTimeOutError = LnTimeOutError;
   LnSignalTranspErrorEvent (LnTrspTimeOutError);
} /*** End of LnTranspErrorEvent ***/

/**************************************/
/*** LnWriteNbBytesFromSourceToDest ***/
/**************************************/
INLINE void LnWriteNbBytesFromSourceToDest (uint16_t  NbOfBytesToWrite,
                                     uint8_t *SourceBufferPtr,
                                     uint8_t *DestinationBufferPtr)
{
   uint16_t ByteNumber;
   for (ByteNumber = 0; ByteNumber < NbOfBytesToWrite; ByteNumber++)
   {
      *DestinationBufferPtr++ = *SourceBufferPtr++;
   }
} /*** End of LnWriteNbBytesFromSourceToDest ***/

/*****************************************************/
/*** Initialize GMLAN application ServiceDataFrame ***/
/*****************************************************/
INLINE void InitializeLnAppServiceDataFrame (void)
{
   LnServiceDataFrame.DataLength = 0;
   LnServiceDataFrame.CurrentDataLength = 0;
} /*** End of InitializeLnAppServiceDataFrame ***/

/***********************************************/
/***********************************************/
/***********************************************/
/***                                         ***/
/***  R I N G   B U F F E R   C O N T R O L  ***/
/***                                         ***/
/***********************************************/
/***********************************************/
/***********************************************/

/************************************/
/*** Initialize GMLAN ring buffer ***/
/************************************/
INLINE void InitializeLnRingBuffer (void)
{
   LnInPointer = &LnServiceDataFrame.Data[0];
   LnOutPointer = &LnServiceDataFrame.Data[0];
   LnNbOfUsedBytesInRingBuffer = 0;
   LnServiceDataBeingInserted = false;
} /*** End of LnInitializeRingBuffer ***/

/******************************************/
/*** GetLnServNbOfFreeBytesInRingBuffer ***/
/******************************************/
uint16_t GetLnServNbOfFreeBytesInRingBuffer (void)
{
   return (DataBufferSize - LnNbOfUsedBytesInRingBuffer);
} /*** End of GetLnServNbOfFreeBytesInRingBuffer ***/

/******************************************/
/*** GetLnServNbOfUsedBytesInRingBuffer ***/
/******************************************/
uint16_t GetLnServNbOfUsedBytesInRingBuffer (void)
{
   return LnNbOfUsedBytesInRingBuffer;
} /*** End of GetLnServNbOfUsedBytesInRingBuffer ***/

/**************************************/
/*** StoreLnServNbBytesInRingBuffer ***/
/**********************************************************************/
/*** return TRUE if could store the number of bytes                 ***/
/*** return FALSE if did not store any byte                         ***/
/***              because there was not enough free bytes available ***/
/**********************************************************************/
bool StoreLnServNbBytesInRingBuffer (uint16_t NbBytesToStore,
                                        uint8_t *SourceBufferPtr)
{
   //uint32_t          interrupt_state;
   interrupt_state_t context ;   
   bool Stored;
   uint16_t ByteNumber;
   uint8_t *LocalSourceBufferPtr;

   LocalSourceBufferPtr = SourceBufferPtr;
   //interrupt_state = EnterCriticalSection();
  context = Enter_Critical_Section();
   if (GetLnServNbOfFreeBytesInRingBuffer () >= NbBytesToStore)
   {
      for (ByteNumber = 0; ByteNumber < NbBytesToStore; ByteNumber++)
      {
         *LnInPointer = *LocalSourceBufferPtr++;
         if (LnInPointer == &LnServiceDataFrame.Data [DataBufferSize - 1])
         {
            LnInPointer = &LnServiceDataFrame.Data [0];
         }
         else
         {
            LnInPointer++;
         }
         LnNbOfUsedBytesInRingBuffer++;
         LnServiceDataFrame.CurrentDataLength++;
         if (LnServiceDataFrame.CurrentDataLength > DataBufferSize)
         {
            LnServiceDataFrame.IndexOfValidDataNotOverwrittenYet++;
          }
      }
      if (LnServiceDataFrame.CurrentDataLength == LnServiceDataFrame.DataLength)
      {
         LnServiceDataBeingInserted = false;
      }
      else
      {
         LnServiceDataBeingInserted = true;
      }
      Stored = true;
   }
   else
   {
      Stored = false;
   }
  // ExitCriticalSection( interrupt_state );
  Leave_Critical_Section(context);
   return Stored;
} /*** End of StoreLnServNbBytesInRingBuffer ***/

/*******************************************/
/*** RetrieveLnServNbBytesFromRingBuffer ***/
/***************************************************************************/
/*** return TRUE if could get the number of bytes requested              ***/
/***              in that case, the retrieval did release the Number of  ***/
/***              bytes retrieved from the ring buffer. there are then   ***/
/***              free to be written again by new received data if in Rx ***/
/***              or by new data to transmit if in Tx                    ***/
/*** return FALSE if did not get any byte                                ***/
/***              because there was not enough bytes ready for retrieve  ***/
/***************************************************************************/
bool RetrieveLnServNbBytesFromRingBuffer (uint16_t  NbBytesToRetrieve,
                                             uint8_t *DestinationBufferPtr)
{
   bool CouldGet;
   uint16_t ByteNumber;
  // uint32_t          interrupt_state;
  // interrupt_state = EnterCriticalSection();
  interrupt_state_t context ;   
  context = Enter_Critical_Section();
   if (GetLnServNbOfUsedBytesInRingBuffer () >= NbBytesToRetrieve)
   {
      for (ByteNumber = 0; ByteNumber < NbBytesToRetrieve; ByteNumber++)
      {
         *DestinationBufferPtr++ = *LnOutPointer;
         if (LnOutPointer == &LnServiceDataFrame.Data [DataBufferSize - 1])
         {
            LnOutPointer = &LnServiceDataFrame.Data [0];
         }
         else
         {
            LnOutPointer++;
         }
         LnNbOfUsedBytesInRingBuffer--;
      }
      CouldGet = true;
   }
   else
   {
      CouldGet = false;
   }
  // ExitCriticalSection( interrupt_state );
  Leave_Critical_Section(context);
   return CouldGet;
} /*** End of RetrieveLnServNbBytesFromRingBuffer ***/

/***********************************************/
/***********************************************/
/***********************************************/
/***                                         ***/
/***              E N D   O F                ***/
/***  R I N G   B U F F E R   C O N T R O L  ***/
/***                                         ***/
/***********************************************/
/***********************************************/
/***********************************************/
/*********************************/
/*********************************/
/*********************************/
/***                           ***/
/*** N E T W O R K   L A Y E R ***/
/***                           ***/
/*********************************/
/*********************************/
/*********************************/
/*********************************/
/***                           ***/
/*** N E T W O R K   L A Y E R ***/
/***                           ***/
/***     R E C E P T I O N     ***/
/***                           ***/
/*********************************/

/********************************************/
/*** LnGoToWaitingForRxFirstOrSingleFrame ***/
/********************************************/
void LnGoToWaitingForRxFirstOrSingleFrame (void)
{
   interrupt_state_t context ;   

  context = Enter_Critical_Section();
  // uint32_t          interrupt_state;
  
   //interrupt_state = EnterCriticalSection();
   LnMultipleFrameRxState = WaitingForRxFirstOrSingleFrame;
   LnServiceDataFrame.CurrentDataLength = 0;
   InitializeLnRingBuffer ();
   LnEvent2EmptyRingBuffTransmitted = false;
   //ExitCriticalSection( interrupt_state );
   Leave_Critical_Section(context);
} /*** End of LnGoToWaitingForRxFirstOrSingleFrame ***/

/***********************************/
/*** LnGoToSendingFlowControlCts ***/
/***********************************/
INLINE void LnGoToSendingFlowControlCts (void)
{
   LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (MaxTimeForSengingOneFrameInMs / 1000.0);
   LnMultipleFrameRxState = SendingFlowControlCts;
} /*** End of LnGoToSendingFlowControlCts ***/

/************************************/
/*** LnGoToSendingFlowControlWait ***/ /* unused function in GMLAN , FlowControlWait not allowed in GMLAN */
/************************************/
INLINE void LnGoToSendingFlowControlWait (void)
{
   LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (MaxTimeForSengingOneFrameInMs / 1000.0);
   LnMultipleFrameRxState = SendingFlowControlWait;
} /*** End of LnGoToSendingFlowControlWait ***/

/*************************************/
/*** LnGoToWaitingForRxBlockOfData ***/
/*************************************/
void LnGoToWaitingForRxBlockOfData (TwTIME_t_R7p8125ms MaxTimeToWaitForFirstCf)
{
   LnNetworkLayerWaitTimeCounter = MaxTimeToWaitForFirstCf;
   LnMultipleFrameRxState = WaitingForRxBlockOfData;
} /*** End of LnGoToWaitingForRxBlockOfData ***/

/**********************************/
/*** LnGoToReceivingBlockOfData ***/
/**********************************/
INLINE void LnGoToReceivingBlockOfData (void)
{
  /* LnNbConsFrameRcvdInCurrentBlock = 0;  unused code BSmax always = 0 in GMLAN */
   LnMultipleFrameRxState = ReceivingBlockOfData;
} /*** End of LnGoToReceivingBlockOfData ***/

/*******************************************/
/*** LnGoToWaitingForRxRingBufferNotFull ***/ /* unused function in GMLAN , FlowControlWait not allowed in GMLAN */
/*******************************************/
INLINE void LnGoToWaitingForRxRingBufferNotFull (TwTIME_t_R7p8125ms MaxTimeToWait)
{
   if (LnMultipleFrameRxState != WaitingForRxRingBufferNotFull)
   {
      LnNetworkLayerWaitTimeCounter = MaxTimeToWait;
      LnMultipleFrameRxState = WaitingForRxRingBufferNotFull;
      LnEventRxWaitingAppToEmptyRingBuffer ();
   }
} /*** End of LnGoToWaitingForRxRingBufferNotFull ***/

/*****************************************/
/*** LnGoToReceptionCompleteMsgWaiting ***/
/*****************************************/
INLINE void LnGoToReceptionCompleteMsgWaiting (void)
{
   LnEventReceptionCompleteMsgWaiting ();
   LnServiceDataFrame.CurrentDataLength = 0;
   LnMultipleFrameRxState = ReceptionCompleteMsgWaiting;
} /*** End of LnGoToReceptionCompleteMsgWaiting ***/

/*****************************************************/
/*** Initialize Multiframe Reception State Machine ***/
/*****************************************************/
INLINE void InitializeLnMultipleFrameRxState (void)
{
   InitializeLnRingBuffer ();
   LnServiceDataFrame.IndexOfValidDataNotOverwrittenYet = 0;
   LnGoToWaitingForRxFirstOrSingleFrame ();
} /*** End of InitializeLnMultipleFrameRxState ***/

/****************************************/
/*** LnWaitingForRxFirstOrSingleFrame ***/
/****************************************/
INLINE void LnWaitingForRxFirstOrSingleFrame (void)
{
    /*--- nothing to do.
          the transition to ReceivingBlocOfData is done in LnReceiveUsdtFirstFrame ().
          LnReceiveUsdtFirstFrame () is called on interrupt from Data Link Layer. ---*/
} /*** End of LnWaitingForRxFirstOrSingleFrame ***/

/******************************/
/*** LnReceivingBlockOfData ***/
/******************************/
void LnReceivingBlockOfData (void)
{
  /*--- check time since last reception of last Consecutive Frame ---*/
   if (LnNetworkLayerWaitTimeCounter == 0)
   {
      LnGoToWaitingForRxFirstOrSingleFrame ();
      LnTranspErrorEvent (TimeOutFromCfToCf);
   }
} /*** End of LnReceivingBlockOfData ***/

/*******************************/
/*** Send Flow Control frame ***/
/*******************************/
void SendFlowControl (void)
{
   LnUsdtFlowControlFrameType LnUsdtFlowControlFrame;


/* the following code has been put in comment because FlowControlWait not allowed
   and BSmax always = 0 in CANOBD */
/*   AvailableNbOfFreeByteInRxBuffer = GetLnServNbOfFreeBytesInRingBuffer (); */
/*   if (AvailableNbOfFreeByteInRxBuffer < 8) */
/*     {/*--- send control Flow Wait ---*/
/*     LnUsdtFlowControlFrame.PCIByte = PCIFlowControl + FlowControlFlowStatusWait; */
/*     LnGoToSendingFlowControlWait (); */
/*     } */
/*   else */
/*     {/*--- send control Flow ClearToSend ---*/
/*     RemainingNbBytetoReceive = LnServiceDataFrame.DataLength */
/*                                - LnServiceDataFrame.CurrentDataLength; */
/*     LnUsdtFlowControlFrame.PCIByte = PCIFlowControl + FlowControlFlowStatusClearToSend; */
/*     if (RemainingNbBytetoReceive > AvailableNbOfFreeByteInRxBuffer) */
/*       { */
/*       /*--- determine Block Size max ---*/
/*       LnUsdtFlowControlFrame.BSmax = AvailableNbOfFreeByteInRxBuffer / 7; */
/*       } */
/*     else */
/*       { */
/*       LnUsdtFlowControlFrame.BSmax = BlockSizeNoFurtherFlowControl; */
/*       } */
/*     LnUsdtFlowControlFrame.STmin = MinimumSeparationTimeInMs; */
/*     /* LnBSmax = LnUsdtFlowControlFrame.BSmax; unused code, BSmax always = 0 in GMLAN */
/*     LnGoToSendingFlowControlCts (); */
/*     } */

/* always FlowControl FlowStatus ClearToSend because FlowControlWait not allowed in GMLAN */
   LnUsdtFlowControlFrame.PCIByte = PCIFlowControl + FlowControlFlowStatusClearToSend;
   LnUsdtFlowControlFrame.BSmax = BlockSizeNoFurtherFlowControl; /* always 0 in CANOBD */
   LnUsdtFlowControlFrame.STmin = MinimumSeparationTimeInMs;
   LnUsdtFlowControlFrame.Unused1=0;
   LnUsdtFlowControlFrame.Unused2=0;
   LnUsdtFlowControlFrame.Unused3=0;
   LnUsdtFlowControlFrame.Unused4=0;
   LnUsdtFlowControlFrame.Unused5=0;

   LnGoToSendingFlowControlCts ();
   RequestCanToTransmit (LnTranspRespUsdtFrameCanId,
                        (Can8DataBytesArrayType *) &LnUsdtFlowControlFrame);
} /*** End of SendFlowControl ***/

/***************************************/
/*** LnWaitingForRxRingBufferNotFull ***/
/***************************************/
INLINE void LnWaitingForRxRingBufferNotFull (void)
{
   if (LnNetworkLayerWaitTimeCounter == 0)
   {
      while (true) {}; /* this should never happen, reset after wait time */
   }
} /*** End of LnWaitingForRxRingBufferNotFull ***/

/*********************************/
/***                           ***/
/*** N E T W O R K   L A Y E R ***/
/***                           ***/
/***  T R A N S M I S S I O N  ***/
/***                           ***/
/*********************************/

/************************/
/*** LnGoToNotSending ***/
/************************/
INLINE void LnGoToNotSending (void)
{
   LnMultipleFrameTxState = NotSending;
} /*** End of LnGoToNotSending ***/

/********************************/
/*** LnGoToSendingSingleFrame ***/
/********************************/
INLINE void LnGoToSendingSingleFrame (void)
{
   LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (MaxTimeForSengingOneFrameInMs / 1000.0);
   LnMultipleFrameTxState = SendingSingleFrame;
} /*** End of LnGoToSendingSingleFrame ***/

/*******************************/
/*** LnGoToSendingFirstFrame ***/
/*******************************/
INLINE void LnGoToSendingFirstFrame (void)
{
   LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (MaxTimeForSengingOneFrameInMs / 1000.0);
   LnMultipleFrameTxState = SendingFirstFrame;
   LnSequenceNumber = 0;
} /*** End of LnGoToSendingFirstFrame ***/

/*************************************/
/*** LnGoToWaitingForRxFlowControl ***/
/*************************************/
void LnGoToWaitingForRxFlowControl (TwTIME_t_R7p8125ms MaxTimeToWait)
{
   LnNetworkLayerWaitTimeCounter = MaxTimeToWait;
   LnMultipleFrameTxState = WaitingForRxFlowControl;
} /*** End of LnGoToWaitingForRxFlowControl ***/

/**********************************************/
/*** LnGoToWaitingForRxFlowControlAfterWait ***/
/**********************************************/
INLINE void LnGoToWaitingForRxFlowControlAfterWait (TwTIME_t_R7p8125ms MaxTimeToWait)
{
   LnNetworkLayerWaitTimeCounter = MaxTimeToWait;
   LnMultipleFrameTxState = WaitingForRxFlowControlAfterWait;
} /*** End of LnGoToWaitingForRxFlowControlAfterWait ***/

/***********************************************/
/*** LnGoToWaitingForTxFirstConsecutiveFrame ***/
/***********************************************/
INLINE void LnGoToWaitingForTxFirstConsecutiveFrame (TwTIME_t_R7p8125ms MaxTimeToWait)
{
   LnNetworkLayerWaitTimeCounter = MaxTimeToWait;
   LnMultipleFrameTxState = WaitingForTxFirstConsecutiveFrame;
} /*** End of LnGoToWaitingForTxFirstConsecutiveFrame ***/

/********************************/
/*** LnGoToSendingBlockOfData ***/
/******************************************************************/
/*** LnGoToSendingBlockOfData means transmission of the         ***/
/*** Consecutive Frame of the Block of data                     ***/
/*** and so not the transmission of the First Frame !!!         ***/
/*** block of data = only composed of Consecutive Frame,        ***/
/***                 i.e. First Frame not part of Block of data ***/
/*** the Sequence Number of the first Consecutive Frame of the  ***/
/*** block will not systematically re-start with 1              ***/
/******************************************************************/
void LnGoToSendingBlockOfData (void)
{
   Can8DataBytesArrayType Can8DataBytesArray;
   Clear_Buffer(&Can8DataBytesArray [0]);

      /* LnNbConsecutiveFrameTransmitted = 0; unused code,
         BSmax always = 0 in GMLAN */
   LnSequenceNumber++;
   Can8DataBytesArray[ 0 ] = ConsecutiveFrame | ( LnSequenceNumber &
         ConsecutiveFrameSequenceNumberMask );

   LnMultipleFrameTxState = WaitingForBlockFrameTx;
   LnNetworkLayerWaitTimeCounter =
         C_R7p8125ms16( MaxTimeForSengingOneFrameInMs / 1000.0 );

   if( NbOfBytesStillToTransmit <= 7 )
   {
         /*--- First and last Consecutive Frame ---*/
      RetrieveLnServNbBytesFromRingBuffer( NbOfBytesStillToTransmit,
            ( uint8_t * )&Can8DataBytesArray[ 1 ] );
      RequestCanToTransmit( LnTranspRespUsdtFrameCanId,
            &Can8DataBytesArray );
      NbOfBytesStillToTransmit = 0;
   }
   else
   {
         /*--- First and not the last Consecutive Frame ---*/
      RetrieveLnServNbBytesFromRingBuffer( 7,
            ( uint8_t * )&Can8DataBytesArray[ 1 ] );
      NbOfBytesStillToTransmit = NbOfBytesStillToTransmit - 7;
      RequestCanToTransmit8Bytes( LnTranspRespUsdtFrameCanId,
            &Can8DataBytesArray );
   }
}
 /*** End of LnGoToSendingBlockOfData ***/

/******************************************/
/*** LnGoToWaitingDataForTxInRingBuffer ***/
/******************************************/
INLINE void LnGoToWaitingDataForTxInRingBuffer (void)
{
   LnMultipleFrameTxState = WaitingDataForTxInRingBuffer;
} /*** End of LnGoToWaitingDataForTxInRingBuffer ***/

/********************************************************/
/*** Initialize Multiframe Transmission State Machine ***/
/********************************************************/
void InitializeLnMultipleFrameTxState (void)
{
   InitializeLnRingBuffer ();
   LnGoToNotSending ();
} /*** End of InitializeLnMultipleFrameTxState ***/

/************************/
/*** Send First Frame ***/
/************************/
/*####TRICORE The tasking does not seem to like this inline and crashes with an assertion
INLINE void SendFirstFrame (void)
*/
void SendFirstFrame (void)
{
   Can8DataBytesArrayType Can8DataBytesArray;
   Can8DataBytesArray [0] = 0x10 | (LnServiceDataFrame.DataLength / 256);
   Can8DataBytesArray [1] = (uint8_t) LnServiceDataFrame.DataLength;
  /*--- SID is always data byte [0] in frame to transmit because always
        positive answer since negative answer < 6 bytes and then no first frame ---*/
   RetrieveLnServNbBytesFromRingBuffer (6, (uint8_t *) &Can8DataBytesArray [2]);
   NbOfBytesStillToTransmit = LnServiceDataFrame.DataLength - 6;
   LnGoToSendingFirstFrame ();
   RequestCanToTransmit8Bytes (LnTranspRespUsdtFrameCanId, &Can8DataBytesArray);
} /*** End of SendFirstFrame ***/
#if 0
/*************************/
/*** LnSendUudtMessage ***/
/*************************/
void LnSendUudtMessage (Can8DataBytesArrayType *Can8DataBytesArrayPtr, uint8_t NbBytesToTransmit)
{
   PARAM_NOT_USED (NbBytesToTransmit);
  /*RequestCanToTransmitNbBytes (DiagRespUudtSingleFrameCanId,
                               &Can8DataBytesArrayPtr [0],
                               NbBytesToTransmit);*/
   RequestCanToTransmit (DiagRespUudtSingleFrameCanId,
                        &Can8DataBytesArrayPtr [0]);
} /*** End of LnSendUudtMessage ***/
#endif
/*********************/
/*** LnSendMessage ***/
/*********************/
void LnSendMessage (void)
{
   Can8DataBytesArrayType Can8DataBytesArray;

   if (LnServiceDataFrame.DataLength <= 7)
   { /*--- send Single Frame ---*/
      Clear_Buffer(&Can8DataBytesArray [0]);
      Can8DataBytesArray [0] = LnServiceDataFrame.DataLength; /*--- PCI = $0X, X = Data Length ---*/
      LnWriteNbBytesFromSourceToDest (LnServiceDataFrame.DataLength,
                                    (uint8_t *)(&LnServiceDataFrame.Data[0]),
                                    (uint8_t *) &Can8DataBytesArray [1]);
      RequestCanToTransmit (LnTranspRespUsdtFrameCanId, &Can8DataBytesArray);
      LnGoToSendingSingleFrame ();
   }
   else
   { /*--- send Multiple Frame ---*/
      if (!LnServiceDataBeingInserted)
      { /*--- Initialize LnInPointer only if all the data are in the frame array ---*/
        /*--- this is needed if the data have not been written by
              StoreLnServNbBytesInRingBuffer () ---*/
         LnInPointer = &LnServiceDataFrame.Data [LnServiceDataFrame.DataLength];
         LnNbOfUsedBytesInRingBuffer = LnServiceDataFrame.DataLength;
      }
      LnOutPointer = &LnServiceDataFrame.Data [0];
      SendFirstFrame ();
      //LnGoToSendingFirstFrame ();
   }
} /*** End of LnSendMessage ***/

/*********************************/
/*** LnWaitingForRxFlowControl ***/
/*********************************/
INLINE void LnWaitingForRxFlowControl (void)
{
  /*--- check time since last Transmission of FF or CF ---*/
   if (LnNetworkLayerWaitTimeCounter == 0)
   {
      LnGoToNotSending ();
      LnGoToWaitingForRxFirstOrSingleFrame ();
      LnTranspErrorEvent (TimeOutFromFfOrCfToFc);
   }
} /*** End of LnWaitingForRxFlowControl ***/

/******************************************/
/*** LnWaitingForRxFlowControlAfterWait ***/
/******************************************/
INLINE void LnWaitingForRxFlowControlAfterWait (void)
{
  /*--- check time since last reception of Flow Control Wait ---*/
   if (LnNetworkLayerWaitTimeCounter == 0)
   {
      LnGoToNotSending ();
      LnGoToWaitingForRxFirstOrSingleFrame ();
      LnTranspErrorEvent (TimeOutFromFfOrCfToFc);
   }
} /*** End of LnWaitingForRxFlowControlAfterWait ***/

/************************/
/* RequestCanToTransmit */
/***********************************************************************/
/* Description: This primitive is called by the application to send a  */
/*              message of 8 data bytes on CAN providing in parameter: */
/*              - the CAN ID,                                          */
/*              - a pointer on the data to transmit                    */
/***********************************************************************/
void RequestCanToTransmit (CanIdType CanId,
                           Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
  Transmit_Message (CanId, Can8DataBytesArrayPtr[0]);
} /*** End of RequestCanToTransmit ***/

/****************************/
/*** LnSendingBlockOfData ***/ /*--- routine called every 10 ms ---*/
/****************************/
/***********************************************************/
/*** Only one Consecutive Frame per 10 ms is transmitted ***/
/*** to be sure no throughput problemm is encountered    ***/
/***********************************************************/
/*####TRICORE The tasking does not seem to like this inline and crashes with an assertion
INLINE void LnSendingBlockOfData (void)
*/
void LnSendingBlockOfData (void)
{
   Can8DataBytesArrayType Can8DataBytesArray;
   Clear_Buffer(&Can8DataBytesArray [0]);
   if (NbOfBytesStillToTransmit != 0)
   {
      if (LnSTminInBaseLoopSecB == 0)
      {
       //  LnSTminInBaseLoopSecB = LnSTmin / CcSYST_BASE_LOOP_1_TIME_x2;
        LnSTminInBaseLoopSecB = LnSTmin* 1000 / 7812;
         LnSequenceNumber++;
      /*--- prepare PCI = Consecutive Frame + Sequence Number ---*/
         Can8DataBytesArray [0] = ConsecutiveFrame
                               |
                               (LnSequenceNumber & ConsecutiveFrameSequenceNumberMask);
         if (NbOfBytesStillToTransmit <= 7)
         { /*--- last Consecutive Frame of the message ---*/
            if (RetrieveLnServNbBytesFromRingBuffer (NbOfBytesStillToTransmit,
                                                 (uint8_t *) &Can8DataBytesArray [1]))
            {
               NbOfBytesStillToTransmit = 0;
               LnMultipleFrameTxState = WaitingForBlockFrameTx;
               LnNetworkLayerWaitTimeCounter =  C_R7p8125ms16 (MaxTimeForSengingOneFrameInMs / 1000.0);
               RequestCanToTransmit (LnTranspRespUsdtFrameCanId, &Can8DataBytesArray);
            }
            else
            { /*--- the Nb of bytes to transmit from application are not available
                  in ring buffer... could the application be sleeping? ---*/
               LnGoToWaitingDataForTxInRingBuffer ();
            }
         }
         else
         { /*--- not the last Consecutive Frame ---*/
            if (RetrieveLnServNbBytesFromRingBuffer (7, (uint8_t *) &Can8DataBytesArray [1]))
            {
               LnMultipleFrameTxState = WaitingForBlockFrameTx;
               LnNetworkLayerWaitTimeCounter =  C_R7p8125ms16 (MaxTimeForSengingOneFrameInMs / 1000.0);
               RequestCanToTransmit8Bytes (LnTranspRespUsdtFrameCanId, &Can8DataBytesArray);
               NbOfBytesStillToTransmit = NbOfBytesStillToTransmit - 7;
            }
            else
            { /*--- the Nb of bytes to transmit from application are not available
                 in ring buffer... could the application be sleeping? ---*/
               LnGoToWaitingDataForTxInRingBuffer ();
            }
         }
      }
      else
      {
         LnSTminInBaseLoopSecB--;
      }
   }
   else
   {
      LnGoToNotSending ();
   }
} /*** End of LnSendingBlockOfData ***/

/**************************************/
/*** LnWaitingDataForTxInRingBuffer ***/
/**************************************/
INLINE void LnWaitingDataForTxInRingBuffer (void)
{
} /*** End of LnWaitingDataForTxInRingBuffer ***/

/*********************************/
/***                           ***/
/*** N E T W O R K   L A Y E R ***/
/***                           ***/
/***  U P D A T E   R X / T X  ***/
/***                           ***/
/*********************************/


/**************************/
/*** LnFrameTransmitted ***/
/**************************/
 void LnFrameTransmitted (void)
{
   LnGoToWaitingForRxFirstOrSingleFrame ();
   LnGoToNotSending ();
   LntranspEventFrameTransmitted ();
   //InitializeLnDiagSvCommunication();
   LnTranspRespUsdtFrameCanId = DiagRespUsdtFrameCanId;
} /*** End of LnFrameTransmitted ***/

/****************************************************/
/***                                              ***/
/*** FUNCTIONS CALLED BY DATA LINK LAYER ROUTINES ***/
/***                                              ***/
/***   ON THE RECEPTION OF UUDT OR USDT FRAMES    ***/
/***                                              ***/
/****************************************************/

/*****************************************************************/
/***          USDT Physical Request Received Event             ***/
/***          Single Frame or First Frame or Consecutive Frame ***/
/***                       or Flow Control                     ***/
/*****************************************************************/
INLINE void LnTrspUsdtRcvdFromDistantEvent (Can8DataBytesArrayType Can8DataBytesArray)
{
   uint8_t PCIByte;
   uint16_t  DataLength;
   uint16_t  RemainingNbBytetoReceive;

   PCIByte = Can8DataBytesArray [0];

   switch (PCIByte & UsdtFrameTypePciMask)
   {
      case SingleFrame:
/*      if (LnMultipleFrameRxState == WaitingForRxFirstOrSingleFrame)
        {*/
      /*--- in the case two concecutive requests are received without letting the
           time to the application to use the first one, the second one will
           overwrite the first one even if it could not be used by the
           application.
           The GMLAN ENHANCED DIAGNOSTIC TEST MODE SPECIFICATION, rev 1.1,
           specifies this in the paragraph 'Diagnostic Communication
           Implementation rules'.
           The maximum polling rate specified there is 30 ms.
           Our application polling rate is 10 ms. ---*/
      DataLength = (uint16_t) (PCIByte & SingleFrameDataLengthPciMask);
      LnServiceDataFrame.DataLength = DataLength;
      LnWriteNbBytesFromSourceToDest (DataLength,
                                      &Can8DataBytesArray [1],
                                      &LnServiceDataFrame.Data [0]);
      LnServiceDataFrame.CurrentDataLength = DataLength;
      SetLnMessageAddressingMode (PhysicalAddressing);
      LnGoToReceptionCompleteMsgWaiting ();
/*        }*/
      break;
      case FirstFrame:
/*      if (LnMultipleFrameRxState == WaitingForRxFirstOrSingleFrame)
        {*/
      /*--- in the case two concecutive requests are received without letting the
           time to the application to use the first one, the second one will
           overwrite the first one even if it could not be used by the
           application.
           The GMLAN ENHANCED DIAGNOSTIC TEST MODE SPECIFICATION, rev 1.1,
           specifies this in the paragraph 'Diagnostic Communication
           Implementation rules'.
           The maximum polling rate specified there is 30 ms.
           Our application polling rate is 10 ms. ---*/
      LntranspEventResetToWaitingRequest ();
      DataLength = (uint16_t) (((PCIByte & SingleFrameDataLengthPciMask) << 8)
                                      + Can8DataBytesArray [1]);
      LnServiceDataFrame.DataLength = DataLength;
      StoreLnServNbBytesInRingBuffer (6, &Can8DataBytesArray [2]);

            SendFlowControl();

      break;
      case ConsecutiveFrame:
      if (LnMultipleFrameRxState == WaitingForRxBlockOfData)
      { /*--- on first Consecutive Frame ---*/
         LnGoToReceivingBlockOfData ();
      }
      LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (MaxTimeFromCfToCfInMs / 1000.0);
      if (LnMultipleFrameRxState == ReceivingBlockOfData)
      {
        /* LnNbConsFrameRcvdInCurrentBlock++; unused code BSmax always = 0 in GMLAN */
         RemainingNbBytetoReceive = LnServiceDataFrame.DataLength -
                                   LnServiceDataFrame.CurrentDataLength;
         if (RemainingNbBytetoReceive > 7)
         { /*--- remaining number of byte to receive >= 7 ---*/
            if (!StoreLnServNbBytesInRingBuffer (7, &Can8DataBytesArray [1]))
            {
               LnGoToWaitingForRxRingBufferNotFull (C_R7p8125ms16 (MaxTimeToWaitforRingBufferNotFullInMs / 1000.0));
            }
            if (LnNbOfUsedBytesInRingBuffer > 80 /* 1 frame per ms <=> 80 bytes per 10 ms */
              &&
              !LnEvent2EmptyRingBuffTransmitted)
            {
               LnEventRxWaitingAppToEmptyRingBuffer ();
               LnEvent2EmptyRingBuffTransmitted = true;
            }
         }
         else
         { /*--- this is the last Consecutive frame of this block
                  because all data bytes have been received ---*/
            if (!StoreLnServNbBytesInRingBuffer (RemainingNbBytetoReceive,
                                               &Can8DataBytesArray [1]))
            {
               LnGoToWaitingForRxRingBufferNotFull (C_R7p8125ms16 (MaxTimeToWaitforRingBufferNotFullInMs / 1000.0));
            }
            else
            {
            /*--- all data bytes have been received ---*/
               SetLnMessageAddressingMode (PhysicalAddressing);
               LnGoToReceptionCompleteMsgWaiting ();
            }
         }
      }
      break;
      case PCIFlowControl:
      if (LnMultipleFrameTxState == WaitingForRxFlowControl)
      {
         if ((PCIByte & UsdtFrameTypePciMask) == PCIFlowControl)
         { /*--- received Flow Control in transmission ---*/
            if ((PCIByte & FlowControlFlowStatusMask) == FlowControlFlowStatusClearToSend)
            {
               /* LnBSmax = Can8DataBytesArray [1]; unused code, BSmax always = 0 in GMLAN */
               LnSTmin = Can8DataBytesArray [2];
               /*--- conversion from 1 ms or 100us to 7.8125 ms precision since logic called every 7.8125 ms ---*/
               if (LnSTmin <= OneMsMaxRange)
               {
			  /* 1 ms per count */
                 // LnSTminInBaseLoopSecB = LnSTmin / CcSYST_BASE_LOOP_1_TIME_x2;
                  LnSTminInBaseLoopSecB = LnSTmin* 1000 / 7812;
                  if ((LnSTmin % 8) != 0)
                  {
                    LnSTminInBaseLoopSecB++;
                  }
               }
               else
               {
			  /* 100 us per count: set minimum time to 7.8125 ms  */
                  LnSTminInBaseLoopSecB = 1;
               }
            /*--- the current specification do not require to wait after the reception
                  of a Control Flow to transmit the fisrt Consecutive frame ---*/
            /* if ()
              {
              LnGoToWaitingForTxFirstConsecutiveFrame (TwTIME_t_R7p8125ms MaxTimeToWait);
              }
            else
              { */
               LnGoToSendingBlockOfData ();
              /*} */
            }
            else if ((PCIByte & FlowControlFlowStatusMask) == FlowControlFlowStatusWait)
            { /* this should never happen in GMLAN */
               LnGoToWaitingForRxFlowControlAfterWait (C_R7p8125ms16 (MaxTimeFromFcWtToFcInMs / 1000.0));
            }
         }
      }
      else
      { /*--- must have received the Flow Control the ECM has transmitted ---*/
         if (LnMultipleFrameRxState == SendingFlowControlCts)
         {
            LnGoToWaitingForRxBlockOfData (C_R7p8125ms16 (MaxTimeFromFcCtsToCfInMs / 1000.0));
         }
        /*--- if in any any other state, ignore present message ---*/
      }
      break;
   }
} /*** End of LnTrspUsdtRcvdFromDistantEvent ***/


/*******************************************************/
/*** CAN Id = $7df frame received event              ***/
/***          EOBD USDT Functionnal Request          ***/
/*******************************************************/
void LnTrspCanId7dfRcvdEvent (Can8DataBytesArrayType Can8DataBytesArray)
{
   uint8_t PCIByte;
   uint16_t  DataLength;
   PCIByte = Can8DataBytesArray [0];

   if ((PCIByte & 0xF0) == 0x00 /*--- only Single Frame in functional mode cf spec. ---*/
      //&&
     // LnMultipleFrameRxState == WaitingForRxFirstOrSingleFrame
      )
   {
     LnMultipleFrameRxState = WaitingForRxFirstOrSingleFrame;
      SetLnMessageAddressingMode (FunctionalAddressing);
      DataLength = (uint16_t) (PCIByte & SingleFrameDataLengthPciMask);
      LnServiceDataFrame.DataLength = DataLength;
      LnWriteNbBytesFromSourceToDest (DataLength,
                                    &Can8DataBytesArray [1],
                                    &LnServiceDataFrame.Data [0]);
      LnServiceDataFrame.CurrentDataLength = DataLength;
      LnGoToReceptionCompleteMsgWaiting ();
      LntranspEventFunctionalRequest ();
   }
} /*** End of LnTrspCanId7dfRcvdEvent ***/

/*****************************************************************/
/*** CAN Id = USDT frame received event,                       ***/
/***          this is a frame the ECM has transmitted          ***/
/*****************************************************************/
void LnTrspUsdtRcvdFromEcmEvent (Can8DataBytesArrayType Can8DataBytesArray)
{
   uint8_t PCIByte;
   PCIByte = Can8DataBytesArray [0];

   switch (PCIByte & UsdtFrameTypePciMask)
   {
      case SingleFrame:
         LnFrameTransmitted ();
      break;
      case FirstFrame:
         LnGoToWaitingForRxFlowControl(
         C_R7p8125ms16( MaxTimeFromFfOrCfToFcInMs / 1000.0 ) );
      break;
      case ConsecutiveFrame:
         if (LnMultipleFrameTxState==WaitingForBlockFrameTx)
         {
            LnMultipleFrameTxState=SendingBlockOfData;
         }
      /* LnNbConsecutiveFrameTransmitted++; unused code, BSmax always = 0 in GMLAN */
      /*--- nothing else to do, a concecutive frame is send every 10 ms by the backgrond ---*/
         if (NbOfBytesStillToTransmit == 0)
         { /*--- on last Consecutive Frame ---*/
            LnFrameTransmitted ();
         }

      break;
      case PCIFlowControl:
         if (LnMultipleFrameRxState == SendingFlowControlCts)
         {
            LnGoToWaitingForRxBlockOfData (C_R7p8125ms16 (MaxTimeFromFcCtsToCfInMs / 1000.0));
          }
      break;

	  default :
		
                LnMultipleFrameTxState=SendingBlockOfData;
	break; 

   }
} /*** End of LnTrspUsdtRcvdFromEcmEvent ***/


/*********************/
/* CanId7dfRcvdEvent */
/*********************/
void CanId7dfRcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnServiceDataFrame.SourceCanId = DCAN_RECEIVE_MESSAGE_ID;
   LnTranspRespUsdtFrameCanId = DiagRespUsdtFrameCanId;
   LnTrspCanId7dfRcvdEvent (*Can8DataBytesArrayPtr);
} /*** End of CanId7dfRcvdEvent ***/

/*********************/
/* CanId7e0RcvdEvent */
/*********************/
void CanId7e0RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnServiceDataFrame.SourceCanId = DCAN_FLOWCONTROL_MESSAGE_ID;
   LnTranspRespUsdtFrameCanId = DiagRespUsdtFrameCanId;
   LnTrspUsdtRcvdFromDistantEvent (*Can8DataBytesArrayPtr);
} /*** End of CanId7e0RcvdEvent ***/

/*********************/
/* CanId7e8RcvdEvent */
/*********************/
void CanId7e8RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnTrspUsdtRcvdFromEcmEvent (*Can8DataBytesArrayPtr);
} /*** End of CanId7e8RcvdEvent ***/

#define KERNEL_FLASH_STARTADDR_LOW    (0x8000)
#define KERNEL_RAM_STARTADDR           (0x5000)
#define KERNEL_SIZE                    (2809)
/* ========================================================================= *\
 * FUNCTION: Copy_DFlash_to_RAM_and_Execute
 * Description: copy code from D-Flash to RAM and execute
\* ========================================================================= */
static void Copy_Flash_to_RAM_and_Execute( uint8_t *rom_add, uint8_t *ram_add, uint16_t size )
{
 void (*fp_reprogramkernal)(void);

   ReadIO_Flash_BlockData( rom_add, ram_add, size);
   
   fp_reprogramkernal = (void*) ((uint16_t)(KERNEL_RAM_STARTADDR));

   /* Call routine. */
   //fp_reprogramkernal();  
  (*fp_reprogramkernal)();

}

bool Get_Reprogram_Conditions_Met(void)
{
   bool reprogram_allowed = false;

   if ( GetVIOS_n_EngSpd() < V_RPMa( 200 ) &&
         GetVIOS_v_VehSpd() < V_KPH( 3 ) )
   {
       reprogram_allowed = true;
   }
   return reprogram_allowed;
}

FAR_COS void KW2KCAN_Received_Message(Can8DataBytesArrayType Can8DataBytesArrayPtr)
{
   uint8_t startDiagResp[8]= { 0xFB, 0x02, 0x50, 0x84, 0x00, 0x00, 0x00, 0x00 };



 if ( Get_Reprogram_Conditions_Met() )
 {

      // okay to FLASH 

    Transmit_Message( KW2K_CANID_TRANSMIT, startDiagResp);
    CAN_Clear_Transmit_Buffer_Empty_Flag(KeHWIO_CCP_CanPort,1);      /* request message xmit for CAN0 */
    CAN_Clear_Receive_Buffer_Full_Flag(KeHWIO_CCP_CanPort);
     // Put ECU into a known safe state 
     // SetIO_Outputs_For_Flash_Program();
    SetVIOS_MainRlyOff();
    Disable_Interrupts();
    TLE4471_WatchDog_Feeding();
    OS_COPClear();
	  
	Copy_Flash_to_RAM_and_Execute( (uint8_t*)KERNEL_FLASH_STARTADDR_LOW,
                                   (uint8_t*)KERNEL_RAM_STARTADDR,
                                             KW2k_Over_CAN_Kernel_Size);
   }
}

/****************************************************/
/***                   END OF                     ***/
/***                                              ***/
/*** FUNCTIONS CALLED BY DATA LINK LAYER ROUTINES ***/
/***                                              ***/
/***   ON THE RECEPTION OF UUDT OR USDT FRAMES    ***/
/***                                              ***/
/****************************************************/

/***********************************************/
/***********************************************/
/***                                         ***/
/*** E N D   O F   N E T W O R K   L A Y E R ***/
/***                                         ***/
/***********************************************/
/***********************************************/

/****************************************/
/*** Initialize GMLAN Transport Layer ***/
/****************************************/
void InitializeLnTransportLayer (void)
{
   InitializeLnRingBuffer ();
   InitializeLnMultipleFrameRxState ();
   InitializeLnMultipleFrameTxState ();
   InitializeLnAppServiceDataFrame ();
} /*** End of InitializeLnTransportLayer ***/

/****************************/
/*** UpdateLnTransportLayer ***/
/****************************/
void UpdateLnTransportLayer (void)
{
   if (LnNetworkLayerWaitTimeCounter != 0)
   {
      LnNetworkLayerWaitTimeCounter--;
   }

   switch (LnMultipleFrameRxState)
   {
      case WaitingForRxFirstOrSingleFrame:
         LnWaitingForRxFirstOrSingleFrame ();
      break;
      case SendingFlowControlWait:
      case SendingFlowControlCts:
         if (LnNetworkLayerWaitTimeCounter == 0)
         {
            LnGoToWaitingForRxFirstOrSingleFrame ();
            LnTranspErrorEvent (CanFrameNotTransmitedOnTime);
          }
      break;
      case WaitingForRxBlockOfData:
    /*--- check time since last reception of last Consecutive Frame ---*/
         if (LnNetworkLayerWaitTimeCounter == 0)
        {
            LnGoToWaitingForRxFirstOrSingleFrame ();
            LnTranspErrorEvent (TimeOutFromFcCtsToCf);
         }
      break;
      case ReceivingBlockOfData:
         LnReceivingBlockOfData ();
      break;
      case WaitingForRxRingBufferNotFull:
         LnWaitingForRxRingBufferNotFull ();
      break;
      case ReceptionCompleteMsgWaiting:
	 // LnDiagSvCommunicationState = RxCompleteWaitingAppToRespond;
      break;
      default :
      for (;;) {}
   }
   switch (LnMultipleFrameTxState)
   {
      case NotSending:
      break;
      case SendingSingleFrame:
         if (LnNetworkLayerWaitTimeCounter == 0)
         {
            LnGoToNotSending ();
            LnTranspErrorEvent (CanFrameNotTransmitedOnTime);
         }
      break;
      case SendingFirstFrame:
         if( LnNetworkLayerWaitTimeCounter == 0 )
         {
            LnGoToNotSending();
            LnTranspErrorEvent( CanFrameNotTransmitedOnTime );
         }
      break;
      case WaitingForRxFlowControl:
         LnWaitingForRxFlowControl ();
      break;
      case WaitingForRxFlowControlAfterWait: /* this should never happen in GMLAN */
         LnWaitingForRxFlowControlAfterWait ();
      break;
      case WaitingForTxFirstConsecutiveFrame:
         if (LnNetworkLayerWaitTimeCounter == 0)
         {
            LnGoToSendingBlockOfData ();
         }
      break;
      case SendingBlockOfData:
         LnSendingBlockOfData ();
      break;
      case WaitingForBlockFrameTx:
         if (LnNetworkLayerWaitTimeCounter == 0)
         {
            LnGoToNotSending ();
            LnTranspErrorEvent (CanFrameNotTransmitedOnTime);
         }
      break;
      case WaitingDataForTxInRingBuffer:
         LnWaitingDataForTxInRingBuffer ();
      break;
      default : 
      for (;;) {}
   }
} /*** End of UpdateLnTransportLayer ***/

void INCA_ReFlash (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
  {
  KW2KCAN_Received_Message (*Can8DataBytesArrayPtr);
  }

/****************************************************************/
/***                     RECEPTION TASKS                      ***/
/****************************************************************/
const CanRxMessageControlType CanRxMesgControlTable [] = {
/* Functional Request EOBD */
  DCAN_RECEIVE_MESSAGE_ID,
  BufferCanId7df,
  CanId7dfRcvdEvent
  ,
/* Diagnostic Information Usdt */
  DCAN_FLOWCONTROL_MESSAGE_ID,
  BufferCanId7e0,
  CanId7e0RcvdEvent
  ,
/* Functionnal Request Diag */
  KW2K_CANID_RECEIVE,
  BufferCanId6fb,
  INCA_ReFlash

};

#define RxMsgNbWithRxTimingsControlled (sizeof (CanRxMesgControlTable) / sizeof (CanRxMessageControlType))
const uint8_t BufferSizeRxMesgControlTable = RxMsgNbWithRxTimingsControlled;

//FAR_COS void Notify_Application_CANOBD( uint16_t  message_id )
FAR_COS void MngDCAN_RcvdEvent( uint16_t  message_id )
{
   VioCanRxBufferStructType * PtrOnVioCanRxBuffer;
   Can8DataBytesArrayType *Can8DataBytesArrayPtr;
   uint16_t PreviousRxBufferstate;
   uint8_t CanBuffer=0;
   uint8_t found = false;
   uint8_t CAN_message_number = 0;
   //uint8_t  Transferlayerbuffernumber = 0;

  // Transferlayerbuffernumber = Get_Receive_Message_Number_From_Message_ID(message_id); //mzyqz4-sep10
 
   for( CAN_message_number = 0;
        CAN_message_number <  BufferSizeRxMesgControlTable ;
        CAN_message_number++ )
   {
      if( CanRxMesgControlTable[CAN_message_number].CAN_message_ID == message_id )
      {
         found  = 1;
         CanBuffer = CAN_message_number;
         break;
      }
   }

   if (found != false)
   {
      // we have found a matching buffer entry,lets try to process the received msg.
      
     //CanBuffer = CanRxMesgControlTable [CAN_message_number].MessageBufferNumber;

      PtrOnVioCanRxBuffer = &(VioCanRxBuffer [CanBuffer]);

      PreviousRxBufferstate = VioCanRxBuffer[CanBuffer].State; 
      VioCanRxBuffer[CanBuffer].State = VioRxBufferBusy;

      if ( Get_Message( DCAN_RECEIVE_MESSAGE_ID, PtrOnVioCanRxBuffer->DataBytes ) )
      {
         if (PreviousRxBufferstate == VioRxBufferEmpty) 
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferFull;
         }
         else
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferOverrun;
         }
         Can8DataBytesArrayPtr =
                   (Can8DataBytesArrayType *) &(VioCanRxBuffer [CanBuffer].DataBytes);
        (*CanRxMesgControlTable [CanBuffer].Task) (Can8DataBytesArrayPtr);

      }
     else if ( Get_Message( DCAN_FLOWCONTROL_MESSAGE_ID, PtrOnVioCanRxBuffer->DataBytes ) )
      {
         if (PreviousRxBufferstate == VioRxBufferEmpty) 
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferFull;
         }
         else
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferOverrun;
         }
         Can8DataBytesArrayPtr =
                   (Can8DataBytesArrayType *) &(VioCanRxBuffer [CanBuffer].DataBytes);
        (*CanRxMesgControlTable [CanBuffer].Task) (Can8DataBytesArrayPtr);

      }
     else if ( Get_Message( KW2K_CANID_RECEIVE, PtrOnVioCanRxBuffer->DataBytes ) )
      {
         if (PreviousRxBufferstate == VioRxBufferEmpty) 
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferFull;
         }
         else
         {
            VioCanRxBuffer[CanBuffer].State = VioRxBufferOverrun;
         }
         Can8DataBytesArrayPtr =
                   (Can8DataBytesArrayType *) &(VioCanRxBuffer [CanBuffer].DataBytes);
        (*CanRxMesgControlTable [CanBuffer].Task) (Can8DataBytesArrayPtr);

     }
	     
   } 
}


FAR_COS void MngDCAN_TransmitdEvent( uint16_t   msg_id)
{

uint8_t CAN_transmit_message_number ;
Can8DataBytesArrayType *Can8DataBytesArrayPtr;

   for( CAN_transmit_message_number = 0;
        CAN_transmit_message_number <  CAN_NUMBER_OF_TRANSMIT_MESSAGES;
        CAN_transmit_message_number++ )
   {
      if( (TRANSMIT_CAN_MESSAGE_ID == msg_id)
	  	&&(DCAN_RESPONSE_MESSAGE_ID == msg_id))
      {
            break;
      }
   }
  
   Can8DataBytesArrayPtr = (Can8DataBytesArrayType *)(TRANSMIT_NEXT_DATA_OUT_PTR -TRANSMIT_CAN_MESSAGE_LENGTH);
   //CanId7e8TransmitdEvent(Can8DataBytesArrayPtr);
   CanId7e8RcvdEvent(Can8DataBytesArrayPtr);

}


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     060215 cr       Created from TCL version (archive cvs partition op36cm)
*
* 2     070629 abh      Modified to implement padding the non information bytes
*                       with zeros
* 3     080117 HHO CR28 Integrated immobilizer functions (GMW 7349)
*
* tcb_pt1#3.1.1
*       080603 HHO CR28 Added flags to inform immobilizer end of multi-frame tx
* tci_pt3#3.1.2
*       080924 VP  7329 Changes to support Customized TP for Immobilizer.
*
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
* 4.0  100915    hdg  xxx  Implemented CAN Flash in MT22.1 paltform.
* 3    100917    wj  CTC RSM8069
*                           Added CAN ID 101 for CAN reflash
* 4    101011    wj  CTC RSM8069 Turn off main power relay when reprogramming on going.
*
******************************************************************************/


