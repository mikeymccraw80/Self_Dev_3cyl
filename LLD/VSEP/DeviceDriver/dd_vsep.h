#ifndef DD_VSEP_H
#define DD_VSEP_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep.h~7:incl:mt20u2#2 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 11:47:53 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Mon Feb 12 14:49:19 2007 %
//
// %version:         7 %
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
// Defines all the drivers that are available.
// Include before the ifdef.
//=============================================================================
#include "dd_vsep_txd.h"
#include "dd_vsep_rxd.h"
//#include "dd_vsep_init_config.h"
#include "dd_vsep_config.h"

extern uint32_t            VSEP_Channel_Enabled;

#define Calculate_Vsep_Protect_Mask(x) (0x0001<<x)

#define Parameter_Not_Used( notused ) ((notused)?(notused+1):(notused+2)) 
typedef enum
{
   VSEP_MESSAGE_INIT,
   VSEP_MESSAGE_VR,
   VSEP_MESSAGE_DEPS,
   VSEP_MESSAGE_LEDMODE,
   VSEP_MESSAGE_PCH_MPIO,
   VSEP_MESSAGE_EST_SELECT,
   VSEP_MESSAGE_EST_FAULT,
   VSEP_MESSAGE_SOH,
   VSEP_MESSAGE_SOH_STATUS,
   VSEP_MESSAGE_FAULT,
   VSEP_MESSAGE_MPIO_MODE,
   VSEP_MESSAGE_PWM,
   VSEP_MESSAGE_MAX
}VSEP_Message_T;

typedef enum
{
   VSEP_INDEX_0,
   VSEP_INDEX_1,
   VSEP_INDEX_MAX
} VSEP_Index_T;

typedef enum
{
   VSEP_CHANNEL_PCH_01_FLT_LVL_1,
   VSEP_CHANNEL_PCH_02_FLT_LVL_1,
   VSEP_CHANNEL_PCH_03_FLT_LVL_1,
   VSEP_CHANNEL_PCH_04_FLT_LVL_1_2,
   VSEP_CHANNEL_PCH_05_FLT_LVL_1_2,
   VSEP_CHANNEL_PCH_06_FLT_LVL_1_2,
   VSEP_CHANNEL_PCH_07_FLT_LVL_1_2,
   VSEP_CHANNEL_PCH_08_FLT_LVL_1_2,
   VSEP_CHANNEL_PCH_09_FLT_LVL_2,
   VSEP_CHANNEL_PCH_10_FLT_LVL_2,
   VSEP_CHANNEL_PCH_11_FLT_LVL_2,
   VSEP_CHANNEL_PCH_12_FLT_LVL_2,
   VSEP_CHANNEL_PCH_13_FLT_LVL_3,
   VSEP_CHANNEL_PCH_14_FLT_LVL_3,
   VSEP_CHANNEL_PCH_15_PWM_1_FLT_LVL_3,
   VSEP_CHANNEL_PCH_16_PWM_2_FLT_LVL_3,
   VSEP_CHANNEL_PCH_17_FLT_LVL_4,
   VSEP_CHANNEL_PCH_18_FLT_LVL_4,
   VSEP_CHANNEL_PCH_19_FLT_LVL_5,
   VSEP_CHANNEL_PCH_20_FLT_LVL_5,
   VSEP_CHANNEL_PCH_21_PWM_3_FLT_LVL_6,
   VSEP_CHANNEL_PCH_22_PWM_4_FLT_LVL_6,
   VSEP_CHANNEL_PCH_23_FLT_LVL_6,
   VSEP_CHANNEL_PCH_24_PWM_5_FLT_LVL_6,
   VSEP_CHANNEL_PCH_25_FLT_LVL_7,
   VSEP_CHANNEL_PCH_26_FLT_LVL_7,
   VSEP_CHANNEL_PCH_27_PWM_6_FLT_LVL_7,
   VSEP_CHANNEL_PCH_28_PWM_7_FLT_LVL_7,
   VSEP_CHANNEL_PCH_29_PWM_8_FLT_LVL_7,
   VSEP_CHANNEL_PCH_30_FLT_LVL_7,
   VSEP_CHANNEL_MPIO_1,
   VSEP_CHANNEL_MPIO_2,
   VSEP_CHANNEL_MPIO_3,
   VSEP_CHANNEL_LEDMODE_25,
   VSEP_CHANNEL_LEDMODE_26,
   VSEP_CHANNEL_LEDMODE_30,
   VSEP_CHANNEL_VR1,
   VSEP_CHANNEL_VR2,
   VSEP_CHANNEL_DEPS,
   VSEP_CHANNEL_ISO,
   VSEP_CHANNEL_CAN,
   VSEP_CHANNEL_CLK,
   VSEP_CHANNEL_IREF,
   VSEP_CHANNEL_SOHRSTEN_STAT,
   VSEP_CHANNEL_MAX

} VSEP_Channel_T;

