
//===========================================================================
// include files                                                
//===========================================================================
#include "dd_mcd5401_interface.h"
#include "io_config_tpu.h"

//=============================================================================
// Variable Definitions
//=============================================================================
uint32_t  FI_Current_Count[FEI_INDEX_MAX];
uint32_t  FI_Previous_Count[FEI_INDEX_MAX];
uint32_t  FI_Current_Time[FEI_INDEX_MAX];
uint32_t  FI_Previous_Time[FEI_INDEX_MAX];


//=============================================================================
// FI_Initialize
//=============================================================================
void FI_Initialize(void )
{
 uint8_t        counter;
 
   for( counter = 0; counter < FEI_INDEX_MAX; counter++ )
   {
     MCD5401_Initialize_Channel(FEI_TPU_INDEX, &TPU, TPU_CONFIG_IC_FI[counter]);
   }
  
}


//=============================================================================
// FI_Get_current_Count
//=============================================================================
void FI_Get_current_Count(void )
{
 uint8_t        counter;
     for( counter = 0; counter < FEI_INDEX_MAX; counter++ )
   {
    FI_Current_Count[counter]=MCD5401_Get_Edge_Time(FEI_TPU_INDEX, TPU_CONFIG_IC_FI[counter] );
    FI_Current_Time[counter]=MCD5401_Get_Edge_Count(FEI_TPU_INDEX, TPU_CONFIG_IC_FI[counter] );
   }
}



