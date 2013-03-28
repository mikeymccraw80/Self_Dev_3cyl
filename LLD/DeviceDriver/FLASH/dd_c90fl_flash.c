//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   dd_c90fl_flash.c~2:csrc:ctc_pt3#1 %
//
// created_by:       fzfns4
//
// date_created:     Fri May  5 11:58:47 2006
//
// %derived_by:      zzrfyj %
//
// %date_modified:     %
//
// %version:         2 %
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
//   1. (Motorola) Flash Memory of MPC5674F Microcontroller Reference
//       Manual.
//   2. (Motorola) MPC55xx H7Fa Standard Software Driver User's Manual.
//                 The version of the used driver is 3.10.
//=============================================================================

//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "ssd_types.h"
#include "ssd_c90fl.h"             // prototype for C90FL driver

//===========================================================================
//       Preprocessor #include directive(s) for "other header files"
//===========================================================================
#include "dd_flash_interface.h"              // FLASH_Initialize
#include "dd_c90fl_flash.h"
#include "dd_c90fl_flash_init.h"    // H7FA_TOTAL_BLOCK_NUMBER
#include "dd_flash_mpc5644.h"     // FLASH register address definition
//===========================================================================
// Local preprocessor #define CONSTANTS (object-like MACROS)
//===========================================================================
// maximum 28 blocks for high address space
#define C90FL_BLOCK_LOCK_VALUE ((uint32_t)0x0FFFFFFF)
// 8 bytes requested by Freescale Driver
#define C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY 8

//===========================================================================
// Local preprocessor #define MACROS() (i.e., those using # or ## operator)
//===========================================================================

//===========================================================================
//  Local Type Declarations (enum, struct, union, typedef)
//===========================================================================

//===========================================================================
// Exported Object Definitions
//===========================================================================

//===========================================================================
//  Local object definitions
//===========================================================================
// 8 byte RAM buffer, but shall be 4 byte boundary per flash driver
static uint32_t c90fl_align_boundary_buffer[
                           C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY /
                           sizeof(uint32_t)];
// Ensure initialize Flash driver before reprogramming and only once
static bool c90fl_programming_initialize_request = true;

//===========================================================================
//  Local Function Prototypes
//===========================================================================
static uint32_t C90FL_Select_Block(uint32_t select,
                uint16_t block_number);

//===========================================================================
// C90FL_Select_Erase_Block
//
// @func Set flag bit for the block which will be erased.
//
// @parm uint32_t | select | block flag bit
//
// @parm uint16_t | block number | range 0-19
//
// @rdesc uint32_t | the appropriate block bit is set.
//
// @end
//===========================================================================
static uint32_t C90FL_Select_Block(uint32_t select,uint16_t block_number)
{
   return (select | ((uint32_t)1 << block_number));
}

//===========================================================================
//  Local Inline Function Definitions and #define Function-Like Macros()
//===========================================================================

