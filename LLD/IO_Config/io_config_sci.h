#ifndef IO_CONFIG_SCI_H_
#define IO_CONFIG_SCI_H_
//=============================================================================
//
//       COPYRIGHT, 2010, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:   io_config_sci.h~5:incl:ctc_pt3#1 %
//
// created_by:       fz3pdz
//
// date_created:     %data_created%
//
// %derived_by:      zzrfyj %
//
// %date_modified:          %
//
// %version:         5 %
//
//=============================================================================
#include "dd_sci.h"

//=======================================================================================
// SCI0 - SCI_DEVICE_0
//=======================================================================================
#define SCI_DEVICE_0 \
                         ( SCI_Set_Index( 0, SCI_INDEX_A                       ) | \
              SCI_Device_Set_Data_Format( 0, SCI_DATA_BITS_8_BIT               ) | \
              SCI_Device_Set_Wakeup_Mode( 0, SCI_WAKEUP_MODE_IDLE_LINE         ) | \
           SCI_Device_Set_Idle_Line_Type( 0, SCI_IDLE_LINE_TYPE_AFTER_STOP_BIT ) | \
      SCI_Device_Set_Fast_Bit_Error_Mode( 0, SCI_FAST_BIT_ERROR_MODE_OFF       ) | \
       SCI_Device_Set_Bit_Bus_Error_Stop( 0, true                             ) | \
             SCI_Device_Set_Break_Length( 0, SCI_BREAK_BIT_MODE_13_14_BITS     ) | \
    SCI_Device_Set_Bit_Error_Sample_Mode( 0, SCI_SAMPLE_RT_CLOCK_9             ) | \
           SCI_Device_Set_Bit_Error_Stop( 0, false                             ) | \
                   SCI_Device_Set_Parity( 0, SCI_PARITY_NONE                   ))

//=======================================================================================
// SCI0 TC_INT - MTSA_CONFIG_SCI_A_TC_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_A_TC_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_A                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_TX_COMPLETE      ) )

//=======================================================================================
// SCI0 TDRE_INT - MTSA_CONFIG_SCI_A_TDRE_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_A_TDRE_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_A                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY  ) )

//=======================================================================================
// SCI0 RX_INT - MTSA_CONFIG_SCI_A_RX_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_A_RX_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_A                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_RX               ) )

//=======================================================================================
// SCI1 - SCI_DEVICE_1
//=======================================================================================
#define SCI_DEVICE_1 \
                         ( SCI_Set_Index( 0, SCI_INDEX_B) | \
              SCI_Device_Set_Data_Format( 0, SCI_DATA_BITS_8_BIT               ) | \
              SCI_Device_Set_Wakeup_Mode( 0, SCI_WAKEUP_MODE_IDLE_LINE         ) | \
           SCI_Device_Set_Idle_Line_Type( 0, SCI_IDLE_LINE_TYPE_AFTER_START_BIT ) | \
      SCI_Device_Set_Fast_Bit_Error_Mode( 0, SCI_FAST_BIT_ERROR_MODE_OFF       ) | \
       SCI_Device_Set_Bit_Bus_Error_Stop( 0, false                             ) | \
             SCI_Device_Set_Break_Length( 0, SCI_BREAK_BIT_MODE_10_11_BITS     ) | \
    SCI_Device_Set_Bit_Error_Sample_Mode( 0, SCI_SAMPLE_RT_CLOCK_9             ) | \
           SCI_Device_Set_Bit_Error_Stop( 0, false                             ) | \
                   SCI_Device_Set_Parity( 0, SCI_PARITY_NONE                   ) | \
				   MTSA_CONFIG_SCI_B_RX_INTERRUPT )

//=======================================================================================
// SCI1 TC_INT - MTSA_CONFIG_SCI_B_TC_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_B_TC_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_B                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_TX_COMPLETE      ) )

//=======================================================================================
// SCI1 TDRE_INT - MTSA_CONFIG_SCI_B_TDRE_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_B_TDRE_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_B                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_TX_BUFFER_EMPTY  ) )

//=======================================================================================
// SCI1 RX_INT - MTSA_CONFIG_SCI_B_RX_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_B_RX_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_B                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_RX               ) )

//=======================================================================================
// SCI1 IDLE_INT - MTSA_CONFIG_SCI_B_IDLE_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_B_IDLE_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_B                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_IDLE_LINE        ) )

//=======================================================================================
// SCI1 FE_INT - MTSA_CONFIG_SCI_B_FE_INTERRUPT
//=======================================================================================
#define MTSA_CONFIG_SCI_B_FE_INTERRUPT \
             ( SCI_Set_Index( 0, SCI_INDEX_B                            ) | \
   SCI_Interrupt_Set_Channel( 0, SCI_INTERRUPT_CHANNEL_FRAME_ERROR      ) )

#endif // IO_CONFIG_SCI_H_
