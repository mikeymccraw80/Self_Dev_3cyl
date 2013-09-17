
//=============================================================================
// include files
//=============================================================================
#include "dd_pit_interface.h"
#include "os_type.h"

//=============================================================================
// local variables
//=============================================================================
static uint32_t OS_RTI_1ms_Count;
RtiFlagsType RTI_Flags;

//=============================================================================
// local functions
//=============================================================================
 void OS_TimeBasedTask1ms(void) ;
 void OS_TimeBasedTask2ms(void) ;
 void OS_TimeBasedTask5ms(void) ;
 void OS_TimeBasedTask10ms(void);

//=============================================================================
// OS_RTI_1ms_INT, this the time schedule reference
//=============================================================================
void OS_RTI_1ms_INT(void)
{
	PIT_INTERRUPT_Clear_Pending(PIT_CHANNEL_RTI);

	OS_RTI_1ms_Count = (OS_RTI_1ms_Count >= 10)? 1 : OS_RTI_1ms_Count++;

	/* 1ms task reference */
	RTI_Flags.bf.TimeFor1ms = 1;
	OS_TimeBasedTask1ms();

	/* 2ms task reference */
	if (OS_RTI_1ms_Count & 0x01) {
		RTI_Flags.bf.TimeFor2ms = 1;
		OS_TimeBasedTask2ms();
	}

	/* 5ms task reference */
	if ((OS_RTI_1ms_Count % 5) == 0) {
		RTI_Flags.bf.TimeFor5ms = 1;
		OS_TimeBasedTask5ms();
	}

	/* 10ms task reference */
	if ((OS_RTI_1ms_Count % 10) == 0) {
		RTI_Flags.bf.TimeFor10ms = 1;
		OS_TimeBasedTask10ms();
	}
}

