
//=============================================================================
// include files
//=============================================================================
#include "dd_pfi_interface.h"
#include "io_conversion.h"
#include "hal_fuel.h"

//=============================================================================
// FUEL
//=============================================================================
// IO_PFI_Initialization_Parameters_T const IO_Init_Pfi_Initialization_Parameters;
//=============================================================================
// DisableHWIO_FuelInjector
//=============================================================================
void DisableHWIO_FuelInjector( T_COUNT_BYTE LeHWIO_FuelChannel )
{
   PFI_Disable_Channel( LeHWIO_FuelChannel );
}

//=============================================================================
// DisableHWIO_TrimPulse
//=============================================================================
void DisableHWIO_TrimPulse( uint8_t index)
{
   PFI_Disable_Trim_Pulses(index);
}

//=============================================================================
// EnableHWIO_FuelInjector
//=============================================================================
void EnableHWIO_FuelInjector( T_COUNT_BYTE LeHWIO_FuelChannel )
{
 //  if (C2MIO_Is_Channel_Fault_Threshold_Reach(C2MIO_Get_Channel( MTSA_CONFIG_FAULT_INJ1 ) + (C2MIO_Channel_T)LeHWIO_FuelChannel  )) 
   //{
   // PFI_Enable_Channel(LeHWIO_FuelChannel);
 //  }
 //  else
 //  {
       PFI_Enable_Channel(LeHWIO_FuelChannel);
   //}
}

//=============================================================================
// EnableHWIO_TrimPulse
//=============================================================================
void EnableHWIO_TrimPulse( uint8_t index)
{
   PFI_Enable_Trim_Pulses(index);
}

//=============================================================================
// GetHWIO_InjCktState
//=============================================================================
TeINJ_CIRCUIT_STATE GetHWIO_InjCktState( uint8_t in_index )
{
   TeINJ_CIRCUIT_STATE status;
   status =( TeINJ_CIRCUIT_STATE)( (0x01) & (PFI_Injector_Diagnostic >> in_index) );
   return   status;
  // PFI_Get_Injector_Circuit_State(in_index);
}


//=============================================================================
// PerfmHWIO_FuelChannelInit
//=============================================================================
void PerfmHWIO_FuelChannelInit( void )
{
  
  // PFI_Initialize( (IO_PFI_Initialization_Parameters_T  * const)&IO_Init_Pfi_Initialization_Parameters );
}

//=============================================================================
// PerfmHWIO_SimultaneousFuelDelivery
//=============================================================================
void PerfmHWIO_SimultaneousFuelDelivery( void )
{
   PFI_Perform_Simultaneous_Delivery();
}

