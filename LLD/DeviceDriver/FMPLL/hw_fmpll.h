#ifndef HW_FMPLL_H
#define HW_FMPLL_H

//=============================================================================
// Only Include reuse.h for the hardware definition files
//=============================================================================
#include "reuse.h"

//=============================================================================
// ID - FMPLL Synthesizer Control Register (FMPLL_SYNCR))
// Base Offset : 0000 0004H
//
// Reset Value : 0x****0000H  ( Refer Manual for more details. )
//
//The symbol * means that the reset value is defined at SoC integration or by an external pin.
//
// Field        Bits      Type      Description
// ==========  =========  ====      =============================================
// 0              0         r       Reserved, should be cleared.
//
// PREDIV        1–3       rw      Pre-divider. This 3-bit field controls the value
//                                 of the divider on the input clock. The output of
//                                 the pre-divider circuit generates the reference
//                                 clock to the FMPLL analog loop. The value 111 causes
//                                 the input clock to be inhibited.
//                                 000 Divide by 1
//                                 001 Divide by 2
//                                 010 Divide by 3
//                                 011 Divide by 4
//                                 100 Divide by 5
//                                 101 Divide by 6
//                                 110 Divide by 7
//                                 111 Clock inhibit
//
// MFD           4–8       rw      Multiplication factor divider. This 5-bit field
//                                 controls the value of the divider in the FMPLL
//                                 feedback loop.The value specified by the MFD bits
//                                 establishes the multiplication factor applied to
//                                 the reference frequency.he system clocks have failed
//                                 000xx Invalid
//                                 00100 Divide by 8
//                                 00101 Divide by 9
//                                 00110 Divide by 10
//                                 10011 Divide by 23
//                                 10100 Divide by 24
//                                 10101 Invalid
//                                 1011x Invalid
//                                 11xxx Invalid
//
// 0              9         r      Reserved, should be cleared.
//
// RFD          10–12      rw      Reduced frequency divider. This 3-bit field controls
//                                 a divider at the output of the FMPLL. The value
//                                 specified by the RFD bits establishes the division
//                                 factor applied to the FMPLL frequency.
//                                 000 Divide by 1
//                                 001 Divide by 2
//                                 010 Divide by 4
//                                 011 Invalid
//                                 1xx Invalid
//
// LOCEN         13        rw      Loss-of-clock enable. The LOCEN bit determines if the
//                                 loss-of-clock function is operational. This bit only
//                                 has effect in normal mode. In bypass mode, the loss-of-
//                                 clock function is always enabled, regardless ofthe state
//                                 of the LOCEN bit. Furthermore, the LOCEN bit has no
//                                 effect on the loss-of-lock detection circuitry.
//                                 0 Loss of clock disabled.
//                                 1 Loss of clock enabled.
//
// LOLRE         14        rw      Loss-of-lock reset enable. The LOLRE bit determines
//                                 whether system reset is asserted or not upon a
//                                 loss-of-lock indication. When operating in normal
//                                 mode, the FMPLL must be locked before setting the
//                                 LOLRE bit, otherwise reset is immediately asserted.
//                                 Note that once reset is asserted, the operating
//                                 mode is switched to bypass mode, and once in bypass,
//                                 a loss-of-lock condition does not generate reset,
//                                 regardless of the value of the LOLRE bit.
//                                 0 Ignore loss-of-lock. Reset not asserted.
//                                 1 Assert reset on loss-of-lock when operating in
//                                 normal mode.
//
// LOCRE         15        rw      Loss-of-clock reset enable. The LOCRE bit determines
//                                 whether system reset is asserted or not upon a
//                                 loss-of-clock condition when LOCEN=1. LOCRE has no
//                                 effect when LOCEN=0. If the LOCF bit in the SYNSR
//                                 indicates a loss-of-clock condition, setting the
//                                 LOCRE bit causes immediate reset. In bypass mode
//                                 with crystal reference, reset will occur if the
//                                 reference clock fails, even if LOCRE=0 or even if
//                                 LOCEN=0. The LOCRE bit has no effect in bypass mode
//                                 with external reference. In this mode, the
//                                 reference clock is not monitored at all.
//                                 0 Ignore loss-of-clock. Reset not asserted.
//                                 1 Assert reset on loss-of-clock.
//
// 0             16        r       Reserved, should be cleared.
//
// LOLIRQ        17        rw      Loss-of-lock interrupt request. The LOLIRQ bit
//                                 enables a loss-of-lock interrupt request when the LOLF
//                                 flag is set. If either LOLF or LOLIRQ is negated, the
//                                 interrupt request is negated. When operating in
//                                 normal mode, the FMPLL must be locked before setting
//                                 the LOLIRQ bit, otherwise an interrupt is immediately
//                                 asserted. The interrupt request only happens in normal
//                                 mode, therefore the LOLIRQ bit has no effect in bypass
//                                 mode.
//                                 0 Ignore loss-of-lock. Interrupt not requested.
//                                 1 Enable interrupt request upon loss-of-lock.
//
// LOCIRQ        18        rw     Loss-of-clock interrupt request. The LOCIRQ bit enables
//                                a loss-of-clock interrupt request when the LOCF flag is
//                                set. If either LOCF or LOCIRQ is negated, the interrupt
//                                request is negated. If loss-of-clock is detected while
//                                in bypass mode, a system reset is generated. Therefore,
//                                LOCIRQ has no effect in bypass mode.
//                                0 Ignore loss-of-clock. Interrupt not requested.
//                                1 Enable interrupt request upon loss-of-clock.
//
// 0           19–31       r      Reserved, should be cleared.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef struct FMPLL_SYNCR_F_Tag
{
   bitfield32_t             :  BIT_1;  // Bit       0 reserved
   bitfield32_t  PREDIV     :  BIT_3;  // Bits      1-3
   bitfield32_t  MFD        :  BIT_5;  // Bits      4-8
   bitfield32_t             :  BIT_1;  // Bits      9 reserved
   bitfield32_t  RFD        :  BIT_3;  // Bits      10-12
   bitfield32_t  LOCEN      :  BIT_1;  // Bit       13
   bitfield32_t  LOLRE      :  BIT_1;  // Bit       14
   bitfield32_t  LOCRE      :  BIT_1;  // Bit       15
   bitfield32_t             :  BIT_1;  // Bit       16 reserved
   bitfield32_t  LOLIRQ     :  BIT_1;  // Bit       17
   bitfield32_t  LOCIRQ     :  BIT_1;  // Bit       18
   bitfield32_t             :  BIT_13; // Bit       19-31 reserved

}  FMPLL_SYNCR_F_T;

