//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_init.c~12:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 11:47:56 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Mon Aug 27 14:48:09 2007 %
//
// %version:         12 %
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

#include "io_config_spi.h"
#include "io_config_vsep.h"

#include "dd_vsep.h"
#include "dd_vsep_deps.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_init_config.h"
#include "hwiocald.h"


#ifdef  VSEP_CALIBRATION_ENABLE
uint16_t VSEP_INIT_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_INIT_TXD_MESSAGE_MAX];
#else
const uint16_t VSEP_INIT_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_INIT_TXD_MESSAGE_MAX] =
{
   {
      {
          VSEP_Msg_Set_FLTCLR( 0, true                   ) |
         VSEP_Msg_Set_CRTOCLR( 0, true                   ) |
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED ) | 
            ( 0, VSEP_TXD_SDIA_VR1_CTRL )   
      },
      { 
          VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_1_INIT )      ) |        
             VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_1_INIT ) ) |
             VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Min_Threshold( VSEP_0_VR_1_INIT ) ) 
      },
      { 
          VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_2_INIT )      ) |        
             VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_2_INIT ) ) |
             VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Min_Threshold( VSEP_0_VR_2_INIT ) ) 
      },
      {     
          VSEP_Msg_DEPS_Set_Delay( 0, VSEP_DEPS_Get_Initial_Delay( VSEP_0_DEPS_INIT ) ) 
      },
      { 
          VSEP_Msg_SLEW_Set_Group_1( 0, VSEP_Get_Slew_Group_1( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_2( 0, VSEP_Get_Slew_Group_2( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_3( 0, VSEP_Get_Slew_Group_3( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_4( 0, VSEP_Get_Slew_Group_4( VSEP_0_SLEW_INIT )     ) |
          VSEP_Msg_SLEW_Set_Group_5( 0, VSEP_Get_Slew_Group_5( VSEP_0_SLEW_INIT )     ) |
        VSEP_Msg_SLEW_Set_Group_CAN( 0, VSEP_Get_Slew_Group_CAN( VSEP_0_SLEW_INIT )   )
      },
      {
         VSEP_Msg_FAULT_Set_Level_1( 0, VSEP_Get_Fault_Level_1( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_2( 0, VSEP_Get_Fault_Level_2( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_3( 0, VSEP_Get_Fault_Level_3( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_4( 0, VSEP_Get_Fault_Level_4( VSEP_0_FAULT_INIT ) ) 
        
      },
      {
         VSEP_Msg_FAULT_Set_Level_5( 0, VSEP_Get_Fault_Level_5( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_6( 0, VSEP_Get_Fault_Level_6( VSEP_0_FAULT_INIT ) ) |
         VSEP_Msg_FAULT_Set_Level_7( 0, VSEP_Get_Fault_Level_7( VSEP_0_FAULT_INIT ) ) 
      },
      {
          ( VSEP_Msg_FAULT_Filter_Set_Non_Spark_Channels_1_To_8( 0, VSEP_FAULT_FILTER_Get_1TO8NSP_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                VSEP_Msg_FAULT_Filter_Set_Spark_Channels_1_To_8( 0,  VSEP_FAULT_FILTER_Get_1TO8SP_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                     VSEP_Msg_FAULT_Filter_Set_Channels_9_To_12( 0,   VSEP_FAULT_FILTER_Get_9TO12_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_13_To_16( 0,  VSEP_FAULT_FILTER_Get_13TO16_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_17_To_18( 0,  VSEP_FAULT_FILTER_Get_17TO18_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_19_To_20( 0,  VSEP_FAULT_FILTER_Get_19TO20_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_21_To_24( 0,  VSEP_FAULT_FILTER_Get_21TO24_Time( VSEP_0_FAULT_FILTER_INIT ) ) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_25_To_30( 0,  VSEP_FAULT_FILTER_Get_25TO30_Time( VSEP_0_FAULT_FILTER_INIT ) ) )
      },
      {
          ( VSEP_Msg_LEDMODE_Set_Channel_25( 0, VSEP_LEDMODE_Get_Enable( VSEP_0_LEDMODE_25_INIT ) ) |
            VSEP_Msg_LEDMODE_Set_Channel_26( 0, VSEP_LEDMODE_Get_Enable( VSEP_0_LEDMODE_26_INIT ) ) |
            VSEP_Msg_LEDMODE_Set_Channel_30( 0, VSEP_LEDMODE_Get_Enable( VSEP_0_LEDMODE_30_INIT ) ) )
      },
      { 
          VSEP_Msg_IGBT_Set_GRADFILT( 0,  VSEP_Gradient_Check_Get_Filter_Time(VSEP_0_GRADIENT_CHECK_INIT ) ) |
         VSEP_Msg_IGBT_Set_GRADTHR( 0, VSEP_Gradient_Check_Get_Threshold(VSEP_0_GRADIENT_CHECK_INIT ) ) 
      },
      { 
            VSEP_Msg_EST_Set_EDGE( 0,     VSEP_EST_Select_Get_Index_Pin_Select( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
           VSEP_Msg_EST_Set_INDEX( 0, VSEP_EST_Select_Get_Increment_Index_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     VSEP_EST_Select_Get_Paired_Fire_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) 
      },
      {
                   VSEP_Msg_Set_SOHRSTEN( 0, VSEP_SOH_Get_SOHRSTEN( VSEP_0_SOHRSTEN_INIT )                                              ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_1-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M1_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_2-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M2_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_3-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M3_INIT ) ) |
                 VSEP_Msg_EST_Set_CYLCNT( 0, VSEP_EST_Select_Get_Cylinder_Count( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
              VSEP_Msg_EST_Set_DEC_DISCB( 0,    VSEP_EST_Select_Get_Select_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
                VSEP_Msg_EST_Set_IGBTCFG( 0,     VSEP_EST_Select_Get_Drive_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
		VSEP_Msg_SOH_Set_CRDISARM( 0,     VSEP_SOH_Get_ENABLE_STATE( VSEP_0_SOH_ENABLE_INIT )        )
	}
   }
};
#endif

uint16_t VSEP_LEDMODE_Txd[NUMBER_OF_VSEP][VSEP_LEDMODE_TXD_MESSAGE_MAX];


uint16_t VSEP_EST_Select_Txd[NUMBER_OF_VSEP][VSEP_EST_SELECT_TXD_MESSAGE_MAX];
uint16_t VSEP_EST_Select_Rxd[NUMBER_OF_VSEP][VSEP_EST_SELECT_RXD_MESSAGE_MAX];

#ifdef VSEP_EST_DIAGNOSTIC_DEBUG
uint8_t VSEP_EST_Select_Dwell_Current_Time[NUMBER_OF_VSEP][8];
#endif

#ifdef  VSEP_CALIBRATION_ENABLE
 uint16_t VSEP_EST_SELECT_INITIAL[NUMBER_OF_VSEP][VSEP_EST_SELECT_TXD_MESSAGE_MAX];
#else
const uint16_t VSEP_EST_SELECT_INITIAL[NUMBER_OF_VSEP][VSEP_EST_SELECT_TXD_MESSAGE_MAX] =
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
      {
         VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_EST_STAT  ) |
         VSEP_Msg_Set_SDIA(0,VSEP_TXD_SDIA_EST_CTRL)  
      } ,
      { // Do not set the count for the initial structure.
            VSEP_Msg_EST_Set_EDGE( 0,     VSEP_EST_Select_Get_Index_Pin_Select( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
           VSEP_Msg_EST_Set_INDEX( 0, VSEP_EST_Select_Get_Increment_Index_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     VSEP_EST_Select_Get_Paired_Fire_Mode( VSEP_0_EST_SELECT_SETUP_INIT ) ) 
      }
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,{
      {
         VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_EST_STAT  ) |
         VSEP_Msg_Set_SDIA(0,VSEP_TXD_SDIA_EST_CTRL)  
      },
      { // Do not set the count for the initial structure.
            VSEP_Msg_EST_Set_EDGE( 0,     VSEP_EST_Select_Get_Index_Pin_Select( VSEP_1_EST_SELECT_SETUP_INIT ) ) |
           VSEP_Msg_EST_Set_INDEX( 0, VSEP_EST_Select_Get_Increment_Index_Mode( VSEP_1_EST_SELECT_SETUP_INIT ) ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     VSEP_EST_Select_Get_Paired_Fire_Mode( VSEP_1_EST_SELECT_SETUP_INIT ) ) 
      }
   }
#endif
};
#endif

uint16_t VSEP_DEPS_Txd[NUMBER_OF_VSEP][VSEP_DEPS_TXD_MESSAGE_MAX];
const uint32_t VSEP_TIMER_DEPS_Base_Frequency = 0;

const uint16_t VSEP_DEPS_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_DEPS_TXD_MESSAGE_MAX] =
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_DEPS_CTRL )   
      },
      {     
            VSEP_Msg_DEPS_Set_Delay( 0, VSEP_DEPS_Get_Initial_Delay( VSEP_0_DEPS_INIT ) ) 
      }
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,{
      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_DEPS_CTRL )   
      },
      {     
            VSEP_Msg_DEPS_Set_Delay( 0, VSEP_DEPS_Get_Initial_Delay( VSEP_1_DEPS_INIT ) ) 
      }
   }
#endif
};

// uint16_t VSEP_VR_Txd[NUMBER_OF_VSEP][VSEP_VR_TXD_MESSAGE_MAX];
// uint16_t VSEP_VR_Rxd[NUMBER_OF_VSEP][VSEP_VR_RXD_MESSAGE_MAX];

const uint32_t VSEP_TIMER_VR_Base_Frequency = 0;

const uint16_t VSEP_VR_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_VR_TXD_MESSAGE_MAX] = 
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_VR1_CTRL  )   
      },
      { 
         VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_1_INIT )      ) |
            VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_1_INIT ) ) |
            VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_1_INIT ) )
      },
      { 
         VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_0_VR_2_INIT )      ) |
            VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_2_INIT ) ) |
            VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_0_VR_2_INIT ) ) 
      }
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,{
      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_VR1_CTRL  )   
      },
      { 
         VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_1_VR_1_INIT )      ) |
            VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_1_VR_1_INIT ) ) |
            VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_1_VR_1_INIT ) )
      },
      { 
         VSEP_Msg_VR_Set_Delay( 0, VSEP_VR_Get_Initial_Delay( VSEP_1_VR_2_INIT )      ) |
            VSEP_Msg_VR_Set_AT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_1_VR_2_INIT ) ) |
            VSEP_Msg_VR_Set_MT( 0, VSEP_VR_Get_Adaptive_Threshold( VSEP_1_VR_2_INIT ) ) 
      }
   }
