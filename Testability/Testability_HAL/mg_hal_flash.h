#ifndef MG_HAL_FLASH_H
#define MG_HAL_FLASH_H

bool mg_HAL_Flash_Set_Lock(uint32_t flash_address, bool state);
bool mg_HAL_Flash_Erase_Flash(uint32_t in_address, void *call_function);
bool mg_HAL_FLash_Program_Flash(uint32_t byte_length, uint32_t source_address, uint32_t destination_address, void *call_function);

#endif
