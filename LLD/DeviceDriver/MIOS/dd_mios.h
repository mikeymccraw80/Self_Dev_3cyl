#ifndef DD_MIOS_H
#define DD_MIOS_H

#include "reuse.h"

#include "hw_mios.h"

#define SECTION_MIOS_REGISTER
#include "section.h"
extern MIOS_T MIOS;
#define SECTION_END
#include "section.h"


//=============================================================================
// @enum MIOS Channel Modes
//=============================================================================
typedef enum MIOS_Channel_Mode_TAG
{
   MIOS_CHANNEL_MODE_GPIO_IN                             = 0x00, // @emem 0000 0000 General purpose input/output mode (input)
   MIOS_CHANNEL_MODE_GPIO_OUT                            = 0x01, // @emem 0000 0001 General purpose input/output mode (output)
   MIOS_CHANNEL_MODE_SAIC                                = 0x02, // @emem 0000 0010 Single action input capture
   MIOS_CHANNEL_MODE_SAOC                                = 0x03, // @emem 0000 0011 Single action output compare
   MIOS_CHANNEL_MODE_IPWM                                = 0x04, // @emem 0000 0100 Input pulse width measurement
   MIOS_CHANNEL_MODE_IPM                                 = 0x05, // @emem 0000 0101 Input period measurement
   MIOS_CHANNEL_MODE_DAOC_FLAG_ON_MATCH_2                = 0x06, // @emem 0000 0110 Double action output compare (with FLAG set on the second match)
   MIOS_CHANNEL_MODE_DAOC_FLAG_ON_BOTH                   = 0x07, // @emem 0000 0111 Double action output compare (with FLAG set on both match) Table 17-10. EMIOS_CCRn Field Description (continued) Bits Name Description

   MIOS_CHANNEL_MODE_MC_UP_BUFFERED_INTERNAL_CLOCK                = 0x50, // @emem 0101 0000 Modulus up counter, buffered, internal clock
   MIOS_CHANNEL_MODE_MC_UP_BUFFERED_EXTERNAL_CLOCK                = 0x51, // @emem 0101 0001 Modulus up counter, buffered, external clock
   MIOS_CHANNEL_MODE_RESERVED_52                                  = 0x52, // @emem 0101 0010 Reserved
   MIOS_CHANNEL_MODE_RESERVED_53                                  = 0x53, // @emem 0101 0011 Reserved
   MIOS_CHANNEL_MODE_MC_UP_DOWN_BUFFERED_FLAG_ONE_INTERNAL_CLOCK  = 0x54, // @emem 0101 0100 Modulus up/down counter, buffered (FLAG set on one event, internal clock)
   MIOS_CHANNEL_MODE_MC_UP_DOWN_BUFFERED_FLAG_ONE_EXTERNAL_CLOCK  = 0x55, // @emem 0101 0101 Modulus up/down counter, buffered (FLAG set on one event, external clock)
   MIOS_CHANNEL_MODE_MC_UP_DOWN_BUFFERED_FLAG_BOTH_INTERNAL_CLOCK = 0x56, // @emem 0101 0110 Modulus up/down counter, buffered (FLAG set on both events, internal clock)
   MIOS_CHANNEL_MODE_MC_UP_DOWN_BUFFERED_FLAG_BOTH_EXTERNAL_CLOCK = 0x57, // @emem 0101 0111 Modulus up/down counter, buffered (FLAG set on both events, external clock)
   MIOS_CHANNEL_MODE_OPWFM_BUFFERED_FLAG_B                        = 0x58, // @emem 0101 1000 Output pulse width and frequency modulation, buffered (FLAG set at match of internal counter and comparator B)
   MIOS_CHANNEL_MODE_RESERVED_59                                  = 0x59, // @emem 0101 1001 Reserved
   MIOS_CHANNEL_MODE_OPWFM_BUFFERED_FLAG_A_OR_B                   = 0x5A, // @emem 0101 1010 Output pulse width and frequency modulation, buffered (FLAG set at match of internal counter and comparator A or comparator B)

   MIOS_CHANNEL_MODE_OPWM_BUFFERED_FLAG_MATCH_2                   = 0x60, // @emem 0110 0000 Output pulse width modulation, buffered (FLAG set on second match)   **To be used as an output compare**
   MIOS_CHANNEL_MODE_RESERVED_61                                  = 0x61, // @emem 0110 0001 Reserved
   MIOS_CHANNEL_MODE_OPWM_BUFFERED_FLAG_MATCH_BOTH                = 0x62 // @emem 0110 0010 Output pulse width modulation, buffered (FLAG set on both matches)   **To be used as an output compare**

}  MIOS_Channel_Mode_T;

