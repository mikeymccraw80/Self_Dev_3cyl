#ifndef HW_TPU_H
#define HW_TPU_H

#include "reuse.h"

#define TPU_CHANNEL_CONTROL_QUANTITY     (32)

#define TPU_SDM_SIZE_IN_U32        ( 0xC00 / sizeof(uint32_t) )          //3k BYTES

#define TPU_SCM_SIZE_IN_U32        ( 0x3800 / sizeof(uint32_t) )        // 14k BYTES

#define TPU_SDM_PSE_SIZE_IN_U32    ( 0xC00 / sizeof(uint32_t) )         //3K BYTES

#define TPU_ARRAY_SIZE_01 (0x0001)
#define TPU_ARRAY_SIZE_02 (0x0002)
#define TPU_ARRAY_SIZE_04 (0x0004)
#define TPU_RESERVED_0004 (0x0004)
#define TPU_RESERVED_0008 (0x0008)
#define TPU_RESERVED_000C (0x000C)
#define TPU_RESERVED_0010 (0x0010)
#define TPU_RESERVED_001C (0x001C)
#define TPU_RESERVED_0020 (0x0020)
#define TPU_RESERVED_0190 (0x0190)
#define TPU_RESERVED_0200 (0x0200)
#define TPU_RESERVED_016C (0x016C)
#define TPU_RESERVED_7800 (0x7800)
#define TPU_RESERVED_3400 (0x3400)

//=============================================================================
// ID - eTPU Module Configuration Register (TPU_MCR)
//
// Base Offset : 0000 0000 H
//
// Reset Value : 00XX 0000 H
//
// Field        Bits     Type Description
//============  ======== ==== ===============================================
// GEC              31     w  Global exception clear. Negates global
//                            exception request and clears global exception
//                            status bits MGEA, MGEB, ILFA, ILFB and SCMMISF.
//                            A read will always return 0. Writes have the
//                            following effect:
//                              0 Keep global exception request and status
//                                bits ILFA, ILFB, MGEA, MGEB, and
//                                SCMMISF as is.
//                              1 Negate global exception, clear status bits
//                                ILFA, ILFB, MGEA, MGEB, and SCMMISF.
//                            GEC works the same way with either one or both
//                            engines in stop mode.
//
// SDMERR           30     r  SDM Read Error
//                            This flag indicates that an SDM read error 
//                            occurred on a microengine read, generating a 
//                            Global Exception.
//                            1 Global Exception requested by SDM read error 
//                              is pending.
//                            0 No Global Exception pending because of 
//                              SDM read error
//
// WDTO1,2     [29:28]     r  Watchdog Timeout
//                            WDTO1 and WDTO2 indicate that a Watchdog Timeout 
//                            occurred in eTPU_A and eTPU_B.These bits are 
//                            cleared by writing 1 to GEC.
//                            1 Global Exception requested by Watchdog timeout
//                            0 No Global Exception pending because of 
//                              Watchdog timeout.
//
// MGEA             27     r  Microcode global exception engine A. Indicates
//                            that a global exception was asserted by
//                            microcode executed on the respective engine.
//                            The determination of the reason why the
//                            global exception was asserted is
//                            application dependent: it can be coded in
//                            an SPRAM status parameter, for instance.
//                            This bit is cleared by writing 1 to GEC.
//                            0 No microcode-requested global exception
//                              pending.
//                            1 Global exception requested by microcode
//                              is pending.
//
// MGEB             26     r  Microcode global exception engine B. Indicates
//                            that a global exception was asserted by
//                            microcode executed on the respective engine.
//                            The determination of the reason why the
//                            global exception was asserted is application
//                            dependent: it can be coded in an SPRAM
//                            status parameter, for instance. This bit is
//                            cleared by writing 1 to GEC.
//                              0 No microcode requested global exception
//                                pending.
//                              1 Global exception requested by microcode
//                                is pending.
//
// ILFA             25     r  Illegal instruction flag eTPU A. Set by
//                            the microengine to indicate that an illegal
//                            instruction was decoded in engine A. This
//                            bit is cleared by host writing 1 to GEC.
//                              0 Illegal Instruction not detected.
//                              1 Illegal Instruction detected by eTPU A.
//
// ILFB             24     r  Illegal instruction flag eTPU B. Set by the
//                            microengine to indicate that an illegal
//                            instruction was decoded in engine B. This
//                            bit is cleared by host writing 1 to GEC.
//                              0 Illegal Instruction not detected.
//                              1 Illegal Instruction detected by eTPU B.
//
// SCMERR           23     r  SCM Read Error.This flag indicates that an
//                            SCM read error occurred on a microengine read,
//                            generating a Global Exception.Errors from Host
//                            reads neither set this flag nor generation 
//                            Global Exceptions. This bit is cleared by 
//                            writing 1 to GEC.
//                             1 Global Exception requested by SCM read 
//                               error is pending.
//                             0 No Global Exception pending because of
//                               SCM read error.
//
// 0           [22:21]     r  Reserved.
//
// SCMSIZE     [20:16]     r  SCM size. Holds the number of 2 Kbyte SCM
//                            Blocks minus 1. This value is MCU-dependent.
//
// 0           [15:12]     r  Reserved.
//
// SCMMISC          11     r  SCM MISC Complete, SCM MISC Complete Clear
// SCMMISCC                W  Flag SCMMISC indicates that MISC has completed
//                            the evaluation of the SCM signature
//                            SCMMISC is cleared by writing 1 to SCMMISCC
//                            and is not cleared when MISC is disabled
//                            1 MISC completed at least one SCM signature 
//                              calculation and compare since the last time 
//                              SCMMISC was cleared.
//                            0 MISC has not yet completed an SCM signature 
//                              calculation and compare since the last time 
//                              SCMMISC was cleared
//
// SCMMISF          10     r  SCM MISC Flag. Set by the SCM MISC (Multiple
//                            Input Signature Calculator) logic to
//                            indicate that the calculated signature does
//                            not match the expected value, at the end of
//                            a MISC iteration. The SCMMISF bit is not
//                            affected by eTPU A or eTPU B internal soft
//                            reset.
//                              0 Signature mismatch not detected.
//                              1 MISC has read entire SCM array and the
//                                expected signature in TPU_MISCCMPR
//                                does not match the value calculated.
//                            This bit is automatically cleared when
//                            SCMMISEN changes from 0 to 1, or when global
//                            exception is cleared by writing 1 to GEC.
//
// SCMMISEN         09    rw  SCM MISC enable. Used for enabling/disabling
//                            the operation of the MISC logic. SCMMISEN is
//                            readable and writable at any time. The MISC
//                            logic will only operate when this bit is set
//                            to 1. When the bit is reset the MISC address
//                            counter is set to the initial SCM address.
//                            When enabled, the MISC will continuously cycle
//                            through the SCM addresses, reading each and
//                            calculating a CRC. In order to save power, the
//                            MISC can be disabled by clearing the SCMMISEN
//                            bit. The SCMMISEN bit is not affected by
//                            eTPU A or eTPU B internal soft reset.
//                              0 MISC operation disabled. The MISC logic is
//                                reset to its initial state.
//                              1 MISC operation enabled. (Toggling to 1
//                                clears the SCMMISF bit)
//
//                            SCMMISEN is cleared automatically when MISC
//                            logic detects an error; that is, when
//                            SCMMISF transitions from 0 to 1, disabling
//                            the MISC operation.
//
// 0           [08:07]     r  Reserved.
//
// VIS              06    rw  SCM visibility. Determines SCM visibility
//                            to the IP bus interface and resets the MISC
//                            state (but SCMMISEN keeps its value).
//                              0 SCM is not visible to the IP bus.
//                                Accessing SCM address space issues a
//                                bus error.
//                              1 SCM is visible to the IP bus. The MISC
//                                state is reset.
//                            This bit is write protected when any of the
//                            engines are not in halt or stop states. When
//                            VIS=1, the TPU_ECR STOP bits are write
//                            protected, and only 32-bit aligned SCM
//                            writes are supported. The value written to
//                            SCM is unpredictable if other transfer sizes
//                            are used.
//
// 0           [05:01]     r  Reserved.
//
// GTBE             00    rw  Global time base enable. Enables time bases
//                            in both engines, allowing them to be started
//                            synchronously. An assertion of GTBE also
//                            starts the eMIOS time base1. This enables
//                            the eTPU time bases and the eMIOS time base
//                            to all start synchronously.
//                              1 time bases in both eTPU engines and eMIOS
//                                are enabled to run.
//                              0 time bases in both engines are disabled
//                                to run.
//
//=============================================================================

typedef struct TPU_MCR_F_Tag
{
   bitfield32_t   GEC      :  BIT_1;  // Bit      31
   bitfield32_t   SDMERR   :  BIT_1;  // Bit      30
   bitfield32_t   WDTO1    :  BIT_1;  // Bit      29
   bitfield32_t   WDTO2    :  BIT_1;  // Bit      28
   bitfield32_t   MGEA     :  BIT_1;  // Bit      27
   bitfield32_t   MGEB     :  BIT_1;  // Bit      26
   bitfield32_t   ILFA     :  BIT_1;  // Bit      25
   bitfield32_t   ILFB     :  BIT_1;  // Bit      24
   bitfield32_t   SCMERR   :  BIT_1;  // Bit      23
   bitfield32_t            :  BIT_2;  // Bits [22:21] are reserved
   bitfield32_t   SCMSIZE  :  BIT_5;  // Bits [20:16]
   bitfield32_t            :  BIT_4;  // Bits [15:12] are reserved
   bitfield32_t   SCMMISC  :  BIT_1;  // Bit      11
   bitfield32_t   SCMMISF  :  BIT_1;  // Bit      10
   bitfield32_t   SCMMISEN :  BIT_1;  // Bit       9
   bitfield32_t            :  BIT_2;  // Bits [ 8: 7] are reserved
   bitfield32_t   VIS      :  BIT_1;  // Bit       6
   bitfield32_t            :  BIT_5;  // Bits [ 5: 1] are reserved
   bitfield32_t   GTBE     :  BIT_1;  // Bit       0

}  TPU_MCR_F_T;

typedef union TPU_MCR_Tag
{
   TPU_MCR_F_T          F;
   uint32_t             U32;

}  TPU_MCR_T;

