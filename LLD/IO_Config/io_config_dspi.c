
#include "io_config_dspi.h"
#include "dd_dspi.h"

//=============================================================================
// Initialization Constants for Module Control Register (MCR)
// Field definitions:
//=============================================================================

const DSPI_MCR_T    DSPI_B_MCR_INIT =
{
   //Master/Slave Mode Select
   DSPI_DEVICE_TYPE_MASTER,  // bitfield32_t  MSTR      :  BIT_1;  // Bit      31
   //Continuous SCK Enable
   false,                                     //bitfield32_t  CONT_SCKE :  BIT_1;  // Bit      30
   //DSPI Configuration
   DSPI_MCR_DCONF_SPI,          //bitfield32_t  DCONF     :  BIT_2;  // Bits [29:28]
   //Freeze
   false,                                     //bitfield32_t  FRZ       :  BIT_1;  // Bit      27
   //Modified Timing Format Enable
   false,                                     //bitfield32_t  MTFE      :  BIT_1;  // Bit      26
   //Peripheral Chip Select Strobe Enable
   false,                                      //bitfield32_t  PCSSE     :  BIT_1;  // Bit      25
   //Receive FIFO Overflow Overwrite Enable
   true,                                       // bitfield32_t  ROOE      :  BIT_1;  // Bit      24
   //Peripheral Chip Select Inactive State
   0x3F,                                      //bitfield32_t  PCSISx    :  BIT_8;  // Bits [21:16]
   //Doze Enable
   false,                                       //bitfield32_t  DOZE      :  BIT_1;  // Bit      15
   //Module Disable
   false,                                       //bitfield32_t  MDIS      :  BIT_1;  // Bit      14
   //Disable Transmit FIFO
   false,                                        //bitfield32_t  DIS_TXF   :  BIT_1;  // Bit      13
   //Disable Receive FIFO
   false,                                       //bitfield32_t  DIS_RXF   :  BIT_1;  // Bit      12
   //Clear TX FIFO
   true,                                       //bitfield32_t  CLR_TXF   :  BIT_1;  // Bit      11
   //Clear RX FIFO
   true,                                       //bitfield32_t  CLR_RXF   :  BIT_1;  // Bit      10
   //SMPL_PT field controls when the DSPI master samples SIN in Modified Transfer Format
   DSPI_MCR_SMPL_PT_0,           //bitfield32_t  SMPL_PT   :  BIT_2;  // Bits [ 9: 8]
   //Fast Continuous PCS Mode
   DSPI_CONT_SCK_DISABLE,      //bitfield32_t  FCPCS :  BIT_1;  // Bit       2
   //PES bit controls SPI operation when a parity error detected in received SPI frame.
   false,                                            //bitfield32_t    PES       :  BIT_1;  // Bit       1
   //The HALT bit starts and stops DSPI transfers
   true                                         //bitfield32_t  HALT      :  BIT_1;  // Bit       0

};

//=============================================================================
// Initialization Constants for Module Control Register (MCR)
// Field definitions:
//=============================================================================

