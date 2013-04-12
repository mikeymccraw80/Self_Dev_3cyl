#ifndef IO_CONFIG_EEPROM_H
#define IO_CONFIG_EEPROM_H

/*=============================================================================
 * Macro Definitions
 *===========================================================================*/
// NVRAM macros
#define NVRAM_PAGE_SIZE                         ((8) * 1024)    //8K page size
#define EEP_NVRAM_PER_BANK_PAGES                (2)
#define EEP_NVRAM_MAX_PAGE                      (4)
// MFG macros
#define MFG_PAGE_SIZE                           (256)           //256 bytes page size
#define MFG_PATTERN_ADDR_OFFSET                 (0)             //offset from MFG_*** start address
#define MFG_SEQNO_ADDR_OFFSET                   (2)             //offset from MFG_*** start address
#define MFG_CHKSUM_ADDR_OFFSET                  (254)           //offset from MFG_*** start address
#define MFG_CHKSUM_OFFSET_SIZE                  (MFG_PAGE_SIZE - MFG_CHKSUM_ADDR_OFFSET)
#define EEP_NVM_MFG_SEQUENCE_NO_MAX             (62)            // max sequence no. in NVM

#define NVRAM_MFG_START_ADDR_OFFSET             (8)             // MFG start address offset from NVRAM start address

//NVRAM Flash Related Constants


#define EEP_NVRAM_BANK0_START_ADDR              (0x00018000)   // block 2b
#define EEP_NVRAM_BANK1_START_ADDR              (0x0001C000)   // block 3

#define EEP_NVM_START_ADDR                      (0x00000000)   // block 1a
#define EEP_NVM_MFG_START_ADDR                  (0x00000200)   // block 1a start address + PML offset
#define EEP_NVM_MFG_END_ADDR                    (0x00003FFF)   // block 1a end address

#define Get_EEP_NVM_MFG_ADDRESS(page)           (EEP_NVM_MFG_START_ADDR + ((page) * MFG_PAGE_SIZE))

/*=============================================================================
 * EEPROM Page Constants
*==============================================================================*/
#define PF_KKSUM_ADDRESS                        (0x0017FFF8)   

/*=============================================================================
 * NVRAM Mirror RAM area
*==============================================================================*/
#define MIRROR_RAM_START_ADDR                   (0x40000000)

#define RAM_MFG_START_ADDR                      (0x40000008)
#define RAM_MFG_DATA_START_ADDR                 (0x4000000C)

#define BANK_CORRUPTED_PATTERN                  (0x2222) /* pattern to indicate that Bank (0 or 1) of NVRAM pflash block is corrupted */
#define BANK_NOT_CORRUPTED_PATTERN              (0x4444) /* pattern to indicate that Bank (0 or 1) of NVRAM pflash block is NOT corrupted*/

#endif

