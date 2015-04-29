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
 *                    UpdateLnReadFailureRecordAllParam
 *                    LnRespondToDisableNormComAfterFlush
 *                    LnDisableNormalCommunication
 *                    LnDynamicallyDefineMessage
 *                    LnRequestDownload
 *                    DownloadDataAndAnswerContinued
 *                    RespOutOfRangeWhenRxCompleteReq
 *                    DownloadDataAndAnswer
 *                    LnTransferData
 *                    WriteMemoryByAddress
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
 * %full_name:     ctc_pt3#2/csrc/dcanserv.c/3.14 %
 * %date_created:  Thu Jun 26 10:56:53 2014 %
 * %version:       3.14 %
 * %derived_by:    dzrpmq %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
// #include "obdsfexi.h"

/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanserv.h"  /* for LnDiagSvFlagsType, LnDiagSvFlags */
#include "dcanlegi.h"   /*for legist service*/
#include "dcansv2f.h" /*LnInputOutputControlByIdentifier()*/
#include "dcansv10.h" /*LnDiagnosticSessionControl()*/
#include "dcansv11.h" /*LnEcuReset ()*/
#include "dcansv14.h"/*LnClearDiagnosticInformation ()*/
#include "dcansv19.h"/*LnReadDiagnosticInformation()*/
#include "dcansv22.h"/*LnReadDataByCommonIdentifier ()*/
#include "dcansv23.h"/*LnReadMemoryByAddress ()*/
#include "dcansv27.h" /*LnSecurityAccess()*/
#include "dcansv2a.h" /*LnReadDataByPacketIdentifier ()*/
#include "dcansv2e.h" /*LnWriteDataByIdentifier()*/
#include "dcansv2f.h" /*LnInputOutputControlByIdentifier*/
#include "dcansv31.h"/*LnTesterPresent()*/
#include "dcansv3e.h"/*LnRoutineControl()*/
#include "dcansv28.h"/*LnCommunicationControl()*/
#include "dcansv85.h"/*LnControlDTCSetting()*/
#include "dcansvb0.h"/*TestService()*/
#include "kw2app.h"
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlfsrv.h"/*SetECUResetPending()*/
// #include "obdlfpid.h"/*Mode_12*/
// #include "obdlfdtc.h"/*ClearDiagnosticData()*/
#ifdef COMPILE_CANOBD_PCHUD
#include "pchdpall.h"
#endif
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"   /* for SubFunctionNotSupported_InvalidFormat..*/
// #include "io_dcan_config.h"
// #include "obdlcald.h"
/*****************************************************************************
 * Public constants & variables
 *****************************************************************************/
/**
 * This array of DS_SERVICE structs contains the available services in 
 * the DiagnosticSessionControl. The services must be sorted with lowest service-
 * identifier first. See the definition of type DS_SERVICE for information about 
 * the members.
 */
const DS_SERVICE DS_01_Session[] =
{
/*  Identifier,       ServiceFunc */
   {0x01,    J1979Mode1Handler_DCAN },
   {0x02,    J1979Mode2Handler_DCAN},
   {0x03,    J1979Mode3Handler_DCAN },
   {0x04,    J1979Mode4Handler_DCAN },
   {0x06,    J1979Mode6Handler_DCAN },
   {0x07,    J1979Mode7Handler_DCAN},
   {0x09,    J1979Mode9Handler_DCAN },
   {0x10,    LnDiagnosticSessionControl },
   {0x11,    LnEcuReset },
   {0x14,    LnClearDiagnosticInformation },
   {0x19,    LnReadDiagnosticInformation},
   {0x22,    LnReadDataByCommonIdentifier },
   {0x23,    LnReadMemoryByAddress },
   {0x3e,    LnTesterPresent },
   {0xb0,    TestService },
};

const DS_SERVICE DS_02_Session[] =
{
/*  Identifier,      ServiceFunc */
   {0x10,    LnDiagnosticSessionControl },
   {0x11,    LnEcuReset },
   {0x22,    LnReadDataByCommonIdentifier },
   {0x27,    LnSecurityAccess },
   {0x2e,    LnWriteDataByIdentifier },
   {0x31,    LnRoutineControl },
   {0x3e,    LnTesterPresent },
};

/**
 * This array of DS_SERVICE structs contains the available services in 
 * the DiagnosticSessionControl. The services must be sorted with lowest service-
 * identifier first. See the definition of type DS_SERVICE for information about 
 * the members.
 */
