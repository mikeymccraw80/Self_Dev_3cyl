 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  FlashDepletionRecover.c                              *
 * FUNCTION      :  Flash depletion recover with soft program only		 *
 * DESCRIPTION   :  This function will soft program selected blks.       *
 *                  NOTE: The blks need to be unlocked first.            *
 *                  We don't unlock blks in erase function to be         *
 *                  consistent with customer usage, since otherwise it   *
 *                  violates the original intention of block protection. *
 *	 				This is a layered architecture, the top layer is     *
 *					flash dependent and the bottom layer is generic for  *
 *					C90FL flash family. This function is the top layer.	 *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 shadowFlag - determine if shadow row needs to be      *
 *                 soft programmed                                       *
 *                 lowEnabledBlocks - selected Low Address Space block(s)*
 *                 midEnabledBlocks - selected Mid Address Space block(s)*
 *                 highEnabledBlocks - selected High Address Space       *
 *                 block(s)                                              *
 *                 CallBack  - Callback function pointer for timeout     *
 *                 checking.                                             *
 * RETURN VALUES : C90FL_OK          - Soft program passes               *
 *                 C90FL_ERROR_EGOOD - Soft program fails                *
 *                 C90FL_ERROR_BUSY  - Other HV operation in progress    *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.1   05.23.2011         Chen He	     Initial Version ported over from FlashErase
************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"


