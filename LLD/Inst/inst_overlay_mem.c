
#include "inst_config.h"
#include "inst_overlay_mem.h"
#include "dd_flash_interface.h"
#include "hal_os.h"




static void INST_Operation_CALLBACK(void)
{
    // operation callbak

     ToggleHWIO_WatchDog();
     SWT_Service_WatchDog(); 
     hwi_kick_wdg_local();
}



/*=============================================================================
 * INST_Calc_Page_Checksum
 * @func Calculate the check sum
 *
 * @parm start addresses,size of data
 * @rdesc  check sum value
 *===========================================================================*/
static uint16_t INST_Calc_Page_Checksum(
      uint16_t *in_data,
      uint16_t in_size )
{
   uint16_t index;
   uint16_t sum = 1;

   for(index = 0; index < in_size; index++)
   {
      sum += in_data[index];
   }

   return sum;
}

/*=============================================================================
 * INST_Compare_Data
 * @func  Compare the data in two addresses
 *
 * @parm EEPROM addresses,NVRAM Mfg addresses,size of data
 *
 * @rdesc return true or false
 *===========================================================================*/
static bool INST_Compare_Data(
      uint32_t * in_data1_ptr,
      uint32_t * in_data2_ptr,
      uint16_t  in_size )
{
   uint16_t index;

   bool data_valid = true;

   for(index = 0; index < in_size; index++)
   {
      if(*in_data1_ptr++ != *in_data2_ptr++)
      {
         data_valid = false;
         break;
      }
   }
   return data_valid;
}

/*=============================================================================
 * Get_Working_Page_RAM_Validation
 * @func  Determine if RAM mirror of working page is valid
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
bool Get_Working_Page_RAM_Validation(void)
{
   bool return_code;
   return_code = false;
   if (CPU_LCI == CPU_Info) 
   {
      if(INST_VALID_PAGE == *((uint16_t *)(INST_WORKING_PAGE_RAM_START_ADDRESS + INST_CHECK_PATTERN_OFFSET)))
      {
         return_code = true;
      }
   }
   else  // Verical is in use
   {
      if(INST_VALID_PAGE == *((uint16_t *)(VERTICAL_WORKING_PAGE_RAM_START_ADDRESS + INST_CHECK_PATTERN_OFFSET)))
      {
         return_code = true;
      }
   }
   return return_code;
}

/*=============================================================================
 * Get_Working_Page_FLASH_Backup_Validation
 * @func  Determine if FLASH backup of working page is valid
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
static bool Get_Working_Page_FLASH_Backup_Validation(void)
{
   bool       return_code;
   uint16_t   backup_cheksum;

   return_code = false;
   backup_cheksum = INST_Calc_Page_Checksum((uint16_t *)(INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS + INST_CAL_DATA_START_OFFSET),(CAL_PAGE_SIZE-4)/2);

   if((INST_VALID_PAGE == *((uint16_t *)(INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS + INST_CHECK_PATTERN_OFFSET))) &&
         ( backup_cheksum == *((uint16_t *)(INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS + INST_CHECKSUM_OFFSET))) 
         && (Cw_CalFORM_ID == *((uint16_t *)(INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS + INST_CAL_VERSION_OFFSET)))
         )
   {
      return_code = true;
   }
   return return_code;
}

/*=============================================================================
 * Get_Reference_Page_Validation
 * @func  Determine if reference page is valid
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
static bool Get_Reference_Page_Validation(void)
{
   bool return_code;
   return_code = false;
   if(INST_VALID_PAGE == *((uint16_t *)(INST_REFERENCE_PAGE_START_ADDRESS + INST_CHECK_PATTERN_OFFSET)))
   {
      return_code = true;
   }
   return return_code;
}

/*=============================================================================
 * INST_Backup_Working_Page
 * @func  Backup working page from mirror RAM to FLASH
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
void INST_Backup_Working_Page(void)
{
   uint16_t               backup_cheksum;
   interrupt_state_t      context;

   if(!INST_Compare_Data((uint32_t *)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,
                         (uint32_t *)INST_WORKING_PAGE_RAM_START_ADDRESS,
                         (CAL_PAGE_SIZE-4)/4))
   {
      // calculate checksum of mirror RAM
      backup_cheksum = INST_Calc_Page_Checksum((uint16_t *)(INST_WORKING_PAGE_RAM_START_ADDRESS+INST_CAL_DATA_START_OFFSET),(CAL_PAGE_SIZE-4)/2);
      // update checksum pattern
      *((uint16_t *)(INST_WORKING_PAGE_RAM_START_ADDRESS + INST_CHECKSUM_OFFSET)) = backup_cheksum;
      // update check pattern
      *((uint16_t *)(INST_WORKING_PAGE_RAM_START_ADDRESS + INST_CHECK_PATTERN_OFFSET)) = INST_VALID_PAGE;

      context = Enter_Critical_Section();
      flash_memory_interface->FLASH_Set_Lock((uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,0);
        if(!flash_memory_interface->FLASH_Check_Erased((uint32_t)CAL_PAGE_SIZE,(uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,INST_Operation_CALLBACK))
      {
         flash_memory_interface->FLASH_Erase_Memory((uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,INST_Operation_CALLBACK);
      }

      flash_memory_interface->FLASH_Program_Memory(CAL_PAGE_SIZE,(uint32_t)INST_WORKING_PAGE_RAM_START_ADDRESS,
                                               (uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,INST_Operation_CALLBACK);

      flash_memory_interface->FLASH_Set_Lock((uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,1);
      Leave_Critical_Section( context );
   }

}

/*=============================================================================
 * INST_Fix_Backup_Page_ECC_Error
 * @func  Clear Backup page for the ECC Error
 *
 * @parm
 *
 * @rdesc 
 *===========================================================================*/
