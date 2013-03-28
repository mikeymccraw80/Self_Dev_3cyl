#ifndef HW_SIU_H
#define HW_SIU_H
 

#include "reuse.h"

#define  SIU_ARRAY_SIZE_2     (   2)
#define  SIU_ARRAY_SIZE_4     (   4)
#define  SIU_ARRAY_SIZE_53    (  53)
#define  SIU_ARRAY_SIZE_75    (  75)
#define  SIU_ARRAY_SIZE_214   ( 214)
#define  BIT_32      32

//=============================================================================
// ID - MCU ID Register (SIU_MIDR2)
//
// Base Offset : 0x0000
//
// Reset Value : 0x3200 4D00
//
// Field        Bits     Type Description
//============= ======== ==== ===============================================
// S_F            31     r    Identifies the Manufacturer
//                            0   FSL
//                            1   ST
//-----------------------------------------------------------------------------
// FLASH_SIZE_1  [30:27] r    Define major Flash memory size
//-----------------------------------------------------------------------------
// FLASH_SIZE_2  [26:23] r    Define Flash memory size, small granularity
//-----------------------------------------------------------------------------
// TEMP_RANGE    [22:21] r    Define maximum operating range
//-----------------------------------------------------------------------------
// 0               20    r    Reserved
//-----------------------------------------------------------------------------  
// MAX_FREQ      [19:18] r    Define maximum device speed
//-----------------------------------------------------------------------------
// 0               17    r    Reserved
//-----------------------------------------------------------------------------
// SUPPLY          16    r    Defines if the part is 5 V or 3 V
//                            1  3 V
//                            0  5 V
//-----------------------------------------------------------------------------
// PART_NUMBER   [15:8]  r    Contain the ASCII representation of the character 
//                            that indicates the product family.
//-----------------------------------------------------------------------------
// TBD             7     r    Reserved
//-----------------------------------------------------------------------------
// 0             [6:5]   r    Reserved
//-----------------------------------------------------------------------------
// EE              4     r    Indicates if Data Flash is present
//                            1  Data Flash present
//                            0  Data Flash not present
//-----------------------------------------------------------------------------
// 0             [3:1]   r    Reserved
//-----------------------------------------------------------------------------
// FR              0     r    Indicates if Data FlexRay is present
//                            1  FlexRay present
//                            0  FlexRay not present
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================
typedef struct SIU_MIDR2_F_Tag
{
   bitfield32_t  S_F              :  BIT_1;   // Bit  31
   bitfield32_t  FLASH_SIZE_1     :  BIT_4;   // Bits [30:27]
   bitfield32_t  FLASH_SIZE_2     :  BIT_4;   // Bits [26:23]
   bitfield32_t  TEMP_RANGE       :  BIT_2;   // Bits [22:21]
   bitfield32_t                   :  BIT_1;   // Reserved Bit 20
   bitfield32_t  MAX_FREQ         :  BIT_2;   // Bit  [19:18]
   bitfield32_t                   :  BIT_1;   // Reserved Bit 17
   bitfield32_t  SUPPLY           :  BIT_1;   // Bit  16
   bitfield32_t  PART_NUMBER      :  BIT_8;   // Bits [15:8]
   bitfield32_t  TBD              :  BIT_1;   // Bit  7
   bitfield32_t                   :  BIT_2;   // Reserved Bit [6:5]
   bitfield32_t  EE               :  BIT_1;   // Bit  4
   bitfield32_t                   :  BIT_3;   // Reserved Bits[3:1]
   bitfield32_t  FR               :  BIT_1;   // Bit 0

}  SIU_MIDR2_F_T;

typedef union SIU_MIDR2_Tag
{
   SIU_MIDR2_F_T     F;
   uint32_t          U32;
   uint16_t          U16[SIU_ARRAY_SIZE_2];

}  SIU_MIDR2_T;

//=============================================================================
// ID - MCU ID Register (SIU_MIDR)
//
// Base Offset : 0x0004
//
// Reset Value : 0x5633 3400 
//
// Field        Bits     Type Description
//============= ======== ==== ===============================================
// PARTNUM      [31:16]  r    MCU part number. Read-only, mask programmed
//                            part number of the MCU 0x05633
//----------------------------------------------------------------------------- 
// CSP            15     r    CSP configuration:
//                            1 = VertiCal 496 CSPpackage
//                            0 = standard QFP package or BGA208 package
//-----------------------------------------------------------------------------
// PKG          [14:10]  r    Indicate the package the die is mounted in
//-----------------------------------------------------------------------------                                       
// 0            [9:8]    r    Reserved, should be cleared
//-----------------------------------------------------------------------------
// MASKNUM_MAJOR [7:4]   r    MCU mask number. Read-only, mask programmed
//                            mask number of the MCU. Reads 0x0000 for the
//                            initial mask set of the device, and changes
//                            sequentially for each mask set.
//-----------------------------------------------------------------------------
// MASKNUM_MINOR [3:0]   r    Minor revision number of MCU mask. Read-only, 
//                            mask programmed mask number of the
//                            MCU. Reads 0x0 for the initial mask set of the 
//                            device, and changes sequentially for each
//                            mask set.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//      not a copy from the manual
//=============================================================================
typedef struct SIU_MIDR_F_Tag
{
   bitfield32_t  PARTNUM           :  BIT_16;  // Bits [31:16]
   bitfield32_t  CSP               :  BIT_1;   // Bit  15
   bitfield32_t  PKG               :  BIT_5;   // Bits [14:10]
   bitfield32_t                    :  BIT_2;   // Reserved bits [9:8]
   bitfield32_t  MASKNUM_MAJOR     :  BIT_4;   // Bits [7:4]
   bitfield32_t  MASKNUM_MINOR     :  BIT_4;   // Bits [3:0]

}  SIU_MIDR_F_T;

typedef union SIU_MIDR_Tag
{
   SIU_MIDR_F_T      F;
   uint32_t          U32;
   uint16_t          U16[SIU_ARRAY_SIZE_2];

}  SIU_MIDR_T;

//=============================================================================
// ID - Reset Status Register (SIU_RSR)
// Base Offset : 0x000C
//
// Reset Value : SIU_RSR receives its reset values during power-on reset.
//               The reset value of the WKPCFG bit is determined by the
//               value on the WKPCFG pin at reset.
//               The reset value of the BOOTCFG field is determined by the
//               values on the BOOTCFG[0:1] pins at reset.
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// PORS           31      r   Power-on reset status.
//                            1 A Power-On Reset has occurred.
//                            0 No Power-On Reset has occurred.
//-----------------------------------------------------------------------------
// ERS            30      r   External reset status.
//                            1 An External Reset has occurred.
//                            0 No External Reset has occurred.
//-----------------------------------------------------------------------------
// LLRS           29      r   Loss of lock reset status.
//                            1 Loss of Lock Reset has occurred
//                            0 No Loss of Lock Reset has occurred
//-----------------------------------------------------------------------------
// LCRS           28      r   Loss of clock reset status.
//                            1 A Loss of Clock Reset has occurred due to a 
//                              loss of the reference or failure of the FMPLL.
//                            0 No Loss of Clock Reset has occurred.
//-----------------------------------------------------------------------------
// WDRS           27      r   Watchdog timer/debug reset status.
//                            1 A Watchdog Timer or Debug Reset has occurred.
//                            0 No Watchdog Timer or Debug Reset has occurred.
//-----------------------------------------------------------------------------
// CRS            26      r   Checkstop reset status.
//                            1 An enabled Checkstop Reset has occurred.
//                            0 No enabled Checkstop Reset has occurred.
//-----------------------------------------------------------------------------
// SWTRS          25      r   Software Watchdog Timer Reset Status
//                            0 An enabled SWT Reset has occurred.   
//                            1 No enabled SWT Reset has occurred.        
//-----------------------------------------------------------------------------
// 0            [24:18]   r   Reserved, should be cleared.
//-----------------------------------------------------------------------------
// SSRS           17      r   Software system reset status.
//                            0 A Software System Reset has occurred.
//                            1 No Software System Reset has occurred.
//-----------------------------------------------------------------------------
// SERF           16      r   Software external reset flag.
//                            1 A Software External Reset has occurred.
//                            0 No Software External Reset has occurred.
//-----------------------------------------------------------------------------
// WKPCFG         15      r   Weak pull up configuration pin status.
//                            1 WKPCFG pin latched during the last reset was 
//                              logical one and weak pull up is the default 
//                              setting
//                            0 WKPCFG pin latched during the last reset was 
//                              logical zero and weak pull down is the default 
//                              setting.
//-----------------------------------------------------------------------------
// 0            [14:4]    r   Reserved, should be cleared.
//-----------------------------------------------------------------------------
// ABR            3       r   Auto Baud Rate
//                            1  Auto Baud Rate Enabled.
//                            0  Auto Baud Rate Disabled, eSys compatible.
//-----------------------------------------------------------------------------
// BOOTCFG      [2:1]     r   Reset configuration pin status.
//                            Holds the value of the BOOTCFG pins that was
//                            latched on last negation of the RSTOUT signal.
//-----------------------------------------------------------------------------
// RGF            0       r   Reset glitch flag.
//                            1 A glitch was detected on the RESET pin.
//                            0 No glitch was detected on the RESET pin.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_RSR_F_Tag
{
   bitfield32_t  PORS       :  BIT_1;  // Bit  31
   bitfield32_t  ERS        :  BIT_1;  // Bit  30
   bitfield32_t  LLRS       :  BIT_1;  // Bit  29
   bitfield32_t  LCRS       :  BIT_1;  // Bit  28
   bitfield32_t  WDRS       :  BIT_1;  // Bit  27
   bitfield32_t  CRS        :  BIT_1;  // Bit  26
   bitfield32_t  SWTRS      :  BIT_1;  // Bit  25
   bitfield32_t             :  BIT_7;  // Bits [24:18] Reserved
   bitfield32_t  SSRS       :  BIT_1;  // Bit  17
   bitfield32_t  SERF       :  BIT_1;  // Bit  16
   bitfield32_t  WKPCFG     :  BIT_1;  // Bit  15
   bitfield32_t             :  BIT_11; // Bits [14:4] Reserved
   bitfield32_t  ABR        :  BIT_1;  // Bit  3  
   bitfield32_t  BOOTCFG    :  BIT_2;  // Bits [2:1]
   bitfield32_t  RGF        :  BIT_1;  // Bit  0

}  SIU_RSR_F_T;

