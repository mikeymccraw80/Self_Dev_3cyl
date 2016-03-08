/******************************************************************************
 *
 * Filename:          cn_io_transfer.c
 *
 * Description:       This file contains CAN interrupt routines and message
 *                    transmis/receive handlers.
 *
 * Global Functions Defined:
 *                    CAN_Reset_Init()
 *                    J1939_Handler_Cold_Init()
 *                    Get_Transmit_Message_Number_From_Message_ID()
 *                    Get_Receive_Message_Number_From_Message_ID()
 *                    Get_Message()
 *                    Transmit_Message()
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
#define XbCNIO_FEXI_INCLUDE_HAL_CAN
#define XbCNIO_FEXI_INCLUDE_CAN_PUBLIC_TYPE
#define XbCNIO_FEXI_INCLUDE_OBD_PUBLIC_TYPE
#define XbCNIO_FEXI_INCLUDE_CAN_INTERFACE
#define XbCNIO_FEXI_INCLUDE_IMMO_INTERFACE

#include "cn_io_transfer.h"
#include "cn_io_interface.h"
#include "cn_io_diagnostic.h"
#include "dd_flexcan_common.h"
#include "io_dcan_config.h"
#include "dd_flexcan.h"
#include "obdlcald.h"

CAN_Message_Parameter_T *CAN_Message_Parameter_Table_Ptr;
//============================================================================
// Name:  InitCANH_Message_Parameter_Table
//
// Description: according to the calibration, initialize current CAN message
//              parameter table.
//
// Shared Variables: none
//
// Parameters: none
//
// Return Value: none
//
//============================================================================
void InitCANH_Message_Parameter_Table(void)
{
   static BYTE SaCANH_TempBuffer[MESSAGE_NUM_OF_CANOBD][8];
   static CAN_Message_Parameter_T CAN_Message_Parameter_Table[MESSAGE_NUM_OF_CANOBD];
   uint8_t LyCANH_index;

   for(LyCANH_index=0; LyCANH_index<MESSAGE_NUM_OF_CANOBD; LyCANH_index++)
   {
      CAN_Message_Parameter_Table[LyCANH_index] = Get_CANOBD_Message_Parameter_Table(LyCANH_index);
   }

   CAN_Message_Parameter_Table_Ptr = CAN_Message_Parameter_Table;
}

//=============================================================================
// Name: CAN_Reset_Init
//
// Description:
//     Initializes CAN hardware registers (calls I/O layer to
//     initialize hardware) and software buffers.
//
// Warning: none
//
// Shared Variables: Message_Buffer_Ctl_Ptr
//                   CAN_Message_Parameter_Table_Ptr
//
// Parameters: none
//
// Return Value: none
//
//=============================================================================
void CAN_Reset_Init( void )
{
   uint8_t message_objet;
   IO_Configuration_T in_configuration;
   FlexCAN_MSGOBJ_INDEX_T msgobj_r = FLEXCAN_MSG_OBJ_8;
   FlexCAN_MSGOBJ_INDEX_T msgobj_t = FLEXCAN_MSG_OBJ_14;

   /* init the can obd cald id by KwDCANOBD_CANID */
   Initial_CANOBD_CAL_ID(KwDCANOBD_CANID);

   InitCANH_Message_Parameter_Table();
   // Initialize CAN transmit/receive buffer control parameters
   for ( message_objet = 0; message_objet < MESSAGE_NUM_OF_CANOBD; message_objet++ )
   {
      in_configuration = 0;

      in_configuration |= FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_A)| FlexCAN_MSGOBJ_Set_ID_Length( 0, FLEXCAN_MSGOBJ_ID_STD)|
                          FlexCAN_MSGOBJ_Set_SRR( 0, false) |
                          FlexCAN_MSGOBJ_Set_RTR( 0, false) |
                          FlexCAN_MSGOBJ_Set_Interrupt( 0, true);
      if(CANOBD_Message_Parameter_Table[message_objet].CAN_message_ID>0xFFF)
      {
         in_configuration |= FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_A)| FlexCAN_MSGOBJ_Set_ID_Length( 0, FLEXCAN_MSGOBJ_ID_EXT)|
                             FlexCAN_MSGOBJ_Set_SRR( 0, true) |
                             FlexCAN_MSGOBJ_Set_RTR( 0, false) |
                             FlexCAN_MSGOBJ_Set_Interrupt( 0, true);
      }

      if (CANH_MESSAGE_DIRECTION_RECEIVE == (CAN_Message_Parameter_Table_Ptr+message_objet)->message_dir) 
      {
         in_configuration |= FlexCAN_MSGOBJ_Set_Direction( 0, FLEXCAN_MSGOBJ_DIR_RX  );
         in_configuration |= FlexCAN_MSGOBJ_Set_Index( 0, msgobj_r);
         msgobj_r ++;
      }
      else if (CANH_MESSAGE_DIRECTION_TRANSMIT == (CAN_Message_Parameter_Table_Ptr+message_objet)->message_dir) 
      {
         in_configuration |= FlexCAN_MSGOBJ_Set_Direction( 0, FLEXCAN_MSGOBJ_DIR_TX  );
         in_configuration |= FlexCAN_MSGOBJ_Set_Index( 0, msgobj_t);
         msgobj_t ++;
      }
      else
      {
      }

	  (CAN_Message_Parameter_Table_Ptr+message_objet)->in_configuration = in_configuration;

      FlexCAN_Initialize_Message_Object(in_configuration, (uint32_t)(CAN_Message_Parameter_Table_Ptr+message_objet)->CAN_message_ID);
   }
}

