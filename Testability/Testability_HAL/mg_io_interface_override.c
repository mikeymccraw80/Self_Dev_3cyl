//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_io_interface_override.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:               %
//
// %version:         8 %
//
//=============================================================================

#include "io_type.h"
// #include "io_scale.h"
// #include "dd_vsep_init.h"
#include "mg_hal_config.h"
#include "io_config_siu.h"
// #include "io_interrupt.h"

// #include "dd_mcd5402_interface.h"
// #include "dd_tpu_discrete_interface.h"
// #include "dd_tpu_interrupt_interface.h"


//=============================================================================
// SIU
//=============================================================================
// #include "dd_siu.h"
// #include "dd_siu_general_purpose_io_interface.h"
// #include "dd_siu_dspi_general_purpose_io_interface.h"
// #include "dd_siu_interrupt_interface.h"
// #include "dd_siu_init_macros.h"

// #include "mg_io_interface_override.h"
// #include "dd_mcd5403_interface.h"
// #include "dd_vsep.h"
// #include "dd_vsep_interface.h"
// #include "dd_vsep_fault_interface.h"
// #include "dd_mios_discrete_interface.h"
// #include "dd_mios_interrupt_interface.h"
// #include "com_sci_port_driver.h"
// #include "dd_vsep_fault.h"
// #include "dd_vsep_pwm_interface.h"
#if 0
#define MG_MTSA_CONFIG_D_OUT_EST1 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_131                 ) )

#define MG_MTSA_CONFIG_D_OUT_ESTSYNC \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_132                 ) )

#endif

#if 0
#define MG_MTSA_CONFIG_D_OUT_INJ1 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_135                 ) )

#define MG_MTSA_CONFIG_D_OUT_INJ2 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_134                 ) )

#define MG_MTSA_CONFIG_D_OUT_INJ3 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_133                 ) )

#define MG_MTSA_CONFIG_D_OUT_INJ4 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_136                 ) )
#endif 
#if 0
#define MG_MTSA_CONFIG_D_OUT_INJ1 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_121                 ) )

#define MG_MTSA_CONFIG_D_OUT_INJ2 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_122                 ) )

#define MG_MTSA_CONFIG_D_OUT_INJ3 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_123                 ) )

#define MG_MTSA_CONFIG_D_OUT_INJ4 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_124                 ) )

#define MG_SIU_GPIO_OUT \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
            SIU_GPIO_Set_Ignore_Init( 0, false                                ) )

#define MG_SIU_GPIO_IN \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_IN                   ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
            SIU_GPIO_Set_Ignore_Init( 0, false                                ) )

#define MG_SIU_VSEP_PWM \
             ( SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_PRIMARY_0) | \
                       SIU_GPIO_Set_Ignore_Init( 0, false                         ) )

// ETPUA0
#define MG_MTSA_CONFIG_IC_58XPOS \
                            ( TPU_Set_Index( 0,TPU_INDEX_0                   ) |\
                    TPU_CHANNEL_Set_Channel( 0,TPU_CHANNEL_0                ) |\
                  TPU_CHANNEL_Set_Primitive( 0,PWMIE_FUNCTION_NUM            ) |\
		TPU_CHANNEL_Set_TCR_Time_Base( 0, TPU_TCR1_TIME_BASE          ) | \
                   TPU_CHANNEL_Set_Polarity( 0,IO_ACTIVE_HIGH                ) |\
           TPU_CHANNEL_Set_Channel_Priority( 0,TPU_CHANNEL_PRIORITY_LOW      ) )

//#define TPU_A_CHANNEL_00_INIT_SDM_SIZE   PWMIE_SPRAM_FRAME_SIZE

// ETPUA1
#define MG_MTSA_CONFIG_IC_CAM1 \
                            ( TPU_Set_Index( 0,TPU_INDEX_0                   ) |\
                    TPU_CHANNEL_Set_Channel( 0,TPU_CHANNEL_1                ) |\
                  TPU_CHANNEL_Set_Primitive( 0,PWMIE_FUNCTION_NUM            ) |\
		TPU_CHANNEL_Set_TCR_Time_Base( 0, TPU_TCR1_TIME_BASE          ) | \
                   TPU_CHANNEL_Set_Polarity( 0,IO_ACTIVE_HIGH                ) |\
           TPU_CHANNEL_Set_Channel_Priority( 0,TPU_CHANNEL_PRIORITY_LOW      ) )

