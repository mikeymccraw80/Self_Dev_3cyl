
#ifndef IO_CONFIG_FMPLL_H
#define IO_CONFIG_FMPLL_H

#include "dd_fmpll.h"
// fOSC
#define CRYSTAL_FREQUENCY_HZ     ( 8000000 )

// 7-bit field controls the value of the divider in the FMPLL
//feedback loop.
// values 32 to 96  others are invalid
#define FMPLL_EMFD_VALUE       ( 80 )

// 4-bit field controls the value of the divider on the input clock
// Values 0-15 are valid 16 is invalid

//A zero value leads to divide by zero error
#define FMPLL_EPREDIV_VALUE    ( 1 )

// This 2-bit field controls a divider at the output of the FMPLL
//  00 Divide by 2;01 Divide by 4;10 Divide by 8;11 Divide by 16
#define FMPLL_ERFD_VALUE       ( 1 )

// fREF
#define EXTERNAL_FREQUENCY_HZ     ( 8000000 )

#define FMPLL_MODE_BYPASS              (  0 ) // 1 = PLL bypass mode selected
#define FMPLL_MODE_CRYSTAL             (  1 ) // 1 = Crystal Reference
#define FMPLL_MODE_EXTERNAL            (  0 ) // 1 = External Reference

#if FMPLL_MODE_CRYSTAL == 1
#define FMPLL_CLKCFG_VALUE (FMPLL_MODE_NORMAL_CRYSTAL_REF_PLL_ON)
#elif FMPLL_MODE_EXTERNAL == 1
#define FMPLL_CLKCFG_VALUE (FMPLL_MODE_NORMAL_EXTERNAL_REF_PLL_ON)
#else
#define FMPLL_CLKCFG_VALUE (FMPLL_MODE_BYPASS_EXTERNAL_REF_PLL_OFF)
#endif

#if FMPLL_MODE_CRYSTAL == 1
#define REFERENCE_FREQUENCY_HZ CRYSTAL_FREQUENCY_HZ
#else
#define REFERENCE_FREQUENCY_HZ EXTERNAL_FREQUENCY_HZ
#endif

// In enhanced mode, the relationship between input and output frequency is determined by:

//                                                          (          EMFD         )
//                               fSYS = fREF * ( ------------------------ )
//                                                 ( [ (EPREDIV + 1) * 2^(ERFD+1) ] )

#define FMPLL_FREQUENCY_HZ_CRYSTAL_OR_EXT_REF_MODE   ( ( ( REFERENCE_FREQUENCY_HZ ) * ( FMPLL_EMFD_VALUE  ) ) / ( ( FMPLL_EPREDIV_VALUE + 1 ) *(2<<( FMPLL_ERFD_VALUE ) )) )

#define SIU_BYPASS_SYS_CLOCK_DIVIDER_INIT (1) /* 1: bypassed */
//System Clock Divide
//System Clock Divide. The SYSCLKDIV bits select the divider value for the
//system clock (ipg_clk). Note that the SYSCLKDIV divider is required in
//addition to the RFD to allow the other sources for the system clock (16MHz
//IRC and OSC) to be divided down to slowest frequencies to improve power.
//The output of the clock divider is nominally a 50% duty cycle.
//00 = Divide by 2
//01 = Divide by 4
//10 = Divide by 8
//11 = Divide by 16
#define SIU_SYSTEM_CLOCK_DIV_INIT  (0) 

#define SYSTEM_FREQUENCY_HZ     (SIU_BYPASS_SYS_CLOCK_DIVIDER_INIT ?\
                                        (FMPLL_FREQUENCY_HZ_CRYSTAL_OR_EXT_REF_MODE) :\
                                        (FMPLL_FREQUENCY_HZ_CRYSTAL_OR_EXT_REF_MODE/(2<<SIU_SYSTEM_CLOCK_DIV_INIT)) )

#define CPU_FREQUENCY_HZ  ( SYSTEM_FREQUENCY_HZ )

#define CYCLE_TIME_SEC           ( 1.0 / (SYSTEM_FREQUENCY_HZ) )

#define SYSTEM_FREQUENCY_MHZ     ( (SYSTEM_FREQUENCY_HZ) / 1000000.0 )

#define CYCLE_TIME_US            ( 1000000.0 / (SYSTEM_FREQUENCY_HZ) )

#define ConvertusToCycles(x)     ( (x) * (SYSTEM_FREQUENCY_HZ) )

#define SYSTEM_CLK_OUT           SYSTEM_FREQUENCY_HZ




//PLL Modulation VAlues
#define FMPLL_MODULATION_FREQUENCY_HZ  (24000)

#define FMPLL_MODULATION_DEPTH   (2)

//modperiod = round(fref/4 × fmod)
//where fref=(input_frequency/PreDivider value)
#define FMPLL_MODULATION_PERIOD  (uint16_t)((REFERENCE_FREQUENCY_HZ)/(4*FMPLL_MODULATION_FREQUENCY_HZ*FMPLL_EPREDIV_VALUE))


//the effective modulation depth applied to the FMPLL is given
//by the following formula:
//                                ((2^15 – 1) * MD * EMFD)
//               incstep = round -------------------------
//                                  (100 * 5 * modperiod)
#define FMPLL_INCR_STEP_CONST_1  (32767)

#define FMPLL_INCR_STEP_CONST_2  (500)

#define FMPLL_INCREMENT_STEP  (uint16_t)((FMPLL_INCR_STEP_CONST_1*FMPLL_MODULATION_DEPTH*FMPLL_EMFD_VALUE)/(FMPLL_INCR_STEP_CONST_2*FMPLL_MODULATION_PERIOD))

#endif //IO_CONFIG_FMPLL_H