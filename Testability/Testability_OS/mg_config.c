#include "reuse.h"
#include "mg_config.h"
#include "mg_mailbox.h"

// function test routines
#ifdef __MG_FACT_TEST
#include "mg_fact_test.h"
#endif
#ifdef __MG_ANALOG_IN_TEST
#include "mg_analog_in_test.h"
#endif
#ifdef __MG_DISCRETE_OUT_TEST
#include "mg_discrete_out_test.h"
#endif
#ifdef __MG_DISCRETE_IN_TEST
#include "mg_discrete_in_test.h"
#endif
#ifdef __MG_OUTPUT_CYCLING
#include "mg_output_cycling.h"
#endif
#ifdef __MG_OUTPUT_CYCLING_EMC
#include "mg_output_cycling_EMC.h"
#endif
#ifdef __MG_OUTPUT_CYCLING_VALIDATION
#include "mg_output_cycling_validation.h"
#endif
#ifdef __MG_INJECTOR_TEST
#include "mg_injector_test.h"
#endif
#ifdef __MG_KNOCK_TEST
#include "mg_knock_test.h"
#endif
#ifdef __MG_BARO_SENSOR_TEST_H
#include "mg_baro_sensor_test.h"
#endif
#ifdef __MG_KP254_FAULT_DIAGNOSTIC_TEST
#include "mg_baro_fault_diagnostic_test.h"
#endif
#ifdef __MG_EST_TEST
#include "mg_est_test.h"
#endif
#ifdef __MG_ETC_TEST
#include "mg_etc_test.h"
#endif
#ifdef __MG_FUEL_PUMP_OUTPUT_TEST
#include "mg_fuel_pump_output_test.h"
#endif
#ifdef __MG_FREQ_IN_TEST
#include "mg_freq_in_test.h"
#endif
#ifdef __MG_CRC_CHECKSUM_TEST
#include "mg_CRC_checksum_test.h"
#endif
#ifdef __MG_MEMORY_CHECKSUM_TEST
#include "mg_memory_checksum_test.h"
#endif
#ifdef __MG_KKSUM_CHECKSUM_TEST
#include "mg_KKsum_checksum_test.h"
#endif
#ifdef __MG_RAM_TEST
#include "mg_RAM_test.h"
#endif
#ifdef __MG_C2MIO_FAULT_DIAGNOSTIC_TEST
#include "mg_C2MIO_fault_diagnostic_test.h"
#endif
#ifdef __MG_VSEP_FAULT_DIAGNOSTIC_TEST
#include "mg_VSEP_fault_diagnostic_test.h"
#endif
#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
#include "mg_PHDL_fault_diagnostic_test.h"
#endif
#ifdef __MG_L9958_FAULT_DIAGNOSTIC_TEST
#include "mg_L9958_fault_diagnostic_test.h"
#endif
#ifdef __MG_C2PS_FAULT_DIAGNOSTIC_TEST
#include "mg_C2PS_fault_diagnostic_test.h"
#endif
#ifdef __MG_TLE4471_FAULT_DIAGNOSTIC_TEST
#include "mg_TLE4471_fault_diagnostic_test.h"
#endif
#ifdef __MG_C2PS_RESET_VOLT_TEST
#include "mg_C2PS_reset_volt_test.h"
#endif
#ifdef __MG_TLE4471_RESET_VOLT_TEST
#include "mg_TLE4471_reset_volt_test.h"
#endif
#ifdef __MG_MEMORY_READ_TEST
#include "mg_memory_read_test.h"
#endif
#ifdef __MG_EEEP_PML_WRITE_TEST
#include "mg_EEEP_PML_write_test.h"
#endif
#ifdef __MG_GENERAL_PORT_WRITE_TEST
#include "mg_general_port_write_test.h"
#endif
#ifdef __MG_TOD_TEST
#include "mg_TOD_test.h"
#endif
#ifdef __MG_IGBT_OVER_CURRENT_TEST
#include "mg_IGBT_over_current_test.h"
#endif
#ifdef __MG_C2PS_WATCHDOG_RESET_TEST
#include "mg_C2PS_watchdog_reset_test.h"
#endif
#ifdef __MG_TLE4471_WATCHDOG_RESET_TEST
#include "mg_TLE4471_watchdog_reset_test.h"
#endif
#ifdef __MG_COP_TIME_OVERFLOW_TEST
#include "mg_COP_time_overflow_test.h"
#endif
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
#include "mg_C2MIO_state_of_health_test.h"
#endif
#ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
#include "mg_VSEP_state_of_health_test.h"
#endif
#ifdef __MG_MICROP_FREQ_TEST
#include "mg_MicroP_freq_test.h"
#endif
#ifdef __MG_KW2000_TEST
#include "mg_kw2000_test.h"
#endif
#ifdef __MG_LIN_TEST
#include "mg_lin_test.h"
#endif

/* type define */
typedef void (* mgFnPtr_T)(void);

/* function declare */
void mg_unimplemented_test(void);

