//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_EEEP_PML_write_test.c %
//
// created_by:       tzwfxv %
//
// %date_created:	Thu May  2 16:16:05 2013 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:           %
//
// %version:         3 %
//
//=============================================================================


#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_config.h"
#include "mg_hal.h"
#include "mg_hal_flash.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define SIZE_OF_RESERVED    0x580       // this is defined by li chunyao
/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/



/*****************************************************************************
 * Function Prototype: void mg_EEEP_PML_write_test(void)
 *
 * Description: This function is to write PML partion to EEEP
 *              specified in the mail box
 *            
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void mg_EEEP_PML_write_test(void)
{
    interrupt_state_t      context;
    uint32_t memory_add_ptr;
    uint8_t number_of_write_byte;
    uint8_t PML_in_ram[SIZE_OF_RESERVED];
    uint16_t idx;
    /* Send out the Test Id as first byte */
    number_of_write_byte = MG_MAILBOX_IN(parameter[0]);
    memory_add_ptr = MG_MAILBOX_IN(parameter[1]);
    memory_add_ptr = ((memory_add_ptr << 8) | MG_MAILBOX_IN(parameter[2]));
    memory_add_ptr = ((memory_add_ptr << 8) | MG_MAILBOX_IN(parameter[3]));
    if (memory_add_ptr < 0x100)
    {
        for (idx = 0; idx < SIZE_OF_RESERVED; idx++)
        {
            if ((idx >= memory_add_ptr - BASS_ADDRESS) && (idx < (memory_add_ptr + number_of_write_byte - BASS_ADDRESS)))
            {
                PML_in_ram[idx] = MG_MAILBOX_IN(parameter[4 + idx - memory_add_ptr]);
            }
            else
            {
                PML_in_ram[idx] = *(uint8_t*)(BASS_ADDRESS + idx);
            }
            mg_HAL_Service_WatchDog();
        }
        context = Enter_Critical_Section();
        if (mg_HAL_Flash_Set_Lock(memory_add_ptr, false))
        {
            if (mg_HAL_Flash_Erase_Flash(memory_add_ptr, mg_HAL_Service_WatchDog))
            {
                if (mg_HAL_FLash_Program_Flash(SIZE_OF_RESERVED, (uint32_t)PML_in_ram, (uint32_t)START_ADDRESS_OF_PML, mg_HAL_Service_WatchDog))
                {
                    MG_MAILBOX_OUT(parameter[1]) = 0x00;
                }
                else
                {
                    MG_MAILBOX_OUT(parameter[1]) = 0xFF;
                }
            }
            mg_HAL_Flash_Set_Lock(memory_add_ptr, true);
        }
        Leave_Critical_Section( context );
    }
    MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);
}
