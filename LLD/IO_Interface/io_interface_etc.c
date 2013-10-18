//=============================================================================
// include files
//=============================================================================
#include "HLS.h"
#include "hal_pulse.h"
#include "hal_gpio.h"
#include "io_config_mios.h"

void MIOS_Interrupt_Enable(
    MIOS_Channel_T   channel);

void MIOS_Interrupt_Disable(
    MIOS_Channel_T   channel);

void MIOS_Interrupt_Clear_Flag(
    MIOS_Channel_T   channel);

void MIOS_Interrupt_Clear_Pending(
   MIOS_Channel_T channel );


//=============================================================================
// IO_ETC_Update_Function_1msIO_ETC_Update_Function_1ms
//=============================================================================
void IO_ETC_Update_1msTimeBase(void) 
{
	static uint16_t etc_freq_old, etc_duty_old;
	static uint8_t etc_dir_old;
	uint32_t dc_temp;

	/* detect the disable and enable control of etc signal */
	HAL_GPIO_SET_ETCDIS_Enable(!(bool)etc_sig.etc_enable);

	/*detect etc direction change, 1 equal ETC open */
	if (etc_dir_old != etc_sig.etc_direction) {
		// trigger compare B register interrupt
		etc_dir_old = etc_sig.etc_direction;
		MIOS_Interrupt_Clear_Pending(MIOS_ETCCTLPWM_CH);
		MIOS_Interrupt_Enable(MIOS_ETCCTLPWM_CH);
	}


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
	}
}

void IO_ETC_PWM_INT_Handler(void)
{
	HAL_GPIO_SET_ETCDIR_Enable(!(bool) etc_sig.etc_direction);
	MIOS_Interrupt_Disable(MIOS_ETCCTLPWM_CH);
	MIOS_Interrupt_Clear_Pending(MIOS_ETCCTLPWM_CH);
}
