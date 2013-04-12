#ifndef IO_CONFIG_MMU_H
#define IO_CONFIG_MMU_H

    //PID register default init values
    //  24:31  PID      process id
 #define MMU_PID_INIT   ((uint32_t)0x0)

    //    :30   TLBCAM_FI  TBL1 flash invalidate  1 = invalidate
 #define MMU_CSR0_INIT   ((uint32_t)0x0)


   //Choose VLE or BookE option
 #define ENCODING_FORMAT MMU_TLB_POWERPC_VLE_PAGE

    //Choose VLE or BookE option
 #define ENCODING_ENDIANNESS MMU_TLB_ENDIANNESS_BIG_ENDIAN
 
 #define MMU_MAS_Memory_Coherence       MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED
 


 #define MTSA_INSTRUCTION_CACHE_INIT\
	(L1CACHE_Set_Initial_Enable(0, false) | L1CACHE_Set_Cache_Type(0, L1CACHE_CACHE_TYPE_INSTRUCTION))
	

 #define MTSA_DATA_CACHE_INIT\
	(L1CACHE_Set_Initial_Enable(0, false) | L1CACHE_Set_Cache_Type(0, L1CACHE_CACHE_TYPE_DATA))
	
//MMU_TLB_default 

#define MMU_MAS_ADDRESS_DEFAULT (0xFFFFFFFF)
#define MMU_MAS_TLB_ENTRY_Default_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_4K_BYTES
#define MMU_MAS_TLB_ENTRY_Default_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_Default_Write_Access   MMU_TLB_WRITE_BACK
#define MMU_MAS_TLB_ENTRY_Default_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_Default_Guarded        MMU_TLB_GUARDED_DISABLED
#define MMU_MAS_TLB_ENTRY_Default_User_Execute_Permission        MMU_TLB_PERMISSION_NOT_ALLOWED
#define MMU_MAS_TLB_ENTRY_Default_User_Write_Permission        MMU_TLB_PERMISSION_NOT_ALLOWED
#define MMU_MAS_TLB_ENTRY_Default_User_Read_Permission        MMU_TLB_PERMISSION_NOT_ALLOWED
#define MMU_MAS_TLB_ENTRY_Default_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_NOT_ALLOWED
#define MMU_MAS_TLB_ENTRY_Default_Supervisor_Write_Permission        MMU_TLB_PERMISSION_NOT_ALLOWED
#define MMU_MAS_TLB_ENTRY_Default_Supervisor_Read_Permission        MMU_TLB_PERMISSION_NOT_ALLOWED

//MMU_TLB_ENTRY_0
#define FLASH_PML_BOOT_64K_TLB_Index    MMU_TLB_ENTRY_INDEX_0
#define MMU_TLB_ENTRY_0_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_0_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_0_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_0_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_0_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_0_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_0_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_0_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_0_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_0_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_0_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_0_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED


#define FLASH_PML_BOOT_64K_EFFECTIVE_ADDRESS         ( 0x00000000 )
#define FLASH_PML_BOOT_64K_REAL_ADDRESS              ( 0x00000000 )

//End MMU_TLB_ENTRY_0

//MMU_TLB_ENTRY_1	

#define INTERNAL_RAM_TLB_Index   MMU_TLB_ENTRY_INDEX_1
#define MMU_TLB_ENTRY_1_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_1_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_256K_BYTES
#define MMU_MAS_TLB_ENTRY_1_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_1_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_1_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_1_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_1_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_1_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_1_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_1_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_1_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_1_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
			
#define INTERNAL_RAM_EFFECTIVE_ADDRESS          ( 0x40000000 )
#define INTERNAL_RAM_REAL_ADDRESS               ( 0x40000000 )

//End MMU_TLB_ENTRY_1

//MMU_TLB_ENTRY_2		
#define MMR_REGISTER_0_TLB_Index         MMU_TLB_ENTRY_INDEX_2

#define MMU_TLB_ENTRY_2_TID_INIT   ((uint8_t)0x0)


