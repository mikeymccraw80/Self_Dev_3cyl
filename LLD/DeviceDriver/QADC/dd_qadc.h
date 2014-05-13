#ifndef DD_QADC_H
#define DD_QADC_H


//=============================================================================
// Standard Include Files
//=============================================================================
#include "reuse.h"

//=============================================================================
// Include Files
//=============================================================================
#include "hw_qadc.h"
#include "hw_adc.h"

//=============================================================================
// @globalv QADC_T | QADC |
// The Register Memory Overlay of the Enhanced Queued Analog-to-Digital Converter
// to provide software access and debug information.
//
// @end
//=============================================================================
#define SECTION_QADC_REGISTER
#include "section.h"
extern QADC_T QADC;
#define SECTION_END
#include "section.h"


typedef enum
{
   QADC_DEVICE_A,
   QADC_DEVICE_MAX

}  QADC_Index_T;

//=============================================================================
// @enum QADC_Trigger_Input_Select_T | Specifies the input for eQADC trigger
//=============================================================================
typedef enum QADC_Trigger_Input_Select_1_Tag
{
   QADC_TRIGGER_SELECT_1_eTRIG0          = 0,
   QADC_TRIGGER_SELECT_1_eTRIG1          = 0,

   QADC_TRIGGER_SELECT_1_RTI_TRIGGER     = 1,
   QADC_TRIGGER_SELECT_1_PIT0_TRIGGER    = 2,
   QADC_TRIGGER_SELECT_1_PIT1_TRIGGER    = 3,
   QADC_TRIGGER_SELECT_1_PIT2_TRIGGER    = 4,
   QADC_TRIGGER_SELECT_1_PIT3_TRIGGER    = 5,
   QADC_TRIGGER_SELECT_1_RESERVED6       = 6,

   QADC_TRIGGER_SELECT_1_eTRIG3          = 7,
   QADC_TRIGGER_SELECT_1_eTRIG2          = 7,

   QADC_TRIGGER_SELECT_1_eTPU30_PIT0     = 8,
   QADC_TRIGGER_SELECT_1_eTPU31_PIT0     = 8,

   QADC_TRIGGER_SELECT_1_eTPU30_PIT1     = 9,
   QADC_TRIGGER_SELECT_1_eTPU31_PIT1     = 9,

   QADC_TRIGGER_SELECT_1_RESERVED10     = 10,
   QADC_TRIGGER_SELECT_1_RESERVED11     = 11,
   QADC_TRIGGER_SELECT_1_eTPU28         = 12,
   QADC_TRIGGER_SELECT_1_eTPU29         = 13,
   QADC_TRIGGER_SELECT_1_eTPU30         = 14,
   QADC_TRIGGER_SELECT_1_eTPU31         = 15,
   QADC_TRIGGER_SELECT_1_RESERVED16     = 16,
   QADC_TRIGGER_SELECT_1_RESERVED17     = 17,
   QADC_TRIGGER_SELECT_1_RESERVED18     = 18,
   QADC_TRIGGER_SELECT_1_RESERVED19     = 19,

   QADC_TRIGGER_SELECT_1_eMIOS10_PIT2   = 20,
   QADC_TRIGGER_SELECT_1_eMIOS11_PIT2   = 20,

   QADC_TRIGGER_SELECT_1_eMIOS10_PIT3   = 21,
   QADC_TRIGGER_SELECT_1_eMIOS11_PIT3   = 21,

   QADC_TRIGGER_SELECT_1_RESERVED4      = 22,
   QADC_TRIGGER_SELECT_1_RESERVED5      = 23,
   QADC_TRIGGER_SELECT_1_RESERVED24     = 24,
   QADC_TRIGGER_SELECT_1_RESERVED25     = 25,
   QADC_TRIGGER_SELECT_1_RESERVED26     = 26,
   QADC_TRIGGER_SELECT_1_RESERVED27     = 27,
   QADC_TRIGGER_SELECT_1_RESERVED28     = 28,
   QADC_TRIGGER_SELECT_1_RESERVED29     = 29,
   QADC_TRIGGER_SELECT_1_RESERVED30     = 30,
   QADC_TRIGGER_SELECT_1_eMIOS23        = 31

} QADC_Trigger_Input_Select_1_T;


//=============================================================================
// @emem QADC_ALT_Config_Select_T |
// Selects one of the alternate configurations.
//=============================================================================
typedef enum QADC_ALT_Config_Select_Tag
{
   QADC_CONFIGURATION_REGISTER_1       = 0x08,
   QADC_CONFIGURATION_REGISTER_2       = 0x09,
   QADC_CONFIGURATION_REGISTER_3       = 0x0A,
   QADC_CONFIGURATION_REGISTER_4       = 0x0B,
   QADC_CONFIGURATION_REGISTER_5       = 0x0C,
   QADC_CONFIGURATION_REGISTER_6       = 0x0D,
   QADC_CONFIGURATION_REGISTER_7       = 0x0E,
   QADC_CONFIGURATION_REGISTER_8       = 0x0F

}  QADC_ALT_Config_Select_T;

//=============================================================================
// @globalv QADC_T | QADC |
// The Register Memory Overlay of the Enhanced Queued Analog-to-Digital Converter
// to provide software access and debug information.
//
// @end
//=============================================================================

// @enum ADC_Converter_T | The Analog to Digital Converter used by the Command
typedef enum ADC_Converter_Tag
{
   ADC_CONVERTER_0,  // @emem 0x00
   ADC_CONVERTER_1,  // @emem 0x01
   ADC_CONVERTER_MAX // @emem 0x06

}  ADC_Converter_T;

// @enum QADC_Fifo_Index_T | The Index to the Command, Receive Fifos and Status Registers
typedef enum QADC_Fifo_Index_Tag
{
   QADC_FIFO_0,  // @emem 0x00
   QADC_FIFO_1,  // @emem 0x01
   QADC_FIFO_2,  // @emem 0x02
   QADC_FIFO_3,  // @emem 0x03
   QADC_FIFO_4,  // @emem 0x04
   QADC_FIFO_5,  // @emem 0x05
   QADC_FIFO_MAX // @emem 0x06

}  QADC_Fifo_Index_T;

