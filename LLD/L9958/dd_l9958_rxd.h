#ifndef DD_L9958_RXD_H
#define DD_L9958_RXD_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_rxd.h %
//
// created_by:       hz23l2
//
// date_created:     Mon Apr 02 13:53:42 2007
//
// %derived_by:       jznxv7 %
//
// %date_modified:    %
//
// %version:         1 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================
#include "io_type.h"
#include "dd_l9958_txd.h"

typedef enum 
{
   L9958_FAULT_STATUS_WIDTH    =  16

} L9958_Fault_Status_Width_T;

typedef enum 
{
   L9958_FAULT_STATUS_POSITION    =  0
} L9958_Fault_Status_Position_T;

typedef enum
{
	L9958_DIAG_WIDTH_OL_OFF             = 1, // [   0 ] DIAG_RST_DIS 
	L9958_DIAG_WIDTH_OL_ON              = 1, // [   1 ] CL_1, CL_2 
	L9958_DIAG_WIDTH_VS_UV              = 1, // [   2 ] VSR Value 
	L9958_DIAG_WIDTH_VDD_OV             = 1, // [   3 ] ISR Value 
	L9958_DIAG_WIDTH_ILIM               = 1, // [   4 ] ISR_DIS 
	L9958_DIAG_WIDTH_TWARN              = 1, // [   5 ] OL_ON 
	L9958_DIAG_WIDTH_TSD                = 1, // [   6 ] OL_ON 
	L9958_DIAG_WIDTH_ACT                = 1, // [   7 ] OL_ON 
	L9958_DIAG_WIDTH_OC_LS1             = 1, // [   8 ] OL_ON 
	L9958_DIAG_WIDTH_OC_LS2             = 1, // [   9 ] OL_ON 
	L9958_DIAG_WIDTH_OC_HS1             = 1, // [   10] OL_ON 
	L9958_DIAG_WIDTH_OC_HS2             = 1, // [   11] OL_ON 
	L9958_DIAG_WIDTH_NOT_USED           = 2, // [13:12] OL_ON 
	L9958_DIAG_WIDTH_SGND_OFF           = 1, // [   14] OL_ON 
	L9958_DIAG_WIDTH_SBAT_OFF           = 1  // [   15] OL_ON 
}L9958_Msg_DIAG_REG_Width_T;

typedef enum
{
	L9958_DIAG_POSITION_OL_OFF          = 0, // [   0 ] DIAG_RST_DIS 
	L9958_DIAG_POSITION_OL_ON           = 1, // [   1 ] CL_1, CL_2 
	L9958_DIAG_POSITION_VS_UV           = 2, // [   2 ] VSR Value 
	L9958_DIAG_POSITION_VDD_OV          = 3, // [   3 ] ISR Value 
	L9958_DIAG_POSITION_ILIM            = 4, // [   4 ] ISR_DIS 
	L9958_DIAG_POSITION_TWARN           = 5, // [   5 ] OL_ON 
	L9958_DIAG_POSITION_TSD             = 6, // [   6 ] OL_ON 
	L9958_DIAG_POSITION_ACT             = 7, // [   7 ] OL_ON 
	L9958_DIAG_POSITION_OC_LS1          = 8, // [   8 ] OL_ON 
	L9958_DIAG_POSITION_OC_LS2          = 9, // [   9 ] OL_ON 
	L9958_DIAG_POSITION_OC_HS1          = 10,// [   10] OL_ON 
	L9958_DIAG_POSITION_OC_HS2          = 11,// [   11] OL_ON 
	L9958_DIAG_POSITION_NOT_USED        = 12,// [13:12] OL_ON 
	L9958_DIAG_POSITION_SGND_OFF        = 14,// [   14] OL_ON 
	L9958_DIAG_POSITION_SBAT_OFF        = 15 // [   15] OL_ON 
}L9958_Msg_DIAG_REG_Position_T;

//=============================================================================
// L9958_Msg_Set_OL_OFF
//
// @func Sets the OL_OFF Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_OL_OFF( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_OL_OFF, L9958_DIAG_WIDTH_OL_OFF ) )

//=============================================================================
// L9958_Msg_Get_OL_OFF
//
// @func Gets the OL_OFF Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_OL_OFF( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_OL_OFF, L9958_DIAG_WIDTH_OL_OFF ) )

//=============================================================================
// L9958_Msg_Set_OL_ON
//
// @func Sets the OL_ON Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_OL_ON( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_OL_ON, L9958_DIAG_WIDTH_OL_ON ) )

//=============================================================================
// L9958_Msg_Get_OL_ON
//
// @func Gets the OL_ON Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_OL_ON( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_OL_ON, L9958_DIAG_WIDTH_OL_ON ) )

//=============================================================================
// L9958_Msg_Set_VS_UnderVolt
//
// @func Sets the VS Under Voltage bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_VS_UnderVolt( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_VS_UV, L9958_DIAG_WIDTH_VS_UV ) )

//=============================================================================
// L9958_Msg_Get_VS_UnderVolt
//
// @func Gets the VS Under Voltage bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_VS_UnderVolt( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_VS_UV, L9958_DIAG_WIDTH_VS_UV ) )

//=============================================================================
// L9958_Msg_Set_Vdd_OverVolt
//
// @func Sets the Vdd Over Voltage bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Vdd_OverVolt( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_VDD_OV, L9958_DIAG_WIDTH_VDD_OV ) )

//=============================================================================
// L9958_Msg_Get_Vdd_OverVolt
//
// @func Gets the Vdd Over Voltage bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_Vdd_OverVolt( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_VDD_OV, L9958_DIAG_WIDTH_VDD_OV ) )

