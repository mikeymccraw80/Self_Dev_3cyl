//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec    :   dd_mcd5402.c %
//
// created_by       :   dz48hg
//
// date_created     :   Mon, Sep 10, 2007 7:57:31 PM
//
// %derived_by       :   mz01yw %
//
// %date_modified    :    Mon, Mar 24, 2008 09:26:30 AM %
//
// %version          :   tci_pt2#7 %
//
// ============================================================================
//
//==========================================================================
// REUSE:                                                                    
// DO NOT MODIFY THIS FILE.  Coordinate any desired changes with the         
// Complex I/O group.                                                        
//                                                                           
//===========================================================================

#include "dd_mcd5402.h"
#include "mcd5402.h"
#include "dd_tpu.h"
// #include "io.h"
// #include "pulse.h"

//=============================================================================
// MCD5402_Initialize_Channel
//=============================================================================
void MCD5402_Initialize_Channel(
   TPU_Index_T index,
   TPU_T       *p_tpu,
   TPU_CHANNEL_Configuration_T   configure )
{
   TPU_Channel_T channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU_Index_T index_group = TPU_Get_Index_Group(index);

   uint32_t critical_status;

   uint8_t fun_mode0;

   uint8_t fun_mode1;

   critical_status = Enter_Critical_Section();
    
   TPU_Initialize_Channel(index, configure);

   TPU_Set_Static_Base_Address(index, configure);
   // Select the time base
   fun_mode0 = configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0;

   p_tpu->Channel_Map[index_group].Channel_Control[channel].CSCR.F.FM0 = fun_mode0;

   //Set the edge type
   fun_mode1 = configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE1;

   p_tpu->Channel_Map[index_group].Channel_Control[channel].CSCR.F.FM1 = fun_mode1;

   // Issue HSR
   TPU_Set_HSR(index, configure, PWMIE_HSR_INITIALIZE);

   //Set channel priority
   TPU_Channel_Enable(index, configure); 

   // Wait until the channel not active
   TPU_Wait_HSR_Request_Complete(index, configure);

   Leave_Critical_Section( critical_status );

}

