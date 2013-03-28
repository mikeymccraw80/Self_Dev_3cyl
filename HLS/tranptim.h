#ifndef TRANPTIM
#define TRANPTIM
/******************************************************************************
 *
 * Filename:          tranptim.h
 *
 * Description:       Contains functionality which is subsystem specific for
 *                    the Hyundai Transmission Software Project.
 *                    This includes Stopwatch timer data types.
 *                    Initialization routines used to initialize a timer
 *                    variable. Uses real-life seconds. This set includes
 *                    all scalars and constants used to perform initializations.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2002-2004, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"
#include "t_fixed.h"

/*****************************************************************************
 *  Configuration Include Files
 *****************************************************************************/
#include "trnspcfg.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Timer data types.  The data type names reflect timer precision and size.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
typedef INTEGER TwTIME_t_TranLoopTime_div64ms_DIFF;   /* 16-bit data type SIGNED  */
#define SwTIME_t_TranLoopTime_div64ms_DIFF 14      /* 16-bit mathlib scaling integer */
typedef WORD TwTIME_t_TranLoopTime_div64ms;   /* 16-bit data type */
#define SwTIME_t_TranLoopTime_div64ms 14      /* 16-bit mathlib scaling integer */

typedef BYTE TyTIME_t_TranLoopTime_ms;    /* 8-bit data type  */
typedef WORD TwTIME_t_TranLoopTime_ms;    /* 16-bit data type */
#define SwTIME_t_TranLoopTime_ms 8        /* 16-bit mathlib scaling integer */

typedef BYTE TyTIME_t_TranLoopTime_x2ms;
typedef WORD TwTIME_t_TranLoopTime_x2ms;
#define SwTIME_t_TranLoopTime_x2ms 7

typedef INTEGER TwTIME_t_TranLoopTime_x4ms_DIFF;
#define SwTIME_t_TranLoopTime_x4ms_DIFF 6
typedef BYTE TyTIME_t_TranLoopTime_x4ms;
typedef WORD TwTIME_t_TranLoopTime_x4ms;
#define SwTIME_t_TranLoopTime_x4ms 6

typedef BYTE TyTIME_t_TranLoopTime_x8ms;
typedef WORD TwTIME_t_TranLoopTime_x8ms;
#define SwTIME_t_TranLoopTime_x8ms 5

typedef BYTE TyTIME_t_TranLoopTime_x16ms;
typedef WORD TwTIME_t_TranLoopTime_x16ms;
#define SwTIME_t_TranLoopTime_x16ms 4

typedef BYTE TyTIME_t_TranLoopTime_x32ms;
typedef WORD TwTIME_t_TranLoopTime_x32ms;
#define SwTIME_t_TranLoopTime_x32ms 3

typedef BYTE TyTIME_t_TranLoopTime_x128ms;
typedef WORD TwTIME_t_TranLoopTime_x128ms;
#define SwTIME_t_TranLoopTime_x128ms 1

typedef BYTE TyTIME_t_TranLoopTime_x256ms;
typedef WORD TwTIME_t_TranLoopTime_x256ms;
#define SwTIME_t_TranLoopTime_x256ms 0


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * the first set of scalars are used to convert (at compile
 * time) the input (in seconds) to timer ticks.
 *
 * the next set of scalars are used to determine the maximum time
 * (in seconds) an input parameter can be before converting to timer
 * ticks; used in initialization (compile time) macro expansion.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define CfTRAN_LoopTime_x4msToLoopTime_div64msSclr 256
