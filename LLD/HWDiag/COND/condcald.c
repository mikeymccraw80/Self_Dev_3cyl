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
#include "condfcfg.h"   /* For COND Local Configuration       */
#include "condfexi.h"   /* For global inputs                  */
#include "condcald.h"   /* For Definition-Declaration check   */
#include "condstyp.h"   /* For COND Local type definitions    */
#include "condptyp.h"   /* For global type definitions        */

#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
#pragma section const {CAL_COND}
#endif

/******************************************************************************
 *  Local cdf-types Definitions
 *****************************************************************************/

/******************************************************************************
 *  Calibration definitions
 *****************************************************************************/
#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_TORQUE
/*
*| condcald.{
*|   KcCOND_SequencingCntUp {
*|     : is_calconst;
*|     : description = "Value added to the Sequencing fail counter each"
*| "time a Sequencing error is detected and subtracted every "
*| "KfCOND_t_SequencingDecTim seconds.";
*|     : type = fixed.t_count_word;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_WORD CAL0ADDR KcCOND_SequencingCntUp         = V_COUNT_WORD(50);
#endif

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_TORQUE
/*
*| condcald.{
*|   KcCOND_SequencingFailThrsh {
*|     : is_calconst;
*|     : description = "Fail counter value above which the controller"
*| "sequencing diagnostic is failed.";
*|     : type = fixed.t_count_word;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_WORD CAL0ADDR KcCOND_SequencingFailThrsh     = V_COUNT_WORD(500);
#endif

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_TORQUE
/*
*| condcald.{
*|   KfCOND_t_SequencingDecTim {
*|     : is_calconst;
*|     : description = "Time between decrements of controller sequencing fail"
*| "counter. Used to avoid setting faults on long drives due"
*| "to occasional errors.";
*|     : type = fixed.t_w_R125ms;
*|     : units = "s";
*|  }
*| }
*/
const TwTIME_t_R125ms CAL0ADDR KfCOND_t_SequencingDecTim   = C_R125ms16(10);
#endif

#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT

#if XeSYST_ETC_WatchdogCPU_HW == CeSYST_ETC_WatchdogCPU_Present
/******************************************************************************
* Calibration definitions for WD throttle circuit diagnostic (condmwdt.c)
******************************************************************************/
/*
*| condcald.{
*|  KcCOND_ThrotCircuitFailThrsh {
*|    : is_calconst;
*|    : description = "Maximum number of failures before reporting "
*| "the failure to the Diagnostic Data Manager (DGDM) for the "
*| "Throttle Circuit Diagnostic.; "
*| "Engineering Range: 0 to 255 count  Resolution:  1 count / Count ";
*|    : type = fixed.t_count_byte;
*|    : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KcCOND_ThrotCircuitFailThrsh   = V_COUNT_BYTE(2);

/*
*| condcald.{
*|  KcCOND_ThrotCircuitSampleThrsh {
*|     : is_calconst;
*|     : description = "Maximum number of samples required before "
*| "reporting a result to the Diagnostic Data Manager (DGDM) for the "
*| "Throttle Circuit Diagnostic.; "
*| "Engineering Range: 0 to 255 count  Resolution:  1 count / Count ";
*|     : type = fixed.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KcCOND_ThrotCircuitSampleThrsh = V_COUNT_BYTE(4);

/*
*| condcald.{
*|  KcCOND_DsblThrotCirFailThrsh {
*|     : is_calconst;
*|     : description = "Maximum number of failures before reporting "
*| "the failure to the Diagnostic Data Manager (DGDM) for the Disable "
*| "Throttle Circuit Diagnostic.; "
*| "Engineering Range: 0 to 255 count  Resolution:  1 count / Count ";
*|     : type = fixed.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KcCOND_DsblThrotCirFailThrsh   = V_COUNT_BYTE(2);

/*
*| condcald.{
*|  KcCOND_DsblThrotCirSampleThrsh {
*|     : is_calconst;
*|     : description = "Maximum number of samples required before "
*| "reporting a result to the Diagnostic Data Manager (DGDM) for the Disable "
*| "Throttle Circuit Diagnostic.; "
*| "Engineering Range: 0 to 255 count  Resolution:  1 count / Count ";
*|     : type = fixed.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KcCOND_DsblThrotCirSampleThrsh = V_COUNT_BYTE(4);
#endif

#endif /*#if XeSYST_LOAD_CNTRL_TYPE == CeSYST_ELECTRONIC_THROT */

