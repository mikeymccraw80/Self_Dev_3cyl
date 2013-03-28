//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_c90lc_flash.c %
//
// %created_by:      zzrfyj %
//
// %date_created:    Mon Jul 11 12:25:07 2011 %
//
// %derived_by:      %
//
// %date_modified:   %
//
// %version:         %
//
// ============================================================================
// SPECIFICATION REVISION:
//
// ============================================================================
// Configurable Development Software Module:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
//
//=============================================================================

//=============================================================================
//
//                          Device Programming Driver
// This module provides interfaces between Freescale flash driver and
// Application interfaces.
//
// Requirements Document(s):
//   1. (Motorola) Chapter 10 Flash Memory of MPC5634M Microcontroller Reference
//       Manual.
//   2. (Motorola) Standard Software Driver for C90LC Flash in xPC56xx User's Manual.
//=============================================================================

//===========================================================================
//       Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "ssd_types.h"
#include "ssd_c90lc.h"             // prototype for C90LC driver

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================
#include "dd_flash_interface.h"
#include "dd_c90lc_flash_init.h"   // C90LC_TOTAL_BLOCK_NUMBER
#include "dd_c90lc_flash.h"

//===========================================================================
// Local preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================
// maximum 28 blocks for high address space
#define C90LC_BLOCK_LOCK_VALUE ((uint32_t)0x0FFFFFFF)
// 8 bytes requested by Freescale Driver
#define C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY 8

//===========================================================================
// Local preprocessor #define MACROS() (i.e., those using # or ## operator)
//===========================================================================

//===========================================================================
//  Local Type Declarations (enum, struct, union, typedef)
//===========================================================================

//===========================================================================
//  Local object definitions
//===========================================================================
// 8 byte RAM buffer, but shall be 4 byte boundary per flash driver
static uint32_t c90lc_align_boundary_buffer[
                           C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY /
                           sizeof(uint32_t)];
// Ensure initialize Flash driver before reprogramming and only once
static bool c90lc_programming_initialize_request = true;

//===========================================================================
//  Local Function Prototypes
//===========================================================================
static uint32_t C90LC_Select_Block(uint32_t select,
                uint16_t block_number);


//===========================================================================
//  Local Inline Function Definitions and #define Function-Like Macros()
//===========================================================================

//===========================================================================
// Function definitions
//===========================================================================

//===========================================================================
// FUNCTION: C90LC_Select_Block
//===========================================================================
// EXTERNAL REFERENCES:
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Set flag bit for the block which will be erased or programmed.
//===========================================================================
static uint32_t C90LC_Select_Block(uint32_t select,uint16_t block_number)
{
   return (select | ((uint32_t)1 << block_number));
}

//===========================================================================
// FUNCTION: C90LC_Get_Block_Number
//===========================================================================
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
// Calculate block number per address.
//===========================================================================
static C90LC_Block_Number_T C90LC_Get_Block_Number(uint32_t flash_address)
{
   uint8_t              idx;
   C90LC_Block_Number_T block_number;

   // invalid block
   block_number = INVALID_BLOCK;

   for(idx = C90LC_BLOCK_0; idx < C90LC_Number_of_Blocks; idx++)
   {
      if( (flash_address >= C90LC_Memory_Map[ idx ].Start_Addr) &&
          (flash_address <  (C90LC_Memory_Map[ idx ].Start_Addr + C90LC_Memory_Map[ idx ].Size_In_Byte)) )
      {
         block_number = idx;
         break;
      }
   }
   return block_number;
}



