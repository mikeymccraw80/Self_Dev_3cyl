#ifndef HW_ADC_H
#define HW_ADC_H


#include "reuse.h"


//=============================================================================
// | ADC Internal registers ( sent via command )
//=============================================================================
//=============================================================================
// ID - ADCn Control Registers (ADC0_CR and ADC1_CR)
//
// Field        Bits     Type  Description
// ============ ======== ====  =================================================
// ADCn_EN       0         rw  ADCn enable. Enables ADCn to perform A/D conversions.
//                             Refer to Section 19.4.5.1,"Enabling and Disabling
//                             the on-chip ADCs," for details.
//                             0 ADC is disabled. Clock supply to ADC0/1 is stopped.
//                             1 ADC is enabled and ready to perform A/D conversions.
//                               Note: The bias generator circuit inside the
//                               ADC ceases functioning when both ADC0_EN and ADC1_EN
//                               bits are negated.
//                               Note: Conversion commands sent to a disabled ADC 
//                               are ignored by the ADC control hardware.
//                               Note: When the ADCn_EN status is changed from 
//                               asserted to negated, the ADC clock will not stop 
//                               until it reaches its low phase.
//
// 0             [1:3]         Reserved.
//
// ADCn_EMUX      4       rw  ADCn external multiplexer enable. When ADCn_EMUX is 
//                            asserted, the MA pins will output digital values 
//                            according to the number of the external channel 
//                            being converted for selecting external multiplexer
//                            inputs. Refer to Section 19.4.6, "Internal/External
//                            Multiplexing," for a  detailed description about 
//                            how ADCn_EMUX affects channel number decoding.
//                            0 External multiplexer disabled; no external
//                              multiplexer channels can be selected.
//                            1 External multiplexer enabled; external multiplexer
//                              channels can be selected.
//                              Note: Both ADCn_EMUX bits must not be asserted
//                                    at the same time.
//                              Note: The ADCn_EMUX bit must only be written when 
//                                    the ADCn_EN bit is negated. ADCn_EMUX can be 
//                                    set during the same write cycle used to set 
//                                    ADCn_EN.
//
// 0             [5]          Reserved.
//
//ADCn_TBSEL     [6:7]       Timebase Selection for ADC0/1
//                           The ADC0/1_TBSEL[0:1] field selects the time 
//                           information to be used as timestamp according to
//                           Table below
//                           
//                           ADC0/1_TBSEL[0:1]           Definition
//                           00       Selects internally generated time base as time stamp.
//                           01       Selects imported time base 1 indicated by SRV1 bit 
//                                    field of EQADC_REDLCCR register.
//                           10       Selects imported time base 2 indicated by SRV2 bit 
//                                    field of EQADC_REDLCCR register.
//                           11       Reserved
//
//ADC0n_ODD_PS     8         Clock Prescaler Odd Rates Selector for ADC0/1
//                           The ADC0/1_CLK_DTY field controls the duty rate of the 
//                           ADC0/1 clock when the ADC0/1_CLK_PS field is asserted.
//                           The generated clock has an odd number of system clock 
//                           cycles, therefore this field is used to select a clock 
//                           duty higher or lower than 50%.
//                           1 = Odd divide factor is selected. The final divide factor 
//                               is dependent of ADC0/1_CLK_PS field.
//                           0 = Even divide factor is selected. The final divide factor
//                               is dependent of ADC0/1_CLK_PS field.
//
//ADCn_CLK_DTY      9        Clock Duty Rate Selector for ADC0/1 (for odd divide factors)
//                           The ADC0/1_ODD_PS field is used together with the 
//                           ADC0/1_CLK_PS field to define even/odd
//                           divide factors in the generation of the ADC0/1 clocks.
//                           1 = clock high pulse is longer 1 clock cycle than low portion.
//                           0 = clock low interval is longer 1 clock cycle than high pulse.
//
// ADCn_CLK_SEL    10        Clock Selector for ADC0/1
//                           The ADC0/1_CLK_SEL is used to select between the 
//                           system clock signal or the prescaler output signal.
//                           The prescaler provides the system clock signal divided 
//                           by a even factor from 2 to 64. This is required to 
//                           permit the ADC to run as fast as possible when the 
//                           device is in Low Power Active mode and system clock is 
//                           around 1 MHz.
//                           1 = System clock is selected - maximum frequency.
//                           0 = Prescaler output clock is selected.
//
// ADCn_CLK_PS   [11:15]      ADCn clock prescaler. The ADCn_CLK_PS field controls the system clock divide factor for
//                            the ADCn clock as in Table 19-28. See Section 19.4.5.2, "ADC Clock and Conversion
//                            Speed," for details about how to set ADC0/1_CLK_PS.
//                            The ADCn_CLK_PS field must only be written when the ADCn_EN bit is negated. This field
//                            can be configured during the same write cycle used to set ADCn_EN.
// 
//=============================================================================
typedef struct ADC_CR_F_Tag
{
   bitfield16_t  EN      :  BIT_1;   // Bit  0
   bitfield16_t          :  BIT_3;   // Bit  [1:3]
   bitfield16_t  EMUX    :  BIT_1;   // Bit  4
   bitfield16_t          :  BIT_1;   // Bits 5
   bitfield16_t  TBSEL   :  BIT_2;   // Bits [6:7]
   bitfield16_t  ODD_PS  :  BIT_1;   // Bits 8
   bitfield16_t  CLK_DTY :  BIT_1;   // Bits 9
   bitfield16_t  CLK_SEL :  BIT_1;   // Bit  10
   bitfield16_t  CLK_PS  :  BIT_5;   // Bit  [11:15]

}  ADC_CR_F_T;

