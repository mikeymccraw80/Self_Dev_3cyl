#ifndef DD_DMA_H
#define DD_DMA_H

//=============================================================================
// Include Files
//=============================================================================
#include "hw_dma.h"


//=============================================================================
// @globalv DMA_T | DMA |
// The Register Memory Overlay of the enhanced Direct Memeory Access 2 engine
// to provide software access and debug information.
//
// @end
//=============================================================================
#define SECTION_DMA_A_REGISTER
#include "section.h"
extern DMA_T DMA_A;
#define SECTION_END
#include "section.h"

typedef enum
{
   DMA_DEVICE_A,
   DMA_DEVICE_MAX

}  DMA_Index_T;

// @enum DMA_Channel_T | Defines the DMA Channel.
typedef enum
{
   DMA_CHANNEL_QADC_FISR0_CFFF_0    =  0, // @emem eQADC Command FIFO 0 Fill Flag
   DMA_CHANNEL_QADC_FISR0_RFDF_0    =  1, // @emem eQADC Receive FIFO 0 Drain Flag
   DMA_CHANNEL_QADC_FISR1_CFFF_1    =  2, // @emem eQADC Command FIFO 1 Fill Flag
   DMA_CHANNEL_QADC_FISR1_RFDF_1    =  3, // @emem eQADC Receive FIFO 1 Drain Flag
   DMA_CHANNEL_QADC_FISR2_CFFF_2    =  4, // @emem eQADC Command FIFO 2 Fill Flag
   DMA_CHANNEL_QADC_FISR2_RFDF_2    =  5, // @emem eQADC Receive FIFO 2 Drain Flag
   DMA_CHANNEL_QADC_FISR3_CFFF_3    =  6, // @emem eQADC Command FIFO 3 Fill Flag
   DMA_CHANNEL_QADC_FISR3_RFDF_3    =  7, // @emem eQADC Receive FIFO 3 Drain Flag
   DMA_CHANNEL_QADC_FISR4_CFFF_4    =  8, // @emem eQADC Command FIFO 4 Fill Flag
   DMA_CHANNEL_QADC_FISR4_RFDF_4    =  9, // @emem eQADC Receive FIFO 4 Drain Flag
   DMA_CHANNEL_QADC_FISR5_CFFF_5    = 10, // @emem eQADC Command FIFO 5 Fill Flag
   DMA_CHANNEL_QADC_FISR5_RFDF_5    = 11, // @emem eQADC Receive FIFO 5 Drain Flag
   DMA_CHANNEL_DSPI_B_SR_TFFF       = 12, // @emem DSPIB Transmit FIFO Fill Flag
   DMA_CHANNEL_DSPI_B_SR_RFDF       = 13, // @emem DSPIB Receive FIFO Drain Flag
   DMA_CHANNEL_DSPI_C_SR_TFFF       = 14, // @emem DSPIC Transmit FIFO Fill Flag
   DMA_CHANNEL_DSPI_C_SR_RFDF       = 15, // @emem DSPIC Receive FIFO Drain Flag
   DMA_CHANNEL_DSPI_D_SR_TFFF       = 16, // @emem DSPID Transmit FIFO Fill Flag
   DMA_CHANNEL_DSPI_D_SR_RFDF       = 17, // @emem DSPID Receive FIFO Drain Flag
   DMA_CHANNEL_SCI_A_SR_TDRE        = 18, // @emem eSCIA combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCI_A_SR_TC          = 18, // @emem eSCIA combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCI_A_SR_TXRDY       = 18, // @emem eSCIA combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCI_A_SR_RDRF        = 19, // @emem eSCIA combined DMA request of the Receive Data Register Full and LIN Receive Data Ready DMA requests
   DMA_CHANNEL_SCI_A_SD_RXRDY       = 19, // @emem eSCIA combined DMA request of the Receive Data Register Full and LIN Receive Data Ready DMA requests
   DMA_CHANNEL_MIOS_EMIOSFLAG_0     = 20, // @emem eMIOS Channel 0 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_1     = 21, // @emem eMIOS Channel 1 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_2     = 22, // @emem eMIOS Channel 2 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_3     = 23, // @emem eMIOS Channel 3 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_4     = 24, // @emem eMIOS Channel 4 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_8     = 25, // @emem eMIOS Channel 8 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_9     = 26, // @emem eMIOS Channel 9 Flag
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_0   = 27, // @emem eTPUA Channel 0 Data Transfer Request Status
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_1   = 28, // @emem eTPUA Channel 1 Data Transfer Request Status
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_2   = 29, // @emem eTPUA Channel 2 Data Transfer Request Status
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_14  = 30, // @emem eTPUA Channel 14 Data Transfer Request Status
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_15  = 31, // @emem eTPUA Channel 15 Data Transfer Request Status
   DMA_CHANNEL_LOWER_MAX            = 32, // @emem DMA maximum lower channels
   DMA_CHANNEL_DSPI_A_TX_FIFO_FILL  = 32, // @emem Reserved channel
   DMA_CHANNEL_DSPI_A_RX_FIFO_DRAIN = 33, // @emem Reserved channel
   DMA_CHANNEL_SCIB_SR_TDRE         = 34, // @emem eSCIB combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCIB_SR_TC           = 34, // @emem eSCIB combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCIB_SR_TXRDY        = 34, // @emem eSCIB combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCIB_SR_RDRF         = 35, // @emem eSCIB combined DMA request of the Receive Data Register Full and LIN Receive Data Ready DMA requests
   DMA_CHANNEL_SCIB_SR_RXRDY        = 35, // @emem eSCIB combined DMA request of the Receive Data Register Full and LIN Receive Data Ready DMA requests
   DMA_CHANNEL_MIOS_EMIOSFLAG_6     = 36, // @emem eMIOS Channel 6 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_7     = 37, // @emem eMIOS Channel 7 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_10    = 38, // @emem eMIOS Channel 10 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_11    = 39, // @emem eMIOS Channel 11 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_16    = 40, // @emem eMIOS Channel 16 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_17    = 41, // @emem eMIOS Channel 17 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_18    = 42, // @emem eMIOS Channel 18 Flag
   DMA_CHANNEL_MIOS_EMIOSFLAG_19    = 43, // @emem eMIOS Channel 19 Flag
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_12  = 44, // @emem eTPUA Channel 12 Data Transfer Request Status
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_13  = 45, // @emem eTPUA Channel 13 Data Transfer Request Status
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_28  = 46, // @emem eTPUA Channel 28 Data Transfer Request Status
   DMA_CHANNEL_TPU_DTRSR_A_DTRS_29  = 47, // @emem eTPUA Channel 29 Data Transfer Request Status
   DMA_CHANNEL_SIU_EISR_EIF_0       = 48, // @emem eSIU  External Interrupt Flag 0
   DMA_CHANNEL_SIU_EISR_EIF_1       = 49, // @emem eSIU  External Interrupt Flag 1
   DMA_CHANNEL_SIU_EISR_EIF_2       = 50, // @emem eSIU  External Interrupt Flag 2
   DMA_CHANNEL_SIU_EISR_EIF_3       = 51, // @emem eSIU  External Interrupt Flag 3
   DMA_CHANNEL_DECFIL_FILL_BUF_A    = 52, // @emem Decimation Filter AFill Buffer
   DMA_CHANNEL_DECFIL_DRAIN_BUF_A   = 53, // @emem Decimation Filter A Drain Buffer
   DMA_CHANNEL_DECFIL_FILL_BUF_B    = 54, // @emem Decimation Filter B Fill Buffer
   DMA_CHANNEL_DECFIL_DRAIN_BUF_B   = 55, // @emem Decimation Filter B Drain Buffer
   DMA_CHANNEL_SCIC_SR_TDRE         = 56, // @emem eSCIC combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCIC_SR_TC           = 56, // @emem eSCIC combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCIC_SR_TXRDY        = 56, // @emem eSCIC combined DMA request of the Transmit Data Register Empty, Transmit Complete, and LIN Transmit Data Ready DMA requests
   DMA_CHANNEL_SCIC_SR_RDRF         = 57, // @emem eSCIC combined DMA request of the Receive Data Register Full and LIN Receive Data Ready DMA requests
   DMA_CHANNEL_SCIC_SR_RXRDY        = 57, // @emem eSCIC combined DMA request of the Receive Data Register Full and LIN Receive Data Ready DMA requests
   DMA_CHANNEL_RESERVED_2           = 58, // @emem Reserved channel
   DMA_CHANNEL_RESERVED_3           = 59, // @emem Reserved channel
   DMA_CHANNEL_RESERVED_4           = 60, // @emem Reserved channel
   DMA_CHANNEL_RESERVED_5           = 61, // @emem Reserved channel
   DMA_CHANNEL_RESERVED_6           = 62, // @emem Reserved channel
   DMA_CHANNEL_RESERVED_7           = 63, // @emem Reserved channel
   DMA_CHANNEL_MAX                  = 64  // @emem Reserved channel

}  DMA_Channel_T;




