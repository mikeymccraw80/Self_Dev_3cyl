#ifndef DD_VSEP_DISCRETE_H
#define DD_VSEP_DISCRETE_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_discrete.h~4:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:42 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 11:58:39 2007 %
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

#define NUMBER_OF_VSEP (1)

typedef enum
{
                                                        // [ 6: 0] Reserved by VSEP.h
   VSEP_PCH_CONFIGURATION_POSITION_POLARITY        = 7, //      7  Polarity
   VSEP_PCH_CONFIGURATION_POSITION_INITIAL_STATE   = 8, //      8  Initial State
   VSEP_MPIO_CONFIGURATION_POSITION_INPUT_MODE     = 9  // [10: 9]  MPIO Input mode
}VSEP_PCH_Configuration_Position_T;

typedef enum
{
                                                        // [ 6: 0] Reserved by VSEP.h
   VSEP_PCH_CONFIGURATION_WIDTH_POLARITY           = 1, //      7  Polarity
   VSEP_PCH_CONFIGURATION_WIDTH_INITIAL_STATE      = 1, //      8  Initial State
   VSEP_MPIO_CONFIGURATION_WIDTH_INPUT_MODE        = 2  // [10: 9]  MPIO Input mode    
}VSEP_PCH_Configuration_Width_T;

typedef enum 
{
   VSEP_PCH_CHANNEL_OUT_18,
   VSEP_PCH_CHANNEL_OUT_19,
   VSEP_PCH_CHANNEL_OUT_20,
   VSEP_PCH_CHANNEL_OUT_23,
   VSEP_PCH_CHANNEL_OUT_25,
   VSEP_PCH_CHANNEL_OUT_26,
   VSEP_PCH_CHANNEL_OUT_30,
   VSEP_PCH_CHANNEL_OUT_RESERVED,
   VSEP_PCH_CHANNEL_OUT_4,
   VSEP_PCH_CHANNEL_OUT_5,
   VSEP_PCH_CHANNEL_OUT_6,
   VSEP_PCH_CHANNEL_OUT_7,
   VSEP_PCH_CHANNEL_OUT_8,
   VSEP_PCH_CHANNEL_OUT_13,
   VSEP_PCH_CHANNEL_OUT_14,
   VSEP_PCH_CHANNEL_OUT_17,
   VSEP_PCH_CHANNEL_MPIO_1,
   VSEP_PCH_CHANNEL_MPIO_2,
   VSEP_PCH_CHANNEL_MPIO_3,
   VSEP_PCH_CHANNEL_SOHRSTEN_STAT,
   VSEP_PCH_CHANNEL_MAX
}VSEP_PCH_Channel_T;

//=============================================================================
// VSEP_PCH_Get_Polarity
//
// @func Get the configured polarity
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t IO_Polarity_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PCH_Get_Polarity( x ) \
   (IO_Polarity_T)( Extract_Bits( x, VSEP_PCH_CONFIGURATION_POSITION_POLARITY, VSEP_PCH_CONFIGURATION_WIDTH_POLARITY ) )

//=============================================================================
// VSEP_PCH_Get_Inverte_State
//
// @func Get the Inverte State from the  configured polarity
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t IO_Polarity_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PCH_Get_Inverte_State(x)\
	(VSEP_PCH_Get_Polarity( x )?false:true)
	
//=============================================================================
// VSEP_PCH_Set_Polarity
//
// @func Set the desired polarity
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm IO_Polarity_T | y | The desired polarity 
//
// @rdesc <t IO_Configuration_T> element encoded with the desired IO_Polarity_T
//
// @end
//=============================================================================
#define VSEP_PCH_Set_Polarity( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_PCH_CONFIGURATION_POSITION_POLARITY, VSEP_PCH_CONFIGURATION_WIDTH_POLARITY ) )

//=============================================================================
// VSEP_PCH_Get_Initial_State
//
// @func Get the configured initial state
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t IO_Active_State_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_PCH_Get_Initial_State( x ) \
   (IO_Active_State_T)( Extract_Bits( x, VSEP_PCH_CONFIGURATION_POSITION_INITIAL_STATE, VSEP_PCH_CONFIGURATION_WIDTH_INITIAL_STATE ) )

//=============================================================================
// VSEP_PCH_Set_Initial_State
//
// @func Set the desired initial state
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm IO_Active_State_T | y | The desired polarity 
//
// @rdesc <t IO_Configuration_T> element encoded with the desired IO_Active_State_T
//
// @end
//=============================================================================
#define VSEP_PCH_Set_Initial_State( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_PCH_CONFIGURATION_POSITION_INITIAL_STATE, VSEP_PCH_CONFIGURATION_WIDTH_INITIAL_STATE ) )

typedef enum
{
   VSEP_MPIO_NOT_USED                              =0,
   VSEP_MPIO_INPUT_MODE_DISCRETE_INPUT             =0,
   VSEP_MPIO_INPUT_MODE_EXTERNAL_DISCRETE_ENABLE   =1,
   VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT  =2,
   VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT   =3
}VSEP_MPIO_Input_Mode_T;

//=============================================================================
// VSEP_MPIO_Get_Input_Mode
//
// @func Get the configured input mode selection
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_MPIO_Input_Mode_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_MPIO_Get_Input_Mode( x ) \
   (VSEP_MPIO_Input_Mode_T)( Extract_Bits( x, VSEP_MPIO_CONFIGURATION_POSITION_INPUT_MODE, VSEP_MPIO_CONFIGURATION_WIDTH_INPUT_MODE ) )

