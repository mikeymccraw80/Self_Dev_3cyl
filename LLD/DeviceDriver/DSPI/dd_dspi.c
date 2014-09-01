#include "dd_dspi.h"
#include "io_config_dspi.h"
#include "io_config_dma.h"
#include "dd_dma_interface.h"
#include "dd_stm_interface.h"

// DSPI_B
// @type DSPI_B | Handle to DSPI_B Registers
#define SECTION_DSPI_B_REGISTER
#include "section.h"
DSPI_T DSPI_B;
#define SECTION_END
#include "section.h"

// DSPI_C
// @type DSPI_C | Handle to DSPI_C Registers
#define SECTION_DSPI_C_REGISTER
#include "section.h"
DSPI_T DSPI_C;
#define SECTION_END
#include "section.h"

#define DSPI_TCF_EOQF_RFDF_CLEAR_FLAG (0xB587FFFF)

//define the max overtime period, unit is us
#define DSPI_EXCHANGE_TIME_MAX        (0x80)

//DMA buffer
uint16_t DSPI_SPI_Port_Rxd_B[ DSPI_SPI_PORT_DATA_LENGTH_INIT_B ];
uint32_t DSPI_SPI_Port_Txd_B[ DSPI_SPI_PORT_DATA_LENGTH_INIT_B ];

uint16_t *DSPI_Recevice_Pointer;
uint16_t    DSPI_Recevice_length;

void DSPI_B_Clear_FIFO(void);

//=============================================================================
// DSPI_B_Initialize_Device
//=============================================================================
void DSPI_B_Initialize_Device(void )
{

	//in case reinitalinze
	if( DSPI_B.MCR.F.MDIS == 0 ) {
		DSPI_B.MCR.F.HALT = 1;

		// Wait for DSPI to stop
		while( 1 == DSPI_B.SR.F.TXRXS ) {
			;
		}
	}

	DSPI_B.TCR.F.TCNT = 0;


//=============================================================================
// Initialization Constants for Module Control Register (MCR)
// Field definitions:
//=============================================================================

	DSPI_B.MCR.U32 = DSPI_B_MCR_INIT.U32;

//=============================================================================
// Initialization Constants for DMA/Interrupt Select and Enable (DSPIx_RSER)
//=============================================================================

	DSPI_B.RSER.U32 = DSPI_B_RSER_INIT.U32;


//=======================================================================================
// DSPI_B_CTAR_0
//=======================================================================================


	DSPI_B.CTAR[0].U32  =   DSPI_B_CTAR0_INIT.U32;

//=======================================================================================
// DSPI_B_CTAR_1_
//=======================================================================================

	DSPI_B.CTAR[1].U32  =   DSPI_B_CTAR1_INIT.U32;

//=======================================================================================
// DSPI_B_CTAR_2_
//=======================================================================================

	DSPI_B.CTAR[2].U32  =   DSPI_B_CTAR2_INIT.U32;

//=======================================================================================
// DSPI_B_CTAR_3_C2PS
//=======================================================================================

	//DSPI_B.CTAR[3].U32  =    DSPI_B_CTAR3_INIT.U32;

	DSPI_B_Clear_FIFO();
}


//=============================================================================
// DSPI_C_Initialize_Device
//=============================================================================
void DSPI_C_Initialize_Device(void )
{


//=============================================================================
// Initialization Constants for DMA/Interrupt Select and Enable (DSPIx_RSER)
//=============================================================================

	DSPI_C.RSER.U32 = DSPI_C_RSER_INIT.U32;

//=============================================================================
// Initialization Constants for Module Control Register (MCR)
// Field definitions:
//=============================================================================

	DSPI_C.MCR.U32 = DSPI_C_MCR_INIT.U32;

//=======================================================================================
// DSPI_C_CTAR_0_ - 20M BPS
//=======================================================================================
	DSPI_C.CTAR[0].U32  =   DSPI_C_CTAR0_INIT.U32;

//========================================================================
// Initialize SIU DISR
//========================================================================
	DSPI_C.DSICR.U32 =DSPIC_DSICR_INIT.U32;

	DSPI_C.SR.U32 = -1;

}


//============================================================================
// DSPI_Enable_Transfer
//============================================================================
void DSPI_B_Enable_Transfer (bool   in_enable )
{

	DSPI_B.MCR.F.HALT = ((in_enable) ? false : true );
}

