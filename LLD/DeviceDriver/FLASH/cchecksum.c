 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  cchecksum.c                                          *
 * FUNCTION      :  CcheckSum                                            *
 * DESCRIPTION   :  This function will perform a 32-bit sum over the     *
 *                   specified flash memory range without carry, which   *
 *                   provides a rapid method for checking data integrity *
 * PARAMETERS    :                                                       *
 *                  pSSDConfig - Flash driver configuration structure    *
 *                  dest - Variable to store address from where checksum *
 *                         has to be calculated                          *
 *                  size - Variable to store size for which checksum has *
 *                         to be calculated                              *
 *                  psum - pointer to store checksum                     *
 *                  *CallBack - function pointer to Callback function    *
 * RETURN        : C90FL_OK - passes                                     *
 *                 C90FL_ERROR_ALIGNMENT - Alignment Error               *
 *                 C90FL_ERROR_RANGE - Range Error                       *
 * DATE          : September 20, 2008                                    *
 * AUTHOR        : Infosys Team                                          *
 * E-mail        : r56611@freescale.com                                  *
 *                                                                       *
 *************************************************************************/

 /******************************* CHANGES *********************************
  0.0.0   2008.09.20          Arvind Awasthi      Initial Version
  0.4.4	  2010.07.27          FPT Team 		      Finalize to this version
  0.4.8	  05.05.2011		  FPT Team		      Add CallBack to input 
												  argument and source code	
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"
#include    "ssd_c90fl_internal.h"


UINT32 CcheckSum (UINT32 dest,
                  UINT32 size,
                  UINT32 *pSum,
				  void(*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 destIndex;               /* destination address index */
	UINT32 temp; 					/* CallBack step */


    /* Check alignments */
    if ( ((dest | size) % C90FL_DWORD_SIZE) != 0 )
    {
        returnCode = C90FL_ERROR_ALIGNMENT;
        goto EXIT;
    }

    returnCode = C90FL_OK;

    *pSum = 0;
	temp = 0;
    /* word by word checksum */
    for (destIndex = 0; destIndex < (size / C90FL_WORD_SIZE); destIndex++)
    {
        *pSum += *(UINT32 *)dest;

        dest += C90FL_WORD_SIZE;
		
		/* CallBack */
    	if( (CallBack != NULL_CALLBACK) && (destIndex == temp) )
    	{
        	CallBack();
        	temp += CALLBACK_CS;
    	}
    }

EXIT:

    return returnCode;
}
