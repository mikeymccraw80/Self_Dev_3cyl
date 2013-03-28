#ifndef HW_FLASH_MPC5634_H
#define HW_FLASH_MPC5634_H


#include "reuse.h"

#define HW_ARRAY_SIZE_2 (2)

//wic Bit Masks
#define FLASH_EER_CLEAR_MASK (0xFFFFBFFF)
#define FLASH_RWE_CLEAR_MASK (0xFFFF7FFF)
//===========================================================================
// ID - Module Configuration Register (FLASH_MCR)
//
// Base Offset : 0x0000 0000
//
// Reset Value : 0x0760 3600
//
// Type        :
//
// Field        Bits     Type Description
//============= ======== ==== ===============================================
// 0            [31:28]   r   Reserved
//
// SIZE[3:0]    [27:24]   r   Array space size. Dependent upon the size of
//                            the Flash module. All possible values of SIZE
//                            and the configuration to which each value
//                            corresponds are shown below
//                            0000 256 Kbytes (No High or Mid Address Space)
//                            0001 512 Kbytes (No High Address Space)
//                            0010 768 Kbytes (256 Kbytes in High Addr Space)
//                            0011 1 Mbyte (512 Kbytes in High Address Space)
//                            0100 1.25 Mbytes
//                            0101 1.5 Mbytes
//                            0110 1.75 Mbytes
//                            0111 2 Mbytes
//                            1000 2.25 Mbytes
//                            1001 2.5 Mbytes
//                            1010 2.75 Mbytes
//                            1011 3 Mbytes
//                            1100 3.25 Mbytes
//                            1101 3.5 Mbytes
//                            1110 3.75 Mbytes
//                            1111 4 Mbytes
//
// 0                 23   r   Reserved
//
// LAS[2:0]     [22:20]   r   Low address space.
//                            Corresponds to the configuration of the low
//                            address space. All possible values of LAS and
//                            the configuration to which each value corres-
//                            ponds are shown below.
//                            000 Two 128-Kbyte blocks
//                            001 Four 64-Kbyte blocks
//                            010 Four 16-Kbyte blocks and Four 48-Kbyte
//                                blocks
//                            011 Sixteen 16-Kbyte blocks
//                            100 Eight 16-Kyte blocks and Two 64-Kbyte
//                                blocks
//                            101 Ten 16-Kbyte blocks and Two 48-Kbyte
//                                blocks
//                            110 Two 16-Kbyte blocks, Two 48-Kbyte blocks,
//                                and Two 64-Kbyte blocks
//                            111 Not Used
//
// 0            [19:17]   r   Reserved
//
// MAS               16   r   Mid address space size. Corresponds to the
//                            configuration of the mid address space.
//                            MAS is read only. The value of the parameter
//                            for this device is shown in bold.
//                            Note: The MAS encoding for the MPC5554 is 0.
//                            0 Two 128-Kbyte blocks are available
//                            1 Four 64-Kbyte midsize blocks are available
//
// EER               15   rw  ECC event error. Provides information on
//                            previous reads If a double bit detection
//                            occurred, the EER bit will be set to a 1.
//                            This bit must then be cleared, or a reset must
//                            occur before this bit will return to a 0 state.
//                            This bit may not be set by the user. In the
//                            event of a single bit detection and correction,
//                            this bit will not be set. If EER is not set,
//                            or remains 0, this indicates that all previous
//                            reads (from the last reset, or clearing ofEER)
//                            were correct. Since this bit is an error flag,
//                            it must be cleared to a 0 by writing a 1 to the
//                            register location. A write of 0 will have no
//                            effect.
//                            0 Reads are occurring normally.
//                            1 An ECC Error occurred during a previous read.
//
// RWE               14   rw  Read while write event error.
//                            Provides information on previous RWW reads.
//                            If a read while write error occurs, this bit
//                            will be set to 1. This bit must then be cleared
//                            or a reset must occur before this bit will
//                            return to a 0 state. This bit may not be writ-
//                            ten to a 1 by the user. If RWE is not set, or
//                            remains 0, this indicates that all previous RWW
//                            reads (from the last reset, or clearing of RWE)
//                            were correct. Since this bit is an error flag,
//                            it must be cleared to a 0 by writing a 1 to the
//                            register location. A write of 0 will have no
//                            effect.
//                            0 Reads are occurring normally.
//                            1 A Read While Write Error occurred during
//                            a previous read.
//
// 0            [13:12]   r   Reserved
// 
// PEAS              11   r   Program/erase access space.
//                            Indicates which space is valid for program
//                            and erase operations, either main array space
//                            or shadow space. PEAS is read only.
//                            0 Shadow address space is disabled for
//                            program/erase and main address space enabled
//                            1 Shadow address space is enabled for
//                            program/erase and main address space disabled.
//
// DONE              10   r   State machine status.
//                            Indicates if the Flash module is performing
//                            a high voltage operation.
//                            DONE is set to a 1 on termination of the Flash
//                            module reset. DONE is set to a 1 at the end of
//                            program and erase high voltage sequences.
//                            0 Flash is executing a high voltage operation.
//                            1 Flash is not executing a high voltage
//                            operation.
//
// PEG                9   r   Program/erase good.
//                            Indicates the completion status of the last
//                            Flash program or erase sequence for which high
//                            voltage operations were initiated. The value
//                            of PEG is updated automatically during the
//                            program and erase high voltage operations.
//                            Aborting a program/erase high voltage operation
//                            will cause PEG to be cleared, indicating the
//                            sequence failed. PEG is set to a 1 when the
//                            module is reset. PEG is read only.
//                            The value of PEG is valid only when PGM = 1
//                            and/or ERS = 1 and after DONE has transitioned
//                            from 0 to 1 due to an abort or the completion
//                            of a program/erase operation.
//                            PEG is valid until PGM/ERS makes a 1 to 0
//                            transition or EHV makes a 0 to 1 transition.
//                            The value in PEG is not valid after a 0 to 1
//                            transition of DONE caused by PSUS or ESUS being
//                            set to logic 1.
//                            0 Program or erase operation failed.
//                            1 Program or erase operation successful.
//
// 0              [8:7]   r   Reserved
//
// STOP               6   rw  Stop mode enabled.
//                            Puts the Flash into stop mode. Changing the
//                            value in STOP from a 0 to a 1 places the Flash
//                            module in stop mode. A 1 to 0 transition of
//                            STOP returns the Flash module to normal
//                            operation. STOP may be written only when PGM
//                            and ERS are low. When STOP = 1, only the STOP
//                            bit in the MCR can be written. In STOP mode
//                            all address spaces, registers and register bits
//                            are deactivated except for the FLASH_MCR[STOP]
//                            bit.
//                            0 Flash is not in stop mode.
//                            1 Flash is in stop mode.
//
// 0                  5   r   Reserved
//
// PGM                4   rw  Program.
//                            Used to set up Flash for a program operation.
//                            A 0 to 1 transition of PGM initiates an Flash
//                            program sequence. A 1 to 0 transition of PGM
//                            ends the program sequence. PGM can be set only
//                            under one of the following conditions:
//                            - User mode read (STOP and ERS are low).
//                            - Erase suspend 1 (ERS and ESUS are 1)
//                            with EHV low.
//                            PGM can be cleared by the user only when EHV
//                            is low and DONE is high. PGM is cleared on
//                            reset.
//                            0 Flash is not executing a program sequence.
//                            1 Flash is executing a program sequence.
//
// PSUS               3   rw  Program suspend. Indicates the Flash module is
//                            in program suspend or in the process of
//                            entering a suspend state. The Flash module is
//                            in program suspend when PSUS = 1 and DONE = 1.
//                            PSUS can be set high only when PGM and EHV are
//                            high. A 0 to 1 transition of PSUS starts the
//                            sequence which sets DONE and places the Flash
//                            in program suspend. PSUS can be cleared only
//                            when DONE and EHV are high. A 1 to 0 transition
//                            of PSUS with EHV = 1 starts the sequence which
//                            clears DONE and returns the Flash module to
//                            program. The Flash module cannot exit program
//                            suspend and clear DONE while EHV is low.
//                            PSUS is cleared on reset.
//                            0 Program sequence is not suspended.
//                            1 Program sequence is suspended.
//
// ERS                2   rw  Erase.
//                            Used to set up Flash for an erase operation.
//                            A 0 to 1 transition of ERS initiates an Flash
//                            erase sequence. A 1 to 0 transition of ERS ends
//                            the erase sequence. ERS can be set only in a
//                            normal operating mode read(STOP and PGM are
//                            low). ERS canbe cleared by the user only when
//                            ESUS and EHV are low and DONE is high. ERS is
//                            cleared on reset.
//                            0 Flash is not executing an erase sequence.
//                            1 Flash is executing an erase sequence.
//
// ESUS               1   rw  Erase suspend.
//                            Indicates that the Flash module is in erase
//                            suspend or in the process of entering a suspend
//                            state. The Flash module is in erase suspend
//                            when ESUS = 1 and DONE = 1. ESUS can be set
//                            high only when ERS and EHV are high and PGM is
//                            low. A 0 to 1 transition of ESUS starts the
//                            sequence which sets DONE and places the Flash
//                            in erase suspend. ESUS can be cleared only
//                            when DONE and EHV are high and PGM is low.
//                            A 1 to 0 transition of ESUS with EHV = 1 starts
//                            the sequence which clears DONE and returns the
//                            Flash module to erase. The Flash module cannot
//                            exit erase suspend and clear DONE while EHV
//                            is low. ESUS is cleared on reset.
//                            0 Erase sequence is not suspended.
//                            1 Erase sequence is suspended.
//
// EHV                0   rw  Enable high voltage.
//                            Enables the Flash module for a high voltage
//                            program/erase operation.EHV is cleared on
//                            reset. EHV must be set after an interlock write
//                            to start a program/erase sequence.EHV may be
//                            set, initiating a program/erase, after an
//                            interlock under one of the following conditions
//                            Erase (ERS = 1, ESUS = 0).
//                            Program (ERS = 0, ESUS = 0, PGM = 1, PSUS=0).
//                            Erase-suspended program (ERS = 1, ESUS = 1,
//                            PGM = 1, PSUS = 0).
//                            0 Flash is not enabled to perform a high
//                            voltage operation.
//                            1 Flash is enabled to perform a high voltage
//                            operation.
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//===========================================================================

