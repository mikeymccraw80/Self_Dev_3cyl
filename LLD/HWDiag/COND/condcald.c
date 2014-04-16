/******************************************************************************
 *
 * Filename:          condcald.c
 *
 * Description:       Process Sequence Diagnostic for Master CPU
 *                    Calibration definitions
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
 * Copyright 1999-2007, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#3/csrc/condcald.c/5 %
 * %date_created:  Mon Aug 31 15:49:33 2009 %
 * %version:       5 %
 * %derived_by:    wzmkk7 %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Include Files                                                            *
 *****************************************************************************/
#include "condcald.h" /* For Generic data types                            */

/*
*| condcald.{
*|   KfCOND_U_SystemThrshHi {
*|     : is_calconst;
*|     : description ="System voltage high threshold below which the diagnostic "
*| "test will be disabled";
*|     : type = fixed.t_voltb;
*|     : units = "volts";
*|   }
*| }
*/
const T_VOLTb KfCOND_U_SystemThrshHi = V_VOLTb(16.0);

/*
*| condcald.{
*|   KfCOND_U_SystemThrshLo {
*|     : is_calconst;
*|     : description ="System voltage low threshold below which the diagnostic "
*| "test will be disabled";
*|     : type = fixed.t_voltb;
*|     : units = "volts";
*|   }
*| }
*/
const T_VOLTb KfCOND_U_SystemThrshLo = V_VOLTb(11.0);

/*
*| condcald.{
*|   KfCOND_t_ADC0EnblDlyTmrThrsh {
*|     : is_calconst;
*|     : description ="Enable delay timer threshold for ADC0.";
*|     : type = fixed.t_time_sec_p125;
*|     : units = "sec";
*|   }
*| }
*/
const TwTIME_t_R125ms KfCOND_t_ADC0EnblDlyTmrThrsh = C_R125ms16(0);

/*
*| condcald.{
*|   KfCOND_t_ClockEnblDlyTmrThrsh {
*|     : is_calconst;
*|     : description ="Enable delay timer threshold for Main CPU Clock.";
*|     : type = fixed.t_time_sec_p125;
*|     : units = "sec";
*|   }
*| }
*/
const TwTIME_t_R125ms KfCOND_t_ClockEnblDlyTmrThrsh = C_R125ms16(0);

/*
*| condcald.{
*|   KfCOND_U_AD_RespIgnLoDsbl {
*|    : is_calconst;
*|    : description = "Ignition voltage below which the A/D Input Response"
*| "diagnostic is disabled. "
*| "Engineering Range: [0, 32), Resolution: 0.00048828125 Volt / Count ";
*|    : type = fixed.t_voltb;
*|    : units = "volt";
*|   }
*| }
*/
const T_VOLTb        KfCOND_U_AD_RespIgnLoDsbl = V_VOLTb(4);

/*
*| condcald.{
*|   KfCOND_U_AD_RespIgnHiDsbl {
*|    : is_calconst;
*|    : description = "Ignition voltage above which the A/D Input Response "
*| "diagnostic is disabled. "
*| "Engineering Range: [0, 32), Resolution: 0.00048828125 Volt / Count ";
*|    : type = fixed.t_voltb;
*|    : units = "volt";
*|   }
*| }
*/
const T_VOLTb        KfCOND_U_AD_RespIgnHiDsbl = V_VOLTb(24);

/*
*| condcald.{
*|   KfCOND_Pct_AD_RespAPS_PreShortMin {
*|    : is_calconst;
*|    : description = "Raw APS1 value below which the A/D Input Response "
*| "diagnostic is disabled (CADRENBL = False). "
*| "Engineering Range: [0, 200), Resolution: 0.0030517578125 % / Count ";
*|    : type = fixed.t_percenta;
*|    : units = "%";
*|   }
*| }
*/
const T_PERCENTa      KfCOND_Pct_AD_RespAPS_PreShortMin = V_PERCENTa(5);

