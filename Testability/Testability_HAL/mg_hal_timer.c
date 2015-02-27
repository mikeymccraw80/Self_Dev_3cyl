#if 0
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "io_pulse.h"
#include "io_conversion.h"
#include "io_scale.h"
#include "dd_stm.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define MG_STM_CNT_REG                     (uint32_t volatile  *)(0xFFF3C004)
#define MG_STM_OVERFLOW_VALUE      (0xFFFFFFFF)
#define MG_STM_PRESCALE                                  80

/*=============================================================================
 * mg_HAL_Timer_Get_STM_In_ms
 * @func  get system timer value
 * @parm  none
 * @rdesc current system timer value, unit: ms 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_In_ms(void)
{
   return IO_PULSE_Timer_Get_Value( &MTSA_SYSTEM_TIMER, 0, MILLISECOND_RESOLUTION );
}

/*=============================================================================
 * mg_HAL_Timer_Get_STM_Diff_In_ms
 * @func  Get system timer diff 
 * @parm  current time/start time
 * @rdesc time diff, unit: ms 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_Diff_In_ms(uint32_t current_time,uint32_t start_time)
{
    uint32_t time_diff;
    if (current_time >= start_time)
    {
       time_diff = current_time - start_time;
    }
    else 
    {
       time_diff = current_time + (IO_Convert_Count_To_Time(MG_STM_OVERFLOW_VALUE,SYSTEM_FREQUENCY_HZ,0,MILLISECOND_RESOLUTION) - start_time);
    }
    return time_diff;
}

/*=============================================================================
 * mg_HAL_Timer_Get_STM_In_us
 * @func  get system timer value
 * @parm  none
 * @rdesc current system timer value, unit: us 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_In_us(void)
{
   return IO_PULSE_Timer_Get_Value( &MTSA_SYSTEM_TIMER, 0, MICROSECOND_RESOLUTION );
}

/*=============================================================================
 * mg_HAL_Timer_Get_STM_Diff_In_us
 * @func  Get system timer diff 
 * @parm  current time/start time
 * @rdesc time diff, unit: us 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_Diff_In_us(uint32_t current_time,uint32_t start_time)
{
    uint32_t time_diff;
    if (current_time >= start_time)
    {
       time_diff = current_time - start_time;
    }
    else 
    {
       time_diff = current_time + (IO_Convert_Count_To_Time(MG_STM_OVERFLOW_VALUE,SYSTEM_FREQUENCY_HZ,0,MICROSECOND_RESOLUTION) - start_time);
    }
    return time_diff;
}

/*=============================================================================
 * mg_HAL_Timer_Get_STM_In_CNT
 * @func  get system timer value
 * @parm  none
 * @rdesc current system timer value, unit: us 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_In_CNT(void)
{
   return *MG_STM_CNT_REG;
}

/*=============================================================================
 * mg_HAL_Timer_Get_STM_Diff_In_CNT
 * @func  Get system timer diff 
 * @parm  current time count/start time count
 * @rdesc time diff, unit: 1/80 us 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_Diff_In_CNT(uint32_t current_time,uint32_t start_time)
{
    uint32_t time_diff;
    if (current_time >= start_time)
    {
       time_diff = current_time - start_time;
    }
    else 
    {
       time_diff = current_time + (MG_STM_OVERFLOW_VALUE - start_time);
    }
    return time_diff;
}

/*=============================================================================
 * mg_hal_get_STM_diff_in_CNT
 * @func  Get system timer diff 
 * @parm  current time count/start time count
 * @rdesc time diff, unit: 1/80 us 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_Diff_In_us_By_CNT(uint32_t current_time,uint32_t start_time)
{
    uint32_t time_diff;
    if (current_time >= start_time)
    {
       time_diff = current_time - start_time;
    }
    else 
    {
       time_diff = current_time + (MG_STM_OVERFLOW_VALUE - start_time);
    }
    time_diff /= (SYSTEM_FREQUENCY_HZ / 1000000);
    return time_diff;
}

/*=============================================================================
 * mg_HAL_Time_Hard_Delay_us
 * @func  time delay
 * @parm  microsecond
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Time_Hard_Delay_us(uint32_t wait_time)
{
    uint32_t start_timer;
    uint32_t current_timer;
    uint32_t diff;
    start_timer = mg_HAL_Timer_Get_STM_In_us();
    do {
        current_timer = mg_HAL_Timer_Get_STM_In_us();
        diff = mg_HAL_Timer_Get_STM_Diff_In_us(current_timer, start_timer);
        mg_HAL_Service_WatchDog();
    } while (diff < wait_time);
}

/*=============================================================================
 * mg_HAL_Time_Hard_Delay_us
 * @func  time delay
 * @parm  microsecond
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Time_Hard_Delay_ms(uint32_t wait_time, void (*callback)(void))
{
    uint32_t start_timer;
    uint32_t current_timer;
    uint32_t diff;
    start_timer = mg_HAL_Timer_Get_STM_In_ms();
    do {
        current_timer = mg_HAL_Timer_Get_STM_In_ms();
        diff = mg_HAL_Timer_Get_STM_Diff_In_ms(current_timer, start_timer);
        if (NULL != callback)
        {
            callback();
        }
    } while (diff < wait_time);
}

/*=============================================================================
 * mg_HAL_Timer_Set_STM_Enable
 * @func  set STM timer enable state
 * @parm  enable state
 * @rdesc  none
 *===========================================================================*/
void mg_HAL_Timer_Set_STM_Enable(bool state)
{
    STM_Set_Timer_Enable(state);
}

/*=============================================================================
 * mg_HAL_Timer_Get_MPTAC_Value
 * @func  get MPTAC timer value
 * @parm  in_device
 * @rdesc  none
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_MPTAC_Value(HIODEVICE in_device)
{
    const IO_Mptac_T *mptac = (IO_Mptac_T*)in_device;
    return mptac->P->Timer.Get_Value(mptac->Configuration);
}

#endif