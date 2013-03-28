#ifndef HW_SWT_H
#define HW_SWT_H


#include "reuse.h"

#define SWT_RESERVED_3FE4    (0x3FE4)



//===============================================================================================================
// ID - SWT Control Register (SWT_MCR)
//
// Base Offset : SWT_BASE+0x0000
//
//
// Field        Bits     Type   Description
// ========== =========  ==== //==========================================================================================
// MAPn          0-7            Master Access Protection for Master n.
//                              0 = Access for the master is not enabled
//                              1 = Access for the master is enabled
//
//              8-21            Reserved  all zeros
//
// KEY           22             Keyed Service Mode.
//                              0 = Fixed Service Sequence, the fixed sequence 0xA602, 0xB480 is used to service the watchdog
//                              1 = Keyed Service Mode, two pseudorandom key values are used to service the watchdog
// 
// RIA           23             Reset on Invalid Access.
//                              0 = Invalid access to the SWT generates a bus error
//                              1 = Invalid access to the SWT causes a system reset if WEN=1
//
// WND           24             Window Mode.
//                              0 = Regular mode, service sequence can be done at any time
//                              1 = Windowed mode, the service sequence is only valid when the down counter is less than
//                              the value in the SWT_WN register
//
// ITR           25             Interrupt Then Reset.
//                              0 = Generate a reset on a time-out
//                              1 = Generate an interrupt on an initial time-out, reset on a second consecutive time-out
//
// HLK           26             Hard Lock. This bit is only cleared at reset.
//                              0 = SWT_CR, SWT_TO, SWT_WN and SWT_SK are read/write registers if SLK=0
//                              1 = SWT_CR, SWT_TO, SWT_WN and SWT_SK are read only registers
//
// SLK           27             Soft Lock. This bit is cleared by writing the unlock sequence to the service register.
//                              0 = SWT_CR, SWT_TO SWT_WN and SWT_SK are read/write registers if HLK=0
//                              1 = SWT_CR, SWT_TO, SWT_WN and SWT_SK are read only registers    
//
// CSL           28             Clock Selection. Selects the clock that drives the internal timer.
//                              0 = System clock.
//                              1 = Oscillator clock.
//
// STP           29             Stop Mode Control. Allows the watchdog timer to be stopped when the device enters stop mode.
//                              0 = SWT counter continues to run in stop mode
//                              1 = SWT counter is stopped in stop mode
//
// FRZ           30             Debug Mode Control. Allows the watchdog timer to be stopped when the device enters debug mode.
//                              0 = SWT counter continues to run in debug mode
//                              1 = SWT counter is stopped in debug mode
//
// WEN           31             Watchdog Enabled.
//                              0 = SWT is disabled
//                              1 = SWT is enabled
//===============================================================================================================
typedef struct SWT_MCR_F_Tag
{
   bitfield32_t   MAP0      :1;        //bits  0
   bitfield32_t   MAP1      :1;        //bits  1
   bitfield32_t   MAP2      :1;        //bits  2
   bitfield32_t             :1;        //bits  3
   bitfield32_t             :1;        //bits  4
   bitfield32_t             :1;        //bits  5
   bitfield32_t             :1;        //bits  6
   bitfield32_t             :1;        //bits  7
   bitfield32_t             :14;       //bits  8-21
   bitfield32_t   KEY       :1;        //bits  22
   bitfield32_t   RIA       :1;        //bits  23
   bitfield32_t   WND       :1;        //bits  24
   bitfield32_t   ITR       :1;        //bits  25
   bitfield32_t   HLK       :1;        //bits  26
   bitfield32_t   SLK       :1;        //bits  27
   bitfield32_t   CSL       :1;        //bits  28
   bitfield32_t   STP       :1;        //bits  29
   bitfield32_t   FRZ       :1;        //bits  30
   bitfield32_t   WEN       :1;        //bits  31
} SWT_MCR_F_T;


typedef union SWT_MCR_Tag
{
   SWT_MCR_F_T    F;
   uint32_t      U32;
}SWT_MCR_T;

//===============================================================================================================
// ID - SWT Interrupt Register (SWT_IR)
//
// Base Offset : SWT_BASE + 0x0004 (
//
// Reset Value :0
//
// Field        Bits     Type   Description
// ========== =========  ==== //=================================================================================
//
//              0-30            Reserved all zeros
//
// TIF           31             Time-out Interrupt Flag. The flag and interrupt are cleared by writing a 1 to 
//                              this bit. Writing a 0 has no effect.
//                              0 = No interrupt request.
//                              1 = Interrupt request due to an initial time-out.
//===============================================================================================================

typedef struct  SWT_IR_F_Tag
{
   bitfield32_t             :31;        //bits  0-30 reserved
   bitfield32_t    TIF      :1;         //bits  31
}SWT_IR_F_T;


