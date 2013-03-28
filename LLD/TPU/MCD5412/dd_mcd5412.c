
#include "dd_mcd5412.h"
//#include "dd_mcd5412_interface.h"
   MCD5412_SDM_T   *mcd5412_sdm_vis;
//=============================================================================
// MCD5412_Initialize_Channel
//=============================================================================
void MCD5412_Initialize_Channel(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   interrupt_state_t  interrupts_status;

     // Enter critical section
   interrupts_status = Enter_Critical_Section();
	 
	    mcd5412_sdm_vis = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure); 


   // Select TCR1/TCR2,Entry table,CFSR and SIU and host interrupt
   TPU_Initialize_Channel(index, configure);
   
   // Initialization of PRAM start address in CPBA
   TPU_Set_Static_Base_Address(index, configure);

   // Use Set functions for selecting angle/time mode, multi-pulse,
   // DIG_Shutoff_Enabled, ED / SD modes

   // Issue HSR
   TPU_Set_HSR(index, configure, MPTACE_HSR_INITIALIZE);

   // Set channel priority CPR
   TPU_Channel_Enable(index, configure); 

   // Wait until the channel not active
   TPU_Wait_HSR_Request_Complete(index, configure);

   // Exit critical section
   Leave_Critical_Section( interrupts_status );
}

//=============================================================================
// MCD5412_Request_Pulse
//=============================================================================
void MCD5412_Request_Pulse( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   interrupt_state_t  interrupts_status;

   // Enter critical section
   interrupts_status = Enter_Critical_Section();
   
   // Issue Request HSR
   TPU_Set_HSR(index, configure, MPTACE_HSR_REQUEST);

   // Exit critical section
   Leave_Critical_Section( interrupts_status );
}

//=============================================================================
// MCD5412_Request_Update
//=============================================================================
void MCD5412_Request_Update( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   interrupt_state_t  interrupts_status;

   // Enter critical section
   interrupts_status = Enter_Critical_Section();

   // Issue Request HSR
   TPU_Set_HSR(index, configure, MPTACE_HSR_UPDATE);

   // Exit critical section
   Leave_Critical_Section( interrupts_status );
}

//=============================================================================
// MCD5412_Set_Min_Duration
//=============================================================================
void MCD5412_Set_Min_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_value ) 
{
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   mcd5412_sdm->Min_Duration.F.Duration = in_value;
}

//=============================================================================
// MCD5412_Get_Min_Duration
//=============================================================================
uint32_t MCD5412_Get_Min_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return (uint32_t)mcd5412_sdm->Min_Duration.F.Duration;
}

//=============================================================================
// MCD5412_Set_Max_Duration
//=============================================================================
void MCD5412_Set_Max_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_value )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   mcd5412_sdm->Max_Duration.F.Duration = in_value;
}

//=============================================================================
// MCD5412_Get_Max_Duration
//=============================================================================
uint32_t MCD5412_Get_Max_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return (uint32_t)mcd5412_sdm->Max_Duration.F.Duration;
}

//=============================================================================
// MCD5412_Set_Duration
//=============================================================================
void MCD5412_Set_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_value )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   // do for all
   // Limit to range maximum
   in_value = MCD5412_LIMIT_TO_TIMER_MAX_DIV_BY_2(in_value);

   mcd5412_sdm->Duration.F.Duration = in_value;

}

//=============================================================================
// MCD5412_Get_Desired_Duration
//=============================================================================
uint32_t MCD5412_Get_Desired_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t return_value;
   
   if( mcd5412_sdm->Critical_Event.F.In_SD_Mode == 0)
   {
      // Endtime Duration Mode
      return_value = mcd5412_sdm->Duration.F.Duration; 
   }
   else
   {
      // Starttime Duration Mode
      return_value = mcd5412_sdm->Min_Duration.F.Duration;
   }
   return return_value;
}

//=============================================================================
// MCD5412_Get_Actual_Duration
//=============================================================================
uint32_t MCD5412_Get_Actual_Duration( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t actual_duration;

   // Get the actual duration
   actual_duration = mcd5412_sdm->Fall_1_Time.F.Time - mcd5412_sdm->Rise_Time.F.Time;
   
   // Limit the result to timer max
   actual_duration = MCD5412_LIMIT_TO_TIMER_SIZE( actual_duration );
   
   return actual_duration;
}

