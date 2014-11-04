/*-------------------------------------------------------------------*/
/* filename -  DCANSV2F.C                                            */
/*                                                                   */
/* purpose:                                                          */
/*    This module is application layer of the Delco Electronics      */
/*    engine control s/w, where the GMLAN diagnostics services       */
/*    are processed. This module contains CPID functions.            */
/*                                                                   */
/*    LN stands for Local Network                                    */
/*                                                                   */
/*                                                                   */
/*                                                                   */
/*-------------------------------------------------------------------*/
/* DELPHI Delco Luxembourg C Engine Management Software              */
/* (c) Copyright DELPHI Delco Electronics Systems 2001, 2008         */
/*-------------------------------------------------------------------*/

 /****************************************************************************
 *
 * Current Module Info:
 * %full_name:      ctc_pt3#1/csrc/dcansv2f.c/5 %
 * %date_created:   Thu Jun 26 10:57:05 2014 %
 * %version:        5 %
 * %derived_by:     dzrpmq %
 *
 *****************************************************************************/
#include "dcansv2f.h" 
#if (XeDCAN_SID_2F_Supported == CeDCAN_Supported)
/******************************************************************************
* APP Include Files
******************************************************************************/
/******************************************************************************
* CAN OBD Service Include Files
******************************************************************************/
/******************************************************************************
* OBD lib Service Include Files
******************************************************************************/
#include "ofvcpall.h"/*GetOFVC_OvrdDevice()*/
/******************************************************************************
* CAN OBD NW Layer Include Files
******************************************************************************/
#include "dcancomm.h"   /* for SubFunctionNotSupported_InvalidFormat..*/
#include "obdlcald.h"

/* this group defines the response codes for device control */
/* values passed back from the algorithm layer in the       */
/* .VyOFVC_Response byte                                    */

#define CyOFVC_LN_SUCCESSFUL                   0x00
#define CyOFVC_LN_VentVacuumTooHigh            0x01
#define CyOFVC_LN_AC_PressureNotInRange        0x03
#define CyOFVC_LN_EngSpdTooHigh                0x05
#define CyOFVC_LN_VSS_Fault                    0x02
#define CyOFVC_LN_VSS_Not_Zero                 0x01
#define CyOFVC_LN_RPM_Not_Zero                 0x01
#define CyOFVC_LN_InjFlowTestInProgress        0x04
#define CyOFVC_LN_InjTestLimitExceeded         0x02
#define CyOFVC_LN_InjAlreadyTested             0x05
#define CyOFVC_LN_PurgeVacuumTooHi             0x01
#define CyOFVC_LN_SparkRqstOutOfRange          0x01
#define CyOFVC_LN_InvalidInjectorNum           0x03
#define CyOFVC_LN_Eng_RUN_Evap_SerBay          0x03
#define CyOFVC_LN_Transmission_in_Gear         0x02
#define CyOFVC_LN_AutoTransLoad_NotInPark      0x01
#define CyOFVC_LN_AutoTransLoad_EngineRunning  0x02
#define CyOFVC_LN_EngineNotIdle                0x01

#define CyLimitExceedCondtn                    0xE3

#define CyOFVC_LN_MAX_NUM_RESPONSES 22

/*****************************************************************************
 *  Local Data Define
 *****************************************************************************/
