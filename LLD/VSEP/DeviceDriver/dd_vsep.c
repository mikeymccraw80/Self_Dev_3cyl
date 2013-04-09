//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep.c~13.1.1.1.2:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 11:47:36 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 12:08:07 2007 %
//
// %version:         13.1.1.1.2 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

//=============================================================================
// Include the Type file for the device driver and io layers
//=============================================================================
//#include "io_type.h"// this file is the same with the one in MT80

//=============================================================================
// Include interface for the device driver
//=============================================================================

//#include "dd_port.h"
//#include "dd_spi.h"
//#include "dd_config.h"
#include "dd_vsep_fault.h"
#include "io_spi_config.h"
#include "io_config_spi.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_discrete_interface.h"
#include "dd_vsep_soh.h"
#include "io_config_vsep.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_config.h"
#include "dd_vsep_init.h"
#include "dd_vsep_vr.h"

//#include "dd_dma_interface.h"
#include "dd_dspi_interface.h"
#include "io_config_dma.h"
#include "io_config_dspi.h"

uint32_t            VSEP_Channel_Enabled;
extern const SPI_Message_T VSEP_MESSAGE[ NUMBER_OF_VSEP ][VSEP_MESSAGE_MAX+7];


//=============================================================================
// VSEP_Clear_Device
//=============================================================================
void VSEP_Clear_Device(IO_Configuration_T in_configuration)
{
	Parameter_Not_Used( in_configuration );
}

//=============================================================================
// VSEP_LEDMODE_Initialize_Device
//=============================================================================
void VSEP_LEDMODE_Initialize_Device(IO_Configuration_T in_configuration )
{
	VSEP_Index_T device = VSEP_Get_Device_Index( in_configuration );

	VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED );
	VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_LED_MODE_CTRL );
}

