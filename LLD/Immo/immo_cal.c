/* ============================================================================ *\
 * v_immo.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       immo_cal.c-2:csrc:mt20a#1
 * Revision:        2
 * Creation date:   Tuesday, June 18, 2002 4:50:08 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the immobilizer calibration.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "io_type.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "immo_cal.h"


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define macros.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local type declarations.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */

/*---------------------------------------------*\
 *--- Number  ---*
\*---------------------------------------------*/
const Immo_Option_T K_Immo_option = CeImmo_STEC;
/*
*|immo_cal. {
*|    K_Immo_option
*|    {
*|       :is_calconst;
*|       :units = "Immo_Option_T";
*|       :description = "0- no immobilizer 1: Siemens Immobilizer.";
*|    }
*/

const FuelPump_Channel_T K_Immo_FuelPump_channel = CeFuelPumpPin;
/*
*|    K_Immo_FuelPump_channel
*|    {
*|       :is_calconst;
*|       :units = "FuelPump_Channel_T";
*|       :description = "Fuel Pump channel selection in Immobiliser application";
*|    }
*/

const Every_Loop_Sec_B K_SingleAuthenticationMaxTime = FixDefConst( 0.110, Every_Loop_Sec_B );
/*
*|    K_SingleAuthenticationMaxTime
*|    {
*|       :is_calconst;
*|       :type = types.Every_Loop_Sec_B;
*|       :units = "Seconds";
*|       :description = "Immobilizer Single Authentication Max Time";
*|    }
*/



const Every_Loop_Sec_W K_ImmoAuthenticationClearTime  = FixDefConst (0.125, Every_Loop_Sec_W);
/*
*|    K_ImmoAuthenticationClearTime
*|    {
*|       :is_calconst;
*|       :type = types.Every_Loop_Sec_W;
*|       :units = "Seconds";
*|       :description = "Immo re-activation period since Ignition Off ";
*|    }
*/

const EOBD_KPH K_ImmoByPassVSS = FixDefConst (15.0, EOBD_KPH );
/*
*|     K_ImmoByPassVSS
*|     {
*|         : is_calconst;
*|         : type = types.EOBD_KPH;
*|         : units = "KPH";
*|         : description = "Calibration of Vehicle Speed (km) to bypass Immo authentication result";
*|     }
*/

const Every_16th_Loop_Sec_W  K_ImmoNoAuthLimit = FixDefConst (10.0, Every_16th_Loop_Sec_W ) ;
/*
*|     K_ImmoNoAuthLimit
*|     {
*|         : is_calconst;
*|         : type = types.Every_16th_Loop_Sec_W;
*|         : units = "Seconds";
*|         : description = "the Max Engine Enable time without Immo authentication Pass ";
*|     }
*/

const uint8_t  KcMyImmoSourceAddr = 0xC1 ;
/*
*|     KcMyImmoSourceAddr
*|     {
*|         : is_calconst;
*|         : type = types.uint8_t;
*|         : units = "HEX";
*|         : description = "immo source address ";
*|     }
*/

const uint16_t KwIMMO_SiemensPreReleaseTime = 180;
/*
*|    KwIMMO_SiemensPreReleaseTime
*|    {
*|       :is_calconst;
*|       : type = types.uint16_t;
*|       :units = "count";
*|       :description = "Pre-Release time of Siemens immobilizer (default: 1.8s). Note: it should not be greater than 512 (4s)";
*|    }
*/

const Every_Loop_Sec_W K_Immo_ECMDelayTime  = FixDefConst (0.9375, Every_Loop_Sec_W);
/*
*|    K_Immo_ECMDelayTime
*|    {
*|       :is_calconst;
*|       :type = types.Every_Loop_Sec_W;
*|       :units = "Seconds";
*|       :description = "ECM Learned Delay Time ";
*|    }
*/

const uint8_t KaIMMO_CustomerID[4] = {0x53, 0x54, 0x45, 0x43};
/*
*|     KaIMMO_CustomerID
*|     {
*|         : is_calconst;
*|         : type = types.uint8_t;
*|         : units = "HEX";
*|         : description = "the Siemens Immobilizer and Brilliance Immobilizer use the customer ID, please get the value from customer before change the KaIMMO_CustomerID ";
*|     }
*|  }
*/

/* ============================================================================ *\
 * Local variables.
\* ============================================================================ */
/*  none */


/* ============================================================================ *\
 * Local function prototypes.
\* ============================================================================ */




/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 
 * 
\* ============================================================================ */