typedef union ADC_CR_Tag
{
   ADC_CR_F_T     F;
   uint16_t       U16;

}  ADC_CR_T;

//=============================================================================
// ID - ADC Time Stamp Control Register (ADC_TSCR)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0             [0:11]      Reserved.
// 
// TBC_CLK_PS    [12:15]      Time base counter clock prescaler. Contains the system clock divide factor for the time
//                            base counter. It controls the accuracy of the time stamp. The prescaler is disabled when
//                            TBC_CLK_PS is set to 0b0000.
// 
//=============================================================================
typedef struct ADC_TSCR_F_Tag
{
   bitfield16_t               :  BIT_12;  // Bits [0:11]
   bitfield16_t  TBC_CLK_PS   :  BIT_4;   // Bit  [12:15]

}  ADC_TSCR_F_T;

typedef union ADC_TSCR_Tag
{
   ADC_TSCR_F_T   F;
   uint16_t       U16;

}  ADC_TSCR_T;

//=============================================================================
// ID - ADC Time Base Counter Registers (ADC_TBCR)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// TBC_VALUE     [15: 0]      Time base counter VALUE. Contains the current value of the time base counter. Reading
//                            TBC_VALUE returns the current value of time base counter. Writes to TBC_VALUE
//                            register load the written data to the counter. The time base counter counts from 0x0000 to
//                            0xFFFF and wraps when reaching 0xFFFF.
// 
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct ADC_TBCR_F_Tag
{
   bitfield16_t  TBC_VALUE :  BIT_16;  // Bit  [15: 0]

}  ADC_TBCR_F_T;


typedef union ADC_TBCR_Tag
{
   ADC_TBCR_F_T   F;
   uint16_t       U16;

}  ADC_TBCR_T;
//=============================================================================
// ID - ADCn Gain Calibration Constant Registers (ADC0_GCCR and ADC1_GCCR)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            0             Reserved.
// 
// GCCn          [1:15]      ADCn gain calibration constant. Contains the gain calibration constant used to fine-tune
//                            ADCn conversion results. It is a unsigned 15-bit fixed pointed value. The gain calibration
//                            constant is an unsigned fixed point number expressed in the GCC_INT.GCC_FRAC binary
//                            format. The integer part of the gain constant (GCC_INT) contains a single binary digit while
//                            its fractional part (GCC_FRAC) contains 14 digits. For details about the GCC data format
//                            refer to Section 19.4.5.4.2, "MAC Unit and Operand Data Format."
// 
//=============================================================================
typedef struct ADC_GCCR_F_Tag
{
   bitfield16_t         :  BIT_1;   // Bit      0
   bitfield16_t  GCC    :  BIT_15;  // Bits [1:15]

}  ADC_GCCR_F_T;

typedef union ADC_GCCR_Tag
{
   ADC_GCCR_F_T   F;
   uint16_t       U16;

}  ADC_GCCR_T;

//=============================================================================
// ID - ADCn Gain Calibration Constant Registers (ADC0_GCCR and ADC1_GCCR)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0             [0:1]        Reserved.
// 
// OCCn          [2:15]       ADCn offset calibration constant. Contains the offset calibration constant used to
//                            fine-tune ADCn conversion results. Negative values should be expressed using the
//                            two’s complement representation.
// 
//=============================================================================
typedef struct ADC_OCCR_F_Tag
{
   bitfield16_t         :  BIT_2;  // Bits [0:1]
   bitfield16_t  OCC    :  BIT_14; // Bit  [2:15]

}  ADC_OCCR_F_T;

typedef union ADC_OCCR_Tag
{
   ADC_OCCR_F_T   F;
   uint16_t       U16;

}  ADC_OCCR_T;

