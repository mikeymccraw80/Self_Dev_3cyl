#ifndef EPSDPAPI_H
#define EPSDPAPI_H
/******************************************************************************
 *
 * Filename:          epsdpapi.h
 *
 * Description:                This is the public header file for
 *                             Engine Position Sensor Diagnostic subsystem
 *                               (Crank and Cam Short Diagnostics)
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    GetEPSD_CamNoSigFailCriteriaMet
 *                    GetEPSD_CamNoSigTestStatReported
 *                    GetEPSD_CamRatnlyFailCriteriaMet
 *                    GetEPSD_CrankNoisySigFailCriteriaMet
 *                    GetEPSD_CrankNoSigFailCriteriaMet
 *                    GetEPSD_CamCylEventCntr
 *
 * Forward Engine Management Systems
 *
 * Copyright 1996-2002, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h"
/****************************************************************************
 *  Utility Library Include Files
 ****************************************************************************/
#include "timclib.h"

/*****************************************************************************
 *  Function Exports
 *****************************************************************************/


/******************************************************************************
 *  Diagnostic Execution Routine Definitions
 *****************************************************************************/
//void InitEPSD_CamRstToKeyOn(void);
void InitEPSD_CamCrankToStall(void);
void InitEPSD_CamRunToPowerOffDelay(void);
void MngEPSD_CamEventTasks(void); 
void InitEPSD_CrankRstToKeyOn(void);
void InitEPSD_CrankCrankToStall(void);
void InitEPSD_CrankRunToPowerOffDelay(void);
void MngEPSD_CrankEventTasks(void);
void MngEPSD_Crank7p81msTasks(void);
void InitEPSD_CamRstToKeyOn(void);
// void InitEPSD_CamRstTo_Keyoff(void);
// void InitEPSD_CrankRstTo_Keyoff(void);
#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