//=============================================================================
// ID - eTPU Coherent Dual-Parameter Controller Register (TPU_CDCR)
//
// Base Offset : 0000 0004 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type Description
//============  ======== ==== ===============================================
// STS              31    rw  Start. Set by the host in order to start the
//                            data transfer between the parameter buffer
//                            pointed by PBBASE and the target addresses
//                            selected by the concatenation of fields
//                            CTBASE and PARM0/1. The host receives
//                            wait-states until the data transfer is
//                            complete. Coherency logic resets STS once
//                            the data transfer is complete.
//                              0 (Write) does not start a coherent
//                                transfer.
//                              1 (Write) starts a coherent transfer.
//
// CTBASE      [30:26]    rw  Channel transfer base. This field
//                            concatenates with fields PARM0/PARM1 to
//                            determine the absolute offset (from the
//                            SPRAM base) of the parameters to be
//                            transferred:
//                              Parameter 0 address =
//                              {CTBASE, PARM0} + SPRAM base
//
//                              Parameter 1 address =
//                              {CTBASE, PARM1} + SPRAM base
//
// PBBASE      [25:16]    rw  Parameter buffer base address. Points to
//                            the base address of the parameter buffer
//                            location, with granularity of 2 parameters
//                            (8 bytes). The host (byte) address of the
//                            first parameter in the buffer is
//                            PBBASE × 8 + SPRAM Base Address.
//
// PWIDTH           15    rw  Parameter width selection. Selects the width
//                            of the parameters to be transferred between
//                            the PB and the target address.
//
//                              0 Transfer 24-bit parameters. The upper byte
//                                remains unchanged in the destination
//                                address.
//                              1 Transfer 32-bit parameters. All 32 bits of
//                                the parameters are written in the
//                                destination address.
//
// PARM0       [14:08]    rw  Channel Parameter number 0. This field in
//                            concatenation with CTBASE[3:0] determine
//                            the address offset (from the SPRAM base
//                            address) of the parameter which is the
//                            destination or source (defined by WR) of
//                            the coherent transfer. The SPRAM address
//                            offset of the parameter is {CTBASE,
//                            PARM0}*4.Note that PARM0 allows
//                            non-contiguous parameters to be
//                            transferred coherently.
//
// WR               07    rw  Read/Write selection. This bit selects the
//                            direction of the coherent data transfer.
//
//                              1 Write operation. Data transfer is from the
//                                PB to the selected parameter RAM address.
//
//                              0 Read operation. Data transfer is from the
//                                selected parameter RAM address to the PB.
//
// PARM1       [06:00]    rw  Channel Parameter number 1. This field in
//                            concatenation with CTBASE[3:0] determines
//                            the address offset (from the SPRAM base)
//                            of the parameter which is the destination
//                            or source (defined by WR) of the coherent
//                            transfer. The SPRAM address offset of the
//                            parameter is {CTBASE, PARM1}*4.Note that
//                            PARM1 allows non-contiguous parameters to
//                            be transferred coherently.
//
// =============================================================================

typedef struct TPU_CDCR_F_Tag
{
   bitfield32_t   STS      :  BIT_1;   // Bit      31
   bitfield32_t   CTBASE   :  BIT_5;   // Bits [30:26]
   bitfield32_t   PBBASE   :  BIT_10;  // Bits [25:16]
   bitfield32_t   PWIDTH   :  BIT_1;   // Bit      15
   bitfield32_t   PARM0    :  BIT_7;   // Bits [14: 8]
   bitfield32_t   WR       :  BIT_1;   // Bit       7
   bitfield32_t   PARM1    :  BIT_7;   // Bits [ 6: 0]

}  TPU_CDCR_F_T;

typedef union TPU_CDCR_Tag
{
   TPU_CDCR_F_T          F;
   uint32_t              U32;

}  TPU_CDCR_T;

//=============================================================================
// ID - eTPU MISC Compare Register (TPU_MISCCMPR)
//
// Base Offset : 0000 000C H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// EMISCCMP    [31:00]    rw  Expected multiple input signature calculator
//                            compare register value.
//
//=============================================================================

typedef uint32_t   TPU_MISCCMPR_T;

//=============================================================================
// ID - eTPU Engine Configuration Register (TPU_ECR)
//
// Base Offset : 0000 0014 H  ( TPU_ECR_1 )
//               0000 0018 H  ( TPU_ECR_2 )
//
// Reset Value : 0800 0000 H  ( TPU_ECR_1 )
//               0000 0000 H  ( TPU_ECR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// FEND             31    rw  Force end. Assertion terminates any current
//                            running thread as if an END instruction have
//                            been executed.
//                              0 Normal operation.
//                              1 Puts engine in reset.
//                            This bit is self-negating, that is the host
//                            receives wait-states during the reset. Once
//                            the reset is completed FEND is cleared.
//                            Therefore FEND always reads as 0. FEND
//                            assertion is ignored when the microengine is
//                            in TST, Halt, or Idle.
//
// STOP             30    rw  Low power stop bit. When STOP is set, the
//                            engine shuts down its internal clocks. TCR1
//                            and TCR2 cease to increment, and input
//                            sampling stops. The engine asserts the stop
//                            flag (STF) bit to indicate that it has
//                            stopped. However, the BIU continues to run,
//                            and the host can access all registers except
//                            for the channel registers1. After STOP is set,
//                            even before STF asserts, data read from the
//                            channel registers is not meaningful, a Bus
//                            Error is issued, and writes are unpredictable.
//                            When the STOP bit is asserted while the
//                            microcode is executing, the eTPU will stop
//                            when the thread is complete.
//                              0 eTPU engine runs.
//                              1 Commands engine to stop its clocks.
//
//                            Stop completes on the next system clock after
//                            the stop condition is valid. The STOP bit is
//                            write-protected when TPU_MCR[VIS]=1.
//
// 0                29     r  Reserved.
//
// STF              28     r  Stop flag bit. Each engine asserts its stop
//                            flag (STF) to indicate that it has stopped.
//                            Only then the host can assume that the engine
//                            has actually stopped. The eTPU system is fully
//                            stopped when the STF bits of both eTPU engines
//                            are asserted. In case of STAC bus stop, the
//                            eTPU system responds with stop acknowledge
//                            only after both eTPU A and eTPU B have been
//                            stopped. The engine only stops when any ongoing
//                            thread is complete in this case.
//
//                              0 The engine is operating.
//                              1 The engine has stopped (after the local
//                                STOP bit has been asserted, or after the
//                                STAC bus stop line has been asserted).
//
//                            Summarizing engine stop conditions, which STF
//                            reflects:
//                            STF_1 := (after stop completed) STOP_1 |
//                                    ipg_stop
//                            STF_2 := (after stop completed) STOP_2 |
//                                    ipg_stop
//                            STF_1 and STF_2 mean STF bit from engine A
//                            and STF bit from engine B respectively.
//
// 0           [27:24]     r  Reserved.
//
// HLTF             23     r  Halt mode flag. If eTPU engine entered halt
//                            state, this flag is asserted. The flag
//                            remains asserted while the microengine is in
//                            halt state, even during a single-step or
//                            forced instruction execution.
//
//                              0 eTPU engine is not halted.
//                              1 eTPU engine is halted
//
// 0           [22:20]     r  Reserved.
//
// FCSS          19      rw  Filter Clock Source Selection
//                            Speeds up the filter clock source before the 
//                            prescaler, allowing more input capture resolution
//                            at minimum prescaling.
//                            1  use system clock as EDF clock source before 
//                                prescaler
//                            0  use system clock / 2 as EDF clock source 
//                                before prescaler 
// 
// FPSCK       [18:16]    rw  Filter prescaler clock control. Controls
//                            the prescaling of the clocks used in digital
//                            filters for the channel input signals and
//                            TCRCLK input. The following table illustrates
//                            filter prescaler clock control.
//
//                              Filter Control       Sample on System
//                                                  Clock Divided by:
//                                000                      2
//                                001                      4
//                                010                      8
//                                011                      16
//                                100                      32
//                                101                      64
//                                110                      128
//                                111                      256
//
//                            Filtering can be controlled independently by
//                            the engine, but all input digital filters in
//                            the same engine have same clock prescaling.
//
// CDFC        [15:14]    rw  Channel digital filter control. Select a
//                            digital filtering mode for the channels when
//                            configured as inputs for improved noise
//                            immunity. Channel digital filter control is
//                            illustrated in the following table.
//
//                              CDFC  Selected Digital Filter
//                               00   TPU2/3 two sample mode: Using
//                                    the filter clock which is the system
//                                    clock divided by (2, 4, 8,..., 256)
//                                    as a sampling clock (selected by FPSCK
//                                    field in TPU_ECR), comparing two
//                                    consecutive samples which agree with
//                                    each other sets the input signal state.
//                                    This is the default reset state.
//                               01   Reserved.
//                               10   eTPU three sample mode: Similar to the
//                                    TPU2/3 two sample mode, but comparing
//                                    three consecutive samples which agree
//                                    with each other sets the input signal
//                                    state.
//                               11   eTPU continuous mode: Signal needs to
//                                    be stable for the whole filter clock
//                                    period. This mode compares all the
//                                    values at the rate of system clock
//                                    divided by two, between two consecutive
//                                    filter clock pulses. If all the values
//                                    agree with each other,input signal
//                                    state is updated.
//
//                            The eTPU has three digital filtering modes
//                            for the channels which provide programmable
//                            trade-off between signal latency and noise
//                            immunity. Changing CDFC during eTPU normal
//                            input channel operation is not recommended
//                            since it changes the behavior of the
//                            transition detection logic while executing
//                            its operation.
//
// 0            13        r   Reserved.
//
// ERBA        [12:8]     rw  Engine Relative Base Address.
//                            This field value is concatenated with the AID 
//                            instruction field in engine relative address mode 
//                            to form
//
// SPPDIS       7         rw  Schedule Priority Passing Disable
//                            Disable the priority passing mechanism 
//                            of the microengine scheduler
//                            1 Scheduler priority passing mechanism disabled.
//                            0 Scheduler priority passing mechanism enabled
//
// 0           [6:05]     r   Reserved.
//
// ETB         [04:00]    rw  Entry table base. Determines the location of
//                           the microcode entry table for the eTPU
//                            functions in SCM. The following table shows
//                            the entry table base address options.
//
//                                   Entry Table Base  Entry Table Base Addr
//                             ETB  Addr for CPU Host  for Microcode Address
//                                   Addr(byte fmt)      (word format)
//
//                            00000      0x0_0000          0x0_0000
//                            00001      0x0_0800          0x0_0200
//                            00010      0x0_1000          0x0_400
//                              .           .                .
//                              .           .                .
//                              .           .                .
//                              .           .                .
//                            11110      0x0_F000          0x0_3C00
//                            11111      0x0_F800          0x0_3E00
//
//=============================================================================

