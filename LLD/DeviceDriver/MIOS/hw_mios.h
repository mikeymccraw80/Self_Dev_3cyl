#ifndef HW_MIOS_H
#define HW_MIOS_H

#include "reuse.h"
#define MIOS_RESERVED_0002 (0x0002)
//wic Bit masks
#define MIOS_CSR_FLAG_CLEAR_MASK   (0x7FFF7FFFUL)
#define MIOS_CSR_OVR_CLEAR_MASK    (0xFFFF7FFEUL)
#define MIOS_CSR_OVFL_CLEAR_MASK   (0x7FFFFFFEUL)
#define MIOS_RESERVED_F38   (0xF38)
//=============================================================================
// ID - MIOS Module Configuration Register (MIOS_MCR)
// Base Offset: Base + 0x00
// Reset Value: 0000 0000 H
//
// MIOS_MCR contains global control bits for the MIOS module.
//
// Field           Bits  Type  Description
// ========== ========== ==== ==============================================
// DOZEEN           31    rw  Doze Enable bit. Enables the eMIOS200 module to
//                            enter low power mode when Doze Mode is requested
//                            at the MCU level. The doze mode is used to stop 
//                            the clock to the module except access to the MCR
//                            OUDR and UCDIS (registers.
//                            0 Enable entry to low power mode when Doze 
//                              Mode is requested
//                            1 Not enable to enter low power mode when Doze
//                              Mode is requested
//
// MDIS             30    rw  Module disable. Puts the eMIOS in low power
//                            mode. The MDIS bit is used to stop the clock
//                            of the block, except the access to registers
//                            MTSMCR, MTSOUDIS and MTSUCDIS.
//
//                              0 Clock is running
//                              1 Enter low power mode
//
// FRZ              29    rw  Freeze. Enables the eMIOS to freeze the
//                            registers of the Unified Channels when Debug
//                            Mode is requested at MCU level. Each Unified
//                            Channel should have FREN bit set in order to
//                            enter freeze mode. While in Freeze mode, the
//                            eMIOS continues to operate to allow the MCU
//                            access to the Unified Channels registers. The
//                            Unified Channel will remain frozen until the
//                            FRZ bit is written to zero or the MCU exits
//                            Debug mode or the Unified Channel FREN bit
//                            is cleared.
//
//                              0 Exit freeze mode
//                              1 Stops Unified Channels operation when in
//                                Debug mode and the FREN bit is set in the
//                                MTSCn register
//
// GTBE             28    rw  Global time base enable. Used to export a
//                            Global Time Base Enable from the module and
//                            provide a method to start time bases of
//                            several blocks simultaneously.
//
//                              0 Global Time Base Enable Out signal negated
//                              1 Global Time Base Enable Out signal
//                                asserted
//
//                            NOTE: The Global Time Base Enable input pin
//                                  controls the internal counters. When
//                                  asserted, Internal counters are enabled.
//                                  When negated, Internal counters disabled.
//
// ETB              27    rw  External time base. Selects the time base
//                            source that drives counter bus[A].
//
//                              0 Counter bus[A] assigned to Unified Channel
//                              1 Counter bus[A] assigned to REDC
//
// GPREN            26    rw  Global prescaler enable. Enables the prescaler
//                            counter.
//
//                              0 Prescaler disabled (no clock) and
//                                prescaler counter is cleared
//                              1 Prescaler enabled
//
// 0            [25:20]    r  Reserved, should be cleared.
//
// SRV          [19:16]   rw  Server time slot. Selects the address of a
//                            specific STAC server to which the REDC is
//                            assigned.
//
// GPRE         [15: 8]   rw  Global Prescaler. Selects the clock divider
//                            value for the global prescaler, as shown in
//                            Table.
//
//                              Global Prescaler Clock Divider
//
//                             GPRE[7:0]             Divide ratio
//
//                             00000000                1
//                             00000001                2
//                             00000010                3
//                             00000011                4
//                               .                     .
//                               .                     .
//                               .                     .
//                             11111110                255
//                             11111111                256
//
// 0            [ 7: 0]    r  Reserved, should be cleared.
//
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct MIOS_MCR_F_Tag
{
   bitfield32_t   DOZEEN :  BIT_1;   // Bit      31
   bitfield32_t   MDIS   :  BIT_1;   // Bit      30
   bitfield32_t   FRZ    :  BIT_1;   // Bit      29
   bitfield32_t   GTBE   :  BIT_1;   // Bit      28
   bitfield32_t   ETB    :  BIT_1;   // Bit      27
   bitfield32_t   GPREN  :  BIT_1;   // Bit      26
   bitfield32_t          :  BIT_6;   // Bit  [25:20]
   bitfield32_t   SRV    :  BIT_4;   // Bits [19:16]
   bitfield32_t   GPRE   :  BIT_8;   // Bits [15: 8]
   bitfield32_t          :  BIT_8;   // Bits [ 7: 0] are reserved

}  MIOS_MCR_F_T;

