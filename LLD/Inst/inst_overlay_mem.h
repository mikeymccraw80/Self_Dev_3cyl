#ifndef INST_OVERLAY_MEM_H
#define INST_OVERLAY_MEM_H

#include "reuse.h"
#include "dd_siu_interface.h"



/*=============================================================================
 * Get_Working_Page_RAM_Validation
 * @func  Determine if RAM mirror of working page is valid
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
bool Get_Working_Page_RAM_Validation(void);

/*=============================================================================
 * INST_Backup_Working_Page
 * @func  Backup working page from mirror RAM to FLASH
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
void INST_Backup_Working_Page(void);

/*=============================================================================
 * INST_Fix_Backup_Page_ECC_Error
 * @func  Clear Backup page for the ECC Error
 *
 * @parm
 *
 * @rdesc 
 *===========================================================================*/
void INST_Fix_Backup_Page_ECC_Error(uint32_t err_addr);

/*=============================================================================
 * INST_Restore_Working_Page
 * @func  restore mirror ram of working page from FLASH
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
void INST_Restore_Working_Page(HWIO_Reset_Status_T status_poweron);

/*=============================================================================
 * INST_Restore_Working_Page_Again
 * @func  restore mirror ram of working page from reference
 *
 * @parm
 *
 * @rdesc return true or false
 *===========================================================================*/
void INST_Restore_Working_Page_Again(void);





#endif

