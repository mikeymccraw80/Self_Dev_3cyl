/******************************************************************************
 *
 * Filename:          dcancarb.c
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
 *                    J1979ModeBHandler
 *                    J1979ModeCHandler
 *                    J1979ModeDHandler
 *                    J1979ModeEHandler
 *                    J1979ModeFHandler
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
 * %full_name:     mt20u2#1/csrc/dcanlegi.c/1 %
 * %date_created:  Tue Sep  7 14:57:25 2010 %
 * %version:       1 %
 * %derived_by:    pz0vmh %
 *
 *****************************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/
//#include "obdsfexi.h" /*GetVIOS_EngSt_Run()*/

/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanlegi.h"
#include "dcanpmid.h"  /*GetDCAN_Param_Value(),GetDCAN_TID_Num(),GetDCAN_MIDNumber()*/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlcdat.h"/*KyDCAN_Mode_09_Info_01_To_08*/
#include "obdlfsrv.h"/*Cy1979_SuppPIDRange_00_20*/
//#include "obdlfpid.h"/*MaskMode_01*/
//#include "cmnpid.h"/*MaskMode_01,Get_Valid_PID_Info*/
//#include "obdlfdtc.h"/*Get_Next_Valid_Emission_P_Code*/
//#include "obdlnvmd.h"/*VinFirst*/
//#include "kw2nvmd.h"/*VinFirst*/
#include "kw2srv10m.h"
//#include "ofvccald.h" /*KbDCANCORE_MODE4_With_EngRUN*/
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"  /*for PfrmDCAN_AckReqWithoutResponse()*/
//#include "dcantran.h" /*for GetLnServiceData()*/
#include "j1979.h"/*Cy1979_SuppPIDRange_00_20,TsC2AP_O2Sensor*/
#include "kw2cal.h"/*KyDCAN_Mode_09_Info_01_To_08*/
#include "obdltype.h"/*BYTEANDWORD1*/
#include "kw2type.h"/*FOUR_BYTE_DATA_TYPE*/
//#include "cmndtc.h"/*DTC_STATUS_INFO_TYPE Get_Next_Valid_Emission_P_Code*/
#include "dcanfapi.h" 
#include "dcancreuse.h"
//#include "ddmspapi.h"
/*********************************************************************/
/*            TYPE DEFS                                              */
/*********************************************************************/

/*********************************************************************/
/*            EQUATES                                                */
/*********************************************************************/
#define ConvRATIO_0_128(x)   ( ( (x) * 32) / 512)

/*********************************************************************/
/*            GLOBAL CONSTANT VARIABLES                              */
/*********************************************************************/
//TbBOOLEAN VbDCAN_NRC78hexInProgress;
//TbBOOLEAN VbDCAN_SendNRC78hexResponse;

#if (XeDCAN_SID_06_Supported == CeDCAN_Supported)
BYTE   VyDCAN_1979_RequestedMID;
#endif

/*********************************************************************/
/*            STATIC DATA DECLARATIONS                               */
/*********************************************************************/
#if (XeDCAN_SID_08_Supported == CeDCAN_Supported)
//static TeMode8TestIDStatus             Se1979Mode8TestID_01_Status;
#endif

#if (XeDCAN_SID_09_Supported == CeDCAN_Supported)
static BYTE                            Sy1979_Mode09_CalIdx ;
static TbBOOLEAN                       Sb1979_M9_InfoTypeFound;
#endif

