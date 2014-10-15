/*===========================================================================*/
/* FILE: immo_comu.c                                                         */
/*===========================================================================*/
/* COPYRIGHT, 2004, DELPHI ELECTRONICS & SAFETY SYSTEMS, All Rights reserved */
/* Delphi Confidential                                                       */
/*===========================================================================*/
/* %name:             immo_comu.c %                                          */
/*                                                                           */
/* created_by:       Liu Zheng                                                */
/*                                                                           */
/* date_created:     26 Feb 2005                                              */
/*                                                                           */
/* %derived_by:       vzp48z %                                               */
/*                                                                           */
/* %date_modified:   %                                                       */
/*                                                                           */
/* %version:         5 %                                                     */
/*                                                                           */
/*===========================================================================*/
/* DESCRIPTION:                                                              */
/*   This file contains executive called during power On for Immobiliser.    */
/*                                                                           */
/* ABBREVIATIONS:                                                            */
/* None.                                                                     */
/*                                                                           */
/* TRACEABILITY INFO:                                                        */
/*   Design Document:                                                        */
/*                                                                           */
/*   Requirements Document(s):                                               */
/*                                                                           */
/*   Applicable Standards:                                                   */
/*   C Coding Standards:        SW_REF 264.15D.                              */
/*                                                                           */
/* DEVIATIONS FROM STANDARDS:                                                */
/* None.                                                                     */
/*                                                                           */
/*===========================================================================*/
/* REUSE: DO NOT MODIFY THIS FILE.                                           */
/* Co-ordinate any desired changes with the Software Forward Engineering and */
/* Building Blocks group                                                     */
/*===========================================================================*/
#include "reuse.h"
#include "types.h"


/* ========================================================================== *\
 * Other header files.
\* ========================================================================== */
#include "immo.h"
#include "immo_exec.h"
#include "immo_encrypt.h"
#include "immo_fexi.h"
#include "kw2app.h"
#include "kw2dll.h"
#include "kw2dllcf.h"
#include "kw2exec.h"
#include "dd_port.h"
#include "bootloader.h"
#include "os_kernel.h"
#include "dd_atd.h"
//#include "v_eep.h"
#include "Dg_malf.h"
//#include "v_vspeed.h"
#include "os_kernel.h"
#include "io_eep.h"
#include "ddmspapi.h"

/*for Siemens immo*/
#include "siemens_immossrv.h"
#include "kw2srv27.h"
/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
//extern FAR_COS void PINProtectService (void);
//extern FAR_COS TbBOOLEAN PINWriteSuccess(void);
//extern FAR_COS TbBOOLEAN SKWriteSuccess(void);
//extern FAR_COS void GoToAuthenticationState(void);
extern FAR_COS void ImmoEndService(void);
//extern FAR_COS void GoToEndTesterState(void);
extern FAR_COS void GoToEndResponderState(void);
/* ========================================================================== *\
 * Global variables.
\* ========================================================================== */
bool ImmoNoResponseDetected;
bool ImmoAuthenErrorDetected;
bool Immo_KLineDisconnected;

/*Added newly for Siemens Immo*/

TeIMMO_ActReason        VeSiemens_ActReason;
TeSiemens_ECM_Relation  VeSiemens_ECMImmoRelation;
TeIMMO_DLL_STATUS       VeSiemens_DLL_State;
TbBOOLEAN               VbSiemens_StartCommReceived;
TbBOOLEAN               VbSiemens_StopCommReceived;

  //uint16_t  Level2SecurityTimer_Temp;
uint16_t L2SecurityTmrCoefficient;
/* ========================================================================== *\
 * Local Macro definitions
\* ========================================================================== */
#define SINGLEAUTHENMAXTIME_TIMES2         ( K_SingleAuthenticationMaxTime * 2 )
#define Delay2ms          FixDefConst(2000.0, MicroSec_HighRes_Type)
#define Delay4ms          FixDefConst(4000.0, MicroSec_HighRes_Type)
/*for Siemens immo */
/* Time counter for CeIMMO_SendingRequestMsg state. 7.8125ms per count */
static Every_Loop_Sec_B SyIMMO_SendReqMsgTimeCntr;
/*for Siemens immo */
/* Time counter for CeIMMO_WaitICUResponse state. 7.8125ms per count */
static Every_Loop_Sec_B     SyIMMO_SingleAuthCntr;

/* ========================================================================== *\
 * Local funcs declaration
\* ========================================================================== */
//void Authentication_Service(void);
//void AuthenticationResult_Service(void);
//void ImmoLearnFromECM_Service(void);
//void ECMLearnFromImmo_Service(void);
//static void CheckImmoKLineStatus(void);
//static void BuildAuthenticaionRequest(void);
//static void BuildAuthenticaionResultRequest(void);
//static void SendKW2000Request(void);
//static void GoToFeedbackAuthenticationState(void);
//static void Authentication_OverTime(void);
//static void AuthenticationResult_OverTime(void);
//static void LostCommunicationService(void);

/*for Siemens Immo*/
//static void CntrlIMMO_WaitTinitime(void);
/*for Siemens Immo*/
static void CntrlIMMO_PrepareResponseMessage(void);
/*for Siemens Immo*/
static void DtrmnIMMO_BuildKW2000Response(void);
/*for Siemens Immo*/
static void CntrlIMMO_SendingResponseMsg(void);
/*for Siemens Immo*/
static TbBOOLEAN CheckIMMO_ReqIsSentOut(void);
/*for Siemens Immo*/
static void CntrlIMMO_InitSCIRcvStatus(void);
/*for Siemens Immo*/
static void CntrlIMMO_WaitICURequest(void);
/*for Siemens Immo*/
static TbBOOLEAN CheckIMMO_GotICURequest(void);
/*for Siemens Immo*/
static void CheckIMMO_SingleAuthOvertime(void);
/*for Siemens Immo*/
static void DtrmnIMMO_LostCommService(void);
/*for Siemens Immo*/
static void DtrmnIMMO_ReAuthentication(void);
/*for Siemens Immo*/
static void DtrmnIMMO_ReAcknowldge(void);

/*
const KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE CaMasterServiceDefinition[ ]=
{
   //SID A0
    { Authentication,
      Authentication_Service
    },
   
   //SID A1
    { FeedbackAuthentication,
      AuthenticationResult_Service
    },
};
*/

