/***********************************************************************
*  DELCO ELECTRONICS CORPORATION, INC.                                 *
*  COPYRIGHT 1999 DELCO ELECTRONICS CORPORATION, INC.                  *
*  ALL RIGHTS RESERVED                                                 *
*  This program may not be reproduced, in whole or in part in any form *
*  or by any means whatsoever without the written permission of:       *
*                                                                      *
*         DELCO ELECTRONICS CORPORATION                                *
*         One Corporate Center                                         *
*         Kokomo, Indiana  46904-9005                                  *
*         USA                                                          *
*                                                                      *
************************************************************************
* Filename     : dcansv2a.c                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : CANOBD                                *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 10 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 10 as the defined by the above applicable doc.*
*                                                                      *
*                Set the keyword 2000 diagnostic mode to be the        *
*                Standard Diagnostitic State or to be the              *
*                ECU Programming State by the request message.         *
*                In the ECU Programming State, this service can change *
*                the communication baud rate to be the desired baud    *
*                rate.                                                 *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2002:kw2srv10.c $              *
* $Revision$                                                     *
* $Author: brighton.tcb:/users/sa..._2002_MathLib:safayyad $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-12-98  JZha    Initial file creation                        *
* 2.1.2 08-30-13  mzh1qz  RCR#1239 Added LbValid_PID in function       *
*                                  LnBuildAndTxCan8Data()              *
******************************************************************************/
#include "dcansv2a.h"
#if (XeDCAN_SID_2A_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdsfexi.h"/*GetCMNDTCP_Code*/
#include "obdlfpid.h"/*Mode_22,VeDIAG_PID,ProcessReqstdPIDData*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcansv10.h"/*DS_S3SERVER_TIME*/
#include "dcanserv.h"
#include "dcancomm.h"

/******************************************************************************
 * Global Variables
 *****************************************************************************/
Array7PidType LnDpidsTxDefinitionArray[8]=
{
        /*  PIDListDataPacket_1 */
        { 0x1100,
           0x1101,
           0x1102,
           0x1103,
           0x0011,
           0x11A1
        },
        /*  PIDListDataPacket_2 */
        { 0x000C,
           0x12B1,
           0x000B,
           0x000D,
           0x0005
        },
        /*  PIDListDataPacket_3 */
        { 0x1469,
           0x000F,
           0x11AC,
           0x0042
        },
       /*  PIDListDataPacket_4 */
        { 0x1145,
           0x1146,
           0x0000,
           0x11D7,
           0X121A         
        },
       /*  PIDListDataPacket_5 */
        { 0x123F,
           0x1241,
           0x1212,
           0x0000
        },
       /*  PIDListDataPacket_7 */
        { 0x12F0,
           0x1200,
           0x11E4,
           0x11E6
       },
       /*  PIDListDataPacket_8 */
        { 0x1509,
           0x1505,
           0x1504,
           0x1506,
           0x119E
        },
       /*  PIDListDataPacket_A */
        { 0x0000,
           0x0000,
           0x0000,
           0x0000,
           0x139E,
           0x13AA
        }
  };

const uint8_t DpidNumberTab [] =
  {
    Dpid01,
    Dpid02,
    Dpid03,
    Dpid04,
    Dpid05,
    Dpid07,
    Dpid08,
    Dpid0A
  };
//typedef uint8_t DpidType;

/*--- design choice ---*/
/*--- it was decided to implement LnDpidTxSchedulerTable in code/flash section
      instead of RAM like
      LnDpidTxSchedulerType LnDpidTxSchedulerTable [NumberOfSupportedDPIDs];
      for a cpu time usage reason and also for saving code size.
      use of dynamic table in RAM would have implicate either:
      - rearrangement/move of the DPIDs LnDpidTxSchedulerType every time
        one or several DPID(s) would be deleted: shifting up the DPIDs by a the nb of DPIDs
        deleted when deleting DPID(s)
      - no real interest in the case of keeping holes in the table when deleting DPID(s) in
        term of cpu usage time versus having the table as constant in the code. ---*/

/*****************************/
/* DPIDs Tx definition array */
/*****************************/
#define NumberOfSupportedDPIDs (sizeof(DpidNumberTab))

LnDpidTxSchedulerType LnDpidTxScheduler [NumberOfSupportedDPIDs];

/*--- definition of the Maximum Number of DPIDs that can be scheduled simultaneously ---*/
#define MaxNbOfDpidThatCanBeScheduledSimultaneously (NumberOfSupportedDPIDs)
/*--- this number limitates the cpu time needed by this service ---*/
/*--- it can be extended to NumberOfSupportedDPIDs ---*/

