/* ============================================================================ *\
 * immo.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       immo.c-2:csrc:mt20a#1
 * Revision:        2
 * Creation date:   Monday, June 17, 2002 9:35:36 AM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the application layer of immobilizer.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "reuse.h"
#include "types.h"

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "immo_cal.h"
#include "immo.h"
#include "kw2app.h"
#include "immo_exec.h"
#include "immo_fexi.h"
#include "siemens_immossrv.h"

/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define macros.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local type declarations.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */

/*****************************************************************************/
#pragma section DATA " " ".nc_nvram"         /* nvram variables, checked with a checksum */
/*****************************************************************************/
bool           ImmoInhibitEngine;

/*****************************************************************************/
#pragma section DATA " " ".bss"              /* normal volatile variables */
/*****************************************************************************/

//ImmoStatusByteType      ImmoStatusByte;
//bool                    ImmoRecordSuccessCEL;
//ImmoDeactivateStateType ImmoDeactivateState;

//Every_Loop_Sec_W        ImmoDeactivateOnTimer;
//bool                    ImmoGenericEnabled;
//bool                    ImmoJiChengEnabled;
/* Added Siemens Immo */
bool                    ImmoSiemensEnabled;

/* ============================================================================ *\
 * Local variables.
\* ============================================================================ */


/* ============================================================================ *\
 * Local function prototypes.
\* ============================================================================ */

/* ============================================================================ *\
 * FUNCTION: ImmoDeactivateProcess
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function contain the immobilizer deactivation state transition
 * machine
 *
\* ============================================================================ */
#if 0
void FCALL ImmoDeactivateProcess(void)
{

   switch(ImmoDeactivateState)
   {
      case ImmoDeactivateIdle:
      {
         /* level2 security is unlock */
         if(GetLevel2VulnerabilityState())
         {
            /* Initialize Deactivation On Timer. 
             * The actual precision for generic immo logic is 7.8125ms 
             */
            ImmoDeactivateOnTimer = FixConvert( K_ImmoDeactivateOnSec,
                                                Every_4th_Loop_Sec_W,
                                                Every_Loop_Sec_W);
            /* Go to Deactivation Delay state */
            ImmoDeactivateState = ImmoDeactivateOn;
         }
         else
         {
            /* Do nothing */
         }
         break;
      }
      case ImmoDeactivateOn:
      {
         if( ( ImmoDeactivateOnTimer>0 ) &&
             GetCommunicationEstablishedState() )
         {
            ImmoDeactivateOnTimer--;
         }
         else
         {
            lockL2SecurityAccess();
            /* go back to idle state */
            ImmoDeactivateState = ImmoDeactivateIdle;
         }
         break;
      }
      default:
      {
         /* Shouldn't get it */
         break;
      }
   }
}
#endif
/* ============================================================================ *\
 * FUNCTION: DtrmImmoStatus
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function determine the status of immobilizer, active or deactive
 *
\* ============================================================================ */
void DtrmImmoStatus( void )
{
   //ImmoGenericEnabled = false;
   //ImmoJiChengEnabled = false;
   ImmoSiemensEnabled = false;

/*
{
   if (K_Immo_option == CeImmo_Generic)
   {
	  ImmoGenericEnabled = true;
   }
   else if(K_Immo_option == CeImmo_Generic_EEControl)
   {
	  if(EE_Immo_option == 0)
	  {
		 ImmoGenericEnabled = true;
	  }
   }
   else if(K_Immo_option == CeImmo_JiCheng)
   {
	  ImmoJiChengEnabled = true;
	   
	  // If PIN is protected, Activate PIN Access delay.
	  ReadImmoEEPROMData();
	  if (ImmoEEPROMStatus[PINProtectFlagIdx]==PINProtected)
	  {	   
		 PIN_Protect_Timer=PINAccessDelayTime; 
	  }
	  else    
	  {
		 PIN_Protect_Timer=0;
	  }
   }
    else if((K_Immo_option == CeImmo_Brilliance)||(K_Immo_option ==CeImmo_Siemens))
    	{
    	  ImmoSiemensEnabled = true;
    	}
}
*/


    if((K_Immo_option == CeImmo_STEC))
    	{
    	  ImmoSiemensEnabled = true;
    	}
   else
   {
      // do nothing
   }
}  


/* ============================================================================ *\
 * FUNCTION: ImmobilizerIgnitionOn
 * ============================================================================
 *
 * This function contain the immobilizer ignition on logic
 *
\* ============================================================================ */
void ImmobilizerIgnitionOn(void)
{
   DtrmImmoStatus();

     if(Chk_SiemensImmo_Disabled())  
   {
      ImmoInhibitEngine = false;  
   }

/*
   //for the condition of no IMMO action, clear the flag 
   if(Chk_GenericImmo_Disabled()&& Chk_JiChengImmo_Disabled()
   	&& Chk_SiemensImmo_Disabled())  
   {
      ImmoInhibitEngine = false;  
   }

   //occur battery removed
   if(Chk_GenericImmo_Enabled() )
   {
	  if(BatteryRemoved)
	  {
              NoAuthenticationTimer = FixConvert( K_ImmoNoAuthLimit,Every_16th_Loop_Sec_W,Every_Loop_Sec_W  );
	  }
   }
*/
}

/**************************************************************************                                                                  
* Function:          Immo_Executive                                         
* Description:       This procedure is the main routine of Immobilization.  
* Execution Rate:    7.81 ms                                                                                                                    
* Parameters:        none                                                  
* Return:            none                                                                                                                    
**************************************************************************/
void Immo_Executive (void)
{
/*
{
   if (Chk_GenericImmo_Enabled())
   {  
      // do not bypass the Immobilizer functions 
     // execute Immobilizer Ignition Key logic 
      GenericImmo_AuthenticationResultLostService ();
   }
   else if (Chk_JiChengImmo_Enabled())
   {
      PINUnProtectService();
      JiChengImmo_AuthenticationResultLostService();
   }
   else if (Chk_SiemensImmo_Enabled())
   {

      SiemensImmo_AuthResultLostService();
	  	
      UpdateL2SecurityTmrDelay10s();//for Delay10s
   }
}
*/

  if (Chk_SiemensImmo_Enabled())
   {

      SiemensImmo_AuthResultLostService();
	  	
      UpdateL2SecurityTmrDelay10s();//for Delay10s
   }
  
   if (!GetNormalKeywordMode())
   {
      /*-- immobilizer Keyword Mode. Client Mode. --*/
      Update_IMMO_DLL_Service ();  /* update kw2000 date link service */
      Immo_UpdateService ();      /* immobilization service state machine */
   }    	
}


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
\* ============================================================================ */
