#ifndef HW_DSPI_H
#define HW_DSPI_H

#include "reuse.h"


#define NUMBER_OF_DSPI_DEVICES    (   4)
#define DSPI_ARRAY_SIZE_2         (   2)

#define DSPI_CTA_QUANTITY         (   8)
#define DSPI_TRANSFER_QUANTITY    (  16)
#define DSPI_RECEIVE_QUANTITY     (  16)
#define DSPI_PISR_QUANTITY        (   4)
#define DSPI_RESERVED_4           (   4)

//w1c Bit Masks
#define DSPI_TCF_CLEAR_MASK       (0xA585FFFF)
#define DSPI_TXRXS_CLEAR_MASK     (0x6585FFFF)
#define DSPI_EOQF_CLEAR_MASK      (0x3585FFFF)
#define DSPI_TFUF_CLEAR_MASK      (0x2D85FFFF)
#define DSPI_TFFF_CLEAR_MASK      (0x2785FFFF)
#define DSPI_DPEF_CLEAR_MASK      (0x25C5FFFF)
#define DSPI_SPEF_CLEAR_MASK      (0x25A5FFFF)
#define DSPI_DDIF_CLEAR_MASK      (0x2595FFFF)
#define DSPI_RFOF_CLEAR_MASK      (0x258DFFFF)
#define DSPI_RFDF_CLEAR_MASK      (0x2587FFFF)


//=============================================================================
// ID - DSPI Module Configuration Register (DSPI_MCR)
//
// Base Offset : 0000 0000 H
//
// Reset Value : 0000 0001 H
//
// Field        Bits     Type Description
//============= ======== ==== ===============================================
// MSTR             31    rw  Master/slave mode select. The MSTR bit
//                            configures the DSPI for either Master Mode or
//                            Slave Mode.
//                                       1 DSPI is in Master Mode
//                                       0 DSPI is in Slave Mode
//
// CONT_SCKE        30    rw  Continuous SCK Enable. The CONT_SCKE bit
//                            enables the Serial Communication Clock (SCK)
//                            to run continuously.
//                                     1 Continuous SCK enabled
//                                     0 Continuous SCK disabled
//
// DCONF       [29:28]    rw  DSPI Configuration. The DCS field selects
//                            between the three different configurations of
//                            the DSPI. The table below lists the DCONF
//                            values for the various configurations.
//                                  DCONF         Configuration
//                                   00               SPI
//                                   01               DSI
//                                   10               CSI
//                                   11               Reserved
//
// FRZ              27    rw  Freeze.The FRZ bit enables the DSPI transfers
//                            to be stopped on the next frame boundary when
//                            the MPC5554 enters Debug Mode.
//                                   1 Halt serial transfers
//                                   0 Do not halt serial transfers
//
// MTFE             26    rw  Modified Timing Format Enable. The MTFE bit
//                            enables a modified transfer format to be used.
//                                   1 Modified SPI transfer format enabled
//                                   0 Modified SPI transfer format disabled
//
// PCSSE            25    rw  Peripheral Chip Select Strobe Enable.The PCSSE
//                            bit enables the PCS[5]/PCSS to operate as an
//                            PCS Strobe output signal.
//                                   1 PCS[5]/PCSS is used as an active-low
//                                     PCS Strobe signal
//                                   0 PCS[5]/PCSS is used as the Peripheral
//                                     Chip Select[5] signal
//
// ROOE             24    rw  Receive FIFO Overflow Overwrite Enable. The
//                            ROOE bit enables an RX FIFO overflow condition
//                            to either ignore the incoming serial data or
//                            to overwrite existing data. If the RX FIFO is
//                            full and new data is received, the data from
//                            the transfer that generated the overflow is
//                            either ignored or shifted in to the shift
//                            register. If the ROOE bit is asserted, the
//                            incoming  data is shifted in to the shift
//                            register. If the ROOE bit is negated, the
//                            incoming data is ignored.
//                                    1 Incoming data is shifted in to the
//                                      shift register
//                                    0 Incoming data is ignored
//
// PCSISx      [23:16]    rw  Peripheral Chip Select Inactive State. The
//                            PCSIS bit determines the inactive state of the
//                            PCSx signal.
//                                    1 The inactive state of PCSx is high
//                                    0 The inactive state of PCSx is low
//
// DOZE             15    rw  Doze Enable. The DOZE bit provides support for
//                            externally controlled Doze Mode power-saving
//                            mechanism.
//
// MDIS             14    rw  Module Disable. The MDIS bit allows the clock
//                            to be stopped to the non-memory mapped logic in
//                            the DSPI effectively putting the DSPI in a
//                            software controlled power-saving state. The
//                            reset value of the MDIS bit is parameterized,
//                            with a default reset value of ‘0’.
//                                     1 Allow external logic to disable
//                                       DSPI clocks.
//                                     0 Enable DSPI clocks.
//
// DIS_TXF          13    rw  Disable Transmit FIFO. The DIS_TXF bit provides
//                            a mechanism to disable the TX FIFO. When the
//                            TX FIFO is disabled, the transmit part of the
//                            DSPI operates as a simplified double-buffered
//                            SPI.
//                                     1 TX FIFO is disabled
//                                     0 TX FIFO is enabled
//
// DIS_RXF          12    rw  Disable Receive FIFO. The DIS_RXF bit provides
//                            a mechanism to disable the RX FIFO. When the
//                            RX FIFO is disabled, the receive part of the
//                            DSPI operates as a simplified double-buffered
//                            SPI.
//                                    1 RX FIFO is disabled
//                                    0 RX FIFO is enabled
//
// CLR_TXF          11    rw  Clear TX FIFO. CLR_TXF is used to flush the
//                            TX FIFO. Writing a ‘1’ to CLR_TXF clears the TX
//                            FIFO Counter. The CLR_TXF bit is always read as
//                            zero.
//                                    1 Clear the TX FIFO Counter
//                                    0 Do not clear the TX FIFO Counter
//
// CLR_RXF          10    rw  Clear RX FIFO. CLR_RXF is used to flush the RX
//                            FIFO. Writing a ‘1’ to CLR_RXF clears the RX
//                            Counter.The CLR_RXF bit is always read as zero.
//                                    1 Clear the RX FIFO Counter
//                                    0 Do not clear the RX FIFO Counter
//
// SMPL_PT       [9:8]    rw  Sample Point.SMPL_PT allows the host software
//                            to select when the DSPI Master samples SIN in
//                            Modified Transfer Format.The table below lists
//                            the various delayed sample points.
//
//                           SMPL_PT            Number of system clock cycles
//                                          between odd-numbered edge of SCK
//                                               and sampling of SIN.
//                              00                          0
//                              01                          1
//                              10                          2
//                              11                          Reserved
//
// 0             [7:2]     r  Reserved, should be cleared.
//
// PES               1    rw  Parity Error Stop. PES bit controls SPI operation 
//                            when a parity error detected in received SPI frame.
//                                    0 SPI frames transmission continue.
//                                    1 SPI frames transmission stop.
//
// HALT              0    rw  Halt. The HALT bit provides a mechanism for
//                            software to start and stop DSPI transfers.
//                                          1 Stop transfers
//                                          0 Start transfers
//
//
// Note: The Bit      numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef volatile struct DSPI_MCR_F_Tag
{
   bitfield32_t  MSTR      :  BIT_1;  // Bit      31
   bitfield32_t  CONT_SCKE :  BIT_1;  // Bit      30
   bitfield32_t  DCONF     :  BIT_2;  // Bits [29:28]
   bitfield32_t  FRZ       :  BIT_1;  // Bit      27
   bitfield32_t  MTFE      :  BIT_1;  // Bit      26
   bitfield32_t  PCSSE     :  BIT_1;  // Bit      25
   bitfield32_t  ROOE      :  BIT_1;  // Bit      24
   bitfield32_t  PCSISx    :  BIT_8;  // Bits [21:16]
   bitfield32_t  DOZE      :  BIT_1;  // Bit      15
   bitfield32_t  MDIS      :  BIT_1;  // Bit      14
   bitfield32_t  DIS_TXF   :  BIT_1;  // Bit      13
   bitfield32_t  DIS_RXF   :  BIT_1;  // Bit      12
   bitfield32_t  CLR_TXF   :  BIT_1;  // Bit      11
   bitfield32_t  CLR_RXF   :  BIT_1;  // Bit      10
   bitfield32_t  SMPL_PT   :  BIT_2;  // Bits [ 9: 8]
   bitfield32_t            :  BIT_5;  // Bits [ 7:3]
   bitfield32_t  FCPCS :  BIT_1;  // Bit       2
   bitfield32_t  PES       :  BIT_1;  // Bit       1
   bitfield32_t  HALT      :  BIT_1;  // Bit       0

}  DSPI_MCR_F_T;

