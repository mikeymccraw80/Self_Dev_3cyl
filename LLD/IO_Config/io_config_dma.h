#ifndef IO_CONFIG_DMA_H
#define IO_CONFIG_DMA_H


#include "dd_dma.h"
#include "io_config_qadc.h"
#include "dd_qadc_interface.h"
#include "dd_dspi_interface.h"

//=============================================================================
// Initialization Constant for DMA Group Priority
//=============================================================================

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
#define DMA_DSPIB_SR_RFDF_Dlast  -(DMA_DSPIB_SR_RFDF_SIZE*2)

extern DMA_Second_32Bit_T DMA_DSPIB_SR_RFDF_Second_32Bit;

extern DMA_Third_32Bit_T DMA_DSPIB_SR_RFDF_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_DSPIB_SR_RFDF_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_DSPIB_SR_RFDF_Eighth_32Bit;

//=============================================================================
//DMA_CHANNEL_MIOS_EMIOSFLAG_4
//=============================================================================
extern uint32_t SOH_DMA_External_Ref_Time[8];

#define DMA_EMIOSFLAG_4_Source_Address  (uint32_t)&MIOS.CH[4].CADR
#define DMA_EMIOSFLAG_4_Dest_Address   (uint32_t) SOH_DMA_External_Ref_Time
#define DMA_EMIOSFLAG_4_SIZE ( sizeof(SOH_DMA_External_Ref_Time)/sizeof(uint32_t) )
#define DMA_EMIOSFLAG_4_Slast   0
#define DMA_EMIOSFLAG_4_Dlast  -(DMA_EMIOSFLAG_4_SIZE*sizeof(uint32_t))

extern DMA_Second_32Bit_T DMA_EMIOSFLAG_4_Second_32Bit;

extern DMA_Third_32Bit_T DMA_EMIOSFLAG_4_Third_32Bit;

extern DMA_Sixth_32Bit_T DMA_EMIOSFLAG_4_Sixth_32Bit;

extern DMA_Eighth_32Bit_T DMA_EMIOSFLAG_4_Eighth_32Bit;

#endif
