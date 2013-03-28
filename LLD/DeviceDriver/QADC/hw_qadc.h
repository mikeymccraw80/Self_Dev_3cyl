#ifndef HW_QADC_H
#define HW_QADC_H


#include "reuse.h"

#define QADC_FIFO_QUANTITY    (6U)      // Number of CFCR Registers
                                       // Number of IDCR Registers
                                       // Number of CFPR Registers
                                       // Number of RFPR Registers
                                       // Number of FISR Registers
                                       // Number of CFTCR Registers
                                       // Number of CFRn Groups of Registers
                                       // Number of RFRn Groups of Registers

#define QADC_CFSSR_QUANTITY   (2U)      // Number of CFSSR Registers
#define QADC_CFR_QUANTITY     (4U)      // Number of CFR Registers
#define QADC_RFR_QUANTITY     (4U)      // Number of RFR Registers

#define QADC_RESERVED_0x0008  (0x0008U)
#define QADC_RESERVED_0x0004  (0x0004U)
#define QADC_RESERVED_0x0014  (0x0014U)
#define QADC_RESERVED_0x002C  (0x002CU)
#define QADC_RESERVED_0x0044  (0x0044U)
#define QADC_RESERVED_0x0030  (0x0030U)
#define QADC_RESERVED_0x0020  (0x0020U)
#define QADC_RESERVED_0x0080  (0x0080U)
#define QADC_RESERVED_0x0380  (0x0380U)
//W1C BIT MASKS
#define QADC_NCF_CLEAR_MASK     (0x85F5FFFFUL)
#define QADC_TORF_CLEAR_MASK    (0x45F5FFFFUL)
#define QADC_PF_CLEAR_MASK      (0x25F5FFFFUL)
#define QADC_EOQF_CLEAR_MASK    (0x15F5FFFFUL)
#define QADC_CFUF_CLEAR_MASK    (0x0DF5FFFFUL)
#define QADC_CFFF_CLEAR_MASK    (0x07F5FFFFUL)
#define QADC_RFOF_CLEAR_MASK    (0x05FDFFFFUL)
#define QADC_RFDF_CLEAR_MASK    (0x05F7FFFFUL)

#define QADC_ARRAY_SIZE_2     (2)
//=============================================================================
// ID - eQADC Module Configuration Register (QADC_MCR)
//
// Base Offset :
//
// Reset Value :
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [0:23]     r   Reserved
//
// ICEA0           24     rw  Immediate Conversion Command Enable ADC0
//                            ICEA0 enables the EQADC to abort on-chip ADC0 
//                            current conversion and to start the immediate
//                            conversion command from CFIFO0 in the requested 
//                            ADC0.
//                            1 = Enable immediate conversion command request.
//                            0 = Disable immediate conversion command request.
//
// ICEA1           25     rw  Immediate Conversion Command Enable ADC1
//                            ICEA1 enables the EQADC to abort on-chip ADC1 
//                            current conversion and to start the immediate
//                            conversion command from CFIFO0 in the requested 
//                            ADC1.
//                            1 = Enable immediate conversion command request.
//                            0 = Disable immediate conversion command request.
//
// 0                5      r  Reserved.
//
// ESSIE       [27:28]    rw  EQADC Synchronous Serial Interface Enable. The
//                            ESSIE field defines the EQADC synchronous
//                            serial interface operation according to Table
//                            given below.
//
//                            ESSIE[0:1]                     Meaning
//
//                             0b00                  EQADC SSI is disabled
//
//                             0b01                        Reserved
//
//                             0b10            EQADC SSI is enabled, FCK is
//                                             free running, and serial
//                                             transmissions are disabled.
//
//                             0b11            EQADC SSI is enabled, FCK is
//                                             free running, and serial
//                                             transmissions are enabled.
//
// 0                 2     r  Reserved.
//
// DBG           [31]     rw  DBG[0:1] - Debug enable. The DBG field defines
//                            the EQADC response to a debug mode entry
//                            request as in the Table given below.
//
//                             DBG0:1                    Meaning
//
//                             0b00               Do not enter debug mode.
//
//                             0b01               Reserved
//                             0b10               Enter debug mode. If the
//                                                EQADC SSI is enabled, FCK
//                                                stops while the QADC is
//                                                in debug mode.
//                             0b11               Enter debug mode. If the
//                                                EQADC SSI is enabled, FCK
//                                                is free running while the
//                                                EQADC is in debug mode.
//
//=============================================================================
typedef struct QADC_MCR_F_Tag
{
   bitfield32_t          :  BIT_24; // Bits [31: 8]  are reserved
   bitfield32_t  ICEA0   :  BIT_1;  // Bit       7
   bitfield32_t  ICEA1   :  BIT_1;  // Bit       6
   bitfield32_t          :  BIT_1;  // Bit       5 is reserved
   bitfield32_t  ESSIE   :  BIT_2;  // Bits [ 4: 3]
   bitfield32_t          :  BIT_1;  // Bit       2 is reserved
   bitfield32_t  DBG     :  BIT_2;  // Bits [ 0: 1]

}  QADC_MCR_F_T;

typedef union QADC_MCR_Tag
{
   QADC_MCR_F_T        F;
   uint32_t             U32;

}  QADC_MCR_T;


//=============================================================================
// ID - eQADC Test Register (QADC_TST)
// Base Offset : Register address: QADC_BASE+0x004
//
// Reset Value : 
//
// Field        Bits     Type Description
// ==========  ======== ====  ===============================================

typedef uint32_t QADC_TST_T;


//=============================================================================
// ID - eQADC Null Message Send Format Register (QADC_NMSFR)
// Base Offset : QADC_BASE+0x008
//
// Reset Value : 
//
// Field        Bits     Type Description
// ==========  ======== ====  ===============================================
// 0            [0:5]      r  Reserved.
//
// NMF          [6:31]    rw  Null Message Format. The NMF field contains
//                            the programmable null message send value for
//                            the EQADC. The value written to this register
//                            will be sent as a null message when serial
//                            transmissions from the EQADC_A SSI are enabled
//                            (ESSIE field configured to 0b11 in
//                            QADC Module Configuration Register(EQADC_MCR))
//                            and either
//
//                            there are no triggered CFIFOs with commands
//                            bound for external CBuffers, or;
//                            there are triggered CFIFOs with commands
//                            bound for external CBuffers but the
//                            external CBuffers are full.
//
//                            Null Message Receive Format for External Device
//                            Operation
//
//=============================================================================
typedef struct QADC_NMSFR_F_Tag
{
   bitfield32_t          :  BIT_6;  // Bits [0:5]  are reserved
   bitfield32_t  NMF     :  BIT_26; // Bits [6:31]

}  QADC_NMSFR_F_T;

typedef union QADC_NMSFR_Tag
{
   QADC_NMSFR_F_T       F;
   uint32_t             U32;

}  QADC_NMSFR_T;

//=============================================================================
// ID - eQADC External Trigger Digital Filter Register (QADC_TDFR)
// Base Offset : 0000 000CH
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ==========   ======== ==== ===============================================
// 0            [31:4]     r  Reserved.
//
// DFL           [3:0]    rw  Digital Filter Length. The DFL field specifies
//                            the minimum number of system clocks that must
//                            be counted by the digital filter counter to
//                            recognize a logic state change. The count
//                            specifies the sample period of the digital
//                            filter which is calculated according to the
//                            following equation:
//
//                            FilterPeriod = (systemClockPeriod * 2^DFL) +
//                                           1 (systemClockPeriod )
//                            Minimum clock counts for which an ETRIG signal
//                            needs to be stable to be passed through the
//                            filter are shown in Table .
//                            Note: The DFL field must only be written when
//                            the MODEx of all CFIFOs are configured to
//                            disabled.
//
//                             Minimum Required Time to Valid ETRIG
//
//                             DFL[0:3]  Min Clock Count  Min Time (ns)
//                                                       (sys clk =80MHz)
//
//                             0b0000         2             25.0
//                             0b0001         3             37.5
//                             0b0010         5             62.5
//                             0b0011         9            112.5
//                             0b0100        17            212.5
//                             0b0101        33            412.5
//                             0b0110        65            812.5
//                             0b0111       129           1612.5
//                             0b1000       257           3212.5
//                             0b1001       513           6412.5
//                             0b1010      1025          12812.5
//                             0b1011      2049          25612.5
//                             0b1100      4097          51212.5
//                             0b1101      8193         102412.5
//                             0b1110     16385         204812.5
//                             0b1111     32769         409612.5
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef struct QADC_ETDFR_F_Tag
{
   bitfield32_t          :  BIT_28;  // Bits [0:27]  are reserved
   bitfield32_t  DFL     :  BIT_4;   // Bits [28:31]

}  QADC_ETDFR_F_T;

