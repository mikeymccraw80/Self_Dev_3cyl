#ifndef HW_DMA_H
#define HW_DMA_H


#include "reuse.h"

#define DMA_CPR_QUANTITY   (  32)
#define DMA_TCD_QUANTITY   (  32)

#define DMA_ARRAY_SIZE_2   (   2)
#define DMA_ARRAY_SIZE_8   (   8)

#define DMA_RESERVED_4     (   4)
#define DMA_RESERVED_208   ( 208)
#define DMA_RESERVED_1024  (1024)
#define DMA_RESERVED_3808  (3808)

//=============================================================================
// ID - eDMA Control Register (DMA_CR)
//
// Base Offset : 0000 0000 H
//
// Reset Value : 0000 7400 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0           [31:16]     r  Reserved.
//
// GRP3PRI     [15:14]    rw  Channel group 3 priority. Group 3 priority
//                            level when fixed priority group arbitration is
//                            enabled.
//
// GRP2PRI     [13:12]    rw  Channel group 2 priority. Group 2 priority
//                            level when fixed priority group arbitration is
//                            enabled.
//
// GRP1PRI     [11:10]    rw  Channel group 1 priority. Group 1 priority
//                            level when fixed priority group arbitration is
//                            enabled.
//
// GRP0PRI     [09:08]    rw  Channel group 0 priority. Group 0 priority
//                            level when fixed priority group arbitration
//                            is enabled.
//
// 0           [07:04]     r  Reserved.
//
// ERGA             03    rw  Enable round robin group arbitration.
//                              0 Fixed priority arbitration is used for
//                                selection among the groups.
//                              1 Round robin arbitration is used for
//                                selection among the groups.
//
// ERCA             02    rw  Enable round robin channel arbitration.
//                              0 Fixed priority arbitration is used for
//                                channel selection within each group.
//                              1 Round robin arbitration is used for
//                                channel selection within each group.
//
// EDBG             01    rw  Enable debug.
//                              0 The assertion of the ipg_debug
//                                input is ignored.
//                              1 The assertion of the ipg_debug input
//                                causes the eDMA to stall the start
//                                of a new channel. Executing channels
//                                are allowed to complete.Channel
//                                execution will resume when either the
//                                system debug control input is negated 
//                                or the EDBG bit is cleared.
//
//EBW               00    rw  Enable Buffered Writes
//                              0 The bufferable write signal (hprot[2]) 
//                                is not asserted during AMBA AHB writes.
//                              1 The bufferable write signal (hprot[2]) is 
//                                asserted on all AMBA AHB writes except 
//                                for the last write sequence.
//
// Note: The Bit numbering is as per the manual
//       
//=============================================================================

typedef struct DMA_CR_F_Tag
{
   bitfield32_t            :  BIT_16; // Bits [31:16] are reserved
   bitfield32_t  GRP3PRI   :  BIT_2;  // Bits [15:14]
   bitfield32_t  GRP2PRI   :  BIT_2;  // Bits [13:12]
   bitfield32_t  GRP1PRI   :  BIT_2;  // Bits [11:10]
   bitfield32_t  GRP0PRI   :  BIT_2;  // Bits [09:08]
   bitfield32_t            :  BIT_4;  // Bits [07:04]
   bitfield32_t  ERGA      :  BIT_1;  // Bit      03
   bitfield32_t  ERCA      :  BIT_1;  // Bit      02
   bitfield32_t  EDBG      :  BIT_1;  // Bit      01
   bitfield32_t  EBW       :  BIT_1;  // Bit      00

}  DMA_CR_F_T;

typedef union DMA_CR_Tag
{
   DMA_CR_F_T  F;
   uint16_t    U16[DMA_ARRAY_SIZE_2];
   uint32_t    U32;

}  DMA_CR_T;


//=============================================================================
// ID - eDMA Error Status Register (DMA_ESR)
//
// Base Offset : 0000 0004 H
//
// Reset Value : 0000 0000 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// VLD              31     r  Logical OR of all DMA_ERL status bits.
//                              0 No DMA_ER bits are set.
//                              1 At least one DMA_ER bit is set indicating
//                                a valid error exists that has not been
//                                cleared.
//
// 0           [30:16]     r  Reserved.
//
// GPE              15     r  Group priority error.
//                              0 No group priority error.
//                              1 The last recorded error was a configuration
//                                error among the group priorities
//                                indicating not all group priorities are
//                                unique.
//
// CPE              14     r  Channel priority error.
//                              0 No channel priority error.
//                              1 The last recorded error was a
//                                configuration error in the channel
//                                priorities within a group, indicating
//                                not all channel priorities within a
//                                group are unique.
//
// ERRCHN      [13:08]     r  Error channel number. The channel number of
// [5:0]                      the last recorded error (excluding GPE
//                            and CPE errors)
//
// SAE              07     r  Source address error.
//                              0 No source address configuration error.
//                              1 The last recorded error was a
//                                configuration error detected in the
//                                TCD.SADDR field, indicating TCD.SADDR
//                                is inconsistent with TCD.SSIZE.
//
// SOE              06     r  Source offset error.
//                              0 No source offset configuration error.
//                              1 The last recorded error was a configuration
//                                error detected in the TCD.SOFF field,
//                                indicating TCD.SOFF is inconsistent with
//                                TCD.SSIZE.
//
// DAE              05     r  Destination address error.
//                              0 No destination address configuration error.
//                              1 The last recorded error was a configuration
//                                error detected in the TCD.DADDR field,
//                                indicating TCD.DADDR is inconsistent
//                                with TCD.DSIZE.
//
// DOE              04     r  Destination offset error.
//                              0 No destination offset configuration
//                                error.
//                              1 The last recorded error was a
//                                configuration error detected in the
//                                TCD.DOFF field, indicating TCD.DOFF
//                                is inconsistent with TCD.DSIZE.
//
// NCE              03     r  NBYTES/CITER configuration error.
//                              0 No NBYTES/CITER configuration error.
//                              1 The last recorded error was a
//                                configuration error detected in the
//                                TCD.NBYTES or TCD.CITER fields,
//                                indicating the following conditions
//                                exist:
//
//                                - TCD.NBYTES is not a multiple of
//                                  TCD.SSIZE and
//                                - TCD.DSIZE, or
//                                - TCD.CITER is equal to zero, or
//                                - TCD.CITER.E_LINK is not equal to
//                                  TCD.BITER.E_LINK.
//
//
// SGE              02     r  Scatter/gather configuration error.
//                              0 No scatter/gather configuration error.
//                              1 The last recorded error was a
//                                configuration error detected in the
//                                TCD.DLAST_SGA field, indicating
//                                TCD.DLAST_SGA is not on a 32-byte
//                                boundary. This field is checked at the
//                                beginning of a scatter/gather operation
//                                after major loop completion if TCD.E_SG
//                                is enabled.
//
// SBE              01     r  Source bus error.
//                              0 No source bus error.
//                              1 The last recorded error was a bus
//                                error on a source read.
//
// DBE              00     r  Destination bus error.
//                              0 No destination bus error.
//                              1 The last recorded error was a bus
//                                error on a destination write.
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_ESR_F_Tag
{
   bitfield32_t   VLD      :  BIT_1;  // Bit      31
   bitfield32_t            :  BIT_15; // Bits [30:16] are reserved
   bitfield32_t   GPE      :  BIT_1;  // Bit      15
   bitfield32_t   CPE      :  BIT_1;  // Bit      14
   bitfield32_t   ERRCHN   :  BIT_6;  // Bits [13:08]
   bitfield32_t   SAE      :  BIT_1;  // Bit      07
   bitfield32_t   SOE      :  BIT_1;  // Bit      06
   bitfield32_t   DAE      :  BIT_1;  // Bit      05
   bitfield32_t   DOE      :  BIT_1;  // Bit      04
   bitfield32_t   NCE      :  BIT_1;  // Bit      03
   bitfield32_t   SGE      :  BIT_1;  // Bit      02
   bitfield32_t   SBE      :  BIT_1;  // Bit      01
   bitfield32_t   DBE      :  BIT_1;  // Bit      00

}  DMA_ESR_F_T;