typedef struct FLASH_MCR_F_Tag
{
   bitfield32_t  EDC     :  BIT_1;  // Bit  0 ECC Data Correction (Read/Clear)
   bitfield32_t          :  BIT_4;  // Bit  [1:4]  Reserved
   bitfield32_t  SIZE    :  BIT_3;  // Bits [5:7]
   bitfield32_t          :  BIT_1;  // Bit  8  Reserved
   bitfield32_t  LAS     :  BIT_3;  // Bits [9:11]
   bitfield32_t          :  BIT_3;  // Bits [12:14] Reserved
   bitfield32_t  MAS     :  BIT_1;  // Bits 15
   bitfield32_t  EER     :  BIT_1;  // Bit  16
   bitfield32_t  RWE     :  BIT_1;  // Bit  17
   bitfield32_t          :  BIT_2;  // Bits [18:19] Reserved
   bitfield32_t  PEAS    :  BIT_1;  // Bit  20
   bitfield32_t  DONE    :  BIT_1;  // Bit  21
   bitfield32_t  PEG     :  BIT_1;  // Bit  22
   bitfield32_t          :  BIT_4;  // Bits [23:26] Reserved
   bitfield32_t  PGM     :  BIT_1;  // Bit  27
   bitfield32_t  PSUS    :  BIT_1;  // Bit  28
   bitfield32_t  ERS     :  BIT_1;  // Bit  29
   bitfield32_t  ESUS    :  BIT_1;  // Bit  30
   bitfield32_t  EHV     :  BIT_1;  // Bit  31
}  FLASH_MCR_F_T;

