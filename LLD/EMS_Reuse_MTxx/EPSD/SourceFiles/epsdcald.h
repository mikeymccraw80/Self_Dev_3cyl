#ifndef EPSDCALD_H
#define EPSDCALD_H
/******************************************************************************
 *
 * Filename:          epsdcald.h
 *
 * Description:                  This is the calibration data header file
 *                               for the Engine Performance Sensing Diagnostic
 *                               (EPSD) subsystem
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 1998-2002, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"
#include "t_fixed.h"
#include "t_scaled.h"
#include "t_tables.h"
#include "t_user.h"
#include "t_custom.h"

/*****************************************************************************
 *  Local Include Files
 *****************************************************************************/

/*****************************************************************************
 *  GMPT Library Include Files
 *****************************************************************************/

/******************************************************************************
*  Constant Definitions
******************************************************************************/

/******************************************************************************
*  Type Declarations
******************************************************************************/

/******************************************************************************
*  Control Algorithm Include Files
******************************************************************************/

/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/
extern const T_COUNT_WORD       CAL0ADDR KcEPSD_CamNoSignalCylEvent;
extern const T_COUNT_WORD       CAL0ADDR KcEPSD_CamRationalityFailThrsh;
extern const T_COUNT_WORD       CAL0ADDR KcEPSD_CamRationalityPassThrsh;
extern const T_COUNT_WORD       CAL0ADDR KcEPSD_CrankToothErrFailThrsh;
extern const T_COUNT_WORD       CAL0ADDR KcEPSD_CrankNoisySigFailThrsh;
extern const T_COUNT_WORD       CAL0ADDR KcEPSD_CrankNoisySigSampleThrsh;
extern const T_KPAa             CAL0ADDR KfEPSD_p_CrankDeltaMAP_Thrsh;
extern const T_VOLTb            CAL0ADDR KfEPSD_U_CrankDeltaIgnThrsh;
extern const TwTIME_t_R7p8125ms CAL0ADDR KfEPSD_t_CrankNoSignalTmr;
extern const TwTIME_t_R7p8125ms CAL0ADDR KfEPSD_t_CrankNoSignalResetThrs;

/*****************************************************************************
 *  Function Exports
 *****************************************************************************/

/*****************************************************************************
 *  Function Prototype
 *****************************************************************************/

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/

