#ifndef IO_CONFIG_TPU_H
#define IO_CONFIG_TPU_H

#include "dd_tpu.h"
#include "dd_pfi.h"
#include "io_config_fmpll.h"
#include "io_config_spark.h"
#include "io_config_fuel.h"
#include "io_config_cam.h"




//TCR1 and TCR2 prescalers

//TCR1  resoultion is 1/80MHz/(2*(CONFIG_TPU_TBCR_A_TCR1P+1)) = 0.25usec
#define CONFIG_TPU_TBCR_A_TCR1P       9

//TCR2 ??????????
#define CONFIG_TPU_TBCR_A_TCR2P      32

//=============================================================================
// eEPU Scaling
//=============================================================================
#define ETPU_SYSTEM_FREQUENCY_HZ (SYSTEM_FREQUENCY_HZ)

#define ETPU_TCR1_CLOCK_SELECT     TPU_TCR1_SYSCLK_DIV2_CLK

// TCR1 Clock Freq
#define TPU_A_TCR1_CLOCK_FREQ (( ETPU_TCR1_CLOCK_SELECT ==TPU_TCR1_SYSCLK_DIV2_CLK ) ?\
                                   (SYSTEM_FREQUENCY_HZ/2/(CONFIG_TPU_TBCR_A_TCR1P+1)) :\
                                   (SYSTEM_FREQUENCY_HZ/(CONFIG_TPU_TBCR_A_TCR1P+1)) )


//ETPUA0 - EPPwMT
#define EPPWMT_TPU_INDEX  TPU_INDEX_0

extern const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_EPPWMT;

#define EPPWMT_EDGE_ARRAY_SIZE              ( 64 /* MCD5408_EDGE_TIME_ARRAY_SIZE*/ )
#define EPPWMT_BUFFER_SIZE                  ( EPPWMT_EDGE_ARRAY_SIZE * 4 )
#define TPU_A_CHANNEL_00_INIT_SDM_SIZE      ( EPPE_SPRAM_FRAME_SIZE + EPPWMT_BUFFER_SIZE )

//ETPUA1 - CAM1FIVO
#define TPU_A_CHANNEL_01_INIT_SDM_SIZE      ( CAME_SPRAM_FRAME_SIZE )
//ETPUA 16 -CAM2FIVO
#define TPU_A_CHANNEL_16_INIT_SDM_SIZE      ( CAME_SPRAM_FRAME_SIZE )

#define CAME_TPU_INDEX  TPU_INDEX_0

extern const TPU_CHANNEL_Configuration_T   CAM_CAME[CAM_NUMBER_OF_SENSORS];

//ETPUA17 - EST1
#define MPTAC_TPU_INDEX  TPU_INDEX_0

extern const TPU_CHANNEL_Configuration_T   SPARK_Mptac[SPARK_SELECT_MAX];

#define TPU_A_CHANNEL_17_INIT_SDM_SIZE      ( MPTACE_SPRAM_FRAME_SIZE )

//ETPUA19 - INJ1
                            
#define TPU_A_CHANNEL_19_INIT_SDM_SIZE   DESFIE_SPRAM_FRAME_SIZE


//ETPUA20 -INJ2

#define TPU_A_CHANNEL_20_INIT_SDM_SIZE   DESFIE_SPRAM_FRAME_SIZE

// ETPUA21 - INJ3
                             
#define TPU_A_CHANNEL_21_INIT_SDM_SIZE   DESFIE_SPRAM_FRAME_SIZE

// ETPUA22 - INJ4
                             
#define TPU_A_CHANNEL_22_INIT_SDM_SIZE   DESFIE_SPRAM_FRAME_SIZE

#define PFI_FUEL_TPU_INDEX  TPU_INDEX_0
//extern const TPU_CHANNEL_Configuration_T PFI_Desfi[CRANK_MAX_CYLINDERS];
extern const TPU_CHANNEL_Configuration_T PFI_Desfi[PFI_MAX_CYLINDERS];


#define FEI_TPU_INDEX  TPU_INDEX_0

