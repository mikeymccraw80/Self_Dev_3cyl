//=============================================================================
// include files
//=============================================================================
#include "reuse.h"
#include "io_init.h"
#include "mg_main.h"

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
static int app_selection;
void main(void)
{
    int Mode = AM_ManufacturingTest;
    InitializeHardwareRegisters();
    InitializeHardwareLast();

    // if (InitializeIllegalConditionCheck() == false) {
    if (app_selection == 0) {
        Mode = AM_normal;
    } else {
        Mode = AM_ManufacturingTest;
    }

    //go into os schedule, event and time schedule
    if( Mode == AM_normal ) {
        StartOS_Task_Normal();
    } else if (Mode == AM_ManufacturingTest){
        mg_main();
    } else {
        while(1);
    }

    exit();
}
