#ifndef DD_L9958_H
#define DD_L9958_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958.h %
//
// created_by:       zz2t4p
//
// date_created:     Wed Mar 28 10:53:44 2007
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   %
//
// %version:         mt20u2#2 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

#include "io_type.h"


#include "dd_L9958_config.h"
#include "dd_L9958_txd.h"
//#include "dd_L9958_rxd.h"

extern const uint16_t  L9958_TXD_INITIAL[ NUMBER_OF_L9958 ];
extern uint16_t        L9958_Txd[ NUMBER_OF_L9958 ];
extern uint16_t        L9958_Rxd[ NUMBER_OF_L9958 ];

typedef enum
{
   L9958_INDEX_0,        //@emem Device index 0
   L9958_INDEX_1,        //@emem Device index 1
   L9958_INDEX_2,        //@emem Device index 2
   L9958_INDEX_3,        //@emem Device index 3
   L9958_INDEX_MAX       //@emem Device index Max

} L9958_Index_T;

typedef enum
{   
   L9958_REG_CONFIG_POSITION_DEVICE_INDEX              = 0, // [ 1:0 ] Device Index
   L9958_REG_CONFIG_POSITION_DIAG_RST_DISABLE          = 2, // [   2 ] DIAG_RST_DISABLE
   L9958_REG_CONFIG_POSITION_REGULATION_CURR_LEVEL     = 3, // [ 4:3 ] CL_1, CL_2 (Regulation Current)
   L9958_REG_CONFIG_POSITION_VOLT_SLEW_CONTROL         = 5, // [   5 ] Volt Slew Control Reg (VSR)
   L9958_REG_CONFIG_POSITION_CURR_SLEW_CONTROL         = 6, // [   6 ] Curr Slew Control Reg(ISR)
   L9958_REG_CONFIG_POSITION_CURR_SLEW_CONTROL_DISABLE = 7, // [   7 ] ISR Disable
   L9958_REG_CONFIG_POSITION_OPEN_LOAD_ON_ENABLE       = 8  // [   8 ] Open Load ON Enable

}L9958_REG_Configuration_Position_T;

typedef enum
{
   L9958_REG_CONFIG_WIDTH_DEVICE_INDEX                = 2, // [ 1:0 ] Device Index
   L9958_REG_CONFIG_WIDTH_DIAG_RST_DISABLE            = 1, // [   2 ] DIAG_RST_DISABLE
   L9958_REG_CONFIG_WIDTH_REGULATION_CURR_LEVEL       = 2, // [ 4:3 ] CL_1, CL_2 (Regulation Current)
   L9958_REG_CONFIG_WIDTH_VOLT_SLEW_CONTROL           = 1, // [   5 ] Volt Slew Control Reg (VSR)
   L9958_REG_CONFIG_WIDTH_CURR_SLEW_CONTROL           = 1, // [   6 ] Curr Slew Control Reg (ISR)
   L9958_REG_CONFIG_WIDTH_CURR_SLEW_CONTROL_DISABLE   = 1, // [   7 ] ISR Disable
   L9958_REG_CONFIG_WIDTH_OPEN_LOAD_ON_ENABLE         = 1  // [   8 ] Open Load ON Enable

}L9958_REG_Configuration_Width_T;

#define MTSA_CONFIG_L9958_DEVICE_0			( (IO_Configuration_T)(0) )
//=============================================================================
// L9958_Get_Device_Index
//
// @func Gets the Device number.
//
// @parm IO_Configuration_T | context | 
//
// @rdesc L9958_Index_T
//
// @end
//=============================================================================
#define L9958_Get_Device_Index( x ) \
   (L9958_Index_T)( Extract_Bits( x, L9958_REG_CONFIG_POSITION_DEVICE_INDEX, L9958_REG_CONFIG_WIDTH_DEVICE_INDEX ) )

//=============================================================================
// L9958_Set_Device_Index
//
// @func Sets the Device number.
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Set_Device_Index( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, L9958_REG_CONFIG_POSITION_DEVICE_INDEX, L9958_REG_CONFIG_WIDTH_DEVICE_INDEX ) )

//=============================================================================
// L9958_Set_Diag_Reset_Disable
//
// @func Sets the Diagnostic Reset Disable/Enable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Set_Diag_Reset_Disable( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, L9958_REG_CONFIG_POSITION_DIAG_RST_DISABLE, L9958_REG_CONFIG_WIDTH_DIAG_RST_DISABLE ) )

//=============================================================================
// L9958_Get_Diag_Reset_Disable
//
// @func Gets the Diag reset Disable Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_DIAG_RST_DISABLE_T
//
// @end
//=============================================================================
#define L9958_Get_Diag_Reset_Disable( x ) \
   (L9958_DIAG_RST_DISABLE_T)( Extract_Bits( x, L9958_REG_CONFIG_POSITION_DIAG_RST_DISABLE , L9958_REG_CONFIG_WIDTH_DIAG_RST_DISABLE ) )

