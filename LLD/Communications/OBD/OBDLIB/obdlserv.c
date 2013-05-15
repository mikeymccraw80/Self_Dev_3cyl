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
* FILE NAME:   : obdlserv.c                                              *
* Applicable   : Keyword Protocol 2000, Ver.1.1, July 10 1998.         *
* Documents                                                            *
*                                                                      *
* Description:  This modules contains the all user interface constants *
*
* $SOURCE: ems_project@brighton.tcb:daewoo_2002:kw2api.c $
* $REVISION: 1.1 $
* $AUTHOR: brighton.tcb:/users/safayya...daewoo_2002_MathLib:safayyad $
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   09-11-98  cdw     Initial file creation                        *
* 1.2   09-23-98  cdw     Added Get_EngineTurning() function           *
* 1.4   09-24-98  iaj     Added security access related functions.     *
* 1.5   09-28-98  JZha    Correct the function Address_Is_Validkw().   *
*                         Completed the function Get_EngineTurning().  *
* 1.6   10-6-98   JZha    Move in Global Arrays.                       *
*                         Added Revord Local ID for service 21.        *
* 1.7   10-10-98  iaj     Added the definition of the function         *
*                         ResetActivatorsIfActivated.                  *
* 1.8   10-15-98  CDW     New version created from Daewoo delivery     *
* 1.9   12-09-98  CDW     Removed PID routines                         *
* 1.10  01-14-99  CDW     Fixed function header                        *
* 1.11  01-25-99 JZha     Added the ResetStatus array and the size.    *
* 1.13  02-03-99 JZha     Changed the memory end range.                *
* 1.14  07-30-99  HFU     Modified ECUIDScalingTable according to spec.*
* 1.15  03-31-00  bdt     Modified ECUIDScalingTable according to spec.*
* 1.16  04-11-00  bdt     Remove unused ECUIDScalingSize.              *
* 1.17  05-11-00  iaj     Added the definition for                     *
*                         Srv23Address_Is_Validkw.                     *
* tci_pt3#3.1.2                                                        *
*       031202  ban 3482  Modified ECU scaling table to match Hyundai  *
*                         KW spec                                      *
*                                                                      *
************************************************************************
* MT34 Revision History                                                *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* tcb_pt1#9                                                            *
*       040827  kan -BM-  Corrected merge error from 5SF65_GMDAT_MT34: *
*       040608  kan -BM-  Modified function PerformReset to allow a Mode
*                         10, 85 to reset the controller for re-flash. *
* tci_pt3#8.1.1                                                        *
*       040831 ban 4392 Updated ECUIDScalingTable to match the GMDAT   *
*                       specifications                                 *
*                       Added KW2000_SideRail_Ptr and                  *
*                       KW2000_DelphiBaseModelPN_Ptr                   *
* tcb_pt1#11
*       041129 kan -BM- Merge following versions:
* tci_pt3#9
*       040825 ban 4373  Added KpKW2K_ReflashRamPatPtr
* tcb_pt1#12
*       041207 kan 4731 Modified function Srv23Address_Is_Validkw() by
*                        adding valid check for EEPROM address range.
* tci_pt3#13
*       050106 ban 4803 Added MEC and Vulnerability check to access
*                       EEPROM/PML memory range
* tci_pt3#14
*       050214 ban 4921 Modified ECUIDScalingTable
*
*
************************************************************************
* SGM MT80IAC Revision History                                                   *
* Rev.  Date    User    SCR         Description of Changes                       *
* ----  --------  ----    -------------------------------------------------*
*
*ctc_pt3#1.0
*         070421 WJ  ctc_pt3#13  Added PerformReset() into Modifed PerformReset() *
*                                            for supporting SID11                 *
*                                                                                 *
*ctc_pt3#2.0                                                                                             
*         070629 WJ ctc_pt3#21   Modified ReadECUIdentification Service (SID1A)   *
*                                            Changed ECUIDScalingTable            *
* 2       100917 wj CTC RSM8069
*                                Updated for CAN reflash
***********************************************************************/


/*********************************************************************/
/*            INCLUDE FILES                                          */
/*********************************************************************/
/******************************************************************************
* APP Include Files
******************************************************************************/

/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/

/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
#include "dcanfapi.h" /* DCAN_GetCommunicationActiveState */
/******************************************************************************
* KW2K Service Include Files
******************************************************************************/
#include "kw2kfapi.h" /*KW2K_GetCommunicationActiveState */
#include "kw2dll.h"/*For GetKw2000ServiceData(),*/
#include "kw2dll.h" /*PerformReset()*/
#include "kw2srv10.h" /*Init2CCommVariables*/
#include "kw2srv10m.h"
/******************************************************************************
/* For Hal Interface*/
/******************************************************************************/
#include "obdssvio.h" 
/*********************************************************************/
/*            Global  Variable                                             */
/*********************************************************************/
/******************************************************************************
/* For Reset and RunKernelOnRam Only*/
/******************************************************************************/
//TbBOOLEAN  VbECUResetPending ;
TbBOOLEAN  VbCopyAndExecuteKernelPending;
//Kw2000DiagStateType  Kw2000DiagSt ;


/*
 * used to save supported Service request
 * table index.
 */
TbBOOLEAN         VbCAN_OBD_Enabled;
TbBOOLEAN         VbKW2K_OBD_Enabled;

