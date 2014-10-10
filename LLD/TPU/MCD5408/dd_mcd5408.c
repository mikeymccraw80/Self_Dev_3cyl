
#include "dd_mcd5408.h"
#include "mcd5408.h"
#include "dd_tpu.h"

   MCD5408_SDM_T             *mcd5408_sdm_vis;
   volatile TPU_GLOBAL_RAM_T *TPU_GLOBAL_RAM_vis;
//=============================================================================
// MCD5408_Initialize_Channel
//=============================================================================
void MCD5408_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure,
    MCD5408_Channel_Init_T  const  *parameters   
   )
   
{
  TPU_Channel_T channel= configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   MCD5408_SDM_T          *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);
   //MCD5408_Channel_Init_T  *parameters = (MCD5408_Channel_Init_T*)in_init;
   TPU_TBCR_T              temp_tbcr;
   uint32_t                cssr_channel_mask;
   interrupt_state_t       interrupt_status;

   //Enter critical section
   interrupt_status = Enter_Critical_Section();
      mcd5408_sdm_vis = mcd5408_sdm; 
   TPU_GLOBAL_RAM_vis = (TPU_GLOBAL_RAM_T *)TPU_GLOBAL_ADDRESS(index);

   // Following steps should executed before calling the initialize function

   // Initialization TCR1,Entry table,CFSR and SIU and host interrupt
   TPU_Initialize_Channel(index, configure);

   // Initialization of PRAM start address in CPBA
   TPU_Set_Static_Base_Address(index, configure);

   //TCR1 Time base initialisation is taken acre in the TPU Initialise device function
   //Inform the EPPE algorithm of the TCR1CS setting by  writing 
   //TRUE(1)/FALSE (0) to the Options flag TCR1CS_Set.
   mcd5408_sdm->Options.F.TCR1CS_Set = p_tpu->Clock[index].TBCR.F.TCR1CS;

   // Set the TCR2 angle mode option
   switch( parameters->angle_mode )
   {
      case EPPWMT_ANGLE_MODE_DISABLED :
         mcd5408_sdm->Options.F.TCR2_Option = EPPE_TIME_MODE;
         break;
      case EPPWMT_ANGLE_MODE_PLL :
         mcd5408_sdm->Options.F.TCR2_Option = EPPE_ANGLE_HW;
         break;
      case EPPWMT_ANGLE_MODE_EDGE_COUNT :
         mcd5408_sdm->Options.F.TCR2_Option = EPPE_EDGE_COUNT;
         break;
      default :
         break;
   }

   // In angle mode, disable TCR2 until the initialization HSR is completed
   if( EPPE_TIME_MODE != mcd5408_sdm->Options.F.TCR2_Option )
   {
      temp_tbcr.U32 = p_tpu->Clock[index].TBCR.U32;

      // Disable Angle Clock
      temp_tbcr.F.AM = false;
      // Disable TCR2 hw control
      temp_tbcr.F.TCR2CTL = TPU_TCR2_SHUTDOWN;

      p_tpu->Clock[index].TBCR.U32 = temp_tbcr.U32;
   }

   //falling edge tempoary
      mcd5408_sdm->Options.F.Critical_Edge = EPPE_CRIT_FALLING;


   // Select the time base for crtical edge time( FM0 )
   // TCR1 Time base tempoary
      p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM0 = EPPE_TIMEBASE_TCR1;


   // Select CAM Normal Mode( FM1 )
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 =  EPPE_CAM_NORMAL_MODE;

   // Select the filter configuration and initialize the filter time
   if(EPPE_HW_MIN_PERIOD == parameters->filter_type )
   {
      // HW filtering
      mcd5408_sdm->Options.F.Min_Period_Method = EPPE_HW_MIN_PERIOD;

      mcd5408_sdm->Options.F.Min_Period = parameters->filter_value;
   }
   else if(EPPE_SW_MIN_PERIOD == parameters->filter_type )
   {
      // SW filtering
      mcd5408_sdm->Options.F.Min_Period_Method = EPPE_SW_MIN_PERIOD;

      mcd5408_sdm->Options.F.Min_Period = parameters->filter_value;
   }
   else
   {
      // No additional filtering
     mcd5408_sdm->Options.F.Min_Period_Method = EPPE_HW_MIN_PERIOD;
     mcd5408_sdm->Options.F.Min_Period = 0x0000;
   }

   // Initialize edge time array mask
   mcd5408_sdm->Links.F.Array_Mask = parameters->edge_array_mask;

   if(true == parameters->gap_detect_enable)
   {
      // Enable gap detect
      mcd5408_sdm->Options.F.Gap_Detect_Enabled = MCD5408_GAP_DETECT_ENABLE;
   }
   else
   {
      // Disable gap detect
      mcd5408_sdm->Options.F.Gap_Detect_Enabled = MCD5408_GAP_DETECT_DISABLE;
   }

   if(EPPE_1_X__Y_1 == parameters->gap_detect_method)
   {
      // Use 1_X__Y_1 method for gap detection
      mcd5408_sdm->Options.F.Gap_Detect_Method = EPPE_1_X__Y_1;

      mcd5408_sdm->Mult_1_X = parameters->gap_detect_ratio;

      mcd5408_sdm->Mult_Y_1 = parameters->gap_detect_ratio;
   }
   else
   {
      // Use Percent period method for gap detection
      mcd5408_sdm->Options.F.Gap_Detect_Method = EPPE_PERCENT_PERIOD;

      mcd5408_sdm->Percent_Multiplier = parameters->gap_detect_ratio;
   }

   // Set the Gap size & Gap count
   mcd5408_sdm->Gap_Size = parameters->gap_size;

   // Throw the gap count to far future
   mcd5408_sdm->Gap_Count = (uint16_t)(mcd5408_sdm->Critical_Coherent_Edge.F.Count-1);

   //   Reverse Crank Pulses detection is disabled during initialization
   mcd5408_sdm->Dir_Crank_Params.F.Reverse_Detect_Enable = 0;
   //   Reverse Crank Pulses processing is disabled during initialization
   mcd5408_sdm->Dir_Crank_Params.F.Reverse_Process_Enable = 0;
   //   During initialization clear LS_Gap_Detect_Disable
   mcd5408_sdm->Dir_Crank_Params.F.LS_Gap_Detect_Disable = 0;

   mcd5408_sdm->Dir_Crank_Params.F.PW_Threshold = 0;

   // Disable links
   mcd5408_sdm->Link_Count.F.Count_1 = 0x00;

   mcd5408_sdm->Link_Count.F.Count_2 = 0x00;

   mcd5408_sdm->Links.F.Link_Pointer = 0x000000;

   // Tachometer channel- no action here, host should initialize

   // CAM History - no action here, host should initialize

   ENGINE_GLOBAL_RAM(index).F.pEPPE_Engine_Data.F.pEPPE = (uint32_t)
            ((uint32_t)(&(mcd5408_sdm->Critical_Coherent_Edge.U32[0])) -
            TPU_SDM_START(index));
   //Disable all IRQs - host should enable IRQs

   // Clear IRQ Enable mask; bits 25 to 31
   mcd5408_sdm->IRQ_Edge_Time_1.U8[0]= 0x00;
   // Clear IRQ Request bits; bits 25 to 31
   mcd5408_sdm->IRQ_Edge_Time_2.U8[0] = 0x00;

   // Enable interrupt to host
   // MCD5408_Enable_Host_Interrupt
   p_tpu->CIER[index].U32 |= (uint32_t)(1 << channel);

   // DMA trigger set up
  //TPU_TRANSFER_REQUEST_DISABLE
   p_tpu->CDTRER[index].U32 &= ~((uint32_t)(1 << channel)); 

   if( EPPE_EDGE_COUNT == mcd5408_sdm->Options.F.TCR2_Option )
   {
      temp_tbcr.U32 = p_tpu->Clock[index].TBCR.U32;

      // Enable Angle Clock
      temp_tbcr.F.AM = true;

      // Ensure Disabled TCR2 hw control
      temp_tbcr.F.TCR2CTL = TPU_TCR2_SHUTDOWN;

      p_tpu->Clock[index].TBCR.U32 = temp_tbcr.U32;
   }
   // Issue HSR
   TPU_Set_HSR(index, configure, EPPE_HSR_INIT);

   // Set channel priority CPR
   TPU_Channel_Enable(index, configure);

   // Wait until the channel not active
   TPU_Wait_HSR_Request_Complete(index, configure);

   // Initialize Angle hardware
   if( EPPE_ANGLE_HW == mcd5408_sdm->Options.F.TCR2_Option )
   {
      temp_tbcr.U32 = p_tpu->Clock[index].TBCR.U32;

      // Enable Angle Clock
      temp_tbcr.F.AM = true;

      if(EPPE_CRIT_RISING == mcd5408_sdm->Options.F.Critical_Edge)
      {
         temp_tbcr.F.TCR2CTL = TPU_TCR2_RISE_TRANSITION_INC_TCR2;
      }
      else
      {
         temp_tbcr.F.TCR2CTL = TPU_TCR2_FALL_TRANSITION_INC_TCR2;
      }

      p_tpu->Clock[index].TBCR.U32 = temp_tbcr.U32;
   }

   // Exit critical section
   Leave_Critical_Section( interrupt_status );

}



