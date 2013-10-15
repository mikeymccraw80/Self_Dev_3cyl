

#include "io_config_mios.h"





const MIOS_MCR_T MIOS_MCR_INITIAL =
{

     MIOS_DOZEEN_DISABLE,     // :  BIT_1;   // Bit      31 // Module disable
     MIOS_MODULE_ENABLE,       // Module disable   :  BIT_1;   // Bit      30
     MIOS_DEBUG_FREEZE_DISABLE,   // Freeze enable  :  BIT_1;   // Bit      29
     MIOS_GLOBAL_TIME_BASE_ENABLE,   // Global time base enable   :  BIT_1;   // Bit      28
     MIOS_EXTERNAL_TIME_BASE_SELECT_STAC,   // External time base   ETB    :  BIT_1;   // Bit      27
     true,               //  GPREN  :  BIT_1;   // Bit      26
     MIOS_SERVER_TIME_SLOT_TPUA_TCR1,   // Server time slot  SRV    :  BIT_4;   // Bits [19:16]
     EMIOS_GLOBAL_PRESCALER                //   GPRE   :  BIT_8;   // Bits [15: 8]

};





const MIOS_CSR_T MIOS_RESET_CSR = 
{
   1, // OVR  
   1, // OVFL 
   0, // UCIN 
   0, // UCOUT
   1  // FLAG 
};




//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_0 - 
//=======================================================================================

const MIOS_CCR_T MIOS_CH0_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH0_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_SET_B_CLEAR, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED  // Mode selection
  };


//=======================================================================================
// MIOS_CHANNEL_INIT_1 
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_2
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_3 - 
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_4 - 
// SAIC Mode for ETC_SOH External 818HZ frequency input
// Channel bus from TRC1 4MHZ 0.25us each count
// DMA request SAIC
// Validate TCR1 of ETPU2 against 818HZ
//=======================================================================================
const MIOS_CCR_T MIOS_CH4_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // Normal opreation
      MIOS_OUTPUT_DISABLE, // Output disable MIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH4_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_DMA, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      true, // FLAG Enable bit FEN,DMA request
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // no effect
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, //no effect
      MIOS_CLOCK_BUS_BUS_A, // Bus select BSL ,validate TCR1 against TCR1 from ETPU2
      //0 The EDPOL value
      0, // Edge select EDSEL, input mode single edge
      MIOS_EDGE_POLARITY_INPUT_MODE_FALLING, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_SINGLE_ACTION_INPUT_CAPTURE// Mode selection SAIC
  };

//=======================================================================================
// MIOS_CHANNEL_INIT_5 -
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_6 -
//=======================================================================================


//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_8 - 
//=======================================================================================
const MIOS_CCR_T MIOS_CH8_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH8_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_SET_B_CLEAR, // Edge polarity
      MIOS_CHANNEL_MODE_OPWFM_BUFFERED_FLAG_B  // Mode selection
  };

//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_9 - 
//=======================================================================================
const MIOS_CCR_T MIOS_CH9_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH9_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED  // Mode selection
  };

//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_10 - 
//=======================================================================================
const MIOS_CCR_T MIOS_CH10_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH10_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED  // Mode selection
  };


//=======================================================================================
// MIOS_CHANNEL_INIT_11 - 
//=======================================================================================

//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_12 - 
//=======================================================================================
const MIOS_CCR_T MIOS_CH12_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH12_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED  // Mode selection
  };

//=======================================================================================
// MIOS_CHANNEL_INIT_13 - 
//=======================================================================================

//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_14 - 
//=======================================================================================
const MIOS_CCR_T MIOS_CH14_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH14_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED  // Mode selection
  };


//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_15 - 
//=======================================================================================

const MIOS_CCR_T MIOS_CH15_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_PRESCALER_RATIO_1, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED  // Mode selection
  };


//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_23
//=======================================================================================

const MIOS_CCR_T MIOS_CH23_INITIAL = 
{
      ///1 Freeze UC registers values
      ///0 Normal operation
      false,  // FREN  Freeze enable
      MIOS_OUTPUT_NORMAL, // Output disableMIOS
      MIOS_OUTPUT_LINE_0 ,// Output disable select ODISSL
      MIOS_CH23_PRESCALER, // Prescaler UCPRE
      ///1 Prescaler enabled
      ///0 Prescaler disabled (no clock)
      true, // Prescaler enable UCPREN
      MIOS_FLAG_SELECT_INTERRUPT, // Interrupt or DMA Flag
      MIOS_INPUT_FILTER_BYPASS, // Input filter
      MIOS_FILTER_CLOCK_SELECT_PRESCALED, // Filter clock select
      //The FEN bit allows the Unified Channel FLAG bit to generate an interrupt signal or a DMA request
     //signal (The type of signal to be generated is defined by the DMA bit).
     ////1 = Enable (FlAG will generate an interrupt or DMA request)
     ////0 = Disable (FLAG does not generate an interrupt or DMA request)
      false, // FLAG Enable bit FEN
      ///1 Force a match at comparator A
     ///0 Has no effect
      false, // Force match A FORCMA
      ///1 Force a match at comparator B
     ///0 Has no effect
      false, // Force match B FORCMB
      MIOS_CLOCK_BUS_INTERNAL_COUNTER, // Bus select BSL
      //0 The EDPOL value
      0, // Edge select EDSEL
      MIOS_EDGE_POLARITY_OUTPUT_MODE_MATCH_A_CLEAR_B_SET, // Edge polarity
      MIOS_CHANNEL_BASE_MODE_PULSE_WIDTH_FREQUENCY_MODULATION_BUFFERED  // Mode selection
  };