#define MMU_MAS_TLB_ENTRY_2_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_1M_BYTES
#define MMU_MAS_TLB_ENTRY_2_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_2_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_2_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_2_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_2_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_2_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_2_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_2_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_2_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_2_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

			
#define MMR_REGISTER_0_EFFECTIVE_ADDRESS      ( 0xC3F80000 )
#define MMR_REGISTER_0_REAL_ADDRESS           ( 0xC3F80000 )

//End MMU_TLB_ENTRY_2			
			
//MMU_TLB_ENTRY_3
#define MMR_REGISTER_1_TLB_Index  MMU_TLB_ENTRY_INDEX_3

#define MMU_TLB_ENTRY_3_TID_INIT   ((uint8_t)0x0)


#define MMU_MAS_TLB_ENTRY_3_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_1M_BYTES
#define MMU_MAS_TLB_ENTRY_3_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_3_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_3_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_3_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_3_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_3_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_3_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_3_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_3_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_3_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

			
#define MMR_REGISTER_1_EFFECTIVE_ADDRESS      ( 0xFFF00000 )
#define MMR_REGISTER_1_REAL_ADDRESS           ( 0xFFF00000 )

#define MMU_TLB_EFFECTIVE_ADDRESS_3    ( MMR_REGISTER_1_EFFECTIVE_ADDRESS )
#define MMU_TLB_REAL_ADDRESS_3          ( MMR_REGISTER_1_REAL_ADDRESS )
//End MMU_TLB_ENTRY_3			

//MMU_TLB_ENTRY_4	
#define FLASH_CODE_1_256K_TLB_Index MMU_TLB_ENTRY_INDEX_4

#define MMU_TLB_ENTRY_4_TID_INIT   ((uint8_t)0x0)



#define MMU_MAS_TLB_ENTRY_4_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_256K_BYTES
#define MMU_MAS_TLB_ENTRY_4_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_4_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_4_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_4_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_4_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_4_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_4_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_4_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_4_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_4_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

			
#define FLASH_CODE_1_256K_EFFECTIVE_ADDRESS   ( 0x00040000 )
#define FLASH_CODE_1_256K_REAL_ADDRESS        ( 0x00040000 )

#define MMU_TLB_EFFECTIVE_ADDRESS_4     ( FLASH_CODE_1_256K_EFFECTIVE_ADDRESS )
#define MMU_TLB_REAL_ADDRESS_4          ( FLASH_CODE_1_256K_REAL_ADDRESS )
//End MMU_TLB_ENTRY_4

//MMU_TLB_ENTRY_5	
#define FLASH_CODE_2_256K_TLB_Index MMU_TLB_ENTRY_INDEX_5
#define MMU_TLB_ENTRY_5_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_5_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_256K_BYTES
#define MMU_MAS_TLB_ENTRY_5_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_5_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_5_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_5_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_5_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_5_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_5_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_5_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_5_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_5_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

			
#define FLASH_CODE_2_256K_EFFECTIVE_ADDRESS      ( 0x00080000 )
#define FLASH_CODE_2_256K_REAL_ADDRESS           ( 0x00080000 )

//End MMU_TLB_ENTRY_5


//MMU_TLB_ENTRY_6	
#define FLASH_CODE_3_256K_TLB_Index MMU_TLB_ENTRY_INDEX_6
#define MMU_TLB_ENTRY_6_TID_INIT   ((uint8_t)0x0)


#define MMU_MAS_TLB_ENTRY_6_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_256K_BYTES
#define MMU_MAS_TLB_ENTRY_6_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_6_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_6_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_6_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_6_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_6_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_6_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_6_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_6_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_6_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

		
#define FLASH_CODE_3_256K_EFFECTIVE_ADDRESS      ( 0x000C0000 )
#define FLASH_CODE_3_256K_REAL_ADDRESS           ( 0x000C0000 )

//End MMU_TLB_ENTRY_6

//MMU_TLB_ENTRY_7
#define FLASH_CODE_4_1M_TLB_Index  MMU_TLB_ENTRY_INDEX_7

#define MMU_TLB_ENTRY_7_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_7_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_1M_BYTES
#define MMU_MAS_TLB_ENTRY_7_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_7_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_7_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_7_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_7_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_7_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_7_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_7_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_7_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_7_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

#define FLASH_CODE_4_1M_EFFECTIVE_ADDRESS      ( 0x00100000 )
#define FLASH_CODE_4_1M_REAL_ADDRESS           ( 0x00100000 )

//End MMU_TLB_ENTRY_7

//MMU_TLB_ENTRY_8	
#define FLASH_EEPROM_64K_TLB_Index MMU_TLB_ENTRY_INDEX_8

#define MMU_TLB_ENTRY_8_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_8_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_8_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_8_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_8_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_8_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_8_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_8_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_8_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_8_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_8_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_8_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED


#define FLASH_EEPROM_64K_EFFECTIVE_ADDRESS      ( 0x00010000 )
#define FLASH_EEPROM_64K_REAL_ADDRESS           ( 0x00010000 )

//End MMU_TLB_ENTRY_8

//MMU_TLB_ENTRY_9 
#define MMU_TLB_ENTRY_9_TLB_Index MMU_TLB_ENTRY_INDEX_9

#define MMU_TLB_ENTRY_9_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_9_Page_Size   MMU_MAS_TLB_ENTRY_Default_Page_Size
#define MMU_MAS_TLB_ENTRY_9_Invaldation_Protect   MMU_MAS_TLB_ENTRY_Default_Invaldation_Protect
#define MMU_MAS_TLB_ENTRY_9_Write_Access   MMU_MAS_TLB_ENTRY_Default_Write_Access
#define MMU_MAS_TLB_ENTRY_9_Cache_Access   MMU_MAS_TLB_ENTRY_Default_Cache_Access
#define MMU_MAS_TLB_ENTRY_9_Guarded        MMU_MAS_TLB_ENTRY_Default_Guarded
#define MMU_MAS_TLB_ENTRY_9_User_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_User_Execute_Permission
#define MMU_MAS_TLB_ENTRY_9_User_Write_Permission        MMU_MAS_TLB_ENTRY_Default_User_Write_Permission
#define MMU_MAS_TLB_ENTRY_9_User_Read_Permission        MMU_MAS_TLB_ENTRY_Default_User_Read_Permission
#define MMU_MAS_TLB_ENTRY_9_Supervisor_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Execute_Permission
#define MMU_MAS_TLB_ENTRY_9_Supervisor_Write_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Write_Permission
#define MMU_MAS_TLB_ENTRY_9_Supervisor_Read_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Read_Permission


#define MMU_MAS_TLB_ENTRY_9_EFFECTIVE_ADDRESS      ( MMU_MAS_ADDRESS_DEFAULT )
#define MMU_MAS_TLB_ENTRY_9_REAL_ADDRESS           ( MMU_MAS_ADDRESS_DEFAULT )



//End MMU_TLB_ENTRY_9

//MMU_TLB_ENTRY_10	
#define MMU_TLB_ENTRY_10_TLB_Index MMU_TLB_ENTRY_INDEX_10
#define MMU_TLB_ENTRY_10_TID_INIT   ((uint8_t)0x0)


#define MMU_MAS_TLB_ENTRY_10_Page_Size   MMU_MAS_TLB_ENTRY_Default_Page_Size
#define MMU_MAS_TLB_ENTRY_10_Invaldation_Protect   MMU_MAS_TLB_ENTRY_Default_Invaldation_Protect
#define MMU_MAS_TLB_ENTRY_10_Write_Access   MMU_MAS_TLB_ENTRY_Default_Write_Access
#define MMU_MAS_TLB_ENTRY_10_Cache_Access   MMU_MAS_TLB_ENTRY_Default_Cache_Access
#define MMU_MAS_TLB_ENTRY_10_Guarded        MMU_MAS_TLB_ENTRY_Default_Guarded
#define MMU_MAS_TLB_ENTRY_10_User_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_User_Execute_Permission
#define MMU_MAS_TLB_ENTRY_10_User_Write_Permission        MMU_MAS_TLB_ENTRY_Default_User_Write_Permission
#define MMU_MAS_TLB_ENTRY_10_User_Read_Permission        MMU_MAS_TLB_ENTRY_Default_User_Read_Permission
#define MMU_MAS_TLB_ENTRY_10_Supervisor_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Execute_Permission
#define MMU_MAS_TLB_ENTRY_10_Supervisor_Write_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Write_Permission
#define MMU_MAS_TLB_ENTRY_10_Supervisor_Read_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Read_Permission


