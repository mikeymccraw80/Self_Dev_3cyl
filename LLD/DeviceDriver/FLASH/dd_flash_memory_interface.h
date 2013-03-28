#ifndef DD_FLASH_MEMORY_INTERFACE_H
#define DD_FLASH_MEMORY_INTERFACE_H

#include "reuse.h"


typedef enum FLASH_MODULE_Tag
{
   C90LC_Module,
   C90FL_Module,
   FLASH_Module_Number
} FLASH_MODULE_T;

extern FLASH_MODULE_T Flash_Info;

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



#endif // DD_FLASH_MEMORY_INTERFACE_H


