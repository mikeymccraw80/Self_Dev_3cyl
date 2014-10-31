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
#include "io_type.h"


/* ========================================================================== *\
 * Other header files.
\* ========================================================================== */
#include "immo_exec.h"
#include "immo.h"
#include "immo_encrypt.h"
#include "kw2dll.h"
#include "immo_fexi.h"
#include "v_immo.h"
#include "immo_cal.h"
#include "intr_ems.h"
#include "siemens_immosaut.h"
#include "hal_eeprom_nvm.h"
#include "hal_eeprom_mfg.h"
#include "io_interface_os.h"

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

/* Immobilizer OBD interface */
#pragma section DATA " " ".nc_nvram"
TbBOOLEAN SbImmo_KeyCodeNotPgmdTestFailed;
TbBOOLEAN SbImmo_NoResponseTestFailed;
TbBOOLEAN SbImmo_AuthenErrorTestFailed;
#pragma section DATA " " ".bss"

TbBOOLEAN SbImmo_KeyCodeNotPgmdTestComplete;
TbBOOLEAN SbImmo_NoResponseTestComplete;
TbBOOLEAN SbImmo_AuthenErrorTestComplete;


/* Immobilizer Varible */
// #pragma section [ram_boot]
uint8_t                    ECMKEY_Reserved[GenericImmoKey_Length];
uint8_t                    AuthenticationCounter, FeedbackAuthCounter, ValidAuthRspCounter;
Every_Loop_Sec_B           SingleAuthenCounter;
Immo_Error_T               Immo_Erro_Code;
Immo_Status_T              ImmoServiceState;
ECM_Immo_Relation_T        ECMImmoRelation;
Authentication_Request_T   Authentication_Request_ID;
// #pragma section []



// #pragma section [nvram]
#pragma section DATA " " ".nc_nvram"
//uint8_t                    ECMKEY[JiChengImmoKey_Length];
WORD                       TotalAuthenticationCounter;
TbBOOLEAN                  AuthenticationResult;
TbBOOLEAN                  AuthenticationResultState;
TbBOOLEAN                  ImmoPassThisKeyon;
Every_Loop_Sec_W           NoAuthenticationTimer;
IMMO_WarningState          ImmoCodeWarningSts = AuthenticationResultFail;
// #pragma section []
#pragma section DATA " " ".bss"              /* normal volatile variables */

SK_H_T                     Immo_SK_H;
SK_L_T                     Immo_SK_L;
bool                       ImmoSK_NotProgrammed;
uint8_t                    ImmoChallengeStartTime;

static Every_Loop_Sec_W    ImmoStallModeTimer;         /* Maximum: 8192sec */
static Every_Loop_Sec_W    ImmoIGNOffModeTimer;        /* Maximum: 512sec */

WORD                       PIN_Protect_Timer;
BYTE                       ImmoIgnTimer;

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

/*****************************************************************************
 *
 * Function:           GoToECMLearnFromImmoState
 * Description:        GoToECMLearnFromImmoState.
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/

void GoToECMLearnFromImmoState(void)
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

void GoToImmoLearnFromECMState(void)
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
uint8_t CalculateChecksum(BYTE *address1, BYTE *address2)
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
 * Function:           ImmoEngineStallCheck
 * Description:        Check Engine state
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void ImmoEngineStallCheck(void)
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
void ImmoIGNOffCheck(void)
{
	if (Chk_SiemensImmo_Enabled()) {
		if(Ignition_On() == ( bitfield16_t )false) {
			/* Use IGNSTATE. TBD: */
			/*"ImmoIGNOffModeTimeOut" be taken place by K_SiemensImmoAuthenticationClearTime*/
			if ((ImmoIGNOffModeTimer) < K_ImmoAuthenticationClearTime) {
				IncreaseTimerImmoIGNOffMode();
			} else {
				ResetTimerImmoIGNOffMode();
				/* clear result state to trigger authentication. note: need to wait till next ignition on */
				ClearAuthenticationResult();
				ClearImmoAuthenticationResult();
				IGNOffModeTimeOut = true;
				/* to avoid running reset check */
				// if ( (EOBD_VehSpd > K_ImmoByPassVSS) && (!GetDGDM_FaultActive(CeDGDM_VSS_NoSignal) ) )
				if (EOBD_VehSpd > K_ImmoByPassVSS) {
					ImmoEnableEngine();
				}
			}
		} else {
			ResetTimerImmoIGNOffMode();
		}

		/* this codition time must less than the power off delay time 5.1s */  
		if (IgnitionOffTimeVar/16 >=  AuthenticationClearTime) {
			ImmoPassThisKeyon = CbFALSE;
			ClearAuthenticationResult();
			ClearImmoAuthenticationResult();
		}
	}
}/*** End of ImmoIGNOffCheck ***/

/*****************************************************************************
 *
 * Function:           ImmoEngineRunLimite
 * Description:        
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
//static void ImmoEngineRunLimit(void)
void ImmoEngineRunLimit(void)
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
 * Function:           Immo_UpdateService
 * Description:        
 * Parameters:         None
 * Return:             None
 *
 *****************************************************************************/
void Immo_UpdateService (void)
{
	if ( (ECMImmoRelation == EndAuthentication)|| (VeSiemens_ECMImmoRelation == CeSiemens_EndAuthentication) ) {
		ImmoEndService();
	} else if ( GetSCIRespReceivedFlag() ) {
		if ( Chk_SiemensImmo_Enabled() ) {
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
TbBOOLEAN CheckIMMO_ECMNotLearned(void)
{
   uint8_t i=0;
   TbBOOLEAN CheckResult;
   uint8_t *EE_SiemensSK = NsFILE_NVM_EE_ManufactData.VaFILE_EE_SecretKey;

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

