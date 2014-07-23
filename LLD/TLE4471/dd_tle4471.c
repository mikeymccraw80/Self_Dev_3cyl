/* ============================================================================ *\
 * dd_tle4471.c
 * ============================================================================
 * COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * %full_filespec:   dd_tle4471.c~2:csrc:mt20u2#2 %
 * created_by:       sjl
 * date_created:     Dec 12, 2007
 * %derived_by:      nz45s2 %
 * %date_modified:   Mon Mar  7 18:46:28 2011 %
 * %version:         2 %
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains I/O routines for S12X Xgate.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

 /* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "io_type.h"

/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "dd_tle4471.h"
#include "dd_siu.h"
#include "io_config_siu.h"  
#include "hwiocald.h"

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/
#ifndef Max
#define Max(a,b) ( ( (a)>(b) )?(a):(b) )
#endif

#define TLE4471_WD_EDEGE_INTERVAL_25US  (25*(SYSTEM_FREQUENCY_HZ/1000000))
#define TLE4471_WD_TOGGLE_3MS           (3*(SYSTEM_FREQUENCY_HZ/1000))

/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */
uint32_t TLE4471_WD_Toggle_Last_Time;
uint32_t TLE4471_WD_Feed_StateHigh_Last_Time;
uint32_t NfHWIO_t_HWWD_MaxFeedingInterval;
bool     VbHWIO_EnableLogMaxHWWDTime;

/* ============================================================================ *\
 * Function definitions
 * ============================================================================ */
void  InitRamVariable_EnableLogMaxHWWDTime(void)
{
    VbHWIO_EnableLogMaxHWWDTime = KbHWIO_EnableLogMaxHWWDTime;
}

/*=============================================================================
 * TLE4471_WD_Toggle_Immediate
 * @func  Service external watchdog 
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void TLE4471_WD_Toggle_Immediate(void)
{
        TLE4471_WatchDog_Toggle();

        if(VbHWIO_EnableLogMaxHWWDTime == true)
        {
             if(TLE4471_WatchDog_Get_State() == true)
             {
                 NfHWIO_t_HWWD_MaxFeedingInterval = Max((uint32_t)( READ_SPR_VALUE( SPR_TBL) -TLE4471_WD_Feed_StateHigh_Last_Time), 
				 	                                                                                 (uint32_t)NfHWIO_t_HWWD_MaxFeedingInterval);
                 TLE4471_WD_Feed_StateHigh_Last_Time = READ_SPR_VALUE( SPR_TBL);
             }
        }
}

/*=============================================================================
 * TLE4471_WD_Toggle_Exceed_3ms
 * @func  Service external watchdog 
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void TLE4471_WD_Toggle_Exceed_3ms(void)
{
  uint32_t delta_time;

   delta_time = READ_SPR_VALUE( SPR_TBL) - TLE4471_WD_Toggle_Last_Time;
   if (delta_time > TLE4471_WD_TOGGLE_3MS )
    {
        TLE4471_WatchDog_Toggle();
        TLE4471_WD_Toggle_Last_Time = READ_SPR_VALUE( SPR_TBL);
		
        if(VbHWIO_EnableLogMaxHWWDTime == true)
        {
             if(TLE4471_WatchDog_Get_State() == true)
             {
                 NfHWIO_t_HWWD_MaxFeedingInterval = (FIXED_UL_06)Max((uint32_t)(READ_SPR_VALUE( SPR_TBL) -TLE4471_WD_Feed_StateHigh_Last_Time), 
				 	                                                                                 (uint32_t)NfHWIO_t_HWWD_MaxFeedingInterval);
                 TLE4471_WD_Feed_StateHigh_Last_Time = READ_SPR_VALUE( SPR_TBL);
             }
        }
    }
}

/*=============================================================================
 * TLE4471_WD_Feeding()
 * @func  Service external watchdog 
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void TLE4471_WD_Feeding(void)
{
uint32_t  toggle_Last_Time;

   TLE4471_WatchDog_Toggle();
   toggle_Last_Time = READ_SPR_VALUE( SPR_TBL);
   
   if(VbHWIO_EnableLogMaxHWWDTime == true)
   {
        if(TLE4471_WatchDog_Get_State() == true)
        {
             if(TLE4471_WD_Feed_StateHigh_Last_Time != 0) //The 1st of 4471 rising edge in App, Not record the timer
             {
                 NfHWIO_t_HWWD_MaxFeedingInterval = (FIXED_UL_06)Max((uint32_t)(READ_SPR_VALUE( SPR_TBL) -TLE4471_WD_Feed_StateHigh_Last_Time), 
				 	                                                                                 (uint32_t)NfHWIO_t_HWWD_MaxFeedingInterval);
             }
             TLE4471_WD_Feed_StateHigh_Last_Time = READ_SPR_VALUE( SPR_TBL);
        }
   }
    while ( (READ_SPR_VALUE( SPR_TBL ) - toggle_Last_Time) <= TLE4471_WD_EDEGE_INTERVAL_25US)
    {
        //according SPEC, waiting for at least 25us
    }
   TLE4471_WatchDog_Toggle();
   
   if(VbHWIO_EnableLogMaxHWWDTime == true)
   {
        if(TLE4471_WatchDog_Get_State() == true)
        {
             NfHWIO_t_HWWD_MaxFeedingInterval = (FIXED_UL_06)Max((uint32_t)(READ_SPR_VALUE( SPR_TBL) -TLE4471_WD_Feed_StateHigh_Last_Time), 
				 	                                                                             (uint32_t)NfHWIO_t_HWWD_MaxFeedingInterval);
             TLE4471_WD_Feed_StateHigh_Last_Time = READ_SPR_VALUE( SPR_TBL);
        }
   }
}

/*===========================================================================
 * File revision history (top to bottom, first revision to last revision
 *===========================================================================
 *                                                                   
 * Rev.  YYMMDD  Who    RSM#   Changes
 * ----  ------  -----  ----   -------
 *
 *===========================================================================*/

