 /************************************************************************
 *           Copyright (C) 2005-2007 by Freescale. All rights reserved.  *
 *************************************************************************
 *                                                                       *
 *   Freescale reserves the right to make changes without further notice *
 *   to any product herein to improve reliability, function or design.   *
 *   Freescale does not assume any liability arising out of the          *
 *   application or use of any product, circuit, or software described   *
 *   herein; neither does it convey any license under its patent rights  *
 *   nor the rights of others.                                           *
 *                                                                       *
 *   Freescale products are not designed, intended, or authorized for    *
 *   use as components in systems intended for surgical implant into     *
 *   the body, or other applications intended to support life, or for    *
 *   any other application in which the failure of the Freescale product *
 *   could create a situation where personal injury or death may occur.  *
 *                                                                       *
 *   Should Buyer purchase or use Freescale products for any such        *
 *   unintended or unauthorized application, Buyer shall indemnify and   *
 *   hold Freescale and its officers, employees, subsidiaries,           *
 *   affiliates, and distributors harmless against all claims costs,     *
 *   damages, and expenses, and reasonable attorney fees arising out     *
 *   of, directly or indirectly, any claim of personal injury or death   *
 *   associated with such unintended or unauthorized use, even if such   *
 *   claim alleges that Freescale was negligent regarding the design     *
 *   or manufacture of the part.                                         *
 *                                                                       *
 *   Freescale and the Freescale logo* are registered trademarks of      *
 *   Freescale Semicondutor, Inc.                                        *
 *                                                                       *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Standard Software Driver for C90fl                      *
 *                                                                       *
 * FILE NAME     :  ssd_c90fl.h                                          *
 * DATE          :  Spetember 11, 2008                                   *
 * AUTHOR        :  Arvind Awasthi                                       *
 * E-mail        :  r56611@freescale.com                                 *
 *                                                                       *
 *************************************************************************/

/******************************* CHANGES *********************************
  0.0.0   09.11.2008         Arvind Awasthi       Initial Version
  0.4.4   07.27.2010         FPT Team         Update to support to Cobra90
  0.4.6   01.11.2011         FPT Team         Update macro C90FL_HBL_HBLOCK
                                              to support Cobra90
                                              Remove other unused macros
 *************************************************************************/

#ifndef _C90FL_H_
#define _C90FL_H_
#include    "ssd_types.h"

#define CODE_WARRIOR                      0x01
#define DIAB_COMPILER                     0x00

/*For selecting Codewarrior compiler define COMPILER_SELECT as CODE_WARRIOR   */
/*For selecting Diab compiler define COMPILER_SELECT as DIAB_COMPILER */
#define COMPILER_SELECT                   DIAB_COMPILER
//#define COMPILER_SELECT                   CODE_WARRIOR

//#define C90FL_ON                          0x01
//#define C90FL_OFF                         0x00

/*************************************************************************/
/*     Offsets of C90FL Control Registers and PFBIU Control Registers     */
/*************************************************************************/
#define C90FL_MCR             0x0000       /* Module Configuration Register */
#define C90FL_LML             0x0004       /* Low/Mid Address Space Block Locking Register */
#define C90FL_HBL             0x0008       /* High Address Space Block Locking Register */
#define C90FL_SLL             0x000C       /* Secondary Low/Mid Address Space Block Locking Register */
#define C90FL_LMS             0x0010       /* Low/Mid Address Space Block Select Register */
#define C90FL_HBS             0x0014       /* High Address Space Block Select Register */
#define C90FL_ADR             0x0018       /* Address Register */
#define PFB_CR                0x001C       /* PFBIU Configuration Register for port 0 */
#define C90FL_UT0             0x003C       /* The User Test 0 register */
#define C90FL_UT1             0x0040       /* The User Test 1 register */
#define C90FL_UT2             0x0044       /* The User Test 2 register */
#define C90FL_UM0             0x0048       /* The User MISR 0 Register */
#define C90FL_UM1             0x004C       /* The User MISR 1 Register */
#define C90FL_UM2             0x0050       /* The User MISR 2 Register */
#define C90FL_UM3             0x0054       /* The User MISR 3 Register */
#define C90FL_UM4             0x0058       /* The User MISR 4 Register */

