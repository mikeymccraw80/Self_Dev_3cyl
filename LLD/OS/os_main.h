#ifndef OS_MAIN_H
#define OS_MAIN_H

//=============================================================================
// type define
//=============================================================================
/* Data Types */
typedef enum
{
   AM_normal,
   AM_HardwareTest,
   AM_ManufacturingTest
}AppModeType_T;

//=============================================================================
//StartOS
//=============================================================================
void StartOS(AppModeType_T Mode);

#endif