typedef union SIU_RSR_Tag
{
   SIU_RSR_F_T      F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];

}  SIU_RSR_T;

//=============================================================================
// ID -  System Reset Control Register (SIU_SRCR)
//  Base Offset : 0x0010
//
// Reset Value  : 0x0000 8000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// SSR            31     rw   Software System Reset.
//                            Writing a one to this bit causes an internal 
//                            reset and assertion of the RSTOUT pin. The bit is
//                            automatically cleared by all reset sources except
//                            the Software External Reset.
//                            1 Generate a Software System Reset.
//                            0 Do not generate a Software System Reset.
//-----------------------------------------------------------------------------
// SER            30     rw   Software External Reset.
//                            Writing a one to this bit causes a Software
//                            External Reset. The RSTOUT pin is asserted for 
//                            the predetermined number of clock cycles, but the
//                            MCU is not reset. The bit is automatically 
//                            cleared when Software External Reset completes.
//                            1 Generate a Software External Reset.
//                            0 Do not generate a Software External Reset.
//-----------------------------------------------------------------------------
// 0            [29:16]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// CRE            15     rw   Checkstop Reset Enable.
//                            Writing a one to this bit enables a Checkstop 
//                            Reset when the e200z335 core enters a checkstop 
//                            state. The CRE bit defaults to Checkstop Reset 
//                            enabled. If this bit is cleared, it remains 
//                            cleared until the next POR.
//                            1 A reset occurs when the e200z335 core enters a 
//                              checkstop state.
//                            0 No reset occurs when the e200z335 core enters a
//                              checkstop state.
//-----------------------------------------------------------------------------
// 0            [14:0]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_SRCR_F_Tag
{
   bitfield32_t  SSR    :  BIT_1;  // Bit  31
   bitfield32_t  SER    :  BIT_1;  // Bit  30
   bitfield32_t         :  BIT_14; // Bits [29:16] Reserved
   bitfield32_t  CRE    :  BIT_1;  // Bit  15
   bitfield32_t         :  BIT_15; // Bits [14:0] Reserved

}  SIU_SRCR_F_T;

typedef union SIU_SRCR_Tag
{
   SIU_SRCR_F_T    F;
   uint32_t        U32;
   uint16_t        U16[SIU_ARRAY_SIZE_2];

}  SIU_SRCR_T;

//=============================================================================
// ID - External Interrupt Status Register (SIU_EISR)
//  Base Offset : 0x0014
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== =================================================
// NMI            31     rw   Non-Maskable Interrupt Flag.This bit is set when 
//                            a NMI interrupt occurs on the NMI input pin.
//                            1  An NMI event has occurred on the NMI input
//                            0  No NMI event has occurred on the NMI input
//-----------------------------------------------------------------------------
// 0            [30:24]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// SWT            23     rw   Software Watch Dog Timer Interrupt Flag, from 
//                            platform.This bit is set when a SWT interrupt 
//                            occurs on the platform.
//                            1  An SWT event has occurred
//                            0  No SWT event has occurred
//-----------------------------------------------------------------------------
// 0            [22:16]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// EIFx         [15:8]   rw   External interrupt request flag x. This bit is
// (n=8-15)                   set when an edge triggered event occurs on
//                            the corresponding IRQx input.
//                            0 No edge triggered event has occurred on the
//                            corresponding IRQ[x] input.
//                            1 An edge triggered event has occurred on the
//                            corresponding IRQ[x] input.
//-----------------------------------------------------------------------------
// 0            [7:5]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// EIFx         [4:3]    rw   External interrupt request flag x.
// (x=3-4)
//-----------------------------------------------------------------------------
// 0            [2:1]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// EIF0           0      rw   External interrupt request flag 0.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_EISR_F_Tag
{
   bitfield32_t  NMI            :  BIT_1;  // Bit  31
   bitfield32_t                 :  BIT_7;  // Bits [30:24] Reserved
   bitfield32_t  SWT            :  BIT_1;  // Bit  23
   bitfield32_t                 :  BIT_7;  // Bits [22:16] Reserved
   bitfield32_t  EIF15          :  BIT_1;  // Bit  15
   bitfield32_t  EIF14          :  BIT_1;  // Bit  14
   bitfield32_t  EIF13          :  BIT_1;  // Bit  13
   bitfield32_t  EIF12          :  BIT_1;  // Bit  12
   bitfield32_t  EIF11          :  BIT_1;  // Bit  11
   bitfield32_t  EIF10          :  BIT_1;  // Bit  10
   bitfield32_t  EIF9           :  BIT_1;  // Bit  9
   bitfield32_t  EIF8           :  BIT_1;  // Bit  8 
   bitfield32_t                 :  BIT_3;  // Bits [7:5] Reserved
   bitfield32_t  EIF4           :  BIT_1;  // Bit  4
   bitfield32_t  EIF3           :  BIT_1;  // Bit  3
   bitfield32_t                 :  BIT_2;  // Bits [2:1] Reserved  
   bitfield32_t  EIF0           :  BIT_1;  // Bit  0

}  SIU_EISR_F_T;

typedef union SIU_EISR_Tag
{
   SIU_EISR_F_T     F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];

}  SIU_EISR_T;

//=============================================================================
// ID - DMA/Interrupt Request Enable Register (SIU_DIRER)
//  Base Offset : 0x0018
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// NMI_SEL        31     rw   NMI Interrupt Platform Input Selection 
//                            This write once bit selects NMI or CI for the  
//                            SWaT timer. 
//                            0 NMI interrupt request input is selected.
//                            1 Critical interrupt request input is selected.
//-----------------------------------------------------------------------------
// 0            [30:24]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// SWT_SEL        23     rw   Software Watchdog Timer Interrupt/Critical 
//                            Interrupt Platform Input Selection 
//                            This write once bit select each platform input 
//                            will be used for the SWT interrupt signal, when 
//                            an edge triggered event occurs on the NMI input. 
//                            0 NMI interrupt request input is selected.
//                            1 Critical interrupt request input is selected.
//-----------------------------------------------------------------------------
// 0            [22:16]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// EIREx        [15:0]   rw   External DMA/Interrupt Request Enable x.
//                            This bit enables the assertion of a DMA or the 
//                            interrupt request from the SIU to the interrupt 
//                            controller when an edge triggered event occurs on 
//                            the IRQx inputs.
//                            0 External interrupt request is disabled.
//                            1 External interrupt request is enabled.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_DIRER_F_Tag
{
   bitfield32_t  NMI_SEL :  BIT_1;  // Bit 31         
   bitfield32_t          :  BIT_7;  // Bits [30:24] Reserved
   bitfield32_t  SWT_SEL :  BIT_1;  // Bit 23         
   bitfield32_t          :  BIT_7;  // Bits [22:16] Reserved
   bitfield32_t  EIRE15  :  BIT_1;  // Bit  15
   bitfield32_t  EIRE14  :  BIT_1;  // Bit  14
   bitfield32_t  EIRE13  :  BIT_1;  // Bit  13
   bitfield32_t  EIRE12  :  BIT_1;  // Bit  12
   bitfield32_t  EIRE11  :  BIT_1;  // Bit  11
   bitfield32_t  EIRE10  :  BIT_1;  // Bit  10
   bitfield32_t  EIRE9   :  BIT_1;  // Bit  9
   bitfield32_t  EIRE8   :  BIT_1;  // Bit  8
   bitfield32_t  EIRE7   :  BIT_1;  // Bit  7
   bitfield32_t  EIRE6   :  BIT_1;  // Bit  6
   bitfield32_t  EIRE5   :  BIT_1;  // Bit  5
   bitfield32_t  EIRE4   :  BIT_1;  // Bit  4
   bitfield32_t  EIRE3   :  BIT_1;  // Bit  3
   bitfield32_t  EIRE2   :  BIT_1;  // Bit  2
   bitfield32_t  EIRE1   :  BIT_1;  // Bit  1
   bitfield32_t  EIRE0   :  BIT_1;  // Bit  0

}  SIU_DIRER_F_T;

typedef union SIU_DIRER_Tag
{
   SIU_DIRER_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];

}  SIU_DIRER_T;

