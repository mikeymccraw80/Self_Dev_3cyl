#ifndef DD_VSEP_INIT_H
#define DD_VSEP_INIT_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_init.h~2:incl:mt20u2#2 %
//
// created_by:       fz3pdz
//
// date_created:     Tue Mar 22 12:35:05 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Mon Aug 27 17:03:08 2007 %
//
// %version:         2 %
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

#define VSEP_DEVICES_0 (0)
#define VSEP_DEVICES_1 (1)

#define VSEP_MIN_OFF_TIME_FOR_TEST    (200)
#define VSEP_FAULT_FILTER_TIME_7_5US  (  8)  //this value rounded to 8 to avoid scaling
#define VSEP_FAULT_FILTER_TIME_15US   ( 15)  
#define VSEP_FAULT_FILTER_TIME_34US   ( 34)  
#define VSEP_FAULT_FILTER_TIME_46US   ( 46)

///////////////////////////////////////////////////////////////////////////////
// VSEP Slew Init Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_SLEW_INIT_DEFAULT \
   (  VSEP_Set_Slew_Group_1( 0, VSEP_SLEW_GROUP_1_4_750UA   ) |\
      VSEP_Set_Slew_Group_2( 0, VSEP_SLEW_GROUP_2_3_100UA   ) |\
      VSEP_Set_Slew_Group_3( 0, VSEP_SLEW_GROUP_2_3_100UA   ) |\
      VSEP_Set_Slew_Group_4( 0, VSEP_SLEW_GROUP_1_4_750UA   ) |\
      VSEP_Set_Slew_Group_5( 0, VSEP_SLEW_GROUP_5_300UA     ) |\
    VSEP_Set_Slew_Group_CAN( 0, VSEP_SLEW_GROUP_CAN_500KBPS ) )

#ifndef VSEP_0_SLEW_INIT
#define VSEP_0_SLEW_INIT VSEP_SLEW_INIT_DEFAULT
#endif

#ifndef VSEP_1_SLEW_INIT
#define VSEP_1_SLEW_INIT VSEP_SLEW_INIT_DEFAULT
#endif
   
///////////////////////////////////////////////////////////////////////////////
// VSEP Fault Init Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_FAULT_INIT_DEFAULT \
   (  VSEP_Set_Fault_Level_1( 0, VSEP_FAULT_LEVEL_1_125MV       ) |\
      VSEP_Set_Fault_Level_2( 0, VSEP_FAULT_LEVEL_2_3_6_7_125MV ) |\
      VSEP_Set_Fault_Level_3( 0, VSEP_FAULT_LEVEL_2_3_6_7_125MV ) |\
      VSEP_Set_Fault_Level_4( 0, VSEP_FAULT_LEVEL_4_5_125MV     ) |\
      VSEP_Set_Fault_Level_5( 0, VSEP_FAULT_LEVEL_4_5_125MV     ) |\
      VSEP_Set_Fault_Level_6( 0, VSEP_FAULT_LEVEL_2_3_6_7_125MV ) |\
      VSEP_Set_Fault_Level_7( 0, VSEP_FAULT_LEVEL_2_3_6_7_125MV ) )

#ifndef VSEP_0_FAULT_INIT
#define VSEP_0_FAULT_INIT VSEP_FAULT_INIT_DEFAULT
#endif

#ifndef VSEP_1_FAULT_INIT
#define VSEP_1_FAULT_INIT VSEP_FAULT_INIT_DEFAULT
#endif

