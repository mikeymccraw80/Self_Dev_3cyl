
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
*|   KsVSEP_Fault_Level_Initial1 {
*|     : is_calconst;
*|     : description = "If the voltage on any of these input becomes greater than the FLTLVL[x]  in the on state \n" 
*| "then this output shall be considered as STB and shut off  as long as it meets \n "
*| " the minimum requirement of the digital fault filters FILT_X.Fault_Level 1,2,3,4 setting.";
*|     .KeVSEP_FLTLVL3
*|     {
*|        :type = uint8;
*|        :description = "fault voltage threshold for channel:13,14,15,16";
*|        :units = "0 TO 7";
*|     }
*|     .KeVSEP_FLTLVL4
*|     {
*|        :type = uint8;
*|        :description = "fault voltage threshold for channel:17,18 ";
*|        :units = "0 TO 15";
*|     }
*|     .KbVSEP_FLTLVL_dummy_bit1
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_FLTLVL_dummy_bit1, leave it alone "
*| "it should be 0 always.";
*|        :units = "0 TO 1";
*|     }
*|     .KeVSEP_FLTLVL1
*|     {
*|        :type = uint8;
*|        :description = "fault voltage threshold for channel: 1,2,3,4,5,6,7,8";
*|        :units = "0 TO 15";
*|     }
*|     .KeVSEP_FLTLVL2
*|     {
*|        :type = uint8;
*|        :description = "fault voltage threshold for channel:4,5,6,7,8,9,10,11,12 ";
*|        :units = "0 TO 7";
*|     }
*|     .KbVSEP_FLTLVL_dummy_bit2
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_FLTLVL_dummy_bit2,leave it alone "
*| "it should be 0 always.";
*|        :units = "0 TO 1";
*|     }
*| }
*|   }
*/

const  KsVSEP_Fault_Level_Cals1  KsVSEP_Fault_Level_Initial1= {
             3,1,0,
             13,5,0

 };

/*
*| hwiocald.{
*|   KsVSEP_Fault_Level_Initial2 {
*|     : is_calconst;
*|     : description = "If the voltage on any of these input becomes greater than the FLTLVL[x]  in the on state \n" 
*| "then this output shall be considered as STB and shut off  as long as it meets \n "
*| " the minimum requirement of the digital fault filters FILT_X.Fault_Level 5,6,7 setting.";
*|     .KeVSEP_FLTLVL7
*|     {
*|        :type = uint8;
*|        :description = "fault voltage threshold for channel:25,26,27,28,29,30";
*|        :units = "0 TO 7";
*|     }
*|     .KeVSEP_FLTLVL_dummy_bit3
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_FLTLVL_dummy_bit3,leave it alone "
*| "it should be 0 always.";
*|        :units = "0 TO 31";
*|     }
*|     .KeVSEP_FLTLVL5
*|     {
*|        :type = uint8;
*|        :description = "fault voltage threshold for channel:19,20 ";
*|        :units = "0 TO 15";
*|     }
*|     .KeVSEP_FLTLVL6
*|     {
*|        :type = uint8;
*|        :description = "fault voltage threshold for channel:21,22,23,24";
*|        :units = "0 TO 7";
*|     }
*|     .KbVSEP_FLTLVL_dummy_bit4
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_FLTLVL_dummy_bit4,leave it alone "
*| "it should be 0 always.";
*|        :units = "0 TO 1";
*|     }
*| }
*|   }
*/

const  KsVSEP_Fault_Level_Cals2  KsVSEP_Fault_Level_Initial2= {

             3,0,
             3,3,0

 };


/*
*| hwiocald.{
*|   KsVSEP_VR1_Setting_Initial {
*|     : is_calconst;
*|     : description = "VR1 configuration initialization.";
*|     .KeVSEP_VR1_MT
*|     {
*|        :type = uint8;
*|        :description = "Input Minimum Threshold for VR1";
*|        :units = "0 TO 7";
*|     }
*|     .KbVSEP_VR1_PERC50
*|     {
*|        :type = uint8;
*|        :description = "0, Adaptive threshold percentage of 30%; 1, 50% ";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_VR1_RST
*|     {
*|        :type = uint8;
*|        :description = "0, reset is inactive; 1, provides a pules output on SPI write enable. ";
*|        :units = "0 TO 1";
*|     }
*|     .KeVSEP_VR1_dummy_bit1
*|     {
*|        :type = uint8;
*|        :description =  "KeVSEP_VR1_dummy_bit1,leave it alone "
*| "it should be 0 always ";
*|        :units = "0 TO 7";
*|     }
*|     .KeVSEP_VR1_DLY
*|     {
*|        :type = uint8;
*|        :description = "VR1 digital filter delay times";
*|        :units = "0 TO 127";
*|     }
*|    .KbVSEP_VR1_dummy_bit2
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_VR1_dummy_bit2,leave it alone "
*| "it should be 0 always.";
*|        :units = "0 TO 1";
*|   }
*| }
*|   }
*/