typedef union MIOS_MCR_Tag 
{
   MIOS_MCR_F_T   F;
   uint32_t       U32;

}  MIOS_MCR_T;
//=============================================================================
// ID - MIOS Global Flag Register (MIOS_GFR)
// Base Offset: Base + 0x04
// Reset Value: 0000 0000 H
//
// The MIOS_GFR is a read-only register that groups the FLAG bits from all 
// channels. This organization improves interrupt handling on simpler devices. 
// These bits are mirrors of the FLAG bits of each channel register (MIOS_CSR) 
// and flag bits in those channel registers cannot be cleared by accessing this 
// ‘mirror’ register.
//
// Field         Bits    Type  Description
// ========== ========== ==== ==============================================
//              [31-24]   r   Reserved
//
// FLAG         [23: 0]    r  The GFLAG is a read-only register that
//                            groups the FLAG bits from all channels. This
//                            organization improves interrupt handling on
//                            simpler devices. These bits are mirrors of the
//                            FLAG bits of each channel register.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct MIOS_GFR_F_Tag
{
   bitfield32_t         :  BIT_8;   // Bit   31-24
   bitfield32_t   F23   :  BIT_1;   // Bit   23
   bitfield32_t   F22   :  BIT_1;   // Bit   22
   bitfield32_t   F21   :  BIT_1;   // Bit   21
   bitfield32_t   F20   :  BIT_1;   // Bit   20
   bitfield32_t   F19   :  BIT_1;   // Bit   19
   bitfield32_t   F18   :  BIT_1;   // Bit   18
   bitfield32_t   F17   :  BIT_1;   // Bit   17
   bitfield32_t   F16   :  BIT_1;   // Bit   16
   bitfield32_t   F15   :  BIT_1;   // Bit   15
   bitfield32_t   F14   :  BIT_1;   // Bit   14
   bitfield32_t   F13   :  BIT_1;   // Bit   13
   bitfield32_t   F12   :  BIT_1;   // Bit   12
   bitfield32_t   F11   :  BIT_1;   // Bit   11
   bitfield32_t   F10   :  BIT_1;   // Bit   10
   bitfield32_t   F9    :  BIT_1;   // Bit    9
   bitfield32_t   F8    :  BIT_1;   // Bit    8
   bitfield32_t   F7    :  BIT_1;   // Bit    7
   bitfield32_t   F6    :  BIT_1;   // Bit    6
   bitfield32_t   F5    :  BIT_1;   // Bit    5
   bitfield32_t   F4    :  BIT_1;   // Bit    4
   bitfield32_t   F3    :  BIT_1;   // Bit    3
   bitfield32_t   F2    :  BIT_1;   // Bit    2
   bitfield32_t   F1    :  BIT_1;   // Bit    1
   bitfield32_t   F0    :  BIT_1;   // Bit    0

}  MIOS_GFR_F_T;

typedef union MIOS_GFR_Tag 
{
   MIOS_GFR_F_T   F;
   uint32_t       U32;

}  MIOS_GFR_T;

