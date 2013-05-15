#ifndef DCANSERV_H
#define DCANSERV_H
/******************************************************************************
 *
 * Filename:          dcanserv.h
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    GetGMLN_BroadcastCodeDataValue
 *                    GetGMLN_BroadcastCodeDataByte
 *                    WrtGMLN_BroadcastCodeDataValue
 *                    WrtGMLN_BroadcastCodeDataByte
 *                    GetSecurityAccessSeed
 *                    GetSecurityAccessKey
 *                    GetGMLN_LnCommActive
 *                    GetLnDiagServicesDisableDTCs
 *                    IsDiagDownloadRequestRequested
 *                    IsDiagTransferDataRequested
 *                    IsDownLoadGranted
 *                    LnDiagDecrementMEC
 *                    IsSecurityAccessUnlocked
 *                    GetLnEMS_LrnRstRqstPend
 *                    GetJulianDayByteOne
 *                    GetJulianDayByteTwo
 *                    GetJulianDayByteThree
 *                    GetUPS_SeqSerialNumber
 *
 * Forward Engine Management Systems
 *
 * Copyright 2006-2008 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#24/incl/dcanserv.h/3 %
 * %date_created:  Fri Sep 17 10:21:32 2010 %
 * %version:       3 %
 * %derived_by:    lz37cb %
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
#include "obdltype.h"
#include "timepcvc.h"


typedef
    struct
      {
      bitfield16_t ReadOnly:                   1;
      bitfield16_t ReadProtected:              1;
      bitfield16_t WriteProtected:             1;
      bitfield16_t Hidden:                     1;
      } MemoryAccessType;

typedef
  struct
    {
    uint32_t          StartAddress; 
    uint32_t          EndAddress;
    uint32_t          VirtualAddressConversion;
    MemoryAccessType  MemoryAccess;
    }
  MemoryMapType;

typedef void (*LnDiagFunctionPtrType)(void);

/*--- MT80 Diagnostic Services Id Requests ---*/ /*--- Implemented: ---*/

#define SidRequestCurrentPowertrainDiagData       (0x01)   /*--- YES ---*/
#define SidRequestPowertrainFreezeFrameData     (0x02)   /*--- YES ---*/
#define SidRequestEmmissionPowertrainDTC          (0x03)   /*--- YES ---*/
#define SidClearDiagnosticInformation                    (0x04)   /*--- YES ---*/
#define SidRequestO2SensorMonitoringTestResult  (0x05)   /*--- NO ---*/
#define SidRequestOnBoardTestResult                     (0x06)   /*--- YES ---*/
#define SidRequestOnBoardTestResultContinuous   (0x07)   /*--- YES ---*/
#define SidRequestControlOnBoardTest                   (0x08)   /*--- NO ---*/
#define SidRequestVehicleInformation                    (0x09)   /*--- YES ---*/
#define SidRequestEmmissionPermanentDTC          (0x0A)   /*--- NO ---*/

#define SidInitiateDiagnosticOperation           (0x10)   /*--- YES ---*/
#define SidEcuReset                                         (0x11)   /*--- YES ---*/
#define SidReadFailureRecordData                 (0x12)   /*--- NO ---*/
#define SidClearDiagInformation                  (0x14)   /*--- YES ---*/
#define SidReadDataByIdentifier                  (0x1A)   /*--- NO ---*/
#define SidReturnToNormalMode                    (0x20)   /*--- NO ---*/
#define SidReadDataByCommonIdentifier            (0x22)   /*--- YES ---*/
#define SidReadMemoryByAddress                   (0x23)   /*--- YES ---*/
#define SidSecurityAccess                        (0x27)   /*--- YES ---*/
#define SidDisableNormalCommunication            (0x28)   /*--- YES ---*/
#define SidDynamicallyDefineMessage              (0x2C)   /*---NO ---*/
#define SidRoutineControl                        (0x31)   /*--- YES ---*/
#define SidRequestDownload                       (0x34)   /*--- NO ---*/
#define SidTransferData                          (0x36)   /*--- NO ---*/
#define SidWriteDataByIdentifier                 (0x2E)   /*--- YES ---*/
#define SidWriteMemoryByAddress                  (0x3D)   /*--- NO ---*/
#define SidTesterPresent                         (0x3E)   /*--- YES ---*/
#define SidReportProgrammedState                 (0xA2)   /*--- YES ---*/
#define SidProgrammingMode                       (0xA5)   /*--- NO ---*/
#define SidReadDiagnosticInformation             (0x19)   /*--- YES ---*/
#define SidReadDataByPacketIdentifier            (0x2A)   /*--- YES ---*/
#define SidInputOutputControlByIdentifier            (0x2F)   /*--- YES ---*/

