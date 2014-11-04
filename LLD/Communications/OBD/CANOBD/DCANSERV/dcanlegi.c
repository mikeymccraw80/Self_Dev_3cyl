/******************************************************************************
 *
 * Filename:          dcanlegi.c
 *
 * Description:       J1979/ISO 15031-5 Modes 0x01- 0x0F diagnostic handler
 *
 * Global Functions Defined:
 *                    J1979Mode1Handler_DCAN
 *                    J1979Mode2Handler_DCAN
 *                    J1979Mode3Handler_DCAN
 *                    FormJ1979_Mode_43_Data_DCAN
 *                    J1979Mode4Handler_DCAN
 *                    J1979Mode5Handler_DCAN
 *                    J1979Mode6Handler_DCAN
 *                    J1979Mode7Handler_DCAN
 *                    FormJ1979_Mode_47_Data_DCAN
 *                    J1979Mode8Handler_DCAN
 *                    J1979Mode9Handler_DCAN
 *                    FormJ1979_NextMode49_DCAN
 *                    J1979ModeAHandler
 *                    FormJ1979_Mode_4A_Data
 * Static Functions Defined:
 *                    Read_O2Sensor_DCAN
 *                    DtrmnDCAN_M6_Data
 *                    PrfmDCAN_MID_SuppRange
 *                    Is1979Mode8TestIDSupp_DCAN
 *                    Refresh1979_Mode8_SystemLeakTest_DCAN
 *                    DtrmnJ1979_SuppM9Infotypes
 *                    GetDCANService09Info08data
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2003-2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     ctc_pt3#1/csrc/dcanlegi.c/10 %
 * %date_created:  Thu Jun 26 10:56:47 2014 %
 * %version:       10 %
 * %derived_by:    dzrpmq %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
// #include "obdsfexi.h" /*GetVIOS_EngSt_Run()*/
#include "hal_eng.h"
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanlegi.h"
#include "dcanpmid.h"  /*GetDCAN_Param_Value(),GetDCAN_TID_Num(),GetDCAN_MIDNumber()*/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlcdat.h"/*KyDCAN_Mode_09_Info_01_To_08*/
#include "obdlfsrv.h" /* Cy1979_SuppPIDRange_00_20 */
// #include "obdlfpid.h"/*MaskMode_01*/
// #include "obdlfdtc.h"/*Get_Next_Valid_Emission_P_Code*/
// #include "obdlcald.h" /*KbDCANCORE_MODE4_With_EngRUN*/
// #include "ofvcpall.h"/*VbOFVC_DeviceControlActive*/
#include "obdlcdat.h"
#include "kw2srv10m.h"

/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"  /*for PfrmDCAN_AckReqWithoutResponse()*/

/*********************************************************************/
/*            TYPE DEFS                                              */
/*********************************************************************/

/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/
#define  MaskMode_01 0x10
#define  MaskMode_02 0x20
#define  MaskMode_12 0x40
#define  MaskMode_22 0x80

#define  Mode_01 MaskMode_01
#define  Mode_02 MaskMode_02
#define  Mode_12 MaskMode_12 
#define  Mode_22 MaskMode_22 

/*********************************************************************/
/*            GLOBAL CONSTANT VARIABLES                              */
/*********************************************************************/
TbBOOLEAN VbDCAN_NRC78hexInProgress;
TbBOOLEAN VbDCAN_SendNRC78hexResponse;

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
BYTE   VyDCAN_1979_RequestedMID;
#endif

/*********************************************************************/
/*            STATIC DATA DECLARATIONS                               */
/*********************************************************************/
#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)
static TeMode8TestIDStatus             Se1979Mode8TestID_01_Status;
#endif

#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
static BYTE                            Sy1979_Mode09_CalIdx ;
static TbBOOLEAN                       Sb1979_M9_InfoTypeFound;
#endif

/*********************************************************************/
/*            Static FUNCTIONS                                       */
/*********************************************************************/
#if (XeDCAN_SID_05_Supported == CeDCAN_Supported)
INLINE WORD DCAN_LimitFunction(WORD ,WORD ,WORD );
#endif

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
static FOUR_BYTE_DATA_TYPE PrfmDCAN_MID_SuppRange(void);
static void DtrmnDCAN_M6_Data(TWO_BYTE_DATA_TYPE *,
                              TWO_BYTE_DATA_TYPE *,
                              TWO_BYTE_DATA_TYPE *,
                              BYTE,
                              BYTE);
#endif

#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)
static TbBOOLEAN    Is1979Mode8TestIDSupp_DCAN( BYTE ) ;
static void         Refresh1979_Mode8_SystemLeakTest_DCAN( void ) ;
#endif

#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
static BYTE         GetDCANService09Info08data(BYTE); /*Added for SID 09 infotype 08*/
static T_COUNT_BYTE DtrmnJ1979_SuppM9Infotypes(T_COUNT_BYTE,
                                               T_COUNT_BYTE);
#endif

/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/
TbBOOLEAN                       Sb1979_EngCVNSent;
BYTE                            Vy1979_InfoType ;
/*********************************************************************/
/*            GLOBAL FUNCTIONS                                       */
/*********************************************************************/

/*********************************************************************/
/* FUNCTION:     J1979Mode1Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   Request current Powertrain Diagnostic Data          */
/*                                                                   */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_01_Supported == CeDCAN_Supported)

#define J1979_MODE_01_MIN_MSG_LENGTH (2)
#define J1979_MODE_01_MAX_MSG_LENGTH (7)
#define CyMode1_DataOffset           (1)

void J1979Mode1Handler_DCAN (void)
{
   BYTE       Ly1979_MsgIdx ;
   BYTE       LyDCAN_PID_DataIdx ;
   BYTE       Ly1979_DataIdx ;
   BYTE       Ly1979_PIDIdx ;
   TbBOOLEAN  Lb1979_PIDSupported ;
   TbBOOLEAN  Lb1979_SuppPID_Requested ;
   TbBOOLEAN  Lb1979_PIDData_Requested ;
   BYTE       La1979_ServiceData[J1979_MODE_01_MAX_MSG_LENGTH] ;
   BYTE       LyDCAN_1979_RequestedPID;
   TbBOOLEAN  LbValid_PID;

   Ly1979_MsgIdx = 1 ;
   Lb1979_PIDSupported = CbFALSE;
   Lb1979_SuppPID_Requested = CbFALSE;
   Lb1979_PIDData_Requested = CbFALSE;

   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      /* check for message validity */
      /* length should contain at least one PID */
      if (( GetLnServiceDataLength () >= J1979_MODE_01_MIN_MSG_LENGTH )
         && ( GetLnServiceDataLength () <= J1979_MODE_01_MAX_MSG_LENGTH ))
      {
         for(Ly1979_DataIdx = CyMode1_DataOffset;
             Ly1979_DataIdx < GetLnServiceDataLength (); Ly1979_DataIdx++)
         {
             La1979_ServiceData[Ly1979_DataIdx] = (GetLnServiceData ())[Ly1979_DataIdx];
         }

         for(Ly1979_PIDIdx = CyMode1_DataOffset;
             Ly1979_PIDIdx < GetLnServiceDataLength (); Ly1979_PIDIdx++)
         {
            LyDCAN_1979_RequestedPID = La1979_ServiceData[Ly1979_PIDIdx];

            if( (!Lb1979_PIDData_Requested)
              && ( (Cy1979_SuppPIDRange_00_20 == LyDCAN_1979_RequestedPID)
                || (Cy1979_SuppPIDRange_20_40 == LyDCAN_1979_RequestedPID)
                || (Cy1979_SuppPIDRange_40_60 == LyDCAN_1979_RequestedPID)
                || (Cy1979_SuppPIDRange_60_80 == LyDCAN_1979_RequestedPID)
                || (Cy1979_SuppPIDRange_80_A0 == LyDCAN_1979_RequestedPID)
                || (Cy1979_SuppPIDRange_A0_C0 == LyDCAN_1979_RequestedPID)
                || (Cy1979_SuppPIDRange_C0_E0 == LyDCAN_1979_RequestedPID)
                || (Cy1979_SuppPIDRange_E0_FF == LyDCAN_1979_RequestedPID) ) )
            {
                Lb1979_SuppPID_Requested = CbTRUE;
            }
            else if((!Lb1979_SuppPID_Requested)
		             && (Cy1979_SuppPIDRange_00_20 != LyDCAN_1979_RequestedPID)
                      && (Cy1979_SuppPIDRange_20_40 != LyDCAN_1979_RequestedPID)
                      && (Cy1979_SuppPIDRange_40_60 != LyDCAN_1979_RequestedPID)
                      && (Cy1979_SuppPIDRange_60_80 != LyDCAN_1979_RequestedPID)
                      && (Cy1979_SuppPIDRange_80_A0 != LyDCAN_1979_RequestedPID)
                      && (Cy1979_SuppPIDRange_A0_C0 != LyDCAN_1979_RequestedPID)
                      && (Cy1979_SuppPIDRange_C0_E0 != LyDCAN_1979_RequestedPID)
                      && (Cy1979_SuppPIDRange_E0_FF != LyDCAN_1979_RequestedPID) )
            {
                Lb1979_PIDData_Requested = CbTRUE;
            }
            else
            {
                /* Cannot request Suppported PID and PID data in the same message */
                Lb1979_PIDSupported = CbFALSE;
                break;
            }

            /* Test for valid PID and Build Buffer */
			LbValid_PID = Get_Valid_PID_Info((WORD)
               La1979_ServiceData[Ly1979_PIDIdx], MaskMode_01);
            if(CbTRUE == LbValid_PID )
            {
               /* Write request PID Number to Transmit Buffer */
               WrtDCAN_ServiceData( La1979_ServiceData[Ly1979_PIDIdx] ,
                               Ly1979_MsgIdx++ ) ;
               /* Build Transmit buffer 
               LyDCAN_PID_DataIdx =
                   PfrmDCAN_ReqstdPIDData( GetWrtbufferAddr(), Ly1979_MsgIdx ,
                                           GetVeDIAG_PIDIndex() ) ;
               */
               LyDCAN_PID_DataIdx =
                   ProcessReqstdPIDData( GetLnServiceData(), Ly1979_MsgIdx ,
                                           GetVeDIAG_PIDIndex() ) ;

               if(LyDCAN_PID_DataIdx != Ly1979_MsgIdx)
               {
                  Lb1979_PIDSupported = CbTRUE;
                  /* Buffer filled up with PID data, send positive response */
                  Ly1979_MsgIdx = LyDCAN_PID_DataIdx ;
               }
               else
               {
                  /* Buffer not filled with PID data for some reason */
                  Ly1979_MsgIdx--;
               }
            }
         }

         if(Lb1979_PIDSupported)
         {
            /* Send Keyword message buffer */
            SendLnStandardPositiveAnswer ( Ly1979_MsgIdx  );
         }
         else
         {
            /* Do not send any response  */
            PfrmDCAN_AckReqWithoutResponse();
         }
      }
      else
      {
         /* Do not send any response if invalid message received */
         PfrmDCAN_AckReqWithoutResponse ();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse ();
   }
}
#endif

