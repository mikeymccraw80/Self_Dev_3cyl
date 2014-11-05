#ifndef CN_IO_INTERFACE_H
#define CN_IO_INTERFACE_H
/******************************************************************************
 *
 * Filename:          cn_io_interface.h
 *
 * Description:       can interface header file.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/
//=============================================================================
// Include Files
//=============================================================================
#include "t_gentypes.h"

typedef struct
{
   bool       inactive_message;
   bool       received_message;  
   uint8_t    number_of_messages_in_buffer;
   uint16_t   next_data_in_offset;
   uint16_t   next_data_out_offset;
} CAN_Message_Buffer_Ctl_T;

typedef uint32_t								CAN_TMR_MSEC_T;
#define V_CAN_TMR_MSEC_T(val) 					(uint32_t)((val)*64)
#define S_CAN_TMR_MSEC_T         				( 6 )

//=============================================================================
// Global Variables declare
//=============================================================================
extern CAN_Message_Buffer_Ctl_T  Message_Buffer_Ctl_Ptr [];

//=============================================================================
// Global  Function Prototypes
//=============================================================================
extern void Hw_Transmit_Message(uint8_t );
extern void CAN_Error_Handler(uint8_t ,	uint8_t );
extern void CAN_Transmit_Callback(uint32_t );
extern void CAN_Receive_Callback(uint8_t ,uint8_t* , uint8_t );

extern void CAN_Setup_Interrupt(CAN_TMR_MSEC_T);
extern void Enable_CANH_Device(void);
extern void Disable_CANH_Device(void);



#endif/*CN_IO_INTERFACE_H*/
/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     090416 yrw xxxx Initial version
* 2     100322 sh  xxxx Delete #include "t_gentypes.h"
* 3.1   110516 sh  SCR_CTC_620 Modify Message_Buffer_Ctl_Ptr
******************************************************************************/

