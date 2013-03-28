#include "dd_intc.h"
#include "dd_expection_handlers.h"


// Compiler option to place functions at least 16 bytes apart.
// This is necessary, because the IVORx registers that point to
// each of these functions for each exception do not use the
// lower four bits for the offset address to these functions.
#pragma option -Xalign-functions=16

// Compiler option to use rfci for returning from critical interrupt.
#pragma option -Xinterrupt-funcs-use-rfci

INTERRUPT void INTC_EXCEPTION_Critical_Input(void)
{
       Exception_Critical_Input_ISR();
}