const DSPI_MCR_T    DSPI_C_MCR_INIT =
{
   //Master/Slave Mode Select
   DSPI_DEVICE_TYPE_MASTER,  // bitfield32_t  MSTR      :  BIT_1;  // Bit      31
   //Continuous SCK Enable
   false,                                     //bitfield32_t  CONT_SCKE :  BIT_1;  // Bit      30
   //DSPI Configuration
   DSPI_MCR_DCONF_DSI,          //bitfield32_t  DCONF     :  BIT_2;  // Bits [29:28]
   //Freeze
   false,                                     //bitfield32_t  FRZ       :  BIT_1;  // Bit      27
   //Modified Timing Format Enable
   false,                                     //bitfield32_t  MTFE      :  BIT_1;  // Bit      26
   //Peripheral Chip Select Strobe Enable
   false,                                      //bitfield32_t  PCSSE     :  BIT_1;  // Bit      25
   //Receive FIFO Overflow Overwrite Enable
   true,                                       // bitfield32_t  ROOE      :  BIT_1;  // Bit      24
   //Peripheral Chip Select Inactive State
   0x3F,                                      //bitfield32_t  PCSISx    :  BIT_8;  // Bits [21:16]
   //Doze Enable
   false,                                       //bitfield32_t  DOZE      :  BIT_1;  // Bit      15
   //Module Disable
   false,                                       //bitfield32_t  MDIS      :  BIT_1;  // Bit      14
   //Disable Transmit FIFO
   false,                                        //bitfield32_t  DIS_TXF   :  BIT_1;  // Bit      13
   //Disable Receive FIFO
   false,                                       //bitfield32_t  DIS_RXF   :  BIT_1;  // Bit      12
   //Clear TX FIFO
   true,                                       //bitfield32_t  CLR_TXF   :  BIT_1;  // Bit      11
   //Clear RX FIFO
   true,                                       //bitfield32_t  CLR_RXF   :  BIT_1;  // Bit      10
   //SMPL_PT field controls when the DSPI master samples SIN in Modified Transfer Format
   DSPI_MCR_SMPL_PT_0,           //bitfield32_t  SMPL_PT   :  BIT_2;  // Bits [ 9: 8]
   //Fast Continuous PCS Mode
   DSPI_CONT_SCK_DISABLE,      //bitfield32_t  FCPCS :  BIT_1;  // Bit       2
   //PES bit controls SPI operation when a parity error detected in received SPI frame.
   false,                                            //bitfield32_t    PES       :  BIT_1;  // Bit       1
   //The HALT bit starts and stops DSPI transfers
   true                                         //bitfield32_t  HALT      :  BIT_1;  // Bit       0

};

//=============================================================================
// Initialization Clock and Transfer Attribute Register (CTAR)
// Field definitions:
//=============================================================================
//=======================================================================================
//  The CTAR values are changed dynamically based on message parameters
//  The prescaler values are fixed and are to be put in io_scale.h
//  The LSB first attribute is not part of message parameters and hence must be set 
//  correctly here. 
//
//  SCK baud rate = fSYS * (1 + DBR) / (PBR * BR)
//
//======================================================================================

//=======================================================================================
// DSPI_B_CTAR_0_VSEP
//=======================================================================================
const DSPI_CTAR_T   DSPI_B_CTAR0_INIT=
{
       DSPI_CTAR_DBR_DISABLE,    //Double Baud Rate 
       DSPI_CTAR_FMSZ_16,            //Frame Size
       DSPI_CTAR_SCK_INACTIVE_STATE_LO, //Clock Polarity
       DSPI_CTAR_SCK_PHASE_LEADING_EDGE, //Clock Phase
       false, //MSB First
       DSPI_CTAR_PCSSCK_1, //PCS to SCK Delay Prescaler
       DSPI_CTAR_PASC_1,   //After SCK Delay Prescaler
       DSPI_CTAR_PDT_1, //Delay after Transfer Prescaler
       DSPI_CTAR_PBR_5, //Baud Rate Prescaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_64, //PCS to SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_64, //After SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_8, //Delay after Transfer Scaler
       DSPI_CTAR_BR_SCALER_4    //Baud Rate Scaler

};


//=======================================================================================
// DSPI_B_CTAR_1_PHD
//=======================================================================================

const DSPI_CTAR_T   DSPI_B_CTAR1_INIT=
{
       DSPI_CTAR_DBR_DISABLE,    //Double Baud Rate 
       DSPI_CTAR_FMSZ_16,            //Frame Size
       DSPI_CTAR_SCK_INACTIVE_STATE_LO, //Clock Polarity
       DSPI_CTAR_SCK_PHASE_FALLING_EDGE, //Clock Phase
       true, //LSB First
       DSPI_CTAR_PCSSCK_1, //PCS to SCK Delay Prescaler
       DSPI_CTAR_PASC_1,   //After SCK Delay Prescaler
       DSPI_CTAR_PDT_1, //Delay after Transfer Prescaler
       DSPI_CTAR_PBR_5, //Baud Rate Prescaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_16, //PCS to SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_8, //After SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_8, //Delay after Transfer Scaler
       DSPI_CTAR_BR_SCALER_4    //Baud Rate Scaler

};