//=============================================================================
// L9958_Set_Regulation_Curr_Level
//
// @func Sets the Regulation current level 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Set_Regulation_Curr_Level( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, L9958_REG_CONFIG_POSITION_REGULATION_CURR_LEVEL , L9958_REG_CONFIG_WIDTH_REGULATION_CURR_LEVEL ) )

//=============================================================================
// L9958_Get_Regulation_Curr_Level
//
// @func Gets the Regulation Current level value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_CURRENT_LEVEL_T
//
// @end
//=============================================================================
#define L9958_Get_Regulation_Curr_Level( x ) \
   (L9958_CURRENT_LEVEL_T)( Extract_Bits( x, L9958_REG_CONFIG_POSITION_REGULATION_CURR_LEVEL , L9958_REG_CONFIG_WIDTH_REGULATION_CURR_LEVEL ) )

//=============================================================================
// L9958_Set_Voltage_Slew_Control
//
// @func Sets the Voltage Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Set_Voltage_Slew_Control( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, L9958_REG_CONFIG_POSITION_VOLT_SLEW_CONTROL , L9958_REG_CONFIG_WIDTH_VOLT_SLEW_CONTROL ) )

//=============================================================================
// L9958_Voltage_Slew_Control
//
// @func Gets the Voltage Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_VSR_CONTROL_T
//
// @end
//=============================================================================
#define L9958_Get_Voltage_Slew_Control( x ) \
   (L9958_VSR_CONTROL_T)( Extract_Bits( x, L9958_REG_CONFIG_POSITION_VOLT_SLEW_CONTROL , L9958_REG_CONFIG_WIDTH_VOLT_SLEW_CONTROL ) )

//=============================================================================
// L9958_Set_Current_Slew_Control
//
// @func Sets the Current Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Set_Current_Slew_Control( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, L9958_REG_CONFIG_POSITION_CURR_SLEW_CONTROL , L9958_REG_CONFIG_WIDTH_CURR_SLEW_CONTROL ) )

//=============================================================================
// L9958_Get_Current_Slew_Control
//
// @func Gets the Current Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_ISR_CONTROL_T
//
// @end
//=============================================================================
#define L9958_Get_Current_Slew_Control( x ) \
   (L9958_ISR_CONTROL_T)( Extract_Bits( x, L9958_REG_CONFIG_POSITION_CURR_SLEW_CONTROL , L9958_REG_CONFIG_WIDTH_CURR_SLEW_CONTROL ) )

//=============================================================================
// L9958_Set_Current_Slew_Control_Disable
//
// @func Sets the Current Slew rate control Disable/Enable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Set_Current_Slew_Control_Disable( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, L9958_REG_CONFIG_POSITION_CURR_SLEW_CONTROL_DISABLE , L9958_REG_CONFIG_WIDTH_CURR_SLEW_CONTROL_DISABLE ) )

//=============================================================================
// L9958_Current_Slew_Control_Disable
//
// @func Gets the Current Slew rate control Disable/Enable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_ISR_DISABLE_T
//
// @end
//=============================================================================
#define L9958_Get_Current_Slew_Control_Disable( x ) \
   (L9958_ISR_DISABLE_T)( Extract_Bits( x, L9958_REG_CONFIG_POSITION_CURR_SLEW_CONTROL_DISABLE , L9958_REG_CONFIG_WIDTH_CURR_SLEW_CONTROL_DISABLE ) )

//=============================================================================
// L9958_Set_Open_Load_in_ON_Enable
//
// @func Sets the Open load in ON state Enable/Disable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Set_Open_Load_in_ON_Enable( x, y ) \
   (IO_Configuration_T)( Insert_Bits( x, y, L9958_REG_CONFIG_POSITION_OPEN_LOAD_ON_ENABLE, L9958_REG_CONFIG_WIDTH_OPEN_LOAD_ON_ENABLE ) )

//=============================================================================
// L9958_Get_Open_Load_in_ON_Enable
//
// @func Gets the Open load in ON state Enable/Disable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_OPEN_LOAD_ON_T
//
// @end
//=============================================================================
#define L9958_Get_Open_Load_in_ON_Enable( x ) \
   (L9958_OPEN_LOAD_ON_T)( Extract_Bits( x, L9958_REG_CONFIG_POSITION_OPEN_LOAD_ON_ENABLE , L9958_REG_CONFIG_WIDTH_OPEN_LOAD_ON_ENABLE ) )


//===========================================================================
// L9958_Device_Initialize
//
// @func This function initializes L9958 
//
// @parm IO_Configuration_T| in_configuration |
//
// @rdesc None. 
//
// @end
//===========================================================================
FAR_COS void L9958_Device_Initialize(IO_Configuration_T in_configuration);


