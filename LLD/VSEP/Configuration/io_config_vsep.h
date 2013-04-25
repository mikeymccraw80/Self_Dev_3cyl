#ifndef IO_CONFIG_DISCRETE_H
#define IO_CONFIG_DISCRETE_H
//=============================================================================
//
//                COPYRIGHT, 2002, DELPHI TECHNOLOGIES, INC.
//
//===========================================================================
// %name:            io_config_vsep.h %
//
// created_by:       rskearne
//
// date_created:     Fri Mar 22 08:17:54 2002
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Thursday, October 18, 2007 3:44:59 PM %
//
// %version:         7 %
//
//===========================================================================
// REUSE:
// None
//=============================================================================


//port0~5 define were deleted
//=============================================================================
// VSEP
//=============================================================================

//=============================================================================
// PCH_01 - ESTA
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_01 \
        ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
                  VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_01_FLT_LVL_1     ) )

#define VSEP_EST_A_CH  MTSA_CONFIG_VSEP_PCH_01
//=============================================================================
// PCH_02 - ESTB
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_02 \
        ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
                  VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_02_FLT_LVL_1     ) )

#define VSEP_EST_B_CH  MTSA_CONFIG_VSEP_PCH_02
//=============================================================================
// PCH_03 - ESTC
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_03 \
        ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     		VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
             VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_03_FLT_LVL_1     ) )

#define VSEP_EST_C_CH MTSA_CONFIG_VSEP_PCH_03

//=============================================================================
// PCH_04 - SDOUT_4 - ESTD
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_04 \
        ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_04_FLT_LVL_1_2     ) )

#define VSEP_0_PCH4_INIT MTSA_CONFIG_VSEP_PCH_04

#define VSEP_EST_D_CH  MTSA_CONFIG_VSEP_PCH_04

//=============================================================================
// PCH_05 - SDOUT_5 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_05 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_ACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_05_FLT_LVL_1_2     ) )

#define VSEP_0_PCH5_INIT MTSA_CONFIG_VSEP_PCH_05

#define VSEP_DO_MPR_CH  MTSA_CONFIG_VSEP_PCH_05

//=============================================================================
// PCH_06 - SDOUT_6 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_06 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_ACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_06_FLT_LVL_1_2     ) )

#define VSEP_0_PCH6_INIT MTSA_CONFIG_VSEP_PCH_06

#define VSEP_DO_FPR_CH  MTSA_CONFIG_VSEP_PCH_06

//=============================================================================
// PCH_07 - SDOUT_7 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_07 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_ACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_07_FLT_LVL_1_2     ) )

#define VSEP_0_PCH7_INIT MTSA_CONFIG_VSEP_PCH_07

#define VSEP_DO_ACCLUTCH_CH  MTSA_CONFIG_VSEP_PCH_07

//=============================================================================
// PCH_08 - SDOUT_8 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_08 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_08_FLT_LVL_1_2     ) )

#define VSEP_0_PCH8_INIT MTSA_CONFIG_VSEP_PCH_08

#define VSEP_DO_FAN2_CH  MTSA_CONFIG_VSEP_PCH_08

//=============================================================================
// PCH_09 - INJ1
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_09 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
               VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_09_FLT_LVL_2       ) )
               
#define VSEP_INJA_CH  MTSA_CONFIG_VSEP_PCH_09
//=============================================================================
// PCH_10 - INJ2
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_10 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
               VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_10_FLT_LVL_2       ) )

#define VSEP_INJB_CH  MTSA_CONFIG_VSEP_PCH_10
//=============================================================================
// PCH_11 - INJ3
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_11 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
               VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_11_FLT_LVL_2       ) )

#define VSEP_INJC_CH  MTSA_CONFIG_VSEP_PCH_11
//=============================================================================
// PCH_12 - INJ4
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_12 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
               VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_12_FLT_LVL_2       ) )

#define VSEP_INJD_CH  MTSA_CONFIG_VSEP_PCH_12

//=============================================================================
// PCH_13 - Mcrop_D_13 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_13 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_13_FLT_LVL_3       ) )

#define VSEP_0_PCH13_INIT MTSA_CONFIG_VSEP_PCH_13

#define VSEP_DO_FUELCON_CH  MTSA_CONFIG_VSEP_PCH_13

//=============================================================================
// PCH_14 - SDOUT_14 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_14 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_14_FLT_LVL_3       ) )

#define VSEP_0_PCH14_INIT MTSA_CONFIG_VSEP_PCH_14

#define VSEP_DO_IMMOREQ_CH  MTSA_CONFIG_VSEP_PCH_14

