#ifndef HW_DFILTER_H
#define HW_DFILTER_H


#include "reuse.h"


#define DECFILT_RESERVED_0x08       (0x08U)
#define DECFILT_COEFF_QUANTITY      (0x09)
#define DECFILT_RESERVED_0x34       (0x34U)
#define DECFILT_TAP_QUANTITY        (0x08U)
#define DECFILT_RESERVED_0x38       (0x38U)
#define DECFILT_RESERVED_0x0C       (0x0CU)
#define DECFILT_RESERVED_0x12C    (0x12CU)

#define DEC_FILTER_IDF_CLEAR_MASK      (0x02000000UL)
#define DEC_FILTER_ODF_CLEAR_MASK      (0x01000000UL)
#define DEC_FILTER_MSR_ERR_CLEAR_MASK  (0x000F0000UL)
#define DEC_FILTER_SDF_CLEAR_MASK      (0x01000000UL)
#define DEC_FILTER_IBIF_CLEAR_MASK     (0x00400000UL)
#define DEC_FILTER_OBIF_CLEAR_MASK     (0x00200000UL)
#define DEC_FILTER_SSOVFC_CLEAR_MASK   (0x00040000UL)
#define DEC_FILTER_SCOVFC_CLEAR_MASK   (0x00020000UL)

