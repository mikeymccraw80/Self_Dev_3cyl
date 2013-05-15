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
* Filename     : kw2srv12.c                                            *
* Project Name : Reusable KW2K                                         *
*                                                                      *
* Applicable   : Keyword Protocol 2000                                 *
* Documents      2000 Implementation of Diagnostic                     *
*                Service 12 Recommended Practice  Vers. 1.1   1-31-97  *
*                                                                      *
* Description  : This module contains the Keyword 2000 Diagnostic      *
*                Service 12 as defined by the above applicable doc.    *
*                                                                      *
* $Source: ems_project@bright...:daewoo_2003:kw2srv12.c $              *
* $Revision: 1.2 $                                                     *
* $Author: brighton $          *
*                                                                      *
************************************************************************
*                                                                      *
* Change Log:                                                          *
*                                                                      *
* Rev.    Date    User    Description of Changes                       *
* ----  --------  ----    ---------------------------------------------*
* 1.1   11-16-98  JZha    Initial file creation                        *
* 1.2   12-14-98  CDW     Added new PID routines                       *
* 1.3   12-15-98  CDW     Fixed new PID routines                       *
* 1.5   01-19-99  JZha    Standardized this file                       *
* 1.6   10-26-99  HFU     Modified for Freeze Frame 1-4, if no DTCs    *
*                         will give negative response.                 *
* 1.7   10-28-99  HFU     Modified for asking all frames, positive     *
*                         response for stored frames, negative         *
*                         response for empty frames.                   *
************************************************************************
* Functions in this file:                                              *
************************************************************************
*  extern:                                                             *
*         void KwJ1423ReadFreezeFrameData( void );                     *
*         void FormAndSendFreezeFrameData (void);                      * 
***********************************************************************/
#include "kw2dll.h"
#include "kw2api.h"
#include "kw2srv12.h"
//#include "cmnpid.h"
//#include "cmndtc.h"

/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
#if 0
/*Define the Msg length, the record access method, the received
 *Frame number position and accsess mothed position in the Msg.
 */
#define SyReadFreezeFrameDataMsgLength  3
#define SyRecordAccessMethod            0
#define SyReceivedFramePosition         1
#define SyReceivedAccsessMethodPosition 2

/*Define the all frame and the number of frames    */
#define Cy14230_Sv12_AllPID             0xff
#define Cy14230_Sv12_FrmNo              4

/*Define the variable to store the received frame number
 * and the current frame number
 */
BYTE Vy14230_S12_FrameToSend;
BYTE Vy14230_S12_CurrentFrame ;


/***********************************************************************
* FUNCTION:  KwJ1423ReadFreezeFrameData         (Service  12)          *
*                                                                      *
*                                                                      *
* Description: This function processes incoming service 12 request     *
*              and if all conditions are fulfilled allows access       *
*              to freeze frame data which was captured and stored as   *
*              a result of diagnostics trouble codes being set.        *
*              This mode can result in one or more mode52 responses    *
*                                                                      *
************************************************************************
* Last modified on: 01/19/99              by: John Zha                 *
***********************************************************************/
/* To read the freeze Frame Data in the kw2pids table                 */
void KwJ1423ReadFreezeFrameData( void )
{
  BYTE idx;
  TbBOOLEAN DTC_Check = CbFALSE;
  /* Check if the recieved data is a correct format.  If it is not,      */
  /* an error message 0x12 - SubFunctionNotSupported_InvalidFormat will  */
  /* be sent.                                                            */
  
  if (GetKeyword2000ServiceDataLength() != 
       SyReadFreezeFrameDataMsgLength )      
  {
    SendStandardNegativeAnswer(
    nrcSubFunctionNotSupported_InvalidFormat);
  }
  
  else if ( (GetKw2000ServiceData(SyReceivedAccsessMethodPosition) != 
             SyRecordAccessMethod) ||
            ((GetKw2000ServiceData(SyReceivedFramePosition) !=
             Cy14230_Sv12_AllPID) &&
            (GetKw2000ServiceData(SyReceivedFramePosition) >
             Cy14230_Sv12_FrmNo)) )
  {
    SendStandardNegativeAnswer(nrcRequestOutOfRange);
  }
  
  else  
  {
    for (idx = 0; idx <= Cy14230_Sv12_FrmNo; idx++)
    {
       SetRequestedFrame ( idx );
       if(Get_Freeze_Frame_DTC( GetRequestedFrame() ) != 0)
         DTC_Check = CbTRUE;
    }
    if ( DTC_Check )
    {
     /* If the received data has correct format, then load the received */
     /* Frame number into the local variable.                           */
      Vy14230_S12_FrameToSend = 
                  GetKw2000ServiceData(SyReceivedFramePosition);

     /* If it request all frames, start from the frame 00               */
      if(Vy14230_S12_FrameToSend == Cy14230_Sv12_AllPID)
        {
         Vy14230_S12_CurrentFrame = 0;
         SetRequestedFrame ( 0 );
        }
      else
        {
        /* If it request one frame, load the frame number to the       */
        /* Current frame                                               */
         Vy14230_S12_CurrentFrame = Vy14230_S12_FrameToSend;
         SetRequestedFrame( Vy14230_S12_CurrentFrame );
        }

        /* Call the function FormAndSendFreezeFrameData() to send      */
        /* the Freeze frame data.                                      */
         FormAndSendFreezeFrameData();
    }
    else
    {
    SendStandardNegativeAnswer(nrcRequestOutOfRange);
    }  
  }
}/*** End of KwJ14230ReadFreezeFrameData ***/