typedef struct TPU_ECR_F_Tag
{
   bitfield32_t   FEND     :  BIT_1;   // Bit      31
   bitfield32_t   MDIS     :  BIT_1;   // Bit      30
   bitfield32_t            :  BIT_1;   // Bit      29  is reserved
   bitfield32_t   STF      :  BIT_1;   // Bit      28
   bitfield32_t            :  BIT_4;   // Bits [27:24] are reserved
   bitfield32_t   HLTF     :  BIT_1;   // Bit      23
   bitfield32_t            :  BIT_3;   // Bits [22:20] are reserved
   bitfield32_t   FCSS     :  BIT_1;   // Bits 19
   bitfield32_t   FPSCK    :  BIT_3;   // Bits [18:16]
   bitfield32_t   CDFC     :  BIT_2;   // Bits [15:14]
   bitfield32_t            :  BIT_1;   // Bit  13  is reserved
   bitfield32_t   ERBA     :  BIT_5;   // Bits [12:8]
   bitfield32_t   SPPDIS   :  BIT_1;   // Bits 7
   bitfield32_t            :  BIT_2;   // Bits [6: 5] are reserved
   bitfield32_t   ETB      :  BIT_5;   // Bits [ 4: 0]

}  TPU_ECR_F_T;

typedef union TPU_ECR_Tag
{
   TPU_ECR_F_T          F;
   uint32_t             U32;

}  TPU_ECR_T;

//=============================================================================
// ID - eTPU Time Base Configuration Register (TPU_TBCR)
//
// Base Offset : 0000 0020 H  or ( TPU_TBCR_1 )
//               0000 0040 H     ( TPU_TBCR_2 )
//
// Reset Value : 2000 0000 H   ( TPU_TBCR_1 )
//               2000 0000 H   ( TPU_TBCR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// TCR2CTL     [31:29]    rw  TCR2 clock/gate control. Part of the TCR2
//  [2:0]                     clocking system. They determine the clock
//                            source for TCR2. TCR2 can count on any
//                            detected edge of the TCRCLK signal or use
//                            it for gating system clock divided by 8. After
//                            reset, TCRCLK signal rising edge is selected.
//                            TCR2 can also be clocked by the system clock
//                            divided by 8. TCR2 clock sources are listed
//                            in the following table.
//
//                            TCR2CTL  TCR2 Clock             Angle Tooth
//                                                              Detection
//                              000  Gated DIV8 clock (system   Not Used
//                                   clock / 8). When the
//                                   external TCRCLK signal is
//                                   low, the DIV8 clock is
//                                   blocked, preventing it
//                                   from incrementing TCR2.
//                                   When the external TCRCLK
//                                   signal is high, TCR2 is
//                                   incremented at the
//                                   frequency of the system
//                                   clock divided by 8.
//
//                              001  Rise transition on TCRCLK  Rising Edge
//                                   signal increments TCR2.
//
//                              010  Fall transition on TCRCLK  Falling Edge
//                                   signal increments TCR2.
//
//                              011  Rise or fall transition    Rising or
//                                   on TCRCLK signal           Falling Edge
//                                   increments TCR2.
//
//                              100  DIV8 clock (system clock/8)  Not Used
//                                   TCRCLK not used
//
//                              101  Reserved
//                              110  
//                              111
//
// TCRCF       [28:27]    rw  TCRCLK signal filter control. Controls the
//  [1:0]                     TCRCLK digital filter determining whether
//                            the TCRCLK signal input (after a
//                            synchronizer) is filtered with the same
//                            filter clock as the channel input
//                            signals or uses the system clock divided
//                            by 2, and also whether the TCRCLK digital
//                            filter works in integrator mode or two
//                            sample mode. The following table describes
//                            TCRCLK filter clock/mode.
//
//                            TCRCF      Filter Input          Filter Mode
//                             00   system clock divided by 2    two sample
//                             01   filter clock of the channels two sample
//                             10   system clock divided by 2    integration
//                             11   filter clock of the channels integration
//
// AM            [26:25] rw   Angle mode selection. When the AM bit is set
//                            and neither TCR1 nor TCR2 are STAC interface
//                            clients, the EAC (eTPU Angle Clock) hardware
//                            provides angle information to the channels
//                            using the TCR2 bus. When the AM is reset
//                            (non-angle mode), EAC operation is disabled,
//                            and its internal registers can be used as
//                            general purpose registers.
//                              0 EAC operation is disabled.
//                              1 TCR2 works in angle mode. If TCR1/TCR2 is not a
//                                STAC client the EAC works and stores
//                                tooth counter and angle tick counter
//                                data in TCR2.
//                            If TCR1 or TCR2 is a STAC bus client, EAC
//                            operation is forbidden. Therefore, if AM is
//                            set, the angle logic will not work properly.
//
// 0           [24:22]     r  Reserved.
//
// TCR2P       [21:16]    rw  Timer count register 2 prescaler control.
//                            Part of the TCR2 clocking system. TCR2 is
//                            clocked from the output of a prescaler.
//                            The prescaler divides its input by (TCR2P+1)
//                            allowing frequency divisions from 1 to 64.
//                            The prescaler input is the system clock
//                            divided by 8 (in gated or non-gated clock
//                            mode) or TCRCLK filtered input.
//
// TCR1CTL     [15:14]    rw  TCR1 clock/gate control. Part of the TCR1
//                            clocking system. It determines the clock
//                            source for TCR1. TCR1 can count on
//                            detected rising edge of the TCRFCLK signal
//                            or the system clock divided by 2. After
//                            reset TCRCLK signal is selected.The following
//                            table shows the selection of the TCR1 clock
//                            source.
//
//                            TCR1CTL                 TCR1 Clock
//                              00    selects TCRCLK as clock source for
//                                    the TCR1 prescaler
//                              01    reserved
//                              10    selects system clock divided by 2 as
//                                    clock source for the TCR1 prescaler
//                              11    reserved
//
//  TCR1CS   13         rw TCR1 Clock Source
//                             TCR1CS provides the option to double the TCR1 
//                             incrementing speed, using system clock as its clock
//                             source instead of system clock / 2.
//                             1  use system clock as TCR1 clock source before 
//                                 the prescaler; can only be set in specific 
//                                 combinations with TCR1CTL
//                             0  use system clock / 2 as TCR1 clock source 
//                                 before the prescaler, if that clock source is selected
//                                 by TCR1CTL.
//
//                          TCR1CTL TCR1CS TCR1 Clock         
//                           00             0        Selects TCRCLK as clock source for 
//                                                     the TCR1 prescaler2  
//                           01             0        Selects Peripheral Timebase clock 
//                                                      as source for the TCR1 prescaler
//                           10             0         Selects system clock divided by 2 as 
//                                                      clock source for the TCR1 prescaler
//                           10             1         Selects system clock as clock source 
//                                                       for the TCR1 prescaler
//                           11             0         TCR1 frozen, except as a Red Line client
//
//                           NOTE  : All other combinations of TCR1CTL and TCR1CS are reserved.
//
//  0          [12:08]     r  Reserved.
//
// TCR1P       [07:00]    rw  Timer count register 1 prescaler control.
//                            Clocked from the output of a prescaler.
//                            The input to the prescaler is the internal
//                            eTPU system clock divided by 2 or the output
//                            of TCRCLK filter. The prescaler divides this
//                            input by (TCR1P+1) allowing frequency
//                            divisions from 1 up to 256.
//
//=============================================================================

typedef struct TPU_TBCR_F_Tag
{
   bitfield32_t   TCR2CTL  :  BIT_3;   // Bits [31:29]
   bitfield32_t   TCRCF    :  BIT_2;   // Bits [28:27]
   bitfield32_t   AM       :  BIT_2;   // Bit  [26:25]
   bitfield32_t            :  BIT_3;   // Bits [24:22] are reserved
   bitfield32_t   TCR2P    :  BIT_6;   // Bits [21:16]
   bitfield32_t   TCR1CTL  :  BIT_2;   // Bits [15:14]
   bitfield32_t   TCR1CS   :  BIT_1;   // Bit 13
   bitfield32_t            :  BIT_5;   // Bits [12: 8] are reserved
   bitfield32_t   TCR1P    :  BIT_8;   // Bits [ 7: 0]

}  TPU_TBCR_F_T;

typedef union TPU_TBCR_Tag
{
   TPU_TBCR_F_T          F;
   uint8_t               U8[TPU_ARRAY_SIZE_04];
   uint16_t              U16[TPU_ARRAY_SIZE_02];
   uint32_t              U32;

}  TPU_TBCR_T;

//=============================================================================
// ID - eTPU Time Base 1 (TCRx) Visibility Register (TPU_TBxR)
//
// Base Offset : 0000 0024 H  or ( TPU_TB1R_1 )
//               0000 0044 H     ( TPU_TB1R_2 )
//
// Reset Value : 0000 0000 H    ( TPU_TB1R_1 )
//               0000 0000 H    ( TPU_TB1R_2 )
//
// ID - eTPU Time Base 2 (TCR2) Visibility Register (TPU_TB2R)
//
// Base Offset : 0000 0028 H  or   ( TPU_TB2R_1 )
//               0000 0048 H       ( TPU_TB2R_2 )
//
// Reset Value : 0000 0000 H      ( TPU_TB2R_1 )
//               0000 0000 H      ( TPU_TB2R_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0           [31:24]     r  Reserved.
//
// TCR2        [23:00]     r  TCR2 value. Used on matches and captures.
//
//
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct TPU_TBR_F_Tag
{
   bitfield32_t            :  BIT_8;   // Bits  [31:24]
   bitfield32_t   TCR      :  BIT_24;  // Bits  [23: 0]

}  TPU_TBR_F_T;

typedef union TPU_TBR_Tag
{
   TPU_TBR_F_T          F;
   uint8_t              U8[TPU_ARRAY_SIZE_04];
   uint16_t             U16[TPU_ARRAY_SIZE_02];
   uint32_t             U32;

}  TPU_TBR_T;