//=============================================================================
// MCD5408_Shutdown
//=============================================================================
void MCD5408_Shutdown(
   TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{
   interrupt_state_t  interrupts_status;
     TPU_Channel_T channel;
  channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   // Enter critical section
   interrupts_status = Enter_Critical_Section();

   while(0 != p_tpu->Channel_Map[index].Channel_Control[channel].CHSRR.F.HSR)
   {
      // Wait Until Channel Not Active
   }

   // Issue Shutdown HSR
   TPU_Set_HSR(index, configure, EPPE_HSR_SHUTDOWN);

   while(0 != p_tpu->Channel_Map[index].Channel_Control[channel].CHSRR.F.HSR)
   {
      // Wait Until HSR completed
   }

   // Disable EPP channel
   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CPR = TPU_CHANNEL_PRIORITY_DISABLED;

   // Exit critical section
   Leave_Critical_Section( interrupts_status );

}

//=============================================================================
// MCD5408_Enable_Host_Interrupt
//=============================================================================
void MCD5408_Enable_Host_Interrupt(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{

  TPU_Channel_T channel;
  channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   p_tpu->CIER[index].U32 |= (uint32_t)(1 << channel);
}

//=============================================================================
// MCD5408_Disable_Host_Interrupt
//=============================================================================
void MCD5408_Disable_Host_Interrupt(
         TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
   
{
  TPU_Channel_T channel;
  channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   p_tpu->CIER[index].U32 &= ~( (uint32_t) (1 << channel));
}

//=============================================================================
// MCD5408_Get_Buffered_Edge_Time
//=============================================================================
uint32_t MCD5408_Get_Buffered_Edge_Time(
      TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   // MCD5408 supports more than one IRQ, so an argument is added to select the IRQ
   EPPwMT_IRQ_T in_irq )
{
  
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   uint32_t irq_edge_time = 0;

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         irq_edge_time = mcd5408_sdm->IRQ_Edge_Time_1.F.Time;
         break;

      case EPPWMT_IRQ_2 :
         irq_edge_time = mcd5408_sdm->IRQ_Edge_Time_2.F.Time;
         break;

      case EPPWMT_IRQ_3 :
         irq_edge_time = mcd5408_sdm->IRQ_Edge_Time_3.F.Time;
         break;

      case EPPWMT_IRQ_4 :
         irq_edge_time = mcd5408_sdm->IRQ_Edge_Time_4.F.Time;
         break;

      default :
         break;
   }

   return(irq_edge_time);
}

//=============================================================================
// MCD5408_Get_Coherent_Edge_Time_And_Count
//=============================================================================
EPPwMT_Coherent_Edge_Time_And_Count_T *  MCD5408_Get_Coherent_Edge_Time_And_Count(
    TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_Coherent_Edge_Time_And_Count_T *in_edge_time_and_count )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
    // use Read Coherent function

   //Edge Time and Count are stored coherenty, so no coherency check needed
   in_edge_time_and_count->Time = mcd5408_sdm->Critical_Coherent_Edge.F.Time;

   in_edge_time_and_count->Count = (uint16_t)mcd5408_sdm->Critical_Coherent_Edge.F.Count;

   return( in_edge_time_and_count );
}

//=============================================================================
// MCD5408_Get_IRQ_Count_At_Last_Interrupt
//=============================================================================
uint16_t MCD5408_Get_IRQ_Count_At_Last_Interrupt(
      TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   uint16_t irq_count = 0;

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_1;
         break;

      case EPPWMT_IRQ_2 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_2;
         break;

      case EPPWMT_IRQ_3 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_3;
         break;

      case EPPWMT_IRQ_4 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_4;
         break;

      default :
         break;
   }

   return(irq_count - MCD5408_EDGE_COUNTER_RANGE_DIV2);
}

//=============================================================================
// MCD5408_Get_IRQ_Count
//=============================================================================
uint16_t MCD5408_Get_IRQ_Count(
        TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq )
{
 
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   uint16_t irq_count = 0;

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_1;
         break;

      case EPPWMT_IRQ_2 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_2;
         break;

      case EPPWMT_IRQ_3 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_3;
         break;

      case EPPWMT_IRQ_4 :
         irq_count = mcd5408_sdm->IRQ_Edge_Count_4;
         break;

      default :
         break;
   }

   return(irq_count);
}

//=============================================================================
// MCD5408_Get_Period
//=============================================================================
uint32_t MCD5408_Get_Period(
          TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   return (mcd5408_sdm->Period.F.Time);
}

//=============================================================================
// MCD5408_Set_Previous_n_1
//=============================================================================
void MCD5408_Set_Previous_n_1(
          TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint16_t       in_previous_n_1 )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   mcd5408_sdm->Previous_Y_1_Count = in_previous_n_1;

}

//=============================================================================
// MCD5408_Get_Previous_n_1
//=============================================================================
uint16_t MCD5408_Get_Previous_n_1(
          TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   return (uint16_t)mcd5408_sdm->Previous_Y_1_Count;
}

