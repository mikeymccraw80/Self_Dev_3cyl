
/*****************************************************************************
 *
 * (c) 1997 General Motors Corporation, all rights reserved
 *
 *  Workfile:    %name: t_base.h %
 *  Revision:    %version: 1 %
 *  Modtime:     %date_created: Wed Mar 19 09:46:37 2008 %
 *  Author:      %created_by: vzp48z %
 *
 *  Description:        This file contains global definitions associated
 *                      with this project.  All information is considered
 *                      public.
 *
 *                      This file contains definitions whose purpose is to
 *                      allow GMPT application code to be CPU and compiler
 *                      independant.
 *
 *****************************************************************************/
#ifndef T_BASE
#define T_BASE

/*****************************************************************************/
/* <stddef.h> and <string.h> are included for the definitions of "NULL",     */
/* "size_t", "ptrdiff_t", and "offsetof".  Both headers are included because */
/* some compilers define "NULL" and "size_t" in <string.h> and other         */
/* compilers define these in <stddef.h>.  Therefore, if an application needs */
/* a definition from a system library, it should be done here so that        */
/* compiler differences do not force application code to change.             */
/*****************************************************************************/
#include <stddef.h>
#include <string.h>

/*****************************************************************************
 *
 * Description:         Define 8, 16 & 32 bit variables in a hardware
 *                      independent fashion.
 *
 *
 * Change History:      Created for testing Jun-94
 *****************************************************************************/

/*****************************************************************************/
/* Define base types to be used by all GM "C" Code                           */
/*                                                                           */
/*                                                                           */
/* This module will be include by all GM "C" Software                        */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/* Define CPU Dependent Information                                          */
/*****************************************************************************/
/*
/*  BigEndian:    One who breaks open an egg on the big end                  */
/*  LittleEndian: One who breaks open an egg on the little end               */
/*  It is a long standing war between the Lilliput and the Blefuscu.         */
/*  From Gulliver's Travels by Jonathan Swift                                */
/*                                                                           */
/*                                                                           */
/*  In computer terms, BigEndian computers have the most significant byte    */
/*     first. LittleEndian computer have the most significant byte last.     */


/*****************************************************************************/
/* Define all hardware dependent types                                       */
/*****************************************************************************/



#define CPU_BigEndian 1
  typedef signed char        SHORTINT;
  typedef unsigned char      BYTE;
  typedef short signed int   INTEGER;
  typedef short unsigned int WORD;
  typedef long signed int    LONGINT;
  typedef long unsigned int  LONGWORD;
  typedef signed int         MEDINT;
  typedef unsigned int       MEDWORD;


/*****************************************************************************/
/* Define Bit Mask Types                                                     */
/*****************************************************************************/

#define MAX_UL             0xFFFFFFFF
#define MIN_UL             0x00000000
#define MAX_SL             0x7FFFFFFF
#define MIN_SL             0x80000000
#define MAX_UM             0x00FFFFFF
#define MIN_UM             0x00000000
#define MAX_SM             0x007FFFFF
#define MIN_SM             0xFF800000
#define MAX_UW             0xFFFF
#define MIN_UW             0x0000
#define MAX_SW             0x7FFF
#define MIN_SW             0x8000
#define MAX_UB             0xFF   /* maximum value of byte */
#define MIN_UB             0x00   /* minimum value of byte */
#define luMAX_UW           65535L
#define luMIN_UW           0L
#define liMAX_SW           32767L
#define liMIN_SW          -32768L

/*****************************************************************************/
/* Define Pointer Qualifiers                                                 */
/*****************************************************************************/


#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 
******************************************************************************/

