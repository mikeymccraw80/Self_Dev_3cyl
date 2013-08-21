#ifndef DD_VSEP_VR_H
#define DD_VSEP_VR_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_vr.h~2:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:09:07 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Fri Feb 16 11:29:19 2007 %
//
// %version:         2 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

#include "dd_vsep.h"

typedef enum 
{
                                                        //[ 6: 0] Reserved by VSEP.h
   VSEP_VR_CONFIGURATION_POSITION_INITIAL_DELAY    = 7, //[18: 7] VRDLY
   VSEP_VR_CONFIGURATION_POSITION_MIN_THRESH       =19, //[21:19] MT
   VSEP_VR_CONFIGURATION_POSITION_ADAPT_THRESH     =22, //    22  ATS 30% or 50%
   VSEP_VR_CONFIGURATION_POSITION_SETUP            =23, //[26:23] MT&ATS value
   VSEP_VR_CONFIGURATION_POSITION_CHANNEL          =27  //    27  VR Index (0-1)
}VSEP_VR_Configuration_Position_T;

typedef enum 
{
                                                         //[ 6: 0] Reserved by VSEP.h
   VSEP_VR_CONFIGURATION_WIDTH_INITIAL_DELAY       =12,  //[18: 7] VRDLY
   VSEP_VR_CONFIGURATION_WIDTH_MIN_THRESH          = 3,  //[21:19] MT
   VSEP_VR_CONFIGURATION_WIDTH_ADAPT_THRESH        = 1,  //    22  ATS 30% or 50% 
   VSEP_VR_CONFIGURATION_WIDTH_SETUP               = 4,  //[26:23] MT&ATS value
   VSEP_VR_CONFIGURATION_WIDTH_CHANNEL             = 1   //    27  VR Index (0-1)
}VSEP_VR_Configuration_Width_T;



typedef enum
{
   VSEP_VR_ADAPTIVE_THRESHOLD_30,
   VSEP_VR_ADAPTIVE_THRESHOLD_50
}VSEP_VR_Adaptive_Threshold_T;

//=============================================================================
// VSEP_VR_Set_Adaptive_Threshold
//
// @func Set desired adaptive threshold setting for the VR. 
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_VR_Adaptive_Threshold_T | y | A <t VSEP_VR_Adaptive_Threshold_T> raw value 
//    for the ATS.
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_VR_Adaptive_Threshold_T>
//
// @end
//=============================================================================
#define VSEP_VR_Set_Adaptive_Threshold(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_VR_CONFIGURATION_POSITION_ADAPT_THRESH, VSEP_VR_CONFIGURATION_WIDTH_ADAPT_THRESH ) )

//=============================================================================
// VSEP_VR_Get_Adaptive_Threshold
//
// @func Get desired adaptive threshold setting for the VR. 
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_VR_Adaptive_Threshold_T> raw value for ATS decoded from the 
//    <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_VR_Get_Adaptive_Threshold(x) \
   (VSEP_VR_Min_Threshold_T)( Extract_Bits( x, VSEP_VR_CONFIGURATION_POSITION_ADAPT_THRESH, VSEP_VR_CONFIGURATION_WIDTH_ADAPT_THRESH ) )

typedef enum
{
   VSEP_VR_MIN_THRESHOLD_250MVPP,
   VSEP_VR_MIN_THRESHOLD_335MVPP,
   VSEP_VR_MIN_THRESHOLD_600MVPP,
   VSEP_VR_MIN_THRESHOLD_825MVPP,
   VSEP_VR_MIN_THRESHOLD_1250MVPP,
   VSEP_VR_MIN_THRESHOLD_1650MVPP,
   VSEP_VR_MIN_THRESHOLD_1900MVPP,
   VSEP_VR_MIN_THRESHOLD_2500MVPP

}VSEP_VR_Min_Threshold_T;

