
#include "dd_siu.h"
#include "io_config_siu.h"


//=============================================================================
// SIU
//=============================================================================
SIU_T SIU;


//=============================================================================
// SIU_Initialize_Device
//=============================================================================
void SIU_Initialize_Device(void )
{

   //The SIU_ECCR controls the timing relationship between the system clock and the external clock
   //CLKOUT. All bits and fields in the SIU_ECCR are read/write and are reset by the IP Green-Line
   //asynchronous reset signal.
   SIU.ECCR.U32 = SIU_INITIAL_ECCR.U32;
   
   //System Clock Register (SIU_SYSDIV)
   SIU.SYSDIV.U32 = SIU_INITIAL_SYSDIV.U32;
   
   //The DSPI Input Select Register (SIU_DISR) register specifies the source of each DSPI data input, slave
   //select, clock input, and trigger input to allow serial and parallel chaining of the DSPI blocks.
   SIU.DISR.U32 = SIU_INITIAL_DISR.U32;

   //Chip Configuration Register (SIU_CCR)
   SIU.CCR.U32   = SIU_INITIAL_CCR.U32;
   
   //The SIU_ISEL 8 register is used to multiplex the ETPU[24:29] inputs. These six eTPU channels can come
   //from the output of the DSPI or the corresponding pad.
   SIU.ISEL8.U32 = SIU_INITIAL_ISEL8.U32;

   //eQADC Trigger Input Select Register (SIU_ETISR)
    SIU.ETISR.U32 = SIU_ETISR_INITIAL.U32;
   SIU.ISEL3.U32 = SIU_ISEL3_INITIAL.U32;

   //SIU.ISEL9.U32 = SIU_INITIAL_ISEL9.U32;
  

}