//=============================================================================
// L9958_Msg_Set_Curr_LIM
//
// @func Sets the Current Limit Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Curr_LIM( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_ILIM, L9958_DIAG_WIDTH_ILIM ) )

//=============================================================================
// L9958_Msg_Get_Curr_LIM
//
// @func Gets the Current Limit Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_Curr_LIM( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_ILIM, L9958_DIAG_WIDTH_ILIM ) )

//=============================================================================
// L9958_Msg_Set_Temp_Warning
//
// @func Sets the Temperature Warning Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Temp_Warning( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_TWARN, L9958_DIAG_WIDTH_TWARN ) )

//=============================================================================
// L9958_Msg_Get_Temp_Warning
//
// @func Gets the Temperature Warning Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_Temp_Warning( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_TWARN, L9958_DIAG_WIDTH_TWARN ) )

//=============================================================================
// L9958_Msg_Set_OverTemp_Shutdown
//
// @func Sets the OverTemp Shutdown Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_OverTemp_Shutdown( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_TSD, L9958_DIAG_WIDTH_TSD ) )

//=============================================================================
// L9958_Msg_Get_OverTemp_Shutdown
//
// @func Gets the OverTemp Shutdown Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_OverTemp_Shutdown( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_TSD, L9958_DIAG_WIDTH_TSD ) )

//=============================================================================
// L9958_Msg_Set_Bridge_Enabled
//
// @func Sets the Bridge Enable Bit (ACT)
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Bridge_Enabled( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_ACT, L9958_DIAG_WIDTH_ACT ) )

//=============================================================================
// L9958_Msg_Get_Bridge_Enabled
//
// @func Gets the Bridge Enable (ACT) Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_Bridge_Enabled( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_ACT, L9958_DIAG_WIDTH_ACT ) )

//=============================================================================
// L9958_Msg_Set_OverCurr_LS1
//
// @func Sets the OverCurr_LS1 Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_OverCurr_LS1( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_OC_LS1, L9958_DIAG_WIDTH_OC_LS1 ) )

//=============================================================================
// L9958_Msg_Get_OverCurr_LS1
//
// @func Gets OverCurr_LS1 Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_OverCurr_LS1( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_OC_LS1, L9958_DIAG_WIDTH_OC_LS1 ) )

//=============================================================================
// L9958_Msg_Set_OverCurr_LS2
//
// @func Sets the OverCurr_LS2 Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_OverCurr_LS2( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_OC_LS2, L9958_DIAG_WIDTH_OC_LS2 ) )

//=============================================================================
// L9958_Msg_Get_OverCurr_LS2
//
// @func Gets the OverCurr_LS2 Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_OverCurr_LS2( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_OC_LS2, L9958_DIAG_WIDTH_OC_LS2 ) )

//=============================================================================
// L9958_Msg_Set_OverCurr_HS1
//
// @func Sets OverCurr_HS1 Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_OverCurr_HS1( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_OC_HS1, L9958_DIAG_WIDTH_OC_HS1 ) )

//=============================================================================
// L9958_Msg_Get_OverCurr_HS1
//
// @func Gets the OverCurr_HS1 Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_OverCurr_HS1( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_OC_HS1, L9958_DIAG_WIDTH_OC_HS1 ) )

//=============================================================================
// L9958_Msg_Set_OverCurr_HS2
//
// @func Sets the OverCurr_HS2 Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_OverCurr_HS2( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_OC_HS2, L9958_DIAG_WIDTH_OC_HS2 ) )

//=============================================================================
// L9958_Msg_Get_OverCurr_HS2
//
// @func Gets the OverCurr_HS2 Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_OverCurr_HS2( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_OC_HS2, L9958_DIAG_WIDTH_OC_HS2 ) )

//=============================================================================
// L9958_Msg_Set_Short_to_GND_in_OFF
//
// @func Sets the Short_to_GND_in_OFF Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Short_to_GND_in_OFF( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_SGND_OFF, L9958_DIAG_WIDTH_SGND_OFF ) )

//=============================================================================
// L9958_Msg_Get_Short_to_GND_in_OFF
//
// @func Gets the Short_to_GND_in_OFF Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_Short_to_GND_in_OFF( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_SGND_OFF, L9958_DIAG_WIDTH_SGND_OFF ) )

//=============================================================================
// L9958_Msg_Set_Short_to_BAT_in_OFF
//
// @func Sets the Short_to_BAT_in_OFF Bit
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc IO_Configuration_T
//
// @end
//=============================================================================
#define L9958_Msg_Set_Short_to_BAT_in_OFF( msg, y ) \
   (IO_Configuration_T)( Insert_Bits( msg, y, L9958_DIAG_POSITION_SBAT_OFF, L9958_DIAG_WIDTH_SBAT_OFF ) )

//=============================================================================
// L9958_Msg_Get_Short_to_BAT_in_OFF
//
// @func Gets the Short_to_BAT_in_OFF Bit value 
//
// @parm IO_Configuration_T | L9958_Index_T | 
//
// @rdesc bool
//
// @end
//=============================================================================
#define L9958_Msg_Get_Short_to_BAT_in_OFF( msg ) \
   (bool)( Extract_Bits( msg, L9958_DIAG_POSITION_SBAT_OFF, L9958_DIAG_WIDTH_SBAT_OFF ) )

//=============================================================================
// L9958_Msg_Get_Fault_Status
//
// @func  Sets the fault status 
//
// @parm L9958_Msg_Channel_T | L9958_Channel_T | 
//
// @rdesc L9958_Fault_Status_T
//
// @end
//=============================================================================
#define L9958_Msg_Get_Fault_Status( msg ) \
   (L9958_Fault_Status_T)( Extract_Bits( msg, L9958_FAULT_STATUS_POSITION, L9958_FAULT_STATUS_WIDTH ) )

#endif // DD_L9958_RXD_H