//=============================================================================
// ID - STAC Bus Configuration Register (TPU_REDCR)
//
// Base Offset : 0000 002C H  or   ( TPU_REDCR_1 )
//               0000 004C H       ( TPU_REDCR_2 )
//
// Reset Value : 0000 0000 H       ( TPU_REDCR_1 )
//               0000 0000 H       ( TPU_REDCR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// REN1             31    rw  TCR1 resource  client/server operation enable.
//                            Enables or disables client/server operation
//                            for the eTPU STAC interface. REN1 enables TCR1.
//
//                              0 Server/client operation for resource 1 is
//                                disabled.
//                              1 Server/client operation for resource 1 is
//                                enabled.
//
// RSC1             30    rw  TCR1 resource server/client assignment.
//                            Selects the eTPU data resource assignment
//                            to be used as a server or client. RSC1 selects
//                            the functionality of TCR1. For server mode,
//                            external plugging determines the unique server
//                            address assigned to each TCR.
//                              0 Resource client operation.
//                              1 Resource server operation.
//
// 0                 29:28   Reserved
//
// VALID1        27:24   rw  Server 1 valid bit. Provides the status of
//                            the internal valid state of the STAC interface
//                            (in server operation) to TCR1. The host can
//                            set the VALID1 bit to force data transmission
//                            from the STAC interface on the next selected
//                            time slot. When set by the host, this bit is
//                            automatically cleared when data is transmitted.
//
//                              0 On reads, 0 indicates that STAC interface
//                                will not transmit its data at its next time
//                                slot. Writing 0 is ignored.
//                              1 The STAC interface will transmit its data
//                                at its next time slot.
//
// 0           [23:20]     r  Reserved.
//
// SRV1        [19:16]    rw  TCR1 resource server. Selects the address
//                            of the specific STAC Server the local TCR1
//                            will listen to when configured as a STAC
//                            client.
//
// REN2             15    rw  TCR2 resource1 client/server operation enable.
//                            Enables or disables client/server operation
//                            for eTPU IP resources. REN2 enables TCR2 IP
//                            bus operations.
//
//                              1 Server/client operation for resource 2 is
//                                enabled.
//                              0 Server/client operation for resource 2 is
//                                disabled.
//
// RSC2             14    rw  TCR22 resource server/client assignment.
//                            Selects the eTPU data resource assignment
//                            to be used as a server or client. RSC2
//                            selects the functionality of TCR2. For
//                            server mode, external plugging determines
//                            the unique server address assigned to
//                            each TCR. For a client mode, the SRV2
//                            field determines the Server address to
//                            which the client listens.
//
//                              0 Resource Client operation.
//                              1 Resource Server operation.
//
//  0             13:12     Reserved
//
// VALID2      11:8    rw  Server 2 valid. Provides the status of the
//                            internal valid state of the STAC interface (in
//                            server operation) to TCR2. The host can set
//                            the VALID2 bit to force data transmission
//                            from the STAC interface on the next selected
//                            time slot. When set by the host, this bit
//                            is automatically cleared when data is
//                            transmitted.
//
//                              0 On reads, indicates that STAC server will
//                                not transmit its data at its next time
//                                slot. Writing 0 to VALID2 is ignored.
//                              1 The STAC server will transmit its data at
//                                its next time slot.
//
// 0           [7:04]     r  Reserved.
//
// SRV2        [03:00]    rw  TCR2 resource server. Selects the address
//                            of the specific STAC server the local TCR2
//                            listens to when configured as a STAC Client.
//
//=============================================================================

typedef struct TPU_REDCR_F_Tag
{
   bitfield32_t   REN1     :  BIT_1;   // Bit      31
   bitfield32_t   RSC1     :  BIT_1;   // Bit      30
   bitfield32_t            :  BIT_2;   // Bits [29:28]
   bitfield32_t   SRV_ID1  :  BIT_4;   // Bits [27:24]
   bitfield32_t            :  BIT_4;   // Bits [23:20]
   bitfield32_t   SRV1     :  BIT_4;   // Bits [19:16]
   bitfield32_t   REN2     :  BIT_1;   // Bit      15
   bitfield32_t   RSC2     :  BIT_1;   // Bit      14
   bitfield32_t            :  BIT_2;   // Bits[13: 12]
   bitfield32_t   SRV_ID2  :  BIT_4;   // Bits [11: 8]
   bitfield32_t            :  BIT_4;   // Bits [ 7: 4]
   bitfield32_t   SRV2     :  BIT_4;   // Bits [ 3: 0]

}  TPU_REDCR_F_T;

typedef union TPU_REDCR_Tag
{
   TPU_REDCR_F_T         F;
   uint16_t              U16[TPU_ARRAY_SIZE_02];
   uint32_t              U32;

}  TPU_REDCR_T;

typedef struct TPU_Clock_Tag
{
   TPU_TBCR_T     TBCR;
   TPU_TBR_T      TBR[TPU_ARRAY_SIZE_02];
   TPU_REDCR_T    REDCR;
   uint8_t        reserved[TPU_RESERVED_0010];

}  TPU_Clock_T;

//=============================================================================
// ID - eTPU Watchdog Timer Register (TPU_WDTR)
//
// Base Offset : 0000 0060 H  or   ( TPU_WDTR_1 )
//               0000 0070 H       ( TPU_WDTR_2 )
//
// Reset Value : 0000 0000 H        ( TPU_WDTR_1 )
//               0000 0000 H       ( TPU_WDTR_2 )
//
// Field         Bits     Type Description
//=========== ========== ==== ===============================================
// WDM       [31:30]    rw   Watchdog Mode
//                           WDM Selects the Watchdog operation mode
//                           Value  Mode
//                           00     WDT disabled
//                           01     Reserved
//                           10     Thread Length
//                           11     Busy Length 
//
// 0         [29:16]    r    Reserved
//
// WDTCNT    [15:00]    rw   Watchdog Count
//                           This field indicates the maximum number 
//                           of microcyles allowed for a thread 
//                           (in thread length mode)or a sequence
//                           of threads (in busy length mode) before 
//                           the current running thread is forced to end.
//
//=============================================================================
typedef struct TPU_WDTR_F_Tag
{
   bitfield32_t   WDM     :  BIT_2;   // Bits [ 31:30]
   bitfield32_t           :  BIT_14;  // Bits [ 29:16]
   bitfield32_t   WDTCNT  :  BIT_16;  // Bits [15:0]
   
}   TPU_WDTR_F_T;
 
typedef union TPU_WDTR_Tag
{
   TPU_WDTR_F_T           F;
   uint16_t               U16[TPU_ARRAY_SIZE_02];
   uint32_t               U32;

}  TPU_WDTR_T;
//=============================================================================
// ID - eTPU Idle Register (TPU_IDLER)
//
// Base Offset : 0000 0068 H  or   ( TPU_IDLER_1 )
//               0000 0078 H       ( TPU_IDLER_2 )
//
// Reset Value : 0000 0000 H       ( TPU_IDLER_1 )
//               0000 0000 H       ( TPU_IDLER_2 )
//
// Field         Bits     Type Description
//=========== ========== ==== ===============================================
// IDLE_CNT   [31:0]   r  Idle Count. This is a freeruning count of the no.
//                        of idle microcycles in the microengine
//
// ICLR         0      w   This write-only bit is used to clear the idle 
//                         count IDLE_CNT 
//                         1 clear the idle count IDLE_CNT
//                         0 do not clear idle count IDLE_CNT
//
//=============================================================================
typedef struct TPU_IDLER_F_Tag
{
   bitfield32_t        :  BIT_31;   // Bit  [31:0]
   bitfield32_t   ICLR :  BIT_1;    // Bit  0
   
}   TPU_IDLER_F_T;

typedef union TPU_IDLER_Tag
{
   TPU_IDLER_F_T    F;
   uint16_t               U16[TPU_ARRAY_SIZE_02];
   uint32_t               U32;

}  TPU_IDLER_T;

typedef struct TPU_Wdt_Idle_Tag
{
   TPU_WDTR_T     WDTR;
   uint8_t        reserved_0[TPU_RESERVED_0004];
   TPU_IDLER_T    IDLER;
   uint8_t        reserved_1[TPU_RESERVED_0004];

}   TPU_Wdt_Idle_T;


//=============================================================================
// ID - eTPU Channel Interrupt Status Register (TPU_CISR)
//
// Base Offset : 0000 0200 H  or    ( TPU_CISR_1 )
//               0000 0204 H        ( TPU_CISR_2 )
//
// Reset Value : 0000 0000 H        ( TPU_CISR_1 )
//               0000 0000 H        ( TPU_CISR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// CISn        [31:00]     r  Channel n interrupt status.
//                            0 indicates that channel n has no pending
//                              interrupt to the host CPU.
//                            1 indicates that channel n has a pending
//                              interrupt to the host CPU.
//
// CICn        [31:00]     w  Channel n interrupt clear
//                              0 keep interrupt status bit unaltered.
//                              1 clear interrupt status bit.
//
//=============================================================================

typedef struct TPU_CISR_F_Tag
{
   bitfield32_t   CIC31 :  BIT_1;   // Bit  31
   bitfield32_t   CIC30 :  BIT_1;   // Bit  30
   bitfield32_t   CIC29 :  BIT_1;   // Bit  29
   bitfield32_t   CIC28 :  BIT_1;   // Bit  28
   bitfield32_t   CIC27 :  BIT_1;   // Bit  27
   bitfield32_t   CIC26 :  BIT_1;   // Bit  26
   bitfield32_t   CIC25 :  BIT_1;   // Bit  25
   bitfield32_t   CIC24 :  BIT_1;   // Bit  24
   bitfield32_t   CIC23 :  BIT_1;   // Bit  23
   bitfield32_t   CIC22 :  BIT_1;   // Bit  22
   bitfield32_t   CIC21 :  BIT_1;   // Bit  21
   bitfield32_t   CIC20 :  BIT_1;   // Bit  20
   bitfield32_t   CIC19 :  BIT_1;   // Bit  19
   bitfield32_t   CIC18 :  BIT_1;   // Bit  18
   bitfield32_t   CIC17 :  BIT_1;   // Bit  17
   bitfield32_t   CIC16 :  BIT_1;   // Bit  16
   bitfield32_t   CIC15 :  BIT_1;   // Bit  15
   bitfield32_t   CIC14 :  BIT_1;   // Bit  14
   bitfield32_t   CIC13 :  BIT_1;   // Bit  13
   bitfield32_t   CIC12 :  BIT_1;   // Bit  12
   bitfield32_t   CIC11 :  BIT_1;   // Bit  11
   bitfield32_t   CIC10 :  BIT_1;   // Bit  10
   bitfield32_t   CIC09 :  BIT_1;   // Bit   9
   bitfield32_t   CIC08 :  BIT_1;   // Bit   8
   bitfield32_t   CIC07 :  BIT_1;   // Bit   7
   bitfield32_t   CIC06 :  BIT_1;   // Bit   6
   bitfield32_t   CIC05 :  BIT_1;   // Bit   5
   bitfield32_t   CIC04 :  BIT_1;   // Bit   4
   bitfield32_t   CIC03 :  BIT_1;   // Bit   3
   bitfield32_t   CIC02 :  BIT_1;   // Bit   2
   bitfield32_t   CIC01 :  BIT_1;   // Bit   1
   bitfield32_t   CIC00 :  BIT_1;   // Bit   0

}  TPU_CISR_F_T;

 
typedef union TPU_CISR_Tag
{
   TPU_CISR_F_T           F;
   uint16_t               U16[TPU_ARRAY_SIZE_02];
   uint32_t               U32;

}  TPU_CISR_T;

