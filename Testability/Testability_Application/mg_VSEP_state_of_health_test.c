//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_VSEP_state_of_health_test.c %
//
// created_by:       tzwfxv %
//
// date_created:      %
//
// %derived_by:       tzwfxv %
//
// %date_created:	Tue Oct 23 19:46:55 2012 %
//
// %version:         2 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_soh.h"
#include "mg_hal_discrete.h"
#include "mg_hal_inj.h"
#include "mg_hal_etc.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_VSEP_state_of_health_test(void)
 *
 * Description: This test do response or not response after get a challege as contorl.
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_VSEP_state_of_health_test(void)
{
    uint8_t state_of_health;
    uint32_t challenge_temp;
    uint32_t response_temp;
    uint8_t exe_state = 0xFF;
    uint8_t dir;

    if (mg_HAL_Get_SOH_Test_Flag()== 0)
    {
        MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
        if (((MG_MAILBOX_IN(parameter[0]) & 0x03) != 0) && ((MG_MAILBOX_IN(parameter[0]) & 0xFC) == 0))
        {
            /* Set SOH test flag & reset for initialize to Armed state */
            mg_HAL_Set_SOH_Test_Flag(8 |MG_MAILBOX_IN(parameter[0]));
            mg_HAL_SWT_Enable_WatchDog( true );
        }
        else
        {
            /* Without test options, don't execute */
            MG_MAILBOX_OUT(parameter[1]) = 0xFF;
        }
    }
    else
    {
        MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
        state_of_health = MG_MAILBOX_IN(parameter[0]);
        
        mg_HAL_Discrete_Set_FSE(true);
        mg_HAL_Injector_Set_Group_Value(0, true);
        mg_HAL_ETC_Discrete_Enable(true);
        dir = true;
        MG_HAL_ETC_GROUP.duty = 32;
        MG_HAL_ETC_GROUP.freq = 0xFA0;
        MG_HAL_ETC_GROUP.reverse_time_ms = (1 * SYSTEM_FREQUENCY_HZ);
        MG_HAL_ETC_GROUP.timer.start_time = mg_HAL_Timer_Get_STM_In_CNT();
        mg_HAL_ETC_Set_Freq_And_Duty();
        while ((state_of_health & 0x03) != 0x00)
        {
            state_of_health = MG_MAILBOX_IN(parameter[0]);
            MG_HAL_ETC_GROUP.timer.current_time = mg_HAL_Timer_Get_STM_In_CNT();
            if (MG_HAL_ETC_GROUP.reverse_time_ms < mg_HAL_Timer_Get_STM_Diff_In_CNT(MG_HAL_ETC_GROUP.timer.current_time, MG_HAL_ETC_GROUP.timer.start_time))
            {
                dir = !dir;
                mg_HAL_ETC_Discrete_Direction(dir);
                MG_HAL_ETC_GROUP.timer.start_time = MG_HAL_ETC_GROUP.timer.current_time;
            }
            if ((state_of_health & 0x03) == 0x01)
            {
                challenge_temp = mg_HAL_SOH_Get_Challenge();
                response_temp = mg_HAL_SOH_Calculate_Response( challenge_temp );
                response_temp ^= 0xFFFFFFFF;
                mg_HAL_SOH_Set_Response(response_temp);
                exe_state = 0;
            }
            else if ((state_of_health & 0x03) == 0x02)
            {
                exe_state = 0;
            }
            else if ((state_of_health & 0x03) == 0x03)
            {
                challenge_temp = mg_HAL_SOH_Get_Challenge();
                response_temp = mg_HAL_SOH_Calculate_Response( challenge_temp );
                mg_HAL_SOH_Set_Response(response_temp);
                exe_state = 0;
            }
            else
            {
            
            }
            mg_HAL_Service_WatchDog();
        }
        
        MG_MAILBOX_OUT(parameter[1]) = exe_state;

        /* Clear SOH test flag & reset for other test */
        mg_HAL_Set_SOH_Test_Flag(0);
        mg_HAL_SWT_Enable_WatchDog( true );            
    }
}


