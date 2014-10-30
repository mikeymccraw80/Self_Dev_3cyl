#ifndef KW2SRV30_H
#define KW2SRV30_H
/* ============================================================================ *\
 * kw2srv30.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       kw2srv30.h-1:incl:mt20a#1
 * Revision:        1
 * Creation date:   Thursday, June 20, 2002 1:37:40 PM
 * Last changed:    %date_modified%
 *
 * Description:
 *   This file contains kw2000 service $30 - Input/output control by local identifier
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

#include "io_type.h"
#include "t_base.h"
#include "t_user.h"

/*--- IO Local Ids: Group On/Off [01h..06h] ---*/
#define ioliCheckLight                  (0x01)
#define ioliCharcoalCanisterPurgeOnOff  (0x02)
#define ioliFuelPumpRelay               (0x03)
#define ioliAIRPumpRelay                (0x04) /*--- Not Used ---*/
#define ioliAIRSolenoid                 (0x05) /*--- Not Used ---*/
#define ioliACCutoffRelay               (0x06)
#define ioliFan1                        (0x08)
#define ioliFan2                        (0x09)
#define ioliCoolTempLamp                (0x0A)
#define ioliMIVECSolenoid               (0x0B)
/*--- IO Local Ids: Group Control [80h..8Ah] ---*/
#define ioliDwellTime                   (0x80)
#define ioliSparkAdvance                (0x81)
#define ioliIdleAdjustInParkNeutral     (0x82)
#define ioliDesiredIdle                 (0x83)
#define ioliAirFuelRatio                (0x84)
#define ioliLegrPulseRatio              (0x85)
#define ioliVolumetricEfficiency        (0x86)
#define ioliIdleAirControl              (0x87)
#define ioliCharcoalCanisterPurge       (0x88)
#define ioliIdleAdjustInDrive           (0x89)
#define ioliPWMFanDutyCycle             (0x8A)
/*--- IO Local Ids: Group Activate [E1h..E5h] ---*/
#define ioliIgnitionSparkTestSequence   (0xE1)
#define ioliInjectorCutoffTest          (0xE2)
#define ioliSeedAndKey                  (0xE3) /*--- Not Used ---*/
#define ioliQDSMFaultIsolation          (0xE4) /*--- Not Used ---*/
#define ioliInjectorFaultIsolation      (0xE5)
#define ioliFactoryTest                 (0xE6)
#define ioliIgnitionTest                (0xE7)
/*--- IO Local Ids: Group Reset [F0h..F2h] ---*/
#define ioliIdleAirControlBLM           (0xF0)
#define ioliO2BLMCells                  (0xF1)
#define ioliKnockControlSlowCellReset   (0xF2)
/*--- IO Local Ids: Group Learn {FEh} ---*/
#define ioliLearnImmobilizer            (0xFE) /*--- Not Used ---*/

/*--- IO Control Parameters                          used: ---*/
#define iocpReturnControlToECU          (0x00)  /*--- YES  ---*/
#define iocpReportCurrentState          (0x01)  /*--- YES  ---*/
#define iocpReportIOConditions          (0x02)  /*---  no  ---*/
#define iocpReportIOScaling             (0x03)  /*---  no  ---*/
#define iocpResetToDefault              (0x04)  /*--- YES  ---*/
#define iocpFreezeCurrentState          (0x05)  /*--- YES  ---*/
#define iocpExecuteControlOption        (0x06)  /*---  no  ---*/
#define iocpShortTermAdjustment         (0x07)  /*--- YES  ---*/
#define iocpLongTermAdjustment          (0x08)  /*--- YES  ---*/
#define iocpReportCalibrationParameters (0x09)  /*--- YES  ---*/
#if PC_HUD == ENABLED
#define iocpAddOffset                   (0x80)  /*--- YES  ---*/
#define iocpSubOffset                   (0x81)  /*--- YES  ---*/
#define iocpReportSlewState             (0x82)  /*--- YES  ---*/
#endif /* PC_HUD */



/*****************************************************************************
 *  Global Data Define
 *****************************************************************************/

typedef struct
{
  
  TbBOOLEAN  VbOFVC_RqstPending;
  BYTE       VyOFVC_Device;
  BYTE       VyOFVC_Request;
  BYTE       VyOFVC_Action1;
  BYTE       VyOFVC_Action2;
  BYTE       VyOFVC_Response;

} TsOFVC_OvrdMessage;


