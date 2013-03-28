 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Standard Software Driver for C90fl                      *
 *                                                                       *
 * FILE NAME     :  factorymarginreadcheck.c                             *
 * FUNCTION      :  FactoryMarginReadCheck                               *
 * DESCRIPTION   :  This function will will check the array integrity    *
 *                  of the Flash                                         *
 * PARAMETERS    :                                                       *
 *                 pSSDConfig - Flash driver configuration structure     *
 *                 lowEnabledBlocks - selected Low Address Space block(s)*
 *                 midEnabledBlocks - selected Mid Address Space block(s)*
 *                 highEnabledBlocks    - selected High Address Space    *
 *                  block(s)                                             *
 *                 marginLevel - to determine the margin level to be     *
 *                  used during margin reads of array integrity checks.  *
 *                 misrValue_Bk0 - contains the MISR values calculated   *
 *                  by the user for Bank 0.                              *
 *                 misrValue_Bk0 - contains the MISR values calculated   *
 *                  by the user for Bank 0..                             *
 *                 CallBack  - Callback function pointer for timeout     *
 *                 checking.                                             *
 * RETURN VALUES : C90FL_OK          - Array Integrity Check passes      *
 *                 C90FL_ERROR_MISR_NO_BLOCK - No block enable for Array *
 *                 Integrity Check                                       *
 *                 C90FL_ERROR_MISR_MISMATCH - Array Integrity Check     *
 *                  fails                                                *
 * DATE          :  December 22, 2008                                    *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   12.22.2008         Arvind Awasthi      Initial Version
 0.4.4	 07.27.2010         FPT Team 		    Finalize to this version
 *************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"

#if (DIAB_COMPILER == COMPILER_SELECT)
asm void write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif

UINT32 ssd_c90fl_FactoryMarginReadCheck ( PSSD_CONFIG pSSDConfig,
                                UINT32 lowEnabledBlocks,
                                UINT32 midEnabledBlocks,
                                UINT32 highEnabledBlocks,
                                BOOL marginLevel,
                                MISR misrValue_Bk0,
                                MISR misrValue_Bk1,
                                void (*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 c90flRegBase;            /* base address of C90FL registers */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    MISR misrCalcValue_Bk0;         /* store contents of the hardware calculated MISR for Bank0 */
    MISR misrCalcValue_Bk1;         /* store contents of the hardware calculated MISR for Bank1 */
    UINT32 UT0Address;              /* Address of the UT0 register */
    UINT32 cLowEnabledBlocks;       /* Low blocks in respective banks */
    UINT32 cMidEnabledBlocks;       /* Mid blocks in respective banks */
    UINT32 tempBlocks;              /* Temp variable to keep track number of blocks in each bank */
    UINT32 temp;                    /* Temp Variable to store MAS blocks of the two banks*/
    UINT8  bkFlag;                  /* Flag for tracking the bank for which AIC is going on 01-Bank0;02-Bank1*/


    bkFlag = 0x0;

    /* initialize returnCode */
    returnCode = C90FL_OK;

    if (!((lowEnabledBlocks | highEnabledBlocks)|midEnabledBlocks))
    {
        /* no blocks to be selected for evaluation */
        returnCode = C90FL_ERROR_FMR_NO_BLOCK;
        goto EXIT;
    }

    /*************************** Bk0 Check******************************/

    if (0 != (lowEnabledBlocks | highEnabledBlocks))
    {
	   c90flRegBase = pSSDConfig->c90flRegBase;
	   MCRAddress = c90flRegBase + C90FL_MCR;
       MCRValue = C90FL_REG_READ (MCRAddress);

	   /* Determine the number of blocks in middle address space in BANK0*/
       if ( MCRValue & C90FL_MCR_MAS)
       {
	      temp = 1;
       }
	   else
	   {
	      temp = 2;
	   }

       /* Get the Low Blocks of Bk0 */
       tempBlocks = pSSDConfig->lowBlockNum - temp;

       /* mask off reserved bits for low address space in Bk0 */
       cLowEnabledBlocks = (lowEnabledBlocks & (0xFFFFFFFF >> (32 - tempBlocks)));

       /* mask off reserved bits for mid address space in Bk0 */
       cMidEnabledBlocks = (lowEnabledBlocks  >> tempBlocks);

       /* mask off reserved bits for mid address space in Bk0 */
       cLowEnabledBlocks |= (cMidEnabledBlocks & (0xFFFFFFFF >> (32 - temp))) << 16;

       /* mask off reserved bits for high address space */
       highEnabledBlocks &= 0xFFFFFFFF >> (32 - pSSDConfig->highBlockNum);

       /* call common cFlashArrayIntegrityCheck for Bk0*/
       returnCode = CFactoryMarginReadCheck(c90flRegBase,cLowEnabledBlocks,highEnabledBlocks,marginLevel);
       bkFlag |=0x01;
   }

   /*************************** Bk0 Check - End******************************/

   /*************************** Bk1 Check************************************/
    /*Is the block in MAS or HAS*/
	if (0 != (midEnabledBlocks | highEnabledBlocks))
	{
        c90flRegBase = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET;
        MCRAddress = c90flRegBase + C90FL_MCR;
        MCRValue = C90FL_REG_READ (MCRAddress);
        /* Determine the number of blocks in middle address space in BANK0*/
		if ( MCRValue & C90FL_MCR_MAS)
		{
		   temp = 1;
		}
		else
	    {
		   temp = 2;
	    }

	    /* Get the Low Blocks in Bk0 */
	    tempBlocks = pSSDConfig->midBlockNum - temp;

	    /* mask off reserved bits for low address space Bk1 */
		cLowEnabledBlocks = (midEnabledBlocks & (0xFFFFFFFF >> (32 - tempBlocks)));
		/* mask off reserved bits for mid address space Bk1 */
        cMidEnabledBlocks = (midEnabledBlocks >> tempBlocks);
        /* mask off reserved bits for mid address space in Bk0 */
        cLowEnabledBlocks |= (cMidEnabledBlocks & (0xFFFFFFFF >> (32 - temp))) << 16;
        /* mask off reserved bits for high address space */
        highEnabledBlocks &= 0xFFFFFFFF >> (32 - pSSDConfig->highBlockNum);

        /* call common cFlashArrayIntegrityCheck for Bk1*/
        returnCode = CFactoryMarginReadCheck(c90flRegBase,cLowEnabledBlocks,highEnabledBlocks,marginLevel);
        bkFlag |=0x02;
	}
    /*************************** Bk1 Check - End******************************/

    /* check for AIC in Bank0*/
    if(bkFlag & 0x01)
    {
        c90flRegBase = pSSDConfig->c90flRegBase;
        UT0Address = c90flRegBase + C90FL_UT0;
       /* wait until UT0-AID is set */
        while ( !(C90FL_REG_READ (UT0Address) & C90FL_UT0_AID) )
        {
           if (CallBack != NULL_CALLBACK)
           {
              CallBack();
           }
        }

        misrCalcValue_Bk0.W0 = C90FL_REG_READ(c90flRegBase + C90FL_UM0);
        misrCalcValue_Bk0.W1 = C90FL_REG_READ(c90flRegBase + C90FL_UM1);
        misrCalcValue_Bk0.W2 = C90FL_REG_READ(c90flRegBase + C90FL_UM2);
        misrCalcValue_Bk0.W3 = C90FL_REG_READ(c90flRegBase + C90FL_UM3);
        misrCalcValue_Bk0.W4 = C90FL_REG_READ(c90flRegBase + C90FL_UM4);

        if( (misrCalcValue_Bk0.W0 != misrValue_Bk0.W0) || (misrCalcValue_Bk0.W1 != misrValue_Bk0.W1)
             || (misrCalcValue_Bk0.W2 != misrValue_Bk0.W2) || (misrCalcValue_Bk0.W3 != misrValue_Bk0.W3)
             || (misrCalcValue_Bk0.W4 != misrValue_Bk0.W4) )
        {
            /* set the returned value to an error code */
            returnCode |= C90FL_ERROR_FMR_MISMATCH;
        }

        /* clear UTO-AIE bit */
        C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_AIE);

        /* clear UTO-UTE bit to disable User Test Mode */
        C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_UTE);
        /* clear bank0 flag*/
		bkFlag &= ~(0x01);
	}

    /* check for AIC in Bank1*/
    if(bkFlag & 0x02)
    {
        c90flRegBase = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET;
        UT0Address = c90flRegBase + C90FL_UT0;
       /* wait until UT0-AID is set */
        while ( !(C90FL_REG_READ (UT0Address) & C90FL_UT0_AID) )
        {
           if (CallBack != NULL_CALLBACK)
           {
              CallBack();
           }
        }

        misrCalcValue_Bk1.W0 = C90FL_REG_READ(c90flRegBase + C90FL_UM0);
        misrCalcValue_Bk1.W1 = C90FL_REG_READ(c90flRegBase + C90FL_UM1);
        misrCalcValue_Bk1.W2 = C90FL_REG_READ(c90flRegBase + C90FL_UM2);
        misrCalcValue_Bk1.W3 = C90FL_REG_READ(c90flRegBase + C90FL_UM3);
        misrCalcValue_Bk1.W4 = C90FL_REG_READ(c90flRegBase + C90FL_UM4);

        if( (misrCalcValue_Bk1.W0 != misrValue_Bk1.W0) || (misrCalcValue_Bk1.W1 != misrValue_Bk1.W1)
             || (misrCalcValue_Bk1.W2 != misrValue_Bk1.W2) || (misrCalcValue_Bk1.W3 != misrValue_Bk1.W3)
             || (misrCalcValue_Bk1.W4 != misrValue_Bk1.W4) )
        {
            /* set the returned value to an error code */
            returnCode |= C90FL_ERROR_FMR_MISMATCH;
        }

        /* clear UTO-AIE bit */
        C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_AIE);

        /* clear UTO-UTE bit to disable User Test Mode */
        C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_UTE);
        /* clear bank1 flag*/
		bkFlag &= ~(0x02);
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