/*********************************************************************/
/* FUNCTION:     KwJ1979Mode2Handler                                 */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This allows access to the data which is captured    */
/*               in the powertrain controller freezeframe            */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_02_Supported == CeDCAN_Supported)
void J1979Mode2Handler_DCAN (void)
{
   BYTE       Ly1979_MsgIdx;
   BYTE       LyDCAN_PID_DataIdx ;
   BYTE       Ly1979_PIDIdx ;
   BYTE       Ly1979_DataIdx ;
   BYTE       Ly1979_RequestedPID ;
   BYTE       Ly1979_RequestedFF ;
   TbBOOLEAN  Lb1979_PIDFound ;
   TbBOOLEAN  Lb1979_SuppPID_Requested ;
   TbBOOLEAN  Lb1979_PIDData_Requested ;
   BYTE       La1979_ServiceData[J1979_MODE_02_MAX_MSG_LENGTH] ;
   TbBOOLEAN  LbValid_PID;

   Ly1979_MsgIdx = 1 ;
   Lb1979_PIDFound = CbFALSE;
   
   Lb1979_SuppPID_Requested = CbFALSE;
   Lb1979_PIDData_Requested = CbFALSE;
   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      /*  Set frame number to zero */
      SetRequestedFrame ( Cy1979FrameReqZero );

      /* check for message validity */
      if (( GetLnServiceDataLength () >= J1979_MODE_02_MIN_MSG_LENGTH )
         && ( GetLnServiceDataLength () <= J1979_MODE_02_MAX_MSG_LENGTH ))
      {
         for(Ly1979_DataIdx = CyMode2_DataOffset;
             Ly1979_DataIdx < GetLnServiceDataLength (); Ly1979_DataIdx++)
         {
             La1979_ServiceData[Ly1979_DataIdx] = (GetLnServiceData ())[Ly1979_DataIdx];
         }
			 
         for(Ly1979_PIDIdx =  CyMode2_DataOffset;
             Ly1979_PIDIdx < GetLnServiceDataLength (); Ly1979_PIDIdx++)
         {
            Ly1979_RequestedPID = La1979_ServiceData[Ly1979_PIDIdx++];
            Ly1979_RequestedFF = La1979_ServiceData[Ly1979_PIDIdx];
            if( (!Lb1979_PIDData_Requested)
              && ( (Cy1979_SuppPIDRange_00_20 == Ly1979_RequestedPID)
                || (Cy1979_SuppPIDRange_20_40 == Ly1979_RequestedPID)
                || (Cy1979_SuppPIDRange_40_60 == Ly1979_RequestedPID)) )
            {
                Lb1979_SuppPID_Requested = CbTRUE;
            }
            else if((!Lb1979_SuppPID_Requested)
		            &&  (Cy1979_SuppPIDRange_00_20 != Ly1979_RequestedPID)
                    && (Cy1979_SuppPIDRange_20_40 != Ly1979_RequestedPID)
                    && (Cy1979_SuppPIDRange_40_60 != Ly1979_RequestedPID))
            {
                Lb1979_PIDData_Requested = CbTRUE;
            }
            else
            {
                /* Cannot request Suppported PID and PID data in the same message */
                //Lb1979_PIDSupported = CbFALSE;
                Lb1979_PIDFound= CbFALSE;
                break;
            }
			
			LbValid_PID = Get_Valid_PID_Info((WORD)Ly1979_RequestedPID, MaskMode_02);
            if((CbTRUE ==LbValid_PID)
                && (Cy1979FrameReqZero == Ly1979_RequestedFF))
            {
               if ((Get_Freeze_Frame_DTC( GetRequestedFrame() ) != 0) ||
                  (Ly1979_RequestedPID <= 0x02) ||
                  (Ly1979_RequestedPID == Cy1979_SuppPIDRange_20_40) ||
                  (Ly1979_RequestedPID == Cy1979_SuppPIDRange_40_60) )
               {
                                 /* response data. */
                  WrtDCAN_ServiceData(Ly1979_RequestedPID,
                                 Ly1979_MsgIdx++) ;

                  WrtDCAN_ServiceData(Cy1979FrameReqZero, Ly1979_MsgIdx++ ) ;
                  /* Build Transmit buffer 
                  LyDCAN_PID_DataIdx =
                    PfrmDCAN_ReqstdPIDData(GetWrtbufferAddr(), Ly1979_MsgIdx,
                                           GetVeDIAG_PIDIndex() ) ;*/
                  LyDCAN_PID_DataIdx =
                    ProcessReqstdPIDData( GetLnServiceData(), Ly1979_MsgIdx,
                                           GetVeDIAG_PIDIndex() ) ;
                  if(LyDCAN_PID_DataIdx != Ly1979_MsgIdx)
                  {
                     Lb1979_PIDFound = CbTRUE;
                     /* Buffer filled up with PID data, send positive response */
                     Ly1979_MsgIdx = LyDCAN_PID_DataIdx ;
                  }
                  else
                  {
                     /* Buffer not filled with PID data for some reason */
                     /* Send negative response                          */
                     Ly1979_MsgIdx = Ly1979_MsgIdx - 2;
                  }
               }
            }
         }
			 
         if(Lb1979_PIDFound)
         {
            SendLnStandardPositiveAnswer ( Ly1979_MsgIdx );
         }
         else
         {
            /* Do not send any response if FF empty */
            PfrmDCAN_AckReqWithoutResponse();
         }
      }
      else
      {
         /* Do not send any response if invalid message received */
         PfrmDCAN_AckReqWithoutResponse();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse();
   }
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode3Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Handles the initial request to transmit emission    */
/*               related fault codes.  The message length must be 4  */
/*               and there must NOT be a mode 3 already in process.  */
/*               fThe flag Vb1979_M3_InProgress is used to determine */
/*               if a previous mode 3 is in process.  If valid faults*/
/*               exist ,then a message is queued and a callback is   */
/*               generated to stuff the codes in the message.        */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: Vb1979_M3_FirstMsg,Vb1979_M3_InProgress,*/
/*                           ViC2GL_CurrentMsg                       */
/*********************************************************************/
#if (XeDCAN_SID_03_Supported == CeDCAN_Supported)
#define CcM3_RETURN_ID_OFFSET      (2)

void J1979Mode3Handler_DCAN (void)
{
   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      /* Test for valid  message length */
      if (( J1979_MODE_03_MSG_LENGTH ) ==
                           GetLnServiceDataLength() )
      {
         FormJ1979_Mode_43_Data_DCAN ();
      }
      else
      {
         /* Do not send a response if request invalid */
         PfrmDCAN_AckReqWithoutResponse();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse();
   }
}
#endif

/*********************************************************************/
/* FUNCTION:     FormJ1979_Mode_43_Data_DCAN                              */
/*                                                                   */
/* Type:         local                                               */
/*                                                                   */
/* DESCRIPTION:  Invoked by Mode_03 handler as well as Queue1979_Next*/
/*               Mode43 procedure, this function finds out and forms */
/*               the data block for the mode 43 response.            */
/*               As long as valid fault codes exist, this procedure  */
/*               will continue to queue new messages.  When no more  */
/*               faults exist, the remaining bytes of the Keyword    */
/*               message are padded with 0s.                         */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       2 if there are more faults                          */
/*               1 if there is 1 or 2 fault                          */
/*               0 if there is no fault                              */
/*                                                                   */
/* Global Variables Updated: Va1979_M43_Data,Vb1979_M3_FirstMsg,     */
/*********************************************************************/
#if (XeDCAN_SID_03_Supported == CeDCAN_Supported)
void FormJ1979_Mode_43_Data_DCAN( void )
{
    WORD          DTCCount ;
    WORD          Lc1979_ValidDTCCount ;
  /* This signifies if at least one DTC was found. */

    WORD                 TrByteCount ;
    DTC_STATUS_INFO_TYPE DTCRecord, *DTCRecordPtr ;
    MODES_TYPE           ModeVal ;

    TrByteCount = CcM3_RETURN_ID_OFFSET ;
    ModeVal     = MODE_3 ;
    Lc1979_ValidDTCCount = V_COUNT_WORD(0);
    DTCCount = V_COUNT_WORD(0);

    // while ( DTCCount < GetCMNMaxNumberOfDTCs () )
    while (0)
    {
       // DTCRecordPtr = Get_Next_Valid_Emission_P_Code ( DTCCount, ModeVal );
       DTCRecordPtr = NULL;
       DTCRecord = *DTCRecordPtr;
       DTCCount++;

       if ( DTCRecord.DTC_Valid )
       {
          Lc1979_ValidDTCCount++;
          DTCRecord.DTC_Valid = CbFALSE;

          WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_One,
                         TrByteCount++);
          WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_Two,
                         TrByteCount++);
       }
    }

    WrtDCAN_ServiceData( Lc1979_ValidDTCCount, CyM3_M7_NumDTC_Offset);

    SendLnStandardPositiveAnswer (TrByteCount);
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode4Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Mode 4 message is a request to clear/reset all      */
/*               diagnostic information.  This request initializes   */
/*               both emission and non-emission related powertrain   */
/*               diagnostics which must include all transmission,    */
/*               engine, etc. diagnostics.  The list of variables and*/
/*               corresponding initialization values is extensive.   */
/*               Along with clearing DTC's, freeze frame and failure */
/*               records Fault ID's must be cleared, diagnostic      */
/*               timers and counters initialized, etc.  Some variable*/
/*               initialization is conditional on whether a DTC is   */
/*               stored.  A typical application will likely be       */
/*               required to initialize humdreds of variables.       */
/*               "initialization" in general does not mean "clear".  */
/*               The PCM response to this request contains only an   */
/*               acknowledgement that the request has been granted   */
/*               or is in the process of being granted.  The PCM will*/
/*               always respond to this request affirmatively after  */
/*               it has received it.  The PCM does not need to wait  */
/*               until the actual initialization process is complete */
/*               to respond.  The PCM requirement the initialization */
/*               shall be complete no later than 1 second after the  */
/*               44 response.  At a minimum, the ignition must be ON */
/*               to guarantee a complete execution of this request.  */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_04_Supported == CeDCAN_Supported)
/* no callback need to be set for mode 44 transmit*/
#define CcM4_RETURN_ID_OFFSET     (1)

