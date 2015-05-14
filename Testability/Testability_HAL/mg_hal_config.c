//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal_config.c %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      rz65p6 %
//
// %date_modified:                  %
//
// %version:         7.1.2 %
//
//=============================================================================

#include "reuse.h"
#include "mg_hal_config.h"
#include "mg_hal_io_map.h"
#include "io_type.h"
#include "dd_vsep.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_pwm.h"
#include "io_config_vsep.h"

#define NOT_CARE            0

//============================================ analog group ======================================
const AD_Analog_T MG_HAL_ANALOG_GROUP[] =
{
    MG_HIODEVICE_AN00,
    MG_HIODEVICE_AN01,
    MG_HIODEVICE_AN02,
    MG_HIODEVICE_AN03,
    MG_HIODEVICE_AN04,
    MG_HIODEVICE_AN05,
    MG_HIODEVICE_AN06,
    MG_HIODEVICE_AN07,
    MG_HIODEVICE_AN08,
    MG_HIODEVICE_AN09,
    MG_HIODEVICE_AN10,
    MG_HIODEVICE_AN11,
    MG_HIODEVICE_AN12,
    MG_HIODEVICE_AN13,
    MG_HIODEVICE_AN14,
    MG_HIODEVICE_AN15,
    MG_HIODEVICE_AN16,
    MG_HIODEVICE_AN17,
    MG_HIODEVICE_AN18,
    MG_HIODEVICE_AN19,
    MG_HIODEVICE_AN20,
    MG_HIODEVICE_AN21,
    MG_HIODEVICE_AN22,
    MG_HIODEVICE_AN23,
    MG_HIODEVICE_AN24,
    MG_HIODEVICE_AN25,
    MG_HIODEVICE_AN26,
    MG_HIODEVICE_AN27,
    MG_HIODEVICE_AN28,
    MG_HIODEVICE_AN29,
    MG_HIODEVICE_AN30,
    MG_HIODEVICE_AN31,
    MG_HIODEVICE_AN32,
    MG_HIODEVICE_AN33,
    MG_HIODEVICE_AN34,
    MG_HIODEVICE_AN35,
    MG_HIODEVICE_AN36,
    MG_HIODEVICE_AN37,
    MG_HIODEVICE_AN38,
    MG_HIODEVICE_AN39
};

#define MG_SIZE_OF_ANALOG_GROUP   (sizeof(MG_HAL_ANALOG_GROUP)/sizeof(AD_Analog_T))

const uint8_t MG_Number_of_Analog_Device = MG_SIZE_OF_ANALOG_GROUP;


//============================================ analog group end ==================================

//============================================ discrete in group ==================================
const SIU_GPIO_Channel_T MG_HAL_DISCRETE_IN_GROUP[] =
{
    MG_HIODEVICE_DI_MPIO1,
    MG_HIODEVICE_DI_MPIO2,
    MG_HIODEVICE_DI_MPIO3,
    MG_HIODEVICE_DI_GPIO139,
    MG_HIODEVICE_DI_GPIO138,
    MG_HIODEVICE_DI_GPIO224,
    MG_HIODEVICE_DI_GPIO121,
    MG_HIODEVICE_DI_GPIO122,
    MG_HIODEVICE_DI_AN4,
    MG_HIODEVICE_DI_AN12,
    MG_HIODEVICE_DI_AN24,
    MG_HIODEVICE_DI_AN3,
    MG_HIODEVICE_DI_AN25,
    MG_HIODEVICE_DI_AN23,
    MG_HIODEVICE_DI_AN18,
    MG_HIODEVICE_DI_AN15,
};

#define MG_SIZE_OF_DISCRETE_IN_GROUP   (sizeof(MG_HAL_DISCRETE_IN_GROUP)/sizeof(SIU_GPIO_Channel_T))

const uint8_t MG_Number_of_Discrete_In_Device = MG_SIZE_OF_DISCRETE_IN_GROUP;


//============================================ discrete in group end ==================================

