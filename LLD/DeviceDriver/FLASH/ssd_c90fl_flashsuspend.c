 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  flashsuspend.c                                       *
 * FUNCTION      :  flashsuspend                                         *
 * DESCRIPTION   :  This function will check if there is any high voltage*
 *                  operation, erase or program, in progress on the C90FL*
 *                  module and if the operation can be suspended.        *
 *                  This function will suspend the ongoing operation     *
 *                  if it can be suspended.                              *
 * PARAMETERS    :                                                       *
 *                  pSSDConfig - Flash driver configuration structure    *
 *                  suspendState and Suspend flag - variables to store   *
 *                      state of the ongoing flash operation             *
 * RETURN VALUES : C90FL_OK									             *
 *                 													     *
 * DATE          :  September 18, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   09.18.2008         Vikas Kothari	         Initial Version
 0.4.4	 07.27.2010	        FPT Team 		     	 Finalize to this version
*************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"


#if (DIAB_COMPILER == COMPILER_SELECT)
asm void write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif

UINT32 ssd_c90fl_FlashSuspend (PSSD_CONFIG pSSDConfig, UINT8 *suspendState, UINT8 *suspendFlag)
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */

    returnCode = C90FL_OK;
    *suspendState = NO_OPERATION;
    *suspendFlag = FALSE;

	/*Check for BK0*/
    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

    /* No program/erase sequence */
    if ( !(MCRValue & (C90FL_MCR_PGM | C90FL_MCR_ERS)) )
    {
       /* Do nothing*/
    }
    else
    {
    	CflashSuspend (MCRAddress,suspendState, suspendFlag);
        /* Wait until MCR-DONE = 1 */
        while ( !C90FL_REG_BIT_TEST (MCRAddress, C90FL_MCR_DONE) )
        {
        }

        /* Set MCR-EHV to 0 */
        C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);

    }


	/*check for BK1*/
    MCRAddress = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);
    /* No program/erase sequence */
    if ( !(MCRValue & (C90FL_MCR_PGM | C90FL_MCR_ERS)) )
    {
        goto EXIT;
    }
	CflashSuspend (MCRAddress,suspendState, suspendFlag);
    /* Wait until MCR-DONE = 1 */
    while ( !C90FL_REG_BIT_TEST (MCRAddress, C90FL_MCR_DONE) )
    {
    }

    /* Set MCR-EHV to 0 */
    C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);

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
