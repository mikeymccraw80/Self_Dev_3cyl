/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"
#include "hal_diag.h"
#include "io_interface_diag.h"
#include "io_config_vsep.h"

/*===========================================================================*\
 * Local variable define
\*===========================================================================*/

/*===========================================================================*\
 * Local function declarition
\*===========================================================================*/

/* ========================================================================= *\
 * FUNCTION: Diag_Digital_Output_Faults
 * =========================================================================
 * RETURN VALUE:
 *
 *
 * PARAMETERS:
 *
 * EXTERNAL REFERENCES:
 *
 *
 * -------------------------------------------------------------------------
 * ABSTRACT:
 * -------------------------------------------------------------------------
 * Decode and display diagnostic code.( vsep )
\* ========================================================================= */
static void Diag_Digital_Output_Faults(void)
{
	/* Injector A */
	if (InjectorAShortHi()) {
		Diag_INJ_A_Status = Diag_INJ_A_Status | OUT_SHORT_HIGH;
	} else {
		Diag_INJ_A_Status = Diag_INJ_A_Status & ~OUT_SHORT_HIGH;
	}

	if (InjectorAShortLo()) {
		Diag_INJ_A_Status = Diag_INJ_A_Status | OUT_SHORT_LOW;
	} else {
		Diag_INJ_A_Status = Diag_INJ_A_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_INJ_A_Status & OUT_FAIL_MASK ) {
		Diag_INJ_A_Status = Diag_INJ_A_Status | OUT_FAIL;
	} else {
		Diag_INJ_A_Status = OUT_FAULT_CLEAR;
	}

	/* Injector B */
	if (InjectorBShortHi()) {
		Diag_INJ_B_Status = Diag_INJ_B_Status | OUT_SHORT_HIGH;
	} else {
		Diag_INJ_B_Status = Diag_INJ_B_Status & ~OUT_SHORT_HIGH;
	}

	if (InjectorBShortLo()) {
		Diag_INJ_B_Status = Diag_INJ_B_Status | OUT_SHORT_LOW;
	} else {
		Diag_INJ_B_Status = Diag_INJ_B_Status & ~OUT_SHORT_LOW;
	} 

	if ( Diag_INJ_B_Status & OUT_FAIL_MASK ) {
		Diag_INJ_B_Status = Diag_INJ_B_Status | OUT_FAIL;
	} else {
		Diag_INJ_B_Status = OUT_FAULT_CLEAR;
	}

	/* Injector C */
	if (InjectorCShortHi()) {
		Diag_INJ_C_Status = Diag_INJ_C_Status | OUT_SHORT_HIGH;
	} else {
		Diag_INJ_C_Status = Diag_INJ_C_Status & ~OUT_SHORT_HIGH;
	}

	if (InjectorCShortLo()) {
		Diag_INJ_C_Status = Diag_INJ_C_Status | OUT_SHORT_LOW;
	} else {
		Diag_INJ_C_Status = Diag_INJ_C_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_INJ_C_Status & OUT_FAIL_MASK ) {
		Diag_INJ_C_Status = Diag_INJ_C_Status | OUT_FAIL;
	} else {
		Diag_INJ_C_Status = OUT_FAULT_CLEAR;
	}

	/* Injector D */
	if (InjectorDShortHi()) {
		Diag_INJ_D_Status = Diag_INJ_D_Status | OUT_SHORT_HIGH;
	} else {
		Diag_INJ_D_Status = Diag_INJ_D_Status & ~OUT_SHORT_HIGH;
	}

	if (InjectorDShortLo()) {
		Diag_INJ_D_Status = Diag_INJ_D_Status | OUT_SHORT_LOW;
	} else {
		Diag_INJ_D_Status = Diag_INJ_D_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_INJ_D_Status & OUT_FAIL_MASK ) {
		Diag_INJ_D_Status = Diag_INJ_D_Status | OUT_FAIL;
	} else {
		Diag_INJ_D_Status = OUT_FAULT_CLEAR;
	}


	/* MIL */
	if (!K_Can_Meter_MIL_Disable) {
		if (GetVIOS_MILD_FaultShortHi()) {
			Diag_MIL_Status = Diag_MIL_Status | OUT_SHORT_HIGH;
		} else {
			Diag_MIL_Status = Diag_MIL_Status & ~OUT_SHORT_HIGH;
		}

		if (GetVIOS_MILD_FaultShortLo()) {
			Diag_MIL_Status = Diag_MIL_Status | OUT_SHORT_LOW;
		} else {
			Diag_MIL_Status = Diag_MIL_Status & ~OUT_SHORT_LOW;
		}

		if ( Diag_MIL_Status & OUT_FAIL_MASK ) {
			Diag_MIL_Status = Diag_MIL_Status | OUT_FAIL;
		} else {
			Diag_MIL_Status = OUT_FAULT_CLEAR;
		}
	}

	/* TACHO Meter */ /* Not used for EOBD */
	if (!K_Can_Meter_TACH_Disable) {
		if (DD_GetDiscreteDiagStatus(PULSE_OUT_TACHOMETER,OUTPUT_SHORT_CKT_FAULT)) {
			Diag_TACHO_Status = Diag_TACHO_Status | OUT_SHORT_HIGH;
		} else {
			Diag_TACHO_Status = Diag_TACHO_Status & ~OUT_SHORT_HIGH;
		}

		if (DD_GetDiscreteDiagStatus(PULSE_OUT_TACHOMETER,OUTPUT_OPEN_CKT_FAULT)) {
			Diag_TACHO_Status = Diag_TACHO_Status | OUT_SHORT_LOW;
		} else {
			Diag_TACHO_Status = Diag_TACHO_Status & ~OUT_SHORT_LOW;
		}

		if ( Diag_TACHO_Status & OUT_FAIL_MASK ) {
			Diag_TACHO_Status = Diag_TACHO_Status | OUT_FAIL;
		} else {
			Diag_TACHO_Status = OUT_FAULT_CLEAR;
		}
	}

   /* CCP/Purge PWM5 */
	if (GetHWIO_PurgeSolOutputFaultShortHi()) {
		Diag_Purge_Status = Diag_Purge_Status | OUT_SHORT_HIGH;
	} else {
		Diag_Purge_Status = Diag_Purge_Status & ~OUT_SHORT_HIGH;
	}

	if (GetHWIO_PurgeSolOutputFaultShortLo()) {
		Diag_Purge_Status = Diag_Purge_Status | OUT_SHORT_LOW;
	} else {
		Diag_Purge_Status = Diag_Purge_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_Purge_Status & OUT_FAIL_MASK ) {
		Diag_Purge_Status = Diag_Purge_Status | OUT_FAIL;
	} else {
		Diag_Purge_Status = OUT_FAULT_CLEAR;
	}

	/* FRONT O2 HEATER PWM0 */
	if (GetVIOS_O2_11_Htr_PSVIFaultShortHi()) {
		Diag_O2AHeat_Status = Diag_O2AHeat_Status | OUT_SHORT_HIGH;
	} else {
		Diag_O2AHeat_Status = Diag_O2AHeat_Status & ~OUT_SHORT_HIGH;
	}

	if (GetVIOS_O2_11_Htr_PSVIFaultShortLow()) {
		Diag_O2AHeat_Status = Diag_O2AHeat_Status | OUT_SHORT_LOW;
	} else {
		Diag_O2AHeat_Status = Diag_O2AHeat_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_O2AHeat_Status & OUT_FAIL_MASK ) {
		Diag_O2AHeat_Status = Diag_O2AHeat_Status | OUT_FAIL;
	} else {
		Diag_O2AHeat_Status = OUT_FAULT_CLEAR;
	}

	/* Back O2 HEATER PWM1 */
	if (GetVIOS_O2_12_Htr_PSVIFaultShortHi()) {
		Diag_O2BHeat_Status = Diag_O2BHeat_Status | OUT_SHORT_HIGH;
	} else {
		Diag_O2BHeat_Status = Diag_O2BHeat_Status & ~OUT_SHORT_HIGH;
	}

	if (GetVIOS_O2_12_Htr_PSVIFaultShortLow()) {
		Diag_O2BHeat_Status = Diag_O2BHeat_Status | OUT_SHORT_LOW;
	} else {
		Diag_O2BHeat_Status = Diag_O2BHeat_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_O2BHeat_Status & OUT_FAIL_MASK ) {
		Diag_O2BHeat_Status = Diag_O2BHeat_Status | OUT_FAIL;
	} else {
		Diag_O2BHeat_Status = OUT_FAULT_CLEAR;
	}

	/* coolant gauge or thermal control */
	if (DD_GetDiscreteDiagStatus(PULSE_OUT_COOL_TEMP_PWM,OUTPUT_SHORT_CKT_FAULT)) {
		Diag_ECT_PWM_Status = Diag_ECT_PWM_Status | OUT_SHORT_HIGH;
	} else {
		Diag_ECT_PWM_Status = Diag_ECT_PWM_Status & ~OUT_SHORT_HIGH;
	}

	if (DD_GetDiscreteDiagStatus(PULSE_OUT_COOL_TEMP_PWM,OUTPUT_OPEN_CKT_FAULT)) {
		Diag_ECT_PWM_Status = Diag_ECT_PWM_Status | OUT_SHORT_LOW;
	} else {
		Diag_ECT_PWM_Status = Diag_ECT_PWM_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_ECT_PWM_Status & OUT_FAIL_MASK ) {
		Diag_ECT_PWM_Status = Diag_ECT_PWM_Status | OUT_FAIL;
	} else {
		Diag_ECT_PWM_Status = OUT_FAULT_CLEAR;
	}


	/* FAN1 */
	if (GetVIOS_FANA_FaultShortHi()) {
		Diag_Fan1_Status = Diag_Fan1_Status | OUT_SHORT_HIGH;
	} else {
		Diag_Fan1_Status = Diag_Fan1_Status & ~OUT_SHORT_HIGH;
	}

	if (GetVIOS_FANA_FaultShortLo()) {
		Diag_Fan1_Status = Diag_Fan1_Status | OUT_SHORT_LOW;
	} else {
		Diag_Fan1_Status = Diag_Fan1_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_Fan1_Status & OUT_FAIL_MASK ) {
		Diag_Fan1_Status = Diag_Fan1_Status | OUT_FAIL;
	} else {
		Diag_Fan1_Status = OUT_FAULT_CLEAR;
	}

	/* FAN2 */
	if (GetVIOS_FANB_FaultShortHi()) {
		Diag_Fan2_Status = Diag_Fan2_Status | OUT_SHORT_HIGH;
	} else {
		Diag_Fan2_Status = Diag_Fan2_Status & ~OUT_SHORT_HIGH;
	}

	if (GetVIOS_FANB_FaultShortLo()) {
		Diag_Fan2_Status = Diag_Fan2_Status | OUT_SHORT_LOW;
	} else {
		Diag_Fan2_Status = Diag_Fan2_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_Fan2_Status & OUT_FAIL_MASK ) {
		Diag_Fan2_Status = Diag_Fan2_Status | OUT_FAIL;
	} else {
		Diag_Fan2_Status = OUT_FAULT_CLEAR;
	}

	/* Fuel Consumption PWM6*/
	if (!K_Can_Meter_Fuel_Consum_Disable) {
		if (DD_GetDiscreteDiagStatus(DISCRETE_OUT_TRIP_COMPUTER,OUTPUT_SHORT_CKT_FAULT)) {
			Diag_FulCsum_Status = Diag_FulCsum_Status | OUT_SHORT_HIGH;
		} else {
			Diag_FulCsum_Status = Diag_FulCsum_Status & ~OUT_SHORT_HIGH;
		}

		if (DD_GetDiscreteDiagStatus(DISCRETE_OUT_TRIP_COMPUTER,OUTPUT_OPEN_CKT_FAULT)) {
			Diag_FulCsum_Status = Diag_FulCsum_Status | OUT_SHORT_LOW;
		} else {
			Diag_FulCsum_Status = Diag_FulCsum_Status & ~OUT_SHORT_LOW;
		}

		if ( Diag_FulCsum_Status & OUT_FAIL_MASK ) {
			Diag_FulCsum_Status = Diag_FulCsum_Status | OUT_FAIL;
		} else {
			Diag_FulCsum_Status = OUT_FAULT_CLEAR;
		}
	}

	/* MAINRLY */
	if (GetVIOS_MPRD_FaultShortHi()) {
		Diag_MainRly_Status = Diag_MainRly_Status | OUT_SHORT_HIGH;
	} else {
		Diag_MainRly_Status = Diag_MainRly_Status & ~OUT_SHORT_HIGH;
	}

	if (GetVIOS_MPRD_FaultShortLo()) {
		Diag_MainRly_Status = Diag_MainRly_Status | OUT_SHORT_LOW;
	} else {
		Diag_MainRly_Status = Diag_MainRly_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_MainRly_Status & OUT_FAIL_MASK ) {
		Diag_MainRly_Status = Diag_MainRly_Status | OUT_FAIL;
	} else {
		Diag_MainRly_Status = OUT_FAULT_CLEAR;
	}

	/* FUEL_PUMP */
	if (GetVIOS_FPRD_FaultShortHi()) {
		Diag_FulPump_Status = Diag_FulPump_Status | OUT_SHORT_HIGH;
	} else {
		Diag_FulPump_Status = Diag_FulPump_Status & ~OUT_SHORT_HIGH;
	}

	if (GetVIOS_FPRD_FaultShortLo()) {
		Diag_FulPump_Status = Diag_FulPump_Status | OUT_SHORT_LOW;
	} else {
		Diag_FulPump_Status = Diag_FulPump_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_FulPump_Status & OUT_FAIL_MASK ) {
		Diag_FulPump_Status = Diag_FulPump_Status | OUT_FAIL;
	} else {
		Diag_FulPump_Status = OUT_FAULT_CLEAR;
	}

	/* AC_CLUTCH */
	if (GetVIOS_ACCD_FaultShortHi()) {
		Diag_ACCluch_Status = Diag_ACCluch_Status | OUT_SHORT_HIGH;
	} else { 
		Diag_ACCluch_Status = Diag_ACCluch_Status & ~OUT_SHORT_HIGH;
	}

	if (GetVIOS_ACCD_FaultShortLo()) {
		Diag_ACCluch_Status = Diag_ACCluch_Status | OUT_SHORT_LOW;
	} else {
		Diag_ACCluch_Status = Diag_ACCluch_Status & ~OUT_SHORT_LOW;
	}

	if ( Diag_ACCluch_Status & OUT_FAIL_MASK ) {
		Diag_ACCluch_Status = Diag_ACCluch_Status | OUT_FAIL;
	} else {
		Diag_ACCluch_Status = OUT_FAULT_CLEAR;
	}
}
////////////////////////////////////////////////////////////////////////////////////////	 
////////////////////////////////////////////////////////////////////////////////////////	 
/* Diag ETC Driver Faults*/
////////////////////////////////////////////////////////////////////////////////////////	 
////////////////////////////////////////////////////////////////////////////////////////	 

static void Diag_ETC_Driver_Faults(void)
{
	etc_sig.status3.ETC_Fault = L9958_FAULT_Diagnose_Update();
}

////////////////////////////////////////////////////////////////////////////////////////	 
////////////////////////////////////////////////////////////////////////////////////////	 
/* Diag Analog Faults*/
////////////////////////////////////////////////////////////////////////////////////////	 
////////////////////////////////////////////////////////////////////////////////////////	 

static void Diag_Analog_Faults(void)
{

}

/* update this function in 10ms Task */
void Update_DiagStatus_10ms(void)
{
	Diag_Digital_Output_Faults();
	Diag_Analog_Faults();
	Diag_ETC_Driver_Faults();
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
\*===========================================================================*/