typedef union QADC_ETDFR_Tag
{
   QADC_ETDFR_F_T       F;
   uint32_t             U32;

}  QADC_ETDFR_T;

//=============================================================================
// ID - eQADC CFIFO Push Registers (QADC_CFPR)
// Base Offset : 
// EQADC_BASE+0x010 (EQADC_CFPR0); EQADC_BASE+0x014 (EQADC_CFPR1);
// EQADC_BASE+0x018 (EQADC_CFPR2);EQADC_BASE+0x01C (EQADC_CFPR3);
// EQADC_BASE+0x020 (EQADC_CFPR4);EQADC_BASE+0x024 (EQADC_CFPR5);
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ============ ======== ==== ================================================
// CF_PUSHx     [31:0]    rw  CFIFO Push Data x. When CFIFOx is not full,
//                            writing to the whole word or any bytes of
//                            EQADC_CFPRx will push the 32-bit CF_PUSHx value
//                            into CFIFOx. Writing to the CF_PUSHx field also
//                            increments the corresponding CFCTRx value by
//                            one in EQADC FIFO and Interrupt Status Registers
//                            (EQADC_FISR). When the CFIFOx is full, the
//                            EQADC ignores any write to the CF_PUSHx. Reading
//                            the EQADC_CFPRx always returns zero.
//
//                            Note: Only whole words must be written to
//                            EQADC_CFPR. Writing half-words or bytes to
//                            EQADC_CFPR will still push the whole 32-bit
//                            CF_PUSH field into the corresponding CFIFO,
//                            but undefined data will fill the areas of
//                            CF_PUSH that were not specifically designated as
//                            target locations for the write.
//
//=============================================================================

//=============================================================================
// ID - eQADC Result FIFO Pop Registers (QADC_RFPR)
// Base Offset : 0000 0030H - 0000 0044H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ===========  ======== ==== ===============================================
// 0            [0:15]     r  Reserved.
//
// RF_POPx      [16:31]    r  Result FIFO Pop Data x. When RFIFOx is not
//                            empty, the RF_POPx contains the next unread
//                            entry value of RFIFOx. Reading the whole word,
//                            a half-word, or any bytes of EQADC_RFPRx will
//                            pop one entry from RFIFOx,and the corresponding
//                            RFCTRx value will be decremented by one in
//                            EQADC FIFO and Interrupt Status Registers
//                            (EQADC_FISR). When the RFIFOx is empty, any
//                            read on EQADC_RFPRx returns undefined data
//                            value and does not decrement the RFCTRx value.
//                            Writing to EQADC_RFPRx has no effect.
//
//=============================================================================
typedef struct QADC_RFPR_F_Tag
{
   bitfield32_t          :  BIT_16;  // Bits [31:16]  are reserved
   bitfield32_t  RF_POP  :  BIT_16;  // Bits [15: 0]

}  QADC_RFPR_F_T;

typedef union EQADC_RFPR_Tag
{
   QADC_RFPR_F_T        F;
   uint16_t             U16[QADC_ARRAY_SIZE_2];
   uint32_t             U32;

}  QADC_RFPR_T;

//=============================================================================
// ID - eQADC Command FIFO Control Registers (QADC_CFCR0)(0:5)
// Base Offset : 0000 0050H - 0000 0058H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type   Description
// ==========  ========= ====   ===============================================
// 0            [0:2]      r    Reserved.
//
//CFEEE0          3       rw    CFIFO0 Entry Number Extension Enable
//                              The CFEEE0 bit is used to enable the 
//                              extension of the CFIFO0 entries. When in 
//                              extended mode, the CFIFO0 total entries is
//                              the sum of normal entries plus the defined 
//                              value for extension
//                              1 = Enable the extension of CFIFO0 entries.
//                              0 = CFIFO0 has a normal value of entries.
//
//STRME0          4       rw    CFIFO0 Streaming Mode Operation Enable
//                              The STRME0 bit is used to enable the streaming
//                              mode of operation of CFIFO0. In this case, it 
//                              is possible to repeat some sequence of commands
//                              of this FIFO
//                              1 = Enable the streaming mode of CFIFO0.
//                              0 = Streaming mode of CFIFO0 is disabled.
//
// SSE            5       w     CFIFO Single-Scan Enable Bit x. The SSEx bit
//                              is used to set the SSSx bit in EQADC FIFO and
//                              Interrupt Status Registers (EQADC_FISR).
//                              Writing a 1 to SSEx will set the SSSx in
//                              EQADC FIFO and Interrupt Status Registers
//                              (EQADC_FISR), if the CFIFO is in single-scan
//                               mode. When SSSx is already asserted,writing a 1
//                              to SSEx also has no effect. If the CFIFO is in
//                              continuous-scan mode or is disabled, writing a
//                              1 to SSEx will not set SSSx.Writing a 0 to SSEx
//                              has no effect. SSEx always is read as 0.
//                                    0 Set the SSSx bit.
//                                    1 No effect.
//
// CFINV          6       rw    CFIFO Invalidate Bit x. The CFINVx bit causes
//                              the EQADC to invalidate all entries of CFIFOx.
//                              Writing a 1 to CFINVx will reset the value of
//                              CFCTRx in EQADC FIFO and Interrupt Status
//                              Registers (EQADC_FISR).Writing a 1 to CFINVx
//                              also resets the Push Next Data Pointer,Transfer
//                              Next Data Pointer to the first entry of CFIFOx
//                              CFINVx always is read as 0. Writing a 0 has no
//                               effect.
//                              0 Invalidate all of the entries in the
//                               corresponding CFIFO.
//                              1 No effect.
//                              Note: Writing CFINVx only invalidates commands
//                              stored in CFIFOx; previously transferred
//                              commands that are waiting for execution, that
//                              is commands stored in the CBuffers, will still
//                              be executed, and results generated by them will
//                              be stored in the appropriate RFIFO.
//                              Note: CFINVx must not be written unless the
//                              MODEx is configured to disabled,and CFIFO
//                              status is IDLE.
//
// 0                7      r   Reserved.
//
// MODEx        [8:11]    rw   CFIFO Operation Mode x. The MODEx field selects
//                             the CFIFO operation mode for CFIFOx.
//                             Note: If MODEx is not disabled, it must not be
//                             changed to any other mode besides disabled.
//                             If MODEx is disabled and the CFIFO status is
//                             IDLE, MODEx can be changed to any other mode.
//
//                                     CFIFO Operation Mode Table
//
//                            MODEx[0:3]           CFIFO Operation Mode
//
//                             0b0000      Disabled
//                             0b0001      Software Trigger, Single Scan
//                             0b0010      Low Level Gated External Trigger,
//                                         Single Scan
//                             0b0011      High Level Gated External Trigger,
//                                         Single Scan
//                             0b0100      Falling Edge External Trigger,
//                                         Single Scan
//                             0b0101      Rising Edge External Trigger,
//                                         Single Scan
//                             0b0110      Falling or Rising Edge External
//                                         Trigger, Single Scan
//                             0b0111 to   Reserved
//                             0b1000
//                             0b1001      Software Trigger, Continuous Scan
//                             0b1010      Low Level Gated External Trigger,
//                                         Continuous Scan
//                             0b1011      High Level Gated External Trigger,
//                                         Continuous Scan
//                             0b1100      Falling Edge External Trigger,
//                                         Continuous Scan
//                             0b1101      Rising Edge External Trigger,
//                                         Continuous Scan
//                             0b1110      Falling or Rising Edge External
//                                         Trigger, Continuous Scan
//                             0b1111      Reserved
//
//
// AMODE0      [ 12:15]     r  Reserved.
//
//=============================================================================
//Note:CFEEE0,STRME0,AMODE0 These bit fields are applicable for only QADC_CFCR0
typedef struct QADC_CFCR_F_Tag
{
   bitfield16_t           :  BIT_3; // Bits [15:13] are reserved
   bitfield16_t  CFEEE0   :  BIT_1; // Bits     12
   bitfield16_t  STRME0   :  BIT_1; // Bit      11
   bitfield16_t  SSE      :  BIT_1; // Bit      10
   bitfield16_t  CFINV    :  BIT_1; // Bit       9
   bitfield16_t           :  BIT_1; // Bit       8   is reserved
   bitfield16_t  MODE     :  BIT_4; // Bits [ 7: 4]
   bitfield16_t  AMODE0   :  BIT_4; // Bits [ 3: 0] 

}  QADC_CFCR_F_T;

