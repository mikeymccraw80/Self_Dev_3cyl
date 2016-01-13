/******************************************************************************
 * Copyright 2008 Delphi Technologies, Inc., All Rights Reserved              *
 * REVISION: 1.0                                                              *
 * AUTHORS: Anupindi Sarma                                                    *
 * File Name: can_stub.c                                                      *
 * File Description:                                                          *
******************************************************************************/
#include "j1939_stub.h"
#include "j1939_app.h"
#include "j1939_pgn_65271.h"
#include "j1939_pgn_65272.h"
#include "j1939_pgn_65273.h"
#include "j1939_pgn_65274.h"
#include "j1939_pgn_65275.h"
#include "j1939_pgn_65276.h"
#include "j1939_pgn_65277.h"
#include "j1939_pgn_65278.h"
#include "j1939_pgn_65279.h"
#include "j1939_pgn_65296.h"

#include "j1939_pgn_65282.h"
#include "j1939_pgn_65283.h"
#include "j1939_pgn_65284.h"

CAN_Port_Error_T VfJ1939_BusError;

/*TX Signals*/

// Function : PGN_65282
//Description : Status Message 1.
static uint8_t  stub_SM1_Mode = 0x03;
static uint8_t  stub_SM1_TimeToDelivery =0x66;
static uint8_t  stub_SM1_TimeToCoolDown = 0x44;
static uint8_t  stub_SM1_OutputVoltage = 0x66;
static uint16_t stub_SM1_PresentOutputPower= 0x00E8;
static uint16_t stub_SM1_MaxOutputPower= 0xA5A5;

// Function : PGN_65283
//Description : Status Message 2.
static uint16_t stub_SM2_InstantaneousFuelConsumption = 0x0055;
static uint16_t stub_SM2_AccumulatedFuelConsumption = 0x1122;
static uint32_t  stub_SM2_HourMeter = 0x00AABBCC;

// Function : PGN_65284
//Description : Alarm Message.
static uint8_t stub_AM_UnitAlarmFault = 0x05;
static uint8_t stub_AM_FaultCode = 0X0F;
static uint8_t  stub_AM_AlarmCode = 0x0B;
static uint8_t  stub_AM_ServiceRequest= 0x0D;


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
 
static void Rx_PGN_65271(void);
static void Rx_PGN_65276(void);
static void Rx_PGN_65296(void);


static void Rx_PGN_65271(void)
{
 if(true == J1939_Get_PGN_65271_Message_Indicator())
 {
   stub_SVEPM_NetBatteryCurrent = AIFGetNet_Battery_Current();    
   stub_SVEPM_AlternatorCurrent = AIFGetAlternator_Current();    
   stub_SVEPM_BatteryPotentialPowerInput1= AIFGetBatt_Potential_Power_Input_1();    
   stub_SVEPM_ChargingSystemPotential = AIFGetCharging_System_Potential();    
   stub_SVEPM_KeyswitchBatteryPotential = AIFGetKeyswitch_Battery_Potential();    
   J1939_Clear_PGN_65271_Message_Indicator();
 }
}

static void Rx_PGN_65272(void)
{
 if(true == J1939_Get_PGN_65272_Message_Indicator())
 {
   J1939_Clear_PGN_65272_Message_Indicator();
 }
}

static void Rx_PGN_65273(void)
{
 if(true == J1939_Get_PGN_65273_Message_Indicator())
 {
   J1939_Clear_PGN_65273_Message_Indicator();
 }
}

static void Rx_PGN_65274(void)
{
 if(true == J1939_Get_PGN_65274_Message_Indicator())
 {
   J1939_Clear_PGN_65274_Message_Indicator();
 }
}

static void Rx_PGN_65275(void)
{
 if(true == J1939_Get_PGN_65275_Message_Indicator())
 {
   J1939_Clear_PGN_65275_Message_Indicator();
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
   // Function : PGN_65282
   //Description : Status Message 1.
   AIFPutMode(stub_SM1_Mode);
   AIFPutTime_To_Delivery(stub_SM1_TimeToDelivery);
   AIFPutTime_To_Cooldown(stub_SM1_TimeToCoolDown);
   AIFPutOutput_Voltage(stub_SM1_OutputVoltage);
   AIFPutPresent_Output_Power(stub_SM1_PresentOutputPower);
   AIFPutMAX_Output_Power(stub_SM1_MaxOutputPower);

   // Function : PGN_65283
   //Description : Status Message 2.
   AIFPutInstantaneous_Fuel_Consumption(stub_SM2_InstantaneousFuelConsumption);
   AIFPutAccumulated_Fuel_Consumption(stub_SM2_AccumulatedFuelConsumption);
   AIFPutHour_Meter(stub_SM2_HourMeter);

   // Function : PGN_65284
   //Description : Alarm Message.
   AIFPutUnit_Alarm_Fault(stub_AM_UnitAlarmFault);
   AIFPutFault_Code(stub_AM_FaultCode);
   AIFPutAlarm_Code(stub_AM_AlarmCode);
   AIFPutService_Request(stub_AM_ServiceRequest);
}


void J1939_Receive_Test_Task(void)
{
   VfJ1939_BusError = J1939_Get_BusOffState();
   Rx_PGN_65271();
   Rx_PGN_65272();
   Rx_PGN_65273();
   Rx_PGN_65274();
   Rx_PGN_65275();
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
