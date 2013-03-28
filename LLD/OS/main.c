
//
// other includes
//

#include "dd_swt_interface.h"
#include "os_main.h"
#include "io_init.h"
#include "io_config_swt.h"

unsigned int test0; 

extern  void exit(void);
//=============================================================================
// main
//
// Implementation Characteristics:
//
//
//=============================================================================


void main(void)
{
   InitializeHardwareRegisters();
   test0++;
 //  if (!InitializeIllegalConditionCheck()) 
   //{
      StartOS(AM_normal);
   //}
  // else 
   //{
      // barch to testability software and never return
   //   StartOS(AM_ManufacturingTest);
   //}

   exit();
}


