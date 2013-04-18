//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_config.c %
//
// created_by:       fz3pdz
//
// date_created:     Thu Apr 27 11:00:23 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Thu Nov  8 22:02:01 2007 %
//
// %version:         mt20u2#3 %
//
//=============================================================================

//#include "dd_config.h"
#include "io_config_spi.h"
//#include "dd_spi.h"
#include "dd_l9958.h"
#include "dd_l9958_fault.h"
#include "dd_l9958_txd.h"

#include "io_config_dma.h"
#include "io_config_dspi.h"
#include "dd_dspi_interface.h"

//=============================================================================
// Include the spi port
//=============================================================================
#include "spi_message.h"

//=============================================================================
// Local Types definition
//=============================================================================
typedef struct Fault_Diagnostic_Channel_Tag
{
   const IO_Configuration_T   L9958_config;
   bool                       is_parallel;
} Fault_Diagnostic_Channel_T;

//=============================================================================
//L9958 Peripheral Device Setup Parameters
//=============================================================================
const SPI_Peripheral_Device_Parameters_T L9958_PARAMS = 
{
   5,// Baud Rate 5Mhz, needs to be converted in terms of clock countL9958_0_SPBR,  // @field Baud Rate 
   16,//L9958_0_XFER,  // @field Data Width          
   0,//L9958_0_DSCKL, // @field Delay Before First Clock 
   0,//L9958_0_DTL,   // @field Delay After Message 
   SPI_MESSAGE_CLOCK_PHASE_LEADING_EDGE,//L9958_0_PHASE, // @field Clock Phasing  
   SPI_MESSAGE_CLOCK_POLARITY_ACTIVE_HIGH,//L9958_0_POL,   // @field Clock Polarity                   
 };

//=============================================================================
// L9958  Peripheral Device setup
//=============================================================================
const SPI_Peripheral_Device_T L9958[ NUMBER_OF_L9958 ] = 
{
   { 
      &L9958_PARAMS, 
      NULL,//&MTSA_SPI_CHANNEL_B,  
      NULL //&L9958_CHIP_SELECT[L9958_INDEX_0]
   }
};

//=============================================================================
// L9958 CFG_REG MESSAGE Data Descriptor
//=============================================================================
const SPI_Message_Data_Descriptor_T L9958_CFG_MESSAGE_DESCRIPTORS[ NUMBER_OF_L9958 ][ 1 ] =
{
   {
      { &L9958[ L9958_INDEX_0 ], false }
   }
};

//=============================================================================
// L9958 DIAG_REG Data Descriptor
//=============================================================================
const SPI_Message_Data_Descriptor_T L9958_DIAG_MESSAGE_DESCRIPTORS[ NUMBER_OF_L9958 ][ 1 ] =
{
   {
      { &L9958[ L9958_INDEX_0 ], false }
   }
};



//=============================================================================
// L9958 CFG_REG Message Defintion
//=============================================================================
const SPI_Message_Definition_T L9958_CFG_MESSAGE_DEFINITION[ NUMBER_OF_L9958 ] =
{
   { 
      //L9958_CFG_MESSAGE_DESCRIPTORS[ L9958_INDEX_0 ],
      &L9958_Rxd[ L9958_INDEX_0 ],
      &L9958_Txd[ L9958_INDEX_0 ],
      //SPI_MESSAGE_TYPE_MASTER,
      0,
      0,
      0
      //0,
      //sizeof( L9958_CFG_MESSAGE_DESCRIPTORS[ L9958_INDEX_0 ] ) / sizeof( SPI_Message_Data_Descriptor_T )
   }
};

//=============================================================================
// L9958 Diag Message Defintion
//=============================================================================
const SPI_Message_Definition_T L9958_DIAG_MESSAGE_DEFINITION[ NUMBER_OF_L9958 ] =
{
   { 
     // L9958_DIAG_MESSAGE_DESCRIPTORS[ L9958_INDEX_0 ],
      &L9958_Rxd[ L9958_INDEX_0 ],
      &L9958_Txd[ L9958_INDEX_0 ],
      //SPI_MESSAGE_TYPE_MASTER,
      0,
      0,
      0
      //0,
      //sizeof( L9958_DIAG_MESSAGE_DESCRIPTORS[ L9958_INDEX_0 ] ) / sizeof( SPI_Message_Data_Descriptor_T )
   }
};


static SPI_Message_Control_Block_T L9958_CFG_CB[ NUMBER_OF_L9958 ];
static SPI_Message_Control_Block_T L9958_DIAG_CB[ NUMBER_OF_L9958 ];

//=============================================================================
// L9958 GATE_SELECT Message
//=============================================================================
const SPI_Message_T L9958_CFG_MESSAGE[ NUMBER_OF_L9958 ] =
{ 
   { &L9958_CFG_MESSAGE_DEFINITION[ L9958_INDEX_0 ], &L9958_CFG_CB[ L9958_INDEX_0 ] }
};

