#include "dd_intc.h"
#include "dd_expection_handlers.h"

// Compiler option to place functions at least 16 bytes apart.
// This is necessary, because the IVORx registers that point to
// each of these functions for each exception do not use the
// lower four bits for the offset address to these functions.
#pragma option -Xalign-functions=16

///////////////////////////////////////////////////////////////////////////////
// INTC_Interrupt_Handler - IVOR4
///////////////////////////////////////////////////////////////////////////////

 INTC_Channel_T channel;
const INTC_Vector_Callback_T* pVector ;
INTERRUPT void INTC_Interrupt_Handler( void )
{
  // INTC_Channel_T channel = ( INTC_Channel_T )(INTC.IACKR_PRC0.F.INTVEC );
   //const INTC_Vector_Callback_T* pVector = &INTC_Vector_Table[ channel ];

  channel = ( INTC_Channel_T )(INTC.IACKR_PRC0.F.INTVEC );
  pVector = &INTC_Vector_Table[ channel ];
   INTC_External_Interrupt_Prologue(  );
   
   if(INTC_Vector_Table[ channel ] != NULL )
   {
      INTC_Vector_Table[ channel ]();
   }

   NOP();
   NOP();
   INTC_External_Interrupt_Epilogue(  );
}