//===========================================================================
// FUNCTION: C90LC_Write
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashProgram() and ProgramVerify() in ssd_C90LC library.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
// Write a set of data to C90LC memory. Write a page of 32 byte each time
// until all data are written.
//===========================================================================
static bool C90LC_Write(PSSD_CONFIG ssdConfig,
                   uint32_t byte_length,
                   uint32_t *source_address_ptr,
                   uint32_t *destination_address_ptr,
                   void *function)
{
   uint32_t fail_address;         // save the failed address in flash
   uint64_t fail_data;            // save the failed data in flash
   uint64_t fail_source_data;     // save the failed data in source buffer

   uint32_t local_source_address;
   uint32_t local_dst_start_address;

   bool write_status;

   write_status = false;

   if (byte_length != 0)
   {
      local_source_address = (uint32_t)source_address_ptr;

      local_dst_start_address = (uint32_t)destination_address_ptr;

      // Programming
      if (C90FL_OK == ssd_c90lc_FlashProgram(ssdConfig,
                                  local_dst_start_address,
                                  byte_length,
                                  local_source_address,
                                  function))
      {
         // Verify
         if (C90FL_OK == ssd_c90lc_ProgramVerify(ssdConfig,
                                      local_dst_start_address,
                                      byte_length,
                                      local_source_address,
                                      &fail_address,
                                      &fail_data,
                                      &fail_source_data,
                                      function))
         {
            write_status = true;
         }
      }
   }
   else
   {
      write_status = true;
   }

   return (write_status);
}

//===========================================================================
// FUNCTION: C90LC_Initialize
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashInit() in ssd_c90lc library
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Initial ssdConfig according to operation block
//  This fuction shall be called first before useing other driver.
//===========================================================================
bool C90LC_Initialize(void)
{
   bool init_success;

   C90LC_Block_Number_T blocknum;

   for(blocknum = C90LC_BLOCK_0; blocknum < C90LC_Number_of_Blocks; blocknum++)
   {
      switch(C90LC_Memory_Map[blocknum].Address_Space)
      {
         case C90LC_MEMORY_A0_L:
         case C90LC_MEMORY_A0_M:
         case C90LC_MEMORY_A0_S:
            C90LC_Memory_Map[blocknum].ssdConfig = &ssdA0Config;
            break;
         case C90LC_MEMORY_A1_H:
            C90LC_Memory_Map[blocknum].ssdConfig = &ssdA1Config;
            break;
         case C90LC_MEMORY_A2_H:
            C90LC_Memory_Map[blocknum].ssdConfig = &ssdA2Config;
            break;
         default:
            break;
      }

   }

   if ( c90lc_programming_initialize_request )
   {
      if ( C90FL_OK == ssd_c90lc_FlashInit(&ssdA0Config) )
      {
         if ( C90FL_OK == ssd_c90lc_FlashInit(&ssdA1Config) )
         {
            if ( C90FL_OK == ssd_c90lc_FlashInit(&ssdA2Config) )
            {
               init_success = true;
               c90lc_programming_initialize_request = false;
            }
         }
      }
      else
      {
         init_success = false;
      }
   }
   else
   {
      init_success = true;
   }

   return (init_success);
}

