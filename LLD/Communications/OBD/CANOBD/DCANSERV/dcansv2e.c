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
* Filename     : dcansv2e.c                                            *
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
* 2     03-07-12   cjqq   Add GetLnServiceDataLength () condition      *
* 3     04-09-12  cjqq    Update the CANOBD per customer requirement   *
* 5     07-31-12  azh     Add Kostal PEPS IMMO interface               *
* 5     08-29-12  cjqq    Modify the write VIN format same with KW2000 *
* 6     09-14-12  cjqq    Add PID f1a0 f1a1 f1a2 for GW                *
* 7     10-17-12  xll     change complie option MT92_GDI_4CYL_T3_TURBO_LO2 *
*                         to MT92_GDI_PID_Config                       *
* 9     12-13-12  xll     VIR1022_Use cal to differentiate customized  *
*                         requirement or CHK011 project                *
* 10    12-13-12  xll     SCR1032 Add break in case DIdKostallImmoSKCheckResult *
* 11    13-01-18  xll     RCR#1036 Add new CAL variable array to specify Service ID $2E *
*                         & 2F if these SID need unlock  the security access *
* 13    13-08-30  xll     RCR#1239 Modified LnWriteDataByIdentifier()  *
* 15    14-04-03  tz9dw1  RSM8282 Modified dcansv2e for implementing   *
*                         TTE CAN IMMO into MT62p1                     *
* 20    14-06-30  lgj     SCR 1167  Modified LnWriteDataByIdentifier() *
***********************************************************************/
#include "dcansv2e.h"
#if (XeDCAN_SID_2E_Supported == CeDCAN_Supported)

#define EE_CalibrationData_Size             (96)
#define CrankShaftAdaptiveCylinderSize      (16)

#include "filenvmd.h"
/******************************************************************************
* APP Include Files
******************************************************************************/
//#include "systpcfg.h"
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
//#include "obdsfexi.h"/*CeVIOS_SYS_DEVELOPMENT*/
#include "obdlfsrv.h"/*SetECUResetPending()*/
//#include "obdlfpid.h"/* GetCalPIDNumber() */
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcanserv.h"
#include "dcancomm.h"
#include "obdlcald.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************
* void KwJ14230StartDiagnosticSession( void );                         *
* void KwJ14230ExecuteService10NextResponse( void );                   *
***********************************************************************/

#if defined(OBD_CONTROLLER_IS_MT22P3)
   #if defined(CeFILE_USE_CMC_2nd_Set_VIN)

/*********************************************************************
 *                   static function declarations                    *
 *********************************************************************/
static TbBOOLEAN CheckVINAllZero(BYTE *vin_data, BYTE vin_length);

static TbBOOLEAN CheckVINAllZero(BYTE *vin_data, BYTE vin_length)
{
   BYTE i, sum = 0;
   for (i = 0; i < vin_length; ++i) {
      sum |= vin_data[i];
   }

   if (sum == 0)
   {
      // All zeros in vin_data
      return CbTRUE;
   }
   else if (sum != 0)
   {
      // At least one array element is non-zero
      return CbFALSE;
   }
   else
   {
      // do nothing.
   }
}

   #endif /* #if defined (CeFILE_USE_CMC_2nd_Set_VIN)*/
#endif /* #if defined(OBD_CONTROLLER_IS_MT22P3)*/

/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/

