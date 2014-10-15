/*===========================================================================*/
/* FILE: immo_exec.c                                                         */
/*===========================================================================*/
/* COPYRIGHT, 2004, DELPHI ELECTRONICS & SAFETY SYSTEMS, All Rights reserved */
/* Delphi Confidential                                                       */
/*===========================================================================*/
/* %name:             immo_exec.c %                                          */
/*                                                                           */
/* created_by:       GururajK                                                */
/*                                                                           */
/* date_created:     5 Jan 2005                                              */
/*                                                                           */
/* %derived_by:       vzp48z %                                               */
/*                                                                           */
/* %date_modified:   %                                                       */
/*                                                                           */
/* %version:         dev07 %                                                     */
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
#include "immo_exec.h"
#include "immo.h"
#include "immo_encrypt.h"
#include "kw2dll.h"
#include "bootloader.h"
#include "os_kernel.h"
#include "hal.h"
//#include "cm_state.h"
//#include "v_engine.h"
#include "immo_fexi.h"
//#include "eng_stat.h"
#include "v_immo.h"
//#include "v_efi.h"
#include "immo_cal.h"
//#include "io_cpu12.h"
#include "dd_port.h"
#include "intr_ems.h"
#include "ddmspapi.h"
#include "siemens_immosaut.h"

/* ========================================================================== *\
 * Local preprocessor #define commands.
\* ========================================================================== */
/*  none  */


/* ========================================================================== *\
 * Local preprocessor #define macros.
\* ========================================================================== */
/*  none  */


/* ========================================================================== *\
 * Local type declarations.
\* ========================================================================== */
/*  none  */


/* ========================================================================== *\
 * Local preprocessor #define commands.
\* ========================================================================== */
/*  none  */


/* ========================================================================== *\
 * Global variables.
\* ========================================================================== */

/* Immobilizer Varible */
#pragma section [ram_boot]
uint8_t                    ECMKEY_Reserved[GenericImmoKey_Length];
uint8_t                    AuthenticationCounter, FeedbackAuthCounter, ValidAuthRspCounter;
Every_Loop_Sec_B           SingleAuthenCounter;
Immo_Error_T               Immo_Erro_Code;
Immo_Status_T              ImmoServiceState;
ECM_Immo_Relation_T        ECMImmoRelation;
Authentication_Request_T   Authentication_Request_ID;
#pragma section []



#pragma section [nvram]
//uint8_t                    ECMKEY[JiChengImmoKey_Length];
WORD                       TotalAuthenticationCounter;
TbBOOLEAN                  AuthenticationResult;
TbBOOLEAN                  AuthenticationResultState;
TbBOOLEAN                  ImmoPassThisKeyon;
Every_Loop_Sec_W           NoAuthenticationTimer;
IMMO_WarningState          ImmoCodeWarningSts = AuthenticationResultFail;
#pragma section []

SK_H_T                     Immo_SK_H;
SK_L_T                     Immo_SK_L;
bool                       ImmoSK_NotProgrammed;
uint8_t                    ImmoChallengeStartTime;

static Every_Loop_Sec_W    ImmoStallModeTimer;         /* Maximum: 8192sec */
static Every_Loop_Sec_W    ImmoIGNOffModeTimer;        /* Maximum: 512sec */

WORD                       PIN_Protect_Timer;
BYTE                       ImmoIgnTimer;

uint8_t                    Immo_PIN[PIN_Length_JiCheng];
uint8_t                    Immo_SK[SK_Length];
BYTE                       SKPIN_LearnMode;

bool                       GetSCIRespReceived;
TbBOOLEAN                  LearnSKandPINState;
static bool                Clear_Variable_Flag;

bool                       IGNOffModeTimeOut;

/* ========================================================================== *\
 * Local Macro definitions
\* ========================================================================== */
#define IncreaseTimerImmoStallMode()    ( ImmoStallModeTimer ++  )
#define ResetTimerImmoStallMode()       ( ImmoStallModeTimer = 0 )
#define ImmoStallModeTimeOut            ( FixDefConst(500.0, Every_Loop_Sec_W))


