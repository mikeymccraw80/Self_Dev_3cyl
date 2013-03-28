#ifndef HW_FLASH_MPC5644_H
#define HW_FLASH_MPC5644_H


#include "reuse.h"

#define HW_ARRAY_SIZE_2 (2)

//w1c Bit Masks
#define FLASH_EER_CLEAR_MASK  (0xFFFF9FFF)
#define FLASH_RWE_CLEAR_MASK  (0xFFFF5FFF)
#define FLASH_SBC_CLEAR_MASK  (0xFFFF3FFF)

#define FLASH_RESERVED_0x14 (0x14)
#define FLASH_RESERVED_0x04 (0x04)
#define FLASH_RESERVED_0x3FA4 (0x3FA4)
#define FLASH_USER_MULTIPLE_SIGNATURE (0x04)
//===========================================================================
// ID - Module Configuration Register (FLASH_MCR)
//
// Base Offset : 0x0000 0000
//
// Reset Value : 0x0360 0200
//
// Field        Bits     Type Description
//============= ======== ==== ===============================================
// 0            [31:27]   r   Reserved
//
// SIZE[3:0]    [26:24]   r   Array space size. Dependent upon the size of
//                            the Flash module. All possible values of SIZE
//                            and the configuration to which each value
//                            corresponds are shown below
//                            000 128 KB (Only LAS option for this size 
//                                is LAS = 2, and consists of two 16 KB 
//                                and two 48 KB blocks,128 KB of LAS 
//                                available, and no MAS or HAS available)
//                            001 256 KB (Only LAS option for this size is 
//                                LAS = 1, and LAS = 2, no MAS or HAS available)
//                            010 512 KB (Any LAS or MAS option is available, no
//                                HAS available)
//                            011 1.0 MB (256 KB of LAS, 256 KB of MAS, and 512
//                                KB of HAS)
//                            100 1.5 MB (256 KB of LAS, 256 KB of MAS, and 1 MB
//                                of HAS)
//                            101 2.0 MB (256 KB of LAS, 256 KB of MAS, and 1.5
//                                 MB of HAS)
//                            110 Reserved
//                            111 Reserved
//
// 0                 23   r   Reserved
//
// LAS[2:0]     [22:20]   r   Low address space.
//                            Corresponds to the configuration of the low
//                            address space. All possible values of LAS and
//                            the configuration to which each value corres-
//                            ponds are shown below.
//                            000 One 256 KB Blocks
//                            001 Two 128 KB Blocks
//                            010 Four 16 KB, four 48 KB Blocks
//                            011 Reserved
//                            100 Eight 16 KB, two 64 KB Blocks
//                            101 Reserved
//                            110 Two 16 KB, two 48 KB, two 64 KB Blocks
//                            111 Reserved
//
// 0            [19:17]   r   Reserved
//
// MAS               16   r   Mid address space size. Corresponds to the
//                            configuration of the mid address space.
//                            MAS is read only. The value of the parameter
//                            for this device is shown in bold.
//                            Note: The MAS encoding for the MPC5554 is 0.
//                            0 Two 128-Kbyte blocks are available
//                            1 One 256 KB Blocks (Only available if LAS = 0)
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
// SBC               13   rw Single Bit Correction. SBC provides 
//                            information on previous reads provided the 
//                            UT0[SPCE] is set. If a single bit correction 
//                            occurred, the SBC bit is set to a 1. This bit 
//                            must then be cleared, or a reset must occur
//                            before this bit returns to a 0 state. If SBC 
//                            is not set, or remains 0, this indicates that 
//                            all previous reads (from the last reset, or 
//                            clearing of SBC) did not require a correction. 
//                            Since this bit is an error flag, it must be 
//                            cleared to a 0 by writing a 1 to the register 
//                            location. A write of 0 has no effect.
//                            0 Reads are occurring without corrections
//                            1 A Single Bit Correction occurred during a 
//                               previous read.
//
// 0                   12   r   Reserved
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
// 0               [8:5]   r   Reserved
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
   bitfield32_t          :  BIT_5;  // Bit  [31:27] Reserved
   bitfield32_t  SIZE    :  BIT_3;  // Bits [26:24]
   bitfield32_t          :  BIT_1;  // Bit  23  Reserved
   bitfield32_t  LAS     :  BIT_3;  // Bits [22:20]
   bitfield32_t          :  BIT_3;  // Bits [19:17] Reserved
   bitfield32_t  MAS     :  BIT_1;  // Bits 16
   bitfield32_t  EER     :  BIT_1;  // Bit  15
   bitfield32_t  RWE     :  BIT_1;  // Bit  14
   bitfield32_t  SBC     :  BIT_1;  // Bit  13
   bitfield32_t          :  BIT_1;  // Bits 12 Reserved
   bitfield32_t  PEAS    :  BIT_1;  // Bit  11
   bitfield32_t  DONE    :  BIT_1;  // Bit  10
   bitfield32_t  PEG     :  BIT_1;  // Bit  9
   bitfield32_t          :  BIT_4;  // Bit  [8:5]  Reserved
   bitfield32_t  PGM     :  BIT_1;  // Bit  4
   bitfield32_t  PSUS    :  BIT_1;  // Bit  3
   bitfield32_t  ERS     :  BIT_1;  // Bit  2
   bitfield32_t  ESUS    :  BIT_1;  // Bit  1
   bitfield32_t  EHV     :  BIT_1;  // Bit  0
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
// Reset Value : 0x001F 03FF
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
// 0            [15:10]   r    Reserved.
//
// LLOCK         [9:0]   rw   Low Address Space Block Lock. A value of 1 in a 
//                            bit of the lock register signifies that the 
//                            corresponding block is locked for program and 
//                            erase. A value of 0 in the lock register 
//                            signifies that the corresponding block is 
//                            available to receive program and erase pulses.
//                            The block numbering for Low Address Space starts
//                            with LLOCK[0] and continues until all blocks are
//                            accounted.For more details on LLOCK, please see 
//                            MLOCK bit description.LLOCK is not writable 
//                            unless LME is high.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================

