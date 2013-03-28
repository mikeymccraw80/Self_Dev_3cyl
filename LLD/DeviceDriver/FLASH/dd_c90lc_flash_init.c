//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_c90lc_flash_init.c %
//
// %created_by:      zzrfyj %
//
// %date_created:    Mon Jul 11 12:23:26 2011 %
//
// %derived_by:      %
//
// %date_modified:   %
//
// %version:         %
//
// ============================================================================
// SPECIFICATION REVISION:
//
// ============================================================================
// Configurable Development Software Module:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================

//=============================================================================
//
//                          Device Programming Driver
// This module provides Flash Memory information only. If use different flash
// memory, need to change this memory mapping.
//
// Requirements Document(s):
//   1. (Motorola) Chapter 10 Flash Memory of MPC5634M Microcontroller Reference
//       Manual.
//   2. (Motorola) Standard Software Driver for C90LC Flash in xPC56xx User's Manual.
//=============================================================================

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "dd_c90lc_flash_init.h"

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================
#include "dd_flash_mpc5634.h"     // FLASH register address definition

//===========================================================================
// Local preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================

//===========================================================================
// Local preprocessor #define MACROS() (i.e., those using # or ## operator)
//===========================================================================

//===========================================================================
//  Local Type Declarations (enum, struct, union, typedef)
//===========================================================================

//===========================================================================
// Exported Object Definitions
//===========================================================================
// This configuration shall be an RAM variable. Driver will change the value.
SSD_CONFIG ssdA0Config =
{
   (uint32_t)&FLASH_B0,       // base address of Flash A registers
   C90LC_ARRAY0_BASE_ADDRESS,  // base of main array
   0,                         // size of main array
   C90LC_SHADOW_BASE_ADDRESS, // base of shadow row 0
   C90LC_SHADOW_BYTE_SIZE,     // size of shadow row 0
   0,                         // block number in low address space
   0,                         // block number in middle address space
   0,                         // block number in high address space
   C90FL_PAGE_SIZE_08,        // page size - 8 bytes
   false                      // debug mode selection
};

SSD_CONFIG ssdA1Config =
{
   (uint32_t)&FLASH_B1A1,     // base address of Flash A registers
   C90LC_ARRAY1_BASE_ADDRESS, // base of main array
   0,                         // size of main array
   0,                         // base of shadow row 0
   0,                         // size of shadow row 0
   0,                         // block number in low address space
   0,                         // block number in middle address space
   0,                         // block number in high address space
   C90FL_PAGE_SIZE_08,        // page size - 8 bytes
   false                      // debug mode selection
};

SSD_CONFIG ssdA2Config =
{
   (uint32_t)&FLASH_B1A2,     // base address of Flash A registers
   C90LC_ARRAY2_BASE_ADDRESS,  // base of main array
   0,                         // size of main array
   0,                         // base of shadow row 0
   0,                         // size of shadow row 0
   0,                         // block number in low address space
   0,                         // block number in middle address space
   0,                         // block number in high address space
   C90FL_PAGE_SIZE_08,        // page size - 8 bytes
   false                      // debug mode selection
};

// Memory information of flash module, need to be initialized before use
C90LC_Memory_Map_T C90LC_Memory_Map[C90LC_Number_of_Blocks] =
{
   //   start address            size             Memory Array       Array space block number    ssdconfig - loaded at initialization
   // Low Address Space
   {     0x00000000,          FLASH_KB(16),      C90LC_MEMORY_A0_L,            0 ,               NULL  },
   {     0x00004000,          FLASH_KB(16),      C90LC_MEMORY_A0_L,            1 ,               NULL  },
   {     0x00008000,          FLASH_KB(32),      C90LC_MEMORY_A0_L,            2 ,               NULL  },
   {     0x00010000,          FLASH_KB(32),      C90LC_MEMORY_A0_L,            3 ,               NULL  },
   {     0x00018000,          FLASH_KB(16),      C90LC_MEMORY_A0_L,            4 ,               NULL  },
   {     0x0001C000,          FLASH_KB(16),      C90LC_MEMORY_A0_L,            5 ,               NULL  },
   {     0x00020000,          FLASH_KB(64),      C90LC_MEMORY_A0_L,            6 ,               NULL  },
   {     0x00030000,          FLASH_KB(64),      C90LC_MEMORY_A0_L,            7 ,               NULL  },
   // Mid Address Space
   {     0x00040000,          FLASH_KB(128),     C90LC_MEMORY_A0_M,            0 ,               NULL  },
   {     0x00060000,          FLASH_KB(128),     C90LC_MEMORY_A0_M,            1 ,               NULL  },
   // High Address Space
   {     0x00080000,          FLASH_KB(128),     C90LC_MEMORY_A1_H,            0 ,               NULL  },
   {     0x000A0000,          FLASH_KB(128),     C90LC_MEMORY_A1_H,            1 ,               NULL  },
   {     0x000C0000,          FLASH_KB(128),     C90LC_MEMORY_A1_H,            2 ,               NULL  },
   {     0x000E0000,          FLASH_KB(128),     C90LC_MEMORY_A1_H,            3 ,               NULL  },
   // High Address Space
   {     0x00100000,          FLASH_KB(128),     C90LC_MEMORY_A2_H,            0 ,               NULL  },
   {     0x00120000,          FLASH_KB(128),     C90LC_MEMORY_A2_H,            1 ,               NULL  },
   {     0x00140000,          FLASH_KB(128),     C90LC_MEMORY_A2_H,            2 ,               NULL  },
   {     0x00160000,          FLASH_KB(128),     C90LC_MEMORY_A2_H,            3 ,               NULL  },
   // Shadow
   {     0x00FFC000,          FLASH_KB(16),      C90LC_MEMORY_A0_S,            0 ,               NULL  }
};


//===========================================================================
//  Local object definitions
//===========================================================================

//===========================================================================
//  Local Function Prototypes
//===========================================================================

//===========================================================================
//  Local Inline Function Definitions and #define Function-Like Macros()
//===========================================================================

//===========================================================================
// Function definitions
//===========================================================================


//=============================================================================
//
// Revisiion History:
//
// Rev. YYMMDD Who  SCR# Changes
// ---- ------ ---- ---- -----------------------------------------------------
// 1.0  110711 xh   xxxx Create initial release.
//=============================================================================

