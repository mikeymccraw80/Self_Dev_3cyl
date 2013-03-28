
//=============================================================================
//                                Includes
//=============================================================================
#include "dd_pit.h"

//=============================================================================
// Register overlay of the submodule
//=============================================================================

PIT_T  PIT;

//=============================================================================
// PIT_Initialize_Device
//=============================================================================
void PIT_Initialize_Device(void)
{
   PIT_Channel_T index ;

   PIT.MCR.F.MDIS_RTI= RTI_ENABLE;
   PIT.MCR.F.MDIS = PIT_ENABLE; 
   for(index = PIT_CHANNEL_RTI; index < PIT_CHANNEL_MAX; index ++)
   {
      PIT.Timer[index].TCTRL.F.TEN= PIT_DISABLE;
      PIT.Timer[index].TCTRL.F.TIE= PIT_TIMER_INTERRUPT_DISABLE;
   }
}


//=============================================================================
// PIT_Timer_Set_Value
//=============================================================================
void PIT_TIMER_Set_Value(
   PIT_Channel_T channel,
   uint32_t  in_time   )
{

   //Disable the timer
   PIT.Timer[channel].TCTRL.F.TEN = false;

   if(channel == PIT_CHANNEL_RTI && in_time < PIT_RTI_MIN_VALUE)    //RTI is the channel selected
   {
    //RTI timer cannot be loaded with less than 32 cycles
      //do noting
   }
   else
   {
      PIT.Timer[channel].LDVA = in_time;
   }
   //Enable the timer
   PIT.Timer[channel].TCTRL.F.TEN = true;
}

//=============================================================================
// PIT_Get_Timer_Value
//=============================================================================
uint32_t PIT_TIMER_Get_Value(
	PIT_Channel_T channel)
{
   uint32_t timer_value;
     timer_value = (PIT.Timer[channel].CVAL);
   return timer_value;
}

//=============================================================================
// PIT_Clear_TImer_Value
//=============================================================================
void PIT_Clear_Timer_Value(
   PIT_Channel_T channel )
{

   PIT.Timer[channel].TCTRL.F.TEN = false;
   PIT.Timer[channel].LDVA = 0;
}

//=============================================================================
// PIT_INTERRUPT_Set_Enable
//=============================================================================
void PIT_INTERRUPT_Set_Enable(
   PIT_Channel_T channel ,
   bool               in_enable )
{
   PIT.Timer[channel].TCTRL.F.TIE = in_enable;
}

//=============================================================================
// PIT_INTERRUPT_Get_Enable
//=============================================================================
bool PIT_INTERRUPT_Get_Enable(
   PIT_Channel_T channel )
{   
   bool enable =  (bool)(PIT.Timer[channel].TCTRL.F.TIE) ;
   return enable;
}

//=============================================================================
// PIT_INTERRUPT_Get_Status
//=============================================================================
bool PIT_INTERRUPT_Get_Status(
   PIT_Channel_T channel)
{

   bool status = (bool)(PIT.Timer[channel].TFLG.F.TIF) ;

   return status;
}

//=============================================================================
// PIT_INTERRUPT_Clear_Pending
//=============================================================================
void PIT_INTERRUPT_Clear_Pending(
   PIT_Channel_T channel )
{

   PIT.Timer[channel].TFLG.F.TIF = true;
}



