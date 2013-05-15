/******************************************************************************
 *
 * Filename:          dcanserv.c
 *
 * Global Functions Defined:
 *                    LnActivateTesterPresent
 *                    LnInitiateDiagnosticOperation
 *                    LnReadFailureRecordData
 *                    SendLnPosAnswerToReadDataById
 *                    LnReadDataByIdentifier
 *                    LnReturnToNormalMode
 *                    UpdateLnReadMemoryByAddress
 *                    FindMatchingMemoryArea
 *                    LnReadMemoryByAddress
 *                    UpdateLnReadFailureRecordAllParam
 *                    LnReadFailureRecordAllParam
 *                    LnSecurityAccess
 *                    LnRespondToDisableNormComAfterFlush
 *                    LnDisableNormalCommunication
 *                    LnDynamicallyDefineMessage
 *                    LnRequestDownload
 *                    DownloadDataAndAnswerContinued
 *                    RespOutOfRangeWhenRxCompleteReq
 *                    DownloadDataAndAnswer
 *                    LnTransferData
 *                    WriteMemoryByAddress
 *                    LnWriteDataByIdentifier
 *                    LnReadStatusOfDTCByDTCNumber
 *                    UpdateReadStatusOfDTCByStatusMask
 *                    LnReadStatusOfDTCByStatusMask
 *                    ContinuousTesterPresentCheck
 *                    LnSendOnChangeReportingOfDTC
 *                    LnReadDiagnosticInformation
 *                    LnBuildAndTxCan8Data
 *                    ClearAndDisableAllDpids
 *                    UpdateReadDataByPacketIdentifier
 *                    TellIfDpidIsSupported
 *                    GetIndexOfDpidInSchedulerTable
 *                    TellIfDpidByIndexIsAlreadyScheduled
 *                    UpdateNumberOfDpidCurrentlyScheduled
 *                    ScheduleDpidByIndexAndTxPeriodRate
 *                    StopSendingPeriodicDpid
 *                    LnEventFunctionalRequest
 *                    UpdateLnDiagServices
 *                    InitializeLnDiagServices
 * Static Functions Defined:
 *                    LnReadDataByPacketIdentifier
 * Inline Functions Defined:
 *                    LockSecurityAccess
 *                    UnlockSecurityAccess_DCAN
 *                    GetSeed
 *                    GetKey
 *                    InitializeSecurityAccessTiming
 *                    TriggerSecurityAccessTiming
 *                    LnDeactivateTesterPresent
 *                    GetStartAddress
 *                    GetVirtualAddress
 *                    GetEndAddress
 *                    CopyBlockInRamWithIntegrity
 *                    LnTesterPresent
 *                    LnReportProgrammedState
 *                    LnProgrammingMode
 *                    InitializeReadDataByPacketIdentifier
 *                    ScheduleReadDataByPacketIdentifier
 *                    GetNbDpidScheduledAtRate
 *                    LnReadDataByCommonIdentifier
 *                    InitializeLnDiagSvSecurityAccess
 *                    InitNormalCommEnablingConditions
 *
 * Forward Engine Management Systems
 *
 * Copyright 9999-2009 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     lux_pt1#1/csrc/lndiagsv.c/1 %
 * %date_created:  Wed Feb 15 18:20:47 2006 %
 * %version:       1 %
 * %derived_by:    c23cr %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "obdsfapp.h" /*Get_Message(),VyCANH_Current_message_Number*/

/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanserv.h"  /* for LnDiagSvFlagsType, LnDiagSvFlags */
#include "dcanlegi.h"   /*for legist service*/
//#include "dcancpid.h" /*LnInputOutputControlByIdentifier()*/
#include "dcanfapi.h"
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
//#include "cmnpidapi.h"
//#include "cmndtc.h"
//#include "cmndtcapi.h"
//#include "cmnpid.h"
#include "kw2app.h"
#include "kw2api.h"
#include "kw2srv10.h"
#include "kw2srv10m.h"
#include "dd_nvram.h"
#include "kw2srv31.h"
//#include "kw2nvmd.h"/*WrtVinDataByte*/
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"   /* for SubFunctionNotSupported_InvalidFormat..*/
//#include "dcantran.h" /*GetLnServiceData()*, RequestCanToTransmit()*/
//#include "cmndtc.h"/*DTC_TEST_STATUS_INFO_TYPE*/
//#include "obdsfexi.h"/* GetCMNDTC_InternalHistFaultFlag*/  
#include "obdlfsrv.h"
#include "kw2app.h"

/*--- the transmission speed is of 7 data bytes per 10 ms because
      of the design of the tranport layer.
      So between 7 bytes are normally transmitted between 2 calls
      to UpdateLnReadMemoryByAddress () = 10 ms.
      The application fills the Tx buffer by packet of 20 bytes
      as soon as there is enough free bytes in the Tx buffer. ---*/
#define PacketNbOfBytesToTransfer (20)

/******************************************************************************
 *  Global Variables
 *****************************************************************************/
bool               ExtendedDiagnosticSessionControl;
uint8_t           CurrentSessionIndex;
volatile LnDiagSvFlagsType      LnDiagSvFlags;
TwTIME_t_R7p8125ms             S3ServerTimer;
/*unused varable*/
LnDiagFunctionPtrType            LnDiagRoutinePtr;
bool               LnDiagServicesDisableDTCs;
bool               LnEMS_LrnRstRqstPend;
uint8_t              LnReadMemByAddrData [PacketNbOfBytesToTransfer];
GLOBALPOINTER_BYTE_T  LnCAN_PhysicalAddress; 
uint8_t             *LnDownloadDestinationBufferPtr;
/******************************************************************************
 * Static Variables
 *****************************************************************************/
static WORD SwIndex_buffer=0, SwLocation_num_of_PIDs=0;
static WORD CurrentDtcInedx;
static WORD CurrentDataInedx;
static LnDelayedActionT             LnDelayedAction;
static uint16_t      NbOfPeriodicDpidCurrentlyScheduled;
static TwTIME_t_R7p8125ms      LnDiagSecurityDelayTimer;
static uint8_t        LnDgSecAccessSpsBadKeyCounter;
static LnDiagFunctionPtrType LnDiagResponsePendingFunctionPtr;
static uint32_t      LnReadMemByAddrMemToReadPtr;
static uint16_t      LnReadMemByAddrNbBytesToRead;
static bool           SPS_Security_Key_Allowed;

/*unused varable*/
static uint8_t        First_msg_queued;
/******************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/
extern uint16_t    LnNbOfUsedBytesInRingBuffer;
//extern BYTE VyCANH_Current_message_Number;
/**********************************************************************/
/*** Function prototype                                             ***/
/**********************************************************************/
//void ClearAndDisableAllDpids (void);
void LnReadFailureRecordAllParam (void);
//extern FAR_COS void ClearOFVC_AllDeviceControlParameters (void);
/**********************************************************************/
/*** Inline Function prototype                                             ***/
/**********************************************************************/
INLINE void InitializeSecurityAccessTiming (void);
/**********************************************************************/
/*** type define                                             ***/
/**********************************************************************/

/**********************************************************************/
/*** Lock Security Access.                                          ***/
/**********************************************************************/
INLINE void LockSecurityAccess_DCAN (void)
{
   LnDiagSvFlags.SecurityAccessUnlocked = false;
} /*** End of LockSecurityAccess ***/

/**********************************************************************/
/*** Unlock Security Access.                                        ***/
/**********************************************************************/
INLINE void UnlockSecurityAccess_DCAN (void)
{
   LnDiagSvFlags.SecurityAccessUnlocked = true;
} /*** End of UnlockSecurityAccess_DCAN ***/

/*********************************************************************/
/***   Get Security Access flag state.                             ***/
/*********************************************************************/
INLINE TbBOOLEAN GetLnVulnerabilityState (void)
{
   return LnDiagSvFlags.SecurityAccessUnlocked;
}

static void LoadCANServiceDataFromMemory(uint8_t  LyNbByteToRead)
{
   uint8_t LyIdx;
   for ( LyIdx = 0 ;LyIdx < LyNbByteToRead; LyIdx++)
   {  
        LnReadMemByAddrData[LyIdx] = *LnCAN_PhysicalAddress.g_pointer;
        LnCAN_PhysicalAddress.g_pointer++;
   }
   LnReadMemByAddrMemToReadPtr =(uint32_t)(&LnReadMemByAddrData);
}

/**********************************************************************/
/*** Is Security Access Activated                                   ***/
/**********************************************************************/
static bool IsSecurityAccessActivated (void)
{
   //return ((GetVIOS_ManufactEnableCounter () == 0) &&
    //      (!GetVIOS_VehInDev ()));

   return false;
} /*** End of IsSecurityAccessActivated ***/

