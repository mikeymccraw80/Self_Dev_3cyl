#ifndef DD_STM_H
#define DD_STM_H

#include "hw_stm.h"

//=============================================================================
// STM
//=============================================================================
#define SECTION_STM_REGISTER
#include "section.h"
extern STM_T  STM;
#define SECTION_END
#include "section.h"


// @enum STM_Freeze_T | STM Freeze type
typedef enum STM_Freeze_Tag
{
   STM_FREEZE_DISABLE ,         //@emem Disable Freeze
   STM_FREEZE_ENABLE            //@emem Enable Freeze

}  STM_Freeze_T;

// @enum STM_Channel_Index_T 
typedef enum STM_Channel_Index_Tag
{
   STM_CHANNEL_0 ,       //@emem Select Channel0.
   STM_CHANNEL_1 ,       //@emem Select Channel1.
   STM_CHANNEL_2 ,       //@emem Select Channel2.
   STM_CHANNEL_3 ,       //@emem Select Channel3 
   STM_CHANNEL_MAX      //@emem Select Channel_MAX 

}  STM_Channel_Index_T;

//external function

extern void STM_INTERRUPT_Clear_Pending(STM_Channel_Index_T channel );
extern void STM_Timer_Set_Value(STM_Channel_Index_T channel,uint32_t in_time);
#endif // DD_STM_H