//=============================================================================
// ID - DMA/Interrupt Request Select Register (SIU_DIRSR)
//  Base Offset : 0x001C
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:4]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// DIRS3          3      rw   DMA/Interrupt Request Select 3.
//                            Selects between a DMA or interrupt request when
//                            an edge triggered event occurs on the IRQ3 pin.
//                            0 Interrupt request is selected.
//                            1 DMA request is selected.
//-----------------------------------------------------------------------------
// 0            [2:1]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// DIRS0          0      rw   DMA/Interrupt Request Select 0.
//                            Selects between a DMA or interrupt request when
//                            an edge triggered event occurs on the IRQ0 pin.
//                            0 Interrupt request is selected.
//                            1 DMA request is selected.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_DIRSR_F_Tag
{
   bitfield32_t          :  BIT_28; // Bits [31:4]  Reserved
   bitfield32_t  DIRS3   :  BIT_1;  // Bit  3
   bitfield32_t          :  BIT_2;  // Bits [2:1] Reserved
   bitfield32_t  DIRS0   :  BIT_1;  // Bit  0

}  SIU_DIRSR_F_T;

typedef union SIU_DIRSR_Tag
{
   SIU_DIRSR_F_T    F;
   uint32_t         U32;

}  SIU_DIRSR_T;

//=============================================================================
// ID - Overrun Status Register (SIU_OSR)
//  Base Offset : 0x0020
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:16]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// OVFx         [15:8]   rw   Overrun flag x.
//(x=8-15)                    This bit is set when an overrun occurs on the
//                            corresponding IRQx pin.
//                            0 No overrun has occurred on the corresponding
//                              IRQx pin.
//                            1 An overrun has occurred on the corresponding
//                              IRQx pin.
//-----------------------------------------------------------------------------          
// 0            [7:5]    r    Reserved, should be cleared
//-----------------------------------------------------------------------------
// OVFx         [4:3]    rw   Overrun flag x.  
// (x=4-3)
//-----------------------------------------------------------------------------
// 0            [2:1]    r    Reserved, should be cleared
//-----------------------------------------------------------------------------
// OVF0           0      rw   Overrun flag 0. 
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_OSR_F_Tag
{
   bitfield32_t         :  BIT_16; // Bits [31:16] Reserved
   bitfield32_t  OVF15  :  BIT_1;  // Bit  15
   bitfield32_t  OVF14  :  BIT_1;  // Bit  14
   bitfield32_t  OVF13  :  BIT_1;  // Bit  13
   bitfield32_t  OVF12  :  BIT_1;  // Bit  12
   bitfield32_t  OVF11  :  BIT_1;  // Bit  11
   bitfield32_t  OVF10  :  BIT_1;  // Bit  10
   bitfield32_t  OVF9   :  BIT_1;  // Bit  9
   bitfield32_t  OVF8   :  BIT_1;  // Bit  8
   bitfield32_t         :  BIT_3;  // Bits [7:5] Reserved
   bitfield32_t  OVF4   :  BIT_1;  // Bit  4
   bitfield32_t  OVF3   :  BIT_1;  // Bit  3
   bitfield32_t         :  BIT_2;  // Bits [2:1] Reserved
   bitfield32_t  OVF0   :  BIT_1;  // Bit  0

}  SIU_OSR_F_T;

typedef union SIU_OSR_Tag
{
   SIU_OSR_F_T      F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];

}  SIU_OSR_T;

//=============================================================================
// ID - Overrun Request Enable Register (SIU_ORER)
//  Base Offset : 0x0024
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== =================================================
// 0            [31:16]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// OREx         [15:8]   rw   Overrun request enable x.
//(x=8-15)                    Enables the corresponding overrun request when
//                            an overrun occurs on corresponding IRQx pin.
//                            0 Overrun request is disabled.
//                            1 Overrun request is enabled.
//-----------------------------------------------------------------------------
// 0            [7:5]    r    Reserved, should be cleared. 
//----------------------------------------------------------------------------- 
//OREx          [4:3]    rw   Overrun request enable x.
//(x=4-3)               
//-----------------------------------------------------------------------------
// 0            [2:1]    r    Reserved, should be cleared. 
//-----------------------------------------------------------------------------
// ORE0           0      rw   Overrun request enable 0.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_ORER_F_Tag
{
   bitfield32_t         :  BIT_16; // Bits [31:16] Reserved
   bitfield32_t  ORE15  :  BIT_1;  // Bit  15
   bitfield32_t  ORE14  :  BIT_1;  // Bit  14
   bitfield32_t  ORE13  :  BIT_1;  // Bit  13
   bitfield32_t  ORE12  :  BIT_1;  // Bit  12
   bitfield32_t  ORE11  :  BIT_1;  // Bit  11
   bitfield32_t  ORE10  :  BIT_1;  // Bit  10
   bitfield32_t  ORE9   :  BIT_1;  // Bit  9
   bitfield32_t  ORE8   :  BIT_1;  // Bit  8
   bitfield32_t         :  BIT_3;  // Bits [7:5] Reserved  
   bitfield32_t  ORE4   :  BIT_1;  // Bit  4
   bitfield32_t  ORE3   :  BIT_1;  // Bit  3
   bitfield32_t         :  BIT_2;  // Bits [2:1] Reserved
   bitfield32_t  ORE0   :  BIT_1;  // Bit  0

}  SIU_ORER_F_T;

typedef union SIU_ORER_Tag
{
   SIU_ORER_F_T     F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];

}  SIU_ORER_T;

//=============================================================================
// ID - IRQ Rising-Edge Event Enable Register (SIU_IREER)
//  Base Offset : 0x0028
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// NMIRE          31     rw   NMI Rising-Edge Event Enable x
//                            This write once bit enables rising-edge 
//                            triggered events on the NMI input.
//                            0 Rising-edge event is disabled
//                            1 Rising-edge event is enabled.
//-----------------------------------------------------------------------------
// 0            [30:24]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// SWTRE          23     rw   SWT Rising-Edge Event Enable x.  
//                            Enables rising-edge triggered events on the 
//                            NMI input.
//                            0 Rising-edge event is disabled
//                            1 Rising-edge event is enabled.
//-----------------------------------------------------------------------------
// 0            [30:24]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// IREEx        [15:8]   rw   IRQ rising-edge event enable x.
// (x=8-15)                   Enables rising-edge triggered events on the
//                            corresponding IRQx pin.
//                            0 Rising edge event is disabled.
//                            1 Rising edge event is enabled.
//-----------------------------------------------------------------------------
// 0            [7:5]    r    Reserved, should be cleared.             
//-----------------------------------------------------------------------------
// IREEx        [4:3]    rw   IRQ rising-edge event enable x.
// (x=3-4)
//-----------------------------------------------------------------------------
// 0            [2:1]    r    Reserved, should be cleared.             
//-----------------------------------------------------------------------------
// IREE0          0      rw   IRQ rising-edge event enable 0.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_IREER_F_Tag
{
   bitfield32_t  NMIRE      :  BIT_1;  // Bit  31
   bitfield32_t             :  BIT_7;  // Bits [30:24] Reserved
   bitfield32_t  SWTRE      :  BIT_1;  // Bit  23
   bitfield32_t             :  BIT_7;  // Bits [22:16] Reserved
   bitfield32_t  IREE15     :  BIT_1;  // Bit  15
   bitfield32_t  IREE14     :  BIT_1;  // Bit  14
   bitfield32_t  IREE13     :  BIT_1;  // Bit  13
   bitfield32_t  IREE12     :  BIT_1;  // Bit  12
   bitfield32_t  IREE11     :  BIT_1;  // Bit  11
   bitfield32_t  IREE10     :  BIT_1;  // Bit  10
   bitfield32_t  IREE9      :  BIT_1;  // Bit  9
   bitfield32_t  IREE8      :  BIT_1;  // Bit  8
   bitfield32_t             :  BIT_3;  // Bits [7:5] Reserved
   bitfield32_t  IREE4      :  BIT_1;  // Bit  4
   bitfield32_t  IREE3      :  BIT_1;  // Bit  3
   bitfield32_t             :  BIT_2;  // Bits  [2:1] Reserved
   bitfield32_t  IREE0      :  BIT_1;  // Bit  0

}  SIU_IREER_F_T;

typedef union SIU_IREER_Tag
{
   SIU_IREER_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];

}  SIU_IREER_T;

