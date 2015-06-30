//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_discrete_in_test.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:         %
//
// %version:         3 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_common.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
// #include "mg_hal_timer.h"

/*****************************************************************************
 * Function Prototype: void mg_Baro_sensor_Test(void)
 *
 * Description: This test get the discrete input value.
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_discrete_in_test(void)
{
    uint8_t idx;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

    MG_Bitmap_Init((void*)0);

    for (idx = 0; idx < MG_Number_of_Discrete_In_Device; idx++) 
    {
        if(mg_HAL_Discrete_Get_Discrete_In_Group(idx))
        {
            MG_Bitmap_Set(idx);
        }
        else
        {
            MG_Bitmap_Clr(idx);
        }
        mg_HAL_Service_WatchDog();
    }
    MG_MAILBOX_OUT(parameter[1]) = mg_bitmap[0];
    MG_MAILBOX_OUT(parameter[2]) = mg_bitmap[1];
    MG_MAILBOX_OUT(parameter[3]) = mg_bitmap[2];

}
