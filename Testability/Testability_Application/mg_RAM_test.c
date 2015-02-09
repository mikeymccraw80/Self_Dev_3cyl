
/**********************************************************************
*
*	C %name:		mg_RAM_test.c %
*	Instance:		ctc_pt3_1
*	Description:	
*	%created_by:	tzwfxv %
*	%date_created:	Thu May  2 16:28:16 2013 %
*
**********************************************************************/

#include "reuse.h"
#include "mg_mailbox.h"
#include "mg_config.h"
#include "mg_hal.h"
/*----------------------------------------------------------------------------*/
/*   Definition of local macros                                               */
/*----------------------------------------------------------------------------*/
#define COP_COUNT (0x50)
/*----------------------------------------------------------------------------*/
/*   Definition of function prototypes                                        */
/*----------------------------------------------------------------------------*/
typedef void (*fPtrRAMTest_T)(void);
uint8_t           failure_flag ;
uint8_t           out_of_range_flag;
fPtrRAMTest_T     byExecAddr;
uint16_t          execAddr;



void mg_RAM_test(void);
void low_to_high_bytes(uint8_t prev_data,uint8_t current_data,
                       uint32_t start_add,uint32_t end_add);
void high_to_low_bytes(uint8_t prev_data,uint8_t current_data,
                       uint32_t start_add,uint32_t end_add);
void low_to_high_words(uint16_t prev_data,uint16_t current_data,
                       uint32_t start_add,uint32_t end_add);
void high_to_low_words(uint16_t prev_data,uint16_t current_data,
                       uint32_t start_add,uint32_t end_add);




/*******************************************************************************
 * Function Prototype: void low_to_high_bytes(uint8_t prev_data,
                       uint8_t current_data,uint32_t start_add,uint32_t end_add)
 *
 * Description:  This routine verifies the previous data and writes the given 
 *               pattern byte by byte to the location after the verification 
 *               from low add to high add
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void low_to_high_bytes(uint8_t prev_data,uint8_t current_data,
                       uint32_t start_add,uint32_t end_add)
{
  uint8_t prv_dta    = prev_data;
  uint8_t crnt_dta   = current_data;
  uint32_t strt_adds = start_add;
  uint32_t end_adds  = end_add;

  uint8_t * ram_add_ptr = (uint8_t *)strt_adds;
  uint8_t temp;
  while((ram_add_ptr <= (uint8_t *)end_adds) && 
        (failure_flag != 0x01)
       )
    {
	/* Initial verification is not required for first time */
	/*i.e for the pattern 0xFF(first pattern) */ 
   	if(crnt_dta != 0xff)
   	  {
   	  /* To verify the previoous data before writing */
      temp = *ram_add_ptr ;
      if(temp != prv_dta)
        {
        /* setting the error flag if the verification fails */ 
        failure_flag = 0x01;
   	    }
   	  else
        {
   	    /* To write the current data */
        *ram_add_ptr = crnt_dta;
        }
   	  }
    else
      {
   	  /* To write the current data */
   	  *ram_add_ptr = crnt_dta;
      }	  
    temp = *ram_add_ptr ;
    /* To verify the written data before writing the next location */ 
    if(temp != crnt_dta)
      {
      /* setting the error flag if the verification fails */ 
      failure_flag = 0x01;
      }

    mg_HAL_Service_WatchDog();
    /* Incrementing the ram_add pointer to the next location */ 
    ram_add_ptr++;
       
    }// while(ram_add_ptr <= (@far @gpage uint8_t *)end_add )

}


/*******************************************************************************
 * Function Prototype: void high_to_low_bytes(uint8_t prev_data,
                       uint8_t current_data,uint32_t start_add,uint32_t end_add)
 *
 * Description:  This routine verifies the previous data and writes the given 
 *               pattern byte by byte to the location after the verification	 
 *               from high add to low add
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void high_to_low_bytes(uint8_t prev_data,uint8_t current_data,
                       uint32_t start_add,uint32_t end_add)
{
  uint8_t prv_dta	  = prev_data;
  uint8_t crnt_dta	  = current_data;
  uint32_t strt_adds  = start_add;
  uint32_t end_adds	  = end_add;

  uint8_t * ram_add_ptr = (uint8_t *)end_adds;
  uint8_t temp;
  while((ram_add_ptr >= (uint8_t *)strt_adds) && 
        (failure_flag != 0x01) 
       )
    {
	temp = *ram_add_ptr ;
    if(temp != prv_dta)
      {
      /* setting the error flag if the verification fails */ 
      failure_flag = 0x01;
      }
	else
      {
	  if(prv_dta != 0x00)
	    {
        *ram_add_ptr = crnt_dta;
		}
	  else
	    {
		  //do nothing
		}
      }
	/* After the last pattern no need to write,only verification is */
	/* required so skipping the writing part */
	if(prv_dta != 0x00)
	  { 
      temp = *ram_add_ptr ;
      /* To verify the written data before writing the next location */ 
      if(temp != crnt_dta)
        {
        /* setting the error flag if the verification fails */ 
        failure_flag = 0x01;
  	    }
      /* Decrementing the ram_add pointer to the next location */ 
      ram_add_ptr--;
      }
	else
	  {
      /* Decrementing the ram_add pointer to the next location */ 
      ram_add_ptr--;
      }
    mg_HAL_Service_WatchDog();

	}// (ram_add_ptr >= (@far @gpage uint8_t *)start_add )

}

