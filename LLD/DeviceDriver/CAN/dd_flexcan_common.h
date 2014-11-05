#ifndef DD_FLEXCAN_COMMON_H
#define DD_FLEXCAN_COMMON_H
//=============================================================================
//
//       COPYRIGHT, 2005, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_flexcan_common.h~kok_pt2#15:incl:kok_toy#1 %
//
// created_by:       gzdmlz
//
// date_created:     Fri Jan 13 22:58:37 2006
//
// %derived_by:      hz1swt %
//
// %date_modified:   Mon Apr 16 09:41:17 2012 %
//
// %version:         kok_pt2#15 %
//
// ============================================================================
// ============================================================================
// Configurable Development Software Module:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================
#include "hw_flexcan.h"
#include "io_type.h"

// CAN bit related constants
#define CAN_REGISTER_SET_ALL_BITS          0xFFFFFFFF
#define CAN_INT_REGISTER_BYTE_NUM          4
#define CAN_INT_FLAG_MSB                   7
#define CAN_INT_REGISTER_BIT_NUM           32
#define FLEXCAN_STD_ID_SHIFT               ((uint8_t)18)
#define FLEXCAN_MSGBUF_TX (0x8)

// CAN Dynamic initialization Table
typedef struct
{
   uint32_t Separate_Message_Mask14;
   uint32_t Separate_Message_Mask15;
   uint32_t Global_Message_Mask;
   uint16_t RJW;
   uint8_t  Time_Segment_1;
   uint8_t  Time_Segment_2;
   uint8_t  Bit_Rate;
   bool     Clk_Src;

} FlexCAN_Init_Table_T;
//=============================================================================
// @enum FlexCAN Device Index
//=============================================================================
typedef enum
{
   FLEXCAN_DEVICE_A,  // @emem FlexCAN A
   FLEXCAN_DEVICE_B,  // @emem FlexCAN B
   FLEXCAN_DEVICE_C,  // @emem FlexCAN C
   FLEXCAN_DEVICE_D,  // @emem FlexCAN D
   FLEXCAN_DEVICE_E,  // @emem FlexCAN D
   FLEXCAN_DEVICE_MAX
} FlexCAN_Index_T;

typedef enum
{
   FLEXCAN_OSCILLATOR_CLOCK, // @emem Oscillator clock
   FLEXCAN_SYSTEM_CLOCK      // @emem System Clock
} FlexCAN_CLOCK_T;

typedef enum
{
   FLEXCAN_SAMPLE_MODE_ONE,  // @emem One Sample Mode
   FLEXCAN_SAMPLE_MODE_THREE // @emem Three Sample Mode
} FlexCAN_SAMPLE_MODE_T;

typedef enum
{
   FLEXCAN_LOWEST_ID_FIRST, // @emem Transmit Lowest ID first
   FLEXCAN_BUFFER_NO_FIRST  // @emem Transmit lowest buffer no first
} FlexCAN_TX_PRIORITY_T;

typedef enum
{
   FLEXCAN_MODE_RX,       // @emem RX Interrupt
   FLEXCAN_MODE_TX,       // @emem TX Interrupt
   FLEXCAN_MODE_ERROR     // @emem Error Interrupt
} FlexCAN_INTERRUPT_MODE_T;
//=============================================================================
// @enum FlexCAN Device Configuration Position
//=============================================================================
typedef enum
{
   FLEXCAN_CONFIGURATION_POSITION_INDEX        = 0,  //@emem [ 1: 0] FlexCAN Device Index
   FLEXCAN_CONFIGURATION_POSITION_MDIS         = 3,  //@emem    3    FlexCAN Module disable
   FLEXCAN_CONFIGURATION_POSITION_FRZ          = 4,  //@emem    4    FlexCAN Freeze Mode
   FLEXCAN_CONFIGURATION_POSITION_BOFFMSK      = 5,  //@emem    5    FlexCAN Bus off Mask
   FLEXCAN_CONFIGURATION_POSITION_ERRMSK       = 6,  //@emem    6    FlexCAN Error Mask
   FLEXCAN_CONFIGURATION_POSITION_CLK_SRC      = 7,  //@emem    7    FlexCAN Clock Source
   FLEXCAN_CONFIGURATION_POSITION_LPB          = 8,  //@emem    8    FlexCAN Loop back Mode
   FLEXCAN_CONFIGURATION_POSITION_SMP          = 9,  //@emem    9    FlexCAN Sample Mode
   FLEXCAN_CONFIGURATION_POSITION_BOFFREC      = 10,  //@emem    10    FlexCAN Bus off Recovery
   FLEXCAN_CONFIGURATION_POSITION_TSYN         = 11, //@emem    11   FlexCAN Timer Sync Mode
   FLEXCAN_CONFIGURATION_POSITION_LBUF         = 12, //@emem    12   FlexCAN Tx priority
   FLEXCAN_CONFIGURATION_POSITION_LOM          = 13, //@emem    13   FlexCAN Listen Only Mode
   FLEXCAN_CONFIGURATION_POSITION_MAXMB        = 14  //@emem [19:14] FlexCAN Message Buffer Size
}FlexCAN_Configuration_Position_T;