#endif
};

// uint16_t VSEP_PWM_Txd[NUMBER_OF_VSEP][VSEP_PWM_CHANNEL_MAX][VSEP_PWM_TXD_MESSAGE_MAX];
// uint16_t VSEP_PWM_Rxd[NUMBER_OF_VSEP][VSEP_PWM_RXD_MESSAGE_MAX];

const uint32_t VSEP_BASE_FREQUENCY = VSEP_EXTERNAL_CLOCK_BASE_FREQUENCY;

#define VSEP_GRADCOUNT_BASE_FREQUENCY_DEFINE ((VSEP_EXTERNAL_CLOCK_BASE_FREQUENCY + (VSEP_GRADCOUNT_DIVIDER/2)) / VSEP_GRADCOUNT_DIVIDER)

const uint32_t VSEP_GRADCOUNT_BASE_FREQUENCY = VSEP_GRADCOUNT_BASE_FREQUENCY_DEFINE;

#define VSEP_128_US_BASE_FREQUENCY ( 1.0 / 0.000128 )

const uint8_t VSEP_GRADCOUNT_FAULT_WINDOW = (uint8_t)((VSEP_GRADCOUNT_BASE_FREQUENCY_DEFINE + (VSEP_128_US_BASE_FREQUENCY/2))/ VSEP_128_US_BASE_FREQUENCY); //128us in terms of GRADCOUNT ticks

