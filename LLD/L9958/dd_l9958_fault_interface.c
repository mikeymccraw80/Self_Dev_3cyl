//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_fault_interface.c %
//
// created_by:       hz23l2
//
// date_created:     Wed Apr 04 11:15:09 2007
//
// %derived_by:       jznxv7 %
//
// %date_modified:    %
//
// %version:         1 %
//
//=============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================
#include "dd_l9958_fault_interface.h"
#include "dd_L9958_fault.h"

#ifndef OVERLOAD_L9958_FAULT_INTERFACE
const Fault_Interface_T L9958_FAULT_INTERFACE =
{
   L9958_FAULT_Get_Device_Fault,
   L9958_FAULT_Clear_Device_Fault,
   0 //DEFAULT_FAULT_Diagnose_Device_Fault
};

#endif