#define CfTRAN_SecToLoopTime_div64msSclr           (1/(CcTRNS_SYST_BASE_LOOP_TIME_SEC/64))
#define CfTRAN_MSecToLoopTime_div64msSclr          (CfTRAN_SecToLoopTime_div64msSclr/1000)
#define CfTRAN_SecToLoopTime_div64msSclr_DIFF      (1/(CcTRNS_SYST_BASE_LOOP_TIME_SEC/64))
#define CfTRAN_MSecToLoopTime_div64msSclr_DIFF     (CfTRAN_SecToLoopTime_div64msSclr/1000)
#define CfTRAN_SecToLoopTime_msSclr                (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC)
#define CfTRAN_MSecToLoopTime_msSclr               (CfTRAN_SecToLoopTime_msSclr/1000)
#define CfTRAN_SecToLoopTime_x2msSclr              (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x2)
#define CfTRAN_MSecToLoopTime_x2msSclr             (CfTRAN_SecToLoopTime_x2msSclr/1000)
#define CfTRAN_SecToLoopTime_x4msSclr              (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x4)
#define CfTRAN_MSecToLoopTime_x4msSclr             (CfTRAN_SecToLoopTime_x4msSclr/1000)
#define CfTRAN_SecToLoopTime_x4msSclr_DIFF         (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x4)
#define CfTRAN_MSecToLoopTime_x4msSclr_DIFF        (CfTRAN_SecToLoopTime_x4msSclr_DIFF/1000)
#define CfTRAN_SecToLoopTime_x8msSclr              (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x8)
#define CfTRAN_MSecToLoopTime_x8msSclr             (CfTRAN_SecToLoopTime_x8msSclr/1000)
#define CfTRAN_SecToLoopTime_x16msSclr             (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x16)
#define CfTRAN_MSecToLoopTime_x16msSclr            (CfTRAN_SecToLoopTime_x16msSclr/1000)
#define CfTRAN_SecToLoopTime_x32msSclr             (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x32)
#define CfTRAN_MSecToLoopTime_x32msSclr            (CfTRAN_SecToLoopTime_x32msSclr/1000)
#define CfTRAN_SecToLoopTime_x128msSclr            (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x128)
#define CfTRAN_MSecToLoopTime_x128msSclr           (CfTRAN_SecToLoopTime_x128msSclr/1000)
#define CfTRAN_SecToLoopTime_x256msSclr            (1/CcTRNS_SYST_BASE_LOOP_TIME_SEC_x256)
#define CfTRAN_MSecToLoopTime_x256msSclr           (CfTRAN_SecToLoopTime_x256msSclr/1000)


#define CfTRAN_MaxSecToLoopTime_div64ms16          (65535*(CcTRNS_SYST_BASE_LOOP_TIME_SEC/64))
#define CfTRAN_MaxMSecToLoopTime_div64ms16         (65535*((CcTRNS_SYST_BASE_LOOP_TIME_SEC/64)*1000))
#define CfTRAN_MaxSecToLoopTime_div64ms16_DIFF     (32767*(CcTRNS_SYST_BASE_LOOP_TIME_SEC/64))
#define CfTRAN_MinSecToLoopTime_div64ms16_DIFF     (-32768*(CcTRNS_SYST_BASE_LOOP_TIME_SEC/64))
#define CfTRAN_MaxMSecToLoopTime_div64ms16_DIFF    (32767*((CcTRNS_SYST_BASE_LOOP_TIME_SEC/64)*1000))
#define CfTRAN_MinMSecToLoopTime_div64ms16_DIFF    (-32768*((CcTRNS_SYST_BASE_LOOP_TIME_SEC/64)*1000))
#define CfTRAN_MaxSecToLoopTime_ms8                (255*CcTRNS_SYST_BASE_LOOP_TIME_SEC)
#define CfTRAN_MaxSecToLoopTime_ms16               (65535*CcTRNS_SYST_BASE_LOOP_TIME_SEC)
#define CfTRAN_MaxMSecToLoopTime_ms16              (65535*CcTRNS_SYST_BASE_LOOP_TIME_MS)
#define CfTRAN_MaxSecToLoopTime_x2ms8              (255*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x2)
#define CfTRAN_MaxSecToLoopTime_x2ms16             (65535*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x2)
#define CfTRAN_MaxMSecToLoopTime_x2_ms16           (65535*CcTRNS_SYST_BASE_LOOP_TIME_MS_x2)
#define CfTRAN_MaxSecToLoopTime_x4ms8              (255*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x4)
#define CfTRAN_MaxSecToLoopTime_x4ms16             (65535*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x4)
#define CfTRAN_MaxMSecToLoopTime_x4_ms16           (65535*CcTRNS_SYST_BASE_LOOP_TIME_MS_x4)
#define CfTRAN_MaxSecToLoopTime_x4ms16_DIFF        (32767*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x4)
#define CfTRAN_MinSecToLoopTime_x4ms16_DIFF        (-32767*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x4)
#define CfTRAN_MaxMSecToLoopTime_x4ms16_DIFF       (32767*CcTRNS_SYST_BASE_LOOP_TIME_MS_x4)
#define CfTRAN_MinMSecToLoopTime_x4ms16_DIFF       (-32767*CcTRNS_SYST_BASE_LOOP_TIME_MS_x4)
#define CfTRAN_MaxSecToLoopTime_x8ms8              (255*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x8)
#define CfTRAN_MaxSecToLoopTime_x8ms16             (65535*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x8)
#define CfTRAN_MaxMSecToLoopTime_x8_ms16           (65535*CcTRNS_SYST_BASE_LOOP_TIME_MS_x8)
#define CfTRAN_MaxSecToLoopTime_x16ms8             (255*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x16)
#define CfTRAN_MaxSecToLoopTime_x16ms16            (65535*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x16)
#define CfTRAN_MaxMSecToLoopTime_x16_ms16          (65535*CcTRNS_SYST_BASE_LOOP_TIME_MS_x16)
#define CfTRAN_MaxSecToLoopTime_x32ms8             (255*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x32)
#define CfTRAN_MaxSecToLoopTime_x32ms16            (65535*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x32)
#define CfTRAN_MaxMSecToLoopTime_x32_ms16          (65535*CcTRNS_SYST_BASE_LOOP_TIME_MS_x32)
#define CfTRAN_MaxSecToLoopTime_x128ms8            (255*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x128)
#define CfTRAN_MaxSecToLoopTime_x128ms16           (65535*CcTRNS_SYST_BASE_LOOP_TIME_SEC_x128)
#define CfTRAN_MaxSecToLoopTime_x256ms8            (255)
#define CfTRAN_MaxSecToLoopTime_x256ms16           (65535)
#define CcTRAN_MS_Per_Sec                          (1000)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * initialization (at compile time) macros.
 *
 * these routines convert from real-life time units of seconds to
 * a timer type (with one of the given precisions)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * convert real-life units (in seconds) to LoopTimex16 seconds precision timers
 */