#define IncreaseTimerImmoIGNOffMode()   ( ImmoIGNOffModeTimer ++  )
#define ResetTimerImmoIGNOffMode()      ( ImmoIGNOffModeTimer = 0 )
#define ImmoIGNOffModeTimeOut           (FixDefConst(0.04685, Every_Loop_Sec_W)) /* 46.875ms/7.8125ms IGNoff has its own delay logic.Originally 10 */
/*if counter expired, authentication result will be cleared. 
Note: this codition time must less than the power off delay time 5.1s.*/
#define AuthenticationClearTime         (FixDefConst( 4.5, Every_16th_Loop_Sec_W))
/* ========================================================================== *\
 * Local function prototypes.
\* ========================================================================== */
//static void Get_SK(void);
//static void GenericImmobilizerInitializing(void);
//static void JiChengImmobilizerInitializing(void);
/*****************************************************************************
 *
 * Function:           CheckSingleAuthenticationTime
 * Description:        Check Single Authentication Time
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
FAR_COS void CheckSingleAuthenticationTime(void)
{
   if (ImmoServiceState==WaitingResponse)
   {
      if (SingleAuthenCounter >= (K_SingleAuthenticationMaxTime-3))
      {
         SingleAuthenCounter=0;
         ImmoNoResponseDetected = true;
         ImmoStatusByte.Bits.EcmImmoCommError = (bitfield8_t)true;
         ImmoAuthenErrorDetected=false;
         GoToLostCommunicationState();
      }
      else
      {
         SingleAuthenCounter++;
      }
   }
    
}*//*** End of CheckSingleAuthenticationTime ***/

/*****************************************************************************
 *
 * Function:           CheckTotalAuthorizationTime
 * Description:       Check Total Authorization Time
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/

/*FAR_COS void CheckTotalAuthorizationTime(void)
{
   if ((Authentication==ECMImmoRelation)||(FeedbackAuthentication==ECMImmoRelation))
   {
      if (TotalAuthenticationCounter>=TotalAuthenticationMaxTime)
      {
         // Record Erro code. 
         Immo_Erro_Code=nrcNoImmoResponse;
         ImmoNoResponseDetected=true;
         ImmoAuthenErrorDetected=false;
			   
         // Enter ImmoEndService in next loop. 
         GoToEndTesterState();
      }
      TotalAuthenticationCounter++;
   }
}*//*** End of CheckTotalAuthorizationTime ***/

/*****************************************************************************
 *
 * Function:           GoToECMLearnFromImmoState
 * Description:        GoToECMLearnFromImmoState.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/

FAR_COS void GoToECMLearnFromImmoState(void)
{
   ECMImmoRelation=ECMLearnFromImmo;
   Kw2000State=k2sWaitingInitializing;
}

/*****************************************************************************
 *
 * Function:           GoToImmoLearnFromECMState
 * Description:        GoToImmoLearnFromECMState.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/

FAR_COS void GoToImmoLearnFromECMState(void)
{
   ECMImmoRelation=ImmoLearnFromECM;
   Kw2000State=k2sWaitingInitializing;
}

/*****************************************************************************
 * Function:           CalculateChecksum
 * Description:        Calculate Checksum of a memory section
 * Parameters:         None
 * Return:             uint8_t
 *
 *****************************************************************************/
FAR_COS uint8_t CalculateChecksum(BYTE *address1, BYTE *address2)
{
   uint8_t *addressidx, checksum=0;
 	
   for ( addressidx=address1;addressidx<address2;addressidx++ )
   {
      checksum = checksum + *(addressidx); 
   }	

   return checksum;
}/*** End of CalculateChecksum ***/

/*****************************************************************************
 *
 * Function:           CalculateAuthenticationKey
 * Description:       Calculate Authentication Key
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
/*
FAR_COS void CalculateAuthenticationKey(void)
{
   	if(Chk_JiChengImmo_Enabled())
   {
      if (Authentication==ECMImmoRelation)
      {
         if (SKPIN_LearnMode==0x0B)
         {
           // ECM will Calculate KEY with SK from Immo during ECM learn process.
            digsig(ECMSeed, Immo_SK, ECMKEY);
         }
         else
         {
            digsig(ECMSeed, EE_SK, ECMKEY);
         }
      }
			
   }
		
}*//*** End of CalculateAuthenticationKey ***/

/**************************************************************************
 *
 * Function:           GenericImmo_AuthenticationResultLostService
 * Description:        Authentication Result will be lost during ING OFF. ECM will re-authoriztion 
 *                     after Authentication Result Lost.
 * Parameters:         None
 * Return:             None
 *
 **************************************************************************/