//=============================================================================
// ID - MIOS Output Update Disable Register (MIOS_OUDR)
// Base Offset: Base + 0x08
// Reset Value: 0000 0000 H
//
// The MIOS_OUDR serves to disable transfers from the A1 to the A2 channel 
// registers and from the B1 to the B2 channel registers when values are written 
// to these registers, and the channel is running in modulus counter (MC) mode 
// or an output mode.
//
// Field         Bits    Type  Description
// ========== ========== ==== ==============================================
//              [31-24]   r   Reserved
//
// OUn          [23:00]   rw  Channel n output update disable. When running
//                            MC mode or an output mode, values are written
//                            to registers A2 and B2. OUn bits are used to
//                            disable transfers from registers A2 to A1 and
//                            B2 to B1. Each bit controls one channel.
//
//                              0 Transfer enabled. Depending on the
//                                operation mode, transfer may occur
//                                immediately or in the next period. Unless
//                                stated otherwise, transfer occurs
//                                immediately.
//
//                              1 Transfers disabled
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct MIOS_OUDR_F_Tag
{
   bitfield32_t         :  BIT_8;   // Bit   31-24
   bitfield32_t   OU23  :  BIT_1;   // Bit   23
   bitfield32_t   OU22  :  BIT_1;   // Bit   22
   bitfield32_t   OU21  :  BIT_1;   // Bit   21
   bitfield32_t   OU20  :  BIT_1;   // Bit   20
   bitfield32_t   OU19  :  BIT_1;   // Bit   19
   bitfield32_t   OU18  :  BIT_1;   // Bit   18
   bitfield32_t   OU17  :  BIT_1;   // Bit   17
   bitfield32_t   OU16  :  BIT_1;   // Bit   16
   bitfield32_t   OU15  :  BIT_1;   // Bit   15
   bitfield32_t   OU14  :  BIT_1;   // Bit   14
   bitfield32_t   OU13  :  BIT_1;   // Bit   13
   bitfield32_t   OU12  :  BIT_1;   // Bit   12
   bitfield32_t   OU11  :  BIT_1;   // Bit   11
   bitfield32_t   OU10  :  BIT_1;   // Bit   10
   bitfield32_t   OU9   :  BIT_1;   // Bit    9
   bitfield32_t   OU8   :  BIT_1;   // Bit    8
   bitfield32_t   OU7   :  BIT_1;   // Bit    7
   bitfield32_t   OU6   :  BIT_1;   // Bit    6
   bitfield32_t   OU5   :  BIT_1;   // Bit    5
   bitfield32_t   OU4   :  BIT_1;   // Bit    4
   bitfield32_t   OU3   :  BIT_1;   // Bit    3
   bitfield32_t   OU2   :  BIT_1;   // Bit    2
   bitfield32_t   OU1   :  BIT_1;   // Bit    1
   bitfield32_t   OU0   :  BIT_1;   // Bit    0

}  MIOS_OUDR_F_T;

typedef union MIOS_OUDR_Tag 
{
   MIOS_OUDR_F_T  F;
   uint32_t       U32;
}  MIOS_OUDR_T;

