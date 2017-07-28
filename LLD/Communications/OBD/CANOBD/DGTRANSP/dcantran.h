#ifndef DCANTRAN
#define DCANTRAN
/*-------------------------------------------------------------------*/
/* filename -  DCANTRAN.H                                            */
/*                                                                   */
/*    This module is GMLAN transport layer of the DELPHI Delco       */
/*    engine control s/w, where the GMLAN messages transmission      */
/*    or reception are processed.                                    */
/*    This layer is composed of two layers:                          */
/*    - application interface layer :                                */
/*      it is the interface to the application which provides the    */
/*      access functions to the data of the received frames and for  */
/*      the transmission of the application frames.                  */
/*    - Network layer in charge of the transmission and reception    */
/*      of the different frames using segmentation if needed.        */
/*                                                                   */
/*    LN stands for Local Network                                    */
/*                                                                   */
/* list of function(s):                                              */
/*  Proto:                                                           */
/*          InitializeLnTransportLayer                               */
/*          LnBuildCan8DataBy8Functions                              */
/*          UpdateLnTransportLayer                                   */
/*          LnGoToWaitingForRxFirstOrSingleFrame                     */
/*          LnSendMessage                                            */
/*          LnSendUudtMessage                                        */
/*                                                                   */
/*          GetLnServNbOfFreeBytesInRingBuffer                       */
/*          GetLnServNbOfUsedBytesInRingBuffer                       */
/*          StoreLnServNbBytesInRingBuffer                           */
/*          LntrspCanId100RcvdEvent                                  */
/*          LntrspCanId101RcvdEvent                                  */
/*          LntrspCanId102RcvdEvent                                  */
/*          LntrspCanId5e8RcvdEvent                                  */
/*          LntrspCanId7e0RcvdEvent                                  */
/*          LntrspCanId7e8RcvdEvent                                  */
/*                                                                   */
/*  Inline:                                                          */
/*          GetLnAnswerStillBeingSent                                */
/*          GetLnReceptionCompleteMsgWaiting                         */
/*                                                                   */
/*          GetLnFunctionalAddress                                   */
/*          GetLnIndexOfValidDataNotOverwrittenYet                   */
/*          GetLnServiceData                                         */
/*          GetLnServiceDataServiceId                                */
/*          GetLnServiceDataSubFunctParameter                        */
/*          GetLnServiceDataByIndex                                  */
/*          GetLnServiceCurrentLastDataIndex                         */
/*          GetLnServiceSourceCanId                                  */
/*          GetLnServiceCurrentDataLength                            */
/*          GetLnServiceDataLength                                   */
/*          GetLnServReqMsgAddressingMode  (Functional or Phys.)     */
/*          GetLnIndexOfFirstFreeDataForWrite                        */
/*          SetLnMessageAddressingMode                               */
/*          WriteLnServiceDataByIndex                                */
/*          WriteLnMessageDataLength                                 */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/* DELPHI Delco Luxembourg C Engine Management Software              */
/* (c) Copyright DELPHI Delco Electronics System 2001                */
/*-------------------------------------------------------------------*/

 /****************************************************************************
 *
 * Current Module Info:
 * %full_name:      lux_pt1#1/incl/dcantran.h/1 %
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
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
/******************************************************************************
 *  Library Include Files
 *****************************************************************************/
#include "obdsbase.h"
/*********************************/
/* GENERIC CAN TYPES DEFINITION  */
/*********************************/
typedef uint16_t  CanIdType;
typedef uint8_t Can8DataBytesArrayType [8];
typedef uint8_t LnTrspTimeOutErrorType;

#define DataLengthInBytes         (8)
#define RX_MSG_BUFFER_NUMBER      (3) /* effective number of Rx msg allocated */
                                       /* Don't forget the ccp can msg 4 Tx + 2 Rx */
/*--- the ISO spec concerning frame data length indicates 4095 bytes
      as the maximum data bytes that can be transmitted (of course segmented) ---*/ 
#define DataBufferSize (261) /*--- 261 = for service Write Data by Identifier
                                     + Did Write Data By Address
                                     + 3 bytes address
                                     + 256 bytes of data ---*/
