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
* Filename     : dcansv31.c                                            *
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
*1. 20110830  cjqq   -BM-         Creat from MT80
*2. 20110913  cjqq   RSM_CTC_8109 Update StartRoutineByLocalIdentifier()
*6. 20120731  azh    SCR899       Add Kostal PEPS IMMO interface
*7. 20130107  xh  xxxx    Support entering boot for MT62.1
*8. 20130306  azh    SCR1071      Change SRV31 routine name for Kostal IMMO
*9. 20130509  xll    SCR1111      Update StartRoutineByLocalIdentifier()
*                                 and StartRoutine_NVMReInitLogic()
*10 20130510  xll    SCR1125      Delete KPH condition in Update StartRoutineByLocalIdentifier()
*                                 and StartRoutine_NVMReInitLogic().
*13 20140630  lgj    SCR 1167     Modified DS_RoutineControl() *
***********************************************************************/
#include "dcansv31.h"
#if (XeDCAN_SID_31_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
#include "kw2app.h"
// #include "obdsfexi.h"/*CyEEPROM_SectionStart*/
/******************************************************************************
* OBD Lib Service Include Files
******************************************************************************/
#include "obdlfsrv.h"/*CyEEPROM_SectionStart*/
/******************************************************************************
* CANOBD Service Include Files
******************************************************************************/
#include "dcanserv.h"
#include "dcancomm.h"
//#include "dcantran.h"
/***********************************************************************
* Functions in this file:                                              *
************************************************************************

***********************************************************************/
/*********************************************************************/
/*           CONSTANT and ENUMERATION DECLARATIONS                   */
/*********************************************************************/
/**********************************************************************/
/*** LnDiag service: Routine Control       (SID31)                          ***/
/**********************************************************************/
#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
   && (XbIMMO_KOSTAL_SUBS_SELECT_FLAG == CbSUBS_ON) )
#define CyIMMO_Kostsal_EOL_RID_B20A        (0xB20A)
#define CyIMMO_Kostsal_EOL_RID_B20B        (0xB20B)
#define CyIMMO_Kostsal_EOL_RID_B20C        (0xB20C)
#define CyIMMO_Kostsal_EOL_RID_B20D        (0xB20D)
#define CyIMMO_Kostsal_EOL_RID_B10A        (0xB10A)

#define CyIMMO_Kostsal_ChangePEPS_RID_B205 (0xB205)
#define CyIMMO_Kostsal_ChangePEPS_RID_B206 (0xB206)
#define CyIMMO_Kostsal_ChangePEPS_RID_B207 (0xB207)
#define CyIMMO_Kostsal_ChangePEPS_RID_B105 (0xB105)

#define DS_NUM_ROUTINE_CTRL_KOSTAL 9
#else
#define DS_NUM_ROUTINE_CTRL_KOSTAL 0
#endif

#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
     && (XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) )
#define CyIMMO_HIRAIN_EOL_RID_0209         (0x0209)

#define DS_NUM_ROUTINE_CTRL_HIRAIN  1
#else
#define DS_NUM_ROUTINE_CTRL_HIRAIN  0
#endif

#if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
   && (XbIMMO_VALEO_SUBS_SELECT_FLAG == CbSUBS_ON) )
#define CyIMMO_Valeo_LearnSK_RID           (0xC000)
#define CyIMMO_Valeo_TeachSK_RID           (0xC001)
#define CyIMMO_Valeo_RstECM_RID            (0xC002)
#define DS_NUM_ROUTINE_CTRL_VALEO (3)
#else 
#define DS_NUM_ROUTINE_CTRL_VALEO (0)
#endif

#define DS_ORIGINAL_ROUTINE_CTRL (2)

#define DS_NUM_ROUTINE_CTRL   (DS_ORIGINAL_ROUTINE_CTRL + DS_NUM_ROUTINE_CTRL_KOSTAL + DS_NUM_ROUTINE_CTRL_HIRAIN + DS_NUM_ROUTINE_CTRL_VALEO)

uint8_t VyDCAN_SRV31_PosRespLength;
extern bool    KW31_EndofLine_FuelAdjustMode;
extern TbBOOLEAN     SaINJD_CktTestFailed[4]; 
extern TbBOOLEAN     SbEMSD_FPRDShortHiTestFailed;
extern TbBOOLEAN     SbEMSD_FPRDShortLoTestFailed;
extern bool Pb_FuelAdjustOnlyonetime_enable;
/***********************************************************************
*                                                                      *
* FUNCTION:          StartRoutineByLocalIdentifier                     *
*                                                                      *
* TYPE:              GLOBAL                                            *
*                                                                      *
* DESCRIPTION:       This is to execute a routine identified by a      *
*                    local identifier                                  *
*                                                                      *
* INPUT PARAMETERS:  NONE                                              *
*                                                                      *
* RETURN VALUES:     NONE                                              *
************************************************************************
* Last modified on: 06/10/10              by: Abhishek Sharma          *
***********************************************************************/

