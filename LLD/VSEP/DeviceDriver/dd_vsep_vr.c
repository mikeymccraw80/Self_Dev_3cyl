//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_vr.c~4:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:09:04 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Fri Feb 16 10:37:45 2007 %
//
// %version:         4 %
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
#include "reuse.h"
#include "dd_vsep.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_txd.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_msg_config.h"
#include "dd_vsep_init_config.h"

uint16_t VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_MAX];
uint16_t VSEP_VR_Rxd[VSEP_VR_RXD_MESSAGE_MAX];

//=============================================================================
// VSEP_VR_Get_Channel
//=============================================================================
static VSEP_VR_Channel_T VSEP_VR_Get_Channel( 
   IO_Configuration_T   in_configuration )
{
   VSEP_Channel_T    vsep_channel = VSEP_Get_Channel( in_configuration );
   VSEP_VR_Channel_T      channel = (vsep_channel >= VSEP_CHANNEL_VR1) && (vsep_channel <= VSEP_CHANNEL_VR2) ? 
                                    (vsep_channel - VSEP_CHANNEL_VR1) : VSEP_CHANNEL_MAX;

   return channel;
   
}

//=============================================================================
// VSEP_PULSE_VR_Initialize_Device
//=============================================================================
void VSEP_PULSE_VR_Initialize_Device(void)
{
#ifdef VSEP_VR_STATIC_INITIALIZATION
    VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_CTRL ] = VSEP_VR_TXD_INITIAL[ VSEP_VR_TXD_MESSAGE_CTRL ];
    VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_VR1 ]  = VSEP_VR_TXD_INITIAL[ VSEP_VR_TXD_MESSAGE_VR1 ]; 
    VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_VR2 ]  = VSEP_VR_TXD_INITIAL[ VSEP_VR_TXD_MESSAGE_VR2 ]; 
#else
    VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_VR_FLT );
    VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_VR1_CTRL );
#endif
}

//=============================================================================
// VSEP_PULSE_VR_Initialize_Channel
//=============================================================================
void VSEP_PULSE_VR_Initialize_Channel(
   IO_Configuration_T   in_configuration )
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel( in_configuration);
   
   if( channel !=  VSEP_VR_CHANNEL_MAX )
   {
      VSEP_TIMER_VR_Set_Value( in_configuration, VSEP_VR_Get_Initial_Delay( in_configuration) );

      VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_VR1 + channel ] = VSEP_Msg_VR_Set_AT( VSEP_VR_Txd[ VSEP_VR_TXD_MESSAGE_VR1 + channel ], 
                                                                                            VSEP_VR_Get_Adaptive_Threshold( in_configuration ) );
   }
}

//=============================================================================
// VSEP_TIMER_VR_Set_Value
//=============================================================================
void VSEP_TIMER_VR_Set_Value(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time )
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel( in_configuration);

   if( channel != VSEP_VR_CHANNEL_MAX )
   {
      VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel ] = 
            VSEP_Msg_VR_Set_Delay(VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel],
                                    ( in_time >> VSEP_TXD_VR_DLY_FIXED_BITS ) );
   }
}

//=============================================================================
// VSEP_TIMER_VR_Set_Value_Immediate
//=============================================================================
void VSEP_TIMER_VR_Set_Value_Immediate(
   IO_Configuration_T   in_configuration,
   uint32_t             in_time )
{
    VSEP_TIMER_VR_Set_Value( in_configuration, in_time );
	VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_VR );
}

//=============================================================================
// VSEP_TIMER_VR_Get_Value
//=============================================================================
uint32_t VSEP_TIMER_VR_Get_Value(
   IO_Configuration_T   in_configuration)
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel( in_configuration);
   uint32_t value = 0xffffffffU;//need pay attention again

   if( channel != VSEP_VR_CHANNEL_MAX )
   {
      value = VSEP_Msg_VR_Get_Delay(VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel]);
      value <<= VSEP_TXD_VR_DLY_FIXED_BITS;
      value |= VSEP_TXD_VR_DLY_MIN_TIME;
   }

   return value;
}

//=============================================================================
// VSEP_TIMER_VR_Get_State
//=============================================================================
IO_Timer_State_T VSEP_TIMER_VR_Get_State(
   IO_Configuration_T   in_configuration)
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel( in_configuration);
   IO_Timer_State_T   state  = IO_TIMER_STATE_RESET;

   if( channel != VSEP_VR_CHANNEL_MAX )
   {

      if( VSEP_VR_Rxd[ VSEP_VR_RXD_MESSAGE_VR_FLT ] & ( 0x08 << channel ) )
      {
         state = IO_TIMER_STATE_OVERFLOW;
      }
      else
      {
         state = IO_TIMER_STATE_RUNNING;
      }
   }

   return state;
}

//=============================================================================
// VSEP_TIMER_VR_Get_Base_Frequency
//=============================================================================
uint32_t VSEP_TIMER_VR_Get_Base_Frequency(
   IO_Configuration_T   in_configuration)
{
   return VSEP_TIMER_VR_Base_Frequency;
}

//=============================================================================
// VSEP_TIMER_VR_Get_Size
//=============================================================================
IO_Timer_Size_T VSEP_TIMER_VR_Get_Size(
   IO_Configuration_T   in_configuration )
{
   return IO_TIMER_12_BIT;
}

//=============================================================================
// VSEP_VR_Set_AT
//=============================================================================
void VSEP_VR_Set_AT( IO_Configuration_T in_configuration, VSEP_VR_Adaptive_Threshold_T in_AT )
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel( in_configuration);
   
   VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel ] = VSEP_Msg_VR_Set_AT(VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel ], in_AT);
}

//=============================================================================
// VSEP_VR_Get_AT
//=============================================================================
VSEP_VR_Adaptive_Threshold_T VSEP_VR_Get_AT( IO_Configuration_T in_configuration )
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel(in_configuration);

   return VSEP_Msg_VR_Get_AT( VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel ] );
}


//=============================================================================
// VSEP_VR_Set_MT
//=============================================================================
void VSEP_VR_Set_MT( IO_Configuration_T in_configuration, VSEP_VR_Adaptive_Threshold_T in_AT )
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel( in_configuration);
   
   VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel] = VSEP_Msg_VR_Set_MT(VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel ], in_AT);
}

//=============================================================================
// VSEP_VR_Get_MT
//=============================================================================
VSEP_VR_Min_Threshold_T VSEP_VR_Get_MT( IO_Configuration_T in_configuration )
{
   VSEP_VR_Channel_T channel = VSEP_VR_Get_Channel( in_configuration);

   return VSEP_Msg_VR_Get_MT( VSEP_VR_Txd[VSEP_VR_TXD_MESSAGE_VR1 + channel]);
}
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 *
 * 04/16/09     sjl         306
 * + MT22.1: RSM_CTC_0137_Add 58x signal heavy filter during crank_Rev1_20090227
 *   - Changed VSEP_TIMER_VR_Set_Value_Immediate() to @far type
\*===========================================================================*/
