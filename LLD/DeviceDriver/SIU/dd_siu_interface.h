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
extern void SIU_GPIO_DISCRETE_Set_State(
   SIU_GPIO_Channel_T channel,
   bool                 in_state );

//=============================================================================
// SIU_GPIO_DISCRETE_Get_State_Local
//=============================================================================
extern bool SIU_GPIO_DISCRETE_Get_State(SIU_GPIO_Channel_T channel );

//=============================================================================
// SIU_GPIO_DISCRETE_Toggle_State
//=============================================================================
extern void SIU_GPIO_DISCRETE_Toggle_State(SIU_GPIO_Channel_T channel );
//=============================================================================
// SIU_GPIO_DISCRETE_Get_State_Local
//=============================================================================
 void SIU_GPIO_Output_Confige(SIU_GPIO_Channel_T channel, bool enable );

#endif // DD_SIU_INTERFACE_H

