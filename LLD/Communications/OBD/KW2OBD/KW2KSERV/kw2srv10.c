/* ============================================================================ *\
 * kw2srv10.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv10.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, June 18, 2002 9:01:19 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $10 -  start diagnostic session
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */


#include "kw2app.h"
#include "kw2srv10m.h"
#include "kw2srv10.h"
#include "kw2srv36.h"
#include "kw2api.h"

bool      Utility_Download_Flag;
/***********************************************************************
* FUNCTION:     KwJ14230StartDiagnosticSession   (SERVICE 10)          *
*                                                                      *
* TYPE:         Global                                                 *
*                                                                      *
* DESCRIPTION:  Same as the above file description.                    *
*                                                                      *
***********************************************************************/
void KwJ14230StartDiagnosticSession( void )
{
    Utility_Download_Flag = true;

   /* Define the local variables to store the diagnostic mode and
    * the baud rates.
    */

   /* Get the Diagnostic mode from the received data */
   Kw2DiagMode = GetKw2000ServiceData(CyDiagnosticMode);

   /* Write the received diagnostic mode into the transmit buffer
    * to prepare the answer data.
    */
   WrtKw2000ServiceData(Kw2DiagMode,CyDiagnosticMode) ;
   BaudRateChangedSrv10 = false ;
   BaudRateChangeRequest = false ;

   /* Check for correct number of data bytes in the request msg. */
   if (( GetKeyword2000ServiceDataLength()  !=
         CyStartDiagMsgLength_WithBaud )    &&
       ( GetKeyword2000ServiceDataLength()  !=
         CyStartDiagMsgLength_WithoutBaud ))
   {
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
   }

   /* The number of the Msg data bytes is correct, Ckeck if it is without
    * baud rate changing (the number of the receved data bytes are 2).
    */

   else if (GetKeyword2000ServiceDataLength() ==
            CyStartDiagMsgLength_WithoutBaud )
   {
      switch (Kw2DiagMode)
      {
         case CyStandardDiagnosticMode:  /* Mode 81 */
             /* If the current mode is ProgrammingMode, do reset,
                otherwise Change the baud rate to default value.
                A reset is necessary for the Change form ProgrammingMode
                to DiagnosticMode.
                */
            if ( CheckProgrammingState () )
            {
               SetECUResetPending(true) ;
            }
            else
            {
               BaudRateChangedSrv10  = true ;
               SetStandardDiagnosticState() ;
               BaudRateValueSrv10    =  CyKw2000BaudRate10p4 ;
            }

            SendStandardPositiveAnswer (CyPositiveAnswer_WithoutBaud) ;
            break;

      case CyECUProgrammingMode:      /* Mode: 85 */
           /* First check to see if the ECU is unlocked */

            if (!GetVulnerabilityState () )
//           if ( !IsDevelopmentOrManfModeActive() )

            {
               SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested );
            }
            else
            {
               /* Check if the engine is running.          */
               if (!GetAppRdyForPrograming() )
               {
                  /* set responce pending flag to process App timers */
                  SetAppResponsePending() ;
               }
               else
               {
                  /*
                   * Set Keyword to ECU Programing state
                   * Tell other services where ready for programing
                   * Clear responce pending
                   */
                  SetECUProgrammingSessionState();
                  SetTransferStateToNotTransfering();
                  ClrAppResponsePending() ;
                  SendStandardPositiveAnswer( CyPositiveAnswer_WithoutBaud);
               }
            }
            break;

      default:

            SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
            break;
      }
   }
   /* Check to see if additional Baudrate Identifier is requested for
    * the ECUProgrammingMode (0x85) .
    * If the number of the received data bytes are 3 and it is in
    * the ECU Programming state.
    */
   else if (Kw2DiagMode == CyECUProgrammingMode)
   {
      /* First check to see if the ECU is unlocked */

      if (!GetVulnerabilityState () )
//     if ( !IsDevelopmentOrManfModeActive() )
      {
         SendStandardNegativeAnswer( nrcSecurityAccessDenied_SecurityAccessRequested );
      }
      else if (!GetAppRdyForPrograming() )
      /* Check if the engine is running.          */
      {
         /* set responce pending flag to process App timers */
         SetAppResponsePending() ;
         /* Get requested kw2BaudRate and process it */
         Kw2BaudRate = GetKw2000ServiceData(CyBaudRateSelect);
         BaudRateChangeRequest = true ;

      }
      else
      {
         /*
          * Set Keyword to ECU Programing state
          * Tell other services we are ready for programing
          * Clear responce pending
          */
         SetECUProgrammingSessionState();
         SetTransferStateToNotTransfering();
         ClrAppResponsePending() ;
         Kw2BaudRate = GetKw2000ServiceData(CyBaudRateSelect);
         ProcessRequest () ;
      }
   }
   else
   {
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
   }

} /*** End of StartDiagnosticSession ***/


/***********************************************************************
* FUNCTION:     KwJ14230ProcessDelayedResponce   (SERVICE 10)          *
*                                                                      *
* TYPE:         Global                                                 *
*                                                                      *
* DESCRIPTION:  Same as the above file description.                    *
*                                                                      *
***********************************************************************/
void  KwJ14230ExecuteService10NextResponse( void )
{

   ClrAppResponsePending () ;
   if (GetAppRdyForPrograming() )
   {
      SetECUProgrammingSessionState();
      if ( !BaudRateChangeRequest )
      {
         SendStandardPositiveAnswer( CyPositiveAnswer_WithoutBaud ) ;
      }
      else
      {
         BaudRateChangeRequest = false ;
         ProcessRequest () ;
      }
   }
   else
   {
      SendStandardNegativeAnswer( nrcConditionsNotCorrect_RequestSequenceError ) ;
   }
}

FAR_COS void InitKwJ14230StartDiagnosticSession(void )
{
   if ( IsDevelopmentOrManfModeActive() )
   {
      /* in a development unit, unlock the security */
      UnlockSecurityAccess();
   }
}


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
\* ============================================================================ */
