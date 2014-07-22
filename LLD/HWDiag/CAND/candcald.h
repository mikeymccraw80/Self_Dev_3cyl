#ifndef CANDCALD_H
#define CANDCALD_H
/******************************************************************************
 *
 * Filename:          candcald.h
 *
 * Description:       CAN Diagnostic - Calibration header file
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
 * Copyright 2001-2002, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/******************************************************************************
 *  Subsystem Include Files
 *****************************************************************************/
#include "t_gentypes.h"

extern const T_COUNT_WORD  KcCAND_FailThrsh;
extern const T_COUNT_WORD  KcCAND_SampleThrsh;
extern const T_COUNT_WORD  KfCAND_t_CommEngRunThrsh;
extern const T_VOLTb       KfCAND_U_CommSystemThrshLo;

#endif


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 16/12/05     LShoujun    mt20u2#36
 * + Baseline - Add CAN Commu Failure Diag
 *
\* ============================================================================ */