//============================================ discrete out group ================================
// must be located in RAM
MG_HAL_DISCRETE_OUT_T MG_HAL_DISCRETE_OUT_GROUP[] = 
{
    { MG_HIODEVICE_DO_DFB05, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB06, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB07, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB08, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB13, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM_REVERSE },
    { MG_HIODEVICE_DO_DFB14, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB15, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB16, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB17, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM_REVERSE },
    { MG_HIODEVICE_DO_DFB18, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM_REVERSE },
    { MG_HIODEVICE_DO_DFB19, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB20, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB21, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB22, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB23, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM_REVERSE },
    { MG_HIODEVICE_DO_DFB24, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB25, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB26, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
    { MG_HIODEVICE_DO_DFB27, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB28, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB29, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, PWM },
    { MG_HIODEVICE_DO_DFB30, NOT_CARE, NOT_CARE, NOT_CARE, NOT_CARE, DISCRETE },
};

#define MG_SIZE_OF_DISCRETE_OUT_GROUP    (sizeof(MG_HAL_DISCRETE_OUT_GROUP)/sizeof(MG_HAL_DISCRETE_OUT_T))

const uint8_t MG_Number_of_Discrete_Out_Device = MG_SIZE_OF_DISCRETE_OUT_GROUP;
//============================================ discrete out group end ==============================

//============================================ EST =================================================

MG_HAL_EST_OUT_T MG_HAL_EST_GROUP =
{
    {
        MG_HIODEVICE_DO_EST1,
        MG_HIODEVICE_DO_ESTSYNC
    }
};
//============================================ EST end =============================================

//============================================ PFI =================================================
MG_HAL_PFI_OUT_T MG_HAL_INJ_GROUP = 
{
    { 
        MG_HIODEVICE_DO_DFB09,
        MG_HIODEVICE_DO_DFB10, 
        MG_HIODEVICE_DO_DFB11, 
        MG_HIODEVICE_DO_DFB12
    }
};
//============================================ PFI end =============================================


//============================================ ETC =================================================
MG_HAL_ETC_OUT_T MG_HAL_ETC_GROUP =
{
    {
        MG_HIODEVICE_ETC_PWM,
        MG_HIODEVICE_ETCDIR, 
        MG_HIODEVICE_ETCDIS, 
        MG_HIODEVICE_ETCCS
    }
};
//============================================ ETC end =============================================

//============================================ Frequency Input =====================================
const MT_HAL_FREQUENCY_IN_T MG_HAL_FREQUENCY_IN_GROUP[] = 
{
    MG_HIODEVICE_FI_58XPOS,
    MG_HIODEVICE_FI_VSS,
    MG_HIODEVICE_FI_CAM1,
    MG_HIODEVICE_FI_CAM2,
    MG_HIODEVICE_FI_ABSPWM,
    MG_HIODEVICE_FI_ENS
};

#define MG_SIZE_OF_FREQUENCY_IN_GROUP    (sizeof(MG_HAL_FREQUENCY_IN_GROUP)/sizeof(MT_HAL_FREQUENCY_IN_T))

const uint8_t MG_Number_of_Frequency_In_Device = MG_SIZE_OF_FREQUENCY_IN_GROUP;
//============================================ Frequency Input =====================================
#if 0
//============================================ Baro =================================================
const MG_HAL_BARO_IN_T MG_HAL_BARO_GROUP[] =
{
    MG_HIODEVICE_BARO_PRESSURE,
    MG_HIODEVICE_BARO_TEMPERATURE
};

#define MG_SIZE_OF_BARO_GROUP   (sizeof(MG_HAL_BARO_GROUP)/sizeof(MG_HAL_BARO_IN_T))

const uint8_t MG_Number_of_BARO_Device = MG_SIZE_OF_BARO_GROUP;
//============================================ Baro end =============================================
#endif
//============================================ Knock group ======================================
const MG_HAL_ANALOG_T MG_HAL_KNOCK_GROUP[] =
{
    MG_HIODEVICE_KNOCK_HIGH,
    MG_HIODEVICE_KNOCK_LOW,
};

#define MG_SIZE_OF_KNOCK_GROUP   (sizeof(MG_HAL_KNOCK_GROUP)/sizeof(MG_HAL_ANALOG_T))

const uint8_t MG_Number_of_KNOCK_Device = MG_SIZE_OF_KNOCK_GROUP;

//============================================ Knock group end ==================================
