
#include "hwiocald.h"

/*===========================================================================*\
 * /-----------------------------------------------------------------------\
 * Description: Calibration file for 58x section of hardware input output
 *                          subsystem.
 * \-----------------------------------------------------------------------/
\*===========================================================================*/

/*===========================================================================*\
 * The crank tooth number were the first LoRes event occurs after the gap in
 * the crank wheel
\*===========================================================================*/
/*===========================================================================*\
 * The crank tooth number were the state of the cam signal should be read
\*===========================================================================*/
/*
*| hwiocald.{
*|   KyHWIO_ToothOfFirstLoResEvent {
*|     : is_calconst;
*|     : description = "First tooth of crank position sensor which "
*| "corresponds to a reference event";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const   uint8_t  KyHWIO_ToothOfFirstLoResEvent = 3;

/*
*| hwiocald.{
*|   KyHWIO_ToothOfCAMRefEvent {
*|     : is_calconst;
*|     : description = "Outlet cam phase and inlet cam phase calculate reference";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const   uint8_t  KyHWIO_ToothOfCAMRefEvent = 2;

/*
*| hwiocald.{
*|   KyHWIO_phi_ToothAngleForCamRead {
*|     : is_calconst;
*|     : description = "Crank angle for CAM read";
*|     : type = types.t_crank_angle;
*|     : units = "degrees";
*|   }
*| }
*/
const   T_CRANK_ANGLE   KyHWIO_phi_ToothAngleForCamRead = V_CRANK_ANGLE(18);

/*===========================================================================*\
 * The crank tooth number were the crank logic should start synchronization
 * after the gap in the crank wheel
\*===========================================================================*/
/*
*| hwiocald.{
*|   KyHWIO_CrankSyncStartTooth {
*|     : is_calconst;
*|     : description = "Crank tooth number were the start synchronization "
*| "after the gap";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const   uint8_t    KyHWIO_CrankSyncStartTooth = 2;



/*===========================================================================*\
 * The state at which the Cam1 signal is considered to have occured for
 * cylinder A
\*===========================================================================*/
/*
*| hwiocald.{
*|   KeHWIO_Cam1OccurredTrue {
*|     : is_calconst;
*|     : description = "Cam1 sensor input state when cylinder A is next";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const   bool        KeHWIO_Cam1OccurredTrue     = false;

/*===========================================================================*\
 * The state at which the Cam2 signal is considered to have occured for
 * cylinder A
\*===========================================================================*/
/*
*| hwiocald.{
*|   KeHWIO_Cam2OccurredTrue {
*|     : is_calconst;
*|     : description = "Cam2 sensor input state when cylinder A is next";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const   bool        KeHWIO_Cam2OccurredTrue     = false;

/*===========================================================================*\
 * The number of 58x gaps to detect prior to trusting the Cam sensor.
 * This calibration is needed to compensate for a h/w instability wherein the
 * cam sensor signal is not stable until after 3 pulses
\*===========================================================================*/
/*
*| hwiocald.{
*|   KyHWIO_Num58xGapsBeforeSeqn {
*|     : is_calconst;
*|     : description = "Number of 58x gaps to be detected before trusting Cam";
*|     : type = types.t_count_byte;
*|     : units = "gaps";
*|   }
*| }
*/
const   uint8_t     KyHWIO_Num58xGapsBeforeSeqn = 3;

/*===========================================================================*\
 * Number of teeth of crank position sensor between the reference event and
 * TDC
\*===========================================================================*/
/*
*| hwiocald.{
*|   KfHWIO_phi_TopDeadCenter {
*|     : is_calconst;
*|     : description = "Crank angle offset from the reference event to TDC";
*|     : type = types.t_crank_angle;
*|     : units = "degrees";
*|   }
*| }
*/
const   T_CRANK_ANGLE    KfHWIO_phi_TopDeadCenter = V_CRANK_ANGLE(102);


/*===========================================================================*\
 * Calibration parameters related to PFI fuel output logic
\*===========================================================================*/
/*
*| hwiocald.{
*|   KfHWIO_phi_BoundaryFraction {
*|     : is_calconst;
*|     : description = "Crank angle between the fuel reference event and the "
*| "closing of intake valve";
*|     : type = types.t_crank_angle;
*|     : units = "degree";
*|   }
*| }
*/
const   T_CRANK_ANGLE    KfHWIO_phi_BoundaryFraction = V_CRANK_ANGLE(90);

