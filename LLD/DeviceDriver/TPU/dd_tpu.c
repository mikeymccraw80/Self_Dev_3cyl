
//#include "dd_tpu.h"
#include "io_config_tpu.h"
//=============================================================================
//                        TPU Variables
//=============================================================================
#define SECTION_TPU_REGISTER
#include "section.h"
TPU_T           TPU;
#define SECTION_END
#include "section.h"

#define TPU_SCM_BLOCK_SIZE         (uint32_t)(2048)

#define TPU_SCM_12K_SIZE           (uint32_t)( 1024 * 12 )
#define TPU_SCM_14K_SIZE           (uint32_t)( 1024 * 14)
#define TPU_SCM_16K_SIZE           (uint32_t)( 1024 * 16 )
#define TPU_SCM_20K_SIZE           (uint32_t)( 1024 * 20 )
#define TPU_SCM_24K_SIZE           (uint32_t)( 1024 * 24 )

#define TPU_SDM_BLOCK_SIZE        (uint32_t)(8)

#define TPU_SDM_BUFFER_ADDR(index)                                                \
   (TPU_SDM_BLOCK_ALIGN( (TPU_Get_SDM_Base_Address(index) + TPU_SDM_SIZE(index)) - 32 ))

#define TPU_SDM_BUFFER_BASE(index)                                                \
   (TPU_SDM_BUFFER_ADDR(index) - TPU_Get_SDM_Base_Address(index))

#define TPU_SDM_BUFFER(index)                                                      \
   (*( volatile struct TPU_SDM_Buffer_Tag *) TPU_SDM_BUFFER_ADDR(index))

#define CTBASE_BIT_POSITION         (7)
#define CDCR_SDM_MASK               (0x7f)
#define WRITE_COHERENT_DATA         (1)
#define READ_COHERENT_DATA          (0)
#define START_COHERENT_TRANSFER     (1)
#define COHERENT_TRANSFER_COMPLETE  (0)

#define ETPU_GLOBAL_EXCEPTION_MASK  (0x0f000000)

const uint32_t TPU_RESET_STATUS_REG = 0x00000000;

typedef struct TPU_SDM_Buffer_Tag
{
   uint32_t Parameter_0;
   uint32_t Parameter_1;

} TPU_SDM_Buffer_T;


//=============================================================================
// TPU_Initialize_SCM_SDM
//=============================================================================
void TPU_Initialize_SCM_SDM(
   void )
{
   uint32_t index;
   uint32_t ucode_size;
   uint32_t scm_size;
   uint32_t* memory;
   uint32_t etpu_sdm_end_address;
   uint32_t sdm_start_address;
   uint32_t TPU_SCM_Size;

   // Init SCM - Start
   // Stop engines
   TPU.ECR[TPU_INDEX_0].F.MDIS = 1;

//Wait until engine is stopped
   while(0 ==TPU.ECR[TPU_INDEX_0].F.STF) 
   {
      ;
   }
   // Disable Checksum Protection 
   TPU.MCR.F.SCMMISEN = 0;

   //set visibility bit 
   TPU.MCR.F.VIS = 1;

   // Download the microcode into SCM
   TPU_SCM_Size = (( TPU.MCR.F.SCMSIZE + 1 ) * TPU_SCM_BLOCK_SIZE );

   ucode_size = sizeof( etpu_ucode_image ) / sizeof(uint32_t);
   scm_size = ( TPU_SCM_Size / sizeof(uint32_t) );

   if( ucode_size > scm_size )
   {
      ucode_size = scm_size;
   }

   index = 0;

   while( index < ucode_size )
   {
      ((uint32_t *)&TPU.SCM)[index] = etpu_ucode_image[index];
      index ++;
   }

   while( index < scm_size )
   {
      ((uint32_t *)&TPU.SCM)[index] = 0;
      index ++;
   }

   // Write the Micro-Code Checksum 
   switch((ucode_size * sizeof(uint32_t)))
   {

#ifdef ETPU_CHECKSUM_14K
      case TPU_SCM_14K_SIZE:
      TPU.MISCCMPR = ETPU_CHECKSUM_14K;
      break;
#endif

#ifdef ETPU_CHECKSUM_16K
   case TPU_SCM_16K_SIZE:
      TPU.MISCCMPR = ETPU_CHECKSUM_16K;
      break;
#endif

   default :
      break;

   }

   // clear visibility bit 
   TPU.MCR.F.VIS = 0;
   // Enable Checksum Protection 
   TPU.MCR.F.SCMMISEN = 1;
   // Start Engines 
   TPU.ECR[TPU_INDEX_0].F.MDIS = 0;
   // Init SCM - END
   sdm_start_address = (uint32_t)(TPU_Get_SDM_Base_Address(TPU_INDEX_0));

   // Init SDM
   etpu_sdm_end_address = (uint32_t)( TPU_Get_SDM_Base_Address(TPU_INDEX_0) + TPU_SDM_SIZE(TPU_INDEX_0) );

   // Clear Parameter RAM
   for( memory =  (uint32_t*)sdm_start_address;
        (uint32_t)memory < etpu_sdm_end_address;
        memory ++ )
   {
      *memory = 0;
   }
}


