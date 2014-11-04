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
* Filename     : dcansvb0.c                                            *
*                                                                      *
* Applicable   : CANOBD                                *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 10 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This service is only used for specific test purposes      *
*                                                                      *
* $Source:                                                        *
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
#include "dcansvb0.h"
#if (XeDCAN_SID_B0_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/

/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
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

/**********************************************************************/
/*** LnDiag service: TestService    (SIDb0)                ***/
/**********************************************************************/
void TestService(void)
{
/* Define the local variable to store the reset mode */
  uint8_t    SubFunction;
  uint16_t  MsgLength;

  MsgLength = GetLnServiceDataLength();
  /* Check for correct number of data bytes in the request msg. */
  if ( MsgLength > 32)
  {
    SendLnStandardNegativeAnswer (IncorrectMessageLength);
  }
  else
  {
      SubFunction = (GetLnServiceData ()) [1];
      switch (SubFunction)
      {
         case EchoRequest: /* Mode 01 */ 
            SendLnStandardPositiveAnswer(MsgLength);
         break;
         default:

            SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);

         break;
      }
  }
}
#endif