#define MMU_MAS_TLB_ENTRY_10_EFFECTIVE_ADDRESS      ( MMU_MAS_ADDRESS_DEFAULT )
#define MMU_MAS_TLB_ENTRY_10_REAL_ADDRESS           ( MMU_MAS_ADDRESS_DEFAULT )



//End MMU_TLB_ENTRY_10

//===========================================================================
// MMU configuration for CAL(Reference Page and Working Page)
//===========================================================================
//Reference Page below
//MMU_TLB_ENTRY_11	
#define FLASH_CAL_1_64K_TLB_Index MMU_TLB_ENTRY_INDEX_11

#define MMU_TLB_ENTRY_11_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_11_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_11_Page_Type  MMU_TLB_POWERPC_VLE_PAGE
#define MMU_MAS_TLB_ENTRY_11_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_11_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_11_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_11_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_11_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

#define FLASH_CAL_1_64K_EFFECTIVE_ADDRESS   ( 0x00020000 )
#define FLASH_CAL_1_64K_REAL_ADDRESS        ( 0x00020000 )

//End MMU_TLB_ENTRY_11

//MMU_TLB_ENTRY_12
#define FLASH_CAL_2_64K_TLB_Index MMU_TLB_ENTRY_INDEX_12


#define MMU_TLB_ENTRY_12_TID_INIT   ((uint8_t)0x0)


#define MMU_MAS_TLB_ENTRY_12_Page_Size   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_12_Page_Type  MMU_TLB_POWERPC_VLE_PAGE
#define MMU_MAS_TLB_ENTRY_12_Invaldation_Protect   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_12_Write_Access   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_12_Cache_Access   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_12_Guarded        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_12_User_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_User_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_User_Read_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission        MMU_TLB_PERMISSION_ALLOWED

		
#define FLASH_CAL_2_64K_EFFECTIVE_ADDRESS   ( 0x00030000 )
#define FLASH_CAL_2_64K_REAL_ADDRESS        ( 0x00030000 )

//End MMU_TLB_ENTRY_12

// Working Page - LCI Below
//MMU_TLB_ENTRY_11		
#define FLASH_CAL_1_WORKING_PAGE_64K_TLB_Index MMU_TLB_ENTRY_INDEX_11


#define MMU_MAS_TLB_ENTRY_11_Page_Size_LCI   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_11_Page_Type_LCI   MMU_TLB_POWERPC_VLE_PAGE
#define MMU_MAS_TLB_ENTRY_11_Invaldation_Protect_LCI   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_11_Write_Access_LCI   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_11_Cache_Access_LCI   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_11_Guarded_LCI        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_11_User_Execute_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_User_Write_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_User_Read_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED

			
#define FLASH_CAL_1_WORKING_PAGE_64K_EFFECTIVE_ADDRESS   ( 0x00020000 )
#define FLASH_CAL_1_WORKING_PAGE_64K_REAL_ADDRESS        ( 0x40010000 )
//End MMU_TLB_ENTRY_11

//MMU_TLB_ENTRY_12
#define FLASH_CAL_2_WORKING_PAGE_64K_TLB_Index MMU_TLB_ENTRY_INDEX_12

#define MMU_MAS_TLB_ENTRY_12_Page_Size_LCI   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_12_Page_Type_LCI   MMU_TLB_POWERPC_VLE_PAGE
#define MMU_MAS_TLB_ENTRY_12_Invaldation_Protect_LCI   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_12_Write_Access_LCI   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_12_Cache_Access_LCI   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_12_Guarded_LCI        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_12_User_Execute_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_User_Write_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_User_Read_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED

		
#define FLASH_CAL_2_WORKING_PAGE_64K_EFFECTIVE_ADDRESS   ( 0x00030000 )
#define FLASH_CAL_2_WORKING_PAGE_64K_REAL_ADDRESS        ( 0x40020000 )
//End MMU_TLB_ENTRY_12

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
#define FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_TLB_Index MMU_TLB_ENTRY_INDEX_11


