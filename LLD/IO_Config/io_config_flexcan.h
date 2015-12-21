#ifndef IO_CONFIG_FLEXCAN_H
#define IO_CONFIG_FLEXCAN_H


#include "dd_flexcan.h"
#include"io_config_fmpll.h"

//=============================================================================
// FlexCAN Scaling
//=============================================================================
#define FLEXCAN_SYSTEM_FREQUENCY (CRYSTAL_FREQUENCY_HZ)


//============================================================================
//FlexCAN Device Baud Rate definitions
//This one works with a Baker board and CANCase hardware.
//============================================================================
#if 0
#define  FLEXCAN_A_BAUD_RATE    FLEXCAN_BAUD_500KBPS
#define  FLEXCAN_C_BAUD_RATE    FLEXCAN_BAUD_500KBPS
#endif
#define  FLEXCAN_A_BAUD_RATE    FLEXCAN_BAUD_500KBPS
#define  FLEXCAN_C_BAUD_RATE    FLEXCAN_BAUD_500KBPS

#define FlexCAN_A_Time_Quanta    16
#define FlexCAN_C_Time_Quanta    16

#define FlexCAN_A_RJW   3
#define FlexCAN_C_RJW   3

#define FlexCAN_A_Phase_Segment1 3
#define FlexCAN_C_Phase_Segment1 3


#define FlexCAN_A_Phase_Segment2 3
#define FlexCAN_C_Phase_Segment2 3

#define FlexCAN_A_Prop_Segment  6
#define FlexCAN_C_Prop_Segment  6

#define FLEXCAN_MSG_OBJ_Index_CCP_CANID_CRO       FLEXCAN_MSG_OBJ_0
#define FLEXCAN_MSG_OBJ_Index_CCP_CANID_DTO       FLEXCAN_MSG_OBJ_1
#define FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ0     FLEXCAN_MSG_OBJ_2
#define FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ1     FLEXCAN_MSG_OBJ_3
#define FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ2     FLEXCAN_MSG_OBJ_4
#define FLEXCAN_MSG_OBJ_Index_CCP_CANID_DAQ3     FLEXCAN_MSG_OBJ_5
#define FLEXCAN_MSG_OBJ_Index_CCP_INCA_RECEIVE   FLEXCAN_MSG_OBJ_6
#define FLEXCAN_MSG_OBJ_Index_CCP_INCA_TRANSIT   FLEXCAN_MSG_OBJ_7

//====================================================================
// FlexCAN Device Bit Rate Values
// Ensure that: 
//      PROPSEG + PSEG1 + 2 = [4...16]
//      PSEG2 + 1           = [2...8 ]
//      Time Quanta         = [8...25]
//=========================================================================
#if 0
#ifndef FLEXCAN_A_DEVICE_BITRATE_INIT 
#define FLEXCAN_A_DEVICE_BITRATE_INIT\
   (         FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_A    ) |\
              FlexCAN_Set_Baud( 0, FLEXCAN_BAUD_500KBPS) |\
    FlexCAN_Set_Phase_Segment1( 0, 0                   ) |\
    FlexCAN_Set_Phase_Segment2( 0, 0                   ) |\
      FlexCAN_Set_Prop_Segment( 0, 0                   ) |\
               FlexCAN_Set_RJW( 0, 0                   ) |\
       FlexCAN_Set_Time_Quanta( 0, 16                  ) )
#endif

#ifndef FLEXCAN_C_DEVICE_BITRATE_INIT 
#define FLEXCAN_C_DEVICE_BITRATE_INIT\
   (         FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_C    ) |\
              FlexCAN_Set_Baud( 0, FLEXCAN_BAUD_500KBPS) |\
    FlexCAN_Set_Phase_Segment1( 0, 0                   ) |\
    FlexCAN_Set_Phase_Segment2( 0, 0                   ) |\
      FlexCAN_Set_Prop_Segment( 0, 0                   ) |\
               FlexCAN_Set_RJW( 0, 0                   ) |\
       FlexCAN_Set_Time_Quanta( 0, 16                  ) )
