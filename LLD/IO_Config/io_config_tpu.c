
#include "io_config_tpu.h"



//ETPUA0 - EPPwMT
const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_EPPWMT =
{
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_0,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_ENABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_LOW,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   EPPE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
};

//ETPUA1 - CAM1FIVO
//ETPUA 16 -CAM2FIVO

const TPU_CHANNEL_Configuration_T   CAM_CAME[CAM_NUMBER_OF_SENSORS] =
{
   {

   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_1,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_DISABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_LOW,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   CAME_FUNCTION_NUM          //   TPU Primitives or Channel function Select
   },
   {
    TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_16,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_DISABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_LOW,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   CAME_FUNCTION_NUM          //   TPU Primitives or Channel function Select
   }

};

//ETPUA2 - Not used 

//ETPUA3 - Not used 


//ETPUA4 - Not used 

//ETPUA4  - Not used 

//ETPUA5 - Not used 

//ETPUA6 - Not used 

//ETPUA7 - Not used 

//ETPUA8 - Not used 

//ETPUA09  - Not used 

//ETPUA10  - Not used  

//ETPUA11 - Not used 

//ETPUA12 - Not used 

//ETPUA13  - Not used 

//ETPUA14  - Not used 

//ETPUA15  - Not used 



//ETPUA17 - EST1

const TPU_CHANNEL_Configuration_T   SPARK_Mptac[SPARK_SELECT_MAX] =
{
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_17,            //     Channel
   MPTACE_ANGLE_MODE,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_DISABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_HIGH,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   MPTACE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  }
};

//ETPUA18 - Not used 


//ETPUA19 - INJ1
//ETPUA20 - INJ2
//ETPUA21 - INJ3
//ETPUA22 - INJ4


const TPU_CHANNEL_Configuration_T PFI_Desfi[PFI_MAX_CYLINDERS] =
{
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_21,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_DISABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_HIGH,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   DESFIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
  },
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_20,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_DISABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_HIGH,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   DESFIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
  },
 {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_19,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_DISABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
    ACTIVE_HIGH,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   DESFIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
  }
   #if 0
  
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_22,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_DISABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_HIGH,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   DESFIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
  }
#endif
};


// ETPUA23 - Not used 

// ETPUA24 - Not used 

// ETPUA25 - Not used 

// ETPUA26 - SPFI
const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_FI[FEI_INDEX_MAX] =
{
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_26,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_ENABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_LOW,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   FIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
   },

// ETPUA27 - VSSFI
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_27,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_ENABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_LOW,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   FIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
  },

// ETPUA28  - WSSFI
//const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_WSSFI =
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_28,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_ENABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_LOW,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   FIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
  },

//TPUA 29  - ENSFI
//const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_ENSFI =
  {
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_29,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_ENABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_MEDIUM,  // Channel Priority Index
   ACTIVE_LOW,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_FALLING,                 //   Host Service Request Type
   FIE_FUNCTION_NUM          //   TPU Primitives or Channel function Select
  
  }
};

// ETPUA30 - WINGATE_RQOME
const TPU_CHANNEL_Configuration_T   WINGATE_RQOME =
{
   TPU_EVENT_ABSOLUTE,   //   Set the desired value for TPU configuration
   0,                                   //      PWM Update Mode 1- Coherent,0- synchronus
   0,                                   //     Refernce channel number
   TPU_CHANNEL_30,            //     Channel
   0,                                   //    Channel Function Mode1
   TPU_TCR1_TIME_BASE,                                     //   Channel Function Mode0
   0,                                      //  Entry Table Condition Select
   TPU_CHANNEL_INTERRUPT_ENABLE,  //1  //Interrupt Request Enable
   TPU_TRANSFER_REQUEST_DISABLE,   //Transfer Request Enable
   TPU_CHANNEL_PRIORITY_LOW,  // Channel Priority Index
   ACTIVE_HIGH,  //    Active state of channel
   TPU_OFF_OUTPUT_DISABLE,            //       8   Output Disable
   EDGE_RISING,                 //   Host Service Request Type
   RQOME_FUNCTION_NUM          //   TPU Primitives or Channel function Select
};

