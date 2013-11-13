#ifndef POWERPC_DIABDATA_H
#define POWERPC_DIABDATA_H

//=============================================================================
// Include Files
//=============================================================================
#include "powerpc_diabdata_types.h"

//=============================================================================
// Function Prototypes
//=============================================================================

void Ldmst( uint32_t *address, uint32_t value, uint32_t position, uint32_t width);
//uint32_t Extract_Bits( uint32_t value, uint32_t position, uint32_t width );
//uint32_t Insert_Bits( uint32_t old_value, uint32_t value, uint32_t position, uint32_t width );
stack_pointer_t Get_Stack_Pointer( void );
void Set_Stack_Pointer( void * New_Stack_Pointer );
uint32_t Count_Leading_Zeros_For_UINT32 ( uint32_t word );
void Set_SPR( uint32_t spr, uint32_t value );
uint32_t Get_SPR( uint32_t spr );
void Disable_Interrupts( void );
void Enable_Interrupts( void );



//=============================================================================
// Define Special Purpose Register (SPR) numbers.
//=============================================================================
#define SPR_DEC     22  // Decrementer Register
#define SPR_SRR0    26  // Machine Status Save and Restore Register 0
#define SPR_SRR1    27  // Machine Status Save and Restore Register 1
#define SPR_EIE     80  // External Interrupts Enable  psuedo-SPR
#define SPR_EID     81  // External Interrupts Disable psuedo-SPR
#define SPR_NRI     82  // Non-Recoverable Interrupts  psuedo-SPR
#define SPR_DER    149  // Debug Enable Register
#define SPR_ICTRL  158  // I-Bus Support Control Register
#define SPR_BBCMCR 560  // Burst Buffer Controller Module Config Register
#define SPR_L2UMCR 568  // L-Bus <=> U-Bus Module COnfig Register
#define SPR_IMMR   638  // Internal Memory Mapping Register

//=============================================================================
//   Standard Type Specifiers:
//=============================================================================
#define INLINE    __inline__

#define INTERRUPT __interrupt__

#define CPU_IS_LITTLE_ENDIAN (false)

#define HUGE


//=============================================================================
// Ldmst
//
// @func Insert bits from into an address using the value, position and width.
//
// @parm <t uint32_t>* | address | the address to insert the bits.
//
// @parm <t uint32_t> | value | the 32 bit value to insert.
//
// @parm <t uint32_t> | position | value from 0 to 31
//
// @parm <t uint32_t> | width | value from 1 to 32
//
// @rdesc none.
//
//=============================================================================
asm void Ldmst( uint32_t *address, uint32_t value, uint32_t position, uint32_t width)
{
% reg address, value, position; lab loop; con width
! "r5","r4", "r6" /* scratch registers used */
loop:
   addi     r4, r0, ((width << 1) - 1) # create the mask
   slw      r4, r4, position           # move the mask up to the position
   lwarx    r5, 0, address             # get the value to modify
   andc     r6, r5, r4                 # and it with the twos compliment
   slw      r4, value, position        # shift our value
   or       r5, r6, r4                 # or together
   stwcx.   r5, 0,address              # store insert
   bne      loop                       # in case interrupted before stwcz.
}
#if 0

//=============================================================================
// Extract_Bits
//
// @func Extract bits from a 32 bit value given the position and width.
//
// @parm <t uint32_t> | value | the 32 bit value to extract the bits from.
//
// @parm <t uint32_t> | position | value from 0 to 31
//
// @parm <t uint32_t> | width | value from 1 to 32
//
// @rdesc the bits extracted.
//
//=============================================================================

asm uint32_t Extract_Bits( uint32_t value, uint32_t position, uint32_t width )
{
% reg value, position; con width
	subfic	position,position,32
   rlwnm    r3, value, position, 32-width, 31
} 


//=============================================================================
// Insert_Bits
//
// @func Insert bits into a 32 bit value given the position and width.
//
// @parm <t uint32_t> | old_value | the 32 bit value to insert the bits into.
//
// @parm <t uint32_t> | value | the 32 bit value to insert the bits into.
//
// @parm <t uint32_t> | position | value from 0 to 31
//
// @parm <t uint32_t> | width | value from 1 to 32
//
// @rdesc the new value.
//
//=============================================================================


asm uint32_t Insert_Bits( uint32_t old_value, uint32_t value, uint32_t position, uint32_t width )
{
% reg value, old_value; con width, position
   mr       r3, old_value
   rlwimi   r3, value, position, (31-position)-width+1,31-position
}
#endif

//=============================================================================
// Put_Bit
//
// @func Insert a bit into a 32 bit value given the value, address and position.
//
// @parm <t uint32_t> | value | the 32 bit value to extract the bits from.
//
// @parm <t uint32_t>* | address | the address to insert the bits.
//
// @parm <t uint32_t> | position | value from 0 to 31
//
// @rdesc none.
//
//=============================================================================


#define Put_Bit(value,address,position) (Ldmst((value),(address),(position),1))




#if 0
// Function to disable interrupts
asm void Disable_Interrupts( void )
{
  !
   .set noreorder /* needed to prevent DIAB to reorder the asm instructions */
   // wrteei 0  /* force MSR[EE] to 0 */
    .set reorder /* allow reordering of asm instruction from now on */
}