//#define TPU_A_CHANNEL_01_INIT_SDM_SIZE   PWMIE_SPRAM_FRAME_SIZE
                             
// ETPUA16
#define MG_MTSA_CONFIG_IC_CAM2 \
                            ( TPU_Set_Index( 0,TPU_INDEX_0                   ) |\
                    TPU_CHANNEL_Set_Channel( 0,TPU_CHANNEL_16                ) |\
                  TPU_CHANNEL_Set_Primitive( 0,PWMIE_FUNCTION_NUM            ) |\
		TPU_CHANNEL_Set_TCR_Time_Base( 0, TPU_TCR1_TIME_BASE          ) | \
                   TPU_CHANNEL_Set_Polarity( 0,IO_ACTIVE_HIGH                ) |\
           TPU_CHANNEL_Set_Channel_Priority( 0,TPU_CHANNEL_PRIORITY_LOW      ) )

//#define TPU_A_CHANNEL_16_INIT_SDM_SIZE   PWMIE_SPRAM_FRAME_SIZE

// ETPUA27
#define MG_MTSA_CONFIG_IC_VSS \
                            ( TPU_Set_Index( 0,TPU_INDEX_0                   ) |\
                    TPU_CHANNEL_Set_Channel( 0,TPU_CHANNEL_27                ) |\
                  TPU_CHANNEL_Set_Primitive( 0,PWMIE_FUNCTION_NUM            ) |\
		TPU_CHANNEL_Set_TCR_Time_Base( 0, TPU_TCR1_TIME_BASE          ) | \
                   TPU_CHANNEL_Set_Polarity( 0,IO_ACTIVE_HIGH                ) |\
           TPU_CHANNEL_Set_Channel_Priority( 0,TPU_CHANNEL_PRIORITY_LOW      ) )

// ETPUA29
#define MG_MTSA_CONFIG_IC_ENS \
                            ( TPU_Set_Index( 0,TPU_INDEX_0                   ) |\
                    TPU_CHANNEL_Set_Channel( 0,TPU_CHANNEL_29                ) |\
                  TPU_CHANNEL_Set_Primitive( 0,PWMIE_FUNCTION_NUM            ) |\
		TPU_CHANNEL_Set_TCR_Time_Base( 0, TPU_TCR1_TIME_BASE          ) | \
                   TPU_CHANNEL_Set_Polarity( 0,IO_ACTIVE_HIGH                ) |\
           TPU_CHANNEL_Set_Channel_Priority( 0,TPU_CHANNEL_PRIORITY_LOW      ) )

#define MG_MTSA_CONFIG_PWM_FUEL_CONSUM \
                             ( TPU_Set_Index( 0, TPU_INDEX_0                 ) | \
                     TPU_CHANNEL_Set_Channel( 0, TPU_CHANNEL_5               ) | \
                   TPU_CHANNEL_Set_Primitive( 0, PWMOE_FUNCTION_NUM          ) | \
               TPU_CHANNEL_Set_TCR_Time_Base( 0, TPU_TCR1_TIME_BASE          ) | \
                        TPU_CHANNEL_Set_Edge( 0, IO_EDGE_FALLING             ) | \
                    TPU_CHANNEL_Set_Polarity( 0, IO_ACTIVE_HIGH              ) | \
     TPU_CHANNEL_Set_Transfer_Request_Enable( 0, TPU_TRANSFER_REQUEST_ENABLE ) | \
            TPU_CHANNEL_Set_Channel_Priority( 0, TPU_CHANNEL_PRIORITY_LOW    ) )

#define MG_MTSA_CONFIG_D_OUT_FPO1 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_138                 ) )

#define MG_MTSA_CONFIG_D_OUT_FPO2 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_137                 ) )

#define MG_MTSA_CONFIG_D_OUT_FPO3 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_129                 ) )

#define MG_MTSA_CONFIG_D_OUT_FPO4 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_128                 ) )

#define MG_MTSA_CONFIG_D_OUT_FPO5 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_126                 ) )

#define MG_MTSA_CONFIG_D_OUT_FPO6 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_124                 ) )

