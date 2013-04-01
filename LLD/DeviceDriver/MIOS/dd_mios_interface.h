#include "dd_mios.h"

//=============================================================================
// MIOS_Initialize_Device
//=============================================================================
void MIOS_Initialize_Device(void);

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
void MIOS_PWM_Set_Period_And_DutyCycle_US(
   MIOS_Channel_T   channel,
   uint32_t             in_period,
   uint16_t             in_duty_cycle );

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
void MIOS_PWM_Set_Frequency_And_DutyCycle(
   MIOS_Channel_T   channel,
   uint16_t             in_hz,
   uint16_t             in_duty_cycle );

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
void MIOS_PWM_Set_Duty_Cycle(
   MIOS_Channel_T   channel,
   uint16_t             in_duty_cycle );

//=============================================================================
// MIOS_PULSE_Enable_Channel
//=============================================================================
extern void MIOS_PWM_Enable_Channel(
    MIOS_Channel_T   channel, 
    bool enable );

