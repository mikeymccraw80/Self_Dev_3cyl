#ifndef DD_DSPI_INTERFACE_H
#define DD_DSPI_INTERFACE_H

#include "dd_dspi.h"
#include "io_config_dspi.h"

//=============================================================================
// DSPI
//=============================================================================

extern uint16_t DSPI_SPI_Port_Rxd_B[ DSPI_SPI_PORT_DATA_LENGTH_INIT_B ];
extern uint32_t DSPI_SPI_Port_Txd_B[ DSPI_SPI_PORT_DATA_LENGTH_INIT_B ];


//=============================================================================
// DSPI_B_Initialize_Device
//=============================================================================
void DSPI_B_Initialize_Device(void );
//=============================================================================
// DSPI_C_Initialize_Device
//=============================================================================
void DSPI_C_Initialize_Device(void );

//============================================================================
// DSPI_Enable_Transfer
//============================================================================
void DSPI_B_Enable_Transfer (bool   in_enable );

//============================================================================
// DSPI_Enable_Transfer
//============================================================================
void DSPI_C_Enable_Transfer (bool   in_enable );

//=============================================================================
// DSPIPort_Initialize_Message
//=============================================================================
void DSPI_B_Initialize_Message_16bits(
   DSPI_CS_T                in_cs_select,
   DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
   uint16_t        *in_tx_data_buffer,
   uint8_t                       in_transmit_count  );
//=============================================================================
// DSPIPort_Initialize_Message
//=============================================================================
void DSPI_B_Initialize_Message_8bits(
   DSPI_CS_T                in_cs_select,
   DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
   uint8_t        *in_tx_data_buffer,
   uint8_t                       in_transmit_count  );

//=============================================================================
// DSPIPort_Copy_Transmit_Data
//=============================================================================
void DSPI_B_Copy_Receive_Data_16bits(
    uint16_t           *in_rx_data_buffer,
   uint16_t                       in_receive_count);

//=============================================================================
// DSPIPort_Copy_Transmit_Data
//=============================================================================
void DSPI_B_Copy_Receive_Data_8bits(
    uint8_t           *in_rx_data_buffer,
   uint8_t                       in_receive_count);

//=============================================================================
// DSPI_B_Clear_FIFO
//=============================================================================
void DSPI_B_Clear_FIFO(void);

//=============================================================================
// DSPI_B_Exchange_Data
//=============================================================================
void   DSPI_B_Exchange_Data(
   DSPI_CS_T                in_cs_select,
   DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
   DSPI_CTAR_FMSZ_T FMSize,
   uint16_t       * in_tx_data,
   uint16_t       * in_rx_data,
   uint16_t    Transmit_size);

//=============================================================================
// DSPI_B_Exchange_Data
//=============================================================================
void   DSPI_B_Send_Data(
   DSPI_CS_T                in_cs_select,
   DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
   DSPI_CTAR_FMSZ_T FMSize,
   uint16_t       * in_tx_data,
   uint16_t    Transmit_size);

//=============================================================================
// DSPI_B_Clear_TCF
//=============================================================================
void DSPI_B_Clear_TCF(void);
//=============================================================================
// DSPI_B_Clear_EOQF
//=============================================================================
void DSPI_B_Clear_EOQF(void);

//=============================================================================
// DSPI_B_Clear_RFDF
//=============================================================================
void DSPI_B_Clear_RFDF(void);

//=============================================================================
// DSPI_B_SET_CTAR_FMSZ
//=============================================================================
void DSPI_B_SET_CTAR_FMSZ(DSPI_PUSHR_DSICR_CTAS_T CTAR , DSPI_CTAR_FMSZ_T FMSize);

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
                );





//=============================================================================
// DSPI_B_Exchange_Data
//=============================================================================
uint16_t   DSPI_B_Exchange_Data1(
   DSPI_CS_T                in_cs_select,
   DSPI_PUSHR_DSICR_CTAS_T             in_ctar_msg,
   DSPI_CTAR_FMSZ_T FMSize,
   uint16_t        in_tx_data,
   bool in_end);
//=============================================================================

#endif

