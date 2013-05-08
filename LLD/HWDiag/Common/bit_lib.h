#ifndef BIT_LIB
#define BIT_LIB
/******************************************************************************
 *
 * Filename:          bit_lib.h
 *
 *  Description:           utility file for bit library
 *                         in both bit and byte form
 *                         1). DclrBIT_Arry will define a byte array
 *                              instead of bit packing
 *                         2). Bit mauplation is possible for byte storage
 *                              in assmbly
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 1997-2012, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:     tcb_pt1#5/incl/bit_lib.h/kok_pt2#1.1.3 %
 * %date_created:  Thu May 31 14:07:31 2012 %
 * %version:       kok_pt2#1.1.3 %
 * %derived_by:    pz87t9 %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_gentypes.h"

/*****************************************************************************
 *
 * Name:                DclrBIT_Arry
 * Description:         Create a one-dimensional byte array whose size is the
 *                      LwBIT_NumBits
 *
 * Parameters:     I    LaBIT_BitArray     The name of the byte array
 *                 I    LwBIT_NumBits      The number of bits to hold in the array.
 * Returns:  A one-dimensional byte arr
 *****************************************************************************/
#define DclrBIT_Arry(LwBIT_BitArray,LwBIT_NumBits) T_COUNT_BYTE \
         LwBIT_BitArray[LwBIT_NumBits]

/*****************************************************************************
 *
 * New Name:            SetBIT_InArry
 * Description:         Set a single bit within the input array.
 *
 * Parameters:     I/O  LaBIT_BitArray     The name of the byte array
 *                 I    LiBIT_Offset       The number of bits to be set to TRUE
 *
 *****************************************************************************/
#define SetBIT_InArry(LaBIT_BitArray,LiBIT_Offset) \
  (LaBIT_BitArray[LiBIT_Offset] = CbTRUE)

/*****************************************************************************
 *
 * Name:                ClrBIT_InArry
 * Description:         Clear a single bit within the input array.
 * Parameters:     I/O  LaBIT_BitArray     The name of the bit array
 *                 I    LiBIT_Offset       The number of bits to be set to FALSE
 *
 *****************************************************************************/
#define ClrBIT_InArry(LaBIT_BitArray,LiBIT_Offset) \
  (LaBIT_BitArray[LiBIT_Offset] = CbFALSE)

/*****************************************************************************
 * Name:                GetBIT_InArry
 * Description:         Get the value of a single bit within the input array.
 *                      The bit order is
 *                           [0,1,2,...,NumBits]
 * Parameters:     I/O  LaBIT_BitArray     The name of the bit array
 *                 I    LiBIT_Offset       The number of the bit to be tested
 *
 * Returns:  The value of the bit at the specified offset
 *****************************************************************************/
#define GetBIT_InArry(LaBIT_BitArray,LiBIT_Offset) LaBIT_BitArray[LiBIT_Offset]

/*****************************************************************************
 *
 * Name:                SetBIT_InByte
 * Description:         Set a single bit within the input byte;
 *
 * Parameters:     I/O  LaBIT_Byte         The name of the byte variable
 *                 I    LiBIT_Offset       The number of bits to be set to TRUE
 *                                         within the byte.
 *****************************************************************************/
#define SetBIT_Byte(a,b) SetBIT_InByte(a,b)

#define SetBIT_InByte(LaBIT_Byte,LiBIT_Offset) \
    (LaBIT_Byte | ( 1U << LiBIT_Offset ) )

/*****************************************************************************
 *
 * Name:                ClrBIT_InByte
 * Description:         Clear a single bit within the input byte;
 *
 * Parameters:     I/O  LaBIT_Byte         The name of the byte variable
 *                 I    LiBIT_Offset       The number of bits to be set to FALSE
 *                                         within the byte.
 *****************************************************************************/
#define ClearBIT_Byte(a,b) ClrBIT_InByte(a,b)

#define ClrBIT_InByte(LaBIT_Byte,LiBIT_Offset) \
    (LaBIT_Byte & ~( 1 << LiBIT_Offset ) )

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.3   970324 mye      Changed bit to byte, got rid of other stuff not uesd
*                       Created asm routines for real bit manuplation
* 1.6   970501 mye      Added "__" before asm for allowing "strict-ansi"
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   010827 kan 1444 Replaced all __asm code with C code, removed
*                        function TestBIT_ByteValue since it is never used.
* tci_pt3#1.1.1
*       040913  pd 4396 Making Code Cosmic Compatible - second phase.
* tci_pt3#1.1.2
*       091013 Sha 8428 QAC Fix Rule 12.7 : The macro 'SetBIT_InByte()'
*                       has been defined with integer constant '1' explicitly
*                       suffixed with 'U' used as left operand in the shift
*                       expression
* kok_pt2#1.1.3
*       120524 cjk 0081 Update includes.
*
******************************************************************************/
