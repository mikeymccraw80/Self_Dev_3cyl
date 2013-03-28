#ifndef DD_TPU_H
#define DD_TPU_H

#include "hw_tpu.h"
#include "hw_etpu_ucode.h"


//=============================================================================
// @globalv TPU_T | TPU |
// The Register Memory Overlay of the Enhanced Time Processing Unit
// to provide software access and debug information.
//
// @end
//=============================================================================
#define SECTION_TPU_REGISTER
#include "section.h"
extern TPU_T           TPU;
#define SECTION_END
#include "section.h"

#define TPU_NUMBER_OF_ENGINES       1
#define TPU_ENGINE_1                0
#define TPU_ENGINE_2                1


#define CAUSE_OF_EXCEPTION_CLEAR    (0xff)

#define TPU_SDM_START(index)        ( (index == 2) ? 0xC3E28000 : 0xC3FC8000 )

//SDM size is 3K
#define TPU_SDM_SIZE(index)         ( (index == 2) ? 0x00000C00 : 0x00000C00 )

#define MAX_HSR_LOOP_COUNT (128000)

#define TPU_SDM_BLOCK_ALIGN( start )                                        \
   (((uint32_t)(((start) + 7) / 8)) * 8)


//=============================================================================
// /-----------------------------------------------------------------------\
//  TPU DEVICE Configuration
// \-----------------------------------------------------------------------/
//=============================================================================

typedef enum
{
   TPU_KEEP_GLOBAL_EXCEPTION,      //@emem Keep global exception request and status bits ILFA, ILFB, MGEA, MGEB, and SCMMISF as is.
   TPU_NEGATE_GLOBAL_EXCEPTION     //@enum Negate global exception
}  TPU_Global_Exce_Clear_T;


typedef enum
{
   TPU_MISC_OPERATION_DISABLED,    //@emem MISC operation disabled.
   TPU_MISC_OPERATION_ENABLED      //@enum MISC operation enabled.
}TPU_SCM_MISC_Enable_T;



typedef enum
{
   TPU_SCM_NOT_VISIBLE,    //@emem SCM is not visible to the IP bus.
   TPU_SCM_VISIBLE         //@enum SCM is visible to the IP bus.
}TPU_SCM_Visibility_Bit_T;


typedef enum
{
   TPU_DISABLE_TIME_BASE,    //@emem time bases in both engines are disabled to run.
   TPU_ENABLE_TIME_BASE      //@enum time bases in both eTPU engines and eMIOS are enabled to run.
}TPU_Global_TB_Enable_T;



//=============================================================================
// /-----------------------------------------------------------------------\
//  TPU ECR Register Configuration
// \-----------------------------------------------------------------------/
//=============================================================================

typedef enum
{
   TPU_NORMAL_OPERATION,  //@emem Normal Operation
   TPU_ENABLE_FORCE_END   //@emem Puts engine in Reset
}  TPU_Force_End_T;



typedef enum
{
   TPU_ENGINE_RUNING,         //@emem Normal Operation
   TPU_STOP_ENGINE_CLOCKS   //@emem Commands Engine to stop its clocks
}  TPU_Module_Disable_Stop_T;


typedef enum
{
   TPU_SYSTEM_CLOCK_2,         //@emem Sample on System Clock Divided by:2
   TPU_SYSTEM_CLOCK_4,         //@emem Sample on System Clock Divided by:4
   TPU_SYSTEM_CLOCK_8,         //@emem Sample on System Clock Divided by:8
   TPU_SYSTEM_CLOCK_16,        //@emem Sample on System Clock Divided by:16
   TPU_SYSTEM_CLOCK_32,        //@emem Sample on System Clock Divided by:32
   TPU_SYSTEM_CLOCK_64,        //@emem Sample on System Clock Divided by:64
   TPU_SYSTEM_CLOCK_128,       //@emem Sample on System Clock Divided by:128
   TPU_SYSTEM_CLOCK_256        //@emem Sample on System Clock Divided by:256
}  TPU_Filter_Prescaler_Clk_T;


typedef enum
{
   TPU_2_SAMPLE_MODE,             //@emem Two Sample Mode
   TPU_RESERVED,                  //@enum reserved
   TPU_3_SAMPLE_MODE,             //@emem Three Sample Mode
   TPU_CONTINUOUS_SAMPLE_MODE     //@emem Continuous Sample Mode
}  TPU_Channel_Filter_Control_T;

#define TPU_ENTRY_TABLE_BASE_ADDRESS    (ETPU_ENTRYTABLE_ADDRESS/0x800)


typedef enum
{
   TPU_USE_SYSTEM_CLK_DIV_BY2,
   TPU_USE_SYSTEM_CLK
} TPU_Channel_Filter_Clock_Source_Selection_T;


typedef enum
{
   TPU_SCHEDULER_PRIORITY_ENABLED,
   TPU_SCHEDULER_PRIORITY_DISABLED
} TPU_Scheduler_priority_disable_T;


typedef enum
{
   TPU_WDT_DISABLED,
   TPU_WDT_RESERVED,
   TPU_THREAD_LENGTH,
   TPU_BUSY_LENGTH

} TPU_Watchdog_mode_T;


//=============================================================================
// /-----------------------------------------------------------------------\
// |                     TPU Device Configuration
// \-----------------------------------------------------------------------/
//=============================================================================

// @enum TPU_Device_Configuration_Width_T | Defines width for extract and insertion of the channel configuration 
typedef enum
{
   TPU_DEVICE_CONFIGURATION_WIDTH_INDEX                    =  2  // @emem [23:22] Device Index


}  TPU_Device_Configuration_Width_T;

// @enum TPU_Device_Configuration_Position_T | Defines position for extract and insertion of the channel configuration
typedef enum
{
   TPU_DEVICE_CONFIGURATION_POSITION_INDEX                 = 22  // @emem [23:22] Device Index

}  TPU_Device_Configuration_Position_T;

                                       
//=============================================================================
// /------------------------------------------------------------------------
// |                                Functions
// \------------------------------------------------------------------------
//=============================================================================

//
// Defined by the uCode set
//


typedef enum
{
   TPU_OFF_OUTPUT_DISABLE, // @emem Output is 0 (0v) when active, 1 (5v,3.3v) when inactive.
   TPU_ON_ACTIVE_HIGH // @emem Output is 1 (5v,3.3v) when active, 0 (0v) when inactive.
}  TPU_Polarity_T;



// @enum TPU_Channel_Priority_T | Defines the priority for a given channel..
typedef enum
{
   TPU_CHANNEL_PRIORITY_DISABLED,   // @emem
   TPU_CHANNEL_PRIORITY_LOW,        // @emem
   TPU_CHANNEL_PRIORITY_MEDIUM,     // @emem
   TPU_CHANNEL_PRIORITY_HIGH        // @emem

}  TPU_Channel_Priority_T;


typedef enum
{
   TPU_TRANSFER_REQUEST_DISABLE, // @emem 
   TPU_TRANSFER_REQUEST_ENABLE   // @emem
}  TPU_Transfer_Request_T;


typedef enum
{
   TPU_CHANNEL_INTERRUPT_DISABLE, // @emem 
   TPU_CHANNEL_INTERRUPT_ENABLE   // @emem 
}  TPU_Channel_Interrupt_T;


typedef enum
{
   TPU_TCR1_TIME_BASE, // @emem 
   TPU_TCR2_TIME_BASE   // @emem 
}  TPU_Time_Base_T;


// @enum TPU_Channel_T | Defines the tpu channel number for the configuration 
typedef enum
{
   TPU_CHANNEL_0,    // @emem Tpu Channel  0
   TPU_CHANNEL_1,    // @emem Tpu Channel  1
   TPU_CHANNEL_2,    // @emem Tpu Channel  2
   TPU_CHANNEL_3,    // @emem Tpu Channel  3
   TPU_CHANNEL_4,    // @emem Tpu Channel  4
   TPU_CHANNEL_5,    // @emem Tpu Channel  5
   TPU_CHANNEL_6,    // @emem Tpu Channel  6
   TPU_CHANNEL_7,    // @emem Tpu Channel  7
   TPU_CHANNEL_8,    // @emem Tpu Channel  8
   TPU_CHANNEL_9,    // @emem Tpu Channel  9
   TPU_CHANNEL_10,   // @emem Tpu Channel 10
   TPU_CHANNEL_11,   // @emem Tpu Channel 11
   TPU_CHANNEL_12,   // @emem Tpu Channel 12
   TPU_CHANNEL_13,   // @emem Tpu Channel 13
   TPU_CHANNEL_14,   // @emem Tpu Channel 14
   TPU_CHANNEL_15,   // @emem Tpu Channel 15
   TPU_CHANNEL_16,   // @emem Tpu Channel 16
   TPU_CHANNEL_17,   // @emem Tpu Channel 17
   TPU_CHANNEL_18,   // @emem Tpu Channel 18
   TPU_CHANNEL_19,   // @emem Tpu Channel 19
   TPU_CHANNEL_20,   // @emem Tpu Channel 20
   TPU_CHANNEL_21,   // @emem Tpu Channel 21
   TPU_CHANNEL_22,   // @emem Tpu Channel 22
   TPU_CHANNEL_23,   // @emem Tpu Channel 23
   TPU_CHANNEL_24,   // @emem Tpu Channel 24
   TPU_CHANNEL_25,   // @emem Tpu Channel 25
   TPU_CHANNEL_26,   // @emem Tpu Channel 26
   TPU_CHANNEL_27,   // @emem Tpu Channel 27
   TPU_CHANNEL_28,   // @emem Tpu Channel 28
   TPU_CHANNEL_29,   // @emem Tpu Channel 29
   TPU_CHANNEL_30,   // @emem Tpu Channel 30
   TPU_CHANNEL_31,   // @emem Tpu Channel 31
   TPU_CHANNEL_MAX   // @emem this value is 32, the largest value for the channel parameter

}  TPU_Channel_T;

