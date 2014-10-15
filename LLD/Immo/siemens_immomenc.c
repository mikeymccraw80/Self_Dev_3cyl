/******************************************************************************
 *
 * Filename:          Siemens_immomenc.c
 *
 * Description:       This module contains the encrypt arithmetic of 
 *                    Siemens Immobilizer 
 *
 * Global Functions Defined:
 *                    void CalcSiemens_Encrypt()
 * Static Functions Defined:
 *                 
 *                    
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/******************************************************************************
 *  Include Files
 *****************************************************************************/


#include "siemens_immosenc.h"



BYTE VaSiemens_RandomNum[6] = {8, 1, 0, 2, 2, 3};  /* Challenge vector */
BYTE VaSiemens_RefResponse[6]; /* Response vector */

//prepare for the function CalcSiem_Encrypt
#define NORMED_CARRY_IN		7
#define NORMED_EXOR_OUT		6

/* The following EXOR'ed ZC to function after output matches directly */
#define MATCH_EXOUT_F1

/* Masks for U Bytes to get the index in lookup table for function block */
#define U0_MASK_F0			68
#define U1_MASK_F0			2
#define U2_MASK_F0			25
#define U3_MASK_F0			0

#define U0_MASK_F1			144
#define U1_MASK_F1			12
#define U2_MASK_F1			98
#define U3_MASK_F1			0

#define U0_MASK_F2			34
#define U1_MASK_F2			129
#define U2_MASK_F2			0
#define U3_MASK_F2			80

#define U0_MASK_F3			9
#define U1_MASK_F3			48
#define U2_MASK_F3			0
#define U3_MASK_F3			6


/* Permutation B Get number of R for RB */
#define R0_MASK			0x20
#define R1_MASK			0x80
#define R2_MASK			0x08
#define R3_MASK			0x01
#define R4_MASK			0x10
#define R5_MASK			0x02
#define R6_MASK			0x04
#define R7_MASK			0x40

/* Masks to read the permuted output of a functional block in RB */
#define F0_RB_MASK			0xA0
#define F1_RB_MASK			0x09
#define F2_RB_MASK			0x12
#define F3_RB_MASK			0x44

/* Masks for setting the EXORed input and output bis in index of */
/* the lookup table */
#define F0_CARRY_IN_MASK	0x20
#define F0_ZC6_MASK		0x80

#define F1_CARRY_IN_MASK	0x01
#define F1_ZC13_MASK		0x20

#define F2_CARRY_IN_MASK	0x04
#define F2_ZC20_MASK		0x08

#define F3_CARRY_IN_MASK	0x40
#define F3_ZC27_MASK		0x80


/* Conversion from UByte to ZC for debugging */
#define ZC0_U_BYTE			U0
#define ZC0_U_BIT_MASK		0x4
#define ZC1_U_BYTE			U2
#define ZC1_U_BIT_MASK		0x8
#define ZC2_U_BYTE			U1
#define ZC2_U_BIT_MASK		0x2
#define ZC3_U_BYTE			U2
#define ZC3_U_BIT_MASK		0x1
#define ZC4_U_BYTE			U2
#define ZC4_U_BIT_MASK		0x10
#define ZC5_U_BYTE			U0
#define ZC5_U_BIT_MASK		0x40
#define ZC6_U_BYTE			U1
#define ZC6_U_BIT_MASK		0x40
#define ZC7_U_BYTE			U0
#define ZC7_U_BIT_MASK		0x10
#define ZC8_U_BYTE			U1
#define ZC8_U_BIT_MASK		0x4
#define ZC9_U_BYTE			U2
#define ZC9_U_BIT_MASK		0x2
#define ZC10_U_BYTE			U1
#define ZC10_U_BIT_MASK		0x8
#define ZC11_U_BYTE			U2
#define ZC11_U_BIT_MASK		0x40
#define ZC12_U_BYTE			U0
#define ZC12_U_BIT_MASK		0x80
#define ZC13_U_BYTE			U2
#define ZC13_U_BIT_MASK		0x20
#define ZC14_U_BYTE			U1
#define ZC14_U_BIT_MASK		0x1
#define ZC15_U_BYTE			U1
#define ZC15_U_BIT_MASK		0x80
#define ZC16_U_BYTE			U3
#define ZC16_U_BIT_MASK		0x10
#define ZC17_U_BYTE			U0
#define ZC17_U_BIT_MASK		0x2
#define ZC18_U_BYTE			U3
#define ZC18_U_BIT_MASK		0x40
#define ZC19_U_BYTE			U0
#define ZC19_U_BIT_MASK		0x20
#define ZC20_U_BYTE			U2
#define ZC20_U_BIT_MASK		0x80
#define ZC21_U_BYTE			U0
#define ZC21_U_BIT_MASK		0x8
#define ZC22_U_BYTE			U0
#define ZC22_U_BIT_MASK		0x1
#define ZC23_U_BYTE			U1
#define ZC23_U_BIT_MASK		0x10
#define ZC24_U_BYTE			U3
#define ZC24_U_BIT_MASK		0x4
#define ZC25_U_BYTE			U3
#define ZC25_U_BIT_MASK		0x2
#define ZC26_U_BYTE			U1
#define ZC26_U_BIT_MASK		0x20
#define ZC27_U_BYTE			U2
#define ZC27_U_BIT_MASK		0x4

