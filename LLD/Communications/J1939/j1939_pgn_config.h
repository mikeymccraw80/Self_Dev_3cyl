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
//J1939_Handler_Periodic_Task was scheduled in 10ms periodic task.
#define J1939_BASE_LOOP                   (10)

/******************************************************************************
*                                          CONFIGURATION FOR J1939 Channels
******************************************************************************/

#define J1939_NO_OF_CHANNELS_SUPPORTED       ( 1 )

#define J1939_CH0_SELECTED
#undef J1939_CH1_SELECTED
#undef J1939_CH2_SELECTED

/******************************************************************************
*                                          J1939 PGN Supported Config
******************************************************************************/
//for rx pgns
#define J1939_PGN_59904_SUPPORTED             1   //tp pgn
#define J1939_PGN_60160_SUPPORTED             1   //tp pgn
#define J1939_PGN_60416_SUPPORTED             1   //tp pgn
#define J1939_PGN_57344_SUPPORTED             1   //jd rx pgn
#define J1939_PGN_00000_SUPPORTED             1   //jd rx pgn
#define J1939_73_dm7_SUPPORTED                   1
#define J1939_73_dm13_SUPPORTED                 1
#define J1939_PGN_65265_SUPPORTED             1   //jd rx pgn
#define J1939_PGN_64971_SUPPORTED             1   //jd rx pgn
#define J1939_PGN_61442_SUPPORTED             1   //jd rx pgn
#define J1939_PGN_61445_SUPPORTED             1   //jd rx pgn
#define J1939_PGN_65298_SUPPORTED             1   //jd rx pgn
#define J1939_PGN_65276_SUPPORTED             0
#define J1939_PGN_65277_SUPPORTED             0
#define J1939_PGN_65278_SUPPORTED             0
#define J1939_PGN_65279_SUPPORTED             0
#define J1939_PGN_65296_SUPPORTED             0
#define J1939_PGN_55808_SUPPORTED             0



//for tx pgns
#define J1939_DENY_REQUEST_SUPPORTED          1
#define J193973_PGN_65226_SUPPORTED           1
#define J193973_PGN_65227_SUPPORTED           1
#define J193973_PGN_65228_SUPPORTED           1
#define J193973_PGN_65229_SUPPORTED           1
#define J193973_PGN_65230_SUPPORTED           1
#define J193973_PGN_65235_SUPPORTED           1
#define J193973_PGN_65236_SUPPORTED           0
#define J193973_PGN_65249_SUPPORTED           0
#define J193973_PGN_65251_SUPPORTED           1
#define J1939_PGN_64965_SUPPORTED             1
#define J1939_PGN_65242_SUPPORTED             1
#define J1939_PGN_61444_SUPPORTED             1
#define J1939_PGN_61443_SUPPORTED             1
#define J1939_PGN_65247_SUPPORTED             1
#define J1939_PGN_64997_SUPPORTED             1
#define J1939_PGN_65154_SUPPORTED             1
#define J1939_PGN_65266_SUPPORTED             1
#define J1939_PGN_65262_SUPPORTED             1
#define J1939_PGN_65263_SUPPORTED             1
#define J1939_PGN_65270_SUPPORTED             1
#define J1939_PGN_65271_SUPPORTED             1
#define J1939_PGN_65213_SUPPORTED             1
#define J1939_PGN_65253_SUPPORTED             0
#define J1939_PGN_65232_SUPPORTED             1
#define J1939_PGN_65289_SUPPORTED             1
#define J1939_PGN_60928_SUPPORTED             1
#define J1939_PGN_65299_SUPPORTED             1
/******************************************************************************
*                                          CONFIGURATION FOR J1939 Messages
******************************************************************************/
#define J1939_RECEIVE_MESSAGES_NUMBER_SUPPORTED       ( 24 )
#define J1939_TRANSMIT_MESSAGES_NUMBER_SUPPORTED    ( 40 )