/***********************************************************************/
/*** Initialize the lockout timer for security access to 10 seconds. ***/
/***********************************************************************/
INLINE void InitializeSecurityAccessTiming (void)
{
  /* in the case of Flash reprogramming by GMLAN, a Security Access
     is requested after the reset before programming the watchdog cal
     and also after the reset before programming the EEPROM (VIN,...).
     in that case 2 times 10 sec can be saved in the process */
   if (IsSecurityAccessActivated ()
      &&
      !IsSecurityAccessUnlocked ())
   {
      LnDiagSecurityDelayTimer = C_R7p8125ms16 (10.0);
   }
   else
   { /* normal case (not in flash programming) */
      LnDiagSecurityDelayTimer = C_R7p8125ms16 (0.0);
   }
  /* LnDgSecAccessSpsBadKeyCounter = 0; */
} /*** End of InitializeSecurityAccessTiming ***/

/**********************************************************************/
/*** Set the lockout timer for security access to 10 seconds.       ***/
/**********************************************************************/
INLINE void TriggerSecurityAccessTiming (void)
{
   LnDiagSecurityDelayTimer = C_R7p8125ms16 (10.0);
   LnDgSecAccessSpsBadKeyCounter = 0;
} /*** End of TriggerSecurityAccessTiming ***/

/**********************************************************************/
/*** LnDiag service: LnDiagnosticSessionControl  (SID10)                  ***/
/**********************************************************************/
/**
 * @brief Struct type defining a Session.
 *
 * @param Type          Specifies the Diagnostic Session Type.
 * @param P2ServerMax   Specifies the P2ServerMax timeout for the session.
 * @param P2SServerMax  Specifies the P2*ServerMax timeout for the session.
 */
typedef struct
{
    uint8_t  Type;
    uint16_t P2ServerMax;
    uint16_t P2SServerMax;
}DS_SESSION;

/**
* Time that the server will stay in a session other\n * than defaultSession if
no requests are received.
*/
#define DS_S3SERVER_TIME       5
#define NUMBER_OF_SESSIONS  2
/**
 * This array of DS_SESSION structs contains the available diagnostic sessions. 
 * The first record should be the default session.
 * See the definition of type DS_SERVICE for information about the members.
 */
const DS_SESSION DS_Sessions[NUMBER_OF_SESSIONS] =
{
/*  Type,  P2ServerMax, P2SServerMax */
    { 0x01,  0x0032,      0x1388 },
    { 0x03,  0x0032,      0x1388 },
};


void ChangeSession(uint8_t newSession)
{ 
   if(DS_Sessions[CurrentSessionIndex].Type == DefaultSession)
   {
      if(newSession == DefaultSession)
      {
            /* 1 */
        // ClearOFVC_AllDeviceControlParameters();
      }     
      else
      {
            /* 2 */
            /*
             * When service 0x86 is implemented the following
             * function needs to be added: ResetService86Events
             */
      	}
   } 
   else
   {       
      if(newSession != DefaultSession)
      {
            /* 3 */
            /*
             * When service 0x86 is implemented the following
             * function needs to be added: ResetService86Events
             */
         LockSecurityAccess_DCAN ();
         SPS_Security_Key_Allowed = false;
      }     
      else
      {
            /* 4 */
            /*
             * When service 0x86 is implemented the following
             * function needs to be added: ResetService86Events
             *
             * When service 0x85 is implemented the following
             * function needs to be added: ResetControlDTCSettings
             */
         LockSecurityAccess_DCAN ();
         SPS_Security_Key_Allowed = false;
         //ClearOFVC_AllDeviceControlParameters();
	 // ClearAndDisableAllDpids ();
      	}
   
   }
}

void LnDiagnosticSessionControl (void)
{
   uint8_t sessionType;
   uint8_t sessionIndex;
   bool  suppressPosRespMsgIndicationBit;
   bool  found = false;
   uint8_t msglength;
   if(GetLnServiceDataLength () != 2)
   {
       SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      suppressPosRespMsgIndicationBit = ((GetLnServiceData (1)) & 0x80) ? true : false;
      sessionType = ((GetLnServiceData (1))  & 0x7f);
      sessionIndex=0;
      msglength=1;
      while((sessionIndex<NUMBER_OF_SESSIONS) && !found)
      {
         if(sessionType == DS_Sessions[sessionIndex].Type)
         {
            found = true;
         }
         if(!found)
         {
            sessionIndex++;
         }
      }
      if(!found)
      {
         if(GetLnServReqMsgAddressingMode () == FunctionalAddressing)
         {
            PfrmDCAN_AckReqWithoutResponse ();
         }
         else
         {
            SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
         }
      }
      if(sessionType != DefaultSession) 
      {
      //  ActivateS3ServerTimer = true;
         ExtendedDiagnosticSessionControl= true;
      }
      else
      {
         ExtendedDiagnosticSessionControl= false;
      }
      ChangeSession(sessionType);
      CurrentSessionIndex = sessionIndex;
      S3ServerTimer = C_R7p8125ms16 (DS_S3SERVER_TIME);

      if( suppressPosRespMsgIndicationBit ||((sessionType != 0x01) && (sessionType != 0x03)) )
      {
        PfrmDCAN_AckReqWithoutResponse ();
      }
      else 
      {
         WrtDCAN_ServiceData( sessionType,msglength++ ) ;	
         WrtDCAN_ServiceData( (((DS_Sessions[CurrentSessionIndex].P2ServerMax)>>8) & 0xff),
	   	                    msglength++ ) ;
         WrtDCAN_ServiceData( ((DS_Sessions[CurrentSessionIndex].P2ServerMax) & 0xff),
	   	                    msglength++ ) ;
         WrtDCAN_ServiceData( (((DS_Sessions[CurrentSessionIndex].P2SServerMax)>>8) & 0xff),
	   	                    msglength++ ) ;
         WrtDCAN_ServiceData( ((DS_Sessions[CurrentSessionIndex].P2SServerMax) & 0xff),
	   	                    msglength++ ) ;
         SendLnStandardPositiveAnswer(msglength);
        
      }
   }
}

/**********************************************************************/
/*** LnDiag service: LnEcuReset    (SID11)                ***/
/**********************************************************************/
#define SubFuncSWReset     (0x03)
void LnEcuReset (void)
{
/* Define the local variable to store the reset mode */
  uint8_t  ResetMode;

  /* Check for correct number of data bytes in the request msg. */
  if ( GetLnServiceDataLength()  != 2)
  {
    SendLnStandardNegativeAnswer (IncorrectMessageLength);
  }
  else
  {
      ResetMode = (GetLnServiceData (1)) ;
      switch (ResetMode)
       {
        case SubFuncSWReset: /* Mode 03 */ 
            SendLnStandardPositiveAnswer(2);
            SetECUResetPending(CbTRUE);
            break;
        default:
           SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
           break;
       }
  }
}

/**********************************************************************/
/*** LnDiag service: LnClearDiagnosticInformation     (SID14)              ***/
/**********************************************************************/
void LnClearDiagnosticInformation (void)
{
   uint32_t  groupOfDTC;
   if ((GetLnServiceDataLength () != 4))
   {/*--- No parameter for this request ID ---*/
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      groupOfDTC = (((uint32_t )(GetLnServiceData (1)))<<16) | 
                 (((uint16_t )(GetLnServiceData (2)))<<8) |
                 (GetLnServiceData (3));               
      if((groupOfDTC == 0xffffff))
      {
         //ClearDiagnosticData ();
         SendLnStandardPositiveAnswer (1);
      } 
      else
      {
         SendLnStandardNegativeAnswer (RequestOutOfRange); 
      }
   }
} /*** End of LnClearDiagnosticInformation ***/

/***************************************************************/
/*** function needed for LnDiag service ReadMemoryByAddress: ***/
/*** UpdateLnReadMemoryByAddress       (SID23)                      ***/
/***************************************************************/

void UpdateLnReadMemoryByAddress (void)
{
   if (LnReadMemByAddrNbBytesToRead > PacketNbOfBytesToTransfer)
   {
      if (GetLnServNbOfFreeBytesInRingBuffer () >= PacketNbOfBytesToTransfer)
      {
                           	   /* Load to the buffer with the memory data */    
         LoadCANServiceDataFromMemory(PacketNbOfBytesToTransfer);

         StoreLnServNbBytesInRingBuffer (PacketNbOfBytesToTransfer,
                                        (uint8_t *) LnReadMemByAddrMemToReadPtr);
        // LnReadMemByAddrMemToReadPtr = LnReadMemByAddrMemToReadPtr + PacketNbOfBytesToTransfer;
         LnReadMemByAddrNbBytesToRead = LnReadMemByAddrNbBytesToRead - PacketNbOfBytesToTransfer;
      }
   }
   else
   {
      if (GetLnServNbOfFreeBytesInRingBuffer () >= LnReadMemByAddrNbBytesToRead)
      {
                       	   /* Load to the buffer with the memory data */    
         LoadCANServiceDataFromMemory(PacketNbOfBytesToTransfer);

         StoreLnServNbBytesInRingBuffer (LnReadMemByAddrNbBytesToRead,
                                        (uint8_t *) LnReadMemByAddrMemToReadPtr);
      }
      LnReadMemByAddrNbBytesToRead = 0;
      LnDiagSvFlags.ReadMemoryByAddressActive = (bitfield16_t) false;
   }
} /*** End of UpdateLnReadMemoryByAddress ***/