typedef union DMA_ESR_Tag
{
   DMA_ESR_F_T F;
   uint32_t    U32;

}  DMA_ESR_T;

//=============================================================================
// ID - eDMA Enable Request Registers (DMA_ERQRL)
//
// Base Offset : 0000 000C H  (DMA_ERQRL)
//
// Reset Value : 0000 0000 H  (DMA_ERQRL)
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// ERQn         [31:0]    rw  Enable DMA request n.
//                            0 The DMA request signal for channel n
//                              is disabled.
//                            1 The DMA request signal for channel n is
//                              enabled.
//
// Note: The Bit numbering is as per the manual
//       
//=============================================================================

typedef struct DMA_ERQRL_F_Tag
{
   bitfield32_t   ERQ31    :  BIT_1;  // Bit      31
   bitfield32_t   ERQ30    :  BIT_1;  // Bit      30
   bitfield32_t   ERQ29    :  BIT_1;  // Bit      29
   bitfield32_t   ERQ28    :  BIT_1;  // Bit      28
   bitfield32_t   ERQ27    :  BIT_1;  // Bit      27
   bitfield32_t   ERQ26    :  BIT_1;  // Bit      26
   bitfield32_t   ERQ25    :  BIT_1;  // Bit      25
   bitfield32_t   ERQ24    :  BIT_1;  // Bit      24
   bitfield32_t   ERQ23    :  BIT_1;  // Bit      23
   bitfield32_t   ERQ22    :  BIT_1;  // Bit      22
   bitfield32_t   ERQ21    :  BIT_1;  // Bit      21
   bitfield32_t   ERQ20    :  BIT_1;  // Bit      20
   bitfield32_t   ERQ19    :  BIT_1;  // Bit      19
   bitfield32_t   ERQ18    :  BIT_1;  // Bit      18
   bitfield32_t   ERQ17    :  BIT_1;  // Bit      17
   bitfield32_t   ERQ16    :  BIT_1;  // Bit      16
   bitfield32_t   ERQ15    :  BIT_1;  // Bit      15
   bitfield32_t   ERQ14    :  BIT_1;  // Bit      14
   bitfield32_t   ERQ13    :  BIT_1;  // Bit      13
   bitfield32_t   ERQ12    :  BIT_1;  // Bit      12
   bitfield32_t   ERQ11    :  BIT_1;  // Bit      11
   bitfield32_t   ERQ10    :  BIT_1;  // Bit      10
   bitfield32_t   ERQ09    :  BIT_1;  // Bit      09
   bitfield32_t   ERQ08    :  BIT_1;  // Bit      08
   bitfield32_t   ERQ07    :  BIT_1;  // Bit      07
   bitfield32_t   ERQ06    :  BIT_1;  // Bit      06
   bitfield32_t   ERQ05    :  BIT_1;  // Bit      05
   bitfield32_t   ERQ04    :  BIT_1;  // Bit      04
   bitfield32_t   ERQ03    :  BIT_1;  // Bit      03
   bitfield32_t   ERQ02    :  BIT_1;  // Bit      02
   bitfield32_t   ERQ01    :  BIT_1;  // Bit      01
   bitfield32_t   ERQ00    :  BIT_1;  // Bit      00

}  DMA_ERQRL_F_T;

typedef union DMA_ERQRL_Tag
{
   DMA_ERQRL_F_T  F;
   uint32_t       U32;

}  DMA_ERQRL_T;

