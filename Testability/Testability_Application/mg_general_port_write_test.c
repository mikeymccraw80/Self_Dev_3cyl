//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_general_port_write_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Tue Oct 23 19:53:17 2012 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:            %
//
// %version:         2 %
//
//=============================================================================
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal_discrete.h"
#include "mg_hal_PWM.h"
#include "mg_hal_etc.h"

/*****************************************************************************
 * Function Prototype: void mg_general_port_write_test(void)
 *
 * Description: This test output the following pins as control
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_general_port_write_test(void)
{
    uint8_t port;
    uint8_t data;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    port = MG_MAILBOX_IN(parameter[0]);
    data =  MG_MAILBOX_IN(parameter[1]);
    mg_HAL_ETC_Discrete_Enable(true);
    mg_HAL_PWM_Set_ETCCTLPWM_Frequency_And_Duty(100, 50);
    if (port == 0)
    {
        if (data & 0x01)
        {
            mg_HAL_ETC_Discrete_Direction(true);
        }
        else
        {
            mg_HAL_ETC_Discrete_Direction(false);
        }
        if (data & 0x02)
        {
            mg_HAL_ETC_Discrete_Enable(true);
        }
        else
        {
            mg_HAL_ETC_Discrete_Enable(false);
        }
        if (data & 0x04)
        {
            mg_HAL_Discrete_Set_O2_1_Pump_Current(true);
        }
        else
        {
            mg_HAL_Discrete_Set_O2_1_Pump_Current(false);
        }
        if (data & 0x08)
        {
            mg_HAL_Discrete_Set_O2_2_Pump_Current(true);
        }
        else
        {
            mg_HAL_Discrete_Set_O2_2_Pump_Current(false);
        }
        if (data & 0x10)
        {
            mg_HAL_Discrete_Set_FSE(true);
        }
        else
        {
            mg_HAL_Discrete_Set_FSE(false);
        }
        if (data & 0x20)
        {
            mg_HAL_Discrete_Set_ELOAD2(true);
        }
        else
        {
            mg_HAL_Discrete_Set_ELOAD2(false);
        }
        if (data & 0x40)
        {
            mg_HAL_Discrete_Set_ELOAD1(true);
        }
        else
        {
            mg_HAL_Discrete_Set_ELOAD1(false);
        }
        if (data & 0x80)
        {
            mg_HAL_Discrete_Set_BRKLDI(true);
        }
        else
        {
            mg_HAL_Discrete_Set_BRKLDI(false);
        }
    }
    else
    {
        if (data & 0x01)
        {
            mg_HAL_Discrete_Set_ACREQDI(true);
        }
        else
        {
            mg_HAL_Discrete_Set_ACREQDI(false);
        }
        if (data & 0x02)
        {
            mg_HAL_Discrete_Set_PSPSDI(true);
        }
        else
        {
            mg_HAL_Discrete_Set_PSPSDI(false);
        }
        if (data & 0x04)
        {
            mg_HAL_Discrete_Set_MIDACDI(true);
        }
        else
        {
            mg_HAL_Discrete_Set_MIDACDI(false);
        }
        if (data & 0x08)
        {
        }
        else
        {
        }
        if (data & 0x10)
        {
        }
        else
        {
        }
        if (data & 0x20)
        {
        }
        else
        {
        }
        if (data & 0x40)
        {
        }
        else
        {
        }
        if (data & 0x80)
        {
        }
        else
        {
        }
    }
}