/*
*| condcald.{
*|   KfCOND_Pct_AD_RespAPS_ShortedMax {
*|    : is_calconst;
*|    : description = "APS1 shorted value below which the A/D Input Response "
*| "diagnostic is OK (CADRFCM = False). "
*| "Engineering Range: [0, 200), Resolution: 0.0030517578125 % / Count ";
*|    : type = fixed.t_percenta;
*|    : units = "%";
*|   }
*| }
*/
const T_PERCENTa     KfCOND_Pct_AD_RespAPS_ShortedMax = V_PERCENTa(100);

/*
*| condcald.{
*|   KfCOND_Pct_AD_RespRecDeltaAPS1_Max {
*|    : is_calconst;
*|    : description = "Change in APS1 pre-short to post-short below which "
*| "APS1 slow recovery is set False. "
*| "Engineering Range: [0, 200), Resolution: 0.0030517578125 % / Count ";
*|    : type = fixed.t_percenta;
*|    : units = "%";
*|   }
*| }
*/
const T_PERCENTa     KfCOND_Pct_AD_RespRecDeltaAPS1_Max = V_PERCENTa(100);

/*
*| condcald.{
*|   KfCOND_Pct_AD_RespRecDeltaAPS2_Max {
*|    : is_calconst;
*|    : description = "Change in APS2 pre-short to post-short above which "
*| "APS1 slow recovery is not evaluated. "
*| "Engineering Range: [0, 200), Resolution: 0.0030517578125 % / Count ";
*|    : type = fixed.t_percenta;
*|    : units = "%";
*|   }
*| }
*/
const T_PERCENTa     KfCOND_Pct_AD_RespRecDeltaAPS2_Max = V_PERCENTa(0);

/*
*| condcald.{
*|   KfCOND_Pct_AD_RespDeltaAPS2_Max {
*|    : is_calconst;
*|    : description = "Change in APS2 value when APS1 is shorted above which "
*| "APS short together CADRSHRT is set True. "
*| "Passed to ETCD for handling as an APS correlation fault. "
*| "Engineering Range: [0, 200), Resolution: 0.0030517578125 % / Count ";
*|    : type = fixed.t_percenta;
*|    : units = "%";
*|   }
*| }
*/
const T_PERCENTa     KfCOND_Pct_AD_RespDeltaAPS2_Max = V_PERCENTa(100);

/*
*| condcald.{
*|   KfCOND_t_AD_RespTstInterval {
*|    : is_calconst;
*|    : description = "Minimum Time between the A/D Input Response diagnostic tests. "
*| "Engineering Range: [0, 16), Resolution: 0.000244140625 s / Count ";
*|    : type = apptypes.t_cond_time_sec_0_16;
*|    : units = "s";
*|   }
*| }
*/
const T_COND_TIME_SEC_0_16     KfCOND_t_AD_RespTstInterval = V_COND_TIME_SEC_0_16(0.3);

/*
*| condcald.{
*|   KfCOND_t_AD_RespShortSettleMin {
*|    : is_calconst;
*|    : description = "A/D settling time CADRSSTM below which "
*| "the A/D Input Response diagnostic short to ground is not evaluated (CADRFCM = False). "
*| "Engineering Range: [0, 16), Resolution: 0.000244140625 s / Count ";
*|    : type = apptypes.t_cond_time_sec_0_16;
*|    : units = "s";
*|   }
*| }
*/
const T_COND_TIME_SEC_0_16     KfCOND_t_AD_RespShortSettleMin = V_COND_TIME_SEC_0_16(0.004);

/*
*| condcald.{
*|   KfCOND_t_AD_RespRecSettleMin {
*|    : is_calconst;
*|    : description = "A/D settling time (CADNSST) below which "
*| "APS1 slow recovery is not evaluated (CADRSLOW = False). "
*| "Engineering Range: [0, 16), Resolution: 0.000244140625 s / Count ";
*|    : type = apptypes.t_cond_time_sec_0_16;
*|    : units = "s";
*|   }
*| }
*/
const T_COND_TIME_SEC_0_16 \
                     KfCOND_t_AD_RespRecSettleMin = V_COND_TIME_SEC_0_16(0.008);

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
*
******************************************************************************/
