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
// #include "dcanfapi.h" /* DCAN_GetCommunicationActiveState */
/******************************************************************************
* KW2K Service Include Files
******************************************************************************/
#include "kw2kfapi.h" /*KW2K_GetCommunicationActiveState */
#include "kw2dll.h"/*For GetKw2000ServiceData(),*/
// #include "kw2srv10.h" /*Init2CCommVariables*/
// #include "kw2srv10m.h"
#include "obdssvio.h"
#include "kw2api.h"
#include "hal_ucram.h"
#include "inst_overlay.h"
#include "dcancomm.h"
#include "obdlfsrv.h"

/*********************************************************************/
/*            Global  Variable                                             */
/*********************************************************************/
//TbBOOLEAN  VbECUResetPending ;
TbBOOLEAN  VbCopyAndExecuteKernelPending;
//Kw2000DiagStateType  Kw2000DiagSt ;


/*
 * used to save supported Service request
 * table index.
 */
TbBOOLEAN         VbCAN_OBD_Enabled;
TbBOOLEAN         VbKW2K_OBD_Enabled;

static BYTE                 OBD_PML_SAIndex;
static T_COUNT_WORD         Kw2000_Seed;
static T_COUNT_WORD         Kw2000_Key;
static T_COUNT_LONG         OBD_Seed_4Bytes;
static T_COUNT_LONG         OBD_Key_4Bytes;

/*********************************************************************/
/*           Static  Variable                                             */
/*********************************************************************/

void InitAppLvlCommVariables(void);

/*********************************************************************/
/***   This returns the ECM key value.                             ***/
/*********************************************************************/
WORD Get_Key( void )
{
  Kw2000_Key = *((WORD *)KW2K_KEY_ADDRESS); /* take this out when EEPROM keyis implemented */
  return ( (WORD)Kw2000_Key );
}

/*********************************************************************/
/***  This returns stored seed value.                              ***/
/*********************************************************************/
WORD Get_Security_Seed_Data( void )
{
  Kw2000_Seed = *((WORD *)KW2K_SEED_ADDRESS); /* take this out when EEPROM seed is implemented */
  return ( (WORD)Kw2000_Seed );
}

LONGWORD GetOBD_4ByteKey( void )
{
  OBD_Key_4Bytes = *((LONGWORD *)OBD_KEY_4Bytes_ADDRESS); /* take this out when EEPROM keyis implemented */
  return ( (LONGWORD)OBD_Key_4Bytes ); 
}

LONGWORD GetOBD_4ByteSeed( void )
{
  OBD_Seed_4Bytes = *((LONGWORD *)OBD_SEED_4Bytes_ADDRESS);/* take this out when EEPROM seed is implemented */
  return ( (LONGWORD)OBD_Seed_4Bytes );
}

/*********************************************************************/
/*** Get Communication Established Status.                         ***/
/*********************************************************************/
TbBOOLEAN GetCommunicationEstablishedState( void )
{
   bool LyRtnVal;
   LyRtnVal = false;
   if ( VbCAN_OBD_Enabled )
   {
      LyRtnVal = GetLnCommunicationActiveState();
   }
   else if ( VbKW2K_OBD_Enabled )
   {
      LyRtnVal = KW2K_GetCommunicationActiveState();
   }
   return (LyRtnVal);  
} /*** End of GetCommunicationEstablishedState ***/

void OBD_ByKW2000( void )
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
/*** Run Kernel On Ram                     ***/
/*********************************************************************/
extern void Force_Stay_In_Boot(uint16_t pattern);
void RunKernelOnRam (void )
{
	/* Set the Copy Kernel to Ram and Execute Pending flag to be FALSE*/
	SetCopyAndExecuteKernelPending(CbFALSE) ;

	Disable_Interrupts();

	DMA_Clear_Device( );

	INST_Set_Active_Calibration_Page( INST_CALIBRATION_PAGE_REFERENCE );

	HAL_uncleard_ram.data[NCRAM_REPROGRAM_FLAG] = true;
	Force_Stay_In_Boot(0xDEAD);
}