//=============================================================================
// VSEP_VR_Set_Min_Threshold
//
// @func Set desired initial minimum threshold setting for the VR. 
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_VR_Min_Threshold_T | y | A <t VSEP_VR_Min_Threshold_T> raw value 
//    for the MT.
//
// @rdesc <t IO_Configuration_T> containing the element <t uint16_t>
//
// @end
//=============================================================================
#define VSEP_VR_Set_Min_Threshold(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_VR_CONFIGURATION_POSITION_MIN_THRESH, VSEP_VR_CONFIGURATION_WIDTH_MIN_THRESH ) )

//=============================================================================
// VSEP_VR_Get_Min_Threshold
//
// @func Get desired initial minimum threshold setting for the VR. 
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_VR_Min_Threshold_T> raw value for MT decoded from the 
//    <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_VR_Get_Min_Threshold(x) \
   (VSEP_VR_Min_Threshold_T)( Extract_Bits( x, VSEP_VR_CONFIGURATION_POSITION_MIN_THRESH, VSEP_VR_CONFIGURATION_WIDTH_MIN_THRESH ) )

//=============================================================================
// VSEP_VR_Get_Setup
//
// @func Get MT and the ATS values together. 
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> raw value for MT and ATS decoded from the 
//    <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_VR_Get_Setup( x )\
      (uint8_t)( Extract_Bits( x, VSEP_VR_CONFIGURATION_POSITION_SETUP, VSEP_VR_CONFIGURATION_WIDTH_SETUP ) )


//=============================================================================
// VSEP_VR_Set_Initial_Delay
//
// @func Set desired initial VR delay. This is a 12-bit value. The lower 5 bits 
//    are fixed to 01111 by the VSEP. The VSEP device driver will mask the lower 
//    5 bits to %01111.
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm uint16_t | y | A <t uint16_t> raw value for the VRDLY.
//
// @rdesc <t IO_Configuration_T> containing the element <t uint16_t>
//
// @end
//=============================================================================
#define VSEP_VR_Set_Initial_Delay(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_VR_CONFIGURATION_POSITION_INITIAL_DELAY, VSEP_VR_CONFIGURATION_WIDTH_INITIAL_DELAY ) )

//=============================================================================
// VSEP_VR_Get_Initial_Delay
//
// @func Get desired initial VR delay. This is a 12-bit value. The lower 5 bits 
//    are fixed to 01111 by the VSEP. The VSEP device driver will mask the lower 
//    5 bits to %01111.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t uint16_t> raw value for VRDLY decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_VR_Get_Initial_Delay(x) \
   (uint32_t)( Extract_Bits( x, VSEP_VR_CONFIGURATION_POSITION_INITIAL_DELAY, VSEP_VR_CONFIGURATION_WIDTH_INITIAL_DELAY ) )

//=============================================================================
// VSEP_VR_Get_Initial_Delay
//
// @func Convert the desirec VR delay to VR register value
//
// @parm float | delay | Delay in  microseconds.
//
// @rdesc <t uint16_t> raw value for VRDLY
//
// @comment This macro should not be used in code only for compile time constants.
//
// @end
//=============================================================================
#define VSEP_VR_Convert_Delay( delay )\
  (uint32_t)( ( delay - 4.0 ) / 8.0 )

typedef enum
{
   VSEP_VR_CHANNEL_VR1,
   VSEP_VR_CHANNEL_VR2,
   VSEP_VR_CHANNEL_MAX
}VSEP_VR_Channel_T;

typedef enum
{
   VSEP_VR_TXD_MESSAGE_CTRL,
   VSEP_VR_TXD_MESSAGE_VR1,
   VSEP_VR_TXD_MESSAGE_VR2,
   VSEP_VR_TXD_MESSAGE_MAX
}VSEP_VR_Txd_Message_T;

typedef enum
{
   VSEP_VR_RXD_MESSAGE_FLT,
   VSEP_VR_RXD_MESSAGE_VR_FLT,
   VSEP_VR_RXD_MESSAGE_NU_0,
   VSEP_VR_RXD_MESSAGE_MAX
}VSEP_VR_Rxd_Message_T;