//=============================================================================
// ID - IRQ Falling-Edge Event Enable Register (SIU_IFEER)
//  Base Offset : 0x002C
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// NMIFE          31     rw   NMI Falling-Edge Event Enable x
//                            This write once bit enables falling-edge 
//                            triggered events on the NMI input
//                            1 Falling edge event is enabled
//                            0 Falling edge event is disabled
//-----------------------------------------------------------------------------
// 0            [30:16]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// SWTFE          23     rw   SWT Falling-Edge Event Enable x 
//                            Enables  falling-edge triggered events on the 
//                            corresponding NMIs. NMI comes from watch
//                            dog timer
//                            0 Falling edge event is disabled
//                            1 Falling edge event is enabled.
//-----------------------------------------------------------------------------
// 0            [30:24]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// IFEEx        [15:8]   rw   IRQ falling-edge event enable x.
// (x=8-15)                   Enables falling-edge triggered events on the
//                            corresponding IRQx pin.
//                            0 Falling edge event is disabled.
//                            1 Falling edge event is enabled.
//-----------------------------------------------------------------------------
// 0            [7:5]    r    Reserved, should be cleared.
//----------------------------------------------------------------------------- 
// IFEEx        [4:3]    rw   IRQ falling-edge event enable x.
// (x=3-4)
//-----------------------------------------------------------------------------
// 0            [2:1]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// IFEE0          0      rw   IRQ falling-edge event enable 0.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_IFEER_F_Tag
{
   bitfield32_t  NMIFE   :  BIT_1;  // Bit  31
   bitfield32_t          :  BIT_7;  // Bits [30:24] Reserved
   bitfield32_t  SWTFE   :  BIT_1;  // Bit  23
   bitfield32_t          :  BIT_7;  // Bits [22:16] Reserved
   bitfield32_t  IFEE15  :  BIT_1;  // Bit  15
   bitfield32_t  IFEE14  :  BIT_1;  // Bit  14
   bitfield32_t  IFEE13  :  BIT_1;  // Bit  13
   bitfield32_t  IFEE12  :  BIT_1;  // Bit  12
   bitfield32_t  IFEE11  :  BIT_1;  // Bit  11
   bitfield32_t  IFEE10  :  BIT_1;  // Bit  10
   bitfield32_t  IFEE9   :  BIT_1;  // Bit  9
   bitfield32_t  IFEE8   :  BIT_1;  // Bit  8
   bitfield32_t          :  BIT_3;  // Bits [7:5] Reserved
   bitfield32_t  IFEE4   :  BIT_1;  // Bit  4
   bitfield32_t  IFEE3   :  BIT_1;  // Bit  3
   bitfield32_t          :  BIT_2;  // Bits [2:1] Reserved
   bitfield32_t  IFEE0   :  BIT_1;  // Bit  0
}  SIU_IFEER_F_T;

typedef union SIU_IFEER_Tag
{
   SIU_IFEER_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];

}  SIU_IFEER_T;

//=============================================================================
// ID - IRQ Digital Filter Register (SIU_IDFR)
//  Base Offset : 0x0030
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:4]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// DFL          [3:0]    rw   Digital filter length.
//                            Defines digital filter period on IRQx inputs
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_IDFR_F_Tag
{
   bitfield32_t       :  BIT_28; // Bits [31:4] Reserved
   bitfield32_t  DFL  :  BIT_4;  // Bits [3:0]

}  SIU_IDFR_F_T;

typedef union SIU_IDFR_Tag
{
   SIU_IDFR_F_T       F;
   uint32_t         U32;

}  SIU_IDFR_T;

//=============================================================================
// ID - Pad Configuration Registers (SIU_PCR)
//     Base Offset : 0x40-0x37B(PCR0-413)
//
// Reset Value  : 0x0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [15:14]   r   Reserved, should be cleared.
//-----------------------------------------------------------------------------
// PA           [13:10]   rw  Pin assignment. 
//                            Selects the function of a multiplexed pad. 
//-----------------------------------------------------------------------------
// OBE            9       rw  Output buffer enable.
//                            Enables the pad as an output and drives
//                            the output buffer enable signal.
//                            0 Disable output buffer for the pad.
//                            1 Enable output buffer for the pad is enabled.
//-----------------------------------------------------------------------------
// IBE            8       rw  Input buffer enable.
//                            Enables the pad as an input and drives the
//                            input buffer enable signal.
//                            0 Disable input buffer for the pad.
//                            1 Enable input buffer for the pad is enabled.
//-----------------------------------------------------------------------------
// DSC          [7:6]     rw  Drive strength control.
//                             Controls the pad drive strength.
//                            Drive strength control pertains to pins with
//                            the fast I/O pad type.
//                            00 10 pF Drive Strength
//                            01 20 pF Drive Strength
//                            10 30 pF Drive Strength
//                            11 50 pF Drive Strength          
//-----------------------------------------------------------------------------
// ODE            5       rw  Open drain output enable.
//                            Controls output driver configuration for the
//                            pads. Either open drain or push/pull driver
//                            configurations can be selected.
//                            This feature applies to output pins only.
//                            0 Disable open drain for the pad.
//                            1 Enable open drain for the pad.
//-----------------------------------------------------------------------------
// HYS            4       rw  Input hysteresis.
//                            Controls whether hysteresis is enabled for the
//                            pad or pad group.
//                            0 Disable hysteresis for the pad.
//                            1 Enable hysteresis for the pad.
//-----------------------------------------------------------------------------
// SRC          [3:2]     rw  Slew rate control.
//                            Controls slew rate for the pad or pad group.
//                            Slew rate control pertains to pins with slow
//                            or medium I/O pad types, and the output
//                            signals are driven according to the value of
//                            this field. Actual slew rate is dependent on
//                            the pad type and load. See the electrical
//                            specification for this information
//                            00 Minimum Slew Rate
//                            01 Medium Slew Rate
//                            10 Invalid value
//                            11 Maximum Slew Rate
//-----------------------------------------------------------------------------
// WPE            1       rw  Weak pull up/down enable.
//                            Controls whether the weak pull up/down devices
//                            are enabled/disabled for the pad or pad group
//                            Pull up/down devices are enabled by default.
//                            0 Disable weak pull device for the pad.
//                            1 Enable weak pull device for the pad.
//-----------------------------------------------------------------------------
// WPS            0       rw  Weak pull up/down select.
//                            Controls whether weak pull up or weak pull
//                            down devices are used for the pad or pad group
//                            when weak pull up/down devices are enabled.
//                            The WKPCFG pin determines whether pull up or
//                            pull down devices are enabled at reset.
//                            The WPS bit determines whether weak pull up or
//                            pull down devices are used after reset, or for
//                            pads in which the WKPCFG pin does not determine
//                            the reset weak pull up/down state.
//                            0 Pulldown is enabled for the pad.
//                            1 Pullup is enabled for the pad.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_PCR_F_Tag
{
   bitfield16_t           :  BIT_2;  // Bits [15:14] Reserved
   bitfield16_t  PA       :  BIT_4;  // Bits [13:10]
   bitfield16_t  OBE      :  BIT_1;  // Bit  9
   bitfield16_t  IBE      :  BIT_1;  // Bit  8
   bitfield16_t  DSC      :  BIT_2;  // Bits [7:6]
   bitfield16_t  ODE      :  BIT_1;  // Bit  5
   bitfield16_t  HYS      :  BIT_1;  // Bit  4
   bitfield16_t  SRC      :  BIT_2;  // Bits [3:2]
   bitfield16_t  WPE      :  BIT_1;  // Bit  1
   bitfield16_t  WPS      :  BIT_1;  // Bit  0

}  SIU_PCR_F_T;

typedef union SIU_PCR_Tag
{
   SIU_PCR_F_T    F;
   uint16_t       U16;  

}  SIU_PCR_T;



//=============================================================================
//=============================================================================
// ID - GPIO Pin Data Out Register 
// (SIU_GPDO83_86-SIU_GPDO230_232-SIU_GPDO350_413)
// Base Offset : 0x600+n (n=83-86, 230 -232, 350-413)
// Gaps exist in this memory space where the pin is not available 
// in the package
//
// Reset Value  : 0x00
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [7:1]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// PDOn           0      rw   Pin data out. Stores the data to be driven out
// (n=83-86)                  on the external GPIO pin associated with the
// (n=230-232)                register.
// (n=350-413)                0 VOL is driven on the external GPIO pin when
//                              the pin is configured as an output.
//                            1 VOH is driven on the external GPIO pin when
//                              the pin is configured as an output.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_GPDO_F_Tag
{
   bitfield8_t         :  BIT_7;  // Bits [7:1]  Reserved
   bitfield8_t  PDO    :  BIT_1;  // Bit  0

}  SIU_GPDO_F_T;

typedef union SIU_GPDO_Tag
{
   SIU_GPDO_F_T    F;
   uint8_t         U8;

}  SIU_GPDO_T;

//=============================================================================
// ID - GPIO Pin Data In Register 83-86 (SIU_GPDI83_86 - SIUGPDI232)
// Base Offset : 0x800+n (n=83-232)
// Gaps exist in this memory space where the pin is not available 
// in the package
// Reset Value  : 0x00
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [7:1]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// PDIn           0      rw   Pin data in. This bit stores the input state
// (n=83-213)                 on the external GPIO pin associated with the
//                            register.
//                            0 Signal on pin is less than or equal to VIL.
//                            1 Signal on pin is greater than or equal to VIH
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_GPDI_F_Tag
{
   bitfield8_t          :  BIT_7;  // Bits [7:1]  Reserved
   bitfield8_t  PDI     :  BIT_1;  // Bit  0

}  SIU_GPDI_F_T;

typedef union SIU_GPDI_Tag
{
   SIU_GPDI_F_T    F;
   uint8_t         U8;

}  SIU_GPDI_T;