//=============================================================================
// MCD5408_Set_Previous_1_n
//=============================================================================
void MCD5408_Set_Previous_1_n(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint16_t       in_previous_1_n )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   mcd5408_sdm->Previous_1_X_Count = in_previous_1_n;
}

//=============================================================================
// MCD5408_Get_Previous_1_n
//=============================================================================
uint16_t MCD5408_Get_Previous_1_n(
           TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   return (uint16_t)mcd5408_sdm->Previous_1_X_Count;
}

//=============================================================================
// MCD5408_Set_New_IRQ_Count
//=============================================================================
void MCD5408_Set_New_IRQ_Count(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq,
   uint16_t        in_new_irq_count)
{
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         mcd5408_sdm->IRQ_Edge_Count_1 = in_new_irq_count;
         break;

      case EPPWMT_IRQ_2 :
         mcd5408_sdm->IRQ_Edge_Count_2 = in_new_irq_count;
         break;

      case EPPWMT_IRQ_3 :
         mcd5408_sdm->IRQ_Edge_Count_3 = in_new_irq_count;
         break;

      case EPPWMT_IRQ_4 :
         mcd5408_sdm->IRQ_Edge_Count_4 = in_new_irq_count;
         break;

      default :
         break;
   }
}

//=============================================================================
// MCD5408_Set_Next_IRQ_Cnt_Via_Delta
//=============================================================================
void MCD5408_Set_Next_IRQ_Cnt_Via_Delta(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   EPPwMT_IRQ_T    in_irq,
   uint16_t       in_delta_teeth )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   uint16_t           irq_cnt;

   irq_cnt = mcd5408_sdm->IRQ_Edge_Count_1;
   irq_cnt += in_delta_teeth - MCD5408_EDGE_COUNTER_RANGE_DIV2;

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         mcd5408_sdm->IRQ_Edge_Count_1 = irq_cnt;
         break;

      case EPPWMT_IRQ_2 :
         mcd5408_sdm->IRQ_Edge_Count_2 = irq_cnt;
         break;

      case EPPWMT_IRQ_3 :
         mcd5408_sdm->IRQ_Edge_Count_3 = irq_cnt;
         break;

      case EPPWMT_IRQ_4 :
         mcd5408_sdm->IRQ_Edge_Count_4 = irq_cnt;
         break;

      default :
         break;
   }
}

//=============================================================================
// MCD5408_Set_New_Gap_Count
//=============================================================================
void MCD5408_Set_New_Gap_Count(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint16_t       in_pulse_count )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   mcd5408_sdm->Gap_Count = in_pulse_count;
}

//=============================================================================
// MCD5408_Set_Gap_Count
//=============================================================================
void MCD5408_Set_Gap_Count(
           TPU_Index_T index,
    TPU_CHANNEL_Configuration_T   configure,
   uint8_t        in_delta_teeth )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   uint16_t gap_cnt;

   gap_cnt = mcd5408_sdm->Previous_Y_1_Count;

   gap_cnt += in_delta_teeth - MCD5408_DEFAULT_GAP_SIZE;

   mcd5408_sdm->Gap_Count = gap_cnt;
}

//=============================================================================
// MCD5408_Get_Gap_Count
//=============================================================================
uint16_t MCD5408_Get_Gap_Count(
            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   return(mcd5408_sdm->Gap_Count);
}

//=============================================================================
// MCD5408_Update_IRQ_Count
//=============================================================================
void MCD5408_Update_IRQ_Count(
              TPU_Index_T index,
                 TPU_T         *p_tpu,
       TPU_CHANNEL_Configuration_T   configure )
{
   interrupt_state_t  interrupts_status;
  TPU_Channel_T channel;
  channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   // Enter critical section
   interrupts_status = Enter_Critical_Section();

   while(0 != p_tpu->Channel_Map[index].Channel_Control[channel].CHSRR.F.HSR)
   {
      // Wait Until Channel Not Active
   }

   // Issue update HSR
   TPU_Set_HSR(index, configure, EPPE_HSR_UPDATE);

   // Exit critical section
   Leave_Critical_Section( interrupts_status );
}

//=============================================================================
// MCD5408_Get_Real_Period
//=============================================================================
uint32_t MCD5408_Get_Real_Period(
             TPU_Index_T index,
     TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return( (uint32_t)mcd5408_sdm->Real_Period.F.Time);
}

//=============================================================================
// MCD5408_Get_Real_Edge_Time
//=============================================================================
uint32_t MCD5408_Get_Real_Edge_Time(
             TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return( mcd5408_sdm->Real_Coherent_Edge.F.Time);
}

//=============================================================================
// MCD5408_Get_Real_Edge_Count
//=============================================================================
uint16_t MCD5408_Get_Real_Edge_Count(
             TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return( mcd5408_sdm->Real_Coherent_Edge.F.Count);
}


//=============================================================================
// MCD5408_Get_Synthetic_Edge_Cnt
//=============================================================================
uint32_t MCD5408_Get_Synthetic_Edge_Cnt(
             TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index, configure);

   return( mcd5408_sdm->Flags.F.Remaining_Synthetic_Teeth );
}

//=============================================================================
// MCD5408_Get_Time_Base
//=============================================================================
uint32_t MCD5408_Get_Time_Base(
              TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure  )
{
   return TPU_TIMER_Get_Base_Frequency( index, configure );
}

//=============================================================================
// MCD5408_Get_Max_Time
//=============================================================================
uint32_t MCD5408_Get_Max_Time(void )
{

   //return max TCR value
   return(MCD5408_MAX_TCR_COUNT);
}

//=============================================================================
// MCD5408_Set_Host_Interrupt_Status
//=============================================================================
void MCD5408_Set_Host_Interrupt_Status(
   TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure  ,
   bool            in_interrupt_status )
{
  TPU_Channel_T channel;
  channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   if ( true == in_interrupt_status )
   {
      // request host interrupt
      // Not supported in TPU
   }
   else
   {
      // clear pending host interrupt
      p_tpu->CISR[index].U32 = (uint32_t)(1 << channel);
   }

}

//=============================================================================
// MCD5408_Get_Host_Interrupt_Status
//=============================================================================
bool MCD5408_Get_Host_Interrupt_Status(
    TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure )
{

   bool status;
     TPU_Channel_T channel;
  channel =  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   status =   (bool)((p_tpu->CISR[index].U32 & (uint32_t)(1 << channel))>>channel);
   return (status);
}

//=============================================================================
// MCD5408_Set_Edge_Time_In_Array
//=============================================================================
void MCD5408_Set_Edge_Time_In_Array(
              TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  ,
   uint32_t       in_edge_time,
   uint16_t       in_edge_count )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   // Mask the edge count
   uint8_t array_index = (uint8_t)(in_edge_count & MCD5408_EDGE_TIME_ARRAY_MASK);

   mcd5408_sdm->Critical_Array[array_index].F.Time = in_edge_time;

}

//=============================================================================
// MCD5408_Get_Edge_Time_From_Array
//=============================================================================
uint32_t MCD5408_Get_Edge_Time_From_Array(
                TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure  ,
   uint16_t       in_edge_count )
{
 
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   // Mask the edge count
   uint8_t array_index = (uint8_t)(in_edge_count & MCD5408_EDGE_TIME_ARRAY_MASK);

   return(mcd5408_sdm->Critical_Array[array_index].F.Time);
}

