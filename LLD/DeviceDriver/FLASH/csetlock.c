 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Common Standard Software Driver for C90fl               *
 *                                                                       *
 * FILE NAME     :  csetlock.c                                           *
 * FUNCTION      :  CsetLock                                             *
 * DESCRIPTION   :  This function will set the block lock state for      *
 *                  Shadow/Low/Middle/High address space on the C90FL    *
 *                  module to protect them from program/erase.           *
 * PARAMETERS    :                                                       *
 *                  regsisterBase: Base address of MCR register for the  *
 *                  respective bank                                      *
 *                  blkLockIndicator - variable for storing block lock   *
 *                                    indicator value                    *
 *                  blkLockState - variable for storing block lock state *
 *                                 value                                 *
 *                 password - Variable for storing password              *
 * RETURN        : C90FL_OK - passes                                     *
 *                 C90FL_ERROR_LOCK_INDICATOR - wrong indicator value    *
 *                 C90FL_ERROR_PASSWORD - incorrect password             *
 * DATE          : September 17, 2008                                    *
 * AUTHOR        : Infosys Team                                          *
 * E-mail        : r56611@freescale.com                                  *
 *                                                                       *
 *************************************************************************/

 /******************************* CHANGES *********************************
  0.0.0   09.17.2008         Arvind Awasthi      Initial Version
  0.4.4	  07.27.2010         FPT Team 		     Finalize to this version
 *************************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90fl.h"


UINT32 CsetLock (UINT32 registerBase,
                 UINT8 blkLockIndicator,
                 BOOL  shadowLockPrimary,
                 UINT32 blkLockState,
                 UINT32 password)
{
    register UINT32 returnCode;    /* return code */
    UINT32 address;                /* address of the block locking register */
    UINT32 mask;                   /* block locking field mask of an address space */
    UINT32 shift;                  /* bit shift value for the block locking field of an address space */

    returnCode = C90FL_OK;

    /* assume blkLockIndicator == LOCK_SHADOW_PRIMARY */
    address = C90FL_LML;
    mask = C90FL_LML_SLOCK;
    shift = 20;

    if (LOCK_LOW_PRIMARY == blkLockIndicator)
    {
        mask = C90FL_LML_LLOCK;
        shift = 0;
    }
    else if (LOCK_MID_PRIMARY == blkLockIndicator)
    {
        mask = C90FL_LML_MLOCK;
        shift = 16;
    }
    else if (FALSE == shadowLockPrimary)
    {
        /* assume blkLockIndicator == LOCK_SHADOW_SECONDARY */
        address = C90FL_SLL;

        if (LOCK_LOW_SECONDARY == blkLockIndicator)
        {
            mask = C90FL_SLL_SLLOCK;
            shift = 0;
        }
        else if (LOCK_MID_SECONDARY == blkLockIndicator)
        {
            mask = C90FL_SLL_SMLOCK;
            shift = 16;
        }
        else if (LOCK_HIGH == blkLockIndicator)
        {
            address = C90FL_HBL;
            mask = C90FL_HBL_HBLOCK;
            shift = 0;
        }
    }
    else
    {
		/*do nothing*/
	}

    address += registerBase;

    /* write password to block lock register if it's locked for register writes */
    if (!C90FL_REG_BIT_TEST (address, 0x80000000))
    {
        /* write user provided password to block lock register */
        C90FL_REG_WRITE (address, password);

        /* check if the block lock register is enabled for register writes after writing password */
        if (!C90FL_REG_BIT_TEST (address, 0x80000000))
        {
            returnCode = C90FL_ERROR_PASSWORD;
            goto EXIT;
        }
    }

    /* clear the block lock field */
    C90FL_REG_BIT_CLEAR (address, mask);

    /* set the new value to the block lock field */
    C90FL_REG_BIT_SET (address, (blkLockState << shift) & mask);
EXIT:
    return returnCode;
}
