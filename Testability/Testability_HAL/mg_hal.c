//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:              %
//
// %version:         7 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_config.h"
#include "mg_hal_config.h"
#include "mg_hal_analog.h"
#include "mg_hal_discrete.h"
#include "mg_hal_pwm.h"
#include "io_config_fmpll.h"
// #include "mg_hal_soh.h"
// #include "mg_hal_lin.h"
#include "mg_hal_timer.h"
#include "mg_hal_fault.h"
#include "hal_soh.h"
#include "dd_vsep_soh.h"
// #include "io_discrete.h"
// #include "io_interface.h"
#include "dd_swt_interface.h"
#ifdef __MG_C2PS_WATCHDOG_RESET_TEST
#include "dd_c2ps.h"
#endif
#ifdef __MG_TLE4471_WATCHDOG_RESET_TEST
#include "dd_tle4471.h"
#endif
#if 0
#define MG_STM_OVERFLOW_VALUE              0xFFFFFFFF
#define STM_CNT_REG                                    (uint32_t volatile  *)(0xFFF3C004)
#define STM_PRESCALE                                  80

#if MG_MCD5412_USED
#define UNIT_US                                         (TPU_A_TCR1_CLOCK_FREQ / 1000000)
#else
#define UNIT_US                                         (SYSTEM_FREQUENCY_HZ / 1000000)
#endif

#if MG_MCD5412_USED
#define VALIDATION_EST_US_ON                       (3400 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#define VALIDATION_EST_US_DELAY                    (6600 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#else
#define VALIDATION_EST_US_ON                       (3400 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define VALIDATION_EST_US_DELAY                    (6600 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#define VALIDATION_INJ_US_ON                       (10000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define VALIDATION_INJ_US_DELAY                    (0 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define VALIDATION_ETC_MS_REVERSE                  (10 * SYSTEM_FREQUENCY_HZ)
#define VALIDATION_ETC_FREQ                     3300

#if MG_MCD5412_USED
#define THERMAL_EST_US_ON                    (2680 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#define THERMAL_EST_US_DELAY              (2320 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#else
#define THERMAL_EST_US_ON                    (2680 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define THERMAL_EST_US_DELAY              (2320 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#define THERMAL_INJ_US_ON                    (2000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define THERMAL_INJ_US_DELAY              (3000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define THERMAL_ETC_MS_REVERSE          (10 * SYSTEM_FREQUENCY_HZ)
#define THERMAL_ETC_FREQ            3300
#if MG_MCD5412_USED
#define THERMAL_120_EST_US_ON                    (3400 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#define THERMAL_120_EST_US_DELAY              (27850 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#else
#define THERMAL_120_EST_US_ON                    (3400 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define THERMAL_120_EST_US_DELAY              (27850 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#define THERMAL_120_INJ_US_ON                    (15625 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define THERMAL_120_INJ_US_DELAY              (15625 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define THERMAL_120_ETC_MS_REVERSE          (10 * SYSTEM_FREQUENCY_HZ)
#define THERMAL_120_ETC_FREQ            1000

#if MG_MCD5412_USED
#define EMC_MODE_1_EST_ON                               (0 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#define EMC_MODE_1_EST_OFF                              (1000 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#else
#define EMC_MODE_1_EST_ON                               (0 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define EMC_MODE_1_EST_OFF                              (1000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#define EMC_MODE_1_INJ_ON                                (0 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define EMC_MODE_1_INJ_OFF                               (1000 * (SYSTEM_FREQUENCY_HZ / 1000000))

#if MG_MCD5412_USED
#define EMC_MODE_2_EST_ON                               (10000 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#define EMC_MODE_2_EST_OFF                              (15000 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#else
#define EMC_MODE_2_EST_ON                               (10000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define EMC_MODE_2_EST_OFF                              (15000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#define EMC_MODE_2_INJ_ON                                (25000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define EMC_MODE_2_INJ_OFF                               (0 * (SYSTEM_FREQUENCY_HZ / 1000000))

#if MG_MCD5412_USED
#define EMC_MODE_3_EST_ON                               (2800 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#define EMC_MODE_3_EST_OFF                              (7200 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#else
#define EMC_MODE_3_EST_ON                               (2800 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define EMC_MODE_3_EST_OFF                              (7200 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#define EMC_MODE_3_INJ_ON                                (10000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define EMC_MODE_3_INJ_OFF                               (0 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#if MG_MCD5412_USED
#define PC_EST_US_ON                    (3400 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#define PC_EST_US_DELAY              (6600 * (TPU_A_TCR1_CLOCK_FREQ / 1000000))
#else
#define PC_EST_US_ON                    (3400 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define PC_EST_US_DELAY              (6600 * (SYSTEM_FREQUENCY_HZ / 1000000))
#endif
#define PC_INJ_US_ON                    (10000 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define PC_INJ_US_DELAY              (0 * (SYSTEM_FREQUENCY_HZ / 1000000))
#define PC_ETC_MS_REVERSE          (10 * SYSTEM_FREQUENCY_HZ)
#define PC_ETC_FREQ            3300
#define PC_ETC_FREQ_MAX            (PC_ETC_FREQ * 1.05)
#define PC_ETC_FREQ_MIN            (PC_ETC_FREQ * 0.95)


#ifdef __MG_C2PS_WATCHDOG_RESET_TEST
#if (C2PS_CONFIG_TIMEOUT_MODE_INIT_0 == C2PS_COP_TIMEOUT_MODE_15P625)
#define MG_COP_MIN_PERIOD                       (5 * (SYSTEM_FREQUENCY_HZ / 1000))      /* 5ms */
#else
    #if (C2PS_CONFIG_TIMEOUT_MODE_INIT_0 == C2PS_COP_TIMEOUT_MODE_31P25MS)
