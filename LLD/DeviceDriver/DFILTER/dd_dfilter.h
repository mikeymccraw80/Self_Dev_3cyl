#ifndef DD_DFILTER_H
#define DD_DFILTER_H

//=============================================================================
// Include Files
//=============================================================================
#include "hw_dfilter.h"

//=============================================================================
// Define Marco
//=============================================================================
typedef enum DEC_FILTER_Device_Index_Tag
{
   DEC_FILT_A,
   DEC_FILT_MAX

}  DEC_FILTER_Device_Index_T;

//=============================================================================
// @globalv DEC_FILTER_T | DEC_FILTER_n |
// The Register Memory Overlay of the decimation filter module
// to provide software access and debug information.
//
// @end
//=============================================================================
#define SECTION_DEC_FILTER_REGISTER
#include "section.h"
extern DEC_FILTER_T DEC_FILTER_A;
#define SECTION_END
#include "section.h"

//=============================================================================
//Define Marco
//=============================================================================


typedef enum DEC_FILTER_OutBuf_Result_Trnsfr_Tag
{
   DEC_FILTER_TRNSFR_RES_TPU_TRIG_DISABLE,
   DEC_FILTER_TRNSFR_RES_TPU_TRIG_ENABLE

}DEC_FILTER_OutBuf_Result_Trnsfr_T;


typedef enum DEC_FILTER_OutBuf_Trig_Mode_Tag
{
   DEC_FILTER_TRNSFR_RES_TPU_RISING_EDGE,
   DEC_FILTER_TRNSFR_RES_TPU_LEVEL_0,
   DEC_FILTER_TRNSFR_RES_TPU_FALLING_EDGE,
   DEC_FILTER_TRNSFR_RES_TPU_LEVEL_1

}DEC_FILTER_OutBuf_Trig_Mode_T;


typedef enum DEC_FILTER_Interrupt_Type_Tag
{
   DEC_FILTER_INPUT_DATA_INT,
   DEC_FILTER_OUTPUT_DATA_INT,
   DEC_FILTER_ERROR_INT,
   DEC_FILTER_INTG_DATA_INT,
   DEC_FILTER_INBUFFER_REQ_INT,
   DEC_FILTER_OUTBUFFER_REQ_INT
}DEC_FILTER_Interrupt_Type_T;



typedef enum DEC_FILTER_Device_Enable_Tag
{
   DEC_FILTER_DEVICE_ENABLE,
   DEC_FILTER_DEVICE_DISABLE
}DEC_FILTER_Device_Enable_T;



//=============================================================================
// @enum DEC_FILTER_Cascade_Mode_T | Specifies the Cascade mode for Filter
//=============================================================================
typedef enum DEC_FILTER_Cascade_Mode_Tag
{
   DEC_FILTER_DEVICE_NO_CASCADE,
   DEC_FILTER_DEVICE_HEAD_BLK_CASCADE,
   DEC_FILTER_DEVICE_TAIL_BLK_CASCADE,
   DEC_FILTER_DEVICE_MIDDLE_BLK_CASCADE

} DEC_FILTER_Cascade_Mode_T;



//=============================================================================
// @enum DEC_FILTER_Cascade_Quantity_T | Specifies the Cascade mode for Filter
//=============================================================================
typedef enum DEC_FILTER_Cascade_Config_Tag
{
   DEC_FILTER_DEVICE_CASCADE_HEAD_TAIL,
   DEC_FILTER_DEVICE_CASCADE_HEAD_MIDDLE_TAIL

} DEC_FILTER_Cascade_Config_T;


//=============================================================================
// @enum DEC_FILTER_Filter_Type_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Filter_Type_Tag
{
   DEC_FILTER_BYPASS,             //No filter selected
   DEC_FILTER_4_ORDER_IIR,        //IIR Filter - 1 x 4th order
   DEC_FILTER_8_ORDER_FIR,        //FIR Filter - 1 x 8th order
   DEC_FILTER_TYPE_RESERVED

} DEC_FILTER_Filter_Type_T;


//=============================================================================
// @enum DEC_FILTER_Scaling_Factor_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Scaling_Factor_Tag
{
   DEC_FILTER_SCALING_FACTOR_1,
   DEC_FILTER_SCALING_FACTOR_4,
   DEC_FILTER_SCALING_FACTOR_8,
   DEC_FILTER_SCALING_FACTOR_16

} DEC_FILTER_Scaling_Factor_T;


//=============================================================================
// @enum DEC_FILTER_Saturation_Enable_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Saturation_Enable_Tag
{
   DEC_FILTER_SATURATION_DISABLE,
   DEC_FILTER_SATURATION_ENABLE

} DEC_FILTER_Saturation_Enable_T;


//=============================================================================
// @enum DEC_FILTER_IO_Select_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Input_Select_Tag
{
     DEC_FILTER_Input_PSI_Slavebus,
   DEC_FILTER_Input_Device_Slavebus


} DEC_FILTER_Input_Select_T;