//=============================================================================
// TPU_Initialize_Channels
//=============================================================================
void TPU_Initialize_Channels(
         TPU_Index_T index)
{
    // Disable all channel interrupt
   TPU.CIER[index].U32 = (uint32_t)TPU_INITIAL_CIER[index].U32;
   // Disable Data Transfer Request
   TPU.CDTRER[index].U32 = (uint32_t)TPU_INITIAL_CDTRER[index].U32;
   // Clear all Interrupt status registers
   TPU.CISR[index].U32 = TPU_RESET_STATUS_REG;

   //Clear Channel Data Transfer Request
   TPU.CDTRSR[index].U32 = TPU_RESET_STATUS_REG;

   //Clear Channel Interrupt Overflow Status
   TPU.CIOSR[index].U32 = TPU_RESET_STATUS_REG;

   //Clear Channel Data Transfer Request Overflow Status
   TPU.CDTROSR[index].U32 = TPU_RESET_STATUS_REG;

   //Initialize Timer configration registers
   TPU.Clock[index].TBCR.U32 = (uint32_t)TPU_INITIAL_Clock[index].TBCR.U32;

   //Initialize STAC BUS configuration registers
   TPU.Clock[index].REDCR.U32 = (uint32_t)TPU_INITIAL_Clock[index].REDCR.U32;

   //Initialize Engine configuration registers
   TPU.ECR[index].U32 = (uint32_t)TPU_INITIAL_ECR[index].U32;
}

//=============================================================================
// TPU_Initialize_Device
//=============================================================================
void TPU_Initialize_Device(void )
{
   uint32_t interrupt_status;
   uint32_t index;

   // Turn off eTPU and eMIOS timers
   // WARNING: this turns off the eMIOS timers also
   TPU.MCR.F.GTBE = 0;
   TPU_Initialize_SCM_SDM();
   //Reset cause of exception 
   TPU_GLOBAL_RAM(TPU_INDEX_0).Cause_Of_Exception = CAUSE_OF_EXCEPTION_CLEAR;

      // Init Engine - Start
   // Reset cause of exception 
   // Set TPU recovery Opcode
   TPU.SCMOFFDATAR = (uint32_t)ETPU_RECOVERY_OPCODE;

   //Initialize Coherent Dual-Parameter Controller (CDCR)
   TPU.CDCR.U32 = TPU_INITIAL_CDCR.U32;
   TPU_Initialize_Channels( TPU_INDEX_0);
   //Initialize Module configuration register
   TPU.MCR.U32 = TPU_INITIAL_MCR.U32;
  
}



//=============================================================================
// TPU_Clear_Global_Exception
//=============================================================================
void TPU_Clear_Global_Exception(
   uint32_t in_context )
{
   static TPU_MCR_T tpu_mcr_debug;
   uint32_t interrupt_status;
   static void (*signature_fault_callback)( void );



   tpu_mcr_debug.U32 = TPU.MCR.U32;

   // Check for Checksum Fault 
   if( tpu_mcr_debug.F.SCMMISF == 1 )
   {
      // Use callback function to report fault to customer application. 
      if ( NULL != (void *)in_context )
      {
         signature_fault_callback = (void *)in_context;
         (*signature_fault_callback)();
      }
   }

   // Check for non-Checksum Faults 
   if( tpu_mcr_debug.U32 & ETPU_GLOBAL_EXCEPTION_MASK )
   {

   }

   // Clear Exception 
   TPU.MCR.F.GEC = 1;

   // Exiting Critical Section
}

