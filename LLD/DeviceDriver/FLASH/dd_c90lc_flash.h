#ifndef DD_C90LC_FLASH_H
#define DD_C90LC_FLASH_H

//=============================================================================
//
//                COPYRIGHT, 2006, DELPHI TECHNOLOGIES, INC.
//
//===========================================================================
// %full_filespec:    dd_c90lc_flash.h %
//
// %created_by:       zzrfyj %
//
// %date_created:     Mon Jul 11 12:25:16 2011 %
//
// %derived_by:       %
//
// %date_modified:    %
//
// %version:          %
//
//===========================================================================
// REUSE:
// None
//=============================================================================

//=============================================================================
//
//                          Device Programming Driver
// This module provides interfaces between Freescale flash driver and
// Application interfaces.
//
// Requirements Document(s):
//   1. (Motorola) Chapter 10 Flash Memory of MPC5634M Microcontroller Reference
//       Manual.
//   2. (Motorola) Standard Software Driver for C90LC Flash in xPC56xx User's Manual.
//=============================================================================

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "reuse.h"
#include "ssd_c90lc.h"


//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================

//===========================================================================
//    Exported preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================


//************************************************************************
//                  Password for unlock blocked blocks
//************************************************************************
#define C90LC_LMLR_PASSWORD  ((uint32_t)0xA1A11111)  // Enable to change LMLR
#define C90LC_HLR_PASSWORD   ((uint32_t)0xB2B22222)  // Enable to change HLR
#define C90LC_SLMLR_PASSWORD ((uint32_t)0xC3C33333)  // Enable to change SLMLR

//===========================================================================
//  Exported preprocessor #define MACROS() (i.e., those using # or ##)
//===========================================================================
#ifndef FLASH_KB
#define FLASH_KB(x)   ((x) * 1024)
#endif
#ifndef FLASH_MB
#define FLASH_MB(x)   ((x) * 1024 * 1024)
#endif

//===========================================================================
//    Exported Type Declarations (enum, struct, union, typedef)
//===========================================================================
// @enum C90LC_Block_Number_Tag
typedef enum C90LC_Block_Number_Tag
{
    C90LC_BLOCK_0,
    C90LC_BLOCK_1a,
    C90LC_BLOCK_1b,
    C90LC_BLOCK_2a,
    C90LC_BLOCK_2b,
    C90LC_BLOCK_3,
    C90LC_BLOCK_4,
    C90LC_BLOCK_5,
    C90LC_BLOCK_6,
    C90LC_BLOCK_7,
    C90LC_BLOCK_8,
    C90LC_BLOCK_9,
    C90LC_BLOCK_10,
    C90LC_BLOCK_11,
    C90LC_BLOCK_12,
    C90LC_BLOCK_13,
    C90LC_BLOCK_14,
    C90LC_BLOCK_15,
    C90LC_BLOCK_S0,
    C90LC_Number_of_Blocks,
    INVALID_BLOCK = 0xFFFF
} C90LC_Block_Number_T;

// @enum C90LC_MEMORY_Array_Tag
typedef enum C90LC_MEMORY_Array_Tag
{
   C90LC_MEMORY_A0_L,
   C90LC_MEMORY_A0_M,
   C90LC_MEMORY_A1_H,
   C90LC_MEMORY_A2_H,
   C90LC_MEMORY_A0_S
} C90LC_MEMORY_Array_T;


// @struct C90LC_Memory_Map_T | Define start address and size of a block
typedef struct C90LC_Memory_Map_Tag
{
   uint32_t Start_Addr;
   uint32_t Size_In_Byte;
   C90LC_MEMORY_Array_T Address_Space;
   uint16_t Array_Space_Block_Number;
   PSSD_CONFIG ssdConfig;
} C90LC_Memory_Map_T;

//===========================================================================
//  Exported Object Declarations
//===========================================================================

//===========================================================================
//  Exported Function Prototypes
//===========================================================================
//===========================================================================
// C90LC_Initialize
//
// @func Initial all ssdConfig
//       This fuction shall be called first before useing other driver.
//
// @parm
//
// @rdesc bool | 1 - success, 0 - failure
//
// @end
//===========================================================================
bool C90LC_Initialize(void);

//===========================================================================
// C90LC_Erase_Block
//
// @func Erase a block
//
// @parm uint32_t | in_address | in address
//
// @rdesc bool | true - erase success, else failure
//
// @end
//===========================================================================
bool C90LC_Erase_Block(uint32_t in_address, void *function);

//===========================================================================
// C90LC_Check_Erased
//
// @func Check an area of flash memory if erased
//
// @parm uint32_t | byte_length | byte number shall be multiply of 8
//
// @parm uint32_t | address | flash start address, shall be 8 byte boundary
//
// @rdesc bool | true - erased, else not whole erased
//
// @end
//===========================================================================
bool C90LC_Check_Erased(uint32_t byte_length,
                       uint32_t start_address,
                       void *function);