//=============================================================================
// ID - ADCn Alternate Configuration 1-8 Control Registers(ADC_ACR1-8)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
//RET_INH        0        rw  Result Transfer Inhibit / Decimation Filter Pre-Fill
//                            This bit is used to inhibit the transfer of the 
//                            result data from the peripheral module to the result
//                            queue When the module is a Decimation Filter, this 
//                            bit sets the filter in a special mode (PRE-FILL) in 
//                            which it does not generate decimated samples out from
//                            the conversion results received from the EQADC
//                            block, but the conversion samples are used by the 
//                            filter algorithm
//                            1 = No result transfer to result queue / Decimation 
//                                Filter PRE-FILL mode
//                            0 = Result transfer to result queue / Decimation 
//                                Filter in filtering mode
//
//               1         r  reserved
//
//DEST         [2:5]     rw  Conversion Result Destination Selection
//                           The DEST[0:3] field selects the destination of the 
//                           conversion result generated by the Alternate
//                           Conversion Command
// 
//FMTA           6       rw  Conversion Data Format for Alternate Configuration
//                           If the DEST field is not 0b000, the FMTA bit specifies 
//                           how the 12-bit conversion data returned by the
//                           ADCs is formatted into the 16-bit data which is sent 
//                           to the parallel side interface. The same applies
//                           from the data that returns from the side interface 
//                           to be stored in the RFIFOs.
//                           1 = Right justified signed
//                           0 = Right justified unsigned
//
//              7         r  Reserved
//
//RESSEL      [8:9]      rw  ADC Resolution Selection
//                           The RESSEL[0:1] field selects the resolution of the ADC
//                           according to Table
//
//                           RESSEL[0:1]               Definition
//                              00             ADC set to 12-bits resolution
//                              01             ADC set to 10-bits resolution
//                              10             ADC set to 8-bits resolution
//                              11                     Reserved
//
//           [10:11]      r  reserved
//
//ATBSEL     [12:13]     rw  Alternate Command Timebase Selector
//                           The ATBSEL[0:1] field selects the time information to 
//                           be used as timestamp according to Table
//
//                           ATBSEL[0:1]               Definition
//                              00     Selects internally generated time base as time stamp.
//                              01     Selects imported time base 1 indicated by SRV1 bit 
//                                     field of EQADC_REDLCCR register.
//                              10     Selects imported time base 2 indicated by SRV2 bit
//                                     field of EQADC_REDLCCR register.
//                              11                      Reserved
//
//PRE_GAIN  [14:15]      rw  ADC Pre-gain control
//                           The PRE_GAIN[0:1] controls the gain of the ADC input stage by
//                           changing the internal ADC iterations in the gain stage.
//                           The gain is selected according to Table
//
//                           Pre_gain[0:1]          Description
//                               00                   X1 gain
//                               01                   X2 gain
//                               10                   X4 gain
//                               11                   Reserved
//=============================================================================
typedef struct ADC_ACR_F_Tag
{
   bitfield16_t  RET_INH  :  BIT_1; // Bits     0
   bitfield16_t           :  BIT_1; // Bits     1 is reserved
   bitfield16_t  DEST     :  BIT_4; // Bits     [2:5]
   bitfield16_t  FMTA     :  BIT_1; // Bits     6
   bitfield16_t           :  BIT_1; // Bits     7 is reserved
   bitfield16_t  RESSEL   :  BIT_2; // Bits     [8:9]
   bitfield16_t           :  BIT_2; // Bits     [10:11]are reserved
   bitfield16_t  ATBSEL   :  BIT_2; // Bits     [12:13]
   bitfield16_t  PRE_GAIN :  BIT_2; // Bits     [14:15]

}  ADC_ACR_F_T;

typedef union ADC_ACR_Tag
{
   ADC_ACR_F_T   F;
   uint16_t       U16;

}  ADC_ACR_T;

//=============================================================================
// ID - ADC0/1 Alternate Gain Registers(ADC0_AGR1-2 and ADC1_AGR1-2)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
//                0       r    reserved
//
// ALTGCCn      [1:15]    rw   Alternate Gain Calibration Constant
//                             ALTGCC0/1x[0:14] contain the gain calibration 
//                             constants used to fine-tune ADC0/1 conversion
//                             results for alternate configurations 1 and 2.
//                             The gain calibration constants are 15-bit 
//                             unsigned fixed point numbers expressed in the 
//                             GCC_INT.GCC_FRAC binary format. The integer part
//                             of the gain constants (GCC_INT) contain a single
//                             binary digit while their fractional part 
//                            (GCC_FRAC) contain fourteen digits.
// 
//=============================================================================
typedef struct ADC_AGR_F_Tag
{
   bitfield16_t          : BIT_1;  // Bit      15 is Rserved
   bitfield16_t  ALTGCC  : BIT_15; // Bits [14: 0]

}  ADC_AGR_F_T;

typedef union ADC_AGR_Tag
{
   ADC_AGR_F_T    F;
   uint16_t       U16;

}  ADC_AGR_T;

//=============================================================================
// ID - ADC0/1 Alternate Offset Register (ADC0_AOR1-2 and ADC1_AOR1-2)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
//              [0:1]     r   reserved
//
//ALTOCCn       [2:15]    rw  Alternate Offset Calibration Constant
//                            ALTOCC0/1x[0:13] contain the offset calibration 
//                            constants used to fine-tune ADCs conversion results
//                            for alternate configurations 1 or 2. Negative values
//                            should be expressed using the two’s complement
//                            representation.
//=============================================================================
typedef struct ADC_AOR_F_Tag
{
   bitfield16_t          : BIT_2;  // Bit  [15:14] are Rserved
   bitfield16_t  ALTOCC  : BIT_14; // Bits [13: 0]

}  ADC_AOR_F_T;

typedef union ADC_AOR_Tag
{
   ADC_AOR_F_T    F;
   uint16_t       U16;

}  ADC_AOR_T;

//=============================================================================
// ID - ADC Pull Up/Down Control Register x (ADC_PUDCRx, x=0-7)
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
//              [0:1]     r   reserved
//
//CH_PULLn      [2:3]     rw  Channel x Pull Up/Down Control bits
//                            The CH_PULLx[0:1] field controls the pull up/down
//                            configuration of the channel x according to Table
//
//                            CH_PULLx[0:1]          Definition
//                                00       No Pull resistors connected to the channel
//                                01       Pull Up resistor connected to the channel
//                                10       Pull Down resistor connected to the channel
//                                11       Pull Up and Pull Down resistors connected 
//                                         to the channel
//
//              [4:5]      r  reserved
//
//PULL_STRn     [6:7]      rw  Pull Up/Down Strength Control bits of channel x
//                             The PULL_STRx[0:1] bit field defines the strength of the
//                             channel x pull up or down resistors,according to Table
//                             CH_PULLx[0:1]               Definition
//                                  00        No Pull resistors connected to the channel
//                                  01        Pull Up resistor connected to the channel
//                                  10        Pull Down resistor connected to the channel
//                                  11        Pull Up and Pull Down resistors connected
//                                            to the channel
//=============================================================================
typedef struct ADC_PUDCR_F_Tag
{
   bitfield16_t            : BIT_2; // Bit [0:1] are Reserved
   bitfield16_t  CH_PULL   : BIT_2; // Bit [2:3]
   bitfield16_t            : BIT_2; // Bit [4:5] are Reserved
   bitfield16_t  PULL_STR  : BIT_2; // Bit [6:7]
   bitfield16_t            : BIT_8; // Bit [8:15] are Resrved

}  ADC_PUDCR_F_T;