///////////////////////////////////////////////////////////////////////////////
// VSEP Fault Filter Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_FAULT_FILTER_INIT \
      (    VSEP_FAULT_FILTER_Set_1TO8SP_Time( 0, VSEP_FAULT_FILTER_7_5US ) |\
          VSEP_FAULT_FILTER_Set_1TO8NSP_Time( 0, VSEP_FAULT_FILTER_7_5US ) |\
            VSEP_FAULT_FILTER_Set_9TO12_Time( 0, VSEP_FAULT_FILTER_7_5US ) |\
           VSEP_FAULT_FILTER_Set_13TO16_Time( 0, VSEP_FAULT_FILTER_7_5US ) |\
           VSEP_FAULT_FILTER_Set_17TO18_Time( 0, VSEP_FAULT_FILTER_7_5US ) |\
           VSEP_FAULT_FILTER_Set_19TO20_Time( 0, VSEP_FAULT_FILTER_7_5US ) |\
           VSEP_FAULT_FILTER_Set_21TO24_Time( 0, VSEP_FAULT_FILTER_7_5US ) |\
           VSEP_FAULT_FILTER_Set_25TO30_Time( 0, VSEP_FAULT_FILTER_7_5US ) )

#ifndef VSEP_0_FAULT_FILTER_INIT
#define VSEP_0_FAULT_FILTER_INIT VSEP_FAULT_FILTER_INIT
#endif
   
#ifndef VSEP_1_FAULT_FILTER_INIT
#define VSEP_1_FAULT_FILTER_INIT VSEP_FAULT_FILTER_INIT
#endif

///////////////////////////////////////////////////////////////////////////////
// VSEP LEDMODE Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_LEDMODE_INIT_DEFAULT( index, channel ) \
      (        VSEP_Set_Device_Index( 0, index                ) |\
                    VSEP_Set_Channel( 0, channel              ) |\
             VSEP_LEDMODE_Set_Enable( 0, VSEP_LEDMODE_DISABLE ) )

#ifndef VSEP_0_LEDMODE_25_INIT
#define VSEP_0_LEDMODE_25_INIT VSEP_LEDMODE_INIT_DEFAULT( VSEP_INDEX_0, VSEP_CHANNEL_LEDMODE_25 )
#endif

#ifndef VSEP_0_LEDMODE_26_INIT
#define VSEP_0_LEDMODE_26_INIT VSEP_LEDMODE_INIT_DEFAULT( VSEP_INDEX_0, VSEP_CHANNEL_LEDMODE_26 )
#endif

#ifndef VSEP_0_LEDMODE_30_INIT
#define VSEP_0_LEDMODE_30_INIT VSEP_LEDMODE_INIT_DEFAULT( VSEP_INDEX_0, VSEP_CHANNEL_LEDMODE_30 )
#endif

#ifndef VSEP_1_LEDMODE_25_INIT
#define VSEP_1_LEDMODE_25_INIT VSEP_LEDMODE_INIT_DEFAULT( VSEP_INDEX_1, VSEP_CHANNEL_LEDMODE_25 )
#endif

#ifndef VSEP_1_LEDMODE_26_INIT
#define VSEP_1_LEDMODE_26_INIT VSEP_LEDMODE_INIT_DEFAULT( VSEP_INDEX_1, VSEP_CHANNEL_LEDMODE_26 )
#endif

#ifndef VSEP_1_LEDMODE_30_INIT
#define VSEP_1_LEDMODE_30_INIT VSEP_LEDMODE_INIT_DEFAULT( VSEP_INDEX_1, VSEP_CHANNEL_LEDMODE_30 )
#endif

///////////////////////////////////////////////////////////////////////////////
// EST Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_EST_SELECT_DEFAULT_SETUP\
   (          VSEP_EST_Select_Set_Drive_Mode( 0, VSEP_EST_SELECT_DRIVE_MODE_EST ) |\
             VSEP_EST_Select_Set_Select_Mode( 0, VSEP_EST_SELECT_SELECT_MODE_EXTERNAL_IO )|\
        VSEP_EST_Select_Set_Paired_Fire_Mode( 0, VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED ) |\
    VSEP_EST_Select_Set_Increment_Index_Mode( 0, VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER ) |\
        VSEP_EST_Select_Set_Index_Pin_Select( 0, VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN ) )

#ifndef VSEP_0_EST_SELECT_SETUP_INIT
#define VSEP_0_EST_SELECT_SETUP_INIT (VSEP_EST_SELECT_DEFAULT_SETUP)
#endif