//=============================================================================
// ID - eMIOS200 Channel Disable (UCDIS)
// Base Offset: EMIOS_BASE (0xC3FA_0000) + 0x000C
// Reset Value: 0000 0000 H
//
// Field         Bits    Type  Description
// ========== ========== ==== ==============================================
//              [31:24]    r  Reserved.
//
// A            [23-00]   rw  CHDIS[n] — Disable Channel [n] bit
//                            The CHDIS[n] bit is used to disable a channel 
//                            by stopping its respective clock.
//                            0 Channel [n]  enabled
//                            1 Channel [n] disabled
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef struct MIOS_UCDIS_F_Tag
{
   bitfield32_t            :  BIT_8;   // Bit   31-24
   bitfield32_t   CHDIS23  :  BIT_1;   // Bit   23
   bitfield32_t   CHDIS22  :  BIT_1;   // Bit   22
   bitfield32_t   CHDIS21  :  BIT_1;   // Bit   21
   bitfield32_t   CHDIS20  :  BIT_1;   // Bit   20
   bitfield32_t   CHDIS19  :  BIT_1;   // Bit   19
   bitfield32_t   CHDIS18  :  BIT_1;   // Bit   18
   bitfield32_t   CHDIS17  :  BIT_1;   // Bit   17
   bitfield32_t   CHDIS16  :  BIT_1;   // Bit   16
   bitfield32_t   CHDIS15  :  BIT_1;   // Bit   15
   bitfield32_t   CHDIS14  :  BIT_1;   // Bit   14
   bitfield32_t   CHDIS13  :  BIT_1;   // Bit   13
   bitfield32_t   CHDIS12  :  BIT_1;   // Bit   12
   bitfield32_t   CHDIS11  :  BIT_1;   // Bit   11
   bitfield32_t   CHDIS10  :  BIT_1;   // Bit   10
   bitfield32_t   CHDIS9   :  BIT_1;   // Bit    9
   bitfield32_t   CHDIS8   :  BIT_1;   // Bit    8
   bitfield32_t   CHDIS7   :  BIT_1;   // Bit    7
   bitfield32_t   CHDIS6   :  BIT_1;   // Bit    6
   bitfield32_t   CHDIS5   :  BIT_1;   // Bit    5
   bitfield32_t   CHDIS4   :  BIT_1;   // Bit    4
   bitfield32_t   CHDIS3   :  BIT_1;   // Bit    3
   bitfield32_t   CHDIS2   :  BIT_1;   // Bit    2
   bitfield32_t   CHDIS1   :  BIT_1;   // Bit    1
   bitfield32_t   CHDIS0   :  BIT_1;   // Bit    0

}  MIOS_UCDIS_F_T;

typedef union MIOS_UCDIS_Tag
{
   MIOS_UCDIS_F_T     F;
   uint32_t         U32;
}MIOS_UCDIS_T;

//=============================================================================
// ID - MIOS Channel A Data Register (MIOS_CADRn)
// Base Offset: UCn Base + 0x00
// Reset Value: 0000 0000 H
//
// Depending on the mode of operation, internal registers A1 or A2, used for 
// matches and captures, can be assigned to address MIOS_CADRn. Both A1 and A2 
// are cleared by reset. Table 17-9 summarizes the MIOS_CADRn writing and 
// reading accesses for all operating modes.
//
// Field         Bits    Type  Description
// ========== ========== ==== ==============================================
// 0            [31:24]    r  Reserved.
//
// A            [23:00]   rw  Depending on the mode of operation, internal
//                            registers A1 or A2, used for matches and
//                            captures, can be assigned to address MTSAn.
//                            Both A1 and A2 are cleared by reset.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
//=============================================================================
// ID - MIOS Channel B Data Register (MIOS_CBDRn)
// Base Offset: UCn Base + 0x04
// Reset Value: 0000 0000 H
//
// Depending on the mode of operation, internal registers B1 or B2 can be assigned 
// to address MIOS_CBDRn. Both B1 and B2 are cleared by reset. Table 17-9 
// summarizes the MIOS_CBDRn writing and reading accesses for all operating modes. 
//
// NOTE:
//    The MIOS_CBDRn must not be read speculatively. For future compatibility, 
// the TLB entry covering the MIOS_CBDRn must be configured to be guarded.
//
// Field         Bits    Type  Description
// ========== ========== ==== ==============================================
// 0            [31:24]    r  Reserved.
//
// B            [23:00]   rw  Depending on the mode of operation, internal
//                            registers B1 or B2, can be assigned to address
//                            MTSBn. Both B1 and B2 are cleared by reset.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