//=======================================================================================
// DSPI_B_CTAR_2_KP254
//=======================================================================================

const DSPI_CTAR_T   DSPI_B_CTAR2_INIT=
{
       DSPI_CTAR_DBR_ENABLE,    //Double Baud Rate 
       DSPI_CTAR_FMSZ_8,            //Frame Size
       DSPI_CTAR_SCK_INACTIVE_STATE_LO, //Clock Polarity
       DSPI_CTAR_SCK_PHASE_FALLING_EDGE, //Clock Phase
       false, //LSB First
       DSPI_CTAR_PCSSCK_3, //PCS to SCK Delay Prescaler
       DSPI_CTAR_PASC_3,   //After SCK Delay Prescaler
       DSPI_CTAR_PDT_1, //Delay after Transfer Prescaler
       DSPI_CTAR_PBR_5, //Baud Rate Prescaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_16, //PCS to SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_4, //After SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_256, //Delay after Transfer Scaler
       DSPI_CTAR_BR_SCALER_6    //Baud Rate Scaler

};

//=======================================================================================
// DSPI_B_CTAR_3_C2PS
//=======================================================================================
/*const DSPI_CTAR_T   DSPI_B_CTAR3_INIT=
{
       DSPI_CTAR_DBR_ENABLE,    //Double Baud Rate 
       DSPI_CTAR_FMSZ_16,            //Frame Size
       DSPI_CTAR_SCK_INACTIVE_STATE_LO, //Clock Polarity
       DSPI_CTAR_SCK_PHASE_FALLING_EDGE, //Clock Phase
       false, //LSB First
       DSPI_CTAR_PCSSCK_1, //PCS to SCK Delay Prescaler
       DSPI_CTAR_PASC_3,   //After SCK Delay Prescaler
       DSPI_CTAR_PDT_7, //Delay after Transfer Prescaler
       DSPI_CTAR_PBR_7, //Baud Rate Prescaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_16, //PCS to SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_16, //After SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_32, //Delay after Transfer Scaler
       DSPI_CTAR_BR_SCALER_6    //Baud Rate Scaler

};
*/

//=======================================================================================
// DSPI_C_CTAR_0_ - 20M BPS
//=======================================================================================
const DSPI_CTAR_T   DSPI_C_CTAR0_INIT=
{
       DSPI_CTAR_DBR_DISABLE,    //Double Baud Rate 
       DSPI_CTAR_FMSZ_16,            //Frame Size
       DSPI_CTAR_SCK_INACTIVE_STATE_LO, //Clock Polarity
       DSPI_CTAR_SCK_PHASE_LEADING_EDGE, //Clock Phase
       false, //LSB First
       DSPI_CTAR_PCSSCK_1, //PCS to SCK Delay Prescaler
       DSPI_CTAR_PASC_1,   //After SCK Delay Prescaler
       DSPI_CTAR_PDT_1, //Delay after Transfer Prescaler
       DSPI_CTAR_PBR_2, //Baud Rate Prescaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_16, //PCS to SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_16, //After SCK Delay Scaler
       DSPI_CTAR_CSSCK_DT_ASC_SCALER_2, //Delay after Transfer Scaler
       DSPI_CTAR_BR_SCALER_2    //Baud Rate Scaler
};

//=============================================================================
// Initialization Constants for DMA/Interrupt Select and Enable (DSPIx_RSER)
//=============================================================================