//=============================================================================
// MCD5408_Set_Angle_Clock_Mode
//=============================================================================
void MCD5408_Set_Angle_Clock_Mode(
                TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  ,
   EPPwMT_Angle_Mode_T           in_mode )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   // Set default to TCR2 time mode
   mcd5408_sdm->Options.F.TCR2_Option = EPPE_TIME_MODE;

   if( EPPWMT_ANGLE_MODE_PLL == in_mode )
   {
      mcd5408_sdm->Options.F.TCR2_Option = EPPE_ANGLE_HW;
   }
   else if( EPPWMT_ANGLE_MODE_EDGE_COUNT == in_mode)
   {
      mcd5408_sdm->Options.F.TCR2_Option = EPPE_EDGE_COUNT;
   }
}

//=============================================================================
// MCD5408_Get_Angle_Clock_Mode
//=============================================================================
EPPwMT_Angle_Mode_T MCD5408_Get_Angle_Clock_Mode(
                   TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure  )
{
 
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   EPPwMT_Angle_Mode_T angle_mode;

   // Get TCR2 time option
   MCD5408_TCR2_Option_T tcr2_option = (MCD5408_TCR2_Option_T)mcd5408_sdm->Options.F.TCR2_Option;

   if( EPPE_ANGLE_HW == tcr2_option )
   {
      angle_mode = EPPWMT_ANGLE_MODE_PLL;
   }
   else if( EPPE_EDGE_COUNT == tcr2_option)
   {
      angle_mode = EPPWMT_ANGLE_MODE_EDGE_COUNT;
   }
   else
   {
      angle_mode = EPPWMT_ANGLE_MODE_DISABLED;
   }

   return(angle_mode);
}

//=============================================================================
// MCD5408_Get_Only_Edge_Time_From_Array
//=============================================================================
uint32_t MCD5408_Get_Only_Edge_Time_From_Array(
                  TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure ,
   uint16_t       in_edge_count )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   // Mask the edge count
   uint8_t array_index = (uint8_t)(in_edge_count & MCD5408_EDGE_TIME_ARRAY_MASK);

   return(mcd5408_sdm->Critical_Array[array_index].F.Time);
}

//=============================================================================
// MCD5408_Set_Period_Calculation_Method
//=============================================================================
void MCD5408_Set_Period_Calculation_Method(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure ,
   bool           in_calculation_method )
{
    MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   mcd5408_sdm->Options.F.Period_Calc_Enabled = in_calculation_method;
}

//=============================================================================
// MCD5408_Get_Period_Calculation_Method
//=============================================================================
bool MCD5408_Get_Period_Calculation_Method(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   return((bool)mcd5408_sdm->Options.F.Period_Calc_Enabled);
}

//=============================================================================
// MCD5408_Set_Gap_Period_Fmult
//=============================================================================
void MCD5408_Set_Gap_Period_Fmult(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure ,
   uint32_t       in_fractional_multiplier )
{


   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   // Gap_Fmult type is uint16_t
   mcd5408_sdm->Gap_Fmult = (uint16_t)in_fractional_multiplier;
}

//=============================================================================
// MCD5408_Get_Gap_Period_Fmult
//=============================================================================
uint32_t MCD5408_Get_Gap_Period_Fmult(
                     TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   // Gap_Fmult type is uint16_t
   return(mcd5408_sdm->Gap_Fmult);
}

//=============================================================================
// MCD5408_BACKUP_MODE_Initialize_Channel
//=============================================================================
void MCD5408_BACKUP_MODE_Initialize_Channel(
   TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   void            *in_init )
{


   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
     TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   uint32_t channel_mask;

   uint32_t current_time;

   interrupt_state_t  interrupts_status;

   TPU_TBCR_T              temp_tbcr;

   // Check if TCR2 is in time mode, backup not supported in time mode
   if( MCD5408_TCR2_TIME_MODE != mcd5408_sdm->Options.F.TCR2_Option )
   {
      //Enter critical section
      interrupts_status = Enter_Critical_Section();

      //Disable EPP channel
      p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CPR = TPU_CHANNEL_PRIORITY_DISABLED;

      channel_mask =  1 << channel;
      while(p_tpu->CSSR[index].U32 & channel_mask != 0)
      {
         // Wait as long as the channel is busy
      }

      // Get TBCR value
      temp_tbcr.U32 = p_tpu->Clock[index].TBCR.U32;

      // MCD recommends a value of 6
      temp_tbcr.F.TCR2CTL = TPU_TCR2_RESERVED_2;
      temp_tbcr.F.AM = true;

      // Enable angle mode
      p_tpu->Clock[index].TBCR.U32 = temp_tbcr.U32;

      // Update Gap Count

      mcd5408_sdm->Options.F.Min_Period_Method = EPPE_SW_MIN_PERIOD;

      if( (p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 ) == EPPE_CAM_NORMAL_MODE )
      {
         // Convert critical edge count to real edge count
         mcd5408_sdm->Gap_Detect_Count =
            (uint16_t)( mcd5408_sdm->Gap_Detect_Count +
               (uint16_t)( mcd5408_sdm->Real_Coherent_Edge.F.Count -
                           mcd5408_sdm->Critical_Coherent_Edge.F.Count ));
      }

      p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 = EPPE_CAM_BACKUP_MODE;

      mcd5408_sdm->IRQ_Edge_Time_4.F.Backups_Left = 0;

      // Set bkup_1st_Edge_Time
      mcd5408_sdm->Backup.F.First_Edge_Time = TPU_TIMER_Get_Value_Channel(index,configure );

      mcd5408_sdm->Backup.F.Between_Cams = 0;

      // Re-enable EPP channel
      TPU_Channel_Enable(index,configure );

      // Exit critical section
      Leave_Critical_Section( interrupts_status );

   }
}

//=============================================================================
// Initialize_Edge_Time_Buffer
//
// @func This function is designed to be used internal to the EPPE device
//       driver. This function will initialize the EPPE edge time buffer
//       based on the most recent hires period. This will write to all of
//       the buffered edge times so that it appears the the engine has been
//       running at a steady engine speed.
//       The EPPE channel must be disabled before calling this function.
//       Interrupts must be disabled before calling this channel. The
//       EPPE channel must be initialize by calling Initialize before calling
//       this interface.
//
// @parm IO_Eppwmt_C_T * | in_eppwmt | A handle to the device.
//
// @rdesc none
//
// @end
//=============================================================================
static void Initialize_Edge_Time_Buffer    (                 
TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure )
{
   uint32_t crank_period;
   uint32_t edge_time;
   uint8_t  start_index;
 
   uint16_t index_mask;

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   index_mask = (uint16_t)mcd5408_sdm->Links.F.Array_Mask;

   // Read crank data for current edge
   crank_period = (uint32_t)mcd5408_sdm->Period.F.Time;
   start_index  = (uint8_t)(mcd5408_sdm->Critical_Coherent_Edge.F.Count&
                  index_mask);
   index        = (uint8_t)((uint8_t)(start_index - 1) & index_mask);
   edge_time    = ((uint32_t)( mcd5408_sdm->Critical_Coherent_Edge.F.Time
                  - crank_period) & MCD5408_MAX_TCR_COUNT);

   // Synthesize edge time data base on current crank period
   do
   {
     // The following registers can only be written if the EPPE
     // primitive is not currently running!
      mcd5408_sdm->Critical_Array[index].F.Time= edge_time;

      index = (uint8_t)((uint8_t)(index - 1) & index_mask);
      edge_time = ((uint32_t)(edge_time - crank_period) & MCD5408_MAX_TCR_COUNT);

   } while( index != start_index );
}