//============================================================================
// DSPI_Enable_Transfer
//============================================================================
void DSPI_C_Enable_Transfer (bool   in_enable )
{

	DSPI_C.MCR.F.HALT = ((in_enable) ? false : true );
}


//=============================================================================
// DSPIPort_Initialize_Message -DMA
//=============================================================================
void DSPI_B_Initialize_Message_16bits(
        DSPI_CS_T                in_cs_select,
        DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
        uint16_t        *in_tx_data_buffer,
        uint8_t                       in_transmit_count  )
{
	uint8_t index;
	DSPI_PUSHR_T tx_data_buffer;
	uint32_t *transmit_buffer = DSPI_SPI_Port_Txd_B;

	tx_data_buffer.U32 = 0;
	tx_data_buffer.F.PCSx = 1<<in_cs_select;
	tx_data_buffer.F.CTAS  = in_ctar_msg;
	tx_data_buffer.F.CONT = true;
	tx_data_buffer.F.EOQ = 0;
	DSPI_B.CTAR[in_ctar_msg].F.FMSZ = 15;
	for( index = 0; index < in_transmit_count; index++ ) {

		if(index == (in_transmit_count-1)	) {
			tx_data_buffer.F.CONT = false;
			tx_data_buffer.F.CTCNT= true;
			tx_data_buffer.F.EOQ =true;
		}
		*transmit_buffer++ = tx_data_buffer.U32 | *in_tx_data_buffer++;
		tx_data_buffer.F.TXDATA= 0;
	}

}

//=============================================================================
// DSPIPort_Initialize_Message-DMA
//=============================================================================
void DSPI_B_Initialize_Message_8bits(
        DSPI_CS_T                in_cs_select,
        DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
        uint8_t        *in_tx_data_buffer,
        uint8_t                       in_transmit_count  )
{
	uint8_t index;
	DSPI_PUSHR_T tx_data_buffer;
	uint32_t *transmit_buffer = DSPI_SPI_Port_Txd_B;

	tx_data_buffer.U32 = 0;
	tx_data_buffer.F.PCSx = 1<<in_cs_select;
	tx_data_buffer.F.CTAS  = in_ctar_msg;
	tx_data_buffer.F.CONT = true;
	tx_data_buffer.F.EOQ = 0;
	DSPI_B.CTAR[in_ctar_msg].F.FMSZ = 7;
	for( index = 0; index < in_transmit_count; index++ ) {

		if(index == (in_transmit_count-1)	) {
			tx_data_buffer.F.CONT = false;
			tx_data_buffer.F.CTCNT= true;
			tx_data_buffer.F.EOQ =true;
		}
		*transmit_buffer++ = tx_data_buffer.U32 | *in_tx_data_buffer++;
		tx_data_buffer.F.TXDATA= 0;
	}

}


//=============================================================================
// DSPIPort_Copy_Transmit_Data-DMA
//=============================================================================
void DSPI_B_Copy_Receive_Data_16bits(
        uint16_t       *in_rx_data_buffer,
        uint16_t                       in_receive_count)
{
	uint8_t index;
	uint16_t *receive_buffer = DSPI_SPI_Port_Rxd_B;

	for( index = 0; index < in_receive_count; index++ ) {
		*in_rx_data_buffer++ = *receive_buffer++;
	}

}

//=============================================================================
// DSPIPort_Copy_Transmit_Data-DMA
//=============================================================================
void DSPI_B_Copy_Receive_Data_8bits(
        uint8_t           *in_rx_data_buffer,
        uint8_t                       in_receive_count)
{
	uint8_t index;
	uint16_t *receive_buffer = DSPI_SPI_Port_Rxd_B;

	for( index = 0; index < in_receive_count; index++ ) {
		*in_rx_data_buffer++ = (uint8_t)*receive_buffer++;
	}

}


//=============================================================================
// DSPI_B_Clear_FIFO-DMA
//=============================================================================
void DSPI_B_Clear_FIFO(void)
{
	//Clean up the DSPI module to be ready for next transfer
	DSPI_B.MCR.F.CLR_TXF = 1;
	DSPI_B.MCR.F.CLR_RXF = 1;
}

