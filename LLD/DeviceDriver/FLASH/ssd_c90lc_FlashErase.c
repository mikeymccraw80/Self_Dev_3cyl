/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : flasherase.c
*
* DESCRIPTION : This file contains FlashErase function implementation
*
* COPYRIGHT :(c) 2009, Freescale & STMicroelectronics
*
* VERSION   : Beta 1.0
* DATE      : 10.26.2009
* AUTHOR    : ...
*
* HISTORY :
* 2007.12.11    Arvind Awasthi   Initial Version
* 2007.12.13    Chen He          Added test mode workaround for Monaco rev0
* 2008.03.28    Leonardo Colombo Porting for SPC560B:Removed test mode
*                                workaround for Monaco rev0
* 2008.04.18    Leonardo Colombo SPC560B SPC560P CFLASH DFLASH management
* 2008.08.29    Leonardo Colombo  SPC560B SPC560P CFLASH DFLASH management
*                                 SPC560S CFLASH0 CFLASH1 DFLASH management
* 2009.01.28    Leonardo Colombo  Porting for xPC563M64 devices (C0, C1, C2)
* 2009.04.08    Leonardo Colombo  Porting for xPC560B64 devices (C MM, D)
* 2009.10.26		  Leonardo Colombo		"Unified" version supporting all targets with LC flash
******************************************************************/


#include "ssd_types.h"
#include "ssd_c90lc.h"

/*******************************************************************
| external declarations
|------------------------------------------------------------------*/

/*******************************************************************
| defines and macros (scope: module-local)
|------------------------------------------------------------------*/
#define CFLASH_BASE_ADDR   (UINT32)(0xC3F88000)
#define DFLASH_BASE_ADDR   (UINT32)(0xC3F8C000)

/*******************************************************************
| typedefs and structures (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| global variable definitions (scope: module-exported)
|------------------------------------------------------------------*/

/*******************************************************************
| global variable definitions (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function prototypes (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function implementations (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function implementations (scope: module-exported)
|------------------------------------------------------------------*/

/*************************************************************************
 *                                                                       *
 * FUNCTION      : FlashErase                                            *
 * DESCRIPTION   : This function will erase selected blks.               *
 *                 NOTE: The blks need to be unlocked first.             *
 *                 We don't unlock blks in erase function to be          *
 *                 consistent with customer usage, since otherwise it    *
 *                 violates the original intention of block protection.  *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 shadowFlag - determine if shadow row needs to be      *
 *                 erased                                                *
 *                 lowEnabledBlocks - selected Low Address Space block(s)*
 *                 midEnabledBlocks - selected Mid Address Space block(s)*
 *                 highEnabledBlocks - selected High Address Space       *
 *                 block(s)                                              *
 *                 CallBack  - Callback function pointer for timeout     *
 *                 checking.                                             *
 * RETURN VALUES : C90FL_OK          - Erase passes                      *
 *                 C90FL_ERROR_EGOOD - Erase fails                       *
 *                 C90FL_ERROR_BUSY  - Other HV operation in progress    *
 *                                                                       *
 *************************************************************************/
