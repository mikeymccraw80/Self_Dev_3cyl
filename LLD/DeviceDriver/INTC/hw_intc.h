#ifndef HW_INTC_H
#define HW_INTC_H

#include "reuse.h"

#define INTC_PSR_QUANTITY     (0x0200U)
#define INTC_SSCIR_QUANTITY   (0x08U)


//=============================================================================
// ID - INTC Module Configuration Register (INTC_MCR)
//
// Base Offset : 0000 0000 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31:6]     r   Reserved.
//
// VTES_PRC0     5        rw  Vector Table Entry Size for Processor 0. 
//                            The VTES_PRC0 bit controls the number of ‘0’s to 
//                            the right of INTVEC_PRC0 , INTC Interrupt 
//                            Acknowledge Register for processor 0
//                            (INTC_IACKR_PRC0).If the contents of INTC_IACKR_PRC0 
//                            are used as an address of an entry in a vector
//                            table as in software vector mode, then the
//                            number of rightmost ‘0’s will determine the
//                            size of each vector table entry.
//                            VTES_PRC0 impacts software vector mode operation
//                            but also affects INTC_IACKR_PRC0[INTVEC_PRC0] 
//                            position in both hardware vector mode and 
//                            software vector mode.
//
//                               0 4 bytes (Normal expected use)
//                               1 8 bytes (Intended for potential future
//                                 code compression)
//
//
// 0           [ 4: 1]    r   Reserved.
//
// HVEN_PRC0       0      rw  Hardware Vector Enable for Processor 0. The HVEN_PRC0 
//                            bit controls whether the INTC is in hardware vector 
//                            mode or software vector mode.
//
//                               0 Software vector mode
//                               1 Hardware vector mode
//
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct INTC_MCR_F_Tag
{
   bitfield32_t                 :  BIT_26;  // Bits [31:6] are reserved
   bitfield32_t  VTES_PRC0      :  BIT_1;   // Bit  5
   bitfield32_t                 :  BIT_4;   // Bits [ 4: 1] are reserved
   bitfield32_t  HVEN_PRC0      :  BIT_1;   // Bit  0

}  INTC_MCR_F_T;

typedef union INTC_MCR_Tag
{
   INTC_MCR_F_T         F;
   uint32_t             U32;

}  INTC_MCR_T;

//=============================================================================
// ID - INTC Current Priority Register for Processor 0 (INTC_CPR)
//
// Base Offset : 0000 0008 H
//
// Reset Value : 0000 000F H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31:04]     r  Reserved.
//
// PRI         [03:00]    rw  Priority. PRI is the priority of the currently
//                            executing ISR according to the field values
//                            defined in Table given below.
//
//                                      PRI Values
//
//                                    PRI       Meaning
//
//                                   1111     Priority 15 - highest priority
//                                   1110     Priority 14
//                                   1101     Priority 13
//                                   1100     Priority 12
//                                   1011     Priority 11
//                                   1010     Priority 10
//                                   1001     Priority 9
//                                   1000     Priority 8
//                                   0111     Priority 7
//                                   0110     Priority 6
//                                   0101     Priority 5
//                                   0100     Priority 4
//                                   0011     Priority 3
//                                   0010     Priority 2
//                                   0001     Priority 1
//                                   0000     Priority 0 - lowest priority
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct INTC_CPR_F_Tag
{
   bitfield32_t            :  BIT_28; // Bits [31:04] are reserved
   bitfield32_t  PRI       :  BIT_4;  // Bit  [03:00]

}  INTC_CPR_F_T;

typedef union INTC_CPR_Tag
{
   INTC_CPR_F_T         F;
   uint32_t             U32;

}  INTC_CPR_T;

//=============================================================================
// ID - INTC Interrupt Acknowledge Register for Processor 0 (INTC_IACKR)
//
// Base Offset : 0000 0010 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// VTBA_PRC0   [31:11]    rw  Vector Table Base Address for Processor 0. 
// [20:00]                    VTBA_PRC0 can be the base address of a vector 
//                            table of addresses of ISRs for Processor 0. 
//                            The VTBA_PRC0 only uses the leftmost 20 bits 
//                            when the VTES_PRC0 bit in INTC_MCR is asserted.
//
// INTVEC_PRC0 [10: 2]     r  Interrupt Vector for Processor 0. INTVEC_PRC0 
//                            is the vector of the peripheral or software 
//                            setable interrupt request that caused the 
//                            interrupt request to the processor. When the 
//                            interrupt request to the processor asserts, the 
//                            INTVEC_PRC0 is updated,whether the INTC is in 
//                            software or hardware vector mode.
//                            Note: If INTC_MCR[VTES_PRC0] = 1, then 
//                            INTVEC_PRC0 field is shifted left one position 
//                            to bits 20:18. VTBA_PRC0 is then shortened by 
//                            one bit to bits 0:19. 
//
// 0           [ 1: 0]     r  Reserved.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef struct INTC_IACKR_F_Tag
{
   bitfield32_t  VTBA           :  BIT_21; // Bits [31:11]
   bitfield32_t  INTVEC         :  BIT_9;  // Bits [10: 2]
   bitfield32_t                 :  BIT_2;  // Bits [ 1: 0] are reserved

}  INTC_IACKR_F_T;

typedef union INTC_IACKR_Tag
{
   INTC_IACKR_F_T         F;
   uint32_t               U32;

}  INTC_IACKR_T;