typedef
  enum
    {
    WaitingForRxFirstOrSingleFrame,
    SendingFlowControlWait,
    SendingFlowControlCts,
    WaitingForRxBlockOfData,
    ReceivingBlockOfData,   /*--- receiving USDT Consecutive Frames ---*/
    WaitingForRxRingBufferNotFull, /*--- waiting application to fill out ---*/
    ReceptionCompleteMsgWaiting
    }
  LnMultipleFrameRxStateType;


typedef
  enum
    {
    NotSending,
    SendingSingleFrame,
    SendingFirstFrame,
    WaitingForRxFlowControl, /*--- after Transmitted First Frame ---*/
    WaitingForRxFlowControlAfterWait,
    WaitingForTxFirstConsecutiveFrame,
    SendingBlockOfData,   /*--- sending USDT Consecutive Frames ---*/
    WaitingForBlockFrameTx, /*--- wait till frame from SendingBlockOfData has been sent ---*/
    WaitingDataForTxInRingBuffer /*--- waiting transmission to fill out ---*/
    }
  LnMultipleFrameTxStateType;

typedef
  struct
    {
    uint8_t   PCIByte;
    uint8_t   BSmax;
    uint8_t   STmin;
    uint8_t   Unused1;
    uint8_t   Unused2;
    uint8_t   Unused3;
    uint8_t   Unused4;
    uint8_t   Unused5;
    }
  LnUsdtFlowControlFrameType;


typedef struct {
    CanIdType   SourceCanId;
    uint16_t    AddressingMode; /*--- 0 = Physical, 1 = Functional ---*/
    uint16_t    CurrentDataLength; /*--- is the current data byte nb written in the 
                                         data ring buffer ---*/ 
    uint16_t    DataLength;
    uint16_t    IndexOfValidDataNotOverwrittenYet; /*--- because of ring buffer ---*/
    uint8_t     Data [DataBufferSize]; /*--- data ring buffer ---*/
} LnServiceDataFrameType;

typedef uint8_t CanDataByteArrayType [DataLengthInBytes];

typedef
struct
{
   uint16_t State; /*--- VioRxBufferNotActive = 0 = not active  ---*/
                    /*--- VioRxBufferEmpty     = 1 = empty       ---*/
                    /*--- VioRxBufferBusy      = 2 = busy (being ---*/
                    /*---         filled by a new receive frame  ---*/
                    /*--- VioRxBufferFull      = 3 = full        ---*/
                    /*--- VioRxBufferOverrun   = 4 = overrun     ---*/
   CanDataByteArrayType DataBytes;
}
VioCanRxBufferStructType;

/*********************************************************************/
/*** Definitions for Network Layer and application interface layer ***/
/*********************************************************************/
#define PhysicalAddressing           (0)
#define FunctionalAddressing         (1)
#define FunctionalAddressingAllNodes (2)

#define ExtendedAddressing		     (3)

/****************************************************/
/*   Definition of CAN messages by their CAN IDs    */
/****************************************************/
#define CanId5e8                  (0x5e8) /*--- Transmitted but must also be Received ---*/
#define CanId7df                  (0x7df)
#define CanIdCAL                  (0x000)
#define CanId7e0                  (0x7e0)
#define CanId7e8                  (0x7e8) /*--- Transmitted but must also be Received ---*/


#define TXIndxCanIdCAL   (2)
#define IndxCanIdCAL     (4)
/********************************/
/*** CANOBD Response CAN Id ***/
/******************************8*/
//#define DiagRespUudtSingleFrameCanId      (CanId5e8)
#define DiagRespPhysclRespPeriodicCanId   (CanId5e8)

/*** CAN Id definition for all USDT response frames (single, First, consecutive ***/
/*** and FlowControl) when request is issued by the tester (CAN id = $7e0)      ***/
/*** for diagnostic needs                                                       ***/
#define DiagRespUsdtFrameCanId            (CanId7e8)

/****************************************************************/
/*** Definitions for Network Layer Addressing Modes           ***/
/****************************************************************/
//#define UsdtFrameVnidFunctionalAllNodes  (0xFE)