typedef union SWT_IR_Tag
{
   SWT_IR_F_T   F;
   uint32_t     U32;
}SWT_IR_T;


//===============================================================================================================
// ID - SWT Time-Out Register (SWT_TO)
//
// Base Offset : SWT_BASE + 0x008 
//
// Reset Value :The reset value of the SWT_TO register is device specific.
//
// Field        Bits     Type   Description
// ========== =========  ==== //=================================================================================
//
//  WTO         0-31           Watchdog time-out period in clock cycles. An internal 32-bit down counter is loaded 
//                             with this value or 0x100 which ever is greater when the service sequence is written 
//                             or when the SWT is enabled.
//===============================================================================================================

typedef uint32_t SWT_TO_T;


//===============================================================================================================
// ID - SWT Window Register (SWT_WN)
//
// Base Offset : SWT_BASE + 0x00C 
//
// Reset Value : Zeros
//
// Field        Bits     Type   Description
// ========== =========  ==== //=================================================================================
//
// WST               0-31        Window start value. When window mode is enabled, the service sequence can only
//                               be written when the internal down counter is less than this value.
//===============================================================================================================

typedef uint32_t SWT_WN_T;

//===============================================================================================================
// ID - SWT Service Register (SWT_SR)
//
// Base Offset : SWT_BASE + 0x010 
//
// Reset Value : All Zeros
//
// Field        Bits     Type   Description
// ========== =========  ==== //================================================================================
//
//              0-15             REserved All zeros
//
//  WSC        16-31             Watchdog Service Code.This field is used to service the watchdog and to clear 
//                               the soft lock bit(SWT_CR[SLK]). If the SWT_CR[KEY] bit is set, two pseudorandom 
//                               key values are written to service the watchdog, see Section 17.4 for details.
//                               Otherwise, the sequence 0xA602 followed by 0xB480 is written to the WSC field.
//                               To clear the soft lock bit (SWT_CR[SLK]), the value 0xC520 followed by 0xD928 is 
//                               written to the WSC field.
//===============================================================================================================

typedef struct SWT_SR_F_tag
{
   bitfield32_t               :16;        //bits 0-15
   bitfield32_t      WSC      :16;        //bits 16-31
} SWT_SR_F_T;


typedef union SWT_SR_Tag
{
   SWT_SR_F_T            F;
   uint32_t            U32;
} SWT_SR_T;

//===============================================================================================================
// ID - SWT Counter Output Register (SWT_CO)
//
// Base Offset : SWT_BASE + 0x014 
//
// Reset Value :all zeros
//
// Field       Bits     Type   Description
// ========== =========  ====   ===================================================================================
//
//  CNT        0-31           Watchdog Count. When the watchdog is disabled (SWT_CR[WEN]=0) this field shows the 
//                            value of the internal down counter. When the watchdog is enabled the value of this 
//                            field is 0x0000_0000. Values in this field can lag behind the internal counter value 
//                            for up to six system plus eight counter clock cycles. Therefore, the value read from 
//                            this field immediately after disabling the watchdog may be higher than the actual 
//                            value of the internal counter.
//===============================================================================================================

typedef uint32_t SWT_CO_T;

//===============================================================================================================
// ID - SWT Service Key Register (SWT_SK)
//
// Base Offset : SWT_BASE + 0x018 
//
// Reset Value : All Zeros
//
// Field       Bits     Type   Description
// ========== =========  ==== =====================================================================================
//
//             0-15           resreved All Zeros
//
// SK          16-31          Service Key.This field is the previous (or initial) service key value used in
//                            keyed service mode. If SWT_CR[KEY] is set, the next key value to be written to 
//                            the SWT_SR is (17*SK+3) mod 216.
//===================================================================================================================

typedef struct SWT_SK_F_Tag
{
   bitfield32_t                :16;      //bits 0-15
   bitfield32_t      SK        :16;      //bits 15-31
} SWT_SK_F_T;

typedef union SWT_SK_Tag
{
   SWT_SK_F_T          F;
   uint32_t           U32;
} SWT_SK_T;


typedef volatile struct SWT_Tag
{
   SWT_MCR_T          SWT_MCR;                            //0x0000-0x0003
   SWT_IR_T           SWT_IR;                             //0x0004-0x0007
   SWT_TO_T           SWT_TO;                             //0x0008-0x000B
   SWT_WN_T           SWT_WN;                             //0x000C–0x000F
   SWT_SR_T           SWT_SR;                             //0x0010-0x0013
   SWT_CO_T           SWT_CO;                             //0x0014–0x0017
   SWT_SK_T           SWT_SK;                             //0x0018-0x001B
   uint8_t            reserved[SWT_RESERVED_3FE4];        //0x001C-0x3FFF
}SWT_T;

#endif // HW_SWT_H