typedef enum
{
   VSEP_CONFIGURATION_POSITION_DEVICE_INDEX   = 0, //      0  Device Index
   VSEP_CONFIGURATION_POSITION_CHANNEL        = 1  // [ 6: 1] Channel
}VSEP_Configuration_Position_T;

typedef enum
{
   VSEP_CONFIGURATION_WIDTH_DEVICE_INDEX      = 1,  //      0  Device Index
   VSEP_CONFIGURATION_WIDTH_CHANNEL           = 6   // [ 6: 1] Channel
}VSEP_Configuration_Width_T;

typedef enum
{
   VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_1    = 0,  // [ 3: 0] Fault Level 1
   VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_2    = 4,  // [ 6: 4] Fault Level 2
   VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_3    = 7,  // [ 9: 7] Fault Level 3
   VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_4    =10,  // [13:10] Fault Level 4
   VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_5    =14,  // [17:14] Fault Level 5
   VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_6    =18,  // [20:18] Fault Level 6
   VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_7    =21   // [23:21] Fault Level 7
}VSEP_Fault_Level_Configuration_Position_T;

typedef enum
{
   VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_1       = 4,  // [ 3: 0] Fault Level 1
   VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_2       = 3,  // [ 6: 4] Fault Level 2
   VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_3       = 3,  // [ 9: 7] Fault Level 3
   VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_4       = 4,  // [13:10] Fault Level 4
   VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_5       = 4,  // [17:14] Fault Level 5
   VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_6       = 3,  // [20:18] Fault Level 6
   VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_7       = 3   // [23:21] Fault Level 7
}VSEP_Fault_Level_Configuration_Width_T;

typedef enum
{
   VSEP_FAULT_LEVEL_GROUP_1,
   VSEP_FAULT_LEVEL_GROUP_2,
   VSEP_FAULT_LEVEL_GROUP_3,
   VSEP_FAULT_LEVEL_GROUP_4,
   VSEP_FAULT_LEVEL_GROUP_5,
   VSEP_FAULT_LEVEL_GROUP_6,
   VSEP_FAULT_LEVEL_GROUP_7,
   VSEP_FAULT_LEVEL_GROUP_MAX

}VSEP_Fault_Level_Group_T;

typedef enum
{
   VSEP_FAULT_LEVEL_1_125MV,
   VSEP_FAULT_LEVEL_1_174MV,	
   VSEP_FAULT_LEVEL_1_223MV,	
   VSEP_FAULT_LEVEL_1_298MV,	
   VSEP_FAULT_LEVEL_1_372MV,	
   VSEP_FAULT_LEVEL_1_447MV,	
   VSEP_FAULT_LEVEL_1_521MV,	
   VSEP_FAULT_LEVEL_1_596MV,	
   VSEP_FAULT_LEVEL_1_1903MV,	
   VSEP_FAULT_LEVEL_1_2053MV,	
   VSEP_FAULT_LEVEL_1_2203MV,	
   VSEP_FAULT_LEVEL_1_2353MV,	
   VSEP_FAULT_LEVEL_1_2503MV,	
   VSEP_FAULT_LEVEL_1_2653MV,	
   VSEP_FAULT_LEVEL_1_2803MV,	
   VSEP_FAULT_LEVEL_1_2953MV
}VSEP_Fault_Level_1_T;

typedef enum
{
   VSEP_FAULT_LEVEL_2_3_6_7_125MV,
   VSEP_FAULT_LEVEL_2_3_6_7_174MV,
   VSEP_FAULT_LEVEL_2_3_6_7_223MV,
   VSEP_FAULT_LEVEL_2_3_6_7_298MV,
   VSEP_FAULT_LEVEL_2_3_6_7_372MV,
   VSEP_FAULT_LEVEL_2_3_6_7_447MV,
   VSEP_FAULT_LEVEL_2_3_6_7_521MV,
   VSEP_FAULT_LEVEL_2_3_6_7_596MV
}VSEP_Fault_Level_2_3_6_7_T;

typedef enum
{
   VSEP_FAULT_LEVEL_4_5_125MV,
   VSEP_FAULT_LEVEL_4_5_174MV,
   VSEP_FAULT_LEVEL_4_5_223MV,
   VSEP_FAULT_LEVEL_4_5_298MV,
   VSEP_FAULT_LEVEL_4_5_372MV,
   VSEP_FAULT_LEVEL_4_5_447MV,
   VSEP_FAULT_LEVEL_4_5_521MV,
   VSEP_FAULT_LEVEL_4_5_596MV,
   VSEP_FAULT_LEVEL_4_5_720MV,
   VSEP_FAULT_LEVEL_4_5_794MV,
   VSEP_FAULT_LEVEL_4_5_869MV,
   VSEP_FAULT_LEVEL_4_5_943MV,
   VSEP_FAULT_LEVEL_4_5_1018MV,
   VSEP_FAULT_LEVEL_4_5_1092MV,
   VSEP_FAULT_LEVEL_4_5_1167MV,
   VSEP_FAULT_LEVEL_4_5_1241MV
}VSEP_Fault_Level_4_5_T;


#define MTSA_CONFIG_VSEP_DEVICE_0			( VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ) )
//=============================================================================
// VSEP_Set_Fault_Level_1
//
// @func Set fault level 1 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Fault_Level_1_T | y | A <t VSEP_Fault_Level_1_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Fault_Level_1_T>
//
// @end
//=============================================================================
#define VSEP_Set_Fault_Level_1(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_1, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_1 ) )

//=============================================================================
// VSEP_Get_Fault_Level_1
//
// @func Get fault level 1 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Fault_Level_1_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Fault_Level_1(x) \
   (VSEP_Fault_Level_1_T)( Extract_Bits( x, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_1, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_1 ) )

//=============================================================================
// VSEP_Set_Fault_Level_2
//
// @func Set fault level 2 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Fault_Level_2_3_6_7_T | y | A <t VSEP_Fault_Level_2_3_6_7_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Fault_Level_2_3_6_7_T>
//
// @end
//=============================================================================
#define VSEP_Set_Fault_Level_2(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_2, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_2 ) )

//=============================================================================
// VSEP_Get_Fault_Level_2
//
// @func Get fault level 2 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Fault_Level_2_3_6_7_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Fault_Level_2(x) \
   (VSEP_Fault_Level_2_3_6_7_T)( Extract_Bits( x, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_2, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_2 ) )

//=============================================================================
// VSEP_Set_Fault_Level_3
//
// @func Set fault level 3 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Fault_Level_2_3_6_7_T | y | A <t VSEP_Fault_Level_2_3_6_7_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Fault_Level_2_3_6_7_T>
//
// @end
//=============================================================================
#define VSEP_Set_Fault_Level_3(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_3, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_3 ) )

//=============================================================================
// VSEP_Get_Fault_Level_3
//
// @func Get fault level 3 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Fault_Level_2_3_6_7_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Fault_Level_3(x) \
   (VSEP_Fault_Level_2_3_6_7_T)( Extract_Bits( x, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_3, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_3 ) )

//=============================================================================
// VSEP_Set_Fault_Level_4
//
// @func Set fault level 4 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Fault_Level_4_5_T | y | A <t VSEP_Fault_Level_4_5_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Fault_Level_4_5_T>
//
// @end
//=============================================================================
#define VSEP_Set_Fault_Level_4(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_4, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_4 ) )

