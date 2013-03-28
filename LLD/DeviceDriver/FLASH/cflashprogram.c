 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *                Common Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  flashprogram.c                                       *
 * FUNCTION      :  FlashProgram                                         *
 * DESCRIPTION   :  This function will program user data to specified    *
 *                  flash range..                                        *
 *                  NOTE: The blks need to be unlocked first.            *
 *                  We don't unlock blks in erase function to be         *
 *                  consistent with customer usage, since otherwise it   *
 *                  violates the original intention of block protection. *
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
 *                 C90FL_ERROR_BUSY  - Other HV operation in progress    *
 * DATE          : September 23, 2008                                    *
 * AUTHOR        : Infosys Team                                          *
 * E-mail        : r56611@freescale.com                                  *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
  0.0.0   09.23.2008          Arvind Awasthi      Initial Version
  0.0.1   02.23.2009          Arvind Awasthi      Added size in the function
                                                  parameters to enable page
                                                  programming.
  0.1.0   02.09.2010     FPT Team		add support of program shadow when erase suspend on main array
  0.4.4	  07.27.2010	 FPT Team 		          Finalize to this version
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"


UINT32 CflashProgram (UINT32 MCRAddress,
                      UINT32 shadowRowBase,
                      BOOL mainAddrSpaceSelect,
                      UINT32 dest,
                      UINT32 source,
                      UINT32 size)
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    UINT32 temp;                    /* temporary variable */
    returnCode = C90FL_OK;
    /* load MCR value */
    MCRValue = C90FL_REG_READ (MCRAddress);

    /* Cases that program operation can start:
       1. no program and erase sequence:
          (PGM low and ERS low)
       2. erase suspend with EHV low on main array and try to program main array
          (PGM low, PEAS low, ERS high, ESUS high, EHV low, and rangeType = 2)

       Cases that program operation cannot start:
       1. program in progress (PGM high);
       2. program not in progress (PGM low):
          a. erase in progress but not in suspend state;
 
	*/
    if ( !( (!(MCRValue & (C90FL_MCR_PGM | C90FL_MCR_ERS))) ||
            (!(MCRValue & (C90FL_MCR_PGM | C90FL_MCR_EHV)) &&
              ((MCRValue & (C90FL_MCR_ERS | C90FL_MCR_ESUS)) == (C90FL_MCR_ERS | C90FL_MCR_ESUS))
            ) ) )
    {
        returnCode = C90FL_ERROR_BUSY;
        goto EXIT;
    }
	
    /* Check MCR-EER and MCR-RWE bit */
    if (MCRValue & (C90FL_MCR_EER | C90FL_MCR_RWE))
    {
        returnCode = C90FL_ERROR_BUSY;
        goto EXIT;
        /* FIXME: xuhui changed this, below code will trigger execption */
        /* use shadow row to release bus error */
        //temp = *(VUINT32 *)(shadowRowBase + 0xE0);
    }

    /* Set MCR-PGM to start program operation */
    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_PGM);

    /* Programming write */
    *(UINT64 *)dest = *(UINT64 *)source;
    /* program page if size = C90FL_PAGE_SIZE*/
    if( C90FL_PAGE_SIZE == size)
    {
		/* Update source index */
		dest += C90FL_DWORD_SIZE;
        source += C90FL_DWORD_SIZE;
        *(UINT64 *)dest = *(UINT64 *)source;
	}

    /* Set MCR-EHV bit */
    C90FLMCR_BIT_SET (MCRAddress, C90FL_MCR_EHV);

    /*while ( !(C90FL_REG_READ (MCRAddress) & C90FL_MCR_DONE) )*/
    /*{*/
    /*}*/

    /* Clear MCR-EHV bit */
    /*C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_EHV);*/
    /*C90FLMCR_BIT_CLEAR (MCRAddress, C90FL_MCR_PGM);*/

EXIT:
    return returnCode;
}