//=============================================================================
// TPU_SDM_Read_Coherent_Data
//=============================================================================
void TPU_SDM_Read_Coherent_Data( 
   bool      parameter_width,
   uint32_t* parameter_0_ptr,
   uint32_t* parameter_0_data,
   uint32_t* parameter_1_ptr,
   uint32_t* parameter_1_data )
{


   uint32_t SDM_address = TPU_Get_SDM_Base_Address(TPU_INDEX_0);
   TPU_SDM_BUFFER(TPU_INDEX_0).Parameter_0 = 0;
   TPU_SDM_BUFFER(TPU_INDEX_0).Parameter_1 = 0;

   TPU.CDCR.F.PBBASE  = TPU_SDM_BUFFER_ADDR(TPU_INDEX_0)/TPU_SDM_BLOCK_SIZE;
   TPU.CDCR.F.CTBASE = ((( (uint32_t)parameter_0_ptr - SDM_address ) /
                        sizeof(uint32_t) ) >> CTBASE_BIT_POSITION );

   TPU.CDCR.F.PARM0 = ((( (uint32_t)parameter_0_ptr - SDM_address ) /
                        sizeof(uint32_t) ) & CDCR_SDM_MASK );

   TPU.CDCR.F.PARM1 = ((( (uint32_t)parameter_1_ptr - SDM_address ) /
                        sizeof(uint32_t) ) & CDCR_SDM_MASK );

   TPU.CDCR.F.PWIDTH = parameter_width;
   TPU.CDCR.F.WR = READ_COHERENT_DATA;
   TPU.CDCR.F.STS = START_COHERENT_TRANSFER;

   while ( TPU.CDCR.F.STS != COHERENT_TRANSFER_COMPLETE )
   {
      ;/* Wait for data to be transfered */
   }
   *parameter_0_data = TPU_SDM_BUFFER(TPU_INDEX_0).Parameter_0;
   *parameter_1_data = TPU_SDM_BUFFER(TPU_INDEX_0).Parameter_1;

   // Exiting Critical Section
}

//============================================================================
// TPU_SDM_Write_Coherent_Data
//============================================================================
void TPU_SDM_Write_Coherent_Data(
   bool      parameter_width,
   uint32_t* parameter_0_ptr,
   uint32_t  parameter_0_data,
   uint32_t* parameter_1_ptr,
   uint32_t  parameter_1_data )
{


   uint32_t SDM_address = TPU_Get_SDM_Base_Address(TPU_INDEX_0);
   TPU_SDM_BUFFER(TPU_INDEX_0).Parameter_0 = parameter_0_data;
   TPU_SDM_BUFFER(TPU_INDEX_0).Parameter_1 = parameter_1_data;

   TPU.CDCR.F.PBBASE  = TPU_SDM_BUFFER_BASE(TPU_INDEX_0)/TPU_SDM_BLOCK_SIZE;
   TPU.CDCR.F.CTBASE = ((( (uint32_t)parameter_0_ptr - SDM_address ) /
                        sizeof(uint32_t) ) >> CTBASE_BIT_POSITION );
   TPU.CDCR.F.PARM0 = ((( (uint32_t)parameter_0_ptr - SDM_address ) /
                        sizeof(uint32_t) ) & CDCR_SDM_MASK );
   TPU.CDCR.F.PARM1 = ((( (uint32_t)parameter_1_ptr - SDM_address ) /
                        sizeof(uint32_t) ) & CDCR_SDM_MASK );

   TPU.CDCR.F.PWIDTH = parameter_width;
   TPU.CDCR.F.WR = WRITE_COHERENT_DATA;
   TPU.CDCR.F.STS = START_COHERENT_TRANSFER;

   while ( TPU.CDCR.F.STS != COHERENT_TRANSFER_COMPLETE )
   {
      ;/* Wait for data to be transfered */
   }

}


//=============================================================================
// TPU_Set_HSR
//=============================================================================
void TPU_Set_HSR(
       TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure,
   uint8_t              in_hsr)
{
   uint32_t interrupt_status;
       TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   // Wait Until Channel Not Active
   TPU_Wait_HSR_Request_Complete(index, configure);
   // Issue HSR 
   TPU.Channel_Map[index].Channel_Control[channel].CHSRR.F.HSR = in_hsr;

}

