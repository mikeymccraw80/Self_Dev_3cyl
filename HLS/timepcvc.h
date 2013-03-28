#ifndef TIMEPCVC
#define TIMEPCVC
/******************************************************************************
 *
 * Filename:          timepcvc.h
 *
 * Description:       Contains routines for converting calibration time values
 *                    into counts. Also defined are the Stopwatch timer data
 *                    types and scalers that are used by these routines. Uses
 *                    real-life seconds.
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
 * Copyright 2000-2010, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************
 *
 * Current Module Info:
 *
 * %full_name:      tcb_pt1#5/incl/timepcvc.h/kok_pt2#10 %
 * %date_created:   Mon Oct 11 13:59:33 2010 %
 * %version:        kok_pt2#10 %
 * %derived_by:     qzy3n5 %
 *
 *****************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "t_base.h"
#include "t_fixed.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *
 * This section is for PRIVATE functions only and should never be used
 * by any subsystem other than the TIME subsystem.  It does not come with
 * any guarantees!
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

/*
 * MAX function.
 */
#define _MIN(a,b) (((a)<(b))?(a):(b))

/*
 * "paste" function.
 */
/*
 * #define _cat(x,y) x##y
 * #define _xcat(x,y) _cat(x,y)
 */



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Timer data types.  The data type names reflect timer precision and size.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
typedef INTEGER TwTIME_t_R0p061035ms_DIFF;   /* 16-bit data type SIGNED  */
#define SwTIME_t_R0p061035ms_DIFF 14      /* 16-bit mathlib scaling integer */
typedef WORD TwTIME_t_R0p061035ms;   /* 16-bit data type */
#define SwTIME_t_R0p061035ms 14      /* 16-bit mathlib scaling integer */
typedef WORD TwTIME_t_R0p12207ms;
#define SwTIME_t_R0p12207ms 13
typedef BYTE TyTIME_t_R3p90625ms;    /* 8-bit data type  */
typedef WORD TwTIME_t_R3p90625ms;    /* 16-bit data type */
#define SwTIME_t_R3p90625ms 8        /* 16-bit mathlib scaling integer */

typedef BYTE TyTIME_t_R7p8125ms;
typedef WORD TwTIME_t_R7p8125ms;
#define SwTIME_t_R7p8125ms 7
typedef INTEGER TwTIME_t_R7p8125ms_DIFF;
#define SwTIME_t_R7p8125ms_DIFF 7

typedef BYTE TyTIME_t_R7p81ms;
typedef WORD TwTIME_t_R7p81ms;

typedef BYTE TyTIME_t_R15p625ms;
typedef WORD TwTIME_t_R15p625ms;
#define SwTIME_t_R15p625ms 6
typedef INTEGER TwTIME_t_R15p625ms_DIFF;
#define SwTIME_t_R15p625ms_DIFF 6

