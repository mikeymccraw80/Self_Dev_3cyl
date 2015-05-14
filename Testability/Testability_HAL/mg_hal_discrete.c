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
#include "io_config_vsep.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_led.h"
#include "dd_vsep_discrete_interface.h"
#endif
#include "hal_gpio.h"

void mg_HAL_Discrete_Set_Discrete_Out_Group_Value(uint8_t index, bool state)
{
    if (MG_HIODEVICE_DO_NULL != MG_HAL_DISCRETE_OUT_GROUP[index].io)
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

void mg_HAL_Discrete_Set_BRKLDI(bool state)
{
    HAL_GPIO_SET_BRKLMPDICTL_Enable(state);
}


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

void mg_HAL_Discrete_Set_TACH(bool state)
{
    /* use pwm to simulate GPIO */
    if (state) {
       VSEP_PWM_PWMSetPeriod(VSEP_PO_TACH_CH, 100*64);
       VSEP_PWM_PWMSetDuty(VSEP_PO_TACH_CH, 32768);
    // VSEP_DiscreteSetImmediate(VSEP_PO_TACH_CH, state);
    } else {
       VSEP_PWM_PWMSetPeriod(VSEP_PO_TACH_CH, 100*64);
       VSEP_PWM_PWMSetDuty(VSEP_PO_TACH_CH, 0);
    }
    VSEP_SPI_Immediate_Transfer(VSEP_PO_TACH_CH, VSEP_MESSAGE_PWM );
}

void mg_HAL_Discrete_Set_ACREQDI(bool state)
{
#ifdef __MG_VSEP_USED
//    IO_DISCRETE_Set_Immediate_State(&MTSA_D_IN_ACREQDI, state);
    if (state)
    {
        VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_ACRequest_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);
    }
    else
    {
        VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_ACRequest_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT);
    }
#endif
}

void mg_HAL_Discrete_Set_PSPSDI(bool state)
{
#ifdef __MG_VSEP_USED
//    IO_DISCRETE_Set_Immediate_State(&MTSA_D_IN_PSPSDI, state);
    if (state)
    {
        VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_PSPS_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);
    }
    else
    {
        VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_PSPS_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT);
    }
#endif
}

void mg_HAL_Discrete_Set_MIDACDI(bool state)
{
#ifdef __MG_VSEP_USED
//    IO_DISCRETE_Set_Immediate_State(&MTSA_D_IN_MIDACDI, state);
    if (state)
    {
        VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_MIDAC_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);
    }
    else
    {
        VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_MIDAC_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT);
    }
#endif
}

#if 0
void mg_HAL_Discrete_Set_Fuel_Pump_Low(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_DISCRETE_OUT_FPR, state);
#endif
#ifdef  __MG_VSEP_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_VSEP_D_OUT_FPR, state);
#endif
}
#endif

void mg_HAL_Discrete_Set_FAN1(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_PWM_2_FAN1, state);
#endif
#ifdef  __MG_VSEP_USED
    HAL_GPIO_SET_FAN1_Enable(state);
#endif
}

void mg_HAL_Discrete_Set_FAN2(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_DISCRETE_OUT_FAN2, state);
#endif
#ifdef  __MG_VSEP_USED
    HAL_GPIO_SET_FAN2_Enable(state);
    VSEP_SPI_Immediate_Transfer(0, VSEP_MESSAGE_PCH_MPIO);
#endif
}

void mg_HAL_Discrete_Set_O2_1_Pump_Current(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_O2_1_PUMPING_CURRENT, state);
#endif
#ifdef  __MG_VSEP_USED
    // IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_O2APUMP, state);
    HAL_GPIO_SET_O2APUMP_Enable(state);
#endif
}

void mg_HAL_Discrete_Set_O2_2_Pump_Current(bool state)
{
#ifdef  __MG_C2MIO_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2MIO_O2_2_PUMPING_CURRENT, state);
#endif
#ifdef  __MG_VSEP_USED
    // IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_O2BPUMP, state);
    HAL_GPIO_SET_O2BPUMP_Enable(state);
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
    HAL_GPIO_SET_GEN_Enable(state);
#endif
}


void mg_HAL_Discrete_Set_TODO(bool state)
{
#ifdef __MG_C2PS_USED
    IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_CONFIG_TURN_OFF_INHIBIT_CONTROL, state);
#endif
#ifdef __MG_TLE4471_USED
    HAL_GPIO_SET_TODO_Enable(state);
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

bool mg_HAL_Discrete_Get_Discrete_In_Group(uint8_t index)
{
    bool state;
    if ((index >= 0) && (index <= 2)) {
        state = VSEP_DiscreteGet(MG_HAL_DISCRETE_IN_GROUP[index]);
    }
    else if (MG_HIODEVICE_DI_NULL != MG_HAL_DISCRETE_IN_GROUP[index])
    {
        state = SIU_GPIO_DISCRETE_Get_State(MG_HAL_DISCRETE_IN_GROUP[index]);
    }
    else
    {
        state = false;
    }
    return state;
}

bool mg_HAL_Discrete_Get_BRkSW(void)
{
    return HAL_GPIO_GET_BRKSWDI_Status();
}

bool mg_HAL_Discrete_Get_ELOAD1(void)
{
    return HAL_GPIO_GET_ELOAD1_Status();
}

bool mg_HAL_Discrete_Get_ELOAD2(void)
{
    return HAL_GPIO_GET_ELOAD2_Status();
}

void mg_HAL_Discrete_Reconfigure_CAL(void)
{

    /* reconfig eload and vsep mpio */
    HAL_GPIO_SET_ELOAD1DICTL_Enable(!IO_ACTIVE_HIGH);
    HAL_GPIO_SET_ELOAD2DICTL_Enable(!IO_ACTIVE_HIGH);
    HAL_GPIO_SET_BRKLMPDICTL_Enable(!IO_ACTIVE_HIGH);
    
    
    VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_ACRequest_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT);
    VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_PSPS_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);
    VSEP_MPIO_Set_MODE_Immediate(VSEP_MPIO_MIDAC_CH, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT);

    /* disable three led channel led mode */
    VSEP_LEDMODE_Set_Channel(VSEP_PO_CRUISI_CH, VSEP_LEDMODE_30, 0);
}