//=============================================================================
// @enum Bus select. Used to select either one of the counter buses or the 
// internal counter to be used by the unified channel.
//=============================================================================
typedef enum
{
   MIOS_CHANNEL_0,            //@emem Channel  0
   MIOS_CHANNEL_1,            //@emem Channel  1
   MIOS_CHANNEL_2,            //@emem Channel  2
   MIOS_CHANNEL_3,            //@emem Channel  3
   MIOS_CHANNEL_4,            //@emem Channel  4
   MIOS_CHANNEL_5,            //@emem Channel  5
   MIOS_CHANNEL_6,            //@emem Channel  6
   MIOS_CHANNEL_7_RESERVED,   //@emem Channel  7
   MIOS_CHANNEL_8,            //@emem Channel  8
   MIOS_CHANNEL_9,            //@emem Channel  9
   MIOS_CHANNEL_10,           //@emem Channel 10
   MIOS_CHANNEL_11,           //@emem Channel 11
   MIOS_CHANNEL_12,           //@emem Channel 12
   MIOS_CHANNEL_13,           //@emem Channel 13
   MIOS_CHANNEL_14,           //@emem Channel 14
   MIOS_CHANNEL_15,           //@emem Channel 15
   MIOS_CHANNEL_16_RESERVED,  //@emem Channel 16
   MIOS_CHANNEL_17_RESERVED,  //@emem Channel 17
   MIOS_CHANNEL_18_RESERVED,  //@emem Channel 18
   MIOS_CHANNEL_19_RESERVED,  //@emem Channel 19
   MIOS_CHANNEL_20_RESERVED,  //@emem Channel 20
   MIOS_CHANNEL_21_RESERVED,  //@emem Channel 21
   MIOS_CHANNEL_22_RESERVED,  //@emem Channel 22
   MIOS_CHANNEL_23,           //@emem Channel 23
   MIOS_CHANNEL_MAX           //@emem Max Channel value for the MIOS

}  MIOS_Channel_T;


//=============================================================================
// @enum Bus select. Used to select either one of the counter buses or the 
// internal counter to be used by the unified channel.
//=============================================================================
typedef enum
{
   MIOS_CLOCK_BUS_BUS_A,            //@emem  All channels: counter bus[A]
   MIOS_CLOCK_BUS_BUS_B_C_D,        //@emem  Channels 0 to 7:   counter bus[B]
                                    //       Channels 8 to 15:  counter bus[C]
                                    //       Channels 16 to 23: counter bus[D]
   MIOS_CLOCK_BUS_RESERVED,         //@emem  Reserved
   MIOS_CLOCK_BUS_INTERNAL_COUNTER  //@emem  All channels: internal counter

}  MIOS_Clock_Bus_T;


//=============================================================================
// @enum Doze enable Used to enable entry into LOw power mode when MCU DOZE bit 
// is asserted.
//=============================================================================

typedef enum
{
   MIOS_DOZEEN_ENABLE,
   MIOS_DOZEEN_DISABLE

}MIOS_Dozeen_T;


//=============================================================================

typedef enum
{
   MIOS_CHANNEL_SMALL,
   MIOS_CHANNEL_MEDIUM,
   MIOS_CHANNEL_BIG,
   MIOS_CHANNEL_RESERVED
}MIOS_Channel_Type_T;



//=============================================================================
// @enum Module disable. Puts the eMIOS in low power mode. The MDIS bit is used 
// to stop the clock of the module, except the access to registers EMIOS_MCR 
// and EMIOS_OUDR.
//=============================================================================
typedef enum
{
   MIOS_MODULE_ENABLE,  //@emem Clock is running
   MIOS_MODULE_DISABLE  //@emem Enter low power mode

}  MIOS_Module_T;