/*===========================================================================*\
 * Number of Cylinders Calibration
\*===========================================================================*/
/*
*| hwiocald.{
*|   KyHWIO_NumberOfCylinders {
*|     : is_calconst;
*|     : description ="This calibration determines the number of cylinders number. "
*| "Value To Calibrate Out: N/A "
*| "Engineering Range: 0 to 255  Resolution: 1 / Count ";
*|     : type = types.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const uint8_t KyHWIO_NumberOfCylinders = 4;

/*
*| hwiocald.{
*| KyHWIO_NumValidPeriodsBeforeSyncStart {
*|     : is_calconst;
*|     : description = "Number of valid 58x periods to be seen "
*| "by the 58x logic before trying to synch ";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const uint8_t KyHWIO_NumValidPeriodsBeforeSyncStart = 15;

/*
*| hwiocald.{
*| KyHWIO_MaxErrorTeethMore {
*|     : is_calconst;
*|     : description = "Number of error for 58x diagnose, if beyond this, resynchronize";
*|     : type = types.t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const uint16_t KyHWIO_MaxErrorTeethMore = 4;

/*
*| hwiocald.{
*| KyHWIO_MaxErrorTeethLess {
*|     : is_calconst;
*|     : description = "Number of error for 58x diagnose, if beyond this, resynchronize";
*|     : type = types.t_count_word;
*|     : units = "count";
*|   }
*| }
*/
const uint16_t KyHWIO_MaxErrorTeethLess = 3;


//=============================================================================
// Number of gaps seen before CAM switches to software toggle.
//=============================================================================
/*
*| hwiocald.{
*|   KyHWIO_Num58xGapsUsingCamForSync {
*|     : is_calconst;
*|     : description = "Number of 58x gaps to use Cam sensor for cylinder ID."
*| " 255=Always use Cam";
*|     : type = types.t_count_byte;
*|     : units = "gaps";
*|   }
*| }
*/
const   uint8_t     KyHWIO_Num58xGapsUsingCamForSync = 12;


/*
*| hwiocald.{
*|    DSP_LOW_PASS_FILTER_IIR_COEFF {
*|     : is_calconst;
*|     : description ="Calibratable IIR coefficient for DSP Knock low pass filter  "
*| "Engineering Range: 0~ 0xFFFFFF";
*|     : units = "filter";
*|     : elements:type=types.t_count_long;
*|  }
*| }
*/

/*===========================================================================*\
 * /-----------------------------------------------------------------------\
 * | Knock Calibrations
 * \-----------------------------------------------------------------------/
\*===========================================================================*/

const T_COUNT_BYTE KyHWIO_Knock_Preshift = 0;

/*
*| hwiocald.{
*|   KyHWIO_Knock_Preshift {
*|     : is_calconst;
*|     : description = "Preshift for the DSP Knock intensity value";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
const uint32_t  DSP_LOW_PASS_FILTER_IIR_COEFF[] =
{
 // decim coeffs: 
 //Low pass filter. 
 //pass band: 15k. stop band:30k.
 //scale is 4.

  0x006751,                                           // B0
  0xFFA822,                                           // B1
  0x00A975,                                           // B2
  0xFFA822,                                           // B3
  0x006751,                                           // B4
  0x647238,                                           // -A1
  0x81753B,                                           // -A2
  0x4AAC55,                                           // -A3
  0xEEA3DE                                            // -A4


};

/*
*| hwiocald.{
*|    DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF1 {
*|     : is_calconst;
*|     : description ="Calibratable IIR coefficient for DSP Knock low pass filter  "
*| "Engineering Range: 0~ 0xFFFFFF";
*|     : units = "filter";
*|     : elements:type=types.t_count_long;
*|  }
*| }
*/
const uint32_t DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF1[] =
{
 // decim coeffs: 
 //Band pass filter. 
 //7~8K
 //scale is 4.

  0x001DAB,                                           // B0
  0x0,                                           // B1
  0xFFC4AA,                                           // B2
  0x0,                                           // B3
  0x001DAB,                                           // B4
  0x480B31,                                           // -A1
  0x9D0D0E,                                           // -A2
  0x41E81B,                                           // -A3
  0xE535CF                                            // -A4

};

