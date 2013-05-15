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
* Filename     : kw2srv19.c                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents       What document........?                               *
*                                                                      *
* Description  : This module implements the Keyword 2000 protocol      *
*                service 19.  The service 19 request searches the DTC  *
*                (Diagnostic Trouble Codes) list.  The input request   *
*                provides a status mask byte with intended bits set.   *
*                The output is the list of DTC's whose at least one    *
*                status bit is set corresponding to the input mask bits*
*                                                                      *
*                                                                      *
* $Source: ems_project@bright...:daewoo_2003:kw2srv19.c $              *
* $Revision: 1.2 $                                                     *
* $Author: brighton $             *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   06-08-99  IAJ     Initial file creation                        *
* 1.2   08-27-99  HFU     Restructured the service, make it less time  *
*                         in each response. Include file kw2srv18.h    *
* 1.3   10-28-99  HFU     For invalid Group ID and invalid DTC ID      *
*                         give negative response.                      *
************************************************************************
* Functions in this fille.                                             *
*        KwJ14230ReadStatusOfDiagnosticTroubleCodesByStatus            *
*        FormAndLoad14230_Mode_59_Data                                 *
***********************************************************************/
#if 0
#include "kw2dll.h"
#include "kw2srv19.h"
#include "kw2srv18.h"
#include "cmndtc.h"

#define Sy14230_MODE_19_MSG_LENGTH  (4)
/* The first two bytes of transmit buffer are Response Id and
   number of DTC's.  The remaining are the DTC info */
#define TestMaxDataSize             (MaxiServiceDataSize - 2)
#define SyTRANSMIT_MSG_BUFF_OFFSET_BYTE1   (1)
#define SyTRANSMIT_MSG_BUFF_OFFSET_BYTE2   (2)
#define SyTRANSMIT_MSG_BUFF_OFFSET_BYTE0   (0)

typedef struct 
{
  BYTE DTC_Count;            /*  number of DTCs */    
  BYTE TrByteCount;         /* transfer count*/
  WORD DTC_Values;         /*  DTC enum number value */
  BYTE ClientRequest;
} Mode19_Counters_Type;
 
Mode19_Counters_Type Mode19_Values;

/***********************************************************************
*                                                                      *
* FUNCTION:         KwJ14230ReadStatusOfDiagnosticTroubleCodesByStatus.*
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 19 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
************************************************************************
* Last modified on: 08/27/99              by: Haifan Fu                *
***********************************************************************/
 
void KwJ14230ReadStatusOfDiagnosticTroubleCodesByStatus( void )
{

  enum {
        ReqServiceId,
        ReqDTCTestMask,
        ReqGroupOfDTCHighByte,
        ReqGroupOfDTCLowByte
  } ReadDTCByStatus;

  union DiagGroupType {
    struct BytesType {
    BYTE byte1;
    BYTE byte2;
    } BytesVar;
    WORD WordVar;
  } DiagGroupVar;

  BYTE RequestMask;

  RequestMask = GetKw2000ServiceData ( ReqDTCTestMask );

  DiagGroupVar.BytesVar.byte1 = 
                       GetKw2000ServiceData ( ReqGroupOfDTCHighByte );
  DiagGroupVar.BytesVar.byte2 = 
                       GetKw2000ServiceData ( ReqGroupOfDTCLowByte );
 

  /* If input message length is not equal to 4 or sub-mode is not 
     valid, send negative response.   */
     
     if ( Sy14230_MODE_19_MSG_LENGTH !=
            GetKeyword2000ServiceDataLength() )
     {
        /* Invalid Message format */
        SendStandardNegativeAnswer( 
                       nrcSubFunctionNotSupported_InvalidFormat  ) ;
        /* negative response format:
           Byte #1 : 0x7F
           Byte #2 : 0x18
           Byte #3 : 0x12
           */ 
     }
     else
     {  
       /* Determine the range the DTC's to process */
        DetermineDTCRangeToCheck ( DiagGroupVar.WordVar );
        Mode19_Values.DTC_Count = 0;
        Mode19_Values.DTC_Values = 0;
        Mode19_Values.ClientRequest = RequestMask ;
        Mode19_Values.TrByteCount = SyTRANSMIT_MSG_BUFF_OFFSET_BYTE2;

        /* Calculate the number of DTC's which satisfy the
           requested criteria. */
        NumberOfDTC = Calc_Number_Of_Valid_Mask_DTCs ( RequestMask );

        if (( GetCMNServ18DTCMinValue() == 
              GetCMNServ18DTCMaxValue()) && ( NumberOfDTC == 0 ))
           {
           SendStandardNegativeAnswer( nrcRequestOutOfRange ) ;
           }
        else
           {                   
           WrtMultiRespInProgress( CbTRUE  ) ;        
           }
        
     }
} /*  KwJ14230ReadStatusOfDiagnosticTroubleCodesByStatus  */
 
