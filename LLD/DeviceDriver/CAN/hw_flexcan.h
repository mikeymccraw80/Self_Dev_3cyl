#ifndef HW_FLEXCAN_H
#define HW_FLEXCAN_H

//=============================================================================
//
//                        FlexCAN Module
//
// The FlexCAN module is a communication controller that implements
// the controller area network (CAN) protocol, an asynchronous
// communications protocol used in automotive and industrial control
// systems. It is a high speed (1 Mbit/sec), short distance, priority
// based protocol which can communicate using a variety of mediums.
// The FlexCAN supports both the standard and extended identifier (ID)
// message formats specified in the CAN protocol specification,
// revision 2.0, part U8.
//
// The FlexCAN module contains 16 message buffers, which are used for
// transmit and receive functions. It also contains message filters,
// which are used to qualify the received message IDs when comparing
// them to the receive buffer identifiers.
//
//=============================================================================
#include "reuse.h"

#define   CAN_NO_OF_MSG_BUF      (64)

//wic Bit Masks
#define CAN_ESR_BOFF_CLEAR_MASK   (0xFFFCFFFC)
#define CAN_ESR_ERR_CLEAR_MASK    (0xFFFCFFFA)
#define CAN_MCR_MDIS_MASK         (0x80000000)
//=============================================================================
// MCR - Module Configuration Register
//
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t   MDIS     : 1;   // Module enable, 0=enable
      bitfield32_t   FRZ      : 1;   // Freeze enable, 0=ignore, 1=freeze
      bitfield32_t   FEN      : 1;   // FIFO Enable, 0= Not Enabled, 1= Enabled
      bitfield32_t   HALT     : 1;   // Halt S-Clock, 0=normal, 1=debug
      bitfield32_t   NOTRDY   : 1;   // Not Ready (read-only)
      bitfield32_t   WAK_MSK  : 1;   // Wake Up Interrupt Mask, 0=disabled, 1=enabled
      bitfield32_t   SOFTRST  : 1;   // Soft Reset, 0=complete,1=initiate
      bitfield32_t   FRZACK   : 1;   // FRZ mode ack. 1 = FRZ mode
      bitfield32_t   SUPV     : 1;   // Supervisor mode, 1=In supervisor mode, 0=In unrestricted mode
      bitfield32_t   SLF_WAK  : 1;   // Self Wake Up, 0=disabled, 1=enabled
      bitfield32_t   WRNEN    : 1;   // Warning Interrupt Enable,1 = TWRNINT and RWRNINT bits are set, 
                                     //                          0 == TWRNINT and RWRNINT bits not set
      bitfield32_t   MDISACK  : 1;   // Low Power Mode acknowledgement 1=FlexCAN2 disabled
      bitfield32_t   WAK_SRC  : 1;   // Wakeup Source, 1=Filtered input, 0=Nonfiltered input source
      bitfield32_t   DOZE     : 1;   // Doze Mode, 0=Not Enabled, 1=Enabled
      bitfield32_t   SRXDIS   : 1;   // Self Reception Disable, 1=Self Rx disabled, 0=Self Rx Enabled
      bitfield32_t   MBFEN    : 1;   // Message buffer filter enable, 1=Individual Rx Mask & queue enabled, 0=Disabled
      bitfield32_t            : 2;   // Reserved
      bitfield32_t   LPRIO_EN : 1;   // Local Priority Enable, 1= Enabled, 0=Disabled
      bitfield32_t   AEN      : 1;   // Abort Enable, 0=Abort Disabled,1=Abort Enabled
      bitfield32_t            : 2;   // Reserved
      bitfield32_t   IDAM     : 2;   // ID Acceptance Mode, 00=format-A, 01=format-B,10=format-C,11=format-D
      bitfield32_t            : 2;  // Not Used
      bitfield32_t   MAXMB    : 6;   // Maximum Number of message buffers

   }      F;

   uint32_t U32;

}  FLEXCAN_MCR_T;
//=============================================================================
// CTRL - Control Register
//
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t   PRESDIV  : 8;  // Prescaler Division Factor
      bitfield32_t   RJW      : 2;  // Resynchronization jump width
      bitfield32_t   PSEG1    : 3;  // Phase Buffer Segment 1
      bitfield32_t   PSEG2    : 3;  // Phase Buffer Segment 2
      bitfield32_t   BOFFMSK  : 1;  // Bus Off interrupt mask, 0=dis, 1=en
      bitfield32_t   ERRMSK   : 1;  // Error interrupt mask, 0=dis, 1=en
      bitfield32_t   CLKSRC   : 1;  // Engine clock source
      bitfield32_t   LPB      : 1;  // Loop Back, 0=disable, 1=enable
      bitfield32_t   TWRNMSK  : 1;  // Tx Warning Int Mask, 0=Disable,1=En
      bitfield32_t   RWRNMSK  : 1;  // Rx Warning Int Mask, 0=Disable,1=En
      bitfield32_t            : 2;  // Reserved
      bitfield32_t   SMP      : 1;  // Sampling Mode, 0=1, 1=3 samples
      bitfield32_t   BOFFREC  : 1;  // Bus off recovery mode
      bitfield32_t   TSYN     : 1;  // Timer Synchronize mode, 0=dis, 1=en
      bitfield32_t   LBUF     : 1;  // Lowest Buffer Transmitted first
      bitfield32_t   LOM      : 1;  // Listen only mode
      bitfield32_t   PROPSEG  : 3;  // Propagation Segment Time

   }     F;

   uint32_t U32;

}  FLEXCAN_CR_T;
//=============================================================================
// Timer - Free Running Timer Register
//
// The TIMER is clocked by the FlexCAN bit-clock. During a message, it
// increments by one for each bit that is received or transmitted.
// When there is no message on the bus, it increments at the nominal
// bit rate.
//=============================================================================
typedef uint32_t FLEXCAN_TIMER_T;
//=============================================================================
// RXGMSK - Receive Global Mask Register
//
// The receive global mask registers use four bytes. The mask bits
// are applied to all receive-identifiers, excluding receive-buffers
// 14-15 which have their own specific mask registers.
//
// RX14MSK - Receive Buffer 14 Mask register High
//
// The receive buffer 14 mask registers have the same structure as
// the receive global mask registers and are used to mask buffer 14.
//
// RX15MSK - Receive Buffer 15 Mask register High
//
// The receive buffer 15 mask registers have the same structure as
// the receive global mask registers and are used to mask buffer 15.
//
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t             : 3;
      bitfield32_t   ID28to18  : 11;
      bitfield32_t   ID17to0   : 18;

   }      F;

   uint32_t U32;

}  FLEXCAN_MSK_T;
//=============================================================================
// ECR - Error Counter Register
//
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t             : 16;  // Unused
      bitfield32_t   RX_ERR_CT : 8;   // Error counter
      bitfield32_t   TX_ERR_CT : 8;   // Error counter

   }      F;

   uint32_t U32;

}  FLEXCAN_ECR_T;
//=============================================================================
// ESR - Error and Status Register
//
// This register reflects various error conditions, general status
// and has the enable bits for three of the FlexCAN interrupt sources.
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t            : 14;  // Unused
      bitfield32_t   TWRNINT  : 1;   // Tx Warning Interrupt Flag, (1 TXECTR >= 96)Write 1 to clear, Writing 0 has no effect.
      bitfield32_t   RWRNINT  : 1;   // Rx Warning Interrupt Flag, (1 RXECTR >= 96)Write 1 to clear, Writing 0 has no effect.
      bitfield32_t   BIT1ERR  : 1;   // Transmit Bit1 Error
      bitfield32_t   BIT0ERR  : 1;   // Transmit Bit0 Error
      bitfield32_t   ACKERR   : 1;   // Acknowledge Error
      bitfield32_t   CRCERR   : 1;   // Cycle Redundancy Check Error
      bitfield32_t   FRMERR   : 1;   // Form Error
      bitfield32_t   STFERR   : 1;   // Bit Stuff Error
      bitfield32_t   TXWRN    : 1;   // Transmit Error Status Flag
      bitfield32_t   RXWRN    : 1;   // Receiver Error Status Flag
      bitfield32_t   IDLE     : 1;   // Idle Status, 1= Can Bus Idle
      bitfield32_t   TXRX     : 1;   // Transmit/Receive Status
      bitfield32_t   FLT_CONF : 2;   // Fault Confinement State
      bitfield32_t            : 1;   // Unused
      bitfield32_t   BOFFINT  : 1;   // Bus Off Interrupt
      bitfield32_t   ERRINT   : 1;   // Error Interrupt
      bitfield32_t   WAKINT   : 1;   // Wake Up Interrupt

   }      F;

   uint32_t U32;

}  FLEXCAN_ESR_T;
//=============================================================================
// IMASK2 - Interrupt Mask Register 2
//
// IMASK contains one interrupt mask bit per buffer. It allows the
// CPU32 to designate which buffers will generate interrupts after
// successful transmission/reception.
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t   MASKBUF63   : 1;   // Interrupt Mask Register 63
      bitfield32_t   MASKBUF62   : 1;   // Interrupt Mask Register 62
      bitfield32_t   MASKBUF61   : 1;   // Interrupt Mask Register 61
      bitfield32_t   MASKBUF60   : 1;   // Interrupt Mask Register 60
      bitfield32_t   MASKBUF59   : 1;   // Interrupt Mask Register 59
      bitfield32_t   MASKBUF58   : 1;   // Interrupt Mask Register 58
      bitfield32_t   MASKBUF57   : 1;   // Interrupt Mask Register 67
      bitfield32_t   MASKBUF56   : 1;   // Interrupt Mask Register 56
      bitfield32_t   MASKBUF55   : 1;   // Interrupt Mask Register 55
      bitfield32_t   MASKBUF54   : 1;   // Interrupt Mask Register 54
      bitfield32_t   MASKBUF53   : 1;   // Interrupt Mask Register 53
      bitfield32_t   MASKBUF52   : 1;   // Interrupt Mask Register 52
      bitfield32_t   MASKBUF51   : 1;   // Interrupt Mask Register 51
      bitfield32_t   MASKBUF50   : 1;   // Interrupt Mask Register 50
      bitfield32_t   MASKBUF49   : 1;   // Interrupt Mask Register 49
      bitfield32_t   MASKBUF48   : 1;   // Interrupt Mask Register 48
      bitfield32_t   MASKBUF47   : 1;   // Interrupt Mask Register 47
      bitfield32_t   MASKBUF46   : 1;   // Interrupt Mask Register 46
      bitfield32_t   MASKBUF45   : 1;   // Interrupt Mask Register 45
      bitfield32_t   MASKBUF44   : 1;   // Interrupt Mask Register 44
      bitfield32_t   MASKBUF43   : 1;   // Interrupt Mask Register 43
      bitfield32_t   MASKBUF42   : 1;   // Interrupt Mask Register 42
      bitfield32_t   MASKBUF41   : 1;   // Interrupt Mask Register 41
      bitfield32_t   MASKBUF40   : 1;   // Interrupt Mask Register 40
      bitfield32_t   MASKBUF39   : 1;   // Interrupt Mask Register 39
      bitfield32_t   MASKBUF38   : 1;   // Interrupt Mask Register 38
      bitfield32_t   MASKBUF37   : 1;   // Interrupt Mask Register 37
      bitfield32_t   MASKBUF36   : 1;   // Interrupt Mask Register 36
      bitfield32_t   MASKBUF35   : 1;   // Interrupt Mask Register 35
      bitfield32_t   MASKBUF34   : 1;   // Interrupt Mask Register 34
      bitfield32_t   MASKBUF33   : 1;   // Interrupt Mask Register 33
      bitfield32_t   MASKBUF32   : 1;   // Interrupt Mask Register 32

   }      F;

   uint32_t U32;

}  FLEXCAN_IMRH_T;