/*********************************************************************/
/*           Static  Variable                                             */
/*********************************************************************/

void InitAppLvlCommVariables(void);


/*********************************************************************/
/*** Get Communication Established Status.                         ***/
/*********************************************************************/
FAR_COS TbBOOLEAN GetCommunicationEstablishedState( void )
{
   bool LyRtnVal;
   LyRtnVal = false;
   if ( VbCAN_OBD_Enabled )
   {
      LyRtnVal = DCAN_GetCommunicationActiveState();
   }
   else if ( VbKW2K_OBD_Enabled )
   {
      LyRtnVal = KW2K_GetCommunicationActiveState();
   }
   return (LyRtnVal);  
} /*** End of GetCommunicationEstablishedState ***/

FAR_COS void OBD_ByKW2000( void )
{
   VbKW2K_OBD_Enabled = CbTRUE; 
   VbCAN_OBD_Enabled = CbFALSE;
}

void OBD_ByCAN( void )
{
   VbKW2K_OBD_Enabled = CbFALSE; 
   VbCAN_OBD_Enabled = CbTRUE;
}

/*********************************************************************/
/*** Builds a standard OBD negative answer                      ***/
/*********************************************************************/
FAR_COS void SendStandardNegativeAnswer(  uint8_t  in_code )
{
   if ( VbCAN_OBD_Enabled )
   {
      DCAN_SendStandardNegativeAnswer( in_code );
   }
   else if ( VbKW2K_OBD_Enabled )
   {
      KW2K_SendStandardNegativeAnswer( in_code );
   }
}
/*********************************************************************/
/*** Builds a standard kw2000 positive answer                      ***/
/*********************************************************************/
FAR_COS void SendStandardPositiveAnswer( BYTE in_msg_size )
{
   if (VbCAN_OBD_Enabled )
   {
      DCAN_SendStandardPositiveAnswer( in_msg_size );
   }
   else if ( VbKW2K_OBD_Enabled )
   {
      KW2K_SendStandardPositiveAnswer( in_msg_size );  
   }
}


 void InitAppLvlCommVariables(void)
{ 
   if ( VbCAN_OBD_Enabled )
   {
    /* Set standard diagnostic mode as default */
      SetStandardDiagnosticState() ;
   }
   else if ( VbKW2K_OBD_Enabled )
   {
    /* Invoke application functions. */
   InitKwJ14230StartDiagnosticSession();
   }
}
/***********************************************************************
* FUNCTION:      UpdateOBD_Services                                   *
*                                                                      *
* TYPE:          Global                                                *
*                                                                      *
* Description: This function will be called at each 7.82 ms  by the    *
*              operation system to check the recieved Msg.             *
*                                                                      *
***********************************************************************/   
FAR_COS void UpdateOBD_Services(void)
{ 
   Can8DataBytesArrayType *Can8_DataBytesArrayPtr;
   if ((!DCAN_AnswerStillBeingSent ())&&
           (!Keyword2000AnswerStillBeingSent ()))
   { 
        /*--- Triggers Programmming Session only after */
   /*    answer is sent to the tester ---*/
   /*--- Provoque a hardware Reset ---*/
      if ( GetECUResetPending())
      {
  /* Set the ECU Reset Pending flag to be FALSE.
   */
         SetECUResetPending(CbFALSE) ;
   /* Do systems and software required necessary actions before
      reset, for example clear NVRAM etc.
    */

         PerformReset () ;
      }
	  
      if ( GetCopyAndExecuteKernelPending())
      {
         KW2KCAN_Received_Message (*Can8_DataBytesArrayPtr);
      }
  
   }
 /*
    If a new communication session has started, initialize
    required application variables.
    */
   if ( GetCommunicationEstablishedState () )
   {
      if ( !CommunicationStatus )
      {
         CommunicationStatus = CbTRUE;
         InitAppLvlCommVariables();
      }
   }
   else
   {
       CommunicationStatus = CbFALSE;
   }
}


/*********************************************************************/
/***   Returns the start address of the Calibration                ***/
/***   Rom section.                                                ***/
/*********************************************************************/

/*********************************************************************/
/***   This functions returns TRUE, if the conditions exists to    ***/
/***   run the service 38 in diagnostic mode. Application has to   ***/
/**    include the logic to test the conditions.                   ***/
/*********************************************************************/
TbBOOLEAN CheckIfConditionsCorrectToRunInDiagMode ( void )
{
   return ( CbTRUE );
}


/*********************************************************************/
/** This function does required actions before doing a reset.  It    */
/** clears the non-volatile (NVRAM) here.  This ensures that NVRAM is*/
/** initialised after reset.  The application must add other         */
/** functionality.                                                   */
/*********************************************************************/
void DoNecessaryActionsBeforeReset ( void )
{
#if 0
  WORD *Pointer ;

   for ( Pointer = ( WORD *) &CpHWIO_RAM_NVM_CriticalStartAddress ;
         Pointer <=( WORD *) &CpHWIO_RAM_NVM_CriticalEndAddress ;
         Pointer++ )
   {
      *Pointer = 0 ;
   }

   for ( Pointer = ( WORD *) &CpHWIO_RAM_NVM_StartAddress ;
         Pointer <=( WORD *) &CpHWIO_RAM_NVM_EndAddress ;
         Pointer++ )
   {
      *Pointer = 0 ;
   }
#endif
}
