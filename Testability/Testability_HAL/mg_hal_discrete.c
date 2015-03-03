//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal_discrete_out.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:             %
//
// %version:         6 %
//
//=============================================================================

#include "mg_config.h"
#include "mg_hal_config.h"
#include "io_config_siu.h"
#include "dd_siu_interface.h"
#ifdef __MG_VSEP_USED
#include "dd_vsep_discrete.h"
#include "dd_vsep_discrete_interface.h"
#endif
#include "hal_gpio.h"

void mg_HAL_Discrete_Set_Discrete_Out_Group_Value(uint8_t index, bool state)
{
    if (NULL != MG_HAL_DISCRETE_OUT_GROUP[index].io)
    {
        VSEP_DiscreteSetImmediate(MG_HAL_DISCRETE_OUT_GROUP[index].io, state);
    }
}

void mg_HAL_Discrete_Set_ELOAD1(bool state)
{
    HAL_GPIO_SET_ELOAD1DICTL_Enable(state);
}

void mg_HAL_Discrete_Set_ELOAD2(bool state)
{
    HAL_GPIO_SET_ELOAD2DICTL_Enable(state);
}
#if 0
void mg_HAL_Discrete_Set_BRKLDI(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_BRKLDICTL, state);
}
#endif

#if 0
void mg_HAL_Discrete_Set_FPO1(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MG_MTSA_D_OUT_FPO1, state);
}

void mg_HAL_Discrete_Set_FPO2(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MG_MTSA_D_OUT_FPO2, state);
}

void mg_HAL_Discrete_Set_FPO3(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MG_MTSA_D_OUT_FPO3, state);
}

void mg_HAL_Discrete_Set_FPO4(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MG_MTSA_D_OUT_FPO4, state);
}

void mg_HAL_Discrete_Set_FPO5(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MG_MTSA_D_OUT_FPO5, state);
}

void mg_HAL_Discrete_Set_FPO6(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MG_MTSA_D_OUT_FPO6, state);
}

void mg_HAL_Discrete_Set_FPO7(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MG_MTSA_D_OUT_FPO7, state);
}
#endif
void mg_HAL_Discrete_Set_FSE(bool state)
{
    HAL_GPIO_SET_FSE_Enable(state);
}
#if 0
void mg_HAL_Discrete_Set_TACH(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_PWM_TACH, state);
}

void mg_HAL_Discrete_Set_ACREQDI(bool state)
{
#ifdef __MG_VSEP_USED
//    IO_DISCRETE_Set_Immediate_State(&MTSA_D_IN_ACREQDI, state);
    if (state)
    {
        VSEP_MPIO_Set_MODE_Immediate(MTSA_D_IN_ACREQDI.Configuration, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);
    }
    else
    {
        VSEP_MPIO_Set_MODE_Immediate(MTSA_D_IN_ACREQDI.Configuration, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT);
    }
#endif
}

void mg_HAL_Discrete_Set_PSPSDI(bool state)
{
#ifdef __MG_VSEP_USED
//    IO_DISCRETE_Set_Immediate_State(&MTSA_D_IN_PSPSDI, state);
    if (state)
    {
        VSEP_MPIO_Set_MODE_Immediate(MTSA_D_IN_PSPSDI.Configuration, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);
    }
    else
    {
        VSEP_MPIO_Set_MODE_Immediate(MTSA_D_IN_PSPSDI.Configuration, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT);
    }
#endif
}

void mg_HAL_Discrete_Set_MIDACDI(bool state)
{
#ifdef __MG_VSEP_USED
//    IO_DISCRETE_Set_Immediate_State(&MTSA_D_IN_MIDACDI, state);
    if (state)
    {
        VSEP_MPIO_Set_MODE_Immediate(MTSA_D_IN_MIDACDI.Configuration, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);
    }
    else
    {
        VSEP_MPIO_Set_MODE_Immediate(MTSA_D_IN_MIDACDI.Configuration, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT);
    }
#endif
}

