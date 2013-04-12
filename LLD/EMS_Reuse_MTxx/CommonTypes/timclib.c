
/*************************************************************************************
*  Filename:              timclib.c
*
*  Description:          Contains update functions which are used internally by
*                        the LECC project stopwatch timer library.
*
*  List of inlines:
*
*
*  List of finuctions:
*
*
*  C Software Project Forward EMS
* (c) Copyright Delco Electronics    1996
***************************************************************************************/


/*
 * GMPT Control Algorithm Functions Include Files
 */
#include "t_base.h"
#include "t_fixed.h"
#include "t_scaled.h"
#include "bit_lib.h"
#include "timclib.h"


/*
 * MAX function.
 */
#define MAX(a,b) (((a)>(b))?(a):(b))

/*
 * Update functions:
 *
 *                    Update the input stopwatch timers.
 *
 * PRIVATE, called by macros which exist in timclib.h
 *
 */
@far void UpdateTIMC_StopWatchesUp16 ( WORD *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                  WORD LwTIMC_Size )
{
  int i;
  for (i=0; i<LwTIMC_Size; i++)
  {
    if (GetBIT_InArry( LaTIMC_TmrEnbl, i ) )
    {
      if ( LaTIMC_TmrArr [i] < MAXWORD )
      {
        ++LaTIMC_TmrArr [i] ;
      }
    }
  }
}


@far void UpdateTIMC_StopWatchesDown16 ( WORD *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                    WORD LwTIMC_Size)
{
  int i;
  for (i=0; i<LwTIMC_Size; i++)
  {
    if (GetBIT_InArry(LaTIMC_TmrEnbl, i) )
    {
      if (LaTIMC_TmrArr [i]  > MINWORD )
      {
        --LaTIMC_TmrArr [i] ;
      }
    }
  }
}

@far void UpdateTIMC_StopWatchesUp8 ( BYTE *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                 WORD LwTIMC_Size )
{
  int i;
  for (i=0; i<LwTIMC_Size; i++)
  {
    if (GetBIT_InArry(LaTIMC_TmrEnbl, i) )
    {
      if ( LaTIMC_TmrArr [i] < MAXBYTE )
      {
        ++LaTIMC_TmrArr [i] ;
      }
    }
  }
}

@far void UpdateTIMC_StopWatchesDown8 ( BYTE *LaTIMC_TmrArr, BYTE *LaTIMC_TmrEnbl,
                                   WORD LwTIMC_Size )
{
  int i;
  for (i=0; i<LwTIMC_Size; i++)
  {
    if (GetBIT_InArry(LaTIMC_TmrEnbl, i ) )
    {
      if (LaTIMC_TmrArr [i]  > MINBYTE )
      {
        --LaTIMC_TmrArr [i] ;
      }
    }
  }
}


/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
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

