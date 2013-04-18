
// Include files
#include "ccp2flexcan.h"
#include "ccp2conf.h" 
#include "ccp2main.h"
#include "inst_overlay.h"
#include "ccp2conf.h"
#include "hal_can.h"
#include "hwiocald.h"
#include "dd_flash_interface.h"
#include "dd_dma_interface.h"
#include "dd_crank_interface.h"
#include "dd_intc_interface.h"
#include "hal_ucram.h"



typedef enum 
{
   CAN_MESSAGE_IN_UNCAL_TABLE,
   CAN_MESSAGE_IN_CAL_TABLE,
   CAN_MESSAGE_NOT_IN_TABLE = 255
} CAN_MESSAGE_LOCATION;


void CCP_Received_Message( void );
void KW2KCAN_Received_Message( void );


//#define CAN_CRO_BUFFER_NUMBER  (CyCANH_MaxRxMsgs + 0)
//#define CAN_KW2K_BUFFER_NUMBER (CyCANH_MaxRxMsgs + 1)
#define FLASH_ENGINE_RAM_START (0x40002010)
#define FLASH_ENGINE_FLASH_START (0x7000)
#define FLASH_ENGINE_SIZE       (0x9000)
#define NULL_NOTIFIER_PTR        ( (void (*)(void))0 )
#define FLEXCAN_MESSAGE_NULL_CONFIG (0)


//=============================================================================
// FlexCAN Data Buffers
//=============================================================================


static uint8_t FlexCAN_TX_Buffer_CCP_DTO[8];
static uint8_t FlexCAN_TX_Buffer_CCP_DAQ0[8];
static uint8_t FlexCAN_TX_Buffer_CCP_DAQ1[8];
static uint8_t FlexCAN_TX_Buffer_CCP_DAQ2[8];
static uint8_t FlexCAN_TX_Buffer_CCP_DAQ3[8];
static uint8_t FlexCAN_TX_Buffer_CCP_KW2KCAN[8];
static uint8_t FlexCAN_RX_Buffer_CCP_CRO[8];
static uint8_t FlexCAN_RX_Buffer_CCP_KW2KCAN[8];
static uint8_t FlexCAN_RX_Buffer_MCAMOS[8];