//=============================================================================
// PCH_15 - PWM_1 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_15 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_15_PWM_1_FLT_LVL_3 ) )

#define VSEP_0_PWM_1_INIT MTSA_CONFIG_VSEP_PCH_15
#define VSEP_0_PWM_1_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0)

#define VSEP_PO_FAN1_CH  MTSA_CONFIG_VSEP_PCH_15
//=============================================================================
// PCH_16 - PWM_2 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_16 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_16_PWM_2_FLT_LVL_3 ) )


#define VSEP_0_PWM_2_INIT MTSA_CONFIG_VSEP_PCH_16
#define VSEP_0_PWM_2_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0 )


#define VSEP_PO_CCP_CH  MTSA_CONFIG_VSEP_PCH_16

//=============================================================================
// PCH_17 - Microp_D_17
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_17 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_17_FLT_LVL_4       ) )

#define VSEP_0_PCH17_INIT MTSA_CONFIG_VSEP_PCH_17
#define VSEP_PO_VVT1_CH  MTSA_CONFIG_VSEP_PCH_17

//=============================================================================
// PCH_18 - Microp_D_18
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_18 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_18_FLT_LVL_4       ) )

#define VSEP_0_PCH18_INIT MTSA_CONFIG_VSEP_PCH_18
#define VSEP_PO_VVT2_CH  MTSA_CONFIG_VSEP_PCH_18

//=============================================================================
// PCH_19 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_19 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_19_FLT_LVL_5       ) )

#define VSEP_0_PCH19_INIT MTSA_CONFIG_VSEP_PCH_19
#define VSEP_DO_VGIS1_CH  MTSA_CONFIG_VSEP_PCH_19

//=============================================================================
// PCH_20
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_20 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_20_FLT_LVL_5       ) )

#define VSEP_0_PCH20_INIT MTSA_CONFIG_VSEP_PCH_20
#define VSEP_DO_VGIS2_CH  MTSA_CONFIG_VSEP_PCH_20

//=============================================================================
// PCH_21 - PWM_3 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_21 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_21_PWM_3_FLT_LVL_6 ) )

#define VSEP_0_PWM_3_INIT MTSA_CONFIG_VSEP_PCH_21
#define VSEP_0_PWM_3_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0 )

#define VSEP_PO_O2AHTR_CH  MTSA_CONFIG_VSEP_PCH_21
//=============================================================================
// PCH_22 - PWM_4
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_22 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_22_PWM_4_FLT_LVL_6 ) )


#define VSEP_0_PWM_4_INIT MTSA_CONFIG_VSEP_PCH_22
#define VSEP_0_PWM_4_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0 )

#define VSEP_PO_O2BHTR_CH  MTSA_CONFIG_VSEP_PCH_22



//=============================================================================
// PCH_23 - SDOUT_23
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_23 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) |\
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) |\
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_23_FLT_LVL_6       ) )

#define VSEP_0_PCH23_INIT MTSA_CONFIG_VSEP_PCH_23

#define VSEP_PO_CLTPUMP_CH  MTSA_CONFIG_VSEP_PCH_23

//=============================================================================
// PCH_24 - PWM_5 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_24 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_24_PWM_5_FLT_LVL_6 ) )


#define VSEP_0_PWM_5_INIT MTSA_CONFIG_VSEP_PCH_24
#define VSEP_0_PWM_5_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0 )

#define VSEP_PO_ALTCTL_CH  MTSA_CONFIG_VSEP_PCH_24

//=============================================================================
// PCH_25 - SDOUT_25 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_25 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) | \
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_25_FLT_LVL_7       ) )

#define VSEP_0_PCH25_INIT MTSA_CONFIG_VSEP_PCH_25
#define VSEP_DO_MIL_CH  MTSA_CONFIG_VSEP_PCH_25

//=============================================================================
// PCH_26 - SDOUT_26
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_26 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) | \
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_26_FLT_LVL_7       ) )

#define VSEP_0_PCH26_INIT MTSA_CONFIG_VSEP_PCH_26
#define VSEP_DO_SVS_CH  MTSA_CONFIG_VSEP_PCH_26

//=============================================================================
// PCH_27 - PWM_6 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_27 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_27_PWM_6_FLT_LVL_7 ) )

#define VSEP_0_PWM_6_INIT   MTSA_CONFIG_VSEP_PCH_27 

#define VSEP_0_PWM_6_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0 )
#define VSEP_PO_CLTGAUGE_CH  MTSA_CONFIG_VSEP_PCH_27
//=============================================================================
// PCH_28 - PWM_7
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_28 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_28_PWM_7_FLT_LVL_7 ) )