//=============================================================================
// Name:Get_Transmit_Message_Number_From_Message_ID
//
// Description:
//     All CAN functions except this one and the related receive version
//     take a message number as an
//     argument instead of the message ID.  If the user has a message
//     ID and does not know the correct message number to use, then
//     this procedure will return the correct message number.
//
// Warning: None
//
// Shared Variables: CAN_Message_Parameter_Table_Ptr
//
// Parameters: Message ID
//
// Return Value: message_number
//
//=============================================================================
uint8_t Get_Transmit_Message_Number_From_Message_ID( uint16_t Message_ID )
{

   uint8_t CAN_transmit_message_number;
   uint8_t message_number = MESSAGE_ID_NOT_IN_TABLE;

   for( CAN_transmit_message_number = 0; CAN_transmit_message_number < MESSAGE_NUM_OF_CANOBD; CAN_transmit_message_number++ )
   {
      if(( (CAN_Message_Parameter_Table_Ptr+CAN_transmit_message_number)->CAN_message_ID == Message_ID )&&
	  	 ( (CAN_Message_Parameter_Table_Ptr+CAN_transmit_message_number)->message_dir == HAL_CAN_MESSAGE_DIRECTION_TRANSMIT))
      {
         message_number = CAN_transmit_message_number;
         break;
      }
   }

   return( message_number );
}

   
//=============================================================================
// Name:Get_Receive_Message_Number_From_Message_ID
//
// Description:
//     All CAN functions except this one and the related transmit version
//     take a message number as an
//     argument instead of the message ID.  If the user has a message
//     ID and does not know the correct message number to use, then
//     this procedure will return the correct message number.
//
// Warning: None
//
// Shared Variables: CAN_Message_Parameter_Table_Ptr
//
// Parameters: Message ID
//
// Return Value: message_number
//
//
//=============================================================================
uint8_t Get_Receive_Message_Number_From_Message_ID( uint16_t Message_ID )
{
   uint8_t CAN_receive_message_number;
   uint8_t message_number = MESSAGE_ID_NOT_IN_TABLE;

   for ( CAN_receive_message_number = 0; CAN_receive_message_number < MESSAGE_NUM_OF_CANOBD; CAN_receive_message_number++ )
   {
      if(( (CAN_Message_Parameter_Table_Ptr+CAN_receive_message_number)->CAN_message_ID == Message_ID )&&
	  	 ( (CAN_Message_Parameter_Table_Ptr+CAN_receive_message_number)->message_dir == HAL_CAN_MESSAGE_DIRECTION_RECEIVE))
      {
         message_number =  CAN_receive_message_number;
         break;
      }
   }

   return( message_number + FLEXCAN_MSG_OBJ_32);
}

//=============================================================================
// Name: Get_OBD_Message
//
// Description:
//     Gets the specified message if possible.
//
// Warning: none
//
// Shared Variables:  Message_Buffer_Ctl_Ptr
//                    CAN_Message_Parameter_Table_Ptr
// Parameters: CAN_receive_message_number
//             message address
//
// Return Value: TRUE if the request can be honored, else FALSE.
//
//=============================================================================
bool Get_OBD_Message( uint8_t CAN_receive_message_number, uint8_t *message_address )
{
   bool         request_honored = true;
   uint8_t      loop_counter;
   uint8_t      temp_length;
   uint8_t      *temp_buffer_ptr;
   CAN_Message_Parameter_T temp_message;
   uint32_t     istate;

   if(FLEXCAN_MSG_OBJ_32 <= CAN_receive_message_number)
   {
      istate = Enter_Critical_Section();
      temp_message = Get_CANOBD_Message_Parameter_Table(CAN_receive_message_number - FLEXCAN_MSG_OBJ_32);
      temp_buffer_ptr = temp_message.CAN_buffer_ptr;
      temp_length = temp_message.CAN_message_length;
      for (loop_counter = 0; loop_counter < temp_length; loop_counter++)
      {
         *message_address++ = *temp_buffer_ptr++;
      }
      Leave_Critical_Section(istate);
   }
   else
   {
      request_honored = false;
   }

   return ( request_honored );
}

//=============================================================================
// Name: Transmit_Message
//
// Description:
//     Loads a message into the software buffers and calls the I/O
//     layer function to transmit the message.
//
// Warning: none
//
// Shared Variables: CAN_Message_Parameter_Table_Ptr
//                   Message_Buffer_Ctl_Ptr
// Parameters: can_id
//             message_address
//
// Return Value: TRUE if the request could be honored, else FALSE.
//
//=============================================================================
bool Transmit_Message( uint16_t can_id, uint8_t *message_address )
{
   uint8_t CAN_transmit_message_number;
   uint8_t *transmit_message_buffer;
   uint8_t index;

   // offset from obj begain
   CAN_transmit_message_number = Get_Transmit_Message_Number_From_Message_ID(can_id);
   // copy data to tx buffer for logic arithmetic
   transmit_message_buffer = (CAN_Message_Parameter_Table_Ptr + CAN_transmit_message_number)->CAN_buffer_ptr;
   for (index = 0; index < 8; index++)
   {
        *transmit_message_buffer++ = *(message_address+index);
   }
   // do real transmit here, drop data into register
   FlexCAN_Transmit_Message(&FlexCAN_A,
                            FlexCAN_MSGOBJ_Get_Index((CAN_Message_Parameter_Table_Ptr+CAN_transmit_message_number)->in_configuration),
                            (uint32_t)can_id, 
                            message_address,
                            (CAN_Message_Parameter_Table_Ptr+CAN_transmit_message_number)->CAN_message_length);

   return true;
}


/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
******************************************************************************/

