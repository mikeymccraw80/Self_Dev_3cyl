
#include "dd_dfilter.h"
#include "io_config_knock.h"
#include "io_config_dma.h"
#include "dd_siu_hwinfo.h"
#include "dd_dma_interface.h"

//=============================================================================
// DEC_FILTER
//=============================================================================
#define SECTION_DEC_FILTER_REGISTER
#include "section.h"
DEC_FILTER_T DEC_FILTER_A;
#define SECTION_END
#include "section.h"

//=============================================================================
// DMA Buffers
//=============================================================================
 int16_t DEC_FILT_A_Result_Buffer_A[DEC_FILT_A_DMA_RESULT_BUFF_SIZE];
  __attribute__ (( aligned(2) ))  int16_t DEC_FILT_A_Result_Buffer_B[DEC_FILT_A_DMA_RESULT_BUFF_SIZE];
 uint16_t DEC_FILT_A_Result_Buffer_C[DEC_FILT_A_DMA_RESULT_BUFF_SIZE];

extern uint16_t      KNOCK_DSP_Process_Count_Winagte_PostStatus;
//=============================================================================
// DEC_FILTER_MCR_SETUP
//=============================================================================
void DEC_FILTER_MCR_SETUP( const uint32_t  *filt_coeff, const DECFILT_MCR_T dfilter_mcr,const  int16_t *dfilter_buffer )
{
   uint8_t coeff_cntr;
   uint8_t prefill_cntr;
   //disable DMA 
   if(CPU_Info==CPU_LCI)
   {
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_FILL_BUF_A);
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_DRAIN_BUF_A );
   }
   else
   {
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_FILL_BUF );
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_DRAIN_BUF);
   }


   // execute soft reset to initialize decimation filter interface
   DEC_FILTER_A.MCR.F.SRES = 1;

     //wait till Filter is Busy
   while (DEC_FILTER_A.MSR.F.BSY == 1 ){}

   DEC_FILTER_A.MCR.F.MDIS = 1;  //Input disabled here

   DEC_FILTER_A.MCR.U32 =dfilter_mcr.U32;  //Initialise the filter params


   //Initialise the coefficient registers
   for( coeff_cntr = 0; coeff_cntr < DECFILT_COEFF_QUANTITY ;coeff_cntr++)
   {
      DEC_FILTER_A.COEF[coeff_cntr].U32 = *filt_coeff;
	  filt_coeff = filt_coeff ++;//sizeof(uint32_t);
   }
   // enable decimation filter inputs
   DEC_FILTER_A.MCR.F.MDIS = 0;
   // execute soft reset to initialize decimation filter interface
   DEC_FILTER_A.MCR.F.SRES = 1;


    //flush all tempoary data in DEC        
   DEC_FILTER_A.IB.F.FLUSH = 0x01;
   //initializes the Decimation Filter to a initial state.Self negative.      
   while(DEC_FILTER_A.IB.F.FLUSH) { }    
   
   //Prefill  
   DEC_FILTER_A.IB.F.PREFILL = 0x01;
   
  for (prefill_cntr=0;prefill_cntr<DEC_FILT_A_DMA_PREFILL_SIZE;prefill_cntr++)
   {
   	DEC_FILTER_A.IB.F.INPBUF= (unsigned int)dfilter_buffer[prefill_cntr];
   	while(DEC_FILTER_A.MSR.F.BSY){}
  }
   
  DEC_FILTER_A.IB.F.PREFILL = 0x00;// cancel prefill


}

//=============================================================================
// DEC_FILTER_DMA_SETUP_LOWPASS
//=============================================================================

