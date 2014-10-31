//=============================================================================
// include files
//=============================================================================
#include "hal_gpio.h"
#include "hal_analog.h"
#include "HLS.h"
#include "vehicle_can_cald.h"
#include "immo_cal.h"
#include "immo.h"


//=============================================================================
// LLD_di_samplecnt
//=============================================================================
uint8_t LLD_di_samplecnt[LLD_DI_MAX_CHANNEL];


//=============================================================================
//  IO_GPIO_DI_Task
//=============================================================================
void IO_GPIO_DI_Task(void)
{
	// DI
	LLD_di_table[LLD_DI_IGN_ON_OFF_SW].value =(HAL_Analog_Get_IGNVI_Value() >4094)? 0x01: 0x00;

	LLD_di_table[LLD_DI_AC_REQUEST_INPUT].value = (uint8_t)HAL_GPIO_GET_ACRequest_Status();

	LLD_di_table[LLD_DI_AC_PRESSURE_SWITCH].value = (uint8_t)HAL_GPIO_GET_MIDAC_Status();

	LLD_di_table[LLD_DI_HEAD_LAMP].value = (uint8_t)HAL_GPIO_GET_ELOAD2_Status();

	/* brake switch input, notice, this is high active but it is alway connected, so we reverse it */
	LLD_di_table[LLD_DI_BRAKE_SWITCH].value = (HAL_GPIO_GET_BRKSWDI_Status()?false:true);

	/* this channel is changed to AD channel */
	// LLD_di_table[LLD_DI_BRAKE_LAMP].value = (uint8_t)HAL_GPIO_GET_BRKLMPDI_Status();

	/* crank request input channel */
	LLD_di_table[LLD_DI_CRANK_REQUEST].value = (uint8_t)HAL_GPIO_GET_ELOAD1_Status();

	/* power steering and clutch share some input channel */
	LLD_di_table[LLD_DI_CLUTCH_TOP].value = (uint8_t)HAL_GPIO_GET_PSPS_Status();
	LLD_di_table[LLD_DI_POWER_STEERING].value = (uint8_t)HAL_GPIO_GET_PSPS_Status();
}

//=============================================================================
//IO_GPIO_DO_Task
//=============================================================================
void IO_GPIO_DO_Task(void) 
{
	HAL_GPIO_SET_MPR_Enable((bool) LLD_do_table[LLD_DO_MAIN_RELAY].value);

	if(Chk_SiemensImmo_Disabled()||(K_Immo_FuelPump_channel==CeFuelPumpPin)) {
		if (ImmoStopEngine()) {
			HAL_GPIO_SET_FPR_Enable((bool) false);
		} else {
			HAL_GPIO_SET_FPR_Enable((bool) LLD_do_table[LLD_DO_FUEL_PUMP].value);
		}
		HAL_GPIO_SET_ACClutch_Enable((bool) LLD_do_table[LLD_DO_AC_CLUTCH].value);
	} else {
		if (ImmoStopEngine()) {
			HAL_GPIO_SET_ACClutch_Enable(false);
		} else {
			HAL_GPIO_SET_ACClutch_Enable((bool) LLD_do_table[LLD_DO_FUEL_PUMP].value);
		}
		HAL_GPIO_SET_FPR_Enable((bool) LLD_do_table[LLD_DO_AC_CLUTCH].value);
	}

	HAL_GPIO_SET_FAN1_Enable((bool) LLD_do_table[LLD_DO_FAN1].value);
	HAL_GPIO_SET_FAN2_Enable((bool) LLD_do_table[LLD_DO_FAN2].value);
	// HAL_GPIO_SET_IMMOREQ_Enable((bool) LLD_do_table[LLD_DO_R_LINE].value);
	// HAL_GPIO_SET_SMR_Enable((bool) LLD_do_table[LLD_DO_START_MOTR_RLY].value);
	HAL_GPIO_SET_CRUISI_Enable((bool) LLD_do_table[LLD_DO_START_MOTR_RLY].value);
	HAL_GPIO_SET_VGIS1_Enable((bool) LLD_do_table[LLD_DO_VIS_SWITCH].value);
	
	/* for meter signal output */
	if (!K_Can_Meter_MIL_Disable) {
		HAL_GPIO_SET_MIL_Enable((bool) LLD_do_table[LLD_DO_MIL_LAMP].value);
	}
	if (!K_Can_Meter_SVS_Disable) {
		HAL_GPIO_SET_SVS_Enable((bool) LLD_do_table[LLD_DO_SVS_LAMP].value);
	}
}


//=============================================================================
//IO_GPIO_DO_Task
//=============================================================================
void IO_GPIO_DO_Task_1ms(void) 
{

}