typedef BYTE TyTIME_t_R31p25ms;
typedef WORD TwTIME_t_R31p25ms;
#define SwTIME_t_R31p25ms 5
typedef BYTE TyTIME_t_R62p5ms;
typedef WORD TwTIME_t_R62p5ms;
#define SwTIME_t_R62p5ms 4
typedef BYTE TyTIME_t_R125ms;
typedef WORD TwTIME_t_R125ms;
#define SwTIME_t_R125ms 3
typedef BYTE TyTIME_t_R250ms;
typedef WORD TwTIME_t_R250ms;
#define SwTIME_t_R250ms 2
typedef BYTE TyTIME_t_R500ms;
typedef WORD TwTIME_t_R500ms;
#define SwTIME_t_R500ms 1
typedef BYTE TyTIME_t_R1000ms;
typedef WORD TwTIME_t_R1000ms;
#define SwTIME_t_R1000ms 0

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * the conversion factors used below were chosen based on the
 * following observations:
 *
 * for a 3p90625ms precision timer, 3.90625 ms = 1 unit
 * in units of seconds, 3.90625 ms = V_SECONDS( 0.00390625 ) = 0.03 units
 * in units of seconds K, 3.90625 ms = V_SECONDS_K( 0.00390625 ) = 4 units
 * in units of milliseconds, 3.90625 ms = V_MILLISECONDS( 3.90625 ) = 500 units
 *
 * for a 15p625ms precision timer, 15.625 ms = 1 unit
 * in units of seconds, 15.625 ms = V_SECONDS( 0.015625 ) = 0.125 units
 * in units of seconds K, 15.625 ms = V_SECONDS_K( 0.015625 ) = 16 units
 * in units of milliseconds, 15.625 ms = V_MILLISECONDS(15.625 ) = 2000 units
 *
 * for a 62.5ms precision timer, 62.5 ms = 1 unit
 * in units of seconds, 62.5 ms = V_SECONDS( 0.0625 ) = 0.5 units
 * in units of seconds K, 62.5 ms = V_SECONDS_K( 0.0625 ) = 64 units
 * in units of milliseconds, 62.5 ms = V_MILLISECONDS( 62.5 ) = 8000 units
 *
 * for a 125ms precision timer, 125 ms = 1 unit
 * in units of seconds, 125 ms = V_SECONDS( .125 ) = 1 units
 * in units of seconds K, 125 ms = V_SECONDS_K( .125 ) = 128 units
 * in units of milliseconds, 125 ms = V_MILLISECONDS( 125 ) = 16000 units
 *
 * for a 1000ms precision timer, 1000 ms = 1 unit
 * in units of seconds, 1000 ms = V_SECONDS( 1 ) = 8 units
 * in units of seconds K, 1000 ms = V_SECONDS_K( 1 ) = 1024 units
 * in units of milliseconds, 1000 ms = V_MILLISECONDS( 1000 ) = 128000 units
 *                                                    (N/A)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


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
#define CfTIME_R15p625msToR0p061035msSclr   256
#define CfTIME_SecToR0p061035msSclr      16384
#define CfTIME_MSecToR0p061035msSclr     16.384
#define CfTIME_SecToR0p061035msSclr_DIFF   16384
#define CfTIME_MSecToR0p061035msSclr_DIFF  16.384
#define CfTIME_SecToR0p12207msSclr       8192
#define CfTIME_MSecToR0p12207msSclr      8.192
#define CfTIME_SecToR3p90625msSclr       256   /* 1 sec=1000 ms=256 ticks */
#define CfTIME_MSecToR3p90625msSclr      0.256
#define CfTIME_SecToR7p8125msSclr        128
#define CfTIME_MSecToR7p8125msSclr       0.128
#define CfTIME_SecToR15p625msSclr        64
#define CfTIME_MSecToR15p625msSclr       0.064
#define CfTIME_SecToR15p625msSclr_DIFF   64
#define CfTIME_MSecToR15p625msSclr_DIFF  0.064
#define CfTIME_SecToR31p25msSclr         32
#define CfTIME_MSecToR31p25msSclr        0.032
#define CfTIME_SecToR62p5msSclr          16
#define CfTIME_MSecToR62p5msSclr         0.016
#define CfTIME_SecToR125msSclr           8
#define CfTIME_MSecToR125msSclr          0.008
#define CfTIME_SecToR250msSclr           4
#define CfTIME_MSecToR250msSclr          0.004
#define CfTIME_SecToR500msSclr           2
#define CfTIME_MSecToR500msSclr          0.002
#define CfTIME_SecToR1000msSclr          1
#define CfTIME_MSecToR1000msSclr         0.001