/**********************************************************************/
/*** LnDiag service: ReadMemoryByAddress                            ***/
/**********************************************************************/
#define MaxRMemSize                      (255)
#define C_NoVirtualAddress               (0x00L)

/*--- (####TRICORE hard-coded for now) ---*/
#define BootBaseL              ((uint32_t) 0x7ff800L)
#define BootEndL                ((uint32_t) 0x7fff00L)

#define FlashBaseL                    ((uint32_t) 0x740000L)
#define FlashEndL                      ((uint32_t) 0x800000L)

/*--- Functions to substract 1 to get real end-address ---*/
/*--- this is necessary as no address calculations in table are allowed after compile time.     ---*/
INLINE uint32_t GetStartAddress (const MemoryMapType *Addr) { return (Addr->StartAddress);}
INLINE uint32_t GetVirtualAddress (const MemoryMapType *Addr) { return (Addr->VirtualAddressConversion);}
INLINE uint32_t GetEndAddress (const MemoryMapType *Addr) { return ((Addr->EndAddress - 1));}

/**********************************************************************/
/* Table defining the different readable memory zones and the real    */
/* address conversion if the transmitted addresses are virtual.       */
/* The table also indicates the attributes (Read-Only, Read-Protected */
/* Write-Protected). Memory areas may be overlapping (for example     */
/* EEPNVM area inside of RAM area), but in that case the start-       */
/* addresses of those areas must be in increasing order. The virtual  */
/* address conversion will be the one of the last found matching area.*/
/* Start & end addresses may be in different areas, but the virtual   */
/* addresses of both areas must be the same, otherwise a neg. resp.   */
/* "Out of range" is issued.                                          */
/* The protections are OR-ed between start-, end- and included areas, */
/* meaning if a protected area is included between start and end,     */
/* then the access will be denied.                                    */
/* NOTE: End-Address in table is EXCLUDED of the respective area (-1) */
/* The Hidden Attribute table is EXCLUDED of the respective area (-1) */
/**********************************************************************/

const MemoryMapType EcuMemoryMap [] =
  {
  
/*Start-Address              EndAddress                 VirtualAddrConversion       R-only R-prot W-Prot Hidden */
  BootBaseL                  , BootEndL                 , C_NoVirtualAddress        , true , true,  true,  false, /* Boot-ROM   */
  CyEEPROM_SectionStart      , CyEEPROM_SectionEnd      , C_NoVirtualAddress        , true, true,  true,  false,  /* EEP-ROM */
  FlashBaseL                  , FlashEndL                 , C_NoVirtualAddress       , true , true,  true,  false, /* Flash-ROM   */
  CyRAM_DCAN_SectionStart         , CyRAM_DCAN_SectionEnd        , C_NoVirtualAddress       , true, false, true,  false  /* complete RAM */
  };

#define C_NumberOfAreas (sizeof(EcuMemoryMap)/sizeof(MemoryMapType))

/**********************************************************************/
/*** Look for a matching memory range for Start&End Address         ***/
/**********************************************************************/
bool FindMatchingMemoryArea (uint32_t StartPtr, uint32_t  EndPtr, uint32_t *VirtualConversion, uint32_t *StartAddr,
                                bool *ReadOnly, bool *ReadProt,bool *WriteProt, bool *Hidden)
{
  uint8_t i, StartArea, EndArea;
  bool Found;

  /* Look for best matching memory area for both Start- and EndPtr */
  /* If Start- and End-Pointer- Areas do not have the same virtual */
  /* address- conversion, the request will be denied.              */
  /* The highest protection of all matching areas will be applied  */
  *ReadOnly = false;
  *ReadProt = false;
  *WriteProt = false;
  *Hidden = false;
  StartArea = C_NumberOfAreas;
  EndArea = C_NumberOfAreas;

  for (i=0; i < C_NumberOfAreas; i++)
    {
    if (((StartPtr >= GetStartAddress (&EcuMemoryMap[i])) &&
        (StartPtr <= GetEndAddress (&EcuMemoryMap[i])))&&
        ((EndPtr >= GetStartAddress (&EcuMemoryMap[i])) &&
        (EndPtr <= GetEndAddress (&EcuMemoryMap[i]))))
      { /*--- find start-area ---*/
      StartArea = i;
      EndArea = i;
	  break;
      }
    }

  if ((StartArea < C_NumberOfAreas && EndArea < C_NumberOfAreas) &&
      (EcuMemoryMap[StartArea].VirtualAddressConversion == EcuMemoryMap[EndArea].VirtualAddressConversion))
      { /*--- found valid area, virtual addresses match, determine attributes ---*/
      *VirtualConversion = EcuMemoryMap[StartArea].VirtualAddressConversion;
      *StartAddr = EcuMemoryMap[StartArea].StartAddress;
      /* Attributes: -OR- between start, end and included areas */
      *ReadOnly |= (EcuMemoryMap[StartArea].MemoryAccess.ReadOnly ||
                    EcuMemoryMap[EndArea].MemoryAccess.ReadOnly) ? true : false;
      *ReadProt |= (!IsSecurityAccessUnlocked () &&
                    (EcuMemoryMap[StartArea].MemoryAccess.ReadProtected ||
                     EcuMemoryMap[EndArea].MemoryAccess.ReadProtected)) ? true : false;
      *WriteProt |= (!IsSecurityAccessUnlocked () &&
                     (EcuMemoryMap[StartArea].MemoryAccess.WriteProtected ||
                      EcuMemoryMap[EndArea].MemoryAccess.WriteProtected)) ? true : false;
      /* area is "hidden" when security access activated, even if seed&key correct! */
      *Hidden |= (IsSecurityAccessActivated () &&
                  (EcuMemoryMap[StartArea].MemoryAccess.Hidden ||
                   EcuMemoryMap[EndArea].MemoryAccess.Hidden)) ? true : false;
      Found = true;
      }
  else
     {
       Found = false;
     }
  return Found;
} /*** End of FindMatchingMemoryArea ***/

void LnReadMemoryByAddress (void)

  {
  uint32_t  LnReadMemByAddrMemToReadEndPtr;
  uint32_t  StartAddress, VirtualConversion;
  bool   ReadOnly,ReadProtected, WriteProtected, Hidden, Found;

  if ((GetLnServiceData (1))  == 0x14 )
  {
    /* Build the memory start address (24 bit) from the request message. 
     */
    /* The bit 24 to bit 32 of the memory start address 
     * should be zero 
     */ 

    /* The bit 16 to bit 23 of the memory start address
     * is the received memory address high byte.
     */   
    LnCAN_PhysicalAddress.g_l.globle_page =  GetLnServiceData (3);

    /* The bit 8 to bit 15 of the memory start address
     * is the received memory address middle byte.
     */  
    /* The bit 0 to bit7 of the memory start address
     * is the received memory address low byte.
     */  
    LnCAN_PhysicalAddress.g_l.local_addr = 
          (uint16_t)( (uint8_t*)(((GetLnServiceData (4)) << 8) |(GetLnServiceData (5))));
   LnReadMemByAddrNbBytesToRead = (uint16_t)((GetLnServiceData (6)));
     if (GetLnServiceDataLength () != 7)
     {
        SendLnStandardNegativeAnswer (IncorrectMessageLength);
     }
 
    else  if (LnReadMemByAddrNbBytesToRead > MaxRMemSize)
     {
    /*--- case desired Size > than max. message length ---*/
        SendLnStandardNegativeAnswer (RequestOutOfRange);
     }
     else
     {
         LnReadMemByAddrMemToReadEndPtr = (uint32_t)LnCAN_PhysicalAddress.g_pointer + (uint32_t) (LnReadMemByAddrNbBytesToRead - 1);

         Found = FindMatchingMemoryArea ((uint32_t)LnCAN_PhysicalAddress.g_pointer, LnReadMemByAddrMemToReadEndPtr,
                                    &VirtualConversion, &StartAddress,
                                    &ReadOnly, &ReadProtected,
                                    &WriteProtected, &Hidden);
        if (!Found || Hidden)
        { /* no matching area found or area "hidden" through activated security access */
           SendLnStandardNegativeAnswer (RequestOutOfRange);
           return; /*--- exit function ---*/
        }
        else if (ReadProtected)
        { /*--- Inside area with Security Access not obtained ---*/
           SendLnStandardNegativeAnswer (SecurityAccessDenied);
           return; /*--- exit function ---*/
        }
        else
        {
           if (VirtualConversion != C_NoVirtualAddress)
           { /*--- calculate StartAddress from Virtual-Address ---*/
               LnCAN_PhysicalAddress.g_pointer = LnCAN_PhysicalAddress.g_pointer + (VirtualConversion - StartAddress);
           //LnReadMemByAddrMemToReadPtr = LnReadMemByAddrMemToReadPtr + (VirtualConversion - StartAddress);

           }

        /*--- the use of the ring buffer allows the Read Memory By Address
                      to read a number of bytes bigger than the size of the buffer
                      of the transport layer ---*/
           StoreLnServNbBytesInRingBuffer (1, (uint8_t *) (&LnServiceDataFrame.Data [0]));

           WriteLnMessageDataLength (LnReadMemByAddrNbBytesToRead + 1);

           if (LnReadMemByAddrNbBytesToRead > PacketNbOfBytesToTransfer)
           { /*--- response will be filled by block
            of PacketNbOfBytesToTransfer bytes ---*/
              LnDiagSvFlags.ReadMemoryByAddressActive = (bitfield16_t) true;
	       /* Load to the buffer with the memory data */    
              LoadCANServiceDataFromMemory(PacketNbOfBytesToTransfer);

              StoreLnServNbBytesInRingBuffer (PacketNbOfBytesToTransfer,
                          (uint8_t *) LnReadMemByAddrMemToReadPtr);
              SendLnStandardPositiveAnswer (LnReadMemByAddrNbBytesToRead + 1);
             // LnReadMemByAddrMemToReadPtr = LnReadMemByAddrMemToReadPtr
              //                              + PacketNbOfBytesToTransfer;
              LnReadMemByAddrNbBytesToRead = LnReadMemByAddrNbBytesToRead
                                        - PacketNbOfBytesToTransfer;
           }
           else
           {
	      /* Load to the buffer with the memory data */    
              LoadCANServiceDataFromMemory(PacketNbOfBytesToTransfer);
              StoreLnServNbBytesInRingBuffer (LnReadMemByAddrNbBytesToRead,
                         (uint8_t *) LnReadMemByAddrMemToReadPtr);
              SendLnStandardPositiveAnswer (LnReadMemByAddrNbBytesToRead + 1);
           }
        }
     }
  }
 else 
 {
    SendLnStandardNegativeAnswer (RequestOutOfRange);
 }
} /*** End of LnReadMemoryByAddress ***/

