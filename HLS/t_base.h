
/******************************************************************************
 *
 * Filename:          t_base.h
 *
 * Description:       This file contains global definitions associated
 *                    with this project.  All information is considered
 *                    public.
 *  Revision:    %version: kok_pt2#5 %
 *  Modtime:     %date_created: Tue Sep  6 14:00:45 2011 %
 *  Author:      %created_by: zzmkdw %
 *
 *                    This file contains definitions whose purpose is to
 *                    allow GMPT application code to be CPU and compiler
 *                    independant.
 *
 * Forward Engine Management Systems
 *
 * Copyright 1997-2011, Delphi Technologies, Inc.
 * All rights reserved.
 *****************************************************************************
 *
 * Current Module Info:
 * %full_name:      tcb_pt1#4/incl/t_base.h/kok_pt2#5 %
 * %date_created:   Tue Sep  6 14:00:45 2011 %
 * %version:        kok_pt2#5 %
 * %derived_by:     zzmkdw %
 *
 *****************************************************************************/
#ifndef T_BASE
#define T_BASE



  typedef signed char        shortint_t;
  typedef unsigned char      byte_t;
  typedef short signed int   integer_t;
  typedef short unsigned int word_t;
  typedef long signed int    longint_t;
  typedef long unsigned int  longword_t;
  typedef signed int         medint_t;
  typedef unsigned int       medword_t;

#define SHORTINT   shortint_t
#define BYTE       byte_t
#define INTEGER    integer_t
#define WORD       word_t
#define LONGINT    longint_t
#define LONGWORD   longword_t
#define MEDINT     medint_t
#define MEDWORD    medword_t



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

#define huge
#define far
#define near

#endif

