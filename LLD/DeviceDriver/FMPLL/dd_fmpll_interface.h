#ifndef DD_FMPLL_INTERFACE_H
#define DD_FMPLL_INTERFACE_H

#include "dd_fmpll.h"



//=============================================================================
// Function to initialize the FM PLL.
// This function accepts a 32-bit value that is formatted in the same
//  manner as the FMPLL[SYNCR] register. It then parses the 32-bit value
//  and writes the FMPLL[SYNCR] register in the proper sequence to
//  initialize or change the FMPLL.
// @param io_config IO_Configuration_T - an FMPLL[SYNCR] value.
//
// @return none
//
// @par EXTERNAL REFERENCES:
//  Disables interrupts while executing. If the PLL has problems LOCKing,
//   this function could cause the CPU to reset ( if a watchdog timer
//   is enabled and running before this function it called ). 
//
// @par DEVIATIONS FROM STANDARDS:
//   None.
//
// @par Preconditions:
//   The user must understand that calling this function to change the PLL
//    will change the system clock frequency and affect all other submodule
//    timers and any devices on the external system bus or that use the
//    clkout clock.
//
// @par Postconditions:
//   FMPLL will be initialized and the system clock may be different than when
//    this function was called. The system clock may be FM as well.
//=============================================================================
extern void FMPLL_Initialize_Device(void);



#endif // DD_FMPLL_INTERFACE_H