#ifndef VSEP_1_EST_SELECT_SETUP_INIT
#define VSEP_1_EST_SELECT_SETUP_INIT (VSEP_EST_SELECT_DEFAULT_SETUP)
#endif

///////////////////////////////////////////////////////////////////////////////
// DEPS Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_DEPS_DEFAULT_AT ( 0 )
#define VSEP_DEPS_DEFAULT_DELAY (0)

#define VSEP_DEPS_Default_Init( index, channel ) \
                         ( VSEP_Set_Device_Index( 0, index                   ) | \
                                VSEP_Set_Channel( 0, channel                 ) |\
                     VSEP_DEPS_Set_Initial_Delay( 0, VSEP_DEPS_DEFAULT_DELAY ) )

#ifndef VSEP_0_DEPS_INIT
#define VSEP_0_DEPS_INIT (VSEP_DEPS_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_DEPS ) )
#endif

#ifndef VSEP_1_DEPS_INIT
#define VSEP_1_DEPS_INIT (VSEP_DEPS_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_DEPS ) )
#endif

///////////////////////////////////////////////////////////////////////////////
// VR Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_VR_DEFAULT_AT (VSEP_VR_ADAPTIVE_THRESHOLD_50)
#define VSEP_VR_DEFAULT_MT (VSEP_VR_MIN_THRESHOLD_250MVPP)
#define VSEP_VR_DEFAULT_DELAY (0)

#define VSEP_VR_Default_Init(index, channel)\
               ( VSEP_Set_Device_Index( 0, index                 ) | \
                      VSEP_Set_Channel( 0, channel               ) |\
             VSEP_VR_Set_Initial_Delay( 0, VSEP_VR_DEFAULT_DELAY ) |\
             VSEP_VR_Set_Min_Threshold( 0, VSEP_VR_DEFAULT_MT    ) |\
        VSEP_VR_Set_Adaptive_Threshold( 0, VSEP_VR_DEFAULT_AT    ) )


#ifndef VSEP_0_VR_1_INIT
#define VSEP_0_VR_1_INIT (VSEP_VR_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_VR1))
#endif

#ifndef VSEP_0_VR_2_INIT
#define VSEP_0_VR_2_INIT (VSEP_VR_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_VR2))
#endif

#ifndef VSEP_1_VR_1_INIT
#define VSEP_1_VR_1_INIT (VSEP_VR_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_VR1))
#endif

#ifndef VSEP_1_VR_2_INIT
#define VSEP_1_VR_2_INIT (VSEP_VR_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_VR2))
#endif

///////////////////////////////////////////////////////////////////////////////
// PWM Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_PWMx_Default_Init( index, channel ) \
                          ( VSEP_Set_Device_Index( 0, index             ) | \
                                 VSEP_Set_Channel( 0, channel           ) )


#ifndef VSEP_0_PWM_1_INIT
#define VSEP_0_PWM_1_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_15_PWM_1_FLT_LVL_3 ) )
#endif

#ifndef VSEP_0_PWM_1_PWM_INIT
//#define VSEP_0_PWM_1_PWM_INIT (0)
#endif

#ifndef VSEP_0_PWM_2_INIT
#define VSEP_0_PWM_2_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_16_PWM_2_FLT_LVL_3 ) )
#endif

#ifndef VSEP_0_PWM_2_PWM_INIT
//#define VSEP_0_PWM_2_PWM_INIT (0)
#endif

#ifndef VSEP_0_PWM_3_INIT
#define VSEP_0_PWM_3_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_21_PWM_3_FLT_LVL_6 ) )
#endif

#ifndef VSEP_0_PWM_3_PWM_INIT
//#define VSEP_0_PWM_3_PWM_INIT (0)
#endif

#ifndef VSEP_0_PWM_4_INIT
#define VSEP_0_PWM_4_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_22_PWM_4_FLT_LVL_6 ) )
#endif

#ifndef VSEP_0_PWM_4_PWM_INIT
//#define VSEP_0_PWM_4_PWM_INIT (0)
#endif