//===========================================================================
// Function definitions
//===========================================================================
//===========================================================================
// FUNCTION: C90FL_Initialize
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashInit() in ssd_c90fl library
//      FLASH_Initialize in dd_flash.c
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Checks and initialize the control register of the H7Fa module.
//  Unlock all blocks and Disable prefetch.
//  This fuction shall be called first before useing other driver.
//===========================================================================
bool C90FL_Initialize(void)
{
   uint32_t hwio_status, reg_value;
   bool init_success;

   if (c90fl_programming_initialize_request )
   {
      //Write 1 to Clear EER and RWE bits for FLASH A
      reg_value = FLASH_A.MCR.U32;
      reg_value = (reg_value & FLASH_EER_CLEAR_MASK);

      FLASH_A.MCR.U32 = reg_value;

      reg_value = FLASH_A.MCR.U32;
      reg_value = (reg_value & FLASH_RWE_CLEAR_MASK);

      FLASH_A.MCR.U32 = reg_value;

     //Write 1 to Clear SBC bit for FLASH A
      reg_value = FLASH_A.MCR.U32;
      reg_value = (reg_value & FLASH_SBC_CLEAR_MASK);

      FLASH_A.MCR.U32 = reg_value;

     //Write 1 to Clear EER and RWE bits for FLASH B
      reg_value = FLASH_B.MCR.U32;
      reg_value = (reg_value & FLASH_EER_CLEAR_MASK);

      FLASH_B.MCR.U32 = reg_value;

      reg_value = FLASH_B.MCR.U32;
      reg_value = (reg_value & FLASH_RWE_CLEAR_MASK);

      FLASH_B.MCR.U32 = reg_value;

     //Write 1 to Clear SBC bit for FLASH B
      reg_value = FLASH_B.MCR.U32;
      reg_value = (reg_value & FLASH_SBC_CLEAR_MASK);

      FLASH_B.MCR.U32 = reg_value;

      hwio_status = ssd_c90fl_FlashInit(&ssdConfig);

      if (C90FL_OK == hwio_status)
      {
         init_success = true;
         // Initialize flash driver once only
         c90fl_programming_initialize_request = false;

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
// FUNCTION: C90FL_Get_Block_Number
//===========================================================================
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
// Calculate block number per address.
//===========================================================================
static uint16_t C90FL_Get_Block_Number(uint32_t flash_address)
{
   uint8_t              idx;
   C90FL_Block_Number_T block_number;

   // invalid block
   block_number = INVALID_BLOCK;

   for(idx = C90FL_BLOCK_L0; idx < C90FL_Number_of_Blocks; idx++)
   {
      if( (flash_address >= C90FL_Memory_Map[ idx ].Start_Addr) &&
          (flash_address <  (C90FL_Memory_Map[ idx ].Start_Addr + C90FL_Memory_Map[ idx ].Size_In_Byte)) )
      {
         block_number = idx;
         break;
      }
   }
   return block_number;
}


//===========================================================================
// FUNCTION: C90FL_SetLock
//===========================================================================
// EXTERNAL REFERENCES:
// Call SetLock() in ssd_h7fa.a.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
// Unlock or Lock all blocks including shadow without checking original status
//===========================================================================
bool C90FL_SetLock(uint32_t in_address, bool lockstate)
{
   uint32_t                block_lock_state;
   C90FL_Block_Number_T    block_number;
   uint32_t                current_lock;
   bool                    register_enabled;
   bool                    return_code;
   uint32_t                block_select;

   struct para_tag{
      uint8_t             Primary;
      uint8_t             Secondary;
      bool                SecondaryNeeded;
      uint32_t            Primary_Password;
   } f_para;


   return_code = false;
   block_select = 0;

   block_number = C90FL_Get_Block_Number(in_address);

   if(block_number < C90FL_Number_of_Blocks)
   {
      block_select = C90FL_Select_Block(block_select,C90FL_Memory_Map[block_number].Address_Space_Block_Number);
      switch(C90FL_Memory_Map[block_number].Address_Space)
      {
         case C90FL_MEMORY_LOW_ADDRESS_SPACE:
            f_para.Primary = LOCK_LOW_PRIMARY;
            f_para.Secondary = LOCK_LOW_SECONDARY;
            f_para.SecondaryNeeded = true;
            f_para.Primary_Password = C90FL_LMLR_PASSWORD;
            break;
         case C90FL_MEMORY_MID_ADDRESS_SPACE:
            f_para.Primary = LOCK_LOW_PRIMARY;
            f_para.Secondary = LOCK_LOW_SECONDARY;
            f_para.SecondaryNeeded = true;
            f_para.Primary_Password = C90FL_LMLR_PASSWORD;
            break;
         case C90FL_MEMORY_HIGH_ADDRESS_SPACE:
            f_para.Primary = LOCK_HIGH;
            f_para.Secondary = 0xFF;
            f_para.SecondaryNeeded = false;
            f_para.Primary_Password = C90FL_HLR_PASSWORD;
            break;
         case C90FL_MEMORY_SHADOW_ADDRESS_SPACE:
         default:
            block_number = INVALID_BLOCK;
            break;
      }
   }
   else
   {
      block_number = INVALID_BLOCK;
   }

   if(INVALID_BLOCK != block_number)    // real operation here call GetLock() and SetLock() from library
   {
      if(C90FL_OK == ssd_c90fl_GetLock(C90FL_Memory_Map[block_number].ssdConfig,
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
         if(C90FL_OK == ssd_c90fl_SetLock(C90FL_Memory_Map[block_number].ssdConfig, f_para.Primary, current_lock, f_para.Primary_Password))
         {
            return_code = true;
         }
      }

      if(return_code == true)
      {
         if(f_para.SecondaryNeeded)
         {
            if(C90FL_OK == ssd_c90fl_GetLock(C90FL_Memory_Map[block_number].ssdConfig,
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
               if(C90FL_OK == ssd_c90fl_SetLock(C90FL_Memory_Map[block_number].ssdConfig, f_para.Secondary, current_lock, C90FL_SLMLR_PASSWORD))
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

   return (return_code);
}

//===========================================================================
// FUNCTION: C90FL_Erase_Block
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashErase() in ssd_h7fa.a.
//--------------------------------------------------------------------------
// ABSTRACT:
//--------------------------------------------------------------------------
// Erase a block.
//===========================================================================
bool C90FL_Erase_Block(uint32_t in_address, void *function)
{
   uint32_t low_block_select;     // selected blocks in low space
   uint32_t mid_block_select;     // selected blocks in middle space
   uint32_t high_block_select;    // selected blocks in high space

   C90FL_Block_Number_T    block_number;

   uint16_t space_block_number;

   bool shadow_flag;

   bool erase_status;
   bool erase_need;

   shadow_flag = false;
   low_block_select = 0;
   mid_block_select = 0;
   high_block_select = 0;

   erase_status = false;
   erase_need = true;

   block_number = C90FL_Get_Block_Number(in_address);

   if(block_number < C90FL_Number_of_Blocks)
   {
      space_block_number = C90FL_Memory_Map[block_number].Address_Space_Block_Number;

      switch (C90FL_Memory_Map[block_number].Address_Space)
      {
         case C90FL_MEMORY_LOW_ADDRESS_SPACE:
         {
            low_block_select = C90FL_Select_Block(low_block_select,
                                                      space_block_number);
            break;
         }

         case C90FL_MEMORY_MID_ADDRESS_SPACE:
         {
            mid_block_select = C90FL_Select_Block(mid_block_select,
                                                      space_block_number);
            break;
         }

         case C90FL_MEMORY_HIGH_ADDRESS_SPACE:
         {
            high_block_select = C90FL_Select_Block(high_block_select,
                                                       space_block_number);
            break;
         }

         case C90FL_MEMORY_SHADOW_ADDRESS_SPACE:
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
         MPC5644_FLASH_Initialize_Programming();
        
         // erasing
         if (C90FL_OK == ssd_c90fl_FlashErase(C90FL_Memory_Map[block_number].ssdConfig,
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
                  C90FL_Check_Erased(C90FL_Memory_Map[block_number].Size_In_Byte,
                                    C90FL_Memory_Map[block_number].Start_Addr,
                                    function);
            }
            else
            {
               erase_status =
                  C90FL_Check_Erased(ssdConfig.shadowRowSize,
                                    ssdConfig.shadowRowBase,
                                    function);
            }
         }

         // Enable prefetch
         MPC5644_FLASH_Initialize_Normal();
      }
   }

   return (erase_status);
}

//===========================================================================
// FUNCTION: C90FL_Write
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashProgram() and ProgramVerify() in ssd_h7fa.a.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
// Write a set of data to H7Fa memory. Write a page of 32 byte each time
// until all data are written.
//===========================================================================
bool C90FL_Write(PSSD_CONFIG ssdConfig,
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
      if (C90FL_OK == ssd_c90fl_FlashProgram(ssdConfig,
                                  local_dst_start_address,
                                  byte_length,
                                  local_source_address,
                                  function))
      {
         // Verify
         if (C90FL_OK == ssd_c90fl_ProgramVerify(ssdConfig,
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

//==========================================================================
// FUNCTION: C90FL_Check_Erased
//==========================================================================
// EXTERNAL REFERRNCES:
// Call BlankCheck() in ssd_h7fa.a.
// ------------------------------------------------------------------------
// ABSTRACT:
// Check assigned memory area are erased.
// Note: Based on hardware structure, reprogramming flash memory with
// 64 bit uint each time.
// This also means:
// byte_length shall be multiply of 8.
// start_address Shall be 64bit boundary.
//==========================================================================
bool C90FL_Check_Erased(uint32_t byte_length,
                       uint32_t start_address,
                       void *function)
{
   uint32_t                           fail_address;         // save the failed address in flash
   uint64_t                           fail_data;            // save the failed data in flash
   uint32_t                           hwio_status;
   uint32_t                           end_address;
   bool                               erase_status;
   C90FL_Block_Number_T               start_blocknum;

   erase_status = false;
   end_address = start_address + byte_length;
   start_blocknum = C90FL_Get_Block_Number(start_address);

   while(start_address < end_address)
   {
      hwio_status = ssd_c90fl_BlankCheck(C90FL_Memory_Map[start_blocknum].ssdConfig,
                               start_address,
                               C90FL_Memory_Map[start_blocknum].ssdConfig->pageSize,
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
      start_address += C90FL_Memory_Map[start_blocknum].ssdConfig->pageSize;
   }

   return (erase_status);
}

//===========================================================================
// FUNCTION: C90FL_Suspend_Erase
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashSuspend() in ssd_h7fa.a.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Suspend erase operation.
//===========================================================================
bool C90FL_Suspend_Erase(uint32_t in_address)
{
   uint32_t hwio_status;

   bool suspend_flag;
   bool suspend_success;

   uint8_t suspend_state;
   C90FL_Block_Number_T               blocknum;

   suspend_success = false;

   blocknum = C90FL_Get_Block_Number(in_address);

   hwio_status = ssd_c90fl_FlashSuspend(C90FL_Memory_Map[blocknum].ssdConfig,
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
// FUNCTION: C90FL_Suspend_Program
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashSuspend() in ssd_h7fa.a.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Suspend program operation.
//===========================================================================
bool C90FL_Suspend_Program(void)
{
   uint32_t hwio_status;

   bool suspend_flag;
   bool suspend_success;

   uint8_t suspend_state;

   suspend_success = false;

   hwio_status = ssd_c90fl_FlashSuspend(C90FL_Memory_Map[0].ssdConfig,
                              &suspend_state,
                              &suspend_flag);

   if ((C90FL_OK == hwio_status) && suspend_flag && (PGM_SUS == suspend_state))
   {
      // suspend program
      suspend_success = true;
   }

   return (suspend_success);
}

//===========================================================================
// FUNCTION: C90FL_Resume_Erase
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashResume() in ssd_h7fa.a.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Resume erase operation.
//===========================================================================
bool C90FL_Resume_Erase(uint32_t in_address)
{
   uint32_t hwio_status;

   bool resume_success;

   uint8_t resume_state;

   C90FL_Block_Number_T               blocknum;

   resume_success = false;

   blocknum = C90FL_Get_Block_Number(in_address);

   hwio_status = ssd_c90fl_FlashResume(C90FL_Memory_Map[blocknum].ssdConfig,
                             &resume_state);

   if ((C90FL_OK == hwio_status) && (RES_ERS == resume_state))
   {
      // resume erase
      resume_success = true;
   }

   return (resume_success);
}

//===========================================================================
// FUNCTION: C90FL_Resume_Program
//===========================================================================
// EXTERNAL REFERENCES:
// Call FlashResume() in ssd_h7fa.a.
// --------------------------------------------------------------------------
// ABSTRACT:
// --------------------------------------------------------------------------
//  Resume program operation.
//===========================================================================
bool C90FL_Resume_Program(void)
{
   uint32_t hwio_status;

   bool resume_success;

   uint8_t resume_state;

   resume_success = false;

   hwio_status = ssd_c90fl_FlashResume(C90FL_Memory_Map[0].ssdConfig,
                             &resume_state);

   if ((C90FL_OK == hwio_status) && (RES_PGM == resume_state))
   {
      // resume write
      resume_success = true;
   }

   return (resume_success);
}

//===========================================================================
// C90FL_Write_Flash_Memory
//
// Write flash memory. Using this interface eliminates limitation of
// size and address of flash memory - do not request programmed memory
// shall be 8 byte boundary.
//===========================================================================
bool C90FL_Write_Flash_Memory(uint32_t byte_length,
                             uint32_t source_address,
                             uint32_t destination_address,
                             void *call_function)
{
   volatile uint32_t local_byte_length;
   volatile uint32_t local_source_start_address;
   volatile uint32_t local_destination_start_address;
   volatile uint32_t local_destination_end_address;

   C90FL_Block_Number_T               blocknum;

   uint8_t *source_address_byte_ptr;
   uint8_t *destination_address_byte_ptr;

   uint16_t index;

   volatile uint16_t modul_byte_length;
   uint16_t buffer_modul_head_byte_number;

   volatile bool write_good;

   write_good = true;

   blocknum = C90FL_Get_Block_Number(destination_address);

   if(blocknum < C90FL_Number_of_Blocks)
   {
      if (byte_length > 0)
      {
         // Disable prefetch
         //FLASH_Controller_Interface[MPC5644_FLASH].Initial_Programming();
		 MPC5644_FLASH_Initialize_Programming();
		

         local_byte_length = byte_length;
         local_destination_start_address = destination_address;

         local_source_start_address = source_address;
         local_destination_end_address = destination_address + byte_length;

         // Check flash start address if it's 8 byte boundary
         modul_byte_length = (uint16_t)(local_destination_start_address %
                                        C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY);
         if (modul_byte_length)   // not 8 byte boundary
         {
            // copy flash memory to h7fa_align_boundary_buffer
            local_destination_start_address -= modul_byte_length;
            source_address_byte_ptr = (uint8_t *)local_destination_start_address;
            destination_address_byte_ptr =
                                        (uint8_t *)&c90fl_align_boundary_buffer[0];
            for (index = 0; index < modul_byte_length; index++)
            {
               *destination_address_byte_ptr++ = *source_address_byte_ptr++;
            }

            // copy reprogramming buffer to h7fa_align_boundary_buffer
            source_address_byte_ptr = (uint8_t *)local_source_start_address;

            buffer_modul_head_byte_number = C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY -
                                            modul_byte_length;
            if (local_byte_length >= buffer_modul_head_byte_number)
            {
               // data number in buffer are enough for 8 bytes align
               for (; index < C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY; index++)
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
               for (; index < C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY; index++)
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
                  C90FL_Write(C90FL_Memory_Map[blocknum].ssdConfig,
                             (uint32_t)C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY,
                             (uint32_t *)&c90fl_align_boundary_buffer[0],
                             (uint32_t *)local_destination_start_address,
                             call_function);

            //
            // Since programming source start address shall be 4 byte boundary
            // requested by flash driver, need to adjust buffer
            //
            if (write_good && (local_byte_length != 0))
            {
               local_destination_start_address +=
                                       C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY;

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
             (uint16_t)(local_byte_length % C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY);
            if (modul_byte_length)
            {

               // need to fill reprogramming buffer with flash memory contents
               // read data from block end address in flash memory
             write_good = C90FL_Write(C90FL_Memory_Map[blocknum].ssdConfig,
                                    (local_byte_length-modul_byte_length),
                                    (uint32_t *)local_source_start_address,
                                    (uint32_t *)local_destination_start_address,
                                    call_function);

           if (write_good)
           {
            destination_address_byte_ptr = (uint8_t *)(&c90fl_align_boundary_buffer[0]);
            source_address_byte_ptr = (uint8_t *)(local_source_start_address + local_byte_length - modul_byte_length);

            for (index=0; index < modul_byte_length ; index++)
            {
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
            }

           local_destination_start_address = local_destination_start_address + local_byte_length-modul_byte_length;

            modul_byte_length = C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY -
                                   modul_byte_length;

            source_address_byte_ptr = (uint8_t *)local_destination_end_address;

               // fill buffer to ensure it's 8 byte boundary
               for (index = 0; index < modul_byte_length; index++)
               {
                  *destination_address_byte_ptr++ = *source_address_byte_ptr++;
               }

               write_good = C90FL_Write(C90FL_Memory_Map[blocknum].ssdConfig,
                                    C90FL_PROGRAMMED_FLASH_MEMORY_BOUNDARY,
                                    (uint32_t *)&c90fl_align_boundary_buffer[0],
                                    (uint32_t *)local_destination_start_address,
                                    call_function);
           }

            }
            else
            {

            //
            // write an integral block which both start and end address
            // are 8 byte boundary.
            //
            write_good = C90FL_Write(C90FL_Memory_Map[blocknum].ssdConfig,
                                     local_byte_length,
                                    (uint32_t *)local_source_start_address,
                                    (uint32_t *)local_destination_start_address,
                                    call_function);
            }
         }

         // Enable prefetch
        // FLASH_Controller_Interface[MPC5644_FLASH].Initial_Normal();
		  MPC5644_FLASH_Initialize_Normal();
      }
   }
   else
   {
      write_good = false;
   }

   return (write_good);
}

//===========================================================================
// H7Fa_Flash_ECClogic_Check
//
// ECC logic check function will check the ECC logic of the flash
// The API will simulate a single or double bit fault depending on
// user input
//===========================================================================
bool C90FL_Flash_ECCLogic_Check(uint32_t in_address,
                               uint64_t data_value,
                               uint64_t error_bits,
                               uint32_t ecc_value)
{
   bool ecc_error;

   if(C90FL_OK == ssd_c90fl_FlashECCLogicCheck(C90FL_Memory_Map[0].ssdConfig,
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
// C90FL_Flash_Array_Integrity_Check
//
// Flash array integrity check function will check the array integrity
// of the flash based on the user specified address space
// The API will compare the Multiple Input Signature register (MISR)
// value calculated by the hardware with the values passed by the user
//
//===========================================================================

bool C90FL_Flash_Array_Integrity_Check(uint32_t in_address,
                                      bool addrSeq,
                                      MISR misrValue_Bk0,
                                      MISR misrValue_Bk1,
                                      void *function)
{
   uint32_t low_block_select  = 0;     // selected blocks in low space
   uint32_t mid_block_select  = 0;     // selected blocks in middle space
   uint32_t high_block_select = 0;     // selected blocks in high space
   uint16_t space_block_number;
   C90FL_Block_Number_T      block_number;

   bool integrity_status = false;
   bool integrity_need = true;

   block_number = C90FL_Get_Block_Number(in_address);

   if(block_number <= C90FL_Number_of_Blocks)
   {
      space_block_number = C90FL_Memory_Map[block_number].Address_Space_Block_Number;

      switch (C90FL_Memory_Map[block_number].Address_Space)
      {
         case C90FL_MEMORY_LOW_ADDRESS_SPACE:
         {
            low_block_select = C90FL_Select_Block(low_block_select,
                                                      space_block_number);
            break;
         }

         case C90FL_MEMORY_MID_ADDRESS_SPACE:
         {
            mid_block_select = C90FL_Select_Block(mid_block_select,
                                                      space_block_number);
            break;
         }

         case C90FL_MEMORY_HIGH_ADDRESS_SPACE:
         {
            high_block_select = C90FL_Select_Block(high_block_select,
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
         if(C90FL_OK == ssd_c90fl_FlashArrayIntegrityCheck(C90FL_Memory_Map[block_number].ssdConfig,
                                                 low_block_select,
                                                 mid_block_select,
                                                 high_block_select,
                                                 addrSeq,
                                                 misrValue_Bk0,
                                                 misrValue_Bk1,
                                                 function))
         {
             integrity_status = true;
         }

      }
   }
   return (integrity_status);
}

//===========================================================================
// C90FL_Factory_Margin_Read_Check
//
// Factory Margin Read Check function will check the Factory Margin
// Reads of the flash The user specified margin level is used for
// reads and the operation is done on the specified blocks.
//
//===========================================================================
bool C90FL_Factory_Margin_Read_Check(uint32_t in_address,
                                    bool marginLevel,
                                    MISR misrValue_Bk0,
                                    MISR misrValue_Bk1,
                                    void *function)
{
   C90FL_Block_Number_T      block_number;
   uint32_t low_block_select  = 0;     // selected blocks in low space
   uint32_t mid_block_select  = 0;     // selected blocks in middle space
   uint32_t high_block_select = 0;     // selected blocks in high space
   uint16_t space_block_number;

   bool FMR_status = false;
   bool FMR_need = true;

   block_number = C90FL_Get_Block_Number(in_address);

   if(block_number <= C90FL_Number_of_Blocks)
   {
      space_block_number = C90FL_Memory_Map[block_number].Address_Space_Block_Number;

      switch (C90FL_Memory_Map[block_number].Address_Space)
      {
         case C90FL_MEMORY_LOW_ADDRESS_SPACE:
         {
            low_block_select = C90FL_Select_Block(low_block_select,
                                                      space_block_number);
            break;
         }

         case C90FL_MEMORY_MID_ADDRESS_SPACE:
         {
            mid_block_select = C90FL_Select_Block(mid_block_select,
                                                      space_block_number);
            break;
         }

         case C90FL_MEMORY_HIGH_ADDRESS_SPACE:
         {
            high_block_select = C90FL_Select_Block(high_block_select,
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
         if(C90FL_OK == ssd_c90fl_FactoryMarginReadCheck(C90FL_Memory_Map[block_number].ssdConfig,
                                               low_block_select,
                                               mid_block_select,
                                               high_block_select,
                                               marginLevel,
                                               misrValue_Bk0,
                                               misrValue_Bk1,
                                               function))
         {
             FMR_status = true;
         }

      }
   }

   return (FMR_status);

}



