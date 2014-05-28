/******************************************************************************
 *
 * Filename:          knodcald.c
 *
 *  Description:         OBDII Knock System and Sensor Diagnostic Calibrations
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
 * Copyright 2004 , Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     mt20u2#8/csrc/knodcald.c/1 %
 * %date_created:  Wed Mar 19 10:11:39 2008 %
 * %version:       1 %
 * %derived_by:    vzp48z %
 *
 *****************************************************************************/

/******************************************************************************
*  Include Files 
*****************************************************************************/ 
#include "knodcald.h"   /* For Definition-Declaration check   */
#include "knodpapi.h"   /* For Definition-Declaration check   */

  /* Number of knock system low fault determinations that 
     cause a failure to be reported to the Data Manager. */

/*
*| knodcald.{
*|    KcKNKD_SystemFailLoThrsh {
*|     : is_calconst;
*|     : description ="Number of knock system short fault determinations that \
cause a failure to be reported to the Data Manager";
*|     : type = fixed.knod_t_count_byte;
*|     : units = "count";
*|    }
*| }
*/
const T_COUNT_BYTE KcKNKD_SystemFailLoThrsh = V_COUNT_BYTE(26);

/*================================================================*/
  /* Number of knock system high fault determinations that 
     cause a failure to be reported to the Data Manager. */
    
/*
*| knodcald.{
*|    KcKNKD_SystemFailHiThrsh {
*|     : is_calconst;
*|     : description ="Number of knock system high fault determinations that \
*| cause a failure to be reported to the Data Manager";
*|     : type = fixed.knod_t_count_byte;
*|     : units = "count";
*|    }
*| }
*/
const T_COUNT_BYTE KcKNKD_SystemFailHiThrsh = V_COUNT_BYTE(26);

/*================================================================*/
   /* Number of samples in the knock system test before 
      a passing result can be reported. */

/*
*| knodcald.{
*|    KcKNKD_SystemSampleThrsh {
*|     : is_calconst;
*|     : description ="Number of samples in the knock system test before \
a passing result can be reported";
*|     : type = fixed.knod_t_count_byte;
*|     : units = "count";
*|    }
*| }
*/
const T_COUNT_BYTE KcKNKD_SystemSampleThrsh = V_COUNT_BYTE(80);

/*================================================================*/
   /* Number of knock sensor fault determinations that 
      cause a failure to be reported to the Data Manager. */

/*
*| knodcald.{
*|    KcKNKD_SensorFailThrsh {
*|     : is_calconst;
*|     : description ="Number of knock sensor fault determinations that \
cause a failure to be reported to the Data Manager";
*|     : type = fixed.knod_t_count_byte;
*|     : units = "count";
*|    }
*| }
*/
const T_COUNT_BYTE KcKNKD_SensorFailThrsh = V_COUNT_BYTE(16);

/*
*| knodcald.{
*|  KfKNKD_FaultDetectGain {
*|     : is_calconst;
*|     : description ="The CCESC  minimum gain value to set knock sensor fail criteria met.  "
*| "Value MUST be an EVEN number AND between 0 and 26.  "
*| "Engineering Range:  -8192 to 8192   Resolution: 0.25 /Count";
*|     : type = fixed.t_decibels;
*|     : units = "dB";
*|   }
*| }
*/
const T_DECIBELS KfKNKD_FaultDetectGain = V_DECIBELS(16);
 
/*================================================================*/
   /* Number of samples in the knock sensor test before a 
      passing result can be reported. */
      
/*
*| knodcald.{
*|    KcKNKD_SensorSampleThrsh {
*|     : is_calconst;
*|     : description ="Number of samples in the knock sensor test before \
a passing result can be reported";
*|     : type = fixed.knod_t_count_byte;
*|     : units = "count";
*|    }
*| }
*/
const T_COUNT_BYTE KcKNKD_SensorSampleThrsh = V_COUNT_BYTE(64);

/*================================================================*/
   /* Indicates threshold for the short to supply test.  If the
      average reading from the knock sensor goes above this value,
      the input to the knock system is determined to be
      shorted to supply. */
      
