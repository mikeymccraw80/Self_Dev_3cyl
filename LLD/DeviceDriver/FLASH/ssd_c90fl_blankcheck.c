 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  blankcheck.c                                         *
 * FUNCTION      :  blankcheck                                           *
 * DESCRIPTION   :  This function will check whether a block has been    *
 *	 	    erasedThis is a layered architecture, the top layer  *
 *		    is flash dependent and the bottom layer is generic   *
 *		    forC90FL flash family.This function is the top layer *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 dest - Destination address to be checked.      	 *
 *                 size -  Size in bytes, of the flash region to check.  *
 *                 pFailAddress - sReturn the address of the first 	 *
 *		   non-blank Flash location in the checking region	 *
 *                 pFailData - Return the content of the first non-blank *
 *				 Flash location in the checking region.  *
 *                 CallBack  - Callback function pointer for timeout     *
 *                 checking.                                             *
 * RETURN VALUES : C90FL_OK, C90FL_ERROR_ALIGNMENT                       *
 *                 C90FL_ERROR_RANGE, C90FL_ERROR_NOT_BLANK              *
 *                 							 *						       *                                                                       * 
 * DATE          :  September 16, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   09.16.2008         Vikas Kothari	     Initial Version
 0.0.1   12.17.2008         Arvind Awasthi	     Address of BANKS made
                                                 relative to main array
                                                 base
 0.4.4	 07.27.2010	        FPT Team 		     Finalize to this version		
 0.4.8	 05.05.2011		 	FPT Team		     Add CallBack input to CblankCheck													 
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

UINT32 ssd_c90fl_BlankCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailAddress,
                    UINT64 *pFailData,
                    void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 shadowRowEnd;            /* shadow row base + shadow size */
    UINT32 shadowRowEnd_bk1;        /* shadow row base + shadow size */
    UINT32 mainArrayEnd;            /* main array base + main array size */
    UINT32 endAddress;              /* dest + size, or CallBack step */

    /* The flash range should fall within either shadow row or main array */
    shadowRowEnd = pSSDConfig->shadowRowBase + pSSDConfig->shadowRowSize;
    shadowRowEnd_bk1 = (pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET) + SHADOW_ROW_BANK1_SIZE;
    mainArrayEnd = pSSDConfig->mainArrayBase + pSSDConfig->mainArraySize;
    endAddress = dest + size;

    if ( !(((dest >= pSSDConfig->shadowRowBase) && (dest < shadowRowEnd) &&
           (size <= pSSDConfig->shadowRowSize) && (endAddress <= shadowRowEnd))
          ||
         ((dest >= pSSDConfig->mainArrayBase) && (dest < mainArrayEnd) &&
           (size <= pSSDConfig->mainArraySize) && (endAddress <= mainArrayEnd))
         ||
          ((dest >= (pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET)) && (dest < shadowRowEnd_bk1) &&
           (size <= SHADOW_ROW_BANK1_SIZE) && (endAddress <= shadowRowEnd_bk1))) )
    {
        returnCode = C90FL_ERROR_RANGE;
        goto EXIT;
    }

	returnCode = CblankCheck(dest, size, pFailAddress, pFailData, CallBack);
	
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