#define  J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_0 ( 	J1939_PGN_59904_SUPPORTED 	+\
														J1939_PGN_60160_SUPPORTED	+\
														J1939_PGN_60416_SUPPORTED	+\
														J1939_PGN_57344_SUPPORTED 	+\
														J1939_PGN_00000_SUPPORTED	+\
														J1939_PGN_65265_SUPPORTED	+\
														J1939_PGN_64971_SUPPORTED	+\
														J1939_PGN_61442_SUPPORTED	+\
														J1939_PGN_61445_SUPPORTED	+\
														J1939_PGN_65298_SUPPORTED	+\
														J1939_PGN_65276_SUPPORTED	+\
														J1939_PGN_65277_SUPPORTED	+\
														J1939_PGN_65278_SUPPORTED	+\
														J1939_PGN_65279_SUPPORTED	+\
														J1939_PGN_65296_SUPPORTED+\
														J1939_73_dm7_SUPPORTED	+\
														J1939_73_dm13_SUPPORTED    +\
														J1939_PGN_55808_SUPPORTED)
#define J1939_RECEIVE_MESSAGES_NUMBER_CHANNEL_1     ( 0 )

#define  J1939_TRANSMIT_MESSAGES_NUMBER_CHANNEL_0 (6 + J1939_DENY_REQUEST_SUPPORTED	+\
															  J193973_PGN_65226_SUPPORTED	+\
															  J193973_PGN_65227_SUPPORTED	+\
															  J193973_PGN_65228_SUPPORTED	+\
															  J193973_PGN_65229_SUPPORTED	+\
															  J193973_PGN_65230_SUPPORTED	+\
															  J193973_PGN_65235_SUPPORTED	+\
															  J193973_PGN_65236_SUPPORTED	+\
															  J193973_PGN_65249_SUPPORTED	+\
															  J193973_PGN_65251_SUPPORTED	+\
															  J1939_PGN_64965_SUPPORTED		+\
															  J1939_PGN_65242_SUPPORTED		+\
															  J1939_PGN_61444_SUPPORTED		+\
															  J1939_PGN_61443_SUPPORTED		+\
															  J1939_PGN_65247_SUPPORTED		+\
															  J1939_PGN_64997_SUPPORTED		+\
															  J1939_PGN_65154_SUPPORTED		+\
															  J1939_PGN_65266_SUPPORTED		+\
															  J1939_PGN_65262_SUPPORTED		+\
															  J1939_PGN_65263_SUPPORTED		+\
															  J1939_PGN_65270_SUPPORTED		+\
															  J1939_PGN_65271_SUPPORTED		+\
															  J1939_PGN_65213_SUPPORTED		+\
															  J1939_PGN_65253_SUPPORTED		+\
															  J1939_PGN_65232_SUPPORTED		+\
															  J1939_PGN_65289_SUPPORTED		+\
															  J1939_PGN_55808_SUPPORTED			+\
															  J1939_PGN_60928_SUPPORTED    +\
															  J1939_PGN_65299_SUPPORTED)                 
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
#if J1939_DENY_REQUEST_SUPPORTED
  J1939_TX_TRANSPORT_OUT_0,
  J1939_TX_TRANSPORT_OUT_1,
  J1939_TX_TRANSPORT_OUT_2,

  J1939_TX_TRANSPORT_IN_0,
  J1939_TX_TRANSPORT_IN_1,
  J1939_TX_TRANSPORT_IN_2,
#endif                       
#if J193973_PGN_65226_SUPPORTED  
  J1939_TX_PGN_65226_INDEX, 
#endif
#if J193973_PGN_65227_SUPPORTED
  J1939_TX_PGN_65227_INDEX,
#endif
#if J193973_PGN_65228_SUPPORTED 
  J1939_TX_PGN_65228_INDEX, 
 #endif
#if J193973_PGN_65229_SUPPORTED 
  J1939_TX_PGN_65229_INDEX,
