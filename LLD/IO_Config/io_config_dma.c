
#include "io_config_dma.h"



//=============================================================================
// DMA_QADC_CFFF_4
//=============================================================================
DMA_Second_32Bit_T DMA_QADC_CFFF_4_Second_32Bit =

{
     false,                                                       //SMOD Source address modulo
     DMA_SIZE_32_BIT,                              //SSIZE Source data transfer size
     false,                                                      //DMOD Destination address modulo
     DMA_SIZE_32_BIT,                     //DSIZE Destination data transfer size
     sizeof(uint32_t)                                       //SOFF Source address signed offset
};

DMA_Third_32Bit_T DMA_QADC_CFFF_4_Third_32Bit =

{
     sizeof(uint32_t)                   //NBYTES  Inner ¡°minor¡± byte transfer count
};

DMA_Sixth_32Bit_T DMA_QADC_CFFF_4_Sixth_32Bit =
	
{

   false,     //CITER_E_LINK :  Enable channel-to-channel linking on minor loop complete
   false,     //CITER_LINKCH :  Current ¡°major¡± iteration count or Link channel number
   DMA_QADC_CFFF_4_SIZE,   //CITER        Current ¡°major¡± iteration count
   0           //DOFF         Destination address signed offset

};

DMA_Eighth_32Bit_T DMA_QADC_CFFF_4_Eighth_32Bit =

{

   false,               // Enable channel-to-channel linking on minor loop complete  BITER_E_LINK :  BIT_1;  // Bit       31
   0,                    // Beginning ¡°major¡± iteration count or Beginning Link channel number bitfield32_t   BITER_LINKCH :  BIT_6;  // Bits  [30:25]
   DMA_QADC_CFFF_4_SIZE,   //Beginning ¡°major¡± iteration count bitfield32_t   BITER        :  BIT_9;  // Bits  [24:16]
   DMA_BANDWIDTH_CONTROL_NO_ENGINE_STALL,   //Bandwidth control bitfield32_t   BWC          :  BIT_2;  // Bits  [15:14]
   0,                    //Link channel number bitfield32_t   MAJOR_LINKCH :  BIT_6;  // Bits  [13:08]
   false,               //Channel done bitfield32_t   DONE         :  BIT_1;  // Bit       07
   false,               //Channel active bitfield32_t   ACTIVE       :  BIT_1;  // Bit       06
   false,               //Enable channel-to-channel linking on major loop completebitfield32_t   MAJOR_E_LINK :  BIT_1;  // Bit       05
   false,               //Enable scatter/gather processing bitfield32_t   E_SG         :  BIT_1;  // Bit       04
   false,               // bitfield32_t   D_REQ        :  BIT_1;  // Bit       03
   false,               //Enable an interrupt when major counter is half completebitfield32_t   INT_HALF     :  BIT_1;  // Bit       02
   false,               //Enable an interrupt when major iteration count completesbitfield32_t   INT_MAJ      :  BIT_1;  // Bit       01
   false                //Channel start bitfield32_t   START        :  BIT_1;  // Bit       00

};

//=============================================================================
// DMA_QADC_RFDF_4
//=============================================================================
DMA_Second_32Bit_T DMA_QADC_RFDF_4_Second_32Bit =

{
     false,                                         //SMOD Source address modulo
     DMA_SIZE_16_BIT,                    //SSIZE Source data transfer size
     false,                                        //DMOD Destination address modulo
     DMA_SIZE_16_BIT,                   //DSIZE Destination data transfer size
     0                                              //SOFF Source address signed offset
};

DMA_Third_32Bit_T DMA_QADC_RFDF_4_Third_32Bit =

{
     sizeof(uint16_t)                   //NBYTES  Inner ¡°minor¡± byte transfer count
};

DMA_Sixth_32Bit_T DMA_QADC_RFDF_4_Sixth_32Bit =
	
{

   false,     //CITER_E_LINK :  Enable channel-to-channel linking on minor loop complete
   false,     //CITER_LINKCH :  Current ¡°major¡± iteration count or Link channel number
   DMA_QADC_RFDF_4_SIZE,   //CITER        Current ¡°major¡± iteration count
   sizeof(uint16_t)            //DOFF         Destination address signed offset

};


