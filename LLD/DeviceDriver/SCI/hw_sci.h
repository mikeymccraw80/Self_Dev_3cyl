#ifndef HW_SCI_H
#define HW_SCI_H
//==============================================================================
//
//         COPYRIGHT, 2002, DELPHI TECHNOLOGIES, INC. ALL RIGHTS RESERVED
//                                  Delphi Confidential
//
// ===========================================================================
// %name:            hw_sci.h %
//
// created_by:       qznx5b
//
// date_created:     Tue Feb 7, 2006
//
// %derived_by:nztnkh %date_modified:    Fri Jun 10 08:12:01 2011 %
//
// %version:         kok_pt2#2 %
//
// ===========================================================================
// @doc
//
// @module hw_sci.h | This module provides the standard definitions for the 
//    Enhanced Serial Communication Interface (eSCI).
//
// @normal Copyright <cp> 2006 Delphi Technologies, Inc. All Rights Reserved
//
// @end
//
// SPECIFICATION REVISION:
//     MPC5644A Microcontroller Reference Manual,
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// 
//==============================================================================
#include "io_type.h"

// ============================================================================
//w1c bit Masks
// ============================================================================
#define ESCI_SR_TDRE_CLEAR_MASK     (0x80EF00FC)
#define ESCI_SR_TC_CLEAR_MASK       (0x40EF00FC)
#define ESCI_SR_RDRF_CLEAR_MASK     (0x20EF00FC)
#define ESCI_SR_IDLE_CLEAR_MASK     (0x10EF00FC)
#define ESCI_SR_OR_CLEAR_MASK       (0x08EF00FC)
#define ESCI_SR_NF_CLEAR_MASK       (0x04EF00FC)
#define ESCI_SR_FE_CLEAR_MASK       (0x02EF00FC)
#define ESCI_SR_PF_CLEAR_MASK       (0x01EF00FC)
#define ESCI_SR_BERR_CLEAR_MASK     (0x00FF00FC)
#define ESCI_SR_RXRDY_CLEAR_MASK    (0x00EF80FC)
#define ESCI_SR_TXRDY_CLEAR_MASK    (0x00EF40FC)
#define ESCI_SR_LWAKE_CLEAR_MASK    (0x00EF20FC)
#define ESCI_SR_STO_CLEAR_MASK      (0x00EF10FC)
#define ESCI_SR_PBERR_CLEAR_MASK    (0x00EF08FC)
#define ESCI_SR_CERR_CLEAR_MASK     (0x00EF04FC)
#define ESCI_SR_CKERR_CLEAR_MASK    (0x00EF02FC)
#define ESCI_SR_FRC_CLEAR_MASK      (0x00EF01FC)
#define ESCI_SR_UREQ_CLEAR_MASK     (0x00EF00FE)
#define ESCI_SR_OVFL_CLEAR_MASK     (0x00EF00FD)
//==============================================================================
//    Type Definitions
//==============================================================================
//==============================================================================
// eSCI Control Register 1 (eSCIx_CR1)
// Addresses:   0xFFFB0002 (A)
//              0xFFFB4002 (B)
//              0xFFFB8002 (C)
// Size(byte):  2
// Reset value: 0x0000
// Field Descriptions:

//   Fields Bit(s) R/W Descriptions
//
//   SBR   [28:16]    r/w   Serial Baud Rate. 
//                           This field provides the baud rate control value SBR.
//
//   LOOPS  15     r/w Loop Selection
//                     0 - Normal operation. Loop operation disabled
//                     1 - Loop operation enabled. RXD pin is disconnected from
//                         eSCI and the tx output is internally connected to the
//                         rx input. Both tx and rx should be enabled.
//
//          14      r   reserved
//
//   RSRC   13     r/w Receiver Source (when LOOPS = 1)
//                     0 - Loop mode with RXD internally connnected to TXD
//                     1 - Single-wire mode with RXD connected to TXD
//
//   M      12     r/w Data Format Mode
//                     0 - 1 start bit, 8 data bits, 1 stop bit
//                     1 - 1 start bit, 9 data bits, 1 stop bit
//
//   WAKE   11     r/w Wakeup Condition
//                     0 - Idle condition on RXD wakeup
//                     1 - Address mark wakeup (a logic 1 in the MSB of a
//                         receive data character)
//
//   ILT    10     r/w Idle Line Type - determines when the receiver starts
//                     counting logic 1s as idle character bits.
//                     0 - Idle character bit count begins after start bit (a
//                         string of logic 1s preceding the stop bit may cause
//                         false recognition of an idle character)
//                     1 - Idle character bit count begins after stop bit (avoid
//                         false recognition of an idle character, but requires
//                         properly synchronized transmission)
//
//   PE     9     r/w Parity Enable
//                     0 - Parity function disabled
//                     1 - Parity function enabled. Insert a parity bit in the
//                         MSB position of the tx word. During reception the
//                         parity bit is copied to the data register.
//
//   PT     8     r/w Parity Type
//                     0 - Even parity (even number of 1s clear the parity bit)
//                     1 - Odd parity  (odd number of 1s clear the parity bit)
//
//   TIE    7     r/w Tx Data Register empty flag SR[TDRE] interrupt enable.
//                     The interrupt is suppressed in TX DMA mode.
//                     0 - TDRE interrupt disabled
//                     1 - TDRE interrupt enabled
//
//   TCIE   6     r/w Transmission Complete Flag SR[TC] interrupt enable.
//                     The interrupt is suppressed in TX DMA mode.
//                     0 - TC interrupt request is disabled
//                     1 - TC interrupt request is enabled
//
//   RIE    5     r/w Recever Full SR[RDRF] and Overrun SR[OR] Interrupt Enable
//                     0 - RDRF and OR interrupt request disabled
//                     1 - RDRF and OR interrupt request enabled
//
//   ILIE   4     r/w Idle Line SR[IDLE] Interrupt Enable
//                     0 - IDLE interrupt request disabled
//                     1 - IDLE interrupt request enabled
//
//   TE     3     r/w Transmitter Enable. Enables eSCI transmitter and
//                     configure TXD pin as being controlled by eSCI. TE bit can
//                     be used to queue an idle preamble
//                     0 - Thansmitter disabled
//                     1 - Thansmitter enabled
//
//   RE     2     r/w Receiver Enable
//                     0 - Receiver disabled
//                     1 - Receiver enabled
//
//   RWU    1     r/w Receiver Wakeup. Standby state.
//                     0 - Normal operation
//                     1 - RWU enales the wakeup function and inhibits further
//                         receiver interrupt requests. (Normally hardware wakes
//                         receiver by automatically clearing RWU)
//
//   SBK    0     r/w Send Break. Toggling SBK sends one break character (10 or
//                     11 logic 0s, respactively 13 or 14 logic 0s if CR2[BRK13]
//                     is set).Toggling implies clearing the SBK bit before the
//                     break character has finished transmitting. As long as SBK
//                     is set, the transmitter continues to send complete break
//                     characters.
//                     0 - No break characters
//                     1 - Tranmit break characters.
//
//==============================================================================
typedef struct SCI_CR1_F_Tag
{
   bitfield32_t         :3;   // Bit [31 : 29]
   bitfield32_t SBR     :13;  // Bit [28 : 16]
   bitfield32_t LOOPS   :1;   // Bit 15
   bitfield32_t         :1;   // Bit 14
   bitfield32_t RSRC    :1;   // Bit 13
   bitfield32_t M       :1;   // Bit 12
   bitfield32_t WAKE    :1;   // Bit 11
   bitfield32_t ILT     :1;   // Bit 10
   bitfield32_t PE      :1;   // Bit 9
   bitfield32_t PT      :1;   // Bit 8
   bitfield32_t TIE     :1;   // Bit 7
   bitfield32_t TCIE    :1;   // Bit 6
   bitfield32_t RIE     :1;   // Bit 5
   bitfield32_t ILIE    :1;   // Bit 4
   bitfield32_t TE      :1;   // Bit 3
   bitfield32_t RE      :1;   // Bit 2
   bitfield32_t RWU     :1;   // Bit 1
   bitfield32_t SBK     :1;   // Bit 0

} SCI_CR1_F_T;

typedef union SCI_CR1_Tag
{
   SCI_CR1_F_T F;
   uint8_t      U8[4];
   uint16_t     U16[2];
   uint32_t     U32;

} SCI_CR1_T;