/*FAR_COS void  GenericImmo_AuthenticationResultLostService (void)
{
   ImmoEngineStallCheck();
   ImmoIGNOffCheck();
   ImmoDeactivateProcess();
       
   // Start Immobilizer routine while condition met. 
   if ( AuthenticationResultLost() &&
      (Ignition_On()== ( bitfield16_t )true)&&
      !((!GetFUEL_FuelCutOff()) && ImmoAuthenticationResultPass() && GetEngineTurning()) )
   {
         GenericImmobilizerInitializing();
   }

   ImmoEngineRunLimit();
	
}*//*** End of GenericImmo_AuthenticationResultLostService ***/

/**************************************************************************
 *
 * Function:           JiChengImmo_AuthenticationResultLostService
 * Description:        Authentication Result will be lost during ING OFF. ECM will re-authoriztion 
 *                     after Authentication Result Lost.
 * Parameters:         None
 * Return:             None
 *
 **************************************************************************/
/*FAR_COS void  JiChengImmo_AuthenticationResultLostService (void)
{
    ImmoIGNOffCheck();

    if (AuthenticationResultLost()&&(Ignition_On()== ( bitfield16_t )true)&&(!ImmoAuthenticationResultPass()))
    {	
			
        if(ImmoIgnTimer>=ImmoWaitingLoop)
        {
            if((PwrUpResetFlag)
               ||((!GetDGDM_FaultActive(CeDGDM_VSS_NoSignal))&&(EOBD_VehSpd <= K_ImmoByPassVSS))
               ||(GetDGDM_FaultActive(CeDGDM_VSS_NoSignal)&&(GetHWIO_EngineSpeed()<= FixDefConst( 1000, RPM_W))))
            {
                JiChengImmobilizerInitializing();
            }							  
        }
        else
        {
            ImmoIgnTimer++;
        }
    }
}*//*** End of JiChengImmo_AuthenticationResultLostService ***/

/*****************************************************************************
 *
 * Function:           ImmoEngineStallCheck
 * Description:        Check Engine state
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
FAR_COS void ImmoEngineStallCheck(void)
{
    if(((!ImmoInhibitEngine)) &&
       (!GetEngineTurning()))
    { 
       if ( ImmoStallModeTimer < ImmoStallModeTimeOut)
       {
          IncreaseTimerImmoStallMode();
       }
       else
       {
          ResetTimerImmoStallMode();
          ClearAuthenticationResult();
	  ClearImmoAuthenticationResult();
             /* to avoid running reset check */
          ImmoDisableEngine();
       } 
    }
    else
    {
       ResetTimerImmoStallMode();
    }
}/*** End of ImmoEngineStallCheck ***/