/**********************************************************************/
/*** LnDiag service: WriteDataByIdentifier     (SID2E)                     ***/
/**********************************************************************/
void LnWriteDataByIdentifier (void)
{
   uint16_t WriteDataIdentifierId, LyIndex;
   uint8_t  Idx;
   uint8_t Idx_WritePointer;
   uint32_t LgDF_DID_OdoServiceValue;
   TbBOOLEAN LbCalDID_Found;
   uint8_t LyCalDIDIndx;
   BYTE CalDID_DataSize;  
   BYTE CalDID_Offset;
   BYTE CalDID_EndDataOffset;
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
        && ((XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
          || (XbIMMO_VALEO_SUBS_SELECT_FLAG == CbSUBS_ON) \
          || (XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) \
          || (XbIMMO_TTEC_SUBS_SELECT_FLAG == CbSUBS_ON)) )
   uint8_t LyEcsFlag;
#endif
   LgDF_DID_OdoServiceValue = 0; LyIndex =0;
   LbCalDID_Found = CbFALSE;
   LyCalDIDIndx = 0;

   WriteDataIdentifierId = (((uint16_t) (GetLnServiceData ()) [1] << 8) |(GetLnServiceData ()) [2]);
   if ( GetLnServiceDataLength () <= 3 )
   {
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else if( (KaDCANOBD_SecurityAccessUsedService[CeServiceID_2E] == CeService_SecurityAccessUsed)
           &&(!GetLnVulnerabilityState()) )//&& !(HIRAIN_IMMO_ENABLED()&&(WriteDataIdentifierId==DIdHIRAINIMMOWriteSK)) )
   {
      SendLnStandardNegativeAnswer(SecurityAccessDenied);  
   }
   else
   {	
	
        /*--- NOTE: The switch statement contains the LocalIds which
                   do not require a security access*/
      switch (WriteDataIdentifierId)
      {
          /*--- NO Security Access required for these Data ---*/

         case DIdVehicleIdentificationNumber:
         if (GetLnServiceDataLength () !=(3 + VIN_Size))
         {
            SendLnStandardNegativeAnswer (IncorrectMessageLength);
         }
         else
         {

			/*--- Program VehicleIdentificationNumber ---*/
            for ( Idx = 0 ; Idx < VIN_Size ; Idx++ )
            {
               
               NsFILE_NVM_EE_ManufactData.VaFILE_EE_VIN[Idx] = (GetLnServiceData ()) [3 + Idx];
               scnVehInfo.VIN[Idx] = NsFILE_NVM_EE_ManufactData.VaFILE_EE_VIN[Idx];
            }
			
			SendLnStandardPositiveAnswer (3);
         }
         break;
	  
         case DIdRepairShopCodeOrTesterSerialNumber:

		 if (GetLnServiceDataLength () != (3 + RepairShopCode_Size))
         {
            SendLnStandardNegativeAnswer (IncorrectMessageLength);
         }
         else
         {
            for (Idx = 0; Idx < RepairShopCode_Size; Idx++)
            {
              // WrtKW2RepairShopCodeByte (Idx,(GetLnServiceData ()) [3 + Idx]);
            }
            
            SendLnStandardPositiveAnswer (3);
         }
         break;


         case DIdProgrammingDate:
         if (GetLnServiceDataLength () != (3 + ProgrammingDate_Size))
         {
            SendLnStandardNegativeAnswer (IncorrectMessageLength);
         }
         else
         {
            for (Idx = 0; Idx < ProgrammingDate_Size; Idx++)
            {
              // WrtKW2ProgrammingDateByte (Idx,(GetLnServiceData ()) [3 + Idx]);
            }
            
            SendLnStandardPositiveAnswer (3);
         }
         break;


#if 0
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
   && (XbIMMO_KOSTAL_SUBS_SELECT_FLAG == CbSUBS_ON) )
         case DIdKostallImmoSKCheckResult:
         {
            if(KOSTAL_IMMO_ENABLED() )
            {
               /* Log Check Result */
               
               SendLnStandardPositiveAnswer (3);
            }
            else
            {
               SendLnStandardNegativeAnswer (RequestOutOfRange);
            }
         }
		 break;
#endif		
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
        && ((XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
         || (XbIMMO_TTEC_SUBS_SELECT_FLAG == CbSUBS_ON)) )
#if XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON
			case DIdContiIMMOWriteSC:
#endif
#if XbIMMO_TTEC_SUBS_SELECT_FLAG == CbSUBS_ON
         case DIdTTECANIMMOWriteSC:
#endif
            LyEcsFlag = ContiIMMO_WriteSC();
            if (LyEcsFlag)
            {
               SendLnStandardNegativeAnswer (LyEcsFlag);
            }
            else
            {
               SendLnStandardPositiveAnswer (3);
            }
         break;
#endif
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
        && ((XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
           ||(XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) \
           ||(XbIMMO_TTEC_SUBS_SELECT_FLAG == CbSUBS_ON)) )
#if XbIMMO_CONTI_SUBS_SELECT_FLAG == CbSUBS_ON
         case DIdContiIMMOWriteSK:
		LyEcsFlag = ContiIMMO_WriteSK();
#endif
#if XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON
         case DIdHIRAINIMMOWriteSK:
		LyEcsFlag = HIRAINIMMO_WriteSK(); 	
#endif
#if XbIMMO_TTEC_SUBS_SELECT_FLAG == CbSUBS_ON
         case DIdTTECANIMMOWriteSK:	
		LyEcsFlag = ContiIMMO_WriteSK(); 	
#endif

            if (LyEcsFlag)
            {
               SendLnStandardNegativeAnswer (LyEcsFlag);
            }
            else
            {
               SendLnStandardPositiveAnswer (3);
            }
         break;
#endif
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
      && (XbIMMO_VALEO_SUBS_SELECT_FLAG == CbSUBS_ON) )
         case DIdValeoIMMOWriteSC:
            LyEcsFlag = ValeoIMMO_WriteSC();
            if (LyEcsFlag)
            {
               SendLnStandardNegativeAnswer (LyEcsFlag);
            }
            else
            {
               SendLnStandardPositiveAnswer (3);
            }
            break;
#endif

#ifdef OBD_CONTROLLER_IS_MT22P3
         case DIdCMCEngineDataIdentifier:
            if (GetLnServiceDataLength () != (3 + EngPerfIdentData_Size))
            {
               SendLnStandardNegativeAnswer (IncorrectMessageLength);
            }
            else if((CbTRUE == GetVIOS_EngSt_Run()) || ( GetVIOS_v_VehSpd() > V_KPH(0)))
            {
               SendLnStandardNegativeAnswer (ConditionsNotCorrectOrRequestSequenceError);
            }
            else
            {
               for (Idx = 0; Idx < EngPerfIdentData_Size; Idx++)
               {
                  WrtEngPerfIdentDataByte (Idx, (GetLnServiceData()) [3 + Idx]);
               }
               WrtEngPerfIdentDataValue();
               SendLnStandardPositiveAnswer (3);
            }
         break;
#endif /* #if defined(OBD_CONTROLLER_IS_MT22P3) */
#endif
         default :
            SendLnStandardNegativeAnswer (RequestOutOfRange);
         break;
      } /* End of Switch*/
	
   }
} /*** End of LnWriteDataByIdentifier ***/

#endif