//=============================================================================
// DSPI_B_Exchange_Data
//=============================================================================
void   DSPI_B_Exchange_Data(
        DSPI_CS_T                in_cs_select,
        DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
        DSPI_CTAR_FMSZ_T FMSize,
        uint16_t       * in_tx_data,
        uint16_t       * in_rx_data,
        uint16_t    Transmit_size)
{



	uint16_t  return_data;
	uint32_t   ssr_reg_value;
	uint8_t index;
	DSPI_PUSHR_T tx_data_buffer;

	tx_data_buffer.U32 = 0;
	tx_data_buffer.F.PCSx = 1<<in_cs_select;
	tx_data_buffer.F.CTAS  = in_ctar_msg;
	tx_data_buffer.F.CONT = true;
	tx_data_buffer.F.EOQ = 0;

	DSPI_B.CTAR[in_ctar_msg].F.FMSZ ;

	DSPI_B.SR.U32 = 0x90020000;

	//Enable DSPI Transfers
//  DSPI_B.MCR.F.HALT = 0;
	//This flag will trigger the DMA channel for transmit
	//DSPI_Clear_Device_Status(dspi, DSPI_INTERRUPT_TX_COMPLETE);
	//  ssr_reg_value = DSPI_B.SR.U32 ;
	//  ssr_reg_value = (ssr_reg_value & DSPI_TCF_CLEAR_MASK);
	//   DSPI_B.SR.U32 = ssr_reg_value;

	for(index=0; index<Transmit_size-1; index++) {

		tx_data_buffer.U32 = tx_data_buffer.U32| (uint16_t)*in_tx_data;
		while(DSPI_B.SR.F.TFFF==0) {
		}
		DSPI_B.PUSHR.U32 = tx_data_buffer.U32;
		tx_data_buffer.F.TXDATA = 0;
		in_tx_data++;
	}

	tx_data_buffer.F.CONT = false;
	tx_data_buffer.F.CTCNT= true;
	tx_data_buffer.F.EOQ = 1;
	tx_data_buffer.U32 = tx_data_buffer.U32| (uint16_t)*in_tx_data;
	while(DSPI_B.SR.F.TFFF==0) {
	}
	DSPI_B.PUSHR.U32 = tx_data_buffer.U32;

	while(DSPI_B.SR.F.EOQF!=1) {
		//wait for SPI return data
	}

	for(index=0; index<Transmit_size; index++) {
		while(DSPI_B.SR.F.RFDF==1) {

			*in_rx_data++ = (uint16_t)DSPI_B.POPR.F.RXDATA;
		}
	}



	DSPI_B.SR.U32 = 0x90020000;
	//This flag will start the SPI device transfer
	//Very important to clear the EOQF flag after DMA has been disabled.
//   DSPI_Clear_Device_Status(dspi, DSPI_INTERRUPT_DSPI_FINISHED);
	//   ssr_reg_value = DSPI_B.SR.U32 ;
	//   ssr_reg_value = (ssr_reg_value & DSPI_EOQF_CLEAR_MASK);
	//    DSPI_B.SR.U32 = ssr_reg_value;


//clear EOQF, TCF and RFDF
//ssr_reg_value.U32 = DSPI_B.SR.U32;
// reg_value = (reg_value & DSPI_EOQF_CLEAR_MASK);
//reg_value = (reg_value & DSPI_TCF_CLEAR_MASK);
//reg_value = (reg_value & DSPI_RFDF_CLEAR_MASK);

//DSPI_B.SR.U32 = reg_value;
// DSPI_B.SR.U32 = 0x90020000;

	//Clean up the DSPI module to be ready for next transfer
	//DSPI_B.MCR.F.CLR_TXF = 1;
	//DSPI_B.MCR.F.CLR_RXF = 1;

// return return_data;

}