#define MG_MTSA_CONFIG_D_OUT_FPO7 \
             ( SIU_GPIO_Set_Polarity( 0, IO_ACTIVE_HIGH                       ) | \
   SIU_GPIO_Set_Initial_Output_State( 0, IO_INACTIVE                          ) | \
         SIU_GPIO_Set_Pin_Assignment( 0, SIU_GPIO_PIN_ASSIGNMENT_GPIO         ) | \
         SIU_GPIO_Set_Data_Direction( 0, SIU_GPIO_BUFFER_OUT                  ) | \
         SIU_GPIO_Set_Drive_Strength( 0, SIU_GPIO_DRIVE_STRENGTH_10pF         ) | \
             SIU_GPIO_Set_Open_Drain( 0, SIU_GPIO_OPEN_DRAIN_DISABLED         ) | \
       SIU_GPIO_Set_Input_Hysteresis( 0, SIU_GPIO_INPUT_HYSTERESIS_DISABLED   ) | \
              SIU_GPIO_Set_Slew_Rate( 0, SIU_GPIO_SLEW_RATE_MINIMUM           ) | \
    SIU_GPIO_Set_Pull_Up_Down_Enable( 0, SIU_GPIO_PULL_UP_DISABLED            ) | \
                SIU_GPIO_Set_Pull_Up( 0, SIU_GPIO_PULL_DOWN                   ) | \
                SIU_GPIO_Set_Channel( 0, SIU_GPIO_CHANNEL_123                 ) )

           
const Pulse_Width_Modulation_T MG_MIOS_PWM =
{
   {
      MIOS_PULSE_Initialize_Channel,
      MIOS_PULSE_Clear_Channel,
      MIOS_PULSE_Enable_Channel,
      MIOS_PULSE_Disable_Channel,
      MIOS_PULSE_Get_Channel_Status,
      MIOS_PULSE_Get_Event_Occured
   },
   {
      MIOS_TIMER_Set_Value,
      MIOS_TIMER_Set_Value,
      MIOS_TIMER_Get_Value,
      MIOS_TIMER_Get_Value,
      MIOS_TIMER_Get_State,
      MIOS_TIMER_Get_Base_Frequency,
      MIOS_TIMER_Get_Size,
   },
   {
      MIOS_PWM_Set_Period_And_Duty_Cycle,
      MIOS_PWM_Set_Period_And_Duty_Cycle_Immediate,
      MIOS_PWM_Get_Period,
      MIOS_PWM_Get_Period,
      MIOS_PWM_Get_Duty_Cycle,
      MIOS_PWM_Get_Duty_Cycle
   }
};

//=======================================================================================
// MIOS_CHANNEL_0
//=======================================================================================


//=======================================================================================
// MIOS_CHANNEL_8
//=======================================================================================
const IO_Pulse_Width_Modulation_T MG_MTSA_PWM_ETCCTLPWM =
{
   MTSA_CONFIG_PWM_ETCCTLPWM,
   &MIOS_DISCRETE,
   &MIOS_INTERRUPT,
   &MG_MIOS_PWM
};

//=======================================================================================
// MIOS_CHANNEL_9
//=======================================================================================
const IO_Pulse_Width_Modulation_T MG_MTSA_PWM_FP_IN =
{
   0,//MTSA_CONFIG_PWM_FP_IN,
   &MIOS_DISCRETE,
   &MIOS_INTERRUPT,
   &MG_MIOS_PWM
};

//=======================================================================================
//  MIOS_CHANNEL_10
//=======================================================================================
const IO_Pulse_Width_Modulation_With_Fault_T MG_MTSA_PWM_CCP =
{
   MTSA_CONFIG_VSEP_PCH_16,
   &VSEP_PWM_DISCRETE_INTERFACE,
   NULL,
   &VSEP_PULSE_WIDTH_MODULATION,
   &VSEP_Fault_Log[VSEP_Get_Device_Index(MTSA_CONFIG_VSEP_PCH_16)][VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_16)],
   &VSEP_FAULT_INTERFACE
};

// eMIOS_10 being used to measure 32KHz external clock, as part of SOH strategy

//=======================================================================================
// MTSA_PWM_GENLTERM - MIOS_CHANNEL_12
//=======================================================================================
const IO_Pulse_Width_Modulation_With_Fault_T MG_MTSA_PWM_EGR =
{
   MTSA_CONFIG_VSEP_PCH_18,
   &MIOS_DISCRETE,
   &MIOS_INTERRUPT,
   &MG_MIOS_PWM,
   &VSEP_Fault_Log[VSEP_Get_Device_Index(MTSA_CONFIG_VSEP_PCH_18)][VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_18)],
   &VSEP_FAULT_INTERFACE 
};

