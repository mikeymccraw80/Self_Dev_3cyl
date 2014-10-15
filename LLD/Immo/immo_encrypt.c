/**************************************************************************
 *
 *  Mini-Crypt Version 2 (for JAC)
 *
 *
 *  Copyright (c) 1996-2005
 *
 *  by               Delphi Automotive Systems Deutschland GmbH
 *                   Body & Security Electronics
 *                   Albert-Einstein-Strasse 5
 *                   51766 Engelskirchen
 *                   Germany
 *
 *  All rights reserved. Diese Software ist urheberrechtlich geschuetzt.
 *
 *  Classification:  D E L P H I   c o n f i d e n t i a l
 *
 *  ------------------------------------------------------------------------
 *
 *  Revision History:
 *
 *  Date    Revision I Name  Change Description
 *  -----------------I-----------------------------------------------------
 *  00-09-08   2.0   I Feeding of random number into algorithm changed
 *                   I
 *
 *  ------------------------------------------------------------------------
 *
 *  Important Information:
 *
 *    Check the Customer Key!
 *
 ********************************************************* end of comment */


//#include "immo_encrypt.h"

/*#define ROUNDS 200
const unsigned char
   f1a[32] = {1,0,0,1,0,0,1,1,0,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0};
const unsigned char
   f1b[32] = {0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,0,1,0,1,1,0,1,0,1};
const unsigned char
   f1c[32] = {1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,0,1,0,0,0,1,1,1,0,1};
const unsigned char
   f1d[32] = {0,1,0,1,1,0,1,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,1,1,0,1,0,1,1,0,1,0};
const unsigned char 
   f1e[16] = {1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1};
const unsigned char 
   f2[16] = {0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0};
const unsigned char 
   f3[16] = {0,3,1,3,2,1,2,0,0,2,1,2,1,3,3,0};*/
/*int round;
unsigned char x0,x1,x2,x3,x4,k0,k1,k2,k3,k4,
              d0,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,
              a0,a1,a2,a3,b,count,j,carry;
unsigned char kcarry; *//* can be 'bit' */


//////////////////////////////////////////////////////////////////////



/* two cryptographical tables for the feedback and filter functions */
/*
const U8 feedback_tab[32] = {
      0x66, 0x66,
      0x66, 0x66,
      0x99, 0x99,
      0x99, 0x99,
      0x66, 0x66,
      0x66, 0x66,
      0x99, 0x99,
      0x99, 0x99,
      0x99, 0x99,
      0x99, 0x99,
      0x66, 0x66,
      0x66, 0x66,
      0x99, 0x99,
      0x99, 0x99,
      0x66, 0x66,
      0x66, 0x66
      };
*/


/*const U8 output_tab[32] = {
      0xd7, 0x74,
      0x24, 0x91,
      0x83, 0x65,
      0xbc, 0x4d,
      0xe3, 0x55,
      0x38, 0xfb,
      0x76, 0x2c,
      0x8d, 0x70,
      0xf5, 0x23,
      0x85, 0xe5,
      0x8c, 0x1c,
      0xfc, 0x6e,
      0xa7, 0x22,
      0xb9, 0x33,
      0x39, 0x7c,
      0x48, 0x0a
      };
*/

/* a simple bitmasktable */

/*const U8 bitmask_tab[ 8] = {
      0x80,
      0x40,
      0x20,
      0x10,
      0x08,
      0x04,
      0x02,
      0x01
      };
*/

//U16 F_Result, G_Result;
//uint8_t ECMSeed[5];

