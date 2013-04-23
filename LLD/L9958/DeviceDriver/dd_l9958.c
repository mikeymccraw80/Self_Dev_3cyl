//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958.c %
//
// created_by:       hz23l2
//
// date_created:     Thu Mar 29 19:53:36 2006
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
//=============================================================================
// Include the Type file for the device driver and io layers
//=============================================================================
//#include "io_type.h"

//=============================================================================
// Include interface for the device driver
//=============================================================================
#include "dd_l9958.h"
#include "dd_l9958_txd.h"
#include "dd_l9958_rxd.h"
//#include "dd_config.h"

//=============================================================================
// L9958_DISCRETE_Device_Initialize
//=============================================================================
void L9958_Device_Initialize(
   IO_Configuration_T in_configuration)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ] = L9958_TXD_INITIAL[ index ];

   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_CFG_REG );
}

//===========================================================================
// L9958_Diag_Rst_Disable_Set
//===========================================================================
void L9958_Diag_Rst_Disable_Set( 
   IO_Configuration_T          in_configuration,
   L9958_DIAG_RST_DISABLE_T    in_diag_rst_disable)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ] = 
      L9958_Msg_Set_Diag_Reset_Disable( L9958_Txd[ index ], in_diag_rst_disable );
   
}

//===========================================================================
// L9958_Diag_Rst_Disable_Set_Immediate
//===========================================================================
void L9958_Diag_Rst_Disable_Set_Immediate( 
   IO_Configuration_T         in_configuration,
   L9958_DIAG_RST_DISABLE_T   in_diag_rst_disable)
{
   L9958_Diag_Rst_Disable_Set(in_configuration, in_diag_rst_disable);
   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_CFG_REG );
   
}

//===========================================================================
// L9958_Regulation_Curr_Level_Set
//===========================================================================
void L9958_Regulation_Curr_Level_Set( 
   IO_Configuration_T      in_configuration,
   L9958_CURRENT_LEVEL_T   in_curr_level)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ] = 
      L9958_Msg_Set_Regulation_Curr_Level( L9958_Txd[ index ], in_curr_level );

}

//===========================================================================
// L9958_Regulation_Curr_Level_Set_Immediate
//===========================================================================
void L9958_Regulation_Curr_Level_Set_Immediate( 
   IO_Configuration_T      in_configuration,
   L9958_CURRENT_LEVEL_T   in_diag_rst_disable)
{
   L9958_Regulation_Curr_Level_Set(in_configuration, in_diag_rst_disable );
   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_CFG_REG ); 
   
}

//===========================================================================
// L9958_VSR_Set
//===========================================================================
void L9958_VSR_Set( 
   IO_Configuration_T     in_configuration,
   L9958_VSR_CONTROL_T    in_volt_slew)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ] = 
      L9958_Msg_Set_Voltage_Slew_Control( L9958_Txd[ index ], in_volt_slew );

}

//===========================================================================
// L9958_VSR_Set_Immediate
//===========================================================================
void L9958_VSR_Set_Immediate( 
   IO_Configuration_T    in_configuration,
   L9958_VSR_CONTROL_T   in_volt_slew)
{
   L9958_VSR_Set( in_configuration, in_volt_slew);
   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_CFG_REG ); 
   
}

//===========================================================================
// L9958_ISR_Set
//===========================================================================
void L9958_ISR_Set( 
   IO_Configuration_T     in_configuration,
   L9958_ISR_CONTROL_T    in_curr_slew)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ] = 
      L9958_Msg_Set_Current_Slew_Control( L9958_Txd[ index ], in_curr_slew );

}

//===========================================================================
// L9958_Current_Slew_Control_Set_Immediate
//===========================================================================
void L9958_ISR_Set_Immediate( 
   IO_Configuration_T    in_configuration,
   L9958_ISR_CONTROL_T   in_curr_slew)
{
   L9958_ISR_Set( in_configuration, in_curr_slew);
   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_CFG_REG );
   
}

//===========================================================================
// L9958_Current_Slew_Control_Disable_Set
//===========================================================================
void L9958_ISR_Disable_Set( 
   IO_Configuration_T     in_configuration,
   L9958_ISR_DISABLE_T    in_curr_slew_Disable)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ]= 
      L9958_Msg_Set_Current_Slew_Control_Disable( L9958_Txd[ index ], in_curr_slew_Disable );
   
}

//===========================================================================
// L9958_ISR_Disable_Set_Immediate
//===========================================================================
void L9958_ISR_Disable_Set_Immediate( 
   IO_Configuration_T    in_configuration,
   L9958_ISR_DISABLE_T   in_curr_slew_Disable)
{
   L9958_ISR_Disable_Set(in_configuration, in_curr_slew_Disable);
   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_CFG_REG );
   
}

//===========================================================================
// L9958_OL_ON_Enable_Set
//===========================================================================
void L9958_OL_ON_Enable_Set( 
   IO_Configuration_T      in_configuration,
   L9958_OPEN_LOAD_ON_T    in_open_load_state)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ] = 
      L9958_Msg_Set_Open_Load_in_ON_Enable( L9958_Txd[ index ], in_open_load_state );
   
}

//===========================================================================
// L9958_OL_ON_Enable_Set_Immediate
//===========================================================================
void L9958_OL_ON_Enable_Set_Immediate( 
   IO_Configuration_T     in_configuration,
   L9958_OPEN_LOAD_ON_T   in_open_load_state)
{
   L9958_OL_ON_Enable_Set(in_configuration, in_open_load_state);
   L9958_SPI_Immediate_Transfer( in_configuration, L9958_TXD_MESSAGE_CFG_REG ); 
   
}
   
//=============================================================================
// L9958_Clear_Device
//=============================================================================
void L9958_Clear_Device(
   IO_Configuration_T in_configuration)
{
   L9958_Index_T index = L9958_Get_Device_Index( in_configuration );

   L9958_Txd[ index ] = 0;
 
}