typedef union FLASH_MCR_Tag
{
   FLASH_MCR_F_T   F;
   uint32_t        U32;
   uint16_t        U16[HW_ARRAY_SIZE_2];
}  FLASH_MCR_T;


//===========================================================================
// ID - Low/Mid Address Space Block Locking Register(FLASH_LMLR)
// Base Offset : 0x04
//
// Reset Value : 0x001F FFFF
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// LME               31   r   Low and mid address lock enable.
//                            Enables the locking register fields (SLOCK,
//                            MLOCK and LLOCK) to be set or cleared by
//                            register writes. This bit is a status bit only,
//                            and may not be written or cleared, and the
//                            reset value is 0. The method to set this bit
//                            to write a password, and if password matches,
//                            the LME bit will be set to reflect the status
//                            of enabled, and is enabled until a reset oper-
//                            ation occurs. For LME, the password 0xA1A1_1111
//                            must be written to the FLASH_LMLR.
//                            0 Low and mid address locks are disabled,
//                            and can not be modified.
//                            1 Low and mid address locks are enabled and
//                            can be written.
//
// 0            [30:21]   r   Reserved.
//
// SLOCK             20   rw  Shadow lock.
//                            Locks the shadow row from programs and erases.
//                            A value of 1 in the SLOCK bit signifies that
//                            the shadow row is locked for program and erase.
//                            A value of 0 in the SLOCK bit signifies that
//                            the shadow row is available to receive program
//                            and erase pulses. The SLOCK bit is not writable
//                            once an interlock write is completed or if a
//                            high voltage operation is suspended.Upon reset,
//                            information from the shadow row is loaded into
//                            the SLOCK bit. The SLOCK bit may be written as
//                            a register. Reset will cause bits to go back to
//                            their shadow row value. The default value of
//                            the SLOCK bit (assuming erased fuses) would
//                            be locked. SLOCK is not writable unless LME
//                            is high.
//                            0 Shadow row is available to receive program
//                            and erase pulses.
//                            1 Shadow row is locked for program and erase.
//
// 0            [19:18]   r   Reserved.
//
// MLOCK        [17:16]   rw  Mid address block lock.
//                            A value of 1 in a bit of the lock register
//                            signifies that the corresponding block is
//                            locked for program and erase. A value of 0 in
//                            the lock register signifies that the corresp-
//                            onding block is available to receive program
//                            and erase pulses. The lock register is not
//                            writable once an interlock write is completed
//                            or if a high voltage operation is suspended.
//                            Upon reset, information from the shadow row is
//                            loaded into the block registers. The LOCK bits
//                            may be written as a register. Reset will cause
//                            the bits to go back to their shadow row value.
//                            The default value of the LOCK bits (assuming
//                            erased fuses) would be locked.
//                            In the event that blocks are not present(due to
//                            configuration or total memory size), the LOCK
//                            bits will default to locked, and will not be
//                            writable. The reset value will always be 1
//                            (independent of the shadow row), and register
//                            writes will have no effect.
//                            MLOCK is not writable unless LME is high.
//
// 0            [15:6]   r    Reserved.
//
// LLOCK         [5:0]   rw   Low address block lock.
//                            These bits have the same description and
//                            attributes as MLOCK. As an example of how the
//                            LLOCK bits are used, if a configuration has 16
//                            16-Kbyte blocks in the low address space
//                            (MCR-LAS = 3'b011), the block residing at
//                            address Array Base + 0, will correspond to
//                            LLOCK0.The next 16-Kbyte block will correspond
//                            to LLOCK1, and so on up to LLOCK15.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================

