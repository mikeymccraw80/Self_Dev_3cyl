;******************************************************************************
;**                        Copyright (c) 2001 Delphi DE
;**                          All rights reserved.
;**                  Developed under contract by ETAS, Inc.
;**
;** File Name:    init_code.pri
;** Project:      Delphi EMS_Core Configuration Development
;** File Type:    ProF Configuration File
;** CM ID:
;** Description:  Routine to make initial connect with INCA.
;**
;** Revision History: 
;** Date     Engineer   Changes
;** ---------------------------------------------------------------------------
;** 03/20/01 * DLN      Initial release.
;** 04/10/01 * DLN      New file for parameterization.
;** 03/06/02 * JWD      Allow cancelling before beginning programming
;******************************************************************************

procedure init
{
  [RE_ENTRY]
   EXTENDED_MESSAGE(FALSE)
   DEFAULT_SCREEN_LAYOUT (0)
   CHECK_INCA_CONFIGURATION
   case TRUE : init_prog
   default:  zndg_ein
  [RE_ENTRY_END]

  [zndg_ein]
   DISPLAY_MESSAGE("",FALSE)
   DISPLAY_MESSAGE("            Cannot connect to INCA device...           ",FALSE)
   DISPLAY_MESSAGE("   please check the CAN connection ...",GREEN_FALSE)
   DISPLAY_MESSAGE("",FALSE)
   default: WAIT_INCA
  [zndg_ein_END]

  [WAIT_INCA]
   DISPLAY_MESSAGE("",OVER_WRITE)
   CHECK_INCA_CONFIGURATION
   case TRUE: init_prog
   default: WAIT_KEY
  [WAIT_INCA_END]

  [WAIT_KEY]
   WAIT_FOR_KEY (1)
   case ESCAPE: dsp_break
   default: WAIT_INCA
  [WAIT_KEY_END]

  [dsp_break]
   DISPLAY_MESSAGE ("    Cannot initialize...", BLINK_FALSE)
   default : EXIT
  [dsp_break_END]

  [init_prog]
   INIT_FLASH_PROGRAMMING (ECU_ADDRESS, 1, CONFIG_CODE)
   case TRUE: CONVERT_BIN
   default : $return
  [init_prog_END]

  [CONVERT_BIN]
   DISPLAY_MESSAGE (" ",FALSE)
   CALL (convert)
   case FALSE : $return FALSE
   default : init_kw
  [CONVERT_BIN_END]

  [init_kw]
    DISPLAY_MESSAGE(" To begin flashing : Click Continue...",TRUE)
    case TRUE : UNLOCK_BOX
    default : $return FALSE 
  [init_kw_END]
 
  [UNLOCK_BOX]
    DISPLAY_MESSAGE (" ",FALSE);
    START_COMMUNICATION
    DISPLAY_MESSAGE ("     Unlocking the ECM ...",FALSE)
    case TRUE: INITLOOP
    default: ACCESS_ERROR
  [UNLOCK_BOX_END]

  ;
  ; Initialize a loop to retry the KW 10 message a few times before
  ; giving up on communicating with the module....
  [INITLOOP]
    DISPLAY_MESSAGE (" ",FALSE);
    SET_LOOP_COUNTER (3)
    default : LOOP
  [INITLOOP_END]

  [LOOP]
    DISPLAY_MESSAGE("     ECM Successfully Unlocked ... ",FALSE)
    DISPLAY_MESSAGE("     Initializing Programming Mode ... ",FALSE)
    START_DIAGNOSTIC_SESSION (0)
    case TRUE : $return
    default :	retry
  [LOOP_END]

  [retry]
    ; 
    ; Something failed, decrement the loop counter and try again...
    DISPLAY_MESSAGE ("", FALSE);
    DISPLAY_MESSAGE (" Initial attempt to connect failed, trying again...", FALSE)
    DISPLAY_MESSAGE (" ", FALSE);
    DEC_LOOP_COUNTER
    case 0 : DSP_ERROR
    default : LOOP
  [retry_END]

[ACCESS_ERROR]
    DISPLAY_MESSAGE ("", FALSE);
    DISPLAY_MESSAGE (" ERROR-ERROR  Unable to UNLOCK the ECM ERROR-ERROR..", FALSE)
    DISPLAY_MESSAGE (" ", FALSE);
    default : DSP_ERROR
[ACCESS_ERROR_END]

[DSP_ERROR]
   DISPLAY_MESSAGE ("", FALSE);
   DISPLAY_MESSAGE ("", FALSE);
   DISPLAY_MESSAGE (" ERROR-ERROR-ERROR-ERROR-ERROR-ERROR-ERROR-ERROR-ERROR-ERROR-ERROR-ERROR-ERROR", RED_FALSE)
   DISPLAY_MESSAGE ("         session aborted by error", BLINK_FALSE)
   DISPLAY_MESSAGE (" ", FALSE);
   DISPLAY_MESSAGE ("  If you can't solve your problem, please contact the support line  ", GREEN_FALSE)
   DISPLAY_MESSAGE ("  and have the files FPSTAT.PRT and INCAPROT.LOG from the temporary ", GREEN_FALSE)
   DISPLAY_MESSAGE ("  directory of your PC (e.g. C:\WINDOWS\TEMP) ready (e.g. for fax)  ", GREEN_FALSE)
   EXTENDED_MESSAGE(FALSE)
   default : $return FALSE
[DSP_ERROR_END]

}
