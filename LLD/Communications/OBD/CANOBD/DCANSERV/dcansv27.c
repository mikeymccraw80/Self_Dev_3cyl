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
* Filename     : dcansv27.c                                            *
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
* 2     03-07-12  cjqq    Add GetLnServiceDataLength  condition        *
* 3     04-09-12  cjqq    Update the CANOBD per customer requirement   *
* 4     07-31-12  azh     Add Kostal PEPS IMMO interface               *
* 4     09-10-12  cjqq    Updated NRC=24 when request sequence error   *
* 6     10-17-12  xll     set limit for LnReceivedSeed                 *
* 7     02-05-13  azh     Remove length check in LnSecurityAccess      *
* 9     07-25-13  xll     SCR#1169 New CAN requirement from JAC        *
*                         GDI application                              *
* 10    11-21-13  xll     SCR1309 Modified SequenceNumberoffset to 16  *
* 11    14-01-24  XLL     SCR1428 fix issue that NRC is wrong when send*
*                         message's length is smaller than 2.          *
* 13    14-04-03  tz9dw1  RSM8282 Modified dcansv22 for implementing   *
*                         TTE CAN IMMO into MT62p1                     *
* 17    14-07-01  xll     SCR1581 Added compile option COMPILE_SID27_GWM_CHK011 *
*                         and COMPILE_SID27_JAC_SII
***********************************************************************/
#include "dcansv27.h"
#if (XeDCAN_SID_27_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "obdsfapp.h" /* For IMMO configuration */
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlfsrv.h"/*IsDevelopmentOrManfModeActive()*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcanserv.h"
#include "obdlcald.h" /*KeDCANCORE_Security_Algorithm*/
#include "dcancomm.h"
#include "obdspcfg.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************
* void KwJ14230StartDiagnosticSession( void );                         *
* void KwJ14230ExecuteService10NextResponse( void );                   *
***********************************************************************/
   
#define SequenceNumData_Size (4)
#define SequenceNumberoffset (16)

static uint32_t  LnReceivedSeed;
static uint32_t  LnReceivedKey;
BYTE KW2SequenceNumData [SequenceNumData_Size];

/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
uint32_t LnSeedToKey (uint32_t seed, uint32_t mask)
{
   uint32_t key = 0;
   uint8_t  item;
   if( seed!=0 )
   {
      for (item = 0; item < 35; item++)
      {
        if (seed & 0x80000000)
        {
           seed = seed << 0x01;
           seed = seed ^ mask;
        }
        else
        {
           seed = seed << 0x01;
        }
      }
      key = seed;
   }
   return key;
}
uint32_t JAC_SII_seedToKey (uint8_t num_rounds, uint32_t Seed, uint8_t *SN)
{
   uint32_t key;
   uint32_t v0,v1;
   uint8_t seed0,seed1,seed2,seed3,i;
   uint32_t k[4];
   uint32_t sum=0;
   uint32_t delta=0x9E3779B9;

   seed0 = (uint8_t)(Seed >>24);
   seed1 = (uint8_t)((Seed & 0x00FFFFFF)>>16);
   seed2 = (uint8_t)((Seed & 0x0000FFFF)>>8);
   seed3 = (uint8_t)(Seed & 0x000000FF);

   v0 = Seed;
   v1 = ((((uint32_t)(~seed0))<<24) & 0xFF000000) |
   	    ((((uint32_t)(~seed1))<<16)& 0x00FF0000) |
   	    ((((uint32_t)(~seed2))<<8)& 0x0000FF00) |
        (((uint32_t)(~seed3))& 0x000000FF);

   for(i=0;i<4;i++)
   {
      //   k[i]=(uint32_t)((((*(SN + i))&0x07)<<5)|((*(SN + i))>>3));
      k[i]=(uint32_t)(*(SN+i));
	}
   for(i=0;i<num_rounds;i++)
   {
      v0 +=(((v1<<4)^(v1>>5))+v1)^(sum + k[sum&3]);
      sum += delta;
      v1+=(((v0<<4)^(v0>>5))+v0)^(sum + k[(sum>>11)&3]);
   }

   key = v0;
   return key;
}

INLINE void GetKW2SequenceNumValue(void)
{   
   uint8_t i = 0;
   for(i=0;i<SequenceNumData_Size;i++)
   {
      //KW2SequenceNumData[i]=*((@gpage @far BYTE *)CgSideRailSequenceNumAddr+i); // MT22.1
#ifdef OBD_CONTROLLER_IS_MT92
      KW2SequenceNumData[i]=*((uint8_t *) (CpKW2KSideRailAddress_Ptr + SequenceNumberoffset +i));
#endif
   }
}

