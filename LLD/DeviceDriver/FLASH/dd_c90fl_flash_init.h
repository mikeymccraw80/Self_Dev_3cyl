#ifndef DD_C90FL_FLASH_INIT_H
#define DD_C90FL_FLASH_INIT_H

//=============================================================================
//
//                COPYRIGHT, 2006, DELPHI TECHNOLOGIES, INC.
//
//===========================================================================
// %full_filespec:   dd_c90fl_flash_init.h~1:incl:ctc_pt3#8 %
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
// This module provides memory mapping.
//
// Requirements Document(s):
//   1. (Motorola) Chapter 13 Flash Memory of MPC5554 Microcontroller Reference
//       Manual.
//   2. (Motorola) MPC55xx C90FL Standard Software Driver User's Manual.
//                 The version of the used driver is 3.10.
//=============================================================================

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "reuse.h"

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================
#include "ssd_types.h"
#include "ssd_c90fl.h"       // SSD_CONFIG, the header file shall follow
                            // ssd_types.h
#include "dd_c90fl_flash.h"  // C90FL_Memory_Map_T,
                            // C90FL_MEMORY_ADDRESS_SPACE_TYTE_T

//===========================================================================
//    Exported preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================
//*************************************************************************
//                   FLASH memory base address
//*************************************************************************
// Internal flash memory base address
#define C90FL_ARRAY_BASE_ADDRESS     (0x00000000)
#define C90FL_SHADOW0_BASE_ADDRESS   (0x00EFC000)
#define C90FL_SHADOW1_BASE_ADDRESS   (0x00FFC000)
#define C90FL_SHADOW_BYTE_SIZE    (0x4000)      // 16K


//===========================================================================
//  Exported preprocessor #define MACROS() (i.e., those using # or ##)
//===========================================================================

//===========================================================================
//    Exported Type Declarations (enum, struct, union, typedef)
//===========================================================================

//===========================================================================
//  Exported Object Declarations
//===========================================================================
extern C90FL_Memory_Map_T C90FL_Memory_Map[C90FL_Number_of_Blocks];
extern SSD_CONFIG ssdConfig;

//===========================================================================
//  Exported Function Prototypes
//===========================================================================

//===========================================================================
// Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================

#endif  // DD_C90FL_FLASH_INIT_H