const uint16_t VSEP_PWM_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_PWM_CHANNEL_MAX][VSEP_PWM_TXD_MESSAGE_MAX]=
{
#if (NUMBER_OF_VSEP > VSEP_DEVICES_0)
   {
      { //PWM Channel 1
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_1   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_1_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_1_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_1_PWM_INIT ) )
         } 
      },
      { //PWM Channel 2
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_2   )
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_2_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_2_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_2_PWM_INIT ) )
         }
      },
      { //PWM Channel 3
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_3   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_3_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_3_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_3_PWM_INIT ) )
         }
      },
      { //PWM Channel 4
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_4   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_4_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_4_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_4_PWM_INIT ) )
         }
      },
      { //PWM Channel 5
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_5   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_5_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_5_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_5_PWM_INIT ) )
         }
      },
      { //PWM Channel 6
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_6   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_6_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_6_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_6_PWM_INIT ) )
         }
      },
      { //PWM Channel 7
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_7   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_7_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_7_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_7_PWM_INIT ) )
         }
      },
      { //PWM Channel 8
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_8   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_0_PWM_8_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_0_PWM_8_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_0_PWM_8_PWM_INIT ) )
         }
      }
   }

#endif
#if (NUMBER_OF_VSEP > VSEP_DEVICES_1)
   ,{
      { //PWM Channel 1
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_1   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_1_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_1_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_1_PWM_INIT ) )
         } 
      },
      { //PWM Channel 2
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_2   )
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_2_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_2_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_2_PWM_INIT ) )
         }
      },
      { //PWM Channel 3
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_3   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_3_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_3_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_3_PWM_INIT ) )
         }
      },
      { //PWM Channel 4
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_4   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_4_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_4_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_4_PWM_INIT ) )
         }
      },
      { //PWM Channel 5
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_5   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_5_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_5_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_5_PWM_INIT ) )
         }
      },
      { //PWM Channel 6
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_6   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_6_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_6_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_6_PWM_INIT ) )
         }
      },
      { //PWM Channel 7
         {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_7   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_7_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_7_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_7_PWM_INIT ) )
         }
      },
      { //PWM Channel 8
         {
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_FAULT_GRP_8 ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PWM_ONT_8   )   
         },
         {
            VSEP_Msg_PWM_Set_OnTime( 0, VSEP_PWM_Get_Initial_Duty_Cycle( VSEP_1_PWM_8_PWM_INIT ) )   
         },
         {
             VSEP_Msg_PWM_Set_Period( 0, VSEP_PWM_Get_Initial_Period( VSEP_1_PWM_8_PWM_INIT         ) ) |
            VSEP_Msg_PWM_Set_Divider( 0, VSEP_PWM_Get_Base_Frequency_Divider( VSEP_1_PWM_8_PWM_INIT ) )
         }
      }
   }