//=============================================================================
// ID - eQADC Trigger Input Select Register (SIU_ETISR)
//  Base Offset : 0x0900
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// TSEL5        [31:30]   rw  eQADC trigger input select 5.
//                            Specifies the input for eQADC trigger 5.
//                            00 eTSEL5
//                            01 ETPUA26 channel
//                            10 EMIOS12 channel
//                            11 ETRIG1 pin
//-----------------------------------------------------------------------------
// TSEL4        [29:28]   rw  eQADC trigger input select 4.
//                            Specifies the input for eQADC trigger 4.
//                            00 eTSEL4
//                            01 ETPUA27 channel
//                            10 EMIOS13 channel
//                            11 ETRIG0 pin
//-----------------------------------------------------------------------------
// TSEL3        [27:26]   rw  eQADC trigger input select 3.
//                            Specifies the input for eQADC trigger 3.
//                            00 eTSEL3
//                            01 ETPUA28 channel
//                            10 EMIOS14 channel
//                            11 ETRIG1 pin
//-----------------------------------------------------------------------------
// TSEL2        [25:24]   rw  eQADC trigger input select 2.
//                            Specifies the input for eQADC trigger 2.
//                            00 eTSEL2
//                            01 ETPUA29 channel
//                            10 EMIOS15 channel
//                            11 ETRIG0 pin
//-----------------------------------------------------------------------------
// TSEL1        [23:22]   rw  eQADC trigger input select 1.
//                            Specifies the input for eQADC trigger 1.
//                            00 eTSEL1
//                            01 ETPUA31 channel
//                            10 EMIOS11 channel
//                            11 ETRIG1 pin
//-----------------------------------------------------------------------------
// TSEL0        [21:20]   rw  eQADC trigger input select 0.
//                            Specifies the input for eQADC trigger 0.
//                            00 eTSEL0
//                            01 ETPUA30 channel
//                            10 EMIOS10 channel
//                            11 ETRIG0 pin
//-----------------------------------------------------------------------------
// 0             [19:0]   r   Reserved, should be cleared.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_ETISR_F_Tag
{
   bitfield32_t  TSEL5  :  BIT_2;  // Bits [31:30]
   bitfield32_t  TSEL4  :  BIT_2;  // Bits [29:28]
   bitfield32_t  TSEL3  :  BIT_2;  // Bits [27:26]
   bitfield32_t  TSEL2  :  BIT_2;  // Bits [25:24]
   bitfield32_t  TSEL1  :  BIT_2;  // Bits [23:22]
   bitfield32_t  TSEL0  :  BIT_2;  // Bits [21:20]
   bitfield32_t         :  BIT_20; // Bits [19:0]  Reserved

}  SIU_ETISR_F_T;

typedef union SIU_ETISR_Tag
{
   SIU_ETISR_F_T    F;
   uint32_t         U32;

}  SIU_ETISR_T;

//=============================================================================
// ID - External IRQ Input Select Register (SIU_EIISR)
//  Base Offset : 0x0904
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// ESEL15       [31:30]   rw  External IRQ input select 15.
//                            Specifies the input for IRQ 15.
//                            00 IRQ15 pin
//                            01 DSPI_B15 
//                            10 DSPI_C0 
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL14       [29:28]   rw  External IRQ input select 14.
//                            Specifies the input for IRQ 14.
//                            00 IRQ14 pin
//                            01 DSPI_B14 serialized input (EMIOS13 pin)
//                            10 DSPI_C15 serialized input (ETPUA11 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL13       [27:26]   rw  External IRQ input select 13.
//                            Specifies the input for IRQ 13.
//                            00 IRQ13 pin
//                            01 DSPI_B13 serialized input (ETPUA20 pin)
//                            10 DSPI_C14 serialized input (ETPUA10 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL12       [25:24]   rw  External IRQ input select 12.
//                            Specifies the input for IRQ 12.
//                            00 IRQ12 pin
//                            01 DSPI_B12 serialized input (ETPUA25 pin)
//                            10 DSPI_C13 serialized input (ETPUA9 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL11       [23:22]   rw  External IRQ input select 11.
//                            Specifies the input for IRQ 11.
//                            00 IRQ11 pin
//                            01 DSPI_B11 serialized input (ETPUA26 pin)
//                            10 DSPI_C12 serialized input (ETPUA8 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL10       [21:20]   rw  External IRQ input select 10.
//                            Specifies the input for IRQ 10.
//                            00 IRQ10 pin
//                            01 DSPI_B10 serialized input (ETPUA27 pin)
//                            10 DSPI_C11 serialized input (ETPUA7 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL9        [19:18]   rw  External IRQ input select 9.
//                            Specifies the input for IRQ 9.
//                            00 IRQ9 pin
//                            01 DSPI_B9  serialized input (ETPUA28 pin)
//                            10 DSPI_C10 serialized input (ETPUA6 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL8        [17:16]   rw  External IRQ input select 8.
//                            Specifies the input for IRQ 8.
//                            00 IRQ8 pin
//                            01 DSPI_B8  serialized input (ETPUA29 pin)
//                            10 DSPI_C9  serialized input (ETPUA5 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL7        [15:14]   rw  External IRQ input select 7.
//                            Specifies the input for IRQ 7.
//                            00 IRQ7 pin
//                            01 DSPI_B7 serialized input (ETPUA16 pin)
//                            10 DSPI_C8 serialized input (ETPUA4  pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL6        [13:12]   rw  External IRQ input select 6.
//                            Specifies the input for IRQ 6.
//                            00 Disabled
//                            01 DSPI_B6 serialized input (ETPUA17 pin)
//                            10 DSPI_C7 serialized input (ETPUA3  pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL5        [11:10]   rw  External IRQ input select 5.
//                            Specifies the input for IRQ 5.
//                            00 IRQ5 pin
//                            01 DSPI_B5 serialized input (ETPUA18 pin)
//                            10 DSPI_C6 serialized input (ETPUA2 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL4          [9:8]   rw  External IRQ input select 4.
//                            Specifies the input for IRQ 4.
//                            00 IRQ4 pin
//                            01 DSPI_B4 serialized input (ETPUA19 pin)
//                            10 DSPI_C5 serialized input (ETPUA1 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL3          [7:6]   rw  External IRQ input select 3.
//                            Specifies the input for IRQ 3.
//                            00 IRQ3 pin
//                            01 DSPI_B3 serialized input (ETPUA20 pin)
//                            10 DSPI_C4 serialized input (ETPUA0 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL2          [5:4]   rw  External IRQ input select 2.
//                            Specifies the input for IRQ 2.
//                            00 IRQ2 pin
//                            01 DSPI_B2 serialized input (ETPUA21 pin)
//                            10 DSPI_C3 serialized input (ETPUA15 pin)
//                            11 Reserved
//-----------------------------------------------------------------------------
// ESEL1          [3:2]   rw  External IRQ input select 1.
//                            Specifies the input for IRQ 1.
//                            00 IRQ1 pin
//                            01 DSPI_B1  serialized input (EMIOS10 pin)
//                            10 DSPI_C2  serialized input (ETPUA14 pin)
//                            11 eMIOS[15]_IRQ[1] pin
//-----------------------------------------------------------------------------
// ESEL0          [1:0]   rw  External IRQ input select 0.
//                            Specifies the input for IRQ 0.
//                            00 IRQ0 pin
//                            01 DSPI_B0 serialized input (EMIOS11 pin)
//                            10 DSPI_C1 serialized input (ETPUA5 pin)
//                            11 eMIOS[14]_IRQ[0] pin
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_EIISR_F_Tag
{
   bitfield32_t  ESEL15  :  BIT_2;  //  Bits [31:30]
   bitfield32_t  ESEL14  :  BIT_2;  //  Bits [29:28]
   bitfield32_t  ESEL13  :  BIT_2;  //  Bits [27:26]
   bitfield32_t  ESEL12  :  BIT_2;  //  Bits [25:24]
   bitfield32_t  ESEL11  :  BIT_2;  //  Bits [23:22]
   bitfield32_t  ESEL10  :  BIT_2;  //  Bits [21:20]
   bitfield32_t  ESEL9   :  BIT_2;  //  Bits [19:18]
   bitfield32_t  ESEL8   :  BIT_2;  //  Bits [17:16]
   bitfield32_t  ESEL7   :  BIT_2;  //  Bits [15:14]
   bitfield32_t  ESEL6   :  BIT_2;  //  Bits [13:12]
   bitfield32_t  ESEL5   :  BIT_2;  //  Bits [11:10]
   bitfield32_t  ESEL4   :  BIT_2;  //  Bits [9:8]
   bitfield32_t  ESEL3   :  BIT_2;  //  Bits [7:6]
   bitfield32_t  ESEL2   :  BIT_2;  //  Bits [5:4]
   bitfield32_t  ESEL1   :  BIT_2;  //  Bits [3:2]
   bitfield32_t  ESEL0   :  BIT_2;  //  Bits [1:0]

}  SIU_EIISR_F_T;

typedef union SIU_EIISR_Tag
{
   SIU_EIISR_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];
   uint8_t          U8[SIU_ARRAY_SIZE_4];

}  SIU_EIISR_T;