#define MMU_MAS_TLB_ENTRY_11_Page_Size_VertiCAL   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_11_Page_Type_VertiCAL   MMU_TLB_POWERPC_VLE_PAGE
#define MMU_MAS_TLB_ENTRY_11_Invaldation_Protect_VertiCAL    MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_11_Write_Access_VertiCAL    MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_11_Cache_Access_VertiCAL     MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_11_Guarded_VertiCAL          MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_11_User_Execute_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_User_Write_Permission_VertiCAL         MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_User_Read_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
	
#define FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS   ( 0x00020000 )
#define FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_REAL_ADDRESS        ( 0x30000000 )
//End MMU_TLB_ENTRY_11

//MMU_TLB_ENTRY_12
#define FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_TLB_Index MMU_TLB_ENTRY_INDEX_12


#define MMU_MAS_TLB_ENTRY_12_Page_Size_VertiCAL   MMU_TLB_ENTRY_PAGE_SIZE_64K_BYTES
#define MMU_MAS_TLB_ENTRY_12_Page_Type_VertiCAL   MMU_TLB_POWERPC_VLE_PAGE
#define MMU_MAS_TLB_ENTRY_12_Invaldation_Protect_VertiCAL    MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_12_Write_Access_VertiCAL    MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_12_Cache_Access_VertiCAL     MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_12_Guarded_VertiCAL          MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_12_User_Execute_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_User_Write_Permission_VertiCAL         MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_User_Read_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission_VertiCAL          MMU_TLB_PERMISSION_ALLOWED


#define FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS   ( 0x00030000 )
#define FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_REAL_ADDRESS        ( 0x30010000 )
//End MMU_TLB_ENTRY_12

//MMU_TLB_ENTRY_13	
#define MMU_TLB_ENTRY_13_TLB_Index   MMU_TLB_ENTRY_INDEX_13

#define MMU_TLB_ENTRY_13_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_13_Page_Size   MMU_MAS_TLB_ENTRY_Default_Page_Size
#define MMU_MAS_TLB_ENTRY_13_Invaldation_Protect   MMU_MAS_TLB_ENTRY_Default_Invaldation_Protect
#define MMU_MAS_TLB_ENTRY_13_Write_Access   MMU_MAS_TLB_ENTRY_Default_Write_Access
#define MMU_MAS_TLB_ENTRY_13_Cache_Access   MMU_MAS_TLB_ENTRY_Default_Cache_Access
#define MMU_MAS_TLB_ENTRY_13_Guarded        MMU_MAS_TLB_ENTRY_Default_Guarded
#define MMU_MAS_TLB_ENTRY_13_User_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_User_Execute_Permission
#define MMU_MAS_TLB_ENTRY_13_User_Write_Permission        MMU_MAS_TLB_ENTRY_Default_User_Write_Permission
#define MMU_MAS_TLB_ENTRY_13_User_Read_Permission        MMU_MAS_TLB_ENTRY_Default_User_Read_Permission
#define MMU_MAS_TLB_ENTRY_13_Supervisor_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Execute_Permission
#define MMU_MAS_TLB_ENTRY_13_Supervisor_Write_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Write_Permission
#define MMU_MAS_TLB_ENTRY_13_Supervisor_Read_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Read_Permission


#define MMU_MAS_TLB_ENTRY_13_EFFECTIVE_ADDRESS      ( MMU_MAS_ADDRESS_DEFAULT )
#define MMU_MAS_TLB_ENTRY_13_REAL_ADDRESS           ( MMU_MAS_ADDRESS_DEFAULT )



//End MMU_TLB_ENTRY_13

//MMU_TLB_ENTRY_14	
#define MMU_TLB_ENTRY_14_TLB_Index   MMU_TLB_ENTRY_INDEX_14