/*************************************************************************/
/*              C90FL(2) Module Control Registers Field Definition           */
/*************************************************************************/
/* Module Configuration Register */
//#define C90FL_MCR_SFS         0x10000000   /* Special Flash Selector */
#define C90FL_MCR_SIZE        0x07000000   /* Array Space Size */
#define C90FL_MCR_LAS         0x00700000   /* Low Address Space Size */
#define C90FL_MCR_MAS         0x00010000   /* Mid Address Space Size */
#define C90FL_MCR_EER         0x00008000   /* ECC Event Error */
#define C90FL_MCR_RWE         0x00004000   /* Read While Write Event Error */
#define C90FL_MCR_SBC         0x00002000   /* Single Bit Correction Error */
#define C90FL_MCR_PEAS        0x00000800   /* Program/Erase Access Space */
#define C90FL_MCR_DONE        0x00000400   /* State Machine Status */
#define C90FL_MCR_PEG         0x00000200   /* Program/Erase Good */
#define C90FL_MCR_PGM         0x00000010   /* Program */
#define C90FL_MCR_PSUS        0x00000008   /* Program Suspend */
#define C90FL_MCR_ERS         0x00000004   /* Erase */
#define C90FL_MCR_ESUS        0x00000002   /* Erase Suspend */
#define C90FL_MCR_EHV         0x00000001   /* Enable High Voltage */


/* Low/Mid Address Space Block Locking Register */
//#define C90FL_LML_LME         0x80000000   /* Low and Mid Address Lock Enable */
#define C90FL_LML_SLOCK       0x00100000   /* Shadow Lock */
#define C90FL_LML_MLOCK       0x00030000   /* Mid Address Block Lock */
#define C90FL_LML_LLOCK       0x000003FF   /* Low Address Block Lock */

/* EEPROM High Address Space Block Locking Register */
//#define C90FL_HBL_HBE         0x80000000   /* High Address Lock Enable */
#define C90FL_HBL_HBLOCK      0x000003FF   /* High Address Space Block Lock */

/* Secondary Low/Mid Address Space Block Locking Register */
//#define C90FL_SLL_SLE         0x80000000   /* Secondary Low and Mid Address Lock Enable */
#define C90FL_SLL_SSLOCK      0x00100000   /* Secondary Shadow Lock */
#define C90FL_SLL_SMLOCK      0x00030000   /* Secondary Mid Address Block Lock */
#define C90FL_SLL_SLLOCK      0x000003FF   /* Secondary Low Address Block Lock */

/* Low/Mid Address Space Block Select Register */
//#define C90FL_LMS_MSEL        0x00030000   /* Mid Address Space Block Select */
//#define C90FL_LMS_LSEL        0x000003FF   /* Low Address Space Block Select */

/* High Address Space Block Select Register */
//#define C90FL_HBS_HBSEL       0x000003FF   /* High Address Space Block Select */

/* Platform Flash BIU Configuration Register */
//#define PFB_CR_APC            0x0000E000   /* Address Pipelining Control */
//#define PFB_CR_WWSC           0x00001800   /* Write Wait State Control */
//#define PFB_CR_RWSC           0x00000700   /* Read Wait State Control */
#define PFB_CR_BFEN           0x00000001   /* PFBIU Line Read Buffers Enable */

