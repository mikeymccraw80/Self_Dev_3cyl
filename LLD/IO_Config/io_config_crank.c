#include "io_config_crank.h"
#include "io_config_tpu.h"



//=============================================================================
// EPPwMT
//=============================================================================


const MCD5408_Channel_Init_T EPPWMT_INIT = 
{
   true,                                       //gap_detect_enable;
   CRANK_TEETH_PER_GAP,                                          //gap_size;
   EPPE_1_X__Y_1,                              //gap_detect_method - EPPE_1_X__Y_1 or EPPE_PERCENT_PERIOD
   0x73,                                       //gap_detect_ratio; - in percentage - 0 to FF (0 to 100%)
   EPPE_HW_MIN_PERIOD,                         //filter_type; - EPPE_HW_MIN_PERIOD or EPPE_SW_MIN_PERIOD
   (uint16_t)(TPU_A_TCR1_CLOCK_FREQ*0.00002),  //filter_value in TCR1 count;
   EPPWMT_ANGLE_MODE_PLL,                      //angle_mode;
   (EPPWMT_EDGE_ARRAY_SIZE - 1),               //Edge Time Array Mask
   EDGE_FALLING,// Edge_T            critical_edge;
   true,                                       // bool                 clear_edge_count;
   30,                                         // uint16_t             tach_low;
   30,                                         // uint16_t             tach_high;
   TPU_CHANNEL_0,                              // TPU_Channel_T        tach_channel; /* If Tach_Chan_Number is set to 0x0,the tachometer feature will be disabled*/
   TPU_CHANNEL_1                               // TPU_Channel_T        cam_channel;

} ;

//=============================================================================
// 
//=============================================================================