/**********************************************************************/
/*** LnDiag service: SecurityAccess    (SID27)                             ***/
/**********************************************************************/
#define SubFuncRequestSeed (0x01)
#define SubFuncSendKey     (0x02)

void LnSecurityAccess (void)
{
   uint8_t SecurityAccessSubFunction;
   uint16_t  ReceivedKey;
   uint8_t  meslegth;
  
   SecurityAccessSubFunction = (GetLnServiceData (1));
   meslegth = 2;
   switch (SecurityAccessSubFunction)
   {
      case SubFuncRequestSeed:
      if (GetLnServiceDataLength () != 2)
      {
          SendLnStandardNegativeAnswer (IncorrectMessageLength);
      }
      else
      {
         if (( IsDevelopmentOrManfModeActive () )  ||
                    CheckProgrammingState ()  ||
                   GetLnVulnerabilityState() )
                                   /* PCM already unlocked */
         {
            WrtDCAN_ServiceData(0x00, meslegth++);
	     WrtDCAN_ServiceData(0x00, meslegth++);
	     UnlockSecurityAccess_DCAN ();
	     SendLnStandardPositiveAnswer (meslegth);
         }
         else
         {
       if (LnDiagSecurityDelayTimer)
            {
               SendLnStandardNegativeAnswer (RequiredTimeDelayNotExpired);
            }
            else
            {
               SPS_Security_Key_Allowed = true; 
               WrtDCAN_ServiceData(((uint8_t) (Get_Security_Seed_Data() >> 8)), meslegth++);
               WrtDCAN_ServiceData(((uint8_t) Get_Security_Seed_Data()), meslegth++);
               SendLnStandardPositiveAnswer (meslegth);
            }
         }
      }
      break;
      case SubFuncSendKey:
      if (LnDiagSecurityDelayTimer)
      {
         SendLnStandardNegativeAnswer (RequiredTimeDelayNotExpired);
      }
      else
      {
         if (GetLnServiceDataLength () != 4)
         {
            SendLnStandardNegativeAnswer (IncorrectMessageLength);
         }
         else
         {
            if (SPS_Security_Key_Allowed)
            {
               SPS_Security_Key_Allowed = false;
               ReceivedKey = ((GetLnServiceData (2))  << 8) + (GetLnServiceData (3));
               if (ReceivedKey == Get_Security_Key_Data() )
               {
                 UnlockSecurityAccess_DCAN ();
                  LnDgSecAccessSpsBadKeyCounter = 0;
                 /*--- (GetLnServiceData ()) [1] = SubFuncSendKey;Not changed ---*/
                  SendLnStandardPositiveAnswer (2);
               }
               else
               {
                    LnDgSecAccessSpsBadKeyCounter ++;
                    if (LnDgSecAccessSpsBadKeyCounter == 2)
                    {
                       SendLnStandardNegativeAnswer (ExceedNumberOfAttempts);
                       TriggerSecurityAccessTiming ();
                    }
                    else
                    {
                       SendLnStandardNegativeAnswer (InvalidKey);
                    }
                 }
            }
            else
            {
               SendLnStandardNegativeAnswer (ConditionsNotCorrectOrRequestSequenceError);
            }
         }
      }
      break;
      default:
         SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
      break;
   }
} /*** End of LnSecurityAccess ***/
  
