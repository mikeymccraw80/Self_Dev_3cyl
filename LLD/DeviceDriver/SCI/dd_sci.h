#ifndef DD_SCI_H
#define DD_SCI_H
//==============================================================================
//
//         COPYRIGHT, 2002, DELPHI TECHNOLOGIES, INC. ALL RIGHTS RESERVED
//                                  Delphi Confidential
//
// ============================================================================

//==============================================================================
//    Include Files
//==============================================================================
#include "hw_sci.h"

//==============================================================================
//   Exported Type Declarations (enum, struct, union, typedef)
//==============================================================================
typedef enum
{
   SCI_INTERRUPT_CHANNEL_RX,
   SCI_INTERRUPT_CHANNEL_TX_COMPLETE,
   SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY,
   SCI_INTERRUPT_CHANNEL_IDLE_LINE,
   SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR,
   SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR,
   SCI_INTERRUPT_CHANNEL_FRAME_ERROR,
   SCI_INTERRUPT_CHANNEL_PARITY_ERROR,
   SCI_INTERRUPT_CHANNEL_MAX

} SCI_Interrupt_Channel_T;

// SCI module selection
typedef enum
{
   SCI_INDEX_A,
   SCI_INDEX_B,
   SCI_INDEX_MAX

}  SCI_Index_T;

// Select loop operation MODE
typedef enum
{
   SCI_NO_LOOPBACK,
   SCI_LOOPBACK_ON_INTERNAL_CONNECT,
   SCI_LOOPBACK_ON_EXTERNAL_CONNECT

} SCI_Loopback_Mode_T;

// Select data character length
typedef enum
{
   SCI_DATA_BITS_8_BIT,
   SCI_DATA_BITS_9_BIT

} SCI_Data_Bits_T;

// Select wake-up condition
typedef enum
{
   SCI_WAKEUP_MODE_IDLE_LINE,
   SCI_WAKEUP_MODE_ADDRESS_MARK

} SCI_Wakeup_Mode_T;

// Select idle line type
typedef enum
{
   SCI_IDLE_LINE_TYPE_AFTER_START_BIT,
   SCI_IDLE_LINE_TYPE_AFTER_STOP_BIT

} SCI_Idle_Line_Type_T;

typedef enum
{
   SCI_SAMPLE_RT_CLOCK_9,
   SCI_SAMPLE_RT_CLOCK_13

} SCI_Sample_RT_Clock_T;

// Select parity type
typedef enum
{
   SCI_PARITY_NONE,
   SCI_PARITY_RESERVED,
   SCI_PARITY_EVEN,
   SCI_PARITY_ODD

} SCI_Parity_T;

typedef enum
{
   SCI_BIT_ERROR_STOP_DISABLE,
   SCI_BIT_ERROR_STOP_ENABLE

} SCI_Bit_Error_Stop_T;

// Select bit error detection mode
typedef enum
{
   SCI_FAST_BIT_ERROR_MODE_OFF,  // bit error detection per byte
   SCI_FAST_BIT_ERROR_MODE_ON    // bit error detection per bit

} SCI_Fast_Bit_Error_Mode_T;

typedef enum
{
   SCI_BREAK_BIT_MODE_10_11_BITS,
   SCI_BREAK_BIT_MODE_13_14_BITS

} SCI_Break_Bit_Mode_T;

typedef enum
{
   SCI_WUD_4_BIT_TIME,
   SCI_WUD_8_BIT_TIME,
   SCI_WUD_32_BIT_TIME,
   SCI_WUD_64_BIT_TIME

} SCI_Wakeup_Delimiter_Mode_T;

// @enum SCI_Configuration_Position_T | The SCI global configuration
typedef enum
{
   SCI_CONFIGURATION_POSITION_INDEX = 0   // 0   SCI Device

} SCI_Configuration_Position_T;

// @enum SCI_Configuration_Width_T | The SCI global configuration
typedef enum
{
   SCI_CONFIGURATION_WIDTH_INDEX    = 2   // 0   SCI Device

} SCI_Configuration_Width_T;