//=============================================================================
// IMASK1 - Interrupt Mask Register 1
//
// IMASK contains one interrupt mask bit per buffer. It allows the
// CPU32 to designate which buffers will generate interrupts after
// successful transmission/reception.
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t   MASKBUF31   : 1;   // Interrupt Mask Register 31
      bitfield32_t   MASKBUF30   : 1;   // Interrupt Mask Register 30
      bitfield32_t   MASKBUF29   : 1;   // Interrupt Mask Register 29
      bitfield32_t   MASKBUF28   : 1;   // Interrupt Mask Register 28
      bitfield32_t   MASKBUF27   : 1;   // Interrupt Mask Register 27
      bitfield32_t   MASKBUF26   : 1;   // Interrupt Mask Register 26
      bitfield32_t   MASKBUF25   : 1;   // Interrupt Mask Register 25
      bitfield32_t   MASKBUF24   : 1;   // Interrupt Mask Register 24
      bitfield32_t   MASKBUF23   : 1;   // Interrupt Mask Register 23
      bitfield32_t   MASKBUF22   : 1;   // Interrupt Mask Register 22
      bitfield32_t   MASKBUF21   : 1;   // Interrupt Mask Register 21
      bitfield32_t   MASKBUF20   : 1;   // Interrupt Mask Register 20
      bitfield32_t   MASKBUF19   : 1;   // Interrupt Mask Register 19
      bitfield32_t   MASKBUF18   : 1;   // Interrupt Mask Register 18
      bitfield32_t   MASKBUF17   : 1;   // Interrupt Mask Register 17
      bitfield32_t   MASKBUF16   : 1;   // Interrupt Mask Register 16
      bitfield32_t   MASKBUF15   : 1;   // Interrupt Mask Register 15
      bitfield32_t   MASKBUF14   : 1;   // Interrupt Mask Register 14
      bitfield32_t   MASKBUF13   : 1;   // Interrupt Mask Register 13
      bitfield32_t   MASKBUF12   : 1;   // Interrupt Mask Register 12
      bitfield32_t   MASKBUF11   : 1;   // Interrupt Mask Register 11
      bitfield32_t   MASKBUF10   : 1;   // Interrupt Mask Register 10
      bitfield32_t   MASKBUF9    : 1;   // Interrupt Mask Register 9
      bitfield32_t   MASKBUF8    : 1;   // Interrupt Mask Register 8
      bitfield32_t   MASKBUF7    : 1;   // Interrupt Mask Register 7
      bitfield32_t   MASKBUF6    : 1;   // Interrupt Mask Register 6
      bitfield32_t   MASKBUF5    : 1;   // Interrupt Mask Register 5
      bitfield32_t   MASKBUF4    : 1;   // Interrupt Mask Register 4
      bitfield32_t   MASKBUF3    : 1;   // Interrupt Mask Register 3
      bitfield32_t   MASKBUF2    : 1;   // Interrupt Mask Register 2
      bitfield32_t   MASKBUF1    : 1;   // Interrupt Mask Register 1
      bitfield32_t   MASKBUF0    : 1;   // Interrupt Mask Register 0

   }      F;

   uint32_t U32;

}  FLEXCAN_IMRL_T;
//=============================================================================
// IFLAG2 - Interrupt Flag Register  2
//
// IFLAG contains one interrupt flag bit per buffer. Each successful
// transmission/reception sets the corresponding IFLAG bit and, if
// the corresponding IMASK bit is set, an interrupt request will be
// generated.
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t   FLAGBUF63   : 1;   // Interrupt Flag Register 63
      bitfield32_t   FLAGBUF62   : 1;   // Interrupt Flag Register 62
      bitfield32_t   FLAGBUF61   : 1;   // Interrupt Flag Register 61
      bitfield32_t   FLAGBUF60   : 1;   // Interrupt Flag Register 60
      bitfield32_t   FLAGBUF59   : 1;   // Interrupt Flag Register 59
      bitfield32_t   FLAGBUF58   : 1;   // Interrupt Flag Register 58
      bitfield32_t   FLAGBUF57   : 1;   // Interrupt Flag Register 57
      bitfield32_t   FLAGBUF56   : 1;   // Interrupt Flag Register 56
      bitfield32_t   FLAGBUF55   : 1;   // Interrupt Flag Register 55
      bitfield32_t   FLAGBUF54   : 1;   // Interrupt Flag Register 54
      bitfield32_t   FLAGBUF53   : 1;   // Interrupt Flag Register 53
      bitfield32_t   FLAGBUF52   : 1;   // Interrupt Flag Register 52
      bitfield32_t   FLAGBUF51   : 1;   // Interrupt Flag Register 51
      bitfield32_t   FLAGBUF50   : 1;   // Interrupt Flag Register 50
      bitfield32_t   FLAGBUF49   : 1;   // Interrupt Flag Register 49
      bitfield32_t   FLAGBUF48   : 1;   // Interrupt Flag Register 48
      bitfield32_t   FLAGBUF47   : 1;   // Interrupt Flag Register 47
      bitfield32_t   FLAGBUF46   : 1;   // Interrupt Flag Register 46
      bitfield32_t   FLAGBUF45   : 1;   // Interrupt Flag Register 45
      bitfield32_t   FLAGBUF44   : 1;   // Interrupt Flag Register 44
      bitfield32_t   FLAGBUF43   : 1;   // Interrupt Flag Register 43
      bitfield32_t   FLAGBUF42   : 1;   // Interrupt Flag Register 42
      bitfield32_t   FLAGBUF41   : 1;   // Interrupt Flag Register 41
      bitfield32_t   FLAGBUF40   : 1;   // Interrupt Flag Register 40
      bitfield32_t   FLAGBUF39   : 1;   // Interrupt Flag Register 39
      bitfield32_t   FLAGBUF38   : 1;   // Interrupt Flag Register 38
      bitfield32_t   FLAGBUF37   : 1;   // Interrupt Flag Register 37
      bitfield32_t   FLAGBUF36   : 1;   // Interrupt Flag Register 36
      bitfield32_t   FLAGBUF35   : 1;   // Interrupt Flag Register 35
      bitfield32_t   FLAGBUF34   : 1;   // Interrupt Flag Register 34
      bitfield32_t   FLAGBUF33   : 1;   // Interrupt Flag Register 33
      bitfield32_t   FLAGBUF32   : 1;   // Interrupt Flag Register 32

   }      F;

   uint32_t U32;

}  FLEXCAN_IFRH_T;
//=============================================================================
// IFLAG1 - Interrupt Flag Register  1
//
// IFLAG contains one interrupt flag bit per buffer. Each successful
// transmission/reception sets the corresponding IFLAG bit and, if
// the corresponding IMASK bit is set, an interrupt request will be
// generated.
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t   FLAGBUF31   : 1;   // Interrupt Flag Register 31
      bitfield32_t   FLAGBUF30   : 1;   // Interrupt Flag Register 30
      bitfield32_t   FLAGBUF29   : 1;   // Interrupt Flag Register 29
      bitfield32_t   FLAGBUF28   : 1;   // Interrupt Flag Register 28
      bitfield32_t   FLAGBUF27   : 1;   // Interrupt Flag Register 27
      bitfield32_t   FLAGBUF26   : 1;   // Interrupt Flag Register 26
      bitfield32_t   FLAGBUF25   : 1;   // Interrupt Flag Register 25
      bitfield32_t   FLAGBUF24   : 1;   // Interrupt Flag Register 24
      bitfield32_t   FLAGBUF23   : 1;   // Interrupt Flag Register 23
      bitfield32_t   FLAGBUF22   : 1;   // Interrupt Flag Register 22
      bitfield32_t   FLAGBUF21   : 1;   // Interrupt Flag Register 21
      bitfield32_t   FLAGBUF20   : 1;   // Interrupt Flag Register 20
      bitfield32_t   FLAGBUF19   : 1;   // Interrupt Flag Register 19
      bitfield32_t   FLAGBUF18   : 1;   // Interrupt Flag Register 18
      bitfield32_t   FLAGBUF17   : 1;   // Interrupt Flag Register 17
      bitfield32_t   FLAGBUF16   : 1;   // Interrupt Flag Register 16
      bitfield32_t   FLAGBUF15   : 1;   // Interrupt Flag Register 15
      bitfield32_t   FLAGBUF14   : 1;   // Interrupt Flag Register 14
      bitfield32_t   FLAGBUF13   : 1;   // Interrupt Flag Register 13
      bitfield32_t   FLAGBUF12   : 1;   // Interrupt Flag Register 12
      bitfield32_t   FLAGBUF11   : 1;   // Interrupt Flag Register 11
      bitfield32_t   FLAGBUF10   : 1;   // Interrupt Flag Register 10
      bitfield32_t   FLAGBUF9    : 1;   // Interrupt Flag Register 9
      bitfield32_t   FLAGBUF8    : 1;   // Interrupt Flag Register 8
      bitfield32_t   FLAGBUF7    : 1;   // Interrupt Flag Register 7
      bitfield32_t   FLAGBUF6    : 1;   // Interrupt Flag Register 6
      bitfield32_t   FLAGBUF5    : 1;   // Interrupt Flag Register 5
      bitfield32_t   FLAGBUF4    : 1;   // Interrupt Flag Register 4
      bitfield32_t   FLAGBUF3    : 1;   // Interrupt Flag Register 3
      bitfield32_t   FLAGBUF2    : 1;   // Interrupt Flag Register 2
      bitfield32_t   FLAGBUF1    : 1;   // Interrupt Flag Register 1
      bitfield32_t   FLAGBUF0    : 1;   // Interrupt Flag Register 0

   }      F;

   uint32_t U32;

}  FLEXCAN_IFRL_T;
//=============================================================================
// CTRSTATUS - Can Message Control/Status
//
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t              : 4;   
      bitfield32_t   CODE       : 4;   // Message Code
      bitfield32_t              : 1;   
      bitfield32_t   SRR        : 1;   // Substitute Remote Request
      bitfield32_t   IDE        : 1;   // Extended format, 0=STD,1=Ext
      bitfield32_t   RTR        : 1;   // Remote Transmission Request
      bitfield32_t   LENGTH     : 4;   // Message Length
      bitfield32_t   TIME_STAMP : 16;  // Message Time Stamp

   }      F;

   uint32_t U32;

}  FLEXCAN_CTRSTATUS_T;
    
