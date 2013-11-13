
//=============================================================================
// Include Files
//=============================================================================
#include "dd_dma.h"
#include "io_config_dma.h"

//=============================================================================
// 
//=============================================================================
// DMA_A
//=================================================================================
#define SECTION_DMA_A_REGISTER
#include "section.h"
DMA_T DMA_A;
#define SECTION_END
#include "section.h"

//=============================================================================
// DMA_Initialize_Device
//=============================================================================
void DMA_Initialize_Device( void  )
{

   DMA_A.CR.F.ERGA = false;  // enable group Fixed priority arbitration
   DMA_A.CR.F.ERCA = false;  // enable channel Fixed priority arbitration
   DMA_A.CR.F.EDBG = false;  // disable debug
   DMA_A.CR.F.EBW  = false;  // The bufferable write signal (hprot[2]) is not
                            // asserted during AMBA AHB writes.
   // Enabling debug will cause eDMA to stall between minor loops, possibly
   //  within a major loop - i.e. will break SPI messages and Analog queues,
   //  etc. - anything that uses the eDMA has potential to copy data
   //  incorrectly.
   //DMA_CHANNEL_QADC_FISR1_CFFF_1
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR1_CFFF_1].U8 =0;
   //Enable Channel Preemption
   //Channel n can be temporarily suspended by the service request of a higher priority channel.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR1_CFFF_1].F.ECP =false;
   //Channel priority when fixed-priority arbitration is enabled.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR1_CFFF_1].F.CHPRI = DMA_CHANNEL_PRIORITY_2;
      //DMA_CHANNEL_QADC_FISR1_RFDF_1
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR1_RFDF_1].U8 =0;
   //Enable Channel Preemption
   //Channel n can be temporarily suspended by the service request of a higher priority channel.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR1_RFDF_1].F.ECP =false;
   //Channel priority when fixed-priority arbitration is enabled.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR1_RFDF_1].F.CHPRI = DMA_CHANNEL_PRIORITY_3;

   
   //DMA_CHANNEL_QADC_FISR4_CFFF_4
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR4_CFFF_4].U8 =0;
   //Enable Channel Preemption
   //Channel n can be temporarily suspended by the service request of a higher priority channel.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR4_CFFF_4].F.ECP =false;
   //Channel priority when fixed-priority arbitration is enabled.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR4_CFFF_4].F.CHPRI = DMA_CHANNEL_PRIORITY_8;


      //DMA_CHANNEL_QADC_FISR4_RFDF_4
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR4_RFDF_4].U8 =0;
   //Enable Channel Preemption
   //Channel n can be temporarily suspended by the service request of a higher priority channel.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR4_RFDF_4].F.ECP =false;
   //Channel priority when fixed-priority arbitration is enabled.
   DMA_A.CPR[DMA_CHANNEL_QADC_FISR4_RFDF_4].F.CHPRI = DMA_CHANNEL_PRIORITY_9;

      //DMA_CHANNEL_DSPI_B_SR_TFFF
   DMA_A.CPR[DMA_CHANNEL_DSPI_B_SR_TFFF].U8 =0;
   //Enable Channel Preemption
   //Channel n can be temporarily suspended by the service request of a higher priority channel.
   DMA_A.CPR[DMA_CHANNEL_DSPI_B_SR_TFFF].F.ECP =false;
   //Channel priority when fixed-priority arbitration is enabled.
   DMA_A.CPR[DMA_CHANNEL_DSPI_B_SR_TFFF].F.CHPRI = DMA_CHANNEL_PRIORITY_12;


      //DMA_CHANNEL_DSPI_B_SR_RFDF
   DMA_A.CPR[DMA_CHANNEL_DSPI_B_SR_RFDF].U8 =0;
   //Enable Channel Preemption
   //Channel n can be temporarily suspended by the service request of a higher priority channel.
   DMA_A.CPR[DMA_CHANNEL_DSPI_B_SR_RFDF].F.ECP =false;
   //Channel priority when fixed-priority arbitration is enabled.
   DMA_A.CPR[DMA_CHANNEL_DSPI_B_SR_RFDF].F.CHPRI = DMA_CHANNEL_PRIORITY_13;
	 
     //DMA_CHANNEL_MIOS_EMIOSFLAG_4
   DMA_A.CPR[DMA_CHANNEL_MIOS_EMIOSFLAG_4].U8 =0;
   //Enable Channel Preemption
   //Channel n can be temporarily suspended by the service request of a higher priority channel.
   DMA_A.CPR[DMA_CHANNEL_MIOS_EMIOSFLAG_4].F.ECP =false;
   //Channel priority when fixed-priority arbitration is enabled.
   DMA_A.CPR[DMA_CHANNEL_MIOS_EMIOSFLAG_4].F.CHPRI = DMA_CHANNEL_PRIORITY_8;


   // Disable all DMA requests
   DMA_A.ERQRL.U32 = 0;

   // Disable all DMA error interrupts
   DMA_A.EEIRL.U32 = 0;
}

