//==============================================================================
//
//         COPYRIGHT, 2002, DELPHI TECHNOLOGIES, INC. ALL RIGHTS RESERVED
//                                  Delphi Confidential
//
//=============================================================================

//==============================================================================
//     Include Files
//==============================================================================
#include "dd_sci.h"
#include "io_config_fmpll.h"

//==============================================================================
//     Macro Definitions
//==============================================================================
#define SCI_SBR_MIN   ( 1 )
#define SCI_SBR_MAX   ( 8191 )

#define SCI_CR1_RESET (uint32_t)(0x00000000)
#define SCI_CR2_RESET (uint16_t)(0x2000)

#define SCI_BAUD_DIVIDER       (16)
#define SCI_BAUD_DIVIDER_SHIFT (4)

#define SCI_FREQUENCY_HZ (SYSTEM_FREQUENCY_HZ)

//==============================================================================
//     Module Location
//==============================================================================
SCI_T SCI_A;      // SCI_A base address 0xFFFB0000

SCI_T SCI_B;      // SCI_B base address 0xFFFB4000

//==============================================================================
//     Global Functions
//==============================================================================
//==============================================================================
// SCI_Get_Device_Register
//==============================================================================
SCI_T* SCI_Get_Device_Register(
   IO_Configuration_T in_configuration )
{
   SCI_T *sci;

   SCI_Index_T device_index = SCI_Get_Index( in_configuration );

   switch(device_index)
   {
      case SCI_INDEX_A:
         sci = &SCI_A;
         break;

      case SCI_INDEX_B:
         sci = &SCI_B;
         break;
      
      default:
         sci = &SCI_A;
         break;
   }

     return sci;
}

//==============================================================================
// SCI_Set_Speed
//==============================================================================
bool SCI_Set_Speed( 
   IO_Configuration_T in_configuration,
   uint32_t           in_speed )
{
   SCI_T    *sci = SCI_Get_Device_Register( in_configuration );
   uint32_t sci_sbr_value;       // calculated SBR value

   if( in_speed == 0 )
   {
      sci_sbr_value = 0;
   }
   else
   {
      //   Baudrate = (SystemFreq)/(SBR_Val * 16)       
      sci_sbr_value= (SCI_FREQUENCY_HZ / in_speed ) >> SCI_BAUD_DIVIDER_SHIFT; 
      
      if( sci_sbr_value <= (uint32_t)SCI_SBR_MIN )
      {
         sci_sbr_value = (uint16_t)SCI_SBR_MIN;
      }
      else if( sci_sbr_value >= (uint32_t)SCI_SBR_MAX )
      {
         sci_sbr_value = (uint16_t)SCI_SBR_MAX;
      }
   }

//Disable the Transmitter and Receiver of SCI
   sci->CR1.F.TE = 0;
   sci->CR1.F.RE = 0;

   sci->CR1.F.SBR  = (uint16_t)sci_sbr_value;

//Enable the Transmitter and Receiver of SCI after setting Baudrate
   sci->CR1.F.TE = 1;
   sci->CR1.F.RE = 1;

   return true;
}

//==============================================================================
// SCI_Get_Speed
//==============================================================================
uint32_t SCI_Get_Speed( 
   IO_Configuration_T in_configuration )
{
   uint32_t sci_sbr;
   uint32_t sci_baud_rate;
   SCI_T    *sci = SCI_Get_Device_Register( in_configuration );

   sci_sbr = (uint32_t)sci->CR1.F.SBR;
   
   if(sci_sbr != 0)
   {
      sci_baud_rate = ( SCI_FREQUENCY_HZ / sci_sbr ) >> SCI_BAUD_DIVIDER_SHIFT;
   }
   else
   {
      sci_baud_rate = SCI_SBR_MAX;
   }

   return sci_baud_rate;
}

//==============================================================================
// SCI_Get_Loopback_Mode_Enabled
//==============================================================================
SCI_Loopback_Mode_T SCI_Get_Loopback_Mode_Enabled(
   IO_Configuration_T in_configuration )
{
   SCI_T *sci = SCI_Get_Device_Register( in_configuration );
   SCI_Loopback_Mode_T mode;

   if( sci->CR1.F.LOOPS )
   {
      mode = sci->CR1.F.RSRC ? SCI_LOOPBACK_ON_INTERNAL_CONNECT : SCI_LOOPBACK_ON_EXTERNAL_CONNECT;
   }
   else
   {
      mode = SCI_NO_LOOPBACK;
   }

   return mode;
}

//==============================================================================
// SCI_Read
//==============================================================================
uint16_t SCI_Read( 
   IO_Configuration_T in_configuration )
{
   SCI_T                *sci = SCI_Get_Device_Register( in_configuration );
   SCI_Data_Bits_T data_bits = SCI_Device_Get_Data_Format( in_configuration );
   uint16_t             data = 0;

   if( data_bits == SCI_DATA_BITS_9_BIT )
   {
      data = (uint16_t)(((uint16_t)sci->DR.F.R8) << BIT_8);
   }

   data |= (uint16_t)sci->DR.F.D;
   
   return data;
}

