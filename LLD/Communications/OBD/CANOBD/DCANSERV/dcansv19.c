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
* Filename     : dcansv19.c                                            *
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
* 1.2   03-12-11  cjqq    Delted the limited of 64DTC                  *
* 2     03-07-12  cjqq    Add 3 bytes DTC                              *
* 3     04-09-12  cjqq    Fix the bug about config_Compiler_Vendor     *  
* 4     04-12-12  cjqq    Modify DTCGetDTCSnapshotIdentification()     *
*                         BuildResponse_SID19_5() for 3 bytes DTC      *
* 5    120704 cjqq xxxx   Fix the bug of 3rd DTC not right at SID 19 02*
* 9    130830 xll  RCR1239 Change GetMaxPIDTableIndex() instead of     *
*                          CyDIAG_MAX_PID_INDEX                        *
* 10   140124 xll  SCR1375 fix the issue to use a ring buffer for reading DTC * 
* 11   140701 xll  RSM#8333 MT92_Add New Subfunction 04 and 06 for SID19
******************************************************************************/
#include "dcansv19.h"
#if (XeDCAN_SID_19_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdsfexi.h"/*GetCMNDTCP_Code*/
#include "obdlfpid.h"/*Mode_12,VeDIAG_PID*/
#include "obdlfdtc.h"/*SetRequestedFrame*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcanserv.h"
#include "dcancomm.h"

/******************************************************************************
 * Static Variables
 *****************************************************************************/
static WORD SwIndex_buffer=0, SwLocation_num_of_PIDs=0;
static WORD CurrentDtcInedx;
static WORD CurrentDataInedx;
/***********************************************************************
* Functions in this file:                                              *
************************************************************************

***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
#define NUM_OF_DTCExtendedDataRecord 3
const BYTE DTCExtendedDataRecordNumberList[NUM_OF_DTCExtendedDataRecord]=
{0x01,0x02,0xFF};
/**********************************************************************/
/*** LnDiag service: (SID19)                ***/
/**********************************************************************/
/*********************************************************************/
/* DESCRIPTION   Returns TRUE, if the given DTC is emission related  */
/*               type, otherwise FALSE.  An emission related DTC is  */
/*               of TYPE A or TYPE B.                                */
/*********************************************************************/
#define CheckDCANDTC_IfDTCEmissionRelated( Count )  (GetDGDM_DTC_EmissionsType(Count))


BYTE GetDCANDTCStatusByte ( WORD DTCIndex )
{
  /* This bit structure conforms to the status byte defined in the
     protocol. */
#if CPU_BigEndian
/* This is for,Diab */
  typedef union
  {
     BYTE y_DTC_Status;
     struct {
         BYTE b_bit_7 : 1;
         BYTE b_bit_6 : 1;
         BYTE b_bit_5 : 1;
         BYTE b_bit_4 : 1;
         BYTE b_bit_3 : 1;
         BYTE b_bit_2 : 1;
         BYTE b_bit_1 : 1;
         BYTE b_bit_0 : 1;
         } s_DTC_Status;
  } DTC_Status;
 #else
 typedef union
  {
     BYTE y_DTC_Status;
     struct {
         BYTE b_bit_0 : 1;
         BYTE b_bit_1 : 1;
         BYTE b_bit_2 : 1;
         BYTE b_bit_3 : 1;
         BYTE b_bit_4 : 1;
         BYTE b_bit_5 : 1;
         BYTE b_bit_6 : 1;
         BYTE b_bit_7 : 1;
         } s_DTC_Status;
  } DTC_Status;
#endif

  DTC_Status DTC_Status_Var ;

   DTC_Status_Var.s_DTC_Status.b_bit_0 =
                               GetCMNDTCFaultActiveStatus(DTCIndex) ;//bit 0
   DTC_Status_Var.s_DTC_Status.b_bit_1 =
                               GetCMNDTC_TestFailedThisKeyOnStatus(DTCIndex) ;//bit 1
   DTC_Status_Var.s_DTC_Status.b_bit_2 =
                             ( GetCMNDTC_TestFailedThisKeyOnStatus(DTCIndex) ||
                               GetCMNDTC_ActivePriorTripStatus(DTCIndex) ||
                               GetCMNDTC_InternalHistFaultFlag(DTCIndex) );//bit 2
   DTC_Status_Var.s_DTC_Status.b_bit_3 =
                               GetCMNDTCHistoryStatus(DTCIndex) ;//bit 3
   DTC_Status_Var.s_DTC_Status.b_bit_4 =
                             ( GetCMNDTCTestNotPassedSnceCdClrStatus(DTCIndex) &&
                              !GetCMNDTCTestFailSinceCodeClrStatus(DTCIndex) );//bit 4

   DTC_Status_Var.s_DTC_Status.b_bit_5 = 
                               GetCMNDTCTestFailSinceCodeClrStatus(DTCIndex);//bit 5
   DTC_Status_Var.s_DTC_Status.b_bit_6 =
                            ( !GetCMNDTC_TestPassedThisKeyOnStatus(DTCIndex) &&
                              !GetCMNDTC_TestFailedThisKeyOnStatus(DTCIndex) );//bit 6

   DTC_Status_Var.s_DTC_Status.b_bit_7 =
                               GetCMNDTCLightRequestStatus(DTCIndex);//bit 7
   return(DTC_Status_Var.y_DTC_Status);
}

