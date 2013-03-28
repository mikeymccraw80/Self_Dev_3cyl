#ifndef DD_MCD5401_INTERFACE_H
#define DD_MCD5401_INTERFACE_H


//===========================================================================
// inlucde files                                                
//===========================================================================
#include "dd_mcd5401.h"


//===========================================================================
// MCD5401_Initialize_Channel                                                
//===========================================================================
void MCD5401_Initialize_Channel   (
    TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure );
//=============================================================================
// MCD5401_Channel_Shutdown
//=============================================================================
void MCD5401_Channel_Shutdown(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5401_Get_Edge_Time
//=============================================================================
uint32_t MCD5401_Get_Edge_Time(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );
//=============================================================================
// MCD5401_Get_Edge_Count
//=============================================================================
uint32_t MCD5401_Get_Edge_Count(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5401_Get_Event_Time
//=============================================================================
uint32_t MCD5401_Get_Event_Time(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// MCD5401_Set_Requested_Event
//=============================================================================
void MCD5401_Set_Requested_Event(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t             in_requested_event);

//=============================================================================
// MCD5401_Update_Requested_Event
//=============================================================================
void MCD5401_Update_Requested_Event(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint32_t                in_requested_event);

//=============================================================================
// MCD5401_Get_Requested_Event
//=============================================================================
uint32_t MCD5401_Get_Requested_Event(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure );

#endif // DD_MCD5401_INTERFACE_H 