// @enum QADC_Channel_T | CFIFO (CHANNEL)
typedef enum QADC_Channel_Tag
{
   QADC_CHANNEL_AN0_DAN_0_P,        // @emem 0x00
   QADC_CHANNEL_AN1_DAN_0_N,        // @emem 0x01
   QADC_CHANNEL_AN2_DAN_1_P,        // @emem 0x02
   QADC_CHANNEL_AN3_DAN_1_N,        // @emem 0x03
   QADC_CHANNEL_AN4_DAN_2_P,        // @emem 0x04
   QADC_CHANNEL_AN5_DAN_2_N,        // @emem 0x05
   QADC_CHANNEL_AN6_DAN_3_P,        // @emem 0x06
   QADC_CHANNEL_AN7_DAN_3_N,        // @emem 0x07
   QADC_CHANNEL_AN8_ANW,            // @emem 0x08
   QADC_CHANNEL_AN9_ANX,            // @emem 0x09
   QADC_CHANNEL_AN10_ANY,           // @emem 0x0A
   QADC_CHANNEL_AN11_ANZ,           // @emem 0x0B
   QADC_CHANNEL_AN12_MA0_SDS,       // @emem 0x0C
   QADC_CHANNEL_AN13_MA1_SDO,       // @emem 0x0D
   QADC_CHANNEL_AN14_MA2_SDI,       // @emem 0x0E
   QADC_CHANNEL_AN15_FCK,           // @emem 0x0F
   QADC_CHANNEL_AN16,               // @emem 0x10
   QADC_CHANNEL_AN17,               // @emem 0x11
   QADC_CHANNEL_AN18,               // @emem 0x12
   QADC_CHANNEL_AN19,               // @emem 0x13
   QADC_CHANNEL_AN20,               // @emem 0x14
   QADC_CHANNEL_AN21,               // @emem 0x15
   QADC_CHANNEL_AN22,               // @emem 0x16
   QADC_CHANNEL_AN23,               // @emem 0x17
   QADC_CHANNEL_AN24,               // @emem 0x18
   QADC_CHANNEL_AN25,               // @emem 0x19
   QADC_CHANNEL_AN26,               // @emem 0x1A
   QADC_CHANNEL_AN27,               // @emem 0x1B
   QADC_CHANNEL_AN28,               // @emem 0x1C
   QADC_CHANNEL_AN29,               // @emem 0x1D
   QADC_CHANNEL_AN30,               // @emem 0x1E
   QADC_CHANNEL_AN31,               // @emem 0x1F
   QADC_CHANNEL_AN32,               // @emem 0x20
   QADC_CHANNEL_AN33,               // @emem 0x21
   QADC_CHANNEL_AN34,               // @emem 0x22
   QADC_CHANNEL_AN35,               // @emem 0x23
   QADC_CHANNEL_AN36,               // @emem 0x24
   QADC_CHANNEL_AN37,               // @emem 0x25
   QADC_CHANNEL_AN38,               // @emem 0x26
   QADC_CHANNEL_AN39,               // @emem 0x27
   QADC_CHANNEL_AN_VRH,             // @emem 0x28
   QADC_CHANNEL_AN_VRL,             // @emem 0x29
   QADC_CHANNEL_AN_VRH_VRL_DIV_2,   // @emem 0x2A
   QADC_CHANNEL_AN_75VRH_VRL_DIV_2, // @emem 0x2B
   QADC_CHANNEL_AN_25VRH_VRL_DIV_2, // @emem 0x2C
   QADC_CHANNEL_AN45_RESERVED,      // @emem 0x2D
   QADC_CHANNEL_AN46_RESERVED,      // @emem 0x2E
   QADC_CHANNEL_AN47_RESERVED,      // @emem 0x2F
   QADC_CHANNEL_AN48_RESERVED,      // @emem 0x30
   QADC_CHANNEL_AN49_RESERVED,      // @emem 0x31
   QADC_CHANNEL_AN50_RESERVED,      // @emem 0x32
   QADC_CHANNEL_AN51_RESERVED,      // @emem 0x33
   QADC_CHANNEL_AN52_RESERVED,      // @emem 0x34
   QADC_CHANNEL_AN53_RESERVED,      // @emem 0x35
   QADC_CHANNEL_AN54_RESERVED,      // @emem 0x36
   QADC_CHANNEL_AN55_RESERVED,      // @emem 0x37
   QADC_CHANNEL_AN56_RESERVED,      // @emem 0x38
   QADC_CHANNEL_AN57_RESERVED,      // @emem 0x39
   QADC_CHANNEL_AN58_RESERVED,      // @emem 0x3A
   QADC_CHANNEL_AN59_RESERVED,      // @emem 0x3B
   QADC_CHANNEL_AN60_RESERVED,      // @emem 0x3C
   QADC_CHANNEL_AN61_RESERVED,      // @emem 0x3D
   QADC_CHANNEL_AN62_RESERVED,      // @emem 0x3E
   QADC_CHANNEL_AN63_RESERVED,      // @emem 0x3F
   QADC_CHANNEL_ANW_0,              // @emem 0x40
   QADC_CHANNEL_ANW_1,              // @emem 0x41
   QADC_CHANNEL_ANW_2,              // @emem 0x42
   QADC_CHANNEL_ANW_3,              // @emem 0x43
   QADC_CHANNEL_ANW_4,              // @emem 0x44
   QADC_CHANNEL_ANW_5,              // @emem 0x45
   QADC_CHANNEL_ANW_6,              // @emem 0x46
   QADC_CHANNEL_ANW_7,              // @emem 0x47
   QADC_CHANNEL_ANX_0,              // @emem 0x48
   QADC_CHANNEL_ANX_1,              // @emem 0x49
   QADC_CHANNEL_ANX_2,              // @emem 0x4A
   QADC_CHANNEL_ANX_3,              // @emem 0x4B
   QADC_CHANNEL_ANX_4,              // @emem 0x4C
   QADC_CHANNEL_ANX_5,              // @emem 0x4D
   QADC_CHANNEL_ANX_6,              // @emem 0x4E
   QADC_CHANNEL_ANX_7,              // @emem 0x4F
   QADC_CHANNEL_ANY_0,              // @emem 0x50
   QADC_CHANNEL_ANY_1,              // @emem 0x51
   QADC_CHANNEL_ANY_2,              // @emem 0x52
   QADC_CHANNEL_ANY_3,              // @emem 0x53
   QADC_CHANNEL_ANY_4,              // @emem 0x54
   QADC_CHANNEL_ANY_5,              // @emem 0x55
   QADC_CHANNEL_ANY_6,              // @emem 0x56
   QADC_CHANNEL_ANY_7,              // @emem 0x57
   QADC_CHANNEL_ANZ_0,              // @emem 0x58
   QADC_CHANNEL_ANZ_1,              // @emem 0x59
   QADC_CHANNEL_ANZ_2,              // @emem 0x5A
   QADC_CHANNEL_ANZ_3,              // @emem 0x5B
   QADC_CHANNEL_ANZ_4,              // @emem 0x5C
   QADC_CHANNEL_ANZ_5,              // @emem 0x5D
   QADC_CHANNEL_ANZ_6,              // @emem 0x5E
   QADC_CHANNEL_ANZ_7,              // @emem 0x5F
   QADC_CHANNEL_DAN_0,              // @emem 0x60
   QADC_CHANNEL_DAN_1,              // @emem 0x61
   QADC_CHANNEL_DAN_2,              // @emem 0x62
   QADC_CHANNEL_DAN_3,              // @emem 0x63
   QADC_CHANNEL_AN100_RESERVED,     // @emem 0x64
   QADC_CHANNEL_AN101_RESERVED,     // @emem 0x65
   QADC_CHANNEL_AN102_RESERVED,     // @emem 0x66
   QADC_CHANNEL_AN103_RESERVED,     // @emem 0x67
   QADC_CHANNEL_AN104_RESERVED,     // @emem 0x68
   QADC_CHANNEL_AN105_RESERVED,     // @emem 0x69
   QADC_CHANNEL_AN106_RESERVED,     // @emem 0x6A
   QADC_CHANNEL_AN107_RESERVED,     // @emem 0x6B
   QADC_CHANNEL_AN108_RESERVED,     // @emem 0x6C
   QADC_CHANNEL_AN109_RESERVED,     // @emem 0x6D
   QADC_CHANNEL_AN110_RESERVED,     // @emem 0x6E
   QADC_CHANNEL_AN111_RESERVED,     // @emem 0x6F
   QADC_CHANNEL_AN112_RESERVED,     // @emem 0x70
   QADC_CHANNEL_AN113_RESERVED,     // @emem 0x71
   QADC_CHANNEL_AN114_RESERVED,     // @emem 0x72
   QADC_CHANNEL_AN115_RESERVED,     // @emem 0x73
   QADC_CHANNEL_AN116_RESERVED,     // @emem 0x74
   QADC_CHANNEL_AN117_RESERVED,     // @emem 0x75
   QADC_CHANNEL_AN118_RESERVED,     // @emem 0x76
   QADC_CHANNEL_AN119_RESERVED,     // @emem 0x77
   QADC_CHANNEL_AN120_RESERVED,     // @emem 0x78
   QADC_CHANNEL_AN121_RESERVED,     // @emem 0x79
   QADC_CHANNEL_AN122_RESERVED,     // @emem 0x7A
   QADC_CHANNEL_AN123_RESERVED,     // @emem 0x7B
   QADC_CHANNEL_AN124_RESERVED,     // @emem 0x7C
   QADC_CHANNEL_AN125_RESERVED,     // @emem 0x7D
   QADC_CHANNEL_AN126_RESERVED,     // @emem 0x7E
   QADC_CHANNEL_AN127_RESERVED,     // @emem 0x7F
   QADC_CHANNEL_AN128_TEMP_SENSOR,  // @emem 0x80
   QADC_CHANNEL_AN129_SPARE,        // @emem 0x81
   QADC_CHANNEL_AN130_RESERVED,     // @emem 0x64
   QADC_CHANNEL_AN131_RESERVED,     // @emem 0x65
   QADC_CHANNEL_AN132_RESERVED,     // @emem 0x66
   QADC_CHANNEL_AN133_RESERVED,     // @emem 0x67
   QADC_CHANNEL_AN134_RESERVED,     // @emem 0x68
   QADC_CHANNEL_AN135_RESERVED,     // @emem 0x69
   QADC_CHANNEL_AN136_RESERVED,     // @emem 0x6A
   QADC_CHANNEL_AN137_RESERVED,     // @emem 0x6B
   QADC_CHANNEL_AN138_RESERVED,     // @emem 0x6C
   QADC_CHANNEL_AN139_RESERVED,     // @emem 0x6D
   QADC_CHANNEL_AN140_RESERVED,     // @emem 0x6E
   QADC_CHANNEL_AN141_RESERVED,     // @emem 0x6F
   QADC_CHANNEL_AN142_RESERVED,     // @emem 0x70
   QADC_CHANNEL_AN143_RESERVED,     // @emem 0x71
   QADC_CHANNEL_AN144_RESERVED,     // @emem 0x72
   QADC_CHANNEL_AN145_RESERVED,     // @emem 0x73
   QADC_CHANNEL_AN146_RESERVED,     // @emem 0x74
   QADC_CHANNEL_AN147_RESERVED,     // @emem 0x75
   QADC_CHANNEL_AN148_RESERVED,     // @emem 0x76
   QADC_CHANNEL_AN149_RESERVED,     // @emem 0x77
   QADC_CHANNEL_AN150_RESERVED,     // @emem 0x78
   QADC_CHANNEL_AN151_RESERVED,     // @emem 0x79
   QADC_CHANNEL_AN152_RESERVED,     // @emem 0x7A
   QADC_CHANNEL_AN153_RESERVED,     // @emem 0x7B
   QADC_CHANNEL_AN154_RESERVED,     // @emem 0x7C
   QADC_CHANNEL_AN155_RESERVED,     // @emem 0x7D
   QADC_CHANNEL_AN156_RESERVED,     // @emem 0x7E
   QADC_CHANNEL_AN157_RESERVED,     // @emem 0x7F
   QADC_CHANNEL_AN158_RESERVED,     // @emem 0x7C
   QADC_CHANNEL_AN159_RESERVED,     // @emem 0x7D
   QADC_CHANNEL_AN160_RESERVED,     // @emem 0x7E
   QADC_CHANNEL_AN161_RESERVED,     // @emem 0x7F
   QADC_CHANNEL_AN162_VDDEH1B_50,   // @emem 0x7C
   QADC_CHANNEL_AN163_VDDEH4A_50,   // @emem 0x7D
   QADC_CHANNEL_AN164_VDDEH4B_50,   // @emem 0x7E
   QADC_CHANNEL_AN165_VDDEH6A_50,   // @emem 0x7F
   QADC_CHANNEL_AN166_VDDEH6B_50,   // @emem 0x7C
   QADC_CHANNEL_AN167_VDDEH7_50,    // @emem 0x7D
   QADC_CHANNEL_AN168_RESERVED,     // @emem 0x7E
   QADC_CHANNEL_AN169_RESERVED,     // @emem 0x7F
   QADC_CHANNEL_AN170_RESERVED,     // @emem 0x64
   QADC_CHANNEL_AN171_RESERVED,     // @emem 0x65
   QADC_CHANNEL_AN172_RESERVED,     // @emem 0x66
   QADC_CHANNEL_AN173_RESERVED,     // @emem 0x67
   QADC_CHANNEL_AN174_RESERVED,     // @emem 0x68
   QADC_CHANNEL_AN175_RESERVED,     // @emem 0x69
   QADC_CHANNEL_AN176_RESERVED,     // @emem 0x6A
   QADC_CHANNEL_AN177_RESERVED,     // @emem 0x6B
   QADC_CHANNEL_AN178_RESERVED,     // @emem 0x6C
   QADC_CHANNEL_AN179_RESERVED,     // @emem 0x6D
   QADC_CHANNEL_AN180_RESERVED,     // @emem 0x6E
   QADC_CHANNEL_AN181_RESERVED,     // @emem 0x6F
   QADC_CHANNEL_AN182_RESERVED,     // @emem 0x70
   QADC_CHANNEL_AN183_RESERVED,     // @emem 0x71
   QADC_CHANNEL_AN184_RESERVED,     // @emem 0x72
   QADC_CHANNEL_AN185_RESERVED,     // @emem 0x73
   QADC_CHANNEL_AN186_RESERVED,     // @emem 0x74
   QADC_CHANNEL_AN187_RESERVED,     // @emem 0x75
   QADC_CHANNEL_AN188_RESERVED,     // @emem 0x76
   QADC_CHANNEL_AN189_RESERVED,     // @emem 0x77
   QADC_CHANNEL_AN190_RESERVED,     // @emem 0x78
   QADC_CHANNEL_AN191_RESERVED,     // @emem 0x79
   QADC_CHANNEL_AN192_RESERVED,     // @emem 0x7A
   QADC_CHANNEL_AN193_RESERVED,     // @emem 0x7B
   QADC_CHANNEL_AN194_VDD12,        // @emem 0x7C
   QADC_CHANNEL_AN195_LVI12,        // @emem 0x7D
   QADC_CHANNEL_AN196_VDD33,        // @emem 0x7E
   QADC_CHANNEL_AN197_LVI33,        // @emem 0x7F
   QADC_CHANNEL_AN198_LVI50_50,     // @emem 0x7C
   QADC_CHANNEL_AN199_VDDEH1A_50,   // @emem 0x7D
   QADC_CHANNEL_AN200_RESERVED,     // @emem 0x7E
   QADC_CHANNEL_AN201_RESERVED,     // @emem 0x7F
   QADC_CHANNEL_AN202_RESERVED,     // @emem 0x66
   QADC_CHANNEL_AN203_RESERVED,     // @emem 0x67
   QADC_CHANNEL_AN204_RESERVED,     // @emem 0x68
   QADC_CHANNEL_AN205_RESERVED,     // @emem 0x69
   QADC_CHANNEL_AN206_RESERVED,     // @emem 0x6A
   QADC_CHANNEL_AN207_RESERVED,     // @emem 0x6B
   QADC_CHANNEL_AN208_RESERVED,     // @emem 0x6C
   QADC_CHANNEL_AN209_RESERVED,     // @emem 0x6D
   QADC_CHANNEL_AN210_RESERVED,     // @emem 0x6E
   QADC_CHANNEL_AN211_RESERVED,     // @emem 0x6F
   QADC_CHANNEL_AN212_RESERVED,     // @emem 0x70
   QADC_CHANNEL_AN213_RESERVED,     // @emem 0x71
   QADC_CHANNEL_AN214_RESERVED,     // @emem 0x72
   QADC_CHANNEL_AN215_RESERVED,     // @emem 0x73
   QADC_CHANNEL_AN216_RESERVED,     // @emem 0x74
   QADC_CHANNEL_AN217_RESERVED,     // @emem 0x75
   QADC_CHANNEL_AN218_RESERVED,     // @emem 0x76
   QADC_CHANNEL_AN219_RESERVED,     // @emem 0x77
   QADC_CHANNEL_AN220_RESERVED,     // @emem 0x78
   QADC_CHANNEL_AN221_RESERVED,     // @emem 0x79
   QADC_CHANNEL_AN222_RESERVED,     // @emem 0x7A
   QADC_CHANNEL_AN223_RESERVED,     // @emem 0x7B
   QADC_CHANNEL_AN224_RESERVED,     // @emem 0x7C
   QADC_CHANNEL_AN225_RESERVED,     // @emem 0x7D
   QADC_CHANNEL_AN226_RESERVED,     // @emem 0x7E
   QADC_CHANNEL_AN227_RESERVED,     // @emem 0x7F
   QADC_CHANNEL_AN228_RESERVED,     // @emem 0x64
   QADC_CHANNEL_AN229_RESERVED,     // @emem 0x65
   QADC_CHANNEL_AN230_RESERVED,     // @emem 0x66
   QADC_CHANNEL_AN231_RESERVED,     // @emem 0x65
   QADC_CHANNEL_AN232_RESERVED,     // @emem 0x65
   QADC_CHANNEL_AN233_RESERVED,     // @emem 0x67
   QADC_CHANNEL_AN234_RESERVED,     // @emem 0x68
   QADC_CHANNEL_AN235_RESERVED,     // @emem 0x69
   QADC_CHANNEL_AN236_RESERVED,     // @emem 0x6A
   QADC_CHANNEL_AN237_RESERVED,     // @emem 0x6B
   QADC_CHANNEL_AN238_RESERVED,     // @emem 0x6C
   QADC_CHANNEL_AN239_RESERVED,     // @emem 0x6D
   QADC_CHANNEL_AN240_RESERVED,     // @emem 0x6E
   QADC_CHANNEL_AN241_RESERVED,     // @emem 0x6F
   QADC_CHANNEL_AN242_RESERVED,     // @emem 0x70
   QADC_CHANNEL_AN243_RESERVED,     // @emem 0x71
   QADC_CHANNEL_AN244_RESERVED,     // @emem 0x72
   QADC_CHANNEL_AN245_RESERVED,     // @emem 0x73
   QADC_CHANNEL_AN246_RESERVED,     // @emem 0x74
   QADC_CHANNEL_AN247_RESERVED,     // @emem 0x75
   QADC_CHANNEL_AN248_RESERVED,     // @emem 0x76
   QADC_CHANNEL_AN249_RESERVED,     // @emem 0x77
   QADC_CHANNEL_AN250_RESERVED,     // @emem 0x78
   QADC_CHANNEL_AN251_RESERVED,     // @emem 0x79
   QADC_CHANNEL_AN252_RESERVED,     // @emem 0x7A
   QADC_CHANNEL_AN253_RESERVED,     // @emem 0x7B
   QADC_CHANNEL_AN254_RESERVED,     // @emem 0x7C
   QADC_CHANNEL_AN255_RESERVED,     // @emem 0x7D
   QADC_CHANNEL_MAX

}  QADC_Channel_T;