/***********************************************************************
*       NAME                                PARAMETER                  *
*                                                                      *
* Get_Next_Matching_P_Code       numDTC, statusMask, Output buffer     *
*                                                                      *
* Description:  This function services the request 0x19 SID            *
*                                                                      *
* Returns:                                                             *
************************************************************************/
DTC_TEST_STATUS_INFO_TYPE *Get_Next_Matching_P_Code (
                                   uint16_t Count,
                                   uint8_t RequestMask,
                                   bool emission, bool supported )
{

   WORD ReadDTCFaultCode;
   uint8_t ReadTestStatus ;
   BYTE ReadDTCFailureType;
   static DTC_TEST_STATUS_INFO_TYPE DTCMainRecord;

   DTCMainRecord.DTC_Number.Word_Access = 0;
   DTCMainRecord.DTC_Status = 0;
   DTCMainRecord.DTC_Valid = CbFALSE;
   DTCMainRecord.DTC_Test_Status = 0;


   /* A DTC is valid
        - if fault-type is valid &
        - at least one of the requested mask bits are set in the
          DTC status byte.
          */
  ReadDTCFaultCode  = GetCMNDTCP_Code(Count);
  ReadTestStatus = GetDCANDTCStatusByte( Count ) ;
  ReadDTCFailureType = GetCMNDTC_FailureTypeByte(Count);
  
  if (  CheckCMNIfDTCFaultTypeValid( Count ) )
  {
    if(( ( ReadTestStatus & RequestMask ) &&
         ( (CheckDCANDTC_IfDTCEmissionRelated( Count ) && emission) ||
           (!emission))) || 
       (supported))
    {
      DTCMainRecord.DTC_Number.Word_Access = ReadDTCFaultCode;
	  DTCMainRecord.DTC_FailureType = ReadDTCFailureType; 
      DTCMainRecord.DTC_Valid = CbTRUE;
      DTCMainRecord.DTC_Test_Status = ReadTestStatus;
    }
  }

   return ( &DTCMainRecord );
}

