
/*==========================================================================*\
 * header files
\*==========================================================================*/
#include "dd_expection_handlers.h"
#include "dd_siu.h"
#include "dd_ecsm.h"
#include "hw_sprs_cu.h"




typedef enum
{
   Exception_Critical_Input = 0,
   Exception_Machine_Check,
   Exception_Data_Storage,
   Exception_Instruction_Storage,
   Exception_External_Interrupt,
   Exception_Alignment,
   Exception_Program,
   Exception_Fp_Unavailable,
   Exception_System_Call,
   Exception_Aux_Proc_Unavailable,
   Exception_Decrementer,
   Exception_Fixed_Interval_Timer,
   Exception_Watchdog,
   Exception_Data_Tlb,
   Exception_Instruction_Tlb,
   Exception_Debug,
   Exception_Spe_Apu_Unavail = 32,
   Exception_Spe_Fp_Data = 33,
   Exception_Spe_Fp_Round = 34,
   Exception_Illegal_Interrupt = 99

} Exception_T;


uint32_t Exception_Address;
uint32_t Exception_CPU_State;
uint32_t Exception_Detail;
uint32_t Exception_Data;
Exception_T Exception_Type;
INTC_EXCEPTION_Log_T INTC_EXCEPTION_Unhandled_Exception_Data;



void INTC_EXCEPTION_Halt( void )
{
   Disable_Interrupts();

   SIU.SRCR.F.SER = 1;
   SIU.SRCR.F.SSR = 1;

   while(1){}
}

uint32_t Get_Excepting_Address( void )
{
   return Exception_Address;
}

void Restore_Exception_Details( void )
{
   Exception_Detail = READ_SPR_VALUE( SPR_SPRG3 );
   Exception_CPU_State = READ_SPR_VALUE( SPR_SPRG4 );
   Exception_Address = READ_SPR_VALUE( SPR_SPRG5 );
   Exception_Data = READ_SPR_VALUE( SPR_SPRG6 );
   Exception_Type = (short) READ_SPR_VALUE( SPR_SPRG7 );
}

void Save_Exception_Details( void )
{
   STORE_SPR_VALUE_VAR( SPR_SPRG3, Exception_Detail );
   STORE_SPR_VALUE_VAR( SPR_SPRG4, Exception_CPU_State );
   STORE_SPR_VALUE_VAR( SPR_SPRG5, Exception_Address );
   STORE_SPR_VALUE_VAR( SPR_SPRG6, Exception_Data );
   STORE_SPR_VALUE_VAR( SPR_SPRG7, Exception_Type );
}

