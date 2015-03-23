#ifndef HAL_MEMORY_H
#define HAL_MEMORY_H

#include "io_type.h"

typedef struct
{
    uint16_t * VpHWIO_MemSegmentStartAddress;
    uint16_t * VpHWIO_MemSegmentEndAddress;
} TsMEMORY_SEGMENT_POINTERS;

extern const TsMEMORY_SEGMENT_POINTERS const IO_MEM_ROM_Block_Checksum[];

#endif /* HAL_MEMORY_H */
