#ifndef DD_L9958_H
#define DD_L9958_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//=============================================================================

#include "io_type.h"
#include "dd_l9958_txd.h"

/* L9958 Diag Register define */
typedef union {
	uint16_t Value;
	struct {
		uint16_t SBAT_OFF : 1;		//Short to Battery in OFF condition
		uint16_t SGND_OFF : 1;		//Short to GND in OFF condition
		uint16_t RES13_12 : 2;
		uint16_t OC_HS2 : 1;		// Over-Current on How Side 2
		uint16_t OC_HS1 : 1;		// Over-Current on How Side 1
		uint16_t OC_LS2 : 1;		// Over-Current on Low Side 2
		uint16_t OC_LS1 : 1;		// Over-Current on Low Side 1
		uint16_t ACT : 1;			// Bridge enable,Ture after reset
		uint16_t TSD : 1;			// Over-temperature Shutdown
		uint16_t TWARN : 1;			// Temperature warning
		uint16_t ILIM : 1;			// Current Limitation reached
		uint16_t VDD_OV : 1;		// Power supply for ECT Dirver overvoltage
		uint16_t VS_UV : 1;			// 12 Vs undervoltage
		uint16_t OL_ON : 1;			// Open Load in ON condition
		uint16_t OL_OFF : 1;		// Open Load in OFF condition
	} Bits;
} l9958_diag_t;

/* L9958 Configuration Register define */
typedef union {
	uint16_t Value;
	struct {
		uint16_t RES15_12: 4;
		uint16_t OL_ON : 1;		// Open Load in ON state Enable
		uint16_t ISR_DIS : 1;		// Current Slew Rate Control Disable
		uint16_t ISR : 1;		// Over-Current on Low Side 2
		uint16_t VSR : 1;		// Over-Current on Low Side 1
		uint16_t RES7_4 : 4;			// Bridge enable,Ture after reset
		uint16_t CL_2 : 1;			// Over-temperature Shutdown
		uint16_t CL_1 : 1;			// Temperature warning
		uint16_t DR : 1;			// Current Limitation reached
		uint16_t RES0 : 1;		// Power supply for ECT Dirver overvoltage
	} Bits;
} l9958_conf_t;

extern l9958_diag_t L9958_Rxd;
extern l9958_conf_t L9958_Txd;

//===========================================================================
// L9958_Device_Initialize
//
// @func This function initializes L9958 
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Device_Initialize(void);


//===========================================================================
// L9958_Diag_Rst_Disable_Set
//
// @func This function sets the Diag reset Disable TRUE/FALSE
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_DIAG_RST_DISABLE_T|    in_diag_rst_disable|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Diag_Rst_Disable_Set(L9958_DIAG_RST_DISABLE_T in_diag_rst_disable);


//===========================================================================
// L9958_Diag_Rst_Disable_Set_Immediate
//
// @func  This function sets the Diag reset Disable TRUE/FALSE immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_DIAG_RST_DISABLE_T|    in_diag_rst_disable|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Diag_Rst_Disable_Set_Immediate(L9958_DIAG_RST_DISABLE_T   in_diag_rst_disable);


//===========================================================================
// L9958_Regulation_Curr_Level_Set
//
// @func This function sets the Regulation Current Level
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_CURRENT_LEVEL_T|    in_curr_level|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Regulation_Curr_Level_Set(L9958_CURRENT_LEVEL_T  in_curr_level);


//===========================================================================
// L9958_Regulation_Curr_Level_Set_Immediate
//
// @func  This function sets the Regulation Current Level immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_CURRENT_LEVEL_T|    in_curr_level|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Regulation_Curr_Level_Set_Immediate(L9958_CURRENT_LEVEL_T  in_diag_rst_disable);


//===========================================================================
// L9958_VSR_Set
//
// @func This function sets the Voltage Slew Control Hi /LO
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_VSR_CONTROL_T|    in_volt_slew|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_VSR_Set(L9958_VSR_CONTROL_T in_volt_slew);


//===========================================================================
// L9958_VSR_Set_Immediate
//
// @func  This function sets the Voltage Slew Control Hi /LO immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_VSR_CONTROL_T|    in_volt_slew|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_VSR_Set_Immediate(L9958_VSR_CONTROL_T in_volt_slew);


//===========================================================================
// L9958_ISR_Set
//
// @func This function sets the Current Slew Control Hi /LO
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_ISR_CONTROL_T|    in_curr_slew|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Set(L9958_ISR_CONTROL_T in_curr_slew);


//===========================================================================
// L9958_Current_Slew_Control_Set_Immediate
//
// @func  This function sets the Current Slew Control Hi /LO immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_ISR_CONTROL_T|    in_curr_slew|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Set_Immediate(L9958_ISR_CONTROL_T   in_volt_slew);


//===========================================================================
// L9958_Current_Slew_Control_Disable_Set
//
// @func This function sets the Current Slew Control Disable TRUE /FALSE
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_ISR_DISABLE_T|    in_curr_slew_Disable|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Disable_Set(L9958_ISR_DISABLE_T   in_curr_slew_Disable);


//===========================================================================
// L9958_ISR_Disable_Set_Immediate
//
// @func  This function sets the Current Slew Control Disable TRUE /FALSE  immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_ISR_DISABLE_T|    in_curr_slew_Disable|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_ISR_Disable_Set_Immediate(L9958_ISR_DISABLE_T   in_curr_slew_Disable);


//===========================================================================
// L9958_OL_ON_Enable_Set
//
// @func This function sets the Open Load in ON Enable Enable/Disable
//
// @parm IO_Configuration_T| in_configuration | . 
//            L9958_OPEN_LOAD_ON_T|    in_open_load_state|
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_OL_ON_Enable_Set(L9958_OPEN_LOAD_ON_T  in_open_load_state);


//===========================================================================
// L9958_OL_ON_Enable_Set_Immediate
//
// @func  This function sets the Open load in ON state Enable /Disable  immediate
//
// @parm IO_Configuration_T| in_configuration | .
//            L9958_OPEN_LOAD_ON_T|    in_open_load_state|   
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_OL_ON_Enable_Set_Immediate(L9958_OPEN_LOAD_ON_T   in_open_load_state);


//===========================================================================
// L9958_Clear_Device
//
// @func This function clears the device
//
// @parm IO_Configuration_T| in_configuration | .
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Clear_Device(void);

void L9958_SPI_Immediate_Transfer(void);

#endif // DD_L9958_H
