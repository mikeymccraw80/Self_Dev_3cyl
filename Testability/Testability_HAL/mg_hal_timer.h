#ifndef MG_HAL_TIMER_H
#define MG_HAL_TIMER_H

#include "io_config_tpu.h"

#define FREQ_0P5_50_ON          (1 * SYSTEM_FREQUENCY_HZ)         //  80000000 = 1000000 us * 80(prescale)
#define FREQ_0P5_50_OFF        (1 * SYSTEM_FREQUENCY_HZ)           //  80000000 = 1000000 us * 80(prescale)
#define FREQ_0P5_80_ON          (1600 * (SYSTEM_FREQUENCY_HZ / 1000))         //  128000000 = 1600000 us * 80(prescale)
#define FREQ_0P5_20_OFF        (400 * (SYSTEM_FREQUENCY_HZ / 1000))           //  32000000 = 400000 us * 80(prescale)
#define FREQ_1_50_ON              (500 * (SYSTEM_FREQUENCY_HZ / 1000))         //  32000000 = 500000 us * 64(prescale)
#define FREQ_1_50_OFF            (500 * (SYSTEM_FREQUENCY_HZ / 1000))         //  32000000 = 500000 us * 64(prescale)
#define FREQ_4_80_ON              (200 * (SYSTEM_FREQUENCY_HZ / 1000))         //  16000000 = 200000 us * 80(prescale)
#define FREQ_4_20_OFF            (50 * (SYSTEM_FREQUENCY_HZ / 1000))           //  4000000 = 50000 us * 80(prescale)
#define FREQ_8_50_ON              (62500 * (SYSTEM_FREQUENCY_HZ / 1000000))             //  4000000 = 125000us * 64(prescale)
#define FREQ_8_50_OFF            (62500 * (SYSTEM_FREQUENCY_HZ / 1000000))             //  4000000 = 125000us * 64(prescale)
#define FREQ_16_50_ON            (31250 * (SYSTEM_FREQUENCY_HZ / 1000000))            //  2500000 = 31250 us * 80(prescale)
#define FREQ_16_50_OFF          (31250 * (SYSTEM_FREQUENCY_HZ / 1000000))            //  2500000 = 31250 us * 80(prescale)
#define FREQ_16_25_ON            (15625 * (SYSTEM_FREQUENCY_HZ / 1000000))            //  2500000 = 31250 us * 80(prescale)
#define FREQ_16_25_OFF          (46875 * (SYSTEM_FREQUENCY_HZ / 1000000))            //  2500000 = 31250 us * 80(prescale)
#define FREQ_32_50_ON            (15625 * (SYSTEM_FREQUENCY_HZ / 1000000))            //  1250000 = 15625 us * 80(prescale)
#define FREQ_32_50_OFF          (15625 * (SYSTEM_FREQUENCY_HZ / 1000000))            //  1250000 = 15625 us * 80(prescale)
#define FREQ_50_50_ON            (10 * (SYSTEM_FREQUENCY_HZ / 1000))            //   800000 = 10000 us * 80(prescale)
#define FREQ_50_50_OFF          (10 * (SYSTEM_FREQUENCY_HZ / 1000))            //   800000 = 10000 us * 80(prescale)
#define FREQ_100_50_ON          (5 * (SYSTEM_FREQUENCY_HZ / 1000))             //   400000 = 5000 us * 80(prescale)
#define FREQ_100_50_OFF        (5 * (SYSTEM_FREQUENCY_HZ / 1000))             //   400000 = 5000 us * 80(prescale)
#define FREQ_100_25_ON          (2500 * (SYSTEM_FREQUENCY_HZ / 1000000))             //   400000 = 5000 us * 80(prescale)
#define FREQ_100_25_OFF        (7500 * (SYSTEM_FREQUENCY_HZ / 1000000))             //   400000 = 5000 us * 80(prescale)
#define FREQ_128_50_ON          (3906.25 * (SYSTEM_FREQUENCY_HZ / 1000000))             //   312500 = 3906.25 us * 80(prescale)
#define FREQ_128_50_OFF        (3906.25 * (SYSTEM_FREQUENCY_HZ / 1000000))             //   312500 = 3906.25 us * 80(prescale)
#define FREQ_500_50_ON          (0.75 * (1 * (SYSTEM_FREQUENCY_HZ / 1000)))               //80000 * 75% adjust for freq error             80000 = 1000 us * 80(prescale)
#define FREQ_500_50_OFF        (0.75 * (1 * (SYSTEM_FREQUENCY_HZ / 1000)))                //80000 * 75% adjust for freq error             80000 = 1000 us * 80(prescale)
#define FREQ_10K_50_ON          (50 * (SYSTEM_FREQUENCY_HZ / 1000000))                //    4000 = 50 us * 80(prescale)
#define FREQ_10K_50_OFF        (50 * (SYSTEM_FREQUENCY_HZ / 1000000))                //    4000 = 50 us * 80(prescale)

#define CONST_TRUE_ON            (1 * SYSTEM_FREQUENCY_HZ)
#define CONST_TRUE_OFF          (0 * SYSTEM_FREQUENCY_HZ)
#define CONST_FALSE_ON          (0 * SYSTEM_FREQUENCY_HZ)
#define CONST_FALSE_OFF        (1 * SYSTEM_FREQUENCY_HZ)

#define DURING_10_S                 (10 * SYSTEM_FREQUENCY_HZ)

/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/
#if 0
#define STM_CNT_REG                     (uint32_t volatile  *)(0xFFF3C004)
#define STM_OVERFLOW_VALUE      (0xFFFFFFFF)
#define STM_PRESCALE                            (80)
#endif
uint32_t mg_HAL_Timer_Get_STM_In_ms(void);
uint32_t mg_HAL_Timer_Get_STM_Diff_In_ms(uint32_t current_time,uint32_t start_time);
uint32_t mg_HAL_Timer_Get_STM_In_us(void);
uint32_t mg_HAL_Timer_Get_STM_Diff_In_us(uint32_t current_time,uint32_t start_time);
uint32_t mg_HAL_Timer_Get_STM_In_CNT(void);
uint32_t mg_HAL_Timer_Get_STM_Diff_In_CNT(uint32_t current_time,uint32_t start_time);
uint32_t mg_HAL_Timer_Get_STM_Diff_In_us_By_CNT(uint32_t current_time,uint32_t start_time);
void mg_HAL_Time_Hard_Delay_us(uint32_t wait_time);
void mg_HAL_Timer_Set_STM_Enable(bool state);
// uint32_t mg_HAL_Timer_Get_MPTAC_Value( HIODEVICE in_device);

#endif
