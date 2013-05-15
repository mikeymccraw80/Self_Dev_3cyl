#ifndef OBDSFCFG_H
#define OBDSFCFG_H
/******************************************************************************
 *
 * Filename:          obdsfcfg.h
 *
 * Description:       Main configuration header file for OBD subsystem.
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
 * Copyright 2008, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

/******************************************************************************
 *  Global Data Type Include File
 *****************************************************************************/
#include "t_gentypes.h"  /* For CbSUBS_ON  */
                         /*     CbSUBS_OFF */

/******************************************************************************
 *  xxxx module Section
 *****************************************************************************/

/******************************************************************************
 *  Generic defines which can be used for any option.
 *  (Assign one of the following values to XeSYST_define_of_your_choice)
 *****************************************************************************/
#define CeSYST_NOT_AVAILABLE                  0
#define CeSYST_AVAILABLE                      1


/******************************************************************************
 *  OBD Communication Configuration Types
 *  (Assign one of the following values to XeSYST_OBD_CommunicationType)
 *  (Assign one of the following values to XeSYST_OBD_LegislatedSrvs)
 *  (List new assignments as they are used.
 *****************************************************************************/
#define CeSYST_OBD_OVER_CAN                   0
#define CeSYST_OBD_OVER_KW2K                  1
#define CeSYST_INVALID                        2


/******************************************************************************
 *  Serial Data Section
 *  (Assign one or more of the following values to XeSYST_SERIAL_DATA_XXXXX)
 *****************************************************************************/
#define CeSYST_SERIAL_DATA_NOT_PRESENT        0x0000
#define CeSYST_SERIAL_DATA_CAN_PRESENT        0x0001
#define CeSYST_SERIAL_DATA_CAN_DAEWOO         0x0003
#define CeSYST_SERIAL_DATA_CAN_ISUZU          0x0005
#define CeSYST_SERIAL_DATA_CAN_ECM_HYUNDAI    0x0009
#define CeSYST_SERIAL_DATA_CAN_PCM_HYUNDAI    0x0011
#define CeSYST_SERIAL_DATA_CAN_CEC            0x0021
#define CeSYST_SERIAL_DATA_CLASS2_PRESENT     0x0001
#define CeSYST_SERIAL_DATA_KW2K_PRESENT       0x0001
#define CeSYST_SERIAL_DATA_KW2K_DAEWOO        0x0003
#define CeSYST_SERIAL_DATA_KW2K_HYUNDAI       0x0005

/******************************************************************************
 *  Serial Data Availability Selection (user configurable)
 *****************************************************************************/
#define XeSYST_SERIAL_DATA_CAN    CeSYST_SERIAL_DATA_CAN_PRESENT//CeSYST_SERIAL_DATA_CAN_PCM_HYUNDAI
#define XeSYST_SERIAL_DATA_CLASS2 CeSYST_SERIAL_DATA_NOT_PRESENT
#define XeSYST_SERIAL_DATA_KW2K   CeSYST_SERIAL_DATA_KW2K_PRESENT

/******************************************************************************
 *  OBD Protocol Type
 *****************************************************************************/
#define XeSYST_OBD_CommunicationType CeSYST_OBD_OVER_KW2K

#define XeSYST_OBD_LegislatedSrvs CeSYST_OBD_OVER_CAN

#define XeSYST_CANOBD_SrvsEnable  CeSYST_AVAILABLE

#define XeSYST_KW2KOBD_SrvsEnable  CeSYST_AVAILABLE

#define XeSYST_CANOBD_NonLegislatedSrvs CeSYST_AVAILABLE


/******************************************************************************
 *  Controller Type Section
 *****************************************************************************/
#define CeOBDS_SYST_CONTROLLER_IS_MT80        0x00
#define CeOBDS_SYST_CONTROLLER_IS_MT92        0x01
#define CeOBDS_SYST_CONTROLLER_IS_MT22p1      0x02

#define XeOBDS_SYST_CONTROLLER_DIAG_TYPE      CeOBDS_SYST_CONTROLLER_IS_MT22p1    


#endif /* OBDSFCFG_H */

/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     100728 hdg ---- Initial version
******************************************************************************/

