#ifndef IMMO_ENCRYPT_H
#define IMMO_ENCRYPT_H
//*****************************************************************************
//*                                                                           *
//* Copyright 2004 Delphi Technologies, Inc., All Rights Reserved             *
//*                                                                           *
//* Module:         tabcrypt.h                                                *
//* Creator:        Uwe Kneemeyer                                             *
//* Location:       Bomig (Germany)                                           *
//*                                                                           *
//*****************************************************************************
//*                                                                           *
//* CLASSIFICATION:   D E L P H I   c o n f i d e n t i a l                   *
//*                                                                           *
//* DESCRIPTION:                                                              *
//*   Header-File which contains the declaration of API                       *
//*                                                                           *
//*                                                                           *
//*****************************************************************************

//-----------------------------------------------------------------------------
//---------------------- EXPORTED TYPE DECLARATIONS ---------------------------
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//----------------------EXPORTED OBJECT DECLARATIONS --------------------------
//-----------------------------------------------------------------------------
//#include "reuse.h"
/*
  The variable "txpdata" is used as buffer for the input data for the function
  "tabcrypt" as well as the buffer for the result of that function.

  Input:
    txpdata [15] ... txpdata [12]
    These data correspond to those, which are sent from the ECM to the
    immobilizer.
    Order:
      txpdata [15].7
      txpdata [15].6
      ...
      txpdata [15].0
      txpdata [14].7
      ...
      txpdata [12].0

  Output:
    txpdata [0]
    txpdata [1]

    These data corrrespond to those, which are sent from the immobilizer to the
    ECM.
    Order:
      txpdata [1].5
      txpdata [1].4
      ...
      txpdata [1].0
      txpdata [0].7
      ...
      txpdata [0].0
*/
//extern u8 txpdata [16];
// constant + macro definitons by #define directive - Scope: this File
// ********************************************************************

// Customer Key = EC 46 B0 1E 8B C3
//#define CUSTOMER_KEY_H   0xEC46       /* higher 16 Bit */
//#define CUSTOMER_KEY_L   0xB01E8BC3L  /* lower  32 Bit */

//#define BIT15 0x8000
//#define export volatile


//#define BIG_ENDIAN


// typedefs - Scope: this File
// ********************************************************************
//typedef unsigned short U16;
//typedef unsigned long  U32;
//typedef unsigned char  U8;


//#ifdef BIG_ENDIAN
  /* this part makes separate access to all 4 bytes available */
  /* high byte first */
  //typedef struct {
 // U8 hh;
 // U8 hl;
 // U8 lh;
 // U8 ll;
 // } U32_via_U8;
//#endif

//#ifdef LITTLE_ENDIAN
  /* this part makes separate access to all 4 bytes available */
  /* low byte first */
 // typedef struct {
 // U8 ll;
 // U8 lh;
  //U8 hl;
 // U8 hh;
  //} U32_via_U8;
//#endif

/* access to the whole 32-bit-unit */
//typedef struct{
 // U32 l;
//} U32_via_U32;

/* and now: all together... */
//typedef union {
//  U32_via_U8  c;
//  U32_via_U32 l;
//} myU32;



/* some definitions for less typing work */
//#define chh c.hh
//#define chl c.hl
//#define clh c.lh
//#define cll c.ll
//#define lon l.l

/* maskpatterns for the positions of bits, which define the feedback */
//#define HH_MASKE 0x84
//#define HL_MASKE 0x28
//#define LH_MASKE 0x50
//#define LL_MASKE 0x03

/* some useful constants */
//#define START_DIVERGENCY 38
//#define F_SIZE 12           /* size of first result */
//#define F_MASK 0x0FFF
//#define GAP_DIVERGENCY 20
//#define G_SIZE 14           /* size of second result */
//#define G_MASK 0x3FFF

//-----------------------------------------------------------------------------
//--------------------- EXPORTED FUNCTIONS PROTOTYPES -------------------------
//-----------------------------------------------------------------------------

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
//extern FAR_COS void digsig( unsigned char *, unsigned char *, unsigned char *);

//=============================================================================
// FUNCTION: tabcrypt
//-----------------------------------------------------------------------------
// DESCRIPTION:
//   This function calculates the output of the crypt-algorithm-function "f" 
//
// PARAMETERS:
//   no
//
// RETURN VALUE:  
//   no
//=============================================================================
//extern FAR_COS void tabcrypt (u8* txpdata);

//extern U16      F_Result, G_Result;
//extern uint8_t  ECMSeed[];

/*extern FAR_COS void mini_crypt( U32 random, U16 secretkey_h, U32 secretkey_l,
                          U16 *f_result, U16 *g_result);*/
//extern FAR_COS void mini_crypt ( uint32_t random, uint16_t secretkey_h, uint32_t secretkey_l,
//                        U16 *f_result, U16 *g_result);

/* ==========================================================================*/
/* File revision history (top to bottom, first revision to last revision     */
/* ==========================================================================*/
/*                                                                           */
/* Date         user id     SCR       (description on following lines)       */
/* ----------   -------     ---                                              */
/* 
/* ==========================================================================*/


#endif // #ifdef IMMO_ENCRYPT_H