/*****************************************************************************
 *
 * Function:           ImmoIGNOffCheck
 * Description:        Check IGN state
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
FAR_COS void ImmoIGNOffCheck(void)
{
  /*
   if(Chk_GenericImmo_Enabled())
   {
      if(Ignition_On()== ( bitfield16_t )false)
      { 
         if(Clear_Variable_Flag == false)
         {
			if ((ImmoIGNOffModeTimer+1) < K_ImmoAuthenticationClearTime)
				
			//To clear immo authentication result within K_ImmoAuthenticationClearTime,
			  //but not a period of ( K_ImmoAuthenticationClearTime+[0, 7.8125ms] )
			  
			{
			   IncreaseTimerImmoIGNOffMode();
			}
			else
			{
			   ResetTimerImmoIGNOffMode();
			   ClearAuthenticationResult();
			   ClearImmoAuthenticationResult();
			   ECMImmoRelation = NO_Relation;
			   AuthenticationCounter=0;
			   FeedbackAuthCounter=0;
			   ValidAuthRspCounter=0;
			   SingleAuthenCounter=0;
			   ImmoServiceState = Immo_End;
			   ImmoNoResponseDetected = false;
			   ImmoAuthenErrorDetected = false;
			   Clear_Variable_Flag = true;
			} 

		 }
      }
      else
      {
         ResetTimerImmoIGNOffMode();
         Clear_Variable_Flag = false;

      }
		 
      if (IgnitionOffTimeVar >= AuthenticationClearTime)	// this codition time must less than the power off delay time 5.1s 
      {
        ImmoPassThisKeyon = false;
      }

   }
   else if(Chk_JiChengImmo_Enabled())
   {
      if(Ignition_On()== ( bitfield16_t )false)
      { 
         if(Clear_Variable_Flag == false)
         {
			if ((ImmoIGNOffModeTimer+1) < K_ImmoAuthenticationClearTime)
			
			  //To clear immo authentication result within K_ImmoAuthenticationClearTime,
			  //but not a period of ( K_ImmoAuthenticationClearTime+[0, 7.8125ms] )
			  
			{
			   IncreaseTimerImmoIGNOffMode();
			}
			else
			{
			   ImmoDisableEngine();
			   ResetTimerImmoIGNOffMode();
			   ClearAuthenticationResult();
			   ClearImmoAuthenticationResult();
			
			   ECMImmoRelation = NO_Relation;
			   AuthenticationCounter=0;
			   FeedbackAuthCounter=0;
			   ValidAuthRspCounter=0;
			   SingleAuthenCounter=0;
			   ImmoServiceState = Immo_End;
			   Clear_Variable_Flag = true;
			} 

		 }
      }
      else
      {

            ResetTimerImmoIGNOffMode();
            Clear_Variable_Flag = false;

      }

   }
   else if (Chk_SiemensImmo_Enabled())
  {
     if(Ignition_On() == ( bitfield16_t )false)
     {
    // Use IGNSTATE. TBD: 
    //"ImmoIGNOffModeTimeOut" be taken place by K_SiemensImmoAuthenticationClearTime
      if ((ImmoIGNOffModeTimer) < K_ImmoAuthenticationClearTime)
        {
          IncreaseTimerImmoIGNOffMode();
        }
       else
        {
          ResetTimerImmoIGNOffMode();
          //clear result state to trigger authentication.
           //  note: need to wait till next ignition on 
          ClearAuthenticationResult();
          ClearImmoAuthenticationResult();
	  IGNOffModeTimeOut = true;
         ///to avoid running reset check 
	if ( (EOBD_VehSpd > K_ImmoByPassVSS)
               && (!GetDGDM_FaultActive(CeDGDM_VSS_NoSignal) ) )
	   {
            ImmoEnableEngine();
       }	
        } 
      }
     else
       {
         ResetTimerImmoIGNOffMode();
       }
    
     // this codition time must less than the power off delay time 5.1s   
     if (IgnitionOffTimeVar/16 >=  AuthenticationClearTime)
     {
        ImmoPassThisKeyon = CbFALSE;
        ClearAuthenticationResult();
        ClearImmoAuthenticationResult();
     }    
   }

   */
   if (Chk_SiemensImmo_Enabled())
  {
     if(Ignition_On() == ( bitfield16_t )false)
     {
    /* Use IGNSTATE. TBD: */
    /*"ImmoIGNOffModeTimeOut" be taken place by K_SiemensImmoAuthenticationClearTime*/
      if ((ImmoIGNOffModeTimer) < K_ImmoAuthenticationClearTime)
        {
          IncreaseTimerImmoIGNOffMode();
        }
       else
        {
          ResetTimerImmoIGNOffMode();
          /* clear result state to trigger authentication.
             note: need to wait till next ignition on */
          ClearAuthenticationResult();
          ClearImmoAuthenticationResult();
		  
	  IGNOffModeTimeOut = true;
         /* to avoid running reset check */
	if ( (EOBD_VehSpd > K_ImmoByPassVSS)
               && (!GetDGDM_FaultActive(CeDGDM_VSS_NoSignal) ) )
	   {

            ImmoEnableEngine();
       }	
        } 
      }
     else
       {
         ResetTimerImmoIGNOffMode();
       }
    
     /* this codition time must less than the power off delay time 5.1s */  
     if (IgnitionOffTimeVar/16 >=  AuthenticationClearTime)
     {
        ImmoPassThisKeyon = CbFALSE;
        ClearAuthenticationResult();
        ClearImmoAuthenticationResult();
     }    
   	}
}/*** End of ImmoIGNOffCheck ***/

/*
static void Get_SK(void)
{
   Immo_SK_H.Byte[0] = EE_SK[5];
   Immo_SK_H.Byte[1] = EE_SK[4];     
   Immo_SK_L.Byte[0] = EE_SK[3];
   Immo_SK_L.Byte[1] = EE_SK[2];     
   Immo_SK_L.Byte[2] = EE_SK[1];
   Immo_SK_L.Byte[3] = EE_SK[0];
}
*/

