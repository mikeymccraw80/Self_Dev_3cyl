
#include "io_config_dfilter.h"

const DECFILT_MCR_T  DECFILT_MCR_LOWPASS =
{

      DEC_FILTER_DEVICE_ENABLE,             //Filter Enable/ Disable
      0,                                                                         //Freeze Mode Disabled
      0,                                                                         // FRZ
      0,                                                                         //SRES:No action
      DEC_FILTER_DEVICE_NO_CASCADE,              //Cascade Mode
      0,                                                                         //Input data Interrupt Enable/Disable
      0,                                                                         //Output data Interrupt Enable/Disable
      DEC_FILTER_ERR_INT_DISABLE,           //Error Interrupt Enable/Disable
      DEC_FILTER_4_ORDER_IIR,               //Filter Type
      DEC_FILTER_SCALING_FACTOR_4,     //Scaling Factor
      DEC_FILTER_SATURATION_DISABLE,  //Saturation Enable/Disable
      DEC_FILTER_Input_Device_Slavebus,          //Input Select
      0,                                                                                                                              //MIXM
      DEC_FILTER_DECIMATION_RATE_4,          //Deciamtion Rate
      DEC_FILTER_DMA_ENABLED,        //DMA Enable Request
      DEC_FILTER_IP_BUFFER_INT_DISABLE,    //Input Buffer Interrupt Request Enable
      DEC_FILTER_OUT_BUFFER_INT_DISABLE,   //output Buffer Interrupt Request Enable
      0,                                                                         //Enhanced Debug Monitor Enable
      DEC_FILTER_TRNSFR_RES_TPU_TRIG_DISABLE,     // Triggered Output Result Enable—
      DEC_FILTER_TRNSFR_RES_TPU_RISING_EDGE //Selects the way the eTPU signal controls the transfer

};

const DECFILT_MCR_T  DECFILT_MCR_BANDPASS =
{

      DEC_FILTER_DEVICE_ENABLE,             //Filter Enable/ Disable
      0,                                                                         //Freeze Mode Disabled
      0,                                                                         // FRZ
      0,                                                                         //SRES:No action
      DEC_FILTER_DEVICE_NO_CASCADE,              //Cascade Mode
      0,                                                                         //Input data Interrupt Enable/Disable
      0,                                                                         //Output data Interrupt Enable/Disable
      DEC_FILTER_ERR_INT_DISABLE,           //Error Interrupt Enable/Disable
      DEC_FILTER_4_ORDER_IIR,               //Filter Type
      DEC_FILTER_SCALING_FACTOR_4,     //Scaling Factor
      DEC_FILTER_SATURATION_DISABLE,  //Saturation Enable/Disable
      DEC_FILTER_Input_Device_Slavebus,          //IO Select
      0,                                                                                                                               //MIXM
      DEC_FILTER_NO_DECIMATION,          //Deciamtion Rate
      DEC_FILTER_DMA_ENABLED,        //DMA Enable Request
      DEC_FILTER_IP_BUFFER_INT_DISABLE,    //Input Buffer Interrupt Request Enable
      DEC_FILTER_OUT_BUFFER_INT_DISABLE,   //output Buffer Interrupt Request Enable
      0,                                                                         //Enhanced Debug Monitor Enable
      DEC_FILTER_TRNSFR_RES_TPU_TRIG_DISABLE,     // Triggered Output Result Enable—
      DEC_FILTER_TRNSFR_RES_TPU_RISING_EDGE //Selects the way the eTPU signal controls the transfer
};
