//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_init.c %
//
// created_by:       hz23l2
//
// date_created:     Mon Apr 02 09:00:46 2007
//
// %derived_by:       wzmkk7 %
//
// %date_modified:    %
//
// %version:         mt20u2#2 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================
//#include "dd_config.h"
#include "dd_l9958_txd.h"
#include "dd_l9958_rxd.h"
#include "dd_l9958.h"
#include "dd_l9958_init.h"

uint16_t L9958_Rxd[ NUMBER_OF_L9958];
uint16_t L9958_Txd[ NUMBER_OF_L9958 ];

const uint16_t  L9958_TXD_INITIAL[ NUMBER_OF_L9958 ]  =
{
   {
       (   L9958_Msg_Set_Diag_Reset_Disable(          0,  L9958_Get_Diag_Reset_Disable( L9958_CONFIGURATION_REG_INIT_0 )          ) | \
           L9958_Msg_Set_Regulation_Curr_Level(       0,  L9958_Get_Regulation_Curr_Level( L9958_CONFIGURATION_REG_INIT_0 )       ) | \
           L9958_Msg_Set_Voltage_Slew_Control(        0,  L9958_Get_Voltage_Slew_Control( L9958_CONFIGURATION_REG_INIT_0 )        ) | \
           L9958_Msg_Set_Voltage_Slew_Control(        0,  L9958_Get_Current_Slew_Control( L9958_CONFIGURATION_REG_INIT_0 )        ) | \
           L9958_Msg_Set_Current_Slew_Control_Disable(0,  L9958_Get_Current_Slew_Control_Disable( L9958_CONFIGURATION_REG_INIT_0) ) | \
           L9958_Msg_Set_Open_Load_in_ON_Enable(      0,  L9958_Get_Open_Load_in_ON_Enable( L9958_CONFIGURATION_REG_INIT_0)       ) )
   }
};