/*
*| knodcald.{
*|    KfKNKD_Pct_SystemIntensThrshLo {
*|     : is_calconst;
*|     : description ="Indicates threshold for the short to groundtest. \
If all instantaneous readings for all cylinders are below this value, \
the knock control system is determined to be shorted to ground";
*|     : type = fixed.knod_t_percenta;
*|     : units = "percent";
*|    }
*| }
*/
const T_PERCENTa KfKNKD_Pct_SystemIntensThrshLo = V_PERCENTa(3.9);

/*================================================================*/
   /* Indicates threshold for the short to supply test.  If the
      average reading from the knock sensor goes above this value,
      the input to the knock system is determined to be
      shorted to supply. */
      
/*
*| knodcald.{
*|    KfKNKD_Pct_SystemIntnsAvThrshHi {
*|     : is_calconst;
*|     : description ="Indicates threshold for the short to supply (vcc). \
*| If knock cylinder average is above this value, the knock control system \
*| is determined to be shorted high.";
*|     : type = fixed.knod_t_percenta;
*|     : units = "percent";
*|    }
*| }
*/
const T_PERCENTa KfKNKD_Pct_SystemIntnsAvThrshHi = V_PERCENTa(80.0);

/*================================================================*/
   /* Minimum acceptable difference between maximum and minimum
      values of CCESC_Intensity_Unfilt.  Used in the sensor check.  */

/*
*| knodcald.{
*|    KfKNKD_Pct_SensorIntnsDeltThrsh {
*|     : is_calconst;
*|     : description ="Minimum acceptable difference between maximum minimum \
*| values of OBD_CCESC_Int_Unflt_Blw_Thrsh.";
*|     : type = fixed.knod_t_percenta;
*|     : units = "percent";
*|    }
*| }
*/
const T_PERCENTa KfKNKD_Pct_SensorIntnsDeltThrsh = V_PERCENTa(0.39);

/*================================================================*/
    /* Minimum rpm to run the knock system diagnostic test. */

/*
*| knodcald.{
*|    KfKNKD_n_EngSpdSystemEnblThrsh {
*|     : is_calconst;
*|     : description ="Minimum rpm to run the knock system diagnostic test";
*|     : type = fixed.knod_t_rpma;
*|     : units = "rpm";
*|    }
*| }
*/
const T_RPMa KfKNKD_n_EngSpdSystemEnblThrsh = V_RPMa(1600);

/*================================================================*/
    /* Minimum rpm to run the knock sensor diagnostic test. */

/*
*| knodcald.{
*|    KfKNKD_n_EngSpdSensorEnblThrsh {
*|     : is_calconst;
*|     : description ="Minimum rpm to run the knock sensor diagnostic test";
*|     : type = fixed.knod_t_rpma;
*|     : units = "rpm";
*|    }
*| }
*/
const T_RPMa KfKNKD_n_EngSpdSensorEnblThrsh = V_RPMa(1600);

/*================================================================*/
    /* Indicates maximum engine vacuum allowable for enabling both Knock
       Sensor Circuit faults and Knock Sensor faults. */
       
/*
*| knodcald.{
*|    KtKNKD_p_EngVacThrsh {
*|     : is_calconst;
*|     : description ="Indicates maximum engine vacuum allowable for "
*| "enabling both Knock Sensor Circuit faults and Knock Sensor DSNEF "
*| "faults. Rescale Engineerng Range of 0 to 105 kPa";
*|    :type=fixed.knod_t_kpaa;
*|     :units = "kpa";
*|  
*|    }
*| }
*/
const kPa_W_EOBD KtKNKD_p_EngVacThrsh[9] = {
                            V_KPAa(25), V_KPAa(40), V_KPAa(50),
                            V_KPAa(60), V_KPAa(70), V_KPAa(80),
                            V_KPAa(90), V_KPAa(100), V_KPAa(105) };

/******************************************************************************
*
* Revision history: 
*
* Rev.  YYMMDD Who RSM# Changes                                       
* ----- ------ --- ---- -------------------------------------------------------
* 
*******************************************************************************/