typedef enum
{
  FEI_INDEX_SPFI,
  FEI_INDEX_VSSFI,
  FEI_INDEX_WSSFI,
  FEI_INDEX_ENSFI,
  FEI_INDEX_MAX

} FEI_INDEX_T;

extern const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_FI[FEI_INDEX_MAX];

#define PWMIE_TPU_INDEX  TPU_INDEX_0

// ETPUA26 - SPFI
//extern const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_SPFI;
#define TPU_A_CHANNEL_26_INIT_SDM_SIZE   FIE_SPRAM_FRAME_SIZE

// ETPUA27 - VSSFI
//extern const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_VSSFI;
#define TPU_A_CHANNEL_27_INIT_SDM_SIZE   FIE_SPRAM_FRAME_SIZE

// ETPUA28  - WSSFI
//extern const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_WSSFI;
#define TPU_A_CHANNEL_28_INIT_SDM_SIZE   FIE_SPRAM_FRAME_SIZE

//TPUA 29  - ENSFI
//extern const TPU_CHANNEL_Configuration_T   TPU_CONFIG_IC_ENSFI;
#define TPU_A_CHANNEL_29_INIT_SDM_SIZE   FIE_SPRAM_FRAME_SIZE

//TPUA 30 - wingate
#define RQOME_TPU_INDEX  TPU_INDEX_0

#define TPU_A_CHANNEL_30_INIT_SDM_SIZE   RQOME_SPRAM_FRAME_SIZE

extern const TPU_CHANNEL_Configuration_T   WINGATE_RQOME;

//=============================================================================
// /------------------------------------------------------------------------
// | External Constants
// \------------------------------------------------------------------------
//=============================================================================
//=============================================================================
// @globalv TPU_MCR_T | TPU_INITIAL_MCR |
//
//=============================================================================
extern const TPU_MCR_T TPU_INITIAL_MCR;

//=============================================================================
// @globalv TPU_CDCR_T | TPU_INITIAL_CDCR |
//
//=============================================================================
extern const TPU_CDCR_T TPU_INITIAL_CDCR;

//=============================================================================
// @globalv TPU_MISCCMPR_T | TPU_INITIAL_MISCCMPR |
//
//=============================================================================
extern const TPU_MISCCMPR_T TPU_INITIAL_MISCCMPR;

//=============================================================================
// @globalv TPU_ECR_T | TPU_INITIAL_ECR |
//
//=============================================================================
extern const TPU_ECR_T TPU_INITIAL_ECR[TPU_NUMBER_OF_ENGINES];

//=============================================================================
// @globalv TPU_Wdt_Idle_T | TPU_INITIAL_Wdt_Idle |
//
//=============================================================================
extern const TPU_Wdt_Idle_T TPU_INITIAL_Wdt_Idle[TPU_NUMBER_OF_ENGINES] ; 

//=============================================================================
// @globalv TPU_Clock_T | TPU_INITIAL_Clock |
//
//=============================================================================
extern const TPU_Clock_T TPU_INITIAL_Clock[TPU_NUMBER_OF_ENGINES];

//=============================================================================
// @globalv TPU_CIER_T | TPU_INITIAL_CIER |
//
//=============================================================================
extern const TPU_CIER_T TPU_INITIAL_CIER[TPU_NUMBER_OF_ENGINES];

//=============================================================================
// @globalv TPU_CDTRER_T | TPU_INITIAL_CDTRER |
//
//=============================================================================
extern const TPU_CDTRER_T TPU_INITIAL_CDTRER[TPU_NUMBER_OF_ENGINES];

//=============================================================================
// @globalv TPU_Channel_Control_Init_T | TPU_INITIAL_CHANNEL_CONTROL |
//
//=============================================================================
extern const TPU_Channel_Control_Init_T   TPU_INITIAL_CHANNEL_CONTROL[TPU_NUMBER_OF_ENGINES][TPU_CHANNEL_MAX];

//=============================================================================
// @globalv uint32_t | TPU_INITIAL_SDM_ADDRESS |
//
//=============================================================================
extern const uint32_t TPU_INITIAL_SDM_ADDRESS[TPU_NUMBER_OF_ENGINES][TPU_CHANNEL_MAX];


#endif // IO_CONFIG_SWT_H

