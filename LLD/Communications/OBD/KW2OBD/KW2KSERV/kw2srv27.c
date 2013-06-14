/* ============================================================================ *\
 * kw2srv27.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv27.c-1:csrc:mt20a#1
 * Revision:        1
 * Creation date:   Tuesday, June 18, 2002 9:01:51 AM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $27 -  Unlock security
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "kw2api.h"
#include "kw2app.h"
#include "kw2dll.h"
#include "kw2cfg.h"
#include "kw2srv10.h"
#include "kw2srv27.h"
// #include "immo_cal.h"
// #include "immo.h"
// #include "immo_exec.h"

#define SyRequestForSeed                    (0x01)
#define SySendKey                           (0x02)
#define SyRequestForL2Seed                  (0x03)
#define SySendL2Key                         (0x04)
#define Sy14230_MODE_27_MSG01_LENGTH        (2)
#define Sy14230_MODE_27_MSG02_LENGTH        (4)
#define Sy14230_MODE_27_MSG03_LENGTH        (2)
#define Sy14230_MODE_27_MSG04_LENGTH        (4)
#define SySecurityAccessAllowedCode         (0x34)

/* The first byte i.e byte 0 of transmit buffer is Response Id .
   The remaining bytes are message data.
 */
#define SyTRANSMIT_MSG_BUFF_OFFSET_BYTE1   (1)

static bool Vb14230_M27_Sec_Key_Allowed;   /* indicates that the client */
                                                /* can send the key value.  */
static bool Level2_Sec_Key_Allowed;        /* indicates that the client */
                                                /* can send the level2 key value*/
static uint8_t WrongAttemptTry;
//static uint8_t L2_WrongAttemptTry;

// #pragma section [nvram]
 uint8_t L2_WrongAttemptTry;
// #pragma section []
/***********************************************************************
*                                                                      *
* FUNCTION:          KwJ14230SecurityAccess.                           *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       Implements the service 27 functionality.          *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
***********************************************************************/

static enum
{
    ReqServiceId,
    ReqAccessMode,
    ReqKeyHighByte,
    ReqKeyLowByte
} ReadDTCByStatus;