#if 0
/***********************************************************************
*       NAME                                PARAMETER                  *
*                                                                      *
* DTCGetDTCByStatusMask   numDTC, statusMask, Output buffer     *
*                                                                      *
* Description:  This function services the request 0x19 SID            *
*                                                                      *
* Returns:                                                             *
************************************************************************/
 static void DTCGetDTCByStatusMask(uint8_t* buffer, uint16_t* numDTC, uint8_t statusMask,
                                     bool emission, bool supported)
{
   WORD DTC_Index = 0;
   WORD DTC_Count = 0;
   WORD Idx = 0;
   DTC_TEST_STATUS_INFO_TYPE DTC_Record, *DTC_RecordPtr;
   while (   DTC_Index  < GetCMNMaxNumberOfDTCs () )
   {
      /* Get the next valid DTC information */
      DTC_RecordPtr = Get_Next_Matching_P_Code ( DTC_Index, statusMask, emission, supported );
      DTC_Record = *DTC_RecordPtr;
      if ( DTC_Record.DTC_Valid )
      {
        /* build the message */
         DTC_Count++;
         if( buffer )
         {
           buffer[Idx] = DTC_Record.DTC_Number.Byte_Access.Byte_One;
           Idx++;

           buffer[Idx] = DTC_Record.DTC_Number.Byte_Access.Byte_Two;
           Idx++;

           /* NOTE: Iso 15031 and MECEL spec calls for LOW-BYTE of three-byte
              response = 0x00. The low byte is the "Failure Type Byte" which 
              Delphi does not support. Therefoe this must be 0x00. */
           buffer[Idx] = 0;
           Idx++;

           buffer[Idx] = DTC_Record.DTC_Test_Status;
           Idx++;
         }
      }
        DTC_Index ++;
      /*This is to limit the maximum response length to 261 bytes due to
        RAM shortage. 64 DTCs * 4 = 256 bytes plus 3 bytes for POSID, sub
        function and status mask.*/
      if(buffer)
      {
        if(64 == DTC_Count)
        {
            break;
        }
      }
   }
   *numDTC = DTC_Count;
}
#endif
/***********************************************************************
*       NAME                                PARAMETER                  *
*                                                                      *
* DTCGetSupportdDTC   numDTC, statusMask, Output buffer     *
*                                                                      *
* Description:  This function services the request 0x19 SID            *
*                                                                      *
* Returns:                                                             *
************************************************************************/
 static void DTCGetSupportedDTCNum(uint16_t* numDTC,
                                   uint8_t RequestMask,
                                   bool emission, bool supported )
{
   uint16_t DTC_Index = 0;
   uint16_t DTC_Count = 0;

   while (   DTC_Index  < GetCMNMaxNumberOfDTCs () )
   {
      if (  CheckCMNIfDTCFaultTypeValid ( DTC_Index ) )
      {
         if(( ( GetDCANDTCStatusByte ( DTC_Index ) & RequestMask ) &&
              ( (CheckDCANDTC_IfDTCEmissionRelated( DTC_Index ) && emission) ||
              (!emission))) || 
              (supported))
         {
            DTC_Count++;
         }
      }
      DTC_Index++;  
   }
   *numDTC = DTC_Count;  
}

/***********************************************************************
*       NAME                                PARAMETER                  *
*                                                                      *
* DTCGetSupportedDTCData   numDTC, statusMask, Output buffer     *
*                                                                      *
* Description:  This function services the request 0x19 SID            *
*                                                                      *
* Returns:                                                             *
************************************************************************/
 static void DTCGetSupportedDTCData(uint8_t* buffer, uint8_t statusMask,
                                     bool emission, bool supported)
{
   uint16_t DTC_Index = 0;
   uint16_t DTC_Count = 0;
   uint16_t Idx = 0;
   DTC_TEST_STATUS_INFO_TYPE DTC_Record, *DTC_RecordPtr;
   
   EmissionDTC = emission;
   SupportedDTC = supported;	   
   CurrentStatusMask = statusMask;
   while (   DTC_Index  < GetCMNMaxNumberOfDTCs () )
   {
      /* Get the next valid DTC information */
      DTC_RecordPtr = Get_Next_Matching_P_Code ( DTC_Index, statusMask, emission, supported );
      DTC_Record = *DTC_RecordPtr;
      if ( DTC_Record.DTC_Valid )
      {
        /* build the message */
         DTC_Count++;
         buffer[Idx++] = DTC_Record.DTC_Number.Byte_Access.Byte_One;
         buffer[Idx++] = DTC_Record.DTC_Number.Byte_Access.Byte_Two;
           /* NOTE: Iso 15031 and MECEL spec calls for LOW-BYTE of three-byte
              response = 0x00. The low byte is the "Failure Type Byte" which 
              Delphi does not support. Therefoe this must be 0x00. */
         buffer[Idx++] = DTC_Record.DTC_FailureType;
         buffer[Idx++] = DTC_Record.DTC_Test_Status;
      }
      DTC_Index ++;
      if (2 == DTC_Count)
      {
         LnDiagSvFlags.ReadSupportedDTCActive = (bitfield16_t)true;
	     CurrentDtcInedx = DTC_Index;	 
	     LnServiceDataBeingInserted = true;
	     LnServiceDataFrame.CurrentDataLength = Idx+3;
	     LnNbOfUsedBytesInRingBuffer =Idx+3;
	     CurrentDataInedx = Idx+3;
	     break;
      }
   } 
}