// @enum SCI_Interrupt_Configuration_Position_T | The SCI interupt configuration
typedef enum
{
                                                     //[ 12: 0 ] Reserved for INTC
                                                     //     13   Reserved for SCI Device
   SCI_INTERRUPT_CONFIGURATION_POSITION_CHANNEL = 14 //[ 16:14 ] Interrupt channel 
}SCI_Interrupt_Configuration_Position_T;

// @enum SCI_Interrupt_Configuration_Width_T | The SCI interupt configuration
typedef enum
{
                                                      //[ 12: 0 ] Reserved for INTC
                                                      //     13   Reserved for SCI Device 
   SCI_INTERRUPT_CONFIGURATION_WIDTH_CHANNEL    = 3   //[ 16:14 ] Interrupt channel
}SCI_Interrupt_Configuration_Width_T;

//=============================================================================
// SCI_Set_Index
//
// @func Set SCI Index
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm SCI_Index_T | y | A <t SCI_Index_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Index_T>
//
// @end
//=============================================================================
#define SCI_Set_Index( x, y ) \
   (IO_Configuration_T)(Insert_Bits( x, y, SCI_CONFIGURATION_POSITION_INDEX, SCI_CONFIGURATION_WIDTH_INDEX ) )

//=============================================================================
// SCI_Get_Index
//
// @func Get SCI Index
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Index_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Get_Index( x ) \
   (SCI_Index_T)(Extract_Bits( x, SCI_CONFIGURATION_POSITION_INDEX, SCI_CONFIGURATION_WIDTH_INDEX ) )

//=============================================================================
// SCI_Interrupt_Set_Channel
//
// @func Set desired SCI interrupt Channel 
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm SCI_Interrupt_Channel_T | y | A <t SCI_Interrupt_Channel_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Interrupt_Channel_T>
//
// @end
//=============================================================================
#define SCI_Interrupt_Set_Channel( x, y ) \
   (IO_Configuration_T)(Insert_Bits( x, y, SCI_INTERRUPT_CONFIGURATION_POSITION_CHANNEL, SCI_INTERRUPT_CONFIGURATION_WIDTH_CHANNEL ) )

//=============================================================================
// SCI_Interrupt_Get_Channel
//
// @func Get the configured SCI interrupt channel
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Interrupt_Channel_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Interrupt_Get_Channel( x ) \
   (SCI_Interrupt_Channel_T)(Extract_Bits( x, SCI_INTERRUPT_CONFIGURATION_POSITION_CHANNEL, SCI_INTERRUPT_CONFIGURATION_WIDTH_CHANNEL ) )

// @enum SCI_Device_Configuration_Position_T | The SCI Device Configuration
typedef enum
{
                                                                   // @emem   [1:0]   SCI Device 
   SCI_DEVICE_CONFIGURATION_POSITION_DATA_FORMAT             = 2,  // @emem       2   M - Data format
   SCI_DEVICE_CONFIGURATION_POSITION_WAKE_UP_CONDITION       = 3,  // @emem       3   WAKE - Wakeup condition
   SCI_DEVICE_CONFIGURATION_POSITION_IDLE_LINE_TYPE          = 4,  // @emem       4   ILT - Idle Line Type
   SCI_DEVICE_CONFIGURATION_POSITION_FAST_BIT_ERROR_DETECT   = 5,  // @emem       5   FBR - Fast Bit Error Detect
   SCI_DEVICE_CONFIGURATION_POSITION_PHYSICAL_BUS_ERROR_STOP = 6,  // @emem       6   BSTP - Bit Error/Physical Bus Error Stop
   SCI_DEVICE_CONFIGURATION_POSITION_BREAK_LENGTH            = 7,  // @emem       7   BRK13 - Break Transmit Character Length
   SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_SAMPLE_MODE   = 8,  // @emem       8   BESM13 - Bit Error Sample Mode
   SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_STOP          = 9,  // @emem       9   SBSTP - Bit Error Stop
   SCI_DEVICE_CONFIGURATION_POSITION_PARITY                  = 10   // @emem [ 11: 10 ] PE/PT - Parity Enable and Parity Type

} SCI_Device_Configuration_Position_T;

