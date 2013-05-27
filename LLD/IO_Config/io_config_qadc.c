

#include "io_config_qadc.h"



//=============================================================================
// eQADC
//=============================================================================


//The eQADC Module Configuration Register (EQADC_MCR) contains bits used to control how the
//eQADC responds to a debug mode entry request, and to enable the eQADC SSI interface.
const QADC_MCR_T QADC_INITIAL_MCR=
{
   	//Immediate Conversion Command Enable ADCn (n = 0, 1)
      0,0, //ICEAn
      //eQADC Synchronous Serial Interface Enable Field
      QADC_SYNC_SERIAL_INTERFACE_DISABLED, //ESSIE
      //Debug enable
      QADC_DEBUG_DISABLED  //DBG

};

//The eQADC STAC Client Configuration Register (EQADC_REDLCCR) contains bits used to control
//which time slots the eQADC selects to obtain predefined external time bases.
const QADC_REDLCCR_T QADC_INITIAL_REDLCCR =
{

      QADC_REDBS_TBASE_0_15, //REDBS2
      QADC_SRV_eTPUA_TCR1,   //SRV2
      QADC_REDBS_TBASE_0_15, //REDBS1
      QADC_SRV_eTPUA_TCR1   //SRV1
};


//
// CFIFO Control Registers (QADC_CFCRn)
//
const QADC_CFCR_T  QADC_CFCR_RESET=
{
      0,                      // CFIFO0 has a normal value of entries.
      0,                      // Streaming mode of CFIFO0 is disabled.
      0,                      // Single-Scan disabled
      1,                      // Reset CFIFO
      0,                      // CFIFO is disabled
      0

};

//
// FIFO and Interrupt Status Registers (QADC_FISRn)
//
//   !!NOTE!!
//   these are status registers that require a write of '1' to clear values
//

const QADC_FISR_T  QADC_FISR_RESET =
{
      1,                       // Non-coherency status
      1,                       // Trigger-overrun status
      1,                       // Pause status
      1,                       // End-of-Queue status
      1,                       // CFIFO underflow status
      0,                       // SSSn bit - !!writing has no effect!!
      1,                       // !!do not write '1' when DMA Requests set!!
      1,                       // RFIFO overflow status
      1,                       // !!do not write '1' when DMA Requests set!!
      0,                       // CFCTRn     \ 
      0,                       // TNXTPTRn    -\  writes to these fields
      0,                       // RFCTRn      -/  have no effect
      0                        // POPNXTPTRn / 

};

const QADC_SSICR_T  QADC_INITIAL_SSICR=
{
      QADC_MINIMUM_DELAY_AFTER_TRANSMISSION_FCLOCK_1, // minimum delay after transmission
      QADC_BAUD_RATE_SYSTEM_CLOCK_DIVIDE_FACTOR_8    // FCK sys clock divider
};
//The eQADC External Trigger Digital Filter Register (EQADC_ETDFR) is used to set the minimum time
//a signal must be held in a logic state on the CFIFO triggers inputs to be recognized as an edge or level
//gated trigger. The Digital Filter Length field specifies the minimum number of system clocks that must be
//counted by the digital filter counter to recognize a logic state change. However, there is a control signal
//that can be used to bypass the digital filter when this is not needed.
const QADC_ETDFR_T QADC_INITIAL_ETDFR =
{
      QADC_DIGITAL_FILTER_LENGTH_2//DFL
};

const ADC_ACR_T  QADC_INITIAL_ACR1 =
{
   ADC_ALTCFG_RETINH_RESULT_TRANSFER_TO_RESULT_QUEUE,      // RET_INH  :  BIT_1; // Bits     0
   ADC_ALTCFG_DEST_RFIFO,                                     //DEST     :  BIT_4; // Bits     [2:5]
   ADC_ALTCFG_FMTA_RIGHT_JUSTIFIED_UNSIGNED,  // FMTA     :  BIT_1; // Bits     6
   ADC_ALTCFG_RESSEL_12BIT,                                 // bitfield16_t  RESSEL   :  BIT_2; // Bits     [8:9]
   ADC_ALTCFG_ATBSEL_INTERNAL, // bitfield16_t  ATBSEL   :  BIT_2; // Bits     [12:13]
   ADC_ALTCFG_PREGAIN_X1 //bitfield16_t  PRE_GAIN :  BIT_2; // Bits     [14:15]

};

const ADC_CCMF_T  QADC_CMD_Timebase[AD_ANALOG_MAX_SIGNAL_NAMES]=
{

  {
    1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN0_DAN_0_P,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
  },

//const ADC_CCMF_T  QADC_CMD_ESCLoVI = 
 {
    1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN1_DAN_0_N,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
 },

//const ADC_CCMF_T  QADC_CMD_MAPSVI  = 
 {
    1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN2_DAN_1_P,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_ACPVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN3_DAN_1_N,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_EGRFBVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN4_DAN_2_P,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_TPS1VI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN5_DAN_2_N,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_TPS2VI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN6_DAN_3_P,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_PPS1VI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN7_DAN_3_N,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_PPS2VI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN9_ANX,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_FLVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN11_ANZ,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_EOPVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN12_MA0_SDS,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_O2AVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN13_MA1_SDO,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},
//const ADC_CCMF_T  QADC_CMD_O2BVI   = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN14_MA2_SDI,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_CRUCTLVI   = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN15_FCK,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_CLTVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN16,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_IAT_VI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN17,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_BSTTVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN18,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_FETVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN21,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_BRKPVI  = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN22,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_IHFBVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN23,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},
//const ADC_CCMF_T  QADC_CMD_BSTPVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN24,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_SPA1VI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN25,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_SPA2VI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN27,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},


//const ADC_CCMF_T  QADC_CMD_SPA3VI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN28,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_IGNVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN30,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_ACCVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN31,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},
//const ADC_CCMF_T  QADC_CMD_PBATTVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN32,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_ETCCurVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN33,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_PumpVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN34,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_DFSWDI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN35,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_HWCFGVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN38,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_DACVI = 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN39,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
},

//const ADC_CCMF_T  QADC_CMD_TEMP_SENSOR= 
{
   1,    //EOQ      
   0,    //PAUSE 
   0,    // REP     
   0,    //EB   
   ADC_CONVERTER_1,    //BN    
   false,   // CAL  
   QADC_FIFO_4,   //MESSAGE_TAG 
   QADC_SAMPLE_CYCLES_2,   //LST        
   0,   //TSR       
   QADC_CHANNEL_CONVERSION_FORMAT_RIGHT_JUSTIFIED_UNSIGNED,   //FMT         
   QADC_CHANNEL_AN128_TEMP_SENSOR,    // CHANNEL 
   QADC_CONFIGURATION_REGISTER_1
}

 };

