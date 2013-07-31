#ifndef DD_L9958_FAULT_INTERFACE_H
#define DD_L9958_FAULT_INTERFACE_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//=============================================================================
#include "fault.h"
#include "dd_l9958_fault.h"
#include "dd_l9958.h"

//=============================================================================
// L9958 Interface structures
//=============================================================================

// L9958 interface to extract common fault flag
#define L9958_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(x) \
	FAULT_Get_Occured_Short_To_Battery(x)
#define L9958_FAULT_Get_OUTPUT_SHORT_CKT_TESTED(x) \
	FAULT_Get_Tested_Short_To_Battery(x)
#define L9958_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(x) \
	(FAULT_Get_Occured_Open_Circuit(x)||FAULT_Get_Occured_Short_To_Ground(x))
#define L9958_FAULT_Get_OUTPUT_OPEN_CKT_TESTED(x) \
	(FAULT_Get_Tested_Open_Circuit(x)||FAULT_Get_Tested_Short_To_Ground(x))

// L9958 interface to reset common fault flag
#define L9958_FAULT_Clear_OUTPUT_SHORT_CKT_FAULT(x) \
	FAULT_Set_Occured_Short_To_Battery(x,false) 
#define L9958_FAULT_Clear_OUTPUT_SHORT_CKT_TESTED(x) \
	 FAULT_Set_Tested_Short_To_Battery(x,false)
#define L9958_FAULT_Clear_OUTPUT_OPEN_CKT_FAULT(x) \
	(FAULT_Clear_Occured_Open_Circuit(x)&FAULT_Clear_Occured_Short_To_Ground(x))
#define L9958_FAULT_Clear_OUTPUT_OPEN_CKT_TESTED(x) \
	(FAULT_Clear_Tested_Open_Circuit(x)&FAULT_Clear_Tested_Short_To_Ground(x))


// L9958 diagnostic interface
// EMS_DIAGNOSTIC_T : value
#define L9958_SPIDiag(action,value)\
	L9958_SPIFault ## action ## (value)

// Extract L9958 fault flag
// EMS_DIAGNOSTIC_T : value
#define L9958_SPIFaultGet(value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	L9958_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(L9958_Fault_Log):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	L9958_FAULT_Get_OUTPUT_SHORT_CKT_TESTED(L9958_Fault_Log):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	L9958_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(L9958_Fault_Log):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	L9958_FAULT_Get_OUTPUT_OPEN_CKT_TESTED(L9958_Fault_Log):0))))

// Reset L9958 fault flag
// EMS_DIAGNOSTIC_T : value
#define L9958_SPIFaultClear(value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	L9958_Fault_Log=L9958_FAULT_Clear_OUTPUT_SHORT_CKT_FAULT(L9958_Fault_Log):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	L9958_Fault_Log=L9958_FAULT_Clear_OUTPUT_SHORT_CKT_TESTED(L9958_Fault_Log):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	L9958_Fault_Log=L9958_FAULT_Clear_OUTPUT_OPEN_CKT_FAULT(L9958_Fault_Log):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	L9958_Fault_Log=L9958_FAULT_Clear_OUTPUT_OPEN_CKT_TESTED(L9958_Fault_Log):0))))

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
void L9958_FAULT_Diagnose_Update(void);

uint16_t L9958_FAULT_Get_HWDiag_Status(void);

#endif // DD_L9958_FAULT_INTERFACE_H
