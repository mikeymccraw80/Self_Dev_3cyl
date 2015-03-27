//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_analog_in_test.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:          %
//
// %version:         3 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_analog.h"



/*=============================================================================
 * mg_analog_test
 * @func  perform analog input test
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_analog_test(void)
{
   uint8_t   idx;
   uint16_t  *outptr;

   MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

   outptr = (uint16_t *)&(MG_MAILBOX_OUT(parameter[1]));

   for (idx = 0; idx < MG_Number_of_Analog_Device; idx++, outptr++) 
   {
      *outptr = mg_HAL_Analog_Get_Analog_Value(idx);
      mg_HAL_Service_WatchDog();
   }

}