#define MMU_TLB_ENTRY_14_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_14_Page_Size   MMU_MAS_TLB_ENTRY_Default_Page_Size
#define MMU_MAS_TLB_ENTRY_14_Invaldation_Protect   MMU_MAS_TLB_ENTRY_Default_Invaldation_Protect
#define MMU_MAS_TLB_ENTRY_14_Write_Access   MMU_MAS_TLB_ENTRY_Default_Write_Access
#define MMU_MAS_TLB_ENTRY_14_Cache_Access   MMU_MAS_TLB_ENTRY_Default_Cache_Access
#define MMU_MAS_TLB_ENTRY_14_Guarded        MMU_MAS_TLB_ENTRY_Default_Guarded
#define MMU_MAS_TLB_ENTRY_14_User_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_User_Execute_Permission
#define MMU_MAS_TLB_ENTRY_14_User_Write_Permission        MMU_MAS_TLB_ENTRY_Default_User_Write_Permission
#define MMU_MAS_TLB_ENTRY_14_User_Read_Permission        MMU_MAS_TLB_ENTRY_Default_User_Read_Permission
#define MMU_MAS_TLB_ENTRY_14_Supervisor_Execute_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Execute_Permission
#define MMU_MAS_TLB_ENTRY_14_Supervisor_Write_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Write_Permission
#define MMU_MAS_TLB_ENTRY_14_Supervisor_Read_Permission        MMU_MAS_TLB_ENTRY_Default_Supervisor_Read_Permission


#define MMU_MAS_TLB_ENTRY_14_EFFECTIVE_ADDRESS      ( MMU_MAS_ADDRESS_DEFAULT )
#define MMU_MAS_TLB_ENTRY_14_REAL_ADDRESS           ( MMU_MAS_ADDRESS_DEFAULT )


//End MMU_TLB_ENTRY_14

//MMU_TLB_ENTRY_15 - LCI only
#define FLASH_CAL_WORKING_PAGE_BACKUP_128K_TLB_Index MMU_TLB_ENTRY_INDEX_15

#define MMU_TLB_ENTRY_15_TID_INIT   ((uint8_t)0x0)

#define MMU_MAS_TLB_ENTRY_15_Page_Size_LCI   MMU_TLB_ENTRY_PAGE_SIZE_1M_BYTES
#define MMU_MAS_TLB_ENTRY_15_Invaldation_Protect_LCI   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_15_Write_Access_LCI   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_15_Cache_Access_LCI   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_15_Guarded_LCI        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_15_User_Execute_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_User_Write_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_User_Read_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_Supervisor_Execute_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_Supervisor_Write_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_Supervisor_Read_Permission_LCI        MMU_TLB_PERMISSION_ALLOWED


#define FLASH_CAL_WORKING_PAGE_BACKUP_128K_EFFECTIVE_ADDRESS      ( 0x00200000 )
#define FLASH_CAL_WORKING_PAGE_BACKUP_128K_REAL_ADDRESS           ( 0x00200000 )
			
#define MMU_TLB_ENTRY_15_INIT                    ( FLASH_CAL_WORKING_PAGE_BACKUP_128K )
#define MMU_TLB_EFFECTIVE_ADDRESS_15_INIT        ( FLASH_CAL_WORKING_PAGE_BACKUP_128K_EFFECTIVE_ADDRESS )
#define MMU_TLB_REAL_ADDRESS_15_INIT             ( FLASH_CAL_WORKING_PAGE_BACKUP_128K_REAL_ADDRESS )
//End MMU_TLB_ENTRY_15

//MMU_TLB_ENTRY_15 - Vertical only
#define EXTERNAL_RAM_128K_TLB_Index MMU_TLB_ENTRY_INDEX_15