/**********************************************************************/
/*** LnDiag service: WriteDataByIdentifier     (SID2E)                     ***/
/**********************************************************************/
#define wdliMalfDisableArray    (0xFA)
#define ExpectedTimeToFlushAllEepInMs (2000.0)
#define CrankShaftAdaptiveCylinderSize     (16)
void LnWriteDataByIdentifier (void)
{
  uint16_t WriteDataIdentifierId, LyIndex;
  uint16_t  Idx;
  uint8_t Idx_WritePointer;
  uint32_t LgDF_DID_OdoServiceValue;
  LONGWORD Temp_Long;
   BYTE KW2CrankShaftAdaptiveCylinder[CrankShaftAdaptiveCylinderSize];

  LgDF_DID_OdoServiceValue = 0; LyIndex =0;

  WriteDataIdentifierId = (((uint16_t) (GetLnServiceData (1))  << 8) |(GetLnServiceData (2)) );
  if (!LnDiagSvFlags.WaitingForWriteDataByIdToComplete)
  {
        /*--- NOTE: The switch statement contains the LocalIds which
                   do not require a security access*/
     switch (WriteDataIdentifierId)
     {

	 #if 0
          /*--- NO Security Access required for these Data ---*/
        case DIdCrankshaftAdaptiveCylinder:
            if (GetLnServiceDataLength () !=
                (3 + CrankShaftAdaptiveCylinderSize))
            {
               SendLnStandardNegativeAnswer (IncorrectMessageLength);
            }
            else if(IsDevelopmentOrManfModeActive() != CbTRUE)
            {
               SendLnStandardNegativeAnswer ( nrcConditionsNotCorrect_RequestSequenceError);
            }
            else
            {

              /*--- Program CrankShaft Adaptive Cylinder ---*/
              for(Idx_WritePointer = 0, Idx = 0;
                  Idx_WritePointer < CcSYST_NUM_OF_CYLINDERS;
                  Idx_WritePointer++)
              {
                KW2CrankShaftAdaptiveCylinder[Idx] = GetLnServiceData (3 + Idx) ;
                Temp_Long  = (LONGWORD) ( (KW2CrankShaftAdaptiveCylinder[Idx] & 0xff) << 24);
                Idx++;

                KW2CrankShaftAdaptiveCylinder[Idx] = (GetLnServiceData (3 + Idx)) ;
                Temp_Long += (LONGWORD) ( (KW2CrankShaftAdaptiveCylinder[Idx] & 0xff) << 16);
                Idx++;

                KW2CrankShaftAdaptiveCylinder[Idx] = (GetLnServiceData (3 + Idx)) ;
                Temp_Long += (LONGWORD) ( (KW2CrankShaftAdaptiveCylinder[Idx] & 0xff) << 8);
                Idx++;

                KW2CrankShaftAdaptiveCylinder[Idx] = (GetLnServiceData (3 + Idx)) ;
                Temp_Long += (LONGWORD) (KW2CrankShaftAdaptiveCylinder[Idx] & 0xff);
                Idx++;

                //NaTECD_FactorTotals[Idx_WritePointer] = Temp_Long;
                }
              //ModifyFILE_EE_TEC_Factors(NaTECD_FactorTotals);

              SendLnStandardPositiveAnswer (3);
            }
          break;
		  
        case DIdTECDSampleCounter:
            if (GetLnServiceDataLength () !=
                (3 + CrankShaftAdaptiveCntr_Size))
            {
               SendLnStandardNegativeAnswer (IncorrectMessageLength);
            }
            else if(IsDevelopmentOrManfModeActive() != CbTRUE)
            {
               SendLnStandardNegativeAnswer ( nrcConditionsNotCorrect_RequestSequenceError);
            }
            else
           {
              NcTECD_SampleCntr = (GetLnServiceData (3)) ;
              ModifyFILE_EE_TEC_SmplCntr(&NcTECD_SampleCntr);
              SendLnStandardPositiveAnswer (3);
              }
          break;
		
        case DIdManufacturersEnableCounter:

            if (GetLnServiceDataLength () != 4)
              {
              SendLnStandardNegativeAnswer (IncorrectMessageLength);
              }
            else
              {
              if(GetVIOS_ManufactEnableCounter() == 0)
                {
                if(GetVIOS_VehInDev ())
                  {
                 // NyVIOS_ManufactEnableCounter = (GetLnServiceData (3)) ;
                  //ModifyFILE_EE_MEC_ManufEnblCntr(&NyVIOS_ManufactEnableCounter);
                  SetVIDS_OFVC_ManufactEnableCounter(GetLnServiceData (3));
                  SendLnStandardPositiveAnswer (3);
                  }
                else
                  {
              SendLnStandardNegativeAnswer (ConditionsNotCorrectOrRequestSequenceError);
                 }
               }
           else
             {
               // NyVIOS_ManufactEnableCounter = (GetLnServiceData (3)) ;
               // ModifyFILE_EE_MEC_ManufEnblCntr(&NyVIOS_ManufactEnableCounter);
                SetVIDS_OFVC_ManufactEnableCounter(GetLnServiceData (3));
                SendLnStandardPositiveAnswer (3);
                }
           }
        break;
			
        case DIdVehicleIdentificationNumber:
           if (GetLnServiceDataLength () !=(3 + VIN_Size))
           {
               SendLnStandardNegativeAnswer (IncorrectMessageLength);
           }
           else
           {
                    /*--- Program VehicleIdentificationNumber ---*/
              for (Idx = 0; Idx < VIN_Size; Idx++)
              {
                 //WrtVinDataByte (Idx, (GetLnServiceData (3 + Idx)));
                 WriteNvmEeprom( &NV_VINNumber[Idx], GetLnServiceData (3 + Idx));
              }
                   /* Write to EE */
              //WrtVinDataValue();
              SendLnStandardPositiveAnswer (3);
           }
        break;
			  
        case DIdRepairShopCodeOrTesterSerialNumber:
            if (GetLnServiceDataLength () != (3 + RepairShopCode_Size))
            {
               SendLnStandardNegativeAnswer (IncorrectMessageLength);
            }
            else
            {
               for (Idx = 0; Idx < RepairShopCode_Size; Idx++)
               {
                 // WrtKW2RepairShopCodeByte (Idx,(GetLnServiceData (3 + Idx)));
		    WriteNvmEeprom( &NV_RepairShopCode[Idx], GetLnServiceData (3 + Idx)) ;
               }
               //WrtKW2RepairShopCodeValue ();
               SendLnStandardPositiveAnswer (3);
            }
        break;

        case DIdProgrammingDate:
                if (GetLnServiceDataLength () != (3 + ProgrammingDate_Size))
                 {
                 SendLnStandardNegativeAnswer (IncorrectMessageLength);
                 }
                 else
                 {
                   for (Idx = 0; Idx < ProgrammingDate_Size; Idx++)
                     {
                         //WrtKW2ProgrammingDateByte (Idx,(GetLnServiceData (3 + Idx)));
			    WriteNvmEeprom( &NV_ProgrammingDate[Idx], GetLnServiceData (3 + Idx)) ;
                     }
                   //WrtKW2ProgrammingDateValue ();
                   SendLnStandardPositiveAnswer (3);
                    }
        break;
	#endif  	
        default :
           SendLnStandardNegativeAnswer (RequestOutOfRange);
        break;
           } /* End of Switch*/
  } /*--- end of if !LnDiagSvFlags.WaitingForWriteDataByIdToComplete  ---*/
} /*** End of LnWriteDataByIdentifier ***/

/**********************************************************************/
/*** LnDiag service: ReadDataByIdentifier                           ***/
/**********************************************************************/
void LnReadDataByIdentifier (bool SingleFrameOnly)

  {
  uint8_t DataId, Idx;
  uint16_t  SdIdx;
  uint16_t  BIdx;
  uint16_t DataWord;
  uint32_t DataLong;
  uint16_t EMN_LastFourByte;
  uint8_t LuDPID;
  //T_KILOMETERSe LgCOMM_Odo_AccumltdDist;

  if (GetLnServiceDataLength() != 2)
    {
    SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
    return;
    }

  DataId = (GetLnServiceData(1));

  switch (DataId)
    {
	case DIdECUDiagnosticAddress:                      /*--- Read only added by  */
		SdIdx = 2;
		(GetLnServiceData(SdIdx++)) = ECUDiagnosticAddress;
		SendLnStandardPositiveAnswer(SdIdx);
	    break;	
		
    default:
        SendLnStandardNegativeAnswer(RequestOutOfRange);
        break;
    }
  } /*** End of LnReadDataByIdentifier ***/

#define SubFuncDisableAllDTCs (0x02)
void LnInitiateDiagnosticOperation (void)
{
  uint8_t SubFuncPar;
  bool   ValidRequest;

  SubFuncPar = (GetLnServiceData(1)) ;

  if (GetLnServiceDataLength() != 2)
  {
    SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
    ValidRequest = false;
  }
  else
  {
      if (SubFuncDisableAllDTCs == SubFuncPar )
	  {
	     //LnDiagServicesDisableDTCs = true;
	     ValidRequest = true;
      }
	  else
	  {
	     SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
	     ValidRequest = false;
      }
    }

  if (ValidRequest)
  { /*** Enable the TesterPresentState logic ***/
    //LnActivateTesterPresent ();
    SendLnStandardPositiveAnswer(1);
  }
} /*** End of LnInitiateDiagnosticOperation ***/

/*****************************************************************/
/*** LnDiag service: ReturnToNormalMode                        ***/
/*****************************************************************/

void LnReturnToNormalMode (void)
{
  if (GetLnServiceDataLength() != 1)
  {
    SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
  }
  else
  {
	PfrmDCAN_AckReqWithoutResponse();

    }
  } /*** End of LnReturnToNormalMode ***/

/**********************************************************************/
/*** LnDiag service: DisableNormalCommunication                     ***/
/**********************************************************************/

void LnDisableNormalCommunication (void)
{
  if (GetLnServiceDataLength() != 1)
  {
    SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
  }
  else
  {
    if (!GetVIOS_EngTurning())
    {
      //LnDiagServicesDisableDTCs = true;

      //LnActivateTesterPresent ();
      GetLnServiceData(0) = SidDisableNormalCommunication;
      SendLnStandardPositiveAnswer(1);
    }
    else
    {
      SendLnStandardNegativeAnswer(ConditionsNotCorrectOrRequestSequenceError);
    }
  }
} /*** End of LnDisableNormalCommunication ***/

/**********************************************************************/
/*** LnDiag service: TesterPresent        (SID3E)                          ***/
/**********************************************************************/
void LnTesterPresent (void)
{
   bool suppressPosRespMsgIndicationBit;
   uint8_t  subFunction;
   if(GetLnServiceDataLength () != 2)
   {
        /* Request should be 2 bytes long */
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      suppressPosRespMsgIndicationBit = ((GetLnServiceData (1)) & 0x80) ? true: false;
      subFunction = ((GetLnServiceData (1)) & 0x7f);
      if( subFunction != 0x00 )
      {
        /* Sub function is not supported */
         if (GetLnServReqMsgAddressingMode () == PhysicalAddressing)
         {
            SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
         }
         else
         {
         /* if a request is functionally adressed no response */
            PfrmDCAN_AckReqWithoutResponse();
         }
      }
      if( suppressPosRespMsgIndicationBit )
      {
         PfrmDCAN_AckReqWithoutResponse();
      }
      else 
      {
         SendLnStandardPositiveAnswer (2);
      }
   }
}

/**********************************************************************/
/*** LnDiag service: ReportProgrammedState                          ***/
/**********************************************************************/

#define FullyProgrammed (0)
#define NoOperationalSwOrCalData (1)

void LnReportProgrammedState(void)
{
  if ((GetLnServiceDataLength() == 1))
  {
    (GetLnServiceData(1)) = FullyProgrammed;
    SendLnStandardPositiveAnswer(2);
  }
  else
  {
    SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
  }
} /*** End of LnReportProgrammedState ***/

/**********************************************************************/
/*** LnDiag service: ProgrammingMode                                ***/
/**********************************************************************/
#define requestProgrammingMode           (01)
#define requestProgrammingMode_HighSpeed (02)
#define enableProgrammingMode            (03)

