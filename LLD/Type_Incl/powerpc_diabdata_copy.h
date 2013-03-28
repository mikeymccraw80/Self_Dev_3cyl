#ifndef POWERPC_DIABDATA_COPY_H
#define POWERPC_DIABDATA_COPY_H

#include "reuse.h"


void Copy_Bytes( uint8_t *Source, uint8_t *Destination, uint32_t Num_Bytes );
void Copy_Words( uint16_t *Source, uint16_t *Destination, uint32_t Num_Words );
void Copy_Bytes_To_Words( uint8_t *Source, uint16_t *Destination, unsigned int Num_Bytes );
void Copy_Words_To_Bytes( uint16_t *Source, uint8_t *Destination, unsigned int Num_Words );
void Clear_Words( uint16_t *Source, unsigned int Num_Words );

void Copy_Longs ( void    * Source,
                        void    * Destination,
                        uint16_t  Num_Longs
                      );
void Fill_Longs ( void  * Source, uint16_t  Num_Longs, uint32_t  Value );
void Clear_Longs ( void  * Source, uint16_t  Num_Longs );

//=============================================================================
// Copy Memory
//
// @func  W A R N I N G
// <nl> The Diab Data compiler won't always reserve registers below r14
//  properly for function usage so these routines that are using r3
//  and r4 may not work properly. Be sure to check the compiler
//  output whenever you use any of these routines.
//
// @parm uint8_t * | Source | address of the source to copy from
//
// @parm uint8_t * | Destination | address of the destination to copy to
//
// @parm uint32_t | Num_Bytes | number of the bytes to be copied
//
// @rdesc none
//
//=============================================================================

