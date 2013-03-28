 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Standard Software Driver for C90fl                      *
 *                                                                       *
 * FILE NAME     :  cFlashArrayIntegrityCheck.c                          *
 * FUNCTION      :  cFlashArrayIntegrityCheck                            *
 * DESCRIPTION   :  This function will will check the array integrity    *
 *                    of the Flash                                       *
 * PARAMETERS    :                                                       *
 *                 c90flRegBase - Register base of Flash module          *
 *                 lowEnabledBlocks - selected Low Address Space block(s)*
 *                 midEnabledBlocks - selected Mid Address Space block(s)*
 *                 highEnabledBlocks    - selected High Address Space    *
 *                  block(s)                                             *
 *                 addrSeq - to determine the address sequence to be     *
 *                  used during array integrity checks.                  *
 *                 misrValue - contains the MISR values calculated       *
 *                  by the user.                                         *
 *                 CallBack  - Callback function pointer for timeout     *
 *                 checking.                                             *
 * RETURN VALUES : C90FL_OK          - Array Integrity Check passes      *
 *                 C90FL_ERROR_MISR_NO_BLOCK - No block enable for Array *
 *                  Integrity Check                                      *
 *                 C90FL_ERROR_MISR_MISMATCH - Array Integrity Check     *
 *                  fails                                                *
 * DATE          :  December 22, 2008                                    *
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

 UINT32 CFlashArrayIntegrityCheck(UINT32 c90flRegBase,
                                   UINT32 lowEnabledBlocks,
                                   UINT32 highEnabledBlocks,
                                   BOOL addrSeq)
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

     /* set the Address sequence to be used */
     if( C90FL_LOG_SEQ == addrSeq)
     {
         /* the logical sequence is used */
         C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_AIS);
     }
     else
     {
         /* the default sequence is used */
     }

     /* set the seed values of the MISR in UMx registers */
     C90FL_REG_WRITE(c90flRegBase + C90FL_UM0, 0);
     C90FL_REG_WRITE(c90flRegBase + C90FL_UM1, 0);
     C90FL_REG_WRITE(c90flRegBase + C90FL_UM2, 0);
     C90FL_REG_WRITE(c90flRegBase + C90FL_UM3, 0);
     C90FL_REG_WRITE(c90flRegBase + C90FL_UM4, 0);

     /* initiate the Array Integrity Check by wirting 1 to Ut0_AIE bit*/
     C90FL_REG_BIT_SET (UT0Address , C90FL_UT0_AIE);

     return returnCode;

}