//=============================================================================
// ID - Decimation Filter Module Configuration Register (DECFILT_x_MCR)
//
// Base Offset :Address: DECFILT_x_BASE + 0x000
//
// Reset Value :0x0
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// MDIS         [0]       rw   Module Disable
//                             The MDIS bit puts the Decimation Filter in 
//                             low power mode. Communication through the eQADC
//                             Interface is ignored in this mode. Writes to the
//                             configuration register are allowed with the exception
//                             of writes to the FREN and SRES bits, which are 
//                             ignored. Writes to the Coefficient registers are
//                             allowed. The Decimation Filter cannot enter 
//                             Freeze mode once in disable mode.
//                             1 = Low Power Mode
//                             0 = Normal Mode
//
// FREN          1        rw   The FREN bit enables the Decimation Filter to
//                             enter freeze mode
//                             1 = Freeze mode enabled
//                             0 = Freeze mode disabled
//
// 0             2         r   Reserved.
//
// FRZ           3        rw   The FRZ bit controls the freeze mode of the 
//                             Decimation Filter. For this bit to take effect 
//                             the FREN freeze enable bit also needs to be 
//                             asserted. While in freeze mode the MAC operations 
//                             are halted
//                             1 = Freeze Mode
//                             0 = Normal Mode
//
// SRES         [4]      r0w   The SRES is a self-negated bit which provides the 
//                             capability to initialize the Decimation Filter
//                             interface. This bit always reads as zero.
//                             1 = Software-Reset
//                             0 = No action
//
// CASCD       [5:6]      rw   Cascade Mode Configuration
//                             The CASCD[1:0] bit field configures the block to 
//                             work in cascade mode of operation according to
//                             Table
//                                  CASCD[1:0]          Description
//                                     00       No cascade mode (single block)
//                                     01       Cascade Mode, Head block config.
//                                     10       Cascade Mode, Tail block config.
//                                     11      Cascade Mode, Middle block config.
//
// IDEN        [7]        rw   Input Data Interrupt Enable
//                             The IDEN bit enables the Decimation Filter to 
//                             generate interrupt requests on all new input data 
//                             written to the Interface Input Buffer register.
//                             1 = Input Data Interrupt Enabled
//                             0 = Input Data Interrupt Disabled
//
// ODEN        [8]        rw   Output Data Interrupt Enable
//                             The ODEN bit enables the Decimation Filter to 
//                             generate interrupt requests on all new data written
//                             to the filter Output buffer. This is independent of 
//                             the IO_SEL field setting.
//                             1 = Output Data Interrupt Enabled
//                             0 = Output Data Interrupt Disabled
//
// ERREN       [9]        rw   Error Interrupt Enable
//                             The ERREN bit enables the Decimation Filter to 
//                             generate interrupt requests based on the assertion 
//                             of the DECFILTER_MSR register error flags OVF, DIVR,
//                             SVR, OVR or IVR.
//                             1 = Error Interrupts Enabled
//                             0 = Error Interrupts Disabled
//
// 0           [10]       r    Reserved
//
// FTYPE       [11:12]    rw   Filter Type Selection bits
//                             The FTYPE[1:0] bits select the filter type according
//                             to Table below.
//                                  FTYPE[1:0]           Description
//                                      00              Filter Bypass
//                                      01         IIR Filter - 1 x 4th order
//                                      10         FIR Filter - 1 x 8th order
//                                      11                 reserved
//
// 0           [13]       r    Reserved
//
// SCAL       [14;15]     rw   Filter Scaling Factor
//                             The SCAL[1:0] bit field selects the scaling factor 
//                             used by the filter algorithm according to Table below.
//                                      SCAL[1:0]      Description
//                                         00       Scaling Factor = 1
//                                         01       Scaling Factor = 4
//                                         10       Scaling Factor = 8
//                                         11       Scaling Factor = 16
//
// IDIS       [16]        rw   Input Disable
//                             The IDIS bit disables the block input, so that writes
//                             to the input buffer have no effect and input DMA
//                             or interrupt requests are not issued. Input disabling
//                             is needed to change the block configuration to or
//                             from cascade mode.
//                             1 = Input disabled
//                             0 = Input enabled
//
// SAT        [17]       rw    Saturation Enable
//                             The SAT bit enables the saturation of the filter output
//                          .  See Section 27.3.11, “Saturation,” for more
//                             details.
//                             1 = Enable Saturation
//                             0 = Disables Saturation
//
// IO_SEL   [18:19]      rw    The IO_SEL[1:0] field selects the source of the input 
//                             data to the Decimation Filter, and the destination
//                             for the filter output result. The IO_SEL[1:0] encoding
//                             and associated source and destination definitions is 
//                             given in Table 27-7. Note that when Decimation Filters
//                             are cascaded to form larger filters, the IO_SEL[1:0] 
//                             field only is applicable to the input data source for
//                             the head filter in the cascade, and to the output result
//                             destination for the tail filter in the cascade. Filters
//                             in the middle of the cascade receive input and send output
//                             to their adjacent filters in the cascade. Regardless 
//                             of the IO_SEL setting, the Decimation Filter input and 
//                             output buffer registers can be read by the CPU/DMA at any
//                             time, and the output buffer register is updated in the 
//                             case of the eQADC_B result destination. Note that the 
//                             eQADC_B module has to configured to send conversion 
//                             results to a decimation filter in addition to setting 
//                             the IO_SEL field.
//                             IO_SEL[1]  IO_SEL[0]     Input Data Source Output
//                                                           Result Destination
//                                0         0  eQADC_B A/D conversion result eQADC RFIFO
//                                0         1  eQADC_B A/D conversion result Output 
//                                                    Buffer Register (CPU/DMA)
//                                1         0  Input Buffer Register (CPU/DMA) Output
//                                                    Buffer Register (CPU/DMA)
//                                1         1  Input Buffer Register (CPU/DMA) eQADC RFIFO
//
// DEC_RATE   [20:23]    rw    Decimation Rate Selection
//                             The DEC_RATE[3:0] field selects the decimation rate used by
//                             the Decimation Filter. The decimation
//                             rate defines the number of data samples from master block
//                             that is required to generate one
//                             decimated result in the Decimation Filter output.
//                             DEC_RATE[3:0]              Description
//                                0000          No Decimation: one filter output for
//                                                      each sample input
//                             0001 - 1111   one filter output for each (DEC_RATE+1)s
//                                                       ample inputs
//
// SDIE       [24]       rw    Integrator Data Interrupt Enable
//                             The SDIE field enables output buffer interrupts due to 
//                             integrator data result being ready.
//                             1 = Integration ready causes an output interrupt
//                             0 = Integration ready does not cause an output interrupt.
//
// DSEL       [25]       rw    DMA Selection
//                             The DSEL bit determines whether the data transfers — to 
//                             the input buffer (write to) and from the
//                             output buffer (read from)are performed by DMA requests
//                             or by interrupt requests .
//                             1 = DMA requests are generated
//                             0 = Interrupt requests are generated
//
// IBIE       [26]       rw    Input Buffer Interrupt Request Enable
//                             The IBIE bit enables the Decimation Filter to generate 
//                             interrupt requests when:
//                             CPU/DMA is selected (IO_SEL[1]=1), DSEL=0, and the input 
//                             buffer is available to receive new data;
//                             eQADC input is selected with Enhanced debug (IO_SEL[1]=0,
//                             EDME=1), DSEL=0, and the
//                             input buffer has data to be read by theCPU.
//                             1 = Input Buffer Interrupt Request Enabled
//                             0 = Input Buffer Interrupt Request Disabled
//
// OBIE       [27]       rw    Output Buffer Interrupt Request Enable
//                             The OBIE bit enables the Decimation Filter interrupt 
//                             requests when outputs are directed to the
//                             CPU/DMA and DMA requests is not selected (DSEL=0).
//                             1 = Output Buffer Interrupt Request Enabled
//                             0 = Output Buffer Interrupt Request Disabled
//
// EDME       [28]      rw     Enhanced Debug Monitor Enable
//                             The EDME bit defines the enhanced debug monitor when input 
//                             Selection is from eQADC (IO_SEL[1]=0).
//                             1 = Enhanced debug monitor enabled
//                             0 = Enhanced debug monitor disabled
//
// TORE       [29]      rw     Triggered Output Result Enable—Enables an eTPU signal to 
//                             transfer the filter result to its destination, using the
//                             mode specified by TMODE[1:0].
//                             0 Output buffer transfer by eTPU signal disabled
//                             1 Output buffer transfer by eTPU signal enabled
//
// TMODE    [30:31]     rw     Trigger Mode—Selects the way the eTPU signal controls 
//                             the transfer of a new output result
//                             00 result is transferred at the rising edge of the eTPU signal
//                             01 result is transferred while the eTPU signal is 0
//                             10 result is transferred at the falling edge of the eTPU signal
//                             11 result is transferred while the eTPU signal is 1
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct DECFILT_MCR_F_Tag
{
   bitfield32_t  MDIS      :  BIT_1;  // Bit  [0]
   bitfield32_t  FREN      :  BIT_1;  // Bit   1
   bitfield32_t            :  BIT_1;  // Bit   2 is reserved
   bitfield32_t  FRZ       :  BIT_1;  // Bit   3
   bitfield32_t  SRES      :  BIT_1;  // Bits  4
   bitfield32_t  CASCD     :  BIT_2;  // Bit   5:6
   bitfield32_t  IDEN      :  BIT_1;  // Bit   7
   bitfield32_t  ODEN      :  BIT_1;  // Bit   8
   bitfield32_t  ERREN     :  BIT_1;  // Bit   9
   bitfield32_t            :  BIT_1;  // Bit   10
   bitfield32_t  FTYPE     :  BIT_2;  // Bit   11:12
   bitfield32_t            :  BIT_1;  // Bit   13
   bitfield32_t  SCAL      :  BIT_2;  // Bit   14:15
   //bitfield32_t  IDIS      :  BIT_1;  // Bit   16
   bitfield32_t        :  BIT_1;  // Bit   16
   bitfield32_t  SAT       :  BIT_1;  // Bit   17
  // bitfield32_t  IO_SEL    :  BIT_2;  // Bit   18:19
   bitfield32_t  ISEL    :  BIT_1;  // Bit   18:19
   bitfield32_t  MIXM    :  BIT_1;  // Bit   19
   bitfield32_t  DEC_RATE  :  BIT_4;  // Bit   20:23
  // bitfield32_t  SDIE      :  BIT_1;  // Bit   24
   bitfield32_t        :  BIT_1;  // Bit   24
   bitfield32_t  DSEL      :  BIT_1;  // Bit   25
   bitfield32_t  IBIE      :  BIT_1;  // Bit   26
   bitfield32_t  OBIE      :  BIT_1;  // Bit   27
   bitfield32_t  EDME      :  BIT_1;  // Bit   28
   bitfield32_t  TORE      :  BIT_1;  // Bit   29
   bitfield32_t  TMODE     :  BIT_2;  // Bit   30:31

}  DECFILT_MCR_F_T;

