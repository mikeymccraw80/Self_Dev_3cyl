#ifndef DD_MCD5402_H
#define DD_MCD5402_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec    :   dd_mcd5402.h %
//
// created_by       :   dz48hg
//
// date_created     :   Mon, Sep 10, 2007 7:57:31 PM
//
// %derived_by       :   mz01yw %
//
// %date_modified    :   Mon, Mar 24, 2008 09:26:30 AM %
//
// %version          :   tci_pt2#4 %
//
//=============================================================================
//
//===========================================================================
// REUSE:                                                                    
// DO NOT MODIFY THIS FILE.  Coordinate any desired changes with the         
// Complex I/O group.                                                        
//                                                                           
//===========================================================================

#include "dd_tpu.h"
#include "mcd5402.h"
#include "io_type.h"

#define MCD5402_MAX_MEASUREABLE_PERIOD 0xFFFFFF
#define MCD5402_MAX_EDGE_COUNT         0xFF

//===========================================================================
// Function Prototypes                                                       
//===========================================================================

//=============================================================================
// MCD5402_Initialize_Channel
//
// @func Initilaizes the MCD5402(PWM Input) primitive
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void MCD5402_Initialize_Channel(
   TPU_Index_T index,
   TPU_T       *p_tpu,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5403_Get_Period
//
// @func This function will return the period of the PWM input.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The period in counts.
//
// @end
//=============================================================================
uint32_t MCD5402_Get_Period(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5402_Get_Duty_Cycle
//
// @func This function will return the duty cycle of the PWM input.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The duty cycle in counts.
//
// @end
//=============================================================================
uint32_t MCD5402_Get_Duty_Cycle(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5402_Get_Coherent_Period_And_Duty_Cycle
//
// @func This function will return the period and duty cycle of the PWM input.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm PWM_Data_T* | pwm_data | pointer to a structure containing period and
//          duty cycle.
//
// @rdesc Pointer to a structure containing the PWM period and
//          duty cycle
//
// @end
//=============================================================================
PWM_Data_T* MCD5402_Get_Coherent_Period_And_Duty_Cycle(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   PWM_Data_T*          pwm_data );

//=============================================================================
// MCD5402_Get_Coherent_Accum_Period_Duty_And_Count
//
// @func This function will return the duty cycle and edge of the PWM input.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm PWM_Data_T* | pulse_data | pointer to a structure containing edge count 
//          and duty cycle.
//
// @rdesc Pointer to a structure containing the accumulated
//          period duty cycle and edge count of the PWM.
//
// @end
//=============================================================================
PWM_Data_T* MCD5402_Get_Coherent_Accum_Period_Duty_And_Count(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   PWM_Data_T*       pulse_data );

//=============================================================================
// MCD5402_Get_Coherent_Edge_Time_And_Count
//
// @func This function will return the edge time and edge count of the PWM input.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm IO_Edge_Data_T* | edge_data | pointer to a structure containing the edge time
//          and edge count.
//
// @rdesc Pointer to a structure containing the edge time
//          and edge count.
//
// @end
//=============================================================================
IO_Edge_Data_T* MCD5402_Get_Coherent_Edge_Time_And_Count(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   IO_Edge_Data_T*      edge_data );

//=============================================================================
// MCD5402_Get_Period_TimeOut
//
// @func This function will return period timeout status.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc True means period timeout occured due to no input signal
//
// @end
//=============================================================================
bool MCD5402_Get_Period_TimeOut(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5402_Shutdown
//
// @func This function shuts down the MCD5402  PWM Input Primitive
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void MCD5402_Shutdown(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5402_Get_Edge
//
// @func returns edge information for the input capture
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc Edge information none, rising, falling or both
//
// @end
//=============================================================================
IO_Edge_T MCD5402_Get_Edge(
   TPU_Index_T index,
   TPU_T       *p_tpu,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5402_Set_Edge
//
// @func Provides edge change capability for the input capture
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm IO_Edge_T | in_edge | none, rising, falling, or both
//
// @rdesc none.
//
// @end
//=============================================================================
void MCD5402_Set_Edge(
   TPU_Index_T index,
   TPU_T       *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   IO_Edge_T in_edge );

//=============================================================================
// MCD5402_Get_Max_Measureable_Period
//
// @func This function will return the maximum period that can be measured
//          on the desired input before an overflow occurres.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The maximum period that can be measured in raw counts.
//
// @end
//=============================================================================
uint32_t MCD5402_Get_Max_Measureable_Period(
   IO_Configuration_T   in_configuration );

//=============================================================================
// MCD5402_Get_Max_Edge_Count
//
// @func This function will return the maximum edge count.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The maximum edge count.
//
// @end
//=============================================================================
uint32_t MCD5402_Get_Max_Edge_Count(
   IO_Configuration_T   in_configuration );
#endif // DD_MCD5402_H
