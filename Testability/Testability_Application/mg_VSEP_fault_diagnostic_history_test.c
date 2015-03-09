//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_VSEP_fault_diagnostic_test.c %
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
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_fault.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define PCH_NUMBER                 10
#define INJ_NUMBER                  4
#define EST_NUMBER                  4

#define DIAG_WAIT_SPI_US           1000

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_VSEP_fault_diagnostic_history_Test(void)
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
void mg_VSEP_fault_diagnostic_history_test(void)
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

    /* read fault for VSEP */
    mg_HAL_ComplexIO_Fault_Read();
    mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_SPI_US);
    for (idx = 0; idx < (MG_Number_of_Discrete_Out_Device - 2 + INJ_NUMBER + EST_NUMBER); idx++)
    {
        out_map_index = (idx >> 2);
        out_map_position = ((idx & 0x03) << 1);
        PCH[out_map_index] |= (mg_HAL_ComplexIO_Fault_Get(idx) << out_map_position);
        mg_HAL_Service_WatchDog();
    }

    for (idx = 0; idx < 10; idx++)
    {
        MG_MAILBOX_OUT(parameter[idx + 1]) = PCH[idx];
    }
}