//=============================================================================
//       CAN Application Data Configuration
//=============================================================================
const FlexCAN_message_parameter_T FlexCAN_TX_Message_Parameter_Table[] =
{


   {CCP_CANID_DTO   ,     FlexCAN_TX_Buffer_CCP_DTO    ,     NULL_NOTIFIER_PTR    ,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   {CCP_CANID_DAQ0  ,     FlexCAN_TX_Buffer_CCP_DAQ0   ,     CCP_DTM_Send_Callback,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   {CCP_CANID_DAQ1  ,     FlexCAN_TX_Buffer_CCP_DAQ1   ,     CCP_DTM_Send_Callback,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   {CCP_CANID_DAQ2  ,     FlexCAN_TX_Buffer_CCP_DAQ2   ,     CCP_DTM_Send_Callback,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   {CCP_CANID_DAQ3  ,     FlexCAN_TX_Buffer_CCP_DAQ3   ,     CCP_DTM_Send_Callback,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   {CCP_INCA_TRANSIT,     FlexCAN_TX_Buffer_CCP_KW2KCAN,     NULL_NOTIFIER_PTR    ,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   //Last Entry will always have message id 0
   {    0           ,     NULL                         ,     NULL_NOTIFIER_PTR    ,     FLEXCAN_MESSAGE_NULL_CONFIG}
};

const FlexCAN_message_parameter_T FlexCAN_RX_Message_Parameter_Table[] =
{

   {CCP_CANID_CRO   ,     FlexCAN_RX_Buffer_CCP_CRO    ,     CCP_Received_Message      ,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   {CCP_INCA_RECEIVE,     FlexCAN_RX_Buffer_CCP_KW2KCAN,     KW2KCAN_Received_Message  ,     FLEXCAN_MESSAGE_NULL_CONFIG},     
//   {MCAMOS_CANID_7EE,     FlexCAN_RX_Buffer_MCAMOS     ,     MCAMOS_Process_7EE_Message,     FLEXCAN_MESSAGE_NULL_CONFIG},     
 //  {MCAMOS_CANID_7EF,     FlexCAN_RX_Buffer_MCAMOS     ,     MCAMOS_Process_7EF_Message,     FLEXCAN_MESSAGE_NULL_CONFIG},     
   //Last Entry will always have message id 0
   {    0           ,     NULL                         ,     NULL_NOTIFIER_PTR         ,     FLEXCAN_MESSAGE_NULL_CONFIG}
};



uint8_t FlexCAN_RX_Message_Count[sizeof(FlexCAN_RX_Message_Parameter_Table)/sizeof(FlexCAN_RX_Message_Parameter_Table[0])];

//=============================================================================
// FlexCAN_RX_CallBack
//=============================================================================
bool Get_Message( uint32_t in_message_id,
                  uint8_t *message_address )
{
   uint8_t * dest_buffer;
   uint8_t message;
   uint8_t index;
   bool    new_message;

   for (message = 0; FlexCAN_RX_Message_Parameter_Table[message].Message_ID!=0; message ++)
   {
      if ( FlexCAN_RX_Message_Parameter_Table[message].Message_ID == in_message_id)
         break;
   }
   
   if ( FlexCAN_RX_Message_Count[message] > 0 )
   {
      dest_buffer = FlexCAN_RX_Message_Parameter_Table[message].FlexCAN_buffer_ptr;
      for (index = 0; index < 8; index++)
      {
         *message_address++ = *dest_buffer++ ;
      }
      FlexCAN_RX_Message_Count[message]--;
      new_message = true;
   }
   else
   {
      new_message = false;
   }

   return (new_message);
}


//=============================================================================
// FlexCAN_RX_CallBack
//=============================================================================
void FlexCAN_RX_CallBack (
      uint32_t in_message_id,
      uint8_t *in_data_buffer,
      uint8_t  in_data_length)
{
   uint8_t * dest_buffer;
   uint8_t message;
   uint8_t index;
   CAN_MESSAGE_LOCATION     msg_location = CAN_MESSAGE_NOT_IN_TABLE;

   for (message = 0; FlexCAN_RX_Message_Parameter_Table[message].Message_ID!=0; message ++)
   {
      if ( FlexCAN_RX_Message_Parameter_Table[message].Message_ID == in_message_id)
      {
         msg_location = CAN_MESSAGE_IN_UNCAL_TABLE;
         break;
      }
   }

   if (CAN_MESSAGE_IN_UNCAL_TABLE == msg_location) 
   {
      dest_buffer = FlexCAN_RX_Message_Parameter_Table[message].FlexCAN_buffer_ptr;
      for (index = 0; index < in_data_length; index++)
      {

         *dest_buffer++ = *in_data_buffer++;
      }

      FlexCAN_RX_Message_Count[message]++;
      if(FlexCAN_RX_Message_Parameter_Table[message].notifier_function_ptr != NULL)
      {
         FlexCAN_RX_Message_Parameter_Table[message].notifier_function_ptr();
      }
   else 
   {
   }
  }
}

//=============================================================================
// FlexCAN_TX_CallBack
//=============================================================================
void FlexCAN_TX_CallBack ( 
      uint32_t message_id          )
{
   uint8_t message;
   CAN_MESSAGE_LOCATION     msg_location = CAN_MESSAGE_NOT_IN_TABLE;

   for (message = 0; FlexCAN_TX_Message_Parameter_Table[message].Message_ID!=0; message ++)
   {
      if ( FlexCAN_TX_Message_Parameter_Table[message].Message_ID == message_id)
      {
         msg_location = CAN_MESSAGE_IN_UNCAL_TABLE;
         break;
      }
   }

   if (CAN_MESSAGE_IN_UNCAL_TABLE == msg_location) 
   {
      if (FlexCAN_TX_Message_Parameter_Table[message].notifier_function_ptr != NULL)
      {
         FlexCAN_TX_Message_Parameter_Table[message].notifier_function_ptr();
      }
   }
   else 
   {
      //do nothing
   }

}


//=============================================================================
// Name:         CCP_Received_Message
// Purpose:      Called by can driver when a CCP message interrupt is
//               received.
// Parameters:   None
// Return Value: None
// Design Info:  CAN_CRO_BUFFER_NUMBER must align with the CAN driver CRO 
//=============================================================================
void CCP_Received_Message( void )
{
   uint8_t receive_message[8];

   if( Get_Message( CCP_CANID_CRO, receive_message ) )
   {
      CCP_Process_Command( receive_message );
   }
}

void Seed_N_Key_Msg_Timer(void)
{
}

void Force_Stay_In_Boot(uint16_t pattern)
{
    HAL_uncleard_ram.bootblock[2] = (pattern&0xFF00)>>8;
    HAL_uncleard_ram.bootblock[3] = (pattern&0x00FF);
    //RequestIO_Software_Reset();
    INTC_EXCEPTION_Halt();
}

void Copy_ROM_to_RAM_and_Execute(uint8_t* RAM_start_Address, uint8_t* ROM_start_address, uint32_t size)
{
   void (*function_ptr) (void);
   function_ptr = (void (*)(void))((uint32_t*)RAM_start_Address);
   while(size--)
   {
      *RAM_start_Address++ = *ROM_start_address++;
   }
   function_ptr();
}

//extern const IO_Configuration_T DMA_ADC_AUTOSCAN_CONFIGURATION;
/*===========================================================================*\
 * Name:         KW2KCAN_Received_Message                                    *
 * Purpose:      Called by can driver when a KW2K over CAN msg is received.  *
 *                                                                           *
 * Parameters:   None                                                        *
 * Return Value: None                                                        *
 * Design Info:                                                              *
 \*===========================================================================*/
//void Force_Stay_In_Boot(uint16_t pattern);
//void Copy_ROM_to_RAM_and_Execute(uint8_t* RAM_start_Address, uint8_t* ROM_start_address, uint32_t size);

void KW2KCAN_Received_Message( void )
{


   // Validate ECU Conditions
   // Engine Speed < 200 RPM
   // Brain Dead Recovery Enabled

   if ( CRANK_Get_Engine_Speed() < V_RPMa( 200 ) //&&
      //  ((0xAA == KySYST_BrainDeadBOOT_RecovEnbld)||(CPU_Info == CPU_LCI) )
      )
   {

      // Put ECU into a known safe state 
     // SetIO_Outputs_For_Flash_Program();

      Disable_Interrupts();

      DMA_Clear_Device( );

      //Disable Watchdog
      //SCU_WDT_Enable_Watch_Dog_Timer(false);
     if(CPU_Info == CPU_LCI)
     {
        INST_Set_Active_Calibration_Page( INST_CALIBRATION_PAGE_REFERENCE );
     }		
      Force_Stay_In_Boot(0xBEEF);

   }


}