void INST_Fix_Backup_Page_ECC_Error(uint32_t err_addr)
{
   interrupt_state_t      context;  
   if(INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS<=err_addr<(INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS+FLASH_KB(512)))
   {
      context = Enter_Critical_Section();
      flash_memory_interface->FLASH_Set_Lock((uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,0);
      flash_memory_interface->FLASH_Erase_Memory((uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,INST_Operation_CALLBACK);
      flash_memory_interface->FLASH_Set_Lock((uint32_t)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS,1);
      Leave_Critical_Section( context );
   }

}

/*=============================================================================
 * INST_Restore_Working_Page
 * @func  restore mirror ram of working page from FLASH
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
void INST_Restore_Working_Page(HWIO_Reset_Status_T status_poweron)
{
   interrupt_state_t      context;
   uint16_t               ram_index;
   uint32_t*              flash_address;
   uint32_t*              ram_address;
   bool                   restore_needed;

   restore_needed = true;

   if(!status_poweron.bits.Power_On_Reset)   // never power down
   {
      if(Get_Working_Page_RAM_Validation())
      {
         restore_needed = false;
      }

   }

   if(restore_needed)
   {
      if(CPU_LCI == CPU_Info)
      {
         ram_address = (uint32_t *)INST_WORKING_PAGE_RAM_START_ADDRESS;
      
         if(Get_Working_Page_FLASH_Backup_Validation())    // flash back up is valid
         {
            flash_address = (uint32_t *)INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS;
         }
         else
         {
            flash_address = (uint32_t *)INST_REFERENCE_PAGE_START_ADDRESS;
         }
      }
      else if (CPU_VERTICAL == CPU_Info) 
      {
         ram_address = (uint32_t *)VERTICAL_WORKING_PAGE_RAM_START_ADDRESS;
         flash_address = (uint32_t *)INST_REFERENCE_PAGE_START_ADDRESS;
      }
      else
      {
         /* do nothing */
      }
      context = Enter_Critical_Section();
      for( ram_index = 0; ram_index < (CAL_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
      {
         *ram_address++ = *flash_address++;
      }
      Leave_Critical_Section( context );
   }
}

/*=============================================================================
 * INST_Restore_Working_Page_Again
 * @func  restore mirror ram of working page from reference
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
void INST_Restore_Working_Page_Again(void)
{
   interrupt_state_t      context;
   uint16_t               ram_index;
   uint32_t*              flash_address;
   uint32_t*              ram_address;

   if (CPU_LCI == CPU_Info) 
   {
      ram_address = (uint32_t *)INST_WORKING_PAGE_RAM_START_ADDRESS;
   }
   else // vertical is in use
   {
      ram_address = (uint32_t *)VERTICAL_WORKING_PAGE_RAM_START_ADDRESS;
   }

   flash_address = (uint32_t *)INST_REFERENCE_PAGE_START_ADDRESS;

   context = Enter_Critical_Section();
   for( ram_index = 0; ram_index < (CAL_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
   {
      *ram_address++ = *flash_address++;
   }
   Leave_Critical_Section( context );

}