//==============================================================================
// eSCI Control Register 2 (eSCIx_CR2)
// Addresses:   0xFFFB0004 (A)
//              0xFFFB4004 (B)
//              0xFFFB8004 (C)
// Size(byte):  2
// Reset value: 0x2000
// Field Descriptions:
//   Fields Bit(s) R/W Descriptions
//   MDIS   0      r/w Modle Disable
//                     0 - Module enabled (default)
//                     1 - Module disabled
//
//   FBR    1      r/w Fast Bit Eror Detection Enable.
//                     0 - Enabled. Bit errors are detected on a per bit basis
//                     1 - Disabled. Bit errors are detected on a per byte basis
//
//   BSTP   2      r/w Bit Error/Physical Bus Error Stop. Causes DMA TX request
//                     to be suppressed, as long asthe bit error and physicle
//                     writes bus error flags are not cleared. This stops
//                     further DMA writes, which would otherwise cause data
//                     bytes to be interpreted as LIN header information. 
//                     0 - Not stop DMA TX while bit error/physical bus error
//                         exists
//                     1 - Stop DMA TX while bit error/physical bus error exists
//
//   IEBERR 3      r/w Bit Error Interrupt Enable
//                     0 - Disabled
//                     1 - Enabled
//
//   RXDMA  4      r/w RX DMA Channel Active. Override RIE bit.
//                     0 - RX DMA channel disabled
//                     1 - RX DMA channel enabled. If eSCI received data, it
//                         will raise a DMA RX request instead of RX interrupt.
//
//   TXDMA  5      r/w TX DMA Channel Active.
//                     0 - TX DMA channel disabled
//                     1 - TX DMA channel enabled. Whenever eSCI is able to
//                         transmit data, it will raise a DMA TX request. It
//                         overrides TIE TCIE bits and prevents eSCI from
//                         generating TX interrupt.
//
//   BRK13  6      r/w Break Transmit Character Length
//                     0 - Break character is 10 or 11 bits long
//                     1 - Break character is 13 or 14 bits long
//          7      r/w reserved
//
//   TXDIR         r/w TXD pin output enable. 
//                         This bit determines whether the TXD pin is used 
//                         as an output.
//                       0 TXD pin is not used as output.
//                       1 TXD pin is used as output.
//   Note: This bit is used in Single Wire Mode only.
//
//   BESM13 8      r/w Bit ErrorSample Mode. Determines when to sample the
//                     incoming bit to detect a bit error when FBR is set.
//                     0 - Sample at RT clock 9
//                     1 - Sample at RT clock 13
//
//   SBSTP  9      r/w SCI Bit Error Stop. Allowing to stop driving the LIN bus
//                     quickly after a bit error has been detected
//                     0 - Not stop after a SCI bit error is asserted
//                     1 - Stop after a SCI bit error is asserted

//   RXPOL 10      r/w  RXD Pin polarity. 
//                      This bit controls the polarity of the RXD pin. 
//                    0 - Normal Polarity.
//                    1 - Inverted Polarity.

//   PMSK          r/w  Parity Bit Masking. 
//                      This bit defines whether the received parity bit 
//                      is presented in the related bit position in the
//                      SCI Data Register (eSCI_SDR).
//                    0 - The received parity bit is presented in the bit 
//                        position related to the parity bit.
//                    1 - The value 0 is presented in the bit position 
//                        related to the parity bit.
//
//   ORIE   12     r/w Overrun Error Interrupt Enable..
//                     0 - Overrun Error Interupt disabled
//                     1 - Generates an interrupt when an overrun error is
//                         detected
//
//   NFIE   13     r/w Noise Flag Interrupt Enable
//                     0 - Noise flag interrupt disabled
//                     1 - Noise flag interrupt enabled
//
//   FEIE   14     r/w Frame Error Interrupt Enable
//                     0 - Frame error interrupt request disabled
//                     1 - Frame error interrupt request enabled
//
//   PFIE   15     r/w Parity Flag Interrupt Enable.
//                     0 - Parity flag interrupt disabled
//                     1 - Parity flag interrupt enabled
//
//==============================================================================
typedef struct SCI_CR2_F_Tag
{
   bitfield16_t MDIS   :1;   // Bit 0
   bitfield16_t FBR    :1;   // Bit 1
   bitfield16_t BSTP   :1;   // Bit 2
   bitfield16_t IEBERR :1;   // Bit 3
   bitfield16_t RXDMA  :1;   // Bit 4
   bitfield16_t TXDMA  :1;   // Bit 5
   bitfield16_t BRK13  :1;   // Bit 6
   bitfield16_t TXDIR  :1;   // Bit 7
   bitfield16_t BESM13 :1;   // Bit 8
   bitfield16_t SBSTP  :1;   // Bit 9
   bitfield16_t RXPOL  :1;   // Bit 10
   bitfield16_t PMSK   :1;   // Bit 11
   bitfield16_t ORIE   :1;   // Bit 12
   bitfield16_t NFIE   :1;   // Bit 13
   bitfield16_t FEIE   :1;   // Bit 14
   bitfield16_t PFIE   :1;   // Bit 15

} SCI_CR2_F_T;

