/*===========================================================================*\
 * Header Files
\*===========================================================================*/
#include "HLS.h"
#include "io_config_mios.h"
#include "io_config_vsep.h"
#include "dd_vsep_pwm_interface.h"


//=============================================================================
//HAL_Pulse_VSEP_CLK_Enable
//=============================================================================
 void HAL_Pulse_VSEP_CLK_Enable(bool in_enable) 
{
    MIOS_PWM_Enable_Channel(MIOS_VSEPCLK_CH,in_enable );
} 

//=============================================================================
//HAL_Pulse_ETC_Enable
//=============================================================================
 void HAL_Pulse_ETC_Enable(bool in_enable) 
{

    MIOS_PWM_Enable_Channel(MIOS_ETCCTLPWM_CH,in_enable );

} 

//=============================================================================
// HAL_Pulse_ETC_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_ETC_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   MIOS_PWM_Set_Period_And_DutyCycle_US(MIOS_ETCCTLPWM_CH, in_period, in_duty);  
   
}

//=============================================================================
//HAL_Pulse_CLTPUMPCTL_Enable
//=============================================================================
 void HAL_Pulse_CLTPUMPCTL_Enable(bool in_enable) 
{

    MIOS_PWM_Enable_Channel(MIOS_CLTPUMPCTL_CH,in_enable );

} 

//=============================================================================
// HAL_Pulse_CLTPUMPCTL_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_CLTPUMPCTL_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   MIOS_PWM_Set_Period_And_DutyCycle_US(MIOS_CLTPUMPCTL_CH, in_period, in_duty);  
   
}

//=============================================================================
//HAL_Pulse_CRUISICTL_Enable
//=============================================================================
 void HAL_Pulse_CRUISICTL_Enable(bool in_enable) 
{

    MIOS_PWM_Enable_Channel(MIOS_CRUISICTL_CH,in_enable );

} 

//=============================================================================
// HAL_Pulse_CRUISICTL_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_CRUISICTL_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   MIOS_PWM_Set_Period_And_DutyCycle_US(MIOS_CRUISICTL_CH, in_period, in_duty);  
   
}
//=============================================================================
//HAL_Pulse_VVT2CTL_Enable
//=============================================================================
 void HAL_Pulse_VVT2CTL_Enable(bool in_enable) 
{

    MIOS_PWM_Enable_Channel(MIOS_VVT2CTL_CH,in_enable );

} 

//=============================================================================
// HAL_Pulse_VVT2CTL_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_VVT2CTL_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   MIOS_PWM_Set_Period_And_DutyCycle_US(MIOS_VVT2CTL_CH, in_period, in_duty);  
   
}
//=============================================================================
//HAL_Pulse_VVT1CTL_Enable
//=============================================================================
 void HAL_Pulse_VVT1CTL_Enable(bool in_enable) 
{

    MIOS_PWM_Enable_Channel(MIOS_VVT1CTL_CH,in_enable );

} 

//=============================================================================
// HAL_Pulse_VVT1CTL_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_VVT1CTL_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   MIOS_PWM_Set_Period_And_DutyCycle_US(MIOS_VVT1CTL_CH, in_period, in_duty);  
   
}
//=============================================================================
//HAL_Pulse_FUELCONCTL_Enable
//=============================================================================
 void HAL_Pulse_FUELCONCTL_Enable(bool in_enable) 
{

    MIOS_PWM_Enable_Channel(MIOS_FUELCONCTL_CH,in_enable );

} 

//=============================================================================
// HAL_Pulse_FUELCONCTL_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_FUELCONCTL_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   MIOS_PWM_Set_Period_And_DutyCycle_US(MIOS_FUELCONCTL_CH, in_period, in_duty);  
   
}

//=============================================================================
// HAL_Pulse_CCP_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_CCP_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   VSEP_PWM_PWMSetPeriod(VSEP_PO_CCP_CH, in_period);
   VSEP_PWM_PWMSetDuty(VSEP_PO_CCP_CH, in_duty);
   
}


//=============================================================================
// HAL_Pulse_O2AHTR_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_O2AHTR_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   VSEP_PWM_PWMSetPeriod(VSEP_PO_O2AHTR_CH, in_period);
   VSEP_PWM_PWMSetDuty(VSEP_PO_O2AHTR_CH, in_duty);
   
}


//=============================================================================
// HAL_Pulse_O2BHTR_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_O2BHTR_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   VSEP_PWM_PWMSetPeriod(VSEP_PO_O2BHTR_CH, in_period);
   VSEP_PWM_PWMSetDuty(VSEP_PO_O2BHTR_CH, in_duty);
   
}

//=============================================================================
// HAL_Pulse_ALTCTL_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_ALTCTL_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   VSEP_PWM_PWMSetPeriod(VSEP_PO_ALTCTL_CH, in_period);
   VSEP_PWM_PWMSetDuty(VSEP_PO_ALTCTL_CH, in_duty);
   
}


//=============================================================================
// HAL_Pulse_CLTGAUGE_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_CLTGAUGE_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   VSEP_PWM_PWMSetPeriod(VSEP_PO_CLTGAUGE_CH, in_period);
   VSEP_PWM_PWMSetDuty(VSEP_PO_CLTGAUGE_CH, in_duty);
   
}


//=============================================================================
// HAL_Pulse_TACH_Set_Period_Duty
//=============================================================================
 void HAL_Pulse_TACH_Set_Period_Duty(uint32_t in_period, uint16_t in_duty ) 
{

   VSEP_PWM_PWMSetPeriod(VSEP_PO_TACH_CH, in_period);
   VSEP_PWM_PWMSetDuty(VSEP_PO_TACH_CH, in_duty);
   
}


