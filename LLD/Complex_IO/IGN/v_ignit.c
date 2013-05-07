/* ============================================================================ *\
 * v_ignit.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       v_ignit.c-5:csrc:mt20a#2
 * Revision:        5
 * Creation date:   Tuesday, July 16, 2002 3:12:14 PM
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
#include "v_ignit.h"
#include "hal_analog.h"

/******************* Global Variables **************/
Volts_B                         Ignition_Voltage_B;
IgnitionOnStatus_Type           IgnitionOnStatus;
Seconds_MedPrec                 IgnitionOn_Time;
Every_Loop_Sec_B                Timer_125ms_Mark;


/* ============================================================================ *\
 * Update_IgnitionOn_Time
\* ============================================================================ */
static void Update_IgnitionOn_Time( void )
{
	/*--- Every 0.125 second, do: ---*/
	if (Timer_125ms_Mark == FixDefConst( 0.125, Every_Loop_Sec_B )) {
		Inc(IgnitionOn_Time);
		Timer_125ms_Mark = FixDefConst(0.0, Every_Loop_Sec_B);
	} else {
		Timer_125ms_Mark++;
	}
}


/**************************************************************************/
/*                                                                        */
/* FUNCTION: UpdateIgnitionState                                            */
/*                                                                        */
/* DESCRIPTION:                                                           */
/*    updates the Ignition Status                                            */
/*                                                                        */
/* GLOBAL: Nil.                                                           */
/**************************************************************************/
void UpdateIgnitionState( void )
{
	uint16_t v_ign_value;
	v_ign_value = HAL_Analog_Get_IGNVI_Value();
	/* Update ignition voltage */
	Ignition_Voltage_B = FixConvert(v_ign_value, Volts_Plus_Fraction, Volts_B ) ;

	if ( Ignition_Voltage_B < FixDefConst( 4.0, Volts_B ) )
	{
		IgnitionOnStatus.IgnitionWasBelow4Volts = ( bitfield8_t )true ;
		IgnitionOnStatus.IgnitionIsOn = ( bitfield8_t )false ;
		IgnitionOn_Time = FixDefConst(0.0, Seconds_MedPrec);
	}
	else if ( ( IgnitionOnStatus.IgnitionWasBelow4Volts == ( bitfield8_t )false ) ||
			 ( Ignition_Voltage_B > FixDefConst(9.0, Volts_B) ) )
	{
		IgnitionOnStatus.IgnitionWasBelow4Volts = ( bitfield8_t )false ;
		IgnitionOnStatus.IgnitionIsOn = ( bitfield8_t )true ;
		Update_IgnitionOn_Time();
	}
	else
	{
		// nothing
	}
}


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 10/10/02     ndboer      -
 * + Baseline - Created from P2003AXZ02.
 *
\* ============================================================================ */