// @enum DMA_Circular_Buffer_Length_T | Defines which address bits can be changed by the DMA module.
//
// applies to registers SMOD/DMOD
// note: all DMA hw address increments are affected by this wrap characteristic.
// This type defines which bits are allowed to be modified by the hardware so special consideration
// must be taken for placement of the source and destination addresses to avoid hitting wrap/alignment
// boundaries.
typedef enum DMA_Circular_Buffer_Length_Tag
{
   DMA_CIRCULAR_BUFFER_LENGTH_0,          // @emem The address bits S/DADR[31: 0] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_2,          // @emem The address bits S/DADR[31: 1] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_4,          // @emem The address bits S/DADR[31: 2] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_8,          // @emem The address bits S/DADR[31: 3] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_16,         // @emem The address bits S/DADR[31: 4] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_32,         // @emem The address bits S/DADR[31: 5] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_64,         // @emem The address bits S/DADR[31: 6] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_128,        // @emem The address bits S/DADR[31: 7] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_256,        // @emem The address bits S/DADR[31: 8] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_512,        // @emem The address bits S/DADR[31: 9] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_1024,       // @emem The address bits S/DADR[31:10] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_2048,       // @emem The address bits S/DADR[31:11] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_4096,       // @emem The address bits S/DADR[31:12] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_8192,       // @emem The address bits S/DADR[31:13] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_16384,      // @emem The address bits S/DADR[31:14] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_32768,      // @emem The address bits S/DADR[31:15] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_65536,      // @emem The address bits S/DADR[31:16] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_131072,     // @emem The address bits S/DADR[31:17] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_262144,     // @emem The address bits S/DADR[31:18] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_524288,     // @emem The address bits S/DADR[31:19] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_1048576,    // @emem The address bits S/DADR[31:20] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_2097152,    // @emem The address bits S/DADR[31:21] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_4194304,    // @emem The address bits S/DADR[31:22] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_8388608,    // @emem The address bits S/DADR[31:23] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_16777216,   // @emem The address bits S/DADR[31:24] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_33554432,   // @emem The address bits S/DADR[31:25] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_67108864,   // @emem The address bits S/DADR[31:26] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_134217728,  // @emem The address bits S/DADR[31:27] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_268435456,  // @emem The address bits S/DADR[31:28] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_536870912,  // @emem The address bits S/DADR[31:29] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_1073741824, // @emem The address bits S/DADR[31:30] are left unchanged after a move operation
   DMA_CIRCULAR_BUFFER_LENGTH_2147483648  // @emem The address bits S/DADR[31:31] are left unchanged after a move operation

}  DMA_Circular_Buffer_Length_T;

