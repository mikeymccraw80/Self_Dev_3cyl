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
* Filename     : dcansv10.c                                            *
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
* 1.2   03-12-11  cjqq    fixed the bug about lock security access     *
*                 when change reprogram session to extend session      *
* 4     07-31-12  azh     Add Kostal PEPS IMMO interface               *
* 5     05-09-13  xll     enable CAN_OBD commucation after tester present timeout.
* 6     09-26-13  xll     Lock security access when transitions from   *
*                         none default session                         *
* 7     14-01-24  xll     Modified function ChangeSession().           *
***********************************************************************/

#include "dcansv10.h"
#if (XeDCAN_SID_10_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
// #include "obdsfexi.h"
// #include "ofvcpall.h"/*ClearOFVC_AllDeviceControlParameters*/
#include "obdltype.h"/*LnDiagSvFlagsType*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcansv2a.h"/*ClearAndDisableAllDpids()*/
#include "dcanserv.h"
#include "dcancomm.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************
* void KwJ14230StartDiagnosticSession( void );                         *
* void KwJ14230ExecuteService10NextResponse( void );                   *
***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
//volatile LnDiagSvFlagsType      LnDiagSvFlags;


/**********************************************************************/
/*** Lock Security Access.                                          ***/
/**********************************************************************/
static void LockSecurityAccess_DCAN (void)
{
   LnDiagSvFlags.SecurityAccessUnlocked = false;
} /*** End of LockSecurityAccess ***/

/**********************************************************************/
/*** ChangeSession                                         ***/
/**********************************************************************/
void ChangeSession(uint8_t newSession)
{ 
   if (DS_Sessions[CurrentSessionIndex].Type == DefaultSession)
   {
      if (newSession == DefaultSession)
      {
            /* 1 */
         // ClearOFVC_AllDeviceControlParameters();
      }     
      else
      {
           /*
             * When service 0x86 is implemented the following
             * function needs to be added: ResetService86Events
             */
      }
   } 
   else
   {  
   	  LockSecurityAccess_DCAN ();
	  SPS_Security_Key_Allowed = CbFALSE;
      if (newSession != DefaultSession)
      {
            /* 3 */
            /*
             * When service 0x86 is implemented the following
             * function needs to be added: ResetService86Events
             */
      }     
      else
      {
            /* 4 */
            /*
             * When service 0x86 is implemented the following
             * function needs to be added: ResetService86Events
             */
         ClearIMMO_SecurityUnlockStatus();
         // VbDiagServicesDisableDTCs = CbFALSE;
         ClearOFVC_AllDeviceControlParameters();
	     ClearAndDisableAllDpids ();
		 EnableCANH_Receive_By_OBD();
         EnableCANH_Send_By_OBD();
      }
   
   }
}

/**********************************************************************/
/*** LnDiag service: LnDiagnosticSessionControl  (SID10)                  ***/
/**********************************************************************/
void LnDiagnosticSessionControl (void)
{
   uint8_t sessionType;
   uint8_t sessionIndex;
   bool  suppressPosRespMsgIndicationBit;
   bool  found = false;
   uint8_t msglength;
   if(GetLnServiceDataLength () != 2)
   {
       SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      suppressPosRespMsgIndicationBit = ((GetLnServiceData ()) [1] & 0x80) ? true : false;
      sessionType = ((GetLnServiceData ()) [1] & 0x7f);
      sessionIndex=0;
      msglength=1;
      while((sessionIndex<DS_NUMBER_OF_SESSIONS) && !found)
      {
         if(sessionType == DS_Sessions[sessionIndex].Type)
         {
            found = true;
         }
         if(!found)
         {
            sessionIndex++;
         }
      }
      if(!found)
      {
         SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
      }
      else
      {
         if(sessionType != DefaultSession) 
         {
            S3ServerTimer = C_R7p8125ms16 (DS_S3SERVER_TIME);
         }
         ChangeSession(sessionType);
         CurrentSessionIndex = sessionIndex;

         if( suppressPosRespMsgIndicationBit )
         {
           PfrmDCAN_AckReqWithoutResponse ();
         }
         else 
         {
            WrtDCAN_ServiceData( sessionType,msglength++ ) ;	
            WrtDCAN_ServiceData( (((DS_Sessions[CurrentSessionIndex].P2ServerMax)>>8) & 0xff),
	   	                    msglength++ ) ;
            WrtDCAN_ServiceData( ((DS_Sessions[CurrentSessionIndex].P2ServerMax) & 0xff),
	   	                    msglength++ ) ;
            WrtDCAN_ServiceData( (((DS_Sessions[CurrentSessionIndex].P2SServerMax)>>8) & 0xff),
	   	                    msglength++ ) ;
            WrtDCAN_ServiceData( ((DS_Sessions[CurrentSessionIndex].P2SServerMax) & 0xff),
	   	                    msglength++ ) ;
            SendLnStandardPositiveAnswer(msglength);
        
         }
      }
   }
}
#endif


