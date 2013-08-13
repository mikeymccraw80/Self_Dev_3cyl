//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_discrete.c~5.1.1:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:40 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 12:00:54 2007 %
//
// %version:         5.1.1 %
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
#include "dd_vsep.h"
#include "dd_vsep.h"
#include "dd_vsep_led.h"
#include "dd_vsep_txd.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_init_config.h"

/* LED spi tx and rx message buffer definiton */
uint16_t VSEP_LEDMODE_Txd[VSEP_LEDMODE_TXD_MESSAGE_MAX];


//=============================================================================
// VSEP_LEDMODE_Initialize_Device
//=============================================================================
void VSEP_LEDMODE_Initialize_Device(IO_Configuration_T in_configuration )
{
	VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED );
	VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_LED_MODE_CTRL );
}

//=============================================================================
// VSEP_LEDMODE_Set_Channel
//=============================================================================
void VSEP_LEDMODE_Set_Channel(IO_Configuration_T in_configuration, VSEP_LEDMODE_Channel_T in_group, uint32_t in_ledmode )
{
	switch ( in_group ) {
	case VSEP_LEDMODE_25:
		VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_25( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
		break;
	case VSEP_LEDMODE_26:
		VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_26( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
		break;
	case VSEP_LEDMODE_30:
		VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_30( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
	break;
	case  VSEP_LEDMODE_ALL_CHANNEL:
		VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] = VSEP_Msg_LEDMODE_Set_Channel_ALL( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ], in_ledmode );
		break;
	}
	VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_LEDMODE );
}


//=============================================================================
// VSEP_LEDMODE_Get_Channel
//=============================================================================
uint32_t VSEP_LEDMODE_Get_Channel(IO_Configuration_T in_configuration, VSEP_LEDMODE_Channel_T in_group )
{
	uint32_t ledmode = 0;

	switch( in_group ) {
	case VSEP_LEDMODE_25:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_25( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	case VSEP_LEDMODE_26:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_26( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	case VSEP_LEDMODE_30:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_30( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	case VSEP_LEDMODE_ALL_CHANNEL:
		ledmode = VSEP_Msg_LEDMODE_Get_Channel_ALL( VSEP_LEDMODE_Txd[ VSEP_LEDMODE_TXD_MESSAGE_ENABLE ] );
		break;
	}

	return ledmode;
}



