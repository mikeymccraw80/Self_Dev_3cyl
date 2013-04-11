//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_deps.c~2:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:24 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 10:39:52 2007 %
//
// %version:         2 %
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

#include "dd_vsep_deps.h"
#include "dd_vsep_txd.h"
#include "dd_vsep_rxd.h"
#include "dd_vsep.h"


uint16_t VSEP_DEPS_Txd[NUMBER_OF_VSEP][VSEP_DEPS_TXD_MESSAGE_MAX];
uint16_t VSEP_DEPS_Rxd[NUMBER_OF_VSEP][VSEP_DEPS_RXD_MESSAGE_MAX];

//=============================================================================
// VSEP_PULSE_DEPS_Initialize_Device
//=============================================================================
void VSEP_PULSE_DEPS_Initialize_Device(
   IO_Configuration_T   in_configuration )
{
   VSEP_Index_T device = VSEP_Get_Device_Index(in_configuration);

#ifdef VSEP_DEPS_STATIC_INITIALIZATION

   VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_CTRL  ] = VSEP_DEPS_TXD_INITIAL[ device ][ VSEP_DEPS_TXD_MESSAGE_CTRL ];
   VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_DELAY ] = VSEP_DEPS_TXD_INITIAL[ device ][ VSEP_DEPS_TXD_MESSAGE_DELAY ]; 
#else

   VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED );
   VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_DEPS_CTRL );
#endif
}

//=============================================================================
// VSEP_PULSE_DEPS_Clear_Device
//=============================================================================
void VSEP_PULSE_DEPS_Clear_Device(
   IO_Configuration_T   in_configuration )
{
   Parameter_Not_Used( in_configuration );
}

//=============================================================================
// VSEP_PULSE_DEPS_Initialize_Channel
//=============================================================================
void VSEP_PULSE_DEPS_Initialize_Channel(
   IO_Configuration_T   in_configuration )
{
   VSEP_TIMER_DEPS_Set_Value( in_configuration, VSEP_DEPS_Get_Initial_Delay( in_configuration) );
}

//=============================================================================
// VSEP_TIMER_DEPS_Set_Value
//=============================================================================
void VSEP_TIMER_DEPS_Set_Value(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time )
{
   VSEP_Index_T      device = VSEP_Get_Device_Index(in_configuration);

   
   VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_DELAY ] = 
      VSEP_Msg_DEPS_Set_Delay( VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_DELAY ], (in_time >> VSEP_TXD_DEPS_FIXED_BITS ) );
}

//=============================================================================
// VSEP_TIMER_DEPS_Set_Value_Immediate
//=============================================================================
void VSEP_TIMER_DEPS_Set_Value_Immediate(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time )
{
   VSEP_TIMER_DEPS_Set_Value( in_configuration, in_time );
   //VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_DEPS );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_DEPS );
}

//=============================================================================
// VSEP_TIMER_DEPS_Get_Value
//=============================================================================
uint32_t VSEP_TIMER_DEPS_Get_Value(
   IO_Configuration_T   in_configuration)
{
   VSEP_Index_T device = VSEP_Get_Device_Index(in_configuration);
   uint32_t value;

   value = VSEP_Msg_DEPS_Get_Delay( VSEP_DEPS_Txd[ device ][ VSEP_DEPS_TXD_MESSAGE_DELAY ] );

   value <<= VSEP_TXD_DEPS_FIXED_BITS;
   value |= VSEP_TXD_DEPS_MIN_TIME;

   return value;
}

//=============================================================================
// VSEP_TIMER_DEPS_Get_State
//=============================================================================
IO_Timer_State_T VSEP_TIMER_DEPS_Get_State(
   IO_Configuration_T   in_configuration)
{
   Parameter_Not_Used( in_configuration );
   return IO_TIMER_STATE_RUNNING;
}

//=============================================================================
// VSEP_TIMER_DEPS_Get_Base_Frequency
//=============================================================================
uint32_t VSEP_TIMER_DEPS_Get_Base_Frequency(
   IO_Configuration_T   in_configuration)
{
   Parameter_Not_Used( in_configuration );
   return VSEP_TIMER_DEPS_Base_Frequency;
}

//=============================================================================
// VSEP_TIMER_DEPS_Get_Size
//=============================================================================
IO_Timer_Size_T VSEP_TIMER_DEPS_Get_Size(
   IO_Configuration_T   in_configuration )
{
   Parameter_Not_Used( in_configuration );
   return IO_TIMER_11_BIT;
}
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
\*===========================================================================*/