#define VSEP_0_PWM_7_INIT  MTSA_CONFIG_VSEP_PCH_28
#define VSEP_0_PWM_7_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0 )
#define VSEP_PO_SMR_CH  MTSA_CONFIG_VSEP_PCH_28
//=============================================================================
// PCH_29 - PWM_8
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_29 \
           ( VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
             VSEP_PWM_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
        VSEP_PWM_Set_Initial_State( 0, IO_INACTIVE                         ) | \
                  VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_29_PWM_8_FLT_LVL_7 ) )

#define VSEP_0_PWM_8_INIT  MTSA_CONFIG_VSEP_PCH_29
#define VSEP_0_PWM_8_PWM_INIT VSEP_PWM_Set_Initial_Frequency_Duty_Cycle( VSEP_PWM_CDIV_32, 400, 0 )
#define VSEP_PO_TACH_CH  MTSA_CONFIG_VSEP_PCH_29
//=============================================================================
// PCH_30 - SDOUT_30 
//=============================================================================
#define MTSA_CONFIG_VSEP_PCH_30 \
     (    VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
          VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
     VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) | \
               VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_30_FLT_LVL_7       ) )

#define VSEP_0_PCH30_INIT MTSA_CONFIG_VSEP_PCH_30
#define VSEP_PO_CRUISI_CH  MTSA_CONFIG_VSEP_PCH_30

//=============================================================================
// MPIO1
//=============================================================================
#define MTSA_CONFIG_VSEP_MPIO1 \
           (      VSEP_Set_Device_Index( 0, VSEP_INDEX_0                                  ) | \
                       VSEP_Set_Channel( 0, VSEP_CHANNEL_MPIO_1                           ) | \
               VSEP_MPIO_Set_Input_Mode( 0, VSEP_MPIO_INPUT_MODE_ACTIVE_LOW_SWITCH_DETECT ) | \
                  VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                                ) | \
             VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                                   ) )

#define VSEP_0_MPIO_M1_INIT MTSA_CONFIG_VSEP_MPIO1
#define VSEP_MPIO_ACRequest_CH  MTSA_CONFIG_VSEP_MPIO1

//=============================================================================
// MPIO2 
//=============================================================================
#define MTSA_CONFIG_VSEP_MPIO2  \
           (         VSEP_Set_Device_Index( 0, VSEP_INDEX_0                                   ) | \
                          VSEP_Set_Channel( 0, VSEP_CHANNEL_MPIO_2                            ) | \
                  VSEP_MPIO_Set_Input_Mode( 0, VSEP_MPIO_INPUT_MODE_ACTIVE_HIGH_SWITCH_DETECT ) | \
                     VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                                 ) | \
                VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                                    ) )


#define VSEP_0_MPIO_M2_INIT MTSA_CONFIG_VSEP_MPIO2
#define VSEP_MPIO_PSPS_CH  MTSA_CONFIG_VSEP_MPIO2

//=============================================================================
// MPIO3
//=============================================================================
#define MTSA_CONFIG_VSEP_MPIO3  \
           (         VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
                          VSEP_Set_Channel( 0, VSEP_CHANNEL_MPIO_3                 ) | \
                  VSEP_MPIO_Set_Input_Mode( 0, VSEP_MPIO_INPUT_MODE_DISCRETE_INPUT ) | \
                     VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) | \
                VSEP_PCH_Set_Initial_State( 0, IO_INACTIVE                         ) )

#define VSEP_0_MPIO_M3_INIT MTSA_CONFIG_VSEP_MPIO3
#define VSEP_MPIO_MIDAC_CH  MTSA_CONFIG_VSEP_MPIO3

//=============================================================================
// SOHRSTEN_STAT 
//=============================================================================
#define MTSA_CONFIG_D_OUT_SOHRSTEN_STAT \
           (         VSEP_Set_Device_Index( 0, VSEP_INDEX_0                        ) | \
                          VSEP_Set_Channel( 0, VSEP_CHANNEL_SOHRSTEN_STAT          ) | \
                     VSEP_PCH_Set_Polarity( 0, IO_ACTIVE_HIGH                      ) )


#endif // IO_CONFIG_DISCRETE_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        yy/mm/dd     By   Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14     WSQ  Created the initial version for MT22p1 based on MT80       *
 *
 * 5.0  272        08/11/24     sjl
 * + Add configurable calibrations for discrete inputs 
 *   - Changed MTSA object name of MPIOs
 *
\*===========================================================================*/
