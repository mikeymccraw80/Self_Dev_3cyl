//=============================================================================
// include files
//=============================================================================
#include "hal_pulse.h"
#include "intr_ems.h"
#include "HLS.h"


//=============================================================================
// HAL_Pulse_Init_Task
//=============================================================================
void  IO_Pulse_Update_Function(void) 
{
	//MIOS channel: VVT1
	//period in us
	//duty resoultion is 1/1000
	if(LLD_pwm_out_table[LLD_PWM_VVT1].B_enable)
	{
		HAL_Pulse_VVT1CTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_VVT1].period*1000,
										  (uint16_t)LLD_pwm_out_table[LLD_PWM_VVT1].duty*1000/255);
	}
	else
	{
		HAL_Pulse_VVT1CTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_VVT1].period*1000,
										   0);
	}

	//MIOS channel: VVT2
	//period in us
	//duty resoultion is 1/1000
	if(LLD_pwm_out_table[LLD_PWM_VVT2].B_enable)
	{
		HAL_Pulse_VVT2CTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_VVT2].period*1000,
										  (uint16_t)LLD_pwm_out_table[LLD_PWM_VVT2].duty*1000/255);
	}
	else
	{
		HAL_Pulse_VVT2CTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_VVT2].period*1000,
										   0);
	}

	//MIOS channel: fuel consumption
	//period in us
	//duty resoultion is 1/1000
	if(LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].B_enable)
	{
		HAL_Pulse_FUELCONCTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].period*1000,
										  (uint16_t)LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].duty*1000/255);
	}
	else
	{
		HAL_Pulse_FUELCONCTL_Set_Period_Duty((uint32_t)LLD_pwm_out_table[LLD_PWM_FUEL_CONSUMPTION].period*1000,
										   0);
	}

	//VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
	//VSEP channel :CCP
	if(LLD_pwm_out_table[LLD_PWM_PURGE].B_enable)
	{
		HAL_Pulse_CCP_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_PURGE].period*64, 
									   (uint16_t)LLD_pwm_out_table[LLD_PWM_PURGE].duty*128);
	}
	else
	{
		HAL_Pulse_CCP_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_PURGE].period*64,
									   (uint16_t)0);
	}

	//Chery period resolution is 1ms
	//VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
	//VSEP channel :O2 HTRA
	if(LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].B_enable)
	{
		HAL_Pulse_O2AHTR_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].period*64, 
										  (uint16_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].duty*128);
	}
	else
	{
		HAL_Pulse_O2AHTR_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_1].period*64, 
										   0);
	}

	//Chery period resolution is 1ms
	//VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
	//VSEP channel :O2 HTRB
	if(LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].B_enable)
	{
		HAL_Pulse_O2BHTR_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].period*64, 
										  (uint16_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].duty*128);
	}
	else
	{
		HAL_Pulse_O2BHTR_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_O2_HEATER_2].period*64, 
										  (uint16_t)0);
	}

	//Chery period resolution is 1ms
	//VSEP channel: period resoultion is 1/64ms; duty resoultion is 1/32768
	//VSEP channel :CLT Gauge
	if(LLD_pwm_out_table[LLD_PWM_ECT].B_enable)
	{
		HAL_Pulse_CLTGAUGE_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_ECT].period*64, 
											(uint16_t)LLD_pwm_out_table[LLD_PWM_ECT].duty*128);
	}
	else
	{
		HAL_Pulse_CLTGAUGE_Set_Period_Duty( (uint32_t)LLD_pwm_out_table[LLD_PWM_ECT].period*64, 
											(uint16_t)0);
	}
}
//=============================================================================
// IO_Pulse_VSEP_CLK_Enable
//=============================================================================
void  IO_Pulse_VSEP_CLK_Enable(void)
{
	HAL_Pulse_VSEP_CLK_Enable(true);
}

//=============================================================================
// IO_Pulse_VSS_Update_500ms
//=============================================================================
static uint32_t  Pulse_VSS_Count_Previous;

void IO_Pulse_VSS_Update_500ms(void)
{
	uint32_t  Pulse_VSS_Count;

	Pulse_VSS_Count = HAL_Pulse_Get_VSS_Count();

	if ((GetVIOS_EngSt() == CeENG_KEYON)
		|| (GetVIOS_EngSt() == CeENG_POWEROFFDELAY)
		|| (Pulse_VSS_Count == Pulse_VSS_Count_Previous))
	{
		veh_spd_sig.period = 0xFFFFFFFF;
	}
	else
	{
		//TPU time is 4M and VSS period resoultion is 0.01ms
		veh_spd_sig.period = HAL_Pulse_Get_VSS_Period() / 40;
	}

	Pulse_VSS_Count_Previous = Pulse_VSS_Count;
}

//=============================================================================
// IO_Pulse_Update_Function_1ms
//=============================================================================
void  IO_Pulse_Update_Function_1ms(void) 
{
#if 0
 	static uint16_t etc_freq_old;
	static uint16_t etc_duty_old;
	uint32_t dc_temp;

	//MIOS channel: ETC
	//500us equal 2KHZ
	//duty resoultion is 1/1000
	//etc freq is period form HLS, not frequency
	// HAL_Pulse_ETC_Enable((bool)etc_sig.etc_enable);
	if(etc_sig.etc_enable) {
		/* avoid writing freq and duty register frequently(1ms) */
		if ((etc_duty_old != etc_sig.etc_duty) || (etc_freq_old != etc_sig.etc_freq)) {
			dc_temp = 65535 - etc_sig.etc_duty;
			HAL_Pulse_ETC_Set_Period_Duty((uint32_t)etc_sig.etc_freq, (uint16_t)(dc_temp*1000/65535));
			etc_freq_old = etc_sig.etc_freq; //record this new data
			etc_duty_old = etc_sig.etc_duty; //record this new data
		}
	} else {
		// HAL_Pulse_ETC_Set_Period_Duty((uint32_t)etc_sig.etc_freq, 65535);
	}
#endif
}