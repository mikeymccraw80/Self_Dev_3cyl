#ifndef HW_PIT_H
#define HW_PIT_H

#include "reuse.h"

#define PIT_CHANNEL_QUANTITY  (5)

#define PIT_RESERVED_0x00EC  (0x00EC)

#define PIT_RTI_MIN_VALUE    (32)
//=============================================================================
// ID - PIT Module Control Register (PITMCR)
//
// Base Offset : 0000 0000H
//
// Reset Value : 0000 0000H
//
// Field        Bits     Type Description
//============= ======== ==== =================================================
// 0            31:3     r    Reserved, read as zero	 
// 
// MDIS_RTI  2      rw        Module Disable - RTI section. This is used to 
//                            disable the RTI timer.This bit should be 
//                            enabled before any RTI setup is done
//                            0 = Clock for RTI is enabled (default)
//                            1 = Clock for RTI disabled
//                                  
// MDIS         1      rw     Module Disable - (PIT section).This is used to
//                            disable the standard timers.The RTI timer 
//                            is not affected by this bit. This bit should
//                            be enabled before any other setup is done.
//                            0 = Clock for PIT Timers is enabled (default)
//                            1 = Clock for PIT Timers is disabled
//
// FRZ           0            Freeze. Allows the timers to be stopped
//                            when the device enters debug mode.
//                            0 = Timers continue to run in debug mode.
//                            1 = Timers are stopped in debug mode
//
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================
typedef struct PIT_MCR_F_Tag
{
   bitfield32_t                   :  BIT_29; // Bit    [31:3]  Reserved
   bitfield32_t   MDIS_RTI        :  BIT_1;  // Bit     2      Module Disable-RTI section
   bitfield32_t   MDIS            :  BIT_1;  // Bits    1      Module Disable - PIT section
   bitfield32_t   FRZ             :  BIT_1;  // Bits    0      Freeze

}  PIT_MCR_F_T;

typedef union PIT_MCR_Tag
{
   PIT_MCR_F_T         F;
   uint32_t          U32;

}  PIT_MCR_T;

//=============================================================================
// ID - Timer Load Value Register ((LDVAL)
// Base Offset : 0x0F0, 0X100, 0X110, 0X120, 0X130 
//
// Reset Value : 0000 0000H
//
// Field        Bits  Type    Description
// ============ ======== ==== ================================================
// TSVn     [31:0]  rw        Time Start Value Bits. These bits set the
//                            timer start value.The timer will count down
//                            until it reaches 0, then it will generate an 
//                            interrupt and load this register value again. 
//                            Writing a new value to this register will not
//                            restart the timer, instead the value will 
//                            be loaded once the timer expires. To abort 
//                            the current cycle and start a timer period 
//                            with the new value, the timer must be
//                            disabled and enabled again 
//                               
//=============================================================================

typedef uint32_t    PIT_LDVAL_T;

//=============================================================================
// ID - Current Timer Value Register (CVAL)
// Base Offset :0X104 ,0X114 ,0X124 ,0X134 
//
// Reset Value : 0000 0000H 
//
// Field        Bits     Type   Description
// ============ ======== ==== =================================================
//TVLn       [31:0]    r        Current Timer Value. These bits represent 
//                              the current timer value. Note that the 
//                              timer uses a downcounter.  
//
//=============================================================================
typedef uint32_t    PIT_CVAL_T;

//=============================================================================
// ID - Timer Control Register (TCTRL)
// Base Offset :0X108,0X118,0X128,0X138 
// 
// Reset Value :0000 0000H  
//
// Field  Bits    Type Description
// ============ ======== ==== =================================================
// 0       [31:2]   r     Reserved, should be cleared.

// TIE       1       rw    Timer Interrupt Enable Bit.
//                         0 = Interrupt requests from Timer x are disabled
//                         1 = Interrupt will be requested whenever TIF is 
//                         set. When an interrupt is pending (TIF set), 
//                         enabling the interrupt will immediately cause
//                         an interrupt event. To avoid this, the 
//                         associated TIF flag must be cleared first.
//
// TEN       0      rw     Timer Enable Bit.
//                         0 = Timer will be disabled
//                         1 = Timer will be active

//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================

typedef struct PIT_TCTRL_F_Tag
{
   bitfield32_t               :  BIT_30; // [31:2]   Reserved
   bitfield32_t   TIE         :  BIT_1;  // 1  Timer  Interrupt enable 
   bitfield32_t   TEN         :  BIT_1;  // 0  TImer Enable bit  

}  PIT_TCTRL_F_T;

typedef union PIT_TCTRL_Tag
{
   PIT_TCTRL_F_T          F;
   uint32_t              U32;

}  PIT_TCTRL_T;

//=============================================================================
// ID - Timer Flag Register (TFLG)
// Base Offset :0X10C,0X11C,0X12C,0X13C 
//
// Reset Value : 0000 0000H
//
// Field    Bits   Type  Description
// ============ ======== ==== =================================================
// TIF       0      rw     Time Interrupt Flag. TIF is set to 1 at the end
//                         of the timer period.This flag can be cleared
//                         only by writing it with a 1.Writing a 0 has 
//                         no effect. If enabled (TIE = 1), TIF causes
//                         an interrupt request.
//                         0 = Time-out has not yet occurred
//                         1 = Time-out has occurred
//=============================================================================
typedef struct PIT_TFLG_F_Tag
{
   bitfield32_t             :  BIT_31;  //  [31:1] Reserved
   bitfield32_t   TIF       :  BIT_1;   //  0      Time interrupt Flag
   
}  PIT_TFLG_F_T;

typedef union PIT_TFLG_Tag
{
   PIT_TFLG_F_T            F;
   uint32_t              U32;

}  PIT_TFLG_T;

//=============================================================================
typedef struct PIT_Timer_Register_Tag
{
   PIT_LDVAL_T   LDVA;
   PIT_CVAL_T    CVAL;
   PIT_TCTRL_T   TCTRL;
   PIT_TFLG_T    TFLG;

}  PIT_Timer_Register_T;
//=============================================================================
//  Periodic Interrupt Timer register  Structure
//=============================================================================
typedef volatile struct PIT_Tag
{
   PIT_MCR_T              MCR;                                // 0X000 to 0X003
   uint8_t                reserved_1[ PIT_RESERVED_0x00EC];   //0x004 to 0x0EF
   PIT_Timer_Register_T   Timer[PIT_CHANNEL_QUANTITY];        // 0XF0 to 0X13C

}  PIT_T;

#endif // HW_PIT_H

