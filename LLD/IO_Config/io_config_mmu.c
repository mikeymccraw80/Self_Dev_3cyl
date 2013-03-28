
#include "dd_mmu.h"
#include "io_config_mmu.h"

//=============================================================================
// MMU_MAS_0_INITIAL
//=============================================================================
//MMU_TLB_ENTRY_0	
const MMU_MAS0_T  MMU_MAS_0_FLASH_PML_BOOT_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_PML_BOOT_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };
//MMU_TLB_ENTRY_1	
const MMU_MAS0_T  MMU_MAS_0_INTERNAL_RAM = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         INTERNAL_RAM_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };
//MMU_TLB_ENTRY_2	
const MMU_MAS0_T  MMU_MAS_0_MMR_REGISTER_0 = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         MMR_REGISTER_0_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_3	
const MMU_MAS0_T  MMU_MAS_0_MMR_REGISTER_1 = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         MMR_REGISTER_1_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_4	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_1_256K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CODE_1_256K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_5	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_2_256K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CODE_2_256K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_6	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_3_256K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CODE_3_256K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_7	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CODE_4_1M = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CODE_4_1M_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_8	
const MMU_MAS0_T  MMU_MAS_0_FLASH_EEPROM_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_EEPROM_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_9	
const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_9 = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         MMU_TLB_ENTRY_9_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_10	
const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_10 = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         MMU_TLB_ENTRY_10_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//Reference Page below
//MMU_TLB_ENTRY_11	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_1_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CAL_1_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//Reference Page below
//MMU_TLB_ENTRY_12	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_2_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CAL_2_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };



// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_1_WORKING_PAGE_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CAL_1_WORKING_PAGE_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_2_WORKING_PAGE_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CAL_2_WORKING_PAGE_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_13	
const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_13 = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         MMU_TLB_ENTRY_13_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_14	
const MMU_MAS0_T  MMU_MAS_0_TLB_ENTRY_14 = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         MMU_TLB_ENTRY_14_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//MMU_TLB_ENTRY_15	
const MMU_MAS0_T  MMU_MAS_0_FLASH_CAL_WORKING_PAGE_BACKUP_128K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         FLASH_CAL_WORKING_PAGE_BACKUP_128K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };


//MMU_TLB_ENTRY_15	
const MMU_MAS0_T  MMU_MAS_0_EXTERNAL_RAM_128K = 
   {
                                                1,    //   2:3   TLBSEL  Set to 01
         EXTERNAL_RAM_128K_TLB_Index,    //  11:15  ESEL Set TLB entry number
                                                0     //  27:31  NV   sw updates this field
   };