/*************************************************/
/*** Definitions for Network Layer USDT frames ***/
/*************************************************/
#define UsdtFrameTypePciMask               (0xF0)
#define SingleFrame                        (0x00)
#define FirstFrame                         (0x10)
#define ConsecutiveFrame                   (0x20)
#define ConsecutiveFrameSequenceNumberMask (0x0F)
#define PCIFlowControl                     (0x30)
#define FlowControlFlowStatusMask          (0x0F)
#define FlowControlFlowStatusClearToSend   (0x00)
#define FlowControlFlowStatusWait          (0x01)
#define FlowControlFlowStatusoverflow      (0x02)
#define BlockSizeNoFurtherFlowControl      (0)
#define SingleFrameDataLengthPciMask       (0x0F)

/**************************************************/
/*** Definitions of Network Layer Waiting times ***/
/**************************************************/
#define MaxTimeFromFfOrCfToFcInMs (75) /*--- Max time to wait after the transmission
                                               of the First Frame and the reception
                                               of the Flow Control ---N_Bs*/
#define MaxTimeFromFcCtsToCfInMs  (150) /*--- Max time to wait after the transmission
                                               of the FC CTS (with BS and STmim) and
                                               the reception of the first Consecutive
                                               Frame ---N_Cr*/
#define MaxTimeFromCfToCfInMs     (1000) /*--- Max time between the reception of 2
                                               Consecutive Frames ---*/
#define MaxTimeFromFcWtToFcInMs   (75) /*--- Max time to wait after the reception
                                               of the Flow Control Wait frame and the
                                               reception of the next Frame ---*/ 
#define MinimumSeparationTimeInMs (2)    /*--- the minimum separation time of this
                                               application is defined here of 2 ms
                                               to avoid throughput problem.
                                               (each reception of a consecutive frame
                                               generates an interrupt ...) ---*/
#define EcmTimeFromFcWtToFcWtInMs (900)  /*--- time to wait after the transmission
                                               of the Flow Control Wait frame and the
                                               transmission of the next Flow Control
                                               Wait Frame ---*/ 
#define MaxTimeForSengingOneFrameInMs (50)  /*--- max time to wait for our trannsmission ---*/

#define EcmCountForTxFirstCF (2)/*--- wait count to Tx FirstConsecutiveFrame ---N_Cs*/
/*********************************************************************/
/*** Definitions of time-out errors of Network Layer Waiting times ***/
/*********************************************************************/
#define NetworkLayerNoTimeOutError   (0)

#define CanFrameNotTransmitedOnTime  (1)
#define TimeOutFromFfOrCfToFc        (2)
#define TimeOutFromFcCtsToCf         (3)
#define TimeOutFromCfToCf            (4)
#define TimeOutFromFcWtToFc          (5)

/*** WARNING : Buffer can not be allocated beyond 24 as 8 buffers are used for Transmit msgs ***/
/*-----------------------------------------------------------------*/
/*--- VIO RECEIVE MESSAGES TYPES DEFINITION                        */
/*--- (for Received messages which have a buffer in Virtual IO) ---*/
/*-----------------------------------------------------------------*/
#define VioRxBufferNotActive (0)
#define VioRxBufferEmpty     (1)
#define VioRxBufferBusy      (2)
#define VioRxBufferFull      (3)
#define VioRxBufferOverrun   (4)

/*************************/
/*** data declaration  ***/
/*************************/ 
extern LnServiceDataFrameType      LnServiceDataFrame;
extern bool                     LnServiceDataBeingInserted;
extern uint16_t                   LnNbOfUsedBytesInRingBuffer;
extern LnMultipleFrameTxStateType  LnMultipleFrameTxState;
extern LnMultipleFrameRxStateType  LnMultipleFrameRxState;
extern uint16_t                    NbOfBytesStillToTransmit;
extern uint8_t                     LnSequenceNumber;
extern bool                        VbDCAN_SvIgnoredMessage;
/***************************/
/*** function prototypes ***/
/***************************/
uint16_t GetLnServNbOfFreeBytesInRingBuffer (void);
uint16_t GetLnServNbOfUsedBytesInRingBuffer (void);
bool StoreLnServNbBytesInRingBuffer (uint16_t  NbBytesToStore,
                                        uint8_t *SourceBufferPtr); 
bool RetrieveLnServNbBytesFromRingBuffer (uint16_t  NbBytesToRetrieve,
                                             uint8_t *DestinationBufferPtr);