void DEC_FILTER_DMA_SETUP_LOWPASS(void)
{

  DMA_Channel_T dfilter_input_dma_ch, dfilter_output_dma_ch;

   if(CPU_Info==CPU_LCI)
   {
     dfilter_input_dma_ch = DMA_CHANNEL_DECFIL_FILL_BUF_A; 
     dfilter_output_dma_ch = DMA_CHANNEL_DECFIL_DRAIN_BUF_A;
   }
   else
   {
     dfilter_input_dma_ch = DMA_CHANNEL_DECFIL_FILL_BUF; 
     dfilter_output_dma_ch = DMA_CHANNEL_DECFIL_DRAIN_BUF;
   }


	DMA_Initialize_Channel(
	dfilter_input_dma_ch,
	DMA_DECFIL_FILL_BUFA_LowPass_Source_Address,
	DMA_DECFIL_FILL_BUFA_LowPass_Second_32Bit,
	DMA_DECFIL_FILL_BUFA_LowPass_Third_32Bit,
	DMA_DECFIL_FILL_BUFA_LowPass_Slast,
	DMA_DECFIL_FILL_BUFA_LowPass_Dest_Address,
	DMA_DECFIL_FILL_BUFA_LowPass_Sixth_32Bit,
	DMA_DECFIL_FILL_BUFA_LowPass_Dlast,
	DMA_DECFIL_FILL_BUFA_LowPass_Eighth_32Bit);

	DMA_Set_Channel_Transfer_Count(dfilter_input_dma_ch, 
		(uint32_t)(KNOCK_DSP_Process_Count_Winagte_PostStatus -DEC_FILT_A_DMA_PREFILL_SIZE));

	//DMA_Set_Channel_SLast(dfilter_input_dma_ch, (uint32_t)(-((KNOCK_DSP_Process_Count_Winagte_PostStatus -DEC_FILT_A_DMA_PREFILL_SIZE)*sizeof(uint16_t))));


	DMA_Initialize_Channel(
	dfilter_output_dma_ch,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Source_Address,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Second_32Bit,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Third_32Bit,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Slast,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Dest_Address,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Sixth_32Bit,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Dlast,
	DMA_DECFIL_DRAIN_BUFA_LowPass_Eighth_32Bit);

	DMA_Set_Channel_Transfer_Count(dfilter_output_dma_ch, 
		(uint32_t)((KNOCK_DSP_Process_Count_Winagte_PostStatus -DEC_FILT_A_DMA_PREFILL_SIZE) /DEC_FILT_A_DMA_LOWPASS_DECRATE));


	//DMA_Set_Channel_DLast(dfilter_output_dma_ch,
        //                                  (uint32_t)(400-((KNOCK_DSP_Process_Count_Winagte_PostStatus -DEC_FILT_A_DMA_PREFILL_SIZE) /DEC_FILT_A_DMA_LOWPASS_DECRATE))*sizeof(uint16_t));
  
}

