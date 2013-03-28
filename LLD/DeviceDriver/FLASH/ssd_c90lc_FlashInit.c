/*****************************************************************
* PROJECT : Standard Software Driver (SSD) for M10ST based devices
* FILE    : FlashInit.c
*
* DESCRIPTION : This function will read the flash configuration information
*               from the flash control registers and initialize parameters
*               in SSD configuration structure
*
* COPYRIGHT :(c) 2009, Freescale & STMicroelectronics
*
* VERSION   : Beta 1.0
* DATE      : 10.26.2009
* AUTHOR    : ...
*
* HISTORY :
* 2007.12.10    Arvind Awasthi    Initial Version for JPC563M target
* 2008.01.03				Chen He			        HAS blk size changed from 128KB to 256KB
* 2008.03.28				Leonardo Colombo		Porting for SPC560B CFLASH
* 2008.04.18    Leonardo Colombo  SPC560B SPC560P CFLASH DFLASH management
* 2008.08.29    Leonardo Colombo  SPC560B SPC560P CFLASH DFLASH management
*                                 SPC560S CFLASH0 CFLASH1 DFLASH management
* 2009.01.28				Leonardo Colombo		Porting for xPC563M64 devices (C0, C1, C2)
* 2009.04.08			 Leonardo Colombo		Porting for xPC560B64 devices (C MM, D)
* 2009.10.26		 	   Leonardo Colombo		"Unified" version supporting all targets with LC flash
******************************************************************/

#include    "ssd_types.h"
#include    "ssd_c90lc.h"


/*******************************************************************
| external declarations
|------------------------------------------------------------------*/

/*******************************************************************
| defines and macros (scope: module-local)
|------------------------------------------------------------------*/
#define CFLASH_BASE_ADDR   (UINT32)(0xC3F88000)
#define DFLASH_BASE_ADDR   (UINT32)(0xC3F8C000)
#define C1_BASE_ADDR       (UINT32)(0xC3FB0000)
#define C2_BASE_ADDR       (UINT32)(0xC3FB4000)

/*******************************************************************
| typedefs and structures (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| global variable definitions (scope: module-exported)
|------------------------------------------------------------------*/

/*******************************************************************
| global variable definitions (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function prototypes (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function implementations (scope: module-local)
|------------------------------------------------------------------*/

/*******************************************************************
| function implementations (scope: module-exported)
|------------------------------------------------------------------*/

