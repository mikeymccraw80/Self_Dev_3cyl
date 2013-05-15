//=============================================================================
//
//       COPYRIGHT, 2006, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_sci_interrupt.c~kok_pt2#4:csrc:tci_pt2#22 %
//
// created_by:       fz3pdz
//
// date_created:     Mon Apr 24 10:13:30 2006
//
// %derived_by:      pzkdkj %
//
// %date_modified:   Thu Sep  8 07:10:48 2011 %
//
// %version:         kok_pt2#4 %
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================
#include "io_type.h"
#include "dd_sci.h"
#include "dd_sci_interrupt.h"
#include "dd_intc.h"

//=============================================================================
// SCI_INTERRUPT_Clear
//=============================================================================
void SCI_INTERRUPT_Clear(
   IO_Configuration_T   in_configuration )
{
   SCI_INTERRUPT_Set_Enable( in_configuration, false );
   SCI_INTERRUPT_Clear_Pending( in_configuration );
   //TBD: Not sure we want to do this
   //INTC_INTERRUPT_Clear( in_configuration );
}

//=============================================================================
// SCI_INTERRUPT_Set_Enable
//=============================================================================
void SCI_INTERRUPT_Set_Enable(
   IO_Configuration_T   in_configuration,
   bool                 in_enable )
{
   SCI_Interrupt_Channel_T channel = SCI_Interrupt_Get_Channel( in_configuration );
   SCI_Index_T              device = SCI_Get_Index( in_configuration );
   SCI_T*                      sci = SCI_Get_Device_Register( device );

   switch( channel )
   {
   case SCI_INTERRUPT_CHANNEL_RX:
      sci->CR1.F.RIE = in_enable;
      break;
   case SCI_INTERRUPT_CHANNEL_TX_COMPLETE:
      sci->CR1.F.TCIE = in_enable;
      break;
   case SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY:
      sci->CR1.F.TIE = in_enable;
      break;
   case SCI_INTERRUPT_CHANNEL_IDLE_LINE:
      sci->CR1.F.ILIE = in_enable;
      break;
   case SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR:
      sci->CR2.F.ORIE = in_enable;
      break;
   case SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR:
      sci->CR2.F.NFIE = in_enable;
      break;
   case SCI_INTERRUPT_CHANNEL_FRAME_ERROR:
      sci->CR2.F.FEIE = in_enable;
      break;
   case SCI_INTERRUPT_CHANNEL_PARITY_ERROR:
      sci->CR2.F.PFIE = in_enable;
      break;
   default:
      ASSERT( 0 );
      break;
   }
}

//=============================================================================
// SCI_INTERRUPT_Get_Enable
//=============================================================================
bool SCI_INTERRUPT_Get_Enable(
   IO_Configuration_T   in_configuration )
{
   SCI_Interrupt_Channel_T channel = SCI_Interrupt_Get_Channel( in_configuration );
   SCI_Index_T              device = SCI_Get_Index( in_configuration );
   SCI_T*                      sci = SCI_Get_Device_Register( device );
   bool                    enabled = false;
   
   switch( channel )
   {
   case SCI_INTERRUPT_CHANNEL_RX:
      enabled = (bool)(sci->CR1.F.RIE);
      break;
   case SCI_INTERRUPT_CHANNEL_TX_COMPLETE:
      enabled = (bool)(sci->CR1.F.TCIE);
      break;
   case SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY:
      enabled = (bool)(sci->CR1.F.TIE);
      break;
   case SCI_INTERRUPT_CHANNEL_IDLE_LINE:
      enabled = (bool)(sci->CR1.F.ILIE);
      break;
   case SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR:
      enabled = (bool)(sci->CR2.F.ORIE);
      break;
   case SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR:
      enabled = (bool)(sci->CR2.F.NFIE);
      break;
   case SCI_INTERRUPT_CHANNEL_FRAME_ERROR:
      enabled = (bool)(sci->CR2.F.FEIE);
      break;
   case SCI_INTERRUPT_CHANNEL_PARITY_ERROR:
      enabled = (bool)(sci->CR2.F.PFIE);
      break;
   default:
      ASSERT( 0 );
      break;
   }

   return enabled;
}

//=============================================================================
// SCI_INTERRUPT_Get_Status
//=============================================================================
bool SCI_INTERRUPT_Get_Status(
   IO_Configuration_T   in_configuration )
{
   SCI_Interrupt_Channel_T channel = SCI_Interrupt_Get_Channel( in_configuration );
   SCI_Index_T              device = SCI_Get_Index( in_configuration );
   SCI_T*                      sci = SCI_Get_Device_Register( device );
   bool                    enabled = false;

   switch( channel )
   {
   case SCI_INTERRUPT_CHANNEL_RX:
      enabled = (bool)(sci->SR1.F.RDRF);
      break;
   case SCI_INTERRUPT_CHANNEL_TX_COMPLETE:
      enabled = (bool)(sci->SR1.F.TC);
      break;
   case SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY:
      enabled = (bool)(sci->SR1.F.TDRE);
      break;
   case SCI_INTERRUPT_CHANNEL_IDLE_LINE:
      enabled = (bool)(sci->SR1.F.IDLE);
      break;
   case SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR:
      enabled = (bool)(sci->SR1.F.OR);
      break;
   case SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR:
      enabled = (bool)(sci->SR1.F.NF);
      break;
   case SCI_INTERRUPT_CHANNEL_FRAME_ERROR:
      enabled = (bool)(sci->SR1.F.FE);
      break;
   case SCI_INTERRUPT_CHANNEL_PARITY_ERROR:
      enabled = (bool)(sci->SR1.F.PF);
      break;
   default:
      ASSERT( 0 );
      break;
   }

   return enabled;

}

//=============================================================================
// SCI_INTERRUPT_Clear_Pending
//=============================================================================
void SCI_INTERRUPT_Clear_Pending(
   IO_Configuration_T   in_configuration )
{
   SCI_Interrupt_Channel_T channel = SCI_Interrupt_Get_Channel( in_configuration );
   SCI_Index_T              device = SCI_Get_Index( in_configuration );
   SCI_T*                      sci = SCI_Get_Device_Register( device );
   uint32_t                    reg_value;
   switch( channel )
   {
   case SCI_INTERRUPT_CHANNEL_RX:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_RDRF_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   case SCI_INTERRUPT_CHANNEL_TX_COMPLETE:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_TC_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   case SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_TDRE_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   case SCI_INTERRUPT_CHANNEL_IDLE_LINE:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_IDLE_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   case SCI_INTERRUPT_CHANNEL_OVERRUN_ERROR:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_OR_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   case SCI_INTERRUPT_CHANNEL_NOISE_FLAG_ERROR:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_NF_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   case SCI_INTERRUPT_CHANNEL_FRAME_ERROR:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_FE_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   case SCI_INTERRUPT_CHANNEL_PARITY_ERROR:
        reg_value = sci->SR1.U32;
        reg_value = (reg_value & ESCI_SR_PF_CLEAR_MASK);
        sci->SR1.U32 = reg_value;
      break;
   default:
      ASSERT( 0 );
      break;
   }

}