//=============================================================================
// DEC_FILTER_DMA_SETUP_BANDPASS
//=============================================================================
void DEC_FILTER_DMA_SETUP_BANDPASS(void)
{

  DMA_Channel_T dfilter_input_dma_ch, dfilter_output_dma_ch;

   if(CPU_Info==CPU_LCI)
   {
     dfilter_input_dma_ch = DMA_CHANNEL_DECFIL_FILL_BUF_A; 
     dfilter_output_dma_ch = DMA_CHANNEL_DECFIL_DRAIN_BUF_A;
   }
   else
   {
     dfilter_input_dma_ch = DMA_CHANNEL_DECFIL_FILL_BUF; 
     dfilter_output_dma_ch = DMA_CHANNEL_DECFIL_DRAIN_BUF;
   }


	DMA_Initialize_Channel(
	dfilter_input_dma_ch,
	DMA_DECFIL_FILL_BUFA_BandPass_Source_Address,
	DMA_DECFIL_FILL_BUFA_BandPass_Second_32Bit,
	DMA_DECFIL_FILL_BUFA_BandPass_Third_32Bit,
	DMA_DECFIL_FILL_BUFA_BandPass_Slast,
	DMA_DECFIL_FILL_BUFA_BandPass_Dest_Address,
	DMA_DECFIL_FILL_BUFA_BandPass_Sixth_32Bit,
	DMA_DECFIL_FILL_BUFA_BandPass_Dlast,
	DMA_DECFIL_FILL_BUFA_BandPass_Eighth_32Bit);


			 
      DMA_Set_Channel_Transfer_Count( dfilter_input_dma_ch,
            (uint32_t)(KNOCK_DSP_Process_Count_Winagte_PostStatus/DEC_FILT_A_DMA_LOWPASS_DECRATE -DEC_FILT_A_DMA_PREFILL_SIZE-1) );



	DMA_Set_Channel_SLast(dfilter_input_dma_ch,
                                          (uint32_t)(-((KNOCK_DSP_Process_Count_Winagte_PostStatus/DEC_FILT_A_DMA_LOWPASS_DECRATE -DEC_FILT_A_DMA_PREFILL_SIZE-1)*sizeof(uint16_t))));


	DMA_Initialize_Channel(
	dfilter_output_dma_ch,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Source_Address,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Second_32Bit,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Third_32Bit,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Slast,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Dest_Address,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Sixth_32Bit,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Dlast,
	DMA_DECFIL_DRAIN_BUFA_BandPass_Eighth_32Bit);

     DMA_Set_Channel_Transfer_Count( dfilter_output_dma_ch, 
				(uint32_t)((KNOCK_DSP_Process_Count_Winagte_PostStatus/DEC_FILT_A_DMA_LOWPASS_DECRATE -DEC_FILT_A_DMA_PREFILL_SIZE-1) ));


	DMA_Set_Channel_DLast(dfilter_output_dma_ch,
                                          (uint32_t)(2*( (DEC_FILT_A_DMA_RESULT_BUFF_SIZE-KNOCK_DSP_Process_Count_Winagte_PostStatus)/4-DEC_FILT_A_DMA_PREFILL_SIZE-1)));


}
//=============================================================================
// DEC_FILTER_INOUTPUT_DMA_ENABLE
//=============================================================================
void DEC_FILTER_INOUTPUT_DMA_ENABLE(void)
{
     if(CPU_Info==CPU_LCI)
   {
         if (DEC_FILTER_A.MCR.F.DSEL == DEC_FILTER_DMA_ENABLED) 
      {
      
        DMA_Enable_Request(DMA_CHANNEL_DECFIL_DRAIN_BUF_A);
      	 
         if (DEC_FILTER_A.MCR.F.ISEL == DEC_FILTER_Input_Device_Slavebus) 
         {
            DMA_Enable_Request(DMA_CHANNEL_DECFIL_FILL_BUF_A);
         }
      	}	
   
    }
   else
   {
         if (DEC_FILTER_A.MCR.F.DSEL == DEC_FILTER_DMA_ENABLED) 
      {
      
        DMA_Enable_Request(DMA_CHANNEL_DECFIL_DRAIN_BUF);
		
         if (DEC_FILTER_A.MCR.F.ISEL == DEC_FILTER_Input_Device_Slavebus) 
         {
            DMA_Enable_Request(DMA_CHANNEL_DECFIL_FILL_BUF);
         }

      	}	

   }
 
}

//=============================================================================
// DEC_FILTER_STOP_DSP
//=============================================================================

void DEC_FILTER_STOP_DSP(void)
{

   //disable DMA 
   if(CPU_Info==CPU_LCI)
   {
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_FILL_BUF_A);
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_DRAIN_BUF_A );
   }
   else
   {
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_FILL_BUF );
      DMA_Clear_Request( DMA_CHANNEL_DECFIL_DRAIN_BUF);
   }


	   // execute soft reset to initialize decimation filter interface
   DEC_FILTER_A.MCR.F.SRES = 1;

      //wait till Filter is Busy
   while (DEC_FILTER_A.MSR.F.BSY == 1 ){}

    DEC_FILTER_A.MCR.F.MDIS = 1;  //Input disabled here

 

 
}