//===========================================================================
// FUNCTION: C90LC_Erase_Block
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashErase() in ssd_C90LC library.
//--------------------------------------------------------------------------
// ABSTRACT:
//--------------------------------------------------------------------------
// Erase a block.
//===========================================================================
bool C90LC_Erase_Block(uint32_t in_address, void *function)
{
   PSSD_CONFIG             ssdConfig;
   uint32_t                low_block_select;     // selected blocks in low space
   uint32_t                mid_block_select;     // selected blocks in middle space
   uint32_t                high_block_select;    // selected blocks in high space
   uint16_t                space_block_number;
   bool                    shadow_flag;
   bool                    erase_status;
   bool                    erase_need;
   C90LC_Block_Number_T    block_number;

   shadow_flag = false;
   low_block_select = 0;
   mid_block_select = 0;
   high_block_select = 0;

   erase_status = false;
   erase_need = true;

   block_number = C90LC_Get_Block_Number(in_address);

   if(block_number < C90LC_Number_of_Blocks)
   {
      space_block_number = C90LC_Memory_Map[block_number].Array_Space_Block_Number;
      ssdConfig = C90LC_Memory_Map[block_number].ssdConfig;

      switch (C90LC_Memory_Map[block_number].Address_Space)
      {
         case C90LC_MEMORY_A0_L:
         {
            low_block_select = C90LC_Select_Block(low_block_select,
                                                      space_block_number);
            break;
         }

         case C90LC_MEMORY_A0_M:
         {
            mid_block_select = C90LC_Select_Block(mid_block_select,
                                                      space_block_number);
            break;
         }

         case C90LC_MEMORY_A1_H:
         {
            high_block_select = C90LC_Select_Block(high_block_select,
                                                       space_block_number);
            break;
         }

         case C90LC_MEMORY_A2_H:
         {
            high_block_select = C90LC_Select_Block(high_block_select,
                                                       space_block_number);
            break;
         }

         case C90LC_MEMORY_A0_S:
         {
            shadow_flag = true;
            break;
         }

         default:
         {
            erase_need = false;
            break;
         }

      }


      if (erase_need)
      {
         // Disable prefetch
       //  FLASH_Controller_Interface[MPC5634_FLASH].Initial_Programming();
		 MPC5634_FLASH_Initialize_Programming();
	

         // erasing
         if (C90FL_OK == ssd_c90lc_FlashErase(ssdConfig,
                                    shadow_flag,
                                    low_block_select,
                                    mid_block_select,
                                    high_block_select,
                                    function))
         {
            // Check content
            if (!shadow_flag)
            {
               erase_status =
                  C90LC_Check_Erased(C90LC_Memory_Map[block_number].Size_In_Byte,
                                    C90LC_Memory_Map[block_number].Start_Addr,
                                    function);
            }
            else
            {
               erase_status =
                  C90LC_Check_Erased(ssdConfig->shadowRowSize,
                                    ssdConfig->shadowRowBase,
                                    function);
            }
         }

         // Enable prefetch
        // FLASH_Controller_Interface[MPC5634_FLASH].Initial_Normal();
		 	  MPC5634_FLASH_Initialize_Normal();
      }
   }

   return (erase_status);
}

//==========================================================================
// FUNCTION: C90LC_Check_Erased
//==========================================================================
// EXTERNAL REFERRNCES:
// Call BlankCheck() in ssd_C90LC library.
// ------------------------------------------------------------------------
// ABSTRACT:
// Check assigned memory area are erased.
// Note: Based on hardware structure, reprogramming flash memory with
// 64 bit uint each time.
// This also means:
// byte_length shall be multiply of 8.
// start_address Shall be 64bit boundary.
//==========================================================================
bool C90LC_Check_Erased(uint32_t byte_length,
                        uint32_t start_address,
                        void *function)
{
   PSSD_CONFIG                        ssdConfig;
   uint32_t                           fail_address;         // save the failed address in flash
   uint64_t                           fail_data;            // save the failed data in flash
   uint32_t                           hwio_status;
   uint32_t                           end_address;
   bool                               erase_status;
   bool                               invlaid_input;

   C90LC_Block_Number_T               start_blocknum;
   C90LC_Block_Number_T               end_blocknum;


   erase_status    = false;
   invlaid_input   = false;
   end_address     = start_address + byte_length;

   start_blocknum  = C90LC_Get_Block_Number(start_address);
   end_blocknum    = C90LC_Get_Block_Number(end_address-1);

   if(start_blocknum < C90LC_Number_of_Blocks)
   {
      ssdConfig = C90LC_Memory_Map[start_blocknum].ssdConfig;
      if(end_blocknum < C90LC_Number_of_Blocks)
      {
         if(ssdConfig != C90LC_Memory_Map[end_blocknum].ssdConfig)
         {
            invlaid_input = true;
         }
      }
      else
      {
         invlaid_input = true;
      }
   }
   else
   {
      invlaid_input = true;
   }


   if(invlaid_input == false)
   {
      while(start_address < end_address)
      {
         hwio_status = ssd_c90lc_BlankCheck(ssdConfig,
                                  start_address,
                                  ssdConfig->pageSize,
                                  &fail_address,
                                  &fail_data,
                                  function);
         if (C90FL_OK == hwio_status)
         {
            erase_status = true;
         }
         else
         {
            erase_status = false;
            break;
         }
         start_address += ssdConfig->pageSize;
      }
   }

   return (erase_status);
}