//==============================================================================
// SCI_Write
//==============================================================================
void SCI_Write( 
   IO_Configuration_T in_configuration,
   uint16_t           in_data )
{
   SCI_T           *sci = SCI_Get_Device_Register( in_configuration );
   SCI_Data_Bits_T data_bits = SCI_Device_Get_Data_Format( in_configuration );
   SCI_DR_T        data;

   data.U16 = 0;
   
   if( data_bits == SCI_DATA_BITS_9_BIT )
   {
      data.F.T8 = ( in_data >> BIT_8 ) & 1;
   }

   data.F.D = (uint8_t)in_data;

   sci->DR.U16 =  data.U16;
}

//==============================================================================
// SCI_Get_Interrupt_Enable
//==============================================================================
bool SCI_Get_Interrupt_Enable( 
   IO_Configuration_T in_configuration )
{
   SCI_T *sci = SCI_Get_Device_Register( in_configuration );

   // Since interrupt bits are set/reset the same time, only one need to be read
   return ( ( sci->CR1.F.TIE ) ? true : false );
}

//==============================================================================
// SCI_Set_Interrupt_Enable
//==============================================================================
bool SCI_Set_Interrupt_Enable( 
   IO_Configuration_T in_configuration,
   bool               in_state )
{
   SCI_T *sci = SCI_Get_Device_Register( in_configuration );
   bool  previous_enable_status = SCI_Get_Interrupt_Enable( in_configuration );

   if( in_state )
   {
      sci->CR1.F.TIE  = 1;
      sci->CR1.F.TCIE = 1;
      sci->CR1.F.RIE  = 1;
   }
   else
   {
      sci->CR1.F.TIE  = 0;
      sci->CR1.F.TCIE = 0;
      sci->CR1.F.RIE  = 0;
   }

   return previous_enable_status;
}

//==============================================================================
// SCI_Set_Wake_Up_Enable
//==============================================================================
void SCI_Set_Wake_Up_Enable(
   IO_Configuration_T in_configuration )
{
   SCI_T *sci = SCI_Get_Device_Register( in_configuration );

   sci->CR1.F.RWU = 1;
}

//==============================================================================
// SCI_Get_Rx_Error_Flag
//==============================================================================
bool SCI_Get_Rx_Error_Flag( 
   IO_Configuration_T in_configuration )
{
   SCI_T *sci;

   sci = SCI_Get_Device_Register( in_configuration );

   return ( (sci->SR1.F.NF | sci->SR1.F.FE | sci->SR1.F.OR | sci->SR1.F.PF ) ? true : false );
}

//==============================================================================
// SCI_Get_Status
//==============================================================================
bool SCI_Get_Status( 
   IO_Configuration_T      in_configuration, 
   SCI_Interrupt_Channel_T in_flag_id )
{
   SCI_T *sci = SCI_Get_Device_Register( in_configuration );
   bool  status = false;

   switch( in_flag_id )
   {
      case SCI_INTERRUPT_CHANNEL_RX:
         status = (bool)( sci->SR1.F.RDRF );
         break;
      case SCI_INTERRUPT_CHANNEL_TX_COMPLETE:
         status = (bool)( sci->SR1.F.TC );
         break;
      case SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY:
         status = (bool)( sci->SR1.F.TDRE );
         break;
      case SCI_INTERRUPT_CHANNEL_IDLE_LINE:
         status = (bool)( sci->SR1.F.IDLE );
         break;
      case SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR:
         status = (bool)( sci->SR1.F.OR );
         break;
      case SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR:
         status = (bool)( sci->SR1.F.NF );
         break;
      case SCI_INTERRUPT_CHANNEL_FRAME_ERROR:
         status = (bool)( sci->SR1.F.FE );
         break;
      case SCI_INTERRUPT_CHANNEL_PARITY_ERROR:
         status = (bool)( sci->SR1.F.PF );
         break;
   }

   return status;
}


//==============================================================================
// SCI_Get_Active_Status
//==============================================================================
bool SCI_Get_Active_Status(IO_Configuration_T      in_configuration)
{
	SCI_T *sci = SCI_Get_Device_Register( in_configuration );
	bool  status = false;
	status = (bool)( sci->SR1.F.RACT );
	return status;
}

