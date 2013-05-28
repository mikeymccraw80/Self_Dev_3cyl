/* ============================================================================ *\
 * kw2appcf.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2appcf.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:09:38 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 application layer configuration.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/***********************LOCAL DEFINITIONS:*****************************/
#include "kw2app.h"
// #include "dd_boot.h"
#include "kw2dll.h"
#include "kw2appcf.h"

/*  services specific includes */
#include "j1979.h"
// #include "obdlfsrv.h"

void ServiceNotSupported( void )
{
   SendStandardNegativeAnswer( nrcServiceNotSupported ) ;
} /*** End of ServiceNotSupported ***/


void KwNoMultiModeAval( void )
{
   SendStandardNegativeAnswer( nrcServiceNotSupported );
} /*** End of KwNoMultiModeAval ***/

/*********************************************************************
 * Table:        CsServiceDefArray                                   *
 *                                                                   *
 * Type:         global                                              *
 *                                                                   *
 * DESCRIPTION:  This table defines the supported 1979/14230 ID and  *
 *               support functions. The support messages may be      *
 *               entered in the table in any order or number. The    *
 *               Update Service routine in kw2app.c will search the  *
 *               table till know messages are found.                 *
 *                                                                   *
 * PARAMETERS:   None                                                *
 *                                                                   *
 * RETURN:       None                                                *
 *                                                                   *
 * Global Variables Updated: Service definition Array                *
 *********************************************************************/
 /*
  * SERVICE_DEFINITION_ARRAY_TYPE defines a structure that contains
  * the messages ID and a pointer to the supported service function.
  */
const SERVICE_DEFINITION_ARRAY_TYPE CaServiceDefinition[ ]=
{
    /*
     * 14230 Service and 1979 Mode Function address table
     */
    {
        0 ,                         /* Mode doesnt match */
        ServiceNotSupported ,
        KwNoMultiModeAval
    },                            /* For NonSupported Modes */

  /*
   * Supported 1979 Modes
   */
    { sirSAEJ1979DiagTestMode01 ,
      J1979Mode1Handler   ,       /* Mode 1 */
      KwNoMultiModeAval
    } ,

    { sirSAEJ1979DiagTestMode02,
      J1979Mode2Handler  ,        /* Mode 2 */
      KwNoMultiModeAval
    },

    { sirSAEJ1979DiagTestMode03,
      J1979Mode3Handler  ,        /* Mode 3 */
      FormJ1979_Mode_43_Data
    },

    { sirSAEJ1979DiagTestMode04,
      J1979Mode4Handler  ,        /* Mode 4 */
      KwNoMultiModeAval
    },

//    { sirSAEJ1979DiagTestMode05,
//      J1979Mode5Handler   ,       /* Mode 5 */
//      KwNoMultiModeAval
//    } ,

//    { sirSAEJ1979DiagTestMode06,
//      J1979Mode6Handler   ,       /* Mode 6 */
//      FormJ1979_NextMode46
//    } ,

    { sirSAEJ1979DiagTestMode07,
      J1979Mode7Handler   ,       /* Mode 7 */
      FormJ1979_Mode_47_Data
    } ,

//    { sirSAEJ1979DiagTestMode08,
//      J1979Mode8Handler  ,        /* Mode 8 */
//      KwNoMultiModeAval
//    },

    { sirSAEJ1979DiagTestMode09,
      J1979Mode9Handler  ,       /* Mode 9 */
      FormJ1979_NextMode49
    },
};

/*
 * This constant defines the sizeof the supported service table
 * length. This size is calculated at compile time and is used
 * by the Update Service routine in file kw2app.c to search the service
 * table.
 */
const uint8_t  CyMaxServiceDefTableEntrys  =
     (sizeof( CaServiceDefinition )/
     sizeof( SERVICE_DEFINITION_ARRAY_TYPE ));

/**********************************************************************/
/*** This function initializes the service module variables when a  ***/
/*** new communication session is started.  It should be updated    ***/
/*** for individual applications.                                   ***/
/**********************************************************************/
void InitAppLvlCommVariables_KW ( void )
{
   /* Invoke application functions. */
    InitKwJ14230StartDiagnosticSession();
}

/**********************************************************************/
/*** This function initializes the service module variables when    ***/
/*** Kw2000 is a whole is initialise. This is only done at power up.***/
/**********************************************************************/
void InitAppLvlCommVariablesGlobal ( void )
{
   /* Invoke application initialisations. */
    InitKwJ14230DynamicallyDefineLocalIdentifier();
}


static void CheckVulnerability(void)
{




}


/**********************************************************************/
/*** This function executes logic which is required for a specific  ***/
/*** service even if the service itself might not be active         ***/
/**********************************************************************/
void UpdateKeyword2000ServiceTasks(void)
{
   CheckVulnerability();
}



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
