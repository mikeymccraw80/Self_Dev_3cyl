#ifndef DD_MMU_H
#define DD_MMU_H

#include "hw_mmu.h"


#define MMU_MAS_ADDRESS_DEFAULT (0xFFFFFFFF)

#define MMU_MAS_Is_Valid_Entry( x ) \
   (x == MMU_MAS_ADDRESS_DEFAULT ? 0 : 1)

#define MMU_MAS_Get_Effective_Address( x ) \
   ( x >> ( 12 ) )
#define MMU_MAS_Get_Real_Address( x ) \
   ( x >> ( 12 ) )


//==========================================================================
// object-like(name and constant) macros
//==========================================================================
#define MMU_MAS1_MASK (0xC0FF1F00UL)
#define MMU_MAS2_MASK (0xFFFFF03FUL)
#define MMU_MAS3_MASK (0xFFFFF3FFUL)

typedef enum
{
   MMU_TLB_ENTRY_INDEX_0,
   MMU_TLB_ENTRY_INDEX_1,
   MMU_TLB_ENTRY_INDEX_2,
   MMU_TLB_ENTRY_INDEX_3,
   MMU_TLB_ENTRY_INDEX_4,
   MMU_TLB_ENTRY_INDEX_5,
   MMU_TLB_ENTRY_INDEX_6,
   MMU_TLB_ENTRY_INDEX_7,
   MMU_TLB_ENTRY_INDEX_8,
   MMU_TLB_ENTRY_INDEX_9,
   MMU_TLB_ENTRY_INDEX_10,
   MMU_TLB_ENTRY_INDEX_11,
   MMU_TLB_ENTRY_INDEX_12,
   MMU_TLB_ENTRY_INDEX_13,
   MMU_TLB_ENTRY_INDEX_14,
   MMU_TLB_ENTRY_INDEX_15

}MMU_TLB_Entry_Index_T;


typedef enum
{
   MMU_TLB_ENTRY_PAGE_SIZE_4K_BYTES    =1,
   MMU_TLB_ENTRY_PAGE_SIZE_16K_BYTES   =2,
   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES   =3,
   MMU_TLB_ENTRY_PAGE_SIZE_256K_BYTES  =4,
   MMU_TLB_ENTRY_PAGE_SIZE_1M_BYTES    =5,
   MMU_TLB_ENTRY_PAGE_SIZE_4M_BYTES    =6,
   MMU_TLB_ENTRY_PAGE_SIZE_16M_BYTES   =7,
   MMU_TLB_ENTRY_PAGE_SIZE_64M_BYTES   =8,
   MMU_TLB_ENTRY_PAGE_SIZE_256M_BYTES  =9,
   MMU_TLB_ENTRY_PAGE_SIZE_1G_BYTES    =10,
   MMU_TLB_ENTRY_PAGE_SIZE_4G_BYTES    =11

}MMU_TLB_Entry_Page_Size_T;


typedef enum
{
   MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,
   MMU_TLB_MEMORY_COHERENCE_REQUIRED
}MMU_TLB_Coherence_T;

typedef enum
{
   MMU_ASSIST_CONFIGURATION_POSITION_WRITE_THROUGH                   =10, //[    10 ] Write Through
   MMU_ASSIST_CONFIGURATION_POSITION_CACHE_INHIBITED                 =11, //[    11 ] Cache Inhibit
   MMU_ASSIST_CONFIGURATION_POSITION_GUARDED                         =12, //[    12 ] Guarded
   MMU_ASSIST_CONFIGURATION_POSITION_ENDIANNESS                      =13, //[    13 ] Endianness
   MMU_ASSIST_CONFIGURATION_POSITION_USER_BITS                       =14, //[ 17:14 ] User Defined bits
   MMU_ASSIST_CONFIGURATION_POSITION_USER_EXECUTE_PERMISSION         =18, //[    18 ] user execute permission
   MMU_ASSIST_CONFIGURATION_POSITION_SUPERVISOR_EXECUTE_PERMISSION   =19, //[    19 ] supervisor execute permission
   MMU_ASSIST_CONFIGURATION_POSITION_USER_WRITE_PERMISSION           =20, //[    20 ] user write permission
   MMU_ASSIST_CONFIGURATION_POSITION_SUPERVISOR_WRITE_PERMISSION     =21, //[    21 ] supervisor write permission
   MMU_ASSIST_CONFIGURATION_POSITION_USER_READ_PERMISSION            =22, //[    22 ] user read permission
   MMU_ASSIST_CONFIGURATION_POSITION_SUPERVISOR_READ_PERMISSION      =23, //[    23 ] uspervisor read permission
   MMU_ASSIST_CONFIGURATION_POSITION_VLE                             =24 //[    24 ] PowerPC Variable Length Encoding page

} MMU_Assist_Configuration_Position_T;