// @enum DMA_Channel_Data_Size_T | Defines the data width for source and destination transactions of DMA channel.
typedef enum
{
   DMA_SIZE_8_BIT,         // @emem 8-bit (byte) transaction selected
   DMA_SIZE_16_BIT,        // @emem 16-bit (half-word) transaction selected
   DMA_SIZE_32_BIT,        // @emem 32-Bit (word) transaction selected
   DMA_SIZE_64_BIT,        // @emem 64 bits (double-word) transaction selected
   DMA_SIZE_RESERVED,      // @emem reserved selection. do not use
   DMA_SIZE_32BYTE_BURST   // @emem 32 byte burst transaction selected

}  DMA_Channel_Data_Size_T;

// @enum DMA_Bandwidth_Control_T | Bandwidth control (BWC)
typedef enum DMA_Bandwidth_Control_Tag
{
   DMA_BANDWIDTH_CONTROL_NO_ENGINE_STALL,       // @emem No eDMA engine stalls
   DMA_BANDWIDTH_CONTROL_RESERVED,              // @emem Reserved
   DMA_BANDWIDTH_CONTROL_ENGINE_STALL_4_CYCLES, // @emem eDMA engine stalls for 4 cycles after each r/w
   DMA_BANDWIDTH_CONTROL_ENGINE_STALL_8_CYCLES  // @emem eDMA engine stalls for 8 cycles after each r/w

}  DMA_Bandwidth_Control_T;

// @enum DMA_Channel_Priority_T | Defines the priority of the channels....
typedef enum
{
   DMA_CHANNEL_PRIORITY_0,     // @emem priority  0
   DMA_CHANNEL_PRIORITY_1,     // @emem priority  1
   DMA_CHANNEL_PRIORITY_2,     // @emem priority  2
   DMA_CHANNEL_PRIORITY_3,     // @emem priority  3
   DMA_CHANNEL_PRIORITY_4,     // @emem priority  4
   DMA_CHANNEL_PRIORITY_5,     // @emem priority  5
   DMA_CHANNEL_PRIORITY_6,     // @emem priority  6
   DMA_CHANNEL_PRIORITY_7,     // @emem priority  7
   DMA_CHANNEL_PRIORITY_8,     // @emem priority  8
   DMA_CHANNEL_PRIORITY_9,     // @emem priority  9
   DMA_CHANNEL_PRIORITY_10,    // @emem priority 10
   DMA_CHANNEL_PRIORITY_11,    // @emem priority 11
   DMA_CHANNEL_PRIORITY_12,    // @emem priority 12
   DMA_CHANNEL_PRIORITY_13,    // @emem priority 13
   DMA_CHANNEL_PRIORITY_14,    // @emem priority 14
   DMA_CHANNEL_PRIORITY_15     // @emem priority 15

}  DMA_Channel_Priority_T;