//=============================================================================
// ID - eDMA Enable Error Interrupt Registers (DMA_EEIRL)
//
// Base Offset : 0000 0014 H  (DMA_EEIRL)
//
// Reset Value : 0000 0000 H  (DMA_EEIRL)
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// EEIn         [31:0]    rw  Enable error interrupt n.
//                              0 The error signal for channel n does
//                                not generate an error interrupt.
//                              1 The assertion of the error signal for
//                                channel n generate an error interrupt
//                                request.
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_EEIRL_F_Tag
{
   bitfield32_t   EEI31    :  BIT_1;  // Bit      31
   bitfield32_t   EEI30    :  BIT_1;  // Bit      30
   bitfield32_t   EEI29    :  BIT_1;  // Bit      29
   bitfield32_t   EEI28    :  BIT_1;  // Bit      28
   bitfield32_t   EEI27    :  BIT_1;  // Bit      27
   bitfield32_t   EEI26    :  BIT_1;  // Bit      26
   bitfield32_t   EEI25    :  BIT_1;  // Bit      25
   bitfield32_t   EEI24    :  BIT_1;  // Bit      24
   bitfield32_t   EEI23    :  BIT_1;  // Bit      23
   bitfield32_t   EEI22    :  BIT_1;  // Bit      22
   bitfield32_t   EEI21    :  BIT_1;  // Bit      21
   bitfield32_t   EEI20    :  BIT_1;  // Bit      20
   bitfield32_t   EEI19    :  BIT_1;  // Bit      19
   bitfield32_t   EEI18    :  BIT_1;  // Bit      18
   bitfield32_t   EEI17    :  BIT_1;  // Bit      17
   bitfield32_t   EEI16    :  BIT_1;  // Bit      16
   bitfield32_t   EEI15    :  BIT_1;  // Bit      15
   bitfield32_t   EEI14    :  BIT_1;  // Bit      14
   bitfield32_t   EEI13    :  BIT_1;  // Bit      13
   bitfield32_t   EEI12    :  BIT_1;  // Bit      12
   bitfield32_t   EEI11    :  BIT_1;  // Bit      11
   bitfield32_t   EEI10    :  BIT_1;  // Bit      10
   bitfield32_t   EEI09    :  BIT_1;  // Bit      09
   bitfield32_t   EEI08    :  BIT_1;  // Bit      08
   bitfield32_t   EEI07    :  BIT_1;  // Bit      07
   bitfield32_t   EEI06    :  BIT_1;  // Bit      06
   bitfield32_t   EEI05    :  BIT_1;  // Bit      05
   bitfield32_t   EEI04    :  BIT_1;  // Bit      04
   bitfield32_t   EEI03    :  BIT_1;  // Bit      03
   bitfield32_t   EEI02    :  BIT_1;  // Bit      02
   bitfield32_t   EEI01    :  BIT_1;  // Bit      01
   bitfield32_t   EEI00    :  BIT_1;  // Bit      00

}  DMA_EEIRL_F_T;

typedef union DMA_EEIRL_Tag
{
   DMA_EEIRL_F_T  F;
   uint32_t       U32;

}  DMA_EEIRL_T;

//=============================================================================
// ID - eDMA Set Enable Request Register (DMA_SERQR)
//
// Base Offset : 0000 0018 H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// SERQ        [06:00]    rw  Set enable request.
//                              0-63 Set the corresponding bit in DMA_ERQL
//                              64-127 Set all bits in DMA_ERQL
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_SERQR_F_Tag
{
   bitfield8_t             :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   SERQ      :  BIT_7;  // Bits [06:00]

}  DMA_SERQR_F_T;

typedef union DMA_SERQR_Tag
{
   DMA_SERQR_F_T  F;
   uint8_t        U8;

}  DMA_SERQR_T;

//=============================================================================
// ID - eDMA Clear Enable Request Register (DMA_CERQR)
//
// Base Offset : 0000 0019 H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// CERQ        [06:00]    rw  Clear enable request.
//                              0-63 Clear the corresponding bit in DMA_ERQL
//                              64-127 Clear all bits in DMA_ERQL 
//
// Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_CERQR_F_Tag
{
   bitfield8_t             :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   CERQ      :  BIT_7;  // Bits [06:00]

}  DMA_CERQR_F_T;

typedef union DMA_CERQR_Tag
{
   DMA_CERQR_F_T  F;
   uint8_t        U8;

}  DMA_CERQR_T;

//=============================================================================
// ID - eDMA Set Enable Error Interrupt Register (DMA_SEEIR)
//
// Base Offset : 0000 001A H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// SEEI        [06:00]    rw  Set enable error interrupt.
//                              0-63 Set the corresponding bit in DMA_EEIRL
//                              64-127 Set all bits in DMA_EEIRL 
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_SEEIR_F_Tag
{
   bitfield8_t             :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   SEEI      :  BIT_7;  // Bits [06:00]

}  DMA_SEEIR_F_T;

typedef union DMA_SEEIR_Tag
{
   DMA_SEEIR_F_T  F;
   uint8_t        U8;

}  DMA_SEEIR_T;

//=============================================================================
// ID - eDMA Clear Enable Error Interrupt Register (DMA_CEEIR)
//
// Base Offset : 0000 001B H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// CEEI        [06:00]    rw  Clear enable error interrupt.
//                              0-63 Clear the corresponding bit in DMA_EEIRL
//                              64-127 Clear all bits in DMA_EEIRL 
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_CEEIR_F_Tag
{
   bitfield8_t             :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   CEEI      :  BIT_7;  // Bits [06:00]

}  DMA_CEEIR_F_T;

typedef union DMA_CEEIR_Tag
{
   DMA_CEEIR_F_T  F;
   uint8_t        U8;

}  DMA_CEEIR_T;

//=============================================================================
// ID - eDMA Clear Interrupt Request Register (DMA_CIRQR)
//
// Base Offset : 0000 001C H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// CINT        [06:00]    rw  Clear interrupt request.
//                              0-63 Clear the corresponding bit in DMA_IRQRL
//                              64-127 Clear all bits in DMA_IRQRL 
//
// Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_CIRQR_F_Tag
{
   bitfield8_t             :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   CINT      :  BIT_7;  // Bits [06:00]

}  DMA_CIRQR_F_T;

typedef union DMA_CIRQR_Tag
{
   DMA_CIRQR_F_T  F;
   uint8_t        U8;

}  DMA_CIRQR_T;

