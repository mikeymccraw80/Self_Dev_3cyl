#ifndef DD_C90FL_FLASH_H
#define DD_C90FL_FLASH_H

//=============================================================================
//
//                COPYRIGHT, 2006, DELPHI TECHNOLOGIES, INC.
//
//===========================================================================
// %full_filespec:   dd_c90fl_flash.h~1:incl:ctc_pt3#8 %
//
// created_by:       fzfns4
//
// date_created:     Thu Feb 02 08:17:54 2006
//
// %derived_by:      rz65p6 %
//
// %date_modified:    %
//
// %version:         1 %
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
//   1. (Motorola) Chapter 11 Flash Memory of MPC5674F Microcontroller Reference
//       Manual.
//   2. (Motorola) MPC55xx HC90FLStandard Software Driver User's Manual.
//                 The version of the used driver is 3.10.
//=============================================================================

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "reuse.h"
#include "ssd_c90fl.h"

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================

//===========================================================================
//    Exported preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================

//************************************************************************
//                  Password for unlock blocked blocks
//************************************************************************
#define C90FL_LMLR_PASSWORD  ((uint32_t)0xA1A11111)  // Enable to change LMLR
#define C90FL_HLR_PASSWORD   ((uint32_t)0xB2B22222)  // Enable to change HLR
#define C90FL_SLMLR_PASSWORD ((uint32_t)0xC3C33333)  // Enable to change SLMLR

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
// @enum C90FL_Block_Number_Tag
typedef enum C90FL_Block_Number_Tag
{
    C90FL_BLOCK_L0,
    C90FL_BLOCK_L1,
    C90FL_BLOCK_L2,
    C90FL_BLOCK_L3,
    C90FL_BLOCK_L4,
    C90FL_BLOCK_L5,
    C90FL_BLOCK_L6,
    C90FL_BLOCK_L7,
    C90FL_BLOCK_L8,
    C90FL_BLOCK_L9,
    C90FL_BLOCK_L10,
    C90FL_BLOCK_L11,
    C90FL_BLOCK_M0,
    C90FL_BLOCK_M1,
    C90FL_BLOCK_H0,
    C90FL_BLOCK_H1,
    C90FL_BLOCK_H2,
    C90FL_BLOCK_H3,
    C90FL_BLOCK_H4,
    C90FL_BLOCK_H5,
    C90FL_BLOCK_S0,
    C90FL_BLOCK_S1,
    C90FL_Number_of_Blocks,
    INVALID_BLOCK = 0xFFFF
} C90FL_Block_Number_T;

// @enum C90FL_MEMORY_ADDRESS_SPACE_TYTE_Tag
typedef enum C90FL_MEMORY_ADDRESS_SPACE_TYTE_Tag
{
   C90FL_MEMORY_LOW_ADDRESS_SPACE,
   C90FL_MEMORY_MID_ADDRESS_SPACE,
   C90FL_MEMORY_HIGH_ADDRESS_SPACE,
   C90FL_MEMORY_SHADOW_ADDRESS_SPACE
} C90FL_MEMORY_ADDRESS_SPACE_TYTE_T;


// @struct C90FL_Memory_Map_T | Define start address and size of a block
typedef struct C90FL_Memory_Map_Tag
{
   uint32_t Start_Addr;
   uint32_t Size_In_Byte;
   C90FL_MEMORY_ADDRESS_SPACE_TYTE_T Address_Space;
   uint16_t Address_Space_Block_Number;
   PSSD_CONFIG ssdConfig;
} C90FL_Memory_Map_T;

//===========================================================================
//  Exported Object Declarations
//===========================================================================

//===========================================================================
//  Exported Function Prototypes
//===========================================================================
//===========================================================================
// C90FL_Initialize
//
// @func Checks and initialize the control register of the C90FL module.
//       Unlock all blocks and disable prefetch.
//       This fuction shall be called first before useing other driver.
//
// @parm
//
// @rdesc bool | 1 - success, 0 - failure
//
// @end
//===========================================================================
bool C90FL_Initialize(void);

//===========================================================================
// C90FL_SetLock
//
// @func Unlock or Lock all blocks including Shadow without checking original
//       status.
//
// @parm bool | true - lock. else unlock
//
// @rdesc bool | true - set success, else failure
//
// @end
//===========================================================================
bool C90FL_SetLock(uint32_t in_address, bool lockstate);

//===========================================================================
// C90FL_Erase_Block
//
// @func Erase a block
//
// @parm uint16_t | block_number | block number
//
// @rdesc bool | true - erase success, else failure
//
// @end
//===========================================================================
bool C90FL_Erase_Block(uint32_t in_address, void *function);

//===========================================================================
// C90FL_Check_Erased
//
// @func Check an area of flash memory if erased
//
// @parm uint32_t | byte_length | byte number shall be multiply of 8
//
// @parm uint32_t | address | flash start address, shall be 8 byte boundary
//
// @parm *f() | function pointer | service watchdog at least
//
// @rdesc bool | true - erased, else not whole erased
//
// @end
//===========================================================================
bool C90FL_Check_Erased(uint32_t byte_length,
                       uint32_t start_address,
                       void *function);

//===========================================================================
// C90FL_Suspend_Erase
//
// @func Suspend erasing
//
// @parm
//
// @rdesc bool | true - Suspend success, else failure
//
// @end
//===========================================================================
bool C90FL_Suspend_Erase(uint32_t in_address);

//===========================================================================
// C90FL_Resume_Erase
//
// @func Resume a suspended erase
//
// @parm
//
// @rdesc bool | true - Resume success, else failure
//
// @end
//===========================================================================
bool C90FL_Resume_Erase(uint32_t in_address);

//===========================================================================
// C90FL_Suspend_Program
//
// @func Suspend writing
//
// @parm
//
// @rdesc bool | true - Suspend success, else failure
//
// @end
//===========================================================================
bool C90FL_Suspend_Program(void);

//===========================================================================
// C90FL_Resume_Program
//
// @func Resume a suspended write
//
// @parm
//
// @rdesc bool | true - Resume success, else failure
//
// @end
//===========================================================================
bool C90FL_Resume_Program(void);

//===========================================================================
// C90FL_Write_Flash_Memory
//
// @func Write flash memory. Using this interface eliminates limitation of
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
bool C90FL_Write_Flash_Memory(uint32_t byte_length,
                             uint32_t source_address,
                             uint32_t destination_address,
                             void *call_function);

//===========================================================================
// C90FL_Flash_ECCLogic_Check
//
// @func ECC logic check
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
bool C90FL_Flash_ECCLogic_Check(uint32_t in_address,
                               uint64_t data_value,
                               uint64_t error_bits,
                               uint32_t ecc_value);

//===========================================================================
// C90FL_Flash_Array_Integrity_Check
//
// @func Array Integrity check
//
// @parm uint16_t | block_number | block number
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
bool C90FL_Flash_Array_Integrity_Check(uint32_t in_address,
                                      bool addrSeq,
                                      MISR misrValue_Bk0,
                                      MISR misrValue_Bk1,
                                      void *function);

//===========================================================================
// C90FL_Factory_Margin_Read_Check
//
// @func Factory Margin Read check
//
// @parm uint16_t | block_number | block number
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
// @rdesc bool | 1 - MISR value calculated is correct, 0 - MISR value is incorrect
//
// @end
//===========================================================================
bool C90FL_Factory_Margin_Read_Check(uint32_t in_address,
                                    bool marginLevel,
                                    MISR misrValue_Bk0,
                                    MISR misrValue_Bk1,
                                    void *function);

//===========================================================================
// Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================


#endif // DD_C90FL_FLASH_H