/* User Test 0 Register */
#define C90FL_UT0_UTE         0x80000000
#define C90FL_UT0_SBCE        0x40000000
//#define C90FL_UT0_DSI         0x00FF0000
#define C90FL_UT0_MRE         0x00000020
#define C90FL_UT0_MRV         0x00000010
#define C90FL_UT0_EIE         0x00000008
#define C90FL_UT0_AIS         0x00000004
#define C90FL_UT0_AIE         0x00000002
#define C90FL_UT0_AID         0x00000001
#define C90FL_LOG_SEQ         0x00000001   /* Array integrity sequence is logically sequential. */
//#define C90FL_ABF_SEQ         0x00000000   /* Array integrity sequence is proprietary sequence. */

#define C90FL_FMR_ERASED_LEVEL       0x00000001 /* Margin checked to an erased level (MRV=1) */
//#define C90FL_FMR_PROGRAMMED_LEVEL   0x00000000 /* Margin checked to an programmed level (MRV=0) */
#define C90FL_TEST_ENABLE_PASSWORD 0xF9F99999

/* MCU ID Register */
//#define SIU_MIDR            0xC3F90004

/* Macros for Accessing the Registers */
#define C90FL_REG_BIT_SET(address, mask)        (*(VUINT32*)(address) |= (mask))
#define C90FL_REG_BIT_CLEAR(address, mask)      (*(VUINT32*)(address) &= ~(mask))
#define C90FL_REG_BIT_TEST(address, mask)       (*(VUINT32*)(address) & (mask))
#define C90FL_REG_WRITE(address, value)         (*(VUINT32*)(address) = (value))
#define C90FL_REG_READ(address)                 ((UINT32)(*(VUINT32*)(address)))
#define C90FL_GET_BIT(value, position)          (UINT8)(((value) >> (position)) & 0x01)

/* Set/Clear C90FLMCR bits without affecting MCR-EER and MCR-RWE */
#define C90FLMCR_BIT_SET(MCRAddress, mask)      \
    C90FL_REG_WRITE(MCRAddress, ((mask | C90FL_REG_READ(MCRAddress)) & (~(C90FL_MCR_EER | C90FL_MCR_RWE))))

#define C90FLMCR_BIT_CLEAR(MCRAddress, mask)    \
    C90FL_REG_WRITE(MCRAddress, (((~mask) & C90FL_REG_READ(MCRAddress)) & (~(C90FL_MCR_EER | C90FL_MCR_RWE))))

#define C90FLMCR_EER_CLEAR(MCRAddress, mask)    \
    C90FL_REG_WRITE(MCRAddress, ((mask | C90FL_REG_READ(MCRAddress)) & (~C90FL_MCR_RWE)))

/*************************************************************************/
/*                   Return Codes for SSD functions                      */
/*************************************************************************/

#define C90FL_OK                      0x00000000
//#define C90FL_INFO_RWE                0x00000001   /* There is read-while-write error for previous reads */
//#define C90FL_INFO_EER                0x00000002   /* There is ECC error for previous reads */
//#define C90FL_INFO_EPE                0x00000004   /* The program/erase for all blocks including shadow row and excluding the boot block is disabled */
//#define C90FL_INFO_BBEPE              0x00000008   /* The program/erase for boot block is disabled */
//#define C90FL_ERROR_PARTID            0x00000010   /* The SSD cannot operate on this part */
//#define C90FL_ERROR_STOP              0x00000020   /* The flash is in STOP mode and no operation is allowed */
#define C90FL_ERROR_ALIGNMENT         0x00000100   /* Alignment error */
#define C90FL_ERROR_RANGE             0x00000200   /* Address range error */
#define C90FL_ERROR_BUSY              0x00000300   /* New program/erase cannot be preformed while previous high voltage operation in progress */
#define C90FL_ERROR_PGOOD             0x00000400   /* The program operation is unsuccessful */
#define C90FL_ERROR_EGOOD             0x00000500   /* The erase operation is unsuccessful */
#define C90FL_ERROR_NOT_BLANK         0x00000600   /* There is non-blank location in the checked flash memory */
#define C90FL_ERROR_VERIFY            0x00000700   /* There is a mismatch between the source data and content in the checked flash memory */
#define C90FL_ERROR_LOCK_INDICATOR    0x00000800   /* Invalid block lock indicator */
//#define C90FL_ERROR_RWE               0x00000900   /* Read while write error on the previous reads */
#define C90FL_ERROR_PASSWORD          0x00000A00   /* The password provided cannot unlock the block lock register for register writes */
#define C90FL_ERROR_AIC_MISMATCH      0x00000B00   /* The MISR generated by the AIC hardware doesnot match the MISR passed by the user */
#define C90FL_ERROR_AIC_NO_BLOCK      0x00000C00   /* No blocks have been enabled for Array Integrity check */
#define C90FL_ERROR_FMR_MISMATCH      0x00000D00   /* The MISR generated by the FMR hardware doesnot match the MISR passed by the user */
#define C90FL_ERROR_FMR_NO_BLOCK      0x00000E00   /* No blocks have been enabled for Factory Margin Read check */
#define C90FL_ERROR_ECC_LOGIC         0x00000F00   /* The ECC Logic check has failed */

