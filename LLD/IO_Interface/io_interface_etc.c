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

void MIOS_PWM_Set_Polarity(
    MIOS_Channel_T   channel, bool egde_pol);

void MIOS_PWM_Set_Frozen(
    MIOS_Channel_T   channel, bool fren);

void MIOS_PWM_Clear_FreeRunningRegister(
    MIOS_Channel_T   channel);

enum {
	ETC_DIR_EDGE_NULL,
	ETC_DIR_EDGE_FALLING,
	ETC_DIR_EDGE_RISING
};

static int etc_pwm_edge_type = ETC_DIR_EDGE_NULL;

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
		// trigger compare b interrupt
		// HAL_GPIO_SET_ETCDIR_Enable(!(bool) etc_sig.etc_direction);
		etc_dir_old = etc_sig.etc_direction;
		// if (etc_sig.etc_direction) {
			// etc_pwm_edge_type = FALLING_EDGE;
		// } else {
			// etc_pwm_edge_type = RISING_EDGE;
		// }
		MIOS_Interrupt_Clear_Pending(MIOS_ETCCTLPWM_CH);
		MIOS_Interrupt_Enable(MIOS_ETCCTLPWM_CH);
	}


	//MIOS channel: ETC
	//500us equal 2KHZ
	//duty resoultion is 1/1000
	//etc freq is period form HLS, not frequency
	// HAL_Pulse_ETC_Enable((bool)etc_sig.etc_enable);
	if(etc_sig.etc_enable) {
		/* avoid writing freq and duty register frequently(1ms) */
		// if ((etc_duty_old != etc_sig.etc_duty) || (etc_freq_old != etc_sig.etc_freq) ||(etc_pwm_type != NULL_EDGE)) {
			if (etc_sig.etc_direction) {
				dc_temp = etc_sig.etc_duty;
				// MIOS_PWM_Set_Polarity(MIOS_ETCCTLPWM_CH, MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET);
				//seting polarity -> MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET
			} else  {
				dc_temp = 65535 - etc_sig.etc_duty;
				//seting polarity -> MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_SET_B_CLEAR
				// MIOS_PWM_Set_Polarity(MIOS_ETCCTLPWM_CH, MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_SET_B_CLEAR);
			}
			HAL_Pulse_ETC_Set_Period_Duty((uint32_t)etc_sig.etc_freq, (uint16_t)(dc_temp*1000/65535));
			etc_freq_old = etc_sig.etc_freq; //record this new data
			etc_duty_old = etc_sig.etc_duty; //record this new data
		// }
	} else {
		// HAL_Pulse_ETC_Set_Period_Duty((uint32_t)etc_sig.etc_freq, 65535);
	}
}


void IO_ETC_PWM_INT_Handler(void)
{
	MIOS_PWM_Set_Frozen(MIOS_ETCCTLPWM_CH, true);
	MIOS_PWM_Clear_FreeRunningRegister(MIOS_ETCCTLPWM_CH);
	if (etc_sig.etc_direction) {
		MIOS_PWM_Set_Polarity(MIOS_ETCCTLPWM_CH, MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET);
	} else {
		MIOS_PWM_Set_Polarity(MIOS_ETCCTLPWM_CH, MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_SET_B_CLEAR);
	}
	MIOS_PWM_Set_Frozen(MIOS_ETCCTLPWM_CH, false);
	// etc_pwm_edge_type = ETC_DIR_EDGE_NULL;
	HAL_GPIO_SET_ETCDIR_Enable(!(bool) etc_sig.etc_direction);
	MIOS_Interrupt_Disable(MIOS_ETCCTLPWM_CH);
	MIOS_Interrupt_Clear_Pending(MIOS_ETCCTLPWM_CH);
}