#define MG_COP_MIN_PERIOD                       (10 * (SYSTEM_FREQUENCY_HZ / 1000))      /* 10ms */
    #else
        #if(C2PS_CONFIG_TIMEOUT_MODE_INIT_0 == C2PS_COP_TIMEOUT_MODE_62P5MS)
#define MG_COP_MIN_PERIOD                       (20 * (SYSTEM_FREQUENCY_HZ / 1000))      /* 20ms */
        #else
            #if(C2PS_CONFIG_TIMEOUT_MODE_INIT_0 == C2PS_COP_TIMEOUT_MODE_125MS)
#define MG_COP_MIN_PERIOD                       (40 * (SYSTEM_FREQUENCY_HZ / 1000))      /* 40ms */
            #endif
        #endif
    #endif
#endif
#endif
// #ifdef __MG_TLE4471_WATCHDOG_RESET_TEST
#define MG_COP_MIN_PERIOD                       (10 * (1000000 / 1000))    /* 10ms */
// #endif

#if 0

/*=============================================================================
 * mg_HAL_Entey_Critical
 * @func  loose C2PS COP during
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Entey_Critical(void)
{
#ifdef __MG_C2PS_USED
    C2PS_CONFIG_Txd[0][0] = C2PS_CONFIG_Txd[0][0] & ~(uint16_t)0x18 |C2PS_COP_TIMEOUT_MODE_125MS;
    C2PS_SPI_Immediate_Transfer( C2PS_Set_Device_Index(0,C2PS_INDEX_0), C2PS_MESSAGE_CONFIG );
#endif
#ifdef __MG_TLE4471_USED
#endif
}

/*=============================================================================
 * mg_HAL_Exit_Critical
 * @func  restore C2PS COP during
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Exit_Critical(void)
{
#ifdef __MG_C2PS_USED
    C2PS_CONFIG_Txd[0][0] = C2PS_CONFIG_Txd[0][0] & ~(uint16_t)0x18 |C2PS_COP_TIMEOUT_MODE_31P25MS;
    C2PS_SPI_Immediate_Transfer( C2PS_Set_Device_Index(0,C2PS_INDEX_0), C2PS_MESSAGE_CONFIG );
#endif
#ifdef __MG_TLE4471_USED
#endif
}
#endif

/*=============================================================================
 * mg_HAL_Service_WatchDog
 * @func  service watchdog here, including COP and C2PS watchdog
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Service_WatchDog(void)
{
    // XuHui - add watchdog service here
    static uint32_t start_timer = 0;
    uint32_t current_timer;
#ifdef __MG_TLE4471_WATCHDOG_RESET_TEST
    uint32_t CHALLENGE_TEMP, RESPONSE_TEMP;
#endif
    current_timer = mg_HAL_Timer_Get_STM_In_CNT();
    if (MG_COP_MIN_PERIOD < mg_HAL_Timer_Get_STM_Diff_In_CNT(current_timer, start_timer))
    {
        start_timer = mg_HAL_Timer_Get_STM_In_CNT();
#ifdef __MG_C2PS_WATCHDOG_RESET_TEST
        C2PS_CONFIG_COP_Set_Toggle_Sequence(0);
        C2PS_SPI_Immediate_Transfer( C2PS_Set_Device_Index(0,C2PS_INDEX_0), C2PS_MESSAGE_COP );
#endif
#ifdef __MG_TLE4471_WATCHDOG_RESET_TEST
        TLE4471_WD_Toggle_Immediate();
        SOH_VSEP_CR_Service();
#endif
    }
}

/*=============================================================================
 * mg_HAL_SWT_Enable_WatchDog
 * @func  set SWT enable state
 * @parm  enable state
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_SWT_Enable_WatchDog(bool state)
{
    SWT_Enable_WatchDog( state );
}
#if 0
void mg_HAL_Disable_CAN_10ms_Task_Timer(void)
{
    IO_INTERRUPT_Set_Enable( &MTSA_PIT_TIMER_3, false );
}

void mg_HAL_Internal_Device_Init(void)
{
    IO_PULSE_IC_Initialize_Channel(&MG_MTSA_IC_58XPOS);
    IO_PULSE_IC_Initialize_Channel(&MG_MTSA_IC_CAM1);
    IO_PULSE_IC_Initialize_Channel(&MG_MTSA_IC_CAM2);
    IO_PULSE_IC_Initialize_Channel(&MG_MTSA_IC_VSS);
    IO_PULSE_IC_Initialize_Channel(&MG_MTSA_IC_ENS);

    mg_HAL_Timer_Set_STM_Enable(true);

    mg_HAL_LIN_Set_DMA_Enable(false);
    
    MG_Reset_SCI(&SCI_PORT_0);
    MG_Init_SCI(&SCI_PORT_0);
    MG_Init_SCI(&SCI_PORT_1);
}
#endif
/*=============================================================================
 * mg_External_Device_Init
 * @func  Initialize the external devices
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_External_Device_Init(void)
{
    if (mg_HAL_Get_SOH_Test_Flag() == 0)
    {
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
        mg_HAL_SOH_Init(true);
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
        mg_HAL_SOH_Init(false);
#endif
    }
    else
    {
        mg_HAL_SOH_Init(false);
        MG_MAILBOX_IN(testid) = 0x19;
        MG_MAILBOX_IN(parameter[0]) = (mg_HAL_Get_SOH_Test_Flag() & 0x03);
    }
}

#if 0
void mg_HAL_SPI_Timer_Enable(bool state)
{
    IO_INTERRUPT_Set_Enable( &MTSA_SPI_TIMER, state );
}
#endif

void mg_HAL_Output_Cycling_Init(void)
{
    MG_SIU_GPIO_PWM_Initialize_Device_Override();
    MG_HAL_DISCRETE_OUT_GROUP[19].type = DISCRETE;
}

void mg_HAL_Output_Cycling_Uninit(void)
{
//    MG_HAL_DISCRETE_OUT_GROUP[21].type = PWM;
}

void mg_HAL_Output_Cycling_Config(void)
{
    MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = FREQ_0P5_50_ON;             /* MPR */
    MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = FREQ_0P5_50_ON;             /* FPR */
    MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[2].on_time_us = FREQ_0P5_50_ON;             /* AC Clutch */
    MG_HAL_DISCRETE_OUT_GROUP[2].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[3].on_time_us = FREQ_0P5_50_ON;             /* FAN2 */
    MG_HAL_DISCRETE_OUT_GROUP[3].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[4].frequency = 500;                                   /* 500Hz Fuel Consumption */
    MG_HAL_DISCRETE_OUT_GROUP[4].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[5].on_time_us = FREQ_0P5_50_ON;               /* SAIC */
    MG_HAL_DISCRETE_OUT_GROUP[5].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[6].on_time_us = FREQ_0P5_50_ON;               /* FAN1 / PWM FAN */
    MG_HAL_DISCRETE_OUT_GROUP[6].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[7].frequency = 16;                                    /* 16Hz CCP */
    MG_HAL_DISCRETE_OUT_GROUP[7].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[8].frequency = 250;                                   /* 128Hz VVT1 */
    MG_HAL_DISCRETE_OUT_GROUP[8].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[9].frequency = 250;                                   /* 128Hz VVT2 */
    MG_HAL_DISCRETE_OUT_GROUP[9].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[10].on_time_us = FREQ_0P5_50_ON;             /* Inter Coolant Fan / VGIS1 */
    MG_HAL_DISCRETE_OUT_GROUP[10].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[11].on_time_us = FREQ_0P5_50_ON;             /* Turbo BPAR / VGIS2 */
    MG_HAL_DISCRETE_OUT_GROUP[11].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[12].on_time_us = FREQ_16_50_ON;             /* 16Hz O2A Heater */
    MG_HAL_DISCRETE_OUT_GROUP[12].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[12].frequency = 16;                                    /* 16Hz O2A Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[12].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[13].on_time_us = FREQ_16_50_ON;             /* 16Hz O2B Heater */
    MG_HAL_DISCRETE_OUT_GROUP[13].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[13].frequency = 16;                                    /* 16Hz O2B Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[13].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[14].frequency = 250;                                /* 250Hz Water Pump Control  */
    MG_HAL_DISCRETE_OUT_GROUP[14].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[15].frequency = 32;                                  /* 32Hz Turbo AWG/Turbo VGT */
    MG_HAL_DISCRETE_OUT_GROUP[15].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = FREQ_0P5_50_ON;            /* MIL / CEL */
    MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[17].on_time_us = FREQ_0P5_50_ON;            /* SVS */
    MG_HAL_DISCRETE_OUT_GROUP[17].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[18].on_time_us = FREQ_100_50_ON;        /* 100Hz Coolant Guage / Thermal Control */
    MG_HAL_DISCRETE_OUT_GROUP[18].off_time_us = FREQ_100_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[18].frequency = 100;                               /* 100Hz Coolant Guage / Thermal Control */
