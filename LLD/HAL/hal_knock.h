#ifndef HAL_KNOC_H
#define HAL_KNOC_H

#include "hal.h"

typedef enum
{
   MULTIKNOCK_WINDOW_1,
   MULTIKNOCK_WINDOW_2,
   MULTIKNOCK_NUM_WINDOWS
} EMS_MultiKnock_Window_T;


typedef enum
{
   MULTIKNOCK_FILTER_1,
   MULTIKNOCK_FILTER_2,
   MULTIKNOCK_FILTER_3,
   MULTIKNOCK_NUM_FILTERS
} EMS_MultiKnock_Filter_T;

void GetIO_MultiKnock_Intensity_Value(EMS_MultiKnock_Window_T window, T_PERCENT_MULTb* mult);
void SetIO_MultiKnock_High_Gain(uint8_t in_gain);
void SetIO_MultiKnock_Window_Start(EMS_MultiKnock_Window_T window, T_CRANK_ANGLEa angle);
void SetIO_MultiKnock_Window_End(EMS_MultiKnock_Window_T window, T_CRANK_ANGLEa angle);
T_PERCENT_MULTb GetIO_MultiKnock_Raw_Sample(EMS_MultiKnock_Window_T window);

#endif /* HAL_KNOC_H */
