/* ============================================================================ *\
 * v_power.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       v_power.c-5:incl:ctc_mt20u2
 * Revision:        1
 * Creation date:   Wednesday, August 17, 2005 9:10:31 AM
 * Last changed:    Mon Nov 29 13:21:33 2010
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains power source condition for components
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */
#include "v_power.h"
#include "hwiocald.h"
#include "v_ignit.h"
#include "intr_ems.h"
#include "hal_gpio.h"
#include "lux_math.h"
#include "reuse.h"


/******************* Global Variables **************/
bool               PowerSource_Status[4];
PowerStatusType    APPPowerStatus;


/******************* Local Variables **************/
static Every_Loop_Sec_B   FPRPowerSrc_DelayTimer;
static Every_Loop_Sec_B   MPRPowerSrc_DelayTimer;

/******************* Local Const **************/
static const Every_Loop_Sec_B CcFPRPowerSrc_Delay = FixDefConst(1.2, Every_Loop_Sec_B);
static const Every_Loop_Sec_B CcMPRPowerSrc_Delay = FixDefConst(1.2, Every_Loop_Sec_B);

/*********************************************************************/
/*  Local Function                                                   */
/*********************************************************************/
static void UpdatePowerSrcStatus( void );

static bool GetMPRStatus(void)
{
	return ((HAL_GPIO_GET_MPR_Status()) && !GetVIOS_MPRD_FaultAny());
}

static bool GetVIOS_FuelPumpRly_Status(void)
{
	return ((HAL_GPIO_GET_FPR_Status()) && !GetVIOS_FPRD_FaultAny());
}


/*********************************************************************/
/*  This function updates Power Source status.                       */
/*********************************************************************/
static void UpdatePowerSrcStatus( void )
{
	PowerSource_Status[IgnitionON] = (bool)IgnitionOnStatus.IgnitionIsOn;

	/*  MPR as power source  */
	if ( GetMPRStatus() && (MPRPowerSrc_DelayTimer > CcMPRPowerSrc_Delay))
	{
		PowerSource_Status[MainPowerRelay] = true ;    /*  Main Power Relay   */
	} else if (!GetMPRStatus()) {
		MPRPowerSrc_DelayTimer = 0;
		PowerSource_Status[MainPowerRelay] = false ;
	} else {
		MPRPowerSrc_DelayTimer++;
	}

	/*  FPR as power source  */
	if (GetVIOS_FuelPumpRly_Status() && (FPRPowerSrc_DelayTimer > CcFPRPowerSrc_Delay)) {
		PowerSource_Status[FuelPumpRelay] = true;    /*  Fuel Pump Relay    */
	} else if (!GetVIOS_FuelPumpRly_Status()) {
		FPRPowerSrc_DelayTimer = 0;
		PowerSource_Status[FuelPumpRelay] = false ;
	} else {
		FPRPowerSrc_DelayTimer++;
	}

}


/******************************************************************************/
/*                                                                            */
/* FUNCTION: InitializePowerSource()                                       */
/*                                                                            */
/* DESCRIPTION: Initialize Power Source related variables                              */
/*                                                                            */
/* GLOBAL:                                                                    */
/*                                                                            */
/******************************************************************************/
void InitializePowerSource(void)
{
	FPRPowerSrc_DelayTimer = 0;
	MPRPowerSrc_DelayTimer = 0;

	PowerSource_Status[Battery] = true;          /*  Battery            */
	PowerSource_Status[IgnitionON] = false;      /*  Ignition           */
	PowerSource_Status[MainPowerRelay] = false;  /*  Main Power Relay   */
	PowerSource_Status[FuelPumpRelay] = false;   /*  Fuel Pump Relay    */

	APPPowerStatus.Word       = 0;
}


/******************************************************************************/
/*                                                                            */
/* FUNCTION: VirHW_Reading_EveryLoop()                                       */
/*                                                                            */
/* DESCRIPTION: Read Calibratable Discrete Input                              */
/*                                                                            */
/* GLOBAL:                                                                    */
/* Execution Rate :  8ms                                                 */
/*                                                                            */
/******************************************************************************/
void PowerSourceStatus_EveryLoop(void)
{
	UpdatePowerSrcStatus();

	APPPowerStatus.Bits.FPR       = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_FPR);
	APPPowerStatus.Bits.CCP       = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_CCP);
	APPPowerStatus.Bits.FANA      = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_FANA);
	APPPowerStatus.Bits.FANB      = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_FANB);
	APPPowerStatus.Bits.ACClutch  = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_ACClutch);
	APPPowerStatus.Bits.SparkCoil = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_SparkCoil);
	APPPowerStatus.Bits.O2Heater  = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_O2Heater);
	APPPowerStatus.Bits.Injector  = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_Injector);
 	APPPowerStatus.Bits.ETC  = (bitfield16_t) GetVIOS_PowerOK(K_PowerConfig_ETC);
}

/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */
