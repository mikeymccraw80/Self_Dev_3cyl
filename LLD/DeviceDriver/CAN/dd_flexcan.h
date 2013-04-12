#ifndef DD_FLEXCAN_H
#define DD_FLEXCAN_H

#include "hw_flexcan.h"
#include "io_type.h"
#include "io_config_flexcan.h"

#define SECTION_FLEXCAN_A_REGISTER
#include "section.h"
extern FLEXCAN_T FlexCAN_A;
#define SECTION_END
#include "section.h"

#define SECTION_FLEXCAN_C_REGISTER
#include "section.h"
extern FLEXCAN_T FlexCAN_C;
#define SECTION_END
#include "section.h"


// Though Monaco contains only FlexCaN A and C, to use the array indexing feature, 
// No of Flexcan devices is kept at 3.
#define NUMBER_OF_FLEXCAN_DEVICES  ( 3)

// Constants
#define THIRTYONE (31)
#define THIRTYTWO (32)

typedef enum FlexCAN_ID_Acc_Mask_Tag
{
   FLEXCAN_ONE_FULL_ID,
   FLEXCAN_2FULL_STDID_OR_2PART_EXT_ID,
   FLEXCAN_4PART_STD_OR_EXT_ID,
   FLEXCAN_ALL_ID_REJECT

} FlexCAN_ID_Acc_Mask_T;

// FlexCAN Bit Rate Values
#define FLEXCAN_BAUD_RATE_100KBPS   (100000)
#define FLEXCAN_BAUD_RATE_250KBPS   (250000)
#define FLEXCAN_BAUD_RATE_500KBPS   (500000)
#define FLEXCAN_BAUD_RATE_1MBPS     (1000000)


// CAN bit related constants
#define CAN_REGISTER_SET_ALL_BITS          0xFFFFFFFF
#define CAN_INT_REGISTER_BYTE_NUM          4
#define CAN_INT_FLAG_MSB                   7
#define CAN_INT_REGISTER_BIT_NUM           32
#define FLEXCAN_STD_ID_SHIFT               ((uint8_t)18)
#define FLEXCAN_MSGBUF_TX (0x8)



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
// @enum FlexCAN Device Baud Rate Configuration Position
//=============================================================================

typedef enum
{
   FLEXCAN_BAUD_250KBPS,
   FLEXCAN_BAUD_500KBPS,
   FLEXCAN_BAUD_1MBPS,
   FLEXCAN_BAUD_MAX
}FlexCAN_BAUD_T;


//=============================================================================
// @enum FlexCAN Message Object Configuration Position
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t                              : 2; 
      bitfield32_t   INDEX                 : 6;   //@emem [ 7: 2] FlexCAN Message Object Index
      bitfield32_t   DATA_LENGTH    : 4;  //@emem [11: 8] FlexCAN Message Object Data Length
      bitfield32_t   ID_LENGTH         : 1;    //@emem    12   FlexCAN Message Object ID Length
      bitfield32_t   CODE                   : 4;   //@emem [16:13] FlexCAN Message Object Code
      bitfield32_t   SRR                      : 1;    //@emem   17    FlexCAN Message Object Substitute Remote Request
      bitfield32_t   RTR                      : 1;   //@emem   18    FlexCAN Message Object Remote Tx Request
      bitfield32_t   DIRECTION          : 1;   //@emem   19    FlexCAN Message Object Direction
      bitfield32_t   INTERRUPT         : 1; //@emem   20    FlexCAN Message Object Interrupt Enable
      bitfield32_t                              : 11; 
   }      F;

   uint32_t U32;

}  FlexCAN_MSGOBJ_Configuration_T;



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


//FlexCAN C has only 32 MB's
#define FLEXCAN_C_MSG_OBJ_MAX    (32)

#define FLEXCAN_Get_Prescaler( device_freq, desired_baud, time_quanta )\
       (uint8_t)(( device_freq/(desired_baud * time_quanta)) - 1 )

//=============================================================
//  FlexCAN Prescalar macro
//==============================================================
#define FLEXCAN_A_PRESCALER \
   FLEXCAN_Get_Prescaler(FLEXCAN_SYSTEM_FREQUENCY,\
   (FLEXCAN_A_BAUD_RATE == FLEXCAN_BAUD_250KBPS ? FLEXCAN_BAUD_RATE_250KBPS :\
    FLEXCAN_A_BAUD_RATE == FLEXCAN_BAUD_500KBPS ? FLEXCAN_BAUD_RATE_500KBPS :\
    FLEXCAN_A_BAUD_RATE == FLEXCAN_BAUD_1MBPS ? FLEXCAN_BAUD_RATE_1MBPS :\
    FLEXCAN_BAUD_RATE_500KBPS)\
   ,FlexCAN_A_Time_Quanta)


#define FLEXCAN_C_PRESCALER \
   FLEXCAN_Get_Prescaler(FLEXCAN_SYSTEM_FREQUENCY,\
  ( FLEXCAN_C_BAUD_RATE == FLEXCAN_BAUD_250KBPS ? FLEXCAN_BAUD_RATE_250KBPS : \
   FLEXCAN_C_BAUD_RATE == FLEXCAN_BAUD_500KBPS ? FLEXCAN_BAUD_RATE_500KBPS : \
   FLEXCAN_C_BAUD_RATE== FLEXCAN_BAUD_1MBPS ? FLEXCAN_BAUD_RATE_1MBPS : \
    FLEXCAN_BAUD_RATE_500KBPS)\
   ,FlexCAN_C_Time_Quanta)


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


#endif // DD_FLEXCAN_H