//===========================================================================
// FUNCTION: C90LC_Suspend_Erase
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashSuspend() in ssd_C90LC library.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Suspend erase operation.
//===========================================================================
bool C90LC_Suspend_Erase(uint32_t in_address)
{
   PSSD_CONFIG              ssdConfig;
   uint32_t                 hwio_status;
   bool                     suspend_flag;
   bool                     suspend_success;
   uint8_t                  suspend_state;
   C90LC_Block_Number_T     block_number;

   suspend_success = false;

   block_number = C90LC_Get_Block_Number(in_address);

   if(block_number < C90LC_Number_of_Blocks)
   {
      ssdConfig = C90LC_Memory_Map[block_number].ssdConfig;
   }

   hwio_status = ssd_c90lc_FlashSuspend(ssdConfig,
                              &suspend_state,
                              &suspend_flag);

   if ((C90FL_OK == hwio_status) && suspend_flag &&
       ((ERS_SUS == suspend_state) || (SHADOW_ERS_SUS == suspend_state)))
   {
      // suspend erase
      suspend_success = true;
   }

   return (suspend_success);
}

//===========================================================================
// FUNCTION: C90LC_Suspend_Program
//===========================================================================
// EXTERNAL REFERENCES:
// Program suspend is not available on MPC5634.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Suspend program operation.
//===========================================================================
bool C90LC_Suspend_Program(void)
{
   return (false);
}

//===========================================================================
// FUNCTION: C90LC_Resume_Erase
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashResume() in ssd_C90LC library.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Resume erase operation.
//===========================================================================
bool C90LC_Resume_Erase(uint32_t in_address)
{
   PSSD_CONFIG               ssdConfig;
   uint32_t                  hwio_status;
   bool                      resume_success;
   uint8_t                   resume_state;
   C90LC_Block_Number_T      block_number;


   resume_success = false;

   block_number = C90LC_Get_Block_Number(in_address);

   if(block_number < C90LC_Number_of_Blocks)
   {
      ssdConfig = C90LC_Memory_Map[block_number].ssdConfig;
   }

   hwio_status = ssd_c90lc_FlashResume(ssdConfig,
                             &resume_state);

   if ((C90FL_OK == hwio_status) && (RES_ERS == resume_state))
   {
      // resume erase
      resume_success = true;
   }

   return (resume_success);
}

//===========================================================================
// FUNCTION: C90LC_Resume_Program
//===========================================================================
// EXTERNAL REFERENCES:
// Program suspend is not available on MPC5634.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Resume program operation.
//===========================================================================
bool C90LC_Resume_Program(void)
{
   return (true);
}

