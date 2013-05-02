#ifndef DD_L9958_H
#define DD_L9958_H
//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//=============================================================================

#include "io_type.h"
#include "dd_L9958_config.h"
#include "dd_L9958_txd.h"

extern const uint16_t  L9958_TXD_INITIAL;
extern uint16_t        L9958_Txd;
extern uint16_t        L9958_Rxd;

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


//===========================================================================
// L9958_Fault_Diagnose_Channels
//
// @func This function 
//
// @parm L9958_Index_T
//
// @rdesc None. 
//
// @end
//===========================================================================
void L9958_Fault_Diagnose_Channels(void);


#endif // DD_L9958_H