#endif
#if J193973_PGN_65230_SUPPORTED  
  J1939_TX_PGN_65230_INDEX,
 #endif
#if J193973_PGN_65235_SUPPORTED 
  J1939_TX_PGN_65235_INDEX,
#endif
#if J193973_PGN_65236_SUPPORTED
  J1939_TX_PGN_65236_INDEX,
#endif
#if J193973_PGN_65249_SUPPORTED
  J1939_TX_PGN_65249_INDEX,
#endif
#if J193973_PGN_65251_SUPPORTED
  J1939_TX_PGN_65251_INDEX,
#endif
#if J1939_PGN_64965_SUPPORTED   
  J1939_TX_PGN_64965_INDEX,
#endif
#if J1939_PGN_65242_SUPPORTED
  J1939_TX_PGN_65242_INDEX,
#endif
#if J1939_PGN_61444_SUPPORTED
  J1939_TX_PGN_61444_INDEX,
#endif
#if J1939_PGN_61443_SUPPORTED
  J1939_TX_PGN_61443_INDEX,
#endif
#if J1939_PGN_65247_SUPPORTED
  J1939_TX_PGN_65247_INDEX,
#endif
#if J1939_PGN_64997_SUPPORTED
  J1939_TX_PGN_64997_INDEX,
#endif
#if J1939_PGN_65266_SUPPORTED
  J1939_TX_PGN_65266_INDEX,
#endif
#if J1939_PGN_65262_SUPPORTED
  J1939_TX_PGN_65262_INDEX,
#endif
#if J1939_PGN_65263_SUPPORTED
  J1939_TX_PGN_65263_INDEX,
#endif
#if J1939_PGN_65270_SUPPORTED
  J1939_TX_PGN_65270_INDEX,
#endif
#if J1939_PGN_65271_SUPPORTED
  J1939_TX_PGN_65271_INDEX,
#endif
#if J1939_PGN_65213_SUPPORTED
  J1939_TX_PGN_65213_INDEX,
#endif
#if J1939_PGN_65253_SUPPORTED
  J1939_TX_PGN_65253_INDEX,
#endif
#if J1939_PGN_65232_SUPPORTED
  J1939_TX_PGN_65232_INDEX,
#endif
#if J1939_PGN_65289_SUPPORTED
  J1939_TX_PGN_65289_INDEX,
#endif
#if J1939_PGN_60928_SUPPORTED
   J1939_TX_PGN_60928_INDEX, /* john deere Address Claim */
#endif
#if J1939_PGN_65299_SUPPORTED
   J1939_TX_PGN_65299_INDEX, /* john deere Defined PGN */
#endif
#if J1939_PGN_65154_SUPPORTED
  J1939_TX_PGN_65154_INDEX,
#endif
#if J1939_PGN_55808_SUPPORTED
   J1939_TX_PGN_55808_INDEX,
#endif
#if J1939_DENY_REQUEST_SUPPORTED  
  J1939_TX_PGN_Denny_INDEX,