//===========================================================================
// C90LC_Write_Array_Memory
//
// Write array memory. Using this interface eliminates limitation of
// size and address of flash memory - do not request programmed memory
// shall be 8 byte boundary.
//===========================================================================
bool C90LC_Write_Array_Memory(uint32_t byte_length,
                             uint32_t source_address,
                             uint32_t destination_address,
                             void *call_function)
{
   PSSD_CONFIG ssdConfig;
   C90LC_Block_Number_T start_blocknum;
   C90LC_Block_Number_T end_blocknum;
   volatile uint32_t local_byte_length;
   volatile uint32_t local_source_start_address;
   volatile uint32_t local_destination_start_address;
   volatile uint32_t local_destination_end_address;

   uint8_t *source_address_byte_ptr;
   uint8_t *destination_address_byte_ptr;

   uint16_t index;

   volatile uint16_t modul_byte_length;
   uint16_t buffer_modul_head_byte_number;

   volatile bool write_good;
   bool des_address_valid;

   write_good = true;
   des_address_valid = true;

   start_blocknum = C90LC_Get_Block_Number(destination_address);
   end_blocknum = C90LC_Get_Block_Number(destination_address + byte_length - 1);

   if(start_blocknum < C90LC_Number_of_Blocks)
   {
      ssdConfig = C90LC_Memory_Map[start_blocknum].ssdConfig;
      if(end_blocknum < C90LC_Number_of_Blocks)
      {
         if(ssdConfig != C90LC_Memory_Map[end_blocknum].ssdConfig)
         {
            des_address_valid = false;
         }
      }
      else
      {
         des_address_valid = false;
      }
   }
   else
   {
      des_address_valid = false;
   }

   if(des_address_valid)
   {
      if (byte_length > 0)
      {
         // Disable prefetch
         //FLASH_Controller_Interface[MPC5634_FLASH].Initial_Programming();
		 MPC5634_FLASH_Initialize_Programming();
		 	  

         local_byte_length = byte_length;
         local_destination_start_address = destination_address;

         local_source_start_address = source_address;
         local_destination_end_address = destination_address + byte_length;

         // Check flash start address if it's 8 byte boundary
         modul_byte_length = (uint16_t)(local_destination_start_address %
                                        C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY);
         if (modul_byte_length)   // not 8 byte boundary
         {
            // copy flash memory to c90lc_align_boundary_buffer
            local_destination_start_address -= modul_byte_length;
            source_address_byte_ptr = (uint8_t *)local_destination_start_address;
            destination_address_byte_ptr =
                                        (uint8_t *)&c90lc_align_boundary_buffer[0];
            for (index = 0; index < modul_byte_length; index++)
            {
               *destination_address_byte_ptr++ = *source_address_byte_ptr++;
            }

            // copy reprogramming buffer to h7fa_align_boundary_buffer
            source_address_byte_ptr = (uint8_t *)local_source_start_address;

            buffer_modul_head_byte_number = C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY -
                                            modul_byte_length;
            if (local_byte_length >= buffer_modul_head_byte_number)
            {
               // data number in buffer are enough for 8 bytes align
               for (; index < C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY; index++)
               {
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
               }

               local_byte_length -= (uint32_t)buffer_modul_head_byte_number;
            }
            else
            {
               // data number in buffer are less for 8 bytes align
               for (; index < (modul_byte_length + local_byte_length); index++)
               {
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
               }

               source_address_byte_ptr = (uint8_t *)local_destination_end_address;
               for (; index < C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY; index++)
               {
                  //
                  // read flash memory data to h7fa_align_boundary_buffer
                  // to make full 8 bytes.
                  //
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
               }

               local_byte_length = 0;
            }

            // Reprogram 8 bytes first
            write_good =
                  C90LC_Write(ssdConfig,
                             (uint32_t)C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY,
                             (uint32_t *)&c90lc_align_boundary_buffer[0],
                             (uint32_t *)local_destination_start_address,
                             call_function);

            //
            // Since programming source start address shall be 4 byte boundary
            // requested by flash driver, need to adjust buffer
            //
            if (write_good && (local_byte_length != 0))
            {
               local_destination_start_address +=
                                       C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY;

               //
               // Left shift reprogramming buffer to ensure
               // flash sorce address is 4 byte boundary.
               //
               destination_address_byte_ptr =
                                       (uint8_t *)local_source_start_address;
               for (index = 0; index < (uint16_t)local_byte_length; index++)
               {
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
               }
            }
         }

         // treat trail for 8 byte boundary
         if (write_good && (local_byte_length != 0))
         {
            modul_byte_length =
             (uint16_t)(local_byte_length % C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY);
            if (modul_byte_length)
            {

               // need to fill reprogramming buffer with flash memory contents
               // read data from block end address in flash memory
             write_good = C90LC_Write(ssdConfig,
                                    (local_byte_length-modul_byte_length),
                                    (uint32_t *)local_source_start_address,
                                    (uint32_t *)local_destination_start_address,
                                    call_function);

           if (write_good)
           {
            destination_address_byte_ptr = (uint8_t *)(&c90lc_align_boundary_buffer[0]);
            source_address_byte_ptr = (uint8_t *)(local_source_start_address + local_byte_length - modul_byte_length);

            for (index=0; index < modul_byte_length ; index++)
            {
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
            }

           local_destination_start_address = local_destination_start_address + local_byte_length-modul_byte_length;

            modul_byte_length = C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY -
                                   modul_byte_length;

            source_address_byte_ptr = (uint8_t *)local_destination_end_address;

               // fill buffer to ensure it's 8 byte boundary
               for (index = 0; index < modul_byte_length; index++)
               {
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
               }

               write_good = C90LC_Write(ssdConfig,
                                     C90LC_PROGRAMMED_FLASH_MEMORY_BOUNDARY,
                                    (uint32_t *)&c90lc_align_boundary_buffer[0],
                                    (uint32_t *)local_destination_start_address,
                                    call_function);
           }
               // update reprogrammed data size
               //local_byte_length += (uint32_t)modul_byte_length;
            }
            else
            {

            //
            // write an integral block which both start and end address
            // are 8 byte boundary.
            //
            write_good = C90LC_Write(ssdConfig,
                                     local_byte_length,
                                    (uint32_t *)local_source_start_address,
                                    (uint32_t *)local_destination_start_address,
                                    call_function);
            }
         }

         // Enable prefetch
         //FLASH_Controller_Interface[MPC5634_FLASH].Initial_Normal();
		 MPC5634_FLASH_Initialize_Normal();
      }
   }
   else
   {
      write_good = false;
   }

   return (write_good);
}