typedef union QADC_CFCR_Tag
{
   QADC_CFCR_F_T        F;
   uint16_t             U16;

}  QADC_CFCR_T;

//=============================================================================
// ID - eQADC Interrupt and DMA Control Registers (QADC_IDCR)
// Base Offset : 0000 0060H - 0000 0068H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// NCIE             0     rw  Non-Coherency Interrupt Enable x. NCIEx enables
//                            the EQADC to generate an interrupt request when
//                            the corresponding NCFx in EQADC FIFO and
//                            Interrupt Status Registers (EQADC_FISR), is
//                            asserted.
//                               0 Disable non-coherency interrupt request.
//                               1 Enable non-coherency interrupt request.
//
// TORIE            1     rw  Trigger Overrun Interrupt Enable x. TORIEx
//                            enables the EQADC to generate an interrupt
//                            request when the corresponding TORFx in EQADC
//                            FIFO and Interrupt Status Registers
//                            (EQADC_FISR), is asserted. Apart from
//                            generating an independent interrupt request for
//                            a CFIFOx Trigger Overrun event, the EQADC also
//                            provides a combined interrupt at which the
//                            Result FIFO Overflow Interrupt, the Command
//                            FIFO Underflow Interrupt, and the Command FIFO
//                            Trigger Overrun Interrupt requests of ALL
//                            CFIFOs are ORed. When RFOIEx, CFUIEx, and
//                            TORIEx are all asserted, this combined
//                            interrupt request is asserted whenever one of
//                            the following 18 flags becomes asserted:
//                            RFOFx, CFUFx, and TORFx (assuming that all
//                            interrupts are enabled).
//
//                              0 Disable trigger overrun interrupt request.
//                              1 Enable trigger overrun interrupt request
//
// PIE              2     rw  Pause Interrupt Enable x. PIEx enables the
//                            EQADC to generate an interrupt request when
//                            the corresponding PFx in EQADC FIFO and
//                            Interrupt Status Registers (QEADC_FISR),
//                            is asserted.
//
//                              0 Disable pause interrupt request.
//                              1 Enable pause interrupt request.
//
// EOQIE            3     rw  End of Queue Interrupt Enable x. EOQIEx enables
//                            the EQADC to generate an interrupt request when
//                            the corresponding EOQFx in EQADC FIFO and
//                            Interrupt Status Registers (EQADC_FISR),
//                            is asserted.
//                              0 Disable End of Queue interrupt request.
//                              1 Enable End of Queue interrupt request.
//
// CFUIE            4     rw  CFIFO Underflow Interrupt Enable x. CFUIEx
//                            enables the EQADC to generate an interrupt
//                            request when the corresponding CFUFx in EQADC
//                            FIFO and Interrupt Status Registers
//                            (EQADC_FISR), is asserted. Apart from
//                            generating an independent interrupt request for
//                            a CFIFOx underflow event, the EQADC also
//                            provides a combined interrupt at which the
//                            Result FIFO Overflow Interrupt, the Command
//                            FIFO Underflow Interrupt, and the Command FIFO
//                            Trigger Overrun Interrupt requests of ALL
//                            CFIFOs are ORed. When RFOIEx, CFUIEx, and
//                            TORIEx are all asserted, this combined
//                            interrupt request is asserted whenever one of
//                            the following 18 flags becomes asserted: RFOFx,
//                            CFUFx, and TORFx (assuming that all interrupts
//                            are enabled).
//                              0 Disable Underflow Interrupt request.
//                              1 Enable Underflow Interrupt request.
//
// 0                5     r   Reserved
//
// CFFE              6     rw  CFIFO Fill Enable x. CFFEx enables the EQADC
//                            to generate an interrupt request (CFFSx is
//                            asserted) or DMA request (CFFSx is negated)
//                            when CFFFx in EQADC FIFO and Interrupt Status
//                            Registers (EQADC_FISR),is asserted.
//
//                             0 Disable CFIFO Fill DMA or Interrupt request.
//                             1 Enable CFIFO Fill DMA or Interrupt request.
//                            Note: CFFEx must not be negated while a DMA
//                            transaction is in progress.
//
// CFFS              7     rw  CFIFO Fill Select x. CFFSx selects if a DMA or
//                            interrupt request is generated when CFFFx in
//                            EQADC FIFO and Interrupt Status Registers
//                            (EQADC_FISR), is asserted. If CFFEx is
//                            asserted, the QADC generates an interrupt
//                            request when CFFSx is negated, or it generates
//                            a DMA request if CFFSx is asserted.
//
//                              0 Generate interrupt request to move data
//                                from the system memory to CFIFOx.
//                              1 Generate DMA request to move data from the
//                                system memory to CFIFOx.
//                            Note: CFFSx must not be negated while a DMA
//                                  transaction is in progress.
//
// 0            [8:11]   r   Reserved
//                    
//
// RFOIE            12    rw  RFIFO Overflow Interrupt Enable x. RFOIEx
//                            enables the EQADC to generate an interrupt
//                            request when the corresponding RFOFx in ,EQADC
//                            FIFO and Interrupt Status Registers
//                            (EQADC_FISR), is asserted. Apart from
//                            generating an independent interrupt request for
//                            an RFIFOx overflow event, the EQADC also
//                            provides a combined interrupt at which the
//                            Result FIFO Overflow Interrupt, the Command
//                            FIFO Underflow Interrupt, and the Command
//                            FIFO Trigger Overrun Interrupt requests of ALL
//                            CFIFOs are ORed. When RFOIEx, CFUIEx, and
//                            TORIEx are all asserted, this combined
//                            interrupt request is asserted whenever one of
//                            the following 18 flags becomes asserted: RFOFx,
//                            CFUFx, and TORFx (assuming that all interrupts
//                            are enabled).
//                                0 Disable Overflow Interrupt request.
//                                1 Enable Overflow Interrupt request.
//
// 0                13    r   Reserved
//
// RFDE             14    rw  RFIFO Drain Enable x. RFDEx enables the EQADC
//                            to generate an interrupt request
//                            (RFDSx is asserted) or DMA request (RFDSx is
//                            negated) when RFDFx in, EQADC FIFO and
//                            Interrupt Status Registers (EQADC_FISR), is
//                            asserted.
//
//                             0 Disable RFIFO Drain DMA or Interrupt request
//                             1 Enable RFIFO Drain DMA or Interrupt request.
//                            Note: RFDEx must not be negated while a DMA
//                                  transaction is in progress.
//
// RFDS             15    rw  RFIFO Drain Select x. RFDSx selects if a DMA or
//                            interrupt request is generated when RFDFx in
//                            EQADC FIFO and Interrupt Status Registers
//                            (EQADC_FISR), is asserted.If RFDEx is asserted,
//                            the EQADC generates an interrupt request when
//                            RFDSx is negated, or it generates a DMA request
//                            when RFDSx is asserted.
//
//                             0 Generate interrupt request to move data
//                               from RFIFOx to the system memory.
//                             1 Generate DMA request to move data from
//                               RFIFOx to the system memory.
//                            Note: RFDSx must not be negated while a DMA
//                                 transaction is in progress.
//
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct QADC_IDCR_F_Tag
{
   bitfield16_t  NCIE    :  BIT_1;  // Bit      0
   bitfield16_t  TORIE   :  BIT_1;  // Bit      1
   bitfield16_t  PIE     :  BIT_1;  // Bit      2
   bitfield16_t  EOQIE   :  BIT_1;  // Bit      3
   bitfield16_t  CFUIE   :  BIT_1;  // Bit      4
   bitfield16_t          :  BIT_1;  // Bit      5   is reserved
   bitfield16_t  CFFE    :  BIT_1;  // Bit      6
   bitfield16_t  CFFS    :  BIT_1;  // Bit      7
   bitfield16_t          :  BIT_4;  // Bits [8:11] are reserved
   bitfield16_t  RFOIE   :  BIT_1;  // Bit      12
   bitfield16_t          :  BIT_1;  // Bit      13   is reserved
   bitfield16_t  RFDE    :  BIT_1;  // Bit      14
   bitfield16_t  RFDS    :  BIT_1;  // Bit      15

}  QADC_IDCR_F_T;