#define CfTIME_MaxSecToR0p061035ms16   (65535*0.00006103515625)
#define CfTIME_MaxMSecToR0p061035ms16  (65535*0.06103515625)
#define CfTIME_MaxSecToR0p061035ms16_DIFF   (32767*0.00006103515625)
#define CfTIME_MinSecToR0p061035ms16_DIFF   (-32768*0.00006103515625)
#define CfTIME_MaxMSecToR0p061035ms16_DIFF  (32767*0.06103515625)
#define CfTIME_MinMSecToR0p061035ms16_DIFF  (-32768*0.06103515625)
#define CfTIME_MaxSecToR0p12207ms16    (65535*0.0001220703125)
#define CfTIME_MaxMSecToR0p12207ms16   (65535*0.1220703125)
#define CfTIME_MaxSecToR3p90625ms8     (255*0.00390625)
#define CfTIME_MaxSecToR3p90625ms16    (65535*0.00390625)
#define CfTIME_MaxSecToR7p8125ms8      (255*0.0078125)
#define CfTIME_MaxSecToR7p8125ms16     (65535*0.0078125)
#define CfTIME_MaxSecToR7p8125ms16_DIFF    (32767*0.0078125)
#define CfTIME_MinSecToR7p8125ms16_DIFF    (-32767*0.0078125)
#define CfTIME_MaxMSecToR7p8125ms16    (65535*7.8125)
#define CfTIME_MaxSecToR15p625ms8      (255*0.015625)
#define CfTIME_MaxSecToR15p625ms16     (65535*0.015625)
#define CfTIME_MaxMSecToR15p625ms16    (65535*15.625)
#define CfTIME_MaxSecToR15p625ms16_DIFF     (32767*0.015625)
#define CfTIME_MinSecToR15p625ms16_DIFF     (-32767*0.015625)
#define CfTIME_MaxMSecToR15p625ms16_DIFF    (32767*15.625)
#define CfTIME_MinMSecToR15p625ms16_DIFF    (-32767*15.625)
#define CfTIME_MaxSecToR31p25ms8       (255*0.03125)
#define CfTIME_MaxSecToR31p25ms16      (65535*0.03125)
#define CfTIME_MaxSecToR62p5ms8        (255*0.0625)
#define CfTIME_MaxSecToR62p5ms16       (65535*0.0625)
#define CfTIME_MaxSecToR125ms8         (255*0.125)
#define CfTIME_MaxSecToR125ms16        (65535*0.125)
#define CfTIME_MaxSecToR250ms8         (255*0.25)
#define CfTIME_MaxSecToR250ms16        (65535*0.25)
#define CfTIME_MaxSecToR500ms8         (255*0.5)
#define CfTIME_MaxSecToR500ms16        (65535*0.5)
#define CfTIME_MaxSecToR1000ms8        (255)
#define CfTIME_MaxSecToR1000ms16       (65535)

#define CyTIME_MaxCnts8                (255)
#define CwTIME_MaxCnts16               (65535)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * initialization (at compile time) macros.
 *
 * these routines convert from real-life time units of seconds to
 * a timer type (with one of the given precisions)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*
 * convert real-life units (in seconds) to 0.06103515625 ms precision timers
 */

#define C_R0p061035ms16( Seconds ) \
  ((WORD) (Seconds>CfTIME_MaxSecToR0p061035ms16)?(WORD) 65535: \
   (WORD) (Seconds*CfTIME_SecToR0p061035msSclr))

#define C_R0p061035ms16_msec( MSeconds ) \
  ((WORD) (MSeconds>CfTIME_MaxMSecToR0p061035ms16)?(WORD) 65535: \
   (WORD) (MSeconds*CfTIME_MSecToR0p061035msSclr))

#define C_R0p061035ms16_DIFF( Seconds ) \
  ((INTEGER)(Seconds>CfTIME_MaxSecToR0p061035ms16_DIFF)?(INTEGER) 32767: \
   ((INTEGER)(Seconds<CfTIME_MinSecToR0p061035ms16_DIFF)?(INTEGER) -32768: \
   (INTEGER) (Seconds*CfTIME_SecToR0p061035msSclr_DIFF)))

#define C_R0p061035ms16_msec_DIFF( MSeconds ) \
  ((INTEGER)(MSeconds>CfTIME_MaxMSecToR0p061035ms16_DIFF)?(INTEGER) 32767: \
   ((INTEGER)(MSeconds<CfTIME_MinMSecToR0p061035ms16_DIFF)?(INTEGER) -32768: \
   (INTEGER) (MSeconds*CfTIME_MSecToR0p061035msSclr_DIFF)))

/*
 * convert real-life units (in seconds) to 0.1220703125 ms precision timers
 */

#define C_R0p12207ms16( Seconds ) \
  ((WORD) (Seconds>CfTIME_MaxSecToR0p12207ms16)?(WORD) 65535: \
   (WORD) (Seconds*CfTIME_SecToR0p12207msSclr))

#define C_R0p12207ms16_msec( MSeconds ) \
  ((WORD) (MSeconds>CfTIME_MaxMSecToR0p12207ms16)?(WORD) 65535: \
   (WORD) (MSeconds*CfTIME_MSecToR0p12207msSclr))

/*
 * convert real-life units (in seconds) to 3.90625 ms precision timers
 */

#define C_R3p90625ms8( Seconds ) \
  ((BYTE) (Seconds> CfTIME_MaxSecToR3p90625ms8)?(BYTE) 255: \
    (BYTE)(Seconds*CfTIME_SecToR3p90625msSclr))