/**********************************************************************/
/*** LnDiag service: SecurityAccess    (SID27)                             ***/
/**********************************************************************/
void LnSecurityAccess (void)
{
   uint8_t   SecurityAccessSubFunction;
   uint16_t  ReceivedKey;
   uint8_t   meslegth;
   uint8_t   DataLength_ReqSeed;
   uint8_t   DataLength_ReqKey;
   bool      PostiveResponse;
   uint8_t   num_rounds;

   PostiveResponse = false;
   SecurityAccessSubFunction = (GetLnServiceData ()) [1];
   meslegth = 2;
   num_rounds = 2;

   switch( KeDCANOBD_Security_Algorithm )
   {
	  case CeDelphi_Generic_Static:
   	    DataLength_ReqKey  = SID27_MSG02_LENGTH;
		    break;
#ifdef COMPILE_SID27_GWM_CHK011
	  case CeGWM_CHK011:
	      DataLength_ReqKey  = SID27_MSG02_CHK011_LENGTH;							
		    break;
#endif
#ifdef COMPILE_SID27_JAC_SII
    case CeJAC_SII:
        DataLength_ReqKey  = SID27_MSG02_JAC_LENGTH;							
        break;
#endif
    case CePML_2Sd4Key:
    case CePML_4Sd4Key:
        DataLength_ReqKey  = SID27_MSG02_DelphiGeneric_4KyLENGTH; 
        break;
    default:
        DataLength_ReqKey = 0;
	      break;	
   }

   if(GetLnServiceDataLength () < 2)
   {
   	  SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
     if(SubFuncRequestSeed == SecurityAccessSubFunction)
     {
        if (GetLnServiceDataLength () != SID27_MSG01_LENGTH)
        {
            SendLnStandardNegativeAnswer (IncorrectMessageLength);
        }
        else
        {
          if (( IsDevelopmentOrManfModeActive () )  ||
                CheckProgrammingState ()  ||
                GetLnVulnerabilityState() )
                                  /* PCM already unlocked */
          {
            switch( KeDCANOBD_Security_Algorithm )
            {
              case CeDelphi_Generic_Static:
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    break;
#ifdef COMPILE_SID27_GWM_CHK011
              case CeGWM_CHK011:
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    break;
#endif
#ifdef COMPILE_SID27_JAC_SII
              case CeJAC_SII:
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    break;
#endif
              case CePML_2Sd4Key:
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    break; 
              case CePML_4Sd4Key:
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    WrtDCAN_ServiceData(0x00, meslegth++);
                    break;
              default:
                    break;	
            }
            UnlockSecurityAccess_DCAN ();
            SendLnStandardPositiveAnswer (meslegth);
          }
          else
          {
              if (LnDiagSecurityDelayTimer)
              {
                 SendLnStandardNegativeAnswer (RequiredTimeDelayNotExpired);
              }
              else
              {
                  SPS_Security_Key_Allowed = CbTRUE; 
                  switch( KeDCANOBD_Security_Algorithm )
                  {
                    case CeDelphi_Generic_Static:
                        WrtDCAN_ServiceData(((uint8_t) (Get_Security_Seed_Data() >> 8)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) Get_Security_Seed_Data()), meslegth++);
                        break;
#ifdef COMPILE_SID27_GWM_CHK011
                    case CeGWM_CHK011:
                        LnReceivedSeed = LnSeed_Random;
                        if((LnReceivedSeed==0x00000000)||((LnReceivedSeed==0xFFFFFFFF)))
                        {
                          LnReceivedSeed=0x00000001ul;
                        }
                        WrtDCAN_ServiceData(((uint8_t) (LnReceivedSeed >> 24)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) (LnReceivedSeed >> 16)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) (LnReceivedSeed >> 8)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) LnReceivedSeed ), meslegth++);
                        break;
#endif
#ifdef COMPILE_SID27_JAC_SII
                    case CeJAC_SII:
                        LnReceivedSeed = LnSeed_Random;
                        if((LnReceivedSeed==0x00000000)||((LnReceivedSeed==0xFFFFFFFF)))
                        {
                          LnReceivedSeed=0x00000001ul;
                        }
                        WrtDCAN_ServiceData(((uint8_t) (LnReceivedSeed >> 24)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) (LnReceivedSeed >> 16)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) (LnReceivedSeed >> 8)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) LnReceivedSeed ), meslegth++);
                        break;
