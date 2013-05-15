#ifndef KW2SRV34_H 
#define KW2SRV34_H
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
* Filename     : kw2srv34.h                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents      Implementation of Diagnostic Services                 *
*                Recommended Practice  Vers. 1.1   1-31-97             *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 34. The service 34 is used by the client to   *
*                initiate a data transfer from the client to the       *
*                server (download).  After the server has received the *
*                message, the controller shall take all necessary      *
*                actions to receive data, before it sends a positive   *
*                response message. The actual transfer of data occurs  *
*                during the service 36.                                *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2003:kw2srv34.h $              *
* $Revision$                                                     *
* $Author: brighton $           *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-17-98  IAJ     Initial file creation                        *
* 1.2   12-23-98  IAJ     Changed the .c file.                         *
* 1.3   01-07-99  IAJ     Changed the header.                          *
* 1.4   01-21-99  IAJ     Changed the .c file.                         *
************************************************************************
* Functions in this fille.                                             *
*         KwJ14230RequestDownload                                      *
***********************************************************************/
 
extern void  KwJ14230RequestDownload ( void );

#endif