void LnProgrammingMode(void)
{
  uint8_t SubFunctionParameterLevel;

  if ((GetLnServiceDataLength() != 2))
  {
    SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
  }
  else
  {
    SubFunctionParameterLevel = (GetLnServiceData(1));
    switch (SubFunctionParameterLevel)
    {
      case requestProgrammingMode:
          if (GetVIOS_EngTurning ())
          {
            SendLnStandardNegativeAnswer(ConditionsNotCorrectOrRequestSequenceError);
          }
          else
          {
            //LnProgrammingModeEntryOk = true;
            SendLnStandardPositiveAnswer(1);
          }
          break;

      case enableProgrammingMode:
          /*--- verify that a previous request was received
                     with $Level = requestProgrammingMode ---*/

            /*--- No response to this request from any ECU ---*/
            PfrmDCAN_AckReqWithoutResponse();

          break;

      case requestProgrammingMode_HighSpeed:
          /*--- only for Low Speed CAN bus nodes ---*/
      default:
          SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
          break;
     } /* End switch (SubFunctionParameterLevel) */
   }
} /*** End of LnProgrammingMode ***/


/**********************************************************************/
/*** LnDiag service: Routine Control       (SID31)                          ***/
/**********************************************************************/
#define DS_NUM_ROUTINE_CTRL 2
typedef uint8_t  (* DS_RC_HNDL_FUNC)(uint8_t type);

typedef struct
{
    uint16_t Identifier;
    bool Protected;
    DS_RC_HNDL_FUNC HandlerFunc;
}DS_ROUTINE_CTRL;
/***********************************************************************
*                                                                      *
* FUNCTION:          StartRoutineByLocalIdentifier                     *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       This is to execute a routine identified by a      *
*                    local identifier                                  *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
************************************************************************
* Last modified on: 06/10/10              by: Abhishek Sharma          *
***********************************************************************/
uint8_t StartRoutineByLocalIdentifier(void)
{
  uint8_t LyResponse;
       if(( GetLnVulnerabilityState() )
                   //|| ( GetVIOS_VehInDev() ))
                && (GetVIOS_v_VehSpd() == V_KPH(0))
                && (GetVIOS_n_EngSpd() == V_RPM(0)))
              {
                 SetCopyAndExecuteKernelPending(CbTRUE);
          LyResponse = 0x00;
	       //return 0x00;
              }
              else
              {
          LyResponse = 0x7F;
          // return 0x7F;
              }

	return (LyResponse);
 
  } /*** End of KwJ14230StopDiagnosticSession ***/

uint8_t StartRoutine_NVMReInitLogic(void)
{
 //  WriteFILE_NVM_CriticalByte(&NbFILE_NVM_Reset_RequestFromSerial, 
   //                                      CbTRUE);
   NbFILE_NVM_Reset_RequestFromSerial = CbTRUE;
   return 0x00;
}
/**
 * Handlerfunction for RC 0x03
 * Length=2: 'RoutineControl'
 */
uint8_t DS_RC_F000_Handler(uint8_t type)
{
    /* TODO: Insert code to perform RC handling! */
    uint8_t status;
	
    status=0x00;
    switch(type)
    {
    case 0x01:  /* StartRoutine */
        status = StartRoutineByLocalIdentifier();
        break;
    case 0x02:  /* StopRoutine */
    case 0x03:  /* requestRoutineResult */
        status = 0x12; /* subfunction not supported */
    }
    return status;
}

uint8_t DS_RC_AA00_Handler(uint8_t type)
{
    /* TODO: Insert code to perform RC handling! */
    uint8_t status;
	
    status=0x00;
    switch(type)
    {
    case 0x01:  /* StartRoutine */
        status = StartRoutine_NVMReInitLogic();
        break;
    case 0x02:  /* StopRoutine */
    case 0x03:  /* requestRoutineResult */
        status = 0x12; /* subfunction not supported */
    }
    return status;
}

/**
 * Array of DS_ROUTINE_CTRL structures defining the available RoutineControl 
 * parameters. The RoutineControl records must be sorted with the identifier with
 * the lowest value first.
 * See the definition of type DS_ROUTINE_CTRL for information about the members.
 */
const DS_ROUTINE_CTRL DS_RoutineControl[DS_NUM_ROUTINE_CTRL] =
{
/*  Identifier, Protected,   HandlerFunc */
    {0xAA00,    true,       DS_RC_AA00_Handler },
    {0xF000,    true,       DS_RC_F000_Handler }
};

/* 
 * BinarySearchU16 is documented in header file
 */
uint16_t BinarySearchU16(const void* table, uint8_t offset, uint16_t low, uint16_t high, uint16_t key)
{
   uint16_t middle;

   while( CbTRUE ) /* Loop forever, leave the loop only by return on match or 
                    the end is reached. */ 
   {
      if( high == low ) /* Check if only one index left */
      {
         if( key == *((const uint16_t*)(((const uint8_t*)table) + (low*offset))) ) 
         {
            /* We have a match */
            return low;
         }
         else
         {
            /* There is NO match */
            return 0xFFFF;
         }
      }
      else
      {
         /* Get the middle index in the interval */
         middle = ( low + high ) / 2;
         if( key == *((const uint16_t*)(((const uint8_t*)table) + (middle*offset))) )
         {
            /* We have a match */
            return middle;
         }
         else if( key < *((const uint16_t*)(((const uint8_t*)table) + (middle*offset))) )
         {
            /* Narrow the interval on the top */
            high = middle;
         }
         else
         {
            /* Narrow the interval on the bottom */
            low = middle + 1;
         }
      }
   }
}

void LnRoutineControl(void)
{
   uint16_t  index, routineId;
   const DS_ROUTINE_CTRL* routineCtrl;
   uint8_t  routineCtrlType;
   uint8_t  rc;
   bool suppressPosRespMsgIndicationBit;
	
   if(GetLnServiceDataLength()!= 4)
   { /* DS_Request should be atleast 4 bytes long */
       SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      suppressPosRespMsgIndicationBit = ((GetLnServiceData (1))  & 0x80) ? true: false;
      routineId = (((GetLnServiceData (2))*0x100) + (GetLnServiceData (3)));
      index = BinarySearchU16(&DS_RoutineControl[0].Identifier,sizeof(DS_ROUTINE_CTRL),0,DS_NUM_ROUTINE_CTRL,routineId);
      routineCtrl = &DS_RoutineControl[index];
      routineCtrlType = ((GetLnServiceData (1)) & 0x7f);
      if(index == 0xFFFF)
      {/* There is no routineControl whith the requested id */
         SendLnStandardNegativeAnswer (RequestOutOfRange);
      }
      else if((routineCtrl->Protected) && (!IsSecurityAccessUnlocked()))
      {/* Protected routineControl and SecurityAccess is not called */
         SendLnStandardNegativeAnswer (SecurityAccessDenied);
      }
      else
      {
         switch(routineCtrlType)
         {
         case 0x01:
           rc = routineCtrl->HandlerFunc(routineCtrlType);        
           if( rc == 0x00 )
           {
              if( suppressPosRespMsgIndicationBit )
              {
                 PfrmDCAN_AckReqWithoutResponse();
              }
              else
              {
                 SendLnStandardPositiveAnswer (4);
              }
           }
           else 
           {
              SendLnStandardNegativeAnswer (ConditionsNotCorrectOrRequestSequenceError);
           }
	   break;	   
         default:
            if(GetLnServReqMsgAddressingMode () == FunctionalAddressing)
            {
              PfrmDCAN_AckReqWithoutResponse();
            }
            else
            {
              SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
            }
	   break;	 		
         }
      }
   }
}



/***************************/
/*** function prototypes ***/
/***************************/
void LnEventFunctionalRequest (void)
{
   switch (GetLnServiceDataServiceId ())
   {
    /*--- only serve Request that seems critical , i.e. which must not be missed
          because they can be interlaced in physical request ---*/
    case SidReadDataByIdentifier:
           LnReadDataByIdentifier(false);
           break;
    case SidInitiateDiagnosticOperation:
           LnInitiateDiagnosticOperation();
		   break;
    case SidReturnToNormalMode:
           LnReturnToNormalMode();
           break;
    case SidDisableNormalCommunication:
           LnDisableNormalCommunication();
           break;
      case SidTesterPresent:
           LnTesterPresent ();
           break;
    case SidReportProgrammedState:
           LnReportProgrammedState();
           break;
    case SidProgrammingMode:
           LnProgrammingMode();
           break;		   
      default: /*--- This default statement in not doing anything intentionaly         ---*/
             /*--- This is important for the modular architecture of LnDiag services ---*/
           break;
   }
} /*** End of UpdateLnDiagServices ***/

/**********************************************************************/
/*** LnDiag service: RequestDownload                                ***/
/**********************************************************************/

#define DataFormatIdentifierNul                 (0x00)
#define LnDownloadUncompressedMemorySizeInvalid (true)