//=============================================================================
// VSEP_Get_Fault_Level_4
//
// @func Get fault level 4 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Fault_Level_4_5_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Fault_Level_4(x) \
   (VSEP_Fault_Level_4_5_T)( Extract_Bits( x, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_4, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_4 ) )

//=============================================================================
// VSEP_Set_Fault_Level_5
//
// @func Set fault level 5 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Fault_Level_4_5_T | y | A <t VSEP_Fault_Level_4_5_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Fault_Level_4_5_T>
//
// @end
//=============================================================================
#define VSEP_Set_Fault_Level_5(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_5, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_5 ) )

//=============================================================================
// VSEP_Get_Fault_Level_5
//
// @func Get fault level 5 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Fault_Level_4_5_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Fault_Level_5(x) \
   (VSEP_Fault_Level_4_5_T)( Extract_Bits( x, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_5, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_5 ) )


//=============================================================================
// VSEP_Set_Fault_Level_6
//
// @func Set fault level 6 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Fault_Level_2_3_6_7_T | y | A <t VSEP_Fault_Level_2_3_6_7_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Fault_Level_2_3_6_7_T>
//
// @end
//=============================================================================
#define VSEP_Set_Fault_Level_6(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_6, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_6 ) )

//=============================================================================
// VSEP_Get_Fault_Level_6
//
// @func Get fault level 6 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Fault_Level_2_3_6_7_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Fault_Level_6(x) \
   (VSEP_Fault_Level_2_3_6_7_T)( Extract_Bits( x, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_6, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_6 ) )

//=============================================================================
// VSEP_Set_Fault_Level_7
//
// @func Set fault level 7 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Fault_Level_2_3_6_7_T | y | A <t VSEP_Fault_Level_2_3_6_7_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Fault_Level_2_3_6_7_T>
//
// @end
//=============================================================================
#define VSEP_Set_Fault_Level_7(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_7, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_7 ) )

//=============================================================================
// VSEP_Get_Fault_Level_7
//
// @func Get fault level 7 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Fault_Level_2_3_6_7_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Fault_Level_7(x) \
   (VSEP_Fault_Level_2_3_6_7_T)( Extract_Bits( x, VSEP_FAULT_LEVEL_CONFIGURATION_POSITION_7, VSEP_FAULT_LEVEL_CONFIGURATION_WIDTH_7 ) )

typedef enum
{
   VSEP_SLEW_CONFIGURATION_POSITION_1     = 0,  // [ 1: 0] Slew 1
   VSEP_SLEW_CONFIGURATION_POSITION_2     = 2,  // [ 4: 2] Slew 2
   VSEP_SLEW_CONFIGURATION_POSITION_3     = 5,  // [ 7: 5] Slew 3
   VSEP_SLEW_CONFIGURATION_POSITION_4     = 8,  // [ 9: 8] Slew 4
   VSEP_SLEW_CONFIGURATION_POSITION_5     =10,  // [11:10] Slew 5
   VSEP_SLEW_CONFIGURATION_POSITION_CAN   =12   // [13:12] Slew CAN
}VSEP_Slew_Configuration_Position_T;

typedef enum
{
   VSEP_SLEW_CONFIGURATION_WIDTH_1        = 2,  // [ 1: 0] Slew 1
   VSEP_SLEW_CONFIGURATION_WIDTH_2        = 3,  // [ 4: 2] Slew 2
   VSEP_SLEW_CONFIGURATION_WIDTH_3        = 3,  // [ 7: 5] Slew 3
   VSEP_SLEW_CONFIGURATION_WIDTH_4        = 2,  // [ 9: 8] Slew 4
   VSEP_SLEW_CONFIGURATION_WIDTH_5        = 2,  // [11:10] Slew 5
   VSEP_SLEW_CONFIGURATION_WIDTH_CAN      = 2   // [13:12] Slew CAN
}VSEP_Slew_Configuration_Width_T;