void UpdateLnReadDTCGetSupportedDTCData ( uint8_t statusMask,
                                     bool emission, bool supported)
{
   WORD DTC_Count = 0;
   DTC_TEST_STATUS_INFO_TYPE DTC_Record, *DTC_RecordPtr;

   if ( LnNbOfUsedBytesInRingBuffer < 253)/*253=261-8, write the data in buffer should after the old data in this buffer have been transmitted*/
   {
       while (   CurrentDtcInedx  < GetCMNMaxNumberOfDTCs () )
       {
          /* Get the next valid DTC information */
          DTC_RecordPtr = Get_Next_Matching_P_Code ( CurrentDtcInedx, statusMask, emission, supported );
          DTC_Record = *DTC_RecordPtr;
          if ( DTC_Record.DTC_Valid )
          {
            /* build the message */
             DTC_Count++;
             (GetLnServiceData ())[CurrentDataInedx++] = DTC_Record.DTC_Number.Byte_Access.Byte_One;
             if (CurrentDataInedx>260)
             {
          	    CurrentDataInedx=0;
             }
             (GetLnServiceData ())[CurrentDataInedx++] = DTC_Record.DTC_Number.Byte_Access.Byte_Two;
             if (CurrentDataInedx>260)
             {
          	    CurrentDataInedx=0;
             }
               /* NOTE: Iso 15031 and MECEL spec calls for LOW-BYTE of three-byte
                  response = 0x00. The low byte is the "Failure Type Byte" which 
                  Delphi does not support. Therefoe this must be 0x00. */
             (GetLnServiceData ())[CurrentDataInedx++] = DTC_Record.DTC_FailureType;
             if (CurrentDataInedx>260)
             {
          	    CurrentDataInedx=0;
             }
             (GetLnServiceData ())[CurrentDataInedx++] = DTC_Record.DTC_Test_Status;
             if (CurrentDataInedx>260)
            {
          	    CurrentDataInedx=0;
             }
             LnServiceDataFrame.CurrentDataLength = LnServiceDataFrame.CurrentDataLength+4;
    	  LnNbOfUsedBytesInRingBuffer = LnNbOfUsedBytesInRingBuffer+4;
          }
          CurrentDtcInedx ++;
          if(2 == DTC_Count)
          {
              break;
          }
       }
   }
   if (LnServiceDataFrame.CurrentDataLength == LnServiceDataFrame.DataLength)
   {
      LnDiagSvFlags.ReadSupportedDTCActive = (bitfield16_t) false;
      LnServiceDataBeingInserted = false;
   }
}
/*****************************************************************************
* Function Name :  DTCGetDTCSnapshotIdentification
*
* Description : This function stores the DTC number and the Failure
*               Record number in the response message.
*
* Parameters:   snapshotRecord, numRec
* 
* Return Type: TbBOOLEAN
*
******************************************************************************/
static void DTCGetDTCSnapshotIdentification(uint8_t* snapshotRecord, uint16_t* numRec)
{
   BYTE LyDTCFailure_Record_num=0,LyIndex_snapshotRecord=0;
   uint16_t Lwnumrec= 0;
   WORD LwDTC_number=0;
   BYTE Lylow_byte=0,Lyhigh_byte=0;

   while(LyDTCFailure_Record_num <= CcDGDM_FailureRecords)
   {
     /* Get the DTC Number */

     LwDTC_number = Get_Freeze_Frame_DTC(LyDTCFailure_Record_num);

     /* If the dtc is set, store it in Snapshot record */
     if(0 != LwDTC_number)
     {
        Lylow_byte = (LwDTC_number & 0x00FF);
        Lyhigh_byte = ((LwDTC_number & 0xFF00) >> 8);
        snapshotRecord[LyIndex_snapshotRecord++] = Lyhigh_byte;
        snapshotRecord[LyIndex_snapshotRecord++] = Lylow_byte;

     /* NOTE: ISO 14229 and MECEL spec calls for LOW-BYTE of three-byte
              response = 0x00. The low byte is the "Failure Type Byte" which 
              Delphi does not support. Therefore this must be 0x00. */
      snapshotRecord[LyIndex_snapshotRecord++] = LnFailureRecordsTypeByte;
      snapshotRecord[LyIndex_snapshotRecord++] = LyDTCFailure_Record_num;
      Lwnumrec++;
     }
     else
     {
       /* Do nothing */
     }
     LyDTCFailure_Record_num++;
   }
   *numRec= Lwnumrec;
}