const   KsVSEP_VR1_Setting_Cals  KsVSEP_VR1_Setting_Initial= {

                1, 0, 0, 0,
                1,0
  
 };


/*
*| hwiocald.{
*|   KsVSEP_VR1_Setting_Initial_Crank {
*|     : is_calconst;
*|     : description = "Structure of calibrations for the vsep  "
*| "VR1 setting.";
*|     .KeVSEP_VR1_DLY
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_VR1_DLY";
*|        :units = "0 TO 127";
*|     }
*|    .Unused
*|     {
*|        :type = uint8;
*|        :description = "Unused";
*|        :units = "0 TO 1";
*|   }
*| }
*|   }
*/

const   KsVSEP_VR1_HeavyDelay_T  KsVSEP_VR1_Setting_Initial_Crank= {
                4, 0
 };


/*
*| hwiocald.{
*|   KsVSEP_VR2_Setting_Initial {
*|     : is_calconst;
*|     : description = "VR2 configuration initialization.";
*|     .KeVSEP_VR2_MT
*|     {
*|        :type = uint8;
*|        :description = "Input Minimum Threshold for VR2";
*|        :units = "0 TO 7";
*|     }
*|     .KbVSEP_VR2_PERC50
*|     {
*|        :type = uint8;
*|        :description = "0, Adaptive threshold percentage of 30%; 1, 50% ";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_VR2_RST
*|     {
*|        :type = uint8;
*|        :description = "0, reset is inactive; 1, provides a pules output on SPI write enable. ";
*|        :units = "0 TO 1";
*|     }
*|     .KeVSEP_VR2_dummy_bit1
*|     {
*|        :type = uint8;
*|        :description =  "KeVSEP_VR2_dummy_bit1,leave it alone "
*| "it should be 0 always ";
*|        :units = "0 TO 7";
*|     }
*|     .KeVSEP_VR2_DLY
*|     {
*|        :type = uint8;
*|        :description = "VR2 digital filter delay times";
*|        :units = "0 TO 127";
*|     }
*|    .KbVSEP_VR2_dummy_bit2
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_VR2_dummy_bit2,leave it alone "
*| "it should be 0 always.";
*|        :units = "0 TO 1";
*|   }
*| }
*|   }
*/

const  KsVSEP_VR2_Setting_Cals  KsVSEP_VR2_Setting_Initial= {

                1, 0, 0, 0,
                0x12,0
  
 };


/*
*| hwiocald.{
*|   KsVSEP_DEPSDLY_Setting_Initial {
*|     : is_calconst;
*|     : description = "DEPS IN digital filter delay times. bit weight: 0,8us;1, 16us;2,32us;3,64us;4,128us;5,256us  ";
*|     .KeVSEP_DEPSDLY_dummy_bit1
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_DEPSDLY_dummy_bit1,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 255";
*|     }
*|     .KeVSEP_DEPSDLY
*|     {
*|        :type = uint8;
*|        :description = "DEPS IN digital filter delay times,bit weight: 0,8us;1, 16us;2,32us;3,64us;4,128us;5,256us ";
*|        :units = "0 TO 127";
*|     }
*|     .KbVSEP_DEPSDLY_dummy_bit2
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_DEPSDLY_dummy_bit2,leave it alone "
*| "it should be 0 always.";
*|        :units = "0 TO 1";
*|     }
*| }
*|   }
*/

const  KsVSEP_DEPSDLY_Setting_Cals  KsVSEP_DEPSDLY_Setting_Initial= {

                0,
                1,0

 };


/*
*| hwiocald.{
*|   KsVSEP_SLEW_Initialization {
*|     : is_calconst;
*|     : description = "Slew channel drive feature";
*|     .KeVSEP_SLEW4
*|     {
*|        :type = uint8;
*|        :description = "Slew gate drive currence.00 0.75mA;01 1.5mA;10 3.0mA;11 6.0mA ";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_SLEW5
*|     {
*|        :type = uint8;
*|        :description = "Slew gate drive currence;000 300uA ;001 700uA ;010 1100uA ;011 1500uA ";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_SLEWCAN
*|     {
*|        :type = uint8;
*|        :description = "Slew the CAN rate.00 500Kbps;01 250Kbps;10 125Kbps;11 1.0Mbps ";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_SLEW_dummy_bit
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_SLEW_dummy_bit,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_SLEW1
*|     {
*|        :type = uint8;
*|        :description = "Slew gate drive currence;00 0.75mA;01 1.5mA;10 3.0mA;11 6.0mA ";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_SLEW2
*|     {
*|        :type = uint8;
*|        :description = "Slew gate drive currence;000 100uA;001 300uA;010 500uA;011 700uA; \n"
*|"100 900uA;101 1100uA;110 1300uA;111 1500uA ";
*|        :units = "0 TO 7";
*|     }
*|     .KeVSEP_SLEW3
*|     {
*|        :type = uint8;
*|        :description = "Slew gate drive currence;000 100uA;001 300uA;010 500uA;011 700uA;\n"
*|"100 900uA;101 1100uA;110 1300uA;111 1500uA ";
*|        :units = "0 TO 7";
*|     }
*| }
*|   }
*/

