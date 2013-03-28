
#include "dd_qadc.h"
#include "io_config_dma.h"

//=============================================================================
// QADC
//=============================================================================
QADC_T QADC;

uint16_t QADC_Queue_Result_4[AD_ANALOG_MAX_SIGNAL_NAMES];

//=============================================================================
// QADC_Initialize_Device
//=============================================================================
void QADC_Initialize_Device(void )
{

   //ADC_WCCMF_F_T WCCMF_temp;
   ADC_CMF_T CMF_temp;

   // set eQADC module configuration register
   QADC.MCR.U32                   = QADC_INITIAL_MCR.U32;
   //eQADC STAC Client Configuration Register (EQADC_REDLCCR)
   QADC.REDLCCR.U32          = QADC_INITIAL_REDLCCR.U32;


// set eQADC CFIFO control register 
  QADC.CFCR[QADC_FIFO_0].U16 = QADC_CFCR_RESET.U16;  // invalidate all CCW entries in CFIFO0  
  QADC.CFCR[QADC_FIFO_1].U16 = QADC_CFCR_RESET.U16;  // invalidate all CCW entries in CFIFO1  
  QADC.CFCR[QADC_FIFO_2].U16 = QADC_CFCR_RESET.U16;  // invalidate all CCW entries in CFIFO2  
  QADC.CFCR[QADC_FIFO_3].U16 = QADC_CFCR_RESET.U16;  // invalidate all CCW entries in CFIFO3  
  QADC.CFCR[QADC_FIFO_4].U16 = QADC_CFCR_RESET.U16;  // invalidate all CCW entries in CFIFO4  
  QADC.CFCR[QADC_FIFO_5].U16 = QADC_CFCR_RESET.U16;  // invalidate all CCW entries in CFIFO5 

   // set eQADC FIFO and interrupt staus registers
  QADC.FISR[QADC_FIFO_0].U32 = QADC_FISR_RESET.U32;  // clear all interrupt flags relative to CFIFO0
  QADC.FISR[QADC_FIFO_1].U32 = QADC_FISR_RESET.U32;  // clear all interrupt flags relative to CFIFO1
  QADC.FISR[QADC_FIFO_2].U32 = QADC_FISR_RESET.U32;  // clear all interrupt flags relative to CFIFO2
  QADC.FISR[QADC_FIFO_3].U32 = QADC_FISR_RESET.U32;  // clear all interrupt flags relative to CFIFO3
  QADC.FISR[QADC_FIFO_4].U32 = QADC_FISR_RESET.U32;  // clear all interrupt flags relative to CFIFO4
  QADC.FISR[QADC_FIFO_5].U32 = QADC_FISR_RESET.U32;  // clear all interrupt flags relative to CFIFO5
  
  // set eQADC interrupt and DMA control register
  QADC.IDCR[QADC_FIFO_0].U16 = 0x0000;  // disable all interrupts and DMA request from CFIFO0
  QADC.IDCR[QADC_FIFO_1].U16 = 0x0000;  // disable all interrupts and DMA request from CFIFO1
  QADC.IDCR[QADC_FIFO_2].U16 = 0x0000;  // disable all interrupts and DMA request from CFIFO2
  QADC.IDCR[QADC_FIFO_3].U16 = 0x0000;  // disable all interrupts and DMA request from CFIFO3
  QADC.IDCR[QADC_FIFO_4].U16 = 0x0000;  // disable all interrupts and DMA request from CFIFO4
  QADC.IDCR[QADC_FIFO_5].U16 = 0x0000;  // disable all interrupts and DMA request from CFIFO5

  // eQADC CFIFO Transfer Counter Registers (EQADC_CFTCR)
  QADC.CFTCR[QADC_FIFO_0].U16 = 0x0000;  // clear Transfer Counter for CFIFOx 
  QADC.CFTCR[QADC_FIFO_1].U16 = 0x0000;  // clear Transfer Counter for CFIFOx 
  QADC.CFTCR[QADC_FIFO_2].U16 = 0x0000;  // clear Transfer Counter for CFIFOx 
  QADC.CFTCR[QADC_FIFO_3].U16 = 0x0000;  // clear Transfer Counter for CFIFOx 
  QADC.CFTCR[QADC_FIFO_4].U16 = 0x0000;  // clear Transfer Counter for CFIFOx 
  QADC.CFTCR[QADC_FIFO_5].U16 = 0x0000;  // clear Transfer Counter for CFIFOx 
  
   // set eQADC Null message send format register
   QADC.NMSFR.U32 = 0x00000000;  // Null Message Format

   //eQADC External Trigger Digital Filter Register (EQADC_ETDFR)
   QADC.ETDFR.U32 = QADC_INITIAL_ETDFR.U32;

   //eQADC SSI Control Register (EQADC_SSICR)
   QADC.SSICR.U32 = QADC_INITIAL_SSICR.U32;

  //ADC0_CR
   CMF_temp.U32 = 0x00000000;   
   CMF_temp.WF.BN = ADC_CONVERTER_0;
   CMF_temp.WF.R_W = QADC_READ_WRITE_FLAG_WRITE;
   CMF_temp.WF.REG_DATA = QADC_ADC_0_CR_INIT_VALUE;
   CMF_temp.WF.REG_ADDRESS = QADC_REGISTER_ADDRESS_CONTROL_REGISTER;

//////////////////////////////////////////////////////////////////////////
      //Set FIFO 0 to software triggered mode
   QADC.CFCR[QADC_FIFO_0].F.MODE = QADC_TRIGGER_MODE_SOFTWARE_TRIGGER_Single_Scan;
	  
    //eQADC CFIFO Push Registers (EQADC_CFPR)
    QADC.CFPR[QADC_FIFO_0] =  CMF_temp.U32;

   //ADC1_CR
   CMF_temp.U32 = 0x00000000;   
   CMF_temp.WF.BN = ADC_CONVERTER_1;
   CMF_temp.WF.R_W = QADC_READ_WRITE_FLAG_WRITE;
   CMF_temp.WF.REG_DATA = QADC_ADC_1_CR_INIT_VALUE;
   CMF_temp.WF.REG_ADDRESS = QADC_REGISTER_ADDRESS_CONTROL_REGISTER;
   
    //eQADC CFIFO Push Registers (EQADC_CFPR)
    QADC.CFPR[QADC_FIFO_0] =  CMF_temp.U32;

   //ADC_ACR1
   CMF_temp.U32 = 0x00000000;   
   CMF_temp.WF.EOQ = 0x1;
   CMF_temp.WF.BN= ADC_CONVERTER_0;
   CMF_temp.WF.R_W = QADC_READ_WRITE_FLAG_WRITE;
   CMF_temp.WF.REG_DATA = QADC_INITIAL_ACR1.U16;
   CMF_temp.WF.REG_ADDRESS = QADC_REGISTER_ADDRESS_ALTERNATE_CONFIGURATION_1_CONTROL_REGISTER;
       //eQADC CFIFO Push Registers (EQADC_CFPR)
    QADC.CFPR[QADC_FIFO_0] =  CMF_temp.U32;


   //Set to single scan enabled ( when this value is written FISRn.SSS is set until EOQF if processed
   QADC.CFCR[QADC_FIFO_0].F.SSE = 1;

   // now wait for the Command Queue to reach End-Of-Queue status, where
   // we need to disable the CFIFO so that it can be reset for conversion
   // queues (CFIFO MODE must be disabled before resetting to another mode
   // according to eQADC specifications)
   while( QADC.FISR[QADC_FIFO_0].F.EOQF != 1 )
   {
      // wait till End-Of-Queue reached
   }
   QADC.FISR[QADC_FIFO_0].F.EOQF = 1;
   //Disable the FIFO and Invalidate
   QADC.CFCR[QADC_FIFO_0].F.MODE = 0x0;
   while(QADC.CFSR.F.CFS0 ) {}
   QADC.CFCR[QADC_FIFO_0].F.CFINV = 0x1;

   // clear the flag by writing a one to it
   QADC.FISR[QADC_FIFO_0].F.CFUF = 0x1; 

   
//////////////////////////////////////////////////

   //
   QADC.IDCR[QADC_FIFO_4].F.CFFS = QADC_IDCR_REQUEST_DMA_TRANSFER;
   QADC.IDCR[QADC_FIFO_4].F.CFFE =  true;
   //
   QADC.IDCR[QADC_FIFO_4].F.RFDS = QADC_IDCR_REQUEST_DMA_TRANSFER;
   QADC.IDCR[QADC_FIFO_4].F.RFDE=  true;


   //Set FIFO 0 to software triggered mode
   //  QADC.CFCR[QADC_FIFO_4].F.MODE = QADC_TRIGGER_MODE_FALLING_EDGE_EXTERNAL_TRIGGER;
 QADC.CFCR[QADC_FIFO_4].F.MODE = QADC_TRIGGER_MODE_FALLING_EDGE_EXTERNAL_TRIGGER_Continuous_Scan;


}


//=============================================================================
// QADC_Analog_Get_Value
//=============================================================================
 uint16_t  QADC_Analog_Get_Value(AD_Analog_T channel )
{
   return QADC_Queue_Result_4[channel];
}



