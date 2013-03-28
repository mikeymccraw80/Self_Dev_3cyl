#include "reuse.h"
#include "hw_sprs_cu.h"
#include "e200z3.h"



void INTC_EXCEPTION_Critical_Input(void);
void INTC_EXCEPTION_Machine_Check(void);
void INTC_EXCEPTION_Data_Storage(void);
void INTC_EXCEPTION_Instruction_Storage(void);
void INTC_Interrupt_Handler( void );
void INTC_EXCEPTION_Alignment(void);
void INTC_EXCEPTION_Program(void);
void INTC_EXCEPTION_Floating_Point_Unavailable(void);
void INTC_EXCEPTION_System_Call(void);
void INTC_EXCEPTION_Auxiliary_Processor_Unavailable(void);
void INTC_EXCEPTION_Decrementer(void);
void INTC_EXCEPTION_Fixed_Interval_Timer_ISR(void);
void INTC_EXCEPTION_Watchdog_Timer_Interrupt(void);
void INTC_EXCEPTION_Data_TLB_Error(void);
void INTC_EXCEPTION_Instruction_TLB_Error(void);
void INTC_EXCEPTION_Debug(void);
void INTC_EXCEPTION_SPE_APU_Unavailable(void);
void INTC_EXCEPTION_SPE_Floating_Point_Data(void);
void INTC_EXCEPTION_SPE_Floating_Point_Round(void);




void INTC_Exception_Initialize( void* in_table )
{
   // Save exception table start address to IVPR for exception
   //  table base address.
   STORE_SPR_VALUE_VAR(IVPR_SPR, ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR0_SPR, ( uint32_t )&INTC_EXCEPTION_Critical_Input - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR1_SPR, ( uint32_t )&INTC_EXCEPTION_Machine_Check - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR2_SPR, ( uint32_t )&INTC_EXCEPTION_Data_Storage - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR3_SPR, ( uint32_t )&INTC_EXCEPTION_Instruction_Storage - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR4_SPR, ( uint32_t )&INTC_Interrupt_Handler - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR5_SPR, ( uint32_t )&INTC_EXCEPTION_Alignment - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR6_SPR, ( uint32_t )&INTC_EXCEPTION_Program - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR7_SPR, ( uint32_t )&INTC_EXCEPTION_Floating_Point_Unavailable - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR8_SPR, ( uint32_t )&INTC_EXCEPTION_System_Call - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR9_SPR, ( uint32_t )&INTC_EXCEPTION_Auxiliary_Processor_Unavailable - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR10_SPR,( uint32_t )&INTC_EXCEPTION_Decrementer - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR11_SPR,( uint32_t )&INTC_EXCEPTION_Fixed_Interval_Timer_ISR - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR12_SPR,( uint32_t )&INTC_EXCEPTION_Watchdog_Timer_Interrupt - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR13_SPR,( uint32_t )&INTC_EXCEPTION_Data_TLB_Error - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR14_SPR,( uint32_t )&INTC_EXCEPTION_Instruction_TLB_Error - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR15_SPR,( uint32_t )&INTC_EXCEPTION_Debug - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR32_SPR,( uint32_t )&INTC_EXCEPTION_SPE_APU_Unavailable - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR33_SPR,( uint32_t )&INTC_EXCEPTION_SPE_Floating_Point_Data - ( uint32_t )in_table);
   STORE_SPR_VALUE_VAR(IVOR34_SPR,( uint32_t )&INTC_EXCEPTION_SPE_Floating_Point_Round - ( uint32_t )in_table);
}


