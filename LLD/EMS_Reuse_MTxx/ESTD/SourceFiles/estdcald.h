#ifndef ESTDCALD_H
#define ESTDCALD_H

/*****************************************************************************
* Filename:              estdcald.h                                           
*                                                                             
* Description:  Calibration file for EST Diagnostic subsystem                 
*                                                                             
* List of functions: None                                                     
*                                                                             
* List of inlines: None                                                       
*                                                                             
*                                                                             
* C Software Project FORWARD EMS                                              
* (c) Copyright Delco Electronics  2003                                       
*****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files                                           *
 *****************************************************************************/
#include "estdfexi.h" /* For ESTD GLobal Input */
#include "t_gentypes.h" /* For Global Input */

/*****************************************************************************
 *  Calibration declarations for AC Detect
 *****************************************************************************/
extern const T_COUNT_BYTE       KcESTD_FailThrsh;
extern const T_COUNT_BYTE       KcESTD_SampleThrsh;
extern const T_COUNT_BYTE       KcESTD_NumOfEST_Outputs;
extern const T_VOLTb            KfESTD_U_IgnVoltResetThrsh;
extern const TwTIME_t_R7p8125ms KfESTD_t_EnableDelayTime;

#endif
/******************************************************************************
* 
******************************************************************************
* 
******************************************************************************/