#endif
#endif
#ifndef FLEXCAN_A_DEVICE_BITRATE_INIT 
#define FLEXCAN_A_DEVICE_BITRATE_INIT\
   (         FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_A    ) |\
              FlexCAN_Set_Baud( 0, FLEXCAN_BAUD_250KBPS) |\
    FlexCAN_Set_Phase_Segment1( 0, 0                   ) |\
    FlexCAN_Set_Phase_Segment2( 0, 0                   ) |\
      FlexCAN_Set_Prop_Segment( 0, 0                   ) |\
               FlexCAN_Set_RJW( 0, 0                   ) |\
       FlexCAN_Set_Time_Quanta( 0, 16                  ) )
#endif

#ifndef FLEXCAN_C_DEVICE_BITRATE_INIT 
#define FLEXCAN_C_DEVICE_BITRATE_INIT\
   (         FlexCAN_Set_Index( 0, FLEXCAN_DEVICE_C    ) |\
              FlexCAN_Set_Baud( 0, FLEXCAN_BAUD_250KBPS) |\
    FlexCAN_Set_Phase_Segment1( 0, 0                   ) |\
    FlexCAN_Set_Phase_Segment2( 0, 0                   ) |\
      FlexCAN_Set_Prop_Segment( 0, 0                   ) |\
               FlexCAN_Set_RJW( 0, 0                   ) |\
       FlexCAN_Set_Time_Quanta( 0, 16                  ) )
#endif
//=============================================================
//  FlexCAN Prescalar macro
//==============================================================
#define FLEXCAN_A_PRESCALER \
   FLEXCAN_Get_Prescaler(FLEXCAN_SYSTEM_FREQUENCY,\
   (FlexCAN_Get_Baud(FLEXCAN_A_DEVICE_BITRATE_INIT) == FLEXCAN_BAUD_250KBPS ? FLEXCAN_BAUD_RATE_250KBPS :\
    FlexCAN_Get_Baud(FLEXCAN_A_DEVICE_BITRATE_INIT) == FLEXCAN_BAUD_500KBPS ? FLEXCAN_BAUD_RATE_500KBPS :\
    FlexCAN_Get_Baud(FLEXCAN_A_DEVICE_BITRATE_INIT) == FLEXCAN_BAUD_1MBPS ? FLEXCAN_BAUD_RATE_1MBPS :\
    FLEXCAN_BAUD_RATE_500KBPS)\
   ,(FlexCAN_Get_Time_Quanta(FLEXCAN_A_DEVICE_BITRATE_INIT)))


#define FLEXCAN_C_PRESCALER \
   FLEXCAN_Get_Prescaler(FLEXCAN_SYSTEM_FREQUENCY,\
   (FlexCAN_Get_Baud(FLEXCAN_C_DEVICE_BITRATE_INIT) == FLEXCAN_BAUD_250KBPS ? FLEXCAN_BAUD_RATE_250KBPS : \
    FlexCAN_Get_Baud(FLEXCAN_C_DEVICE_BITRATE_INIT) == FLEXCAN_BAUD_500KBPS ? FLEXCAN_BAUD_RATE_500KBPS : \
    FlexCAN_Get_Baud(FLEXCAN_C_DEVICE_BITRATE_INIT) == FLEXCAN_BAUD_1MBPS ? FLEXCAN_BAUD_RATE_1MBPS : \
    FLEXCAN_BAUD_RATE_500KBPS)\
   ,(FlexCAN_Get_Time_Quanta(FLEXCAN_C_DEVICE_BITRATE_INIT)))


//=============================================================================
// MCR - Module Configuration Register
//
//=============================================================================
extern const FLEXCAN_MCR_T  FLEXCAN_A_MCR_INIT; 
//=============================================================================
// MCR - Module Configuration Register
//
//=============================================================================
extern const FLEXCAN_MCR_T  FLEXCAN_C_MCR_INIT;

//=============================================================================
// Initialization Constants for Control Register (CR)
// Field definitions:
//=============================================================================

extern const FLEXCAN_CR_T  FLEXCAN_A_CR_INIT;

extern const FLEXCAN_CR_T  FLEXCAN_C_CR_INIT;

//=============================================================================
// Initialization Constants for Rx Global Mask Register (RXGMASK)
//=============================================================================
extern const FLEXCAN_MSK_T  FLEXCAN_A_RXGMASK_INIT;
extern const FLEXCAN_MSK_T  FLEXCAN_C_RXGMASK_INIT;
//=============================================================================
// Initialization Constants for Rx 14 Mask Register (RX14MASK)
//=============================================================================
extern const FLEXCAN_MSK_T  FLEXCAN_A_RX14MASK_INIT;