/*********************************************************************/
/*            Static FUNCTIONS                                       */
/*********************************************************************/
#if (XeDCAN_SID_05_Supported == CeDCAN_Supported)
static TsC2AP_O2Sensor Read_O2Sensor_DCAN(BYTE , BYTE);
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
//extern TbBOOLEAN                       Sb1979_EngCVNSent;
//extern BYTE    Vy1979_InfoType ;
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
             La1979_ServiceData[Ly1979_DataIdx] = (GetLnServiceData (Ly1979_DataIdx));
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
            if(Get_Valid_PID_Info((WORD)
               La1979_ServiceData[Ly1979_PIDIdx], MaskMode_01))
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
                   ProcessReqstdPIDData( DCAN_GetServiceData(), Ly1979_MsgIdx ,
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
            SendStandardPositiveAnswer ( Ly1979_MsgIdx  );
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
             La1979_ServiceData[Ly1979_DataIdx] = (GetLnServiceData (Ly1979_DataIdx));
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
            if(Get_Valid_PID_Info((WORD)Ly1979_RequestedPID, MaskMode_02)
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
                    ProcessReqstdPIDData(DCAN_GetServiceData(), Ly1979_MsgIdx,
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
            SendStandardPositiveAnswer ( Ly1979_MsgIdx );
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
//#define J1979_Mode_43_DTC_Length   (7)
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
    //DTC_STATUS_INFO_TYPE DTCRecord, *DTCRecordPtr ;
    DTC_STATUS_INFO_TYPE DTCRecord ;
    MODES_TYPE           ModeVal ;

    TrByteCount = CcM3_RETURN_ID_OFFSET ;
    ModeVal     = MODE_3 ;
    Lc1979_ValidDTCCount = V_COUNT_WORD(0);
    DTCCount = V_COUNT_WORD(0);

    while ( DTCCount < GetCMNMaxNumberOfDTCs () )
    {
     //  DTCRecordPtr = Get_Next_Valid_Emission_P_Code ( DTCCount, ModeVal );
      // DTCRecord = *DTCRecordPtr;
       //DTCCount++;
       DTCRecord = Get_Next_Valid_Emission_P_Code ( DTCCount,
                                                    ModeVal );
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

    SendStandardPositiveAnswer (TrByteCount);
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
        && ( GetVIOS_EngSt_Run() )
        && ( ! KbDCANCORE_MODE4_With_EngRUN ) )
      {
         SendStandardNegativeAnswer(
                       CcDCAN_CondNotCorrect_RequestSequenceError);
      }
      else if (GetLnServiceDataLength() ==
                    ( J1979_MODE_04_MSG_LENGTH ))
      {
         /* It is not required to reply after clearing the DTC's.
          * The DTC's should be cleared within 1 second of sending
          * the response.
         */
         SendStandardPositiveAnswer ( CcM4_RETURN_ID_OFFSET );
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

   Ly1979_TestID  = (GetLnServiceData (CyTestIDMode5));
   Ly1979_O2ID    = (GetLnServiceData (Cy02IDMode5));

   /*Check if it is in standard diagnostic mode to support service*/
   if(!CheckStandardDiagnosticState())
   {
      SendStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
   }
   else
   {
      if ( J1979_MODE_05_MSG_LENGTH == GetLnServiceDataLength())
      {

         WrtDCAN_ServiceData( Ly1979_TestID , Ly1979_MsgIdx++) ;
         WrtDCAN_ServiceData( Ly1979_O2ID   , Ly1979_MsgIdx++) ;

         Ls1979_T_Code = Read_O2Sensor_DCAN(Ly1979_TestID , Ly1979_O2ID );

         if ( Ls1979_T_Code.LyTestIdFlag )
         {
            if ( OneByteO2Snsr == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;

               SendStandardPositiveAnswer ( Ly1979_MsgIdx );

            }
            else if ( ThreeByteO2Snsr == Ls1979_T_Code.LyRsltSize)
            {
               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_One ,
                               Ly1979_MsgIdx++ ) ;

               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Two ,
                               Ly1979_MsgIdx++ ) ;

               WrtDCAN_ServiceData( Ls1979_T_Code.LuRslt.Byte_Access.Byte_Three ,
                               Ly1979_MsgIdx++ ) ;

               SendStandardPositiveAnswer ( Ly1979_MsgIdx );
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

               SendStandardPositiveAnswer ( Ly1979_MsgIdx );
            }
         }
         else
         {
            /* Send negative responce if PID not supported */
            SendStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
         }
      }
      else
      {
         /* Send negative responce if PID not supported */
         SendStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
      }
   }
}

/*********************************************************************/
/* FUNCTION:    Read_O2Sensor_DCAN()                                      */
/*                                                                   */
/* Type:        static                                               */
/*                                                                   */
/* DESCRIPTION: Checks mode 5 supported test ids for any given O2-ID */
/*              if supported reads the O2_ID specified o2 sensor and */
/*              returns the scaled sensor value.                     */
/*                                                                   */
/*                                                                   */
/* PARAMETERS:  BYTE test ID and BYTE O2 ID                          */
/*                                                                   */
/* RETURN:      TsC2AP_O2Sensor                                      */
/*                                                                   */
/* Global Variables Updated: None                                    */
/* CHANGE LOG:    04/20/00 bdt add test for Lyo2ID while testing     */
/*                CeMode5TestRange0 - 80                             */
/*                                                                   */
/* REVISION NO:   1.0                                                */
/*********************************************************************/
static TsC2AP_O2Sensor Read_O2Sensor_DCAN(BYTE LyTestID, BYTE LyO2ID)
{
   TsC2AP_O2Sensor LsC2AP_O2SensorRes;
   BYTEANDWORD1 temp1;
   LsC2AP_O2SensorRes.LyRsltSize = OneByteO2Snsr;
   LsC2AP_O2SensorRes.LyTestIdFlag = CbTRUE;

   switch(LyTestID)
   {
      case Ce1979_Mode_05_TestID_3:

         switch(LyO2ID)
         {
            case CeBank1O2Sensor1:
               temp1.uword = usLookup_Rescale_xy_us(
                                    &CsC2SC_MAP256_U_O2_VOLT,
                                    GetEOSD_U_11_RespLeanThrsh() );

       #if config_Compiler_Vendor == option_TASKING
               LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         DCAN_GetHighByte(temp1.uword);
       #else
               LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = temp1.ubyte;
       #endif
               break;
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT

            case CeBank2O2Sensor1:
               temp1.uword = usLookup_Rescale_xy_us(
                                    &CsC2SC_MAP256_U_O2_VOLT,
                                    GetEOSD_U_21_RespLeanThrsh() );

       #if config_Compiler_Vendor == option_TASKING
               LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         DCAN_GetHighByte(temp1.uword);
       #else
               LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = temp1.ubyte;
       #endif
               break;
#endif

            default:
               LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;
               break;
            }
            break;

       case Ce1979_Mode_05_TestID_4:

            switch(LyO2ID)
            {
                case CeBank1O2Sensor1:

                     temp1.uword = usLookup_Rescale_xy_us(
                                         &CsC2SC_MAP256_U_O2_VOLT,
                                         GetEOSD_U_11_RespRichThrsh() );

          #if config_Compiler_Vendor == option_TASKING
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         DCAN_GetHighByte(temp1.uword);
          #else
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = temp1.ubyte;
          #endif
                     break;
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT

                case CeBank2O2Sensor1:

                     temp1.uword = usLookup_Rescale_xy_us(
                                         &CsC2SC_MAP256_U_O2_VOLT,
                                         GetEOSD_U_21_RespRichThrsh() );

          #if config_Compiler_Vendor == option_TASKING
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         DCAN_GetHighByte(temp1.uword);
          #else
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = temp1.ubyte;
          #endif
                     break;
#endif
                default:

                     LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;

                     break;
            }
            break;

       case Ce1979_Mode_05_TestID_5:

            LsC2AP_O2SensorRes.LyRsltSize = ThreeByteO2Snsr;

            switch(LyO2ID)
            {
                case CeBank1O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_11_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_11_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_11_Response)))
                     || ((GetEOSD_O2_11_RespRichLeanAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_11_RespLeanRichAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_11_ResponseRatio() == V_RATIO_0_128(0))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                    ConvO2_SECS(GetEOSD_O2_11_RespRichLeanAvg());

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                                    ConvO2_SECS(GetEOSD_11_RespRichLeanAvgThrsh());
                  }
                     break;
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT

                case CeBank2O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_21_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_21_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_21_Response)))
                     || ((GetEOSD_O2_21_RespRichLeanAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_21_RespLeanRichAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_21_ResponseRatio() == V_RATIO_0_128(0))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                     ConvO2_SECS(GetEOSD_O2_21_RespRichLeanAvg());

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                                     ConvO2_SECS(GetEOSD_21_RespRichLeanAvgThrsh());
                  }
                     break;