//=============================================================================
// ID - eTPU Channel Data Transfer Request Status Register (TPU_CDTRSR)
//
// Base Offset : 0000 0210 H  or  ( TPU_CDTRSR_1 )
//               0000 0214 H      ( TPU_CDTRSR_2 )
//
// Reset Value : 0000 0000 H     ( TPU_CDTRSR_1 )
//               0000 0000 H     ( TPU_CDTRSR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// DTRSn       [31:00]     r  Channel n data transfer request status.
//                              0 Indicates that channel n has no pending
//                                data transfer request.
//                              1 Indicates that channel n has a pending
//                                data transfer request.
//
// DTRCn       [31:00]     w  Channel n data transfer request clear.
//                              0 Keep status bit unaltered
//                              1 Clear status bit.
//
//=============================================================================

typedef struct TPU_CDTRSR_F_Tag
{
   bitfield32_t   DTRC31:  BIT_1;   // Bit  31
   bitfield32_t   DTRC30:  BIT_1;   // Bit  30
   bitfield32_t   DTRC29:  BIT_1;   // Bit  29
   bitfield32_t   DTRC28:  BIT_1;   // Bit  28
   bitfield32_t   DTRC27:  BIT_1;   // Bit  27
   bitfield32_t   DTRC26:  BIT_1;   // Bit  26
   bitfield32_t   DTRC25:  BIT_1;   // Bit  25
   bitfield32_t   DTRC24:  BIT_1;   // Bit  24
   bitfield32_t   DTRC23:  BIT_1;   // Bit  23
   bitfield32_t   DTRC22:  BIT_1;   // Bit  22
   bitfield32_t   DTRC21:  BIT_1;   // Bit  21
   bitfield32_t   DTRC20:  BIT_1;   // Bit  20
   bitfield32_t   DTRC19:  BIT_1;   // Bit  19
   bitfield32_t   DTRC18:  BIT_1;   // Bit  18
   bitfield32_t   DTRC17:  BIT_1;   // Bit  17
   bitfield32_t   DTRC16:  BIT_1;   // Bit  16
   bitfield32_t   DTRC15:  BIT_1;   // Bit  15
   bitfield32_t   DTRC14:  BIT_1;   // Bit  14
   bitfield32_t   DTRC13:  BIT_1;   // Bit  13
   bitfield32_t   DTRC12:  BIT_1;   // Bit  12
   bitfield32_t   DTRC11:  BIT_1;   // Bit  11
   bitfield32_t   DTRC10:  BIT_1;   // Bit  10
   bitfield32_t   DTRC09:  BIT_1;   // Bit   9
   bitfield32_t   DTRC08:  BIT_1;   // Bit   8
   bitfield32_t   DTRC07:  BIT_1;   // Bit   7
   bitfield32_t   DTRC06:  BIT_1;   // Bit   6
   bitfield32_t   DTRC05:  BIT_1;   // Bit   5
   bitfield32_t   DTRC04:  BIT_1;   // Bit   4
   bitfield32_t   DTRC03:  BIT_1;   // Bit   3
   bitfield32_t   DTRC02:  BIT_1;   // Bit   2
   bitfield32_t   DTRC01:  BIT_1;   // Bit   1
   bitfield32_t   DTRC00:  BIT_1;   // Bit   0

}  TPU_CDTRSR_F_T;

typedef union TPU_CDTRSR_Tag
{
   TPU_CDTRSR_F_T            F;
   uint16_t                  U16[TPU_ARRAY_SIZE_02];
   uint32_t                  U32;

}  TPU_CDTRSR_T;

//=============================================================================
// ID - eTPU Channel Interrupt Overflow Status Register (TPU_CIOSR)
//
// Base Offset : 0000 0220 H  or  ( TPU_CIOSR_1 )
//               0000 0224 H      ( TPU_CIOSR_2 )
//
// Reset Value : 0000 0000 H      ( TPU_CIOSR_1 )
//               0000 0000 H      ( TPU_CIOSR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// CIOSn       [31:00]     r  Channel n interrupt overflow status.
//                              0 indicates that no interrupt overflow
//                                occurred in the channel.
//                              1 indicates that an interrupt overflow
//                                occurred in the channel.
//
// CIOCn       [31:00]     r  Channel n interrupt overflow clear.
//                              0 keep status bit unaltered.
//                              1 clear status bit.
//
//=============================================================================

typedef struct TPU_CIOSR_F_Tag
{
   bitfield32_t   CIOC31:  BIT_1;   // Bit  31
   bitfield32_t   CIOC30:  BIT_1;   // Bit  30
   bitfield32_t   CIOC29:  BIT_1;   // Bit  29
   bitfield32_t   CIOC28:  BIT_1;   // Bit  28
   bitfield32_t   CIOC27:  BIT_1;   // Bit  27
   bitfield32_t   CIOC26:  BIT_1;   // Bit  26
   bitfield32_t   CIOC25:  BIT_1;   // Bit  25
   bitfield32_t   CIOC24:  BIT_1;   // Bit  24
   bitfield32_t   CIOC23:  BIT_1;   // Bit  23
   bitfield32_t   CIOC22:  BIT_1;   // Bit  22
   bitfield32_t   CIOC21:  BIT_1;   // Bit  21
   bitfield32_t   CIOC20:  BIT_1;   // Bit  20
   bitfield32_t   CIOC19:  BIT_1;   // Bit  19
   bitfield32_t   CIOC18:  BIT_1;   // Bit  18
   bitfield32_t   CIOC17:  BIT_1;   // Bit  17
   bitfield32_t   CIOC16:  BIT_1;   // Bit  16
   bitfield32_t   CIOC15:  BIT_1;   // Bit  15
   bitfield32_t   CIOC14:  BIT_1;   // Bit  14
   bitfield32_t   CIOC13:  BIT_1;   // Bit  13
   bitfield32_t   CIOC12:  BIT_1;   // Bit  12
   bitfield32_t   CIOC11:  BIT_1;   // Bit  11
   bitfield32_t   CIOC10:  BIT_1;   // Bit  10
   bitfield32_t   CIOC09:  BIT_1;   // Bit   9
   bitfield32_t   CIOC08:  BIT_1;   // Bit   8
   bitfield32_t   CIOC07:  BIT_1;   // Bit   7
   bitfield32_t   CIOC06:  BIT_1;   // Bit   6
   bitfield32_t   CIOC05:  BIT_1;   // Bit   5
   bitfield32_t   CIOC04:  BIT_1;   // Bit   4
   bitfield32_t   CIOC03:  BIT_1;   // Bit   3
   bitfield32_t   CIOC02:  BIT_1;   // Bit   2
   bitfield32_t   CIOC01:  BIT_1;   // Bit   1
   bitfield32_t   CIOC00:  BIT_1;   // Bit   0

}  TPU_CIOSR_F_T;

typedef union TPU_CIOSR_Tag
{
   TPU_CIOSR_F_T             F;
   uint16_t                  U16[TPU_ARRAY_SIZE_02];
   uint32_t                  U32;

}  TPU_CIOSR_T;

//=============================================================================
// ID - eTPU Channel Data Transfer Request Overflow Status Register
//      (TPU_CDTROSR)
//
// Base Offset : 0000 0230 H  or   ( TPU_CDTROSR_1 )
//               0000 0234 H       ( TPU_CDTROSR_2 )
//
// Reset Value : 0000 0000 H       ( TPU_CDTROSR_1 )
//               0000 0000 H       ( TPU_CDTROSR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// DTROSn      [31:00]     r  Channel n data transfer request overflow
//                            status.
//                              0 indicates that no data transfer request
//                                overflow occurred in the channel
//                              1 indicates that a data transfer request
//                                overflow occurred in the channel.
//
// DTROCn      [31:00]     r  Channel n data transfer request overflow clear.
//                              0 keep status bit unaltered.
//                              1 clear status bit.
//
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct TPU_CDTROSR_F_Tag
{
   bitfield32_t   DTROC31 :  BIT_1;   // Bit  31
   bitfield32_t   DTROC30 :  BIT_1;   // Bit  30
   bitfield32_t   DTROC29 :  BIT_1;   // Bit  29
   bitfield32_t   DTROC28 :  BIT_1;   // Bit  28
   bitfield32_t   DTROC27 :  BIT_1;   // Bit  27
   bitfield32_t   DTROC26 :  BIT_1;   // Bit  26
   bitfield32_t   DTROC25 :  BIT_1;   // Bit  25
   bitfield32_t   DTROC24 :  BIT_1;   // Bit  24
   bitfield32_t   DTROC23 :  BIT_1;   // Bit  23
   bitfield32_t   DTROC22 :  BIT_1;   // Bit  22
   bitfield32_t   DTROC21 :  BIT_1;   // Bit  21
   bitfield32_t   DTROC20 :  BIT_1;   // Bit  20
   bitfield32_t   DTROC19 :  BIT_1;   // Bit  19
   bitfield32_t   DTROC18 :  BIT_1;   // Bit  18
   bitfield32_t   DTROC17 :  BIT_1;   // Bit  17
   bitfield32_t   DTROC16 :  BIT_1;   // Bit  16
   bitfield32_t   DTROC15 :  BIT_1;   // Bit  15
   bitfield32_t   DTROC14 :  BIT_1;   // Bit  14
   bitfield32_t   DTROC13 :  BIT_1;   // Bit  13
   bitfield32_t   DTROC12 :  BIT_1;   // Bit  12
   bitfield32_t   DTROC11 :  BIT_1;   // Bit  11
   bitfield32_t   DTROC10 :  BIT_1;   // Bit  10
   bitfield32_t   DTROC09 :  BIT_1;   // Bit   9
   bitfield32_t   DTROC08 :  BIT_1;   // Bit   8
   bitfield32_t   DTROC07 :  BIT_1;   // Bit   7
   bitfield32_t   DTROC06 :  BIT_1;   // Bit   6
   bitfield32_t   DTROC05 :  BIT_1;   // Bit   5
   bitfield32_t   DTROC04 :  BIT_1;   // Bit   4
   bitfield32_t   DTROC03 :  BIT_1;   // Bit   3
   bitfield32_t   DTROC02 :  BIT_1;   // Bit   2
   bitfield32_t   DTROC01 :  BIT_1;   // Bit   1
   bitfield32_t   DTROC00 :  BIT_1;   // Bit   0

}  TPU_CDTROSR_F_T;

typedef union TPU_CDTROSR_Tag
{
   TPU_CDTROSR_F_T           F;
   uint16_t                  U16[TPU_ARRAY_SIZE_02];
   uint32_t                  U32;

}  TPU_CDTROSR_T;

