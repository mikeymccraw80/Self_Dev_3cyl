/************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl              *
 *                                                                       *
 * FILE NAME     :  setlock.c                                            *
 * FUNCTION      :  SetLock                                              *
 * DESCRIPTION   :  This function will set the block lock state for      *
 *                  Shadow/Low/Middle/High address space on the C90FL    *
 *                  module to protect them from program/erase.           *
 * PARAMETERS    :                                                       *
 *                  pSSDConfig - Flash driver configuration structure    *
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
  0.0.0   09.17.2008        Arvind Awasthi    Initial Version
  0.0.1   11.06.2008	    Chen He	          corrected bug in checking
  blkLockStateTemp
  0.0.2   12.17.2008        Arvind Awasthi    Optimized code to generate
  binaries in Diab compiler.
  0.4.4	  07.27.2010	    FPT Team 		  Finalize to this version	
  0.4.6   01.11.2011        FPT Team          Finalize to this version
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


UINT32 ssd_c90fl_SetLock ( PSSD_CONFIG pSSDConfig,
      UINT8 blkLockIndicator,
      UINT32 blkLockState,
      UINT32 password)
{
   register UINT32 returnCode;    /* return code */
   UINT32 mask;                   /* block locking field mask of an address space */
   UINT32 blkLockStateTemp;       /* local variable used to pass block lock state to underlying driver*/
   UINT32 MCRAddress;             /* address of C90FLMCR register */
   UINT32 MCRValue;               /* content of C90FLMCR register */
   UINT32 lowBlockNumberBk0;      /* Temporary variable to store Low blocks of BANK0 */
   UINT32 lowBlockNumberBk1;      /* Temporary variable to store Low blocks of BANK1 */
   BOOL   shadowLockPrimary;      /* variable passed to common driver TRUE: When shadow lock primary is enabled*/
   UINT8  blkLockIndicatorTemp;

   if (blkLockIndicator > LOCK_HIGH)
   {
      returnCode = C90FL_ERROR_LOCK_INDICATOR;
      goto EXIT;
   }

   shadowLockPrimary = FALSE;
   returnCode = C90FL_OK;
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
   MCRAddress = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET + C90FL_MCR;
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
   lowBlockNumberBk1 = pSSDConfig->midBlockNum - mask;

   if( LOCK_SHADOW0_PRIMARY == blkLockIndicator || LOCK_SHADOW0_SECONDARY == blkLockIndicator )
   {
      if(LOCK_SHADOW0_PRIMARY == blkLockIndicator)
      {
         shadowLockPrimary = TRUE;
      }
      returnCode = CsetLock(pSSDConfig->c90flRegBase , blkLockIndicator,shadowLockPrimary, blkLockState,password );
   }
   else if( LOCK_SHADOW1_PRIMARY == blkLockIndicator || LOCK_SHADOW1_SECONDARY == blkLockIndicator)
   {
      if(LOCK_SHADOW1_PRIMARY == blkLockIndicator)
      {
         shadowLockPrimary = TRUE;
      }
      returnCode = CsetLock((pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET), blkLockIndicator,shadowLockPrimary, blkLockState,password );
   }
   else if (LOCK_LOW_PRIMARY == blkLockIndicator || LOCK_LOW_SECONDARY == blkLockIndicator)
   {
      /* Lock the blocks in LAS of BANK0 */
      /* get the LAS blocks to be locked in BANK0*/
      blkLockStateTemp = (blkLockState & (0xFFFFFFFF >> (32 - lowBlockNumberBk0)) );
      returnCode = CsetLock( pSSDConfig->c90flRegBase, blkLockIndicator,shadowLockPrimary, blkLockStateTemp, password );

      if(LOCK_LOW_PRIMARY == blkLockIndicator)
      {
         blkLockIndicatorTemp = LOCK_MID_PRIMARY;
      }
      else
      {
         blkLockIndicatorTemp = LOCK_MID_SECONDARY ;
      }
      /* Lock the blocks in MAS of BANK0 (LAS for user) */
      /* get the MAS blocks to be locked in BANK0*/
      blkLockStateTemp = (blkLockState >> lowBlockNumberBk0);
      returnCode |= CsetLock( pSSDConfig->c90flRegBase, blkLockIndicatorTemp,shadowLockPrimary, blkLockStateTemp, password );
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
      /* Lock the blocks in MAS */
      /* get the LAS blocks to be locked in BANK1 (MAS for user*/
      blkLockStateTemp = (blkLockState & (0xFFFFFFFF >> (32 - lowBlockNumberBk1)) );
      returnCode = CsetLock( (pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET), blkLockIndicatorTemp,shadowLockPrimary, blkLockStateTemp, password );

      /* Lock the blocks in MAS of BANK1 (MAS for user) */
      /* get the MAS blocks to be locked in BANK1*/
      blkLockStateTemp = (blkLockState >> lowBlockNumberBk1);
      returnCode |= CsetLock( (pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET), blkLockIndicator,shadowLockPrimary, blkLockStateTemp, password );
   }
   else if (LOCK_HIGH == blkLockIndicator)
   {
      /* Lock HAS blocks of BANK0*/
      returnCode = CsetLock( pSSDConfig->c90flRegBase, blkLockIndicator,shadowLockPrimary, blkLockState, password );
      /* Lock HAS blocks of BANK1*/
      returnCode |= CsetLock( (pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET), blkLockIndicator,shadowLockPrimary, blkLockState, password );
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


