//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_MicroP_freq_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Thu May  2 16:26:48 2013 %
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
#include "mg_hal_discrete.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define TIME_20_MS                      (20 * (SYSTEM_FREQUENCY_HZ / 1000))      /* 20 ms */
/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_MicroP_freq_test(void)
 *
 * Description: This test output a pulse with 20 ms.
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_MicroP_freq_test(void)
{
    uint32_t start_timer;
    uint32_t current_timer;
    uint32_t diff;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    mg_HAL_Discrete_Set_GEN_ENABLE(true);
    mg_HAL_Discrete_Set_FAN2( false);
    start_timer = mg_HAL_Timer_Get_STM_In_CNT();
    mg_HAL_Discrete_Set_FAN2( true);
    do
    {
        current_timer = mg_HAL_Timer_Get_STM_In_CNT();
        diff = mg_HAL_Timer_Get_STM_Diff_In_CNT(current_timer, start_timer);
    } while (diff < TIME_20_MS);
    mg_HAL_Discrete_Set_FAN2( false);
}