//=============================================================================
// ID - Can Message ID
//
//=============================================================================
typedef union
{
   struct
   {
      bitfield32_t   PRIO       : 3;
      bitfield32_t   STD_EXT    : 11;
      bitfield32_t   EXTENDED   : 18;

   }      F;

   uint32_t U32;

}  FLEXCAN_ID_T;
typedef union
{
   uint8_t   U8[8];
   uint16_t U16[4];
   uint32_t U32[2];

}  FLEXCAN_DATA_T;
//=============================================================================
// CAN_MSG - The structure of the Can Message Buffer.
//
// This structure will support both Standard and Extended formats.
// The IDHIGH and IDLOW fields structure is as follows:
//   Standard: ID_HIGH_STD and ID_LOW_STD
//   Extended: ID_HIGH_EX  and ID_LOW_EX
//=============================================================================
typedef union
{
   struct
   {
      FLEXCAN_CTRSTATUS_T   CTRSTS;    // Control/Status
      FLEXCAN_ID_T          ID;        // ID
      FLEXCAN_DATA_T        DATA;      // Data Bytes

   }         F;

   uint32_t U32[4];

}  FLEXCAN_MSG_T;
//=============================================================================
// FLEXCAN Module Register Structure
//=============================================================================
typedef volatile struct FLEXCAN_Tag
{
   FLEXCAN_MCR_T       MCR;                       // 0x0000 - 0x0003
   FLEXCAN_CR_T        CR;                        // 0x0004 - 0x0007
   FLEXCAN_TIMER_T     TIMER;                     // 0x0008 - 0x000B
   uint8_t             unused1[4];                // 0x000C - 0x000F
   FLEXCAN_MSK_T       RXGMASK;                   // 0x0010 - 0x0013
   FLEXCAN_MSK_T       RX14MASK;                  // 0x0014 - 0x0017
   FLEXCAN_MSK_T       RX15MASK;                  // 0x0018 - 0x001B
   FLEXCAN_ECR_T       ECR;                       // 0x001C - 0x001F
   FLEXCAN_ESR_T       ESR;                       // 0x0020 - 0x0023
   FLEXCAN_IMRH_T      IMRH;                      // 0x0024 - 0x0027
   FLEXCAN_IMRL_T      IMRL;                      // 0x0028 - 0x002B
   FLEXCAN_IFRH_T      IFRH;                      // 0x002C - 0x002F
   FLEXCAN_IFRL_T      IFRL;                      // 0x0030 - 0x0033
   uint8_t             unused2[76];               // 0x0034 - 0x007F 
   FLEXCAN_MSG_T       MSGBUF[CAN_NO_OF_MSG_BUF]; // 0x0080 - 0x047F
   uint8_t             unused3[1024];             // 0x0480 - 0x087F 
   FLEXCAN_MSK_T       RXIMR[CAN_NO_OF_MSG_BUF];  // 0x0880 - 0x097F

}  FLEXCAN_T;

#endif // HW_FLEXCAN_H

