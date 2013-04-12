#ifndef DD_FLASH_MPC5634_H
#define DD_FLASH_MPC5634_H

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================

#include "hw_flash_mpc5634.h"

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================

//===========================================================================
//    Exported preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================

//===========================================================================
//  Exported object definitions
//===========================================================================
#define SECTION_FLASH_B0_REGISTER
#include "section.h"
extern FLASHB0_T FLASH_B0;
#define SECTION_END
#include "section.h"

#define SECTION_FLASH_B1A1_REGISTER
#include "section.h"
extern FLASHB1_T FLASH_B1A1;
#define SECTION_END
#include "section.h"

#define SECTION_FLASH_B1A2_REGISTER
#include "section.h"
extern FLASHB1_T FLASH_B1A2;
#define SECTION_END
#include "section.h"


//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================


//===========================================================================
//  Enumeration: Prefetch limit(PFLIM)
//
//  PFLIM[2:0] Meaning of Value
//  ========== ==============================================================
//         000 No prefetching is performed
//         001 A single additional line (next sequential) is prefetched
//             on a buffer miss
//         010 Up to two additional lines may be prefetched following each
//             buffer miss before prefetching is halted. A single additional
//             line (next sequential) is prefetched on a buffer miss, and the
//             next sequential line is prefetched on a buffer hit
//             (if not already present).
//         011 Up to three additional lines may be prefetched following each
//             buffer miss before prefetching is halted. Only a single
//             additional prefetch is initiated after each buffer hit or miss
//         100 Up to four additional lines may be prefetched following each
//             buffer miss before prefetching is halted. Only a single
//             additional prefetch is initiated after each buffer hit or miss
//         101 Up to five additional lines may be prefetched following each
//             buffer miss before prefetching is halted. Only a single
//             additional prefetch is initiated after each buffer hit or miss
//         110 An unlimited number of additional lines may be prefetched
//             following each buffer miss. Only a single additional prefetch
//             is initiated on each buffer hit or miss.
//         111 Reserved
//===========================================================================
typedef enum FLASH_BIUCR_PFLIM_Tag
{
   FLASH_BIUCR_PFLIM_NO_PREFETCH,
   FLASH_BIUCR_PFLIM_SINGLE_ADDITIONAL_LINE,
   FLASH_BIUCR_PFLIM_UPTO_TWO_ADDITIONAL_LINES,
   FLASH_BIUCR_PFLIM_UPTO_THREE_ADDITIONAL_LINES,
   FLASH_BIUCR_PFLIM_UPTO_FOUR_ADDITIONAL_LINES,
   FLASH_BIUCR_PFLIM_UPTO_FIVE_ADDITIONAL_LINES,
   FLASH_BIUCR_PFLIM_UNLIMITED_ADDITIONAL_LINES,
   FLASH_BIUCR_PFLIM_RESERVED
}  FLASH_BIUCR_PFLIM_T;


//===========================================================================
//  Enumeration: Instruction prefetch enable(IPFEN)
//
//  IPFEN[1:0] Meaning of Value
//  ========== ==============================================================
//          00 No prefetching is triggered by a instruction read access
//          01 Prefetching may be triggered only by a instruction burst
//             read access
//          10 Reserved
//          11 Prefetching may be triggered by any instruction read access
//===========================================================================
typedef enum FLASH_BIUCR_IPFEN_Tag
{
   FLASH_BIUCR_IPFEN_NO_PREFETCH,
   FLASH_BIUCR_IPFEN_PREFETCH_ONLY_BY_BURST_READ,
   FLASH_BIUCR_IPFEN_RESERVED,
   FLASH_BIUCR_IPFEN_PREFETCH_BY_ANY_READ
}  FLASH_BIUCR_IPFEN_T;

//===========================================================================
//  Enumeration: Data prefetch enable(DPFEN)
//
//  DPFEN[1:0] Meaning of Value
//  ========== ==============================================================
//          00 No prefetching is triggered by a data read access
//          01 Prefetching may be triggered only by a data burst read access
//          10 Reserved
//          11 Prefetching may be triggered by any data read access
//===========================================================================
typedef enum FLASH_BIUCR_DPFEN_Tag
{
   FLASH_BIUCR_DPFEN_NO_PREFETCH,
   FLASH_BIUCR_DPFEN_PREFETCH_ONLY_BY_BURST_READ,
   FLASH_BIUCR_DPFEN_RESERVED,
   FLASH_BIUCR_DPFEN_PREFETCH_BY_ANY_READ
}  FLASH_BIUCR_DPFEN_T;

