//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            hal_emulated_eeprom.c %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      zzrfyj %
//
// %date_modified:        %
//
// %version:         5 %
//
//=============================================================================
#include "io_config_eeprom.h"
//#include "hal_nvm.h"
//#include "fileseei.h"
//#include "filepmng.h"   /* UpdateFILE_NVM_Checksum   */
#include "hal_emulated_eeprom.h"
#include "hal_eeprom_nvm.h"
#include "dd_swt_interface.h"
#include "hal_ucram.h"
#include "hal_os.h"
#include "dd_sswt.h"

/*=============================================================================
 * Marco Definitions
 *===========================================================================*/
#define INVALID_BANK                    (0xFF)
#define INVALID_ADDR                    (0)
#define BLANK_PAGE_DATA                 (0xFFFF)
#define VALID_PAGE_DATA                 (0xA55A)
#define ALL_PAGES_INVALID               (0xFF)

/*=============================================================================
 * Public Variables Definitions
 *===========================================================================*/
uint8_t                   EEP_NVRAM_active_page=0;
bool                      EEP_NVM_full_flg=0;
uint8_t                   Mfg_change_flg = 0;
uint8_t                   No_active_page_flg=0;
EEPROM_State_T            Present_EEPROM_State = EEPROM_NULL;
uint16_t                  High_sequence_No_EEP_NVM=0;
uint32_t                  High_sequence_No_EEP_NVRAM=0;
bool                      EEP_NVM_Fault=0;




/*=============================================================================
 * const Definitions
 *===========================================================================*/

const EEPROM_Page_T EEPROM_Pages[EEP_NVRAM_MAX_PAGE] =
{
   {
      (uint32_t *)(EEP_NVRAM_BANK0_START_ADDR + (NVRAM_PAGE_SIZE * 0)),
      (uint32_t *)(EEP_NVRAM_BANK0_START_ADDR + (NVRAM_PAGE_SIZE * 1)),
      true,
      EEP_NVRAM_BANK0_START_ADDR
   },
   {
      (uint32_t *)(EEP_NVRAM_BANK0_START_ADDR + (NVRAM_PAGE_SIZE * 1)),
      (uint32_t *)(EEP_NVRAM_BANK1_START_ADDR + (NVRAM_PAGE_SIZE * 0)),
      false,
      EEP_NVRAM_BANK0_START_ADDR
   },
   {
      (uint32_t *)(EEP_NVRAM_BANK1_START_ADDR + (NVRAM_PAGE_SIZE * 0)),
      (uint32_t *)(EEP_NVRAM_BANK1_START_ADDR + (NVRAM_PAGE_SIZE * 1)),
      true,
      EEP_NVRAM_BANK1_START_ADDR
   },
   {
      (uint32_t *)(EEP_NVRAM_BANK1_START_ADDR + (NVRAM_PAGE_SIZE * 1)),
      (uint32_t *)(EEP_NVRAM_BANK0_START_ADDR + (NVRAM_PAGE_SIZE * 0)),
      false,
      EEP_NVRAM_BANK1_START_ADDR
   }
};

/*===========================================================================
 *  @func EEPROM_Get_Mirror_RAM_check_pattern from mirror memory
 *  @parm nvram_start_addr : mirror ram start address
 *  @rdesc  Returns an _pattern
 *===========================================================================*/
static uint16_t EEPROM_Get_Mirror_RAM_check_pattern( uint32_t*  nvram_start_addr )
{
   uint16_t* pattern_address = (uint16_t*)nvram_start_addr;

   return *pattern_address & 0xFFFF;
}

/*===========================================================================
 *  @func EEPROM_Get_Mirror_RAM_NV_KKSUM
 *  @parm   nvram_start_addr : mirror ram start address
 *  @rdesc  Returns NV_KKSUM
 *===========================================================================*/
static uint16_t EEPROM_Get_Mirror_RAM_NV_KKSUM( uint32_t*  nvram_start_addr )
{
   uint16_t  in_checksum;
   uint16_t* checksum_address = &((uint16_t*)nvram_start_addr)[3];

   in_checksum = *checksum_address;
   return in_checksum & 0xFFFF;
}

/*=============================================================================
 * EEPROM_NVM_Compare_Data
 * @func  Compare the data in two addresses
 *
 * @parm EEPROM addresses,NVRAM Mfg addresses,size of data
 *
 * @rdesc return true or false
 *===========================================================================*/