typedef union ADC_PUDCR_Tag
{
   ADC_PUDCR_F_T   F;
   uint16_t        U16;

}  ADC_PUDCR_T;
//=============================================================================
// /------------------------------------------------------------------------
// | ADC Command Messages
// \------------------------------------------------------------------------
//=============================================================================
//=============================================================================
// ID - ADC Conversion Command Message Format for On-Chip ADC Operation
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// EOQ           0         rw End-of-queue. Asserted in the last command of a command queue to indicate to the
//                            eQADC that a scan of the queue is completed. EOQ instructs the eQADC to reset its
//                            current CFIFO transfer counter value (TC_CF) to 0. Depending on the CFIFO mode of
//                            operation, the CFIFO status will also change upon the detection of an asserted EOQ bit on
//                            the last transferred command. See Section 19.4.3.5, CFIFO Scan Trigger Modes, for
//                            details.
//                            0 Not the last entry of the command queue.
//                            1 Last entry of the command queue.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted..
//
// PAUSE        1          rw Pause. Allows software to create sub-queues within a command queue. When the eQADC
//                            completes the transfer of a command with an asserted pause bit, the CFIFO enters the
//                            WAITING FOR TRIGGER state. Refer to Section 19.4.3.6.1, CFIFO Operation Status, for
//                            a description of the state transitions. The pause bit is only valid when CFIFO operation
//                            mode is configured to single or continuous-scan edge trigger mode.
//                            0 Do not enter WAITING FOR TRIGGER state after transfer of the current command message.
//                            1 Enter WAITING FOR TRIGGER state after transfer of the current command message.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted.
//
// 0            [3:4]      r  Reserved.
//
// EB             5        rw External buffer bit. A negated EB bit indicates that the command is sent to an on chip ADC.
//                            0 Command is sent to an internal buffer.
//                            1 Command is sent to an external buffer.
//
// BN             6        rw Buffer number. Indicates which ADC the message will be sent to. ADCs 1 and 0 can either
//                            be internal or external depending on the EB bit setting.
//                            0 Message sent to ADC 0.
//                            1 Message sent to ADC 1.
//
// CAL            7        rw Calibration. Indicates if the returning conversion result must be calibrated.
//                            0 Do not calibrate conversion result.
//                            1 Calibrate conversion result.
//
// MESSAGE_TAG  [8:11]     rw MESSAGE_TAG field. Allows the eQADC to separate returning results into different
//                            the eQADC transfers a command, the MESSAGE_TAG is included as part
//                            of the command. Eventually the external device/on-chip ADC returns the result with the
//                            same MESSAGE_TAG. The eQADC separates incoming messages into different RFIFOs
//                            by decoding the MESSAGE_TAG of the incoming data.
//
//                               MESSAGE_TAG[0:3]  MESSAGE_TAG Meaning
//                               0b0000            Result is sent to RFIFO 0
//                               0b0001            Result is sent to RFIFO 1
//                               0b0010            Result is sent to RFIFO 2
//                               0b0011            Result is sent to RFIFO 3
//                               0b0100            Result is sent to RFIFO 4
//                               0b0101            Result is sent to RFIFO 5
//                               0b0110            0b0111 Reserved
//                               0b1000            Null message received
//                               0b1001            Reserved for customer use.(1)
//                               0b1010            Reserved for customer use.(1)
//                               0b1011-0b1111     Reserved
//
//                           (1) These messages are treated as null messages. Therefore, they must obey the
//                               format for incoming null messages and return valid BUSY0/1 fields. Refer to
//                               Section , " Null Message Format for External Device Operation."
//
// LST         [12:13]     rw Long sampling time. These two bits determine the duration of the sampling time in ADC
//                            clock cycles.
//                            Note: For external mux mode, 64 or 128 sampling cycles is recommended.
//
//                               LST[0:1]          Sampling cycles
//                                                 (ADC Clock Cycles)
//                               0b00                2
//                               0b01                8
//                               0b10               64
//                               0b11              128
//
// TSR           14       rw Time stamp request. TSR indicates the request for a time stamp. When TSR is asserted,
//                            the on-chip ADC control logic returns a time stamp for the current conversion command
//                            after the conversion result is sent to the RFIFOs. See Section 19.4.5.3, Time Stamp
//                            Feature, for details.
//                            0 Return conversion result only.
//                            1 Return conversion time stamp after the conversion result.
//
// FMT           15        rw Conversion data format. FMT specifies to the eQADC how to format the 12-bit conversion
//                            data returned by the ADCs into the 16-bit format which is sent to the RFIFOs. See Section ,
//                            " ADC Result Format for On-Chip ADC Operation," for details.
//                            0 Right justified unsigned.
//                            1 Right justified signed.
//
// CHANNEL      [16:23]    rw Channel number. Selects the analog input channel. The software programs this field with
//                            the channel number corresponding to the analog input pin to be sampled and converted.
//                            See Section 19.4.6.1, "Channel Assignment," for details.
//
// 0            [24:31]    r  Reserved.
//
//=============================================================================
typedef struct ADC_CCMF_F_Tag
{
   bitfield32_t  EOQ         :  BIT_1;   // Bit       0
   bitfield32_t  PAUSE       :  BIT_1;   // Bit       1
   bitfield32_t  REP         :  BIT_1;   // Bit       2
   bitfield32_t              :  BIT_2;   // Bit    [3:4]
   bitfield32_t  EB          :  BIT_1;   // Bit       5
   bitfield32_t  BN          :  BIT_1;   // Bit       6
   bitfield32_t  CAL         :  BIT_1;   // Bit       7
   bitfield32_t  MESSAGE_TAG :  BIT_4;   // Bit   [8:11]
   bitfield32_t  LST         :  BIT_2;   // Bits [12:13]
   bitfield32_t  TSR         :  BIT_1;   // Bit      14
   bitfield32_t  FFMT         :  BIT_1;   // Bit      15
   bitfield32_t  CHANNEL     :  BIT_8;   // Bit   [16:23]
   bitfield32_t ALT_CFG_SEL   :  BIT_8;   // Bits  [24:31]

}  ADC_CCMF_F_T;