//===========================================================================
// L9958_Diag_Rst_Disable_Set
//
// @func This function sets the Diag reset Disable TRUE/FALSE
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_DIAG_RST_DISABLE_T|    in_diag_rst_disable|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Diag_Rst_Disable_Set( 
   IO_Configuration_T          in_configuration,
   L9958_DIAG_RST_DISABLE_T    in_diag_rst_disable);


//===========================================================================
// L9958_Diag_Rst_Disable_Set_Immediate
//
// @func  This function sets the Diag reset Disable TRUE/FALSE immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_DIAG_RST_DISABLE_T|    in_diag_rst_disable|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Diag_Rst_Disable_Set_Immediate( 
   IO_Configuration_T         in_configuration,
   L9958_DIAG_RST_DISABLE_T   in_diag_rst_disable);


//===========================================================================
// L9958_Regulation_Curr_Level_Set
//
// @func This function sets the Regulation Current Level
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_CURRENT_LEVEL_T|    in_curr_level|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Regulation_Curr_Level_Set( 
   IO_Configuration_T     in_configuration,
   L9958_CURRENT_LEVEL_T  in_curr_level);


//===========================================================================
// L9958_Regulation_Curr_Level_Set_Immediate
//
// @func  This function sets the Regulation Current Level immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_CURRENT_LEVEL_T|    in_curr_level|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Regulation_Curr_Level_Set_Immediate( 
   IO_Configuration_T     in_configuration,
   L9958_CURRENT_LEVEL_T  in_diag_rst_disable);


//===========================================================================
// L9958_VSR_Set
//
// @func This function sets the Voltage Slew Control Hi /LO
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_VSR_CONTROL_T|    in_volt_slew|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_VSR_Set( 
   IO_Configuration_T    in_configuration,
   L9958_VSR_CONTROL_T   in_volt_slew);


//===========================================================================
// L9958_VSR_Set_Immediate
//
// @func  This function sets the Voltage Slew Control Hi /LO immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_VSR_CONTROL_T|    in_volt_slew|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_VSR_Set_Immediate( 
   IO_Configuration_T    in_configuration,
   L9958_VSR_CONTROL_T   in_volt_slew);


//===========================================================================
// L9958_ISR_Set
//
// @func This function sets the Current Slew Control Hi /LO
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_ISR_CONTROL_T|    in_curr_slew|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Set( 
   IO_Configuration_T    in_configuration,
   L9958_ISR_CONTROL_T   in_curr_slew);


//===========================================================================
// L9958_Current_Slew_Control_Set_Immediate
//
// @func  This function sets the Current Slew Control Hi /LO immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_ISR_CONTROL_T|    in_curr_slew|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Set_Immediate( 
   IO_Configuration_T    in_configuration,
   L9958_ISR_CONTROL_T   in_volt_slew);


//===========================================================================
// L9958_Current_Slew_Control_Disable_Set
//
// @func This function sets the Current Slew Control Disable TRUE /FALSE
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_ISR_DISABLE_T|    in_curr_slew_Disable|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Disable_Set( 
   IO_Configuration_T    in_configuration,
   L9958_ISR_DISABLE_T   in_curr_slew_Disable);


//===========================================================================
// L9958_ISR_Disable_Set_Immediate
//
// @func  This function sets the Current Slew Control Disable TRUE /FALSE  immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_ISR_DISABLE_T|    in_curr_slew_Disable|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Disable_Set_Immediate( 
   IO_Configuration_T    in_configuration,
   L9958_ISR_DISABLE_T   in_curr_slew_Disable);


//===========================================================================
// L9958_OL_ON_Enable_Set
//
// @func This function sets the Open Load in ON Enable Enable/Disable
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_OPEN_LOAD_ON_T|    in_open_load_state|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_OL_ON_Enable_Set( 
   IO_Configuration_T    in_configuration,
   L9958_OPEN_LOAD_ON_T  in_open_load_state);


//===========================================================================
// L9958_OL_ON_Enable_Set_Immediate
//
// @func  This function sets the Open load in ON state Enable /Disable  immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_OPEN_LOAD_ON_T|    in_open_load_state|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_OL_ON_Enable_Set_Immediate( 
   IO_Configuration_T     in_configuration,
   L9958_OPEN_LOAD_ON_T   in_open_load_state);


//===========================================================================
// L9958_Clear_Device
//
// @func This function clears the device
//
// @parm IO_Configuration_T| in_configuration | .
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Clear_Device(
   IO_Configuration_T in_configuration);


//===========================================================================
// L9958_Fault_Diagnose_Channels
//
// @func This function 
//
// @parm L9958_Index_T
//
// @rdesc None. 
//
// @end
//===========================================================================
FAR_COS void L9958_Fault_Diagnose_Channels(
   IO_Configuration_T in_configuration );


#endif // DD_L9958_H