typedef struct FLASH_LMLR_F_Tag
{
   bitfield32_t  LME    :  BIT_1;   // Bit  31
   bitfield32_t         :  BIT_10;  // Bits [30:21] Reserved
   bitfield32_t  SLK    :  BIT_1;   // Bit  20
   bitfield32_t         :  BIT_2;   // Bits [19:18] Reserved
   bitfield32_t  MLK    :  BIT_2;   // Bits [17:16]
   bitfield32_t         :  BIT_8;  // Bits [15:6] Reserved
   bitfield32_t  LLK    :  BIT_8;   // Bits [5:0]
}  FLASH_LMLR_F_T;

typedef union FLASH_LMLR_Tag
{
   FLASH_LMLR_F_T    F;
   uint32_t          U32;
   uint16_t          U16[HW_ARRAY_SIZE_2];
}  FLASH_LMLR_T;

//===========================================================================
// ID - High Address Space Block Locking Register (FLASH_HLR)
//  Base Offset : 0x08
//
// Reset Value : 0x0FFF FFFF
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// HBE               31   r   High address lock enable.
//                            Enables the locking field (HBLOCK) to be set
//                            or cleared by register writes. This bit is a
//                            status bit only, and may not be written or
//                            cleared, and the reset value is 0. The method
//                            to set this bit is to provide a password, and
//                            if the password matches, the HBE bit will be
//                            set to reflect the status of enabled, and is
//                            enabled until a reset operation occurs.For HBE,
//                            the password 0xB2B2_2222 must be written to
//                            FLASH_HLR.
//                            0 High address locks are disabled, and can not
//                            be modified.
//                            1 High address locks are enabled to be written.
//
// 0            [30:12]   r   Reserved
//
// HBLOCK        [11:0]   rw  High address space block lock. Has the same
//                            characteristics as MLOCK.The block numbering
//                            for High Address space starts with HBLOCK[0]
//                            and continues until all blocks are accounted.
//                            HBLOCK is not writable unless HBE is set.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================

typedef struct FLASH_HLR_F_Tag
{
   bitfield32_t  HBE   :  BIT_1;   // Bit 31
   bitfield32_t        :  BIT_27;  // Bits [30:12] Reserved
   bitfield32_t  HLK   :  BIT_4;  // BitS [11:0]
}  FLASH_HLR_F_T;

typedef union FLASH_HLR_Tag
{
   FLASH_HLR_F_T      F;
   uint32_t           U32;
}  FLASH_HLR_T;

