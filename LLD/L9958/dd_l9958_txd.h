#ifndef DD_L9958_TXD_H
#define DD_L9958_TXD_H
//=============================================================================
//
//       COPYRIGHT, 2003, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//=============================================================================

typedef enum
{
	L9958_TXD_MESSAGE_CFG_REG,            //@emem Config Reg
	L9958_TXD_MESSAGE_DIAG_REG,          //@emem Diagnostics Reg
	L9958_TXD_MESSAGE_MAX 
}L9958_Txd_Message_T;


 //=============================================================================
// @enum L9958 Message configaration
//=============================================================================

typedef enum
{
	L9958_CFG_WIDTH_DIAG_RST_DISABLE               = 1, // [   1 ] DIAG_RST_DIS 
	L9958_CFG_WIDTH_REGULATION_CURR_LEVEL          = 2, // [ 3:2 ] CL_1, CL_2 
	L9958_CFG_WIDTH_VOLT_SLEW_CONTROL              = 1, // [   8 ] VSR Value 
	L9958_CFG_WIDTH_CURR_SLEW_CONTROL              = 1, // [   9 ] ISR Value 
	L9958_CFG_WIDTH_CURR_SLEW_CONTROL_DISABLE      = 1, // [  10 ] ISR_DIS 
	L9958_CFG_WIDTH_OPEN_LOAD_ON_ENABLE            = 1  // [  11 ] OL_ON 
}L9958_Msg_CFG_REG_Width_T;

typedef enum
{
	L9958_CFG_POSITION_DIAG_RST_DISABLE            = 1,  // [   1 ] DIAG_RST_DIS 
	L9958_CFG_POSITION_REGULATION_CURR_LEVEL       = 2,  // [ 3:2 ] CL_1, CL_2 
	L9958_CFG_POSITION_VOLT_SLEW_CONTROL           = 8,  // [   8 ] VSR Value 
	L9958_CFG_POSITION_CURR_SLEW_CONTROL           = 9,  // [   9 ] ISR Value 
	L9958_CFG_POSITION_CURR_SLEW_CONTROL_DISABLE   = 10, // [   10] ISR_DIS 
	L9958_CFG_POSITION_OPEN_LOAD_ON_ENABLE         = 11  // [   11] OL_ON 
}L9958_Msg_CFG_REG_Position_T;


typedef enum 
{
   L9958_DIAG_RST_DISABLE_FLASE,
   L9958_DIAG_RST_DISABLE_TRUE

}L9958_DIAG_RST_DISABLE_T;

//=============================================================================
// L9958_Msg_Set_Diag_Reset_Disable
//
// @func Sets the Dwell time Prescale
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Diag_Reset_Disable( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y,  L9958_CFG_POSITION_DIAG_RST_DISABLE, L9958_CFG_WIDTH_DIAG_RST_DISABLE   ) )

//=============================================================================
// L9958_Msg_Get_Diag_Reset_Disable
//
// @func Gets the Diag reset Disable Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_DIAG_RST_DISABLE_T
//
// @end
//=============================================================================
#define L9958_Msg_Get_Diag_Reset_Disable( msg ) \
   (L9958_DIAG_RST_DISABLE_T)( Extract_Bits( msg, L9958_CFG_POSITION_DIAG_RST_DISABLE , L9958_CFG_WIDTH_DIAG_RST_DISABLE  ) )


typedef enum
{
   L9958_CURRENT_LEVEL_2P5,
   L9958_CURRENT_LEVEL_4,
   L9958_CURRENT_LEVEL_6P6,
   L9958_CURRENT_LEVEL_8P6

}L9958_CURRENT_LEVEL_T;

//=============================================================================
// L9958_Msg_Set_Regulation_Curr_Level
//
// @func Sets the Regulation current level 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Regulation_Curr_Level( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_CFG_POSITION_REGULATION_CURR_LEVEL , L9958_CFG_WIDTH_REGULATION_CURR_LEVEL  ) )

//=============================================================================
// L9958_Msg_Get_Regulation_Curr_Level
//
// @func Gets the Regulation Current level value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_CURRENT_LEVEL_T
//
// @end
//=============================================================================
#define L9958_Msg_Get_Regulation_Curr_Level( msg ) \
   (L9958_CURRENT_LEVEL_T)( Extract_Bits( msg,L9958_CFG_POSITION_REGULATION_CURR_LEVEL , L9958_CFG_WIDTH_REGULATION_CURR_LEVEL  ) )


