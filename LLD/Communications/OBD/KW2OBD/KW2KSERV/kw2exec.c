/* ============================================================================ *\
 * kw2exec.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2exec.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Friday, June 14, 2002 4:10:07 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the re-useable KW2000 executive.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */


/***********************INCLUDE FILES*****************************/
#include "kw2exec.h"
#include "kw2app.h"
#include "kw2dll.h"
#include "kw2dllcf.h"
//#include "immo_exec.h"

/***********************************************************************
*       NAME                            PARAMETER                      *
*                                                                      *
* InitCANH_PHY_Parms                      none                         *
*                                                                      *
* Applicable Documents:                                                *
*                                                                      *
* Description: Keyword 2000 Executive Routine                          *
*                                                                      *
************************************************************************
* Last modified on: 06-23-97        by: Carl Walthall                  *
*                                                                      *
* Last verified on: mm-dd-yy        by:                                *
*                                                                      *
************************************************************************
*                                                                      *
* External variables and constants referenced, and why:                *
*          NAME            DECLARED IN            REASON/PURPOSE       *
*                                                                      *
*                                                                      *
***********************************************************************/

#include "kw2exec.h"
#include "kw2appcf.h"

void FAR_COS KeywordExecutive( KW2000_Status_T LyKW2000_ModeSelect )
{

 switch( LyKW2000_ModeSelect )
 {
   /* Initialize Keyword 2000 software */
   case CwKW2000_Initializes:
         /* Normal Keyword Phyical Address */
         KW2000CommuState=KW2000_Responder;
         SetMyPhysicalAddr ( MyPhysicalAddr ) ;
         InitializeKw2000VIO() ;
         InitializeKw2000Services() ;
         break ;
   /* Update Keyword 2000 buffers */
   case CwKW2000_RunMode:
         UpdateKeyword2000ServiceTasks();
         UpdateKeyword2000VIO() ;
         UpdateKeyword2000Services() ;
         break ;
 }
}


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - Changed to support KWP2000 master mode for generic immo
 *
 * 22/11/07	   Yu Runwu    mt20u2#194
 * + Implement CJAE Immobilizer and Remove Old Immobilizer
 *   - Delete the case CwImmoTester_RunMode.
\* ============================================================================ */
