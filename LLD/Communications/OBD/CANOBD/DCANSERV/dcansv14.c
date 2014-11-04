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
* Filename     : dcansv14.c                                            *
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
***********************************************************************/
#include "dcansv14.h"
#if (XeDCAN_SID_14_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlfdtc.h"/*ClearDiagnosticData()*/
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
/*** LnDiag service: LnClearDiagnosticInformation     (SID14)              ***/
/**********************************************************************/
void LnClearDiagnosticInformation (void)
{
   uint32_t  groupOfDTC;
   if ((GetLnServiceDataLength () != 4))
   {/*--- No parameter for this request ID ---*/
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      groupOfDTC = (((uint32_t )(GetLnServiceData ()) [1])<<16) | 
                 (((uint16_t )(GetLnServiceData ()) [2])<<8) |
                 (GetLnServiceData ()) [3];               
      if((groupOfDTC == 0xffffff))
      {
         ClearDiagnosticData ();
         SendLnStandardPositiveAnswer (1);
      } 
      else
      {
         SendLnStandardNegativeAnswer (RequestOutOfRange); 
      }
   }
} /*** End of LnClearDiagnosticInformation ***/

#endif