//=============================================================================
// @enum Freeze. Enables the eMIOS to freeze the registers of the unified 
// channels when debug mode is requested at MCU level. Each unified channel 
// should have FREN bit set in order to enter freeze mode. While in freeze mode, 
// the eMIOS continues to operate to allow the MCU access to the unified channels 
// registers. The unified channel will remain frozen until the FRZ bit is written 
// to zero or the MCU exits debug mode or the unified channel FREN bit is cleared.
//=============================================================================
typedef enum
{
   MIOS_DEBUG_FREEZE_DISABLE, //@emem Freeze. Enables the eMIOS to freeze the 
                              // registers of the unified channels when debug
                              // mode is requested at MCU level. Each unified channel 
                              // should have FREN bit set in order to enter freeze 
                              // mode. While in freeze mode, the eMIOS continues 
                              // to operate to allow the MCU access to the unified 
                              // channels registers. The unified channel will remain 
                              // frozen until the FRZ bit is written to zero or 
                              // the MCU exits debug mode or the unified channel FREN
                              // bit is cleared.

   MIOS_DEBUG_FREEZE_ENABLE   //@emem Stops unified channels operation when in debug 
                              // mode and the EMIOS_CCRn[FREN] bit is set
}  MIOS_Debug_Freeze_T;


// TBD: Does this item need to be configurable.
// This attribute provides a method to sync all the counters
//=============================================================================
// @enum Global time base enable. Used to export a global time base enable from
// the module and provide a method to start time bases of several modules 
// simultaneously.
//
// Note: The global time base enable input signal controls the internal counters. 
// When asserted, internal counters are enabled. When negated, internal counters 
// disabled.
//=============================================================================
typedef enum
{
   MIOS_GLOBAL_TIME_BASE_DISABLE,   //@emem Global time base enable out signal negated
   MIOS_GLOBAL_TIME_BASE_ENABLE     //@emem Global time base enable out signal asserted

}  MIOS_Global_Time_Base_T;


//=============================================================================
// @enum External time base. Selects the time base source that drives counter 
// bus[A].
//
// Note: 
// If ETB is set to select STAC as the counter bus[A] source, the GTBE 
// must be set to enable the STAC to counter bus[A]. See Section 17.4.2, 
// "STAC Client Submodule" and the shared time and angle clock (STAC) bus 
// interface section and the STAC bus configuration register (ETPU_REDCR) 
// section of the eTPU chapter for more information about the STAC.
//=============================================================================
typedef enum
{
   MIOS_EXTERNAL_TIME_BASE_SELECT_UC23,   //@emem Unified channel 23 drives counter bus[A]
   MIOS_EXTERNAL_TIME_BASE_SELECT_STAC    //@emem STAC drives counter bus[A]

}  MIOS_External_Time_Base_Select_T;


//=============================================================================
// @enum Server time slot. Selects the address of a specific STAC server to 
// which the STAC client submodule is assigned (refer to Section 17.4.2, "STAC 
// Client Submodule," for details)
//=============================================================================
typedef enum
{
   MIOS_SERVER_TIME_SLOT_TPUA_TCR1, //@emem eTPU engine A, TCR1
   MIOS_SERVER_TIME_SLOT_TPUB_TCR1, //@emem eTPU engine B, TCR1
   MIOS_SERVER_TIME_SLOT_TPUA_TCR2, //@emem eTPU engine A, TCR2
   MIOS_SERVER_TIME_SLOT_TPUB_TCR2  //@emem eTPU engine B, TCR2

}  MIOS_Server_Time_Slot_T;



//=============================================================================
// @enum MIOS Channel Base Modes
//=============================================================================
typedef enum
{
   MIOS_CHANNEL_BASE_MODE_GPIO                                   = 0x00,   // @emem 0b000000 General purpose input/output mode
   MIOS_CHANNEL_BASE_MODE_SINGLE_ACTION_INPUT_CAPTURE            = 0x02,   // @emem 0b000010 Single action input capture
   MIOS_CHANNEL_BASE_MODE_SINGLE_ACTION_OUTPUT_COMPARE           = 0x03,   // @emem 0b000011 Single action output compare
   MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_MEASUREMENT                = 0x04,   // @emem 0b000100 Input pulse width measurement
   MIOS_CHANNEL_BASE_MODE_PERIOD_MEASUREMENT                     = 0x05,   // @emem 0b000101 Input period measurement
   MIOS_CHANNEL_BASE_MODE_DUAL_ACTION_OUTPUT_COMPARE             = 0x06,   // @emem 0b000110 Double action output compare 
   MIOS_CHANNEL_BASE_MODE_FREQUENCY_INPUT                        = 0x08,   // @emem 0b001000 Pulse/edge accumulation or Pulse/edge counting
   MIOS_CHANNEL_BASE_MODE_QUADRATURE_DECODE                      = 0x0C,   // @emem 0b001100 Quadrature decode **No Support**
   MIOS_CHANNEL_BASE_MODE_MODULUS_COUNTER_UP                     = 0x10,   // @emem 0b010000 Modulus counter
   MIOS_CHANNEL_BASE_MODE_MODULUS_COUNTER_UP_AND_DOWN            = 0x14,   // @emem 0b010100 Modulus counter
   MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION       = 0x18,   // @emem 0b011000 Output pulse width and frequency modulation
   MIOS_CHANNEL_BASE_MODE_CENTER_ALIGNED_PULSE_WIDTH_MODULATION  = 0x1C,   // @emem 0b011100 Center aligned output pulse width modulation
   MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_MODULATION                 = 0x20,    // @emem 0b100000 Output pulse width modulation **To be used as an output compare**
   MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED     = 0x58    // @emem 0b100000 Output pulse width modulation **To be used as an output compare**

}  MIOS_Channel_Base_Mode_T;