/*
const KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE CaJiChengImmoServiceDefinition[]=
{
   // SID A0
    {  Authentication,
       Authentication_Service
    },
   // SID A1
    {  FeedbackAuthentication,
       AuthenticationResult_Service
    },
   //SID A2
    {  ECMLearnFromImmo,
       ECMLearnFromImmo_Service
    },
   //SID A3
    {  ImmoLearnFromECM,
       ImmoLearnFromECM_Service
    },
};
*/
/*
 * This constant defines the size of the supported service table
 * length. This size is calculated at compile time and is used
 * by the Update Service routine in file immo_exec1.c to search the service
 * table.
 */
/*
const uint8_t  CyKW2MASTERMaxServiceDefTableEntrys  =
                         ( sizeof(CaMasterServiceDefinition) /
                           sizeof(KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE) );    

const uint8_t  CyKW2JiChengImmoMaxServiceDefTableEntrys =
                         ( sizeof(CaJiChengImmoServiceDefinition) /
                           sizeof(KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE) );
 */

const T_COUNT_WORD    CaSiemens_L2WrongAttemptDelay[10] = {1, 1, 60, 120, 240, 480,960, 1920, 3840, 7680};// 10s/count

/*****************************************************************************
 *
 * Function:           CheckImmoKLineStatus
 * Description:        Check whether the K-Line is disconnected
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/

/*
static void CheckImmoKLineStatus(void)
{
  if ( ((FastPitLoopCounter - ImmoChallengeStartTime) > SINGLEAUTHENMAXTIME_TIMES2) &&
       ((AuthenticationCounter == 0) &&
        (Authentication == ECMImmoRelation) ))
   {
      Immo_KLineDisconnected = true;
      ImmoNoResponseDetected = true;
      ImmoAuthenErrorDetected = false;
      ImmoStatusByte.Bits.EcmImmoCommError = (bitfield8_t)true;
      ImmoServiceState = Immo_End;
      ImmoEndService();
   }
   else
   {
      // do nothing 
   }
    
}
*/

/*****************************************************************************
 *
 * Function:           BuildAuthenticaionRequest
 * Description:        Generate radom data.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
  /*
static void BuildAuthenticaionRequest(void)
{

   if(Chk_GenericImmo_Enabled())
   {
      uint8_t ByteIndex, *byte_prt;
      U16 *F_Result_temp, *G_Result_temp;
      uint32_t *word_prt;
		
      TxServiceData[0]=CalculateChecksum((uint8_t*) 0x3FA0, (BYTE*) 0x3FB7)\
			                     +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0050)\
			                               +(BYTE)ATD0_buffer[AD_IGNITION];
      TxServiceData[1]=CalculateChecksum((uint8_t*) 0x3FB8, (BYTE*) 0x3FCF)\
			                     +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0060)\
			                               +(BYTE)ATD0_buffer[AD_MAPSLOW];
      TxServiceData[2]=CalculateChecksum((uint8_t*) 0x3FD0, (BYTE*) 0x3FE7)\
			                     +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0070);
      TxServiceData[3]=CalculateChecksum((uint8_t*) 0x3FE8, (BYTE*) 0x3FFF)\
			                     +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0080);

      mini_crypt(*((uint32_t *) (TxServiceData)), Immo_SK_H.Word, Immo_SK_L.LongWord, &F_Result, &G_Result);
		
      TxServiceData[4]=(uint8_t) (F_Result>>8);
      TxServiceData[5]=(uint8_t) (F_Result);
		
      ECMKEY[0]=(uint8_t) (G_Result>>8);
      ECMKEY[1]=(uint8_t) (G_Result);

      Authentication_Request_ID = Authentication_Rqst;
   }
   if(Chk_JiChengImmo_Enabled())
   {
      BYTE ByteIndex;
      ECMSeed[0]=CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0090);
      ECMSeed[1]=CalculateChecksum((uint8_t*) 0x3FA0, (BYTE*) 0x3FB7)\
			               +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0050)\
			                         +(BYTE)ATD0_buffer[AD_IGNITION];
      ECMSeed[2]=CalculateChecksum((uint8_t*) 0x3FB8, (BYTE*) 0x3FCF)\
			               +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0060)\
			                        +(BYTE)ATD0_buffer[AD_MAPSLOW];
      ECMSeed[3]=CalculateChecksum((uint8_t*) 0x3FD0, (BYTE*) 0x3FE7)\
                                       +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0070);
      ECMSeed[4]=CalculateChecksum((uint8_t*) 0x3FE8, (BYTE*) 0x3FFF)\
                                       +CalculateChecksum((BYTE*) 0x0020, (BYTE*) 0x0080);

      TxServiceData[0]=A0_Request_ID;
      TxServiceData[1]=ECMSeed[0];
      TxServiceData[2]=ECMSeed[1];
      TxServiceData[3]=ECMSeed[2];
      TxServiceData[4]=ECMSeed[3];
      TxServiceData[5]=ECMSeed[4];
		
   }
   
}*//*** End of BuildAuthenticaionRequest ***/

/*****************************************************************************
 *
 * Function:           BuildAuthenticaionResultRequest
 * Description:        Generate authentication result frame.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
static void BuildAuthenticaionResultRequest(void)
{

   if(Chk_GenericImmo_Enabled())
   {
      if (ImmoAuthenticationResultPass()) 
      {
         TxServiceData[0]=0x73;
      }
      else
      {
         TxServiceData[0]=0xC5;	   
      }
      Authentication_Request_ID = FeedBackResult_Rqst;
   }
   else if(Chk_JiChengImmo_Enabled())
   {
      TxServiceData[0]=A1_Request_ID;
      if (ImmoAuthenticationResultPass())
      {
         TxServiceData[1]=AuthorizationSuccess; 
      }
      else
      {
         TxServiceData[1]=AuthorizationFail; 	
      }
   }
  
}
 */
