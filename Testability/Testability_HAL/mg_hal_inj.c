#include "mg_hal_config.h"
#include "mg_hal_timer.h"

/*=============================================================================
 * mg_HAL_Injector_Set_Group_Value
 * @func  set injector pin
 * @parm  injector channel, output state
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Injector_Set_Group_Value(uint8_t index, bool state)
{
    if (NULL != MG_HAL_INJ_GROUP.io[index])
    {
        IO_DISCRETE_Set_Immediate_State(MG_HAL_INJ_GROUP.io[index], state);
    }
}

/*=============================================================================
 * mg_HAL_Injector_Discrete_Cycling
 * @func  cycling injector
 *             ____                                   ____
 * INJ1 ___|t1|___________________t2|t1|______
 *                                 ____
 * INJ2 _____________t2|t1|___________________
 *             ____                                   ____
 * INJ3 ___|t1|___________________t2|t1|______
 *                                 ____
 * INJ4 _____________t2|t1|___________________
 *                t1 = on_time_ms    t2 = delay_time_ms
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void mg_HAL_Injector_Discrete_Cycling(void)
{
   uint16_t idx;
   uint32_t time_diff;

   MG_HAL_INJ_GROUP.timer.current_time = mg_HAL_Timer_Get_STM_In_CNT();

   time_diff = mg_HAL_Timer_Get_STM_Diff_In_CNT(MG_HAL_INJ_GROUP.timer.current_time,MG_HAL_INJ_GROUP.timer.start_time);

   switch(MG_HAL_INJ_GROUP.current_inj)
   {
      case MG_INJ_IDX_1:
         if (MG_HAL_INJ_GROUP.io[MG_INJ_IDX_1] != NULL) 
         {
            if (MG_HAL_INJ_GROUP.current_state == true) 
            {
               if (time_diff >= MG_HAL_INJ_GROUP.on_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_1,false);
                  MG_HAL_INJ_GROUP.current_state = false;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
            else
            {
               if (time_diff >= MG_HAL_INJ_GROUP.delay_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_2,true);
                  MG_HAL_INJ_GROUP.current_inj = MG_INJ_IDX_2;
                  MG_HAL_INJ_GROUP.current_state = true;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
         }
         break;
      case MG_INJ_IDX_2:
         if (MG_HAL_INJ_GROUP.io[MG_INJ_IDX_2] != NULL) 
         {
            if (MG_HAL_INJ_GROUP.current_state == true) 
            {
               if (time_diff >= MG_HAL_INJ_GROUP.on_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_2,false);
                  MG_HAL_INJ_GROUP.current_state = false;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
            else
            {
               if (time_diff >= MG_HAL_INJ_GROUP.delay_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_3,true);
                  MG_HAL_INJ_GROUP.current_inj = MG_INJ_IDX_3;
                  MG_HAL_INJ_GROUP.current_state = true;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
         }
         break;
      case MG_INJ_IDX_3:
         if (MG_HAL_INJ_GROUP.io[MG_INJ_IDX_3] != NULL) 
         {
            if (MG_HAL_INJ_GROUP.current_state == true) 
            {
               if (time_diff >= MG_HAL_INJ_GROUP.on_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_3,false);
                  MG_HAL_INJ_GROUP.current_state = false;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
            else
            {
               if (time_diff >= MG_HAL_INJ_GROUP.delay_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_4,true);
                  MG_HAL_INJ_GROUP.current_inj = MG_INJ_IDX_4;
                  MG_HAL_INJ_GROUP.current_state = true;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
         }
         break;
      case MG_INJ_IDX_4:
         if (MG_HAL_INJ_GROUP.io[MG_INJ_IDX_4] != NULL) 
         {
            if (MG_HAL_INJ_GROUP.current_state == true) 
            {
               if (time_diff >= MG_HAL_INJ_GROUP.on_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_4,false);
                  MG_HAL_INJ_GROUP.current_state = false;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
            else
            {
               if (time_diff >= MG_HAL_INJ_GROUP.delay_time_us) 
               {
                  mg_HAL_Injector_Set_Group_Value(MG_INJ_IDX_1,true);
                  MG_HAL_INJ_GROUP.current_inj = MG_INJ_IDX_1;
                  MG_HAL_INJ_GROUP.current_state = true;
                  MG_HAL_INJ_GROUP.timer.start_time = MG_HAL_INJ_GROUP.timer.current_time;
               }
            }
         }
         break;
      default:
         break;
   }
}

