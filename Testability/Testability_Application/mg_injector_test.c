//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_injector_test.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:           %
//
// %version:         1 %
//
//=============================================================================
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
#include "mg_hal_inj.h"
#include "mg_hal_timer.h"

/*=============================================================================
 * mg_pfi_test
 * @func  perfrom injector test
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_injector_test(void)
{
    uint8_t duty;
    uint16_t freq;

    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

    duty = MG_MAILBOX_IN(parameter[0]);
    freq = MG_MAILBOX_IN(parameter[1])*256 + MG_MAILBOX_IN(parameter[2]);

    mg_HAL_Discrete_Set_FSE(true);
    
    // duty cycly can't exceed 25%
    if ((duty!=0)&&(duty<=25)&&(freq!=0)) 
    {
        MG_HAL_INJ_GROUP.on_time_us = (SYSTEM_FREQUENCY_HZ / freq) * duty / 100;
        MG_HAL_INJ_GROUP.delay_time_us = (SYSTEM_FREQUENCY_HZ / freq) / 4 - MG_HAL_INJ_GROUP.on_time_us;
        mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_1,true);
        MG_HAL_INJ_GROUP.current_state = true;
        MG_HAL_INJ_GROUP.current_inj = MG_INJ_IDX_1;

        do
        {
            mg_HAL_Injector_Discrete_Cycling();
            duty = MG_MAILBOX_IN(parameter[0]);
            freq = MG_MAILBOX_IN(parameter[1])*256 + MG_MAILBOX_IN(parameter[2]);
            mg_HAL_Service_WatchDog();
        } while((duty!=0)&&(freq!=0));
        
        /* Shut down all INJ output after finish this test */
        mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_1,false);
        mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_2,false);
        mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_3,false);
        mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_4,false);
    }


}