//===========================================================================
// C90LC_Suspend_Erase
//
// @func Suspend erasing
//
// @parm uint32_t | in_address |
//
// @rdesc bool | true - Suspend success, else failure
//
// @end
//===========================================================================
bool C90LC_Suspend_Erase(uint32_t in_address);

//===========================================================================
// C90LC_Resume_Erase
//
// @func Resume a suspended erase
//
// @parm uint32_t | in_address |
//
// @rdesc bool | true - Resume success, else failure
//
// @end
//===========================================================================
bool C90LC_Resume_Erase(uint32_t in_address);

//===========================================================================
// C90LC_Suspend_Program
//
// @func Suspend writing - Program suspend is not available on MPC5634
//
// @parm
//
// @rdesc bool | true - Suspend success, else failure
//
// @end
//===========================================================================
bool C90LC_Suspend_Program(void);

//===========================================================================
// C90LC_Resume_Program
//
// @func Resume a suspended write - Program suspend is not available on MPC5634
//
// @parm
//
// @rdesc bool | true - Resume success, else failure
//
// @end
//===========================================================================
bool C90LC_Resume_Program(void);

//===========================================================================
// C90LC_Write_Array_Memory
//
// @func Write array memory. Using this interface eliminates limitation of
//       size and address of flash memory - do not request programmed memory
//       shall be 8 byte boundary.
//
// @parm uint32_t | size | Programmed flash memory sise
//
// @parm uint32_t | address | Source data RAM start address which shall be
//       4 byte boundary
//
// @parm uint32_t | address | flash memory start address
//
// @parm *function() | pointer function | call this function during writing
//
// @rdesc bool | 1 - success, 0 - failure
//
// @end
//===========================================================================
bool C90LC_Write_Array_Memory(uint32_t byte_length,
                             uint32_t source_address,
                             uint32_t destination_address,
                             void *call_function);

//===========================================================================
// C90LC_Flash_ECCLogic_Check
//
// @func ECC logic check
//
// @parm uint32_t | in_address | flash configuration needed by freescale driver
//
// @parm uint64_t | data_value | data on which ECC is calculated
//
// @parm uint64_t | error_bits | mask of error bits
//
// @parm uint32_t | ecc_value | ECC value calculated offline
//
// @rdesc bool | 1 - ecc error detected, 0 - failure
//
// @end
//===========================================================================
bool C90LC_Flash_ECCLogic_Check(uint32_t in_address,
                               uint64_t data_value,
                               uint64_t error_bits,
                               uint32_t ecc_value);

//===========================================================================
// C90LC_Flash_Array_Integrity_Check
//
// @func Array Integrity check
//
// @parm uint32_t | in_address |
//
// @parm bool | addrSeq | 0- default or proprietary sequence,
// 1 - logical sequence
//
// @parm MISR | misrValue_Bk0 | MISR values for Bank0 calculated
// by user
//
// @parm MISR | misrValue_Bk1 | MISR values for Bank1 calculated
// by user
//
// @rdesc bool | 1 - MISR value calculated is correct, 0 - MISR value is incorrect
//
// @end
//===========================================================================
bool C90LC_Flash_Array_Integrity_Check(uint32_t in_address,
                                      bool addrSeq,
                                      MISR misrValue,
                                      void *function);

//===========================================================================
// C90LC_Factory_Margin_Read_Check
//
// @func Factory Margin Read check
//
// @parm uint32_t | in_address |
//
// @parm bool | marginLevel | 0- Programmed level
// 1 - Erased Level
//
// @parm MISR | misrValue_Bk0 | MISR values for Bank0 calculated
// by user
//
// @parm MISR | misrValue_Bk1 | MISR values for Bank1 calculated
// by user
//
// @rdesc bool | 1 - MISR value calculated is correct, 0 - MISR value is   incorrect
//
// @end
//===========================================================================
bool C90LC_Factory_Margin_Read_Check(uint32_t in_address,
                                    bool marginLevel,
                                    MISR misrValue,
                                    void *function);

//===========================================================================
// C90LC_SetLock
//
// @func Set the lock state of block
//
// @parm uint16_t | blocknum | block number
//
// @parm bool | lockstate | 0- unlock  1 - lock
//
// @rdesc bool | 1 - Lock is set correctly, 0 - Lock is set incorrectly
//
// @end
//===========================================================================
bool C90LC_SetLock(uint32_t in_address, bool lockstate);



//===========================================================================
// Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================


#endif // DD_C90LC_FLASH_H

//=============================================================================
//
// Revisiion History:
//
// Rev. YYMMDD Who  SCR# Changes
// ---- ------ ---- ---- -----------------------------------------------------
// 1.0  110711 xh   xxxx Create initial release.
//=============================================================================

