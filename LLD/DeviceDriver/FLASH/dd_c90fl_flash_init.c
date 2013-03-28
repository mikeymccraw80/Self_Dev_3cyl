//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_h7fa_flash_init.c~1:csrc:ctc_pt3#8 %
//
// created_by:       fzfns4
//
// date_created:     Fri May  5 12:10:47 2006
//
// %derived_by:      rz65p6 %
//
// %date_modified:    %
//
// %version:         1 %
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
//   1. (Motorola) Chapter 11 Flash Memory of MPC5674F Microcontroller Reference
//       Manual.
//   2. (Motorola) MPC55xx H7Fa Standard Software Driver User's Manual.
//                 The version of the used driver is 3.10.
//=============================================================================

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "dd_c90fl_flash_init.h"

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================
#include "dd_flash_mpc5644.h"     // FLASH register address definition

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
SSD_CONFIG ssdConfig =
{
   (uint32_t)&FLASH_A,        // base address of Flash A registers
   C90FL_ARRAY_BASE_ADDRESS,   // base of main array
   0,                         // size of main array
   C90FL_SHADOW0_BASE_ADDRESS, // base of shadow row 0
   C90FL_SHADOW_BYTE_SIZE,     // size of shadow row 0
   0,                         // block number in low address space
   0,                         // block number in middle address space
   0,                         // block number in high address space
   0x10,                      // page size
   false                      // debug mode selection
};

// Linear memory map of c90fl
C90FL_Memory_Map_T C90FL_Memory_Map[C90FL_Number_of_Blocks] =
{
   //   start address            size                 Memory Address Space       Array space block number      ssdconfig
   // Low Address Space - FLASH_A LAS + FLASH_A MAS
   // FLASH_A LAS
   {     0x00000000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            0 ,               &ssdConfig  },
   {     0x00004000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            1 ,               &ssdConfig  },
   {     0x00008000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            2 ,               &ssdConfig  },
   {     0x0000C000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            3 ,               &ssdConfig  },
   {     0x00010000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            4 ,               &ssdConfig  },
   {     0x00014000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            5 ,               &ssdConfig  },
   {     0x00018000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            6 ,               &ssdConfig  },
   {     0x0001C000,          FLASH_KB(16),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            7 ,               &ssdConfig  },
   {     0x00020000,          FLASH_KB(64),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            8 ,               &ssdConfig  },
   {     0x00030000,          FLASH_KB(64),      C90FL_MEMORY_LOW_ADDRESS_SPACE,            9 ,               &ssdConfig  },
   // FLASH_A MAS
   {     0x00040000,          FLASH_KB(128),     C90FL_MEMORY_LOW_ADDRESS_SPACE,            10 ,              &ssdConfig  },
   {     0x00060000,          FLASH_KB(128),     C90FL_MEMORY_LOW_ADDRESS_SPACE,            11 ,              &ssdConfig  },
   // Mid Address Space - FLASH_B LAS + FLASH_B MAS
   // FLASH_B LAS
   {     0x00080000,          FLASH_KB(256),     C90FL_MEMORY_MID_ADDRESS_SPACE,            0 ,               &ssdConfig  },
   // FLASH_B MAS
   {     0x000C0000,          FLASH_KB(256),     C90FL_MEMORY_MID_ADDRESS_SPACE,            1 ,               &ssdConfig  },
   // High Address Space - FLASH_A HAS + FLASH_B HAS
   {     0x00100000,          FLASH_KB(512),     C90FL_MEMORY_HIGH_ADDRESS_SPACE,           0 ,               &ssdConfig  },
   {     0x00180000,          FLASH_KB(512),     C90FL_MEMORY_HIGH_ADDRESS_SPACE,           1 ,               &ssdConfig  },
   {     0x00200000,          FLASH_KB(512),     C90FL_MEMORY_HIGH_ADDRESS_SPACE,           2 ,               &ssdConfig  },
   {     0x00280000,          FLASH_KB(512),     C90FL_MEMORY_HIGH_ADDRESS_SPACE,           3 ,               &ssdConfig  },
   {     0x00300000,          FLASH_KB(512),     C90FL_MEMORY_HIGH_ADDRESS_SPACE,           4 ,               &ssdConfig  },
   {     0x00380000,          FLASH_KB(512),     C90FL_MEMORY_HIGH_ADDRESS_SPACE,           5 ,               &ssdConfig  },
   // Shadow
   {     0x00FFC000,          FLASH_KB(16),      C90FL_MEMORY_SHADOW_ADDRESS_SPACE,         0 ,               &ssdConfig  },
   {     0x00FFC000,          FLASH_KB(16),      C90FL_MEMORY_SHADOW_ADDRESS_SPACE,         0 ,               &ssdConfig  }
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
