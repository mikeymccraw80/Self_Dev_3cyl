#ifndef IO_CONFIG_MIOS_H
#define IO_CONFIG_MIOS_H

#include "dd_mios.h"
#include "io_config_fmpll.h"
#include "io_config_vsep.h"



#define MIOS_Global_Frequency  ( SYSTEM_FREQUENCY_HZ )

//=============================================================================
// eMIOS
//  Divide the system clock to get an 8 MHz eMIOS global clock.
//=============================================================================
#define EMIOS_FREQUENCY_HZ             ( 40000000 )
#define EMIOS_GLOBAL_PRESCALER        ( ( SYSTEM_FREQUENCY_HZ/EMIOS_FREQUENCY_HZ ) -1)


extern const MIOS_MCR_T MIOS_MCR_INITIAL;
extern const MIOS_CSR_T MIOS_RESET_CSR;


//OPWFMB
// VSEPCLK
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_0 - 
//=======================================================================================
extern const MIOS_CCR_T MIOS_CH0_INITIAL;
#define      VSEPCLK_Frequency                           VSEP_EXTERNAL_CLOCK_BASE_FREQUENCY   //2000HZ
#define      MIOS_CH0_PRESCALER                MIOS_PRESCALER_RATIO_1
#define      MIOS_CH0_CBDR_INITIAL           EMIOS_FREQUENCY_HZ/(VSEPCLK_Frequency* (MIOS_PRESCALER_RATIO_1+1))
#define      MIOS_VSEPCLK_CH              MIOS_CHANNEL_0 

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
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_5 -
//=======================================================================================

//=======================================================================================
// MIOS_CHANNEL_INIT_6 -
//=======================================================================================


//OPWFMB
//PWM_ETCCTLPWM 
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_8 - 
//=======================================================================================
extern const MIOS_CCR_T MIOS_CH8_INITIAL;
#define      ETC_Frequency                           2000   //2000HZ
#define      MIOS_CH8_PRESCALER              MIOS_PRESCALER_RATIO_1
#define      MIOS_CH8_CBDR_INITIAL         EMIOS_FREQUENCY_HZ/(ETC_Frequency* (MIOS_PRESCALER_RATIO_1+1))
#define      MIOS_ETCCTLPWM_CH              MIOS_CHANNEL_8  

//OPWFMB
//CLTPUMPCTL
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_9 - 
//=======================================================================================
extern const MIOS_CCR_T MIOS_CH9_INITIAL;
#define      CLTPUMPCTL_Frequency                           10   //100HZ
#define      MIOS_CH9_PRESCALER              MIOS_PRESCALER_RATIO_1
#define      MIOS_CH9_CBDR_INITIAL           EMIOS_FREQUENCY_HZ/(CLTPUMPCTL_Frequency* (MIOS_PRESCALER_RATIO_1+1))
#define      MIOS_CLTPUMPCTL_CH              MIOS_CHANNEL_9  


//OPWFMB
//CRUISICTL
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_10 - 
//=======================================================================================
extern const MIOS_CCR_T MIOS_CH10_INITIAL;
#define      CRUISICTL_Frequency                           10   //100HZ
#define      MIOS_CH10_PRESCALER              MIOS_PRESCALER_RATIO_1
#define      MIOS_CH10_CBDR_INITIAL           EMIOS_FREQUENCY_HZ/(CRUISICTL_Frequency* (MIOS_PRESCALER_RATIO_1+1))
#define      MIOS_CRUISICTL_CH              MIOS_CHANNEL_10  

//=======================================================================================
// MIOS_CHANNEL_INIT_11 - 
//=======================================================================================

//OPWFMB
//VVT2CTL
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_12 - 
//=======================================================================================
extern const MIOS_CCR_T MIOS_CH12_INITIAL;
#define     VVT2CTL_Frequency                           10   //100HZ
#define      MIOS_CH12_PRESCALER              MIOS_PRESCALER_RATIO_1
#define      MIOS_CH12_CBDR_INITIAL           EMIOS_FREQUENCY_HZ/(VVT2CTL_Frequency* (MIOS_PRESCALER_RATIO_1+1))
#define      MIOS_VVT2CTL_CH              MIOS_CHANNEL_12  
//=======================================================================================
// MIOS_CHANNEL_INIT_13 - 
//=======================================================================================

//OPWFMB
//VVT1CTL
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_14 - 
//=======================================================================================
extern const MIOS_CCR_T MIOS_CH14_INITIAL;
#define      VVT1CTL_Frequency                           10   //10000HZ
#define      MIOS_CH14_PRESCALER              MIOS_PRESCALER_RATIO_1
#define      MIOS_CH14_CBDR_INITIAL            EMIOS_FREQUENCY_HZ/(VVT1CTL_Frequency* (MIOS_PRESCALER_RATIO_1+1))
#define      MIOS_VVT1CTL_CH              MIOS_CHANNEL_14  

//OPWFMB
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_15 - 
//=======================================================================================
//extern const MIOS_CCR_T MIOS_CH15_INITIAL;
//#define      VVT2_Frequency                           100   //10000HZ
//#define      MIOS_CH15_CBDR_INITIAL           EMIOS_FREQUENCY_HZ/(VVT2_Frequency* (MIOS_PRESCALER_RATIO_1+1))
//#define      MIOS_VVT2_CH              MIOS_CHANNEL_15  


//OPWFMB
//FUELCONCTL
//MIOS_CHANNEL_BIG
//=======================================================================================
// MIOS_CHANNEL_INIT_23
//=======================================================================================

extern const MIOS_CCR_T MIOS_CH23_INITIAL;
#define      FUELCONCTL_Frequency                           10   //10000HZ
#define      MIOS_CH23_PRESCALER              MIOS_PRESCALER_RATIO_1
#define      MIOS_CH23_CBDR_INITIAL           EMIOS_FREQUENCY_HZ/(FUELCONCTL_Frequency* (MIOS_PRESCALER_RATIO_1+1))
#define      MIOS_FUELCONCTL_CH              MIOS_CHANNEL_23  


#define      Convert_HZ_to_Count(x)         (EMIOS_FREQUENCY_HZ/(x* (MIOS_PRESCALER_RATIO_1+1)))


#endif
