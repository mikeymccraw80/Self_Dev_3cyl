#ifndef MG_HAL_PWM_H
#define MG_HAL_PWM_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal_PWM.h %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:         %
//
// %version:         1 %
//
//=============================================================================


void mg_HAL_PWM_Discrete_Out_Cycling(void);
void mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty(uint8_t index);
void mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty_Immediate(uint8_t index);
void mg_HAL_PWM_Set_ETCCTLPWM_Frequency_And_Duty(uint32_t frequency, uint32_t duty);
void mg_HAL_PWM_Set_Fuel_Pump_High_Frequency_And_Duty(uint32_t freq, uint32_t duty);
void mg_HAL_PWM_Set_SWT_Timer(uint32_t time);
void mg_HAL_PWM_Channel_Initialize(void);
void mg_HAL_PWM_Validation_Cycling_Initialize(void);
uint32_t mg_HAL_PWM_Get_Frequency_In_Group_Period(uint8_t index);
uint32_t mg_HAL_PWM_Get_ETCCTLPWM_Frequency();



#endif /* end of include guard: MG_HAL_DISCRETE_OUT_H */