#endif  
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
#define J1939_PGN_59904_BASE_ID               0x18EA0000
#define J1939_PGN_59904_LENGTH                8
#define J1939_PGN_59904_FREQ                  (10/J1939_BASE_LOOP)
#define J1939_PGN_59904_TIMEOUT               (30/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_59904(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_57344_BASE_ID               0x18E00017
#define J1939_PGN_57344_LENGTH                8
#define J1939_PGN_57344_FREQ                  (KfHWIO_J1939_PGN_57344_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_57344_TIMEOUT               (KfHWIO_J1939_PGN_57344_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_57344(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_00000_BASE_ID               0x0C000017
#define J1939_PGN_00000_LENGTH                8
#define J1939_PGN_00000_FREQ                  (KfHWIO_J1939_PGN_00000_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_00000_TIMEOUT               (KfHWIO_J1939_PGN_00000_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_00000(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65265_BASE_ID               0x18FEF117
#define J1939_PGN_65265_LENGTH                8
#define J1939_PGN_65265_FREQ                  (KfHWIO_J1939_PGN_65265_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65265_TIMEOUT               (KfHWIO_J1939_PGN_65265_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65265(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_64971_BASE_ID               0x18FDCB17
#define J1939_PGN_64971_LENGTH                8
#define J1939_PGN_64971_FREQ                  (KfHWIO_J1939_PGN_64971_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_64971_TIMEOUT               (KfHWIO_J1939_PGN_64971_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_64971(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_61442_BASE_ID               0x0CF00217
#define J1939_PGN_61442_LENGTH                8
#define J1939_PGN_61442_FREQ                  (KfHWIO_J1939_PGN_61442_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_61442_TIMEOUT               (KfHWIO_J1939_PGN_61442_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_61442(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_61445_BASE_ID               0x18F00517
#define J1939_PGN_61445_LENGTH                8
#define J1939_PGN_61445_FREQ                  (KfHWIO_J1939_PGN_61445_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_61445_TIMEOUT               (KfHWIO_J1939_PGN_61445_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_61445(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

