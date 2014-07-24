#ifndef HAL_UCRAM_H
#define HAL_UCRAM_H

#include "reuse.h"

typedef struct HAL_UNCLEARED_RAM_Tag 
{
   volatile uint8_t bootblock[4]; // refer to bootblock, data[0] - Running reset counter, data[1] - Reason of stay in boot
   volatile uint8_t reset_exception_pattern;
   volatile uint8_t reset_reason;
   volatile uint8_t data[10];
} HAL_UNCLEARED_RAM_T; // 16bytes are reserved

extern HAL_UNCLEARED_RAM_T HAL_uncleard_ram;

/* this flag is used to indicate whether the inca re-flash was operated */
#define NCRAM_REPROGRAM_FLAG 15


#endif /* end of include guard: HAL_UCRAM_H */
