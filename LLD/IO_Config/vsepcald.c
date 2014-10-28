//=============================================================================
// include files
//=============================================================================
#include "vsepcald.h"

//=============================================================================
//const define
//=============================================================================
/*
*| vsepcald.{
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
*| vsepcald.{
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
*| vsepcald.{
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
                4,0
  
 };


/*
*| vsepcald.{
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
*| vsepcald.{
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
*| vsepcald.{
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
*| vsepcald.{
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
*| vsepcald.{
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
*| vsepcald.{
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
                0,0,1,0

 };

/*
*| vsepcald.{
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
*| vsepcald.{
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
*| vsepcald.{
*|   KeVSEP_ACReq_pin79_Status{
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Caution: configuration for VSEP MULTI channels";
*|   }
*|   }
*/



const VSEP_MPIO_Input_Mode_T KeVSEP_ACReq_pin79_Status = VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT;

/*
*| vsepcald.{
*|   KeVSEP_PSPS_pin60_Status{
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Caution: configuration for VSEP MULTI channels";
*|   }
*|   }
*/


const VSEP_MPIO_Input_Mode_T KeVSEP_PSPS_pin60_Status = VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT;
/*
*| vsepcald.{
*|   KeVSEP_MIDAC_pin40_Status{
*|       :is_calconst;
*|       :units = "type";
*|       :description = "Caution: configuration for VSEP MULTI channels";
*|   }
*|   }
*/


const VSEP_MPIO_Input_Mode_T KeVSEP_MIDAC_pin40_Status = VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT;


/*
*| vsepcald.{
*|   KsVSEP_Diagnostic_Counter_Thd {
*|     : is_calconst;
*|     : description ="threshold of fault counter(7.8ms/counter), if exceed, the coresponding channel will disabled untill key on again";
*|     : type = types.t_count_word;
*|     : units = "count";
*|   }
*|   }
*/


const   uint16_t KsVSEP_Diagnostic_Counter_Thd = 16;