#endif
};

uint16_t VSEP_PCH_Txd[NUMBER_OF_VSEP][VSEP_PCH_TXD_MESSAGE_MAX];
uint16_t VSEP_PCH_Rxd[NUMBER_OF_VSEP][VSEP_PCH_RXD_MESSAGE_MAX];

const uint16_t VSEP_PCH_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_PCH_TXD_MESSAGE_MAX] = 
{  
#if NUMBER_OF_VSEP > VSEP_DEVICES_0
   {
      {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_EST_STAT ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PCH      )   
            
      },
      {
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_4,  VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH4_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_5 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH5_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_6 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH6_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_7 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH7_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_8 , VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH8_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_13, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH13_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_14, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH14_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_17, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH17_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_18, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH18_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_19, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH19_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_20, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH20_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_23, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH23_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_25, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH25_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_26, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH26_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_30, VSEP_Msg_PCH_Get_Initial_State( VSEP_0_PCH30_INIT ) ) ) 
      }
   }
#endif
#if NUMBER_OF_VSEP > VSEP_DEVICES_1
   ,{
      {      
            VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_Mx_INPUT ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_PCH      )   
      },
      {
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_4,  VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH4_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_5 , VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH5_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_6 , VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH6_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_7 , VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH7_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_8 , VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH8_INIT  ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_13, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH13_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_14, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH14_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_17, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH17_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_18, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH18_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_19, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH19_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_20, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH20_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_23, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH23_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_25, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH25_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_26, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH26_INIT ) ) ) |
          ( VSEP_Msg_PCHx_Set_State( 0, VSEP_PCH_CHANNEL_OUT_30, VSEP_Msg_PCH_Get_Initial_State( VSEP_1_PCH30_INIT ) ) ) 
      }
   }
#endif
};