//=============================================================================
// ID - eDMA Clear Error Register (DMA_CER)
//
// Base Offset : 0000 001D H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// CERR        [06:00]    rw  Clear error indicator.
//                              0-63 Clear the corresponding bit in
//                              DMA_ERQRH or DMA_ERQRL
//                              64-127 Clear all bits in DMA_ERQRH and
//                              DMA_ERQRL
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_CER_F_Tag
{
   bitfield8_t             :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   CERR      :  BIT_7;  // Bits [06:00]

}  DMA_CER_F_T;

typedef union DMA_CER_Tag
{
   DMA_CER_F_T F;
   uint8_t     U8;

}  DMA_CER_T;

//=============================================================================
// ID - eDMA Set START Bit Register (DMA_SSBR)
//
// Base Offset : 0000 001E H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// SSRT       [06:00]    rw  Set START bit (channel service request).
//                              0-63 Set the corresponding channel’s
//                              TCD.START
//                              64-127 Set all TCD.START bits
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_SSBR_F_Tag
{
   bitfield8_t         :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   SSRT  :  BIT_7;  // Bits [06:00]

}  DMA_SSBR_F_T;

typedef union DMA_SSBR_Tag
{
   DMA_SSBR_F_T   F;
   uint8_t        U8;

}  DMA_SSBR_T;

//=============================================================================
// ID - eDMA Clear DONE Status Bit Register (DMA_CDSBR)
//
// Base Offset : 0000 001F H
//
// Reset Value : 00 H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// 0                07     r  Reserved.
//
// CDNE        [06:00]    rw  Clear DONE status bit.
//                              0-63 Clear the corresponding channel’s
//                              DONE bit
//                              64-127 Clear all TCD DONE bits
//
// Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_CDSBR_F_Tag
{
   bitfield8_t             :  BIT_1;  // Bit      07 is reserved
   bitfield8_t   CDNE      :  BIT_7;  // Bits [06:00]

}  DMA_CDSBR_F_T;

typedef union DMA_CDSBR_Tag
{
   DMA_CDSBR_F_T  F;
   uint8_t        U8;

}  DMA_CDSBR_T;

//=============================================================================
// ID - eDMA Interrupt Request Registers (DMA_IRQRL)
//
// Base Offset : 0000 0024 H  (DMA_IRQRL)
//
// Reset Value : 0000 0000 H  (DMA_IRQRL)
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// INTn        [31:00]    rw  eDMA interrupt request n.
//                              0 The interrupt request for channel n is
//                                cleared.
//                              1 The interrupt request for channel n is
//                                active.
//
// Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_IRQRL_F_Tag
{
   bitfield32_t   INT31    :  BIT_1;  // Bit      31
   bitfield32_t   INT30    :  BIT_1;  // Bit      30
   bitfield32_t   INT29    :  BIT_1;  // Bit      29
   bitfield32_t   INT28    :  BIT_1;  // Bit      28
   bitfield32_t   INT27    :  BIT_1;  // Bit      27
   bitfield32_t   INT26    :  BIT_1;  // Bit      26
   bitfield32_t   INT25    :  BIT_1;  // Bit      25
   bitfield32_t   INT24    :  BIT_1;  // Bit      24
   bitfield32_t   INT23    :  BIT_1;  // Bit      23
   bitfield32_t   INT22    :  BIT_1;  // Bit      22
   bitfield32_t   INT21    :  BIT_1;  // Bit      21
   bitfield32_t   INT20    :  BIT_1;  // Bit      20
   bitfield32_t   INT19    :  BIT_1;  // Bit      19
   bitfield32_t   INT18    :  BIT_1;  // Bit      18
   bitfield32_t   INT17    :  BIT_1;  // Bit      17
   bitfield32_t   INT16    :  BIT_1;  // Bit      16
   bitfield32_t   INT15    :  BIT_1;  // Bit      15
   bitfield32_t   INT14    :  BIT_1;  // Bit      14
   bitfield32_t   INT13    :  BIT_1;  // Bit      13
   bitfield32_t   INT12    :  BIT_1;  // Bit      12
   bitfield32_t   INT11    :  BIT_1;  // Bit      11
   bitfield32_t   INT10    :  BIT_1;  // Bit      10
   bitfield32_t   INT09    :  BIT_1;  // Bit      09
   bitfield32_t   INT08    :  BIT_1;  // Bit      08
   bitfield32_t   INT07    :  BIT_1;  // Bit      07
   bitfield32_t   INT06    :  BIT_1;  // Bit      06
   bitfield32_t   INT05    :  BIT_1;  // Bit      05
   bitfield32_t   INT04    :  BIT_1;  // Bit      04
   bitfield32_t   INT03    :  BIT_1;  // Bit      03
   bitfield32_t   INT02    :  BIT_1;  // Bit      02
   bitfield32_t   INT01    :  BIT_1;  // Bit      01
   bitfield32_t   INT00    :  BIT_1;  // Bit      00

}  DMA_IRQRL_F_T;

typedef union DMA_IRQRL_Tag
{
   DMA_IRQRL_F_T  F;
   uint32_t      U32;

}  DMA_IRQRL_T;