unsigned char U0; /* U byte 0 */
unsigned char U1; /* U byte 1 */
unsigned char U2; /* U byte 2 */
unsigned char U3; /* U byte 3 */

unsigned char RB; /* 8 bit feedback value */
unsigned char PIndex; /* Current P index */
bool HBit;

unsigned char P[29]; /* P sequence */

typedef unsigned char *TPointerToResponseByte;
typedef unsigned char *TPointerToChallengeByte;

static const unsigned char tabBitMask_1to8[9] = { 0x00, 0x01, 0x02, 0x04, 0x08,
		0x10, 0x20, 0x40, 0x80 };

/* The lookup table for all function blocks with permutation B */
const unsigned char LookupTable[256] =
{
0xA8,0xA1,0x45,0xBA,0x5E,0xF7,0xBA,0x01,0x4E,0x47,0x03,0x18,0xF5,
0xB8,0x11,0x4E,0x13,0x5E,0xBA,0xE5,0x45,0xA8,0x4C,0xF7,0xF5,0xB8,
0xFC,0x03,0xAA,0x47,0xE7,0x18,0x5F,0x00,0xF6,0x1B,0xED,0x12,0x09,
0xE4,0xB9,0xE6,0xF4,0xB9,0x02,0x19,0xA2,0xEF,0xA0,0xBB,0x4D,0x44,
0xB2,0x4D,0xBB,0x56,0x46,0x5D,0x0B,0xA2,0x5D,0xA2,0x54,0xFD,0x45,
0x4C,0xBA,0xE5,0xB3,0xBA,0x45,0x5E,0xAA,0xA3,0xF5,0x4E,0x18,0x55,
0xEE,0x11,0xEC,0x13,0x57,0x08,0xBA,0x45,0xA1,0x1A,0x0A,0xF5,0x11,
0xEE,0xF5,0xAA,0x0A,0xF5,0xA0,0xFF,0x09,0x56,0x12,0x4D,0xF6,0xA9,
0x4F,0x10,0x02,0xFD,0xFD,0xE6,0x5D,0xA2,0x5F,0xE4,0xB2,0xBB,0x4D,
0xB2,0x44,0xA9,0xB9,0x02,0xF4,0x5D,0x02,0x5D,0xAB,0x02,0x73,0x7A,
0x8C,0x61,0x8C,0x25,0x73,0xDA,0x95,0x9C,0xCA,0xC3,0x27,0x6A,0xD8,
0x95,0xC8,0x85,0x61,0x3E,0x9E,0x73,0x97,0x2C,0x2E,0x63,0x27,0xD8,
0x71,0x9C,0x3C,0xC3,0x96,0xDB,0x2D,0xD2,0x2D,0xC0,0xD2,0x2D,0x70,
0x3D,0x2F,0x70,0xC2,0xCB,0x79,0x26,0x69,0x72,0x96,0x8D,0x7B,0x84,
0x60,0x9F,0x8F,0x94,0xD0,0x6B,0x94,0x6B,0x8F,0x34,0x8C,0x97,0x73,
0x2C,0x73,0x68,0x8C,0x97,0x63,0x78,0x3C,0x87,0xD8,0x87,0x27,0xD8,
0x3E,0xC1,0x9E,0xC1,0x61,0x9E,0x61,0xDA,0xD1,0x2E,0xD1,0x2E,0x2E,
0x71,0xCA,0x35,0x7B,0x24,0xC0,0x9F,0xC0,0x9F,0x3F,0x60,0x94,0xCB,
0xCB,0x34,0x2F,0x34,0x94,0x6B,0x9F,0x36,0x69,0x60,0x84,0x69,0x96,
0x7B,0x70,0xD9,0x26,0x8F,0xCB,0x86,0x79,0xD0
};