/*****************************************************************************
 *
 * Function:           ImmoECMLearnService
 * Description:       ECM service for SID 30 sub ID 62.
 * Parameters:       None
 * Return:              None
 *
 *****************************************************************************/
#if 0
FAR_COS void ImmoECMLearnService(void)
{
   ReadImmoEEPROMData();

   /* Keep RxFormatByte and RxSourceAddress for responder. */
   if (KW2000_Responder==KW2000CommuState)
   {
      RxFormatByte_Responder=RxFormatByte;
      RxSourceAddress_Responder=RxSourceAddress;
   }
   
   if (GetEngineTurning())
   {
      /* If RPM is not zero, ECM can not begin learning process. */
      SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
   }
   else if (ImmoEEPROMStatus[PINProtectFlagIdx]==PINProtected)
   {
      /* If PIN is protected, send NegativeResponse. */
      SendStandardNegativeAnswer(nrcPINProtected);
   }
   else if (RxServiceData[2]==0x0A)
   {
      /* For ECM learn SK from Immobilizer. */
      if(ImmoEEPROMStatus[LeartFlagIdx]==ECMLearned)
      {
   	 SendStandardNegativeAnswer(nrcSystemNotInDeliveryCondition);
      }
      else
      {
         /* Save PIN in RAM. */
         Immo_PIN[0]=GetKw2000ServiceData(3);
         Immo_PIN[1]=GetKw2000ServiceData(4);		
         SKPIN_LearnMode=0x0A;
         LearnSKandPINState=CbTRUE;
	 SendStandardNegativeAnswer(nrcRequestCorrectlyReceived_ResponsePending);
         WrtMultiRespInProgress(CbTRUE);
      }
   }
   else if (RxServiceData[2]==0x0B)
   {
      /* For Immobilizer learn from ECM. */
      if (ImmoEEPROMStatus[LeartFlagIdx]!=ECMLearned)
      {
     	 /* If ECM is not learned, send NegativeResponse. */
     	 SendStandardNegativeAnswer(nrcECMImmoFunctionNotProgrammed);
      }
      else
      {
         if (PINValid())
	 {	         				
            SKPIN_LearnMode=0x0B;
            LearnSKandPINState=CbTRUE;
            WrtMultiRespInProgress( CbTRUE  ) ;
            SendStandardNegativeAnswer(nrcRequestCorrectlyReceived_ResponsePending);
         }
         else
         {
            /* If PIN is wrong, send NegativeResponse and protect PIN. */
            SendStandardNegativeAnswer(nrcPINCodeNotCorrect);
            PINProtectService();
         }
      }
   }
   else if (RxServiceData[2]==0x0E)
   {
      /* Change ECM into unlearned.  */	
      if (ECMLearned!=ImmoEEPROMStatus[LeartFlagIdx])
      {
         SendStandardNegativeAnswer(nrcECMImmoFunctionNotProgrammed);
      }
      else if (PINValid())
      {
         LearnSKandPINState=CbTRUE;
         ImmoSK_NotProgrammed=true;

         ImmoEEPROMStatus[LeartFlagIdx]=ECMNotLearned;	
         UpdateImmoEEPROMData();
         ClearSKPIN();
							 
         TxServiceData[0]=0x70;
         TxServiceData[1]=0x62;
         TxServiceData[2]=0x0E;
         SendStandardPositiveAnswer(3);

      }
      else
      {
         /* If PIN is wrong, send NegativeResponse and protect PIN. */
         SendStandardNegativeAnswer(nrcPINCodeNotCorrect);
         PINProtectService();
      }
   }
   else
   {
      SendStandardNegativeAnswer (nrcSubFunctionNotSupported_InvalidFormat);
   }
  
}/*** End of ImmoECMLearnService ***/
#endif
/*****************************************************************************
 *
 * Function:           GenericImmobilizerInitializing
 * Description:        Initialize Genericimmobilizer
 * Parameters:         None
 * Return:             None
 *
 * ABSTRACT:                                                                 
 * This funtion is called during Ignition On. Initializing communication with 
 *   immo.                                                                   
 *****************************************************************************/