//=============================================================================
// TPU_Set_Function_Mode0
//=============================================================================
void TPU_Set_Function_Mode0(
       TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure,
   uint8_t              in_time_base)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU.Channel_Map[index].Channel_Control[channel].CSCR.F.FM0 = in_time_base;
}

//=============================================================================
// TPU_Set_Function_Mode1
//=============================================================================
void TPU_Set_Function_Mode1(
       TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure,
   uint8_t              in_function_mode1)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU.Channel_Map[index].Channel_Control[channel].CSCR.F.FM1 = in_function_mode1;
}

//=============================================================================
// TPU_Set_Static_Base_Address
//=============================================================================
void TPU_Set_Static_Base_Address(
    TPU_Index_T index,
   TPU_CHANNEL_Configuration_T   configure)
{
   uint32_t             channel_sdm_address;   
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   
   channel_sdm_address = TPU_Get_Channel_SDM_Start_Address(index,configure);
   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CPBA = 
            (( channel_sdm_address - TPU_Get_SDM_Base_Address(TPU_INDEX_0) ) / TPU_SDM_BLOCK_SIZE );
}

//=============================================================================
// TPU_Get_Static_Base_Address
//=============================================================================
uint32_t TPU_Get_Static_Base_Address(
   TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{

    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   return TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CPBA;
}

//=============================================================================
// TPU_Wait_HSR_Request_Complete
//=============================================================================
void TPU_Wait_HSR_Request_Complete(
          TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{
   uint8_t hsr_status;
   uint32_t  loop_count = 0;
   TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   // Wait Until Channel Not Active 
   hsr_status = (uint8_t)TPU.Channel_Map[index].Channel_Control[channel].CHSRR.F.HSR;
   while( 0 != hsr_status )
   {
      loop_count ++;
      if( loop_count > MAX_HSR_LOOP_COUNT )
      {
         hsr_status = 0;
      }
      else
      {
         hsr_status = (uint8_t)TPU.Channel_Map[index].Channel_Control[channel].CHSRR.F.HSR;
      }
   }
}


//=============================================================================
// TPU_Get_Channel_SDM_Start_Address
//=============================================================================
uint32_t TPU_Get_Channel_SDM_Start_Address(
   TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{

    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   return(TPU_INITIAL_SDM_ADDRESS[index][channel]);
}




//=============================================================================
// TPU_DISCRETE_Get_State
// This function should be used only on the INPUT CHANNELS
//=============================================================================
bool TPU_DISCRETE_Get_State(
     TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{

   Polarity_T  polarity   =  configure.F.TPU_CHANNEL_CONFIGURATION_POLARITY;
   uint32_t             value;
   TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   value = TPU.Channel_Map[index].Channel_Control[channel].CSCR.F.IPS;

   return (( value == polarity ) ? true : false);
}


//=============================================================================
// TPU_INTERRUPT_Clear
//
// @func Clears a configured interrupt for a specific device based on its
// configuration value passed in.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc none
//
// @end
//=============================================================================
void TPU_INTERRUPT_Clear(
   TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU.CISR[index].U32 = 0x00000001<<channel; // 1 = Clear  
}

//=============================================================================
// TPU_INTERRUPT_Set_Enable
//
// @func Enables or disables the interrupt for the specific configuration requested.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @parm bool | inEnable | true enabled, False disabled.
//
// @rdesc none
//
// @end
//=============================================================================
void TPU_INTERRUPT_Set_Enable(
  TPU_Index_T index,
  TPU_CHANNEL_Configuration_T   configure,
   bool                 in_enable )
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CIE = in_enable;
}

//=============================================================================
// TPU_INTERRUPT_Get_Enable
//
// @func .
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc true enabled, False disabled
//
// @end
//=============================================================================
bool TPU_INTERRUPT_Get_Enable(
    TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   return ((bool)TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CIE);
}


//=============================================================================
// TPU_INTERRUPT_Clear_Pending
//
// @func  the interrupt enable state for the input configuration's associated
// interrupt.
//
// @parm IO_Configuration_T | in_configuration | A configurable value set in
//          io_config.h that specifies the device type, device number,
//          pin output, and device specific information.
//
// @rdesc The status of the Timer
// @flag true | interrupt is enabled
// @flag false | interrupt is disabled
//
// @end
//=============================================================================
void TPU_INTERRUPT_Clear_Pending(
    TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU.CISR[index].U32 = 0x00000001<<channel; // 1 = Clear

}



//=============================================================================
// TPU_Initialize_Channel
//=============================================================================
void TPU_Initialize_Channel(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;

   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CPR  = 0;  // CPR = 0, Disables the channel

   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CFS  = 
      configure.F.TPU_CHANNEL_CONFIGURATION_PRIMITIVE;
   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.ODIS = 
      configure.F.TPU_CHANNEL_CONFIGURATION_OUTPUT_DISABLE;

   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CIE  = 
      configure.F.TPU_CHANNEL_CONFIGURATION_IREN;
   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.DTRE = 
      configure.F.TPU_CHANNEL_CONFIGURATION_TREN;
}


//=============================================================================
// TPU_Channel_Enable
//=============================================================================
void TPU_Channel_Enable(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CPR  = 
       configure.F.TPU_CHANNEL_CONFIGURATION_CPR;

}

//=============================================================================
// TPU_Channel_Disable
//=============================================================================
void TPU_Channel_Disable(
       TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
{
    TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   // Wait until the channel not active
   TPU_Wait_HSR_Request_Complete( index,configure  );

   TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CPR  = 0;  // CPR = 0, Disables the channel
}

//=============================================================================
// TPU_Get_Channel_Status
//=============================================================================
bool TPU_Get_Channel_Status(
      TPU_Index_T index,
      TPU_CHANNEL_Configuration_T   configure)
  {
   TPU_Channel_T channel;
   channel = configure.F.TPU_CHANNEL_CONFIGURATION_CHANNEL;
   return (TPU.Channel_Map[index].Channel_Control[channel].CCR.F.CPR > 0) ? true : false;
}
//=============================================================================
// TPU_TIMER_Get_Value
//=============================================================================
uint32_t TPU_TIMER_Get_Value(
      TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure)
{
   uint32_t tcr_type = configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0;
   return( TPU.Clock[index].TBR[tcr_type].U32);
}

//=============================================================================
// TPU_TIMER_Get_State
//=============================================================================
Timer_State_T TPU_TIMER_Get_State(
     TPU_Index_T index,
       TPU_CHANNEL_Configuration_T   configure )
{
   Timer_State_T  timer_state = TIMER_STATE_RUNNING;

   if(TPU_TCR1_TIME_BASE == configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0)
   {
      if(TPU.Clock[index].TBCR.F.TCR1CTL == TPU_TCR1_SHUTDOWN)
      {
         timer_state = TIMER_STATE_RESET;
      }
   }
   else    //Time base selected is TCR2
   {
      if(TPU.Clock[index].TBCR.F.TCR2CTL == TPU_TCR2_SHUTDOWN)
      {
         timer_state = TIMER_STATE_RESET;
      }
   }

   return timer_state;
}

//=============================================================================
// TPU_TIMER_Get_Base_Frequency
//=============================================================================
uint32_t TPU_TIMER_Get_Base_Frequency(
   TPU_Index_T index ,
   TPU_CHANNEL_Configuration_T   configure )
{

   uint8_t  prescaler = 1;

   uint32_t                   frequency;

   if(TPU_TCR1_TIME_BASE ==configure.F.TPU_CHANNEL_CONFIGURATION_FUNCTION_MODE0)
   {
      if (TPU.Clock[index].TBCR.F.TCR1CS == 0 && TPU.Clock[index].TBCR.F.TCR1CTL == 2)
      {
         prescaler = 2;
      }
      frequency = ETPU_SYSTEM_FREQUENCY_HZ/(prescaler * (TPU.Clock[index].TBCR.F.TCR1P + 1));
   }
   else
   {
      frequency = ETPU_SYSTEM_FREQUENCY_HZ/(2 * (TPU.Clock[index].TBCR.F.TCR2P + 1));
   }
   return frequency;
}

//=============================================================================
// TPU_TIMER_Get_Size
//=============================================================================
Timer_Size_T TPU_TIMER_Get_Size(void )
{
 
   return TIMER_24_BIT;
}
