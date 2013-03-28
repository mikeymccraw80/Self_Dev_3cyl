 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  cflasherase.c                                        *
 * FUNCTION      :  CflashErase                                          *
 * DESCRIPTION   :  This function will erase selected blks.              *
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
 *                 erased                                                *
 *                 lowEnabledBlocks - selected Low Address Space block(s)*
 *                 midEnabledBlocks - selected Mid Address Space block(s)*
 *                 highEnabledBlocks - selected High Address Space       *
 *                 block(s)                                              *
 * RETURN VALUES : C90FL_OK          - Erase passes                      *
 *                 C90FL_ERROR_EGOOD - Erase fails                       *
 *                 C90FL_ERROR_BUSY  - Other HV operation in progress    *
 * DATE          :  September 10, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   09.15.2008         Vikas Kothari	         Initial Version
 0.4.4	 07.27.2010	        FPT Team 		     Finalize to this version
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

UINT32 CflashErase ( PSSD_CONFIG pSSDConfig,
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
        returnCode = C90FL_ERROR_BUSY;
        goto EXIT;
        // FIXME: xuhui comment below code, it will trigger exception
        /* read shadow row block key address to clear bus transfer error */
        /* this is a software workaround for some C90FL revision. */
        /* use returnCode temporarily */
        /*returnCode = *(VUINT32 *)interlockWriteAddress;*/
    }

    /* initialize returnCode */
    returnCode = C90FL_OK;

    if (!shadowFlag)
    {
        /* erase the main array blocks */
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

	/* set MCR-ERS to start erase operation */
	C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_ERS);

	/* interlock write */
	*( (UINT32 *)interlockWriteAddress ) = 0xFFFFFFFF;

	/* write a 1 to MCR-EHV */
	C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);

    /* wait until MCR-DONE set */
    /*while ( !(C90FL_REG_READ (MCRAddress) & C90FL_MCR_DONE) )*/
    /*{*/
    /*}*/

    /* clear MCR-EHV bit */
    /*C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);*/
    /*C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_ERS);*/




EXIT:
	return returnCode;
}
/*End of file*/