#define MaxNumberOfDpidToTxWithinOneLoop (TX_MSG_BUFFER_NUMBER - 1)
/*--- This number is the maximum number of Dpid frames that can be requested to be ---*/
/*--- transmitted in one call to ScheduleReadDataByPacketIdentifier ().            ---*/
/*--- it is limited by the maximum number of free (empty) buffer for transmission. ---*/
/*--- "-1" because Dpid service is certainly not the only application using a Tx buffer ---*/

#define MaxNumberOfDpidToTxOverFastPeriod (3 * MaxNumberOfDpidToTxWithinOneLoop)
/*--- This number is the maximum number of Dpid frames that can be requested to be ---*/
/*--- transmitted during the fast rate period. The fast rate period is 100 ms and   ---*/
/*--- so lasts 12 calls to ScheduleReadDataByPacketIdentifier ().                   ---*/
/******************************************************************************
 * Static Variables
 *****************************************************************************/
static uint16_t      NbOfPeriodicDpidCurrentlyScheduled;
static TwTIME_t_R7p8125ms DpidDistributedFisrtTxTime;
static uint8_t NbDpidScheduledAtFastRate;
/***********************************************************************
* Functions in this file:                                              *
************************************************************************

***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
/**********************************************************************/

/**********************************************************************/
/*********************************************************************/
/* DESCRIPTION   Returns TRUE, if the given DTC is emission related  */
/*               type, otherwise FALSE.  An emission related DTC is  */
/*               of TYPE A or TYPE B.                                */
/*********************************************************************/
/**********************************************************************/
/*** LnDiag service: ReadDataByPacketIdentifier    (SID2A)                ***/
/**********************************************************************/

/**********************************************************************/
/*** ClearAndDisableAllDpids function needed for                    ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
 void ClearAndDisableAllDpids (void)
{
   uint16_t Index;

   NbOfPeriodicDpidCurrentlyScheduled = 0;
   for (Index = 0; Index < NumberOfSupportedDPIDs; Index++)
   {
  //  LnDpidTxScheduler [Index].NbOneShotTxRequested  = 0;
      LnDpidTxScheduler [Index].PeriodicTransmissionRate = NoTransmissionPeriod;
      LnDpidTxScheduler [Index].PeriodCounter = 0;
   }
} /*** End of ClearAndDisableAllDpids ***/

void LnBuildAndTxCan8Data (CanIdType CanId, uint16_t DpidIndex)
{
   Can8DataBytesArrayType Can8DataBytesArray;
   uint8_t PIDListIndex;
   uint8_t ArrayIndex;
   uint16_t ParamID;
   TbBOOLEAN LbValid_PID;

  /* first element is the DPID number */
   Can8DataBytesArray [0] = DpidNumberTab [DpidIndex];

   PIDListIndex = 0;
   ArrayIndex = 1;

   while (ArrayIndex < 8)
   {
      ParamID = LnDpidsTxDefinitionArray [DpidIndex][PIDListIndex];

      if (ParamID == PIDDUMMY)
      {
         Can8DataBytesArray [ArrayIndex++] = 0;
      }
      else
      {
	  	/*All pids in LnDpidsTxDefinitionArray is in PID_Definition_Array;
		there is no need to look up the special custom's PID array*/
	  	 LbValid_PID = Get_Valid_PID_Info(ParamID, MaskMode_22);
         if (CbTRUE == LbValid_PID)
         {
		 	/*ArrayIndex = PfrmDCAN_ReqstdPIDData(&Can8DataBytesArray [0], ArrayIndex ,
                                   GetVeDIAG_PIDIndex() ) ;*/

      		ArrayIndex = ProcessReqstdPIDData(&Can8DataBytesArray [0], ArrayIndex ,
                                   GetVeDIAG_PIDIndex() ) ;
         }
      }
      PIDListIndex++;
   }
   RequestCanToTransmit (CanId, &Can8DataBytesArray);
}  /*** End of LnBuildAndTxCan8Data ***/