typedef union DECFILT_MCR_Tag
{
   DECFILT_MCR_F_T        F;
   uint32_t             U32;

}  DECFILT_MCR_T;


//=============================================================================
// ID - Decimation Filter Module Status Register (DECFILT_x_MSR)
// Address: DECFILT_x_BASE + 0x004
//
// Reset Value : 0x0
//
// Field        Bits     Type Description
// ============ ======== ====  ================================================
// ============ ======== ==== =================================================
// BSY          [0]       r    Decimation Filter Busy indication
//                             The BSY bit indicates that the Decimation Filter
//                             is actively processing a new input data sample. 
//                             BSY is not asserted when the filter is disabled 
//                            (FTYPE = 00). The BSY bit is asserted when the 
//                             soft reset is executed.
//                             1 = Decimation Filter Busy
//                             0 = Decimation Filter Idle
//
// 0             1        r    Reserved.
//
// DEC_COUNTER  [2:5]     r    Decimation Counter
//                             The DEC_COUNTER[3:0] field indicates the current
//                             value of the DEC_COUNTER Decimation
//                             Counter, which counts the number of input data 
//                             samples received by the Decimation Filter. When the
//                             value of this counter matches the DEC_RATE[3:0] 
//                             Configuration Register field, one decimated result
//                             is generated and the DEC_COUNTER counter is 
//                             re-initialized at zero. This register is cleared
//                             by a soft reset or a flush command.
//
// IDFC          6        rw   Input Data Flag Clear bit
//                             The IDFC bit clears the IDF Flag bit in the Status
//                             Register. This bit is self negated, therefore it is
//                             always read as zero.
//                             1 = Clears IDF
//                             0 = No action
//
// ODFC         [7]      rw    Output Data Flag Clear bit
//                             The ODFC bit clears the ODF Flag bit in the Status
//                             Register. This bit is self negated, therefore it is
//                             always read as zero.
//                             1 = Clears ODF
//                             0 = No action
//
// 0            [8]       r    Reserved.
//
// IBIC         [9]      rw    Input Buffer Interrupt Request Clear bit
//                             The IBIC bit clears the IBIF Flag bit in the Status
//                             Register. This bit is self negated, therefore it is
//                             always read as zero.
//                             1 = Clears IBIF
//                             0 = No action
//
// OBIC        [10]      rw    Output Buffer Interrupt Request Clear bit
//                             The OBIC bit clears the OBIF Flag bit in the Status
//                             Register. This bit is self negated, therefore it is
//                             always read as zero.
//                             1 = Clears OBIF
//                             0 = No action
//
// 0           [11]       r    Reserved.
//
// DIVRC       [12]      r0w   DIVR Clear bit
//                             The DIVRC bit clears the DIVR Debug Filter Input 
//                             Data Read Overrun indication bit in the Status
//                             Register. This bit is self negated, therefore it 
//                             is always read as zero.
//                             1 = Clears DIVR
//                             0 = No action
//
// OVFC        [13]      r0w   OVF Clear bit
//                             The OVFC bit clears the OVF Output Overflow bit
//                             in the Status Register. This bit is self negated,
//                             therefore it is always read as zero.
//                             1 = Clears OVF
//                             0 = No action
//
// OVRC        [14]      r0w   OVR Clear bit
//                             The OVRC bit clears the OVR Output Overrun bit 
//                             in the Status Register. This bit is self negated,
//                             therefore it is always read as zero.
//                             1 = Clears OVR
//                             0 = No action
//
// IVRC        [15]      r0w   IVR Clear bit
//                             The IVRC bit clears the IVR Output Overrun bit 
//                             in the Status Register. This bit is self negated,
//                             therefore it is always read as zero.
//                             1 = Clears IVR
//                             0 = No action
//
// 0         [16:21]       r   Reserved.
//
// IDF         [22]        r   Input Data Flag
//                             The IDF bit flag indicates when new data is 
//                             available at the DECFILT_x_IB register or at the
//                             DECFILT_x_IOB register. This flag generates an 
//                             Interrupt Request if enabled by the IDEN bit in the
//                             Configuration Register. This Flag is cleared by the
//                             IDFC Status bit or by a soft reset of the decimation
//                             filter.
//                             1 = New Sample received
//                             0 = Sample not received
//
// ODF         [23]        r   Output Data Flag
//                             The ODF bit flag indicates when a new decimated
//                             sample is available at the DECFILT_x_OB register
//                             or at the DECFILT_x_IOB register. This flag generates
//                             an Interrupt Request if enabled by the ODEN
//                             bit in the Configuration Register. This Flag is 
//                             cleared by the ODFC Status bit or by a soft reset of 
//                             the decimation filter.
//                             1 = New Decimated Output Sample available
//                             0 = No new Decimated Output Sample available
//
// 0           [24]       r   Reserved.
//
// IBIF        [25]        r   Input Buffer Interrupt Request Flag
//                             The IBIF bit flag indicates that the input buffer
//                             DECFILT_x_IB is available to be filled with new data,
//                             when Enhanced Debug Monitor is off. In Enhanced Debug
//                             Monitor, it indicates the input buffer
//                             DECFILT_x_IB was filled with a new sample and is 
//                             ready to be read. I
//                             1 = New Sample is requested (IO_SEL[1] = 1, EDME=0)
//                             or new sample is available in Enhanced
//                             Debug Monitor (IO_SEL[1]=0, EDME=1).
//                             0 = No action
//
// OBIF        [26]        r   IOutput Buffer Interrupt Request Flag
//                             The OBIF bit flag indicates that either a new decimated
//                             sample is available at the DECFILT_x_OB register.
//                             1 = New Decimated Output available
//                             0 = No new Decimated Output available
//
// 0           [27]        r   Reserved.
//
// DIVR        [28]        r   Enhanced Debug Monitor Input Data Read Overrun
//                             The DIVR bit indicates that a received sample in the 
//                             Filter Interface Input Register was overwritten by
//                             a new sample and was not read by the CPU/DMA. This 
//                             flag generates an Interrupt Request if enabled
//                             by the ERREN bit in the Configuration Register. 
//                             This Flag is cleared by the DIVRC Status bit or by a
//                             soft reset of the decimation filter.
//                             1 = Enhanced Debug Monitor Input Data Read Overrun occurred
//                             0 = Input Data Read Overrun did not occur in Enhanced Debug monitor
//
// OVF         [29]        r   Filter Overflow Flag
//                             The OVF bit indicates that an overflow occurred in 
//                             the filtered sample result. This flag generates an
//                             Interrupt Request if enabled by the ERREN bit in the 
//                             Configuration Register. This Flag is cleared by
//                             the OVFC Status bit or by a soft reset of the decimation 
//                             filter.
//                             1 = Overflow occurred
//                             0 = No overflow
//
// OVR         [30]        r   Output Interface Buffer Overrun
//                             The OVR bit indicates that a decimated sample was 
//                             overwritten by a new sample in the Interface
//                             Output Buffer Register. This flag generates an Interrupt 
//                             Request if enabled by the ERREN bit in the Configuration 
//                             Register. This Flag is cleared by the OVRC Status bit or 
//                             by a soft reset of the decimation filter.
//                             1 = Filter Output Overrun occurred
//                             0 = No Output Overrun
//
// IVR         [31]        r   Input Interface Buffer Overrun
//                             The IVR bit indicates that a received sample in the 
//                             Filter Interface Input Register was overwritten by
//                             a new sample. This flag generates an Interrupt Request 
//                             if enabled by the ERREN bit in the Configuration Register
//                           . This Flag is cleared by the IVRC Status bit or by a soft 
//                             reset of the decimation filter.
//                             1 = Input Buffer Overrun occurred
//                             0 = Input Buffer Overrun did not occur
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct DECFILT_MSR_F_Tag
{
   bitfield32_t  BSY         :  BIT_1;  // Bit  [0]
   bitfield32_t              :  BIT_1;  // Bit   1 is reserved
   bitfield32_t  DEC_COUNTER :  BIT_4;  // Bit   2:5
   bitfield32_t  IDFC        :  BIT_1;  // Bits  6
   bitfield32_t  ODFC        :  BIT_1;  // Bit   7
   bitfield32_t              :  BIT_1;  // Bit   8 is reserved
   bitfield32_t  IBIC        :  BIT_1;  // Bit   9
   bitfield32_t  OBIC        :  BIT_1;  // Bit   10
   bitfield32_t              :  BIT_1;  // Bit   11 is reserved
   bitfield32_t  DIVRC       :  BIT_1;  // Bit   12
   bitfield32_t  OVFC        :  BIT_1;  // Bit   13
   bitfield32_t  OVRC        :  BIT_1;  // Bit   14
   bitfield32_t  IVRC        :  BIT_1;  // Bit   15
   bitfield32_t              :  BIT_6;  // Bit   16:21
   bitfield32_t  IDF         :  BIT_1;  // Bit   22
   bitfield32_t  ODF         :  BIT_1;  // Bit   23
   bitfield32_t              :  BIT_1;  // Bit   24
   bitfield32_t  IBIF        :  BIT_1;  // Bit   25
   bitfield32_t  OBIF        :  BIT_1;  // Bit   26
   bitfield32_t              :  BIT_1;  // Bit   27
   bitfield32_t  DIVR        :  BIT_1;  // Bit   28
   bitfield32_t  OVF         :  BIT_1;  // Bit   29
   bitfield32_t  OVR         :  BIT_1;  // Bit   30
   bitfield32_t  IVR         :  BIT_1;  // Bit   31

}  DECFILT_MSR_F_T;