DMA_Eighth_32Bit_T DMA_QADC_RFDF_4_Eighth_32Bit =

{

   false,               // Enable channel-to-channel linking on minor loop complete  BITER_E_LINK :  BIT_1;  // Bit       31
   0,                    // Beginning ¡°major¡± iteration count or Beginning Link channel number bitfield32_t   BITER_LINKCH :  BIT_6;  // Bits  [30:25]
   DMA_QADC_RFDF_4_SIZE,   //Beginning ¡°major¡± iteration count bitfield32_t   BITER        :  BIT_9;  // Bits  [24:16]
   DMA_BANDWIDTH_CONTROL_NO_ENGINE_STALL,   //Bandwidth control bitfield32_t   BWC          :  BIT_2;  // Bits  [15:14]
   0,                    //Link channel number bitfield32_t   MAJOR_LINKCH :  BIT_6;  // Bits  [13:08]
   false,               //Channel done bitfield32_t   DONE         :  BIT_1;  // Bit       07
   false,               //Channel active bitfield32_t   ACTIVE       :  BIT_1;  // Bit       06
   false,               //Enable channel-to-channel linking on major loop completebitfield32_t   MAJOR_E_LINK :  BIT_1;  // Bit       05
   false,               //Enable scatter/gather processing bitfield32_t   E_SG         :  BIT_1;  // Bit       04
   false,               // bitfield32_t   D_REQ        :  BIT_1;  // Bit       03
   false,               //Enable an interrupt when major counter is half completebitfield32_t   INT_HALF     :  BIT_1;  // Bit       02
   false,               //Enable an interrupt when major iteration count completesbitfield32_t   INT_MAJ      :  BIT_1;  // Bit       01
   false                //Channel start bitfield32_t   START        :  BIT_1;  // Bit       00

};

//=============================================================================
// DMA_DSPIB_SR_TFFF
//=============================================================================
DMA_Second_32Bit_T DMA_DSPIB_SR_TFFF_Second_32Bit =

{
     false,                                                       //SMOD Source address modulo
     DMA_SIZE_32_BIT,                              //SSIZE Source data transfer size
     false,                                                      //DMOD Destination address modulo
     DMA_SIZE_32_BIT,                     //DSIZE Destination data transfer size
     sizeof(uint32_t)                                       //SOFF Source address signed offset
};

DMA_Third_32Bit_T DMA_DSPIB_SR_TFFF_Third_32Bit =

{
     sizeof(uint32_t)                   //NBYTES  Inner ¡°minor¡± byte transfer count
};

DMA_Sixth_32Bit_T DMA_DSPIB_SR_TFFF_Sixth_32Bit =
	
{

   false,     //CITER_E_LINK :  Enable channel-to-channel linking on minor loop complete
   false,     //CITER_LINKCH :  Current ¡°major¡± iteration count or Link channel number
   DMA_DSPIB_SR_TFFF_SIZE,   //CITER        Current ¡°major¡± iteration count
   0           //DOFF         Destination address signed offset

};

DMA_Eighth_32Bit_T DMA_DSPIB_SR_TFFF_Eighth_32Bit =

