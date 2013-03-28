#ifndef HW_XBAR_MPC5644_H
#define HW_XBAR_MPC5644_H

//=============================================================================
// Only Include hw_def.h for the hardware definition files
//=============================================================================
#include "reuse.h"
//=============================================================================
// Master Priority Registers (XBAR_MPRn)
//
// Field        Bits    Description
// ============ ======= ========================================================
// 0             31     r Reserved, must be cleared
//
// MSTR7        [26:24] rw Master 7 Priority.
//                      These bits set the arbitration priority for master port 7
//                      on the associated slave port.
//                      %000 = This master has the highest priority
//                      %001 = This master has the second highest priority
//                      %100 = This master has the lowest priority
//                      %101 -111 = Reserved
//
// 0             25     r Reserved, must be cleared
//
// MSTR6        [26:24] rw Master 6 Priority.
//                      These bits set the arbitration priority for master port 6
//                      on the associated slave port.
//                      %000 = This master has the highest priority
//                      %001 = This master has the second highest priority
//                           .
//                           .
//                      %100 = This master has the lowest priority
//                      %101 -111 = Reserved
//
// 0            [23:19] r  Reserved , must be cleared
//
// MSTR4        [18:16] rw Master 4 Priority.
//                      These bits set the arbitration priority for master port 4
//                      on the associated slave port.
//                      %000 = This master has the highest priority
//                      %001 = This master has the second highest priority
//                           .
//                           .
//                      %100 = This master has the lowest priority
//                      %101 - 111 = Reserved
//
// 0               [15:7] r Reserved, must be cleared
//
// MSTR1        [6:4] rw Master 1 Priority.
//                      These bits set the arbitration priority for master port 1
//                      on the associated slave port.
//                      %000 = This master has the highest priority
//                      %001 = This master has the second highest priority
//                        .
//                        .
//                      %111 = This master has the lowest priority
//
// 0                [3]  r Reserved, must be cleared
//
// MSTR0        [2:0] rw Master 0 Priority.
//                      These bits set the arbitration priority for master port 0
//                      on the associated slave port.
//                      %000 = This master has the highest priority
//                      %001 = This master has the second highest priority
//                          .
//                          .
//                      %111 = This master has the lowest priority
//
// Note: The Bit numbering is for the software implementation
//          not a copy from the manual
//=============================================================================
typedef struct XBAR_MPR_F_Tag
{
   bitfield32_t               : BIT_1; // reserved
   bitfield32_t   MSTR7       : BIT_3; // Master 7 Priority
   bitfield32_t               : BIT_1; // reserved
   bitfield32_t   MSTR6       : BIT_3; // Master 6 Priority
   bitfield32_t               : BIT_5; // reserved
   bitfield32_t   MSTR4       : BIT_3; // Master 4 Priority
   bitfield32_t               : BIT_9; // reserved
   bitfield32_t   MSTR1       : BIT_3; // Master 1 Priority
   bitfield32_t               : BIT_1; // reserved
   bitfield32_t   MSTR0       : BIT_3; // Master 0 Priority

}  XBAR_MPR_F_T;

// @XBAR_MPR_T | XBAR MPR type
typedef union XBAR_MPR_Tag
{
   XBAR_MPR_F_T F;
   uint32_t     U32;

} XBAR_MPR_T;