// State of Health data
// uint16_t VSEP_SOH_Txd[NUMBER_OF_VSEP][VSEP_SOH_TXD_MESSAGE_MAX];
// uint16_t VSEP_SOH_Rxd[NUMBER_OF_VSEP][VSEP_SOH_RXD_MESSAGE_MAX];
// uint16_t VSEP_SOH_Status_Rxd[ NUMBER_OF_VSEP ][VSEP_SOH_STATUS_RXD_MESSAGE_MAX];
const uint16_t VSEP_SOH_STATUS_TXD[ NUMBER_OF_VSEP ][VSEP_SOH_STATUS_TXD_MESSAGE_MAX] =
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
     {  
         VSEP_Msg_Set_FLTCLR( 0, 0 ) |
        VSEP_Msg_Set_CRTOCLR( 0, 0 ) |
           VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_EST_STAT ) |
           VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_NOT_USED )     
     },
     { 0                                                 }
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,
   {
     {  
         VSEP_Msg_Set_FLTCLR( 0, 0 ) |
        VSEP_Msg_Set_CRTOCLR( 0, 0 ) |
           VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_EST_STAT ) |
           VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_NOT_USED )     
     },
     { 0                                                 }
   }
#endif
};

// IGBT GRAD Fault data
const uint16_t VSEP_EST_FAULT_GRAD_INITIAL[NUMBER_OF_VSEP][VSEP_EST_FAULT_TXD_MESSAGE_MAX]=
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
     {  
         VSEP_Msg_Set_FLTCLR( 0, false ) |
        VSEP_Msg_Set_CRTOCLR( 0, false ) |
           VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_GRADCOUNT ) |
           VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_GRAD_CTRL )     
     },
     {    VSEP_Msg_IGBT_Set_GRADTHR( 0,   VSEP_Gradient_Check_Get_Threshold(VSEP_0_GRADIENT_CHECK_INIT ) ) |
         VSEP_Msg_IGBT_Set_GRADFILT( 0, VSEP_Gradient_Check_Get_Filter_Time(VSEP_0_GRADIENT_CHECK_INIT ) )
     }  // GRADIENT Threshold and Time
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,
   {
     {  
         VSEP_Msg_Set_FLTCLR( 0, false ) |
        VSEP_Msg_Set_CRTOCLR( 0, false ) |
           VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_GRADCOUNT ) |
           VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_GRAD_CTRL )     
     },
     {    VSEP_Msg_IGBT_Set_GRADTHR( 0,   VSEP_Gradient_Check_Get_Threshold(VSEP_1_GRADIENT_CHECK_INIT ) ) |
         VSEP_Msg_IGBT_Set_GRADFILT( 0, VSEP_Gradient_Check_Get_Filter_Time(VSEP_1_GRADIENT_CHECK_INIT ) )
     }  // GRADIENT Threshold and Time
   }
#endif
};

//for MT22.1 special spark and fault diagnostic logic.
const uint8_t VSEP_EST_FAULT_SYNC_MESSAGE_BYTE_INITIAL[NUMBER_OF_VSEP][VSEP_EST_FAULT_SYNC_TXD_MESSAGE_MAX_BYTE]=
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
     {  
         VSEP_Msg_Set_FLTCLR_BYTE_FORMAT( 0, true )  |
        VSEP_Msg_Set_CRTOCLR_BYTE_FORMAT( 0, false ) |
           VSEP_Msg_Set_SDOA_BYTE_FORMAT(0, VSEP_RXD_SDOA_FAULT_GRP_5 ) },
     {  VSEP_Msg_Set_SDIA_BYTE_FORMAT(0, VSEP_TXD_SDIA_EST_CTRL )},
     { 0                                                 } // SDOA 5 byte 1
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,
  {
     {  
         VSEP_Msg_Set_FLTCLR_BYTE_FORMAT( 0, true )  |
        VSEP_Msg_Set_CRTOCLR_BYTE_FORMAT( 0, false ) |
           VSEP_Msg_Set_SDOA_BYTE_FORMAT(0, VSEP_RXD_SDOA_FAULT_GRP_5 ) },
     { VSEP_Msg_Set_SDIA_BYTE_FORMAT(0, VSEP_TXD_SDIA_EST_CTRL ) },
     { 0                                                   } 
   }