typedef volatile union DSPI_MCR_Tag
{
   DSPI_MCR_F_T         F;
   uint32_t             U32;

}  DSPI_MCR_T;

//=============================================================================
// ID - DSPI Hardware Configuration Register (DSPI_HCR)
//
// Base Offset : 0000 0004 H
//
// Reset Value : xxxx 0000 H
//
// Field        Bits     Type Description
//============= ======== ==== ===============================================
// DSI            31      r   DSI features are implemented for the module.
//                            0 - DSI features are not implemented, DSI 
//                            registers don’t exist.
//                            1 - DSI features are implemented
//
// PISR           30      r   PISR, PISR0-3 and parallel inputs frame 
//                            positions selection logic are implemented for
//                            the module.
//                            0 - DSPI_PISR0-3 registers are not implemented.
//                            1 - DSPI_PISR0-3 registers are implemented
//
//             [29:27]    r   Reserved, should be cleared.
//
// CTAR        [26:24]    r   CTAR, Maximum implemented DSPI_CTAR register
//                            number.
//
// TXFR        [23:20]    r   TXFR, Maximum implemented DSPI_TXFR register
//                            number.
//
// RXFR        [19:16]    r   RXFR, Maximum implemented DSPI_RXFR register
//                            number.
//
// 0           [15:0]     r   Reserved, should be cleared.
//
// Note: The Bit      numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef volatile struct DSPI_HCR_F_Tag
{
   bitfield32_t  DSI       :  BIT_1;  // Bit      31
   bitfield32_t  PISR      :  BIT_1;  // Bit      30
   bitfield32_t            :  BIT_3;  // Bits [29:27]
   bitfield32_t  CTAR      :  BIT_3;  // Bits [26:24]
   bitfield32_t  TXFR      :  BIT_4;  // Bits [23:20]
   bitfield32_t  RXFR      :  BIT_4;  // Bits [19:16]
   bitfield32_t            :  BIT_16; // Bits [15:0]

}  DSPI_HCR_F_T;

typedef volatile union DSPI_HCR_Tag
{
   DSPI_HCR_F_T         F;
   uint32_t             U32;

}  DSPI_HCR_T;

//=============================================================================
// ID - DSPI Transfer Count Register (DSPI_TCR)
// Base Offset : 0000 0008H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// SPI_TCNT    [31:16]    rw  SPI Transfer Counter.TCNT is used to keep
//                            track of the number of SPI transfers made.
//                            The TCNT field counts the number of SPI
//                            transfers the DSPI makes. The TCNT field is
//                            incremented every time the last bit of a SPI
//                            frame is transmitted. A value written to
//                            TCNT presets the counter to that value.
//                            TCNT is reset to zero at the beginning of
//                            the frame when the CTCNT field is set in the
//                            executing SPI command. The Transfer Counter
//                            ‘wraps around’ i.e. incrementing the counter
//                            past 65535 resets the counter to zero..
//
// 0           [15:0 ]     r  Reserved, should be cleared.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef volatile struct DSPI_TCR_F_Tag
{
   bitfield32_t  TCNT :  BIT_16;  // Bits [31:16]
   bitfield32_t       :  BIT_16;  // Bits [15: 0] are reserved

}  DSPI_TCR_F_T;

typedef volatile union DSPI_TCR_Tag
{
   DSPI_TCR_F_T            F;
   uint16_t                U16[DSPI_ARRAY_SIZE_2];
   uint32_t                U32;

}  DSPI_TCR_T;