/*****************************************************************************
* Function Name :  Getindex_DTC
*
* Description : This function gets the status byte corresponding to the dtc no.
*
* Parameters:   LwDTC_number
* 
* Return Type:  BYTE
*
******************************************************************************/
static WORD Getindex_DTC(WORD LwDTC_number)
{
   WORD LwDTC_Index=0,LwIndex_DGDM_array=0;
   while(LwIndex_DGDM_array < GetCMNMaxNumberOfDTCs())
   {
     if(LwDTC_number == GetCMNDTCP_Code(LwIndex_DGDM_array))
      {
       LwDTC_Index = LwIndex_DGDM_array;
       break;
      }
      LwIndex_DGDM_array++;
    }
   return(LwDTC_Index);
}
/*****************************************************************************
* Function Name :  BuildResponse_SID19_4_5
*
* Description : This function builds the response format for service 19 sub-
*               option 4 or 5 as specified by ISO 14229 Specification
*
* Parameters:   recordNumber,buffer
* 
* Return Type: None
*
******************************************************************************/
static void BuildResponse_SID19_4_5(uint8_t  recordNumber,uint8_t* buffer, uint8_t subFunction)
{
   BYTE LyPID_arrayIndex=0,LyNum_of_PIDs=0;
   BYTE Lylow_byte=0,Lyhigh_byte=0;
   WORD LwDTC_number=0;

       LwDTC_number = Get_Freeze_Frame_DTC(recordNumber);

       /* If the DTC is set then build the message */
       if(0 != LwDTC_number)
       {
        /*if sub-function is 05, record number is before DTC,it is in #3 byte in response
          if sub-function is 04, record number is after DTC, it is in #7 byte in response*/
        if(0x05 == subFunction)
        {
            buffer[SwIndex_buffer++] = recordNumber;
        }
        Lylow_byte = (LwDTC_number & 0x00FF);
        Lyhigh_byte = ((LwDTC_number & 0xFF00) >> 8);
        /* Store the DTC Number*/
        buffer[SwIndex_buffer++] = Lyhigh_byte;
        buffer[SwIndex_buffer++] = Lylow_byte;

     /* NOTE: ISO 14229 and MECEL spec calls for LOW-BYTE of three-byte
              response = 0x00. The low byte is the "Failure Type Byte" which 
              Delphi does not support. Therefore this must be 0x00. */
        buffer[SwIndex_buffer++] = LnFailureRecordsTypeByte;

        buffer[SwIndex_buffer++] =
            GetDCANDTCStatusByte(Getindex_DTC(LwDTC_number));
         
        if(0x04 == subFunction)
        {
            buffer[SwIndex_buffer++] = recordNumber;
        }

      /* Save the location of Snapshot Record to fill the Number of PIDs */
        SwLocation_num_of_PIDs = SwIndex_buffer++;
        SetRequestedFrame(recordNumber);
        WrtRequestedMode(Mode_12);

       /* Fill Snapshot Record with the PID number and the corresponding
           Freeze Frame data */
        while(LyPID_arrayIndex < GetMaxPIDTableIndex())
        {
          if(GetPIDMode(LyPID_arrayIndex, Mode_12))
           {
            Lylow_byte = (GetPIDNumber(LyPID_arrayIndex) & 0x00FF);
            Lyhigh_byte = ((GetPIDNumber(LyPID_arrayIndex) & 0xFF00) >> 8);
            buffer[SwIndex_buffer++] = Lyhigh_byte;
            buffer[SwIndex_buffer++] = Lylow_byte;
	     VeDIAG_PID =  LyPID_arrayIndex;
           // SwIndex_buffer += PfrmDCAN_ReqstdPIDData((buffer+SwIndex_buffer), LyPID_arrayIndex);
            SwIndex_buffer += ProcessReqstdPIDData((buffer+SwIndex_buffer), 0,LyPID_arrayIndex);
	        LyNum_of_PIDs++;
           }
          LyPID_arrayIndex++;
        }
        buffer[SwLocation_num_of_PIDs] = LyNum_of_PIDs;
       }
       else
       {
         buffer[SwIndex_buffer++] = recordNumber;
       }
}

