#ifndef IMMO_EXEC_H
#define IMMO_EXEC_H
/*===========================================================================*/
/* FILE: immo_exec.h                                                         */
/*===========================================================================*/
/* COPYRIGHT, 2004, DELPHI ELECTRONICS & SAFETY SYSTEMS, All Rights reserved */
/* Delphi Confidential                                                       */
/*===========================================================================*/
/* %name:             immo_exec.h %                                          */
/*                                                                           */
/* created_by:       GururajK                                                */
/*                                                                           */
/* date_created:     5 Jan 2005                                              */
/*                                                                           */
/* %derived_by:       vzp48z %                                             */
/*                                                                           */
/* %date_modified:   %                                                       */
/*                                                                           */
/* %version:         2 %                                                     */
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

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "kw2dll.h"
#include "kw2app.h"
#include "Immo_cal.h"


/* ============================================================================ *\
 * Exported preprocessor #define macros.
\* ============================================================================ */
#define TotalAuthenticationMaxTime              294     /* 7.8125*294=2.3s */

#define ImmoWaitingLoop                         15
#define AuthenticationMessageLength             0x06
#define FeedbackAuthenMessageLength_Generic     0x01
#define FeedbackAuthenMessageLength_JiCheng     0x02
#define ECMLearnFromImmoMessageLength           0x01
#define LearnFromECMMessageLength               0x03
#define SK_All0xFF                              (0xFFFFFFFF)
#define SK_All0x00                              (0x00000000)
#define Authentication_PostiveRespLength        0x02
#define AuthenticationResult_PostiveRespID      0x8C
#define AuthenticationResult_NegativeRespID     0x3A
#define AuthenticationResult_PostiveRespLength  0x1
#define PINAccessDelayTime                      64000  /* 64000*7.8125ms = 500s */
#define PINAccessMaxTimer                       3

#define A0_Request_ID                           0xA0
#define A0_PostiveRespID                        0xE0
#define A0_PostiveRespID_Offset                 0x00
#define A0_PostiveRespLength                    0x06
#define A0_PostiveResp_Code_Offset              0x1

#define NegativeID_Offset                       0x00
#define A0_NegativeRespLength                   0x3
#define A0_NegativeRespID_Offset                0x1
#define A0_NegativeResp_Code_Offset             0x2

#define A1_Request_ID                           0xA1
#define A1_PostiveRespID                        0xE1
#define A1_PostiveRespID_Offset                 0x00
#define A1_PostiveRespLength                    0x1
#define A1_PostiveResp_Code_Offset              0x0
#define A1_NegativeRespLength                   0x3
#define A1_NegativeRespID_Offset                0x1
#define A1_NegativeResp_Code_Offset             0x2

#define A2_Request_ID                           0xA2
#define A2_PostiveRespID                        0xE2
#define A2_PostiveRespID_Offset                 0x00
#define A2_PostiveRespLength                    0x8
#define A2_PostiveResp_Code_Offset              0x02
#define A2_NegativeRespLength                   0x03
#define A2_NegativeRespID_Offset                0x1
#define A2_NegativeResp_Code_Offset             0x2

#define A3_Request_ID                           0xA3
#define A3_PostiveRespID                        0xE3
#define A3_PostiveRespID_Offset                 0x00
#define A3_PostiveRespLength                    0x6
#define A3_PostiveResp_Code_Offset              0x02
#define A3_NegativeRespLength                   0x03
#define A3_NegativeRespID_Offset                0x1
#define A3_NegativeResp_Code_Offset             0x2

#define AuthorizationSuccess                    0x80
#define AuthorizationFail                       0x7F