/******************************************************************************
* Calibration definitions for software version diagnostic (condmswv.c)
******************************************************************************/
#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
/*
*| condcald.{
*|  KyCOND_ETC_CheckSW_Version1  {
*|     : is_calconst;
*|     : description = "The 1st of the 3 acceptable values of ETC PIC checking CPU version.";
*|     : type = fixed.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KyCOND_ETC_CheckSW_Version1        = V_COUNT_BYTE(0xff);
#endif

#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
/*
*| condcald.{
*|  KyCOND_ETC_CheckSW_Version2  {
*|     : is_calconst;
*|     : description = "The 2nd of the 3 acceptable values of ETC PIC checking CPU version.";
*|     : type = fixed.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KyCOND_ETC_CheckSW_Version2        = V_COUNT_BYTE(0xff);
#endif

#if XeCOND_ETC_CHECKING_CPU_TYPE == CeCOND_ETC_CHECKING_CPU_IS_PIC
/*
*| condcald.{
*|  KyCOND_ETC_CheckSW_Version3  {
*|     : is_calconst;
*|     : description = "The 3rd of the 3 acceptable values of ETC PIC checking CPU version.";
*|     : type = fixed.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KyCOND_ETC_CheckSW_Version3        = V_COUNT_BYTE(0xff);
#endif

#if XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_CORRELATION
/*
*| condcald.{
*|   KcCOND_AD_CorrCntUp {
*|     : is_calconst;
*|     : description = "Indicates the Amount added to A/D input correlation "
*| "fail count each loop the fail criteria is met; "
*| "Engineering Range: 0 to 65535 count  Resolution: 1 count / Count ";
*|     : type = fixed.t_count_word;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_WORD CAL0ADDR KcCOND_AD_CorrCntUp = V_COUNT_WORD(3);

/*
*| condcald.{
*|   KcCOND_AD_CorrCntDwn {
*|     : is_calconst;
*|     : description = "Indicates the Amount subtracted to A/D input correlation "
*| "fail count each loop the fail criteria is met; "
*| "Engineering Range: 0 to 65535 count  Resolution: 1 count / Count ";
*|     : type = fixed.t_count_word;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_WORD CAL0ADDR KcCOND_AD_CorrCntDwn = V_COUNT_WORD(1);

/*
*| condcald.{
*|   KfCOND_U_AD_CorrIgnLoDisable {
*|    : is_calconst;
*|    : description = "Ignition voltage below which the analog input "
*| "correlation diagnostic is disabled. "
*| "Engineering Range: 0 to 25.5  Resolution: 0.1 volts / Count ";
*|    : type = fixed.t_voltb;
*|    : units = "volt";
*|   }
*| }
*/
const T_VOLTb        CAL0ADDR  KfCOND_U_AD_CorrIgnLoDisable = V_VOLTb(7);

/*
*| condcald.{
*|   KfCOND_U_AD_CorrIgnHiDisable {
*|    : is_calconst;
*|    : description = "Ignition voltage above which the analog input "
*| "correlation diagnostic is disabled. "
*| "Engineering Range: 0 to 25.5  Resolution: 0.1 volts / Count ";
*|    : type = fixed.t_voltb;
*|    : units = "volt";
*|   }
*| }
*/
const T_VOLTb        CAL0ADDR  KfCOND_U_AD_CorrIgnHiDisable = V_VOLTb(20);

