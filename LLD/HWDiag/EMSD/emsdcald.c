/******************************************************************************
 *
 * Filename:          emsdcald.c
 *
 * Description:       Calibration file for ems side I/O hardware 
 *                    Diagnostic (EMSD) subsystem
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
 * Copyright 1997-2005 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#5/csrc/emsdcald.c/1 %
 * %date_created:  Wed Mar 19 10:10:01 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/*****************************************************************************
 *   Include Files
 *****************************************************************************/
#include "emsdcald.h" /* Forced declaration definition check  */


/*****************************************************************************
 *  Calibration definition for ems side I/O hardware Diagnostic subsystem
 *****************************************************************************/
/*===========================================================================*/
/* This calibration is the ignition on time  required for the signal
 * to reach a steady state. */
/*
*| emsdcald.{
*|   KfEMSD_t_IgnitionOnDelay {
*|     : is_calconst ;
*|     : description = "In normal operation, This calibration is the ignition on time "
*| "required for the ems side I/O hardware fault detection starts.";
*|     : type = fixed.emsd_t_seconds ;
*|     : units = "seconds" ;
*|   }
*| }
*/
const T_SECONDS      KfEMSD_t_IgnitionOnDelay = V_SECONDS (10) ;
/*===========================================================================*/
/* This calibration is the ignition on time  required for the main power relay
 * diagnostic. */
/*
*| emsdcald.{
*|   KfEMSD_t_MPRDIgnitionOnDelay {
*|     : is_calconst ;
*|     : description = "In normal operation, This calibration is the ignition on time "
*| "required for the main power relay hardware fault detection starts.In order to complete "
*| "Main Power Relay short to battery detection,this calibration should be shorter than KFPPU,"
*| "and K_MPRIGNONDELAY should be logner than KFPPU+KfEMSD_t_MPRDIgnitionOnDelay to make sure "
*| "Main Power Relay short to ground detection can also be completed.";
*|     : type = fixed.emsd_t_seconds ;
*|     : units = "seconds" ;
*|   }
*| }
*/
const T_SECONDS      KfEMSD_t_MPRDIgnitionOnDelay = V_SECONDS (10) ;


/*===============================================================================
 *  AC Clutch Relay
 *===============================================================================*/
/*===========================================================================*/

/* Ac Clutch Relay fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_ACCDShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "Front Ac Clutch Relay TPIC ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_ACCDShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* Ac Clutch Relay fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_ACCDShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "Front Ac Clutch Relay TPIC ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_ACCDShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* Ac Clutch Relay fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_ACCDShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "Ac Clutch Relay TPIC pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_ACCDShortSmplThrsh  = V_COUNT_WORD (20) ;

/*===============================================================================
 *  Main Power Relay
 *===============================================================================*/
/*===========================================================================*/

/* Main Power Relay fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MPRDShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "Main Power Relay TPIC ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_MPRDShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* Main Power Relay fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MPRDShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "Main Power Relay TPIC ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_MPRDShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* Main Power Relay fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MPRDShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "Main Power Relay TPIC pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_MPRDShortSmplThrsh  = V_COUNT_WORD (20) ;

/*===============================================================================
 *  Fuel Pump Relay
 *===============================================================================*/
/*===========================================================================*/

/* Fuel Pump Relay fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FPRDShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "Fuel pump Relay TPIC ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FPRDShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* Fuel Pump Relay fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FPRDShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "Fuel Pump Relay TPIC ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FPRDShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* Fuel Pump Relay fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FPRDShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "Fuel Pump Relay TPIC pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FPRDShortSmplThrsh  = V_COUNT_WORD (20) ;

/*===============================================================================
 *  MIL
 *===============================================================================*/
/*===========================================================================*/

/* MIL fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MILDShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "MIL PSVI ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_MILDShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* MIL fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MILDShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "MIL PSVI ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_MILDShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* MIL fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MILDShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "MIL PSVI pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_MILDShortSmplThrsh  = V_COUNT_WORD (20) ;

/*===============================================================================
 *  SVS
 *===============================================================================*/
/*===========================================================================*/

/* SVS fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MILDShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "SVS PSVI ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_SVSDShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* SVS fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_SVSDShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "SVS PSVI ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_SVSDShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* SVS fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MILDShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "SVS PSVI pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_SVSDShortSmplThrsh  = V_COUNT_WORD (20) ;

/*===============================================================================
 *  VGIS
 *===============================================================================*/
/*===========================================================================*/

/* GIS fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_GISDShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "GIS PSVI ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_GISDShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* GIS fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_MILDShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "GIS PSVI ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_GISDShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* GIS fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_GISDShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "GIS PSVI pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_GISDShortSmplThrsh  = V_COUNT_WORD (20) ;

/*===============================================================================
 *  Fanx diagnostic
 *===============================================================================*/
/*===========================================================================*/

/* Fan1 fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FANAShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "Fan1 TPIC ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FANAShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* Fan1 fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FANAShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "Fan1 TPIC ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FANAShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* Fan1 fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FANAShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "Fan1 TPIC pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FANAShortSmplThrsh  = V_COUNT_WORD (20) ;

/*===========================================================================*/

/* Fan2 fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FANBShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "Fan2 TPIC ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FANBShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* Fan2 fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FANBShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "Fan2 TPIC ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FANBShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* Fan2 fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_FANBShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "Fan2 TPIC pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_FANBShortSmplThrsh  = V_COUNT_WORD (20) ;


/*===============================================================================
 *  SMR diagnostic
 *===============================================================================*/
/*===========================================================================*/

/* SMR fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_SMRShortHiFailThrsh {
*|     : is_calconst ;
*|     : description = "SMR TPIC ShortHi Fault determination "
*| "counter threshhold equal to or above which a ShortHi failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_SMRShortHiFailThrsh  = V_COUNT_WORD (10) ;
/*============================================================================*/
/* SMR fault determination counter
 * threshhold equal to or above which a failure is
 * reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_SMRShortLoFailThrsh {
*|     : is_calconst ;
*|     : description = "SMR TPIC ShortLo Fault determination "
*| "counter threshhold equal to or below which a ShortLo failure is"
*| "reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_SMRShortLoFailThrsh  = V_COUNT_WORD (10) ;
/*===========================================================================*/
/* SMR fault sample counter threshhold equal to
 * or above which a pass is reported to the Data Manager */
/*
*| emsdcald.{
*|   KcEMSD_SMRShortSmplThrsh  {
*|     : is_calconst ;
*|     : description = "SMR TPIC pass counter threshold "
*| "equal to or above which a pass is reported to the Data Manager.";
*|     : type = fixed.emsd_t_count_word ;
*|     : units = "count" ;
*|   }
*| }
*/
const T_COUNT_WORD      KcEMSD_SMRShortSmplThrsh  = V_COUNT_WORD (20) ;


/*===============================================================================
 *  Flash Checksum  diagnostic calibration structure
 *===============================================================================*/


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
\* ============================================================================ */