void Exception_Critical_Input_ISR( void )
{
   /* IVOR0 is not used in MPC5553/MPC5554 - but we have a handler anyway */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_CSRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_CSRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Critical_Input;

   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Machine_Check_ISR( void )
{
   /* IVOR1 */

   /* Check to see if machine check caused by a Cache Parity Error. */
   if ( READ_SPR_VALUE( SPR_MCSR ) & 0x10000000 )
   {
      //Service_Cache_Parity_Error();
   }
   else
   {
      /* Not caused by a Cache Parity error so capture data and halt. */

      /* Save the cause of the exception.  */
      Exception_Detail = READ_SPR_VALUE( SPR_ESR );
      /* Save the MSR value before this exception occurred.  */
      Exception_CPU_State = READ_SPR_VALUE( SPR_CSRR1 );
      /*
       * Save address of next instruction - after the one that caused
       * this exception.
       */
      Exception_Address = READ_SPR_VALUE( SPR_CSRR0 );
      Exception_Data = 0;
      Exception_Type = Exception_Machine_Check;
      Save_Exception_Details();

      INTC_EXCEPTION_Halt();
   }
}

void Exception_Data_Storage_ISR( void )
{
   /* IVOR2 */
   uint32_t temp_DEAR;
   uint32_t temp_SRR0;
   uint32_t temp_ESR = READ_SPR_VALUE( SPR_ESR );

   /* Check to see if data storage exception caused by ECC Error Detection. */
   if ( ( temp_ESR & 0x00000001 ) && ( ECSM.ESR.F.RNCE || ECSM.ESR.F.FNCE ) )
   {
      //Service_ECSM_Error();
   }
   /* Check to see if exception was caused by MMU write protect access. */
   else if ( ( temp_ESR & 0x00800080 ) &&
             ( ( temp_ESR & 0xFF7FFF7F ) == 0x00000000 ) )
   {
      temp_DEAR = READ_SPR_VALUE( SPR_DEAR );
      temp_SRR0 = READ_SPR_VALUE( SPR_SRR0 );

      /* Report the fault to the application. */
      //Report_Write_Protected_Fault( temp_DEAR, temp_SRR0 );
   }
   else
   {
      /* Not caused by an ECC or Write Protect error so capture data and halt. */

      /* Save the cause of the exception.  */
      Exception_Detail = READ_SPR_VALUE( SPR_ESR );
      /* Save the MSR value before this exception occurred.  */
      Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
      /*
       * Save address of next instruction - after the one that caused
       * this exception.
       */
      Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
      Exception_Data = 0;
      Exception_Type = Exception_Data_Storage;
      Save_Exception_Details();

      INTC_EXCEPTION_Halt();
   }

   /* Clear DEAR register for future exception processing. */
   temp_DEAR = 0;
   STORE_SPR_VALUE_VAR( SPR_DEAR, temp_DEAR );
}

void Exception_Instruction_Storage_ISR( void )
{
   /* IVOR3 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Instruction_Storage;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_External_Interrupt_ISR( void)
{
   /* IVOR4 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_External_Interrupt;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Alignment_ISR( void )
{
   /* IVOR5 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = READ_SPR_VALUE( SPR_DEAR );
   Exception_Type = Exception_Alignment;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Program_ISR( void)
{
   /* IVOR6 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Program;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Fp_Unavailable_ISR( void )
{
   /* IVOR7 */
   /* Save the cause of the exception.  */
   /* ESR not necessary for FP Unavailable, but it won't hurt to save it */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Fp_Unavailable;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_System_Call_ISR( void )
{
   /* IVOR8 */
   /* Save the cause of the exception.  */
   /* ESR not necessary for System Call, but it won't hurt to save it */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_System_Call;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Aux_Proc_Unavailable_ISR( void )
{
   /* IVOR9 */
   /* Save the cause of the exception.  */
   /*
    * ESR not necessary for Aux Processor Unavailable,
    * but it won't hurt to save it
    */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Aux_Proc_Unavailable;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Decrementer_ISR( void )
{
   /* IVOR10 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_TSR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Decrementer;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Fixed_Interval_Timer_ISR(void )
{
   /* IVOR11 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_TSR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Fixed_Interval_Timer;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Watchdog_ISR( void )
{
   /* IVOR12 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_TSR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Watchdog;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Data_Tlb_ISR( void )
{
   /* IVOR13 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = READ_SPR_VALUE( SPR_DEAR );
   Exception_Type = Exception_Data_Tlb;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Instruction_Tlb_ISR( void )
{
   /* IVOR14 */
   /* Save the cause of the exception.  */
   /*
    * ESR not necessary for Instruction TLB,
    * but it won't hurt to save it
    */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Instruction_Tlb;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Debug_ISR( void )
{
   /* IVOR15 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_DBSR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_CSRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_CSRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Debug;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Spe_Apu_Unavail_ISR( void )
{
   /* IVOR32 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_Spe_Apu_Unavail;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}


void Exception_Spe_Fp_Unavailable_ISR( void )
{
   /* IVOR34 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = READ_SPR_VALUE( SPR_SPEFSCR );
   Exception_Type = Exception_Spe_Fp_Round;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}
void Exception_Spe_Fp_Round_ISR( void )
{
   /* IVOR34 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = READ_SPR_VALUE( SPR_SPEFSCR );
   Exception_Type = Exception_Spe_Fp_Data;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

void Exception_Illegal_Interrupt_ISR( void )
{
   /* IVOR4 */
   /* Save the cause of the exception.  */
   Exception_Detail = READ_SPR_VALUE( SPR_ESR );
   /* Save the MSR value before this exception occurred.  */
   Exception_CPU_State = READ_SPR_VALUE( SPR_SRR1 );
   /*
    * Save address of next instruction - after the one that caused
    * this exception.
    */
   Exception_Address = READ_SPR_VALUE( SPR_SRR0 );
   Exception_Data = 0;
   Exception_Type = Exception_External_Interrupt;
   Save_Exception_Details();

   INTC_EXCEPTION_Halt();
}

 void INTC_EXCEPTION_Default_Handler( uint32_t in_exception_id)
{
   INTC_EXCEPTION_Unhandled_Exception_Data.exception_id = in_exception_id;
   INTC_EXCEPTION_Unhandled_Exception_Data.srr0 = READ_SPR_VALUE ( SPR_SRR0 );
   INTC_EXCEPTION_Unhandled_Exception_Data.srr1 = READ_SPR_VALUE ( SPR_SRR1 );
   INTC_EXCEPTION_Unhandled_Exception_Data.csrr0 = READ_SPR_VALUE ( SPR_CSRR0 ); 
   INTC_EXCEPTION_Unhandled_Exception_Data.csrr1 = READ_SPR_VALUE ( SPR_CSRR1 );
   INTC_EXCEPTION_Unhandled_Exception_Data.dsrr0 = READ_SPR_VALUE ( SPR_DSRR0 );
   INTC_EXCEPTION_Unhandled_Exception_Data.dsrr1 = READ_SPR_VALUE ( SPR_DSRR1 );
   INTC_EXCEPTION_Unhandled_Exception_Data.esr = READ_SPR_VALUE ( SPR_ESR );
   INTC_EXCEPTION_Unhandled_Exception_Data.mcsr = READ_SPR_VALUE ( SPR_MCSR );
   INTC_EXCEPTION_Unhandled_Exception_Data.dear = READ_SPR_VALUE ( SPR_DEAR  );
   INTC_EXCEPTION_Halt();
}