/*******************************************************************************
 * Function Prototype:void low_to_high_words(uint16_t prev_data,
                      uint16_t current_data,uint32_t start_add,uint32_t end_add)
 *
 * Description:  This routine verifies the previous data and writes the given
 *               pattern word by word to the location after the verification 
 *               from low add to high add
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void low_to_high_words(uint16_t prev_data,uint16_t current_data,
                       uint32_t start_add,uint32_t end_add)
{
  uint16_t prv_dta   = prev_data;
  uint16_t crnt_dta	 = current_data;
  uint32_t strt_adds = start_add;
  uint32_t end_adds	 = end_add;
  uint16_t temp;

  uint16_t * ram_add_ptr = (uint16_t *)strt_adds;
  

  while((ram_add_ptr <= (uint16_t *)end_adds) && 
        (failure_flag != 0x01)
       )
    {
	/* Initial verification is not required for first time */ 
	/* Hari Jul 11, 2008 - Changed 0xff in to 0xFFFF */
	if(crnt_dta != 0xffff)	
	  {
      temp = *ram_add_ptr ;
      if(temp != prv_dta)
        {
        /* setting the error flag if the verification fails */ 
        failure_flag = 0x01;
        }
	  else
        {
        *ram_add_ptr = crnt_dta;
        }
	  }
    else
      {
	  *ram_add_ptr = crnt_dta;
      }
      	  
    temp = *ram_add_ptr ;
    
    /* To verify the written data before writing the next location */ 
    if(temp != crnt_dta)
      {
      /* setting the error flag if the verification fails */ 
      failure_flag = 0x01;
 	  }
    /* Incrementing the ram_add pointer to the next location */ 
    ram_add_ptr++;
    mg_HAL_Service_WatchDog();

    }// while(ram_add_ptr <= (@far @gpage uint16_t *)end_add )

}


/*******************************************************************************
 * Function Prototype:void high_to_low_words(uint16_t prev_data,
                      uint16_t current_data,uint32_t start_add,uint32_t end_add)
 *
 * Description:  This routine verifies the previous data and writes the given
 *               pattern word by word to the location after the verification	 
 *               from high add to low
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void high_to_low_words(uint16_t prev_data,uint16_t current_data,
                       uint32_t start_add,uint32_t end_add)
{
  uint16_t prv_dta   = prev_data;
  uint16_t crnt_dta	 = current_data;
  uint32_t strt_adds = start_add;
  uint32_t end_adds	 = end_add;

  //@far @gpage uint16_t * ram_add_ptr =  (@far @gpage uint16_t *)(end_adds - 1);
  uint16_t * ram_add_ptr =  (uint16_t *)end_adds;
  uint16_t temp;
  while((ram_add_ptr >= (uint16_t *)strt_adds) && 
        (failure_flag != 0x01)
       )
    {
	temp = *ram_add_ptr ;
    if(temp != prv_dta)
      {
      /* setting the error flag if the verification fails */ 
      failure_flag = 0x01;
      }
	else
      {
	  if(prv_dta != 0x00)
	    {
        *ram_add_ptr = crnt_dta;
		}
	  else
	    {
	    //do nothing
	    }
      }
	/* After the last pattern no need to write,only verification is */
	/* required so skipping the writing part */
	if(prv_dta != 0x00)
	  { 
      temp = *ram_add_ptr ;
       
      /* To verify the written data before writing the next location */ 
      if(temp != crnt_dta)
        {
        /* setting the error flag if the verification fails */ 
        failure_flag = 0x01;
	    }
      /* Incrementing the ram_add pointer to the next location */ 
      ram_add_ptr--;
      }
	else
	  {
      /* Incrementing the ram_add pointer to the next location */ 
      ram_add_ptr--;
	  }

    mg_HAL_Service_WatchDog();

	
    }// while(ram_add_ptr >= (@far @gpage uint16_t *)start_add )

}


