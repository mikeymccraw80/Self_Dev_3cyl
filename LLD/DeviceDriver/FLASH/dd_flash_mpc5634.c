//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================

#include "dd_flash_mpc5634.h"

//===========================================================================
//  Local preprocessor #define constants (object-like macros)
//===========================================================================
#define FLASH_BIUCR_PFLIM_MASK  ((uint32_t)0x0000000E)

//===========================================================================
// !!! Note: Change this per the Flash_BIU_Initialize_From_RAM() size
//===========================================================================
#define FLASH_BIU_INITIALIZE_FROM_RAM_32BIT_SIZE 13  // 52 bytes

#define SECTION_FLASH_B0_REGISTER
#include "section.h"
FLASHB0_T FLASH_B0;
#define SECTION_END
#include "section.h"

#define SECTION_FLASH_B1A1_REGISTER
#include "section.h"
FLASHB1_T FLASH_B1A1;
#define SECTION_END
#include "section.h"

#define SECTION_FLASH_B1A2_REGISTER
#include "section.h"
FLASHB1_T FLASH_B1A2;
#define SECTION_END
#include "section.h"





//===========================================================================
// Function definitions
//===========================================================================
// !!!! never directly call function in this file if function is in ROM.
//      Shall run the function in RAM memory. Instead, just call
//      Flash_Initialize() in dd_flash.c that will care this for you.
//===========================================================================
void MPC5634_FLASH_BIU_Initialize(FLASH_BIUCR_T in_biucr, FLASH_BIUAPR_T in_biuapr)
{
  //=======================================================================
  // Memory is synchronized so all instructions preceding the write to
  // FLASH_B0.BIUCR is completed and pipeline is flushed.
  //=======================================================================
  MSYNC();

  FLASH_B0.BIUCR.U32 = in_biucr.U32;
  FLASH_B0.BIUAPR.U32 = in_biuapr.U32;

  ISYNC();
}
uint32_t ram_space[FLASH_BIU_INITIALIZE_FROM_RAM_32BIT_SIZE];
//===========================================================================
// Function definitions
//===========================================================================
void MPC5634_FLASH_Initialize(FLASH_Run_Mode_T  reprogram_mode )
{
   
   uint32_t* src;
   uint32_t  reg_value;

   void (*init)(FLASH_BIUCR_T in_biucr, FLASH_BIUAPR_T in_biuapr);

   FLASH_BIUCR_T biucr;
   FLASH_BIUAPR_T biapr;
      
   uint8_t i;
   uint8_t function_size;

   src = (uint32_t*)(MPC5634_FLASH_BIU_Initialize);

   init = (void *)ram_space;

   function_size =
            (uint8_t)(((uint32_t)MPC5634_FLASH_Initialize -
            (uint32_t)MPC5634_FLASH_BIU_Initialize) / sizeof(uint32_t));

   for ( i = 0; i < function_size; i++ )
   {
      ram_space[i] = src[i];
   }
   
   if (FLASH_RUN_MODE_NORMAL == reprogram_mode)
   {
	//Global Configuration Enable (Read/Write)
      //1: Use the contents of BIUCR to configure both Bank0 and Bank1 operation
      biucr.F.GCE= 0;
      //prefetching may be triggered by the processor core
      biucr.F.M0PFE = FLASH_PREFETCH_ENABLE;
	//No prefetching may be triggered by the NDI  
      biucr.F.M1PFE = FLASH_PREFETCH_DISABLE;
	 // prefetching may be triggered by the DMA module
      biucr.F.M2PFE = FLASH_PREFETCH_ENABLE;
	//This field is not implemented; it has no effect.
      biucr.F.M3PFE = FLASH_PREFETCH_DISABLE;
      //This field is used to control the number of cycles between pipelined access requests.
      //This field must be set to a value corresponding to the operating frequency and it must be the same value
      //as RWSC.
      // 010: Access requests require 2 additional hold cycles
      biucr.F.APC= FLASH_BIUCR_APC_THREE_HOLD_CYCLES;
	//Write Wait State Control (Read/Write)
	//This field is used to control the number of wait-states to be added to the best-case flash array access
       // time for writes.
	//01: 1 additional wait-state is added
      biucr.F.WWSC= FLASH_BIUCR_WWSC_ONE_WAIT_STATE;
        //Read Wait State Control (Read/Write)
	//This field is used to control the number of wait states to be added to the best-case flash array access
       //time for reads.
	//011: 3 additional wait-states are added
      biucr.F.RWSC= FLASH_BIUCR_RWSC_THREE_WAIT_STATES;
      //Data Prefetch Enable (Read/Write)
      //If page buffers are enabled (BFEN = 1), prefetching is triggered by any data read access
      biucr.F.DPFEN= FLASH_BIUCR_DPFEN_PREFETCH_ONLY_BY_BURST_READ;
      //Instruction Prefetch Enable (Read/Write)
      //If page buffers are enabled (BFEN = 1), prefetching is triggered by any instruction fetch read access
      biucr.F.IPFEN= FLASH_BIUCR_IPFEN_PREFETCH_BY_ANY_READ;  
       //Prefetch Limit (Read/Write)
      //1x: The referenced line is prefetched on a buffer miss, or the next sequential page is prefetched on a
      //buffer hit (if not already present), that is, prefetch on miss or hit.
      biucr.F.PFLIM= FLASH_BIUCR_PFLIM_UPTO_TWO_ADDITIONAL_LINES;
	
	//Buffer Enable (Read/Write)
      //The page buffers are enabled to satisfy read requests on hits. Buffer valid bits may be set when the
       //buffers are successfully filled.
      biucr.F.BFEN= 1;
   	}
   else
   	{
	//Global Configuration Enable (Read/Write)
      //1: Use the contents of BIUCR to configure both Bank0 and Bank1 operation
      biucr.F.GCE= 0;
      //prefetching may be triggered by the processor core
      biucr.F.M0PFE = FLASH_PREFETCH_DISABLE;
	//No prefetching may be triggered by the NDI  
      biucr.F.M1PFE = FLASH_PREFETCH_DISABLE;
	 // prefetching may be triggered by the DMA module
      biucr.F.M2PFE = FLASH_PREFETCH_DISABLE;
	//This field is not implemented; it has no effect.
      biucr.F.M3PFE = FLASH_PREFETCH_DISABLE;
      //This field is used to control the number of cycles between pipelined access requests.
      //This field must be set to a value corresponding to the operating frequency and it must be the same value
      //as RWSC.
      // 010: Access requests require 2 additional hold cycles
      biucr.F.APC= FLASH_BIUCR_APC_NO_ADDRESS_PIPELINE;
	//Write Wait State Control (Read/Write)
	//This field is used to control the number of wait-states to be added to the best-case flash array access
       // time for writes.
	//01: 1 additional wait-state is added
      biucr.F.WWSC= FLASH_BIUCR_WWSC_THREE_WAIT_STATES;
        //Read Wait State Control (Read/Write)
	//This field is used to control the number of wait states to be added to the best-case flash array access
       //time for reads.
	//011: 3 additional wait-states are added
      biucr.F.RWSC= FLASH_BIUCR_RWSC_SEVEN_WAIT_STATES;
      //Data Prefetch Enable (Read/Write)
      //If page buffers are enabled (BFEN = 1), prefetching is triggered by any data read access
      biucr.F.DPFEN= FLASH_BIUCR_DPFEN_PREFETCH_ONLY_BY_BURST_READ;
      //Instruction Prefetch Enable (Read/Write)
      //If page buffers are enabled (BFEN = 1), prefetching is triggered by any instruction fetch read access
      biucr.F.IPFEN= FLASH_BIUCR_IPFEN_PREFETCH_ONLY_BY_BURST_READ;  
       //Prefetch Limit (Read/Write)
      //1x: The referenced line is prefetched on a buffer miss, or the next sequential page is prefetched on a
      //buffer hit (if not already present), that is, prefetch on miss or hit.
      biucr.F.PFLIM= FLASH_BIUCR_PFLIM_NO_PREFETCH;
	
	//Buffer Enable (Read/Write)
      //The page buffers are enabled to satisfy read requests on hits. Buffer valid bits may be set when the
       //buffers are successfully filled.
      biucr.F.BFEN= 1;
   	}


  //Controls whether the e200z335 processor core is allowed to make read and write accesses to the flash.
  //11: Both read and write accesses may be performed by the processor core
   biapr.F.M0AP = FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS;

    //Controls whether the Nexus Development Interface (NDI) is allowed to make read and write accesses to the flash..
  //00: No accesses may be performed by the NDI
   biapr.F.M1AP = FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS;

  //Controls whether the DMA module is allowed to make read and write accesses to the flash.
  //11: Both read and write accesses may be performed by the DMA module
   biapr.F.M2AP = FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS;

   
   init( biucr, biapr);
  // MPC5634_FLASH_BIU_Initialize( biucr, biapr);
 
  
   //Write 1 to Clear EER and RWE bits
   reg_value = FLASH_B0.MCR.U32;
   reg_value = (reg_value & FLASH_EER_CLEAR_MASK);
   FLASH_B0.MCR.U32 = reg_value;

   reg_value = FLASH_B0.MCR.U32;
   reg_value = (reg_value & FLASH_RWE_CLEAR_MASK);
   FLASH_B0.MCR.U32 = reg_value;

}

//===========================================================================
// Function definitions
//===========================================================================
// Initialize flash controller to programming
//===========================================================================
void MPC5634_FLASH_Initialize_Programming(void)
{
   MPC5634_FLASH_Initialize(FLASH_RUN_MODE_REPROGRAMMING);
}

//===========================================================================
// Function definitions
//===========================================================================
// Initialize flash controller to normal
//===========================================================================
void MPC5634_FLASH_Initialize_Normal(void)
{
   MPC5634_FLASH_Initialize(FLASH_RUN_MODE_NORMAL);
}