// ETPUA31 - Not used 

const TPU_MCR_T TPU_INITIAL_MCR = 
{
   TPU_NEGATE_GLOBAL_EXCEPTION,      // GEC          :  Bit      0
   0,      // SDMERR       :  Bit      1
   0,       // WDTO1        :  Bit      2
   0,       // WDTO2        :  Bit      3
   0,        // MGEA         :  Bit      4
   0,        // MGEB         :  Bit      5
   0,        // ILFA         :  Bit      6
   0,        // ILFB         :  Bit      7
   0,      // SCMERR       :  Bit      8
   0,     // SCMSIZE      :  Bit      [15:9]
   0,     // SCMMISC      :  Bit      20
   0,     // SCMMISF      :  Bit      21
   TPU_MISC_OPERATION_DISABLED,    // SCMMISEN     :  Bit      22
   TPU_SCM_NOT_VISIBLE,         // VIS          :  Bit      25
   TPU_ENABLE_TIME_BASE         // GTBE         :  Bit      31
};

const TPU_CDCR_T TPU_INITIAL_CDCR = 
{
   0 ,           // STS          :  Bit     0
   0 ,        // CTBASE       :  Bit     [5-1]
   0 ,        // PBBASE       :  Bit     [15-6]
   0 ,        // PWIDTH       :  Bit     16
   0 ,         // PARM0        :  Bit     [23-17]
   0 ,            // WR           :  Bit     24
   0          // PARM1        :  Bit     [31-25]
};

// Actual value will be assigned depending upon SCM size from MCR
// During init it is assigned with 0x0000000
const TPU_MISCCMPR_T TPU_INITIAL_MISCCMPR = 
{
    0   // MISCCMPR   :  Bit     [31-0]
};


const TPU_ECR_T TPU_INITIAL_ECR[TPU_NUMBER_OF_ENGINES] = 
{
   {
      TPU_NORMAL_OPERATION,       // FEND     :  Bit       31
      TPU_ENGINE_RUNING,       // STOP     :  Bit       30
       0 ,        // STF      :  Bit       28
       0,       // HLTF     :  Bit       23
      TPU_USE_SYSTEM_CLK_DIV_BY2,       // FCSS        :  Bit       19
      TPU_SYSTEM_CLOCK_2,      // FPSCK    :  Bits  [18:16]
      TPU_2_SAMPLE_MODE,       // CDFC     :  Bits  [15:14]
      0,       // ERBA     :  Bits  [12:8]
      TPU_SCHEDULER_PRIORITY_ENABLED,     // SPPDIS   :  Bit        7
      TPU_ENTRY_TABLE_BASE_ADDRESS         // ETB      :  Bits  [ 4: 0]
   }
};

const TPU_Wdt_Idle_T TPU_INITIAL_Wdt_Idle[TPU_NUMBER_OF_ENGINES] = 
{
   {
      {  // WDTR_A
         TPU_WDT_DISABLED,     // WDM
         0    // WDCNT
      },
      {  // IDLER_A
         0     // ICR
      }
   }
};

//=============================================================================
//  Time Base Static Init values
//=============================================================================
const TPU_Clock_T TPU_INITIAL_Clock[TPU_NUMBER_OF_ENGINES] = 
{
   {
      {  // TBCR_A
         TPU_TCR2_SHUTDOWN,  // TCR2CTL  :  Bits  [31:29]
         TPU_TBCR_2SAMPL_SYSCLK_DIV2,    // TCRCF    :  Bits  [28:27]
         TPU_TCR2_ANGLE_CLOCK_MODE_DISABLED,       // AM       :  Bit       25
         CONFIG_TPU_TBCR_A_TCR2P,    // TCR2P    :  Bits  [21:16]
         (( ETPU_TCR1_CLOCK_SELECT & 0x06) >> 1),  // TCR1CTL  :  Bits  [15:14] 
         ( ETPU_TCR1_CLOCK_SELECT & 0x01),   // TCR1CS   :  Bits  13
         CONFIG_TPU_TBCR_A_TCR1P     // TCR1P    :  Bits  [ 7: 0]
      },
      {
         {  // TB1R_A
            0  // TCR1     :  Bits  [23:00]
         },
         {  // TB2R_A
            0  // TCR2     :  Bits  [23:00]
         }
      },
      {  // REDCR_A
         TPU_SERVER_CLIENT_OPERATION_ENABLE,       // REN1     :  Bit       31
         TPU_RESOURCE_SERVER_OPERATION,       // RSC1     :  Bit       30
         0,//TPU_Initialize_Server_ID1(TPU_REDCR_INIT_A), // VALID1   :  Bit       29
         TPU_RESOURCE_SERVER_TCR1B,       // SRV1     :  Bits  [19:16]
         TPU_SERVER_CLIENT_OPERATION_DISABLE,       // REN2     :  Bit       15
         TPU_RESOURCE_CLIENT_OPERATION,       // RSC2     :  Bit       14
         0, //TPU_Initialize_Server_ID2(TPU_REDCR_INIT_A), // VALID2   :  Bit       13
         TPU_RESOURCE_SERVER_TCR2B        // SRV2     :  Bits  [ 3: 0]
      }
   }
};