typedef enum
{
   FLEXCAN_CONFIGURATION_WIDTH_INDEX        = 3, //@emem [ 1: 0] FlexCAN Device Index
   FLEXCAN_CONFIGURATION_WIDTH_MDIS         = 1, //@emem    2    FlexCAN Module disable
   FLEXCAN_CONFIGURATION_WIDTH_FRZ          = 1, //@emem    3    FlexCAN Freeze Mode
   FLEXCAN_CONFIGURATION_WIDTH_BOFFMSK      = 1, //@emem    4    FlexCAN Bus off Mask
   FLEXCAN_CONFIGURATION_WIDTH_ERRMSK       = 1, //@emem    5    FlexCAN Error Mask
   FLEXCAN_CONFIGURATION_WIDTH_CLK_SRC      = 1, //@emem    6    FlexCAN Clock Source
   FLEXCAN_CONFIGURATION_WIDTH_LPB          = 1, //@emem    7    FlexCAN Loop back Mode
   FLEXCAN_CONFIGURATION_WIDTH_SMP          = 1, //@emem    8    FlexCAN Sample Mode
   FLEXCAN_CONFIGURATION_WIDTH_BOFFREC      = 1, //@emem    9    FlexCAN Bus off Recovery
   FLEXCAN_CONFIGURATION_WIDTH_TSYN         = 1, //@emem    10   FlexCAN Timer Sync Mode
   FLEXCAN_CONFIGURATION_WIDTH_LBUF         = 1, //@emem    11   FlexCAN Tx priority
   FLEXCAN_CONFIGURATION_WIDTH_LOM          = 1, //@emem    12   FlexCAN Listen Only Mode
   FLEXCAN_CONFIGURATION_WIDTH_MAXMB        = 6  //@emem [19:14] FlexCAN Message Buffer Size
}FlexCAN_Configuration_Width_T;
//=============================================================================
// FlexCAN_Set_Index
//
// @func Set FlexCAN Device Index configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_Index_T | index | A <t FlexCAN_Index_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_Index_T>
//
// @end
//=============================================================================
#define FlexCAN_Set_Index(config,index) \
   (IO_Configuration_T)( Insert_Bits( config, index, FLEXCAN_CONFIGURATION_POSITION_INDEX, FLEXCAN_CONFIGURATION_WIDTH_INDEX ) )
//=============================================================================
// FlexCAN_Get_Index
//
// @func Get FlexCAN Device Index configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_Index_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Index(config) \
   (FlexCAN_Index_T)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_INDEX, FLEXCAN_CONFIGURATION_WIDTH_INDEX ) )
//=============================================================================
// FlexCAN_Set_Module_Disable
//
// @func Set FlexCAN Device ModuleDisable configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | status | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Module_Disable(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MDIS, FLEXCAN_CONFIGURATION_WIDTH_MDIS ) )
//=============================================================================
// FlexCAN_Get_Module_Disable
//
// @func Get FlexCAN Device ModuleDisable configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Module_Disable(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MDIS, FLEXCAN_CONFIGURATION_WIDTH_MDIS ) )
//=============================================================================
// FlexCAN_Set_Freeze_Mode
//
// @func Set FlexCAN Device FreezeMode configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | mode | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Freeze_Mode(config,mode) \
   (IO_Configuration_T)( Insert_Bits( config, mode, FLEXCAN_CONFIGURATION_POSITION_FRZ, FLEXCAN_CONFIGURATION_WIDTH_FRZ ) )
//=============================================================================
// FlexCAN_Get_Freeze_Mode
//
// @func Get FlexCAN Device FreezeMode configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Freeze_Mode(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_FRZ, FLEXCAN_CONFIGURATION_WIDTH_FRZ ) )
//=============================================================================
// FlexCAN_Set_BusOff_Mask
//
// @func Set FlexCAN Device BusOff_Mask configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | status | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_BusOff_Mask(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_BOFFMSK, FLEXCAN_CONFIGURATION_WIDTH_BOFFMSK ) )
//=============================================================================
// FlexCAN_Get_BusOff_Mask
//
// @func Get FlexCAN Device BusOff_Mask configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_BusOff_Mask(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_BOFFMSK, FLEXCAN_CONFIGURATION_WIDTH_BOFFMSK ) )
//=============================================================================
// FlexCAN_Set_Error_Mask
//
// @func Set FlexCAN Device Error_Mask configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | status | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Error_Mask(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_ERRMSK, FLEXCAN_CONFIGURATION_WIDTH_ERRMSK ) )
//=============================================================================
// FlexCAN_Get_BusOff_Mask
//
// @func Get FlexCAN Device Error_Mask configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Error_Mask(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_ERRMSK, FLEXCAN_CONFIGURATION_WIDTH_ERRMSK ) )
//=============================================================================
// FlexCAN_Set_Clock_Source
//
// @func Set FlexCAN Device ClockSource configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_CLOCK_T | clock | A <t FlexCAN_CLOCK_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_CLOCK_T>
//
// @end
//=============================================================================
#define FlexCAN_Set_Clock_Source(config,clock) \
   (IO_Configuration_T)( Insert_Bits( config, clock, FLEXCAN_CONFIGURATION_POSITION_CLK_SRC, FLEXCAN_CONFIGURATION_WIDTH_CLK_SRC ) )
//=============================================================================
// FlexCAN_Get_Clock_Source
//
// @func Get FlexCAN Device ClockSource configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_CLOCK_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Clock_Source(config) \
   (FlexCAN_CLOCK_T)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_CLK_SRC, FLEXCAN_CONFIGURATION_WIDTH_CLK_SRC ) )
//=============================================================================
// FlexCAN_Set_Sample_Mode
//
// @func Set FlexCAN Device SampleMode configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_SAMPLE_MODE_T | mode | A <t FlexCAN_SAMPLE_MODE_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_SAMPLE_MODE_T>
//
// @end
//=============================================================================
#define FlexCAN_Set_Sample_Mode(config,mode) \
   (IO_Configuration_T)( Insert_Bits( config, mode, FLEXCAN_CONFIGURATION_POSITION_SMP, FLEXCAN_CONFIGURATION_WIDTH_SMP ) )
//=============================================================================
// FlexCAN_Get_Sample_Mode
//
// @func Get FlexCAN Device SampleMode configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_SAMPLE_MODE_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Sample_Mode(config) \
   (FlexCAN_SAMPLE_MODE_T)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_SMP, FLEXCAN_CONFIGURATION_WIDTH_SMP ) )
//=============================================================================
// FlexCAN_Set_Loop_Back_Mode
//
// @func Set FlexCAN Device LoopBack_Mode configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | mode | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Loop_Back_Mode(config,mode) \
   (IO_Configuration_T)( Insert_Bits( config, mode, FLEXCAN_CONFIGURATION_POSITION_LPB, FLEXCAN_CONFIGURATION_WIDTH_LPB ) )
