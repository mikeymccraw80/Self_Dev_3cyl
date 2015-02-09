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
#include "mg_hal_est.h"
#include "mg_hal_inj.h"
#include "mg_hal_fault.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define SHORT_GROUND            0
#define SHORT_BATTERY           1

#define PCH_NUMBER                 10
#define INJ_NUMBER                  4
#define EST_NUMBER                  4

#define DIAG_WAIT_IO_US            10
#define DIAG_WAIT_SPI_US           1000

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
void mg_VSEP_fault_diagnostic_test(void)
{
    uint8_t test_mode;
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
    test_mode = MG_MAILBOX_IN(parameter[0]);

    if (mg_HAL_Get_EST_Sequential_Mode())
    {
        mg_HAL_EST_Set_Sequential_Mode(true);
    }
    else
    {
        mg_HAL_EST_Set_Sequential_Mode(false);
    }

    mg_HAL_Service_WatchDog();

    if (SHORT_BATTERY == test_mode)
    {
        /* clear fault buffer before read */
        mg_HAL_ComplexIO_Fault_Clear();
        mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_SPI_US);
        mg_HAL_EST_Toggle();
#if 0        
        for (idx = 0; idx < EST_NUMBER; idx++)
        {
            mg_HAL_EST_Set_EST1(false);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_EST_Set_EST1(true);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_EST_Set_ESTSYNC(false);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_EST_Set_ESTSYNC(true);
            mg_HAL_Service_WatchDog();
        }
#endif            
        for (idx = 0; idx < INJ_NUMBER; idx++)
        {
            mg_HAL_Injector_Set_Group_Value(idx, false);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_Injector_Set_Group_Value(idx, true);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_Service_WatchDog();
        }
        for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
        {
            if (PWM_REVERSE == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
            {
                mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, true);
                mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
                mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, false);
                mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            }
            else
            {
                mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, false);
                mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
                mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, true);
                mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            }
            mg_HAL_Service_WatchDog();
        }
    }
    else if (SHORT_GROUND == test_mode)
    {
        /* clear fault buffer before read */
        mg_HAL_ComplexIO_Fault_Clear();
        mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_SPI_US);
        mg_HAL_EST_Toggle();
#if 0        
        for (idx = 0; idx < EST_NUMBER; idx++)
        {
            mg_HAL_EST_Set_EST1(false);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_EST_Set_ESTSYNC(false);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_EST_Set_ESTSYNC(true);
            mg_HAL_Service_WatchDog();
        }
#endif        
        for (idx = 0; idx < INJ_NUMBER; idx++)
        {
            mg_HAL_Injector_Set_Group_Value(idx, false);
            mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            mg_HAL_Service_WatchDog();
        }
        for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
        {
            if (PWM_REVERSE == MG_HAL_DISCRETE_OUT_GROUP[idx].type)
            {
                mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, true);
                mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            }
            else
            {
                mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, false);
                mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_IO_US);
            }
            mg_HAL_Service_WatchDog();
        }
    }
    else
    {

    }

    mg_HAL_Service_WatchDog();

    /* read fault for C2MIO */
    mg_HAL_ComplexIO_Fault_Read();
    mg_HAL_Time_Hard_Delay_us(DIAG_WAIT_SPI_US);
    for (idx = 0; idx < MG_COMPLEXIO_CHANNEL_MAX; idx++)
    {
        if (SHORT_BATTERY == test_mode)
        {
            if (MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY==
                mg_HAL_ComplexIO_Fault_Get(idx))
            {
                out_map_index = (idx >> 2);
                out_map_position = ((idx & 0x03) << 1);
                PCH[out_map_index] |= (MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY << out_map_position);
            }
        }
        else if (SHORT_GROUND == test_mode)
        {
            if (MG_COMPLEXIO_FAULT_SHORT_TO_GROUND ==
                mg_HAL_ComplexIO_Fault_Get(idx))
            {
                out_map_index = (idx >> 2);
                out_map_position = ((idx & 0x03) << 1);
                PCH[out_map_index] |= (MG_COMPLEXIO_FAULT_SHORT_TO_GROUND << out_map_position);
            }
            else if (MG_COMPLEXIO_FAULT_OPEN ==
                mg_HAL_ComplexIO_Fault_Get(idx))
            {
                out_map_index = (idx >> 2);
                out_map_position = ((idx & 0x03) << 1);
                PCH[out_map_index] |= (MG_COMPLEXIO_FAULT_OPEN << out_map_position);
            }
            else
            {

            }
        }
        else
        {

        }
        mg_HAL_Service_WatchDog();
    }

    for (idx = 0; idx < 10; idx++)
    {
        MG_MAILBOX_OUT(parameter[idx + 1]) = PCH[idx];
    }
}

