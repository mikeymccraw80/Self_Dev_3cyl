#ifndef DD_VSEP_DEPS_H
#define DD_VSEP_DEPS_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_deps.h~1:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:37 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Fri Feb 16 12:02:37 2007 %
//
// %version:         1 %
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
//#include "types.h"

typedef enum 
{
                                                          //[ 6: 0] Reserved by VSEP.h
   VSEP_DEPS_CONFIGURATION_POSITION_INITIAL_DELAY    = 7  //[17: 7] DEPSDLY
}VSEP_VR_CONFIGURATION_POSITION_T;

typedef enum 
{
                                                          //[ 6: 0] Reserved by VSEP.h
   VSEP_DEPS_CONFIGURATION_WIDTH_INITIAL_DELAY       =11  //[17: 7] DEPSDLY
}VSEP_VR_CONFIGURATION_WIDTH_T;

//=============================================================================
// VSEP_DEPS_Set_Initial_Delay
//
// @func Set desired initial DEPS delay. This is a 11-bit value. The lower 5 bits 
//    are fixed to 01111 by the VSEP. The VSEP device driver will mask the lower 
//    5 bits to %01111.
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm uint16_t | y | A <t uint16_t> raw value for the DEPSDLY.
//
// @rdesc <t IO_Configuration_T> containing the element <t uint32_t>
//
// @end
//=============================================================================
#define VSEP_DEPS_Set_Initial_Delay(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_DEPS_CONFIGURATION_POSITION_INITIAL_DELAY, VSEP_DEPS_CONFIGURATION_WIDTH_INITIAL_DELAY ) )

//=============================================================================
// VSEP_DEPS_Get_Initial_Delay
//
// @func Get desired initial VR delay. This is a 12-bit value. The lower 5 bits 
//    are fixed to 01111 by the VSEP. The VSEP device driver will mask the lower 
//    5 bits to %01111.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t uint32_t> raw value for VRDLY decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_DEPS_Get_Initial_Delay(x) \
   (uint32_t)( Extract_Bits( x, VSEP_DEPS_CONFIGURATION_POSITION_INITIAL_DELAY, VSEP_DEPS_CONFIGURATION_WIDTH_INITIAL_DELAY ) )

typedef enum
{
   VSEP_DEPS_TXD_MESSAGE_CTRL,
   VSEP_DEPS_TXD_MESSAGE_DELAY,
   VSEP_DEPS_TXD_MESSAGE_MAX
}VSEP_DEPS_Txd_Message_T;

typedef enum
{
   VSEP_DEPS_RXD_MESSAGE_FLT,
   VSEP_DEPS_RXD_MESSAGE_NU_0,
   VSEP_DEPS_RXD_MESSAGE_MAX
}VSEP_DEPS_Rxd_Message_T;

extern uint16_t VSEP_DEPS_Txd[NUMBER_OF_VSEP][VSEP_DEPS_TXD_MESSAGE_MAX];
extern uint16_t VSEP_DEPS_Rxd[NUMBER_OF_VSEP][VSEP_DEPS_RXD_MESSAGE_MAX];

extern const uint32_t VSEP_TIMER_DEPS_Base_Frequency;
extern const uint16_t VSEP_DEPS_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_DEPS_TXD_MESSAGE_MAX];

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
void VSEP_PULSE_DEPS_Initialize_Device(
   IO_Configuration_T   in_configuration );

//=============================================================================
// VSEP_PULSE_Clear_Device
//
// @func Clear a device's global registers to its reset state.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_PULSE_DEPS_Clear_Device(
   IO_Configuration_T   in_configuration );

//=============================================================================
//  Used for mutilple types
//=============================================================================

//=============================================================================
// VSEP_PULSE_DEPS_Initialize_Channel
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
void VSEP_PULSE_DEPS_Initialize_Channel(
   IO_Configuration_T   in_configuration );

//=============================================================================
// VSEP_TIMER_DEPS_Set_Value
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
void VSEP_TIMER_DEPS_Set_Value(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time );

//=============================================================================
// VSEP_TIMER_DEPS_Set_Value_Immediate
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
void VSEP_TIMER_DEPS_Set_Value_Immediate(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time );

//=============================================================================
// VSEP_TIMER_DEPS_Get_Value
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
uint32_t VSEP_TIMER_DEPS_Get_Value(
   IO_Configuration_T   in_configuration);

//=============================================================================
// VSEP_TIMER_DEPS_Get_State
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
IO_Timer_State_T VSEP_TIMER_DEPS_Get_State(
   IO_Configuration_T   in_configuration);

//=============================================================================
// VSEP_TIMER_DEPS_Get_Base_Frequency
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
uint32_t VSEP_TIMER_DEPS_Get_Base_Frequency(
   IO_Configuration_T   in_configuration);

//=============================================================================
// VSEP_TIMER_DEPS_Get_Size
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
IO_Timer_Size_T VSEP_TIMER_DEPS_Get_Size(
   IO_Configuration_T   in_configuration );

#endif // DD_VSEP_DEPS_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
\*===========================================================================*/
