//===========================================================================
// incldue files
//===========================================================================
#include "dd_mcd5411.h"
#include "dd_cam.h"

//===========================================================================
// MCD5411_Initialize_Channel
//===========================================================================
void MCD5411_Initialize_Channel(
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   const void          *in_init )
{

   TPU_Channel_T channel= configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   MCD5411_Channel_Init_T *parameters = (MCD5411_Channel_Init_T *)in_init;
   MCD5411_SDM_T  *mcd5411_sdm =
      (MCD5411_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t critical_status;

   critical_status = Enter_Critical_Section();
   // Initialize Replicated Cam Output
   mcd5411_sdm->F.Ncrit_ET_And_Flag.F.Rep_Out_En = parameters->Rep_Enable;

   if( MCD5411_CAME_REPLICATE_ENABLE == parameters->Rep_Enable )
   {
      CAME_GLOBAL_RAM(index).F.Rep_Out_Info.F.Rep_Out_Chan_Num = parameters->Rep_Channel;
      CAME_GLOBAL_RAM(index).F.Rep_Out_Info.F.Rep_Out_Lag_Time = parameters->Rep_Lag_Time;
   }

   // Initialize Interrupts
   mcd5411_sdm->F.Ncrit_ET_And_Flag.F.NCrit_IRQ_En = parameters->Non_Crit_IRQ_Enable;
   mcd5411_sdm->F.Ncrit_ET_And_Flag.F.Crit_IRQ_En = parameters->Crit_IRQ_Enable;
   TPU_Initialize_Channel(index, configure);
   TPU_Set_Static_Base_Address(index, configure);
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM0 =
      (uint8_t)parameters->Use_TCR2;
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 =
      (uint8_t)parameters->Rep_Out_Inv;

   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.ETCS =
      CAME_ENTRYTABLE_TYPE;

   MCD5411_Rep_Channel_Num = (uint8_t)parameters->Rep_Channel;
   if(parameters->HSR_Initialize == true)
   {
      TPU_Set_HSR(index, configure, MCD5411_HSR_CRIT_EDGE_RISING );
   }
   else
   {
      TPU_Set_HSR(index, configure, MCD5411_HSR_CRIT_EDGE_FALLING );
   }

   TPU_Channel_Enable(index, configure);

   TPU_Wait_HSR_Request_Complete(index, configure);

   Leave_Critical_Section( critical_status );
}

//===========================================================================
// MCD5411_Clear_Channel
//===========================================================================
void MCD5411_Clear_Channel(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
    uint32_t        counter ;
   MCD5411_SDM_T  *mcd5411_sdm =
      (MCD5411_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);

   // erase parameter ram for this channel
   for ( counter = 0; counter < (  ( sizeof(MCD5411_SDM_F_T) )/( sizeof(uint32_t) )  ); counter++ )
   {
      mcd5411_sdm->U32[counter] = 0;
   }
}

//=============================================================================
// MCD5411_Set_Parameter
//=============================================================================
void MCD5411_Set_Parameter(
          TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Parameter_T  in_parameter,
   uint32_t                in_value )
{
   MCD5411_SDM_T  *mcd5411_sdm = (MCD5411_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);

   switch ( in_parameter )
   {
   case CAM_SENSOR_PARAMETER_MIN_PERIOD:
      {
         // limit the rate at which the primitive can interrupt
         // the CPU if some fault condition creates a high frequency signal at the CAM input
         CAME_GLOBAL_RAM(index).F.Min_Period.F.Min_Period = in_value;
      }
      break;

   case CAM_SENSOR_PARAMETER_REPLICATED_CAM_OUTPUT_LAG_TIME:
      {
         // The amount of time by which the replicated cam output signal will
         //lag the cam input signal. Units correspond with the Use_TCR2 bit. Only valid when Rep_Out_En = 1.
         CAME_GLOBAL_RAM(index).F.Rep_Out_Info.F.Rep_Out_Lag_Time = in_value;
      }
      break;

   case CAM_SENSOR_PARAMETER_NOISE_COUNT:
      {
         // the noise count
         mcd5411_sdm->F.Period_And_Noise_Cnt.F.Noise_Cnt = in_value;
      }
      break;

   default:
      {
         // do nothing
      }
      break;
   }
}

//=============================================================================
// MCD5411_Get_Parameter
//=============================================================================
uint32_t MCD5411_Get_Parameter(
          TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Parameter_T  in_parameter )
{
   MCD5411_SDM_T *mcd5411_sdm = (MCD5411_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t       value;

   switch ( in_parameter )
   {
   case CAM_SENSOR_PARAMETER_OFF_PERIOD:
      {
         // from the non-critical edge time to the critical edge time.  This values update on the critical edge
         volatile uint32_t coherent_1;
         volatile uint32_t coherent_2;
         volatile uint32_t critical_edge_time;
         volatile uint32_t non_critical_edge_time;

         // Critical section is not needed. CAMe_Buff_NCrit_ET and CAMe_Crit_ET can
         // only change value on critical edges.  The only situation that an interrupt
         // latency can cause data incoherency is that if we are processing the data
         // right on a critical edge, which is covered by using coherenct_1 and
         // coherency_2 flag. There is no concern that interrupt latency can last as
         // long as two critical edge distances, becasue they are 180 degrees apart
         // for 4X cam signals.
         do
         {
            non_critical_edge_time = mcd5411_sdm->F.Buff_NCrit_ET_And_Flag.U32;
            critical_edge_time = mcd5411_sdm->F.Crit_ET.U32;

            coherent_2 = mcd5411_sdm->F.Prev_Crit_ET_And_Flags.U32 &
               MCD5411_COHERENCY_BIT_MASK;
            coherent_1 = non_critical_edge_time & MCD5411_COHERENCY_BIT_MASK;

         } while( coherent_1 != coherent_2 );

         critical_edge_time &= UINT24_MAX;
         non_critical_edge_time &= UINT24_MAX;

         value = (uint32_t)
            (((uint32_t)( critical_edge_time - non_critical_edge_time )) &
            UINT24_MAX );
      }
      break;

   case CAM_SENSOR_PARAMETER_ON_PERIOD:
      {
         // starting with the previous critical edge ending with the  non critical edge
         volatile uint32_t coherent_1;
         volatile uint32_t coherent_2;
         volatile uint32_t non_critical_edge_time;
         volatile uint32_t prev_critical_edge_time;
         volatile uint32_t on_period;

         // Critical section is not needed. CAMe_Buff_NCrit_ET and CAMe_Crit_ET can
         // only change value on critical edges.  The only situation that an interrupt
         // latency can cause data incoherency is that if we are processing the data
         // right on a critical edge, which is covered by using coherenct_1 and
         // coherency_2 flag. There is no concern that interrupt latency can last as
         // long as two critical edge distances, becasue they are 180 degrees apart
         // for 4X cam signals.
         do
         {
            non_critical_edge_time = mcd5411_sdm->F.Buff_NCrit_ET_And_Flag.U32;
            prev_critical_edge_time = mcd5411_sdm->F.Prev_Crit_ET_And_Flags.U32;

            coherent_1 = non_critical_edge_time & MCD5411_COHERENCY_BIT_MASK;
            coherent_2 = prev_critical_edge_time & MCD5411_COHERENCY_BIT_MASK;

         } while( coherent_1 != coherent_2 );

         non_critical_edge_time &= UINT24_MAX;
         prev_critical_edge_time &= UINT24_MAX;

         value = (uint32_t)
            (((uint32_t)( non_critical_edge_time - prev_critical_edge_time )) &
            UINT24_MAX );
      }
      break;

   case CAM_SENSOR_PARAMETER_MIN_PERIOD:
      {
         // limit the rate at which the primitive can interrupt the CPU if some fault condition
         // creates a high frequency signal at the CAM input
         value = CAME_GLOBAL_RAM(index).F.Min_Period.F.Min_Period;
      }
      break;

   case CAM_SENSOR_PARAMETER_REPLICATED_CAM_OUTPUT_LAG_TIME:
      {
         // The amount of time by which the replicated cam output signal will lag the cam
         // input signal. Units correspond with the Use_TCR2 bit. Only valid when Rep_Out_En = 1.
         value = CAME_GLOBAL_RAM(index).F.Rep_Out_Info.F.Rep_Out_Lag_Time;
      }
      break;

   case CAM_SENSOR_PARAMETER_CRITICAL_EDGE_TIME:
      {
         // returns the cam critical edge time
         value = mcd5411_sdm->F.Crit_ET.F.Crit_ET;
      }
      break;

   case CAM_SENSOR_PARAMETER_CRITICAL_EDGE_COUNT:
      {
         // the cam critical edge time
         value = mcd5411_sdm->F.Crit_Ecnt.F.Crit_Ecnt;
      }
      break;

   case CAM_SENSOR_PARAMETER_NON_CRITICAL_EDGE_COUNT:
      {
         // the cam non critical edge count
         value = mcd5411_sdm->F.Ncrit_Ecnt_And_Flag.F.Ncrit_Ecnt;
      }
      break;

   case CAM_SENSOR_PARAMETER_NON_CRITICAL_EDGE_TIME:
      {
         // The cam non critical edge time
         value = mcd5411_sdm->F.Ncrit_ET_And_Flag.F.NCrit_ET;
      }
      break;

   case CAM_SENSOR_PARAMETER_NOISE_COUNT:
      {
         // the noise count
         value = mcd5411_sdm->F.Period_And_Noise_Cnt.F.Noise_Cnt;
      }
      break;

   case CAM_SENSOR_PARAMETER_PERIOD:
      {
         // The period between the last two critical cam
         value = mcd5411_sdm->F.Period_And_Noise_Cnt.F.Period;
      }
      break;

   case CAM_SENSOR_PARAMETER_NON_CRITICAL_ANGLE_BUFFERED:
      {
         //Buffered value of NCrit_TCR2 so as to be coherent with other critical edge data
         value = mcd5411_sdm->F.Buff_NCrit_TCR2.F.Buff_NCrit_TCR2;
      }
      break;

   case CAM_SENSOR_PARAMETER_NON_CRITICAL_ANGLE:
      {
         //A snapshot of the TCR2 taken at the non-critical cam edge
         value = mcd5411_sdm->F.NCrit_TCR2_And_Flag.F.NCrit_TCR2;
      }
      break;

   default:
      {
         // do nothing
         value = 0;
      }
      break;
   }

   return value;
}

//=============================================================================
// MCD5411_Set_Flag
//=============================================================================
void MCD5411_Set_Flag(
             TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Flag_T    in_flag,
   bool                 in_value )
{
   MCD5411_SDM_T  *mcd5411_sdm = (MCD5411_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);

   switch ( in_flag )
   {
   case CAM_SENSOR_FLAG_ENABLE_INTERRUPT_ON_CRITICAL_EDGE:
      {
         mcd5411_sdm->F.Ncrit_ET_And_Flag.F.Crit_IRQ_En = in_value;
      }
      break;

   case CAM_SENSOR_FLAG_ENABLE_INTERRUPT_ON_NON_CRITICAL_EDGE:
      {
         mcd5411_sdm->F.Ncrit_ET_And_Flag.F.NCrit_IRQ_En = in_value;
      }
      break;

   case CAM_SENSOR_FLAG_ENABLE_REPLICATED_CAM_OUTPUT:
      {
         mcd5411_sdm->F.Ncrit_ET_And_Flag.F.Rep_Out_En = in_value;

         if( MCD5411_CAME_REPLICATE_ENABLE == in_value )
         {
            CAME_GLOBAL_RAM(index).F.Rep_Out_Info.F.Rep_Out_Chan_Num = MCD5411_Rep_Channel_Num;
         }
      }
      break;

   default:
      {
         // do nothing
      }
      break;
   }
}

//=============================================================================
// MCD5411_Get_Flag
//=============================================================================
bool MCD5411_Get_Flag(
                TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Flag_T    in_flag )
{
   MCD5411_SDM_T *mcd5411_sdm = (MCD5411_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);
   bool           value;
   switch ( in_flag )
   {
   case CAM_SENSOR_FLAG_ENABLE_INTERRUPT_ON_CRITICAL_EDGE:
      {
         value = (bool)mcd5411_sdm->F.Ncrit_ET_And_Flag.F.Crit_IRQ_En;
      }
      break;

   case CAM_SENSOR_FLAG_ENABLE_INTERRUPT_ON_NON_CRITICAL_EDGE:
      {
         value = (bool)mcd5411_sdm->F.Ncrit_ET_And_Flag.F.NCrit_IRQ_En;
      }
      break;

   case CAM_SENSOR_FLAG_ENABLE_REPLICATED_CAM_OUTPUT:
      {
         value = (bool)mcd5411_sdm->F.Ncrit_ET_And_Flag.F.Rep_Out_En;
      }
      break;

   case CAM_SENSOR_FLAG_STATUS_LAST_EDGE_WAS_CRITICAL:
      {
         value = (bool)mcd5411_sdm->F.Prev_Crit_ET_And_Flags.F.Last_Edge_Crit;
      }
      break;

   case CAM_SENSOR_FLAG_STATUS_TIMEOUT:
      {
         value = (bool)mcd5411_sdm->F.Prev_Crit_ET_And_Flags.F.Timeout;
      }
      break;

   default:
      {
         // do nothing
         value = false;
      }
      break;
   }

   return value;
}

//=============================================================================
// MCD5411_Get_Angle_Clock_Data
//=============================================================================
void MCD5411_Get_Angle_Clock_Data(
                TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   uint32_t            *out_current_angle,
   uint32_t            *out_previous_angle )
{
   uint32_t coherent_1;
   uint32_t coherent_2;
   MCD5411_SDM_T  *mcd5411_sdm = (MCD5411_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index, configure);

   do
   {
      coherent_1 = mcd5411_sdm->F.Buff_NCrit_ET_And_Flag.U32 &
         MCD5411_COHERENCY_BIT_MASK;

      *out_current_angle = mcd5411_sdm->F.Crit_TCR2.F.Crit_TCR2;
      *out_previous_angle = mcd5411_sdm->F.Prev_Crit_TCR2.F.Crit_TCR2;

      coherent_2 = mcd5411_sdm->F.Prev_Crit_ET_And_Flags.U32 &
         MCD5411_COHERENCY_BIT_MASK;

   } while( coherent_1 != coherent_2 );

}

//=============================================================================
// MCD5411_Get_Coherent_Angle_With_History
//=============================================================================
void MCD5411_Get_Coherent_Angle_With_History(
                  TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure ,
   Cam_Sensor_Coherent_T   *out_angle_data )
{
   MCD5411_Prev_Crit_ET_And_Flags_T      coherent_2_prev_crit_et;
   MCD5411_Ncrit_Ecnt_And_Flag_T         coherent_2_ncrit_ecnt;
   MCD5411_Crit_ET_T                     came_crit_et;
   MCD5411_Crank_Cnt_T                   came_crank_count_at_critical_edge;
   MCD5411_Crank_Cnt_T                   came_crank_count_at_non_critical_edge_buffered;
   MCD5411_Crank_Cnt_T                   came_crank_count_at_last_non_critical_edge;
   MCD5411_Buff_NCrit_ET_And_Flag_T      coherent_1_buff_ncrit_et;
   MCD5411_NCrit_TCR2_And_Flag_T         coherent_1_ncrit_tcr2;

   MCD5411_SDM_T  *mcd5411_sdm = (MCD5411_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index, configure);

   do
   {
      coherent_1_buff_ncrit_et.U32 = mcd5411_sdm->F.Buff_NCrit_ET_And_Flag.U32;
      came_crank_count_at_critical_edge.U32 = mcd5411_sdm->F.Crank_Cnt.U32;
      came_crank_count_at_non_critical_edge_buffered.U32 = mcd5411_sdm->F.Buff_NCrit_Crank_Cnt.U32;
      came_crit_et.U32 = mcd5411_sdm->F.Crit_ET.U32;
      coherent_2_prev_crit_et.U32 = mcd5411_sdm->F.Prev_Crit_ET_And_Flags.U32;

   }while(coherent_1_buff_ncrit_et.F.Coherent_1 != coherent_2_prev_crit_et.F.Coherent_2);

   do
   {
      coherent_1_ncrit_tcr2.U32 = mcd5411_sdm->F.NCrit_TCR2_And_Flag.U32;
      came_crank_count_at_last_non_critical_edge.U32 = mcd5411_sdm->F.NCrit_Crank_Cnt.U32;
      coherent_2_ncrit_ecnt.U32 = mcd5411_sdm->F.Ncrit_Ecnt_And_Flag.U32;

   }while(coherent_1_ncrit_tcr2.F.Coherent_1 != coherent_2_ncrit_ecnt.F.Coherent_2);

   out_angle_data->current_crank_count_at_critical_edge                 = (uint16_t)came_crank_count_at_critical_edge.F.Crank_Count;
   out_angle_data->previous_crank_count_at_critical_edge                = (uint16_t)came_crank_count_at_critical_edge.F.Prev_Crank_Count;
   out_angle_data->current_crank_count_at_non_critical_edge_buffered    = (uint16_t)came_crank_count_at_non_critical_edge_buffered.F.Crank_Count;
   out_angle_data->previous_crank_count_at_non_critical_edge_buffered   = (uint16_t)came_crank_count_at_non_critical_edge_buffered.F.Prev_Crank_Count;
   out_angle_data->current_crank_count_at_last_non_critical_edge        = (uint16_t)came_crank_count_at_last_non_critical_edge.F.Crank_Count;
   out_angle_data->previous_crank_count_at_last_non_critical_edge       = (uint16_t)came_crank_count_at_last_non_critical_edge.F.Prev_Crank_Count;
   out_angle_data->current_critical_time  = came_crit_et.F.Crit_ET;
   out_angle_data->previous_critical_time = coherent_2_prev_crit_et.F.Prev_Crit_ET;
}

//=============================================================================
// MCD5411_Set_Host_Interrupt_Enable
//=============================================================================
void  MCD5411_Set_Host_Interrupt_Enable(
                   TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure ,
   bool                 in_state )
{

   TPU_Channel_T channel= configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CIE = in_state;

}

//=============================================================================
// MCD5411_Get_Host_Interrupt_Enable
//=============================================================================
bool MCD5411_Get_Host_Interrupt_Enable(
                      TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure  )
{
   TPU_Channel_T channel= configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   return ((bool)p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CIE);
}

//=============================================================================
// MCD5411_Set_Host_Interrupt_Status
//=============================================================================
void MCD5411_Set_Host_Interrupt_Status(
                      TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure ,
   bool                 in_status )
{
   TPU_Channel_T channel= configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   if ( true == in_status )
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
// MCD5411_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5411_Get_Host_Interrupt_Status(
                        TPU_Index_T index,
                     TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure  )
{
   TPU_Channel_T channel= configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   bool status;

   status =   (bool)((p_tpu->CISR[index].U32 & (uint32_t)(1 << channel))>>channel);

   return (status);
}
