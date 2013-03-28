#ifndef HW_ECSM_H
#define HW_ECSM_H


#include "reuse.h"

#define ECSM_RESERVED_0x0001  (0x0001)
#define ECSM_RESERVED_0x0002  (0x0002)
#define ECSM_RESERVED_0x0003  (0x0003)
#define ECSM_RESERVED_0x0004  (0x0004)
#define ECSM_RESERVED_0x0043  (0x0043) 

//=============================================================================
// ID - ECC Configuration Register (ECSM_ECR)
//
// Base Offset : 0000 0043H
//
// Reset Value : 00 H
//
// Field      Bits    Type  Description
// ======== ========= ===== ===============================================
// 0         [7:6]    r     Reserved
//-----------------------------------------------------------------------------
// ER1BR      5       rw    Enable RAM 1-bit reporting
//                          0 Reporting of single-bit platform RAM corrections 
//                            is disabled
//                          1 Reporting of single-bit platform RAM corrections
//                            is enabled
//-----------------------------------------------------------------------------
// EF1BR      4       rw    Enable Flash 1-bit reporting.
//                          0 Reporting of single-bit platform flash  
//                            corrections is disabled.
//                          1 Reporting of single-bit platform flash  
//                            corrections is enabled.
//-----------------------------------------------------------------------------
// 0        [3:2]     r     Reserved.
//-----------------------------------------------------------------------------
// ERNCR      1       rw    Enable platform RAM non-correctable reporting. The
//                          occurrence of a non-correctable multi-bit
//                          RAM error generates a ECSM ECC interrupt
//                          request as signalled by the assertion of
//                          ECSM_ESR[RNCE]. The faulting address,
//                          attributes and data are also captured in the
//                          REAR, PRESR, REMR, REAT and REDR registers.
//                          0 Reporting of non-correctable RAM errors
//                            is disabled.
//                          1 Reporting of non-correctable RAM errors
//                            is enabled.
//-----------------------------------------------------------------------------
// EFNCR      0       rw    Enable platform Flash non-correctable reporting. 
//                          The occurrence of a non-correctable multi-bit
//                          Flash error generates a ECSM ECC interrupt
//                          request as signalled by the assertion of
//                          ECSM_ESR[FNCE]. The faulting address,
//                          attributes and data are also captured in the
//                          FEAR, FEMR, FEAT and FEDR registers.
//                          0 Reporting of non-correctable Flash errors
//                            is disabled.
//                          1 Reporting of non-correctable Flash errors
//                            is enabled.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct ECSM_ECR_F_Tag
{
   bitfield8_t             :  BIT_2;   // Bits [7:6] are reserved
   bitfield8_t  ER1BR      :  BIT_1;   // Bit  5
   bitfield8_t  EF1BR      :  BIT_1;   // Bit  4
   bitfield8_t             :  BIT_2;   // Bits [3:2] are reserved
   bitfield8_t  ERNCR      :  BIT_1;   // Bit  1
   bitfield8_t  EFNCR      :  BIT_1;   // Bit  0

}  ECSM_ECR_F_T;

typedef union ECSM_ECR_Tag
{
   ECSM_ECR_F_T            F;
   uint8_t                 U8;
}  ECSM_ECR_T;