/*****************************************************************************
* Function Name :  DS_DTCGetDTCSnapshotRecordByDTCNumber_Srv
*
* Description : This function stores the DTC number,the Failure
*               Record number,the number of PID's and the Freeze Frame
*               data in the response message.
*
* Parameters:   buffer, bufLength,recordNumber
* 
* Return Type: TbBOOLEAN
*
******************************************************************************/
static void DTCGetDTCSnapshotRecordByRecordNumber(uint8_t* buffer,uint16_t* bufLength,uint8_t  recordNumber,uint8_t subFunction)
{
    SwIndex_buffer = 0;
    BuildResponse_SID19_4_5(recordNumber,buffer,subFunction);
    *bufLength = SwIndex_buffer;
}

static T_COUNT_BYTE Get_Self_Healing_counter(uint16_t dtcId)
{
    T_COUNT_BYTE counter;
    
    if(CheckDCANDTC_IfDTCEmissionRelated(dtcId))
    {
        counter = NcDGDM_EmisRelatdWarmUpCntr;
    }
    else
    {
        counter = NcDGDM_NonEmisRelatdWarmUpCntr;
    }

    return counter;
}
/*****************************************************************************
* Function Name :  BuildResponse_SID19_5
*
* Description : This function builds the response format for service 19 sub-
*               option 6 as specified by ISO 14229 Specification
*
* Parameters:   recordNumber,buffer
* 
* Return Type: None
*
******************************************************************************/
static void BuildResponse_SID19_6(uint8_t  recordNumber,uint8_t* buffer, uint16_t dtcId)
{
    buffer[SwIndex_buffer++] = GetDCANDTCStatusByte(dtcId);
    switch(recordNumber)
    {
        case 0x01:
            buffer[SwIndex_buffer++] = 0x01;
            buffer[SwIndex_buffer++] = Get_Self_Healing_counter(dtcId);
            break;
        case 0x02:
            buffer[SwIndex_buffer++] = 0x02;
            buffer[SwIndex_buffer++] = GetDGDM_TripCounter(dtcId);
            break;
        case 0xff:
            buffer[SwIndex_buffer++] = 0x01;
            buffer[SwIndex_buffer++] = Get_Self_Healing_counter(dtcId);
            buffer[SwIndex_buffer++] = 0x02;
            buffer[SwIndex_buffer++] = GetDGDM_TripCounter(dtcId);
            break;
        default:
            break;
    }
}
/*****************************************************************************
* Function Name :  DS_DTCGetDTCExtendedRecordByDTCNumber_Srv
*
* Description : This function stores the DTC number,the Extended Data Record
*               in the response message.
*
* Parameters:   buffer, bufLength,recordNumber
* 
* Return Type: TbBOOLEAN
*
******************************************************************************/
static void DTCGetDTCExtendedRecordByRecordNumber(uint8_t* buffer,uint16_t* bufLength,uint8_t  recordNumber,uint16_t dtcId)
{
    SwIndex_buffer = 0;
    BuildResponse_SID19_6(recordNumber,buffer,dtcId);
    *bufLength = SwIndex_buffer;
}