#define nrcImmoBusy                             0x21
#define nrcPINProtected                         0x37
#define nrcECMEEPROMError                       0xA0
#define nrcSystemNotInDeliveryCondition         0xA1
#define nrcImmoDismatch                         0xA2
#define nrcNoImmoResponse                       0xA3
#define nrcECMImmoFunctionNotProgrammed         0xA4
#define nrcUnsuccessfullyAuthentication         0xA5
#define nrcRandomAllZeroOrOne                   0xA6
#define nrcPINCodeNotCorrect                    0xA7
#define nrcECMPrereleaseTimeExpired             0xA8
#define nrcProgrammingUnsuccess                 0xA9
/* For Siemens Immo*/
#define  SecurityAccessLevel2KeySize    (2) 
#define  SiemensImmoSecretKeySize          (16)
/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */

typedef enum
{
     SendRequest,
     WaitingResponse,
     HandleResponse,
     NoResponse,
     Immo_End
} Immo_Status_T;

typedef enum
{
     NO_Relation,
     Authentication,
     FeedbackAuthentication,
     ECMLearnFromImmo,
     ImmoLearnFromECM,
     EndAuthentication
} ECM_Immo_Relation_T;

typedef enum
{
     NegativeResp, 
     PostiveResp,
     PendingResp,
     WrongResp
} Immo_Resp_T;

typedef enum
{
     NO_IMMO_ERROR,
     SingleAuthen_OverTime,
     Totalauthen_OverTime,
     ImmoResponse_Timeout,
     NG_ImmoResponse,
     Other_Immo_ERROR
} Immo_Error_T;

typedef enum
{
     Authentication_Rqst=0x03,
     FeedBackResult_Rqst=0x05
} Authentication_Request_T;

typedef union
{
     uint16_t  Word;
     uint8_t   Byte[2];
} SK_H_T;

typedef union
{
     uint32_t  LongWord;
     uint8_t   Byte[4];
} SK_L_T;

typedef enum
{
     LeartFlagIdx,
     PINWrongAttemptCounterIdx,
     PINProtectFlagIdx,
     ActionCntIdx,
     ImmoErrorCodeIdx
} Immo_EEPROM_DATA_T;

typedef enum
{
     PINProtected,
     PINUnProtected
}PIN_Protect_T;

typedef enum
{
     ECMLearned,
     ECMNotLearned
}ECM_Learned_T;


/*for Siemens Immo*/
/******************************************************************************
 * Variable Type Declarations
 ******************************************************************************/
typedef enum
{
  CeIMMO_WaitTiniTime,
  CeIMMO_SendingWup,
  CeIMMO_SendingResponseMsg,//changed CeIMMO_SendingRequestMsg to CeIMMO_SendingResponseMsg
  CeIMMO_WaitICURequest,//changed CeIMMO_WaitICUResponse to CeIMMO_WaitICURequest
  CeIMMO_IdleState
} TeIMMO_DLL_STATUS;


typedef enum
{
  CeSiemens_NoRelation,
  CeSiemens_StartCommunication,
  CeSiemens_Authentication,
  CeSiemens_FeedbackAuthentication,
  CeSiemens_StopCommunication,
  CeSiemens_EndAuthentication
} TeSiemens_ECM_Relation; //this can be optimized. TBD

typedef enum
{
  CeIMMO_NoError,            /* no error                              */
  CeIMMO_SingleAuthOverTime, /* single authentication overtime        */
  CeIMMO_TotalAuthOverTime,  /* total authentication overtime         */
  CeIMMO_ICURespTimeOut,     /* ICU response time out                 */
  CeIMMO_ECURespTimeOut,     /* ecu sending message time out          */
  CeIMMO_ICURespNG,          /* wrong ICU response                    */
  CeIMMO_ECUInVirgin,        /* ecu not programmed                    */
  CeIMMO_ICUReqSeqError,     /* request sequence error (Siemens)         */
  CeIMMO_ICUBadMsg,          /* bad ICU message (corrupt)             */
  CeIMMO_ICUInVirginOrWrgTXP /* icu not programmed or wrong txp (Siemens)*/
} TeIMMO_ActReason;