//=============================================================================
// ID - DSPI Clock and Transfer Attributes Registers 0-7(DSPI_CTARn)
// Base Offset : 0000 000CH to 0000 0028H
//
// Reset Value : 7800 0000H
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// DBR             31     rw  The DBR bit doubles the effective baud rate of 
//                            the Serial Communications Clock (SCK). This field 
//                            is only used in master mode. It effectively 
//                            halves the Baud Rate division ratio supporting 
//                            faster frequencies and odd division ratios for 
//                            the Serial Communications Clock (SCK). When the 
//                            DBR bit is set, the duty cycle of the Serial 
//                            Communications Clock (SCK) depends on the value 
//                            in the Baud Rate Prescaler and the Clock Phase bit.
//                                    0 The baud rate is computed normally 
//                                      with a 50/50 duty cycle
//                                    1 The baud rate is doubled with the duty 
//                                      cycle depending on the Baud Rate Prescaler
//
// FMSZ        [30:27]    rw  FMSZ. The FMSZ field selects the number of bits
//                            transferred per frame. The FMSZ field is used
//                            in Master Mode and Slave Mode. The table below
//                            lists the frame sizes. FMSZ Framesize
//
//                             FMSZ     Framesize     FMSZ     Framesize
//
//                             0000     Reserved      1000        9
//                             0001     Reserved      1001        10
//                             0010     Reserved      1010        11
//                             0011     4             1011        12
//                             0100     5             1100        13
//                             0101     6             1101        14
//                             0110     7             1110        15
//                             0111     8             1111        16
//
// CPOL             26    rw  Clock Polarity. The CPOL bit selects the
//                            inactive state of the Serial Communications
//                            Clock (SCK). This bit is used in both Master
//                            and Slave Mode. For successful communication
//                            between serial devices, the devices must have
//                            identical clock polarities. When the continuous
//                            selection format is selected (CONT = 1 or
//                            DCONT = 1), switching between clock polarities
//                            without stopping the DSPI can cause errors in
//                            the transfer due to the peripheral device
//                            interpreting the switch of clock polarity as a
//                            valid clock edge.
//                                1 The inactive state value of SCK is high
//                                0 The inactive state value of SCK is low
//
// CPHA             25    rw  Clock Phase. The CPHA bit selects which edge of
//                            SCK causes data to change and which edge causes
//                            data to be captured. This bit is used in both
//                            Master and Slave Mode. For successful
//                            communication between serial devices, the
//                            devices must have identical clock phase
//                            settings.
//                                 1 Data is changed on the leading edge of
//                                   SCK and captured on the following edge
//                                 0 Data is captured on the leading edge of
//                                   SCK  and changed on the following edge
//
// LSBFE            24    rw  LSB First Enable. The LSBFE bit selects if the
//                            LSB or MSB of the frame is transferred first.
//                            This bit is only used in Master Mode.
//                                 1 Data is transferred LSB first
//                                 0 Data is transferred MSB first
//
// PCSSCK      [23:22]    rw  PCS to SCK Delay Prescaler. The PCSSCK field
//                            selects the prescaler value for the delay
//                            between assertion of PCS and the first edge of
//                            the SCK.This field is only used in Master Mode.
//                            The table below lists the prescaler values.
//
//                               PCSSCK       PCS to SCK Delay
//                                             Prescaler Value
//                                 00               1
//                                 01               3
//                                 10               5
//                                 11               7
//
// PASC        [21:20]    rw  After SCK Delay Prescaler. The PASC field
//                            selects the prescaler value for the delay
//                            between the last edge of SCK and the negation
//                            of PCS. This field is only used in Master Mode.
//                            The table below lists the prescaler values.
//
//                               PASC       After SCK Delay
//                                           Prescaler Value
//                                 00               1
//                                 01               3
//                                 10               5
//                                 11               7
//
// PDT         [19:18]    rw  Delay after Transfer Prescaler. The PDT field
//                            selects the prescaler value for the delay
//                            between the negation of the PCS signal at the
//                            end of a frame and the assertion of PCS at the
//                            beginning of the next frame. The PDT field is
//                            only used in Master Mode. The table below lists
//                            the prescaler values.
//
//                                PDT       Delay after Transfer
//                                           Prescaler Value
//                                 00               1
//                                 01               3
//                                 10               5
//                                 11               7
//
// PBR         [17:16]    rw  Baud Rate Prescaler. The PBR field selects the
//                            prescaler value for the baud rate. This field
//                            is only used in Master Mode. The Baud Rate is
//                            the frequency of the Serial Communications
//                            Clock (SCK). The system clock is divided by the
//                            prescaler value before the baud rate selection
//                            takes place. The Baud Rate Prescaler values are
//                            listed in the table below.
//
//                                 PBR       Baud Rate
//                                           Prescaler Value
//                                 00               2
//                                 01               3
//                                 10               5
//                                 11               7
//
// CSSCK       [15:12]    rw  PCS to SCK Delay Scaler. The CSSCK field
//                            selects the scaler value for the PCS to SCK
//                            delay. This field is only used in Master Mode.
//                            The PCS to SCK Delay is the delay between the
//                            assertion of PCS and the first edge of the SCK.
//                            The table below lists the scaler values.
//
//                             CSSCK    PCS to SCK     CSSCK     PCS to SCK
//                                   Delay scaler val        Delay scaler val
//
//                             0000     2             1000        512
//                             0001     4             1001        1024
//                             0010     8             1010        2048
//                             0011     16            1011        4096
//                             0100     32            1100        8192
//                             0101     64            1101        16384
//                             0110     128           1110        32768
//                             0111     256           1111        65536
//
//                            The PCS to SCK Delay is a multiple of the
//                            system clock period and it is computed
//                            according to the following equation:
//
//                                 tCSC = 1/ fsys * PCSSCK * CSSCK
//
// ASC          [11:8]    rw  After SCK Delay Scaler. The ASC field selects
//                            the scaler value for the After SCK Delay. This
//                            field is only used in Master Mode. The After
//                            SCK Delay is the delay between the last edge of
//                            SCK and the negation of PCS. The table below
//                            lists the scaler values.
//
//                             ASC   After SCK         ASC     After  SCK
//                                   Delay scaler val        Delay scaler val
//
//                             0000     2             1000        512
//                             0001     4             1001        1024
//                             0010     8             1010        2048
//                             0011     16            1011        4096
//                             0100     32            1100        8192
//                             0101     64            1101        16384
//                             0110     128           1110        32768
//                             0111     256           1111        65536
//
//                            The After SCK Delay is a multiple of the system
//                            clock period, and it is computed according
//                            to the following equation:
//
//                                 tASC = 1/ fsys * PASC * ASC
//
// DT            [7:4]    rw  Delay after Transfer Scaler. The DT field
//                            selects the Delay after Transfer Scaler. This
//                            field is only used in Master Mode. The Delay
//                            after Transfer is the time between the
//                            negation of the PCS signal at the end of a
//                            frame and the assertion of PCS at the beginning
//                            of the next frame. The table below lists the
//                            scaler values.
//
//                             DT   Delay  After       DT    Delay After
//                                  Transfer scaler         Transfer scaler
//                                     Val                        Val
//                             0000     2             1000        512
//                             0001     4             1001        1024
//                             0010     8             1010        2048
//                             0011     16            1011        4096
//                             0100     32            1100        8192
//                             0101     64            1101        16384
//                             0110     128           1110        32768
//                             0111     256           1111        65536
//
//                            The Delay after Transfer is a multiple of the
//                            system clock period and it is computed
//                            according to the following equation:
//
//                                       DT = 1/ fsys * PDT * DT
//
// BR            [3:0]    rw  Baud Rate Scaler. The BR field selects the
//                            scaler value for the baud rate. This field is
//                            only used in Master Mode. The pre-scaled system
//                            clock is divided by the Baud Rate Scaler to
//                            generate the frequency of the SCK. The table
//                            below lists the Baud Rate Scaler values.
//
//                             BR   Baud Rate Scaler   BR   Baud Rate Scaler
//                                      Value                   value
//                            0000          2         1000      256
//                            0001          4         1001      512
//                            0010          6         1010      1024
//                            0011          8         1011      2048
//                            0100          16        1100      4096
//                            0101          32        1101      8192
//                            0110          64        1110      16384
//                            0111          128       1111      32768
//
//                            The baud rate is computed according to the
//                            following equation:
//
//                             SCK baud rate = fsys/PBR * 1 / BR
//
//
//=============================================================================
// ID - DSPI Clock and Transfer Attributes Registers 0(DSPI_CTAR0)
// Base Offset : 0000 000CH 
//
// Reset Value : 7800 0000H
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// FMSZ         31-27   rw  Frame Size. The number of bits transferred per 
//                          frame is equal FMSZ field value plus 1. Minimum 
//                          valid FMSZ field value is 3
//
// CPOL           26    rw  Clock Polarity. The CPOL bit selects the inactive 
//                          state of the Serial Communications Clock (SCK).
//                          0 The inactive state value of SCK is low
//                          1 The inactive state value of SCK is high
//
// CPHA           25    rw  Clock Phase. The CPHA bit selects which edge of 
//                          SCK causes data to change and which edge causes 
//                          data to be captured.
//                          0 Data is captured on the leading edge of SCK and 
//                            changed on the following edge
//                          1 Data is changed on the leading edge of SCK and
//                            captured on the following edge
//
// PE             24      rw  Parity Enable. PE bit enables parity bit 
//                            transmission and reception for the frame
//                            0 No parity bit included/checked.
//                            1 Parity bit is transmitted instead of last 
//                              data bit in frame, parity checked for 
//                              received frame
//
// PP             23     rw  Parity Polarity. PP bit controls polarity of the
//                           parity bit transmitted and checked
//                           0 Even Parity: number of “1” bits in the transmitted 
//                             frame is even. The DSPI_SR[SPEF] bit is set if in 
//                             the received frame number of “1” bits is odd.
//                           1 Odd Parity: number of “1” bits in the transmitted
//                             frame is odd. The DSPI_SR[SPEF] bit is set if in
//                             the received frame number of “1” bits is even.
//
// 0              0-22   r  Reserved
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef volatile struct DSPI_CTAR_F_Tag
{
   bitfield32_t   DBR       :  BIT_1;  // Bit      31 is reserved
   bitfield32_t   FMSZ      :  BIT_4;  // Bits [30:27]
   bitfield32_t   CPOL      :  BIT_1;  // Bit      26
   bitfield32_t   CPHA      :  BIT_1;  // Bit      25
   bitfield32_t   LSBFE     :  BIT_1;  // Bit      24
   bitfield32_t   PCSSCK    :  BIT_2;  // Bits [23:22]
   bitfield32_t   PASC      :  BIT_2;  // Bits [21:20]
   bitfield32_t   PDT       :  BIT_2;  // Bits [19:18]
   bitfield32_t   PBR       :  BIT_2;  // Bits [17:16]
   bitfield32_t   CSSCK     :  BIT_4;  // Bits [15:12]
   bitfield32_t   ASC       :  BIT_4;  // Bits [11: 8]
   bitfield32_t   DT        :  BIT_4;  // Bits [ 7: 4]
   bitfield32_t   BR        :  BIT_4;  // Bits [ 3: 0]

}  DSPI_CTAR_F_T;

typedef volatile struct DSPI_CTAR0_SLAVE_F_Tag
{
   bitfield32_t   FMSZ      :  BIT_5;  // Bits [31:27]
   bitfield32_t   CPOL      :  BIT_1;  // Bit    26
   bitfield32_t   CPHA      :  BIT_1;  // Bit    25
   bitfield32_t   PE        :  BIT_1;  // Bit    24
   bitfield32_t   PP        :  BIT_1;  // Bit    23
   bitfield32_t             :  BIT_23;  // Bits [ 22: 0]

}  DSPI_CTAR0_SLAVE_F_T;