typedef union QADC_IDCR_Tag
{
   QADC_IDCR_F_T        F;
   uint16_t             U16;

}  QADC_IDCR_T;

//=============================================================================
// ID - eQADC FIFO and Interrupt Status Registers (QADC_FISR)
// Base Offset : 0000 0070H - 0000 0084H
//
// Reset Value : 0200 0000H
//
// Field        Bits     Type  Description
// =========== ========= ====  ===============================================
// NCFx          0        rw   Non-Coherency Flag. NCFx is set whenever a
//                             command sequence being transferred through
//                             CFIFOx becomes non coherent. If NCIEx in
//                             QADC Interrupt and DMA Control Registers
//                             (QADC_IDCR), and NCFx are asserted, an
//                             interrupt request will be generated. Write 1 to
//                             clear NCFx. Writing a 0 has no effect.
//                             0 Command sequence being transferred by
//                             CFIFOx is coherent.
//                             1 Command sequence being transferred by
//                             CFIFOx became non-coherent.
//
// TORFx        1         rw   Trigger Overrun Flag for CFIFOx. TORFx is set
//                             when trigger overrun occurs for the specified
//                             CFIFO in edge or level trigger mode. Trigger
//                             overrun occurs when an already triggered CFIFO
//                             receives an additional trigger. When TORIEx in
//                             QADC Interrupt and DMA Control Registers
//                             (QADC_IDCR),and TORFx are asserted, an
//                             interrupt request will be generated. Apart from
//                             generating an independent interrupt request for
//                             a CFIFOx Trigger Overrun event, the QADC also
//                             provides a combined interrupt at which the
//                             Result FIFO Overflow Interrupt, the Command
//                             FIFO Underflow Interrupt, and the Command FIFO
//                             Trigger Overrun Interrupt requests of ALL
//                             CFIFOs are ORed. When RFOIEx, CFUIEx,and TORIEx
//                             are all asserted, this combined interrupt
//                             request is asserted whenever one of the
//                             following 18 flags becomes asserted: RFOFx,
//                             CFUFx, and TORFx (assuming that all interrupts.
//                             are enabled) Write 1 to clear the TORFx bit.
//                             Writing a 0 has no effect.
//                             0 No trigger overrun occurred.
//                             1 Trigger overrun occurred.
//
//                             Note: The trigger overrun flag will not set for
//                             CFIFOs configured for software trigger
//                             mode
//
// PFx        2          rw   Pause Flag x. PF behavior changes according to
//                            the CFIFO trigger mode. In edge trigger mode,
//                            PFx is set when the QADC completes the
//                            transfer of an entry with an asserted Pause
//                            bit from CFIFOx. In level trigger mode, when
//                            CFIFOx is in TRIGGERED status, PFx is set when
//                            CFIFO status changes from TRIGGERED due to the
//                            detection of a closed gate.An interrupt routine
//                            generated due to the asserted PF, can be used
//                            to verify if a complete scan of the CQueue was
//                            performed. If a closed gate is detected while
//                            no command transfers are taking place, it will
//                            have immediate effect on the CFIFO status. If
//                            a closed gate is detected while a command
//                            transfer to an on-chip CBuffer is taking place,
//                            it will only affect the CFIFO status when the
//                            transfer completes.If a closed gate is detected
//                            during the serial transmission of a command to
//                            the external device, it will have no effect on
//                            the CFIFO status until the transmission
//                            completes.The transfer of entries bound for the
//                            on-chip ADCs is considered completed when they
//                            are stored in the appropriate CBuffer. The
//                            transfer of entries bound for the external
//                            device is considered completed when the serial
//                            transmission of the entry is completed. In
//                            software trigger mode, PFx will never become
//                            asserted. If PIEx in QADC Interrupt and DMA
//                            Control Registers (QADC_IDCR), and PFx are
//                            asserted, an interrupt will be generated. Write
//                            1 to clear the PFx. Writing a 0  has no effect.
//
//                            0 Entry with asserted PAUSE bit was not
//                              transferred from CFIFOx (CFIFO in
//                              edge trigger mode), or CFIFO status did
//                              not change from TRIGGERED due to detection
//                              of a closed gate(CFIFO in level trigger mode)
//                            1 Entry with asserted PAUSE bit was transferred
//                              from CFIFOx (CFIFO in edge trigger mode), or
//                              CFIFO status changes from TRIGGERED due to
//                              detection of a closed gate (CFIFO in level
//                              trigger mode).
//
//                            Note: In edge trigger mode, an asserted PFx
//                                  only implies that the QADC has finished
//                                  transferring a command with an asserted
//                                  PAUSE bit from CFIFOx. It does not imply
//                                  that result data for the current command
//                                  and for all previously transferred
//                                  commands hasbeen returned to the .
//                                  appropriate RFIFO.
//
//                            Note: In software or level trigger mode, when
//                                  the QADC completes the transfer of an
//                                  entry from CFIFOx with an asserted
//                                  PAUSE bit, PFx will not be set and
//                                  transfer of commands will continue
//                                  without pausing.
//
// EOQFx       3        rw    End of Queue Flag x. EOQFx indicates
//                            that an entry with an asserted EOQ bit
//                            was transferred from CFIFOx to the
//                            on-chip ADCs or to the external device.
//                            When the QADC completes the transfer of
//                            an entry with an asserted EOQ bit from
//                            CFIFOx, EOQFx will be set. The transfer
//                            of entries bound for the on-chip ADCs
//                            is considered completed when they are
//                            stored in the appropriate CBuffer. The
//                            transfer of entries bound for the
//                            external device is considered completed
//                            when the serial transmission of the
//                            entry is completed. If the EOQIEx
//                            bit in QADC Interrupt and DMA Control
//                            Registers (QADC_IDCR),and EOQFx are
//                            asserted, an interrupt will be
//                            generated. Write 1 to clear the EOQFx
//                            bit. Writing a 0 has no effect.
//
//                              0 Entry with asserted EOQ bit was
//                                not transferred from CFIFOx.
//                              1 Entry with asserted EOQ bit was
//                                transferred from CFIFOx.
//                            Note: An asserted EOQFx only implies that
//                                the QADC has finished
//                                transferring a command with an
//                                asserted EOQ bit from CFIFOx. It
//                                does not imply that result data
//                                for the current command and for
//                                all previously transferred commands
//                                has been returned to the
//                                appropriate RFIFO.
//
// CFUFx       4         rw   CFIFO Underflow Flag x. CFUFx indicates an
//                            underflow event on CFIFOx. CFUFx is set when
//                            CFIFOx is in TRIGGERED state and it becomes
//                            empty. No commands will be transferred from
//                            an underflowing CFIFO, nor will command
//                            transfers from lower priority CFIFOs be
//                            blocked. When CFUIEx in QADC Interrupt and
//                            DMA Control Registers (QADC_IDCR), and
//                            CFUFx are both asserted, the QADC
//                            generates an interrupt request. Apart
//                            from generating an independent interrupt
//                            request for a CFIFOx underflow event, the
//                            QADC also provides a combined interrupt
//                            at which the Result FIFO Overflow Interrupt,
//                            the Command FIFO Underflow Interrupt, and
//                            the Command FIFO Trigger Overrun Interrupt
//                            requests of ALL CFIFOs are ORed. When RFOIEx,
//                            CFUIEx, and TORIEx are all asserted, this
//                            combined interrupt request is asserted
//                            whenever one of the following 18 flags
//                            becomes asserted: RFOFx,CFUFx, and TORFx
//                            (assuming that all interrupts are enabled).
//                            Write 1 to clear CFUFx. Writing a 0 has no
//                            effect.
//                               0 No CFIFO underflow event occurred.
//                               1 A CFIFO underflow event occurred.
//
// SSSx       5           r  CFIFO Single-Scan Status Bit x. An asserted
//                            SSSx bit enables the detection of trigger
//                            events for CFIFOs programmed into single-scan
//                            level- or edge-trigger mode, and works as
//                            trigger for CFIFOs programmed into
//                            single-scan software-trigger mode. The SSSx
//                            bit is set by writing a 1 to the SSEx bit
//                            in QADC CFIFO Control Registers (QADC_CFCR),
//                            The QADC clears the SSSx bit when a command
//                            with an asserted EOQ bit is transferred from
//                            a CFIFO in single-scan mode, when a CFIFO is
//                            in single-scan level-trigger mode and its
//                            status changes from TRIGGERED due to the
//                            detection of a closed gate, or when the value
//                            of the CFIFO operation mode (MODEx) in QADC
//                            CFIFO Control Registers (QADC_CFCR), is
//                            changed to disabled. Writing to SSSx has no
//                            effect. SSSx has no effect in continuous-scan
//                            or in disabled mode.
//
//                              0 CFIFO in single-scan level- or
//                                edge-trigger mode will ignore trigger
//                                events, or CFIFO in single-scan
//                                software-trigger mode is not triggered.
//
//                              1 CFIFO in single-scan level- or
//                                edge-trigger mode will detect a trigger
//                                event, or CFIFO in single-scan
//                                software-trigger mode is triggered.
//
// CFFFx        6         r   CFIFO Fill Flag x. CFFFx is set when the
//                            CFIFOx is not full. When CFFEx in QADC
//                            Interrupt and DMA Control Registers
//                            (QADC_IDCR), and CFFFx are both asserted,
//                            an interrupt or a DMA request will be
//                            generated depending on the status of the
//                            CFFSx bit. When CFFSx is negated (interrupt
//                            requests selected), software clears CFFFx
//                            by writing a 1 to it. Writing a 0 has no
//                            effect. When CFFSx is asserted (DMA
//                            requests selected), CFFFx is automatically
//                            cleared by the QADC when the CFIFO becomes
//                            full.
//
//                              0 CFIFOx is full.
//                              1 CFIFOx is not full.
//
//                            Note: Writing 1  to CFFFx when CFFSx is
//                                  asserted (DMA requests selected) is
//                                  not allowed.
//
// 0          [7:11]       r  Reserved
//
// RFOFx         12      rw   RFIFO Overflow Flag x. RFOFx indicates an
//                            overflow event on RFIFOx. RFOFx is set when
//                            RFIFOx is already full, and a new data is
//                            received from the on-chip ADCs or from the
//                            external device. The RFIFOx will not
//                            overwrite older data in the RFIFO, and the
//                            new data will be ignored. When RFOIEx in
//                            QADC Interrupt and DMA Control Registers
//                            (QADC_IDCR), and RFOFx are both asserted,
//                            the QADC generates an interrupt request.
//                            Apart from generating an independent
//                            interrupt request for an RFIFOx overflow
//                            event, the QADC also provides a combined
//                            interrupt at which the Result FIFO Overflow
//                            Interrupt, the Command FIFO Underflow
//                            Interrupt, and the Command FIFO Trigger
//                            Overrun Interrupt requests of ALL CFIFOs
//                            are ORed. When RFOIEx, CFUIEx, and TORIEx
//                            are all asserted, this combined interrupt
//                            request is asserted whenever one of the
//                            following 18 flags becomes asserted: RFOFx,
//                            CFUFx, and TORFx (assuming that all interrupts
//                            are enabled). Write 1 to clear RFOFx.
//                            Writing a 0 has no effect.
//
//                               0 No RFIFO overflow event occurred.
//                               1 An RFIFO overflow event occurred.
//
// 0            13        r   Reserved
//
// RFDFx        14       rw   RFIFO Drain Flag x. RFDFx indicates if RFIFOx
//                            has valid entries or not. RFDFx is set when the
//                            RFIFOx has at least one valid entry in it.
//                            When RFDEx in QADC Interrupt and DMA Control
//                            Registers (QADC_IDCR), and RFDFx are both
//                            asserted, an interrupt or a DMA request will
//                            be generated depending on the status of the
//                            RFDSx bit. When RFDSx is negated (interrupt
//                            requests selected), software clears RFDFx by
//                            writing a 1 to it. Writing a 0 has no effect.
//                            When RFDSx is asserted (DMA requests selected),
//                            RFDFx is automatically cleared by the QADC
//                            when the RFIFO becomes empty.
//
//                               0 RFIFOx is empty.
//                               1 RFIFOx has at least one valid entry.
//
//                            Note: Writing 1 to RFDFx when RFDSx is
//                            asserted(DMA requests selected) is not allowed.
//
// 0             15       r   Reserved
//
// CFCTRx      [16:19]    r   CFIFOx Entry Counter. CFCTRx indicates the
//                            number of commands stored in the CFIFOx.
//                            When the QADC completes transferring a
//                            piece of new data from the CFIFOx, it
//                            decrements CFCTRx by one. Writing a word
//                            or any bytes to the corresponding QADC
//                            CFIFO Push Registers (QADC_CFPR),
//                            increments CFCTRx by one. Writing any
//                            value to CFCTRx has no effect.
//
// TNXTPTRx     [20:23]   r   CFIFOx Transfer Next Pointer. TNXTPTRx
//                            indicates the index of the next entry to
//                            be removed from CFIFOx when it completes a
//                            transfer. When TNXTPTRx is zero, it points
//                            to the entry with the smallest memory:mapped
//                            address inside CFIFOx. TNXTPTRx is only
//                            updated when a command transfer is completed.
//                            If the maximum index number (CFIFO depth minus
//                            one) is reached, TNXTPTRx is wrapped to zero,
//                            else, it is incremented by one. Writing any
//                            value to TNXTPTRx has no effect.
//
// RFCTRx       [24:27]   r   RFIFOx Entry Counter. RFCTRx indicates the
//                            number of data items stored in the RFIFOx.
//                            When the QADC stores a piece of new data
//                            into RFIFOx, it increments RFCTRx by one.
//                            Reading the whole word, half-word or any
//                            bytes of the corresponding QADC Result FIFO
//                            Pop Registers (QADC_RFPR),decrements RFCTRx
//                            by one. Writing any value to RFCTRx itself
//                            has no effect.
//
// POPNXTPTRx   [28:31]   r   RFIFOx Pop Next Pointer. POPNXTPTRx indicates
//                            the index of the entry that will be returned
//                            when QADC_RFPRx is read. When POPNXTPTRx is
//                            zero, it points to the entry with the
//                            smallest memory-mapped address inside RFIFOx.
//                            POPNXTPTRx is updated when QADC_RFPRx is
//                            read. If the maximum index number (RFIFO
//                            depth minus one) is reached, POPNXTPTRx is
//                            wrapped to zero, else, it is incremented by
//                            one. Writing any value to POPNXTPTRx has no
//                            effect.
//
//=============================================================================
typedef struct QADC_FISR_F_Tag
{
   bitfield32_t  NCF         :  BIT_1;   // Bit       0
   bitfield32_t  TORF        :  BIT_1;   // Bit       1
   bitfield32_t  PF          :  BIT_1;   // Bit       2
   bitfield32_t  EOQF        :  BIT_1;   // Bit       3
   bitfield32_t  CFUF        :  BIT_1;   // Bit       4
   bitfield32_t  SSS         :  BIT_1;   // Bit       5
   bitfield32_t  CFFF        :  BIT_1;   // Bit       6
   bitfield32_t              :  BIT_5;   // Bits  [7:11] are reserved
   bitfield32_t  RFOF        :  BIT_1;   // Bit       12
   bitfield32_t              :  BIT_1;   // Bit       13
   bitfield32_t  RFDF        :  BIT_1;   // Bit       14
   bitfield32_t              :  BIT_1;   // Bit       15
   bitfield32_t  CFCTR       :  BIT_4;   // Bits  [16:19]
   bitfield32_t  TNXTPTR     :  BIT_4;   // Bits  [20:23]
   bitfield32_t  RFCTR       :  BIT_4;   // Bits  [24: 27]
   bitfield32_t  POPNXTPTR   :  BIT_4;   // Bits  [28:31]

}  QADC_FISR_F_T;