/*
*| condcald.{
*|   KaCOND_Pct_AD_CorrThrshStdy {
*|     : is_calconst;
*|     : description = "The absolute ( Analog value - main processor "
*| "Analog value) difference above which a fail criteria is met when the main "
*| "processor value is constant. Each element in the array contains a fail "
*| "criteria threshold for the respective variable. "
*| "Element : 0=APS1, 1=APS2"
*| "Engineering Range: 0 to 2  Resolution: 0.003051757 / Count ";
*|     : elements:type = fixed.t_percenta;
*|     : annotation = anns.ad_to_main_inputcorr;
*|     : elements:units = "percent";
*|   }
*| }
*/
const T_PERCENTa    CAL0ADDR KaCOND_Pct_AD_CorrThrshStdy[2] =
                                    { V_PERCENTa(5),V_PERCENTa(5)};

/*
*| condcald.{
*|   KaCOND_K_AD_CorrDynamicGain {
*|     : is_calconst;
*|     : description = "Dynamic gain cal used for calculating the dynamic part "
*| "of the  A/D correlation per 31.25ms when input stops changing rapidly "
*| "Each element in the array contains a gain rate for the respective variable. "
*| "Element : 0=APS1, 1=APS2"
*| "Engineering Range: 0 to 2  Resolution: 0.003051757 / Count ";
*|     : elements:type = fixed.t_percenta;
*|     : annotation = anns.ad_to_main_inputcorr;
*|     : elements:units = "percent";
*|   }
*| }
*/
const T_PERCENTa      CAL0ADDR KaCOND_K_AD_CorrDynamicGain[2] =
                                        { V_PERCENTa(0.1),V_PERCENTa(0.1)};

/*
*| condcald.{
*|   KaCOND_Pct_AD_CorrDecayDelt {
*|     : is_calconst;
*|     : description = "Dynamic decay cal for calculating the dynamic part  "
*| "of the A/D correlation threshold when input is steady "
*| "Each element in the array contains a gain rate for the respective variable. "
*| "Element : 0=APS1, 1=APS2"
*| "Engineering Range: 0 to 2  Resolution: 0.003051757 / Count ";
*|     : elements:type = fixed.t_percenta;
*|     : annotation = anns.ad_to_main_inputcorr;
*|     : elements:units = "percent";
*|   }
*| }
*/
const T_PERCENTa      CAL0ADDR KaCOND_Pct_AD_CorrDecayDelt[2] =
                                { V_PERCENTa(0.05),V_PERCENTa(0.05)};

/*
*| condcald.{
*|   KcCOND_AD_CorrSampleThrsh {
*|     : is_calconst;
*|     : description = "The sample counter value above which the "
*| " a pass is reported for A/D correlation diagnostic "
*| "Engineering Range: 0 to 65535  Resolution: 1 / Count ";
*|     : type = fixed.t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const T_COUNT_WORD   CAL0ADDR KcCOND_AD_CorrSampleThrsh = V_COUNT_WORD(0);

/*
*| condcald.{
*|   KaCOND_AD_CorrCountMaxAnlg {
*|     : is_calconst;
*|     : description = "The counter threshold above which analog "
*| "input correlation test is failed. Each element in the array "
*| "contains a fail threshold for the respective. "
*| "Element 0=APS1, 1=APS2 "
*| "Engineering Range: 0 to 65535  Resolution: 1 / Count ";
*|     : elements:type = fixed.t_count_word;
*|     : annotation = anns.ad_to_main_inputcorr;
*|     : elements:units = "count";
*|   }
*| }
*/
const T_COUNT_WORD    CAL0ADDR KaCOND_AD_CorrCountMaxAnlg[2] =
                                   { V_COUNT_WORD(60), V_COUNT_WORD(60)};