/*****************************************************************************
 *
 * Function:           SendKW2000Request
 * Description:        Form request message.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
static void SendKW2000Request(void)
{       
   BYTE RqstLength;
   BOOLEAN RqstFlag=TRUE;

   // Prepare Request message. 	
   switch(ECMImmoRelation)
   {	
      case Authentication:
           BuildAuthenticaionRequest();
           RqstLength = AuthenticationMessageLength;
           break;
      case FeedbackAuthentication:
           BuildAuthenticaionResultRequest();
           if(Chk_GenericImmo_Enabled())
           {
              RqstLength=FeedbackAuthenMessageLength_Generic;

           }
           else if(Chk_JiChengImmo_Enabled())
           {
              RqstLength=FeedbackAuthenMessageLength_JiCheng;
           }
           break;  
      case ECMLearnFromImmo:
           RqstLength=ECMLearnFromImmoMessageLength;
           TxServiceData[0]=A2_Request_ID;
           break;
      case ImmoLearnFromECM:
           RqstLength=LearnFromECMMessageLength;
           TxServiceData[0]=A3_Request_ID;
           TxServiceData[1]=EE_PIN[0];
           TxServiceData[2]=EE_PIN[1];   		
           break;
      default:
           RqstFlag =FALSE;
           GoToEndTesterState();
           break;
   }
   

   if(Chk_JiChengImmo_Enabled())
   {
      // Activate JiCheng Immobilizer Request Pin.  	 
      DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, TRUE);
      Delay(Delay2ms);
      DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, FALSE);
      // Delay Tdelay(3ms-6ms). 
      Delay(Delay4ms);
   }


   if (RqstFlag == TRUE)
   {
      //began to send data, clear the single authentication counter
      SingleAuthenCounter=0;
      P3MinTimer=P3MinWL+1;
      P4Timout=P4MinWL+1;
      BuildKw2000Request(RqstLength);
   }
}*//***SendKW2000Request ***/

/*****************************************************************************
 *
 * Function:           GoToAuthenticationState
 * Description:        Goto authentication state.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
FAR_COS void GoToAuthenticationState(void)
{
   ECMImmoRelation=Authentication;
   GoToWaitingInitializingOrP3MinState();
	 
} *//*** End of GoToAuthenticationState ***/

/*****************************************************************************
 *
 * Function:           GoToFeedbackAuthenticationState
 * Description:        Goto FeedbackAuthentication state.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
static void GoToFeedbackAuthenticationState(void)
{
   ECMImmoRelation=FeedbackAuthentication;
   GoToWaitingInitializingOrP3MinState();
}*/ /*** End of GoToAuthenticationState ***/

/*****************************************************************************
 *
 * Function:           GoToEndTesterState
 * Description:        Goto EndTester state.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
FAR_COS void GoToEndTesterState(void)
{
   AuthenticationCounter=0;
   FeedbackAuthCounter=0;
   ValidAuthRspCounter=0;
   SingleAuthenCounter=0;
   TotalAuthenticationCounter=0;
   ECMImmoRelation=EndAuthentication;
   ImmoServiceState = Immo_End;

} *//*** End of GoToAuthenticationState ***/


/*****************************************************************************
 *
 * Function:           Authentication_OverTime
 * Description:        Handle authorization service overtime operation:
 *                         If ECM does not receive postive response after sending out A0 request,
 *                         Authentication_OverTime is called to re-direct work flow.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
static void Authentication_OverTime(void)
{
   if ( ((AuthenticationCounter<K_MaxAuthenTimes) &&
         (ValidAuthRspCounter<K_MaxValidAuthenTimes)) ||
        ((K_MaxAuthenTimes==AuthenticationCounter) &&
         (1==ValidAuthRspCounter)) )
   {
      GoToAuthenticationState();
   }
   else 
   {
      // Save Erro code and Go to ImmoEndService in next loop. 
      GoToFeedbackAuthenticationState();
   }

}*//*** End of Authentication_OverTime ***/

/*****************************************************************************
 *
 * Function:           AuthenticationResult_OverTime
 * Description:        Handle Feed back authorization result service overtime operation.
 *                         If ECM does not receive postive response after sending out A1 request,
 *                         AuthenticationResult_OverTime is called to re-direct work flow.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*static void AuthenticationResult_OverTime(void)
{
   // ECM will send Ack request 3 or 5 times. 
   if (FeedbackAuthCounter<K_MaxFeedbackAuthenTimes)
   {
      // Try again. 
      GoToFeedbackAuthenticationState();
   }
   else
   {
      // Save Erro code and Go to ImmoEndService in next loop. 
      GoToEndTesterState();
   }
}*//*** End of AuthenticationResult_OverTime ***/



/*****************************************************************************
 *
 * Function:           ImmoEndService
 * Description:        Handle exit service to end immo communication.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
FAR_COS void ImmoEndService(void)
{
   /* Change ECM from KW2000 tester to KW2000 responder. */
   ECMImmoRelation=NO_Relation;
   VeSiemens_ECMImmoRelation=CeSiemens_NoRelation;
   /* For normal KW2000 slave service, initialize KW2000. */
   KW2000CommuState=KW2000_Responder;

   if(GetMultiRespInProgress())
   {
      /* For matching process, back to waitingmessage state to send response. */
      SetTimingParameterToDefault ();
      GoToAwaitingMessageK2State (TRUE);
   }
   else
   {
      if (GetImmoAuthenticationResult())  
      {
         ImmoEnableEngine();
         if (GetDGDM_DTC_FaultType (CeDGDM_ImmoNoResponse) != CeDGDM_FAULT_TYPE_Z)
         {
            PerfmDGDM_ProcessPassReport(CeDGDM_ImmoNoResponse);
         }
         if (GetDGDM_DTC_FaultType (CeDGDM_ImmoAuthenError) != CeDGDM_FAULT_TYPE_Z)
         {
            PerfmDGDM_ProcessPassReport(CeDGDM_ImmoAuthenError);
         }
      }
      else
      {
         if ((!ImmoPassThisKeyon )||
	       ((!GetDGDM_FaultActive(CeDGDM_VSS_NoSignal) &&(EOBD_VehSpd <= K_ImmoByPassVSS)) || 
	         ((!GetEngineTurning()) &&(GetDGDM_FaultActive(CeDGDM_VSS_NoSignal)))))
	      
	 {
	    ImmoDisableEngine();
	 }
			  
	 if (ImmoAuthenErrorDetected)
	 {
	    if(GetDGDM_DTC_FaultType (CeDGDM_ImmoAuthenError) != CeDGDM_FAULT_TYPE_Z)
	    {
	        PerfmDGDM_ProcessFailReport(CeDGDM_ImmoAuthenError);
	    }
	    if (GetDGDM_DTC_FaultType (CeDGDM_ImmoNoResponse) != CeDGDM_FAULT_TYPE_Z)
	    {
		PerfmDGDM_ProcessPassReport(CeDGDM_ImmoNoResponse);
	    }
	 }
	 else if (ImmoNoResponseDetected &&
		  GetDGDM_DTC_FaultType (CeDGDM_ImmoNoResponse) != CeDGDM_FAULT_TYPE_Z)
	 {
	    PerfmDGDM_ProcessFailReport(CeDGDM_ImmoNoResponse);
	 }
	 else
	 {
	    /* do nothing */
	 }
      }
      KeywordExecutive( CwKW2000_Initializes ) ;
      L2_WrongAttemptTry=0;
   }

}/*** End of ImmoEndService ***/


