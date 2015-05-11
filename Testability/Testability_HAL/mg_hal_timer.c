#include "mg_hal_config.h"
#include "mg_hal.h"
// #include "io_pulse.h"
#include "io_conversion.h"
// #include "io_scale.h"
#include "dd_stm_interface.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define MG_STM_CNT_REG                     (uint32_t volatile  *)(0xFFF3C004)
#define MG_STM_OVERFLOW_VALUE              (0xFFFFFFFF)
#define MG_STM_PRESCALE                    80

/*=============================================================================
 * mg_HAL_Timer_Get_STM_In_ms
 * @func  get system timer value
 * @parm  none
 * @rdesc current system timer value, unit: ms 
 *===========================================================================*/
uint32_t mg_HAL_Timer_Get_STM_In_ms(void)
{
    /* us -> ms */
    return (time_get(0)/1000);
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

    time_diff = (uint32_t)(current_time - start_time)/1000;

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
   return time_get(0);
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

    time_diff = (uint32_t)(current_time - start_time);

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
   // return *MG_STM_CNT_REG;
   return time_get(0);
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
 * @rdesc time diff, unit: 1 us 
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
    time_udelay(wait_time);
}

/*=============================================================================
 * mg_HAL_Time_Hard_Delay_us
 * @func  time delay
 * @parm  microsecond
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Time_Hard_Delay_ms(uint32_t wait_time, void (*callback)(void))
{
    uint32_t deadline = time_get(0) + wait_time;
    while (time_left(deadline) > 0) {
        if (NULL != callback) {
            callback();
        }
    }
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
// uint32_t mg_HAL_Timer_Get_MPTAC_Value(HIODEVICE in_device)
// {
//     const IO_Mptac_T *mptac = (IO_Mptac_T*)in_device;
//     return mptac->P->Timer.Get_Value(mptac->Configuration);
// }