//    MG_HAL_DISCRETE_OUT_GROUP[18].duty = 50;
//    MG_HAL_DISCRETE_OUT_GROUP[19].frequency = 350;                               /* 350Hz SAIC PWM */
//    MG_HAL_DISCRETE_OUT_GROUP[19].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[19].on_time_us = FREQ_0P5_50_ON;            /* 0.5Hz SAIC PWM */
    MG_HAL_DISCRETE_OUT_GROUP[19].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 50;                               /* 50Hz TACH */
    MG_HAL_DISCRETE_OUT_GROUP[20].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[21].on_time_us = FREQ_0P5_50_ON;           /* Cruise Indicator */
    MG_HAL_DISCRETE_OUT_GROUP[21].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_EST_GROUP.on_time_us = PC_EST_US_ON;                                /* On time 2.68ms, 50Hz for 2IGBT or 25Hz for 4IGBT */
    MG_HAL_EST_GROUP.delay_time_us = PC_EST_US_DELAY;
    MG_HAL_INJ_GROUP.on_time_us = PC_INJ_US_ON;                                /* 25Hz, 25% duty*/
    MG_HAL_INJ_GROUP.delay_time_us = PC_INJ_US_DELAY;
    MG_HAL_ETC_GROUP.reverse_time_ms = PC_ETC_MS_REVERSE;
    MG_HAL_ETC_GROUP.freq = PC_ETC_FREQ;
    MG_HAL_ETC_GROUP.duty = 95;
}