#define GetBitMask_1to8(bit) (tabBitMask_1to8[(bit)])

#define E0_MASK 128 /* Mask for Resonse Bit E0 in U0 => Z0 */
#define E1_MASK 64 /* Mask for Resonse Bit E1 in U0 => Z4 */

#define cror1(var) {if(var & 1) var = 0x80 + (var >> 1); else var = var >> 1;}
// end prepare for the function CalcSiem_Encrypt
static void Phi1(void);
static void Phi2(void );

static void Phi1() 
{
   unsigned char LeftRounds, temp;
   unsigned char FIndex; /* Index in lookup table */

   LeftRounds = 17;
   do 
   {
      FIndex = (U0 & U0_MASK_F0);
      FIndex |= (U1 & U1_MASK_F0);
      FIndex |= (U2 & U2_MASK_F0);
      FIndex |= (U3 & U3_MASK_F0);

      if (HBit)
      {
	   FIndex |= ZC2_U_BIT_MASK;
	}
	else 
	{
	   FIndex &= ~ZC2_U_BIT_MASK;
	}
	if ((ZC6_U_BYTE & ZC6_U_BIT_MASK) != 0) 
	{
	   FIndex |= F0_ZC6_MASK;
	}
	RB = (LookupTable[FIndex] & F0_RB_MASK);

	FIndex = (U0 & U0_MASK_F1);
	FIndex |= (U1 & U1_MASK_F1);
	FIndex |= (U2 & U2_MASK_F1);
	FIndex |= (U3 & U3_MASK_F1);

	if (!HBit)
	{
	   FIndex ^= F1_ZC13_MASK;
	}

	if (RB & R1_MASK) 
	{
	   FIndex |= F1_CARRY_IN_MASK;
	}
	RB |= LookupTable[FIndex] & F1_RB_MASK;

	FIndex = (U0 & U0_MASK_F2);
	FIndex |= (U1 & U1_MASK_F2);
	FIndex |= (U2 & U2_MASK_F2);
	FIndex |= (U3 & U3_MASK_F2);

	if (RB & R3_MASK) 
	{
	   FIndex |= F2_CARRY_IN_MASK;
	}

	if (ZC20_U_BYTE & ZC20_U_BIT_MASK) 
	{
	   FIndex |= F2_ZC20_MASK;
	}
	RB |= (LookupTable[FIndex] & F2_RB_MASK);

	FIndex = (U0 & U0_MASK_F3);
	FIndex |= (U1 & U1_MASK_F3);
	FIndex |= (U2 & U2_MASK_F3);
	FIndex |= (U3 & U3_MASK_F3);

	if (ZC27_U_BYTE & ZC27_U_BIT_MASK) 
	{
	   FIndex |= F3_ZC27_MASK;
	}

	if (RB & R5_MASK) 
	{
	   FIndex |= F3_CARRY_IN_MASK;
	}
	RB |= (LookupTable[FIndex] & F3_RB_MASK);

	cror1(U3);

	temp = U3 ^ RB ^ P[PIndex];

	U3 = U2;
	U2 = U1;
	U1 = U0;
	U0 = temp;

	if (PIndex == 28)
	{
	   PIndex = 0;
	}
	else
	{
	   PIndex++;
	}
   }
   while (--LeftRounds);
}