typedef enum
{
   TPU_SYNCHRONUS_UPDATE, // @emem 
   TPU_COHERENT_UPDATE    // @emem 
}  TPU_PWM_Update_Type_T;


typedef enum
{
   TPU_EVENT_ABSOLUTE,
   TPU_EVENT_RELATIVE,
   TPU_EVENT_FALLING_EDGE_RELATIVE,
   TPU_EVENT_RISING_EDGE_RELATIVE
}  TPU_Event_T;


//=============================================================================
// /-----------------------------------------------------------------------\
// |                     TPU Timer Configuration
// \-----------------------------------------------------------------------/
//=============================================================================



typedef enum 
{
   TPU_TCR2_GATED_DIV_8,                        // @enum system Clock/8
   TPU_TCR2_RISE_TRANSITION_INC_TCR2,           // @enum Rise transition on TCRCLK signal increments TCR2.
   TPU_TCR2_FALL_TRANSITION_INC_TCR2,           // @enum Fall transition on TCRCLK signal increments TCR2.
   TPU_TCR2_RISE_OR_FALL_TRANSITION_INC_TCR2,   // @enum Rise or Fall transition on TCRCLK signal increments TCR2.
   TPU_TCR2_DIV_8_CLOCK,                        // @enum DIV8 clock (system clock / 8)
   TPU_TCR2_RESERVED_1 = 5,
   TPU_TCR2_RESERVED_2 = 6,
   TPU_TCR2_SHUTDOWN                            // @enum DIV8 clock (system clock / 8)
} TPU_TCR2_Clock_Source_T;


typedef enum 
{
   TPU_TBCR_2SAMPL_SYSCLK_DIV2 = 0,    //enum@ system clock divided by 2
   TPU_TBCR_2SAMPL_FLTRCLK_CHAN,       //enum@ filter clock of the channels
   TPU_TBCR_INTGRTN_SYSCLK_DIV2,       //enum@ system clock divided by 2
   TPU_TBCR_INTGRTN_FLTRCLK_CHAN       //enum@ ffilter clock of the channels
}  TPU_TBCR_Filter_Control_T;


typedef enum 
{
   TPU_TCR2_ANGLE_CLOCK_MODE_DISABLED = 0,   //enum@ TPU Angle Clock Mode Disabled
   TPU_TCR2_ANGLE_CLOCK_MODE_ENABLED = 1,    //enum@ TPU Angle Clock Mode Enabled
   TPU_TCR2_ANGLE_TICKS_TCRCLK_INPUT = 1,    //enum@ TCR2 Angle Ticks TCRCLK Input
   TPU_TCR2_ANGLE_TICKS_CHANNEL1_INPUT = 2,  //enum@ TCR2 Angle Ticks Channel1 Input
   TPU_TCR2_ANGLE_TICKS_CHANNEL2_INPUT = 3  //enum@ TCR2 Angle Ticks Channel2 Input
}  TPU_Angle_mode_Selection_T;



typedef enum 
{
   TPU_TCR1_TCRCLK_CLK = 0,                // @enum Selects TCRCLK as clock source
   TPU_TCR1_PERIPHERAL_TIME_BASE_CLK = 2,  // @enum Selects Peripheral Time Base Clock
   TPU_TCR1_SYSCLK_DIV2_CLK = 4 ,          // @enum Sytem clock divided by 2 
   TPU_TCR1_SYS_CLK = 5,                   // @enum System Clock
   TPU_TCR1_FREEZE = 6                     // @enum TCR1 Freeze
} TPU_TCR1_Clock_Source_T;

typedef enum 
{
   TPU_TCR1_SHUTDOWN = 3              // @enum Shuts down TCR1 clock
} TPU_TCR1_Clock_Control_T;


//
typedef enum 
{
   TPU_SERVER_CLIENT_OPERATION_DISABLE,         // @enum Disbles Sever/Client operation for resource 1
   TPU_SERVER_CLIENT_OPERATION_ENABLE           // @enum Enables Sever/Client operation for resource 1
} TPU_STAC_Server_Client_Operation_T;

typedef enum 
{
   TPU_RESOURCE_CLIENT_OPERATION,         // @enum Resource Client operation
   TPU_RESOURCE_SERVER_OPERATION          // @enum Enables Sever/Client operation for resource 1
} TPU_STAC_Server_Client_Assignment_T;


typedef enum ETPU_REDCR_SRV_Tag
{
   TPU_RESOURCE_SERVER_TCR1A = 0,
   TPU_RESOURCE_SERVER_TCR1B,
   TPU_RESOURCE_SERVER_TCR2A,
   TPU_RESOURCE_SERVER_TCR2B
} TPU_Resource_Server_T;


// parameter_width TPU_SDM_Read_Coherent_Data and TPU_SDM_Write_Coherent_Data
#define TRANSFER_32_BIT (1)
#define TRANSFER_24_BIT (0)