typedef union FMPLL_SYNCR_Tag
{
   FMPLL_SYNCR_F_T           F;
   uint32_t                U32;

}  FMPLL_SYNCR_T;


//=============================================================================
// ID - FMPLL Synthesizer Status Register (FMPLL_SYNSR))
// Base Offset : 0000 0004H
//
// Reset Value : 0000 00XXH  ( Refer Manual for more details. )
//
// Field        Bits     Type Description
// ==========  ========= ==== =================================================
// 0            0-21       r  Reserved, should be cleared.
//
// LOLF          22       rw  Loss of lock flag. This bit provides the interrupt
//                            request flag. To clear the flag, the user must
//                            write a 1 to the bit. Writing 0 has no effect.
//                            This flag will not be set, and an  interrupt will
//                            not be requested, if the loss of lock condition was
//                            caused by a system reset,write to the SYNCR which
//                            modifies the MFD bits,or enabling frequency modulation.
//                            If the flag isset due to a system failure,
//                            writing the MFD bits or enabling FM will not
//                            clear the flag.Asserting reset will clear the flag.
//                            This flag bit is sticky in the sense that if lock is
//                            reacquired, the bit will remain set until
//                            either a write 1 or reset is asserted.
//                            0 Interrupt service not requested
//                            1 Interrupt  service requested
//
// LOC           23       rw  Loss-of-clock. This bit is an indication of whether
//                            a loss-of-clock condition is present. If LOC=0, the
//                            system clocks are operating normally. If LOC=1, the
//                            system clocks have failed due to a reference or VCO
//                            failure. If a loss-of-clock condition occurs which
//                            sets this bit and the clocks later return to normal,
//                            this bit will be cleared. A loss-of-clock condition
//                            can only be detected if LOCEN=1. Furthermore, the LOC
//                            bit is notasserted when the FMPLL is in bypass mode
//                           (because, in bypass, the VCO clock is not monitored and
//                            a loss-of-clock on the reference clock causes reset).
//                            0 No loss-of-clock detected. Clocks are operating normally.
//                            1 Loss-of-clock detected. Clocks are not operating normally.
//
// MODE           24      rw  Mode of operation. This bit indicates whether the FMPLL
//                            is working in bypass mode or normal mode. The reset
//                            value indicates bypass mode. In legacy mode (bit EMODE
//                            negated in the ESYNCR1 register), the MODE bit will
//                            change to normal mode at the first time the SYNCR register
//                            is written. In enhanced mode (bit EMODE asserted in the
//                            ESYNCR1 register), the MODE bit reflects the value of
//                            the CLKCFG[0] bit of the ESYNCR1 register.
//                             0 bypass mode.
//                             1 clock mode.
//
// PLLSEL         25      rw  Mode select. In previous MCUs of the MPC5500 family, this
//                            bit was used to differentiate between dual controller mode
//                            and normal mode (negated in bypass or dual controller mode,
//                            asserted in normal mode). Dual controller mode is not supp
//                            orted,therefore in legacy mode this bit resets to zero
//                           (bypass), but
//                            changes to one (normal mode) at the first time the SYNCR
//                            register is written. In enhanced mode, the MODE bit reflects
//                            the value of the CLKCFG[1] bit of the ESYNCR1 register.
//                            0 Legacy mode: bypass or dual controller; enhanced mode:
//                            PLL off.
//                            1 Legacy mode: normal; enhanced mode: PLL on.
//
// PLLREF         26     rw  FMPLL reference source. This bit indicates whether the FMPLL
//                           reference is from a crystal oscillator or from an external
//                           clock generator. The reset value is determined by the state
//                           of the PLLREF pin. In legacy mode, the reset value captured
//                           from the PLLREF pin cannot be changed anymore after reset.
//                           In enhanced mode, the PLLREF bit reflects the value of the
//                           CLKCFG[2] bit of the ESYNCR1 register.
//                           0 External clock reference chosen.
//                           1 Crystal clock reference chosen.
//
// LOCKS           27    rw  Sticky PLL lock status bit. The LOCKS bit is a
//                           sticky indication of PLL lock status. LOCKS is
//                           set by the lock detect circuitry when the PLL
//                           acquires lock after:
//                              1) a system reset, or
//                              2) A write to the SYNCR register in legacy mode which
//                              changes the PREDIV or MFD fields
//                              3) A write to the ESYNCR1 register in enhanced mode which
//                              changes the EMODE, EPREDIV, EMFD or CLKCFG[1:2]
//                           Whenever the FMPLL loses lock, LOCKS is cleared. LOCKS
//                           remains cleared even after the FMPLL re-locks, until one of
//                           the three previously stated conditions occurs. Coming in
//                           bypass mode from system reset, LOCKS is asserted as soon as
//                           the FMPLL has locked, even if normal mode was not entered yet
//                         . If the FMPLL is locked, going from normal to bypass mode does
//                           not clear the LOCKS bit.
//                           0 FMPLL has lost lock since last system reset or last write
//                           to PLL registers which affect the lock status.
//                           1 FMPLL has not lost lock.
//
// LOCK            28    rw  FMPLL lock status bit. Indicates whether the FMPLL has acquired
//                           lock. FMPLL lock occurs when the synthesized frequency matches
//                           to within approximately 4% of the programmed frequency. The FMPLL
//                           loses lock when a frequency deviation of greater than approximately
//                           16% occurs. The flag is also immediately negated when the PREDIV
//                           or MFD fields of the SYNCR are changed in legacy mode, or when
//                           EMODE, EPREDIV, EMFD or CLKCFG[1:2] are changed in enhanced mode,
//                           and then asserted again when the PLL regains lock. If operating
//                           in bypass mode, the LOCK bit is still asserted or negated when
//                           the FMPLL acquires or loses lock.
//                           0 FMPLL is unlocked.
//                           1 FMPLL is locked.
//
// LOCF           29     rw  Loss-of-clock flag. This bit provides the interrupt request flag
//                           for the loss-of-clock. To clear the flag, software must write a
//                           1 to the bit. Writing 0 has no effect. This flag bit is sticky in
//                           the sense that if clocks return to normal, the bit will remain set
//                           until cleared by either writing 1 or asserting reset. The LOCF flag
//                           is not asserted while the FMPLL is in bypass mode.
//                           0 No loss of clock detected. Interrupt service not requested.
//                           1 Loss of clock detected. Interrupt service requested.
//
// 0             30-31   r   Reserved, should be cleared.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef struct FMPLL_SYNSR_F_Tag
{
   bitfield32_t             :  BIT_22; // Bits [0:21] are reserved
   bitfield32_t  LOLF       :  BIT_1;  // Bit       22
   bitfield32_t  LOC        :  BIT_1;  // Bit       23
   bitfield32_t  MODE       :  BIT_1;  // Bit       24
   bitfield32_t  PLLSEL     :  BIT_1;  // Bit       25
   bitfield32_t  PLLREF     :  BIT_1;  // Bit       26
   bitfield32_t  LOCKS      :  BIT_1;  // Bit       27
   bitfield32_t  LOCK       :  BIT_1;  // Bit       28
   bitfield32_t  LOCF       :  BIT_1;  // Bit       29
   bitfield32_t             :  BIT_2;  // Bits      30-31 reserved
}  FMPLL_SYNSR_F_T;

