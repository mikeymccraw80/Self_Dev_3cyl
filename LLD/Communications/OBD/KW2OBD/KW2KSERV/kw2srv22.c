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
* Filename     : kw2srv22.c                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 22 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 22 as defined by the above applicable doc.    *
*                                                                      *
*                The purpose of this service is to allow access to PCM *
*                data by the common identifier (same as the Parameter  *
*                Parameter Identifier (PID) in the class2 protocol.)   *
*                Each common ID number will return the unique          *
*                scaled  resolution of a parameter.                    *
*                                                                      *
* $Source: ems_project@bright...:daewoo_2003:kw2srv22.c $              *
* $Revision$                                                        *
* $Author: brighton $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-16-98  JZha    Initial file creation.                       *
* 1.2   01-14-99  cdw     added new PID routine.                       *
* 1.3   01-19-99  JZha    Standardized hte file.                       *
************************************************************************
* Functions in this file:                                              *
************************************************************************
* extern:                                                              *
*        void KwJ14230ReadDataByCommonIdentifier( void );              *
***********************************************************************/
#if 0
#include "kw2dll.h"
#include "kw2api.h" 
//#include "cmnpid.h"
#include "kw2srv10.h"
//#include "kw2srv10m.h" /* CheckProgrammingState() */
//#include "kw2srv22.h"
/*********************************************************************/
/*           CONSTANT DECLARATIONS                                   */
/*********************************************************************/
/* Define the Msg length and the PID number position in the Msg */

/***********************************************************************
* FUNCTION:      KwJ14230ReadDataByCommonIdentifier     (Service 22)   *
*                                                                      *
* Description:   Same as above file description                        *
*                                                                      *
*                                                                      *
************************************************************************
* Last modified on: 01/19/99              by: John Zha                 *
***********************************************************************/

void KwJ14230ReadDataByCommonIdentifier( void )
{
   SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat ) ;

}/**end of KwJ14230ReadDataByCommonIdentifier() ****/

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * Sep/02/05     Q.W        mt20u2#17
 * + Baseline - Created from  kw2000 core software package.
 *
\* ============================================================================ */
#endif
