#ifndef IO_CONFIG_SWT_H
#define IO_CONFIG_SWT_H


#include "io_config_fmpll.h"
   // Set the watchdog timeout for 400ms during initialization
   //SWT_TO reset value = 0x0013FDE0 giving a timeout period of 32.7544 ms for 8 MHz crystal
#define SWT_TIMEOUT_VALUE_INIT   (400*CRYSTAL_FREQUENCY_HZ/(1000))//r00ms
#define SWT_TIMEOUT_VALUE_NORMAL   (62*CRYSTAL_FREQUENCY_HZ/(1000))//62ms
#endif // IO_CONFIG_SWT_H
