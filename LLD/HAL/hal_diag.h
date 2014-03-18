#ifndef HAL_DIAG_H
#define HAL_DIAG_H
/* ============================================================================ *\
 * hal_diag.h
 * ============================================================================
 * Copyright 1999,2004 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       hal_diag.h
 * Revision:        1
 * Creation date:
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   Hardware test software - PSVI diagnostic test.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "reuse.h"
#include "hal.h"
#include "dd_vsep_fault_config.h"
#include "dd_vsep_fault.h"


/******************************************************************************
 * To test injectors A,B,C,D 
 ******************************************************************************/
#define InjectorAFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_A))
#define InjectorAShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_A))
#define InjectorAShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_A))

#define InjectorBFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_B))
#define InjectorBShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_B))
#define InjectorBShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_B))

#define InjectorCFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_C))
#define InjectorCShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_C))
#define InjectorCShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_C))

#define InjectorDFault()            (GetAnyFault(PULSE_OUT_INJ_CYL_D))
#define InjectorDShortHi()          (GetShortFault(PULSE_OUT_INJ_CYL_D))
#define InjectorDShortLo()          (GetOpenFault(PULSE_OUT_INJ_CYL_D))

#define GetOpenFault(function)      (DD_GetDiscreteDiagStatus(function,OUTPUT_OPEN_CKT_FAULT))
#define GetShortFault(function)     (DD_GetDiscreteDiagStatus(function,OUTPUT_SHORT_CKT_FAULT))
#define GetAnyFault(function)       (GetOpenFault(function) || GetShortFault(function))

/******************************************************************************
 * FUEL PUMP
 ******************************************************************************/
#define GetFuelPump_ShortHi()        (DD_GetDiscreteDiagStatus(DISCRETE_OUT_FUEL_PUMP,OUTPUT_SHORT_CKT_FAULT))
#define GetFuelPump_Open()           (DD_GetDiscreteDiagStatus(DISCRETE_OUT_FUEL_PUMP,OUTPUT_OPEN_CKT_FAULT))

/******************************************************************************
 * AC CLUTCH
 ******************************************************************************/
#define GetAcClutch_ShortFault() (DD_GetDiscreteDiagStatus(DISCRETE_OUT_AC_CLUTCH,OUTPUT_SHORT_CKT_FAULT))
#define GetAcClutch_OpenFault()  (DD_GetDiscreteDiagStatus(DISCRETE_OUT_AC_CLUTCH,OUTPUT_OPEN_CKT_FAULT))

/******************************************************************************
 * TPIC Fault reading for AcClutch diagnostic 
 ******************************************************************************/
#define GetVIOS_ACCD_FaultShortHi()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_AC_CLUTCH,OUTPUT_SHORT_CKT_FAULT))
#define GetVIOS_ACCD_FaultShortLo()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_AC_CLUTCH,OUTPUT_OPEN_CKT_FAULT))
#define GetVIOS_ACCD_FaultAny()        (GetVIOS_ACCD_FaultShortHi() ||\
                                            GetVIOS_ACCD_FaultShortLo() )
#define GetVIOS_ACCD_Presnt()              (true)//(AcFlags.AcPresent)

/******************************************************************************
 * TPIC Fault reading for Main Power Relay diagnostic 
 ******************************************************************************/
#define GetVIOS_MPRD_FaultShortHi()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_MAINRLY,OUTPUT_SHORT_CKT_FAULT))
#define GetVIOS_MPRD_FaultShortLo()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_MAINRLY,OUTPUT_OPEN_CKT_FAULT))
#define GetVIOS_MPRD_FaultAny()        (GetVIOS_MPRD_FaultShortHi()||GetVIOS_MPRD_FaultShortLo() )
#define GetVIOS_MPRD_Presnt()              (true)//(IsMPRPresent())


/******************************************************************************
 * TPIC Fault reading for Fuel Pump Relay diagnostic 
 ******************************************************************************/
#define GetVIOS_FPRD_FaultShortHi()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_FUEL_PUMP,OUTPUT_SHORT_CKT_FAULT))
#define GetVIOS_FPRD_FaultShortLo()    (DD_GetDiscreteDiagStatus(DISCRETE_OUT_FUEL_PUMP,OUTPUT_OPEN_CKT_FAULT))
#define GetVIOS_FPRD_FaultAny()        (GetVIOS_FPRD_FaultShortHi() ||\
                                            GetVIOS_FPRD_FaultShortLo())
#define GetVIOS_FPRD_Presnt()              (CbTRUE)

/******************************************************************************
 * TPIC Fault reading for FAN1 diagnostic 
 ******************************************************************************/
