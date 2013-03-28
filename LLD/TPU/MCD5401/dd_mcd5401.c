
#include "dd_mcd5401.h"

//===========================================================================
// MCD5401_Initialize_Channel                                                
//===========================================================================
void MCD5401_Initialize_Channel   (
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure )
{
   uint32_t interrupt_status = Enter_Critical_Section( );
   TPU_Channel_T channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   TPU_Initialize_Channel(index,configure );
   TPU_Set_Static_Base_Address(index,configure );
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM0 = 
   	 configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0;
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 = 
       configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE1;
   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.ETCS = 
      FIE_ENTRYTABLE_TYPE;

   //TPU Channel HSR
   switch(configure.F.TPU_CHANNEL_CONFIGURATION_HSR)
   {
      case EDGE_RISING:
         TPU_Set_HSR(index,configure, MCD5401_HSR_INIT_RISING_EDGE);
         break;
      case EDGE_FALLING:
         TPU_Set_HSR(index,configure, MCD5401_HSR_INIT_FALLING_EDGE);
         break;
      case EDGE_BOTH:
         TPU_Set_HSR(index,configure, MCD5401_HSR_INIT_BOTH_EDGE);
         break;
      default:
         break;
   }
   TPU_Channel_Enable(index,configure ); 
   //Wait for HSR is complete
   TPU_Wait_HSR_Request_Complete(index,configure );
   //Set channel priority CPR

   Leave_Critical_Section( interrupt_status );
}

//=============================================================================
// MCD5401_Channel_Shutdown
//=============================================================================
void MCD5401_Channel_Shutdown(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   TPU_Set_HSR(index, configure, MCD5401_HSR_SHUTDOWN );

   //Wait until the channel not active 

   TPU_Wait_HSR_Request_Complete(index,configure );
   TPU_Channel_Disable(index,configure );
}


//=============================================================================
// MCD5401_Get_Edge_Time
//=============================================================================
uint32_t MCD5401_Get_Edge_Time(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5401_SDM_T  *mcd5401_sdm = (MCD5401_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index,configure );
   return (mcd5401_sdm->F.Edge_Time.F.Edge_Time);
}

//=============================================================================
// MCD5401_Get_Edge_Count
//=============================================================================
uint32_t MCD5401_Get_Edge_Count(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5401_SDM_T  *mcd5401_sdm = (MCD5401_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index,configure );
   return (mcd5401_sdm->F.Edge_Count.F.Edge_Cnt);
}

//=============================================================================
// MCD5401_Get_Event_Time
//=============================================================================
uint32_t MCD5401_Get_Event_Time(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5401_SDM_T  *mcd5401_sdm = (MCD5401_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index,configure );
   return(mcd5401_sdm->F.Actual_Event_Time.F.Actual_Event_Time);
}

//=============================================================================
// MCD5401_Set_Requested_Event
//=============================================================================
void MCD5401_Set_Requested_Event(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t             in_requested_event)
{
   MCD5401_SDM_T  *mcd5401_sdm = (MCD5401_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index,configure );
   mcd5401_sdm->F.Requested_Time.F.Requested_Time = in_requested_event;
   TPU_Set_HSR(index,configure ,MCD5401_HSR_REQUEST_EVENT_TIME);
}

//=============================================================================
// MCD5401_Update_Requested_Event
//=============================================================================
void MCD5401_Update_Requested_Event(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t                in_requested_event)
{
   MCD5401_SDM_T  *mcd5401_sdm = (MCD5401_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index,configure );
   mcd5401_sdm->F.Requested_Time.F.Requested_Time = in_requested_event;
   TPU_Set_HSR(index,configure ,MCD5401_HSR_UPDATE_EVENT_TIME);
}

//=============================================================================
// MCD5401_Get_Requested_Event
//=============================================================================
uint32_t MCD5401_Get_Requested_Event(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure )
{
   MCD5401_SDM_T  *mcd5401_sdm = (MCD5401_SDM_T *)TPU_Get_Channel_SDM_Start_Address(index,configure );
   return(mcd5401_sdm->F.Requested_Time.F.Requested_Time);
}




