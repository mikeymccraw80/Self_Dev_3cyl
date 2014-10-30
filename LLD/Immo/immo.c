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

bool                    ImmoSiemensEnabled;

/* ============================================================================ *\
 * Local variables.
\* ============================================================================ */


/* ============================================================================ *\
 * Local function prototypes.
\* ============================================================================ */

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
	ImmoSiemensEnabled = false;

	if(K_Immo_option == CeImmo_STEC) {
		ImmoSiemensEnabled = true;
	} else {
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

	if(Chk_SiemensImmo_Disabled()) {
		ImmoInhibitEngine = false;
	}
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
	if (Chk_SiemensImmo_Enabled()) {
		SiemensImmo_AuthResultLostService();
		UpdateL2SecurityTmrDelay10s();//for Delay10s
	}

	if (!GetNormalKeywordMode()) {
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