#endif
                    case CePML_2Sd4Key:
                        WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 8)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) GetOBD_4ByteSeed()), meslegth++); 
                        break;
                    case CePML_4Sd4Key:
                        WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 24)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 16)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) (GetOBD_4ByteSeed() >> 8)), meslegth++);
                        WrtDCAN_ServiceData(((uint8_t) GetOBD_4ByteSeed()), meslegth++); 
                        break;
                    default:
                        break;	
                  } 
                  SendLnStandardPositiveAnswer (meslegth);
              }
           }
        }
     }
     else if(SubFuncSendKey == SecurityAccessSubFunction)
     {
        if (LnDiagSecurityDelayTimer)
        {
           SendLnStandardNegativeAnswer (RequiredTimeDelayNotExpired);
        }
        else
        {
           if (GetLnServiceDataLength () != DataLength_ReqKey)
           {
              SendLnStandardNegativeAnswer (IncorrectMessageLength);
           }
           else
           {
              if (SPS_Security_Key_Allowed)
              {
                 SPS_Security_Key_Allowed = CbFALSE;
                 switch( KeDCANOBD_Security_Algorithm )
                 {
                  case CeDelphi_Generic_Static:
                      ReceivedKey = ((GetLnServiceData ()) [2] << 8) + (GetLnServiceData ()) [3];
                      if((ReceivedKey == Get_Key()))
                      {
                        PostiveResponse = true;
                      }
                      else
                      {
                        PostiveResponse = false;
                      }
                      break;
#ifdef COMPILE_SID27_GWM_CHK011
                  case CeGWM_CHK011:
                      LnReceivedKey = ((GetLnServiceData ()) [2] << 24) + ((GetLnServiceData ()) [3]<< 16) +
                         ((GetLnServiceData ()) [4]<< 8)+ (GetLnServiceData ()) [5];
                      if(LnReceivedKey == LnSeedToKey(LnReceivedSeed, CHK011_Mask))
                      {
                        PostiveResponse = true;
                      }
                      else
                      {
                        PostiveResponse = false;
                      }
                      break;
#endif
#ifdef COMPILE_SID27_JAC_SII
                  case CeJAC_SII:
                      LnReceivedKey = ((GetLnServiceData ()) [2] << 24) + ((GetLnServiceData ()) [3]<< 16) +
                                  ((GetLnServiceData ()) [4]<< 8)+ (GetLnServiceData ()) [5];
                      GetKW2SequenceNumValue();
                      if(LnReceivedKey == JAC_SII_seedToKey (num_rounds, LnReceivedSeed, KW2SequenceNumData))
                      {
                        PostiveResponse = true;
                      }
                      else
                      {
                        PostiveResponse = false;
                      }
                      break;
#endif
                  case CePML_2Sd4Key:
                  case CePML_4Sd4Key:
                      LnReceivedKey =  ((GetLnServiceData ()) [2] <<24) 
                                     + ((GetLnServiceData ()) [3] <<16) 
                                     + ((GetLnServiceData ()) [4] << 8) 
                                     + (GetLnServiceData ()) [5];
                      if((LnReceivedKey == GetOBD_4ByteKey()))
                      {
                        PostiveResponse = true;
                      } 
                      else
                      {
                        PostiveResponse = false; 
                      }
                      break;
                  default:
                      break;
                 }
                 if (true == PostiveResponse)
                 {
                    UnlockSecurityAccess_DCAN ();
                    LnDgSecAccessSpsBadKeyCounter = 0;
                    SendLnStandardPositiveAnswer (2);
                 }
                 else
                 {
                    LnDgSecAccessSpsBadKeyCounter ++;
                    if (LnDgSecAccessSpsBadKeyCounter == 2)
                    {
                       SendLnStandardNegativeAnswer (ExceedNumberOfAttempts);
                       TriggerSecurityAccessTiming ();
                    }
                    else
                    {
                       SendLnStandardNegativeAnswer (InvalidKey);
                    }
                 }
              }
              else
              {
                 SendLnStandardNegativeAnswer (RequestSequenceError);
              }
           }
        }
     }
  #if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
        && (XbIMMO_KOSTAL_SUBS_SELECT_FLAG == CbSUBS_ON) )
     else if( (KOSTAL_IMMO_ENABLED() )
          &&( (SubFuncRequestSeed_EOL == SecurityAccessSubFunction)
           || (SubFuncSendKey_EOL == SecurityAccessSubFunction)
           || (SubFuncRequestSeed_AS == SecurityAccessSubFunction)
           || (SubFuncSendKey_AS == SecurityAccessSubFunction) ) )
     {
        KostalIMMO_OBDSecurityAccess(SecurityAccessSubFunction);
     }
  #endif	   
  #if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
        && ((XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
         || (XbIMMO_TTEC_SUBS_SELECT_FLAG == CbSUBS_ON)) )
     else if( ( CONTI_IMMO_ENABLED() || TTEC_IMMO_ENABLED() )
          &&( (SubFuncRequestSeed_EOL == SecurityAccessSubFunction)
           || (SubFuncSendKey_EOL == SecurityAccessSubFunction)
           || (SubFuncRequestSeed_AS == SecurityAccessSubFunction)
           || (SubFuncSendKey_AS == SecurityAccessSubFunction) ) )
     {
        ContiIMMO_OBDSecurityAccess(SecurityAccessSubFunction);
     }
  #endif	   
  #if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
        && (XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) )
     else if( ( HIRAIN_IMMO_ENABLED() )
            &&( (SubFuncRequestSeed_EOL == SecurityAccessSubFunction)
               ||(SubFuncSendKey_EOL == SecurityAccessSubFunction)))
     {
        HIRAINIMMO_OBDSecurityAccess(SecurityAccessSubFunction);
     }
  #endif	
     else
     {
        if(GetLnServReqMsgAddressingMode () == FunctionalAddressing)
        {
           PfrmDCAN_AckReqWithoutResponse ();
        }
        else
        {
           SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
        }
     }
   }
} /*** End of LnSecurityAccess ***/

#endif