/**********************************************************************/
/*** LnDiag service: ReadDiagnosticInformation ($19)                ***/
/**********************************************************************/
void LnReadDiagnosticInformation (void)
{
   uint16_t numDtc;
   uint16_t numRec;
   uint16_t numBytes;
   uint16_t ReqDtcRecord;
   uint16_t ReqRecordNum;
   uint16_t ReqDtcId;
   uint16_t DtcIdReadByRecordNum;
   uint8_t   subFunction;
   uint8_t   maskstatus;
   uint16_t msglength;
   bool  suppressPosRespMsgIndicationBit;
   bool  PositiveResponse;
   bool  DtcSupport;
   bool  FindSnapshotFlag;
   uint8_t recordnumber;
   uint8_t ExtendedIdx;
   bool FindDtcInList;

   PositiveResponse = false;
   FindSnapshotFlag = false;
   FindDtcInList = false;
   if(GetLnServiceDataLength () < 2)
   {
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      suppressPosRespMsgIndicationBit = ((GetLnServiceData ()) [1]  & 0x80) ? true : false;
      subFunction = ((GetLnServiceData ()) [1]  & 0x7f);
      maskstatus = (GetLnServiceData ()) [2];
      
      
      msglength = 1;
      switch(subFunction)
      {
         case 0x01:  /* reportNumberOfDTCByStatusMask */
         case 0x12:  /* reportNumberOfEmissionsRelatedOBDDTCByStatusMask */
           if(GetLnServiceDataLength () != 3)
           {
              SendLnStandardNegativeAnswer (IncorrectMessageLength);
           }
           else
           {
              if(0x01 == (GetLnServiceData ()) [1])
              {   /* reportNumberOfDTCByStatusMask */
                 //DTCGetDTCByStatusMask( (void*)0, &numDtc, maskstatus, false, false );
                 DTCGetSupportedDTCNum( &numDtc, maskstatus, false, false );
              }
              else
              {   /* reportNumberOfEmissionsRelatedOBDDTCByStatusMask */
                 //DTCGetDTCByStatusMask( (void*)0, &numDtc, maskstatus, true, false );
                 DTCGetSupportedDTCNum( &numDtc, maskstatus, true, false );
              }
              WrtDCAN_ServiceData( subFunction, msglength++ ) ;
              WrtDCAN_ServiceData( 0xff, msglength++ ) ; 
              WrtDCAN_ServiceData( 0x01, msglength++ ) ; 
              WrtDCAN_ServiceData((((numDtc)>>8) & 0xff), msglength++ ) ; 
              WrtDCAN_ServiceData(((numDtc) & 0xff), msglength++ ) ; 
              PositiveResponse = true;
           }
       break;
       case 0x02:  /* reportDTCByStatusMask */
          if(GetLnServiceDataLength ()!= 3)
          {
             SendLnStandardNegativeAnswer (IncorrectMessageLength);
          }
          else
          {
               /* reportDTCByStatusMask */
             WrtDCAN_ServiceData( subFunction, msglength++ ) ;
             WrtDCAN_ServiceData( 0xff, msglength++ ) ;
             DTCGetSupportedDTCNum(&numDtc, maskstatus, false, false);
             msglength = (uint16_t)(3 + (numDtc * 4)); 
             DTCGetSupportedDTCData((GetLnServiceData ()+3), maskstatus, false, false);
             //DTCGetDTCByStatusMask( (GetLnServiceData ()+3), &numDtc, maskstatus, false, false );
	         PositiveResponse = true;
          }
	 break;
        case 0x03:  /* reportDTCSnapshotIdentification */
          if(GetLnServiceDataLength () != 2)
          {
             SendLnStandardNegativeAnswer (IncorrectMessageLength);
          }
          else
          {
             WrtDCAN_ServiceData( subFunction, msglength++ ) ;
             DTCGetDTCSnapshotIdentification((GetLnServiceData ()+2), &numRec);
             msglength = (uint16_t)(2 + (numRec * 4));
	         PositiveResponse = true;
          }
        break;
     case 0x04:  /* ReportDTCSnapshotRecordByDTCNumber */
          if(GetLnServiceDataLength ()!= 6)
          {
             SendLnStandardNegativeAnswer (IncorrectMessageLength);
          }
          else
          {
             WrtDCAN_ServiceData( subFunction, msglength++ ) ;
             ReqDtcRecord = (GetLnServiceData () [2] << 8 )+ (GetLnServiceData () [3]);
             ReqDtcId = Getindex_DTC(ReqDtcRecord);
             DtcSupport = CheckCMNIfDTCFaultTypeValid(ReqDtcId);
             ReqRecordNum = GetLnServiceData () [5];
             if(( (0xFF != ReqRecordNum)
                 &&(ReqRecordNum > CcDGDM_FailureRecords))
                 ||(!DtcSupport))
             {
                 SendLnStandardNegativeAnswer (RequestOutOfRange);
             }
             else
             {
                if(0xFF != ReqRecordNum)
                {
                    DtcIdReadByRecordNum = Get_Freeze_Frame_DTC_FaultID(ReqRecordNum);
                    if(DtcIdReadByRecordNum == ReqDtcRecord)
                    {
                        FindSnapshotFlag = true;
                        recordnumber = ReqRecordNum;
                    }
                }
                else
                {
                    recordnumber = 0;
                    while(recordnumber <= CcDGDM_FailureRecords)
                    {
                        DtcIdReadByRecordNum = Get_Freeze_Frame_DTC_FaultID(recordnumber);
                        if(DtcIdReadByRecordNum == ReqDtcRecord)
                        {
                            FindSnapshotFlag = true;
                            break;
                        }
                        recordnumber++;
                    }
                }
                if(FindSnapshotFlag)
                {
                    DTCGetDTCSnapshotRecordByRecordNumber((GetLnServiceData ()+2),&numBytes,recordnumber,subFunction);
                    msglength  = (uint16_t)(2 + numBytes);
                }
                else
                {
                    msglength = msglength+3;
                    WrtDCAN_ServiceData( GetDCANDTCStatusByte(ReqDtcId), msglength++ ) ;
                }
                PositiveResponse = true;
             }
          }
          break;
          
	 case 0x05:  /* reportSnapshotRecordByRecordNumber */
          if(GetLnServiceDataLength ()!= 3)
          {
             SendLnStandardNegativeAnswer (IncorrectMessageLength);
          }
          else
          {
             WrtDCAN_ServiceData( subFunction, msglength++ ) ;
              if((GetLnServiceData ()) [2]>4)
             {
                 SendLnStandardNegativeAnswer (RequestOutOfRange);
             }
             else
             {
                DTCGetDTCSnapshotRecordByRecordNumber((GetLnServiceData ()+2), &numBytes, maskstatus,subFunction);
          msglength  = (uint16_t)(2 + numBytes);
          PositiveResponse = true;
             }

          }
        break;
        case 0x06:  /* ReportDTCExtendedDataRecordbyDTCNumber */
             if(GetLnServiceDataLength ()!= 6)
             {
                SendLnStandardNegativeAnswer (IncorrectMessageLength);
             }
             else
             {
                WrtDCAN_ServiceData( subFunction, msglength++ ) ;
                ReqDtcRecord = (GetLnServiceData () [2] << 8) + (GetLnServiceData () [3]);
                ReqDtcId = Getindex_DTC(ReqDtcRecord);
                DtcSupport = CheckCMNIfDTCFaultTypeValid(ReqDtcId);
                ReqRecordNum = GetLnServiceData () [5];

                for(ExtendedIdx=0; ExtendedIdx < NUM_OF_DTCExtendedDataRecord; ExtendedIdx++)
                {
                    if(DTCExtendedDataRecordNumberList[ExtendedIdx]== ReqRecordNum)
                    {
                        FindDtcInList = true;
                        break;
                    }
                }
                if(( !FindDtcInList)
                 ||(!DtcSupport))
                {
                    SendLnStandardNegativeAnswer (RequestOutOfRange);
                }
                else
                {
                   DTCGetDTCExtendedRecordByRecordNumber((GetLnServiceData ()+5), &numBytes, ReqRecordNum,ReqDtcId);
                   msglength = (uint16_t)(5+numBytes);
                   PositiveResponse = true;
                }
             }
		break;
        case 0x0A:  /* reportSupportedDTCs */
          if(GetLnServiceDataLength () != 2)
          {
             SendLnStandardNegativeAnswer (IncorrectMessageLength);
          }
          else
          {
             WrtDCAN_ServiceData( subFunction, msglength++ ) ;
             WrtDCAN_ServiceData( 0xff, msglength++ ) ; 
             DTCGetSupportedDTCNum(&numDtc, 0, false, true);
             msglength = (uint16_t)(3 + (numDtc * 4)); 
             DTCGetSupportedDTCData((GetLnServiceData ()+3), 0, false, true);
             PositiveResponse = true;
          }
        break;
        case 0x13:  /* reportEmissionsRelatedOBDDTCByStatusMask */
          if(GetLnServiceDataLength ()  != 3)
          {
             SendLnStandardNegativeAnswer (IncorrectMessageLength);
          }
          else
          {
             WrtDCAN_ServiceData( subFunction, msglength++ ) ;
             WrtDCAN_ServiceData( 0xff, msglength++ ) ;
             DTCGetSupportedDTCNum(&numDtc, maskstatus, true, false);
             msglength = (uint16_t)(3 + (numDtc * 4)); 
             DTCGetSupportedDTCData((GetLnServiceData ()+3), maskstatus, true, false);
             //DTCGetDTCByStatusMask((GetLnServiceData ()+3), &numDtc, maskstatus , true, false );
	      PositiveResponse = true;
          }
        break;
        default:

          SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
		break;
      }
      if ( PositiveResponse )
      {
         if( suppressPosRespMsgIndicationBit )
         {
            PfrmDCAN_AckReqWithoutResponse ();
         }
         else 
         {
            SendLnStandardPositiveAnswer(msglength);
         }
      }
   }
} /*** End of LnReadDiagnosticInformation ***/

#endif