//=============================================================================
// @enum QADC_Trigger_Input_Select_T | Specifies the input for eQADC trigger
//=============================================================================
typedef enum QADC_Trigger_Input_Select_Tag
{
   QADC_TRIGGER_INPUT_SELECT_0_GPIO_206 = 0, //@emem TSEL0 QADC trigger input select 0. 00b General Purpose IO 206
   QADC_TRIGGER_INPUT_SELECT_1_GPIO_207 = 0, //@emem TSEL1 QADC trigger input select 1. 00b General Purpose IO 207
   QADC_TRIGGER_INPUT_SELECT_2_GPIO_206 = 0, //@emem TSEL2 QADC trigger input select 2. 00b General Purpose IO 206
   QADC_TRIGGER_INPUT_SELECT_3_GPIO_207 = 0, //@emem TSEL3 QADC trigger input select 3. 00b General Purpose IO 207
   QADC_TRIGGER_INPUT_SELECT_4_GPIO_206 = 0, //@emem TSEL4 QADC trigger input select 4. 00b General Purpose IO 206
   QADC_TRIGGER_INPUT_SELECT_5_GPIO_207 = 0, //@emem TSEL5 QADC trigger input select 5. 00b General Purpose IO 207
   QADC_TRIGGER_INPUT_SELECT_0_eTSEL0   = 0, //@emem TSEL0 QADC trigger input select 0 00b eTSEL0 (described in SIU_ISEL3)
   QADC_TRIGGER_INPUT_SELECT_1_eTSEL1   = 0, //@emem TSEL1 QADC trigger input select 0 00b eTSEL1 (described in SIU_ISEL3)
   QADC_TRIGGER_INPUT_SELECT_2_eTSEL2   = 0, //@emem TSEL2 QADC trigger input select 0 00b eTSEL2 (described in SIU_ISEL3)
   QADC_TRIGGER_INPUT_SELECT_3_eTSEL3   = 0, //@emem TSEL3 QADC trigger input select 0 00b eTSEL3 (described in SIU_ISEL3)
   QADC_TRIGGER_INPUT_SELECT_4_eTSEL4   = 0, //@emem TSEL4 QADC trigger input select 0 00b eTSEL4 (described in SIU_ISEL3)
   QADC_TRIGGER_INPUT_SELECT_5_eTSEL5   = 0, //@emem TSEL5 QADC trigger input select 0 00b eTSEL5 (described in SIU_ISEL3)
   QADC_TRIGGER_INPUT_SELECT_0_TPU_A_30 = 1, //@emem TSEL0 QADC trigger input select 0. 01b enhanced Timer Processor A channel 30
   QADC_TRIGGER_INPUT_SELECT_1_TPU_A_31 = 1, //@emem TSEL1 QADC trigger input select 1. 01b enhanced Timer Processor A channel 31
   QADC_TRIGGER_INPUT_SELECT_2_TPU_A_29 = 1, //@emem TSEL2 QADC trigger input select 2. 01b enhanced Timer Processor A channel 29
   QADC_TRIGGER_INPUT_SELECT_3_TPU_A_28 = 1, //@emem TSEL3 QADC trigger input select 3. 01b enhanced Timer Processor A channel 28
   QADC_TRIGGER_INPUT_SELECT_4_TPU_A_27 = 1, //@emem TSEL4 QADC trigger input select 4. 01b enhanced Timer Processor A channel 27
   QADC_TRIGGER_INPUT_SELECT_5_TPU_A_26 = 1, //@emem TSEL5 QADC trigger input select 5. 01b enhanced Timer Processor A channel 26
   QADC_TRIGGER_INPUT_SELECT_0_MIOS_10 = 2,  //@emem TSEL0 QADC trigger input select 0. 10b enhanced Modular Input/Output Subsystem channel 10
   QADC_TRIGGER_INPUT_SELECT_1_MIOS_11 = 2,  //@emem TSEL1 QADC trigger input select 1. 10b enhanced Modular Input/Output Subsystem channel 11
   QADC_TRIGGER_INPUT_SELECT_2_MIOS_15 = 2,  //@emem TSEL2 QADC trigger input select 2. 10b enhanced Modular Input/Output Subsystem channel 15
   QADC_TRIGGER_INPUT_SELECT_3_MIOS_14 = 2,  //@emem TSEL3 QADC trigger input select 3. 10b enhanced Modular Input/Output Subsystem channel 14
   QADC_TRIGGER_INPUT_SELECT_4_MIOS_13 = 2,  //@emem TSEL4 QADC trigger input select 4. 10b enhanced Modular Input/Output Subsystem channel 13
   QADC_TRIGGER_INPUT_SELECT_5_MIOS_12 = 2,  //@emem TSEL5 QADC trigger input select 5. 10b enhanced Modular Input/Output Subsystem channel 12
   QADC_TRIGGER_INPUT_SELECT_0_ETRIG_0 = 3,  //@emem TSEL0 QADC trigger input select 0. 11b external trigger pin 0
   QADC_TRIGGER_INPUT_SELECT_1_ETRIG_1 = 3,  //@emem TSEL1 QADC trigger input select 1. 11b external trigger pin 1
   QADC_TRIGGER_INPUT_SELECT_2_ETRIG_0 = 3,  //@emem TSEL2 QADC trigger input select 2. 11b external trigger pin 0
   QADC_TRIGGER_INPUT_SELECT_3_ETRIG_1 = 3,  //@emem TSEL3 QADC trigger input select 3. 11b external trigger pin 1
   QADC_TRIGGER_INPUT_SELECT_4_ETRIG_0 = 3,  //@emem TSEL4 QADC trigger input select 4. 11b external trigger pin 0
   QADC_TRIGGER_INPUT_SELECT_5_ETRIG_1 = 3   //@emem TSEL5 QADC trigger input select 5. 11b external trigger pin 1

} QADC_Trigger_Input_Select_T;