#define GetVIOS_FANA_FaultShortHi()    (GetShortFault(DISCRETE_OUT_FAN_1))
#define GetVIOS_FANA_FaultShortLo()    (GetOpenFault(DISCRETE_OUT_FAN_1))
#define GetVIOS_FANA_FaultAny()        (GetAnyFault(DISCRETE_OUT_FAN_1))
#define GetVIOS_FANA_Presnt()              (true)//(FanPresentFlags.bf.Fan1Present)

/******************************************************************************
 * TPIC Fault reading for FAN2 diagnostic 
 ******************************************************************************/
#define GetVIOS_FANB_FaultShortHi()    (GetShortFault(DISCRETE_OUT_FAN_2))
#define GetVIOS_FANB_FaultShortLo()    (GetOpenFault(DISCRETE_OUT_FAN_2))
#define GetVIOS_FANB_FaultAny()        (GetAnyFault(DISCRETE_OUT_FAN_2))
#define GetVIOS_FANB_Presnt()              (true)//(FanPresentFlags.bf.Fan2Present)


/******************************************************************************
 * PSVI Fault reading for MIL Lamp diagnostic 
 ******************************************************************************/
#define GetVIOS_MILD_FaultShortHi()    (GetShortFault(DISCRETE_OUT_OBD2_LAMP))
#define GetVIOS_MILD_FaultShortLo()    (GetOpenFault(DISCRETE_OUT_OBD2_LAMP))
#define GetVIOS_MILD_FaultAny()        (GetAnyFault(DISCRETE_OUT_OBD2_LAMP))
#define GetVIOS_MILD_Presnt()              (CbTRUE)

/******************************************************************************
 * PSVI Fault reading for GIS Lamp diagnostic 
 ******************************************************************************/
#define GetVIOS_GISD_FaultShortHi()    (GetShortFault(DISCRETE_OUT_VIS_OUTPUT1))
#define GetVIOS_GISD_FaultShortLo()    (GetOpenFault(DISCRETE_OUT_VIS_OUTPUT1))
#define GetVIOS_GISD_FaultAny()        (GetAnyFault(DISCRETE_OUT_VIS_OUTPUT1))
#define GetVIOS_GISD_Presnt()              (CbTRUE)

/******************************************************************************
 * PSVI Fault reading for MIL Lamp diagnostic 
 ******************************************************************************/
#define GetVIOS_SVSD_FaultShortHi()    (GetShortFault(DISCRETE_OUT_SES_LAMP))
#define GetVIOS_SVSD_FaultShortLo()    (GetOpenFault(DISCRETE_OUT_SES_LAMP))
#define GetVIOS_SVSD_FaultAny()        (GetAnyFault(DISCRETE_OUT_SES_LAMP))
#define GetVIOS_SVSD_Presnt()              (CbTRUE)

/******************************************************************************
 * PSVI Fault reading for CCP diagnostic 
 ******************************************************************************/
#define GetHWIO_PurgeSolOutputFault()        (GetAnyFault(PULSE_OUT_CANISTER_PURGE))
#define GetHWIO_PurgeSolOutputFaultShortLo() (GetOpenFault(PULSE_OUT_CANISTER_PURGE))
#define GetHWIO_PurgeSolOutputFaultShortHi() (GetShortFault(PULSE_OUT_CANISTER_PURGE))

#define GetVIOS_O2_11_Htr_PSVIFaultShortHi()\
   ( DD_GetDiscreteDiagStatus(PULSE_OUT_O2_HEATER_11,OUTPUT_SHORT_CKT_FAULT) )
#define GetVIOS_O2_11_Htr_PSVIFaultShortLow()\
   ( DD_GetDiscreteDiagStatus(PULSE_OUT_O2_HEATER_11,OUTPUT_OPEN_CKT_FAULT) )
#define GetVIOS_O2_12_Htr_PSVIFaultShortHi()\
   ( DD_GetDiscreteDiagStatus(PULSE_OUT_O2_HEATER_12,OUTPUT_SHORT_CKT_FAULT) )
#define GetVIOS_O2_12_Htr_PSVIFaultShortLow()\
   ( DD_GetDiscreteDiagStatus(PULSE_OUT_O2_HEATER_12,OUTPUT_OPEN_CKT_FAULT) )

/******************************************************************************
 * PSVI Fault reading for VVT diagnostic 
 ******************************************************************************/
#define GetHWIO_VVT1OutputFault()        (GetAnyFault(PULSE_OUT_VCPS_B1_INTK))
#define GetHWIO_VVT1OutputFaultShortLo() (GetOpenFault(PULSE_OUT_VCPS_B1_INTK))
#define GetHWIO_VVT1OutputFaultShortHi() (GetShortFault(PULSE_OUT_VCPS_B1_INTK))

#define GetHWIO_VVT2OutputFault()        (GetAnyFault(PULSE_OUT_VCPS_B1_EXH))
#define GetHWIO_VVT2OutputFaultShortLo() (GetOpenFault(PULSE_OUT_VCPS_B1_EXH))
#define GetHWIO_VVT2OutputFaultShortHi() (GetShortFault(PULSE_OUT_VCPS_B1_EXH))