/**********************************************************************\
*
* $RCSfile: digsig.c $
* $editor: CJAE-MichaelWang $
* $Date: 2006/01/10 13:29:19 $
* $Revision: V0.2 $ $Name: $
* $State: Exp $
*
* $Type: C Source File $
* $Function: digsig() $
* $Return: type description
* $ none
* $
* $Input: name type description
*
* x unsigned char * pointer to challenge (5 byte)
* k unsigned char * pointer to key (5 byte)
* $
* $Output: name type description
*
* y unsigned char * pointer to response (3 byte)
* $
*
\**********************************************************************/
/*
FAR_COS void digsig( unsigned char *x, unsigned char *k, unsigned char *y)
{
   x0 = x[ 0];
   x1 = x[ 1];
   x2 = x[ 2];
   x3 = x[ 3];
   x4 = x[ 4];
   k0 = k[ 0];
   k1 = k[ 1];
   k2 = k[ 2];
   k3 = k[ 3];
   k4 = k[ 4];
   count = 2;
 for ( round = 1; round <= ROUNDS; round++)
 {
   d0=d1=d2=d3=d4=d5=d6=d7=d8=d9=d10=d11=d12=d13=d14=d15=a0=a1=a2=a3=b=0;
   if ( x4 & 0x01) d15 |= 0x10;
   if ( k4 & 0x01) d15 |= 0x08;
   if ( x3 & 0x01) d15 |= 0x04;
   if ( k3 & 0x01) d15 |= 0x02;
   if ( x2 & 0x01) d15 |= 0x01;
   if ( k2 & 0x01) d14 |= 0x08;
   if ( x1 & 0x01) d14 |= 0x04;
   if ( k1 & 0x01) d14 |= 0x02;
   if ( k0 & 0x01) d14 |= 0x01;
   if ( x4 & 0x02) d13 |= 0x10;
   if ( k4 & 0x02) d13 |= 0x08;
   if ( x3 & 0x02) d13 |= 0x04;
   if ( k3 & 0x02) d13 |= 0x02;
   if ( x2 & 0x02) d13 |= 0x01;
   if ( k2 & 0x02) d12 |= 0x08;
   if ( x1 & 0x02) d12 |= 0x04;
   if ( k1 & 0x02) d12 |= 0x02;
   if ( k0 & 0x02) d12 |= 0x01;
   if ( x4 & 0x04) d11 |= 0x10;
   if ( k4 & 0x04) d11 |= 0x08;
   if ( x3 & 0x04) d11 |= 0x04;
   if ( k3 & 0x04) d11 |= 0x02;
   if ( x2 & 0x04) d11 |= 0x01;
   if ( k2 & 0x04) d10 |= 0x10;
   if ( x1 & 0x04) d10 |= 0x08;
   if ( k1 & 0x04) d10 |= 0x04;
   if ( x0 & 0x04) d10 |= 0x02;
   if ( k0 & 0x04) d10 |= 0x01;
   if ( x4 & 0x08) d9 |= 0x10;
   if ( k4 & 0x08) d9 |= 0x08;
   if ( x3 & 0x08) d9 |= 0x04;
   if ( k3 & 0x08) d9 |= 0x02;
   if ( x2 & 0x08) d9 |= 0x01;
   if ( k2 & 0x08) d8 |= 0x10;
   if ( x1 & 0x08) d8 |= 0x08;
   if ( k1 & 0x08) d8 |= 0x04;
   if ( x0 & 0x08) d8 |= 0x02;
   if ( k0 & 0x08) d8 |= 0x01;
   if ( x4 & 0x10) d7 |= 0x10;
   if ( k4 & 0x10) d7 |= 0x08;
   if ( x3 & 0x10) d7 |= 0x04;
   if ( k3 & 0x10) d7 |= 0x02;
   if ( x2 & 0x10) d7 |= 0x01;
   if ( k2 & 0x10) d6 |= 0x10;
   if ( x1 & 0x10) d6 |= 0x08;
   if ( k1 & 0x10) d6 |= 0x04;
   if ( x0 & 0x10) d6 |= 0x02;
   if ( k0 & 0x10) d6 |= 0x01;
   if ( x4 & 0x20) d5 |= 0x10;
   if ( k4 & 0x20) d5 |= 0x08;
   if ( x3 & 0x20) d5 |= 0x04;
   if ( k3 & 0x20) d5 |= 0x02;
   if ( x2 & 0x20) d5 |= 0x01;
   if ( k2 & 0x20) d4 |= 0x10;
   if ( x1 & 0x20) d4 |= 0x08;
   if ( k1 & 0x20) d4 |= 0x04;
   if ( x0 & 0x20) d4 |= 0x02;
   if ( k0 & 0x20) d4 |= 0x01;
   if ( x4 & 0x40) d3 |= 0x10;
   if ( k4 & 0x40) d3 |= 0x08;
   if ( x3 & 0x40) d3 |= 0x04;
   if ( k3 & 0x40) d3 |= 0x02;
   if ( x2 & 0x40) d3 |= 0x01;
   if ( k2 & 0x40) d2 |= 0x10;
   if ( x1 & 0x40) d2 |= 0x08;
   if ( k1 & 0x40) d2 |= 0x04;
   if ( x0 & 0x40) d2 |= 0x02;
   if ( k0 & 0x40) d2 |= 0x01;
   if ( x4 & 0x80) d1 |= 0x10;
   if ( k4 & 0x80) d1 |= 0x08;
   if ( x3 & 0x80) d1 |= 0x04;
   if ( k3 & 0x80) d1 |= 0x02;
   if ( x2 & 0x80) d1 |= 0x01;
   if ( k2 & 0x80) d0 |= 0x10;
   if ( x1 & 0x80) d0 |= 0x08;
   if ( k1 & 0x80) d0 |= 0x04;
   if ( x0 & 0x80) d0 |= 0x02;
   if ( k0 & 0x80) d0 |= 0x01;
   if ( f1a[ d0]) a0 |= 0x08;
   if ( f1b[ d1]) a0 |= 0x04;
   if ( f1c[ d2]) a0 |= 0x02;
   if ( f1d[ d3]) a0 |= 0x01;
   if ( f1a[ d4]) a1 |= 0x08;
   if ( f1b[ d5]) a1 |= 0x04;
   if ( f1c[ d6]) a1 |= 0x02;
   if ( f1d[ d7]) a1 |= 0x01;
   if ( f1a[ d8]) a2 |= 0x08;
   if ( f1b[ d9]) a2 |= 0x04;
   if ( f1c[ d10]) a2 |= 0x02;
   if ( f1d[ d11]) a2 |= 0x01;
   if ( f1e[ d12]) a3 |= 0x08;
   if ( f1b[ d13]) a3 |= 0x04;
   if ( f1e[ d14]) a3 |= 0x02;
   if ( f1d[ d15]) a3 |= 0x01;
   if ( f2[ a0]) b |= 0x01;
   if ( f2[ a1]) b |= 0x02;
   if ( f2[ a2]) b |= 0x04;
   if ( f2[ a3]) b |= 0x08;
   carry = f3[ b];
   carry ^= ( x0 & 3);
   for ( j = 0; j < 2; j++)
   {
      x0 >>= 1; if ( x1 & 0x1) x0 |= 0x80;
      x1 >>= 1; if ( x2 & 0x1) x1 |= 0x80;
      x2 >>= 1; if ( x3 & 0x1) x2 |= 0x80;
      x3 >>= 1; if ( x4 & 0x1) x3 |= 0x80;
      x4 >>= 1; if ( carry & 1) x4 |= 0x80;
      carry >>= 1;
   }
   count--;
   if ( !count)
   {
      kcarry = 0;
      kcarry ^= (( k0 & 0x01) != 0);
      kcarry ^= (( k0 & 0x04) != 0);
      kcarry ^= (( k2 & 0x08) != 0);
      kcarry ^= (( k2 & 0x20) != 0);
      k0 >>= 1; if ( k1 & 1) k0 |= 0x80;
      k1 >>= 1; if ( k2 & 1) k1 |= 0x80;
      k2 >>= 1; if ( k3 & 1) k2 |= 0x80;
      k3 >>= 1; if ( k4 & 1) k3 |= 0x80;
      k4 >>= 1; if ( kcarry) k4 |= 0x80;
      count = 3;
   }
 }
y[ 0] = x0;
y[ 1] = x1;
y[ 2] = x2;
y[ 3] = x3;
y[ 4] = x4;

}
*/
/**********************************************************************/
/* eof */
/**********************************************************************/

