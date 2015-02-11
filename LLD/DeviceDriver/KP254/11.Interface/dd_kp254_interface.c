//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_interface.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:        %
//
// %version:         1.1.1 %
//
//=============================================================================
#include "analog.h"
#include "dd_kp254_analog.h"
#include "dd_kp254_interface.h"
#include "dd_kp254_fault.h"

#ifndef OVERLOAD_KP254_ANALOG

const Analog_T KP254_ANALOG = 
{
   {
      DEFAULT_ANALOG_Initialize_Channel,
      DEFAULT_ANALOG_Clear_Channel,
      DEFAULT_ANALOG_Enable_Channel,
      DEFAULT_ANALOG_Disable_Channel,
      DEFAULT_ANALOG_Get_Channel_Status,
      DEFAULT_ANALOG_Initialize_Queue,
      DEFAULT_ANALOG_Clear_Queue,
      DEFAULT_ANALOG_Enable_Queue,
      DEFAULT_ANALOG_Disable_Queue,
      DEFAULT_ANALOG_Get_Bit_Resolution,
      DEFAULT_ANALOG_Get_LSB_Mask,
      DEFAULT_ANALOG_Get_Data_Mask,
      DEFAULT_ANALOG_Set_Value,
      DEFAULT_ANALOG_Set_Immediate_Value,
      KP254_ANALOG_Get_Immediate_Value,
      KP254_ANALOG_Get_Immediate_Value,
      DEFAULT_ANALOG_Update_Value,
      DEFAULT_ANALOG_Get_Input_Full_Range,
      DEFAULT_ANALOG_Calibrate_Converter,
      DEFAULT_ANALOG_Trigger_Queue
   }
};

#endif    // OVERLOAD_KP254_ANALOG


#ifndef OVERLOAD_KP254_FAULT

const Fault_T KP254_FAULT =
{
   KP254_FAULT_Get_Device_Fault,
   KP254_FAULT_Clear_Device_Fault,
   KP254_FAULT_Diagnose_Device_Fault
};

#endif // OVERLOAD_KP254_FAULT