//=============================================================================
// Enumeration: Last CFIFO to Transfer to CBuffern (n=0,1). (LCFTCBn)
//
//  LCFTCBn[3:0]                   LCFTCBn Meaning
//
// ==============  ==========================================================
//     0b0000      Last command was transferred from CFIFO0
//     0b0001      Last command was transferred from CFIFO1
//     0b0010      Last command was transferred from CFIFO2
//     0b0011      Last command was transferred from CFIFO3
//     0b0100      Last command was transferred from CFIFO4
//     0b0101      Last command was transferred from CFIFO5
//     0b0110 to   Reserved
//     0b1110
//     0b1111      No command was transferred to CBuffern
//
//=============================================================================
typedef enum QADC_CFSSR_LCFTCBn_Tag
{
   QADC_CFSSR_LCFTCBn_CFIFO_0,
   QADC_CFSSR_LCFTCBn_CFIFO_1,
   QADC_CFSSR_LCFTCBn_CFIFO_2,
   QADC_CFSSR_LCFTCBn_CFIFO_3,
   QADC_CFSSR_LCFTCBn_CFIFO_4,
   QADC_CFSSR_LCFTCBn_CFIFO_5,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED1,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED2,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED3,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED4,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED5,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED6,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED7,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED8,
   QADC_CFSSR_LCFTCBn_CFIFO_RESERVED9,
   QADC_CFSSR_LCFTCBn_NO_CMD

}  QADC_CFSSR_LCFTCBn_T;

