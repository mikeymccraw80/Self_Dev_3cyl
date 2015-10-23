#ifndef IO_CONFIG_KNOCK_H
#define IO_CONFIG_KNOCK_H


#define DEC_FILT_A_DMA_RESULT_BUFF_SIZE        (1200)
#define DEC_FILT_A_DMA_PREFILL_SIZE            (4)
#define DEC_FILT_A_DMA_LOWPASS_DECRATE         (4)


//!
#define MULTIKNOCK_NUM_FILTERS (3)
#define Knock_IIR_ADC_Sample_Time              (5) //5us
#define Knock_Time_Scale                       (4) //
#define Knock_Min_Wingate_Cnt                  (25) //
#define Knock_Stable_Time                      (1500) //us
#define Knock_Stable_Min_Time                  (400) //us
#define Knock_Max_Winggate_Time                (4500) //us

//#define CcSYST_NUM_OF_CYLINDERS 3




#endif // DD_KNOCK_CONFIG_H