//=======================================================================================
// MIOS_CHANNEL_14
//=======================================================================================
const IO_Pulse_Width_Modulation_With_Fault_T MG_MTSA_PWM_VVT1 =
{
   MTSA_CONFIG_PWM_VVT1,
   &MIOS_DISCRETE,
   &MIOS_INTERRUPT,
   &MG_MIOS_PWM,
   &VSEP_Fault_Log[VSEP_Get_Device_Index(MTSA_CONFIG_PWM_VVT1)][VSEP_Get_Channel(MTSA_CONFIG_PWM_VVT1)],
   &VSEP_FAULT_INTERFACE
};

//=======================================================================================
// MTSA_PWM_VVT2 - MIOS_CHANNEL_15
//=======================================================================================
const IO_Pulse_Width_Modulation_With_Fault_T MG_MTSA_PWM_VVT2 =
{
   MTSA_CONFIG_PWM_VVT2,
   &MIOS_DISCRETE,
   &MIOS_INTERRUPT,
   &MG_MIOS_PWM,
   &VSEP_Fault_Log[VSEP_Get_Device_Index(MTSA_CONFIG_PWM_VVT2)][VSEP_Get_Channel(MTSA_CONFIG_PWM_VVT2)],
   &VSEP_FAULT_INTERFACE
};

//=======================================================================================
// MTSA_PWM_GENERATOR_CTRL - MIOS_CHANNEL_23
//=======================================================================================

/*
const IO_Pulse_Width_Modulation_With_Fault_T MG_MTSA_PWM_GENERATOR_CTRL=
{
   MTSA_CONFIG_PWM_GENERATOR_CTRL,
   &MIOS_DISCRETE,
   &MIOS_INTERRUPT,
   &MG_MIOS_PWM,
   &VSEP_Fault_Log[VSEP_Get_Device_Index(MTSA_CONFIG_PWM_GENERATOR_CTRL)][VSEP_Get_Channel(MTSA_CONFIG_PWM_GENERATOR_CTRL)],
   &VSEP_FAULT_INTERFACE
};
*/

//=======================================================================================
// Fuel Consum
//=======================================================================================
const IO_Pulse_Width_Modulation_With_Fault_T MG_MTSA_PWM_FUEL_CONSUM =
{
   MG_MTSA_CONFIG_PWM_FUEL_CONSUM,
   &MCD5403_DISCRETE_OUTPUT,
   NULL,
   &MCD5403_PULSE_WIDTH_MODULATION_OUTPUT,
   NULL,
   NULL
};