/*static void GenericImmobilizerInitializing(void)
{
   if (StillInDelivery())
   {
      ImmoEnableEngine();
      ImmoPassThisKeyon = true;
      ECMImmoRelation=NO_Relation;
   }
   else if (!SecretKeyAndSecurityAccessCodeEEPROMValid())
   {
      ImmoDisableEngine();
      ECMImmoRelation=NO_Relation;
      ImmoSK_NotProgrammed = true;
      if (GetDGDM_DTC_FaultType (CeDGDM_ImmoKeyCodeNotPgmd) != CeDGDM_FAULT_TYPE_Z)
      {
   	 PerfmDGDM_ProcessFailReport(CeDGDM_ImmoKeyCodeNotPgmd);
      }
      ImmoStatusByte.Bits.EcmVirgin = (bitfield8_t)true;
   }
   else
   {
      if(!BatteryRemoved)
      {
         ImmoEnableEngine();
      }
      else
      {
         ImmoDisableEngine();
      }
      Get_SK();
      ImmoSK_NotProgrammed = false;
      GoToAuthenticationState();
      if (GetDGDM_DTC_FaultType (CeDGDM_ImmoKeyCodeNotPgmd) != CeDGDM_FAULT_TYPE_Z)
      {
         PerfmDGDM_ProcessPassReport(CeDGDM_ImmoKeyCodeNotPgmd);
      }
      ImmoStatusByte.Bits.EcmVirgin = (bitfield8_t)false;
   }
   
  
   if (Authentication==ECMImmoRelation)
   {
      /* Begin Authentication.
     ImmoChallengeStartTime = FastPitLoopCounter;
   }

   
   ValidateAuthenticationResult();
   ClearImmoAuthenticationResult();
}
*/
/*****************************************************************************
 *
 * Function:           JiChengImmobilizerInitializing
 * Description:        Initialize JiCheng immobilizer
 * Parameters:         None
 * Return:             None
 *
 * ABSTRACT:                                                                 
 * This funtion is called during Ignition On. Initializing communication with 
 *   immo.                                                                   
 *****************************************************************************/
/*
static void JiChengImmobilizerInitializing(void)
{
   //clear the current pcode
   ImmoSK_NotProgrammed=false;
   ImmoNoResponseDetected=false;
   ImmoAuthenErrorDetected=false;

   if (StillInDelivery())
   {
      ImmoEnableEngine();
   }	 
   else
   {
      // Keep waiting untill Immobilizer ready. 
      TotalAuthenticationCounter=0;
      SingleAuthenCounter=0;

      ReadImmoEEPROMData();
      ClearImmoAuthenticationResult();
      DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, FALSE);
      ECMImmoRelation=NO_Relation;
      AuthenticationResultState=CbTRUE;
		  
      ImmoDisableEngine();
		 
      if (ImmoEEPROMStatus[LeartFlagIdx]==ECMLearned)
      {
	 if (SKPINEEPROMValid())
	 {
		 
	    // If ECM is learned and SK is valid, begin authorization. 
	    ImmoIgnTimer=0;
	    GoToAuthenticationState();
	    if (GetDGDM_DTC_FaultType (CeDGDM_ImmoKeyCodeNotPgmd) != CeDGDM_FAULT_TYPE_Z)
            {
               PerfmDGDM_ProcessPassReport(CeDGDM_ImmoKeyCodeNotPgmd);
            }
	    ImmoStatusByte.Bits.EcmVirgin = (bitfield8_t)false;
	 }
      }
		 
      // If ECM does not need to communicate with Immo, set DTC at once. 
      if (NO_Relation==ECMImmoRelation)
      {
	 ImmoEEPROMStatus[LeartFlagIdx]=ECMNotLearned;
	 ImmoSK_NotProgrammed = true;
	 ImmoStatusByte.Bits.EcmVirgin = (bitfield8_t)true;
	 if (GetDGDM_DTC_FaultType (CeDGDM_ImmoKeyCodeNotPgmd) != CeDGDM_FAULT_TYPE_Z)
	 {
	    PerfmDGDM_ProcessFailReport(CeDGDM_ImmoKeyCodeNotPgmd);
	 }
		 
      }	
      UpdateImmoEEPROMData();
   }       
}
*/