//=============================================================================
// FlexCAN_Get_Loop_Back_Mode
//
// @func Get FlexCAN Device LoopBack_Mode configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Loop_Back_Mode(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_LPB, FLEXCAN_CONFIGURATION_WIDTH_LPB ) )
//=============================================================================
// FlexCAN_Set_BusOff_Recovery
//
// @func Set FlexCAN Device BusOff_Recovery configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | mode | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_BusOff_Recovery(config,mode) \
   (IO_Configuration_T)( Insert_Bits( config, mode, FLEXCAN_CONFIGURATION_POSITION_BOFFREC, FLEXCAN_CONFIGURATION_WIDTH_BOFFREC ) )
//=============================================================================
// FlexCAN_Get_BusOff_Recovery
//
// @func Get FlexCAN Device BusOff_Recovery configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_BusOff_Recovery(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_BOFFREC, FLEXCAN_CONFIGURATION_WIDTH_BOFFREC ) )
//=============================================================================
// FlexCAN_Set_Timer_Sync_Mode
//
// @func Set FlexCAN Device Timer_Sync_Mode configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | mode | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Timer_Sync_Mode(config,mode) \
   (IO_Configuration_T)( Insert_Bits( config, mode, FLEXCAN_CONFIGURATION_POSITION_TSYN, FLEXCAN_CONFIGURATION_WIDTH_TSYN ) )
//=============================================================================
// FlexCAN_Get_Timer_Sync_Mode
//
// @func Get FlexCAN Device TimerSync_Mode configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Timer_Sync_Mode(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_TSYN, FLEXCAN_CONFIGURATION_WIDTH_TSYN ) )
//=============================================================================
// FlexCAN_Set_Tx_Priority_Mode
//
// @func Set FlexCAN Device TxPriority configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_TX_PRIORITY_T | mode | A <t FlexCAN_TX_PRIORITY_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_TX_PRIORITY_T>
//
// @end
//=============================================================================
#define FlexCAN_Set_Tx_Priority_Mode(config,mode) \
   (IO_Configuration_T)( Insert_Bits( config, mode, FLEXCAN_CONFIGURATION_POSITION_LBUF, FLEXCAN_CONFIGURATION_WIDTH_LBUF ) )
//=============================================================================
// FlexCAN_Get_Tx_Priority_Mode
//
// @func Get FlexCAN Device TimerSync_Mode configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_TX_PRIORITY_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Tx_Priority_Mode(config) \
   (FlexCAN_TX_PRIORITY_T)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_LBUF, FLEXCAN_CONFIGURATION_WIDTH_LBUF ) )
//=============================================================================
// FlexCAN_Set_Listen_Only_Mode
//
// @func Set FlexCAN Device ListenOnly configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | mode | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Listen_Only_Mode(config,mode) \
   (IO_Configuration_T)( Insert_Bits( config, mode, FLEXCAN_CONFIGURATION_POSITION_LOM, FLEXCAN_CONFIGURATION_WIDTH_LOM ) )
//=============================================================================
// FlexCAN_Get_Listen_Only_Mode
//
// @func Get FlexCAN Device ListenOnly configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Listen_Only_Mode(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_LOM, FLEXCAN_CONFIGURATION_WIDTH_LOM ) )
//=============================================================================
// FlexCAN_Set_Message_Buffer_Size
//
// @func Set FlexCAN Device Message_Buffer_Size configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | size | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_Message_Buffer_Size(config,size) \
   (IO_Configuration_T)( Insert_Bits( config, size, FLEXCAN_CONFIGURATION_POSITION_MAXMB, FLEXCAN_CONFIGURATION_WIDTH_MAXMB ) )
//=============================================================================
// FlexCAN_Get_Message_Buffer_Size
//
// @func Get FlexCAN Device Message_Buffer_Size configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Message_Buffer_Size(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MAXMB, FLEXCAN_CONFIGURATION_WIDTH_MAXMB ) )
//=============================================================================
// @enum FlexCAN Device Baud Rate Configuration Position
//=============================================================================
typedef enum
{
   FLEXCAN_CONFIGURATION_POSITION_BAUD         = 3, //@emem [ 3: 2] FlexCAN Baud Rate 
   FLEXCAN_CONFIGURATION_POSITION_PSEG1        = 13,//@emem [ 6: 4] FlexCAN Phase Segment 1
   FLEXCAN_CONFIGURATION_POSITION_PSEG2        = 16,//@emem [ 9: 7] FlexCAN Phase Segment 2
   FLEXCAN_CONFIGURATION_POSITION_PROPSEG      = 19,//@emem [12:10] FlexCAN Propogation Segment
   FLEXCAN_CONFIGURATION_POSITION_RJW          = 22,//@emem [14:13] FlexCAN RJW
   FLEXCAN_CONFIGURATION_POSITION_TIME_QUANTA  = 24 //@emem [19:15] FlexCAN Time Quanta
}FlexCAN_BitRate_Configuration_Position_T;
typedef enum
{
   FLEXCAN_CONFIGURATION_WIDTH_BAUD         = 2, //@emem [ 3: 2] FlexCAN Baud Rate 
   FLEXCAN_CONFIGURATION_WIDTH_PSEG1        = 3, //@emem [ 6: 4] FlexCAN Phase Segment 1
   FLEXCAN_CONFIGURATION_WIDTH_PSEG2        = 3, //@emem [ 9: 7] FlexCAN Phase Segment 2
   FLEXCAN_CONFIGURATION_WIDTH_PROPSEG      = 3, //@emem [12:10] FlexCAN Propogation Segment
   FLEXCAN_CONFIGURATION_WIDTH_RJW          = 2, //@emem [14:13] FlexCAN RJW
   FLEXCAN_CONFIGURATION_WIDTH_TIME_QUANTA  = 5  //@emem [19:15] FlexCAN Time Quanta
}FlexCAN_BitRate_Configuration_Width_T;
typedef enum
{
   FLEXCAN_BAUD_250KBPS,
   FLEXCAN_BAUD_500KBPS,
   FLEXCAN_BAUD_1MBPS,
   FLEXCAN_BAUD_MAX
}FlexCAN_BAUD_T;
//=============================================================================
// FlexCAN_Set_Baud
//
// @func Set FlexCAN Device Baud configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_BAUD_T | value | A <t FlexCAN_BAUD_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_BAUD_T>
//
// @end
//=============================================================================
#define FlexCAN_Set_Baud(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_CONFIGURATION_POSITION_BAUD, FLEXCAN_CONFIGURATION_WIDTH_BAUD ) )
//=============================================================================
// FlexCAN_Get_Baud
//
// @func Get FlexCAN Device baud configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_BAUD_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Baud(config) \
   (FlexCAN_BAUD_T)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_BAUD, FLEXCAN_CONFIGURATION_WIDTH_BAUD ) )
