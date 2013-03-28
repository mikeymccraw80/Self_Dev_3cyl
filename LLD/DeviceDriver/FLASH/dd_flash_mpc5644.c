
//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================

#include "dd_flash_mpc5644.h"
#include "dd_flash_init_mpc5644.h"

//===========================================================================
//  Local preprocessor #define constants (object-like macros)
//===========================================================================
#define FLASH_BIUCR_PFLIM_MASK  ((uint32_t)0x00000006)

//===========================================================================
// !!! Note: Change this per the Flash_BIU_Initialize_From_RAM() size
//===========================================================================
#define FLASH_BIU_INITIALIZE_FROM_RAM_32BIT_SIZE  13  // 52 bytes

#define SECTION_FLASH_A_REGISTER
#include "section.h"
FLASH_T FLASH_A;
#define SECTION_END

#define SECTION_FLASH_B_REGISTER
#include "section.h"
FLASH_T FLASH_B;
#define SECTION_END
#include "section.h"

static const FLASH_T* const Flash_Devices[ FLASH_INDEX_MAX ] =
{
   &FLASH_A,
   &FLASH_B
};

//===========================================================================
// Function definitions
//===========================================================================
// !!!! never directly call function in this file if function is in ROM.
//      Shall run the function in RAM memory. Instead, just call
//      Flash_Initialize() in dd_flash.c that will care this for you.
//===========================================================================
void MPC5644_FLASH_BIU_Initialize(
   FLASH_BIUCR1_T in_biucr1,
   FLASH_BIUCR2_T in_biucr2, 
   FLASH_BIUAPR_T in_biuapr )
{
 //=======================================================================
  // Memory is synchronized so all instructions preceding the write to
  // FLASH.BIUCR is completed and pipeline is flushed.
  //=======================================================================
  
   MSYNC();
   FLASH_A.BIUCR1.U32 = in_biucr1.U32;
   FLASH_A.BIUCR2.U32 = in_biucr2.U32;
   FLASH_A.BIUAPR.U32 = in_biuapr.U32;
   ISYNC();
}
   static uint32_t FLASH_Ram_Space[FLASH_BIU_INITIALIZE_FROM_RAM_32BIT_SIZE];
