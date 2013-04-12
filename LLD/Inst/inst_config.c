

#include "inst_config.h"
#include "io_config_mmu.h"


// Instrument - LCI
const MMU_MAS0_T INST_MMU_MAS_0_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
                                                   1,    //   2:3   TBLSEL  Set to 01
            FLASH_CAL_1_64K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                   0     //  27:31  NVCAM   sw updates this field
      },
      // CAL - 2
      {
                                                   1,    //   2:3   TBLSEL  Set to 01
            FLASH_CAL_2_64K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                   0     //  27:31  NVCAM   sw updates this field
      }
   },

   // Working page
   {
      // CAL - 1
      {
                                                           1,    //   2:3   TBLSEL  Set to 01
       FLASH_CAL_1_WORKING_PAGE_64K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                           0     //  27:31  NVCAM   sw updates this field
      },
      // CAL - 2
      {
                                                           1,    //   2:3   TBLSEL  Set to 01
       FLASH_CAL_2_WORKING_PAGE_64K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                           0     //  27:31  NVCAM   sw updates this field
      }
   }
};

const MMU_MAS1_T INST_MMU_MAS_1_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_1_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_11_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                                                  0,    //   8:15    TID     0 = Global Translation ID
                                                                  0,    //    :19    TS      to determine if TLB enrty may be
                                                                        //                   used for translation
                           MMU_MAS_TLB_ENTRY_11_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                        //                   4=256k; 5=1M; 6=4M; 7=16M
      },
      // CAL - 2
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_2_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_12_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                                                  0,    //   8:15    TID     0 = Global Translation ID
                                                                  0,    //    :19    TS      to determine if TLB enrty may be
                                                                        //                   used for translation
                           MMU_MAS_TLB_ENTRY_12_Page_Size    //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                        //                   4=256k; 5=1M; 6=4M; 7=16M
      }
   },
   // Working page
   {
      // CAL - 1
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_1_WORKING_PAGE_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_11_Invaldation_Protect_LCI,    //    :1     IPROT   1 protected from invalidation
                                                                               0,    //   8:15    TID     0 = Global Translation ID
                                                                               0,    //    :19    TS      to determine if TLB enrty may be
                                                                                     //                   used for translation
                           MMU_MAS_TLB_ENTRY_11_Page_Size_LCI     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                     //                   4=256k; 5=1M; 6=4M; 7=16M
      },
      // CAL - 2
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_2_WORKING_PAGE_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_12_Invaldation_Protect_LCI,    //    :1     IPROT   1 protected from invalidation
                                                                               0,    //   8:15    TID     0 = Global Translation ID
                                                                               0,    //    :19    TS      to determine if TLB enrty may be
                                                                                     //                   used for translation
                           MMU_MAS_TLB_ENTRY_12_Page_Size_LCI     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                     //                   4=256k; 5=1M; 6=4M; 7=16M
      }
   }
};

const MMU_MAS2_T INST_MMU_MAS_2_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_1_64K_EFFECTIVE_ADDRESS ),      //   0:19    EPN   Effective Page Number
                            MMU_MAS_TLB_ENTRY_11_Page_Type,      //     26    VLE   0 = standard BookE page,
                                                                               //                 1 = PowerPC VLE page 1
                            MMU_MAS_TLB_ENTRY_11_Write_Access,      //     27    W     0 = write-back   1=write thru
                            MMU_MAS_TLB_ENTRY_11_Cache_Access,      //     28    I     0 = cache inhibit
                            MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                            MMU_MAS_TLB_ENTRY_11_Guarded,      //     30    G     not  Guarded
                            MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      },
      // CAL - 2
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_2_64K_EFFECTIVE_ADDRESS ),      //   0:19    EPN   Effective Page Number
                            MMU_MAS_TLB_ENTRY_12_Page_Type,      //     26    VLE   0 = standard BookE page,
                                                                               //                 1 = PowerPC VLE page 1
                             MMU_MAS_TLB_ENTRY_12_Write_Access,      //     27    W     0 = write-back   1=write thru
                             MMU_MAS_TLB_ENTRY_12_Cache_Access,      //     28    I     0 = cache inhibit
                             MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                             MMU_MAS_TLB_ENTRY_12_Guarded,      //     30    G     not  Guarded
                             MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      }
   },
   // Working page
   {
      // CAL - 1
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_1_WORKING_PAGE_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                           MMU_MAS_TLB_ENTRY_11_Page_Type_LCI,      //     26    VLE   0 =standard BookE page,
                                                                                           //                 1= PowerPC VLE page 1
                            MMU_MAS_TLB_ENTRY_11_Write_Access_LCI,      //     27    W     0 = write-back   1=write thru
                            MMU_MAS_TLB_ENTRY_11_Cache_Access_LCI,      //     28    I     0 = cache inhibit
                            MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                             MMU_MAS_TLB_ENTRY_11_Guarded_LCI,      //     30    G     not  Guarded
                            MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      },
      // CAL - 2
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_2_WORKING_PAGE_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                           MMU_MAS_TLB_ENTRY_12_Page_Type_LCI,      //     26    VLE   0 =standard BookE page,
                                                                                           //                 1= PowerPC VLE page 1
                            MMU_MAS_TLB_ENTRY_12_Write_Access_LCI,      //     27    W     0 = write-back   1=write thru
                            MMU_MAS_TLB_ENTRY_12_Cache_Access_LCI,      //     28    I     0 = cache inhibit
                        MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                                MMU_MAS_TLB_ENTRY_12_Guarded_LCI,      //     30    G     not  Guarded
                              MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      }
   }
};