//////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------------
Function:  mini_crypt
Input :  U32 random         random number
      	 U16 secretkey_h    high part, only 14 bit used
      	 U32 secretkey_l    lo part, all 32 bits used
Output:  pointer to U16 f_result only the lower 12 bits are used
         pointer to U16 g_result only the lower 14 bits are used
Global  :
External:

This routine calculates 2 results - f and g - based on a cryptographical
algorithm.

Typical scenario: 2 ECUs are having the same secret key and want to
authorize each other. One is sending a (good) random number and the first
result f to the second one, which the also calculates. If its f and the
received one are identical, then it will be send to the first ECU. There
it will be also compared.
Only if both compares are good the authentification is ok.


Sample values for customer key 0000 00000000:

 No.  secret_h secret_l    random     f_result g_result
--------------------------------------------------------------------------------
  1.  K: 0000 00000000 R: 00000001   F= 0F12  G= 202F
  2.  K: 0000 00000000 R: 00000002   F= 03BD  G= 11A2
  3.  K: 0000 00000000 R: 11111111   F= 0A1F  G= 1EC1
  4.  K: 0000 00000000 R: 12345678   F= 0590  G= 366A
  5.  K: 0000 00000000 R: 98765432   F= 0E3B  G= 3D5D
  6.  K: 0123 456789AB R: 00000001   F= 0A89  G= 1E1F
  7.  K: 0123 456789AB R: 00000002   F= 0B19  G= 3189
  8.  K: 0123 456789AB R: 11111111   F= 0C77  G= 3464
  9.  K: 0123 456789AB R: 12345678   F= 09F6  G= 00F8
 10.  K: 0123 456789AB R: 98765432   F= 0FE4  G= 1D21

