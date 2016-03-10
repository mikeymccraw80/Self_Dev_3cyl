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
/*          LnTrspCanId101RcvdEvent               -h-                */
/*          LnTrspCanId102RcvdEvent               -h-                */
/*          LnTrspCanId5e8RcvdEvent               -h-                */
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
 * %full_name:      ctc_pt3#1/csrc/dcantran.c/17 %
 * %date_created:   Thu Jun 26 10:57:11 2014 %
 * %version:        17 %
 * %derived_by:     dzrpmq %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "obdsfapp.h" /* Transmit_Message */
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "obdltype.h"
#include "dcancomm.h"/*LnSignalTranspErrorEvent()*/
// #include "cnftyp.h"
#include "dcanserv.h"
// #include "obdlcald.h"
#include "cn_io_transfer.h"

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
LnMultipleFrameTxStateType  LnMultipleFrameTxState;
LnMultipleFrameRxStateType  LnMultipleFrameRxState;
uint16_t                    NbOfBytesStillToTransmit;
uint8_t                     LnSequenceNumber;
bool                        VbDCAN_SvIgnoredMessage;
/******************************************************************************
 * Static Variables
 *****************************************************************************/
/*--- definition of data for network layer multiple frame Rx Tx ---*/
static uint8_t                    *LnInPointer;
static uint8_t                    *LnOutPointer;
static CanIdType                   LnTranspRespUsdtFrameCanId;
static bool                        LnEvent2EmptyRingBuffTransmitted;

static uint8_t                     LnSTmin;  /*--- min Separation Time between transmissions
                                                of 2 Consecutive Frames ---*/
static TyTIME_t_R7p8125ms          LnSTminInBaseLoopSecB; /*--- min Separation Time between
                                                             transmissions of 2 Consecutive Frames ---*/
static TyTIME_t_R7p8125ms          LnSTminToBaseLoop;
static TwTIME_t_R7p8125ms          LnNetworkLayerWaitTimeCounter;
static uint8_t                     LnRxSequenceNumber;															 

/* ISO-15765-2:                                  */
/*   1 ms per count for value between $00 and $7F   */
/*   100 us per count for value between $F1 and $F9 */
/*   for MT80 is 0x19 (25ms)*/
#define   OneMsMaxRange   (0x19)
#define MaxTimeToWaitforRingBufferNotFullInMs (1000)  /*--- max time to wait for ring Buffer not full ---*/

#define LntranspEventFrameTransmitted (LnEventFrameTransmitted)
#define LntranspEventFunctionalRequest (LnEventFunctionalRequest)
#define LntranspEventResetToWaitingRequest (LnGoToWaitingRequest)
#define RequestCanToTransmit8Bytes RequestCanToTransmit

#ifndef CcSYST_BASE_LOOP_1_TIME_x2_
#define CcSYST_BASE_LOOP_1_TIME_x2_ 8
#endif
#ifndef CcSYST_BASE_LOOP_1_TIME_x4_
#define CcSYST_BASE_LOOP_1_TIME_x4_ 16
#endif
#ifndef CcSYST_BASE_LOOP_1_TIME_x6_
#define CcSYST_BASE_LOOP_1_TIME_x6_ 24
#endif