// @enum SCI_Device_Configuration_Width_T | The SCI Device Configuration
typedef enum
{
                                                                   // @emem   [1:0]   SCI Device 
   SCI_DEVICE_CONFIGURATION_WIDTH_DATA_FORMAT                = 1,  // @emem       2   M - Data format
   SCI_DEVICE_CONFIGURATION_WIDTH_WAKE_UP_CONDITION          = 1,  // @emem       3   WAKE - Wakeup condition
   SCI_DEVICE_CONFIGURATION_WIDTH_IDLE_LINE_TYPE             = 1,  // @emem       4   ILT - Idle Line Type
   SCI_DEVICE_CONFIGURATION_WIDTH_FAST_BIT_ERROR_DETECT      = 1,  // @emem       5   FBR - Fast Bit Error Detect
   SCI_DEVICE_CONFIGURATION_WIDTH_PHYSICAL_BUS_ERROR_STOP    = 1,  // @emem       6   BSTP - Bit Error/Physical Bus Error Stop
   SCI_DEVICE_CONFIGURATION_WIDTH_BREAK_LENGTH               = 1,  // @emem       7   BRK13 - Break Transmit Character Length
   SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_SAMPLE_MODE      = 1,  // @emem       8   BESM13 - Bit Error Sample Mode
   SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_STOP             = 1,  // @emem       9   SBSTP - Bit Error Stop
   SCI_DEVICE_CONFIGURATION_WIDTH_PARITY                     = 2   // @emem [ 11: 10 ] PE/PT - Parity Enable and Parity Type

} SCI_Device_Configuration_Width_T;

//==============================================================================
//     Configuration Macros for creating SCI device configuration
//==============================================================================
//=============================================================================
// SCI_Device_Set_Data_Format
//
// @func Set desired SCI serial data format 
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm SCI_Data_Bits_T | data_format | A <t SCI_Data_Bits_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Data_Bits_T>
//
// @end
//=============================================================================
#define SCI_Device_Set_Data_Format( configuration, data_format ) \
   (IO_Configuration_T)(Insert_Bits( configuration, data_format, SCI_DEVICE_CONFIGURATION_POSITION_DATA_FORMAT, SCI_DEVICE_CONFIGURATION_WIDTH_DATA_FORMAT ) )

//=============================================================================
// SCI_Device_Get_Data_Format
//
// @func Get the configured SCI serial data format
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Data_Bits_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Data_Format( configuration ) \
   (SCI_Data_Bits_T)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_DATA_FORMAT, SCI_DEVICE_CONFIGURATION_WIDTH_DATA_FORMAT ) )

//=============================================================================
// SCI_Device_Set_Wakeup_Mode
//
// @func Set desired SCI wakeup mode 
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm SCI_Wakeup_Mode_T | mode | A <t SCI_Wakeup_Mode_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Wakeup_Mode_T>
//
// @end
//=============================================================================
#define SCI_Device_Set_Wakeup_Mode( configuration, mode ) \
   (IO_Configuration_T)(Insert_Bits( configuration, mode, SCI_DEVICE_CONFIGURATION_POSITION_WAKE_UP_CONDITION, SCI_DEVICE_CONFIGURATION_WIDTH_WAKE_UP_CONDITION ) )

//=============================================================================
// SCI_Device_Get_Wakeup_Mode
//
// @func Get the configured SCI wakeup mode
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Wakeup_Mode_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Wakeup_Mode( configuration ) \
   (SCI_Wakeup_Mode_T)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_WAKE_UP_CONDITION, SCI_DEVICE_CONFIGURATION_WIDTH_WAKE_UP_CONDITION ) )

