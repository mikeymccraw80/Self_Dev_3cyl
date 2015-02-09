//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_knock_test.c %
//
// created_by:       tzwfxv %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:             %
//
// %version:         5 %
//
//=============================================================================

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal_config.h"
#include "mg_hal.h"
#include "mg_hal_analog.h"
#include "mg_hal_timer.h"



/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define COUNTS_2MSEC                   (2 * (SYSTEM_FREQUENCY_HZ / 1000))        /* 2 ms */
#define WAVE_SMOOTH                    (0)
#define WAVE_UP                             (1)
#define WAVE_DOWN                       (2)

uint32_t throughput;
uint32_t last_timer;

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                       */
/*----------------------------------------------------------------------------*/
void mg_knock_test(void);



/*****************************************************************************
 * Function Prototype: void knock_test(void)
 *
 * Description: This test will computes the maximum and the minimum 
 *               voltage of the perticular input channel 
 *
 * Argument(s): void
 *
 * External functions: none	   
 *
 * Return Value: void
 *
 *****************************************************************************/
void mg_knock_test(void)
{
    uint8_t idx;
    uint32_t start_timer;
    uint32_t current_timer;
    uint32_t maxAD_timer[2];
    uint32_t minAD_timer[2];
    uint16_t maxAD_value[2] = 0;
    uint16_t minAD_value[2] = 0;
    uint32_t maxAD_starttimer[2];
    uint32_t maxAD_stoptimer[2];
    uint16_t maxAD_count[2];
    uint16_t temp;
    uint32_t diff[2];
    uint32_t during;
    uint16_t lastAD_value[2];
    uint8_t wave_dir[2];
    uint16_t period[2];

    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    for (idx = 0; idx < MG_Number_of_KNOCK_Device; idx++)
    {
        start_timer = mg_HAL_Timer_Get_STM_In_CNT();
        do
        {
            current_timer = mg_HAL_Timer_Get_STM_In_CNT();
            temp = mg_HAL_Analog_Get_Knock(idx);
            if ((maxAD_value[idx]  == 0) && (minAD_value[idx]  == 0))
            {
                maxAD_value[idx] = temp;
                minAD_value[idx] = temp;
                maxAD_timer[idx] = current_timer;
                minAD_timer[idx] = current_timer;
                lastAD_value[idx] = temp;
                maxAD_count[idx] = 0;
                wave_dir[idx] = WAVE_SMOOTH;
            }
            else if (temp > lastAD_value[idx])
            {
                if (temp > maxAD_value[idx])
                {
                    maxAD_value[idx] = temp;
                }
                wave_dir[idx] = WAVE_UP;
            }
            else if (temp < lastAD_value[idx])
            {
                if (wave_dir[idx] == WAVE_UP)
                {
                    if (maxAD_value[idx] != minAD_value[idx])
                    {
                        if (maxAD_count[idx] == 0)
                        {
                            maxAD_starttimer[idx] = current_timer;
                        }
                        else
                        {
                            maxAD_stoptimer[idx] = current_timer;
                        }
                        maxAD_count[idx]++;
                    }
                }
                if (temp < minAD_value[idx])
                {
                    minAD_value[idx] = temp;
                }
                wave_dir[idx] = WAVE_DOWN;
            }
            else
            {
                /* do nothing */
            }
            during = mg_HAL_Timer_Get_STM_Diff_In_CNT(current_timer, start_timer);
        }while (during < COUNTS_2MSEC);
    }
    
    mg_HAL_Service_WatchDog();

    for (idx = 0; idx < 2; idx++)
    {
        if (maxAD_count[idx] > 1)
        {
            if (maxAD_stoptimer[idx] > maxAD_starttimer[idx])
            {
                diff[idx] = mg_HAL_Timer_Get_STM_Diff_In_us_By_CNT(maxAD_stoptimer[idx], maxAD_starttimer[idx]);
            }
            else
            {
                diff[idx] = mg_HAL_Timer_Get_STM_Diff_In_us_By_CNT(maxAD_stoptimer[idx], maxAD_starttimer[idx]);
            }
            period[idx] = (uint16_t)(diff[idx] / (maxAD_count[idx] - 1));
        }
        else
        {
            period[idx] = 0xFFFF;
        }
    }

    MG_MAILBOX_OUT(parameter[1]) = (uint8_t)(period[0] >> 8);
    MG_MAILBOX_OUT(parameter[2]) = (uint8_t)(period[0] & 0xFF);
    MG_MAILBOX_OUT(parameter[3]) = (uint8_t)(maxAD_value[0] >> 8);
    MG_MAILBOX_OUT(parameter[4]) = (uint8_t)(maxAD_value[0] & 0xFF);
    MG_MAILBOX_OUT(parameter[5]) = (uint8_t)(minAD_value[0] >> 8);
    MG_MAILBOX_OUT(parameter[6]) = (uint8_t)(minAD_value[0] & 0xFF);
    MG_MAILBOX_OUT(parameter[7]) = (uint8_t)(period[1] >> 8);
    MG_MAILBOX_OUT(parameter[8]) = (uint8_t)(period[1] & 0xFF);
    MG_MAILBOX_OUT(parameter[9]) = (uint8_t)(maxAD_value[1] >> 8);
    MG_MAILBOX_OUT(parameter[10]) = (uint8_t)(maxAD_value[1] & 0xFF);
    MG_MAILBOX_OUT(parameter[11]) = (uint8_t)(minAD_value[1] >> 8);
    MG_MAILBOX_OUT(parameter[12]) = (uint8_t)(minAD_value[1] & 0xFF);

}