#endif
                default:

                     LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;

                     break;
            }
            break;
       case Ce1979_Mode_05_TestID_6:

            LsC2AP_O2SensorRes.LyRsltSize = ThreeByteO2Snsr;

            switch(LyO2ID)
            {
                case CeBank1O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_11_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_11_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_11_Response)))
                     || ((GetEOSD_O2_11_RespRichLeanAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_11_RespLeanRichAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_11_ResponseRatio() == V_RATIO_0_128(0))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                  ConvO2_SECS(GetEOSD_O2_11_RespLeanRichAvg());

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                                  ConvO2_SECS(GetEOSD_11_RespLeanRichAvgThrsh());
                  }
                     break;
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT

                case CeBank2O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_21_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_21_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_21_Response)))
                     || ((GetEOSD_O2_21_RespRichLeanAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_21_RespLeanRichAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_21_ResponseRatio() == V_RATIO_0_128(0))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                     ConvO2_SECS(GetEOSD_O2_21_RespLeanRichAvg());

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                                     ConvO2_SECS(GetEOSD_21_RespLeanRichAvgThrsh());
                  }
                     break;
#endif
                 default:

                     LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;

                     break;
            }
            break;

       case Ce1979_Mode_05_TestID_70:

            LsC2AP_O2SensorRes.LyRsltSize = ThreeByteO2Snsr;

            switch(LyO2ID)
            {
                case CeBank1O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_11_Response) == CeDGDM_FAULT_TYPE_Z )
                    || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_11_Response))
                        && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_11_Response))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     if(GetEOSD_O2_11_RespRichLeanSwCntr() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         (BYTE)GetEOSD_O2_11_RespRichLeanSwCntr();
                     }

                     if(GetEOSD_Cnt_11_RespRL_SwThrsh() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                                         (BYTE)GetEOSD_Cnt_11_RespRL_SwThrsh();
                     }

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = MAXBYTE;
                  }
                  break;
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT

                case CeBank2O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_21_Response) == CeDGDM_FAULT_TYPE_Z )
                    || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_21_Response))
                        && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_21_Response))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     if(GetEOSD_O2_21_RespRichLeanSwCntr() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         (BYTE)GetEOSD_O2_21_RespRichLeanSwCntr();
                     }

                     if(GetEOSD_Cnt_21_RespRL_SwThrsh() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                                         (BYTE)GetEOSD_Cnt_21_RespRL_SwThrsh();
                     }

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = MAXBYTE;
                  }
                  break;
