//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_fault_interface.c-2:csrc:kok_pt1#1 %
//
// created_by:       fz3pdz
//
// date_created:     Wed Jul 20 16:44:41 2005
//
// %derived_by:      nzdslq %
//
// %date_modified:   Fri Feb 16 11:23:07 2007 %
//
// %version:         2 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

#include "dd_vsep_fault_interface.h"
#include "dd_vsep_fault.h"

void VSEP_Fault_Task_10MS( void )
{
	VSEP_Fault_Diagnose_Channels((void*)VSEP_Fault_Logging);
}