const DS_SERVICE DS_03_Session[] =
{
/*  Identifier,          ServiceFunc */
   {0x01,    J1979Mode1Handler_DCAN },
   {0x02,    J1979Mode2Handler_DCAN},
   {0x03,    J1979Mode3Handler_DCAN },
   {0x04,    J1979Mode4Handler_DCAN },
   {0x06,    J1979Mode6Handler_DCAN },
   {0x07,    J1979Mode7Handler_DCAN},
   {0x09,    J1979Mode9Handler_DCAN },
   {0x10,    LnDiagnosticSessionControl },
   {0x11,    LnEcuReset },
   {0x14,    LnClearDiagnosticInformation },
   {0x19,    LnReadDiagnosticInformation},
   {0x22,    LnReadDataByCommonIdentifier },
   {0x23,    LnReadMemoryByAddress },
   {0x27,    LnSecurityAccess },
   {0x28,    LnCommunicationControl},
   {0x2a,    LnReadDataByPacketIdentifier },
   {0x2e,    LnWriteDataByIdentifier },
   {0x2f,    LnInputOutputControlByIdentifier },
   {0x31,    LnRoutineControl },
   {0x3e,    LnTesterPresent },
   {0x85,    LnControlDTCSetting},
   {0xb0,    TestService },
};

/**
 * This array of DS_SESSION structs contains the available diagnostic sessions. 
 * The first record should be the default session.
 * See the definition of type DS_SERVICE for information about the members.
 */
const DS_SESSION DS_Sessions[DS_NUMBER_OF_SESSIONS] =
{
/*  Type, NumServices,                                                Services,       P2ServerMax, P2SServerMax */
    { 0x01, sizeof(DS_01_Session)/sizeof(DS_SERVICE), DS_01_Session,  0x0032,      0x01F4 },
    { 0x02, sizeof(DS_02_Session)/sizeof(DS_SERVICE), DS_02_Session,  0x0032,      0x01F4 },
    { 0x03, sizeof(DS_03_Session)/sizeof(DS_SERVICE), DS_03_Session,  0x0032,      0x01F4 },
};

/******************************************************************************
 *  Global Variables
 *****************************************************************************/
TbBOOLEAN                            SPS_Security_Key_Allowed;
uint32_t                        LnReadMemByAddrMemToReadPtr;
uint16_t                        LnReadMemByAddrNbBytesToRead;
uint8_t                         LnDgSecAccessSpsBadKeyCounter;
TwTIME_t_R7p8125ms              LnDiagSecurityDelayTimer;
volatile LnDiagSvFlagsType      LnDiagSvFlags;
TwTIME_t_R7p8125ms              S3ServerTimer;
DT_STATE_TYPE                   DataTransferState; 
uint8_t                         LnOldBlockSequenceCounter;
uint32_t                        DataTransferByteCounter;
uint32_t                        DataTransferAddress;
uint32_t                        LnSeed_Random;
uint8_t                         CurrentStatusMask;
bool                            EmissionDTC;
bool                            SupportedDTC;
/******************************************************************************
 * Static Variables
 *****************************************************************************/
static LnDelayedActionT             LnDelayedAction;

/******************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/
/**********************************************************************/
/*** Function prototype                                             ***/
/**********************************************************************/

/**********************************************************************/
/*** InitializeReadDataByPacketIdentifier function needed for       ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
static  void InitializeReadDataByPacketIdentifier (void)
{
   ClearAndDisableAllDpids ();
} /*** End of InitializeReadDataByPacketIdentifier ***/
/**********************************************************************/
/*** Is Security Access Activated                                   ***/
/**********************************************************************/
TbBOOLEAN IsSecurityAccessActivated (void)
{
   // return ((GetVIOS_ManufactEnableCounter () == 0));
   return 0;
} /*** End of IsSecurityAccessActivated ***/

/***********************************************************************/
/*** Initialize the lockout timer for security access to 10 seconds. ***/
/***********************************************************************/
static void InitializeSecurityAccessTiming (void)
{
  /* in the case of Flash reprogramming by GMLAN, a Security Access
     is requested after the reset before programming the watchdog cal
     and also after the reset before programming the EEPROM (VIN,...).
     in that case 2 times 10 sec can be saved in the process */
   if (IsSecurityAccessActivated ()
      &&
      !IsSecurityAccessUnlocked ())
   {
      // LnDiagSecurityDelayTimer = KfDCAN_t_SecurityAccessDelayTime;
   }
   else
   { /* normal case (not in flash programming) */
      LnDiagSecurityDelayTimer = C_R7p8125ms16 (0.0);
   }
  /* LnDgSecAccessSpsBadKeyCounter = 0; */
} /*** End of InitializeSecurityAccessTiming ***/

