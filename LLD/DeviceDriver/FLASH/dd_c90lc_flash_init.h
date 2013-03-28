#ifndef DD_C90LC_FLASH_INIT_H
#define DD_C90LC_FLASH_INIT_H

//=============================================================================
//
//                COPYRIGHT, 2006, DELPHI TECHNOLOGIES, INC.
//
//===========================================================================
// %full_filespec:   dd_c90lc_flash_init.h %
//
// %created_by:      zzrfyj %
//
// %date_created:    Mon Jul 11 12:23:42 2011 %
//
// %derived_by:      %
//
// %date_modified:   %
//
// %version:         %
//
//===========================================================================
// REUSE:
// None
//=============================================================================

//=============================================================================
//
//                          Device Programming Driver
// This module provides memory mapping.
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

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================
#include "ssd_types.h"
#include "ssd_c90lc.h"       // SSD_CONFIG, the header file shall follow
                            // ssd_types.h
#include "dd_c90lc_flash.h"  // C90LC_Memory_Map_T,
                            // C90LC_MEMORY_ADDRESS_SPACE_TYTE_T

//===========================================================================
//    Exported preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================
//*************************************************************************
//                   FLASH memory base address
//*************************************************************************
// Internal flash memory base address
#define C90LC_ARRAY_BASE_ADDRESS     (0x00000000)
#define C90LC_ARRAY0_BASE_ADDRESS    (0x00000000)
#define C90LC_ARRAY1_BASE_ADDRESS    (0x00080000)
#define C90LC_ARRAY2_BASE_ADDRESS    (0x00100000)
#define C90LC_SHADOW_BASE_ADDRESS    (0x00FFC000)

// Memory Byte Size
#define C90LC_MAIN_AREA_BYTE_SIZE (0x180000)    // 1.5MB
#define C90LC_SHADOW_BYTE_SIZE    (0x4000)      // 16K

// Memory End Address plus 1
#define C90LC_MAIN_AREA_END_ADDRESS \
                     (C90LC_ARRAY_BASE_ADDRESS + C90LC_MAIN_AREA_BYTE_SIZE)
#define C90LC_SHADOW_END_ADDRESS \
                     (C90LC_SHADOW_BASE_ADDRESS + C90LC_SHADOW_BYTE_SIZE)


//===========================================================================
//  Exported preprocessor #define MACROS() (i.e., those using # or ##)
//===========================================================================

//===========================================================================
//    Exported Type Declarations (enum, struct, union, typedef)
//===========================================================================

//===========================================================================
//  Exported Object Declarations
//===========================================================================
extern C90LC_Memory_Map_T C90LC_Memory_Map[C90LC_Number_of_Blocks];
extern SSD_CONFIG ssdA0Config;
extern SSD_CONFIG ssdA1Config;
extern SSD_CONFIG ssdA2Config;

//===========================================================================
//  Exported Function Prototypes
//===========================================================================

//===========================================================================
// Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================

#endif  // DD_C90LC_FLASH_INIT_H

//=============================================================================
//
// Revisiion History:
//
// Rev. YYMMDD Who  SCR# Changes
// ---- ------ ---- ---- -----------------------------------------------------
// 1.0  110711 xh   xxxx Create initial release.
//=============================================================================