typedef struct FLASH_LMLR_F_Tag
{
   bitfield32_t  LME    :  BIT_1;   // Bit  31
   bitfield32_t         :  BIT_10;  // Bits [30:21] Reserved
   bitfield32_t  SLOCK  :  BIT_1;   // Bit  20
   bitfield32_t         :  BIT_2;   // Bits [19:18] Reserved
   bitfield32_t  MLOCK  :  BIT_2;   // Bits [17:16]
   bitfield32_t         :  BIT_6;   // Bits [15:10] Reserved
   bitfield32_t  LLOCK  :  BIT_10;  // Bits [9:0]
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
// Reset Value : 0x0000 003F
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
// 0            [30:6]   r   Reserved
//
// HBLOCK        [5:0]   rw   High address space block lock. Has the same
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
   bitfield32_t        :  BIT_25;  // Bits [30:6]   Reserved
   bitfield32_t  HLOCK :  BIT_6;   // BitS [5:0]
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
// Reset Value : 0x0013 03FF
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
//                            SLE is High.
//
// 0            [15:10]   r    Reserved
//
// SLLOCK        [9:0]   rw   Secondary Low Address Block Lock
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
   bitfield32_t  SSLOCK  :  BIT_1;   // Bit  20
   bitfield32_t          :  BIT_2;   // Bits [19:18] Reserved
   bitfield32_t  SMLOCK  :  BIT_2;   // Bits [17:16]
   bitfield32_t          :  BIT_6;   // Bits [15:10] Reserved
   bitfield32_t  SLLOCK  :  BIT_10;  // Bits [9:0]
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
// 0            [15:10]   r    Reserved
//
// LSEL          [9:0]    rw  Low address space block select.
//                            Used to select blocks in the low address space,
//                            and have the same description and attributes
//                            as the MSEL bits
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_LMSR_F_Tag
{
   bitfield32_t         :  BIT_14;  // Bits [31:18] Reserved
   bitfield32_t  MSEL   :  BIT_2;   // Bits [17:16]
   bitfield32_t         :  BIT_6;   // Bits [15:10] Reserved
   bitfield32_t  LSEL   :  BIT_10;  // Bits [9:0]
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
// 0            [31:6]   r   Reserved
//
// HBSEL        [5:0]   rw   High address space block select.
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
   bitfield32_t         :  BIT_26;  // Bits [31:6] Reserved
   bitfield32_t  HBSEL  :  BIT_6;   // Bits [5:0]
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
// SAD         31         r   Shadow Address. The SAD bit qualifies 
//                             the address captured during an ECC Event 
//                             Error, Single Bit Correction, or State Machine
//                             operation. The SAD register is not writable
//                             0 Address Captured is from Main Array Space
//                             1 Address Captured is from Shadow Array Space
// 
// 0            [30:18]   r   Reserved
//
// ADDR         [17:3]   r   Double word address of first failing address
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
   bitfield32_t  SAD   :  BIT_1;  // Bits 31
   bitfield32_t        :  BIT_13; // Bits [30:18] Reserved
   bitfield32_t  ADDR  :  BIT_15; // Bits [17:3]
   bitfield32_t        :  BIT_3;  // Bits [2:0] Reserved
}  FLASH_AR_F_T;

typedef union FLASH_AR_Tag
{
   FLASH_AR_F_T    F;
   uint32_t        U32;
}  FLASH_AR_T;

//===========================================================================
// ID - Platform Flash Configuration Register 1 (BIUCR1)
//   Base Offset : 0x1C
//
// Reset Value : 0x0000 FF00
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:23]   r   Reserved
// 0              21      r   Reserved
// 0             [19:18]  r   Reserved
// 
// M6PFE        22      rw    Master n prefetch enable.
// M4PFE        20            Used to control whether prefetching may be
// M1PFE        17            triggered based on the master ID of a request-
// M0PFE        16            ing master. These bits are cleared by hardware
//                            reset.
//                            0 No prefetching may be triggered by this
//                            master
//                            1 Prefetching may be triggered by this master
//                            These fields are identified as follows:
//                            M0PFE = z4 Core Instruction
//                            M1PFE = z4 Core Load/Store
//                            M4PFE = eDMA
//                            M6PFE =FlexRay
//                            M7PFE =Z7 Nexus
//
// APC          [15:13]   rw  Address pipelining control.
//                            Used to control the number of cycles between
//                            pipelined access requests. This field must be
//                            set to a value corresponding to the operating
//                            frequency of the FBIU.
//                            000 Accesses may be pipelined back-to-back
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
//                            00 No additional wait-states are added
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
// 0                    7    r  Reserved
//
// DPFEN             6   rw  Data prefetch enable.
//                            Enables or disables prefetching initiated by
//                            a data read access.This field is cleared by
//                            hardware reset.
//                            0 No prefetching is triggered by a data read
//                            access 
//                            1 Prefetching may be triggered by any data
//                            read access
//
// 0                5       r  Reserved
//
// IPFEN          4      rw  Instruction prefetch enable.
//                            Enables or disables prefetching initiated by
//                            an instruction read access.
//                            This field is cleared by hardware reset.
//                            0 No prefetching is triggered by an instruct-
//                            ion read access
//                            1 Prefetching may be triggered by any
//                            instruction read access
//
// 0                   3     r  Reserved
//
// PFLIM          [2:1]   rw  Prefetch limit. Controls the prefetch algor-
//                            ithm used by the FBIU prefetch controller.
//                            This field defines a limit on the maximum num-
//                            ber of sequential prefetches which will be
//                            attempted between buffer misses.
//                            This field is cleared by hardware reset.
//                            00 No prefetching is performed
//                            01 The referenced line is prefetched on a 
//                            buffer miss, i.e., prefetch on miss
//                            1x The referenced line is prefetched on a 
//                            buffer miss, or the next sequential line is 
//                            prefetched on a buffer hit (if not already 
//                            present), i.e., prefetch on miss or hit.
//
// BFEN               0   rw  PFlash line read buffers enable.
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
typedef struct FLASH_BIUCR1_F_Tag
{
   bitfield32_t         :  BIT_7;  // Bits  [31:25] Reserved
   bitfield32_t         :  BIT_1;  // Bits  24
   bitfield32_t         :  BIT_1;  // Bits  23 Reserved
   bitfield32_t  M6PFE  :  BIT_1;  // Bits  22
   bitfield32_t         :  BIT_1;  // Bits  21 Reserved
   bitfield32_t  M4PFE  :  BIT_1;  // Bits  20
   bitfield32_t         :  BIT_2;  // Bit   [19:18] Reserved
   bitfield32_t  M1PFE  :  BIT_1;  // Bits  17
   bitfield32_t  M0PFE  :  BIT_1;  // Bit   16
   bitfield32_t  APC    :  BIT_3;  // Bits  [15:13]
   bitfield32_t  WWSC   :  BIT_2;  // Bits  [12:11]
   bitfield32_t  RWSC   :  BIT_3;  // Bits  [10:8]
   bitfield32_t         :  BIT_1;  // Bit   7
   bitfield32_t  DPFEN  :  BIT_1;  // Bit   6
   bitfield32_t         :  BIT_1;  // Bit   5
   bitfield32_t  IPFEN  :  BIT_1;  // Bit   4
   bitfield32_t         :  BIT_1;  // Bit   3
   bitfield32_t  PFLIM  :  BIT_2;  // Bits  [2:1]
   bitfield32_t  BFEN   :  BIT_1;  // Bit   0
}  FLASH_BIUCR1_F_T;

