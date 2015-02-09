//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_discrete_out_test.c %
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
#include "mg_hal_config.h"
#include "mg_common.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
#include "mg_hal_PWM.h"
#include "mg_hal_timer.h"


/*=============================================================================
 * mg_discrete_out_test
 * @func  perform discrete out test
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_discrete_out_test(void)
{
    uint8_t idx;
    uint8_t channel[4];
    uint8_t duty;
    uint16_t freq;

    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

    duty = MG_MAILBOX_IN(parameter[0]);
    freq = MG_MAILBOX_IN(parameter[1])*256 + MG_MAILBOX_IN(parameter[2]);

    channel[0] = MG_MAILBOX_IN(parameter[3]);
    channel[1] = MG_MAILBOX_IN(parameter[4]);
    channel[2] = MG_MAILBOX_IN(parameter[5]);
    channel[3] = MG_MAILBOX_IN(parameter[6]);

    MG_Bitmap_Init(channel);

    for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++) 
    {
        MG_HAL_DISCRETE_OUT_GROUP[idx].on_time_us = 0;
        MG_HAL_DISCRETE_OUT_GROUP[idx].off_time_us = 0;

        if(MG_Bitmap_Test_Value_In_Map(idx))
        {
            if (DISCRETE == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
            {
                MG_HAL_DISCRETE_OUT_GROUP[idx].on_time_us = duty * (SYSTEM_FREQUENCY_HZ / freq) / 100;
                MG_HAL_DISCRETE_OUT_GROUP[idx].off_time_us = (100 - duty) * (SYSTEM_FREQUENCY_HZ / freq) / 100;
            }
            else
            {
                MG_HAL_DISCRETE_OUT_GROUP[idx].frequency = freq;
                MG_HAL_DISCRETE_OUT_GROUP[idx].duty = duty;
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
            }
        }
        mg_HAL_Service_WatchDog();
    }
   


    while((duty!=0)&&(freq!=0))
    {
        duty = MG_MAILBOX_IN(parameter[0]);
        freq = MG_MAILBOX_IN(parameter[1])*256 + MG_MAILBOX_IN(parameter[2]);
        if ((duty != MG_HAL_DISCRETE_OUT_GROUP[4].duty) || (freq != MG_HAL_DISCRETE_OUT_GROUP[4].frequency))
        {
            for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++) 
            {
                if(MG_Bitmap_Test_Value_In_Map(idx))
                {
                    if (DISCRETE == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
                    {
                        MG_HAL_DISCRETE_OUT_GROUP[idx].on_time_us = duty * (SYSTEM_FREQUENCY_HZ / freq) / 100;
                        MG_HAL_DISCRETE_OUT_GROUP[idx].off_time_us = (100 - duty) * (SYSTEM_FREQUENCY_HZ / freq) / 100;
                    }
                    else
                    {
                        MG_HAL_DISCRETE_OUT_GROUP[idx].frequency = freq;
                        MG_HAL_DISCRETE_OUT_GROUP[idx].duty = duty;
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
                    }
                }
                mg_HAL_Service_WatchDog();
            }
        }
        mg_HAL_PWM_Discrete_Out_Cycling();
        mg_HAL_Service_WatchDog();
   }
    
   /* Shut down all Discrete output after finish this test */
   for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
   {
      mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, false);
   }
   mg_HAL_Service_WatchDog();
}