//=============================================================================
// ID - ADC Command Message Format for External Device Operation
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// EOQ           0        rw  End-of-queue. Asserted in the last command of a command queue to indicate to the
//                            eQADC that a scan of the queue is completed. EOQ instructs the eQADC to reset its
//                            current CFIFO transfer counter value (TC_CF) to 0. Depending on the CFIFO mode of
//                            operation, the CFIFO status will also change upon the detection of an asserted EOQ bit on
//                            the last transferred command. See Section 19.4.3.5, CFIFO Scan Trigger Modes, for
//                            details.
//                            0 Not the last entry of the command queue.
//                            1 Last entry of the command queue.
//                             Note: If both the pause and EOQ bits are asserted in the same command message the
//                             respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                             asserted..
//
// PAUSE         1       rw    Pause. Allows software to create sub-queues within a command queue. When the eQADC
//                             completes the transfer of a command with an asserted pause bit, the CFIFO enters the
//                             WAITING FOR TRIGGER state. Refer to Section 19.4.3.6.1, CFIFO Operation Status, for
//                             a description of the state transitions. The pause bit is only valid when CFIFO operation
//                             mode is configured to single or continuous-scan edge trigger mode.
//                             0 Do not enter WAITING FOR TRIGGER state after transfer of the current command message.
//                             1 Enter WAITING FOR TRIGGER state after transfer of the current command message.
//                             Note: If both the pause and EOQ bits are asserted in the same command message the
//                             respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                             asserted.
//
// 0           [2:3]      rw  Reserved.
//
// ABORT_ST     4         rw  ABORT serial transmission. Indicates whether an on-going serial transmission
//                             should be aborted or not. All CFIFOs can abort null message transmissions when
//                             triggered but only CFIFO0 can abort command transmissions of lower priority
//                             CFIFOs. For more on serial transmission aborts see Section 19.4.3.2, "CFIFO
//                             Prioritization and Command Transfer."
//                             0 Do not abort current serial transmission.
//                             1 Abort current serial transmission.
//
// EB           5          rw  External buffer bit. A negated EB bit indicates that the command is sent to an on chip ADC.
//                             0 Command is sent to an internal buffer.
//                             1 Command is sent to an external buffer.
//
// BN           6          rw  Buffer number. Indicates which ADC the message will be sent to. ADCs 1 and 0 can either
//                             be internal or external depending on the EB bit setting.
//                             0 Message sent to ADC 0.
//                             1 Message sent to ADC 1.
//
// COMMAND     [7:31]      rw  OFF-CHIP COMMAND Field. The OFF_CHIP_COMMAND field can be anything
//                             decodable by the external device. It is 25 bits long and it is transferred together with
//                             the BN bit to the external device when the CFIFO is triggered. Refer to Section ,
//                             " Conversion Command Message Format for On-Chip ADC Operation," for a
//                             description of the command message used when interfacing with the on-chip ADCs.
//
//=============================================================================
typedef struct ADC_CCMF_EXT_F_Tag
{
   bitfield32_t  EOQ         :  BIT_1;   // Bit       0
   bitfield32_t  PAUSE       :  BIT_1;   // Bit       1
   bitfield32_t              :  BIT_2;   // Bit       [2:3]
   bitfield32_t  ABORT_ST    :  BIT_1;   // Bit       4
   bitfield32_t  EB          :  BIT_1;   // Bit       5
   bitfield32_t  BN          :  BIT_1;   // Bit       6
   bitfield32_t  COMMAND     :  BIT_25;  // Bit       [7:31]

}  ADC_CCMF_EXT_F_T;

