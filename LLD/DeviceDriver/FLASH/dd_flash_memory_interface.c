#include "dd_flash_memory_interface.h"


// ============================================================================
// External function
//=============================================================================
//C90FL
bool C90FL_Initialize(void);
bool C90FL_SetLock(uint32_t in_address, bool lockstate);
bool C90FL_Erase_Block(uint32_t in_address, void *function);
bool C90FL_Write_Flash_Memory(uint32_t byte_length,
                             uint32_t source_address,
                             uint32_t destination_address,
                             void *call_function);
bool C90FL_Check_Erased(uint32_t byte_length,
                       uint32_t start_address,
                       void *function);
//C90LC
bool C90LC_Initialize(void);
bool C90LC_SetLock(uint32_t in_address, bool lockstate);
bool C90LC_Erase_Block(uint32_t in_address, void *function);
bool C90LC_Write_Array_Memory(uint32_t byte_length,
                             uint32_t source_address,
                             uint32_t destination_address,
                             void *call_function);
bool C90LC_Check_Erased(uint32_t byte_length,
                       uint32_t start_address,
                       void *function);

// ============================================================================
// FLASH Memory interface.
//
//=============================================================================
const FLASH_Memory_Interface_T FLASH_Memory_Interface[FLASH_Module_Number] =
{
   // C90LC - MPC5634M Monaco
   {
      C90LC_Initialize,
      C90LC_SetLock,
      C90LC_Erase_Block,
      C90LC_Write_Array_Memory,
      C90LC_Check_Erased
   },
   // C90FL - MPC5644A Andorra
   {
      C90FL_Initialize,
      C90FL_SetLock,
      C90FL_Erase_Block,
      C90FL_Write_Flash_Memory,
      C90FL_Check_Erased
   }
};


FLASH_Memory_Interface_T * flash_memory_interface;

