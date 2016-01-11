/*****************************************************************************
* Copyright 2010 Delphi Technologies, Inc., All Rights Reserved             *
* AUTHORS: Sandeep,Prakash                                                  *
* Project: J1939 - PGN Timer Configuration                                  *
* File Name:  j1939_pgn_config.h                                               *
* File Description:                                                         *
* This module contains J1939 PGN transmit and receive timer configurations. *
*****************************************************************************/
#ifndef J1939_PGN_CONFIG_H
#define J1939_PGN_CONFIG_H

#include "j1939_data_types.h"
#include "hwiocald.h"
#include "ssd_types.h"


/*******************************************************************************
 * START OF COMPILE MACRO'S FOR LAYER SELECTION
 ******************************************************************************/
#define J1939_TEST_STUB

/******************************************************************************
*   CONFIGURATION FOR J1939 Source address and Global destination address
******************************************************************************/
#define J1939_GLOBAL_DEST_ADDR            (0xFF)
//#define J1939_THIS_ADDR                 (0x00)
#define J1939_BASE_LOOP                   (5)

/******************************************************************************
*                                          CONFIGURATION FOR J1939 Channels
******************************************************************************/

#define J1939_NO_OF_CHANNELS_SUPPORTED       ( 1 )

#define J1939_CH0_SELECTED
#undef J1939_CH1_SELECTED
#undef J1939_CH2_SELECTED

/******************************************************************************
*                                          CONFIGURATION FOR J1939 Messages
******************************************************************************/
#define J1939_RECEIVE_MESSAGES_NUMBER_SUPPORTED     ( 24 )
#define J1939_TRANSMIT_MESSAGES_NUMBER_SUPPORTED    ( 40 )

#define J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_0     ( 13 )
#define J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_1     ( 0 )

#define J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_0    ( 25 )
#define J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_1    ( 0 )

#define J1939_RECEIVE_MESSAGES_NUMBER    ( J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_0 +\
                                          J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_1 )

#define J1939_TRANSMIT_MESSAGES_NUMBER   ( J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_0 +\
                                          J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_1 )

#define J1939_MESSAGES_NUMBER   ( J1939_RECEIVE_MESSAGES_NUMBER + \
                                 J1939_TRANSMIT_MESSAGES_NUMBER    )

/******************************************************************************
 *  Sanity Check: will cause compiler error
 *                if incompatible options are selected.
 *****************************************************************************/
#if ( (J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_0 > J1939_RECEIVE_MESSAGES_NUMBER_SUPPORTED) \
      || (J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_0 > J1939_TRANSMIT_MESSAGES_NUMBER_SUPPORTED) \
      || (J1939_RECEIVE_MESSAGES_NUMBER_SUPPORTED > 24) \
      || (J1939_TRANSMIT_MESSAGES_NUMBER_SUPPORTED > 40))
#error "(!) J1939 Message Number Configuration ERROR"
#endif

extern const uint8_t J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_0;
extern const uint8_t J1939_NO_OF_RECEIVE_MESSAGES_CHANNEL_1;
extern const uint8_t J1939_NO_OF_TRANSMIT_MESSAGES_CHANNEL_0;
extern const uint8_t J1939_NO_OF_TRANSMIT_MESSAGES_CHANNEL_1;

extern const uint8_t J1939_NO_OF_RECEIVE_MESSAGES;
extern const uint8_t J1939_NO_OF_TRANSMIT_MESSAGES;
extern const uint8_t J1939_NO_OF_MESSAGES;
/************************************************************************/
/* ENUMERATION: TxIndexType                                             */
/* Description: Maps a Transmit message to its corresponding            */
/*                index within TxMsgCtrl[]                              */
/* WARNING!!!: This enum must agree with TxInitRoutine[]                */
/************************************************************************/

typedef enum {
  J1939_TX_TRANSPORT_OUT_0,
  J1939_TX_TRANSPORT_OUT_1,
  J1939_TX_TRANSPORT_OUT_2,

  J1939_TX_TRANSPORT_IN_0,
  J1939_TX_TRANSPORT_IN_1,
  J1939_TX_TRANSPORT_IN_2,
  
  J1939_TX_PGN_65226_INDEX, 
  J1939_TX_PGN_65227_INDEX,
  J1939_TX_PGN_65228_INDEX, 
  J1939_TX_PGN_65229_INDEX,
  J1939_TX_PGN_65235_INDEX,
  J1939_TX_PGN_65236_INDEX,

  J1939_TX_PGN_65249_INDEX,
  J1939_TX_PGN_65251_INDEX,
   
  J1939_TX_PGN_65280_INDEX,
  J1939_TX_PGN_65281_INDEX,
  J1939_TX_PGN_65282_INDEX,
  J1939_TX_PGN_65283_INDEX,
  J1939_TX_PGN_65284_INDEX,
  J1939_TX_PGN_65285_INDEX,
  J1939_TX_PGN_65286_INDEX,
  J1939_TX_PGN_65287_INDEX,
  J1939_TX_PGN_65288_INDEX,
  J1939_TX_PGN_65289_INDEX,
  J1939_TX_PGN_Denny_INDEX,
  CAN_NUM_TX_MSGS,
  INVALID_TX_INDEX
  } TxMsgIndexType;