/*****************************************************************************
 *
 * Function:           LostCommunicationService
 * Description:        Handle lost communication error.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
static void LostCommunicationService(void)
{
   Immo_Erro_Code=SingleAuthen_OverTime;

   if (ECMImmoRelation==Authentication) 
   {
      Authentication_OverTime();
   }
   else if (ECMImmoRelation==FeedbackAuthentication) 
   {
      AuthenticationResult_OverTime();
   }
   else
   {
      /* Save Erro code and Go to ImmoEndService in next loop. 
      GoToEndTesterState();
   }
	
}*//*** End of LostCommunicationService ***/


/*****************************************************************************
 *
 * Function:           Authentication_Service
 * Description:        Handle authorization operation between ECM and immobilizer.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
void Authentication_Service(void)
{
   uint8_t counter;
   Immo_Resp_T A0Status;

   //end of single authentication,so clear the counter
   SingleAuthenCounter=0;
   
   // Calculate KEY during waiting response. 
   CalculateAuthenticationKey();

   if(Chk_GenericImmo_Enabled())
   {
      ValidAuthRspCounter++;
	   
      ClearImmoResponseFlag();
      ImmoStatusByte.Bits.EcmImmoCommError = (bitfield8_t)false;
      if ((Authentication_PostiveRespLength== GetKeyword2000ServiceDataLength ())
	  &&(GetKw2000ServiceData(0)==ECMKEY[0])
	  &&(GetKw2000ServiceData(1)==ECMKEY[1]))
      {
	 // If it is postive response, check it. 
	 A0Status=PostiveResp;
	 Immo_Erro_Code=NO_IMMO_ERROR;
      }
      else
      {
	 // If it is negative, record the error 
	 A0Status= NegativeResp;
	 Immo_Erro_Code=NG_ImmoResponse;
      }
	   
      switch (A0Status)
      {
         case PostiveResp:
              SetImmoAuthenticationResult(CbTRUE);
              ImmoPassThisKeyon = true; 
              ImmoAuthenErrorDetected = false;
              ImmoStatusByte.Bits.ImmoWrongKeyUsed = (bitfield8_t)false;
              GoToFeedbackAuthenticationState();
              break;	
							
         case NegativeResp:
         default:
              ImmoAuthenErrorDetected = true;
              ImmoStatusByte.Bits.ImmoWrongKeyUsed = (bitfield8_t)true;
              Authentication_OverTime();
              break;
      }	   

   }
   else if(Chk_JiChengImmo_Enabled())
   {
      ValidAuthRspCounter++;
		  
      ClearImmoResponseFlag();
      ImmoStatusByte.Bits.EcmImmoCommError = (bitfield8_t)false;
      if ((A0_PostiveRespID==GetKw2000ServiceData(A0_PostiveRespID_Offset))&&
          (A0_PostiveRespLength== GetKeyword2000ServiceDataLength ()))
      {
         // If it is postive response, check it. 
         A0Status=PostiveResp;
         Immo_Erro_Code=NO_IMMO_ERROR;		
         for (counter=0;counter<JiChengImmoKey_Length;counter++)
         {
            if (GetKw2000ServiceData(A0_PostiveResp_Code_Offset+counter)
                !=ECMKEY[counter])
            {
               A0Status=NegativeResp;
               Immo_Erro_Code=nrcProgrammingUnsuccess; 			
               break;
            }
         }
         if ((SKPIN_LearnMode==0x0A)&&(PostiveResp==A0Status))
         {
            counter=ECMLearned;
            EEPROMWrite(&counter, &EE_Learnt_Flag,1);
         }
         if ((SKPIN_LearnMode==0x0B)&&(PostiveResp==A0Status))
         {
            // If ECM learn SK from Immo, save SK into EEPROM only authorizaion pass. 	
            EEPROMWrite(Immo_SK,EE_SK,5);
            if (!SKWriteSuccess())
            {
               A0Status=NegativeResp;
               Immo_Erro_Code=nrcProgrammingUnsuccess; 	
            }
         }		
      }
      else if ((NegativeResponse==GetKw2000ServiceData(NegativeID_Offset))&&
               (A0_NegativeRespLength ==GetKeyword2000ServiceDataLength ())&&
               (A0_Request_ID==GetKw2000ServiceData(A0_NegativeRespID_Offset)))
      {
         // If it is negative, record the error 
         Immo_Erro_Code=GetKw2000ServiceData(A0_NegativeResp_Code_Offset);
         if (Immo_Erro_Code==nrcRequestCorrectlyReceived_ResponsePending)  
         {
            A0Status=PendingResp;
         }
         else
         {
            A0Status= NegativeResp;
         }
      }
      else
      {
         // other conditions 
         A0Status= WrongResp;
         Immo_Erro_Code=nrcNoImmoResponse;
      }
	   
      switch (A0Status)
      {
         case PostiveResp:
              SetImmoAuthenticationResult(CbTRUE);
              ImmoAuthenErrorDetected=false;
              ImmoStatusByte.Bits.ImmoWrongKeyUsed = (bitfield8_t)false;
              GoToFeedbackAuthenticationState();
              ImmoEnableEngine();
              break;
			
         case PendingResp:
              Kw2000State=k2sAwaitingMessage;
			
              P2MaxWL=P3MaxWL;
              P2MinTimer=0;
              P3MinTimer=0;
              break;
			
         case NegativeResp:
         case WrongResp: 		
         default:			
              ImmoAuthenErrorDetected = true;
              ImmoStatusByte.Bits.ImmoWrongKeyUsed = (bitfield8_t)true;
              Authentication_OverTime();
              break;				
      }		   

   }
}*//*** End of Authentication_Service ***/