//===========================================================================
// C90LC_Flash_ECClogic_Check
//
// ECC logic check function will check the ECC logic of the flash
// The API will simulate a single or double bit fault depending on
// user input
//===========================================================================
bool C90LC_Flash_ECCLogic_Check(uint32_t in_address,
                               uint64_t data_value,
                               uint64_t error_bits,
                               uint32_t ecc_value)
{
   PSSD_CONFIG               ssdConfig;
   bool                      ecc_error;
   C90LC_Block_Number_T      block_number;


   block_number = C90LC_Get_Block_Number(in_address);

   if(block_number < C90LC_Number_of_Blocks)
   {
      ssdConfig = C90LC_Memory_Map[block_number].ssdConfig;
   }

   if(C90FL_OK == ssd_c90lc_FlashECCLogicCheck(ssdConfig,
                                       data_value,
                                       error_bits,
                                       ecc_value))
   {
      ecc_error = true;
   }
   else
   {
      ecc_error = false;
   }

   return (ecc_error);

}

//===========================================================================
// C90LC_Flash_Array_Integrity_Check
//
// Flash array integrity check function will check the array integrity
// of the flash based on the user specified address space
// The API will compare the Multiple Input Signature register (MISR)
// value calculated by the hardware with the values passed by the user
//
//===========================================================================

