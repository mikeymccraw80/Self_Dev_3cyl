#ifndef DD_FLASH_MPC5644_H
#define DD_FLASH_MPC5644_H

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================

#include "hw_flash_mpc5644.h"

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================

//===========================================================================
//    Exported preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================

//===========================================================================
//  Exported object definitions
//===========================================================================
#define SECTION_FLASH_A_REGISTER
#include "section.h"
extern FLASH_T FLASH_A;
#define SECTION_END
#include "section.h"

#define SECTION_FLASH_B_REGISTER
#include "section.h"
extern FLASH_T FLASH_B;
#define SECTION_END
#include "section.h"

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================

//===========================================================================
//    Exported preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================

//===========================================================================
//  Enumeration: Location of each field in FLASH_BIUCR
//  Flash Bus Interface Unit Control Register
//===========================================================================
typedef enum FLASH_BIUCR_Position_Tag
{
   FLASH_BIUCR_POSITION_BFEN  =  0,  // @emem  0 FBIU line read buffers enable
   FLASH_BIUCR_POSITION_PFLIM =  1,  // @emem [2:1] Prefetch limit
   FLASH_BIUCR_POSITION_IPFEN =  3,  // @emem 3 Instruction prefetch enable
   FLASH_BIUCR_POSITION_DPFEN =  4,  // @emem 4 Data prefetch enable
   FLASH_BIUCR_POSITION_RWSC  =  5,  // @emem [7:5] Read wait state control
   FLASH_BIUCR_POSITION_WWSC  =  8,  // @emem [9:8] Write wait state control
   FLASH_BIUCR_POSITION_APC   = 10,  // @emem [12:10] Address pipelining control
   FLASH_BIUCR_POSITION_M0PFE = 13,  // @emem 13 e200z4 Instruction prefetch
   FLASH_BIUCR_POSITION_M4PFE = 14,  // @emem 14 eDMA prefetch enable
   FLASH_BIUCR_POSITION_M1PFE = 15,  // @emem 15 e200z4 Load/Store
   FLASH_BIUCR_POSITION_M6PFE = 16,  // @emem 16 Flexray prefetch enable
   FLASH_BIUCR_POSITION_LBCFG = 17,  // @emem [18:17] Line Buffer Configuration
   FLASH_BIUCR_POSITION_M8PFE = 19   // @emem 19 Nexus prefetch enable
   
} FLASH_BIUCR_Position_T;

//===========================================================================
//  Enumeration: Width of each field in FLASH_BIUCR
//  Flash Bus Interface Unit Control Register
//===========================================================================
typedef enum FLASH_BIUCR_Width_Tag
{
   FLASH_BIUCR_WIDTH_BFEN  = 1,   // @emem 0 FBIU line read buffers enable
   FLASH_BIUCR_WIDTH_PFLIM = 2,   // @emem [2:1] Prefetch limit
   FLASH_BIUCR_WIDTH_IPFEN = 1,   // @emem 3 Instruction prefetch enable
   FLASH_BIUCR_WIDTH_DPFEN = 1,   // @emem 4 Data prefetch enable
   FLASH_BIUCR_WIDTH_RWSC  = 3,   // @emem [7:5] Read wait state control
   FLASH_BIUCR_WIDTH_WWSC  = 2,   // @emem [9:8] Write wait state control
   FLASH_BIUCR_WIDTH_APC   = 3,   // @emem [12:10] Address pipelining control
   FLASH_BIUCR_WIDTH_M0PFE = 1,   // @emem 13 e200z6 prefetch enable
   FLASH_BIUCR_WIDTH_M4PFE = 1,   // @emem 14 eDMA prefetch enable
   FLASH_BIUCR_WIDTH_M1PFE = 1,   // @emem 15 e200z4 Load/Store
   FLASH_BIUCR_WIDTH_M6PFE = 1,   // @emem 16 Flexray prefetch enable
   FLASH_BIUCR_WIDTH_LBCFG = 2,   // @emem 17 Line Buffer Configuration
   FLASH_BIUCR_WIDTH_M8PFE = 1    // @emem 19 Nexus prefetch enable

} FLASH_BIUCR_Width_T;