//=============================================================================
// Enumeration: Current CFIFO Status. (CFSx)
//
//  CFIFO Status  Field          Explanation
//                Value
//                [1:0]
// ============= ======== ===================================================
//   IDLE           0b00  CFIFO is disabled.
//                        CFIFO is in single-scan edge or level trigger
//                        mode and does not have SSS asserted.
//                        QADC completed the transfer of the last entry
//                        of the CQueue in single-scan mode.
//
//   Reserved       0b01  Not applicable.
//
//   WAITING        0b10  CFIFO Mode is modified to continuous-scan edge or
//    FOR                 level trigger mode.
//   TRIGGER              CFIFO Mode is modified to single-scan edge or
//                        level trigger mode and SSS is asserted.
//                        CFIFO Mode is modified to single-scan software
//                        trigger mode and SSS is negated.
//                        CFIFO is paused.
//                        QADC transferred the last entry of the queue in
//                        continuous-scan edge trigger mode.
//
//  TRIGGERED       0b11  CFIFO is triggered
//
//=============================================================================
typedef enum QADC_CFSR_CFS_Tag
{
   QADC_CFSR_CFS_IDLE,
   QADC_CFSR_CFS_RESERVED,
   QADC_CFSR_CFS_WAIT_FOR_TRIG,
   QADC_CFSR_CFS_TRIGRD

}  QADC_CFSR_CFS_T;


//=============================================================================
// IDCRn (Interrupt and DMA Control Registers [0-5])
//=============================================================================
typedef enum QADC_IDCR_Interrupt_Dma_Tag
{
   QADC_IDCR_REQUEST_INTERRUPT,
   QADC_IDCR_REQUEST_DMA_TRANSFER

}  QADC_IDCR_Interrupt_Dma_T;


//=============================================================================
// REDBS (RedLine Time Base Selection)
//=============================================================================
typedef enum QADC_REDBS_RedLine_Timebase_Selection_Tag
{
   QADC_REDBS_TBASE_0_15,
   QADC_REDBS_TBASE_1_16,
   QADC_REDBS_TBASE_2_17,
   QADC_REDBS_TBASE_3_18,
   QADC_REDBS_TBASE_4_19,
   QADC_REDBS_TBASE_5_20,
   QADC_REDBS_TBASE_6_21,
   QADC_REDBS_TBASE_7_22,
   QADC_REDBS_TBASE_8_23,
   QADC_REDBS_TBASE_RESERVED1,
   QADC_REDBS_TBASE_RESERVED2,
   QADC_REDBS_TBASE_RESERVED3,
   QADC_REDBS_TBASE_RESERVED4,
   QADC_REDBS_TBASE_RESERVED5,
   QADC_REDBS_TBASE_RESERVED6,
   QADC_REDBS_TBASE_RESERVED7

}  QADC_REDBS_RedLine_Timebase_Selection_T;

//=============================================================================
// REDBS (RedLine Time Base Selection)
//=============================================================================
typedef enum QADC_REDBS_RedLine_Server_Data_Slot_Selector_Tag
{
   QADC_SRV_eTPUA_TCR1       = 0,
   QADC_SRV_eTPUB_TCR1       = 1,
   QADC_SRV_eTPUB_RESERVED0  = 1,
   QADC_SRV_eTPUA_TCR2       = 2,
   QADC_SRV_eTPUA_RESERVED   = 2,
   QADC_SRV_eTPUB_TCR2       = 3,
   QADC_SRV_eTPUB_RESERVED1  = 3,
   QADC_SRV_eTPUC_TCR1       = 4,
   QADC_SRV_eTPUC_RESERVED0  = 4,
   QADC_SRV_eTPUC_TCR2       = 5,
   QADC_SRV_eTPUC_RESERVED1  = 5,
   QADC_SRV_TBASE_RESERVED1  = 6,
   QADC_SRV_TBASE_RESERVED2  = 7,
   QADC_SRV_TBASE_RESERVED3  = 8,
   QADC_SRV_TBASE_RESERVED4  = 9,
   QADC_SRV_TBASE_RESERVED5  = 10,
   QADC_SRV_TBASE_RESERVED6  = 11,
   QADC_SRV_TBASE_RESERVED7  = 12,
   QADC_SRV_TBASE_RESERVED8  = 13,
   QADC_SRV_TBASE_RESERVED9  = 14,
   QADC_SRV_TBASE_RESERVED10 = 15

}  QADC_REDBS_RedLine_Server_Data_Slot_Selector_T;


//=============================================================================
// /------------------------------------------------------------------------
// | QADC common enumerated values
// \------------------------------------------------------------------------
//=============================================================================

//=============================================================================
// @enum QADC_Debug_Enable_T | Debug enable. Defines the eQADC response to a debug mode entry request.
//=============================================================================
typedef enum QADC_Debug_Enable_Tag
{
   QADC_DEBUG_DISABLED,             // @emem 00 Do not enter debug mode
   QADC_DEBUG_RESERVED,             // @emem 01 Reserved
   QADC_DEBUG_FCK_STOP_DEBUG_MODE,  // @emem 10 Enter debug mode. If the eQADC SSI is enabled, FCK stops while the eQADC is in debug mode.
   QADC_DEBUG_FCK_RUN_DEBUG_MODE    // @emem 11 Enter debug mode. If the eQADC SSI is enabled, FCK is free running while the eQADC is in debug mode
   
}  QADC_Debug_Enable_T;

//=============================================================================
// @enum QADC_Sync_Serial_Interface_Enable_T | eQADC synchronous serial interface enable. Defines the eQADC synchronous serial interface operation.
//=============================================================================
typedef enum QADC_Sync_Serial_Interface_Enable_Tag
{
   QADC_SYNC_SERIAL_INTERFACE_DISABLED,               // @emem 00 eQADC SSI is disabled
   QADC_SYNC_SERIAL_RESERVED,                         // @emem 01 Reserved
   QADC_SYNC_SERIAL_ENABLED_FCK_RUNNING_TX_DISABLED,  // @emem 10 eQADC SSI is enabled, FCK is free running, and serial transmissions are disabled
   QADC_SYNC_SERIAL_ENABLED_FCK_RUNNING_TX_ENABLED    // @emem 11 eQADC SSI is enabled, FCK is free running, and serial transmissions are enabled
   
}  QADC_Sync_Serial_Interface_Enable_T;

//=============================================================================
// @enum QADC_Minimum_Delay_After_Transmission_T | Minimum Delay After Transmission (tMDT) Time
//=============================================================================
typedef enum QADC_Minimum_Delay_After_Transmission_Tag
{                                                     //       MDT      tMDT (FCK period)
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_1,    // @emem 0b000         1
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_2,    // @emem 0b001         2
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_3,    // @emem 0b010         3
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_4,    // @emem 0b011         4
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_5,    // @emem 0b100         5
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_6,    // @emem 0b101         6
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_7,    // @emem 0b110         7
   QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_8     // @emem 0b111         8

}  QADC_Minimum_Delay_After_Transmission_T;