bool C90LC_Flash_Array_Integrity_Check(uint32_t in_address,
                                      bool addrSeq,
                                      MISR misrValue,
                                      void *function)
{
   PSSD_CONFIG               ssdConfig;
   C90LC_Block_Number_T      block_number;
   uint32_t                  low_block_select  = 0;     // selected blocks in low space
   uint32_t                  mid_block_select  = 0;     // selected blocks in middle space
   uint32_t                  high_block_select = 0;     // selected blocks in high space
   uint16_t                  space_block_number;

   bool integrity_status = false;
   bool integrity_need = true;

   block_number = C90LC_Get_Block_Number(in_address);

   if(block_number <= C90LC_Number_of_Blocks)
   {
      space_block_number = C90LC_Memory_Map[block_number].Array_Space_Block_Number;
      ssdConfig = C90LC_Memory_Map[block_number].ssdConfig;

      switch (C90LC_Memory_Map[block_number].Address_Space)
      {
         case C90LC_MEMORY_A0_L:
         {
            low_block_select = C90LC_Select_Block(low_block_select,
                                                      space_block_number);
            break;
         }

         case C90LC_MEMORY_A0_M:
         {
            mid_block_select = C90LC_Select_Block(mid_block_select,
                                                      space_block_number);
            break;
         }

         case C90LC_MEMORY_A1_H:
         {
            high_block_select = C90LC_Select_Block(high_block_select,
                                                       space_block_number);
            break;
         }

         case C90LC_MEMORY_A2_H:
         {
            high_block_select = C90LC_Select_Block(high_block_select,
                                                       space_block_number);
            break;
         }

         default:
         {
            integrity_need = false;
            break;
         }
      }

      if (integrity_need == true)
      {
         if(C90FL_OK == ssd_c90lc_FlashArrayIntegrityCheck(ssdConfig,
                                                 low_block_select,
                                                 mid_block_select,
                                                 high_block_select,
                                                 addrSeq,
                                                 misrValue,
                                                 function))
         {
             integrity_status = true;
         }

      }
   }
   return (integrity_status);
}

//===========================================================================
// C90LC_Factory_Margin_Read_Check
//
// Factory Margin Read Check function will check the Factory Margin
// Reads of the flash The user specified margin level is used for
// reads and the operation is done on the specified blocks.
//
//===========================================================================
bool C90LC_Factory_Margin_Read_Check(uint32_t in_address,
                                    bool marginLevel,
                                    MISR misrValue,
                                    void *function)
{
   PSSD_CONFIG               ssdConfig;
   C90LC_Block_Number_T      block_number;
   uint32_t                  low_block_select  = 0;     // selected blocks in low space
   uint32_t                  mid_block_select  = 0;     // selected blocks in middle space
   uint32_t                  high_block_select = 0;     // selected blocks in high space
   uint16_t                  space_block_number;

   bool FMR_status = false;
   bool FMR_need = true;

   block_number = C90LC_Get_Block_Number(in_address);

   if(block_number <= C90LC_Number_of_Blocks)
   {
      space_block_number = C90LC_Memory_Map[block_number].Array_Space_Block_Number;
      ssdConfig = C90LC_Memory_Map[block_number].ssdConfig;

      switch (C90LC_Memory_Map[block_number].Address_Space)
      {
         case C90LC_MEMORY_A0_L:
         {
            low_block_select = C90LC_Select_Block(low_block_select,
                                                      space_block_number);
            break;
         }

         case C90LC_MEMORY_A0_M:
         {
            mid_block_select = C90LC_Select_Block(mid_block_select,
                                                      space_block_number);
            break;
         }

         case C90LC_MEMORY_A1_H:
         {
            high_block_select = C90LC_Select_Block(high_block_select,
                                                       space_block_number);
            break;
         }

         case C90LC_MEMORY_A2_H:
         {
            high_block_select = C90LC_Select_Block(high_block_select,
                                                       space_block_number);
            break;
         }

         default:
         {
            FMR_need = false;
            break;
         }
      }
      if (FMR_need == true)
      {
         if(C90FL_OK == ssd_c90lc_FactoryMarginReadCheck(ssdConfig,
                                               low_block_select,
                                               mid_block_select,
                                               high_block_select,
                                               marginLevel,
                                               misrValue,
                                               function))
         {
             FMR_status = true;
         }

      }
   }

   return (FMR_status);
}