#define C90FL_ECC_ERR_BIT_SET_ZERO    0x00
#define C90FL_ECC_ERR_BIT_SET_ONE     0x01
#define C90FL_ECC_ERR_BIT_SET_TWO     0x02
/*************************************************************************/
/*                   Other Macros for SSD functions                      */
/*************************************************************************/

#define C90FL_WORD_SIZE           4   /* size of a word in byte */
#define C90FL_DWORD_SIZE          8   /* size of a double word in byte */

/* Indication for setting/getting block lock state */
#define LOCK_SHADOW0_PRIMARY     0   /* Primary Block lock protection of BANK0 shadow address space */
#define LOCK_SHADOW0_SECONDARY   1   /* Secondary Block lock protection of BANK0 shadow address space */
#define LOCK_SHADOW1_PRIMARY     2   /* Primary Block lock protection of BANK1 shadow address space */
#define LOCK_SHADOW1_SECONDARY   3   /* Secondary Block lock protection of BANK1 shadow address space */
#define LOCK_LOW_PRIMARY         4   /* Primary block lock protection of low address space */
#define LOCK_LOW_SECONDARY       5   /* Secondary block lock protection of low address space */
#define LOCK_MID_PRIMARY         6   /* Primary block lock protection of mid address space */
#define LOCK_MID_SECONDARY       7   /* Secondary block lock protection of mid address space */
#define LOCK_HIGH                8   /* Block lock protection of high address space */

/* Macros for flash suspend operation */
#define NO_OPERATION             0   /* no program/erase operation */
#define PGM_WRITE                1   /* A program sequence in interlock write stage. */
#define ERS_WRITE                2   /* An erase sequence in interlock write stage. */
#define ERS_SUS_PGM_WRITE        3   /* A erase-suspend program sequence in interlock write stage. */
#define PGM_SUS                  4   /* The program operation is in suspend state */
#define ERS_SUS                  5   /* The erase operation on main array is in suspend state */
#define SHADOW_ERS_SUS           6   /* The erase operation on shadow row is in suspend state. */
#define ERS_SUS_PGM_SUS          7   /* The erase-suspended program operation is in suspend state */

/* Macros for flash resume operation */
#define RES_NOTHING              0   /* No suspended program/erase operation */
#define RES_PGM                  1   /* The program operation is resumed */
#define RES_ERS                  2   /* The erase operation is resumed */
#define RES_ERS_PGM              3   /* The erase-suspended program operation is resumed */


/*************************************************************************/
/*                   SSD Configuration Structure                         */
/*************************************************************************/
#define C90FL_PAGE_SIZE       0x10   /* page size for C90fl derivatives*/