//=============================================================================
// ID - ECC Status Register (ECSM_ESR)
//
// Base Offset : 0000 0047H
//
// Reset Value : 00 H
//
// Field     Bits   Type  Description
// ========== ========= ===== ===============================================
// 0         [7:6]   r    Reserved.
//-----------------------------------------------------------------------------
// R1BC        5     rw   Platform RAM 1-bit Correction.This bit can only be  
//                        set if ECR[ER1BR] is asserted. The occurrence 
//                        of a properly-enabled single-bit RAM 
//                        correction generates an ECSM ECC 
//                        interrupt request. The address, attributes 
//                        and data are also captured in the REAR, 
//                        PRESR, REMR, REAT and REDR registers. 
//                        To clear this interrupt flag, write a 1 to 
//                        this bit.Writing a 0 has no effect
//                        0 No reportable single-bit platform RAM correction 
//                          has been detected
//                        1 A reportable single-bit platform RAM correction 
//                          has been detected
//-----------------------------------------------------------------------------
// F1BC        4     rw   Platform Flash 1-bit Correction. This bit can only be 
//                        set if ECR[EF1BR] is asserted. The 
//                        occurrence of a properly-enabled single-bit 
//                        flash correction generates an ECSM ECC 
//                        interrupt request. The address, attributes
//                        and data are also captured in the FEAR, 
//                        FEMR, FEAT and FEDR registers. To clear 
//                        this interrupt flag, write a 1 to this bit.
//                        Writing a 0 has no effect
//                        0 No reportable single-bit platform flash correction 
//                          has been detected
//                        1 A reportable single-bit platform flash correction 
//                          has been detected
//-----------------------------------------------------------------------------
// 0         [3:2]   r    Reserved.
//-----------------------------------------------------------------------------
// RNCE        1     rw   RAM non-correctable error. The occurrence
//                        of a properly-enabled non-correctable
//                        RAM error generates an ECSM ECC interrupt
//                        request. The faulting address, attributes
//                        and data are also captured in the REAR,
//                        PRESR, REMR, REAT and REDR registers.
//                        To clear this interrupt flag, write a 1 to
//                        this bit. Writing a 0 has no effect.
//                        0 No reportable non-correctable platform RAM error
//                          has been detected.
//                        1 A reportable non-correctable platform RAM error
//                          has been detected.
//-----------------------------------------------------------------------------
// FNCE        0     rw   Flash non-correctable error. The occurrence
//                        of a properly-enabled non-correctable Flash
//                        error generates an ECSM ECC interrupt
//                        request. The faulting address, attributes
//                        and data are also captured in the FEAR,
//                        FEMR, FEAT and FEDR registers. To clear
//                        this interrupt flag, write a 1 to this bit.
//                        Writing a 0 has no effect.
//                        0 No reportable non-correctable platform Flash error
//                          has been detected.
//                        1 A reportable non-correctable platform Flash error
//                          has been detected.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct ECSM_ESR_F_Tag
{
   bitfield8_t             :  BIT_2;   // Bits [7:6] are reserved
   bitfield8_t  R1BC       :  BIT_1;   // Bit  5
   bitfield8_t  F1BC       :  BIT_1;   // Bit  4
   bitfield8_t             :  BIT_2;   // Bits [3:2] are reserved
   bitfield8_t  RNCE       :  BIT_1;   // Bit  1
   bitfield8_t  FNCE       :  BIT_1;   // Bit  0

}  ECSM_ESR_F_T;

typedef union ECSM_ESR_Tag
{
   ECSM_ESR_F_T            F;
   uint8_t                 U8;
}  ECSM_ESR_T;

//=============================================================================
// ID - ECC Error Generation Register (ECSM_EEGR)
//
// Base Offset : 0x004A
//
// Reset Value : 0x0000
//
// Field    Bits   Type  Description
// ========== ========= ===== ==============================================
// 0       [15:10]  r    Reserved.
//-----------------------------------------------------------------------------
// FRCNCI    9      rw   Force RAM continuous noncorrectable 
//                       data Inversions.
//                       0 No RAM continuous 2-bit data inversions 
//                         are generated.
//                       1 2-bit data inversions in the RAM are 
//                         continuously generated.
//-----------------------------------------------------------------------------
// FR1NCI    8      rw   Force RAM one noncorrectable data Inversions
//                       0 No RAM single 2-bit data inversions are 
//                         generated.
//                       1 One 2-bit data error in the RAM is 
//                        generated.
//-----------------------------------------------------------------------------
// ERRBIT  [7:0]    rw   Error bit position. Defines the bit position which 
//                       is complemented to create the data inversions on 
//                       the write operation. The bit specified by this field 
//                       plus the odd parity bit of the ECC code are inverted.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct ECSM_EEGR_F_Tag
{
   bitfield16_t              :  BIT_6;   // Bits [15:10] are reserved
   bitfield16_t  FRCNCI      :  BIT_1;   // Bits 9 
   bitfield16_t  FR1NCI      :  BIT_1;   // Bits 8
   bitfield16_t  ERRBIT      :  BIT_8;   // Bits [7:0]

}  ECSM_EEGR_F_T;