//=============================================================================
// MCD5412_Get_Pulse_Counter
//=============================================================================
uint32_t MCD5412_Get_Pulse_Counter( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
 
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return (mcd5412_sdm->Rise_Time.F.Pulse_Counter);
}

//=============================================================================
// MCD5412_Get_End_Time
//=============================================================================
uint32_t MCD5412_Get_End_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return (mcd5412_sdm->Fall_1_Time.F.Time);
}

//=============================================================================
// MCD5412_Get_Start_Time
//=============================================================================
uint32_t MCD5412_Get_Start_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return (mcd5412_sdm->Rise_Time.F.Time);
}

//=============================================================================
// MCD5412_Get_CPU_End_Time
//=============================================================================
uint32_t MCD5412_Get_CPU_End_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t value;
   
   // Limit to range maximum 
   value = MCD5412_LIMIT_TO_TIMER_MAX_DIV_BY_2(mcd5412_sdm->Critical_Event.F.Event);

   return (value);
}

//=============================================================================
// MCD5412_Set_CPU_End_Time
//=============================================================================
void MCD5412_Set_CPU_End_Time(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t            value )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   mcd5412_sdm->Critical_Event.F.Event = value;
}

//=============================================================================
// MCD5412_Get_CPU_Start_Time
//=============================================================================
uint32_t MCD5412_Get_CPU_Start_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t value;
   
   // Limit to range maximum
   value = MCD5412_LIMIT_TO_TIMER_MAX_DIV_BY_2(mcd5412_sdm->Critical_Event.F.Event);

   return (value);
}

//=============================================================================
// MCD5412_Set_CPU_Start_Time
//=============================================================================
void MCD5412_Set_CPU_Start_Time(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t            value )
{
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   mcd5412_sdm->Critical_Event.F.Event = value;
}

//=============================================================================
// MCD5412_Get_Angle
//=============================================================================
uint32_t MCD5412_Get_Angle( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return (mcd5412_sdm->Critical_Event.F.Event);
}

//=============================================================================
// MCD5412_Set_Angle
//=============================================================================
void MCD5412_Set_Angle(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t          in_angle )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
     
   // Assign the value
   mcd5412_sdm->Critical_Event.F.Event = in_angle;
}

//=============================================================================
// MCD5412_Get_Min_Off_Time
//=============================================================================
uint32_t MCD5412_Get_Min_Off_Time( 
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return (mcd5412_sdm->Min_Off_Time.F.Time);
}

//=============================================================================
// MCD5412_Set_Min_Off_Time
//=============================================================================
void MCD5412_Set_Min_Off_Time( 
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t       in_min_off_time )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   
   // Limit to range maximum
   mcd5412_sdm->Min_Off_Time.F.Time = MCD5412_LIMIT_TO_TIMER_MAX_DIV_BY_2(in_min_off_time);
}


//=============================================================================
// MCD5412_Set_On_Time_2
//=============================================================================
void MCD5412_Set_On_Time_2(
       TPU_Index_T index,
   uint32_t          value ) 
{

   MPTACE_GLOBAL_RAM(index).F.On_Time_2.F.On_Time_2 = value;
}

//=============================================================================
// MCD5412_Get_On_Time_2
//=============================================================================
uint32_t MCD5412_Get_On_Time_2(
        TPU_Index_T index ) 
{

   return (MPTACE_GLOBAL_RAM(index).F.On_Time_2.F.On_Time_2);
}

//=============================================================================
// MCD5412_Set_Off_Time_2
//=============================================================================
void MCD5412_Set_Off_Time_2(
       TPU_Index_T index,
   uint32_t          value ) 
{

   MPTACE_GLOBAL_RAM(index).F.Off_Time_2.F.Off_Time_2 = value;
}

//=============================================================================
// MCD5412_Get_Off_Time_2
//=============================================================================
uint32_t MCD5412_Get_Off_Time_2(
        TPU_Index_T index )
{
   return (MPTACE_GLOBAL_RAM(index).F.Off_Time_2.F.Off_Time_2);
}

//=============================================================================
// MCD5412_Set_On_Time_3
//=============================================================================
void MCD5412_Set_On_Time_3(
       TPU_Index_T index,
   uint32_t          value ) 
{

   MPTACE_GLOBAL_RAM(index).F.On_Time_3.F.On_Time_3 = value;
}

