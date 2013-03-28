
#include "dd_mcd5417.h"
#include "io_config_tpu.h"

   volatile MCD5417_SDM_T  *mcd5417_sdm_vis[4]; 
volatile DESFIE_GLOBAL_RAM_T *DESFIE_GLOBAL_RAM_vis;
//=============================================================================
// MCD5417_Initialize_Channel
//=========================================================================
void MCD5417_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)

{

   TPU_Channel_T channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   uint32_t polarity = (uint32_t)((configure.F.TPU_CHANNEL_CONFIGURATION_POLARITY== ACTIVE_LOW) ? 0 : 1);
   uint32_t critical_status;

   critical_status = Enter_Critical_Section();
   // Supress interrupts
    mcd5417_sdm_vis[channel-TPU_CHANNEL_19] = (volatile MCD5417_SDM_T *)TPU_INITIAL_SDM_ADDRESS[0][channel];
   DESFIE_GLOBAL_RAM_vis = ( volatile DESFIE_GLOBAL_RAM_T *) DESFIE_GLOBAL_ADDRESS(index);
   
   // Engine data is shared to EPPWMT premitive
   ENGINE_GLOBAL_RAM(index).F.pDESFIE_Engine_Data.F.pDESFIE = (uint32_t)
      ((uint32_t)&DESFIE_GLOBAL_RAM(index).F.Edge_Time.F -
      TPU_Get_SDM_Base_Address(index) );
   //TPU Channel init
   TPU_Initialize_Channel(index, configure);
   TPU_Set_Static_Base_Address(index, configure);
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM0 =
     configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0;
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 =
      polarity;//(uint8_t)parameteres->OutPut_Signal_Polarity;
      
   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.ETCS =
      DESFIE_ENTRYTABLE_TYPE;

   //TPU Channel HSR
   TPU_Set_HSR( index, configure, MCD5417_HSR_INITIALIZE );
   TPU_Channel_Enable(index, configure);
   //Wait for HSR is complete
   TPU_Wait_HSR_Request_Complete(index, configure);
   //Set channel priority CPR
   Leave_Critical_Section( critical_status );
}