const  KsVSEP_SLEW_Cals  KsVSEP_SLEW_Initialization= {

                1,2,0,0,
                1,6,2
 
 };


/*
*| hwiocald.{
*|   KsVSEP_Fault_Filter_Initial {
*|     : is_calconst;
*|     : description = "If the voltage on any of these input becomes greater than the FLTLVL[x]  in the on state \n" 
*| "then this output shall be considered as STB and shut off  as long as it meets \n "
*| " the minimum requirement of the digital fault filters FILT_X.00, 7.5us, 01 15us, 10 34us, 11 46us.";
*|     .KeVSEP_FILT_17TO18
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH17-PCH18";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_FILT_19TO20
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH19-PCH20";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_FILT_21TO24
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH21-PCH24";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_FILT_25TO30
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH25-PCH30";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_FILT_1TO8SP
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH1-PCH8 if defined as ignition Channels.";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_FILT_1TO8NS
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH1-PCH8 if not defined as ignition Channels.";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_FILT_9TO12
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH9-PCH12";
*|        :units = "0 TO 3";
*|     }
*|     .KeVSEP_FILT_13TO16
*|     {
*|        :type = uint8;
*|        :description = "Short to Battery Fault Filter Time For PCH13-PCH16";
*|        :units = "0 TO 3";
*|     }
*| }
*|   }
*/

const  KsVSEP_Fault_Filter_Cals  KsVSEP_Fault_Filter_Initial= {

                3,3,3,3,
                3,3,3,3//Byte 1=> low bit
  
 };

/*
*| hwiocald.{
*|   KsVSEP_LEDMODE_Initial {
*|     : is_calconst;
*|     : description = "PCH25, PCH26 & PCH30 can be configurated to drive LED. 0, normal mode, Off State Diagnostic Current Sounce is Enabled.\n"
*| " 1, LED mode, Off State Diagnostic Current Sounce is Disabled.";
*|     .KeVSEP_LEDMODE_dummy_bit1
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_LEDMODE_dummy_bit1,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 255";
*|     }
*|     .KbVSEP_LEDMODE_25
*|     {
*|        :type = uint8;
*|        :description = "for channel 25,0, normal mode,1, LED mode";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_LEDMODE_26
*|     {
*|        :type = uint8;
*|        :description = "for channe 26;0, normal mode,1, LED mode";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_LEDMODE_30
*|     {
*|        :type = uint8;
*|        :description = "for channe 30;0, normal mode,1, LED mode";
*|        :units = "0 TO 1";
*|     }
*|     .KeVSEP_LEDMODE_dummy_bit2
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_LEDMODE_dummy_bit2,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 31";
*|     }
*| }
*|   }
*/

const  KsVSEP_LEDMODE_Cals  KsVSEP_LEDMODE_Initial= {

                0,
                0,0,0,0

 };

/*
*| hwiocald.{
*|   KsVSEP_GRAD_Initialization {
*|     : is_calconst;
*|     : description = "configuration of  'slope gradient check' and current trip circuitry for STB protection of IGBT";
*|     .KeVSEP_GRAD_dummy_bit1
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_GRAD_dummy_bit1,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 255";
*|     }
*|     .KbVSEP_GRADFILT
*|     {
*|        :type = uint8;
*|        :description = "Gradient check fault timer selection";
*|        :units = "0 TO 7";
*|     }
*|     .KbVSEP_GRADTHR
*|     {
*|        :type = uint8;
*|        :description = "Threshold value used to determine when an over current event has \n"
*| "occurred for IGBT outputs being used as Ignition drivers.";
*|        :units = "0 TO 7";
*|     }
*|     .KeVSEP_GRAD_dummy_bit2
*|     {
*|        :type = uint8;
*|        :description = "KeVSEP_GRAD_dummy_bit2,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 3";
*|     }
*| }
*|   }
*/

const  KsVSEP_GRAD_Cals  KsVSEP_GRAD_Initialization= {
                0,
                0,7,0                

 };


