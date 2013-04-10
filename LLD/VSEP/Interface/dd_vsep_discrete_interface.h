#ifndef DD_VSEP_DISCRETE_INTERFACE_H
#define DD_VSEP_DISCRETE_INTERFACE_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_discrete_interface.h~4:incl:mt20u2#2 %
//
// created_by:       fz3pdz
//
// date_created:     Thu Mar  3 23:47:38 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 11:25:38 2007 %
//
// %version:         4 %
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


#include "dd_vsep_discrete.h"
#include "dd_vsep_fault.h"

//extern const Discrete_T VSEP_PCH_DISCRETE_INTERFACE;
#define VSEP_SPIDISCRETE(action,in_configuration,value)  VSEP_Discrete ## action ## (in_configuration, value)


#define VSEP_DiscreteInitialize(in_configuration, value) \
	VSEP_DISCRETE_Channel_Initialize(in_configuration)
	
#define VSEP_DiscreteClear(in_configuration, value) \
	VSEP_DISCRETE_Channel_Clear(in_configuration)
	
#define VSEP_DiscreteSet(in_configuration, value) \
	VSEP_DISCRETE_Set_State(in_configuration, value)
	
#define VSEP_DiscreteSetImmediate(in_configuration, value) \
	VSEP_DISCRETE_Set_Immediate_State(in_configuration, value)	
	
#define VSEP_DiscreteGet(in_configuration, value) \
	VSEP_DISCRETE_Get_State(in_configuration)
	
#define VSEP_DiscreteGetImmediate(in_configuration, value) \
	VSEP_DISCRETE_Get_Immediate_State(in_configuration)
	
#define VSEP_DiscreteToggle(in_configuration) \
	VSEP_DISCRETE_Toggle_State(in_configuration)	
	
#define VSEP_DiscreteToggleImmediate(in_configuration) \
	VSEP_DISCRETE_Toggle_Immediate_State(in_configuration)
	
#define VSEP_DiscreteGet_Fault(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	VSEP_FAULT_Get_OUTPUT_SHORT_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	VSEP_FAULT_Get_OUTPUT_SHORT_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	VSEP_FAULT_Get_OUTPUT_OPEN_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	VSEP_FAULT_Get_OUTPUT_OPEN_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):0))))

#define VSEP_DiscreteClear_Fault(in_configuration, value) \
	(OUTPUT_SHORT_CKT_FAULT == value? \
	VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_SHORT_CKT_TESTED == value? \
	VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_SHORT_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_FAULT == value? \
	VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_FAULT(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):\
	(OUTPUT_OPEN_CKT_TESTED == value? \
	VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]=VSEP_FAULT_Clear_OUTPUT_OPEN_CKT_TESTED(VSEP_Fault_Log[VSEP_Get_Device_Index(in_configuration)][VSEP_Get_Channel(in_configuration)]):0))))
	

#endif // DD_VSEP_DISCRETE_INTERFACE_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
\*===========================================================================*/