//=============================================================================
// FlexCAN_Set_Phase_Segment1
//
// @func Set FlexCAN Device PhaseSeg1 configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | value | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_Phase_Segment1(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_CONFIGURATION_POSITION_PSEG1, FLEXCAN_CONFIGURATION_WIDTH_PSEG1 ) )
//=============================================================================
// FlexCAN_Get_Phase_Segment1
//
// @func Get FlexCAN Device PhaseSeg1 configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Phase_Segment1(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_PSEG1, FLEXCAN_CONFIGURATION_WIDTH_PSEG1 ) )
//=============================================================================
// FlexCAN_Set_Phase_Segment2
//
// @func Set FlexCAN Device PhaseSeg2 configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | value | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_Phase_Segment2(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_CONFIGURATION_POSITION_PSEG2, FLEXCAN_CONFIGURATION_WIDTH_PSEG2 ) )
//=============================================================================
// FlexCAN_Get_Phase_Segment2
//
// @func Get FlexCAN Device PhaseSeg2 configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Phase_Segment2(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_PSEG2, FLEXCAN_CONFIGURATION_WIDTH_PSEG2 ) )
//=============================================================================
// FlexCAN_Set_Prop_Segment
//
// @func Set FlexCAN Device PropSeg configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | value | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_Prop_Segment(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_CONFIGURATION_POSITION_PROPSEG, FLEXCAN_CONFIGURATION_WIDTH_PROPSEG ) )
//=============================================================================
// FlexCAN_Get_Prop_Segment
//
// @func Get FlexCAN Device PropSeg configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Prop_Segment(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_PROPSEG, FLEXCAN_CONFIGURATION_WIDTH_PROPSEG ) )
//=============================================================================
// FlexCAN_Set_RJW
//
// @func Set FlexCAN Device RJW configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | value | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_RJW(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_CONFIGURATION_POSITION_RJW, FLEXCAN_CONFIGURATION_WIDTH_RJW ) )
//=============================================================================
// FlexCAN_Get_RJW
//
// @func Get FlexCAN Device RJW configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_RJW(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_RJW, FLEXCAN_CONFIGURATION_WIDTH_RJW ) )
//=============================================================================
// FlexCAN_Set_Time_Quanta
//
// @func Set FlexCAN Device TimeQuanta configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | value | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_Time_Quanta(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_CONFIGURATION_POSITION_TIME_QUANTA, FLEXCAN_CONFIGURATION_WIDTH_TIME_QUANTA ) )
//=============================================================================
// FlexCAN_Get_Time_Quanta
//
// @func Get FlexCAN Device TimeQuanta configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Time_Quanta(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_TIME_QUANTA, FLEXCAN_CONFIGURATION_WIDTH_TIME_QUANTA ) )
//=============================================================================
// @enum FlexCAN Message Object Configuration Position
//=============================================================================
typedef enum FlexCAN_MSGOBJ_Configuration_Position_Tag
{
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_INDEX        = 3,  //@emem [ 7: 2] FlexCAN Message Object Index
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_DATA_LENGTH  = 9,  //@emem [11: 8] FlexCAN Message Object Data Length
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_ID_LENGTH    = 13, //@emem    12   FlexCAN Message Object ID Length
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_CODE         = 14, //@emem [16:13] FlexCAN Message Object Code
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_SRR          = 18, //@emem   17    FlexCAN Message Object Substitute Remote Request
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_RTR          = 19, //@emem   18    FlexCAN Message Object Remote Tx Request
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_DIRECTION    = 20, //@emem   19    FlexCAN Message Object Direction
   FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_INTERRUPT    = 21  //@emem   20    FlexCAN Message Object Interrupt Enable
}FlexCAN_MSGOBJ_Configuration_Position_T;

typedef enum FlexCAN_MSGOBJ_Configuration_Width_Tag
{
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_INDEX        = 6,  //@emem [ 7: 2] FlexCAN Message Object Index
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_DATA_LENGTH  = 4,  //@emem [11: 8] FlexCAN Message Object Data Length
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_ID_LENGTH    = 1,  //@emem    12   FlexCAN Message Object ID Length
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_CODE         = 4,  //@emem [16:13] FlexCAN Message Object Code
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_SRR          = 1,  //@emem   17    FlexCAN Message Object Substitute Remote Request
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_RTR          = 1,  //@emem   18    FlexCAN Message Object Remote Tx Request
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_DIRECTION    = 1,  //@emem   19    FlexCAN Message Object Direction
   FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_INTERRUPT    = 1   //@emem   20    FlexCAN Message Object Interrupt Enable
}FlexCAN_MSGOBJ_Configuration_Width_T;