//=============================================================================
// ID - INTC End of Interrupt Register (INTC_EOIR)
//
// Base Offset : 0000 0018 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31:00]     r  Writing to the End of Interrupt Register
//                            signals the end of the servicing of the
//                            interrupt request.Those values and sizes
//                            written to this register neither update the
//                            INTC_EOIR_PRC0 contents or affect whether the 
//                            LIFO pops. For possible future compatibility, 
//                            write four bytes of all ‘0’s to the INTC_EOIR_PRC0.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
// ID - INTC Software Set/Clear Interrupt Registers (INTC_SSCIR0_3 )
//
// Base Offset : 0000 0020 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31:26]     r  Reserved.
//             [23:18]
//             [15:10]
//             [ 7: 2]
//
// SET0-SET3   25,17,9,    w  Set Flag bits. Writing a ‘1’ will set the
//              1             corresponding CLRx bit. Writing a ‘0’ will
//                            have no effect. Each SETx always will be
//                            read as a ‘0’.
//
// CLR0-CLR3  24,16,8,0   rw  Clear Flag bits. CLRx is the flag bit.
//                            Writing a ‘1’ to CLRx will clear it
//                            provided that a ‘1’ is not written
//                            simultaneously to its corresponding SETx bit.
//                            Writing a ‘0’ to CLRx will have no effect.
//
//                              0 Interrupt request not pending within INTC.
//                              1 Interrupt request pending within INTC.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

//=============================================================================
// ID - INTC Software Set/Clear Interrupt Registers (INTC_SSCIR4_7 )
//
// Base Offset : 0000 0024 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31:26]     r  Reserved.
//             [23:18]
//             [15:10]
//             [ 7: 2]
//
// SET4-SET7   25,17,9,    w  Set Flag bits. Writing a ‘1’ will set the
//              1             corresponding CLRx bit. Writing a ‘0’ will
//                            have no effect. Each SETx always will be
//                            read as a ‘0’.
//
// CLR4-CLR7  24,16,8,0   rw  Clear Flag bits. CLRx is the flag bit.
//                            Writing a ‘1’ to CLRx will clear it
//                            provided that a ‘1’ is not written
//                            simultaneously to its corresponding SETx bit.
//                            Writing a ‘0’ to CLRx will have no effect.
//
//                              0 Interrupt request not pending within INTC.
//                              1 Interrupt request pending within INTC.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef struct INTC_SSCIR_F_Tag
{
   bitfield8_t             :  BIT_6;  // Bits [ 7: 2] are reserved
   bitfield8_t   SET       :  BIT_1;  // Bit       1
   bitfield8_t   CLR       :  BIT_1;  // Bit       0


}  INTC_SSCIR_F_T;

typedef union INTC_SSCIR_Tag
{
   INTC_SSCIR_F_T    F;
   uint8_t           U8;

}  INTC_SSCIR_T;

//=============================================================================
// ID - INTC Priority Select Registers (INTC_PSR0_ 3)
//
// Base Offset : 0000 0040 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31:28]     r  Reserved.
//             [23:20]
//             [15:12]
//             [ 7: 4]
//
// PRI0        [27:24]    rw  Priority Select. PRIn selects the priority
// PRI1        [19:16]        for the interrupt requests.
// PRI2        [11: 8]
// PRI3        [ 3: 0]
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
// ID - INTC Priority Select Registers (INTC_PSR508_ 511)
//
// Base Offset : 0000 023C H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31:28]     r  Reserved.
//             [23:20]
//             [15:12]
//             [ 7: 4]
//
// PRI508      [27:24]    rw  Priority Select. PRIn selects the priority
// PRI509      [19:16]        for the interrupt requests.
// PRI510      [11: 8]
// PRI511      [ 3: 0]
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

typedef struct INTC_PSR_F_Tag
{
   bitfield8_t             :  BIT_4;  // Bits [ 7: 4] are reserved
   bitfield8_t   PRI       :  BIT_4;  // Bits [ 3: 0]

}  INTC_PSR_F_T;

typedef union INTC_PSR_Tag
{
   INTC_PSR_F_T   F;
   uint8_t        U8;

}  INTC_PSR_T;


//=============================================================================
//  INTC Module Register Structure
//=============================================================================
#define INTC_RESERVED_0x0004  (0x0004U)
#define INTC_RESERVED_0x0018  (0x0018U)

typedef volatile struct INTC_Tag
{
   INTC_MCR_T         MCR;                                // 0x0000 - 0x0003
   uint8_t            reserved_0[INTC_RESERVED_0x0004];   // 0x0004 - 0x0007
   INTC_CPR_T         CPR_PRC0;                           // 0x0008 - 0x000B
   uint8_t            reserved_1[INTC_RESERVED_0x0004];   // 0x000C - 0x000F
   INTC_IACKR_T       IACKR_PRC0;                         // 0x0010 - 0x0013
   uint8_t            reserved_2[INTC_RESERVED_0x0004];   // 0x0014 - 0x0017
   uint32_t           EOIR_PRC0;                          // 0x0018 - 0x001B
   uint8_t            reserved_3[INTC_RESERVED_0x0004];   // 0x001C - 0x001F
   INTC_SSCIR_T       SSCIR[INTC_SSCIR_QUANTITY];         // 0x0020 - 0x0027
   uint8_t            reserved_4[INTC_RESERVED_0x0018];   // 0x0028 - 0x003F
   INTC_PSR_T         PSR[INTC_PSR_QUANTITY];             // 0x0040 - 0x023F

}  INTC_T;

#endif // HW_INTC_H

