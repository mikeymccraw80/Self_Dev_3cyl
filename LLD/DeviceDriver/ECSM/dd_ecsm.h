#ifndef DD_ECSM_H
#define DD_ECSM_H


//=============================================================================
//                                Includes
//=============================================================================

#include "hw_ecsm.h"

//=============================================================================
// Register overlay of the submodule
//=============================================================================
#define SECTION_ECSM_REGISTER
#include "section.h"
extern ECSM_T ECSM;
#define SECTION_END
#include "section.h"

#define NO_OF_ECSM_ERROR_BIT_POS  (116)
#define ECSM_ESR_CLEAR  (0x33)

#define ECSM_ESR_RAM_1_BIT_MASK  (0x20)
#define ECSM_ESR_FLASH_1_BIT_MASK  (0x10)
#define ECSM_ESR_RAM_NONCORRECTABLE_BIT_MASK  (0x02)
#define ECSM_ESR_FLASH_NONCORRECTABLE_BIT_MASK  (0x01)
extern const ECSM_ECR_T ECSM_ECR_INITIAL;
extern const ECSM_EEGR_T ECSM_EEGR_INITIAL;
typedef enum
{
   ECSM_CONFIGURATION_WIDTH_ENABLE_FLASH_1_BIT_REPORTING          =  1, //[ 11 ] Enable Flash one bit error Reporting
   ECSM_CONFIGURATION_WIDTH_ENABLE_RAM_1_BIT_REPORTING            =  1, //[ 12 ] Enable RAM One bit error reporting
   ECSM_CONFIGURATION_WIDTH_FORCE_RAM_1_BIT_INVERSION             =  1, //[ 13 ] Force RAM One bit inversion
   ECSM_CONFIGURATION_WIDTH_FORCE_RAM_CONTINUOUS_1_BIT_INVERSION  =  1, //[ 14 ] Force RAM Continuous One Bit inversion
   ECSM_CONFIGURATION_WIDTH_INTERRUPT_TYPE                        =  3  //[ 17:15 ] Interrupt Type

}   ECSM_Configuration_Width_T;

typedef enum
{
   ECSM_CONFIGURATION_POSITION_ENABLE_FLASH_1_BIT_REPORTING         =  11, //[ 11 ] Enable Flash one bit error Reporting
   ECSM_CONFIGURATION_POSITION_ENABLE_RAM_1_BIT_REPORTING           =  12, //[ 12 ] Enable RAM One bit error reporting
   ECSM_CONFIGURATION_POSITION_FORCE_RAM_1_BIT_INVERSION            =  13, //[ 13 ] Force RAM One bit inversion
   ECSM_CONFIGURATION_POSITION_FORCE_RAM_CONTINUOUS_1_BIT_INVERSION =  14, //[ 14 ] Force RAM Continuous One Bit inversion
   ECSM_CONFIGURATION_POSITION_INTERRUPT_TYPE                       =  15  //[17:15] Interrupt Type

}   ECSM_Configuration_Position_T;


typedef enum ECSM_RAM_Flash_Attributes_Status_Tag
{
   ECSM_FEAR_FLASH_FAULT_ADDRESS,
   ECSM_FEMR_FLASH_MASTER_NO,
   ECSM_FEAT_PROTECTION,
   ECSM_FEAT_BUS_SIZE,
   ECSM_FEAT_WRITE_ACCESS,
   ECSM_FEDR_DATA_H,
   ECSM_FEDR_DATA_L,
   ECSM_REAR_RAM_FAULT_ADDRESS,
   ECSM_PRESR_RAM_SYNDROME,
   ECSM_REMR_RAM_MASTER_NO,
   ECSM_REAT_PROTECTION,
   ECSM_REAT_BUS_SIZE,
   ECSM_REAT_WRITE_ACCESS,
   ECSM_REDR_DATA_H,
   ECSM_REDR_DATA_L

} ECSM_RAM_Flash_Attributes_Status_T;