typedef union FLASH_BIUCR1_Tag
{
   FLASH_BIUCR1_F_T    F;
   uint32_t          U32;
   uint16_t          U16[HW_ARRAY_SIZE_2];
}  FLASH_BIUCR1_T;

//===========================================================================
// ID - Platform Flash Access Protection Register(FLASH_PFAPR)
//   Base Offset : 0x20
//
// Reset Value : 0xFFFF FFFF
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0             [31:18]   r   Reserved
// 0             [15:14]   r   Reserved
// 0             [7:2]     r   Reserved 
//
// M0AP[1:0]         rw       Master n access protection.
// M4AP[9:8]                  Controls whether read and write accesses to
// M5AP[11:10]                the Flash are allowed based on the master ID
// M6AP[13:12]                of a requesting master. These fields are
// M8AP[17:16]                initialized by hardware reset.
//                            00 No accesses may be performed by this master
//                            01 Only read accesses may be performed by this
//                            master
//                            10 Only write accesses may be performed by this
//                            master
//                            11 Read and write accesses may be performed
//                            by this master
//                            These fields are identified as follows:
//                            M0AP= MCU core
//                            M1AP= Core load/store
//                            M4AP= eDMA
//                            M6AP= FlexRay
//                            M8AP= Z7 Nexus
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_BIUAPR_F_Tag
{
   bitfield32_t         :  BIT_14; // Bits [31:18] Reserved
   bitfield32_t         :  BIT_2;  // Bits [17:16]
   bitfield32_t         :  BIT_2;  // Bits [15:14] Reserved
   bitfield32_t  M6AP   :  BIT_2;  // Bits [13:12]
   bitfield32_t         :  BIT_2;  // Bits [11:10]
   bitfield32_t  M4AP   :  BIT_2;  // Bits [9:8]
   bitfield32_t         :  BIT_4;  // Bits [7:4] Reserved
   bitfield32_t  M1AP   :  BIT_2;  // Bits [3:2]
   bitfield32_t  M0AP   :  BIT_2;  // Bits [1:0]
   
}  FLASH_BIUAPR_F_T;