//  Exported preprocessor #define constants (object-like macros)
#define TPU_GLOBAL_ADDRESS(index) (TPU_SDM_START(index) + GLOBAL_CAUSE_OF_EXCEPTION)
#define TPU_GLOBAL_RAM(index)\
   (*( volatile struct TPU_GLOBAL_RAM_tag *) TPU_GLOBAL_ADDRESS(index) )

#define ENGINE_GLOBAL_ADDRESS(index) (TPU_SDM_START(index) + GLOBAL_PEPPE_ENGINE_DATA - 1)
#define ENGINE_GLOBAL_RAM(index)\
   (*( volatile struct ENGINE_GLOBAL_RAM_Tag *) ENGINE_GLOBAL_ADDRESS(index) )

#define MPTACE_GLOBAL_ADDRESS(index) (TPU_SDM_START(index) + GLOBAL_MPTACE_EXTRA_PULSES)
#define MPTACE_GLOBAL_RAM(index)\
   (*( volatile struct MPTACE_GLOBAL_RAM_Tag *) MPTACE_GLOBAL_ADDRESS(index) )

#define CAME_GLOBAL_ADDRESS(index) (TPU_SDM_START(index) + GLOBAL_CAME_MIN_PER - 1)
#define CAME_GLOBAL_RAM(index)\
   (*( volatile struct CAME_GLOBAL_RAM_Tag *) CAME_GLOBAL_ADDRESS(index) )

#define DESFIE_GLOBAL_ADDRESS(index) (TPU_SDM_START(index) + GLOBAL_DESFIE_NORMAL_OFFSET - 1)
#define DESFIE_GLOBAL_RAM(index)\
   (*( volatile struct DESFIE_GLOBAL_RAM_Tag *) DESFIE_GLOBAL_ADDRESS(index) )

// ------------------------ GLOBAL ETPU RAM STRUCTURE ------------------------
typedef struct TPU_GLOBAL_RAM_tag
{
   uint8_t           Cause_Of_Exception;
   uint8_t           Tach_Chan_Number;
   uint8_t           Cam_Chan_Number;
   uint8_t           DIG_Chan_Number;

} TPU_GLOBAL_RAM_T;

// ------------------------ ENGINE GLOBAL RAM STRUCTURE ----------------------
typedef struct pEPPE_Engine_Data_F_Tag
{
   bitfield32_t             : 8;
   bitfield32_t pEPPE       : 24;
} pEPPE_Engine_Data_F_T;

typedef union pEPPE_Engine_Data_Tag
{
   pEPPE_Engine_Data_F_T           F;
   uint32_t                        U32;
} pEPPE_Engine_Data_T;

typedef struct pDESFIE_Engine_Data_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t pDESFIE            : 24;
} pDESFIE_Engine_Data_F_T;

typedef union pDESFIE_Engine_Data_Tag
{
   pDESFIE_Engine_Data_F_T         F;
   uint32_t                        U32;
} pDESFIE_Engine_Data_T;

typedef struct ENGINE_GLOBAL_RAM_F_Tag
{
   pEPPE_Engine_Data_T             pEPPE_Engine_Data;
   pDESFIE_Engine_Data_T           pDESFIE_Engine_Data;

} ENGINE_GLOBAL_RAM_F_T;

typedef struct ENGINE_GLOBAL_RAM_Tag
{
   ENGINE_GLOBAL_RAM_F_T           F;
} ENGINE_GLOBAL_RAM_T;

// ------------------------ MPTACE GLOBAL RAM STRUCTURE ----------------------
typedef struct MPTACE_On_Time_2_F_Tag
{
   bitfield32_t Extra_Pulses       : 8;
   bitfield32_t zeroed_bit         : 1;
   bitfield32_t On_Time_2          : 23;
} MPTACE_On_Time_2_F_T;

typedef union MPTACE_On_Time_2_Tag
{
   MPTACE_On_Time_2_F_T            F;
   uint32_t                        U32;
} MPTACE_On_Time_2_T;

typedef struct MPTACE_Off_Time_2_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t zeroed_bit         : 1;
   bitfield32_t Off_Time_2         : 23;
} MPTACE_Off_Time_2_F_T;

typedef union MPTACE_Off_Time_2_Tag
{
   MPTACE_Off_Time_2_F_T           F;
   uint32_t                        U32;

} MPTACE_Off_Time_2_T;

typedef struct MPTACE_On_Time_3_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t zeroed_bit         : 1;
   bitfield32_t On_Time_3          : 23;
} MPTACE_On_Time_3_F_T;

typedef union MPTACE_On_Time_3_Tag
{
   MPTACE_On_Time_3_F_T            F;
   uint32_t                        U32;
} MPTACE_On_Time_3_T;

typedef struct MPTACE_GLOBAL_RAM_F_Tag
{
   MPTACE_On_Time_2_T              On_Time_2;
   MPTACE_Off_Time_2_T             Off_Time_2;
   MPTACE_On_Time_3_T              On_Time_3;

} MPTACE_GLOBAL_RAM_F_T;

