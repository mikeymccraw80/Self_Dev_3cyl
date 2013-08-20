//=============================================================================
//
//       COPYRIGHT, 2003, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_vsep_config.c %
//
// created_by:       fz3pdz
//
// date_created:     Tue Mar 22 12:40:49 2005
//
// %derived_by:      nz45s2 %
//
// %date_modified:   Mon Mar  7 18:18:29 2011 %
//
// %version:         15.1.2.1.1.3.2 %
//
// ============================================================================
//
// SPECIFICATION REVISION:
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

//=============================================================================
// Include the spi port
//=============================================================================
#include "dd_vsep.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_deps.h"
#include "io_config_vsep.h"
#include "dd_vsep_discrete_interface.h"
#include "io_config_spi.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_led.h"
#include "dd_vsep_init_config.h"

#define DISCRETE_OUT_VSEP_CSS 0x00

//=============================================================================
// VSEP EST Fault Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_EST_FAULT_MESSAGE_DEFINITION =
{
    VSEP_EST_Fault_Rxd,
    VSEP_EST_Fault_Txd,
    VSEP_EST_FAULT_RXD_MESSAGE_MAX,
    VSEP_EST_FAULT_TXD_MESSAGE_MAX,      
};

//=============================================================================
// VSEP Fault Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_FAULT_MESSAGE_DEFINITION =
{
    VSEP_Fault_Rxd,
    (void*)VSEP_FAULT_TXD,
    VSEP_FAULT_RXD_MESSAGE_MAX,
    VSEP_FAULT_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP INIT Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_INIT_MESSAGE_DEFINITION =
{
    NULL,//
    VSEP_INIT_TXD_INITIAL,
    0,
    VSEP_INIT_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP PCH Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_PCH_MESSAGE_DEFINITION =
{
    VSEP_PCH_Rxd,
    VSEP_PCH_Txd,
    VSEP_PCH_RXD_MESSAGE_MAX,
    VSEP_PCH_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP PWM Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_PWM_MESSAGE_DEFINITION[ VSEP_PWM_CHANNEL_MAX ] =
{
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[VSEP_PWM_CHANNEL_1],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_2 ],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_3 ],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_4 ],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_5 ],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_6 ],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_7 ],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_8],
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    }
};

//=============================================================================
// VSEP SOH Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_SOH_MESSAGE_DEFINITION =
{
    VSEP_SOH_Rxd,
    VSEP_SOH_Txd,
    VSEP_SOH_RXD_MESSAGE_MAX,
    VSEP_SOH_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP SOH Status Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_SOH_STATUS_MESSAGE_DEFINITION =
{
    VSEP_SOH_Status_Rxd,
    (void *)VSEP_SOH_STATUS_TXD,
    VSEP_SOH_STATUS_RXD_MESSAGE_MAX,
    VSEP_SOH_STATUS_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP LEDMODE Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_LEDMODE_MESSAGE_DEFINITION =
{
    NULL,
    VSEP_LEDMODE_Txd,
    0,
    VSEP_LEDMODE_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP VR Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_VR_MESSAGE_DEFINITION =
{
    VSEP_VR_Rxd,
    VSEP_VR_Txd,
    VSEP_VR_RXD_MESSAGE_MAX,
    VSEP_VR_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP DEPS Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_DEPS_MESSAGE_DEFINITION =
{
    VSEP_DEPS_Rxd,
    VSEP_DEPS_Txd,
    VSEP_DEPS_RXD_MESSAGE_MAX,
    VSEP_DEPS_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP EST Select Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_EST_SELECT_MESSAGE_DEFINITION =
{
    VSEP_EST_Select_Rxd,
    VSEP_EST_Select_Txd,
    VSEP_EST_SELECT_RXD_MESSAGE_MAX,
    VSEP_EST_SELECT_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP MPIO MODE Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_MPIO_MODE_MESSAGE_DEFINITION =
{
    NULL,
    VSEP_MPIO_MODE_Txd,
    0,
    VSEP_MPIO_MODE_TXD_MESSAGE_MAX
};

//=============================================================================
// VSEP Message
//=============================================================================
const SPI_Message_Definition_T * VSEP_MESSAGE[VSEP_MESSAGE_MAX+7] =
{
    &VSEP_INIT_MESSAGE_DEFINITION                   ,  //VSEP_MESSAGE_INIT
    &VSEP_VR_MESSAGE_DEFINITION                     ,  //VSEP_MESSAGE_VR
    &VSEP_DEPS_MESSAGE_DEFINITION                   ,  //VSEP_MESSAGE_DEPS
    &VSEP_LEDMODE_MESSAGE_DEFINITION                ,  //VSEP_MESSAGE_LEMODE
    &VSEP_PCH_MESSAGE_DEFINITION                    ,  //VSEP_MESSAGE_PCH_MPIO
    &VSEP_EST_SELECT_MESSAGE_DEFINITION             ,  //VSEP_MESSAGE_EST_SELECT
    &VSEP_EST_FAULT_MESSAGE_DEFINITION              ,  //VSEP_MESSAGE_EST_FAULT
    &VSEP_SOH_MESSAGE_DEFINITION                    ,  //VSEP_MESSAGE_SOH
    &VSEP_SOH_STATUS_MESSAGE_DEFINITION             ,  //VSEP_MESSAGE_SOH_STATUS
    &VSEP_FAULT_MESSAGE_DEFINITION                  ,  //VSEP_MESSAGE_FAULT
    &VSEP_MPIO_MODE_MESSAGE_DEFINITION              ,   //VSEP_MESSAGE_MPIO_MODE
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_1],  //VSEP_MESSAGE_PWM_1
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_2],  //VSEP_MESSAGE_PWM_2
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_3],  //VSEP_MESSAGE_PWM_3
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_4],  //VSEP_MESSAGE_PWM_4
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_5],  //VSEP_MESSAGE_PWM_5
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_6],  //VSEP_MESSAGE_PWM_6
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_7],  //VSEP_MESSAGE_PWM_7
    &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_8]   //VSEP_MESSAGE_PWM_8
};


/* return true if channel fault counter reach threshold */
bool VSEP_Is_Channel_Fault_Threshold_Reach(VSEP_Channel_T channel)
{
    return ((VSEP_Fault_Counter[channel] >= KsVSEP_Diagnostic_Counter_Thd) ? true : false);
}

/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       * 
 * 15.1.2.1.1.3.1 110128 nz45s2 mt20u2#809 RSM_CTC_0375_add auto start-stop function in MT22.1_Rev0_20101229
 * 15.1.2.1.1.3.2 20110222 nz45s2 mt20u2#828 RSM_CTC_0340_Support Lin type battery Sensor in MT22p1p1 Stop-Start SW_Rev3_20110114
\*===========================================================================*/