//=============================================================================
// MCD5412_Get_On_Time_3
//=============================================================================
uint32_t MCD5412_Get_On_Time_3(
        TPU_Index_T index ) 
{
   return (MPTACE_GLOBAL_RAM(index).F.On_Time_3.F.On_Time_3);
}

//=============================================================================
// MCD5412_Set_Extra_Pulses
//=============================================================================
void MCD5412_Set_Extra_Pulses(
       TPU_Index_T index,
   uint32_t          value ) 
{
 
   MPTACE_GLOBAL_RAM(index).F.On_Time_2.F.Extra_Pulses = value;
}

//=============================================================================
// MCD5412_Get_Extra_Pulses
//=============================================================================
uint32_t MCD5412_Get_Extra_Pulses(
        TPU_Index_T index )
{

   // handled by global ram
   return (MPTACE_GLOBAL_RAM(index).F.On_Time_2.F.Extra_Pulses);
}

//=============================================================================
// MCD5412_Set_Time_Mode
//=============================================================================
void MCD5412_Set_Time_Mode(
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   MPTAC_Time_Mode_T in_mode )
{
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   TPU_Channel_T channel  = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   if ( in_mode == MPTAC_TIME_MODE_CPU_CALCULATES_END_TIME )
   {   
      // End time Duration mode 
      mcd5412_sdm->Critical_Event.F.In_SD_Mode = MCD5412_END_DURATION_MODE;

      p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 =  MCD5412_TIME_MODE;
      
   }

   if ( in_mode == MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_END_TIME )
   {
      // End time Duration mode 
      mcd5412_sdm->Critical_Event.F.In_SD_Mode = MCD5412_END_DURATION_MODE;

      p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 =  MCD5412_ANGLE_MODE;
   }


   if ( in_mode == MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME )
   {
      // Start time Duration mode
      mcd5412_sdm->Critical_Event.F.In_SD_Mode = MCD5412_START_DURATION_MODE;

      p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 = MCD5412_TIME_MODE;
   }


   if ( in_mode == MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_START_TIME )
   {
      // Start angle Duration Mode 
      mcd5412_sdm->Critical_Event.F.In_SD_Mode = MCD5412_START_DURATION_MODE;

      p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 =  MCD5412_ANGLE_MODE;
   }
}

//=============================================================================
// MCD5412_Get_Time_Mode
//=============================================================================
MPTAC_Time_Mode_T MCD5412_Get_Time_Mode(
     TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
     TPU_Channel_T channel  = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   MCD5412_Angle_Mode_T   time_cal_mode;
   MPTAC_Time_Mode_T   time_mode;

   time_cal_mode = (MCD5412_Angle_Mode_T)p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1;

   if(MCD5412_TIME_MODE == time_cal_mode)
   {
      if(mcd5412_sdm->Critical_Event.F.In_SD_Mode == MCD5412_START_DURATION_MODE)
      {
         time_mode = MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME;
      }
      else
      {
         time_mode = MPTAC_TIME_MODE_CPU_CALCULATES_END_TIME;
      }
   }
   else
   {
      if(mcd5412_sdm->Critical_Event.F.In_SD_Mode == MCD5412_START_DURATION_MODE)
      {
         time_mode = MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_START_TIME;
      }
      else
      {
         time_mode = MPTAC_TIME_MODE_PRIMITIVE_CALCULATES_END_TIME;
      }
   }
   return time_mode;
}

//=============================================================================
// MCD5412_Set_Host_Interrupt_Enable
//=============================================================================
void MCD5412_Set_Host_Interrupt_Enable(
       TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool                in_state )
{
   TPU_Channel_T channel =configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   
   if ( true == in_state )
   {
      p_tpu->CIER[index].U32 |= (uint32_t)(1 << channel);
   }
   else
   {
      p_tpu->CIER[index].U32 &= ~((uint32_t)(1 << channel));
   }
}

