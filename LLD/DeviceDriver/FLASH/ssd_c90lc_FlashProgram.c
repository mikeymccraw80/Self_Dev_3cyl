/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : flashprogram.c
*
* DESCRIPTION : This file contains FlashProgram function implementation
*
* COPYRIGHT :(c) 2008, Freescale & STMicroelectronics
*
* VERSION   : Beta 1.0
* DATE      : 10.26.2009
* AUTHOR    : ...
*
* HISTORY :
* 2007.12.11    Arvind Awasthi   Initial Version
* 2007.12.13    Chen He          Removed PFBIU related code
* 2008.02.05    Chen He          Mask off addr[17] for shadow row program
*                                Add back code to invalide PFBIU buffer.
* 2008.03.31    Leonardo Colombo Porting for SPC560B: Added 8 bytes page length
*                                                     management
* 2008.04.18    Leonardo Colombo SPC560B SPC560P CFLASH DFLASH management
* 2008.08.29    Leonardo Colombo SPC560B SPC560P CFLASH DFLASH management
*                                SPC560S CFLASH0 CFLASH1 DFLASH management
* 2009.01.28     Leonardo Colombo Porting for xPC563M64 devices (C0, C1, C2)
* 2009.04.08    Leonardo Colombo Porting for xPC560B64 devices (C MM, D)
* 2009.10.26		 Leonardo Colombo		"Unified" version supporting all targets with LC flash
******************************************************************/


#include    "ssd_types.h"
#include    "ssd_c90lc.h"

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

 /************************************************************************
 *                                                                       *
 * FUNCTION      : FlashProgram                                          *
 * DESCRIPTION   : This function will program user data to specified     *
 *                 flash range..                                         *
 *                 NOTE: The blks need to be unlocked first.             *
 *                 We don't unlock blks in erase function to be          *
 *                 consistent with customer usage, since otherwise it    *
 *                 violates the original intention of block protection.  *
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
 *                                                                       *
 *************************************************************************/
