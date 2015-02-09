//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_COP_time_overflow_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Thu May  2 16:14:52 2013 %
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
#include "mg_hal_PWM.h"
#include "mg_hal_discrete.h"

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
 * Function Prototype: void mg_COP_time_overflow_Test(void)
 *
 * Description: This test perform Frequency Input measurement of the EXTCLK
 *              input from LMC555 circuit
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_COP_time_overflow_test(void)
{
    uint32_t time_out;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    time_out = MG_MAILBOX_IN(parameter[0]);
    switch (time_out)
    {
        case 1:
            mg_HAL_PWM_Set_SWT_Timer(2048);
            break;
        case 2:
            mg_HAL_PWM_Set_SWT_Timer(8192);
            break;
        case 3:
            mg_HAL_PWM_Set_SWT_Timer(32768);
            break;
        case 4:
            mg_HAL_PWM_Set_SWT_Timer(131072);
            break;
        case 5:
            mg_HAL_PWM_Set_SWT_Timer(524288);
            break;
        case 6:
            mg_HAL_PWM_Set_SWT_Timer(1048576);
            break;
        case 7:
            mg_HAL_PWM_Set_SWT_Timer(2097152);
            break;
        default:
            time_out = 0;
            break;
    }
    mg_HAL_Discrete_Set_TACH( true);
    if ((time_out & 0x07) != 0)
    {
        mg_HAL_SWT_Enable_WatchDog( true );
    }
}


