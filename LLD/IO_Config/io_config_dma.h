#ifndef IO_CONFIG_DMA_H
#define IO_CONFIG_DMA_H


#include "dd_dma.h"
#include "io_config_qadc.h"
#include "io_config_knock.h"
#include "dd_qadc_interface.h"
#include "dd_dfilter_interface.h"
#include "dd_dspi_interface.h"
#include "soh_mpc56xx.h"

//=============================================================================
// Initialization Constant for DMA Group Priority
//=============================================================================
//=============================================================================
// DMA_QADC_CFFF_1
//=============================================================================
#define DMA_QADC_CFFF_1_Source_Address  (uint32_t)&QADC_CMD_FIFO1
#define DMA_QADC_CFFF_1_Dest_Address   (uint32_t)&(QADC.CFPR[1])
#define DMA_QADC_CFFF_1_SIZE ( sizeof(QADC_CMD_FIFO1)/sizeof(uint32_t) )
#define DMA_QADC_CFFF_1_Slast -( DMA_QADC_CFFF_1_SIZE*sizeof(uint32_t) )
#define DMA_QADC_CFFF_1_Dlast 0

extern DMA_Second_32Bit_T DMA_QADC_CFFF_1_Second_32Bit;

extern DMA_Third_32Bit_T DMA_QADC_CFFF_1_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_QADC_CFFF_1_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_QADC_CFFF_1_Eighth_32Bit;

//=============================================================================
// DMA_QADC_RFDF_1
//=============================================================================
#define DMA_QADC_RFDF_1_Source_Address  (uint32_t)&(QADC.RFPR[1].U16[1])
#define DMA_QADC_RFDF_1_Dest_Address     (uint32_t)&QADC_Queue_Result_1
#define DMA_QADC_RFDF_1_SIZE     ( sizeof(QADC_Queue_Result_1)/sizeof(uint16_t) )
#define DMA_QADC_RFDF_1_Slast   0
#define DMA_QADC_RFDF_1_Dlast   -( DMA_QADC_RFDF_1_SIZE*sizeof(uint16_t) )

extern DMA_Second_32Bit_T DMA_QADC_RFDF_1_Second_32Bit;

extern DMA_Third_32Bit_T DMA_QADC_RFDF_1_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_QADC_RFDF_1_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_QADC_RFDF_1_Eighth_32Bit ;


//=============================================================================
// DMA_QADC_CFFF_0
//=============================================================================
#define DMA_QADC_CFFF_0_Source_Address  (uint32_t)&QADC_KNOCK_ADC0
#define DMA_QADC_CFFF_0_Dest_Address   (uint32_t)&(QADC.CFPR[0])
#define DMA_QADC_CFFF_0_SIZE ( sizeof(QADC_KNOCK_ADC0)/sizeof(uint32_t) )
#define DMA_QADC_CFFF_0_Slast -( DMA_QADC_CFFF_0_SIZE*sizeof(uint32_t) )
#define DMA_QADC_CFFF_0_Dlast 0

extern DMA_Second_32Bit_T DMA_QADC_CFFF_0_Second_32Bit;

extern DMA_Third_32Bit_T DMA_QADC_CFFF_0_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_QADC_CFFF_0_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_QADC_CFFF_0_Eighth_32Bit;

//=============================================================================
// DMA_QADC_RFDF_0
//=============================================================================
#define DMA_QADC_RFDF_0_Source_Address  (uint32_t)&(QADC.RFPR[0].U16[1])
#define DMA_QADC_RFDF_0_Dest_Address     (uint32_t)&DEC_FILT_A_Result_Buffer_A
#define DMA_QADC_RFDF_0_SIZE     DEC_FILT_A_DMA_RESULT_BUFF_SIZE //( sizeof(DEC_FILT_A_Result_Buffer_A)/sizeof(int16_t) )
#define DMA_QADC_RFDF_0_Slast   0
#define DMA_QADC_RFDF_0_Dlast   -( DMA_QADC_RFDF_0_SIZE*sizeof(uint16_t) )

extern DMA_Second_32Bit_T DMA_QADC_RFDF_0_Second_32Bit;

extern DMA_Third_32Bit_T DMA_QADC_RFDF_0_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_QADC_RFDF_0_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_QADC_RFDF_0_Eighth_32Bit ;
//=============================================================================
// DMA_QADC_CFFF_4
//=============================================================================
#define DMA_QADC_CFFF_4_Source_Address  (uint32_t)&QADC_CMD_Timebase
#define DMA_QADC_CFFF_4_Dest_Address   (uint32_t)&(QADC.CFPR[4])
#define DMA_QADC_CFFF_4_SIZE ( sizeof(QADC_CMD_Timebase)/sizeof(uint32_t) )
#define DMA_QADC_CFFF_4_Slast -( DMA_QADC_CFFF_4_SIZE*sizeof(uint32_t) )
#define DMA_QADC_CFFF_4_Dlast 0

