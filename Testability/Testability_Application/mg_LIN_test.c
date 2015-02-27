//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_LIN_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Thu May  2 16:22:15 2013 %
//
// %derived_by:       tzwfxv %
//
// %date_modified:          %
//
// %version:         3 %
//
//=============================================================================
#if 0
#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_analog.h"
#include "mg_hal_lin.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define TPS1_COMPARE_VOLT       0x7FFF
/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_LIN_Test(void)
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
void mg_LIN_test(void)
{
    uint8_t data_buffer;
    uint8_t reference_value;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    reference_value = MG_MAILBOX_IN(parameter[0]);
    data_buffer = 0;
    /* read for clear rx buffer */
    mg_HAL_LIN_Reset_Read_Status();
    mg_HAL_LIN_Read();
    do
    {
        if (mg_HAL_LIN_Get_Read_Status())
        {
            mg_HAL_LIN_Reset_Read_Status();
            data_buffer = mg_HAL_LIN_Read();
            break;
        }
        mg_HAL_Service_WatchDog();
    } while (TPS1_COMPARE_VOLT < mg_HAL_Analog_Get_TPS1());
    if (data_buffer == reference_value)
    {
        data_buffer = 0 - reference_value;
        /* If received data is correct, change out box immediately */
        MG_MAILBOX_OUT(parameter[1]) = data_buffer;
        /* Sending message continue 3 s */
        do
        {
            if (mg_HAL_LIN_Get_Write_Status())
            {
                mg_HAL_LIN_Reset_Write_Status();
                mg_HAL_LIN_Write(data_buffer);
            }
            mg_HAL_Service_WatchDog();
        } while (TPS1_COMPARE_VOLT < mg_HAL_Analog_Get_TPS1());
    }
    else
    {
        MG_MAILBOX_OUT(parameter[1]) = 0xFF;
    }
}

#endif