//=============================================================================
// ID - MIOS Channel Counter Register (MIOS_CCNTRn)
// Base Offset: UCn Base + 0x08
// Reset Value: 0000 0000 H
//
// The MIOS_CCNTRn The EMIOS_CCNTR[n] register contains the value of the internal 
// counter for eMIOS channel n. When GPIO mode is selected or the channel is frozen, 
// the EMIOS_CCNTR[n] register is read/write. For all other modes, the EMIOS_CCNTR[n] 
// is a read-only register. When entering some operation modes, this register
// is automatically cleared 
//
// NOTE:
//    In GPIO mode or freeze action, this register is writable.
//
// Field         Bits    Type  Description
// ========== ========== ==== ==============================================
// 0            [31:24]    r  Reserved.
//
// C            [23:00]    r  The MTSCNTn register contains the value of the
//                            internal counter. When GPIO mode is selected
//                            or the channel is frozen, the MTSCNTn register
//                            is read/write. For all others modes, the
//                            MTSCNTn is a read-only register. When entering
//                            some operation modes, this register is
//                            automatically cleared.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

//=============================================================================
// ID - MIOS Channel Control Register (MIOS_CCRn)
// Base Offset: UCn Base + 0x0C
// Reset Value: 0000 0000 H
//
//    The MIOS_CCRn enables the setting of several control parameters for a 
// unified channel. Among these controls are the setting of a channel prescaler, 
// channel mode selection, input trigger sensitivity and filtering, interrupt and 
// DMA request enabling, and output mode control.
//
// Field         Bits    Type  Description
// ========== ========== ==== ==============================================
// FREN             31    rw  Freeze enable. The FREN bit, if set and
//                            validated by FRZ bit in MTSMCR, freezes all
//                            registers values when in debug mode, allowing
//                            the MCU to perform debug functions.
//
//                              1 Freeze UC registers values
//                              0 Normal operation
//
// ODIS             30    rw  Output disable. Allows disabling the output
//                            pin when running any of the output modes with
//                            the exception of GPIO mode.
//
//                              0 The output pin operates normally
//                              1 If the selected Output Disable Input
//                                signal is asserted, the output pin goes
//                                to the complement of EDPOL, but the
//                                Unified Channel continues to operate
//                                normally, i.e., it continues to produce
//                                FLAG and matches. When the selected Output
//                                Disable Input signal is negated,the output
//                                pin operates normally
//
// ODISSL       [29:28]   rw  Output disable select. Select one of the four
//                            output disable input signals.
//
//                              00 Output Disable Input 0
//                              01 Output Disable Input 1
//                              10 Output Disable Input 2
//                              11 Output Disable Input 3
//
// UCPRE        [27:26]   rw  Prescaler. Select the clock divider value for
//                            the internal prescaler of Unified Channel,
//                            as shown below.
//
//                                UCPRE[1:0]         Divide ratio
//
//                                      00              1
//                                      01              2
//                                      10              3
//                                      11              4
//
// UCPREN           25    rw  Prescaler enable. Enables the prescaler
//                            counter.
//
//                              0 Prescaler disabled (no clock) and
//                                prescaler counter is loaded with
//                                UCPRE[0:1] value
//                              1 Prescaler enabled
//
// DMA              24    rw  Direct memory access. Selects if the FLAG
//                            generation will be used as an interrupt or as
//                            a DMA request.
//
//                              0 FLAG assigned to Interrupt request
//                              1 FLAG assigned to DMA request
//
// 0                23     r  Reserved, should be cleared.
//
// IF           [22:19]   rw  Input filter. Control the programmable input
//                            filter, selecting the minimum input pulse
//                            width that can pass through the filter, as
//                            shown below. For output modes, these bits have
//                            no meaning.
//
//                               IF[0:3] 1     Minimum input Pulse width
//                                              [FLT_CLK periods]
//
//                                  0000          Bypassed 2
//                                  0001          02
//                                  0010          04
//                                  0100          08
//                                  1000          16
//                                  all           Reserved
//                                others
//                            1 Filter latency is 3 clock edges.
//                            2 The input signal is synchronized before
//                              arriving to the digital filter.
//
// FCK              18    rw  Filter clock select. Selects the clock source
//                            for the programmable input filter.
//
//                              0 Prescaled clock
//                              1 Main clock
//
// FEN              17    rw  FLAG enable. Allows the Unified Channel FLAG
//                            bit to generate an interrupt signal or a DMA
//                            request signal (The type of signal to be
//                            generated is defined by the DMA bit).
//
//                              0 Disable (FLAG does not generate an
//                                interrupt or DMA request)
//                              1 Enable (FlAG will generate an interrupt
//                                or DMA request)
//
// 0            [16:14]   rw  Reserved, should be cleared.
//
// FORCMA           13    rw  Force match A. For output modes, the FORCMA
//                            bit is equivalent to a successful comparison
//                            on comparator A (except that the FLAG bit is
//                            not set). This bit is cleared by reset and is
//                            always read as zero. This bit is valid for
//                            every output operation mode which uses
//                            comparator A, otherwise it has no effect.
//
//                              0 Has no effect
//                              1 Force a match at comparator A
//
//                            For input modes, the FORCMA bit is not used
//                            and writing to it has no effect.
//
// FORCMB           12    rw  Force Match B. For output modes, the FORCMB
//                            bit is equivalent to a successful comparison
//                            on comparator B (except that the FLAG bit is
//                            not set). This bit is cleared by reset and is
//                            always read as zero. This bit is valid for
//                            every output operation mode which uses
//                            comparator B, otherwise it has no effect.
//
//                              0 Has not effect
//                              1 Force a match at comparator B
//
//                            For input modes, the FORCMB bit is not used
//                            and writing to it has no effect.
//
// 0                11     r  Reserved, should be cleared.
//
// BSL          [10: 9]   rw  Bus select. Used to select either one of the
//                            counter buses or the internal counter to be
//                            used by the Unified Channel.
//
//                              BSL[0:1]         Selected Bus
//
//                                00         All channels: counter bus[A]
//                                01         Channels 0 to 7: counter bus[B]
//                                           Channels 8 to 15: counter bus[C]
//                                           Channels 16 to 23:counter bus[D]
//                                10         Reserved
//                                11         All channels: internal counter
//
// EDSEL             8    rw  Edge selection bit. For input modes, the EDSEL
//                            bit selects whether the internal counter is
//                            triggered by both edges of a pulse or just by
//                            a single edge as defined by the EDPOL bit. When
//                            not shown in the mode of operation description,
//                            this bit has no effect.
//
//                              0 Single edge triggering defined by the
//                                EDPOL bit
//                              1 Both edges triggering
//
//                            For GPIO in mode, the EDSEL bit selects if a
//                            FLAG can be generated.
//
//                              0 A FLAG is generated as defined by the
//                                EDPOL bit
//                              1 No FLAG is generated
//
//                            For SAOC mode, the EDSEL bit selects the
//                            behavior of the output flip-flop at each match.
//
//                              0 The EDPOL value is transferred to the
//                                output flip-flop
//                              1 The output flip-flop is toggled
//
// EDPOL             7    rw  Edge polarity. For input modes (except QDEC
//                            mode), the EDPOL bit asserts which edge
//                            triggers either the internal counter or an
//                            input capture or a FLAG. When not shown in the
//                            mode of operation description, this bit has no
//                            effect.
//
//                              0 Trigger on a falling edge
//                              1 Trigger on a rising edge
//
//                            For QDEC (MODE[6] cleared), the EDPOL bit
//                            selects the count direction according to
//                            direction signal (UCn input).
//
//                              0 Counts down when UCn is asserted
//                              1 Counts up when UCn is asserted
//
//                            NOTE: UC[n-1] EDPOL bit selects which edge
//                                  clocks the internal counter of UCn
//
//                              0 Trigger on a falling edge
//                              1 Trigger on a rising edge
//
//                            For QDEC (MODE[6] set), the EDPOL bit selects
//                            the count direction according to the phase
//                            difference.
//
//                              0 Internal counter decrements if phase_A is
//                                ahead phase_B signal
//                              1 Internal counter increments if phase_A is
//                                ahead phase_B signal
//
//                            NOTE: In order to operate properly, EDPOL bit
//                                  must contain the same value in UCn and
//                                  UC[n-1]
//                            For output modes, the EDPOL bit is used to
//                            select the logic level on the output pin.
//
//                              0 A match on comparator A clears the output
//                                flip-flop, while a match on comparator B
//                                sets it
//                              1 A match on comparator A sets the output
//                                flip-flop, while a match on comparator B
//                                clears it
//
// MODE         [ 6: 0]   rw  Mode selection. Select the mode of operation of
//                            the Unified Channel,as shown in Table
//
//                              MODE0:6] 1           Mode of Operation
//
//                               0000000      General purpose Input/Output
//                                            mode (input)
//                               0000001      General purpose Input/Output
//                                            mode (output)
//                               0000010      Single Action Input Capture
//                               0000011      Single Action Output Compare
//                               0000100      Input Pulse Width Measurement
//                               0000101      Input Period Measurement
//                               0000110      Double Action Output compare
//                                            (with FLAG set on the second
//                                             match)
//                               0000111      Double Action Output compare
//                                            (with FLAG set on both match)
//                               0001000      Pulse/Edge Accumulation
//                                            (continuous)
//                               0001001      Pulse/Edge Accumulation (single
//                                            shot)
//                               0001010      Pulse/Edge Counting(continuous)
//                               0001011      Pulse/Edge Counting(singleShot)
//                               0001100      Quadrature Decode (for count &
//                                            direction encoders type)
//                               0001101      Quadrature Decode (for phase_A
//                                            & phase_B encoders type)
//                               0001110      Windowed Programmable Time
//                                            Accumulation
//                               0001111      Reserved
//                               001000b      Modulus Counter (Up counter)
//                               0010010 -    Reserved
//                               0010011
//                               00101bb      Modulus Counter (Up/Down
//                                            counter)
//                               00110b0      Output Pulse Width and
//                                            Frequency Modulation
//                                            (immediate update)
//                               00110b1      Output Pulse Width and
//                                            Frequency Modulation (next
//                                            period update)
//                               00111b0      Center Aligned Output Pulse
//                                            Width Modulation (with trail
//                                            edge dead-time)
//                               00111b1      Center Aligned Output Pulse
//                                            Width Modulation (with lead
//                                            edge dead-time)
//                               01000b0      Output Pulse Width Modulation
//                                            (immediate update)
//                               01000b1      Output Pulse Width Modulation
//                                            (next period update)
//                               1100100
//                                     to     Reserved
//                               1111111
//                            1 b = adjust parameters for the mode of
//                            operation.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct MIOS_CCR_F_Tag
{
   bitfield32_t   FREN     :  BIT_1;   // Bit      31
   bitfield32_t   ODIS     :  BIT_1;   // Bit      30
   bitfield32_t   ODISSL   :  BIT_2;   // Bits [29:28]
   bitfield32_t   UCPRE    :  BIT_2;   // Bits [27:26]
   bitfield32_t   UCPREN   :  BIT_1;   // Bit      25
   bitfield32_t   DMA      :  BIT_1;   // Bit      24
   bitfield32_t            :  BIT_1;   // Bit      23   is reserved
   bitfield32_t   IF       :  BIT_4;   // Bits [22:19]
   bitfield32_t   FCK      :  BIT_1;   // Bit      18
   bitfield32_t   FEN      :  BIT_1;   // Bit      17
   bitfield32_t            :  BIT_3;   // Bits [16:14] are reserved
   bitfield32_t   FORCMA   :  BIT_1;   // Bit      13
   bitfield32_t   FORCMB   :  BIT_1;   // Bit      12
   bitfield32_t            :  BIT_1;   // Bit      11   is reserved
   bitfield32_t   BSL      :  BIT_2;   // Bits [10: 9]
   bitfield32_t   EDSEL    :  BIT_1;   // Bit       8
   bitfield32_t   EDPOL    :  BIT_1;   // Bit       7
   bitfield32_t   MODE     :  BIT_7;   // Bits [ 6: 0]

}  MIOS_CCR_F_T;