#ifndef VSEP_0_PWM_5_INIT
#define VSEP_0_PWM_5_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_24_PWM_5_FLT_LVL_6 ) )
#endif

#ifndef VSEP_0_PWM_5_PWM_INIT
//#define VSEP_0_PWM_5_PWM_INIT (0)
#endif

#ifndef VSEP_0_PWM_6_INIT
#define VSEP_0_PWM_6_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_27_PWM_6_FLT_LVL_7 ) )
#endif

#ifndef VSEP_0_PWM_6_PWM_INIT
//#define VSEP_0_PWM_6_PWM_INIT (0)
#endif

#ifndef VSEP_0_PWM_7_INIT
#define VSEP_0_PWM_7_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_28_PWM_7_FLT_LVL_7 ) )
#endif

#ifndef VSEP_0_PWM_7_PWM_INIT
//#define VSEP_0_PWM_7_PWM_INIT (0)
#endif

#ifndef VSEP_0_PWM_8_INIT
#define VSEP_0_PWM_8_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_0, VSEP_CHANNEL_PCH_29_PWM_8_FLT_LVL_7 ) )
#endif

#ifndef VSEP_0_PWM_8_PWM_INIT
//#define VSEP_0_PWM_8_PWM_INIT (0)
#endif



#ifndef VSEP_1_PWM_1_INIT
#define VSEP_1_PWM_1_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_15_PWM_1_FLT_LVL_3 ) )
#endif

#ifndef VSEP_1_PWM_1_PWM_INIT
#define VSEP_1_PWM_1_PWM_INIT (0)
#endif

#ifndef VSEP_1_PWM_2_INIT
#define VSEP_1_PWM_2_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_16_PWM_2_FLT_LVL_3 ) )
#endif

#ifndef VSEP_1_PWM_2_PWM_INIT
#define VSEP_1_PWM_2_PWM_INIT (0)
#endif

#ifndef VSEP_1_PWM_3_INIT
#define VSEP_1_PWM_3_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_21_PWM_3_FLT_LVL_6 ) )
#endif

#ifndef VSEP_1_PWM_3_PWM_INIT
#define VSEP_1_PWM_3_PWM_INIT (0)
#endif

#ifndef VSEP_1_PWM_4_INIT
#define VSEP_1_PWM_4_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_22_PWM_4_FLT_LVL_6 ) )
#endif

#ifndef VSEP_1_PWM_4_PWM_INIT
#define VSEP_1_PWM_4_PWM_INIT (0)
#endif

#ifndef VSEP_1_PWM_5_INIT
#define VSEP_1_PWM_5_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_24_PWM_5_FLT_LVL_6 ) )
#endif

#ifndef VSEP_1_PWM_5_PWM_INIT
#define VSEP_1_PWM_5_PWM_INIT (0)
#endif

#ifndef VSEP_1_PWM_6_INIT
#define VSEP_1_PWM_6_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_27_PWM_6_FLT_LVL_7 ) )
#endif

#ifndef VSEP_1_PWM_6_PWM_INIT
#define VSEP_1_PWM_6_PWM_INIT (0)
#endif

#ifndef VSEP_1_PWM_7_INIT
#define VSEP_1_PWM_7_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_28_PWM_7_FLT_LVL_7 ) )
#endif

#ifndef VSEP_1_PWM_7_PWM_INIT
#define VSEP_1_PWM_7_PWM_INIT (0)
#endif

#ifndef VSEP_1_PWM_8_INIT
#define VSEP_1_PWM_8_INIT (VSEP_PWMx_Default_Init(VSEP_INDEX_1, VSEP_CHANNEL_PCH_29_PWM_8_FLT_LVL_7 ) )
#endif

#ifndef VSEP_1_PWM_8_PWM_INIT
#define VSEP_1_PWM_8_PWM_INIT (0)
#endif

///////////////////////////////////////////////////////////////////////////////
// PCH Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
#define VSEP_PCHx_Default_Init( index, channel )\
     (        VSEP_Set_Device_Index( 0, index          ) | \
              VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH ) |\
         VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE    ) |\
                   VSEP_Set_Channel( 0, channel        ) )

