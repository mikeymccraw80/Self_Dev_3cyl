#ifndef DD_L9958_INIT_H
#define DD_L9958_INIT_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_l9958_init.h %
//
// created_by:       hz23l2
//
// date_created:     Mon Apr 02 10:53:50 2006
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

#define L9958_DEVICES_0 (0)
#define L9958_DEVICES_1 (1)
#define L9958_DEVICES_2 (2)
#define L9958_DEVICES_3 (3)

#define L9958_CFG_REG_DEFAULT_CONFIGURATION \
     (            L9958_Set_Diag_Reset_Disable( 0, L9958_DIAG_RST_DISABLE_FLASE ) | \
               L9958_Set_Regulation_Curr_Level( 0, L9958_CURRENT_LEVEL_8P6      ) | \
                L9958_Set_Voltage_Slew_Control( 0, L9958_VSR_LO                 ) | \
                L9958_Set_Current_Slew_Control( 0, L9958_ISR_LO                 ) | \
        L9958_Set_Current_Slew_Control_Disable( 0, L9958_ISR_DISABLE_FALSE      ) | \
              L9958_Set_Open_Load_in_ON_Enable( 0, L9958_OPEN_LOAD_ON_ENABLE   ) )

#ifndef L9958_CONFIGURATION_REG_INIT_0
#define L9958_CONFIGURATION_REG_INIT_0 \
     (        L9958_Set_Device_Index(0 , L9958_INDEX_0 ) | \
              L9958_CFG_REG_DEFAULT_CONFIGURATION      )
#endif

#ifndef L9958_CONFIGURATION_REG_INIT_1
#define L9958_CONFIGURATION_REG_INIT_1 \
     (        L9958_Set_Device_Index(0 , L9958_INDEX_1 ) | \
              L9958_CFG_REG_DEFAULT_CONFIGURATION      )
#endif


#ifndef L9958_CONFIGURATION_REG_INIT_2
#define L9958_CONFIGURATION_REG_INIT_2 \
     (        L9958_Set_Device_Index(0 , L9958_INDEX_2 ) | \
              L9958_CFG_REG_DEFAULT_CONFIGURATION      )
#endif


#ifndef L9958_CONFIGURATION_REG_INIT_3
#define L9958_CONFIGURATION_REG_INIT_3 \
     (        L9958_Set_Device_Index(0 , L9958_INDEX_3 ) | \
              L9958_CFG_REG_DEFAULT_CONFIGURATION      )
#endif


#endif // DD_L9958_INIT_H