//=============================================================================
// @enum DEC_FILTER_Decimation_Rate_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Decimation_Rate_Tag
{
   DEC_FILTER_NO_DECIMATION,
   DEC_FILTER_DECIMATION_RATE_2,
   DEC_FILTER_DECIMATION_RATE_3,
   DEC_FILTER_DECIMATION_RATE_4,
   DEC_FILTER_DECIMATION_RATE_5,
   DEC_FILTER_DECIMATION_RATE_6,
   DEC_FILTER_DECIMATION_RATE_7,
   DEC_FILTER_DECIMATION_RATE_8,
   DEC_FILTER_DECIMATION_RATE_9,
   DEC_FILTER_DECIMATION_RATE_10,
   DEC_FILTER_DECIMATION_RATE_11,
   DEC_FILTER_DECIMATION_RATE_12,
   DEC_FILTER_DECIMATION_RATE_13,
   DEC_FILTER_DECIMATION_RATE_14,
   DEC_FILTER_DECIMATION_RATE_15,
   DEC_FILTER_DECIMATION_RATE_16

} DEC_FILTER_Decimation_Rate_T;


//=============================================================================
// @enum DEC_FILTER_DMA_Request_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_DMA_Request_Tag
{
   DEC_FILTER_DMA_DISABLED,
   DEC_FILTER_DMA_ENABLED

} DEC_FILTER_DMA_Request_T;



//=============================================================================
// @enum DEC_FILTER_Ip_Buffer_Int_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Inp_Buffer_Int_Tag
{
   DEC_FILTER_IP_BUFFER_INT_DISABLE,
   DEC_FILTER_IP_BUFFER_INT_ENABLE

} DEC_FILTER_Ip_Buffer_Int_T;



//=============================================================================
// @enum DEC_FILTER_Out_Buffer_Int_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Out_Buffer_Int_Tag
{
   DEC_FILTER_OUT_BUFFER_INT_DISABLE,
   DEC_FILTER_OUT_BUFFER_INT_ENABLE

} DEC_FILTER_Out_Buffer_Int_T;


//=============================================================================
// @enum DEC_FILTER_Error_Int_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_Error_Int_Tag
{
   DEC_FILTER_ERR_INT_DISABLE,
   DEC_FILTER_ERR_INT_ENABLE

} DEC_FILTER_Error_Int_T;

//=============================================================================
// /-----------------------------------------------------------------------\
// |                     DECIMATION FILTER INTEGRATOR Configuration
// \-----------------------------------------------------------------------/
//=============================================================================



//=============================================================================
// @enum DEC_FILTER_INTG_DMA_Enable_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_INTG_DMA_Enable_Tag
{
   DEC_FILTER_INTG_DMA_DISABLE,
   DEC_FILTER_INTG_DMA_ENABLE

} DEC_FILTER_INTG_DMA_Enable_T;



//=============================================================================
// @enum DEC_FILTER_INTG_Signal_Selection_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_INTG_Signal_Selection_Tag
{
   DEC_FILTER_INTG_SIGNAL_IN_ABSOLUTE,
   DEC_FILTER_INTG_SIGNAL_IN_NORMAL

} DEC_FILTER_INTG_Signal_Selection_T;



//=============================================================================
// @enum DEC_FILTER_INTG_Saturation_Sel_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_INTG_Saturation_Sel_Tag
{
   DEC_FILTER_INTG_SATURATION_DISABLE,
   DEC_FILTER_INTG_SATURATION_ENABLE

} DEC_FILTER_INTG_Saturation_Sel_T;


//=============================================================================
// @enum DEC_FILTER_INTG_Saturation_Sel_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_INTG_Counter_Saturation_Sel_Tag
{
   DEC_FILTER_INTG_CNTR_SATURATION_DISABLE,
   DEC_FILTER_INTG_CNTR_SATURATION_ENABLE

} DEC_FILTER_INTG_Counter_Saturation_Sel_T;

//=============================================================================
// @enum DEC_FILTER_Decimated_Signal_Sel_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_INTG_Decimated_Signal_Sel_Tag
{
   DEC_FILTER_INTG_IN_DECIMATED_SIGNAL,
   DEC_FILTER_INTG_IN_NON_DECIMATED_SIGNAL

} DEC_FILTER_INTG_Decimated_Signal_Sel_T;


//=============================================================================
// @enum DEC_FILTER_INTG_Zero_Cntrl_Mode_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_INTG_Zero_Cntrl_Mode_Tag
{
   DEC_FILT_INTG_ZERO_REQUEST_DISABLED,
   DEC_FILT_INTG_ZERO_SIGNAL_TOGGLE,
   DEC_FILT_INTG_ZERO_RISING_EDGE_SIGNAL,
   DEC_FILT_INTG_ZERO_FALLING_EDGE_SIGNAL

} DEC_FILTER_INTG_Zero_Cntrl_Mode_T;

