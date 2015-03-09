//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_freq_in_test.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:             %
//
// %version:         6 %
//
//=============================================================================
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal_PWM.h"


/*=============================================================================
 * mg_freq_in_test
 * @func  perform frequency input test
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_freq_in_test(void)
{
    uint8_t   idx;
    uint32_t period[7];

    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    for (idx = 0; idx < MG_Number_of_Frequency_In_Device; idx ++)
    {
        period[idx] = mg_HAL_PWM_Get_Frequency_In_Group_Period(idx);
    }
    for (idx = 0; idx < MG_Number_of_Frequency_In_Device; idx++)
    {
        MG_MAILBOX_OUT(parameter[idx * 3 + 1]) = (uint8_t)((period[idx] >> 16) & 0xFF);
        MG_MAILBOX_OUT(parameter[idx * 3 + 2]) = (uint8_t)((period[idx] >> 8) & 0xFF);
        MG_MAILBOX_OUT(parameter[idx * 3 + 3]) = (uint8_t)(period[idx] & 0xFF);
    }
}