//=============================================================================
// ID - DSPI Input Select Register (SIU_DISR)
//  Base Offset : 0x0908
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:24]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// SINSELB      [23:22]  rw   DSPI_B data input select.
//                            Specifies the source of DSPI_B data input.
//                            00 SINB_PCSC2_GPIO103 pin
//                            01 Reserved
//                            10 SOUTC
//                            11 SOUTD
//-----------------------------------------------------------------------------
// SSSELB       [21:20]  rw   DSPI_B slave select input select.
//                            Specifies the source of the DSPI_B
//                            slave select input.
//                            00 PCSB0_PCSD2_GPIO105 pin
//                            01 Reserved
//                            10 PCSC0 (Master)
//                            11 Reserved
//-----------------------------------------------------------------------------
// SCKSELB      [19:18]  rw   DSPI_B clock input select.
//                            Specifies the source of the DSPI_B
//                            clock input.
//                            00 SCKB_PCSC1_GPIO102 pin
//                            01 Reserved
//                            10 SCKC (Master)
//                            11 Reserved
//-----------------------------------------------------------------------------
// TRIGSELB     [17:16]  rw   DSPI_B trigger input select.
//                            Specifies the source of the DSPI_B
//                            trigger input for master or slave mode.
//                            00 Reserved
//                            01 Reserved
//                            10 PCSC4
//                            11 Reserved
//-----------------------------------------------------------------------------
// SINSELC      [15:14]  rw   DSPI_C data input select.
//                            Specifies the source of the DSPI_C data input.
//                            00 PCSA2_SINC_GPIO108 pin
//                            01 Reserved
//                            10 SOUTB
//                            11 Reserved
//-----------------------------------------------------------------------------
// SSSELC       [13:12]  rw   DSPI_C slave select input select.
//                            Specifies the source of the DSPI_C
//                            slave select input.
//                            00 PCSB5_PCSC0_GPIO110 pin
//                            01 Reserved
//                            10 PCSB0 (Master)
//                            11 Reserved
//-----------------------------------------------------------------------------
// SCKSELC      [11:10]  rw   DSPI_C clock input select.
//                            Specifies the source of the DSPI_C clock
//                            input when in slave mode.
//                            00 PCSB4_SCKC_GPIO109 pin
//                            01 Reserved
//                            10 SCKB (Master)
//                            11 Reserved
//-----------------------------------------------------------------------------
// TRIGSELC     [9:8]    rw   DSPI_C trigger input select.
//                            Specifies the source of the DSPI_C
//                            trigger input for master or slave mode.
//                            00 Reserved
//                            01 Reserved
//                            10 PCSB4
//                            11 Reserved
//-----------------------------------------------------------------------------
// 0            [7:0]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_DISR_F_Tag
{
   bitfield32_t                         :  BIT_8;  //  Bits [31:24] Reserved
   bitfield32_t  SINSELB                :  BIT_2;  //  Bits [23:22]
   bitfield32_t  SSSELB                 :  BIT_2;  //  Bits [21:20]
   bitfield32_t  SCKSELB                :  BIT_2;  //  Bits [19:18]
   bitfield32_t  TRIGSELB               :  BIT_2;  //  Bits [17:16]
   bitfield32_t  SINSELC                :  BIT_2;  //  Bits [15:14]
   bitfield32_t  SSSELC                 :  BIT_2;  //  Bits [13:12]
   bitfield32_t  SCKSELC                :  BIT_2;  //  Bits [11:10]
   bitfield32_t  TRIGSELC               :  BIT_2;  //  Bits [9:8]
   bitfield32_t                         :  BIT_8;  //  Bits [7:0] Reserved

}  SIU_DISR_F_T;

typedef union SIU_DISR_Tag
{
   SIU_DISR_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];
   uint8_t          U8[SIU_ARRAY_SIZE_4];

}  SIU_DISR_T;

//=============================================================================
// ID - Mux Select Register 3 (SIU_ISEL3)
//  Base Offset : 0x090C
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:30]  r    Reserved
//-----------------------------------------------------------------------------
// eTSELx       [29:0]   rw   External eQADC trigger inputs source
// (x=0-5) 
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual

//=============================================================================
typedef struct SIU_ISEL3_F_Tag
{
   bitfield32_t             :  BIT_2;  //  Bits [31:30] Reserved
   bitfield32_t   eTSEL5    :  BIT_5;  //  Bits [29:25]
   bitfield32_t   eTSEL4    :  BIT_5;  //  Bits [24:20]
   bitfield32_t   eTSEL3    :  BIT_5;  //  Bits [19:15]
   bitfield32_t   eTSEL2    :  BIT_5;  //  Bits [14:10]
   bitfield32_t   eTSEL1    :  BIT_5;  //  Bits [9:5]
   bitfield32_t   eTSEL0    :  BIT_5;  //  Bits [4:0]
   
}  SIU_ISEL3_F_T;

typedef union SIU_ISEL3_Tag
{
   SIU_ISEL3_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];
   uint8_t          U8[SIU_ARRAY_SIZE_4];

}  SIU_ISEL3_T;

//=============================================================================
// ID - Mux Select Register 8 (SIU_ISEL8)
//  Base Offset : 0x0920
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:21]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// eSEL5          20     rw   eTPU[29] input channel.
//                            1 eTPU channel 29
//                            0 DSPI_B Serialized input 8
//-----------------------------------------------------------------------------
// 0            [19:17]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// eSEL4          16     rw   eTPU[29] input channel.
//                            1 eTPU channel 28
//                            0 DSPI_B Serialized input 9
//-----------------------------------------------------------------------------
// 0            [15:13]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// eSEL3          12     rw   eTPU[29] input channel.
//                            1 eTPU channel 27
//                            0 DSPI_B Serialized input 10
//-----------------------------------------------------------------------------
// 0            [11:9]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// eSEL2          8      rw   eTPU[29] input channel.
//                            1 eTPU channel 26
//                            0 DSPI_B Serialized input 11
//-----------------------------------------------------------------------------
// 0            [7:5]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// eSEL1          4      rw   eTPU[29] input channel.
//                            1 eTPU channel 25
//                            0 DSPI_B Serialized input 12
//-----------------------------------------------------------------------------
// 0            [3:1]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// eSEL0          0      rw   eTPU[29] input channel.
//                            1 eTPU channel 24
//                            0 DSPI_B Serialized input 13
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_ISEL8_F_Tag
{
   bitfield32_t               :  BIT_11; //  Bit [31:21] Reserved
   bitfield32_t   eSEL5       :  BIT_1;  //  Bit  20
   bitfield32_t               :  BIT_3;  //  Bits [19:17] Reserved
   bitfield32_t   eSEL4       :  BIT_1;  //  Bit  16
   bitfield32_t               :  BIT_3;  //  Bits [15:13] Reserved
   bitfield32_t   eSEL3       :  BIT_1;  //  Bit  12
   bitfield32_t               :  BIT_3;  //  Bits [11:9] Reserved
   bitfield32_t   eSEL2       :  BIT_1;  //  Bit  8
   bitfield32_t               :  BIT_3;  //  Bits [7:5] Reserved
   bitfield32_t   eSEL1       :  BIT_1;  //  Bit  4
   bitfield32_t               :  BIT_3;  //  Bits [3:1] Reserved
   bitfield32_t   eSEL0       :  BIT_1;  //  Bit  0
   
}  SIU_ISEL8_F_T;

typedef union SIU_ISEL8_Tag
{
   SIU_ISEL8_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2];
}  SIU_ISEL8_T;

//=============================================================================
// ID - IMux Select Register 9 (SIU_ISEL9)
//  Base Offset : 0x0924
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:5]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// eTSEL0A      [4-0]    rw   This mode requires a second trigger for 
//                            queue 0.The source for this trigger can come 
//                            from ETPU,EMIOS or PIT channels. A mux select 
//                            register is required to select the source of 
//                            this new queue0 trigger.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual

//=============================================================================
typedef struct SIU_ISEL9_F_Tag
{
   bitfield32_t               :  BIT_27; //  Bits [31:5] Reserved
   bitfield32_t   eTSEL0A     :  BIT_5;  //  Bits [4:0]
      
}  SIU_ISEL9_F_T;

typedef union SIU_ISEL9_Tag
{
   SIU_ISEL9_F_T    F;
   uint32_t         U32;
   uint16_t         U16[SIU_ARRAY_SIZE_2]; 

}  SIU_ISEL9_T;

//=============================================================================
// ID - Chip Configuration Register (SIU_CCR)
//  Base Offset : 0x0980
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:18]  r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// MATCH          17     r    Compare register match.
//                            The MATCH bit is a read only bit that indicates 
//                            the result of a 64-bit comparison between the 
//                            values in the SIU_CBRH and SIU_CBRL registers and
//                            the censorship word stored in the shadow block of
//                            flash. The match input is asserted if the values
//                            are equal.
//                            0 Match input signal is negated.
//                            1 Match input signal is asserted.
//-----------------------------------------------------------------------------
// DISNEX         16     r    Disable Nexus.
//                            The DISNEX bit is a read only bit that holds
//                            the value of the Nexus disable input signal
//                            to the SIU. When the system reset negates, 
//                            the value in this bit depends on the censorship
//                            control word and the boot configuration bits.
//                            0 Nexus disable input signal is negated.
//                            1 Nexus disable input signal is asserted.
//-----------------------------------------------------------------------------
// 0            [15:2]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// CRSE           1      rw   Calibration Reflection Suppression Enable
//                            The CRSE bit enables the suppression of reflections
//                            from the EBI’s calibration bus onto the
//                            non-calibration bus
//                            0 Calibration reflection suppression is disabled
//                            1 Calibration reflection suppression is enabled   
//-----------------------------------------------------------------------------
// 0              0      r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_CCR_F_Tag
{
   bitfield32_t               :  BIT_14; // Bits [31:18]  Reserved
   bitfield32_t  MATCH        :  BIT_1;  // Bit  17
   bitfield32_t  DISNEX       :  BIT_1;  // Bit  16
   bitfield32_t               :  BIT_14; // Bits [15:2]   Reserved
   bitfield32_t  CRSE         :  BIT_1;  // Bit 1
   bitfield32_t               :  BIT_1;  // Bit 0    Reserved
   

}  SIU_CCR_F_T;