//=============================================================================
// MMU_MAS_1_INITIAL
//=============================================================================
//MMU_TLB_ENTRY_0	
const MMU_MAS1_T MMU_MAS_1_FLASH_PML_BOOT_64K =
{
           MMU_MAS_Is_Valid_Entry( FLASH_PML_BOOT_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_0_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_0_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_0_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//MMU_TLB_ENTRY_1	
const MMU_MAS1_T MMU_MAS_1_INTERNAL_RAM =
{
           MMU_MAS_Is_Valid_Entry( INTERNAL_RAM_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_1_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_1_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_1_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//MMU_TLB_ENTRY_2
const MMU_MAS1_T MMU_MAS_1_MMR_REGISTER_0 =
{
           MMU_MAS_Is_Valid_Entry( MMR_REGISTER_0_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_2_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_2_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_2_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//MMU_TLB_ENTRY_3
const MMU_MAS1_T MMU_MAS_1_MMR_REGISTER_1 =
{
           MMU_MAS_Is_Valid_Entry( MMR_REGISTER_1_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_3_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_3_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_3_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};


//MMU_TLB_ENTRY_4
const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_1_256K =
{
           MMU_MAS_Is_Valid_Entry( FLASH_CODE_1_256K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_4_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_4_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_4_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};


//MMU_TLB_ENTRY_5
const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_2_256K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CODE_2_256K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_5_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_5_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_5_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//MMU_TLB_ENTRY_6
const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_3_256K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CODE_3_256K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_6_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_6_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_6_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//MMU_TLB_ENTRY_7
const MMU_MAS1_T MMU_MAS_1_FLASH_CODE_4_1M =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CODE_4_1M_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_7_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_7_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_7_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};


//MMU_TLB_ENTRY_8
const MMU_MAS1_T MMU_MAS_1_FLASH_EEPROM_64K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_EEPROM_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_8_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_8_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_8_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//MMU_TLB_ENTRY_9
const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_9 =
{
           MMU_MAS_Is_Valid_Entry(MMU_MAS_TLB_ENTRY_9_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_9_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_9_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_9_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};


//MMU_TLB_ENTRY_10
const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_10 =
{
           MMU_MAS_Is_Valid_Entry(MMU_MAS_TLB_ENTRY_10_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_10_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_10_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_10_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//Reference Page below
//MMU_TLB_ENTRY_11	
const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_1_64K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CAL_1_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_11_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_11_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_11_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};


//Reference Page below
//MMU_TLB_ENTRY_12	
const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_2_64K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CAL_2_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_12_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_12_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_12_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_1_WORKING_PAGE_64K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CAL_1_WORKING_PAGE_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_11_Invaldation_Protect_LCI,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_11_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_11_Page_Size_LCI     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_2_WORKING_PAGE_64K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CAL_2_WORKING_PAGE_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_12_Invaldation_Protect_LCI,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_12_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_12_Page_Size_LCI     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_11_Invaldation_Protect_VertiCAL,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_11_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_11_Page_Size_VertiCAL     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_12_Invaldation_Protect_VertiCAL,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_12_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_12_Page_Size_VertiCAL     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};


//MMU_TLB_ENTRY_13	
const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_13 =
{
           MMU_MAS_Is_Valid_Entry(MMU_TLB_ENTRY_13_TLB_Index),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_13_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_13_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_13_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};


//MMU_TLB_ENTRY_14	
const MMU_MAS1_T MMU_MAS_1_TLB_ENTRY_14 =
{
           MMU_MAS_Is_Valid_Entry(MMU_TLB_ENTRY_14_TLB_Index),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_14_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_14_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_14_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//LCI only
//MMU_TLB_ENTRY_15	
const MMU_MAS1_T MMU_MAS_1_FLASH_CAL_WORKING_PAGE_BACKUP_128K =
{
           MMU_MAS_Is_Valid_Entry(FLASH_CAL_WORKING_PAGE_BACKUP_128K_TLB_Index),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_15_Invaldation_Protect_LCI,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_15_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_15_Page_Size_LCI     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//VertiCAL only
//MMU_TLB_ENTRY_15	
const MMU_MAS1_T MMU_MAS_1_EXTERNAL_RAM_128K =
{
           MMU_MAS_Is_Valid_Entry(EXTERNAL_RAM_128K_EFFECTIVE_ADDRESS),    //    :0     Valid   1 TLB entry is valid
           MMU_MAS_TLB_ENTRY_15_Invaldation_Protect_VertiCAL,    //    :1     IPROT   1 protected from invalidation
                                 MMU_TLB_ENTRY_15_TID_INIT,    //   8:15    TID     Translation ID
                                                                       0,    //    :19    TS      to determine if TLB enrty may be
                                                                              //                   used for translation
           MMU_MAS_TLB_ENTRY_15_Page_Size_VertiCAL//  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                              //                   4=256k; 5=1M; 6=4M; 7=16M; 8=64M;
                                                                                              //                   9=256M; 10 = 1G; 11 = 4 G
};

//=============================================================================
// MMU_MAS_2_INITIAL
//=============================================================================
//MMU_TLB_ENTRY_0	

const MMU_MAS2_T MMU_MAS_2_FLASH_PML_BOOT_64K =
{
   MMU_MAS_Get_Effective_Address( FLASH_PML_BOOT_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_0_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_0_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_0_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

//MMU_TLB_ENTRY_1	

const MMU_MAS2_T MMU_MAS_2_INTERNAL_RAM =
{
   MMU_MAS_Get_Effective_Address( INTERNAL_RAM_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_1_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_1_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_1_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

//MMU_TLB_ENTRY_2

const MMU_MAS2_T MMU_MAS_2_MMR_REGISTER_0  =
{
   MMU_MAS_Get_Effective_Address( MMR_REGISTER_0_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_2_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_2_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_2_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

//MMU_TLB_ENTRY_3
const MMU_MAS2_T MMU_MAS_2_MMR_REGISTER_1  =
{
   MMU_MAS_Get_Effective_Address( MMR_REGISTER_1_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_3_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_3_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_3_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//MMU_TLB_ENTRY_4

const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_1_256K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CODE_1_256K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_4_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_4_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_4_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//MMU_TLB_ENTRY_5
const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_2_256K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CODE_2_256K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_5_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_5_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_5_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

//MMU_TLB_ENTRY_6
const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_3_256K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CODE_3_256K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_6_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_6_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_6_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//MMU_TLB_ENTRY_7
const MMU_MAS2_T MMU_MAS_2_FLASH_CODE_4_1M  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CODE_4_1M_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_7_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_7_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_7_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//MMU_TLB_ENTRY_8
const MMU_MAS2_T MMU_MAS_2_FLASH_EEPROM_64K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_EEPROM_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_8_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_8_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_8_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

//MMU_TLB_ENTRY_9
const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_9  =
{
   MMU_MAS_Get_Effective_Address( MMU_MAS_TLB_ENTRY_9_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_9_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_9_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_9_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };



//MMU_TLB_ENTRY_10

const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_10  =
{
   MMU_MAS_Get_Effective_Address( MMU_MAS_TLB_ENTRY_10_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_10_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_10_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_10_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

//Reference Page below
//MMU_TLB_ENTRY_11	
const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_1_64K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CAL_1_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_11_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_11_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_11_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//Reference Page below
//MMU_TLB_ENTRY_12	
const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_2_64K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CAL_2_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_12_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_12_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_12_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_1_WORKING_PAGE_64K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CAL_1_WORKING_PAGE_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_11_Write_Access_LCI,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_11_Cache_Access_LCI,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_11_Guarded_LCI,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_2_WORKING_PAGE_64K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CAL_2_WORKING_PAGE_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_12_Write_Access_LCI,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_12_Cache_Access_LCI,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_12_Guarded_LCI,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	
const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_11_Write_Access_VertiCAL,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_11_Cache_Access_VertiCAL,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_11_Guarded_VertiCAL,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_12_Write_Access_VertiCAL,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_12_Cache_Access_VertiCAL,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_12_Guarded_VertiCAL,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//MMU_TLB_ENTRY_13	


const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_13  =
{
   MMU_MAS_Get_Effective_Address( MMU_MAS_TLB_ENTRY_13_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_13_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_13_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_13_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//MMU_TLB_ENTRY_14	
const MMU_MAS2_T MMU_MAS_2_TLB_ENTRY_14  =
{
   MMU_MAS_Get_Effective_Address( MMU_MAS_TLB_ENTRY_14_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_14_Write_Access,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_14_Cache_Access,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_14_Guarded,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//LCI only
//MMU_TLB_ENTRY_15	
const MMU_MAS2_T MMU_MAS_2_FLASH_CAL_WORKING_PAGE_BACKUP_128K  =
{
   MMU_MAS_Get_Effective_Address( FLASH_CAL_WORKING_PAGE_BACKUP_128K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_15_Write_Access_LCI,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_15_Cache_Access_LCI,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_15_Guarded_LCI,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };


//VertiCAL only
//MMU_TLB_ENTRY_15	
const MMU_MAS2_T MMU_MAS_2_EXTERNAL_RAM_128K  =
{
   MMU_MAS_Get_Effective_Address( EXTERNAL_RAM_128K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                                                                                                  ENCODING_FORMAT,       //     26    VLE   0 = standard BookE page, 
                                                                                                                                        //                 1 = PowerPC VLE page 1
                                                                       MMU_MAS_TLB_ENTRY_15_Write_Access_VertiCAL,      //     27    W     0 = write-back   1=write thru
                                                                       MMU_MAS_TLB_ENTRY_15_Cache_Access_VertiCAL,      //     28    I     0 = cache inhibit                   
                                                                                   MMU_MAS_Memory_Coherence,      //     29    M     e200z3. Memory Coherence
                                                                               MMU_MAS_TLB_ENTRY_15_Guarded_VertiCAL,      //     30    G     not  Guarded
                                                                                           ENCODING_ENDIANNESS      //     31    E     0 = big-endian byte order
 };

//=============================================================================
// MMU_MAS_3_INITIAL
//=============================================================================

 //MMU_TLB_ENTRY_0	
 const MMU_MAS3_T MMU_MAS_3_FLASH_PML_BOOT_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_PML_BOOT_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_0_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_0_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_0_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_0_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_0_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_0_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };
			  
//MMU_TLB_ENTRY_1	

 const MMU_MAS3_T MMU_MAS_3_INTERNAL_RAM =
{
   MMU_MAS_Get_Real_Address( INTERNAL_RAM_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_1_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_1_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_1_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_1_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_1_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_1_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_2

 const MMU_MAS3_T MMU_MAS_3_MMR_REGISTER_0=
{
   MMU_MAS_Get_Real_Address( MMR_REGISTER_0_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_2_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_2_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_2_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_2_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_2_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_2_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_3
 const MMU_MAS3_T MMU_MAS_3_MMR_REGISTER_1=
{
   MMU_MAS_Get_Real_Address( MMR_REGISTER_1_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_3_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_3_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_3_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_3_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_3_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_3_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_4

 const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_1_256K=
{
   MMU_MAS_Get_Real_Address( FLASH_CODE_1_256K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_4_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_4_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_4_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_4_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_4_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_4_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_5
 const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_2_256K=
{
   MMU_MAS_Get_Real_Address( FLASH_CODE_2_256K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_5_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_5_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_5_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_5_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_5_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_5_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_6
 const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_3_256K=
{
   MMU_MAS_Get_Real_Address( FLASH_CODE_3_256K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_6_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_6_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_6_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_6_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_6_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_6_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_7
 const MMU_MAS3_T MMU_MAS_3_FLASH_CODE_4_1M=
{
   MMU_MAS_Get_Real_Address( FLASH_CODE_4_1M_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_7_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_7_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_7_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_7_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_7_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_7_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };


//MMU_TLB_ENTRY_8
 const MMU_MAS3_T MMU_MAS_3_FLASH_EEPROM_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_EEPROM_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_8_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_8_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_8_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_8_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_8_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_8_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_9
 const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_9 =
{
   MMU_MAS_Get_Real_Address( MMU_MAS_TLB_ENTRY_9_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_9_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_9_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_9_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_9_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_9_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_9_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_10

 const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_10 =
{
   MMU_MAS_Get_Real_Address( MMU_MAS_TLB_ENTRY_10_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_10_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_10_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_10_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_10_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_10_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_10_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//Reference Page below
//MMU_TLB_ENTRY_11	
 const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_1_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_CAL_1_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_11_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_11_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_11_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };


//Reference Page below
//MMU_TLB_ENTRY_12	

 const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_2_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_CAL_2_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_12_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_12_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_12_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };


// Working Page - LCI Below
//MMU_TLB_ENTRY_11	
 const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_1_WORKING_PAGE_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_CAL_1_WORKING_PAGE_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_11_User_Execute_Permission_LCI,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_11_User_Write_Permission_LCI,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_11_User_Read_Permission_LCI,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission_LCI,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission_LCI,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission_LCI       //     31     SR    1 = supervisor read premission
  };

// Working Page - LCI Below
//MMU_TLB_ENTRY_12	
 const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_2_WORKING_PAGE_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_CAL_2_WORKING_PAGE_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_12_User_Execute_Permission_LCI,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_12_User_Write_Permission_LCI,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_12_User_Read_Permission_LCI,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission_LCI,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission_LCI,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission_LCI       //     31     SR    1 = supervisor read premission
  };

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_11	

 const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_11_User_Execute_Permission_VertiCAL,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_11_User_Write_Permission_VertiCAL,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_11_User_Read_Permission_VertiCAL,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission_VertiCAL,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission_VertiCAL,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission_VertiCAL       //     31     SR    1 = supervisor read premission
  };

// Working Page - VertiCAL Below
//MMU_TLB_ENTRY_12	
 const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K =
{
   MMU_MAS_Get_Real_Address( FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_12_User_Execute_Permission_VertiCAL,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_12_User_Write_Permission_VertiCAL,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_12_User_Read_Permission_VertiCAL,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission_VertiCAL,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission_VertiCAL,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission_VertiCAL       //     31     SR    1 = supervisor read premission
  };

//MMU_TLB_ENTRY_13	

 const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_13 =
{
   MMU_MAS_Get_Real_Address( MMU_MAS_TLB_ENTRY_13_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_13_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_13_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_13_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_13_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_13_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_13_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };


//MMU_TLB_ENTRY_14	

 const MMU_MAS3_T MMU_MAS_3_TLB_ENTRY_14 =
{
   MMU_MAS_Get_Real_Address( MMU_MAS_TLB_ENTRY_14_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_14_User_Execute_Permission,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_14_User_Write_Permission,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_14_User_Read_Permission,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_14_Supervisor_Execute_Permission,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_14_Supervisor_Write_Permission,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_14_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
  };

//LCI only
//MMU_TLB_ENTRY_15	
 const MMU_MAS3_T MMU_MAS_3_FLASH_CAL_WORKING_PAGE_BACKUP_128K =
{
   MMU_MAS_Get_Real_Address(FLASH_CAL_WORKING_PAGE_BACKUP_128K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_15_User_Execute_Permission_LCI,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_15_User_Write_Permission_LCI,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_15_User_Read_Permission_LCI,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_15_Supervisor_Execute_Permission_LCI,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_15_Supervisor_Write_Permission_LCI,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_15_Supervisor_Read_Permission_LCI       //     31     SR    1 = supervisor read premission
  };


//VertiCAL only
//MMU_TLB_ENTRY_15	
const MMU_MAS3_T MMU_MAS_3_EXTERNAL_RAM_128K =
{
   MMU_MAS_Get_Real_Address( EXTERNAL_RAM_128K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                                                       MMU_TLB_USER_DEFINED_OPERATION_NONE,      //  22:25     User Bits
                                               MMU_MAS_TLB_ENTRY_15_User_Execute_Permission_VertiCAL,      //     26     UX    1 = user execute permission
                                                   MMU_MAS_TLB_ENTRY_15_User_Write_Permission_VertiCAL,      //     27     UW    1 = user write permission            
                                                   MMU_MAS_TLB_ENTRY_15_User_Read_Permission_VertiCAL,      //     28     SX    1 = supervisor execute premission
                                      MMU_MAS_TLB_ENTRY_15_Supervisor_Execute_Permission_VertiCAL,      //     29     SW    1 = supervisor write premission
                                          MMU_MAS_TLB_ENTRY_15_Supervisor_Write_Permission_VertiCAL,      //     30     UR    1 = user read permission
                                          MMU_MAS_TLB_ENTRY_15_Supervisor_Read_Permission_VertiCAL       //     31     SR    1 = supervisor read premission
  };

//=============================================================================
// MMU_MAS_4_INITIAL
//=============================================================================
const MMU_MAS4_T MMU_MAS_4_INITIAL =
{
   1,    //   2:3      TLBSELD    Set to 01
   0,    //  12:15     TIDSELD    default PID
   6,    //  20:23     TSIZED     default size  4MB
   0,    //     26     VLED       0 = Default VLE value
   1,    //     27     WD         0 = write-back default
   1,    //     28     ID         1 = cache-inhibited default
   0,    //     29     MD         not supported - ignored
   0,    //     30     GD         Guarded default
   0     //     31     ED         Endian default 0=big-endian
};

//=============================================================================
// MMU_MAS_6_INITIAL
//=============================================================================
const MMU_MAS6_T MMU_MAS_6_INITIAL =
{
   0x00,  //   8:15     SPID     PID value for searches
   1      //     31     SAS      AS value for searches
};



