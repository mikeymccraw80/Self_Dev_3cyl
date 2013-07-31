#ifndef DD_L9958_CONFIG_H
#define DD_L9958_CONFIG_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//=============================================================================

#define L9958_TXD_INITIAL  (L9958_Msg_Set_Diag_Reset_Disable(          0, L9958_DIAG_RST_DISABLE_FALSE) | \
							L9958_Msg_Set_Regulation_Curr_Level(       0, L9958_CURRENT_LEVEL_8P6     ) | \
							L9958_Msg_Set_Voltage_Slew_Control(        0, L9958_VSR_LO                ) | \
							L9958_Msg_Set_Current_Slew_Control(        0, L9958_ISR_LO                ) | \
							L9958_Msg_Set_Current_Slew_Control_Disable(0, L9958_ISR_DISABLE_FALSE     ) | \
							L9958_Msg_Set_Open_Load_in_ON_Enable(      0, L9958_OPEN_LOAD_ON_ENABLE   ) )


#endif // DD_L9958_INIT_H