//=============================================================================
// @enum MIOS primitive mode conditions
//=============================================================================
typedef enum
{
   //=============================================================================
   // GPIO modes for GPI/GPO modes
   //=============================================================================
   MIOS_MODE_CONDITION_INPUT                 = 0,
   MIOS_MODE_CONDITION_OUTPUT                = 1,

   //=============================================================================
   // Pulse/Edge modes for PEA/PEC modes
   //=============================================================================
   MIOS_MODE_CONDITION_CONTINUOUS            = 0,
   MIOS_MODE_CONDITION_SINGLE_SHOT           = 1,

   //=============================================================================
   // Clock source selections for MC modes
   //=============================================================================
   MIOS_MODE_CONDITION_CLOCK_SOURCE_INTERNAL = 0,
   MIOS_MODE_CONDITION_CLOCK_SOURCE_EXTERNAL = 1,
   
   //=============================================================================
   // Pin action modes for OPWM modes
   //=============================================================================
   MIOS_MODE_CONDITION_UPDATE_IMMEDIATE      = 0,
   MIOS_MODE_CONDITION_UPDATE_NEXT_PERIOD    = 1,

   //=============================================================================
   // Dead Time settings for the OPWMC modes
   //=============================================================================
   MIOS_MODE_CONDITION_DEAD_TIME_TRAILING    = 0,
   MIOS_MODE_CONDITION_DEAD_TIME_LEADING     = 1,

   //=============================================================================
   // Direction counting modes for MC_UPDN modes
   //=============================================================================
   MIOS_MODE_CONDITION_DIRECTION_NO_CHANGE   = 0,
   MIOS_MODE_CONDITION_DIRECTION_CHANGE      = 1

}  MIOS_Mode_Condition_T;


//=============================================================================
// @enum FLAG modes for OPWM/OPWFM/OPWMC/MC_UP/MC_UPDN primitives
//=============================================================================
typedef enum
{
   //DAOC/OPWM/OPWFM
   MIOS_MODE_FLAG_SECOND_MATCH    = 0,
   MIOS_MODE_FLAG_BOTH_MATCH      = 1,

   //CAOPWM
   MIOS_MODE_FLAG_TRAILING_EDGE   = 0,
   MIOS_MODE_FLAG_BOTH_EDGE       = 1,

   //MC_UPDN
   MIOS_MODE_FLAG_ONE_EVENT       = 0,
   MIOS_MODE_FLAG_BOTH_EVENT      = 1

}  MIOS_Channel_Mode_Flag_T;

//=============================================================================
// @enum Buffered selection for OPWM/OPWFM/OPWMC/MC_UP/MC_UPDN primitives
//=============================================================================
typedef enum
{
   MIOS_MODE_BUFFERED_DISABLE,
   MIOS_MODE_BUFFERED_ENABLE

}  MIOS_Mode_Buffered_T;