UINT32 ssd_c90lc_FlashInit ( PSSD_CONFIG pSSDConfig )
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRAddress;              /* address of C90FLMCR register */
    UINT32 MCRValue;                /* content of C90FLMCR register */
    UINT32 temp;                    /* temporary variable */

    MCRAddress = pSSDConfig->c90flRegBase + C90FL_MCR;
    MCRValue = C90FL_REG_READ (MCRAddress);

    returnCode = C90FL_OK;

    /* Check MCR-EER and MCR-RWE bits */
    returnCode = (MCRValue & (C90FL_MCR_EER|C90FL_MCR_RWE)) >> 14;
    if (returnCode)
    {
        /* Clear EER and RWE bits are set in MCR register */
        C90FL_REG_BIT_SET(MCRAddress,(C90FL_MCR_EER|C90FL_MCR_RWE));
    }

    pSSDConfig->lowBlockNum = 0;
    pSSDConfig->midBlockNum = 0;
    pSSDConfig->highBlockNum = 0;

    /* Number of blocks in low address space and fill into SSD_CONFIG structure */
    temp = (MCRValue & C90FL_MCR_LAS) >> 20;

    /**************************************************************************
    *  Number of blocks in low address space and fill into SSD_CONFIG structure
    *  LAS = 0: lowBlockNum = 0;        Sectorization = 0
    *  LAS = 1: lowBlockNum = 2;        Sectorization = 2x128K
    *  LAS = 2: lowBlockNum = 6;        Sectorization = 32K+2x16K+2x32K+128K
	   *  LAS = 3: lowBlockNum = Res;      Sectorization = n.a
    *  LAS = 4: lowBlockNum = Res;      Sectorization = n.a
	   *  LAS = 5: lowBlockNum = Res;      Sectorization = n.a
	   *  LAS = 6: lowBlockNum = 4;        Sectorization = 4x16K
	   *  LAS = 7: lowBlockNum = 8;        Sectorization = 2x16K+2x32K+2x16K+2x64K
	   **************************************************************************/
    switch(temp)
    {
           case 1:
                pSSDConfig->lowBlockNum = 2;
           break;
           case 2:
                pSSDConfig->lowBlockNum = 6;
           break;
           case 6:
                pSSDConfig->lowBlockNum = 4;
           break;
           case 7:
                pSSDConfig->lowBlockNum = 8;
           break;
    }

	   /* Find main array size and fill into SSD_CONFIG structure */
	   temp = (MCRValue & C90FL_MCR_SIZE) >> 24;

	   /**************************************************************************
	   *  Get Main array size and fill into SSD_CONFIG structure
	   *  Size = 0: Main Array Size = 128KB;
	   *  Size = 1: Main Array Size = 256KB;
	   *  Size = 2: Main Array Size = 512KB;
	   *  Size = 3: Main Array Size = 1MB;
	   *  Size = 4: Main Array Size = 1.5MB;
	   *  Size = 5: Main Array Size = 2MB;
	   *  Size = 6: Main Array Size = 64KB;
	   *  Size = 7: Main Array Size = Reserved;
	   **************************************************************************/
    switch(temp)
	   {
    /*  case 0:
	        temp = 0x20000;
	        break;*/
	     case 1:
	        temp = 0x40000;
	        break;
	     case 2:
	        temp = 0x80000;
	        break;
	     case 3:
	        temp = 0x100000;
	        break;
	     case 4:
	        temp = 0x180000;
	        break;
	  /* case 5:
	        temp = 0x200000;
	        break; */
	     case 6:
	        temp = 0x10000;
	        break;
    }

    /*update Main Array size in SSD config*/
    pSSDConfig->mainArraySize = temp;

    /**************************************************************************
    *  Number of blocks in middle address space and fill into SSD_CONFIG structure
    *
    *  C Flash
    *  MAS = 0: midBlockNum = 2;    Sectorization = 2x128K
	   *  MAS = 1: midBlockNum = Res;  Sectorization = n.a
    *
    *  D Flash
    *  MAS = 0: midBlockNum = 0;    Sectorization = 0
    *  MAS = 1: midBlockNum = Res;  Sectorization = n.a
    *
	   **************************************************************************/

    /* Determine the number of blocks in middle address space and fill into
       SSD_CONFIG structure.
    */
	   if ((UINT32)0x0 == (MCRValue & C90FL_MCR_MAS))
	   {
        if(CFLASH_BASE_ADDR == pSSDConfig->c90flRegBase)
        {
	          pSSDConfig->midBlockNum = 2;
        }

        if(DFLASH_BASE_ADDR == pSSDConfig->c90flRegBase)
        {
           pSSDConfig->midBlockNum = 0;
        }
	   }

    if ( temp > (UINT32)0x00080000 )
    {
        /* (mainArraySize - 512K) / 128K */
        pSSDConfig->highBlockNum = (temp - (UINT32)0x00080000) >> 17;
    }

    /* For C1 and C2 flash array all blocks below to high address space !!! */
    if((C1_BASE_ADDR == pSSDConfig->c90flRegBase) ||
       (C2_BASE_ADDR == pSSDConfig->c90flRegBase))
    {
        pSSDConfig->lowBlockNum = 0;
        pSSDConfig->midBlockNum = 0;
        pSSDConfig->highBlockNum = 4;
    }

    if (pSSDConfig->BDMEnable)
    {
        //asm ( "mr   r3,returnCode" );   /* save the return code to R3 */
        #ifdef VLE_ASM
        	asm ( "se_sc " );                /* generate system call interrupt */
        #else
        	asm ( "sc " );
        #endif
    }

    return returnCode;
}