typedef struct _ssd_config
{
    UINT32 c90flRegBase;         /* C90FL control register base */
    UINT32 mainArrayBase;        /* base of main array */
    UINT32 mainArraySize;        /* size of main array */
    UINT32 shadowRowBase;        /* base of shadow row */
    UINT32 shadowRowSize;        /* size of shadow row */
    UINT32 lowBlockNum;          /* block number in low address space */
    UINT32 midBlockNum;          /* block number in middle address space */
    UINT32 highBlockNum;         /* block number in high address space */
    UINT32 pageSize;             /* page size */
    UINT32 BDMEnable;            /* debug mode selection */
} SSD_CONFIG, *PSSD_CONFIG;

typedef struct _c90fl_MISR
{
    UINT32 W0;
    UINT32 W1;
    UINT32 W2;
    UINT32 W3;
    UINT32 W4;
} MISR;

/*************************************************************************/
/*                   BANK specific macros (fixed)                        */
/*************************************************************************/
#define BANK_LAS_SIZE           0x00040000   /* LAS size of Any Bank*/
#define BANK_MAS_SIZE           0x00040000   /* MAS size of Any Bank*/
#define C90FL_LAS_SIZE         (BANK_LAS_SIZE + BANK_MAS_SIZE) /* LAS Size for user*/
#define C90FL_MAS_STARTADDR    C90FL_LAS_SIZE   /* MAS Start Address for user */
#define C90FL_MAS_SIZE         C90FL_LAS_SIZE   /* MAS Size for user */
#define C90FL_HAS_STARTADDR    (C90FL_LAS_SIZE + C90FL_MAS_SIZE ) /* Start address of HAS */
#define SHADOW_ROW_BANK0_OFFSET 0x00000000   /* Start address of Shadow row for BANK0*/
#define SHADOW_ROW_BANK0_SIZE   0x00004000   /* Size of Shadow row for BANK0*/
#define SHADOW_ROW_BANK1_OFFSET 0x00100000   /* Start address of Shadow row for BANK1*/
#define SHADOW_ROW_BANK1_SIZE   0x00004000   /* Size of Shadow row for BANK1*/
#define BANK1_REG_BASEOFFSET    0x00004000   /* BANK1 register base */



/*************************************************************************/
/*                   BANK specific macros (tentative)                    */
/*************************************************************************/
//#define LAS_MASK_BANK0          0x000003FF   /* Mask for BANK0 LAS Blocks */
//#define MAS_MASK_BANK0          0x00000C00   /* Mask for BANK0 MAS Blocks */
//#define LAS_BLOCKS_BANK0        0X0A
//#define LAS_MASK_BANK1          0x00000001   /* Mask for BANK1 LAS Blocks */
//#define MAS_MASK_BANK1          0x00000001   /* Mask for BANK1 MAS Blocks */
//#define LAS_BLOCKS_BANK1        0X01
/*************************************************************************/
/*                   NULL CallBack Function Pointer                      */
/*************************************************************************/
#define NULL_CALLBACK            ((void *)0xFFFFFFFF)

/*************************************************************************/
/*                      Prototypes of wrapper SSD Functions             */
/*************************************************************************/

extern UINT32 ssd_c90fl_FlashInit ( PSSD_CONFIG pSSDConfig );

extern UINT32 ssd_c90fl_FlashErase ( PSSD_CONFIG pSSDConfig,
                UINT8  shadowFlag,
                UINT32 lowEnabledBlocks,
                UINT32 midEnabledBlocks,
                UINT32 highEnabledBlocks,
                void (*CallBack)(void)
                );

extern UINT32 ssd_c90fl_BlankCheck ( PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 *pFailAddress,
                UINT64 *pFailData,
                void (*CallBack)(void)
                );

extern UINT32 ssd_c90fl_FlashProgram ( PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 source,
                void (*CallBack)(void)
                );

extern UINT32 ssd_c90fl_ProgramVerify ( PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 source,
                UINT32 *pFailAddress,
                UINT64 *pFailData,
                UINT64 *pFailSource,
                void (*CallBack)(void)
                );