extern TsOFVC_OvrdMessage VsOFVC_OvrdRqstStruct;
extern bool R_LineEnable;

/*****************************************************************************
 * PUBLIC:
 *****************************************************************************/
//extern FAR_COS void PostOFVC_ResponseToRequest (void) ;
extern void KwJ14230InputOutputControlByLocalIdentifier (void) ;
extern BYTE GetOFVC_PID_OvrdReqResp (void) ;
extern void FormAndSendImmoData (void);

/*****************************************************************************
 * INTERFACE:
 *****************************************************************************/

/*****************************************************************************
 *  IO Local Identifier and parameter values
 *****************************************************************************/

#define CeOFVC_RETURN_CTRL_TO_ECU 0x00
#define CeOFVC_RPT_CURRENT_STATE  0x01
#define CeOFVC_RPT_IO_CONDITIONS  0x02
#define CeOFVC_RPT_IO_SCALING     0x03
#define CeOFVC_RST_TO_DEFAULT     0x04
#define CeOFVC_FRZ_CRNT_STATE     0x05
#define CeOFVC_EXECUTE_CTRL_OPT   0x06
#define CeOFVC_SHORT_TERM_MODIFY  0x07
#define CeOFVC_LONG_TERM_MODIFY   0x08
#define CeOFVC_RPT_CAL_PARAMS     0x09

/*****************************************************************************
 *  INLINES:
 *****************************************************************************/

/* This function is a dummy to be compatible with application layer device */
/* control, which may be used with other protocols which allow responses   */
/* without a tester request */
INLINE void NotifyOFVC_InvalidConditionExit (BYTE LyOFVC_Reason)
{

}

INLINE void ClearOFVC_OvrdRqstPending (void)
{
  VsOFVC_OvrdRqstStruct.VbOFVC_RqstPending = CbFALSE;
}

INLINE void SetOFVC_OvrdRqstPending (void)
{
  VsOFVC_OvrdRqstStruct.VbOFVC_RqstPending = CbTRUE;
}


#define GetOFVC_OvrdRqstPending()\
        (VsOFVC_OvrdRqstStruct.VbOFVC_RqstPending) 



#define GetOFVC_OvrdDevice()\
        (VsOFVC_OvrdRqstStruct.VyOFVC_Device) 


#define GetOFVC_OvrdRequest()\
        (VsOFVC_OvrdRqstStruct.VyOFVC_Request) 



#define GetOFVC_OvrdAction1()\
        (VsOFVC_OvrdRqstStruct.VyOFVC_Action1) 



#define GetOFVC_OvrdAction2()\
        (VsOFVC_OvrdRqstStruct.VyOFVC_Action2) 



INLINE void SetOFVC_OvrdReqResp (BYTE LyOFVC_Response)
{
  VsOFVC_OvrdRqstStruct.VyOFVC_Response = LyOFVC_Response;
}

#define GetOFVC_OvrdReqResp()\
        (VsOFVC_OvrdRqstStruct.VyOFVC_Response)



/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 23/10/02     pllye       80
 * + Added LEGR logic.
 * - Added KWP2000 IO control for LEGR.
 *
 * 25/03/03     tmhau       97
 * + Slew VE by KWP2000 / MDS
 *   - Add VE Slew, Remove BPW Slew
 *
 * 25/09/04     Q.W        213
 * +Reused MT20U RSMs for PWMFan logic.
 *   - Add ioliPWMFanDutyCycle
 *
 * Aug/22/05    Q.W     mt20u2#17
 * + Add Tooth Error Correction Diangostic (TECD) module 
 *  - rewrite kw2k SID30 to support standard EOL(OFVC) function. 
 *
 * Nov/23/05    Q.W     mt20u2#32
 * + Add PID parameters for Autotune support(ID22)
 *  - declare function  GetOFVC_PID_OvrdReqResp to far call function 
 *
 * 25/01/06     LShoujun    mt20u2#44
 * + Add DVT Function
 *   - Defined GetPCHUDSlew_Active() to disable DVT when Slew function is active
 *
 * 09/06/06     Jerry.Wu    mt20u2#51
 * + Update kword spec
 *   - Add kw2srv30exec.h
 *
 * 17/04/07     dzb1zg      mt20u2#104  
 * + MIVEC control
 *
 * 22/11/07	   Yu Runwu    mt20u2#194
 * + Implement CJAE Immobilizer and Remove Old Immobilizer
 *   - Declare the FormAndSendImmoData().
\* ============================================================================ */
#endif

