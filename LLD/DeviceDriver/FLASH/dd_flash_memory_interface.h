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

//=============================================================================
// FLASH_Memory_Initial_T
//=============================================================================
typedef bool (*FLASH_Memory_Initial_T)(void);

//=============================================================================
// FLASH_Set_Lock_T
//=============================================================================
typedef bool (*FLASH_Set_Lock_T)(uint32_t in_address, bool state);

//=============================================================================
// FLASH_Erase_Memory_T
//=============================================================================
typedef bool (*FLASH_Erase_Memory_T)(uint32_t in_address, void *call_function);

//=============================================================================
// FLASH_Program_Memory_T
//=============================================================================
typedef bool (*FLASH_Program_Memory_T)(uint32_t byte_length,
                                       uint32_t source_address,
                                       uint32_t destination_address,
                                       void *call_function);

//=============================================================================
// FLASH_Check_Erased_T
//=============================================================================
typedef bool (*FLASH_Check_Erased_T)(uint32_t byte_length,
                                   uint32_t start_address,
                                   void *function);

//===========================================================================
//  Exported Function Prototypes
//===========================================================================

typedef struct FLASH_Memory_Interface_Tag
{
   FLASH_Memory_Initial_T         FLASH_Memory_Initial;
   FLASH_Set_Lock_T               FLASH_Set_Lock;
   FLASH_Erase_Memory_T           FLASH_Erase_Memory;
   FLASH_Program_Memory_T         FLASH_Program_Memory;
   FLASH_Check_Erased_T           FLASH_Check_Erased;
}  FLASH_Memory_Interface_T;


extern const FLASH_Memory_Interface_T FLASH_Memory_Interface[FLASH_Module_Number];


#endif // DD_FLASH_MEMORY_INTERFACE_H