//=============================================================================
// @enum QADC_Baud_Rate_System_Clock_Divide_Factor_T | System Clock Divide Factor
//=============================================================================
typedef enum QADC_Baud_Rate_System_Clock_Divide_Factor_Tag
{                                                  //       BR[0:3]   System Clock Divide Factor
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_2,    // @emem 0b0000        2
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_3,    // @emem 0b0001        3
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_4,    // @emem 0b0010        4
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_5,    // @emem 0b0011        5
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_6,    // @emem 0b0100        6
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_7,    // @emem 0b0101        7
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_8,    // @emem 0b0110        8
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_9,    // @emem 0b0111        9
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_10,   // @emem 0b1000       10
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_11,   // @emem 0b1001       11
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_12,   // @emem 0b1010       12
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_13,   // @emem 0b1011       13
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_14,   // @emem 0b1100       14
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_15,   // @emem 0b1101       15
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_16,   // @emem 0b1110       16
   QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_17    // @emem 0b1111       17

}  QADC_Baud_Rate_System_Clock_Divide_Factor_T;

//=============================================================================
// @enum QADC_Digital_Filter_Length_T | FilterPeriod = (systemClockPeriod * 2^DFL) +
//                                           1 (systemClockPeriod )
//=============================================================================
typedef enum QADC_Digital_Filter_Length_Tag
{                                       //  DFL[0:3]     Min Clock Count  Min Time (ns) (sys clk =120MHz)
   QADC_DIGITAL_FILTER_LENGTH_2,       // @emem 0b0000           2             16.66
   QADC_DIGITAL_FILTER_LENGTH_3,       // @emem 0b0001           3             25.00
   QADC_DIGITAL_FILTER_LENGTH_5,       // @emem 0b0010           5             41.66
   QADC_DIGITAL_FILTER_LENGTH_9,       // @emem 0b0011           9             75.00
   QADC_DIGITAL_FILTER_LENGTH_17,      // @emem 0b0100          17            141.66
   QADC_DIGITAL_FILTER_LENGTH_33,      // @emem 0b0101          33            275.00
   QADC_DIGITAL_FILTER_LENGTH_65,      // @emem 0b0110          65            541.66
   QADC_DIGITAL_FILTER_LENGTH_129,     // @emem 0b0111         129           1075.00
   QADC_DIGITAL_FILTER_LENGTH_257,     // @emem 0b1000         257           2141.66
   QADC_DIGITAL_FILTER_LENGTH_513,     // @emem 0b1001         513           4275.00
   QADC_DIGITAL_FILTER_LENGTH_1025,    // @emem 0b1010        1025           8541.66
   QADC_DIGITAL_FILTER_LENGTH_2049,    // @emem 0b1011        2049          17075.00
   QADC_DIGITAL_FILTER_LENGTH_4097,    // @emem 0b1100        4097          34141.00
   QADC_DIGITAL_FILTER_LENGTH_8193,    // @emem 0b1101        8193          68275.00
   QADC_DIGITAL_FILTER_LENGTH_16385,   // @emem 0b1110       16385         136541.66
   QADC_DIGITAL_FILTER_LENGTH_32769    // @emem 0b1111       32769         273075.00

}  QADC_Digital_Filter_Length_T;

//=============================================================================
// @enum QADC_CHANNEL_Scan_State_T | 
//=============================================================================
typedef enum QADC_CHANNEL_Scan_State_Tag
{
   QADC_CHANNEL_SCAN_STATE_NO_ACTION,     // @emem 
   QADC_CHANNEL_SCAN_STATE_END_OF_QUEUE,  // @emem 
   QADC_CHANNEL_SCAN_STATE_PAUSE          // @emem 
   
}  QADC_CHANNEL_Scan_State_T;

//=============================================================================
// @enum QADC_CHANNEL_Result_Format_Format_T | 
//=============================================================================
typedef enum QADC_CHANNEL_Result_Format_Format_Tag
{
   QADC_CHANNEL_RESULT_FORMAT_RESULT_ONLY,            // @emem 0 Return conversion result only.
   QADC_CHANNEL_RESULT_FORMAT_RESULT_AND_TIME_STAMP   // @emem 1 Return conversion time stamp after the conversion result.
   
}  QADC_CHANNEL_Result_Format_Format_T;

//=============================================================================
// @enum QADC_CHANNEL_Conversion_Format_T | 
//=============================================================================
typedef enum QADC_CHANNEL_Conversion_Format_Tag
{
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED, // @emem 00 Right justified unsigned.
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_SIGNED    // @emem 01 Right justified signed.
   
}  QADC_CHANNEL_Conversion_Format_T;


//=============================================================================
// @enum QADC_Queue_External_Converter_T | External Trigger enabled
//=============================================================================
typedef enum QADC_Queue_External_Converter_Tag
{
   QADC_QUEUE_EXTERNAL_CONVERTER_DISABLED,   // @emem 0b0  QADC no external CONVERTER
   QADC_QUEUE_EXTERNAL_CONVERTER_ENABLED     // @emem 0b1  QADC external CONVERTER Present

}  QADC_Queue_External_Converter_T;

//=============================================================================
// @enum QADC_Trigger_Mode_T | CFIFO Trigger Mode  (MODE,trigger portion) 
//=============================================================================
typedef enum QADC_Trigger_Mode_Tag
{
   QADC_TRIGGER_MODE_DISABLED,                                 // @emem 0b000 Disabled
   QADC_TRIGGER_MODE_SOFTWARE_TRIGGER_Single_Scan,                         // @emem 0b001 Software Trigger
   QADC_TRIGGER_MODE_LOW_LEVEL_GATED_EXTERNAL_TRIGGER_Single_Scan,         // @emem 0b010 Low Level Gated External Trigger
   QADC_TRIGGER_MODE_HIGH_LEVEL_GATED_EXTERNAL_TRIGGER_Single_Scan,        // @emem 0b011 High Level Gated External Trigger
   QADC_TRIGGER_MODE_FALLING_EDGE_EXTERNAL_TRIGGER_Single_Scan,            // @emem 0b100 Falling Edge External Trigger
   QADC_TRIGGER_MODE_RISING_EDGE_EXTERNAL_TRIGGER_Single_Scan,             // @emem 0b101 Rising Edge External Trigger
   QADC_TRIGGER_MODE_FALLING_OR_RISING_EDGE_EXTERNAL_TRIGGER_Single_Scan,   // @emem 0b110 Falling or Rising Edge External Trigger
   QADC_TRIGGER_MODE_Reserved_1_TRIGGER ,
   QADC_TRIGGER_MODE_Reserved_2_TRIGGER ,
   QADC_TRIGGER_MODE_SOFTWARE_TRIGGER_Continuous_Scan,                         // @emem 0b001 Software Trigger
   QADC_TRIGGER_MODE_LOW_LEVEL_GATED_EXTERNAL_TRIGGER_Continuous_Scan,         // @emem 0b010 Low Level Gated External Trigger
   QADC_TRIGGER_MODE_HIGH_LEVEL_GATED_EXTERNAL_TRIGGER_Continuous_Scan,        // @emem 0b011 High Level Gated External Trigger
   QADC_TRIGGER_MODE_FALLING_EDGE_EXTERNAL_TRIGGER_Continuous_Scan,            // @emem 0b100 Falling Edge External Trigger
   QADC_TRIGGER_MODE_RISING_EDGE_EXTERNAL_TRIGGER_Continuous_Scan,             // @emem 0b101 Rising Edge External Trigger
   QADC_TRIGGER_MODE_FALLING_OR_RISING_EDGE_EXTERNAL_TRIGGER_Continuous_Scan   // @emem 0b110 Falling or Rising Edge External Trigger

}  QADC_Trigger_Mode_T;

//=============================================================================
// @enum QADC_Scan_Mode_T | CFIFO Scan Mode  (MODE,scan portion) 
//=============================================================================
typedef enum QADC_Scan_Mode_Tag
{
   QADC_SCAN_MODE_SINGLE,     // @emem 0b0 Single Scan
   QADC_SCAN_MODE_CONTINUOUS  // @emem 0b1 Continuous Scan

}  QADC_Scan_Mode_T;

//=============================================================================
// @enum QADC_Justified_T | Return the value from get analog in format specified by the configuration.
//=============================================================================
typedef enum QADC_Justified_Tag
{
   QADC_JUSTIFY_RESULT_RIGHT,   // @emem 0b0 Right justified result, left as is
   QADC_JUSTIFY_RESULT_LEFT     // @emem 0b1 Left Justified result, shifted to represent 16 bit value.

}  QADC_Justify_Result_T;


