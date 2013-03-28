#ifndef E200Z3_H
#define E200Z3_H

#include "powerpc_diabdata_types.h"



void Enable_SPE_APU(void);
void STORE_SPR_VALUE(const uint32_t spr_register, const uint32_t spr_value);
void STORE_SPR_VALUE_VAR(const uint32_t spr_register, uint32_t spr_value);
uint32_t READ_SPR_VALUE(const uint32_t spr_regaddr);
void Set_Sync_And_Link_Register( void );
void Save_Machine_Status( void );
void Restore_Machine_Status( void );
void Enable_MachineCheck(void);
void TLBWE(void);
void TLBRE(void);
void MSYNC(void);
void ISYNC(void);
void EIEIO(void);
 void NOP(void);



/*============================================================================*\
 * MACRO: STORE_SPR_VALUE
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void STORE_SPR_VALUE(const uint32_t spr_register, const uint32_t spr_value)
{
% con spr_register; con spr_value
! "r3"
   isync
   addis   r3,r0,spr_value@h
   addi    r3,r3,spr_value@l
   mtspr   spr_register,r3
   isync
}

/*============================================================================*\
 * MACRO: STORE_SPR_VALUE_VAR
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void STORE_SPR_VALUE_VAR(const uint32_t spr_register, uint32_t spr_value)
{
% con spr_register; reg spr_value
! "r3"
   isync
   mtspr   spr_register, spr_value
   isync
}

/*============================================================================*\
 * MACRO: READ_SPR_VALUE
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *   Function to read SPR register content.
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm uint32_t READ_SPR_VALUE(const uint32_t spr_regaddr)
{
% con spr_regaddr
! "r3"
   mfspr   r3,spr_regaddr
}


/*****************************************************/
/* Define instances of modules                       */
/*  with special register numbers                    */
/*****************************************************/

// The CR register does not have an SPR#
// The GPR registers do not have an SPR#
// The MSR register does not have an SPR#

#define SPR_LR          8
#define SPR_CTR         9
#define SPR_XER         1

#define SPR_PIR       286
#define SPR_PVR       287
#define SPR_SVR      1023
#define SPR_HID0     1008
#define SPR_HID1     1009

#define SPR_TBL       (284)
#define SPR_TBU       (285)
#define SPR_TCR       340
#define SPR_TSR       336
#define SPR_DEC        22
#define SPR_DECAR      54

#define SPR_PID0       48
#define SPR_MMUCSR0  1012
#define SPR_MMUCFG   1015
#define SPR_TLB0CFG   688
#define SPR_TLB1CFG   689
#define SPR_MAS0      624
#define SPR_MAS1      625
#define SPR_MAS2      626
#define SPR_MAS3      627
#define SPR_MAS4      628
#define SPR_MAS6      630

#define SPR_L1CFG0    515
#define SPR_L1CFG1    516
#define SPR_L1CSR0   1010
#define SPR_L1CSR1   1011
#define SPR_L1FINV0  1016
#define SPR_L1FINV1   959

#define SPR_SPEFSCR   512

#define SPR_SPRG0     272
#define SPR_SPRG1     273
#define SPR_SPRG2     274
#define SPR_SPRG3     275
#define SPR_SPRG4     276
#define SPR_SPRG5     277
#define SPR_SPRG6     278
#define SPR_SPRG7     279
#define SPR_USPRG0    256
#define SPR_SRR0       26
#define SPR_SRR1       27
#define SPR_CSRR0      58
#define SPR_CSRR1      59
#define SPR_DSRR0     574
#define SPR_DSRR1     575
#define SPR_ESR        62
#define SPR_MCSR      572
#define SPR_DEAR       61
#define SPR_IVPR       63
#define SPR_IVOR0     400
#define SPR_IVOR1     401
#define SPR_IVOR2     402
#define SPR_IVOR3     403
#define SPR_IVOR4     404
#define SPR_IVOR5     405
#define SPR_IVOR6     406
#define SPR_IVOR7     407
#define SPR_IVOR8     408
#define SPR_IVOR9     409
#define SPR_IVOR10    410
#define SPR_IVOR11    411
#define SPR_IVOR12    412
#define SPR_IVOR13    413
#define SPR_IVOR14    414
#define SPR_IVOR15    415
#define SPR_IVOR32    528
#define SPR_IVOR33    529
#define SPR_IVOR34    530

