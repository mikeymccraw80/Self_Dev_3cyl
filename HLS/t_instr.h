#ifndef T_INSTR_H
#define T_INSTR_H
/******************************************************************************
 *
 * Filename:          t_instr.h
 *
 * Description:       This is the structure header file
 *                    for MDS instrumentation.
 *
 * Global Functions Defined:
 *                    None
 * Static Functions Defined:
 *                    None
 * Inline Functions Defined:
 *                    None
 *
 * C Project Software Forward EMS
 *
 * (c) Copyright Delco Electronics 1997
 *
 *****************************************************************************/

/******************************************************************************
 *  Global Data Type Include Files
 *****************************************************************************/
#include "systpcfg.h"
#include "t_base.h"


#define FLASH_BUFFER_SIZE     ( 0x000800 )


  enum Slew_Modes
    {
    NoSlew,
    Absolute,
    Modify,
    Illegal_Mode
    };


  enum Slew_Signs
    {
    Positive,
    Negative,
    Illegal_Sign
    };


typedef
  struct
    {
    BYTE Mode;
    BYTE Sign;
    union
      {
      BYTE Value_Array_Byte [4];
      WORD  Value_Array_Word[2];
      LONGWORD  Value_Longword;
      }
    Slew_Value;
    }
  Slew_Data_Type;



typedef
  struct
    {
    char      MDS_Prog_Name [10];
    BYTE MDS_Prog_Rev;
    }
  MDSProgramName_Type;



typedef
   union
    {
      LONGWORD Function_Code_Address;
      void (*Function_To_Execute) (void);
    } MDS_FunctionCode_Type;


typedef
  struct
    {
    BYTE DummyByte;
    BYTE UpperByte;
    union
      {
      WORD  AddressContent;
      BYTE *DoubleByteAddressPointer;
      }Discr;
    }
  MDS_AddressPointer_Type;


enum
{ Product_Memory, MDS_Memory };


typedef union
{
    struct
    {
        BYTE Execute_State     : 1;
        BYTE Unused_6_4        : 3;
        BYTE Request           : 4;
    }Access_Method_Read;
    BYTE Command;
}ROMDIS_Control_Type;


typedef union
{
   WORD Whole_Word;
   struct
    {
        BYTE High_Byte;
        BYTE Low_Byte;
    }Two_Bytes;
   struct
   {
     WORD    Unused_Upper_Bits          : 8;
     WORD    Write_State_Machine_Status : 1;
     WORD    Erase_Suspend_Status       : 1;
     WORD    Erase_Status               : 1;
     WORD    Program_Status             : 1;
     WORD    VPP_Status                 : 1;
     WORD    Unused_Bit02               : 1;
     WORD    Unused_Bit01               : 1;
     WORD     Unused_Bit00              : 1;
   }I28F400_Status;
}Flash_Registers_Type;


typedef struct
{
Flash_Registers_Type Local_Buffer[FLASH_BUFFER_SIZE];
}MDS_Subr_Struct ;


/* Communication Memory */
typedef struct
{

/* addr   contents                                */
/* (hex)                                          */

/* 00 */  volatile WORD Presence_Pattern;

/* 02 */  volatile MDSProgramName_Type MDS_Program_Name;

/* 0E */  volatile MDS_FunctionCode_Type   MDS_Function;

/* 12 */  volatile ROMDIS_Control_Type ROMDIS_Control;

/* 14 */  volatile BYTE Reset_Status_Byte;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* Every time the MDS pulls RESET, this byte is written to       */
/* indicate that the MDS was responsible for the RESET.  It      */
/* should be cleared after coming out of reset so that the       */
/* next reset may be determined.                                  */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* 16 */  volatile WORD ADM_io;
/* volatile WORD ADM_Info_0 = ADM_INFO_0; */
/* 18 */  volatile WORD ADM_Info_1;
/* 1A */  volatile WORD ADM_Info_2;
/* 1C */  volatile WORD ADM_Info_3;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* The ADM inputs are sequentially logged to these variables.    */
/* Thus, they must remain in order and grouped together.         */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* 1E */  volatile WORD ADM_hd;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* The MDS will set this byte to a "1" when the ADM block has    */
/* been written.  The product should reset this byte to a "0"    */
/* in order to sense the next update.                            */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* 20 */  volatile WORD CIB_Logging_Status;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* The MIP will write the status of the CIB to this variable.    */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* 22 */  Slew_Data_Type  Mem_Address_High_Slew_Data;
/* 28 */  Slew_Data_Type  Mem_Address_Mid_Slew_Data;
/* 2E */  Slew_Data_Type  Mem_Address_Low_Slew_Data;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* These variables are used to display any byte in Memory from   */
/* the MDS by slewing Mem_Address_Hi, Mem_Address_Mid,           */
/*                                 and Mem_Address_Low.          */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* 34 */  volatile BYTE  *Down_Start ;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* This value contains the address of the starting location that   */
/* the download or verify begins at.                               */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* 38 */  volatile LONGWORD Block_Size ;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* The number of bytes that are to be downloaded or verified.      */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* 3C */  volatile Flash_Registers_Type  Down_Sum ;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* During download, this is the running checksum of the            */
/* downloaded bytes.                                               */
/*                                                                 */
/* If there is a mismatch during verify, the high byte indicates   */
/* the ROM contents and the low byte the RAM contents.  Start      */
/* Address has the address immediately following the mismatch      */
/* (and thus the location at which to continue the verification    */
/* if so commanded by the MAC.  Block_Size is the number of        */
/* bytes remaining in the verify.                                  */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/* Your slew data (YourDataSlewData) should be defined outside     */
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

} MDS_Com_Struct ;


