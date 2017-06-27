//=============================================================================
// include files
//=============================================================================
#include "io_interface_can.h"
#include "hal_can.h"
#include "HLS.h"
#include "vehicle_can_cald.h"


/* ==========================================================================*\
 * Exported Macro Define
\* ==========================================================================*/
// Receive CAN Messages ID
#define CHERY_CANR_1AE_ID                          0x1ae
#define CHERY_CANR_2E9_ID                          0x2e9
#define CHERY_CANR_310_ID                          0x310
#define CHERY_CANR_3C0_ID                          0x3c0
#define CHERY_CANR_430_ID                          0x430
#define CHERY_CANR_51A_ID                          0x51A

// Transmit CAN Messages ID
#define CHERY_CANT_0FA_ID                          0x0FA
#define CHERY_CANT_101_ID                          0x101
#define CHERY_CANT_270_ID                          0x270
#define CHERY_CANT_278_ID                          0x278
#define CHERY_CANT_2C1_ID                          0x2c1
#define CHERY_CANT_370_ID                          0x370
#define CHERY_CANT_378_ID                          0x378
#define CHERY_CANT_501_ID                          0x501
#define CHERY_CANT_623_ID                          0x623
#define CHERY_CANT_7C1_ID                          0x7c1


/* Data for transmit */
uint8_t  VsCAN_CHERY_ID0FA[8];
uint8_t  VsCAN_CHERY_ID101[8];
uint8_t  VsCAN_CHERY_ID270[8];
uint8_t  VsCAN_CHERY_ID278[8];
uint8_t  VsCAN_CHERY_ID2C1[8];
uint8_t  VsCAN_CHERY_ID370[8];
uint8_t  VsCAN_CHERY_ID378[8];
uint8_t  VsCAN_CHERY_ID501[8];
uint8_t  VsCAN_CHERY_ID623[8];
uint8_t  VsCAN_CHERY_ID7C1[6];

/* Data for receive */
uint8_t  VsCAN_CHERY_ID2E9[8];
uint8_t  VsCAN_CHERY_ID310[8];
uint8_t  VsCAN_CHERY_ID3C0[8];
uint8_t  VsCAN_CHERY_ID430[8];
uint8_t  VsCAN_CHERY_ID1AE[8];
uint8_t  VsCAN_CHERY_ID300[8];
uint8_t  VsCAN_CHERY_ID51A[8];

void MngChery_Can_10ms(void)
{
}
void MngChery_Can_50ms(void)
{
}
void MngChery_Can_100ms(void)
{
}

void MngChery_Can_1000ms(void)
{
}

void MngChery_Can_2000ms(void)
{
}