/*
*| hwiocald.{
*|    DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF2 {
*|     : is_calconst;
*|     : description ="Calibratable IIR coefficient for DSP Knock low pass filter  "
*| "Engineering Range: 0~ 0xFFFFFF";
*|     : units = "filter";
*|     : elements:type=types.t_count_long;
*|  }
*| }
*/
const uint32_t DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF2[] =
{
 // decim coeffs: 
 //Band pass filter. 
 //10~11k
 //scale is 4.

  0x001DAB,                                           // B0
  0x0,                                           // B1
  0xFFC4AA,                                           // B2
  0x0,                                           // B3
  0x001DAB,                                           // B4
  0x1E7B40,                                           // -A1
  0xBE66E0,                                           // -A2
  0x1BE288,                                           // -A3
  0xE535CF                                            // -A4


};

/*
*| hwiocald.{
*|    DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF3 {
*|     : is_calconst;
*|     : description ="Calibratable IIR coefficient for DSP Knock low pass filter  "
*| "Engineering Range: 0~ 0xFFFFFF";
*|     : units = "filter";
*|     : elements:type=types.t_count_long;
*|  }
*| }
*/
const uint32_t DSP_KNOCK_CENTER_FREQUENCY_IIR_COEFF3[] =
{
 // decim coeffs: 
 //Band pass filter. 
 //13~14k
 //scale is 4.

  0x001DAB,                                           // B0
  0x0,                                           // B1
  0xFFC4AA,                                           // B2
  0x0,                                           // B3
  0x001DAB,                                           // B4
  0xF0A35D,                                           // -A1
  0xC3D3A7,                                           // -A2
  0xF1F25E,                                           // -A3
  0xE535CF                                            // -A4

};


/*
*| hwiocald.{
*|   KfSPRK_t_DwellInit {
*|     : is_calconst;
*|     : description = "This calibration determines the dwell value used during initialization. "
*| "Value To Calibrate Out: N/A "
*| "Engineering Range: 0 to 1024 ms  Resolution: 0.015625 ms / Count ";
*|     : type = types.t_millisecondsb;
*|     : units = "milliseconds";
*|   }
*| }
*/
const T_MILLISECONDSb  KfSPRK_t_DwellInit = V_MILLISECONDSb(4);

/*
*| hwiocald.{
*|   KfSPRK_t_CrankMinDwellInit {
*|     : is_calconst;
*|     : description = "This calibration determines the minimum dwell value used in initialization. "
*| "Value To Calibrate Out: N/A "
*| "Engineering Range: 0 to 1024 ms  Resolution: 0.015625 ms / Count ";
*|     : type = types.t_millisecondsb;
*|     : units = "milliseconds";
*|   }
*| }
*/
const T_MILLISECONDSb  KfSPRK_t_CrankMinDwellInit = V_MILLISECONDSb(0.5);

/*
*| hwiocald.{
*|   KfSPRK_t_CrankMaxDwellInit {
*|     : is_calconst;
*|     : description = "This calibration determines the maximum dwell value used in initialization. "
*| "Value To Calibrate Out: N/A "
*| "Engineering Range: 0 to 1024 ms  Resolution: 0.015625 ms / Count ";
*|     : type = types.t_millisecondsb;
*|     : units = "milliseconds";
*|   }
*| }
*/
const T_MILLISECONDSb KfSPRK_t_CrankMaxDwellInit = V_MILLISECONDSb(10);

/*
*| hwiocald.{
*|   KbHWIO_ELOAD1_Active_High {
*|     : is_calconst;
*|     : description = "KbHWIO_ELOAD1_Active_High";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/

const   bool        KbHWIO_ELOAD1_Active_High     = true;

/*
*| hwiocald.{
*|   KbHWIO_ELOAD2_Active_High {
*|     : is_calconst;
*|     : description = "KbHWIO_ELOAD2_Active_High";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const   bool        KbHWIO_ELOAD2_Active_High     = true;

/*
*| hwiocald.{
*|   KbHWIO_BRKLMP_Active_High {
*|     : is_calconst;
*|     : description = "KbHWIO_BRKLMP_Active_High";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const   bool        KbHWIO_BRKLMP_Active_High     = true;

/*
*| hwiocald.{
*|   KbHWIO_EnableLogMaxHWWDTime {
*|     : is_calconst;
*|     : description = "To enable Log Max HWWD toggle high state Interval function in HWIO layer.";
*|     : type = types.size2_0to1;
*|     : units = "boolean";
*|   }
*| }
*/
const bool       KbHWIO_EnableLogMaxHWWDTime  =  false;