//=============================================================================
// ID - eDMA Error Registers (DMA_ERL)
//
// Base Offset : 0000 002C H  (DMA_ERL)
//
// Reset Value : 0000 0000 H  (DMA_ERL)
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// ERRn        [31:00]    rw  eDMA Error n.
//                              0 An error in channel n has not occurred.
//                              1 An error in channel n has occurred.
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_ERL_F_Tag
{
   bitfield32_t   ERR31    :  BIT_1;  // Bit      31
   bitfield32_t   ERR30    :  BIT_1;  // Bit      30
   bitfield32_t   ERR29    :  BIT_1;  // Bit      29
   bitfield32_t   ERR28    :  BIT_1;  // Bit      28
   bitfield32_t   ERR27    :  BIT_1;  // Bit      27
   bitfield32_t   ERR26    :  BIT_1;  // Bit      26
   bitfield32_t   ERR25    :  BIT_1;  // Bit      25
   bitfield32_t   ERR24    :  BIT_1;  // Bit      24
   bitfield32_t   ERR23    :  BIT_1;  // Bit      23
   bitfield32_t   ERR22    :  BIT_1;  // Bit      22
   bitfield32_t   ERR21    :  BIT_1;  // Bit      21
   bitfield32_t   ERR20    :  BIT_1;  // Bit      20
   bitfield32_t   ERR19    :  BIT_1;  // Bit      19
   bitfield32_t   ERR18    :  BIT_1;  // Bit      18
   bitfield32_t   ERR17    :  BIT_1;  // Bit      17
   bitfield32_t   ERR16    :  BIT_1;  // Bit      16
   bitfield32_t   ERR15    :  BIT_1;  // Bit      15
   bitfield32_t   ERR14    :  BIT_1;  // Bit      14
   bitfield32_t   ERR13    :  BIT_1;  // Bit      13
   bitfield32_t   ERR12    :  BIT_1;  // Bit      12
   bitfield32_t   ERR11    :  BIT_1;  // Bit      11
   bitfield32_t   ERR10    :  BIT_1;  // Bit      10
   bitfield32_t   ERR09    :  BIT_1;  // Bit      09
   bitfield32_t   ERR08    :  BIT_1;  // Bit      08
   bitfield32_t   ERR07    :  BIT_1;  // Bit      07
   bitfield32_t   ERR06    :  BIT_1;  // Bit      06
   bitfield32_t   ERR05    :  BIT_1;  // Bit      05
   bitfield32_t   ERR04    :  BIT_1;  // Bit      04
   bitfield32_t   ERR03    :  BIT_1;  // Bit      03
   bitfield32_t   ERR02    :  BIT_1;  // Bit      02
   bitfield32_t   ERR01    :  BIT_1;  // Bit      01
   bitfield32_t   ERR00    :  BIT_1;  // Bit      00

}  DMA_ERL_F_T;

typedef union DMA_ERL_Tag
{
   DMA_ERL_F_T F;
   uint32_t    U32;

}  DMA_ERL_T;

//=============================================================================
// ID - eDMA Channel n Priority Registers (DMA_CPRn)
//
// Base Offset : 0x100 + n
//
// Reset Value : 1F H
//
// Field        Bits     Type Description
//=========== ========== ==== ===============================================
// ECP              07    rw  Enable channel preemption.
//                              0 Channel n cannot be suspended by a higher
//                                priority channel’s service request.
//                              1 Channel n can be temporarily suspended by
//                                the service request of a higher priority
//                                channel.
//
// 0                06     r  Reserved.
//
// GRPPRI      [05:04]     r  Channel n current group priority. Group
// [1:0]                      priority assigned to this channel group when
//                            fixed-priority arbitration is enabled. These
//                            two bits are read only; writes are ignored.
//
// CHPRI       [03:00]    rw  Channel n arbitration priority. Channel
// [3:0]                      priority when fixed-priority arbitration
//                            is enabled.
//
//  Note: The Bit numbering is as per the manual
//=============================================================================

typedef struct DMA_CPR_F_Tag
{
   bitfield8_t   ECP       :  BIT_1;  // Bit      07
   bitfield8_t             :  BIT_1;  // Bit 06 is reserved
   bitfield8_t   GRPPRI    :  BIT_2;  // Bits [05:04]
   bitfield8_t   CHPRI     :  BIT_4;  // Bits [03:00]

}  DMA_CPR_F_T;

typedef union DMA_CPR_Tag
{
   DMA_CPR_F_T F;
   uint8_t     U8;

}  DMA_CPR_T;