typedef enum FlexCAN_MSGOBJ_INDEX_Tag
{
   FLEXCAN_MSG_OBJ_0,  //@emem Message Object 0
   FLEXCAN_MSG_OBJ_1,  //@emem Message Object 1
   FLEXCAN_MSG_OBJ_2,  //@emem Message Object 2
   FLEXCAN_MSG_OBJ_3,  //@emem Message Object 3
   FLEXCAN_MSG_OBJ_4,  //@emem Message Object 4
   FLEXCAN_MSG_OBJ_5,  //@emem Message Object 5
   FLEXCAN_MSG_OBJ_6,  //@emem Message Object 6
   FLEXCAN_MSG_OBJ_7,  //@emem Message Object 7
   FLEXCAN_MSG_OBJ_8,  //@emem Message Object 8
   FLEXCAN_MSG_OBJ_9,  //@emem Message Object 9
   FLEXCAN_MSG_OBJ_10, //@emem Message Object 10
   FLEXCAN_MSG_OBJ_11, //@emem Message Object 11
   FLEXCAN_MSG_OBJ_12, //@emem Message Object 12
   FLEXCAN_MSG_OBJ_13, //@emem Message Object 13
   FLEXCAN_MSG_OBJ_14, //@emem Message Object 14
   FLEXCAN_MSG_OBJ_15, //@emem Message Object 15
   FLEXCAN_MSG_OBJ_16, //@emem Message Object 16
   FLEXCAN_MSG_OBJ_17, //@emem Message Object 17
   FLEXCAN_MSG_OBJ_18, //@emem Message Object 18
   FLEXCAN_MSG_OBJ_19, //@emem Message Object 19
   FLEXCAN_MSG_OBJ_20, //@emem Message Object 20
   FLEXCAN_MSG_OBJ_21, //@emem Message Object 21
   FLEXCAN_MSG_OBJ_22, //@emem Message Object 22
   FLEXCAN_MSG_OBJ_23, //@emem Message Object 23
   FLEXCAN_MSG_OBJ_24, //@emem Message Object 24
   FLEXCAN_MSG_OBJ_25, //@emem Message Object 25
   FLEXCAN_MSG_OBJ_26, //@emem Message Object 26
   FLEXCAN_MSG_OBJ_27, //@emem Message Object 27
   FLEXCAN_MSG_OBJ_28, //@emem Message Object 28
   FLEXCAN_MSG_OBJ_29, //@emem Message Object 29
   FLEXCAN_MSG_OBJ_30, //@emem Message Object 30
   FLEXCAN_MSG_OBJ_31, //@emem Message Object 31
   FLEXCAN_MSG_OBJ_32, //@emem Message Object 32
   FLEXCAN_MSG_OBJ_33, //@emem Message Object 33
   FLEXCAN_MSG_OBJ_34, //@emem Message Object 34
   FLEXCAN_MSG_OBJ_35, //@emem Message Object 35
   FLEXCAN_MSG_OBJ_36, //@emem Message Object 36
   FLEXCAN_MSG_OBJ_37, //@emem Message Object 37
   FLEXCAN_MSG_OBJ_38, //@emem Message Object 38
   FLEXCAN_MSG_OBJ_39, //@emem Message Object 39
   FLEXCAN_MSG_OBJ_40, //@emem Message Object 40
   FLEXCAN_MSG_OBJ_41, //@emem Message Object 41
   FLEXCAN_MSG_OBJ_42, //@emem Message Object 42
   FLEXCAN_MSG_OBJ_43, //@emem Message Object 43
   FLEXCAN_MSG_OBJ_44, //@emem Message Object 44
   FLEXCAN_MSG_OBJ_45, //@emem Message Object 45
   FLEXCAN_MSG_OBJ_46, //@emem Message Object 46
   FLEXCAN_MSG_OBJ_47, //@emem Message Object 47
   FLEXCAN_MSG_OBJ_48, //@emem Message Object 48
   FLEXCAN_MSG_OBJ_49, //@emem Message Object 49
   FLEXCAN_MSG_OBJ_50, //@emem Message Object 50
   FLEXCAN_MSG_OBJ_51, //@emem Message Object 51
   FLEXCAN_MSG_OBJ_52, //@emem Message Object 52
   FLEXCAN_MSG_OBJ_53, //@emem Message Object 53
   FLEXCAN_MSG_OBJ_54, //@emem Message Object 54
   FLEXCAN_MSG_OBJ_55, //@emem Message Object 55
   FLEXCAN_MSG_OBJ_56, //@emem Message Object 56
   FLEXCAN_MSG_OBJ_57, //@emem Message Object 57
   FLEXCAN_MSG_OBJ_58, //@emem Message Object 58
   FLEXCAN_MSG_OBJ_59, //@emem Message Object 59
   FLEXCAN_MSG_OBJ_60, //@emem Message Object 60
   FLEXCAN_MSG_OBJ_61, //@emem Message Object 61
   FLEXCAN_MSG_OBJ_62, //@emem Message Object 62
   FLEXCAN_MSG_OBJ_63, //@emem Message Object 63
   FLEXCAN_MSG_OBJ_MAX //@emem Message Object Max

}FlexCAN_MSGOBJ_INDEX_T;

typedef enum FlexCAN_MSGOBJ_Data_Length_Tag
{
   FLEXCAN_DATA_0_BYTES = 0,
   FLEXCAN_DATA_1_BYTES = 1,
   FLEXCAN_DATA_2_BYTES = 2,
   FLEXCAN_DATA_3_BYTES = 3,
   FLEXCAN_DATA_4_BYTES = 4,
   FLEXCAN_DATA_5_BYTES = 5,
   FLEXCAN_DATA_6_BYTES = 6,
   FLEXCAN_DATA_7_BYTES = 7,
   FLEXCAN_DATA_MAX_BYTES = 8

}FlexCAN_MSGOBJ_Data_Length_T;

typedef enum FlexCAN_MSGOBJ_DIR_Tag
{
   FLEXCAN_MSGOBJ_DIR_RX, //@emem Message Direction Rx
   FLEXCAN_MSGOBJ_DIR_TX  //@emem Message Direction Tx
}FlexCAN_MSGOBJ_DIR_T;

typedef enum FlexCAN_MSGOBJ_ID_Tag
{
   FLEXCAN_MSGOBJ_ID_STD, //@emem Standard Message ID
   FLEXCAN_MSGOBJ_ID_EXT  //@emem Extended Message ID
}FlexCAN_MSGOBJ_ID_T;

