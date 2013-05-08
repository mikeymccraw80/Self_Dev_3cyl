/*****************************************************************************
* Filename:                   injdcald.c
*
* Description:                Calibration file for Injector Circuits
*                             Diagnostic subsystem
*
* List of functions:
*
* List of inlines:
*
* C Software Project FORWARD EMS
* (c) Copyright Delco Electronics  1997
*****************************************************************************/


/******************************************************************************
*  Include Files
*****************************************************************************/
#include "injdcald.h"

/*****************************************************************************
 *  GMPT Library Include Files
 *****************************************************************************/

/*****************************************************************************
 *  Global Include Files
 *****************************************************************************/

/*****************************************************************************
 *  Local Include Files
 *****************************************************************************/

/*****************************************************************************
 *  Calibration declaration for Injector Circuits diagnostic module
 *****************************************************************************/
      /* Indicates minimum RPM reqired to enable the injector diagnostics */
      /* Range: V_RPMa(0) to V_RPMa(8000)                                 */
/*
*| injdcald.{
*|   KfINJD_n_EngSpdThrshLo {
*|     : is_calconst;
*|     : description ="Indicates minimum RPM reqired to enable the injector \
diagnostics. Range: V_RPMa(0) to V_RPMa(8000) ";
*|     : type = fixed.injd_t_rpma;
*|     : units = "rpm";
*|   }
*| }
*/
const T_RPMa  KfINJD_n_EngSpdThrshLo = V_RPMa(500);

      /* Indicates how long an injector must indicate a failure before a  */
      /* failure is registered Range: C_R125ms8(0) to C_R125ms8(255)      */
/*
*| injdcald.{
*|   KfINJD_t_InjCircuitFailThrsh {
*|     : is_calconst;
*|     : description ="Indicates how long an injector must indicate a failure \
before a failure is registered. Range: C_R125ms8(0) to C_R125ms8(255) ";
*|     : type = fixed.injd_t_y_R125ms;
*|     : units = "seconds";
*|   }
*| }
*/
const TyTIME_t_R125ms KfINJD_t_InjCircuitFailThrsh = C_R125ms8(3);

/*****************************************************************************
*
******************************************************************************/