#endif
};
//Fault data	for MT22.1, start at VSEP_RXD_SDOA_FAULT_GRP_6 
const uint16_t VSEP_FAULT_TXD[NUMBER_OF_VSEP][VSEP_FAULT_TXD_MESSAGE_MAX]=
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
     {  
         VSEP_Msg_Set_FLTCLR( 0, true )  |
        VSEP_Msg_Set_CRTOCLR( 0, false ) |
           VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_FAULT_GRP_6 ) |
           VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_NOT_USED )     
     },
     { 0                                                 }, // SDOA 6 word 1
     { 0                                                 }, // SDOA 8 word 2
     { 0                                                 }, // SDOA A word 3
     { 0                                                 } // SDOA C word 4
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,
   {
     {  
         VSEP_Msg_Set_FLTCLR( 0, true )  |
        VSEP_Msg_Set_CRTOCLR( 0, false ) |
           VSEP_Msg_Set_SDOA(0, VSEP_RXD_SDOA_FAULT_GRP_6 ) |
           VSEP_Msg_Set_SDIA(0, VSEP_TXD_SDIA_NOT_USED )     
     },
     { 0                                                 }, // SDOA 6 word 1
     { 0                                                 }, // SDOA 8 word 2
     { 0                                                 }, // SDOA A word 3
     { 0                                                 }  // SDOA C word 4
   }
#endif
};

uint16_t VSEP_Fault_Rxd[NUMBER_OF_VSEP][VSEP_FAULT_RXD_MESSAGE_MAX];

Fault_Log_T VSEP_Fault_Log[NUMBER_OF_VSEP][VSEP_CHANNEL_MAX];

