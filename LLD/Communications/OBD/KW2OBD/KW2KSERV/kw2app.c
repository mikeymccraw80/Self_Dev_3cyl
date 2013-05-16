/* ============================================================================ *\
 * kw2app.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2app.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:29 PM
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

#include "kw2api.h"
#include "kw2app.h"
#include "kw2dll.h"
#include "immo_exec.h"
#include "immo.h"


uint16_t       Kw2000Seed;
uint16_t       Kw2000Key;
uint16_t       Kw2000Level2Seed;
uint16_t       Kw2000Level2Key;
uint8_t        Kw2000VulnerabilityFlag;

uint16_t       SecurityTimer;
bool           AppResponsePending ;

/* Keeps track of change in communication state. */
bool    CommunicationStatus ;
bool           SecurityAccessStatus ; /* This flag indicates the ECU lock/unlock status.
                                       *     A FALSE value : ECU locked,
                                             A TRUE  value : ECU unlocked. */
/* Level 2 security access status */
bool L2_SecurityAccessStatus;
/* Level 2 security access timer  */
T_COUNT_WORD Level2SecurityTimer;

bool L2SecurityTmrDelay10s=false;


/***********************************************************************************/
#pragma section [nvram]                    /* NVRAM Variables                      */
/***********************************************************************************/

/* used to save supported Keyword protocol 2000 Service request table index. */
uint8_t CyServiceRequestTable_Idx ;   /* --- NVMEM --- */

/***********************************************************************************/
#pragma section []                         /* Normal Variables                     */
/***********************************************************************************/

/* Local functions used to parse Multi/Requested messages */
static void  ExcuteNextCurrentMultiMsg( uint8_t ) ;
static void  ExcuteNextRequestedMsg( uint8_t , uint8_t ) ;



/***********************************************************************
* FUNCTION:      UpdateKeyword2000Services                             *
*                                                                      *
* TYPE:          Global                                                *
*                                                                      *
* Description: This function will be called at each 7.82 ms  by the    *
*              operation system to check the recieved Msg.             *
*                                                                      *
************************************************************************
* Last modified on: 03/21/00              by: Iqbal Javid              *
***********************************************************************/
void UpdateKeyword2000Services (void)
{
	uint16_t *AddPointer ;
	/* Count down the Security Timer */
	if (SecurityTimer != 0 ) {
		SecurityTimer--;
	}
	/* Count down the level 2 Security Timer */
	if (Chk_SiemensImmo_Enabled()) {
		if ((Level2SecurityTimer != 0)&&(L2SecurityTmrDelay10s==true)) {
			Level2SecurityTimer--;
			L2SecurityTmrDelay10s=false;
			L2SecurityTmrCoefficient=1250;
		} else if (Level2SecurityTimer==0) {
			L2SecurityTmrDelay10s=false;
			L2SecurityTmrCoefficient=0;
		}
	} else {
		if (Level2SecurityTimer != 0) {
			Level2SecurityTimer--;
		}
	}   
	/* If there is no Msg on bus */
	if (!Keyword2000AnswerStillBeingSent ())
	{
		/*--- Triggers Programmming Session only after */
		/*    answer is sent to the tester ---*/
		/*--- Provoque a hardware Reset ---*/
		if ( GetECUResetPending()) {
			/* Set the ECU Reset Pending flag to be FALSE. */
			SetECUResetPending(false) ;
			/* Do systems and software required necessary actions before
			reset, for example clear NVRAM etc. */

			DoNecessaryActionsBeforeReset() ;
			PerformReset() ;
		}
	}
	/* If a new communication session has started, initialize required application variables. */
	if ( GetCommunicationEstablishedState ()){
		if ( !CommunicationStatus ) {
			CommunicationStatus = true;
			InitAppLvlCommVariables ();
		}
	} else {
		CommunicationStatus = false;
	}

	/* If there is no Msg on bus and it need to send the multiresponse */
	if (( GetMultiRespInProgress() ||
		GetAppResponsePending()) &&
		(!Keyword2000AnswerStillBeingSent()))
	{
		ExcuteNextCurrentMultiMsg( CyServiceRequestTable_Idx ) ;
	}
	else
	{
		/* Check if the ECU received a message and need to response */
		if (ApplicationLevelKeyword2000ServicePending()) {
			ExcuteNextRequestedMsg( GetKw2000ServiceData( CyMsgReq_ID ), GetMsg_ID_TableMsgLength()) ;
		} /*** End of UpdateKeyword2000Services ***/
	}
}


void UpdateL2SecurityTmrDelay10s (void)
{
	if(L2SecurityTmrCoefficient!=0) {
		L2SecurityTmrCoefficient--;
	} else if(L2SecurityTmrCoefficient==0) {
		L2SecurityTmrDelay10s=true;
	}
}

/***********************************************************************
* FUNCTION:      ExucuteNextCurrentMultiMsg                            *
*                                                                      *
* TYPE:          Local                                                 *
*                                                                      *
* Description:   This function to deal the multi-response or period    *
*                response.                                             *
************************************************************************
* Last modified on: 09/03/98              by: Carl Walthall            *
***********************************************************************/
static void  ExcuteNextCurrentMultiMsg( uint8_t lyMsgselected )
{
	/* Exucute the multiple message select by the request */
	CaServiceDefinition[ lyMsgselected ].MultiMessageFunction( );
}


/***********************************************************************
* FUNCTION:      ExucuteNextRequestedMsg                               *
*                                                                      *
* TYPE:          Local                                                 *
*                                                                      *
* Description:   This function will check and execute to response      *
*                the next request message.                             *
*                                                                      *
************************************************************************
* Last modified on: 06/18/98              by: Carl Walthall            *
***********************************************************************/
static void ExcuteNextRequestedMsg( uint8_t lyCurrentRequestedMsg,
                                     uint8_t lyMsg_ID_TableLength )
{
   #define CyNoRequestfound (0)

   /* Set to no Request found */
   bool  lyValidRequestfound = false ;
   /*
    * Search Message Request table for valid ID
    */

	for( CyServiceRequestTable_Idx = 0;
		CyServiceRequestTable_Idx < lyMsg_ID_TableLength;
		CyServiceRequestTable_Idx++ )
	{
		/*
		* Test for a valid message ID to Respond to
		*/
		if( CaServiceDefinition[ CyServiceRequestTable_Idx ].ServiceID == lyCurrentRequestedMsg ) 
		{
			CaServiceDefinition[ CyServiceRequestTable_Idx ].Service_Function() ;
			lyValidRequestfound = true ;
			break ;
		}
	}
	/*
	* If there where no matching Request ? Send invalid format
	*/
	if( !lyValidRequestfound )
	{
		CaServiceDefinition[CyNoRequestfound].Service_Function() ;
	}
}


/*********************************************************************
* FUNCTION:     InitializeKw2000Services                             *
*                                                                    *
* Type:         global                                               *
*                                                                    *
* DESCRIPTION:  Initialize Kw2000 application level service handler. *
**********************************************************************
* Last modified on: 06/18/98              by: Carl Walthall          *
*********************************************************************/
void InitializeKw2000Services (void)
{
	TriggerSecurityTiming () ;
	TriggerL2SecurityTiming();
	SetECUResetPending( false ) ;
	CommunicationStatus = false ;
	InitAppLvlCommVariablesGlobal();
} /*** End of InitializeKw2000Services ***/


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