#define SPR_DBCR0     308
#define SPR_DBCR1     309
#define SPR_DBCR2     310
#define SPR_DBCR3     561
#define SPR_DBSR      304
#define SPR_DBCNT     562
#define SPR_IAC1      312
#define SPR_IAC2      313
#define SPR_IAC3      314
#define SPR_IAC4      315
#define SPR_DAC1      316
#define SPR_DAC2      317


//=============================================================================
// Enable_SPE_APU
//
// @func  Set the SPE bit in the MSR register to enble the SPE APU.
//
// @rdesc none
//
//=============================================================================
asm void Enable_SPE_APU(void)
{
! "r3"
   mfmsr   r3            ; Read MSR value
   e_oris    r3,r3,0x200 ; Set SPE bit
   isync
   mtmsr   r3            ; Write MSR value
   isync
}


//=============================================================================
// Set_Sync_And_Link_Register
//
// @func  Load the following physical address into the Link
// Register. Jump to that address so that Link Register
// equals Program Counter.
//
// @rdesc none
//
//=============================================================================
asm void Set_Sync_And_Link_Register( void )
{
% lab sync_jump
! "r3"
   lis      r0,0               ; load r0 with 0
   e_oris     r3,r0,sync_jump@h  ; load the address
   ori      r3,r3,sync_jump@l
   mtlr     r3
                         ; CTR needs to be cleared here?
                         ; to make sure it is not zero during bclr jump
   blr                   ; unconditionally to address in Link Register (LR)

sync_jump:
   isync    ; This ensures that no other instruction is fetched until the
            ; previous instruction is completely finished
}


//=============================================================================
// Save_Machine_Status
//
// @func
//
// @rdesc none
//
//=============================================================================
asm void Save_Machine_Status( void )
{
!
  stwu     r1,-20(r1)      ; create stack frame and save SP
  stw      r31,08(r1)      ; save temporary register
  mfspr    r31,srr0        ; save SRR0...
  stw      r31,12(r1)      ; ...on stack
  mfspr    r31,srr1        ; save SRR1...
  stw      r31,16(r1)      ; ...on stack
  lwz      r31,08(r1)      ; restore temporary register
}


//=============================================================================
// Restore_Machine_Status
//
// @func
//
// @rdesc none
//
//=============================================================================
asm void Restore_Machine_Status( void )
{
!
  stw      r31,08(r1)      ; save temporary register
  lwz      r31,12(r1)      ; restore SSR0...
  mtspr    srr0,r31        ; ...from stack
  lwz      r31,16(r1)      ; restore SSR1...
  mtspr    srr1,r31        ; ...from stack
  lwz      r31,08(r1)      ; restore temporary register
  addi     r1,r1,20        ; recover stack frame
}

asm void Enable_MachineCheck(void)
{
! "r3"
   mfmsr   r3            ; Read MSR value
   ori     r3,r3,0x1000  ; Set  ME bit
   isync
   mtmsr   r3            ; Write MSR value
   isync
}


/*============================================================================*\
 * MACRO: TLBWE
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *   Reference Book E, chapter 11.
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *   Function to write MMU table entry. Use this call to get syncronization.
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void TLBWE(void)
{
!
   msync
   tlbwe
   msync
}

/*============================================================================*\
 * MACRO: TLBWE
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *   Reference Book E, chapter 11.
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *   Function to write MMU table entry. Use this call to get syncronization.
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void TLBRE(void)
{
!
   msync
   tlbre
   msync
}


/*============================================================================*\
 * MACRO: MSYNC
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *   Function to issue msync instruction.
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void MSYNC(void)
{
!
   msync
}

/*============================================================================*\
 * MACRO: ISYNC
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *   Function to issue isync instruction.
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void ISYNC(void)
{
!
   isync
}

/*============================================================================*\
 * MACRO: EIEIO
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *   Reference Book E, chapter 11.
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *   Function to ensure instructions are executed in order.
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void EIEIO(void)
{
!
   eieio
}


/*============================================================================*\
 * MACRO: NOP
 *============================================================================
 * RETURN VALUE:
 *   None
 *
 * PARAMETERS:
 *   None
 *
 * EXTERNAL REFERENCES:
 *   Reference Book E, chapter 11.
 *
 * DEVIATIONS FROM STANDARDS:
 *   None
 *
 *---------------------------------------------------------------------------
 * ABSTRACT:
 *---------------------------------------------------------------------------
 *   Function to ensure a NOP is inserted.
 *
 * PRECONDITIONS:
 *   None
 *
 * POSTCONDITIONS:
 *   None
 *
\*============================================================================*/
asm void NOP(void)
{
!
   .set noreorder
   e_ori 0,0,0
   .set reorder
}


#endif // E200Z6_H

