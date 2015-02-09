//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_main.c %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:                  %
//
// %version:         11 %
//
//=============================================================================


#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_main.h"
#include "mcamos.h"
#include "mg_config.h"


#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_discrete.h"
#include "mg_output_cycling_EMC.h"
#include "mg_output_cycling_validation.h"
#if 0
// function test routines
#include "mg_fact_test.h"
#include "mg_analog_in_test.h"
#include "mg_discrete_out_test.h"
#include "mg_discrete_in_test.h"
#include "mg_output_cycling.h"
#include "mg_output_cycling_EMC.h"
#include "mg_output_cycling_validation.h"
#include "mg_injector_test.h"
#include "mg_knock_test.h"
#include "mg_baro_sensor_test.h"
#include "mg_est_test.h"
#include "mg_etc_test.h"
#include "mg_fuel_pump_output_test.h"
#include "mg_freq_in_test.h"
#include "mg_CRC_checksum_test.h"
#include "mg_memory_checksum_test.h"
#include "mg_KKsum_checksum_test.h"
#include "mg_RAM_test.h"
#include "mg_C2MIO_fault_diagnostic_test.h"
#include "mg_PHDL_fault_diagnostic_test.h"
#include "mg_C2PS_fault_diagnostic_test.h"
#include "mg_C2PS_reset_volt_test.h"
#include "mg_memory_read_test.h"
#include "mg_EEEP_PML_write_test.h"
#include "mg_general_port_write_test.h"
#include "mg_TOD_test.h"
#include "mg_IGBT_over_current_test.h"
#include "mg_C2PS_watchdog_reset_test.h"
#include "mg_COP_time_overflow_test.h"
#include "mg_C2MIO_state_of_health_test.h"
#include "mg_MicroP_freq_test.h"
#include "mg_kw2000_test.h"
#include "mg_lin_test.h"

// function test routines include end

#define MG_FINISHED                      0xFF
#define MG_UNIMPLEMENTED_TEST            0xFE



void mg_unimplemented_test(void);




const mgFnPtr_T mgFn[] = {
   mg_fact_test,                                    /* testID 0x00 */
   mg_CRC_checksum_test,                          /* testID 0x01 */
   mg_memory_checksum_test,                          /* testID 0x02 */
   mg_KKsum_checksum_test,                          /* testID 0x03 */
   mg_RAM_test,                          /* testID 0x04 */
   mg_memory_read_test,                          /* testID 0x05 */
   mg_unimplemented_test,                          /* testID 0x06 */
   mg_EEEP_PML_write_test,                          /* testID 0x07 */
   mg_analog_test,                                 /* testID 0x08 */
   mg_freq_in_test,                                /* testID 0x09 */
   mg_PHDL_fault_diagnostic_test,                          /* testID 0x0A */
   mg_MicroP_freq_test,                          /* testID 0x0B */
   mg_C2PS_fault_diagnostic_test,                          /* testID 0x0C */
   mg_C2PS_reset_volt_test,                          /* testID 0x0D */
   mg_unimplemented_test,                          /* testID 0x0E */
   mg_general_port_write_test,                          /* testID 0x0F */
   mg_etc_test,                                    /* testID 0x10 */
   mg_fuel_pump_output_test,                          /* testID 0x11 */
   mg_injector_test,                                    /* testID 0x12 */
   mg_knock_test,                          /* testID 0x13 */
   mg_C2MIO_fault_diagnostic_test,                          /* testID 0x14 */
   mg_TOD_test,                          /* testID 0x15 */
   mg_IGBT_over_current_test,                          /* testID 0x16 */
   mg_C2PS_watchdog_reset_test,                          /* testID 0x17 */
   mg_COP_time_overflow_test,                          /* testID 0x18 */
   mg_C2MIO_state_of_health_test,                          /* testID 0x19 */
   mg_Baro_sensor_test,                          /* testID 0x1A */
   mg_LIN_test,                          /* testID 0x1B */
   mg_est_test,                                    /* testID 0x1C */
   mg_discrete_out_test,                           /* testID 0x1D */
   mg_unimplemented_test,                          /* testID 0x1E */
   mg_discrete_in_test,                            /* testID 0x1F */
   mg_kw2000_test,                          /* testID 0x20 */
   mg_output_cycling,                              /* testID 0x21 */
};


#define MAX_NUMBER_OF_TESTS  (sizeof(mgFn)/sizeof(mgFnPtr_T)) 
#endif

