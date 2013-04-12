#ifndef DD_FLASH_INTERFACE_H
#define DD_FLASH_INTERFACE_H

#include "dd_siu_interface.h"
#include "dd_flash_memory_interface.h"
//===========================================================================
//  Imported Function Prototypes
//===========================================================================
//MCP5634M - Monaco
extern void MPC5634_FLASH_Initialize_Programming(void);
extern void MPC5634_FLASH_Initialize_Normal(void);
//MPC5644A - Andorra
extern void MPC5644_FLASH_Initialize_Programming(void);
extern void MPC5644_FLASH_Initialize_Normal(void);

//===========================================================================
//  Exported Object Declarations
//===========================================================================
extern const FLASH_Memory_Interface_T * flash_memory_interface;

//===========================================================================
// Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================
// load current flash driver - this must be called before the using of any flash driver
INLINE void FLASH_Driver_Load(void)
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
}


#endif