#endif
                default:

                LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;

                break;
            }
            break;

       case Ce1979_Mode_05_TestID_71:

            LsC2AP_O2SensorRes.LyRsltSize = ThreeByteO2Snsr;

            switch(LyO2ID)
            {
                case CeBank1O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_11_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_11_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_11_Response))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     if(GetEOSD_O2_11_RespLeanRichSwCntr() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         (BYTE)GetEOSD_O2_11_RespLeanRichSwCntr();
                     }

                     if(GetEOSD_Cnt_11_RespLR_SwThrsh() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                                         (BYTE)GetEOSD_Cnt_11_RespLR_SwThrsh();
                     }

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = MAXBYTE;
                  }
                  break;
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT

                case CeBank2O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_21_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_21_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_21_Response))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     if(GetEOSD_O2_21_RespLeanRichSwCntr() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                                         (BYTE)GetEOSD_O2_21_RespLeanRichSwCntr();
                     }

                     if(GetEOSD_Cnt_21_RespLR_SwThrsh() > MAXBYTE)
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = MAXBYTE;
                     }
                     else
                     {
                        LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                                         (BYTE)GetEOSD_Cnt_21_RespLR_SwThrsh();
                     }

                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = MAXBYTE;
                  }
                  break;
#endif
                default:

                LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;

                break;
            }
            break;

       case Ce1979_Mode_05_TestID_81:

            LsC2AP_O2SensorRes.LyRsltSize = ThreeByteO2Snsr;

            switch(LyO2ID)
            {
                case CeBank1O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_11_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_11_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_11_Response)))
                     || ((GetEOSD_O2_11_RespRichLeanAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_11_RespLeanRichAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_11_ResponseRatio() == V_RATIO_0_128(0))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     temp1.uword = ConvRATIO_0_128(GetEOSD_O2_11_ResponseRatio());
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                            (BYTE)DCAN_LimitFunction(0,temp1.uword,MAXBYTE);

                     temp1.uword = ConvRATIO_0_128(GetEOSD_11_RespRatioThrshLo());
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                            (BYTE)DCAN_LimitFunction(0,temp1.uword,MAXBYTE);

                     temp1.uword = ConvRATIO_0_128(GetEOSD_11_RespRatioThrshHi());
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                            (BYTE)DCAN_LimitFunction(0,temp1.uword,MAXBYTE);
                  }
                  break;
#if XeSYST_EOSD_21_SENSOR == CeSYST_EOSD_SENSOR_PRESENT

                case CeBank2O2Sensor1:

                  if((GetDGDM_DTC_FaultType (CeDGDM_O2_21_Response) == CeDGDM_FAULT_TYPE_Z )
                     || ((GetDGDM_TestNotPassedSnceCdClr(CeDGDM_O2_21_Response))
                         && ( !GetDGDM_TestFailSinceCodeClr(CeDGDM_O2_21_Response)))
                     || ((GetEOSD_O2_21_RespRichLeanAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_21_RespLeanRichAvg() == V_RATIO_0_128(0))
                         && (GetEOSD_O2_21_ResponseRatio() == V_RATIO_0_128(0))))
                  {
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two = 0x00;
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three = 0x00;
                  }
                  else
                  {
                     temp1.uword = ConvRATIO_0_128(GetEOSD_O2_21_ResponseRatio());
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                            (BYTE)DCAN_LimitFunction(0,temp1.uword,MAXBYTE);

                     temp1.uword = ConvRATIO_0_128(GetEOSD_21_RespRatioThrshLo());
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                            (BYTE)DCAN_LimitFunction(0,temp1.uword,MAXBYTE);

                     temp1.uword = ConvRATIO_0_128(GetEOSD_21_RespRatioThrshHi());
                     LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                            (BYTE)DCAN_LimitFunction(0,temp1.uword,MAXBYTE);
                  }
                  break;
#endif
                default:

                LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;

                break;
            }
            break;

       case CeMode5TestRange0:

            if( (CeBank1O2Sensor1 == LyO2ID) ||
                (CeBank2O2Sensor1 == LyO2ID) )
            {
                LsC2AP_O2SensorRes.LyRsltSize = FourByteCalConst;

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                Ka1979_M5_TestRange_00Thru80[0];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                Ka1979_M5_TestRange_00Thru80[1];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                Ka1979_M5_TestRange_00Thru80[2];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Four =
                Ka1979_M5_TestRange_00Thru80[3];
            }
            else
            {
                LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;
            }
            break;

       case CeMode5TestRange20:

            if( (CeBank1O2Sensor1 == LyO2ID) ||
                (CeBank2O2Sensor1 == LyO2ID) )
            {
                LsC2AP_O2SensorRes.LyRsltSize = FourByteCalConst;

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                Ka1979_M5_TestRange_00Thru80[4];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                Ka1979_M5_TestRange_00Thru80[5];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                Ka1979_M5_TestRange_00Thru80[6];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Four =
                Ka1979_M5_TestRange_00Thru80[7];
            }
            else
            {
            LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;
            }
            break;

       case CeMode5TestRange40:

            if( (CeBank1O2Sensor1 == LyO2ID) ||
                (CeBank2O2Sensor1 == LyO2ID) )
            {
                LsC2AP_O2SensorRes.LyRsltSize = FourByteCalConst;

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                              Ka1979_M5_TestRange_00Thru80[8];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                              Ka1979_M5_TestRange_00Thru80[9];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                              Ka1979_M5_TestRange_00Thru80[10];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Four =
                              Ka1979_M5_TestRange_00Thru80[11];
            }
            else
            {
                LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;
            }
            break;

       case CeMode5TestRange60:

            if( (CeBank1O2Sensor1 == LyO2ID) ||
                (CeBank2O2Sensor1 == LyO2ID) )
            {
                LsC2AP_O2SensorRes.LyRsltSize = FourByteCalConst;

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                Ka1979_M5_TestRange_00Thru80[12];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                Ka1979_M5_TestRange_00Thru80[13];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                Ka1979_M5_TestRange_00Thru80[14];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Four =
                Ka1979_M5_TestRange_00Thru80[15];
            }
            else
            {
                LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;
            }

            break;

       case CeMode5TestRange80:

            if( (CeBank1O2Sensor1 == LyO2ID) ||
                (CeBank2O2Sensor1 == LyO2ID) )
            {
                LsC2AP_O2SensorRes.LyRsltSize = FourByteCalConst;

      LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_One =
                Ka1979_M5_TestRange_00Thru80[16];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Two =
                Ka1979_M5_TestRange_00Thru80[17];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Three =
                Ka1979_M5_TestRange_00Thru80[18];

                LsC2AP_O2SensorRes.LuRslt.Byte_Access.Byte_Four =
                Ka1979_M5_TestRange_00Thru80[19];
            }
            else
            {
                LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;
            }

            break;

        default:

            LsC2AP_O2SensorRes.LyTestIdFlag = CbFALSE;

            break;
   }

   return(LsC2AP_O2SensorRes);
}