#ifndef VSEP_0_PCH4_INIT
#define VSEP_0_PCH4_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_04_FLT_LVL_1_2 )
#endif

#ifndef VSEP_0_PCH5_INIT
#define VSEP_0_PCH5_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_05_FLT_LVL_1_2 )
#endif

#ifndef VSEP_0_PCH6_INIT
#define VSEP_0_PCH6_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_06_FLT_LVL_1_2 )
#endif

#ifndef VSEP_0_PCH7_INIT
#define VSEP_0_PCH7_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_07_FLT_LVL_1_2 )
#endif

#ifndef VSEP_0_PCH8_INIT
#define VSEP_0_PCH8_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_08_FLT_LVL_1_2 )
#endif

#ifndef VSEP_0_PCH13_INIT
#define VSEP_0_PCH13_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_13_FLT_LVL_3 )
#endif

#ifndef VSEP_0_PCH14_INIT
#define VSEP_0_PCH14_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_14_FLT_LVL_3 )
#endif

#ifndef VSEP_0_PCH17_INIT
#define VSEP_0_PCH17_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_17_FLT_LVL_4 )
#endif

#ifndef VSEP_0_PCH18_INIT
#define VSEP_0_PCH18_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_18_FLT_LVL_4 )
#endif

#ifndef VSEP_0_PCH19_INIT
#define VSEP_0_PCH19_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_19_FLT_LVL_5 )
#endif

#ifndef VSEP_0_PCH20_INIT
#define VSEP_0_PCH20_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_20_FLT_LVL_5 )
#endif

#ifndef VSEP_0_PCH23_INIT
#define VSEP_0_PCH23_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_23_FLT_LVL_6 )
#endif

#ifndef VSEP_0_PCH25_INIT
#define VSEP_0_PCH25_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_25_FLT_LVL_7 )
#endif

#ifndef VSEP_0_PCH26_INIT
#define VSEP_0_PCH26_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_26_FLT_LVL_7 )
#endif

#ifndef VSEP_0_PCH30_INIT
#define VSEP_0_PCH30_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_0, VSEP_CHANNEL_PCH_30_FLT_LVL_7 )
#endif

#ifndef VSEP_1_PCH4_INIT
#define VSEP_1_PCH4_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_04_FLT_LVL_1_2 )
#endif

#ifndef VSEP_1_PCH5_INIT
#define VSEP_1_PCH5_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_05_FLT_LVL_1_2 )
#endif

#ifndef VSEP_1_PCH6_INIT
#define VSEP_1_PCH6_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_06_FLT_LVL_1_2 )
#endif

#ifndef VSEP_1_PCH7_INIT
#define VSEP_1_PCH7_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_07_FLT_LVL_1_2 )
#endif

#ifndef VSEP_1_PCH8_INIT
#define VSEP_1_PCH8_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_08_FLT_LVL_1_2 )
#endif

#ifndef VSEP_1_PCH13_INIT
#define VSEP_1_PCH13_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_13_FLT_LVL_3 )
#endif

#ifndef VSEP_1_PCH14_INIT
#define VSEP_1_PCH14_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_14_FLT_LVL_3 )
#endif

#ifndef VSEP_1_PCH17_INIT
#define VSEP_1_PCH17_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_17_FLT_LVL_4 )
#endif

#ifndef VSEP_1_PCH18_INIT
#define VSEP_1_PCH18_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_18_FLT_LVL_4 )
#endif

#ifndef VSEP_1_PCH19_INIT
#define VSEP_1_PCH19_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_19_FLT_LVL_5 )
#endif

#ifndef VSEP_1_PCH20_INIT
#define VSEP_1_PCH20_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_20_FLT_LVL_5 )
#endif

#ifndef VSEP_1_PCH23_INIT
#define VSEP_1_PCH23_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_23_FLT_LVL_6 )
#endif

