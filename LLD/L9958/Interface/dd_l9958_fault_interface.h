#ifndef DD_L9958_FAULT_INTERFACE_H
#define DD_L9958_FAULT_INTERFACE_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_fault_interface.h %
//
// created_by:       hz23l2
//
// date_created:     Wed Apr 04 11:15:09 2007
//
// %derived_by:       wzmkk7 %
//
// %date_modified:    %
//
// %version:         mt20u2#2 %
//
//=============================================================================

#include "fault.h"
#include "dd_l9958_fault.h"
#include "hal.h"

//=============================================================================
// L9958 Interface structures
//=============================================================================
extern const Fault_Interface_T L9958_FAULT_INTERFACE;

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
#define L9958_SPIDiag(action,in_configuration,value)\
        L9958_SPIFault ## action ## (in_configuration, value)
	
// Extract L9958 fault flag
#define L9958_SPIFaultGet(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	L9958_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(L9958_Fault_Log[0]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	L9958_FAULT_Get_OUTPUT_SHORT_CKT_TESTED(L9958_Fault_Log[0]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	L9958_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(L9958_Fault_Log[0]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	L9958_FAULT_Get_OUTPUT_OPEN_CKT_TESTED(L9958_Fault_Log[0]):0))))

// Reset L9958 fault flag
#define L9958_SPIFaultClear(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	L9958_Fault_Log[0]=L9958_FAULT_Clear_OUTPUT_SHORT_CKT_FAULT(L9958_Fault_Log[0]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	L9958_Fault_Log[0]=L9958_FAULT_Clear_OUTPUT_SHORT_CKT_TESTED(L9958_Fault_Log[0]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	L9958_Fault_Log[0]=L9958_FAULT_Clear_OUTPUT_OPEN_CKT_FAULT(L9958_Fault_Log[0]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	L9958_Fault_Log[0]=L9958_FAULT_Clear_OUTPUT_OPEN_CKT_TESTED(L9958_Fault_Log[0]):0))))


#endif // DD_L9958_FAULT_INTERFACE_H