/**************************************************************************/
/* FUNCTION:   FormAndSendFreezeFrameData                                 */
/*                                                                        */
/* TYPE:         global                                                   */
/*                                                                        */
/* DESCRIPTION:  This function send the all freeze frame PID's data       */
/*               This function send out one freeze frame PID's data       */
/*               once each invokation, there will be totally 5 freeze     */
/*               Frame for U2 package to use, which means 4 mutiple       */
/*               responses. In every response, the data length is one byte*/
/*               which means there will be at last 64*4 data bytes( 64 is */
/*               the max PID numbers for one freeze frame , and 4 bytes is*/ 
/*               the max data length of one freeze frame PID.)            */
/*                                                                        */
/**************************************************************************/
/* Last modified on: 01/19/99              by: John Zha                   */
/**************************************************************************/
void FormAndSendFreezeFrameData (void)                   
{ 
 /* Define a local variable to index the data location */
 BYTE LyRespDataCnt = 1;

 /* Load the Minimum PID as the current PID */
 BYTE VeDIAG_M12_CurrentPID = GetMinPIDtableIndex(); 

 if(Get_Freeze_Frame_DTC( GetRequestedFrame() ) != 0) 
 {
    /* Write the current frame number into the transmit buffer 
     * to prepare the response data.
     */ 
    WrtKw2000ServiceData( Vy14230_S12_CurrentFrame, LyRespDataCnt++) ;

    /* Get all freeze data from the PID table */
    while ( VeDIAG_M12_CurrentPID <  GetMaxPIDTableIndex())
    {   
       /*
        * Check for requested PID supported 
        */
       if(CheckDIAG_Reqstd_PID_Supported( VeDIAG_M12_CurrentPID ,
                                          MaskMode_12 ))
       {
         /*
          *Write the PID number into the transmit buffer 
          */
          WrtKw2000ServiceData( GetPIDNumberHighByte( VeDIAG_M12_CurrentPID ),
                                LyRespDataCnt++ );
  
          WrtKw2000ServiceData( GetPIDNumberLowByte( VeDIAG_M12_CurrentPID ),
                                LyRespDataCnt++ );   

         /*
          * Load Transmit data buffer with PID Data and update buffer index
          */ 
          LyRespDataCnt = ProcessReqstdPIDData( GetWrtbufferAddr() ,  
                                                LyRespDataCnt ,
                                                VeDIAG_M12_CurrentPID ) ;
        }
       /*Increase the PID number */
        VeDIAG_M12_CurrentPID++ ;
     }


     /* Write the accsess method to the transmit buffer to prepare the
      * data.
      */
      WrtKw2000ServiceData( 
      GetKw2000ServiceData(SyReceivedAccsessMethodPosition), LyRespDataCnt++ );  
  
     /* Send out the positive response. */
      SendStandardPositiveAnswer( LyRespDataCnt );
 }
 else
 {
    SendStandardNegativeAnswer(nrcRequestOutOfRange);
 }
 
 /* If the Frame number is for all frame, then increase the current frame number
  * untill to the maxmum Frame number and set the multiresponse flag.
  */
 if ( Vy14230_S12_FrameToSend == Cy14230_Sv12_AllPID )
 { 
   WrtMultiRespInProgress( CbTRUE  ) ;
   /* Go to the next frame */
   Vy14230_S12_CurrentFrame++;
   SetRequestedFrame ( Vy14230_S12_CurrentFrame );

   if(Vy14230_S12_CurrentFrame > Cy14230_Sv12_FrmNo )
   {
     /* If the Frame number reached the maxmum number defined by the user,
      * then disabled the multiresponse flag.
      */
     WrtMultiRespInProgress( CbFALSE  ) ;
   }
 }
}
#endif


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 30/03/05     Q.W          294
 * + Baseline - Created from  kw2000 core software package.
 *
\* ============================================================================ */