typedef enum FlexCAN_Msg_Code_Tag
{
   FLEXCAN_MSGOBJ_RX_INACTIVE      = 0x0,  //@emem RX Inactive
   FLEXCAN_MSGOBJ_RX_BUSY          = 0x1,  //@emem RX Busy
   FLEXCAN_MSGOBJ_RX_FULL          = 0x2,  //@emem RX FULL
   FLEXCAN_MSGOBJ_RX_EMPTY         = 0x4,  //@emem RX Empty
   FLEXCAN_MSGOBJ_RX_OVERRUN       = 0x6,  //@emem RX Overrun
   FLEXCAN_MSGOBJ_TX_INACTIVE      = 0x8,  //@emem TX Inactive
   FLEXCAN_MSGOBJ_TX_REMOTE        = 0xA,  //@emem TX Remote
   FLEXCAN_MSGOBJ_TX_UNCONDITIONAL = 0xC,  //@emem TX Unconditional
   FLEXCAN_MSGOBJ_TX_REMOTE_MATCH  = 0xE   //@emem Tx Remote match

} FlexCAN_Msg_Code_T ;

//=============================================================================
// FlexCAN_MSGOBJ_Set_Index
//
// @func Set FlexCAN Message Object Index configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_MSGOBJ_INDEX_T | value | A <t FlexCAN_MSGOBJ_INDEX_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_MSGOBJ_INDEX_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_Index(config,index) \
   (IO_Configuration_T)( Insert_Bits( config, index, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_INDEX, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_INDEX ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_Index
//
// @func Get FlexCAN Message Object Index configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_Index(config) \
   (FlexCAN_MSGOBJ_INDEX_T)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_INDEX, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_INDEX ) )
//=============================================================================
// FlexCAN_MSGOBJ_Set_Direction
//
// @func Set FlexCAN Message Object Direction configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_MSGOBJ_DIR_T | value | A <t FlexCAN_MSGOBJ_DIR_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_MSGOBJ_DIR_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_Direction(config,dir) \
   (IO_Configuration_T)( Insert_Bits( config, dir, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_DIRECTION, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_DIRECTION ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_Direction
//
// @func Get FlexCAN Message Object Direction configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_MSGOBJ_DIR_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_Direction(config) \
   (FlexCAN_MSGOBJ_DIR_T)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_DIRECTION, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_DIRECTION ) )
//=============================================================================
// FlexCAN_MSGOBJ_Set_ID_Length
//
// @func Set FlexCAN Message Object ID_Length configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_MSGOBJ_ID_T | value | A <t FlexCAN_MSGOBJ_ID_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_MSGOBJ_ID_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_ID_Length(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_ID_LENGTH, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_ID_LENGTH ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_ID_Length
//
// @func Get FlexCAN Message Object ID_Length configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_MSGOBJ_DIR_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_ID_Length(config) \
   (FlexCAN_MSGOBJ_ID_T)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_ID_LENGTH, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_ID_LENGTH ) )
//=============================================================================
// FlexCAN_MSGOBJ_Set_Data_Length
//
// @func Set FlexCAN Message Object Data_Length configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_MSGOBJ_Data_Length_T | value | A <t FlexCAN_MSGOBJ_DataLength_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_Data_Length(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_DATA_LENGTH, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_DATA_LENGTH ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_Data_Length
//
// @func Get FlexCAN Message Object Data_Length configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_MSGOBJ_Data_Length_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_Data_Length(config) \
   (FlexCAN_MSGOBJ_Data_Length_T)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_DATA_LENGTH, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_DATA_LENGTH ) )
//=============================================================================
// FlexCAN_MSGOBJ_Set_Message_Code
//
// @func Set FlexCAN Message Object MsgCode configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_Msg_Code_T | code | A <t FlexCAN_Msg_Code_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_Msg_Code_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_Message_Code(config,code) \
   (IO_Configuration_T)( Insert_Bits( config, code, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_CODE, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_CODE ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_Message_Code
//
// @func Get FlexCAN Message Object MsgCode configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_Msg_Code_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_Message_Code(config) \
   (FlexCAN_Msg_Code_T)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_CODE, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_CODE ) )
//=============================================================================
// FlexCAN_MSGOBJ_Set_SRR
//
// @func Set FlexCAN Message Object SRR configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | value | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_SRR(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_SRR, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_SRR ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_SRR
//
// @func Get FlexCAN Message Object SRR configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_SRR(config) \
   (bool)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_SRR, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_SRR ) )
//=============================================================================
// FlexCAN_MSGOBJ_Set_RTR
//
// @func Set FlexCAN Message Object RTR configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | value | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_RTR(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_RTR, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_RTR ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_RTR
//
// @func Get FlexCAN Message Object RTR configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_RTR(config) \
   (bool)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_RTR, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_RTR ) )
//=============================================================================
// FlexCAN_MSGOBJ_Set_Interrupt
//
// @func Set FlexCAN Message Object RTR configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm bool | value | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Set_Interrupt(config,value) \
   (IO_Configuration_T)( Insert_Bits( config, value, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_INTERRUPT, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_INTERRUPT ) )
//=============================================================================
// FlexCAN_MSGOBJ_Get_Interrupt
//
// @func Get FlexCAN Message Object Interrupt configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_MSGOBJ_Get_Interrupt(config) \
   (bool)( Extract_Bits( config, FLEXCAN_MSGOBJ_CONFIGURATION_POSITION_INTERRUPT, FLEXCAN_MSGOBJ_CONFIGURATION_WIDTH_INTERRUPT ) )
//=============================================================================
// @enum FlexCAN Device Bus Off/Error Interrupt Configuration Position
//=============================================================================
typedef enum FlexCAN_Interrupt_Configuration_Position_Tag
{
   FLEXCAN_INTERRUPT_CONFIGURATION_POSITION_TYPE   = 2  //@emem [ 3: 2] FlexCAN Interrupt Type 
}FlexCAN_Interrupt_Configuration_Position_T;

typedef enum FlexCAN_Interrupt_Configuration_Width_Tag
{
   FLEXCAN_INTERRUPT_CONFIGURATION_WIDTH_TYPE   = 2  //@emem [ 3: 2] FlexCAN Interrupt Type 
}FlexCAN_Interrupt_Configuration_Width_T;