//=============================================================================
// DSPI_B_Exchange_Data
//=============================================================================
void   DSPI_B_Send_Data(
        DSPI_CS_T                in_cs_select,
        DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
        DSPI_CTAR_FMSZ_T FMSize,
        uint16_t       * in_tx_data,
        uint16_t    Transmit_size)
{

	// DSPI_PUSHR_T tx_data_buffer;
	// uint16_t  return_data;
//  uint32_t   reg_value;

	uint16_t  return_data;
	uint32_t   ssr_reg_value;
	uint8_t index;
	DSPI_PUSHR_T tx_data_buffer;

	tx_data_buffer.U32 = 0;
	tx_data_buffer.F.PCSx = 1<<in_cs_select;
	tx_data_buffer.F.CTAS  = in_ctar_msg;
	tx_data_buffer.F.EOQ = 0;

	DSPI_B.CTAR[in_ctar_msg].F.FMSZ ;


	//Enable DSPI Transfers
//  DSPI_B.MCR.F.HALT = 0;
	//This flag will trigger the DMA channel for transmit
	//DSPI_Clear_Device_Status(dspi, DSPI_INTERRUPT_TX_COMPLETE);
	//  ssr_reg_value = DSPI_B.SR.U32 ;
	//  ssr_reg_value = (ssr_reg_value & DSPI_TCF_CLEAR_MASK);
	//   DSPI_B.SR.U32 = ssr_reg_value;

	for(index=0; index<Transmit_size-1; index++) {

		tx_data_buffer.U32 = tx_data_buffer.U32| (uint16_t)*in_tx_data;
		DSPI_B.PUSHR.U32 = tx_data_buffer.U32;
		tx_data_buffer.F.TXDATA = 0;
		in_tx_data++;
	}


	tx_data_buffer.F.EOQ = 1;
	tx_data_buffer.U32 = tx_data_buffer.U32| (uint16_t)*in_tx_data;
	DSPI_B.PUSHR.U32 = tx_data_buffer.U32;

	while(DSPI_B.SR.F.EOQF!=1) {
		//wait for SPI return data
	}

	//for(index=0; index<Transmit_size-1; index++)
	//  {

	//    *in_rx_data++ = (uint16_t)DSPI_B.POPR.F.RXDATA;
	// }



	DSPI_B.SR.U32 = 0x90020000;


#if 0
	tx_data_buffer.U32 = 0;
	tx_data_buffer.F.PCSx = 1<<in_cs_select;
	tx_data_buffer.F.CTAS  = in_ctar_msg;
	tx_data_buffer.F.EOQ = 1;
	tx_data_buffer.U32 = tx_data_buffer.U32 | (uint16_t)in_tx_data;

	DSPI_B.CTAR[in_ctar_msg].F.FMSZ ;
	DSPI_B.PUSHR.U32 = tx_data_buffer.U32;

//clear EOQF, TCF and RFDF
//ssr_reg_value.U32 = DSPI_B.SR.U32;
// reg_value = (reg_value & DSPI_EOQF_CLEAR_MASK);
//reg_value = (reg_value & DSPI_TCF_CLEAR_MASK);
//reg_value = (reg_value & DSPI_RFDF_CLEAR_MASK);

//DSPI_B.SR.U32 = reg_value;
	DSPI_B.SR.U32 = 0x90020000;
//DSPI_B.SR.U32 = -1;
#endif


}




//=============================================================================
// DSPI_B_Clear_TCF
//=============================================================================
void DSPI_B_Clear_TCF(void)
{
	uint32_t   reg_value;

	reg_value = DSPI_B.SR.U32;
	reg_value = (reg_value & DSPI_TCF_CLEAR_MASK);
	DSPI_B.SR.U32 = reg_value;
}

//=============================================================================
// DSPI_B_Clear_EOQF
//=============================================================================
void DSPI_B_Clear_EOQF(void)
{
	uint32_t   reg_value;

	reg_value = DSPI_B.SR.U32;
	reg_value = (reg_value & DSPI_EOQF_CLEAR_MASK);
	DSPI_B.SR.U32 = reg_value;
}

//=============================================================================
// DSPI_B_Clear_RFDF
//=============================================================================
void DSPI_B_Clear_RFDF(void)
{
	uint32_t   reg_value;

	reg_value = DSPI_B.SR.U32;
	reg_value = (reg_value & DSPI_RFDF_CLEAR_MASK);
	DSPI_B.SR.U32 = reg_value;
}

//=============================================================================
// DSPI_B_SET_CTAR_FMSZ
//=============================================================================
void DSPI_B_SET_CTAR_FMSZ(DSPI_PUSHR_DSICR_CTAS_T CTAR , DSPI_CTAR_FMSZ_T FMSize)
{
	DSPI_B.CTAR[CTAR].F.FMSZ = FMSize;
}