//=============================================================================
// ID - Transfer Control Descriptor (TCD)
//
// Base Offset : 0x1000
//
// Reset Value : --
//
// Field        Bits     Type Description
//========== =========== ==== ===============================================
// SADDR     [255:224]     -  Source address. Memory address pointing to
// [31:0]                     the source data.
//
// SMOD      [223:219]     -  Source address modulo.
//2[31:27]                      0 Source address modulo feature is disabled.
//                              non-0 This value defines a specific address
//                              range which is specified to be either the
//                              value after SADDR + SOFF calculation is
//                              performed or the original register value.
//                              The setting of this field provides the
//                              ability to easily implement a circular data
//                              queue. For data queues requiring
//                              power-of-2 "size" bytes, the queue should
//                              start at a 0-modulo-size address and the
//                              SMOD field should be set to the appropriate
//                              value for the queue, freezing the desired
//                              number of upper address bits. The value
//                              programmed into this field specifies the
//                              number of lower address bits that are
//                              allowed to change. For this circular queue
//                              application, the SOFF is typically set to
//                              the transfer size to implement
//                              post-increment addressing with the
//                              SMOD function constraining the addresses
//                              to a 0-modulo-size range.
//
// SSIZE     [218:216]     -  Source data transfer size.
//2[26:24]                      000 8-bit
//                              001 16-bit
//                              010 32-bit
//                              011 64-bit
//                              100 16-byte (32-bit implementations only)
//                              101 32-byte (if supported by the platform)
//                              110 Reserved
//                              111 Reserved
//                              The attempted specification of a 64-bit source size in a
//                              32-bit AMBA AHB bus implementation produces a
//                              configuration error. Likewise, the attempted
//                              specification of a 16-byte source size in a 64-bit AMBA
//                              AHB bus implementation generates a configuration
//                              error. The attempted specification of a 32-byte burst on
//                              platforms that do not support such a transfer type will
//                              result in a configuration error.
//
// DMOD      [215:211]     -  Destination address modulo.
//2[23:19]
//
// DSIZE     [210:208]     -  Destination data transfer size.
//2[18:16]
//
// SOFF      [207:192]     -  Source address signed offset. Sign-extended
//2[15: 0]                    offset applied to the current source address
//                            to form the next-state value as each source
//                            read is completed.
//
// NBYTES    [191:160]     -  Inner "minor" byte transfer count. Number of
//3[31: 0]                    bytes to be transferred in each service request
//                            of the channel. As a channel is activated, the
//                            contents of the appropriate TCD is loaded into
//                            the eDMA engine, and the appropriate reads and
//                            writes performed until the complete byte
//                            transfer count has been transferred. This is
//                            an indivisible operation and cannot be stalled
//                            or halted. Once the minor count is exhausted,
//                            the current values of the SADDR and DADDR are
//                            written back into the local memory, the major
//                            iteration count is decremented and restored
//                            to the local memory. If the major iteration
//                            count is completed, additional processing
//                            is performed.
//                            The nbytes value 0x0000_0000 is interpreted as
//                            0x1_0000_0000, thus specifying a 4 GB transfer.
//
// SLAST     [159:128]     -  Last source address adjustment.Adjustment value
//4[31: 0]                    added to the source address at the completion
//                            of the outer major iteration count. This value
//                            can be applied to "restore" the source address
//                            to the initial value, or adjust the address to
//                            reference the next data structure.
//
// DADDR      [127:96]     -  Destination address. Memory address pointing
//5[31: 0]                    to the destination data.
//
// CITER.           95     -  Enable channel-to-channel linking on minor
// E_LINK                     loop complete. As the channel completes the
//6    31                     inner minor loop, this flag enables the
//                            linking to another channel, defined by
//                            CITER.LINKCH[0:5]. The link target channel
//                            initiates a channel service request via an
//                            internal mechanism that sets the TCD.START
//                            bit of the specified channel. If channel
//                            linking is disabled, the CITER value is
//                            extended to 15 bits in place of a link channel
//                            number. If the major loop is exhausted, this
//                            link mechanism is suppressed in favor of
//                            the MAJOR.E_LINK channel linking.
//
//                              0 The channel-to-channel linking is
//                                disabled.
//                              1 The channel-to-channel linking is
//                                enabled.
//                            Note: This bit must be equal to the
//                                 BITER.E_LINK bit otherwise a
//                                 configuration error will be
//                                 reported.
//
// CITER      [94:89]     -  Current "major" iteration count or link channel
//6[30:16]                    number. If channel-to-channel linking is
// LINKCH                     disabled (TCD.CITER.E_LINK = 0), then
//6[30:25]                      - No channel-to-channel linking (or chaining)
//                                is performed after the inner minor loop
//                                is exhausted.TCD bits [161:175] are used to
//                                form a 15-bit CITER field. otherwise
//                              - After the minor loop is exhausted, the eDMA
//                                engine initiates a channel service request
//                                at the channel defined by CITER.LINKCH[5:0]
//                                by setting that channel’s TCD.START bit.
//                            Note: The value contained in citer.linkch[5:0] must 
//                                  not exceed the number of implemented channels.
//
// CITER       [88:80]     -  Current "major" iteration count. This 9 or
//6[24:16]                    15-bit count represents the current major loop
//                            count for the channel. It is decremented each
//                            time the minor loop is completed and updated
//                            in the transfer control descriptor memory.
//                            Once the major iteration count is exhausted,
//                            the channel performs a number of operations
//                            (for example, final source and destination
//                            address calculations), optionally generating
//                            an interrupt to signal channel completion
//                            before reloading the CITER field from the
//                            beginning iteration count (BITER) field.
//                            Note: When the CITER field is initially
//                                loaded by software, it must be set to
//                                the same value as that contained in
//                                the BITER field.
//                            Note: If the channel is configured to execute
//                                 a single service request, the initial
//                                 values of BITER and CITER should be
//                                 0x0001.
//
// DOFF        [79:64]     -  Destination address signed offset.
//6[15: 0]                    Sign-extended offset applied to the
//                            current destination address to form the
//                            next-state value as each destination
//                            write is completed.
//
// DLAST_      [63:32]     -  Last destination address adjustment or the
// SGA                        memory address for the next transfer control
//7[31: 0]                    descriptor to be loaded into this channel
//                            (scatter/gather). If scatter/gather
//                            processing for the channel is disabled
//                            (TCD.E_SG = 0) then
//
//                              - Adjustment value added to the destination
//                                address at the completion of the outer
//                                major iteration count. This value can be
//                                applied to "restore" the destination
//                                address to the initial value, or adjust
//                                the address to reference the next data
//                                structure.Otherwise
//                              - This address points to the beginning of a
//                                0-modulo-32 region containing the next
//                                transfer control descriptor to be loaded
//                                into this channel. This channel reload is
//                                performed as the major iteration count
//                                completes. The scatter/gather address must
//                                be 0-modulo-32, otherwise a configuration
//                                error is reported.
//
// BITER.           31     -  This is the initial value copied into the 
// E_LINK                     citer.e_link field when the major loop is 
//8    31                     completed.The citer.e_link field controls 
//                            channel linking during channel execution. This 
//                            bit must be equal to the citer.e_link bit otherwise
//                            a configuration error will be reported.
//
//                              0 The channel-to-channel linking is
//                                disabled.
//                              1 The channel-to-channel linking is
//                                enabled.
//
// BITER       [30:25]     -  Beginning "major" iteration count or link
//8[30:16]                    channel number. If channel-to-channel
//  or                        linking is disabled (TCD.BITER.E_LINK = 0),
// LINKCH                     then
//8[30:25]                      - No channel-to-channel linking
//                                (or chaining) is performed after the
//                                inner minor loop is exhausted. TCD bits
//                                [225:239] are used to form a 15-bit
//                                BITER field. Otherwise
//                              - After the minor loop is exhausted, the
//                                eDMA engine initiates a channel service
//                                request at the channel, defined by
//                                BITER.LINKCH[0:5], by setting that
//                                channel’s TCD.START bit.
//                            Note: The value contained in biter.linkch[5:0] must not
//                                  exceed the number of implemented channels.
//
// BITER       [24:16]     -  Beginning major iteration count. This 9- or 
//8[24:16]                    15-bit count represents the beginning major
//                            loop count for the channel. As the major iteration
//                            count is exhausted, the contents of the entire 16-bit
//                            biter entry is reloaded into the 16-bit citer entry.
//                            When the biter field is initially loaded by software, it
//                            must be set to the same value as that contained in the
//                            citer field.
//                            Note: If the channel is configured to execute a single
//                                  service request, the initial values of biter 
//                                  and citer should be 0x0001.
//
// BWC         [15:14]     -  Bandwidth control. This two-bit field provides
//8[15:14]                    a mechanism to effectively throttle the
//                            amount of bus bandwidth consumed by the eDMA.
//                            In general, as the eDMA processes the inner
//                            minor loop, it continuously generates
//                            read/write sequences until the minor count
//                            is exhausted. This field forces the eDMA to
//                            stall after the completion of each
//                            read/write access to control the bus request
//                            bandwidth seen by the crossbar switch (XBAR).
//                            To minimize start-up latency, bandwidth control 
//                            stalls are suppressed for the first two AHB bus 
//                            cycles and after the last write of each minor loop.
//                            The dynamic priority elevation setting elevates the
//                            priority of the DMA as seen by the cross-bar
//                            arbitration switch for the executing channel. Dynamic
//                            priority elevation is suppressed during the first two
//                            AHB bus cycles.
//                              00 No eDMA engine stalls
//                              01 Dynamic priority elevation
//                              10 eDMA engine stalls for 4 cycles after
//                                 each r/w
//                              11 eDMA engine stalls for 8 cycles after
//                                 each r/w
//
// MAJOR.      [13:08]     -  Link channel number.
// LINKCH                     If channel-to-channel linking on major
//8[13:08]                    loop complete is disabled
//                            (TCD.MAJOR.E_LINK = 0) then
//                              - No channel-to-channel linking
//                                (or chaining) is performed after
//                                the outer major loop counter
//                                is exhausted. Otherwise
//                              - After the major loop counter is
//                                exhausted, the eDMA engine initiates
//                                a channel service request at the
//                                channel defined by MAJOR.LINKCH[0:5]
//                                by setting that channel’s TCD.START
//                                bit.
//                                Note: The value contained in major.linkch[5:0] 
//                                      must not exceed the number of implemented 
//                                      channels.
//
// DONE             07     -  Channel done. This flag indicates the eDMA
//8    07                     has completed the outer major loop. It is
//                            set by the eDMA engine as the CITER count
//                            reaches zero; it is cleared by software, or
//                            the hardware when the channel is activated.
//                            NOTE: This bit must be cleared in order to
//                                  write the MAJOR.E_LINK or E_SG bits.
//
// ACTIVE           06     -  Channel active. This flag signals the channel
//8    06                     is currently in execution. It is set when
//                            channel service begins, and is cleared by the
//                            eDMA engine as the inner minor loop
//                            completes or if any error condition is
//                            detected.
//
// MAJOR.           05     -  Enable channel-to-channel linking on major
// E_LINK                     loop complete. As the channel completes
//8    05                     the outer major loop, this flag enables the
//                            linking to another channel, defined by
//                            MAJOR.LINKCH[0:5]. The link target channel
//                            initiates a channel service request via an
//                            internal mechanism that sets the TCD.START
//                            bit of the specified channel.
//                            NOTE: To support the dynamic linking
//                                  coherency model, this field is forced
//                                  to zero when written to while the
//                                  TCD.DONE bit is set.
//                              0 The channel-to-channel linking is disabled.
//                              1 The channel-to-channel linking is enabled.
//
// E_SG             04     -  Enable scatter/gather processing. As the
//8    04                     channel completes the outer major loop,
//                            this flag enables scatter/gather
//                            processing in the current channel. If
//                            enabled, the eDMA engine uses DLAST_SGA
//                            as a memory pointer to a 0-modulo-32
//                            address containing a 32-byte data
//                            structure which is loaded as the transfer
//                            control descriptor into the local memory.
//
//                            NOTE: To support the dynamic scatter/gather
//                                  coherency model, this field is forced to
//                                  zero when written to while the TCD.DONE
//                                  bit is set.
//                              0 The current channel’s TCD is "normal"
//                                format.
//                              1 The current channel’s TCD specifies a
//                                scatter gather format. The DLAST_SGA field
//                                provides a memory pointer to the next TCD
//                                to be loaded into this channel after the
//                                outer major loop completes its execution.
//
// D_REQ            03     -  Disable request. If this flag is set,
//8    03                     the eDMA hardware automatically clears the
//                            corresponding DMAERQ bit when the current
//                            major iteration count reaches zero.
//                              0 The channel’s DMAERQ bit is not affected.
//                              1 The channel’s DMAERQ bit is cleared when
//                                the outer major loop is complete.
//
// INT_HALF         02     -  Enable an interrupt when major counter is
//8    02                     half complete. If this flag is set, the
//                            channel generates an interrupt request by
//                            setting the appropriate bit in the
//                            DMA_IRQRL when the current major iteration
//                            count reaches the halfway point.
//                            Specifically, the comparison performed by
//                            the eDMA engine is (CITER == (BITER >> 1)).
//                            This halfway point interrupt request is
//                            provided to support double-buffered
//                            (aka ping-pong) schemes, or other types of
//                            data movement where the processor needs an
//                            early indication of the transfer’s progress.
//                            The halfway complete interrupt is disabled when 
//                            biter values are less than two.
//                              0 The half-point interrupt is disabled.
//                              1 The half-point interrupt is enabled.
//
// INT_MAJ          01     -  Enable an interrupt when major iteration
//8    01                     count completes. If this flag is set,
//                            the channel generates an interrupt request
//                            by setting the appropriate bit in the
//                            DMA_IRQRL when the current major iteration
//                            count reaches zero.
//                              0 The end-of-major loop interrupt is
//                                disabled.
//                              1 The end-of-major loop interrupt is
//                                enabled.
//
// START           00      -  Channel start. If this flag is set, the
//8    00                     channel is requesting service. The eDMA
//                            hardware automatically clears this flag
//                            after the channel begins execution.
//                              0 The channel is not explicitly started.
//                              1 The channel is explicitly started via
//                                a software initiated service request.
//
// Note: The Bit numbering is as per the manual
//       
//=============================================================================

