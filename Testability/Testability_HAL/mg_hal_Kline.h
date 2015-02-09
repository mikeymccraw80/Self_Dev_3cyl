#ifndef MG_HAL_KLINE_H
#define MG_HAL_KLINE_H

bool mg_HAL_Kline_Get_Read_Status(void);
void mg_HAL_Kline_Reset_Read_Status(void);
bool mg_HAL_Kline_Get_Write_Status(void);
void mg_HAL_Kline_Reset_Write_Status(void);
uint8_t mg_HAL_Kline_Read(void);
void mg_HAL_Kline_Write(uint8_t data);

#endif