{

   false,               // Enable channel-to-channel linking on minor loop complete  BITER_E_LINK :  BIT_1;  // Bit       31
   0,                    // Beginning ¡°major¡± iteration count or Beginning Link channel number bitfield32_t   BITER_LINKCH :  BIT_6;  // Bits  [30:25]
   DMA_DSPIB_SR_TFFF_SIZE,   //Beginning ¡°major¡± iteration count bitfield32_t   BITER        :  BIT_9;  // Bits  [24:16]
   DMA_BANDWIDTH_CONTROL_NO_ENGINE_STALL,   //Bandwidth control bitfield32_t   BWC          :  BIT_2;  // Bits  [15:14]
   0,                    //Link channel number bitfield32_t   MAJOR_LINKCH :  BIT_6;  // Bits  [13:08]
   false,               //Channel done bitfield32_t   DONE         :  BIT_1;  // Bit       07
   false,               //Channel active bitfield32_t   ACTIVE       :  BIT_1;  // Bit       06
   false,               //Enable channel-to-channel linking on major loop completebitfield32_t   MAJOR_E_LINK :  BIT_1;  // Bit       05
   false,               //Enable scatter/gather processing bitfield32_t   E_SG         :  BIT_1;  // Bit       04
   true,               // bitfield32_t   D_REQ        :  BIT_1;  // Bit       03
   false,               //Enable an interrupt when major counter is half completebitfield32_t   INT_HALF     :  BIT_1;  // Bit       02
   false,               //Enable an interrupt when major iteration count completesbitfield32_t   INT_MAJ      :  BIT_1;  // Bit       01
   false                //Channel start bitfield32_t   START        :  BIT_1;  // Bit       00

};


//=============================================================================
// DMA_DSPIB_RFDF
//=============================================================================
DMA_Second_32Bit_T DMA_DSPIB_SR_RFDF_Second_32Bit =

{
     false,                                         //SMOD Source address modulo
     DMA_SIZE_16_BIT,                    //SSIZE Source data transfer size
     false,                                        //DMOD Destination address modulo
     DMA_SIZE_16_BIT,                   //DSIZE Destination data transfer size
     0                                              //SOFF Source address signed offset
};

DMA_Third_32Bit_T DMA_DSPIB_SR_RFDF_Third_32Bit =

{
     sizeof(uint16_t)                   //NBYTES  Inner ¡°minor¡± byte transfer count
};

DMA_Sixth_32Bit_T DMA_DSPIB_SR_RFDF_Sixth_32Bit =
	
{

   false,     //CITER_E_LINK :  Enable channel-to-channel linking on minor loop complete
   false,     //CITER_LINKCH :  Current ¡°major¡± iteration count or Link channel number
   DMA_DSPIB_SR_RFDF_SIZE,   //CITER        Current ¡°major¡± iteration count
   sizeof(uint16_t)            //DOFF         Destination address signed offset

};


DMA_Eighth_32Bit_T DMA_DSPIB_SR_RFDF_Eighth_32Bit =

{

   false,               // Enable channel-to-channel linking on minor loop complete  BITER_E_LINK :  BIT_1;  // Bit       31
   0,                    // Beginning ¡°major¡± iteration count or Beginning Link channel number bitfield32_t   BITER_LINKCH :  BIT_6;  // Bits  [30:25]
   DMA_DSPIB_SR_RFDF_SIZE,   //Beginning ¡°major¡± iteration count bitfield32_t   BITER        :  BIT_9;  // Bits  [24:16]
   DMA_BANDWIDTH_CONTROL_NO_ENGINE_STALL,   //Bandwidth control bitfield32_t   BWC          :  BIT_2;  // Bits  [15:14]
   0,                    //Link channel number bitfield32_t   MAJOR_LINKCH :  BIT_6;  // Bits  [13:08]
   false,               //Channel done bitfield32_t   DONE         :  BIT_1;  // Bit       07
   false,               //Channel active bitfield32_t   ACTIVE       :  BIT_1;  // Bit       06
   false,               //Enable channel-to-channel linking on major loop completebitfield32_t   MAJOR_E_LINK :  BIT_1;  // Bit       05
   false,               //Enable scatter/gather processing bitfield32_t   E_SG         :  BIT_1;  // Bit       04
   true,               // bitfield32_t   D_REQ        :  BIT_1;  // Bit       03
   false,               //Enable an interrupt when major counter is half completebitfield32_t   INT_HALF     :  BIT_1;  // Bit       02
   false,               //Enable an interrupt when major iteration count completesbitfield32_t   INT_MAJ      :  BIT_1;  // Bit       01
   false                //Channel start bitfield32_t   START        :  BIT_1;  // Bit       00

};


//=============================================================================
// Initialization Constant for DMA Channel Priority
//=============================================================================