/*********************************************************************/
/*** Initialize LnDiag application level service Security Access   ***/
/*********************************************************************/
static void InitializeLnDiagSvSecurityAccess (void)
{
   InitializeSecurityAccessTiming ();
   LnDiagSvFlags.SecurityAccessUnlocked = (bitfield16_t) (!IsSecurityAccessActivated ());
   SPS_Security_Key_Allowed = CbFALSE;
} /*** End of InitializeLnDiagSvSecurityAccess ***/
/*********************************************************************/
/*** Initialize LnDiag application level service handler.          ***/
/*********************************************************************/
void InitializeLnDiagServices (void)
{
   InitializeLnDiagSvCommunication ();
   InitializeLnDiagSvSecurityAccess ();
   InitializeReadDataByPacketIdentifier ();

   LnDiagSvFlags.ReadMemoryByAddressActive = (bitfield16_t) false;
   LnDiagSvFlags.ReadSupportedDTCActive = (bitfield16_t) false;
   LnDiagSvFlags.WriteLongPIDData = (bitfield16_t) false;
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
   SetECUResetPending( CbFALSE) ;
   SetCopyAndExecuteKernelPending(CbFALSE);
   // local_Timer         = 0;
   // VbDiagServicesDisableDTCs = CbFALSE;
   VbDCAN_NRC78hexInProgress   = CbFALSE;
   VbDCAN_SendNRC78hexResponse = CbTRUE;
   CurrentSessionIndex = Default_session;
   CurrentStatusMask = 0;
   DataTransferState = DT_IDLE;
   VbCAN_OBD_Enabled = CbFALSE;
   VbKW2K_OBD_Enabled = CbFALSE;
   VbDCAN_SvIgnoredMessage = false;
   EmissionDTC = false; 
   SupportedDTC = false; 
   // LnFailureRecordsTypeByte = 0x00;
    // Initial_CANOBD_CAL_ID(KwDCANOBD_CANID);
} /*** End of InitializeDCAN_Services ***/

 /*********************************************************************/
/*** CANOBD Answer still being sent.                         ***/
/*********************************************************************/
TbBOOLEAN DCAN_AnswerStillBeingSent( void )
{
   return (GetLnEcuSendingAnswer()
           || GetLnEcuWaitingP2cMinBeforeAns());
}

/**********************************************************************/
/*** Unlock Security Access.                                        ***/
/**********************************************************************/
 void UnlockSecurityAccess_DCAN (void)
{
   LnDiagSvFlags.SecurityAccessUnlocked = true;
} /*** End of UnlockSecurityAccess_DCAN ***/

/*********************************************************************/
/***   Get Security Access flag state.                             ***/
/*********************************************************************/
 TbBOOLEAN GetLnVulnerabilityState (void)
{
   return LnDiagSvFlags.SecurityAccessUnlocked;
}

/**********************************************************************/
/*** Set the lockout timer for security access to 10 seconds.       ***/
/**********************************************************************/
void TriggerSecurityAccessTiming (void)
{
   LnDiagSecurityDelayTimer = C_R7p8125ms16 (10.0);
   LnDgSecAccessSpsBadKeyCounter = 0;
} /*** End of TriggerSecurityAccessTiming ***/

/***************************/
/*** function prototypes ***/
/***************************/
void LnEventFunctionalRequest (void)
{
   switch (GetLnServiceDataServiceId ())
   {
    /*--- only serve Request that seems critical , i.e. which must not be missed
          because they can be interlaced in physical request ---*/
      #if 0
      case SidReadDataByIdentifier:
           LnReadDataByIdentifier (false);
           break;
      #endif
      case SidTesterPresent:
	/* if we don't set S3ServerTimer to 5s, when we use CANID 7df to send $3E sevice, 
	S3ServerTimer will keep to 0 and server can't keep in a diagnostic session but 
	change to default session. */
	  	   S3ServerTimer = C_R7p8125ms16 (DS_S3SERVER_TIME);
           LnTesterPresent ();
           break;
      default: /*--- This default statement in not doing anything intentionaly         ---*/
             /*--- This is important for the modular architecture of LnDiag services ---*/
           break;
   }
} /*** End of UpdateLnDiagServices ***/


static void ServiceManager(DS_SESSION const * session)
{
   uint8_t  SIDIndex;
   TbBOOLEAN ValidSid;

   SIDIndex = 0;
   ValidSid = CbFALSE;
   while((SIDIndex<(session->NumServices)) && !ValidSid)
   {
      if(GetLnServiceDataServiceId () == session->Services[SIDIndex].Identifier)
      {
         ValidSid = CbTRUE;
      }
      else
      {
         SIDIndex++;
      }
   }
   if (ValidSid)
   {       
      session->Services[SIDIndex].ServiceFunc();
   }
   else
   { 
	   SIDIndex = 0;
       ValidSid = CbFALSE;
	   while((SIDIndex<(sizeof(DS_03_Session)/sizeof(DS_SERVICE))) && !ValidSid)
      {
      	if(GetLnServiceDataServiceId () == DS_03_Session[SIDIndex].Identifier)
      	{
         	ValidSid = CbTRUE;
      	}
      	else
      	{
         	SIDIndex++;
      	}
   	   }
       if(ValidSid)
       {
	   		SendLnStandardNegativeAnswer (ServiceIdNotSupportedInActiveSession);
	   }
	   else
	   {
	   		SendLnStandardNegativeAnswer (ServiceIdNotSupported);
	   	}
	   
   }
}

