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

#endif // IO_CONFIG_FLEXCAN_H