extern const FLEXCAN_MSK_T  FLEXCAN_C_RX14MASK_INIT ;
//=============================================================================
// Initialization Constants for Rx 15 Mask Register (RX15MASK)
//=============================================================================
extern const FLEXCAN_MSK_T  FLEXCAN_A_RX15MASK_INIT;

extern const FLEXCAN_MSK_T  FLEXCAN_C_RX15MASK_INIT;
//=============================================================================
// Initialization Constants for Individual Rx Mask Registers (RXIMR0-RXIMR63)
//=============================================================================
extern const FLEXCAN_MSK_T  FLEXCAN_A_RXIMR_INIT [];

extern  const FLEXCAN_MSK_T  FLEXCAN_C_RXIMR_INIT [];
//=============================================================================
// Initialization Constants for Interrupt Mask Register for MB32-MB63 (IMRH)
//=============================================================================
extern const FLEXCAN_IMRH_T  FLEXCAN_A_IMRH_INIT;
extern const FLEXCAN_IMRH_T  FLEXCAN_C_IMRH_INIT ;
//=============================================================================
// Initialization Constants for Interrupt Mask Register for MB0-MB31 (IMRL)
//=============================================================================
extern const FLEXCAN_IMRL_T  FLEXCAN_A_IMRL_INIT;

extern const FLEXCAN_IMRL_T  FLEXCAN_C_IMRL_INIT;
//=============================================================================
// Initialization Constants for Interrupt Clear Register for MB32-MB63 (IFRH)
//=============================================================================
extern const FLEXCAN_IFRH_T  FLEXCAN_A_IFRH_INIT;
extern const FLEXCAN_IFRH_T  FLEXCAN_C_IFRH_INIT ;
//=============================================================================
// Initialization Constants for Interrupt Clear Register for MB0-MB31 (IFRL)
//=============================================================================
extern const FLEXCAN_IFRL_T  FLEXCAN_A_IFRL_INIT;
extern const FLEXCAN_IFRL_T  FLEXCAN_C_IFRL_INIT ;

#ifndef FLEXCAN_TRANSMIT_CALLBACK_INIT_A
#define FLEXCAN_TRANSMIT_CALLBACK_INIT_A (FlexCAN_Transmit_Callback_T)(0)
#endif

#ifndef FLEXCAN_TRANSMIT_CALLBACK_INIT_C
#define FLEXCAN_TRANSMIT_CALLBACK_INIT_C (FlexCAN_Transmit_Callback_T)(0)
#endif

#ifndef FLEXCAN_RECEIVE_CALLBACK_INIT_A
#define FLEXCAN_RECEIVE_CALLBACK_INIT_A (FlexCAN_Receive_Callback_T)(0)
#endif

#ifndef FLEXCAN_RECEIVE_CALLBACK_INIT_C
#define FLEXCAN_RECEIVE_CALLBACK_INIT_C (FlexCAN_Receive_Callback_T)(0)
#endif

#ifndef FLEXCAN_ERROR_CALLBACK_INIT_A
#define FLEXCAN_ERROR_CALLBACK_INIT_A (FlexCAN_Error_Callback_T)(0)
#endif

#ifndef FLEXCAN_ERROR_CALLBACK_INIT_C
#define FLEXCAN_ERROR_CALLBACK_INIT_C (FlexCAN_Error_Callback_T)(0)
#endif

//=============================================================================
// FLEXCAN_TRANSMIT_CALLBACK
//=============================================================================
extern const FlexCAN_Transmit_Callback_T FLEXCAN_TRANSMIT_CALLBACK[ NUMBER_OF_FLEXCAN_DEVICES ];

//=============================================================================
//FLEXCAN_RECEIVE_CALLBACK
//=============================================================================
extern const FlexCAN_Receive_Callback_T FLEXCAN_RECEIVE_CALLBACK[ NUMBER_OF_FLEXCAN_DEVICES ];

//=============================================================================
//FLEXCAN_ERROR_CALLBACK
//=============================================================================
extern const FlexCAN_Error_Callback_T FLEXCAN_ERROR_CALLBACK[ NUMBER_OF_FLEXCAN_DEVICES ];

#endif // IO_CONFIG_FLEXCAN_H