//=============================================================================
// SIU_GPIO_DISCRETE_Initialize_Device
//=============================================================================
void SIU_GPIO_Initialize_Device( void )
{

     // GPIO Pin 83 CAN_A_TX
     SIU.PCR[SIU_GPIO_CHANNEL_83] =SIU_INITIAL_PCR_83 ;
    // GPIO Pin 84  CAN_A_RX
     SIU.PCR[SIU_GPIO_CHANNEL_84] =SIU_INITIAL_PCR_84 ;
    // GPIO Pin 87 CAN_C_TX
     SIU.PCR[SIU_GPIO_CHANNEL_87] =SIU_INITIAL_PCR_87 ;
    // GPIO Pin 88 CAN_C_RX
     SIU.PCR[SIU_GPIO_CHANNEL_88] =SIU_INITIAL_PCR_88 ;
	
     // GPIO Pin 89 SCI_A_TX
     SIU.PCR[SIU_GPIO_CHANNEL_89] =SIU_INITIAL_PCR_89 ;
     // GPIO Pin 90 SCI_A_RX
     SIU.PCR[SIU_GPIO_CHANNEL_90] =SIU_INITIAL_PCR_90 ;
     // GPIO Pin 91 SCI_B_TX
     SIU.PCR[SIU_GPIO_CHANNEL_91] =SIU_INITIAL_PCR_91 ;
     // GPIO Pin 92 SCI_B_RX
     SIU.PCR[SIU_GPIO_CHANNEL_92] =SIU_INITIAL_PCR_92 ;

     //Pad Configuration Registers 98 - 99
    //waiting for update

	 
     // GPIO Pin 102  DSPI_B_SCK
     SIU.PCR[SIU_GPIO_CHANNEL_102] =SIU_INITIAL_PCR_102 ;
     // GPIO Pin 103 DSPI_B_SIN
     SIU.PCR[SIU_GPIO_CHANNEL_103] =SIU_INITIAL_PCR_103 ;
     // GPIO Pin 104 DSPI_B_SOUT
     SIU.PCR[SIU_GPIO_CHANNEL_104] =SIU_INITIAL_PCR_104 ;
     // GPIO Pin 105  DSPI_B_PCS[0]
     SIU.PCR[SIU_GPIO_CHANNEL_105] =SIU_INITIAL_PCR_105 ;
     // GPIO Pin 106  DSPI_B_PCS[1]
     SIU.PCR[SIU_GPIO_CHANNEL_106] =SIU_INITIAL_PCR_106 ;
      // GPIO Pin 107  DSPI_B_PCS[2]
     SIU.PCR[SIU_GPIO_CHANNEL_107] =SIU_INITIAL_PCR_107 ;
      // GPIO Pin 108  DSPI_B_PCS[3]
     SIU.PCR[SIU_GPIO_CHANNEL_108] =SIU_INITIAL_PCR_108 ;
      // GPIO Pin 109  DSPI_B_PCS[4]
     SIU.PCR[SIU_GPIO_CHANNEL_109] =SIU_INITIAL_PCR_109 ;
     // GPIO Pin 110  DSPI_B_PCS[5]
     SIU.PCR[SIU_GPIO_CHANNEL_110] =SIU_INITIAL_PCR_110 ;


    //eTPU A
    // GPIO Pin 114  eTPU0  
     SIU.PCR[SIU_GPIO_CHANNEL_114] =SIU_INITIAL_PCR_114 ;
    // GPIO Pin 115  eTPU1  
     SIU.PCR[SIU_GPIO_CHANNEL_115] =SIU_INITIAL_PCR_115 ;
    // GPIO Pin 116  eTPU2  
     SIU.PCR[SIU_GPIO_CHANNEL_116] =SIU_INITIAL_PCR_116 ;
    // GPIO Pin 117  eTPU3
     SIU.PCR[SIU_GPIO_CHANNEL_117] =SIU_INITIAL_PCR_117 ;
    // GPIO Pin 118  eTPU4
     SIU.PCR[SIU_GPIO_CHANNEL_118] =SIU_INITIAL_PCR_118 ;
	 // GPIO Pin 119  eTPU5
     SIU.PCR[SIU_GPIO_CHANNEL_119] =SIU_INITIAL_PCR_119 ;
	// GPIO Pin 120  eTPU6
     SIU.PCR[SIU_GPIO_CHANNEL_120] =SIU_INITIAL_PCR_120 ;
	 // GPIO Pin 121  eTPU7
     SIU.PCR[SIU_GPIO_CHANNEL_121] =SIU_INITIAL_PCR_121 ;
	 // GPIO Pin 122 eTPU8
     SIU.PCR[SIU_GPIO_CHANNEL_122] =SIU_INITIAL_PCR_122 ;
	 // GPIO Pin 123 eTPU9
     SIU.PCR[SIU_GPIO_CHANNEL_123] =SIU_INITIAL_PCR_123 ;
	 // GPIO Pin 124  eTPU10
     SIU.PCR[SIU_GPIO_CHANNEL_124] =SIU_INITIAL_PCR_124 ;
	// GPIO Pin 125  eTPU11
     SIU.PCR[SIU_GPIO_CHANNEL_125] =SIU_INITIAL_PCR_125 ;
	// GPIO Pin 126  eTPU12 
     SIU.PCR[SIU_GPIO_CHANNEL_126] =SIU_INITIAL_PCR_126 ;
	 // GPIO Pin 127  eTPU13
     SIU.PCR[SIU_GPIO_CHANNEL_127] =SIU_INITIAL_PCR_127 ;
	 // GPIO Pin 128  eTPU14
     SIU.PCR[SIU_GPIO_CHANNEL_128] =SIU_INITIAL_PCR_128 ;
	// GPIO Pin 129  eTPU15 
     SIU.PCR[SIU_GPIO_CHANNEL_129] =SIU_INITIAL_PCR_129 ;
	 // GPIO Pin 130  eTPU16 
     SIU.PCR[SIU_GPIO_CHANNEL_130] =SIU_INITIAL_PCR_130 ;
	  // GPIO Pin 131  eTP17  
     SIU.PCR[SIU_GPIO_CHANNEL_131] =SIU_INITIAL_PCR_131 ;
	// GPIO Pin 132  eTPU18  
     SIU.PCR[SIU_GPIO_CHANNEL_132] =SIU_INITIAL_PCR_132 ;
	// GPIO Pin 133 eTPU19  
     SIU.PCR[SIU_GPIO_CHANNEL_133] =SIU_INITIAL_PCR_133 ;
	  // GPIO Pin 134  eTPU20  
     SIU.PCR[SIU_GPIO_CHANNEL_134] =SIU_INITIAL_PCR_134 ;
	 // GPIO Pin 135 eTPU21  
     SIU.PCR[SIU_GPIO_CHANNEL_135] =SIU_INITIAL_PCR_135 ;
	// GPIO Pin 136  eTPU22  
     SIU.PCR[SIU_GPIO_CHANNEL_136] =SIU_INITIAL_PCR_136 ;
	// GPIO Pin 137 eTPU23 
     SIU.PCR[SIU_GPIO_CHANNEL_137] =SIU_INITIAL_PCR_137 ;
	 // GPIO Pin 138 eTPU24  
     SIU.PCR[SIU_GPIO_CHANNEL_138] =SIU_INITIAL_PCR_138 ;
	 // GPIO Pin 139  eTPU25 
     SIU.PCR[SIU_GPIO_CHANNEL_139] =SIU_INITIAL_PCR_139 ;
	 // GPIO Pin 140  eTPU26  
     SIU.PCR[SIU_GPIO_CHANNEL_140] =SIU_INITIAL_PCR_140 ;
	// GPIO Pin 141 eTPU27  
     SIU.PCR[SIU_GPIO_CHANNEL_141] =SIU_INITIAL_PCR_141 ;
	 // GPIO Pin 142  eTPU28  
     SIU.PCR[SIU_GPIO_CHANNEL_142] =SIU_INITIAL_PCR_142 ;
	// GPIO Pin 143  eTPU29  
     SIU.PCR[SIU_GPIO_CHANNEL_143] =SIU_INITIAL_PCR_143 ;
      // GPIO Pin 144  eTPU30  
     SIU.PCR[SIU_GPIO_CHANNEL_144] =SIU_INITIAL_PCR_144 ;
	// GPIO Pin 145  eTPU31  
     SIU.PCR[SIU_GPIO_CHANNEL_145] =SIU_INITIAL_PCR_145 ;


      //eMISO
      // GPIO Pin 179  EMIOS00
     SIU.PCR[SIU_GPIO_CHANNEL_179] =SIU_INITIAL_PCR_179 ;
     // GPIO Pin 180  emios 01  not pin in 144 package
     //SIU.PCR[SIU_GPIO_CHANNEL_180] =SIU_INITIAL_PCR_180 ;
     // GPIO Pin 181 EMIOS02
     SIU.PCR[SIU_GPIO_CHANNEL_181] =SIU_INITIAL_PCR_181;
     // GPIO Pin 183  EMIOS04  
     SIU.PCR[SIU_GPIO_CHANNEL_183] =SIU_INITIAL_PCR_183;
     // GPIO Pin 187  EMIOS08  
     SIU.PCR[SIU_GPIO_CHANNEL_187] =SIU_INITIAL_PCR_187;
     // GPIO Pin 188  EMIOS09  
     SIU.PCR[SIU_GPIO_CHANNEL_188] =SIU_INITIAL_PCR_188;
     // GPIO Pin 189  EMIOS10
     SIU.PCR[SIU_GPIO_CHANNEL_189] =SIU_INITIAL_PCR_189;
     // GPIO Pin 190  EMIOS11
     SIU.PCR[SIU_GPIO_CHANNEL_190] =SIU_INITIAL_PCR_190;
    // GPIO Pin 191  EMIOS12
     SIU.PCR[SIU_GPIO_CHANNEL_191] =SIU_INITIAL_PCR_191;
    // GPIO Pin 192  eMIOS[13]  not pin in 144 package
    // SIU.PCR[SIU_GPIO_CHANNEL_192] =SIU_INITIAL_PCR_192;
    // GPIO Pin 193  EMIOS14
     SIU.PCR[SIU_GPIO_CHANNEL_193] =SIU_INITIAL_PCR_193;
    // GPIO Pin 194  eMIOS[15]  not pin in 144 package
    // SIU.PCR[SIU_GPIO_CHANNEL_194] =SIU_INITIAL_PCR_194;
    // GPIO Pin 202  EMIOS23
     SIU.PCR[SIU_GPIO_CHANNEL_202] =SIU_INITIAL_PCR_202;


        // LCI&Prod for  GPIO 219
      //SIU.PCR[SIU_GPIO_CHANNEL_219] =SIU_INITIAL_PCR_219 ;
       
     if(CPU_Info == CPU_LCI)
     {
        // LCI for  GPIO 219
       // SIU.PCR[SIU_GPIO_CHANNEL_219] =SIU_INITIAL_PCR_219 ;
	 //  LCI for GPIO 220
        SIU.PCR[SIU_GPIO_CHANNEL_180] =SIU_INITIAL_PCR_180_LCI ;
         // LCI for  GPIO 221
        SIU.PCR[SIU_GPIO_CHANNEL_192] =SIU_INITIAL_PCR_192_LCI ;
	  // LCI for  GPIO 222
        SIU.PCR[SIU_GPIO_CHANNEL_194] =SIU_INITIAL_PCR_194_LCI ;
	  // LCI for  GPIO 223
        SIU.PCR[SIU_GPIO_CHANNEL_RESERVED_80] =SIU_INITIAL_PCR_80_LCI ;
	  // LCI for  GPIO 224
        SIU.PCR[SIU_GPIO_CHANNEL_RESERVED_81] =SIU_INITIAL_PCR_81_LCI ;
	  //  LCI for GPIO 225
        SIU.PCR[SIU_GPIO_CHANNEL_RESERVED_82] =SIU_INITIAL_PCR_82_LCI ;
	  // LCI for  GPIO 227
        SIU.PCR[SIU_GPIO_CHANNEL_99] =SIU_INITIAL_PCR_99_LCI ;
        // LCI for GPIO231
        SIU.PCR[SIU_GPIO_CHANNEL_98] =SIU_INITIAL_PCR_98_LCI ;
     }	
     else
     {
  	 // GPIO 219
       // SIU.PCR[SIU_GPIO_CHANNEL_219] =SIU_INITIAL_PCR_219 ;
	 // GPIO 220
        SIU.PCR[SIU_GPIO_CHANNEL_220] =SIU_INITIAL_PCR_220 ;
         // GPIO 221
        SIU.PCR[SIU_GPIO_CHANNEL_221] =SIU_INITIAL_PCR_221 ;
	  // GPIO 222
        SIU.PCR[SIU_GPIO_CHANNEL_222] =SIU_INITIAL_PCR_222 ;
	  // GPIO 223
        SIU.PCR[SIU_GPIO_CHANNEL_223] =SIU_INITIAL_PCR_223 ;
	  // GPIO 224
        SIU.PCR[SIU_GPIO_CHANNEL_224] =SIU_INITIAL_PCR_224 ;
	  // GPIO 225
        SIU.PCR[SIU_GPIO_CHANNEL_225] =SIU_INITIAL_PCR_225 ;
	  // GPIO 227
        SIU.PCR[SIU_GPIO_CHANNEL_227] =SIU_INITIAL_PCR_227 ;
	 // GPIO 231
        SIU.PCR[SIU_GPIO_CHANNEL_231] =SIU_INITIAL_PCR_231 ;
     }	 



 

    // configure for DSPI DSI mode
    //=============================================================================
    // SIU_GPIO_382 - EMIOS12
    //=============================================================================
    // SIU.PCR[SIU_GPIO_CHANNEL_382] =  SIU_INITIAL_PCR_382;

    //=============================================================================
    // SIU_GPIO_383 - ETPU13
    //=============================================================================

    //  SIU.PCR[SIU_GPIO_CHANNEL_383]  = SIU_INITIAL_PCR_383;


    //=============================================================================
    // SIU_GPIO_384 - EMIOS14
   //=============================================================================
   //   SIU.PCR[SIU_GPIO_CHANNEL_384]  = SIU_INITIAL_PCR_384;


    //=============================================================================
    // SIU_GPIO_385 - EMIOS15
    //=============================================================================
    //  SIU.PCR[SIU_GPIO_CHANNEL_385] =  SIU_INITIAL_PCR_385;
    //=============================================================================
    // SIU_GPIO_386 - EMIOS23
    //=============================================================================
   //   SIU.PCR[SIU_GPIO_CHANNEL_386] =  SIU_INITIAL_PCR_386 ;

    //=============================================================================
    // SIU_GPIO_387 - EMIOS00
    //=============================================================================
     // SIU.PCR[SIU_GPIO_CHANNEL_387] = SIU_INITIAL_PCR_387;

   //=============================================================================
   // SIU_GPIO_388 - ETPU02
    //=============================================================================

    //  SIU.PCR[SIU_GPIO_CHANNEL_388] = SIU_INITIAL_PCR_388 ;

    //=============================================================================
    // SIU_GPIO_389 - ETPU03
   //=============================================================================
     // SIU.PCR[SIU_GPIO_CHANNEL_389] = SIU_INITIAL_PCR_389;


    //=============================================================================
    // SIU_GPIO_390 - ETPU04
    //=============================================================================
   //   SIU.PCR[SIU_GPIO_CHANNEL_390] = SIU_INITIAL_PCR_390;

   //=============================================================================
   // SIU_GPIO_391 - GPIO
  //=============================================================================
   //   SIU.PCR[SIU_GPIO_CHANNEL_391] = SIU_INITIAL_PCR_391;

  //=============================================================================
  // SIU_GPIO_392 - GPIO
  //=============================================================================
    //  SIU.PCR[SIU_GPIO_CHANNEL_392] = SIU_INITIAL_PCR_392 ;


  //=============================================================================
  // SIU_GPIO_393 - GPIO
  //=============================================================================
   //   SIU.PCR[SIU_GPIO_CHANNEL_393] =SIU_INITIAL_PCR_393 ;


  //=============================================================================
  // SIU_GPIO_394 - GPIO
  //=============================================================================
  //    SIU.PCR[SIU_GPIO_CHANNEL_394] = SIU_INITIAL_PCR_394;


 //=============================================================================
 // SIU_GPIO_395 - GPIO
 //=============================================================================
    //  SIU.PCR[SIU_GPIO_CHANNEL_395] = SIU_INITIAL_PCR_395;


  //=============================================================================
  // SIU_GPIO_396 - EMIOS10
  //=============================================================================
   //   SIU.PCR[SIU_GPIO_CHANNEL_396] = SIU_INITIAL_PCR_396;

 //=============================================================================
 // SIU_GPIO_397 - GPIO
 //=============================================================================
   //   SIU.PCR[SIU_GPIO_CHANNEL_397] =SIU_INITIAL_PCR_397;

    
	
 }