void mg_HAL_Discrete_Set_Fuel_Pump_Low(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_DISCRETE_OUT_FPR, state);
#endif
#ifdef  __MG_VSEP_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_VSEP_D_OUT_FPR, state);
#endif
}

void mg_HAL_Discrete_Set_FAN1(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_PWM_2_FAN1, state);
#endif
#ifdef  __MG_VSEP_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_PWM_FAN, state);
#endif
}

void mg_HAL_Discrete_Set_FAN2(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_DISCRETE_OUT_FAN2, state);
#endif
#ifdef  __MG_VSEP_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_VSEP_D_OUT_FAN2, state);
#endif
}

void mg_HAL_Discrete_Set_O2_1_Pump_Current(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_O2_1_PUMPING_CURRENT, state);
#endif
#ifdef  __MG_VSEP_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_O2APUMP, state);
#endif
}

void mg_HAL_Discrete_Set_O2_2_Pump_Current(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_O2_2_PUMPING_CURRENT, state);
#endif
#ifdef  __MG_VSEP_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_O2BPUMP, state);
#endif
}

void mg_HAL_Discrete_Set_GEN_No_Affect(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_D_OUT_MIL, state);
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_D_OUT_CRUISE_LAMP, state);
#endif
#ifdef __MG_VSEP_USED
#endif
}

void mg_HAL_Discrete_Set_GEN_ENABLE(bool state)
{
#ifdef  __MG_C2PS_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_CONFIG_IOEN_CONTROL, state);
#endif
#ifdef __MG_TLE4471_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_GEN_ENABLE_REQ, state);
#endif
}

void mg_HAL_Discrete_Set_TODO(bool state)
{
#ifdef __MG_C2PS_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_CONFIG_TURN_OFF_INHIBIT_CONTROL, state);
#endif
#ifdef __MG_TLE4471_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_TLE4471_TODO, state);
#endif
}

#ifdef  __MG_C2PS_USED
void mg_HAL_Discrete_Set_C2PS_WTO(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_LPC_WTO_CONFIG_BIT, state);
}

void mg_HAL_Discrete_Set_C2PS_WP_Config(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_CONFIG_WP_CONFIG_OUTPUT_DRIVER, state);
}

void mg_HAL_Discrete_Set_C2PS_DRVENS(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_CONFIG_OUTPUT_DRIVER_ENABLE, state);
}

void mg_HAL_Discrete_Set_C2PS_VIGNF(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_CONFIG_VIGNF_CONFIGURATION, state);
}
#endif
#endif


bool mg_HAL_Discrete_Get_Discrete_In_Group(uint8_t index)
{
    bool state;
    if (MG_HIODEVICE_DI_NULL != MG_HAL_DISCRETE_IN_GROUP[index])
    {
        state = SIU_GPIO_DISCRETE_Get_State(MG_HAL_DISCRETE_IN_GROUP[index]);
    }
    else
    {
        state = false;
    }
    return state;
}

#if 0
bool mg_HAL_Discrete_Get_BRkSW(void)
{
    return IO_DISCRETE_Get_Immediate_State(&MTSA_D_IN_J1_69);
}

bool mg_HAL_Discrete_Get_ELOAD1(void)
{
    return IO_DISCRETE_Get_Immediate_State(&MTSA_D_IN_J1_35);
}

bool mg_HAL_Discrete_Get_ELOAD2(void)
{
    return IO_DISCRETE_Get_Immediate_State(&MTSA_D_IN_J1_34);
}

void mg_HAL_Discrete_Reconfigure_CAL(void)
{
    MTSA_D_IN_J1_33.Configuration = SIU_GPIO_Set_Polarity(MTSA_CONFIG_D_IN_J1_33, IO_ACTIVE_HIGH);
    MTSA_D_IN_J1_34.Configuration = SIU_GPIO_Set_Polarity(MTSA_CONFIG_D_IN_J1_34, IO_ACTIVE_HIGH);
    MTSA_D_IN_J1_35.Configuration = SIU_GPIO_Set_Polarity(MTSA_CONFIG_D_IN_J1_35, IO_ACTIVE_HIGH);
}
#endif