//=============================================================================
// L9958 Diag Message
//=============================================================================
const SPI_Message_T L9958_DIAG_MESSAGE[ NUMBER_OF_L9958 ] =
{ 
   { &L9958_DIAG_MESSAGE_DEFINITION[ L9958_INDEX_0 ], &L9958_DIAG_CB[ L9958_INDEX_0 ] }
};

//=============================================================================
// L9958_SPI_Immediate_Transfer
//=============================================================================
void L9958_SPI_Immediate_Transfer( 
   IO_Configuration_T  in_configuration ,
   L9958_Txd_Message_T    in_msg_index)
{
L9958_Index_T index = L9958_Get_Device_Index( in_configuration );
interrupt_state_t     irq_state;
   uint8_t              transmint_length;

   irq_state = Get_Interrupt_State();
   Disable_Interrupts();

   L9958_Rxd[index] = 
			 	DSPI_B_Exchange_Data1(ETC_CHIP_SELECT,
			 	                                        ETC_CTAR_SELECT,
			 	                                         DSPI_CTAR_FMSZ_16,
                                                                     L9958_Txd[index],
                                                                     1);
   #if 0

   transmint_length = 1;
     while((DMA_Get_Channel_Running_Status(DMA_CHANNEL_DSPI_B_SR_RFDF)==true)||
	 	(DMA_Get_Channel_Running_Status(DMA_CHANNEL_DSPI_B_SR_TFFF)==true))
     	{
       //do nothing
     	}
     DMA_Clear_Request(DMA_CHANNEL_DSPI_B_SR_TFFF);
     DMA_Clear_Request(DMA_CHANNEL_DSPI_B_SR_RFDF);

     DSPI_B_Initialize_Message_16bits(ETC_CHIP_SELECT, ETC_CTAR_SELECT,
                                                    &(  L9958_Txd[index]),transmint_length);
	 
    DMA_Set_Channel_Transfer_Count( DMA_CHANNEL_DSPI_B_SR_TFFF,transmint_length);
    DMA_Set_Channel_Source_Address( DMA_CHANNEL_DSPI_B_SR_TFFF, DMA_DSPIB_SR_TFFF_Source_Address);
    //Clean up the DSPI module to be ready for next transfer
    DSPI_B_Clear_FIFO();
    //This flag will trigger the DMA channel for transmit
    DSPI_B_Clear_TCF();
	
    DMA_Enable_Request(DMA_CHANNEL_DSPI_B_SR_TFFF);
    DMA_Enable_Request(DMA_CHANNEL_DSPI_B_SR_RFDF);

     //This flag will start the SPI device transfer
     //Very important to clear the EOQF flag after DMA has been disabled.
     DSPI_B_Clear_EOQF();

     while(DMA_Get_Channel_Running_Status(DMA_CHANNEL_DSPI_B_SR_RFDF)==true)
     	{
       //do nothing
     	}
     
     DMA_Clear_Request(DMA_CHANNEL_DSPI_B_SR_TFFF);
     DMA_Clear_Request(DMA_CHANNEL_DSPI_B_SR_RFDF);

     DSPI_B_Copy_Receive_Data_16bits(& (  L9958_Rxd[index]),transmint_length);
#endif
   Set_Interrupt_State(irq_state) ;
}

//=============================================================================
// L9958 diagnostic channel
//=============================================================================
const Fault_Diagnostic_Channel_T L9958_SPI_FAULT_CHANNELS[NUMBER_OF_L9958][2] =
{
   {
      {0, true },
   }

};

//=============================================================================
// L9958_Fault_Diagnose_Channels
//=============================================================================
FAR_COS void L9958_Fault_Diagnose_Channels( IO_Configuration_T in_configuration )
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );
   uint8_t x;

   L9958_Diag_Rst_Disable_Set(in_configuration, L9958_DIAG_RST_DISABLE_TRUE);
   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_DIAG_REG );

   for( x = 0; x < (sizeof( L9958_SPI_FAULT_CHANNELS )/sizeof(Fault_Diagnostic_Channel_T ))/NUMBER_OF_L9958; x++ )
   {
      L9958_FAULT_Diagnose_Fault(  
              L9958_SPI_FAULT_CHANNELS[index][x].L9958_config, 
              L9958_SPI_FAULT_CHANNELS[index][x].is_parallel );
   }
}


/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 *
 * 03/30/09     sjl         mt20u2#304
 * + MT22.1: RSM_CTC_0129_Add ESC integral signal DA output_Rev1_20090227
 *   - Modified L9958_SPI_Immediate_Transfer as a result of revised SPI driver
 *
\* ============================================================================ */

