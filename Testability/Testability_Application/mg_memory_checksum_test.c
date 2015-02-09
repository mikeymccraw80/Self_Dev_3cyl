/**********************************************************************
*
*	C %name:		mg_memory_checksum_test.c %
*	Instance:		ctc_pt3_1
*	Description:	
*	%created_by:	tzwfxv %
*	%date_created:	Thu May  2 16:26:18 2013 %
*
**********************************************************************/


#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_config.h"
#include "mg_hal.h"
/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/

void mg_memory_checksum_test(void);


/*****************************************************************************
 * Function Prototype: void memory_checksum_test(void)
 *
 * Description: This function is to calculate the memory check sum of all the 
 *              pages from 0 to 32.check sum is calculated as the sum of single 
 *              bytes from the start address of page 1 of FLASH to the end 
 *              address of page 32 of FLASHand the resultant checksum is 2 bytes 
 *            
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void mg_memory_checksum_test(void)
{
    uint16_t idx;
    uint8_t * flash_add_ptr =(uint8_t *)FLASH_START_ADDRESS;
    uint16_t mem_checksum = 0;
    uint8_t temp;
    uint8_t count;

    /* Send out the Test Id as first byte */
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
	
    /* To calculate the check sum for the memory range 0x00000000 to 0x0017FFFF */
    /* taking 1 byte at a time and this to the checksum                 */	
    while(flash_add_ptr <= ((uint8_t *)FLASH_END_ADDRESS))
    {
        temp = *flash_add_ptr;
        mem_checksum = (uint16_t)(temp + mem_checksum);
        flash_add_ptr++;
        mg_HAL_Service_WatchDog();
    }
    /* To add the last byte to the check sum */
    temp = *flash_add_ptr;
    mem_checksum = (uint16_t)(temp + mem_checksum);
    /* To send the calculated check sum in to the outbox */
    MG_MAILBOX_OUT(parameter[1]) = (uint8_t)((mem_checksum & 0xFF00) >> 8);
    MG_MAILBOX_OUT(parameter[2]) = (uint8_t)(mem_checksum & 0x00FF);

}

