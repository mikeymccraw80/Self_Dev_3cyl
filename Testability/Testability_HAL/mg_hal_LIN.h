#ifndef MG_HAL_LIN_H
#define MG_HAL_LIN_H

bool mg_HAL_LIN_Get_Read_Status(void);
void mg_HAL_LIN_Reset_Read_Status(void);
bool mg_HAL_LIN_Get_Write_Status(void);
void mg_HAL_LIN_Reset_Write_Status(void);
uint8_t mg_HAL_LIN_Read(void);
void mg_HAL_LIN_Write(uint8_t data);
void mg_HAL_LIN_Set_DMA_Enable(bool state);

#endif