void mg_HAL_Output_Cycling_Diagnostic(uint8_t *pch)
{
    uint8_t idx;
    uint8_t *pch_idx;
    uint8_t out_map_index;
    uint8_t out_map_position;
    uint32_t ETC_freq;
    pch_idx = pch;
    for (idx = 0; idx < 16; idx++)
    {
        *(pch_idx + idx) = 0;
    }
//    pch_idx = 0;
    mg_HAL_ETC_Fault_Clear();
    mg_HAL_Fault_ETC_Over_Current_Test_Configure(0x00);
    mg_HAL_ETC_Fault_Read();
#ifdef __MG_PHDL_USED
    *pch_idx = mg_HAL_ETC_Fault_Get(0);
    pch_idx++;
#endif
#ifdef __MG_L9958_USED
    *pch_idx = mg_HAL_ETC_Fault_Get(0);
    pch_idx++;
    *pch_idx = mg_HAL_ETC_Fault_Get(1);
    pch_idx++;
#endif
#ifdef __MG_C2MIO_USED
    mg_HAL_ComplexIO_Fault_Read();
    for (idx = 0; idx < MG_COMPLEXIO_CHANNEL_MAX; idx++)
    {
        out_map_index = (idx >> 2);
        out_map_position = ((idx & 0x03) << 1);
        *(pch_idx +out_map_index) |= mg_HAL_ComplexIO_Fault_Get( idx) << out_map_position;
    }
    pch_idx += (out_map_index + 1);
    mg_HAL_ComplexIO_Fault_Clear();
#endif
#ifdef __MG_VSEP_USED
    // mg_HAL_ComplexIO_Fault_Read();
    for (idx = 0; idx < MG_COMPLEXIO_CHANNEL_MAX; idx++)
    {
        out_map_index = (idx >> 2);
        out_map_position = ((idx & 0x03) << 1);
        // *(pch_idx +out_map_index) |= mg_HAL_ComplexIO_Fault_Get( idx) << out_map_position;
    }
    pch_idx += (out_map_index + 1);
    // mg_HAL_ComplexIO_Fault_Clear();
#endif
#ifdef __MG_PHDL_USED
    ETC_freq = mg_HAL_PWM_Get_ETCCTLPWM_Frequency();
    if ((PC_ETC_FREQ_MAX > ETC_freq) || (PC_ETC_FREQ_MIN < ETC_freq))
    {
        *pch_idx = 0x00;
    }
    else
    {
        *pch_idx = 0xFF;
    }
    pch_idx++;
    *pch_idx = (uint8_t)((ETC_freq >> 8) & 0xFF);
    pch_idx++;
    *pch_idx = (uint8_t)(ETC_freq & 0xFF);
    pch_idx++;
#endif
#ifdef __MG_C2PS_USED
    mg_HAL_PowerDevice_Fault_Read();
    *pch_idx = mg_HAL_PowerDevice_Fault_Get( 0);
#endif

}
#if 0
void mg_HAL_Output_Cycling_EMC_Init(void)
{
    MG_SIU_GPIO_PWM_Initialize_Device_Override();
//    mg_HAL_PWM_EMC_Cycling_Initialize();
//    MG_HAL_DISCRETE_OUT_GROUP[13].io = (void *)&MG_MTSA_PWM_FUEL_CONSUM;
    MG_HAL_DISCRETE_OUT_GROUP[19].type = DISCRETE;
}
#endif
void mg_HAL_Output_Cycling_EMC_Uninit(void)
{
    
}
#if 0
void mg_HAL_Output_Cycling_EMC_Config(void)
{
    if (mg_HAL_Analog_Get_TPS1() < 0x7fff)
    {
        if (mg_HAL_Analog_Get_TPS2() < 0x7fff)
        {
            MG_HAL_EST_GROUP.on_time_us = EMC_MODE_1_EST_ON;                     /* IGN off */
            MG_HAL_EST_GROUP.delay_time_us = EMC_MODE_1_EST_OFF;
            MG_HAL_INJ_GROUP.on_time_us = EMC_MODE_1_INJ_ON;                       /* no output */
            MG_HAL_INJ_GROUP.delay_time_us = EMC_MODE_1_INJ_OFF;
            mg_HAL_Discrete_Set_GEN_ENABLE(false);
            mg_HAL_Discrete_Set_FSE(false);
            MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = CONST_FALSE_ON;                                  /* MPR */
            MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = CONST_FALSE_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = CONST_FALSE_ON;                                  /* FPR */
            MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = CONST_FALSE_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = CONST_FALSE_ON;                                /* MIL */
            MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = CONST_FALSE_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 100;                               /* TACH */
            MG_HAL_DISCRETE_OUT_GROUP[20].duty = 0;
            MG_HAL_ETC_GROUP.freq = 0;
        }
        else
        {
            MG_HAL_EST_GROUP.on_time_us = EMC_MODE_2_EST_ON;                     /* 90% 10Hz */
            MG_HAL_EST_GROUP.delay_time_us = EMC_MODE_2_EST_OFF;
            MG_HAL_INJ_GROUP.on_time_us = EMC_MODE_2_INJ_ON;                       /* 75% 10Hz */
            MG_HAL_INJ_GROUP.delay_time_us = EMC_MODE_2_INJ_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = FREQ_4_80_ON;                                  /* MPR */
            MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = FREQ_4_20_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = FREQ_4_80_ON;                                  /* FPR */
            MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = FREQ_4_20_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[2].on_time_us = FREQ_1_50_ON;             /* AC Clutch */
    MG_HAL_DISCRETE_OUT_GROUP[2].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[3].on_time_us = FREQ_1_50_ON;             /* FAN2 */
    MG_HAL_DISCRETE_OUT_GROUP[3].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[4].frequency = 500;                                   /* 500Hz Fuel Consumption */
    MG_HAL_DISCRETE_OUT_GROUP[4].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[5].on_time_us = FREQ_1_50_ON;               /* SAIC */
    MG_HAL_DISCRETE_OUT_GROUP[5].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[6].on_time_us = FREQ_1_50_ON;               /* FAN1 / PWM FAN */
    MG_HAL_DISCRETE_OUT_GROUP[6].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[7].frequency = 16;                                    /* 16Hz CCP */
    MG_HAL_DISCRETE_OUT_GROUP[7].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[8].frequency = 128;                                   /* 128Hz VVT1 */
    MG_HAL_DISCRETE_OUT_GROUP[8].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[9].frequency = 128;                                   /* 128Hz VVT2 */
    MG_HAL_DISCRETE_OUT_GROUP[9].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[10].on_time_us = FREQ_1_50_ON;             /* Inter Coolant Fan / VGIS1 */
    MG_HAL_DISCRETE_OUT_GROUP[10].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[11].on_time_us = FREQ_1_50_ON;             /* Turbo BPAR / VGIS2 */
    MG_HAL_DISCRETE_OUT_GROUP[11].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[12].on_time_us = FREQ_16_50_ON;             /* 16Hz O2A Heater */
    MG_HAL_DISCRETE_OUT_GROUP[12].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[12].frequency = 16;                                    /* 16Hz O2A Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[12].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[13].on_time_us = FREQ_16_50_ON;             /* 16Hz O2B Heater */
    MG_HAL_DISCRETE_OUT_GROUP[13].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[13].frequency = 16;                                    /* 16Hz O2B Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[13].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[14].frequency = 250;                                /* 250Hz Water Pump Control  */
    MG_HAL_DISCRETE_OUT_GROUP[14].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[15].frequency = 32;                                  /* 32Hz Turbo AWG/Turbo VGT */
    MG_HAL_DISCRETE_OUT_GROUP[15].duty = 50;
            MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = FREQ_4_80_ON;                                /* MIL */
            MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = FREQ_4_20_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[17].on_time_us = FREQ_1_50_ON;            /* SVS */
    MG_HAL_DISCRETE_OUT_GROUP[17].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[18].on_time_us = FREQ_100_50_ON;        /* 100Hz Coolant Guage / Thermal Control */
    MG_HAL_DISCRETE_OUT_GROUP[18].off_time_us = FREQ_100_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[18].frequency = 100;                               /* 100Hz Coolant Guage / Thermal Control */
//    MG_HAL_DISCRETE_OUT_GROUP[18].duty = 50;
//    MG_HAL_DISCRETE_OUT_GROUP[19].frequency = 1;                               /* 128Hz SAIC PWM */
//    MG_HAL_DISCRETE_OUT_GROUP[19].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[19].on_time_us = FREQ_1_50_ON;            /* 1Hz SAIC PWM */
    MG_HAL_DISCRETE_OUT_GROUP[19].off_time_us = FREQ_1_50_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 50;                               /* TACH */
            MG_HAL_DISCRETE_OUT_GROUP[20].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[21].on_time_us = FREQ_1_50_ON;           /* Cruise Indicator */
    MG_HAL_DISCRETE_OUT_GROUP[21].off_time_us = FREQ_1_50_OFF;
        }
    }
    else
    {
        if (mg_HAL_Analog_Get_TPS2() < 0x7fff)
        {
            MG_HAL_EST_GROUP.on_time_us = EMC_MODE_3_EST_ON;                     /* 93% 25Hz */
            MG_HAL_EST_GROUP.delay_time_us = EMC_MODE_3_EST_OFF;
            MG_HAL_INJ_GROUP.on_time_us = EMC_MODE_3_INJ_ON;                       /* 75% 25Hz */
            MG_HAL_INJ_GROUP.delay_time_us = EMC_MODE_3_INJ_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = FREQ_4_80_ON;                                  /* MPR */
            MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = FREQ_4_20_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = FREQ_4_80_ON;                                  /* FPR */
            MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = FREQ_4_20_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[2].on_time_us = FREQ_1_50_ON;             /* AC Clutch */
    MG_HAL_DISCRETE_OUT_GROUP[2].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[3].on_time_us = FREQ_1_50_ON;             /* FAN2 */
    MG_HAL_DISCRETE_OUT_GROUP[3].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[4].frequency = 500;                                   /* 500Hz Fuel Consumption */
    MG_HAL_DISCRETE_OUT_GROUP[4].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[5].on_time_us = FREQ_1_50_ON;               /* SAIC */
    MG_HAL_DISCRETE_OUT_GROUP[5].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[6].on_time_us = FREQ_1_50_ON;               /* FAN1 / PWM FAN */
    MG_HAL_DISCRETE_OUT_GROUP[6].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[7].frequency = 16;                                    /* 16Hz CCP */
    MG_HAL_DISCRETE_OUT_GROUP[7].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[8].frequency = 128;                                   /* 128Hz VVT1 */
    MG_HAL_DISCRETE_OUT_GROUP[8].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[9].frequency = 128;                                   /* 128Hz VVT2 */
    MG_HAL_DISCRETE_OUT_GROUP[9].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[10].on_time_us = FREQ_1_50_ON;             /* Inter Coolant Fan / VGIS1 */
    MG_HAL_DISCRETE_OUT_GROUP[10].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[11].on_time_us = FREQ_1_50_ON;             /* Turbo BPAR / VGIS2 */
    MG_HAL_DISCRETE_OUT_GROUP[11].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[12].on_time_us = FREQ_16_50_ON;             /* 16Hz O2A Heater */
    MG_HAL_DISCRETE_OUT_GROUP[12].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[12].frequency = 16;                                    /* 16Hz O2A Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[12].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[13].on_time_us = FREQ_16_50_ON;             /* 16Hz O2B Heater */
    MG_HAL_DISCRETE_OUT_GROUP[13].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[13].frequency = 16;                                    /* 16Hz O2B Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[13].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[14].frequency = 250;                                /* 250Hz Water Pump Control  */
    MG_HAL_DISCRETE_OUT_GROUP[14].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[15].frequency = 32;                                  /* 32Hz Turbo AWG/Turbo VGT */
    MG_HAL_DISCRETE_OUT_GROUP[15].duty = 50;
            MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = FREQ_4_80_ON;                                /* MIL */
            MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = FREQ_4_20_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[17].on_time_us = FREQ_1_50_ON;            /* SVS */
    MG_HAL_DISCRETE_OUT_GROUP[17].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[18].on_time_us = FREQ_100_50_ON;        /* 100Hz Coolant Guage / Thermal Control */
    MG_HAL_DISCRETE_OUT_GROUP[18].off_time_us = FREQ_100_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[18].frequency = 100;                               /* 100Hz Coolant Guage / Thermal Control */
//    MG_HAL_DISCRETE_OUT_GROUP[18].duty = 50;
//    MG_HAL_DISCRETE_OUT_GROUP[19].frequency = 1;                               /* 128Hz SAIC PWM */
//    MG_HAL_DISCRETE_OUT_GROUP[19].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[19].on_time_us = FREQ_1_50_ON;            /* 1Hz SAIC PWM */
    MG_HAL_DISCRETE_OUT_GROUP[19].off_time_us = FREQ_1_50_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 50;                               /* TACH */
            MG_HAL_DISCRETE_OUT_GROUP[20].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[21].on_time_us = FREQ_1_50_ON;           /* Cruise Indicator */
    MG_HAL_DISCRETE_OUT_GROUP[21].off_time_us = FREQ_1_50_OFF;
        }
        else
        {
            MG_HAL_EST_GROUP.on_time_us = EMC_MODE_1_EST_ON;                     /* EMS doesn't work */
            MG_HAL_EST_GROUP.delay_time_us = EMC_MODE_1_EST_OFF;
            MG_HAL_INJ_GROUP.on_time_us = EMC_MODE_1_INJ_ON;                       /* EMS doesn't work */
            MG_HAL_INJ_GROUP.delay_time_us = EMC_MODE_1_INJ_OFF;
            mg_HAL_Discrete_Set_GEN_ENABLE(false);
            mg_HAL_Discrete_Set_FSE(false);
            MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = CONST_FALSE_ON;                                  /* MPR */
            MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = CONST_FALSE_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = CONST_FALSE_ON;                                  /* FPR */
            MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = CONST_FALSE_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = CONST_FALSE_ON;                                /* MIL */
            MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = CONST_FALSE_OFF;
            MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 100;                               /* TACH */
            MG_HAL_DISCRETE_OUT_GROUP[20].duty = 0;
            MG_HAL_ETC_GROUP.freq = 0;
        }
    }
}

