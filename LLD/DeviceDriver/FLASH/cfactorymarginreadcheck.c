 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Standard Software Driver for C90fl                    *
 *                                                                       *
 * FILE NAME     :  cfactorymarginreadcheck.c                            *
 * FUNCTION      :  cFactoryMarginReadCheck                              *
 * DESCRIPTION   :  This function will will check the array integrity    *
 *                    of the Flash                                       *
 * PARAMETERS    :                                                       *
 *                 c90flRegBase - Register base of Flash module          *
 *                 lowEnabledBlocks - selected Low Address Space block(s)*
 *                 highEnabledBlocks    - selected High Address Space    *
 *                  block(s)                                             *
 *                 marginLevel - to determine the margin level to be     *
 *                  used during margin reads of array integrity checks.  *
 * RETURN VALUES : C90FL_OK - All operations are done as expected        *
 * DATE          :  January 29, 2009                                     *
 * AUTHOR        :  Infosys Team                                         *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
 0.0.0   2008.12.22         Arvind Awasthi      Initial Version
 0.4.4	 2010.07.27         FPT Team 		    Finalize to this version
 *************************************************************************/

#include "ssd_types.h"
#include "ssd_c90fl.h"

 UINT32 CFactoryMarginReadCheck   (UINT32 c90flRegBase,
                                   UINT32 lowEnabledBlocks,
                                   UINT32 highEnabledBlocks,
                                   BOOL marginLevel)
 {
     register UINT32 returnCode;     /* return code */
     UINT32 LMSAddress;              /* address of C90FLLMS register */
     UINT32 UT0Address;              /* Address of the UT0 register */

     LMSAddress = c90flRegBase + C90FL_LMS;
     UT0Address = c90flRegBase + C90FL_UT0;

     /* initialize returnCode */
     returnCode = C90FL_OK;

    /* write password to UT0 register to enable test mode */
    C90FL_REG_WRITE(c90flRegBase + C90FL_UT0,C90FL_TEST_ENABLE_PASSWORD);

    /* set the block selection registers */
    C90FL_REG_WRITE (LMSAddress, lowEnabledBlocks);
    C90FL_REG_WRITE (c90flRegBase + C90FL_HBS, highEnabledBlocks);

    /* set UT0_MRE to enable Factory Margin Read */
    C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_MRE);

    /* set the Margin level to be used */
    if( C90FL_FMR_ERASED_LEVEL == marginLevel)
    {
        /* the erase level is used */
        C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_MRV);
    }
    else
    {
        /* the programmed level is used */
        C90FL_REG_BIT_CLEAR (UT0Address , C90FL_UT0_MRV);
    }

    /* set the seed values of the MISR in UMx registers */
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM0, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM1, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM2, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM3, 0);
    C90FL_REG_WRITE(c90flRegBase + C90FL_UM4, 0);

    /* initiate the Factory Margin Read Check by wirting 1 to UT0_AIE bit*/
    C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_AIE);

    return returnCode;

}