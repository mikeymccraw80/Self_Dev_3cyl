#ifndef DD_KP254_ANALOG_H
#define DD_KP254_ANALOG_H

//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_kp254_analog.h %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      zzrfyj %
//
// %date_modified:       %
//
// %version:         1 %
//
//=============================================================================
#include "io_type.h"

//=============================================================================
// KP254_ANALOG_Get_Buffered_Value
//
// @func
//
// @parm IO_Configuration | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc 
//
// @end
//=============================================================================
uint16_t KP254_ANALOG_Get_Buffered_Value(
   IO_Configuration_T in_configuration );

//=============================================================================
// KP254_ANALOG_Get_Immediate_Value
//
// @func
//
// @parm IO_Configuration | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc 
//
// @end
//=============================================================================
uint16_t KP254_ANALOG_Get_Immediate_Value(
   IO_Configuration_T in_configuration );


#endif /* end of include guard: DD_KP254_ANALOG_H */
