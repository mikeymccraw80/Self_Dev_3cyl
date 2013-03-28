#ifndef DD_SIU_INTERFACE_H
#define DD_SIU_INTERFACE_H

//=============================================================================
//                                Includes
//=============================================================================

#include "dd_siu.h"

//=============================================================================
//                                extern init  function
//=============================================================================
extern void SIU_Initialize_Device(void );

//=============================================================================
//                                extern init  function
//=============================================================================
extern void SIU_GPIO_Initialize_Device( void );

//=============================================================================
// SIU_GPIO_DISCRETE_Set_State
//=============================================================================
INLINE void SIU_GPIO_DISCRETE_Set_State(
   SIU_GPIO_Channel_T channel,
   bool                 in_state )
{
   SIU.GPDO[channel].F.PDO = in_state;
}

//=============================================================================
// SIU_GPIO_DISCRETE_Get_State_Local
//=============================================================================
INLINE bool SIU_GPIO_DISCRETE_Get_State(SIU_GPIO_Channel_T channel )
{
  // bool                       channel_state;

   // get the current value
  // The SIU_GPDIx_x registers are read-only registers that allow software to read the input state of an external
  //GPIO pin. Each byte of a register represents the input state of a single external GPIO pin. If the GPIO pin
  //is configured as an output, and the input buffer enable (IBE) bit is set in the associated Pad Configuration
  //Register, the SIU_GPDIx_x register reflects the actual state of the output pin.
  // channel_state = SIU.GPDI[channel].F.PDI;

   return SIU.GPDO[channel].F.PDO;
}


//#define  SIU_GPIO_DISCRETE_Get_State( ch )  (SIU.GPDI[siu_ch].F.PDI)
//=============================================================================
// SIU_GPIO_DISCRETE_Toggle_State
//=============================================================================
INLINE void SIU_GPIO_DISCRETE_Toggle_State(SIU_GPIO_Channel_T channel )
{
   // Get the current state of the output pin and toggle
   bool state = ( SIU_GPIO_DISCRETE_Get_State( channel ) == false ) ? true : false;

   // Set output to the toggled state
   SIU_GPIO_DISCRETE_Set_State( channel, state );
}

#endif // DD_SIU_INTERFACE_H