//===========================================================================
// ID - Secondary Low/Mid Address Space Block Locking Register(FLASH_SLMLR)
//   Base Offset : 0x0C
//
// Reset Value : 0x001F FFFF
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// SLE               31   r   Secondary low and mid address lock enable.
//                            Enables the secondary lock fields (SSLOCK,
//                            SMLOCK and SLLOCK) to be set or cleared by
//                            register writes. This bit is a status bit only,
//                            and may not be written or cleared, and the
//                            reset value is 0. The method to set this bit
//                            is to provide a password, and if the password
//                            matches, the SLE bit will be set to reflect
//                            the status of enabled, and is enabled until a
//                            reset operation occurs.For SLE, the password
//                            0xC3C3_3333 must be written to the FLASH_SLMLR.
//                            0 Secondary Low and Mid Address Locks are dis-
//                            abled, and can not be modified.
//                            1 Secondary Low and Mid Address Locks are enab
//                            led to be written.
//
// 0            [30:21]   r   Reserved
//
// SSLOCK          20     rw  Secondary shadow lock
//                            An alternative method that may be used to lock
//                            the shadow row from programs and erases.
//                            Low/Mid Address Space Block Locking Register
//                            (FLASH_LMLR).SSLOCK is not writable unless SLE
//                            is high.
//
// 0            [19:18]   r   Reserved
//
// SMLOCK       [17:16]   rw   Secondary mid address block lock. Alternative
//                            method that may be used to lock the mid
//                            address space blocks from programs and erases.
//                            Low/Mid Address Space Block Locking Register
//                            (FLASH_LMLR).SMLOCK is not writable unless
//                            SLE is set.
//
// 0            [15:6]   r    Reserved
//
// SLLOCK        [5:0]   rw   Secondary Low Address Block Lock
//                            These bits are an alternative method that may
//                            be used to lock the low address space blocks
//                            from programs and erases.
//                            SLLOCK is not writable unless SLE is high.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================

typedef struct FLASH_SLMLR_F_Tag
{
   bitfield32_t  SLE     :  BIT_1;   // Bit  31
   bitfield32_t          :  BIT_10;  // Bits [30:21] Reserved
   bitfield32_t  SSLK    :  BIT_1;   // Bit  20
   bitfield32_t          :  BIT_2;   // Bits [19:18] Reserved
   bitfield32_t  SMK     :  BIT_2;   // Bits [17:16]
   bitfield32_t          :  BIT_8;  // Bits [15:6] Reserved
   bitfield32_t  SLK     :  BIT_8;   // Bits [5:0]
}  FLASH_SLMLR_F_T;

typedef union FLASH_SLMLR_Tag
{
   FLASH_SLMLR_F_T    F;
   uint32_t           U32;
   uint16_t           U16[HW_ARRAY_SIZE_2];
}  FLASH_SLMLR_T;

//===========================================================================
// ID - Low/Mid Address Space Block Select Register (FLASH_LMSR)
//   Base Offset : 0x10
//
// Reset Value : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:18]   r   Reserved
//
// MSEL         [17:16]   rw  Mid address space block select.
//                            A value of 1 in the select register signifies
//                            that the block is selected for erase. A value
//                            of 0 in the select register signifies that the
//                            block is not selected. The reset value for the
//                            select registers is 0, or unselected.The blocks
//                            must be selected (or unselected) before doing
//                            an erase interlock write as part of the erase
//                            sequence. The select register is not writable
//                            once an interlock write is completed or if a
//                            high voltage operation is suspended. In the
//                            event that blocks are not present (due to con-
//                            figuration or total memory size), the corresp-
//                            onding SELECT bits will default to unselected,
//                            and will not be writable. The reset value will
//                            always be 0, and register writes will have
//                            no effect.
//
// 0            [15:6]   r    Reserved
//
// LSEL          [5:0]    rw  Low address space block select.
//                            Used to select blocks in the low address space,
//                            and have the same description and attributes
//                            as the MSEL bits
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_LMSR_F_Tag
{
   bitfield32_t  LSE    :  BIT_1;  // Bits [31:18] Reserved
   bitfield32_t         :  BIT_13; // Bits [31:18] Reserved
   bitfield32_t  MSEL   :  BIT_2;  // Bits [17:16]
   bitfield32_t         :  BIT_8;  // Bits [15:6] Reserved
   bitfield32_t  LSEL   :  BIT_8;  // Bits [5:0]
}  FLASH_LMSR_F_T;

typedef union FLASH_LMSR_Tag
{
   FLASH_LMSR_F_T    F;
   uint32_t          U32;
   uint16_t          U16[HW_ARRAY_SIZE_2];
}  FLASH_LMSR_T;

//===========================================================================
// ID - High Address Space Block Select Register (FLASH_HSR)
//   Base Offset : 0x14
//
// Reset Value : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:12]   r   Reserved
//
// HBSEL        [11:0]   rw   High address space block select.
//                            A value of 1 in the select register signifies
//                            that the block is selected for erase. A value
//                            of 0 in the select register signifies that the
//                            block is not selected. The reset value for the
//                            select registers is 0, or unselected.The blocks
//                            must be selected (or unselected) before doing
//                            an erase interlock write as part of the erase
//                            sequence. The select register is not writable
//                            once an interlock write is completed or if a
//                            high voltage operation is suspended. In the
//                            event that blocks are not present (due to con-
//                            figuration or total memory size), the corresp-
//                            onding SELECT bits will default to unselected,
//                            and will not be writable. The reset value will
//                            always be 0, and register writes will have
//                            no effect.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_HSR_F_Tag
{
   bitfield32_t         :  BIT_28;  // Bits [31:12] Reserved
   bitfield32_t  HBSEL  :  BIT_4;  // Bits [11:0]
}  FLASH_HSR_F_T;

