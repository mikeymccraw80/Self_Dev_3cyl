
//
// other includes
//

#include "dd_swt_interface.h"
#include "os_main.h"
#include "io_init.h"
#include "io_config_swt.h"
#include "dd_siu_interface.h"


//=============================================================================
// exit
//
// Implementation Characteristics:
//
//
//=============================================================================
 void exit(void)
{
   // Set the watchdog timeout to 300ms for flash erase/program
   SWT_Set_Timeout_Value(SWT_TIMEOUT_VALUE_INIT) ;
   SWT_Service_WatchDog();


   EEPROM_Backup_MFG_NVM_Block( true );
   EEPROM_Backup_Vehicle_NVRAM_Block();

   // only LCI will do the instrumentation operation
   if(CPU_LCI == CPU_Info)
   {
      // backup cal 
      INST_Backup_Working_Page();
   }


   //Set TOD low now since all power down processing is complete
  // IO_DISCRETE_Set_Immediate_State(&MTSA_C2PS_CONFIG_TURN_OFF_INHIBIT_CONTROL, false );
    INTC_EXCEPTION_Halt();
   // Wait in an infinite loop for the power supply to shutdown
   do {} while (true);

}



