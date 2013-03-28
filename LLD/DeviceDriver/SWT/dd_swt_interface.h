#ifndef DD_INTERFACE_H
#define DD_INTERFACE_H

#include "dd_swt.h"

//=============================================================================
// SWT_Timer_Set_Timeout_Value
//
// @func Modifies the WatchDog timeout value based on the configurations defined by
// the user.
//
// @parm uint32_t | timeout value | The timeout value  for 
//watch dog 
//
// @end
//=============================================================================
extern void SWT_Set_Timeout_Value( uint32_t time);


//=============================================================================
// SWT_Service_WatchDog
//
// @func Services the SWT
//
// @parm None
//
// @end
//=============================================================================

extern void SWT_Service_WatchDog(void);

#endif