typedef enum FlexCAN_Interrupt_Type_Tag
{
   FLEXCAN_BUSOFF_INTERRUPT,     //@emem Bus off interrupt type
   FLEXCAN_ERROR_INTERRUPT,      //@emem Error interrupt type
   FLEXCAN_MESSAGE_INTERRUPT,    //@emem Message Buffer interrupt type
   FLEXCAN_INTERRUPT_MAX

}FlexCAN_Interrupt_Type_T;
//=============================================================================
// FlexCAN_Set_Interrupt_Type
//
// @func Set FlexCAN Device Interrupt Type configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm FlexCAN_Interrupt_Type_T | type | A <t FlexCAN_Interrupt_Type_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_Interrupt_Type_T>
//
// @end
//=============================================================================
#define FlexCAN_Set_Interrupt_Type(config,type) \
   (IO_Configuration_T)( Insert_Bits( config, type, FLEXCAN_INTERRUPT_CONFIGURATION_POSITION_TYPE, FLEXCAN_INTERRUPT_CONFIGURATION_WIDTH_TYPE ) )
//=============================================================================
// FlexCAN_Get_Interrupt_Type
//
// @func Get FlexCAN Device Interrupt Type configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_Interrupt_Type_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Interrupt_Type(config) \
   (FlexCAN_Interrupt_Type_T)( Extract_Bits( config, FLEXCAN_INTERRUPT_CONFIGURATION_POSITION_TYPE, FLEXCAN_INTERRUPT_CONFIGURATION_WIDTH_TYPE ) )
//=============================================================================
// FlexCAN_Set_InterruptEnable_Mask
//
// @func This function returns the Interrupt Enable mask for FlexCAN message object
//
// @parm uint32_t* | address | 32-bit address for setting the bit
//       bool| status | Enable/Disable status for message object interrupt
//       FlexCAN_MSGOBJ_T| index | message object index
//
// @rdesc none
//
// @end
//=============================================================================
#define FlexCAN_Set_Interrupt_Enable_Mask( address, status, index)\
       Ldmst( address, status, index, 1 )
//=============================================================================
// FlexCAN_Get_InterruptStatus_Flag
//
// @func This function returns the Interrupt Status info for FlexCAN message object
//
// @parm uint32_t | config | 32-bit interrupt mask register value
//       FlexCAN_MSGOBJ_T| index | message object index
//
// @rdesc bool |interrupt status flag bit
//
// @end
//=============================================================================
#define FlexCAN_Get_Interrupt_Status( config, index)\
       ((bool)(Extract_Bits( config, index, 1 )==1)? true: false)
//=============================================================================
// FlexCAN_Get_InterruptEnable_Mask
//
// @func This function returns the Interrupt Enable mask for FlexCAN message object
//
// @parm uint32_t | config | 32-bit interrupt flag register value
//       FlexCAN_MSGOBJ_T| index | message object index
//
// @rdesc bool |interrupt enable mask status
//
// @end
//=============================================================================
#define FlexCAN_Get_Interrupt_Enable_Mask( config, index)\
       ((bool)(Extract_Bits( config, index, 1 )==1)? true: false)
//=============================================================================
// FLEXCAN_Get_Prescaler
//
// @func This function returns the prescalar value for FlexCAN device
//
// @parm const |device_freq| Frequency of the FlexCAN device
//       const |desired_baud| Desired Baud Rate value
//       const |time_quanta | No of Time quanta
//
// @rdesc 8-bit prescalar divider value
//
// @end
//=============================================================================
#define FLEXCAN_Get_Prescaler( device_freq, desired_baud, time_quanta )\
       (uint8_t)(( device_freq/(desired_baud * time_quanta)) - 1 )

typedef  void (* const FlexCAN_Transmit_Callback_T )(uint32_t);
typedef  void (* const FlexCAN_Receive_Callback_T)(uint32_t,  uint8_t*, uint8_t);
typedef  void (* const FlexCAN_Error_Callback_T)(void);

//=============================================================================
// FlexCAN_Initialize_Message_Object
//
// @func This function initializes FlexCAN MSGBUF registers
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Initialize_Message_Object(
   IO_Configuration_T in_configuration, 
   uint32_t message_id);

//=============================================================================
// FLEXCAN_Get_Free_Running_Timer
//
// @func This function returns the valuen of free running timer
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T  in_msgobj   message object no
//
// @rdesc uint16_t | Free running timer value
//
// @end
//=============================================================================
uint16_t FLEXCAN_Get_Free_Running_Timer(
   const FLEXCAN_T*        in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T  in_msgobj);

//=============================================================================
// FLEXCAN_MSGOBJ_Configure_For_Transmit
//
// @func This function configures a message object for Transmit
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T  in_msg_obj   message object no
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_Configure_For_Transmit(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj);

//=============================================================================
// FLEXCAN_MSGOBJ_Configure_For_Recieve
//
// @func This function configures a message object for Receive
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T  in_msg_obj   message object no
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_Configure_For_Recieve(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj);

//=============================================================================
// FLEXCAN_MSGOBJ_Write_Data
//
// @func This function writes the data to be transmitted in HW buffer
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T  in_msgobj   message object no
//       uint8_t* in_buffer  input buffer to copy Rx message
//       uint8_t  in_length  length of data in bytes to be copied
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_Write_Data(
   FLEXCAN_T *                  in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T       in_msgobj,
   const uint8_t *              in_buffer,
   FlexCAN_MSGOBJ_Data_Length_T in_length);

//=============================================================================
// FLEXCAN_MSGOBJ_Get_Data
//
// @func This function copies the recieved data bytes in input buffer
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T  in_msgobj   message object no
//       uint8_t* in_buffer  input buffer to copy Rx message
//       uint8_t  in_length  length of data in bytes to be copied
//
// @rdesc None
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_Get_Data(
   const FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj,
   uint8_t *              in_buffer,
   uint8_t                in_length);

//=============================================================================
// FlexCAN_Interrupt_Get_Direction
//
// @func This function returns the Rx/Tx direction for a particluar message
//       object interrupt
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc FlexCAN_MSGOBJ_DIR_T Rx/Tx direction
//
// @end
//=============================================================================
FlexCAN_MSGOBJ_DIR_T FlexCAN_Interrupt_Get_Direction(
   IO_Configuration_T in_configuration);

