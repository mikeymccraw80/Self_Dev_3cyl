//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_output_cycling.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:            %
//
// %version:         5 %
//
//=============================================================================
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
#include "mg_hal_PWM.h"
#include "mg_hal_est.h"
#include "mg_hal_etc.h"
#include "mg_hal_inj.h"
#include "mg_hal_fault.h"
#include "mg_hal_timer.h"

#define ETC_4ESTIGBT    0x00
#define ETC_2ESTIGBT    0x01
#define IAC_4ESTIGBT    0x02
#define IAC_2ESTIGBT    0x03
#define EXIT_CYCLING    0x77


/*=============================================================================
 * mg_output_cycling
 * @func  perform output cycling
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_output_cycling(void)
{
    uint8_t idx;
    uint32_t start_timer;
    uint32_t current_timer;
    uint32_t time_diff;
    uint8_t data_byte;
//    uint8_t PCH[16];

    mg_HAL_Output_Cycling_Init();
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    data_byte = MG_MAILBOX_IN(parameter[0]);
    /* output configuration */
    if ((ETC_4ESTIGBT == data_byte) || (ETC_2ESTIGBT == data_byte))
    {
        mg_HAL_Output_Cycling_Config();
        /* run output cycling */
        switch (data_byte)
        {
            case ETC_4ESTIGBT:
                mg_HAL_EST_Set_Sequential_Mode(true);
                break;
            case ETC_2ESTIGBT:
                mg_HAL_EST_Set_Sequential_Mode(false);
                break;
            default:
                break;
        }
        mg_HAL_EST_Init(MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME,  MG_HAL_EST_GROUP.on_time_us,
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
        start_timer = mg_HAL_Timer_Get_STM_In_CNT();

        mg_HAL_Discrete_Set_FSE(true);
        mg_HAL_Discrete_Set_GEN_ENABLE(true);
        
        mg_HAL_EST_Start();
        
        while (data_byte != 0x77)
        {
            mg_HAL_EST_cycling();
            mg_HAL_Injector_Discrete_Cycling();
            mg_HAL_PWM_Discrete_Out_Cycling();
            mg_HAL_ETC_Discrete_Cycling_Validation();

            current_timer = mg_HAL_Timer_Get_STM_In_CNT();
            time_diff = mg_HAL_Timer_Get_STM_Diff_In_CNT(current_timer, start_timer);
            if (time_diff > DURING_10_S)
            {
                start_timer = mg_HAL_Timer_Get_STM_In_CNT();
                mg_HAL_Output_Cycling_Diagnostic((uint8_t*)(&MG_MAILBOX_OUT(parameter[1])));
            }
            
            data_byte = MG_MAILBOX_IN(parameter[0]);
            
            mg_HAL_Service_WatchDog();
        }
        /* stop all PWM output */
        for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
        {
            mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, false);
            mg_HAL_Service_WatchDog();
        }
        mg_HAL_ETC_Discrete_Enable(false);
    }
    mg_HAL_Output_Cycling_EMC_Uninit();
}