extern DMA_Second_32Bit_T DMA_QADC_CFFF_4_Second_32Bit;

extern DMA_Third_32Bit_T DMA_QADC_CFFF_4_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_QADC_CFFF_4_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_QADC_CFFF_4_Eighth_32Bit;

//=============================================================================
// DMA_QADC_RFDF_4
//=============================================================================
#define DMA_QADC_RFDF_4_Source_Address  (uint32_t)&(QADC.RFPR[4].U16[1])
#define DMA_QADC_RFDF_4_Dest_Address     (uint32_t)&QADC_Queue_Result_4
#define DMA_QADC_RFDF_4_SIZE     ( sizeof(QADC_CMD_Timebase)/sizeof(uint32_t) )
#define DMA_QADC_RFDF_4_Slast   0
#define DMA_QADC_RFDF_4_Dlast   -( DMA_QADC_RFDF_4_SIZE*sizeof(uint16_t) )

extern DMA_Second_32Bit_T DMA_QADC_RFDF_4_Second_32Bit;

extern DMA_Third_32Bit_T DMA_QADC_RFDF_4_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_QADC_RFDF_4_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_QADC_RFDF_4_Eighth_32Bit ;

//=============================================================================
// DMA_DSPIB_SR_TFFF
//=============================================================================
#define DMA_DSPIB_SR_TFFF_Source_Address  (uint32_t) DSPI_SPI_Port_Txd_B
#define DMA_DSPIB_SR_TFFF_Dest_Address     (uint32_t) &DSPI_B.PUSHR.U32
#define DMA_DSPIB_SR_TFFF_SIZE     ( sizeof(DSPI_SPI_Port_Txd_B)/sizeof(uint32_t) )
#define DMA_DSPIB_SR_TFFF_Slast   -(DMA_DSPIB_SR_TFFF_SIZE*2)
#define DMA_DSPIB_SR_TFFF_Dlast   0

extern DMA_Second_32Bit_T DMA_DSPIB_SR_TFFF_Second_32Bit;

extern DMA_Third_32Bit_T DMA_DSPIB_SR_TFFF_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_DSPIB_SR_TFFF_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_DSPIB_SR_TFFF_Eighth_32Bit ;


//=============================================================================
// DMA_QADC_CFFF_4
//=============================================================================
#define DMA_DSPIB_SR_RFDF_Source_Address  (uint32_t) (&DSPI_B.POPR.U32+2) 
#define DMA_DSPIB_SR_RFDF_Dest_Address   (uint32_t) DSPI_SPI_Port_Rxd_B
#define DMA_DSPIB_SR_RFDF_SIZE ( sizeof(DSPI_SPI_Port_Rxd_B)/sizeof(uint32_t) )
#define DMA_DSPIB_SR_RFDF_Slast   0
#define DMA_DSPIB_SR_RFDF_Dlast  -(DMA_DSPIB_SR_RFDF_SIZE*sizeof(uint16_t) )

extern DMA_Second_32Bit_T DMA_DSPIB_SR_RFDF_Second_32Bit;

extern DMA_Third_32Bit_T DMA_DSPIB_SR_RFDF_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_DSPIB_SR_RFDF_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_DSPIB_SR_RFDF_Eighth_32Bit;

//=============================================================================
//  DMA_DECFIL_FILL_BUF_A_LowPass
//=============================================================================
#define DMA_DECFIL_FILL_BUFA_LowPass_Source_Address  (uint32_t)&DEC_FILT_A_Result_Buffer_A[DEC_FILT_A_DMA_PREFILL_SIZE]
#define DMA_DECFIL_FILL_BUFA_LowPass_Dest_Address     (uint32_t)&(DEC_FILTER_A.IB)+2
#define DMA_DECFIL_FILL_BUFA_LowPass_SIZE     ( sizeof(DEC_FILT_A_Result_Buffer_A) -DEC_FILT_A_DMA_PREFILL_SIZE) 
#define DMA_DECFIL_FILL_BUFA_LowPass_Slast   0//-(DMA_DECFIL_FILL_BUFA_LowPass_SIZE*sizeof(uint16_t) )
#define DMA_DECFIL_FILL_BUFA_LowPass_Dlast   0

extern DMA_Second_32Bit_T DMA_DECFIL_FILL_BUFA_LowPass_Second_32Bit;

extern DMA_Third_32Bit_T DMA_DECFIL_FILL_BUFA_LowPass_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_DECFIL_FILL_BUFA_LowPass_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_DECFIL_FILL_BUFA_LowPass_Eighth_32Bit ;

