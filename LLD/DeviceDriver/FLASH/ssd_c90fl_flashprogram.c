 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  FlashProgram.c                                       *
 * FUNCTION      :  FlashProgram                                         *
 * DESCRIPTION   :  This function will program user data to specified    *
 *                  flash range..                                        *
 *                  NOTE: The blks need to be unlocked first.            *
 *                  We don't unlock blks in erase function to be         *
 *                  consistent with customer usage, since otherwise it   *
 *                  violates the original intention of block protection. *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 dest - start flash addr to be programmed              *
 *                 size - number of bytes to be programmed               *
 *                        (need to be dword-aligned)                     *
 *                 source - start RAM addr for source data               *
 *                          (need to be word-aligned)                    *
 *                 CallBack  - Callback function pointer for timeout     *
 *                             checking                                  *
 * RETURN VALUES : C90FL_OK          - Program passes                    *
 *                 C90FL_ERROR_EGOOD - Program fails                     *
 *                 C90FL_ERROR_BUSY  - Other HV operation in progress    *
 *                 C90FL_ERROR_RANGE - Invalid addr range                *
 *                 C90FL_ERROR_ALIGNMENT - Invalid alignment             *
 * DATE          : September 23, 2008                                    *
 * AUTHOR        : Infosys Team                                          *
 * E-mail        : r56611@freescale.com                                  *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
  0.0.0   09.23.2008         Arvind Awasthi    Initial Version
  0.0.1	  11.10.2008		 Chen He		   Correct HAS blks logic
  0.0.2   12.17.2008         Arvind Awasthi	   Adresses of BANKS made
                                               relative to main array
                                               base
  0.0.3   02.23.2009         Arvind Awasthi    Modified to program page
                                               and parallel program
                                               across the two banks.
  0.1.0	  02.09.2010	  FPT Team		  PFBIU buffer is automatically invalidated by hardware
										  Add Checking whether each page programing is OK or not
  0.4.4	  07.27.2010	  FPT Team 		       Finalize to this version									  
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"


#if (DIAB_COMPILER == COMPILER_SELECT)
asm void write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif

UINT32 ssd_c90fl_FlashProgram ( PSSD_CONFIG pSSDConfig,
                      UINT32 dest,
                      UINT32 size,
                      UINT32 source,
                      void(*CallBack)(void)
                      )
{
    register UINT32 returnCode;     /* return code */
    UINT32 shadowRowEnd;            /* shadow row base + shadow size */
    UINT32 shadowRowEnd_bk1;		/* shadow row base + shadow size - module B */
    UINT32 mainArrayEnd;            /* main array base + main array size */
    UINT32 temp;                    /* dest + size, or size / C90FL_DWORD_SIZE */
    //UINT32 pfb_cr_val;              /* value of PFB_CR register */
    UINT32 dest_Bk0;                /* destination address in BANK0 */
    UINT32 size_Bk0;                /* size to be programmed in BANK0 */
    UINT32 source_Bk0;              /* source for BANK0 */
    UINT32 dest_Bk1;                /* destination address in BANK1 */
    UINT32 size_Bk1;                /* size to be programmed in BANK1 */
    UINT32 source_Bk1;              /* source for BANK1 */
    UINT32 dest_HAS;                /* destination address for HAS */
    UINT32 size_HAS;                /* size to be programmed in HAS */
    UINT32 source_HAS;              /* source for HAS */
    UINT32 MCRAddress0;             /* MCR address for BANK0 */
    UINT32 MCRAddress1;             /* MCR address for BANK1 */
    UINT8  pgmBank;                 /* variable to track programming of the two banks*/
    UINT8 errorPgmFlag;             /* Variable for error on programming*/
    BOOL   mainAddrSpaceSelect;     /* passed to underlying driver indicating destination address lies in main address space of BANK0*/

    returnCode = C90FL_OK;
    /* Check alignments */
    if ( (((dest | size) % C90FL_DWORD_SIZE) != 0) ||
         ((source % C90FL_WORD_SIZE) != 0))
    {
        returnCode = C90FL_ERROR_ALIGNMENT;
        goto EXIT;
    }
    /* The flash range should fall within either shadow row or main array */
    shadowRowEnd = pSSDConfig->shadowRowBase + pSSDConfig->shadowRowSize;
    shadowRowEnd_bk1 = (pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET) + SHADOW_ROW_BANK1_SIZE;
    mainArrayEnd = pSSDConfig->mainArrayBase + pSSDConfig->mainArraySize;
    temp = dest + size;

    if (!(((dest >= pSSDConfig->shadowRowBase) && (dest < shadowRowEnd) &&
        (size <= pSSDConfig->shadowRowSize) && (temp <= shadowRowEnd)) ||
		((dest >= (pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET)) && (dest < shadowRowEnd_bk1) &&
        (size <= SHADOW_ROW_BANK1_SIZE) && (temp <= shadowRowEnd_bk1)) ||
        ((dest >= pSSDConfig->mainArrayBase) && (dest < mainArrayEnd) &&
         (size <= pSSDConfig->mainArraySize) && (temp <= mainArrayEnd))))
    {
        /* Address is an invalid address */
        returnCode = C90FL_ERROR_RANGE;
        goto EXIT;
    }
    /* Anything to program? */
    if ( !size )
    {
        goto EXIT;
	}
    mainAddrSpaceSelect = 0;
    if((dest >= pSSDConfig->mainArrayBase) && /*(dest < mainArrayEnd) &&*/
         /*(size <= pSSDConfig->mainArraySize) &&*/ (temp <= mainArrayEnd))
    {
         mainAddrSpaceSelect = 1;
    }
    /* address of MCR register for BANK0*/
    MCRAddress0 = pSSDConfig->c90flRegBase + C90FL_MCR;
    /* address of MCR register for BANK1*/
    MCRAddress1 = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET + C90FL_MCR;
    /* Initialize all variables to zero */
    size_Bk0 =0;
    size_Bk1 =0;
    size_HAS =0;
    pgmBank = 0;
    errorPgmFlag =0;
    /* initilzation finish*/

    /* dest lies in Shadow Row of BANK1*/
    if ((dest >= (pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET)) && (temp <= ((pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET) + SHADOW_ROW_BANK1_SIZE)))
    {
        dest_Bk1 = dest;
        size_Bk1 = size;
        source_Bk1 = source;
	}
    else if ((dest >= (pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET)) && (temp <= ((pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET) + SHADOW_ROW_BANK0_SIZE)))
    {
	    /* dest lies in Shadow of BANK0*/
        dest_Bk0 = dest;
        size_Bk0 = size;
        source_Bk0 = source;
	}
	else /* check for main array programming*/
	{
         /* Destination address lies in logical LAS blks */
		 if( (dest < (pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR) ))
		 {
		     /* Addresses to be programmed are only in physical LAS*/
		     if( temp <pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR)
		     {
				dest_Bk0 = dest;
				size_Bk0 = size;
				source_Bk0 = source;
				/* keep dest and size as it is */
		     }
		     else if ( temp < pSSDConfig->mainArrayBase + C90FL_HAS_STARTADDR)
		     {
		     	/* Addresses to be programmed are in physical LAS and MAS*/
			    dest_Bk0 = dest;
			    size_Bk0= pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR - dest_Bk0;
			    source_Bk0 = source;
			    dest_Bk1 = pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR;
			    size_Bk1 = size - size_Bk0;
			    source_Bk1 = source + size_Bk0;
		     }
		     else
		     {
		     	/* Addresses to be programmed are in physical LAS,MAS and HAS*/
			    dest_Bk0 = dest;
			    size_Bk0 = pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR - dest_Bk0 ;
			    source_Bk0 = source;
			    dest_Bk1 = pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR;
			    size_Bk1 = C90FL_MAS_SIZE;
			    source_Bk1 = source + size_Bk0;
			    dest_HAS = pSSDConfig->mainArrayBase + C90FL_HAS_STARTADDR;
			    size_HAS = size - (size_Bk1 + size_Bk0);
			    source_HAS = source + size_Bk0 + size_Bk1;
			 }
		 }
		 else if( dest < pSSDConfig->mainArrayBase + C90FL_HAS_STARTADDR)
		 {
		 	 /* Addresses to be programmed are only in MAS*/
		 	 if( temp < pSSDConfig->mainArrayBase + C90FL_HAS_STARTADDR)
		 	 {
		         /* only one address space has to be programmed */
                 dest_Bk1 = dest;
				 size_Bk1 = size;
				 source_Bk1 = source;
		 	 }
		 	 else
		 	 {
			 	 /*Addresses to be programmed are in MAS and HAS*/
		 	     dest_Bk1 = dest;
		 		 size_Bk1= pSSDConfig->mainArrayBase + C90FL_HAS_STARTADDR - dest_Bk1;
		 		 source_Bk1 = source;
		 		 dest_HAS = pSSDConfig->mainArrayBase + C90FL_HAS_STARTADDR;
		 		 size_HAS = size - size_Bk1;
		 		 source_HAS = source + size_Bk1;
		     }
		 }
		 else
		 {
		     /* Get the MCR register value for BANK1 */
			 /* Addresses to be programmed are only in HAS*/
		 	 dest_HAS = dest;
		 	 size_HAS = size;
		 	 source_HAS = source;
		 }
	}/* check for main array programming -- end*/

 /* Program data Dword by Dword*/
 while ( (size_Bk0 + size_Bk1 + size_HAS) > 0)
 {
     /* program LAS */
     if (size_Bk0 > 0)
     {
		 /* program page if size is greater than a page and dest address is page aligned*/
		 if((size_Bk0/C90FL_PAGE_SIZE) && ((dest_Bk0 & 0x08) == 0x0))
		 {
			 /* call underlying flash driver with correct parameters to program in LAS(BANK0)*/
			 returnCode = CflashProgram (MCRAddress0,(pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET),mainAddrSpaceSelect,dest_Bk0,source_Bk0,C90FL_PAGE_SIZE);
			 /* increment destination, size and source*/
			 dest_Bk0 = dest_Bk0 + C90FL_PAGE_SIZE;
			 source_Bk0 = source_Bk0 + C90FL_PAGE_SIZE;
			 size_Bk0 = size_Bk0 - C90FL_PAGE_SIZE;
             pgmBank |= 0x01;
		 }
		 else
		 {
			 /* call underlying flash driver with correct parameters to program in LAS(BANK0)*/
			 returnCode = CflashProgram (MCRAddress0,(pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET),mainAddrSpaceSelect,dest_Bk0,source_Bk0,C90FL_DWORD_SIZE);
			 /* increment destination, size and source*/
			 dest_Bk0 = dest_Bk0 + C90FL_DWORD_SIZE;
			 source_Bk0 = source_Bk0 + C90FL_DWORD_SIZE;
			 size_Bk0 = size_Bk0 - C90FL_DWORD_SIZE;
             pgmBank |= 0x01;
		 }

	 }
	 /* program MAS */
	 /* if required both will be programmed parallely */
	 if( size_Bk1> 0)
	 {
         /* program page if size is greater than a page and dest address is page aligned*/
		 if((size_Bk1/C90FL_PAGE_SIZE) && ((dest_Bk1 & 0x08) == 0x0))
		 {
		    /* call underlying flash driver with correct parameters to program in MAS(BANK1)*/
		    returnCode = CflashProgram (MCRAddress1,(pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET),mainAddrSpaceSelect,dest_Bk1,source_Bk1,C90FL_PAGE_SIZE);
		    /* increment destination, size and source*/
		    dest_Bk1 = dest_Bk1 + C90FL_PAGE_SIZE;
		    source_Bk1 = source_Bk1 + C90FL_PAGE_SIZE;
            size_Bk1 = size_Bk1 - C90FL_PAGE_SIZE;
            pgmBank |= 0x02;
		 }
		 else
		 {
		    /* call underlying flash driver with correct parameters to program in MAS(BANK1)*/
		    returnCode = CflashProgram (MCRAddress1,(pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET),mainAddrSpaceSelect,dest_Bk1,source_Bk1,C90FL_DWORD_SIZE);
		    /* increment destination, size and source*/
		    dest_Bk1 = dest_Bk1 + C90FL_DWORD_SIZE;
		    source_Bk1 = source_Bk1 + C90FL_DWORD_SIZE;
            size_Bk1 = size_Bk1 - C90FL_DWORD_SIZE;
            pgmBank |= 0x02;
		 }
	 }
	 /* HAS programming */
	 if((0 == size_Bk0) && (0 == size_Bk1) && (size_HAS > 0))
	 {
		 /* reuse LAS and MAS variables for HAS programming */
		 /* Bk0 variables are used to store HAS Bank0 parameters */
		 /* Bk1 variables are used to store HAS Bank1 parameters */
		 /* If the DWORD to be programmed lies in BANK1 */
		 if(dest_HAS & 0x10)
		 {
			 if((dest_HAS & 0x08) || (!(size_HAS/C90FL_PAGE_SIZE)))
			 {
			    /* call CflashProgram to program HAS of BANK1*/
		        returnCode = CflashProgram (MCRAddress1,(pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET),mainAddrSpaceSelect,dest_HAS,source_HAS,C90FL_DWORD_SIZE);
			    /* increment destination, size and source*/
			    dest_HAS = dest_HAS + C90FL_DWORD_SIZE;
			    source_HAS = source_HAS + C90FL_DWORD_SIZE;
	            size_HAS = size_HAS - C90FL_DWORD_SIZE;
	            pgmBank |= 0x02;
			 }
			 else
			 {
			    /* call CflashProgram to program HAS of BANK1*/
		        returnCode = CflashProgram (MCRAddress1,(pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET),mainAddrSpaceSelect,dest_HAS,source_HAS,C90FL_PAGE_SIZE);
			    /* increment destination, size and source*/
			    dest_HAS = dest_HAS + C90FL_PAGE_SIZE;
			    source_HAS = source_HAS + C90FL_PAGE_SIZE;
	            size_HAS = size_HAS - C90FL_PAGE_SIZE;
	            pgmBank |= 0x02;
			 }
	     }
	     if(!(dest_HAS & 0x10) && (size_HAS >0) ) /* The DWORD to be programmed lies in BANK0 */
	     {
			 if((dest_HAS & 0x08) || (!(size_HAS/C90FL_PAGE_SIZE)))
			 {
			    /* call CflashProgram to program HAS of BANK0 */
			    returnCode = CflashProgram (MCRAddress0,(pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET),mainAddrSpaceSelect,dest_HAS,source_HAS,C90FL_DWORD_SIZE);
			    /* increment destination, size and source*/
			    dest_HAS = dest_HAS + C90FL_DWORD_SIZE;
			    source_HAS = source_HAS + C90FL_DWORD_SIZE;
	            size_HAS = size_HAS - C90FL_DWORD_SIZE;
	            pgmBank |= 0x01;
		     }
		     else
		     {
			    /* call CflashProgram to program HAS of BANK0 */
			    returnCode = CflashProgram (MCRAddress0,(pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET),mainAddrSpaceSelect,dest_HAS,source_HAS,C90FL_PAGE_SIZE);
			    /* increment destination, size and source*/
			    dest_HAS = dest_HAS + C90FL_PAGE_SIZE;
			    source_HAS = source_HAS + C90FL_PAGE_SIZE;
	            size_HAS = size_HAS - C90FL_PAGE_SIZE;
	            pgmBank |= 0x01;
			 }
		 }
	 }/* HAS programming --end */
	  /* Check whether the page programing is OK or not */
	 if (C90FL_ERROR_BUSY == returnCode)
	 {
	 	goto EXIT;	 	
	 }
     /* wait for Bank0 programming to finish*/
     if (pgmBank & 0x01)
     {
         /* Wait until MCR-DONE set */
         while ( !(C90FL_REG_READ (MCRAddress0) & C90FL_MCR_DONE))
         {
             if (CallBack != NULL_CALLBACK)
             {
                 CallBack();
             }
         }
         /* Confirm MCR-PEG = 1 */
         if ( !(C90FL_REG_READ (MCRAddress0) & C90FL_MCR_PEG) )
         {
             /* Clear MCR-EHV bit */
             C90FLMCR_BIT_CLEAR (MCRAddress0, C90FL_MCR_EHV);
             returnCode = C90FL_ERROR_PGOOD;
             errorPgmFlag |= 0x01;
             goto EXIT_EHV;
         }
		 /* Clear MCR-EHV bit */
		 C90FLMCR_BIT_CLEAR (MCRAddress0, C90FL_MCR_EHV);
		 /* clear bank0 flag*/
		 pgmBank &= ~(0x01);
		 /* save PFB_CR */
		 //pfb_cr_val = C90FL_REG_READ(pSSDConfig->c90flRegBase + PFB_CR);
		 /* Invalidate the PFBIU line read buffer */
		 //C90FL_REG_BIT_CLEAR (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);
		 /* Clear MCR-PGM bit */
		 C90FLMCR_BIT_CLEAR (MCRAddress0, C90FL_MCR_PGM);
		 /* Validate the PFBIU line read buffer */
		 //C90FL_REG_BIT_SET (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);
		 /* restore PFB_CR */
		 //C90FL_REG_WRITE(pSSDConfig->c90flRegBase + PFB_CR, pfb_cr_val);
	 }
     /* wait for Bank0 programming to finish*/
     if(pgmBank & 0x02)
     {
         /* Wait until MCR-DONE set */
         while ( !(C90FL_REG_READ (MCRAddress1) & C90FL_MCR_DONE) )
         {
             if (CallBack != NULL_CALLBACK)
             {
                 CallBack();
             }
         }
         /* Confirm MCR-PEG = 1 */
         if ( !(C90FL_REG_READ (MCRAddress1) & C90FL_MCR_PEG) )
         {
             /* Clear MCR-EHV bit */
             C90FLMCR_BIT_CLEAR (MCRAddress1, C90FL_MCR_EHV);

             returnCode = C90FL_ERROR_PGOOD;
             errorPgmFlag |= 0x02;
             goto EXIT_EHV;
         }
         /* Clear MCR-EHV bit */
         C90FLMCR_BIT_CLEAR (MCRAddress1, C90FL_MCR_EHV);
         /* clear bank1 flag*/
         pgmBank &= ~(0x02);
         /*PFCR Register is only accessible via Flash A.
         Treat as Reserved in Flash B.*/
          /* save PFB_CR */
	     //pfb_cr_val = C90FL_REG_READ(pSSDConfig->c90flRegBase + PFB_CR);
	     /* Invalidate the PFBIU line read buffer */
	     //C90FL_REG_BIT_CLEAR (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);
	     /* Clear MCR-PGM bit */
	     C90FLMCR_BIT_CLEAR (MCRAddress1, C90FL_MCR_PGM);
	     /* Validate the PFBIU line read buffer */
	     //C90FL_REG_BIT_SET (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);
	     /* restore PFB_CR */
	     //C90FL_REG_WRITE(pSSDConfig->c90flRegBase + PFB_CR, pfb_cr_val);
	  }

 }


EXIT_EHV:

    if (errorPgmFlag & 0x03)
    {
        /* save PFB_CR */
        //pfb_cr_val = C90FL_REG_READ(pSSDConfig->c90flRegBase + PFB_CR);
        /* Invalidate the PFBIU line read buffer */
        //C90FL_REG_BIT_CLEAR (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);
        if (errorPgmFlag & 0x01)
        {
            /* Clear MCR-PGM bit */
            C90FLMCR_BIT_CLEAR (MCRAddress0, C90FL_MCR_PGM);
        }
        if(errorPgmFlag & 0x02)
        {
           /* Clear MCR-PGM bit */
           C90FLMCR_BIT_CLEAR (MCRAddress1, C90FL_MCR_PGM);
        }
        /* Validate the PFBIU line read buffer */
        //C90FL_REG_BIT_SET (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);
        /* restore PFB_CR */
        //C90FL_REG_WRITE(pSSDConfig->c90flRegBase + PFB_CR, pfb_cr_val);
    }


EXIT:
    if (pSSDConfig->BDMEnable)
    {
        /* save the return code to R3 */
        /* For CodeWarrior */
        #if (CODE_WARRIOR == COMPILER_SELECT)
        asm ( "mr   r3,returnCode" );
        #else
        /* For Diab */
        write_r3(returnCode);
        #endif

        #ifdef VLE_ASM
            asm ( "nop" );
            asm ( "se_sc " );                  /* generate system call interrupt */
            asm ( "nop" );
        #else
            asm ( "nop" );
            asm ( "sc " );
            asm ( "nop" );
        #endif
    }

    return returnCode;
}