const BYTE CyOFVC_LN_MessageResponseTranslate[CyOFVC_LN_MAX_NUM_RESPONSES] =
{
   CyOFVC_LN_SUCCESSFUL,                              /* affirmative */
   SubFunctionNotSupported_InvalidFormat,
   ConditionsNotCorrectOrRequestSequenceError,
   CyOFVC_LN_VentVacuumTooHigh,
   CyOFVC_LN_AC_PressureNotInRange,
   CyOFVC_LN_EngSpdTooHigh,
   CyOFVC_LN_VSS_Fault,
   CyOFVC_LN_VSS_Not_Zero,
   CyOFVC_LN_RPM_Not_Zero,
   CyOFVC_LN_InjFlowTestInProgress,
   CyOFVC_LN_InjTestLimitExceeded,
   CyOFVC_LN_InjAlreadyTested,
   CyOFVC_LN_PurgeVacuumTooHi,
   CyOFVC_LN_SparkRqstOutOfRange,
   CyOFVC_LN_InvalidInjectorNum,
   CyOFVC_LN_Eng_RUN_Evap_SerBay,
   CyOFVC_LN_Transmission_in_Gear,
   CyOFVC_LN_AutoTransLoad_NotInPark,
   CyOFVC_LN_AutoTransLoad_EngineRunning,
   CyOFVC_LN_EngineNotIdle,
   RequestOutOfRange,
   CyLimitExceedCondtn
};

/* standard outgoing message length for transmitted device control response */
#define CyOFVC_LnDevCntrlStdTXMsgLength 4
#if XeSYST_CO_ADJUST_OPTION == CeSYST_AVAILABLE
#define CyOFVC_LnDevCntrlCOATXMsgLength 2//6832 Modified as standard positive response as per GMW3110 is 2 bytes
#define COAdjustDeviceCtrl 0x01
#endif

#define CyOFVC_LN_DATA1   1
#define CyOFVC_LN_DATA2   2
#define CyOFVC_LN_DATA3   3
#define CyOFVC_LN_DATA4   4
#define CyOFVC_LN_DATA5   5
#define CyOFVC_LN_DATA6   6

/*****************************************************************************
 *  static Variable 
 *****************************************************************************/
#if XeSYST_CO_ADJUST_OPTION == CeSYST_AVAILABLE
static T_COUNT_BYTE          SyDCAN_OvrdResponseLength;
#endif 

/*****************************************************************************
 *
 * Function:           PostOFVC_ResponseToRequest
 * Description:        Callback for application layer to post a response to
 *                     a GMLAN device control request
 *
 * Parameters:         None
 * Return:             None
 *****************************************************************************/
void PostOFVC_LnResponseToRequest (void)
{
   BYTE LyOFVC_Response;

   VsOFVC_OvrdRqstStruct.VbOFVC_RqstPending = CbFALSE ;

   if( VsOFVC_OvrdRqstStruct.VyOFVC_Response < CyOFVC_LN_MAX_NUM_RESPONSES )
   {
      /* decode the response sent to us by the OFVC layer */
      LyOFVC_Response = CyOFVC_LN_MessageResponseTranslate[VsOFVC_OvrdRqstStruct.VyOFVC_Response] ;

      /* NOTE that a failure to execute a device control request may still    */
      /* return a positive message. The format of the positive message is as  */
      /* follows:                                                             */
      /* Byte 1 = Device ID (the number of the device you want to control)    */
      /* Byte 2 = Control request (short term mod, rtn ctrl to ecu, etc...)   */
      /* Byte 3 = Response code (00 = success, != 00 means limit cond met)    */
      /* The length of the message must still be 4 even though we're only     */
      /* filling 3 bytes because WrtKw2000ServiceData automatically adds 40h  */
      /* to the mode byte and shoves it in the TX buffer, but doesn't account */
      /* for that byte in the message length it gets from your call           */

      if( ( LyOFVC_Response != SubFunctionNotSupported_InvalidFormat ) &&
          ( LyOFVC_Response != ConditionsNotCorrectOrRequestSequenceError ) &&
          ( LyOFVC_Response != RequestOutOfRange ) &&
          ( LyOFVC_Response != CyLimitExceedCondtn ) )
      {
        // (GetLnServiceData ()) [CyOFVC_LN_DATA1] = VsOFVC_OvrdRqstStruct.VyOFVC_Device;
        #if XeSYST_CO_ADJUST_OPTION == CeSYST_AVAILABLE
         if ( GetOFVC_OvrdDevice () == COAdjustDeviceCtrl )
         {
            SendLnStandardPositiveAnswer (SyDCAN_OvrdResponseLength);
         }
        
		 else
	 #endif
		 {
		   (GetLnServiceData ()) [CyOFVC_LN_DATA3] = LyOFVC_Response;
		   SendLnStandardPositiveAnswer (CyOFVC_LnDevCntrlStdTXMsgLength);
		 }
      }
      else
      {
           
         /* send the negative response, mode 7Fh, with one of the allowed fail */
         /* codes.                                                             */
		if ( LyOFVC_Response != CyLimitExceedCondtn )
          {
            SendLnStandardNegativeAnswer (LyOFVC_Response) ;
		  }
		else
		 {
		    SendLimitExceedNegativeAnswer (LyOFVC_Response) ;
		 }
      }
   }
}