typedef enum 
{
   L9958_VSR_LO,
   L9958_VSR_HI 

}L9958_VSR_CONTROL_T;

//=============================================================================
// L9958_Msg_Set_Voltage_Slew_Control
//
// @func Sets the Voltage Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Voltage_Slew_Control( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_CFG_POSITION_VOLT_SLEW_CONTROL , L9958_CFG_WIDTH_VOLT_SLEW_CONTROL ) )

//=============================================================================
// L9958_Msg_Get_Voltage_Slew_Control
//
// @func Gets the Voltage Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_VSR_CONTROL_T
//
// @end
//=============================================================================
#define L9958_Msg_Get_Voltage_Slew_Control( msg ) \
   (L9958_VSR_CONTROL_T)( Extract_Bits( msg, L9958_CFG_POSITION_VOLT_SLEW_CONTROL , L9958_CFG_WIDTH_VOLT_SLEW_CONTROL ) )


typedef enum 
{
   L9958_ISR_LO,
   L9958_ISR_HI 

}L9958_ISR_CONTROL_T;

//=============================================================================
// L9958_Msg_Set_Current_Slew_Control
//
// @func Sets the Current Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Current_Slew_Control( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_CFG_POSITION_CURR_SLEW_CONTROL , L9958_CFG_WIDTH_CURR_SLEW_CONTROL ) )

//=============================================================================
// L9958_Msg_Get_Current_Slew_Control
//
// @func Gets the Current Slew rate control value
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_ISR_CONTROL_T
//
// @end
//=============================================================================
#define L9958_Msg_Get_Current_Slew_Control( msg ) \
   (L9958_ISR_CONTROL_T)( Extract_Bits( msg, L9958_CFG_POSITION_CURR_SLEW_CONTROL , L9958_CFG_WIDTH_CURR_SLEW_CONTROL ) )


typedef enum 
{
   L9958_ISR_DISABLE_FALSE,
   L9958_ISR_DISABLE_TRUE  

}L9958_ISR_DISABLE_T;

//=============================================================================
// L9958_Msg_Set_Current_Slew_Control_Disable
//
// @func Sets the Current Slew rate control Disable/Enable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Current_Slew_Control_Disable( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_CFG_POSITION_CURR_SLEW_CONTROL_DISABLE , L9958_CFG_WIDTH_CURR_SLEW_CONTROL_DISABLE ) )

//=============================================================================
// L9958_Msg_Get_Current_Slew_Control_Disable
//
// @func Gets the Current Slew rate control Disable/Enable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_ISR_DISABLE_T
//
// @end
//=============================================================================
#define L9958_Msg_Get_Current_Slew_Control_Disable( msg ) \
   (L9958_ISR_DISABLE_T)( Extract_Bits( msg, L9958_CFG_POSITION_CURR_SLEW_CONTROL_DISABLE , L9958_CFG_WIDTH_CURR_SLEW_CONTROL_DISABLE ) )


typedef enum 
{
   L9958_OPEN_LOAD_ON_DISABLE, 
   L9958_OPEN_LOAD_ON_ENABLE 

}L9958_OPEN_LOAD_ON_T;

//=============================================================================
// L9958_Msg_Set_Open_Load_in_ON_Enable
//
// @func Sets the Open load in ON state Enable/Disable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Open_Load_in_ON_Enable( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_CFG_POSITION_OPEN_LOAD_ON_ENABLE, L9958_CFG_WIDTH_OPEN_LOAD_ON_ENABLE ) )

//=============================================================================
// L9958_Msg_Get_Open_Load_in_ON_Enable
//
// @func Gets the Open load in ON state Enable/Disable
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc L9958_OPEN_LOAD_ON_T
//
// @end
//=============================================================================
#define L9958_Msg_Get_Open_Load_in_ON_Enable( msg ) \
   (L9958_OPEN_LOAD_ON_T)( Extract_Bits( msg, L9958_CFG_POSITION_OPEN_LOAD_ON_ENABLE , L9958_CFG_WIDTH_OPEN_LOAD_ON_ENABLE ) )


#endif
