/*****************************************************************************
* Filename:                   estdcald.c
*                                                                           
* Description:                Calibration file for EST Diagnostic subsystem
*
* List of functions:                                  
*                                       
* List of inlines:
*
* C Software Project FORWARD EMS
* (c) Copyright Delco Electronics  1997     
*****************************************************************************/

/*****************************************************************************
 *  Include Files 
 *****************************************************************************/
#include "estdcald.h" /* For Declaration-Definition Check */

/*****************************************************************************
 *  Calibration declaration for EST diagnostic module 
 *****************************************************************************/
/*
*| estdcald.{
*|   KcESTD_FailThrsh {
*|     : is_calconst;
*|     : description ="Indicates the number of samples that can register a \
failure before a fault is set for that EST output. Range 0 to 255. ";
*|     : type = fixed.estd_t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE KcESTD_FailThrsh = V_COUNT_BYTE(5);

/*
*| estdcald.{
*|   KcESTD_SampleThrsh {
*|     : is_calconst;
*|     : description ="Indicates the total number of samples taken before a \
passing result can be reported to the Data Manager. Range 0 to 255. ";
*|     : type = fixed.estd_t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE KcESTD_SampleThrsh = V_COUNT_BYTE(15);


/*
*| estdcald.{
*|   KfESTD_U_IgnVoltResetThrsh {
*|     : is_calconst;
*|     : description =" Voltage threshold used to prevent false failure "
*| " indication when the ignition is cycled quickly as the engine is "
*| " turning. Due to hardware characteristics, the EST failure register "
*| " bits may set during an ignition transistion (key_0n to Key_off) "
*| " with RPM > 0 ";
*|     : type = fixed.estd_t_voltb;
*|     : units = "volts";
*|   }
*| }
*/
const T_VOLTb KfESTD_U_IgnVoltResetThrsh = V_VOLTb(11);

/*
*| estdcald.{
*|   KfESTD_t_EnableDelayTime {
*|     : is_calconst;
*|     : description =" Timer threshold used to indicate sufficient time "
*| " has elapsed since an engine at OFVC diagnostic clear has occurred "
*| " to enable the diagnostic. Due to hardware characteristics, the EST "
*| " failure register bits may set during an ignition transition (Key_off "
*| " to Key_on) with RPM >0 ";
*|     : type = fixed.estd_t_w_R7p8125ms;
*|     : units = "seconds";
*|   }
*| }
*/
const TwTIME_t_R7p8125ms KfESTD_t_EnableDelayTime = C_R7p8125ms16(0);



/*****************************************************************************
*
*
******************************************************************************/