void J1979Mode4Handler_DCAN (void)
{
   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      if ( ( GetLnServiceDataLength() ==
                    ( J1979_MODE_04_MSG_LENGTH ) )
        && ( GetVIOS_EngSt_Run() ))
        // && ( ! KbDCANCORE_MODE4_With_EngRUN ) )
      {
         SendLnStandardNegativeAnswer(
                       CcDCAN_CondNotCorrect_RequestSequenceError);
      }
      else if (GetLnServiceDataLength() ==
                    ( J1979_MODE_04_MSG_LENGTH ))
      {
         /* It is not required to reply after clearing the DTC's.
          * The DTC's should be cleared within 1 second of sending
          * the response.
         */
         SendLnStandardPositiveAnswer ( CcM4_RETURN_ID_OFFSET );
         /* imported from CMNDTC module */
         ClearDiagnosticData ();
      }
      else
      {
          /* Do not send a response if request invalid */
          PfrmDCAN_AckReqWithoutResponse();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse();
   }
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode5Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This mode is to obtain the results of O2 Sensor     */
/*               Monitoring Tests with in the PCM .                  */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_05_Supported == CeDCAN_Supported)

void J1979Mode5Handler_DCAN (void)
{
   TsC2AP_O2Sensor Ls1979_T_Code;

   BYTE    Ly1979_TestID;
   BYTE    Ly1979_O2ID;

   BYTE    Ly1979_MsgIdx;

   Ly1979_MsgIdx  = J1979_ActualDataLoc ;

   Ly1979_TestID  = (GetLnServiceData ())[CyTestIDMode5];
   Ly1979_O2ID    = (GetLnServiceData ())[Cy02IDMode5];

   /*Check if it is in standard diagnostic mode to support service*/
   if(!CheckStandardDiagnosticState())
   {
      SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
   }
   else
   {
      if ( J1979_MODE_05_MSG_LENGTH == GetLnServiceDataLength())
      {

         WrtDCAN_ServiceData( Ly1979_TestID , Ly1979_MsgIdx++) ;
         WrtDCAN_ServiceData( Ly1979_O2ID   , Ly1979_MsgIdx++) ;

         Ls1979_T_Code = Read_O2Sensor(Ly1979_TestID , Ly1979_O2ID );

         if ( Ls1979_T_Code.LyTestIdFlag )
         {
            if ( OneByteO2Snsr == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;

               SendLnStandardPositiveAnswer ( Ly1979_MsgIdx );

            }
            else if ( ThreeByteO2Snsr == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;

               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Two ,
                               Ly1979_MsgIdx++ ) ;

               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Three ,
                               Ly1979_MsgIdx++ ) ;

               SendLnStandardPositiveAnswer ( Ly1979_MsgIdx );
            }
            /* Reading and queueing the Cal constant value           */
            else if(FourByteCalConst == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Two ,
                               Ly1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Three ,
                               Ly1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Four ,
                               Ly1979_MsgIdx++ ) ;

               SendLnStandardPositiveAnswer ( Ly1979_MsgIdx );
            }
         }
         else
         {
            /* Send negative responce if PID not supported */
            SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
         }
      }
      else
      {
         /* Send negative responce if PID not supported */
         SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
      }
   }
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode6Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This mode is to obtain the results of On board      */
/*               Diagnostic tests by Test ID.                        */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
void J1979Mode6Handler_DCAN (void)
{
   BYTE                LyDCAN_DataIdx ;
   BYTE                LyDCAN_DataIdx_Old ;
   TbBOOLEAN           LbDCAN_MID_Found;
   TbBOOLEAN           LbDCAN_SendResponse;
   TbBOOLEAN           LbDCAN_SuppMID_Requested;
   TbBOOLEAN           LbDCAN_MIDData_Requested;
   BYTE                LyDCAN_MID_Index;
   BYTE                LyDCAN_TID_Index;
   TWO_BYTE_DATA_TYPE  LuDCAN_TestValue;
   FOUR_BYTE_DATA_TYPE LuDCAN_Supp_Range ;
   TWO_BYTE_DATA_TYPE  LuDCAN_Min_Thrsh;
   TWO_BYTE_DATA_TYPE  LuDCAN_Max_Thrsh;
   BYTE                LyDCAN_MsgIdx ;
   BYTE                LaDCAN_ServiceData[CcDCAN_MODE6_MAX_MSG_LENGTH] ;

   LbDCAN_MID_Found         = CbFALSE;
   LbDCAN_SendResponse      = CbFALSE;
   LyDCAN_MID_Index         = 0;
   LyDCAN_MsgIdx            = CcDCAN_MODE6_DataOffset;
   LbDCAN_SuppMID_Requested = CbFALSE;
   LbDCAN_MIDData_Requested = CbFALSE;

   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      /* check for message validity */
      /* length should contain at least one MID */
      if (( GetLnServiceDataLength () >= CcDCAN_MODE6_MIN_MSG_LENGTH )
         && ( GetLnServiceDataLength () <= CcDCAN_MODE6_MAX_MSG_LENGTH ))
      {
         for(LyDCAN_DataIdx = CcDCAN_MODE6_DataOffset;
             LyDCAN_DataIdx < GetLnServiceDataLength (); LyDCAN_DataIdx++)
         {
            LaDCAN_ServiceData[LyDCAN_DataIdx] = (GetLnServiceData ())[LyDCAN_DataIdx];
         }

         for(LyDCAN_DataIdx = CcDCAN_MODE6_DataOffset;
             LyDCAN_DataIdx < GetLnServiceDataLength (); LyDCAN_DataIdx++)
         {
            VyDCAN_1979_RequestedMID = LaDCAN_ServiceData[LyDCAN_DataIdx];
            /* The do-while loop below is repeatedly executed until either find */
            /* matching MID Index or get to last index.                         */

            /* Write request MID Number to Transmit Buffer */
            WrtDCAN_ServiceData( VyDCAN_1979_RequestedMID ,
                                  LyDCAN_MsgIdx++ ) ;

            LyDCAN_DataIdx_Old = LyDCAN_MsgIdx;

            if( (!LbDCAN_MIDData_Requested)
              && ( (CeDCAN_MID_00 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_20 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_40 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_60 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_80 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_A0 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_C0 == VyDCAN_1979_RequestedMID)
                || (CeDCAN_MID_E0 == VyDCAN_1979_RequestedMID) ) )
            {
               LbDCAN_SuppMID_Requested = CbTRUE;
               LuDCAN_Supp_Range = PrfmDCAN_MID_SuppRange();
               if(LuDCAN_Supp_Range.DWord_Access != V_COUNT_LONG(0))
               {
                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_One ,
                                        LyDCAN_MsgIdx++ ) ;

                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_Two ,
                                        LyDCAN_MsgIdx++ ) ;

                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_Three ,
                                        LyDCAN_MsgIdx++ ) ;

                  WrtDCAN_ServiceData( LuDCAN_Supp_Range.Byte_Access.Byte_Four ,
                                        LyDCAN_MsgIdx++ ) ;
               }
            }
            else if( (!LbDCAN_SuppMID_Requested)
                    && (GetLnServiceDataLength () == CcDCAN_MODE6_MIN_MSG_LENGTH) )
            {
               do
               {
                  if (  GetDCAN_MIDNumber( LyDCAN_MID_Index ) ==
                        VyDCAN_1979_RequestedMID )
                  {
                     LbDCAN_MID_Found = CbTRUE;
                     break ;
                  }
                  LyDCAN_MID_Index++ ;
               }  while ( LyDCAN_MID_Index <= GetDCAN_NumberOfMIDs() );

               if(LbDCAN_MID_Found)
               {
                  LyDCAN_TID_Index    = 0;

                  while(LyDCAN_TID_Index < GetDCAN_Num_Of_TIDs(LyDCAN_MID_Index))
                  {
                     WrtDCAN_ServiceData( GetDCAN_TID_Num(LyDCAN_MID_Index, LyDCAN_TID_Index),
                               LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( GetDCAN_TID_ScalingID(LyDCAN_MID_Index, LyDCAN_TID_Index),
                               LyDCAN_MsgIdx++ ) ;

                     DtrmnDCAN_M6_Data(&LuDCAN_TestValue,
                                       &LuDCAN_Min_Thrsh,
                                       &LuDCAN_Max_Thrsh,
                                       LyDCAN_MID_Index,
                                       LyDCAN_TID_Index);

                     WrtDCAN_ServiceData( LuDCAN_TestValue.Byte_Access.Byte_One ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_TestValue.Byte_Access.Byte_Two ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Min_Thrsh.Byte_Access.Byte_One ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Min_Thrsh.Byte_Access.Byte_Two ,
                                    LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Max_Thrsh.Byte_Access.Byte_One ,
                                  LyDCAN_MsgIdx++ ) ;

                     WrtDCAN_ServiceData( LuDCAN_Max_Thrsh.Byte_Access.Byte_Two ,
                                LyDCAN_MsgIdx++ ) ;

                     LyDCAN_TID_Index++;

                     if(LyDCAN_TID_Index < GetDCAN_Num_Of_TIDs(LyDCAN_MID_Index))
                     {
                        /* Write request MID Number to Transmit Buffer */
                        WrtDCAN_ServiceData( VyDCAN_1979_RequestedMID ,
                                              LyDCAN_MsgIdx++ ) ;
                     }
                  } /*End of while */
               } /* if(LbDCAN_MID_Found) */
               else
               {
                  /* Do nothing */
               }
            }
            else
            {
               /* Do not suppport MID supported and MID data in the same message */
               LbDCAN_SendResponse = CbFALSE;
               break;
            }

            if(LyDCAN_DataIdx_Old != LyDCAN_MsgIdx)
            {
               LbDCAN_SendResponse = CbTRUE;
            }
            else
            {
               /* Buffer not filled with MID data for some reason */
               LyDCAN_MsgIdx--;
            }
         } /* End of For loop */

         if(LbDCAN_SendResponse)
         {
            SendLnStandardPositiveAnswer ( LyDCAN_MsgIdx  );
         }
         else
         {
            /* Do not send any response if invalid message received */
            PfrmDCAN_AckReqWithoutResponse ();
         }
      }
      else
      {
         /* Do not send any response if invalid message received */
         PfrmDCAN_AckReqWithoutResponse ();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse ();
   }
}

