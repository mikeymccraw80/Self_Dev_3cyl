#ifndef IO_CONFIG_SPI_H
#define IO_CONFIG_SPI_H
//=============================================================================
//
//                COPYRIGHT, 2002, DELPHI TECHNOLOGIES, INC.
//
//===========================================================================
// %name:            io_config_spi.h %
//
// created_by:       rskearne
//
// date_created:     Fri Mar 22 08:17:54 2002
//
// %derived_by:      nz45s2 %
//
// %date_modified:   Tue Mar  1 20:20:01 2011 %
//
// %version:         4.1.1 %
//
//===========================================================================
// REUSE:
// None
//=============================================================================
//#include "systpcfg.h"
//=============================================================================
//
//                          I/O Configuration
//
//=============================================================================
#define MTSA_USE_BITS_MACRO



#define CcSYST_NUM_OF_CYLINDERS 4

// DEPS Delay = [(DEPS[5:0] * 8) + 4]
// total 11 bits: DEPS[5:0] and last 5 bits fixed at 01111 (will be done by VSEP)
#define DEPS_Delay_44US (0x05)
// VR Delay = [(VRDLY[6:0] * 8) + 4]
#define VR_Delay_148US (0x12) 

//=============================================================================  
//                 VSEP
//=============================================================================

//=============================================================================
// VSEP Time Constants
//=============================================================================
#define VSEP_EXTERNAL_CLOCK_BASE_FREQUENCY (4000000UL)

#define VSEP_0_VR_1_INIT \
         ( VSEP_VR_Set_Adaptive_Threshold( 0, VSEP_VR_ADAPTIVE_THRESHOLD_30 ) | \
                VSEP_VR_Set_Min_Threshold( 0, VSEP_VR_MIN_THRESHOLD_335MVPP ) | \
                VSEP_VR_Set_Initial_Delay( 0, 0                             ) | \
                         VSEP_Set_Channel( 0, VSEP_CHANNEL_VR1              ) )

#define VSEP_0_VR_2_INIT \
         ( VSEP_VR_Set_Adaptive_Threshold( 0, VSEP_VR_ADAPTIVE_THRESHOLD_30 ) | \
                VSEP_VR_Set_Min_Threshold( 0, VSEP_VR_MIN_THRESHOLD_335MVPP ) | \
                VSEP_VR_Set_Initial_Delay( 0, VR_Delay_148US                ) | \
                         VSEP_Set_Channel( 0, VSEP_CHANNEL_VR2              ) )

#define VSEP_0_DEPS_INIT \
        (  VSEP_DEPS_Set_Initial_Delay( 0, DEPS_Delay_44US  ) )

#define VSEP_0_SLEW_INIT\
        (  VSEP_Set_Slew_Group_1( 0, VSEP_SLEW_GROUP_1_4_1500UA             ) | \
           VSEP_Set_Slew_Group_2( 0, VSEP_SLEW_GROUP_2_3_1300UA              ) | \
           VSEP_Set_Slew_Group_3( 0, VSEP_SLEW_GROUP_2_3_500UA              ) | \
           VSEP_Set_Slew_Group_4( 0, VSEP_SLEW_GROUP_1_4_1500UA             ) | \
           VSEP_Set_Slew_Group_5( 0, VSEP_SLEW_GROUP_5_1100UA                ) | \
         VSEP_Set_Slew_Group_CAN( 0, VSEP_SLEW_GROUP_CAN_500KBPS            ) )


#define VSEP_0_FAULT_INIT \
        (  VSEP_Set_Fault_Level_1( 0, VSEP_FAULT_LEVEL_1_2653MV             ) | \
           VSEP_Set_Fault_Level_2( 0, VSEP_FAULT_LEVEL_2_3_6_7_447MV        ) | \
           VSEP_Set_Fault_Level_3( 0, VSEP_FAULT_LEVEL_2_3_6_7_521MV        ) | \
           VSEP_Set_Fault_Level_4( 0, VSEP_FAULT_LEVEL_4_5_223MV            ) | \
           VSEP_Set_Fault_Level_5( 0, VSEP_FAULT_LEVEL_4_5_1241MV            ) | \
           VSEP_Set_Fault_Level_6( 0, VSEP_FAULT_LEVEL_2_3_6_7_521MV        ) | \
           VSEP_Set_Fault_Level_7( 0, VSEP_FAULT_LEVEL_2_3_6_7_596MV        ) )  



#define VSEP_0_FAULT_FILTER_INIT \
      (    VSEP_FAULT_FILTER_Set_1TO8SP_Time( 0, VSEP_FAULT_FILTER_15US   ) | \
          VSEP_FAULT_FILTER_Set_1TO8NSP_Time( 0, VSEP_FAULT_FILTER_15US   ) | \
            VSEP_FAULT_FILTER_Set_9TO12_Time( 0, VSEP_FAULT_FILTER_15US   ) | \
           VSEP_FAULT_FILTER_Set_13TO16_Time( 0, VSEP_FAULT_FILTER_34US   ) | \
           VSEP_FAULT_FILTER_Set_17TO18_Time( 0, VSEP_FAULT_FILTER_15US   ) | \
           VSEP_FAULT_FILTER_Set_19TO20_Time( 0, VSEP_FAULT_FILTER_15US   ) | \
           VSEP_FAULT_FILTER_Set_21TO24_Time( 0, VSEP_FAULT_FILTER_15US    ) | \
           VSEP_FAULT_FILTER_Set_25TO30_Time( 0, VSEP_FAULT_FILTER_15US   ) )

