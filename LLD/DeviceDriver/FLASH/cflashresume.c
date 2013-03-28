 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************
 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  cflashresume.c                                       *
 * FUNCTION      :  cflashresume                                         *
 * DESCRIPTION   :  This function will check if there is any suspended   *
 *                  erase or program operation on the C90FL module, and  *
 *                  will resume the suspended operation if there is any. *
 * PARAMETERS    :                                                       *
 *                  MCRValue of the flash block	                         *
 *                  resumeState - variable to store state of the ongoing *
 *                                flash operation                        *
 * RETURN VALUES : bit mask that should be written to MCR reg            *
 *                 													     *
 * DATE          :  September 19, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   09.19.2008         Vikas Kothari	         Initial Version
 0.4.4	 07.27.2010	        FPT Team 		      Finalize to this version
************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"

UINT32 CflashResume (UINT32 MCRValue, UINT8 *resumeState)
{

	UINT32 bitMask;

    *resumeState = RES_NOTHING;
    bitMask = C90FL_MCR_PSUS;

    /* program in suspend state or entering suspend state */
    if (MCRValue & C90FL_MCR_PSUS)
    {
        *resumeState = RES_PGM;

        if (MCRValue & C90FL_MCR_ESUS)
        {
            /* erase-suspended program is suspended */
            *resumeState = RES_ERS_PGM;
        }
    }
    else
    {
        /* erase in suspend state or entering suspend state */
        if ((MCRValue & C90FL_MCR_ESUS) && !(MCRValue & C90FL_MCR_PGM))
        {
            *resumeState = RES_ERS;
            bitMask = C90FL_MCR_ESUS;
        }
        /*else no suspend operation*/

    }
	return bitMask;
}
/* End of File */
