#ifndef ESTDPALL_H
#define ESTDPALL_H
/*****************************************************************************
* Filename:             estdpall.h
*                                                                           
* Description:		This is the public header file for EST Fault 
*                       Diagnostics
*
* List of Function 
*         Prototypes:   InitINJD_RstToKeyOn()
*                       InitINJD_OFVC_Clear()
*                       MngINJD_RefEventTasks()
*
* List of Inlines:      None
*
* C Software Project Forward EMS
* (c) Copyright Delco Electronics  1997
******************************************************************************/

/*****************************************************************************
 *  Global Data Type Include Files 
 *****************************************************************************/
#include "t_base.h"     
#include "t_fixed.h"
#include "t_scaled.h"
#include "t_tables.h"
#include "t_user.h"
#include "timclib.h"

/*****************************************************************************
 *  GMPT Library Include Files
 *****************************************************************************/

/******************************************************************************
*  Control Algorithm Include Files
******************************************************************************/
#include "dgdmpall.h"

/******************************************************************************
*  Type declaration
*****************************************************************************/
enum /* ESTD steady state timers */
{
  CeESTD_FaultEnblDlyTmr,
  CcESTD_Num7p8Tmrs
};

DclrTIMC_StopWatches16(VaESTD_t_7p8msTimerArray, VaESTD_7p8msTimerEnbl,
                       R7p8125ms, CcESTD_Num7p8Tmrs) ;

/******************************************************************************
*  Constant defines
******************************************************************************/
/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/
extern TbBOOLEAN VaESTD_FailCriteriaMet[CcSYST_NUM_OF_EST_OUTPUTS];

/*****************************************************************************
 *  Function Prototype
 *****************************************************************************/


#endif
/*****************************************************************************
*
******************************************************************************

