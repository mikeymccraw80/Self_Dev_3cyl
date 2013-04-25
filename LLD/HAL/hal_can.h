#ifndef HAL_CAN_H
#define HAL_CAN_H


#include "reuse.h"

void HAL_CAN_Initialize(void);
void HAL_CAN_Transmit_Message(uint32_t id, uint8_t len, uint8_t *pdata);

#endif