typedef struct DMA_Second_32Bit_F_Tag
{
   bitfield32_t   SMOD      :  BIT_5;  // Bits  [31:27]
   bitfield32_t   SSIZE     :  BIT_3;  // Bits  [26:24]
   bitfield32_t   DMOD      :  BIT_5;  // Bits  [23:19]
   bitfield32_t   DSIZE     :  BIT_3;  // Bits  [18:16]
   bitfield32_t   SOFF      :  BIT_16; // Bits  [15:00]

}  DMA_Second_32Bit_F_T;

typedef union DMA_Second_32Bit_Tag
{
   DMA_Second_32Bit_F_T F;
   uint16_t             U16[DMA_ARRAY_SIZE_2];
   uint32_t             U32;

}  DMA_Second_32Bit_T;

typedef struct DMA_Third_32Bit_Tag
{
   uint32_t             NBYTES;

} DMA_Third_32Bit_T;

typedef struct DMA_Sixth_32Bit_F_Tag
{
   bitfield32_t   CITER_E_LINK :  BIT_1;  // Bit      31
   bitfield32_t   CITER_LINKCH :  BIT_6;  // Bits  [30:25]
   bitfield32_t   CITER        :  BIT_9;  // Bits  [24:16]
   bitfield32_t   DOFF         :  BIT_16; // Bits  [15:00]

}  DMA_Sixth_32Bit_F_T;

