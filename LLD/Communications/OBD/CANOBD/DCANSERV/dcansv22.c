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
* Filename     : dcansv22.c                                            *
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
* 3     13-08-30  xll     RCR1239 Modified LnReadDataByCommonIdentifier() *
* 5     14-04-03  tz9dw1  RSM8282 Modified dcansv22 for implementing   *
*                         TTE CAN IMMO into MT62p1                     *
* 6     14-04-23  tz9dw1  ctc_pt3#1529 Correct Conti IMMO security access *
*                                      delete TTEC_IMMO_ENABLED() and     *
*                                      TTE CAN IMMO compiler option       *
* 7     14-05-20  xll     RSM_CTC_8331_MT92_PCHUD_Function_Rev00_20140420.doc
******************************************************************************/
#include"dcansv22.h"
#if (XeDCAN_SID_22_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/

/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
// #include "obdlfpid.h"/*MaskMode_22*/
// #include "obdsfexi.h" //for IMMO include 
#include "dcanserv.h"
// #include "pchdpall.h"
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcancomm.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************

***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
#define CANPID_VALEO_READSC   (0x20B2)
#define CANPID_VALEO_DELIVERY (0x0300)
#define CANPID_CONTI_READSK   (0x0201)
#define CANPID_CONTI_READSC   (0x0206)
#define CANPID_HIRAIN_READSK_MTCHSTUS   (0x0202)
#define CANPID_HIRAIN_READSK            (0x0203)

#define  MaskMode_01 0x10
#define  MaskMode_02 0x20
#define  MaskMode_12 0x40
#define  MaskMode_22 0x80

#define  Mode_01 MaskMode_01
#define  Mode_02 MaskMode_02
#define  Mode_12 MaskMode_12 
#define  Mode_22 MaskMode_22 

#define EE_CalibrationData_Size             (96)

