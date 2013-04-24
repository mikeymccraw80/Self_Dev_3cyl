#ifndef HAL_CAN_H
#define HAL_CAN_H


#include "reuse.h"

void CCP_Initialize(void);
void HAL_CAN_10ms_Task(void);
void CAN_RX_B15_Config(void);
void HAL_CAN_Transmit_Message(uint32_t id, uint8_t len, uint8_t *pdata);
void HAL_CAN_Transmit_Message(uint32_t id, uint8_t len, uint8_t *pdata);

#endif

