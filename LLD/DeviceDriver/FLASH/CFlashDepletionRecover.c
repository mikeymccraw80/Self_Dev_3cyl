 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  CFlashDepletionRecover.c                             *
 * FUNCTION      :  Common low level flash depletion recover             *
 * DESCRIPTION   :  This function will soft program selected blks.       *
 *                  NOTE: The blks need to be unlocked first.            *
 *                  We don't unlock blks in erase function to be         *
 *                  consistent with customer usage, since otherwise it   *
 *                  violates the original intention of block protection. *
 *	 				This is a layered architecture, the top layer is     *
 *					flash dependent and the bottom layer is generic for  *
 *					C90FL flash family. This is the bottom layer		 *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 shadowFlag - determine if shadow row needs to be      *
 *                 soft programmed                                       *
 *                 lowEnabledBlocks - selected Low Address Space block(s)*
 *                 midEnabledBlocks - selected Mid Address Space block(s)*
 *                 highEnabledBlocks - selected High Address Space       *
 *                 block(s)                                              *
 * RETURN VALUES : C90FL_OK          - Soft program passes               *
 *                 C90FL_ERROR_EGOOD - Soft program fails                *
 *                 C90FL_ERROR_BUSY  - Other HV operation in progress    *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.1   05.23.2011         Chen He	         Initial Version ported from cflasherase
************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"
/*
Notes:

shadow flag
b00 - No shadow block selected
b01 - Shadow block 1 selected
b10 - Shadow block 0 selected
b11 - Both shadow blocks selected

User					Hardware
12 block in LAS			10 blocks in LAS and 2 blocks of MAS in BK0
2 blocks in MAS			1 block in LAS and 1 block in MAS in BK1
6 blocks in HAS 		6 blocks in HAS in each bank viz BK0 & BK1
*/

UINT32 CFlashDepletionRecover ( PSSD_CONFIG pSSDConfig,
                    UINT8 shadowFlag,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks)
{

    register UINT32 returnCode;     /* return code */
    UINT32 c90flRegBase;              /* base address of C90FL registers */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    UINT32 interlockWriteAddress;   /* interlock write address */

    c90flRegBase = pSSDConfig->c90flRegBase;
    MCRAddress = c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

    /* initialize returnCode */
    returnCode = C90FL_OK;

    /* program and/or erase operation in progress */
    if (MCRValue & (C90FL_MCR_PGM | C90FL_MCR_ERS))
    {
        returnCode = C90FL_ERROR_BUSY;
        goto EXIT;
    }

    /* interlock write address: shadow row block key address */
    /* it will be modified to mainArrayBase in case of erasing main array */
    interlockWriteAddress = pSSDConfig->shadowRowBase + 0xE0;

    /* Check MCR-EER and MCR-RWE bit */
    if (MCRValue & (C90FL_MCR_EER | C90FL_MCR_RWE))
    {
        /* read shadow row block key address to clear bus transfer error */
        /* this is a software workaround for some C90FL revision. */
        /* use returnCode temporarily */
        returnCode = *(VUINT32 *)interlockWriteAddress;
    }

    /* initialize returnCode */
    returnCode = C90FL_OK;

    if (!shadowFlag)
    {
        /* soft program the main array blocks */
        interlockWriteAddress = pSSDConfig->mainArrayBase;
        /* shift bits for mid address space */
        lowEnabledBlocks |= (midEnabledBlocks << 16);

        if ( !(lowEnabledBlocks | highEnabledBlocks) )
        {
            /* no blocks to be erased */
            goto EXIT;
        }

        /* set the block selection registers */
        C90FL_REG_WRITE (c90flRegBase + C90FL_LMS, lowEnabledBlocks);
        C90FL_REG_WRITE (c90flRegBase + C90FL_HBS, highEnabledBlocks);
    }
    
    //enter flash test mode
    *((VUINT32 *) (c90flRegBase + 0xAC)) = 0x24E25B81;
    *((VUINT32 *) (c90flRegBase + 0xBC)) = 0xA588EF0B;
    *((VUINT32 *) (c90flRegBase + 0xA4)) = 0xF97E8178;
    *((VUINT32 *) (c90flRegBase + 0xA8)) = 0xBCD9A55D;
    
    //set TME
    C90FL_REG_WRITE(c90flRegBase + 0x100, 0x80000000);
    
	//Set FFC0 CS0 with Soft Program Verify, NSP0 Done Pass and NSF0 with Soft Program Pulse.
	//Set FFC0 CS1 with soft Program Pulse, NSP1  soft Program Verify and NSF1 with Done Fail.
	//Clear FFC0 FB.
    C90FL_REG_WRITE(c90flRegBase + 0x14c, 0x098f08e9);
    
	/* set MCR-ERS to start erase operation */
	C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_ERS);

	/* interlock write */
	*( (UINT32 *)interlockWriteAddress ) = 0xFFFFFFFF;

	/* write a 1 to MCR-EHV */
	C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);
	
EXIT:
	return returnCode;
}
/*End of file*/

