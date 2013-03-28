#ifndef DD_FLASH_INTERFACE_H
#define DD_FLASH_INTERFACE_H


#include "reuse.h"
//===========================================================================
//  Imported Function Prototypes
//===========================================================================
//MCP5634M - Monaco
extern void MPC5634_FLASH_Initialize_Programming(void);
extern void MPC5634_FLASH_Initialize_Normal(void);
//MPC5644A - Andorra
extern void MPC5644_FLASH_Initialize_Programming(void);
extern void MPC5644_FLASH_Initialize_Normal(void);


#endif