#elif XeCOND_AD_INPUT_VALIDATION_METHOD == CeCOND_AD_INPUT_RESPONSE
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
const T_VOLTb        CAL0ADDR  KfCOND_U_AD_RespIgnLoDsbl = V_VOLTb(4);

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
const T_VOLTb        CAL0ADDR  KfCOND_U_AD_RespIgnHiDsbl = V_VOLTb(24);

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
const T_PERCENTa     CAL0ADDR  KfCOND_Pct_AD_RespAPS_PreShortMin = V_PERCENTa(5);

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
const T_PERCENTa     CAL0ADDR  KfCOND_Pct_AD_RespAPS_ShortedMax = V_PERCENTa(100);

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
const T_PERCENTa     CAL0ADDR  KfCOND_Pct_AD_RespRecDeltaAPS1_Max = V_PERCENTa(100);

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
const T_PERCENTa     CAL0ADDR  KfCOND_Pct_AD_RespRecDeltaAPS2_Max = V_PERCENTa(0);

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
const T_PERCENTa     CAL0ADDR  KfCOND_Pct_AD_RespDeltaAPS2_Max = V_PERCENTa(100);

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
const T_COND_TIME_SEC_0_16 \
                     CAL0ADDR  KfCOND_t_AD_RespTstInterval = V_COND_TIME_SEC_0_16(0.3);

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
const T_COND_TIME_SEC_0_16 \
                     CAL0ADDR  KfCOND_t_AD_RespShortSettleMin = V_COND_TIME_SEC_0_16(0.004);

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
                     CAL0ADDR  KfCOND_t_AD_RespRecSettleMin = V_COND_TIME_SEC_0_16(0.004);

#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
#pragma section const {SHARED_CAL}
#endif
/*
*| condcald.{
*|   KsCOND_AD_RespTstCals {
*|     : is_calconst;
*|     : description = "Structure of calibrations for the AD input "
*| "response diagnostic.";
*|     .CountUp
*|     {
*|      :type = fixed.t_count_word;
*|      :description = "Amount added to the A/D Input Response fail count "
*| "when an evaluation result is fail criteria met. ";
*|      :units = "counts";
*|     }
*|     .CountDown
*|     {
*|      :type = fixed.t_count_word;
*|      :description = "Amount subtracted from the A/D Input Response fail count "
*| "when an evaluation result is fail criteria not met. ";
*|      :units = "counts";
*|     }
*|     .FailThrsh
*|     {
*|      :type = fixed.t_count_word;
*|      :description = "Fail count CADRFCNT value above which an the A/D Input Response "
*| "fault is reported for the current ignition cycle. ";
*|      :units = "counts";
*|     }
*|     .SampleThrsh
*|     {
*|      :type = fixed.t_count_word;
*|      :description = "Sample count CADRSCNT value above which an the A/D Input Response "
*| "pass is reported to the diagnostic manager if it has not failed. ";
*|      :units = "counts";
*|     }
*|   }
*| }
*/
const TsOBDU_DiagTstCals \
                     CAL0ADDR  KsCOND_AD_RespTstCals =
{
  V_COUNT_WORD(1),
  V_COUNT_WORD(1),
  V_COUNT_WORD(1),
  V_COUNT_WORD(1)
};

#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
#pragma section const {CAL_COND}
#endif
#endif /* XeCOND_AD_INPUT_VALIDATION_METHOD */

/*
*| condcald.{
*|  KfCOND_U_LPI_IFB_CommSysThrshLo {
*|     : is_calconst;
*|     : description = "This parameter indicates the threshold above"
*| "which the ignition voltage has to be in order to enable the "
*| "diagnostic; "
*| "Engineering Range: 0 to 31.999 v  Resolution: 0.000488281 v / Count ";
*|     : type = fixed.t_voltb;
*|     : units = "volts";
*|   }
*| }
*/
const T_VOLTb CAL0ADDR KfCOND_U_LPI_IFB_CommSysThrshLo = V_VOLTb(11);