/*********************************************************************/
/* FUNCTION:    DtrmnDCAN_M6_Data()                                  */
/*                                                                   */
/* Type:        static                                               */
/*                                                                   */
/* DESCRIPTION: Builds the bit encoded value of supported MIDs       */
/*                                                                   */
/* PARAMETERS:  TWO_BYTE_DATA_TYPE                                   */
/*              TWO_BYTE_DATA_TYPE                                   */
/*              TWO_BYTE_DATA_TYPE                                   */
/*              BYTE                                                 */
/*              BYTE                                                 */
/*                                                                   */
/* RETURN:      NONE                                                 */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
static void DtrmnDCAN_M6_Data(TWO_BYTE_DATA_TYPE *LpDCAN_Test_Value,
                              TWO_BYTE_DATA_TYPE *LpDCAN_Min_Thrsh,
                              TWO_BYTE_DATA_TYPE *LpDCAN_Max_Thrsh,
                              BYTE               LyDCAN_MID_Index,
                              BYTE               LyDCAN_TID_Index)
{
   TbBOOLEAN LbDCAN_TestReportingEnabled = CbFALSE;
   TeDGDM_DIAGNOSTIC_TESTS    LeDCAN_DTC_ID;

   LeDCAN_DTC_ID = GetDCAN_DTC_ID(LyDCAN_MID_Index,LyDCAN_TID_Index);

   if ( CeDGDM_Misfire == LeDCAN_DTC_ID )
   {
      if ( DtrmnMISF_CAN_TestReportingEnabled() )
      {
         LbDCAN_TestReportingEnabled = CbTRUE;
      }
   }
   else if ( ( CeDGDM_NoFault == LeDCAN_DTC_ID )
          || ( ( CeDGDM_FAULT_TYPE_Z != GetDGDM_DTC_FaultType(LeDCAN_DTC_ID) )
            && ( GetDGDM_TestCompletedSnceCdClr(LeDCAN_DTC_ID) ) ) )
   {
     LbDCAN_TestReportingEnabled = CbTRUE;
   }

   if ( LbDCAN_TestReportingEnabled )
   {
      GetDCAN_Param_Value(LyDCAN_MID_Index, LyDCAN_TID_Index,
                          &LpDCAN_Test_Value->Word_Access);
      GetDCAN_Param_Min_Value(LyDCAN_MID_Index, LyDCAN_TID_Index,
                          &LpDCAN_Min_Thrsh->Word_Access);
      GetDCAN_Param_Max_Value(LyDCAN_MID_Index, LyDCAN_TID_Index,
                          &LpDCAN_Max_Thrsh->Word_Access);
   }
   else
   {
      LpDCAN_Test_Value->Word_Access = V_COUNT_WORD(0);
      LpDCAN_Min_Thrsh->Word_Access = V_COUNT_WORD(0);
      LpDCAN_Max_Thrsh->Word_Access = V_COUNT_WORD(0);
   }
}