//=============================================================================
// Slave General-Purpose Control Registers (XBAR_SGPCRn)
//
// Field        Bits    Description
// ============ ======= ========================================================
// RO           [31]    Read Only.
//                      This bit forces slave registers to be read only after
//                      to a 1.
//                      %0 = This slave register is writeable
//                      %1 = This slave register is Read Only
//
// 0            [30:24]  r Reserved, must be cleared
//
// HPEx         [23:16] rw High Priority Enable - These bits are used to enable
//                      the mX_high_priority inputs for the respective master.
//                      These bits are initialized by hardware reset.
//                      The reset value is 0
//                      0 = The mX_high_priority input is disabled on this
//                          slave port
//                      1 = The mX_high_priority input is enabled on this
//                          slave port.
//
// 0            [15:10] r Reserved, must be cleared
//
// ARB          [9:8] rw Arbitration Mode.
//                      These bits set the arbitration policy for the slave port.
//                      %00 = Fixed priority  using MPR
//                      %01 = Round-robin priority
//                      %1x = Reserved
//
// 0              [7:6] r  Reserved, must be cleared
//
// PCTL         [5:4] rw Parking Control.
//                      These bits set the parking algorithm for the slave port.
//                      %00 = Park on master defined by PARK field
//                      %01 = Park on last master to own.
//                      %10 = Park on no master with outputs in safe state.
//                      %11 = Reserved
//
// 0               3    Reserved, must be cleared
//
// PARK         [2:0] rw Park
//                      These bits set the master on which to park when PCTL set
//                      to 00.
//                      %000 = Park on Master Port 0 (e200z446n3 core instruction).
//                      %001 = Park on Master Port 1 (e200z446n3 core Load/Store)
//                      %010 = Reserved
//                      %011 = Reserved
//                      %100 = Park on Master Port 4.
//                      %101 = Reserved
//                      %110 = Park on Master Port 6 (FlexRay)
//                      %111 = Park on Master Port 7 (EBI)
//
// Note: The Bit numbering is for the software implementation
//          not a copy from the manual
//=============================================================================
// @XBAR_SGPCR_T | XBAR SGPCR type
typedef struct XBAR_SGPCR_F_Tag
{
   bitfield32_t   RO    : BIT_1; // Read Only
   bitfield32_t         : BIT_7; // Reserved
   bitfield32_t   HPE7  : BIT_1; // High Priority Enable 7
   bitfield32_t   HPE6  : BIT_1; // High Priority Enable 6
   bitfield32_t         : BIT_1; // Reserved
   bitfield32_t   HPE4  : BIT_1; // High Priority Enable 4
   bitfield32_t         : BIT_2; // Reserved
   bitfield32_t   HPE1  : BIT_1; // High Priority Enable 1
   bitfield32_t   HPE0  : BIT_1; // High Priority Enable 0
   bitfield32_t         : BIT_6; // Reserved
   bitfield32_t   ARB   : BIT_2; // Arbitration Mode
   bitfield32_t         : BIT_2; // Reserved
   bitfield32_t   PCTL  : BIT_2; // Parking Control
   bitfield32_t         : BIT_1; // Reserved
   bitfield32_t   PARK  : BIT_3; // Park

}  XBAR_SGPCR_F_T;

typedef union XBAR_SGPCR_Tag
{
   XBAR_SGPCR_F_T F;
   uint32_t       U32;

} XBAR_SGPCR_T;

//=============================================================================
// XBAR_T
//=============================================================================
#define XBAR_RESERVED_0x0C    (0x000C)
#define XBAR_RESERVED_0xEC    (0x00EC)

// Slave ports are not in sequence.In order to maintain uniformity
// the slave port maximum is made as 8
#define XBAR_SLAVE_PORTS_MAX 8

typedef struct XBAR_SLAVE_PORT_Tag
{
   XBAR_MPR_T     MPR;                             // 0x0000 - 0x0003
   uint8_t        reserved_0[XBAR_RESERVED_0x0C];  // 0x0004 - 0x000F
   XBAR_SGPCR_T   SGPCR;                           // 0x0010 - 0x0013
   uint8_t        reserved_1[XBAR_RESERVED_0xEC];  // 0x0014 - 0x00FF
} XBAR_SLAVE_PORT_T;

typedef volatile struct XBAR_Tag
{
   XBAR_SLAVE_PORT_T SLAVE_PORT[XBAR_SLAVE_PORTS_MAX];  // 0x0000 - 0x07FF

}  XBAR_T;

#endif // HW_XBAR_MPC5644_H