UINT32 ssd_c90lc_FlashErase ( PSSD_CONFIG pSSDConfig,
                    BOOL shadowFlag,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
                    void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 regBase;                 /* base address of C90FL registers */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 LMSAddress;              /* address of C90FLLMS register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    UINT32 interlockWriteAddress;   /* interlock write address */
	   UINT32 pfb_cr_val;				          /* value of PFB_CR register */

    regBase = pSSDConfig->c90flRegBase;
    MCRAddress = regBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);
    LMSAddress = regBase + C90FL_LMS;

    /* program and/or erase operation in progress */
    if (MCRValue & (C90FL_MCR_PGM | C90FL_MCR_ERS))
    {
        returnCode = C90FL_ERROR_BUSY;
        goto EXIT;
    }

    /* interlock write address: shadow row block key address */
    /* it will be modified to mainArrayBase in case of erasing main array */
    if((UINT32)0x0 != pSSDConfig->shadowRowBase)
    {
       interlockWriteAddress = pSSDConfig->shadowRowBase + 0xE0;
    }

    /* initialize returnCode */
    returnCode = C90FL_OK;

    if (!shadowFlag)
    {
        /* erase the main array blocks */
        interlockWriteAddress = pSSDConfig->mainArrayBase;

        /* mask off reserved bits for low address space */
        lowEnabledBlocks &= 0xFFFFFFFF >> (32 - pSSDConfig->lowBlockNum);

        /* mask off reserved bits for mid address space */
        lowEnabledBlocks |= (midEnabledBlocks & (0xFFFFFFFF >> (32 - pSSDConfig->midBlockNum))) << 16;

        /* mask off reserved bits for high address space */
        highEnabledBlocks &= 0xFFFFFFFF >> (32 - pSSDConfig->highBlockNum);

        if ( !(lowEnabledBlocks | highEnabledBlocks) )
        {
            /* no blocks to be erased */
            goto EXIT;
        }

        /* set the block selection registers */
        C90FL_REG_WRITE (LMSAddress, lowEnabledBlocks);
        C90FL_REG_WRITE (regBase + C90FL_HBS, highEnabledBlocks);
    }
    else
    {
        if((UINT32)0x0 == pSSDConfig->shadowRowBase)
        {
            /* Shadow block erase has been requested but there is no shadow block */
            goto EXIT;
        }
    }

    /* set MCR-ERS to start erase operation */
    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_ERS);

    /* interlock write */
    *( (UINT32 *)interlockWriteAddress ) = 0xFFFFFFFF;

    /* write a 1 to MCR-EHV */
    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);

    /* wait until MCR-DONE set */
    while ( !(C90FL_REG_READ (MCRAddress) & C90FL_MCR_DONE) )
    {
        if (CallBack != NULL_CALLBACK)
        {
            CallBack();
        }
    }

    /* clear MCR-EHV bit */
    C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);

    /* confirm MCR-PEG = 1 */
    if ( !(C90FL_REG_READ (MCRAddress) & C90FL_MCR_PEG) )
    {
        returnCode = C90FL_ERROR_EGOOD;
    }

    if(DFLASH_BASE_ADDR != pSSDConfig->c90flRegBase)   /* CFLASH */
    {
       /* save PFB_CR */
       pfb_cr_val = C90FL_REG_READ(CFLASH_BASE_ADDR + PFB_CR);

       /* Invalidate the PFBIU line read buffer */
       C90FL_REG_BIT_CLEAR (CFLASH_BASE_ADDR + PFB_CR, PFB_CR_BFEN);

       /* clear MCR-ERS bit */
       C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_ERS);

       /* restore PFB_CR */
       C90FL_REG_WRITE(CFLASH_BASE_ADDR + PFB_CR, pfb_cr_val);
    }

    if(DFLASH_BASE_ADDR == pSSDConfig->c90flRegBase)  /* DFLASH */
    {
       /* save PFB_CR1 */
       pfb_cr_val = C90FL_REG_READ(CFLASH_BASE_ADDR + PFB_CR1);

       /* Invalidate the PFBIU holding register */
       C90FL_REG_BIT_CLEAR (CFLASH_BASE_ADDR + PFB_CR1, PFB_CR_BFEN);

       /* clear MCR-ERS bit */
       C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_ERS);

       /* restore PFB_CR1 */
       C90FL_REG_WRITE(CFLASH_BASE_ADDR + PFB_CR1, pfb_cr_val);
    }

EXIT:

    if (pSSDConfig->BDMEnable)
    {
        //asm ( "mr   r3,returnCode" );   /* save the return code to R3 */
        #ifdef VLE_ASM
        	asm ( "se_sc " );                /* generate system call interrupt */
        #else
        	asm ( "sc" );
        #endif
    }

    return returnCode;
}