typedef union DMA_Sixth_32Bit_Tag
{
   DMA_Sixth_32Bit_F_T  F;
   uint16_t             U16[DMA_ARRAY_SIZE_2];
   uint32_t             U32;

}  DMA_Sixth_32Bit_T;

typedef struct DMA_Eighth_32Bit_F_Tag
{
   bitfield32_t   BITER_E_LINK :  BIT_1;  // Bit       31
   bitfield32_t   BITER_LINKCH :  BIT_6;  // Bits  [30:25]
   bitfield32_t   BITER        :  BIT_9;  // Bits  [24:16]
   bitfield32_t   BWC          :  BIT_2;  // Bits  [15:14]
   bitfield32_t   MAJOR_LINKCH :  BIT_6;  // Bits  [13:08]
   bitfield32_t   DONE         :  BIT_1;  // Bit       07
   bitfield32_t   ACTIVE       :  BIT_1;  // Bit       06
   bitfield32_t   MAJOR_E_LINK :  BIT_1;  // Bit       05
   bitfield32_t   E_SG         :  BIT_1;  // Bit       04
   bitfield32_t   D_REQ        :  BIT_1;  // Bit       03
   bitfield32_t   INT_HALF     :  BIT_1;  // Bit       02
   bitfield32_t   INT_MAJ      :  BIT_1;  // Bit       01
   bitfield32_t   START        :  BIT_1;  // Bit       00

}  DMA_Eighth_32Bit_F_T;

typedef union DMA_Eighth_32Bit_Tag
{
   DMA_Eighth_32Bit_F_T F;
   uint16_t             U16[DMA_ARRAY_SIZE_2];
   uint32_t             U32;

}  DMA_Eighth_32Bit_T;

typedef struct DMA_TCD_F_Tag
{
   uint32_t             SADDR;
   DMA_Second_32Bit_T   F_2;
   DMA_Third_32Bit_T    F_3;
   uint32_t             SLAST;
   uint32_t             DADDR;
   DMA_Sixth_32Bit_T    F_6;
   uint32_t             DLAST_SGA;
   DMA_Eighth_32Bit_T   F_8;

}  DMA_TCD_F_T;


typedef union DMA_TCD_Tag
{
   DMA_TCD_F_T F;
   uint32_t    U32[DMA_ARRAY_SIZE_8];

}  DMA_TCD_T;

//=============================================================================
//  eDMA Module Register Structure
//=============================================================================

typedef volatile struct DMA_Tag
{
   DMA_CR_T             CR;                              // 0x0000 - 0x0003
   DMA_ESR_T            ESR;                             // 0x0004 - 0x0007
   uint8_t              unused0[DMA_RESERVED_4];         // 0x0008 - 0x000B
   DMA_ERQRL_T          ERQRL;                           // 0x000C - 0x000F
   uint8_t              unused1[DMA_RESERVED_4];         // 0x0010 - 0x0013
   DMA_EEIRL_T          EEIRL;                           // 0x0014 - 0x0017
   DMA_SERQR_T          SERQR;                           // 0x0018
   DMA_CERQR_T          CERQR;                           // 0x0019
   DMA_SEEIR_T          SEEIR;                           // 0x001A
   DMA_CEEIR_T          CEEIR;                           // 0x001B
   DMA_CIRQR_T          CIRQR;                           // 0x001C
   DMA_CER_T            CER;                             // 0x001D
   DMA_SSBR_T           SSBR;                            // 0x001E
   DMA_CDSBR_T          CDSBR;                           // 0x001F
   uint8_t              unused2[DMA_RESERVED_4];         // 0x0020 - 0x0023
   DMA_IRQRL_T          IRQRL;                           // 0x0024 - 0x0027
   uint8_t              unused3[DMA_RESERVED_4];         // 0x0028 - 0x002B
   DMA_ERL_T            ERL;                             // 0x002C - 0x002F
   uint8_t              unused4[DMA_RESERVED_208];       // 0x0030 - 0x00FF
   DMA_CPR_T            CPR[DMA_CPR_QUANTITY];           // 0x0100 - 0x011F
   uint8_t              unused5[DMA_RESERVED_3808];      // 0x0120 - 0x0FFF
   DMA_TCD_T            TCD[DMA_TCD_QUANTITY];           // 0x1000 - 0x13FC
   uint8_t              unused6[DMA_RESERVED_1024];      // 0x1400 - 0x17FF

}  DMA_T;

#endif // HW_DMA_H