//=============================================================================
// ID - eTPU Channel Interrupt Enable Register (TPU_CIER)
//
// Base Offset : 0000 0240 H  or   ( TPU_CIER_1 )
//               0000 0244 H       ( TPU_CIER_2 )
//
// Reset Value : 0000 0000 H        ( TPU_CIER_1 )
//               0000 0000 H        ( TPU_CIER_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// CIEn        [31:00]    rw  Channel n interrupt enable. Enable the eTPU
//                            channels to interrupt the MPC5554 CPU.
//                              0 Interrupt disabled for channel n.
//                              1 Interrupt enabled for channel n
//
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct TPU_CIER_F_Tag
{
   bitfield32_t   CIE31      :  BIT_1;   // Bit  31
   bitfield32_t   CIE30      :  BIT_1;   // Bit  30
   bitfield32_t   CIE29      :  BIT_1;   // Bit  29
   bitfield32_t   CIE28      :  BIT_1;   // Bit  28
   bitfield32_t   CIE27      :  BIT_1;   // Bit  27
   bitfield32_t   CIE26      :  BIT_1;   // Bit  26
   bitfield32_t   CIE25      :  BIT_1;   // Bit  25
   bitfield32_t   CIE24      :  BIT_1;   // Bit  24
   bitfield32_t   CIE23      :  BIT_1;   // Bit  23
   bitfield32_t   CIE22      :  BIT_1;   // Bit  22
   bitfield32_t   CIE21      :  BIT_1;   // Bit  21
   bitfield32_t   CIE20      :  BIT_1;   // Bit  20
   bitfield32_t   CIE19      :  BIT_1;   // Bit  19
   bitfield32_t   CIE18      :  BIT_1;   // Bit  18
   bitfield32_t   CIE17      :  BIT_1;   // Bit  17
   bitfield32_t   CIE16      :  BIT_1;   // Bit  16
   bitfield32_t   CIE15      :  BIT_1;   // Bit  15
   bitfield32_t   CIE14      :  BIT_1;   // Bit  14
   bitfield32_t   CIE13      :  BIT_1;   // Bit  13
   bitfield32_t   CIE12      :  BIT_1;   // Bit  12
   bitfield32_t   CIE11      :  BIT_1;   // Bit  11
   bitfield32_t   CIE10      :  BIT_1;   // Bit  10
   bitfield32_t   CIE09      :  BIT_1;   // Bit   9
   bitfield32_t   CIE08      :  BIT_1;   // Bit   8
   bitfield32_t   CIE07      :  BIT_1;   // Bit   7
   bitfield32_t   CIE06      :  BIT_1;   // Bit   6
   bitfield32_t   CIE05      :  BIT_1;   // Bit   5
   bitfield32_t   CIE04      :  BIT_1;   // Bit   4
   bitfield32_t   CIE03      :  BIT_1;   // Bit   3
   bitfield32_t   CIE02      :  BIT_1;   // Bit   2
   bitfield32_t   CIE01      :  BIT_1;   // Bit   1
   bitfield32_t   CIE00      :  BIT_1;   // Bit   0

}  TPU_CIER_F_T;

typedef union TPU_CIER_Tag
{
   TPU_CIER_F_T         F;
   uint16_t             U16[TPU_ARRAY_SIZE_02];
   uint32_t             U32;

}  TPU_CIER_T;

//=============================================================================
// ID - eTPU Channel Data Transfer Request Enable Register (TPU_CDTRER)
//
// Base Offset : 0000 0250 H  or    ( TPU_CDTRER_1 )
//               0000 0254 H        ( TPU_CDTRER_2 )
//
// Reset Value : 0000 0000 H        ( TPU_CDTRER_1 )
//               0000 0000 H        ( TPU_CDTRER_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// DTREn       [31:00]    rw  Channel n data transfer request enable. Enable
//                            data transfer requests for their respective
//                            channels.
//
//                              0 Data transfer request disabled for
//                                channel n.
//                              1 Data transfer request enabled for
//                                channel n.
//
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct TPU_CDTRER_F_Tag
{
   bitfield32_t   DTRE31     :  BIT_1;   // Bit  31
   bitfield32_t   DTRE30     :  BIT_1;   // Bit  30
   bitfield32_t   DTRE29     :  BIT_1;   // Bit  29
   bitfield32_t   DTRE28     :  BIT_1;   // Bit  28
   bitfield32_t   DTRE27     :  BIT_1;   // Bit  27
   bitfield32_t   DTRE26     :  BIT_1;   // Bit  26
   bitfield32_t   DTRE25     :  BIT_1;   // Bit  25
   bitfield32_t   DTRE24     :  BIT_1;   // Bit  24
   bitfield32_t   DTRE23     :  BIT_1;   // Bit  23
   bitfield32_t   DTRE22     :  BIT_1;   // Bit  22
   bitfield32_t   DTRE21     :  BIT_1;   // Bit  21
   bitfield32_t   DTRE20     :  BIT_1;   // Bit  20
   bitfield32_t   DTRE19     :  BIT_1;   // Bit  19
   bitfield32_t   DTRE18     :  BIT_1;   // Bit  18
   bitfield32_t   DTRE17     :  BIT_1;   // Bit  17
   bitfield32_t   DTRE16     :  BIT_1;   // Bit  16
   bitfield32_t   DTRE15     :  BIT_1;   // Bit  15
   bitfield32_t   DTRE14     :  BIT_1;   // Bit  14
   bitfield32_t   DTRE13     :  BIT_1;   // Bit  13
   bitfield32_t   DTRE12     :  BIT_1;   // Bit  12
   bitfield32_t   DTRE11     :  BIT_1;   // Bit  11
   bitfield32_t   DTRE10     :  BIT_1;   // Bit  10
   bitfield32_t   DTRE09     :  BIT_1;   // Bit   9
   bitfield32_t   DTRE08     :  BIT_1;   // Bit   8
   bitfield32_t   DTRE07     :  BIT_1;   // Bit   7
   bitfield32_t   DTRE06     :  BIT_1;   // Bit   6
   bitfield32_t   DTRE05     :  BIT_1;   // Bit   5
   bitfield32_t   DTRE04     :  BIT_1;   // Bit   4
   bitfield32_t   DTRE03     :  BIT_1;   // Bit   3
   bitfield32_t   DTRE02     :  BIT_1;   // Bit   2
   bitfield32_t   DTRE01     :  BIT_1;   // Bit   1
   bitfield32_t   DTRE00     :  BIT_1;   // Bit   0

}  TPU_CDTRER_F_T;

typedef union TPU_CDTRER_Tag
{
   TPU_CDTRER_F_T       F;
   uint16_t             U16[TPU_ARRAY_SIZE_02];
   uint32_t             U32;

}  TPU_CDTRER_T;

//=============================================================================
// ID - eTPU Watch Dog Status Register (TPU_WDSR)
//
// Base Offset : 0000 0260 H  or   ( TPU_WDSR_1 )
//               0000 0264 H       ( TPU_WDSR_2 )
//
// Reset Value : 0000 0000 H       ( TPU_WDSR_1 )
//               0000 0000 H       ( TPU_WDSR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// WDSx      [31:00]     r  Channel x watch dog status                
//                              0 no watchdog force on the channel
//                              1 watchdog forced end of the channel thread and disabled it.
//
// WDSCx     [31:00]    w  Channel x Watchdog Status Clear
//                              0 keep watchdog status bit unaltered.
//                              1 clear watchdog status bit.
//========================================================================
typedef struct TPU_WDSR_F_Tag
{
   bitfield32_t   WDSC31 :  BIT_1;   // Bit  31
   bitfield32_t   WDSC30 :  BIT_1;   // Bit  30
   bitfield32_t   WDSC29 :  BIT_1;   // Bit  29
   bitfield32_t   WDSC28 :  BIT_1;   // Bit  28
   bitfield32_t   WDSC27 :  BIT_1;   // Bit  27
   bitfield32_t   WDSC26 :  BIT_1;   // Bit  26
   bitfield32_t   WDSC25 :  BIT_1;   // Bit  25
   bitfield32_t   WDSC24 :  BIT_1;   // Bit  24
   bitfield32_t   WDSC23 :  BIT_1;   // Bit  23
   bitfield32_t   WDSC22 :  BIT_1;   // Bit  22
   bitfield32_t   WDSC21 :  BIT_1;   // Bit  21
   bitfield32_t   WDSC20 :  BIT_1;   // Bit  20
   bitfield32_t   WDSC19 :  BIT_1;   // Bit  19
   bitfield32_t   WDSC18 :  BIT_1;   // Bit  18
   bitfield32_t   WDSC17 :  BIT_1;   // Bit  17
   bitfield32_t   WDSC16 :  BIT_1;   // Bit  16
   bitfield32_t   WDSC15 :  BIT_1;   // Bit  15
   bitfield32_t   WDSC14 :  BIT_1;   // Bit  14
   bitfield32_t   WDSC13 :  BIT_1;   // Bit  13
   bitfield32_t   WDSC12 :  BIT_1;   // Bit  12
   bitfield32_t   WDSC11 :  BIT_1;   // Bit  11
   bitfield32_t   WDSC10 :  BIT_1;   // Bit  10
   bitfield32_t   WDSC09 :  BIT_1;   // Bit   9
   bitfield32_t   WDSC08 :  BIT_1;   // Bit   8
   bitfield32_t   WDSC07 :  BIT_1;   // Bit   7
   bitfield32_t   WDSC06 :  BIT_1;   // Bit   6
   bitfield32_t   WDSC05 :  BIT_1;   // Bit   5
   bitfield32_t   WDSC04 :  BIT_1;   // Bit   4
   bitfield32_t   WDSC03 :  BIT_1;   // Bit   3
   bitfield32_t   WDSC02 :  BIT_1;   // Bit   2
   bitfield32_t   WDSC01 :  BIT_1;   // Bit   1
   bitfield32_t   WDSC00 :  BIT_1;   // Bit   0

}  TPU_WDSR_F_T;
 
typedef union TPU_WDSR_Tag
{
   TPU_WDSR_F_T           F;
   uint16_t               U16[TPU_ARRAY_SIZE_02];
   uint32_t               U32;

}  TPU_WDSR_T;