typedef enum
{
  AuthenticationResultPass,      /* Engine Start Enable         */
  AuthenticationResultFail,      /* Engine Start Disable        */
  ImmoFuncNotProgrammed,         /* Key ID Not Stored           */
  InvalidFormat                  /* Signal Not Valid                */
} IMMO_WarningState;

typedef union
{
  uint8_t  seed_byte[4];
  uint32_t seed_word;
} U32_Seed;

/***********************************************************/
/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */

extern TbBOOLEAN SbImmo_KeyCodeNotPgmdTestFailed;
extern TbBOOLEAN SbImmo_NoResponseTestFailed;
extern TbBOOLEAN SbImmo_AuthenErrorTestFailed;
extern TbBOOLEAN SbImmo_KeyCodeNotPgmdTestComplete;
extern TbBOOLEAN SbImmo_NoResponseTestComplete;
extern TbBOOLEAN SbImmo_AuthenErrorTestComplete;

extern bool                       ImmoInhibitEngine;
extern uint8_t                    ECMKEY[];
extern uint8_t                    AuthenticationCounter, FeedbackAuthCounter, ValidAuthRspCounter;
//extern Every_Loop_Sec_B           SingleAuthenCounter;
//extern WORD                       TotalAuthenticationCounter;
extern TbBOOLEAN                  AuthenticationResult;
extern TbBOOLEAN                  AuthenticationCondition;
extern Immo_Error_T               Immo_Erro_Code;
extern Immo_Status_T              ImmoServiceState;
extern ECM_Immo_Relation_T        ECMImmoRelation;
//extern Authentication_Request_T   Authentication_Request_ID;
extern SK_H_T                     Immo_SK_H;
extern SK_L_T                     Immo_SK_L;
extern bool                       ImmoNoResponseDetected;
extern bool                       ImmoSK_NotProgrammed;
extern bool                       ImmoAuthenErrorDetected;
extern TbBOOLEAN                  AuthenticationResultState;
extern uint8_t                    ImmoChallengeStartTime;
extern TbBOOLEAN                  ImmoPassThisKeyon;
extern Every_Loop_Sec_W           NoAuthenticationTimer;
extern WORD                       PIN_Protect_Timer;
//extern uint8_t                    ImmoEEPROMStatus[];
//extern const uint8_t              CyKW2MASTERMaxServiceDefTableEntrys;
//extern const KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE     CaMasterServiceDefinition[ ];
//extern const uint8_t                                     CyKW2JiChengImmoMaxServiceDefTableEntrys;
//extern const KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE     CaJiChengImmoServiceDefinition[ ];
extern uint8_t                    Immo_PIN[];
extern uint8_t                    Immo_SK[];
extern BYTE                       ImmoIgnTimer;
extern BYTE                       SKPIN_LearnMode;
extern bool                       GetSCIRespReceived;
/*for Siemens immo*/
extern TeSiemens_ECM_Relation     VeSiemens_ECMImmoRelation;
extern TeIMMO_DLL_STATUS          VeSiemens_DLL_State;
extern TeIMMO_ActReason           VeSiemens_ActReason;
extern IMMO_WarningState          ImmoCodeWarningSts;

extern bool                       IGNOffModeTimeOut;
extern const T_COUNT_WORD     CaSiemens_L2WrongAttemptDelay[];
extern uint16_t               L2SecurityTmrCoefficient;

/* Defined per Siemens IMMO Specification */

extern TbBOOLEAN VbSiemens_StartCommReceived;
extern TbBOOLEAN VbSiemens_StopCommReceived;

extern TbBOOLEAN                  LearnSKandPINState;