/***********************************************************************
*                                                                      *
* FUNCTION:          FormAndLoad14230_Mode_59_Data                     *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Biulds the service 19 response message, service   *
*                    Id  59.  It also handles multiple messages.       *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
************************************************************************
* Last modified on: 11/10/99              by: Haifan Fu                *
***********************************************************************/

void FormAndLoad14230_Mode_59_Data ( void )
{
      //DTC_TEST_STATUS_INFO_TYPE DTCRecord, *DTCRecordPtr;
      DTC_TEST_STATUS_INFO_TYPE DTCRecord;
 
        /*  Write NumberOfDTC in transmit buffer */
        WrtKw2000ServiceData( NumberOfDTC, 
                              SyTRANSMIT_MSG_BUFF_OFFSET_BYTE1);
        
        while ( Mode19_Values.DTC_Values < GetCMNMaxNumberOfDTCs() )
        {
          /* Get the next valid DTC information */
           //DTCRecordPtr = Get_Next_Valid_Mask_P_Code ( 
           //                                 Mode19_Values.DTC_Values, 
            //                                Mode19_Values.ClientRequest );
           //DTCRecord = *DTCRecordPtr;
	    DTCRecord = Get_Next_Valid_Mask_P_Code ( 
                                            Mode19_Values.DTC_Values, 
                                            Mode19_Values.ClientRequest );
           if ( DTCRecord.DTC_Valid )
           {
             /* build the message */
              Mode19_Values.DTC_Count++;
              WrtKw2000ServiceData( 
              DTCRecord.DTC_Number.Byte_Access.Byte_One, 
                                           Mode19_Values.TrByteCount++);
              WrtKw2000ServiceData( 
              DTCRecord.DTC_Number.Byte_Access.Byte_Two, 
                                           Mode19_Values.TrByteCount++);
              WrtKw2000ServiceData( 
              DTCRecord.DTC_Status, Mode19_Values.TrByteCount++);
              
              WrtKw2000ServiceData( 
              DTCRecord.DTC_Test_Status, Mode19_Values.TrByteCount++);
              
              
              /* If one DTC information was requested or the transmit
                 buffer limit reached, exit the loop*/
  
              if (( GetCMNServ18DTCMinValue() == 
                                           GetCMNServ18DTCMaxValue()) 
                  ||
                  ( Mode19_Values.TrByteCount >= TestMaxDataSize ))
              {
                 Mode19_Values.DTC_Values++;
                 break;
              }
           }
           Mode19_Values.DTC_Values++;
        }
        
        if (Mode19_Values.TrByteCount > SyTRANSMIT_MSG_BUFF_OFFSET_BYTE1)
          SendStandardPositiveAnswer (Mode19_Values.TrByteCount);
        else
          SendStandardPositiveAnswer (SyTRANSMIT_MSG_BUFF_OFFSET_BYTE0);
        
        /* Test if multiple messages need to be transmitted */
        if (( Mode19_Values.DTC_Values < GetCMNMaxNumberOfDTCs()) &&
            ( Mode19_Values.TrByteCount >= TestMaxDataSize ))
        {
         Mode19_Values.TrByteCount = SyTRANSMIT_MSG_BUFF_OFFSET_BYTE1;
         WrtMultiRespInProgress( CbTRUE  ) ;
        }
        else
        {
         WrtMultiRespInProgress( CbFALSE  ) ;
        }
        
} /* FormAndLoad14230_Mode_59_Data */

#endif
/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 12/04/05     Q.W         294
 * + Baseline - Created for the U2 program.
\* ============================================================================ */