// EST object
const IO_Discrete_T MG_MTSA_D_OUT_EST1 =
{
   MG_MTSA_CONFIG_D_OUT_EST1,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// EST SYNC object
const IO_Discrete_T MG_MTSA_D_OUT_ESTSYNC =
{
   MG_MTSA_CONFIG_D_OUT_ESTSYNC,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// Injector 1 objects
const IO_Discrete_T MG_MTSA_D_OUT_INJ1 =
{
   MG_MTSA_CONFIG_D_OUT_INJ1,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// Injector 2 objects
const IO_Discrete_T MG_MTSA_D_OUT_INJ2 =
{
   MG_MTSA_CONFIG_D_OUT_INJ2,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// Injector 3 objects
const IO_Discrete_T MG_MTSA_D_OUT_INJ3 =
{
   MG_MTSA_CONFIG_D_OUT_INJ3,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// Injector 4 objects
const IO_Discrete_T MG_MTSA_D_OUT_INJ4 =
{
   MG_MTSA_CONFIG_D_OUT_INJ4,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// FPO 01 objects
const IO_Discrete_T MG_MTSA_D_OUT_FPO1 =
{
   MG_MTSA_CONFIG_D_OUT_FPO1,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// FPO 02 objects
const IO_Discrete_T MG_MTSA_D_OUT_FPO2 =
{
   MG_MTSA_CONFIG_D_OUT_FPO2,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// FPO 03 objects
const IO_Discrete_T MG_MTSA_D_OUT_FPO3 =
{
   MG_MTSA_CONFIG_D_OUT_FPO3,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// FPO 04 objects
const IO_Discrete_T MG_MTSA_D_OUT_FPO4 =
{
   MG_MTSA_CONFIG_D_OUT_FPO4,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// FPO 05 objects
const IO_Discrete_T MG_MTSA_D_OUT_FPO5 =
{
   MG_MTSA_CONFIG_D_OUT_FPO5,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// FPO 06 objects
const IO_Discrete_T MG_MTSA_D_OUT_FPO6 =
{
   MG_MTSA_CONFIG_D_OUT_FPO6,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// FPO 07 objects
const IO_Discrete_T MG_MTSA_D_OUT_FPO7 =
{
   MG_MTSA_CONFIG_D_OUT_FPO7,
   &SIU_GPIO_DISCRETE,
   &SIU_GPIO_INTERRUPT
};

// SIU PCR register  initialization group for pwm
const SIU_PCR_T MG_PWM_SIU_INITIAL_PCR =
{
   SIU_PCR_Initialize_PA(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_OBE(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_IBE(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_DSC(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_ODE(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_HYS(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_SRC(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_WPE(MG_SIU_VSEP_PWM),
   SIU_PCR_Initialize_WPS(MG_SIU_VSEP_PWM)
};


// SIU GPDO register intialization group for gpio out
// const SIU_GPDO_T  MG_DO_SIU_INITIAL_GPDO =
// {
//    SIU_PCR_Initialize_GPDO(DO_SIU_INITIAL_PCR)
// };

// SIU GPDO register intialization group for gpio in
const SIU_GPDO_T  MG_DI_SIU_INITIAL_GPDO =
{
   SIU_PCR_Initialize_GPDO(MG_SIU_GPIO_IN)
};

// SIU PCR register initialization group for gpio out
const SIU_PCR_T MG_DO_SIU_INITIAL_PCR =
{
   SIU_PCR_Initialize_PA(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_OBE(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_IBE(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_DSC(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_ODE(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_HYS(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_SRC(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_WPE(MG_SIU_GPIO_OUT),
   SIU_PCR_Initialize_WPS(MG_SIU_GPIO_OUT)
};

const SIU_PCR_T MG_DI_SIU_INITIAL_PCR =
{
   SIU_PCR_Initialize_PA(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_OBE(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_IBE(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_DSC(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_ODE(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_HYS(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_SRC(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_WPE(MG_SIU_GPIO_IN),
   SIU_PCR_Initialize_WPS(MG_SIU_GPIO_IN)
};

IO_Pulse_History_T MG_MTSA_IC_Pulse_History_58XPOS;
PWM_Frequency_T    MG_MTSA_IC_Data_58XPOS;
const IO_Input_Capture_T MG_MTSA_IC_58XPOS =
{
   MG_MTSA_CONFIG_IC_58XPOS,
   &TPU_DISCRETE,
   &TPU_INTERRUPT,
   &MCD5402_INPUT_CAPTURE,
   NULL,
   &MG_MTSA_IC_Pulse_History_58XPOS,
   true
};

IO_Pulse_History_T MG_MTSA_IC_Pulse_History_CAM1;
PWM_Frequency_T    MG_MTSA_IC_Data_CAM1;
const IO_Input_Capture_T MG_MTSA_IC_CAM1 =
{
   MG_MTSA_CONFIG_IC_CAM1,
   &TPU_DISCRETE,
   &TPU_INTERRUPT,
   &MCD5402_INPUT_CAPTURE,
   NULL,
   &MG_MTSA_IC_Pulse_History_CAM1,
   true
};

IO_Pulse_History_T MG_MTSA_IC_Pulse_History_CAM2;
PWM_Frequency_T    MG_MTSA_IC_Data_CAM2;
const IO_Input_Capture_T MG_MTSA_IC_CAM2 =
{
   MG_MTSA_CONFIG_IC_CAM2,
   &TPU_DISCRETE,
   &TPU_INTERRUPT,
   &MCD5402_INPUT_CAPTURE,
   NULL,
   &MG_MTSA_IC_Pulse_History_CAM2,
   true
};

IO_Pulse_History_T MG_MTSA_IC_Pulse_History_VSS;
PWM_Frequency_T    MG_MTSA_IC_Data_VSS;
const IO_Input_Capture_T MG_MTSA_IC_VSS =
{
   MG_MTSA_CONFIG_IC_VSS,
   &TPU_DISCRETE,
   &TPU_INTERRUPT,
   &MCD5402_INPUT_CAPTURE,
   NULL,
   &MG_MTSA_IC_Pulse_History_VSS,
   true
};
IO_Pulse_History_T MG_MTSA_IC_Pulse_History_ENS;
PWM_Frequency_T    MG_MTSA_IC_Data_ENS;
const IO_Input_Capture_T MG_MTSA_IC_ENS =
{
   MG_MTSA_CONFIG_IC_ENS,
   &TPU_DISCRETE,
   &TPU_INTERRUPT,
   &MCD5402_INPUT_CAPTURE,
   NULL,
   &MG_MTSA_IC_Pulse_History_ENS,
   true
};

#endif
/*=============================================================================
 * MG_SIU_GPIO_DISCRETE_Initialize_Device_Override
 * @func  override application SIU initialization
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void MG_SIU_GPIO_DISCRETE_Initialize_Device_Override(void)
{
    // override application's configuration, force est stay gpio mode
    // SIU.GPDO[SIU_GPIO_CHANNEL_131] = DO_SIU_INITIAL_PDO;
    // SIU.GPDO[SIU_GPIO_CHANNEL_132] = DO_SIU_INITIAL_PDO;
    // SIU.PCR[SIU_GPIO_CHANNEL_131]  = DO_SIU_INITIAL_PCR;
    // SIU.PCR[SIU_GPIO_CHANNEL_132]  = DO_SIU_INITIAL_PCR;

    // override application's configuration, force inj stay gpio mode
    SIU.GPDO[SIU_GPIO_CHANNEL_133] = DO_SIU_INITIAL_PDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_134] = DO_SIU_INITIAL_PDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_135] = DO_SIU_INITIAL_PDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_136] = DO_SIU_INITIAL_PDO;
    SIU.PCR[SIU_GPIO_CHANNEL_133]  = DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_134]  = DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_135]  = DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_136]  = DO_SIU_INITIAL_PCR;


#if 0
    // override application's configuration, force FPO stay gpio mod
    SIU.GPDO[SIU_GPIO_CHANNEL_138] = MG_DO_SIU_INITIAL_GPDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_137] = MG_DO_SIU_INITIAL_GPDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_129] = MG_DO_SIU_INITIAL_GPDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_128] = MG_DO_SIU_INITIAL_GPDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_126] = MG_DO_SIU_INITIAL_GPDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_124] = MG_DO_SIU_INITIAL_GPDO;
    SIU.GPDO[SIU_GPIO_CHANNEL_123] = MG_DO_SIU_INITIAL_GPDO;

    SIU.PCR[SIU_GPIO_CHANNEL_138] = MG_DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_137] = MG_DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_129] = MG_DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_128] = MG_DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_126] = MG_DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_124] = MG_DO_SIU_INITIAL_PCR;
    SIU.PCR[SIU_GPIO_CHANNEL_123] = MG_DO_SIU_INITIAL_PCR;
#endif
    // disable RTI, cause it will operate ETC
    // IO_INTERRUPT_Set_Enable( MG_HIODEVICE_RTI, false);
}

void MG_SIU_GPIO_PWM_Initialize_Device_Override(void)
{
    // SIU.PCR[SIU_GPIO_CHANNEL_391] = MG_PWM_SIU_INITIAL_PCR;
}

void MG_Reset_SCI(const CommPort_T * in_port)
{
    IO_Configuration_T  in_configuration = in_port->Configuration;
    SCI_T *sci = SCI_Get_Device_Register( in_configuration );
    sci->CR1.U32 = 0;
    sci->CR2.U16 = 0;
    sci->DR.U16 = 0;
    sci->SR1.U32 = 0xFF10FF03;
    sci->LCR1.U32= 0;
    sci->LTR.U32 = 0;
    sci->LRR.D = 0;
    sci->LPR.U32 = 0;
}

void MG_Init_SCI(const CommPort_T * in_port)
{
    SCIPort_Init_T *sci_init;
    sci_init = (SCIPort_Init_T *)in_port->Init;
    SCI_Configure_Device(in_port->Configuration, sci_init->loopback);
    SCI_Set_Speed(in_port->Configuration, sci_init->speed );
}