/*
*| hwiocald.{
*|    K_MainPowerRelayPresent {
*|       : is_calconst;
*|       : description = "Main Power Relay is present";
*|       : type = types.size2_0to1;
*|       : units = "boolean";
*|    }
*| }
*/
const bool        K_MainPowerRelayPresent = true;

/*
*| hwiocald.{
*|   KfVIOS_T_RunCoolHi {
*|     : is_calconst;
*|     : description ="This calibration determines coolant temperature above which "
*| "KcVIOS_RunRefHot is selected as the cylinder event threshold.  If the "
*| "coolant temperature is less than this cal and greater than KfVIOS_T_RunCoolHi "
*| "then KcVIOS_RunRefWarm will be chosen. "
*| "Value To Calibrate Out: -256 "
*| "Engineering Range: -256 to +255 deg C  Resolution: 0.0078125 deg C / Count ";
*|     : type = types.t_deg_ca;
*|     : units = "deg C";
*|   }
*| }
*/
const T_DEG_Ca      KfVIOS_T_RunCoolHi = V_DEG_Ca(65);

/*
*| hwiocald.{
*|   KfVIOS_T_RunCoolLo {
*|     : is_calconst;
*|     : description ="This calibration determines coolant temperature below which "
*| "KcVIOS_RunRefCold is selected as the cylinder event threshold.  If the "
*| "coolant temperature is greater than this cal and less than KfVIOS_T_RunCoolLo "
*| "then KcVIOS_RunRefWarm will be chosen. "
*| "Value To Calibrate Out: -256 "
*| "Engineering Range: -256 to +255 deg C  Resolution: 0.0078125 deg C / Count ";
*|     : type = types.t_deg_ca;
*|     : units = "deg C";
*|   }
*| }
*/
const T_DEG_Ca      KfVIOS_T_RunCoolLo = V_DEG_Ca(10);

/*
*| hwiocald.{
*|   KcVIOS_RunRefCold{
*|     : is_calconst;
*|     : description ="This calibration determines the number of consecutive cylinder events that "
*| "the engine speed must be greater than KfVIOS_n_CrankToRunThrsh when the "
*| "coolant temperature is less than KfVIOS_T_RunCoolLo for the engine state to "
*| "become RUN."
*| "Value To Calibrate Out: 1 "
*| "Engineering Range: 0 to 255 cylinder events  Resolution: 1 cylinder event / Count ";
*|     : type = types.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE  KcVIOS_RunRefCold = V_COUNT_BYTE(12);

/*
*| hwiocald.{
*|   KcVIOS_RunRefWarm {
*|     : is_calconst;
*|     : description ="This calibration determines the number of consecutive cylinder events that "
*| "the engine speed must be greater than KfVIOS_n_CrankToRunThrsh when the "
*| "coolant temperature is greater than KfVIOS_T_RunCoolLo and less than "
*| "KfVIOS_T_RunCoolHi for the engine state to become RUN."
*| "Value To Calibrate Out: 1 "
*| "Engineering Range: 0 to 255 cylinder events  Resolution: 1 cylinder event / Count ";
*|     : type = types.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE  KcVIOS_RunRefWarm = V_COUNT_BYTE(9);

/*
*| hwiocald.{
*|   KcVIOS_RunRefHot {
*|     : is_calconst;
*|     : description ="This calibration determines the number of consecutive cylinder events that "
*| "the engine speed must be greater than KfVIOS_n_CrankToRunThrsh when the "
*| "coolant temperature is greater than KfVIOS_T_RunCoolHi for the engine state to "
*| "become RUN."
*| "Value To Calibrate Out: 1 "
*| "Engineering Range: 0 to 255 cylinder events  Resolution: 1 cylinder event / Count ";
*|     : type = types.t_count_byte;
*|     : units = "counts";
*|   }
*| }
*/
const T_COUNT_BYTE  KcVIOS_RunRefHot = V_COUNT_BYTE(6);

/*
*| hwiocald.{
*|   KfVIOS_n_CrankToRunThrsh {
*|     : is_calconst;
*|     : description ="This calibration determines the crank-to-run engine speed threshold. "
*| "The engine speed must be greater than this calibration for a selective "
*| "number of cylinder events before the engine state is RUN. "
*| "Value To Calibrate Out: N/A "
*| "Enginerring Range: 0 to 8192 rpm  Resolution: 0.125 rpm / Count ";
*|     : type = types.t_rpma;
*|     : units = "RPM";
*|   }
*| }
*/
const T_RPMa       KfVIOS_n_CrankToRunThrsh = V_RPMa(450);