/**********************************************************************/
/*** Periodic Local Network service handler logic (Every Loop)      ***/
/**********************************************************************/
void UpdateLnDiagServices (void)
{
   TbBOOLEAN LbOFVC_OvrdConditionsValid;
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
   if ((!DCAN_AnswerStillBeingSent ())&& (VbCAN_OBD_Enabled))
   {
      UpdateOBD_Services();
   }
 
   if (!LnDiagSvFlags.PreviousCommState && GetLnCommunicationActiveState ())
    /*--- Transition from OFF to ON (established) ---*/
   {
      LnDiagSvFlags.SecurityAccessUnlocked = (bitfield16_t) (!IsSecurityAccessActivated ());
   }

   if (LnDiagSvFlags.PreviousCommState && !GetLnCommunicationActiveState ())
    /*--- Transition from ON to OFF (not established) ---*/
   {
      // ClearOFVC_AllDeviceControlParameters ();
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
   }

   if (LnDiagSvFlags.ReadMemoryByAddressActive)
   {
      UpdateLnReadMemoryByAddress ();
   }
   
   // if (LnDiagSvFlags.ReadSupportedDTCActive)
   // {
   //    UpdateLnReadDTCGetSupportedDTCData (CurrentStatusMask, EmissionDTC, SupportedDTC);
   // }
      
   /* Initialize OBD application type to default value. */
   // InitPIDApplictaion_Type();
   LnSeed_Random ++;
   //CurrentSession = (BYTE)(CurrentSessionIndex +1);
   if (GetLnRxCompleteWaitingAppToRespond ())
   { /*--- New service received ---*/
      OBD_ByCAN();
      S3ServerTimer = C_R7p8125ms16 (DS_S3SERVER_TIME);      
      ServiceManager(&DS_Sessions[CurrentSessionIndex]);
   }

  /*** function UpdateReadDataByPacketIdentifier must be called after the    ***/
  /*** requested service. Otherwise, the risk is that a new service be       ***/
  /*** trigerred because the event correponding to the previous still hasn't ***/
  /*** been received.                                                        ***/
   UpdateReadDataByPacketIdentifier ();

   if(VbDCAN_NRC78hexInProgress)
   {
     FormJ1979_NextMode49_DCAN();
   }
   if(!VbDCAN_NRC78hexInProgress)
   {
     VbDCAN_SendNRC78hexResponse = CbTRUE;
   }
   if (VbCAN_OBD_Enabled)
   {
      if ((GetLnCommunicationActiveState() == CbFALSE))
      {
         LbOFVC_OvrdConditionsValid = CbFALSE;
      }
      else
      {
         LbOFVC_OvrdConditionsValid = CbTRUE;
      }   
 /* Call this every 15.6 mS */
      // if( local_Timer % 2 == 0)
      // { 
      //    UpdateOFVC_PeriodicFunctions (LbOFVC_OvrdConditionsValid);
      //    UpdateOFVC_PendingDevCtrlRqst ();
      //    if (GetOFVC_OvrdRqstPending())
      //    {
      //       PostOFVC_LnResponseToRequest();
      //    }
      // }
      // local_Timer++;
   }
} /*** End of UpdateLnDiagServices ***/

void DefineOSTK_EmptyFunction(void)
{
  return;
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
*3. 20110401     cjqq      Constructure optimized
*4  120409       cjqq      Update the CANOBD per customer requirement  
*5  120412   cjqq   9602   Initialized LnFailureRecordsTypeByte 
*6  120704   cjqq   xxxx   Fix the bug of 3rd DTC not right at SID 19 02 
*7  120914   cjqq   xxxx   Add CurrentSession for PIDF186.
*8  121017   xll    xxxx   initianize CANOBD_Message_Parameter_Table and CanRxMesgControlTable
*9  130509   xll   SCR1111 Added the logic when Service ID Not Supported In the whole Session
*10 130604   xll   SCR1145 fix the bug:use CANID 7df to send $3E service can't keep sever in a diagnostic session.
*3.10 140307 tz9dw1 8285Rev0 Changed 0x1388 to 0x01F4 in DS_Sessions
*3.11 140520 xll   8133 RSM_CTC_8331_MT92_PCHUD_Function_Rev00_20140420
*3.12 140520 xll   SCR1584  Add InitPIDApplictaion_Type() in UpdateLnDiagServices().
******************************************************************************/