typedef union QADC_FISR_Tag
{
   QADC_FISR_F_T        F;
   uint32_t             U32;

}  QADC_FISR_T;

//=============================================================================
// ID - eQADC CFIFO Transfer Counter Registers (QADC_CFTCR)
// Base Offset : 0000 0090H - 0000 0098H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
// ========== ========== ==== ===============================================
// 0           [15:11]     r  Reserved
//
// TC_CFx      [10: 0]    rw  Transfer Counter for CFIFOx. TC_CFx counts the
//                            number of commands which have been completely
//                            transferred from CFIFOx.The transfer of entries
//                            bound for the on-chip ADCs is considered
//                            completed when they are stored in the
//                            appropriate CBuffer. The transfer of entries
//                            bound for an external device is considered
//                            completed when the serial transmission of the
//                            entry is completed. The QADC increments the
//                            TC_CFx value by one after a command is
//                            transferred. TC_CFx resets to zero after QADC
//                            completes transferring a command with an
//                            asserted EOQ bit. Writing any value to TC_CFx
//                            sets the counter to that written value.
//
//                            Note: If CFIFOx is in TRIGGERED state when its
//                                 MODEx field is programmed to disabled, the
//                                 exact number of entries transferred from
//                                 the CFIFO until that point - TC_CFx - is
//                                 only known after the CFIFO status changes
//                                 to IDLE, as indicated by CFSx.
//
//=============================================================================
typedef struct QADC_CFTCR_F_Tag
{
   bitfield16_t              :  BIT_5;   // Bits  [0:4] are reserved
   bitfield16_t  TC_CF       :  BIT_11;  // Bits  [5:15]

}  QADC_CFTCR_F_T;

