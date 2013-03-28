 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Common Standard Software Driver for C90fl               *
 *                                                                       *
 * FILE NAME     :  cblankcheck.c                                        *
 * FUNCTION      :  cblankcheck                                          *
 * DESCRIPTION   :  This function will c heck whether a block has been   *
 *	 	    erasedThis is a layered architecture, the top layer  *
 *		    is flash dependent and the bottom layer is generic   *
 *		    C90FL flash family.This funnction is the bottom layer*
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 dest - Destination address to be checked.     	 *
 *                 size -  Size in bytes, of the flash region to check.  *
 *                 pFailAddress - sReturn the address of the first 	 *
 *			non-blank Flash location in the checking region	 *
 *                 pFailData - Return the content of the first non-blank *
 *				 Flash location in the checking region.  *
 *                 CallBack  - Callback function pointer for timeout     *
 *                 checking.                                             *
 * RETURN VALUES : C90FL_OK, C90FL_ERROR_ALIGNMENT                       *
 *                 C90FL_ERROR_RANGE, C90FL_ERROR_NOT_BLANK              *
 *									 *                 					 *								         *
 * DATE          :  September 16, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES **********************************
 0.0.0   09.16.2008         Vikas Kothari	    Initial Version
 0.4.4	 07.27.2010	        FPT Team 		    Finalize to this version
 0.4.7   03.24.2011         FPT Team            Fix the issue that BlankCheck 
                                                only scan half of the selected address.
 0.4.8	 05.05.2011		 	FPT Team		    Add CallBack to input argument and source code		
												and add #include "ssd_c90fl_internal.h"
**************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"
#include "ssd_c90fl_internal.h"

UINT32 CblankCheck (UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailAddress,
                    UINT64 *pFailData,
					void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 destIndex;               /* destination address index */
	UINT32 temp;					/* CallBack step */

    returnCode = C90FL_OK;
    /* Check alignments */
    if ( ((dest | size) % C90FL_DWORD_SIZE) != 0 )
    {
        returnCode = C90FL_ERROR_ALIGNMENT;
        goto EXIT;
    }

	temp = 0;	
    /* Blank check by double word */
    for (destIndex = 0; destIndex < (size / C90FL_DWORD_SIZE); destIndex++)
    {
        if ( (*(UINT64 *)dest) != 0xFFFFFFFFFFFFFFFF )
        {
            returnCode = C90FL_ERROR_NOT_BLANK;
            *pFailAddress = dest;
            *pFailData = *(UINT64 *)dest;
            break;
        }
		dest += C90FL_DWORD_SIZE;
		
		/* CallBack */
        if ( (CallBack != NULL_CALLBACK) && (destIndex == temp) )
        {
            CallBack();
            temp += CALLBACK_BC;
        }
	}
EXIT:
	 return returnCode;
}
/* End of File */
