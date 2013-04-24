//=============================================================================
// include files
//=============================================================================
#include "io_interface_can.h"
#include "hal_can.h"
#include "HLS.h"


/* ==========================================================================*\
 * Exported Macro Define
\* ==========================================================================*/
// Receive CAN Messages ID
#define CHERY_CANR_2E9_ID                          0x2e9
#define CHERY_CANR_310_ID                          0x310
#define CHERY_CANR_391_ID                          0x391
#define CHERY_CANR_3C0_ID                          0x3c0
#define CHERY_CANR_430_ID                          0x430

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
uint8_t  VsCAN_CHERY_ID391[8];
uint8_t  VsCAN_CHERY_ID3C0[8];
uint8_t  VsCAN_CHERY_ID430[8];

void MngChery_Can_10ms(void)
{
	HAL_CAN_Transmit_Message(CHERY_CANT_0FA_ID, 8, VsCAN_CHERY_ID0FA);
	HAL_CAN_Transmit_Message(CHERY_CANT_101_ID, 8, VsCAN_CHERY_ID101);
	HAL_CAN_Transmit_Message(CHERY_CANT_270_ID, 8, VsCAN_CHERY_ID270);
	HAL_CAN_Transmit_Message(CHERY_CANT_278_ID, 8, VsCAN_CHERY_ID278);
	HAL_CAN_Transmit_Message(CHERY_CANT_2C1_ID, 8, VsCAN_CHERY_ID2C1);
	HAL_CAN_Transmit_Message(CHERY_CANT_370_ID, 8, VsCAN_CHERY_ID370);
	HAL_CAN_Transmit_Message(CHERY_CANT_378_ID, 8, VsCAN_CHERY_ID378);
}

void MngChery_Can_100ms(void)
{
	HAL_CAN_Transmit_Message(CHERY_CANT_501_ID, 8, VsCAN_CHERY_ID501);
}

void MngChery_Can_1000ms(void)
{
	HAL_CAN_Transmit_Message(CHERY_CANT_623_ID, 8, VsCAN_CHERY_ID623);
}

void MngChery_Can_2000ms(void)
{
	HAL_CAN_Transmit_Message( CHERY_CANT_7C1_ID, 8, VsCAN_CHERY_ID7C1);
}



