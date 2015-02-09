//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_IGBT_over_current_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Thu May  2 16:17:57 2013 %
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
#include "mg_hal_discrete.h"
#include "mg_hal_analog.h"
#include "mg_hal_est.h"
#include "mg_hal_fault.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define TEST_TIME_US        2000000                     /* 2 s */
#define EST_NUMBER                  4
#define DIAG_WAIT_SPI_US           1000               /* 1 ms */
/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_IGBT_over_current_test(void)
 *
 * Description: This test detect the over current state of IGBT
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_IGBT_over_current_test(void)
{
    uint32_t start_time;
    uint32_t current_time;
    uint8_t duty;
    uint16_t frequency;
    uint8_t idx;
    uint8_t PCH;
    uint8_t out_map_position;
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    
    duty = MG_MAILBOX_IN(parameter[0]);
    frequency = (uint16_t)((MG_MAILBOX_IN(parameter[1]) << 8) | MG_MAILBOX_IN(parameter[2]));

    mg_HAL_Discrete_Set_FSE(true);

    PCH = 0;

    if (duty > 25)
    {
        duty = 25;
    }

    if (mg_HAL_Get_EST_Sequential_Mode())
    {
        mg_HAL_EST_Set_Sequential_Mode(true);
        MG_HAL_EST_GROUP.on_time_us = ((TPU_A_TCR1_CLOCK_FREQ / 100) * duty / frequency);
        MG_HAL_EST_GROUP.delay_time_us = ((TPU_A_TCR1_CLOCK_FREQ / 100) * (25 - duty) / frequency);
    }
    else
    {
        mg_HAL_EST_Set_Sequential_Mode(false);
        MG_HAL_EST_GROUP.on_time_us = ((TPU_A_TCR1_CLOCK_FREQ / 100) * duty / frequency);
        MG_HAL_EST_GROUP.delay_time_us = ((TPU_A_TCR1_CLOCK_FREQ / 100) * (50 - duty) / frequency);
    }
    mg_HAL_EST_Init(MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME,  MG_HAL_EST_GROUP.on_time_us,
        MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.delay_time_us, 0);
    
    /* clear fault buffer before read */
    mg_HAL_ComplexIO_Fault_Clear();

    
    start_time = mg_HAL_Timer_Get_STM_In_us();
    current_time = start_time;

    mg_HAL_EST_Start();
    
    while (TEST_TIME_US > mg_HAL_Timer_Get_STM_Diff_In_us(current_time, start_time))
    {
        mg_HAL_EST_cycling();
        current_time = mg_HAL_Timer_Get_STM_In_us();
        mg_HAL_Service_WatchDog();
    }
    /* read fault for VSEP */
    mg_HAL_ComplexIO_Fault_Read();
    for (idx = 0; idx < EST_NUMBER; idx++)
    {
        if (MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY==
            mg_HAL_ComplexIO_Fault_Get( idx))
        {
            out_map_position = (uint8_t)((idx & 0x03) << 1);
            PCH |= (MG_COMPLEXIO_FAULT_SHORT_TO_BATTERY << out_map_position);
        }
    }
    MG_MAILBOX_OUT(parameter[1]) = PCH;
}