typedef union FMPLL_SYNSR_Tag
{
   FMPLL_SYNSR_F_T           F;
   uint32_t                U32;

}  FMPLL_SYNSR_T;

//=============================================================================
// ID - FMPLL Enhanced Synthesizer Control Register1 (FMPLL_ESYNCR1)
//
// Base Offset : 0000 0008 H
//
// Reset Value : 0x*00*00** H
//
// Field        Bits     Type  Description
// ======   ============ ====  =================================================
// EMODE         0       rw    Enhanced mode enable. This bit determines whether
//                             the FMPLL will be controlled by SYNCR or ESYNCR1/
//                             ESYNCR2. At SoC integration, a signal tie will dictate
//                             the default state that the PLL operates. If the SoC
//                             integration ties the FMPLL to run in enhanced mode,
//                             the EMODE bit will reflect this by reading a logic 1.
//                             Additionally, software writes to this bit to revert to
//                             legacy mode will not be allowed. If the signal is tied
//                             to select legacy mode as the default state, the EMODE
//                             bit will reflect this by reading a logic 0. In this case
//                             , software writes to this bit to enable enhanced mode
//                             is allowed, but it is a write once operation. After
//                             written to one, further write attempts to this bit
//                             will have no effect.
//                             0 Legacy mode. FMPLL controlled by SYNCR.
//                             1 Enhanced mode. FMPLL controlled by ESYNCR1/ESYNCR2.
//
// CLKCFG      1-3   rw       Clock configuration. This 3-bit field is used to change
//                            the operating mode of the FMPLL. Bit 2 is not writable
//                            to zero while bit 1 is 1. The reset state of bit 3 is d
//                            etermined by the state of the PLLREF pin.
//                            000 Bypass mode with external reference and PLL off.
//                            001 Bypass mode with crystal reference and PLL off.
//                            010 Bypass mode with external reference and PLL running.
//                            011 Bypass mode with crystal reference and PLL running.
//                            100 Reserved.
//                            101 Reserved.
//                            110 Normal mode with external reference.
//                            111 Normal mode with crystal reference.
//
// 0           4-11   r       Reserved, should be cleared.
//
// EPREDIV     12-15   rw     Enhanced pre-divider. This 4-bit field controls the value
//                            of the divider on the input clock. The output of the pre-divider
//                            circuit generates the reference clock to the PLL analog loop.
//                            The PREDIV value 1111 causes the input clock to be inhibited.
//                            0000 Divide by 1
//                            0001 Divide by 2
//                            0010 Divide by 3
//                            0011 Divide by 4
//                            0100 Divide by 5
//                            0101 Divide by 6
//                            0110 Divide by 7
//                            0111 Divide by 8
//                            1000 Divide by 9
//                            1001 Divide by 10
//                            1010 Divide by 11
//                            1011 Divide by 12
//                            1100 Divide by 13
//                            1101 Divide by 14
//                            1110 Divide by 15
//                            1111 Clock inhibit
//-----------------------------------------------------------------------------
// 0          16-24     r     Reserved.
//-----------------------------------------------------------------------------
// EMFD       25-31     rw    Enhanced multiplication factor divider. This 7-bit field
//                            controls the value of the divider in the FMPLL feedback
//                            loop. The value specified by the EMFD bits establishes
//                            the multiplication factor applied to the reference frequency
//                          . The valid range of multiplication factors is 32 (010_0000)
//                            to 96 (110_0000). Values outside this range are invalid and
//                            will cause the FMPLL to produce unpredictable clock output.
//=============================================================================