#define J1939_PGN_65298_BASE_ID               0x0CFF1217
#define J1939_PGN_65298_LENGTH                8
#define J1939_PGN_65298_FREQ                  (KfHWIO_J1939_PGN_65298_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65298_TIMEOUT               (KfHWIO_J1939_PGN_65298_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Receive_Initialize_PGN_65298(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

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
/* PGN: DA00                                                               */
/******************************************************************************/
#define J1939_PGN_55808_BASE_ID               0x18DA0000
#define J1939_PGN_55808_LENGTH                8
#define J1939_PGN_55808_FREQ                  (0)
#define J1939_PGN_55808_TIMEOUT               (0)
extern void J1939_RxInit_PGN_55808(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);
extern void J1939_TxInit_PGN_55808(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

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
extern void J193973_TxInit_PGN_65230(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65228_Ack (J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65235_Ack (J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65236(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65249(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65251(J1939_Transmit_Message_Control_T *MsgCtrl);
extern void J193973_TxInit_PGN_65232(J1939_Transmit_Message_Control_T * MsgCtrl);
extern void J1939_TxInit_PGN_65289(J1939_Transmit_Message_Control_T * MsgCtrl);
extern void J1939_TxInit_PGN_60928(J1939_Transmit_Message_Control_T * MsgCtrl);
extern void J1939_TxInit_PGN_65299(J1939_Transmit_Message_Control_T * MsgCtrl);
extern void J1939_TxInit_PGN_65154(J1939_Transmit_Message_Control_T * MsgCtrl);
extern void J1939_SendUnmanagedAcknowledgement (AckModeType Mode, uint32_t RequestedPgn);
extern void J1939_RequestTxMsgService (TxMsgIndexType index, uint8_t requester);
extern void J1939_Trigger_Transmit_Message_Service (uint8_t Index);
extern void J1939_Event_Trigger_Transmit(uint8_t index);
extern bool J1939_Transmit_Unmanaged_Message (J1939_Transmit_Message_Info_T *Tx_Message);

/***********************************************************************/
/* 65262 ET1                                                           */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65262)                               */
/*  |  |   | | PGN (PF = 254, PS= 238 )                                */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65262_BASE_ID               0x18FEEED5
#define J1939_PGN_65262_LENGTH                8
#define J1939_PGN_65262_FREQ                  (KfHWIO_J1939_PGN_65262_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65262_TIMEOUT               (KfHWIO_J1939_PGN_65262_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65262(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);
/***********************************************************************/
/* 65263 EFL/P1                                                        */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65263)                               */
/*  |  |   | | PGN (PF = 254, PS= 239 )                                */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65263_BASE_ID               0x18FEEFD5
#define J1939_PGN_65263_LENGTH                8
#define J1939_PGN_65263_FREQ                  (KfHWIO_J1939_PGN_65263_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65263_TIMEOUT               (KfHWIO_J1939_PGN_65263_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65263(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 65266 LFE                                                           */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65266)                               */
/*  |  |   | | PGN (PF = 254, PS= 242 )                                */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65266_BASE_ID               0x18FEF2D5
#define J1939_PGN_65266_LENGTH                8
#define J1939_PGN_65266_FREQ                  (KfHWIO_J1939_PGN_65266_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65266_TIMEOUT               (KfHWIO_J1939_PGN_65266_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65266(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 61444 EEC1                                                          */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 61444)                               */
/*  |  |   | | PGN (PF = F0, PS=04 )                                */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_61444_BASE_ID               0x0CF004D5
#define J1939_PGN_61444_LENGTH                8
#define J1939_PGN_61444_FREQ                  (KfHWIO_J1939_PGN_61444_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_61444_TIMEOUT               (KfHWIO_J1939_PGN_61444_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_61444(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 61443 EEC2                                                          */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 61443)                               */
/*  |  |   | | PGN (PF = F0, PS= 03 )                                  */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_61443_BASE_ID               0x0CF003D5
#define J1939_PGN_61443_LENGTH                8
#define J1939_PGN_61443_FREQ                  (KfHWIO_J1939_PGN_61443_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_61443_TIMEOUT               (KfHWIO_J1939_PGN_61443_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_61443(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 61443 EEC3                                                          */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 61443)                               */
/*  |  |   | | PGN (PF = F0, PS= 03 )                                  */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65247_BASE_ID               0x18FEDFD5
#define J1939_PGN_65247_LENGTH                8
#define J1939_PGN_65247_FREQ                  (KfHWIO_J1939_PGN_65247_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65247_TIMEOUT               (KfHWIO_J1939_PGN_65247_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65247(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 64997 mvs                                                           */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 64997)                               */
/*  |  |   | | PGN (PF = FD, PS=E5 )                                   */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_64997_BASE_ID               0x18FDE500
#define J1939_PGN_64997_LENGTH                8
#define J1939_PGN_64997_FREQ                  (KfHWIO_J1939_PGN_64997_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_64997_TIMEOUT               (KfHWIO_J1939_PGN_64997_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_64997(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 65270 Electrical Power                                              */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65270)                               */
/*  |  |   | | PGN (PF = 254, PS = 247 => PGN = 65271)                 */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1111 1110 1111 0111,xxxx xxxx                           */
/* 0001/1000/1111/1110/1111/0111/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65270_BASE_ID               0x18FEF6D5
#define J1939_PGN_65270_LENGTH                8
#define J1939_PGN_65270_FREQ                  (KfHWIO_J1939_PGN_65270_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65270_TIMEOUT               (KfHWIO_J1939_PGN_65270_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65270(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

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
#define J1939_PGN_65271_FREQ                  (KfHWIO_J1939_PGN_65271_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65271_TIMEOUT               (KfHWIO_J1939_PGN_65271_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65271(J1939_Transmit_Message_Control_T *tx_msg_ctrl_ptr);

/***********************************************************************/
/* 65213 FD                                                          */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65213)                               */
/*  |  |   | | PGN (PF = F0, PS= 03 )                                  */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65213_BASE_ID               0x18FEBDD5
#define J1939_PGN_65213_LENGTH                8
#define J1939_PGN_65213_FREQ                  (KfHWIO_J1939_PGN_65213_FREQ/J1939_BASE_LOOP)
#define J1939_PGN_65213_TIMEOUT               (KfHWIO_J1939_PGN_65213_FREQ*10/J1939_BASE_LOOP)
extern void J1939_Transmit_Initialize_PGN_65213(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 65253 Hours                                                          */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65253)                               */
/*  |  |   | | PGN (PF = F0, PS= 03 )                                  */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65253_BASE_ID               0x18FEE5D5
#define J1939_PGN_65253_LENGTH                8
#define J1939_PGN_65253_FREQ                  (0)
#define J1939_PGN_65253_TIMEOUT               (0)
extern void J1939_Transmit_Initialize_PGN_65253(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 64965 ECUID                                                         */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65253)                               */
/*  |  |   | | PGN (PF = F0, PS= 03 )                                  */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_64965_BASE_ID               0x18FDC500
#define J1939_PGN_64965_LENGTH                8
#define J1939_PGN_64965                       (0x0000FDC5UL)
#define J1939_PGN_64965_FREQ                  (0)
#define J1939_PGN_64965_TIMEOUT               (0)
extern void J1939_TxInit_PGN_64965(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

/***********************************************************************/
/* 65242 SOFT                                                          */
/* Always 0                                                            */
/*  |  Priority = 6                                                    */
/*  |  |   R1 = 0                                                      */
/*  |  |   | Data Page = 0 (PGN = 65242)                               */
/*  |  |   | | PGN (PF = F0, PS= 03 )                                  */
/*  |  |   | | |                   src address (ie 00 master 01 slave) */
/*  |  |   | | |                   |                                   */
/* 000,110,0,0,1110 1000 yyyy yyyy,xxxx xxxx y = DA = 255              */
/* 0001/1000/1110/1000/yyyy/yyyy/xxxx/xxxx                             */
/***********************************************************************/
#define J1939_PGN_65242_BASE_ID               0x18FEDA00
#define J1939_PGN_65242_LENGTH                8
#define J1939_PGN_65242                       (0x0000FEDAUL)
#define J1939_PGN_65242_FREQ                  (0)
#define J1939_PGN_65242_TIMEOUT               (0)
extern void J1939_TxInit_PGN_65242(J1939_Transmit_Message_Control_T * tx_msg_ctrl_ptr);

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
#define J193973_PGN_65226_FREQ                 (KfHWIO_J1939_PGN_65226_FREQ / J1939_BASE_LOOP)
#define J1939_PGN_65226_TIMEOUT                (KfHWIO_J1939_PGN_65226_FREQ * 1.5 / J1939_BASE_LOOP) // Timeout set to 1.5s

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
/* PGN: 65230 DM5                                                             */
/******************************************************************************/
#define J193973_PGN_65230_BASE_ID              (0x18FECE00UL) /*FFCD=65230,Prio=6,src=0*/
#define J193973_PGN_65230_LENGTH               (8)
#define J193973_PGN_65230                      (0x0000FECEUL)
#define J193973_PGN_65230_FREQ                 (0)
#define J1939_PGN_65230_TIMEOUT                (0) 

/******************************************************************************/
/* PGN: dm7                                                               */
/******************************************************************************/
#define J1939_73_dm7_BASE_ID               0x18E30017
#define J1939_73_dm7_LENGTH                8
#define J1939_73_dm7_FREQ                  (0)
#define J1939_73_dm7_TIMEOUT               (0)
extern void J1939_Receive_Initialize_73_dm7(J1939_Receive_Message_Control_T *rx_msg_ctrl_ptr);

extern void J1939_RxInit_73_dm7 (J1939_Receive_Message_Control_T *MsgCtrl);

/******************************************************************************/
/* PGN: 65232 DM8                                                             */
/******************************************************************************/
#define J193973_PGN_65232_BASE_ID              (0x18FED000UL) /*FFCD=65232,Prio=6,src=0*/
#define J193973_PGN_65232_LENGTH               (8)
#define J193973_PGN_65223                      (0x0000FED0UL)
#define J193973_PGN_65232_FREQ                 (0)
#define J1939_PGN_65232_TIMEOUT                (0) 

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
/* PGN: 57088 DM13                                                            */
/******************************************************************************/
#define J193973_PGN_57088_BASE_ID              (0x18DF0000UL) /*DF00=57088,Prio=6,src=0*/
#define J193973_PGN_57088_LENGTH               (8)
#define J193973_PGN_57088                      (0x0000DF00UL)
#define J193973_PGN_57088_FREQ                 (0)
#define J1939_PGN_57088_TIMEOUT                (0) 
extern void J1939_Receive_Initialize_73_dm13(J1939_Receive_Message_Control_T * rx_msg_ctrl_ptr); 
extern const J1939_Message_Table_T   J1939_Message_Table[];
/******************************************************************************/
/* PGN: 65249                                                             */
/******************************************************************************/
#define J193973_PGN_65249_BASE_ID              (0x18FEE100UL) /*FFCA=65249,Prio=6,src=0*/
#define J193973_PGN_65249_LENGTH               (8)
#define J193973_PGN_65249                      (0x0000FEE1UL)
#define J193973_PGN_65249_FREQ                 (KfHWIO_J1939_PGN_65249_FREQ/ J1939_BASE_LOOP)
#define J1939_PGN_65249_TIMEOUT                (KfHWIO_J1939_PGN_65249_FREQ*10/ J1939_BASE_LOOP) 

/******************************************************************************/
/* PGN: 65154                                                             */
/******************************************************************************/
#define J1939_PGN_65154_BASE_ID                (0x1CFE8200UL) /*FFCA=65154,Prio=7,src=0*/
#define J1939_PGN_65154_LENGTH                 (8)
#define J1939_PGN_65154                        (0x0000FE82UL)
#define J1939_PGN_65154_FREQ                   (0)
#define J1939_PGN_65154_TIMEOUT                (0) 

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
/* PGN: 65289                                                                */
/******************************************************************************/
#define J1939_PGN_65289_BASE_ID              (0x18FF0900UL)
#define J1939_PGN_65289_LENGTH               (8)
#define J1939_PGN_65289                      (0x0000FF09UL)
#define J1939_PGN_65289_FREQ                 (0)
#define J1939_PGN_65289_TIMEOUT              (0) 
/******************************************************************************/
/* PGN: 60928 EE00                                                               */
/******************************************************************************/
#define J1939_PGN_60928_BASE_ID               0x18EE0000
#define J1939_PGN_60928_LENGTH                8
#define J1939_PGN_60928                      (0x0000EE00UL)
#define J1939_PGN_60928_FREQ                  (0)
#define J1939_PGN_60928_TIMEOUT               (0)
/******************************************************************************/
/* PGN: 65299 FF13                                                               */
/******************************************************************************/
#define J1939_PGN_65299_BASE_ID               0x18FF1300
#define J1939_PGN_65299_LENGTH                8
#define J1939_PGN_65299                      (0x0000FF13UL)
#define J1939_PGN_65299_FREQ                  (KfHWIO_J1939_PGN_65299_FREQ / J1939_BASE_LOOP)
#define J1939_PGN_65299_TIMEOUT               (KfHWIO_J1939_PGN_65299_FREQ * 10 / J1939_BASE_LOOP)
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
#define J1939_DM4_BUFFER_SIZE  (sizeof(J1939_73_dm4))

/************************************************************************/
/* DEFINE: J1939_DM12_BUFFER_SIZE                                       */
/* Description: Buffer size to store the lamp staus and the             */
/*              emissions-related  active DTCs                          */
/************************************************************************/
#define J1939_DM12_BUFFER_SIZE (14)

#define J1939_PGN_65249_BUFFER_SIZE (19)
//the latest protocol defined this PGN a 40-byte message, according to JD, by hongfei
#define J1939_PGN_65251_BUFFER_SIZE (40) 

#endif
/*-------------------------------------------------------------------*/
/* j1939_pgn_config.h  rev.     - 22 Aug 2014 - Xi Yanpeng           */
/*                                                                   */
/* -Add PGN65251 PGN65259 Configurations                             */
/*-------------------------------------------------------------------*/
