
#include "dd_qadc.h"
#include "io_config_dma.h"

//=============================================================================
// QADC
//=============================================================================
#define SECTION_QADC_REGISTER
#include "section.h"
 QADC_T QADC;
#define SECTION_END
#include "section.h"

uint16_t QADC_Queue_Result_4[AD_ANALOG_MAX_SIGNAL_NAMES];


//=============================================================================
// Macros to Clear the W1C Bits
//=============================================================================
#define QADC_RFOF_RFDF_CLEAR (0x05FFFFFFUL)
#define QADC_CFUF_CLEAR      (0x0DF5FFFFUL)
#define QADC_CFUF_RFDF_CLEAR (0x0DF7FFFFUL)
#define QADC_RFDF_CLEAR      (0x05F7FFFFUL)

//=============================================================================
// Gain calibration for QADC, keep around when only offset is selected
//=============================================================================
static uint16_t QADC_ADC_Calibration_Gain[] =
{
   1,1
};

static uint16_t QADC_ADC_Calibration_Offset[] =
{
   0,0
};

#define QADC_POWER_2_TO_THE_14TH (16384U)
#define ADC_CAL_RES75_VREF (12288U)
#define ADC_CAL_RES25_VREF (4096U)
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
// QADC_ANALOG_Calibrate_Converter
//=============================================================================
void QADC_ANALOG_Calibrate_Converter( ADC_Converter_T  converter)
{
   ADC_CMF_T         cmf;
   int32_t           occ_int ;
   uint32_t          raw_res75_vref;
   uint32_t          raw_res25_vref = 0;
   uint32_t          counter;
   uint32_t          reg_value;
   static uint32_t   pop;


          // reset to disabled before returning to a running state.
   QADC.CFCR[QADC_FIFO_0].F.MODE = QADC_TRIGGER_MODE_DISABLED;

      while ( QADC_COMMAND_FIFO_STATUS_IDLE != Extract_Bits(QADC.CFSR.U32, ( BIT_30 - ( QADC_FIFO_0 * BIT_2 ) ),BIT_2 ) )
      {
         // Certify that CFS has changed to IDLE before setting CFINVn.
      }

   // ONLY write to this when mode is configured as disabled!!!
   QADC.CFCR[QADC_FIFO_0].F.CFINV = 1;

   QADC.CFTCR[QADC_FIFO_0].F.TC_CF = 0;

   QADC.CFCR[QADC_FIFO_0].F.MODE = QADC_TRIGGER_MODE_SOFTWARE_TRIGGER_Single_Scan;

   // enable single scan for QADC_TRIGGER_MODE_SOFTWARE_TRIGGER mode
   QADC.CFCR[QADC_FIFO_0].F.SSE = 1;

   // if there is something still left, remove it.
   for ( counter = 0; counter < QADC.FISR[QADC_FIFO_0].F.RFCTR; counter++ )
   {
      pop = (uint16_t)QADC.RFPR[QADC_FIFO_0].F.RF_POP;
   }
   // resets RFIFO Overflow status
     reg_value = QADC.FISR[QADC_FIFO_0].U32;
     reg_value = (reg_value & QADC_RFOF_RFDF_CLEAR);
     QADC.FISR[QADC_FIFO_0].U32 = reg_value;

      //////////////////////////////////////////////////////////////////////////

      // 1. Convert channel 44 with a command that has its CAL bit negated and obtain the raw, uncalibrated
      //    result for 25%VREF (RAW_RES25%VREF).
     // Push command into fifo
      QADC.CFPR[QADC_FIFO_0] =  QADC_CALIBRATION_ADC1_REF25[converter].U32;

      //
      // clear the underflow status flag. The eQADC will not transfer
      // entries from an underflowing CFIFO.
      //
      reg_value = QADC.FISR[QADC_FIFO_0].U32;
      reg_value = (reg_value & QADC_CFUF_CLEAR);
      QADC.FISR[QADC_FIFO_0].U32 = reg_value;
      // Wait for completion
      while (  QADC.FISR[QADC_FIFO_0].F.RFDF == QADC_RESULT_FIFO_EMPTY )
      {
         // Do Nothing
      }
	  
      // read result
      raw_res25_vref = (uint16_t)(QADC.RFPR[QADC_FIFO_0].F.RF_POP);

      //////////////////////////////////////////////////////////////////////////

	          // reset to disabled before returning to a running state.
   QADC.CFCR[QADC_FIFO_0].F.MODE = QADC_TRIGGER_MODE_DISABLED;

      while ( QADC_COMMAND_FIFO_STATUS_IDLE != Extract_Bits(QADC.CFSR.U32, ( BIT_30 - ( QADC_FIFO_0 * BIT_2 ) ),BIT_2 ) )
      {
         // Certify that CFS has changed to IDLE before setting CFINVn.
      }

   // ONLY write to this when mode is configured as disabled!!!
   QADC.CFCR[QADC_FIFO_0].F.CFINV = 1;

   QADC.CFTCR[QADC_FIFO_0].F.TC_CF = 0;

   QADC.CFCR[QADC_FIFO_0].F.MODE = QADC_TRIGGER_MODE_SOFTWARE_TRIGGER_Single_Scan;

   // enable single scan for QADC_TRIGGER_MODE_SOFTWARE_TRIGGER mode
   QADC.CFCR[QADC_FIFO_0].F.SSE = 1;

   // if there is something still left, remove it.
   for ( counter = 0; counter < QADC.FISR[QADC_FIFO_0].F.RFCTR; counter++ )
   {
      pop = (uint16_t)QADC.RFPR[QADC_FIFO_0].F.RF_POP;
   }
   // resets RFIFO Overflow status
     reg_value = QADC.FISR[QADC_FIFO_0].U32;
     reg_value = (reg_value & QADC_RFOF_RFDF_CLEAR);
     QADC.FISR[QADC_FIFO_0].U32 = reg_value;

      //////////////////////////////////////////////////////////////////////////
      // 2. Convert channel 43 with a command that has its CAL bit negated and obtain the raw, uncalibrated
      //    result for 75%VREF (RAW_RES75%VREF).
      // Push command into fifo
      QADC.CFPR[QADC_FIFO_0] = QADC_CALIBRATION_ADC1_REF75[converter].U32;


      reg_value = QADC.FISR[QADC_FIFO_0].U32;
      reg_value = (reg_value & QADC_CFUF_CLEAR);
      QADC.FISR[QADC_FIFO_0].U32 = reg_value;
      // Wait for completion
      while (  QADC.FISR[QADC_FIFO_0].F.RFDF == QADC_RESULT_FIFO_EMPTY )
      {
         // Do Nothing
      }

      // read result
      raw_res75_vref = (uint16_t)(QADC.RFPR[QADC_FIFO_0].F.RF_POP);

      //////////////////////////////////////////////////////////////////////////
      // 3. Because the expected values for the conversion of these voltages are known (CAL_RES25%VREF
      //    and CAL_RES75%VREF), GCC and OCC values can be calculated from equations (5.5.d) and
      //    (5.5.e) using these values, and the results determined in steps 1 and 2.
      QADC_ADC_Calibration_Gain[converter] = (uint16_t)(( ( ADC_CAL_RES75_VREF - ADC_CAL_RES25_VREF ) * QADC_POWER_2_TO_THE_14TH ) / (uint16_t)(raw_res75_vref - raw_res25_vref ));
      
      if( (( ( ADC_CAL_RES75_VREF - ADC_CAL_RES25_VREF ) * QADC_POWER_2_TO_THE_14TH ) - ((uint16_t)(raw_res75_vref - raw_res25_vref )*QADC_ADC_Calibration_Gain[converter])) >= ((uint16_t)(raw_res75_vref - raw_res25_vref ) /2) )
      {
         QADC_ADC_Calibration_Gain[converter] += 1;
      }

        //QADC.FISR[QADC_FIFO_0].F.EOQF = 1;
      // 4. Write the GCC value to ADCn gain calibration registers (see Section 19.3.3.4) and the OCC value
      //    to ADCn offset calibration constant registers (see Section 19.3.3.5) using write configuration
      //     commands.

       cmf.U32 = 0x00000000;   
       cmf.WF.EOQ = 0x0;
       cmf.WF.BN= converter;
       cmf.WF.R_W = QADC_READ_WRITE_FLAG_WRITE;
       cmf.WF.REG_DATA = QADC_ADC_Calibration_Gain[converter];
       cmf.WF.REG_ADDRESS = QADC_REGISTER_ADDRESS_GAIN_CALIBRATION_CONSTANT_REGISTER;
      QADC.CFPR[QADC_FIFO_0] = cmf.U32;

	  

      occ_int = ( ADC_CAL_RES75_VREF * QADC_POWER_2_TO_THE_14TH ) - ( (int32_t)QADC_ADC_Calibration_Gain[converter] * (int32_t)raw_res75_vref ) - ( 2U * QADC_POWER_2_TO_THE_14TH );
      QADC_ADC_Calibration_Offset[converter] = (int16_t)(occ_int / QADC_POWER_2_TO_THE_14TH);

      if( (((int32_t)QADC_ADC_Calibration_Offset[converter] *QADC_POWER_2_TO_THE_14TH) - occ_int) >= (QADC_POWER_2_TO_THE_14TH/2))
      {
         if( QADC_ADC_Calibration_Offset[converter]  >= 0 )
         {
            QADC_ADC_Calibration_Offset[converter]  += 1;
         }
         else
         {
            QADC_ADC_Calibration_Offset[converter]  -= 1;
         }
      }
	  
      // 5. Write the GCC value to ADCn gain calibration registers (see Section 19.3.3.4) and the OCC value
      //    to ADCn offset calibration constant registers (see Section 19.3.3.5) using write configuration
      //     commands.
        cmf.U32 = 0x00000000;   
       cmf.WF.EOQ = 0x1;
       cmf.WF.BN= converter;
       cmf.WF.R_W = QADC_READ_WRITE_FLAG_WRITE;
       cmf.WF.REG_DATA = QADC_ADC_Calibration_Offset[converter];
       cmf.WF.REG_ADDRESS = QADC_REGISTER_ADDRESS_OFFSET_CALIBRATION_CONSTANT_REGISTER;

  
      QADC.CFPR[QADC_FIFO_0] = cmf.U32;


     
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

   // enable single scan for QADC_TRIGGER_MODE_SOFTWARE_TRIGGER mode
   QADC.CFCR[QADC_FIFO_0].F.SSE = 1;

   // if there is something still left, remove it.
   for ( counter = 0; counter < QADC.FISR[QADC_FIFO_0].F.RFCTR; counter++ )
   {
      pop = (uint16_t)QADC.RFPR[QADC_FIFO_0].F.RF_POP;
   }
   //Disable the FIFO and Invalidate
   QADC.CFCR[QADC_FIFO_0].F.MODE = QADC_TRIGGER_MODE_DISABLED;
   
    while ( QADC_COMMAND_FIFO_STATUS_IDLE != Extract_Bits(QADC.CFSR.U32, ( BIT_30 - ( QADC_FIFO_0 * BIT_2 ) ),BIT_2 ) )
   {
      // Certify that CFS has changed to IDLE before setting CFINVn.
   }

   // ONLY write to this when mode is configured as disabled!!!
   QADC.CFCR[QADC_FIFO_0].F.CFINV = 1;
   // resets RFIFO status
   QADC.CFTCR[QADC_FIFO_0].F.TC_CF = 0;
   reg_value = QADC.FISR[QADC_FIFO_0].U32;
   reg_value = (reg_value & QADC_RFDF_CLEAR);
   QADC.FISR[QADC_FIFO_0].U32 = reg_value;
 

}


//=============================================================================
// QADC_Analog_Get_Value
//=============================================================================
 uint16_t  QADC_Analog_Get_Value(AD_Analog_T channel )
{
   return QADC_Queue_Result_4[channel];
}



