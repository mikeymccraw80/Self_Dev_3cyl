#ifndef HAL_FUEL_H
#define HAL_FUEL_H

//=============================================================================
// include files
//=============================================================================
#include "hal.h"

//=============================================================================
// DisableHWIO_FuelInjector
//=============================================================================
void DisableHWIO_FuelInjector( T_COUNT_BYTE LeHWIO_FuelChannel );
//=============================================================================
// DisableHWIO_TrimPulse
//=============================================================================
void DisableHWIO_TrimPulse( uint8_t index);
//=============================================================================
// EnableHWIO_FuelInjector
//=============================================================================
void EnableHWIO_FuelInjector( T_COUNT_BYTE LeHWIO_FuelChannel );
//=============================================================================
// EnableHWIO_TrimPulse
//=============================================================================
void EnableHWIO_TrimPulse( uint8_t index);
//=============================================================================
// PerfmHWIO_FuelChannelInit
//=============================================================================
void PerfmHWIO_FuelChannelInit( void );
//=============================================================================
// PerfmHWIO_SimultaneousFuelDelivery
//=============================================================================
void PerfmHWIO_SimultaneousFuelDelivery( void );
//=============================================================================
// SetHWIO_AllFuelInjectorPulseWidths
//=============================================================================
void SetHWIO_AllFuelInjectorPulseWidths( T_MILLISECONDSb in_value );
//=============================================================================
// SetHWIO_FuelInjectorEOIT
//=============================================================================
void SetHWIO_FuelInjectorEOIT( T_CRANK_ANGLE LfVIOS_FuelEOIT );
//=============================================================================
// SetHWIO_FuelInjectorPulseWidth
//=============================================================================
void SetHWIO_FuelInjectorPulseWidth( T_COUNT_BYTE LeHWIO_FuelInjChannel, T_MILLISECONDSb LfHWIO_t_PulseWidth );
//=============================================================================
// SetHWIO_FuelInjectorTrimEOIT
//=============================================================================
void SetHWIO_FuelInjectorTrimEOIT( T_CRANK_ANGLE LfVIOS_FuelTrimEOIT );

//=============================================================================
// SetHWIO_InjectorOffset
//=============================================================================
void SetHWIO_InjectorOffset( T_MILLISECONDSb LfHWIO_FuelInjectorOffset );

//=============================================================================
// SetHWIO_MinInjectorOffTime
//=============================================================================
void SetHWIO_MinInjectorOffTime( T_MILLISECONDSb LfHWIO_FuelMinInjectorOffTime );

//=============================================================================
// SetHWIO_MinTrimPulseWidth
//=============================================================================
void SetHWIO_MinTrimPulseWidth( T_MILLISECONDSb LfHWIO_FuelMinTrimPulseWidth );
//=============================================================================
// SetHWIO_FuelMode
//=============================================================================
void SetHWIO_SequentialFuelMode(bool flag );

#endif