//=============================================================================
// @enum QADC_Mode_T |  
//=============================================================================
typedef enum QADC_Mode_Tag
{
   QADC_SCAN,     // @emem  
   QADC_COMMAND   // @emem 

}  QADC_Mode_T;

//=============================================================================
// @enum QADC_Command_FIFO_Status_T |
//=============================================================================
typedef enum QADC_Command_FIFO_Status_Tag
{
   QADC_COMMAND_FIFO_STATUS_IDLE,               // @emem (1)CFIFO is disabled. 
                                                //       (2)CFIFO is in single-scan edge or level trigger mode and does not have QADC.FISR[n].F.SSS asserted.
                                                //       (3)eQADC completed the transfer of the last entry of the user defined command queue in single-scan mode.
   QADC_COMMAND_FIFO_STATUS_RESERVED,           // @emem Not applicable.
   QADC_COMMAND_FIFO_STATUS_WAITING_FOR_TRIGGER,// @emem (1)CFIFO mode is modified to continuous-scan edge or level trigger mode.
                                                //       (2)CFIFO mode is modified to single-scan edge or level trigger mode and QADC.FISR[n].F.SSS is asserted.
                                                //       (3)CFIFO mode is modified to single-scan software trigger mode and QADC.FISR[n].F.SSS is negated.
                                                //       (4)CFIFO is paused.
                                                //       (5)eQADC transferred the last entry of the queue in continuous-scan edge trigger mode.
   QADC_COMMAND_FIFO_STATUS_TRIGGERED           // @emem CFIFO is triggered.

}  QADC_Command_FIFO_Status_T;

//=============================================================================
// @enum QADC_Command_FIFO_Fill_Status_T |
//=============================================================================
typedef enum QADC_Command_FIFO_Fill_Status_Tag
{
   QADC_COMMAND_FIFO_FULL,      // @emem
   QADC_COMMAND_FIFO_NOT_FULL   // @emem

}  QADC_Command_FIFO_Fill_Status_T;

//=============================================================================
// @enum QADC_Result_FIFO_Fill_Status_T |
//=============================================================================
typedef enum QADC_Result_FIFO_Fill_Status_Tag
{
   QADC_RESULT_FIFO_EMPTY,      // @emem
   QADC_RESULT_FIFO_NOT_EMPTY   // @emem

}  QADC_Result_FIFO_Fill_Status_T;

//=============================================================================
// @enum QADC_Result_FIFO_Fill_Status_T |
//=============================================================================
typedef enum QADC_Destination_Select_Tag
{
   QADC_RESULT_DECIMATION_FILTER,            // @emem Result to only decimation filter by Alt. COnfig
   QADC_RESULT_BOTH_DECIMATION_FILTER_RFIFO  // @emem Result to both RFIFO and decimation filter by 
                                             //  Extended Alternate configuration register.
}  QADC_Destination_Select_T;



//=============================================================================
// QADC_Get_Interrupt_Type
//
// @func Get QADC Device Interrupt Type configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t QADC_Interrupt_Type_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================

typedef enum
{
   QADC_NONCOHERENCY_INTERRUPT,        //@emem Non coherency interrupt type
   QADC_TRIGGER_OVERRUN_INTERRUPT,     //@emem Trigger overrun interrupt type
   QADC_PAUSE_INTERRUPT,               //@emem Pause interrupt type
   QADC_END_OF_QUEUE_INTERRUPT,        //@emem End Of Queue interrupt type
   QADC_CFIFO_UNDERFLOW_INTERRUPT,     //@emem CFIFO underflow interrupt type
   QADC_CFIFO_FILL_ENABLE_INTERRUPT,   //@emem CFIFO Fill enable type
   QADC_RFIFO_OVERFLOW_INTERRUPT,      //@emem RFIFO overflow interrupt type
   QADC_RFIFO_DRAIN_ENABLE_INTERRUPT,  //@emem RFIFO drain enable 
                                       //interrupt/DMA type

   QADC_INTERRUPT_MAX

}  QADC_Interrupt_Type_T;

//=============================================================================
// 
// This register is also accessible by configuration commands sent to the ADC0 or ADC1 command buffer.Write/Read
//=============================================================================
typedef enum QADC_Register_Address_Tag
{
   QADC_REGISTER_ADDRESS_CONVERSION_COMMAND                          =0x00, //0x00 ADC0 Address 0x00 is used for conversion command messages.
   QADC_REGISTER_ADDRESS_CONTROL_REGISTER                            =0x01, //0x01 ADC0,1 Control Register (ADC0_CR,ADC1_CR) Write/Read
   QADC_REGISTER_ADDRESS_TIME_STAMP_CONTROL_REGISTER                 =0x02, //0x02 ADC Time Stamp Control Register (ADC_TSCR) 1 Write/Read
   QADC_REGISTER_ADDRESS_TIME_BASE_COUNTER_REGISTER                  =0x03, //0x03 ADC Time Base Counter Register (ADC_TBCR) 1 Write/Read
   QADC_REGISTER_ADDRESS_GAIN_CALIBRATION_CONSTANT_REGISTER          =0x04, //0x04 ADC0,1 Gain Calibration Constant Register (ADC0_GCCR,ADC1_GCCR) Write/Read
   QADC_REGISTER_ADDRESS_OFFSET_CALIBRATION_CONSTANT_REGISTER        =0x05, //0x05 ADC0,1 Offset Calibration Constant Register (ADC0_OCCR,ADC1_OCCR) Write/Read
   // Alternate Conversion Command to be added
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_1_CONTROL_REGISTER  =0x30, //0x30 ADC0,1 Alternate Configuration 1 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_ALTERNATE_GAIN_1_REGISTER                   =0x31,
   QADC_REGISTER_ADDRESS_ALTERNATE_OFFSET_1_REGISTER                 =0x32,
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_1_CONTROL_REGISTER      =0x33,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_2_CONTROL_REGISTER  =0x34, //0x34 ADC0,1 Alternate Configuration 2 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_ALTERNATE_GAIN_2_REGISTER                   =0x35,
   QADC_REGISTER_ADDRESS_ALTERNATE_OFFSET_2_REGISTER                 =0x36,
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_2_CONTROL_REGISTER      =0x37,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_3_CONTROL_REGISTER  =0x38, //0x38 ADC0,1 Alternate Configuration 3 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_3_CONTROL_REGISTER      =0x3B,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_4_CONTROL_REGISTER  =0x3C, //0x3C ADC0,1 Alternate Configuration 4 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_4_CONTROL_REGISTER      =0x3F,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_5_CONTROL_REGISTER  =0x40, //0x40 ADC0,1 Alternate Configuration 5 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_5_CONTROL_REGISTER      =0x43,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_6_CONTROL_REGISTER  =0x44, //0x44 ADC0,1 Alternate Configuration 6 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_6_CONTROL_REGISTER      =0x47,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_7_CONTROL_REGISTER  =0x48, //0x48 ADC0,1 Alternate Configuration 7 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_7_CONTROL_REGISTER      =0x4B,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_8_CONTROL_REGISTER  =0x4C, //0x4C ADC0,1 Alternate Configuration 8 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_8_CONTROL_REGISTER      =0x4F,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_9_CONTROL_REGISTER  =0x50, //0x4C ADC0,1 Alternate Configuration 8 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_9_CONTROL_REGISTER      =0x53,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_10_CONTROL_REGISTER =0x54, //0x4C ADC0,1 Alternate Configuration 8 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_10_CONTROL_REGISTER     =0x57,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_11_CONTROL_REGISTER =0x58, //0x4C ADC0,1 Alternate Configuration 8 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_11_CONTROL_REGISTER     =0x5B,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_12_CONTROL_REGISTER =0x5C, //0x4C ADC0,1 Alternate Configuration 8 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_12_CONTROL_REGISTER     =0x5F,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_13_CONTROL_REGISTER =0x60, //0x4C ADC0,1 Alternate Configuration 8 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_13_CONTROL_REGISTER     =0x63,
   QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_14_CONTROL_REGISTER =0x64, //0x4C ADC0,1 Alternate Configuration 8 Control Registers) Write/Read
   QADC_REGISTER_ADDRESS_EXTENDED_ALT_CONFIG_14_CONTROL_REGISTER     =0x67,

   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_1_REGISTER             =0x70, //0x30 ADC0,1 Pull Up/Down Control Register 1
   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_2_REGISTER             =0x71, //0x34 ADC0,1 Pull Up/Down Control Register 2
   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_3_REGISTER             =0x72, //0x38 ADC0,1 Pull Up/Down Control Register 3
   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_4_REGISTER             =0x73, //0x3C ADC0,1 Pull Up/Down Control Register 4
   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_5_REGISTER             =0x74, //0x40 ADC0,1 Pull Up/Down Control Register 5
   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_6_REGISTER             =0x75, //0x44 ADC0,1 Pull Up/Down Control Register 6
   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_7_REGISTER             =0x76, //0x48 ADC0,1 Pull Up/Down Control Register 7
   QADC_REGISTER_ADDRESS_PULL_UP_DOWN_CONTROL_8_REGISTER             =0x77  //0x4C ADC0,1 Pull Up/Down Control Register 8

}  QADC_Register_Address_T;

