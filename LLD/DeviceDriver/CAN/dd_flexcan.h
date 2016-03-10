#ifndef DD_FLEXCAN_H
#define DD_FLEXCAN_H
//=============================================================================
//
//       COPYRIGHT, 2005, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_flexcan.h~kok_pt2#7:incl:tci_pt2#6 %
//
// created_by:       gzdmlz
//
// date_created:     Fri Jan 13 22:58:37 2006
//
// %derived_by:      hz1swt %
//
// %date_modified:   Mon Apr 16 09:41:34 2012 %
//
// %version:         kok_pt2#7 %
//
// ============================================================================
// ============================================================================
// Configurable Development Software Module:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================
#include "dd_flexcan_common.h"

#define SECTION_FLEXCAN_A_REGISTER
#include "section.h"
extern FLEXCAN_T FlexCAN_A;
#define SECTION_END
#include "section.h"

#define SECTION_FLEXCAN_C_REGISTER
#include "section.h"
extern FLEXCAN_T FlexCAN_C;
#define SECTION_END
#include "section.h"

#define CAN_A     (*( struct FLEXCAN2_tag *)  0xFFFC0000)
#define CAN_C     (*( struct FLEXCAN2_tag *)  0xFFFC8000)

// Though Monaco contains only FlexCaN A and C, to use the array indexing feature, 
// No of Flexcan devices is kept at 3.
#define NUMBER_OF_FLEXCAN_DEVICES  ( 3)

// Constants
#define THIRTYONE (31)
#define THIRTYTWO (32)

typedef enum FlexCAN_ID_Acc_Mask_Tag
{
   FLEXCAN_ONE_FULL_ID,
   FLEXCAN_2FULL_STDID_OR_2PART_EXT_ID,
   FLEXCAN_4PART_STD_OR_EXT_ID,
   FLEXCAN_ALL_ID_REJECT

} FlexCAN_ID_Acc_Mask_T;

