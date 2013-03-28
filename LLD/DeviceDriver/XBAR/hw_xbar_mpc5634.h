#ifndef HW_XBAR_MPC5634_H
#define HW_XBAR_MPC5634_H

//=============================================================================
//=============================================================================
// Only Include hw_def.h for the hardware definition files
//=============================================================================
#include "reuse.h"

//=============================================================================
// Master Priority Registers (XBAR_MPRn)
// 
// Reset Value : 7654 3210 H
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// 0           [31]       r    Master Priority Register Reserved 
//                             This bit is reserved for future expansion. 
//                             It is read as zero and should be written
//                             with zero for upward compatibility.
// 
// MSTR7        [30:28]    rw  Master 7 Priority.
//                             These bits set the arbitration priority  
//                             for master port 7 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//
// 0           [27]       r    Master Priority Register Reserved 
//
// MSTR6       [26:24]    rw   Master 6 Priority.
//                             These bits set the arbitration priority  
//                             for master port 6 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//
// 0           [23]       r    Master Priority Register Reserved 
//
// MSTR5       [22:20]    rw   Master 5 Priority.
//                             These bits set the arbitration priority  
//                             for master port 5 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//
// 0           [19]       r    Master Priority Register Reserved 
//
// MSTR4       [18:16]    rw   Master 4 Priority.
//                             These bits set the arbitration priority  
//                             for master port 4 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//
// 0           [15]       r    Master Priority Register Reserved 
//
// MSTR3       [14:12]    rw   Master 3 Priority.
//                             These bits set the arbitration priority  
//                             for master port 3 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//
// 0           [11]       r    Master Priority Register Reserved 
//
// MSTR2       [10: 8]    rw   Master 2 Priority.
//                             These bits set the arbitration priority  
//                             for master port 2 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//
// 0           [7]       r    Master Priority Register Reserved 
//
// MSTR1       [6:4]     rw    Master 1 Priority.
//                             These bits set the arbitration priority  
//                             for master port 1 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//
// 0           [3]       r     Master Priority Register Reserved 
//
// MSTR0       [2:0]     rw    Master 0 Priority.
//                             These bits set the arbitration priority  
//                             for master port 0 on the associated slave port.
//                             These bits are initialized by hardware reset.
//                             000 = This master has the highest priority
//                                   when accessing the slave port.   
//                             111 = This master has the lowest priority
//                                   when accessing the slave port.                     
//=============================================================================
typedef struct XBAR_MPR_F_Tag
{
   bitfield32_t         : BIT_1; // Reserved 
   bitfield32_t         : BIT_3; // Master 7 Priority
   bitfield32_t         : BIT_1; // Reserved 
   bitfield32_t         : BIT_3; // Master 6 Priority
   bitfield32_t         : BIT_1; // Reserved 
   bitfield32_t         : BIT_3; // Master 5 Priority
   bitfield32_t         : BIT_1; // Reserved 
   bitfield32_t   MSTR4 : BIT_3; // Master 4 Priority
   bitfield32_t         : BIT_1; // Reserved 
   bitfield32_t         : BIT_3; // Master 3 Priority
   bitfield32_t         : BIT_1; // Reserved    
   bitfield32_t   MSTR2 : BIT_3; // Master 2 Priority
   bitfield32_t         : BIT_1; // Reserved 
   bitfield32_t   MSTR1 : BIT_3; // Master 1 Priority
   bitfield32_t         : BIT_1; // Reserved 
   bitfield32_t   MSTR0 : BIT_3; // Master 0 Priority

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
// Reset Value : 0000 00000 H
// Field        Bits     Type   Description
// ========== =========  ==== ==============================================
// RO           [31]      rw    Read Only
//                              This bit forces all slave port registers to 
//                              be read only.Once written to 1 it can only 
//                              be cleared by hardware reset.                    
//                              0 = This slave register is writeable
//                              1 = This slave register is Read Only
//
// HLP          [30]      rw    Halt Low Priority
//                              This bit is used to set the initial
//                              arbitration priority of the max_halt_request 
//                              input.
//                              0 = The max_halt_request input has the
//                                  highest priority for arbitration on 
//                                  this slave
//                              1 = The max_halt_request input has the
//                                  lowest initial priority for arbitration 
//                                  on this slave port.
//
// 0            [29:24]    r    Slave General Purpose Control Register Reserved
// 
// HPEx         [23:16]    rw   High Priority Enable
//                              These bits are used to enable the  
//                              mX_high_priority inputs for the respective master.
//                              0 = The mX_high_priority input is disabled on
//                                  this slave port
//                              1 = The mX_high_priority input is enabled on
//                                  this slave port.
//
// 0            [15:10]    r    Slave General Purpose Control Register Reserved 
//
// ARB          [9:8]      rw   Arbitration Mode.
//                              These bits set the arbitration policy for the 
//                              slave port.
//                              00 = Fixed priority  
//                              01 = Round-robin priority
//                              1x = Reserved
//
// 0             [7:6]     r    Slave General Purpose Control Register Reserved
//
// PCTL          [5:4]     rw   Parking Control.
//                              These bits determine the parking control used by 
//                              this slave port. 
//                              00 = Park on master defined by PARK field
//                              01 = Park on last master to own.
//                              10 = Park on no master with outputs in safe state.
//                              11 = Reserved
//
// 0             [3]       r    Slave General Purpose Control Register Reserved
//
// PARK         [2:0]      rw   Park
//                              These bits set the master on which to park when
//                              PCTL set to 00.                              
//                              000 = Park on Master Port 0.
//                              001 = Park on Master Port 1.
//                              010 = Park on Master Port 2.
//                              011 = Park on Master Port 3.  
//                              1xx = Illegal Master Port
//
//=============================================================================
// @XBAR_SGPCR_T | XBAR SGPCR type
typedef struct XBAR_SGPCR_F_Tag
{
   bitfield32_t   RO    : BIT_1; // Read Only
   bitfield32_t   HLP   : BIT_1; // Halt Low Priority   
   bitfield32_t         : BIT_6; // Reserved
   bitfield32_t         : BIT_1; // High Priority Enable 7
   bitfield32_t         : BIT_1; // High Priority Enable 6
   bitfield32_t         : BIT_1; // High Priority Enable 5
   bitfield32_t   HPE4  : BIT_1; // High Priority Enable 4
   bitfield32_t         : BIT_1; // High Priority Enable 3
   bitfield32_t   HPE2  : BIT_1; // High Priority Enable 2
   bitfield32_t   HPE1  : BIT_1; // High Priority Enable 1
   bitfield32_t   HPE0  : BIT_1; // High Priority Enable 0
   bitfield32_t         : BIT_6; // Reserved
   bitfield32_t   ARB   : BIT_2; // Arbitration Mode
   bitfield32_t         : BIT_2; // Reserved
   bitfield32_t   PCTL  : BIT_2; // Parking Control
   bitfield32_t         : BIT_1; 
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
#define XBAR_RESERVED_0    ((0x000F-0x0004) + 1 )
#define XBAR_RESERVED_1    ((0x00FF-0x0014) + 1 )
#define XBAR_RESERVED_2    ((0x02FF-0x0200) + 1 )
#define XBAR_RESERVED_3    ((0x06FF-0x0400) + 1 )
#define XBAR_SLAVE_PORTS_MAX 4
#define XBAR_MASTER_PORTS_MAX 3

typedef struct XBAR_SLAVE_PORT_Tag
{
   XBAR_MPR_T     MPR;                           // 0x0000 - 0x0003
   uint8_t        reserved_0[XBAR_RESERVED_0 ];  // 0x0004 - 0x000F
   XBAR_SGPCR_T   SGPCR;                         // 0x0010 - 0x0013
   uint8_t        reserved_1[XBAR_RESERVED_1];   // 0x0014 - 0x00FF
   
} XBAR_SLAVE_PORT_T;

typedef union XBAR_Tag
{
   volatile struct
   {
     XBAR_SLAVE_PORT_T SLAVE_PORT_0;                // 0x0000 - 0x00FF
     XBAR_SLAVE_PORT_T SLAVE_PORT_1;                // 0x0100 - 0x01FF
     uint8_t           reserved_2[XBAR_RESERVED_2]; // 0x0200 - 0x02FF
     XBAR_SLAVE_PORT_T SLAVE_PORT_3;                // 0x0300 - 0x03FF
     uint8_t           reserved_3[XBAR_RESERVED_3]; // 0x0400 - 0x06FF
     XBAR_SLAVE_PORT_T SLAVE_PORT_7;                // 0x0700 - 0x07FF
   } F ;
   
   volatile XBAR_SLAVE_PORT_T SLAVE_PORT[7];

}  XBAR_T;

#endif // HW_XBAR_MPC5634_H

