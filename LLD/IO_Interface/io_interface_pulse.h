#ifndef IO_INTERFACE_PULSE_H
#define IO_INTERFACE_PULSE_H

//=============================================================================
// include files
//=============================================================================
#include "reuse.h"

//=============================================================================
// HAL_Pulse_Init_Task
//=============================================================================
 void  IO_Pulse_Update_Function(void) ;
//=============================================================================
// IO_Pulse_VSEP_CLK_Enable
//=============================================================================
void  IO_Pulse_VSEP_CLK_Enable(void);
//=============================================================================
// IO_Pulse_VSS_Update_500ms
//=============================================================================
void  IO_Pulse_VSS_Update_500ms(void);
//=============================================================================
// IO_Pulse_VSS_Update_500ms
//=============================================================================
void  IO_Pulse_VSS_Update_10ms(void);
//=============================================================================
// IO_Pulse_FuelConsumption_Update_2ms
//=============================================================================
void IO_Pulse_FuelConsumption_Update_2ms(void);
//=============================================================================
// IO_Pulse_Update_Function_1ms
//=============================================================================
 void  IO_Pulse_Update_Function_1ms(void) ;
 

#endif