// FlexCAN Bit Rate Values
#define FLEXCAN_BAUD_RATE_100KBPS   (100000)
#define FLEXCAN_BAUD_RATE_250KBPS   (250000)
#define FLEXCAN_BAUD_RATE_500KBPS   (500000)
#define FLEXCAN_BAUD_RATE_1MBPS     (1000000)
//=============================================================================
// @enum FlexCAN Device Additional Configuration Position
//=============================================================================
typedef enum FlexCAN_Additional_Config_Position_Tag
{
   FLEXCAN_CONFIGURATION_POSITION_WRNEN        = 20, //@emem    20   FlexCAN Warning Interrupt Enable
   FLEXCAN_CONFIGURATION_POSITION_SRXDIS       = 21, //@emem    21   FlexCAN Self Reception Disable
   FLEXCAN_CONFIGURATION_POSITION_MBFEN        = 22, //@emem    22   FlexCAN Msg Buff Indv Mask Enable
   FLEXCAN_CONFIGURATION_POSITION_TWRNMSK      = 23, //@emem    23   FlexCAN TxWarn Intr Enabled Mask
   FLEXCAN_CONFIGURATION_POSITION_RWRNMSK      = 24, //@emem    24   FlexCAN RxWarn Intr Enabled Mask
   FLEXCAN_CONFIGURATION_POSITION_MCR_FEN      = 25, //@emem    25   FlexCAN FIFO Enable
   FLEXCAN_CONFIGURATION_POSITION_MCR_WAKMSK   = 26, //@emem    26   FlexCAN Wakeup Mask
   FLEXCAN_CONFIGURATION_POSITION_MCR_SLFWAK   = 27, //@emem    27   FlexCAN Self Wakeup
   FLEXCAN_CONFIGURATION_POSITION_MCR_DOZE     = 28, //@emem    28   FlexCAN Doze Mode Enable
   FLEXCAN_CONFIGURATION_POSITION_MCR_AEN      = 29, //@emem    29   FlexCAN Abort Enable
   FLEXCAN_CONFIGURATION_POSITION_MCR_IDAM     = 30  //@emem    30:31   FlexCAN ID Acceptance Mask

}FlexCAN_Additional_Config_Position_T;
//=============================================================================
// @enum FlexCAN Device Additional Configuration Width
//=============================================================================
typedef enum FlexCAN_Additional_Config_Width_Tag
{
   FLEXCAN_CONFIGURATION_WIDTH_WRNEN        = 1, //@emem    20   FlexCAN Warning Interrupt Enable
   FLEXCAN_CONFIGURATION_WIDTH_SRXDIS       = 1, //@emem    21   FlexCAN Self Reception Disable
   FLEXCAN_CONFIGURATION_WIDTH_MBFEN        = 1, //@emem    22   FlexCAN Msg Buff Indv Mask Enable
   FLEXCAN_CONFIGURATION_WIDTH_TWRNMSK      = 1, //@emem    23   FlexCAN TxWarn Intr Enabled Mask
   FLEXCAN_CONFIGURATION_WIDTH_RWRNMSK      = 1, //@emem    24   FlexCAN RxWarn Intr Enabled Mask
   FLEXCAN_CONFIGURATION_WIDTH_MCR_FEN      = 1, //@emem    25   FlexCAN FIFO Enable
   FLEXCAN_CONFIGURATION_WIDTH_MCR_WAKMSK   = 1, //@emem    26   FlexCAN Wakeup Mask
   FLEXCAN_CONFIGURATION_WIDTH_MCR_SLFWAK   = 1, //@emem    27   FlexCAN Self Wakeup
   FLEXCAN_CONFIGURATION_WIDTH_MCR_DOZE     = 1, //@emem    28   FlexCAN Doze Mode Enable
   FLEXCAN_CONFIGURATION_WIDTH_MCR_AEN      = 1, //@emem    29   FlexCAN Abort Enable
   FLEXCAN_CONFIGURATION_WIDTH_MCR_IDAM     = 2  //@emem    30:31   FlexCAN ID Acceptance Mask

}FlexCAN_Additional_Config_Width_T;
//=============================================================================
// FlexCAN_Set_Warning_Int_Enable
//
// @func Set FlexCAN Device Warning_Interrupt configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_Warning_Int_Enable(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_WRNEN, FLEXCAN_CONFIGURATION_WIDTH_WRNEN ) )
//=============================================================================
// FlexCAN_Get_Warning_Int_Enable
//
// @func Get FlexCAN Device Warning_Interrupt configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Warning_Int_Enable(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_WRNEN, FLEXCAN_CONFIGURATION_WIDTH_WRNEN ) )
//=============================================================================
// FlexCAN_Set_Self_Reception
//
// @func Set FlexCAN Device Self_Reception configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_Self_Reception(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_SRXDIS, FLEXCAN_CONFIGURATION_WIDTH_SRXDIS ) )
//=============================================================================
// FlexCAN_Get_Warning_Interrupt
//
// @func Get FlexCAN Device Self_Reception configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Self_Reception(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_SRXDIS, FLEXCAN_CONFIGURATION_WIDTH_SRXDIS ) )
//=============================================================================
// FlexCAN_Set_MsgBuf_Individual_Mask
//
// @func Set FlexCAN Device MsgBuf_Individual_Mask configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_MsgBuf_Individual_Mask(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MBFEN, FLEXCAN_CONFIGURATION_WIDTH_MBFEN ) )
//=============================================================================
// FlexCAN_Get_MsgBuf_Individual_Mask
//
// @func Get FlexCAN Device MsgBuf_Individual_Mask configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_MsgBuf_Individual_Mask(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MBFEN, FLEXCAN_CONFIGURATION_WIDTH_MBFEN ) )
//=============================================================================
// FlexCAN_Set_TxWarn_Interrupt_Mask
//
// @func Set FlexCAN Device TxWarn_Interrupt_Mask configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_TxWarn_Interrupt_Mask(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_TWRNMSK, FLEXCAN_CONFIGURATION_WIDTH_TWRNMSK ) )
//=============================================================================
// FlexCAN_Get_TxWarn_Interrupt_Mask
//
// @func Get FlexCAN Device TxWarn_Interrupt_Mask configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_TxWarn_Interrupt_Mask(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_TWRNMSK, FLEXCAN_CONFIGURATION_WIDTH_TWRNMSK ) )
//=============================================================================
// FlexCAN_Set_RxWarn_Interrupt_Mask
//
// @func Set FlexCAN Device RxWarn_Interrupt_Mask configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t uint8_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_RxWarn_Interrupt_Mask(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_RWRNMSK, FLEXCAN_CONFIGURATION_WIDTH_RWRNMSK ) )
//=============================================================================
// FlexCAN_Get_RxWarn_Interrupt_Mask
//
// @func Get FlexCAN Device TxWarn_Interrupt_Mask configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t uint8_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_RxWarn_Interrupt_Mask(config) \
   (uint8_t)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_RWRNMSK, FLEXCAN_CONFIGURATION_WIDTH_RWRNMSK ) )

