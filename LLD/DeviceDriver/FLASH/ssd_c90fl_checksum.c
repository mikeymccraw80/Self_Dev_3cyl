 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Wrapper Standard Software Driver for C90fl(2)           *
 *                                                                       *
 * FILE NAME     :  ssd_c90fl_CheckSum.c                                           *
 * FUNCTION      :  ssd_c90fl_CheckSum                                             *
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
 * DATE          : September 16, 2008                                    *
 * AUTHOR        : Infosys Team                                          *
 * E-mail        : r56611@freescale.com                                  *
 *                                                                       *
 *************************************************************************/

 /******************************* CHANGES *********************************
  0.0.0   09.16.2008       Arvind Awasthi      Initial Version
  0.4.4	  07.27.2010	   FPT Team 		   Finalize to this version
  0.4.8	  05.05.2011	   FPT Team		       Add CallBack input to CcheckSum
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

UINT32 ssd_c90fl_CheckSum ( PSSD_CONFIG pSSDConfig,
                  UINT32 dest,
                  UINT32 size,
                  UINT32 *pSum,
                  void(*CallBack)(void))
{
    register UINT32 returnCode;     /* return code */
    UINT32 shadowRowEnd;            /* shadow row base + shadow size */
    UINT32 shadowRowEnd_bk1;        /* shadow row base + shadow size - module B*/
    UINT32 mainArrayEnd;            /* main array base + main array size */
    UINT32 endAddress;              /* dest + size*/

    returnCode = C90FL_OK;

    /* The flash range falls within either main array or shadow row */
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

    /* call underlying flash driver with correct destination and size*/
    returnCode = CcheckSum(dest,size,pSum,CallBack);



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
