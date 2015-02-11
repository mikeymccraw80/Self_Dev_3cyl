#ifndef DD_KP254_FAULT_H
#define DD_KP254_FAULT_H

#include "dd_kp254.h"

typedef enum KP254_FAULT_TYPE
{
    FEC_ERROR = 0x10,
    DIAG1 = 0x08,
    DIAG2 = 0x04,
    PRESSURE_RANGE_HIGH = 0x02,
    PRESSURE_RANGE_LOW = 0x01,
    NO_ERROR = 0x0A
} KP254_FAULT_T;

//=============================================================================
// KP254_FAULT_Get_Device_Fault
//
// @func Returns the bit if there is a requested fault type on any KP254 FAULT log
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc if there are any faults on the device.
//
// @end
//=============================================================================
bool  KP254_FAULT_Get_Device_Fault(
   IO_Configuration_T in_configuration );

//=============================================================================
// KP254_FAULT_Clear_Device_Fault
//
// @func Clears a requested fault type on any KP254 FAULT log
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void KP254_FAULT_Clear_Device_Fault(
   IO_Configuration_T in_configuration );

//=============================================================================
// KP254_FAULT_Diagnose_Device_Fault
//
// @func Diagnose the specified output pin for the specified KP254.  Diagnostics
//       collected are based on the state of the output pin.  Fault data returned
//       by the SPI message is decoded as testing for Open faults if the output
//       pin is Low, and for Short faults if the output pin is High.  This
//       function is is called in the ExecuteAfter function of the SPI message.
//
// @parm IO_Configuration_T | in_configuration | Specifies which output on which
//       C2PS in the system to diagnose
//
// @end
//=============================================================================
void KP254_FAULT_Diagnose_Device_Fault(
   IO_Configuration_T   in_configuration );

//=============================================================================
// KP254_FAULT_Get_Device_Fault
//
// @func Returns the type of a requested fault type on any KP254 FAULT log
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc if there are any faults on the device.
//
// @end
//=============================================================================
KP254_FAULT_T KP254_FAULT_Get_Device_Fault_Type(
   IO_Configuration_T   in_configuration );
#endif