//=============================================================================
// FLEXCAN_Set_Bit_Rate
//
// @func This function sets the bit rate for the specified CAN
//
// @parm    FLEXCAN_T  *in_pFlexCAN     FlexCAN device address
//          uint8_t     in_time_quanta  TimeQuanta to be set
//          uint32_t    in_bit_rate     Bit Rate 
//
// @rdesc none
//
// @end
//=============================================================================
void FLEXCAN_Set_Bit_Rate(
   FLEXCAN_T *      in_pFlexCAN,
   uint8_t          in_time_quanta,
   uint32_t         in_bit_rate);

//=============================================================================
// FLEXCAN_Get_Msg_ID
//
// @func This function returns the Rx/Tx direction for a particluar message
//       object interrupt
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc FlexCAN_MSGOBJ_DIR_T Rx/Tx direction
//
// @end
//=============================================================================
uint32_t FLEXCAN_Get_Msg_ID(
   const FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj);

//=============================================================================
// FLEXCAN_Set_Msg_ID
//
// @func This function returns the Rx/Tx direction for a particluar message
//       object interrupt
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc FlexCAN_MSGOBJ_DIR_T Rx/Tx direction
//
// @end
//=============================================================================
void FLEXCAN_Set_Msg_ID(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj,
   uint32_t in_message_id);

//=============================================================================
// FLEXCAN_Set_Individual_Ext_Mask
//
// @func This function sets the individual masks to message buffers
//       object interrupt
//
// @parm    FLEXCAN_T | *in_pFlexCAN   |  Address of CAN Device
//          FlexCAN_MSGOBJ_INDEX_T , in_msgobj  Message Buffer no 
//          uint32_t                 in_msg_mask
//
// @rdesc none
//
// @end
//=============================================================================
void FLEXCAN_Set_Individual_Ext_Mask(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj,
   uint32_t               in_msg_mask);

//=============================================================================
// FLEXCAN_Set_Global_Ext_Mask
//
// @func This function sets the global mask for a FlexCAN device
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       uint32_t   in_msg_mask   32-bit global mask
//
// @rdesc none
//
// @end
//=============================================================================
void FLEXCAN_Set_Global_Ext_Mask(
   FLEXCAN_T *            in_pFlexCAN,
   uint32_t               in_msg_mask);

//=============================================================================
// FLEXCAN_Enable_Communication
//
// @func This function enables communictaion by setting HALT bit to '0'
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//
// @rdesc none
//
// @end
//=============================================================================
void FLEXCAN_Enable_Communication(
   FLEXCAN_T* in_pFlexCAN);

//=============================================================================
// FLEXCAN_Disable_Communication
//
// @func This function disables communictaion by setting HALT bit to '1'
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//
// @rdesc none
//
// @end
//=============================================================================
void FLEXCAN_Disable_Communication(
   FLEXCAN_T  *in_pFlexCAN);

//=============================================================================
// FLEXCAN_Get_Device_Freeze_Status
//
// @func This function returns the freeze acknowledge status.
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//
// @rdesc none
//
// @end
//=============================================================================
bool FLEXCAN_Get_Device_Freeze_Status(
   FLEXCAN_T  *in_pFlexCAN);

//=============================================================================
// FLEXCAN_MSGOBJ_Get_Status
//
// @func This function returns the message buffer status (CODE field) of  a FlexCAN device
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T in_msg_obj   message object no
//
// @rdesc FlexCAN_Msg_Code_T message buffer code field value
//
// @end
//=============================================================================
FlexCAN_Msg_Code_T FLEXCAN_MSGOBJ_Get_Status(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj);


//=============================================================================
// FLEXCAN_MSGOBJ_Get_Message_Length
//
// @func This function returns the message buffer length
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T in_msg_obj   message object no
//
// @rdesc uint8_t message buffer length
//
// @end
//=============================================================================
uint8_t FLEXCAN_MSGOBJ_Get_Message_Length(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj);

//=============================================================================
// FLEXCAN_MSGOBJ_Set_Message_Length
//
// @func This function returns the message buffer length
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//       FlexCAN_MSGOBJ_INDEX_T in_msg_obj   message object no
//      uint8_t in_data_length - length of message buffer to be set
//
// @rdesc uint8_t message buffer length
//
// @end
//=============================================================================
void FLEXCAN_MSGOBJ_Set_Message_Length(
   FLEXCAN_T *            in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj,
   uint8_t in_data_length);


//=============================================================================
// FLEXCAN_Unlock_Message_Buffer
//
// @func This function returns the free running timer value of a FlexCAN device to unlock a message buffer
//
// @parm FLEXCAN_T *          in_pFlexCAN  FlexCAN device address
//
// @rdesc FLEXCAN_TIMER_T current free running timer value
//
// @end
//=============================================================================
FLEXCAN_TIMER_T FLEXCAN_Unlock_Message_Buffer(
   FLEXCAN_T* in_pFlexCAN);

//=============================================================================
//  FlexCAN_Enable_Device
//
// @func This function used to Enable/Disable the CAN Device
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @parm bool | in_enable | Enable/Disable 
//
// @rdesc void
//
// @end
//============================================================================
void FlexCAN_Enable_Device(
   IO_Configuration_T in_configuration, 
   bool in_enable);

//=============================================================================
//  FlexCAN_Get_Device_Status
//
// @func This function used to Enable/Disable the CAN device
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc bool | in_enable | Enable/Disable 
//
// @end
//============================================================================
bool FlexCAN_Get_Device_Status(
   IO_Configuration_T in_configuration);

//=============================================================================
//  FlexCAN_Set_Device_Soft_Reset
//
// @func This function used to reset the CAN Node
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc void
//
// @end
//============================================================================
void FlexCAN_Set_Device_Soft_Reset(
   IO_Configuration_T in_configuration);

//=============================================================================
//  FLEXCAN_Get_Device_Soft_Reset_Status
//
// @func This function used to reset the CAN Node
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc bool | Reset Req/No Reset Req 
//
// @end
//============================================================================
bool FLEXCAN_Get_Device_Soft_Reset_Status(
   IO_Configuration_T in_configuration);

#endif // DD_FLEXCAN_COMMON_H