#define C_TranLoopTime_div64ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_div64ms16)?65535: \
   (WORD) (Seconds*CfTRAN_SecToLoopTime_div64msSclr))

#define C_TranLoopTime_div64ms16_msec( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_div64ms16)?65535: \
   (WORD) (MSeconds*CfTRAN_MSecToLoopTime_div64msSclr))

#define C_TranLoopTime_div64ms16_DIFF( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_div64ms16_DIFF)?32767: \
   ((Seconds<CfTRAN_MinSecToLoopTime_div64ms16_DIFF)?-32768: \
   (INTEGER) (Seconds*CfTRAN_SecToLoopTime_div64msSclr_DIFF)))

#define C_TranLoopTime_div64ms16_msec_DIFF( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_div64ms16_DIFF)?32767: \
   ((MSeconds<CfTRAN_MinMSecToLoopTime_div64ms16_DIFF)?-32768: \
   (INTEGER) (MSeconds*CfTRAN_MSecToLoopTime_div64msSclr_DIFF)))

/*
 * convert real-life units (in seconds) to LoopTime ms precision timers
 */

#define C_TranLoopTime_ms8( Seconds ) \
  ((Seconds> CfTRAN_MaxSecToLoopTime_ms8)?255: \
    (BYTE)(Seconds*CfTRAN_SecToLoopTime_msSclr))

#define C_TranLoopTime_ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_ms16)?65535: \
   (WORD) (Seconds*CfTRAN_SecToLoopTime_msSclr))

#define C_TranLoopTime_ms16_msec( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_ms16)?65535: \
   (WORD) (MSeconds*CfTRAN_MSecToLoopTime_msSclr))

/*
 * convert real-life units (in seconds) to LoopTimex2 ms precision timers
 */

#define C_TranLoopTime_x2ms8( Seconds ) \
  ((Seconds> CfTRAN_MaxSecToLoopTime_x2ms8)?255: \
    (BYTE)(Seconds*CfTRAN_SecToLoopTime_x2msSclr))

#define C_TranLoopTime_x2ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x2ms16)?65535: \
   (WORD) (Seconds*CfTRAN_SecToLoopTime_x2msSclr))

#define C_TranLoopTime_x2ms16_msec( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_x2_ms16)?65535: \
   (WORD) (MSeconds*CfTRAN_MSecToLoopTime_x2msSclr))


/*
 * convert real-life units (in seconds) to LoopTimex4 ms precision timers
 */

#define C_TranLoopTime_x4ms8( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x4ms8)?255: \
   (BYTE) (Seconds*CfTRAN_SecToLoopTime_x4msSclr))

#define C_TranLoopTime_x4ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x4ms16)?65535: \
   (WORD) (Seconds*CfTRAN_SecToLoopTime_x4msSclr))

#define C_TranLoopTime_x4ms16_msec( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_x4_ms16)?65535: \
   (WORD) (MSeconds*CfTRAN_MSecToLoopTime_x4msSclr))

