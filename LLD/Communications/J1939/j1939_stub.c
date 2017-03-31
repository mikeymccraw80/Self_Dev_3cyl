/******************************************************************************
 * Copyright 2008 Delphi Technologies, Inc., All Rights Reserved              *
 * REVISION: 1.0                                                              *
 * AUTHORS: Anupindi Sarma                                                    *
 * File Name: can_stub.c                                                      *
 * File Description:                                                          *
******************************************************************************/
#include "j1939_stub.h"
#include "j1939_app.h"
#include "j1939_pgn_57344.h"
#include "j1939_pgn_00000_ICC.h"
#include "j1939_pgn_00000_TCU.h"
#include "j1939_pgn_64971.h"
#include "j1939_pgn_65265.h"
#include "j1939_pgn_65276.h"
#include "j1939_pgn_65277.h"
#include "j1939_pgn_65278.h"
#include "j1939_pgn_65279.h"
#include "j1939_pgn_65296.h"

CAN_Port_Error_T VfJ1939_BusError;

/*TX Signals*/
/* Rx Signals*/

/* RX 65271 - Standard Vehicle Electrical Power Message. */
static uint8_t stub_SVEPM_NetBatteryCurrent;
static uint8_t stub_SVEPM_AlternatorCurrent;
static uint16_t stub_SVEPM_ChargingSystemPotential;
static uint16_t stub_SVEPM_BatteryPotentialPowerInput1;
static uint16_t stub_SVEPM_KeyswitchBatteryPotential;

/* RX 65276 - Standard Vehicle Dash Display Message. */
static uint8_t stub_SVDDM_WasherFluidLevel;
static uint8_t stub_SVDDM_FuelLevel1;
static uint8_t stub_SVDDM_EngFuelFiltDifferentialPressure;
static uint8_t stub_SVDDM_EngOilFiltDifferentialPressure;
static uint8_t stub_SVDDM_FuelLevel2;
static uint16_t stub_SVDDM_CargoAmbientTemperature;

/* RX 65296 - Remote Activation Message.*/
 static uint8_t stub_RAM_OperatingConditionUpdate;
 static uint8_t stub_RAM_ServiceRequested;
 static uint8_t stub_RAM_DesiredOutputVoltage;

 
//uint8_t stub_index;
 
static void Rx_PGN_65276(void);
static void Rx_PGN_65296(void);

static void Rx_PGN_57344(void)
{
 if(true == J1939_Get_PGN_57344_Message_Indicator())
 {
   J1939_Clear_PGN_57344_Message_Indicator();
 }
}

static void Rx_PGN_00000_ICC(void)
{
 if(true == J1939_Get_PGN_00000_Message_Indicator_ICC())
 {
   J1939_Clear_PGN_00000_Message_Indicator_ICC();
 }
}

static void Rx_PGN_00000_TCU(void)
{
 if(true == J1939_Get_PGN_00000_Message_Indicator_TCU())
 {
   J1939_Clear_PGN_00000_Message_Indicator_TCU();
 }
}

static void Rx_PGN_65265(void)
{
 if(true == J1939_Get_PGN_65265_Message_Indicator())
 {
   J1939_Clear_PGN_65265_Message_Indicator();
 }
}

static void Rx_PGN_64971(void)
{
 if(true == J1939_Get_PGN_64971_Message_Indicator())
 {
   J1939_Clear_PGN_64971_Message_Indicator();
 }
}

static void Rx_PGN_65276(void)
{
 if(true == J1939_Get_PGN_65276_Message_Indicator())
 {
   stub_SVDDM_FuelLevel1 = AIFGetFuel_Level_1();    
   stub_SVDDM_EngFuelFiltDifferentialPressure = AIFGetEngine_Fuel_Filt_Diff_Pressure();    
   stub_SVDDM_EngOilFiltDifferentialPressure = AIFGetEngine_Oil_Filt_Diff_Pressure();    
   stub_SVDDM_FuelLevel2 = AIFGetFuel_Level_2();    
   stub_SVDDM_WasherFluidLevel = AIFGetWasher_Fluid_Level();    
   stub_SVDDM_CargoAmbientTemperature = AIFGetCargo_Ambient_Temperature();
   J1939_Clear_PGN_65276_Message_Indicator();
 }
}

static void Rx_PGN_65277(void)
{
 if(true == J1939_Get_PGN_65277_Message_Indicator())
 {
   J1939_Clear_PGN_65277_Message_Indicator();
 }
}

static void Rx_PGN_65278(void)
{
 if(true == J1939_Get_PGN_65278_Message_Indicator())
 {
   J1939_Clear_PGN_65278_Message_Indicator();
 }
}

static void Rx_PGN_65279(void)
{
 if(true == J1939_Get_PGN_65279_Message_Indicator())
 {
   J1939_Clear_PGN_65279_Message_Indicator();
 }
}

static void Rx_PGN_65296(void)
{
 if(true == J1939_Get_PGN_65296_Message_Indicator())
 {
   stub_RAM_DesiredOutputVoltage = AIFGetDesired_Output_Voltage();    
   stub_RAM_OperatingConditionUpdate = AIFGetOperating_Cond_Update();    
   stub_RAM_ServiceRequested = AIFGetService_Requested();    

   J1939_Clear_PGN_65296_Message_Indicator();
 }
}



void J1939_Transmit_Test_Task(void)
{

}


void J1939_Receive_Test_Task(void)
{
   VfJ1939_BusError = J1939_Get_BusOffState();
   Rx_PGN_57344();
   Rx_PGN_00000_ICC();
   Rx_PGN_00000_TCU();
   Rx_PGN_65265();
   Rx_PGN_64971();
   Rx_PGN_65276();
   Rx_PGN_65277();
   Rx_PGN_65278();
   Rx_PGN_65279();
   Rx_PGN_65296();
}

/******************************************************************************
*                        REVISION HISTORY                                     *
*******************************************************************************
* Rev      Date          S/W Engineer          Description                    *
* ===     ============  ================      ====================            *
* 1        10/19/2011    Arpit, Anupindi       SOFC J1939 first release.      *
******************************************************************************/