//===========================================================================
//  Enumeration: Read wait state control.(RWSC)
//
//  RWSC[2:0] Meaning of Value
//  ========= ===============================================================
//        000 Zero wait states
//        001 One wait state
//
//        111 Seven wait states
//===========================================================================

typedef enum FLASH_BIUCR_RWSC_Tag
{
   FLASH_BIUCR_RWSC_ZERO_WAIT_STATE,
   FLASH_BIUCR_RWSC_ONE_WAIT_STATE,
   FLASH_BIUCR_RWSC_TWO_WAIT_STATES,
   FLASH_BIUCR_RWSC_THREE_WAIT_STATES,
   FLASH_BIUCR_RWSC_FOUR_WAIT_STATES,
   FLASH_BIUCR_RWSC_FIVE_WAIT_STATES,
   FLASH_BIUCR_RWSC_SIX_WAIT_STATES,
   FLASH_BIUCR_RWSC_SEVEN_WAIT_STATES
}  FLASH_BIUCR_RWSC_T;


//===========================================================================
//  Enumeration: Write wait state control(WWSC)
//
//  WWSC[1:0] Meaning of Value
//  ========= ===============================================================
//         00 Reserved
//         01 One wait state
//         10 Two wait states
//         11 Three wait states
//===========================================================================

typedef enum FLASH_BIUCR_WWSC_Tag
{
   FLASH_BIUCR_WWSC_RESERVED,
   FLASH_BIUCR_WWSC_ONE_WAIT_STATE,
   FLASH_BIUCR_WWSC_TWO_WAIT_STATES,
   FLASH_BIUCR_WWSC_THREE_WAIT_STATES
}  FLASH_BIUCR_WWSC_T;


//===========================================================================
//  Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================

typedef enum FLASH_Run_Mode_Tag
{
   FLASH_RUN_MODE_NORMAL,
   FLASH_RUN_MODE_REPROGRAMMING
} FLASH_Run_Mode_T;

typedef enum
{
   FLASH_PREFETCH_DISABLE,
   FLASH_PREFETCH_ENABLE
}FLASH_Prefetch_T;


//===========================================================================
//  Enumeration: Address pipelining control(APC)
//
//   APC[2:0] Meaning of Value
//  ========= ===============================================================
//        000 Reserved
//        001 Access requests require one hold cycle
//        010 Access requests require two hold cycles
//
//        110 Access requests require 6 hold cycles
//        111 No address pipelining
//===========================================================================

typedef enum FLASH_BIUCR_APC_Tag
{
   FLASH_BIUCR_APC_RESERVED,
   FLASH_BIUCR_APC_ONE_HOLD_CYCLE,
   FLASH_BIUCR_APC_TWO_HOLD_CYCLES,
   FLASH_BIUCR_APC_THREE_HOLD_CYCLES,
   FLASH_BIUCR_APC_FOUR_HOLD_CYCLES,
   FLASH_BIUCR_APC_FIVE_HOLD_CYCLES,
   FLASH_BIUCR_APC_SIX_HOLD_CYCLES,
   FLASH_BIUCR_APC_NO_ADDRESS_PIPELINE
}  FLASH_BIUCR_APC_T;

//===========================================================================
// FLASH_Initialize
//
// @func This function initializes Flash Bus Interface Control Register
//       (FLASH_BIUCR) through FLASH_BIU_Initialize_From_RAM.
//       Before call FLASH_BIU_Initialize_From_RAM(), the function prepares
//       FLASH_BIUCR value per passed prameter.
//
// @parm IO_Configuration_T| in_configuration | .
//
// @rdesc None. 
//
// @end
//===========================================================================
extern void MPC5634_FLASH_Initialize_Normal(void);
extern void MPC5634_FLASH_Initialize_Programming(void);

#endif // DD_FLASH_H