const DSPI_RSER_T   DSPI_B_RSER_INIT =
{
          //The TCF_RE bit enables TCF flag in the DSPI_SR to generate an interrupt request.
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//TCF_RE 
          //DSI Frame Transmission Complete Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//DSITCF_RE 
          //DSPI Finished Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//EOQF_RE 
          //Transmit FIFO Underflow Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//TFUF_RE
         //SPI Frame Transmission Complete Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_DISABLE, //SPITCF_RE
         //Transmit FIFO Fill Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_ENABLE,//TFFF_RE
         //Transmit FIFO Fill DMA or Interrupt Request Select
         DSPI_RX_FIFO_DRAIN_REQUEST_DMA,//TFFF_DIRS
         //DSI Parity Error Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//DPEF_RE
          //SPI Parity Error Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//SPEF_RE
          //DSI data received with active bits Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//DDIF_RE
         //DSPI_INTERRUPT_DMA_REQUEST_DISABLE
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//RFOF_RE
          //Receive FIFO Drain Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//RFDF_RE
      //Receive FIFO Drain DMA or Interrupt Request Select
        DSPI_RX_FIFO_DRAIN_REQUEST_DMA//RFDF_DIRS

};

//=============================================================================
// Initialization Constants for DMA/Interrupt Select and Enable (DSPIx_RSER)
//=============================================================================

const DSPI_RSER_T   DSPI_C_RSER_INIT =
{
          //The TCF_RE bit enables TCF flag in the DSPI_SR to generate an interrupt request.
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//TCF_RE 
          //DSI Frame Transmission Complete Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//DSITCF_RE 
          //DSPI Finished Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//EOQF_RE 
          //Transmit FIFO Underflow Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//TFUF_RE
         //SPI Frame Transmission Complete Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//SPITCF_RE
         //Transmit FIFO Fill Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_ENABLE,//TFFF_RE
         //Transmit FIFO Fill DMA or Interrupt Request Select
         DSPI_RX_FIFO_DRAIN_REQUEST_DMA,//TFFF_DIRS
         //DSI Parity Error Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//DPEF_RE
          //SPI Parity Error Request Enable
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//SPEF_RE
          //DSI data received with active bits Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//DDIF_RE
         //DSPI_INTERRUPT_DMA_REQUEST_DISABLE
          DSPI_INTERRUPT_DMA_REQUEST_DISABLE,//RFOF_RE
          //Receive FIFO Drain Request Enable
         DSPI_INTERRUPT_DMA_REQUEST_ENABLE,//RFDF_RE
      //Receive FIFO Drain DMA or Interrupt Request Select
        DSPI_RX_FIFO_DRAIN_REQUEST_DMA//RFDF_DIRS

};

//=============================================================================
// Initialization Constants for DSPI DSI Configuration Register (DSPIx_DISCR)
//=============================================================================
const DSPI_DSICR_T  DSPIC_DSICR_INIT =
{

      //Multiple Transfer Operation Enable
      false,//MTOE
      //MSB of the Frame Size in master mode
      0,                                                               //FMSZ
      //Multiple Transfer Operation Count
      0,//MTOCNT
      //Trigger Source for Interleaved TSB mode
      0, // TRG
      //Interleaved TSB mode
      0,//ITSB
      //Timed Serial Bus Configuration
      DSPI_DSICR_TIMED_SERIAL_BUS_DISABLED,//TSBC
      //Transmit Data Source Select
      DSPI_DSICR_SOURCE_DATA_SDR,//TXSSS
      //Trigger Polarity
      DSPI_DSICR_TRIGGER_FALLING_EDGE,//TPOL
      //Trigger Reception Enable
      false,//TRRE
      //Change In Data Transfer Enable
      true,//CID
      //DSI Continuous Peripheral Chip Select Enable
      false,//CONT
      //DSI Clock and Transfer Attributes Select
      DSPI_PUSHR_DSICR_CTAS_CTAR0,//CTAS
      0,                                                               //DMS Data Match Stop
      0,                                                               //PES Parity Error Stop
      0,                                                               //PE Parity Enable
      0,                                                               //PP Parity Polarity
      //DSI Peripheral Chip Select 0¨C7
      //The DPCS bits select which of the PCS signals to assert during a DSI master mode transfer.
      1 //PCSx

};


