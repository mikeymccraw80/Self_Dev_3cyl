/*****************************************************************************
 * Copyright 2009 Delphi Technologies, Inc., All Rights Reserved             *
 * AUTHORS: Sandeep,Prakash                                                  *
 * Project: J1939 - Comm Manager                                             *
 * File Name:  j1939_communication_manager.h                                 *
 * File Description:                                                         *
 * This module contains J1939 Communication manager routines.                *
 *****************************************************************************/

#ifndef J1939_COMMUNICATION_MANAGER_H
#define J1939_COMMUNICATION_MANAGER_H

#include "j1939_data_types.h"

typedef enum
{
   J1939_CHANNEL_0,
   J1939_CHANNEL_1
}J1939_Channel_T;

extern 	const J1939_Message_Table_T   J1939_Message_Table[];


/************************************************************************/
/* Copyright Delphi-Delco Electronics 2004                              */
/*                                                                      */
/* Filename - j1939ComMgr.h                                             */
/*                                                                      */
/* Purpose - Manages the CAN communications                             */
/************************************************************************/

extern void J1939_Initialize_Communication_Manager(J1939_Channel_T channel_num);
extern void J1939_Handler_Periodic_Task(void);
#if 0
/*****************************************************************************/
/* J1939_Disable_Transmit_Message_Service                                                   */
/*****************************************************************************/
extern void J1939_Disable_Transmit_Message_Service (J1939_Channel_T channel_num);

/*****************************************************************************/
/* J1939_Enable_Transmit_Message_Service                                                   */
/*****************************************************************************/
extern void J1939_Enable_Transmit_Message_Service (J1939_Channel_T channel_num);

/*****************************************************************************/
/* J1939_Disable_Receive_Message_Process                                                   */
/*****************************************************************************/
extern void J1939_Disable_Receive_Message_Process (J1939_Channel_T channel_num);

/*****************************************************************************/
/* J1939_Enable_Receive_Message_Process                                                   */
/*****************************************************************************/
extern void J1939_Enable_Receive_Message_Process (J1939_Channel_T channel_num);

/*****************************************************************************/
/* To Read the Tx Start index and End Index for the Channel                  */
/*****************************************************************************/
extern uint8_t J1939_Get_Tx_Start_Index(void);
extern uint8_t J1939_Get_Tx_End_Index(void);

#endif
void J1939_Transmit_Message_Confirmation(uint8_t index);


void J1939_Handler_Cold_Init(void);

void J1939_Message_Receive_Callback(
   uint8_t     in_msg_obj,
   uint8_t     *in_data_buff,
   uint8_t     in_data_length );


#endif

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* * ===     ============  ================      ====================          *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
* 2        02/03/2012    nz8l7x                code clean up                  *
******************************************************************************/
