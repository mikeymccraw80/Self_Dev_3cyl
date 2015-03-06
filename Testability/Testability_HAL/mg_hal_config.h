#ifndef MG_HAL_CONFIG_H
#define MG_HAL_CONFIG_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_hal_config.h %
//
// created_by:       zzrfyj %
//
// date_created:      %
//
// %derived_by:      tzwfxv %
//
// %date_modified:              %
//
// %version:         7 %
//
//=============================================================================

#include "io_type.h"
#include "mg_hal_io_map.h"

typedef struct TIME_KEEPER_Tag
{
   uint16_t  start_time;
   uint16_t  current_time;
} TIME_KEEPER_T;

typedef struct TIME_KEEPER_US_Tag
{
   uint32_t  start_time;
   uint32_t  current_time;
} TIME_KEEPER_US_T;

typedef enum 
{
    DISCRETE,
    PWM,
    PWM_REVERSE
} OUTPUT_TYPE_T;

typedef struct MG_HAL_DISCRETE_OUT_Tag 
{
   IO_Configuration_T  io;
   uint32_t            on_time_us;                     /* For Validation Test*/
   uint32_t            off_time_us;                    /* For Validation Test */
   uint32_t            frequency;
   uint32_t            duty;
   OUTPUT_TYPE_T       type;
   bool                current_state;
   TIME_KEEPER_US_T    timer;
} MG_HAL_DISCRETE_OUT_T;

typedef enum 
{
   MG_INJ_IDX_1,
   MG_INJ_IDX_2,
   MG_INJ_IDX_3,
   MG_INJ_IDX_4,
   MG_INJ_NUMBER
} MG_INJ_IDX_T;

typedef struct MG_HAL_PFI_OUT_Tag 
{
   uint32_t        io[MG_INJ_NUMBER];
   uint32_t         on_time_us;
   uint32_t         delay_time_us;
   MG_INJ_IDX_T     current_inj;
   bool             current_state;
   TIME_KEEPER_US_T    timer;
} MG_HAL_PFI_OUT_T;


typedef enum 
{
   MG_EST1,
   MG_ESTSYNC,
   MG_EST_NUMBER
} MG_EST_IDX_T;

typedef struct MG_HAL_EST_OUT_Tag 
{
   uint32_t         io[MG_EST_NUMBER];
   uint32_t         on_time_us;
   uint32_t         delay_time_us;
   bool             current_state;
   TIME_KEEPER_US_T    timer;
} MG_HAL_EST_OUT_T;


typedef enum 
{
   MG_ETC_PWM,
   MG_ETC_DIR,
   MG_ETC_DIS,
   MG_ETC_CS,
   MG_ETC_NUMBER
} MG_ETC_IDX_T;

typedef struct MG_HAL_ETC_OUT_Tag 
{
   uint32_t         io[MG_ETC_NUMBER];
   uint16_t         freq;
   uint8_t          duty;
   uint32_t         reverse_time_ms;
   TIME_KEEPER_US_T    timer;
} MG_HAL_ETC_OUT_T;

#if 0
typedef struct MG_HAL_DISCRETE_IN_Tag 
{
   HIODEVICE        io;
} MG_HAL_DISCRETE_IN_T;

typedef struct MT_HAL_FREQUENCY_IN_Tag 
{
   HIODEVICE        io;
} MT_HAL_FREQUENCY_IN_T;

typedef struct MG_HAL_BARO_IN_Tag 
{
   HIODEVICE   io;
} MG_HAL_BARO_IN_T;

typedef union
{
   uint16_t word;
#if CPU_BigEndian
   struct
   {
      uint8_t lobyte;
      uint8_t hibyte;
   }byte_access;
#else
   struct
   {
      uint8_t hibyte;
      uint8_t lobyte;
   }byte_access;
#endif
}MG_HAL_WORD_ACCESS_T;
#endif
extern const AD_Analog_T MG_HAL_ANALOG_GROUP[];
extern const uint8_t MG_Number_of_Analog_Device;


extern MG_HAL_DISCRETE_OUT_T MG_HAL_DISCRETE_OUT_GROUP[];
extern const uint8_t MG_Number_of_Discrete_Out_Device;

extern MG_HAL_EST_OUT_T MG_HAL_EST_GROUP;

extern MG_HAL_PFI_OUT_T MG_HAL_INJ_GROUP;
extern const uint8_t MG_Number_of_INJ_Device;
extern MG_HAL_ETC_OUT_T MG_HAL_ETC_GROUP;

extern const SIU_GPIO_Channel_T MG_HAL_DISCRETE_IN_GROUP[];
extern const uint8_t MG_Number_of_Discrete_In_Device;

#if 0
extern const MT_HAL_FREQUENCY_IN_T MG_HAL_FREQUENCY_IN_GROUP[];
extern const uint8_t MG_Number_of_Frequency_In_Device;

extern const MG_HAL_ANALOG_T MG_HAL_KNOCK_GROUP[];
extern const uint8_t MG_Number_of_KNOCK_Device;

extern const MG_HAL_BARO_IN_T MG_HAL_BARO_GROUP[];
#endif
#endif /* end of include guard: MG_HAL_CONFIG_H */
