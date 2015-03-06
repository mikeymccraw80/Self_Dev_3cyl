//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_est_test.c %
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
#include "mg_hal_est.h"
#include "mg_hal_timer.h"

#define MCD5412_TIME_UNIT_ON_US     4

/*=============================================================================
 * mg_est_test
 * @func  perform est test
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_est_test(void)
{
    uint16_t period;
    uint16_t duration;

    /* variable for test */
    uint32_t boundary_angle;
    uint32_t dfpw;
    uint8_t index;
    uint32_t start_timer,current_timer;

    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

    period = MG_MAILBOX_IN(parameter[1])*256 + MG_MAILBOX_IN(parameter[2]);
    duration = MG_MAILBOX_IN(parameter[3])*256 + MG_MAILBOX_IN(parameter[4]);

    /* EST using MCD5412*/
    if (MG_MAILBOX_IN(parameter[0]) == 0x00) 
    {
        mg_HAL_EST_Set_Sequential_Mode(true);
        if (period > (4 * duration))
        {
            MG_HAL_EST_GROUP.on_time_us = (duration * (TPU_A_TCR1_CLOCK_FREQ / 1000000));//MCD5412_TIME_UNIT_ON_US;
            MG_HAL_EST_GROUP.delay_time_us = (period/4 - duration) * (TPU_A_TCR1_CLOCK_FREQ / 1000000);//MCD5412_TIME_UNIT_ON_US;
        }
        else
        {
            MG_HAL_EST_GROUP.on_time_us = 2500 * (TPU_A_TCR1_CLOCK_FREQ / 1000000);//MCD5412_TIME_UNIT_ON_US;
            MG_HAL_EST_GROUP.delay_time_us = 2500 * (TPU_A_TCR1_CLOCK_FREQ / 1000000);//MCD5412_TIME_UNIT_ON_US;
        }
    }
    else 
    {
        mg_HAL_EST_Set_Sequential_Mode(false);
        if (period > (2 * duration))
        {
            MG_HAL_EST_GROUP.on_time_us = (duration * (TPU_A_TCR1_CLOCK_FREQ / 1000000));//MCD5412_TIME_UNIT_ON_US;
            MG_HAL_EST_GROUP.delay_time_us = (period/2 - duration) * (TPU_A_TCR1_CLOCK_FREQ / 1000000);//MCD5412_TIME_UNIT_ON_US;
        }
        else
        {
            MG_HAL_EST_GROUP.on_time_us = 2500 * (TPU_A_TCR1_CLOCK_FREQ / 1000000);//MCD5412_TIME_UNIT_ON_US;
            MG_HAL_EST_GROUP.delay_time_us = 2500 * (TPU_A_TCR1_CLOCK_FREQ / 1000000);//MCD5412_TIME_UNIT_ON_US;
        }
    }
    mg_HAL_EST_Init(MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME, MG_HAL_EST_GROUP.on_time_us,
        MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.delay_time_us, 0);
    mg_HAL_EST_Start();
    do
    {
        mg_HAL_EST_cycling();
        mg_HAL_Service_WatchDog();
        period = MG_MAILBOX_IN(parameter[1])*256 + MG_MAILBOX_IN(parameter[2]);
    } while(period != 0);
    mg_HAL_EST_Shutdown();
}