typedef union FLASH_BIUAPR_Tag
{
   FLASH_BIUAPR_F_T    F;
   uint32_t          U32;
}  FLASH_BIUAPR_T;

//===========================================================================
// ID - Platform Flash Configuration Register 2 (BIUCR2)
//   Base Offset : 0x24
//
// Reset Value : 0xC000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// LBCFG    [31:30]   rw  Line Buffer Configuration. This field controls 
//                            the configuration of all the line buffers in the 
//                            PFLASH controller.The buffers can be organized 
//                            as a ¡°pool¡± of available resources, or with a 
//                            fixed partition between instruction and data 
//                            buffers. This field controls the configuration 
//                            of both the 4 x 128 and 4 x 256 line buffers
//                            00 All four buffers are available for any flash 
//                            access, i.e., there is no partitioning of the 
//                            buffers based on the access type.
//                            01 Reserved
//                            10 The buffers are partitioned into two groups 
//                            with buffers 0 and 1 allocated for instruction 
//                            fetches and buffers 2 and 3 for data accesses.
//                            11 The buffers are partitioned into two groups 
//                            with buffers 0,1,2 allocated for instruction 
//                            fetches and buffer 3 for data accesses.
//
// 0             [29:0]   r   Reserved
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_BIUCR2_F_Tag
{
    bitfield32_t  LBCFG   :  BIT_2;  // Bits [31:30]
    bitfield32_t          :  BIT_30; // Bits [29:0]
    
} FLASH_BIUCR2_F_T;

typedef union FLASH_BIUCR2_Tag
{
   FLASH_BIUCR2_F_T    F;
   uint32_t          U32;
}  FLASH_BIUCR2_T;

