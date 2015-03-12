#include "dd_flash_interface.h"

bool mg_HAL_Flash_Set_Lock(uint32_t in_address, bool state)
{
    return flash_memory_interface->FLASH_Set_Lock(in_address, state);
}

bool mg_HAL_Flash_Erase_Flash(uint32_t in_address, void *call_function)
{
    return flash_memory_interface->FLASH_Erase_Memory(in_address, call_function);
}

bool mg_HAL_FLash_Program_Flash(uint32_t byte_length, uint32_t source_address, uint32_t destination_address, void *call_function)
{
    return flash_memory_interface->FLASH_Program_Memory(byte_length, source_address, destination_address, call_function);
}
