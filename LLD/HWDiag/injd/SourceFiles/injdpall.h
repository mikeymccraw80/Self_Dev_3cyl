#ifndef INJDPALL_H
#define INJDPALL_H
/*****************************************************************************
* Filename:             injdpall.h
*                                                                           
* Description:		This is the public header file for Injector Circuit
*                       Fault Diagnostic
*
* List of Function 
*         Prototypes:   InitINJD_RstToKeyOn()
*                       InitINJD_OFVC_Clear()
*                       MngINJD_125msTasks()
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

/*****************************************************************************
 *  GMPT Library Include Files
 *****************************************************************************/
#include "timclib.h"  /* timer declaration functions */

/******************************************************************************
*  Control Algorithm Include Files
******************************************************************************/
#include "dgdmpall.h"

/******************************************************************************
*  Enumeration Declaration
******************************************************************************/

/***************************************************************************** 
*  Type declaration
******************************************************************************/
typedef enum
{
  CeINJD_InjCircuit1_FaultTimer,
  CeINJD_InjCircuit2_FaultTimer,
  CeINJD_InjCircuit3_FaultTimer,
  CeINJD_InjCircuit4_FaultTimer,
  CeINJD_InjCircuit5_FaultTimer,
  CeINJD_InjCircuit6_FaultTimer,
  CeINJD_125msNmbrOfTimers
};

DclrTIMC_StopWatches8(VaINJD_t_125TimerArray, VaINJD_125TimerEnbl,
		       R125ms, CeINJD_125msNmbrOfTimers);
/*****************************************************************************
 *  Variable Exports
 *****************************************************************************/
extern TbBOOLEAN VaINJD_FailCriteriaMet[CcSYST_NUM_OF_INJECTORS];
extern TbBOOLEAN VbINJD_CircuitsHW_ResetReq;
extern TbBOOLEAN VbINJD_InjectorsAllFaulted;

/*****************************************************************************
 *  Function Exports
 *****************************************************************************/
static inline TbBOOLEAN GetINJD_FailCriteriaMet (BYTE LcINJD_InjectorCount)
{
  return VaINJD_FailCriteriaMet[LcINJD_InjectorCount];
}

static inline TbBOOLEAN GetINJD_CircuitsHW_ResetReq (void)
{
  return VbINJD_CircuitsHW_ResetReq;
}

static inline TbBOOLEAN GetINJD_InjectorsAllFaulted (void)
{
  return VbINJD_InjectorsAllFaulted;
}



/*****************************************************************************
*
******************************************************************************/
#endif

