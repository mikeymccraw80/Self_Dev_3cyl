#ifndef DD_MCD5408_H
#define DD_MCD5408_H

#include "dd_tpu.h"
#include "mcd5408.h"

//===========================================================================
// Macro Definitions                                                         
//===========================================================================

#define MCD5408_EDGE_TIME_ARRAY_MASK       (MCD5408_EDGE_TIME_ARRAY_SIZE - 1)
#define MCD5408_EDGE_COUNTER_RANGE_DIV2    0x8000
#define MCD5408_MAX_TCR_COUNT              0xFFFFFF
#define MCD5408_DEFAULT_GAP_SIZE 2
#define MCD5408_GAP_DETECT_TOOTH    (uint8_t)(2)
#define MCD5408_BITS_IN_CAM_HISTORY (uint32_t)(32)

typedef struct
{
   uint16_t Count;
   uint32_t Time;

}  EPPwMT_Coherent_Edge_Time_And_Count_T;


typedef enum
{
   EPPWMT_ANGLE_MODE_DISABLED,
   EPPWMT_ANGLE_MODE_PLL,
   EPPWMT_ANGLE_MODE_EDGE_COUNT
}  EPPwMT_Angle_Mode_T;

typedef enum
{
   EPPWMT_IRQ_1,
   EPPWMT_IRQ_2,
   EPPWMT_IRQ_3,
   EPPWMT_IRQ_4,
   EPPWMT_IRQ_GAP_DETECTED,
   EPPWMT_IRQ_EDGE_REJECTED,
   EPPWMT_IRQ_CHANGE_DIR
}  EPPwMT_IRQ_T;

typedef enum
{
   EPPWMT_ANGLE_CLOCK1_NOT_USED,
   EPPWMT_ANGLE_CLOCK1_TIMER0_CLOCK0,
   EPPWMT_ANGLE_CLOCK1_TIMER0_CLOCK1,
   EPPWMT_ANGLE_CLOCK1_TIMER1_CLOCK0,
   EPPWMT_ANGLE_CLOCK1_TIMER1_CLOCK1
}  EPPwMT_ANGLE_Clock1_T;

typedef enum
{
   EPPWMT_ARRAY_FLAG_IN_THE_GAP,
   EPPWMT_ARRAY_FLAG_DIR_REVERSE,
   EPPWMT_ARRAY_FLAG_DIR_UNKNOWN,
   EPPWMT_ARRAY_FLAG_PER_TIMEOUT
} EPPwMT_ARRAY_Flag_T;

//===========================================================================
// MCD5408_Backup_Channel_Init_T                                             
//===========================================================================

typedef struct MCD5408_Channel_Init_Tag
{
   bool                 gap_detect_enable;
   uint8_t              gap_size;
   uint8_t              gap_detect_method; //EPPE_1_X__Y_1 or EPPE_PERCENT_PERIOD
   uint8_t              gap_detect_ratio;  //in percentage - 0 to FF (0 to 100%)
   uint8_t              filter_type;       //EPPE_HW_MIN_PERIOD or EPPE_SW_MIN_PERIOD
   uint16_t             filter_value;
   EPPwMT_Angle_Mode_T  angle_mode;
   uint8_t              edge_array_mask;
   Edge_T            critical_edge;
   bool                 clear_edge_count;
   uint16_t             tach_low;
   uint16_t             tach_high;
   TPU_Channel_T        tach_channel;
   TPU_Channel_T        cam_channel;
} MCD5408_Channel_Init_T;

typedef struct MCD5408_Backup_Channel_Init_Tag
{
   uint8_t               freq_multiplier;
}MCD5408_Backup_Channel_Init_T;



#endif // DD_MCD5408_H