typedef enum ECSM_Error_Bit_Position_Tag
{
   ECSM_ERROR_BIT_POS0 = 0,
   ECSM_ERROR_BIT_POS1 = 1,
   ECSM_ERROR_BIT_POS2 = 2,
   ECSM_ERROR_BIT_POS3 = 3,
   ECSM_ERROR_BIT_POS4 = 4,
   ECSM_ERROR_BIT_POS5 = 5,
   ECSM_ERROR_BIT_POS6 = 6,
   ECSM_ERROR_BIT_POS7 = 7,
   ECSM_ERROR_BIT_POS8 = 8,
   ECSM_ERROR_BIT_POS9 = 9,
   ECSM_ERROR_BIT_POS10 = 10,
   ECSM_ERROR_BIT_POS11 = 11,
   ECSM_ERROR_BIT_POS12 = 12,
   ECSM_ERROR_BIT_POS13 = 13,
   ECSM_ERROR_BIT_POS14 = 14,
   ECSM_ERROR_BIT_POS15 = 15,
   ECSM_ERROR_BIT_POS16 = 16,
   ECSM_ERROR_BIT_POS17 = 17,
   ECSM_ERROR_BIT_POS18 = 18,
   ECSM_ERROR_BIT_POS19 = 19,
   ECSM_ERROR_BIT_POS20 = 20,
   ECSM_ERROR_BIT_POS21 = 21,
   ECSM_ERROR_BIT_POS22 = 22,
   ECSM_ERROR_BIT_POS23 = 23,
   ECSM_ERROR_BIT_POS24 = 24,
   ECSM_ERROR_BIT_POS25 = 25,
   ECSM_ERROR_BIT_POS26 = 26,
   ECSM_ERROR_BIT_POS27 = 27,
   ECSM_ERROR_BIT_POS28 = 28,
   ECSM_ERROR_BIT_POS29 = 29,
   ECSM_ERROR_BIT_POS30 = 30,
   ECSM_ERROR_BIT_POS31 = 31,
   ECSM_ERROR_BIT_POS32 = 32,
   ECSM_ERROR_BIT_POS33 = 33,
   ECSM_ERROR_BIT_POS34 = 34,
   ECSM_ERROR_BIT_POS35 = 35,
   ECSM_ERROR_BIT_POS36 = 36,
   ECSM_ERROR_BIT_POS37 = 37,
   ECSM_ERROR_BIT_POS38 = 38,
   ECSM_ERROR_BIT_POS39 = 39,
   ECSM_ERROR_BIT_POS40 = 40,
   ECSM_ERROR_BIT_POS41 = 41,
   ECSM_ERROR_BIT_POS42 = 42,
   ECSM_ERROR_BIT_POS43 = 43,
   ECSM_ERROR_BIT_POS44 = 44,
   ECSM_ERROR_BIT_POS45 = 45,
   ECSM_ERROR_BIT_POS46 = 46,
   ECSM_ERROR_BIT_POS47 = 47,
   ECSM_ERROR_BIT_POS48 = 48,
   ECSM_ERROR_BIT_POS49 = 49,
   ECSM_ERROR_BIT_POS50 = 50,
   ECSM_ERROR_BIT_POS51 = 51,
   ECSM_ERROR_BIT_POS52 = 52,
   ECSM_ERROR_BIT_POS53 = 53,
   ECSM_ERROR_BIT_POS54 = 54,
   ECSM_ERROR_BIT_POS55 = 55,
   ECSM_ERROR_BIT_POS56 = 56,
   ECSM_ERROR_BIT_POS57 = 57,
   ECSM_ERROR_BIT_POS58 = 58,
   ECSM_ERROR_BIT_POS59 = 59,
   ECSM_ERROR_BIT_POS60 = 60,
   ECSM_ERROR_BIT_POS61 = 61,
   ECSM_ERROR_BIT_POS62 = 62,
   ECSM_ERROR_BIT_POS63 = 63,
   ECSM_ERROR_BIT_POS64 = 64,
   ECSM_ERROR_BIT_POS65 = 65,
   ECSM_ERROR_BIT_POS66 = 66,
   ECSM_ERROR_BIT_POS67 = 67,
   ECSM_ERROR_BIT_POS68 = 68,
   ECSM_ERROR_BIT_POS69 = 69,
   ECSM_ERROR_BIT_POS70 = 70,
   ECSM_ERROR_BIT_POS71 = 71,
   ECSM_ERROR_BIT_POS72 = 72,
   ECSM_ERROR_BIT_POS73 = 73,
   ECSM_ERROR_BIT_POS74 = 74,
   ECSM_ERROR_BIT_POS75 = 75,
   ECSM_ERROR_BIT_POS76 = 76,
   ECSM_ERROR_BIT_POS77 = 77,
   ECSM_ERROR_BIT_POS96 = 96,
   ECSM_ERROR_BIT_POS97 = 97,
   ECSM_ERROR_BIT_POS98 = 98,
   ECSM_ERROR_BIT_POS99 = 99,
   ECSM_ERROR_BIT_POS100 = 100,
   ECSM_ERROR_BIT_POS101 = 101,
   ECSM_ERROR_BIT_POS102 = 102,
   ECSM_ERROR_BIT_POS103 = 103,
   ECSM_ERROR_BIT_POS104 = 104,
   ECSM_ERROR_BIT_POS105 = 105,
   ECSM_ERROR_BIT_POS106 = 106,
   ECSM_ERROR_BIT_POS107 = 107,
   ECSM_ERROR_BIT_POS108 = 108,
   ECSM_ERROR_BIT_POS109 = 109,
   ECSM_ERROR_BIT_POS110 = 110,
   ECSM_ERROR_BIT_POS111 = 111,
   ECSM_ERROR_BIT_POS112 = 112,
   ECSM_ERROR_BIT_POS113 = 113,
   ECSM_ERROR_BIT_POS114 = 114,
   ECSM_ERROR_BIT_POS115 = 115,
   ECSM_ERROR_BIT_POS_MAX

} ECSM_Error_Bit_Position_T;