typedef volatile union DSPI_CTAR_Tag
{
   DSPI_CTAR_F_T            F;
   DSPI_CTAR0_SLAVE_F_T     F1;
   uint32_t                U32;

}  DSPI_CTAR_T;

//=============================================================================
// ID - DSPI Status Register (DSPI_SR)
// Base Offset : 0000 002CH
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// =========  ========== ==== ===============================================
// TCF              31    rw  Transfer Complete Flag. The TCF bit indicates
//                            that all bits in a frame have been shifted
//                            out. The TCF bit is set at the end of the frame
//                            transfer. The TCF bit remains set until
//                            cleared by software.
//                                 1       Transfer complete
//                                 0       Transfer not complete
//
// TXRXS            30    rw  TX & RX Status. The TXRXS bit reflects the
//                            status of the DSPI.
//                                1 TX and RX operations are enabled
//                                  (DSPI is in RUNNING state)
//                                0 TX and RX operations are disabled
//                                  (DSPI is in STOPPED state)
//
// 0                29     r  Reserved, should be cleared
//
// EOQF             28    rw  End of Queue Flag. The EOQF bit indicates that
//                            transmission in progress is the last entry
//                            in a queue. The EOQF bit is set when TX FIFO
//                            entry has the EOQ bit set in the command
//                            halfword and the end of the transfer is reached
//                            The EOQF bit remains set until cleared by
//                            software. When the EOQF bit is set, the TXRXS
//                            bit is automatically cleared.
//
//                            1 EOQ bit is set  in the executing SPI command
//                            0 EOQ is not set  in the executing command.
//
// TFUF             27    rw  Transmit FIFO Underflow Flag. The TFUF bit
//                            indicates that an underflow condition in the
//                            TX FIFO has occurred. The transmit underflow
//                            condition is detected only for DSPI blocks
//                            operating in slave mode and SPI configuration.
//                            The TFUF bit is set when the TX FIFO of a DSPI
//                            operating in SPI slave mode is empty, and a
//                            transfer is initiated by an external SPI
//                            master. The TFUF bit remains set until cleared
//                            by software.
//
//                                  1 TX FIFO underflow has occurred
//                                  0 TX FIFO underflow has not occurred
//
// 0                26     r  Reserved, should be cleared.
//
// TFFF             25    rw  Transmit FIFO Fill Flag. The TFFF bit provides
//                            a method for the DSPI to request more entries
//                            to be added to the TX FIFO. The TFFF bit is set
//                            while the TX FIFO is not full. The TFFF bit can
//                            be cleared by host software or an
//                            acknowledgement from the DMA controller when
//                            the TX FIFO is full.
//
//                                   1 TX FIFO is not full
//                                   0 TX FIFO is full
//
// 0           [24:23]     r  Reserved, should be cleared.
//
// DPEF             22    rw  DSI Parity Error Flag. The DPEF flag indicates 
//                            that a DSI frame with parity error had been 
//                            received. The bit remains set until cleared by 
//                            writing 1 to it.
//                                   0 Parity Error has not occurred
//                                   1 Parity Error has occurred
//
// SPEF             21    rw  SPI Parity Error Flag. The SPEF flag indicates 
//                            that a SPI frame with parity error had been 
//                            received. The bit remains set until cleared by 
//                            writing 1 to it.
//                                   0 Parity Error has not occurred
//                                   1 Parity Error has occurred
//
// DDIF             20    rw  DSI data received with active bits. The DDIF flag 
//                            indicates that DSI frame had been received with
//                            bits, selected by DSPI_DIMR with active polarity,
//                            defined by DSPI_DPIR register. The bit remains set
//                            until cleared by writing 1 to it.
//                                   0 No DSI data with active bits was received
//                                   1 DSI data with active bits was received
//
// RFOF             19    rw  Receive FIFO Overflow Flag. The RFOF bit
//                            indicates that an overflow condition in the RX
//                            FIFO has occurred. The bit is set when the RX
//                            FIFO and shift register are full and a transfer
//                            is initiated. The bit remains set until cleared
//                            by software.
//
//                                   1 RX FIFO overflow has occurred
//                                   0 RX FIFO overflow has not occurred
//
// 0                18     r  Reserved, should be cleared.
//
// RFDF             17    rw  Receive FIFO Drain Flag. The RFDF bit provides
//                            a method for the DSPI to request that entries
//                            be removed from the RX FIFO. The bit is set
//                            while the RX FIFO is not empty. The RFDF bit
//                            can be cleared by host software or an
//                            acknowledgement from the DMA controller when
//                            the RX FIFO is empty.
//
//                                    1 RX FIFO is not empty
//                                    0 RX FIFO is empty
//
// 0                16     r  Reserved, should be cleared.
//
// TXCTR       [15:12]     r  TX FIFO Counter. The TXCTR field indicates the
//                            number of valid entries in the TX FIFO.
//                            The TXCTR is incremented every time the
//                            DSPI _PUSHR is written. The TXCTR is
//                            decremented every time a SPI command is
//                            executed and the SPI data is transferred to the
//                            shift register.
//
// TXNXTPTR     [11:8]     r  Transmit Next Pointer. The TXNXTPTR field
//                            indicates which TX FIFO Entry will be
//                            transmitted during the next transfer. The
//                            TXNXTPTR field is updated every time SPI data
//                            is transferred from the TX FIFO to the shift
//                            register.
//
// RXCTR         [7:4]     r  RX FIFO Counter. The RXCTR field indicates the
//                            number of entries in the RX FIFO. The RXCTR is
//                            decremented every time the DSPI _POPR is read.
//                            The RXCTR is incremented every time data is
//                            transferred from the shift register to the RX
//                            FIFO.
//
// POPNXTPTR     [3:0]     r  Pop Next Pointer. The POPNXTPTR field contains
//                            a pointer to the RX FIFO entry that will be
//                            returned when the DSPI_POPR is read. The
//                            POPNXTPTR is updated when the DSPI_POPR is
//                            read.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef volatile struct DSPI_SR_F_Tag
{
   bitfield32_t   TCF       :  BIT_1;  // Bit      31
   bitfield32_t   TXRXS     :  BIT_1;  // Bit      30
   bitfield32_t             :  BIT_1;  // Bit      29 is reserved
   bitfield32_t   EOQF      :  BIT_1;  // Bit      28
   bitfield32_t   TFUF      :  BIT_1;  // Bit      27
   bitfield32_t             :  BIT_1;  // Bit      26 is reserved
   bitfield32_t   TFFF      :  BIT_1;  // Bit      25
   bitfield32_t             :  BIT_2;  // Bits [24:23] are reserved
   bitfield32_t   DPEF      :  BIT_1;  // Bit      22
   bitfield32_t   SPEF      :  BIT_1;  // Bit      21
   bitfield32_t   DDIF      :  BIT_1;  // Bit      20
   bitfield32_t   RFOF      :  BIT_1;  // Bit      19
   bitfield32_t             :  BIT_1;  // Bit      18 is reserved
   bitfield32_t   RFDF      :  BIT_1;  // Bit      17
   bitfield32_t             :  BIT_1;  // Bit      16 is reserved
   bitfield32_t   TXCTR     :  BIT_4;  // Bits [15:12]
   bitfield32_t   TXNXTPTR  :  BIT_4;  // Bits [11: 8]
   bitfield32_t   RXCTR     :  BIT_4;  // Bits [ 7: 4]
   bitfield32_t   POPNXTPTR :  BIT_4;  // Bits [ 3: 0]

}  DSPI_SR_F_T;

typedef volatile union DSPI_SR_Tag
{
   DSPI_SR_F_T            F;
   uint32_t             U32;

}  DSPI_SR_T;