#define MMU_MAS_TLB_ENTRY_15_Page_Size_VertiCAL   MMU_TLB_ENTRY_PAGE_SIZE_1M_BYTES
#define MMU_MAS_TLB_ENTRY_15_Page_Type_VertiCAL  MMU_TLB_POWERPC_VLE_PAGE
#define MMU_MAS_TLB_ENTRY_15_Invaldation_Protect_VertiCAL   MMU_TLB_ENTRY_INVALDATE_PROTECTED
#define MMU_MAS_TLB_ENTRY_15_Write_Access_VertiCAL   MMU_TLB_WRITE_THROUGH
#define MMU_MAS_TLB_ENTRY_15_Cache_Access_VertiCAL   MMU_TLB_CACHE_INHIBIT
#define MMU_MAS_TLB_ENTRY_15_Guarded_VertiCAL        MMU_TLB_GUARDED_ENABLED
#define MMU_MAS_TLB_ENTRY_15_User_Execute_Permission_VertiCAL        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_User_Write_Permission_VertiCAL        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_User_Read_Permission_VertiCAL        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_Supervisor_Execute_Permission_VertiCAL        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_Supervisor_Write_Permission_VertiCAL        MMU_TLB_PERMISSION_ALLOWED
#define MMU_MAS_TLB_ENTRY_15_Supervisor_Read_Permission_VertiCAL        MMU_TLB_PERMISSION_ALLOWED

#define EXTERNAL_RAM_128K_EFFECTIVE_ADDRESS      ( 0x30000000 )
#define EXTERNAL_RAM_128K_REAL_ADDRESS           ( 0x30000000 )
//End MMU_TLB_ENTRY_15


//=============================================================================
// MMU_MAS_0_INITIAL
//=============================================================================
//MMU_TLB_ENTRY_0	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_PML_BOOT_64K;
//MMU_TLB_ENTRY_1	
extern const MMU_MAS0_T  MMU_MAS_0_INTERNAL_RAM ;
//MMU_TLB_ENTRY_2	
extern const MMU_MAS0_T  MMU_MAS_0_MMR_REGISTER_0;

//MMU_TLB_ENTRY_3	
extern const MMU_MAS0_T  MMU_MAS_0_MMR_REGISTER_1;

//MMU_TLB_ENTRY_4	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_1_256K;

//MMU_TLB_ENTRY_5	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_2_256K;

//MMU_TLB_ENTRY_6	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_3_256K ;

//MMU_TLB_ENTRY_7	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_4_1M ;

//MMU_TLB_ENTRY_8	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_EEPROM_64K;

//MMU_TLB_ENTRY_9	
extern const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_9;

//MMU_TLB_ENTRY_10	
extern const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_10;

//Reference Page below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_1_64K;

//Reference Page below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_2_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_1_WORKING_PAGE_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_2_WORKING_PAGE_64K ;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K;

//MMU_TLB_ENTRY_13	
extern const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_13;

//MMU_TLB_ENTRY_14	
extern const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_14;

//MMU_TLB_ENTRY_15	
extern const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_WORKING_PAGE_BACKUP_128K;

//MMU_TLB_ENTRY_15	
extern const MMU_MAS0_T  MMU_MAS_0_EXTERNAL_RAM_128K;

//=============================================================================
// MMU_MAS_1_INITIAL
//=============================================================================
//MMU_TLB_ENTRY_0	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_PML_BOOT_64K;

//MMU_TLB_ENTRY_1	
extern const MMU_MAS1_T MMU_MAS_1_INTERNAL_RAM;

//MMU_TLB_ENTRY_2
extern const MMU_MAS1_T MMU_MAS_1_MMR_REGISTER_0;

//MMU_TLB_ENTRY_3
extern const MMU_MAS1_T MMU_MAS_1_MMR_REGISTER_1;

//MMU_TLB_ENTRY_4
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_1_256K;

//MMU_TLB_ENTRY_5
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_2_256K ;

//MMU_TLB_ENTRY_6
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_3_256K;

//MMU_TLB_ENTRY_7
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_4_1M;

//MMU_TLB_ENTRY_8
extern const MMU_MAS1_T MMU_MAS_1_FLASH_EEPROM_64K;

//MMU_TLB_ENTRY_9
extern const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_9;

//MMU_TLB_ENTRY_10
extern const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_10;

//Reference Page below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_1_64K;

//Reference Page below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_2_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_1_WORKING_PAGE_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_2_WORKING_PAGE_64K;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K;

//MMU_TLB_ENTRY_13	
extern const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_13;

//MMU_TLB_ENTRY_14	
extern const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_14;

