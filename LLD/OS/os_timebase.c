
//=============================================================================
// include files
//=============================================================================
#include "dd_pit_interface.h"
#include "os_type.h"

//=============================================================================
// local variables
//=============================================================================
static uint16_t OS_RTI_1ms_Count;
RtiFlagsType RTI_Flags;



//=============================================================================
// local functions
//=============================================================================
 void OS_TimeBasedTask1ms(void) ;
 void OS_TimeBasedTask2ms(void) ;
 void OS_TimeBasedTask5ms(void) ;
 void OS_TimeBasedTask10ms(void);



//=============================================================================
// OS_TimeBaseLoopControl
//=============================================================================
 void OS_TimeBaseLoopControl( uint8_t loop)
{

 RTI_Flags.bf.TimeFor1ms = 1;
 OS_TimeBasedTask1ms();


 switch (loop)
   {
      case 2:
	     RTI_Flags.bf.TimeFor2ms = 1;
            OS_TimeBasedTask2ms();	
            break;
      case 5:
	     RTI_Flags.bf.TimeFor5ms = 1;
            OS_TimeBasedTask5ms();	
            break;
   
      case 10:
	     RTI_Flags.bf.TimeFor5ms = 1;
	     OS_TimeBasedTask5ms();
	     RTI_Flags.bf.TimeFor10ms = 1;
	     OS_TimeBasedTask10ms();
            break;
       default:
            break;
   }
}


//=============================================================================
// OS_RTI_1ms_INT
//=============================================================================
void OS_RTI_1ms_INT(void)
{
     PIT_INTERRUPT_Clear_Pending(PIT_CHANNEL_RTI);

      OS_RTI_1ms_Count++;
      if( OS_RTI_1ms_Count > 10)
      {
         OS_RTI_1ms_Count = 1;
      }
   
     OS_TimeBaseLoopControl(OS_RTI_1ms_Count);

}

