#ifndef HAL_EMULATED_EEPROM_H
#define HAL_EMULATED_EEPROM_H
//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            hal_emulated_eeprom.h %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      rz65p6 %
//
// %date_modified:      %
//
// %version:         2 %
//
//=============================================================================

#include "reuse.h"
//#include "cpu.h"
//#include "fileftyp.h"
//#include "hal.h"
#include "dd_flash_interface.h"// for hw reset status

/*===========================================================================*\
 *  Data Structure Definitions
\*===========================================================================*/

typedef enum
{
   EEPROM_NVRAM,
   EEPROM_HISTORICAL,
   EEPROM_MANUFACTURING

} EEPROM_Region_T;

typedef enum
{
   EEPROM_READ_SUCCESS,
   EEPROM_READ_BAD_ADDRESS,
   EEPROM_READ_BAD_CHECKSUM

}  EEPROM_Operation_Status_T;

typedef enum
{
   EEPROM_SUCCESS_READ,
   EEPROM_INVALID_DST_ADDR,
   EEPROM_CHKSM_ERROR

}  EEPROM_Read_Status;

typedef enum
{
   EEP_NVRAM_BANK0,
   EEP_NVRAM_BANK1

} EEP_NVRAM_BANK_T;

typedef enum
{
   EEPROM_NULL,
   EEPROM_RESTORE,
   EEPROM_BACKUP

} EEPROM_State_T;

typedef enum
{
   EEPROM_READ,
   EEPROM_WRITE

} EEPROM_OPERATION_T;

 typedef enum
 {
   EEPROM_ACTIVE_PAGE_NOT_FOUND,
   EEPROM_ACTIVE_PAGE_FOUND,
   EEPROM_ACTIVE_PAGE_PARTIALLY

 } EEPROM_ACTIVE_PAGE_T;

typedef enum
{
   EEPROM_INIT_POWER_ON,
   EEPROM_INIT_BEFORE_RESTORE,
   EEPROM_INIT_AFTER_RESTORE

} EEPROM_Init_T;

typedef struct EEPROM_SeqNum_Tag
{
   uint8_t page;
   uint32_t seqno;

} EEPROM_SeqNum_T;

typedef struct EEPROM_Page_Tag
{
   uint32_t *Current;
   uint32_t *Next;
   bool      erase_bank;
   uint32_t  bank_select;

} EEPROM_Page_T;


/*===========================================================================*\
 *  Macro Definitions
\*===========================================================================*/

extern bool        EEP_NVM_full_flg;
extern bool                      EEP_NVM_Fault;
#define Get_EEP_NVM_Fault()  (EEP_NVM_Fault)

/*=============================================================================
 * EEPROM_Get_Current_Bank
 * @func Check if address passed is on bank 0 or 1
 * @parm  addr
 * @rdesc  bank
 *===========================================================================*/
uint8_t EEPROM_Get_Current_Bank(uint32_t addr);

/*=============================================================================
 * EEPROM_Backup_Vehicle_NVRAM_Block
 * @func Vehicle NVRAM data is storing to EEP NVRAM after find out the blank page
 * of banks of dflash.
 * @parm none
 * @rdesc none
 *===========================================================================*/
void EEPROM_Backup_Vehicle_NVRAM_Block(void);

/*=============================================================================
 * EEPROM_Restore_Vehicle_NVRAM_Block
 * @func Restore vehicle NVRAM data.
 * @parm  none
 * @rdesc  none
 *===========================================================================*/
void EEPROM_Restore_Vehicle_NVRAM_Block(HWIO_Reset_Status_T status_poweron);

/*=============================================================================
 * MFG_NVM_Backup_Operation
 * @func Write  MFG data in the blank page of the Pflash.
 * @parm  Mfg addresses,page number
 * @rdesc  none
 *===========================================================================*/
void EEPROM_Backup_MFG_NVM_Block(bool erase_enable);

/*=============================================================================
 * EEPROM_Restore_MFG_NVM_Block
 * @func Restore  MFG data from Pflash if sequence number is less than or equal
 * to 62.
 * @parm   addresses
 * @rdesc  none
 *===========================================================================*/
EEPROM_Operation_Status_T EEPROM_Restore_MFG_NVM_Block(void);

/*=============================================================================
 * EEPROM_Restore_MFG_NVM_Block_Again
 * @func Restore  MFG data
 * @parm   addresses
 * @rdesc  none
 *===========================================================================*/
 EEPROM_Operation_Status_T EEPROM_Restore_MFG_NVM_Block_Again(void);


#endif /* HAL_EMULATED_EEPROM_H */

