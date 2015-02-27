#if 0
#include "mg_hal_config.h"
#include "mg_hal_timer.h"
#include "io_discrete.h"
#include "io_spark.h"
#include "io_mptac.h"

#define MG_EST_SEQUENTIAL_MODE             (uint8_t volatile  *)(0x00000019)

/*=============================================================================
 * mg_HAL_EST_Set_EST1
 * @func  set EST1 state
 * @parm  EST1 state
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_EST_Set_EST1(bool state)
{
    if (NULL != MG_HAL_EST_GROUP.io[MG_EST1])
    {
        IO_DISCRETE_Set_Immediate_State(MG_HAL_EST_GROUP.io[MG_EST1], state);
    }
}

/*=============================================================================
 * mg_HAL_EST_Set_ESTSYNC
 * @func  set ESTSYNC state
 * @parm  ESTSYNC
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_EST_Set_ESTSYNC(bool state)
{
    if (NULL != MG_HAL_EST_GROUP.io[MG_ESTSYNC])
    {
        IO_DISCRETE_Set_Immediate_State(MG_HAL_EST_GROUP.io[MG_ESTSYNC], state);
    }
}

/*=============================================================================
 * mg_HAL_EST_Set_Sequential_Mode
 * @func  set est to sequential mode
 * @parm  seq_mode - true : sequential mode
 *                   false: waste mode
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_EST_Set_Sequential_Mode(bool seq_mode)
{
   if (seq_mode == true) 
   {
      IO_SPARK_Set_Mode( MG_HAL_SPARK, SPARK_SEQUENTIAL_MODE );
   }
   else 
   {
      IO_SPARK_Set_Mode( MG_HAL_SPARK, SPARK_SIMULTANEOUS_MODE );
   }
}

/*=============================================================================
 * mg_HAL_EST_Discrete_Cycling
 * @func  cycling est
 *         ____                     ____
 * EST1 ___|t1|___________________t2|t1|______
 *               ____
 * EST2 _______t2|t1|_________________________
 *                     ____
 * EST3 _____________t2|t1|___________________
 *                           ____
 * EST4 ___________________t2|t1|_____________
 *                t1 = on_time_ms    t2 = delay_time_ms
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_EST_Discrete_Cycling(void)
{
   uint32_t time_diff;

   MG_HAL_EST_GROUP.timer.current_time = mg_HAL_Timer_Get_STM_In_us();

   time_diff = mg_HAL_Timer_Get_STM_Diff_In_us(MG_HAL_EST_GROUP.timer.current_time,MG_HAL_EST_GROUP.timer.start_time);

   if (MG_HAL_EST_GROUP.current_state == true) 
   {
      if (time_diff >= MG_HAL_EST_GROUP.on_time_us) 
      {
         mg_HAL_EST_Set_EST1(false);
         MG_HAL_EST_GROUP.timer.start_time = MG_HAL_EST_GROUP.timer.current_time;
         mg_HAL_EST_Set_ESTSYNC(false);
         MG_HAL_EST_GROUP.current_state = false;
      }
   }
   else
   {
      if (time_diff >= MG_HAL_EST_GROUP.delay_time_us) 
      {
         mg_HAL_EST_Set_EST1(true);
         MG_HAL_EST_GROUP.timer.start_time = MG_HAL_EST_GROUP.timer.current_time;
         mg_HAL_EST_Set_ESTSYNC(true);
         MG_HAL_EST_GROUP.current_state = true;
      }
   }
}

void mg_HAL_EST_Discrete_Cycling_EMC(void)
{
   uint32_t time_diff;

   MG_HAL_EST_GROUP.timer.current_time = mg_HAL_Timer_Get_STM_In_CNT();

   time_diff = mg_HAL_Timer_Get_STM_Diff_In_CNT(MG_HAL_EST_GROUP.timer.current_time,MG_HAL_EST_GROUP.timer.start_time);

   if (MG_HAL_EST_GROUP.current_state == true) 
   {
      if (time_diff >= MG_HAL_EST_GROUP.on_time_us) 
      {
         mg_HAL_EST_Set_EST1(false);
         MG_HAL_EST_GROUP.timer.start_time = MG_HAL_EST_GROUP.timer.current_time;
         mg_HAL_EST_Set_ESTSYNC(false);
         MG_HAL_EST_GROUP.current_state = false;
      }
   }
   else
   {
      if (time_diff >= MG_HAL_EST_GROUP.delay_time_us) 
      {
         mg_HAL_EST_Set_EST1(true);
         MG_HAL_EST_GROUP.timer.start_time = MG_HAL_EST_GROUP.timer.current_time;
         mg_HAL_EST_Set_ESTSYNC(true);
         MG_HAL_EST_GROUP.current_state = true;
      }
   }
}

bool mg_HAL_Get_EST_Sequential_Mode(void)
{
    return (*MG_EST_SEQUENTIAL_MODE == 00) ? true : false;
}

void mg_HAL_EST_Init(MPTAC_Time_Mode_T mode, uint32_t during, uint32_t during_max, uint32_t during_min, uint32_t min_off_time, uint32_t comp_time)
{
    uint32_t start_time = mg_HAL_Timer_Get_MPTAC_Value(&MTSA_OC_MPTAC_0);
    MPTAC_Set_Interrupt_Enable((HIODEVICE)&MTSA_OC_MPTAC_0, false);
    MPTAC_Set_Time_Mode((HIODEVICE)&MTSA_OC_MPTAC_0, mode, true);
    MPTAC_Initialize_Channel((HIODEVICE)&MTSA_OC_MPTAC_0, NULL);
    MPTAC_Set_Duration((HIODEVICE)&MTSA_OC_MPTAC_0, during);
    MPTAC_Set_Max_Duration((HIODEVICE)&MTSA_OC_MPTAC_0, during_max);
    MPTAC_Set_Min_Duration((HIODEVICE)&MTSA_OC_MPTAC_0, during_min);
    MPTAC_Set_CPU_Start_Time((HIODEVICE)&MTSA_OC_MPTAC_0, start_time);
    MPTAC_Set_Min_Off_Time((HIODEVICE)&MTSA_OC_MPTAC_0, min_off_time);
    MPTAC_Set_Comp_Time((HIODEVICE)&MTSA_OC_MPTAC_0, comp_time);
    MG_HAL_EST_GROUP.timer.current_time = start_time;
}

void mg_HAL_EST_Start(void)
{
    MPTAC_Request_Pulse((HIODEVICE)&MTSA_OC_MPTAC_0);
}

void mg_HAL_EST_cycling(void)
{
    if (MPTAC_Get_Interrupt_Status((HIODEVICE)&MTSA_OC_MPTAC_0))
    {
        MPTAC_Set_Interrupt_Status((HIODEVICE)&MTSA_OC_MPTAC_0, false);
        MG_HAL_EST_GROUP.timer.current_time += (MG_HAL_EST_GROUP.on_time_us + MG_HAL_EST_GROUP.delay_time_us);
        mg_HAL_EST_Set_ESTSYNC(true);
        mg_HAL_EST_Set_ESTSYNC(false);
        MPTAC_Set_CPU_Start_Time((HIODEVICE)&MTSA_OC_MPTAC_0, MG_HAL_EST_GROUP.timer.current_time);
        MPTAC_Request_Pulse((HIODEVICE)&MTSA_OC_MPTAC_0);
    }
}

void mg_HAL_EST_Shutdown(void)
{
    MPTAC_Set_Interrupt_Enable((HIODEVICE)&MTSA_OC_MPTAC_0, false);
}

void mg_HAL_EST_Toggle(void)
{
    uint8_t count = 0;
    MG_HAL_EST_GROUP.on_time_us = (50 * (TPU_A_TCR1_CLOCK_FREQ / 1000000));
    MG_HAL_EST_GROUP.delay_time_us = (50 * (TPU_A_TCR1_CLOCK_FREQ / 1000000));
    mg_HAL_EST_Init(MPTAC_TIME_MODE_CPU_CALCULATES_START_TIME, MG_HAL_EST_GROUP.on_time_us,
        MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.on_time_us, MG_HAL_EST_GROUP.delay_time_us, 0);
    mg_HAL_EST_Start();
    while (count < 4)
    {
        if (MPTAC_Get_Interrupt_Status((HIODEVICE)&MTSA_OC_MPTAC_0))
        {
            MPTAC_Set_Interrupt_Status((HIODEVICE)&MTSA_OC_MPTAC_0, false);
            MG_HAL_EST_GROUP.timer.current_time = MPTAC_Get_Start_Time((HIODEVICE)&MTSA_OC_MPTAC_0);
            MG_HAL_EST_GROUP.timer.current_time += (MG_HAL_EST_GROUP.on_time_us + MG_HAL_EST_GROUP.delay_time_us);
            mg_HAL_EST_Set_ESTSYNC(true);
            mg_HAL_EST_Set_ESTSYNC(false);
            MPTAC_Set_CPU_Start_Time((HIODEVICE)&MTSA_OC_MPTAC_0, MG_HAL_EST_GROUP.timer.current_time);
            MPTAC_Request_Pulse((HIODEVICE)&MTSA_OC_MPTAC_0);
            count++;
        }
    }
    mg_HAL_EST_Shutdown();
}
#endif