/**********************************************************************/
/*** ScheduleReadDataByPacketIdentifier function needed for         ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/*** Every Loop routine                                             ***/
/**********************************************************************/
static void ScheduleReadDataByPacketIdentifier (void)
{
   uint16_t DpidIndex;
  /*--- check scheduling of all periodic transmission ---*/
   for (DpidIndex = 0; DpidIndex < NumberOfSupportedDPIDs; DpidIndex++)
   {
      if (LnDpidTxScheduler [DpidIndex].PeriodicTransmissionRate != NoTransmissionPeriod)
      { /* periodic task is scheduled */
         if (LnDpidTxScheduler [DpidIndex].PeriodCounter == 0)
         {
            LnBuildAndTxCan8Data (DiagRespPhysclRespPeriodicCanId,
                              DpidIndex);
            LnDpidTxScheduler [DpidIndex].PeriodCounter =
            LnDpidTxScheduler [DpidIndex].PeriodicTransmissionRate;
         }
      LnDpidTxScheduler [DpidIndex].PeriodCounter -= 1;
      }
   }
} /*** End of ScheduleReadDataByPacketIdentifier ***/

/**********************************************************************/
/*** UpdateReadDataByPacketIdentifier function needed for           ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/*** Every Loop routine                                             ***/
/**********************************************************************/
void UpdateReadDataByPacketIdentifier (void)
{
   ScheduleReadDataByPacketIdentifier ();
} /*** End of UpdateReadDataByPacketIdentifier ***/

/**********************************************************************/
/*** TellIfDpidIsSupported function needed for                      ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
static bool TellIfDpidIsSupported (DataPacketIdentifierType DpidArg)
{
   uint16_t DpidIndex;
   bool  DpidIsSupported;

   DpidIsSupported = false;
   for (DpidIndex = 0 ; DpidIndex < NumberOfSupportedDPIDs && !DpidIsSupported; DpidIndex++)
   {
      if (DpidNumberTab [DpidIndex] == DpidArg)
      {
         DpidIsSupported = true;
      }
   }
   return DpidIsSupported;
} /*** End of TellIfDpidIsSupported ***/

/**********************************************************************/
/*** GetIndexOfDpidInSchedulerTable function needed for             ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/***      return index of DPID in SchedulerTable if found           ***/
/***      return NumberOfSupportedDPIDs if not found                ***/
/**********************************************************************/
uint16_t GetIndexOfDpidInSchedulerTable (DataPacketIdentifierType DpiDArg)
{
   uint16_t DpidIndex;
   bool  DpidIsSupported;

   DpidIsSupported = false;
   DpidIndex = 0;
   while (DpidIndex < NumberOfSupportedDPIDs && !DpidIsSupported)
   {
      if (DpidNumberTab [DpidIndex] == DpiDArg)
      {
         DpidIsSupported = true;
      }
      else
      {
         DpidIndex++;
      }
   }
   return DpidIndex;
} /*** End of GetIndexOfDpidInSchedulerTable ***/

/**********************************************************************/
/*** TellIfDpidByIndexIsAlreadyScheduled function needed for        ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
static bool TellIfDpidByIndexIsAlreadyScheduled (uint16_t DpidIndex)
{
   bool  DpidIsScheduled;

   if (LnDpidTxScheduler [DpidIndex].PeriodicTransmissionRate == NoTransmissionPeriod)
   {
      DpidIsScheduled = false;
   }
   else
   {
      DpidIsScheduled = true;
   }
   return DpidIsScheduled;
} /*** End of TellIfDpidByIndexIsAlreadyScheduled ***/

/**********************************************************************/
/*** UpdateNumberOfDpidCurrentlyScheduled function needed for       ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
static void UpdateNumberOfDpidCurrentlyScheduled (void)
{
   uint16_t TempNbOfPeriodicDpidCurrentlyScheduled;
   uint16_t Index;

   TempNbOfPeriodicDpidCurrentlyScheduled = 0;
   for (Index = 0; Index < NumberOfSupportedDPIDs; Index++)
   {
      if (LnDpidTxScheduler [Index].PeriodicTransmissionRate != NoTransmissionPeriod)
      {
         TempNbOfPeriodicDpidCurrentlyScheduled++;
      }
   }
   NbOfPeriodicDpidCurrentlyScheduled = TempNbOfPeriodicDpidCurrentlyScheduled;
} /*** End of UpdateNumberOfDpidCurrentlyScheduled ***/

/**********************************************************************/
/*** GetNbDpidScheduledAtRate function needed for                   ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
static uint8_t GetNbDpidScheduledAtRate (uint8_t Rate)
{
   TwTIME_t_R7p8125ms PeriodicTxRate;
   uint8_t NbDpidsScheduled;
   uint16_t Index;

   PeriodicTxRate = (Rate == ScheduleAtSlowRate ? SlowRatePeriod :
                    (Rate == ScheduleAtMediumRate ? MediumRatePeriod : FastRatePeriod));
   NbDpidsScheduled = 0;
   for (Index = 0; Index < NumberOfSupportedDPIDs; Index++)
   {
       if (LnDpidTxScheduler [Index].PeriodicTransmissionRate == PeriodicTxRate)
      {
         NbDpidsScheduled++;
      }
   }
   return NbDpidsScheduled;
} /*** End of GetNbDpidScheduledAtRate ***/