void mg_HAL_Output_Cycling_Thermal_Config(void)
{
    MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = FREQ_1_50_ON;             /* MPR */
    MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = FREQ_1_50_ON;             /* FPR */
    MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[2].on_time_us = FREQ_1_50_ON;             /* AC Clutch */
    MG_HAL_DISCRETE_OUT_GROUP[2].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[3].on_time_us = FREQ_1_50_ON;             /* FAN2 */
    MG_HAL_DISCRETE_OUT_GROUP[3].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[4].frequency = 500;                                   /* 500Hz Fuel Consumption */
    MG_HAL_DISCRETE_OUT_GROUP[4].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[5].on_time_us = FREQ_1_50_ON;               /* SAIC */
    MG_HAL_DISCRETE_OUT_GROUP[5].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[6].on_time_us = FREQ_1_50_ON;               /* FAN1 / PWM FAN */
    MG_HAL_DISCRETE_OUT_GROUP[6].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[7].frequency = 16;                                    /* 16Hz CCP */
    MG_HAL_DISCRETE_OUT_GROUP[7].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[8].frequency = 128;                                   /* 128Hz VVT1 */
    MG_HAL_DISCRETE_OUT_GROUP[8].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[9].frequency = 128;                                   /* 128Hz VVT2 */
    MG_HAL_DISCRETE_OUT_GROUP[9].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[10].on_time_us = FREQ_1_50_ON;             /* Inter Coolant Fan / VGIS1 */
    MG_HAL_DISCRETE_OUT_GROUP[10].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[11].on_time_us = FREQ_1_50_ON;             /* Turbo BPAR / VGIS2 */
    MG_HAL_DISCRETE_OUT_GROUP[11].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[12].on_time_us = FREQ_16_50_ON;             /* 16Hz O2A Heater */
    MG_HAL_DISCRETE_OUT_GROUP[12].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[12].frequency = 16;                                    /* 16Hz O2A Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[12].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[13].on_time_us = FREQ_16_50_ON;             /* 16Hz O2B Heater */
    MG_HAL_DISCRETE_OUT_GROUP[13].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[13].frequency = 16;                                    /* 16Hz O2B Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[13].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[14].frequency = 250;                                /* 250Hz Water Pump Control  */
    MG_HAL_DISCRETE_OUT_GROUP[14].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[15].frequency = 32;                                  /* 32Hz Turbo AWG/Turbo VGT */
    MG_HAL_DISCRETE_OUT_GROUP[15].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = FREQ_1_50_ON;            /* MIL / CEL */
    MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[17].on_time_us = FREQ_1_50_ON;            /* SVS */
    MG_HAL_DISCRETE_OUT_GROUP[17].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[18].on_time_us = FREQ_100_50_ON;        /* 100Hz Coolant Guage / Thermal Control */
    MG_HAL_DISCRETE_OUT_GROUP[18].off_time_us = FREQ_100_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[18].frequency = 100;                               /* 100Hz Coolant Guage / Thermal Control */
//    MG_HAL_DISCRETE_OUT_GROUP[18].duty = 50;
//    MG_HAL_DISCRETE_OUT_GROUP[19].frequency = 1;                               /* 128Hz SAIC PWM */
//    MG_HAL_DISCRETE_OUT_GROUP[19].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[19].on_time_us = FREQ_1_50_ON;            /* 1Hz SAIC PWM */
    MG_HAL_DISCRETE_OUT_GROUP[19].off_time_us = FREQ_1_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 200;                               /* 200Hz TACH */
    MG_HAL_DISCRETE_OUT_GROUP[20].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[21].on_time_us = FREQ_1_50_ON;           /* Cruise Indicator */
    MG_HAL_DISCRETE_OUT_GROUP[21].off_time_us = FREQ_1_50_OFF;
    MG_HAL_EST_GROUP.on_time_us = THERMAL_EST_US_ON;                     /* High freq, use STM CNT, On time 2.68ms, 100Hz for 2IGBT */
    MG_HAL_EST_GROUP.delay_time_us = THERMAL_EST_US_DELAY;
    MG_HAL_INJ_GROUP.on_time_us = THERMAL_INJ_US_ON;                       /* High freq, use STM CNT, 100Hz, 90% duty*/
    MG_HAL_INJ_GROUP.delay_time_us = THERMAL_INJ_US_DELAY;
    MG_HAL_ETC_GROUP.reverse_time_ms = THERMAL_ETC_MS_REVERSE;
    MG_HAL_ETC_GROUP.freq = THERMAL_ETC_FREQ;
    MG_HAL_ETC_GROUP.duty = 95; 
}