// Function to enable interrupts
asm void Enable_Interrupts( void )
{
!
    .set noreorder /* needed to prevent DIAB to reorder the asm instructions */
    wrteei 1  /* force MSR[EE] to 1 */
    .set reorder /* allow reordering of asm instruction from now on */
}
#endif

// Function to disable interrupts
asm void Disable_Interrupts( void )
{
!
   wrteei    0
}

// Function to enable interrupts
asm void Enable_Interrupts( void )
{
!
   wrteei    1
}


//=============================================================================
//   Interrupt Handling:
//=============================================================================
asm uint32_t MFMSR( void )
{
   // write msr contents to the R0
   mfmsr    r0       
}

asm uint32_t MTMSR( uint32_t in_msr )
{
% reg in_msr
   // the "in_value" argument will be in R3
   // write R3 contents to the msr
   mtmsr    in_msr       
}


//=============================================================================
// ESYS_READ_MSR_VALUE
//
// @func read the given value in the MSR special function register.
//
// @rdesc <t uint32_t> | contents of MSR register.
//
//=============================================================================
asm uint32_t ESYS_READ_MSR_VALUE(void)
{
! "r3"
   mfmsr   r3
}

//=============================================================================
// ESYS_READ_MSR_VALUE
//
// @func store the given value in the MSR special function register.
//
// @parm <t uint32_t> | msr_value | value to put in MSR register.
//
// @rdesc none.
//
//=============================================================================
asm void ESYS_STORE_MSR_VALUE_VAR(uint32_t msr_value)
{
% reg msr_value
! "r3"
   isync
   mtmsr   msr_value
   isync
}



// Function to retrieve current interrupt state (disabled/enabled)
INLINE interrupt_state_t Get_Interrupt_State( void )
{
   uint32_t msr_copy;

   msr_copy = ESYS_READ_MSR_VALUE();

   // The interrupt is bit 16. Test this bit and return the value
   return (( msr_copy >> 15 ) & (uint32_t)0x1);
}

// Function to test current interrupt state
INLINE bool Interrupts_Are_Disabled( void )
{
   return( Get_Interrupt_State() ? false : true );
}

// Function to test current interrupt state
INLINE bool Interrupts_Are_Enabled( void )
{
   return( Get_Interrupt_State() ? true : false );
}

// Function to restore previous interrupt state (disabled/enabled)
INLINE void Set_Interrupt_State( interrupt_state_t interrupt_state )
{
   if( interrupt_state )
   {
      Enable_Interrupts();
   }
   else
   {
      Disable_Interrupts();
   }
}

//=============================================================================
// Stack Pointer
//=============================================================================
/* Function to retrieve current stack pointer */
asm stack_pointer_t Get_Stack_Pointer( void )
{
   addi  r0,r1,0 // Get the stack pointer by returning r1 with an immediate addition
} 
  
//=============================================================================
// Set_Stack_Pointer
//
// @func Set the stack pointer to the given address.
//  WARNING - Since the stack will have been changed be careful about
//            calling this and then returning from a function.
//
// @parm <t void>* | New_Stack_Pointer | the address to point to for the stack.
//
//=============================================================================
asm void Set_Stack_Pointer( void * New_Stack_Pointer )
{
% reg New_Stack_Pointer
   addi  r1,r3,0 // Set the stack pointer by adding r1 with an immediate 0.
}



//=============================================================================
// Count_Leading_Zeros_For_UINT32
//
// @func Count Leading Zeros of incoming Word
//
// @parm <t uint32_t> | word | value to have the leading zeros counted.
//
// @rdesc <t uint32_t> | number of the most significant non-zero bit position.
//
//=============================================================================
asm uint32_t Count_Leading_Zeros_For_UINT32 ( uint32_t word )
{
% reg word
  cntlzw   r3,word  ; R3 will = most significant non-zero bit position #
}



//=============================================================================
// Set_SPR
//
// @func Set a Special_Purpose_Register with a 32-bit value.
//
// @parm <t uint32_t> | spr | special purpose register to be modified.
//
// @parm <t uint32_t> | value | value to write to the spr.
//
// @rdesc none
//
//=============================================================================
asm void Set_SPR( uint32_t spr, uint32_t value )
{
% con spr;reg value
   mtspr    spr,value   // write value contents to the SPR
}

//=============================================================================
// Get_SPR
//
// @func Get the contents of a Special_Purpose_Register.
//
// @parm <t uint32_t> | spr | special purpose register to be read.
//
// @rdesc <t uint32_t> | contents of the spr
//
//=============================================================================
asm uint32_t Get_SPR( uint32_t spr )
{
% con spr
   mfspr    r3, spr   // write R4 contents to the SPR
}



asm void Leave_Critical_Section_asm( interrupt_state_t in_interrupt_state )
{
% reg in_interrupt_state
!
    isync
    wrtee in_interrupt_state  ; restore EE bit
    isync
}


//=============================================================================
// Disable/Enable HWIO_MasterIRQ
//=============================================================================
 interrupt_state_t Enter_Critical_Section( void );

//=============================================================================
// Disable/Enable HWIO_MasterIRQ
//=============================================================================
 interrupt_state_t Enter_Critical_Enable_Section( void );

 void Leave_Critical_Section( interrupt_state_t in_interrupt_state );

#endif // POWERPC_DIABDATA_H