typedef union QADC_CFTCR_Tag
{
   QADC_CFTCR_F_T       F;
   uint16_t             U16;

}  QADC_CFTCR_T;

//=============================================================================
// ID - eQADC CFIFO Status Snapshot Registers (QADC_CFSSR)
// Base Offset : 0000 00A0H - 0000 00A4H
//
// Reset Value : 0000 7800H
//
// Field          Bits    Type Description
// =========== ========= ==== ===============================================
// CFSx_TCBn   [0:11]     r   CFIFO Status at Transfer to CBuffern (n=0,1).
//[0:1]                       CFSx_TCBn indicates the CFIFOx status at the
//                            time a command transfer to CBuffern is
//                            initiated. CFSx_TCBn is a copy of the
//                            corresponding CFSx in QADC CFIFO Status
//                            Register (QADC_CFSR), captured at the time a
//                            command transfer to CBuffern is initiated.
//
// 0           [12:16]     r  Reserved
//
// LCFTCBn     [17:20]     r  Last CFIFO to Transfer to CBuffern (n=0,1).
// [0:3]                      LCFTCBn holds the CFIFO number of last CFIFO
//                            to have initiated a command transfer to
//                            CBuffern.
//
//                                      LCFTCBn Description
//
//                               LCFTCBn          LCFTCBn Meaning
//                                [0:3]
//                               0b0000      Last cmd was transferred from
//                                           CFIFO0
//                               0b0001      Last command was transferred
//                                           from CFIFO1
//                               0b0010      Last command was transferred
//                                           from CFIFO2
//                               0b0011      Last command was transferred
//                                           from CFIFO3
//                               0b0100      Last command was transferred
//                                           from CFIFO4
//                               0b0101      Last command was transferred
//                                           from CFIFO5
//                               0b0110 -    Reserved
//                               0b1110
//                               0b1111      No command was transferred to
//                                           CBuffern
//
// TC_LCFTCBn   [21:31]     r  Transfer Counter for Last CFIFO to transfer
// [0:10]                     commands to CBuffern. TC_LCFTCBn indicates
//                            the number of commands which have been
//                            completely transferred from CFIFOx when a
//                            command transfer from CFIFOx to CBuffern is
//                            initiated. TC_LCFTCBn is a copy of the
//                            corresponding TC_CFx in QADC CFIFO Transfer
//                            Counter Registers (QADC_CFTCR), captured
//                            at the time a command transfer from CFIFOx
//                            to CBuffern is initiated. This field has no
//                            meaning when LCFTCBn is 0b1111.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================
typedef struct QADC_CFSSR_F_Tag
{
   bitfield32_t   CFS0_TCB      :  BIT_2;   // Bits  [0:1]
   bitfield32_t   CFS1_TCB      :  BIT_2;   // Bits  [2:3]
   bitfield32_t   CFS2_TCB      :  BIT_2;   // Bits  [4:5]
   bitfield32_t   CFS3_TCB      :  BIT_2;   // Bits  [6:7]
   bitfield32_t   CFS4_TCB      :  BIT_2;   // Bits  [8:9]
   bitfield32_t   CFS5_TCB      :  BIT_2;   // Bits  [10:11]
   bitfield32_t                 :  BIT_5;   // Bits  [12:16] are reserved
   bitfield32_t   LCFTCB        :  BIT_4;   // Bits  [17:20]
   bitfield32_t   TC_LCFTCB     :  BIT_11;  // Bits  [21:31]

}  QADC_CFSSR_F_T;

typedef union QADC_CFSSR_Tag
{
   QADC_CFSSR_F_T       F;
   uint32_t             U32;

}  QADC_CFSSR_T;

//=============================================================================
// ID - eQADC CFIFO Status Snapshot Register2 (QADC_CFSSR2)
// Base Offset : 0000 00A8H
//
// Reset Value : 0000 7800H
//
// Field          Bits    Type Description
// =========== ========= ==== ===============================================
// CFSx_TSSI      [0:11]    r  CFIFO Status at Transfer through the QADC
// [0:1]                       SSI. CFSx_TSSI indicates the CFIFOx status
//                             at the time a serial transmission through
//                             the QADC SSI is initiated. CFSx_TSSI is a
//                             copy of the corresponding CFSx in QADC
//                             CFIFO Status Register (QADC_CFSR),
//                             capture at the time a serial transmission
//                             through the QADC SSI is initiated.
//
// 0            [12:15]     r  Reserved
//
// ECBNI            16      r   External CBuffer Number Indicator. ECBNI
//                              indicates to which external CBuffer the
//                              last command was transmitted.
//                              0 Last command was transferred to CBuffer2.
//                              1 Last command was transferred to CBuffer3.
//
// LCFTSSI     [17:20]     r   Last CFIFO to Transfer Commands through the
// [0:3]                       QADC SSI. LCFTSSI holds the CFIFO number of
//                             last CFIFO to have initiated a command
//                             transfer to an external CBuffer through the
//                             QADC SSI. LCFTSSI does not indicate the
//                             transmission of null messages.
//
//                                   LCFTSSI Description
//                             LCFTSSI[0:3]           LCFTSSI Meaning
//
//                             0b0000          Last command was transferred
//                                            from CFIFO0
//                             0b0001          Last command was transferred
//                                            from CFIFO1
//                             0b0010          Last command was transferred
//                                            from CFIFO2
//                             0b0011          Last command was transferred
//                                            from CFIFO3
//                             0b0100          Last command was transferred
//                                            from CFIFO4
//                             0b0101          Last command was transferred
//                                            from CFIFO5
//                             0b0110 -        Reserved
//                             0b1110
//                             0b1111          No command was transferred to
//                                            an external CBuffer
//
// TC_LCFTSSI   [21:31]     r  Transfer Counter for Last CFIFO to Transfer
// [0:10]                      commands through QADC SSI. TC_LCFTSSI
//                             indicates the number of commands which have
//                             been completely transferred from a
//                             particular CFIFO at the time a command
//                             transfer from that CFIFO to an external
//                             CBuffer is initiated. TC_LCFTSSI is a copy
//                             of the corresponding TC_CFx in QADC CFIFO
//                             Transfer Counter Registers (QADC_CFTCR),
//                             captured at the time a command transfer to
//                             an external CBuffer is initiated. This
//                             field has no meaning when LCFTSSI is 0b1111.
//
//=============================================================================
typedef struct QADC_CFSSR2_F_Tag
{
   bitfield32_t   CFS0_TSSI     :  BIT_2;   // Bits  [0:1]
   bitfield32_t   CFS1_TSSI     :  BIT_2;   // Bits  [2:3]
   bitfield32_t   CFS2_TSSI     :  BIT_2;   // Bits  [4:5]
   bitfield32_t   CFS3_TSSI     :  BIT_2;   // Bits  [6:7]
   bitfield32_t   CFS4_TSSI     :  BIT_2;   // Bits  [8:9]
   bitfield32_t   CFS5_TSSI     :  BIT_2;   // Bits  [10:11]
   bitfield32_t                 :  BIT_4;   // Bits  [12:15]
   bitfield32_t   ECBNI         :  BIT_1;   // Bit     16
   bitfield32_t   LCFTSSI       :  BIT_4;   // Bits  [17:20]
   bitfield32_t   TC_LCFTSSI    :  BIT_11;  // Bits  [21:31]

}  QADC_CFSSR2_F_T;