void mg_HAL_Output_Cycling_Thermal_Config_120(void)
{
    MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = FREQ_0P5_50_ON;             /* MPR */
    MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = FREQ_0P5_50_ON;             /* FPR */
    MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[2].on_time_us = FREQ_0P5_50_ON;             /* AC Clutch */
    MG_HAL_DISCRETE_OUT_GROUP[2].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[3].on_time_us = FREQ_0P5_50_ON;             /* FAN2 */
    MG_HAL_DISCRETE_OUT_GROUP[3].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[4].frequency = 500;                                   /* 500Hz Fuel Consumption */
    MG_HAL_DISCRETE_OUT_GROUP[4].duty = 25;
    MG_HAL_DISCRETE_OUT_GROUP[5].on_time_us = FREQ_0P5_50_ON;               /* SAIC */
    MG_HAL_DISCRETE_OUT_GROUP[5].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[6].on_time_us = FREQ_0P5_50_ON;               /* FAN1 / PWM FAN */
    MG_HAL_DISCRETE_OUT_GROUP[6].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[7].frequency = 16;                                    /* 16Hz CCP */
    MG_HAL_DISCRETE_OUT_GROUP[7].duty = 25;
    MG_HAL_DISCRETE_OUT_GROUP[8].frequency = 128;                                   /* 128Hz VVT1 */
    MG_HAL_DISCRETE_OUT_GROUP[8].duty = 25;
    MG_HAL_DISCRETE_OUT_GROUP[9].frequency = 128;                                   /* 128Hz VVT2 */
    MG_HAL_DISCRETE_OUT_GROUP[9].duty = 25;
    MG_HAL_DISCRETE_OUT_GROUP[10].on_time_us = FREQ_0P5_50_ON;             /* Inter Coolant Fan / VGIS1 */
    MG_HAL_DISCRETE_OUT_GROUP[10].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[11].on_time_us = FREQ_0P5_50_ON;             /* Turbo BPAR / VGIS2 */
    MG_HAL_DISCRETE_OUT_GROUP[11].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[12].on_time_us = FREQ_16_25_ON;             /* 16Hz O2A Heater */
    MG_HAL_DISCRETE_OUT_GROUP[12].off_time_us = FREQ_16_25_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[12].frequency = 16;                                    /* 16Hz O2A Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[12].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[13].on_time_us = FREQ_16_25_ON;             /* 16Hz O2B Heater */
    MG_HAL_DISCRETE_OUT_GROUP[13].off_time_us = FREQ_16_25_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[13].frequency = 16;                                    /* 16Hz O2B Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[13].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[14].frequency = 250;                                /* 250Hz Water Pump Control  */
    MG_HAL_DISCRETE_OUT_GROUP[14].duty = 25;
    MG_HAL_DISCRETE_OUT_GROUP[15].frequency = 32;                                  /* 32Hz Turbo AWG/Turbo VGT */
    MG_HAL_DISCRETE_OUT_GROUP[15].duty = 25;
    MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = FREQ_0P5_50_ON;            /* MIL / CEL */
    MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[17].on_time_us = FREQ_0P5_50_ON;            /* SVS */
    MG_HAL_DISCRETE_OUT_GROUP[17].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[18].on_time_us = FREQ_100_25_ON;        /* 100Hz Coolant Guage / Thermal Control */
    MG_HAL_DISCRETE_OUT_GROUP[18].off_time_us = FREQ_100_25_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[18].frequency = 100;                               /* 100Hz Coolant Guage / Thermal Control */
//    MG_HAL_DISCRETE_OUT_GROUP[18].duty = 50;
//    MG_HAL_DISCRETE_OUT_GROUP[19].frequency = 1;                               /* 128Hz SAIC PWM */
//    MG_HAL_DISCRETE_OUT_GROUP[19].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[19].on_time_us = FREQ_0P5_50_ON;            /* 1Hz SAIC PWM */
    MG_HAL_DISCRETE_OUT_GROUP[19].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 32;                               /* 200Hz TACH */
    MG_HAL_DISCRETE_OUT_GROUP[20].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[21].on_time_us = FREQ_0P5_50_ON;           /* Cruise Indicator */
    MG_HAL_DISCRETE_OUT_GROUP[21].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_EST_GROUP.on_time_us = THERMAL_120_EST_US_ON;                     /* On time 2.68ms, 50Hz for 2IGBT or 25Hz for 4IGBT */
    MG_HAL_EST_GROUP.delay_time_us = THERMAL_120_EST_US_DELAY;
    MG_HAL_INJ_GROUP.on_time_us = THERMAL_120_INJ_US_ON;                       /* 25Hz, 25% duty*/
    MG_HAL_INJ_GROUP.delay_time_us = THERMAL_120_INJ_US_DELAY;
    MG_HAL_ETC_GROUP.reverse_time_ms = THERMAL_120_ETC_MS_REVERSE;
    MG_HAL_ETC_GROUP.freq = THERMAL_120_ETC_FREQ;
    MG_HAL_ETC_GROUP.duty = 25; 
}