typedef union DECFILT_MSR_Tag
{
   DECFILT_MSR_F_T       F;
   uint32_t             U32;

}  DECFILT_MSR_T;

//=============================================================================
// ID - Decimation Filter Interface Input Buffer Register (DECFILT_x_IB)
// Address: DECFILT_x_BASE + 0x010
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ==========  ========= ==== ===============================================
// 0            [0:3]     r   Reserved.
//
// INTAG        [4:7]    rw   Decimation filter input tag bits
//                            The INTAG[3:0] bit field is defined as a selector
//                            signal and it is used to identify different destinations
//                            for the INBUF[15:0] data.
//                            When the input data source is the CPU/DMA and the
//                            output destination is eQADC_B, INTAG is used
//                            to address the appropriate RFIFO in the eQADC block.
//
// 0           [8:13]     r   Reserved.
//
// PREFILL      [14]     rw   Decimation Filter Prefill/Filter control bit
//                            The PREFILL bit selects the Decimation Filter 
//                            operation mode
//                            1 = Decimation Filter prefill sample
//                            0 = Decimation Filter normal sample
//
// FLUSH        [15]     rw   Decimation Filter Flush control bit
//                            Assertion of the FLUSH bit initializes the Decimation
//                            Filter to a initial state,
//                            This bit is self negated and it is cleared only when
//                            the data is read and the flush is executed.
//                            1 = flush request
//                            0 = no flush request
//
// INPBUF     [16:31]    rw   Input Buffer Data
//                            The INPBUF[15:0] bit field carries the sample data
//                            to be filtered. This data buffer can be written from
//                            the eQADC or by the CPU/DMA.
//
//=============================================================================
typedef struct DECFILT_IB_F_Tag
{
   bitfield32_t           :  BIT_4;  // Bit    0:3    reserved
   bitfield32_t  INTAG    :  BIT_4;  // Bits   4:7
   bitfield32_t           :  BIT_6;  // Bit    8:13   reserved
   bitfield32_t  PREFILL  :  BIT_1;  // Bit    14
   bitfield32_t  FLUSH    :  BIT_1;  // Bit    15
   bitfield32_t  INPBUF   :  BIT_16; // Bit   16:31

}  DECFILT_IB_F_T;