//===========================================================================
// FUNCTION: C90LC_SetLock
//===========================================================================
// EXTERNAL REFERENCES:
// Call SetLock() in ssd_C90LC library.
//--------------------------------------------------------------------------
// ABSTRACT:
//--------------------------------------------------------------------------
// Erase a block.
//===========================================================================
bool C90LC_SetLock(uint32_t in_address, bool lockstate)
{
   bool                    return_code;
   uint32_t                block_select;
   uint32_t                current_lock;
   bool                    register_enabled;
   C90LC_Block_Number_T    blocknum;

   struct para_tag{
      PSSD_CONFIG         ssdConfig;
      uint8_t             Primary;
      uint8_t             Secondary;
      bool                SecondaryNeeded;
      uint32_t            Primary_Password;
   } f_para;

   return_code = false;
   block_select = 0;

   blocknum = C90LC_Get_Block_Number(in_address);

   if(blocknum < C90LC_Number_of_Blocks)
   {
      block_select = C90LC_Select_Block(block_select,C90LC_Memory_Map[blocknum].Array_Space_Block_Number);
      f_para.ssdConfig = C90LC_Memory_Map[blocknum].ssdConfig;

      switch(C90LC_Memory_Map[blocknum].Address_Space)     //get function parameters according to block location
      {
         case C90LC_MEMORY_A0_L:
            f_para.Primary = LOCK_LOW_PRIMARY;
            f_para.Secondary = LOCK_LOW_SECONDARY;
            f_para.SecondaryNeeded = true;
            f_para.Primary_Password = C90LC_LMLR_PASSWORD;
            break;
         case C90LC_MEMORY_A0_M:
            f_para.Primary = LOCK_MID_PRIMARY;
            f_para.Secondary = LOCK_MID_SECONDARY;
            f_para.SecondaryNeeded = true;
            f_para.Primary_Password = C90LC_LMLR_PASSWORD;
            break;

         case C90LC_MEMORY_A1_H:
            f_para.Primary = LOCK_HIGH;
            f_para.Secondary = 0xFF;
            f_para.SecondaryNeeded = false;
            f_para.Primary_Password = C90LC_HLR_PASSWORD;
            break;

         case C90LC_MEMORY_A2_H:
            f_para.Primary = LOCK_HIGH;
            f_para.Secondary = 0xFF;
            f_para.SecondaryNeeded = false;
            f_para.Primary_Password = C90LC_HLR_PASSWORD;
            break;

         default:
            blocknum = INVALID_BLOCK;
            break;
      }
   }
   else
   {
      blocknum = INVALID_BLOCK;
   }

   if(INVALID_BLOCK != blocknum)    // real operation here call GetLock() and SetLock() from library
   {
      if(C90FL_OK == ssd_c90lc_GetLock(f_para.ssdConfig,
                             f_para.Primary,
                             &register_enabled,
                             &current_lock))
      {
         if(lockstate)
         {
            current_lock |= block_select;
         }
         else
         {
            current_lock &= ~block_select;
         }
         if(C90FL_OK == ssd_c90lc_SetLock(f_para.ssdConfig, f_para.Primary, current_lock, f_para.Primary_Password))
         {
            return_code = true;
         }
      }

      if(return_code == true)
      {
         if(f_para.SecondaryNeeded)
         {
            if(C90FL_OK == ssd_c90lc_GetLock(f_para.ssdConfig,
                                   f_para.Secondary,
                                   &register_enabled,
                                   &current_lock))
            {
               if(lockstate)
               {
                  current_lock |= block_select;
               }
               else
               {
                  current_lock &= ~block_select;
               }
               if(C90FL_OK == ssd_c90lc_SetLock(f_para.ssdConfig, f_para.Secondary, current_lock, C90LC_SLMLR_PASSWORD))
               {
                  return_code = true;
               }
               else
               {
                  return_code = false;
               }
            }
            else
            {
               return_code = false;
            }
         }
      }
   }
   else
   {
      return_code = false;
   }


   return return_code;

}


//=============================================================================
//
// Revisiion History:
//
// Rev. YYMMDD Who  SCR# Changes
// ---- ------ ---- ---- -----------------------------------------------------
// 1.0  110711 xh   xxxx Create initial release.
//=============================================================================