static bool EEPROM_NVM_Compare_Data(
      uint8_t * in_data1_ptr,
      uint8_t * in_data2_ptr,
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
 * EEPROM_Calc_Page_Checksum
 * @func Calculate the check sum
 *
 * @parm start addresses,size of data
 * @rdesc  check sum value
 *===========================================================================*/
static uint16_t EEPROM_Calc_Page_Checksum(
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
 * EEPROM_Set_Mirror_RAM_Pattern
 * @func Set valid page pattern to mirror ram
 * @parm start addresses,in_pattern
 * @rdesc  check sum value
 *===========================================================================*/
static void EEPROM_Set_Mirror_RAM_Pattern(
      uint32_t* in_nvm_base_address,
      uint16_t  in_pattern )
{
   uint16_t* pattern_address;

   pattern_address = (uint16_t*)(in_nvm_base_address);
   *pattern_address = in_pattern;
}

/*=============================================================================
 * EEPROM_Set_Mirror_RAM_Sequence_No
 * @func EEPROM_Set_NVRAM_Sequence_No
 * @parm start addresses,Sequence_no
 * @rdesc  none.
 *===========================================================================*/
static void EEPROM_Set_Mirror_RAM_Sequence_No(
      uint32_t* in_nvm_base_address,
      uint32_t  Sequence_no )
{
   uint32_t* pattern_address = (uint32_t*)(in_nvm_base_address);

   *pattern_address = Sequence_no;
}

/*=============================================================================
 * EEPROM_Get_EEP_NVRAM_Pattern
 * @func Get valid page pattern from EEP_NVRAM
 *
 * @parm page
 * @rdesc  uint16_t
 *===========================================================================*/
static uint16_t EEPROM_Get_EEP_NVRAM_Pattern(
      uint8_t in_page )
{
   uint16_t* pattern_address = (uint16_t*)EEPROM_Pages[in_page].Current;
   return *pattern_address & 0xFFFE;
}

/*=============================================================================
 * EEPROM_Get_EEP_NVRAM_Sequence_Number
 * @func Get sequence number of NVRAM from EEP_NVRAM
 * @parm page
 * @rdesc  uint32_t
 *===========================================================================*/
static uint32_t EEPROM_Get_EEP_NVRAM_Sequence_Number(
      uint8_t in_page )
{
   uint32_t* sequence_number_address = (uint32_t*)((uint16_t*)EEPROM_Pages[in_page].Current + 1 );
   return *sequence_number_address;
}

/*=============================================================================
 * EEPROM_Get_EEP_NVRAM_MFG_Sequence_Number
 * @func Get sequence number of MFG in NVRAM from EEP_NVRAM
 * @parm page
 * @rdesc  uint32_t
 *===========================================================================*/
static uint16_t EEPROM_Get_EEP_NVRAM_MFG_Sequence_Number(
      uint8_t in_page )
{
   uint16_t* sequence_number_address = (uint16_t*)((uint32_t*)EEPROM_Pages[in_page].Current + 2 ); // offset to MFG start in NVRAM
   sequence_number_address++; // offset 2 bytes checksum pattern
   return *sequence_number_address;
}

/*=============================================================================
 * EEPROM_Set_Mirror_RAM_Checksum
 * @func Set NVRAM checksum in mirror RAM
 * @parm start addresses,in_checksum
 * @rdesc  none
 *===========================================================================*/
static void EEPROM_Set_Mirror_RAM_Checksum(
      uint32_t* in_nvm_base_address,
      uint16_t  in_checksum )
{
   uint16_t* checksum_address = &((uint16_t*)in_nvm_base_address)[(NVRAM_PAGE_SIZE/sizeof(uint16_t))-1];
   *checksum_address = in_checksum;
}

/*=============================================================================
 * EEPROM_Set_Mirror_RAM_KKSUM_Checksum
 * @func Set KKSUm to mirror ram
 * @parm in_page
 * @rdesc  none
 *===========================================================================*/
static void EEPROM_Set_Mirror_RAM_KKSUM_Checksum(
      uint32_t* in_nvm_base_address,
      uint16_t  in_checksum )
{
   uint16_t* checksum_address = &((uint16_t*)in_nvm_base_address)[3];

   *checksum_address = in_checksum;
}

/*=============================================================================
 * EEPROM_Get_EEP_NVRAM_Checksum
 * @func Get page checksum from EEP_NVRAM
 * @parm in_page
 * @rdesc  check sum value
 *===========================================================================*/
static uint16_t EEPROM_Get_EEP_NVRAM_Checksum(
      uint8_t in_page )
{
   uint16_t* checksum_address = (uint16_t*)EEPROM_Pages[in_page].Current;
   return checksum_address[(NVRAM_PAGE_SIZE/sizeof(uint16_t))-1];
}
/*=============================================================================
 * EEPROM_Get_EEP_NVM_MFG_Pattern
 * @func Get the MFG pattern from EEP_NVM
 *
 * @parm page number
 * @rdesc pattern
 *===========================================================================*/
static uint16_t EEPROM_Get_EEP_NVM_MFG_Pattern(uint8_t in_page )
{
   uint16_t* pattern_address = (uint16_t*)(EEP_NVM_MFG_START_ADDR + in_page * MFG_PAGE_SIZE);
   return *pattern_address;
}

// FIEXME - A... HAL layer is not supposed to invoke variables from applicaton
#if 0
/*=============================================================================
 * EEPROM_Get_MFG_Data_Start_Address
 * @func EEPROM_Get_MFG_Data_Start_Address
 * @parm none
 * @rdesc  EEPROM_Get_MFG_Data_Start_Address
 *===========================================================================*/
uint32_t* EEPROM_Get_MFG_Data_Start_Address(void)
{
   return (uint32_t *)&NsFILE_NVM_EE_ManufactData;
}

/*=============================================================================
 * EEPROM_Get_size_of_MFG_Data
 * @func EEPROM_Get_size_of_MFG_Data
 * @parm none
 * @rdesc  EEPROM_Get_size_of_MFG_Data
 *===========================================================================*/
uint16_t EEPROM_Get_size_of_MFG_Data(void)
{
   return sizeof(NsFILE_NVM_EE_ManufactData);
}
#endif

/*=============================================================================
 * Get_KKSUM_checksum
 * @func find out the code check sum  from the Pflash application software ..
 * @parm  none
 * @rdesc	pass or fail
 *===========================================================================*/
static uint16_t Get_KKSUM_checksum(void)
{
   uint16_t  pf_kksum;
   uint32_t  *pf_addr;
   pf_addr = (uint32_t*)PF_KKSUM_ADDRESS;
   pf_kksum = *((uint16_t *)pf_addr);
   return (pf_kksum);
}

/*=============================================================================
 * Mem_BlankTest
 * @func find out is the memory blank.
 * @parm  none
 * @rdesc	TRUE (memory blank) or FALSE (memory not blank)
 *===========================================================================*/
static uint8_t Mem_BlankTest(uint16_t *in_address, uint16_t in_size)
{
   int16_t index;
   uint8_t result = true;

   for (index = 0; (index < in_size) && (result == true); index++)
   {
      if (*in_address++ != BLANK_PAGE_DATA) result = false;
   }

   return result;
}

/*=============================================================================
 * Get_EEP_NVRAM_Active_Page
 * @func Find out EEP_NVRAM_Active_Page  from EEP NVRAM..
 *		 Sort all the sequence numbers in all the pages and set
 *		 the page with the highest sequence number as the most
 *		 active page
 * @parm  none
 * @rdesc  pass or fail
 *===========================================================================*/
static EEPROM_ACTIVE_PAGE_T Get_EEP_NVRAM_Active_Page(void)
{
   uint8_t                          page;
   uint32_t                         temp_sequence_num = 0;
   uint32_t                         Present_Sequence_No;
   uint32_t                         *Sequence_No_Addr;
   uint8_t                          pass_flg;
   uint16_t                         stored_check_sum;
   uint16_t                         calculated_check_sum;
   uint8_t                          count;
   EEPROM_ACTIVE_PAGE_T             op_return = EEPROM_ACTIVE_PAGE_NOT_FOUND;
   EEPROM_SeqNum_T	               sort_seq_num[EEP_NVRAM_MAX_PAGE];

   EEP_NVRAM_active_page = 0;
   pass_flg = 0;

   /* erase successful, reset flags */
   if ((BANK_CORRUPTED_PATTERN == Backup_Disrupted.Bank0_Corrupted) && (BANK_CORRUPTED_PATTERN == Backup_Disrupted.Bank1_Corrupted))
   {
      return(op_return);
   }
   else
   {
      /* sort EEP NVRAM pages by sequence number in ascending order */
      for(page = 0; page < EEP_NVRAM_MAX_PAGE; page++)
      {
         if(page < EEP_NVRAM_PER_BANK_PAGES )
         {
            if (BANK_CORRUPTED_PATTERN == Backup_Disrupted.Bank0_Corrupted)
            {
               temp_sequence_num = 0;
            }
            else
            {
               Sequence_No_Addr = (uint32_t*)(EEP_NVRAM_BANK0_START_ADDR + page * NVRAM_PAGE_SIZE + 2 );
               temp_sequence_num = *Sequence_No_Addr;
            }
         }
         else if (page >= EEP_NVRAM_PER_BANK_PAGES)
         {
            if (BANK_CORRUPTED_PATTERN == Backup_Disrupted.Bank1_Corrupted)
            {
               temp_sequence_num = 0;
            }
            else
            {
               Sequence_No_Addr = (uint32_t*)(EEP_NVRAM_BANK1_START_ADDR + (page - EEP_NVRAM_PER_BANK_PAGES) * NVRAM_PAGE_SIZE + 2 );
               temp_sequence_num = *Sequence_No_Addr;
            }
         }
         Present_Sequence_No = temp_sequence_num;

         count = page;
         while ((count > 0) &&
               (Present_Sequence_No < sort_seq_num[count-1].seqno))
         {
            sort_seq_num[count] = sort_seq_num[count-1];
            sort_seq_num[count-1].seqno = 0;
            count--;
         }
         sort_seq_num[count].page = page;
         sort_seq_num[count].seqno = Present_Sequence_No;
      }

      /* search for active page starting with the highest sequence number (at top of array) */
      count = EEP_NVRAM_MAX_PAGE - 1;
      while (((count >= 0) && (count < EEP_NVRAM_MAX_PAGE)) && (pass_flg == 0))
      {
         if (sort_seq_num[count].seqno != 0xFFFFFFFF)
         {
            stored_check_sum = EEPROM_Get_EEP_NVRAM_Checksum(sort_seq_num[count].page);
            calculated_check_sum = EEPROM_Calc_Page_Checksum((uint16_t*)EEPROM_Pages[sort_seq_num[count].page].Current, (NVRAM_PAGE_SIZE - sizeof(uint16_t))/2);
            /* check for valid check pattern and page checksum */
            if ((EEPROM_Get_EEP_NVRAM_Pattern(sort_seq_num[count].page) == VALID_PAGE_DATA) &&
                  (stored_check_sum == calculated_check_sum))
            {
               /* EEP NVRAM active page found */
               High_sequence_No_EEP_NVRAM = sort_seq_num[count].seqno;
               pass_flg = 1;
               EEP_NVRAM_active_page = sort_seq_num[count].page;
               op_return = EEPROM_ACTIVE_PAGE_FOUND;
            }
         }

         count--;
      }
      /* if MFG NVM is full and "read MFG NVM data from MFG NVM" flag not set */
      if ((1 == EEP_NVM_full_flg) && (0 == No_active_page_flg))
      {
         if (1 == pass_flg) /* EEP NVRAM active page found */
         {
            /* retrieve MFG NVM sequence number in DFLASH*/
            pass_flg = 0;
            High_sequence_No_EEP_NVM = EEPROM_Get_EEP_NVRAM_MFG_Sequence_Number(EEP_NVRAM_active_page);
            /* if MFG NVRAM sequence number < EEP_NVM_MFG_SEQUENCE_NO_MAX set read MFG NVM data from EEP NVM flag */
            if (High_sequence_No_EEP_NVM < EEP_NVM_MFG_SEQUENCE_NO_MAX )
            {
               No_active_page_flg = 1;
            }
            else
            {
               /* nil */
            }
         }
         else
         {
            /* nil */
         }
      }
      else
      {
         /* nil */
      }

      return(op_return);
   }
}


/*=============================================================================
 * Get_EEP_NVM_Active_Page
 * @func Find out high sequence number from EEP NVM.
 * @parm  none
 * @rdesc  pass or fail, High_sequence_No_EEP_NVM updated
 *===========================================================================*/
static EEPROM_ACTIVE_PAGE_T Get_EEP_NVM_Active_Page(void)
{
   uint16_t                *mfg_nvm_addr;
   uint16_t                Prev_Sequence_No;
   uint16_t                Present_Sequence_No;
   uint8_t                 index;
   uint16_t                calculated_checksum;
   uint16_t                stored_checksum;
   uint16_t                *src;

   EEPROM_ACTIVE_PAGE_T   op_return = EEPROM_ACTIVE_PAGE_NOT_FOUND;

   Prev_Sequence_No = 0;
   Present_Sequence_No = 0;

   /* find the most recently used MFG NVM page - forward search
    *  criteria: next page is empty and sequence number must match the page index
    */
   for(index = 0; index < EEP_NVM_MFG_SEQUENCE_NO_MAX; index++ )
   {
      if (Present_Sequence_No == index)
      {
         Prev_Sequence_No = Present_Sequence_No;
      }
      mfg_nvm_addr = (uint16_t *)Get_EEP_NVM_MFG_ADDRESS(index);
      Present_Sequence_No = *(uint16_t *)((uint8_t *)(mfg_nvm_addr) + MFG_SEQNO_ADDR_OFFSET);
      /* search from EEP NVM page 0 to page (EEP_NVM_MFG_SEQUENCE_NO_MAX - 1) */
      if (	   (Present_Sequence_No == BLANK_PAGE_DATA)
            && (Prev_Sequence_No != BLANK_PAGE_DATA) )
      {
         if (Mem_BlankTest(mfg_nvm_addr, MFG_PAGE_SIZE/2) == true)
         {
            High_sequence_No_EEP_NVM = Prev_Sequence_No;
            break;
         }
      }
      else if (index == (EEP_NVM_MFG_SEQUENCE_NO_MAX-1)) /* at last page */
      {
         /* end of search */
         EEP_NVM_full_flg = 1; /* set MFG in NVM is full flag */
         /* last EEP NVM page sequence number is EEP_NVM_MFG_SEQUENCE_NO_MAX not other values */
         if (Present_Sequence_No == EEP_NVM_MFG_SEQUENCE_NO_MAX )
         {
            /* "read MFG NVM data from EEP NVM" flag is set */
            if(1 == No_active_page_flg )
            {
               High_sequence_No_EEP_NVM = EEP_NVM_MFG_SEQUENCE_NO_MAX;
            }
            else
            {
               /* exit without identifying any MFG NVM active page */
               op_return = EEPROM_ACTIVE_PAGE_FOUND;
               return(op_return);
            }
         }
         else
         {
         }
      }
   }

   /* find the active page with valid page check pattern and checksum - backward search */
   for (index = High_sequence_No_EEP_NVM; index > 0; index--)
   {
      src = (uint16_t*)Get_EEP_NVM_MFG_ADDRESS(index-1);
      calculated_checksum = EEPROM_Calc_Page_Checksum(src, (MFG_PAGE_SIZE - MFG_CHKSUM_OFFSET_SIZE)/2);
      stored_checksum	  = *((uint16_t *)( (uint8_t *)src + MFG_CHKSUM_ADDR_OFFSET ));
      if ( (*( (uint16_t *)( (uint8_t *)src + MFG_PATTERN_ADDR_OFFSET) ) == VALID_PAGE_DATA)
            &&(calculated_checksum == stored_checksum) )
      {
         High_sequence_No_EEP_NVM = index;
         op_return = EEPROM_ACTIVE_PAGE_FOUND;
         break;
      }
   }

   if (EEPROM_ACTIVE_PAGE_NOT_FOUND == op_return)
   {
      High_sequence_No_EEP_NVM = 0;
   }

   return(op_return);
}
/*=============================================================================
 * EEP_Operation_CALLBACK
 * @func callback function when eep operation is ongoing
 * @parm  bank
 * @rdesc  none
 *===========================================================================*/
static void EEP_Operation_CALLBACK(void)
{
    //feeding watchdog here
    //fash key on fucntion can be implemented here
//#ifndef HWTEST
 SWT_Service_WatchDog(); 
 //ToggleHWIO_WatchDog();
 TLE4471_WD_Toggle_Immediate();
 hwi_kick_wdg_local();
//#endif
}
/*=============================================================================
 * EEP_NVRAM_Erase
 * @func Erase  bank 0 or bank1 or both the banks of EEP NVRAM.
 * @parm  bank
 * @rdesc  none
 *===========================================================================*/
static void EEP_NVRAM_Erase(uint8_t  bank)
{
   interrupt_state_t context;
   uint32_t EEPROM_BANK_START_ADDR;

   if( EEP_NVRAM_BANK0 == bank )
   {
      EEPROM_BANK_START_ADDR = (uint32_t )EEP_NVRAM_BANK0_START_ADDR;
      Backup_Disrupted.Bank0_Corrupted = BANK_CORRUPTED_PATTERN;
   }
   else
   {
      EEPROM_BANK_START_ADDR = (uint32_t )EEP_NVRAM_BANK1_START_ADDR;
      Backup_Disrupted.Bank1_Corrupted = BANK_CORRUPTED_PATTERN;
   }

   context = Enter_Critical_Section();
   flash_memory_interface->FLASH_Set_Lock(EEPROM_BANK_START_ADDR,0);
   flash_memory_interface->FLASH_Erase_Memory(EEPROM_BANK_START_ADDR,EEP_Operation_CALLBACK);
   flash_memory_interface->FLASH_Set_Lock(EEPROM_BANK_START_ADDR,1);
   Leave_Critical_Section(context);

   /* erase successful, reset flags */
   if( EEP_NVRAM_BANK0 == bank )
   {
      Backup_Disrupted.Bank0_Corrupted = BANK_NOT_CORRUPTED_PATTERN;
   }
   else
   {
      Backup_Disrupted.Bank1_Corrupted = BANK_NOT_CORRUPTED_PATTERN;
   }

   /* Calculate and store the NVM checksum */
   // FIXME - A... ensure it can be removed
//   UpdateFILE_NVM_Checksum();
}

/*===========================================================================
 * EEPROM_Erase_NVM_BLOCK
 *  @func Erase EEP NVM block, for development only
 *  @parm    none
 *  @rdesc  none
 *===========================================================================*/
static void EEPROM_Erase_NVM_BLOCK(void)
{
   interrupt_state_t context;
   context = Enter_Critical_Section();
   flash_memory_interface->FLASH_Set_Lock((uint32_t)(EEP_NVM_START_ADDR),0);
   flash_memory_interface->FLASH_Erase_Memory((uint32_t)(EEP_NVM_START_ADDR),EEP_Operation_CALLBACK);
   flash_memory_interface->FLASH_Set_Lock((uint32_t)(EEP_NVM_START_ADDR),1);
   Leave_Critical_Section(context);
}

/*=============================================================================
 * Clear_Vehicle_NVRAM_In_Mirror
 * @func Clear Vehicle NVRAM part.
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
static void Clear_Vehicle_NVRAM_In_Mirror(void)
{
   uint32_t *           nvram_start_addr;
   uint16_t             ram_index;
   interrupt_state_t    context;

   nvram_start_addr = (uint32_t *)MIRROR_RAM_START_ADDR;
   context = Enter_Critical_Section();
   for( ram_index = 0; ram_index < (NVRAM_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
   {
      *nvram_start_addr++ = 0x0;
   }
   Leave_Critical_Section(context);
}

/*=============================================================================
 * EEPROM_Write_Block
 * @func EEPROM_Write_Block
 *
 * @parm in_nvm_address,in_page
 * @rdesc  page
 *===========================================================================*/
static void EEPROM_Write_Block(
      uint32_t* in_nvm_address,
      uint8_t   in_page,uint8_t  bank)
{
   uint16_t               page_index;
   uint16_t               pf_kksum;
   uint32_t*              nvm_mfg_data_start_addr;
   uint32_t*              mfg_start_addr;
   uint16_t               data_buffer_temp[(MFG_PAGE_SIZE/sizeof(uint16_t))]; /* local copy of mfg data */
   uint8_t                index;

   interrupt_state_t      context;

   nvm_mfg_data_start_addr =(uint32_t *) RAM_MFG_DATA_START_ADDR;
   mfg_start_addr = (uint32_t *)RAM_MFG_START_ADDR;

   pf_kksum         = Get_KKSUM_checksum();

   if(EEPROM_ACTIVE_PAGE_FOUND == bank)
   {
      EEPROM_Set_Mirror_RAM_KKSUM_Checksum(in_nvm_address,pf_kksum);
      High_sequence_No_EEP_NVRAM ++;
   }
   else if(EEPROM_ACTIVE_PAGE_NOT_FOUND == bank)
   {
      EEPROM_Set_Mirror_RAM_KKSUM_Checksum(in_nvm_address,0);
      High_sequence_No_EEP_NVRAM = 1;
   }
   EEPROM_Set_Mirror_RAM_Pattern( in_nvm_address, (uint16_t)VALID_PAGE_DATA);
   EEPROM_Set_Mirror_RAM_Sequence_No((uint32_t *)(((uint8_t *) in_nvm_address) + 2), High_sequence_No_EEP_NVRAM);
   if(1 == EEP_NVM_full_flg)
   {
      if(1 == Mfg_change_flg)
      {
         Mfg_change_flg =0;
         for(index = 0; index< (MFG_PAGE_SIZE/sizeof(uint16_t)); index++)
         {
            data_buffer_temp[index] = 0x0000;
         }
         data_buffer_temp[0] = VALID_PAGE_DATA;
         data_buffer_temp[1] = High_sequence_No_EEP_NVM+1;
         memcpy(&data_buffer_temp[2], ((uint16_t *)nvm_mfg_data_start_addr), (MFG_PAGE_SIZE-6));
         data_buffer_temp[(MFG_PAGE_SIZE/sizeof(uint16_t))-1] = EEPROM_Calc_Page_Checksum((uint16_t*)(&data_buffer_temp[0]),(MFG_PAGE_SIZE-sizeof(uint16_t))/2);
         memcpy(((uint16_t *)mfg_start_addr), &data_buffer_temp[0], MFG_PAGE_SIZE);
      }
   }
   //Calculate the checksum;
   EEPROM_Set_Mirror_RAM_Checksum( in_nvm_address, EEPROM_Calc_Page_Checksum((uint16_t*)in_nvm_address, (NVRAM_PAGE_SIZE - sizeof(uint16_t))/2) );

   context = Enter_Critical_Section();
   flash_memory_interface->FLASH_Set_Lock((uint32_t)EEPROM_Pages[in_page].Current,0);
   flash_memory_interface->FLASH_Program_Memory(NVRAM_PAGE_SIZE,(uint32_t)in_nvm_address,(uint32_t)EEPROM_Pages[in_page].Current,EEP_Operation_CALLBACK);
   flash_memory_interface->FLASH_Set_Lock((uint32_t)EEPROM_Pages[in_page].Current,1);
   Leave_Critical_Section( context );
}

/*=============================================================================
 * Get_KKSUM_EEP_NVRAM
 * @func Get NV_KKSUM from EEP NVRAM.
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
static uint16_t Get_KKSUM_EEP_NVRAM(uint8_t  in_page)
{
   uint16_t* checksum_address = (uint16_t*)EEPROM_Pages[in_page].Current;

   return checksum_address[3];
}

/*=============================================================================
 * EEPROM_Write_Mfg_Block
 * @func Write  MFG data into EEP NVM
 * @parm  Mfg addresses,page number
 * @rdesc  none
 *===========================================================================*/
static void EEPROM_Write_Mfg_Block( uint32_t *in_mfg_address,uint8_t  in_page )
{
   uint16_t               page_index;
   uint32_t               flash_page_addr;
   interrupt_state_t      context;
   uint32_t *             mfg_start_addr;
   uint16_t               data_buffer_temp[(MFG_PAGE_SIZE/sizeof(uint16_t))]; /* local copy of mfg data */
   uint8_t                index;

   mfg_start_addr  = (uint32_t *)RAM_MFG_START_ADDR;

   flash_page_addr = Get_EEP_NVM_MFG_ADDRESS(in_page);

   for(index = 0; index< (MFG_PAGE_SIZE/sizeof(uint16_t)); index++)
   {
      data_buffer_temp[index] = 0x0000;
   }
   data_buffer_temp[0] = VALID_PAGE_DATA;
   data_buffer_temp[1] = in_page+1;
   memcpy(&data_buffer_temp[2], ((uint16_t *)in_mfg_address), (MFG_PAGE_SIZE-6));
   data_buffer_temp[(MFG_PAGE_SIZE/sizeof(uint16_t))-1] = EEPROM_Calc_Page_Checksum((uint16_t*)(&data_buffer_temp[0]),(MFG_PAGE_SIZE-sizeof(uint16_t))/2);
   memcpy(((uint16_t *)mfg_start_addr), &data_buffer_temp[0], MFG_PAGE_SIZE);

   context = Enter_Critical_Section();
   flash_memory_interface->FLASH_Set_Lock(flash_page_addr,0);
   flash_memory_interface->FLASH_Program_Memory(MFG_PAGE_SIZE,(uint32_t)mfg_start_addr,flash_page_addr,EEP_Operation_CALLBACK);
   flash_memory_interface->FLASH_Set_Lock(flash_page_addr,1);
   Leave_Critical_Section( context );

}

/*=============================================================================
 * EEPROM_Get_Current_Bank
 * @func Check if address passed is on bank 0 or 1
 * @parm  addr
 * @rdesc  bank
 *===========================================================================*/
uint8_t EEPROM_Get_Current_Bank(uint32_t addr)
{
   uint8_t bank = INVALID_BANK;

   if (addr >= EEP_NVRAM_BANK0_START_ADDR &&
         addr < (EEP_NVRAM_BANK0_START_ADDR + NVRAM_PAGE_SIZE * EEP_NVRAM_PER_BANK_PAGES))
   {
      bank = EEP_NVRAM_BANK0;
   }
   else if (addr >= EEP_NVRAM_BANK1_START_ADDR &&
         addr < (EEP_NVRAM_BANK1_START_ADDR + NVRAM_PAGE_SIZE * EEP_NVRAM_PER_BANK_PAGES))
   {
      bank = EEP_NVRAM_BANK1;
   }
   else
   {
      /* nil */
   }

   return bank;
}

/*******************************************************************************
 *
 * Function:    EEPROM_Backup_Vehicle_NVRAM_Block
 *
 * Description: This function performs the Vehicle MVRAM backup operation when
 *              the ECM does housekeeping when powering down.This operation
 *              starts after MFG NVM backup is completed.
 *              (1) It searches for the next available empty page after the
 *                  current active page in the DFlash and takes the backup there.
 *              (2) When the MFG NVM sequence page number value is smaller than
 *                  or equal to 62 the MFG NVM is backup to both the PFlash and
 *                  DFlash.It is backup only to DFlash otherwise.
 *
 * Parameters:  none
 * Return:      none
 *
 *******************************************************************************/
void EEPROM_Backup_Vehicle_NVRAM_Block(void)
{
   bool                   blank_check = false;
   uint32_t *             nvram_start_addr;
   uint8_t                page;
   uint32_t *             nvm_mfg_data_start_addr;
   EEP_NVRAM_BANK_T       not_active_bank;
   EEPROM_ACTIVE_PAGE_T   op_return;

   Present_EEPROM_State = EEPROM_BACKUP;

   //LMB_ERROR_LOCK_BIT = 0;

   nvram_start_addr = (uint32_t *)MIRROR_RAM_START_ADDR;

   nvm_mfg_data_start_addr = (uint32_t *) RAM_MFG_DATA_START_ADDR;

   if( BANK_CORRUPTED_PATTERN == Backup_Disrupted.Bank0_Corrupted )
   {
      EEP_NVRAM_Erase(0);
   }
   if( BANK_CORRUPTED_PATTERN == Backup_Disrupted.Bank1_Corrupted )
   {
      EEP_NVRAM_Erase(1);
   }

   op_return = Get_EEP_NVRAM_Active_Page();

   if( EEPROM_ACTIVE_PAGE_FOUND == op_return)
   {
      page = EEP_NVRAM_active_page;
      not_active_bank = ((page > (EEP_NVRAM_PER_BANK_PAGES-1))?(EEP_NVRAM_BANK0):(EEP_NVRAM_BANK1));

      if (!EEPROM_NVM_Compare_Data((uint8_t*)(EEPROM_Pages[page].Current), (uint8_t*)nvram_start_addr, NVRAM_PAGE_SIZE))
      {
         if (1 == EEP_NVM_full_flg)
         {
            if (!EEPROM_NVM_Compare_Data((uint8_t*)((uint8_t*)EEPROM_Pages[page].Current + 10),(uint8_t*)nvm_mfg_data_start_addr,(MFG_PAGE_SIZE - 4)))
            {
               Mfg_change_flg = 1;
            }
         }
         while (false == blank_check)
         {
            page++;
            if ((EEP_NVRAM_MAX_PAGE) <= page)
            {
               page = 0;
            }
            if (true == Mem_BlankTest(((uint16_t*)(EEPROM_Pages[page].Current)), (NVRAM_PAGE_SIZE/2)))
            {
               blank_check = true;
            }
            if ((page == EEP_NVRAM_active_page) || ((true == blank_check) && ((0 == page) || (2 == page))))
            {
               EEP_NVRAM_Erase(not_active_bank);
               page = ((EEP_NVRAM_BANK0 == not_active_bank)?(0):(EEP_NVRAM_PER_BANK_PAGES));
               blank_check = true;
            }
         }
         EEPROM_Write_Block( nvram_start_addr, page,EEPROM_ACTIVE_PAGE_FOUND);
      }
      else
      {

      }
   }
   else
   {
      EEP_NVRAM_Erase(0);
      EEP_NVRAM_Erase(1);
      page = 0;
      Mfg_change_flg = 1;
      High_sequence_No_EEP_NVM = EEP_NVM_MFG_SEQUENCE_NO_MAX;
      EEPROM_Write_Block((uint32_t*)nvram_start_addr,page,EEPROM_ACTIVE_PAGE_NOT_FOUND);

   }
   No_active_page_flg = 0;

}

/*******************************************************************************
 *
 * Function:    EEPROM_Restore_Vehicle_NVRAM_Block
 *
 * Description: This function is  executed right after ECM reset operation.It
 *              restores the Vehicle data, whose backup had been taken in
 *              EEPROM_Backup_Vehicle_NVRAM_Block ,from DFlash back to
 *              the mirror memory .
 *              (1) It compares the Application software checksum PF_KKSUM
 *                  stored in PFlash with the DF_KKSUM stored in DFlash.If both
 *                  are equal then restore operation proceeeds further else
 *                  all stored data in PFlash and DLash are cleared along with
 *                  mirror memory data.
 *              (2) Based on comparison of the 2 checksums and the kind of reset
 *                  taking place the restore operation is performed.
 *
 * Parameters:  SCU_Reset_Status_T status
 * Return:      none
 *
 *******************************************************************************/
void EEPROM_Restore_Vehicle_NVRAM_Block(HWIO_Reset_Status_T status_poweron)
{
   uint32_t *             nvram_start_addr;
   uint32_t *             src;
   uint32_t *             mfg_data_start_addr;
   uint8_t                page;
   uint16_t               ram_index;
   interrupt_state_t      context;
   uint16_t               pf_kksum;
   uint16_t               df_kksum;
   uint16_t               nvram_check_pattern;
   uint16_t               nvram_check_sum;
   EEPROM_ACTIVE_PAGE_T   op_return;

   Present_EEPROM_State = EEPROM_RESTORE;

   //LMB_ERROR_LOCK_BIT = 0;
   //EEPROM_Scan_For_Errors();

   nvram_start_addr = (uint32_t *)MIRROR_RAM_START_ADDR;
   mfg_data_start_addr = (uint32_t *)RAM_MFG_START_ADDR;

   op_return = Get_EEP_NVM_Active_Page();
   op_return = Get_EEP_NVRAM_Active_Page();
   pf_kksum = Get_KKSUM_checksum();

   if(( EEPROM_ACTIVE_PAGE_NOT_FOUND == op_return) || HAL_OS_Get_Battery_Remove() || HAL_uncleard_ram.data[NCRAM_REPROGRAM_FLAG])
   {
      EEP_NVRAM_Erase(EEP_NVRAM_BANK0);
      EEP_NVRAM_Erase(EEP_NVRAM_BANK1);
      Clear_Vehicle_NVRAM_In_Mirror();
      EEPROM_Write_Block((uint32_t*)nvram_start_addr,0,0);
      if(1 == EEP_NVM_full_flg)
      {
         No_active_page_flg = 1;
      }
      EEP_NVM_Fault = true;
   }
   else if(op_return == EEPROM_ACTIVE_PAGE_FOUND)
   {
      page = EEP_NVRAM_active_page;
      df_kksum = Get_KKSUM_EEP_NVRAM(page);
      if(pf_kksum != df_kksum)  // restore MFG only
      {
         Clear_Vehicle_NVRAM_In_Mirror();
         EEPROM_Set_Mirror_RAM_Pattern((uint32_t*)nvram_start_addr, (uint16_t)VALID_PAGE_DATA);
         EEPROM_Set_Mirror_RAM_Sequence_No((uint32_t*)(((uint8_t*)nvram_start_addr) +2),High_sequence_No_EEP_NVRAM);
         src = EEPROM_Pages[page].Current;
         src = (uint32_t*)(((uint8_t *)src) + NVRAM_MFG_START_ADDR_OFFSET);
         context = Enter_Critical_Section();
         for( ram_index = 0; ram_index < (MFG_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
         {
            *mfg_data_start_addr++ = *src++;
         }
         Leave_Critical_Section( context );
         EEPROM_Set_Mirror_RAM_KKSUM_Checksum((uint32_t*) nvram_start_addr,pf_kksum);
        EEP_NVM_Fault = true;
      }
      else if((1 == status_poweron.bits.Power_On_Reset) && (pf_kksum == df_kksum))
      {
         EEPROM_Set_Mirror_RAM_KKSUM_Checksum( (uint32_t*) nvram_start_addr,0);
         page = EEP_NVRAM_active_page;
         src = EEPROM_Pages[page].Current;
         for( ram_index = 0; ram_index < NVRAM_PAGE_SIZE/sizeof(uint32_t); ram_index++ )
         {
            *nvram_start_addr++ = *src++;
         }
	  EEP_NVM_Fault = false;

      }
      else if((pf_kksum == df_kksum)&&(0 == status_poweron.bits.Power_On_Reset))
      {
         nvram_check_pattern = EEPROM_Get_Mirror_RAM_check_pattern(nvram_start_addr);
         nvram_check_sum = EEPROM_Get_Mirror_RAM_NV_KKSUM(nvram_start_addr);
         if((nvram_check_pattern != VALID_PAGE_DATA)||(nvram_check_sum!=df_kksum))
         {
            EEPROM_Set_Mirror_RAM_KKSUM_Checksum( (uint32_t*) nvram_start_addr,0);
            page = EEP_NVRAM_active_page;
            src = EEPROM_Pages[page].Current;
//            src = ((uint8_t *)src);
            for( ram_index = 0; ram_index < NVRAM_PAGE_SIZE/sizeof(uint32_t); ram_index++ )
            {
               *nvram_start_addr++ = *src++;
            }

         }
         else
         {
         }
          EEP_NVM_Fault = false;	 
      }

   }

}

/*******************************************************************************
 *
 * Function:    EEPROM_Clear_Vehicle_NVRAM_Block
 *
 * Description: This function is to clear nvram
 * Parameters:  none
 * Return:      none
 *
 *******************************************************************************/
void EEPROM_Clear_Vehicle_NVRAM_Block(void)
{
   uint32_t *             nvram_start_addr;
   uint16_t               pf_kksum;
   EEPROM_ACTIVE_PAGE_T   op_return;

   nvram_start_addr = (uint32_t *)MIRROR_RAM_START_ADDR;
   op_return = Get_EEP_NVM_Active_Page();
   op_return = Get_EEP_NVRAM_Active_Page();
   pf_kksum = Get_KKSUM_checksum();

   EEP_NVRAM_Erase(EEP_NVRAM_BANK0);
   EEP_NVRAM_Erase(EEP_NVRAM_BANK1);
   Clear_Vehicle_NVRAM_In_Mirror();
   EEPROM_Write_Block((uint32_t*)nvram_start_addr,0,0);
   if(1 == EEP_NVM_full_flg)
   {
      No_active_page_flg = 1;
   }
   EEP_NVM_Fault = true;
}

/*******************************************************************************
 *
 * Function:    EEPROM_Backup_MFG_NVM_Block
 *
 * Description: This function performs the MFG NVM backup operation when the ECM
 *              does housekeeping when powering down
 *              (1) It compares the MFG NVM content in the mirror memory with
 *                  active MFG region in PFlash if number of writes to PFlash
 *                  has not exceeded 62 else the MFG backup is taken care of
 *                  in the EEPROM_Backup_Vehicle_NVRAM_Block.
 *
 *              (2) If there is no change in data the backup operation is aborted.
 *
 * Parameters:  none
 * Return:      none
 *
 *******************************************************************************/
void EEPROM_Backup_MFG_NVM_Block(bool erase_enable)
{
   uint16_t*              mfg_nvm_addr;
   uint8_t                blank_page;
   EEPROM_ACTIVE_PAGE_T   op_return;

   op_return = Get_EEP_NVM_Active_Page();


   /* FIXME: for DEVELOPMENT purpose ONLY, allow to write FIRST MFG first page only when special Conditions
    * are met.  Must remove this condition check in production release
    */
   if(( EEPROM_ACTIVE_PAGE_NOT_FOUND == op_return ) && (erase_enable == true))
   {

      EEPROM_Erase_NVM_BLOCK();
      //write to page 0
      High_sequence_No_EEP_NVM =0;
      EEPROM_Write_Mfg_Block((uint32_t *) RAM_MFG_DATA_START_ADDR, 0);

   }
   /* write only if EEP NVM is not full */
   else if(( EEPROM_ACTIVE_PAGE_FOUND == op_return )&& (0 == EEP_NVM_full_flg))
   {
      /* backup only if mirror area content have changed */
      if(!EEPROM_NVM_Compare_Data((uint8_t*)(Get_EEP_NVM_MFG_ADDRESS(High_sequence_No_EEP_NVM-1)) + 4,(uint8_t*)RAM_MFG_DATA_START_ADDR,(MFG_PAGE_SIZE - 4)))
      {
         for(blank_page  = High_sequence_No_EEP_NVM; blank_page < EEP_NVM_MFG_SEQUENCE_NO_MAX; blank_page++)
         {
            mfg_nvm_addr = (uint16_t *)Get_EEP_NVM_MFG_ADDRESS(blank_page);
            /* blank page check */
            if (Mem_BlankTest(mfg_nvm_addr, MFG_PAGE_SIZE/2) == true)
            {
               /* backup to an empty page */
               EEPROM_Write_Mfg_Block((uint32_t *)RAM_MFG_DATA_START_ADDR, blank_page);
               break;
            }
         }
      }
      else
      {
      }
   }
}

/*******************************************************************************
 *
 * Function:    EEPROM_Restore_MFG_NVM_Block
 *
 * Description: This MFG NVM data restore operation takes place only if the
 *              PFlash has not been written for more than 61 times.
 *              (1)Here it copies the MFG data stored in active PFlash region
 *                 back to the mirror memory (RAM).
 *
 * Parameters:  none
 * Return:      EEPROM_Operation_Status_T
 *
 *******************************************************************************/
EEPROM_Operation_Status_T EEPROM_Restore_MFG_NVM_Block(void)
{
   uint16_t                   page;
   uint16_t                   ram_index;
   uint32_t                   *nvm_data_start_addr;
   uint32_t                   *src;
   interrupt_state_t          context;
   EEPROM_ACTIVE_PAGE_T       pass_fail;
   EEPROM_Operation_Status_T return_Value = EEPROM_READ_SUCCESS;

   nvm_data_start_addr =(uint32_t *)RAM_MFG_START_ADDR; // get NVM MFG mirror ram area addr
   pass_fail = Get_EEP_NVM_Active_Page(); // Get active page from EEP NVM
   if(( EEPROM_ACTIVE_PAGE_FOUND == pass_fail)&&(0 == EEP_NVM_full_flg))
   {
      page = High_sequence_No_EEP_NVM -1 ;
      src = (uint32_t*)((uint32_t)(EEP_NVM_MFG_START_ADDR + page*MFG_PAGE_SIZE));
      context = Enter_Critical_Section();
      for( ram_index = 0; ram_index < (MFG_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
      {
         *nvm_data_start_addr++ = *src++;
      }
      Leave_Critical_Section( context );
      return_Value= EEPROM_READ_SUCCESS;
   }
   else if (( EEPROM_ACTIVE_PAGE_FOUND == pass_fail) && (1 == No_active_page_flg))
   {
      page = High_sequence_No_EEP_NVM - 1;
      src = (uint32_t*)((uint32_t)(EEP_NVM_MFG_START_ADDR + page*MFG_PAGE_SIZE));
      context = Enter_Critical_Section();
      for( ram_index = 0; ram_index < (MFG_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
      {
         *nvm_data_start_addr++ = *src++;
      }
      Leave_Critical_Section( context );
      return_Value= EEPROM_READ_SUCCESS;

   }
   else if( EEPROM_ACTIVE_PAGE_NOT_FOUND == pass_fail)
   {
      context = Enter_Critical_Section();
      for( ram_index = 0; ram_index < (MFG_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
      {
         *nvm_data_start_addr++ = 0x0;
      }
      Leave_Critical_Section( context );
      return_Value= EEPROM_READ_BAD_ADDRESS;
   }

   return(return_Value);
}
#if 0
/*******************************************************************************
 *
 * Function:    EEPROM_Restore_MFG_NVM_Block_Again
 *
 * Description: This MFG NVM data restore operation takes place only if the
 *              Application requested after it void the MFG data
 *              (1)Here it copies the most recent and valid MFG data stored in active PFlash or DFlash region
 *                 back to the mirror memory (RAM).
 *
 * Parameters:  none
 * Return:      EEPROM_Operation_Status_T
 *
 *******************************************************************************/
EEPROM_Operation_Status_T EEPROM_Restore_MFG_NVM_Block_Again(void)
{
   uint16_t        page;
   uint16_t        ram_index;
   uint32_t        *nvm_data_start_addr;
   uint32_t        *src;
   interrupt_state_t context;

   EEPROM_Operation_Status_T return_Value = EEPROM_READ_SUCCESS;

   EEPROM_ACTIVE_PAGE_T   op_return;

   op_return = Get_EEP_NVM_Active_Page();

   nvm_data_start_addr =(uint32_t *)RAM_MFG_START_ADDR; // get NVM MFG mirror ram area addr

   if (High_sequence_No_EEP_NVM <= EEP_NVM_MFG_SEQUENCE_NO_MAX)
   {
      if (0 == High_sequence_No_EEP_NVM)
      {
         return_Value = EEPROM_READ_BAD_ADDRESS;
      }
      else
      {
         page = High_sequence_No_EEP_NVM -1 ;
         src = (uint32_t*)((uint32_t)(RAM_MFG_START_ADDR + page*MFG_PAGE_SIZE));
         context = Enter_Critical_Section();
         for( ram_index = 0; ram_index < (MFG_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
         {
            *nvm_data_start_addr++ = *src++;
         }
         Leave_Critical_Section( context );
      }
   }
   else
   {
      src = EEPROM_Pages[EEP_NVRAM_active_page].Current;
      src = (uint32_t *)(((uint8_t *)src) + NVRAM_MFG_START_ADDR_OFFSET);
      context = Enter_Critical_Section();
      for( ram_index = 0; ram_index < (MFG_PAGE_SIZE/sizeof(uint32_t)); ram_index++ )
      {
         *nvm_data_start_addr++ = *src++;
      }
      Leave_Critical_Section( context );
   }

   return(return_Value);
}
#endif
/*=============================================================================
 * EEPROM_Fix_ECC_Error
 * @func Check the address where the double bit error occurred then erase its
 *     corresponding bank.
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void EEPROM_Fix_ECC_Error(uint32_t err_addr)
{
   uint8_t bank = INVALID_BANK;

   bank = EEPROM_Get_Current_Bank(err_addr);

   if (bank != INVALID_BANK)
   {

      EEP_NVRAM_Erase(bank);
   }
}

// FIXME - A... error correction code
#if 0
/*=============================================================================
 * EEPROM_Scan_For_Errors
 * @func Scan through both banks to trigger double bit error (DBE) trap if there's any.
 Read once every 64 bits (8bytes) to catch any DBE.
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void EEPROM_Scan_For_Errors(void)
{
   uint32_t page_loop;
   volatile uint32_t mem_dump;

   if(BANK_CORRUPTED_PATTERN != Backup_Disrupted.Bank0_Corrupted)
   {
      for (page_loop = EEPROM_SECTOR1_START_ADDR;
            page_loop < (EEPROM_SECTOR1_START_ADDR + TC17xx_FLASH_PROGRAM_SECTOR_SIZE);
            page_loop += (DFLASH_SCAN_MAX))
      {
         mem_dump = *(uint32_t *)page_loop;
         mem_dump = *(uint32_t *)(page_loop+DFLASH_SCAN_MIN);
         mem_dump = *(uint32_t *)(page_loop+DFLASH_SCAN_2X);
         mem_dump = *(uint32_t *)(page_loop+DFLASH_SCAN_3X);
      }
   }

   if(BANK_CORRUPTED_PATTERN != Backup_Disrupted.Bank1_Corrupted)
   {
      for (page_loop = EEPROM_SECTOR2_START_ADDR;
            page_loop < (EEPROM_SECTOR2_START_ADDR + TC17xx_FLASH_PROGRAM_SECTOR_SIZE);
            page_loop += (DFLASH_SCAN_MAX))
      {
         mem_dump = *(uint32_t *)page_loop;
         mem_dump = *(uint32_t *)(page_loop+DFLASH_SCAN_MIN);
         mem_dump = *(uint32_t *)(page_loop+DFLASH_SCAN_2X);
         mem_dump = *(uint32_t *)(page_loop+DFLASH_SCAN_3X);
      }
   }
}

/*=============================================================================
 * EEPROM_Fix_Dflash_Error
 * @func Check the address where the double bit error occurred then erase its
 *     corresponding bank.
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void EEPROM_Fix_Dflash_Error(void)
{
   uint8_t bank = INVALID_BANK;
   uint32_t err_addr = INVALID_ADDR;
   uint32_t *nvram_start_addr = (uint32_t *)START_NVRAM_ADDR;

   if (LMB_ERROR_LOCK_BIT == 1)
   {
      err_addr = LMB_ERROR_ADDRESS_REGISTER;
      bank = EEPROM_Get_Current_Bank(err_addr);

      if (bank != INVALID_BANK)
      {
         if( DFLASH_BANK0 == bank )
         {
            Backup_Disrupted.Bank0_Corrupted = BANK_CORRUPTED_PATTERN;
         }
         else if( DFLASH_BANK1 == bank )
         {
            Backup_Disrupted.Bank1_Corrupted = BANK_CORRUPTED_PATTERN;
         }
         if (Present_EEPROM_State == EEPROM_RESTORE)
         {
            EEPROM_Set_PF_DF_Checksum((uint32_t*) nvram_start_addr,0);
         }

         /* Calculate and store the NVM checksum */
         UpdateFILE_NVM_Checksum();
      }
      LMB_ERROR_LOCK_BIT = 0;
   }
}
#endif //if 0

// FIXME - A... temporary patch
#if 0
/////////////START OF TEMPORARY PATCH TO BE REMOVED//////////////////////////////
bool check_after_backup_done;
extern volatile TsFILE_EE_ManufactData NsFILE_NVM_EE_ManufactData;
#define CwFILE_EE_ManufactDataSize (sizeof(NsFILE_NVM_EE_ManufactData)/sizeof(WORD))
#define CwFILE_EE_ManufactDataSize_byte (sizeof(NsFILE_NVM_EE_ManufactData)/sizeof(BYTE))
/* THIS FUNCTION RETURNS 0xFFFF IF MFG DATA BLOCK CHECKSUM IS GOOD */
WORD SumHWIO_EE_ManufactBlock(void)
{
   WORD     LwFILE_EE_DataSum = 0;
   WORD     LwFILE_EE_Index;
   LONGWORD LgFILE_EE_IntStatusRegister;

   LgFILE_EE_IntStatusRegister = DisableHWIO_MasterIRQ();
   for(LwFILE_EE_Index = 0;
         LwFILE_EE_Index < CwFILE_EE_ManufactDataSize;
         LwFILE_EE_Index++)
   {
      LwFILE_EE_DataSum +=
         ((WORD *)&NsFILE_NVM_EE_ManufactData)[LwFILE_EE_Index];
   }
   RestoreHWIO_MasterIRQ(LgFILE_EE_IntStatusRegister);
   return (LwFILE_EE_DataSum);
}

/*=============================================================================
 * EEPROM_MFG_Data_Compare_And_Update_Debug_Data
 * @func  Compare the data in two addresses
 *
 * @parm EEPROM addresses,NVRAM Mfg addresses,size of data
 *
 * @rdesc return true or false
 *===========================================================================*/
bool EEPROM_MFG_Data_Compare_And_Update_Debug_Data(
      MFG_Data_Debug_T *debug_data,
      uint8_t * in_data1_ptr,
      uint8_t * in_data2_ptr,
      uint16_t  in_size )
{
   uint16_t index;

   bool data_valid = true;

   for(index = 0; index < in_size; index++)
   {
      if(*in_data1_ptr++ != *in_data2_ptr++)
      {
         data_valid = false;
         debug_data->offset = index;
         debug_data->expected_data = *(--in_data1_ptr);
         debug_data->actual_data = *(--in_data2_ptr);
         debug_data->sequence_num = High_sequence_No_PFLASH;
         break;
      }
   }
   return data_valid;
}

/*******************************************************************************
 *
 * Function:    EEPROM_MFG_NVM_Block_Check_Before_Backup
 *
 * Description: This function performs the MFG NVM check before backup operation
 *              (1) It compares the MFG NVM content in the mirror memory with
 *                  active MFG region in PFlash if number of writes to PFlash
 *                  has not exceeded 62 or in DFlash is exceed 62.
 *
 *              (2) It records debugging data if check fail.
 *
 *              (3) It restore good MFG data from Flash if check fail.
 *
 * Parameters:  none
 * Return:      none
 *
 *******************************************************************************/
void EEPROM_MFG_NVM_Block_Check_Before_Backup(void)
{
   bool check_result;
   EEPROM_Operation_Status_T op_return; // = EEPROM_READ_SUCCESS;
   EEPROM_ACTIVE_PAGE_T   page_op_return = EEPROM_ACTIVE_PAGE_NOT_FOUND;

   /* If MFG data has error, restore good data from Flash into RAM. Record debugging data. */
   if (SumHWIO_EE_ManufactBlock() != 0xFFFF)
   {
      page_op_return = Get_Pflash_Active_Page();
      page_op_return = Get_Dflash_Active_Page();

      /* Pflash is not full */
      if (0 == Pflash_full_flg)
      {
         /* Log 2 set of debug data only */
         if (MFG_Data_Before_Backup_Debug_Counter < NUMBER_OF_DEBUG_DATA_SET)
         {
            check_result = EEPROM_MFG_Data_Compare_And_Update_Debug_Data(
                  &MFG_Data_Before_Backup[MFG_Data_Before_Backup_Debug_Counter],
                  (uint8_t*)(Get_MFG_NVM_ADDRESS(High_sequence_No_PFLASH-1)) + 6,
                  (uint8_t*)(&NsFILE_NVM_EE_ManufactData),
                  (CwFILE_EE_ManufactDataSize_byte));
         }
      }
      else
      {
         /* Log 2 set of debug data only */
         if (MFG_Data_Before_Backup_Debug_Counter < NUMBER_OF_DEBUG_DATA_SET)
         {
            check_result = EEPROM_MFG_Data_Compare_And_Update_Debug_Data(
                  &MFG_Data_Before_Backup[MFG_Data_Before_Backup_Debug_Counter],
                  (uint8_t*)((uint8_t*)EEPROM_Pages[Dflash_active_page].Current + 12),
                  (uint8_t*)(&NsFILE_NVM_EE_ManufactData),
                  (CwFILE_EE_ManufactDataSize_byte));
         }
      }

      if  (MFG_Data_Before_Backup_Debug_Counter < 0xff) MFG_Data_Before_Backup_Debug_Counter++;
      op_return = EEPROM_Restore_MFG_NVM_Block_Again();
   }

   check_after_backup_done = false;
}


/*******************************************************************************
 *
 * Function:    EEPROM_MFG_NVM_Block_Check_After_Backup
 *
 * Description: This function performs the MFG NVM check after backup operation
 *              (1) It compares the MFG NVM content in the mirror memory with
 *                  active MFG region in PFlash if number of writes to PFlash
 *                  has not exceeded 62 or in DFlash is exceed 62.
 *
 *              (2) It will record debugging data if check fail.
 *
 *              (3) It backup MFG data to Flash again if check fail.
 *
 * Parameters:  none
 * Return:      none
 *
 *******************************************************************************/
bool EEPROM_MFG_NVM_Block_Check_After_Backup(void)
{
   bool check_result = true;
   EEPROM_ACTIVE_PAGE_T   op_return = EEPROM_ACTIVE_PAGE_NOT_FOUND;

   op_return = Get_Pflash_Active_Page();
   op_return = Get_Dflash_Active_Page();

   if (false == check_after_backup_done)
   {
      /* Pflash is not full */
      if (0 == Pflash_full_flg)
      {
         /* If MFG data has error, record debugging data. */
         /* Log 2 set of debug data only */
         if (MFG_Data_After_Backup_Debug_Counter < NUMBER_OF_DEBUG_DATA_SET)
         {
            check_result = EEPROM_MFG_Data_Compare_And_Update_Debug_Data(
                  &MFG_Data_After_Backup[MFG_Data_After_Backup_Debug_Counter],
                  (uint8_t*)(&NsFILE_NVM_EE_ManufactData),
                  (uint8_t*)(Get_MFG_NVM_ADDRESS(High_sequence_No_PFLASH-1)) + 6,
                  (CwFILE_EE_ManufactDataSize_byte));
         }
         else
         {
            check_result = EEPROM_NVM_Compare_Data(
                  (uint8_t*)(&NsFILE_NVM_EE_ManufactData),
                  (uint8_t*)(Get_MFG_NVM_ADDRESS(High_sequence_No_PFLASH-1)) + 6,
                  (CwFILE_EE_ManufactDataSize_byte));
         }

         check_after_backup_done = true;
      }

      /* Pflash is full */
      else
      {
         /* If MFG data has error, record debugging data. */
         /* Log 2 set of debug data only */
         if (MFG_Data_After_Backup_Debug_Counter < NUMBER_OF_DEBUG_DATA_SET)
         {
            check_result = EEPROM_MFG_Data_Compare_And_Update_Debug_Data(
                  &MFG_Data_After_Backup[MFG_Data_After_Backup_Debug_Counter],
                  (uint8_t*)(&NsFILE_NVM_EE_ManufactData),
                  (uint8_t*)((uint8_t*)EEPROM_Pages[Dflash_active_page].Current + 12),
                  (CwFILE_EE_ManufactDataSize_byte));
         }
         else
         {
            check_result = EEPROM_NVM_Compare_Data(
                  (uint8_t*)(&NsFILE_NVM_EE_ManufactData),
                  (uint8_t*)((uint8_t*)EEPROM_Pages[Dflash_active_page].Current + 12),
                  (CwFILE_EE_ManufactDataSize_byte));
         }
      }

      if (false == check_result)
      {
         /* If MFG data has error, restore good data from Flash into RAM. Record debugging data. */
         if (SumHWIO_EE_ManufactBlock() != 0xFFFF)
         {
            High_sequence_No_PFLASH--;
            op_return = EEPROM_Restore_MFG_NVM_Block_Again();
         }

         if (MFG_Data_After_Backup_Debug_Counter < 0xff) MFG_Data_After_Backup_Debug_Counter++;
         check_after_backup_done = false;
      }
   }
   else
   {
      // do nothing
   }

   return (check_result);
}

/*******************************************************************************
 *
 * Function:    EEPROM_Initialize_Internal_NVM_Variables
 *
 * Description: This function is to set the NVM variables
 *
 * Parameters:  EEPROM_Init_T
 * Return:      none
 *
 *******************************************************************************/
void EEPROM_Initialize_Internal_NVM_Variables(EEPROM_Init_T in_init_type)
{
   switch(in_init_type )
   {
      case EEPROM_INIT_POWER_ON:
         Backup_Disrupted.Bank0_Corrupted = BANK_NOT_CORRUPTED_PATTERN;
         Backup_Disrupted.Bank1_Corrupted = BANK_NOT_CORRUPTED_PATTERN;
         break;

      case EEPROM_INIT_BEFORE_RESTORE:
         Backup_Disrupted_temp.Bank0_Corrupted= Backup_Disrupted.Bank0_Corrupted;
         Backup_Disrupted_temp.Bank1_Corrupted= Backup_Disrupted.Bank1_Corrupted;
         break;

      case EEPROM_INIT_AFTER_RESTORE:
         Backup_Disrupted.Bank0_Corrupted= Backup_Disrupted_temp.Bank0_Corrupted;
         Backup_Disrupted.Bank1_Corrupted= Backup_Disrupted_temp.Bank1_Corrupted;
         break;

      default:
         break;
   }
}
/////////////END OF TEMPORARY PATCH TO BE REMOVED//////////////////////////////
#endif // if 0