//===========================================================================
//  Enumeration: Prefetch limit(PFLIM)
//
//  PFLIM[2:0] Meaning of Value
//  ========== ==============================================================
//         00 No prefetching is performed
//         01 The referenced line is prefetched on a buffer miss, i.e., 
//            prefetch on miss.             
//         1x The referenced line is prefetched on a buffer miss, or 
//            the next sequential line is prefetched on a buffer hit (if
//            not already present), i.e., prefetch on miss or hit.
//===========================================================================
typedef enum FLASH_BIUCR_PFLIM_Tag
{
   FLASH_BIUCR_PFLIM_NO_PREFETCH,
   FLASH_BIUCR_PFLIM_PREFETCH_ON_MISS,
   FLASH_BIUCR_PFLIM_PREFETCH_ON_MISS_OR_HIT
}  FLASH_BIUCR_PFLIM_T;


//===========================================================================
//  Enumeration: Read wait state control.(RWSC)
//
//  RWSC[2:0] Meaning of Value
//  ========= ===============================================================
//        000 Zero wait states
//        001 One wait state
//        ...
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
//         00 No additional wait state
//         01 One wait state
//         10 Two wait states
//         11 Three wait states
//===========================================================================

typedef enum FLASH_BIUCR_WWSC_Tag
{
   FLASH_BIUCR_WWSC_NO_WAIT_STATE,
   FLASH_BIUCR_WWSC_ONE_WAIT_STATE,
   FLASH_BIUCR_WWSC_TWO_WAIT_STATES,
   FLASH_BIUCR_WWSC_THREE_WAIT_STATES
}  FLASH_BIUCR_WWSC_T;


//===========================================================================
//  Enumeration: Address pipelining control(APC)
//
//   APC[2:0] Meaning of Value
//  ========= ===============================================================
//        000 Access is pipelined back to back
//        001 Access requests require one hold cycle
//        010 Access requests require two hold cycles
//        ...
//        110 Access requests require 6 hold cycles
//        111 No address pipelining
//===========================================================================

typedef enum FLASH_BIUCR_APC_Tag
{
   FLASH_BIUCR_APC_BACK_TO_BACK,
   FLASH_BIUCR_APC_ONE_HOLD_CYCLE,
   FLASH_BIUCR_APC_TWO_HOLD_CYCLES,
   FLASH_BIUCR_APC_THREE_HOLD_CYCLES,
   FLASH_BIUCR_APC_FOUR_HOLD_CYCLES,
   FLASH_BIUCR_APC_FIVE_HOLD_CYCLES,
   FLASH_BIUCR_APC_SIX_HOLD_CYCLES,
   FLASH_BIUCR_APC_NO_ADDRESS_PIPELINE
}  FLASH_BIUCR_APC_T;


typedef enum
{
   FLASH_PREFETCH_DISABLE,
   FLASH_PREFETCH_ENABLE
}FLASH_Prefetch_T;

//===========================================================================
//  Enumeration: Data prefetch enable(DPFEN)
//
//  DPFEN[1:0] Meaning of Value
//  ========== ==============================================================
//          0 No prefetching is triggered by a data read access
//          1 Prefetching may be triggered by any data read access
//===========================================================================
typedef enum FLASH_BIUCR_DPFEN_Tag
{
   FLASH_BIUCR_DPFEN_NO_PREFETCH,
   FLASH_BIUCR_DPFEN_PREFETCH_BY_ANY_READ
}  FLASH_BIUCR_DPFEN_T;
//===========================================================================
//  Enumeration: Instruction prefetch enable(IPFEN)
//
//  IPFEN[1:0] Meaning of Value
//  ========== ==============================================================
//          0 No prefetching is triggered by a instruction read access
//          1 Prefetching may be triggered by any instruction read access
//===========================================================================
typedef enum FLASH_BIUCR_IPFEN_Tag
{
   FLASH_BIUCR_IPFEN_NO_PREFETCH,
   FLASH_BIUCR_IPFEN_PREFETCH_BY_ANY_READ
}  FLASH_BIUCR_IPFEN_T;
//===========================================================================
//  Enumeration: Line Buffer Configuration
//
//  LBCFG[1:0] Meaning of Value
//  ========= ===============================================================
//         00 All four buffers are available for any flash access
//         01 Reserved
//         10 Buffers 0 and 1 allocated for instruction fetches and
//            buffers 2 and 3 for data accesses.
//         11 Buffers 0,1,2 allocated for instruction fetches and buffer
//            3 for data accesses
//===========================================================================
typedef enum FLASH_BIUCR2_LINE_BUFFER_Tag
{
   FLASH_BIUCR2_ALL_BUFFERS_FOR_FLASH_ACCESS,
   FLASH_BIUCR2_RESERVED,
   FLASH_BIUCR2_BUFFER_0_1_INSTR_2_3_DATA,
   FLASH_BIUCR2_BUFFER_0_1_2_INSTR_3_DATA
   
}  FLASH_BIUCR2_LINE_BUFFER_T;