/******************************************************/
/*      E X T E R N    D E C L A R A T I O N S        */
/******************************************************/

/* Transmit Initialization */
extern const void(*const J1939_Transmit_Initialize[]) (J1939_Transmit_Message_Control_T *);
/* Receive Initialization */
extern const void(*const J1939_Receive_Initialize_Channel_0[]) (J1939_Receive_Message_Control_T *);

#define CAN_NO_PERIODIC_SERVICE         (0)
#define CAN_NO_LOST_TIMER               (0)
#define CAN_FASTEST_PERIODIC_SERVICE    (1)

#define J1939_GET_SRC_ADDR(id)           ((id) & 0xFF)
#define J1939_GET_DEST_ADDR(id)          (((id) & 0xFF00) >> 8)
#define J1939_PUT_SRC_ADDR(id, addr)     (((id) & 0xFFFFFF00UL) | (addr))
#define J1939_PUT_DEST_ADDR(id, addr)    (((id) & 0xFFFF00FFUL) | ((addr) << 8))
#define J1939_ADD_THIS_SRC_ADDR(id)      (((id) & 0xFFFFFF00UL) | (uint32_t)(KfHWIO_J193973_SA))

#define J1939_DENY_REQUEST_PGN             (0xFFFFFFFF)
#define J1939_DATA_NOT_AVAILABLE           (0xFF)
/************************************************************************/
/* DEFINE: J1939_PGN...                                                 */
/* Description: J1939 PGN specific values                               */
/************************************************************************/

/******************************************************************************/
/* PGN: Receive                                                               */
/******************************************************************************/

/***********************************************************************/
/* 65271 Electrical Power                                              */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65271)                               */
/*  |  |   | | PGN (PF = 254, PS = 247 => PGN = 65271)                 */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1111 1110 1111 0111,xxxx xxxx                           */
/* 0001/1000/1111/1110/1111/0111/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65271_BASE_ID               0x18FEF7D5
#define J1939_PGN_65271_LENGTH                8
#define J1939_PGN_65271_FREQ                  (10/J1939_BASE_LOOP)
#define J1939_PGN_65271_TIMEOUT               (30/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65271(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_59904_BASE_ID               0x18EA0000
#define J1939_PGN_59904_LENGTH                8
#define J1939_PGN_59904_FREQ                  (10/J1939_BASE_LOOP)
#define J1939_PGN_59904_TIMEOUT               (30/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_59904(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65272_BASE_ID               0x18FEF8D5
#define J1939_PGN_65272_LENGTH                8
#define J1939_PGN_65272_FREQ                  (10/J1939_BASE_LOOP)
#define J1939_PGN_65272_TIMEOUT               (30/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65272(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65273_BASE_ID               0x18FEF9D5
#define J1939_PGN_65273_LENGTH                8
#define J1939_PGN_65273_FREQ                  (10/J1939_BASE_LOOP)
#define J1939_PGN_65273_TIMEOUT               (30/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65273(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65274_BASE_ID               0x18FEFAD5
#define J1939_PGN_65274_LENGTH                8
#define J1939_PGN_65274_FREQ                  (10/J1939_BASE_LOOP)
#define J1939_PGN_65274_TIMEOUT               (30/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65274(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65275_BASE_ID               0x18FEFBD5
#define J1939_PGN_65275_LENGTH                8
#define J1939_PGN_65275_FREQ                  (10/J1939_BASE_LOOP)
#define J1939_PGN_65275_TIMEOUT               (30/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65275(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

/***********************************************************************/
/* 65276 Dash Display Fuel Level                                       */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65276)                               */
/*  |  |   | | PGN (PF = 254, PS = 252 => PGN = 65276)                 */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1111 1110 1111 1100,xxxx xxxx                           */
/* 0001/1000/1111/1110/1111/1100/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65276_BASE_ID               0x18FEFCD0
#define J1939_PGN_65276_LENGTH                8
#define J1939_PGN_65276_FREQ                  (20/J1939_BASE_LOOP)
#define J1939_PGN_65276_TIMEOUT               (60/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65276(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65277_BASE_ID               0x18FEFDD0
#define J1939_PGN_65277_LENGTH                8
#define J1939_PGN_65277_FREQ                  (20/J1939_BASE_LOOP)
#define J1939_PGN_65277_TIMEOUT               (60/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65277(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65278_BASE_ID               0x18FEFED0
#define J1939_PGN_65278_LENGTH                8
#define J1939_PGN_65278_FREQ                  (20/J1939_BASE_LOOP)
#define J1939_PGN_65278_TIMEOUT               (60/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65278(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65279_BASE_ID               0x18FEFFD0
#define J1939_PGN_65279_LENGTH                8
#define J1939_PGN_65279_FREQ                  (20/J1939_BASE_LOOP)
#define J1939_PGN_65279_TIMEOUT               (60/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65279(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65296                                                                */
/******************************************************************************/
#define J1939_PGN_65296_BASE_ID               0x08FF10D5
#define J1939_PGN_65296_LENGTH                8
#define J1939_PGN_65296_FREQ                  (50/J1939_BASE_LOOP)
#define J1939_PGN_65296_TIMEOUT               (150/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65296(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