// @enum DMA_Priority_T | Defines the priority that is used when...
typedef enum
{
   DMA_GROUP_PRIORITY_0,  // @emem priority 0
   DMA_GROUP_PRIORITY_1,  // @emem priority 1
   DMA_GROUP_PRIORITY_2,  // @emem priority 2
   DMA_GROUP_PRIORITY_3   // @emem priority 3

}  DMA_Group_Priority_T;

// @enum DMA_Priority_T | Defines the priority that is used when...
typedef enum DMA_Mode_Tag
{
   DMA_MODE_SOFTWARE,  // @emem Software Requests to activate DMA Channel
   DMA_MODE_HARDWARE   // @emem Hardware Requests to activate DMA Channel

}  DMA_Mode_T;

// @enum DMA_Address_T | Defines the address type...
typedef enum DMA_Address_Tag
{
   DMA_SOURCE_ADDRESS               = 0,
   DMA_SOURCE_ADDRESS_LAST          = 3,
   DMA_DESTINATION_ADDRESS          = 4,
   DMA_DESTINATION_ADDRESS_LAST_SGA = 6,
   DMA_ADDRESS_MAX                  = 7

}  DMA_Address_T;
   
// @struct MPC55xx_DMA_Initialization_Parameters_Tag | Structure containing the initialization parameters for a dma channel.
typedef struct MPC55xx_DMA_Initialization_Parameters_Tag
{
   uint32_t             source_address;                              // @field address of the source (read)
   uint32_t             destination_address;                         // @field address of the destination (write)
   bitfield16_t         source_circular_buffer_length      :  BIT_5; // @field
   bitfield16_t         source_size                        :  BIT_3; // @field
   bitfield16_t         destination_circular_buffer_length :  BIT_5; // @field
   bitfield16_t         destination_size                   :  BIT_3; // @field
   uint16_t             source_offset;                               // @field
   uint16_t             destination_offset;                          // @field
   uint16_t             inner_transfer_loop_size;                    // @field This can be 0. Default values based on Source size and destination size shall be used.

} MPC55xx_DMA_Initialization_Parameters_T;


//=============================================================================
// DMA_Get_Channel
//
// @func Get the Channel from the DMA configuration.
//
// @parm IO_Configuration_T | x | An <t IO_Configuration_T> type
//
// @rdesc <t DMA_Channel_T> element decoded from the <t IO_Configuration_T>
//
// @end
//=============================================================================

typedef enum
{
   DMA_INTERRUPT_DISABLED,   //  @emem interrupt disabled
   DMA_INTERRUPT_ENABLED     //  @emem interrupt enabled

}DMA_Interrupt_Enabled_T;

//=============================================================================
// DMA_Set_Interrupt_Initialization_Enabled
//
// @func Set the Interrupt Enabled for the DMA configuration.
//
// @parm DMA_Interrupt_Enabled_T | x | A <t DMA_Interrupt_Enabled_T> element
//
// @rdesc <t IO_Configuration_T> containing the element <t DMA_Interrupt_Enabled_T>
//
// @end
//=============================================================================

   typedef enum
{
   DMA_ERROR_INTERRUPT,                         //  @emem Error interrupt type  
   DMA_MAJOR_COUNT_HALF_COMPLETE_INTERRUPT,     //  @emem Major count half complete interrupt type
   DMA_MAJOR_COUNT_COMPLETE_INTERRUPT,          //  @emem Major count  complete interrupt type 
   DMA_BOTH_MAJOR_COUNT_COMPLETE_HALF_COMPLETE  //  @emem Major count  complete interrupt type  and Major count half complete interrupt type

}DMA_Interrupt_Type_T;



//=============================================================================
// /------------------------------------------------------------------------
// | DMA External Objects
// \------------------------------------------------------------------------
//=============================================================================

#define   DMA_ERROR_QUEUE_DEPTH (8)
   
extern uint32_t    DMA_Error_Queue[ DMA_ERROR_QUEUE_DEPTH ];
extern uint8_t     DMA_Error_Queue_Index;

//=============================================================================
// Extern declarations
//=============================================================================

extern const DMA_CR_T  DMA_INIT_GROUP_PRIORITY;
extern const DMA_CPR_T DMA_INIT_CHANNEL_PRIORITY[DMA_CHANNEL_MAX];

#endif // DD_DMA_H