#ifndef VSEP_1_PCH25_INIT
#define VSEP_1_PCH25_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_25_FLT_LVL_7 )
#endif

#ifndef VSEP_1_PCH26_INIT
#define VSEP_1_PCH26_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_26_FLT_LVL_7 )
#endif

#ifndef VSEP_1_PCH30_INIT
#define VSEP_1_PCH30_INIT VSEP_PCHx_Default_Init( VSEP_INDEX_1, VSEP_CHANNEL_PCH_30_FLT_LVL_7 )
#endif

#define VSEP_Msg_PCH_Get_Initial_State( x )\
   ( ( VSEP_PCH_Get_Polarity(x) == IO_ACTIVE_HIGH ) ?\
   ( ( VSEP_PCH_Get_Initial_State(x) == IO_ACTIVE ) ? 1 : 0 ) :\
   ( ( VSEP_PCH_Get_Initial_State(x) == IO_ACTIVE ) ? 0 : 1 ) )

///////////////////////////////////////////////////////////////////////////////
// MPIO Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////

#define VSEP_MPIO_Default_Init( channel )\
   (         VSEP_Set_Channel( 0, channel                            ) |\
     VSEP_MPIO_Set_Input_Mode( 0, VSEP_MPIO_INPUT_MODE_DISCRETE_INPUT ) )

#ifndef VSEP_0_MPIO_M1_INIT
#define VSEP_0_MPIO_M1_INIT ( VSEP_MPIO_Default_Init( VSEP_CHANNEL_MPIO_1 ) )
#endif

#ifndef VSEP_0_MPIO_M2_INIT
#define VSEP_0_MPIO_M2_INIT ( VSEP_MPIO_Default_Init( VSEP_CHANNEL_MPIO_2 ) )
#endif

#ifndef VSEP_0_MPIO_M3_INIT
#define VSEP_0_MPIO_M3_INIT ( VSEP_MPIO_Default_Init( VSEP_CHANNEL_MPIO_3 ) )
#endif

#ifndef VSEP_1_MPIO_M1_INIT
#define VSEP_1_MPIO_M1_INIT ( VSEP_MPIO_Default_Init( VSEP_CHANNEL_MPIO_1 ) )
#endif

#ifndef VSEP_1_MPIO_M2_INIT
#define VSEP_1_MPIO_M2_INIT ( VSEP_MPIO_Default_Init( VSEP_CHANNEL_MPIO_2 ) )
#endif

#ifndef VSEP_1_MPIO_M3_INIT
#define VSEP_1_MPIO_M3_INIT ( VSEP_MPIO_Default_Init( VSEP_CHANNEL_MPIO_3 ) )
#endif

#define VSEP_SOHRSTEN_DEFAULT_INIT \
                   ( VSEP_SOH_Set_SOHRSTEN(0, VSEP_SOH_NORMAL_MODE ) )

#ifndef VSEP_0_SOHRSTEN_INIT
#define VSEP_0_SOHRSTEN_INIT (VSEP_SOHRSTEN_DEFAULT_INIT)
#endif

//////////////////////////////////////////////////////////////////////////////
// Gradient Check Default Initial Value Setup
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define VSEP_GRADIENT_CHECK_DEFAULT\
   ( VSEP_Gradient_Check_Set_Filter_Time( 0, VSEP_GRADIENT_CHECK_FILTER_TIME_464US ) |\
      VSEP_Gradient_Check_Set_Threshold( 0, VSEP_GRADIENT_CHECK_THRESHOLD_160MV ) )

#ifndef VSEP_0_GRADIENT_CHECK_INIT
#define VSEP_0_GRADIENT_CHECK_INIT (VSEP_GRADIENT_CHECK_DEFAULT)
#endif

#ifndef VSEP_1_GRADIENT_CHECK_INIT
#define VSEP_1_GRADIENT_CHECK_INIT (VSEP_GRADIENT_CHECK_DEFAULT)
#endif

FAR_COS void  VSEP_INIT_TXD_Buffer_Initialize(void);

#endif // DD_VSEP_INIT_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/