#define C_TranLoopTime_x4ms16_DIFF( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x4ms16_DIFF)?32767: \
   ((Seconds<CfTRAN_MinSecToLoopTime_x4ms16_DIFF)?-32768: \
   (INTEGER) (Seconds*CfTRAN_SecToLoopTime_x4msSclr_DIFF)))

#define C_TranLoopTime_x4ms16_msec_DIFF( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_x4ms16_DIFF)?32767: \
   ((MSeconds<CfTRAN_MinMSecToLoopTime_x4ms16_DIFF)?-32768: \
   (INTEGER) (MSeconds*CfTRAN_MSecToLoopTime_x4msSclr_DIFF)))

/*
 * convert real-life units (in seconds) to LoopTimex8 ms precision timers
 */

#define C_TranLoopTime_x8ms8( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x8ms8)?255: \
   (BYTE) (Seconds*CfTRAN_SecToLoopTime_x8msSclr))

#define C_TranLoopTime_x8ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x8ms16)?65535: \
   (WORD) (Seconds*CfTRAN_SecToLoopTime_x8msSclr))

#define C_TranLoopTime_x8ms16_msec( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_x8_ms16)?65535: \
   (WORD) (MSeconds*CfTRAN_MSecToLoopTime_x8msSclr))

/*
 * convert real-life units (in seconds) to LoopTimex16 ms precision timers
 */
#define C_TranLoopTime_x16ms8( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x16ms8)?255: \
   (BYTE) (Seconds*CfTRAN_SecToLoopTime_x16msSclr))
#define C_TranLoopTime_x16ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x16ms16)?65535: \
   (WORD) (Seconds*CfTRAN_SecToLoopTime_x16msSclr))
#define C_TranLoopTime_x16ms16_msec( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_x16_ms16)?65535: \
   (WORD) (MSeconds*CfTRAN_MSecToLoopTime_x16msSclr))

/*
 * convert real-life units (in seconds) to LoopTimex32 ms precision timers
 */

#define C_TranLoopTime_x32ms8( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x32ms8)?255:\
   (BYTE) (Seconds*CfTRAN_SecToLoopTime_x32msSclr))

#define C_TranLoopTime_x32ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x32ms16)?65535:\
   (WORD) (Seconds*CfTRAN_SecToLoopTime_x32msSclr))

#define C_TranLoopTime_x32ms16_msec( MSeconds ) \
  ((MSeconds>CfTRAN_MaxMSecToLoopTime_x32_ms16)?65535: \
   (WORD) (MSeconds*CfTRAN_MSecToLoopTime_x32msSclr))


/*
 * convert real-life units (in seconds) to LoopTimex128 ms precision timers
 */

#define C_TranLoopTime_x128ms8( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x128ms8)?255:\
   (BYTE) (Seconds*CfTRAN_SecToLoopTime_x128msSclr))

#define C_TranLoopTime_x128ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x128ms16)?65535:\
   (WORD) (Seconds*CfTRAN_SecToLoopTime_x128msSclr))


/*
 * convert real-life units (in seconds) to LoopTimex256 ms precision timers
 */

#define C_TranLoopTime_x256ms8( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x256ms8)?255:\
   (BYTE) (Seconds*CfTRAN_SecToLoopTime_x256msSclr))

#define C_TranLoopTime_x256ms16( Seconds ) \
  ((Seconds>CfTRAN_MaxSecToLoopTime_x256ms16)?65535:\
   (WORD) (Seconds*CfTRAN_SecToLoopTime_x256msSclr))

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.1   021021 arr 2164 Created module.
* tci_pt3#2
*       040517 kvm 3960 Added CcTRAN_MS_Per_Sec macro
* 3     050909 hdb 5302 Add additional disable condition for sport mode
*                        Added: C_TranLoopTime_ms16_msec
*                               C_TranLoopTime_x2ms16_msec
*                               C_TranLoopTime_x8ms16_msec
*                               C_TranLoopTime_x16ms16_msec
*                               C_TranLoopTime_x32ms16_msec
* 3     050822 hdb 5260 Change enable/disable condition of CstLockUp for
*                       engine speed control.  Added:
*                         C_TranLoopTime_x8ms16_msec
*                         C_TranLoopTime_x16ms16_msec
*                         C_TranLoopTime_x32ms16_msec
* ktc_pt1#4
*       051107 rmn -BM- Merged 'tranptim.h-3' with 'tranptim.h-2.1.1'.
*
******************************************************************************/