/*
*| hwiocald.{
*|   KfVIOS_n_RunToCrankThrsh {
*|     : is_calconst;
*|     : description ="This calibration determines the run-to-crank engine speed threshold. "
*| "The engine speed must be less than this calibration before the "
*| "engine state is CRANK. "
*| "Value To Calibrate Out: N/A "
*| "Enginerring Range: 0 to 8192 rpm  Resolution: 0.125 rpm / Count ";
*|     : type = types.t_rpma;
*|     : units = "RPM";
*|   }
*| }
*/
const T_RPMa        KfVIOS_n_RunToCrankThrsh = V_RPMa(150);

/*
*| hwiocald.{
*|   KfVIOS_t_PowerdownDelayTime {
*|     : is_calconst;
*|     : description ="This calibration determines the delay time after key-off to begin the "
*| "shutdown process. "
*| "Value To Calibrate Out: 0 "
*| "Enginerring Range: 0 to 256 s  Resolution: 0.0078125 s / Count ";
*|     : type = types.t_w_R7p8125ms;
*|     : units = "seconds";
*|   }
*| }
*/
const TwTIME_t_R7p8125ms   KfVIOS_t_PowerdownDelayTime = C_R7p8125ms16(3);


/*
*| hwiocald.{
*|    K_PowerConfig_FPR {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for Fuel Pump Relay \n"
*|          "0 = Battery_FPR (same as Battery) \n"
*|          "1 = IgnitionON_FPR (same as IgnitionON) \n"
*|          "2 = MainPowerRelay_FPR (same as MainPowerRelay) ";
*|    }
*| }
*/
const PowerSource_FPR_Type K_PowerConfig_FPR =
{
   IgnitionON
};

/*
*| hwiocald.{
*|    K_PowerConfig_CCP {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for Charcoal Canister Purge \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_CCP =
{
   IgnitionON
};

/*
*| hwiocald.{
*|    K_PowerConfig_FANA {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for Fan A \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_FANA =
{
   IgnitionON
};

/*
*| hwiocald.{
*|    K_PowerConfig_FANB {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for Fan B \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_FANB =
{
   IgnitionON
};

/*
*| hwiocald.{
*|    K_PowerConfig_ACClutch {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for AC Clutch \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_ACClutch =
{
   IgnitionON
};


/*
*| hwiocald.{
*|    K_PowerConfig_SparkCoil {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for Spark Coil \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_SparkCoil =
{
   IgnitionON
};

/*
*| hwiocald.{
*|    K_PowerConfig_O2Heater {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for O2 Sensor Heater \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_O2Heater =
{
   IgnitionON
};

/*
*| hwiocald.{
*|    K_PowerConfig_Injector {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for Fuel Injector \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_Injector =
{
   IgnitionON
};

/*
*| hwiocald.{
*|    K_PowerConfig_ETC {
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Select the power source for ETC \n"
*|          "0 = Battery \n"
*|          "1 = IgnitionON \n"
*|          "2 = MainPowerRelay \n"
*|          "3 = FuelPumpRelay ";
*|    }
*| }
*/
const PowerSourceType K_PowerConfig_ETC =
{
   MainPowerRelay
};

/*
*| hwiocald.{
*|   KySYST_BrainDeadBOOT_RecovEnbld
*|   {
*|     : is_calconst;
*|     : description = "If TRUE, then check for specific input conditions will "
*| "occur within BOOT CODE at key-up.  If input conditions are met, BOOT CODE "
*| "will not vector to application, but will stay in BOOT CODE.  This allows "
*| "recovery from brain-dead state using flash tools which interface directly "
*| "with BOOT CODE. "
*| "Value To Calibrate Out: 00 = FALSE "
*| "Engineering Values: $AA = TRUE, (not $AA) = FALSE ";
*|     : type = types.t_count_byte;
*|     : units = "count";
*|   }
*| }
*/
#pragma section SECTION_BRAIN_DEAD_CAL address=0x0003FFFA
#pragma use_section SECTION_BRAIN_DEAD_CAL KySYST_BrainDeadBOOT_RecovEnbld
const T_COUNT_BYTE KySYST_BrainDeadBOOT_RecovEnbld = 0xAA;
#pragma section