//=============================================================================
// SIU_GPIO_DISCRETE_Set_State
//=============================================================================
 void SIU_GPIO_DISCRETE_Set_State(
   SIU_GPIO_Channel_T channel,
   bool                 in_state )
{
   SIU.GPDO[channel].F.PDO = in_state;
}

//=============================================================================
// SIU_GPIO_DISCRETE_Get_State_Local
//=============================================================================
 bool SIU_GPIO_DISCRETE_Get_State(SIU_GPIO_Channel_T channel )
{

   // get the current value
  // The SIU_GPDIx_x registers are read-only registers that allow software to read the input state of an external
  //GPIO pin. Each byte of a register represents the input state of a single external GPIO pin. If the GPIO pin
  //is configured as an output, and the input buffer enable (IBE) bit is set in the associated Pad Configuration
  //Register, the SIU_GPDIx_x register reflects the actual state of the output pin.
  // channel_state = SIU.GPDI[channel].F.PDI;

 if(SIU.PCR[channel].F.OBE)
 {
     return SIU.GPDO[channel].F.PDO; 
 }
 else
 {
    return SIU.GPDI[channel].F.PDI; 
 }	
	 
}


//#define  SIU_GPIO_DISCRETE_Get_State( ch )  (SIU.GPDI[siu_ch].F.PDI)
//=============================================================================
// SIU_GPIO_DISCRETE_Toggle_State
//=============================================================================
 void SIU_GPIO_DISCRETE_Toggle_State(SIU_GPIO_Channel_T channel )
{
   // Get the current state of the output pin and toggle
   bool state = ( SIU_GPIO_DISCRETE_Get_State( channel ) == false ) ? true : false;

   // Set output to the toggled state
   SIU_GPIO_DISCRETE_Set_State( channel, state );
}


//=============================================================================
// SIU_GPIO_DISCRETE_Get_State_Local
//=============================================================================
 void SIU_GPIO_Output_Confige(SIU_GPIO_Channel_T channel, bool enable )
{

      if(enable)
      {
      SIU.PCR[channel].F.IBE =false;
      SIU.PCR[channel].F.OBE = true;
      }
      else
 	{
 	  SIU.PCR[channel].F.IBE =true;
        SIU.PCR[channel].F.OBE = false;
 	}
}