extern uint16_t VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_MAX];
extern uint16_t VSEP_VR_Rxd[VSEP_VR_RXD_MESSAGE_MAX];

//=============================================================================
// VSEP_PULSE_Initialize_Device
//
// @func Initialize a timer-based device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PULSE_VR_Initialize_Device(void);

//=============================================================================
//  Used for mutilple types
//=============================================================================

//=============================================================================
// VSEP_PULSE_Initialize_Channel
//
// @func Initialize an input capture of a pulse by calling
// the appropriate device function based on the configuration passed in.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PULSE_VR_Initialize_Channel(
   IO_Configuration_T   in_configuration );

//=============================================================================
// VSEP_PULSE_Update_Overflow_Counters
//
// @func This function will update any counters that may overflow their maximum
//    value by calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PULSE_VR_Update_Overflow_Counters(
   IO_Configuration_T   in_configuration );


//=============================================================================
// VSEP_PULSE_Enable_Channel
//
// @func Enables the channel for the specific device requested.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//
//=============================================================================
void VSEP_PULSE_VR_Enable_Channel(
   IO_Configuration_T   in_configuration );

//=============================================================================
// VSEP_PULSE_Disable_Channel
//
// @func Disables the channel for the specific device requested.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//
//=============================================================================
void VSEP_PULSE_VR_Disable_Channel(
   IO_Configuration_T   in_configuration );

//=============================================================================
// VSEP_PULSE_Get_Channel_Status
//
// @func Returns the enable status of the requested channel.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc the enable state of the channel
// @flag  true | channel enabled
// @flag  false | channel disabled
//
// @end
//=============================================================================
bool VSEP_PULSE_VR_Get_Channel_Status(
   IO_Configuration_T   in_configuration);

//=============================================================================
// VSEP_TIMER_VR_Set_Value
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm uint32_t | in_time | The raw timer value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_TIMER_VR_Set_Value(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time );

//=============================================================================
// VSEP_TIMER_VR_Set_Value_Immediate
//
// @func This function will set the timer for a reset or free running timer by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm uint32_t | in_time | The raw timer value.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_TIMER_VR_Set_Value_Immediate(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time );

//=============================================================================
// VSEP_TIMER_VR_Get_Value
//
// @func This function returns the current reset or free running timer value
// by calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The current raw timer value.
//
// @end
//=============================================================================
uint32_t VSEP_TIMER_VR_Get_Value(
   IO_Configuration_T   in_configuration);

//=============================================================================
// VSEP_TIMER_VR_Get_Value_Immediate
//
// @func This function returns the current reset or free running timer value
// by calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The current raw timer value.
//
// @end
//=============================================================================
uint32_t VSEP_TIMER_VR_Get_Value_Immediate(
   IO_Configuration_T   in_configuration );

//=============================================================================
// VSEP_TIMER_VR_Get_State
//
// @func This function will return the Timer State indicating running, 
//       overflow, or underflow.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The state of the Timer
//
// @end
//=============================================================================
IO_Timer_State_T VSEP_TIMER_VR_Get_State(
   IO_Configuration_T   in_configuration);

//=============================================================================
// VSEP_TIMER_VR_Get_Base_Frequency
//
// @func This procedure will return the base frequency for a given port.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The frequency being used by this port.
//
// @end
//=============================================================================
uint32_t VSEP_TIMER_VR_Get_Base_Frequency(
   IO_Configuration_T   in_configuration);

//=============================================================================
// VSEP_TIMER_VR_Get_Size
//
// @func This procedure will return the timer size via an enumerated value.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The size in bits of the timer being used.
//
// @end
//=============================================================================
IO_Timer_Size_T VSEP_TIMER_VR_Get_Size(
   IO_Configuration_T   in_configuration );


#endif // DD_VSEP_VR_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 *
 * 04/16/09     sjl         306
 * + MT22.1: RSM_CTC_0137_Add 58x signal heavy filter during crank_Rev1_20090227
 *   - Changed VSEP_TIMER_VR_Set_Value_Immediate() to @far type
\*===========================================================================*/
