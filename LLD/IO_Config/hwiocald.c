
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
const   T_CRANK_ANGLE    KfHWIO_phi_BoundaryFraction = V_CRANK_ANGLE(180);

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
const uint8_t KyHWIO_NumValidPeriodsBeforeSyncStart = 3;


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