UINT32 ssd_c90lc_FlashProgram ( PSSD_CONFIG pSSDConfig,
                      UINT32 dest,
                      UINT32 size,
                      UINT32 source,
                      void(*CallBack)(void)
                      )
{
    register UINT32 returnCode;     /* return code */

    UINT32 sourceIndex;             /* source address index */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */

    UINT32 shadowRowEnd;            /* shadow row base + shadow size */
    UINT32 mainArrayEnd;            /* main array base + main array size */
    UINT32 temp;                    /* dest + size, or size / C90FL_DWORD_SIZE */
    UINT32 pageSize = (UINT32)8;    /* page size depending on flash type */

    UINT8 rangeType;                /* position of the program memory range */
                                    /* rangeType = 1    -    shadow row */
                                    /* rangeType = 2    -    main array */

	   UINT32 pfb_cr_val;				          /* value of PFB_CR register */

    returnCode = C90FL_OK;
    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;

    /* Check alignments */
    if ( (((dest | size) % C90FL_DWORD_SIZE) != 0) ||
         ((source % C90FL_WORD_SIZE) != 0))
    {
        returnCode = C90FL_ERROR_ALIGNMENT;
        goto EXIT;
    }

    /* The flash range should fall within either shadow row or main array */
    shadowRowEnd = pSSDConfig->shadowRowBase + pSSDConfig->shadowRowSize;
    mainArrayEnd = pSSDConfig->mainArrayBase + pSSDConfig->mainArraySize;
    temp = dest + size;

    if ((dest >= pSSDConfig->shadowRowBase) && (dest < shadowRowEnd) &&
        (size <= pSSDConfig->shadowRowSize) && (temp <= shadowRowEnd))
    {
        /* fall in shadow row */
        rangeType = 1;
    }
    else if ((dest >= pSSDConfig->mainArrayBase) && (dest < mainArrayEnd) &&
             (size <= pSSDConfig->mainArraySize) && (temp <= mainArrayEnd))
    {
        /* fall in main array */
        rangeType = 2;
    }
    else
    {
        returnCode = C90FL_ERROR_RANGE;
        goto EXIT;
    }

    /* Anything to program? */
    if ( !size )
    {
        goto EXIT;
    }

    MCRValue = C90FL_REG_READ (MCRAddress);

    /* Check if program and/or erase operation in progress */
    if (MCRValue & (C90FL_MCR_PGM | C90FL_MCR_ERS | C90FL_MCR_ESUS))
    {
        returnCode = C90FL_ERROR_BUSY;
        goto EXIT;
    }

    /* Set MCR-PGM to start program operation */
    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_PGM);

    /* number of double words */
    temp = size / C90FL_DWORD_SIZE;

    /* determine the page size */
    if (pSSDConfig->pageSize == C90FL_PAGE_SIZE_32)
    {
        pageSize = (UINT32)32;
    }
    else if(pSSDConfig->pageSize == C90FL_PAGE_SIZE_16)
    {
        pageSize = (UINT32)16;
    }
    else if(pSSDConfig->pageSize == C90FL_PAGE_SIZE_08)
    {
        pageSize = (UINT32)8;
    }

    /* Program data page by page, with special attention to incomplete page */
    for (sourceIndex = 1; sourceIndex <= temp; sourceIndex++)
    {
        /* Programming write */
        *(UINT64 *)dest = *(UINT64 *)source;

        /* Update source index */
        dest += C90FL_DWORD_SIZE;
        source += C90FL_DWORD_SIZE;

        /* Is it time to do page programming?  */
        if ( ((dest % pageSize) == 0) || (sourceIndex == temp) )
        {
            /* Set MCR-EHV bit */
            C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);

            /* Wait until MCR-DONE set */
            while ( !(C90FL_REG_READ (MCRAddress) & C90FL_MCR_DONE) )
            {
                if (CallBack != NULL_CALLBACK)
                {
                    CallBack();
                }
            }

            /* Confirm MCR-PEG = 1 */
            if ( !(C90FL_REG_READ (MCRAddress) & C90FL_MCR_PEG) )
            {
                /* Clear MCR-EHV bit */
                C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);

                returnCode = C90FL_ERROR_PGOOD;
                goto EXIT_EHV;
            }

            /* Clear MCR-EHV bit */
            C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);
        }
    }

EXIT_EHV:
    /* Clear MCR-PGM bit */
    C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_PGM);

    if(DFLASH_BASE_ADDR != pSSDConfig->c90flRegBase)   /* CFLASH */
    {
       /* save PFB_CR */
       pfb_cr_val = C90FL_REG_READ(CFLASH_BASE_ADDR + PFB_CR);

       /* Invalidate the PFBIU line read buffer */
       C90FL_REG_BIT_CLEAR (CFLASH_BASE_ADDR + PFB_CR, PFB_CR_BFEN);

       /* restore PFB_CR */
       C90FL_REG_WRITE(CFLASH_BASE_ADDR + PFB_CR, pfb_cr_val);
    }

    if(DFLASH_BASE_ADDR == pSSDConfig->c90flRegBase)   /* DFLASH */
    {
       /* save PFB_CR1 */
       pfb_cr_val = C90FL_REG_READ(CFLASH_BASE_ADDR + PFB_CR1);

       /* Invalidate the PFBIU holding register */
       C90FL_REG_BIT_CLEAR (CFLASH_BASE_ADDR + PFB_CR1, PFB_CR_BFEN);

       /* restore PFB_CR1 */
       C90FL_REG_WRITE(CFLASH_BASE_ADDR + PFB_CR1, pfb_cr_val);
    }

EXIT:
    if (pSSDConfig->BDMEnable)
    {
        //asm ( "mr   r3,returnCode" );   /* save the return code to R3 */
        #ifdef VLE_ASM
        	asm ( "se_sc " );                  /* generate system call interrupt */
        #else
        	asm ( "sc " );
        #endif
    }

    return returnCode;
}