extern UINT32 ssd_c90fl_GetLock ( PSSD_CONFIG pSSDConfig,
                UINT8 blkLockIndicator,
                BOOL *blkLockEnabled,
                UINT32 *blkLockState
                );

extern UINT32 ssd_c90fl_SetLock ( PSSD_CONFIG pSSDConfig,
                UINT8 blkLockIndicator,
                UINT32 blkLockState,
                UINT32 password
                );

extern UINT32 ssd_c90fl_CheckSum ( PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 *pSum,
                void (*CallBack)(void)
                );

extern UINT32 ssd_c90fl_FlashSuspend ( PSSD_CONFIG pSSDConfig,
                      UINT8 *suspendState,
                      UINT8 *suspendFlag
                      );

extern UINT32 ssd_c90fl_FlashResume ( PSSD_CONFIG pSSDConfig,
                     UINT8 *resumeState
                     );

extern UINT32 ssd_c90fl_FlashECCLogicCheck ( PSSD_CONFIG pSSDConfig,
                            UINT64 dataVal,
                            UINT64 errBits,
                            UINT32 eccValue);

extern UINT32 ssd_c90fl_FlashArrayIntegrityCheck ( PSSD_CONFIG pSSDConfig,
                                  UINT32 lowEnabledBlocks,
                                  UINT32 midEnabledBlocks,
                                  UINT32 highEnabledBlocks,
                                  BOOL addrSeq,
                                  MISR misrValue_Bk0,
                                  MISR misrValue_Bk1,
                                  void (*CallBack)(void));

extern UINT32 ssd_c90fl_FactoryMarginReadCheck ( PSSD_CONFIG pSSDConfig,
                                UINT32 lowEnabledBlocks,
                                UINT32 midEnabledBlocks,
                                UINT32 highEnabledBlocks,
                                BOOL marginLevel,
                                MISR misrValue_Bk0,
                                MISR misrValue_Bk1,
                                void (*CallBack)(void));

/*************************************************************************/
/*                      Prototypes of common SSD Functions              */
/*************************************************************************/

extern UINT32 CflashInit ( PSSD_CONFIG pSSDConfig );


extern UINT32 CsetLock (UINT32 registerBase,
                 UINT8 blkLockIndicator,
                 BOOL  shadowLockPrimary,
                 UINT32 blkLockState,
                 UINT32 password);


extern UINT32 CgetLock (UINT32 registerBase,
                 UINT8 blkLockIndicator,
                 BOOL  shadowLockPrimary,
                 BOOL *blkLockEnabled,
                 UINT32 *blkLockState);

extern UINT32 CflashErase ( PSSD_CONFIG pSSDConfig,
                 UINT8  shadowFlag,
                 UINT32 lowEnabledBlocks,
                 UINT32 midEnabledBlocks,
                 UINT32 highEnabledBlocks);

extern UINT32 CblankCheck (UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailAddress,
                    UINT64 *pFailData,
               void (*CallBack)(void));

extern UINT32 CflashProgram (UINT32 MCRAddress,
                 UINT32 shadowRowBase,
                 BOOL mainAddrSpaceSelect,
                 UINT32 dest,
                 UINT32 source,
                 UINT32 size);

extern UINT32 CprogramVerify (UINT32 dest,
                       UINT32 size,
                       UINT32 source,
                       UINT32 *pFailAddress,
                       UINT64 *pFailData,
                       UINT64 *pFailSource,
                  void (*CallBack)(void));

extern UINT32 CcheckSum (UINT32 dest,
                  UINT32 size,
                  UINT32 *pSum,
              void(*CallBack)(void));

extern UINT32 CflashResume (UINT32 MCRValue,
                 UINT8 *resumeState);


extern void CflashSuspend (UINT32 MCRAddress,
                    UINT8 *suspendState,
                    UINT8 *suspendFlag);