//=============================================================================
// MCD5402_Get_Period
//=============================================================================
uint32_t MCD5402_Get_Period(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5402_SDM_T *mcd5402_sdm = (MCD5402_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   return(mcd5402_sdm->Period_Hi_Time.F.Period);   
}

//=============================================================================
// MCD5402_Get_Duty_Cycle
//=============================================================================
uint32_t MCD5402_Get_Duty_Cycle(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5402_SDM_T *mcd5402_sdm = (MCD5402_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   return(mcd5402_sdm->Period_Hi_Time.F.HighTime);   
}

//=============================================================================
// MCD5402_Get_Coherent_Period_And_Duty_Cycle
//=============================================================================
PWM_Data_T* MCD5402_Get_Coherent_Period_And_Duty_Cycle(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   PWM_Data_T*          pwm_data )
{
   MCD5402_SDM_T *mcd5402_sdm = (MCD5402_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   MCD5402_Coherent_Period_Hi_Time_T temp_coherent_data;

   //Period and High Time are written coherently by TPU.
   //CPU should read them coherently.
   TPU_SDM_Read_Coherent_Data(
      0,
      (uint32_t*)&mcd5402_sdm->Period_Hi_Time.U32[0],
      &temp_coherent_data.U32[0],
      (uint32_t*)&mcd5402_sdm->Period_Hi_Time.U32[1],
      &temp_coherent_data.U32[1] );

   pwm_data->Period = temp_coherent_data.F.Period;

   pwm_data->Duty_Cycle = temp_coherent_data.F.HighTime;
     
   return(pwm_data);   
}

//=============================================================================
// MCD5402_Get_Coherent_Accum_Period_Duty_And_Count
//=============================================================================
PWM_Data_T* MCD5402_Get_Coherent_Accum_Period_Duty_And_Count(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   PWM_Data_T*       pulse_data )
{
   MCD5402_SDM_T *mcd5402_sdm = (MCD5402_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   MCD5402_Coherent_Accum_T temp_coherent_data;
   
   //Accumulated Period,High Time and Count are written coherently by TPU.
   // CPU should read them coherently.
   TPU_SDM_Read_Coherent_Data(
      0,
      (uint32_t*)&mcd5402_sdm->Accum_Time_Count.U32[0],
      &temp_coherent_data.U32[0],
      (uint32_t*)&mcd5402_sdm->Accum_Time_Count.U32[1],
      &temp_coherent_data.U32[1] );

   pulse_data->Period = temp_coherent_data.F.Accum_Period;

   pulse_data->Duty_Cycle = temp_coherent_data.F.Accum_Hi_Time;

   return(pulse_data);
}

//=============================================================================
// MCD5402_Get_Coherent_Edge_Time_And_Count
//=============================================================================
IO_Edge_Data_T* MCD5402_Get_Coherent_Edge_Time_And_Count(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   IO_Edge_Data_T*      edge_data )
{
   MCD5402_SDM_T *mcd5402_sdm = (MCD5402_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   MCD5402_Coherent_Edge_T temp_coherent_data;

   temp_coherent_data.U32 = mcd5402_sdm->Crit_Edge_Time_Count.U32;
    
   edge_data->Time = temp_coherent_data.F.Crit_Edge_Time;

   edge_data->Count = temp_coherent_data.F.Crit_Edge_Cnt_B;

   return(edge_data);
}

//=============================================================================
// MCD5402_Get_Period_TimeOut
//=============================================================================
bool MCD5402_Get_Period_TimeOut(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5402_SDM_T *mcd5402_sdm = (MCD5402_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   bool period_time_out;

   period_time_out = (mcd5402_sdm->Period_Hi_Time.F.One_Crit_Edge == 0)? true : false;

   return period_time_out;
}

//=============================================================================
// MCD5402_Get_Edge
//=============================================================================
IO_Edge_T MCD5402_Get_Edge(
   TPU_Index_T index,
   TPU_T       *p_tpu,
   TPU_CHANNEL_Configuration_T   configure )
{
   TPU_Channel_T  channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU_Index_T    index_group = TPU_Get_Index_Group(index);
   bitfield32_t   fun_mode1;
   IO_Edge_T      edge;
    
   fun_mode1 = p_tpu->Channel_Map[index_group].Channel_Control[channel].CSCR.F.FM1;
   
   edge = (fun_mode1 == 0) ? IO_EDGE_FALLING : IO_EDGE_RISING;

   return edge;
}

//=============================================================================
// MCD5402_Set_Edge
//=============================================================================
void MCD5402_Set_Edge(
   TPU_Index_T index,
   TPU_T       *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   IO_Edge_T in_edge )
{
   TPU_Channel_T  channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU_Index_T    index_group = TPU_Get_Index_Group(index);
   bitfield32_t   fun_mode1;
    
   fun_mode1 = (in_edge == IO_EDGE_FALLING) ? 0 : 1;
   
   p_tpu->Channel_Map[index_group].Channel_Control[channel].CSCR.F.FM1 = fun_mode1;
}

//=============================================================================
// MCD5402_Get_Max_Measureable_Period
//=============================================================================
uint32_t MCD5402_Get_Max_Measureable_Period(
   IO_Configuration_T   in_configuration )
{
   // Parameter_Not_Used(in_configuration);
   return MCD5402_MAX_MEASUREABLE_PERIOD;
}

//=============================================================================
// MCD5402_Shutdown
//=============================================================================
void MCD5402_Shutdown(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{

   interrupt_state_t  critical_status;

   //Enter critical section
   critical_status = Enter_Critical_Section();
   
   // Issue HSR
   TPU_Set_HSR(index, configure, PWMIE_HSR_SHUTDOWN);

   // Wait until the channel not active
   TPU_Wait_HSR_Request_Complete(index, configure);

   // Disable channel
   TPU_Channel_Disable(index, configure);

   Leave_Critical_Section( critical_status );

}

//=============================================================================
// MCD5402_Get_Max_Edge_Count
//=============================================================================
uint32_t MCD5402_Get_Max_Edge_Count(
   IO_Configuration_T   in_configuration )
{
   // Parameter_Not_Used(in_configuration);
   return MCD5402_MAX_EDGE_COUNT;
}