//=============================================================================
//  CIER - Channel Interrupt Enable Register
//
//=============================================================================
const TPU_CIER_T TPU_INITIAL_CIER[TPU_NUMBER_OF_ENGINES] = 
{
   {  // TPU A
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE31      :Bit  31
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE30      :Bit  30
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE29      :Bit  29
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE28      :Bit  28
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE27      :Bit  27
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE26      :Bit  26
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE25      :Bit  25
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE24      :Bit  24
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE23      :Bit  23
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE22      :Bit  22
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE21      :Bit  21
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE20      :Bit  20
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE19      :Bit  19
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE18      :Bit  18
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE17      :Bit  17
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE16      :Bit  16
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE15      :Bit  15
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE14      :Bit  14
      TPU_CHANNEL_INTERRUPT_DISABLE,// CIE13      :Bit  13
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE12      :Bit  12
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE11      :Bit  11
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE10      :Bit  10
      TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE09      :Bit  09
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE08      :Bit  08
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE07      :Bit  07
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE06      :Bit  06
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE05      :Bit  05
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE04      :Bit  04
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE03      :Bit  03
      TPU_CHANNEL_INTERRUPT_DISABLE, // CIE02      :Bit  02
      TPU_CHANNEL_INTERRUPT_DISABLE,// CIE01      :Bit  01
      TPU_CHANNEL_INTERRUPT_DISABLE   // CIE00      :Bit  00
   }
};

//=============================================================================
//  CDTRER - Channel Data Transfer Request Enable Register
//
//=============================================================================
const TPU_CDTRER_T TPU_INITIAL_CDTRER[TPU_NUMBER_OF_ENGINES] = 
{
   {  // TPU A
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE31      :Bit  31
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE30      :Bit  30
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE29      :Bit  29
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE28      :Bit  28
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE27      :Bit  27
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE26      :Bit  26
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE25      :Bit  25
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE24      :Bit  24
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE23      :Bit  23
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE22      :Bit  22
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE21      :Bit  21
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE20      :Bit  20
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE19      :Bit  19
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE18      :Bit  18
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE17      :Bit  17
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE16      :Bit  16
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE15      :Bit  15
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE14      :Bit  14
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE13      :Bit  13
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE12      :Bit  12
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE11      :Bit  11
      TPU_CHANNEL_INTERRUPT_DISABLE, // DTRE10      :Bit  10
     TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE09      :Bit  09
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE08      :Bit  08
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE07      :Bit  07
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE06      :Bit  06
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE05      :Bit  05
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE04      :Bit  04
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE03      :Bit  03
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE02      :Bit  02
      TPU_CHANNEL_INTERRUPT_DISABLE,  // DTRE01      :Bit  01
      TPU_CHANNEL_INTERRUPT_DISABLE   // DTRE00      :Bit  00
   }
};