/*********************************************************************/
/*** Builds a standard OBD negative answer                      ***/
/*********************************************************************/
void SendStandardNegativeAnswer(  uint8_t  in_code )
{
   if ( VbCAN_OBD_Enabled )
   {
      // DCAN_SendStandardNegativeAnswer( in_code );
   }
   else if ( VbKW2K_OBD_Enabled )
   {
      KW2K_SendStandardNegativeAnswer( in_code );
   }
}
/*********************************************************************/
/*** Builds a standard kw2000 positive answer                      ***/
/*********************************************************************/
void SendStandardPositiveAnswer( BYTE in_msg_size )
{
   if (VbCAN_OBD_Enabled )
   {
      // DCAN_SendStandardPositiveAnswer( in_msg_size );
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
      //SetStandardDiagnosticState() ;
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
extern TbBOOLEAN DCAN_AnswerStillBeingSent( void );
 void UpdateOBD_Services(void)
{ 
   // Can8DataBytesArrayType *Can8_DataBytesArrayPtr;
   if ((!DCAN_AnswerStillBeingSent ())&&
           (!Keyword2000AnswerStillBeingSent ())&&
           (VbKW2K_OBD_Enabled))
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
         // KW2KCAN_Received_Message (*Can8_DataBytesArrayPtr);
         RunKernelOnRam();
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
/** This function does required actions before doing a reset.  It    */
/** clears the non-volatile (NVRAM) here.  This ensures that NVRAM is*/
/** initialised after reset.  The application must add other         */
/** functionality.                                                   */
/*********************************************************************/
void DoNecessaryActionsBeforeReset ( void )
{

  // WORD *Pointer ;

  //  for ( Pointer = ( WORD *) &CpHWIO_RAM_NVM_CriticalStartAddress ;
  //        Pointer <=( WORD *) &CpHWIO_RAM_NVM_CriticalEndAddress ;
  //        Pointer++ )
  //  {
  //     *Pointer = 0 ;
  //  }

  //  for ( Pointer = ( WORD *) &CpHWIO_RAM_NVM_StartAddress ;
  //        Pointer <=( WORD *) &CpHWIO_RAM_NVM_EndAddress ;
  //        Pointer++ )
  //  {
  //     *Pointer = 0 ;
  //  }
}

/*********************************************************************/
/** FUNCTION:     Srv23Address_Is_Validkw()                          */
/**                                                                  */
/** Type:         global                                             */
/**                                                                  */
/** DESCRIPTION:  This procedure validates the passed address for    */
/**               service 23.                                        */
/**                                                                  */
/** PARAMETERS:   FOUR_BYTE_DATA_TYPE                                */
/**                                                                  */
/** RETURN:       None                                               */
/**                                                                  */
/** Global Variables Updated: None                                   */
/*********************************************************************/
TbBOOLEAN Srv23Address_Is_Validkw(LONGWORD Address, uint8_t Size)
{
   TbBOOLEAN LyRtnVal;

   if ( ((Address >= CyRAM_SectionStart ) &&
      ((Address + (Size-1)) <= CyRAM_SectionEnd ) )
      ||
    ( ( Address >= ( LONGWORD ) CpHWIO_ROM_CalibrationStart ) &&
      ((Address + (Size-1)) <= ( LONGWORD ) CpHWIO_ROM_CalibrationEnd ))
      ||
    (( ( Address >= ( LONGWORD ) CyEEPROM_SectionStart ) &&
      ((Address + (Size-1)) <= ( LONGWORD ) CyEEPROM_SectionEnd ))))
         // && ((GetVIOS_ManufactEnableCounter() > V_COUNT_BYTE(0))
             // || (GetVIOS_VehInDev())))
   {
      LyRtnVal = CbTRUE;
   }
   else
   {
      LyRtnVal = CbFALSE;
   }
   return(LyRtnVal);

}

/*********************************************************************/
/* FUNCTION:     Address_Is_Validkw()                                */
/*                                                                   */
/* Type:         global                                              */
/*                                                                   */
/* DESCRIPTION:  This procedure validates the passed address.        */
/*                                                                   */
/* PARAMETERS:   FOUR_BYTE_DATA_TYPE                                 */
/*                                                                   */
/* RETURN:       None                                                */
/*                                                                   */
/* Global Variables Updated: None                                    */
/*********************************************************************/
TbBOOLEAN Address_Is_Validkw( LONGWORD Address, BYTE Size )
{
 TbBOOLEAN LyRtnVal;

 if ( ((Address >= CyRAM_SectionStart )                  &&
      ((Address + (Size-1)) <= CyRAM_SectionEnd )) )
   {
      LyRtnVal = CbTRUE;
   }
   else
   {
      LyRtnVal = CbFALSE;
   }
   return(LyRtnVal);
}

