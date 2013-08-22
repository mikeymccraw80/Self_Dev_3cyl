
//=============================================================================
// include files
//=============================================================================
#include "io_config_stm.h"
#include "dd_stm_interface.h"
#include "dd_stm.h"
#include "dd_siu.h"


//=============================================================================
// STM_CR_INITIAL
//=============================================================================

const STM_CR_T STM_CR_INITIAL = 
{
   STM_CLOCK_PRESCALER, // Counter Prescaler.
   STM_FREEZE_DISABLE,  //freeze
   false                            //Timer Counter Enabled.
};
//#ifdef 0
void IO_STM0_20ms_INT(void)
{

	STM_INTERRUPT_Clear_Pending(STM_CHANNEL_0);

	SIU.GPDO[129].F.PDO =!SIU.GPDO[129].F.PDO;

	STM_Timer_Set_Value(STM_CHANNEL_0,1000*20);
}
//#endif
