
//===========================================================================
// include files                                                
//===========================================================================
#include "dd_mcd5401_interface.h"
#include "io_config_tpu.h"

//=============================================================================
// Variable Definitions
//=============================================================================
uint32_t  FI_Current_Count[FEI_INDEX_MAX];
uint32_t  FI_Current_Previous_Count[FEI_INDEX_MAX];
uint32_t  FI_Current_Time[FEI_INDEX_MAX];
uint32_t  FI_Current_Previous_Time[FEI_INDEX_MAX];
uint32_t  FI_Current_Period[FEI_INDEX_MAX];


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
// FI_Update_Count_Time
//=============================================================================
void FI_Update_Count_Time(void )
{
 uint8_t        counter;
 uint32_t     count_temp;
 uint32_t     time_temp;
     for( counter = 0; counter < FEI_INDEX_MAX; counter++ )
   {
      FI_Current_Previous_Count[counter] =  FI_Current_Count[counter] ;
      FI_Current_Previous_Time[counter] =  FI_Current_Time[counter];
      FI_Current_Time[counter]=MCD5401_Get_Edge_Time(FEI_TPU_INDEX, TPU_CONFIG_IC_FI[counter] );
      FI_Current_Count [counter]=MCD5401_Get_Edge_Count(FEI_TPU_INDEX, TPU_CONFIG_IC_FI[counter] );

     if(FI_Current_Count[counter] >= FI_Current_Previous_Count[counter] )
      {   
          count_temp = FI_Current_Count[counter] - FI_Current_Previous_Count[counter];
       }
      else
       {
          count_temp = (FI_Current_Count[counter] +UINT24_MAX- FI_Current_Previous_Count[counter]);
        }	


	  
      if(FI_Current_Time[counter] >= FI_Current_Previous_Time[counter] )
      {   
          time_temp = FI_Current_Time[counter] - FI_Current_Previous_Time[counter];
       }
      else
       {
          time_temp = (FI_Current_Time[counter] +UINT24_MAX- FI_Current_Previous_Time[counter]);
        }	

	  if(count_temp>0)
	  {
           FI_Current_Period[counter] = time_temp/count_temp;
	  }	   	
	  
     }
}


//=============================================================================
// FI_Get_current_Count
//=============================================================================
uint32_t  FI_Get_Current_Count(FEI_INDEX_T  index )
{

  return  FI_Current_Count [index];
 
}


//=============================================================================
// FI_Get_Current_Period
//=============================================================================
uint32_t  FI_Get_Current_Period(FEI_INDEX_T  index )
{

  return  FI_Current_Period [index];
 
}