//===========================================================================
// ID - Platform User Test Register 0 (UT0)
//   Base Offset : 0x003C
//
// Reset Value : 0x0000 0001
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// UTE          31        rw  UTest Enable. This status bit gives indication 
//                            when UTest is enabled. All bits in UT0, UT1, UT2,
//                            UM0,UM1, UM2, UM3, and UM4 are locked when this 
//                            bit is 0. This bit is not writable to a 1, but 
//                            may be cleared. The reset value is 0. The method
//                            to set this bit is to provide a password, and 
//                            if the password matches, the UTE bit is set to 
//                            reflect the status of enabled, and is enabled 
//                            until it is cleared by a register write. The 
//                            UTE password will only be accepted if MCR[PGM]=0
//                            and MCR [ERS] = 0 (program and erase are not 
//                            being requested). UTE can only be cleared if 
//                            UT0[AID] = 1, UT0[AIE] and UT0[EIE] = 0.While 
//                            clearing UTE, writes to set AIE or set EIE 
//                            will be ignored. For UTE, the password 0xF9F9_9999
//                            must be written to the UT0 register.
//
// SCBE         30        rw  Single Bit Correction Enable. SBC enables Single 
//                            Bit Correction results to be observed in MCR[SBC].
//                            Also is used as an enable for interrupt signals 
//                            created by the c90fl module (see c90fl Integration
//                            Guide). ECC corrections that occur when SBCE is 
//                            cleared will not be logged.
//                            0 Single Bit Corrections observation is disabled.
//                            1 Single Bit Correction observation is enabled
//
// 0           [29:24]      r  Reserved
//
// DSI         [23:16]     rw  Data Syndrome Input. These bits enable checks of
//                             ECC logic by allowing check bits to be input into
//                             the ECC logic and then read out by doing array 
//                             reads or array integrity checks. The DSI[7:0]
//                             correspond to the 8 ECC check bits on a double
//                             word.
//
// 0           [15:6]     r    Reserved
//
// MRE            5       rw  Margin Read Enable. MRE combined with MRV enables 
//                            Factory Margin Reads to be done. Margin reads are
//                            only active during Array Integrity Checks. Normal
//                            user reads are not affected by MRE. MRE is not 
//                            writable if AID is low.
//                            0 Margin reads are not enabled.
//                            1 Margin reads are enabled during Array Integrity Checks.
//
// MRV            4       rw   Margin Read Value. MRV selects the margin level
//                             that is being checked. Margin can be checked to
//                             an erased level (MRV = 1) or to a programmed 
//                             level (MRV = 0). In order for this value to be
//                             valid, MRE must also be set. MRV is not writable
//                             if AID is low.
//                             0 Zero¡¯s margin reads are requested.
//                             1 One¡¯s margin reads are requested.
//
// EIE            3       rw   ECC Data Input Enable. EIE enables the input 
//                             registers (DSI and DAI) to be the source of data
//                             for the array. This is useful in the ECC logic 
//                             check. If this bit is set, data read through a 
//                             BIU read request will be from the DSI and DAI 
//                             registers when an address match is achieved to
//                             the ADR register. EIE is not simultaneously 
//                             writable to a 1 as UTI is being cleared to a 0.
//                             0 Data read is from the flash array.
//                             1 Data read is from the DSI and DAI registers.
//
// AIS            2       rw   Array Integrity Sequence. AIS determines the 
//                             address sequence to be used during array 
//                             integrity checks. The default sequence(AIS=0)
//                             is meant to replicate sequences normal ¡°user¡±
//                             code follows,and thoroughly checks the read
//                             propagation paths. This sequence is proprietary.
//                             The alternative sequence (AIS = 1) is just 
//                             logically sequential.It should be noted that 
//                             the time to run a sequential sequence is 
//                             significantly shorter than the time to run
//                             the proprietary sequence. If MRE is set, AIS 
//                             has no effect.
//                             0 Array integrity sequence is proprietary sequence.
//                             1 Array integrity sequence is sequential.
//
// AIE            1       rw   Array Integrity Enable. AIE set to one starts 
//                             the array integrity check done on all selected
//                             and unlocked blocks. The address sequence 
//                             selected is determined by AIS, and the MISR 
//                             (UM0 through UM4) can be checked after the
//                             operation is complete, to determine if a correct
//                             signature is obtained. Once an Array Integrity 
//                             operation is requested (AIE = 1), it may be 
//                             terminated by clearing AIE if the operation has
//                             finished (AID = 1) or aborted by clearing AIE 
//                             if the operation is ongoing (AID = 0). AIE is not
//                             simultaneously writable to a 1 as UTI is being 
//                             cleared to a 0.
//                             0 Array integrity checks are not enabled.
//                             1 Array integrity checks are enabled.
//
// AID            0        r   Array Integrity Done. AID is cleared upon an 
//                             Array integrity check being enabled (to signify
//                             the operation is ongoing). Once completed, AID 
//                             is set to indicate that the array integrity 
//                             check is complete.At this time the MISR (UMR 
//                             registers) can be checked. AID can not be 
//                             written, and is status only.
//                             0 Array integrity check is ongoing.
//                             1 Array integrity check is done.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_UT0_F_Tag
{
   bitfield32_t  UTE     :  BIT_1 ; // Bits 31
   bitfield32_t  SCBE    :  BIT_1;  // Bits 30
   bitfield32_t          :  BIT_6;  // Bits [29:24]
   bitfield32_t  DSI     :  BIT_8;  // Bits [23:16]
   bitfield32_t          :  BIT_10; // Bits [15:6]
   bitfield32_t  MRE     :  BIT_1;  // Bits 5
   bitfield32_t  MRV     :  BIT_1;  // Bits 4
   bitfield32_t  EIE     :  BIT_1;  // Bits 3
   bitfield32_t  AIS     :  BIT_1;  // Bits 2
   bitfield32_t  AIE     :  BIT_1;  // Bits 1
   bitfield32_t  AID     :  BIT_1;  // Bits 0
    
} FLASH_UT0_F_T;

