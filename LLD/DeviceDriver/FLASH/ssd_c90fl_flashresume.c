 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  flashresume.c                                        *
 * FUNCTION      :  flashresume                                          *
 * DESCRIPTION   :  This function will check if there is any suspended   *
 *                  erase or program operation on the C90FL module, and  *
 *                  will resume the suspended operation if there is any. *
 * PARAMETERS    :                                                       *
 *                  pSSDConfig - Flash driver configuration structure    *
 *                  resumeState - variable to store state of the ongoing *
 *                                flash operation                        *
 * RETURN VALUES : C90FL_OK									             *
 *                 													     *
 * DATE          :  September 19, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   09.19.2008         Vikas Kothari	      Initial Version
 0.4.4	 07.27.2010	        FPT Team 		      Finalize to this version
 0.4.8   05.05.2011			FPT Team			  Add #include "ssd_c90fl_internal.h"
												  and remove #define FLASH_RESUME_WAIT
************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"
#include "ssd_c90fl_internal.h"

#if (DIAB_COMPILER == COMPILER_SELECT)
asm void write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif


UINT32 ssd_c90fl_FlashResume (PSSD_CONFIG pSSDConfig, UINT8 *resumeState)
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    UINT32 bitMask;                 /* PSUS or ESUS bit to be cleared */
    UINT32 count;                   /* the loop count for the wait loop */

    count = FLASH_RESUME_WAIT;
    returnCode = C90FL_OK;
    *resumeState = RES_NOTHING;

	/*BK0*/
    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

	/*Only if program or erase suspended, call resume*/
	if((MCRValue & C90FL_MCR_PSUS) || (MCRValue & C90FL_MCR_ESUS))
	{
		bitMask = CflashResume (MCRValue, resumeState);
	    /* Set MCR-EHV bit */
	    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);

	    /* clear the MCR-ESUS bit or MCR-PSUS bit */
	    C90FLMCR_BIT_CLEAR (MCRAddress, bitMask);

	    /* wait the MCR-DONE bit goes low */
	    while ( C90FL_REG_BIT_TEST (MCRAddress, C90FL_MCR_DONE) && (count--) > 0);
	}

	/*BK1*/
    count = FLASH_RESUME_WAIT;
    MCRAddress = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

	/*Only if program or erase suspended, call resume*/
	if((MCRValue & C90FL_MCR_PSUS) || (MCRValue & C90FL_MCR_ESUS))
	{
		bitMask = CflashResume (MCRValue, resumeState);
	    /* Set MCR-EHV bit */
	    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);

	    /* clear the MCR-ESUS bit or MCR-PSUS bit */
	    C90FLMCR_BIT_CLEAR (MCRAddress, bitMask);

	    /* wait the MCR-DONE bit goes low */
	    while ( C90FL_REG_BIT_TEST (MCRAddress, C90FL_MCR_DONE) && (count--) > 0);
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
/* End of File */