/*****************************************************************************
 *
 * Function:           AuthenticationResult_Service
 * Description:        Handle feedback authorization result operation between ECM and immobilizer.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
void AuthenticationResult_Service(void)
{
   uint8_t counter;
   Immo_Resp_T A1Status;

   //clear the single authentication counter
   SingleAuthenCounter=0;
   
   if(Chk_GenericImmo_Enabled())
   {
      ClearImmoResponseFlag();
      ImmoStatusByte.Bits.EcmImmoCommError = (bitfield8_t)false;
      // If the length is not right, the response is wrong response. 
      if (  (((AuthenticationResult_PostiveRespID==GetKw2000ServiceData(0))&&(ImmoAuthenticationResultPass())) ||
             ((AuthenticationResult_NegativeRespID==GetKw2000ServiceData(0))&&(ImmoAuthenticationResultFail() )))
		   &&(AuthenticationResult_PostiveRespLength== GetKeyword2000ServiceDataLength()))
      {
         // If it is postive response, check it. 
         A1Status=PostiveResp;
         Immo_Erro_Code=NO_IMMO_ERROR;
			
         if ( AuthenticationResult_NegativeRespID == GetKw2000ServiceData(0) )
         {
            ImmoAuthenErrorDetected = true;
            ImmoStatusByte.Bits.ImmoWrongKeyUsed = (bitfield8_t)true;
         }
	   
      }
      else
      {
         // other conditions 
         A1Status= NegativeResp;
         Immo_Erro_Code=NG_ImmoResponse;
      }
	   
      switch (A1Status)
      {
         case PostiveResp:
              GoToEndTesterState();
              break;
			
         case NegativeResp:
         default:
              AuthenticationResult_OverTime();
              break;
      }

   }
   else if(Chk_JiChengImmo_Enabled())
   {
      ClearImmoResponseFlag();
      ImmoStatusByte.Bits.EcmImmoCommError = (bitfield8_t)false;
      // If the length is not right, the response is wrong response. 
      if ((A1_PostiveRespID==GetKw2000ServiceData(A1_PostiveRespID_Offset))
          &&(A1_PostiveRespLength== GetKeyword2000ServiceDataLength () ))
      {
         // If it is postive response, check it. 
         A1Status=PostiveResp;
         Immo_Erro_Code=NO_IMMO_ERROR;
      }
      else if ((NegativeResponse==GetKw2000ServiceData(NegativeID_Offset)) 
             &&(A1_NegativeRespLength ==GetKeyword2000ServiceDataLength () )
             &&(A1_Request_ID==GetKw2000ServiceData(A1_NegativeRespID_Offset)))
      {
         // If it is negative, record the error 
         A1Status= NegativeResp;
         Immo_Erro_Code=GetKw2000ServiceData(A1_NegativeResp_Code_Offset);
         ImmoAuthenErrorDetected = true;
         ImmoStatusByte.Bits.ImmoWrongKeyUsed = (bitfield8_t)true;

      }
      else
      {
         // other conditions 
         A1Status= WrongResp;
         ImmoAuthenErrorDetected = true;
         ImmoStatusByte.Bits.ImmoWrongKeyUsed = (bitfield8_t)true;
		
      }
	   
      switch (A1Status)
      {
         case PostiveResp:
              GoToEndTesterState();
              break;			
         default:
              AuthenticationResult_OverTime();
              break;				
      }

   }
}*//*** End of AuthenticationResult_Service ***/

/*****************************************************************************
 *
 * Function:           ECMLearnFromImmo_Service
 * Description:       Handle ECM learning from Immobilizer operation.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
/*
void ECMLearnFromImmo_Service(void)
{
   BYTE counter;
   BYTE *sourceaddress, *targetaddress;
   Immo_Resp_T A2Status;

   // If the length is not right, the response is wrong response. 
   if ((A2_PostiveRespID==GetKw2000ServiceData(A2_PostiveRespID_Offset))
     &&(A2_PostiveRespLength== GetKeyword2000ServiceDataLength ()))
   {
      // If it is postive response, check it. 
      if ((Immo_PIN[0]!=GetKw2000ServiceData(6))||(Immo_PIN[1]!=GetKw2000ServiceData(7)))  
      {
         A2Status=NegativeResp;
         Immo_Erro_Code=nrcPINCodeNotCorrect;
         ReadImmoEEPROMData();
         PINProtectService();
      }
      else
      {
         A2Status=PostiveResp;
         Immo_Erro_Code=NO_IMMO_ERROR;
        	
         ReadImmoEEPROMData();
         // Clear PINWrongAttemptCounter. 
         ImmoEEPROMStatus[PINProtectFlagIdx]=PINUnProtected;
         // Unprotect PIN. 
         ImmoEEPROMStatus[PINWrongAttemptCounterIdx]=0;
         UpdateImmoEEPROMData();

         sourceaddress=&(GetKw2000ServiceData(1));
         targetaddress=EE_SK;
         EEPROMWrite(sourceaddress, targetaddress, SK_Length_JiCheng);

         sourceaddress=&(GetKw2000ServiceData(6));
         targetaddress=EE_PIN;
         EEPROMWrite(sourceaddress, targetaddress, PIN_Length_JiCheng);

         for (counter=0;counter<SK_Length_JiCheng;counter++)
         {  
            Immo_SK[counter]=GetKw2000ServiceData(1+counter);
         }

         if ((!SKWriteSuccess())||(!PINWriteSuccess()))
         {
            A2Status=NegativeResp;
            Immo_Erro_Code=nrcProgrammingUnsuccess;
         }
      }
   }
   else if ((NegativeResponse==GetKw2000ServiceData(NegativeID_Offset)) 
          &&(A2_NegativeRespLength ==GetKeyword2000ServiceDataLength () )
          &&(A2_Request_ID==GetKw2000ServiceData(A2_NegativeRespID_Offset)))
   {
      // If it is negative, record the error 
      A2Status= NegativeResp;
      Immo_Erro_Code=GetKw2000ServiceData(A2_PostiveResp_Code_Offset);
   }
   else
   {
      // other conditions 
      A2Status= WrongResp;
      Immo_Erro_Code=nrcNoImmoResponse;
   }

   switch (A2Status)
   {
      case PostiveResp:
           GoToAuthenticationState();
           break;
      default:
           GoToEndTesterState();
           break;  			
   }   
}*/

