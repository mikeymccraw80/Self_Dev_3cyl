
#ifndef IO_CONFIG_STM_H
#define IO_CONFIG_STM_H

//=============================================================================
// include files
//=============================================================================
#include "io_config_fmpll.h"
#include "dd_stm.h"

//=============================================================================
//define
//=============================================================================
#define STM_CLOCK_PRESCALER  ( 0 )
#define STM_CLOCK_FREQUENCY_HZ   ( (SYSTEM_FREQUENCY_HZ)/(STM_CLOCK_PRESCALER+1) )

//=============================================================================
// STM configuration
//=============================================================================
extern const STM_CR_T STM_CR_INITIAL ;

#endif //IO_CONFIG_STM_H

