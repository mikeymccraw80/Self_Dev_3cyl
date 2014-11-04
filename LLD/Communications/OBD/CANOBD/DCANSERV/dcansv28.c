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
* Filename     : dcansv28.c                                            *
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
* 1.2   03-12-11  cjqq    Added new subfunction                        *
* 4     03-07-12  cjqq    fix the bug of no action when                *
*                         suppressPosRespMsgIndicationBit =1.          *
***********************************************************************/

#include "dcansv28.h"
#if (XeDCAN_SID_28_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdltype.h"/*LnDiagSvFlagsType*/
#include "obdlfsrv.h"/*VbDiagServicesDisableAPPTx*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcancomm.h"
#include "obdsfapp.h"
/***********************************************************************
* Functions in this file:                                              *

***********************************************************************/

/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/

/**********************************************************************/
/*** LnDiag service: LnCommunicationControl                     ***/
/**********************************************************************/
void LnCommunicationControl (void)
{
   uint8_t   subFunction;
   uint8_t   CommunicationType;
   bool      suppressPosRespMsgIndicationBit;

   subFunction                     = ((GetLnServiceData ()) [1] & 0x7f);
   suppressPosRespMsgIndicationBit = ((GetLnServiceData ()) [1]  & 0x80) ? true: false;
   CommunicationType               = (GetLnServiceData ()) [2] ;
   if (GetLnServiceDataLength() != 3)
   {
      SendLnStandardNegativeAnswer(IncorrectMessageLength);
   }  
  else if(((0x04 <= subFunction) && (subFunction <= 0x3f)) ||
       (0x7f == subFunction))
   {
        /* This sub function is reserved and should not be used */
      SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
 
   }
   else if(  (CommunicationType == 0) || ((CommunicationType & 0x0c) != 0)) 
   {
        /* The value 0 for CommunicationType is reserved */
        /* Bit 2,3 of CommunicationType are reserved and should always be zero. */
      SendLnStandardNegativeAnswer(RequestOutOfRange);
   }
   else
   {
      switch ( subFunction )
      {
         case EnableRxAndTx:
            if ( CommunicationType & AppCommunicationType )
            {
			     #ifdef OBD_CONTROLLER_IS_MT80
				  EnableCANHNetwork(); 
                  EnableCANHRec() ;
				 #else				  
                  EnableCANH_Send_By_OBD(); 
                  EnableCANH_Receive_By_OBD() ;
				 #endif
               if ( !suppressPosRespMsgIndicationBit ) 
               {
                  SendLnStandardPositiveAnswer(2);
               }
               else
               {
                  PfrmDCAN_AckReqWithoutResponse ();
               }
            }
            else
            {
               SendLnStandardNegativeAnswer(RequestOutOfRange);
            }
         break;
         case EnableRxAndDisableTx:	
            if ( CommunicationType & AppCommunicationType )
            {
                 #ifdef OBD_CONTROLLER_IS_MT80
				  DisableCANHNetwork();
                  EnableCANHRec() ;
				 #else
				  DisableCANH_Send_By_OBD();
                  EnableCANH_Receive_By_OBD() ;
				 #endif
               if ( !suppressPosRespMsgIndicationBit ) 
               {
                  SendLnStandardPositiveAnswer(2);
               }
               else
               {
                  PfrmDCAN_AckReqWithoutResponse ();
               }
            }
            else
            {
               SendLnStandardNegativeAnswer(RequestOutOfRange);
            }
         break;
         case DisableRxAndEnableTx:
            if ( CommunicationType & AppCommunicationType )
            {
                 #ifdef OBD_CONTROLLER_IS_MT80
				  EnableCANHNetwork();
                  DisableCANHRec();
				 #else
				  EnableCANH_Send_By_OBD();
                  DisableCANH_Receive_By_OBD();
				 #endif
               if ( !suppressPosRespMsgIndicationBit ) 
               {
                  SendLnStandardPositiveAnswer(2);
               }
               else
               {
                  PfrmDCAN_AckReqWithoutResponse ();
               }
            }
            else
            {
               SendLnStandardNegativeAnswer(RequestOutOfRange);
            }	 
         break;
         case DisableRxAndTx:
            if ( CommunicationType & AppCommunicationType )
            {
                 #ifdef OBD_CONTROLLER_IS_MT80 
				  DisableCANHNetwork();
                  DisableCANHRec();
				 #else
				  DisableCANH_Send_By_OBD();
                  DisableCANH_Receive_By_OBD();
				 #endif
               if ( !suppressPosRespMsgIndicationBit ) 
               {
                  SendLnStandardPositiveAnswer(2);
               }
               else
               {
                  PfrmDCAN_AckReqWithoutResponse ();
               }
            }
            else
            {
               SendLnStandardNegativeAnswer(RequestOutOfRange);
            }
	  break;
      }
   }
}/*** End of LnCommunicationControl ***/

#endif