//=============================================================================
// ID - DSPI DMA/Interrupt Request Select and Enable Register (DSPI_RSER)
// Base Offset : 0000 0030H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ========== ========== ==== ===============================================
// TCF_RE           31    rw  Transmission Complete Request Enable. The
//                            TCF_RE bit enables TCF flag in the DSPI_SR to
//                            generate an interrupt request.
//
//                               1 TCF interrupt requests are enabled
//                               0 TCF interrupt requests are disabled
//
// 0           [30:29]     r  Reserved, should be cleared.
//
// EOQF_RE          28    rw  DSPI Finished Request Enable. The EOQF_RE bit
//                            enables the EOQF flag in the DSPI_SR to
//                            generate an interrupt request.
//
//                               1 EOQF interrupt requests are enabled
//                               0 EOQF interrupt requests are disabled
//
// TFUF_RE          27    rw  Transmit FIFO Underflow Request Enable.The
//                            TFUF_RE bit enables the TFUF flag in the
//                            DSPI_SR to generate an interrupt request.
//
//                                1 TFUF interrupt requests are enabled
//                                0 TFUF interrupt requests are disabled
//
// 0                26     r  Reserved, should be cleared.
//
// TFFF_RE          25    rw  Transmit FIFO Fill Request Enable. The TFFF_RE
//                            bit enables the TFFF flag in the DSPI_SR to
//                            generate a request. The TFFF_DIRS bit selects
//                            between generating an interrupt request or a
//                            DMA requests.
//
//                                 1 TFFF interrupt requests or DMA requests
//                                   are enabled
//                                 0 TFFF interrupt requests or DMA requests
//                                   are disabled
//
// TFFF_DIRS        24    rw  Transmit FIFO Fill DMA or Interrupt Request
//                            Select. The TFFF_DIRS bit selects between
//                            generating a DMA request or an interrupt
//                            request. When the TFFF flag bit in the DSPI_SR
//                            is set, and the TFFF_RE bit in the DSPI_RSER
//                            register is set, this bit selects between
//                            generating an interrupt request or a DMA
//                            request.
//
//                                 1 DMA request will be generated
//                                 0 Interrupt request will be generated
//
// 0                23     r  Reserved, should be cleared.
//
// DPEF_RE          22    rw  DSI Parity Error Request Enable. The DPEF_RE
//                            bits enables DPEF flag in the DSPI_SR to generate
//                            an interrupt requests.
//                            0 DPEF interrupt requests are disabled
//                            1 DPEF interrupt requests are enabled
//
// SPEF_RE          21    rw  SPI Parity Error Request Enable. The SPEF_RE
//                            bits enables SPEF flag in the DSPI_SR to 
//                            generate an interrupt requests.
//                            0 SPEF interrupt requests are disabled
//                            1 SPEF interrupt requests are enabled
//
// DDIF_RE          20    rw  DSI data received with active bits Request 
//                            Enable. The DDIF_RE bit enables the DDIF flag
//                            in the DSPI_SR to generate an interrupt requests
//                            0 DDIF interrupt requests are disabled
//                            1 DDIF interrupt requests are enabled
//
// RFOF_RE          19    rw  Receive FIFO Overflow Request Enable. The
//                            RFOF_RE bit enables the RFOF flag in the
//                            DSPI_SR to generate an interrupt requests.
//
//                                 1 RFOF interrupt requests are enabled
//                                 0 RFOF interrupt requests are disabled
//
// 0                18     r  Reserved, should be cleared.
//
// RFDF_RE          17    rw  Receive FIFO Drain Request Enable. The RFDF_RE
//                            bit enables the RFDF flag in the DSPI_SR to
//                            generate a request. The RFDF_DIRS bit selects
//                            between generating an interrupt request or a
//                            DMA request.
//
//                                 1 RFDF interrupt requests or DMA requests
//                                   are enabled
//                                 0 RFDF interrupt requests or DMA requests
//                                   are disabled
//
// RFDF_DIRS        16    rw  Receive FIFO Drain DMA or Interrupt Request
//                            Select. The RFDF_DIRS bit selects between
//                            generating a DMA request or an interrupt
//                            request. When the RFDF flag bit in the
//                            DSPI_SR is set, and the RFDF_RE bit in the
//                            DSPI_RSER register is set, the RFDF_DIRS bit
//                            selects between generating an interrupt
//                            request or a DMA request.
//
//                                 1 DMA request will be generated
//                                 0 Interrupt request will be generated
//
// 0            [15: 0]     r  Reserved, should be cleared.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

 typedef volatile struct DSPI_RSER_F_Tag
{
   bitfield32_t   TCF_RE    :  BIT_1;  // Bit      31
   bitfield32_t   DSITCF_RE :  BIT_1; // Bit      30
   bitfield32_t             :  BIT_1;  // Bitd [29] are reserved
   bitfield32_t   EOQF_RE   :  BIT_1;  // Bit      28
   bitfield32_t   TFUF_RE   :  BIT_1;  // Bit      27
   bitfield32_t   SPITCF_RE         :  BIT_1;  // Bit      26 is reserved
   bitfield32_t   TFFF_RE   :  BIT_1;  // Bit      25
   bitfield32_t   TFFF_DIRS :  BIT_1;  // Bit      24
   bitfield32_t             :  BIT_1;  // Bit      23
   bitfield32_t   DPEF_RE   :  BIT_1;  // Bit      22
   bitfield32_t   SPEF_RE   :  BIT_1;  // Bit      21
   bitfield32_t   DDIF_RE   :  BIT_1;  // Bit      20
   bitfield32_t   RFOF_RE   :  BIT_1;  // Bit      19
   bitfield32_t             :  BIT_1;  // Bit      18 is reserved
   bitfield32_t   RFDF_RE   :  BIT_1;  // Bit      17
   bitfield32_t   RFDF_DIRS :  BIT_1;  // Bit      16
   bitfield32_t             :  BIT_16; // Bits [15: 0] are reserved

}  DSPI_RSER_F_T;

typedef volatile union DSPI_RSER_Tag
{
   DSPI_RSER_F_T          F;
   uint32_t             U32;

}  DSPI_RSER_T;

//=============================================================================
// ID - DSPI PUSH TX FIFO Register (DSPI_PUSHR)
// Base Offset : 0000 0034H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ======== ============ ==== ===============================================
// CONT             31    rw  Continuous Peripheral Chip Select Enable.The
//                            CONT bit selects a Continuous Selection
//                            Format. The bit is used in SPI Master Mode. The
//                            bit enables the selected PCS signals to remain
//                            asserted between transfers.
//
//                               1 Keep Peripheral Chip Select signals
//                                 asserted between transfers
//                               0 Return Peripheral Chip Select signals
//                                 to their inactive state between transfers
//
// CTAS        [30:28]    rw  Clock and Transfer Attributes Select. The CTAS
//                            field selects which of the DSPI_CTAR register
//                            is used to set the transfer attributes for the
//                            associated SPI frame. The field is only used in
//                            SPI Master Mode. In SPI Slave Mode DSPI_CTAR0
//                            is used. The table below shows how the CTAS
//                            values map to the DSPI_CTAR registers. There
//                            are eight DSPI_CTAR registers in the MPC5554
//                            DSPI implementation.
//
//                                 CTAS           Use Clock and Transfer
//                                                   Attributes from
//
//                                 000                DSPI_CTAR0
//                                 001                DSPI_CTAR1
//                                 010                DSPI_CTAR2
//                                 011                DSPI_CTAR3
//                                 100                DSPI_CTAR4
//                                 101                DSPI_CTAR5
//                                 110                DSPI_CTAR6
//                                 111                DSPI_CTAR7
//
// EOQ              27    rw  End Of Queue. The EOQ bit provides a means for
//                            Host software to signal to the DSPI that the
//                            current SPI transfer is the last in a queue.
//                            At the end of the transfer the EOQF bit in the
//                            DSPI_SR is set.
//
//                                1 The SPI data is the last data to transfer
//                                0 The SPI data is not the last data to
//                                  transfer
//
// CTCNT            26    rw  Clear TCNT. The CTCNT provides a means for
//                            Host software to clear the SPI transfer
//                            counter. The CTCNT bit clears the TCNT
//                            field in the DSPI_TCR register. The TCNT
//                            field is cleared before transmission of the
//                            current SPI frame begins.
//
//                                1 Clear TCNT field in the DSPI_TCR
//                                0 Do not clear TCNT field in the
//                                  DSPI_TCR
//
// PE               25    rw  Parity Enable. PE bit enables parity bit 
//                            transmission and parity reception check for the
//                            SPI frame
//                            0 No parity bit included/checked.
//                            1 Parity bit is transmitted instead of last data
//                            bit in frame, parity checked for received frame.
//
// PP               24    rw  Parity Polarity. PP bit controls polarity of the
//                            parity bit transmitted and checked
//                            0 Even Parity: number of “1” bits in the 
//                            transmitted frame is even. The DSPI_SR[SPEF] bit
//                            is set if in the received frame number of “1” 
//                            bits is odd.
//                            1 Odd Parity: number of “1” bits in the 
//                            transmitted frame is odd. The DSPI_SR[SPEF] bit
//                            is set if in the received frame number of “1” 
//                            bits is even.
//
// PCSx        [23:16]    rw  Peripheral Chip Select 0 - 5.The PCS bits
//                            select which PCS signals will be asserted for
//                            the transfer.
//                                 1 Assert the PCS[x] signal
//                                 0 Negate the PCS[x] signal
//
// TXDATA       [15: 0]    rw  Transmit Data. The TXDATA field holds SPI data
//                            to be transferred according to the associated
//                            SPI command.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef volatile struct DSPI_PUSHR_F_Tag
{
   bitfield32_t   CONT      :  BIT_1;  // Bit      31
   bitfield32_t   CTAS      :  BIT_3;  // Bits [30:28]
   bitfield32_t   EOQ       :  BIT_1;  // Bit      27
   bitfield32_t   CTCNT     :  BIT_1;  // Bit      26
   bitfield32_t   PE        :  BIT_1;  // Bits     25
   bitfield32_t   PP        :  BIT_1;  // Bits     24
   bitfield32_t   PCSx      :  BIT_8;  // Bits [21:16]
   bitfield32_t   TXDATA    :  BIT_16; // Bits [15: 0]

}  DSPI_PUSHR_F_T;