//LCI only
//MMU_TLB_ENTRY_15	
extern const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_WORKING_PAGE_BACKUP_128K;

//VertiCAL only
//MMU_TLB_ENTRY_15	
extern const MMU_MAS1_T MMU_MAS_1_EXTERNAL_RAM_128K;

//=============================================================================
// MMU_MAS_2_INITIAL
//=============================================================================
//MMU_TLB_ENTRY_0	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_PML_BOOT_64K;

//MMU_TLB_ENTRY_1	
extern const MMU_MAS2_T MMU_MAS_2_INTERNAL_RAM;

//MMU_TLB_ENTRY_2
extern const MMU_MAS2_T MMU_MAS_2_MMR_REGISTER_0;

//MMU_TLB_ENTRY_3
extern const MMU_MAS2_T MMU_MAS_2_MMR_REGISTER_1;


//MMU_TLB_ENTRY_4
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_1_256K;


//MMU_TLB_ENTRY_5
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_2_256K;

//MMU_TLB_ENTRY_6
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_3_256K;


//MMU_TLB_ENTRY_7
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_4_1M;


//MMU_TLB_ENTRY_8
extern const MMU_MAS2_T MMU_MAS_2_FLASH_EEPROM_64K;

//MMU_TLB_ENTRY_9
extern const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_9 ;

//MMU_TLB_ENTRY_10
extern const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_10;

//Reference Page below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_1_64K;


//Reference Page below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_2_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_1_WORKING_PAGE_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_2_WORKING_PAGE_64K;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K  ;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K;

//MMU_TLB_ENTRY_13	
extern const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_13;


//MMU_TLB_ENTRY_14	
extern const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_14 ;


//LCI only
//MMU_TLB_ENTRY_15	
extern const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_WORKING_PAGE_BACKUP_128K;


//VertiCAL only
//MMU_TLB_ENTRY_15	
extern const MMU_MAS2_T MMU_MAS_2_EXTERNAL_RAM_128K;

//=============================================================================
// MMU_MAS_3_INITIAL
//=============================================================================

 //MMU_TLB_ENTRY_0	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_PML_BOOT_64K;
			  
//MMU_TLB_ENTRY_1	
 extern const MMU_MAS3_T MMU_MAS_3_INTERNAL_RAM;

//MMU_TLB_ENTRY_2
extern  const MMU_MAS3_T MMU_MAS_3_MMR_REGISTER_0;

//MMU_TLB_ENTRY_3
 extern const MMU_MAS3_T MMU_MAS_3_MMR_REGISTER_1;

//MMU_TLB_ENTRY_4
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_1_256K;

//MMU_TLB_ENTRY_5
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_2_256K;

//MMU_TLB_ENTRY_6
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_3_256K;

//MMU_TLB_ENTRY_7
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_4_1M;

//MMU_TLB_ENTRY_8
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_EEPROM_64K;

//MMU_TLB_ENTRY_9
 extern const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_9;

//MMU_TLB_ENTRY_10
 extern const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_10;

//Reference Page below
//MMU_TLB_ENTRY_11	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_1_64K;

//Reference Page below
//MMU_TLB_ENTRY_12	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_2_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_1_WORKING_PAGE_64K;

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_2_WORKING_PAGE_64K;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K;

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K ;

//MMU_TLB_ENTRY_13	
 extern const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_13 ;

//MMU_TLB_ENTRY_14	
 extern const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_14;

//LCI only
//MMU_TLB_ENTRY_15	
 extern const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_WORKING_PAGE_BACKUP_128K;

//VertiCAL only
//MMU_TLB_ENTRY_15	
extern const MMU_MAS3_T MMU_MAS_3_EXTERNAL_RAM_128K ;

//=============================================================================
// MMU_MAS_4_INITIAL
//=============================================================================
extern const MMU_MAS4_T MMU_MAS_4_INITIAL ;

//=============================================================================
// MMU_MAS_6_INITIAL
//=============================================================================
extern const MMU_MAS6_T MMU_MAS_6_INITIAL;


#endif // IO_CONFIG_MMU_H