//=============================================================================
//  TPU_INITIAL_SDM_ADDRESS - SDM start address of each channel
//
//=============================================================================
const uint32_t TPU_INITIAL_SDM_ADDRESS[TPU_NUMBER_OF_ENGINES][TPU_CHANNEL_MAX] = 
{
   {
      TPU_A_CHANNEL_00_SDM_BLOCK_START,
      TPU_A_CHANNEL_01_SDM_BLOCK_START,
      TPU_A_CHANNEL_02_SDM_BLOCK_START,
      TPU_A_CHANNEL_03_SDM_BLOCK_START,
      TPU_A_CHANNEL_04_SDM_BLOCK_START,
      TPU_A_CHANNEL_05_SDM_BLOCK_START,
      TPU_A_CHANNEL_06_SDM_BLOCK_START,
      TPU_A_CHANNEL_07_SDM_BLOCK_START,
      TPU_A_CHANNEL_08_SDM_BLOCK_START,
      TPU_A_CHANNEL_09_SDM_BLOCK_START,
      TPU_A_CHANNEL_10_SDM_BLOCK_START,
      TPU_A_CHANNEL_11_SDM_BLOCK_START,
      TPU_A_CHANNEL_12_SDM_BLOCK_START,
      TPU_A_CHANNEL_13_SDM_BLOCK_START,
      TPU_A_CHANNEL_14_SDM_BLOCK_START,
      TPU_A_CHANNEL_15_SDM_BLOCK_START,
      TPU_A_CHANNEL_16_SDM_BLOCK_START,
      TPU_A_CHANNEL_17_SDM_BLOCK_START,
      TPU_A_CHANNEL_18_SDM_BLOCK_START,
      TPU_A_CHANNEL_19_SDM_BLOCK_START,
      TPU_A_CHANNEL_20_SDM_BLOCK_START,
      TPU_A_CHANNEL_21_SDM_BLOCK_START,
      TPU_A_CHANNEL_22_SDM_BLOCK_START,
      TPU_A_CHANNEL_23_SDM_BLOCK_START,
      TPU_A_CHANNEL_24_SDM_BLOCK_START,
      TPU_A_CHANNEL_25_SDM_BLOCK_START,
      TPU_A_CHANNEL_26_SDM_BLOCK_START,
      TPU_A_CHANNEL_27_SDM_BLOCK_START,
      TPU_A_CHANNEL_28_SDM_BLOCK_START,
      TPU_A_CHANNEL_29_SDM_BLOCK_START,
      TPU_A_CHANNEL_30_SDM_BLOCK_START,
      TPU_A_CHANNEL_31_SDM_BLOCK_START
   }
};

const TPU_Channel_Control_Init_T   TPU_INITIAL_CHANNEL_CONTROL[TPU_NUMBER_OF_ENGINES][TPU_CHANNEL_MAX] =
{
   {
      {
         {  // TPU_A_CH_0 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_1 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_2 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_3 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_4 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_5 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_6 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_7 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_8 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_9 
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
             EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_10
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_11
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_12
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_13
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_14
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_15
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_16
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_17
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_18
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_19
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_20
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_21
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_22
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_23
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_24
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_25
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_26
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_27
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_28
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_29
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_30
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      },
      {
         {  // TPU_A_CH_31
            TPU_CHANNEL_INTERRUPT_DISABLE,  // CIE         :  Bit       31
            TPU_TRANSFER_REQUEST_DISABLE, // DTRE        :  Bit       30
            TPU_CHANNEL_PRIORITY_DISABLED,  // CPR         :  Bit   [29:28]
            0, // ETPD        :  Bit       27
            false, // ETCS        :  Bit       24
            0,  // CFS         :  Bits  [20:16]
            TPU_OFF_OUTPUT_DISABLE, // ODIS        :  Bit       15
            false, // OPOL        :  Bit       14
            0  // CPBA        :  Bits  [10: 0]
         },
         {
            0,    // CIS_CIC     :  Bit       31
            0,  // CIOS_CIOC   :  Bit       30
            0,  // DTRS_DTRC   :  Bit       23
            0,// DTROS_DTROC :  Bit       22
            0,        // IPS         :  Bit       15
            0,        // OPS         :  Bit       14
            0,        // OPS         :  Bit       13
            0,        // FM1         :  Bits       1
            TPU_TCR1_TIME_BASE         // FM0         :  Bits       0
         },
         {
            EDGE_NONE    // :  Bits [ 2: 0]
         }
      }
   }
};