/*
*| condcald.{
*|   KcCOND_ECM_LPI_IFB_FailThrsh {
*|     : is_calconst;
*|     : description = "Indicates the number of samples that can "
*| "register a failure before a fault is set; "
*| "Engineering Range: 0 to 65535 count  Resolution: 1 count / Count ";
*|     : type = fixed.t_count_word;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_WORD CAL0ADDR KcCOND_ECM_LPI_IFB_FailThrsh = V_COUNT_WORD(20);

/*
*| condcald.{
*|   KcCOND_ECM_LPI_IFB_SmplThrsh {
*|     : is_calconst;
*|     : description = "Indicates the number of samples that are"
*| "needed to register a pass.; "
*| "Engineering Range: 0 to 65535 count  Resolution: 1 count / Count ";
*|     : type = fixed.t_count_word;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_WORD CAL0ADDR KcCOND_ECM_LPI_IFB_SmplThrsh = V_COUNT_WORD(30);

#if XeSYST_CONTROLLER_DIAG == CeSYST_AVAILABLE
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
const T_VOLTb CAL0ADDR KfCOND_U_SystemThrshHi = V_VOLTb(16.0);

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
const T_VOLTb CAL0ADDR KfCOND_U_SystemThrshLo = V_VOLTb(11.0);

/*
*| condcald.{
*|   KaCOND_t_EnableDelayTime {
*|     : is_calconst;
*|     : description = "Time threshold used to indicate sufficient time to "
*| "enable a diagnostic";
*|     : annotation = anns.io_device;
*|     : type = array.array_dim10_seconds;
*|     : units = "milliseconds";
*|   }
*| }
*/
const T_SECONDS CAL0ADDR KaCOND_t_EnableDelayTime[CcCOND_NumOf_IO_Device] =
{

  V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5),
  V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5), V_SECONDS(0.5)
  };

/*
*| condcald.{
*|   KaCOND_Cnt_FailThrsh {
*|     : is_calconst;
*|     : description ="COND fail counter threshold equal to or above "
*| "which a fail is reported to the Data Manager "
*| "Engineering Range: 0 to 255 Resolution: 1 / Count ";
*|     : annotation = anns.io_device;
*|     : type = array.array_dim10_count_byte;
*|     : units = "";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KaCOND_Cnt_FailThrsh[CcCOND_NumOf_IO_Device] =
{
  V_COUNT_BYTE(1), V_COUNT_BYTE(1), V_COUNT_BYTE(1), V_COUNT_BYTE(40), V_COUNT_BYTE(40),
  V_COUNT_BYTE(40), V_COUNT_BYTE(40), V_COUNT_BYTE(40), V_COUNT_BYTE(40),  V_COUNT_BYTE(1)
};

/*
*| condcald.{
*|   KaCOND_Cnt_SampleThrsh {
*|     : is_calconst;
*|     : description ="COND sample counter threshold equal to or above"
*| "which a fail is reported to the Data Manager "
*| "Engineering Range: 0 to 255 Resolution: 1 / Count ";
*|     : annotation = anns.io_device;
*|     : type = array.array_dim10_count_byte;
*|     : units = "";
*|   }
*| }
*/
const T_COUNT_BYTE CAL0ADDR KaCOND_Cnt_SampleThrsh[CcCOND_NumOf_IO_Device] =
{
  V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80),
  V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80), V_COUNT_BYTE(80),  V_COUNT_BYTE(80)
};

#endif

#if ( ( config_CPU_Type == option_M68HC12 ) \
 && ( config_Compiler_Vendor == option_COSMIC )  )
 #pragma section const {}