//=============================================================================
// FlexCAN_Set_FIFO_Enable
//
// @func Set FlexCAN Device FIFO Enable configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t uint8_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_FIFO_Enable(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MCR_FEN, FLEXCAN_CONFIGURATION_WIDTH_MCR_FEN ) )
//=============================================================================
// FlexCAN_Get_FIFO_Enable
//
// @func Get FlexCAN Device FIFO_Enable configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_FIFO_Enable(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MCR_FEN, FLEXCAN_CONFIGURATION_WIDTH_MCR_FEN ) )

//=============================================================================
// FlexCAN_Set_Wakeup_Mask
//
// @func Set FlexCAN Device Wakeup Mask configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Wakeup_Mask(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MCR_WAKMSK, FLEXCAN_CONFIGURATION_WIDTH_MCR_WAKMSK) )
//=============================================================================
// FlexCAN_Get_Wakeup_Mask
//
// @func Get FlexCAN Device FIFO_Enable configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Wakeup_Mask(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MCR_WAKMSK, FLEXCAN_CONFIGURATION_WIDTH_MCR_WAKMSK ) )

//=============================================================================
// FlexCAN_Set_Self_Wakeup
//
// @func Set FlexCAN Device Self Wakeup configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Self_Wakeup(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MCR_SLFWAK, FLEXCAN_CONFIGURATION_POSITION_MCR_SLFWAK) )
//=============================================================================
// FlexCAN_Get_Self_Wakeup
//
// @func Get FlexCAN Device Self Wakeup configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Self_Wakeup(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MCR_SLFWAK, FLEXCAN_CONFIGURATION_POSITION_MCR_SLFWAK ) )

//=============================================================================
// FlexCAN_Set_Doze_Mode
//
// @func Set FlexCAN Device Doze Mode configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Doze_Mode(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MCR_DOZE, FLEXCAN_CONFIGURATION_WIDTH_MCR_DOZE) )
//=============================================================================
// FlexCAN_Get_Doze_Mode
//
// @func Get FlexCAN Device Doze Mode configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Doze_Mode(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MCR_DOZE, FLEXCAN_CONFIGURATION_WIDTH_MCR_DOZE ) )

//=============================================================================
// FlexCAN_Set_Abort_Enable
//
// @func Set FlexCAN Device Abort Enable configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | status | A <t bool> element
//
// @rdesc <t IO_Configuration_T> containing the element <t bool>
//
// @end
//=============================================================================
#define FlexCAN_Set_Abort_Enable(config,status) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MCR_AEN, FLEXCAN_CONFIGURATION_WIDTH_MCR_AEN ) )
//=============================================================================
// FlexCAN_Get_Abort_Enable
//
// @func Get FlexCAN Device Abort Ebable configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t bool> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_Abort_Enable(config) \
   (bool)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MCR_AEN, FLEXCAN_CONFIGURATION_WIDTH_MCR_AEN ) )

//=============================================================================
// FlexCAN_Set_ID_Acceptance_Mask
//
// @func Set FlexCAN Device ID Acceptance Mask configuration
//
// @parm IO_Configuration_T | config | The value of the configuration prior to modification
//
// @parm uint8_t | id_acc_type | A <t FlexCAN_ID_Acc_Mask_t> element
//
// @rdesc <t IO_Configuration_T> containing the element <t FlexCAN_ID_Acc_Mask_t>
//
// @end
//=============================================================================
#define FlexCAN_Set_ID_Accept_Mask(config,id_acc_type) \
   (IO_Configuration_T)( Insert_Bits( config, status, FLEXCAN_CONFIGURATION_POSITION_MCR_IDAM, FLEXCAN_CONFIGURATION_WIDTH_MCR_IDAM ) )
//=============================================================================
// FlexCAN_Get_ID_Acceptance_Mask
//
// @func Get FlexCAN Device ID Acceptance Mask configuration
//
// @parm IO_Configuration_T | config | A <t IO_Configuration_T> type
//
// @rdesc <t FlexCAN_ID_Acc_Mask_t> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================
#define FlexCAN_Get_ID_Accept_Mask(config) \
   (FlexCAN_ID_Acc_Mask_T)( Extract_Bits( config, FLEXCAN_CONFIGURATION_POSITION_MCR_IDAM, FLEXCAN_CONFIGURATION_WIDTH_MCR_IDAM ) )