typedef union ECSM_EEGR_Tag
{
   ECSM_EEGR_F_T            F;
   uint16_t                 U16;
}  ECSM_EEGR_T;

//=============================================================================
// ID - Platform Flash ECC Address Register (ECSM_FEAR)
//
// Base Offset : 0000 0050H
//
// Reset Value : XXXX XXXX H
//
// Field        Bits    Type  Description
// ========== ========= ===== ===============================================
// FEAR        [31:0]     r   Flash ECC address register. Contains the 
//                            faulting access address of the last, properly
//                            enabled Platform Flash ECC event.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef uint32_t     ECSM_FEAR_T;

//=============================================================================
// ID - Platform Flash ECC Master Number Register (ECSM_FEMR)
//
// Base Offset : 0000 0056H
//
// Reset Value : 0X H
//
// Field        Bits    Type  Description
// ========== ========= ===== ===============================================
// 0           [07:04]    r   Reserved.
//-----------------------------------------------------------------------------
// FEMR        [03:00]    r   Flash ECC master number. Contains the AXBS
//                            bus master number of the faulting access of the
//                            last, properly-enabled Platform Flash ECC event.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct ECSM_FEMR_F_Tag
{
   bitfield8_t             :  BIT_4;   // Bits [7:4] are reserved
   bitfield8_t  FEMR       :  BIT_4;   // Bit  [3:0]
}  ECSM_FEMR_F_T;

typedef union ECSM_FEMR_Tag
{
   ECSM_FEMR_F_T            F;
   uint8_t                  U8;
}  ECSM_FEMR_T;

//=============================================================================
// ID - Flash ECC Attributes Register (ECSM_FEAT)
//
// Base Offset : 0000 0057H
//
// Reset Value : XX H
//
// Field         Bits   Type  Description
// ========== ========= ===== ===============================================
// WRITE          7       r   Write.
//                              0 read access
//                              1 write access
//-----------------------------------------------------------------------------
// SIZE         [6:4]     r   Size.
//                              000 8-bit access
//                              001 16-bit access
//                              010 32-bit access
//                              011 64-bit access
//                              1xx Reserved
//-----------------------------------------------------------------------------
// PROTECTION   [3:0]     r   Protection
//                            0b0xxx = Non-cacheable, 0b1xxx = Cacheable
//                            0bx0xx = Non-bufferable, 0bx1xx = Bufferable
//                            0bxx0x = User mode,      0bxx1x = Supervisor mode
//                            0bxxx0 = I-Fetch,        0bxxx1 = Data 
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct ECSM_FEAT_F_Tag
{
   bitfield8_t  WRITE           :  BIT_1;   // Bit  7
   bitfield8_t  SIZE            :  BIT_3;   // Bits [6:4]
   bitfield8_t  PROTECTION      :  BIT_4;   // Bits [3:0]
}  ECSM_FEAT_F_T;

typedef union ECSM_FEAT_Tag
{
   ECSM_FEAT_F_T            F;
   uint8_t                  U8;
}  ECSM_FEAT_T;

//=============================================================================
// Enumeration: Size     (SIZE)
//
//  SIZE       Meaning of value
//   [2:0]
// ========  ===============================================================
//     000   8-bit AMBA-AHB access
//     001   16-bit AMBA-AHB access
//     010   32-bit AMBA-AHB access
//     011   64-bit AMBA-AHB access
//     1xx   Reserved
//
//=============================================================================

