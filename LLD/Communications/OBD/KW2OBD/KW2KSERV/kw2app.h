#ifndef KW2APP_H
#define KW2APP_H
/* ============================================================================ *\
 * kw2app.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2app.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:34 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 application layer.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "kw2type.h"
#include "reuse.h"
#include "lux_type.h"
// #include "kw2appcf.h"
// #include "dd_nvram.h"

/***********************Global DEFINITIONS:****************************/
/* (1280 * .00781) = 10 Sec. */

#define        SecurityAccessDelay (1250)
#define        SyZERO_VALUE        (0)
#define        CyMsgReq_ID  (0)

/*********************************************************************/
/* DESCRIPTION:  This structure defines the Request messages table.  */
/*********************************************************************/
typedef void  (*p_Service_Function)(void) ;
typedef void  (*p_MultiMessageFunction)(void);

typedef struct
{
  /*
   * Service ID Number supported.
   */
  uint8_t                  ServiceID ;
  /*
   * Matching Service Function Supported
   */
  p_Service_Function    Service_Function ;
  /*
   * Structure used to define the Multi message table.
   */
  p_MultiMessageFunction    MultiMessageFunction ;
} SERVICE_DEFINITION_ARRAY_TYPE ;

typedef struct
{
  /*
   * Service ID Number supported.
   */
  uint8_t                  ServiceID ;
  /*
   * Matching Service Function Supported
   */
  p_Service_Function    Service_Function ;

} KW2MASTER_SERVICE_DEFINITION_ARRAY_TYPE ;

/*********************************************************************/
/*                  GLOBAL VARIABLES DECLARATIONS                    */
/*********************************************************************/
extern uint16_t    Kw2000Seed;
extern uint16_t    Kw2000Key;
extern uint16_t    Kw2000Level2Seed;
extern uint16_t    Kw2000Level2Key;
extern uint8_t     Kw2000VulnerabilityFlag;

extern uint8_t     CyServiceRequestTable_Idx ;
extern uint16_t    SecurityTimer;
extern bool        AppResponsePending ;

extern const SERVICE_DEFINITION_ARRAY_TYPE CaServiceDefinition[] ;
extern const uint8_t CyMaxServiceDefTableEntrys ;

extern bool    CommunicationStatus ;

/*********************************************************************/
/*                  EXTERN FUNCTION DECLARATIONS                     */
/*********************************************************************/
extern void InitializeKw2000Services (void);
extern void UpdateKeyword2000Services (void);
extern void UpdateL2SecurityTmrDelay10s(void);
extern bool SecurityAccessStatus ;

extern bool L2SecurityTmrDelay10s;
/* Level 2 security access status */
extern bool L2_SecurityAccessStatus;
/* Level 2 security access timer */
extern Every_Loop_Sec_W Level2SecurityTimer;
//extern uint32_t local_Timer;
extern  TbBOOLEAN  VbCopyAndExecuteKernelPending;

/*********************************************************************/
/*                  static inline FUNCTION DECLARATIONS                     */
/*********************************************************************/

/*********************************************************************/
/***     Return number of entrys in the Responce table.            ***/
/*********************************************************************/
#define GetMsg_ID_TableMsgLength()                  ((uint8_t) CyMaxServiceDefTableEntrys)

/**********************************************************************/
/***    Load the security timer with the SecurityAccessDelay        ***/
/**********************************************************************/
#define TriggerSecurityTiming()                     (SecurityTimer = SecurityAccessDelay)

/********************************************************************/
/*** Tests if the SecurityTimer variable value is zero.           ***/
/*** Returns true if it is zero otherwise false.              ***/
/********************************************************************/
#define CheckIfSecurityTimerIsZero()                ((bool) ( SecurityTimer == SyZERO_VALUE ))

/*********************************************************************/
/*** Set the current mode to be waiting for responce from Application*/
/*********************************************************************/
#define SetAppResponsePending()                     (AppResponsePending = true)

/*********************************************************************/
/*** Clr the current mode to be waiting for responce from Application*/
/*********************************************************************/
#define ClrAppResponsePending()                     (AppResponsePending = false)

/*********************************************************************/
/*** Check the current mode of Programming state                     ***/
/*********************************************************************/
#define GetAppResponsePending()                     ((bool) AppResponsePending)

/*********************************************************************/
/***   Sets the security access mechanism to locking state.        ***/
/*********************************************************************/
#define lockSecurityAccess()                        (SecurityAccessStatus = false)

/*********************************************************************/
/***    Sets the security access mechanism to unlocking            ***/
/*********************************************************************/
#define UnlockSecurityAccess()                      (SecurityAccessStatus = true)

/*********************************************************************/
/***   Get Security Access flag state.                             ***/
/*********************************************************************/

#define GetVulnerabilityState()                     ( SecurityAccessStatus )

/*********************************************************************/
/***   Unlock level 2 security access.                             ***/
/*********************************************************************/

#define UnlockL2SecurityAccess()    (L2_SecurityAccessStatus = true)

/*********************************************************************/
/***   lock level 2 security access.                               ***/
/*********************************************************************/

#define lockL2SecurityAccess()      (L2_SecurityAccessStatus = false)

/*********************************************************************/
/***   Get level 2 Security Access flag state.                     ***/
/*********************************************************************/

#define GetLevel2VulnerabilityState()  (L2_SecurityAccessStatus)

/**********************************************************************/
/***    Load the security timer with the SecurityAccessDelay        ***/
/**********************************************************************/


//#define Level2SecurityAccessDelay               (1250)

/********************************************************************/
/*** Tests if the level 2 SecurityTimer variable value is zero.   ***/
/*** Returns true if it is zero otherwise false.                  ***/


#define CheckIfL2SecurityTimerIsZero()    (Level2SecurityTimer == 0)


/*********************************************************************/
/***    Get the ECU Reset Pending flag                             ***/
/*********************************************************************/
// static inline TbBOOLEAN GetECUResetPending(void)
// {
  // return VbECUResetPending ; 
// } /*** End of SetECUResetPending ***/


/**********************************************************************/
/***    Load the security timer with the SecurityAccessDelay        ***/
/**********************************************************************/

#define Level2SecurityAccessDelay               (FixDefConst(10.0, Every_Loop_Sec_W))
//#define TriggerL2SecurityTiming()         (Level2SecurityTimer = Level2SecurityAccessDelay)
extern void TriggerL2SecurityTiming(void);
/*********************************************************************/
/***    Set the ECU Reset Pending flag                             ***/
/*********************************************************************/
//static inline void SetECUResetPending( TbBOOLEAN LyECUReset )
//{
 // VbECUResetPending = LyECUReset ;
//} /*** End of SetECUResetPending ***/

/*********************************************************************/
/***    Set the Copy Kernel to Ram and Execute Pending flag                             ***/
/*********************************************************************/
static INLINE void SetCopyAndExecuteKernelPending(bool LyCopyKernel)
{
  VbCopyAndExecuteKernelPending = LyCopyKernel ;
} /*** End of SetCopyAndExecuteKernelPending ***/

/*********************************************************************/
/***    Get the Copy Kernel to Ram and Execute Pending flag                             ***/
/*********************************************************************/
static INLINE bool GetCopyAndExecuteKernelPending(void)
{
  return VbCopyAndExecuteKernelPending ;
} /*** End of SetCopyAndExecuteKernelPending ***/

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 06/08/08     FX      -
 * + Baseline - Created from MT22U.
 *
\* ============================================================================ */
#endif