/*****************************************************************************
 *
 * Function:           ImmoEngineRunLimite
 * Description:        
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
//static void ImmoEngineRunLimit(void)
FAR_COS void ImmoEngineRunLimit(void)
{
   if (ImmoPassThisKeyon == true)
   {
      NoAuthenticationTimer = 0;
   }
   else if (NoAuthenticationTimer >= FixConvert( K_ImmoNoAuthLimit,Every_16th_Loop_Sec_W,Every_Loop_Sec_W  )) 
   {
      ImmoDisableEngine();  
   }
   else if (Ignition_On())
   {
      NoAuthenticationTimer ++;  
   }
}


/*****************************************************************************
 *
 * Function:           GenericImmo_UpdateStateMachine
 * Description:        
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
static void GenericImmo_UpdateStateMachine (void)
{
   uint8_t counter;
   
   for (counter=0;counter<CyKW2MASTERMaxServiceDefTableEntrys;counter++)
   {
      if (CaMasterServiceDefinition[counter].ServiceID==ECMImmoRelation) 
      {
         CaMasterServiceDefinition[counter].Service_Function();
         break;
      }
   }
}
*/

/*****************************************************************************
 *
 * Function:           JiChengImmo_UpdateStateMachine
 * Description:        
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
/*
static void JiChengImmo_UpdateStateMachine(void)
{
   uint8_t counter;
	
   for (counter=0;counter<CyKW2JiChengImmoMaxServiceDefTableEntrys;counter++)
   {
      if (CaJiChengImmoServiceDefinition[counter].ServiceID==ECMImmoRelation) 
      {
         CaJiChengImmoServiceDefinition[counter].Service_Function();
         break;
      }
   }
    
}
*/
/*****************************************************************************
 *
 * Function:           Immo_UpdateService
 * Description:        
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
FAR_COS void Immo_UpdateService (void)
{
   if ( (ECMImmoRelation == EndAuthentication)||
   	(VeSiemens_ECMImmoRelation == CeSiemens_EndAuthentication) )
   {
      ImmoEndService();
   }
   else if ( GetSCIRespReceivedFlag() )
   {/*
      if ( Chk_GenericImmo_Enabled())
      {
         GenericImmo_UpdateStateMachine();
      }
      else if (Chk_JiChengImmo_Enabled())
      {
         JiChengImmo_UpdateStateMachine();
      }
      else   if ( Chk_SiemensImmo_Enabled() )
      {
        SiemensImmo_UpdateStateMachine();
       }*/	
        if ( Chk_SiemensImmo_Enabled() )
      {
        SiemensImmo_UpdateStateMachine();
       }
      ClearSCIRespReceivedFlag();
   }

}

/* added functions for Siemens Immo */
/*****************************************************************************
 *
 * Function:           CheckIMMO_ECMNotLearned
 * Description:        Check Security Key validation at initialization. 
 * Parameters:         None
 * Return:             TbBOOLEAN
 *
 *****************************************************************************/
FAR_COS TbBOOLEAN CheckIMMO_ECMNotLearned(void)
{
   uint8_t i=0;
   TbBOOLEAN CheckResult;
   CheckResult=CbFALSE;

if(((EE_SiemensSK[0]==0)&&(EE_SiemensSK[1]==0)&&(EE_SiemensSK[2]==0)&&(EE_SiemensSK[3]==0)&&(EE_SiemensSK[4]==0)
     &&(EE_SiemensSK[5]==0)&&(EE_SiemensSK[6]==0)&&(EE_SiemensSK[7]==0)&&(EE_SiemensSK[8]==0)&&(EE_SiemensSK[9]==0)
     &&(EE_SiemensSK[10]==0)&&(EE_SiemensSK[11]==0)&&(EE_SiemensSK[12]==0)&&(EE_SiemensSK[13]==0)&&(EE_SiemensSK[14]==0)
     &&(EE_SiemensSK[15]==0))||((EE_SiemensSK[0]==0xFF)&&(EE_SiemensSK[1]==0xFF)&&(EE_SiemensSK[2]==0xFF)&&(EE_SiemensSK[3]==0xFF)&&(EE_SiemensSK[4]==0xFF)
     &&(EE_SiemensSK[5]==0xFF)&&(EE_SiemensSK[6]==0xFF)&&(EE_SiemensSK[7]==0xFF)&&(EE_SiemensSK[8]==0xFF)&&(EE_SiemensSK[9]==0xFF)
     &&(EE_SiemensSK[10]==0xFF)&&(EE_SiemensSK[11]==0xFF)&&(EE_SiemensSK[12]==0xFF)&&(EE_SiemensSK[13]==0xFF)&&(EE_SiemensSK[14]==0xFF)
     &&(EE_SiemensSK[15]==0xFF)))
{
  CheckResult = CbTRUE;
}

return (CheckResult);
}

/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/*
/* ===========================================================================*/