/*********************************************************************
* FUNCTION:     DCAN_LimitFunction                                  *
* DESCRIPTION:  Limits the input value between the limits            *
*                                                                    *
*********************************************************************/
INLINE WORD DCAN_LimitFunction(WORD LfLower,WORD LfValue,WORD LfUpper)
{
    WORD LfLimitVal;

    if (LfValue < LfLower)
    {
        LfLimitVal = LfLower;
    }
    else if (LfValue > LfUpper)
    {
        LfLimitVal = LfUpper;
    }
    else
    {
        LfLimitVal = LfValue;
    }

 return  LfLimitVal;
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
            LaDCAN_ServiceData[LyDCAN_DataIdx] = (GetLnServiceData (LyDCAN_DataIdx));
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
            SendStandardPositiveAnswer ( LyDCAN_MsgIdx  );
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

 /*  if ( CeDGDM_Misfire == LeDCAN_DTC_ID )
   {
      if ( DtrmnMISF_CAN_TestReportingEnabled() )
      {
         LbDCAN_TestReportingEnabled = CbTRUE;
      }
   }
   else*/ if ( ( CeDGDM_NoFault == LeDCAN_DTC_ID )
          || ( ( CeDGDM_FAULT_TYPE_Z != GetDGDM_DTC_FaultType(LeDCAN_DTC_ID) )
            &&( ( GetDGDM_TestFailSinceCodeClr(LeDCAN_DTC_ID) )||
                 ( !GetDGDM_TestNotPassedSnceCdClr(LeDCAN_DTC_ID) ))   ) )
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


    //DTC_STATUS_INFO_TYPE DTCRecord, *DTCRecordPtr ;
    DTC_STATUS_INFO_TYPE DTCRecord ;
    MODES_TYPE  ModeVal ;

    TrByteCount = CcM7_RETURN_ID_OFFSET ;
    Lc1979_ValidDTCCount = V_COUNT_WORD(0);
    DTCCount = V_COUNT_WORD(0);

    ModeVal = MODE_7 ;

    while ( DTCCount < GetCMNMaxNumberOfDTCs () )
    {
       // DTCRecordPtr = Get_Next_Valid_Emission_P_Code ( DTCCount,
        //                                                ModeVal ) ;
        //DTCRecord = *DTCRecordPtr ;
        //DTCCount++ ;
        DTCRecord = Get_Next_Valid_Emission_P_Code ( DTCCount,
                                                    ModeVal );
        DTCCount++;
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

    SendStandardPositiveAnswer (TrByteCount) ;
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
      SendStandardNegativeAnswer(
                            CcDCAN_SubFuncNotSupp_InvalidFormat );
   }
   else
   {
      Refresh1979_Mode8_SystemLeakTest_DCAN( );

      /* Do message verification and validation */
      if ( Ky1979_MODE_08_MSG_LENGTH  ==
                              GetLnServiceDataLength())
      {
         Ly1979_TestRange_TestID = (GetLnServiceData (CyTestID_OR_Range));
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
               SendStandardPositiveAnswer( Li1979_MsgIdx );
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
              SendStandardNegativeAnswer(
                              CcDCAN_SubFuncNotSupp_InvalidFormat);
            }
         }
         else
         {
            SendStandardNegativeAnswer(CcDCAN_SubFuncNotSupp_InvalidFormat);
         }

         if(CbTRUE == LyFlag)
         {
            SendStandardPositiveAnswer( Li1979_MsgIdx );
         }
      }
      else
      {
         /* Send negative responce if Test ID not supported */
         SendStandardNegativeAnswer(
                              CcDCAN_SubFuncNotSupp_InvalidFormat);
      }
   }
   SendStandardNegativeAnswer( CcDCAN_ServiceNotSupported ) ;
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
#define CcFILE_CAL_ID_SIZE           16
#define SizeofKySYST_CALIBRATION_FILE_PART_NR   8
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
//   Sb1979_EngCVNSent = CbFALSE;
   Ly1979_DataIdx = CyInfoType ;
   Lb1979_Found  = CbFALSE;
   Sb1979_M9_InfoTypeFound = CbFALSE;
   //Lb1979_MultiMode = CbFALSE;

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
            La1979_ServiceData[Ly1979_BuffIdx] = (GetLnServiceData (Ly1979_BuffIdx));
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
                     //ReadFILE_EE_FLASH_VIN(VinFirst);
                     GetVinDataValue();

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

                     for (Ly1979_Index = 0; Ly1979_Index <CcFILE_CAL_ID_SIZE ;
                          Ly1979_Index++)
                     {
                        if (Ly1979_Index<SizeofKySYST_CALIBRATION_FILE_PART_NR)
                        {
                           //WrtDCAN_ServiceData( GetSYST_BTC_NR(Ly1979_Index),
                             //                          Ly1979_DataIdx++);

				WrtDCAN_ServiceData   ( KySYST_CALIBRATION_FILE_PART_NR
                                                   [Ly1979_Index], Ly1979_DataIdx++);
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
#if 0
               case Cy1979_InfoType6:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                         (KyDCAN_Mode_09_Info_01_To_08,
                                          Cy1979_InfoType_06_BitPosVal) )
                  {
                      /* Send back a negative response indicating
                         that the function is not complete. */
                 //#if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
                  //   (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
                     // if(GetTRVC_TransCntrlIsPCM())
                     // {
                     //     if(!GetFILE_CVN_Available()
                     //        || !GetFILE_CVN_Available_TRN())
                      //    {
                      //        SendStandardNegativeAnswer(
                       //          CcDCAN_ReqCorrectlyRecvd_ResponsePending);
                       //   }
                     // }
                     // else
                  //#endif
                      //{
                       //   if(!GetFILE_CVN_Available())
                          {
                              SendStandardNegativeAnswer(
                                    CcDCAN_ReqCorrectlyRecvd_ResponsePending);
                          }
                     // }

                      Lb1979_MultiMode = CbTRUE ;
                  }
                  else
                  {
                      Lb1979_Found = CbFALSE ;
                  }
                  break;
#endif
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
#if 0
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

#endif				  
               case Cy1979_InfoType0A:
                  if ( CbFALSE != Chk1979_Md9_InfoTypeSupported
                                   (Ky1979_Mode_09_Info_09_To_16,
                                    Cy1979_InfoType_0A_BitPosVal) )
                  {
                     WrtDCAN_ServiceData( Cy1979_Info_0A_NumDataItems,
                                        Ly1979_DataIdx++) ;

                     if( GetTRVC_TransCntrlIsManual())
                    //     || GetTRVC_TransCntrlIsTCM())
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
          //  if(( Lb1979_MultiMode )
            //  && ( Lb1979_Found ))
           // {
            //   WrtDCANMultiRespInProgress( CbTRUE ) ;
           // }
            //else if ( Lb1979_Found )

	     if ( Lb1979_Found )
            {
               SendStandardPositiveAnswer( Ly1979_DataIdx );
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
               SendStandardPositiveAnswer( Ly1979_DataIdx );
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
#if 0
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
//#define        HexZero     0
void FormJ1979_NextMode49_DCAN( void )
{
   BYTE                Ly1979_DataIdx ;
   FOUR_BYTE_DATA_TYPE Lg1979_CalVerNum[ Cy1979_MaxCalIDs ];
//#if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
 //   (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
//   FOUR_BYTE_DATA_TYPE Lg1979_CalVerNum_TRN[ Cy1979_MaxCalIDs ];
//#endif
  /* fix the bug of receiving "0xBF" when 0x78 Response*/
   Ly1979_DataIdx = 0;
   WrtDCAN_ServiceData( Cy1979_Mode09 , Ly1979_DataIdx++ );
   WrtDCAN_ServiceData( Vy1979_InfoType , Ly1979_DataIdx++ );

   switch(Vy1979_InfoType)
   {
      case Cy1979_InfoType6:
        Sy1979_Mode09_CalIdx = 0;

 //  #if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
    //   (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
  //      WrtDCAN_ServiceData((Cy1979_Info_06_NumDataItems * Cy1979_MaxCVNIDsPCM),
  //                            Ly1979_DataIdx++) ;
 //  #else
        WrtDCAN_ServiceData((Cy1979_Info_06_NumDataItems * Cy1979_MaxCVNIDs),
                              Ly1979_DataIdx++) ;
 //  #endif

        /* Returns CRC of calibration area*/
       // if(GetFILE_CVN_Available() && (!Sb1979_EngCVNSent))
        if(!Sb1979_EngCVNSent)
        {
            Lg1979_CalVerNum[Sy1979_Mode09_CalIdx] = GetFILE_CVN();

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
#if 0
   #if (XeTRVS_SYST_TYPE == XeTRVS_SYST_PCM) && \
       (XeSYST_SEPERATE_CAL == CeSYST_AVAILABLE)
        if(GetTRVC_TransCntrlIsPCM()
          && (GetFILE_CVN_Available_TRN())
          && (Sb1979_EngCVNSent))
        {
            Lg1979_CalVerNum_TRN[Sy1979_Mode09_CalIdx] = GetFILE_CVN_TRN();

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
          SendStandardNegativeAnswer(
                  CcDCAN_ReqCorrectlyRecvd_ResponsePending);
          SetDCAN_Send_Next_78Response(CbFALSE);
       }
    }
    else if(Vy1979_InfoType == Cy1979_InfoType6)
    {
       SendStandardPositiveAnswer( Ly1979_DataIdx );
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
   return LyBufferIndex;
}
#endif
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
    SendStandardPositiveAnswer (TrByteCount);
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979ModeBHandler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:                                                      */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_0B_Supported == CeDCAN_Supported)
void J1979ModeBHandler (void)
{
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979ModeCHandler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:                                                      */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_0C_Supported == CeDCAN_Supported)
void J1979ModeCHandler (void)
{
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979ModeDHandler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:                                                      */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_0D_Supported == CeDCAN_Supported)
void J1979ModeDHandler (void)
{
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979ModeEHandler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:                                                      */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_0E_Supported == CeDCAN_Supported)
void J1979ModeEHandler (void)
{
}
#endif

/*********************************************************************/
/* FUNCTION:     J1979ModeFHandler                                   */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:                                                      */
/*                                                                   */
/* PARAMETERS:   None                                                */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/*********************************************************************/
#if (XeDCAN_SID_0F_Supported == CeDCAN_Supported)
void J1979ModeFHandler (void)
{
}
#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.01  04-07-98  EPA       Converted code from Greg Hogdal (DE Lux.)
*                           for our use, started from version 1.3
*                           RSM # 00LD9-046
* 1.2   11-13-97  EPA       Added some extern's.
* 1.4   10-15-98  cdw       New version created from Daewoo delivery
* 1.5   11-15-98  cdw       Fixed and reduce function code
* 1.8   02-10-98  cdw       Fixed and reduce function code
* 1.9   07-27-99  HFU       Changed modes 6 and 8.
* 2.0   09-17-99  HFU       SID 08 Request Message Length changed to 7,
*                           and Set Flag VbOFVC_EVPD_SerBay_Test_Req.
*                           SID 03 if no DTCs pad response with zeroes.
* 2.1   09-24-99  HFU       Delete all zero's message in SID 07 if DTC
*                           found according to Daewoo Spec.
* 2.2   10-04-99  HFU     Removed TestID 06 in SID06 in Daewoo Project.
* 2.3   10-20-99  HFU       Changed for SID2, which will give negative
*                           response for PIDs 3 and above if no DTC
*                           stored in Freeze Frame.
* 2.4   11-11-99  hfu       Delete Is1979_Mode5_TestID_Supported and
*                           Is1979_M6_TestIdSupported functions.
* 2.5   12-22-99  HFU     Correct function ComputeCRC_CalibrationArea,
*                         add function call PerformHWIO_ToggleWatchdog.
* 2.6   02-01-00  HFU       SID 09-Info 06, send negative response 78
*                           first, then send the result of CRC-16.
* 2.7   04-05-00  bdt       Remove SID 06 test 0A, no longer supported.
*                           T-150    ver. 1.7
* 2.8   04-10-00  bdt       Remove SID 08 which is no longer supported.
*                           T-150    ver. 1.7
* 2.9   04-14-00  hfu       For SID 9 Info 06 set Sy1979_Mode09_CalIdx
*                           index to zero
* 3.0   05-05-00  IAJ       Replace vin access routines with the new
*                           routines.
* 3.1   05-18-00  hfu       Hook up SID 09-04 to return
*                           KySYST_CALIBRATION_FILE_PART_NR.
*                           Changed SID 02 condition check.
* 3.2   05-24-00  hfu       Pad SID 09-04 last 8 bytes with Hex zeros.
* 3.3   06-08-00  hfu       Sliced CRC-16 Checksum Calculation in
*                           SID 09-06 to make it excute less time.
* 3.4   18-08-00  gps       Converted CbTRUE -> ! CbFALSE; 7 changes
* 3.5   03-15-01  SAF       Service ID 08 correction
* tcb_pt1#7
*       03-03-31  ban  2589 Changed the data type of DTC list indices
*                           from BYTE to WORD to support more than 256
*                           DTCs
* tcb_pt1#8
*       03-04-04  ban  2648 Added 0x70 in CyTestID_04CompID[] to
*                           support Bank2 data for SID 06 04
*                           Modified switch case Cy1979_InfoType8
*                           in functions J1979Mode9Handler_DCAN and
*                           FormJ1979_NextMode49_DCAN for SID 09 08
*                           Added function
*                           GetDCANService09Info08data for SID 09 08
*                           Added CySupportedPID20_Thru40 and
*                                 CySupportedPID40_Thru60 for SID 02
* tci_pt3#9
*       03-05-29  ban  2648 Modified SID 05 to match hyundai spec
* tci-pt3#10
*       03-05-09  kvm  2106 New EVAP Algorithm changes into EMS_Core,
*                            Used GetEVPD_TankProtectionMode() in
*                            function J1979Mode8Handler_DCAN
* tci_pt3#11
*       04-09-03  ban  3032 Modified SID 09 infotype 06
* x.xx  030917 rag 3101 EVPD: Modularization.
*                        Replaced evpdpall.h with evpdpapi.h
*       031007 ban          Moved initialisation of variable
*                           Li1979_DataIdx outside the IF statement
* tci_pt3#14
*       031021 ban 3074 Deleted unused local variables
* tci_pt3#15
*       031103 ban 3352 Added logic in SID 09 to split up calibration
*                       IDs for Engine and Transmission
*                       Removed KySYST_CALIBRATION_FILE_PART_NR
* tci_pt3#14.1.1
*       031103 ban 3312 Added logic in SID 09 to split up CVN
*                       for Engine and Transmission
* tci_pt3#14.2.1
*       031210 ban 3497 Added logic to support ECU Development mode
* tci_pt3#14.2.2
*       031210 ban xxxx Merge of versions tci_pt3#14.2.1 and
*                       tci_pt3#16
* tci_pt3#14.2.3
*       040305 tln 3680 Changes for Transmission Modularity
* tci_pt3#14.2.4
*       040309 tln 3680 Merged 'j1979.c-tci_pt3#14.2.3'
*                       with 'j1979.c-tcb_pt1#14.2.3'.
* tci_pt3#14.2.4.1.1
*       040323 ban 3770 Added functionality to read VIN from
*                       FLASH ROM
* tci_pt3#14.2.5
*       040322 ban 3829 Added functionality to read VIN from Flash ROM
*                       using SID 09
* tci_pt3#14.2.7
*       040422 ban 3932 Changed component IDs for test ID 04 to
*                       E0 and F0
* tci_pt3#14.2.8
*       040722 ban 4252 Changed the connection for 09 04 to
*                       KW2HyundaiCalID
* tci_pt3#14.2.7.1.1
*       040906 ban 4412 Modified Mode 3 and Mode 7
* tcb_pt1#14.3 ksr -BM- Merged 'j1979.c-tci_pt3#14.2.8' with
*                        'j1979.c-tci_pt3#14.2.7.1.1'.
* tci_pt3#14.2.8.1.1
*       040928 ban 4462 Removed support for Test ID 07 in SID 06
* tcb_pt1#14.4 ksr -BM- Merged 'j1979.c-tcb_pt1#14.3' with
*                        'j1979.c-tci_pt3#14.2.8.1.1'.
* tci_pt3#14.2.8.1.2
*       041007 ban 4534 Moved cal ID connection from EE to cal area
* tcb_pt#14.5  ksr -BM- Merged 'j1979.c-tcb_pt1#14.4' with
*                        'j1979.c-tci_pt3#14.2.8.1.2'.
* tci_pt3#14.6
*       041027 ban 4600 Modified CVN logic to meet CARB requirements
* tci_pt3#x
*       041221 ban xxxx Corrected comparison of boolean against enum
*                       in Mode 8
*                       Corrected reject reason issues with mode 8
* 2.0   051130 tln 5311 Added logic to support info types for SID 09
*                       Cy1979_InfoTypeA0, Cy1979_InfoTypeC0,
*                       Cy1979_InfoTypeE0
* 3.0   051220 tln 5491 Corrected info types for SID 09 issue
*                       to support mesg 09 00
* 4.0   060110 tln 5491 Modified FormJ1979_Mode_43_Data_DCAN() and
*                       FormJ1979_Mode_47_Data_DCAN() to eliminate the
*                       check for Addl_DTC_Found condition.
*                       (Reference RSM 5410)
* tci_pt3#x
*      06.15.06 ABH  5730 Modified  Sb1979_M9_InfoTypeFound Flag
*                         intialization in J1979Mode9Handler_DCAN
*
* tci_pt3#7
*      070305  AB 6191  Added support for Service 0x09 Infotype 0x0A
*                       Ecu Name ( ECM or PCM ).
* 8    070612 hdb 6346  MODE4 Calibratable Clear Codes
*      070612 hdb 6347 CANOBD MODE6 Misfire MIDs Report Data Conditions
* tcb_pt1#9
*      071016 vs  6614 Modified KyDCAN_ECM_EcuName, KyDCAN_PCM_EcuName
* tcb_pt#10
*      071120 mat 6698 Modified KyDCAN_PCM_EcuName to correct byte
*                       swap
* tcb_p1#11
*     080115 me  6754 Implemented Mode 0x0A handler
*                     Added stub handler for Mode 0x0B to 0x0F
* tcb_pt1#12
*     080909 me  7212 Added Mode9 IT08 RM Add Secondary O2 Results
* 13  090115 me  7637 Modified CANOBD APIs' names.
* kok_pt2#15
*       090603 woz 7672 Renamed NVM vars to follow standard naming conventions.
*
* 3.0  100906    hdg  xxx  Implemented CAN OBD in MT22.1 paltform.
*
******************************************************************************/