/*****************************************************************************
 *
 * Function:           ImmoLearnFromECM_Service
 * Description:       Handle Immobilizer learning from ECM operation.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
/*
void ImmoLearnFromECM_Service(void)
{
   BYTE counter;
   Immo_Resp_T A3Status;

   
   // If the length is not right, the response is wrong response. 
   if ((A3_PostiveRespID==GetKw2000ServiceData(A3_PostiveRespID_Offset))
   	&&(A3_PostiveRespLength== GetKeyword2000ServiceDataLength ()))
    {
   	// If it is postive response, check it. 
   	A3Status=PostiveResp;
   	Immo_Erro_Code=NO_IMMO_ERROR;
   	Immo_SK[0]=GetKw2000ServiceData(1);
   	Immo_SK[1]=GetKw2000ServiceData(2);
   	Immo_SK[2]=GetKw2000ServiceData(3);
   	Immo_SK[3]=GetKw2000ServiceData(4);
   	Immo_SK[4]=GetKw2000ServiceData(5);
    }
   else if ((NegativeResponse==GetKw2000ServiceData(NegativeID_Offset)) 
   	&& (A3_NegativeRespLength ==GetKeyword2000ServiceDataLength () )
   	&&(A3_Request_ID==GetKw2000ServiceData(A3_NegativeRespID_Offset)))
    {
   	// If it is negative, record the error 
   	A3Status= NegativeResp;
   	Immo_Erro_Code=GetKw2000ServiceData(A3_NegativeResp_Code_Offset);
    }
   else
    {
   	 // other conditions 
   	A3Status= WrongResp;
   	Immo_Erro_Code=nrcNoImmoResponse;
    }

   switch (A3Status)
    {
        case PostiveResp:
             GoToAuthenticationState();
             break;
        default:
             GoToEndTesterState();
             break;  			
    }   
}*/

/*****************************************************************************
 *
 * Function:           ImmoTester_Initialize
 * Description:        Initialize ECM to act as master of KW2000.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
FAR_COS void ImmoTester_Initialize(void)
{
   if(Chk_JiChengImmo_Enabled())
   {
      //Initialize KW2000. 
      SCIReceiverReset ();
      SetECUResetPending( FALSE ) ;
      SetTimingParameterToDefault ();
      GoToAwaitingMessageK2State (TRUE);
      SendKW2000Request();
   }
   else if(Chk_GenericImmo_Enabled())
   {
      // Initialize KW2000. 
      SCIReceiverReset ();
      SetECUResetPending( FALSE ) ;
      SetTimingParameterToDefault ();
      GoToAwaitingMessageK2State (TRUE);
      SendKW2000Request();
   }

}*//*** End of ImmoTester_Initialize ***/


/*****************************************************************************
 *
 * Function:           Update_IMMO_DLL_Service
 * Description:        change KW2000 service state.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
FAR_COS void Update_IMMO_DLL_Service(void) 
{
/*
   if ((Chk_GenericImmo_Enabled()) ||(Chk_JiChengImmo_Enabled()))
   {
   KW2000CommuState=KW2000_Tester;
		
   switch(Kw2000State)
   {
      case k2sWaitingInitializing:
           // Initialize communication after power on 200ms. 
           ImmoTester_Initialize();
           break;
		 
      case k2sSendingMessage:
           //--- the state machine is run on interrupt level ---
           break; 	 
		 
      case k2sReceivingMessage:
           // Check and transfer data from RX-buffer to serivce section. 
           ReceivingMessageKw2000State();
           break;
	 
      case k2sWaitingP3MinBeforeSend:
           // Waiting untill P3min OK. 
           WaitingP3MinBeforeSendRequest();
           break;
		 
      case k2sWaitingP4MinBeforeSend:
           // Waiting untill P4min OK. 
           WaitingP4MinBeforeSendRequest();
           break;
	
      case k2sLostCommunication:
           // Communication lost service. 
           LostCommunicationService();
           break;
	
      case k2sAwaitingMessage:
      case k2sErrorRead:
      default:	 
           // Waiting for Message from responder. 
           GoToAwaitingMessageK2State (TRUE);
           break;
   }

   if(Chk_JiChengImmo_Enabled())
   {
      // If Authorization time exceed Tauthen, time out. 
      CheckTotalAuthorizationTime();
   }
   if(Chk_GenericImmo_Enabled())
   {
      CheckImmoKLineStatus();
   }
   // If Tidle time out. 
   CheckSingleAuthenticationTime();
   	}
   else*/
   	if (Chk_SiemensImmo_Enabled())
   	{
   	  //TBD: if the belowing is added.
          //KW2000CommuState=KW2000_Responder;
        
         switch (VeSiemens_DLL_State)
         {
           case CeIMMO_WaitTiniTime:
           {
             //CntrlIMMO_WaitTinitime();
             break;
           }
           case CeIMMO_SendingWup:
           {
		   	
             CntrlIMMO_PrepareResponseMessage();
             break;
           }
           case CeIMMO_SendingResponseMsg:
           {
             CntrlIMMO_SendingResponseMsg ();
             break;
           }
           case CeIMMO_WaitICURequest:
           {
             CntrlIMMO_WaitICURequest();
             break;
           }
           case CeIMMO_IdleState:
           {
             break;
           }
           default:
           {
             break;
           }
          }
          CheckIMMO_SingleAuthOvertime();
   	}
}