//=============================================================================
// MCD5408_BACKUP_MODE_Enter_Backup_Service_Request
//=============================================================================
void MCD5408_BACKUP_MODE_Enter_Backup_Service_Request(
    TPU_Index_T index,
   TPU_T         *p_tpu,
       TPU_CHANNEL_Configuration_T   configure ,
   uint32_t      in_backup_first_edge_time,
   uint32_t      in_backup_period,
   uint16_t      in_backup_first_edge_count,
   uint16_t      in_backups_between_cams )
{


   uint32_t channel_mask;

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );

   TPU_TBCR_T temp_tbcr;

   interrupt_state_t  interrupts_status;

   uint8_t backup_mode;

   TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   if( (p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 ) == EPPE_CAM_BACKUP_MODE )
   {

      // Enter critical section
      interrupts_status = Enter_Critical_Section();

      // Disable EPP channel
      p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CPR = TPU_CHANNEL_PRIORITY_DISABLED;

      channel_mask =  1 << channel;
      while(p_tpu->CSSR[index].U32 & channel_mask != 0)
      {
         // Wait as long as the channel is busy
      }

      // Clear Bkups_Left
      mcd5408_sdm->IRQ_Edge_Time_4.F.Backups_Left = 0;

      // Set bkup_1st_Edge_Time
      mcd5408_sdm->Backup.F.First_Edge_Time = in_backup_first_edge_time;

      // Set Period
      mcd5408_sdm->Period.F.Time = in_backup_period;

      // Set Bkups_Between_Cams
      mcd5408_sdm->Backup.F.Between_Cams = in_backups_between_cams;

      // Initialize Critical Edge Time
      mcd5408_sdm->Critical_Coherent_Edge.F.Time =
         ( in_backup_first_edge_time - in_backup_period ) & MCD5408_MAX_TCR_COUNT;

      // Initialize Critical Edge Count
      mcd5408_sdm->Critical_Coherent_Edge.F.Count =
         (uint16_t)( in_backup_first_edge_count - 1 );

      // Initialize Hires Buffer
      Initialize_Edge_Time_Buffer(index,configure );

      // Issue Backup HSR
      TPU_Set_HSR(index,configure , EPPE_HSR_REQUEST_BKUP);

      // Re-enable EPP channel
      TPU_Channel_Enable(index,configure );

      // Exit critical section
      Leave_Critical_Section( interrupts_status );
   }
}

//=============================================================================
// MCD5408_BACKUP_MODE_Request_Backup_Edges
//=============================================================================
void MCD5408_BACKUP_MODE_Request_Backup_Edges(
    TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   uint32_t      in_backup_first_edge_time,
   uint32_t      in_backup_period,
   uint16_t      in_backup_first_edge_count,
   uint16_t      in_backups_between_cams )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
   MCD5408_Backup_T   backup_data;
   uint16_t           crit_edge_count;
   uint32_t channel_mask;
      TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   if( (p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 ) == EPPE_CAM_BACKUP_MODE )
   {
      crit_edge_count = (uint16_t)( in_backup_first_edge_count - 1 );
      channel_mask =  1 << channel;

      // If Bkups_Left = 0 and EPPE channel is not running and critical
      // edge count is not as expected then restart backup edges
      if(( mcd5408_sdm->IRQ_Edge_Time_4.F.Backups_Left== 0     ) &&
         (p_tpu->CSSR[index].U32 & channel_mask == 0) &&
         ( mcd5408_sdm->Critical_Coherent_Edge.F.Count!= crit_edge_count ))
      {
         MCD5408_BACKUP_MODE_Enter_Backup_Service_Request(      index,
                                          p_tpu,
                                          configure,
                                          in_backup_first_edge_time,
                                          in_backup_period,
                                          in_backup_first_edge_count,
                                          in_backups_between_cams );
      }
      else
      {
         // Set bkup_1st_Edge_Time
         backup_data.F.First_Edge_Time = in_backup_first_edge_time;

         // Set Bkups_Between_Cams
         backup_data.F.Between_Cams = in_backups_between_cams;

         mcd5408_sdm->Backup.U32 = backup_data.U32;

         // Set Period
         mcd5408_sdm->Period.F.Time = in_backup_period;

         // Issue Backup HSR
         TPU_Set_HSR(index,configure, EPPE_HSR_REQUEST_BKUP);
      }
   }
}

//=============================================================================
// MCD5408_BACKUP_MODE_Exit_Backup_Service_Request
//=============================================================================
void MCD5408_BACKUP_MODE_Exit_Backup_Service_Request(
      TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   void          *in_init )
{

   MCD5408_Channel_Init_T *parameters = (MCD5408_Channel_Init_T*)in_init;
   MCD5408_SDM_T         *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure );
      TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   uint32_t         cssr_channel_mask;
   TPU_TBCR_T               temp_tbcr;
   interrupt_state_t interrupt_status;

   // Enter critical section
   interrupt_status = Enter_Critical_Section();

   // Disable EPP channel
   TPU_Channel_Disable(index, configure);

   cssr_channel_mask =  1 << channel;
   while(p_tpu->CSSR[index].U32 & cssr_channel_mask != 0)
   {
      // Wait as long as the channel is busy
   }

   if(mcd5408_sdm->Options.F.TCR2_Option == MCD5408_TCR2_ANGLE_MODE)
   {
      temp_tbcr.U32 = p_tpu->Clock[index].TBCR.U32;

      if(mcd5408_sdm->Options.F.Critical_Edge == EPPE_CRIT_RISING)
      {
         temp_tbcr.F.TCR2CTL = TPU_TCR2_RISE_TRANSITION_INC_TCR2;
      }
      else
      {
         temp_tbcr.F.TCR2CTL = TPU_TCR2_FALL_TRANSITION_INC_TCR2;
      }

      // Enable Angle Clock
      temp_tbcr.F.AM = true;

      p_tpu->Clock[index].TBCR.U32 = temp_tbcr.U32;
   }

   // Set Min_Period_Method
   mcd5408_sdm->Options.F.Min_Period_Method = parameters->filter_type;

   // Update Gap Count
   if( p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 == EPPE_CAM_BACKUP_MODE )
   {
      // Convert real edge count to critical edge count
      mcd5408_sdm->Gap_Detect_Count =
         (uint16_t)( mcd5408_sdm->Gap_Detect_Count +
            (uint16_t)( mcd5408_sdm->Critical_Coherent_Edge.F.Count -
                        mcd5408_sdm->Real_Coherent_Edge.F.Count ));
   }

   // Set to normal mode
   p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 = MCD5408_CAM_NORMAL_MODE;

   mcd5408_sdm->IRQ_Edge_Time_4.F.Backups_Left = 0;

   // Store the last real edge time
   mcd5408_sdm->Critical_Coherent_Edge.F.Time = mcd5408_sdm->Real_Coherent_Edge.F.Time;

   mcd5408_sdm->Period.F.Time = mcd5408_sdm->Real_Period.F.Time;


   // Adjust critical array
   Initialize_Edge_Time_Buffer(index,configure );
   // Adjust gap count

   // Issue exit HSR
   TPU_Set_HSR(index,configure, EPPE_HSR_EXIT_BKUP);

   // Set channel priority CPR
   TPU_Channel_Enable(index,configure);

   // Exit critical section
   Leave_Critical_Section( interrupt_status );

}