/*********************************************************************/
/* FUNCTION:    PrfmDCAN_MID_SuppRange()                             */
/*                                                                   */
/* Type:        static                                               */
/*                                                                   */
/* DESCRIPTION: Builds the bit encoded value of supported MIDs       */
/*                                                                   */
/* PARAMETERS:  TeDCAN_TID_List                                      */
/*                                                                   */
/* RETURN:      TsDCAN_SID06_MID                                     */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
static FOUR_BYTE_DATA_TYPE PrfmDCAN_MID_SuppRange(void)
{
   FOUR_BYTE_DATA_TYPE LuDCAN_TestValue ;
   T_COUNT_BYTE        LyDCAN_MID_NumBitsToShift ;
   T_COUNT_BYTE        LyDCAN_MID_RangeToCheck ;
   T_COUNT_BYTE        LyDCAN_MID_TableIdx;

   LuDCAN_TestValue.DWord_Access = V_COUNT_LONG(0);
   LyDCAN_MID_NumBitsToShift = V_COUNT_BYTE(0);
   LyDCAN_MID_RangeToCheck = V_COUNT_BYTE(0);

   if(CeDCAN_MID_00 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_20;
   }
   else if(CeDCAN_MID_20 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_40;
   }
   else if(CeDCAN_MID_40 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_60;
   }
   else if(CeDCAN_MID_60 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_80;
   }
   else if(CeDCAN_MID_80 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_A0;
   }
   else if(CeDCAN_MID_A0 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_C0;
   }
   else if(CeDCAN_MID_C0 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_E0;
   }
   else if(CeDCAN_MID_E0 == GetDCAN_1979_RequestedMID())
   {
      LyDCAN_MID_RangeToCheck = CeDCAN_MID_FF;
   }
   else
   {
      /* Do nothing */
   }
   for(LyDCAN_MID_TableIdx = 0;LyDCAN_MID_TableIdx < CyDCAN_NumOf_MIDs;
       LyDCAN_MID_TableIdx++)
   {
      if((CaDCAN_Supported_MIDs[LyDCAN_MID_TableIdx].f_MID_Number > GetDCAN_1979_RequestedMID())
        && (CaDCAN_Supported_MIDs[LyDCAN_MID_TableIdx].f_MID_Number <= LyDCAN_MID_RangeToCheck))
      {
         LyDCAN_MID_NumBitsToShift =
            usSUB_us_usp((usSUB_us_usp(CaDCAN_Supported_MIDs[LyDCAN_MID_TableIdx].f_MID_Number,
                                       GetDCAN_1979_RequestedMID(),
                                       S_COUNT_BYTE,
                                       S_COUNT_BYTE,
                                       S_COUNT_BYTE)),
                          V_COUNT_BYTE(1),
                          S_COUNT_BYTE,
                          S_COUNT_BYTE,
                          S_COUNT_BYTE);

         LuDCAN_TestValue.DWord_Access |=
                 (CcDCAN_1979_SuppMID_BitMask >> LyDCAN_MID_NumBitsToShift);
      }
   }
   return(LuDCAN_TestValue);
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode7Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Handles the initial request to transmit emission    */
/*               related fault codes.  The message length must be 4  */
/*               and there must NOT be a mode 7 already in process.  */
/*               If valid faults exist ,then a message is queued and */
/*               a callback is generated to stuff the codes in the   */
/*               message.                                            */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
/* mode 47 transmit callback is set                                  */
#if (XeDCAN_SID_07_Supported == CeDCAN_Supported)
#define J1979_Mode_47_DTC_Length   (7)
#define CcM7_RETURN_ID_OFFSET      (2)

void J1979Mode7Handler_DCAN (void)
{
   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      if ( J1979_MODE_07_MSG_LENGTH == GetLnServiceDataLength() )
      {
         FormJ1979_Mode_47_Data_DCAN ();
      }
      else
      {
          /* Do not send a response if request invalid */
          PfrmDCAN_AckReqWithoutResponse();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse();
   }
}

/*********************************************************************/
/* FUNCTION:     Form1979_Mode_47_Data                               */
/*                                                                   */
/* Type:         local                                               */
/*                                                                   */
/* DESCRIPTION:  Invoked by Mode_07 handler as well as Queue1979_Next*/
/*               Mode47 procedure, this function finds out and forms */
/*               the data block for the mode 47 response.            */
/*               As long as valid fault codes exist, this procedure  */
/*               will continue to queue new messages.  When no more  */
/*               faults exist, the remaining bytes of the Class 2    */
/*               message are padded with 0s.                         */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       2 if there are more faults                          */
/*               1 if there is 1 or 2 fault                          */
/*               0 if there is no fault                              */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
void FormJ1979_Mode_47_Data_DCAN( void )
{
    WORD          DTCCount ;
    BYTE          TrByteCount ;
    T_COUNT_WORD  Lc1979_ValidDTCCount ;


    DTC_STATUS_INFO_TYPE DTCRecord, *DTCRecordPtr ;

    MODES_TYPE  ModeVal ;

    TrByteCount = CcM7_RETURN_ID_OFFSET ;
    Lc1979_ValidDTCCount = V_COUNT_WORD(0);
    DTCCount = V_COUNT_WORD(0);

    ModeVal = MODE_7 ;

    // while ( DTCCount < GetCMNMaxNumberOfDTCs () )
    while(0)
    {
        // DTCRecordPtr = Get_Next_Valid_Emission_P_Code ( DTCCount, ModeVal ) ;
        DTCRecordPtr = NULL;
        DTCRecord = *DTCRecordPtr ;
        DTCCount++ ;

        if ( DTCRecord.DTC_Valid )
        {
           Lc1979_ValidDTCCount++;
           DTCRecord.DTC_Valid = CbFALSE ;
           WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_One,
                                                     TrByteCount++) ;
           WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_Two,
                                                     TrByteCount++) ;
        }
    }

    WrtDCAN_ServiceData( Lc1979_ValidDTCCount, CyM3_M7_NumDTC_Offset);

    SendLnStandardPositiveAnswer (TrByteCount) ;
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979Mode8Handler_DCAN                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION   This mode is to request the mode 08 Test ID's       */
/*               which are supported                                 */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)