//=============================================================================
// SCI_Device_Set_Idle_Line_Type
//
// @func Set desired SCI idle line type 
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm SCI_Idle_Line_Type_T | type | A <t SCI_Idle_Line_Type_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Idle_Line_Type_T>
//
// @end
//=============================================================================
#define SCI_Device_Set_Idle_Line_Type( configuration, type ) \
   (IO_Configuration_T)(Insert_Bits( configuration, type, SCI_DEVICE_CONFIGURATION_POSITION_IDLE_LINE_TYPE, SCI_DEVICE_CONFIGURATION_WIDTH_IDLE_LINE_TYPE ) )

//=============================================================================
// SCI_Device_Get_Idle_Line_Type
//
// @func Get the configured SCI idle line type
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Idle_Line_Type_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Idle_Line_Type( configuration ) \
   (SCI_Idle_Line_Type_T)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_IDLE_LINE_TYPE, SCI_DEVICE_CONFIGURATION_WIDTH_IDLE_LINE_TYPE ) )

//=============================================================================
// SCI_Device_Set_Fast_Bit_Error_Mode
//
// @func Set desired SCI fast bit error mode
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm SCI_Fast_Bit_Error_Mode_T | mode | A <t SCI_Fast_Bit_Error_Mode_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Fast_Bit_Error_Mode_T>
//
// @end
//=============================================================================
#define SCI_Device_Set_Fast_Bit_Error_Mode( configuration, mode ) \
   (IO_Configuration_T)(Insert_Bits( configuration, mode, SCI_DEVICE_CONFIGURATION_POSITION_FAST_BIT_ERROR_DETECT, SCI_DEVICE_CONFIGURATION_WIDTH_FAST_BIT_ERROR_DETECT ) )

//=============================================================================
// SCI_Device_Get_Fast_Bit_Error_Mode
//
// @func Get the configured SCI  fast bit error mode
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Fast_Bit_Error_Mode_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Fast_Bit_Error_Mode( configuration ) \
   (SCI_Fast_Bit_Error_Mode_T)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_FAST_BIT_ERROR_DETECT, SCI_DEVICE_CONFIGURATION_WIDTH_FAST_BIT_ERROR_DETECT ) )

//=============================================================================
// SCI_Device_Set_Bit_Bus_Error_Stop
//
// @func Set desired SCI bit bus error stop
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm bool | enable | true or false
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define SCI_Device_Set_Bit_Bus_Error_Stop( configuration, enable ) \
   (IO_Configuration_T)(Insert_Bits( configuration, enable, SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_STOP, SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_STOP ) )

//=============================================================================
// SCI_Device_Get_Bit_Bus_Error_Stop
//
// @func Get the configured SCI bit bus error stop
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Bit_Bus_Error_Stop( configuration ) \
   (bool)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_STOP, SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_STOP ) )

//=============================================================================
// SCI_Device_Set_Bit_Bus_Error_Stop
//
// @func Set desired SCI break length
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm SCI_Break_Bit_Mode_T | length | A <t SCI_Break_Bit_Mode_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Break_Bit_Mode_T>
//
// @end
//=============================================================================
#define SCI_Device_Set_Break_Length( configuration, length ) \
   (IO_Configuration_T)(Insert_Bits( configuration, length, SCI_DEVICE_CONFIGURATION_POSITION_BREAK_LENGTH, SCI_DEVICE_CONFIGURATION_WIDTH_BREAK_LENGTH ) )

//=============================================================================
// SCI_Device_Get_Bit_Bus_Error_Stop
//
// @func Get the configured SCI break length
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Break_Bit_Mode_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Break_Length( configuration ) \
   (SCI_Break_Bit_Mode_T)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_BREAK_LENGTH, SCI_DEVICE_CONFIGURATION_WIDTH_BREAK_LENGTH ) )

//=============================================================================
// SCI_Device_Set_Bit_Error_Sample_Mode
//
// @func Set desired SCI bit error sample mode
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm SCI_Sample_RT_Clock_T | mode | A <t SCI_Sample_RT_Clock_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Sample_RT_Clock_T>
//
// @end
//=============================================================================
#define SCI_Device_Set_Bit_Error_Sample_Mode( configuration, mode ) \
   (IO_Configuration_T)(Insert_Bits( configuration, mode, SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_SAMPLE_MODE, SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_SAMPLE_MODE ) )

