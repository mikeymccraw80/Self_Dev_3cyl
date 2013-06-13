/* ============================================================================ *\
 * kw2srv10m.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv10m.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, March 20, 2003 11:21:56 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $10 -  start diagnostic session (Minimized)
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "kw2api.h"
#include "kw2dll.h"
#include "kw2srv10m.h"


/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */

Kw2000DiagStateType  Kw2000DiagSt ;
uint8_t              Kw2DiagMode ;
uint8_t              Kw2BaudRate ;
bool                 BaudRateChangeRequest ;



/*********************************************************************/
/*  This function returns baud rate value. The input arguement is an */
/*  enumeration depicting the baud rate. This funtion is defined in  */
/*  api file, as the buad rate ranges are application specific.      */
/*  The Keyword 2000 software supports the six baud rates implemented*/
/*  in the function.  This function needs to be modefied if the      */
/*  application does not support all the baud rates.  Remove the     */
/*  'case' statement processing for the unsupported baud rates.      */
/*********************************************************************/
uint32_t GetSrv10BaudRate ( BaudRate_type BaudRate )
{
   uint32_t NewBaudRate ;

   switch (BaudRate)
   {
   /* In the 9.6 k baud rate case */
   case CeBaudRate9p6KB:
        NewBaudRate = CyKw2000BaudRate9p6 ;
        break;

   /*In the 19.2 k baud rate case */
   case CeBaudRate19p2KB:
        NewBaudRate =  CyKw2000BaudRate19p2 ;
        break;

   /* In the 38.4 k baud rate case */
   case CeBaudRate38p4KB:
        NewBaudRate = CyKw2000BaudRate38p4 ;
        break;

   /* In the 57.6 k baud rate case */
   case CeBaudRate57p6KB:
        NewBaudRate = CyKw2000BaudRate57p6 ;
        break;

      /* In the 115.2 k baud rate case */
   case CeBaudRate115p2KB:
        NewBaudRate = CyKw2000BaudRate115p2 ;
        break;

   default:
        NewBaudRate =  CyKw2000BaudRate10p4 ;
        /* Set BaudRate to default 10.4 k baudrate,
         * if incorrect BaudRate request.
         */
        break;
   }
   return NewBaudRate ;
}


/***********************************************************************
* FUNCTION:     ProcessRequest                                         *
*                                                                      *
* TYPE:         Global                                                 *
*                                                                      *
* DESCRIPTION:  Process Keyword 2000 baud rate change.                 *
*                                                                      *
***********************************************************************/
FAR_COS void ProcessRequest ( void )
{

   /* Write the received baud rate in the transmit buffer to
    * prepare the answer data.
    */
   WrtKw2000ServiceData(Kw2BaudRate, CyBaudRateSelect) ;

   /* Change to the desired baud rate.
    * WARNING:  When the tool used this service to change the ECU's
    *           SCI baud rate, the tool's baud rate should be same
    *           as the changed ECU's baud rate, otherwise, the tool
    *           will be lock up and has to reset the ECU to resume
    *           the communication.
    */

   BaudRateChangedSrv10 = true ;
   BaudRateValueSrv10   = GetSrv10BaudRate ( (BaudRate_type) Kw2BaudRate ) ;

   if ( BaudRateValueSrv10 ==  CyKw2000BaudRate10p4 )
   {
      SendStandardNegativeAnswer(nrcRequestOutOfRange) ;
   }
   else
   {
      SendStandardPositiveAnswer (CyPositiveAnswer_WithBaud) ;
   }

}

/***********************************************************************
* FUNCTION:     KwJ14230MiniStartDiagSession   (SERVICE 10)            *
*                                                                      *
* TYPE:         Global                                                 *
*                                                                      *
* DESCRIPTION:  Same as the above file description.                    *
*                                                                      *
***********************************************************************/
FAR_COS void KwJ14230MiniStartDiagSession( void )
{

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
                A reset is necessary for the Change from ProgrammingMode
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
            /* Set Keyword to ECU Programing state */
            SetECUProgrammingSessionState();
            //SetTransferStateToNotTransfering();
            SendStandardPositiveAnswer( CyPositiveAnswer_WithoutBaud);
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
      /*
       * Set Keyword to ECU Programing state
       * Tell other services we are ready for programing
       */
      SetECUProgrammingSessionState();
      //SetTransferStateToNotTransfering();
      Kw2BaudRate = GetKw2000ServiceData(CyBaudRateSelect);
      ProcessRequest () ;
   }
   else
   {
      SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
   }

}


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *
 *
\* ============================================================================ */