void J1979Mode8Handler_DCAN( void )
{
   BYTE    Li1979_MsgIdx;
   BYTE    Li1979_CalIdx;
   BYTE    LyFlag;
   BYTE    Ly1979_TestRange_TestID ;

   /*Check if it is in standard diagnostic mode to support service*/
   if(!CheckStandardDiagnosticState())
   {
      SendLnStandardNegativeAnswer(
                            CcDCAN_SubFuncNotSupp_InvalidFormat );
   }
   else
   {
      Refresh1979_Mode8_SystemLeakTest_DCAN( );

      /* Do message verification and validation */
      if ( Ky1979_MODE_08_MSG_LENGTH  ==
                              GetLnServiceDataLength())
      {
         Ly1979_TestRange_TestID = (GetLnServiceData ())[CyTestID_OR_Range];
         Li1979_MsgIdx = 1 ;
         LyFlag = CbFALSE;

         WrtDCAN_ServiceData( Ly1979_TestRange_TestID , Li1979_MsgIdx++ ) ;

         if(( CyMode8Test_01 == Ly1979_TestRange_TestID )  &&
              Is1979Mode8TestIDSupp_DCAN( Ly1979_TestRange_TestID ))
         {
            /* Engine is not running                                   */
            if ( ( !Get_EngineTurning())
                 &&  !GetEVPD_TankProtectionMode() )
 /*              &&  ( GetEVPD_TankProtectionMode() == CbFALSE ) ) */
            {
               VbOFVC_DeviceControlActive = 1;
               Se1979Mode8TestID_01_Status = CeMode8TestIDEnabled;
               SetOFVC_DiagEvapVentVlvOvrd (CeFORCE_CLOSED);
               SetOFVC_CCP_SD_OvrdValue (V_PERCENTa(0));

               /* No reject reason */
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               /* Pad the message with Zeros                         */
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;

               LyFlag = CbTRUE; /* Message can be queued            */
            }
            else
            {
               Se1979Mode8TestID_01_Status = CeMode8TestIDEnabled;
               if(Get_EngineTurning())
               {
                  WrtDCAN_ServiceData( 0x2 , Li1979_MsgIdx++ ) ;
               }
               else if (GetEVPD_TankProtectionMode())
               {
                  WrtDCAN_ServiceData( 0x1 , Li1979_MsgIdx++ ) ;
               }
               else
               {
                  /* Send postive respond */
                  WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               }
               /* Pad the message with Zeros            */
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               WrtDCAN_ServiceData( 0x00 , Li1979_MsgIdx++ ) ;
               SendLnStandardPositiveAnswer( Li1979_MsgIdx );
            }
         }
         /* If TestRange is Zero  */
         else if ( Cy1979_Mode_08_TestRange_0 == Ly1979_TestRange_TestID)
         {
            WrtDCAN_ServiceData( 0 , Li1979_MsgIdx++ ) ;
            for (Li1979_CalIdx = Cy1979_InitVal;
               Li1979_CalIdx < Cy1979_Mode_08_IndexLim;
               Li1979_CalIdx++)
            {
             /* Calibration Constant containing the TestID supported */
              WrtDCAN_ServiceData(  Ka1979_M8_TID_Supported[Li1979_CalIdx] ,
                                                     Li1979_MsgIdx++ ) ;

             /* Check for data has been calculated for a valid supported */
             /* Test Range.If no test range is supported,send a negative */
             /* response. */
              if (Cy1979_InitVal !=
                                Ka1979_M8_TID_Supported[Li1979_CalIdx])
              {
                 LyFlag = CbTRUE;
              }
            }
            if(!LyFlag)
            {
              SendLnStandardNegativeAnswer(
                              CcDCAN_SubFuncNotSupp_InvalidFormat);
            }
         }
         else
         {
            SendLnStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
         }

         if(CbTRUE == LyFlag)
         {
            SendLnStandardPositiveAnswer( Li1979_MsgIdx );
         }
      }
      else
      {
         /* Send negative responce if Test ID not supported */
         SendLnStandardNegativeAnswer(
                              CcDCAN_SubFuncNotSupp_InvalidFormat);
      }
   }
   SendLnStandardNegativeAnswer( CcDCAN_ServiceNotSupported ) ;
}

/*********************************************************************/
/* FUNCTION:     Is1979Mode8TestIDSupp_DCAN                               */
/*                                                                   */
/* Type:         Static                                              */
/*                                                                   */
/* DESCRIPTION:  This function returns True of False depending on the*/
/*               support or non-support of the test Id's for Mode 8  */
/*                                                                   */
/* PARAMETERS:   Test ID                                             */
/*                                                                   */
/* RETURN:       TbBOOLEAN                                           */
/*                                                                   */
/* Global Variables Updated:None                                     */
/*********************************************************************/
static TbBOOLEAN Is1979Mode8TestIDSupp_DCAN(BYTE LyTestID)
{
   TbBOOLEAN LyFlag;
   BYTE      LyTempBuff;

   LyFlag = CbFALSE;
   if(CyMode8Test_01 == LyTestID)
   {
      LyTempBuff =  Ka1979_M8_TID_Supported[0];

      /* Evaporative system leak test supported ( TestID 0x01 )     */
      if(LyTempBuff & CySetBit7)
      {
         LyFlag = CbTRUE;
      }
   }
   return LyFlag;
}

/*********************************************************************/
/* FUNCTION:     fresh1979_Mode8_SystemLeakTest                      */
/*                                                                   */
/* Type:         Global                                              */
/*                                                                   */
/* DESCRIPTION:  Refresh function for the Evaporative system leak    */
/*               test. Called in the kw2 executive                   */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: ViC2GL_CurrentMsg, Va1979_M49_Data      */
/*********************************************************************/
static void Refresh1979_Mode8_SystemLeakTest_DCAN( void )
{
   /* Engine is  running                                             */
   if((Get_EngineTurning())
       && (CeMode8TestIDEnabled == Se1979Mode8TestID_01_Status))
   {
      Se1979Mode8TestID_01_Status = CeMode8TestIDDisabled;
   }
}
#endif

/*********************************************************************/
/* FUNCTION:     1979_Mode_09_Request                                */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  This function analyzes the incoming info type and   */
/*               sends the vehicle specific information such as      */
/*               vehicle identification number,calibration ids and   */
/*               calibration verification numbers.This request may   */
/*               have one or more 49 responses.                      */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: ViC2GL_CurrentMsg, Va1979_M49_Data      */
/*********************************************************************/
#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
#define J1979_MODE_09_INFO_LENGTH      (2)
#define J1979_MODE_09_SUPP_INFO_LENGTH (7)
#define CyInfoType                     (1)
#define KW_CRC_Step_Lenth              (100)