//=============================================================================
// MCD5417_Update_Boundary
//=============================================================================
void MCD5417_Update_Boundary(
      TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure,
   uint32_t           in_dfpw,
   uint32_t           in_boundary_angle,
   uint32_t           in_normal_offset,
   uint32_t           in_trim_offset )
{

   MCD5417_SDM_T  *mcd5417_sdm =
      (MCD5417_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t interrupt_status = Enter_Critical_Section( );

   // Set the DFPW value
   DESFIE_DFPW = in_dfpw;
   mcd5417_sdm->F.Fuel_Flag_DFPW.F.DFPW = in_dfpw;

   // Set the Boundary value
   DESFIE_Boundary_Angle = in_boundary_angle;
   mcd5417_sdm->F.Boundary_Angle.F.Boundary_Angle = in_boundary_angle;

   // Set the DESFI_Norm_OS value
   DESFIE_Normal_Offset = in_normal_offset;
   DESFIE_GLOBAL_RAM(index).F.Normal_Offset.F.Normal_Offset = in_normal_offset;

   // Set the DESFI_Trim_OS value
   DESFIE_Trim_Offset = in_trim_offset;
   DESFIE_GLOBAL_RAM(index).F.Trim_Offset.F.Trim_Offset= in_trim_offset;

   // Call MCD4455_Boundary_HSR to issue the HSR
   TPU_Set_HSR( index, configure, MCD5417_HSR_BOUNDARY );
   Leave_Critical_Section( interrupt_status );
}

//=============================================================================
// MCD5417_Update_Channel
//=============================================================================
void MCD5417_Update_Channel(
      TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure,
   uint32_t      in_dfpw,
   uint32_t      in_boundary,
   uint32_t      in_normal_offset,
   uint32_t      in_trim_offset )
{

   MCD5417_SDM_T  *mcd5417_sdm =
      (MCD5417_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index, configure);
   uint32_t interrupt_status = Enter_Critical_Section( );

   // Set the DFPW value
   DESFIE_DFPW = in_dfpw;
   mcd5417_sdm->F.Fuel_Flag_DFPW.F.DFPW = in_dfpw;

   // Set the Boundary value
   DESFIE_Boundary_Angle = in_boundary;
   mcd5417_sdm->F.Boundary_Angle.F.Boundary_Angle = in_boundary;

   // Set the DESFI_Norm_OS value
   DESFIE_Normal_Offset = in_normal_offset;
   DESFIE_GLOBAL_RAM(index).F.Normal_Offset.F.Normal_Offset = in_normal_offset;

   // Set the DESFI_Trim_OS value
   DESFIE_Trim_Offset = in_trim_offset;
   DESFIE_GLOBAL_RAM(index).F.Trim_Offset.F.Trim_Offset= in_trim_offset;

   // Call MCD4455_Boundary_HSR to issue the HSR
   TPU_Set_HSR( index, configure, MCD5417_HSR_UPDATE );

   Leave_Critical_Section( interrupt_status );
}


//=============================================================================
// MCD5417_Update_Engine_Data
//=============================================================================
void MCD5417_Update_Engine_Data(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure,
   uint32_t            edge_time,
   uint16_t            edge_count,
   uint32_t            period )
{
   uint32_t interrupt_status;

   // Must Entering Critical Section to prevent glitches!
   interrupt_status = Enter_Critical_Section();

   // THE ORDER OF THE FOLLOWING DATA WRITES IS CRITICAL TO PREVENT GLITCHES!
   DESFIE_GLOBAL_RAM(index).F.Edge_Time.F.Edge_Time = edge_time;
   DESFIE_GLOBAL_RAM(index).F.Edge_Count.F.Edge_Count = edge_count;
   DESFIE_GLOBAL_RAM(index).F.Period.F.Period = period;
   // THE ORDER OF THE PRECEDING DATA WRITES IS CRITICAL TO PREVENT GLITCHES!

   // All channels must be updated to prevent glitches.
   TPU_Set_HSR( index, configure, DESFIE_HSR_UPDATE );

   // Leaving Critical Section
   Leave_Critical_Section( interrupt_status );

}

//=============================================================================
// MCD5417_Set_Engine_Data
//=============================================================================
void MCD5417_Set_Engine_Data(
         TPU_Index_T index,
   uint32_t            edge_time,
   uint16_t            edge_count,
   uint32_t            period )
{
   // THE ORDER OF THE FOLLOWING DATA WRITES IS CRITICAL TO PREVENT GLITCHES!
   DESFIE_GLOBAL_RAM(index).F.Edge_Time.F.Edge_Time = edge_time;
   DESFIE_GLOBAL_RAM(index).F.Edge_Count.F.Edge_Count = edge_count;
   DESFIE_GLOBAL_RAM(index).F.Period.F.Period = period;
}

//=============================================================================
// MCD5417_Shutdown
//=============================================================================
void MCD5417_Shutdown(
         TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure )
{
   TPU_Set_HSR( index, configure, DESFIE_HSR_SHUTDOWN );
}

//=============================================================================
// MCD5417_Set_Normal_Offset
//=============================================================================
void MCD5417_Set_Normal_Offset(
    TPU_Index_T index,
   uint32_t            normal_offset )
{
   DESFIE_Normal_Offset = normal_offset;
   DESFIE_GLOBAL_RAM(index).F.Normal_Offset.F.Normal_Offset = normal_offset;
}

//=============================================================================
// MCD5417_Get_Normal_Offset
//=============================================================================
uint32_t MCD5417_Get_Normal_Offset(void )
{
   return (DESFIE_Normal_Offset);
}

//=============================================================================
// MCD5417_Set_Trim_Offset
//=============================================================================
void MCD5417_Set_Trim_Offset(
      TPU_Index_T index,
   uint32_t            trim_offset )
{
   DESFIE_Trim_Offset = trim_offset;
   DESFIE_GLOBAL_RAM(index).F.Trim_Offset.F.Trim_Offset = trim_offset;
}

//=============================================================================
// MCD5417_Get_Trim_Offset
//=============================================================================
uint32_t MCD5417_Get_Trim_Offset(void)
{
   return (DESFIE_Trim_Offset);
}

//=============================================================================
// MCD5417_Set_Kinj
//=============================================================================
void MCD5417_Set_Kinj(
         TPU_Index_T index,
   uint32_t            kinj )
{

   DESFIE_Kinj = kinj;
   DESFIE_GLOBAL_RAM(index).F.Kinj.F.Kinj = kinj;
}

//=============================================================================
// MCD5417_Get_Kinj
//=============================================================================
uint32_t MCD5417_Get_Kinj(void )
{
   return (DESFIE_Kinj);
}

//=============================================================================
// MCD5417_Set_Min_Inj_Off
//=============================================================================
void MCD5417_Set_Min_Inj_Off(
    TPU_Index_T index,
   uint32_t            min_inj_off )
{

   DESFIE_Min_Inj_Off = min_inj_off;
   DESFIE_GLOBAL_RAM(index).F.Min_Inj_Off.F.Min_Inj_Off = min_inj_off;
}

//=============================================================================
// MCD5417_Get_Min_Inj_Off
//=============================================================================
uint32_t MCD5417_Get_Min_Inj_Off(void)
{
   return DESFIE_Min_Inj_Off;
}

//=============================================================================
// MCD5417_Set_Min_Trim
//=============================================================================
void MCD5417_Set_Min_Trim(
       TPU_Index_T index,
   uint32_t            min_trim )
{
   DESFIE_Min_Trim = min_trim;
   DESFIE_GLOBAL_RAM(index).F.Min_Trim.F.Min_Trim = min_trim;
}

//=============================================================================
// MCD5417_Get_Min_Trim
//=============================================================================
uint32_t MCD5417_Get_Min_Trim(void)
{
   return (DESFIE_Min_Trim);
}


//=============================================================================
// MCD5417_Set_Multiple_Trim
//=============================================================================
void MCD5417_Set_Multiple_Trim(
      TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t        multiple_trim )
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index, configure);
   DESFIE_Multiple_Trim = ( multiple_trim > 0 ) ? true : false ;
   mcd5417_sdm->F.Fuel_Flag_DFPW.F.Multiple_Trim = multiple_trim;
}


