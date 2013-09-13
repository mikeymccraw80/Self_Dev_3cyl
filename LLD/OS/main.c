//=============================================================================
// include files
//=============================================================================
#include "reuse.h"
#include "io_init.h"

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
// function define
//=============================================================================
extern void StartOS_Task_Normal(void);
extern void exit(void);

//=============================================================================
// main
//
// Implementation Characteristics:
//
//
//=============================================================================


void main(void)
{
    int Mode = AM_normal;
    InitializeHardwareRegisters();
    InitializeHardwareLast();

    //go into os schedule, event and time schedule
    if( Mode == AM_normal ) {
        StartOS_Task_Normal();
    } else {
        while(1);
    }

    exit();
}








