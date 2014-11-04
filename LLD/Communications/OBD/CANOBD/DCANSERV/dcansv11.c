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
* Filename     : dcansv11.c                                            *
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
* 2     04-09-12  cjqq    Update the CANOBD per customer requirement   *
***********************************************************************/
#include "dcansv11.h"
#if (XeDCAN_SID_11_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlfsrv.h"/*SetECUResetPending()*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcanserv.h"
#include "dcancomm.h"
/******************************************************************************
* CORE Include Files
******************************************************************************/
// #include "viosprpm.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************
* void KwJ14230StartDiagnosticSession( void );                         *
* void KwJ14230ExecuteService10NextResponse( void );                   *
***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/

/**********************************************************************/
/*** LnDiag service: LnEcuReset    (SID11)                ***/
/**********************************************************************/
void LnEcuReset (void)
{
/* Define the local variable to store the reset mode */
  uint8_t  ResetMode;
  bool      suppressPosRespMsgIndicationBit;
   
  suppressPosRespMsgIndicationBit = ((GetLnServiceData ()) [1]  & 0x80) ? true: false;
  ResetMode = ((GetLnServiceData ()) [1] & 0x7f);
  /* Check for correct number of data bytes in the request msg. */
  if ( GetLnServiceDataLength()  != 2)
  {
    SendLnStandardNegativeAnswer (IncorrectMessageLength);
  }
  else if(GetVIOS_n_EngSpd() > V_RPM(200))
  {
    SendLnStandardNegativeAnswer(ConditionsNotCorrectOrRequestSequenceError);
  }
  else
  {
     switch (ResetMode)
     {
        case SubFuncSWReset: /* Mode 03 */ 
           if ( !suppressPosRespMsgIndicationBit ) 
           {
               SendLnStandardPositiveAnswer(2);
           }
           else
           {
               PfrmDCAN_AckReqWithoutResponse ();
           }
           SetECUResetPending(CbTRUE);
           break;
#ifdef XeSID11_01_HardwareReset == CeSYST_AVAILABLE
   case SubFuncHWReset: /* Mode 01 */ 
           if ( !suppressPosRespMsgIndicationBit ) 
           {
               SendLnStandardPositiveAnswer(2);
           }
           else
           {
               PfrmDCAN_AckReqWithoutResponse ();
           }
           SetECUHWResetPending(CbTRUE);
           break;
#endif
        default:
           SendLnStandardNegativeAnswer(SubFunctionNotSupported_InvalidFormat);
           break;
     }
  }
}
#endif