//=============================================================================
// SetHWIO_AllFuelInjectorPulseWidths
//=============================================================================
void SetHWIO_AllFuelInjectorPulseWidths( T_MILLISECONDSb in_value )
{
   uint32_t cs;

   cs = Enter_Critical_Section();
   PFI_Set_All_Pulse_Widths( in_value, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
   Leave_Critical_Section( cs );
}

//=============================================================================
// SetHWIO_FuelInjectorEOIT
//=============================================================================
void SetHWIO_FuelInjectorEOIT( T_CRANK_ANGLE LfVIOS_FuelEOIT )
{
	uint32_t cs;

	cs = Enter_Critical_Section();
	PFI_Set_Angle( PFI_NORMAL_ANGLE, LfVIOS_FuelEOIT, 1<<S_CRANK_ANGLE );
	Leave_Critical_Section( cs );
}

//=============================================================================
// SetHWIO_FuelInjectorIllegalEOIT
//=============================================================================
void SetHWIO_FuelInjectorIllegalEOIT( void )
{
  uint32_t cs;

  cs = Enter_Critical_Section();
  PFI_Set_Illegal_Angle(PFI_NORMAL_ANGLE);
  Leave_Critical_Section( cs );
}


//=============================================================================
// SetHWIO_FuelInjectorPulseWidth
//=============================================================================
void SetHWIO_FuelInjectorPulseWidth( T_COUNT_BYTE LeHWIO_FuelInjChannel, T_MILLISECONDSb LfHWIO_t_PulseWidth )
{
    //This is newly added (from MT80)to support INJ cutoff when there is FAULT COUNTER THERESHOLD LIMIT IS REACHED.
   //if (false == (VSEP_Is_Channel_Fault_Threshold_Reach(VSEP_Get_Channel( MTSA_FAULT_INJ1.Configuration ) + (VSEP_Channel_T)(LeHWIO_FuelInjChannel))))
   if ( true )
   {
       PFI_Set_Pulse_Width(LeHWIO_FuelInjChannel, LfHWIO_t_PulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );

   }
   else
   {
       PFI_Set_Pulse_Width(  LeHWIO_FuelInjChannel, 0, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
   }
}

//=============================================================================
// SetHWIO_FuelInjectorTrimEOIT
//=============================================================================
void SetHWIO_FuelInjectorTrimEOIT( T_CRANK_ANGLE LfVIOS_FuelTrimEOIT )
{
   PFI_Set_Angle(  PFI_TRIM_ANGLE, LfVIOS_FuelTrimEOIT, 1<<S_CRANK_ANGLE );
}

//=============================================================================
// SetHWIO_InjectorOffset
//=============================================================================
void SetHWIO_InjectorOffset( T_MILLISECONDSb LfHWIO_FuelInjectorOffset )
{
   PFI_Set_Injector_Offset( LfHWIO_FuelInjectorOffset, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
}

//=============================================================================
// SetHWIO_MinInjectorOffTime
//=============================================================================
void SetHWIO_MinInjectorOffTime( T_MILLISECONDSb LfHWIO_FuelMinInjectorOffTime )
{
   PFI_Set_Minimum_Off_Time(  LfHWIO_FuelMinInjectorOffTime, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
}

//=============================================================================
// SetHWIO_MinTrimPulseWidth
//=============================================================================
void SetHWIO_MinTrimPulseWidth( T_MILLISECONDSb LfHWIO_FuelMinTrimPulseWidth )
{
   PFI_Set_Min_Trim_Pulse_Width( LfHWIO_FuelMinTrimPulseWidth, S_MILLISECONDSb, MILLISECOND_RESOLUTION );
}

//=============================================================================
// SetHWIO_SequentialFuelMode
//=============================================================================
void SetHWIO_SequentialFuelMode( uint8_t SeqModeDelayCtr )
{
   PFI_Set_Fueling_Mode( CeSEQUENTIAL, SeqModeDelayCtr );
}

//=============================================================================
// SetHWIO_SimultaneousFuelMode
//=============================================================================
void SetHWIO_SimultaneousFuelMode( void )
{
   PFI_Set_Update_Enable(false) ;//this will set Update Enable to false.
   PFI_Set_Fueling_Mode(CeSIMULTANEOUS, 0 );
}

//=============================================================================
// UpdateHWIO_PrimePulseComplete
//=============================================================================
void UpdateHWIO_PrimePulseComplete( void )
{
   PFI_Update_Prime_Pulse_Complete();
}


//=============================================================================
// GetHWIO_PrimePulseComplete
//=============================================================================
TbBOOLEAN GetHWIO_PrimePulseComplete( void )
{
   return (TbBOOLEAN)PFI_Flags.Prime_Pulse_Complete;
}

//=============================================================================
// ClrHWIO_PrimePulseComplete
//=============================================================================
void ClrHWIO_PrimePulseComplete( void )
{
   PFI_Flags.Prime_Pulse_Complete = false;
}

//=============================================================================
// SetHWIO_PrimePulseComplete
//=============================================================================
void SetHWIO_PrimePulseComplete( void )
{
   PFI_Flags.Prime_Pulse_Complete = true;
}

//=============================================================================
// SetHWIO_FuelSqSwitch
//=============================================================================
void SetHWIO_FuelSqSwitch( TbBOOLEAN LbHWIO_FuelSqSwitch )
{
   PFI_Set_Update_Enable( ( LbHWIO_FuelSqSwitch ?  false : true ) );
}