uint8_t SetCopyAndExecuteKernel(void)
{
   if((( GetLnVulnerabilityState() ))
     && (GetVIOS_n_EngSpd() < V_RPM(200)))
 /* in AT vehicle, VKPH will be set a default value when CAN is disabled, 
    because the default value is not equal to 0, we can't reflash the ECU with bench,
    it need to delete the condition that VKPH==0 */  
//     &&  (GetVIOS_v_VehSpd()== V_KPH(0)))
   {
      
      SetCopyAndExecuteKernelPending(CbTRUE);

      return 0x00;
   }
   else
   {
      return 0x22;//Change 0x7F to 0x22
   }
 
} /*** End of KwJ14230StopDiagnosticSession ***/

uint8_t StartRoutineByLocalIdentifier(void)
{
   bool    result;
   uint8_t   meslegth;
   
   if((( GetLnVulnerabilityState() ))
     && (GetVIOS_n_EngSpd() < V_RPM(200)))
   {
     if (KbCAN_CHERY_Fuel_Adjust_Enable ) {

		if ((!KW31_EndofLine_FuelAdjustMode) && (Pb_FuelAdjustOnlyonetime_enable == false)) {

            /* check the injector error */
			result = (SaINJD_CktTestFailed[0] || SaINJD_CktTestFailed[1] || \
				     SaINJD_CktTestFailed[2] || SaINJD_CktTestFailed[3]);
			/* check the fuel pump error */
			result = (result || SbEMSD_FPRDShortHiTestFailed || SbEMSD_FPRDShortLoTestFailed);
			/* check the engine turning flag */
			result = (result || GetEngineTurning());
            if ((!result) && (GetVIOS_EngSt() == CeENG_KEYON)) { 
					/*adjust the injector port to GPIO Mode*/
					HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(true);
					/* shut down the GPIO output */
					HAL_GPIO_SET_INJECTION_Enable(false);
					B_EOL_FuelAdjust = true ;
					E_EOL_FuelAdjust = false ;
					KW31_EndofLine_FuelAdjustMode = true;
					return 0x00;
			 }else {
					B_EOL_FuelAdjust = false ;
					E_EOL_FuelAdjust = true ;
					/* shut down the GPIO output */
					HAL_GPIO_SET_INJECTION_Enable(false);
					/*adjust the injector port back to tpu*/
					HAL_GPIO_SET_INJECTION_GPIO_Mode_Enable(false);
					return ConditionsNotCorrectOrRequestSequenceError;
			 }
		}else{

			return ConditionsNotCorrectOrRequestSequenceError;
		}

	 }else{
     		
       return ServiceIdNotSupported;

	 }
			
   }
   else
   {
      return ConditionsNotCorrectOrRequestSequenceError;
   }
 
} /*** End of KwJ14230StopDiagnosticSession ***/

 
/**
 * Handlerfunction for RC 0x03
 * Length=2: 'RoutineControl'
 */
 static  uint8_t DS_RC_0930_Handler(uint8_t type)
{
   /* TODO: Insert code to perform RC handling! */
   uint8_t status = 0x00;

   if(GetLnServiceDataLength() == 4)
   {
      switch(type)
      {
         case 0x01:  /* StartRoutine */
            status = StartRoutineByLocalIdentifier();
         break;
         case 0x02:  /* StopRoutine */
         case 0x03:  /* requestRoutineResult */
         default:
            status = SubFunctionNotSupported_InvalidFormat;
      }
      SetDCAN_SRV31_PosRespLength(4);
   }
   else
   {
      status = IncorrectMessageLength;
   }
   return status;
}

 
static uint8_t DS_RC_F000_Handler(uint8_t type)
{
   /* TODO: Insert code to perform RC handling! */
   uint8_t status = 0x00;

   if(GetLnServiceDataLength() == 4)
   {
      switch(type)
      {
         case 0x01:  /* StartRoutine */
            status = SetCopyAndExecuteKernel();
         break;
         case 0x02:  /* StopRoutine */
         case 0x03:  /* requestRoutineResult */
         default:
            status = SubFunctionNotSupported_InvalidFormat;
      }
      SetDCAN_SRV31_PosRespLength(4);
   }
   else
   {
      status = IncorrectMessageLength;
   }
   return status;
}


