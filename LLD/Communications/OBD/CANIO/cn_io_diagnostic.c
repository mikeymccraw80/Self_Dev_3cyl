/******************************************************************************
 *
 * Filename:          cn_io_diagnostic.c
 *
 * Description:       This file contains CAN Diagnostics Handler Implementation
 *
 * Global Functions Defined:
 *                    
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * Forward Engine Management Systems
 *
 * Copyright 2009, Delphi Technologies, Inc.
 * All rights reserved.
 *
 *****************************************************************************/

//=============================================================================
// Include Files
//=============================================================================
#define XbCNIO_FEXI_INCLUDE_HAL_CAN

#include "cn_io_diagnostic.h"

#include "dd_flexcan_error.h"

bool CAN_message_length_mismatch_flag;
//=============================================================================
// Name: GetCANH_ACKMissing
//
// Description: This function returns if ACK is missing
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
TbBOOLEAN GetCANH_ACKMissing(void)
{
   return (TbBOOLEAN)FlexCAN_Get_Error_Status(FLEXCAN_DEVICE_A,FLEXCAN_ERROR_CHANNEL_ACKERR);
}
//=============================================================================
// Name: GetCANH_PassiveState
//
// Description: This function returns if CAN is in passive state
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
TbBOOLEAN GetCANH_PassiveState(void)
{
   return (TbBOOLEAN)(FlexCAN_Get_Fault_Confinement_State(FLEXCAN_DEVICE_A)==FLEXCAN_FLT_CONF_ERR_PASSTIVE);
}
//=============================================================================
// Name: DisableCANH_NetWork_Send
//
// Description: This function disables the can network
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
void DisableCANH_NetWork_Send(void)
{
   FlexCAN_Enable_Device(FLEXCAN_DEVICE_A,false);
}
//=============================================================================
// Name: EnableCANH_NetWork_Send
//
// Description: This function enables the can network
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
void EnableCANH_NetWork_Send(void)
{
   FlexCAN_Enable_Device(FLEXCAN_DEVICE_A,true);
}
//=============================================================================
// Name: GetCANH_BusOff_Status
//
// Description: This function returns the can bus off status
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
TbBOOLEAN GetCANH_BusOff_Status(void)
{
   return (TbBOOLEAN)(FlexCAN_Get_Fault_Confinement_State(FLEXCAN_DEVICE_A)==FLEXCAN_FLT_CONF_ERR_BUSOFF);
}
//=============================================================================
// Name: SetCANH_BusOff_Reset
//
// Description: This function enables the can bus off reset
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
void SetCANH_BusOff_Reset(void)
{
   FlexCAN_Set_Busoff_Recovery_Auto_Enable(FLEXCAN_DEVICE_A,true);
   FlexCAN_Set_Busoff_Recovery_Auto_Enable(FLEXCAN_DEVICE_A,false);
}
//=============================================================================
// Name: GetCANH_Rx_Error_Counter
//
// Description: This function gets the rx error counter of CAN
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
uint8_t GetCANH_Rx_Error_Counter(void)
{
   FlexCAN_Get_Rx_Error_Counter(FLEXCAN_DEVICE_A);
}
//=============================================================================
// Name: GetCANH_Tx_Error_Counter
//
// Description: This function gets the tx error counter of CAN
//
// Parameters: none
//
// Return Value: none
//
// Shared Variables: none
//
// Assumptions/Preconditions: none
//
// Design Information: none
//
//=============================================================================
uint8_t GetCANH_Tx_Error_Counter(void)
{
   FlexCAN_Get_Tx_Error_Counter(FLEXCAN_DEVICE_A);
}




/******************************************************************************
* REVISION HISTORY:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1     090416 yrw xxxx Initial version
******************************************************************************/