//=============================================================================
// SCI_Device_Get_Bit_Error_Sample_Mode
//
// @func Get the configured SCI bit error sample mode
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Sample_RT_Clock_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Bit_Error_Sample_Mode( configuration ) \
   (SCI_Sample_RT_Clock_T)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_SAMPLE_MODE, SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_SAMPLE_MODE ) )

//=============================================================================
// SCI_Device_Set_Bit_Error_Stop
//
// @func Set desired SCI bit error stop mode
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm bool | enable | true or false
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define SCI_Device_Set_Bit_Error_Stop( configuration, enable ) \
   (IO_Configuration_T)(Insert_Bits( configuration, enable, SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_STOP, SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_STOP ) )

//=============================================================================
// SCI_Device_Get_Bit_Error_Stop
//
// @func Get the configured SCI bit stop mode
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Bit_Error_Stop( configuration ) \
   (bool)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_BIT_ERROR_STOP, SCI_DEVICE_CONFIGURATION_WIDTH_BIT_ERROR_STOP ) )

//=============================================================================
// SCI_Device_Set_Parity
//
// @func Set desired SCI parity mode
//
// @parm IO_Configuration_T | configuration | The value of the configuration prior to modification
//
// @parm SCI_Parity_T | type | A <t SCI_Parity_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t SCI_Parity_T>
//
// @end
//=============================================================================
#define SCI_Device_Set_Parity( configuration, type ) \
   (IO_Configuration_T)(Insert_Bits( configuration, type, SCI_DEVICE_CONFIGURATION_POSITION_PARITY, SCI_DEVICE_CONFIGURATION_WIDTH_PARITY ) )

//=============================================================================
// SCI_Device_Get_Parity
//
// @func Get the configured SCI parity mode
//
// @parm IO_Configuration_T | configuration | A <t IO_Configuration_T> type
//
// @rdesc <t SCI_Parity_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define SCI_Device_Get_Parity( configuration ) \
   (SCI_Parity_T)(Extract_Bits( configuration, SCI_DEVICE_CONFIGURATION_POSITION_PARITY, SCI_DEVICE_CONFIGURATION_WIDTH_PARITY ) )


//==============================================================================
//    external variables
//==============================================================================
extern const uint32_t SCI_FREQUENCY_HZ;

#define SECTION_SCI_A_REGISTER
#include "section.h"
extern SCI_T SCI_A;      // SCI_A base address 0xFFFB0000
#define SECTION_END
#include "section.h"

#define SECTION_SCI_B_REGISTER
#include "section.h"
extern SCI_T SCI_B;      // SCI_B base address 0xFFFB4000
#define SECTION_END
#include "section.h"

