//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_PHDL_fault_diagnostic_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Tue Oct 23 19:57:10 2012 %
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
#include "mg_hal_PWM.h"
#include "mg_hal_etc.h"
#include "mg_hal_fault.h"
#include "mg_hal_timer.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define OPEN_FAULT_TEST         0
#define STB_STG_TEST                1
#define OVER_CURRENT_TEST       2

#define DELAY_2_S                   2000000
#define DELAY_200_MS           200000
#define DELAY_1000_US           1000
#define DELAY_500_US            500
/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*   Definition of static objects                                             */
/*----------------------------------------------------------------------------*/


/*****************************************************************************
 * Function Prototype: void mg_PHDL_fault_diagnostic_test(void)
 *
 * Description: This test detect the fault state of PHDL
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_L9958_fault_diagnostic_test(void)
{
    uint8_t test_mode;
    uint8_t test_slew_rate;
    
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    test_mode = MG_MAILBOX_IN(parameter[0]);
    test_slew_rate = MG_MAILBOX_IN(parameter[1]);
  
    /* Clear the device fault by sending Bit 8 of Txd as '1' */
    mg_HAL_ETC_Discrete_Enable(true);
    mg_HAL_PWM_Set_ETCCTLPWM_Frequency_And_Duty(10000, 100);
    mg_HAL_ETC_Discrete_Direction( true);
    mg_HAL_Time_Hard_Delay_us(DELAY_500_US);
    mg_HAL_ETC_Discrete_Direction( false);
    mg_HAL_Time_Hard_Delay_us(DELAY_500_US);
    mg_HAL_ETC_Fault_Clear();
    
    if (OPEN_FAULT_TEST == test_mode)
    {
        /* Off State */
        mg_HAL_ETC_Discrete_Enable(false);
        /* Low Side Current Limit Set 0x03 */
        mg_HAL_Fault_ETC_Open_Test_Configure();
        mg_HAL_Time_Hard_Delay_us(DELAY_200_MS);
    }
    else if (STB_STG_TEST == test_mode)
    {
        /* Off State */
        mg_HAL_ETC_Discrete_Enable(false);
        /* Low Side Current Limit Set 0x03 */
        mg_HAL_Fault_ETC_STB_STG_Test_Configure();
        mg_HAL_Time_Hard_Delay_us(DELAY_200_MS);
    }
    else if (OVER_CURRENT_TEST == test_mode)
    {
        /* On State */
        mg_HAL_ETC_Discrete_Enable(true);
        /* Low Side Current Limit Set 0x00 */
        mg_HAL_Fault_ETC_Over_Current_Test_Configure(test_slew_rate);
        mg_HAL_PWM_Set_ETCCTLPWM_Frequency_And_Duty(10000, 100);
        mg_HAL_ETC_Discrete_Direction( true);
        mg_HAL_Time_Hard_Delay_us(DELAY_500_US);
        mg_HAL_ETC_Discrete_Direction( false);
        mg_HAL_Time_Hard_Delay_us(DELAY_500_US);
    }
    else
    {
    }

    /* Read Fault State */
    mg_HAL_ETC_Fault_Read();
    MG_MAILBOX_OUT(parameter[1]) = mg_HAL_ETC_Fault_Get(0);
    MG_MAILBOX_OUT(parameter[2]) = mg_HAL_ETC_Fault_Get(1);
    mg_HAL_Time_Hard_Delay_us(DELAY_500_US);
    // Clear fault after over current
    mg_HAL_ETC_Fault_Clear();
    mg_HAL_ETC_Fault_Read();
}