//=============================================================================
// ID - eTPU Channel Pending Service Status Register (TPU_CPSSR)
//
// Base Offset : 0000 0280 H  or   ( TPU_CPSSR_1 )
//               0000 0284 H       ( TPU_CPSSR_2 )
//
// Reset Value : 0000 0000 H       ( TPU_CPSSR_1 )
//               0000 0000 H       ( TPU_CPSSR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// SRn         [31:00]     r  Pending service request n. Indicates a pending
//                            service request for channel n. The SR status
//                            for the pending request is negated at the time
//                            slot transition for the respective service
//                            thread.
//
//                              0 no service request pending for channel n
//                              1 pending service request for channel n
//
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct TPU_CPSSR_F_Tag
{
   bitfield32_t   SR31       :  BIT_1;   // Bit  31
   bitfield32_t   SR30       :  BIT_1;   // Bit  30
   bitfield32_t   SR29       :  BIT_1;   // Bit  29
   bitfield32_t   SR28       :  BIT_1;   // Bit  28
   bitfield32_t   SR27       :  BIT_1;   // Bit  27
   bitfield32_t   SR26       :  BIT_1;   // Bit  26
   bitfield32_t   SR25       :  BIT_1;   // Bit  25
   bitfield32_t   SR24       :  BIT_1;   // Bit  24
   bitfield32_t   SR23       :  BIT_1;   // Bit  23
   bitfield32_t   SR22       :  BIT_1;   // Bit  22
   bitfield32_t   SR21       :  BIT_1;   // Bit  21
   bitfield32_t   SR20       :  BIT_1;   // Bit  20
   bitfield32_t   SR19       :  BIT_1;   // Bit  19
   bitfield32_t   SR18       :  BIT_1;   // Bit  18
   bitfield32_t   SR17       :  BIT_1;   // Bit  17
   bitfield32_t   SR16       :  BIT_1;   // Bit  16
   bitfield32_t   SR15       :  BIT_1;   // Bit  15
   bitfield32_t   SR14       :  BIT_1;   // Bit  14
   bitfield32_t   SR13       :  BIT_1;   // Bit  13
   bitfield32_t   SR12       :  BIT_1;   // Bit  12
   bitfield32_t   SR11       :  BIT_1;   // Bit  11
   bitfield32_t   SR10       :  BIT_1;   // Bit  10
   bitfield32_t   SR09       :  BIT_1;   // Bit   9
   bitfield32_t   SR08       :  BIT_1;   // Bit   8
   bitfield32_t   SR07       :  BIT_1;   // Bit   7
   bitfield32_t   SR06       :  BIT_1;   // Bit   6
   bitfield32_t   SR05       :  BIT_1;   // Bit   5
   bitfield32_t   SR04       :  BIT_1;   // Bit   4
   bitfield32_t   SR03       :  BIT_1;   // Bit   3
   bitfield32_t   SR02       :  BIT_1;   // Bit   2
   bitfield32_t   SR01       :  BIT_1;   // Bit   1
   bitfield32_t   SR00       :  BIT_1;   // Bit   0

}  TPU_CPSSR_F_T;

typedef union TPU_CPSSR_Tag
{
   TPU_CPSSR_F_T        F;
   uint16_t             U16[TPU_ARRAY_SIZE_02];
   uint32_t             U32;

}  TPU_CPSSR_T;

//=============================================================================
// ID - eTPU Channel Service Status Register (TPU_CSSR)
//
// Base Offset : 0000 0290 H  or   ( TPU_CSSR_1 )
//               0000 0294 H       ( TPU_CSSR_2 )
//
// Reset Value : 0000 0000 H      ( TPU_CSSR_1 )
//               0000 0000 H      ( TPU_CSSR_2 )
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// SSn         [31:00]     r  Service status n. Indicates that channel n is
//                            currently being serviced. It is updated at
//                            the 1st microcycle of a time slot transition.
//
//                              0 channel n is not currently being serviced
//                              1 channel n is currently being serviced
//
//=============================================================================

typedef struct TPU_CSSR_F_Tag
{
   bitfield32_t   SS31       :  BIT_1;   // Bit  31
   bitfield32_t   SS30       :  BIT_1;   // Bit  30
   bitfield32_t   SS29       :  BIT_1;   // Bit  29
   bitfield32_t   SS28       :  BIT_1;   // Bit  28
   bitfield32_t   SS27       :  BIT_1;   // Bit  27
   bitfield32_t   SS26       :  BIT_1;   // Bit  26
   bitfield32_t   SS25       :  BIT_1;   // Bit  25
   bitfield32_t   SS24       :  BIT_1;   // Bit  24
   bitfield32_t   SS23       :  BIT_1;   // Bit  23
   bitfield32_t   SS22       :  BIT_1;   // Bit  22
   bitfield32_t   SS21       :  BIT_1;   // Bit  21
   bitfield32_t   SS20       :  BIT_1;   // Bit  20
   bitfield32_t   SS19       :  BIT_1;   // Bit  19
   bitfield32_t   SS18       :  BIT_1;   // Bit  18
   bitfield32_t   SS17       :  BIT_1;   // Bit  17
   bitfield32_t   SS16       :  BIT_1;   // Bit  16
   bitfield32_t   SS15       :  BIT_1;   // Bit  15
   bitfield32_t   SS14       :  BIT_1;   // Bit  14
   bitfield32_t   SS13       :  BIT_1;   // Bit  13
   bitfield32_t   SS12       :  BIT_1;   // Bit  12
   bitfield32_t   SS11       :  BIT_1;   // Bit  11
   bitfield32_t   SS10       :  BIT_1;   // Bit  10
   bitfield32_t   SS09       :  BIT_1;   // Bit   9
   bitfield32_t   SS08       :  BIT_1;   // Bit   8
   bitfield32_t   SS07       :  BIT_1;   // Bit   7
   bitfield32_t   SS06       :  BIT_1;   // Bit   6
   bitfield32_t   SS05       :  BIT_1;   // Bit   5
   bitfield32_t   SS04       :  BIT_1;   // Bit   4
   bitfield32_t   SS03       :  BIT_1;   // Bit   3
   bitfield32_t   SS02       :  BIT_1;   // Bit   2
   bitfield32_t   SS01       :  BIT_1;   // Bit   1
   bitfield32_t   SS00       :  BIT_1;   // Bit   0

}  TPU_CSSR_F_T;

typedef union TPU_CSSR_Tag
{
   TPU_CSSR_F_T         F;
   uint16_t             U16[TPU_ARRAY_SIZE_02];
   uint32_t             U32;

}  TPU_CSSR_T;

//=============================================================================
// ID - eTPU Channel n Configuration Register (TPU_CnCR)
//
// Channel Reg Base Offset : 0000 0000 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// CIE              31    rw  Channel interrupt enable. This bit is mirrored
//                            from the TPU_CIER
//                              0 Disable interrupt for this channel.
//                              1 Enable interrupt for this channel.
//
// DTRE             30    rw  Channel data transfer request enable. This
//                            bit is mirrored from the TPU_CDTRER.
//
//                              0 Disable data transfer request for this
//                                channel.
//                              1 Enable data transfer request for this
//                                channel.
//
// CPR[1:0]    [29:28]    rw  Channel priority. Defines the priority level
//                            for the channel. The priority level is used
//                            by the hardware scheduler. The values for
//                            CPR[1:0] and corresponding levels are shown
//                            in the table below.
//
//                                     CPR           Priority
//                                     00            Disabled
//                                     01            Low
//                                     10            Middle
//                                     11            High
//
// 0           [27:26]     r  Reserved.
//
// ETPD            25     rw  Entry Table Pin Direction. This Bit selects 
//                             which channel signal, input or output, is used
//                             in the Entry Point selection. The ETPD value 
//                             has to be compatible with the function chosen 
//                             for the channel, selected in the field CFS
//                             
//                             1 Use PSTO for Entry Point selection.
//                             0 Use PSTI for Entry Point selection.
//
// ETCS             24    rw  Entry table condition select. Determines the
//                            channel condition encoding scheme that
//                            selects the entry point to be taken in an
//                            entry table. The ETCS value has to be
//                            compatible with the function chosen for the
//                            channel, selected in TPU_CnCR[CFS].
//                            Two condition encoding schemes are
//                            available.
//
//                              1 Select alternate entry table condition
//                                encoding scheme.
//                              0 Select standard entry table condition
//                                encoding scheme.
//
// 0           [23:21]     r  Reserved.
//
// CFS         [20:16]    rw  Channel function select. Defines the function
//                            to be performed by the channel. The function
//                            assigned to the channel has to be compatible
//                            with the channel condition encoding scheme,
//                            selected by TPU_CnCR[ETCS].
//
// ODIS             15    rw  Output disable. Enables the channel to have
//                            its output forced to the value opposite to
//                            OPOL when the output disable input signal
//                            corresponding to the channel group that it
//                            belongs is active.
//
//                              0 Turns off the output disable feature for
//                                the channel.
//                              1 Turns on the output disable feature for
//                                the channel
//
// OPOL             14    rw  Output polarity. Determines the output signal
//                            polarity. The activation of the output disable
//                            signal forces, when enabled by TPU_CnCR[ODIS],
//                            the channel output signal to the opposite of
//                            this polarity.
//
//                              0 Output active low (output disable drives
//                                output to high)
//                              1 Output active high (output disable drives
//                                output to low)
//
// 0           [13:11]     r  Reserved.
//
// CPBA        [10:00]    rw  Channel n parameter base address. The
//                            value of this field multiplied by 8
//                            specifies the SPRAM parameter base host
//                            (byte) address for channel n (2-parameter
//                            granularity). The formula for calculating
//                            the absolute channel parameter base (byte)
//                            address, as seen by the host, is eTPU_Base
//                            + 0x8000 + CPBA*8. The SPRAM is mirrored in
//                            the parameter sign extension (PSE) area. The
//                            formula to calculate the absolute channel
//                            parameter base (byte) address in the PSE area
//                            is eTPU_Base + 0xC000 + CPBA*8.
//
//=============================================================================

typedef struct TPU_CCR_F_Tag
{
   bitfield32_t   CIE       :  BIT_1;  // Bit      31
   bitfield32_t   DTRE      :  BIT_1;  // Bit      30
   bitfield32_t   CPR       :  BIT_2;  // Bit  [29:28]
   bitfield32_t             :  BIT_2;  // Bits [27:26] are reserved
   bitfield32_t   ETPD      :  BIT_1;  // Bit  25
   bitfield32_t   ETCS      :  BIT_1;  // Bit      24
   bitfield32_t             :  BIT_3;  // Bits [23:21] are reserved
   bitfield32_t   CFS       :  BIT_5;  // Bits [20:16]
   bitfield32_t   ODIS      :  BIT_1;  // Bit      15
   bitfield32_t   OPOL      :  BIT_1;  // Bit      14
   bitfield32_t             :  BIT_3;  // Bits [13:11] are reserved
   bitfield32_t   CPBA      :  BIT_11; // Bits [10: 0]

}  TPU_CCR_F_T;

typedef union TPU_CCR_Tag
{
   TPU_CCR_F_T          F;
   uint16_t             U16[TPU_ARRAY_SIZE_02];
   uint32_t             U32;

}  TPU_CCR_T;