//=============================================================================
// FlexCAN_Get_Device
//
// @func This function returns the base register address of FlexCAN device
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//
// @rdesc FLEXCAN_T* FlexCAN register address
//
// @end
//=============================================================================
FLEXCAN_T* FlexCAN_Get_Device(
   IO_Configuration_T in_configuration );
//=============================================================================
// FlexCAN_Initialize_Device
//
// @func This function initializes FlexCAN registers
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//       FlexCAN_Init_Table_T * init_table - The address of table for dynamic
//          initialization of mask, Bit Timing parameters etc.  
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Initialize_Device(
   IO_Configuration_T in_configuration,
   FlexCAN_Init_Table_T * init_table);
//=============================================================================
// FlexCAN_Set_MsgBuf_Filter_Enable
//
// @func This function will Enable/Disable MBFEN bit in MCR Register
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//       bool state - true will set MBFEN Bit and false will Reset MBFEN bit
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Set_MsgBuf_Filter_Enable(
   IO_Configuration_T in_configuration,
   bool state);
//=============================================================================
// FlexCAN_Set_MsgObj_Indiv_Mask
//
// @func This function will Set the individual Mask for Msg Buffer 
//
// @parm IO_Configuration_T | in_config   |A configurable value set in
//          io_config.h that specifies the FlexCAN device, Message Buffer no etc
//       FLEXCAN_MSK_T  in_mask - The individual Mask value to be set 
//
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Set_MsgObj_Indiv_Mask(
   IO_Configuration_T in_configuration,
   uint32_t in_mask );

//=============================================================================
// FlexCAN_Clear_Message_Buffers
//
// @func This function initializes FlexCAN Message buffers
//
// @parm FLEXCAN_T* | pFlexCAN |pointer to FlexCAN register address  
//
// @parm FlexCAN_Index_T | Flexcan device Index
// @rdesc None
//
// @end
//=============================================================================
void FlexCAN_Clear_Message_Buffers(
   FLEXCAN_T*          in_pFlexCAN,
   FlexCAN_Index_T     in_index   );

//==========================================================================
// Extern declarations 
//==========================================================================
//=============================================================================
// @const FlexCAN_Transmit_Callback_T | FLEXCAN_TRANSMIT_CALLBACK |
//=============================================================================
extern const FlexCAN_Transmit_Callback_T FLEXCAN_TRANSMIT_CALLBACK[ NUMBER_OF_FLEXCAN_DEVICES ];
//=============================================================================
// @const FlexCAN_Receive_Callback_T | FLEXCAN_RECEIVE_CALLBACK |
//=============================================================================
extern const FlexCAN_Receive_Callback_T FLEXCAN_RECEIVE_CALLBACK[ NUMBER_OF_FLEXCAN_DEVICES ];
//=============================================================================
// @const FlexCAN_Error_Callback_T | FLEXCAN_ERROR_CALLBACK |
//=============================================================================
extern const FlexCAN_Error_Callback_T FLEXCAN_ERROR_CALLBACK[ NUMBER_OF_FLEXCAN_DEVICES ];
//=============================================================================
extern const uint32_t        FLEXCAN_FREQUENCY_HZ;
extern const FLEXCAN_MCR_T   FLEXCAN_MCR_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_CR_T    FLEXCAN_CR_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_MSK_T   FLEXCAN_RXGMASK_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_MSK_T   FLEXCAN_RX14MASK_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_MSK_T   FLEXCAN_RX15MASK_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_MSK_T   FLEXCAN_RXIMR_INIT[NUMBER_OF_FLEXCAN_DEVICES] [FLEXCAN_MSG_OBJ_MAX];
extern const FLEXCAN_IMRH_T  FLEXCAN_IMRH_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_IMRL_T  FLEXCAN_IMRL_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_IFRH_T  FLEXCAN_IFRH_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern const FLEXCAN_IFRL_T  FLEXCAN_IFRL_INIT[NUMBER_OF_FLEXCAN_DEVICES];
extern uint32_t Rx_PGN_55808_ID;
extern uint32_t Tx_PGN_55808_ID;

#endif // DD_FLEXCAN_H