//=============================================================================
// MCD5408_BACKUP_MODE_Get_Coherent_Real_Edge_Time_And_Count
//=============================================================================
void MCD5408_BACKUP_MODE_Get_Coherent_Real_Edge_Time_And_Count(
       TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,
   EPPwMT_Coherent_Edge_Time_And_Count_T    *in_edge_time_and_count )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   // Edge Time and Count are always coherent
   in_edge_time_and_count->Time = mcd5408_sdm->Real_Coherent_Edge.F.Time;
   in_edge_time_and_count->Count = (uint16_t)mcd5408_sdm->Real_Coherent_Edge.F.Count;
}

//=============================================================================
// MCD5408_BACKUP_MODE_Get_Pending_Backups
//=============================================================================
uint8_t MCD5408_BACKUP_MODE_Get_Pending_Backups(
        TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure  )
{


   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return((uint8_t)mcd5408_sdm->IRQ_Edge_Time_4.F.Backups_Left);
}

//=============================================================================
// MCD5408_Set_Links_Start1_And_Count1
//=============================================================================
void MCD5408_Set_Links_Start1_And_Count1(
          TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,
   uint8_t       in_tpu,
   uint8_t       in_start_1,
   uint8_t       in_count_1)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);
   uint8_t  start_1;

   // Bit 6 & 7 of Start_1 represtents the TPU module
   start_1 = (uint8_t)(in_start_1 | in_tpu << 6);

   // Set first channel to be linked
   mcd5408_sdm->Link_Count.F.Start_1 = start_1;

   // Set the number of consequtive channels to be linked
   mcd5408_sdm->Link_Count.F.Count_1 = in_count_1;
}

//=============================================================================
// MCD5408_Set_Links_Start2_And_Count2
//=============================================================================
void MCD5408_Set_Links_Start2_And_Count2(
           TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,
   uint8_t       in_tpu,
   uint8_t       in_start_2,
   uint8_t       in_count_2)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);
   uint8_t  start_2=0;

   // Bit 6 & 7 of Start_2 represtents the TPU module
   start_2 |= in_tpu << 6;

   // Set first channel to be linked
   mcd5408_sdm->Link_Count.F.Start_1 = start_2;

   // Set the number of consequtive channels to be linked
   mcd5408_sdm->Link_Count.F.Count_1 = in_count_2;
}

//=============================================================================
// MCD5408_Set_IRQ_X_Enable_Mask
//=============================================================================
void MCD5408_Set_IRQ_X_Enable_Mask(
            TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure , EPPwMT_IRQ_T in_irq, bool in_enable )
{


   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_1 = in_enable;
         break;

      case EPPWMT_IRQ_2 :
         mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_2 = in_enable;
         break;

      case EPPWMT_IRQ_3 :
         mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_3 = in_enable;
         break;

      case EPPWMT_IRQ_4 :
         mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_4 = in_enable;
         break;

      case EPPWMT_IRQ_GAP_DETECTED :
         mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_Gap_Detected = in_enable;
         break;

      case EPPWMT_IRQ_EDGE_REJECTED :
         mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_Edge_Rejected = in_enable;
         break;

      case EPPWMT_IRQ_CHANGE_DIR :
         mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_Change_Dir = in_enable;
         break;

      default :
         break;
   }

}

//=============================================================================
// MCD5408_Get_IRQ_X_Enable_Mask
//=============================================================================
bool MCD5408_Get_IRQ_X_Enable_Mask(
              TPU_Index_T index,
         TPU_CHANNEL_Configuration_T   configure ,  EPPwMT_IRQ_T in_irq )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);
   bool enable_state = 0;

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_1);
         break;

      case EPPWMT_IRQ_2 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_2);
         break;

      case EPPWMT_IRQ_3 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_3);
         break;

      case EPPWMT_IRQ_4 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_4);
         break;

      case EPPWMT_IRQ_GAP_DETECTED :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_Gap_Detected);
         break;

      case EPPWMT_IRQ_EDGE_REJECTED :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_Edge_Rejected);
         break;

      case EPPWMT_IRQ_CHANGE_DIR :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_1.F.IRQ_Enable_Change_Dir);
         break;

      default :
         break;
   }
   return (enable_state);
}

//=============================================================================
// MCD5408_Get_IRQ_X_Request
//=============================================================================
bool MCD5408_Get_IRQ_X_Request(
                 TPU_Index_T index,
        TPU_CHANNEL_Configuration_T   configure , EPPwMT_IRQ_T in_irq )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);
   bool enable_state = 0;

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_1);
         break;

      case EPPWMT_IRQ_2 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_2);
         break;

      case EPPWMT_IRQ_3 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_3);
         break;

      case EPPWMT_IRQ_4 :
         enable_state = (uint8_t)(mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_4);
         break;

      case EPPWMT_IRQ_GAP_DETECTED :
         enable_state = (uint8_t)mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_Gap_Detected;
         break;

      case EPPWMT_IRQ_EDGE_REJECTED :
         enable_state = (uint8_t)mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_Edge_Rejected;
         break;

      case EPPWMT_IRQ_CHANGE_DIR :
         enable_state = (uint8_t)mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_Change_Dir;
         break;

      default :
         break;
   }

   return (enable_state);
}

//=============================================================================
// MCD5408_Clear_IRQ_X_Request
//=============================================================================
void MCD5408_Clear_IRQ_X_Request(
      TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure ,
   EPPwMT_IRQ_T in_irq )
{


   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);
  TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   interrupt_state_t  interrupts_status;

   uint32_t channel_mask;

   TPU_Channel_Priority_T current_priority;

   //Enter critical section
   interrupts_status = Enter_Critical_Section();

   //Get the current priority
   current_priority = (TPU_Channel_Priority_T)p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CPR;

   //Disable EPP channel
   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CPR = TPU_CHANNEL_PRIORITY_DISABLED;

   channel_mask =  1 << channel;
   while(p_tpu->CSSR[index].U32 & channel_mask != 0)
   {
      // Wait as long as the channel is busy
   }

   MCD5408_Set_Host_Interrupt_Status(index, p_tpu, configure, false);

   switch(in_irq)
   {
      case EPPWMT_IRQ_1 :
         mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_1 = 0;
         break;

      case EPPWMT_IRQ_2 :
         mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_2 = 0;
         break;

      case EPPWMT_IRQ_3 :
         mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_3 = 0;
         break;

      case EPPWMT_IRQ_4 :
         mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_4 = 0;
         break;

      case EPPWMT_IRQ_GAP_DETECTED :
         mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_Gap_Detected = 0;
         break;

      case EPPWMT_IRQ_EDGE_REJECTED :
         mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_Edge_Rejected = 0;
         break;

      case EPPWMT_IRQ_CHANGE_DIR :
         mcd5408_sdm->IRQ_Edge_Time_2.F.IRQ_Request_Change_Dir = 0;
         break;

      default :
         break;
   }

   // Re-enable EPP channel
   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CPR = current_priority;

   // Exit critical section
   Leave_Critical_Section( interrupts_status );

}

