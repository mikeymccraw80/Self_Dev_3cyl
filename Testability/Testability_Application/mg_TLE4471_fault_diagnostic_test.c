//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_C2PS_fault_diagnostic_test.c %
//
// created_by:       tzwfxv %
//
// date_created:      %
//
// %derived_by:       tzwfxv %
//
// %date_created:	Tue Oct 23 19:48:28 2012 %
//
// %version:         2 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal_discrete.h"
#include "mg_hal_fault.h"
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
 * Function Prototype: void mg_C2PS_fault_diagnostic_Test(void)
 *
 * Description: This test detect the fault state of C2PS.
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_TLE4471_fault_diagnostic_test(void)
{
    uint8_t read_item;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
#if __MG_C2PS_USED
    mg_HAL_Discrete_Set_C2PS_VIGNF( false);
    mg_HAL_Discrete_Set_C2PS_WTO( false);
    mg_HAL_Discrete_Set_C2PS_WP_Config( false);
    mg_HAL_Discrete_Set_C2PS_DRVENS( false);

    mg_HAL_Time_Hard_Delay_us(5000);

    mg_HAL_Discrete_Set_C2PS_DRVENS( true);

    mg_HAL_Time_Hard_Delay_us(5000);
#endif
    /* read C2PS diagnostic */
    mg_HAL_PowerDevice_Fault_Read();
    MG_MAILBOX_OUT(parameter[1]) = mg_HAL_PowerDevice_Fault_Get(0);
}