void KwJ14230SecurityAccess( void )
{

   uint8_t                 SecurityAccessMode;
   uint8_t                 TrByteCount;
   TWO_BYTE_DATA_TYPE      Lu2190_Security_Seed_Value;
   TWO_BYTE_DATA_TYPE      Lu2190_M27_ReceivedKey;
   TWO_BYTE_DATA_TYPE      Lu2190_L2_Security_Seed_Value;
   TWO_BYTE_DATA_TYPE      Lu2190_L2_M27_ReceivedKey;


   SecurityAccessMode= GetKw2000ServiceData ( ReqAccessMode );
   TrByteCount = SyTRANSMIT_MSG_BUFF_OFFSET_BYTE1;
   switch (SecurityAccessMode)
   {
      case SyRequestForSeed:
      {
         /* If input message length is not valid, send negative response.   */
         if ( Sy14230_MODE_27_MSG01_LENGTH != GetKeyword2000ServiceDataLength() )
         {
             SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
         }
         else /* Sy14230_MODE_27_MSG01_LENGTH */
         {
            if (  ( !CheckIfSecurityTimerIsZero () )
                &&( GetVulnerabilityState() == false ) )
            {
               /* if the timer has not expired, send negative response */
               SendStandardNegativeAnswer(nrcRequiredTimeDelayNotExpired);
            }
            else /* CheckIfSecurityTimerIsZero  */
            {
               /* Send the seed data to the tester. */

               Vb14230_M27_Sec_Key_Allowed = true;

               if ( GetVulnerabilityState() == true )
               {
                  Lu2190_Security_Seed_Value.Word_Access = 0x0000;
               }
               else
               {
                  Lu2190_Security_Seed_Value.Word_Access = Get_Security_Seed_Data();
               }

               WrtKw2000ServiceData( SecurityAccessMode, TrByteCount++);
               WrtKw2000ServiceData( Lu2190_Security_Seed_Value.Byte_Access.Byte_One, TrByteCount++);
               WrtKw2000ServiceData( Lu2190_Security_Seed_Value.Byte_Access.Byte_Two, TrByteCount++);
               SendStandardPositiveAnswer (TrByteCount);
            }
         }
         break;
      }
      case SySendKey:
      {
          if (   ( !CheckIfSecurityTimerIsZero () )
              && ( GetVulnerabilityState() == false ) )
          {
              /* if the timer not expired, send negative response */
              SendStandardNegativeAnswer(nrcRequiredTimeDelayNotExpired);
          }
          else  /*  CheckIfSecurityTimerIsZero */
          {
              if (GetKeyword2000ServiceDataLength () != Sy14230_MODE_27_MSG02_LENGTH)
              {
                  SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
              }
              else /* GetKeyword2000ServiceDataLength */
              {

                  if ( true == Vb14230_M27_Sec_Key_Allowed )
                  {

                     Vb14230_M27_Sec_Key_Allowed = false;

                     Lu2190_M27_ReceivedKey.Byte_Access.Byte_One = GetKw2000ServiceData (ReqKeyHighByte);
                     Lu2190_M27_ReceivedKey.Byte_Access.Byte_Two = GetKw2000ServiceData (ReqKeyLowByte);

                     if ( Lu2190_M27_ReceivedKey.Word_Access == Get_Security_Key_Data() )
                     {
                       /* If the key matches the PCM stored key, send positive response. */
                        WrongAttemptTry = 0;
                        UnlockSecurityAccess ();
                        WrtKw2000ServiceData( SecurityAccessMode, TrByteCount++);
                        WrtKw2000ServiceData( SySecurityAccessAllowedCode, TrByteCount++);

                        SendStandardPositiveAnswer (TrByteCount);
                     }
                     else /* Lu2190_M27_ReceivedKey.Word_Acces */
                     {
                        WrongAttemptTry++;
                        if(WrongAttemptTry >= 2)
                        {
                           WrongAttemptTry = 0;
                           TriggerSecurityTiming();
                        }
                        SendStandardNegativeAnswer (nrcInvalidKey);
                     }
                  } /* Vb2190_M27_Sec_Key_Allowed */
                  else
                  {
                      /* The requested messages are out of sequense. */
                      SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
                  }
              } /* GetKeyword2000ServiceDataLength */
          } /* CheckIfSecurityTimerIsZero */
          break;
      }
      case SyRequestForL2Seed:
      {
         // if (( K_Immo_option == CeImmo_Off) )//|| (K_Immo_option == CeImmo_JiCheng)
            //||(Chk_GenericImmo_Disabled()))
          if (0)
         {
            SendStandardNegativeAnswer(nrcServiceNotSupported);
         }
         else if ( Sy14230_MODE_27_MSG03_LENGTH != GetKeyword2000ServiceDataLength())
         {
            SendStandardNegativeAnswer( nrcSubFunctionNotSupported_InvalidFormat );
         }
         else /* Sy14230_MODE_27_MSG03_LENGTH */
         {
            if(!GetVulnerabilityState())
            {
               SendStandardNegativeAnswer(nrcSecurityAccessDenied_SecurityAccessRequested);
            }
            else if (!CheckIfL2SecurityTimerIsZero ())
            {
               /* if the timer has not expired, send negative response */
               SendStandardNegativeAnswer(nrcRequiredTimeDelayNotExpired);
            }
            else /* CheckIfSecurityTimerIsZero  */
            {
               /* Send the seed data to the tester. */

               Level2_Sec_Key_Allowed = true;

               if (GetLevel2VulnerabilityState() == true)
               {
                  Lu2190_L2_Security_Seed_Value.Word_Access = 0x0000;
               }
               else
               {
                  Lu2190_L2_Security_Seed_Value.Word_Access = Get_L2_Security_Seed_Data();
               }

               WrtKw2000ServiceData( SecurityAccessMode, TrByteCount++);
               WrtKw2000ServiceData( Lu2190_L2_Security_Seed_Value.Byte_Access.Byte_One, TrByteCount++);
               WrtKw2000ServiceData( Lu2190_L2_Security_Seed_Value.Byte_Access.Byte_Two, TrByteCount++);
               SendStandardPositiveAnswer (TrByteCount);
            }
         }
         break;
      }
      case SySendL2Key:
      {
         // if ( (K_Immo_option == CeImmo_Off) /*||(K_Immo_option == CeImmo_JiCheng)*/)@
		 if (0)
         {
            SendStandardNegativeAnswer(nrcServiceNotSupported);
         }
         else if (!CheckIfL2SecurityTimerIsZero ())
         {
            /* if the timer not expired, send negative response */
            SendStandardNegativeAnswer(nrcRequiredTimeDelayNotExpired);
         }
         else  /*  CheckIfSecurityTimerIsZero */
         {
            if ((GetKeyword2000ServiceDataLength () != Sy14230_MODE_27_MSG04_LENGTH) )
            {
               SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
            }
            else /* GetKeyword2000ServiceDataLength */
            {


               if ( (true == Level2_Sec_Key_Allowed) /*||
                    (K_Immo_option == CeImmo_Generic)||
                    (K_Immo_option == CeImmo_Generic_EEControl)*/)
               {
                  Level2_Sec_Key_Allowed = false;
                  Lu2190_L2_M27_ReceivedKey.Byte_Access.Byte_One = GetKw2000ServiceData (ReqKeyHighByte);
                  Lu2190_L2_M27_ReceivedKey.Byte_Access.Byte_Two = GetKw2000ServiceData (ReqKeyLowByte);

                  if ( Lu2190_L2_M27_ReceivedKey.Word_Access == Get_L2_Security_Key_Data() )
                  {
                     /* If the key matches the PCM stored key, send positive response. */
                     UnlockL2SecurityAccess ();
                     WrtKw2000ServiceData( SecurityAccessMode, TrByteCount++);
                     WrtKw2000ServiceData( SySecurityAccessAllowedCode, TrByteCount++);

                     /* Reset Wrong Attempt counter */
                     L2_WrongAttemptTry = 0;
                     SendStandardPositiveAnswer (TrByteCount);

                  }
                  else /* Lu2190_M27_ReceivedKey.Word_Acces */
                  {
                      // if (Chk_SiemensImmo_Enabled())
					  if (1)
                      	{
                           if(L2_WrongAttemptTry < 1)
                             {    
                               L2_WrongAttemptTry++;
                             }
                             else
                             {
                               /* Trigger Level 2 security timer */
                               TriggerL2SecurityTiming();
                             }
                      	}
                      else
                      	{
			   L2_WrongAttemptTry++;
                     /* if Wrong Attempt exceed 2 times */
                     if(L2_WrongAttemptTry >= 2)
                     {

                        /* Trigger Level 2 security timer */
                        TriggerL2SecurityTiming();
                        /* Reset Wrong Attempt counter */
                        L2_WrongAttemptTry = 0;
                               }
                     }
                     SendStandardNegativeAnswer (nrcInvalidKey);
                  }
               } /* Vb2190_M27_Sec_Key_Allowed */
               else
               {
                  /* The requested messages are out of sequense. */
                  SendStandardNegativeAnswer(nrcConditionsNotCorrect_RequestSequenceError);
               }
            } /* GetKeyword2000ServiceDataLength */
         } /* CheckIfSecurityTimerIsZero */
         break;
      }
      default:
      {
          SendStandardNegativeAnswer(nrcSubFunctionNotSupported_InvalidFormat);
          break;
      }
   } /* switch */

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
 * 05/01/07     LShoujun    mt20u2#72
 * + Integrated generic immobiliser from MT22U project
 *   - Changed to support generic immo
 *
 * 12/03/07     LShoujun    mt20u2#78
 * + Integrate P2 old immo into dev10
 *   - Changed logic of SySendL2Key to support old immobilizer
 *
 * 22/11/07	   Yu Runwu    mt20u2#194
 * + Implement CJAE Immobilizer and Remove Old Immobilizer
 *   - Change the judge conditions in switch (SecurityAccessMode).
\* ============================================================================ */