//=============================================================================
// MCD5408_Get_Angle_Mode_Error
//=============================================================================
uint16_t MCD5408_Get_Angle_Mode_Error(
        TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return(mcd5408_sdm->TCR2_Error_Count);
}

//=============================================================================
// MCD5408_Get_Gap_Detected_Count
//=============================================================================
uint16_t MCD5408_Get_Gap_Detected_Count(
        TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return(mcd5408_sdm->Gap_Detect_Count);
}

//=============================================================================
// MCD5408_Set_Gap_Percent
//=============================================================================
void MCD5408_Set_Gap_Percent(
          TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   uint8_t         in_gap_percent )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->Percent_Multiplier = in_gap_percent;

}

//=============================================================================
// MCD5408_Set_Cam_Channel
//=============================================================================
void MCD5408_Set_Cam_Channel(
          TPU_Index_T index,
   uint8_t         cam_channel )
{
   TPU_GLOBAL_RAM(index).Cam_Chan_Number = cam_channel;
}

//=============================================================================
// MCD5408_Set_Filter_Time
//=============================================================================
void MCD5408_Set_Filter_Time(
            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   uint16_t         in_filter_time )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->Options.F.Min_Period = in_filter_time;
}

//=============================================================================
// MCD5408_Set_IRQ_Enable
//=============================================================================
void MCD5408_Set_IRQ_Enable(
            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   uint32_t         in_enable_mask )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->IRQ_Edge_Time_1.U8[0] = (uint8_t)(in_enable_mask >> 24);

}

//=============================================================================
// MCD5408_Get_IRQ_Requests
//=============================================================================
uint32_t MCD5408_Get_IRQ_Requests(
         TPU_Index_T index,
   TPU_T         *p_tpu,
       TPU_CHANNEL_Configuration_T   configure )
{
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);
   TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   interrupt_state_t  interrupt_status;
   uint32_t cssr_channel_mask;
   uint32_t irq_mask;

   // Enter critical section
   interrupt_status = Enter_Critical_Section();

   // Disable EPP channel
   p_tpu->Channel_Map[index].Channel_Control[channel].CCR.F.CPR = TPU_CHANNEL_PRIORITY_DISABLED;

   cssr_channel_mask =  1 << channel;
   while(p_tpu->CSSR[index].U32 & cssr_channel_mask != 0)
   {
      // Verify EPP is not currently running
   }

   // Clear pending interrupt
   MCD5408_Set_Host_Interrupt_Status(index,p_tpu,configure,false );

   // The following flags can only be cleared if the EPPE primitive is not
   // currently running
   irq_mask = mcd5408_sdm->IRQ_Edge_Time_2.U8[0];

   // Clear IRQ request flags
   mcd5408_sdm->IRQ_Edge_Time_2.U8[0] = 0x00;

   // Re-enable EPP channel
   TPU_Channel_Enable(index,configure);

   // Exit critical section
   Leave_Critical_Section( interrupt_status );

   // The application requires it to be left shifted
   return( irq_mask << 24 );
}

//=============================================================================
// MCD5408_Get_CAM_History
//=============================================================================
uint32_t MCD5408_Get_CAM_History(            TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return mcd5408_sdm->Cam_History;
}

//=============================================================================
// MCD5408_Set_Critical_Edge
//=============================================================================
void MCD5408_Set_Critical_Edge(
   TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure ,
   Edge_T       in_edge )
{
    MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   if( in_edge == EDGE_RISING)
   {
      // Selet rising edge
      mcd5408_sdm->Options.F.Critical_Edge = EPPE_CRIT_RISING;
   }
   else
   {
      // Selet falling edge
      mcd5408_sdm->Options.F.Critical_Edge = EPPE_CRIT_FALLING;
   }
}

//=============================================================================
// MCD5408_Get_Real_Prev_Period
//=============================================================================
uint32_t MCD5408_Get_Real_Prev_Period(    TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure  )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return mcd5408_sdm->Real_Prev_Period.F.Time;
}

//=============================================================================
// MCD5408_Clear_Gap_History
//=============================================================================
void MCD5408_Clear_Gap_History        ( TPU_Index_T index,
   TPU_T         *p_tpu,
        TPU_CHANNEL_Configuration_T   configure )
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);
   uint32_t interrupt_status;
   uint32_t cssr_channel_mask;
   TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   // Enter critical section
   interrupt_status = Enter_Critical_Section();

   // Disable EPP channel
   TPU_Channel_Disable(index,configure);

   // Verify EPPE is not currently running
   cssr_channel_mask =  1 << channel;
   while(p_tpu->CSSR[index].U32 & cssr_channel_mask != 0)
   {
      // Wait as long as the channel is busy
   }

   mcd5408_sdm->Real_Period.F.Time= MCD5408_MAX_TCR_COUNT;
   mcd5408_sdm->Real_Prev_Period.F.Time = MCD5408_MAX_TCR_COUNT;

   // Re-enable EPP channel
   TPU_Channel_Enable(index,configure);

   // Exit critical section
   Leave_Critical_Section( interrupt_status );
}

//=============================================================================
// MCD5408_Init_Edge_Time_Buffer
//=============================================================================
void MCD5408_Init_Edge_Time_Buffer(    TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure )
{
 
   uint32_t interrupt_status;
   uint32_t cssr_channel_mask;

   // Enter critical section
   interrupt_status = Enter_Critical_Section();

   // Disable EPP channel
   TPU_Channel_Disable(index,configure);

   Initialize_Edge_Time_Buffer(index,configure);

   // Re-enable EPP channel
   TPU_Channel_Enable(index,configure);

   // Exit critical section
   Leave_Critical_Section( interrupt_status );
}

