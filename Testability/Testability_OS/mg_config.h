#ifndef MG_CONFIG_H
#define MG_CONFIG_H

/* External Device Used List */
#undef __MG_C2MIO_USED
#define __MG_VSEP_USED
#undef __MG_C2PS_USED
#define __MG_TLE4471_USED
#undef __MG_PHDL_USED
#define __MG_L9958_USED
#undef __MG_KP254_USED

/* Test Functions Defination */
#undef __MG_FACT_TEST
#define __MG_CRC_CHECKSUM_TEST
#define __MG_MEMORY_CHECKSUM_TEST
#define __MG_KKSUM_CHECKSUM_TEST
#define __MG_RAM_TEST
#define __MG_MEMORY_READ_TEST
#undef __MG_MEMORY_WRITE_TEST
#undef __MG_EEEP_PML_WRITE_TEST
#define __MG_ANALOG_IN_TEST
#define __MG_FREQ_IN_TEST
#undef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
#define __MG_L9958_FAULT_DIAGNOSTIC_TEST
#define __MG_MICROP_FREQ_TEST
#undef __MG_C2MIO_FAULT_DIAGNOSTIC_TEST
#define __MG_VSEP_FAULT_DIAGNOSTIC_TEST
#undef __MG_C2MIO_STATE_OF_HEALTH_TEST
#define __MG_VSEP_STATE_OF_HEALTH_TEST
#undef __MG_C2PS_FAULT_DIAGNOSTIC_TEST
#define __MG_TLE4471_FAULT_DIAGNOSTIC_TEST
#undef __MG_C2PS_RESET_VOLT_TEST
#define __MG_TLE4471_RESET_VOLT_TEST
#undef __MG_C2PS_WATCHDOG_RESET_TEST
#define __MG_TLE4471_WATCHDOG_RESET_TEST
#undef __MG_GENERAL_PORT_WRITE_TEST
#define __MG_EST_TEST
#define __MG_ETC_TEST
#undef __MG_FUEL_PUMP_OUTPUT_TEST
#define __MG_INJECTOR_TEST
#undef __MG_KNOCK_TEST
#define __MG_TOD_TEST
#undef __MG_IGBT_OVER_CURRENT_TEST
#define __MG_COP_TIME_OVERFLOW_TEST
#undef __MG_BARO_SENSOR_TEST_H
#undef __MG_LIN_TEST
#define __MG_DISCRETE_OUT_TEST
#define __MG_DISCRETE_IN_TEST
#define __MG_KW2000_TEST
#define __MG_OUTPUT_CYCLING
#define __MG_OUTPUT_CYCLING_EMC
#define __MG_OUTPUT_CYCLING_VALIDATION
#undef __MG_KP254_FAULT_DIAGNOSTIC_TEST

#ifndef __MG_C2MIO_USED
#undef __MG_C2MIO_FAULT_DIAGNOSTIC_TEST
#undef __MG_C2MIO_STATE_OF_HEALTH_TEST
#endif
#ifndef __MG_C2PS_USED
#undef __MG_C2PS_FAULT_DIAGNOSTIC_TEST
#undef __MG_C2PS_RESET_VOLT_TEST
#undef __MG_C2PS_WATCHDOG_RESET_TEST
#endif
#ifndef __MG_PHDL_USED
#undef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
#endif
#ifndef __MG_KP254_USED
#undef __MG_KP254_FAULT_DIAGNOSTIC_TEST
#endif
#ifndef __MG_VSEP_USED
#undef __MG_VSEP_FAULT_DIAGNOSTIC_TEST
#undef __MG_VSEP_STATE_OF_HEALTH_TEST
#endif
#ifndef __MG_TLE4471_USED
#undef __MG_TLE4471_FAULT_DIAGNOSTIC_TEST
#undef __MG_TLE4471_RESET_VOLT_TEST
#undef __MG_TLE4471_WATCHDOG_RESET_TEST
#endif
#ifndef __MG_L9958_USED
#undef __MG_L9958_FAULT_DIAGNOSTIC_TEST
#endif

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
#ifdef __MG_PHDL_FAULT_DIAGNOSTIC_TEST
#include "mg_PHDL_fault_diagnostic_test.h"
#endif
#ifdef __MG_C2PS_FAULT_DIAGNOSTIC_TEST
#include "mg_C2PS_fault_diagnostic_test.h"
#endif
#ifdef __MG_C2PS_RESET_VOLT_TEST
#include "mg_C2PS_reset_volt_test.h"
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
#ifdef __MG_COP_TIME_OVERFLOW_TEST
#include "mg_COP_time_overflow_test.h"
#endif
#ifdef __MG_C2MIO_STATE_OF_HEALTH_TEST
#include "mg_C2MIO_state_of_health_test.h"
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

/*----------------------------------------------------------------------------*/
/*   Definition of MACMOS macros                                               */
/*----------------------------------------------------------------------------*/
#define MG_FINISHED                      0xFF
#define MG_UNIMPLEMENTED_TEST            0xFE

/*----------------------------------------------------------------------------*/
/*   Definition of CRCSUM test                                               */
/*----------------------------------------------------------------------------*/
#define  MEM_ADDR_START_PTR      ((uint32_t *) 0x00000000)
#define  MEM_ADDR_END_PTR        ((uint32_t *) 0x0017FFFF)

/*----------------------------------------------------------------------------*/
/*   Definition of PML test                                               */
/*----------------------------------------------------------------------------*/
#define START_ADDRESS_OF_PML        0
#define SIZE_OF_PML                             256
#define NULL_CALLBACK            ((void *)0xFFFFFFFF)
#define BASS_ADDRESS START_ADDRESS_OF_PML

/*----------------------------------------------------------------------------*/
/*   Definition of KKSUM test                                               */
/*----------------------------------------------------------------------------*/
#define  KKSUM_START_ADDRESS        (0x00040000)
#define  KKSUM_END_ADDRESS          (0x0017C3FF)
#define  KKSUM_ADDRESS          (0x00160000)

/*----------------------------------------------------------------------------*/
/*   Definition of memory checksum test                                               */
/*----------------------------------------------------------------------------*/
#define  FLASH_START_ADDRESS        (0x00000000)
#define  FLASH_END_ADDRESS          (0x0017FFFF)

/*----------------------------------------------------------------------------*/
/*   Definition of ram test                                               */
/*----------------------------------------------------------------------------*/
#define RAM_START_ADDRESS ((uint32_t)0x40000000)
#define RAM_END_ADDRESS ((uint32_t)0x40001FFF)

#define MG_MCD5412_USED         1
#endif
