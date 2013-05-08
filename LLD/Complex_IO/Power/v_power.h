#ifndef V_POWER_H
#define V_POWER_H
/* ============================================================================ *\
 * v_power.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       v_power.h-5:incl:ctc_mt20u2
 * Revision:        1
 * Creation date:   Wednesday, August 17, 2005 9:10:31 AM
 * Last changed:    Mon Nov 29 13:37:46 2010
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

#include "reuse.h"
#include "HLS.h"


/* ============================================================================ *\
 * Local type definition.
\* ============================================================================ */
typedef enum {
	Battery,
	IgnitionON,
	MainPowerRelay,
	FuelPumpRelay
} PowerSourceType;

typedef enum {
	Battery_FPR,
	IgnitionON_FPR,
	MainPowerRelay_FPR
} PowerSource_FPR_Type;


typedef union {
	struct {
		bitfield16_t FPR             : 1 ;
		bitfield16_t CCP             : 1 ;
		bitfield16_t FANA            : 1 ;
		bitfield16_t FANB            : 1 ;
		bitfield16_t ACClutch        : 1 ;
		bitfield16_t SparkCoil       : 1 ;
		bitfield16_t O2Heater        : 1 ;
		bitfield16_t Injector        : 1 ;
		bitfield16_t NotUsed         : 8 ;
	} Bits;
	uint16_t Word ;
}  PowerStatusType ;


/* ============================================================================ *\
 * Global Variables
\* ============================================================================ */
extern  bool            PowerSource_Status[];
extern  PowerStatusType APPPowerStatus;


/* ============================================================================ *\
 * Macro Define
\* ============================================================================ */

#define GetVIOS_PowerOK(PwrSrc_CAL)            ( PowerSource_Status[PwrSrc_CAL] )

#define GetVIOS_PowerOK_FPR()                  ( (bool)APPPowerStatus.Bits.FPR )
#define GetVIOS_PowerOK_CCP()                  ( (bool)APPPowerStatus.Bits.CCP )
#define GetVIOS_PowerOK_FANA()                 ( (bool)APPPowerStatus.Bits.FANA )
#define GetVIOS_PowerOK_FANB()                 ( (bool)APPPowerStatus.Bits.FANB )
#define GetVIOS_PowerOK_ACClutch()             ( (bool)APPPowerStatus.Bits.ACClutch )
#define GetVIOS_PowerOK_SparkCoil()            ( (bool)APPPowerStatus.Bits.SparkCoil )
#define GetVIOS_PowerOK_O2Heater()             ( (bool)APPPowerStatus.Bits.O2Heater )
#define GetVIOS_PowerOK_Injector()             ( (bool)APPPowerStatus.Bits.Injector )


/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */
void PowerSourceStatus_EveryLoop(void);
void InitializePowerSource(void);


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
\* ============================================================================ */
#endif /* V_POWER_H */