//=============================================================================
// Synthesize_CAM_Buffer_Gap_Teeth
//
// @func This function will synthesize the cam samples that were missed in the
//       gap. The location of the gap is determined by the gap detect count.
//       This function is intended to be called when the crank first gains sync.
//       The gap samples will copied from just before and just after the gap
//       region.
//
// @parm IO_Eppwmt_C_T | in_eppwmt | A handle to the device.
//
// @rdesc none
//
// @end
//=============================================================================
static void Synthesize_CAM_Buffer_Gap_Teeth(    TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure )
{
   uint32_t cam_history;
   uint32_t post_gap_history;
   uint32_t in_gap_history;
   uint32_t pre_gap_history;
   uint32_t post_gap_mask;
   uint32_t gap_mask;
   uint32_t pre_gap_mask;
   uint16_t current_edge_count;
   uint16_t gap_edge_count;
   uint16_t edge_count_delta;
   uint8_t  gap_size;
   uint8_t  gap_shift;

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   gap_size           = mcd5408_sdm->Gap_Size;
   current_edge_count =
      (uint16_t)mcd5408_sdm->Critical_Coherent_Edge.F.Count;
   gap_edge_count     =
      (uint16_t)mcd5408_sdm->Gap_Detect_Count;

   edge_count_delta   = (uint16_t)( current_edge_count - gap_edge_count );

   post_gap_mask      = (uint32_t)0xffffffff >>
      (uint32_t)((MCD5408_BITS_IN_CAM_HISTORY - MCD5408_GAP_DETECT_TOOTH) - edge_count_delta );
   pre_gap_mask       = (uint32_t)0xffffffff <<
      (uint32_t)((gap_size + MCD5408_GAP_DETECT_TOOTH) + edge_count_delta );
   gap_mask           = ~post_gap_mask & ~pre_gap_mask;

   if( gap_size <= ( MCD5408_GAP_DETECT_TOOTH * 2 ))
   {
      gap_shift   = (gap_size / 2);
   }
   else
   {
      gap_shift   = MCD5408_GAP_DETECT_TOOTH;
   }

   cam_history        = mcd5408_sdm->Cam_History;
   post_gap_history   = cam_history & post_gap_mask;
   in_gap_history     = ( cam_history << gap_shift ) & gap_mask;
   pre_gap_history    = ( cam_history << gap_size ) & pre_gap_mask;

   cam_history        = pre_gap_history | in_gap_history | post_gap_history;

   // The following can only be written if EPPE is not running!
   mcd5408_sdm->Cam_History= cam_history;
}

//=============================================================================
// MCD5408_Synthesize_Gap_In_History
//=============================================================================
void MCD5408_Synthesize_Gap_In_History( TPU_Index_T index,
   TPU_T         *p_tpu,
   TPU_CHANNEL_Configuration_T   configure)
{

  TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   uint32_t interrupt_status;
   uint32_t cssr_channel_mask;

   // Enter critical section
   interrupt_status = Enter_Critical_Section();

   // Disable EPP channel
   TPU_Channel_Disable(index,configure);


   // Verify EPPE is not currently running
   cssr_channel_mask =  1 << channel;
   while(p_tpu->CSSR[index].U32 & cssr_channel_mask != 0)
   {
      // Wait as long as the channel is busy
   }

   Initialize_Edge_Time_Buffer(index,configure);

   Synthesize_CAM_Buffer_Gap_Teeth(index,configure);

   // Re-enable EPP channel
   TPU_Channel_Enable(index,configure);

   // Exit critical section
   Leave_Critical_Section( interrupt_status );
}

//=============================================================================
// MCD5408_Get_Backup_Enabled
//=============================================================================
bool MCD5408_Get_Backup_Enabled( TPU_Index_T index,
   TPU_T         *p_tpu,
 TPU_CHANNEL_Configuration_T   configure)
{
  TPU_Channel_T channel=  configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
  bool result = false;

   if ( p_tpu->Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 == EPPE_CAM_BACKUP_MODE )
   {
      result = true;
   }

   return result;
}

//=============================================================================
// MCD5408_Set_Abs_Edge_Count
//=============================================================================
void MCD5408_Set_Abs_Edge_Count(TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   uint8_t         in_edge_count )
{
  
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->AbsEdgeCount_AccumRevEdge.F.Abs_Edge_Count = in_edge_count;

}

//=============================================================================
// MCD5408_Get_Remaining_Synth_Teeth
//=============================================================================
uint32_t MCD5408_Get_Remaining_Synth_Teeth(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return mcd5408_sdm->Flags.F.Remaining_Synthetic_Teeth;
}

//=============================================================================
// MCD5408_Get_Dir_Crank_PW
//=============================================================================
uint32_t MCD5408_Get_Dir_Crank_PW(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return mcd5408_sdm->Dir_Crank_Flags_PW.F.Dir_Crank_PW;
}

//=============================================================================
// MCD5408_Get_Crank_Backwards
//=============================================================================
bool MCD5408_Get_Crank_Backwards(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure)
 {

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return (bool) mcd5408_sdm->Dir_Crank_Flags_PW.F.Crank_Backwards;
}

//=============================================================================
// MCD5408_Get_Accum_Reverse_Edges
//=============================================================================
uint16_t MCD5408_Get_Accum_Reverse_Edges(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return((uint16_t)mcd5408_sdm->AbsEdgeCount_AccumRevEdge.F.Accum_Reverse_Edges);
}


//=============================================================================
// MCD5408_Get_Accum_Edges
//=============================================================================
 uint16_t MCD5408_Get_Accum_Edges(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure)
{
 
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return((uint16_t)mcd5408_sdm->DirCount_AccumEdge.F.Accum_Edges);
}

//=============================================================================
// MCD5408_Get_Abs_Edge_Count
//=============================================================================
uint8_t MCD5408_Get_Abs_Edge_Count(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return((uint8_t)mcd5408_sdm->AbsEdgeCount_AccumRevEdge.F.Abs_Edge_Count);
}


//=============================================================================
// MCD5408_Set_Reverse_Detect_Enable
//=============================================================================
 void MCD5408_Set_Reverse_Detect_Enable(
   TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   bool   in_revdetect_enable)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->Dir_Crank_Params.F.Reverse_Detect_Enable = in_revdetect_enable;
}

 //=============================================================================
// MCD5408_Set_Reverse_Process_Enable
//=============================================================================
void MCD5408_Set_Reverse_Process_Enable(
     TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   bool   in_revprocess_enable)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->Dir_Crank_Params.F.Reverse_Process_Enable = in_revprocess_enable;
}

//=============================================================================
// MCD5408_Set_LS_Gap_Detect_Disable
//=============================================================================
void MCD5408_Set_LS_Gap_Detect_Disable(
   TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   bool   in_LS_gap_detect_disable)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->Dir_Crank_Params.F.LS_Gap_Detect_Disable = in_LS_gap_detect_disable;
}

//=============================================================================
// MCD5408_Set_Dir_PW_Threshold
//=============================================================================
 void MCD5408_Set_Dir_PW_Threshold(
      TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   uint32_t   in_threshold)
{
  
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->Dir_Crank_Params.F.PW_Threshold = in_threshold;
}

//=============================================================================
// MCD5408_Set_Accum_Reverse_Edges
//=============================================================================
void MCD5408_Set_Accum_Reverse_Edges(
      TPU_Index_T index,
 TPU_CHANNEL_Configuration_T   configure,
   uint16_t   in_edges)
{

   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   mcd5408_sdm->AbsEdgeCount_AccumRevEdge.F.Accum_Reverse_Edges = in_edges;
   // Just to make sure eTPU doesn't interfere this write, we should
   // write twice to this parameter.
   mcd5408_sdm->AbsEdgeCount_AccumRevEdge.F.Accum_Reverse_Edges = in_edges;
}

//=============================================================================
// MCD5408_Get_Dir_Crank_PW
//=============================================================================
uint8_t MCD5408_Get_Chg_Dir_Count(
      TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
  
   MCD5408_SDM_T   *mcd5408_sdm = (MCD5408_SDM_T*)TPU_Get_Channel_SDM_Start_Address(index,configure);

   return((uint8_t)mcd5408_sdm->DirCount_AccumEdge.F.Chg_Dir_Count);
}