/*
*| hwiocald.{
*|   KsVSEP_Spark_Mode_Initialization {
*|     : is_calconst;
*|     : description = " Spark Mode configuration ";
*|     .KeVSEP_Spark_CYLCNT
*|     {
*|        :type = uint8;
*|        :description = "determines the number of engine cylinders.";
*|        :units = "0 TO 7";
*|     }
*|     .KbVSEP_Spark_DEC_DISCB
*|     {
*|        :type = uint8;
*|        :description = "0, Ignitition outputs controlled by discrete inputs.\n" 
*|"1, controlled by internal decode logic.";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_Spark_IGBTCFG
*|     {
*|        :type = uint8;
*|        :description = "0, Ignitition output faults set for driving EST inputs.\n"
*|"1, for driving IGBT¡¯s.";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_Spark_dummy_bit1
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_Spark_dummy_bit1,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 7";
*|     }
*|     .KbVSEP_Spark_EDGE
*|     {
*|        :type = uint8;
*|        :description = "0, EST1C will index only on the falling edge of EST1 and EST2C will only index on the falling edge of EST2 \n"
*|"1, EST1C will index only on the rising edge of SYNC and EST2C will index only on the falling edge of SYNC.";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_Spark_INDEX
*|     {
*|        :type = uint8;
*|        :description = "0, EST[x]C[2:0] counters will increment by only one (1), each time an index operation occurs\n"
*|" 1, EST[x]C[2:0] counters will increment by two (2), each time an index operation occurs.";
*|        :units = "0 TO 1";
*|     }
*|     .KeVSEP_Spark_PFMODE
*|     {
*|        :type = uint8;
*|        :description = "0, Paired firing mode of EST logic is disabled. 1, enabled. \n"
*|"actually, KeSPRK_DeliveryMode will determine the PF mode finally";
*|        :units = "0 TO 1";
*|     }
*|     .KbVSEP_Spark_dummy_bit2
*|     {
*|        :type = uint8;
*|        :description = "KbVSEP_Spark_dummy_bit2,leave it alone"
*| "it should be 0 always.";
*|        :units = "0 TO 31";
*|     }
*| }
*|   }
*/

const  KsVSEP_Spark_Mode_Cals  KsVSEP_Spark_Mode_Initialization= {
#if CcSYST_NUM_OF_CYLINDERS == 3
	   2,1,1,0,
	   1,1,0,0
#else
	   3,1,1,0,
	   1,0,0,0
#endif
 };

/*
*| hwiocald.{
*|   KeHWIO_ACReq_pin79_Status{
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Caution: configuration for VSEP MULTI channels";
*|   }
*|   }
*/



const VSEP_MPIO_Input_Mode_T KeHWIO_ACReq_pin79_Status = VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT;

/*
*| hwiocald.{
*|   KeHWIO_PSPS_pin60_Status{
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Caution: configuration for VSEP MULTI channels";
*|   }
*|   }
*/


const VSEP_MPIO_Input_Mode_T KeHWIO_PSPS_pin60_Status = VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT;
/*
*| hwiocald.{
*|   KeHWIO_MIDAC_pin40_Status{
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Caution: configuration for VSEP MULTI channels";
*|   }
*|   }
*/


const VSEP_MPIO_Input_Mode_T KeHWIO_MIDAC_pin40_Status = VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT;


/*
*| hwiocald.{
*|   KsVSEP_Diagnostic_Counter_Thd {
*|     : is_calconst;
*|     : description ="threshold of fault counter(7.8ms/counter), if exceed, the coresponding channel will disabled untill key on again";
*|     : type = types.t_count_word;
*|     : units = "count";
*|   }
*|   }
*/


const   uint16_t KsVSEP_Diagnostic_Counter_Thd = 16;

/*
*| hwiocald.{
*|   t_soh_0_14_ubyte
*|   {
*|     : kind = fixed;
*|     : precision = 1;
*|     : range = 0 TO <15;
*|   }
*|   KSOHCRTH {
*|     : is_calconst;
*|     : is_coordinated;
*|     : description = "SOH challenge and response counter threshold "
*| "below which fuel, spark and ETC outputs are disabled. "
*| "Count should be less than 15";
*|     : type = hwiocald.t_soh_0_14_ubyte;
*|     : units = "count";
*|   }
*|   }
*/
const uint8_t KSOHCRTH = 10;

/*
*|    K_Can_Meter_MIL_Disable {
*|       :is_calconst;
*|       :units = "BOOLEAN";
*|       :description = "Disable MIL output on ECM pin";
*|    }
*/
const bool    K_Can_Meter_MIL_Disable = false ;

/*
*|    K_Can_Meter_TACH_Disable {
*|       :is_calconst;
*|       :units = "BOOLEAN";
*|       :description = "Disable tachometer output on ECM pin";
*|    }
*/
const bool    K_Can_Meter_TACH_Disable = false ;

/*
*|    K_Can_Meter_Fuel_Consum_Disable {
*|       :is_calconst;
*|       :units = "BOOLEAN";
*|       :description = "Disable Fuel_Consum output on ECM pin";
*|    }
*/

const bool    K_Can_Meter_Fuel_Consum_Disable = false ;
