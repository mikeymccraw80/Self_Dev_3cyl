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
#include "dd_vsep_discrete.h"
#include "dd_vsep_txd.h"
#include "dd_vsep_rxd.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_msg_config.h"
#include "dd_vsep_init_config.h"

/* PCH spi tx and rx message buffer definiton */
uint16_t VSEP_PCH_Txd[VSEP_PCH_TXD_MESSAGE_MAX];
uint16_t VSEP_PCH_Rxd[VSEP_PCH_RXD_MESSAGE_MAX];
uint16_t VSEP_MPIO_MODE_Txd[VSEP_MPIO_MODE_TXD_MESSAGE_MAX];

static const uint8_t VSEP_DISCRETE_PCH_CHANNEL_MAP[VSEP_CHANNEL_MAX] =
{
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_OUT_4,
    VSEP_PCH_CHANNEL_OUT_5,
    VSEP_PCH_CHANNEL_OUT_6,
    VSEP_PCH_CHANNEL_OUT_7,
    VSEP_PCH_CHANNEL_OUT_8,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_OUT_13,
    VSEP_PCH_CHANNEL_OUT_14,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_OUT_17,
    VSEP_PCH_CHANNEL_OUT_18,
    VSEP_PCH_CHANNEL_OUT_19,
    VSEP_PCH_CHANNEL_OUT_20,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_OUT_23,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_OUT_25,
    VSEP_PCH_CHANNEL_OUT_26,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_OUT_30,
    VSEP_PCH_CHANNEL_MPIO_1,
    VSEP_PCH_CHANNEL_MPIO_2,
    VSEP_PCH_CHANNEL_MPIO_3,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_MAX,
    VSEP_PCH_CHANNEL_SOHRSTEN_STAT
};

//=============================================================================
// VSEP_DISCRETE_Device_Initialize
//=============================================================================
/* refer to:
//=============================================================================
// PCH_04 - SDOUT_4 - ESTD
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_04 \
        ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_04_FLT_LVL_1_2     ) )

#define VSEP_0_PCH4_INIT MTSA_CONFIG_VSEP_PCH_04
*/

void VSEP_DISCRETE_Device_Initialize(void)
{
#ifdef VSEP_DISCRETE_STATIC_INITIALIZATION
   VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ] = VSEP_PCH_TXD_INITIAL[ VSEP_PCH_TXD_MESSAGE_CTRL ];
   VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_PCH  ] = VSEP_PCH_TXD_INITIAL[ VSEP_PCH_TXD_MESSAGE_PCH  ]; 
#else          
   VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED );
   VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_PCH );
#endif
}

//=============================================================================
// VSEP_DISCRETE_Device_Clear
//=============================================================================
void VSEP_DISCRETE_Device_Clear(void)
{
   VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA( VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED );
   VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA( VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_PCH );
   VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_PCH  ]  = 0; 
}

//=============================================================================
// VSEP_DISCRETE_Initialize_Channel
//=============================================================================
void VSEP_DISCRETE_Channel_Initialize(IO_Configuration_T in_configuration)
{
    VSEP_DISCRETE_Set_State( in_configuration, 
        VSEP_PCH_Get_Initial_State( in_configuration ) == IO_ACTIVE ? true : false );
}

//=============================================================================
// VSEP_DISCRETE_Clear_Channel
//=============================================================================
void VSEP_DISCRETE_Channel_Clear(IO_Configuration_T in_configuration)
{
    VSEP_DISCRETE_Set_State( in_configuration, false );
}

//=============================================================================
// VSEP_DISCRETE_Get_State
//=============================================================================
bool VSEP_DISCRETE_Get_State(IO_Configuration_T in_configuration)
{
   bool                        state = false;
   VSEP_Channel_T       vsep_channel = VSEP_Get_Channel( in_configuration );
   IO_Polarity_T            polarity = VSEP_PCH_Get_Polarity( in_configuration );
   VSEP_PCH_Channel_T        channel = ( vsep_channel < VSEP_CHANNEL_MAX ) ? 
                                       VSEP_DISCRETE_PCH_CHANNEL_MAP[ vsep_channel ] : 
                                       VSEP_PCH_CHANNEL_MAX;


    if( channel < VSEP_PCH_CHANNEL_MPIO_1 ) { 
        state = VSEP_Msg_PCHx_Get_State( VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_PCH ], channel );
        // we only get the state information from the TXD what we have set. no state information out. 
    } else if( channel <= VSEP_PCH_CHANNEL_MPIO_3 ) {
        channel -= VSEP_PCH_CHANNEL_MPIO_1;
        state = (bool)Extract_Bits( VSEP_PCH_Rxd[ VSEP_PCH_RXD_MESSAGE_MPIO ], channel , BIT_1 );
    } else {
        if( channel == VSEP_PCH_CHANNEL_SOHRSTEN_STAT ) {
            state = VSEP_Msg_Get_SOHRSTEN_STAT( VSEP_SOH_Status_Rxd[ VSEP_SOH_STATUS_RXD_MESSAGE_STATUS ]);
        }
    }

    if(polarity != IO_ACTIVE_HIGH) {
        state = (state == true) ? false : true;
    }
   
    return state;
}

//=============================================================================
// VSEP_DISCRETE_Get_Immediate_State
//=============================================================================
bool VSEP_DISCRETE_Get_Immediate_State(IO_Configuration_T in_configuration)
{
    VSEP_Channel_T channel = VSEP_Get_Channel( in_configuration );

    if((channel >= VSEP_CHANNEL_MPIO_1) && (channel <= VSEP_CHANNEL_MPIO_3)) {
        //VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_PCH_MPIO );  
        VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_PCH_MPIO );  
    } else {
        if((channel == VSEP_CHANNEL_SOHRSTEN_STAT)) {
            //VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH_STATUS );  
            VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH_STATUS );  
        }
    }
    // for PCH0~30, did not set the state immediately, are there any risk?
    return VSEP_DISCRETE_Get_State( in_configuration );
}

