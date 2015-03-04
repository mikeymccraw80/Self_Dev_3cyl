#include "mg_config.h"
#include "mg_hal_config.h"
#include "mg_hal_timer.h"
#include "hal_gpio.h"
#include "hal_pulse.h"
#include "dd_mios_interface.h"
// #include "io_pulse.h"
/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/
#define ETC_MS_F_F95              (60 * (SYSTEM_FREQUENCY_HZ / 1000))                    /* 60 ms */
#define ETC_MS_F_F0                (15 * (SYSTEM_FREQUENCY_HZ / 1000))                    /* 15 ms */
#define ETC_MS_B_D95              (45 * (SYSTEM_FREQUENCY_HZ / 1000))                    /* 45 ms */
#define ETC_MS_B_F10              (30 * (SYSTEM_FREQUENCY_HZ / 1000))                    /* 30 ms */

/*=============================================================================
 * mg_HAL_ETC_Set_Freq_And_Duty
 * @func  set the frequency and duty cycle of etc, this function must be called 
 *        before the cycling of ETC
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Set_Freq_And_Duty(void)
{
    MIOS_PWM_Set_Frequency_And_DutyCycle( MG_HAL_ETC_GROUP.io[MG_ETC_PWM], MG_HAL_ETC_GROUP.freq, MG_HAL_ETC_GROUP.duty);
}

/*=============================================================================
 * mg_HAL_ETC_Discrete_Direction
 * @func  change etc direction
 * @parm  direction - true : forward
 *                    false: backward
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Discrete_Direction(bool direction)
{
    if (direction == true) 
    {
#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
        if ((NULL != MG_HAL_ETC_GROUP.io[MG_ETC_FWD]) && (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_REV]))
        {
            IO_DISCRETE_Set_Immediate_State(MG_HAL_ETC_GROUP.io[MG_ETC_FWD],true);
            IO_DISCRETE_Set_Immediate_State(MG_HAL_ETC_GROUP.io[MG_ETC_REV],false);
        }
#endif
#ifdef __MG_L9958_USED
        if (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_DIR])
        {
            SIU_GPIO_DISCRETE_Set_State(MG_HAL_ETC_GROUP.io[MG_ETC_DIR], true);
        }
#endif
    }
    else 
    {
#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
        if ((NULL != MG_HAL_ETC_GROUP.io[MG_ETC_FWD]) && (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_REV]))
        {
            IO_DISCRETE_Set_Immediate_State(MG_HAL_ETC_GROUP.io[MG_ETC_FWD],false);
            IO_DISCRETE_Set_Immediate_State(MG_HAL_ETC_GROUP.io[MG_ETC_REV],true);
        }
#endif
#ifdef __MG_L9958_USED
        if (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_DIR])
        {
            SIU_GPIO_DISCRETE_Set_State(MG_HAL_ETC_GROUP.io[MG_ETC_DIR], false);
        }
#endif
    }
}

/*=============================================================================
 * mg_HAL_ETC_Discrete_Enable
 * @func  enable etc
 * @parm  enable - true : enable etc
 *                 false: disable etc 
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Discrete_Enable(bool enable)
{
    if (enable == true) 
    {
#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
        if (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_DIS])
        {
            IO_DISCRETE_Set_Immediate_State(MG_HAL_ETC_GROUP.io[MG_ETC_DIS],true);
        }
#endif
#ifdef __MG_L9958_USED
        if (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_DIS])
        {
            SIU_GPIO_DISCRETE_Set_State(MG_HAL_ETC_GROUP.io[MG_ETC_DIS],false);
        }
#endif
    }
    else 
    {
#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
        if (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_DIS])
        {
            IO_DISCRETE_Set_Immediate_State(MG_HAL_ETC_GROUP.io[MG_ETC_DIS],false);
        }
#endif
#ifdef __MG_L9958_USED
        if (NULL != MG_HAL_ETC_GROUP.io[MG_ETC_DIS])
        {
            SIU_GPIO_DISCRETE_Set_State(MG_HAL_ETC_GROUP.io[MG_ETC_DIS],true);
        }
#endif
    }
}

#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
/*=============================================================================
 * mg_HAL_ETC_Discrete_Reverse
 * @func  set ETC reverse pin
 * @parm  enable - true : enable etc
 *                 false: disable etc 
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Discrete_Reverse(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_ETCREV, state);
}

/*=============================================================================
 * mg_HAL_ETC_Discrete_Forward
 * @func  set ETC forward pin
 * @parm  enable - true : enable etc
 *                 false: disable etc 
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Discrete_Forward(bool state)
{
    IO_DISCRETE_Set_Immediate_State(&MTSA_D_OUT_ETCFWD, state);
}
#endif

/*=============================================================================
 * mg_HAL_ETC_Discrete_Cycling
 * @func  cycling etc
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Discrete_Cycling(void)
{
   uint32_t time_diff;
   static bool dir = false;

   MG_HAL_ETC_GROUP.timer.current_time = mg_HAL_Timer_Get_STM_In_CNT();

   time_diff = mg_HAL_Timer_Get_STM_Diff_In_CNT(MG_HAL_ETC_GROUP.timer.current_time,MG_HAL_ETC_GROUP.timer.start_time);

   if ((time_diff >= MG_HAL_ETC_GROUP.reverse_time_ms) && (MG_HAL_ETC_GROUP.reverse_time_ms!=0))
   {
      MG_HAL_ETC_GROUP.timer.start_time = MG_HAL_ETC_GROUP.timer.current_time;
      dir = (uint8_t)!dir;
      mg_HAL_ETC_Discrete_Direction(dir);
   }


}

/*=============================================================================
 * mg_HAL_ETC_Discrete_Cycling_Validation
 * @func  cycling etc
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Discrete_Cycling_Validation(void)
{
    uint32_t time_diff;
    static bool dir = false;

    MG_HAL_ETC_GROUP.timer.current_time = mg_HAL_Timer_Get_STM_In_CNT();

    time_diff = mg_HAL_Timer_Get_STM_Diff_In_CNT(MG_HAL_ETC_GROUP.timer.current_time,MG_HAL_ETC_GROUP.timer.start_time);

    if ((time_diff >= MG_HAL_ETC_GROUP.reverse_time_ms) && (MG_HAL_ETC_GROUP.reverse_time_ms!=0))
    {
        MG_HAL_ETC_GROUP.timer.start_time = MG_HAL_ETC_GROUP.timer.current_time;
        dir = (uint8_t)!dir;
        MG_HAL_ETC_GROUP.duty = 95; 
        mg_HAL_ETC_Set_Freq_And_Duty();
        mg_HAL_ETC_Discrete_Direction(dir);
    }
    else
    {
        if (dir == true)
        {
            if (time_diff > (ETC_MS_F_F95 + ETC_MS_F_F0))
            {
                MG_HAL_ETC_GROUP.duty = 40;
                mg_HAL_ETC_Set_Freq_And_Duty();
            }
            else if (time_diff > ETC_MS_F_F95)
            {
                MG_HAL_ETC_GROUP.duty = 0;
                mg_HAL_ETC_Set_Freq_And_Duty();
            }
            else
            {
                /* remain */
            }
        }
        else
        {
            if (time_diff > (ETC_MS_B_D95 + ETC_MS_B_F10))
            {
                MG_HAL_ETC_GROUP.duty = 40;
                mg_HAL_ETC_Set_Freq_And_Duty();
                mg_HAL_ETC_Discrete_Direction(dir);
            }
            else if (time_diff > ETC_MS_B_D95)
            {
                MG_HAL_ETC_GROUP.duty = 10;
                mg_HAL_ETC_Set_Freq_And_Duty();
                mg_HAL_ETC_Discrete_Direction((uint8_t)!dir);
            }
            else
            {
                /* remain */
            }
        }
    }
}

/*=============================================================================
 * mg_HAL_ETC_Discrete_Cycling_120
 * @func  cycling etc
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_ETC_Discrete_Cycling_120(void)
{
    uint32_t time_diff;
    static bool dir = false;

    MG_HAL_ETC_GROUP.timer.current_time = mg_HAL_Timer_Get_STM_In_CNT();

    time_diff = mg_HAL_Timer_Get_STM_Diff_In_CNT(MG_HAL_ETC_GROUP.timer.current_time,MG_HAL_ETC_GROUP.timer.start_time);

    if ((time_diff >= MG_HAL_ETC_GROUP.reverse_time_ms) && (MG_HAL_ETC_GROUP.reverse_time_ms!=0))
    {
        MG_HAL_ETC_GROUP.timer.start_time = MG_HAL_ETC_GROUP.timer.current_time;
        dir = (uint8_t)!dir;
        MG_HAL_ETC_GROUP.duty = 25; 
        mg_HAL_ETC_Set_Freq_And_Duty();
        mg_HAL_ETC_Discrete_Direction(dir);
    }
}