#define DIdECUDiagnosticAddress                  (0xB0)     /*--- Read only  */
#define ECUDiagnosticAddress                     (0x11)


/*#### DATA TO UPDATE !!!!! ####*/
#define DoJumpToBoot()
#define DevalidateNvMemory()
/*#### END DATA TO UPDATE !!!!! ####*/
/*--- definition for Tester Present Active state control ---*/
//#define DefaultP3cMaxInMs (5100.0)
//#define DefaultP3cMaxInSec (DefaultP3cMaxInMs/1000)

/*--- Data Identifier list definition (SID2E)---*/
/*---------------------------------------*/
#define DIdCrankshaftAdaptiveCylinder            (0x010a)
#define DIdTECDSampleCounter                     (0x010b)
#define DIdVehicleIdentificationNumber            (0xf190)
#define DIdRepairShopCodeOrTesterSerialNumber    (0xf198)
#define DIdProgrammingDate                       (0xf199)
#define DIdManufacturersEnableCounter            (0x01a0)

/* Modified Medium and Fast Rates according to MT80 ETC CAN SPEC (SID2A)*/
#define NoTransmissionPeriod  C_R7p8125ms16 (0.000)
#define SlowRatePeriod        C_R7p8125ms16 (1.000)
#define MediumRatePeriod      C_R7p8125ms16 (0.300)
#define FastRatePeriod        C_R7p8125ms16 (0.100)


/*-----------------------------------------------*/
/*--- RECEIVE / TRANSMIT BUFFERS DISTRIBUTION ---*/
/*-----------------------------------------------*/
#define TX_MSG_BUFFER_NUMBER      (18)
   /* effective number of Tx msg allocated */

#define Buffer0        (0x0)
#define Buffer1        (0x1)
#define Buffer2        (0x2)
#define Buffer3        (0x3)
/*--------------------------------------------------------------------*/
/*--- AFFECTATION OF CAN MESSAGES TO THE DIFFERENT RECEIVE BUFFERS ---*/
/*--------------------------------------------------------------------*/
/*---      .                                                       ---*/
/*---     / \     the following definition must follow the naming  ---*/
/*---    / | \    convention:                                      ---*/
/*---   /  |  \   "Buffer"+"Can_message_ID"                        ---*/
/*---  /   |   \                                                   ---*/
/*---  ---------                                                   ---*/
/*--------------------------------------------------------------------*/

#define BufferCanId7df                (Buffer0)
#define BufferCanId7e0                (Buffer1)
#define BufferCanId6fb                 (Buffer2)
#define BufferCanId101                 (Buffer3)
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

#define      CyEEPROM_SectionStart    ((uint32_t)0x000800L)
#define      CyEEPROM_SectionEnd      ((uint32_t)0x000FFFL)


/*****************************************************************************
 *  Type declaration
 *****************************************************************************/
typedef TwTIME_t_R7p8125ms      PeriodicTransmissionRateType;

typedef
struct
{
   uint8_t                    NbOneShotTxRequested; /*--- 0 = No Tx requested ---*/
                                                       /*--- 1 = 1 Tx requested ---*/
                                                       /*--- 2 = 2 Tx requested ... ---*/
   TwTIME_t_R7p8125ms             PeriodicTransmissionRate;
   TwTIME_t_R7p8125ms             PeriodCounter;
}
LnDpidTxSchedulerType;

typedef enum
{
  LnNoAction,
  LnAction_JumpToBoot
} LnDelayedActionT;

typedef
  struct
    {
    bitfield16_t PreviousCommState:                 1;
    bitfield16_t SecurityAccessUnlocked:            1;
    bitfield16_t ECUResetPending:                   1;
    bitfield16_t WaitingForWriteDataByIdToComplete: 1;
    bitfield16_t UnusedBit3:                        1;
    bitfield16_t UnusedBit2:                        1;
    bitfield16_t TransferDataRequested:             1; 
    bitfield16_t DownLoadRequested:                 1;
    
    bitfield16_t DownLoadGranted:                   1;
    bitfield16_t ReprogramWdgCalPending:            1;
    bitfield16_t SendingOneShotDpidResponse:        1;
    bitfield16_t ReadMemoryByAddressActive:         1;
    bitfield16_t ReadSupportedDTCActive:           1;
    bitfield16_t DeviceControlActive:               1;
    bitfield16_t SmallGmLan:                        1;
    }
  LnDiagSvFlagsType;