void mg_HAL_Output_Cycling_Validation_Init(void)
{
    MG_SIU_GPIO_PWM_Initialize_Device_Override();
    MG_HAL_DISCRETE_OUT_GROUP[19].type = DISCRETE;
}

void mg_HAL_Output_Cycling_Validation_Uninit(void)
{
    
}

void mg_HAL_Output_Cycling_Validation_Config(void)
{
    MG_HAL_DISCRETE_OUT_GROUP[0].on_time_us = FREQ_0P5_50_ON;             /* MPR */
    MG_HAL_DISCRETE_OUT_GROUP[0].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[1].on_time_us = FREQ_0P5_50_ON;             /* FPR */
    MG_HAL_DISCRETE_OUT_GROUP[1].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[2].on_time_us = FREQ_0P5_50_ON;             /* AC Clutch */
    MG_HAL_DISCRETE_OUT_GROUP[2].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[3].on_time_us = FREQ_0P5_50_ON;             /* FAN2 */
    MG_HAL_DISCRETE_OUT_GROUP[3].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[4].frequency = 500;                                   /* 500Hz Fuel Consumption */
    MG_HAL_DISCRETE_OUT_GROUP[4].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[5].on_time_us = FREQ_0P5_50_ON;               /* SAIC */
    MG_HAL_DISCRETE_OUT_GROUP[5].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[6].on_time_us = FREQ_0P5_50_ON;               /* FAN1 / PWM FAN */
    MG_HAL_DISCRETE_OUT_GROUP[6].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[7].frequency = 16;                                    /* 16Hz CCP */
    MG_HAL_DISCRETE_OUT_GROUP[7].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[8].frequency = 250;                                   /* 128Hz VVT1 */
    MG_HAL_DISCRETE_OUT_GROUP[8].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[9].frequency = 250;                                   /* 128Hz VVT2 */
    MG_HAL_DISCRETE_OUT_GROUP[9].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[10].on_time_us = FREQ_0P5_50_ON;             /* Inter Coolant Fan / VGIS1 */
    MG_HAL_DISCRETE_OUT_GROUP[10].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[11].on_time_us = FREQ_0P5_50_ON;             /* Turbo BPAR / VGIS2 */
    MG_HAL_DISCRETE_OUT_GROUP[11].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[12].on_time_us = FREQ_16_50_ON;             /* 16Hz O2A Heater */
    MG_HAL_DISCRETE_OUT_GROUP[12].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[12].frequency = 16;                                    /* 16Hz O2A Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[12].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[13].on_time_us = FREQ_16_50_ON;             /* 16Hz O2B Heater */
    MG_HAL_DISCRETE_OUT_GROUP[13].off_time_us = FREQ_16_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[13].frequency = 16;                                    /* 16Hz O2B Heater */
//    MG_HAL_DISCRETE_OUT_GROUP[13].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[14].frequency = 250;                                /* 250Hz Water Pump Control  */
    MG_HAL_DISCRETE_OUT_GROUP[14].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[15].frequency = 32;                                  /* 32Hz Turbo AWG/Turbo VGT */
    MG_HAL_DISCRETE_OUT_GROUP[15].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[16].on_time_us = FREQ_0P5_50_ON;            /* MIL / CEL */
    MG_HAL_DISCRETE_OUT_GROUP[16].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[17].on_time_us = FREQ_0P5_50_ON;            /* SVS */
    MG_HAL_DISCRETE_OUT_GROUP[17].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[18].on_time_us = FREQ_100_50_ON;        /* 100Hz Coolant Guage / Thermal Control */
    MG_HAL_DISCRETE_OUT_GROUP[18].off_time_us = FREQ_100_50_OFF;
//    MG_HAL_DISCRETE_OUT_GROUP[18].frequency = 100;                               /* 100Hz Coolant Guage / Thermal Control */
//    MG_HAL_DISCRETE_OUT_GROUP[18].duty = 50;
//    MG_HAL_DISCRETE_OUT_GROUP[19].frequency = 350;                               /* 350Hz SAIC PWM */
//    MG_HAL_DISCRETE_OUT_GROUP[19].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[19].on_time_us = FREQ_0P5_50_ON;            /* 0.5Hz SAIC PWM */
    MG_HAL_DISCRETE_OUT_GROUP[19].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_DISCRETE_OUT_GROUP[20].frequency = 50;                               /* 50Hz TACH */
    MG_HAL_DISCRETE_OUT_GROUP[20].duty = 50;
    MG_HAL_DISCRETE_OUT_GROUP[21].on_time_us = FREQ_0P5_50_ON;           /* Cruise Indicator */
    MG_HAL_DISCRETE_OUT_GROUP[21].off_time_us = FREQ_0P5_50_OFF;
    MG_HAL_EST_GROUP.on_time_us = VALIDATION_EST_US_ON;                     /* On time 3.4ms, 50Hz for 2IGBT or 25Hz for 4IGBT */
    MG_HAL_EST_GROUP.delay_time_us = VALIDATION_EST_US_DELAY;
    MG_HAL_INJ_GROUP.on_time_us = VALIDATION_INJ_US_ON;                       /* 25Hz, 25% duty*/
    MG_HAL_INJ_GROUP.delay_time_us = VALIDATION_INJ_US_DELAY;
    MG_HAL_ETC_GROUP.reverse_time_ms = VALIDATION_ETC_MS_REVERSE;
    MG_HAL_ETC_GROUP.freq = VALIDATION_ETC_FREQ;
    MG_HAL_ETC_GROUP.duty = 95; 
}
#endif