//==============================================================================
// SCI_Reset_Status
//==============================================================================
void SCI_Reset_Status( 
   IO_Configuration_T      in_configuration, 
   SCI_Interrupt_Channel_T in_flag_id )
{
   SCI_T    *sci = SCI_Get_Device_Register( in_configuration );
   SCI_IFSR1_T mask;

   mask.U32 = 0;

   switch( in_flag_id )
   {
      case SCI_INTERRUPT_CHANNEL_RX:
         mask.F.RDRF = 1;
         break;
      case SCI_INTERRUPT_CHANNEL_TX_COMPLETE:
         mask.F.TC = 1;
         break;
      case SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY:
         mask.F.TDRE = 1;
         break;
      case SCI_INTERRUPT_CHANNEL_IDLE_LINE:
         mask.F.IDLE = 1;
         break;
      case SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR:
         mask.F.OR = 1;
         break;
      case SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR:
         mask.F.NF = 1;
         break;
      case SCI_INTERRUPT_CHANNEL_FRAME_ERROR:
         mask.F.FE = 1;
         break;
      case SCI_INTERRUPT_CHANNEL_PARITY_ERROR:
         mask.F.PF = 1;
         break;
   }

   sci->SR1.U32 = mask.U32;
}

//==============================================================================
// SCI_Send_Single_Break
//==============================================================================
void SCI_Send_Single_Break( 
   IO_Configuration_T in_configuration )
{
   SCI_T    *sci;
   uint32_t save_interrupt_state;

   sci = SCI_Get_Device_Register( in_configuration );

   // NOTE: The SBK bit must be Set and Reset before the break character has
   // finished transmitting; otherwise a string of break characters will be
   // sent.
   save_interrupt_state = Enter_Critical_Section();
   sci->CR1.F.SBK = true;
   sci->CR1.F.SBK = false;
   Leave_Critical_Section( save_interrupt_state );
}

//==============================================================================
// SCI_Shutdown_Device
//==============================================================================
bool SCI_Shutdown_Device( 
   IO_Configuration_T in_configuration )
{
   SCI_T    *sci; 
   uint32_t interrupt_context;

   sci = SCI_Get_Device_Register( in_configuration );

   sci->CR2.F.MDIS = 1;
   sci->CR1.F.SBR  = 0;

   return true;
}

//=============================================================================
// SCI_Configure_Device
//=============================================================================
void SCI_Configure_Device(
   IO_Configuration_T  in_configuration,
   SCI_Loopback_Mode_T in_loopback )
{
   SCI_T                     *sci                  = SCI_Get_Device_Register( in_configuration );
   SCI_Parity_T              parity                = SCI_Device_Get_Parity( in_configuration );
   SCI_Data_Bits_T           data_bits             = SCI_Device_Get_Data_Format( in_configuration );
   SCI_Wakeup_Mode_T         wakeup_mode           = SCI_Device_Get_Wakeup_Mode( in_configuration );
   SCI_Idle_Line_Type_T      idle_line             = SCI_Device_Get_Idle_Line_Type( in_configuration );
   SCI_Fast_Bit_Error_Mode_T fast_bit_error_mode   = SCI_Device_Get_Fast_Bit_Error_Mode( in_configuration );
   bool                      bit_bus_error_stop    = SCI_Device_Get_Bit_Bus_Error_Stop(in_configuration );
   SCI_Break_Bit_Mode_T      break_length          = SCI_Device_Get_Break_Length( in_configuration );
   SCI_Sample_RT_Clock_T     bit_error_sample_mode = SCI_Device_Get_Bit_Error_Sample_Mode( in_configuration);
   bool                      bit_error_stop        = SCI_Device_Get_Bit_Error_Stop( in_configuration );

   SCI_CR1_T                 CR1;
   SCI_CR2_T                 CR2;

   CR1.U32 = 0;
   CR2.U16 = 0;

   ASSERT( sci != NULL );

   CR1.F.LOOPS = ( in_loopback == SCI_NO_LOOPBACK ) ? 0 : 1;
   CR1.F.RSRC  = ( in_loopback == SCI_LOOPBACK_ON_EXTERNAL_CONNECT ) ? 1 : 0;
   CR1.F.M     = data_bits;
   CR1.F.WAKE  = wakeup_mode;
   CR1.F.ILT   = idle_line;
   CR1.F.PE    = ( parity == SCI_PARITY_NONE ) ? 0 : 1;
   CR1.F.PT    = ( parity == SCI_PARITY_ODD  ) ? 1 : 0;

   CR2.F.FBR   = fast_bit_error_mode;
   CR2.F.BSTP  = bit_bus_error_stop;
   CR2.F.BRK13 = break_length;
   CR2.F.BESM13= bit_error_sample_mode;
   CR2.F.SBSTP = bit_error_stop;
   
   //TBD: Make a configuration for these
   CR2.F.RXDMA = 0;
   CR2.F.TXDMA = 0;
   CR2.F.TXDIR  = 0;

   sci->CR1.U32 = CR1.U32;
   sci->CR2.U16 = CR2.U16;
}

//==============================================================================
// SCI_Clear_Device
//==============================================================================
void SCI_Clear_Device(
   IO_Configuration_T in_configuration )
{
   SCI_T *sci;

   sci = SCI_Get_Device_Register( in_configuration );
   sci->CR1.U32 = SCI_CR1_RESET;
   sci->CR2.U16 = SCI_CR2_RESET;
}