//=============================================================================
//@enum Edge polarity. For input modes (except QDEC and WPTA mode), the EDPOL 
// bit asserts which edge triggers either the internal counter or an input 
// capture or a FLAG. 
// When not shown in the mode of operation description, this bit has no affect.
// 0 Trigger on a falling edge
// 1 Trigger on a rising edge
//
// For WPTA mode, the internal counter is used as a time accumulator and counts 
// up when the input gating signal has the same polarity of EDPOL bit.
// 0 Counting occurs when the input gating signal is low
// 1 Counting occurs when the input gating signal is high
//
// For QDEC (MODE[6] cleared), the EDPOL bit selects the count direction 
// according to direction signal (UCn input).
// 0 Counts down when UCn is asserted
// 1 Counts up when UCn is asserted
//
// NOTE: UC[n-1] EDPOL bit selects which edge clocks the internal counter of UCn
// 0 Trigger on a falling edge
// 1 Trigger on a rising edge
//
// For QDEC (MODE[6] set), the EDPOL bit selects the count direction according 
// to the phase difference.
// 0 Internal counter decrements if phase_A is ahead phase_B signal
// 1 Internal counter increments if phase_A is ahead phase_B signal
//
// NOTE: In order to operate properly, EDPOL bit must contain the same value in 
// UCn and UC[n-1]
//
// For output modes, the EDPOL bit is used to select the logic level on the output 
// pin.
// 0 A match on comparator A clears the output flip-flop, while a match on 
//    comparator B sets it
// 1 A match on comparator A sets the output flip-flop, while a match on 
//    comparator B clears it
//=============================================================================
typedef enum
{
   MIOS_EDGE_POLARITY_INPUT_MODE_FALLING                 = 0,
   MIOS_EDGE_POLARITY_INPUT_MODE_RISING                  = 1,

   MIOS_EDGE_POLARITY_WPTA_MODE_COUNT_GATED_LOW          = 0,
   MIOS_EDGE_POLARITY_WPTA_MODE_COUNT_GATED_HIGH         = 1,

   MIOS_EDGE_POLARITY_QDEC_MODE_CLEARED_COUNT_DOWN       = 0,
   MIOS_EDGE_POLARITY_QDEC_MODE_CLEARED_COUNT_UP         = 1,

   MIOS_EDGE_POLARITY_QDEC_MODE_SET_DECREMENT_A_AHEAD_B  = 0,
   MIOS_EDGE_POLARITY_QDEC_MODE_SET_INCREMENT_A_AHEAD_B  = 1,

   MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET    = 0,
   MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_SET_B_CLEAR    = 1

}  MIOS_Edge_Polarity_T;


//=============================================================================
// @enum Edge selection bit. For input modes, the EDSEL bit selects whether the 
// internal counter is triggered by both edges of a pulse or just by a single 
// edge as defined by the EDPOL bit. When not shown in the mode of operation 
// description, this bit has no effect.
//
// 0 Single edge triggering defined by the EDPOL bit
// 1 Both edges triggering
//
// For GPIO input mode, the EDSEL bit selects if a FLAG can be generated.
// 0 A FLAG is generated as defined by the EDPOL bit
// 1 No FLAG is generated
//
// For SAOC mode, the EDSEL bit selects the behavior of the output flip-flop at 
// each match.
// 0 The EDPOL value is transferred to the output flip-flop
// 1 The output flip-flop is toggled

//=============================================================================
typedef enum
{
   MIOS_EDGE_SELECTION_SINGLE                         = 0,
   MIOS_EDGE_SELECTION_BOTH                           = 1,

   MIOS_EDGE_SELECTION_GPIO_MODE_FLAG_GENERATED       = 0,
   MIOS_EDGE_SELECTION_GPIO_MODE_FLAG_NOT_GENERATED   = 1,

   MIOS_EDGE_SELECTION_SAOC_MODE_EDPOL_TRANSFERED     = 0,
   MIOS_EDGE_SELECTION_SAOC_MODE_FLIP_FLOP_TOGGLED    = 1

}  MIOS_Edge_Selection_T;


//=============================================================================
// @enum Filter clock select. Selects the clock source for the programmable 
// input filter.
//=============================================================================
typedef enum
{
   MIOS_FILTER_CLOCK_SELECT_PRESCALED, //@emem Prescaled clock
   MIOS_FILTER_CLOCK_SELECT_MAIN       //@emem Main clock
}  MIOS_Filter_Clock_Select_T;