/* macro define */
#define MAX_NUMBER_OF_TESTS mg_Get_Test_Max_Number()

/* variable define */
MG_MODE_T Mg_Mode = UNDEFINED_MODE;

/* function declare */
uint8_t mg_Get_Test_Max_Number(void);
void mg_Execute_Test(uint8_t test_id);


/*=============================================================================
 * clear_mailbox
 * @func  Prepare mailbox for use
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
static void clear_mailbox(void)
{
   uint8_t *mbptr;
   MG_MAILBOX_IN(testid) = MG_FINISHED;
   mbptr = (uint8_t *)INBOX_PTR;
   mbptr++;
   for (; (uint32_t)mbptr < END_OF_MAILBOX; mbptr++) 
   {
      *mbptr = 0;
   }
}

/*=============================================================================
 * Initialize_Testability
 * @func  Do all initialization here for testability
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
static void Initialize_Testability(void)
{
    uint8_t  idx;

    mg_HAL_SWT_Enable_WatchDog( false );
    clear_mailbox();

    MG_SIU_GPIO_DISCRETE_Initialize_Device_Override();

    mg_HAL_Discrete_Reconfigure_CAL();

    mg_HAL_Internal_Device_Init();

    mg_HAL_External_Device_Init();
    

    mg_HAL_SPI_Timer_Enable( false );


    for (idx = 0; idx < MG_Number_of_Discrete_Out_Device; idx++)
    {
        mg_HAL_Discrete_Set_Discrete_Out_Group_Value(idx, false);
    }
    if (!mg_HAL_Discrete_Get_ELOAD1())
    {
        Mg_Mode = MG_FUNCTION_TEST;
    }
    else
    {
        if (!mg_HAL_Discrete_Get_ELOAD2())
        {
            Mg_Mode = MG_OUTPUT_CYCLING_VALIDATION;
        }
        else
        {
            Mg_Mode = MG_OUTPUT_CYCLING_EMC;
        }
    }
    if ( (Mg_Mode == MG_FUNCTION_TEST) || 
        (Mg_Mode == MG_OUTPUT_CYCLING_EMC)||
        (Mg_Mode == MG_OUTPUT_CYCLING_VALIDATION)      ) 
    {
        MCAMOS_enable = true;
    }
    Enable_Interrupts();
}

/*=============================================================================
 * mg_main
 * @func  main function of testability, it's the entry of testability
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_main(void)
{
    uint8_t volatile testIdx;

    Initialize_Testability();
    mg_HAL_Service_WatchDog();
    mg_HAL_Disable_CAN_10ms_Task_Timer();
    
    /* Detect IGN OFF by TOD function */
#ifdef __MG_C2PS_USED

    mg_HAL_Discrete_Set_TODO(false);
#endif
#ifdef __MG_TLE4471_USED
    mg_HAL_Discrete_Set_TODO(false);
#endif

#ifdef EMC_CYCLING
    Mg_Mode = MG_OUTPUT_CYCLING_EMC;
#endif

   // stay in cycling until a reset occurs or IGN OFF
    while(1)
    {
        mg_HAL_Service_WatchDog();
        switch(Mg_Mode)
        {
            case MG_FUNCTION_TEST:
            {
                testIdx = MG_MAILBOX_IN(testid);
                /* if there is a pending test in mailbox */
                if((testIdx != MG_FINISHED) && (MCAMOS_Get_Message_Size() == 0))
                {
                    /* check if the test is valid */
                    if(testIdx < MAX_NUMBER_OF_TESTS)
                    {
                        mg_Execute_Test(testIdx);
//                        (*mgFn[testIdx])();
                    }
                    /* Test is finished. Overwrite te mailbox with MG_FINISHED */
                    MG_MAILBOX_IN(testid) = MG_FINISHED;
                }
                break;
            }
            case MG_OUTPUT_CYCLING_EMC:
            {
                mg_output_cycling_EMC();
                break;
            }
            case MG_OUTPUT_CYCLING_VALIDATION:
            {
                mg_output_cycling_validation();
                break;
            }
            default:
                break;
        }
        mg_HAL_Service_WatchDog();

    }
}

#if 0
/*=============================================================================
 * mg_unimplemented_test
 * @func  
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_unimplemented_test(void)
{
   MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
   MG_MAILBOX_OUT(parameter[1]) = MG_UNIMPLEMENTED_TEST;
}
#endif