void LnSendMessage (void);
void InitializeLnTransportLayer (void);
void UpdateLnTransportLayer (void);
void LnGoToWaitingForRxFirstOrSingleFrame (void);
void CanId5e8RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr);
void CanId7dfRcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr);
void CanId7e0RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr);
void CanIdCALRcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr);
void CanId7e8RcvdEvent (Can8DataBytesArrayType *Can8DataBytesArrayPtr);
void RequestCanToTransmit (CanIdType CanId,
                           Can8DataBytesArrayType *Can8DataBytesArray);

/*************************************/
/*** GetLnServReqMsgAddressingMode ***/
/**************************************************************************/
/*** returns: 0 if the current service request is physical addressing   ***/
/***          1 if the current service request is Functional addressing ***/
/**************************************************************************/
INLINE uint16_t GetLnServReqMsgAddressingMode (void)
{ 
   return LnServiceDataFrame.AddressingMode;
} /*** End of GetLnServReqMsgAddressingMode ***/

/**********************************/
/*** SetLnMessageAddressingMode ***/
/*************************************************/
/*** AddressingMode: 0 = physical addressing   ***/
/***                 1 = Functional addressing ***/
/*************************************************/
INLINE void SetLnMessageAddressingMode (uint16_t AddressingMode)
{ 
  LnServiceDataFrame.AddressingMode = AddressingMode;
} /*** End of SetLnMessageAddressingMode ***/

/************************/
/*** GetLnServiceData ***/
/**********************************************************************/
/*** this routine returns a pointer to the array of data describing ***/
/*** the current GMLAN service.                                     ***/
/**********************************************************************/
INLINE uint8_t *GetLnServiceData (void)
{
   return LnServiceDataFrame.Data;
} /*** End of GetLnServiceData ***/

/*********************************/
/*** GetLnServiceDataServiceId ***/
/*************************************************************/
/*** this routine returns the service Id = first data byte ***/
/*** in the current GMLAN service.                         ***/
/*************************************************************/
INLINE uint8_t GetLnServiceDataServiceId (void)
{
   return LnServiceDataFrame.Data [0];
} /*** End of GetLnServiceDataServiceId ***/

/*****************************************/
/*** GetLnServiceDataSubFunctParameter ***/
/**********************************************************************/
/*** this routine returns the subfunction parameter first parameter ***/
/*** after the service Id in the current GMLAN service.             ***/
/**********************************************************************/
INLINE uint8_t GetLnServiceDataSubFunctParameter (void)
{
   return LnServiceDataFrame.Data [1];
} /*** End of GetLnServiceDataSubFunctParameter ***/

/******************************/
/*** GetLnServiceDataLength ***/
/******************************/
INLINE uint16_t GetLnServiceDataLength (void)
{
   return LnServiceDataFrame.DataLength;
} /*** End of GetLnServiceDataLength ***/

/********************************/
/*** WriteLnMessageDataLength ***/
/********************************/
INLINE void WriteLnMessageDataLength (uint16_t DataLength)
{ 
   if (DataLength < 4095)
   {
      LnServiceDataFrame.DataLength = DataLength;
   }
   else
   {
      LnServiceDataFrame.DataLength = 4095;
   } 
} /*** End of WriteLnMessageDataLength ***/

/*********************************************************************/
/*** Load a data to a location of  the transmit data buffer        ***/
/*********************************************************************/
INLINE void WrtDCAN_ServiceData( BYTE in_data, BYTE in_location )
{
   (GetLnServiceData ()) [in_location]= in_data;//bankim
}

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     060215 cr       Created from TCL version (archive cvs partition op36cm)
* 2     080117 HHO CR28 Integrated Immobilizer id $3c1 and $3c9 from GMW 7349
* 3     110228 cjqq  change MaxTimeFromFfOrCfToFcInMs from 1000 to  75ms
* 4     111104 cjqq define a time for waiting TX first CF when receive FC.
* 5     120307 cjqq change MaxTimeFromFcWtToFcInMs to 75ms
* 5     121017 xll  add CAN ID 0x600 for extended service functional addressing
* 6     121022 xll  modified the value of CanIdCAL from 0x600 to 0x000.
* 7     130509 xll  Change N_Cr from 1000ms to 150ms
******************************************************************************/

