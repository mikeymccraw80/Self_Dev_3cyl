//=============================================================================
// include files
//=============================================================================
#include "dd_stm.h"
#include "io_config_stm.h"

//=============================================================================
// define
//=============================================================================
#define SECTION_STM_REGISTER
#include "section.h"
 STM_T  STM;
#define SECTION_END
#include "section.h"
#define STM_CHANNEL_ENABLE_MASK (0x00000001)
#define STM_INTERRUPT_MASK (0x00000001)
//=============================================================================
// STM_Initialize_Device
//=============================================================================
void STM_Initialize_Device(void)
{
   STM.CR.U32 = STM_CR_INITIAL.U32;
}

//=============================================================================
// STM_Set_Timer_Enable
//=============================================================================
void STM_Set_Timer_Enable(
   bool in_enable)
{
   STM_CR_T cr;

   cr.U32     = STM.CR.U32;
   cr.F.TEN  = in_enable;
   STM.CR.U32 = cr.U32;
}


//=============================================================================
// STM_Set_Channel_Enable
//=============================================================================
void STM_Set_Channel_Enable( 
      STM_Channel_Index_T channel,
      bool in_enable)
{
   STM_CCRn_T             ccr;

   ccr.U32   = STM.Timer[channel].CCR.U32;
   ccr.F.CEN = in_enable;

   STM.Timer[channel].CCR.U32 = ccr.U32;
}

//=============================================================================
// STM_Get_Channel_Enable
//=============================================================================
bool STM_Get_Channel_Enable( 
      STM_Channel_Index_T channel)
{
   bool                enable;

   enable = (bool) (STM.Timer[channel].CCR.U32 & STM_CHANNEL_ENABLE_MASK);

   return (enable);
}


//=============================================================================
// STM_Timer_Set_Value
//=============================================================================
void STM_Timer_Set_Value(
    STM_Channel_Index_T channel,
     uint32_t  in_time  )
{
   uint32_t              time;

   time = STM.CNT;

   // Disable the timer before setting compare value
   STM_Set_Timer_Enable(false);
   STM.Timer[channel].CMP = time + in_time;

   STM_Set_Channel_Enable(channel,true);

   // Enable the Timer now
   STM_Set_Timer_Enable(true);
}

//=============================================================================
// STM_TIMER_Get_Base_Frequency
//=============================================================================
uint32_t STM_TIMER_Get_Base_Frequency(void )
{

   return STM_CLOCK_FREQUENCY_HZ;
}


//============================================================================
// STM_INTERRUPT_Get_Status
//=============================================================================
bool STM_INTERRUPT_Get_Status(
   STM_Channel_Index_T channel )
{

   bool status = (bool)(STM.Timer[channel].CIR.U32 & STM_INTERRUPT_MASK) ;
   return status;
}

//=============================================================================
// STM_INTERRUPT_Clear
//=============================================================================
void STM_INTERRUPT_Clear_Pending(
   STM_Channel_Index_T channel )
{
 
   STM.Timer[channel].CIR.U32  = STM_INTERRUPT_MASK;
}