//=============================================================================
// ID - ADC Conversion Command Message Format for Alternate Configuration On-Chip ADC Operation
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// EOQ           0         rw End-of-queue. Asserted in the last command of a command queue to indicate to the
//                            eQADC that a scan of the queue is completed. EOQ instructs the eQADC to reset its
//                            current CFIFO transfer counter value (TC_CF) to 0. Depending on the CFIFO mode of
//                            operation, the CFIFO status will also change upon the detection of an asserted EOQ bit on
//                            the last transferred command. See Section 19.4.3.5, CFIFO Scan Trigger Modes, for
//                            details.
//                            0 Not the last entry of the command queue.
//                            1 Last entry of the command queue.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted..
//
// PAUSE        1          rw Pause. Allows software to create sub-queues within a command queue. When the eQADC
//                            completes the transfer of a command with an asserted pause bit, the CFIFO enters the
//                            WAITING FOR TRIGGER state. Refer to Section 19.4.3.6.1, CFIFO Operation Status, for
//                            a description of the state transitions. The pause bit is only valid when CFIFO operation
//                            mode is configured to single or continuous-scan edge trigger mode.
//                            0 Do not enter WAITING FOR TRIGGER state after transfer of the current command message.
//                            1 Enter WAITING FOR TRIGGER state after transfer of the current command message.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted.
//
// 0            [3:4]      r  Reserved.
//
// EB             5        rw External buffer bit. A negated EB bit indicates that the command is sent to an on chip ADC.
//                            0 Command is sent to an internal buffer.
//                            1 Command is sent to an external buffer.
//
// BN             6        rw Buffer number. Indicates which ADC the message will be sent to. ADCs 1 and 0 can either
//                            be internal or external depending on the EB bit setting.
//                            0 Message sent to ADC 0.
//                            1 Message sent to ADC 1.
//
// CAL            7        rw Calibration. Indicates if the returning conversion result must be calibrated.
//                            0 Do not calibrate conversion result.
//                            1 Calibrate conversion result.
//
// MESSAGE_TAG  [8:11]     rw MESSAGE_TAG field. Allows the eQADC to separate returning results into different
//                            the eQADC transfers a command, the MESSAGE_TAG is included as part
//                            of the command. Eventually the external device/on-chip ADC returns the result with the
//                            same MESSAGE_TAG. The eQADC separates incoming messages into different RFIFOs
//                            by decoding the MESSAGE_TAG of the incoming data.
//
//                               MESSAGE_TAG[0:3]  MESSAGE_TAG Meaning
//                               0b0000            Result is sent to RFIFO 0
//                               0b0001            Result is sent to RFIFO 1
//                               0b0010            Result is sent to RFIFO 2
//                               0b0011            Result is sent to RFIFO 3
//                               0b0100            Result is sent to RFIFO 4
//                               0b0101            Result is sent to RFIFO 5
//                               0b0110            0b0111 Reserved
//                               0b1000            Null message received
//                               0b1001            Reserved for customer use.(1)
//                               0b1010            Reserved for customer use.(1)
//                               0b1011-0b1111     Reserved
//
//                           (1) These messages are treated as null messages. Therefore, they must obey the
//                               format for incoming null messages and return valid BUSY0/1 fields. Refer to
//                               Section , " Null Message Format for External Device Operation."
//
// LST         [12:13]     rw Long sampling time. These two bits determine the duration of the sampling time in ADC
//                            clock cycles.
//                            Note: For external mux mode, 64 or 128 sampling cycles is recommended.
//
//                               LST[0:1]          Sampling cycles
//                                                 (ADC Clock Cycles)
//                               0b00                2
//                               0b01                8
//                               0b10               64
//                               0b11              128
//
// TSR           14       rw Time stamp request. TSR indicates the request for a time stamp. When TSR is asserted,
//                            the on-chip ADC control logic returns a time stamp for the current conversion command
//                            after the conversion result is sent to the RFIFOs. See Section 19.4.5.3, Time Stamp
//                            Feature, for details.
//                            0 Return conversion result only.
//                            1 Return conversion time stamp after the conversion result.
//
// FMT           15        rw Conversion data format. FMT specifies to the eQADC how to format the 12-bit conversion
//                            data returned by the ADCs into the 16-bit format which is sent to the RFIFOs. See Section ,
//                            " ADC Result Format for On-Chip ADC Operation," for details.
//                            0 Right justified unsigned.
//                            1 Right justified signed.
//
// CHANNEL      [16:23]    rw Channel number. Selects the analog input channel. The software programs this field with
//                            the channel number corresponding to the analog input pin to be sampled and converted.
//                            See Section 19.4.6.1, "Channel Assignment," for details.
//
// REG_ADDRESS   [24:31]   rw ADC register address. Selects a register on the ADC register set to be used.
//
//                                 ADC0
//                               Register
//                               Address     USE                                                   ACCESS
//                               0x00 ADC0   Address 0x00 is used for conversion command
//                                           messages.
//                               0x01        ADC0   Control Register (ADC0_CR)                     Write/Read
//                               0x02        ADC Time Stamp Control Register (ADC_TSCR) (1)        Write/Read
//                               0x03        ADC Time Base Counter Register (ADC_TBCR) (1)         Write/Read
//                               0x04        ADC0 Gain Calibration Constant Register (ADC0_GCCR)   Write/Read
//                               0x05        ADC0 Offset Calibration Constant Register (ADC0_OCCR) Write/Read
//                               0x06-0xFF   Reserved -
//
//                           (1) This register is also accessible by configuration commands sent to the ADC1 command buffer.
//
//=============================================================================
typedef struct ADC_CCMF_AC_F_Tag
{
   bitfield32_t  EOQ         :  BIT_1;   // Bit       0
   bitfield32_t  PAUSE       :  BIT_1;   // Bit       1
   bitfield32_t  REP         :  BIT_1;   // Bit       2
   bitfield32_t              :  BIT_2;   // Bit    [3:4]
   bitfield32_t  EB          :  BIT_1;   // Bit       5
   bitfield32_t  BN          :  BIT_1;   // Bit       6
   bitfield32_t  CAL         :  BIT_1;   // Bit       7
   bitfield32_t  MESSAGE_TAG :  BIT_4;   // Bit   [8:11]
   bitfield32_t  LST         :  BIT_2;   // Bits [12:13]
   bitfield32_t  TSR         :  BIT_1;   // Bit      14
   bitfield32_t  FMT         :  BIT_1;   // Bit      15
   bitfield32_t  CHANNEL     :  BIT_8;   // Bit   [16:23]
   bitfield32_t  REG_ADDRESS :  BIT_8;   // Bits  [24:31]

}  ADC_CCMF_AC_F_T;