typedef union SIU_CCR_Tag
{
   SIU_CCR_F_T    F;
   uint32_t       U32;

}  SIU_CCR_T;

//=============================================================================
// ID - External Clock Control Register (SIU_ECCR)
//  Base Offset : 0x0984
//
// Reset Value  : 0x0000 1001
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:4]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// EBTS           3      rw   External bus tap select.
//                            The EBTS bit changes the phase relationship
//                            between the system clock and CLKOUT.
//                            Changing the phase relationship so that CLKOUT
//                            is advanced in relation to system clock
//                            increases the output hold time of the external
//                            bus signals to a non-zero value. It also
//                            increases the output delay times, increases
//                            the input hold times to non-zero values, and
//                            decreases the input setup times. Refer to the
//                            Electrical Specifications for how the EBTS bit
//                            affects the external bus timing.
//                            0 External bus signals have zero output
//                              hold times.
//                            1 External bus signals have non-zero output
//                              hold times.
//-----------------------------------------------------------------------------
// 0              2      r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// EBDF         [1:0]    rw   External bus division factor.
//                            The EBDF field specifies the frequency ratio
//                            between the system clock and the external
//                            clock,CLKOUT. The CLKOUT frequency is divided
//                            from the system clock frequency according to
//                            the descriptions below.
//                            This divider must be kept as divide-by-2 when
//                            operating in Dual Controller Mode
//                            00 Divide by 1
//                            01 Divide by 2
//                            10 Reserved
//                            11 Divide by 4
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_ECCR_F_Tag
{
   bitfield32_t             :  BIT_28; // Bits [31:4]  Reserved   
   bitfield32_t  EBTS       :  BIT_1;  // Bit  3
   bitfield32_t             :  BIT_1;  // Bit  2       Reserved
   bitfield32_t  EBDF       :  BIT_2;  // Bits [1:0]

}  SIU_ECCR_F_T;

typedef union SIU_ECCR_Tag
{
   SIU_ECCR_F_T    F;
   uint32_t      U32;

}  SIU_ECCR_T;

//=============================================================================
// ID - Compare A High Register (SIU_CARH)
//  Base Offset : 0x0988
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// CMPAH        [31:0]   rw   32-bit value that is compared against
//                            the value in the SIU_CMPBH register.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

//=============================================================================
// ID - Compare A Low Register (SIU_CARL)
//  Base Offset : 0x98C
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// CMPAL         [31:0]   rw  32-bit value that is compared against
//                            the value in the SIU_CMPBL register.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

//=============================================================================
// ID - Compare B High Register (SIU_CBRH)
//  Base Offset : 0x0990
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// CMPBH         [31:0]   rw  32-bit value that is compared against
//                            the value in the SIU_CMPAH register.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================

//=============================================================================
// ID - Compare B Low Register (SIU_CBRL)
//  Base Offset : 0x994
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// CMPBL         [31:0]   rw  32-bit value that is compared against
//                            the value in the SIU_CMPAL register.
//
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
//=============================================================================
// ID - System Clock Register (SIU_SYSDIV)
//  Base Offset : 0x09A0
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// 0            [31:5]   r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// BYPASS         4      rw   Bypass bit.
//                            1 system clock divider is bypassed
//                            0 system clock divider is not bypassed
//-----------------------------------------------------------------------------
// SYSCLKDIV    [3:2]    rw   System Clock Divide
//                            The SYSCLKDIV bits select the divider value for 
//                            the system clock, i.e., the output of the FMPLL.
//                            SYSCLKDIV divider is required in addition to the
//                            RFD to allow the other sources for the system clk
//                            i.e., output of the FMPLL, to be divided down to
//                            slowest frequencies to improve power. The output
//                            of clock divider is nominally a 50% duty cycle. 
//                            00 = Divide by 2
//                            01 = Divide by 4
//                            10 = Divide by 8
//                            11 = Divide by 16
//-----------------------------------------------------------------------------
// 0            [1:0]    r    Reserved, should be cleared.
//-----------------------------------------------------------------------------
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_SYSDIV_F_Tag
{
   bitfield32_t                :  BIT_27; // Bits [31:5]  Reserved   
   bitfield32_t  BYPASS        :  BIT_1;  // Bit  4
   bitfield32_t  SYSCLKDIV     :  BIT_2;  // Bits [3:2]
   bitfield32_t                :  BIT_2;  // Bits [1:0]   Reserved

}  SIU_SYSDIV_F_T;

typedef union SIU_SYSDIV_Tag
{
   SIU_SYSDIV_F_T    F;
   uint32_t      U32;

}  SIU_SYSDIV_T;
//=============================================================================
// ID - Halt Register (SIU_HLT)
//  Base Offset : 0x09A4
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// CPUSTP         31     rw   CPU stop request. When asserted, a stop request
//                            is sent to the following modules:CPU, cross-bar,
//                            peripheral bridge, system RAM, Flash, STM, DMA.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [30:29]  r    Reserved
//-----------------------------------------------------------------------------
// SWTSTP         28     rw   SWT stop request. When asserted, a stop request
//                            is sent to the Software Watchdog Timer.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0              27     r    Reserved
//-----------------------------------------------------------------------------
// TPUSTP         26     rw   eTPU stop request. When asserted, a stop 
//                            request is sent to the eTPU module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// NPCSTP         25     rw   Nexus stop request. When asserted, a stop 
//                            request is sent to the Nexus Controller.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// EBISTP         24     rw   EBI stop request. When asserted, a stop request 
//                            is sent to the external bus controller which 
//                            handles the calibration interface.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// ADCSTP         23     rw   eQADC stop request. When asserted, a stop 
//                            request is sent to the eQADC module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0              22     r    Reserved
//-----------------------------------------------------------------------------
// MIOSSTP        21     rw   eMIOS stop request. When asserted, a stop 
//                            request is sent to the eMIOS module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// DFILSTP        20     rw   Decimation filter stop request.When asserted, a
//                            stop request is sent to the decimation filter 
//                            module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0              19     r    Reserved
//-----------------------------------------------------------------------------
// PITSTP         18     rw   PIT stop request. When asserted, a stop request
//                            is sent to the periodical internal timer module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [17:15]  r    Reserved
//-----------------------------------------------------------------------------
// CNCSTP         14     rw   FlexCAN C stop request. When asserted, a stop 
//                            request is sent to the FlexCAN C module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// CNBSTP         13     rw   FlexCAN B stop request. When asserted, a stop 
//                            request is sent to the FlexCAN B module.
//                            1  Stop mode request
//                            0  Normal operation
//-----------------------------------------------------------------------------
// CNASTP         12     rw   FlexCAN A stop request. When asserted, a stop
//                            request is sent to the FlexCAN A module.
//                            1  Stop mode request
//                            0 = Normal operation
//-----------------------------------------------------------------------------
// SPIDSTP        11     rw   DSPI D stop request. When asserted, a stop 
//                            request is sent to the DSPI D.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// SPICSTP        10     rw   DSPI C stop request. When asserted, a stop 
//                            request is sent to the DSPI C.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// SPIBSTP        9      rw   DSPI B stop request. When asserted, a stop 
//                            request is sent to the DSPI B.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [8:3]    r    Reserved
//-----------------------------------------------------------------------------
// SCICSTP        2      rw   eSCI Cstop request. When asserted, a stop 
//                            request is sent to the eSCI B module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// SCIBSTP        1      rw   eSCI B stop request. When asserted, a stop 
//                            request is sent to the eSCI B module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// SCIASTP        0      rw   eSCI A stop request. When asserted, a stop 
//                            request is sent to the eSCI A module.
//                            1  Stop mode request
//                            0  Normal operation
//=============================================================================
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_HLT_F_Tag
{
   bitfield32_t  CPUSTP        :  BIT_1;  // Bit  31   
   bitfield32_t                :  BIT_2;  // Bits [30:29]  Reserved
   bitfield32_t  SWTSTP        :  BIT_1;  // Bit  28
   bitfield32_t                :  BIT_1;  // Bit  27       Reserved
   bitfield32_t  TPUSTP        :  BIT_1;  // Bit  26
   bitfield32_t  NPCSTP        :  BIT_1;  // Bit  25   
   bitfield32_t  EBISTP        :  BIT_1;  // Bit  24     
   bitfield32_t  ADCSTP        :  BIT_1;  // Bit  23
   bitfield32_t                :  BIT_1;  // Bit  22       Reserved
   bitfield32_t  MIOSSTP       :  BIT_1;  // Bit  21   
   bitfield32_t  DFILSTP       :  BIT_1;  // Bit  20     
   bitfield32_t                :  BIT_1;  // Bit  19       Reserved
   bitfield32_t  PITSTP        :  BIT_1;  // Bit  18  
   bitfield32_t                :  BIT_3;  // Bits [17:15]  Reserved
   bitfield32_t  CNCSTP        :  BIT_1;  // Bit  14   
   bitfield32_t                :  BIT_1;  // Bit  13       Reserved
   bitfield32_t  CNASTP        :  BIT_1;  // Bit  12  
   bitfield32_t                :  BIT_1;  // Bit  11       Reserved
   bitfield32_t  SPICSTP       :  BIT_1;  // Bit  10  
   bitfield32_t  SPIBSTP       :  BIT_1;  // Bit  9    
   bitfield32_t                :  BIT_7;  // Bits [8:2]    Reserved
   bitfield32_t  SCIBSTP       :  BIT_1;  // Bit  1
   bitfield32_t  SCIASTP       :  BIT_1;  // Bit  0

}  SIU_HLT_F_T;

