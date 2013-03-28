#include "dd_intc.h"
#include "dd_expection_handlers.h"


// Compiler option to place functions at least 16 bytes apart.
// This is necessary, because the IVORx registers that point to
// each of these functions for each exception do not use the
// lower four bits for the offset address to these functions.
#pragma option -Xalign-functions=16

INTERRUPT void INTC_EXCEPTION_SPE_APU_Unavailable(void)
{
  Exception_Spe_Apu_Unavail_ISR();
}
