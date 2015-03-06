#include "mg_hal_config.h"
#include "mg_hal_timer.h"
// #include "io_discrete.h"
// #include "io_spark.h"
// #include "io_mptac.h"
#include "dd_vsep_est_select.h"
#include "dd_mcd5412.h"
#include "dd_siu_interface.h"
#include "dd_mcd5412_interface.h"
#include "io_config_tpu.h"

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
        SIU_GPIO_DISCRETE_Set_State(MG_HAL_EST_GROUP.io[MG_EST1], state);
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
        SIU_GPIO_DISCRETE_Set_State(MG_HAL_EST_GROUP.io[MG_ESTSYNC], state);
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
      VSEP_EST_Set_PF_Mode(VSEP_INDEX_0,VSEP_EST_SELECT_PAIRED_FIRE_MODE_DISABLED);
   }
   else 
   {
       VSEP_EST_Set_PF_Mode(VSEP_INDEX_0,VSEP_EST_SELECT_PAIRED_FIRE_MODE_ENABLED);
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
    return false;
}

void mg_HAL_EST_Init(MPTAC_Time_Mode_T mode, uint32_t during, uint32_t during_max, uint32_t during_min, uint32_t min_off_time, uint32_t comp_time)
{
    // EnableHWIO_Spark_Overide();
    uint32_t start_time = TPU_TIMER_Get_Value_Channel(MPTAC_TPU_INDEX, SPARK_Mptac[0]);
    MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[0], false );
    MCD5412_Initialize_Channel( MPTAC_TPU_INDEX,  SPARK_Mptac[0]);
    MCD5412_Set_Flag(MPTAC_TPU_INDEX,             SPARK_Mptac[0], MPTAC_MULTI_PULSE_MODE_FLAG, false);
    MCD5412_Set_Time_Mode( MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[0], mode);
    MCD5412_Set_Duration(MPTAC_TPU_INDEX,         SPARK_Mptac[0], during);
    MCD5412_Set_Max_Duration(MPTAC_TPU_INDEX,     SPARK_Mptac[0], during_max);
    MCD5412_Set_Min_Duration(MPTAC_TPU_INDEX,     SPARK_Mptac[0], during_min);
    MCD5412_Set_CPU_Start_Time(MPTAC_TPU_INDEX,   SPARK_Mptac[0], start_time);
    MCD5412_Set_Min_Off_Time(MPTAC_TPU_INDEX,     SPARK_Mptac[0], min_off_time);
    MCD5412_Set_Comp_Time(MPTAC_TPU_INDEX,        SPARK_Mptac[0], comp_time);
    MG_HAL_EST_GROUP.timer.current_time = start_time;
}

void mg_HAL_EST_Start(void)
{
    MCD5412_Request_Pulse( MPTAC_TPU_INDEX, SPARK_Mptac[0]);
}

void mg_HAL_EST_cycling(void)
{
    if (MCD5412_Get_Host_Interrupt_Status(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[0], false))
    {
        MCD5412_Set_Host_Interrupt_Status(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[0], false);
        MG_HAL_EST_GROUP.timer.current_time += (MG_HAL_EST_GROUP.on_time_us + MG_HAL_EST_GROUP.delay_time_us);
        mg_HAL_EST_Set_ESTSYNC(true);
        mg_HAL_EST_Set_ESTSYNC(false);
        MCD5412_Set_CPU_Start_Time(MPTAC_TPU_INDEX,   SPARK_Mptac[0], MG_HAL_EST_GROUP.timer.current_time);
        // Request that a new pulse be set up:
        MCD5412_Request_Pulse( MPTAC_TPU_INDEX, SPARK_Mptac[0]);
    }
}

void mg_HAL_EST_Shutdown(void)
{
    MCD5412_Set_Host_Interrupt_Enable(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[0], false );
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
        if (MCD5412_Get_Host_Interrupt_Status(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[0], false))
        {
            MCD5412_Set_Host_Interrupt_Status(MPTAC_TPU_INDEX, &TPU, SPARK_Mptac[0], false);
            MG_HAL_EST_GROUP.timer.current_time = MCD5412_Get_Start_Time(MPTAC_TPU_INDEX, SPARK_Mptac[0]);
            MG_HAL_EST_GROUP.timer.current_time += (MG_HAL_EST_GROUP.on_time_us + MG_HAL_EST_GROUP.delay_time_us);
            mg_HAL_EST_Set_ESTSYNC(true);
            mg_HAL_EST_Set_ESTSYNC(false);
            MCD5412_Set_CPU_Start_Time(MPTAC_TPU_INDEX,   SPARK_Mptac[0], MG_HAL_EST_GROUP.timer.current_time);
            MCD5412_Request_Pulse( MPTAC_TPU_INDEX, SPARK_Mptac[0]);
            count++;
        }
    }
    mg_HAL_EST_Shutdown();
}