//===========================================================================
//  Enumeration: Location of each field in FLASH_BIUAPR
//  Flash Bus Interface Unit Control Register
//
//  Note: The location is for configuration of FLASH_BIU_INIT_RUNMODE,
//        not a physical location.
//===========================================================================
typedef enum FLASH_BIUAPR_Position_Tag
{
   FLASH_BIUAPR_POSITION_M0AP =  21,  // @emem [22:21] MCU core access flash
   FLASH_BIUAPR_POSITION_M4AP =  23,  // @emem [24:23] eDMA access flash
   FLASH_BIUAPR_POSITION_M1AP =  25,  // @emem [26:25] MCU core load store flash
   FLASH_BIUAPR_POSITION_M6AP =  27,  // @emem [28:27] Flexray access flash
   FLASH_BIUAPR_POSITION_M8AP =  29   // @emem [30:29] Nexus access flash

} FLASH_BIUAPR_Position_T;

//===========================================================================
//  Enumeration: Width of each field in FLASH_BIUCR
//  Flash Bus Interface Unit Control Register
//===========================================================================
typedef enum FLASH_BIUAPR_Width_Tag
{
   FLASH_BIUAPR_WIDTH_M0AP  = 2,   // @emem [22:21] MCU core access flash
   FLASH_BIUAPR_WIDTH_M4AP  = 2,   // @emem [24:23] eDMA access flash
   FLASH_BIUAPR_WIDTH_M1AP  = 2,   // @emem [26:25] MCU core load store flash
   FLASH_BIUAPR_WIDTH_M6AP  = 2,   // @emem [28:27] Flexray access flash
   FLASH_BIUAPR_WIDTH_M8AP =  2    // @emem [30:29] Nexus access flash

} FLASH_BIUAPR_Width_T;

typedef enum FLASH_Device_Configuration_Width_Tag
{
   FLASH_CONFIGURATION_WIDTH_INDEX  = 1   // @emem 30 MCU core access flash
   
} FLASH_Device_Configuration_Width_T;

typedef enum FLASH_Device_Configuration_Position_Tag
{
   FLASH_CONFIGURATION_POSITION_INDEX  = 31   // @emem 30 MCU core access flash   
   
} FLASH_Device_Configuration_Position_T;

typedef enum
{
   FLASH_DEVICE_A,
   FLASH_DEVICE_B,
   FLASH_INDEX_MAX
   
} FLASH_INDEX_T;

//===========================================================================
//  Enumeration: Access Protection(MnAP)
//
//  MnAP[1:0] Meaning of Value
//  ========= ===============================================================
//         00  No accesses may be performed by this master
//         01  Only read accesses may be performed by this master
//         10  Only write accesses may be performed by this master
//         11  Read and write accesses may be performed by this master
//===========================================================================
typedef enum FLASH_BIUAPR_MASTER_AP_Tag
{
   FLASH_BIUCR_MASTER_AP_NO_ACCESS,
   FLASH_BIUCR_MASTER_AP_READ_ACCESS_ONLY,
   FLASH_BIUCR_MASTER_AP_WRITE_ACCESS_ONLY,
   FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS
}  FLASH_BIUAPR_MASTER_AP_T;


//===========================================================================
//  Exported Function Prototypes
//===========================================================================

//===========================================================================
//  Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================


typedef enum FLASH_Run_Mode_Tag
{
   FLASH_RUN_MODE_NORMAL,
   FLASH_RUN_MODE_REPROGRAMMING
} FLASH_Run_Mode_T;


#endif // DD_FLASH_H