typedef union FLASH_HSR_Tag
{
   FLASH_HSR_F_T    F;
   uint32_t         U32;
}  FLASH_HSR_T;

//===========================================================================
// ID - Address Register (FLASH_AR)
//   Base Offset : 0x18
//
// Reset Value : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:22]   r   Reserved
//
// ADDR1         [21:3]   r   Double word address of first failing address
//                            in the event of an ECC error, or the address
//                            of a failure occuring during state machine
//                            operation.
//
/// 0           [2:0]     r   Reserved
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_AR_F_Tag
{
   bitfield32_t  SAD    :  BIT_1; // Bits [31:20] Shadow address
   bitfield32_t         :  BIT_10; // Bits [31:20] Reserved
   bitfield32_t  ADDR   :  BIT_18; // Bits [21:3]
   bitfield32_t         :  BIT_3;  // Bits [2:0] Reserved
}  FLASH_AR_F_T;

typedef union FLASH_AR_Tag
{
   FLASH_AR_F_T    F;
   uint32_t        U32;
}  FLASH_AR_T;


//===========================================================================
// ID - Address Register (FLASH_UT0)
//   Base Offset : 0x3c
//===========================================================================
typedef struct FLASH_UT0_F_Tag
{
   bitfield32_t  UTE   :  BIT_1; // Bits [31:20] User test enable (Read/Clear)
   bitfield32_t  SBCE  :  BIT_1; // Single bit correction enable (Read/Clear)
   bitfield32_t        :  BIT_6; // Bits [21:3]
   bitfield32_t  DSI   :  BIT_8; // Bits [2:0] Data syndrome input (Read/Write)
   bitfield32_t        :  BIT_10;// Bits [21:3]
   bitfield32_t  MRE   :  BIT_1; // Bits [21:3] Margin Read Enable (Read/Write)
   bitfield32_t  MRV   :  BIT_1; // Bits [21:3] Margin Read Value (Read/Write)
   bitfield32_t  EIE   :  BIT_1; // Bits [21:3] ECC data Input Enable (Read/Write)
   bitfield32_t  AIS   :  BIT_1; // Bits [21:3] Array Integrity Sequence (Read/Write)
   bitfield32_t  AIE   :  BIT_1; // Bits [21:3] Array Integrity Enable (Read/Write)
   bitfield32_t  AID   :  BIT_1; // Bits [21:3] Array Integrity Done (Read Only)

}  FLASH_UT0_F_T;

typedef union FLASH_UT0_Tag
{
   FLASH_UT0_F_T    F;
   uint32_t        U32;
}  FLASH_UT0_T;


