/**********************************************************************
*
*	C %name:		mg_KKsum_checksum_test.c %
*	Instance:		ctc_pt3_1
*	Description:	
*	%created_by:	tzwfxv %
*	%date_created:	Thu May  2 16:18:14 2013 %
*
**********************************************************************/

/******************************************************************************/

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

void mg_KKsum_checksum_test(void);


/*****************************************************************************
 * Function Prototype: void KKsum_checksum_test(void)
 *
 * Description:  This function performs Flash memory checksum calculation and 
 *               compares this against KKSUM.The Calculated checksum need to be
 *               verified against the value from address indicated in MPI         			   
 *              
 *              
 *            
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void mg_KKsum_checksum_test(void)
{
  uint16_t * flash_add_ptr = (uint16_t *)KKSUM_START_ADDRESS;
  uint16_t no_of_bytes;
  uint16_t checksum = 0;
  uint16_t KK_sum;
  uint16_t temp;
  uint8_t count;

  /* Send out the Test Id as first byte */
  MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

  /* To calculate the check sum for the memory range 740000 to 7fffff */
  /* taking 2 bytes at a time and store this result                   */	
  while(flash_add_ptr <=((uint16_t *)KKSUM_END_ADDRESS))
  {
    temp = *flash_add_ptr ;
    checksum = (temp+ checksum);
    flash_add_ptr++;
    mg_HAL_Service_WatchDog();
  }
  /* To add the last byte to the check sum */
  temp = *flash_add_ptr ;
  checksum = (temp+ checksum);

  /* To subtract the data present in the address range 16_0000 to 16_0003 */
  flash_add_ptr = (uint16_t *)KKSUM_ADDRESS;
  KK_sum = *flash_add_ptr;
  checksum = (checksum - KK_sum);
   
  /* To check whether the check sum matches with the KKcheck sum */
  if(KK_sum == checksum)
    {
    /* check sum matches with the kksum */
    MG_MAILBOX_OUT(parameter[1]) = 0x00; 
    }
  else
    {
    /* check sum doesn't matches with the KKsum */ 
    MG_MAILBOX_OUT(parameter[1]) = 0xFF; 
    }
  /* V Hari Mar 30, 2009 - Store the KKSum result into Outbox */
  MG_MAILBOX_OUT(parameter[2]) = (uint8_t)((KK_sum & 0xFF00) >> 8) ;
  MG_MAILBOX_OUT(parameter[3]) = (uint8_t)(KK_sum & 0x00FF);
  
   
}
