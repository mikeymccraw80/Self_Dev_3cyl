#ifndef HAL_CAN_H
#define HAL_CAN_H

#include "reuse.h"

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
typedef struct
{
  bitfield8_t CAN_ID1AE_ERR :1;
  bitfield8_t CAN_ID2E9_ERR :1;
  bitfield8_t CAN_ID310_ERR :1;
  bitfield8_t CAN_ID391_ERR :1;
  bitfield8_t CAN_ID3C0_ERR :1;
  bitfield8_t CAN_ID430_ERR :1;
  bitfield8_t UNUSED :2;
}CAN_RECEIVE_ERR_TYPE;
/* Used to diagnostic can meter */
extern CAN_RECEIVE_ERR_TYPE VsCAN_Receive_Err;

void HAL_CAN_Initialize(void);
void HAL_CAN_Transmit_Message(uint32_t id, uint8_t len, uint8_t *pdata);

#endif