asm void Copy_Bytes( uint8_t *Source, uint8_t *Destination, uint32_t Num_Bytes )
{
%      reg Source, Destination, Num_Bytes; lab LoopB
!      "r3", "r4"
                                    ; r3 and r4 are scratch registers
                                    ; parameters passed in via registers
       addi  r4,0,0                 # clear r4
LoopB: lbz   r3,0( Source )         # load byte into r6
       stb   r3,0( Destination )    # store byte to addr. in r7
       addi  Source,Source,1             # increment Source
       addi  Destination,Destination,1      # increment Destination
       addi  r4,r4,1                 # increment r4
       cmp   0,0,r4,Num_Bytes       # count == Num_bytes?
       bne   LoopB                  # if count != Num_Bytes goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}


//=============================================================================
// Copy Memory
//
// @func  W A R N I N G
// <nl> The Diab Data compiler won't always reserve registers below r14
//  properly for function usage so these routines that are using r3
//  and r4 may not work properly. Be sure to check the compiler
//  output whenever you use any of these routines.
//
// @parm uint16_t * | Source | address of the source to copy from
//
// @parm uint16_t * | Destination | address of the destination to copy to
//
// @parm uint32_t | Num_Bytes | number of the bytes to be copied
//
// @rdesc none
//
//=============================================================================

asm void Copy_Words( uint16_t *Source, uint16_t *Destination, uint32_t Num_Words )
{
%      reg Source, Destination, Num_Words; lab LoopW
!      "r3", "r4"
                                    ; r3 and r4 are scratch registers
                                    ; parameters passed in via registers
       addi  r4,0,0                 # clear r4
LoopW: lhz   r3,0( Source )         # load byte into r6
       sth   r3,0( Destination )    # store byte to addr. in r7
       addi  Source,Source,2             # increment Source
       addi  Destination,Destination,2   # increment Destination
       addi  r4,r4,1                 # increment r4
       cmp   0,0,r4,Num_Words       # count == Num_Words?
       bne   LoopW                  # if count != Num_Bytes goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}


/*===========================================================================*\
 * Copy_Longs
 *
 *
 * Syntax
 *    Copy_Longs ( void    * Source,
 *                 void    * Destination,
 *                 UINT16  Num_Longs
 *               )
 *
 * Remarks
 *    Copies a block of Num_Bytes UINT32's from Source to Destination.
 *    No check is made for overlapping areas.
 *
 * Calling Parameters
 *         Source = pointer to data to be copied
 *    Destination = pointer to where the data is to be copied
 *      Num_Longs = number of longs to copy
 *
 * Return Value
 *
\*===========================================================================*/

asm void Copy_Longs ( void    * Source,
                        void    * Destination,
                        uint16_t  Num_Longs
                      )
{
%      reg Source, Destination, Num_Longs; lab LoopL
!      "r3", "r4"
                                    ; r3 and r4 are scratch registers
                                    ; parameters passed in via registers
       addi  r4,0,0                 # clear r4
LoopL: lwz   r3,0( Source )         # load longword into r6
       stw   r3,0( Destination )    # store longword to addr. in r7
       addi  Source,Source,4             # increment Source
       addi  Destination,Destination,4   # increment Destination
       addi  r4,r4,1                 # increment r4
       cmp   0,0,r4,Num_Longs       # count == Num_Longs?
       bne   LoopL                  # if count != Num_Longs goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}


//=============================================================================
// Copy Memory
//
// @func  W A R N I N G
// <nl> The Diab Data compiler won't always reserve registers below r14
//  properly for function usage so these routines that are using r3
//  and r4 may not work properly. Be sure to check the compiler
//  output whenever you use any of these routines.
//
// @parm uint16_t * | Source | address of the source to copy from
//
// @parm uint16_t * | Destination | address of the destination to copy to
//
// @parm uint32_t | Num_Bytes | number of the bytes to be copied
//
// @rdesc none
//
//=============================================================================

asm void Copy_Bytes_To_Words( uint8_t *Source, uint16_t *Destination, unsigned int Num_Bytes )
{
%       reg Source, Destination, Num_Bytes; lab LoopBW
!       "r3", "r4"
                                    ; r3 and r4 are scratch registers
                                    ; parameters passed in via registers
        addi  r4,0,0                # clear r4
LoopBW: lbz   r3,0( Source )        # load byte into r6
        sth   r3,0( Destination )   # store byte to addr. in r7
        addi  Source,Source,1       # increment Source
        addi  Destination,Destination,2    # increment Destination
        addi  r4,r4,1                # increment r4
        cmp   0,0,r4,Num_Bytes      # count == Num_Words?
        bne   LoopBW                # if count != Num_Bytes goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}

//=============================================================================
// Copy Memory
//
// @func  W A R N I N G
// <nl> The Diab Data compiler won't always reserve registers below r14
//  properly for function usage so these routines that are using r3
//  and r4 may not work properly. Be sure to check the compiler
//  output whenever you use any of these routines.
//
// @parm uint16_t * | Source | address of the source to copy from
//
// @parm uint16_t * | Destination | address of the destination to copy to
//
// @parm uint32_t | Num_Bytes | number of the bytes to be copied
//
// @rdesc none
//
//=============================================================================

asm void Copy_Words_To_Bytes( uint16_t *Source, uint8_t *Destination, unsigned int Num_Words )
{
%       reg Source, Destination, Num_Words; lab LoopWB
!       "r3", "r4"
                                    ; r3 and r4 are scratch registers
                                    ; parameters passed in via registers
        addi  r4,0,0                # clear r4
LoopWB: lhz   r3,0( Source )        # load byte into r6
        stb   r3,0( Destination )   # store byte to addr. in r7
        addi  Source,Source,2            # increment Source
        addi  Destination,Destination,1  # increment Destination
        addi  r4,r4,1                # increment r4
        cmp   0,0,r4,Num_Words      # count == Num_Words?
        bne   LoopWB                # if count != Num_Bytes goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}



asm void Fill_Longs ( void  * Source, uint16_t  Num_Longs, uint32_t  Value )
{
%      reg Source, Num_Longs, Value; lab LoopL

       addi  r0,0,0                 # clear r0
LoopL: stw   Value,0( Source )      # store Value into Source
       addi  Source,Source,4        # increment Source
       subi  Num_Longs,Num_Longs,1  # decrement count
       cmp   0,0,r0,Num_Longs       # count == 0?
       bne   LoopL                  # if count != 0 goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}


//=============================================================================
//
//                            Clear Memory
//
//=============================================================================


asm void Clear_Words( uint16_t *Source, unsigned int Num_Words )
{
%      reg Source, Num_Words; lab LoopW

       addi  r0,0,0                 # clear r0
LoopW: sth   r0,0( Source )         # store word 0 into Source
       addi  Source,Source,2        # increment Source
       subi  Num_Words,Num_Words,1  # decrement count
       cmp   0,0,r0,Num_Words       # count == 0?
       bne   LoopW                  # if count != 0 goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}



asm void Clear_Longs ( void  * Source, uint16_t  Num_Longs )
{
%      reg Source, Num_Longs; lab LoopL

       addi  r0,0,0                 # clear r0
LoopL: stw   r0,0( Source )         # store word 0 into Source
       addi  Source,Source,4        # increment Source
       subi  Num_Longs,Num_Longs,1  # decrement count
       cmp   0,0,r0,Num_Longs       # count == 0?
       bne   LoopL                  # if count != 0 goto Loop
                                    ; assumes cmpi instr. updates
                                    ; cond. codes in CR0
}


#endif //

