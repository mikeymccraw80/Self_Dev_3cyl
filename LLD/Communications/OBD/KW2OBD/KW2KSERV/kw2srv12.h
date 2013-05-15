#ifndef KW2SRV12_H
#define KW2SRV12_H 

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
* Filename     : kw2srv12.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 12 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 12 related extern and inline functions as     *
*                defined by the above applicable doc.                  *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2003:kw2srv12.h $              *
* $Revision$                                                     *
* $Author: brighton $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-16-98  JZha    Initial file creation                        *
* 1.3   01-19-98  JZha    Standardized this file                       *
************************************************************************
* Functions in this file:                                              *
************************************************************************
*  extern:                                                             *
*         BYTE Vy14230_S12_CurrentFrame;                               *
*         void KwJ1423ReadFreezeFrameData( void );                     *
*         void FormAndSendFreezeFrameData (void);                      *
*  inline:                                                             *
*         static BYTE GetS12_CurrentFrame( void );                     *
*                                                                      *
***********************************************************************/

/*********************************************************************/
/*                  EXTERN FUNCTION DECLARATIONS                     */
/*********************************************************************/
#if 0
extern BYTE Vy14230_S12_CurrentFrame;
extern void KwJ1423ReadFreezeFrameData( void );
extern void FormAndSendFreezeFrameData (void);

/*********************************************************************/
/*                  INLINE FUNCTION DECLARATIONS                     */
/*********************************************************************/
#endif


#endif

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 30/03/05     Q.W          294
 * + Baseline - Created from  kw2000 core software package.
 *
\* ============================================================================ */