void J1979Mode9Handler_DCAN( void )
{
   T_COUNT_BYTE Ly1979_DataIdx;
   T_COUNT_BYTE Ly1979_BuffIdx ;
   T_COUNT_BYTE Ly1979_InfoTypeIdx;
   T_COUNT_BYTE Ly1979_Index;
   TbBOOLEAN    Lb1979_Found;
   TbBOOLEAN    Lb1979_MultiMode;
   BYTE         La1979_ServiceData[J1979_MODE_09_SUPP_INFO_LENGTH] ;
   const BYTE* KyDCAN_EcuName;

   Sy1979_Mode09_CalIdx = 0;
   Sb1979_EngCVNSent = CbFALSE;
   Ly1979_DataIdx = CyInfoType ;
   Lb1979_Found  = CbFALSE;
   Sb1979_M9_InfoTypeFound = CbFALSE;
   Lb1979_MultiMode = CbFALSE;

   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      if(GetLnServiceDataLength() > J1979_MODE_09_SUPP_INFO_LENGTH)
      {
         PfrmDCAN_AckReqWithoutResponse();
      }
      else
      {
         for(Ly1979_BuffIdx = CyInfoType;
             Ly1979_BuffIdx < GetLnServiceDataLength (); Ly1979_BuffIdx++)
         {
            La1979_ServiceData[Ly1979_BuffIdx] = (GetLnServiceData ())[Ly1979_BuffIdx];
         }

         if (( GetLnServiceDataLength() == J1979_MODE_09_INFO_LENGTH )
            && (    (La1979_ServiceData[CyInfoType] != Cy1979_InfoType0)
                 && (La1979_ServiceData[CyInfoType] != Cy1979_InfoType20)
                 && (La1979_ServiceData[CyInfoType] != Cy1979_InfoType40)
                 && (La1979_ServiceData[CyInfoType] != Cy1979_InfoType60)
                 && (La1979_ServiceData[CyInfoType] != Cy1979_InfoType80)
                 && (La1979_ServiceData[CyInfoType] != Cy1979_InfoTypeA0)
                 && (La1979_ServiceData[CyInfoType] != Cy1979_InfoTypeC0)
                 && (La1979_ServiceData[CyInfoType] != Cy1979_InfoTypeE0)
               )
            )
         {
            Vy1979_InfoType =  La1979_ServiceData[CyInfoType];

            WrtDCAN_ServiceData( Vy1979_InfoType , Ly1979_DataIdx++ );

            Lb1979_Found = CbTRUE ;

            switch(Vy1979_InfoType)
            {
               case Cy1979_InfoType1:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (KyDCAN_Mode_09_Info_01_To_08,
                                    Cy1979_InfoType_01_BitPosVal) )
                  {
                     WrtDCAN_ServiceData( Cy1979_NumOfMsgsToRptVIN_DCAN , Ly1979_DataIdx++ );
                  }
                  else
                     Lb1979_Found = CbFALSE ;
                  break;

               case Cy1979_InfoType2:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                     (KyDCAN_Mode_09_Info_01_To_08,
                                    Cy1979_InfoType_02_BitPosVal) )
                  {
                     WrtDCAN_ServiceData(Cy1979_Info_02_NumDataItems, Ly1979_DataIdx++);

                     /* Read VIN from Flash ROM */
                    // ReadFILE_EE_FLASH_VIN(VinFirst);

                     for(Ly1979_Index = 0;Ly1979_Index < VIN_Size;Ly1979_Index++)
                     {
                        WrtDCAN_ServiceData( GetVinDataByte( Ly1979_Index ),
                                           Ly1979_DataIdx++);
                     }
                  }
                  else
                     Lb1979_Found = CbFALSE ;
                  break;

               case Cy1979_InfoType3:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (KyDCAN_Mode_09_Info_01_To_08,
                                    Cy1979_InfoType_03_BitPosVal) )
                  {
                     WrtDCAN_ServiceData(Cy1979_NumOfMsgsToRptCalID_DCAN,
                                       Ly1979_DataIdx++);
                  }
                  else
                     Lb1979_Found = CbFALSE ;
                  break;

               case Cy1979_InfoType4:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (KyDCAN_Mode_09_Info_01_To_08,
                                    Cy1979_InfoType_04_BitPosVal) )
                  {
                     WrtDCAN_ServiceData
                               ((Cy1979_Info_04_NumDataItems * Cy1979_MaxCalIDs),
                                Ly1979_DataIdx++);

                     for (Ly1979_Index = 0; Ly1979_Index < CcFILE_CAL_ID_SIZE;
                          Ly1979_Index++)
                     {
                        if (Ly1979_Index<Cy1979_EngCalIDSize)
                        { 
                           // WrtDCAN_ServiceData( KySYST_BTC_NR[Ly1979_Index],
                           //                             Ly1979_DataIdx++);
                        }
                        else
                        {
                           WrtDCAN_ServiceData( 0x00, Ly1979_DataIdx++); 
                        }
                     }
                  }
                  else
                  {
                     Lb1979_Found = CbFALSE ;
                  }
                  break;

               case Cy1979_InfoType5:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (KyDCAN_Mode_09_Info_01_To_08,
                                    Cy1979_InfoType_05_BitPosVal) )
                  {
                     WrtDCAN_ServiceData((Cy1979_NumOfMsgsToRptCVNs),
                                        Ly1979_DataIdx++) ;
                  }
                  else
                     Lb1979_Found = CbFALSE ;
                  break;

               case Cy1979_InfoType6:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                         (KyDCAN_Mode_09_Info_01_To_08,
                                          Cy1979_InfoType_06_BitPosVal) )
                  {
                      /* Send back a negative response indicating
                         that the function is not complete. */
                 #if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
                     (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
                      if(GetTRVC_TransCntrlIsPCM())
                      {
                          if(!GetFILE_CVN_Available()
                             || !GetFILE_CVN_Available_TRN())
                          {
                              SendLnStandardNegativeAnswer(
                                 CcDCAN_ReqCorrectlyRecvd_ResponsePending);
                          }
                      }
                      else
                  #endif
                      {
                          if(!GetFILE_CVN_Available())
                          {
                              SendLnStandardNegativeAnswer(
                                    CcDCAN_ReqCorrectlyRecvd_ResponsePending);
                          }
                      }

                      Lb1979_MultiMode = CbTRUE ;
                  }
                  else
                  {
                      Lb1979_Found = CbFALSE ;
                  }
                  break;

               case Cy1979_InfoType7:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (KyDCAN_Mode_09_Info_01_To_08,
                                    Cy1979_InfoType_07_BitPosVal) )
                  {
                     WrtDCAN_ServiceData( Cy1979_MessageCountIPT_DCAN,
                                        Ly1979_DataIdx++) ;
                  }
                  else
                     Lb1979_Found = CbFALSE ;
                  break;

               case Cy1979_InfoType8:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (KyDCAN_Mode_09_Info_01_To_08,
                                    Cy1979_InfoType_08_BitPosVal) )
                  {
                     WrtDCAN_ServiceData( Cy1979_Info_08_NumDataItems,
                                        Ly1979_DataIdx++) ;

                       /* OBD Monitoring Conditions Count */
                     Ly1979_DataIdx =
                        GetDCANService09Info08data(Ly1979_DataIdx);
                  }
                  else
                  {
                     Lb1979_Found = CbFALSE ;
                  }
                  break;
				  
               case Cy1979_InfoType0A:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (Ky1979_Mode_09_Info_09_To_16,
                                    Cy1979_InfoType_0A_BitPosVal) )
                  {
                     WrtDCAN_ServiceData( Cy1979_Info_0A_NumDataItems,
                                        Ly1979_DataIdx++) ;

                     if( GetTRVC_TransCntrlIsManual()
                         || GetTRVC_TransCntrlIsTCM())
                     {
                       KyDCAN_EcuName = KyDCAN_ECM_EcuName;
                     }
                     else
                     {
                       KyDCAN_EcuName = KyDCAN_PCM_EcuName;
                     }
                     for (Ly1979_Index = 0; Ly1979_Index < ECU_NAME_Size;
                          Ly1979_Index++)
                     {
                        WrtDCAN_ServiceData( KyDCAN_EcuName[Ly1979_Index],
                                                       Ly1979_DataIdx++);
                     }
                  }
                  else
                  {
                     Lb1979_Found = CbFALSE ;
                  }
                  break;

               default:
                  /* Send negative responce if PID not supported */
                  Lb1979_Found = CbFALSE ;
                  break;
            }
            if(( Lb1979_MultiMode )
              && ( Lb1979_Found ))
            {
               WrtDCANMultiRespInProgress( CbTRUE ) ;
            }
            else if ( Lb1979_Found )
            {
               SendLnStandardPositiveAnswer( Ly1979_DataIdx );
            }
            else
            {
               /* No response if the infotype is not supported */
               PfrmDCAN_AckReqWithoutResponse();
            }
         }
         else
         {
            for(Ly1979_InfoTypeIdx = CyInfoType;Ly1979_InfoTypeIdx < GetLnServiceDataLength();
                Ly1979_InfoTypeIdx++)
            {
               Ly1979_DataIdx =
                     DtrmnJ1979_SuppM9Infotypes(La1979_ServiceData[Ly1979_InfoTypeIdx],
                                                   Ly1979_DataIdx);
            }

            if(Sb1979_M9_InfoTypeFound)
            {
               SendLnStandardPositiveAnswer( Ly1979_DataIdx );
            }
            else
            {
               /* No response if the infotype is not supported */
               PfrmDCAN_AckReqWithoutResponse();
            }
         }
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse();
   }
}

/*********************************************************************/
/* FUNCTION:     DtrmnJ1979_SuppM9Infotypes                          */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Returns all the supported infotypes for Mode 09     */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: Va1979_M49_Data                         */
/*********************************************************************/
static T_COUNT_BYTE DtrmnJ1979_SuppM9Infotypes(T_COUNT_BYTE Ly1979_InfoType,
                                               T_COUNT_BYTE Ly1979_DataIdx)
{
   switch(Ly1979_InfoType)
   {
      case Cy1979_InfoType0:

         WrtDCAN_ServiceData( Ly1979_InfoType ,
                         Ly1979_DataIdx++ );

         WrtDCAN_ServiceData( KyDCAN_Mode_09_Info_01_To_08 ,
                         Ly1979_DataIdx++ );

         WrtDCAN_ServiceData( Ky1979_Mode_09_Info_09_To_16 ,
                         Ly1979_DataIdx++ ) ;

         WrtDCAN_ServiceData( Ky1979_Mode_09_Info_17_To_24,
                         Ly1979_DataIdx++ ) ;

         WrtDCAN_ServiceData( Ky1979_Mode_09_Info_25_To_32 ,
                         Ly1979_DataIdx++ ) ;

         Sb1979_M9_InfoTypeFound = CbTRUE;
         break;

      case Cy1979_InfoType20:
      case Cy1979_InfoType40:
      case Cy1979_InfoType60:
      case Cy1979_InfoType80:
      case Cy1979_InfoTypeA0:
      case Cy1979_InfoTypeC0:
      case Cy1979_InfoTypeE0:
         break;
      default :
         Sb1979_M9_InfoTypeFound = CbFALSE;
         break;
   }

   return (Ly1979_DataIdx);
}

/*********************************************************************/
/* FUNCTION:     FormJ1979_NextMode49_DCAN                                */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Invoked periodically to send many more mode 49      */
/*               responses depending on the available calibration ids*/
/*               as response to the previous mode 9 request received.*/
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: Va1979_M49_Data                         */
/*********************************************************************/

