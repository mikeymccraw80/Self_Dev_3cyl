
#include "dd_mios.h"


//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
extern void MIOS_PWM_Set_Period_And_DutyCycle_US(
   MIOS_Channel_T   channel,
   uint32_t             in_period,
   uint32_t             in_duty_cycle );

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
extern void MIOS_PWM_Set_Frequency_And_DutyCycle(
   MIOS_Channel_T   channel,
   uint16_t             in_hz,
   uint16_t             in_duty_cycle );

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
extern void MIOS_PWM_Set_Duty_Cycle(
   MIOS_Channel_T   channel,
   uint32_t             in_duty_cycle );

//=============================================================================
// MIOS_PWM_Set_Period_And_Duty_Cycle
//=============================================================================
extern uint32_t  MIOS_PWM_Get_Duty_Cycle(
   MIOS_Channel_T   channel );

//=============================================================================
// MIOS_PULSE_Enable_Channel
//=============================================================================
extern void MIOS_PWM_Enable_Channel(
    MIOS_Channel_T   channel, 
    bool enable );