typedef struct FMPLL_ESYNCR1_F_Tag
{
   bitfield32_t  EMODE     :  BIT_1;   // Bits     0
   bitfield32_t  CLKCFG    :  BIT_3;   // Bits     1-3
   bitfield32_t            :  BIT_8;   // Bits     4-11 is reserved
   bitfield32_t  EPREDIV   :  BIT_4;   // Bit      4-15
   bitfield32_t            :  BIT_9;   // Bits     16-24 is reserved
   bitfield32_t  EMFD      :  BIT_7;   // Bits     25-31

}  FMPLL_ESYNCR1_F_T;

typedef union FMPLL_ESYNCR1_Tag
{
   FMPLL_ESYNCR1_F_T        F;
   uint32_t             U32;

}  FMPLL_ESYNCR1_T;

//=============================================================================
// ID - FMPLL Enhanced Synthesizer Control Register 2 (FMPLL_ESYNCR2)
//
// Base Offset : 0000 000C H
//
// Reset Value : 0x0000000* H
//
// Field        Bits     Type Description
// ======   ============ ==== =================================================
// 0          0-7         r    RESERVED
//-----------------------------------------------------------------------------
// LOCEN       8         rw   Loss-of-clock enable. The LOCEN bit determines if the
//                            loss-of-clock function is operational. This bit only
//                            has effect in normal mode. In bypass mode, the loss-of
//                            -clock function is always enabled, regardless of
//                            the state of the LOCEN bit. Furthermore, the LOCEN
//                            bit has no effect on the loss-of-lock detection
//                            circuitry.
//                            0 Loss of clock disabled.
//                            1 Loss of clock enabled.
//-----------------------------------------------------------------------------
// LOLRE       9        rw   Loss-of-lock reset enable. The LOLRE bit determines
//                           whether system reset is asserted or not upon a
//                           loss-of-lock indication. When operating in normal mode,
//                           the FMPLL must be locked before setting the
//                           LOLRE bit, otherwise reset is immediately asserted. Note
//                           that once reset is asserted, the operating mode
//                           is switched to bypass mode, and once in bypass, a
//                           loss-of-lock condition does not generate reset,
//                           regardless of the value of the LOLRE bit.
//                           0 Ignore loss-of-lock. Reset not asserted.
//                           1 Assert reset on loss-of-lock when operating in normal mode.
//-----------------------------------------------------------------------------
// LOCRE        10       rw   Loss-of-clock reset enable. The LOCRE bit determines
//                            whether system reset is asserted or not upon a
//                            loss-of-clock condition when LOCEN=1. LOCRE has no effect
//                            when LOCEN=0. If the LOCF bit in the
//                            SYNSR indicates a loss-of-clock condition, setting the
//                            LOCRE bit causes immediate reset. In bypass
//                            mode with crystal reference, reset will occur if the
//                            reference clock fails, even if LOCRE=0 or even if
//                            LOCEN=0. The LOCRE bit has no effect in bypass mode with
//                            external reference. In this mode, the
//                            reference clock is not monitored at all.
//                            0 Ignore loss-of-clock. Reset not asserted.
//                            1 Assert reset on loss-of-clock.
//-----------------------------------------------------------------------------
// LOLIRQ       11       rw   Loss-of-lock interrupt request. The LOLIRQ bit enables a
//                            loss-of-lock interrupt request when the LOLF
//                            flag is set. If either LOLF or LOLIRQ is negated, the
//                            interrupt request is negated. When operating in
//                            normal mode, the FMPLL must be locked before setting the
//                            LOLIRQ bit, otherwise an interrupt is
//                            immediately asserted. The interrupt request only happens
//                            in normal mode, therefore the LOLIRQ bit has
//                            no effect in bypass mode.
//                            0 Ignore loss-of-lock. Interrupt not requested.
//                            1 Enable interrupt request upon loss-of-lock.
//-----------------------------------------------------------------------------
// LOCIRQ      12         rw   Loss-of-clock interrupt request. The LOCIRQ bit enables
//                             a loss-of-clock interrupt request when the LOCF
//                             flag is set. If either LOCF or LOCIRQ is negated, the
//                             interrupt request is negated. If loss-of-clock is
//                             detected while in bypass mode, a system reset is generated.
//                             Therefore, LOCIRQ has no effect in bypass mode.
//                             0 Ignore loss-of-clock. Interrupt not requested.
//                             1 Enable interrupt request upon loss-of-clock.
//-----------------------------------------------------------------------------
// 0           13-29      r    RESERVED
//-----------------------------------------------------------------------------
// ERFD        30-31     rw   Enhanced reduced frequency divider. This 2-bit field controls
//                            a divider at the output of the FMPLL. The
//                            value specified by the ERFD bits establishes the division
//                            factor applied to the FMPLL frequency.
//                            00 Divide by 2
//                            01 Divide by 4
//                            10 Divide by 8
//                            11 Divide by 16
//=============================================================================