/*******************************************************************************
 * Function Prototype: void RAM_test(void)
 *
 * Description:  This routine performs ram test according to March N17 algorithm
 *            
 * Argument(s): void
 *
 * External functions: none
 *
 * Return Value: void
 *
 *.****************************************************************************/
void mg_RAM_test(void)
{
  uint8_t    ram_start_1;
  uint8_t    ram_start_2;
  uint8_t    ram_start_3;
  uint8_t    ram_start_4;
  uint8_t    ram_end_1;
  uint8_t    ram_end_2;
  uint8_t    ram_end_3;
  uint8_t    ram_end_4;
  uint32_t   ram_start_add;
  uint32_t   ram_end_add;


  Enable_Interrupts();
  failure_flag = 0;
  out_of_range_flag = 0x01;

  /* shall be stored in a temp location                                 */
  MG_MAILBOX_OUT(parameter[0]) = MG_MAILBOX_IN(testid);

  /* To get the start address of the RAM from mailbox */ 
  ram_start_1    = MG_MAILBOX_IN(parameter[0]);
  ram_start_2    = MG_MAILBOX_IN(parameter[1]);
  ram_start_3    = MG_MAILBOX_IN(parameter[2]);
  ram_start_4    = MG_MAILBOX_IN(parameter[3]);

  /* To get the end address of the RAM from the mail box */
  ram_end_1      = MG_MAILBOX_IN(parameter[4]);
  ram_end_2      = MG_MAILBOX_IN(parameter[5]);
  ram_end_3      = MG_MAILBOX_IN(parameter[6]);
  ram_end_4      = MG_MAILBOX_IN(parameter[7]);
 
  /* To get the start address from the 3 bytes received from the mail box */ 
  ram_start_add = ram_start_1;
  ram_start_add = ((ram_start_add << 8) | ram_start_2);
  ram_start_add = ((ram_start_add << 8) | ram_start_3 );
  ram_start_add = ((ram_start_add << 8) | ram_start_4 );

  /* To get the end address from the 3 bytes received from the mail box */ 
  ram_end_add = ram_end_1;
  ram_end_add = ((ram_end_add << 8) | ram_end_2 );
  ram_end_add = ((ram_end_add << 8) | ram_end_3 );
  ram_end_add = ((ram_end_add << 8) | ram_end_4 );
  /* To perform the ram test only if the address range */ 
  /* lies in 0x40000000 to 0x4000FFFF */

  if ((ram_start_add >= RAM_START_ADDRESS) && (ram_end_add <= RAM_END_ADDRESS))
  {
  	low_to_high_bytes(0x00,0xFF,ram_start_add,ram_end_add);
	if (0 == failure_flag)
	{
	low_to_high_bytes(0xFF,0xAA,ram_start_add,ram_end_add); 
	}
	if (0 == failure_flag)
	{
	low_to_high_bytes(0xAA,0x55,ram_start_add,ram_end_add); 
	}
	if (0 == failure_flag)
	{
	high_to_low_bytes(0x55,0xAA,ram_start_add,ram_end_add);
	}
	if (0 == failure_flag)
	{
	high_to_low_bytes(0xAA,0xA5,ram_start_add,ram_end_add);
	}
	if (0 == failure_flag)
	{
	high_to_low_bytes(0xA5,0x00,ram_start_add,ram_end_add);
	}
	if (0 == failure_flag)
	{
	high_to_low_bytes(0x00,0x00,ram_start_add,ram_end_add);
	}
	
	if (0 == failure_flag)
	{
	low_to_high_words(0x0000,0xFFFF, ram_start_add, ram_end_add - 1);
	}
	if (0 == failure_flag)
	{
	low_to_high_words(0xFFFF,0xAAAA, ram_start_add, ram_end_add - 1);
	}
	if (0 == failure_flag)
	{
	low_to_high_words(0xAAAA,0x5555, ram_start_add, ram_end_add - 1);
	}
  	if (0 == failure_flag)
	{
	high_to_low_words(0x5555,0xAAAA, ram_start_add, ram_end_add - 1);
	}
  	if (0 == failure_flag)
	{
	high_to_low_words(0xAAAA,0xA5A5, ram_start_add, ram_end_add - 1);
	}
  	if (0 == failure_flag)
	{
	high_to_low_words(0xA5A5,0x0000, ram_start_add, ram_end_add - 1);
	}
  	if (0 == failure_flag)
	{
	high_to_low_words(0x0000,0x0000, ram_start_add, ram_end_add - 1);
	}
  }
  else
  {
        failure_flag = 1;
  }

  if (0 == failure_flag)
  {
  	MG_MAILBOX_OUT(parameter[1]) = 0x00;
  }
  else
  {
  	MG_MAILBOX_OUT(parameter[1]) = 0xFF;
  }
}
   	   
