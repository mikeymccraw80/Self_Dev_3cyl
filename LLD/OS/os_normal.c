
//=============================================================================
// include files
//=============================================================================
#include "dd_swt_interface.h"
#include "io_config_swt.h"
#include "os_type.h"

//=============================================================================
//  define
//=============================================================================
#define CSA_FILL_PATTERN 0xAA55AA55
#define USTACK_FILL_PATTERN 0xB1B1

#define APP_CAL_PRESENCE_PATTERN                       (0x6A6A)


#define Cw_SOFTWARE_LEVEL       0x03
#define Cw_REVISION_LEVEL       0x00
#define Cw_CalFORM_ID           ( ( (0xff & Cw_SOFTWARE_LEVEL) << 8) + (0xff & Cw_REVISION_LEVEL) )

#pragma section SECTION_PF_KKSUM address=0x00160000
#pragma use_section SECTION_PF_KKSUM PF_KKSUM
const uint16_t PF_KKSUM = 0x6D27;
#pragma section

#pragma section SECTION_APP_PRESENCE_PATTERN address=0x0017FFFE
#pragma use_section SECTION_APP_PRESENCE_PATTERN APP_PRESENCE_PATTERN
const uint16_t APP_PRESENCE_PATTERN = APP_CAL_PRESENCE_PATTERN;
#pragma section

#pragma section SECTION_CAL_PRESENCE_PATTERN address=0x0003FFFE;
#pragma use_section SECTION_CAL_PRESENCE_PATTERN CAL_PRESENCE_PATTERN
const uint16_t CAL_PRESENCE_PATTERN = APP_CAL_PRESENCE_PATTERN;
#pragma section

#pragma section SECTION_CALID_INAPP address=0x0017FFFC
#pragma use_section SECTION_CALID_INAPP CAL_FORMID_INAPP
const uint16_t CAL_FORMID_INAPP  = Cw_CalFORM_ID;
#pragma section

#pragma section SECTION_CALID_INCAL address=0x0003FFFC
#pragma use_section SECTION_CALID_INCAL CAL_FORMID_INCAL
const uint16_t CAL_FORMID_INCAL = Cw_CalFORM_ID;
#pragma section

//=============================================================================
// function define
//=============================================================================
 void OS_Startup_Hook(void);
 void MngOSTK_1msTasks(void);
 void MngOSTK_5msTasks(void);
 void MngOSTK_10msTasks(void);
  void MngOSTK_100msTasks(void);
 void OS_Free_Time_Tasks_Hook(void);


uint8_t  Normal_10ms_CNT;
//=============================================================================
// StartupHook
//=============================================================================
//start up before HWIO init last excute
void StartupHook(void)
{

}



//=============================================================================
// StartOS_Task_Normal
//=============================================================================
void StartOS_Task_Normal(void)
{

   OS_Startup_Hook();
   /* turn on interrupts */
   Enable_Interrupts();

   // Set watchdog timeout to 62ms during normal operation
   SWT_Set_Timeout_Value(SWT_TIMEOUT_VALUE_NORMAL) ;
   SWT_Service_WatchDog();

   /* do until application indicates shutdown */
  // while( !OS_Get_Shutdown_Active() )
  while( 1)
   {

      if (1 == RTI_Flags.bf.TimeFor1ms)
      	{
     	    MngOSTK_1msTasks();
	    RTI_Flags.bf.TimeFor1ms = 0x00;
      	}
      else if(1 == RTI_Flags.bf.TimeFor5ms)
      {
      
         MngOSTK_5msTasks();
	   RTI_Flags.bf.TimeFor5ms = 0x00;
      }
       else if (1 == RTI_Flags.bf.TimeFor10ms)
      {


         MngOSTK_10msTasks();
	  RTI_Flags.bf.TimeFor10ms = 0x00;
	  Normal_10ms_CNT++;

      }
     else
     {
         if(10 == Normal_10ms_CNT)
	  {
	   MngOSTK_100msTasks();
	   Normal_10ms_CNT = 0;
	  }
       OS_Free_Time_Tasks_Hook();
     }	 
   }

   //Turn off power supply and return to OSEK
   /* disable interrupts */
   Disable_Interrupts();

   // Set watchdog timeout to 62ms during normal operation
    SWT_Set_Timeout_Value(SWT_TIMEOUT_VALUE_INIT) ;
    SWT_Service_WatchDog();

   //OS_Powerdown_Callback();
  
}


