//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_etc_test.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:           %
//
// %version:         6 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal_discrete.h"
#include "mg_hal_etc.h"

#define MG_HIODEVICE_ETCCUR	33

/*****************************************************************************
 * Function Prototype: void mg_etc_test(void)
 *
 * Description: This test output ETC as control.
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_etc_test(void)
{
    uint16_t current_value;
	
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    // execute successfully
    MG_MAILBOX_OUT(parameter[1]) = 0x00;

    // don't reverse ETC
    MG_HAL_ETC_GROUP.reverse_time_ms = 0;

    mg_HAL_Discrete_Set_FSE(true);
    mg_HAL_ETC_Discrete_Enable(true);

    if (MG_MAILBOX_IN(parameter[3]) == 0x01)
    {
        mg_HAL_ETC_Discrete_Direction(true);
    }
    else if(MG_MAILBOX_IN(parameter[3]) == 0x02)
    {
        mg_HAL_ETC_Discrete_Direction(false);
    }
    else
    {
        /* error command */
    }

    MG_HAL_ETC_GROUP.duty = MG_MAILBOX_IN(parameter[0]);
    MG_HAL_ETC_GROUP.freq = MG_MAILBOX_IN(parameter[1])*256 + MG_MAILBOX_IN(parameter[2]);
    mg_HAL_ETC_Set_Freq_And_Duty();

    if ((MG_HAL_ETC_GROUP.duty == 0) && (MG_HAL_ETC_GROUP.freq == 0))
    {
        mg_HAL_ETC_Discrete_Enable(false);
    }

}