static void Phi2() 
{
   unsigned char LeftRounds, temp;
   bool DoubleRound;
   unsigned char FIndex; /* Index in lookup table */

   LeftRounds = 17;
   do 
   {
      DoubleRound = 1;
      do 
      {
         FIndex = (U0 & U0_MASK_F0) | (U1 & U1_MASK_F0) | (U2 & U2_MASK_F0) | (U3 & U3_MASK_F0);
         if ((ZC6_U_BYTE & ZC6_U_BIT_MASK) != 0) 
	  {
            FIndex |= F0_ZC6_MASK;
         }
         RB = (LookupTable[FIndex] & F0_RB_MASK);
         FIndex = (U0 & U0_MASK_F1) | (U1 & U1_MASK_F1) | (U2 & U2_MASK_F1) | (U3 & U3_MASK_F1);

         if (RB & R1_MASK) 
         {
            FIndex |= F1_CARRY_IN_MASK;
         }
         RB |= LookupTable[FIndex] & F1_RB_MASK;

         FIndex = (U0 & U0_MASK_F2) | (U1 & U1_MASK_F2) | (U2 & U2_MASK_F2) |(U3 & U3_MASK_F2);

         if (RB & R3_MASK) 
         {
            FIndex |= F2_CARRY_IN_MASK;
         }

         if ( (ZC20_U_BYTE & ZC20_U_BIT_MASK) != 0) 
         {
            FIndex |= F2_ZC20_MASK;
         }
         RB |= (LookupTable[FIndex] & F2_RB_MASK);

         FIndex = (U0 & U0_MASK_F3) | (U1 & U1_MASK_F3) | (U2 & U2_MASK_F3) |(U3 & U3_MASK_F3);

         if (ZC27_U_BYTE & ZC27_U_BIT_MASK) 
         {
            FIndex |= F3_ZC27_MASK;
         }

	if (RB & R5_MASK) 
      {
         FIndex |= F3_CARRY_IN_MASK;
      }
	RB |= (LookupTable[FIndex] & F3_RB_MASK);

	cror1(U3);

	temp = U3 ^ RB ^ P[PIndex];

	U3 = U2;
	U2 = U1;
	U1 = U0;
	U0 = temp;

	DoubleRound=!DoubleRound;
      }
      while (!DoubleRound);

      if (PIndex == 28) 
      {
         PIndex = 0;
      }
      else 
      {
	   PIndex++;
      }
   } 
   while (--LeftRounds);
}

FAR_COS void CalcSiem_Encrypt(BYTE *Challenge, BYTE *CustomerID, BYTE *SecretKey,BYTE *Response)
{
   unsigned char ByteNo; /* loop variable */
   unsigned char i;
   PIndex = 0; /* Initialize PIndex with 0 */
   RB = 0; /* Initialize feedback value RB with 0 */
   
   /* Calculation of the sequence P which defines the order of 
     * the identifier Iden[] and authenticatior Auth[] */
   for (i = 4; i <= 15; i++) 
   {
      P[i-4] = SecretKey[i];
      P[i+12] = SecretKey[i];
   }
   for (i = 0; i <= 3; i++) 
   {
      P[i+12] = CustomerID[i];
   }
   P[28] = CustomerID[0];

   /* Clear Response Vector */
   Response[0] = 0;
   Response[1] = 0;
   Response[2] = 0;
   Response[3] = 0;
   Response[4] = 0;
   Response[5] = 0;

    /* first 4 bytes authenticator */
   U0 = SecretKey[3]; /* Initialize U vector with the Authenticator*/
   U1 = SecretKey[2];
   U2 = SecretKey[1];
   U3 = SecretKey[0];

   /* First call of first rounds after input of the challenge for bit0-31*/
   for (ByteNo = 0; ByteNo != 4; ByteNo++) 
   {
      unsigned char ByteOfChallenge = Challenge[ByteNo]; /* the challenge's byte */
      unsigned char BitNo; /* loop variable */

      BitNo = 8;
      do
      {
         /* Calculate H Bit */
         HBit = ByteOfChallenge & GetBitMask_1to8(BitNo);
         Phi1();
      } 
      while (--BitNo);
   }

   /* Calculate first response with double call to Phi2 */
   for (ByteNo = 0; ByteNo != 4; ByteNo++) 
   {
      /* build pointer to the resonse byte changed in the following loop; */
      TPointerToResponseByte pResponse = &Response[ByteNo];
      unsigned char BitNo; /* loop variable */

      BitNo = 8;
      do
      {
         Phi2();
         /* Calculate Response Bits */
         if ( (U0 & E0_MASK) != 0)
         {
            *pResponse |= GetBitMask_1to8(BitNo);
         }
         BitNo--;
         if ( (U0 & E1_MASK) != 0) 
         {
            *pResponse |= GetBitMask_1to8(BitNo);
         }
      } 
      while (--BitNo);
   }

   /* Second call of first rounds after input of the challenge for bit32-47*/
   /* ByteNo already has the necessary start value 4 */
   for (; ByteNo != 6; ByteNo++) 
   {
      /* the challenge's byte to use */
      unsigned char ByteOfChallenge = Challenge[ByteNo];
      unsigned char BitNo; /* loop variable */

      BitNo = 8;
      do 
      {
         /* Calculate H Bit */
         HBit = ByteOfChallenge & GetBitMask_1to8(BitNo);
         Phi1();
      }
      while (--BitNo);
   }

   /* Calculate second response with double call to Phi2 */
   for (ByteNo = 4; ByteNo != 6; ByteNo++) 
   {
      /* build pointer to the resonse byte changed in the following loop; */
      TPointerToResponseByte pResponse = &Response[ByteNo];
      unsigned char BitNo; /* loop variable */
      BitNo = 8;
      do 
      {
         Phi2();
         /* Calculate Response Bits */
         if ( (U0 & E0_MASK) != 0) 
         {
            *pResponse |= GetBitMask_1to8(BitNo);
         }
         BitNo--;
         if ( (U0 & E1_MASK) != 0) 
         {
            *pResponse |= GetBitMask_1to8(BitNo);
         }
      } 
      while (--BitNo);
   }
}