typedef union DECFILT_IB_Tag
{
   DECFILT_IB_F_T         F;
   uint32_t             U32;

}  DECFILT_IB_T;

//=============================================================================
// ID - Decimation Filter Interface Output Buffer Register (DECFILT_x_OB)
// Address: DECFILT_x_BASE + 0x014
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0           [0:11]     r   reserved
//
// OUTTAG      [12:15]   rw   Decimation filter output tag bits
//                            The OUTTAG[3:0] bit field is defined as a 
//                            selector signal and it is used to identify different
//                            destinations for the OUTBUF[15:0] data.
//                            When the output result destination is eQADC_B,
//                            OUTTAG holds the same value as the
//                            DECFILT_x_IB[INTAG], which is used to address 
//                            the destination RFIFO.
//
// OUTBUF     [16:31]    rw   Output Buffer Data
//                            The OUTPBUF[15:0] bit field is the result data
//                            in the decimation filter Output Buffer. It 
//                            represents a fixed point signed number in two’s
//                            complement format and is updated only when a decimated
//                            result is ready to be transmitted, meaning it contains 
//                            the last decimated result from the filter.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct DECFILT_OB_F_Tag
{
   bitfield32_t          :  BIT_12;  // Bit 0:11
   bitfield32_t  OUTTAG  :  BIT_4;   // Bit 12:15
   bitfield32_t  OUTBUF  :  BIT_16;  // Bit 16:31

}  DECFILT_OB_F_T;

