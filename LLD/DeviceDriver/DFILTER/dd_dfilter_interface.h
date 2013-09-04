
#ifndef DD_DFILTER_INTERFACE_H
#define DD_DFILTER_INTERFACE_H

#include "dd_dfilter.h"
#include "io_config_dfilter.h"

//=============================================================================
// DEC_FILTER_MCR_SETUP
//=============================================================================
extern void DEC_FILTER_MCR_SETUP( const uint32_t  *filt_coeff, 
                                                    const DECFILT_MCR_T dfilter_mcr,const  int16_t *dfilter_buffer );
//=============================================================================
// DEC_FILTER_DMA_SETUP_LOWPASS
//=============================================================================
extern void DEC_FILTER_DMA_SETUP_LOWPASS(void);
//=============================================================================
// DEC_FILTER_DMA_SETUP_BANDPASS
//=============================================================================
extern void DEC_FILTER_DMA_SETUP_BANDPASS(void);
//=============================================================================
// DEC_FILTER_INOUTPUT_DMA_ENABLE
//=============================================================================
extern void DEC_FILTER_INOUTPUT_DMA_ENABLE(void);
//=============================================================================
// DEC_FILTER_STOP_DSP
//=============================================================================
extern void DEC_FILTER_STOP_DSP(void);


//=============================================================================
// DMA Buffers
//=============================================================================
extern  int16_t DEC_FILT_A_Result_Buffer_A[DEC_FILT_A_DMA_RESULT_BUFF_SIZE];
extern  __attribute__ (( aligned(2) ))  int16_t DEC_FILT_A_Result_Buffer_B[DEC_FILT_A_DMA_RESULT_BUFF_SIZE];
//extern uint16_t      KNOCK_DSP_Process_Count_Winagte_PostStatus;

#endif
