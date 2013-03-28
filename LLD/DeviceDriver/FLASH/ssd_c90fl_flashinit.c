 /************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2009, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
  *                                                                      *
  *               Wrapper Standard Software Driver for C90fl             *
  *                                                                      *
  * FILE NAME     : flashinit.c                                          *
  * FUNCTION      : FlashInit                                            *
  * DESCRIPTION   : This function will initialize the flash config       *
  *                 structure.                                           *
  * PARAMETERS    :                                                      *
  *                 pSSDConfig - Flash driver configuration structure    *
  *                                                                      *
  * RETURN        : C90FL_OK           - passes                          *
  *                 C90FL_ERROR_RANGE  - Invalid addr range              *
  *                 C90FL_ERROR_ALIGNMENT - Invalid alignment            *
  * DATE          : September 11, 2008                                   *
  * AUTHOR        : Infosys Team                                         *
  * E-mail        : r56611@freescale.com                                 *
  *                                                                      *
  *************************************************************************/

/******************************* CHANGES *********************************
  0.0.0   09.11.2008         Arvind Awasthi       Initial Version
  0.0.1   12.17.2008         Arvind Awasthi	    Adresses of BANKS made
                                                relative to main array
                                                base
  0.4.4	  07.27.2010         FPT Team 		    Finalize to this version											
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

UINT32 ssd_c90fl_FlashInit ( PSSD_CONFIG pSSDConfig )
{
    register UINT32 returnCode;    /* return code */
    SSD_CONFIG ssdConfigBk;          /* Local ssdconfig to be passed to underlying driver */

    /* set return code to 0 initially*/
    returnCode = C90FL_OK;


    /* Store BANK0 parameters in local SSDConfig structure*/
    ssdConfigBk.c90flRegBase  = pSSDConfig->c90flRegBase;
    ssdConfigBk.mainArrayBase = pSSDConfig->mainArrayBase;
    ssdConfigBk.mainArraySize = pSSDConfig->mainArraySize;
    ssdConfigBk.shadowRowBase = pSSDConfig->shadowRowBase + SHADOW_ROW_BANK0_OFFSET;
    ssdConfigBk.shadowRowSize = SHADOW_ROW_BANK0_SIZE;
    ssdConfigBk.lowBlockNum   = pSSDConfig->lowBlockNum;
    ssdConfigBk.midBlockNum   = pSSDConfig->midBlockNum;
    ssdConfigBk.highBlockNum  = pSSDConfig->highBlockNum;
    ssdConfigBk.pageSize      = pSSDConfig->pageSize;
    ssdConfigBk.BDMEnable     = pSSDConfig->BDMEnable;

    /* call low level driver with the SSDConfig for BANK0 */
    returnCode |= CflashInit(&ssdConfigBk);

    /* LAS blocks to be returned to the user*/
    /* For user: LAS Blocks = BANK0 LAS Blocks + BANK0 MAS Blocks*/
    pSSDConfig->lowBlockNum = ssdConfigBk.lowBlockNum + ssdConfigBk.midBlockNum;
    /* Add main array size of BANK0 to pSSDConfig->mainArraySize */
    pSSDConfig->mainArraySize = ssdConfigBk.mainArraySize;

    /* Store BANK1 parameters in local SSDConfig structure*/
	ssdConfigBk.c90flRegBase  = pSSDConfig->c90flRegBase + BANK1_REG_BASEOFFSET;
	ssdConfigBk.mainArrayBase = pSSDConfig->mainArrayBase + C90FL_MAS_STARTADDR;
	ssdConfigBk.mainArraySize = 0;
	ssdConfigBk.shadowRowBase = pSSDConfig->shadowRowBase - SHADOW_ROW_BANK1_OFFSET;
	ssdConfigBk.shadowRowSize  = SHADOW_ROW_BANK1_SIZE;
	ssdConfigBk.lowBlockNum   = 0;
	ssdConfigBk.midBlockNum   = 0;
	ssdConfigBk.highBlockNum  = 0;
	ssdConfigBk.pageSize      = pSSDConfig->pageSize;
    ssdConfigBk.BDMEnable     = pSSDConfig->BDMEnable;

	/* call low level driver with the SSDConfig for BANK0 */
	returnCode |= CflashInit(&ssdConfigBk);

	/* MAS blocks to be returned to the user*/
	/* For user: MAS Blocks = BANK1 LAS Blocks + BANK1 MAS Blocks*/
    pSSDConfig->midBlockNum = ssdConfigBk.lowBlockNum + ssdConfigBk.midBlockNum;

    /* Total HAS blocks for user are same as the number of HAS blocks in each Bank */
    /* NOTE: Since the HAS blocks are interleaved;*/
    /* Size of one HAS block for the user = Number of banks x Size of one HAS block in any bank*/
    pSSDConfig->highBlockNum = ssdConfigBk.highBlockNum;

    /* Size of the main array is sum of the sizes of main array of the two banks*/
    pSSDConfig->mainArraySize += ssdConfigBk.mainArraySize;

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

