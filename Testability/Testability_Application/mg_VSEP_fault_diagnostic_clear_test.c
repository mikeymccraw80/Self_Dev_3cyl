//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_VSEP_fault_diagnostic_clear_test.c %
//
// created_by:       tzwfxv %
//
// date_created:	Fri Jul 13 14:01:22 2012 %
//
// %derived_by:       tzwfxv %
//
// %date_modified:         %
//
// %version:         2 %
//
//=============================================================================
#if 0
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal_fault.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define PCH_NUMBER                 10

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_VSEP_fault_diagnostic_Test(void)
 *
 * Description: This test detect the fault state of VSEP
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_VSEP_fault_diagnostic_clear_test(void)
{
    uint8_t idx;
    uint8_t PCH[PCH_NUMBER];
    uint8_t fault_map_index;
    uint8_t fault_map_position;
    uint8_t out_map_index;
    uint8_t out_map_position;

    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

    for (idx = 0; idx < PCH_NUMBER; idx++)
    {
        PCH[idx] = 0;
    }
    /* read to clear fault buffer for enable diagnostic next time */
    mg_HAL_ComplexIO_Fault_Clear();
    for (idx = 0; idx < 10; idx++)
    {
        MG_MAILBOX_OUT(parameter[idx + 1]) = PCH[idx];
    }
}

#endif