void FormJ1979_NextMode49_DCAN( void )
{
   BYTE                Ly1979_DataIdx ;
   FOUR_BYTE_DATA_TYPE Lg1979_CalVerNum[ Cy1979_MaxCalIDs ];
#if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
    (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
   FOUR_BYTE_DATA_TYPE Lg1979_CalVerNum_TRN[ Cy1979_MaxCalIDs ];
#endif
  /* fix the bug of receiving "0xBF" when 0x78 Response*/
   Ly1979_DataIdx = 0;
   WrtDCAN_ServiceData( Cy1979_Mode09 , Ly1979_DataIdx++ );
   WrtDCAN_ServiceData( Vy1979_InfoType , Ly1979_DataIdx++ );

   switch(Vy1979_InfoType)
   {
      case Cy1979_InfoType6:
        Sy1979_Mode09_CalIdx = 0;

   #if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
       (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
        WrtDCAN_ServiceData((Cy1979_Info_06_NumDataItems * Cy1979_MaxCVNIDsPCM),
                              Ly1979_DataIdx++) ;
   #else
        WrtDCAN_ServiceData((Cy1979_Info_06_NumDataItems * Cy1979_MaxCVNIDs),
                              Ly1979_DataIdx++) ;
   #endif

        /* Returns CRC of calibration area*/
        if(GetFILE_CVN_Available() && (!Sb1979_EngCVNSent))
        {
            // Lg1979_CalVerNum[Sy1979_Mode09_CalIdx] = GetFILE_CVN();

            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum[Sy1979_Mode09_CalIdx].Byte_Access.Byte_One,
                                           Ly1979_DataIdx++) ;
            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum[Sy1979_Mode09_CalIdx].Byte_Access.Byte_Two,
                                           Ly1979_DataIdx++) ;
            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum[Sy1979_Mode09_CalIdx].Byte_Access.Byte_Three,
                                           Ly1979_DataIdx++) ;
            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum[Sy1979_Mode09_CalIdx].Byte_Access.Byte_Four,
                                           Ly1979_DataIdx++) ;

            Sb1979_EngCVNSent = CbTRUE;
        }

   #if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
       (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
        if(GetTRVC_TransCntrlIsPCM()
          && (GetFILE_CVN_Available_TRN())
          && (Sb1979_EngCVNSent))
        {
            // Lg1979_CalVerNum_TRN[Sy1979_Mode09_CalIdx] = GetFILE_CVN_TRN();

            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum_TRN[Sy1979_Mode09_CalIdx].Byte_Access.Byte_One,
                                           Ly1979_DataIdx++) ;
            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum_TRN[Sy1979_Mode09_CalIdx].Byte_Access.Byte_Two,
                                           Ly1979_DataIdx++) ;
            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum_TRN[Sy1979_Mode09_CalIdx].Byte_Access.Byte_Three,
                                           Ly1979_DataIdx++) ;
            WrtDCAN_ServiceData
                ( Lg1979_CalVerNum_TRN[Sy1979_Mode09_CalIdx].Byte_Access.Byte_Four,
                                           Ly1979_DataIdx++) ;
        }
   #endif
        break;

      default:
         break;
    }

    if ((Vy1979_InfoType == Cy1979_InfoType6)
#if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
    (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
        && (!GetFILE_CVN_Available() || !GetFILE_CVN_Available_TRN()))
#else
        && (!GetFILE_CVN_Available() ))
#endif
    {
       WrtDCANMultiRespInProgress( CbTRUE ) ;
       Sb1979_EngCVNSent = CbFALSE;
       /***********************************************************
       * Check if another 78 negative response needs to be sent   *
       ***********************************************************/
       if(GetDCAN_Send_Next_78Response())
       {
          SendLnStandardNegativeAnswer(
                  CcDCAN_ReqCorrectlyRecvd_ResponsePending);
          SetDCAN_Send_Next_78Response(CbFALSE);
       }
    }
    else if(Vy1979_InfoType == Cy1979_InfoType6)
    {
       SendLnStandardPositiveAnswer( Ly1979_DataIdx );
       WrtDCANMultiRespInProgress( CbFALSE ) ;
    }
    else
    {
       /* Do nothing */
    }
}

/*********************************************************************/
/* FUNCTION:     GetDCANService09Info08data                        */
/*                                                                   */
/* Type:         static                                              */
/*                                                                   */
/* DESCRIPTION:  This function sets up the response data for SID 09  */
/*               info type 08                                        */
/*                                                                   */
/* PARAMETERS:   BYTE                                                */
/*                                                                   */
/* RETURN:       BYTE                                                */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
static BYTE GetDCANService09Info08data(BYTE LyBufferIndex)
{
   FOUR_BYTE_DATA_TYPE Ludata;

   Ludata.Word_Access.Word_One = GetDGDM_RM_Generic_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_OFVC_IgnCycleCntr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_ICMD_B1_Numrtr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_ICMD_B1_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_ICMD_B2_Numrtr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_ICMD_B2_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B1_S1_Numrtr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B1_S1_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B2_S1_Numrtr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B2_S1_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EGR_VVT_Numrtr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EGR_VVT_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_SAID_Numrtr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_SAID_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EVPD_Numrtr();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EVPD_Denom();

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B1_S2_Numrtr();

   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B1_S2_Denom();

   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;
   
   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B2_S2_Numrtr();

   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;

   Ludata.Word_Access.Word_One = GetDGDM_RM_EOSD_B2_S2_Denom();

   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_One,
                   LyBufferIndex++) ;

   WrtDCAN_ServiceData ( Ludata.Byte_Access.Byte_Two,
                   LyBufferIndex++) ;
   return LyBufferIndex;
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979ModeAHandler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  Handles the initial request to transmit permanent   */
/*               fault codes.  The pupose of this service is to      */
/*               enable the external tester to obtain all DTCs with  */
/*               Permanent DTC status. These DTCs thatare confirmed  */
/*               and are retained in the non-volatile memory of the  */
/*               server until the appropriate monitor for each DTC   */
/*               has determined that the malfunction is no longer    */
/*               present and is not commanding the MIL on.           */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_0A_Supported == CeDCAN_Supported)
#define J1979_MODE_0A_MSG_LENGTH   (1)
#define J1979_Mode_4A_DTC_Length   (7)
#define CcMA_RETURN_ID_OFFSET      (2)

void J1979ModeAHandler (void)
{
   /*Check if it is in standard diagnostic mode to support service*/
   if(CheckStandardDiagnosticState())
   {
      /* Test for valid  message length */
      if (( J1979_MODE_0A_MSG_LENGTH ) ==
                           GetLnServiceDataLength() )
      {
         FormJ1979_Mode_4A_Data ();
      }
      else
      {
         /* Do not send a response if request invalid */
         PfrmDCAN_AckReqWithoutResponse();
      }
   }
   else
   {
       /* Do not send a response if the ECU is not in standard diagnostic session */
       PfrmDCAN_AckReqWithoutResponse();
   }
}

/*********************************************************************/
/* FUNCTION:     FormJ1979_Mode_4A_Data                              */
/*                                                                   */
/* Type:         local                                               */
/*                                                                   */
/* DESCRIPTION:  Invoked by Mode_0A handler as well as Queue1979_Next*/
/*               Mode4A procedure, this function finds out and forms */
/*               the data block for the mode 4A response.            */
/*               As long as valid fault codes exist, this procedure  */
/*               will continue to queue new messages.  When no more  */
/*               faults exist, the remaining bytes of the CAN        */
/*               message are padded with 0s.                         */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/*********************************************************************/
void FormJ1979_Mode_4A_Data( void )
{
    BYTE                 LcPermnNDTCCount ;
    BYTE                 TrByteCount ;
    DTC_STATUS_INFO_TYPE DTCRecord;
    WORD                 ReadDTCFaultCode;

    TrByteCount = CcMA_RETURN_ID_OFFSET ;
    LcPermnNDTCCount = V_COUNT_BYTE(0);

    while ( ( GetCMN_PD_PermNDTCArray( LcPermnNDTCCount ) != 0 )
             && (LcPermnNDTCCount < GetCMN_PD_NumOfEEpromDTCs() ) )
    {
       ReadDTCFaultCode = GetCMNDTCP_Code (GetCMN_PD_PermNDTCArray( LcPermnNDTCCount ));
       DTCRecord.DTC_Number.Word_Access = ReadDTCFaultCode;
          WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_One,
                         TrByteCount++);
          WrtDCAN_ServiceData(DTCRecord.DTC_Number.Byte_Access.Byte_Two,
                         TrByteCount++);
       LcPermnNDTCCount++;
    }
    WrtDCAN_ServiceData( LcPermnNDTCCount, CyModeA_NumDTC_Offset);
    SendLnStandardPositiveAnswer (TrByteCount);
}
#endif


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0  110401  cjqq       Base on GMLAN project
* 7.0  130614  xll  SCR#1153 RSM_CTC_8205_OBD_IUPT_InterfaceChange For Mode 09 type 08_v01_20130402.doc
* 8.0  130628  xll  SCR#1168 Change GetSYST_BTC_NR() to KySYST_BTC_NR[].
* 9.0  130830  xll  RCR#1239 Added LbValid_PID in function J1979Mode1Handler_DCAN(),J1979Mode2Handler_DCAN()
*
******************************************************************************/