typedef struct MPTACE_GLOBAL_RAM_Tag
{
   MPTACE_GLOBAL_RAM_F_T           F;
} MPTACE_GLOBAL_RAM_T;

// ------------------------ CAME GLOBAL RAM STRUCTURE ------------------------
typedef struct CAME_Min_Period_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Min_Period         : 24;
} CAME_Min_Period_F_T;

typedef union CAME_Min_Period_Tag
{
   CAME_Min_Period_F_T             F;
   uint32_t                        U32;
} CAME_Min_Period_T;

typedef struct CAME_Rep_Out_ChanNum_LagTime_F_Tag
{
   bitfield32_t Rep_Out_Chan_Num   : 8;
   bitfield32_t Rep_Out_Lag_Time   : 24;
} CAME_Rep_Out_ChanNum_LagTime_F_T;

typedef union CAME_Rep_Out_ChanNum_LagTime_Tag
{
   CAME_Rep_Out_ChanNum_LagTime_F_T  F;
   uint32_t                          U32;

} CAME_Rep_Out_ChanNum_LagTime_T;

typedef struct CAME_GLOBAL_RAM_F_Tag
{
   CAME_Min_Period_T                 Min_Period;
   CAME_Rep_Out_ChanNum_LagTime_T    Rep_Out_Info;

} CAME_GLOBAL_RAM_F_T;


typedef struct CAME_GLOBAL_RAM_Tag
{
   CAME_GLOBAL_RAM_F_T              F;
} CAME_GLOBAL_RAM_T;

// ------------------------ DESFIE GLOBAL RAM STRUCTURE ----------------------
typedef struct DESFIE_Normal_Offset_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Normal_Offset      : 24;

} DESFIE_Normal_Offset_F_T;

typedef union DESFIE_Normal_Offset_Tag
{
   DESFIE_Normal_Offset_F_T        F;
   uint32_t                        U32;
} DESFIE_Normal_Offset_T;

typedef struct DESFIE_Trim_Offset_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Trim_Offset        : 24;

} DESFIE_Trim_Offset_F_T;

typedef union DESFIE_Trim_Offset_Tag
{
   DESFIE_Trim_Offset_F_T          F;
   uint32_t                        U32;

} DESFIE_Trim_Offset_T;

typedef struct DESFIE_Kinj_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Kinj               : 24;

} DESFIE_Kinj_F_T;

typedef union DESFIE_Kinj_Tag
{
   DESFIE_Kinj_F_T                 F;
   uint32_t                        U32;

} DESFIE_Kinj_T;

typedef struct DESFIE_Min_Inj_Off_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Min_Inj_Off        : 24;

} DESFIE_Min_Inj_Off_F_T;

typedef union DESFIE_Min_Inj_Off_Tag
{
   DESFIE_Min_Inj_Off_F_T          F;
   uint32_t                        U32;

} DESFIE_Min_Inj_Off_T;

typedef struct DESFIE_Min_Trim_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Min_Trim           : 24;

} DESFIE_Min_Trim_F_T;

typedef union DESFIE_Min_Trim_Tag
{
   DESFIE_Min_Trim_F_T             F;
   uint32_t                        U32;
} DESFIE_Min_Trim_T;

typedef struct DESFIE_Edge_Time_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Edge_Time          : 24;

} DESFIE_Edge_Time_F_T;

typedef union DESFIE_Edge_Time_Tag
{
   DESFIE_Edge_Time_F_T            F;
   uint32_t                        U32;

} DESFIE_Edge_Time_T;

typedef struct DESFIE_Edge_Count_F_Tag
{
   bitfield32_t                    : 16;
   bitfield32_t Edge_Count         : 16;

} DESFIE_Edge_Count_F_T;

typedef union DESFIE_Edge_Count_Tag
{
   DESFIE_Edge_Count_F_T           F;
   uint32_t                        U32;

} DESFIE_Edge_Count_T;

typedef struct DESFIE_Period_F_Tag
{
   bitfield32_t                    : 8;
   bitfield32_t Period             : 24;

} DESFIE_Period_F_T;

typedef union DESFIE_Period_Tag
{
   DESFIE_Period_F_T               F;
   uint32_t                        U32;

} DESFIE_Period_T;

typedef struct DESFIE_GLOBAL_RAM_F_Tag
{
   DESFIE_Normal_Offset_T          Normal_Offset;
   DESFIE_Trim_Offset_T            Trim_Offset;
   DESFIE_Kinj_T                   Kinj;
   DESFIE_Min_Inj_Off_T            Min_Inj_Off;
   DESFIE_Min_Trim_T               Min_Trim;
   DESFIE_Edge_Time_T              Edge_Time;
   DESFIE_Edge_Count_T             Edge_Count;
   DESFIE_Period_T                 Period;

} DESFIE_GLOBAL_RAM_F_T;


typedef struct DESFIE_GLOBAL_RAM_Tag
{
   DESFIE_GLOBAL_RAM_F_T           F;
} DESFIE_GLOBAL_RAM_T;

//=============================================================================
// Channle SDM start Address definition macros
// 1. Determine the 
//
//=============================================================================