/**********************************************************************/
/*** ScheduleDpidByIndexAndTxPeriodRate function needed for         ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
void ScheduleDpidByIndexAndTxPeriodRate (uint16_t DpidIndex,
                                         PeriodicTransmissionRateType PeriodicTransmissionRate)
{
   LnDpidTxScheduler [DpidIndex].PeriodicTransmissionRate = PeriodicTransmissionRate;
   LnDpidTxScheduler [DpidIndex].PeriodCounter = DpidDistributedFisrtTxTime++;
   if (DpidDistributedFisrtTxTime >= LnDpidTxScheduler [DpidIndex].PeriodicTransmissionRate)
   {
      DpidDistributedFisrtTxTime = 0;
   }
   UpdateNumberOfDpidCurrentlyScheduled ();
} /*** End of ScheduleDpidByIndexAndTxPeriodRate ***/

/**********************************************************************/
/*** StopSendingPeriodicDpid function needed for                    ***/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
static void StopSendingPeriodicDpid (DataPacketIdentifierType Dpid)
{
   uint16_t DpidIndex;

   DpidIndex = GetIndexOfDpidInSchedulerTable (Dpid);
   LnDpidTxScheduler [DpidIndex].PeriodicTransmissionRate = NoTransmissionPeriod;
} /*** End of StopSendingPeriodicDpid ***/

