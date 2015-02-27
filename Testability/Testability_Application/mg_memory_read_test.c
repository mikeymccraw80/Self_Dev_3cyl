/**********************************************************************
*
*	C %name:		mg_memory_read_test.c %
*	Instance:		ctc_pt3_1
*	Description:	
*	%created_by:	tzwfxv %
*	%date_created:	Thu May  2 16:26:36 2013 %
*
**********************************************************************/
#if 0

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_hal.h"
/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/



/*****************************************************************************
 * Function Prototype: void mg_memory_read_test(void)
 *
 * Description: This function is to read n no of bytes from the address 
 *                  specified in the outbox          
 *            
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void mg_memory_read_test(void)
{
    uint32_t memory_add_ptr;
    uint8_t number_of_read_byte;
    uint8_t idx;
    /* Send out the Test Id as first byte */
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
    number_of_read_byte = MG_MAILBOX_IN(parameter[0]);
    memory_add_ptr = MG_MAILBOX_IN(parameter[1]);
    memory_add_ptr = ((memory_add_ptr << 8) | MG_MAILBOX_IN(parameter[2]));
    memory_add_ptr = ((memory_add_ptr << 8) | MG_MAILBOX_IN(parameter[3]));
    memory_add_ptr = ((memory_add_ptr << 8) | MG_MAILBOX_IN(parameter[4]));

    for (idx = 0; idx < number_of_read_byte; idx++)
    {
        MG_MAILBOX_OUT(parameter[idx + 1]) = *(uint8_t*)(memory_add_ptr++);
        mg_HAL_Service_WatchDog();
    }
}
#endif