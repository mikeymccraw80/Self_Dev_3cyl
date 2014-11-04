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
* Filename     : dcansv3e.c                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : CANOBD                                *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 10 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 10 as the defined by the above applicable doc.*
*                                                                      *
*                Set the keyword 2000 diagnostic mode to be the        *
*                Standard Diagnostitic State or to be the              *
*                ECU Programming State by the request message.         *
*                In the ECU Programming State, this service can change *
*                the communication baud rate to be the desired baud    *
*                rate.                                                 *
*                                                                      *
* $Source: ems_project@brigh...:daewoo_2002:kw2srv10.c $              *
* $Revision$                                                     *
* $Author: brighton.tcb:/users/sa..._2002_MathLib:safayyad $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-12-98  JZha    Initial file creation                        *
******************************************************************************/
#include "dcansv3e.h"
#if (XeDCAN_SID_3E_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcancomm.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************

***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
/**********************************************************************/
/*** LnDiag service: TesterPresent        (SID3E)                          ***/
/**********************************************************************/
void LnTesterPresent (void)
{
   bool suppressPosRespMsgIndicationBit;
   uint8_t  subFunction;
   if(GetLnServiceDataLength () != 2)
   {
        /* Request should be 2 bytes long */
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      suppressPosRespMsgIndicationBit = ((GetLnServiceData ()) [1] & 0x80) ? true: false;
      subFunction = ((GetLnServiceData ()) [1] & 0x7f);
      if( subFunction != 0x00 )
      {
        /* Sub function is not supported */
         SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
      }
      else if( suppressPosRespMsgIndicationBit )
      {
         PfrmDCAN_AckReqWithoutResponse();
      }
      else 
      {
         SendLnStandardPositiveAnswer (2);
      }
   }
}

#endif