typedef enum
{
   VSEP_SLEW_GROUP_1,
   VSEP_SLEW_GROUP_2,
   VSEP_SLEW_GROUP_3,
   VSEP_SLEW_GROUP_4,
   VSEP_SLEW_GROUP_5,
   VSEP_SLEW_GROUP_CAN,
   VSEP_SLEW_GROUP_MAX
}VSEP_Slew_Group_T;

typedef enum
{
   VSEP_SLEW_GROUP_1_4_750UA,
   VSEP_SLEW_GROUP_1_4_1500UA,
   VSEP_SLEW_GROUP_1_4_3000UA,
   VSEP_SLEW_GROUP_1_4_6000UA
}VSEP_Slew_Group_1_4_T;

typedef enum
{
   VSEP_SLEW_GROUP_2_3_100UA,
   VSEP_SLEW_GROUP_2_3_300UA,
   VSEP_SLEW_GROUP_2_3_500UA,
   VSEP_SLEW_GROUP_2_3_700UA,
   VSEP_SLEW_GROUP_2_3_900UA,
   VSEP_SLEW_GROUP_2_3_1100UA,
   VSEP_SLEW_GROUP_2_3_1300UA,
   VSEP_SLEW_GROUP_2_3_1500UA
}VSEP_Slew_Group_2_3_T;

typedef enum
{
   VSEP_SLEW_GROUP_5_300UA,
   VSEP_SLEW_GROUP_5_700UA,
   VSEP_SLEW_GROUP_5_1100UA,
   VSEP_SLEW_GROUP_5_1500UA
}VSEP_Slew_Group_5_T;

typedef enum
{
   VSEP_SLEW_GROUP_CAN_500KBPS,
   VSEP_SLEW_GROUP_CAN_250KBPS,
   VSEP_SLEW_GROUP_CAN_125KBPS,
   VSEP_SLEW_GROUP_CAN_1MBPS
}VSEP_Slew_Group_CAN_T;

//=============================================================================
// VSEP_Set_Slew_Group_1
//
// @func Set slew group 1 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Slew_Group_1_4_T | y | A <t VSEP_Slew_Group_1_4_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Slew_Group_1_4_T>
//
// @end
//=============================================================================
#define VSEP_Set_Slew_Group_1(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SLEW_CONFIGURATION_POSITION_1, VSEP_SLEW_CONFIGURATION_WIDTH_1 ) )

//=============================================================================
// VSEP_Get_Slew_Group_1
//
// @func Get slew group 1 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Slew_Group_1_4_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Slew_Group_1(x) \
   (VSEP_Slew_Group_1_4_T)( Extract_Bits( x, VSEP_SLEW_CONFIGURATION_POSITION_1, VSEP_SLEW_CONFIGURATION_WIDTH_1 ) )

//=============================================================================
// VSEP_Set_Slew_Group_2
//
// @func Set slew group 2 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Slew_Group_2_3_T | y | A <t VSEP_Slew_Group_2_3_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Slew_Group_2_3_T>
//
// @end
//=============================================================================
#define VSEP_Set_Slew_Group_2(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SLEW_CONFIGURATION_POSITION_2, VSEP_SLEW_CONFIGURATION_WIDTH_2 ) )

//=============================================================================
// VSEP_Get_Slew_Group_2
//
// @func Get slew group 2 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Slew_Group_2_3_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Slew_Group_2(x) \
   (VSEP_Slew_Group_2_3_T)( Extract_Bits( x, VSEP_SLEW_CONFIGURATION_POSITION_2, VSEP_SLEW_CONFIGURATION_WIDTH_2 ) )

//=============================================================================
// VSEP_Set_Slew_Group_3
//
// @func Set slew 3 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Slew_Group_2_3_T | y | A <t VSEP_Slew_Group_2_3_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Slew_Group_2_3_T>
//
// @end
//=============================================================================
#define VSEP_Set_Slew_Group_3(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SLEW_CONFIGURATION_POSITION_3, VSEP_SLEW_CONFIGURATION_WIDTH_3 ) )