typedef volatile union DSPI_PUSHR_Tag
{
   DSPI_PUSHR_F_T        F;
   uint16_t              U16[DSPI_ARRAY_SIZE_2];
   uint32_t              U32;

}  DSPI_PUSHR_T;

//=============================================================================
// ID - DSPI POP RX FIFO Register (DSPI_POPR)
// Base Offset : 0000 0038H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type  Description
//========  =========== ===== ===============================================
// RXDATA       [31: 0]     r  Received Data. The RXDATA field contains the
//                            SPI data from the RX FIFO entry pointed to by
//                            the Pop Next Data Pointer.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef volatile struct DSPI_POPR_F_Tag
{
   uint32_t   RXDATA;      // Bits [31: 0]

}  DSPI_POPR_F_T;

typedef volatile union DSPI_POPR_Tag
{
   DSPI_POPR_F_T          F;
   uint32_t             U32;

}  DSPI_POPR_T;

//=============================================================================
// ID - DSPI Transmit FIFO Registers 0-3 (DSPI_TXFRn)
// Base Offset : 0000 003CH to 0000 0078H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type  Description
// =======  ===========  ==== ===============================================
// TXCMD       [31:16]     r  Transmit Command. The TXCMD field contains the
//                            command that sets the transfer attributes for
//                            the SPI data.
//
// TXDATA       [15: 0]     r  Transmit Data. The TXDATA field contains the
//                            SPI data to be shifted out.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_TXFR_F_Tag
{
   bitfield32_t   TXCMD     :  BIT_16;  // Bits [31:16]
   bitfield32_t   TXDATA    :  BIT_16;  // Bits [15: 0]

}  DSPI_TXFR_F_T;

typedef volatile union DSPI_TXFR_Tag
{
   DSPI_TXFR_F_T        F;
   uint16_t             U16[DSPI_ARRAY_SIZE_2];
   uint32_t             U32;

}  DSPI_TXFR_T;


//=============================================================================
// ID - DSPI Receive FIFO Registers 0-3 (DSPI_RXFRn)
// Base Offset : 0000 007CH to 0000 00B8H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type  Description
//========  =========== ===== ===============================================
// RXDATA       [31: 0]     r  Received Data. The RXDATA field contains the
//                            SPI data  received.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_RXFR_F_Tag
{
   uint32_t   RXDATA;         // Bits [31: 0]

}  DSPI_RXFR_F_T;

typedef volatile union DSPI_RXFR_Tag
{
   DSPI_RXFR_F_T        F;
   uint16_t             U16[DSPI_ARRAY_SIZE_2];
   uint32_t             U32;

}  DSPI_RXFR_T;

