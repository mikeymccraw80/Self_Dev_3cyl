#ifndef KW2SRV11_H
#define KW2SRV11_H

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
* Filename     : kw2srv11.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000, Ver. 1.0, August 3 1998        *
* Documents                                                            *
*                                                                      *
* Description  : This mode included the Service 11 extern function.    *
*                                                                      *
* $Source: ems_project@brighton.tcb:daewoo_2003:kw2srv11.h $
* $Revision: 1.2 $
* $Author: brighton $
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   12-18-98  cdw     Initial file creation                        *
* 1.2   01-21-99 JZha     Standardized this file.                      *
* 1.3   01-22-99  CDW     Added ECU reset and Get function             *
* 1.5   01-25-99 JZha     Redesign the Service 11 function to match    *
*                         the spec.                                    *
* 1.6   03-20-00 IAJ      Moved the inline functions to the DLL file.  *
************************************************************************
* Functions in this file:                                              *
************************************************************************
* extern:                                                              *
*         void KwJ14230EcuReset( void ) ;                              *
***********************************************************************/

/*********************************************************************/
/*                  GLOBAL VARIABLES DECLARATIONS                    */
/*********************************************************************/

/*********************************************************************/
/*                  EXTERN FUNCTION DECLARATIONS                     */
/*********************************************************************/

void KwJ14230EcuReset( void ) ;

#endif