/*******************************************************************************/
/*** service: LnReadDataByCommonIdentifier      (SID22)                       ***/
/*** Reports the Diagnostic Data corresponding to the Parameter ID (2 bytes) ***/
/*******************************************************************************/
void LnReadDataByCommonIdentifier (void)
{
   uint16_t  ParamID;
   uint8_t   msglength;
   uint8_t    LyPIDIdx ;
   uint8_t    LyDataIdx ;
   uint8_t    LaServiceData[7] ;
   bool        LbPIDFound;
   TbBOOLEAN  LbValid_PID;
   TbBOOLEAN  LbValid_CalPID;
   uint8_t    CalPID_DataLength; 
   uint8_t    CalPID_Offset;
   uint8_t    CalPID_DataEndOffset;
   uint16_t   Longmsglength;
   bool        LbLongPIDFound;
   
   LbPIDFound = CbFALSE;
   LbValid_CalPID = CbFALSE;
   LbValid_PID = CbFALSE;
   LbLongPIDFound = CbFALSE;
   if(GetLnServiceDataLength () < 3)
   {
        /* Request should be atleast 3 bytes long */
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else if(!(GetLnServiceDataLength () & 0x0001))
   {
        /* The length should be an odd value ( SID + n * 2byte ID ) */
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else 
   {
    /* Prepare response */
      msglength = 1;
      for(LyDataIdx = 1; LyDataIdx < GetLnServiceDataLength (); LyDataIdx++)
      {
         LaServiceData[LyDataIdx] = (GetLnServiceData ())[LyDataIdx];
      }
      LyPIDIdx = 1;
      while(LyPIDIdx < GetLnServiceDataLength ())
      {
    /*--- ParamID (also called common identifier is on 2 bytes for this service ---*/
         ParamID = (uint16_t) (LaServiceData[LyPIDIdx++] << 8);
         ParamID = (uint16_t) (ParamID |LaServiceData[LyPIDIdx++]);

   /*Check if the PID was supported in the PID table with Mode 22 */
         LbValid_PID = Get_Valid_SpecialPID_Info(ParamID,&LbValid_CalPID);
   
         if(CbFALSE == LbValid_PID)
         {
		 	LbValid_PID = Get_Valid_PID_Info(ParamID, MaskMode_22);
		 }
         if ((CbTRUE == LbValid_PID)
		 	#ifdef COMPILE_CANOBD_PCHUD
		 	 ||(CANPID_PCHUD == ParamID)
		 	#endif
			 )
         {
	      #if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
	           && ( (XbIMMO_VALEO_SUBS_SELECT_FLAG == CbSUBS_ON) \
	              ||(XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) \
	              ||(XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON) ) )

	        /*Valeo immo---Read DeliveryStatus and SC is only supported by CANOBD 22*/
	        if( ( ((ParamID == CANPID_VALEO_DELIVERY) 
			 	     ||(ParamID == CANPID_VALEO_READSC))
			       && (!VALEO_IMMO_ENABLED()) )
			  /*Conti immo---Read SK and SC is only supported by CANOBD 22*/
#if defined(OBD_CONTROLLER_IS_MT62P1) || defined(OBD_CONTROLLER_IS_MT22P3)
			    || ( ((ParamID == CANPID_HIRAIN_READSK) 
			           || (ParamID == CANPID_HIRAIN_READSK_MTCHSTUS))
			        && (!HIRAIN_IMMO_ENABLED()) )
			    || ( ((ParamID == CANPID_CONTI_READSK) 
			           || (ParamID == CANPID_CONTI_READSC))
			        && (!CONTI_IMMO_ENABLED()) ) )
#else
			    || ( (ParamID == CANPID_CONTI_READSK) 
			        && ( (!CONTI_IMMO_ENABLED())
			           || (!GetIMMO_Conti_LV2SecurityUnlockStatus())) ) 
			    || ( (ParamID == CANPID_CONTI_READSC)
			       && (!CONTI_IMMO_ENABLED()) ) )
#endif
	        {
	            /*The PID is not supported when IMMO is not enabled.*/
				/*do nothing*/
	        }
	        else
	      #endif
	      	{
            WrtDCAN_ServiceData( ((ParamID>>8)&0xff), msglength++ ) ;
            WrtDCAN_ServiceData( (ParamID&0xff),msglength++ ) ;
			
          #ifdef COMPILE_CANOBD_PCHUD
			if(CANPID_PCHUD == ParamID)
			{
				Longmsglength = ProcessReqstdLongPIDData(GetLnServiceData (), msglength);
				LbLongPIDFound = CbTRUE;
				LbPIDFound = CbTRUE;
			}
			else
          #endif
			{
    			if(CbTRUE == LbValid_CalPID)
    			{
    				CalPID_DataLength = GetCalPIDDataLength( GetVeDIAG_PIDIndex() );
    				CalPID_Offset = GetCalPIDDataAddressOffest(GetVeDIAG_PIDIndex());
    				CalPID_DataEndOffset = CalPID_DataLength + CalPID_Offset;
    				
    				if(CalPID_DataEndOffset > EE_CalibrationData_Size )
    				{
    					/*PID in KaDCAN_CalEEPROM_Data exceed EE_CalibrationData_Size*/
    					SendLnStandardNegativeAnswer (RequestOutOfRange);
    				}
    				else
    				{
    					msglength = ProcessReqstdCalPIDData(GetLnServiceData (), msglength ,
                                       CalPID_DataLength, CalPID_Offset ) ;
    					LbPIDFound = CbTRUE;
    				}
    
    			}
    			else
    			{
    				msglength = ProcessReqstdPIDData(GetLnServiceData (), msglength ,
                                       GetVeDIAG_PIDIndex() ) ;
    				LbPIDFound = CbTRUE;
    				
    			}
			}
	      }
         }
      }
      if (CbTRUE == LbPIDFound)
      {
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
    &&( (XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
     || (XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) ) )
         if( ( (!GetIMMO_Conti_LV2SecurityUnlockStatus()) && CONTI_IMMO_ENABLED()
	          &&((ParamID == CANPID_CONTI_READSK)||(ParamID == CANPID_CONTI_READSC)) )
	        ||( (!GetIMMO_HIRAIN_LV2SecurityUnlockStatus()) && HIRAIN_IMMO_ENABLED()
	          &&((ParamID == CANPID_HIRAIN_READSK_MTCHSTUS)||(ParamID == CANPID_HIRAIN_READSK)) ) )
         {
            SendLnStandardNegativeAnswer (SecurityAccessDenied);
         }
         else
         {
#endif
     #ifdef COMPILE_CANOBD_PCHUD
			if(LbLongPIDFound)
            {
				SendLnStandardPositiveAnswer (Longmsglength);
			}
			else
	 #endif
			{
				SendLnStandardPositiveAnswer (msglength);
			}
            
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
    && ((XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
      ||(XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) ) )
         }
#endif
      }
      else
      {
      /*--- PID does not exists in our list: neg answer ---*/
         SendLnStandardNegativeAnswer (RequestOutOfRange);
      }
   }
} /*** End of LnReadDataByCommonIdentifier ***/

#endif




