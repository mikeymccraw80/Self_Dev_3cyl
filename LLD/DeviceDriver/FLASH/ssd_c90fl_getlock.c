 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl(2)           *
 *                                                                       *
 * FILE NAME     :  getlock.c                                            *
 * FUNCTION      :  GetLock                                              *
 * DESCRIPTION   :  This function will check the block locking status of *
 *                  Shadow/Low/Middle/High address spaces in the C90FL   *
 *                  module.                                              *
 * PARAMETERS    :                                                       *
 *                  pSSDConfig - Flash driver configuration structure    *
 *                  blkLockIndicator - variable for storing block lock   *
 *                                    indicator value                    *
 *                  blkLockEnabled - flag to keep track of lock          *
 *                  blkLockState - variable for storing block lock state *
 *                                 value                                 *
 * RETURN        : C90FL_OK - passes                                     *
 *                 C90FL_ERROR_LOCK_INDICATOR - wrong indicator value    *
 *                 C90FL_ERROR_PASSWORD - incorrect password             *
 * DATE          : September 17, 2008                                    *
 * AUTHOR        : Infosys Team                                          *
 * E-mail        : r56611@freescale.com                                  *
 *                                                                       *
 *************************************************************************/

 /******************************* CHANGES *********************************
  0.0.0   09.16.2008        Arvind Awasthi      Initial Version
  0.0.1   12.17.2008        Arvind Awasthi      Optimized code to generate
                                                binaries in Diab compiler.
  0.4.4   07.27.2010      FPT Team              Finalize for this version                                    
  0.4.5	  10.27.2010		FPT Team			Fix bug in get user middle address space	
  0.4.6	  01.11.2011		FPT Team			Finalize to this version
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

UINT32 ssd_c90fl_GetLock ( PSSD_CONFIG pSSDConfig,
                 UINT8 blkLockIndicator,
                 BOOL *blkLockEnabled,
                 UINT32 *blkLockState)
{
    register UINT32 returnCode;     /* return code */
    UINT32 mask;                    /* block locking bit mask for the address space */
    UINT32 blkLockStateTemp;        /* Local variable to store block lock status */
    BOOL   blkLockEnabledTemp;      /* Local Variable to store enabled state of block*/
    UINT32 lowBlockNumberBk0;      /* Temporary variable to store Low blocks of BANK0 */
    UINT32 lowBlockNumberBk1;      /* Temporary variable to store Low blocks of BANK1 */
    UINT32 MCRAddress;             /* address of C90FLMCR register */
    UINT32 MCRValue;               /* content of C90FLMCR register */
    BOOL   shadowLockPrimary;      /* variable passed to common driver TRUE: When shadow lock primary is enabled*/
    UINT8  blkLockIndicatorTemp,i;

    if (blkLockIndicator > LOCK_HIGH)
    {
        returnCode = C90FL_ERROR_LOCK_INDICATOR;
        goto EXIT;
    }

    returnCode = C90FL_OK;
    /* make flag for primary lock for shadow row as false */
    shadowLockPrimary = FALSE;
    /* Get MCR value for BANK0*/
    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);
    /* Determine the number of blocks in middle address space in BANK0*/
    if ( MCRValue & C90FL_MCR_MAS)
    {
        mask = 1;
    }
    else
    {
        mask = 2;
    }
    lowBlockNumberBk0 = pSSDConfig->lowBlockNum - mask;

    /* Get MCR value for BANK1*/
    MCRAddress = (pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET) + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);
    /* Determine the number of blocks in middle address space in BANK1*/
    if ( MCRValue & C90FL_MCR_MAS)
    {
        mask = 1;
    }
    else
    {
        mask = 2;
    }
    lowBlockNumberBk1 = pSSDConfig->midBlockNum - mask;


    if (LOCK_SHADOW0_PRIMARY == blkLockIndicator || LOCK_SHADOW0_SECONDARY == blkLockIndicator )
    {
        if(LOCK_SHADOW0_PRIMARY == blkLockIndicator)
	    {
		    shadowLockPrimary = TRUE;
	    }
        /* Get Lock status for shadow row of BANK1 */
        returnCode = CgetLock(pSSDConfig->c90flRegBase , blkLockIndicator,shadowLockPrimary, blkLockEnabled, blkLockState );
    }
    else if (LOCK_SHADOW1_PRIMARY == blkLockIndicator || LOCK_SHADOW1_SECONDARY == blkLockIndicator)
    {
	    if(LOCK_SHADOW1_PRIMARY == blkLockIndicator)
	    {
	       shadowLockPrimary = TRUE;
	    }
        /* Get Lock status for shadow row of BANK0 */
        returnCode = CgetLock((pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET) , blkLockIndicator,shadowLockPrimary, blkLockEnabled, blkLockState );
    }
    else if (LOCK_LOW_PRIMARY == blkLockIndicator || LOCK_LOW_SECONDARY == blkLockIndicator)
    {
        /* Get Lock status for LAS of BANK0 (LAS for user)*/
        returnCode = CgetLock( pSSDConfig->c90flRegBase, blkLockIndicator,shadowLockPrimary,blkLockEnabled,&blkLockStateTemp);
   
	*blkLockState = blkLockStateTemp;

        if(LOCK_LOW_PRIMARY == blkLockIndicator)
        {
			blkLockIndicatorTemp = LOCK_MID_PRIMARY;
		}
		else
		{
			blkLockIndicatorTemp = LOCK_MID_SECONDARY ;
		}

        /* Get Lock status for MAS of BANK0 (LAS for user)*/
        returnCode = CgetLock( pSSDConfig->c90flRegBase, blkLockIndicatorTemp,shadowLockPrimary, blkLockEnabled, &blkLockStateTemp);

	/* Get the block lock state of LAS to be returned to user*/
        *blkLockState |=(blkLockStateTemp << lowBlockNumberBk0);
    }
    else if (LOCK_MID_PRIMARY == blkLockIndicator || LOCK_MID_SECONDARY == blkLockIndicator)
    {
         if(LOCK_MID_PRIMARY == blkLockIndicator)
        {
			blkLockIndicatorTemp = LOCK_LOW_PRIMARY;
		}
		else
		{
			blkLockIndicatorTemp = LOCK_LOW_SECONDARY ;
		}
        /* Get Lock status for LAS of BANK1 (MAS for user)*/
        returnCode = CgetLock( (pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET) , blkLockIndicatorTemp,shadowLockPrimary,blkLockEnabled,&blkLockStateTemp );

	/* Calculate mask of available bits in LAS of BANK1*/
	mask = 0;
	for (i = 0; i < lowBlockNumberBk1; i++)
	{
	    mask |= (1 << i);
	}
	*blkLockState = blkLockStateTemp & mask;

        /* Get Lock status for logic MAS of BANK1 (MAS for user)*/
        returnCode = CgetLock( (pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET) , blkLockIndicator,shadowLockPrimary,blkLockEnabled,&blkLockStateTemp);

	/* Calculate mask of available bits in logic MAS of BANK1*/
	mask = 0;
	for (i = 0; i <(pSSDConfig->midBlockNum - lowBlockNumberBk1); i++)
	{
	    mask |= (1 << i);
	}
	blkLockStateTemp &= mask;
        /* Get the block lock state of LAS to be returned to user*/
        *blkLockState |= (blkLockStateTemp << lowBlockNumberBk1);
    }
    else if (LOCK_HIGH == blkLockIndicator)
    {
        /* Get Lock status for HAS of BANK0 (HAS for user)*/
        returnCode = CgetLock(pSSDConfig->c90flRegBase, blkLockIndicator,shadowLockPrimary,&blkLockEnabledTemp,&blkLockStateTemp);
        *blkLockEnabled = blkLockEnabledTemp;
        *blkLockState = blkLockStateTemp;

        /* Get Lock status for HAS of BANK0 (HAS for user)*/
        returnCode = CgetLock( (pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET) , blkLockIndicator,shadowLockPrimary,&blkLockEnabledTemp,&blkLockStateTemp);
        /* If block lock is disabled in any BANK return lockstatus as FALSE*/
        *blkLockEnabled &= blkLockEnabledTemp;
        /* If one block is locked in any bank return lock as set(1)*/
        *blkLockState |= blkLockStateTemp;
	
    }
    else
    {
        /*do nothing*/
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

