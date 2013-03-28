//===========================================================================
//     Preprocessor #include directive(s) for standard header files
//===========================================================================
#include "dd_intc.h"

#include "io_vector.h"

///////////////////////////////////////////////////////////////////////////////
// INTC_Vector_Table
///////////////////////////////////////////////////////////////////////////////
const INTC_Vector_Callback_T INTC_Vector_Table [ NO_OF_INTC_CHANNEL ] =
{
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                 INTC Software Settable Interrupt                  */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  #if INTC_CHANNEL_SOFTWARE_CH0 == UNUSED_IRQ
        (INTC_Vector_Callback_T)NULL,
  #else
        INTC_CHANNEL_SOFTWARE_CH0_HANDLER,
  #endif//channel 0

 #if INTC_CHANNEL_SOFTWARE_CH1 == UNUSED_IRQ
       (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SOFTWARE_CH1_HANDLER,
 #endif//channel 1

 #if INTC_CHANNEL_SOFTWARE_CH2 == UNUSED_IRQ
       (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SOFTWARE_CH2_HANDLER,
 #endif//channel 2

 #if INTC_CHANNEL_SOFTWARE_CH3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SOFTWARE_CH3_HANDLER,
 #endif//channel 3
 
 #if INTC_CHANNEL_SOFTWARE_CH4 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SOFTWARE_CH4_HANDLER,
 #endif//channel 4
 
 #if INTC_CHANNEL_SOFTWARE_CH5 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SOFTWARE_CH5_HANDLER,
 #endif//channel 5

  #if INTC_CHANNEL_SOFTWARE_CH6 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SOFTWARE_CH6_HANDLER,
 #endif//channel 6

  #if INTC_CHANNEL_SOFTWARE_CH7 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SOFTWARE_CH7_HANDLER,
 #endif//channel 7


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                           ECSM Interrupts                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  #if INTC_CHANNEL_SW_WATCHDOG_IR == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SW_WATCHDOG_IR_HANDLER,
 #endif//channel 8

   #if INTC_CHANNEL_ECSM_RAM_FLASH_ERROR == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_ECSM_RAM_FLASH_ERROR_HANDLER,
 #endif//channel 9

 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  EDMA Chan 0-31 Interrupts                        */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 #if INTC_CHANNEL_DMA_ERROR_CH31_0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_ERROR_CH31_0_HANDLER,
 #endif//channel 10

  #if INTC_CHANNEL_DMA_CH0_QADC_CFIFO_0_FILL== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH0_QADC_CFIFO_0_FILL_HANDLER,
 #endif//channel 11

  #if INTC_CHANNEL_DMA_CH1_QADC_RFIFO_0_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH1_QADC_RFIFO_0_DRAIN_HANDLER,
 #endif//channel 12

   #if INTC_CHANNEL_DMA_CH2_QADC_CFIFO_1_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH2_QADC_CFIFO_1_FILL_HANDLER,
 #endif//channel 13

  #if INTC_CHANNEL_DMA_CH3_QADC_RFIFO_1_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH3_QADC_RFIFO_1_DRAIN_HANDLER,
 #endif//channel 14

  #if INTC_CHANNEL_DMA_CH4_QADC_CFIFO_2_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH4_QADC_CFIFO_2_FILL_HANDLER,
 #endif//channel 15

  #if INTC_CHANNEL_DMA_CH5_QADC_RFIFO_2_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH5_QADC_RFIFO_2_DRAIN_HANDLER,
 #endif//channel 16

   #if INTC_CHANNEL_DMA_CH6_QADC_CFIFO_3_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH6_QADC_CFIFO_3_FILL_HANDLER,
 #endif//channel 17

 #if INTC_CHANNEL_DMA_CH7_QADC_RFIFO_3_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH7_QADC_RFIFO_3_DRAIN_HANDLER,
 #endif//channel 18


  #if INTC_CHANNEL_DMA_CH8_QADC_CFIFO_4_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH8_QADC_CFIFO_4_FILL_HANDLER,
 #endif//channel 19

   #if INTC_CHANNEL_DMA_CH9_QADC_RFIFO_4_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH9_QADC_RFIFO_4_DRAIN_HANDLER,
 #endif//channel 20

 #if INTC_CHANNEL_DMA_CH10_QADC_CFIFO_5_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH10_QADC_CFIFO_5_FILL_HANDLER,
 #endif//channel 21

  #if INTC_CHANNEL_DMA_CH11_QADC_RFIFO_5_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH11_QADC_RFIFO_5_DRAIN_HANDLER,
 #endif//channel 22

  #if INTC_CHANNEL_DMA_CH12_DSPI_B_TX_FIFO_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH12_DSPI_B_TX_FIFO_FILL_HANDLER,
 #endif//channel 23

  #if INTC_CHANNEL_DMA_CH13_DSPI_B_RX_FIFO_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH13_DSPI_B_RX_FIFO_DRAIN_HANDLER,
 #endif//channel 24

   #if INTC_CHANNEL_DMA_CH14_DSPI_C_TX_FIFO_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH14_DSPI_C_TX_FIFO_FILL_HANDLER,
 #endif//channel 25

    #if INTC_CHANNEL_DMA_CH15_DSPI_C_RX_FIFO_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH15_DSPI_C_RX_FIFO_DRAIN_HANDLER,
 #endif//channel 26

  #if INTC_CHANNEL_DMA_CH16_DEC_FILTER_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH16_DEC_FILTER_FILL_HANDLER,
 #endif//channel 27

   #if INTC_CHANNEL_DMA_CH17_DEC_FILTER_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH17_DEC_FILTER_DRAIN_HANDLER,
 #endif//channel 28

  #if INTC_CHANNEL_DMA_CH18_SCI_A_TX == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH18_SCI_A_TX_HANDLER,
 #endif//channel 29

  #if INTC_CHANNEL_DMA_CH19_SCI_A_RX == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH19_SCI_A_RX_HANDLER,
 #endif//channel 30

  #if INTC_CHANNEL_DMA_CH20_MIOS_CH0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH20_MIOS_CH0_HANDLER,
 #endif//channel 31

   #if INTC_CHANNEL_DMA_CH21_MIOS_CH1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH21_MIOS_CH1_HANDLER,
 #endif//channel 32

  #if INTC_CHANNEL_DMA_CH22_MIOS_CH2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH22_MIOS_CH2_HANDLER,
 #endif//channel 33

  #if INTC_CHANNEL_DMA_CH23_MIOS_CH3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH23_MIOS_CH3_HANDLER,
 #endif//channel 34

 #if INTC_CHANNEL_DMA_CH24_MIOS_CH4 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH24_MIOS_CH4_HANDLER,
 #endif//channel 35

  #if INTC_CHANNEL_DMA_CH25_MIOS_CH8 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH25_MIOS_CH8_HANDLER,
 #endif//channel 36

 #if INTC_CHANNEL_DMA_CH26_MIOS_CH9 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH26_MIOS_CH9_HANDLER,
 #endif//channel 37

  #if INTC_CHANNEL_DMA_CH27_TPU_A_CH0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH27_TPU_A_CH0_HANDLER,
 #endif//channel 38

  #if INTC_CHANNEL_DMA_CH28_TPU_A_CH1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH28_TPU_A_CH1_HANDLER,
 #endif//channel 39

   #if INTC_CHANNEL_DMA_CH29_TPU_A_CH2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH29_TPU_A_CH2_HANDLER,
 #endif//channel 40

 #if INTC_CHANNEL_DMA_CH30_TPU_A_CH14 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH30_TPU_A_CH14_HANDLER,
 #endif//channel 41


  #if INTC_CHANNEL_DMA_CH31_TPU_A_CH15 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_DMA_CH31_TPU_A_CH15_HANDLER,
 #endif//channel 42


 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                          FMPLL Interrupts                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  #if INTC_CHANNEL_FMPLL_LOSS_CLOCK == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_FMPLL_LOSS_CLOCK_HANDLER,
 #endif//channel 43
 
  #if INTC_CHANNEL_FMPLL_LOSS_LOCK == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_FMPLL_LOSS_LOCK_HANDLER,
 #endif//channel 44
 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                          SIU Interrupts                           */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  #if INTC_CHANNEL_SIU_OVERRUN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SIU_OVERRUN_HANDLER,
 #endif//channel 45

   #if INTC_CHANNEL_SIU_EXTERNAL_CH0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SIU_EXTERNAL_CH0_HANDLER,
 #endif//channel 46

  #if INTC_CHANNEL_SIU_EXTERNAL_CH1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SIU_EXTERNAL_CH1_HANDLER,
 #endif//channel 47
 
  #if INTC_CHANNEL_SIU_EXTERNAL_CH2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SIU_EXTERNAL_CH2_HANDLER,
 #endif//channel 48

   #if INTC_CHANNEL_SIU_EXTERNAL_CH3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SIU_EXTERNAL_CH3_HANDLER,
 #endif//channel 49

 #if INTC_CHANNEL_SIU_EXTERNAL_CH15_4 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_SIU_EXTERNAL_CH15_4_HANDLER,
 #endif//channel 50
 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                   EMIOS Chan 0-15 Interrupts                      */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 #if INTC_CHANNEL_MIOS_CH0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_MIOS_CH0_HANDLER,
 #endif//channel 51

  #if INTC_CHANNEL_MIOS_CH1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_MIOS_CH1_HANDLER,
 #endif//channel 52
 

  #if INTC_CHANNEL_MIOS_CH2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_MIOS_CH2_HANDLER,
 #endif//channel 53

  #if INTC_CHANNEL_MIOS_CH3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_MIOS_CH3_HANDLER,
 #endif//channel 54
 
  #if INTC_CHANNEL_MIOS_CH4 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
      INTC_CHANNEL_MIOS_CH4_HANDLER,
 #endif//channel 55

   #if INTC_CHANNEL_MIOS_CH5 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
     INTC_CHANNEL_MIOS_CH5_HANDLER,
 #endif//channel 56

 
   #if INTC_CHANNEL_MIOS_CH6 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
     INTC_CHANNEL_MIOS_CH6_HANDLER,
 #endif//channel 57

  #if INTC_CHANNEL_MIOS_CH7 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
     INTC_CHANNEL_MIOS_CH7_HANDLER,
 #endif//channel 58

 #if INTC_CHANNEL_MIOS_CH8 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
     INTC_CHANNEL_MIOS_CH8_HANDLER,
 #endif//channel 59

   #if INTC_CHANNEL_MIOS_CH9 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
     INTC_CHANNEL_MIOS_CH9_HANDLER,
 #endif//channel 60

  #if INTC_CHANNEL_MIOS_CH10 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
     INTC_CHANNEL_MIOS_CH10_HANDLER,
 #endif//channel 61

   #if INTC_CHANNEL_MIOS_CH11 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_MIOS_CH11_HANDLER,
 #endif//channel 62

 
   #if INTC_CHANNEL_MIOS_CH12 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_MIOS_CH12_HANDLER,
 #endif//channel 63

   #if INTC_CHANNEL_MIOS_CH13 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_MIOS_CH13_HANDLER,
 #endif//channel 64

  #if INTC_CHANNEL_MIOS_CH14 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_MIOS_CH14_HANDLER,
 #endif//channel 65

 #if INTC_CHANNEL_MIOS_CH15 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_MIOS_CH15_HANDLER,
 #endif//channel 66
  
  
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                         ETPU  Interrupts                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  #if INTC_CHANNEL_TPU_GLOBAL_EXCEPTION == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_GLOBAL_EXCEPTION_HANDLER,
 #endif//channel 67

  #if INTC_CHANNEL_TPU_A_CH0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH0_HANDLER,
 #endif//channel 68

  #if INTC_CHANNEL_TPU_A_CH1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH1_HANDLER,
 #endif//channel 69

   #if INTC_CHANNEL_TPU_A_CH2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH2_HANDLER,
 #endif//channel 70

  #if INTC_CHANNEL_TPU_A_CH3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH3_HANDLER,
 #endif//channel 71

  #if INTC_CHANNEL_TPU_A_CH4 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH4_HANDLER,
 #endif//channel 72
 
 #if INTC_CHANNEL_TPU_A_CH5 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH5_HANDLER,
 #endif//channel 73

  #if INTC_CHANNEL_TPU_A_CH6 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH6_HANDLER,
 #endif//channel 74
 
  #if INTC_CHANNEL_TPU_A_CH7 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH7_HANDLER,
 #endif//channel 75

   #if INTC_CHANNEL_TPU_A_CH8 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH8_HANDLER,
 #endif//channel 76
 
   #if INTC_CHANNEL_TPU_A_CH9 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH9_HANDLER,
 #endif//channel 77

  #if INTC_CHANNEL_TPU_A_CH10 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH10_HANDLER,
 #endif//channel 78

 #if INTC_CHANNEL_TPU_A_CH11 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH11_HANDLER,
 #endif//channel 79

 #if INTC_CHANNEL_TPU_A_CH12 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH12_HANDLER,
 #endif//channel 80

 #if INTC_CHANNEL_TPU_A_CH13 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH13_HANDLER,
 #endif//channel 81

  #if INTC_CHANNEL_TPU_A_CH14 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH14_HANDLER,
 #endif//channel 82

   #if INTC_CHANNEL_TPU_A_CH15 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH15_HANDLER,
 #endif//channel 83

 #if INTC_CHANNEL_TPU_A_CH16 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH16_HANDLER,
 #endif//channel 84

 #if INTC_CHANNEL_TPU_A_CH17 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH17_HANDLER,
 #endif//channel 85

  #if INTC_CHANNEL_TPU_A_CH18 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
   INTC_CHANNEL_TPU_A_CH18_HANDLER,
 #endif//channel 86
 
  #if INTC_CHANNEL_TPU_A_CH19 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
   INTC_CHANNEL_TPU_A_CH19_HANDLER,
 #endif//channel 87

  #if INTC_CHANNEL_TPU_A_CH20 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
   INTC_CHANNEL_TPU_A_CH20_HANDLER,
 #endif//channel 88

   #if INTC_CHANNEL_TPU_A_CH21 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
   INTC_CHANNEL_TPU_A_CH21_HANDLER,
 #endif//channel 89


  #if INTC_CHANNEL_TPU_A_CH22 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH22_HANDLER,
 #endif//channel 90

   #if INTC_CHANNEL_TPU_A_CH23 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH23_HANDLER,
 #endif//channel 91

 #if INTC_CHANNEL_TPU_A_CH24 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH24_HANDLER,
 #endif//channel 92

  #if INTC_CHANNEL_TPU_A_CH25 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH25_HANDLER,
 #endif//channel 93

  #if INTC_CHANNEL_TPU_A_CH26 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH26_HANDLER,
 #endif//channel 94

  #if INTC_CHANNEL_TPU_A_CH27 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH27_HANDLER,
 #endif//channel 95

  #if INTC_CHANNEL_TPU_A_CH28 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH28_HANDLER,
 #endif//channel 96

  #if INTC_CHANNEL_TPU_A_CH29 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH29_HANDLER,
 #endif//channel 97

  #if INTC_CHANNEL_TPU_A_CH30 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH30_HANDLER,
 #endif//channel 98

   #if INTC_CHANNEL_TPU_A_CH31 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_TPU_A_CH31_HANDLER,
 #endif//channel 99


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                         EQADC Interrupts                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 #if INTC_CHANNEL_QADC_OVERFLOW == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_OVERFLOW_HANDLER,
 #endif//channel 100
 
 #if INTC_CHANNEL_QADC_CFIFO_CH0_INCOHERENT == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH0_INCOHERENT_HANDLER,
 #endif//channel 101
  
 #if INTC_CHANNEL_QADC_CFIFO_CH0_PAUSE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH0_PAUSE_HANDLER,
 #endif//channel 102
   
 #if INTC_CHANNEL_QADC_CFIFO_CH0_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH0_EOQ_HANDLER,
 #endif//channel 103

  #if INTC_CHANNEL_QADC_CFIFO_CH0_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH0_FILL_HANDLER,
 #endif//channel 104
 
  #if INTC_CHANNEL_QADC_RFIFO_CH0_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_RFIFO_CH0_DRAIN_HANDLER,
 #endif//channel 105
 
 #if INTC_CHANNEL_QADC_CFIFO_CH1_INCOHERENT == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH1_INCOHERENT_HANDLER,
 #endif//channel 106
  
 #if INTC_CHANNEL_QADC_CFIFO_CH1_PAUSE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH1_PAUSE_HANDLER,
 #endif//channel 107
   
 #if INTC_CHANNEL_QADC_CFIFO_CH1_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH1_EOQ_HANDLER,
 #endif//channel 108

  #if INTC_CHANNEL_QADC_CFIFO_CH1_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH1_FILL_HANDLER,
 #endif//channel 109
 
  #if INTC_CHANNEL_QADC_RFIFO_CH1_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_RFIFO_CH1_DRAIN_HANDLER,
 #endif//channel 110
 
 #if INTC_CHANNEL_QADC_CFIFO_CH2_INCOHERENT == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH2_INCOHERENT_HANDLER,
 #endif//channel 111
  
 #if INTC_CHANNEL_QADC_CFIFO_CH2_PAUSE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH2_PAUSE_HANDLER,
 #endif//channel 112
   
 #if INTC_CHANNEL_QADC_CFIFO_CH2_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH2_EOQ_HANDLER,
 #endif//channel 113

  #if INTC_CHANNEL_QADC_CFIFO_CH2_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH2_FILL_HANDLER,
 #endif//channel 114
 
  #if INTC_CHANNEL_QADC_RFIFO_CH2_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_RFIFO_CH2_DRAIN_HANDLER,
 #endif//channel 115

 
 #if INTC_CHANNEL_QADC_CFIFO_CH3_INCOHERENT == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH3_INCOHERENT_HANDLER,
 #endif//channel 116
  
 #if INTC_CHANNEL_QADC_CFIFO_CH3_PAUSE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH3_PAUSE_HANDLER,
 #endif//channel 117
   
 #if INTC_CHANNEL_QADC_CFIFO_CH3_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH3_EOQ_HANDLER,
 #endif//channel 118

  #if INTC_CHANNEL_QADC_CFIFO_CH3_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH3_FILL_HANDLER,
 #endif//channel 119
 
  #if INTC_CHANNEL_QADC_RFIFO_CH3_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_RFIFO_CH3_DRAIN_HANDLER,
 #endif//channel 120

 
 #if INTC_CHANNEL_QADC_CFIFO_CH4_INCOHERENT == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH4_INCOHERENT_HANDLER,
 #endif//channel 121
  
 #if INTC_CHANNEL_QADC_CFIFO_CH4_PAUSE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH4_PAUSE_HANDLER,
 #endif//channel 122
   
 #if INTC_CHANNEL_QADC_CFIFO_CH4_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH4_EOQ_HANDLER,
 #endif//channel 123

  #if INTC_CHANNEL_QADC_CFIFO_CH4_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH4_FILL_HANDLER,
 #endif//channel 124
 
  #if INTC_CHANNEL_QADC_RFIFO_CH4_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_RFIFO_CH4_DRAIN_HANDLER,
 #endif//channel 125

  
 #if INTC_CHANNEL_QADC_CFIFO_CH5_INCOHERENT == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH5_INCOHERENT_HANDLER,
 #endif//channel 126
  
 #if INTC_CHANNEL_QADC_CFIFO_CH5_PAUSE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH5_PAUSE_HANDLER,
 #endif//channel 127
   
 #if INTC_CHANNEL_QADC_CFIFO_CH5_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH5_EOQ_HANDLER,
 #endif//channel 128

  #if INTC_CHANNEL_QADC_CFIFO_CH5_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_CFIFO_CH5_FILL_HANDLER,
 #endif//channel 129
 
  #if INTC_CHANNEL_QADC_RFIFO_CH5_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_QADC_RFIFO_CH5_DRAIN_HANDLER,
 #endif//channel 130

 
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        DSPI B Interrupts                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
  #if INTC_CHANNEL_DSPI_B_OVERFLOW == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_B_OVERFLOW_HANDLER,
 #endif//channel 131

  
  #if INTC_CHANNEL_DSPI_B_TFIFO_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_B_TFIFO_EOQ_HANDLER,
 #endif//channel 132

  
  #if INTC_CHANNEL_DSPI_B_TFIFO_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
   INTC_CHANNEL_DSPI_B_TFIFO_FILL_HANDLER,
 #endif//channel 133

  
  #if INTC_CHANNEL_DSPI_B_TX_COMPLETE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_B_TX_COMPLETE_HANDLER,
 #endif//channel 134

  
  #if INTC_CHANNEL_DSPI_B_RFIFO_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_B_RFIFO_DRAIN_HANDLER,
 #endif//channel 135
 
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        DSPI C Interrupts                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
  #if INTC_CHANNEL_DSPI_C_OVERFLOW == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_C_OVERFLOW_HANDLER,
 #endif//channel 136

  
  #if INTC_CHANNEL_DSPI_C_TFIFO_EOQ == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_C_TFIFO_EOQ_HANDLER,
 #endif//channel 137

  
  #if INTC_CHANNEL_DSPI_C_TFIFO_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
   INTC_CHANNEL_DSPI_C_TFIFO_FILL_HANDLER,
 #endif//channel 138

  
  #if INTC_CHANNEL_DSPI_C_TX_COMPLETE == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_C_TX_COMPLETE_HANDLER,
 #endif//channel 139

  
  #if INTC_CHANNEL_DSPI_C_RFIFO_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DSPI_C_RFIFO_DRAIN_HANDLER,
 #endif//channel 140
 
 
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                       Reserved Interrupts (DSPI C)                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  #if INTC_CHANNEL_RESERVED_141 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_141_HANDLER,
 #endif//channel 141

 
  #if INTC_CHANNEL_RESERVED_142 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_142_HANDLER,
 #endif//channel 142

 
  #if INTC_CHANNEL_RESERVED_143 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_143_HANDLER,
 #endif//channel 143

 
  #if INTC_CHANNEL_RESERVED_144 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_144_HANDLER,
 #endif//channel 144

 
  #if INTC_CHANNEL_RESERVED_145 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_145_HANDLER,
 #endif//channel 145
 
   
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        ESCI A Interrupts                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    
  #if INTC_CHANNEL_SCI_A == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_SCI_A_HANDLER,
 #endif//channel 146

 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        Reserved                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
  #if INTC_CHANNEL_RESERVED_147 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_147_HANDLER,
 #endif//channel 147

  
  #if INTC_CHANNEL_RESERVED_147 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_147_HANDLER,
 #endif//channel 148


 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        ESCI B Interrupts                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
     
  #if INTC_CHANNEL_SCI_B == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_SCI_B_HANDLER,
 #endif//channel 149
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        Reserved                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
  #if INTC_CHANNEL_RESERVED_150 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_150_HANDLER,
 #endif//channel 150

  
  #if INTC_CHANNEL_RESERVED_151 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_151_HANDLER,
 #endif//channel 151

 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                      FlexCan A Interrupts                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   
  #if INTC_CHANNEL_FLEXCAN_A_BUS_OFF == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUS_OFF_HANDLER,
 #endif//channel 152

   
  #if INTC_CHANNEL_FLEXCAN_A_ERROR == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_ERROR_HANDLER,
 #endif//channel 153

    
  #if INTC_CHANNEL_FLEXCAN_A_WAKEUP == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_WAKEUP_HANDLER,
 #endif//channel 154

     
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_0_HANDLER,
 #endif//channel 155

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_1_HANDLER,
 #endif//channel 156

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_2_HANDLER,
 #endif//channel 157

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_3_HANDLER,
 #endif//channel 158

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_4 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_4_HANDLER,
 #endif//channel 159
      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_5 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_5_HANDLER,
 #endif//channel 160

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_6 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_6_HANDLER,
 #endif//channel 161

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_7 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_7_HANDLER,
 #endif//channel 162

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_8 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_8_HANDLER,
 #endif//channel 163

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_9 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_9_HANDLER,
 #endif//channel 164

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_10 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_10_HANDLER,
 #endif//channel 165

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_11 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_11_HANDLER,
 #endif//channel 166

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_12 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_12_HANDLER,
 #endif//channel 167

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_13 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_13_HANDLER,
 #endif//channel 168

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_14 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_14_HANDLER,
 #endif//channel 169

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_15 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_15_HANDLER,
 #endif//channel 170

      
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_31_16 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_31_16_HANDLER,
 #endif//channel 171

       
  #if INTC_CHANNEL_FLEXCAN_A_BUFFER_63_32 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_A_BUFFER_63_32_HANDLER,
 #endif//channel 172
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                      FlexCan A Interrupts                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   
  #if INTC_CHANNEL_FLEXCAN_C_BUS_OFF == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUS_OFF_HANDLER,
 #endif//channel 173

   
  #if INTC_CHANNEL_FLEXCAN_C_ERROR == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_ERROR_HANDLER,
 #endif//channel 174

    
  #if INTC_CHANNEL_FLEXCAN_C_WAKEUP == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_WAKEUP_HANDLER,
 #endif//channel 175

     
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_0_HANDLER,
 #endif//channel 176

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_1_HANDLER,
 #endif//channel 177

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_2_HANDLER,
 #endif//channel 178

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_3_HANDLER,
 #endif//channel 179

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_4 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_4_HANDLER,
 #endif//channel 180

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_5 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_5_HANDLER,
 #endif//channel 181

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_6 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_6_HANDLER,
 #endif//channel 182

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_7 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_7_HANDLER,
 #endif//channel 183

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_8 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_8_HANDLER,
 #endif//channel 184

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_9 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_9_HANDLER,
 #endif//channel 185

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_10 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_10_HANDLER,
 #endif//channel 186

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_11 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_11_HANDLER,
 #endif//channel 187

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_12 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_12_HANDLER,
 #endif//channel 188

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_13 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_13_HANDLER,
 #endif//channel 189

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_14 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_14_HANDLER,
 #endif//channel 190

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_15 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_15_HANDLER,
 #endif//channel 191

      
  #if INTC_CHANNEL_FLEXCAN_C_BUFFER_31_16 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_FLEXCAN_C_BUFFER_31_16_HANDLER,
 #endif//channel 192

     
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        Reserved                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
  #if INTC_CHANNEL_RESERVED_193 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_193_HANDLER,
 #endif//channel 193

  
  #if INTC_CHANNEL_RESERVED_194 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_194_HANDLER,
 #endif//channel 194

   #if INTC_CHANNEL_RESERVED_195== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_195_HANDLER,
 #endif//channel 195

  
  #if INTC_CHANNEL_RESERVED_196 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_196_HANDLER,
 #endif//channel 196


  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        DEC Filter A   INT                                */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

   
  #if INTC_CHANNEL_DEC_FILTER_A_INPUT_FILL == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DEC_FILTER_A_INPUT_FILL_HANDLER,
 #endif//channel 197

   
  #if INTC_CHANNEL_DEC_FILTER_A_OUTPUT_DRAIN == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DEC_FILTER_A_OUTPUT_DRAIN_HANDLER,
 #endif//channel 198

   
  #if INTC_CHANNEL_DEC_FILTER_A_ERROR == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_DEC_FILTER_A_ERROR_HANDLER,
 #endif//channel 199
 
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        SYS Timer   INT                                */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

   
  #if INTC_CHANNEL_SYSTEM_TIMER_MODULE_0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_SYSTEM_TIMER_MODULE_0_HANDLER,
 #endif//channel 200

    
  #if INTC_CHANNEL_SYSTEM_TIMER_MODULE_1_3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
   INTC_CHANNEL_SYSTEM_TIMER_MODULE_1_3_HANDLER,
 #endif//channel 201

  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        Reserved                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
  #if INTC_CHANNEL_RESERVED_202 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_202_HANDLER,
 #endif//channel 202

  
  #if INTC_CHANNEL_RESERVED_203== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_203_HANDLER,
 #endif//channel 203

   #if INTC_CHANNEL_RESERVED_204== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_204_HANDLER,
 #endif//channel 204

  
  #if INTC_CHANNEL_RESERVED_205 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_205_HANDLER,
 #endif//channel 205

   
  #if INTC_CHANNEL_RESERVED_206 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_206_HANDLER,
 #endif//channel 206

   
  #if INTC_CHANNEL_RESERVED_207 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_207_HANDLER,
 #endif//channel 207

   
  #if INTC_CHANNEL_RESERVED_208 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_208_HANDLER,
 #endif//channel 208


  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        MIOS 23 INT                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   
  #if INTC_CHANNEL_MIOS_CH23 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_MIOS_CH23_HANDLER,
 #endif//channel 209
   
  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        Reserved                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

   #if INTC_CHANNEL_RESERVED_210 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_210_HANDLER,
 #endif//channel 210

  
  #if INTC_CHANNEL_RESERVED_211== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_211_HANDLER,
 #endif//channel 211

   #if INTC_CHANNEL_RESERVED_212== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_212_HANDLER,
 #endif//channel 212

  
  #if INTC_CHANNEL_RESERVED_213 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_213_HANDLER,
 #endif//channel 213

   
  #if INTC_CHANNEL_RESERVED_214== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_214_HANDLER,
 #endif//channel 214

   
  #if INTC_CHANNEL_RESERVED_215 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_215_HANDLER,
 #endif//channel 215

   
  #if INTC_CHANNEL_RESERVED_216 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_216_HANDLER,
 #endif//channel 216

    
  #if INTC_CHANNEL_RESERVED_217 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_217_HANDLER,
 #endif//channel 217

    
  #if INTC_CHANNEL_RESERVED_218 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_218_HANDLER,
 #endif//channel 218


    
  #if INTC_CHANNEL_RESERVED_219 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_219_HANDLER,
 #endif//channel 219

    
  #if INTC_CHANNEL_RESERVED_220 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_220_HANDLER,
 #endif//channel 220

    
  #if INTC_CHANNEL_RESERVED_221 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_221_HANDLER,
 #endif//channel 221

    
  #if INTC_CHANNEL_RESERVED_222 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_222_HANDLER,
 #endif//channel 222

    
  #if INTC_CHANNEL_RESERVED_223 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_223_HANDLER,
 #endif//channel 223

    
  #if INTC_CHANNEL_RESERVED_224 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_224_HANDLER,
 #endif//channel 224

    
  #if INTC_CHANNEL_RESERVED_225 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_225_HANDLER,
 #endif//channel 225

    
  #if INTC_CHANNEL_RESERVED_226 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_226_HANDLER,
 #endif//channel 226

    
  #if INTC_CHANNEL_RESERVED_227 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_227_HANDLER,
 #endif//channel 227

    
  #if INTC_CHANNEL_RESERVED_228 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_228_HANDLER,
 #endif//channel 228

    
  #if INTC_CHANNEL_RESERVED_229 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_229_HANDLER,
 #endif//channel 229

    
  #if INTC_CHANNEL_RESERVED_230 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_230_HANDLER,
 #endif//channel 230

    
  #if INTC_CHANNEL_RESERVED_231 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_231_HANDLER,
 #endif//channel 231

    
  #if INTC_CHANNEL_RESERVED_232 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_232_HANDLER,
 #endif//channel 232

    
  #if INTC_CHANNEL_RESERVED_233 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_233_HANDLER,
 #endif//channel 233

    
  #if INTC_CHANNEL_RESERVED_234 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_234_HANDLER,
 #endif//channel 234

    
  #if INTC_CHANNEL_RESERVED_235 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_235_HANDLER,
 #endif//channel 235

    
  #if INTC_CHANNEL_RESERVED_236 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_236_HANDLER,
 #endif//channel 236

    
  #if INTC_CHANNEL_RESERVED_237 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_237_HANDLER,
 #endif//channel 237

    
  #if INTC_CHANNEL_RESERVED_238 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_238_HANDLER,
 #endif//channel 238

    
  #if INTC_CHANNEL_RESERVED_239== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_239_HANDLER,
 #endif//channel 239

    
  #if INTC_CHANNEL_RESERVED_240 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_240_HANDLER,
 #endif//channel 240

    
  #if INTC_CHANNEL_RESERVED_241 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_241_HANDLER,
 #endif//channel 241

    
  #if INTC_CHANNEL_RESERVED_242 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_242_HANDLER,
 #endif//channel 242

    
  #if INTC_CHANNEL_RESERVED_243 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_243_HANDLER,
 #endif//channel 243

    
  #if INTC_CHANNEL_RESERVED_244 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_244_HANDLER,
 #endif//channel 244

    
  #if INTC_CHANNEL_RESERVED_245 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_245_HANDLER,
 #endif//channel 245

    
  #if INTC_CHANNEL_RESERVED_246 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_246_HANDLER,
 #endif//channel 246

    
  #if INTC_CHANNEL_RESERVED_247 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_247_HANDLER,
 #endif//channel 247

    
  #if INTC_CHANNEL_RESERVED_248 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_248_HANDLER,
 #endif//channel 248

    
  #if INTC_CHANNEL_RESERVED_249 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_249_HANDLER,
 #endif//channel 249
    
  #if INTC_CHANNEL_RESERVED_250 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_250_HANDLER,
 #endif//channel 250

    
  #if INTC_CHANNEL_RESERVED_251 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_251_HANDLER,
 #endif//channel 251

    
  #if INTC_CHANNEL_RESERVED_252 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_252_HANDLER,
 #endif//channel 252

    
  #if INTC_CHANNEL_RESERVED_253 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_253_HANDLER,
 #endif//channel 253

    
  #if INTC_CHANNEL_RESERVED_254 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_254_HANDLER,
 #endif//channel 254

    
  #if INTC_CHANNEL_RESERVED_255 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_255_HANDLER,
 #endif//channel 255

    
  #if INTC_CHANNEL_RESERVED_256 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_256_HANDLER,
 #endif//channel 256
    
  #if INTC_CHANNEL_RESERVED_257 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_257_HANDLER,
 #endif//channel 257
    
  #if INTC_CHANNEL_RESERVED_258 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_258_HANDLER,
 #endif//channel 258
    
  #if INTC_CHANNEL_RESERVED_259== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_259_HANDLER,
 #endif//channel 259
    
  #if INTC_CHANNEL_RESERVED_260 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_260_HANDLER,
 #endif//channel 260
    
  #if INTC_CHANNEL_RESERVED_261 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_261_HANDLER,
 #endif//channel 261
    
  #if INTC_CHANNEL_RESERVED_262 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_262_HANDLER,
 #endif//channel 262
    
  #if INTC_CHANNEL_RESERVED_263 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_263_HANDLER,
 #endif//channel 263
    
  #if INTC_CHANNEL_RESERVED_264 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_264_HANDLER,
 #endif//channel 264
    
  #if INTC_CHANNEL_RESERVED_265 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_265_HANDLER,
 #endif//channel 265
    
  #if INTC_CHANNEL_RESERVED_266 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_266_HANDLER,
 #endif//channel 266
    
  #if INTC_CHANNEL_RESERVED_267 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_267_HANDLER,
 #endif//channel 267
    
  #if INTC_CHANNEL_RESERVED_268 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_268_HANDLER,
 #endif//channel 268
    
  #if INTC_CHANNEL_RESERVED_269 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_269_HANDLER,
 #endif//channel 269
    
  #if INTC_CHANNEL_RESERVED_270== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_270_HANDLER,
 #endif//channel 270
    
  #if INTC_CHANNEL_RESERVED_271 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_271_HANDLER,
 #endif//channel 271
    
  #if INTC_CHANNEL_RESERVED_272 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_272_HANDLER,
 #endif//channel 272
    
  #if INTC_CHANNEL_RESERVED_273 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_273_HANDLER,
 #endif//channel 272
    
  #if INTC_CHANNEL_RESERVED_274 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_274_HANDLER,
 #endif//channel 273
    
  #if INTC_CHANNEL_RESERVED_275 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_275_HANDLER,
 #endif//channel 274
    
  #if INTC_CHANNEL_RESERVED_276 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_276_HANDLER,
 #endif//channel 275
    
  #if INTC_CHANNEL_RESERVED_277 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_277_HANDLER,
 #endif//channel 276
    
  #if INTC_CHANNEL_RESERVED_278 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_278_HANDLER,
 #endif//channel 278
    
  #if INTC_CHANNEL_RESERVED_279 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_279_HANDLER,
 #endif//channel 279
    
  #if INTC_CHANNEL_RESERVED_280 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_280_HANDLER,
 #endif//channel 280
    
  #if INTC_CHANNEL_RESERVED_281 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_281_HANDLER,
 #endif//channel 281
    
  #if INTC_CHANNEL_RESERVED_282 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_282_HANDLER,
 #endif//channel 282
    
  #if INTC_CHANNEL_RESERVED_283 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_283_HANDLER,
 #endif//channel 283
    
  #if INTC_CHANNEL_RESERVED_284 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_284_HANDLER,
 #endif//channel 284
    
  #if INTC_CHANNEL_RESERVED_285 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_285_HANDLER,
 #endif//channel 285
    
  #if INTC_CHANNEL_RESERVED_286 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_286_HANDLER,
 #endif//channel 286
    
  #if INTC_CHANNEL_RESERVED_287 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_287_HANDLER,
 #endif//channel 287
    
  #if INTC_CHANNEL_RESERVED_288 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_288_HANDLER,
 #endif//channel 288
    
  #if INTC_CHANNEL_RESERVED_289 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_289_HANDLER,
 #endif//channel 289
    
  #if INTC_CHANNEL_RESERVED_290 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_290_HANDLER,
 #endif//channel 290
    
  #if INTC_CHANNEL_RESERVED_291 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_291_HANDLER,
 #endif//channel 291
    
  #if INTC_CHANNEL_RESERVED_292 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_292_HANDLER,
 #endif//channel 292
    
  #if INTC_CHANNEL_RESERVED_293== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_293_HANDLER,
 #endif  //channel 293
 
  #if INTC_CHANNEL_RESERVED_294 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_294_HANDLER,
 #endif//channel 294
    
  #if INTC_CHANNEL_RESERVED_295 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_295_HANDLER,
 #endif//channel 295
    
  #if INTC_CHANNEL_RESERVED_296 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_296_HANDLER,
 #endif   //channel 296
 
  #if INTC_CHANNEL_RESERVED_297 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_297_HANDLER,
 #endif//channel 297
    
  #if INTC_CHANNEL_RESERVED_298 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_298_HANDLER,
 #endif//channel 298

    
  #if INTC_CHANNEL_RESERVED_299 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_299_HANDLER,
 #endif//channel 299

    
  #if INTC_CHANNEL_RESERVED_300 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_300_HANDLER,
 #endif//channel 300
 
 
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        PIT INT                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

   #if INTC_CHANNEL_PIT_0 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_PIT_0_HANDLER,
 #endif//channel 301


   #if INTC_CHANNEL_PIT_1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_PIT_1_HANDLER,
 #endif//channel 302

 
   #if INTC_CHANNEL_PIT_2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_PIT_2_HANDLER,
 #endif//channel 303

 
   #if INTC_CHANNEL_PIT_3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_PIT_3_HANDLER,
 #endif//channel 304

 
   #if INTC_CHANNEL_RTI == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RTI_HANDLER,
 #endif//channel 305
  
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        PMC/ECC INT                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

 
   #if INTC_CHANNEL_PMC == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_PMC_HANDLER,
 #endif//channel 306

  
   #if INTC_CHANNEL_ECC_CORRECTION == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_ECC_CORRECTION_HANDLER,
 #endif//channel 307
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        Reserved INT                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

     #if INTC_CHANNEL_RESERVED_308 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_308_HANDLER,
 #endif//channel 308

     #if INTC_CHANNEL_RESERVED_309== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_309_HANDLER,
 #endif//channel 309

    #if INTC_CHANNEL_RESERVED_310 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_310_HANDLER,
 #endif//channel 310

  
  #if INTC_CHANNEL_RESERVED_311== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_311_HANDLER,
 #endif//channel 311

   #if INTC_CHANNEL_RESERVED_312== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_312_HANDLER,
 #endif//channel 312

  
  #if INTC_CHANNEL_RESERVED_313 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_313_HANDLER,
 #endif//channel 313

   
  #if INTC_CHANNEL_RESERVED_314== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_314_HANDLER,
 #endif//channel 314

   
  #if INTC_CHANNEL_RESERVED_315 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_315_HANDLER,
 #endif//channel 315

   
  #if INTC_CHANNEL_RESERVED_316 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_316_HANDLER,
 #endif//channel 316


    
  #if INTC_CHANNEL_RESERVED_317 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_317_HANDLER,
 #endif//channel 317


    
  #if INTC_CHANNEL_RESERVED_318 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_318_HANDLER,
 #endif//channel 318



    
  #if INTC_CHANNEL_RESERVED_319 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_319_HANDLER,
 #endif//channel 319


    
  #if INTC_CHANNEL_RESERVED_320 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_320_HANDLER,
 #endif//channel 320


    
  #if INTC_CHANNEL_RESERVED_321 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_321_HANDLER,
 #endif//channel 321

    
  #if INTC_CHANNEL_RESERVED_322 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_322_HANDLER,
 #endif//channel 322

    
  #if INTC_CHANNEL_RESERVED_323 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_323_HANDLER,
 #endif//channel 323

    
  #if INTC_CHANNEL_RESERVED_324 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_324_HANDLER,
 #endif//channel 324

    
  #if INTC_CHANNEL_RESERVED_325 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_325_HANDLER,
 #endif//channel 325

    
  #if INTC_CHANNEL_RESERVED_326 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_326_HANDLER,
 #endif//channel 326

    
  #if INTC_CHANNEL_RESERVED_327 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_327_HANDLER,
 #endif//channel 327

    
  #if INTC_CHANNEL_RESERVED_328 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_328_HANDLER,
 #endif//channel 328

    
  #if INTC_CHANNEL_RESERVED_329 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_329_HANDLER,
 #endif//channel 329

    
  #if INTC_CHANNEL_RESERVED_330 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_330_HANDLER,
 #endif//channel 330

    
  #if INTC_CHANNEL_RESERVED_331 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_331_HANDLER,
 #endif//channel 331

    
  #if INTC_CHANNEL_RESERVED_332 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_332_HANDLER,
 #endif//channel 332

    
  #if INTC_CHANNEL_RESERVED_333 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_333_HANDLER,
 #endif//channel 333

    
  #if INTC_CHANNEL_RESERVED_334 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_334_HANDLER,
 #endif//channel 334

    
  #if INTC_CHANNEL_RESERVED_335 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_335_HANDLER,
 #endif//channel 335

    
  #if INTC_CHANNEL_RESERVED_336 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_336_HANDLER,
 #endif//channel 336

    
  #if INTC_CHANNEL_RESERVED_337 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_337_HANDLER,
 #endif//channel 337

    
  #if INTC_CHANNEL_RESERVED_338 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_338_HANDLER,
 #endif//channel 338

    
  #if INTC_CHANNEL_RESERVED_339== UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_339_HANDLER,
 #endif//channel 339

    
  #if INTC_CHANNEL_RESERVED_340 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_340_HANDLER,
 #endif//channel 340

    
  #if INTC_CHANNEL_RESERVED_341 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_341_HANDLER,
 #endif//channel 341

    
  #if INTC_CHANNEL_RESERVED_342 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_342_HANDLER,
 #endif//channel 342

    
  #if INTC_CHANNEL_RESERVED_343 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_343_HANDLER,
 #endif//channel 343

    
  #if INTC_CHANNEL_RESERVED_344 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_344_HANDLER,
 #endif//channel 344

    
  #if INTC_CHANNEL_RESERVED_345 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_345_HANDLER,
 #endif//channel 345

    
  #if INTC_CHANNEL_RESERVED_346 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_346_HANDLER,
 #endif//channel 346

    
  #if INTC_CHANNEL_RESERVED_347 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_347_HANDLER,
 #endif//channel 347

    
  #if INTC_CHANNEL_RESERVED_348 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_348_HANDLER,
 #endif//channel 348

    
  #if INTC_CHANNEL_RESERVED_349 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_349_HANDLER,
 #endif//channel 349

    
  #if INTC_CHANNEL_RESERVED_350 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_350_HANDLER,
 #endif//channel 350

    
  #if INTC_CHANNEL_RESERVED_351 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_351_HANDLER,
 #endif//channel 351

    
  #if INTC_CHANNEL_RESERVED_352 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_352_HANDLER,
 #endif//channel 352

    
  #if INTC_CHANNEL_RESERVED_353 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_353_HANDLER,
 #endif//channel 353

    
  #if INTC_CHANNEL_RESERVED_354 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_354_HANDLER,
 #endif//channel 354

    
  #if INTC_CHANNEL_RESERVED_355 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_355_HANDLER,
 #endif//channel 355

    
  #if INTC_CHANNEL_RESERVED_356 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_356_HANDLER,
 #endif//channel 356
    
  #if INTC_CHANNEL_RESERVED_357 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_357_HANDLER,
 #endif//channel 357

 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        STM INT                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  #if INTC_CHANNEL_STM_1 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_STM_1_HANDLER,
 #endif//channel 358

   #if INTC_CHANNEL_STM_2 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_STM_2_HANDLER,
 #endif//channel 359

   #if INTC_CHANNEL_STM_3 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_STM_3_HANDLER,
 #endif//channel 360


  /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        Reserved INT                                   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  #if INTC_CHANNEL_RESERVED_361 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_361_HANDLER,
 #endif//channel 361

    
  #if INTC_CHANNEL_RESERVED_362 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL,
 #else
    INTC_CHANNEL_RESERVED_362_HANDLER,
 #endif//channel 362
    
  #if INTC_CHANNEL_RESERVED_363 == UNUSED_IRQ
      (INTC_Vector_Callback_T)NULL
 #else
    INTC_CHANNEL_RESERVED_363_HANDLER
 #endif//channel 363


};