//=============================================================================
// @enum Input filter. Controls the programmable input filter, selecting the 
// minimum input pulse width that can pass through the filter, as shown below. 
// For output modes, these bits have no meaning.
//=============================================================================
typedef enum
{
   MIOS_INPUT_FILTER_BYPASS          = 0,  // @emem Bypassed - The input signal is synchronized before arriving at the digital filter.
   MIOS_INPUT_FILTER_2_CLOCK_PERIOD  = 1,  // @emem  2 filter clock periods
   MIOS_INPUT_FILTER_4_CLOCK_PERIOD  = 2,  // @emem  4 filter clock periods
   MIOS_INPUT_FILTER_8_CLOCK_PERIOD  = 4,  // @emem  8 filter clock periods
   MIOS_INPUT_FILTER_16_CLOCK_PERIOD = 8   // @emem 16 filter clock periods

}  MIOS_Input_Filter_T;


//=============================================================================
// @enum Flag select. Used to select either one of the flags: Interrupt or DMA
// Note: DMA is not available for all channels - see uP specific doc for details
//=============================================================================
typedef enum
{
   MIOS_FLAG_SELECT_INTERRUPT,   // @emem 
   MIOS_FLAG_SELECT_DMA          // @emem 

}  MIOS_Flag_Select_T;


//=============================================================================
// @enum Prescaler. Selects the clock divider value for the unified channel 
// internal prescaler
//=============================================================================
typedef enum
{
   MIOS_PRESCALER_RATIO_1,
   MIOS_PRESCALER_RATIO_2,
   MIOS_PRESCALER_RATIO_3,
   MIOS_PRESCALER_RATIO_4

}  MIOS_Prescaler_Ratio_T;


//=============================================================================
// @enum Output disable select. Selects one of the four output disable input signals.
//=============================================================================
typedef enum
{
   MIOS_OUTPUT_LINE_0,  //@emem output disable input 0
   MIOS_OUTPUT_LINE_1,  //@emem output disable input 1
   MIOS_OUTPUT_LINE_2,  //@emem output disable input 2
   MIOS_OUTPUT_LINE_3   //@emem output disable input 3

}  MIOS_Output_Line_T;


//=============================================================================
// @enum Output disable. Allows output disable in any output mode except GPIO.
//=============================================================================
typedef enum
{
   MIOS_OUTPUT_NORMAL,  // @emem The output pin operates normally
   MIOS_OUTPUT_DISABLE  // @emem If the selected output disable input signal is 
                        // asserted, the output pin goes to the complement of 
                        // EDPOL for OPWFM, OPWFMB, and OPWMB modes, but the 
                        // unified  channel continues to operate normally; that 
                        // is, it continues to produce FLAG and matches. When 
                        // the selected output disable input signal is negated, 
                        // the output pin operates normally.
}  MIOS_Output_T;


//=============================================================================
// /------------------------------------------------------------------------
// | External Constants
// | If static initialization is not used, these values must be defined
// \------------------------------------------------------------------------
//=============================================================================

//=============================================================================
// MIOS_Get_Channel_Type
// returns the group of the channel
//=============================================================================

INLINE MIOS_Channel_Type_T MIOS_Get_Channel_Type(MIOS_Channel_T channel)
{
   MIOS_Channel_Type_T channel_type;

   if( (channel ==MIOS_CHANNEL_1) || (channel ==MIOS_CHANNEL_3) || (channel ==MIOS_CHANNEL_5) ||
       (channel ==MIOS_CHANNEL_6) )
   {
      channel_type = MIOS_CHANNEL_SMALL;
   }
   else if( (channel ==MIOS_CHANNEL_2) || (channel ==MIOS_CHANNEL_4) || (channel ==MIOS_CHANNEL_11) ||
            (channel ==MIOS_CHANNEL_13) )
   {
      channel_type = MIOS_CHANNEL_MEDIUM;
   }
   else if( (channel ==MIOS_CHANNEL_0) || (channel ==MIOS_CHANNEL_8) || (channel ==MIOS_CHANNEL_9) ||
            (channel ==MIOS_CHANNEL_10) || (channel ==MIOS_CHANNEL_12) || (channel ==MIOS_CHANNEL_14) ||
            (channel ==MIOS_CHANNEL_15) || (channel ==MIOS_CHANNEL_23) )
   {
      channel_type = MIOS_CHANNEL_BIG;
   }
   else
   {
      channel_type = MIOS_CHANNEL_RESERVED;
   }

   return (channel_type);
}


//=============================================================================
// @globalv MIOS_T | MIOS |
// The Register Memory Overlay of the Enhanced Modular Input/Output Subsystem
// to provide software access and debug information.
//
// @end
//=============================================================================



#endif // DD_MIOS_H

