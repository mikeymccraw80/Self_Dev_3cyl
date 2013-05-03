//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//=============================================================================
//=============================================================================
// Include the Type file for the device driver and io layers
//=============================================================================

//=============================================================================
// Include interface for the device driver
//=============================================================================
#include "reuse.h"
#include "dd_l9958.h"
#include "dd_l9958_txd.h"
#include "dd_l9958_rxd.h"
#include "dd_l9958_config.h"
#include "io_config_dspi.h"
#include "dd_dspi_interface.h"

uint16_t L9958_Rxd;
uint16_t L9958_Txd;

//=============================================================================
// L9958_DISCRETE_Device_Initialize
//=============================================================================
void L9958_Device_Initialize(void)
{
	L9958_Txd = L9958_TXD_INITIAL;
	L9958_SPI_Immediate_Transfer();
	L9958_FAULT_Initialize_Device();
}

//===========================================================================
// L9958_Diag_Rst_Disable_Set
//===========================================================================
void L9958_Diag_Rst_Disable_Set(L9958_DIAG_RST_DISABLE_T in_diag_rst_disable)
{
	L9958_Txd = L9958_Msg_Set_Diag_Reset_Disable(L9958_Txd, in_diag_rst_disable);
}

//===========================================================================
// L9958_Diag_Rst_Disable_Set_Immediate
//===========================================================================
void L9958_Diag_Rst_Disable_Set_Immediate(L9958_DIAG_RST_DISABLE_T in_diag_rst_disable)
{
	L9958_Diag_Rst_Disable_Set(in_diag_rst_disable);
	L9958_SPI_Immediate_Transfer();
}

//===========================================================================
// L9958_Regulation_Curr_Level_Set
//===========================================================================
void L9958_Regulation_Curr_Level_Set(L9958_CURRENT_LEVEL_T in_curr_level)
{
	L9958_Txd = L9958_Msg_Set_Regulation_Curr_Level(L9958_Txd, in_curr_level);
}

//===========================================================================
// L9958_Regulation_Curr_Level_Set_Immediate
//===========================================================================
void L9958_Regulation_Curr_Level_Set_Immediate(L9958_CURRENT_LEVEL_T in_diag_rst_disable)
{
	L9958_Regulation_Curr_Level_Set(in_diag_rst_disable);
	L9958_SPI_Immediate_Transfer();
}

//===========================================================================
// L9958_VSR_Set
//===========================================================================
void L9958_VSR_Set(L9958_VSR_CONTROL_T in_volt_slew)
{
	L9958_Txd = L9958_Msg_Set_Voltage_Slew_Control(L9958_Txd, in_volt_slew);
}

//===========================================================================
// L9958_VSR_Set_Immediate
//===========================================================================
void L9958_VSR_Set_Immediate(L9958_VSR_CONTROL_T in_volt_slew)
{
	L9958_VSR_Set(in_volt_slew);
	L9958_SPI_Immediate_Transfer(); 
}

//===========================================================================
// L9958_ISR_Set
//===========================================================================
void L9958_ISR_Set(L9958_ISR_CONTROL_T in_curr_slew)
{
	L9958_Txd = L9958_Msg_Set_Current_Slew_Control(L9958_Txd, in_curr_slew);
}

//===========================================================================
// L9958_Current_Slew_Control_Set_Immediate
//===========================================================================
void L9958_ISR_Set_Immediate(L9958_ISR_CONTROL_T in_curr_slew)
{
	L9958_ISR_Set(in_curr_slew);
	L9958_SPI_Immediate_Transfer();
}

//===========================================================================
// L9958_Current_Slew_Control_Disable_Set
//===========================================================================
void L9958_ISR_Disable_Set(L9958_ISR_DISABLE_T in_curr_slew_Disable)
{
	L9958_Txd = L9958_Msg_Set_Current_Slew_Control_Disable(L9958_Txd, in_curr_slew_Disable);
}

//===========================================================================
// L9958_ISR_Disable_Set_Immediate
//===========================================================================
void L9958_ISR_Disable_Set_Immediate(L9958_ISR_DISABLE_T  in_curr_slew_Disable)
{
	L9958_ISR_Disable_Set(in_curr_slew_Disable);
	L9958_SPI_Immediate_Transfer( );
}

//===========================================================================
// L9958_OL_ON_Enable_Set
//===========================================================================
void L9958_OL_ON_Enable_Set(L9958_OPEN_LOAD_ON_T in_open_load_state)
{
	L9958_Txd = L9958_Msg_Set_Open_Load_in_ON_Enable(L9958_Txd, in_open_load_state);
}

//===========================================================================
// L9958_OL_ON_Enable_Set_Immediate
//===========================================================================
void L9958_OL_ON_Enable_Set_Immediate(L9958_OPEN_LOAD_ON_T in_open_load_state)
{
	L9958_OL_ON_Enable_Set(in_open_load_state);
	L9958_SPI_Immediate_Transfer(); 
}
   
//=============================================================================
// L9958_Clear_Device
//=============================================================================
void L9958_Clear_Device(void)
{
	L9958_Txd = 0;
}

//=============================================================================
// L9958_SPI_Immediate_Transfer
//=============================================================================
void L9958_SPI_Immediate_Transfer(void)
{
	//interrupt_state_t irq_state;

	//irq_state = Get_Interrupt_State();
	//Disable_Interrupts();
	Disable_Interrupts();
	L9958_Rxd = DSPI_B_Exchange_Data1(ETC_CHIP_SELECT, ETC_CTAR_SELECT, DSPI_CTAR_FMSZ_16, L9958_Txd, 1);
	//Set_Interrupt_State(irq_state) ;
	Enable_Interrupts();
}


