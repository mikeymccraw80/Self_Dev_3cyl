//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:		mg_TLE4471_watchdog_reset_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Tue Oct 23 19:49:10 2012 %
//
// %derived_by:       tzwfxv %
//
// %date_modified:         %
//
// %version:         2 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define COP_OVER_DURING_US     130000
#define HARD_DELAY_US               500
/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_TLE4471_watchdog_reset_test(void)
 *
 * Description: This test reset processor after the COP limit time.
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_TLE4471_watchdog_reset_test(void)
{
    uint32_t start_timer;
    uint32_t current_timer;
    uint32_t diff;
    diff = 0;
    mg_HAL_Discrete_Set_TACH(true);
    start_timer = mg_HAL_Timer_Get_STM_In_us();
    /* Clear COP for new timer during */
    mg_HAL_Service_WatchDog();
    mg_HAL_Time_Hard_Delay_us(HARD_DELAY_US);
    mg_HAL_Service_WatchDog();
    while (diff < COP_OVER_DURING_US)
    {
        current_timer = mg_HAL_Timer_Get_STM_In_us();
        diff = mg_HAL_Timer_Get_STM_Diff_In_us(current_timer, start_timer);
    }
}


