#ifndef DD_TPU_INTERFACE_H
#define DD_TPU_INTERFACE_H

#include "dd_tpu.h"


//=============================================================================
// TPU_Initialize_Channel
//=============================================================================
void TPU_Initialize_Channel(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);


//=============================================================================
// TPU_Channel_Enable
//=============================================================================
void TPU_Channel_Enable(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);


//=============================================================================
// TPU_Channel_Disable
//=============================================================================
void TPU_Channel_Disable(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// TPU_Get_Channel_Status
//=============================================================================
bool TPU_Get_Channel_Status(
      TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// TPU_INTERRUPT_Clear
//=============================================================================
void TPU_INTERRUPT_Clear(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// TPU_INTERRUPT_Set_Status
//=============================================================================
void TPU_INTERRUPT_Set_Enable(
  TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure,
   bool                 in_enable );

//=============================================================================
// TPU_INTERRUPT_Get_Enable
//=============================================================================
bool TPU_INTERRUPT_Get_Enable(
  TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// TPU_INTERRUPT_Clear_Pending
//=============================================================================
void TPU_INTERRUPT_Clear_Pending(
    TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// TPU_TIMER_Get_State
//=============================================================================
Timer_State_T TPU_TIMER_Get_State(
     TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// TPU_TIMER_Get_Base_Frequency
//=============================================================================
uint32_t TPU_TIMER_Get_Base_Frequency(
   TPU_Index_T index ,
   TPU_CHANNEL_Configuration_T   configure );

//=============================================================================
// TPU_TIMER_Get_Size
//=============================================================================
Timer_Size_T TPU_TIMER_Get_Size(void );
//=============================================================================
// TPU_TIMER_Get_Value_Channel
//=============================================================================
uint32_t TPU_TIMER_Get_Value_Channel(
      TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure);
//=============================================================================
// TPU_TIMER_Get_Value
//=============================================================================
uint32_t TPU_TIMER_Get_Value(
      TPU_Index_T index,
       TPU_Time_Base_T   tcr_type);


#endif // DD_TPU_INTERFACE_H