//=============================================================================
// ID - ADC Write Configuration Command Message Format for On-Chip ADC Operation
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// EOQ             0       rw End-of-queue. Asserted in the last command of a command queue to indicate to the
//                            eQADC that a scan of the queue is completed. EOQ instructs the eQADC to reset its
//                            current CFIFO transfer counter value (TC_CF) to 0. Depending on the CFIFO mode of
//                            operation, the CFIFO status will also change upon the detection of an asserted EOQ bit on
//                            the last transferred command. See Section 19.4.3.5, CFIFO Scan Trigger Modes, for
//                            details.
//                            0 Not the last entry of the command queue.
//                            1 Last entry of the command queue.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted..
//
// PAUSE          1        rw Pause. Allows software to create sub-queues within a command queue. When the eQADC
//                            completes the transfer of a command with an asserted pause bit, the CFIFO enters the
//                            WAITING FOR TRIGGER state. Refer to Section 19.4.3.6.1, CFIFO Operation Status, for
//                            a description of the state transitions. The pause bit is only valid when CFIFO operation
//                            mode is configured to single or continuous-scan edge trigger mode.
//                            0 Do not enter WAITING FOR TRIGGER state after transfer of the current command message.
//                            1 Enter WAITING FOR TRIGGER state after transfer of the current command message.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted.
//
//REP             2       rw  Repeat/loop Start Point Indication Bit
//
// 0             [3:4]        r  Reserved.
//
// EB             5        rw External buffer bit. A negated EB bit indicates that the command is sent to an on chip ADC.
//                            0 Command is sent to an internal buffer.
//                            1 Command is sent to an external buffer.
//
// BN             6        rw Buffer number. Indicates which ADC the message will be sent to. ADCs 1 and 0 can either
//                            be internal or external depending on the EB bit setting.
//                            0 Message sent to ADC 0.
//                            1 Message sent to ADC 1.
//
// R_W            7        rw Read/write. A negated R/W indicates a write configuration command.
//                            0 Write.
//                            1 Read.
//
// REG_DATA      [8:23]   r w ADC register. The value to be written into the
//                            control/configuration register when the R/W bit is negated.
//
// REG_ADDRESS   [24:31]   rw ADC register address. Selects a register on the ADC register set to be written or read. Only
//                            half-word addresses can be used.
//
//                                 ADC0
//                               Register
//                               Address     USE                                                   ACCESS
//                               0x00 ADC0   Address 0x00 is used for conversion command
//                                           messages.
//                               0x01        ADC0   Control Register (ADC0_CR)                     Write/Read
//                               0x02        ADC Time Stamp Control Register (ADC_TSCR) (1)        Write/Read
//                               0x03        ADC Time Base Counter Register (ADC_TBCR) (1)         Write/Read
//                               0x04        ADC0 Gain Calibration Constant Register (ADC0_GCCR)   Write/Read
//                               0x05        ADC0 Offset Calibration Constant Register (ADC0_OCCR) Write/Read
//                               0x06-0xFF   Reserved -
//
//                           (1) This register is also accessible by configuration commands sent to the ADC1 command buffer.
//
//=============================================================================
typedef struct ADC_WCCMF_F_Tag
{
   bitfield32_t  EOQ         :  BIT_1;   // Bit       0
   bitfield32_t  PAUSE       :  BIT_1;   // Bit       1
   bitfield32_t  REP         :  BIT_1;   // Bit       2
   bitfield32_t              :  BIT_2;   // Bit   [3:4]
   bitfield32_t  EB          :  BIT_1;   // Bit       5
   bitfield32_t  BN          :  BIT_1;   // Bit       6
   bitfield32_t  R_W         :  BIT_1;   // Bit       7
   bitfield32_t  REG_DATA    :  BIT_16;  // Bit   [8:23]
   bitfield32_t  REG_ADDRESS :  BIT_8;   // Bits  [24:31]

}  ADC_WCCMF_F_T;