//=============================================================================
// VSEP_DISCRETE_Set_State
//=============================================================================
void VSEP_DISCRETE_Set_State(IO_Configuration_T in_configuration, bool in_state)
{
   VSEP_Channel_T   vsep_channel = VSEP_Get_Channel(in_configuration);
   IO_Polarity_T        polarity = VSEP_PCH_Get_Polarity( in_configuration );
   VSEP_PCH_Channel_T    channel = ( vsep_channel < VSEP_CHANNEL_MAX ) ? 
                                    VSEP_DISCRETE_PCH_CHANNEL_MAP[ vsep_channel ] : 
                                    VSEP_PCH_CHANNEL_MAX;

    if(polarity != IO_ACTIVE_HIGH)// check the polarity
    {
        in_state = (in_state == true) ? false : true;
    }
    if(in_state){
        VSEP_DIS_ON_OFF_state |=(Mask32(vsep_channel,1));
    } else {
        VSEP_DIS_ON_OFF_state &=~(Mask32(vsep_channel,1));
    }
    if( channel < VSEP_PCH_CHANNEL_MPIO_1 ) { 

        VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_PCH ] = 
            VSEP_Msg_PCHx_Set_State( VSEP_PCH_Txd[ VSEP_PCH_TXD_MESSAGE_PCH ], channel, in_state );

    } else  {
        if( channel == VSEP_PCH_CHANNEL_SOHRSTEN_STAT ) {
            VSEP_Msg_Set_SOHRSTEN_STAT( VSEP_SOH_Status_Rxd[ VSEP_SOH_STATUS_RXD_MESSAGE_STATUS ], in_state);
        }
    }
}

//=============================================================================
// VSEP_DISCRETE_Set_Immediate_State
//=============================================================================
void VSEP_DISCRETE_Set_Immediate_State(IO_Configuration_T in_configuration, bool in_state)
{
    VSEP_DISCRETE_Set_State( in_configuration, in_state );
    VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_PCH_MPIO );
}

//=============================================================================
// VSEP_DISCRETE_Toggle_State
//
// @func Toggles the state of the desired output, may be buffered.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_DISCRETE_Toggle_State(IO_Configuration_T in_configuration)
{
    VSEP_DISCRETE_Set_State(in_configuration, 
            VSEP_DISCRETE_Get_State( in_configuration ) == true ? false : true );
}

//=============================================================================
// VSEP_DISCRETE_Toggle_Immediate_State
//
// @func Toggles the state of the desired output immediately.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_DISCRETE_Toggle_Immediate_State(//question: why not get the state first?
   IO_Configuration_T in_configuration)
{
   VSEP_DISCRETE_Toggle_State( in_configuration );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_PCH_MPIO );
}

//===================================================================
// VSEP_MPIO_MODE_Initialize_Device
//===================================================================
void VSEP_MPIO_MODE_Initialize_Device(void)
{
#ifdef VSEP_MPIO_MODE_STATIC_INITIALIZATION
   VSEP_MPIO_MODE_Txd[ VSEP_MPIO_MODE_TXD_MESSAGE_CTRL ] = VSEP_MPIO_MODE_TXD_INITIAL[ VSEP_MPIO_MODE_TXD_MESSAGE_CTRL ];
   VSEP_MPIO_MODE_Txd[ VSEP_MPIO_MODE_TXD_MESSAGE_MODE ] = VSEP_MPIO_MODE_TXD_INITIAL[ VSEP_MPIO_MODE_TXD_MESSAGE_MODE ];
#else

   VSEP_MPIO_MODE_Txd[ VSEP_MPIO_MODE_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDIA ( VSEP_MPIO_MODE_Txd[ VSEP_MPIO_MODE_TXD_MESSAGE_CTRL ], VSEP_RXD_SDOA_NOT_USED ); 
   VSEP_MPIO_MODE_Txd[ VSEP_MPIO_MODE_TXD_MESSAGE_CTRL ] = VSEP_Msg_Set_SDOA ( VSEP_MPIO_MODE_Txd[ VSEP_MPIO_MODE_TXD_MESSAGE_CTRL ], VSEP_TXD_SDIA_SETUP ); 

#endif
}

//=============================================================================
// VSEP_MPIO_Set_Mode
//=============================================================================
void VSEP_MPIO_Set_Mode(IO_Configuration_T configuration, VSEP_MPIO_Input_Mode_T mpio_input_mode )
{
   VSEP_Channel_T  mpio_channel = VSEP_Get_Channel( configuration );

   uint16_t* txd_mode = &VSEP_MPIO_MODE_Txd[ VSEP_MPIO_MODE_TXD_MESSAGE_MODE ];
   *txd_mode = VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( *txd_mode, (mpio_channel-VSEP_CHANNEL_MPIO_1), mpio_input_mode );
}

//=============================================================================
// VSEP_MPIO_MODE_Set_Value_Immediate
//=============================================================================
void VSEP_MPIO_Set_MODE_Immediate(
   IO_Configuration_T   in_configuration, VSEP_MPIO_Input_Mode_T mpio_input_mode )
{
  
   VSEP_MPIO_Set_Mode( in_configuration, mpio_input_mode );

   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_MPIO_MODE);
}

/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
\*===========================================================================*/
