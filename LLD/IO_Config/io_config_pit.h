
#ifndef IO_CONFIG_PIT_H
#define IO_CONFIG_PIT_H

#include "io_config_fmpll.h"



//=============================================================================
// PIT Scaling
//=============================================================================
#define RTI_INTERNAL_VALUE_1MS    1

#define PIT_CLOCK_FREQUENCY_HZ (SYSTEM_FREQUENCY_HZ)
#define RTI_CLOCK_FREQUENCY_HZ (CRYSTAL_FREQUENCY_HZ)

#define RTI_LOAD_VALUE_1MS                 (RTI_INTERNAL_VALUE_1MS*1000.0/ ( 1000000.0/RTI_CLOCK_FREQUENCY_HZ  ) ) //10ms                               

#endif //IO_CONFIG_PIT_H