#ifdef  VSEP_CALIBRATION_ENABLE
void  VSEP_INIT_TXD_Buffer_Initialize(void)
{
	uint8_t               channel;
	VSEP_FAULT_FILTER_T   filter_type = VSEP_FAULT_FILTER_MAX;
	uint32_t              filter_time;

	VSEP_INIT_TXD_INITIAL[0][0] = VSEP_Msg_Set_FLTCLR( 0, true                   ) |
								VSEP_Msg_Set_CRTOCLR( 0, true                   ) |
								VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED ) | 
								VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_VR1_CTRL );

	VSEP_INIT_TXD_INITIAL[0][1] = 
							VSEP_Msg_VR_Set_Delay( 0, (uint16_t)KsVSEP_VR1_Setting_Initial.KeVSEP_VR1_DLY) |        
							VSEP_Msg_VR_Set_AT( 0, (uint16_t)KsVSEP_VR1_Setting_Initial.KbVSEP_VR1_PERC50) |
							VSEP_Msg_VR_Set_MT( 0, (uint16_t)KsVSEP_VR1_Setting_Initial.KeVSEP_VR1_MT);

	VSEP_INIT_TXD_INITIAL[0][2] =     
          VSEP_Msg_VR_Set_Delay( 0, (uint16_t)KsVSEP_VR2_Setting_Initial.KeVSEP_VR2_DLY) |        
             VSEP_Msg_VR_Set_AT( 0, (uint16_t)KsVSEP_VR2_Setting_Initial.KbVSEP_VR2_PERC50) |
             VSEP_Msg_VR_Set_MT( 0, (uint16_t)KsVSEP_VR2_Setting_Initial.KeVSEP_VR2_MT) 
      ;
	VSEP_INIT_TXD_INITIAL[0][3] =          
          VSEP_Msg_DEPS_Set_Delay( 0, (uint16_t)KsVSEP_DEPSDLY_Setting_Initial.KeVSEP_DEPSDLY) 
      ;
	VSEP_INIT_TXD_INITIAL[0][4] =       
          VSEP_Msg_SLEW_Set_Group_1( 0, (uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW1) |
          VSEP_Msg_SLEW_Set_Group_2( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW2) |
          VSEP_Msg_SLEW_Set_Group_3( 0, (uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW3) |
          VSEP_Msg_SLEW_Set_Group_4( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW4) |
          VSEP_Msg_SLEW_Set_Group_5( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW5) |
        VSEP_Msg_SLEW_Set_Group_CAN( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEWCAN)
      ;
 	VSEP_INIT_TXD_INITIAL[0][5] =     
         VSEP_Msg_FAULT_Set_Level_1( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL1) |
         VSEP_Msg_FAULT_Set_Level_2( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL2) |
         VSEP_Msg_FAULT_Set_Level_3( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL3) |
         VSEP_Msg_FAULT_Set_Level_4( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL4) 
        
      ;
	VSEP_INIT_TXD_INITIAL[0][6] =      
         VSEP_Msg_FAULT_Set_Level_5( 0, (uint16_t)KsVSEP_Fault_Level_Initial2.KeVSEP_FLTLVL5) |
         VSEP_Msg_FAULT_Set_Level_6( 0,(uint16_t)KsVSEP_Fault_Level_Initial2.KeVSEP_FLTLVL6) |
         VSEP_Msg_FAULT_Set_Level_7( 0, (uint16_t)KsVSEP_Fault_Level_Initial2.KeVSEP_FLTLVL7) 
      ;
  	VSEP_INIT_TXD_INITIAL[0][7] =    
          ( VSEP_Msg_FAULT_Filter_Set_Non_Spark_Channels_1_To_8( 0, (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_1TO8NS) |
                VSEP_Msg_FAULT_Filter_Set_Spark_Channels_1_To_8( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_1TO8SP) |
                     VSEP_Msg_FAULT_Filter_Set_Channels_9_To_12( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_9TO12) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_13_To_16( 0, (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_13TO16) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_17_To_18( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_17TO18) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_19_To_20( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_19TO20) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_21_To_24( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_21TO24) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_25_To_30( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_25TO30))
      ;
	VSEP_INIT_TXD_INITIAL[0][8] =      
          ( VSEP_Msg_LEDMODE_Set_Channel_25( 0, (uint16_t)KsVSEP_LEDMODE_Initial.KbVSEP_LEDMODE_25) |
            VSEP_Msg_LEDMODE_Set_Channel_26( 0, (uint16_t)KsVSEP_LEDMODE_Initial.KbVSEP_LEDMODE_26) |
            VSEP_Msg_LEDMODE_Set_Channel_30( 0, (uint16_t)KsVSEP_LEDMODE_Initial.KbVSEP_LEDMODE_30) )
      ;
  	VSEP_INIT_TXD_INITIAL[0][9] =     
          VSEP_Msg_IGBT_Set_GRADFILT( 0, (uint16_t)KsVSEP_GRAD_Initialization.KbVSEP_GRADFILT) |
         VSEP_Msg_IGBT_Set_GRADTHR( 0,  (uint16_t)KsVSEP_GRAD_Initialization.KbVSEP_GRADTHR) 
      ;
  	VSEP_INIT_TXD_INITIAL[0][10] =     
            VSEP_Msg_EST_Set_EDGE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_EDGE   ) |
           VSEP_Msg_EST_Set_INDEX( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_INDEX   ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KeVSEP_Spark_PFMODE   ) 
      ;
   	VSEP_INIT_TXD_INITIAL[0][11] =  
         VSEP_Msg_Set_SOHRSTEN( 0, VSEP_SOH_Get_SOHRSTEN( VSEP_0_SOHRSTEN_INIT )                                              ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_1-VSEP_CHANNEL_MPIO_1), (uint16_t)KeHWIO_ACReq_pin79_Status) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_2-VSEP_CHANNEL_MPIO_1), (uint16_t)KeHWIO_PSPS_pin60_Status) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_3-VSEP_CHANNEL_MPIO_1), (uint16_t)KeHWIO_MIDAC_pin40_Status) |
                 VSEP_Msg_EST_Set_CYLCNT( 0, (uint16_t)KsVSEP_Spark_Mode_Initialization.KeVSEP_Spark_CYLCNT   ) |
              VSEP_Msg_EST_Set_DEC_DISCB( 0,    (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_DEC_DISCB ) |
                VSEP_Msg_EST_Set_IGBTCFG( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_IGBTCFG      ) |
		VSEP_Msg_SOH_Set_CRDISARM( 0,     VSEP_SOH_Get_ENABLE_STATE( VSEP_0_SOH_ENABLE_INIT )        )
	;
	
  VSEP_EST_SELECT_INITIAL[0][0] =      
         VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_EST_STAT  ) |
         VSEP_Msg_Set_SDIA(0,VSEP_TXD_SDIA_EST_CTRL)  
       ;
    VSEP_EST_SELECT_INITIAL[0][1] =      
           VSEP_Msg_EST_Set_EDGE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_EDGE   ) |
          VSEP_Msg_EST_Set_INDEX( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_INDEX   ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KeVSEP_Spark_PFMODE   ) 
     ;

	
		