typedef enum ECSM_FEAT_SIZE_Tag
{
   ECSM_FEAT_SIZE_8BIT_AMB_AHB_ACC,
   ECSM_FEAT_SIZE_16BIT_AMB_AHB_ACC,
   ECSM_FEAT_SIZE_32BIT_AMB_AHB_ACC,
   ECSM_FEAT_SIZE_64BIT_AMB_AHB_ACC,
   ECSM_FEAT_SIZE_RESERVED1,
   ECSM_FEAT_SIZE_RESERVED2,
   ECSM_FEAT_SIZE_RESERVED3,
   ECSM_FEAT_SIZE_RESERVED4
}  ECSM_FEAT_SIZE_T;

//=============================================================================
// ID - Platform Flash ECC Data High Register (ECSM_FEDRH)
//
// Base Offset : 0000 0058H
//
// Reset Value : XXXX XXXX H
//
// Field          Bits   Type  Description
// ========== ========= ===== ==============================================
// FEDH        [31:00]     r  Flash ECC data. Contains the data associated
//                            with the faulting access of the last,
//                            properly-enabled Flash ECC event. The register
//                            contains the data value taken directly from
//                            the platform data bus.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef uint32_t     ECSM_FEDRH_T;

//=============================================================================
// ID - Platform Flash ECC Data Low Registers (ECSM_FEDRL)
//
// Base Offset : 0000 005CH
//
// Reset Value : XXXX XXXX H
//
// Field          Bits   Type  Description
// ========== ========= ===== ==============================================
// FEDL        [31:00]     r  Flash ECC data. Contains the data associated
//                            with the faulting access of the last,
//                            properly-enabled Flash ECC event. The register
//                            contains the data value taken directly from
//                            the platform data bus.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef uint32_t     ECSM_FEDRL_T;

//=============================================================================
// ID - Platform RAM ECC Address Register (ECSM_REAR)
//
// Base Offset : 0000 0060H
//
// Reset Value : XXXX XXXX H
//
// Field          Bits   Type  Description
// ========== ========= ===== ==============================================
// REAR        [31:00]     r  RAM ECC Address. Contains the faulting access
//                            address of the last, properly-enabled platform 
//                            RAM ECC event.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef uint32_t     ECSM_REAR_T;

//=============================================================================
// ID - Platform RAM ECC Syndrome Register (ECSM_PRESR)
//
// Base Offset : 0000 0065
//
// Reset Value : XXXX XXXX H
//
// Field        Bits    Type  Description
// ========== ========= ===== ==============================================
// PRESR        [7:0]    r    RAM ECC Syndrom Register. Contains a 
//                            report syndrome obtained by mapping the raw 7-bit
//                            ECC syndrome from each 32-bit bank (even, odd) 
//                            to an 8-bit syndrome that is backwards compatible
//                            with 64-bit organized memories Each 7-bit raw
//                            syndrome is formed by 6 bits of Hamming decoded 
//                            parity plus an odd-parity bit for the entire 39-bit 
//                            (32-bit data + 7 ECC) code word. The upper 6 bits
//                            of the raw syndrome specify the exact bit position 
//                            in error for single-bit correctable codewords, and
//                            the combination of a non-zero 6-bit syndrome
//                            plus overall incorrect parity bit signal a multi-bit, 
//                            non-correctable error.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef uint8_t     ECSM_PRESR_T;


//=============================================================================
// ID - Platform RAM ECC Master Number Register (ECSM_REMR)
//
// Base Offset : 0000 0066H
//
// Reset Value : 0X H
//
// Field        Bits    Type  Description
// ========== ========= ===== ==============================================
// 0           [7:4]     r    Reserved.
//-----------------------------------------------------------------------------
// REMR        [3:0]     r    Platform RAM ECC master number. Contains the AXBS
//                            bus master number of the faulting access of the
//                            last, properly-enabled Platform RAM ECC event.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct ECSM_REMR_F_Tag
{
   bitfield8_t             :  BIT_4;   // Bits [7:4] are reserved
   bitfield8_t  REMR       :  BIT_4;   // Bits [3:0]
}  ECSM_REMR_F_T;

typedef union ECSM_REMR_Tag
{
   ECSM_REMR_F_T            F;
   uint8_t                  U8;
}  ECSM_REMR_T;