//==============================================================================
//    Function Prototypes
//==============================================================================
//==============================================================================
// SCI_Get_Device_Register
//
// @func Returns pointer to a SCI structure based on a configuration word
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc SCI_T * | pointer to a SCI structure - &SCI_A / &SCI_B
//
// @end
//
//==============================================================================
SCI_T* SCI_Get_Device_Register( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Set_Speed
//
// @func Sets eSCIx CR1 SBR (baud rate) bits
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @parm uint32_t | in_speed | [in] requested baud rate
//
// @rdesc bool | Returns true
//
// @end
//
//==============================================================================
bool SCI_Set_Speed( 
   IO_Configuration_T in_configuration, 
   uint32_t           in_speed );

//==============================================================================
// SCI_Get_Speed
//
// @func Returns SCI baud rate
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc uint32_t | Baud rate
//
// @end
//
//==============================================================================
uint32_t SCI_Get_Speed( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Get_Loopback_Mode_Enabled
//
// @func Returns loopback mode enable bit status
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc SCI_Loopback_Mode_T | Loop mode - SCI_NO_LOOP = 0 / SCI_LOOP_OPERATION = 1
//
// @end
//
//==============================================================================
SCI_Loopback_Mode_T SCI_Get_Loopback_Mode_Enabled( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Read
//
// @func Returns one byte received data
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc uint16_t | Received byte
//
// @end
//
//==============================================================================
uint16_t SCI_Read( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Write
//
// @func Sets eSCI DR to the desired value.
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @parm uint16_t | in_data | [in] data byte
//
// @end
//
//==============================================================================
void SCI_Write( 
   IO_Configuration_T in_configuration, 
   uint16_t           in_data );

//==============================================================================
// SCI_Get_Interrupt_Enable
///
// @func If any SCI interrupt enable is set, returns true.
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc bool | Interrupt enable status
//
// @end
//
//==============================================================================
bool SCI_Get_Interrupt_Enable( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Set_Interrupt_Enable
//
// @func Set SCI Rx, Tx buffer empty, and Tx complete interrupt enables to the
//    value in_state
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @parm bool | in_state | [in] Interrupt enable set value - true / false
//
// @rdesc bool | Previous interrupt enable setting - true / false
//
// @end
//
//==============================================================================
bool SCI_Set_Interrupt_Enable( 
   IO_Configuration_T in_configuration,
   bool               in_state );

//==============================================================================
// SCI_Set_Wake_Up_Enable
//
// @func Enables wake-up function and inhibits further rx interrup0t request
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @end
//
//==============================================================================
void SCI_Set_Wake_Up_Enable(
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Get_Rx_Error_Flag
//
// @func If any error flag from OR, NF, FE or PF is set, returns true.
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc bool | SCI receiver error status - true / false
//
// @end
//
//==============================================================================
bool SCI_Get_Rx_Error_Flag( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Get_Status
//
// @func Returns status of a flag in SR
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @parm SCI_Interrupt_Channel_T | in_flag_id | [in] interrupt channel id
//
// @rdesc bool | status of a control flag
//
// @end
//
//==============================================================================
bool SCI_Get_Status( 
   IO_Configuration_T      in_configuration, 
   SCI_Interrupt_Channel_T in_flag_id );
   
//==============================================================================
// SCI_Get_Active_Status
//
// @func Returns status of a flag in SR
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc bool | status of active flag
//
// @end
//
//==============================================================================
bool SCI_Get_Active_Status(IO_Configuration_T      in_configuration);

//==============================================================================
// SCI_Reset_Status
//
// @func Reset a status flag in SR
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @parm SCI_Interrupt_Channel_T | in_flag_id | [in] interrupt channel id
//
// @end
//
//==============================================================================
void SCI_Reset_Status( 
   IO_Configuration_T      in_configuration, 
   SCI_Interrupt_Channel_T in_flag_id );

//==============================================================================
// SCI_Send_Single_Break
//
// @func Sends a single break character for the requested sci module.
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @end
//
//==============================================================================
void SCI_Send_Single_Break( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Shutdown_Device
//
// @func Stop SCI operation
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @rdesc bool | Returns true
//
// @end
//
//==============================================================================
bool SCI_Shutdown_Device( 
   IO_Configuration_T in_configuration );

//==============================================================================
// SCI_Configure_Device
//
// @func Initialize and start a SCI device 
//
// @parm IO_Configuration_T | in_configuration | [in] SCI configuration
//
// @parm SCI_Loopback_Mode_T | in_loopback | [in] SCI loopback enable
//
// @end
//
//==============================================================================
void SCI_Configure_Device(
   IO_Configuration_T   in_configuration,
   SCI_Loopback_Mode_T  in_loopback );

//==============================================================================
// SCI_Clear_Device
//
// @func Reset the SCI module to its reset state
//
// @parm IO_Configuration_T | in_configuration | [in] SCI port configuration
//
// @end
//
//==============================================================================
void SCI_Clear_Device( 
   IO_Configuration_T in_configuration );

#endif // DD_SCI_H
