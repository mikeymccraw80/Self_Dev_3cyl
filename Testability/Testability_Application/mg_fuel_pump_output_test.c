//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_fuel_pump_output_test.c %
//
// created_by:       tzwfxv %
//
// date_created:	Fri Jul 13 14:03:10 2012 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:             %
//
// %version:         3 %
//
//=============================================================================
#if 0
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal_discrete.h"
#include "mg_hal_PWM.h"

/*****************************************************************************
 * Function Prototype: void mg_fuel_pump_output_test(void)
 *
 * Description: This test output fuel pump as control.
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_fuel_pump_output_test(void)
{
    uint32_t freq;
    uint32_t duty;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    duty = MG_MAILBOX_IN(parameter[0]);
    freq =  (MG_MAILBOX_IN(parameter[1]) << 8) + MG_MAILBOX_IN(parameter[2]);
    mg_HAL_Discrete_Set_GEN_ENABLE(true);
    mg_HAL_Discrete_Set_Fuel_Pump_Low(true);
    mg_HAL_PWM_Set_Fuel_Pump_High_Frequency_And_Duty( freq, duty);
}
#endif