#define PARAM_NOT_USED( notused ) 

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
   uint32_t          interrupt_state;
   bool Stored;
   uint16_t ByteNumber;
   uint8_t *LocalSourceBufferPtr;

   LocalSourceBufferPtr = SourceBufferPtr;
   interrupt_state = Enter_Critical_Section();
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
   Leave_Critical_Section( interrupt_state );
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
   uint32_t          interrupt_state;

   interrupt_state = Enter_Critical_Section();
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
   Leave_Critical_Section( interrupt_state );
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
   uint32_t          interrupt_state;

   interrupt_state = Enter_Critical_Section();
   LnMultipleFrameRxState = WaitingForRxFirstOrSingleFrame;
   LnServiceDataFrame.CurrentDataLength = 0;
   InitializeLnRingBuffer ();
   LnEvent2EmptyRingBuffTransmitted = false;
   Leave_Critical_Section( interrupt_state );
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
/*** LnGoToSendingFlowControlOverflow ***/
/************************************/
INLINE void LnGoToSendingFlowControlOverflow (void)
{
   LnNetworkLayerWaitTimeCounter = C_R7p8125ms16(0) ;
   LnMultipleFrameRxState = SendingFlowControlWait;
} /*** End of LnGoToSendingFlowControlOverflow ***/


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
void SendFlowControl (uint16_t  DataLength)
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

   LnUsdtFlowControlFrame.BSmax = BlockSizeNoFurtherFlowControl; /* always 0 in CANOBD */
   LnUsdtFlowControlFrame.STmin = MinimumSeparationTimeInMs;
   LnUsdtFlowControlFrame.Unused1=0;
   LnUsdtFlowControlFrame.Unused2=0;
   LnUsdtFlowControlFrame.Unused3=0;
   LnUsdtFlowControlFrame.Unused4=0;
   LnUsdtFlowControlFrame.Unused5=0;
   if (DataLength <0x0104)
   {
      LnUsdtFlowControlFrame.PCIByte = PCIFlowControl + FlowControlFlowStatusClearToSend;
      LnGoToSendingFlowControlCts ();
   }
   else
   {
     /*overflow*/
      LnUsdtFlowControlFrame.PCIByte = PCIFlowControl + FlowControlFlowStatusoverflow;
	  LnGoToSendingFlowControlOverflow (); //should be added
   }

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
   VbDCAN_SvIgnoredMessage = false;
   
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
	  NbOfBytesStillToTransmit = 0;
	  VbDCAN_SvIgnoredMessage = false;
      RequestCanToTransmit( LnTranspRespUsdtFrameCanId,
            &Can8DataBytesArray );
   }
   else
   {
      VbDCAN_SvIgnoredMessage = true;
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
                                    (uint8_t *) GetLnServiceData (),
                                    (uint8_t *) &Can8DataBytesArray [1]);
	  VbDCAN_SvIgnoredMessage = false;
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
	  VbDCAN_SvIgnoredMessage = true;
      SendFirstFrame ();
      LnGoToSendingFirstFrame ();
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
         LnSTminInBaseLoopSecB = LnSTminToBaseLoop;

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
			   VbDCAN_SvIgnoredMessage = false;	   
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
			   VbDCAN_SvIgnoredMessage = true;
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
void LnTrspUsdtRcvdFromDistantEvent (Can8DataBytesArrayType Can8DataBytesArray)
{
   uint8_t   PCIByte;
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
           
      /*terminate the current reception when SF N_PDU arrives*/
	  if((WaitingForRxBlockOfData == LnMultipleFrameRxState)
	  	 ||(ReceivingBlockOfData == LnMultipleFrameRxState))
      {
	    LnGoToWaitingForRxFirstOrSingleFrame();

      }
      DataLength = (uint16_t) (PCIByte & SingleFrameDataLengthPciMask);
      if ( ((DataLength > 0) && (DataLength < 8))
           &&(DataLength < GetCANMsg_Buffer_DLC())
           &&(!VbDCAN_SvIgnoredMessage))
      {
         LnServiceDataFrame.DataLength = DataLength;
         LnWriteNbBytesFromSourceToDest (DataLength,
                                      &Can8DataBytesArray [1],
                                      &LnServiceDataFrame.Data [0]);
         LnServiceDataFrame.CurrentDataLength = DataLength;
         SetLnMessageAddressingMode (PhysicalAddressing);
         LnGoToReceptionCompleteMsgWaiting ();
      }
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

	  if((WaitingForRxBlockOfData == LnMultipleFrameRxState)
	  	 ||(ReceivingBlockOfData == LnMultipleFrameRxState))
	  {
         LnGoToWaitingForRxFirstOrSingleFrame();
	  }
	  
      DataLength = (uint16_t) (((PCIByte & SingleFrameDataLengthPciMask) << 8)
                                      + Can8DataBytesArray [1]);
      if (( DataLength > 6 )
	  	&&(!VbDCAN_SvIgnoredMessage))
      {
         LnServiceDataFrame.DataLength = DataLength;
         StoreLnServNbBytesInRingBuffer (6, &Can8DataBytesArray [2]);
         SendFlowControl(DataLength);
	     LnRxSequenceNumber = 0;
      }

      break;
      case ConsecutiveFrame:
	  if(!VbDCAN_SvIgnoredMessage)
	  {
         if (LnMultipleFrameRxState == WaitingForRxBlockOfData)
         { /*--- on first Consecutive Frame ---*/
            LnGoToReceivingBlockOfData();
         }
         LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (MaxTimeFromCfToCfInMs / 1000.0);
         LnRxSequenceNumber++;
         if (LnRxSequenceNumber == 0x0F)
         {
       	   LnRxSequenceNumber = 0;
         }
	  }
      if ((LnMultipleFrameRxState == ReceivingBlockOfData)
          &&(LnRxSequenceNumber == (PCIByte & ConsecutiveFrameSequenceNumberMask)))
      {
        /* LnNbConsFrameRcvdInCurrentBlock++; unused code BSmax always = 0 in GMLAN */
         RemainingNbBytetoReceive = LnServiceDataFrame.DataLength -
                                   LnServiceDataFrame.CurrentDataLength;
         if (RemainingNbBytetoReceive > 7)
         { /*--- remaining number of byte to receive >= 7 ---*/
            if( 8 != GetCANMsg_Buffer_DLC() )
            {
               LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (0);
            }
			else
			{
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
         }
         else
         { // when the data length wrong, don't response
		 	if( RemainingNbBytetoReceive > (GetCANMsg_Buffer_DLC()-1) )
            {
               LnNetworkLayerWaitTimeCounter = C_R7p8125ms16 (0);
            }
			else
			{
		 	/*--- this is the last Consecutive frame of this block
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
      }
      break;
      case PCIFlowControl:
      if ((LnMultipleFrameTxState == WaitingForRxFlowControl)
	  	||(LnMultipleFrameTxState == SendingFirstFrame)
	  	||(LnMultipleFrameTxState == WaitingForRxFlowControlAfterWait))
      {
         if (((PCIByte & UsdtFrameTypePciMask) == PCIFlowControl) 
		&& (GetCANMsg_Buffer_DLC() >= 3))
         { /*--- received Flow Control in transmission ---*/
            if ((PCIByte & FlowControlFlowStatusMask) == FlowControlFlowStatusClearToSend)
            {
               /* LnBSmax = Can8DataBytesArray [1]; unused code, BSmax always = 0 in GMLAN */
               LnSTmin = Can8DataBytesArray [2];
               /*--- conversion from 1 ms or 100us to 7.8125 ms precision since logic called every 7.8125 ms ---*/
               if (LnSTmin < OneMsMaxRange)
               {
                  if ( LnSTmin < CcSYST_BASE_LOOP_1_TIME_x2_ )
                  {
                     LnSTminInBaseLoopSecB = 0;
                  }
                  else if (LnSTmin < CcSYST_BASE_LOOP_1_TIME_x4_)	
                  {
                     LnSTminInBaseLoopSecB = 1;                  
                  }
                  else if (LnSTmin < CcSYST_BASE_LOOP_1_TIME_x6_ )	
                  {
                     LnSTminInBaseLoopSecB = 2;                  
                  }
                  else
                  {
                     LnSTminInBaseLoopSecB = 3;                       
                  }
               }
               else if( (LnSTmin <= 0xF9) &&(LnSTmin >= 0xF1) )
               {
                  /*100 us */
                  LnSTminInBaseLoopSecB = 0;               
               }
               else
               {
	           /*  set minimum time to 25 ms  */
                  LnSTminInBaseLoopSecB = 3;
               }
               LnSTminToBaseLoop = LnSTminInBaseLoopSecB;
			   LnGoToWaitingForTxFirstConsecutiveFrame(EcmCountForTxFirstCF);
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

/*****************************************************************/
/*** CAN Id = $5e8 frame received event                        ***/
/***          Diag UUDT Single Frame (response only)           ***/
/*****************************************************************/
void LnTrspCanId5e8RcvdEvent (Can8DataBytesArrayType Can8DataBytesArray)
{
   PARAM_NOT_USED (Can8DataBytesArray);
} /*** End of LnTrspCanId5e8RcvdEvent ***/

/*******************************************************/
/*** CAN Id = $7df frame received event              ***/
/***          EOBD USDT Functionnal Request          ***/
/*******************************************************/
void LnTrspCanId7dfRcvdEvent (Can8DataBytesArrayType Can8DataBytesArray)
{
   uint8_t PCIByte;
   uint16_t  DataLength;
   PCIByte = Can8DataBytesArray [0];
   DataLength = (uint16_t) (PCIByte & SingleFrameDataLengthPciMask);
   if (((PCIByte & 0xF0) == 0x00) /*--- only Single Frame in functional mode cf spec. ---*/
      && (DataLength > 0 && DataLength < 8)
      && (DataLength < GetCANMsg_Buffer_DLC()))
   {
      SetLnMessageAddressingMode (FunctionalAddressing);
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
      /* unused code, BSmax always = 0 in GMLAN
      else
        {
        if (LnBSmax != BlockSizeNoFurtherFlowControl
            &&
            LnNbConsecutiveFrameTransmitted == LnBSmax)
          {
          LnGoToWaitingForRxFlowControl (FixDefConst ((MaxTimeFromFfOrCfToFcInMs / 1000.0),
                                                       TwTIME_t_R7p8125ms));
          }
        } */
      break;
      case PCIFlowControl:
         if (LnMultipleFrameRxState == SendingFlowControlCts)
         {
            LnGoToWaitingForRxBlockOfData (C_R7p8125ms16 (MaxTimeFromFcCtsToCfInMs / 1000.0));
          }
      break;
   }
} /*** End of LnTrspUsdtRcvdFromEcmEvent ***/

/*********************/
/* CanId5e8RcvdEvent */
/*********************/
void CanId5e8RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnTrspCanId5e8RcvdEvent (*Can8DataBytesArrayPtr);
} /*** End of CanId5e8RcvdEvent ***/

/*********************/
/* CanId7dfRcvdEvent */
/*********************/
void CanId7dfRcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnServiceDataFrame.SourceCanId = CanId7df;
   LnTranspRespUsdtFrameCanId = DiagRespUsdtFrameCanId;
   if(!VbDCAN_SvIgnoredMessage)
   {
      LnTrspCanId7dfRcvdEvent (*Can8DataBytesArrayPtr);
   }
} /*** End of CanId7dfRcvdEvent ***/

/*********************/
/* CanId7e0RcvdEvent */
/*********************/
void CanId7e0RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnServiceDataFrame.SourceCanId = CanId7e0;
   LnTranspRespUsdtFrameCanId = DiagRespUsdtFrameCanId;
   LnTrspUsdtRcvdFromDistantEvent (*Can8DataBytesArrayPtr);   
} /*** End of CanId7e0RcvdEvent ***/

/*********************/
/* CanId7e0RcvdEvent */
/*********************/
void PGNDA00RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnServiceDataFrame.SourceCanId = PGNDA00;
   LnTranspRespUsdtFrameCanId = PGNDA00;
   LnTrspUsdtRcvdFromDistantEvent (*Can8DataBytesArrayPtr);   
} /*** End of CanId7e0RcvdEvent ***/

/*********************/
/*CanIdCALRcvdEvent */
void CanIdCALRcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   	  // LnServiceDataFrame.SourceCanId = KwDCANOBD_CANID;
      LnTranspRespUsdtFrameCanId = DiagRespUsdtFrameCanId;
   	  if(!VbDCAN_SvIgnoredMessage)
   	  {
   		 LnTrspCanId7dfRcvdEvent (*Can8DataBytesArrayPtr);
	  } 
} /*** End of CanIdCALRcvdEvent ***/

/*********************/
/* CanId7e8RcvdEvent */
/*********************/
void CanId7e8RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr)
{
   LnTrspUsdtRcvdFromEcmEvent (*Can8DataBytesArrayPtr);
} /*** End of CanId7e8RcvdEvent ***/

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

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     110401 cjqq       Base on T300 GMLAN Project
*
* ctc_pt3#1.0   SCR:ctc_pt3#578
*       101124 cjqq Changed the dlc of CANID 7df/7e0 at CANOBD_Message_Parameter_Table
* ctc_pt3#2.0   SCR:ctc_pt3#597
*       101215 cjqq Recovered the dlc of CANID 7df/7e0 at CANOBD_Message_Parameter_Table
* ctc_pt3#3.0   SCR:ctc_pt3#665
*       110401 cjqq Improved the error handling function at transport layer
* ctc_pt3#4.0   
*       110921 cjqq code optimized to avoid float operation
* 7  
*       111006 cjqq Fix the bug of no response find in MT22.1IAC project.
* 8  
*       111104 cjqq Define a time for waiting TX first CF when receive FC.
* 9     120307 cjqq Add VbDCAN_SvIgnoredMessage to comply the spec,
*                    when sending not response new require.
*                   fix the bug about 30 00 xx no response.
* 10     120829 cjqq Fix the bug of CAN frame DLC too short in a ConsecutiveFrame.
* 11     120829 cjqq Fix the bug of Behaviour of ECU reception of a segmented 
*                    message interrupted with a FirstFrame after FlowControl.
* 12     121017 xll  Added function CanIdCALRcvdEvent().
* 13     121022 xll  modified function CanIdCALRcvdEvent().
* 14     121213 xll  Bug fix for the status of LnMultipleFrameRxState is not restored 
*                    When ECU send the 32 flow control.
* 15     121224 xjj  Define CcSYST_BASE_LOOP_1_TIME_x2_ CcSYST_BASE_LOOP_1_TIME_x4_ 
*                           CcSYST_BASE_LOOP_1_TIME_x6_ if be not defined.
* 16     130509 xll  Added the logic that terminate the current reception when SF or FF N_PDU arrives
*                    Added the logic when the data length wrong ECM  don't response in CF.
******************************************************************************/