const MMU_MAS3_T INST_MMU_MAS_3_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_1_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_11_User_Execute_Permission,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_11_User_Write_Permission,      //     27     UW    1 = user write permission
             MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission,      //     29     SW    1 = supervisor write premission
                     MMU_MAS_TLB_ENTRY_11_User_Read_Permission,      //     30     UR    1 = user read permission
                MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
      },
      // CAL - 2
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_2_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_12_User_Execute_Permission,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_12_User_Write_Permission,      //     27     UW    1 = user write permission
             MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_12_User_Read_Permission,      //     30     UR    1 = user read permission
                MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
      }
   },
   // Working page
   {
         // CAL - 1
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_1_WORKING_PAGE_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_11_User_Execute_Permission_LCI,      //     26     UX    1 = user execute permission
                    MMU_MAS_TLB_ENTRY_11_User_Write_Permission_LCI,      //     27     UW    1 = user write permission
             MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission_LCI,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission_LCI,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_11_User_Read_Permission_LCI,      //     30     UR    1 = user read permission
               MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission_LCI       //     31     SR    1 = supervisor read premission
      },
      // CAL - 2
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_2_WORKING_PAGE_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_12_User_Execute_Permission_LCI,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_12_User_Write_Permission_LCI,      //     27     UW    1 = user write permission
            MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission_LCI,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission_LCI,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_12_User_Read_Permission_LCI,      //     30     UR    1 = user read permission
                MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission_LCI       //     31     SR    1 = supervisor read premission
      }
   }
};


// Instrument - VertiCAL
const MMU_MAS0_T VERTICAL_EXTERNAL_RAM_MMU_MAS_0_INITIAL =
{
                                                   1,    //   2:3   TBLSEL  Set to 01
           EXTERNAL_RAM_128K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                   0     //  27:31  NVCAM   sw updates this field
};

const MMU_MAS1_T VERTICAL_EXTERNAL_RAM_MMU_MAS_1_INITIAL =
{
        MMU_MAS_Is_Valid_Entry( EXTERNAL_RAM_128K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_15_Invaldation_Protect_VertiCAL,    //    :1     IPROT   1 protected from invalidation
                                                                  0,    //   8:15    TID     0 = Global Translation ID
                                                                  0,    //    :19    TS      to determine if TLB enrty may be
                                                                        //                   used for translation
                           MMU_MAS_TLB_ENTRY_15_Page_Size_VertiCAL     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                        //                   4=256k; 5=1M; 6=4M; 7=16M
};

const MMU_MAS2_T VERTICAL_EXTERNAL_RAM_MMU_MAS_2_INITIAL =
{
      MMU_MAS_Get_Effective_Address( EXTERNAL_RAM_128K_EFFECTIVE_ADDRESS ),      //   0:19    EPN   Effective Page Number
                            MMU_MAS_TLB_ENTRY_15_Page_Type_VertiCAL,      //     26    VLE   0 = standard BookE page,
                                                                               //                 1 = PowerPC VLE page 1
                             MMU_MAS_TLB_ENTRY_15_Write_Access_VertiCAL,      //     27    W     0 = write-back   1=write thru
                             MMU_MAS_TLB_ENTRY_15_Cache_Access_VertiCAL,      //     28    I     0 = cache inhibit
                         MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                                  MMU_MAS_TLB_ENTRY_15_Guarded_VertiCAL,      //     30    G     not  Guarded
                               MMU_TLB_ENDIANNESS_BIG_ENDIAN      //     31    E     0 = big-endian byte order
};

const MMU_MAS3_T VERTICAL_EXTERNAL_RAM_MMU_MAS_3_INITIAL =
{
                 MMU_MAS_Get_Real_Address( EXTERNAL_RAM_128K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_15_User_Execute_Permission_VertiCAL,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_15_User_Write_Permission_VertiCAL,      //     27     UW    1 = user write permission
             MMU_MAS_TLB_ENTRY_15_Supervisor_Execute_Permission_VertiCAL,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_15_Supervisor_Write_Permission_VertiCAL,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_15_User_Read_Permission_VertiCAL,      //     30     UR    1 = user read permission
               MMU_MAS_TLB_ENTRY_15_Supervisor_Read_Permission_VertiCAL       //     31     SR    1 = supervisor read premission
};

const MMU_MAS0_T VERTICAL_MMU_MAS_0_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
                                                   1,    //   2:3   TBLSEL  Set to 01
            FLASH_CAL_1_64K_TLB_Index,     //  11:15  ESELCAM Set TLB entry number
                                                   0     //  27:31  NVCAM   sw updates this field
      },
      // CAL - 2
      {
                                                   1,    //   2:3   TBLSEL  Set to 01
            FLASH_CAL_2_64K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                   0     //  27:31  NVCAM   sw updates this field
      }
   },

   // Working page
   {
      // CAL - 1
      {
                                                           1,    //   2:3   TBLSEL  Set to 01
       FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                           0     //  27:31  NVCAM   sw updates this field
      },
      // CAL - 2
      {
                                                           1,    //   2:3   TBLSEL  Set to 01
       FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_TLB_Index,    //  11:15  ESELCAM Set TLB entry number
                                                           0     //  27:31  NVCAM   sw updates this field
      }
   }
};