typedef union SCI_CR2_Tag
{
   SCI_CR2_F_T F;
   uint16_t    U16;

} SCI_CR2_T;

//==============================================================================
// eSCI Data Register (eSCIx_DR)
// Addresses:   0xFFFB0006 (A)
//              0xFFFB4006 (B)
//              0xFFFB8006 (C)
// Size(byte):  2
// Reset value: 0x0000
// Field Descriptions:
//   Fields Bit(s) R/W Descriptions
//   R8     0      r   Received bit 8 (9th data bit received when eSCI is
//                     configured for 9-bit data format (M = 1))
//
//   T8     1      r/w Transmit bit 8 (9th data bit when eSCI is configured for
//                     9-bit data format (M=1))
//
//   ERR    2      r   Receive Error Bit. 
//                     This bit indicates the occurrence of the errors selected 
//                     by the Control Register 3 (eSCI_CR3)
//                     during the reception of the frame presented in 
//                     SCI Data Register (eSCI_SDR). 
//                     In case of an overrun error for
//                     subsequent frames this bit is set too.
//                   0 - None of the selected errors occured.
//                   1 - At least one of the selected errors occured.
//
//          0      r   Reserved
//   RD8_11  [4:7]  r  Received Data. 
//                     The semantic of this field depends on the frame format 
//                     selected by eSCI_CR3[M2] and eSCI_CR1[M].
//                     [M2 = 1,M = 1]: value of the received data bits 11:8. 
//                     (Rn = BITn).It is all 0 for all other frame formats.
//
//   R7-Ro/ [8:15] r/w Received/transmit data bits 7-0.
//   T7-T0 
//
//==============================================================================
typedef struct SCI_DR_F_Tag
{
   bitfield16_t R8     :1;   // Bit 0
   bitfield16_t T8     :1;   // Bit 1
   bitfield16_t ERR    :1;   // Bit 1
   bitfield16_t        :1;   // Bit 1
   bitfield16_t RD8_11 :4;   // Bit 1
   bitfield16_t D      :8;   // Bit [8:15]

} SCI_DR_F_T;

typedef union SCI_DR_Tag
{
   SCI_DR_F_T F;
   uint8_t     U8[2];
   uint16_t    U16;

} SCI_DR_T;