typedef union MIOS_CCR_Tag  
{
   MIOS_CCR_F_T   F;
   uint32_t          U32;

}  MIOS_CCR_T;

//=============================================================================
// ID - MIOS Channel Status Register (MIOS_CSRn)
// Base Offset: UCn Base + 0x10
// Reset Value: 0000 0000 H
//
//    The MIOS_CCRn enables the setting of several control parameters for a 
// unified channel. Among these controls are the setting of a channel prescaler, 
// channel mode selection, input trigger sensitivity and filtering, interrupt and 
// DMA request enabling, and output mode control.
//
// Field         Bits    Type  Description
// =========  ========== ==== ==============================================
// OVR              31    rw  Overrun. Indicates that FLAG generation
//                            occurred when the FLAG bit was already set.
//                            This bit can be cleared by writing a 1 to it
//                            or by clearing the FLAG bit.
//
//                              0 Overrun has not occurred
//                              1 Overrun has occurred
//
// 0            [30:16]   rw  Reserved, should be cleared.
//
// OVFL             15    rw  Overflow. Indicates that an overflow has
//                            occurred in the internal counter. OVFL must be
//                            cleared by software writing a 1 to the OVFLC
//                            bit. This bit can be cleared by writing a 1 to
//                            it.
//
//                              0 No overflow
//                              1 An overflow had occurred
//
// 0            [14: 3]   rw  Reserved, should be cleared.
//
// UCIN              2     r  Unified channel input pin. Reflects the input
//                            pin state after being filtered and
//                            synchronized.
//
// UCOUT             1     r  Unified channel output pin. The UCOUT bit
//                            reflects the output pin state.
//
// FLAG              0    rw  FLAG. Set when an input capture or a match
//                            event in the comparators occurred. This bit
//                            can be cleared by writing a 1 to it.
//
//                              0 FLAG cleared
//                              1 FLAG set event has occurred
//
//                            NOTE: mts_flag_out reflects the FLAG bit
//                                  value. When DMA bit is set, the FLAG
//                                  bit can be cleared by the DMA controller.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct MIOS_CSR_F_Tag
{
   bitfield32_t   OVR   :  1;  // Bit      31
   bitfield32_t         : 15;  // Bits [30:16] are reserved
   bitfield32_t   OVFL  :  1;  // Bit      15
   bitfield32_t         : 12;  // Bits [14: 3] are reserved
   bitfield32_t   UCIN  :  1;  // Bit       2
   bitfield32_t   UCOUT :  1;  // Bit       1
   bitfield32_t   FLAG  :  1;  // Bit       0

}  MIOS_CSR_F_T;