If the results always look like 0xD6B then the wrong big/little endian
type might be choosen.
------------------------------------------------------------------------*/
#if 0
FAR_COS void mini_crypt( U32 random, U16 secretkey_h, U32 secretkey_l,
                        U16 *f_result, U16 *g_result)
{
  myU32 shift_register; /* the shift register variable */

  U8 index;       /* the raw index variable */
  U8 tab_index;   /* the tableindex variable */
  U8 bitmask;     /* the bit position index variable */

  U8 counter;     /* the loop counter variable */
  U8 temp1, temp2;

  shift_register.lon = random
	+secretkey_l
	+CUSTOMER_KEY_L; /* Calculate the start value */

  secretkey_h += (CUSTOMER_KEY_H);
  secretkey_h <<=2;                   /* only 14 bits are used */

  /* initialize the loop counter */
  counter = START_DIVERGENCY+F_SIZE+GAP_DIVERGENCY+G_SIZE;

  do {
  index  = (shift_register.chh & ((U8)HH_MASKE)); /* extract the feedback bits */
  temp1=shift_register.chh;
  temp2=(temp1 & HH_MASKE);
  index |= (shift_register.chl & HL_MASKE); /* they are selected in a way */
  index |= (shift_register.clh & LH_MASKE); /* that there is no need for */
  index |= (shift_register.cll & LL_MASKE); /* bit shifting */

  tab_index = index >> 3; /* calculate the index for tables access */

  bitmask = bitmask_tab[index & 0x07]; /* create a mask to access a single bit */

  shift_register.lon <<= 1; /* shifting one position to the left gives us a 0 as lsb */

  if ((feedback_tab[tab_index] & bitmask) != 0) {
    /* if there is an 1 in the table */
    shift_register.cll |= 1; /* then copy it to lsb of shift_register */
  }

  if (counter <= G_SIZE) {
    /* *** we have to build g *** */
    *g_result <<= 1; /* shifting one position to the left gives us a 0 as lsb */
    if ((output_tab[tab_index] & bitmask) != 0)
    /* if there is an 1 in the table */
    *g_result |= 1; /* then copy it to lsb */
  } else if (counter <= GAP_DIVERGENCY + G_SIZE) {
       /* *** in the gap divergency ***  */
       if (secretkey_h & BIT15)  /* if set then exor the last feedback */
       shift_register.cll ^= 1;
       secretkey_h <<= 1;
       } else if (counter <= F_SIZE + GAP_DIVERGENCY + G_SIZE) {
            /* *** we have to build f *** */
            *f_result <<= 1; /* shifting one position to the left gives us a 0 as lsb */
            if ((output_tab[tab_index] & bitmask) != 0)
            /* if there is an 1 in the table */
            *f_result |= 1; /* then copy it to lsb */
           }

  } while(--counter != 0); /* until we are ready */

  *f_result &=F_MASK;         /* delete the unnecessary bits */
  *g_result &=G_MASK;

} /* end of mini_crypt() */
#endif



/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/* 
/* ==========================================================================*/