const MMU_MAS1_T VERTICAL_MMU_MAS_1_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_1_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_11_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                                                  0,    //   8:15    TID     0 = Global Translation ID
                                                                  0,    //    :19    TS      to determine if TLB enrty may be
                                                                        //                   used for translation
                           MMU_MAS_TLB_ENTRY_11_Page_Size    //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                        //                   4=256k; 5=1M; 6=4M; 7=16M
      },
      // CAL - 2
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_2_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_12_Invaldation_Protect,    //    :1     IPROT   1 protected from invalidation
                                                                  0,    //   8:15    TID     0 = Global Translation ID
                                                                  0,    //    :19    TS      to determine if TLB enrty may be
                                                                        //                   used for translation
                           MMU_MAS_TLB_ENTRY_12_Page_Size     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                        //                   4=256k; 5=1M; 6=4M; 7=16M
      }
   },
   // Working page
   {
      // CAL - 1
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_11_Invaldation_Protect_VertiCAL,    //    :1     IPROT   1 protected from invalidation
                                                                               0,    //   8:15    TID     0 = Global Translation ID
                                                                               0,    //    :19    TS      to determine if TLB enrty may be
                                                                                     //                   used for translation
                          MMU_MAS_TLB_ENTRY_11_Page_Size_VertiCAL     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                     //                   4=256k; 5=1M; 6=4M; 7=16M
      },
      // CAL - 2
      {
        MMU_MAS_Is_Valid_Entry( FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS ),    //    :0     Valid   1 TLB entry is valid
                 MMU_MAS_TLB_ENTRY_12_Invaldation_Protect_VertiCAL,    //    :1     IPROT   1 protected from invalidation
                                                                               0,    //   8:15    TID     0 = Global Translation ID
                                                                               0,    //    :19    TS      to determine if TLB enrty may be
                                                                                     //                   used for translation
                           MMU_MAS_TLB_ENTRY_12_Page_Size_VertiCAL     //  20:23    TSIZE   page size: 1=4k; 2=16k; 3=64k;
                                                                                     //                   4=256k; 5=1M; 6=4M; 7=16M
      }
   }
};