//=============================================================================
// ID - Flash ECC Attributes Register (ECSM_REAT)
//
// Base Offset : 0000 0067H
//
// Reset Value : XX H
//
// Field         Bits   Type  Description
// ========== ========= ===== ===============================================
// WRITE          7       r   Write.
//                              0 read access
//                              1 write access
//-----------------------------------------------------------------------------
// SIZE         [6:4]     r   Size.
//                              000 8-bit access
//                              001 16-bit access
//                              010 32-bit access
//                              011 64-bit access
//                              1xx Reserved
//-----------------------------------------------------------------------------
// PROTECTION   [3:0]     r   Protection
//                            0b0xxx = Non-cacheable, 0b1xxx = Cacheable
//                            0bx0xx = Non-bufferable, 0bx1xx = Bufferable
//                            0bxx0x = User mode,      0bxx1x = Supervisor mode
//                            0bxxx0 = I-Fetch,        0bxxx1 = Data 
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef ECSM_FEAT_T ECSM_REAT_T;

//=============================================================================
// ID - Platform RAM ECC Data High Register (ECSM_REDRH)
//
// Base Offset : 0000 0068H
//
// Reset Value : XXXX XXXX H
//
// Field          Bits   Type  Description
// ========== ========= ===== ==============================================
// REDH       [31:00]     r   Platform RAM ECC data.Contains the data 
//                            associated with the faulting access of the last,
//                            properly-enabled platform RAM ECC event. The 
//                            register contains the data value taken directly 
//                            from the data bus.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef uint32_t     ECSM_REDRH_T;

//=============================================================================
// ID - Platform RAM ECC Data Low Registers (ECSM_REDRL)
//
// Base Offset : 0000 006CH
//
// Reset Value : XXXX XXXX H
//
// Field          Bits   Type  Description
// ========== ========= ===== ==============================================
// REDL        [31:00]     r  Platform RAM ECC data. Contains the data 
//                            associated with the faulting access of the last,
//                            properly-enabled platform RAM ECC event. The 
//                            register contains the data value taken directly
//                            from the data bus.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef uint32_t     ECSM_REDRL_T;

//=============================================================================
//  ECSM Module Register Structure
//=============================================================================

typedef volatile struct ECSM_Tag
{
   
   uint8_t             reserved_0[ECSM_RESERVED_0x0043]; // 0x0000 - 0x0042
   ECSM_ECR_T          ECR;                              // 0x0043
   uint8_t             reserved_1[ECSM_RESERVED_0x0003]; // 0x0044 - 0x0046
   ECSM_ESR_T          ESR;                              // 0x0047
   uint8_t             reserved_2[ECSM_RESERVED_0x0002]; // 0x0048 - 0x0049   
   ECSM_EEGR_T         EEGR;                             // 0x004A - 0x004B
   uint8_t             reserved_3[ECSM_RESERVED_0x0004]; // 0x004C - 0x004F   
   ECSM_FEAR_T         FEAR;                             // 0x0050 - 0x0053
   uint8_t             reserved_4[ECSM_RESERVED_0x0002]; // 0x0054 - 0x0055
   ECSM_FEMR_T         FEMR;                             // 0x0056
   ECSM_FEAT_T         FEAT;                             // 0x0057
   ECSM_FEDRH_T        FEDRH;                            // 0x0058 - 0x005B
   ECSM_FEDRL_T        FEDRL;                            // 0x005C - 0x005F
   ECSM_REAR_T         REAR;                             // 0x0060 - 0x0063
   uint8_t             reserved_5[ECSM_RESERVED_0x0001]; // 0x0064 
   ECSM_PRESR_T        PRESR;                            // 0x0065
   ECSM_REMR_T         REMR;                             // 0x0066
   ECSM_REAT_T         REAT;                             // 0x0067
   ECSM_REDRH_T        REDRH;                            // 0x0068 - 0x006B
   ECSM_REDRL_T        REDRL;                            // 0x006C - 0x006F   

}  ECSM_T;

#endif // HW_ECSM_H

