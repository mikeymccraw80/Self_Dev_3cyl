#ifndef DD_SWT_H
#define DD_SWT_H

#include "hw_swt.h"


//=============================================================================
// Register overlay of the submodule
//=============================================================================
#define SECTION_SWT_REGISTER
#include "section.h"
extern SWT_T SWT;
#define SECTION_END
#include "section.h"


typedef enum
{
   SWT_MASTERn_ACCESS_DISABLE,
   SWT_MASTERn_ACCESS_ENABLE
}SWT_Master_Access_T;


typedef enum
{
   SWT_NO_LOCK,
   SWT_SOFT_LOCK,
   SWT_HARD_LOCK,
   SWT_BOTH_LOCK
}SWT_Lock_Status_T;


typedef enum
{
   SWT_RESET_SOFT_LOCK,
   SWT_SET_SOFT_LOCK,
   SWT_SET_HARD_LOCK
}SWT_Lock_T;

typedef enum 
{
   SWT_FIXED_SERVICE_MODE,
   SWT_KEYED_SERVICE_MODE
}SWT_Service_Mode_T;



typedef enum
{
SWT_BUS_ERR,
SWT_SYSTEM_RESET
}SWT_Invalid_Access_Err_T;

typedef enum 
{
   SWT_REGULAR_MODE,
   SWT_WINDOW_MODE
}SWT_Window_Mode_T;


typedef enum 
{
   SWT_RESET_ON_TIMEOUT,
   SWT_INT_ON_TIMEOUT
}SWT_Action_Timeout_T;

typedef enum
{
   SWT_SYSTEM_CLOCK,
   SWT_OSCILLATOR_CLOCK
}SWT_Clock_Select_T;

typedef enum
{
   SWT_SOFT_LOCK_DISABLE,
   SWT_SOFT_LOCK_ENABLE
}SWT_Soft_Lock_T;

typedef enum
{
   SWT_HARD_LOCK_DISABLE,
   SWT_HARD_LOCK_ENABLE
}SWT_Hard_Lock_T;

typedef enum
{
   SWT_COUNTER_FREEZE_DISABLE,
   SWT_COUNTER_FREEZE_ENABLE
}SWT_Debug_Mode_Control_T;

typedef enum
{
   SWT_COUNTER_ENABLE_STOP,
   SWT_COUNTER_DISABLE_STOP
}SWT_Stop_Mode_Control_T;

typedef enum
{
   SWT_DISABLE,
   SWT_ENABLE
}SWT_ENABLE_T;




#endif // DD_SWT_H