//=============================================================================
//  DMA_DECFIL_FILL_BUF_A_LowPass
//=============================================================================
#define DMA_DECFIL_DRAIN_BUFA_LowPass_Source_Address  (uint32_t)&(DEC_FILTER_A.OB) +2
#define DMA_DECFIL_DRAIN_BUFA_LowPass_Dest_Address      (uint32_t)&DEC_FILT_A_Result_Buffer_B[DEC_FILT_A_DMA_PREFILL_SIZE/4]
#define DMA_DECFIL_DRAIN_BUFA_LowPass_SIZE     (( sizeof(DEC_FILT_A_Result_Buffer_A) -DEC_FILT_A_DMA_PREFILL_SIZE)/4 )
#define DMA_DECFIL_DRAIN_BUFA_LowPass_Slast   0
#define DMA_DECFIL_DRAIN_BUFA_LowPass_Dlast   0

extern DMA_Second_32Bit_T DMA_DECFIL_DRAIN_BUFA_LowPass_Second_32Bit;

extern DMA_Third_32Bit_T DMA_DECFIL_DRAIN_BUFA_LowPass_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_DECFIL_DRAIN_BUFA_LowPass_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_DECFIL_DRAIN_BUFA_LowPass_Eighth_32Bit ;

//=============================================================================
//  DMA_DECFIL_FILL_BUF_A_LowPass
//=============================================================================
#define DMA_DECFIL_FILL_BUFA_BandPass_Source_Address  (uint32_t)&DEC_FILT_A_Result_Buffer_B[DEC_FILT_A_DMA_PREFILL_SIZE+1]
#define DMA_DECFIL_FILL_BUFA_BandPass_Dest_Address     (uint32_t)&(DEC_FILTER_A.IB) +2 
#define DMA_DECFIL_FILL_BUFA_BandPass_SIZE     (uint32_t)(( sizeof(DEC_FILT_A_Result_Buffer_A) -DEC_FILT_A_DMA_PREFILL_SIZE)/4 )
#define DMA_DECFIL_FILL_BUFA_BandPass_Slast   -(DMA_DECFIL_FILL_BUFA_BandPass_SIZE*sizeof(uint16_t) )
#define DMA_DECFIL_FILL_BUFA_BandPass_Dlast   0

extern DMA_Second_32Bit_T DMA_DECFIL_FILL_BUFA_BandPass_Second_32Bit;

extern DMA_Third_32Bit_T DMA_DECFIL_FILL_BUFA_BandPass_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_DECFIL_FILL_BUFA_BandPass_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_DECFIL_FILL_BUFA_BandPass_Eighth_32Bit ;

//=============================================================================
//  DMA_DECFIL_FILL_BUF_A_LowPass
//=============================================================================
#define DMA_DECFIL_DRAIN_BUFA_BandPass_Source_Address  (uint32_t)&(DEC_FILTER_A.OB)+2
#define DMA_DECFIL_DRAIN_BUFA_BandPass_Dest_Address       (uint32_t)&DEC_FILT_A_Result_Buffer_B[DEC_FILT_A_DMA_RESULT_BUFF_SIZE/4+DEC_FILT_A_DMA_PREFILL_SIZE+1]
#define DMA_DECFIL_DRAIN_BUFA_BandPass_SIZE     (uint32_t)(( sizeof(DEC_FILT_A_Result_Buffer_A) -DEC_FILT_A_DMA_PREFILL_SIZE)/4 )
#define DMA_DECFIL_DRAIN_BUFA_BandPass_Slast   0
#define DMA_DECFIL_DRAIN_BUFA_BandPass_Dlast   0

extern DMA_Second_32Bit_T DMA_DECFIL_DRAIN_BUFA_BandPass_Second_32Bit;

extern DMA_Third_32Bit_T DMA_DECFIL_DRAIN_BUFA_BandPass_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_DECFIL_DRAIN_BUFA_BandPass_Sixth_32Bit;

//DMA_CHANNEL_MIOS_EMIOSFLAG_4
//=============================================================================

#define DMA_EMIOSFLAG_4_Source_Address  (uint32_t)&MIOS.CH[4].CADR
#define DMA_EMIOSFLAG_4_Dest_Address   (uint32_t) SOH_DMA_External_Ref_Time
#define DMA_EMIOSFLAG_4_SIZE ( sizeof(SOH_DMA_External_Ref_Time)/sizeof(uint32_t) )
#define DMA_EMIOSFLAG_4_Slast   0
#define DMA_EMIOSFLAG_4_Dlast  -(DMA_EMIOSFLAG_4_SIZE*sizeof(uint32_t))

extern DMA_Second_32Bit_T DMA_EMIOSFLAG_4_Second_32Bit;

extern DMA_Third_32Bit_T DMA_EMIOSFLAG_4_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_EMIOSFLAG_4_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_EMIOSFLAG_4_Eighth_32Bit;

extern DMA_Eighth_32Bit_T DMA_DECFIL_DRAIN_BUFA_BandPass_Eighth_32Bit ;
#endif
