#ifndef KW2SRV37_H 
#define KW2SRV37_H
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
* Filename     : kw2srv37.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents      Implementation of Diagnostic Services                 *
*                Recommended Practice  Vers. 1.1   1-31-97             *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 37.  This service is used by the client to    *
*                terminate a data transfer between client and server.  *
*                Service 36 performs the data transfer function.       *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2003:kw2srv37.h $              *
* $Revision$                                                     *
* $Author: brighton $           *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   12-10-98  IAJ     Initial file creation                        *
* 1.2   01-11-99  IAJ     Changed the function header.                 *
************************************************************************
* Functions in this file:                                              *
*         KwJ14230RequestTransferExit                                  *
***********************************************************************/
 
void  KwJ14230RequestTransferExit ( void );

#endif