typedef enum
{
   MMU_ASSIST_CONFIGURATION_WIDTH_WRITE_THROUGH                      = 1, //[    10 ] Write Through
   MMU_ASSIST_CONFIGURATION_WIDTH_CACHE_INHIBITED                    = 1, //[    11 ] Cache Inhibit
   MMU_ASSIST_CONFIGURATION_WIDTH_GUARDED                            = 1, //[    12 ] Guarded
   MMU_ASSIST_CONFIGURATION_WIDTH_ENDIANNESS                         = 1, //[    13 ] Endianness
   MMU_ASSIST_CONFIGURATION_WIDTH_USER_BITS                          = 4, //[ 17:14 ] User Defined bits
   MMU_ASSIST_CONFIGURATION_WIDTH_USER_EXECUTE_PERMISSION            = 1, //[    18 ] user execute permission
   MMU_ASSIST_CONFIGURATION_WIDTH_SUPERVISOR_EXECUTE_PERMISSION      = 1, //[    19 ] supervisor execute permission
   MMU_ASSIST_CONFIGURATION_WIDTH_USER_WRITE_PERMISSION              = 1, //[    20 ] user write permission
   MMU_ASSIST_CONFIGURATION_WIDTH_SUPERVISOR_WRITE_PERMISSION        = 1, //[    21 ] supervisor write permission
   MMU_ASSIST_CONFIGURATION_WIDTH_USER_READ_PERMISSION               = 1, //[    22 ] user read permission
   MMU_ASSIST_CONFIGURATION_WIDTH_SUPERVISOR_READ_PERMISSION         = 1, //[    23 ] uspervisor read permission
   MMU_ASSIST_CONFIGURATION_WIDTH_VLE                                = 1 //[    24 ] PowerPC Variable Length Encoding page

} MMU_Assist_Configuration_Width_T;


typedef enum
{
   MMU_TLB_STANDARD_BOOKE_PAGE,   // 0 = Page is a standard BookE page
   MMU_TLB_POWERPC_VLE_PAGE       // 1 = Page is a PowerPC VLE page

}MMU_TLB_Page_Type_T;

typedef enum
{
   MMU_TLB_ENTRY_INVALDATE_UNPROTECTED,
   MMU_TLB_ENTRY_INVALDATE_PROTECTED

}MMU_TLB_Entry_Invaldate_T;


typedef enum
{
   MMU_TLB_WRITE_BACK,
   MMU_TLB_WRITE_THROUGH

}MMU_TLB_Write_T;

typedef enum
{
   MMU_TLB_CACHEABLE,
   MMU_TLB_CACHE_INHIBIT

}MMU_TLB_Cache_T;

typedef enum
{
   MMU_TLB_GUARDED_DISABLED,
   MMU_TLB_GUARDED_ENABLED

} MMU_TLB_Guarded_T;


typedef enum
{
   MMU_TLB_ENDIANNESS_BIG_ENDIAN,
   MMU_TLB_ENDIANNESS_LITTLE_ENDIAN

} MMU_TLB_Endianness_T;


typedef enum
{
   MMU_TLB_USER_DEFINED_OPERATION_NONE,
   MMU_TLB_USER_DEFINED_OPERATION_REGISTER_VERIFY,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_0,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_1,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_2,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_3,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_4,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_5,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_6,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_7,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_8,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_9,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_10,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_11,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_12,
   MMU_TLB_USER_DEFINED_OPERATION_RESERVED_13

} MMU_TLB_User_Defined_Operation_T;


typedef enum
{
   MMU_TLB_PERMISSION_NOT_ALLOWED,
   MMU_TLB_PERMISSION_ALLOWED

}MMU_TLB_Permission_T;



//=============================================================================
// MMU_MAS_Initialize_Device
//
// @func Initialize the MMU MAS registers based on the configurations defined by
// the user.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void MMU_MAS_Initialize_Device( void);

//=============================================================================
// MMU_MAS_Verify_Register
//
// @func Test the MMU registers against the initial values. And refresh the 
//    registers if the values are not correct.
//
//   Verify that the MMU register values have not changed since power-up.
//   If a register's contents do not match its power-up initialization
//   value, write the init value to the register before returning to
//   report the failure.
//   The procedure to read the contents of a single TLB entry is 
//   as follows :
//   1. Write MAS0 SPR with appropriate value to select a TLB entry
//   2. Use tlbre instruction to read the contents of one TLB entry 
//      into MAS1, MAS2 and MAS3 Registers which can read by mfspr
//      instruction. 
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc status of the test
// @flag true | test passed
// @flag false | test failed
//
// @end
//=============================================================================
bool MMU_MAS_Verify_Register( void );


#endif // DD_MMU_H