typedef union DECFILT_OB_Tag
{
   DECFILT_OB_F_T         F;
   uint16_t          U16[2];
   uint32_t             U32;

}  DECFILT_OB_T;

//=============================================================================
// ID - Decimation Filter Coefficient n Register (DECFILT_x_COEFn)
// Address: DECFILT_x_BASE + 0x020–0x040
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// =========== ========= ==== ===============================================
// COEFn        [0:7]     r   Coefficient n field sign extended bits
//
// COEFn        [8:31]    rw  Coefficient n field
//                            The COEFn[23:0] bit fields are the digital 
//                            filter coefficients registers. The coefficients
//                            are fractional signed values in two’s complement
//                            format, in the range (-1 ? coef < 1).
//
//=============================================================================
typedef struct DECFILT_COEF_F_Tag
{
   uint32_t  COEFSE      :  BIT_8;   // Bit   0:7
   uint32_t  COEF        :  BIT_24;  // Bit   8:31

}  DECFILT_COEF_F_T;

typedef union DECFILT_COEF_Tag
{
   DECFILT_COEF_F_T        F;
   uint32_t               U32;

}  DECFILT_COEF_T;

//=============================================================================
// ID - Decimation Filter TAPn Register (DECFILT_x_TAPn)
// Address: DECFILT_x_BASE + 0x078–0x094
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ========== ========== ==== ===============================================
// TAP         [0:31]     r  TAPn Register
//                           The read-only TAPn[23:0] bit fields shows the 
//                           contents of the digital filter tap registers, 
//                           as fractional //signed values in two’s complement
//                           format, in the range (-1 ? coef < 1). The tap 
//                           registers hold the input //data delay line 
//                           (Xn, Xn-1,......,Xn-7 for 8th order FIR)
//NOTE:Reads to this register are sign-extended, meaning the coefficient’s 
//sign bit is copied to all 8 most significant register bits.
//=============================================================================