/******************************************************************************
 * IO Diagnostic Clear
 ******************************************************************************/
#define Clear_IO_Pulse_Diag_EST_A( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_EST_A,diagnostic)

#define Clear_IO_Pulse_Diag_EST_B( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_EST_B,diagnostic)

#define Clear_IO_Pulse_Diag_EST_C( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_EST_C,diagnostic)

#define Clear_IO_Pulse_Diag_EST_D( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_EST_D,diagnostic)

#define Clear_IO_Pulse_Diag_INJ_CYL_A( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_INJ_CYL_A,diagnostic)

#define Clear_IO_Pulse_Diag_INJ_CYL_B( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_INJ_CYL_B,diagnostic)

#define Clear_IO_Pulse_Diag_INJ_CYL_C( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_INJ_CYL_C,diagnostic)

#define Clear_IO_Pulse_Diag_INJ_CYL_D( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_INJ_CYL_D,diagnostic)

#define Clear_IO_PWM_Diag_Turbo_BPR( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_TURBBPR,diagnostic)

#define Clear_IO_PWM_Diag_Turbo_VGT( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_TURBVGT,diagnostic)

#define Clear_IO_PWM_Diag_AIR_PUMP_SPEED( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_AIR_PUMP_SPEED,diagnostic)

#define Clear_IO_PWM_Diag_SS_ALTERNATOR_OUTPUT_PWM( diagnostic ) \
					DD_ClearDiscreteDiagStatus(PULSE_OUT_SS_ALTERNATOR_OUTPUT_PWM,diagnostic)

#define Clear_IO_PWM_Diag_CANISTER_PURGE( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_CANISTER_PURGE,diagnostic)

#define Clear_IO_PWM_Diag_COOL_TEMP_PWM( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_COOL_TEMP_PWM,diagnostic)

#define Clear_IO_PWM_Diag_FAN_PWM( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_FAN_PWM,diagnostic)

#define Clear_IO_PWM_Diag_LINEAR_EGR( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_LINEAR_EGR,diagnostic) //Added by czh2h9 on Jun 09 2009

#define Clear_IO_PWM_Diag_O2_HEATER_11( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_O2_HEATER_11,diagnostic)

#define Clear_IO_PWM_Diag_O2_HEATER_12( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_O2_HEATER_12,diagnostic)

#define Clear_IO_PWM_Diag_VCPS_B1_EXH( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_VCPS_B1_EXH,diagnostic)

#define Clear_IO_PWM_Diag_VCPS_B1_INTK( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_VCPS_B1_INTK,diagnostic)

#define Clear_IO_PWM_Diag_WG_PWM( diagnostic ) \
				DD_ClearDiscreteDiagStatus(PULSE_OUT_TURBO_WG_PWM,diagnostic)

#define Clear_IO_Discrete_Diag_AC_CLUTCH( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_AC_CLUTCH,diagnostic)

#define Clear_IO_Discrete_Diag_CRUISE_ACTIVE_LAMP( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_CRUISE_ACTIVE_LAMP,diagnostic)
	
#define Clear_IO_Discrete_Diag_SS_WARNING_LAMP( diagnostic ) \
					DD_ClearDiscreteDiagStatus(DISCRETE_OUT_SS_WARNING_LAMP,diagnostic)

#define Clear_IO_Discrete_Diag_AIR_VALVE( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_AIR_VALVE,diagnostic)

#define Clear_IO_Discrete_Diag_FAN_1( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_FAN_1,diagnostic)

#define Clear_IO_Discrete_Diag_VIS_OUTPUT1( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_VIS_OUTPUT1,diagnostic)

#define Clear_IO_Discrete_Diag_VIS_OUTPUT2( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_VIS_OUTPUT2,diagnostic)

#define Clear_IO_Discrete_Diag_StarerRelay( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_SS_STARTER_RELAY,diagnostic)

#define Clear_IO_Discrete_Diag_FAN_2( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_FAN_2,diagnostic)

#define Clear_IO_Discrete_Diag_FUEL_PUMP( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_FUEL_PUMP,diagnostic)

#define Clear_IO_Discrete_Diag_MAINRLY( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_MAINRLY,diagnostic)

#define Clear_IO_Discrete_Diag_OBD2_LAMP( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_OBD2_LAMP,diagnostic)

#define Clear_IO_Discrete_Diag_SES_LAMP( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_SES_LAMP,diagnostic)

#define Clear_IO_Discrete_Diag_SS_Cluster_TT_Disable( diagnostic ) \
				DD_ClearDiscreteDiagStatus(DISCRETE_OUT_SS_CLUSTER_TT_DISABLE,diagnostic)
 

uint16_t HAL_Diag_Get_L9958_HWDiag_Status(void);
 
#endif