//===========================================================================
// Function definitions
//===========================================================================
void MPC5644_FLASH_Initialize(FLASH_Run_Mode_T reprogram_mode, FLASH_INDEX_T  device_index )
{
   FLASH_T *pFLASH;
   
   uint32_t* src;
   uint32_t  reg_value;

   void (*init)(FLASH_BIUCR1_T in_biucr1, FLASH_BIUCR2_T in_biucr2, FLASH_BIUAPR_T in_biuapr);

   FLASH_BIUCR1_T biucr1;
   FLASH_BIUCR2_T biucr2;
   FLASH_BIUAPR_T biapr;
      
   uint8_t i;
   uint8_t function_size;

   if (device_index == FLASH_DEVICE_A)
   {
       src = (uint32_t*)(MPC5644_FLASH_BIU_Initialize);
       init = (void *)FLASH_Ram_Space;
       function_size =
                (uint8_t)(((uint32_t)MPC5644_FLASH_Initialize -
                (uint32_t)MPC5644_FLASH_BIU_Initialize) / sizeof(uint32_t));


       for ( i = 0; i < function_size; i++ )
       {
          FLASH_Ram_Space[i] = src[i];
       }

       if (FLASH_RUN_MODE_NORMAL == reprogram_mode)
       {

          //Master n prefetch enable
          //FlexRay
	   biucr1.F.M6PFE= FLASH_PREFETCH_DISABLE;
          //eDMA
	   biucr1.F.M4PFE= FLASH_PREFETCH_ENABLE;
	   //z4 Core Load/Store
	   biucr1.F.M1PFE=FLASH_PREFETCH_ENABLE ;
	   //z4 Core Instruction
	   biucr1.F.M0PFE= FLASH_PREFETCH_ENABLE;
	  // Address Pipelining Control
         //000: Accesses may be pipelined back-to-back
         //001: Access requests require one additional hold cycle
         //010: Access requests require two additional hold cycles
         //...
         //110: Access requests require six additional hold cycles
         //111: No address pipelining
	   biucr1.F.APC= FLASH_BIUCR_APC_THREE_HOLD_CYCLES ;
	  //00: No additional wait-states are added
         //01: 1 additional wait-state is added
         //10: 2 additional wait-states are added
         //11: 3 additional wait-states are added
	   biucr1.F.WWSC= FLASH_BIUCR_WWSC_ONE_WAIT_STATE;
	  //000: No additional wait-states are added
         //001: 1 additional wait-state is added
         //010: 2 additional wait-states are added
         //011: 3 additional wait-states are added
         //100: 4 additional wait-states are added
         //101: 5 additional wait-states are added
         //110: 6 additional wait-states are added
         //111: 7 additional wait-states are added
	   biucr1.F.RWSC=FLASH_BIUCR_RWSC_THREE_WAIT_STATES ;
	 // 0: No prefetching is triggered by a data read access
        //1: If page buffers are enabled (BFEN = 1), prefetching is triggered by any data read access
	   biucr1.F.DPFEN=FLASH_BIUCR_DPFEN_PREFETCH_BY_ANY_READ ;
	 //0: No prefetching is triggered by an instruction fetch read access
        //1: If page buffers are enabled (BFEN = 1), prefetching is triggered by any instruction fetch read access
	   biucr1.F.IPFEN= FLASH_BIUCR_IPFEN_PREFETCH_BY_ANY_READ;
	 //00: No prefetching is performed.
        //01: The referenced line is prefetched on a buffer miss, that is, prefetch on miss.
        //1x: The referenced line is prefetched on a buffer miss, or the next sequential page is prefetched on a
        //buffer hit (if not already present), that is, prefetch on miss or hit.
	   biucr1.F.PFLIM= FLASH_BIUCR_PFLIM_PREFETCH_ON_MISS_OR_HIT;
	 //0: The page buffers are disabled from satisfying read requests, and all buffer valid bits are cleared.
        //1: The page buffers are enabled to satisfy read requests on hits. Buffer valid bits may be set when the
        //buffers are successfully filled.
	   biucr1.F.BFEN=1 ;
	 //00: All four buffers are available for any flash access, that is, there is no partitioning of the buffers
        //based on the access type.
        //01: Reserved
        //10: The buffers are partitioned into two groups with buffers 0 and 1 allocated for instruction fetches
        //and buffers 2 and 3 for data accesses.
        //11: The buffers are partitioned into two groups with buffers 0,1,2 allocated for instruction fetches and
        //buffer 3 for data accesses.
       
          biucr2.F.LBCFG = FLASH_BIUCR2_ALL_BUFFERS_FOR_FLASH_ACCESS ;
				  
       }
       else
       {
          //Master n prefetch enable
          //FlexRay
	   biucr1.F.M6PFE= FLASH_PREFETCH_DISABLE;
          //eDMA
	   biucr1.F.M4PFE= FLASH_PREFETCH_DISABLE;
	   //z4 Core Load/Store
	   biucr1.F.M1PFE=FLASH_PREFETCH_DISABLE ;
	   //z4 Core Instruction
	   biucr1.F.M0PFE= FLASH_PREFETCH_DISABLE;
	  // Address Pipelining Control
         //000: Accesses may be pipelined back-to-back
         //001: Access requests require one additional hold cycle
         //010: Access requests require two additional hold cycles
         //...
         //110: Access requests require six additional hold cycles
         //111: No address pipelining
	   biucr1.F.APC= FLASH_BIUCR_APC_THREE_HOLD_CYCLES ;
	  //00: No additional wait-states are added
         //01: 1 additional wait-state is added
         //10: 2 additional wait-states are added
         //11: 3 additional wait-states are added
	   biucr1.F.WWSC= FLASH_BIUCR_WWSC_ONE_WAIT_STATE;
	  //000: No additional wait-states are added
         //001: 1 additional wait-state is added
         //010: 2 additional wait-states are added
         //011: 3 additional wait-states are added
         //100: 4 additional wait-states are added
         //101: 5 additional wait-states are added
         //110: 6 additional wait-states are added
         //111: 7 additional wait-states are added
	   biucr1.F.RWSC=FLASH_BIUCR_RWSC_THREE_WAIT_STATES ;
	 // 0: No prefetching is triggered by a data read access
        //1: If page buffers are enabled (BFEN = 1), prefetching is triggered by any data read access
	   biucr1.F.DPFEN=FLASH_BIUCR_DPFEN_PREFETCH_BY_ANY_READ ;
	 //0: No prefetching is triggered by an instruction fetch read access
        //1: If page buffers are enabled (BFEN = 1), prefetching is triggered by any instruction fetch read access
	   biucr1.F.IPFEN= FLASH_BIUCR_IPFEN_PREFETCH_BY_ANY_READ;
	 //00: No prefetching is performed.
        //01: The referenced line is prefetched on a buffer miss, that is, prefetch on miss.
        //1x: The referenced line is prefetched on a buffer miss, or the next sequential page is prefetched on a
        //buffer hit (if not already present), that is, prefetch on miss or hit.
	   biucr1.F.PFLIM= FLASH_BIUCR_PFLIM_NO_PREFETCH;
	 //0: The page buffers are disabled from satisfying read requests, and all buffer valid bits are cleared.
        //1: The page buffers are enabled to satisfy read requests on hits. Buffer valid bits may be set when the
        //buffers are successfully filled.
	   biucr1.F.BFEN=1 ;
	 //00: All four buffers are available for any flash access, that is, there is no partitioning of the buffers
        //based on the access type.
        //01: Reserved
        //10: The buffers are partitioned into two groups with buffers 0 and 1 allocated for instruction fetches
        //and buffers 2 and 3 for data accesses.
        //11: The buffers are partitioned into two groups with buffers 0,1,2 allocated for instruction fetches and
        //buffer 3 for data accesses.
       
          biucr2.F.LBCFG = FLASH_BIUCR2_ALL_BUFFERS_FOR_FLASH_ACCESS ;
       }

      //00: No accesses may be performed by this master
      //01: Only read accesses may be performed by this master
      //10: Only write accesses may be performed by this master
     //11: Both read and write accesses may be performed by this master
      //FlexRay
      biapr.F.M6AP =  FLASH_BIUCR_MASTER_AP_NO_ACCESS;
      //eDMA
      biapr.F.M4AP =  FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS;
      //z4 Core Load/Store
      biapr.F.M1AP = FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS;
      //z4 Core Instruction
      biapr.F.M0AP = FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS;
       
       init( biucr1, biucr2, biapr );
   }

   pFLASH = (FLASH_T *)Flash_Devices[ device_index ];

   //Write 1 to Clear EER RWE and SBC bits
   reg_value = pFLASH->MCR.U32;
   reg_value = (reg_value & FLASH_EER_CLEAR_MASK);
   pFLASH->MCR.U32 = reg_value;

   reg_value = pFLASH->MCR.U32;
   reg_value = (reg_value & FLASH_RWE_CLEAR_MASK);
   pFLASH->MCR.U32 = reg_value;

   reg_value = pFLASH->MCR.U32;
   reg_value = (reg_value & FLASH_SBC_CLEAR_MASK);
   pFLASH->MCR.U32 = reg_value;
}

//===========================================================================
// Function definitions
//===========================================================================
// Initialize flash controller to programming
//===========================================================================
void MPC5644_FLASH_Initialize_Programming(void)
{
   MPC5644_FLASH_Initialize(FLASH_RUN_MODE_REPROGRAMMING,FLASH_DEVICE_A);
   MPC5644_FLASH_Initialize(FLASH_RUN_MODE_REPROGRAMMING,FLASH_DEVICE_B);
}

//===========================================================================
// Function definitions
//===========================================================================
// Initialize flash controller to normal
//===========================================================================
void MPC5644_FLASH_Initialize_Normal(void)
{
   MPC5644_FLASH_Initialize(FLASH_RUN_MODE_NORMAL,FLASH_DEVICE_A);
   MPC5644_FLASH_Initialize(FLASH_RUN_MODE_NORMAL,FLASH_DEVICE_B);
}