//=============================================================================
// @enum QADC_PULL_TYPE_T | 
//=============================================================================
typedef enum
{
   QADC_NO_PULL = 0,
   QADC_PULL_UP,
   QADC_PULL_DOWN,
   QADC_PULL_UP_DOWN,
   QADC_PULL_TYPE_MAX
}  QADC_PULL_TYPE_T;

//=============================================================================
// @enum QADC_PULL_VALUE_T | 
//=============================================================================
typedef enum
{
   QADC_PULL_RESV = 0,
   QADC_PULL_200K,
   QADC_PULL_100K,
   QADC_PULL_5K,
   QADC_PULL_STRENGTH_MAX
}  QADC_PULL_STRENGTH_T;

// @enum QADC_Sample_Cycles_T | Sample Cycles for the converter 
typedef enum QADC_Sample_Cycles_Tag
{
   QADC_SAMPLE_CYCLES_2,   // @emem 0b00 2 Cycles to sample
   QADC_SAMPLE_CYCLES_8,   // @emem 0b01 8 Cycles to sample
   QADC_SAMPLE_CYCLES_64,  // @emem 0b10 64 Cycles to sample
   QADC_SAMPLE_CYCLES_128  // @emem 0b11 128 Cycles to sample

}  QADC_Sample_Cycles_T;

//=============================================================================
// @emem QADC_Message_Tag_T |
// //These messages are treated as null messages. Therefore, they must obey the
//format for incoming null messages and return valid BUSY0/1 fields. Refer to
//Section , " Null Message Format for External Device Operation."
//=============================================================================
typedef enum QADC_Message_Tag
{
   QADC_MESSAGE_TAG_RESULT_FIFO_0,  //0b0000 Result is sent to RFIFO 0
   QADC_MESSAGE_TAG_RESULT_FIFO_1,  //0b0001 Result is sent to RFIFO 1
   QADC_MESSAGE_TAG_RESULT_FIFO_2,  //0b0010 Result is sent to RFIFO 2
   QADC_MESSAGE_TAG_RESULT_FIFO_3,  //0b0011 Result is sent to RFIFO 3
   QADC_MESSAGE_TAG_RESULT_FIFO_4,  //0b0100 Result is sent to RFIFO 4
   QADC_MESSAGE_TAG_RESULT_FIFO_5,  //0b0101 Result is sent to RFIFO 5
   QADC_MESSAGE_TAG_RESERVED_0,     //0b0110-0b0111 Reserved
   QADC_MESSAGE_TAG_RESERVED_1,     //0b0110-0b0111 Reserved
   QADC_MESSAGE_TAG_NULL,           //0b1000 Null message received
   QADC_MESSAGE_TAG_CUSTOM_0,       //0b1001 Reserved for customer use. (1)
   QADC_MESSAGE_TAG_CUSTOM_1,       //0b1010 Reserved for customer use. (1)
   QADC_MESSAGE_TAG_MAX             // use as max value as the rest are reserved : 0b1011-0b1111 Reserved

}  QADC_Message_Tag_T;

//=============================================================================
// @emem QADC_Read_Write_Flag_T |
// Flag for reading and writing.
//=============================================================================
typedef enum QADC_Read_Write_Flag_Tag
{
   QADC_READ_WRITE_FLAG_WRITE,   //0b0 WRITE
   QADC_READ_WRITE_FLAG_READ     //0b1 READ

}  QADC_Read_Write_Flag_T;



//=============================================================================
typedef enum
{
   ADC_ALTCFG_PREGAIN_X1,
   ADC_ALTCFG_PREGAIN_X2,
   ADC_ALTCFG_PREGAIN_X4,
   ADC_ALTCFG_RESERVED

}ADC_ALTCFG_PREGAIN_T;


//=============================================================================
typedef enum
{
   ADC_ALTCFG_ATBSEL_INTERNAL,
   ADC_ALTCFG_ATBSEL_SRV1,
   ADC_ALTCFG_ATBSEL_SRV2,
   ADC_ALTCFG_ATBSEL_RESERVED

}ADC_ALTCFG_ATBSEL_T;


typedef enum
{
   ADC_ALTCFG_RESSEL_12BIT,
   ADC_ALTCFG_RESSEL_10BIT,
   ADC_ALTCFG_RESSEL_8BIT,
   ADC_ALTCFG_RESSEL_RESERVED

}ADC_ALTCFG_RESSEL_T;


typedef enum
{
   ADC_ALTCFG_FMTA_RIGHT_JUSTIFIED_UNSIGNED,
   ADC_ALTCFG_FMTA_RIGHT_JUSTIFIED_SIGNED
   
}ADC_ALTCFG_Data_Format_T;


//=============================================================================
typedef enum ADC_ALTCFG_DEST_Tag
{
   ADC_ALTCFG_DEST_RFIFO,                              // 0000 The conversion result is sent to the RFIFOs.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCK_A,          // 0001 The conversion result is sent to Decimation Filter block A.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCK_B,          // 0010 The conversion result is sent to Decimation Filter block B.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCK_C,          // 0011 The conversion result is sent to Decimation Filter block C.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCK_D,          // 0100 The conversion result is sent to Decimation Filter block D.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCK_E,          // 0101 The conversion result is sent to Decimation Filter block E.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCK_F,          // 0110 The conversion result is sent to Decimation Filter block F.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCK_G,          // 0111 The conversion result is sent to Decimation Filter block G.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_A_AND_E,   // 1000 The conversion result is sent to Decimation Filter blocks A and E.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_B_AND_E,   // 1001 The conversion result is sent to Decimation Filter blocks B and E.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_C_AND_E,   // 1010 The conversion result is sent to Decimation Filter blocks C and E.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_D_AND_E,   // 1011 The conversion result is sent to Decimation Filter blocks D and E.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_A_AND_G,   // 1100 The conversion result is sent to Decimation Filter blocks A and G.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_B_AND_G,   // 1101 The conversion result is sent to Decimation Filter blocks B and G.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_C_AND_G,   // 1110 The conversion result is sent to Decimation Filter blocks C and G.
   ADC_ALTCFG_DEST_DECIMATION_FILTER_BLOCKS_D_AND_G    // 1111 The conversion result is sent to Decimation Filter blocks D and G.

} ADC_ALTCFG_DEST_T;


//=============================================================================
typedef enum QADC_ALTCFG_RETINH_Tag
{
   ADC_ALTCFG_RETINH_RESULT_TRANSFER_TO_RESULT_QUEUE     = 0,
   ADC_ALTCFG_RETINH_DECIMATION_FILTER_IN_FILTERING_MODE = 0,
   ADC_ALTCFG_RETINH_NO_RESULT_TRANSFER_TO_RESULT_QUEUE  = 1,
   ADC_ALTCFG_RETINH_DECIMATION_FILTER_PREFILL_MODE      = 1

}QADC_ALTCFG_RETINH_T;


//=============================================================================
typedef enum QADC_ALTCFG_RMSEL_Tag
{
   ADC_ALTCFG_DEC_FILTER_RETURN_DATA_TO_QADC_FILTER_DATA,
   ADC_ALTCFG_DEC_FILTER_RETURN_DATA_TO_QADC_NO_SUPPLY_FILTER_DATA

}QADC_ALTCFG_RMSEL_T;



#endif // DD_QADC_H