typedef union QADC_CFSSR2_Tag
{
   QADC_CFSSR2_F_T      F;
   uint32_t             U32;

}  QADC_CFSSR2_T;

//=============================================================================
// ID - eQADC CFIFO Status Register (QADC_CFSR)
// Base Offset : 0000 00ACH
//
// Reset Value : 0000 0000H
//
// Field          Bits   Type  Description
// =========== ========= ==== ===============================================
// CFSx[0:1]   [0:11]     r  CFIFO Status. CFSx indicates the current status
//                            of CFIFOx.
//                                          Current CFIFO Status
//
//                            CFIFO Status  Field Val      Explanation
//
//                            IDLE          0b00     CFIFO is disabled.
//                                                   CFIFO is in
//                                                   single-scan edge or
//                                                   level trigger mode
//                                                   and does not have
//                                                   SSS asserted. QADC
//                                                   completed the transfer
//                                                   of the last entry of
//                                                   the CQueue in
//                                                   single-scan mode.
//
//                            Reserved      0b01     Not applicable.
//
//                            WAITING FOR   0b10     CFIFO Mode is modified
//                                                   to
//                                                   continuous-scan edge or
//                                                   level trigger mode.
//
//                                                   single-scan edge or
//                                                   level trigger mode and
//                                                   SSS is asserted.
//
//                                                   single-scan software
//                                                   trigger mode and SSS is
//                                                   negated.CFIFO is paused.
//
//                                                   QADC transferred the
//                                                   last entry of the queue
//                                                   in continuous-scan edge
//                                                   trigger mode.
//
//                            TRIGGERED     0b11     CFIFO is triggered
//
// 0            [12:31]     r  Reserved
//
//=============================================================================
typedef struct QADC_CFSR_F_Tag
{
   bitfield32_t   CFS0     :  BIT_2;   // Bits  [0:1]
   bitfield32_t   CFS1     :  BIT_2;   // Bits  [2:3]
   bitfield32_t   CFS2     :  BIT_2;   // Bits  [4:5]
   bitfield32_t   CFS3     :  BIT_2;   // Bits  [6:7]
   bitfield32_t   CFS4     :  BIT_2;   // Bits  [8:9]
   bitfield32_t   CFS5     :  BIT_2;   // Bits  [10:11]
   bitfield32_t            :  BIT_20;  // Bits  [12:31]

}  QADC_CFSR_F_T;

typedef union QADC_CFSR_Tag
{
   QADC_CFSR_F_T        F;
   uint32_t             U32;

}  QADC_CFSR_T;

//=============================================================================
// ID - eQADC SSI Control Register (QADC_SSICR)
// Base Offset : 0000 00B4H
//
// Reset Value : 0000 070FH
//
// Field          Bits   Type  Description
// =========== ========= ==== ===============================================
// 0             [0:20]     r  Reserved
//
// MDT[0:2]      [21:23]    r  Minimum Delay after Transmission. MDT field
//                             defines the minimum delay after transmission
//                             time (tMDT) expressed in serial clock (FCK)
//                             periods. tMDT is minimum time SDS should be
//                             kept negated between two consecutive serial
//                             transmissions. The MDT field must only be
//                             written when the serial transmissions from the
//                             QADC SSI are disabled.
//
//                            Minimum Delay After Transmission (tMDT) Time
//
//                                    MDT                  tMDT
//                                                     (FCK period)
//                                   0b000                  1
//                                   0b001                  2
//                                   0b010                  3
//                                   0b011                  4
//                                   0b100                  5
//                                   0b101                  6
//                                   0b110                  7
//                                   0b111                  8
//
// 0             [24:27]   r  Reserved
//
// BR[0:3]       [28:31]   r  Baud Rate Field. The BR field selects system
//                            clock divide factor as shown in Table . The
//                            baud clock is calculated by dividing the
//                            system clock by the clock divide factor
//                            specified with the BR field.
//                            Note:The BR field must only be written when the
//                                 QADC SSI is disabled.
//
//                                System Clock Divide Factor for Baud Clock
//
//                                  BR[0:3]    System Clock Divide Factor 1
//                                   0b0000                  2
//                                   0b0001                  3
//                                   0b0010                  4
//                                   0b0011                  5
//                                   0b0100                  6
//                                   0b0101                  7
//                                   0b0110                  8
//                                   0b0111                  9
//                                   0b1000                  10
//                                   0b1001                  11
//                                   0b1010                  12
//                                   0b1011                  13
//                                   0b1100                  14
//                                   0b1101                  15
//                                   0b1110                  16
//                                   0b1111                  17
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================
typedef struct QADC_SSICR_F_Tag
{
   bitfield32_t            :  BIT_21;  // Bits  [0:20]
   bitfield32_t   MDT      :  BIT_3;   // Bits  [21:23]
   bitfield32_t            :  BIT_4;   // Bits  [24:27]
   bitfield32_t   BR       :  BIT_4;   // Bits  [28:31]

}  QADC_SSICR_F_T;

typedef union QADC_SSICR_Tag
{
   QADC_SSICR_F_T       F;
   uint32_t             U32;

}  QADC_SSICR_T;

//=============================================================================
// ID - eQADC SSI Receive Data Register (QADC_SSIRDR)
// Base Offset : 0000 00B8H
//
// Reset Value : 000F 0000H
//
// Field          Bits    Type Description
// ========= =========== ==== ===============================================
//
// RDV              0      r  RDV Receive Data Valid Bit. The RDV bit
//                            indicates if the last received data is valid.
//                            This bit is cleared automatically whenever the
//                            QADC_SSIRDR register is read. Writes have no
//                            effect.
//                                0 Receive data is not valid.
//                                1 Receive data is valid.
//
// 0           [1:5]       r  Reserved
//
// R_DATA       [6:31]     r  QADC Receive DATA Field. The R_DATA contains
//                            the last result message that was shifted in.
//                            Writes to the R_DATA have no effect. Messages
//                            that were not completely received due to a
//                            transmission abort will not be copied into
//                            QADC_SSIRDR.
//
//=============================================================================

typedef struct QADC_SSIRDR_F_Tag
{
   bitfield32_t   RDV      :  BIT_1;   // Bit     0
   bitfield32_t            :  BIT_5;   // Bits  [1:5] are reserved
   bitfield32_t   R_DATA   :  BIT_26;  // Bits  [6:31]

}  QADC_SSIRDR_F_T;

typedef union QADC_SSIRDR_Tag
{
   QADC_SSIRDR_F_T      F;
   uint32_t             U32;

}  QADC_SSIRDR_T;


//=============================================================================
// ID - eQADC Red Line Client Configuration Register (JTAGC_REDLCCR)
// Base Offset : 0000 0x0D0H
//
// Reset Value : 000F 0000H
//
// Field          Bits    Type Description
// ========= =========== ==== ===============================================
//
//               [0:15]    r   reserved.
//
//REDBSm         [16:19]   rw  Red Line Timebase Bits Selection m (m=1,2)
//               [24:27]       The REDBSm field selects 16 bits from the total
//                             of 24 bits that are received from the Red Line
//                             interface as described in below. Consider 
//                             TBASEm[0:23] the selected time base from slot SRVm:
//
//                             REDBSm[0:3]       Selected Bits
//                             0b0000             TBASEm[0:15]
//                             0b0001             TBASEm[1:16]
//                             0b0010             TBASEm[2:17]
//                             0b0011             TBASEm[3:18]
//                             0b0100             TBASEm[4:19]
//                             0b0101             TBASEm[5:20]
//                             0b0110             TBASEm[6:21]
//                             0b0111             TBASEm[7:22]
//                             0b1000             TBASEm[8:23]
//                             Others              Reserved
//
//SRVm         [20:23]         Red Line Server Data Slot Selector m (m=1,2)
//             [28:31]         The field SRVm indicates the slot number that 
//                             contains the desired time base value sent by 
//                             the Red Line server. It is possible to have up
//                             to 16 different sources to be selected.
//=============================================================================

