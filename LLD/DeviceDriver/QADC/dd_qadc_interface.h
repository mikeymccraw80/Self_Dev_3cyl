#ifndef DD_QADC_INTERFACE_H
#define DD_QADC_INTERFACE_H

#include "dd_qadc.h"
#include "io_config_dma.h"

//=============================================================================
// QADC
//=============================================================================

extern uint16_t QADC_Queue_Result_4[AD_ANALOG_MAX_SIGNAL_NAMES];
extern uint16_t QADC_Queue_Result_1[AD_ANALOG_FIFO1_MAX_SIGNAL_NAMES];

//=============================================================================
// QADC_Initialize_Device
//=============================================================================
extern void QADC_Initialize_Device(void );

//=============================================================================
// QADC_Analog_Get_Value
//=============================================================================
extern uint16_t  QADC_Analog_Get_Value(AD_Analog_T channel );

//=============================================================================
// QADC_Analog_FIFO1_Get_Value
//=============================================================================
extern  uint16_t  QADC_Analog_FIFO1_Get_Value(AD_FIFO1_Analog_T channel );


#endif