//=============================================================================
//     SCI Status Registers
//=============================================================================
//==============================================================================
// eSCI Status Register (eSCIx_SR1)
// Addresses:   0xFFFB0008 (A)
//              0xFFFB4008 (B)
//              0xFFFB8008 (C)
// Size(byte):  2
// Reset value: 0x0000
// Field Descriptions:
//   Fields Bit(s) R/W Descriptions
//   TDRE   0       r  Transmit Data Register Empty Flag.
//                     0 - No byte transferred to tx shift register
//                     1 - Byte transferred to tx shift register; tx data
//                         register empty.
//
//   TC     1       r  Transmit Complete Flag
//                     0 - Transmission in progress
//                     1 - No transmission in progress, TXD signal becomes idle
//
//   RDRF   2       r  Receive Data Register Full Flag
//                     0 - Data not available in DR or has been resd
//                     1 - Received data available in DR
//                     Not need to be cleared in LIN/DMA mode
//
//   IDLE   3       r  Idle Line Flag
//                     0 - Receiver input is either active now or has never been
//                         active since IDLE flag was last cleared
//                     1 - Receive input has become idle
//
//   OR     4       r  Overrun Flag
//                     0 - No overrun
//                     1 - Overrun (second frame received before 1st frame was
//                         read by software 
//
//   NF     5       r  Noise Flag
//                     0 - No noise
//                     1 - Noise detected on the rx input (not set if OR set)
//
//   FE     6       r  Frame Error Flag
//                     0 - No framing error
//                     1 - Framing error (a logic 0 is accepted as the stoip bit
//                         or in LIN mode when break characters are set)
//
//   PF     7       r  Parity Error Flag
//                     0 - No parity eror
//                     1 - Rx data parity error detected when PE=1
//          [8:10]  r  reserved
//
//   BERR   11      r  Bit Error in LIN mode 
//                     (Bit on bus does not match the tx bit)
//                     0 - No bit error
//                     1 - Bit error detected
//
//          [12:19] r  reserved
//
//   TACT   18      r  Transmitter Active. 
//                     The status bit is set as long as the transmission 
//                     of a frame or special character is ongoing.
//                     0 - No transmission in progress.
//                     1 - Transmission in progress.
//
//   RAF    17      r  Receiver Active Flag
//                     0 - No reception is in progress
//                     1 - Peception in progress
//   RXRDY  16      r/w LIN Data Received (clear the bit by writting it with 1)
//                     0 - No data received by LINRX register
//                     1 - LINRX register received a byte
//
//   TXRDY  15     r/w LIN TX Ready to Receive Data (clear the bit by writting
//                     it with 1)
//                     0 - LIN FSM can not accept another write to LINTX
//                     1 - LIN FSM can accept another write to LINTX
//
//   LWAKE  14     r/w LIN Wakeup Signal Received Flag
//                     0 - No LIN wakeup signal has been detected
//                     1 - A LIN slave has sent a wakeup signal on the bus
//
//   STO    13     r/w Slave Time Out (NO_RESPONSE_ERROR)
//                     0 - No slave time out detected
//                     1 - A slave does not complete a frame within the
//                         specified maximum frame length (For LIN 1.3
//                         TFRAME_MAX = (10 * DATA + 44) * 1.4
//
//   PBERR  12     r/w Physical Bus Error (No valid message can be generated on
//                     the bus. After start of a byte transmission, input
//                     remains unchanged for 31 cycles. Will reset FSM) 
//                     0 - No physicle bus error detected
//                     1 - Physicle bus error detected
//
//   CERR   11     r/w CRC Error. CRC pattern received with an extended frame
//                     was not correct.
//                     0 - No CRC error
//                     1 - CRC error detected
//
//   CKERR  10     r/w Checksum Error
//                     0 - No error
//                     1 - Checksum Error on a received frame
//
//   FRC    9     r/w LIN Frame Complete
//                     0 - LIN frame not completed
//                     1 - LIN frame completedly transmitted. All LIN bytes
//                         received
//
//          [8:3] r  reserved
//
//   UREQ   1     r/w Unrequested Data Received Flag. 
//                     This interrupt flag is set when unrequested activity 
//                     has been detected on the LIN bus.
//
//   OVFL   0     r/w LRR Overflow ( Lin rx register has not been read before
//                     a new data byte has been received from the LIN bus)
//                     0 - No LRR overflow
//                     1 - LRR overflow
//==============================================================================

typedef struct SCI_IFSR1_F_Tag
{
   bitfield32_t TDRE  :1;   // Bit 31
   bitfield32_t TC    :1;   // Bit 30
   bitfield32_t RDRF  :1;   // Bit 29
   bitfield32_t IDLE  :1;   // Bit 28
   bitfield32_t OR    :1;   // Bit 27
   bitfield32_t NF    :1;   // Bit 26
   bitfield32_t FE    :1;   // Bit 25
   bitfield32_t PF    :1;   // Bit 24
   bitfield32_t       :3;   // Bit [23:21]
   bitfield32_t BERR  :1;   // Bit 20
   bitfield32_t       :2;   // Bit [19:18]
   bitfield32_t TACT  :1;   // Bit 17
   bitfield32_t RACT  :1;   // Bit 16
   bitfield32_t RXRDY :1;   // Bit 15
   bitfield32_t TXRDY :1;   // Bit 14
   bitfield32_t LWAKE :1;   // Bit 13
   bitfield32_t STO   :1;   // Bit 12
   bitfield32_t PBERR :1;   // Bit 11
   bitfield32_t CERR  :1;   // Bit 10
   bitfield32_t CKERR :1;   // Bit 9
   bitfield32_t FRC   :1;   // Bit 8
   bitfield32_t       :6;   // Bit [7:2]
   bitfield32_t UREQ  :1;   // Bit 1
   bitfield32_t OVFL  :1;   // Bit 0

} SCI_IFSR1_F_T;

