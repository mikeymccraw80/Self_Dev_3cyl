#ifndef MG_HAL_EST_H
#define MG_HAL_EST_H

void mg_HAL_EST_Set_EST1(bool state);
void mg_HAL_EST_Set_ESTSYNC(bool state);
void mg_HAL_EST_Set_Sequential_Mode(bool seq_mode);
void mg_HAL_EST_Discrete_Cycling(void);
void mg_HAL_EST_Discrete_Cycling_EMC(void);
bool mg_HAL_Get_EST_Sequential_Mode(void);
void mg_HAL_EST_Init(MPTAC_Time_Mode_T mode, uint32_t during, uint32_t during_max, uint32_t during_min, uint32_t min_off_time, uint32_t comp_time);
void mg_HAL_EST_Start(void);
void mg_HAL_EST_cycling(void);
void mg_HAL_EST_Shutdown(void);
void mg_HAL_EST_Toggle(void);

#endif
