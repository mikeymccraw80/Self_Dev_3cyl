//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_output_cycling_validation.c %
//
// created_by:       tzwfxv %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:             %
//
// %version:         5 %
//
//=============================================================================
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
#include "mg_hal_analog.h"
#include "mg_hal_PWM.h"
#include "mg_hal_est.h"
#include "mg_hal_etc.h"
#include "mg_hal_inj.h"
#include "mg_hal_fault.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/
static uint8_t mg_VSEP_Fault_count[30];
static bool mg_EST_Enabled = true;
static bool mg_INJ_Enabled = true;
/*=============================================================================
 * mg_output_cycling_validation
 * @func  perform output cycling
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_output_cycling_validation(void)
{
    uint8_t idx;
    uint8_t VSEP_out_index;

    mg_HAL_Output_Cycling_Validation_Init();
    
    mg_HAL_Output_Cycling_Validation_Config();

    mg_HAL_Service_WatchDog();

    if (mg_HAL_Get_EST_Sequential_Mode())
    {
        mg_HAL_EST_Set_Sequential_Mode(true);
    }
    else
    {
        mg_HAL_EST_Set_Sequential_Mode(false);
    }
    mg_HAL_EST_Init(MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME, MG_HAL_EST_GROUP.on_time_us,
        MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.delay_time_us, 0);
    mg_HAL_ETC_Discrete_Enable(true);
    mg_HAL_ETC_Discrete_Direction(false);
    mg_HAL_ETC_Set_Freq_And_Duty();
    for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
    {
        if (PWM == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
        {
            mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty_Immediate(idx);
        }
        else if (PWM_REVERSE == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
        {
            mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty(idx);
        }
        else
        {
            /* do in while */
        }
        mg_HAL_Service_WatchDog();
    }

    mg_HAL_Discrete_Set_FSE(true);
    mg_HAL_Discrete_Set_GEN_ENABLE(true);
    
    mg_HAL_EST_Start();

    for (idx = 0; idx < MG_COMPLEXIO_CHANNEL_MAX; idx++)
    {
        mg_VSEP_Fault_count[idx] = 0;
    }
    // stay in cycling until a reset occurs or IGN OFF
    while(1)
    {
        if (mg_EST_Enabled)
        {
            mg_HAL_EST_cycling();
        }
        if (mg_INJ_Enabled)
        {
            mg_HAL_Injector_Discrete_Cycling();
        }
        mg_HAL_PWM_Discrete_Out_Cycling();
        mg_HAL_ETC_Discrete_Cycling_Validation();

        mg_HAL_ComplexIO_Fault_Read();
        if (idx >= (MG_COMPLEXIO_CHANNEL_MAX - 1))
        {
            idx = 0;
        }
        else
        {
            idx++;
        }
        if (mg_HAL_ComplexIO_Fault_Get(idx) == MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY)
        {
            if (mg_VSEP_Fault_count[idx] <= 16)
            {
                mg_VSEP_Fault_count[idx] += 1;
            }
            else
            {
                if (idx < 4)
                {
                    MG_HAL_EST_GROUP.on_time_us = 0;
                    MG_HAL_EST_GROUP.delay_time_us = 1000;
                    mg_HAL_EST_Shutdown();
                    mg_EST_Enabled = false;
                }
                else if ((idx >= 8) && (idx < 12))
                {
                    MG_HAL_INJ_GROUP.on_time_us = 0;
                    MG_HAL_INJ_GROUP.delay_time_us = 1000;
                    mg_HAL_Injector_Set_Group_Value((idx - 8), false);
                    mg_INJ_Enabled = false;
                }
                else
                {
                    if (idx < 4)
                    {
                        /* PCH5-8 */
                        VSEP_out_index = idx - 4;
                    }
                    else if (idx >= 12)
                    {
                        /* PCH13-30 */
                        VSEP_out_index = idx - (12 - 4);
                    }
                    else
                    {
                        /* do nothing */
                    }
                    if (DISCRETE == MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].type)
                    {
                        MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].on_time_us = 0;
                        MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].off_time_us = 1000;
                    }
                    else
                    {
                        if (PWM == MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].type)
                        {
                            MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].duty = 0;
                        }
                        else
                        {
                            MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].duty = 100;
                        }
                    }
                    if (DISCRETE == MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].type)
                    {
                        mg_HAL_Discrete_Set_Discrete_Out_Group_Value(VSEP_out_index, false);
                    }
                    else
                    {
                        if (PWM == MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].type)
                        {
                            mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty_Immediate(VSEP_out_index);
                        }
                        else if (PWM_REVERSE == MG_HAL_DISCRETE_OUT_GROUP[VSEP_out_index].type)
                        {
                            mg_HAL_PWM_Set_Discrete_Out_Group_Frequency_And_Duty(VSEP_out_index);
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                }
            }
        }
        
        mg_HAL_Service_WatchDog();
    }
    mg_HAL_Output_Cycling_Validation_Uninit();
}