//=============================================================================
// DMA_Initialize_Channel
//=============================================================================
void DMA_Initialize_Channel(
   DMA_Channel_T           channel,
   uint32_t             SADDR,
   DMA_Second_32Bit_T   F_2,
   DMA_Third_32Bit_T    F_3,
   uint32_t             SLAST,
   uint32_t             DADDR,
   DMA_Sixth_32Bit_T    F_6,
   uint32_t             DLAST_SGA,
   DMA_Eighth_32Bit_T   F_8)
{

   //Source Address (saddr)
   DMA_A.TCD[channel].F.SADDR = SADDR;
   //Transfer Attributes(smod, ssize, dmod, dsize)
   //Signed Source Address Offset (soff)
   DMA_A.TCD[channel].F.F_2 = F_2;
   //Inner ¡°Minor¡± Byte Count (nbytes)
   DMA_A.TCD[channel].F.F_3 = F_3;
   //Last Source Address Adjustment (slast)
   DMA_A.TCD[channel].F.SLAST = SLAST;
   //Destination Address (daddr)
   DMA_A.TCD[channel].F.DADDR = DADDR;
   //Current ¡°Major¡± Iteration Count (citer)
   //Signed Destination Address Offset (doff)
   DMA_A.TCD[channel].F.F_6 = F_6;
   //Last Destination Address Adjustment/Scatter Gather Address (dlast_sga)
   DMA_A.TCD[channel].F.DLAST_SGA = DLAST_SGA;
   //Beginning ¡°Major¡± Iteration Count (biter)
   //Channel Control/Statusm (bwc, major.linkch, done, active, major.e_link, e_sg, d_req, int_half, int_maj,start)
   DMA_A.TCD[channel].F.F_8 = F_8;


}

//=============================================================================
// DMA_Set_Channel_Source_Address
//=============================================================================
void DMA_Set_Channel_Transfer_Count(
   DMA_Channel_T           channel,
    uint16_t  elements_number_of)
{

   DMA_A.TCD[channel].F.F_6.F.CITER = elements_number_of;
   DMA_A.TCD[channel].F.F_8.F.BITER = elements_number_of;

}


//=============================================================================
// DMA_Set_Channel_Source_Address
//=============================================================================
void DMA_Set_Channel_Source_Address(
   DMA_Channel_T           channel,
   uint32_t     SADDR)

{
   //Source Address (saddr)
   DMA_A.TCD[channel].F.SADDR = SADDR;
   DMA_A.TCD[channel].F.SLAST = -(DMA_A.TCD[channel].F.F_6.F.CITER*DMA_A.TCD[channel].F.F_3.NBYTES);
  

}

//=============================================================================
// DMA_Set_Channel_Source_Address
//=============================================================================
void DMA_Set_Channel_Destination_Address(
   DMA_Channel_T           channel,
   uint32_t             DADDR)

{
   //Destination Address (daddr)
   DMA_A.TCD[channel].F.DADDR = DADDR;
    DMA_A.TCD[channel].F.DLAST_SGA=-(DMA_A.TCD[channel].F.F_6.F.CITER*DMA_A.TCD[channel].F.F_3.NBYTES);

}

//=============================================================================
// DMA_Set_Channel_SLast
//=============================================================================
void DMA_Set_Channel_SLast(
   DMA_Channel_T           channel,
     uint32_t             SLAST)
{

   //Last Source Address Adjustment (slast)
   DMA_A.TCD[channel].F.SLAST = SLAST;


}


//=============================================================================
// DMA_Set_Channel_DLast
//=============================================================================
void DMA_Set_Channel_DLast(
   DMA_Channel_T           channel,
     uint32_t             DLAST)
{
      //Last Destination Address Adjustment/Scatter Gather Address (dlast_sga)
   DMA_A.TCD[channel].F.DLAST_SGA = DLAST;

}

//=============================================================================
// DMA_Enable_request
//=============================================================================
void DMA_Enable_Request(DMA_Channel_T  dma_channel)
{
  DMA_A.SERQR.F.SERQ = dma_channel;
}

//=============================================================================
// DMA_clear_request
//=============================================================================
void DMA_Clear_Request(DMA_Channel_T  dma_channel)
{
  DMA_A.CERQR.F.CERQ = dma_channel;
}

//=============================================================================
// DMA_Get_Channel_Running_Status
//=============================================================================
bool DMA_Get_Channel_Running_Status(DMA_Channel_T  dma_channel)
{
  bool                    status;

     //If its not done then its running
   status = ( DMA_A.TCD[dma_channel].F.F_8.F.DONE == 0 ) ? true : false;
	   // status = ( DMA_A.TCD[dma_channel].F.F_8.F.ACTIVE== 1 ) ? true : false;
	 
    return status;
}

//=============================================================================
// DMA_Get_Channel_Biter
//=============================================================================
uint16_t  DMA_Get_Channel_Biter(DMA_Channel_T  dma_channel)
{
    uint16_t  biter;
	
    biter = DMA_A.TCD[dma_channel].F.F_8.F.BITER; 
	
   return biter;	
} 

//=============================================================================
// DMA_Get_Channel_Citer
//=============================================================================
uint16_t  DMA_Get_Channel_Citer(DMA_Channel_T  dma_channel)
{     

     uint16_t  citer;
	
    citer = DMA_A.TCD[dma_channel].F.F_6.F.CITER; 
	
   return citer;
}
//=============================================================================
// DMA_clear_request
//=============================================================================
void DMA_Clear_MAJ_Pending_INT(DMA_Channel_T  dma_channel)
{
         DMA_A.CIRQR.U8 = dma_channel;
}

//=============================================================================
// DMA_Clear_Device
//=============================================================================
void DMA_Clear_Device(  void)
{
  
   DMA_A.CR.U32 = 0x00000400;
   
   //Disable all DMA requests
   DMA_A.ERQRL.U32 = 0;

   //Disable all DMA error interrupts
   DMA_A.EEIRL.U32 = 0;

}
	
