#ifndef HAL_CAN_H
#define HAL_CAN_H

#include "reuse.h"

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
typedef struct
{
  bitfield16_t CAN_ID1AE_ERR :1;
  bitfield16_t CAN_ID2E9_ERR :1;
  bitfield16_t CAN_ID310_ERR :1;
  bitfield16_t CAN_ID391_ERR :1;
  bitfield16_t CAN_ID3C0_ERR :1;
  bitfield16_t CAN_ID430_ERR :1;
  bitfield16_t UNUSED_ERR :2;
  bitfield16_t CAN_ID1AE_RXF :1;
  bitfield16_t CAN_ID2E9_RXF :1;
  bitfield16_t CAN_ID310_RXF :1;
  bitfield16_t CAN_ID391_RXF :1;
  bitfield16_t CAN_ID3C0_RXF :1;
  bitfield16_t CAN_ID430_RXF :1;
  bitfield16_t UNUSED_RXF :2;
}CAN_RECEIVE_ERR_TYPE;
/* Used to diagnostic can meter */
extern CAN_RECEIVE_ERR_TYPE VsCAN_Receive_Err;

void HAL_CAN_Initialize(void);
void HAL_CAN_Transmit_Message(uint32_t id, uint8_t len, uint8_t *pdata);
void HAL_CAN_Diag_Network_10ms(void);

#endif