/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/
extern volatile LnDiagSvFlagsType LnDiagSvFlags;
extern bool               LnDiagServicesDisableDTCs;
extern bool               LnEMS_LrnRstRqstPend;
extern uint8_t CurrentSessionIndex;
extern bool   ExtendedDiagnosticSessionControl;
extern TwTIME_t_R7p8125ms        S3ServerTimer;
extern uint8_t             *LnDownloadDestinationBufferPtr;
/*****************************************************************************
 *  Function Exports
 *****************************************************************************/
/*********************************************************************/
/*** Initialize Kw2000 application level service handler.          ***/
/*********************************************************************/
void InitializeLnDiagServices (void);
extern void InitializeDCAN_Services (void);
/**********************************************************************/
/*** Periodic Keyword 2000 service handle logic (every loop)        ***/
/**********************************************************************/
void UpdateLnDiagServices (void);
//void UpdateDCAN_Services (void);
void ChangeSession(uint8_t newSession);
/***************************/
/*** function prototypes ***/
/***************************/
void LnEventFunctionalRequest (void);

/**********************************************************************/
/*** Disable DTCs status.                                           ***/
/**********************************************************************/
INLINE bool GetLnDiagServicesDisableDTCs (void)
{
   return LnDiagServicesDisableDTCs;
} /*** End of GetLnDiagServicesDisableDTCs  ***/

/**********************************************************************/
/*** Is DownLoad Granted                                            ***/
/**********************************************************************/
/* Note: The purpose of the ifdef is to disable the "download granted logic in case
   the application does not support the download to RAM. The MiniCom or Small Gmlan
   feature is for manufacturing and disables the update of variables which are not
   updated in manufacturing mode. */

INLINE bool IsDownLoadGranted (void)
  {
  return false;
  } /*** End of IsDownLoadGranted ***/

/**********************************************************************/
/*** Get Security Access flag state.                                ***/
/*** Gives the state of the vulnerability.                          ***/
/*** If the vulnerability is true, then any service is available,   ***/
/*** else need to receive an Access Security service first.         ***/
/**********************************************************************/

INLINE bool IsSecurityAccessUnlocked (void)

  {
  return LnDiagSvFlags.SecurityAccessUnlocked;
  } /*** End of IsSecurityAccessUnlocked ***/

/**********************************************************************/
/***  Return EMS learn reset request.                               ***/
/**********************************************************************/
INLINE bool GetLnEMS_LrnRstRqstPend (void)
{
   return (false);
   //return LnEMS_LrnRstRqstPend;
}

/***************************************/
/*** DisableAllCanIntExceptGmlanDiag ***/
/***************************************/

/* Mask shall be replaced by explicit disabling of CAN frame */
#define CanDiagSvOnlyInterruptEnableMask    (0x4800)


/*************************/
/* DisableCanInterrupts  */
/*************************/
INLINE void DisableCanInterrupts (uint16_t DisableCanInterruptMask)
  {
  /*** Implement a strategy to disable CAN message individually ***/
  /*** we only need to disable normal CAN messages but not GMLAN***/
  /*** messages for reprogramming                               ***/
//  PARAM_NOT_USED (DisableCanInterruptMask);
  } /*** End of DisableCanInterrupts ***/


INLINE void DisableAllCanIntExceptGmlanDiag (void)

  {
  DisableCanInterrupts ((uint16_t)~CanDiagSvOnlyInterruptEnableMask);
  } /*** End of DisableAllCanIntExceptGmlanDiag ***/


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     060215 cr       Created from TCL version (archive cvs partition op36cm)
*
* 2.0   061120 wzq3zj   modified to support field GMLan re-programming
*tcb_pt1#4
*       070629 abh      Modified to implement non legislative services for J300
* tci_pt3#4
*       070320 abh      Modified seed and key address
* tcb_pt1#xxx
*       070629 abh      Defined GetLnEMS_LrnRstRqstPend(), declared LnEMS_LrnRstRqstPend
* tci_pt3#4.1.2.2.1
*       080115 VP  6563 Added GetJulianDay and GetUPS_SeqSerialNumber.
* tcb_pt1#4.1.3
*       080123 me  6754 Added Mode 0x0A support.
* tci_pt3#4.1.2.2.2
*       080402 VP  6833 Modified the Addresses
*                       CgGMLN_SideRailAddress,CgGMLN_DelphiBaseModelPNAddr.
* ---------------------------------------------------------------------
* After RSM 6865 Communication Project Clean up
* ---------------------------------------------------------------------
* tcb_pt1#2
*       080613  mt -BM- Manually Merged in changes from RSMs created
*                       from an old J300 baseline before the COMM cleanup.
*
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
* 4.0  100915    hdg  xxx  Added service ID for implementing CAN Flash in MT22.1 paltform.
* 3    100917    wj  CTC RSM8069
*                          Updated for CAN re-flash
*
******************************************************************************/
#endif