//=============================================================================
// ID - DSPI DSI Configuration Register (DSPI_DSICR)
// Base Offset : 0000 00BCH
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// =========  ========= ===== ===============================================
// MTOE             31    rw  Multiple Transfer Operation Enable. The MTOE
//                            bit enables multiple DSPIs to be connected in
//                            a parallel or serial configuration.
//
//                                 1 Multiple Transfer Operation enabled
//                                 0 Multiple Transfer Operation disabled
//
// FMSZ             30     r  MSB of the Frame Size in master mode. if the bit
//                            is set, 16 is added to the frame size, defined by
//                            DSPI_CTARn[FMSZ] filed. DSPI_CTARn register is 
//                            selected by the DSICTAS field.
//
// MTOCNT      [29:24]    rw  Multiple Transfer Operation Count. The MTOCNT
//                            field selects number of bits to be shifted out
//                            during a transfer in Multiple Transfer
//                            Operation. The field sets the number of SCK
//                            cycles that the bus Master will generate to
//                            complete the transfer. The number of SCK cycles
//                            used will be one more than the value in the
//                            MTOCNT field. The number of SCK cycles defined
//                            by MTOCNT must be equal to or greater than the
//                            frame size.
//
// 0           [23:21]     r  Reserved, should be cleared.
//
// TSBC             20    rw  Timed Serial Bus Configuration. The TSBC bit 
//                            enables the Timed Serial Bus Configuration. This
//                            configuration allows 32-bit data to be used. It 
//                            also allows tDT to be programmable.
//                            “Timed Serial Bus (TSB)” for detailed information
//                            0 Timed Serial Bus Configuration disabled
//                            1 Timed Serial Bus Configuration enabled
//                            If this bit is clear the DSPI_DSICR1 register 
//                            value has no effect.
//
// TXSS             19    rw  Transmit Data Source Select. The TXSS bit
//                            selects the source of data to be serialized.
//                            The source can be either data from Host
//                            Software written to the DSPI DSI Alternate
//                            Serialization Data Register (DSPI_ASDR), or
//                            Parallel Output pin states latched into the
//                            DSPI DSI Serialization Data Register
//                            (DSPI_SDR).
//
//                             1 Source of serialized data is the DSPI_ASDR
//                             0 Source of serialized data is the DSPI_SDR
//
// TPOL             18    rw  Trigger Polarity. The TPOL bit selects the
//                            active edge of the hardware trigger input
//                            signal (HT). The bit selects which edge will
//                            initiate a transfer in the DSI configuration.
//
//                             1 Rising edge will initiate a transfer
//                             0 Falling edge will initiate a transfer
//
// TRRE             17    rw  Trigger Reception Enable. The TRRE bit enables
//                            the DSPI to initiate a transfer when an
//                            external trigger signal is received. The bit
//                            is only valid in DSI configuration.
//
//                             1 Trigger signal reception enabled
//                             0 Trigger signal reception disabled
//
// CID              16    rw  Change In Data Transfer Enable. The CID bit
//                            enables a change in serialization data to
//                            initiate a transfer. The bit is used in Master
//                            Mode in DSI and CSI configurations to control
//                            when to initiate transfers. When the CID bit
//                            is set, serialization is initiated when the
//                            current DSI data differs from the previous DSI
//                            data shifted out. The DSPI_COMPR register is
//                            compared with the DSPI_SDR or DSPI_ASDR
//                            register to detect a change in data.
//
//                             1 Change in data transfer operation enabled
//                             0 Change in data transfer operation disabled
//
// DCONT            15    rw  DSI Continuous Peripheral Chip Select Enable.
//                            The DCONT bit enables the PCS signals to remain
//                            asserted between transfers. The DCONT bit only
//                            affects the PCS signals in DSI Master Mode.
//
//                             1 Keep Peripheral Chip Select signals asserted
//                               after transfer is complete
//                             0 Return Peripheral Chip Select signals to
//                               their inactive state after transfer is
//                               complete
//
// DSICTAS     [14:12]    rw  DSI Clock and Transfer Attributes Select. The
//                            DSICTAS field selects which of the
//                            DSPI_CTAR register is used to provide transfer
//                            attributes in DSI configuration. The DSICTAS
//                            field is used in DSI Master Mode. In DSI Slave
//                            Mode, the DSPI_CTAR1 is always selected. The
//                            table below shows how the DSICTAS values map
//                            to the DSPI_CTAR registers.
//
//                               DSICTAS  DSI Clock and Transfer Attributes
//                                                   Controlled by
//
//                                 000                DSPI_CTAR0
//                                 001                DSPI_CTAR1
//                                 010                DSPI_CTAR2
//                                 011                DSPI_CTAR3
//                                 100                DSPI_CTAR4
//                                 101                DSPI_CTAR5
//                                 110                DSPI_CTAR6
//                                 111                DSPI_CTAR7
//
// DMS           11       rw  Data Match Stop. DMS bit if set stops DSI frames 
//                            transmissions if DDIF flag is set in the DSPI_SR
//                            register.
//                                0 DDIF flag does not have effect on DSI frames 
//                                  transmissions.
//                                1 DDIF flag stops DSI frame transmissions.
//
// PES           10       rw  Parity Error Stop. PES bit if set stops DSI operation
//                            if the parity error had happened in received DSI frame.
//                                0 parity error does not stop DSI frame transmissions.
//                                1 parity error stops all DSI frame transmissions.
//
// PE            9        rw  Parity Enable. PE bit enables parity bit transmission
//                            and parity reception check for the DSI frames
//                                0 No parity bit included/checked.
//                                1 Parity bit is transmitted instead of last data 
//                                  bit in frame, parity checked for received frame.
//
// PP            8        rw  Parity Polarity. PP bit controls polarity of the parity
//                            bit transmitted and checked
//                                0 Even Parity: number of “1” bits in the transmitted 
//                                  frame is even. The DSPI_SR[DPEF] bit is set if
//                                  in the received frame number of “1” bits is odd.
//                                1 Odd Parity: number of “1” bits in the transmitted 
//                                  frame is odd. The DSPI_SR[DPEF] bit is set if in
//                                  the received frame number of “1” bits is even.
//
// DPCSx         [7:0]    rw  DSI Peripheral Chip Select 0 - 7. The DPCS
//                            bits select which of the PCS signals to assert
//                            during a DSI transfer. The DPCS bits only
//                            control the assertions of the PCS signals in
//                            DSI Master Mode.
//
//                              1 Assert PCS[x]
//                              0 Negate PCS[x]
//
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_DSICR_F_Tag
{
   bitfield32_t   MTOE      :  BIT_1;  // Bit      31
   bitfield32_t   FMSZ      :  BIT_1;  // Bit      30
   bitfield32_t   MTOCNT    :  BIT_6;  // Bits [29:24]
   bitfield32_t             :  BIT_1;  // Bits 23
   bitfield32_t   TRG          :  BIT_1;  // Bits 22
   bitfield32_t   ITSB       :  BIT_1;  // Bits 21
   bitfield32_t   TSBC      :  BIT_1;  // Bit      20
   bitfield32_t   TXSS      :  BIT_1;  // Bit      19
   bitfield32_t   TPOL      :  BIT_1;  // Bit      18
   bitfield32_t   TRRE      :  BIT_1;  // Bit      17
   bitfield32_t   CID       :  BIT_1;  // Bit      16
   bitfield32_t   DCONT     :  BIT_1;  // Bit      15
   bitfield32_t   DSICTAS   :  BIT_3;  // Bits [14:12]
   bitfield32_t   DMS       :  BIT_1;  // Bit      11
   bitfield32_t   PES       :  BIT_1;  // Bit      10
   bitfield32_t   PE        :  BIT_1;  // Bit      9
   bitfield32_t   PP        :  BIT_1;  // Bit      8
   bitfield32_t   DPCS      :  BIT_8;  // Bits [ 7: 0]

}  DSPI_DSICR_F_T;

typedef volatile union DSPI_DSICR_Tag
{
   DSPI_DSICR_F_T          F;
   uint32_t              U32;

}  DSPI_DSICR_T;

//=============================================================================
// ID - DSPI DSI Serialization Data Register (DSPI_SDR)
// Base Offset : 0000 00C0H
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
//==========  =========  ==== ===============================================
//
// SER_DATA     [31: 0]     r  Serialized Data. The SER_DATA filed contains
//                            the signal states of the Parallel Input signals
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_SDR_F_Tag
{
   uint32_t   SER_DATA;  // Bits [31: 0]

}  DSPI_SDR_F_T;

typedef volatile union DSPI_SDR_Tag
{
   DSPI_SDR_F_T          F;
   uint16_t              U16[DSPI_ARRAY_SIZE_2];
   uint32_t              U32;

}  DSPI_SDR_T;

//=============================================================================
// ID - DSPI DSI Alternate Serialization Data Register (DSPI_ASDR)
// Base Offset : 0000 00C4H
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
//===========  ======== ===== ===============================================
//
// ASER_DATA    [31: 0]    rw  Alternate Serialized Data. The ASER_DATA field
//                            holds the alternate data to be serialized.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_ASDR_F_Tag
{
   uint32_t    ASER_DATA;  // Bits [31: 0]

}  DSPI_ASDR_F_T;

typedef volatile union DSPI_ASDR_Tag
{
   DSPI_ASDR_F_T          F;
   uint16_t               U16[DSPI_ARRAY_SIZE_2];
   uint32_t               U32;

}  DSPI_ASDR_T;

//=============================================================================
// ID - DSPI DSI Transmit Comparison Register (DSPI_COMPR)
// Base Offset : 0000 00C8H
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// =========  ========== ==== ===============================================
//
// COMP_DATA    [31: 0]     r  Compare Data. The COMP_DATA field holds the
//                            last serialized DSI data.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_COMPR_F_Tag
{
   uint32_t    COMP_DATA;  // Bits [31: 0]

}  DSPI_COMPR_F_T;

typedef volatile union DSPI_COMPR_Tag
{
   DSPI_COMPR_F_T        F;
   uint16_t              U16[DSPI_ARRAY_SIZE_2];
   uint32_t              U32;

}  DSPI_COMPR_T;

//=============================================================================
// ID - DSPI DSI Deserialization Data Register (DSPI_DDR)
// Base Offset : 0000 00CCH
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// ========== ========= ===== ===============================================
//
// DESER_DATA   [31: 0]     r  Deserialized Data. The DESER_DATA field holds
//                            deserialized data which is presented as signal
//                            states to the Parallel Output signals.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_DDR_F_Tag
{
   uint32_t    DESER_DATA;  // Bits [31: 0]

}  DSPI_DDR_F_T;

typedef volatile union DSPI_DDR_Tag
{
   DSPI_DDR_F_T          F;
   uint16_t              U16[DSPI_ARRAY_SIZE_2];
   uint32_t              U32;

}  DSPI_DDR_T;