/* for Siemens Immo*/
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_WaitTinitime                                  *
* Description:       Wait Tini time elasped                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
#if 0
static void CntrlIMMO_WaitTinitime(void)
{
  if (PowerUpDelayTiniCntr)
  {
    PowerUpDelayTiniCntr--;
  }
  else
  {
    SetSiemens_DLLStateToSendingWup ();
  }
}
/* for Siemens Immo */
	#endif
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_PrepareRequestMessage                                  *
* Description:       Immo Prepare request message                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_PrepareResponseMessage(void)
{
  
  /*----- build frame and trigger sending  ----*/
  DtrmnIMMO_BuildKW2000Response();
  /* Siemens: P2Max Timer */
  SyIMMO_SendReqMsgTimeCntr = 0;
//  Kw2000State=k2sSendingMessage;/* this is for test generateing response with random, but it is not correct*/
  
  SetSiemens_DLLStateToSendingResponseMsg ();
  
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          DtrmnIMMO_BuildKW2000Request                                  *
* Description:       Immo Prepare request message                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void DtrmnIMMO_BuildKW2000Response(void)
{
  /* Prepare Request message. */	
  switch(VeSiemens_ECMImmoRelation)
  {
    case CeSiemens_Authentication:
    {
      SiemensImmo_BldChallengeRspMsgFrame();
   	  break;
    }
   	case CeSiemens_FeedbackAuthentication:
   	{
         SiemensImmo_BldCodeRspMsgFrame();
   	  break;
   	}
    case CeSiemens_StartCommunication:
    case CeSiemens_StopCommunication:
    {
      break;
    }
    case CeSiemens_NoRelation:
    case CeSiemens_EndAuthentication:

   	default:
   	{
      GoToEndResponderState();
   	  break;
   	}
  }
}
/* For Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_SendingResponseMsg                             *
* Description:       Waiting for response being sent out.                    *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_SendingResponseMsg(void)
{

    /* Siemens IMMO use SendStandardNegativeAnswer() and SendStandardPositiveAnswer()
     in standard KW commuication, so here we have to run the KW DLL machine to update
     P2 timer logic before go to sending message */

    UpdateKeyword2000VIO();


  if (CheckIMMO_ReqIsSentOut() )
  {
    /* directly set KW state to KW2000_STATE_RECEIVING_MESSAGE
       skip any initialization phase, prepare for receiving Response */
       
    CntrlIMMO_InitSCIRcvStatus();   

    SyIMMO_SingleAuthCntr = 0;

    SetSiemens_DLLStateToWaitICURequest ();

      /* A round of ICU-ECU communication has finished here.
         Run state machine actively. */
      switch(VeSiemens_ECMImmoRelation)
      {
        case CeSiemens_Authentication:
        {
          /* Go to Immo Code service loop */
          VeSiemens_ECMImmoRelation = CeSiemens_FeedbackAuthentication;    
          break;
        }
        case CeSiemens_FeedbackAuthentication:
        {
          if(ImmoAuthenticationResultPass())
          {
            /* Authentication success, go to stop communication status
               wait immo to send stop communication request*/
            VeSiemens_ECMImmoRelation = CeSiemens_StopCommunication; 
          }
          else 
          {
            /* Redirect workflow to wait IMMO to send a new round 
               challenge request until pre-release time elapsed. */
            VeSiemens_ECMImmoRelation = CeSiemens_Authentication;
          }
          break;
        }
        case CeSiemens_NoRelation:
        case CeSiemens_StartCommunication: /* handled below */
        case CeSiemens_StopCommunication: /* handled below */
        case CeSiemens_EndAuthentication:

        default:
        {
          break;
        }
      }
      
      if(VbSiemens_StartCommReceived)
      {
        /* In case IMMO send start communication request out of state 
           machine transition control. Go to authentication state. */
        VeSiemens_ECMImmoRelation = CeSiemens_Authentication;
        VbSiemens_StartCommReceived = CbFALSE;
	
      }
      else if(VbSiemens_StopCommReceived)
      {
        /* In case IMMO send stop communication request out of state 
           machine transition control. End immediately. */
        GoToEndResponderState();        
        VbSiemens_StopCommReceived = CbFALSE;
      }

  }
  else if (SyIMMO_SendReqMsgTimeCntr >= (K_SingleAuthenticationMaxTime * 2) )
  {
    VeSiemens_ActReason = CeIMMO_ECURespTimeOut;
    /* Siemens:   P2Max Timer (slave) expired */

      /* Failed to send message within P2Max. Redirect DLL state machine to wait 
         ICU's new round of challenge instead of ending up authentication */
      SetSiemens_DLLStateToWaitICURequest();

  }
  else
  {
    SyIMMO_SendReqMsgTimeCntr++;
  }   

}

