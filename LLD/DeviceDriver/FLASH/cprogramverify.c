 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  flashprogram.c                                       *
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
 * DATE          :  September 16, 2008                                   *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
  0.0.0   2008.09.16         Arvind Awasthi      Initial Version
  0.4.4	  2010.07.27         FPT Team 		     Finalize to this version
  0.4.8	  05.05.2011		 FPT Team		     Add CallBack to input argument 
												 and source code
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"
#include    "ssd_c90fl_internal.h"


UINT32 CprogramVerify (UINT32 dest,
                       UINT32 size,
                       UINT32 source,
                       UINT32 *pFailAddress,
                       UINT64 *pFailData,
                       UINT64 *pFailSource,
					   void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 destIndex;               /* destination address index */
	UINT32 temp;					/* CallBack step */

    returnCode = C90FL_OK;

    /* Check alignments */
    if ( (((dest | size) % C90FL_DWORD_SIZE) != 0) ||
         ((source % C90FL_WORD_SIZE) != 0) )
    {
        returnCode = C90FL_ERROR_ALIGNMENT;
        goto EXIT;
    }

	temp = 0;
    /* Verify data dword by dword */
    for (destIndex = 0; destIndex < (size / C90FL_DWORD_SIZE); destIndex++ )
    {
        if ( *(UINT64 *)dest != *(UINT64 *)source )
        {
            returnCode = C90FL_ERROR_VERIFY;
            *pFailAddress = dest;
            *pFailData = *(UINT64 *)dest;
            *pFailSource = *(UINT64 *)source;
            break;
        }

        dest += C90FL_DWORD_SIZE;
        source += C90FL_DWORD_SIZE;
		
		/* CallBack */
        if ( (CallBack != NULL_CALLBACK) && (destIndex == temp) )
        {
            CallBack();
            temp += CALLBACK_PV;
        }
    }
EXIT:
    return returnCode;
}
