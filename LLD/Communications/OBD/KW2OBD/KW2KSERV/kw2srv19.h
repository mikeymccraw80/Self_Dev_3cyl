#ifndef KW2SRV19_H 
#define KW2SRV19_H
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
* Filename     : kw2srv18.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents       What document........?                               *
*                                                                      *
* Description  : This module implements the Keyword 2000 protocol      *
*                service 19.  The service 19 request searches the DTC  *
*                (Diagnostic Trouble Codes) list.  The input request   *
*                provides a status mask byte with intended bits set.   *
*                The output is the list of DTC's whose at least one    *
*                status bit is set corresponding to the input mask bits*
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2003:kw2srv19.h $              *
* $Revision$                                                     *
* $Author: brighton $             *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   06-08-99  IAJ     Initial file creation                        *  
************************************************************************
* Functions in this fille.                                             *
*        KwJ14230ReadStatusOfDiagnosticTroubleCodesByStatus            *
*        FormAndLoad14230_Mode_59_Data                                 *
*                                                                      *
***********************************************************************/
 #if 0
extern void KwJ14230ReadStatusOfDiagnosticTroubleCodesByStatus ( void );
extern void FormAndLoad14230_Mode_59_Data ( void );
#endif
#endif

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 12/04/05     Q.W         294
 * + Baseline - Created for the U2 program.
\* ============================================================================ */