/**
 * Array of DS_ROUTINE_CTRL structures defining the available RoutineControl 
 * parameters. The RoutineControl records must be sorted with the identifier with
 * the lowest value first.
 * See the definition of type DS_ROUTINE_CTRL for information about the members.
 */
 const DS_ROUTINE_CTRL DS_RoutineControl[DS_NUM_ROUTINE_CTRL] =
{
/*  Identifier,                          Protected,  HandlerFunc */
    {0x0930,                             true,       DS_RC_0930_Handler           },
    {0xF000,                             true,       DS_RC_F000_Handler           }
// #if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
//    && (XbIMMO_KOSTAL_SUBS_SELECT_FLAG == CbSUBS_ON) )
//    ,{CyIMMO_Kostsal_EOL_RID_B20A,        false,      KostalIMMO_EOL_Handler_B20A        }
//    ,{CyIMMO_Kostsal_EOL_RID_B20B,        false,      KostalIMMO_EOL_Handler_B20B        }
//    ,{CyIMMO_Kostsal_EOL_RID_B20C,        false,      KostalIMMO_EOL_Handler_B20C        }
//    ,{CyIMMO_Kostsal_EOL_RID_B20D,        false,      KostalIMMO_EOL_Handler_B20D        }
//    ,{CyIMMO_Kostsal_EOL_RID_B10A,        false,      KostalIMMO_EOL_Handler_B10A        }
//    ,{CyIMMO_Kostsal_ChangePEPS_RID_B205, false,      KostalIMMO_ChangePEPS_Handler_B205 }
//    ,{CyIMMO_Kostsal_ChangePEPS_RID_B206, false,      KostalIMMO_ChangePEPS_Handler_B206 }
//    ,{CyIMMO_Kostsal_ChangePEPS_RID_B207, false,      KostalIMMO_ChangePEPS_Handler_B207 }
//    ,{CyIMMO_Kostsal_ChangePEPS_RID_B105, false,      KostalIMMO_ChangePEPS_Handler_B105 }
// #endif
// #if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
//    && (XbIMMO_HIRAIN_SUBS_SELECT_FLAG == CbSUBS_ON) )
//    ,{CyIMMO_HIRAIN_EOL_RID_0209,         true,       HIRAINIMMO_EOL_Handler_0209        }
// #endif
// #if ( (XbIMMO_MULTI_SUBS_SELECT_FLAG == CbSUBS_ON) \
//    && (XbIMMO_VALEO_SUBS_SELECT_FLAG == CbSUBS_ON) )
//    ,{CyIMMO_Valeo_LearnSK_RID,            true,       ValeoIMMO_LearnSK_Handler }
//    ,{CyIMMO_Valeo_TeachSK_RID,            true,       ValeoIMMO_LearnSK_Handler }
//    ,{CyIMMO_Valeo_RstECM_RID,             true,       ValeoIMMO_LearnSK_Handler }
// #endif
};

void LnRoutineControl(void)
{
   uint16_t  index, routineId;
   const DS_ROUTINE_CTRL* routineCtrl;
   uint8_t  routineCtrlType;
   uint8_t  rc;
   bool suppressPosRespMsgIndicationBit;
   bool ValidIndex;

   index=0;
   ValidIndex = false;
   if(GetLnServiceDataLength() < 4)
   { 
      /* DS_Request should be atleast 4 bytes long */
      SendLnStandardNegativeAnswer (IncorrectMessageLength);
   }
   else
   {
      suppressPosRespMsgIndicationBit = ((GetLnServiceData ()) [1] & 0x80) ? true: false;
      routineId = (((GetLnServiceData ()) [2]*0x100) + (GetLnServiceData ()) [3]);
      while((index<DS_NUM_ROUTINE_CTRL) && !ValidIndex)
      {
         if(routineId == (DS_RoutineControl[index].Identifier))
         {
            ValidIndex = true;
         }
         else
         {
            index++;
         }
      }
      routineCtrl = &DS_RoutineControl[index];
      routineCtrlType = ((GetLnServiceData ()) [1] & 0x7f);
      if(!ValidIndex)
      {/* There is no routineControl whith the requested id */
         SendLnStandardNegativeAnswer (RequestOutOfRange);
      }
      else if( (routineCtrl->Protected) && ( 
	  	       ( !IsSecurityAccessUnlocked() )
	  	       ) )
      {/* Protected routineControl and SecurityAccess is not called */
         SendLnStandardNegativeAnswer (SecurityAccessDenied);
      }
      else
      {
         if( (0x01 == routineCtrlType)
          || (0x02 == routineCtrlType)
          || (0x03 == routineCtrlType) )
         {
            rc = routineCtrl->HandlerFunc(routineCtrlType);        
            if( rc == 0x00 )
            {
               if( suppressPosRespMsgIndicationBit )
               {
                  PfrmDCAN_AckReqWithoutResponse();
               }
               else
               {
                  SendLnStandardPositiveAnswer (VyDCAN_SRV31_PosRespLength);
               }
            }
            else 
            {
               SendLnStandardNegativeAnswer (rc);
            }
         }
         else
         {
            SendLnStandardNegativeAnswer (SubFunctionNotSupported_InvalidFormat);
         }
      }
   }
}

#endif

