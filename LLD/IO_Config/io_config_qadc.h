#ifndef IO_CONFIG_QADC_H
#define IO_CONFIG_QADC_H

#include "dd_qadc.h"
#include "io_config_fmpll.h"
 
//=============================================================================
// eQADC Scaling
//=============================================================================
#define EQADC_CLOCK_FREQUENCY_HZ ( 10000000UL )

//=============================================================================
// ADC configurations
//=============================================================================
//
// ADC Control Registers ADC0_CR
//
//  Bit      15  - ADC0.F.EN     - 0 disabled, 1 enabled
//  Bit      11  - ADC0.F.EMUX   - 0 external mux disabled, 1 emux enabled
//  Bits [ 4: 0] - ADC0.F.CLK_PS - Sys clock prescale: divide by 32 : should come from io_scale.h
//

#define ADCx_CLK_PS  ((uint8_t)(SYSTEM_FREQUENCY_HZ/EQADC_CLOCK_FREQUENCY_HZ/2.0))
#define QADC_ADC_0_CR_INIT_VALUE  ((uint16_t) (0x8000 | (ADCx_CLK_PS & 0x1F)))

//
// ADC Control Registers ADC1_CR
//
//  Bit      15  - ADC1.F.EN     - 0 disabled, 1 enabled
//  Bit      11  - ADC1.F.EMUX   - 0 external mux disabled, 1 emux enabled
//  Bits [ 4: 0] - ADC1.F.CLK_PS - Sys clock prescale: divide by 32 : should come from io_scale.h
//
#define QADC_ADC_1_CR_INIT_VALUE  ((uint16_t) (0x8000 | (ADCx_CLK_PS & 0x1F)))


//=============================================================================
// Analog_Channel_T | Defines an enumeration that contains all the analog
//=============================================================================
typedef enum
{
  //AD_ESC1HI_Channel,
  //AD_ESC1LO_Channel,
  AD_MAPVI_Channel,
  AD_ACPREVI_Channel,
  AD_LEGRFBVI_Channel,
  AD_TPS1VI_Channel,
  AD_TPS2VI_Channel,
  AD_PPS1VI_Channel,
  AD_PPS2VI_Channel,
  AD_FLVVI_Channel,
  AD_SPA1VI_Channel,
  AD_O2AVI_Channel,
  AD_O2BVI_Channel,
  AD_CRSVI_Channel,
  AD_CLTVI_Channel,
  AD_MATVI_Channel,
  AD_BSTATVI_Channel,  
  AD_FREPVI_Channel,
  AD_BKVAVII_Channel,
  AD_RREPVI_Channel,
  AD_BSTPREVI_Channel,
  AD_RRVI_Channel,
  AD_PSREF1_Channel,
  AD_PSREF2_Channel,
  AD_IGNVI_Channel,
  AD_58XRAWIN_Channel,
  AD_PBATTVI_Channel,
  //AD_Reserved_1_Channel,
  //AD_Reserved_2_Channel,
  //AD_Reserved_3_Channel,
  AD_HWCFGVI_Channel,
  AD_VCC2_Channel,
  AD_CPUTemp_Channel,
  AD_ANALOG_MAX_SIGNAL_NAMES

} AD_Analog_T;

//The eQADC Module Configuration Register (EQADC_MCR) contains bits used to control how the
//eQADC responds to a debug mode entry request, and to enable the eQADC SSI interface.
extern const QADC_MCR_T QADC_INITIAL_MCR;

//The eQADC STAC Client Configuration Register (EQADC_REDLCCR) contains bits used to control
//which time slots the eQADC selects to obtain predefined external time bases.
extern const QADC_REDLCCR_T QADC_INITIAL_REDLCCR;


//
// CFIFO Control Registers (QADC_CFCRn)
//
extern const QADC_CFCR_T  QADC_CFCR_RESET;

//
// FIFO and Interrupt Status Registers (QADC_FISRn)
//
//   !!NOTE!!
//   these are status registers that require a write of '1' to clear values
//

extern const QADC_FISR_T  QADC_FISR_RESET;

extern const QADC_SSICR_T  QADC_INITIAL_SSICR;
//The eQADC External Trigger Digital Filter Register (EQADC_ETDFR) is used to set the minimum time
//a signal must be held in a logic state on the CFIFO triggers inputs to be recognized as an edge or level
//gated trigger. The Digital Filter Length field specifies the minimum number of system clocks that must be
//counted by the digital filter counter to recognize a logic state change. However, there is a control signal
//that can be used to bypass the digital filter when this is not needed.
extern const QADC_ETDFR_T QADC_INITIAL_ETDFR;

extern const ADC_ACR_T  QADC_INITIAL_ACR1;

extern const ADC_CCMF_T  QADC_CMD_Timebase[AD_ANALOG_MAX_SIGNAL_NAMES];


extern const ADC_CCMF_T  QADC_CALIBRATION_ADC1_REF75[ADC_CONVERTER_MAX];
extern const ADC_CCMF_T  QADC_CALIBRATION_ADC1_REF25[ADC_CONVERTER_MAX]; 

extern const ADC_CCMF_T  QADC_KNOCK_ADC0;


#endif // IO_CONFIG_MMU_H

