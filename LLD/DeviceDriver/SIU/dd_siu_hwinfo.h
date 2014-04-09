#ifndef DD_SIU_HWINFO_H
#define DD_SIU_HWINFO_H

#include "reuse.h"


typedef struct SIU_RESET_Status 
{
   bitfield16_t Power_On_Reset          : 1;     // Last reset was an externally triggered power on reset
   bitfield16_t External_Reset          : 1;     // Last reset was an externally triggered exteranl reset
   bitfield16_t Loss_Lock_Reset         : 1;     // Last reset was an internally triggered loss of lock reset
   bitfield16_t Loss_Clock_Reset        : 1;     // Last reset was an internally triggered loss of clock reset
   bitfield16_t Watchdog_Reset          : 1;     // Last reset was a watchdog triggered reset
   bitfield16_t CheckStop_Reset         : 1;     // Last reset was a checkstop triggered reset
   bitfield16_t SoftwareWDTimer_Reset   : 1;     // Last reset was a Software Watchdog Timer Reset
   bitfield16_t SoftwareSystem_Reset    : 1;     // Last reset was a Software System Reset

   bitfield16_t SoftwareExternal_Reset  : 1;     // Software External Reset
   bitfield16_t                         : 7;     // Reserved
} HWIO_Reset_Status_T;

//===========================================================================
//  Exported preprocessor #define MACROS() (i.e., those using # or ##)
//===========================================================================
#define SIU_MIDR_ADDRESS       0xC3F90004
#define SIU_RSR_ADDRESS        0xC3F9000C

//===========================================================================
//    Exported Type Declarations (enum, struct, union, typedef)
//===========================================================================
typedef enum MCU_ID_Tag
{
   MPC5634 = 0x5634,
   MPC5644 = 0x5644
} MCU_ID_T;

typedef enum CPU_Info_Tag
{
   CPU_PROD,
   CPU_LCI,
   CPU_VERTICAL
} CPU_Info_T;


//===========================================================================
//    Exported Variables
//===========================================================================
extern CPU_Info_T CPU_Info;
extern HWIO_Reset_Status_T Reset_Status;

//===========================================================================
// Exported Inline Function Definitions and #define Function-Like Macros()
//===========================================================================
//determine the type of CPU, prod, LCI(instrument ECM) or VertiCal
INLINE CPU_Info_T SIU_Get_CPU_Information(void)
{
   CPU_Info_T return_code = CPU_PROD;
   volatile uint32_t * SIU_MID_Register = (volatile uint32_t *)SIU_MIDR_ADDRESS;

   if((MCU_ID_T)(*SIU_MID_Register>>16) == MPC5634)
   {
      if ((*SIU_MID_Register&0x8000) == 0)  //CSP code of MCU
      {
         return_code = CPU_PROD;
      }
      else
      {
         return_code = CPU_VERTICAL;
      }
   }

   if((MCU_ID_T)(*SIU_MID_Register>>16) == MPC5644)
   {
      return_code = CPU_LCI;
   }
   return return_code;
}

INLINE HWIO_Reset_Status_T SIU_RESET_Get_Status(void)
{
   HWIO_Reset_Status_T status;
   volatile uint32_t *SIU_RSR_Register = (volatile uint32_t *)SIU_RSR_ADDRESS;
   status.Power_On_Reset   = (*SIU_RSR_Register&0x80000000)?1:0;
   status.External_Reset   = (*SIU_RSR_Register&0x40000000)?1:0;
   status.Loss_Lock_Reset  = (*SIU_RSR_Register&0x20000000)?1:0;
   status.Loss_Clock_Reset = (*SIU_RSR_Register&0x10000000)?1:0;
   status.Watchdog_Reset   = (*SIU_RSR_Register&0x08000000)?1:0;
   status.CheckStop_Reset  = (*SIU_RSR_Register&0x04000000)?1:0;

   return status;
}

#endif

