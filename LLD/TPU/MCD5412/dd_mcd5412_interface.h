#ifndef DD_MCD5412_INTERFACE_H
#define DD_MCD5412_INTERFACE_H

#include "dd_mcd5412.h"



//=============================================================================
// Function Prototypes                                                         
//=============================================================================

//=============================================================================
// MCD5412_Initialize_Channel
//=============================================================================
void MCD5412_Initialize_Channel(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Request_Pulse
//=============================================================================
void MCD5412_Request_Pulse( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Request_Update
//=============================================================================
void MCD5412_Request_Update( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_Min_Duration
//=============================================================================
void MCD5412_Set_Min_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_value ); 

//=============================================================================
// MCD3458_Get_Min_Duration
//=============================================================================
uint32_t MCD5412_Get_Min_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_Max_Duration
//=============================================================================
void MCD5412_Set_Max_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_value );

//=============================================================================
// MCD3458_Get_Max_Duration
//=============================================================================
uint32_t MCD5412_Get_Max_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_Duration
//=============================================================================
void MCD5412_Set_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_value );

//=============================================================================
// MCD5412_Get_Desired_Duration
//=============================================================================
uint32_t MCD5412_Get_Desired_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Get_Actual_Duration
//=============================================================================
uint32_t MCD5412_Get_Actual_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Get_Pulse_Counter
//=============================================================================
uint32_t MCD5412_Get_Pulse_Counter( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Get_End_Time
//=============================================================================
uint32_t MCD5412_Get_End_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Get_Start_Time
//=============================================================================
uint32_t MCD5412_Get_Start_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Get_CPU_End_Time
//=============================================================================
uint32_t MCD5412_Get_CPU_End_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_CPU_End_Time
//=============================================================================
void MCD5412_Set_CPU_End_Time(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t            value );

//=============================================================================
// MCD5412_Get_CPU_Start_Time
//=============================================================================
uint32_t MCD5412_Get_CPU_Start_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_CPU_Start_Time
//=============================================================================
void MCD5412_Set_CPU_Start_Time(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t            value );

//=============================================================================
// MDC5412_Get_Angle
//=============================================================================
uint32_t MCD5412_Get_Angle( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_Angle
//=============================================================================
void MCD5412_Set_Angle(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t          in_angle );

//=============================================================================
// MCD5412_Get_Min_Off_Time
//=============================================================================
uint32_t MCD5412_Get_Min_Off_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_Min_Off_Time
//=============================================================================
void MCD5412_Set_Min_Off_Time( 
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_min_off_time );

//=============================================================================
// MCD5412_Set_On_Time_2
//=============================================================================
void MCD5412_Set_On_Time_2(
       TPU_Index_T index,
   uint32_t          value ); 

//=============================================================================
// MCD5412_Get_On_Time_2
//=============================================================================
uint32_t MCD5412_Get_On_Time_2(
        TPU_Index_T index ); 

//=============================================================================
// MCD5412_Set_Off_Time_2
//=============================================================================
void MCD5412_Set_Off_Time_2(
       TPU_Index_T index,
   uint32_t          value ); 

//=============================================================================
// MCD5412_Get_Off_Time_2
//=============================================================================
uint32_t MCD5412_Get_Off_Time_2(
        TPU_Index_T index ); 

//=============================================================================
// MCD5412_Set_On_Time_3
//=============================================================================
void MCD5412_Set_On_Time_3(
       TPU_Index_T index,
   uint32_t          value ); 

//=============================================================================
// MCD5412_Get_On_Time_3
//=============================================================================
uint32_t MCD5412_Get_On_Time_3(
        TPU_Index_T index ); 

//=============================================================================
// MCD5412_Set_Extra_Pulses
//=============================================================================
void MCD5412_Set_Extra_Pulses(
       TPU_Index_T index,
   uint32_t          value ); 

//=============================================================================
// MCD5412_Get_Extra_Pulses
//=============================================================================
uint32_t MCD5412_Get_Extra_Pulses(
        TPU_Index_T index );

//=============================================================================
// MCD5412_Set_Time_Mode
//=============================================================================
void MCD5412_Set_Time_Mode(
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   MPTAC_Time_Mode_T in_mode );

//=============================================================================
// MCD5412_Get_Time_Mode
//=============================================================================
MPTAC_Time_Mode_T MCD5412_Get_Time_Mode(
     TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5412_Set_Host_Interrupt_Enable
//=============================================================================
void MCD5412_Set_Host_Interrupt_Enable(
       TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool                in_state );

//=============================================================================
// MCD5412_Get_Host_Interrupt_Enable
//=============================================================================
bool MCD5412_Get_Host_Interrupt_Enable(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_Host_Interrupt_Status
//=============================================================================
void MCD5412_Set_Host_Interrupt_Status(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool              in_state );

//=============================================================================
// MCD5412_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5412_Get_Host_Interrupt_Status(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool              in_state );

//=============================================================================
// MCD5412_Get_Actual_End_Angle
//=============================================================================
uint32_t MCD5412_Get_Actual_End_Angle(
           TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// MCD5412_Set_Actual_End_Angle
//=============================================================================
void MCD5412_Set_Actual_End_Angle(
           TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure, 
   uint32_t       in_angle );

//=============================================================================
// MCD5412_Set_Min_Angle_For_Rise
//=============================================================================
void MCD5412_Set_Min_Angle_For_Rise(
              TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint8_t        in_angle );

//=============================================================================
// MCD5412_Set_Max_Fall_Angle
//=============================================================================
void MCD5412_Set_Max_Fall_Angle(
                TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint8_t        in_angle );

//=============================================================================
// MCD5412_Set_Flag
//=============================================================================
void MCD5412_Set_Flag(
                 TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   MPTAC_Flags_T  in_flag,
   bool           in_enable);
           
//=============================================================================
// MCD5412_Request_Abort
//=============================================================================
void MCD5412_Request_Abort(
              TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5412_Set_Comp_Time
//=============================================================================
void MCD5412_Set_Comp_Time(
                  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t        in_comp_time);

//=============================================================================
// MCD5412_Get_Discrete_Status
//=============================================================================
bool MCD5412_Get_Discrete_Status(
                     TPU_Index_T index,
                        TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure);

#endif // DD_MCD5412_INTERFACE_H 
