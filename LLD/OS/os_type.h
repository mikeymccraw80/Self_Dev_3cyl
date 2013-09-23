#ifndef OS_TYPE_H
#define OS_TYPE_H

//=============================================================================
// include files
//=============================================================================
#include "reuse.h"

//=============================================================================
// type define
//=============================================================================
typedef union
{
   struct
   {
      uint8_t TimeFor1ms     : 1 ;
      uint8_t TimeFor2ms     : 1 ;
      uint8_t TimeFor5ms     : 1 ;
      uint8_t TimeFor10ms   : 1 ;
      uint8_t Unused                : 5 ;
   } bf;
   uint8_t byte;
} RtiFlagsType ;

//=============================================================================
// extern variables
//=============================================================================
extern RtiFlagsType RTI_Flags;

/*===========================================================================*\
 * Constant Definitions, this parameter is used for calculate average time
\*===========================================================================*/
#define TIMEMEASURE_PARAMETER             ( 5 )

/*===========================================================================*\
 * Enumeration Definitions For Throughput Data
\*===========================================================================*/
typedef enum {
    CeOSTK_SEG_1msLOOP,
    CeOSTK_SEG_2msLOOP,
    CeOSTK_SEG_5msLOOP,
    CeOSTK_SEG_10msLOOP,
    CeOSTK_SEG_100msLOOP,
    CeOSTK_SEG_1msTIMEBASE,
    CeOSTK_SEG_2msTIMEBASE,
    CeOSTK_SEG_5msTIMEBASE,
    CeOSTK_SEG_10msTIMEBASE,
    NUMBER_OF_CeOSTK_SEG
} OSTK_SEG_T;

/*===========================================================================*\
 * Type Definitions For Throughput Data
\*===========================================================================*/
typedef struct {
    uint32_t  t_AvgExecTime;
    uint32_t  t_MaxExecTime;
    uint32_t  t_MinExecTime;
    uint32_t  t_CurrExecTime;
    uint32_t  t_EnterTime;
    uint32_t  t_LeaveTime;
} LOOP_THROUGHPUT_T;

/*===========================================================================*\
 * Global Functions, these two functions are reentrant
\*===========================================================================*/
void Enter_OSThroughputMeasure(OSTK_SEG_T index);
void Leave_OSThroughputMeasure(OSTK_SEG_T index);

void Init_InitThroughputData(void);


#endif