/* variable define */
const mgFnPtr_T mgFn[] = {
#ifdef __MG_FACT_TEST
   mg_fact_test,                                    /* testID 0x00 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_CRC_CHECKSUM_TEST
   mg_CRC_checksum_test,                          /* testID 0x01 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_MEMORY_CHECKSUM_TEST
   mg_memory_checksum_test,                          /* testID 0x02 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_KKSUM_CHECKSUM_TEST
   mg_KKsum_checksum_test,                          /* testID 0x03 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_RAM_TEST
   mg_RAM_test,                          /* testID 0x04 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_MEMORY_READ_TEST
   mg_memory_read_test,                          /* testID 0x05 */
#else
   mg_unimplemented_test,
#endif
   mg_unimplemented_test,                          /* testID 0x06 */
#ifdef __MG_EEEP_PML_WRITE_TEST
   mg_EEEP_PML_write_test,                          /* testID 0x07 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_ANALOG_IN_TEST
   mg_analog_test,                                 /* testID 0x08 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_FREQ_IN_TEST
   mg_freq_in_test,                                /* testID 0x09 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
   mg_PHDL_fault_diagnostic_test,                          /* testID 0x0A */
#else
    #ifdef __MG_L9958_FAULT_DIAGNOSTIC_TEST
   mg_L9958_fault_diagnostic_test,                          /* testID 0x0A */
    #else
   mg_unimplemented_test,
    #endif
#endif
#ifdef __MG_MICROP_FREQ_TEST
   mg_MicroP_freq_test,                          /* testID 0x0B */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_C2PS_FAULT_DIAGNOSTIC_TEST
   mg_C2PS_fault_diagnostic_test,                          /* testID 0x0C */
#else
    #ifdef __MG_TLE4471_FAULT_DIAGNOSTIC_TEST
   mg_TLE4471_fault_diagnostic_test,                          /* testID 0x0C */
    #else
   mg_unimplemented_test,
    #endif
#endif
#ifdef __MG_C2PS_RESET_VOLT_TEST
   mg_C2PS_reset_volt_test,                          /* testID 0x0D */
#else
    #ifdef __MG_TLE4471_RESET_VOLT_TEST
   mg_TLE4471_reset_volt_test,                          /* testID 0x0D */
    #else
   mg_unimplemented_test,
    #endif
#endif
#ifdef __MG_KP254_FAULT_DIAGNOSTIC_TEST
   mg_Baro_fault_diagnositc_test,                          /* testID 0x0E */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_GENERAL_PORT_WRITE_TEST
   mg_general_port_write_test,                          /* testID 0x0F */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_EST_TEST
   mg_etc_test,                                    /* testID 0x10 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_FUEL_PUMP_OUTPUT_TEST
   mg_fuel_pump_output_test,                          /* testID 0x11 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_INJECTOR_TEST
   mg_injector_test,                                    /* testID 0x12 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_KNOCK_TEST
   mg_knock_test,                          /* testID 0x13 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_C2MIO_FAULT_DIAGNOSTIC_TEST
   mg_C2MIO_fault_diagnostic_test,                          /* testID 0x14 */
#else
    #ifdef __MG_VSEP_FAULT_DIAGNOSTIC_TEST
   mg_VSEP_fault_diagnostic_test,                          /* testID 0x14 */
    #else
   mg_unimplemented_test,
    #endif
#endif
#ifdef __MG_TOD_TEST
   mg_TOD_test,                          /* testID 0x15 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_IGBT_OVER_CURRENT_TEST
   mg_IGBT_over_current_test,                          /* testID 0x16 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_C2PS_WATCHDOG_RESET_TEST
   mg_C2PS_watchdog_reset_test,                          /* testID 0x17 */
#else
    #ifdef __MG_TLE4471_WATCHDOG_RESET_TEST
   mg_TLE4471_watchdog_reset_test,                          /* testID 0x17 */
    #else
   mg_unimplemented_test,
    #endif
#endif
#ifdef __MG_COP_TIME_OVERFLOW_TEST
   mg_COP_time_overflow_test,                          /* testID 0x18 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
   mg_C2MIO_state_of_health_test,                          /* testID 0x19 */
#else
    #ifdef __MG_VSEP_STATE_OF_HEALTH_TEST
   mg_VSEP_state_of_health_test,                          /* testID 0x19 */
    #else
   mg_unimplemented_test,
    #endif
#endif
#ifdef __MG_BARO_SENSOR_TEST_H
   mg_Baro_sensor_test,                          /* testID 0x1A */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_LIN_TEST
   mg_LIN_test,                          /* testID 0x1B */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_EST_TEST
   mg_est_test,                                    /* testID 0x1C */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_DISCRETE_OUT_TEST
   mg_discrete_out_test,                           /* testID 0x1D */
#else
   mg_unimplemented_test,
#endif
   mg_unimplemented_test,                          /* testID 0x1E */
#ifdef __MG_DISCRETE_IN_TEST
   mg_discrete_in_test,                            /* testID 0x1F */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_KW2000_TEST
   mg_kw2000_test,                          /* testID 0x20 */
#else
   mg_unimplemented_test,
#endif
#ifdef __MG_OUTPUT_CYCLING
   mg_output_cycling,                              /* testID 0x21 */
#else
   mg_unimplemented_test,
#endif
};

const uint8_t max_number_of_tests =  (sizeof(mgFn)/sizeof(mgFnPtr_T));
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

/*=============================================================================
 * mg_Get_Test_Max_Number
 * @func  
 * @parm  none
 * @rdesc max number of tests 
 *===========================================================================*/
uint8_t mg_Get_Test_Max_Number(void)
{
    return max_number_of_tests;
}

/*=============================================================================
 * mg_Execute_Test
 * @func  
 * @parm  none
 * @rdesc max number of tests 
 *===========================================================================*/
void mg_Execute_Test(uint8_t test_id)
{
    (*mgFn[test_id])();
}