//=============================================================================
// MCD5417_Get_Multiple_Trim
//=============================================================================
uint32_t MCD5417_Get_Multiple_Trim(void)
{
   return DESFIE_Multiple_Trim;
}

//=============================================================================
// MCD5417_Set_DFPW
//=============================================================================
void MCD5417_Set_DFPW(
         TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t            dfpw )
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   DESFIE_DFPW = dfpw;
   mcd5417_sdm->F.Fuel_Flag_DFPW.F.DFPW = dfpw;
}

//=============================================================================
// MCD5417_Get_DFPW
//=============================================================================
uint32_t MCD5417_Get_DFPW(void)
{
   return DESFIE_DFPW;
}

//=============================================================================
// MCD5417_Set_AFPW
//=============================================================================
 void MCD5417_Set_AFPW(
         TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t            in_afpw )
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   mcd5417_sdm->F.AFPW.F.AFPW = in_afpw;
}

//=============================================================================
// MCD5417_Get_AFPW
//=============================================================================
uint32_t MCD5417_Get_AFPW(
          TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure)
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   return (mcd5417_sdm->F.AFPW.F.AFPW);
}

//=============================================================================
// MCD5417_Set_Boundary
//=============================================================================
void MCD5417_Set_Boundary(
           TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure,
   uint32_t            in_boundary_angle )
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   DESFIE_Boundary_Angle = in_boundary_angle;
   mcd5417_sdm->F.Boundary_Angle.F.Boundary_Angle = in_boundary_angle;
}

//=============================================================================
// MCD5417_Get_Boundary
//=============================================================================
uint32_t MCD5417_Get_Boundary(void)
{
   return ( DESFIE_Boundary_Angle );
}

//=============================================================================
// MCD5417_Get_Normal_Pulse_Occurred
//=============================================================================
uint32_t MCD5417_Get_Normal_Pulse_Occurred(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure)
{
   MCD5417_SDM_T  *mcd5417_sdm =(MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   return ((bool)mcd5417_sdm->F.Flags_StartEnd_Time.F.Normal_Done);
}

//=============================================================================
// MCD5417_Get_Trim_Pulse_Occurred
//=============================================================================
uint32_t MCD5417_Get_Trim_Pulse_Occurred(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure)
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   return ((bool)mcd5417_sdm->F.Flags_StartEnd_Time.F.Trim_Done);
}

//=============================================================================
// MCD5417_Get_Kinj_Active
//=============================================================================
uint32_t MCD5417_Get_Kinj_Active(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure)
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   return ((bool)mcd5417_sdm->F.Flags_StartEnd_Time.F.Kinj_Active);
}

//=============================================================================
// MCD5417_Get_Fuel_Active
//=============================================================================
bool MCD5417_Get_Fuel_Active(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure)
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   return ((bool)mcd5417_sdm->F.Flags_StartEnd_Time.F.Fuel_Active);
}

//=============================================================================
// MCD5417_Get_Min_Inj_Off_Active
//=============================================================================
uint32_t MCD5417_Get_Min_Inj_Off_Active(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure)
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   return ((bool)mcd5417_sdm->F.Flags_StartEnd_Time.F.MIO_Active);
}

//=============================================================================
// MCD5417_Get_Start_End_Time
//=============================================================================
uint32_t MCD5417_Get_Start_End_Time(
             TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure)
{
   MCD5417_SDM_T  *mcd5417_sdm = (MCD5417_SDM_T *)
      TPU_Get_Channel_SDM_Start_Address(index,configure );
   return ((uint32_t)mcd5417_sdm->F.Flags_StartEnd_Time.F.Start_End_Time);
}

//=============================================================================
// MCD5417_Set_Enable_Interrupt
//=============================================================================
void  MCD5417_Set_Host_Interrupt_Enable(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool                in_interrupt_enable)
{
   TPU_Channel_T channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CIE = in_interrupt_enable;

}

//=============================================================================
// MCD5417_Get_Interrupt_Enable
//=============================================================================
bool MCD5417_Get_Host_Interrupt_Enable(
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{
   TPU_Channel_T channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   return ((bool)p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CIE);
}

//=============================================================================
// MCD5417_Set_Host_Interrupt_Status
//=============================================================================
void MCD5417_Set_Host_Interrupt_Status(
      TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
   bool                in_state)
{

   TPU_Channel_T channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

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
// MCD5417_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5417_Get_Host_Interrupt_Status(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{
  TPU_Channel_T channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   bool status;

   status =   (bool)((p_tpu->CISR[index].U32 & (uint32_t)(1 << channel))>>channel);

   return (status);
}