//===========================================================================
// ID - Flash Bus Interface Unit Control Register (FLASH_BIUCR)
//   Base Offset : 0x1C
//
// Reset Value : 0x0000 FF00
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:21]   r   Reserved
//
// MnPFE        [20:16]   rw  Master n prefetch enable.
//                            Used to control whether prefetching may be
//                            triggered based on the master ID of a request-
//                            ing master. These bits are cleared by hardware
//                            reset.
//                            0 No prefetching may be triggered by this
//                            master
//                            1 Prefetching may be triggered by this master
//                            These fields are identified as follows:
//                            M0PFE= e500z6 core
//                            M1PFE= Nexus
//                            M2PFE= eDMA
//                            M3PFE= EBI
//
// APC          [15:13]   rw  Address pipelining control.
//                            Used to control the number of cycles between
//                            pipelined access requests. This field must be
//                            set to a value corresponding to the operating
//                            frequency of the FBIU.
//                            000 Reserved
//                            001 Access requests require one hold cycle
//                            010 Access requests require two hold cycles
//                             :
//                            110 Access requests require 6 hold cycles
//                            111 No address pipelining
//
// WWSC         [12:11]   rw  Write wait state control.
//                            Used to control the timing for array writes.
//                            This field must be set to a value correspond-
//                            ing to the operating frequency of the FBIU.
//                            00 Reserved
//                            01 One wait state
//                            10 Two wait states
//                            11 Three wait states
//
// RWSC          [10:8]   rw  Read wait state control.
//                            Used to control the Flash array access time
//                            for array reads. This field must be set to a
//                            value corresponding to the operating frequency
//                            of the FBIU.
//                            000 Zero wait states
//                            001 One wait state
//                             :
//                            111 Seven wait states
//
// DPFEN          [7:6]   rw  Data prefetch enable.
//                            Enables or disables prefetching initiated by
//                            a data read access.This field is cleared by
//                            hardware reset.
//                            00 No prefetching is triggered by a data read
//                            access
//                            01 Prefetching may be triggered only by a data
//                            burst read access
//                            10 Reserved
//                            11 Prefetching may be triggered by any data
//                            read access
//
// IPFEN          [5:4]   rw  Instruction prefetch enable.
//                            Enables or disables prefetching initiated by
//                            an instruction read access.
//                            This field is cleared by hardware reset.
//                            00 No prefetching is triggered by an instruct-
//                            ion read access
//                            01 Prefetching may be triggered only by an
//                            instruction burst read access
//                            10 Reserved
//                            11 Prefetching may be triggered by any
//                            instruction read access
//
// PFLIM          [3:1]   rw  Prefetch limit. Controls the prefetch algor-
//                            ithm used by the FBIU prefetch controller.
//                            This field defines a limit on the maximum num-
//                            ber of sequential prefetches which will be
//                            attempted between buffer misses.
//                            This field is cleared by hardware reset.
//                            000 No prefetching is performed
//                            001 A single additional line (next sequential)
//                            is prefetched on a buffer miss 
//                            010 Up to two additional lines may be
//                            prefetched following each buffer miss before
//                            prefetching is halted. A single additional line
//                            (next sequential)is prefetched on a buffer miss
//                            and the next sequential line is prefetched on
//                            a buffer hit (if not already present).
//                            011 Up to three additional lines may be
//                            prefetched following each buffer miss before
//                            prefetching is halted. Only a single additional
//                            prefetch is initiated after each buffer hit
//                            or miss.
//                            100 Up to four additional lines may be prefet-
//                            ched following each buffer miss before prefetch
//                            is halted. Only a single additional prefetch is
//                            initiated after each buffer hit or miss.
//                            101 Up to five additional lines may be prefetch
//                            following each buffer miss before prefetching
//                            is halted. Only a single additional prefetch is
//                            initiated after each buffer hit or miss.
//                            110 An unlimited number of additional lines may
//                            be prefetched following each buffer miss.
//                            Only a single additional prefetch is initiated
//                            on each buffer hit or miss.
//                            111 Reserved
//
// BFEN               0   rw  FBIU line read buffers enable.
//                            Enables or disables line read buffer hits.
//                            It is also used to invalidate the buffers.These
//                            bits are cleared by hardware reset.
//                            0 The line read buffers are disabled from
//                            satisfying read requests, and all buffer valid
//                            bits are cleared.
//                            1 The line read buffers are enabled to satisfy
//                            read requests on hits. Buffer valid bits may
//                            be set when buffers are successfully filled.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_BIUCR_F_Tag
{
   bitfield32_t         :  BIT_7;  // Bits [31:25] Reserved
   bitfield32_t  GCE    :  BIT_1 ; // Bits  24
   bitfield32_t         :  BIT_4; // Bits [23:20] Reserved
   bitfield32_t  M3PFE  :  BIT_1 ; // Bits  19
   bitfield32_t  M2PFE  :  BIT_1;  // Bits  18
   bitfield32_t  M1PFE  :  BIT_1;  // Bits  17
   bitfield32_t  M0PFE  :  BIT_1;  // Bit   16
   bitfield32_t  APC    :  BIT_3;  // Bits [15:13]
   bitfield32_t  WWSC   :  BIT_2;  // Bits [12:11]
   bitfield32_t  RWSC   :  BIT_3;  // Bits [10:8]
   bitfield32_t         :  BIT_1;  // Bits   7 Reserved
   bitfield32_t  DPFEN  :  BIT_1;  // Bits   6
   bitfield32_t         :  BIT_1;  // Bits   5 Reserved
   bitfield32_t  IPFEN  :  BIT_1;  // Bits   4
   bitfield32_t         :  BIT_1;  // Bits   3 Reserved
   bitfield32_t  PFLIM  :  BIT_2;  // Bits [2:1]
   bitfield32_t  BFEN   :  BIT_1;  // Bit   0
}  FLASH_BIUCR_F_T;

typedef union FLASH_BIUCR_Tag
{
   FLASH_BIUCR_F_T    F;
   uint32_t          U32;
   uint16_t          U16[HW_ARRAY_SIZE_2];
}  FLASH_BIUCR_T;