extern UINT32 CFlashECCLogicCheck(UINT32 c90flRegBase,
                            UINT32 mainArraybase,
                            UINT32 eccValue,
                            UINT64 flipDataWord,
                            UINT64 errBits,
                            UINT32 dataWord1,
                            UINT32 dataWord2);

extern UINT32 CFlashArrayIntegrityCheck (UINT32 c90flRegBase,
                                   UINT32 lowEnabledBlocks,
                                   UINT32 highEnabledBlocks,
                                   BOOL marginLevel);

extern UINT32 CFlashArrayIntegrityCheck (UINT32 c90flRegBase,
                                   UINT32 lowEnabledBlocks,
                                   UINT32 highEnabledBlocks,
                                   BOOL marginLevel);

extern UINT32 ECCCalculation(UINT64 dataVal);

/*************************************************************************/
/*                      SSD Function Pointer Types                       */
/*************************************************************************/

typedef UINT32 (*pFLASHINIT) ( PSSD_CONFIG pSSDConfig );

typedef UINT32 (*pFLASHERASE) (
                PSSD_CONFIG pSSDConfig,
                BOOL shadowFlag,
                UINT32 lowEnabledBlocks,
                UINT32 midEnabledBlocks,
                UINT32 highEnabledBlocks,
                void (*CallBack)(void)
               );

typedef UINT32 (*pBLANKCHECK) (
                PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 *pFailAddress,
                UINT64 *pFailData,
                void (*CallBack)(void)
               );

typedef UINT32 (*pFLASHPROGRAM) (
                PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 source,
                void (*CallBack)(void)
               );

typedef UINT32 (*pPROGRAMVERIFY) (
                PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 source,
                UINT32 *pFailAddress,
                UINT64 *pFailData,
                UINT64 *pFailSource,
                void (*CallBack)(void)
               );

typedef UINT32 (*pGETLOCK) (
                PSSD_CONFIG pSSDConfig,
                UINT8 blkLockIndicator,
                BOOL *blkLockEnabled,
                UINT32 *blkLockState
               );

typedef UINT32 (*pSETLOCK) (
                PSSD_CONFIG pSSDConfig,
                UINT8 blkLockIndicator,
                UINT32 blkLockState,
                UINT32 password
               );

typedef UINT32 (*pCHECKSUM) (
                PSSD_CONFIG pSSDConfig,
                UINT32 dest,
                UINT32 size,
                UINT32 *pSum,
                void (*CallBack)(void)
               );
typedef UINT32 (*pFLASHSUSPEND) (
                PSSD_CONFIG pSSDConfig,
                UINT8 *suspendState,
                UINT8 *suspendFlag
               );

typedef UINT32 (*pFLASHRESUME) (
                PSSD_CONFIG pSSDConfig,
                UINT8 *resumeState
               );

typedef UINT32 (*pFLASHECCLOGICCHECK) (
                PSSD_CONFIG pSSDConfig,
                UINT64 dataVal,
                UINT64 errBits,
                UINT32 eccValue
               );
typedef UINT32 (*pFLASHARRAYINTEGRITYCHECK) ( PSSD_CONFIG pSSDConfig,
                                  UINT32 lowEnabledBlocks,
                                  UINT32 midEnabledBlocks,
                                  UINT32 highEnabledBlocks,
                                  BOOL addrSeq,
                                  MISR misrValue_Bk0,
                                  MISR misrValue_Bk1,
                                  void (*CallBack)(void));

typedef UINT32 (*pFACTORYMARGINREADCHECK) ( PSSD_CONFIG pSSDConfig,
                                UINT32 lowEnabledBlocks,
                                UINT32 midEnabledBlocks,
                                UINT32 highEnabledBlocks,
                                BOOL marginLevel,
                                MISR misrValue_Bk0,
                                MISR misrValue_Bk1,
                                void (*CallBack)(void));

#endif