/* for Siemens Immo */   //TBD:
/*****************************************************************************
 *
 * Function:           GotoEndTesterState
 * Description:        Goto EndResponder state.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
FAR_COS void GoToEndResponderState (void)
{
  SyIMMO_SingleAuthCntr = 0;
  VeSiemens_ECMImmoRelation = CeSiemens_EndAuthentication;
  SetSiemens_DLLStateToIdleState(); 
} /*** End of GotoEndResponderState ***/

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CheckIMMO_ReqIsSentOut                                  *
* Description:       This procedure will determine if the request message is *
*                    currently being sent.                                   *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            CbTRUE: request message has been sent                   *
*                    CbFALSE: request message is still being sent            *
*                                                                            *
*****************************************************************************/
static TbBOOLEAN CheckIMMO_ReqIsSentOut (void)
{
  TbBOOLEAN LbSentOut;

    /* Siemens IMMO use SendStandardNegativeAnswer() and SendStandardPositiveAnswer()
       in standard KW handler, so here we reuse the standard interface */
    if(Keyword2000AnswerStillBeingSent()  )
    {
      LbSentOut = CbFALSE;      
    }
    else
    {
      LbSentOut = CbTRUE;
    }
  return LbSentOut;
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_InitSCIRcvStatus                              *
* Description:       This procedure will set states to receiving data from   *
*                    ICU                                                     *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_InitSCIRcvStatus (void)
{
   GoToAwaitingMessageK2State (TRUE);
  /* Here we leaped over the Awaiting Message state,
     then P3Max could not be checked. */
  GoToReceivingMessageK2State ();
  ClearSCIRespReceivedFlag();
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CntrlIMMO_WaitICURequest                               *
* Description:       Wait response from ICU.                                 *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            none                                                    *
*                                                                            *
*****************************************************************************/
static void CntrlIMMO_WaitICURequest(void)
{
  /* Currently KW is in IMMO authentication state,KeywordMode is false. 
     The KW task is different with the one in MngOSTK_7p82msGenericTasks which
     is disabled now */
   UpdateKeyword2000VIO() ;


  if (CheckIMMO_GotICURequest())
  {
    /* Set the response receive flag which is to trigger APP Service Table */
    SetSCIRespReceivedFlag();
    SetSiemens_DLLStateToIdleState ();

  }
}

/* for Siemens Immo */
/*****************************************************************************
*                                                                            *
* Function:          CheckIMMO_GotICURequest                                *
* Description:       This procedure will determine if a message has been     *
*                    recieved from the ICU.                                  *
*                                                                            *
* Execution Rate:    7.81 ms                                                 *
*                                                                            *
* Parameters:        none                                                    *
* Return:            CbTRUE: Response recieved; CbFALSE: no response yet     *
*                                                                            *
*****************************************************************************/
static TbBOOLEAN CheckIMMO_GotICURequest(void)
{
  TbBOOLEAN LbGotResponse;
  LbGotResponse = CbFALSE;

  if(Chk_SiemensImmo_Enabled())
  {
    /* communication established, here dealing the app level services */
    if( Kw2000State == k2sWaitingAppLvlServiceExec)
    {
      LbGotResponse = CbTRUE;      
    }
  }

  if ( Kw2000State == k2sErrorRead )
  {
    /* received an error frame, try again. */
    CntrlIMMO_InitSCIRcvStatus();
  }

  return LbGotResponse;
}

/* for Siemens Immo */
/*****************************************************************************
 *
 * Function:           CheckIMMO_SingleAuthOvertime
 * Description:        Check Single Authentication Time
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
static void CheckIMMO_SingleAuthOvertime(void)
{
  if (CeIMMO_WaitICURequest== VeSiemens_DLL_State)
  {
    if (DtrmnIMMO_SingleAuthTimeOvertime(SyIMMO_SingleAuthCntr) )
    {
      SyIMMO_SingleAuthCntr = 0;
      DtrmnIMMO_LostCommService();
      //VbIMMO_RprtNoICUResponse = CbTRUE;
      ImmoNoResponseDetected = true;
    }
    else
    {
      SyIMMO_SingleAuthCntr++;
    }
  }
}

/* for Siemens immo*/
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_SingleAuthTimeOvertime
 *
 * Description:        Check if single authentication counter overflow
 *
 * Parameters:         authentication counter
 *
 * Return:             TRUE - counter overflow
 *                     FALSE - counter doesn't overflow
 *
 *****************************************************************************/
TbBOOLEAN DtrmnIMMO_SingleAuthTimeOvertime(Every_Loop_Sec_B counter)
{
  TbBOOLEAN result = CbFALSE;
 

  /* This will take care of the P3Max Timing check of Siemens */
  if(Chk_SiemensImmo_Enabled() ) 
  {
    if( (CeSiemens_FeedbackAuthentication == VeSiemens_ECMImmoRelation)
     && (counter >= K_SingleAuthenticationMaxTime * 4) )/*4*/
    {
      /* P3_la max timer (270ms). Waiting for immoCode request msg */
      result = CbTRUE;
    }
    else if( ( (CeSiemens_Authentication == VeSiemens_ECMImmoRelation) 
             || (CeSiemens_StopCommunication == VeSiemens_ECMImmoRelation) )
          && (counter >= K_SingleAuthenticationMaxTime) )/*Added /2 */
    {
      /* P3_lb max timer (60ms) */
      result = CbTRUE;
    }
    else if( (CeSiemens_StartCommunication== VeSiemens_ECMImmoRelation) 
          && (counter >= K_SingleAuthenticationMaxTime * 10) )/*10*/
    {
      /* max timer of waiting for start communication request (600ms) */
      result = CbTRUE;
    }
  }

  return result;
}

/* for Siemens immo */
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_LostCommService
 * Description:        Handle lost communication error.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
static void DtrmnIMMO_LostCommService(void)
{
  VeSiemens_ActReason = CeIMMO_ICURespTimeOut;

  switch(VeSiemens_ECMImmoRelation)
  {
    case CeSiemens_Authentication:
    {
      DtrmnIMMO_ReAuthentication();
   	  break;
    }
   	case CeSiemens_FeedbackAuthentication:
   	{
      DtrmnIMMO_ReAcknowldge();
   	  break;
   	}
    case CeSiemens_StartCommunication:
    case CeSiemens_StopCommunication:

      break;
    case CeSiemens_NoRelation:
    case CeSiemens_EndAuthentication:
    //case ECMLearnFromImmo:
    //case ImmoLearnFromECM:
   	default:
    {
      /* Save Erro code and Go to End Service in next loop. */
      ClearImmoAuthenticationResult();
   	  GoToEndResponderState();
   	  break;
   	}
  }
}

/*for Siemens Immo*/
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_ReAuthentication
 *
 * Description:        Handle authorization service overtime operation:
 *                     If ECM does not receive postive response after sending out A0 request,
 *                     DtrmnIMMO_ReAuthentication is called to re-direct work flow.
 *
 * Parameters:         None
 *
 * Return:             None
 *
 *****************************************************************************/
 static void DtrmnIMMO_ReAuthentication(void)
{

  if ( Chk_SiemensImmo_Enabled() )
  {
    SiemensImmo_P3MaxOvertime();
  }

}

/*for Siemens Immo*/
/*****************************************************************************
 *
 * Function:           DtrmnIMMO_ReAcknowldge
 *
 * Description:        Handle Feed back authorization result service overtime operation.
 *                     If ECM does not receive postive response after sending out A1 request,
 *                     DtrmnIMMO_ReAcknowldge is called to re-direct work flow.
 *
 * Parameters:         None
 *
 * Return:             None
 *
 *****************************************************************************/
static void DtrmnIMMO_ReAcknowldge(void)
{
  if ( Chk_SiemensImmo_Enabled() )
  {
    SiemensImmo_P3MaxOvertime();
  }
}

/**********************************************************************/
/***    Load the level 2 security timer                             ***/
/**********************************************************************/
FAR_COS void TriggerL2SecurityTiming (void)
{
/*
 if(Chk_GenericImmo_Enabled() )
  {
    // Trigger Level 2 security timer 
     Level2SecurityTimer = Level2SecurityAccessDelay;
  }
 else*/
if(Chk_SiemensImmo_Enabled() )
  {
    /* count the number of incorrect securityCode entries and 
       insert the respective locking periods */
    if(L2_WrongAttemptTry < 10)
    {
      L2_WrongAttemptTry++;
    }

  Level2SecurityTimer =
  	CaSiemens_L2WrongAttemptDelay[L2_WrongAttemptTry - 1];
  L2SecurityTmrCoefficient=1250;
}
}

/*****************************************************************************
 *
 * Function:           LearnSKandPINService
 * Description:       Mulresp service of learning process.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
FAR_COS void LearnSKandPINService(void)
{
   if (LearnSKandPINState==CbTRUE)
   {
      /* ECM can switch to tester only after sending $78 response. */
      if (!Keyword2000AnswerStillBeingSent())
      {
	 if (SKPIN_LearnMode==0x0A) GoToECMLearnFromImmoState();
	 if (SKPIN_LearnMode==0x0B) GoToImmoLearnFromECMState();
	   	
         LearnSKandPINState=CbFALSE;
      }
   }
   else
   {
      /* Back from tester to responder, recover header message. */
      RxFormatByte=RxFormatByte_Responder;
      RxSourceAddress=RxSourceAddress_Responder;
      /* Send response according to Immo_Erro_Code. */
      if(Immo_Erro_Code==NO_IMMO_ERROR)
      {
	 TxServiceData[0]=0x70;
   	 TxServiceData[1]=0x62;
	 TxServiceData[2]=SKPIN_LearnMode;
   	 RxServiceData[0]=0x30;
	 SendStandardPositiveAnswer(3);
      }
      else
      {
	 RxServiceData[0]=0x30;
	 SendStandardNegativeAnswer(Immo_Erro_Code);
      }
      /* Clear MultiResp flag. */
      WrtMultiRespInProgress( CbFALSE  ) ;

      SKPIN_LearnMode=0;
   }
}/*** End of LearnSKandPINService ***/

/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/*
/* ===========================================================================*/