//#ifndef TPU_A_CHANNEL_00_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_00_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_01_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_01_INIT_SDM_SIZE    0
//#endif
#ifndef TPU_A_CHANNEL_02_INIT_SDM_SIZE
#define TPU_A_CHANNEL_02_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_03_INIT_SDM_SIZE
#define TPU_A_CHANNEL_03_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_04_INIT_SDM_SIZE
#define TPU_A_CHANNEL_04_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_05_INIT_SDM_SIZE
#define TPU_A_CHANNEL_05_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_06_INIT_SDM_SIZE
#define TPU_A_CHANNEL_06_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_07_INIT_SDM_SIZE
#define TPU_A_CHANNEL_07_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_08_INIT_SDM_SIZE
#define TPU_A_CHANNEL_08_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_09_INIT_SDM_SIZE
#define TPU_A_CHANNEL_09_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_10_INIT_SDM_SIZE
#define TPU_A_CHANNEL_10_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_11_INIT_SDM_SIZE
#define TPU_A_CHANNEL_11_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_12_INIT_SDM_SIZE
#define TPU_A_CHANNEL_12_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_13_INIT_SDM_SIZE
#define TPU_A_CHANNEL_13_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_14_INIT_SDM_SIZE
#define TPU_A_CHANNEL_14_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_15_INIT_SDM_SIZE
#define TPU_A_CHANNEL_15_INIT_SDM_SIZE    0
#endif
//#ifndef TPU_A_CHANNEL_16_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_16_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_17_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_17_INIT_SDM_SIZE    0
//#endif
#ifndef TPU_A_CHANNEL_18_INIT_SDM_SIZE
#define TPU_A_CHANNEL_18_INIT_SDM_SIZE    0
#endif
//#ifndef TPU_A_CHANNEL_19_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_19_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_20_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_20_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_21_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_21_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_22_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_22_INIT_SDM_SIZE    0
//#endif
#ifndef TPU_A_CHANNEL_23_INIT_SDM_SIZE
#define TPU_A_CHANNEL_23_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_24_INIT_SDM_SIZE
#define TPU_A_CHANNEL_24_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_25_INIT_SDM_SIZE
#define TPU_A_CHANNEL_25_INIT_SDM_SIZE    0
#endif
//#ifndef TPU_A_CHANNEL_26_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_26_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_27_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_27_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_28_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_28_INIT_SDM_SIZE    0
//#endif
//#ifndef TPU_A_CHANNEL_29_INIT_SDM_SIZE
//#define TPU_A_CHANNEL_29_INIT_SDM_SIZE    0
//#endif
#ifndef TPU_A_CHANNEL_30_INIT_SDM_SIZE
#define TPU_A_CHANNEL_30_INIT_SDM_SIZE    0
#endif
#ifndef TPU_A_CHANNEL_31_INIT_SDM_SIZE
#define TPU_A_CHANNEL_31_INIT_SDM_SIZE    0
#endif

#define TPU_SDM_BASE \
   TPU_SDM_BLOCK_ALIGN( TPU_SDM_START(TPU_INDEX_0) + ETPU_PRAM_START_OFFSET )


#define TPU_A_CHANNEL_00_SDM_BLOCK_START TPU_SDM_BASE
#define TPU_A_CHANNEL_01_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_00_SDM_BLOCK_START + TPU_A_CHANNEL_00_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_02_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_01_SDM_BLOCK_START + TPU_A_CHANNEL_01_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_03_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_02_SDM_BLOCK_START + TPU_A_CHANNEL_02_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_04_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_03_SDM_BLOCK_START + TPU_A_CHANNEL_03_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_05_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_04_SDM_BLOCK_START + TPU_A_CHANNEL_04_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_06_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_05_SDM_BLOCK_START + TPU_A_CHANNEL_05_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_07_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_06_SDM_BLOCK_START + TPU_A_CHANNEL_06_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_08_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_07_SDM_BLOCK_START + TPU_A_CHANNEL_07_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_09_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_08_SDM_BLOCK_START + TPU_A_CHANNEL_08_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_10_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_09_SDM_BLOCK_START + TPU_A_CHANNEL_09_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_11_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_10_SDM_BLOCK_START + TPU_A_CHANNEL_10_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_12_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_11_SDM_BLOCK_START + TPU_A_CHANNEL_11_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_13_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_12_SDM_BLOCK_START + TPU_A_CHANNEL_12_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_14_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_13_SDM_BLOCK_START + TPU_A_CHANNEL_13_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_15_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_14_SDM_BLOCK_START + TPU_A_CHANNEL_14_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_16_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_15_SDM_BLOCK_START + TPU_A_CHANNEL_15_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_17_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_16_SDM_BLOCK_START + TPU_A_CHANNEL_16_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_18_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_17_SDM_BLOCK_START + TPU_A_CHANNEL_17_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_19_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_18_SDM_BLOCK_START + TPU_A_CHANNEL_18_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_20_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_19_SDM_BLOCK_START + TPU_A_CHANNEL_19_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_21_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_20_SDM_BLOCK_START + TPU_A_CHANNEL_20_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_22_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_21_SDM_BLOCK_START + TPU_A_CHANNEL_21_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_23_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_22_SDM_BLOCK_START + TPU_A_CHANNEL_22_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_24_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_23_SDM_BLOCK_START + TPU_A_CHANNEL_23_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_25_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_24_SDM_BLOCK_START + TPU_A_CHANNEL_24_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_26_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_25_SDM_BLOCK_START + TPU_A_CHANNEL_25_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_27_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_26_SDM_BLOCK_START + TPU_A_CHANNEL_26_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_28_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_27_SDM_BLOCK_START + TPU_A_CHANNEL_27_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_29_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_28_SDM_BLOCK_START + TPU_A_CHANNEL_28_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_30_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_29_SDM_BLOCK_START + TPU_A_CHANNEL_29_INIT_SDM_SIZE )
#define TPU_A_CHANNEL_31_SDM_BLOCK_START \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_30_SDM_BLOCK_START + TPU_A_CHANNEL_30_INIT_SDM_SIZE )

