#ifndef DD_L9958_FAULT_H
#define DD_L9958_FAULT_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_fault.h %
//
// created_by:       hz23l2
//
// date_created:     wed Mar 28 13:04:55 2007
//
// %derived_by:      jznxv7 %
//
// %date_modified:   %
//
// %version:         1 %
//
// ============================================================================
// @doc
//
// @module discrete.h | Discrete interface definition file
//
// The purpose of this module is to provide application to access discrete I/O
// functions in a particular format. 
//
// @end
//
//=============================================================================
#include "dd_l9958.h"
#include "dd_l9958_txd.h"

#include "fault.h"
//=============================================================================
// Diag Register (Fault) Bit Definitions
//
// Bit   Name       Description                       Reset Val
// ===   ======    =============================   ============================
//  0   OL_OFF      Open Load in OFF condition          0
//  1   OL_ON       Open Load in ON condition           0
//  2   VS_UV       Vs undervoltage                     0
//  3   VDD_OV      Vdd overvoltage                     0
//  4   ILIM        Current Limitation reached          0
//  5   TWARN       Temperature Warning                 0
//  6   TSD         Over-temperature Shutdown           0
//  7   ACT         Bridge enable                       1
//  8   OC_LS1      Over-Current on Low Side1           0
//  9   OC_LS2      Over-Current on Low Side2           0
// 10   OC_HS1      Over-Current on High Side1          0
// 11   OC_HS2      Over-Current on High Side2          0
// 12   Null        Not Used ---
// 13   Null        Not Used ---
// 14   SGND_OFF    Short to GND in OFF condition       0
// 15   SBAT_OFF    Short to Battery in OFF condition   0
//=============================================================================

typedef enum
{
	L9958_OPEN_LOAD_IN_OFF     = 0x1,
	L9958_OPEN_LOAD_IN_ON      = 0x2,
	L9958_VS_UNDER_VOLTAGE     = 0x4,
	L9958_VDD_OVER_VOLTAGE     = 0x8,
	L9958_CURR_LIM_REACHED     = 0x10,
	L9958_TEMP_WARNING         = 0x20,
	L9958_OVER_TEMP_SHUTDOWN   = 0x40,
	L9958_BRIDGE_ENABLE        = 0x80,
	L9958_OVER_CURR_LO_SIDE1   = 0x100,
	L9958_OVER_CURR_LO_SIDE2   = 0x200,
	L9958_OVER_CURR_HI_SIDE1   = 0x400,
	L9958_OVER_CURR_HI_SIDE2   = 0x800,
	L9958_NOT_USED1            = 0x1000,
	L9958_NOT_USED2            = 0x2000,
	L9958_SHORT_TO_GND_IN_OFF  = 0x4000,
	L9958_SHORT_TO_BAT_IN_OFF  = 0x8000
}L9958_Fault_Status_T;

//=============================================================================
// L9958_FAULT_Initialize_Device
//
// @func Initializes faults on a requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void L9958_FAULT_Initialize_Device(void);

//=============================================================================
// L9958_FAULT_Get_Device_Fault
//
// @func Get the status of any fault on the requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc Return true if there is any fault on the device.
//
// @end
//=============================================================================
bool L9958_FAULT_Get_Device_Fault(void);

//=============================================================================
// L9958_FAULT_Clear_Device_Fault
//
// @func Clears all faults on a requested device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void L9958_FAULT_Clear_Device_Fault(void);

//=============================================================================
// L9958_FAULT_Diagnose_Update
//
// @func Diagnose the output pins for the specified L9958.  Diagnostics collected
//       are based on the state of the output pin.  Fault data returned by the
//       SPI message.  This function is called in the ExecuteAfter 
//       function of the SPI message.
//
// @parm IO_Configuration_T | in_configuration | Specifies which output on which
//       L9958 in the system to diagnose
//
// @parm bool      | in_parallel | Specifies the state of the parallel input
//       associated with the specified output to be diagnosed.
//
// @rdesc none
//
// @end
//=============================================================================
uint16_t L9958_FAULT_Diagnose_Update(void);

extern Fault_Log_T L9958_Fault_Log;

#endif // DD_L9958_FAULT_H