#define C_R3p90625ms16( Seconds ) \
  ((WORD) (Seconds>CfTIME_MaxSecToR3p90625ms16)?(WORD) 65535: \
   (WORD) (Seconds*CfTIME_SecToR3p90625msSclr))

/*
 * convert real-life units (in seconds) to 7.8125 ms precision timers
 */

#define C_R7p8125ms8( Seconds ) \
  ( (BYTE)(Seconds> CfTIME_MaxSecToR7p8125ms8)?(BYTE) 255: \
    (BYTE)(Seconds*CfTIME_SecToR7p8125msSclr))

#define C_R7p8125ms16( Seconds ) \
  ((WORD) (Seconds>CfTIME_MaxSecToR7p8125ms16)?(WORD) 65535: \
   (WORD) (Seconds*CfTIME_SecToR7p8125msSclr))

#define C_R7p8125ms16_DIFF( Seconds ) \
  ((INTEGER)(Seconds>CfTIME_MaxSecToR7p8125ms16_DIFF)?(INTEGER)32767: \
   ((INTEGER)(Seconds<CfTIME_MinSecToR7p8125ms16_DIFF)?(INTEGER)-32768: \
   (INTEGER) (Seconds*CfTIME_SecToR7p8125msSclr)))

#define C_R7p8125ms16_msec( MSeconds ) \
  ((WORD) (MSeconds>CfTIME_MaxMSecToR7p8125ms16)?(WORD) 65535: \
   (WORD) (MSeconds*CfTIME_MSecToR7p8125msSclr))

/*
 * convert real-life units (in seconds) to 15.625 ms precision timers
 */

#define C_R15p625ms8( Seconds ) \
  ((BYTE) (Seconds>CfTIME_MaxSecToR15p625ms8)?(BYTE) 255: \
   (BYTE) (Seconds*CfTIME_SecToR15p625msSclr))

#define C_R15p625ms16( Seconds ) \
  ((WORD)(Seconds>CfTIME_MaxSecToR15p625ms16)?(WORD)65535: \
   (WORD) (Seconds*CfTIME_SecToR15p625msSclr))

#define C_R15p625ms16_msec( MSeconds ) \
  ((WORD) (MSeconds>CfTIME_MaxMSecToR15p625ms16)?(WORD)65535: \
   (WORD) (MSeconds*CfTIME_MSecToR15p625msSclr))

#define C_R15p625ms16_DIFF( Seconds ) \
  ((INTEGER)(Seconds>CfTIME_MaxSecToR15p625ms16_DIFF)?(INTEGER)32767: \
   ((INTEGER)(Seconds<CfTIME_MinSecToR15p625ms16_DIFF)?(INTEGER)-32768: \
   (INTEGER) (Seconds*CfTIME_SecToR15p625msSclr_DIFF)))

#define C_R15p625ms16_msec_DIFF( MSeconds ) \
  ((INTEGER)(MSeconds>CfTIME_MaxMSecToR15p625ms16_DIFF)?(INTEGER)32767: \
   ((INTEGER)(MSeconds<CfTIME_MinMSecToR15p625ms16_DIFF)?(INTEGER) -32768: \
   (INTEGER) (MSeconds*CfTIME_MSecToR15p625msSclr_DIFF)))

/*
 * convert real-life units (in seconds) to 31.25ms precision timers
 */

#define C_R31p25ms8( Seconds ) \
  ((BYTE) (Seconds>CfTIME_MaxSecToR31p25ms8)?(BYTE) 255: \
   (BYTE) (Seconds*CfTIME_SecToR31p25msSclr))

#define C_R31p25ms16( Seconds ) \
  ((WORD) (Seconds>CfTIME_MaxSecToR31p25ms16)?(WORD) 65535: \
   (WORD) (Seconds*CfTIME_SecToR31p25msSclr))

/*
 * convert real-life units (in seconds) to 62.5 ms precision timers
 */
#define C_R62p5ms8( Seconds ) \
  ((BYTE) (Seconds>CfTIME_MaxSecToR62p5ms8)?(BYTE) 255: \
   (BYTE) (Seconds*CfTIME_SecToR62p5msSclr))
#define C_R62p5ms16( Seconds ) \
  ((WORD)(Seconds>CfTIME_MaxSecToR62p5ms16)?(WORD)65535: \
   (WORD) (Seconds*CfTIME_SecToR62p5msSclr))

/*
 * convert real-life units (in seconds) to 125 ms precision timers
 */