void LnRequestDownload (void)

  {
  /*  AddressType LnDownloadUncompressedMemorySize; */ /* NOT USED */
  uint8_t   LnDownloadDataFormatIdentifier;

  LnDownloadDataFormatIdentifier = (GetLnServiceData (1));

  if ((GetLnServiceDataLength () != 6) ||
      ((LnDownloadDataFormatIdentifier != DataFormatIdentifierNul) &&
       (LnDownloadUncompressedMemorySizeInvalid)))
    {
    SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
    }
  else
    {
    if ((!IsSecurityAccessUnlocked ()
        //||
       // !LnProgrammingModeActive
        ||
        (GetVIOS_EngTurning () && !LnDiagSvFlags.DownLoadGranted))
      //&&(!LnProgrammingBootRequested)
      )
      {
      SendLnStandardNegativeAnswer (ConditionsNotCorrectOrRequestSequenceError);
      }
    else
      {
      //LnProgrammingBootRequested = false;
     if (!LnDiagSvFlags.DownLoadRequested)
       {
        LnDiagSvFlags.DownLoadRequested = (bitfield16_t) true;

        /*--- When LnDiagSvFlags.DownLoadRequested is set true, all the background
              and interrupt logics that are not related to RAM download and execute
              via GMLAN should be disabled. ---*/
        /*--- QADC does not generate interrupts in the current version ---*/
        /*--- Disable all Tpu Interrupts ---*/
        DisableAllCanIntExceptGmlanDiag ();
        SendLnStandardPositiveAnswer (1);
        /*--- During this process NVM may get corrupted. show this ! ---*/
        //DevalidateNvMemory ();
        }
      else
        { /* RequestDownload already done */
        SendLnStandardPositiveAnswer (1);
        }
      }
    }
  } /*** End of LnRequestDownload ***/



/*****************************************************************************************/
/*** DownloadDataAndAnswerContinued routine needed by LnDiag service: RequestDownload  ***/
/*****************************************************************************************/

void DownloadDataAndAnswerContinued (void)

  {
  uint32_t          interrupt_state;
  uint16_t NbDataToDownload;
  #define NbOfDownloadedBytes (NbDataToDownload)

  interrupt_state = EnterCriticalSection();
  NbDataToDownload = GetLnServNbOfUsedBytesInRingBuffer ();
  RetrieveLnServNbBytesFromRingBuffer (NbDataToDownload,
                                       LnDownloadDestinationBufferPtr);
  if (GetLnRxCompleteWaitingAppToRespond ())
    { /*--- request with data has been completely received ---*/
    (GetLnServiceData (0)) = SidTransferData;
    SendLnStandardPositiveAnswer (1);
    LnDiagRoutinePtr = 0;
    }
  else
    {
    LnDownloadDestinationBufferPtr += NbOfDownloadedBytes;
    }
  ExitCriticalSection( interrupt_state );
  } /*** End of DownloadDataAndAnswerContinued ***/


/***************************************************************************************/
/*** RespOutOfRangeWhenRxCompleteReq routine needed by LnDiag service: TransferData  ***/
/***************************************************************************************/

void RespOutOfRangeWhenRxCompleteReq (void)

  {
  if (GetLnRxCompleteWaitingAppToRespond ())
    {
    (GetLnServiceData (0)) = SidTransferData;
    SendLnStandardNegativeAnswer (RequestOutOfRange);
    }
  } /*** End of RespOutOfRangeWhenRxCompleteReq ***/


/*****************************************************************************/
/*** DownloadDataAndAnswer routine needed by LnDiag service: DownloadData  ***/
/*****************************************************************************/

void DownloadDataAndAnswer (void)

  {
  uint32_t          interrupt_state;
  uint32_t MemPtr;
  uint16_t NbDataToDownload;
#define NbOfDownloadedBytes (NbDataToDownload)

  MemPtr = (((uint32_t) (GetLnServiceData (2)) << 24) |
            ((uint32_t) (GetLnServiceData (3)) << 16) |
            ((uint16_t) (GetLnServiceData (4)) <<  8) |
            (GetLnServiceData (5)) );
  NbDataToDownload = GetLnServiceDataLength () - 6;
  if ((GetRAMStartAddrForUpDownload () <= (uint8_t *) MemPtr)
      &&
      ((uint8_t *) (MemPtr + NbDataToDownload) < GetRAMEndAddrForUpDownload ()))
    { /*--- Range of  RAM for downloading ram dl and execute routines ---*/

    /*--- First 6 bytes are retrieved but not used because not data to be Downloaded ---*/
    RetrieveLnServNbBytesFromRingBuffer (6, (uint8_t *) (GetWrtbufferAddr ()));

    interrupt_state = EnterCriticalSection();
    NbDataToDownload = GetLnServNbOfUsedBytesInRingBuffer ();
    RetrieveLnServNbBytesFromRingBuffer (NbDataToDownload,
                                         (uint8_t *) MemPtr);
    if (GetLnWaitingReqstRxStrtdApplCanStart ())
      { /*--- request with data has not been completely received ---*/
      LnDownloadDestinationBufferPtr = (uint8_t*) MemPtr + NbOfDownloadedBytes;
      LnDiagRoutinePtr = DownloadDataAndAnswerContinued;
      }
    else
      { /*--- request with data has been completely received ---*/
      SendLnStandardPositiveAnswer (1);
      }
    ExitCriticalSection( interrupt_state );
    }
  else
    {
    if (GetLnRxCompleteWaitingAppToRespond ())
      {
      SendLnStandardNegativeAnswer (RequestOutOfRange);
      }
    else
      {
      LnDiagRoutinePtr = RespOutOfRangeWhenRxCompleteReq;
      }
    }
  } /*** End of DownloadDataAndAnswer ***/


/**********************************************************************/
/*** LnDiag service: TransferData                                   ***/
/**********************************************************************/

#define SubFuncDownload                    (0x00)
#define SubFuncDownloadAndExecuteOrExecute (0x80)
#define EraseFlashMain  (0x00000004)
#define EraseFlashParam (0x00000005)
#define EraseFlashBoot  (0x00000006)
#define CopyKernelToRam (0x00000009)
#define EcuReset        (0x00000000)
#define JumpToBoot      (0x00000001)

void LnTransferData (void)

  {
  uint8_t TransferDataSubFunction;
  uint32_t  MemAddr;
   Can8DataBytesArrayType *Can8_DataBytesArrayPtr;

  TransferDataSubFunction = (GetLnServiceData (1));

  if (!IsSecurityAccessUnlocked ()
      ||
      !LnDiagSvFlags.DownLoadRequested)
    {
    SendLnStandardNegativeAnswer (ConditionsNotCorrectOrRequestSequenceError);
    }
  else
    {
    switch (TransferDataSubFunction)
      {
      case SubFuncDownload:
        if (GetLnServiceDataLength () > 7)
          {
          DownloadDataAndAnswer ();
          }
        else
          {
          SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
          }
        break;
      case SubFuncDownloadAndExecuteOrExecute:
        if (GetLnServiceDataLength () < 6)
          { /*---first download data before execute ---*/
          SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
          }
        else
          {
          MemAddr = (((uint32_t) (GetLnServiceData (2)) << 24) |
                     ((uint32_t) (GetLnServiceData (3)) << 16) |
                     ((uint16_t) (GetLnServiceData (4)) <<  8) |
                     (GetLnServiceData (5)));
          if (GetLnServiceDataLength () > 6)
            { /*---first download data before execute ---*/
            DownloadDataAndAnswer ();
            LnDiagRoutinePtr = (LnDiagFunctionPtrType) MemAddr;
            }
          else
            { /*--- case execute only ---*/
            switch ((uint16_t)MemAddr)
              {
              case (uint16_t)JumpToBoot:
                   /* send positive response and prepare function for next loop */
                   /* stopping the application SW and case a reset */
                   DevalidateNvMemory(); /* Do not rely on NVM after jumping to boot as
                                            it is overwritten in the boot */
                   SendLnStandardPositiveAnswer (1);
                   LnDelayedAction=LnAction_JumpToBoot;
                   break;
				   
              case (uint16_t)EraseFlashMain:
              case (uint16_t)EraseFlashParam:
              case (uint16_t)EraseFlashBoot:
              case (uint16_t)EcuReset:
                   SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
                   break;
				   
             case  (uint16_t)CopyKernelToRam:
			       if ( GetVIOS_n_EngSpd() < V_RPMa( 200 ) &&
         			  GetVIOS_v_VehSpd() < V_KPH( 3 ) )
   					{
				   		SendLnStandardPositiveAnswer (1);
	           	   		KW2KCAN_Received_Message (*Can8_DataBytesArrayPtr);
					}
					else
					{
						SendLnStandardNegativeAnswer(ConditionsNotCorrectOrRequestSequenceError);
					}
                   break;
              default:
                   SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
                   LnDiagRoutinePtr = (LnDiagFunctionPtrType) MemAddr;
                   break;
              }
            }
         }
        break;
      default:
        SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
        break;
      }
    }
  } /*** End of LnTransferData ***/



