#ifndef DD_PIT_H
#define DD_PIT_H

//=============================================================================
//                                Includes
//=============================================================================
#include "hw_pit.h"

//=============================================================================
// Register overlay of the submodule
//=============================================================================
#define SECTION_PIT_REGISTER
#include "section.h"
extern PIT_T PIT;
#define SECTION_END
#include "section.h"


// @enum PIT_Channel_T 
typedef enum 
{
   PIT_CHANNEL_RTI,
   PIT_CHANNEL_0,
   PIT_CHANNEL_1,
   PIT_CHANNEL_2,
   PIT_CHANNEL_3,
   PIT_CHANNEL_MAX
} PIT_Channel_T;


// @enum PIT_Enable_T 
typedef enum 
{
   PIT_ENABLE,  //@emem PIT Feature Enable
   PIT_DISABLE  //@emem PIT Feature Disable
} PIT_Disable_T;

//=============================================================================
// @enum PIT_Enable_RTI_T 
typedef enum 
{
   RTI_ENABLE,    //@emem PIT- RTI Feature Enable
   RTI_DISABLE    //@emem PIT-RTI Feature Disable
} PIT_Disable_RTI_T;

// @enum PIT_Timer_Interrupt_Enable_T 
typedef enum 
{
   PIT_TIMER_INTERRUPT_DISABLE, //@emem PIT Feature Disable
   PIT_TIMER_INTERRUPT_ENABLE   //@emem PIT Feature Enable
} PIT_Timer_Interrupt_Enable_T;

//=============================================================================
// @enum PIT_Freeze_Timer_T
typedef enum 
{
   PIT_RUN_TIMERS,     //@emem Run timers in debug mode
   PIT_FREEZE_TIMERS   //@emem Freeze timers in debug mode
} PIT_Freeze_Timer_T;




#endif // DD_PIT_H