//=============================================================================
// VSEP_Get_Slew_Group_3
//
// @func Get slew group 3 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Slew_Group_2_3_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Slew_Group_3(x) \
   (VSEP_Slew_Group_2_3_T)( Extract_Bits( x, VSEP_SLEW_CONFIGURATION_POSITION_3, VSEP_SLEW_CONFIGURATION_WIDTH_3 ) )

//=============================================================================
// VSEP_Set_Slew_Group_4
//
// @func Set slew group 4 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Slew_Group_1_4_T | y | A <t VSEP_Slew_Group_1_4_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Slew_Group_1_4_T>
//
// @end
//=============================================================================
#define VSEP_Set_Slew_Group_4(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SLEW_CONFIGURATION_POSITION_4, VSEP_SLEW_CONFIGURATION_WIDTH_4 ) )

//=============================================================================
// VSEP_Get_Slew_Group_4
//
// @func Get slew group 4 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Slew_Group_1_4_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Slew_Group_4(x) \
   (VSEP_Slew_Group_1_4_T)( Extract_Bits( x, VSEP_SLEW_CONFIGURATION_POSITION_4, VSEP_SLEW_CONFIGURATION_WIDTH_4 ) )

//=============================================================================
// VSEP_Set_Slew_Group_5
//
// @func Set slew group 5 configuration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Slew_Group_5_T | y | A <t VSEP_Slew_Group_5_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Slew_Group_5_T>
//
// @end
//=============================================================================
#define VSEP_Set_Slew_Group_5(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SLEW_CONFIGURATION_POSITION_5, VSEP_SLEW_CONFIGURATION_WIDTH_5 ) )

//=============================================================================
// VSEP_Get_Slew_Group_5
//
// @func Get slew 5 configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Slew_Group_5_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Slew_Group_5(x) \
   (VSEP_Slew_Group_5_T)( Extract_Bits( x, VSEP_SLEW_CONFIGURATION_POSITION_5, VSEP_SLEW_CONFIGURATION_WIDTH_5 ) )

//=============================================================================
// VSEP_Set_Slew_Group_CAN
//
// @func Set slew group CANconfiguration
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Slew_Group_CAN_T | y | A <t VSEP_Slew_Group_CAN_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Slew_Group_CAN_T>
//
// @end
//=============================================================================
#define VSEP_Set_Slew_Group_CAN(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_SLEW_CONFIGURATION_POSITION_CAN, VSEP_SLEW_CONFIGURATION_WIDTH_CAN ) )

//=============================================================================
// VSEP_Get_Slew_Group_CAN
//
// @func Get slew CAN configuration
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Slew_Group_CAN_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Slew_Group_CAN(x) \
   (VSEP_Slew_Group_CAN_T)( Extract_Bits( x, VSEP_SLEW_CONFIGURATION_POSITION_CAN, VSEP_SLEW_CONFIGURATION_WIDTH_CAN ) )

typedef enum
{
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_1TO8SP     = 0,  // [ 1: 0] 1TO8SP
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_1TO8NSP    = 2,  // [ 3: 2] 1TO8NSP
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_9TO12      = 4,  // [ 5: 4] 9TO12
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_13TO16     = 6,  // [ 7: 6] 13TO16
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_17TO18     = 8,  // [ 9: 8] 17TO18
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_19TO20     =10,  // [11:10] 19TO20
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_21TO24     =12,  // [13:12] 21TO24
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_25TO30     =14   // [15:14] 25TO30

}VSEP_Fault_Filter_Time_Configuration_Position_T;

typedef enum
{
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_1TO8SP        = 2,  // [ 1: 0] 1TO8SP
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_1TO8NSP       = 2,  // [ 3: 2] 1TO8NSP
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_9TO12         = 2,  // [ 5: 4] 9TO12
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_13TO16        = 2,  // [ 7: 6] 13TO16
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_17TO18        = 2,  // [ 9: 8] 17TO18
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_19TO20        = 2,  // [11:10] 19TO20
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_21TO24        = 2,  // [13:12] 21TO24
   VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_25TO30        = 2   // [15:14] 25TO30

}VSEP_Fault_Filter_Configuration_Width_T;