//=============================================================================
// DSPI_B_Exchange_Mesage
//=============================================================================
void DSPI_B_Exchange_Mesage(
        DSPI_CS_T                in_cs_select,
        DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
        uint16_t       * in_tx_data,
        uint16_t       * in_rx_data,
        uint16_t   in_tx_length,
        uint16_t   in_rx_length
)
{

	DSPI_Recevice_Pointer = in_rx_data;
	DSPI_Recevice_length =  in_rx_length;

	DSPI_B_Initialize_Message_16bits(in_cs_select, in_ctar_msg,
	                                 in_tx_data ,in_tx_length);

	DMA_Set_Channel_Transfer_Count( DMA_CHANNEL_DSPI_B_SR_TFFF,in_tx_length);
	DMA_Set_Channel_Source_Address( DMA_CHANNEL_DSPI_B_SR_TFFF, DMA_DSPIB_SR_TFFF_Source_Address);

	DMA_Set_Channel_Transfer_Count( DMA_CHANNEL_DSPI_B_SR_RFDF,in_tx_length);
	DMA_Set_Channel_Destination_Address( DMA_CHANNEL_DSPI_B_SR_RFDF, DMA_DSPIB_SR_RFDF_Dest_Address);

	DMA_Enable_Request(DMA_CHANNEL_DSPI_B_SR_RFDF);
	//Clean up the DSPI module to be ready for next transfer
	DSPI_B_Clear_FIFO();
	//This flag will trigger the DMA channel for transmit
	DSPI_B_Clear_TCF();

	//This flag will start the SPI device transfer
	//Very important to clear the EOQF flag after DMA has been disabled.
	DSPI_B_Clear_EOQF();

	// DSPI_B_Enable_Transfer(true);
	DMA_Enable_Request(DMA_CHANNEL_DSPI_B_SR_TFFF);


}


//=============================================================================
// DSPI_B_SET_CTAR_FMSZ
//=============================================================================
void DSPI_B_RFDF_DMA_MAJ_INT(void)
{

	DMA_Clear_MAJ_Pending_INT(DMA_CHANNEL_DSPI_B_SR_RFDF);
	//check the  EOQ of DSPI
	while(DSPI_B.SR.F.EOQF== false) {

	}

	//This flag will start the SPI device transfer
	//Very important to clear the EOQF flag after DMA has been disabled.
	DSPI_B_Clear_EOQF();
	if(!DSPI_Recevice_length) {
		DSPI_B_Copy_Receive_Data_16bits(DSPI_Recevice_Pointer,DSPI_Recevice_length);
	}

}




//=============================================================================
// DSPI_B_Exchange_Data
//=============================================================================
uint16_t DSPI_B_Exchange_Data1(
        DSPI_CS_T               in_cs_select,
        DSPI_PUSHR_DSICR_CTAS_T in_ctar_msg,
        DSPI_CTAR_FMSZ_T        FMSize,
        void *                in_tx_data,
        bool                    in_end)
{
	DSPI_PUSHR_T tx_data_buffer;
	uint16_t     return_data;
	uint32_t     deadline;

	tx_data_buffer.U32 = 0;
	tx_data_buffer.F.PCSx = 1<< in_cs_select;
	tx_data_buffer.F.CTAS  = in_ctar_msg;
	tx_data_buffer.F.CONT =1;
	if(in_end) {
		tx_data_buffer.F.CONT =0;
		tx_data_buffer.F.CTCNT= true;
	}

	if (FMSize == 8) {
		tx_data_buffer.U32 = tx_data_buffer.U32| ((*(uint8_t *)in_tx_data) & 0x000000ff);
	} else {
		tx_data_buffer.U32 = tx_data_buffer.U32| ((*(uint16_t *)in_tx_data) & 0x0000ffff);
	}

	DSPI_B.CTAR[in_ctar_msg].F.FMSZ = FMSize;

	DSPI_B_Clear_RFDF();

	DSPI_B.PUSHR.U32 = tx_data_buffer.U32;

	/* detect the spi communication overtime */
	deadline = time_get(DSPI_EXCHANGE_TIME_MAX);
	while (DSPI_B.SR.F.RFDF != 1) {			/* wait for SPI return data */
		if (time_left(deadline) < 0) {
			break;
		}
	}

	return_data = (uint16_t)DSPI_B.POPR.F.RXDATA;

	/* clear dspi status register, RF, TF */
	DSPI_B.SR.U32 = 0x90020000;

	return return_data;
}

