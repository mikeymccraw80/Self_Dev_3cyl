
#include "dd_intc.h"

//=============================================================================
// INTC_INTERRUPT_Set_Enable
//=============================================================================
void INTC_INTERRUPT_Set_Enable(
   INTC_Channel_T channel ,
   bool                 in_enable )
{

   if ( channel <= INTC_CHANNEL_SOFTWARE_CH7_CH )
   {
      
       asm(" msync ");
      
       if ( in_enable )
       {
          INTC.SSCIR[channel].F.SET = 1;
       }
       else
       {
          INTC.SSCIR[channel].F.CLR = 1;
       }
      
       asm(" isync ");

   }
   else
   {
       // nothing
   }

}

//=============================================================================
// INTC_INTERRUPT_Get_Enable
//=============================================================================
bool INTC_INTERRUPT_Get_Enable(
   INTC_Channel_T channel  )
{
   bool in_enable=false;
   
   if ( channel <= INTC_CHANNEL_SOFTWARE_CH7_CH )
   {
      
       asm(" msync ");
      
       in_enable = INTC.SSCIR[channel].F.CLR;
      
       asm(" isync ");

   }
   else
   {
       // nothing
   }
   
   return in_enable;
}


//=============================================================================
// INTC_INTERRUPT_Clear_Pending
//=============================================================================
void INTC_INTERRUPT_Clear_Pending(
    INTC_Channel_T channel  )
{

   if ( channel <= INTC_CHANNEL_SOFTWARE_CH7_CH )
   {
      
       asm(" msync ");
      
       INTC.SSCIR[channel].F.CLR = 1;
      
       asm(" isync ");

    }
     else
    {
       // nothing
    }
}

