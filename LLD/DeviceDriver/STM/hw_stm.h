#ifndef HW_STM_H
#define HW_STM_H

#include "reuse.h"

#define  STM_RESERVED_0X0008  (0x0008)
#define  STM_RESERVED_0X0004  (0x0004)
#define  STM_CHANNEL_QANTITY  (4)
#define  STM_RESERVED_0X3FB0  (0x3FB0)
//=============================================================================
// ID - STM Control Register (STM_CR)
//
// Base Offset : 0000 0000H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
//============= ======== ==== =================================================
// 0             [31:16]   r  Reserved
//
// CPS           [15: 8]  rw  Counter Prescaler. Selects the clock divide value
//                            for the prescaler (1 - 256).
//                            0x00 = Divide system clock by 1
//                            0x01 = Divide system clock by 2
//                            ...
//                            0xFF = Divide system clock by 256
//
// 0             [ 7: 2]   r  Reserved
//
// FRZ                1   rw  Freeze. Allows the timer counter to be stopped when
//                            the device enters debug mode.
//                            0 = STM counter continues to run in debug mode.
//                            1 = STM counter is stopped in debug mode.
//
// TEN               0    rw  Timer Counter Enabled.
//                            0 = Counter is disabled.
//                            1 = Counter is enabled.
//=============================================================================


typedef struct STM_CR_F_Tag
{
   bitfield32_t                   :  BIT_16; // Bit  [31:16]  Reserved
   bitfield32_t   CPS             :  BIT_8;  // Bit  [15: 8]  Counter Prescaler.
   bitfield32_t                   :  BIT_6;  // Bits [ 7: 2]  Reserved
   bitfield32_t   FRZ             :  BIT_1;  // Bits      1   Freeze
   bitfield32_t   TEN             :  BIT_1;  // Bits      0   Timer Counter Enabled.

}  STM_CR_F_T;

typedef union STM_CR_Tag
{
   STM_CR_F_T         F;
   uint32_t           U32;

}  STM_CR_T;



//=============================================================================
// ID - STM Count Register (STM_CNT)
//
// Base Offset : 0x0004H
//
// Reset Value : 0x0000H
//
// Field        Bits     Type Description
//============= ======== ==== =================================================

typedef uint32_t    STM_CNT_T;


//=============================================================================
// ID - STM Channel Control Register (STM_CCRn)
//
// Base Offset : 0x10+0x10*n
//
// Reset Value : 0x0000H
//
// Field        Bits     Type Description
//============= ======== ==== =================================================
// 0             [31: 1]  r   Reserved
//
// CEN                0   rw  Channel Enable.
//                            0 = The channel is disabled.
//                            1 = The channel is enabled.
//=============================================================================

typedef struct STM_CCRn_F_Tag
{
   bitfield32_t                   :  BIT_31; // Bit  [31: 1]  Reserved
   bitfield32_t   CEN             :  BIT_1;  // Bit       0


}  STM_CCRn_F_T;

typedef union STM_CCRn_Tag
{
   STM_CCRn_F_T         F;
   uint32_t             U32;

}  STM_CCRn_T;


//=============================================================================
// ID - STM Channel Interrupt Register (STM_CIRn)
//
// Base Offset : 0x14+0x10*n
//
// Reset Value : 0x000H
//
// Field        Bits     Type Description
//============= ======== ==== =================================================
// 0             [31: 1]  r   Reserved
//
// CIF                0   rw  Channel Interrupt Flag. The flag and interrupt are
//                            cleared by writing a 1 to this bit. Writing a 0 has
//                            no effect.
//                            0 = No interrupt request.
//                            1 = Interrupt request due to a match on the channel.
//=============================================================================


typedef struct STM_CIRn_F_Tag
{
   bitfield32_t                   :  BIT_31; // Bit  [31: 1]  Reserved
   bitfield32_t   CIF             :  BIT_1;  // Bit       0


}  STM_CIRn_F_T;

typedef union STM_CIRn_Tag
{
   STM_CIRn_F_T         F;
   uint32_t             U32;

}  STM_CIRn_T;

//=============================================================================
// ID - STM Channel Compare Register (STM_CMPn)
//
// Base Offset : 0x18+0x10*n
//
// Reset Value : 0x0000
//
// Field        Bits     Type Description
//============= ======== ==== =================================================
// CMP           [31: 0]  rw  Compare value for channel n. If the STM_CCRn[CEN]
//                            bit is set and the STM_CMPn register matches the
//                            STM_CNT register, a channel interrupt request is
//                            generated and the STM_CIRn[CIF] bit is set
//=============================================================================

typedef uint32_t    STM_CMPn_T;

//=============================================================================
//  STM_Timer_Register_T
//=============================================================================

typedef struct STM_Timer_Register_Tag
{
   STM_CCRn_T    CCR;
   STM_CIRn_T    CIR;
   STM_CMPn_T    CMP;
   uint8_t       reserved_2[STM_RESERVED_0X0004];

}  STM_Timer_Register_T;


//=============================================================================
//  System Timer register  Structure

//  Note: STM Registers are not Bit Accessible.
//=============================================================================
typedef volatile struct STM_Tag
{
   STM_CR_T               CR;                               // 0X0000 - 0X0003
   STM_CNT_T              CNT;                              // 0x0004 - 0x0007
   uint8_t                reserved_1[STM_RESERVED_0X0008];  // 0x0008 - 0x000F
   STM_Timer_Register_T   Timer[STM_CHANNEL_QANTITY];       // 0x0010 - 0x004F
   uint8_t                reserved_3[STM_RESERVED_0X3FB0];  // 0x0050 - 0x3FFF

}  STM_T;



#endif // HW_STM_H