//=============================================================================
// VSEP_LEDMODE_Set_Channel
//=============================================================================
void VSEP_LEDMODE_Set_Channel(IO_Configuration_T in_configuration, VSEP_LEDMODE_Channel_T in_group, uint32_t in_ledmode )
{
	VSEP_Index_T device = VSEP_Get_Device_Index( in_configuration );

	switch ( in_group ) {
	case VSEP_LEDMODE_25:
		VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_25( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
		break;
	case VSEP_LEDMODE_26:
		VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_26( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
		break;
	case VSEP_LEDMODE_30:
		VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_30( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
	break;
	case  VSEP_LEDMODE_ALL_CHANNEL:
		VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_ALL( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
		break;
	}
	VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_LEDMODE );
}


//=============================================================================
// VSEP_LEDMODE_Get_Channel
//=============================================================================
uint32_t VSEP_LEDMODE_Get_Channel(IO_Configuration_T in_configuration, VSEP_LEDMODE_Channel_T in_group )
{
	VSEP_Index_T device = VSEP_Get_Device_Index( in_configuration );
	uint32_t ledmode = 0;

	switch( in_group ) {
	case VSEP_LEDMODE_25:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_25( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	case VSEP_LEDMODE_26:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_26( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	case VSEP_LEDMODE_30:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_30( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	case VSEP_LEDMODE_ALL_CHANNEL:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_ALL( VSEP_LEDMODE_Txd[ device ][ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	}

	return ledmode;
}

/* FUNCTION: SPI_Port_Transfer_Vsep                                          */
/*===========================================================================*/
/* RETURN VALUE:                                                             */
/*   void                                                                    */
/*                                                                           */
/* INPUT PARAMETERS:                                                         */
/*   SPI_Message_Definition_T        Indicates the SPI message  to be transmitted.                    */
/*                                                                           */
/* EXTERNAL REFERENCES:                                                      */
/*   None.                                                                   */
/*                                                                           */
/* DEVIATIONS FROM STANDARDS:                                                */
/*   None.                                                                   */
/*                                                                           */
/* --------------------------------------------------------------------------*/
/* ABSTRACT:                                                                 */
/* --------------------------------------------------------------------------*/
/* This function transmits a message specified and received corresponding return message using SPI module 0.         */
/* Note: Module 1 and 2 are not required for the project                     */
/*===========================================================================*/
/*
transmit the corresponding message, input VSEP_MESSAGE
*/

void  VSEP_SPI_Port_Transfer(SPI_Message_Definition_T  const *def)
{
	uint8_t   index, transmint_length;
	uint16_t  transmit_size;
	uint8_t   index_transmint,idex_receive;
	bool      end;

	for (index_transmint = 0,idex_receive =0; index_transmint < def->length_of_transmit_message; index_transmint++,idex_receive++) {
		//for word transfer algorithem
		if ((idex_receive<def->length_of_receive_message)&&(((((uint16_t*)def->transmit_data)[0])&0xF00)!=0x0F00)) {
			if(index_transmint == def->length_of_transmit_message-1) {
				end = 1;
			} else {
				end = 0;
			}
			((uint16_t*)def->receive_data)[idex_receive] = DSPI_B_Exchange_Data1(
					 VSEP_CHIP_SELECT,
					 VSEP_CTAR_SELECT,
					 DSPI_CTAR_FMSZ_16,
					 ((uint16_t*)def->transmit_data)[index_transmint],
					 end);
		} else {
			if(index_transmint == def->length_of_transmit_message-1) {
				end = 1;
			} else {
				end = 0;
			}
			DSPI_B_Exchange_Data1(
					VSEP_CHIP_SELECT,
					VSEP_CTAR_SELECT,
					DSPI_CTAR_FMSZ_16,
					((uint16_t*)def->transmit_data)[index_transmint],
					end);
		}
	}
}


//=============================================================================
// VSEP_SPI_Immediate_Transfer
//=============================================================================
void VSEP_SPI_Immediate_Transfer(IO_Configuration_T in_configuration, VSEP_Message_T in_message)
{
	VSEP_PWM_Channel_T pwm_channel;

	switch (in_message) {
	case VSEP_MESSAGE_INIT:
	case VSEP_MESSAGE_VR:
	case VSEP_MESSAGE_FAULT:
	case VSEP_MESSAGE_MPIO_MODE:
	case VSEP_MESSAGE_LEDMODE:
	case VSEP_MESSAGE_DEPS:
	case VSEP_MESSAGE_PCH_MPIO:
	case VSEP_MESSAGE_EST_SELECT:
	case VSEP_MESSAGE_EST_FAULT:
	case VSEP_MESSAGE_SOH:
	case VSEP_MESSAGE_SOH_STATUS:
		VSEP_SPI_Port_Transfer(VSEP_MESSAGE[VSEP_Get_Device_Index(in_configuration)][in_message].def);
		break;
	case VSEP_MESSAGE_PWM:
		pwm_channel = VSEP_PWM_Get_Channel( in_configuration);
		if(pwm_channel != VSEP_PWM_CHANNEL_MAX)
			VSEP_SPI_Port_Transfer(VSEP_MESSAGE[ VSEP_Get_Device_Index( in_configuration ) ][VSEP_MESSAGE_PWM + pwm_channel ].def);
		break;
	default:
		break;
	}
}


void VSEP_Initialize_Device(void)
{
	uint16_t index=0;
	VSEP_Channel_Enabled = 0xFFFFFFFF;   

#ifdef  VSEP_CALIBRATION_ENABLE
	VSEP_INIT_TXD_Buffer_Initialize();
#endif

	VSEP_EST_Select_Initialize_Device(MTSA_CONFIG_VSEP_DEVICE_0);
	VSEP_Fault_Initialize();
	VSEP_MPIO_MODE_Initialize_Device(MTSA_CONFIG_VSEP_DEVICE_0);
	VSEP_PWM_Device_Initialize( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ) );
	VSEP_DISCRETE_Device_Initialize( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ) );
	VSEP_FAULT_EST_Initialize_Device( MTSA_CONFIG_GRADIENT_COUNT );
	VSEP_SPI_SCHEDULER_Initialize();   
	VSEP_LEDMODE_Initialize_Device( MTSA_CONFIG_VSEP_DEVICE_0);
	VSEP_PULSE_VR_Initialize_Device(MTSA_CONFIG_VSEP_DEVICE_0);

	// Hardware Test uses its own method to initialize the VSEP
	// Send the Init message to the VSEP. This will setup all the faults/slews/est select information/
	// along with all the locked bit information.
	VSEP_SPI_Immediate_Transfer( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_MESSAGE_INIT );
	// Need to check why redundant operation is needed, without it, no spark injection
	VSEP_SPI_Immediate_Transfer( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ), VSEP_MESSAGE_INIT );
	//#ifdef HW_SOH_DISABLE
	VSEP_Disable_SOH();
	//#endif

	#if COIL == COIL_AT_PLUG
	//  VSEP_EST_Select_Set_Mode(VSEP_INDEX_0,EST_MODE_SEQUENTIAL_SINGLE_ENABLE);
	#elif COIL == DUAL_COIL_PACK
	//VSEP_EST_Select_Set_Mode(VSEP_INDEX_0,EST_MODE_SIMULTANEOUS_SINGLE_ENABLE);
	#endif
	VSEP_EST_Select_Set_Mode(VSEP_INDEX_0,EST_MODE_SIMULTANEOUS_SINGLE_ENABLE); 
	VSEP_EST_Select_Set_Channel(VSEP_INDEX_0,EST_SELECT_CYLINDER_A);
}