typedef union FLASH_UT0_Tag
{
   FLASH_UT0_F_T    F;
   uint32_t          U32;
}  FLASH_UT0_T;

//===========================================================================
// ID - User Multiple Input Signature Register [0:4] (UMn)
//   Base Offset : 0x0048 - 0x54
//
// Reset Value : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// MISR         127-0     rw    Multiple Input Signature Register bits
//                              The MISR bitfields accumulate a signature
//                              from an array integrity event. The MISR 
//                              captures all data fields, as well as ECC 
//                              fields, and the read transfer error signal.
//                              The MISR can be seeded to any value by 
//                              writing the MISR registers
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//===========================================================================
typedef struct FLASH_UM4_F_Tag
{
   bitfield32_t          :  BIT_16 ; // Bits [31:16]
   bitfield32_t  MISR    :  BIT_16;  // Bits [15:0]
} FLASH_UM4_F_T;

typedef union FLASH_UM4_Tag
{
   FLASH_UM4_F_T     F;
   uint32_t          U32;
}  FLASH_UM4_T;

//===========================================================================
typedef uint32_t FLASH_UT1_T;
typedef uint32_t FLASH_UT2_T;
typedef uint32_t FLASH_UM0_3_T;

//===========================================================================
//  FLASH Module Register Structure
//===========================================================================

typedef volatile struct FLASH_Tag
{
   FLASH_MCR_T        MCR;                                //0x00 - 0x03
   FLASH_LMLR_T       LMLR;                               //0x04 - 0x07
   FLASH_HLR_T        HLR;                                //0x08 - 0x0B
   FLASH_SLMLR_T      SLMLR;                              //0x0C - 0x0F
   FLASH_LMSR_T       LMSR;                               //0x10 - 0x13
   FLASH_HSR_T        HSR;                                //0x14 - 0x17
   FLASH_AR_T         AR;                                 //0x18 - 0x1B
   FLASH_BIUCR1_T     BIUCR1;                             //0x1C - 0x1F
   FLASH_BIUAPR_T     BIUAPR;                             //0x20 - 0x23
   FLASH_BIUCR2_T     BIUCR2;                             //0x24 - 0x27
   uint8_t            reserved_0[FLASH_RESERVED_0x14];    //0x28 - 0x3B
   FLASH_UT0_T        UT0;                                //0x3C - 0x3F
   FLASH_UT1_T        UT1;                                //0x40 - 0x43
   FLASH_UT2_T        UT2;                                //0x44 - 0x47
   FLASH_UM0_3_T      UMn[FLASH_USER_MULTIPLE_SIGNATURE]; //0x48 - 0x57
   FLASH_UM4_T        UM4;                                //0x58 - 0x5B
   uint8_t            reserved_2[FLASH_RESERVED_0x3FA4];  // 0x5C - 0x3FFF

}  FLASH_T;


#endif // HW_FLASH_H

