//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_Baro_Sensor_test.c %
//
// created_by:       tzwfxv %
//
// date_created:      %
//
// %derived_by:       tzwfxv %
//
// %date_modified:            %
//
// %version:         5 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_analog.h"

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
 * Function Prototype: void mg_Baro_sensor_Test(void)
 *
 * Description: This test perform Frequency Input measurement of the Temperature & Current
 *              input from Baro
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_Baro_sensor_test(void)
{
    uint16_t pressure;
    uint16_t temperature;

    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

    pressure = mg_HAL_Analog_Get_Baro_Pressure();
    temperature = mg_HAL_Analog_Get_Baro_Temperature();

    mg_HAL_Service_WatchDog();

    MG_MAILBOX_OUT(parameter[1]) = (uint8_t)(pressure >> 8);
    MG_MAILBOX_OUT(parameter[2]) = (uint8_t)(pressure & 0xFF);
    MG_MAILBOX_OUT(parameter[3]) = (uint8_t)(temperature >> 8);
    MG_MAILBOX_OUT(parameter[4]) = (uint8_t)(temperature & 0xFF);
}