typedef enum
{
   VSEP_FAULT_FILTER_7_5US,
   VSEP_FAULT_FILTER_15US,
   VSEP_FAULT_FILTER_34US,
   VSEP_FAULT_FILTER_46US,
   VSEP_FAULT_FILTER_MAX
}VSEP_FAULT_FILTER_T;

#define VSEP_FAULT_FILTER_Set_1TO8SP_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_1TO8SP, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_1TO8SP ) )

#define VSEP_FAULT_FILTER_Get_1TO8SP_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_1TO8SP, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_1TO8SP ) )

#define VSEP_FAULT_FILTER_Set_1TO8NSP_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_1TO8NSP, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_1TO8NSP ) )

#define VSEP_FAULT_FILTER_Get_1TO8NSP_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_1TO8NSP, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_1TO8NSP ) )

#define VSEP_FAULT_FILTER_Set_9TO12_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_9TO12, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_9TO12 ) )

#define VSEP_FAULT_FILTER_Get_9TO12_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_9TO12, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_9TO12 ) )

#define VSEP_FAULT_FILTER_Set_13TO16_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_13TO16, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_13TO16 ) )

#define VSEP_FAULT_FILTER_Get_13TO16_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_13TO16, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_13TO16 ) )

#define VSEP_FAULT_FILTER_Set_17TO18_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_17TO18, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_17TO18 ) )

#define VSEP_FAULT_FILTER_Get_17TO18_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_17TO18, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_17TO18 ) )

#define VSEP_FAULT_FILTER_Set_19TO20_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_19TO20, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_19TO20 ) )

#define VSEP_FAULT_FILTER_Get_19TO20_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_19TO20, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_19TO20 ) )

#define VSEP_FAULT_FILTER_Set_21TO24_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_21TO24, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_21TO24 ) )

#define VSEP_FAULT_FILTER_Get_21TO24_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_21TO24, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_21TO24 ) )

#define VSEP_FAULT_FILTER_Set_25TO30_Time( configuration, time ) \
   (IO_Configuration_T)( Insert_Bits( configuration, time, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_25TO30, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_25TO30 ) )

#define VSEP_FAULT_FILTER_Get_25TO30_Time( configuration ) \
   (VSEP_FAULT_FILTER_T)( Extract_Bits( configuration, VSEP_FAULT_FILTER_TIME_CONFIGURATION_POSITION_25TO30, VSEP_FAULT_FILTER_TIME_CONFIGURATION_WIDTH_25TO30 ) )


typedef enum
{
   VSEP_INIT_TXD_MESSAGE_CTRL,
   VSEP_INIT_TXD_MESSAGE_VR_1,
   VSEP_INIT_TXD_MESSAGE_VR_2,
   VSEP_INIT_TXD_MESSAGE_DEPS,
   VSEP_INIT_TXD_MESSAGE_SLEW,
   VSEP_INIT_TXD_MESSAGE_FAULT_1_2_3_4,
   VSEP_INIT_TXD_MESSAGE_FAULT_5_6_7,
   VSEP_INIT_TXD_MESSAGE_FAULT_FILTER,
   VSEP_INIT_TXD_MESSAGE_LEDMODE,
   VSEP_INIT_TXD_MESSAGE_GRADIENT,
   VSEP_INIT_TXD_MESSAGE_EST_SELECT_MODE,
   VSEP_INIT_TXD_MESSAGE_EST_SELECT_INIT,
   VSEP_INIT_TXD_MESSAGE_MAX
}VSEP_Init_Txd_Message_T;

//=============================================================================
// VSEP_Set_Device_Index
//
// @func Set desired device index for the cell.
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Index_T | y | A <t VSEP_Index_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Index_T>
//
// @end
//=============================================================================
#define VSEP_Set_Device_Index(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_CONFIGURATION_POSITION_DEVICE_INDEX, VSEP_CONFIGURATION_WIDTH_DEVICE_INDEX ) )