/* ============================================================================ *\
 * Local INLINE functions and #define function-like macros.
\* ============================================================================ */
#define ClearImmoAuthenticationResult()         (AuthenticationResult=CbFALSE)
#define SetImmoAuthenticationResult(result)     (AuthenticationResult=result)
#define GetImmoAuthenticationResult()           (AuthenticationResult)
#define ImmoAuthenticationResultFail()          (AuthenticationResult==CbFALSE)
#define ImmoAuthenticationResultPass()          (AuthenticationResult==CbTRUE)
#define StillInDelivery()                       (NV_ManufacturesEnableCounter[0]!=0)
#define GetNormalKeywordMode()                  ((ECMImmoRelation==NO_Relation)&&(VeSiemens_ECMImmoRelation==CeSiemens_NoRelation))
#define ClearSCIRespReceivedFlag()              (GetSCIRespReceived = false)
#define SetSCIRespReceivedFlag()                (GetSCIRespReceived = true)
#define GetSCIRespReceivedFlag()                (GetSCIRespReceived == true)

/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
//extern FAR_COS void CheckSingleAuthenticationTime(void);
//extern FAR_COS void CheckTotalAuthorizationTime(void);
extern void Update_IMMO_DLL_Service(void) ;
//extern FAR_COS void GenericImmo_AuthenticationResultLostService (void);
//extern FAR_COS void JiChengImmo_AuthenticationResultLostService (void);
extern TbBOOLEAN  EEPROMWriteSuccess( uint8_t *EEP_data_address, uint8_t *RAM_data_address, uint8_t size);
//extern FAR_COS TbBOOLEAN  SecretKeyAndSecurityAccessCodeEEPROMValid(void);
extern TbBOOLEAN CheckIMMO_ECMNotLearned(void);
extern uint8_t    CalculateChecksum(BYTE *address1, BYTE *address2);

//extern FAR_COS void ReadImmoEEPROMData(void);
//extern FAR_COS TbBOOLEAN  SKPINEEPROMValid(void);
//extern FAR_COS void UpdateImmoEEPROMData(void);
//extern FAR_COS void GoToAuthenticationState(void);
extern void Immo_UpdateService (void);
extern void ImmoEndService(void);
//extern FAR_COS void GoToEndTesterState(void);
/*for Siemens immo*/
extern void GoToEndResponderState(void);
//extern FAR_COS void CalculateAuthenticationKey(void);
//extern FAR_COS void PINUnProtectService(void);
//extern FAR_COS void DisableIMMDFlag(void);
//extern FAR_COS TbBOOLEAN  PINValid (void);
//extern FAR_COS void ClearSKPIN(void);
//extern FAR_COS void GoToECMLearnFromImmoState(void);
//extern FAR_COS void GoToImmoLearnFromECMState(void);
//extern FAR_COS void PINProtectService (void);
//extern FAR_COS void ImmoECMLearnService(void);
extern void LearnSKandPINService(void);

extern TbBOOLEAN DtrmnIMMO_SingleAuthTimeOvertime(Every_Loop_Sec_B counter);
/* for Siemens Immo */
extern void ImmoEngineStallCheck(void);
extern void ImmoIGNOffCheck(void);
extern void ImmoEngineRunLimit(void);
extern void TriggerL2SecurityTiming(void);
extern void GoToECMLearnFromImmoState(void);
extern void GoToImmoLearnFromECMState(void);
/*********************************************/
/*--------- Change IMMO DLL state     -------*/
/*********************************************/
INLINE void SetSiemens_DLLStateToWaitTiniTime (void)
{
  VeSiemens_DLL_State = CeIMMO_WaitTiniTime;
}

INLINE void SetSiemens_DLLStateToSendingWup (void)
{
  VeSiemens_DLL_State = CeIMMO_SendingWup;
}

INLINE void SetSiemens_DLLStateToSendingResponseMsg (void)
{
  VeSiemens_DLL_State = CeIMMO_SendingResponseMsg;
}

INLINE void SetSiemens_DLLStateToWaitICURequest (void)
{
  VeSiemens_DLL_State = CeIMMO_WaitICURequest;
}

INLINE void SetSiemens_DLLStateToIdleState (void)
{
  VeSiemens_DLL_State = CeIMMO_IdleState;
}
/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/* 20110715   hzm  Add Enum IMMO_WarningState for IMMO application           */
/* ==========================================================================*/
 
#endif /* IMMO_EXEC_H */