//=============================================================================
// VSEP_MPIO_Set_Input_Mode
//
// @func Set the desired MPIO input mode selection.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @parm VSEP_MPIO_Input_Mode_T | y | The desired input mode selection
//
// @rdesc <t IO_Configuration_T> element encoded with the desired 
//    VSEP_MPIO_Input_Mode_T
//
// @end
//=============================================================================
#define VSEP_MPIO_Set_Input_Mode( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_MPIO_CONFIGURATION_POSITION_INPUT_MODE, VSEP_MPIO_CONFIGURATION_WIDTH_INPUT_MODE ) )


typedef enum
{
   VSEP_PCH_TXD_MESSAGE_CTRL,
   VSEP_PCH_TXD_MESSAGE_PCH,
   VSEP_PCH_TXD_MESSAGE_MAX
}VSEP_PCH_Txd_Message_T;

typedef enum
{
   VSEP_PCH_RXD_MESSAGE_FLT,
   VSEP_PCH_RXD_MESSAGE_MPIO,
   VSEP_PCH_RXD_MESSAGE_MAX
}VSEP_PCH_Rxd_Message_T;

extern uint16_t VSEP_PCH_Txd[VSEP_PCH_TXD_MESSAGE_MAX];
extern uint16_t VSEP_PCH_Rxd[VSEP_PCH_RXD_MESSAGE_MAX];

//=============================================================================
// VSEP_DISCRETE_Device_Initialize
//
// @func Initialize the discrete IO portion of the VSEP device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_DISCRETE_Device_Initialize(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_DISCRETE_Device_Clear
//
// @func Clear the discrete IO portion of the VSEP device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_DISCRETE_Device_Clear(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_DISCRETE_Channel_Initialize
//
// @func Initializes a specific discrete channel on the VSEP device based on 
// its configuration value passed in.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_DISCRETE_Channel_Initialize(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_DISCRETE_Channel_Clear
//
// @func Sets the VSEP discrete channel's registers back to their reset state. 
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_DISCRETE_Channel_Clear(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_DISCRETE_Get_State
//
// @func Gets the current state of the given discrete input as indicated by
// the last set state.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc state of the pin as defined by its configuration value
// @flag true | Pin is active
// @flag false | Pin is inactive
//
// @end
//=============================================================================
FAR_COS bool VSEP_DISCRETE_Get_State( 
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_DISCRETE_Get_Immediate_State
//
// @func Gets the current state of the given discrete input directly
// from the I/O port immediately ( unbuffered ).
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc state of the pin as defined by its configuration value
// @flag true | Pin is active
// @flag false | Pin is inactive
//
// @end
//=============================================================================
FAR_COS bool VSEP_DISCRETE_Get_Immediate_State( 
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_DISCRETE_Set_State
//
// @func Performs a discrete output function directly to the I/O port, 
//       may be buffered
// @comm The output will be buffered for serial device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | in_state | requested state for the pin
// @flag true | pin is active
// @flag false | pin is inactive
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_DISCRETE_Set_State(
   IO_Configuration_T in_configuration,
   bool               in_state);

//=============================================================================
// VSEP_DISCRETE_Set_Immediate_State
//
// @func Performs a discrete output function directly to the I/O port 
//       immediately (unbuffered).
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | in_state | requested state for the pin
// @flag true | pin is active
// @flag false | pin is inactive
//
// @rdesc None
//
// @end
//=============================================================================
FAR_COS void VSEP_DISCRETE_Set_Immediate_State(
   IO_Configuration_T in_configuration,
   bool               in_state);

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
FAR_COS void VSEP_DISCRETE_Toggle_State(
   IO_Configuration_T in_configuration);

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
FAR_COS void VSEP_DISCRETE_Toggle_Immediate_State(
   IO_Configuration_T in_configuration);


//=============================================================================
//MPIO Mode Input
//=============================================================================
typedef enum
{
   VSEP_MPIO_MODE_TXD_MESSAGE_CTRL,
   VSEP_MPIO_MODE_TXD_MESSAGE_MODE,
   VSEP_MPIO_MODE_TXD_MESSAGE_MAX
}VSEP_MPIO_MODE_Txd_Message_T;

extern const uint16_t VSEP_MPIO_MODE_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_MPIO_MODE_TXD_MESSAGE_MAX];

extern uint16_t VSEP_MPIO_MODE_Txd[NUMBER_OF_VSEP][VSEP_MPIO_MODE_TXD_MESSAGE_MAX];

//=============================================================================
// VSEP_MPIO_MODE_Initialize_Device
//
// @func Initialize the discrete Multi-Purpose IO of the VSEP device.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_MPIO_MODE_Initialize_Device( IO_Configuration_T in_configuration );


//=============================================================================
// VSEP_MPIO_Set_Mode
//
// @func This function will set the VSEP Multi-Purpose input channel mode by
// calling the appropriate device function.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm VSEP_MPIO_Input_Mode_T | mpio_input_mode | The multi-purpose IO input mode.
//
// @rdesc none
//
// @end
//=============================================================================
void VSEP_MPIO_Set_Mode(
   IO_Configuration_T configuration, VSEP_MPIO_Input_Mode_T mpio_input_mode );

//=============================================================================
// VSEP_MPIO_MODE_Set_Value_Immediate
//
// @func Interface function to transfer a VSEP MPIO input mode message immediately
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm VSEP_Message_T | in_message | Which VSEP message
//    to transfer.
//
// @rdesc None
//
// @end
//=============================================================================

void VSEP_MPIO_Set_MODE_Immediate(
   IO_Configuration_T   in_configuration, VSEP_MPIO_Input_Mode_T mpio_input_mode );


#endif // DD_VSEP_DISCRETE_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       *
\*===========================================================================*/