typedef struct QADC_REDLCCR_F_Tag
{
   bitfield32_t              :BIT_16;   //[0:15] reserved
   bitfield32_t   REDBS2     :BIT_4;    //[16:19]
   bitfield32_t   SRV2       :BIT_4;    //[20:23]
   bitfield32_t   REDBS1     :BIT_4;    //[24:27]
   bitfield32_t   SRV1       :BIT_4;    //[28:31]

}QADC_REDLCCR_F_T;

typedef union QADC_REDLCCR_Tag
{
   QADC_REDLCCR_F_T    F;
   uint32_t             U32;

}QADC_REDLCCR_T;

//=============================================================================
// ID - eQADC CFIFO Registers (QADC_CFxRw)
//
// Base Offset : 
// CFIFO0: Base + 0x100 (CF0R0); Base + 0x104 (CF0R1); Base + 0x108 (CF0R2); Base + 0x10C (CF0R3)
// CFIFO1: Base + 0x140 (CF1R0); Base + 0x144 (CF1R1); Base + 0x148 (CF1R2); Base + 0x14C (CF1R3)
// CFIFO2: Base + 0x180 (CF2R0); Base + 0x184 (CF2R1); Base + 0x188 (CF2R2); Base + 0x18C (CF2R3)
// CFIFO3: Base + 0x1C0 (CF3R0); Base + 0x1C4 (CF3R1); Base + 0x1C8 (CF3R2); Base + 0x1CC (CF3R3)
// CFIFO4: Base + 0x200 (CF4R0); Base + 0x204 (CF4R1); Base + 0x208 (CF4R2); Base + 0x20C (CF4R3)
// CFIFO5: Base + 0x240 (CF5R0); Base + 0x244 (CF5R1); Base + 0x248 (CF5R2); Base + 0x24C (CF5R3)
//               
//
// Reset Value : 0000 0000H
//
// Field          Bits    Type Description
// ============ ======== ==== ===============================================
//
// CFIFOx_DATAw [31:0]     r  CFIFOx Data w (w = 0, .., 3). Reading
//                            CFIFOx_DATAw returns the value stored on the
//                            wth entry of CFIFOx. Each CFIFO is composed of
//                            four 32-bit entries, with register 0 being
//                            mapped to the one with the smallest memory
//                            mapped address.
//
//=============================================================================
typedef struct QADC_CFR_Tag
{
   uint32_t          U32[QADC_CFR_QUANTITY];          // 0x0000 - 0x000F
   uint32_t          EQADC_CF0ER[QADC_CFR_QUANTITY];  // Only for CFIFO0 [0010-001C]
   uint8_t           reserved[QADC_RESERVED_0x0020];  // 0x0010 - 0x003F

}  QADC_CFR_T;


//=============================================================================
// ID - eQADC RFIFO Registers (QADC_RFxRw)
//
// Base Offset : 
// RFIFO0: Base + 0x300 (RF0R0); Base + 0x304 (RF0R1); Base + 0x308 (RF0R2); Base + 0x30C (RF0R3)
// RFIFO1: Base + 0x340 (RF1R0); Base + 0x344 (RF1R1); Base + 0x348 (RF1R2); Base + 0x34C (RF1R3)
// RFIFO2: Base + 0x380 (RF2R0); Base + 0x384 (RF2R1); Base + 0x388 (RF2R2); Base + 0x38C (RF2R3)
// RFIFO3: Base + 0x3C0 (RF3R0); Base + 0x3C4 (RF3R1); Base + 0x3C8 (RF3R2); Base + 0x3CC (RF3R3)
// RFIFO4: Base + 0x400 (RF4R0); Base + 0x404 (RF4R1); Base + 0x408 (RF4R2); Base + 0x40C (RF4R3)
// RFIFO5: Base + 0x440 (RF5R0); Base + 0x444 (RF5R1); Base + 0x448 (RF5R2); Base + 0x44C (RF5R3)
//
// Reset Value : 0000 0000H
//
// Field          Bits    Type Description
// ========== ========== ==== ===============================================
//
// 0           [31:16]     r  Reserved
//
// RFIFOx_      [15:0]     r  RFIFOx Data w (w = 0, .., 3). Reading
// DATAw                      RFIFOx_DATAw returns the value stored
//                            on the wth entry of RFIFOx. Each RFIFO
//                            is composed of four 16-bit entries, with
//                            register 0 being mapped to the one with
//                            the smallest memory mapped address.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//
//=============================================================================
typedef struct QADC_RFR_Tag
{
   uint32_t          U32[QADC_CFR_QUANTITY];          // 0x0000 - 0x000F
   uint8_t           reserved[QADC_RESERVED_0x0030];  // 0x0010 - 0x003F

}  QADC_RFR_T;


//=============================================================================
//  QADC Module Register Structure
//=============================================================================

typedef volatile struct QADC_Tag
{
   QADC_MCR_T        MCR;                                // 0x0000 - 0x0003

   QADC_TST_T        reserved;                           // 0x0004 - 0x0007 used only for factory test

   QADC_NMSFR_T      NMSFR;                              // 0x0008 - 0x000B

   QADC_ETDFR_T      ETDFR;                              // 0x000C - 0x000F

   uint32_t          CFPR[QADC_FIFO_QUANTITY];           // 0x0010 - 0x0027

   uint8_t           reserved_1[QADC_RESERVED_0x0008];   // 0x0028 - 0x002F

   QADC_RFPR_T       RFPR[QADC_FIFO_QUANTITY];           // 0x0030 - 0x0047

   uint8_t           reserved_2[QADC_RESERVED_0x0008];   // 0x0048 - 0x004F

   QADC_CFCR_T       CFCR[QADC_FIFO_QUANTITY];           // 0x0050 - 0x005B

   uint8_t           reserved_3[QADC_RESERVED_0x0004];   // 0x005C - 0x005F

   QADC_IDCR_T       IDCR[QADC_FIFO_QUANTITY];           // 0x0060 - 0x006B

   uint8_t           reserved_4[QADC_RESERVED_0x0004];   // 0x006C - 0x006F

   QADC_FISR_T       FISR[QADC_FIFO_QUANTITY];           // 0x0070 - 0x0087

   uint8_t           reserved_5[QADC_RESERVED_0x0008];   // 0x0088 - 0x008F

   QADC_CFTCR_T      CFTCR[QADC_FIFO_QUANTITY];          // 0x0090 - 0x009B

   uint8_t           reserved_6[QADC_RESERVED_0x0004];   // 0x009C - 0x009F

   QADC_CFSSR_T      CFSSR[QADC_CFSSR_QUANTITY];         // 0x00A0 - 0x00A7

   QADC_CFSSR2_T     CFSSR2;                             // 0x00A8 - 0x00AB

   QADC_CFSR_T       CFSR;                               // 0x00AC - 0x00AF

   uint8_t           reserved_7[QADC_RESERVED_0x0004];   // 0x00B0 - 0x00B3

   QADC_SSICR_T      SSICR;                              // 0x00B4 - 0x00B7

   QADC_SSIRDR_T     SSIRDR;                             // 0x00B8 - 0x00BB

   uint8_t           reserved_8[QADC_RESERVED_0x0014];   // 0x00BC - 0x00CF

   QADC_REDLCCR_T    REDLCCR;                            // 0x00D0 - 0x00D3

   uint8_t           reserved_9[QADC_RESERVED_0x002C];   // 0x00D4 - 0x00FC

   QADC_CFR_T        CFIFO[QADC_FIFO_QUANTITY];          // 0x0100 - 0x027F

   uint8_t           reserved_10[QADC_RESERVED_0x0080];   // 0x0280 - 0x02FF

   QADC_RFR_T        RFIFO[QADC_FIFO_QUANTITY];          // 0x0300 - 0x047F

   uint8_t           reserved_11[QADC_RESERVED_0x0380];  // 0x0480 - 0x07FF

}  QADC_T;

#endif // HW_QADC_H

