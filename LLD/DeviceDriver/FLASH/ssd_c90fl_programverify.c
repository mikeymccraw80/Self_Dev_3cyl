 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  programverify.c                                      *
 * FUNCTION      :  ProgramVerify                                        *
 * DESCRIPTION   :  This function will verify programmed data in         *
 *                  specified flash range.                               *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 dest      - start flash addr to be programmed         *
 *                 size      - number of bytes to be programmed          *
 *                             (need to be dword-aligned)                *
 *                 source    - start RAM addr for source data            *
 *                             (need to be word-aligned)                 *
 *                 pFailAddress - pointer to first failing address       *
 *                 pFailData     - pointer to first failing actual data  *
 *                 pFailSource   - pointer to first failing expected data*
 *                 CallBack  - Callback function pointer for timeout     *
 *                             checking.                                 *
 *  RETURN        : C90FL_OK           - passes                          *
 *                  C90FL_ERROR_VERIFY - failed verify                   *
 *                  C90FL_ERROR_RANGE  - Invalid addr range              *
 *                  C90FL_ERROR_ALIGNMENT - Invalid alignment            *
 * DATE          :  Sep 16, 2008                                         *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
  0.0.0   2008.09.16        Arvind Awasthi    Initial Version
  0.0.1   12.17.2008        Arvind Awasthi	  Adresses of BANKS made
                                              relative to main array
                                              base
  0.4.4	  07.27.2010	    FPT Team 		  Finalize to this version			
  0.4.8	  05.05.2011		FPT Team		  Add CallBack input to CprogramVerify
											  Remove #include "ssd_c90fl_internal.h" 
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"


#if (DIAB_COMPILER == COMPILER_SELECT)
asm void write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif

UINT32 ssd_c90fl_ProgramVerify ( PSSD_CONFIG pSSDConfig,
                       UINT32 dest,
                       UINT32 size,
                       UINT32 source,
                       UINT32 *pFailAddress,
                       UINT64 *pFailData,
                       UINT64 *pFailSource,
                       void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 shadowRowEnd;            /* shadow row base + shadow size */
    UINT32 shadowRowEnd_bk1;        /* shadow row base + shadow size - module B */
    UINT32 mainArrayEnd;            /* main array base + main array size */
    UINT32 endAddress;              /* dest + size, or CallBack step */

    returnCode = C90FL_OK;

    /* The flash range to be verified should fall within either shadow row or main array */
    shadowRowEnd = pSSDConfig->shadowRowBase + pSSDConfig->shadowRowSize;
    shadowRowEnd_bk1 = (pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET) + SHADOW_ROW_BANK1_SIZE;
    mainArrayEnd = pSSDConfig->mainArrayBase + pSSDConfig->mainArraySize;
    endAddress = dest + size;

    if ( !((dest >= pSSDConfig->shadowRowBase) && (dest < shadowRowEnd) &&
           (size <= pSSDConfig->shadowRowSize) && (endAddress <= shadowRowEnd))
         &&
         !((dest >= pSSDConfig->mainArrayBase) && (dest < mainArrayEnd) &&
           (size <= pSSDConfig->mainArraySize) && (endAddress <= mainArrayEnd))
         &&
          !((dest >= (pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET)) && (dest < shadowRowEnd_bk1) &&
           (size <= SHADOW_ROW_BANK1_SIZE) && (endAddress <= shadowRowEnd_bk1)) )
    {
        returnCode = C90FL_ERROR_RANGE;
        goto EXIT;
    }


    /* call underlying flash driver with correct destination,size and source*/
    returnCode = CprogramVerify(dest,size,source,pFailAddress,pFailData,pFailSource,CallBack);

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