//=============================================================================
// ID - eTPU Channel n Status Control Register (TPU_CnSCR)
//
// Channel Reg Base Offset : : 0000 0004 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// CIS              31     r  Channel interrupt status.
//                              0 Channel has no pending interrupt to the
//                                MPC5554 CPU.
//                              1 Channel has a pending interrupt to the
//                                MPC5554 CPU.
//                            CIS and CIC are mirrored in the TPU_CISR.
//
// CIC              31     w  Channel interrupt clear.
//                              0 Keep interrupt status bit unaltered.
//                              1 Clear interrupt status bit.
//                            CIS and CIC are mirrored in the TPU_CISR.
//
// CIOS             30     r  Channel interrupt overflow status.
//                              0 Interrupt overflow negated for this
//                                channel
//                              1 Interrupt overflow asserted for this
//                                channel
//                            CIOS and CIOC are mirrored in the TPU_CIOSR.
//
// CIOC             30     w  Channel interrupt overflow clear.
//                              0 Keep status bit unaltered.
//                              1 Clear status bit.
//                            CIOS and CIOC are mirrored in the TPU_CIOSR.
//
// 0           [29:24]     r  Reserved.
//
// DTRS             23     r  Data transfer request status.
//                              0 Channel has no pending data transfer
//                                request.
//                              1 Channel has a pending data transfer
//                                request.
//                            DTRS and DTRC are mirrored in the TPU_CISR.
//
// DTRC             23     w  Data transfer request clear.
//                              0 Keep status bit unaltered
//                              1 Clear status bit.
//                            DTRS and DTRC are mirrored in the TPU_CISR.
//
// DTROS            22     r  Data transfer request overflow status.
//                              0 Data transfer request overflow
//                                negated for this channel.
//                              1 Data transfer request overflow
//                                asserted for this channel.
//                            DTROS and DTROC are mirrored in the
//                            TPU_CDTROSR.
//
// DTROC            22     w  Data transfer request overflow clear.
//                              0 Keep status bit unaltered.
//                              1 Clear status bit.
//                            DTROS and DTROC are mirrored in the
//                            TPU_CDTROSR.
//
// 0           [21:16]     r  Reserved.
//
// IPS              15     r  Channel input pin state. Shows the current
//                            value of the filtered channel input signal
//                            state.
//
// OPS              14     r  Channel output pin state. Shows the current
//                            value driven in the channel output signal,
//                            including the effect of the external output
//                            disable feature. If the channel input and
//                            output signals are connected to the same
//                            pad, OPS reflects the value driven to the pad
//                            (if OBE = 1).This is not necessarily the actual
//                            pad value, which drives the value in the
//                            IPS bit.
//
// OBE               13   r Output Buffer Enable. Shows the state of the 
//                            channel output buffer enable signal, controlled 
//                            by microcode.
//
// 0           [12:02]     r  Reserved.
//
// FM          [01:00]    rw  Channel function mode1. Each function may
//                            use this field for specific configuration.
//                            These bits can be tested by microengine code.
//
//=============================================================================

typedef struct TPU_CSCR_F_Tag
{
   bitfield32_t   CIS_CIC     :  BIT_1;  // Bit      31
   bitfield32_t   CIOS_CIOC   :  BIT_1;  // Bit      30
   bitfield32_t               :  BIT_6;  // Bits [29:24] are reserved
   bitfield32_t   DTRS_DTRC   :  BIT_1;  // Bit      23
   bitfield32_t   DTROS_DTROC :  BIT_1;  // Bit      22
   bitfield32_t               :  BIT_6;  // Bits [21:16] are reserved
   bitfield32_t   IPS         :  BIT_1;  // Bit      15
   bitfield32_t   OPS         :  BIT_1;  // Bit      14
   bitfield32_t   OBE         :  BIT_1;  // Bit      13
   bitfield32_t               :  BIT_11; // Bits [12: 2] are reserved
   bitfield32_t   FM1         :  BIT_1;  // Bits      1
   bitfield32_t   FM0         :  BIT_1;  // Bits      0
}  TPU_CSCR_F_T;

typedef union TPU_CSCR_Tag
{
   TPU_CSCR_F_T                 F;
   uint16_t                     U16[TPU_ARRAY_SIZE_02];
   uint32_t                     U32;

}  TPU_CSCR_T;

//=============================================================================
// ID - eTPU Channel n Host Service Request Register (TPU_CnHSRR)
//
// Channel Reg Base Offset : : 0000 0008 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0           [31:03]     r  Reserved.
//
// HSR         [02:00]    rw  Host service request. Used by the host CPU
//                            to request service to the channel
//                            - HSR = 000: no host service request pending
//                            - HSR > 000: function-dependent host service
//                              request pending.
//                            The HSR value turns to 000 automatically at
//                            the end of microengine service for that
//                            channel. The host should write HSR > 0
//                            only when HSR = 0. Writing HSR = 000
//                            withdraws a pending request if the
//                            scheduler has not started to resolve the
//                            entry point, however once the scheduler
//                            starts resolving, the service thread will not
//                            be aborted.
//
//=============================================================================

typedef struct TPU_CHSRR_F_Tag
{
   bitfield32_t             :  BIT_29;  // Bits [31: 3] are reserved
   bitfield32_t   HSR       :  BIT_3;   // Bits [ 2: 0]

}  TPU_CHSRR_F_T;


typedef union TPU_CHSRR_Tag
{
   TPU_CHSRR_F_T          F;
   uint32_t               U32;

}  TPU_CHSRR_T;

//=============================================================================
//  ETPU Module Register Structure
//=============================================================================
typedef struct TPU_Channel_Control_Tag
{
   TPU_CCR_T            CCR;
   TPU_CSCR_T           CSCR;
   TPU_CHSRR_T          CHSRR;
   uint8_t              reserved[TPU_RESERVED_0004];
}  TPU_Channel_Control_T;

//=============================================================================
//  ETPU Module Register Structure
//=============================================================================
typedef struct TPU_Channel_Control_Init_Tag
{
   TPU_CCR_T            CCR;
   TPU_CSCR_T           CSCR;
   TPU_CHSRR_T          CHSRR;
}  TPU_Channel_Control_Init_T;

typedef struct TPU_Channel_Map_Tag
{
   TPU_Channel_Control_T         Channel_Control[TPU_CHANNEL_CONTROL_QUANTITY];
   uint8_t                       reserved13[TPU_RESERVED_0200];
}  TPU_Channel_Map_T;

typedef volatile struct TPU_Tag
{
   TPU_MCR_T                     MCR;                             // 0x0000 - 0x0003
   
   TPU_CDCR_T                    CDCR;                            // 0x0004 - 0x0007
   
   uint8_t                       reserved0[TPU_RESERVED_0004];    // 0x0008 - 0x000B
   
   TPU_MISCCMPR_T                MISCCMPR;                        // 0x000C - 0x000F
   
   uint32_t                      SCMOFFDATAR;                     // 0x0010 - 0x0013
   
   TPU_ECR_T                     ECR[TPU_ARRAY_SIZE_01];          // 0x0014 - 0x0017
   
   uint8_t                       reserved1[TPU_RESERVED_0008];    // 0x0018 - 0x001F
   
   TPU_Clock_T                   Clock[TPU_ARRAY_SIZE_01];        // 0x0020 - 0x003F

   uint8_t                       reserved2[TPU_RESERVED_0020];    // 0x0040 - 0x005F

   TPU_Wdt_Idle_T                Wdt_Idle[TPU_ARRAY_SIZE_01];     // 0x0060 - 0x006F

   uint8_t                       reserved5[TPU_RESERVED_0190];    // 0x0070 - 0x01FF

   TPU_CISR_T                    CISR[TPU_ARRAY_SIZE_01];         // 0x0200 - 0x0203
   
   uint8_t                       reserved6[TPU_RESERVED_000C];    // 0x0204 - 0x020F
   
   TPU_CDTRSR_T                  CDTRSR[TPU_ARRAY_SIZE_01];       // 0x0210 - 0x0213
   
   uint8_t                       reserved7[TPU_RESERVED_000C];    // 0x0214 - 0x021F
   
   TPU_CIOSR_T                   CIOSR[TPU_ARRAY_SIZE_01];        // 0x0220 - 0x0223
   
   uint8_t                       reserved8[TPU_RESERVED_000C];    // 0x0224 - 0x022F
   
   TPU_CDTROSR_T                 CDTROSR[TPU_ARRAY_SIZE_01];      // 0x0230 - 0x0233
   
   uint8_t                       reserved9[TPU_RESERVED_000C];    // 0x0234 - 0x023F
   
   TPU_CIER_T                    CIER[TPU_ARRAY_SIZE_01];         // 0x0240 - 0x0243
   
   uint8_t                       reserved10[TPU_RESERVED_000C];   // 0x0244 - 0x024F
   
   TPU_CDTRER_T                  CDTRER[TPU_ARRAY_SIZE_01];       // 0x0250 - 0x0253
   
   uint8_t                       reserved11[TPU_RESERVED_000C];   // 0x0254 - 0x025F

   TPU_WDSR_T                    WDSR[TPU_ARRAY_SIZE_01];         // 0x0260 - 0x0263

   uint8_t                       reserved12[TPU_RESERVED_001C];   // 0x0264 - 0x027F
   
   TPU_CPSSR_T                   CPSSR[TPU_ARRAY_SIZE_01];        // 0x0280 - 0x0283
   
   uint8_t                       reserved13[TPU_RESERVED_000C];   // 0x0284 - 0x028F
   
   TPU_CSSR_T                    CSSR[TPU_ARRAY_SIZE_01];         // 0x0290 - 0x0293
   
   uint8_t                       reserved14[TPU_RESERVED_016C];   // 0x0294 - 0x03FF
   
   TPU_Channel_Map_T             Channel_Map[TPU_ARRAY_SIZE_01];  // 0x0400 - 0x05FF

   uint8_t                       reserved15[TPU_RESERVED_7800];   // 0x0800 - 0x7FFF

   uint32_t                      SDM[TPU_SDM_SIZE_IN_U32];        // 0x8000 - 0x8BFF       // 3K BYTES

   uint8_t                       reserved16[TPU_RESERVED_3400];   // 0x8C00 - 0xBFFF

   uint32_t                      SDM_PSE[TPU_SDM_PSE_SIZE_IN_U32];// 0xC000 - 0xCBFF       // 3K BYTES
   
   uint8_t                       reserved17[TPU_RESERVED_3400];   // 0xCC00 - 0xFFFF 

   uint32_t                      SCM[TPU_SCM_SIZE_IN_U32];        // 0x10000 -0x137FF       //14K BYTES

   uint8_t                       reserved_SCM[0xC800];            // 0x13800-0x1FFFF

}  TPU_T;


#endif // HW_TPU_H