for(channel=0;channel<30;channel++){
	if( channel >= VSEP_CHANNEL_PCH_01_FLT_LVL_1 )
   {
      if( channel <= VSEP_CHANNEL_PCH_08_FLT_LVL_1_2 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_1TO8NS;
      }
      else if (channel <= VSEP_CHANNEL_PCH_12_FLT_LVL_2)
      {
         filter_type =KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_9TO12;
      }
      else if (channel <= VSEP_CHANNEL_PCH_16_PWM_2_FLT_LVL_3 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_13TO16;
      }
      else if (channel <= VSEP_CHANNEL_PCH_18_FLT_LVL_4 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_17TO18;
      }
      else if (channel <= VSEP_CHANNEL_PCH_20_FLT_LVL_5 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_19TO20;
      }
      else if (channel <= VSEP_CHANNEL_PCH_24_PWM_5_FLT_LVL_6 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_21TO24;
      }
      else if (channel <= VSEP_CHANNEL_PCH_30_FLT_LVL_7 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_25TO30;
      }
      else
      {
         //  Not a valid value for channel
      }
   }

   switch (filter_type)
   {
      case VSEP_FAULT_FILTER_7_5US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_7_5US;
         break;
      }
      case VSEP_FAULT_FILTER_15US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_15US;
         break;
      }
      case VSEP_FAULT_FILTER_34US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_34US;
         break;
      }
      case VSEP_FAULT_FILTER_46US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_46US;
         break;
      }
      default:
      {
         filter_time = 0;
         break;
      }
   }
   Filter_Time_Array[channel] = filter_time;
}
}
#endif


const uint16_t VSEP_MPIO_MODE_TXD_INITIAL[NUMBER_OF_VSEP][VSEP_MPIO_MODE_TXD_MESSAGE_MAX] =
{
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_0 )
   {
      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_SETUP )   
      },
      {     
                   VSEP_Msg_Set_SOHRSTEN( 0, VSEP_SOH_Get_SOHRSTEN( VSEP_0_SOHRSTEN_INIT )                                              ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_1-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M1_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_2-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M2_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_3-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_0_MPIO_M3_INIT ) ) |
                 VSEP_Msg_EST_Set_CYLCNT( 0, VSEP_EST_Select_Get_Cylinder_Count( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
              VSEP_Msg_EST_Set_DEC_DISCB( 0,    VSEP_EST_Select_Get_Select_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) |
                VSEP_Msg_EST_Set_IGBTCFG( 0,     VSEP_EST_Select_Get_Drive_Mode( VSEP_0_EST_SELECT_SETUP_INIT )                         ) 
      }
   }
#endif
#if ( NUMBER_OF_VSEP > VSEP_DEVICES_1 )
   ,
   {
      {     VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED  ) |
            VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_SETUP )   
      },
      {
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_1-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_1_MPIO_M1_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_2-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_1_MPIO_M2_INIT ) ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_3-VSEP_CHANNEL_MPIO_1), VSEP_MPIO_Get_Input_Mode( VSEP_1_MPIO_M3_INIT ) ) |
                 VSEP_Msg_EST_Set_CYLCNT( 0, VSEP_EST_Select_Get_Cylinder_Count( VSEP_1_EST_SELECT_SETUP_INIT )                         ) |
              VSEP_Msg_EST_Set_DEC_DISCB( 0,    VSEP_EST_Select_Get_Select_Mode( VSEP_1_EST_SELECT_SETUP_INIT )                         ) |
                VSEP_Msg_EST_Set_IGBTCFG( 0,     VSEP_EST_Select_Get_Drive_Mode( VSEP_1_EST_SELECT_SETUP_INIT )                         ) 
      }

   }
#endif
};

uint16_t VSEP_MPIO_MODE_Txd[NUMBER_OF_VSEP][VSEP_MPIO_MODE_TXD_MESSAGE_MAX];


/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
 * 9.0  272        08/11/24 sjl Add configurable calibrations for discrete inputs 
\*===========================================================================*/