//=============================================================================
// @enum DEC_FILTER_INTG_Halt_Cntrl_T | Specifies the Type of Filter
//=============================================================================
typedef enum DEC_FILTER_INTG_Halt_Cntrl_Tag
{
   DEC_FILT_INTG_HALT_CNTRL_DISABLED,
   DEC_FILT_INTG_HALT_SIGNAL_INDEPENDENT,
   DEC_FILT_INTG_HALT_SIGNAL_LOW,
   DEC_FILT_INTG_HALT_SIGNAL_HI

} DEC_FILTER_INTG_Halt_Cntrl_T;

//=============================================================================
// @enum DEC_FILTER_INTG_Read_Request_Mode_T | Specifies the INTegrator read Request mode
//=============================================================================
typedef enum DEC_FILTER_INTG_Read_Request_Mode_Tag
{
   DEC_FILT_INTG_OP_REQ_DISABLED,
   DEC_FILT_INTG_OP_TOGGLE_HW_SIGNAL,
   DEC_FILT_INTG_OP_RISING_EDGE_HW_SIGNAL,
   DEC_FILT_INTG_OP_FALLING_EDGE_HW_SIGNAL,
   DEC_FILT_INTG_OP_RESERVED,
   DEC_FILT_INTG_OP_CONTINUOUS_HW_SIGNAL_INDEPENDENT,
   DEC_FILT_INTG_OP_CONTINUOUS_HW_SIGNAL_LOGIC_0,
   DEC_FILT_INTG_OP_CONTINUOUS_HW_SIGNAL_LOGIC_1

} DEC_FILTER_INTG_Read_Request_Mode_T;

//=============================================================================
// @enum DEC_FILTER_INTG_Enable_Cntrl_T | Specifies the INTegrator Enable control
//=============================================================================
typedef enum DEC_FILTER_INTG_Enable_Cntrl_Tag
{
   DEC_FILT_INTG_DISABLED_HW_SIGNAL_INDEPENDENT,
   DEC_FILT_INTG_ENABLED_HW_SIGNAL_INDEPENDENT,
   DEC_FILT_INTG_ENABLED_HW_SIGNAL_LOGIC_0,
   DEC_FILT_INTG_ENABLED_HW_SIGNAL_LOGIC_1

} DEC_FILTER_INTG_Enable_Cntrl_T;

//=============================================================================
// /-----------------------------------------------------------------------\
// |                     DECIMATION FILTER InBuffer Data Configs
// \-----------------------------------------------------------------------/
//=============================================================================


//=============================================================================
// @enum DEC_FILTER_INBUF_Flush_Enable_T | Specifies the Flush Enable control
//=============================================================================
typedef enum DEC_FILTER_INBUF_Flush_Enable_Tag
{
   DEC_FILTER_INBUF_FLUSH_DISABLE,
   DEC_FILTER_INBUF_FLUSH_ENABLE

} DEC_FILTER_INBUF_Flush_Enable_T;

//=============================================================================
// @enum DEC_FILTER_INBUF_Prefill_Enable_T | Specifies the Flush Enable control
//=============================================================================
typedef enum DEC_FILTER_INBUF_Prefill_Enable_Tag
{
   DEC_FILTER_INBUF_PREFILL_DISABLE,
   DEC_FILTER_INBUF_PREFILL_ENABLE

} DEC_FILTER_INBUF_Prefill_Enable_T;



//=============================================================================
// @enum DEC_FILTER_INBUF_InTag_T | Specifies the Destination
//=============================================================================
typedef enum DEC_FILTER_INBUF_InTag_Tag
{
   DEC_FILTER_INBUF_TAG_RFIFO_0,
   DEC_FILTER_INBUF_TAG_RFIFO_1,
   DEC_FILTER_INBUF_TAG_RFIFO_2,
   DEC_FILTER_INBUF_TAG_RFIFO_3,
   DEC_FILTER_INBUF_TAG_RFIFO_4,
   DEC_FILTER_INBUF_TAG_RFIFO_5,
   DEC_FILTER_INBUF_TAG_RFIFO_6,
   DEC_FILTER_INBUF_TAG_RFIFO_7,
   DEC_FILTER_INBUF_TAG_RFIFO_8,
   DEC_FILTER_INBUF_TAG_RFIFO_9,
   DEC_FILTER_INBUF_TAG_RFIFO_10,
   DEC_FILTER_INBUF_TAG_RFIFO_11,
   DEC_FILTER_INBUF_TAG_RESERVED_0,
   DEC_FILTER_INBUF_TAG_RESERVED_1,
   DEC_FILTER_INBUF_TAG_RESERVED_2,
   DEC_FILTER_INBUF_TAG_RESERVED_3

} DEC_FILTER_INBUF_InTag_T;


typedef struct DEC_FILT_INTG_Data_Tag
{
   uint32_t Dec_filt_integrator_value;
   uint32_t Dec_filt_integrator_counts;

}DEC_FILT_INTG_Data_T;




#endif // DD_DFILTER_H