/**********************************************************************/
/*** LnDiag service: LnInputOutputControlByIdentifier                                 ***/
/**********************************************************************/
void LnInputOutputControlByIdentifier (void)
{

  /*--- After 5sec, initial state is restored ----*/
//  LnActivateTesterPresent ();
  if((GetLnServiceDataLength()<4)
  	||(GetLnServiceDataLength()>5))
  {
     SendLnStandardNegativeAnswer(IncorrectMessageLength);    
  }
  else if( (KaDCANOBD_SecurityAccessUsedService[CeServiceID_2F] == CeService_SecurityAccessUsed)
           &&(!GetLnVulnerabilityState()) )
  {
     SendLnStandardNegativeAnswer(SecurityAccessDenied);  
  }
  else if ((GetLnServiceData ())[CyOFVC_LN_DATA1] == 0x20)
  {
     switch (GetLnServiceDataLength ())
     {
         case  (5): 
           if((GetLnServiceData ()) [CyOFVC_LN_DATA3]!=0x00)
           {
              VsOFVC_OvrdRqstStruct.VyOFVC_Action1 = (GetLnServiceData ()) [CyOFVC_LN_DATA4];
              VsOFVC_OvrdRqstStruct.VyOFVC_Request = (GetLnServiceData ()) [CyOFVC_LN_DATA3] ;
              VsOFVC_OvrdRqstStruct.VyOFVC_Device = (GetLnServiceData ()) [CyOFVC_LN_DATA2] ;
              VsOFVC_OvrdRqstStruct.VbOFVC_RqstPending = CbTRUE ;
           }
           else
           {
              SendLnStandardNegativeAnswer(IncorrectMessageLength) ;            
           }
         break;

         case  (4):
           if((GetLnServiceData ()) [CyOFVC_LN_DATA3]==0x00)
           {
              VsOFVC_OvrdRqstStruct.VyOFVC_Request = (GetLnServiceData ()) [CyOFVC_LN_DATA3];
              VsOFVC_OvrdRqstStruct.VyOFVC_Device = (GetLnServiceData ()) [CyOFVC_LN_DATA2];
              VsOFVC_OvrdRqstStruct.VbOFVC_RqstPending = CbTRUE;
           }
           else
           {
              SendLnStandardNegativeAnswer(IncorrectMessageLength) ; 
           }
         break;
			
         default:
            SendLnStandardNegativeAnswer(IncorrectMessageLength) ;
         break;
     }
  }
  else
  {
      SendLnStandardNegativeAnswer(RequestOutOfRange);
  }
} /*** End of LnDeviceControl ***/

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* ---------------------------------------------------------------------
* After RSM 6865 Communication Project Clean up
* ---------------------------------------------------------------------
* tcb_pt1#2
*       080613  mt -BM- Manually Merged in changes from RSMs created
*                       from an old J300 baseline before the COMM cleanup.
* 2     120307   cjqq Add GetLnServiceDataLength() condition.
* 3     120409   cjqq Update the CANOBD per customer requirement  
* 4     130118   xll  RCR#1036 Add new CAL variable array to specify Service ID $2E 
*                         & 2F if these SID need unlock  the security access 
******************************************************************************/