#if 0
FAR_COS void CalcBRIL_Encrypt(BYTE *Challenge, BYTE *CustomerID, BYTE *SecretKey,BYTE *Response)
{
   #define ROUNDS_Brilliance 240
   const unsigned char f11_b[32] = {1,0,1,0,0,0,1,1,0,0,1,1,0,1,0,1,1,0,1,0,1,1,0,0,0,1,0,1,1,1,0,0};
   const unsigned char f12_b[32] = {0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1};
   const unsigned char f13_b[32] = {1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1};
   const unsigned char f14_b[32] = {0,1,0,1,1,0,1,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,0,1,1,0,1,0};
   const unsigned char f15_b[16] = {1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1};
   const unsigned char f2_b[16] = {0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,0};
   const unsigned char f3_b[16] = {0,1,3,3,2,1,2,0,0,2,1,2,3,3,1,0};

   int round_b;
   unsigned char  x0_b,x1_b,x2_b,x3_b,x4_b,x5_b,k0_b,k1_b,k2_b,k3_b,k4_b,k5_b,d0_b,d1_b,d2_b,d3_b,d4_b,
  	                  d5_b,d6_b,d7_b,d8_b,d9_b,d10_b,d11_b,d12_b,d13_b,d14_b,d15_b,a0_b,a1_b,a2_b,a3_b,b_b,count_b,j_b;
   unsigned char  kcarry_b,xcarry_b;
   unsigned char  ExCustomerID[5];
   unsigned char  count_bit_b=0,count_byte_id_b=0,count_byte_sk_b=0,temp_b=0;

   ExCustomerID[0]=CustomerID[0];
   ExCustomerID[1]=CustomerID[1];
   ExCustomerID[2]=CustomerID[2];
   ExCustomerID[3]=CustomerID[3];
   ExCustomerID[4]=0;
   if(CustomerID[0] & 0x08)
   {
      ExCustomerID[4] |=0x01;
   }
   if(CustomerID[0] & 0x80)
   {
      ExCustomerID[4] |=0x02;
   }
   if(CustomerID[1] & 0x08)
   {
      ExCustomerID[4] |=0x04;
   }
   if(CustomerID[1] & 0x80)
   {
      ExCustomerID[4] |=0x08;
   }
   if(CustomerID[2] & 0x08)
   {
      ExCustomerID[4] |=0x10;
   }
   if(CustomerID[2] & 0x80)
   {
      ExCustomerID[4] |=0x20;
   }
   if(CustomerID[3] & 0x08)
   {
      ExCustomerID[4] |=0x40;
   }
   if(CustomerID[3] & 0x80)
   {
      ExCustomerID[4] |=0x80;
   }

   /*local copy of the input data */
   x0_b = Challenge[0];
   x1_b = Challenge[1];
   x2_b = Challenge[2];
   x3_b = Challenge[3];
   x4_b = Challenge[4];
   x5_b = Challenge[5];
   k0_b = SecretKey[0];
   k1_b = SecretKey[1];
   k2_b = SecretKey[2];
   k3_b = SecretKey[3];
   k4_b = SecretKey[4];
   k5_b = SecretKey[5];

   /* do the rounds */
   for ( round_b = 0; round_b < ROUNDS_Brilliance; round_b++)
  {
     /* start by zeroing the d variables */
     d0_b=d1_b=d2_b=d3_b=d4_b=d5_b=d6_b=d7_b=d8_b=d9_b=d10_b=d11_b=d12_b=d13_b=d14_b=d15_b=a0_b=a1_b=a2_b=a3_b=b_b=0;
     /* d15= (x32,k32,x24,k24,x16) */
     if ( x4_b & 0x01)
     {
        d15_b |=0x10;
     }
     if ( k4_b & 0x01)
     {
        d15_b |=0x08;
     }
     if ( x3_b & 0x01)
     {
        d15_b |=0x04;
     }
     if ( k3_b & 0x01)
     {
        d15_b |=0x02;
     }
     if ( x2_b & 0x01)
     {
        d15_b |=0x01;
     }

      /* d14= (k16,x8,k8,k0) */
      if ( k2_b & 0x01)
      {
         d14_b |=0x08;
      }
      if ( x1_b & 0x01) 
      {
         d14_b |=0x04;
      }
      if ( k1_b & 0x01) 
      {
         d14_b |=0x02;
      }
      if ( k0_b & 0x01)
      {
        d14_b |=0x01; 
      }

      /* d13= (x33,k33,x25,k25,x17) */
      if ( x4_b & 0x02)
      {
         d13_b |=0x10;
      }
      if ( k4_b & 0x02)
      {
         d13_b |=0x08;
      }
      if ( x3_b & 0x02)
      {
         d13_b |=0x04;
      }
      if ( k3_b & 0x02) 
      {
         d13_b |=0x02;
      }
      if ( x2_b & 0x02) 
      {
         d13_b |=0x01;
      }

       // d12= (k17,x9,k9,k1) 
	if ( k2_b & 0x02) 
      {
         d12_b |=0x08;
      }
      if ( x1_b & 0x02) 
      {
         d12_b |=0x04;
      }
      if ( k1_b & 0x02) 
      {
         d12_b |=0x02;
      }
      if ( k0_b & 0x02) 
      {
         d12_b |=0x01;
      }

      //d11= (x34,k34,x26,k26,x18) 
      if ( x4_b & 0x04) 
      {
         d11_b |=0x10;
      }
      if ( k4_b & 0x04) 
      {
         d11_b |=0x08;
      }
      if ( x3_b & 0x04) 
      {
         d11_b |=0x04;
      }
      if ( k3_b & 0x04) 
      {
         d11_b |=0x02;
      }
      if ( x2_b & 0x04) 
      {
         d11_b |=0x01;
      }

       // d10= (k18,x10,k10,x2,k2) 
      if ( k2_b & 0x04) 
      {
         d10_b |=0x10;
      }
      if ( x1_b & 0x04) 
      {
         d10_b |=0x08;
      }
      if ( k1_b & 0x04) 
      {
         d10_b |=0x04;
      }
      if ( x0_b & 0x04) 
      {
         d10_b |=0x02;
      }
      if ( k0_b & 0x04) 
      {
         d10_b |=0x01;
      }

      // d9= (x35,k35,x27,k27,x19) 
      if ( x4_b & 0x08) 
      {
         d9_b |=0x10;
      }
      if ( k4_b & 0x08) 
      {
         d9_b |=0x08; 
      }
      if ( x3_b & 0x08) 
      {
         d9_b |=0x04;
      }
      if ( k3_b & 0x08) 
      {
         d9_b |=0x02;
      }
      if ( x2_b & 0x08) 
      {
         d9_b |=0x01;
      }

      // d8= (k19,x11,k11,x3,k3) 
      if ( k2_b & 0x08)
      {
         d8_b |=0x10;
      }
      if ( x1_b & 0x08)
      {
         d8_b |=0x08;
      }
      if ( k1_b & 0x08)
      {
         d8_b |=0x04;
      }
      if ( x0_b & 0x08)
      {
         d8_b |=0x02;
      }
      if ( k0_b & 0x08)
      {
         d8_b |=0x01;
      }

      // d7= (x36,k36,x28,k28,x20) 
      if ( x4_b & 0x10)
      {
         d7_b |=0x10;
      }
      if ( k4_b & 0x10)
      {
         d7_b |=0x08;
      }
      if ( x3_b & 0x10)
      {
         d7_b |=0x04;
      }
      if ( k3_b & 0x10)
      {
         d7_b |=0x02;
      }
      if ( x2_b & 0x10)
      {
         d7_b |=0x01;
      }

      // d6= (k20,x12,k12,x4,k4) 
      if ( k2_b & 0x10)
      {
         d6_b |=0x10;
      }
      if ( x1_b & 0x10)
      {
         d6_b |=0x08;
      }
      if ( k1_b & 0x10)
      {
         d6_b |=0x04;
      }
      if ( x0_b & 0x10)
      {
         d6_b |=0x02;
      }
      if ( k0_b & 0x10)
      {
         d6_b |=0x01;
      }

      // d5= (x37,k37,x29,k29,x21) 
      if ( x4_b & 0x20)
      {
         d5_b |=0x10;
      }
      if ( k4_b & 0x20) 
      {
         d5_b |=0x08;
      }
      if ( x3_b & 0x20)
      {
         d5_b |=0x04;
      }
      if ( k3_b & 0x20)
      {
         d5_b |=0x02;
      }
      if ( x2_b & 0x20)
      {
         d5_b |=0x01;
      }

      // d4= (k21,x13,k13,x5,k5) 
      if ( k2_b & 0x20)
      {
         d4_b |=0x10;
      }
      if ( x1_b & 0x20)
      {
         d4_b |=0x08;
      }
      if ( k1_b & 0x20)
      {
         d4_b |=0x04;
      }
      if ( x0_b& 0x20)
      {
         d4_b |=0x02;
      }
      if ( k0_b & 0x20)
      {
         d4_b |=0x01;
      }

      // d3= (x38,k38,x30,k30,x22) 
      if ( x4_b & 0x40)
      {
         d3_b |=0x10;
      }
      if ( k4_b & 0x40)
      {
         d3_b |=0x08;
      }
      if ( x3_b & 0x40)
      {
         d3_b |=0x04;
      }
      if ( k3_b & 0x40)
      {
         d3_b |=0x02;
      }
      if ( x2_b & 0x40)
      {
         d3_b |=0x01;
      }

      // d2= (k22,x14,k14,x6,k6) 
      if ( k2_b & 0x40)
      {
         d2_b |=0x10;
      }
      if ( x1_b & 0x40)
      {
         d2_b |=0x08;
      }
      if ( k1_b & 0x40)
      {
         d2_b |=0x04;
      }
      if ( x0_b & 0x40)
      {
         d2_b |=0x02;
      }
      if ( k0_b & 0x40)
      {
         d2_b |=0x01;
      }

      // d1= (x39,k39,x31,k31,x23) 
      if ( x4_b & 0x80)
      {
         d1_b |=0x10;
      }
      if ( k4_b & 0x80)
      {
         d1_b |=0x08;
      }
      if ( x3_b & 0x80)
      {
         d1_b |=0x04;
      }
      if ( k3_b & 0x80)
      {
         d1_b |=0x02;
      }
      if ( x2_b & 0x80)
      {
         d1_b |=0x01;
      }

      // d0= (k23,x15,k15,x7,k7) 
      if ( k2_b & 0x80)
      {
         d0_b |=0x10;
      }
      if ( x1_b & 0x80)
      {
         d0_b |=0x08;
      }
      if ( k1_b & 0x80)
      {
         d0_b |=0x04;
      }
      if ( x0_b & 0x80)
      {
         d0_b |=0x02;
      }
      if ( k0_b & 0x80)
      {
         d0_b |=0x01;
      }

      // reduce to 16 bits using the f1x[] functions 
      if ( f11_b[d0_b])
      {
         a0_b |=0x08;
      }
      if ( f12_b[d1_b])
      {
         a0_b |=0x04;
      }
      if ( f13_b[d2_b])
      {
         a0_b |=0x02;
      }
      if ( f14_b[d3_b])
      {
         a0_b |=0x01;
      }
      if ( f11_b[d4_b])
      {
         a1_b |=0x08;
      }
      if ( f12_b[d5_b])
      {
         a1_b |=0x04;
      }
      if ( f13_b[d6_b])
      {
         a1_b |=0x02;
      }
      if ( f14_b[d7_b])
      {
         a1_b |=0x01;
      }
      if ( f11_b[d8_b])
      {
         a2_b |=0x08;
      }
      if ( f12_b[d9_b])
      {
         a2_b |=0x04;
      }
      if ( f13_b[d10_b])
      {
         a2_b |=0x02;
      }
      if ( f14_b[d11_b])
      {
         a2_b |=0x01;
      }
      if ( f15_b[d12_b])
      {
         a3_b |=0x08;
      }
      if ( f12_b[d13_b])
      {
         a3_b |=0x04;
      }
      if ( f15_b[d14_b])
      {
         a3_b |=0x02;
      }
      if ( f14_b[d15_b])
      {
         a3_b |=0x01;
      }

      // reduce to 4 bits using f2[] 
      if ( f2_b[a0_b])
      {
         b_b |=0x01;
      }
      if ( f2_b[a1_b])
      {
         b_b |=0x02;
      }
      if ( f2_b[a2_b])
      {
         b_b |=0x04;
      }
      if ( f2_b[a3_b])
      {
         b_b |=0x08;
      }

      // reduce to 2 bits using f3[] 
      xcarry_b = f3_b[b_b];
      // recycle bits x1, x0 
      xcarry_b^=(x0_b & 3);

      temp_b=(SecretKey[6+count_byte_sk_b]>>count_bit_b)^(ExCustomerID[count_byte_id_b]>>count_bit_b);

      count_bit_b++;
      if (count_bit_b >7)
      {
         count_bit_b=0;
	  count_byte_sk_b++;
	  if (count_byte_sk_b>9)
	  {
	     count_byte_sk_b=0;
	  }
	  count_byte_id_b++;
	  if (count_byte_id_b>4)
	  {
	     count_byte_id_b=0;
	  }
			  
      }

      // shift x twice, putting carry bits into bits x47 and x46 
      for ( j_b=0;j_b<2;j_b++)
      {
         x0_b>>=1;
	  if (x1_b & 0x1)
	  {
	     x0_b |=0x80;
	  }
	  x1_b>>=1; 
	  if (x2_b & 0x1)
	  {
	     x1_b |=0x80;
	  }
	  x2_b>>=1;
	  if (x3_b & 0x1)
	  {
	     x2_b |=0x80;
	  }
	  x3_b>>=1;
	  if (x4_b & 0x1)
	  {
	     x3_b |=0x80;
	  }
	  x4_b>>=1;
	  if (x5_b & 0x1)
	  {
	     x4_b |=0x80;
	  }
	  x5_b>>=1;
	  if ((xcarry_b & 1) ^ (temp_b & 1))
	  {
	     x5_b |=0x80;
	  }
	  xcarry_b>>=1;
      }

      // Key Shcedule consisting of 48-bit LSFR
      // pre-calculate kcarry bit for key reg
      kcarry_b = 0;
      kcarry_b^=((k0_b & 0x01) != 0);  // bit 0 
      kcarry_b^=((k0_b & 0x02) != 0);  // bit 1 
      kcarry_b^=((k3_b & 0x08) != 0);  // bit 19 
      kcarry_b^=((k3_b & 0x10) != 0);  // bit 20 

      // shift key to right, and putting carry bits into bits x47 
      k0_b>>=1;
      if (k1_b & 1)
      {
         k0_b |= 0x80;
      }
      k1_b>>=1;
      if (k2_b & 1)
      {
         k1_b |= 0x80;
      }
      k2_b>>=1;
      if (k3_b & 1)
      {
         k2_b |= 0x80;
      }
      k3_b>>=1;
      if (k4_b & 1)
      {
         k3_b |= 0x80;
      }
      k4_b>>=1;
      if (k5_b & 1)
      {
         k4_b |= 0x80;
      }
      k5_b>>=1;
      if (kcarry_b)
      {
         k5_b |= 0x80;
      }
   }
	   
   // copy result to output 

   Response[0] = x0_b;
   Response[1] = x1_b;
   Response[2] = x2_b;
   Response[3] = x3_b;
   Response[4] = x4_b;
   Response[5] = x5_b;

}
#endif
/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/