//=============================================================================
// ID - ADC Read Configuration Command Message Format for On-Chip ADC Operation
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// EOQ               0     rw End-of-queue. Asserted in the last command of a command queue to indicate to the
//                            eQADC that a scan of the queue is completed. EOQ instructs the eQADC to reset its
//                            current CFIFO transfer counter value (TC_CF) to 0. Depending on the CFIFO mode of
//                            operation, the CFIFO status will also change upon the detection of an asserted EOQ bit on
//                            the last transferred command. See Section 19.4.3.5, CFIFO Scan Trigger Modes, for
//                            details.
//                            0 Not the last entry of the command queue.
//                            1 Last entry of the command queue.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted..
//
// PAUSE             1     rw Pause. Allows software to create sub-queues within a command queue. When the eQADC
//                            completes the transfer of a command with an asserted pause bit, the CFIFO enters the
//                            WAITING FOR TRIGGER state. Refer to Section 19.4.3.6.1, CFIFO Operation Status, for
//                            a description of the state transitions. The pause bit is only valid when CFIFO operation
//                            mode is configured to single or continuous-scan edge trigger mode.
//                            0 Do not enter WAITING FOR TRIGGER state after transfer of the current command message.
//                            1 Enter WAITING FOR TRIGGER state after transfer of the current command message.
//                               Note: If both the pause and EOQ bits are asserted in the same command message the
//                               respective flags are set, but the CFIFO status changes as if only the EOQ bit were
//                               asserted.
//
// REP              2     rw Repeat/loop Start Point Indication Bit
// 0             [3:4]    r  Reserved.
//
// EB                5    rw External buffer bit. A negated EB bit indicates that the command is sent to an on chip ADC.
//                            0 Command is sent to an internal buffer.
//                            1 Command is sent to an external buffer.
//
// BN                6    rw Buffer number. Indicates which ADC the message will be sent to. ADCs 1 and 0 can either
//                            be internal or external depending on the EB bit setting.
//                            0 Message sent to ADC 0.
//                            1 Message sent to ADC 1.
//
// R_W               7    rw Read/write. A negated R/W indicates a write configuration command.
//                            0 Write.
//                            1 Read.
//
// MESSAGE_TAG   [8:11]    rw MESSAGE_TAG field. Allows the eQADC to separate returning results into different
//                            the eQADC transfers a command, the MESSAGE_TAG is included as part
//                            of the command. Eventually the external device/on-chip ADC returns the result with the
//                            same MESSAGE_TAG. The eQADC separates incoming messages into different RFIFOs
//                            by decoding the MESSAGE_TAG of the incoming data.
//
//                               MESSAGE_TAG[0:3]  MESSAGE_TAG Meaning
//                               0b0000            Result is sent to RFIFO 0
//                               0b0001            Result is sent to RFIFO 1
//                               0b0010            Result is sent to RFIFO 2
//                               0b0011            Result is sent to RFIFO 3
//                               0b0100            Result is sent to RFIFO 4
//                               0b0101            Result is sent to RFIFO 5
//                               0b0110            0b0111 Reserved
//                               0b1000            Null message received
//                               0b1001            Reserved for customer use.(1)
//                               0b1010            Reserved for customer use.(1)
//                               0b1011-0b1111     Reserved
//
//                           (1) These messages are treated as null messages. Therefore, they must obey the
//                               format for incoming null messages and return valid BUSY0/1 fields. Refer to
//                               Section , " Null Message Format for External Device Operation."
//
// reserved      [12:23]   rw ADC register. The value to be written into the
//                            control/configuration register when the R/W bit is negated.
//
// REG_ADDRESS   [24:31]   rw ADC register address. Selects a register on the ADC register set to be written or read. Only
//                            half-word addresses can be used.
//
//                                 ADC0
//                               Register
//                               Address     USE                                                   ACCESS
//                               0x00 ADC0   Address 0x00 is used for conversion command
//                                           messages.
//                               0x01        ADC0   Control Register (ADC0_CR)                     Write/Read
//                               0x02        ADC Time Stamp Control Register (ADC_TSCR) (1)        Write/Read
//                               0x03        ADC Time Base Counter Register (ADC_TBCR) (1)         Write/Read
//                               0x04        ADC0 Gain Calibration Constant Register (ADC0_GCCR)   Write/Read
//                               0x05        ADC0 Offset Calibration Constant Register (ADC0_OCCR) Write/Read
//                               0x06-0xFF   Reserved -
//
//                           (1) This register is also accessible by configuration commands sent to the ADC1 command buffer.
//
//=============================================================================
typedef struct ADC_RCCMF_F_Tag
{
   bitfield32_t  EOQ         :  BIT_1;   // Bit       0
   bitfield32_t  PAUSE       :  BIT_1;   // Bit       1
   bitfield32_t  REP         :  BIT_1;   // Bit       2
   bitfield32_t              :  BIT_2;   // Bit   [3:4]
   bitfield32_t  EB          :  BIT_1;   // Bit       5
   bitfield32_t  BN          :  BIT_1;   // Bit       6
   bitfield32_t  R_W         :  BIT_1;   // Bit       7
   bitfield32_t  MESSAGE_TAG :  BIT_4;   // Bit   [8:11]
   bitfield32_t              :  BIT_12;  // Bit   [12:23]
   bitfield32_t  REG_ADDRESS :  BIT_8;   // Bits  [24:31]

}  ADC_RCCMF_F_T;

//=============================================================================
// Command Message Format
//=============================================================================
typedef union ADC_CCMF_Tag
{
   ADC_CCMF_F_T         CF;
   uint32_t             U32;

}  ADC_CCMF_T;


//=============================================================================
// Command Message Format
//=============================================================================
typedef union ADC_CMF_Tag
{
   ADC_CCMF_F_T         CF;
   ADC_CCMF_AC_F_T      AC_CF;
   ADC_CCMF_EXT_F_T     EF;
   ADC_WCCMF_F_T        WF;
   ADC_RCCMF_F_T        RF;
   uint32_t             U32;

}  ADC_CMF_T;


#endif // HW_ADC_H

