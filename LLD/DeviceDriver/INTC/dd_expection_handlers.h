#ifndef DD_EXCEPTION_HANDLERS_H
#define DD_EXCEPTION_HANDLERS_H

/*==========================================================================*\
 * header files
\*==========================================================================*/
#include "reuse.h"
#include "dd_intc.h"

/*==========================================================================*\
 * Global Variables
\*==========================================================================*/

/*==========================================================================*\
 * header files
\*==========================================================================*/

extern void Exception_Critical_Input_ISR( void);

extern void Exception_Machine_Check_ISR( void );

extern void Exception_Data_Storage_ISR( void);

extern void Exception_Instruction_Storage_ISR( void);

extern void Exception_External_Interrupt_ISR( void);

extern void Exception_Alignment_ISR( void );

extern void Exception_Program_ISR( void);

extern void Exception_Fp_Unavailable_ISR( void );

extern void Exception_System_Call_ISR( void );

extern void Exception_Aux_Proc_Unavailable_ISR( void);

extern void Exception_Decrementer_ISR( void );

extern void Exception_Fixed_Interval_Timer_ISR( void);

extern void Exception_Watchdog_ISR( void);

extern void Exception_Data_Tlb_ISR( void );

extern void Exception_Instruction_Tlb_ISR( void);

extern void Exception_Debug_ISR( void );

extern void Exception_Spe_Apu_Unavail_ISR( void );

extern void  Exception_Spe_Fp_Unavailable_ISR( void );

extern void Exception_Spe_Fp_Round_ISR( void );

extern  void INTC_EXCEPTION_Default_Handler(  uint32_t in_exception_id);

void Restore_Exception_Details( void );

uint32_t Get_Excepting_Address( void );


#endif