/**********************************************************************/
/*** Periodic Local Network service handler logic (Every Loop)      ***/
/**********************************************************************/
void UpdateLnDiagServices (void)
{
   First_msg_queued = 0x00;
   if (!GetLnEcuSendingAnswer())
   { /* This logic executes actions that need to be executed after an answer has been sent out */
      switch (LnDelayedAction)
      {
       case LnAction_JumpToBoot:
         DoJumpToBoot(); /* This function will never return ... */
         break;
       default:
         /* No action requested */
         break;
      }
      LnDelayedAction=LnNoAction;
   }
   UpdateOBD_Services();
   if (!LnDiagSvFlags.PreviousCommState && GetLnCommunicationActiveState ())
    /*--- Transition from OFF to ON (established) ---*/
   {
      LnDiagSvFlags.SecurityAccessUnlocked = (bitfield16_t) (!IsSecurityAccessActivated ());
   }

   if (LnDiagSvFlags.PreviousCommState && !GetLnCommunicationActiveState ())
    /*--- Transition from ON to OFF (not established) ---*/
   {
     // ClearOFVC_AllDeviceControlParameters ();
      LnDiagSvFlags.WaitingForWriteDataByIdToComplete = (bitfield16_t) false;
   }

   LnDiagSvFlags.PreviousCommState = GetLnCommunicationActiveState ();

   if (!IsDownLoadGranted ())
   {
      if (LnDiagSecurityDelayTimer)
      {
         LnDiagSecurityDelayTimer--;
      }
      if (S3ServerTimer)
      {
         S3ServerTimer--;
      }
      if( LnDiagResponsePendingFunctionPtr != 0)
      {
         (*LnDiagResponsePendingFunctionPtr) ();
      }
   }

   if (LnDiagSvFlags.ReadMemoryByAddressActive)
   {
      UpdateLnReadMemoryByAddress ();
   }

 //  if (LnDiagSvFlags.ReadSupportedDTCActive)
  // {
  //    UpdateLnReadDTCGetSupportedDTCData (0 , false, true);
   //
   //
 //  }
  /*--- New service fully or partially received, start processing received data ---*/
  /*--- only for services which support this feature                            ---*/
  /*--- NOTE: Services listed here should NOT be listed below with the normal   ---*/
  /*--- services to avoid triggering them twice.                                ---*/
  if (GetLnRxCompleteWaitingAppToRespond () ||
      (GetLnWaitingReqstRxStrtdApplCanStart () &&
      (LnDiagRoutinePtr != DownloadDataAndAnswerContinued)))
    {
    switch (GetLnServiceDataServiceId ())
         {
        case SidTransferData:
               LnTransferData ();
               break;
        default: /*--- This default statement in not doing anything intentionaly         ---*/
                 /*--- This is important for the modular architecture of LnDiag services ---*/
               break;
        }
     }
   if (GetLnRxCompleteWaitingAppToRespond ())
   { /*--- New service received ---*/
      OBD_ByCAN();
      S3ServerTimer = C_R7p8125ms16 (DS_S3SERVER_TIME);
      switch (GetLnServiceDataServiceId ())
      {
       // case SidRequestCurrentPowertrainDiagData:      /*--- $01 ---*/
       //        J1979Mode1Handler_DCAN();
      //         break;
       // case SidRequestPowertrainFreezeFrameData:      /*--- $02 ---*/
      //         J1979Mode2Handler_DCAN ();
      //         break;
      //  case SidRequestEmmissionPowertrainDTC:         /*--- $03 ---*/
      //         J1979Mode3Handler_DCAN ();
      //         break;
    //    case SidClearDiagnosticInformation:            /*--- $04 ---*/
      //         J1979Mode4Handler_DCAN ();
     //          break;
     //   case SidRequestOnBoardTestResult:              /*--- $06 ---*/
     //          J1979Mode6Handler_DCAN ();
     //          break;
      //  case SidRequestOnBoardTestResultContinuous:    /*--- $07 ---*/
      //         J1979Mode7Handler_DCAN ();
      //         break;
      //  case SidRequestVehicleInformation:             /*--- $09 ---*/
      //         J1979Mode9Handler_DCAN ();
      //         break;
      #if (XeSYST_CANOBD_NonLegislatedSrvs==CeSYST_AVAILABLE )
        case SidInitiateDiagnosticOperation:                  /*---$10---*/
               LnDiagnosticSessionControl();         
               break;
        case SidEcuReset :                                             /*---$11---*/
               LnEcuReset ();         
               break;		   
        case SidClearDiagInformation:                   /*---$14---*/
               LnClearDiagnosticInformation ();         
               break;
       // case SidReadDiagnosticInformation:                   /*---19---*/
           //    LnReadDiagnosticInformation ();
         //      break;
       // case SidReadDataByCommonIdentifier:              /*---$22---*/
        //       LnReadDataByCommonIdentifier ();
        //       break;
        case SidReadMemoryByAddress:                         /*---$23---*/
               LnReadMemoryByAddress ();
               break;
	#if 0
        case SidDynamicallyDefineMessage:             /*---$2c---*/      
               LnDynamicallyDefineMessage ();
               break;
	#endif
        case SidRequestDownload:                           /*---$34---*/
               LnRequestDownload ();
               break;

	 case SidTesterPresent:                            /*---$3e---*/
               LnTesterPresent ();
               break; 
      #endif
        default:
	    if (ExtendedDiagnosticSessionControl)
	    {
	       switch (GetLnServiceDataServiceId ())
           {
           case SidSecurityAccess:                                   /*---$27---*/
                LnSecurityAccess ();
	    break;
	    case SidWriteDataByIdentifier:                          /*---2E---*/
	         LnWriteDataByIdentifier ();
           break;
           //case SidReadDataByPacketIdentifier:                 /* ---2A---*/
              //  LnReadDataByPacketIdentifier ();
           //break;
	   // case SidInputOutputControlByIdentifier:             /*---2F---*/
                //LnInputOutputControlByIdentifier();
          // break;
	    case SidRoutineControl:                                     /*---31---*/
                LnRoutineControl();
           break; 
           default:
             if (GetLnServReqMsgAddressingMode () == PhysicalAddressing)
             {
                 SendLnStandardNegativeAnswer (ServiceIdNotSupported);
             }
        }
	 }
	 else
	 {
           if (GetLnServReqMsgAddressingMode () == PhysicalAddressing)
           {
              SendLnStandardNegativeAnswer (ServiceIdNotSupported);
           }
        }
     } 
   }
  

//   local_Timer++;
   //VbOFVC_Runing_CAN=CbTRUE;
} /*** End of UpdateLnDiagServices ***/

/*********************************************************************/
/*** Initialize LnDiag application level service Security Access   ***/
/*********************************************************************/
 void InitializeLnDiagSvSecurityAccess (void)
{
   InitializeSecurityAccessTiming ();
   LnDiagSvFlags.SecurityAccessUnlocked = (bitfield16_t) (!IsSecurityAccessActivated ());
   SPS_Security_Key_Allowed = false;
} /*** End of InitializeLnDiagSvSecurityAccess ***/

/*********************************************************************/
/*** Initialize LnDiag application level service handler.          ***/
/*********************************************************************/
void InitializeLnDiagServices (void)
{
 // InitNormalCommEnablingConditions();
   InitializeLnDiagSvCommunication ();
   InitializeLnDiagSvSecurityAccess ();

   LnDiagSvFlags.ReadMemoryByAddressActive = (bitfield16_t) false;
   LnDiagSvFlags.ReadSupportedDTCActive = (bitfield16_t) false;
} /*** End of InitializeLnDiagServices ***/

 /*********************************************************************
* FUNCTION:     InitializeDCAN_Services                              *
*                                                                    *
* Type:         global                                               *
*                                                                    *
* DESCRIPTION:  Initialize DCAN application level service handler.   *
*********************************************************************/
void InitializeDCAN_Services (void)
{
   //TriggerSecurityTiming () ;
   SetECUResetPending( CbFALSE) ;
   SetCopyAndExecuteKernelPending(CbFALSE);
   CommunicationStatus = CbFALSE ;
   //local_Timer         = 0;
  // VbOFVC_Runing_CAN =CbFALSE;
} /*** End of InitializeDCAN_Services ***/

 /*********************************************************************/
/*** CANOBD Answer still being sent.                         ***/
/*********************************************************************/
TbBOOLEAN DCAN_AnswerStillBeingSent( void )
{
   return (GetLnEcuSendingAnswer()
           || GetLnEcuWaitingP2cMinBeforeAns());
}
 
bool DCAN_GetCommunicationActiveState( void )
{
   return ( GetLnCommunicationActiveState() );
}

void DCAN_SendStandardNegativeAnswer( uint8_t NegativeResponseCode )
{
   SendLnStandardNegativeAnswer(NegativeResponseCode);	
}

void DCAN_SendStandardPositiveAnswer (register uint16_t MsgSize)
{
   SendLnStandardPositiveAnswer( MsgSize);
}


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* base of T300
*1. 20090808     cjqq      Added Legisted CANOBD
*2. 20090930     cjqq      Added NonLegisted CANOBD
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 platform.
* 4.0  100915    hdg  xxx  Added service ID for implementing CAN Flash in MT22.1 platform.
* 3    100917    wj  CTC RSM8069
*                          Updated for CAN reflash
*
******************************************************************************/