/*****************************/
/* Data_Acquisition Triggers */
/*****************************/
typedef struct
{
volatile BYTE MDS_CHANNEL_0;
volatile BYTE MDS_CHANNEL_1;
volatile BYTE MDS_CHANNEL_2;
volatile BYTE MDS_CHANNEL_3;
}Data_Acq_Struct;



/***************************/
/* Semaphore Memory        */
/***************************/
/* 
 * This pragma was added to force all data accesses that follow to full
 *  32-bit adrress.  For short adressing the compiler option '-Xaddr-data=0x10'
 *  is used globally to make all data accesses 16 bits.  When addresses must be
 *  outside of the range 0xff8000 to 0xffffff, this pragma must be used.
 *  A second pragma 'section DATA' ends the effect. 
 */
#if (  ( config_CPU_T == option_MC68377 ) \
      && ( config_Compiler_Vendor == option_DIABDATA )  )

#pragma section DATA far-absolute

#else
#define SECTION_DATA_BEGIN
#include "section.h"
#endif

extern volatile WORD MDS_Com_Mem_Switch;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* There is no hardware memory arbitration with the MDS for      */
/* access to the communications memory.  This variables allows   */
/* a software handshake to be done.  Writing a 0 to it initiates */
/* the handshake.  When a 0 is read from it, access has been     */
/* granted.  To release the memory, write a 1 to this variable.  */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

extern Data_Acq_Struct MDS_Data_Acq;

extern MDS_Com_Struct MDS_Com;

extern MDS_Subr_Struct MDS_Sub;

/* end pragma section DATA far-absolute */
#if (  ( config_CPU_T == option_MC68377 ) \
      && ( config_Compiler_Vendor == option_DIABDATA )  )

#pragma section DATA

#else
/* end pragma section DATA far-absolute */
#define SECTION_DATA_END
#include "section.h"
#endif

#endif

/******************************************************************************
*
* Revision History:
*
* Rev.  YYMMDD Who RSM# Changes
* ----- ------ --- ---- -------------------------------------------------------
* 1.1   960117 mye xxxx Created module
* 1.6   971122 blt xxxx Changed names of VIOS IAC and Idle IACV structures
* 1.7   970901 lcq xxxx Added CCP slew
* 1.8   980218 raw 0409 Add 8 cyl capability
* 1.11  980324 RJK 0416 Added pragmas for short addressing
* 1.11  980511 blt 0486 Merge offline partition node 024 into Lecc node 278
* 1.3   980715 raw xxxx Added Transient Fuel Slew variables
* 1.3   991103 gps 0457 Modularization in CORE
*                       Moved subsystem Slew_Data_Types outside MDS_Com_Struct:
*                         IsINST_EGR_Pstn,
*                         IsINST_SparkDwell,
*                         IsINST_SparkAdv,
*                         IsINST_SparkAdvInd,
*                         IsINST_VE,
*                         IsINST_AF,
*                         IsINST_VIOS_IAC,
*                         IsINST_IDLE_IACV_Reset,
*                         IsINST_CCP_OverideStatus,
*                         IsINST_CCP_DC,
*                         IsINST_CCP_Factor,
*                         IsINST_FF,
*                         IsINST_WIF
*                       Updated header description.
*
* core_dc2 Revision History:
*
* 1.1   000525 woz 0822 Initial EMSDC2 Excalibur Release based on Core Node 32.
*                       The following changes were made from Core Node 32:
*       000426 jh       Changed BYTE MDS_Com_Mem_Switch to WORD
* 1.2   010827 kan 1444 Added #if statement for DiabData compiler.
*
******************************************************************************/
/*
* $Source: common@brighton.tcb:core_dc2:t_instr.h $
* $Revision: 1.2 $
* $Author: brighton.tcb:/users/kanietub/dsds/tasking_update:kanietub $
*/
