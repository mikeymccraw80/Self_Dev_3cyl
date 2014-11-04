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
 * %full_name:     ctc_pt3#2/incl/dcanserv.h/4 %
 * %date_created:  Wed Jul  4 16:27:08 2012 %
 * %version:       4 %
 * %derived_by:    hzpcqq %
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

/* service function pointer definition */
typedef void   (*DS_SERVICE_FUNC)(void);
/**
 * @brief Struct type defining a Service.
 *
 * @param Identifier    Specifies the service identifier.
 * @param ServiceFunc   Specifies the service handler function.
 */
typedef struct
{
    uint8_t Identifier;
    DS_SERVICE_FUNC  ServiceFunc;
}DS_SERVICE;

/**
 * @brief Struct type defining a Session.
 *
 * @param Type          Specifies the Diagnostic Session Type.
 * @param Services      Specifies an array of the supported service structs.
 * @param P2ServerMax   Specifies the P2ServerMax timeout for the session.
 * @param P2SServerMax  Specifies the P2*ServerMax timeout for the session.
 */
typedef struct
{
    uint8_t  Type;
    uint8_t  NumServices;
    const DS_SERVICE* Services;
    uint16_t P2ServerMax;
    uint16_t P2SServerMax;
}DS_SESSION;

/**
 * @brief Enum type defining data transfer states.
 *
 * @param DT_IDLE       Idle state of the data transfer entity.
 * @param DT_UPLOAD     Upload data transfer in progress.
 * @param DT_DOWNLOAD   Download data transfer in progress.
 */
typedef enum 
{ 
    DT_IDLE, 
    DT_UPLOAD, 
    DT_DOWNLOAD
}DT_STATE_TYPE;

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
#define SidDynamicallyDefineMessage              (0x2C)   /*---NO ---*/
#define SidRoutineControl                        (0x31)   /*--- YES ---*/
#define SidRequestDownload                       (0x34)   /*--- NO ---*/
#define SidTransferData                          (0x36)   /*--- NO ---*/
#define SidWriteDataByIdentifier                 (0x2E)   /*--- YES ---*/
#define SidWriteMemoryByAddress                  (0x3D)   /*--- NO ---*/
#define SidTesterPresent                         (0x3E)   /*--- YES ---*/
#define SidProgrammingMode                       (0xA5)   /*--- NO ---*/
#define SidReadDiagnosticInformation             (0x19)   /*--- YES ---*/
#define SidReadDataByPacketIdentifier            (0x2A)   /*--- YES ---*/
#define SidInputOutputControlByIdentifier            (0x2F)   /*--- YES ---*/

/*#### DATA TO UPDATE !!!!! ####*/
#define DoJumpToBoot()

/*#### END DATA TO UPDATE !!!!! ####*/
/*--- definition for Tester Present Active state control ---*/
//#define DefaultP3cMaxInMs (5100.0)
//#define DefaultP3cMaxInSec (DefaultP3cMaxInMs/1000)

/* Modified Medium and Fast Rates according to MT80 ETC CAN SPEC (SID2A)*/
#define NoTransmissionPeriod  C_R7p8125ms16 (0.000)
#define SlowRatePeriod        C_R7p8125ms16 (1.000)
#define MediumRatePeriod      C_R7p8125ms16 (0.300)
#define FastRatePeriod        C_R7p8125ms16 (0.100)
/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/
extern volatile LnDiagSvFlagsType LnDiagSvFlags;
extern TwTIME_t_R7p8125ms         LnDiagSecurityDelayTimer;
extern uint8_t                    LnDgSecAccessSpsBadKeyCounter;
extern TwTIME_t_R7p8125ms         S3ServerTimer;
extern TbBOOLEAN                  SPS_Security_Key_Allowed;
extern uint32_t                   LnReadMemByAddrMemToReadPtr;
extern uint16_t                   LnReadMemByAddrNbBytesToRead;
extern const DS_SESSION           DS_Sessions[];
extern DT_STATE_TYPE              DataTransferState; 
extern uint8_t                    LnOldBlockSequenceCounter;
extern uint32_t                   DataTransferByteCounter;
extern uint32_t                   DataTransferAddress;
extern uint32_t                   LnSeed_Random;
extern uint8_t                    CurrentStatusMask;
extern bool                       EmissionDTC;
extern bool                       SupportedDTC;
/*****************************************************************************
 *  Function Exports
 *****************************************************************************/
/*********************************************************************/
/*** Initialize Kw2000 application level service handler.          ***/
/*********************************************************************/
void InitializeLnDiagServices (void);
void InitializeDCAN_Services (void);

/**********************************************************************/
/*** Periodic Keyword 2000 service handle logic (every loop)        ***/
/**********************************************************************/
void UpdateLnDiagServices (void);
TbBOOLEAN GetLnVulnerabilityState (void);
void UnlockSecurityAccess_DCAN (void);
void TriggerSecurityAccessTiming (void);
TbBOOLEAN IsSecurityAccessActivated (void);
/***************************/
/*** function prototypes ***/
/***************************/
void LnEventFunctionalRequest (void);

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
}


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     20100401 cjqq       Base on T300 GMLAN Project
* 2     120409   cjqq       Update the CANOBD per customer requirement 
* 3     120704   cjqq xxxx  Fix the bug of 3rd DTC not right at SID 19 02  
******************************************************************************/
#endif