#define TPU_SDM_END \
   TPU_SDM_BLOCK_ALIGN( TPU_A_CHANNEL_31_SDM_BLOCK_START + TPU_A_CHANNEL_31_INIT_SDM_SIZE )



typedef struct TPU_CHANNEL_Configuration_F_Tag
{


   bitfield32_t  TPU_CHANNEL_CONFIGURATION_EVENT_TYPE :  BIT_2;   //  [31:30] Event Type
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_PWM_UPDATE_MODE :  BIT_1;//      [29] PWM Update Mode 1- Coherent,0- synchronus
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_REFERNCE_CHANNEL  :  BIT_5;//   [28:24] Refernce channel number
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_CHANNEL  :  BIT_5;// [21:17] Channel
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE1 :  BIT_1;//16  Channel Function Mode1
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0 :  BIT_1 ; // 15  Channel Function Mode0
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_ETCS :  BIT_1 ; //14  Entry Table Condition Select
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_IREN :  BIT_1 ; //13  Interrupt Request Enable
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_TREN :  BIT_1 ; //12  Transfer Request Enable
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_CPR :  BIT_2 ; // [11:10] Channel Priority Index
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_POLARITY :  BIT_1; //  9  Active state of channel
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_OUTPUT_DISABLE :  BIT_1; //       8   Output Disable
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_HSR :  BIT_3 ; //  [ 7: 5] Host Service Request Type
   bitfield32_t  TPU_CHANNEL_CONFIGURATION_PRIMITIVE   :  BIT_5;//  [ 4: 0] TPU Primitives or Channel function Select
  
}  TPU_CHANNEL_Configuration_F_T;


typedef union TPU_CHANNEL_Configuration_Tag
{
   TPU_CHANNEL_Configuration_F_T          F;
   uint32_t             U32;

}  TPU_CHANNEL_Configuration_T;


//=============================================================================
// @enum TPU_Index_T | The Timer Processor Unit used by the configuration
//=============================================================================
typedef enum 
{
   TPU_INDEX_0,   // @emem 0x00
   TPU_INDEX_1,   // @emem 0x01
   TPU_INDEX_MAX  // @emem 0x02

}  TPU_Index_T;


//=============================================================================
// TPU_Get_Index_Group
//=============================================================================
#define TPU_Get_Index_Group(index) (index)

//===========================================================================
//Name:         TPU_Initialize_Channels                                  
//Purpose:      This interface will intialize the channels                      
// Parameters:  : IO_Configuration_T   in_configuration  Channel configuaration info.
//                                                                           
// Return Value: None                                                        
//=========================================================================
void TPU_Initialize_Channels( TPU_Index_T index);

//===========================================================================
//Name:         TPU_Initialize_Device                                  
//Purpose:      This function performs the power up initialization for the TPU 
//              modules. This function must be called before the specific 
//              primitives can be initialized.                               
// Parameters:  IO_Configuration: TPU configuration
//                                                                           
// Return Value: None                                                        
//=========================================================================
void TPU_Initialize_Device(void );


//===========================================================================
//Name:         TPU_Clear_Global_Exception                                  
//Purpose:      This routine will set flags based on the cause of exception.The
//              routine then clears the exception.                               
// Parameters:  in_context: 
//                                                                           
// Return Value: None                                                        
//=========================================================================
void TPU_Clear_Global_Exception(
   uint32_t in_context );

//=============================================================================
// TPU_Set_HSR
//
// @func  This function issues Host Service Requests on all initialized fuel 
// channels.  This function is used to minimize the clock cycles needed to 
// update the fuel channels based on new engine position data. 
// @parm IO_Configuration_T   in_configuration  Channel configuaration info.
//
// @parm uint8_t              hsr| HSR value
// @rdesc  none
// @end
//=============================================================================
void TPU_Set_HSR(
       TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure,
   uint8_t              in_hsr);