typedef struct FMPLL_ESYNCR2_F_Tag
{
   bitfield32_t            :  BIT_8;   // Bits  0-7  is reserved
   bitfield32_t  LOCEN     :  BIT_1;   // Bit   8
   bitfield32_t  LOLRE     :  BIT_1;   // Bit   9
   bitfield32_t  LOCRE     :  BIT_1;   // Bit   10
   bitfield32_t  LOLIRQ    :  BIT_1;   // Bit   11
   bitfield32_t  LOCIRQ    :  BIT_1;   // Bit   12
   bitfield32_t            :  BIT_17;  // Bit   13-29 is reserved
   bitfield32_t  ERFD      :  BIT_2;   // Bits  30-31

}  FMPLL_ESYNCR2_F_T;

typedef union FMPLL_ESYNCR2_Tag
{
   FMPLL_ESYNCR2_F_T        F;
   uint32_t             U32;

}  FMPLL_ESYNCR2_T;



//=============================================================================
// ID - FMPLL Synthesizer FM Modulation Register (FMPLL_SYNFMMR)
//
// Base Offset : 0x0018 H
//
// Reset Value : 0x0000000* H
//
// Field        Bits     Type  Description
// ======   ============ ====  =================================================
// BSY          0         r    Busy. This bit is asserted soon after a write access
//                             to the SYNFMMR register, and remains asserted
//                             while the FMPLL processes the new FM modulation
//                             programming. The CPU must wait until this bit is
//                             negated before attempting another write access to
//                             this register. Any write attempt while the BSY flag
//                             is set will have no effect.
//                             0 Write to the SYNFMMR register is allowed.
//                             1 The FMPLL is still busy processing the previous
//                             change on the SYNFMMR register; write access
//                             to the register is not possible.
//-----------------------------------------------------------------------------
// MODEN        1        rw    Modulation enable. This bit enables the frequency modulation.
//                             0 Frequency modulation disabled.
//                             1 Frequency modulation enabled.
//-----------------------------------------------------------------------------
// MODSEL       2        rw    Modulation selection. This bit selects whether
//                             modulation will be centered around the nominal
//                             frequency or spread below the nominal frequency.
//                             0 Modulation centered around nominal frequency.
//                             1 Modulation spread below nominal frequency.
//-----------------------------------------------------------------------------
// MODPERIOD   3-15      rw    Modulation period. This 13-bit field is the binary
//                             equivalent of the modperiod variable derived from the
//                             formula:modperiod = round(fref/4 × fmod)
//                             where represents the frequency of the feedback divider,
//                             and represents the modulation frequency
//-----------------------------------------------------------------------------
// 0           16        r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// INCSTEP    17-31      rw   Increment step. This 14-bit field is the binary equivalent
//                            of the incstep variable derived from the formula:
//                            incstep =round(((2^15 – 1) × MD × EMFD)/100 × 5 × modperiod)
//                            where md represents the peak modulation depth in percentage
//                            (+/-MD for centered modulation,
//                            -2*MD for modulation below nominal frequency), and represents
//                            the nominal value of the feedback loop divider.
//=============================================================================