//=============================================================================
// MCD5412_Get_Host_Interrupt_Enable
//=============================================================================
bool MCD5412_Get_Host_Interrupt_Enable(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{
   TPU_Channel_T channel =configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   bool status;

   status =   (bool)((p_tpu->CIER[index].U32 & (uint32_t)(1 << channel))>>channel);

   return (status);
}

//=============================================================================
// MCD5412_Set_Host_Interrupt_Status
//=============================================================================
void MCD5412_Set_Host_Interrupt_Status(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool              in_state )
{
   TPU_Channel_T channel =configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   if ( true == in_state )
   {
      // request host interrupt
      // Not supported in TPU
   }
   else
   {
      // clear pending host interrupt
      p_tpu->CISR[index].U32 = (uint32_t)(1 << channel);
   }
}

//=============================================================================
// MCD5412_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5412_Get_Host_Interrupt_Status(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool              in_state )
{
   TPU_Channel_T channel =configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   bool status;

   status =   (bool)((p_tpu->CISR[index].U32 & (uint32_t)(1 << channel))>>channel);

   return (status);
}


//=============================================================================
// MCD5412_Get_Actual_End_Angle
//=============================================================================
uint32_t MCD5412_Get_Actual_End_Angle(
           TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
     
   return (mcd5412_sdm->Fall_1_Angle.F.Angle);
}

//=============================================================================
// MCD5412_Set_Actual_End_Angle
//=============================================================================
void MCD5412_Set_Actual_End_Angle(
           TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure, 
   uint32_t       in_angle )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
     
   mcd5412_sdm->Fall_1_Angle.F.Angle = in_angle;
}

//=============================================================================
// MCD5412_Request_Abort
//=============================================================================
void MCD5412_Request_Abort(
              TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   interrupt_state_t  interrupts_status;


   //Enter critical section
   interrupts_status = Enter_Critical_Section();

   TPU_Set_HSR(index, configure, MPTACE_HSR_ABORT_REQUEST);

   // Exit critical section
   Leave_Critical_Section( interrupts_status );
}

//=============================================================================
// MCD5412_Set_Min_Angle_For_Rise
//=============================================================================
void MCD5412_Set_Min_Angle_For_Rise(
              TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint8_t        in_angle )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
     
   // Assign the value
   mcd5412_sdm->Duration.F.Min_Rise_Angle= in_angle;
}

//=============================================================================
// MCD5412_Set_Max_Fall_Angle
//=============================================================================
void MCD5412_Set_Max_Fall_Angle(
                TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint8_t        in_angle )
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
     
   // Assign the value
   mcd5412_sdm->Min_Duration.F.Max_Fall_Angle = in_angle;
}


//=============================================================================
// MCD5412_Set_Flag
//=============================================================================
void MCD5412_Set_Flag(
                 TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   MPTAC_Flags_T  in_flag,
   bool           in_enable)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
     
   switch(in_flag)
   {
      case MPTAC_REQ_OUT_OF_RANGE_FLAG:
      {
         mcd5412_sdm->Critical_Event.F.Req_Out_Of_Range = (in_enable == true)? 1:0;
         break;
      }
      case MPTAC_MULTI_PULSE_MODE_FLAG:
      {
         mcd5412_sdm->Critical_Event.F.Multi_Pulse_Mode = (in_enable == true)? 1:0;
         break;
      }
      case MPTAC_DIG_SHUTOFF_ENABLED_FLAG:
      {
         mcd5412_sdm->Critical_Event.F.Dig_ShutOff_Enabled = (in_enable == true)? 1:0;
         break;
      }
      default:
      {
         break;
      }
   }
}

//=============================================================================
// MCD5412_Set_Comp_Time
//=============================================================================
void MCD5412_Set_Comp_Time(
                  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t        in_comp_time)
{

   MCD5412_SDM_T   *mcd5412_sdm = (MCD5412_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   mcd5412_sdm->Comp_Time.F.Time = in_comp_time;

}

//=============================================================================
// MCD5412_Get_Discrete_Status
//=============================================================================
bool MCD5412_Get_Discrete_Status(
                     TPU_Index_T index,
                        TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{
   bool  active_state;
   bool  state;
   Polarity_T           polarity =  configure.F.TPU_CHANNEL_CONFIGURATION_POLARITY;
   TPU_Channel_T channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   state = (bool)p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.OPS;

    // State  Polarity  active_state 
   //----------------
   //   0      0        1 
   //   0      1        0 
   //   1      0        0 
   //   1      1        1

   active_state   = ( ( state == polarity ) ? true: false);
   return active_state;
}