typedef union SCI_IFSR1_Tag
{
   SCI_IFSR1_F_T F;
   uint8_t     U8[4];
   uint32_t    U32;

} SCI_IFSR1_T;

//==============================================================================
// eSCI LIN Control Register1 (eSCIx_LCR1)
// Addresses:   0xFFFB000C (A)
//              0xFFFB400C (B)
//              0xFFFB800C (C)
// Size(byte):  2
// Reset value: 0x0000
// Field Descriptions:
//   Fields Bit(s) R/W Descriptions
//   LRES   0      r/w LIN Resynchronize. Causes the LIN protocol engine to
//                     return to start state. This happens automatically after
//                     bit errors, but software may force a return to start
//                     state manually by setting and then clearing this bit.
//
//   WU     1      r/w LIN Bus Wakeup. Generates a wakeup signal on the LIN bus.
//                     This must be set before a transmission, if the bus is in
//                     sleep mode. This bit will auto-clear, so a read from this
//                     bit will always return 0.
//
//   WUD0/1 [2:3]  r/w Wakeup delimiter time. Determines how long the LIN engine
//                     waits after generating a wakeup signal, before starting a
//                     new frame. WUD0/1 and the delimiter time:
//                            WUD0 WUD1 Bit Times
//                            0    0    4
//                            0    1    8
//                            1    0    32
//                            1    1    64
//
//         [4:5]   r   reserved
//
//   PRTY   25      r/w Activating parity generation. Generate the two Parity
//                     Bits in the LIN header.
//
//   LIN    24      r/w LIN mode. Switch device into LIN mode.
//
//   RXIE   23      r/w LIN RXREG ready interrupt enable. Generates an Interrupt
//                     when new data is available in the LIN RXREG.
//
//   TXIE   22      r/w LIN TXREG ready interrupt enable. Generates an Interrupt
//                     when new data can be written to the LIN TXREG.
//
//   WUIE   21     r/w RX wakeup interrupt enable. Generates an Interrupt when a
//                     wakeup flag from a LIN slave has been received.
//
//   STIE   20     r/w Slave timeout error interrupt enable. Generates an
//                     Interrupt when the slave response is too slow.
//
//   PBIE   19     r/w Physical bus error interrupt enable. Generates an
//                     Interrupt when no valid message can be generated on the
//                     bus.
//
//   CIE    18     r/w CRC error interrupt enable. Generates an Interrupt when a
//                     CRC error on a received extended frame is detected.
//
//   CKIE   17     r/w Checksum error interrupt enable. Generates an Interrupt
//                     on a detected Checksum Error.
//
//   FCIE   16     r/w Frame complete interrupt enable. Generates an Interrupt
//                     after complete transmission of a TX frame, or after the
//                     last byte of an RX frame is received. (The complete frame
//                     includes all header, data, CRC and checksum bytes as
//                     applicable.)
//
//  0       15:10   r   Reserved
//
//   UQIE    9     r/w Unrequested Data Received Interrupt Enable. 
//                     This bit controls the eSCI_IFSR2[UREQ] interrupt request
//                     generation.
//                     0 - UREQ interrupt request generation disabled.
//                     1 - UREQ interrupt request generation enabled.
//
//   OFIE    8     r/w Overflow interrupt enable. Generates an Interrupt when a
//                     data byte in the eSCIx_LRR register has not been read
//                     before the next data byte is received.
//
//  0        7:0    r   Reserved
//==============================================================================
typedef struct SCI_LCR1_F_Tag
{
   bitfield32_t LRES :1;   // Bit 31
   bitfield32_t WU   :1;   // Bit 30
   bitfield32_t WUD  :2;   // Bit [29:28]
   bitfield32_t LDBG :1;   // Bit 27
   bitfield32_t DSF  :1;   // Bit 26
   bitfield32_t PRTY :1;   // Bit 25
   bitfield32_t LIN  :1;   // Bit 24
   bitfield32_t RXIE :1;   // Bit 23
   bitfield32_t TXIE :1;   // Bit 22
   bitfield32_t WUIE :1;   // Bit 21
   bitfield32_t STIE :1;   // Bit 20
   bitfield32_t PBIE :1;   // Bit 19
   bitfield32_t CIE  :1;   // Bit 18
   bitfield32_t CKIE :1;   // Bit 17
   bitfield32_t FCIE :1;   // Bit 16
   bitfield32_t      :6;   // Bit 15:10
   bitfield32_t UQIE :1;   // Bit 9
   bitfield32_t OFIE :1;   // Bit 8
   bitfield32_t      :8;   // Bit 7:0

} SCI_LCR1_F_T;

