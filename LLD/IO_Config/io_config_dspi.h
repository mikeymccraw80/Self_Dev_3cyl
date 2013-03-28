
#ifndef IO_CONFIG_DSPI_H
#define IO_CONFIG_DSPI_H


#include "dd_dspi.h"




#define DSPI_SPI_PORT_DATA_LENGTH_INIT_B   (30)

//=============================================================================
// Initialization Constants for Module Control Register (MCR)
// Field definitions:
//=============================================================================

extern const DSPI_MCR_T    DSPI_B_MCR_INIT ;

//=============================================================================
// Initialization Constants for Module Control Register (MCR)
// Field definitions:
//=============================================================================

extern const DSPI_MCR_T    DSPI_C_MCR_INIT;

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
// DSPI_B_CTAR_0_
//=======================================================================================
extern const DSPI_CTAR_T   DSPI_B_CTAR0_INIT;

#define VSEP_CHIP_SELECT  DSPI_CS_0

#define VSEP_CTAR_SELECT  DSPI_PUSHR_DSICR_CTAS_CTAR0

//=======================================================================================
// DSPI_B_CTAR_1_PHD
//=======================================================================================
extern const DSPI_CTAR_T   DSPI_B_CTAR1_INIT;

#define ETC_CHIP_SELECT   DSPI_CS_1

#define ETC_CTAR_SELECT   DSPI_PUSHR_DSICR_CTAS_CTAR1

//=======================================================================================
// DSPI_B_CTAR_2_KP254
//=======================================================================================

extern const DSPI_CTAR_T   DSPI_B_CTAR2_INIT;

#define BARO_CHIP_SELECT   DSPI_CS_2

#define BARO_CTAR_SELECT   DSPI_PUSHR_DSICR_CTAS_CTAR2


//=======================================================================================
// DSPI_B_CTAR_3_C2PS
//=======================================================================================
extern const DSPI_CTAR_T   DSPI_B_CTAR3_INIT;

#define POWER_CHIP_SELECT   DSPI_CS_3

#define POWER_CTAR_SELECT   DSPI_PUSHR_DSICR_CTAS_CTAR3
//=======================================================================================
// DSPI_C_CTAR_0_ - 20M BPS
//=======================================================================================
extern const DSPI_CTAR_T   DSPI_C_CTAR0_INIT;

//=============================================================================
// Initialization Constants for DMA/Interrupt Select and Enable (DSPIx_RSER)
//=============================================================================

extern const DSPI_RSER_T   DSPI_B_RSER_INIT;

//=============================================================================
// Initialization Constants for DMA/Interrupt Select and Enable (DSPIx_RSER)
//=============================================================================

extern const DSPI_RSER_T   DSPI_C_RSER_INIT;
//=============================================================================
// Initialization Constants for DSPI DSI Configuration Register (DSPIx_DISCR)
//=============================================================================
extern const DSPI_DSICR_T  DSPIC_DSICR_INIT;


#endif