typedef enum
{
   ECSM_CONFIGURATION_POSITION_ENABLE_RAM_NON_CORRECTABLE_REPORTING                      = 0, //[ 0 ] Enable RAM non-correctable reporting.
   ECSM_CONFIGURATION_POSITION_ENABLE_FLASH_NON_CORRECTABLE_REPORTING                    = 1, //[ 1 ] Enable Flash non-correctable reporting.
   ECSM_CONFIGURATION_POSITION_FORCE_INTERNAL_SRAM_CONTINUOUS_NONCORRECTABLE_DATA_ERRORS = 2, //[ 2 ] Force internal SRAM continuous noncorrectable data errors
   ECSM_CONFIGURATION_POSITION_FORCE_INTERNAL_SRAM_ONE_NONCORRECTABLE_DATA_ERRORS        = 3, //[ 3 ] Force internal SRAM one noncorrectable data errors.
   ECSM_CONFIGURATION_POSITION_ERROR_BIT_POSITION                                        = 4  //[ 10:4 ] Error bit position.

} ECSM_Ecr_Configuration_Position_T;


typedef enum
{
   ECSM_CONFIGURATION_WIDTH_ENABLE_RAM_NON_CORRECTABLE_REPORTING                      = 1, //[ 0 ] Enable RAM non-correctable reporting.
   ECSM_CONFIGURATION_WIDTH_ENABLE_FLASH_NON_CORRECTABLE_REPORTING                    = 1, //[ 1 ] Enable Flash non-correctable reporting.
   ECSM_CONFIGURATION_WIDTH_FORCE_INTERNAL_SRAM_CONTINUOUS_NONCORRECTABLE_DATA_ERRORS = 1, //[ 2 ] Force internal SRAM continuous noncorrectable data errors
   ECSM_CONFIGURATION_WIDTH_FORCE_INTERNAL_SRAM_ONE_NONCORRECTABLE_DATA_ERRORS        = 1, //[ 3 ] Force internal SRAM one noncorrectable data errors.
   ECSM_CONFIGURATION_WIDTH_ERROR_BIT_POSITION                                        = 7  //[ 4 ] Error bit position.

} ECSM_Ecr_Configuration_WIDTH_T;


// @enum ECSM_Enable_T | ECSM Enable type
typedef enum ECSM_Enable_Tag
{
   ECSM_DISABLE,  //@emem ECSM Feature Disable
   ECSM_ENABLE    //@emem ECSM Feature Enable

}  ECSM_Enable_T;


// @enum ECSM_Interrupt_Type | ECSM Interrupt type
typedef enum ECSM_Interrupt_Type_Tag
{
   ECSM_RAM_1_BIT_CORRECTION,            // RAM_1_Bit_Correction
   ECSM_FLASH_1_BIT_CORRECTION,          // Flash_1_Bit_Correction
   ECSM_RAM_NONCORRECTABLE_ERROR,        // RAM_NonCorrectable_Error
   ECSM_FLASH_NONCORRECTABLE_ERROR       // Flash_NonCorrectable_Error

}  ECSM_Interrupt_Type_T;



//=============================================================================
// ECSM_Initialize_Device
//
// @func ECSM Initialize Device.
//
// @parm  None
//
// @rdesc None
//
// @end
//=============================================================================

void ECSM_Initialize_Device(void);

uint32_t ECSM_Get_RAM_FLASH_Attributes(ECSM_RAM_Flash_Attributes_Status_T attribute_type);


#endif // DD_ECSM_H