typedef struct DECFILT_TAP_F_Tag
{
    int32_t       :8;
    int32_t TAP   :24;
} DECFILT_TAP_F_T;

typedef union DECFILT_TAP_Tag
{
    DECFILT_TAP_F_T  F;
    int32_t        S32;

} DECFILT_TAP_T;

//=============================================================================
// ID - Decimation Filter Interface Enhanced Debug Input Data Register (DECFILT_x_EDID)
// Address: DECFILT_x_BASE + 0x0D0
//
// Reset Value : 0000 7800H
//
// Field          Bits    Type Description
// =========== ========= ==== ===============================================
// 0            [0:15]     r  Reserved
//
// SAMP_DATA    [16:31]   rw  Conversion Sample Data
//                            The SAMP_DATA[15:0] bit field carries the data
//                            that was loaded into the Decimation Filter input
//                            buffer to be processed by the FIR/IIR sub-block.
//                            This value is only updated by input data received from
//                            eQADC_B (DECFILT_x_MCR[IO_SEL[1]] = 0), and the 
//                            Enhanced Debug Monitor is enabled 
//                            (DECFILT_x_MCR[EDME] = 1).
//
//
//=============================================================================
typedef struct DECFILT_EDID_F_Tag
{
   bitfield32_t               :  BIT_16;   // Bits  [0:15] reserved
   bitfield32_t   SAMP_DATA   :  BIT_16;   // Bits  [16:31]

}  DECFILT_EDID_F_T;

typedef union DECFILT_EDID_Tag
{
   DECFILT_EDID_F_T       F;
   uint32_t             U32;

}  DECFILT_EDID_T;
//=============================================================================
//  Decimation Filter Module Register Structure
//=============================================================================

typedef volatile struct DEC_FILTER_Tag
{
   DECFILT_MCR_T     MCR;                                // 0x8000 - 0x8003

   DECFILT_MSR_T     MSR;                                // 0x8004 - 0x8007

   uint8_t           reserved_0[DECFILT_RESERVED_0x08];  // 0x0008 - 0x800F

   DECFILT_IB_T      IB;                                 // 0x8010 - 0x8013

   DECFILT_OB_T      OB;                                 // 0x8014 - 0x8017

   uint8_t           reserved_1[DECFILT_RESERVED_0x08];  // 0x0018 - 0x801F

   DECFILT_COEF_T    COEF[DECFILT_COEFF_QUANTITY];       // 0x8020 - 0x8043

   uint8_t           reserved_2[DECFILT_RESERVED_0x34];  // 0x8044 - 0x8077

   DECFILT_TAP_T     TAP[DECFILT_TAP_QUANTITY];          // 0x8078 - 0x8097

   uint8_t           reserved_3[DECFILT_RESERVED_0x38];  // 0x8098 - 0x80CF

   DECFILT_EDID_T    EDID;                               // 0x80D0 - 0x80D3

   uint8_t           reserved_4[DECFILT_RESERVED_0x12C];  // 0x80D4 - 0x81FF

}  DEC_FILTER_T;

#endif // HW_DFILTER_H