#define C_R125ms8( Seconds ) \
  ((BYTE) (Seconds>CfTIME_MaxSecToR125ms8)?(BYTE) 255:\
   (BYTE) (Seconds*CfTIME_SecToR125msSclr))

#define C_R125ms16( Seconds ) \
  ((WORD)(Seconds>CfTIME_MaxSecToR125ms16)?(WORD)65535:\
   (WORD) (Seconds*CfTIME_SecToR125msSclr))

/*
 * convert real-life units (in seconds) to 250 ms precision timers
 */

#define C_R250ms8( Seconds ) \
  ((BYTE) (Seconds>CfTIME_MaxSecToR250ms8)?(BYTE) 255:\
   (BYTE) (Seconds*CfTIME_SecToR250msSclr))

#define C_R250ms16( Seconds ) \
  ((WORD) (Seconds>CfTIME_MaxSecToR250ms16)?(WORD) 65535:\
   (WORD) (Seconds*CfTIME_SecToR250msSclr))



/*
 * convert real-life units (in seconds) to 500 ms precision timers
 */

#define C_R500ms8( Seconds ) \
  ((BYTE) (Seconds>CfTIME_MaxSecToR500ms8)?(BYTE) 255:\
   (BYTE) (Seconds*CfTIME_SecToR500msSclr))

#define C_R500ms16( Seconds ) \
  ((WORD) (Seconds>CfTIME_MaxSecToR500ms16)?(WORD) 65535:\
   (WORD) (Seconds*CfTIME_SecToR500msSclr))


/*
 * convert real-life units (in seconds) to 1000 ms precision timers
 */

#define C_R1000ms8( Seconds ) \
  ((BYTE) (Seconds>CfTIME_MaxSecToR1000ms8)?(BYTE)255:\
   (BYTE) (Seconds*CfTIME_SecToR1000msSclr))

#define C_R1000ms16( Seconds ) \
  ((WORD)(Seconds>CfTIME_MaxSecToR1000ms16)?(WORD)65535:\
   (WORD) (Seconds*CfTIME_SecToR1000msSclr))

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.1   960417 l.q      Created module.
* 1.3   960910 l.q      Added 7.8125 ms timer functions
* 1.4   961004 l.q      Added 31.25 ms timer and 500 ms timer functions
*
* -- Core Revision History: --
*
* 1.3   981203 arr 0098 Added 16-bit mathlib scaling integer for timers.
* 1.4   990205 arr 0149 Merged in LECC node 375 containing the following
*                       change(s):
*       981001 mhb 0471 Added 16-bit mathlib scaling integer for
*                       timers. This was needed to calculate the slope in the
*                       evpd logic.
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
* 1.2   001206 gps 0901 Upgrade Math Library to 3.8f.
*                       Corrected include section - removed include mathlib.h.
* 1.3   020711 rmn 1423 Added new types TyTIME_t_R7p81ms and TwTIME_t_R7p81ms
* 1.4   021029 kan 2027 Transmission software merge.
* ----- ------ --- ---- -------------------------------------------------------
* 5.1.1 060104 mt  5479 Added TwTime_t_R0p12207ms datatype.
* 6     051215 hdb 5378 New EOSD Parameters for CAN service ID $06
*                          Add C_R7p8125ms16_msec
* 6.2   060601  mt 5303 Added TyTIME_t_R250ms datatype.
* 6.2.1.1
*       070321 teg 5908 Added signed C_R7p8125ms16_DIFF macro
*                       Added TwTIME_t_R7p8125ms_DIFF type
* 6.2.2.1
*       070416 hdb 6262 Add C_R0p12207ms16_msec
* 7     070515 hdb      merge timepcvc.h-6.2.2.1 with timepcvc.h-6.2.1.1
* tci_pt3#8
*       090515 mtc 7459 QAC Rule Fix 10.1, Subrule: 3759.
* tci_pt3#7.5.1
*       090518  ng 7459 QAC Fix: Type casted C_R62p5ms16, C_R125ms16 and
*                       C_R15p625ms16
* tci_pt3#9
*       091013  ng -BM- Merged 'timepcvc.h~tci_pt3#8'
*                       with 'timepcvc.h~tci_pt3#7.2.1'.
* kok_pt2#10
*       101011  mt 9137 Added CyTIME_MaxCnts8 and CwTIME_MaxCnts16
* 
******************************************************************************/