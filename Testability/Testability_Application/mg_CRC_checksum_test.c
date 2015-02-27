//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mg_CRC_checksum_test.c %
//
// created_by:       tzwfxv %
//
// date_created:	Fri Jul 13 14:02:00 2012 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:            %
//
// %version:         4 %
//
//=============================================================================
#if 0

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_config.h"
#include "mg_hal.h"

/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/

#define  CRC32                   ((uint32_t)0xedb88320)

/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/

void mg_CRC_checksum_test(void);


/*****************************************************************************
 * Function Prototype: void Mg_CRC_checksum_test(void)
 *
 * Description: This function is to calculate the CRC check sum of the page
 *              specified in the mail box
 *            
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void mg_CRC_checksum_test(void)
{
  uint32_t             calculatedCRC;
  uint8_t              idx;
  uint8_t  *flash_add_ptr ;
  uint32_t             nBytes;
  /* Address defination follow the TSR */
  uint32_t             globalAddrStart;
  uint32_t             globalAddrEnd;
  uint8_t              msb_mem_start;
  uint8_t              middle_mem_start;
  uint8_t              lsb_mem_start; 
  uint8_t              msb_mem_end;
  uint8_t              middle_mem_end;
  uint8_t              lsb_mem_end; 

  /* Send out the Test Id as first byte */
  MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

  /* To get the start address from mailbox */ 
  msb_mem_start    = MG_MAILBOX_IN(parameter[0]);
  middle_mem_start = MG_MAILBOX_IN(parameter[1]);
  lsb_mem_start    = MG_MAILBOX_IN(parameter[2]);

  /* To get the end address from the mail box */
  msb_mem_end      = MG_MAILBOX_IN(parameter[3]);
  middle_mem_end   = MG_MAILBOX_IN(parameter[4]);
  lsb_mem_end      = MG_MAILBOX_IN(parameter[5]);
 
  /* To get the start address from the 3 bytes received from the mail box */ 
  globalAddrStart = msb_mem_start;
  globalAddrStart =((globalAddrStart << 8) | middle_mem_start );
  globalAddrStart =((globalAddrStart << 8) | lsb_mem_start );

  /* To get the end address from the 3 bytes received from the mail box */ 
  globalAddrEnd = msb_mem_end;
  globalAddrEnd =((globalAddrEnd << 8) | middle_mem_end );
  globalAddrEnd =((globalAddrEnd << 8) | lsb_mem_end ); 

  if (((uint32_t)MEM_ADDR_START_PTR <= globalAddrStart) && ((uint32_t)MEM_ADDR_END_PTR >= globalAddrEnd))
  {
	  nBytes = (uint32_t)(globalAddrEnd - globalAddrStart + 1);
	  
	  flash_add_ptr = (uint8_t *)globalAddrStart;
	  /* To calculate the CRC check sum for the data present in the given page */ 	
	  calculatedCRC = 0xFFFFFFFF;
	  while (nBytes > 0)
	    {
	    calculatedCRC ^= (uint8_t)(*flash_add_ptr++);
	    for (idx = 0; idx < 8; idx++)
	      {
	      calculatedCRC = (calculatedCRC & 0x00000001) ?
	      ((calculatedCRC >> 1) ^ CRC32) : (calculatedCRC >> 1);
	      }
	    nBytes = nBytes - 1;
		mg_HAL_Service_WatchDog();
	    } 

	    /* To send the CRC check sum to the out box */
	MG_MAILBOX_OUT(parameter[1]) = (uint8_t)((calculatedCRC & 0xFF00) >> 8);
	MG_MAILBOX_OUT(parameter[2]) = (uint8_t)(calculatedCRC & 0x00FF);
  }
}
#endif