const MMU_MAS2_T VERTICAL_MMU_MAS_2_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_1_64K_EFFECTIVE_ADDRESS ),      //   0:19    EPN   Effective Page Number
                           MMU_MAS_TLB_ENTRY_11_Page_Type,      //     26    VLE   0 = standard BookE page,
                                                                               //                 1 = PowerPC VLE page 1
                             MMU_MAS_TLB_ENTRY_11_Write_Access,      //     27    W     0 = write-back   1=write thru
                             MMU_MAS_TLB_ENTRY_11_Cache_Access,      //     28    I     0 = cache inhibit
                         MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                                  MMU_MAS_TLB_ENTRY_11_Guarded,      //     30    G     not  Guarded
                               MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      },
      // CAL - 2
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_2_64K_EFFECTIVE_ADDRESS ),      //   0:19    EPN   Effective Page Number
                            MMU_MAS_TLB_ENTRY_12_Page_Type,      //     26    VLE   0 = standard BookE page,
                                                                               //                 1 = PowerPC VLE page 1
                             MMU_MAS_TLB_ENTRY_12_Write_Access,      //     27    W     0 = write-back   1=write thru
                             MMU_MAS_TLB_ENTRY_12_Cache_Access,      //     28    I     0 = cache inhibit
                         MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                                  MMU_MAS_TLB_ENTRY_12_Guarded,      //     30    G     not  Guarded
                               MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      }
   },
   // Working page
   {
      // CAL - 1
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                           MMU_MAS_TLB_ENTRY_11_Page_Type_VertiCAL,      //     26    VLE   0 =standard BookE page,
                                                                                           //                 1= PowerPC VLE page 1
                            MMU_MAS_TLB_ENTRY_11_Write_Access_VertiCAL,      //     27    W     0 = write-back   1=write thru
                            MMU_MAS_TLB_ENTRY_11_Cache_Access_VertiCAL,      //     28    I     0 = cache inhibit
                        MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                                 MMU_MAS_TLB_ENTRY_11_Guarded_VertiCAL,      //     30    G     not  Guarded
                              MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      },
      // CAL - 2
      {
      MMU_MAS_Get_Effective_Address( FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_EFFECTIVE_ADDRESS),      //   0:19    EPN   Effective Page Number
                           MMU_MAS_TLB_ENTRY_12_Page_Type_VertiCAL,      //     26    VLE   0 =standard BookE page,
                                                                                           //                 1= PowerPC VLE page 1
                            MMU_MAS_TLB_ENTRY_12_Write_Access_VertiCAL,      //     27    W     0 = write-back   1=write thru
                            MMU_MAS_TLB_ENTRY_12_Cache_Access_VertiCAL,      //     28    I     0 = cache inhibit
                        MMU_TLB_MEMORY_COHERENCE_NOT_REQUIRED,      //     29    M     e500z6 not supported - ignored
                                 MMU_MAS_TLB_ENTRY_11_Guarded_VertiCAL,      //     30    G     not  Guarded
                              MMU_TLB_ENDIANNESS_BIG_ENDIAN       //     31    E     0 = big-endian byte order
      }
   }
};

const MMU_MAS3_T VERTICAL_MMU_MAS_3_INITIAL[2][2] =
{
   // Reference page
   {
      // CAL - 1
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_1_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_11_User_Execute_Permission,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_11_User_Write_Permission,      //     27     UW    1 = user write permission
             MMU_MAS_TLB_ENTRY_11_User_Execute_Permission,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_11_User_Write_Permission,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_11_User_Read_Permission,      //     30     UR    1 = user read permission
                MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission      //     31     SR    1 = supervisor read premission
      },
      // CAL - 2
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_2_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_12_User_Execute_Permission,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_12_User_Write_Permission,      //     27     UW    1 = user write permission
             MMU_MAS_TLB_ENTRY_12_User_Execute_Permission,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_12_User_Write_Permission,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_12_User_Read_Permission,      //     30     UR    1 = user read permission
                MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission       //     31     SR    1 = supervisor read premission
      }
   },
   // Working page
   {
         // CAL - 1
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_1_WORKING_PAGE_VERTICAL_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_11_User_Execute_Permission_VertiCAL,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_11_User_Write_Permission_VertiCAL,      //     27     UW    1 = user write permission
            MMU_MAS_TLB_ENTRY_11_Supervisor_Execute_Permission_VertiCAL,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_11_Supervisor_Write_Permission_VertiCAL,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_11_User_Read_Permission_VertiCAL,      //     30     UR    1 = user read permission
                MMU_MAS_TLB_ENTRY_11_Supervisor_Read_Permission_VertiCAL      //     31     SR    1 = supervisor read premission
      },
      // CAL - 2
      {
                 MMU_MAS_Get_Real_Address( FLASH_CAL_2_WORKING_PAGE_VERTICAL_64K_REAL_ADDRESS ),      //   0:19     RPN   Real Page Number
                              0,      //  22:25     User Bits
                   MMU_MAS_TLB_ENTRY_12_User_Execute_Permission_VertiCAL,      //     26     UX    1 = user execute permission
                     MMU_MAS_TLB_ENTRY_12_User_Write_Permission_VertiCAL,      //     27     UW    1 = user write permission
             MMU_MAS_TLB_ENTRY_12_Supervisor_Execute_Permission_VertiCAL,      //     28     SX    1 = supervisor execute premission
               MMU_MAS_TLB_ENTRY_12_Supervisor_Write_Permission_VertiCAL,      //     29     SW    1 = supervisor write premission
                      MMU_MAS_TLB_ENTRY_12_User_Read_Permission_VertiCAL,      //     30     UR    1 = user read permission
                MMU_MAS_TLB_ENTRY_12_Supervisor_Read_Permission_VertiCAL      //     31     SR    1 = supervisor read premission
      }
   }
};


