#ifndef DD_MMU_INTERFACE_H
#define DD_MMU_INTERFACE_H


#include "dd_mmu.h"


//=============================================================================
// MMU_MAS_Initialize_Device
//
// @func Initialize the MMU MAS registers based on the configurations defined by
// the user.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void MMU_MAS_Initialize_Device( void );


#endif // DD_MMU_H