//=============================================================================
// VSEP_Get_Device_Index
//
// @func Get desired device index for the cell.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Index_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Device_Index(x) \
   (VSEP_Index_T)( Extract_Bits( x, VSEP_CONFIGURATION_POSITION_DEVICE_INDEX, VSEP_CONFIGURATION_WIDTH_DEVICE_INDEX ) )

//=============================================================================
// VSEP_Set_Channel
//
// @func Set desired channel for the configuration.
//
// @parm IO_Configuration_T | x | The value of the configuration prior to modification
//
// @parm VSEP_Channel_T | y | A <t VSEP_Channel_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t VSEP_Channel_T>
//
// @end
//=============================================================================
#define VSEP_Set_Channel(x,y) \
   (IO_Configuration_T)( Insert_Bits( x, y, VSEP_CONFIGURATION_POSITION_CHANNEL, VSEP_CONFIGURATION_WIDTH_CHANNEL ) )

//=============================================================================
// VSEP_Get_Channel
//
// @func Get configured channel from the configuration.
//
// @parm IO_Configuration_T | x | A <t IO_Configuration_T> type
//
// @rdesc <t VSEP_Channel_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define VSEP_Get_Channel(x) \
   (VSEP_Channel_T)( Extract_Bits( x, VSEP_CONFIGURATION_POSITION_CHANNEL, VSEP_CONFIGURATION_WIDTH_CHANNEL ) )

#define VSEP_SetDiscreteState(function,state) \
      if(function ##_Flag & function ##_DiagMask) \
          DD_SetDiscrete(function,state) 

#define VSEP_ToggleDiscreteState(function) \
      if(function ##_Flag & function ##_DiagMask) \
          DD_ToggleDiscrete(function) 
          
#define VSEP_DISCRETE_Set_Output_Enable(inPin,inState) \
                                  VSEP_Channel_Enabled = (inState ? \
                                  (VSEP_Channel_Enabled | inPin ) : \
                                  (VSEP_Channel_Enabled & ~inPin ) )

#define VSEP_GRADCOUNT_DIVIDER (128)

extern const uint32_t VSEP_BASE_FREQUENCY;

extern const uint32_t VSEP_GRADCOUNT_BASE_FREQUENCY;

extern const uint8_t  VSEP_GRADCOUNT_FAULT_WINDOW;


#ifdef  VSEP_CALIBRATION_ENABLE

extern  uint16_t VSEP_INIT_TXD_INITIAL[VSEP_INIT_TXD_MESSAGE_MAX];
#else
extern const uint16_t VSEP_INIT_TXD_INITIAL[VSEP_INIT_TXD_MESSAGE_MAX];
#endif

#ifdef VSEP_EST_DIAGNOSTIC_DEBUG
extern uint8_t VSEP_EST_Select_Dwell_Current_Time[8];
extern uint8_t VSEP_EST_Select_GRADCOUNT_Current_Time[8];
#endif


//=============================================================================
// VSEP_Clear_Device
//
// @func Clear a device's global registers to its reset state.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc None
//
// @end
//=============================================================================
void VSEP_Clear_Device(
   IO_Configuration_T in_configuration);

//=============================================================================
// VSEP_SPI_Immediate_Transfer
//
// @func Interface function to transfer a VSEP message immediately
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
void VSEP_SPI_Immediate_Transfer( 
   IO_Configuration_T   in_configuration, 
   VSEP_Message_T       in_message );

#ifdef HW_TEST_SW
FAR_COS void VSEP_HWTEST_SPI_Immediate_Transfer( 
   IO_Configuration_T   in_configuration, 
   VSEP_Message_T       in_message );
#endif
/* FUNCTION: SPI_Port_Transfer_Vsep                                              */
/*===========================================================================*/
/* RETURN VALUE:                                                             */
/*   void                                    */
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
 void  VSEP_SPI_Port_Transfer(
					SPI_Message_Definition_T const *def);
FAR_COS void VSEP_Initialize_Device(void);
FAR_COS void VSEP_HWTEST_INIT_TXD_Initialize(uint16_t*	in_buffer,uint8_t device);
#endif // DD_VSEP_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       * 
 \*===========================================================================*/