typedef union SCI_LCR1_Tag
{
   SCI_LCR1_F_T F;
   uint8_t      U8[4];
   uint16_t     U16[2];
   uint32_t     U32;

} SCI_LCR1_T;

//==============================================================================
// eSCI LIN Transmit Register (eSCIx_LTR)
// Addresses:   0xFFFB0010 (A)
//              0xFFFB4010 (B)
//              0xFFFB4010 (c)
// Size(byte):  4
// Reset value: 0x00000000
// Field Descriptions:
//   Fields Bit(s) R/W Descriptions
//   ---------------------------------------------------------------------------
//   (LIN first byte)
//   P1/P0  [0:1]  w   Parity bits. When parity generation is enabled
//                     (eSCIx_LCR[PRTY] = 1), the parity bits are generated
//                     automatically. Otherwise they must be provided in this
//                     field.
//
//   ID5..0 [2:7]  w   Header bits. The LIN address, for LIN 1.x standard frames
//                     the length bits must be set as following. Extended frames
//                     are recognized by their specific patterns.
//                         ID5 ID4 data bytes
//                         0   0   2
//                         0   1   2
//                         1   0   4
//                         1   1   8
//   ---------------------------------------------------------------------------
//   (LIN second byte)
//   L7..0  [0:7]  w   Length bit n. Defines the length of the frame (0 to 255
//                     data bytes). This information is needed by the LIN state
//                     machine in order to insert the checksum or CRC pattern as
//                     required. LIN 1.x slaves will only accept frames with 2,
//                     4 or 8 data bytes.
//   ---------------------------------------------------------------------------
//   (LIN third byte)
//   HDCHK  0      w   Header checksum enable. Include the header fields into
//                     the mod 256 checksum of the standard frames.
// 
//   CSUM   1      w   Checksum enable. Append a checksum byte to the end of a
//                     TX frame. Verify the checksum byte of a RX frame.
// 
//   CRC    2      w   CRC enable. Append two CRC bytes to the end of a TX frame.
//                     Verify the two CRC bytes of a RX frame are correct. If
//                     both CSUM and CRC bits are set, the LIN FSM will first
//                     append the CRC bytes, then the checksum byte. If HDCHK is
//                     set, the CRC calculation will include header and data
//                     bytes, otherwise just the data bytes. CRC bytes are not
//                     part of the LIN standard; they are normal data bytes and
//                     belong to a higher-level protocol.
//
//   TX     3      w   Transmit direction. Indicates a TX frame; that is, the
//                     eSCI will transmit data to a slave. Otherwise, an RX
//                     frame is assumed, and the eSCI only transmits the header.
//                     The data bytes are received from the slave.
//                     0 - RX frame
//                     1 - TX frame
//   
//   T11..8 [4:7]  w   Timeout bits[11:8]. Sets the counter to determine a
//                     NO_RESPONSE_ERROR, if the frame is a read access to a LIN
//                     slave. According to LIN standard rev 1.3, the value must
//                     be (10 × NDATA + 44) × 1.4. For transmissions, this
//                     counter has to be set to 0. For RX frames, the fourth
//                     byte contains timeout bits [7:0]. The time is specified
//                     in multiples of bit times. The timeout period starts with
//                     the transmission of the LIN break character.
//   ---------------------------------------------------------------------------
//   (LIN 4th Rx byte)
//   T7..0  [0:7]  w   Timeout bits[7:0]. Sets the counter to determine a
//                     NO_RESPONSE_ERROR, if the frame is a read access to a LIN
//                     slave. According to LIN standard rev 1.3, the value must
//                     be (10 × NDATA + 44) × 1.4. The timeout period starts
//                     with the transmission of the LIN break character.
//
//   (LIN LIN Tx 4th+ byte/Rx 5th+ bytes
//   D7..0  [0:7]  w   Data bits for transmission.
//   ---------------------------------------------------------------------------
//==============================================================================
typedef struct SCI_LTR_F_Tag
{
   bitfield32_t P     :2;   // Bit [31:30]
   bitfield32_t ID    :6;   // Bit [29:24]
   bitfield32_t LEN   :8;   // Bit [23:16]
   bitfield32_t CSUM  :1;   // Bit 15
   bitfield32_t CSE   :1;   // Bit 14
   bitfield32_t CRC   :1;   // Bit 13
   bitfield32_t TD    :1;   // Bit 12
   bitfield32_t TO    :4;   // Bit 11:8
   bitfield32_t D     :8;   // Bit [0:7]

} SCI_LTR_F_T;