#if (DIAB_COMPILER == COMPILER_SELECT)
asm void write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif
/*
Notes:
shadow flag
b00 - No shadow block selected
b01 - Shadow block 0 selected
b10 - Shadow block 0 selected
b11 - Both shadow blocks selected

User					Hardware
12 block in LAS			10 blocks in LAS and 2 blocks of MAS in BK0
2 blocks in MAS			1 block in LAS and 1 block in MAS in BK1
6 blocks in HAS 		6 blocks in HAS in each bank viz BK0 & BK1
*/
UINT32 ssd_c90fl_FlashDepletionRecover ( PSSD_CONFIG pSSDConfig,
                    UINT8 shadowFlag,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
                    void (*CallBack)(void))
{
	UINT8 bkFlag;
	UINT8 cShadowFlag;
    register UINT32 returnCode;     /* return code */
    UINT32 c90flRegBase;              /* base address of C90FL registers */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
	UINT32 temp;
    UINT32 cLowEnabledBlocks;
    UINT32 cMidEnabledBlocks;
    UINT32 cHighEnabledBlocks;
    //UINT32 pfb_cr_val;              /* value of PFB_CR register */
	SSD_CONFIG ssdConfig0;
	SSD_CONFIG ssdConfig1;

	/*clear the bank erase flags*/
	bkFlag = 0;
    /* initialize returnCode */
    returnCode = C90FL_OK;

	/*Is the block in LAS or HAS */
	if(((lowEnabledBlocks | highEnabledBlocks) != 0) || ((shadowFlag & 0x01) == 0x01))
	{
	    /* Get MAS blocks of BANK0*/
	    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
	    MCRValue = C90FL_REG_READ (MCRAddress);

	    /* Determine the number of blocks in middle address space in BANK0*/
		if ( MCRValue & C90FL_MCR_MAS)
		{
		    temp = 1;
		}
		else
		{
		    temp = 2;
	    }

	    /* Store BANK0 parameters in local SSDConfig structure*/
		ssdConfig0.c90flRegBase  = pSSDConfig->c90flRegBase;
		ssdConfig0.mainArrayBase = pSSDConfig->mainArrayBase;
		ssdConfig0.mainArraySize = (pSSDConfig->mainArraySize + C90FL_LAS_SIZE - C90FL_MAS_SIZE)>>1;
		ssdConfig0.shadowRowBase = pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET;
		ssdConfig0.shadowRowSize  = SHADOW_ROW_BANK0_SIZE;
		ssdConfig0.lowBlockNum   = pSSDConfig->lowBlockNum - temp;
		ssdConfig0.midBlockNum   = temp;
		ssdConfig0.highBlockNum  = pSSDConfig->highBlockNum;
		ssdConfig0.pageSize      = pSSDConfig->pageSize;
	    ssdConfig0.BDMEnable     = pSSDConfig->BDMEnable;

		cShadowFlag = shadowFlag & 0x01;
		/*convert LAS and HAS to BK0 and BK1 locations*/

        /* mask off reserved bits for low address space */
        cLowEnabledBlocks = (lowEnabledBlocks & (0xFFFFFFFF >> (32 - ssdConfig0.lowBlockNum)));
        /* mask off reserved bits for mid address space */
		cMidEnabledBlocks = (lowEnabledBlocks  >> ssdConfig0.lowBlockNum);
        /* mask off reserved bits for high address space */
        cHighEnabledBlocks = (highEnabledBlocks & (0xFFFFFFFF >> (32 - ssdConfig0.highBlockNum)));


		/*invoke the common flash erase routine */
		returnCode |= CFlashDepletionRecover (&ssdConfig0, cShadowFlag, cLowEnabledBlocks, cMidEnabledBlocks, cHighEnabledBlocks);
		/*set flag to indicate bank zero is being erased*/
		bkFlag |= 0x01;
	}
	
	/* Check return value of the erase operation in this bank */
	if (C90FL_ERROR_BUSY == returnCode){
		return returnCode;
	}
	/*Is the block in MAS or HAS*/
	if (((midEnabledBlocks | highEnabledBlocks) != 0) || ((shadowFlag & 0x02) == 0x02))
	{
	    /* Get MAS blocks of BANK1*/
	    MCRAddress = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET + C90FL_MCR;
	    MCRValue = C90FL_REG_READ (MCRAddress);

	    /* Determine the number of blocks in middle address space in BANK0*/
		if ( MCRValue & C90FL_MCR_MAS)
		{
		    temp = 1;
		}
		else
		{
		    temp = 2;
	    }

	    /* Store BANK1 parameters in local SSDConfig structure*/
		ssdConfig1.c90flRegBase  = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET;
		ssdConfig1.mainArrayBase = pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR;
		ssdConfig1.mainArraySize = (pSSDConfig->mainArraySize + C90FL_MAS_SIZE - C90FL_LAS_SIZE)>>1;
		ssdConfig1.shadowRowBase = pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET;
		ssdConfig1.shadowRowSize  = SHADOW_ROW_BANK1_SIZE;
		ssdConfig1.lowBlockNum   = pSSDConfig->midBlockNum - temp;
		ssdConfig1.midBlockNum   = temp;
		ssdConfig1.highBlockNum  = pSSDConfig->highBlockNum;
		ssdConfig1.pageSize      = pSSDConfig->pageSize;
	    ssdConfig1.BDMEnable     = pSSDConfig->BDMEnable;

		cShadowFlag = shadowFlag & 0x02;
		/*convert MAS and HAS to BK0 and BK1 locations*/

        /* mask off reserved bits for low address space */
        cLowEnabledBlocks = (midEnabledBlocks & (0xFFFFFFFF >> (32 - ssdConfig1.lowBlockNum)));
        /* mask off reserved bits for mid address space */
        cMidEnabledBlocks = (midEnabledBlocks >> ssdConfig1.lowBlockNum);
        /* mask off reserved bits for high address space */
        cHighEnabledBlocks = (highEnabledBlocks & (0xFFFFFFFF >> (32 - ssdConfig1.highBlockNum)));

		/*invoke the common flash soft program routine */
		returnCode |= CFlashDepletionRecover (&ssdConfig1, cShadowFlag, cLowEnabledBlocks, cMidEnabledBlocks, cHighEnabledBlocks);
		/*set flag to indicate bank zero is being erased*/
		bkFlag |= 0x02;
	}
	/* Check return value of the soft program operation in this bank */
	if (C90FL_ERROR_BUSY == returnCode){
		return returnCode;
	}
	/*If blocks in BK 0 were soft programmed*/
	if(bkFlag & 0x01)
	{
	    /*Point to the BK0 register set*/
	    c90flRegBase = pSSDConfig->c90flRegBase;
	    MCRAddress = c90flRegBase + C90FL_MCR;
		/*Wait for the flash operation for BK0 to complete*/
	    while(!(C90FL_REG_READ(MCRAddress) & C90FL_MCR_DONE))
	    {
	        if(CallBack != NULL_CALLBACK)
	        {
	            CallBack();
	        }
	    }
		/* clear high voltage bit */
		C90FLMCR_BIT_CLEAR(MCRAddress, C90FL_MCR_EHV);

		/* Was program/erase good? */
		if (!(C90FL_REG_READ(MCRAddress) & C90FL_MCR_PEG))
		{
		   returnCode = C90FL_ERROR_EGOOD;
		}
        /* save PFB_CR */
        //pfb_cr_val = C90FL_REG_READ(c90flRegBase + PFB_CR);

        /* Invalidate the PFBIU line read buffer */
        //C90FL_REG_BIT_CLEAR (c90flRegBase + PFB_CR, PFB_CR_BFEN);

		/* clear erase bit in MCR */
		C90FLMCR_BIT_CLEAR(MCRAddress, C90FL_MCR_ERS);
		
		//reset FFC0
		C90FL_REG_WRITE(c90flRegBase + 0x14c, 0xffffffff);
		
		//clear TME to mask off all test mode regs
		C90FL_REG_WRITE(c90flRegBase + 0x100, 0);

        /* Validate the PFBIU line read buffer */
        //C90FL_REG_BIT_SET (c90flRegBase + PFB_CR, PFB_CR_BFEN);

        /* restore PFB_CR */
        //C90FL_REG_WRITE(c90flRegBase + PFB_CR, pfb_cr_val);
	}
	/*If blocks in BK 1 were soft programmed*/
	if(bkFlag & 0x02)
	{
	    /*Point to the BK1 register set*/
	    c90flRegBase = ((pSSDConfig->c90flRegBase) + BANK1_REG_BASEOFFSET);
	    MCRAddress = c90flRegBase + C90FL_MCR;
		/*Wait for the flash operation for BK1 to complete*/
	    while(!(C90FL_REG_READ(MCRAddress) & C90FL_MCR_DONE))
	    {
	        if(CallBack != NULL_CALLBACK)
	        {
	            CallBack();
	        }
	    }
		/* clear high voltage bit */
		C90FLMCR_BIT_CLEAR(MCRAddress, C90FL_MCR_EHV);

		/* Was program/erase good? */
		if (!(C90FL_REG_READ(MCRAddress) & C90FL_MCR_PEG))
		{
		   returnCode = C90FL_ERROR_EGOOD;
		}

        /*PFCR Register is only accessible via Flash A.
        Treat as Reserved in Flash B.*/

        /* save PFB_CR */
        //pfb_cr_val = C90FL_REG_READ(pSSDConfig->c90flRegBase + PFB_CR);

        /* Invalidate the PFBIU line read buffer */
        //C90FL_REG_BIT_CLEAR (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);

		/* clear erase bit in MCR */
		C90FLMCR_BIT_CLEAR(MCRAddress, C90FL_MCR_ERS);

		//reset FFC0
		C90FL_REG_WRITE(c90flRegBase + 0x14c, 0xffffffff);
		
		//clear TME to mask off all test mode regs
		C90FL_REG_WRITE(c90flRegBase + 0x100, 0);

        /* Validate the PFBIU line read buffer */
        //C90FL_REG_BIT_SET (pSSDConfig->c90flRegBase + PFB_CR, PFB_CR_BFEN);

        /* restore PFB_CR */
        //C90FL_REG_WRITE(pSSDConfig->c90flRegBase + PFB_CR, pfb_cr_val);
	}

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
/*End of file*/