typedef union SIU_HLT_Tag
{
   SIU_HLT_F_T    F;
   uint32_t      U32;

}  SIU_HLT_T;
//=============================================================================
// ID - Halt Acknowledge Register (SIU_HLTACK)
//  Base Offset : 0x09A8
//
// Reset Value  : 0x0000 0000
//
// Field        Bits     Type Description
// ============ ======== ==== ===============================================
// CPUACK         31     r    CPU stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            following modules:CPU, cross-bar, peripheral 
//                            bridge, system RAM, Flash, STM, DMA.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [30:29]  r    Reserved
//-----------------------------------------------------------------------------
// SWTACK         28     r    SWT stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            Software Watchdog Timer. 
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0              27     r    Reserved
//-----------------------------------------------------------------------------
// TPUACK         26     r    eTPU stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            eTPU module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// NPCACK         25     r    Nexus stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            Nexus controller.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// EBIACK         24     r    EBI stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            external bus controller which handles the 
//                            calibration interface.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// ADCACK         23     r    eQADC stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            eQADC module. 
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0              22     r    Reserved
//-----------------------------------------------------------------------------
// MIOSACK        21     r    eMIOS stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            eMIOS module. 
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// DFILACK        20     r    Decimation filter stop acknowledge. When 
//                            asserted, indicates that a stop acknowledge was 
//                            received from the Decimation filter. 
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0              19     r    Reserved
//-----------------------------------------------------------------------------
// PITACK         18     r    PIT stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            periodical internal timer module. 
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [17:15]  r    Reserved
//-----------------------------------------------------------------------------
// CNCACK         14     r    FlexCAN C stop acknowledge. When asserted, 
//                            indicates that a stop acknowledge was received 
//                            from the FlexCAN C module. 
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [17:15]  r    Reserved
//-----------------------------------------------------------------------------
// CNAACK         12     r    FlexCAN A stop acknowledge. When asserted, 
//                            indicates that a stop acknowledge was received 
//                            from the FlexCAN A module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [17:15]  r    Reserved
//-----------------------------------------------------------------------------
// SPICACK        10     r    DSPI C stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            DSPI C.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// SPIBACK        9      r    DSPI B stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            DSPI B.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// 0            [8:3]    r    Reserved
//-----------------------------------------------------------------------------
// SCIBACK        1      r    eSCI B stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            eSCI B module.
//                            1 Stop mode request
//                            0 Normal operation
//-----------------------------------------------------------------------------
// SCIAACK        0      r    eSCI A stop acknowledge. When asserted, indicates
//                            that a stop acknowledge was received from the
//                            eSCI A module. 
//                            1 Stop mode request
//                            0 Normal operation
//=============================================================================
// Note: The Bit numbering is for the software implementation
//       not a copy from the manual
//=============================================================================
typedef struct SIU_HLTACK_F_Tag
{
   bitfield32_t  CPUACK     :  BIT_1;  // Bit  31
   bitfield32_t             :  BIT_2;  // Bits [30:29]  Reserved
   bitfield32_t  SWTACK     :  BIT_1;  // Bit  28
   bitfield32_t             :  BIT_1;  // Bit  27       Reserved
   bitfield32_t  TPUACK     :  BIT_1;  // Bit  26
   bitfield32_t  NPCACK     :  BIT_1;  // Bit  25
   bitfield32_t  EBIACK     :  BIT_1;  // Bit  24
   bitfield32_t  ADCACK     :  BIT_1;  // Bit  23
   bitfield32_t             :  BIT_1;  // Bit  22       Reserved
   bitfield32_t  MIOSACK    :  BIT_1;  // Bit  21
   bitfield32_t  DFILACK    :  BIT_1;  // Bit  20
   bitfield32_t             :  BIT_1;  // Bit  19       Reserved
   bitfield32_t  PITACK     :  BIT_1;  // Bit  18
   bitfield32_t             :  BIT_3;  // Bits [17:15]  Reserved
   bitfield32_t  CNCACK     :  BIT_1;  // Bit  14
   bitfield32_t             :  BIT_1;  // Bit  13       Reserved
   bitfield32_t  CNAACK     :  BIT_1;  // Bit  12
   bitfield32_t             :  BIT_1;  // Bit  11       Reserved
   bitfield32_t  SPICACK    :  BIT_1;  // Bit  10
   bitfield32_t  SPIBACK    :  BIT_1;  // Bit  9
   bitfield32_t             :  BIT_7;  // Bits [8:2]    Reserved
   bitfield32_t  SCIBACK    :  BIT_1;  // Bit  1
   bitfield32_t  SCIAACK    :  BIT_1;  // Bit  0

}  SIU_HLTACK_F_T;

typedef union SIU_HLTACK_Tag
{
   SIU_HLTACK_F_T    F;
   uint32_t      U32;

}  SIU_HLTACK_T;

//=============================================================================
#define SIU_RESERVED_0x000C     (0x000C)
#define SIU_RESERVED_0x0284     (0x0284)
#define SIU_RESERVED_0x0062     (0x0062)

#define SIU_RESERVED_0x0016     (0x0016)
#define SIU_RESERVED_0x0010     (0x0010)
#define SIU_RESERVED_0x0058     (0x0058)
#define SIU_RESERVED_0x0008     (0x0008)
#define SIU_RESERVED_0x0054     (0x0054)

#define SIU_PCR_QUANTITY   (0x019E)
#define SIU_GPDO_QUANTITY  (0x019E)
#define SIU_GPDI_QUANTITY  (0x00EA)

typedef volatile struct SIU_Tag
{
   SIU_MIDR2_T  MIDR2;                              // 0x0000 - 0x0003
   SIU_MIDR_T   MIDR;                               // 0x0004 - 0x0007
   uint32_t     TST;                                // 0x0008 - 0x000B
   SIU_RSR_T    RSR;                                // 0x000C - 0x000F
   SIU_SRCR_T   SRCR;                               // 0x0010 - 0x0013
   SIU_EISR_T   EISR;                               // 0x0014 - 0x0017
   SIU_DIRER_T  DIRER;                              // 0x0018 - 0x001B
   SIU_DIRSR_T  DIRSR;                              // 0x001C - 0x001F
   SIU_OSR_T    OSR;                                // 0x0020 - 0x0023
   SIU_ORER_T   ORER;                               // 0x0024 - 0x0027
   SIU_IREER_T  IREER;                              // 0x0028 - 0x002B
   SIU_IFEER_T  IFEER;                              // 0x002C - 0x002F
   SIU_IDFR_T   IDFR;                               // 0x0030 - 0x0033
   uint8_t      reserved_0[SIU_RESERVED_0x000C];    // 0x0034 - 0x003F
   SIU_PCR_T    PCR[SIU_PCR_QUANTITY];              // 0x0040 - 0x037B   
   uint8_t      reserved_1[SIU_RESERVED_0x0284];    // 0x037C - 0x05FF
   SIU_GPDO_T   GPDO[SIU_GPDO_QUANTITY];            // 0x0600 - 0x079C
   uint8_t      reserved_2[SIU_RESERVED_0x0062];    // 0x079E - 0x07FF
   SIU_GPDI_T   GPDI[SIU_GPDI_QUANTITY];            // 0x0800 - 0x08E9
   uint8_t      reserved_3[SIU_RESERVED_0x0016];    // 0x08EA - 0x08FF
   SIU_ETISR_T  ETISR;                              // 0x0900 - 0x0903
   SIU_EIISR_T  EIISR;                              // 0x0904 - 0x0907
   SIU_DISR_T   DISR;                               // 0x0908 - 0x090B
   SIU_ISEL3_T  ISEL3;                              // 0x090C - 0x090F
   uint8_t      reserved_4[SIU_RESERVED_0x0010];    // 0x0910 - 0x091F
   SIU_ISEL8_T  ISEL8;                              // 0x0920 - 0x0923
   SIU_ISEL9_T  ISEL9;                              // 0x0924 - 0x0927
   uint8_t      reserved_5[SIU_RESERVED_0x0058];    // 0x0928 - 0x097F
   SIU_CCR_T    CCR;                                // 0x0980 - 0x0983
   SIU_ECCR_T   ECCR;                               // 0x0984 - 0x0987
   uint32_t     CARH;                               // 0x0988 - 0x098B
   uint32_t     CARL ;                              // 0x098C - 0x098F
   uint32_t     CBRH;                               // 0x0990 - 0x0993
   uint32_t     CBRL;                               // 0x0994 - 0x0997
   uint8_t      reserved_6[SIU_RESERVED_0x0008];    // 0x0998 - 0x099F
   SIU_SYSDIV_T SYSDIV;                             // 0x09A0 - 0x09A3
   SIU_HLT_T    HLT;                                // 0x09A4 - 0x09A7
   SIU_HLTACK_T HLTACK;                             // 0x09A8 - 0x09AB
   uint8_t      reserved_7[SIU_RESERVED_0x0054];    // 0x09AC - 0x09FF
    
}  SIU_T;

#endif // HW_SIU_H