typedef struct FMPLL_SYNFMMR_F_Tag
{
   bitfield32_t  BSY       :  BIT_1;   // Bit   0
   bitfield32_t  MODEN     :  BIT_1;   // Bit   1
   bitfield32_t  MODSEL    :  BIT_1;   // Bit   2
   bitfield32_t  MODPERIOD :  BIT_13;  // Bit   3-15
   bitfield32_t            :  BIT_1;   // Bit   16
   bitfield32_t  INCSTEP   :  BIT_15;  // Bit   17-31

}  FMPLL_SYNFMMR_F_T;

typedef union FMPLL_SYNFMMR_Tag
{
   FMPLL_SYNFMMR_F_T        F;
   uint32_t             U32;

}  FMPLL_SYNFMMR_T;


//=============================================================================
//  FMPLL Module Register Structure
//=============================================================================
#define FMPLL_RESERVED_0    (8)

typedef volatile struct FMPLL_Tag
{
   FMPLL_SYNCR_T       SYNCR;                        // 0x0000 - 0x0003
   FMPLL_SYNSR_T       SYNSR;                        // 0x0004 - 0x0007
   FMPLL_ESYNCR1_T     ESYNCR1;                      // 0x0008 - 0x000B
   FMPLL_ESYNCR2_T     ESYNCR2;                      // 0x000C - 0x000F
   uint8_t             reserved_0[FMPLL_RESERVED_0]; // 0x0010 - 0x0013
   FMPLL_SYNFMMR_T     SYNFMMR;                      // 0x0018 - 0x001B
}  FMPLL_T;

#endif // HW_FMPLL_H