/**********************************************************************/
/*** LnDiag service: ReadDataByPacketIdentifier                     ***/
/**********************************************************************/
void LnReadDataByPacketIdentifier (void)
{
   uint16_t NumberOfDPIDs;
   bool RequestIsValid;
   uint8_t SubFunctParameter;
   uint16_t NumberOfNewDPIDsRequested;
   uint16_t Index;
   uint16_t DpidIndexInSchedulerTable;
   bool AllDpidsValid;
   DataPacketIdentifierType RequestedDpid;
   PeriodicTransmissionRateType PeriodicTransmissionRate;
  // Can8DataBytesArrayType Can8DataBytesArray;

   RequestIsValid = true;
   NumberOfDPIDs = 0;
   NumberOfNewDPIDsRequested = 0;
   SubFunctParameter = GetLnServiceDataSubFunctParameter ();
   if (((GetLnServiceDataLength () < 3) && (StopSending != SubFunctParameter))
    || ((GetLnServiceDataLength () < 2) && (StopSending == SubFunctParameter)))
   {
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
	  RequestIsValid = false;
   }
   else 
   {
      NumberOfDPIDs = (GetLnServiceDataLength ()) - 2;

   /*
   if (GetLnServReqMsgAddressingMode () == FunctionalAddressing)
   {
      PfrmDCAN_AckReqWithoutResponse();
      RequestIsValid = false;
   }*/
      if((GetLnServiceDataSubFunctParameter () > 4)
   	       ||
   	       (GetLnServiceDataSubFunctParameter () <1))
      {
         SendLnStandardNegativeAnswer (RequestOutOfRange);
         RequestIsValid = false;
      }
      else if ((GetLnServiceDataLength () < 2)
           ||
           ((SubFunctParameter != StopSending) && (NumberOfDPIDs < 1))
           ||
           ((NumberOfDPIDs > MaxNbOfDpidThatCanBeScheduledSimultaneously) &&
            (SubFunctParameter > 0x00)))
      {
         SendLnStandardNegativeAnswer (IncorrectMessageLength);
         RequestIsValid = false;
      }
      else 
      {
    /*********************************************************************
    Check if all DPIDs are valid  and also check how many DPIDs in the request are not 
    already scheduled (if the the sub-function parameter($Level)is $01, $02 or $03).
    These checks are performed in order to determine whether its possible to execute the request
    *********************************************************************/
         AllDpidsValid = true;
         Index = 0; /*--- local counter to traverse the DPIDs in request ---*/
         do
         {
            RequestedDpid = (DataPacketIdentifierType ) ((GetLnServiceData ()) [Index + 2]);
            if (TellIfDpidIsSupported (RequestedDpid))
            {
               DpidIndexInSchedulerTable = GetIndexOfDpidInSchedulerTable (RequestedDpid);
               if (!TellIfDpidByIndexIsAlreadyScheduled (DpidIndexInSchedulerTable))
               {
                  NumberOfNewDPIDsRequested++;
               }
            }
            else
            { /*--- one received DPID is not supported ---*/
               AllDpidsValid = false;
            }
            Index++;
         }
         while ((AllDpidsValid) && (Index < NumberOfDPIDs));
         if (!AllDpidsValid)
         {
            SendLnStandardNegativeAnswer (RequestOutOfRange);
            RequestIsValid = false;
         }
         else if (SubFunctParameter != StopSending)
         {
            NbDpidScheduledAtFastRate = GetNbDpidScheduledAtRate (ScheduleAtFastRate);
            if (((SubFunctParameter > 0x00) /*--- the PDS would Overflow if the Request was Processed ---*/
            &&
            (NumberOfNewDPIDsRequested > (MaxNbOfDpidThatCanBeScheduledSimultaneously
                                         - NbOfPeriodicDpidCurrentlyScheduled)))
            ||
            ((SubFunctParameter == ScheduleAtFastRate)
            &&
            ((NbDpidScheduledAtFastRate + NumberOfNewDPIDsRequested) >
             MaxNumberOfDpidToTxOverFastPeriod)))
            {
               SendLnStandardNegativeAnswer (RequestOutOfRange);
               RequestIsValid = false;
            }
        }
      }
    } /*--- end elseif (SubFunctParameter != StopSending) ---*/
   /*********************************************************************
   If Request Message is Valid, Process Service AA Message
   ***********************************************************************/
   if (RequestIsValid)
   {
      switch (SubFunctParameter)
      {
      case StopSending:
        if (NumberOfDPIDs != 0)
        { /*--- the DPIDs to stop are specified ---*/
           for (Index = 0; Index < NumberOfDPIDs; Index++)
           {
              RequestedDpid = (DataPacketIdentifierType ) ((GetLnServiceData ()) [Index + 2]);
              DpidIndexInSchedulerTable = GetIndexOfDpidInSchedulerTable (RequestedDpid);
              if (TellIfDpidByIndexIsAlreadyScheduled (DpidIndexInSchedulerTable))
              { /*--- Dpid is scheduled ---*/
                 StopSendingPeriodicDpid (RequestedDpid);
                 NbOfPeriodicDpidCurrentlyScheduled--;
              }
            }
          }

        else
          { /*--- no specific DPID specified, stop all DPIDs ---*/
          for (Index = 0; Index < NumberOfSupportedDPIDs; Index++)
            {
            LnDpidTxScheduler [Index].PeriodicTransmissionRate = NoTransmissionPeriod;
            LnDpidTxScheduler [Index].PeriodCounter = 0;
            }
          NbOfPeriodicDpidCurrentlyScheduled = 0;
          }
        /*--- Send Positive Response ($00) in any case ---*/
        SendLnStandardPositiveAnswer (1);
        break;
      case ScheduleAtSlowRate:
      case ScheduleAtMediumRate:
      case ScheduleAtFastRate:
        SendLnStandardPositiveAnswer (1);
        PeriodicTransmissionRate = (SubFunctParameter == ScheduleAtSlowRate ? SlowRatePeriod :
                                    (SubFunctParameter == ScheduleAtMediumRate ? MediumRatePeriod :
                                     FastRatePeriod));
        /**************************************************************
        * Check Max Nb Of Dpid That Can Be Scheduled Simultaneously id
        * done before a few lines above
        **************************************************************/
        /**************************************************************
        * Check for each DPID in request to see if it is already scheduled
        * (present in PDS). If already scheduled, clear the transmit counter
        * so the DPID will be sent and then update the data rate for that DPID.
        * If the DPID is not in the PDS, then put it into the first vacant
        * location in the PDS, set it's rate, and initialize it's transmit
        * counter to $00 so it will be sent as soon as possible.
        **************************************************************/
        for (Index = 0; Index < NumberOfDPIDs; Index++)
          {
          RequestedDpid = (DataPacketIdentifierType ) ((GetLnServiceData ()) [Index + 2]);
          DpidIndexInSchedulerTable = GetIndexOfDpidInSchedulerTable (RequestedDpid);
          ScheduleDpidByIndexAndTxPeriodRate (DpidIndexInSchedulerTable,
                                              PeriodicTransmissionRate);
          }
	 S3ServerTimer = C_R7p8125ms16 (DS_S3SERVER_TIME);
        DpidDistributedFisrtTxTime = 0;
        break;

      default:
        SendLnStandardNegativeAnswer (RequestOutOfRange);
        RequestIsValid=false;
        break;
      } /*** end switch (SubFunctParameter) ---*/               
   }
} /*** End of LnReadDataByPacketIdentifier ***/
#endif

