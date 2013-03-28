#ifndef DD_FLASH_INIT_MPC5644_H
#define DD_FLASH_INIT_MPC5644_H


#ifndef MPC5644_FLASH_BIU_INIT_RUNMODE
#define MPC5644_FLASH_BIU_INIT_RUNMODE                                                             \
   (FLASH_BIU_Set_Flexray_Prefetch_Enable_State( 0, FLASH_PREFETCH_DISABLE                     ) | \
      FLASH_BIU_Set_Nexus_Prefetch_Enable_State( 0, FLASH_PREFETCH_DISABLE                     ) | \
       FLASH_BIU_Set_eDMA_Prefetch_Enable_State( 0, FLASH_PREFETCH_DISABLE                     ) | \
  FLASH_BIU_Set_Core_Load_Store_Prefetch_Enable_State( 0, FLASH_PREFETCH_DISABLE               ) | \
       FLASH_BIU_Set_Core_Prefetch_Enable_State( 0, FLASH_PREFETCH_DISABLE                     ) | \
             FLASH_BIU_Set_Address_Pipe_Control( 0, FLASH_BIUCR_APC_NO_ADDRESS_PIPELINE        ) | \
               FLASH_BIU_Set_Write_Wait_Control( 0, FLASH_BIUCR_WWSC_THREE_WAIT_STATES         ) | \
                FLASH_BIU_Set_Read_Wait_Control( 0, FLASH_BIUCR_RWSC_SEVEN_WAIT_STATES         ) | \
                    FLASH_BIU_Set_Data_Prefetch( 0, FLASH_BIUCR_DPFEN_PREFETCH_BY_ANY_READ     ) | \
             FLASH_BIU_Set_Instruction_Prefetch( 0, FLASH_BIUCR_IPFEN_PREFETCH_BY_ANY_READ     ) | \
                   FLASH_BIU_Set_Prefetch_Limit( 0, FLASH_BIUCR_PFLIM_PREFETCH_ON_MISS_OR_HIT  ) | \
         FLASH_BIU_Set_Line_Read_Buffers_Enable( 0, true                                       ) | \
      FLASH_BIU_Set_Flexray_Access_FLASH_Memory( 0, FLASH_BIUCR_MASTER_AP_NO_ACCESS            ) | \
       FLASH_BIU_Set_eDMA_Access_FLASH_Memory( 0, FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS      ) | \
 FLASH_BIU_Set_MCU_Load_Store_Access_FLASH_Memory( 0, FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS  ) | \
          FLASH_BIU_Set_MCU_Access_FLASH_Memory( 0, FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS    ) | \
        FLASH_BIU_Set_Nexus_Access_FLASH_Memory( 0, FLASH_BIUCR_MASTER_AP_READ_WRITE_ACCESS    ) | \
            FLASH_Set_Line_Buffer_Configuration(0,FLASH_BIUCR2_ALL_BUFFERS_FOR_FLASH_ACCESS)   )

#endif

#ifndef MPC5644_FLASH_BIU_INIT_PROGRAMMING
#define MPC5644_FLASH_BIU_INIT_PROGRAMMING                                    \
        (FLASH_BIU_Set_Prefetch_Limit(MPC5644_FLASH_BIU_INIT_RUNMODE,         \
                         FLASH_BIUCR_PFLIM_NO_PREFETCH))
#endif


#define FLASH_BIU_INIT_RUNMODE                    MPC5644_FLASH_BIU_INIT_RUNMODE
#define FLASH_BIU_INIT_PROGRAMMING                MPC5644_FLASH_BIU_INIT_PROGRAMMING

//===========================================================================
//  Burst mode initialization
//===========================================================================
extern const FLASH_BIUCR1_T MPC5644_FLASH_BIUCR1_INIT;
extern const FLASH_BIUCR1_T MPC5644_FLASH_BIUCR1_PROGRAMMING_INIT;
extern const FLASH_BIUCR2_T MPC5644_FLASH_BIUCR2_PROGRAMMING_INIT;
extern const FLASH_BIUCR2_T MPC5644_FLASH_BIUCR2_INIT;
extern const FLASH_BIUAPR_T MPC5644_FLASH_BIUAPR_INIT;


#endif // DD_FLASH_INIT_H
