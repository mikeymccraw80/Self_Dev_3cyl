//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_TOD_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Thu May  2 16:30:12 2013 %
//
// %derived_by:       tzwfxv %
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
 * Function Prototype: void mg_TOD_Test(void)
 *
 * Description: This test power down the processor after loss of VIGNF
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_TOD_test(void)
{
    uint16_t TPS_value;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    MG_MAILBOX_OUT(parameter[1]) = MG_MAILBOX_IN(parameter[0]);
    mg_HAL_Discrete_Set_FAN1( true);
    while (1)
    {
        TPS_value = mg_HAL_Analog_Get_TPS1();
        if (TPS_value < 0x8000)
        {
#ifdef __MG_C2PS_USED
            mg_HAL_Discrete_Set_TODO(false);
#endif
#ifdef __MG_TLE4471_USED
            mg_HAL_Discrete_Set_TODO(false);
#endif
        }
        else
        {
#ifdef __MG_C2PS_USED
            mg_HAL_Discrete_Set_TODO(true);
#endif
#ifdef __MG_TLE4471_USED
            mg_HAL_Discrete_Set_TODO(true);
#endif
        }
        mg_HAL_Service_WatchDog();
    }
}