typedef union MIOS_CSR_Tag 
{
   MIOS_CSR_F_T   F;
   uint32_t       U32;

}  MIOS_CSR_T;

//=============================================================================
// Unified Channel Structure
//=============================================================================
typedef struct MIOS_CH_Tag 
{
   uint32_t    CADR;                         // Channel A Data Register
   uint32_t    CBDR;                         // Channel B Data Register
   uint32_t    CCNTR;                        // Channel Counter Register
   MIOS_CCR_T  CCR;                          // Channel Control Register
   MIOS_CSR_T  CSR;                          // Channel Status Register
   uint32_t    ALTA;                         // Channel Alternate Address Register
   uint32_t    reserved[MIOS_RESERVED_0002]; // unused 

} MIOS_CH_T;

//=============================================================================
//  MIOS Module Structure  
//=============================================================================
typedef volatile struct MIOS_Tag 
{
   MIOS_MCR_T     MCR;                           // Module Configuration Register
   MIOS_GFR_T     GFR;                           // Global FLAG Register
   MIOS_OUDR_T    OUDR;                          // Output Update Disable Register
   MIOS_UCDIS_T   UCDIS;                         // Disable channel
   uint32_t       reserved[4];                   // unused
   MIOS_CH_T      CH[24];                        // MIOS Channels
   uint32_t       reserved1[MIOS_RESERVED_F38];  //reserved 0x0320–0x3FFF
}  MIOS_T;  

#endif // HW_MIOS_H

