#ifndef DD_PFI_INTERFACE_H
#define DD_PFI_INTERFACE_H

#include "dd_pfi.h"

//=============================================================================
// Data Type and Constant Definitions
//=============================================================================
extern uint32_t       PFI_Desired_Pulse_Width[];
extern uint32_t       PFI_Actual_Pulse_Width[];
extern uint32_t       PFI_Boundary_Time[];
extern PFI_Flags_T    PFI_Flags;
extern uint8_t           PFI_Injector_Diagnostic;

//=============================================================================
// PFI_Disable_Channel
//=============================================================================
void PFI_Disable_Channel(Crank_Cylinder_T  in_cylinder );

//=============================================================================
// PFI_Enable_Channel
//=============================================================================
void PFI_Enable_Channel(Crank_Cylinder_T  in_cylinder );

//=============================================================================
// PFI_Enable_Trim_Pulses
//=============================================================================
void PFI_Enable_Trim_Pulses( uint8_t index);

//=============================================================================
// PFI_Disable_Trim_Pulses
//=============================================================================
void PFI_Disable_Trim_Pulses( uint8_t index);

//=============================================================================
// IO_FUEL_Initialize
//=============================================================================
void PFI_Initialize(IO_PFI_Initialization_Parameters_T * const  in_initialization_parameters );

//=============================================================================
// PFI_Set_Angle
//=============================================================================
void PFI_Set_Angle( Pfi_Angle_T    in_pfi_angle_type, uint32_t       in_angle,  uint8_t        in_precision );

//=============================================================================
// PFI_Set_Fueling_Mode
//=============================================================================
void PFI_Set_Fueling_Mode(Pfi_Fuel_Delivery_Mode_T   in_mode);

//=============================================================================
// PFI_Update_Prime_Pulse_Complete
//=============================================================================
void PFI_Update_Prime_Pulse_Complete( void );

//=============================================================================
// PFI_Perform_Injection_Tasks
//=============================================================================
void PFI_Perform_Injection_Tasks( void );


//=============================================================================
// PFI_Set_Minimum_Off_Time
//=============================================================================
void PFI_Set_Minimum_Off_Time(
   uint32_t    in_min_off_time,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution );


//=============================================================================
// PFI_Set_Min_Trim_Pulse_Width
//=============================================================================
void PFI_Set_Min_Trim_Pulse_Width(
   uint32_t    in_min_pulse_width,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution );


//=============================================================================
// PFI_Set_Injector_Offset
//=============================================================================
void PFI_Set_Injector_Offset(
   uint32_t    in_offset,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution );


//=============================================================================
// PFI_Set_Pulse_Width
//=============================================================================
void PFI_Set_Pulse_Width(
   Crank_Cylinder_T  in_channel,
   uint32_t          in_pulse_width,
   uint8_t           in_time_precision,
   uint8_t           in_time_resolution );


//=============================================================================
// PFI_Set_All_Pulse_Widths
//=============================================================================
void PFI_Set_All_Pulse_Widths(
   uint32_t    in_pulse_width,
   uint8_t     in_time_precision,
   uint8_t     in_time_resolution );


//=============================================================================
// PFI_Set_Delay_Counter
//=============================================================================
void PFI_Set_Delay_Counter(
   uint8_t     inSequentialDelayCounter );


//=============================================================================
// PFI_Reset_Parameters
//=============================================================================
void PFI_Reset_Parameters( void );

//=============================================================================
// PFI_Process_Cylinder_Event
//=============================================================================
void PFI_Process_Cylinder_Event(void);


#endif // DD_PFI_INTERFACE_H