extern void J1939_RxInit_PGN_59904 (J1939_Receive_Message_Control_T *MsgCtrl);

extern const J1939_Message_Table_T   J1939_Message_Table[J1939_MESSAGES_NUMBER];
/******************************************************************************/
/* PGN: Transmit                                                              */
/******************************************************************************/

extern void J1939_TxInit_TransportOut_0(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J1939_TxInit_TransportOut_1(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J1939_TxInit_TransportOut_2(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J1939_TxInit_TransportIn_0(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J1939_TxInit_TransportIn_1(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J1939_TxInit_TransportIn_2(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65226(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65227(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65229(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65228_Ack (J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65235_Ack (J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65236(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65249(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65251(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J1939_SendUnmanagedAcknowledgement (AckModeType Mode, uint32_t RequestedPgn);
extern void J1939_RequestTxMsgService (TxMsgIndexType index, uint8_t requester);
extern void J1939_Trigger_Transmit_Message_Service (uint8_t Index);
extern void J1939_Event_Trigger_Transmit(uint8_t index);
//extern bool J1939_Transmit_Unmanaged_Message (J1939_Transmit_Message_Info_T *Tx_Message);

/***********************************************************************/
/* 59392 Acknowledgment of command                                     */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 59392)                               */
/*  |  |   | | PGN (PF = 232, PS=DA (always 255) => PGN = 59329 + 255) */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_59392_BASE_ID                (0x18E80000UL) /* E800 = 59392 */
#define J1939_PGN_59392_LENGTH                 (8)
#define J1939_PGN_59392                        (0x0000E800UL)
#define J1939_PGN_59392_FREQ                   (CAN_NO_PERIODIC_SERVICE)
#define J1939_PGN_59392_TIMEOUT                (20 / J1939_BASE_LOOP) // 20ms

/***********************************************************************/
/* 65226 J1939/73 DM1 - Active DTC's and lamp status                   */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65226)                               */
/*  |  |   | | PGN (PF = 254, PS = 202 => PGN = 65226)                 */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1111 1110 1100 1010,xxxx xxxx                           */
/* 0001/1000/1111/1110/1100/1010/xxxx/xxxx                             */
/***********************************************************************/
#define J193973_PGN_65226_BASE_ID              (0x18FECA00UL) /*FFCA=65226,Prio=6,src=0*/
#define J193973_PGN_65226_LENGTH               (8)
#define J193973_PGN_65226                      (0x0000FECAUL)
#define J193973_PGN_65226_FREQ                 (1000 / J1939_BASE_LOOP)
#define J1939_PGN_65226_TIMEOUT                (1500 / J1939_BASE_LOOP) // Timeout set to 1.5s

/******************************************************************************/
/* PGN: 65227 DM2                                                             */
/******************************************************************************/
#define J193973_PGN_65227_BASE_ID              (0x18FECB00UL) /*FFCB=65227,Prio=6,src=0*/
#define J193973_PGN_65227_LENGTH               (8)
#define J193973_PGN_65227                      (0x0000FECBUL)
#define J193973_PGN_65227_FREQ                 (0)
#define J1939_PGN_65227_TIMEOUT                (0) 

/******************************************************************************/
/* PGN: 65228 DM3                                                             */
/******************************************************************************/
#define J193973_PGN_65228_BASE_ID              (0x18FECC00UL) /*FFCC=65228,Prio=6,src=0*/
#define J193973_PGN_65228_LENGTH               (8)
#define J193973_PGN_65228                      (0x0000FECCUL)
#define J193973_PGN_65228_FREQ                 (0)
#define J1939_PGN_65228_TIMEOUT                (0) 

/******************************************************************************/
/* PGN: 65228 DM4                                                             */
/******************************************************************************/
#define J193973_PGN_65229_BASE_ID              (0x18FECD00UL) /*FFCD=65229,Prio=6,src=0*/
#define J193973_PGN_65229_LENGTH               (8)
#define J193973_PGN_65229                      (0x0000FECDUL)
#define J193973_PGN_65229_FREQ                 (0)
#define J1939_PGN_65229_TIMEOUT                (0) 

/******************************************************************************/
/* PGN: 65235 DM11                                                             */
/******************************************************************************/
#define J193973_PGN_65235_BASE_ID              (0x18FED300UL) /*FFD3=65235,Prio=6,src=0*/
#define J193973_PGN_65235_LENGTH               (8)
#define J193973_PGN_65235                      (0x0000FED3UL)
#define J193973_PGN_65235_FREQ                 (0)
#define J1939_PGN_65235_TIMEOUT                (0) 

/******************************************************************************/
/* PGN: 65236 DM12                                                             */
/******************************************************************************/
#define J193973_PGN_65236_BASE_ID              (0x18FED400UL) /*FFD4=65236,Prio=6,src=0*/
#define J193973_PGN_65236_LENGTH               (8)
#define J193973_PGN_65236                      (0x0000FED4UL)
#define J193973_PGN_65236_FREQ                 (0)
#define J1939_PGN_65236_TIMEOUT                (0) 
/******************************************************************************/
/* PGN: 65249                                                             */
/******************************************************************************/
#define J193973_PGN_65249_BASE_ID              (0x18FEE100UL) /*FFCA=65249,Prio=6,src=0*/
#define J193973_PGN_65249_LENGTH               (8)
#define J193973_PGN_65249                      (0x0000FEE1UL)
#define J193973_PGN_65249_FREQ                 (5000/ J1939_BASE_LOOP)
#define J1939_PGN_65249_TIMEOUT                (15000/ J1939_BASE_LOOP) 
/******************************************************************************/
/* PGN: 65251                                                             */
/******************************************************************************/

#define J193973_PGN_65251_BASE_ID              (0x18FEE300UL)
#define J193973_PGN_65251_LENGTH               (8)
#define J193973_PGN_65251                      (0x0000FEE3UL)
#define J193973_PGN_65251_FREQ                 (KfHWIO_J193973_PGN_65251_FREQ/ J1939_BASE_LOOP)
#define J1939_PGN_65251_TIMEOUT                ((KfHWIO_J193973_PGN_65251_FREQ*3)/ J1939_BASE_LOOP) 

/******************************************************************************/
/* PGN: 65280                                                                */
/******************************************************************************/
#define J1939_PGN_65280_BASE_ID                0x04FF00D2
#define J1939_PGN_65280_LENGTH                 1
#define J1939_PGN_65280_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65280_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65280(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65281                                                                */
/******************************************************************************/
#define J1939_PGN_65281_BASE_ID                0x04FF01D2
#define J1939_PGN_65281_LENGTH                 2
#define J1939_PGN_65281_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65281_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65281(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65282                                                                */
/******************************************************************************/
#define J1939_PGN_65282_BASE_ID                0x04FF02D2
#define J1939_PGN_65282_LENGTH                 3
#define J1939_PGN_65282_FREQ                   (10/J1939_BASE_LOOP)
#define J1939_PGN_65282_TIMEOUT                (30/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65282(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65283                                                                */
/******************************************************************************/
#define J1939_PGN_65283_BASE_ID                0x04FF03D2
#define J1939_PGN_65283_LENGTH                 4
#define J1939_PGN_65283_FREQ                   (20/J1939_BASE_LOOP)
#define J1939_PGN_65283_TIMEOUT                (60/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65283(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65284                                                                */
/******************************************************************************/
#define J1939_PGN_65284_BASE_ID                0x04FF04D2
#define J1939_PGN_65284_LENGTH                 5
#define J1939_PGN_65284_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65284_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65284(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65285                                                                */
/******************************************************************************/
#define J1939_PGN_65285_BASE_ID                0x04FF05D2
#define J1939_PGN_65285_LENGTH                 6
#define J1939_PGN_65285_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65285_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65285(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65286                                                              */
/******************************************************************************/
#define J1939_PGN_65286_BASE_ID                0x04FF06D2
#define J1939_PGN_65286_LENGTH                 7
#define J1939_PGN_65286_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65286_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65286(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65287                                                                */
/******************************************************************************/
#define J1939_PGN_65287_BASE_ID                0x04FF07D2
#define J1939_PGN_65287_LENGTH                 8
#define J1939_PGN_65287_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65287_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65287(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);


/******************************************************************************/
/* PGN: 65288                                                                */
/******************************************************************************/
#define J1939_PGN_65288_BASE_ID                0x04FF08D2
#define J1939_PGN_65288_LENGTH                 8
#define J1939_PGN_65288_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65288_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65288(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 65289                                                                */
/******************************************************************************/
#define J1939_PGN_65289_BASE_ID                0x04FF09D2
#define J1939_PGN_65289_LENGTH                 8
#define J1939_PGN_65289_FREQ                   (50/J1939_BASE_LOOP)
#define J1939_PGN_65289_TIMEOUT                (150/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65289(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/******************************************************************************/
/* PGN: 59392                                                               */
/******************************************************************************/
extern void J1939_TxInit_SendUnmanagedAcknowledgement(J1939_Transmit_Message_Control_T *MsgCtrl);

/* TP Configuration */
/************************************************************************/
/* DEFINE: J1939_TP_BROADCAST_DELAY_TIME                                */
/* Description: Delay time after sending J1939 BAM frame, before the DT */
/*                frames can be sent. Also delay time between data      */
/*                packets of blobal broadcast message                   */
/************************************************************************/
#define J1939_TP_BROADCAST_DELAY_TIME       (50 / J1939_BASE_LOOP) // 50ms

/************************************************************************/
/* DEFINE: J1939_TP_DEST_SPECIFIC_DELAY_TIME                            */
/* Description: Delay time between sending J1939 DT frames to           */
/*              destination specific address                            */
/************************************************************************/
#define J1939_TP_DEST_SPECIFIC_DELAY_TIME    (50 / J1939_BASE_LOOP) // 50ms

/************************************************************************/
/* DEFINE: J1939_TP_DATA_TIMEOUT                                        */
/* Description: Time between data packets timout (T1)                   */
/************************************************************************/
#define J1939_TP_DATA_TIMEOUT    (10 / J1939_BASE_LOOP) // 10ms

/************************************************************************/
/* DEFINE: J1939_TP_POST_CTS_TIMEOUT                                    */
/* Description: Time after Clear-to-Send (waiting for data) timeout (T2)*/
/************************************************************************/
#define J1939_TP_POST_CTS_TIMEOUT    (40 / J1939_BASE_LOOP) // 40ms

/************************************************************************/
/* DEFINE: J1939_TP_CTS_TIMEOUT                                         */
/* Description: Timeout while waiting for a CTS or ACK (T3)             */
/************************************************************************/
#define J1939_TP_MISSING_CTS_ACK_TIMEOUT    (30 / J1939_BASE_LOOP) // 30ms

/************************************************************************/
/* DEFINE: J1939_TP_HOLD_TIMEOUT                                        */
/* Description: TImeout after receiving a hold (CTS 0) (T4)             */
/************************************************************************/
#define J1939_TP_HOLD_TIMEOUT    (30 / J1939_BASE_LOOP) // 30ms

/************************************************************************/
/* DEFINE: J1939_DM1_BUFFER_SIZE                                        */
/* Description: Buffer size to store the lamp staus and the active DTCs */
/************************************************************************/
#define J1939_DM1_BUFFER_SIZE  (14)

/************************************************************************/
/* DEFINE: J1939_DM2_BUFFER_SIZE                                        */
/* Description: Buffer size to store the lamp staus and the previously  */
/*              active DTCs                                             */
/************************************************************************/
#define J1939_DM2_BUFFER_SIZE  (14)

/************************************************************************/
/* DEFINE: J1939_DM4_BUFFER_SIZE                                        */
/* Description: Buffer size to store the freeze frame                   */
/************************************************************************/
#define J1939_DM4_BUFFER_SIZE  (14)

/************************************************************************/
/* DEFINE: J1939_DM12_BUFFER_SIZE                                       */
/* Description: Buffer size to store the lamp staus and the             */
/*              emissions-related  active DTCs                          */
/************************************************************************/
#define J1939_DM12_BUFFER_SIZE (14)

#define J1939_PGN_65249_BUFFER_SIZE (19)
#define J1939_PGN_65251_BUFFER_SIZE (34)

#endif
/*-------------------------------------------------------------------*/
/* j1939_pgn_config.h  rev.     - 22 Aug 2014 - Xi Yanpeng           */
/*                                                                   */
/* -Add PGN65251 PGN65259 Configurations                             */
/*-------------------------------------------------------------------*/