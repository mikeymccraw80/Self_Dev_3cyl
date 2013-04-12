/********************************************************************************
*  Filename:              timclib.h
*
*  Description:           Contains stopwatch timer functions which are used by
*                         external subsystems.
*
*  List of inlines:
*
*
*  List of finuctions:
*
*
*  C Software Project Forward EMS
* (c) Copyright Delco Electronics    1996
*********************************************************************************/

#ifndef TIMCLIB
#define TIMCLIB

#include "t_base.h"
#include "bit_lib.h"
#include "timepcvc.h"

/***********************************************************************
 *                                                                     *
 *  These are macros which are used exclusively within this module.    *
 *  They are not supported by use from any other subsystem.            *
 *                                                                     *
 ***********************************************************************/
/*
 * "paste" function.
 */
#define _cat(x,y) x##y
#define _xcat(x,y) _cat(x,y)


/*
 * Assemble the requested timer data type.
 */
#define _GetTimxType16(WP) \
  _xcat(TwTIME_t_,WP)
#define _GetTimxType8(WP) \
  _xcat(TyTIME_t_,WP)


#define MINBYTE            0
#define MAXBYTE            255

#define MINWORD            0L
#define MAXWORD            65535L

/***********************************************************************
 *                                                                     *
 *  These are prototypes to private functions.                         *
 *                                                                     *
 ***********************************************************************/
void @far UpdateTIMC_StopWatchesUp16(WORD *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                 WORD LwTIMC_Size);

void @far UpdateTIMC_StopWatchesDown16(WORD *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                   WORD LwTIMC_Size) ;

void @far UpdateTIMC_StopWatchesUp8(BYTE *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                WORD LwTIMC_Size);

void @far UpdateTIMC_StopWatchesDown8(BYTE *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                  WORD LwTIMC_Size);

/***********************************************************************
 *                                                                     *
 *  Beginning of external functions.                                   *
 *                                                                     *
 ***********************************************************************/

/*
 * Declare functions:
 *
 *                    Declare or define stopwatch timer arrays or
 *                    associated bit flag arrays.
 *
 * PUBLIC
 */
#define DclrTIMC_StopWatches16(TmrName, EnblName, WhichPrec, Size) \
extern _GetTimxType16(WhichPrec)  TmrName[Size]; \
extern DclrBIT_Arry(EnblName, (int)Size)

#define DefTIMC_StopWatches16(TmrName, EnblName, WhichPrec, Size) \
_GetTimxType16(WhichPrec)  TmrName[Size]; \
DclrBIT_Arry(EnblName, (int)Size)

#define DclrTIMC_StopWatches8(TmrName, EnblName, WhichPrec, Size) \
extern _GetTimxType8(WhichPrec) TmrName[Size]; \
extern DclrBIT_Arry(EnblName, (int)Size)

#define DefTIMC_StopWatches8(TmrName, EnblName, WhichPrec, Size) \
_GetTimxType8(WhichPrec)  TmrName[Size]; \
DclrBIT_Arry(EnblName, (int)Size)

#define DefTIMC_StopWatches16Static(TmrName, EnblName, WhichPrec, Size) \
static _GetTimxType16(WhichPrec)  TmrName[Size]; \
static DclrBIT_Arry(EnblName, (int)Size)

#define DefTIMC_StopWatches8Static(TmrName, EnblName, WhichPrec, Size) \
static _GetTimxType8(WhichPrec)  TmrName[Size]; \
static DclrBIT_Arry(EnblName, (int)Size)


/*
 * HaltTIMC_StopWatch():   Called by a subsystem to stop a
 *                         timer from incrementing
 *
 * PUBLIC
 */
#define HaltTIMC_StopWatch(EnblName, WhichTmr) \
ClrBIT_InArry(EnblName, WhichTmr)

/*
 * ResumeTIMC_StopWatch():   Called by a subsystem to start
 *                           incrementing a timer without
 *                           first initializing the value
 *                           of the timer
 *
 * PUBLIC
 */
#define ResumeTIMC_StopWatch(EnblName, WhichTmr) \
SetBIT_InArry(EnblName, WhichTmr)

/*
 * GetTIMC_StopWatchState():  Return true if the stopwatch is
 *                            running
 *
 * PUBLIC
 */
#define GetTIMC_StopWatchState(EnblName, WhichTmr) \
GetBIT_InArry(EnblName, WhichTmr)

/*
 * StartTIMC_StopWatch(): Called by a subsystem to
 *                       set a timer to the input value
 *                       and begin incrementing
 *
 * PUBLIC
 */
#define StartTIMC_StopWatch8(TmrName, EnblName, WhichTmr, Val) \
TmrName[WhichTmr] = (BYTE)Val; \
SetBIT_InArry(EnblName, WhichTmr)
#define StartTIMC_StopWatch16(TmrName, EnblName, WhichTmr, Val) \
TmrName[WhichTmr] = (WORD)Val; \
SetBIT_InArry(EnblName, WhichTmr)

/*
 * GetTIMC_t_StopWatch(): Called by a subsystem to get the
 *                          current value of a timer
 *
 * PUBLIC
 */
#define GetTIMC_t_StopWatch8(TmrName, WhichTmr) \
(BYTE)TmrName[WhichTmr]
#define GetTIMC_t_StopWatch16(TmrName, WhichTmr) \
(WORD)TmrName[WhichTmr]

/*
 * SetTIMC_StopWatch():  Called by a subsystem to
 *                       set a timer to the input value;
 *                       this function does not begin
 *                       incrementing
 *
 * PUBLIC
 */
#define SetTIMC_StopWatch8(TmrName, WhichTmr, Val) \
TmrName[WhichTmr] = (BYTE)Val
#define SetTIMC_StopWatch16(TmrName, WhichTmr, Val) \
TmrName[WhichTmr] = (WORD)Val

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.4   971104 blt 0249 API cleanup
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
*
* 21/12/05     LShoujun    mt20u2#38(SCR)
* + Rearrangement for calibration location
*   - defined the functions called out of this file to "@far"
*
******************************************************************************/
/*
* $Source: common@brighton.tcb:core_dc2:timclib.h $
* $Revision: 1.1 $
* $Author: brighton.tcb:/users/mrwoznic/dsds/core_dc2:mrwoznic $
*/

