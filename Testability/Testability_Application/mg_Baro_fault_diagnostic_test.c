//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_Baro_fault_diagnostic_test.c %
//
// created_by:       tzwfxv %
//
// date_created:      %
//
// %derived_by:       tzwfxv %
//
// %date_modified:            %
//
// %version:         1 %
//
//=============================================================================
#if 0
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal.h"
#include "mg_hal_baro.h"
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
 * Function Prototype: void mg_Baro_fault_diagnositc_test(void)
 *
 * Description: This test diagnose Baro errors
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_Baro_fault_diagnositc_test(void)
{
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

//    mg_HAL_Time_Hard_Delay_ms(10, NULL);
    MG_MAILBOX_OUT(parameter[1]) = mg_HAL_Baro_Get_Diagnostic();
//    mg_HAL_Time_Hard_Delay_ms(20, NULL);

}
#endif