typedef union SCI_LTR_Tag
{
   SCI_LTR_F_T  F;
   uint8_t      U8[4];
   uint16_t     U16[2];
   uint32_t     U32;

} SCI_LTR_T;

//==============================================================================
// eSCI LIN Recieve Register (eSCIx_LRR)
// Addresses:   0xFFFB0014 (A)
//              0xFFFB4014 (B)
//              0xFFFB8014 (c)
// Size(byte):  2
// Reset value: 0x0000
// Field Descriptions:
//   Fields Bit(s) R/W Descriptions
//   D7..0  [0:7]   r  Data bits. Provides received data bytes from RX frames.
//                     It is only valid when the eSCIx_SR[RXRDY] flag is set.
//                     CRC and checksum information will not be available in the
//                     eSCIx_LRR unless they are treated as data. It is possible
//                     to treat CRC and checksum bytes as data by deactivating
//                     the CSUM respectively CRC control bits in the eSCIx_LTR
//                     register; however, then CRC and CSUM checking has to be
//                     performed by software.
//
//          [8:15]  r  reserved
//
//==============================================================================
typedef struct SCI_LRR_F_Tag
{
   bitfield32_t  D  :32;    // Data byte

} SCI_LRR_T;

//==============================================================================
// eSCI LIN CRC Polynom Register (eSCIx_LPR)
// Addresses:   0xFFFB0018 (A)
//              0xFFFB4018 (B)
//              0xFFFB8018 (C)
// Size(byte):  2
// Reset value: 0xC599
// Field Descriptions:
//   Fields Bit(s) R/W Descriptions
//   P15..0 [0:15] r/w Polynomial bit xn. Bits P15:P0 are used to define the LIN
//                     polynomial - standard is
//                     x15 + x14 + x10 + x8 + x7 + x4 + x3 + 1
//                     (the Polynomial used for the CAN protocol).
//
//==============================================================================
typedef struct SCI_LPR_F_Tag
{
   bitfield32_t  P     :16;
   bitfield32_t        :3;
   bitfield32_t  SYNM  :1;
   bitfield32_t  EROE  :1;
   bitfield32_t  ERFE  :1;
   bitfield32_t  ERPE  :1;
   bitfield32_t  M2    :1;
   bitfield32_t        :8;

} SCI_LPR_F_T;

typedef union SCI_LPR_Tag
{
   SCI_LPR_F_T  F;
   uint8_t      U8[4];
   uint16_t     U16[2];
   uint32_t     U32;

} SCI_LPR_T;

//==============================================================================
typedef volatile struct SCI_Tag
{
   SCI_CR1_T   CR1;              // 0x0000 - 0x0003 
   SCI_CR2_T   CR2;              // 0x0004 - 0x0005 
   SCI_DR_T    DR;               // 0x0006 - 0x0007 
   SCI_IFSR1_T   SR1;            // 0x0008 - 0x000B 
   SCI_LCR1_T  LCR1;             // 0x000C - 0x000F 
   SCI_LTR_T   LTR;              // 0x0010 - 0x0013 
   SCI_LRR_T   LRR;              // 0x0014 - 0x0017 
   SCI_LPR_T   LPR;              // 0x0018 - 0x001B 

} SCI_T;

#endif // HW_SCI_H#define ESCI_SR_OVFL_CLEAR_MASK     (0x00FD)
