#ifndef V_IGNIT_H
#define V_IGNIT_H
/* ============================================================================ *\
 * v_ignit.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       v_ignit.h-5:incl:mt20a#2
 * Revision:        5
 * Creation date:   Wednesday, October 09, 2002 7:12:50 AM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains ignition voltage virtual I/O
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "reuse.h"
#include "lux_math.h"

/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */
typedef struct {
	bitfield8_t IgnitionIsOn                  : 1 ;
	bitfield8_t IgnitionWasBelow4Volts        : 1 ;
} IgnitionOnStatus_Type ;

typedef uint16_t               Seconds_MedPrec ;
#define Prec_Seconds_MedPrec                  (0.125)
#define Min_Seconds_MedPrec                     (0.0)
#define Max_Seconds_MedPrec            ( 65535*0.125)


/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
extern Volts_B                Ignition_Voltage_B;
extern IgnitionOnStatus_Type  IgnitionOnStatus;
extern Seconds_MedPrec        IgnitionOn_Time;

/* ============================================================================ *\
 * Exported Func.
\* ============================================================================ */
/* should be called in 10ms task */
void UpdateIgnitionState_10MS(void);

/* ============================================================================ *\
 * Exported Macro
\* ============================================================================ */
#define Ignition_Voltage()\
                       (Ignition_Voltage_B)
                       

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
 * 03/03/03     sgchia      106
 * + Boot Loader.
 *   - changed function type.
 *
\* ============================================================================ */
#endif /* V_IGNIT_H */

