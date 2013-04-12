#ifndef DD_FLASH_HWINFO_H
#define DD_FLASH_HWINFO_H

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "reuse.h"
#include "dd_siu_hwinfo.h"
#include "dd_flash_memory_interface.h"
#include "dd_flash_interface.h"

//===========================================================================
//  Exported Object Declarations
//===========================================================================

//===========================================================================
// Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================
// load current flash driver - this must be called before the using of any flash driver
INLINE FLASH_MODULE_T Get_FLASH_Driver_Mode(void)
{
   FLASH_MODULE_T current_flash;
   if((CPU_PROD == CPU_Info)||(CPU_VERTICAL == CPU_Info))
   {
      current_flash = C90LC_Module;
   }
   else
   {
      current_flash = C90FL_Module;
   }

   if(current_flash < FLASH_Module_Number)
   {
      flash_memory_interface = &FLASH_Memory_Interface[current_flash];
   }

   return current_flash;
}


#endif