#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.0   990204 as  0785 Created module.
* 1.1   990303 sai 0739 Add software version diagnostic
* 1.1   990303 sai 0862 Add watchdog CPU throttle disable diagnostic
*
* --- CORE REVISION HISTORY: ---
*
* 1.0   990825 wei 0303 Merged Proto2 package (cp2050f0) into core node 24
* 1.0   990825 wei 0303 Merged Proto2 package (cp2050f0) into core node 24
*              wei 0303 Added compilation switch XeSYST_ETC_WatchdogCPU_HW
*                        around ETC_Watchdog_CPU related cals.
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   000714 woz 0883 Merged modifications implemented between Core (EMSDC1a)
*                        nodes 32 and 53:
*       000221 kan 0607 Used fix_i6l_comments to correct description field.
* 1.3   010518 woz 0059 Reimplemented ETC conditional compile switches.
* 1.4   020920 woz 2152 Added CAL0ADDR storage specifiers. This allows use of
*                        indexed addressing mode for cals. (TriCore only)
* tci_pt3#2.1.1
*       030607  pd 2768 Added the calibrations :
*                        KfCOND_U_LPI_IFB_CommSysThrshLo,
*                        KcCOND_ECM_LPI_IFB_FailThrsh,
*                        KcCOND_ECM_LPI_IFB_SmplThrsh
* tci_pt3#2.1.2
*       031117 PVD 2063 Added CALS
*                       KcCOND_AD_CorrCntDwn,KcCOND_AD_CorrCntUp,
*                       KcCOND_AD_CorrSampleThrsh,KaCOND_AD_CorrCountMaxAnlg
*                       KfCOND_U_AD_CorrIgnLoDisable,KfCOND_U_AD_CorrIgnHiDisable
*                       KaCOND_Pct_AD_CorrThrshStdy[2]
*                       KaCOND_K_AD_CorrDynamicGain[2]
*                       KaCOND_Pct_AD_CorrDecayDelt[2]
*
* 2.1.3 040211 ses 2992 Added: KfCOND_U_SystemThrshHi, KfCOND_U_SystemThrshLo,
*                       KaCOND_t_EnableDelayTime, KaCOND_Cnt_FailThrsh,
*                       KaCOND_Cnt_SampleThrsh
* tci_pt3#2.1.3
*       040302 ban 3666 Added KcCOND_ECM_TRN_MIL_FailThrsh
*                             KcCOND_ECM_TRN_MIL_SmplThrsh
* 2.1.4.2.1
*       040428 wei 3339 Added KyCOND_ETC_CheckSW_Version1
*                             KyCOND_ETC_CheckSW_Version2
*                             KyCOND_ETC_CheckSW_Version3;
*                        removed KcCOND_MainSW_CalformID
*                              & KcCOND_ETC_CalibrationID
* 2.2   040507 jyz 2992 Corrected cals default values and cal def
* 3.0   040601 caw  BM  Merge
* tci_pt3#3.1
*       040617  pd 3927 Making code Cosmic Compatible
* 3.1   040629 jyz 4033 CcCOND_NumOf_IO_Device from 10 to 12
* 3.1.1.1
*       040823 ses 4241 Removed one element from the following arrays:
*                       KaCOND_t_EnableDelayTime, KaCOND_Cnt_FailThrsh,
*                       and KaCOND_Cnt_SampleThrsh.
* 3.0.1.1
*       040726 wei 3438 ETCD: Update process sequencing diagnostic.
* 3.2   040730 arr ---- Merged 'condcald.c-3.1' with 'condcald.c-3.0.1.1'.
* tci_pt3#3.2
*       040726 akk 4073 Changed includes for COND modularisation.
* tci_pt3#
*       040818  pd xxxx Merged parallel versions
* tci_pt3#3.3
*       040823  pd xxxx Merged parallel versions
* 3.1.1.2
*       040912 rmn ---- Merged 'condcald.c-3.1.1.1' with 'condcald.c-tci_pt3#3.3'.
* 4     041124 woz 4538 Removed MLRE_0 element from following cal arrays:
*                        KaCOND_t_EnableDelayTime
*                        KaCOND_Cnt_FailThrsh
*                        KaCOND_Cnt_SampleThrsh
* 5     041214 mll 4736 Changed default values of KaOUTD_Cnt_FailThrsh
*              jyz       and KaOUTD_Cnt_SampleThrsh to actual values
*       050304 kan 4853 Removed XeSYST_CONTROLLER_ForETC
* 6.3.1 061026 hdb 5837 Move cals defined in COND to TRND subsystem:
*                         Moved and renamed KcCOND_ECM_TRN_MIL_FailThrsh
*                                           KcCOND_ECM_TRN_MIL_SmplThrsh
*                         to trndcald
* tci_pt3#7
*       061010 kvm 5837 Removed KcCOND_ECM_TRN_MIL_FailThrsh
*                               KcCOND_ECM_TRN_MIL_SmplThrsh
* 7.1.1 070305 gps 5202 COND: Validate APS Inputs Using Short to Ground Method.
*                       Added new set of calibrations.
* 9     070425 gps -BM- Merged 'condcald.c-8' with 'condcald.c-7.1.1'.
*
******************************************************************************/
