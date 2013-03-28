/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : FlashResume.c
*
* DESCRIPTION :  This function will check if there is any suspended
*                                erase operation on the C90FL module, and
*                                will resume the suspended operation if there is any.
*
* COPYRIGHT :(c) 2009, Freescale & STMicroelectronics
*
* VERSION   : Beta 1.0
* DATE      : 11.05.2009
* AUTHOR    : ...
*
* HISTORY :
* 2009.11.05		 	   Leonardo Colombo		"Unified" version supporting all targets with LC flash
******************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90lc.h"
#include    "ssd_c90lc_internal.h"

/*******************************************************************
| external declarations
|------------------------------------------------------------------*/

/*******************************************************************
| defines and macros (scope: module-local)
|------------------------------------------------------------------*/
#define CFLASH_BASE_ADDR   (UINT32)(0xC3F88000)
#define DFLASH_BASE_ADDR   (UINT32)(0xC3F8C000)
#define C1_BASE_ADDR       (UINT32)(0xC3FB0000)
#define C2_BASE_ADDR       (UINT32)(0xC3FB4000)

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
 * FUNCTION      :  Flashresume
 * DESCRIPTION   :  This function will check if there is any suspended
 *                                  erase operation on the C90FL module, and
 *                                  will resume the suspended operation if there is any.
 * PARAMETERS    :
 *                  pSSDConfig - Flash driver configuration structure
 *                  resumeState - variable to store state of the ongoing
 *                                flash operation
 * RETURN        : C90FL_OK - passes
 *************************************************************************/
UINT32 ssd_c90lc_FlashResume (PSSD_CONFIG pSSDConfig, UINT8 *resumeState)
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    UINT32 bitMask;                 /* PSUS or ESUS bit to be cleared */
    INT32  count;                   /* the loop count for the wait loop */

    returnCode = C90FL_OK;
    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

    count = FLASH_RESUME_WAIT;

    *resumeState = RES_NOTHING;
    bitMask = C90FL_MCR_PSUS;

    /* erase in suspend state or entering suspend state */
    if ((MCRValue & C90FL_MCR_ESUS))
    {
         *resumeState = RES_ERS;
         bitMask = C90FL_MCR_ESUS;
    }
    else
    {
         /* No suspended operation */
         goto EXIT;
    }

    /* Set MCR-EHV bit */
    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);

    /* clear the MCR-ESUS bit or MCR-PSUS bit */
    C90FLMCR_BIT_CLEAR (MCRAddress, bitMask);

    /* wait the MCR-DONE bit goes low */
    while ( C90FL_REG_BIT_TEST (MCRAddress, C90FL_MCR_DONE) && (count--) > 0);

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