//=============================================================================
// TPU_Set_Function_Mode0
//
// @func    The function mode bits are used to select a alternate mode of operation
// for a eTPU primitive.  The effect of the FM bits are primitive specific. 
// @parm IO_Configuration_T   in_configuration  Channel configuaration info.
//
// @parm uint8_t              in_time_base| Select time base
// @rdesc  none
// @end
//=============================================================================
void TPU_Set_Function_Mode0(
       TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure,
   uint8_t              in_time_base);


//=============================================================================
// TPU_Set_Function_Mode1
//
// @func    The function mode bits are used to select a alternate mode of operation
// for a eTPU primitive.  The effect of the FM bits are primitive specific. 
// @parm IO_Configuration_T   in_configuration  Channel configuaration info.
//
// @parm uint8_t              in_function_mode1|Primitive specific
// @rdesc  none
// @end
//=============================================================================
void TPU_Set_Function_Mode1(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint8_t              in_function_mode1);

//=============================================================================
// TPU_Set_Static_Base_Address
// @func    The location of eTPU parameter RAM for a channel is configurable.  This
// interface is used by the primitive device drivers to set the start
// location of Shared data memory of the requested TPU and channel.
//
// @parm uint8_t        in_channel_sdm_address|Channel SDM address
// @rdesc  none
// @end
//=============================================================================
void TPU_Set_Static_Base_Address(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// TPU_Get_Static_Base_Address
// @func    The location of eTPU parameter RAM for a channel is configurable.  This
// interface is used by the primitive device drivers to get the start
// location of Shared data memory of the requested TPU and channel.
//
// @parm  none
// @rdesc  in_channel_sdm_address|Channel SDM address
// @end
//=============================================================================
uint32_t TPU_Get_Static_Base_Address(
   TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);

//=============================================================================
// TPU_Get_Channel_SDM_Start_Address
// @func    The location of eTPU parameter RAM for a channel is configurable.  This
// interface is used by the primitive device drivers to get the initial start
// location of Shared data memory as stored in ROM of the requested TPU and channel.
//
// @parm  none
// @rdesc  in_channel_sdm_address|Channel SDM address
// @end
//=============================================================================
uint32_t TPU_Get_Channel_SDM_Start_Address(
   TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);


//===========================================================================
//Name:         TPU_SDM_Read_Coherent_Data                                  
//Purpose:      This interface will coherently read two 32 or 24 bit
//              parameters to the TPU Shared Data memory                      
// Parameters:  : bool      parameter_width  -> TRANSFER_32_BIT or TRANSFER_24_BIT
//                uint32_t* parameter_0_ptr  -> pointer to parameter 0
//                uint32_t  parameter_0_data -> data to be Read to parameter 0
//                uint32_t* parameter_1_ptr  -> pointer to parameter 1
//                uint32_t  parameter_1_data -> data to be Read to parameter 1
//                                                                           
// Return Value: None                                                        
//=========================================================================
void TPU_SDM_Read_Coherent_Data( 
   bool      parameter_width,
   uint32_t* parameter_0_ptr,
   uint32_t* parameter_0_data,
   uint32_t* parameter_1_ptr,
   uint32_t* parameter_1_data );

//===========================================================================
//Name:         TPU_SDM_Write_Coherent_Data                                  
//Purpose:      This interface will coherently write two 32 or 24 bit
//              parameters to the TPU Shared Data memory                      
// Parameters:  : bool      parameter_width  -> TRANSFER_32_BIT or TRANSFER_24_BIT
//                uint32_t* parameter_0_ptr  -> pointer to parameter 0
//                uint32_t  parameter_0_data -> data to be written to parameter 0
//                uint32_t* parameter_1_ptr  -> pointer to parameter 1
//                uint32_t  parameter_1_data -> data to be written to parameter 1
//                                                                           
// Return Value: None                                                        
//=========================================================================

void TPU_SDM_Write_Coherent_Data(
   bool      parameter_width,
   uint32_t* parameter_0_ptr,
   uint32_t  parameter_0_data,
   uint32_t* parameter_1_ptr,
   uint32_t  parameter_1_data );


//===========================================================================
//Name:         TPU_Initialize_SCM_SDM                                  
//Purpose:      This function performs the power up initialization for the TPU 
//              SCM and SDM memory..                               
// Parameters:  IO_Configuration: TPU configuration
//                                                                           
// Return Value: None                                                        
//=========================================================================
void TPU_Initialize_SCM_SDM(void);
//=============================================================================
//  TPU_Wait_HSR_Request_Complete 
//=============================================================================
 void TPU_Wait_HSR_Request_Complete(
          TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure);
//=============================================================================
// @TPU_Get_SDM_Base_Address
// @func   This interface will get base address of SDM(Shared data memory)
//
// @parm    none.
//
// @rdesc  uint32_t SDM address
// @end
//=============================================================================
INLINE volatile uint32_t TPU_Get_SDM_Base_Address(
   TPU_Index_T  index )
{

   return (uint32_t)(&TPU.SDM);
}




#endif // DD_TPU_H