//===========================================================================
// ID - Flash Bus Interface Unit Access Protection Register(FLASH_BIUAPR)
//   Base Offset : 0x20
//
// Reset Value : 0x0000 FF00
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0             [31:10]   r   Reserved
//
// MnAP[1:0]      [9:0]   rw  Master n access protection.
//                            Controls whether read and write accesses to
//                            the Flash are allowed based on the master ID
//                            of a requesting master. These fields are
//                            initialized by hardware reset.
//                            00 No accesses may be performed by this master
//                            01 Only read accesses may be performed by this
//                            master
//                            10 Only write accesses may be performed by this
//                            master
//                            11 Read and write accesses may be performed
//                            by this master
//                            These fields are identified as follows:
//                            M0AP= e500z6 core
//                            M1AP= Nexus
//                            M2AP= eDMA
//                            M3AP= EBI
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_BIUAPR_F_Tag
{
   bitfield32_t         :  BIT_24; // Bits [31:8] Reserved
   bitfield32_t  M3AP   :  BIT_2 ; // Bits [7:6]
   bitfield32_t  M2AP   :  BIT_2 ; // Bits [5:4]
   bitfield32_t  M1AP   :  BIT_2 ; // Bits [3:2]
   bitfield32_t  M0AP   :  BIT_2 ; // Bits [1:0]
}  FLASH_BIUAPR_F_T;

typedef union FLASH_BIUAPR_Tag
{
   FLASH_BIUAPR_F_T    F;
   uint32_t          U32;
}  FLASH_BIUAPR_T;

//===========================================================================
//  Enumeration: Access Protection(MnAP)
//
//  MnAP[1:0] Meaning of Value
//  ========= ===============================================================
//         00  No accesses may be performed by this maste
//         01  Only read accesses may be performed by this master
//         10  Only write accesses may be performed by this master
//         11  Read and write accesses may be performed by this master
//===========================================================================
typedef enum FLASH_BIUAPR_MASTER_AP_Tag
{
   FLASH_BIUCR_MASTER_AP_NO_ACCESS,
   FLASH_BIUCR_MASTER_AP_READ_ACCESS_ONLY,
   FLASH_BIUCR_MASTER_AP_WRITE_ACCESS_ONLY,
   FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS
}  FLASH_BIUAPR_MASTER_AP_T;

//===========================================================================
//  FLASH Module Register Structure
//===========================================================================

typedef volatile struct FLASHB0_Tag
{
   FLASH_MCR_T        MCR;                         //0x00 - 0x03 @0xC3F8_8000
   FLASH_LMLR_T       LML;                         //0x04 - 0x07
   FLASH_HLR_T        HBL;                         //0x08 - 0x0B
   FLASH_SLMLR_T      SLL;                         //0x0C - 0x0F
   FLASH_LMSR_T       LMS;                         //0x10 - 0x13
   FLASH_HSR_T        HBS;                         //0x14 - 0x17
   FLASH_AR_T         ADR;                         //0x18 - 0x1B

   FLASH_BIUCR_T      BIUCR;                          //0x1C - 0x1F
   FLASH_BIUAPR_T     BIUAPR;                         //0x20 - 0x23
   uint32_t           BIUCR2;                         //0x24 - 0x27
   uint32_t           PFCR3;                          //0x28 - 0x2B
   uint8_t            Reserved1[0x10];                         //0x2c - 0x3b

   FLASH_UT0_T        UT0;                         //0x3C - 0x3F
   uint32_t           UT1;                         //0x40 - 0x43
   uint32_t           UT2;                         //0x44 - 0x47
   uint32_t           UMISR0;                      //0x48 - 0x4b
   uint32_t           UMISR1;                      //0x4c - 0x4f
   uint32_t           UMISR2;                      //0x50 - 0x53
   uint32_t           UMISR3;                      //0x54 - 0x57
   uint32_t           UMISR4;                      //0x58 - 0x5b @0xC3F8_805B

}  FLASHB0_T;


typedef volatile struct FLASHB1_Tag
{
   FLASH_MCR_T        MCR;                         //0x00 - 0x03
   FLASH_LMLR_T       LML;                         //0x04 - 0x07
   FLASH_HLR_T        HBL;                         //0x08 - 0x0B
   FLASH_SLMLR_T      SLL;                         //0x0C - 0x0F
   FLASH_LMSR_T       LMS;                         //0x10 - 0x13
   FLASH_HSR_T        HBS;                         //0x14 - 0x17
   FLASH_AR_T         ADR;                         //0x18 - 0x1B

   uint8_t            Reserved1[0x20];                //0x1c - 0x3b

   uint32_t           UT0;                         //0x3C - 0x3F
   uint32_t           UT1;                         //0x40 - 0x43
   uint32_t           UT2;                         //0x44 - 0x47
   uint32_t           UMISR0;                      //0x48 - 0x4b
   uint32_t           UMISR1;                      //0x4c - 0x4f
   uint32_t           UMISR2;                      //0x50 - 0x53
   uint32_t           UMISR3;                      //0x54 - 0x57
   uint32_t           UMISR4;                      //0x58 - 0x5b

}  FLASHB1_T;

#endif // HW_FLASH_H

