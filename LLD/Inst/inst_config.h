#ifndef INST_CONFIG_H
#define INST_CONFIG_H

#include "dd_mmu_interface.h"

#ifndef FLASH_KB
#define FLASH_KB(x)   ((x) * 1024)
#endif
#ifndef FLASH_MB
#define FLASH_MB(x)   ((x) * 1024 * 1024)
#endif

#define CSA_FILL_PATTERN 0xAA55AA55
#define USTACK_FILL_PATTERN 0xB1B1

#define APP_CAL_PRESENCE_PATTERN                       (0x3223)


#define Cw_SOFTWARE_LEVEL       0x01
#define Cw_REVISION_LEVEL       0x01
#define Cw_CalFORM_ID           ( ( (0xff & Cw_SOFTWARE_LEVEL) << 8) + (0xff & Cw_REVISION_LEVEL) )


#define INST_VALID_PAGE                                   0xAAAA
#define INST_BLANK_PAGE                                   0xFFFF

#define INST_WORKING_PAGE_RAM_START_ADDRESS               0x40010000
#define INST_WORKING_PAGE_FLASH_BACKUP_START_ADDRESS      0x00200000
#define VERTICAL_WORKING_PAGE_RAM_START_ADDRESS           0x30000000
#define INST_REFERENCE_PAGE_START_ADDRESS                 0x00020000

#define CAL_PAGE_SIZE                                     FLASH_KB(128)

#define INST_CHECK_PATTERN_OFFSET                         0x0000
#define INST_CHECKSUM_OFFSET                              0x0002
#define INST_CAL_DATA_START_OFFSET                        0x0004
#define INST_CAL_VERSION_OFFSET                           (CAL_PAGE_SIZE - 4)
#define INST_CAL_CAL_PRESENCE_PATTERN_OFFSET              (CAL_PAGE_SIZE - 2)


#define INST_CAL_WORKING_PAGE_PATTERN                     0xf0e1d2c3
#define INST_CAL_REFERENCE_PAGE_PATTERN                   0x3c2d1e0f

extern const MMU_MAS0_T INST_MMU_MAS_0_INITIAL[2][2];
extern const MMU_MAS1_T INST_MMU_MAS_1_INITIAL[2][2];
extern const MMU_MAS2_T INST_MMU_MAS_2_INITIAL[2][2];
extern const MMU_MAS3_T INST_MMU_MAS_3_INITIAL[2][2];

extern const MMU_MAS0_T VERTICAL_MMU_MAS_0_INITIAL[2][2];
extern const MMU_MAS1_T VERTICAL_MMU_MAS_1_INITIAL[2][2];
extern const MMU_MAS2_T VERTICAL_MMU_MAS_2_INITIAL[2][2];
extern const MMU_MAS3_T VERTICAL_MMU_MAS_3_INITIAL[2][2];

extern const MMU_MAS0_T VERTICAL_EXTERNAL_RAM_MMU_MAS_0_INITIAL;
extern const MMU_MAS1_T VERTICAL_EXTERNAL_RAM_MMU_MAS_1_INITIAL;
extern const MMU_MAS2_T VERTICAL_EXTERNAL_RAM_MMU_MAS_2_INITIAL;
extern const MMU_MAS3_T VERTICAL_EXTERNAL_RAM_MMU_MAS_3_INITIAL;



#endif