//=============================================================================
// ID - DSPI DSI Configuration Register 1 (DSPI_DSICR1)
// Base Offset : 0000 00D0H
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// ========== ========= ===== =================================================
//
// 0            [31:29]     r  Reserved, should be cleared.
//
// TSBCNT       [28: 24]   r   Timed Serial Bus Operation Count. When TSBC 
//                             is set, TSBCNT defines the length of the data 
//                             frame. TSBCNT field valid value is from 3 to 31.
//                             The TSBCNT field selects number of data bits to 
//                             be shifted out during a transfer in TSB mode. 
//                             The number of data bits in the data frame is 
//                             one more than the value in the TSBCNT field.
//
// 0            [23:18]     r  Reserved, should be cleared.
//
// DSE1              17    rw  Data Select Enable1. When TBSC bit is set, the 
//                             DSE1 bit controls insertion of the zero bit 
//                             (Data Select) in the middle of the data frame.
//                             The insertion bit position is defined by FMSZ 
//                             field of DSPI_CTARn register, selected by the 
//                             DSPI_DSICR[DSICTAS] field. The TSBCNT field 
//                             value must be greater than the FMSZ field 
//                             value plus one for proper operation of the 
//                             DSE1 bit.
//                             1 Zero bit is inserted at the middle of the 
//                             data frame. Total number of bits in the data
//                             frame is increased by 1.
//                             0 No Zero bit inserted in the middle of the
//                             data frame.
//
// DSE0              16     r  Data Select Enable0. The DSE0 bit controls 
//                             insertion of the zero bit (Data Select) in the
//                             beginning of the DSI frame.
//                             1 Zero bit is inserted at the beginning of the
//                             data frame. Total number of bits in the data 
//                             frame is increased by 1.
//                             0 No Zero bit inserted in the beginning of the
//                             frame
//
// 0             [15:8]     r  Reserved, should be cleared.
//
// DPCS1         [7: 0]     r  DSI Peripheral Chip Select 0–7. These bits 
//                             define the PCSs to assert for the second part 
//                             of the DSI frame when operating in TSB 
//                             configuration with dual receiver. The DPCS1
//                             bits select which of the PCS signals to assert
//                             during the second part of the DSI frame. The 
//                             DPCS1 bits only control the assertions of the 
//                             PCS signals in TSB mode.
//                             0 Negate PCS[x]
//                             1 Assert PCS[x]
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_DSICR1_F_Tag
{
   bitfield32_t          :  BIT_3;  // Bits [31:29]
   bitfield32_t   TSBCNT :  BIT_5;  // Bits [28:24]
   bitfield32_t          :  BIT_6;  // Bits [23:18]
   bitfield32_t     DSE1 :  BIT_1;  // Bits 17
   bitfield32_t     DSE0 :  BIT_1;  // Bits 16
   bitfield32_t          :  BIT_8;  // Bits [15: 8]
   bitfield32_t    DPCS1 :  BIT_8;  // Bits [7: 0]

}  DSPI_DSICR1_F_T;

typedef volatile union DSPI_DSICR1_Tag
{
   DSPI_DSICR1_F_T       F;
   uint16_t              U16[DSPI_ARRAY_SIZE_2];
   uint32_t              U32;

}  DSPI_DSICR1_T;

//=============================================================================
// ID - DSPI DSI Serialization Source Select Register 1 (DSPI_SSR)
// Base Offset : 0000 00D4H
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// ========== ========= ===== =================================================
// SS          [31:0]     rw   Source Select. The SS bits select serialization 
//                             source for DSI frame. Each SS bit selects data for
//                             corresponded bit in the transmitted frame.
//                             0 the bit in transmitted frame is taken from 
//                             Parallel Input pin;
//                             1 the bit in transmitted frame is taken from 
//                             DSPI_ASDR register
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef uint32_t  DSPI_SSR_T;

//=============================================================================
// ID - DSPI DSI DSI Parallel Input Select Registers (DSPI_PISR0-3)
// Base Offset : 0000 00D8H
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// ========== ========= ===== =================================================
// IPSx         [3:0]     rw   Input Pin Select x. The IPSx field selects 
//                             Parallel Input pin for transmitted frame bit x.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================

typedef volatile struct DSPI_PISR_F_Tag
{
   bitfield32_t    IPS0 :  BIT_4;  // Bits [31:28]
   bitfield32_t    IPS1 :  BIT_4;  // Bits [27:24]
   bitfield32_t    IPS2 :  BIT_4;  // Bits [23:20]
   bitfield32_t    IPS3 :  BIT_4;  // Bits [19:16]
   bitfield32_t    IPS4 :  BIT_4;  // Bits [15:12]
   bitfield32_t    IPS5 :  BIT_4;  // Bits [11:8]
   bitfield32_t    IPS6 :  BIT_4;  // Bits [7:4]
   bitfield32_t    IPS7 :  BIT_4;  // Bits [3:0]

}  DSPI_PISR_F_T;

typedef volatile union DSPI_PISR_Tag
{
   DSPI_PISR_F_T       F;
   uint16_t              U16[DSPI_ARRAY_SIZE_2];
   uint32_t              U32;

}  DSPI_PISR_T;

//=============================================================================
// ID - DSPI DSI Deserialized Data Interrupt Mask Register (DSPI_DIMR)
// Base Offset : 0000 00D8H
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// ========== ========= ===== =================================================
// MASK         [31:0]     rw  MASK. The MASK bits define which bits in 
//                             received deserialization data should be checked
//                             to produce the Deserialized Data Interrupt (DDI)
//                             0 the bit in received DSI frame does not 
//                             produce DDI interrupt.
//                             1 the bit in received DSI frame can produce DDI
//                             interrupt if the data bit matches to configured
//                             polarity.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================
typedef  uint32_t  DSPI_DIMR_T;

//=============================================================================
// ID - DSPI DSI Deserialized Data Polarity Interrupt Register (DSPI_DPIR)
// Base Offset : 0000 00ECH
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// ========== ========= ===== =================================================
// DP           [31:0]     rw  Data Polarity. The DP bits define what value of 
//                             the received deserialization data sets the
//                             DSPI_SR[DDIF] bit.
//                             0 if received bit is 0 the DSPI_SR[DDIF] bit is set.
//                             1 if received bit is 1 the DSPI_SR[DDIF] bit is set.
//
// Note: The Bit      numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================
typedef  uint32_t  DSPI_DPIR_T;


//=============================================================================
//  DSPI Module Register Structure
//=============================================================================

typedef volatile struct DSPI_Tag
{
   DSPI_MCR_T          MCR;                          // 0x0000 - 0x0003
   uint8_t                   reserved_0[DSPI_RESERVED_4] ;                          // 0x0004 - 0x0007
   DSPI_TCR_T          TCR;                          // 0x0008 - 0x000B
   DSPI_CTAR_T         CTAR[DSPI_CTA_QUANTITY];      // 0x000C - 0x002B
   DSPI_SR_T           SR;                           // 0x002C - 0x002F
   DSPI_RSER_T         RSER;                         // 0x0030 - 0x0033
   DSPI_PUSHR_T        PUSHR;                        // 0x0034 - 0x0037
   DSPI_POPR_T         POPR;                         // 0x0038 - 0x003B
   DSPI_TXFR_T         TXFR[DSPI_TRANSFER_QUANTITY]; // 0x003C - 0x007B
   DSPI_RXFR_T         RXFR[DSPI_RECEIVE_QUANTITY];  // 0x007C - 0x00BB
   DSPI_DSICR_T        DSICR;                        // 0x00BC - 0x00BF
   DSPI_SDR_T          SDR;                          // 0x00C0 - 0x00C3
   DSPI_ASDR_T         ASDR;                         // 0x00C4 - 0x00C7
   DSPI_COMPR_T        COMPR;                        // 0x00C8 - 0x00CB
   DSPI_DDR_T          DDR;                          // 0x00CC - 0x00CF
   DSPI_DSICR1_T       DSICR1;                       // 0x00D0 - 0x00D3
   DSPI_SSR_T          SSR;                          // 0x00D4 - 0x00D7
   DSPI_PISR_T         PISR[DSPI_PISR_QUANTITY];     // 0x00D8 - 0x00E7
   DSPI_DIMR_T         DIMR;                         // 0x00E8 - 0x00EB
   DSPI_DPIR_T         DPIR;                         // 0x00EC - 0x00EF

}  DSPI_T;

#endif // HW_DSPI_H