// 
// VSEP_EST_SELECT_INDEX_PIN_SELECT_ESTX_PIN


#if CcSYST_NUM_OF_CYLINDERS == 3

#define VSEP_0_EST_SELECT_SETUP_INIT\
   (          VSEP_EST_Select_Set_Drive_Mode( 0, VSEP_EST_SELECT_DRIVE_MODE_IGBT               ) |\
             VSEP_EST_Select_Set_Select_Mode( 0, VSEP_EST_SELECT_SELECT_MODE_INTERNAL_DECODER  ) |\
        VSEP_EST_Select_Set_Paired_Fire_Mode( 0, VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED     ) |\
    VSEP_EST_Select_Set_Increment_Index_Mode( 0, VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER ) |\
        VSEP_EST_Select_Set_Index_Pin_Select( 0, VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN     ) |\
          VSEP_EST_Select_Set_Cylinder_Count( 0, VSEP_EST_SELECT_NUMBER_OF_CYLINDERS_3         ) )
#elif CcSYST_NUM_OF_CYLINDERS == 4
#define VSEP_0_EST_SELECT_SETUP_INIT\
  (          VSEP_EST_Select_Set_Drive_Mode( 0, VSEP_EST_SELECT_DRIVE_MODE_IGBT                ) |\
             VSEP_EST_Select_Set_Select_Mode( 0, VSEP_EST_SELECT_SELECT_MODE_INTERNAL_DECODER  ) |\
       VSEP_EST_Select_Set_Paired_Fire_Mode( 0, VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED      ) |\
    VSEP_EST_Select_Set_Increment_Index_Mode( 0, VSEP_EST_SELECT_INCREMENT_INDEX_MODE_ONCE_PER ) |\
        VSEP_EST_Select_Set_Index_Pin_Select( 0, VSEP_EST_SELECT_INDEX_PIN_SELECT_SYNC_PIN     ) |\
		    VSEP_EST_Select_Set_Cylinder_Count( 0, VSEP_EST_SELECT_NUMBER_OF_CYLINDERS_4	   ) )
#endif

#define MTSA_CONFIG_GRADIENT_COUNT \
     (             VSEP_Set_Device_Index( 0, VSEP_INDEX_0                              ) |\
     VSEP_Gradient_Check_Set_Filter_Time( 0, VSEP_GRADIENT_CHECK_FILTER_TIME_592US     ) |\
       VSEP_Gradient_Check_Set_Threshold( 0, VSEP_GRADIENT_CHECK_THRESHOLD_280MV       ) )


#define VSEP_0_GRADIENT_CHECK_INIT MTSA_CONFIG_GRADIENT_COUNT

#define VSEP_0_LEDMODE_25_INIT \
      (        VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ) |\
                    VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_25_FLT_LVL_7 ) |\
             VSEP_LEDMODE_Set_Enable( 0, VSEP_LEDMODE_DISABLE ) )

#define VSEP_0_LEDMODE_26_INIT \
      (        VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ) |\
                    VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_26_FLT_LVL_7 ) |\
             VSEP_LEDMODE_Set_Enable( 0, VSEP_LEDMODE_DISABLE ) )

#define VSEP_0_LEDMODE_30_INIT \
      (        VSEP_Set_Device_Index( 0, VSEP_INDEX_0 ) |\
                    VSEP_Set_Channel( 0, VSEP_CHANNEL_PCH_30_FLT_LVL_7 ) |\
             VSEP_LEDMODE_Set_Enable( 0, VSEP_LEDMODE_DISABLE ) )

#define VSEP_0_SOHRSTEN_INIT \
      (        VSEP_Set_Device_Index( 0, VSEP_INDEX_0 )        |\
               VSEP_SOH_Set_SOHRSTEN( 0, VSEP_SOH_NORMAL_MODE ) )
            
 #ifdef  HW_SOH_DISABLE             
 #define VSEP_0_SOH_ENABLE_INIT \
	 (        VSEP_Set_Device_Index( 0, VSEP_INDEX_0 )        |\
                VSEP_SOH_Set_ENABLE( 0, VSEP_SOH_DISABLE ) )
#else
#define VSEP_0_SOH_ENABLE_INIT \
      (        VSEP_Set_Device_Index( 0, VSEP_INDEX_0 )        |\
	   VSEP_SOH_Set_ENABLE( 0, VSEP_SOH_ENABLE) )
#endif

//=============================================================================
//                 VSEP
//=============================================================================
#define VSEP_0_SPBR  ( SPI_Convert_Baud_To_SPBR( 6250000 ) )
#define VSEP_0_XFER  ( 16 )
#define VSEP_0_DSCKL ( 0 )
#define VSEP_0_DTL   ( 0 )
#define VSEP_0_POL   ( SPI_MESSAGE_CLOCK_POLARITY_ACTIVE_LOW )
#define VSEP_0_PHASE ( SPI_MESSAGE_CLOCK_PHASE_TRAILING_EDGE )


#endif // IO_CONFIG_SPI_H
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 * 4.1.1 mt20u2#800 11/01/02 nz45s2 RSM_CTC_8093_Add Mt22p1 ETC 3cylinder package_Rev0_20110120       *
\*===========================================================================*/
