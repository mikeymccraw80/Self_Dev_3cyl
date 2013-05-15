#ifndef KW2KFAPI_H
#define KW2KFAPI_H
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
* Filename     : kw2kfapi.h                                             *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents                                                            *
* Version      : 1.1                                                   *
* Date         : April 14 1998                                         *
*                                                                      *
* Purpose      : API for Keyword 2000 serial communication.     *
*                                                                      *
* Description  : This module is the executive for running Keyword      *
*                2000 routines from the back ground task               *
*                                                                      *
* $Source: ems_project@bright...:daewoo_2002:kw2exec.h $               *
* $Revision: 1.1 $                                                     *
* $Author: brighton.tcb:/users/saf...o_2002_MathLib:safayyad $         *
* Creation Date: APR 7th 1997                                          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.0   01-10-10  cwe     Initial file creation                        *
************************************************************************
*                                                                      *
* External variables and constants referenced, and why:                *
*          NAME                DECLARED IN     REASON/PURPOSE          *
*                                                                      *
************************************************************************
* Functions in this file:                                              *
************************************************************************
*                                                                      *
***********************************************************************/
 
//bool KW2K_GetCommunicationActiveState( void );
//uint8_t* KW2K_GetServiceData(void );
FAR_COS void KW2K_SendStandardNegativeAnswer( uint8_t  in_location);
FAR_COS void KW2K_SendStandardPositiveAnswer(uint8_t  in_location);
void PostOFVC_KWResponseToRequest (void) ;
#endif

