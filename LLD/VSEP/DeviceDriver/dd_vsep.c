//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep.c~13.1.1.1.2:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 11:47:36 2005
//
// %derived_by:      dzhrz4 %
//
// %date_modified:   Fri Feb 16 12:08:07 2007 %
//
// %version:         13.1.1.1.2 %
//
// ============================================================================
// @doc
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

//=============================================================================
// Include interface for the device driver
//=============================================================================
#include "dd_vsep_fault.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_discrete_interface.h"
#include "dd_vsep_soh.h"
#include "io_config_vsep.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_msg_config.h"
#include "dd_vsep_vr.h"
#include "dd_dspi_interface.h"
#include "io_config_dma.h"
#include "io_config_dspi.h"
#include "dd_vsep_init_config.h"
#include "vsep_spi_scheduler.h"

uint32_t     VSEP_Channel_Enabled;
extern const SPI_Message_Definition_T * VSEP_MESSAGE[VSEP_MESSAGE_MAX+7];


#ifdef  VSEP_CALIBRATION_ENABLE
static void  VSEP_INIT_TXD_Buffer_Initialize(void)
{
	uint8_t               channel;
	VSEP_FAULT_FILTER_T   filter_type = VSEP_FAULT_FILTER_MAX;
	uint32_t              filter_time;

	VSEP_INIT_TXD_INITIAL[0] = VSEP_Msg_Set_FLTCLR( 0, true                   ) |
								VSEP_Msg_Set_CRTOCLR( 0, true                   ) |
								VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_NOT_USED ) | 
								VSEP_Msg_Set_SDIA( 0, VSEP_TXD_SDIA_VR1_CTRL );

	VSEP_INIT_TXD_INITIAL[1] = 
							VSEP_Msg_VR_Set_Delay( 0, (uint16_t)KsVSEP_VR1_Setting_Initial.KeVSEP_VR1_DLY) |        
							VSEP_Msg_VR_Set_AT( 0, (uint16_t)KsVSEP_VR1_Setting_Initial.KbVSEP_VR1_PERC50) |
							VSEP_Msg_VR_Set_MT( 0, (uint16_t)KsVSEP_VR1_Setting_Initial.KeVSEP_VR1_MT);

	VSEP_INIT_TXD_INITIAL[2] =     
          VSEP_Msg_VR_Set_Delay( 0, (uint16_t)KsVSEP_VR2_Setting_Initial.KeVSEP_VR2_DLY) |        
             VSEP_Msg_VR_Set_AT( 0, (uint16_t)KsVSEP_VR2_Setting_Initial.KbVSEP_VR2_PERC50) |
             VSEP_Msg_VR_Set_MT( 0, (uint16_t)KsVSEP_VR2_Setting_Initial.KeVSEP_VR2_MT) 
      ;
	VSEP_INIT_TXD_INITIAL[3] =          
          VSEP_Msg_DEPS_Set_Delay( 0, (uint16_t)KsVSEP_DEPSDLY_Setting_Initial.KeVSEP_DEPSDLY) 
      ;
	VSEP_INIT_TXD_INITIAL[4] =       
          VSEP_Msg_SLEW_Set_Group_1( 0, (uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW1) |
          VSEP_Msg_SLEW_Set_Group_2( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW2) |
          VSEP_Msg_SLEW_Set_Group_3( 0, (uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW3) |
          VSEP_Msg_SLEW_Set_Group_4( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW4) |
          VSEP_Msg_SLEW_Set_Group_5( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEW5) |
        VSEP_Msg_SLEW_Set_Group_CAN( 0,(uint16_t)KsVSEP_SLEW_Initialization.KeVSEP_SLEWCAN)
      ;
 	VSEP_INIT_TXD_INITIAL[5] =     
         VSEP_Msg_FAULT_Set_Level_1( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL1) |
         VSEP_Msg_FAULT_Set_Level_2( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL2) |
         VSEP_Msg_FAULT_Set_Level_3( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL3) |
         VSEP_Msg_FAULT_Set_Level_4( 0, (uint16_t)KsVSEP_Fault_Level_Initial1.KeVSEP_FLTLVL4) 
        
      ;
	VSEP_INIT_TXD_INITIAL[6] =      
         VSEP_Msg_FAULT_Set_Level_5( 0, (uint16_t)KsVSEP_Fault_Level_Initial2.KeVSEP_FLTLVL5) |
         VSEP_Msg_FAULT_Set_Level_6( 0,(uint16_t)KsVSEP_Fault_Level_Initial2.KeVSEP_FLTLVL6) |
         VSEP_Msg_FAULT_Set_Level_7( 0, (uint16_t)KsVSEP_Fault_Level_Initial2.KeVSEP_FLTLVL7) 
      ;
  	VSEP_INIT_TXD_INITIAL[7] =    
          ( VSEP_Msg_FAULT_Filter_Set_Non_Spark_Channels_1_To_8( 0, (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_1TO8NS) |
                VSEP_Msg_FAULT_Filter_Set_Spark_Channels_1_To_8( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_1TO8SP) |
                     VSEP_Msg_FAULT_Filter_Set_Channels_9_To_12( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_9TO12) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_13_To_16( 0, (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_13TO16) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_17_To_18( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_17TO18) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_19_To_20( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_19TO20) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_21_To_24( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_21TO24) |
                    VSEP_Msg_FAULT_Filter_Set_Channels_25_To_30( 0,  (uint16_t)KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_25TO30))
      ;
	VSEP_INIT_TXD_INITIAL[8] =      
          ( VSEP_Msg_LEDMODE_Set_Channel_25( 0, (uint16_t)KsVSEP_LEDMODE_Initial.KbVSEP_LEDMODE_25) |
            VSEP_Msg_LEDMODE_Set_Channel_26( 0, (uint16_t)KsVSEP_LEDMODE_Initial.KbVSEP_LEDMODE_26) |
            VSEP_Msg_LEDMODE_Set_Channel_30( 0, (uint16_t)KsVSEP_LEDMODE_Initial.KbVSEP_LEDMODE_30) )
      ;
  	VSEP_INIT_TXD_INITIAL[9] =     
          VSEP_Msg_IGBT_Set_GRADFILT( 0, (uint16_t)KsVSEP_GRAD_Initialization.KbVSEP_GRADFILT) |
         VSEP_Msg_IGBT_Set_GRADTHR( 0,  (uint16_t)KsVSEP_GRAD_Initialization.KbVSEP_GRADTHR) 
      ;
  	VSEP_INIT_TXD_INITIAL[10] =     
            VSEP_Msg_EST_Set_EDGE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_EDGE   ) |
           VSEP_Msg_EST_Set_INDEX( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_INDEX   ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KeVSEP_Spark_PFMODE   ) 
      ;
   	VSEP_INIT_TXD_INITIAL[11] =  
         VSEP_Msg_Set_SOHRSTEN( 0, VSEP_SOH_Get_SOHRSTEN( VSEP_0_SOHRSTEN_INIT )                                              ) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_1-VSEP_CHANNEL_MPIO_1), (uint16_t)KeVSEP_ACReq_pin79_Status) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_2-VSEP_CHANNEL_MPIO_1), (uint16_t)KeVSEP_PSPS_pin60_Status) |
         VSEP_Msg_MPIO_Set_Mx_OHILOB_OEN( 0, (VSEP_CHANNEL_MPIO_3-VSEP_CHANNEL_MPIO_1), (uint16_t)KeVSEP_MIDAC_pin40_Status) |
                 VSEP_Msg_EST_Set_CYLCNT( 0, (uint16_t)KsVSEP_Spark_Mode_Initialization.KeVSEP_Spark_CYLCNT   ) |
              VSEP_Msg_EST_Set_DEC_DISCB( 0,    (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_DEC_DISCB ) |
                VSEP_Msg_EST_Set_IGBTCFG( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_IGBTCFG      ) |
		VSEP_Msg_SOH_Set_CRDISARM( 0,     VSEP_SOH_Get_ENABLE_STATE( VSEP_0_SOH_ENABLE_INIT )        )
	;
	
  VSEP_EST_SELECT_INITIAL[0] =      
         VSEP_Msg_Set_SDOA( 0, VSEP_RXD_SDOA_EST_STAT  ) |
         VSEP_Msg_Set_SDIA(0,VSEP_TXD_SDIA_EST_CTRL)  
       ;
    VSEP_EST_SELECT_INITIAL[1] =      
           VSEP_Msg_EST_Set_EDGE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_EDGE   ) |
          VSEP_Msg_EST_Set_INDEX( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KbVSEP_Spark_INDEX   ) |
          VSEP_Msg_EST_Set_PFMODE( 0,     (uint16_t)KsVSEP_Spark_Mode_Initialization.KeVSEP_Spark_PFMODE   ) 
     ;

	
		
for(channel=0;channel<30;channel++){
	if( channel >= VSEP_CHANNEL_PCH_01_FLT_LVL_1 )
   {
      if( channel <= VSEP_CHANNEL_PCH_08_FLT_LVL_1_2 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_1TO8NS;
      }
      else if (channel <= VSEP_CHANNEL_PCH_12_FLT_LVL_2)
      {
         filter_type =KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_9TO12;
      }
      else if (channel <= VSEP_CHANNEL_PCH_16_PWM_2_FLT_LVL_3 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_13TO16;
      }
      else if (channel <= VSEP_CHANNEL_PCH_18_FLT_LVL_4 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_17TO18;
      }
      else if (channel <= VSEP_CHANNEL_PCH_20_FLT_LVL_5 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_19TO20;
      }
      else if (channel <= VSEP_CHANNEL_PCH_24_PWM_5_FLT_LVL_6 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_21TO24;
      }
      else if (channel <= VSEP_CHANNEL_PCH_30_FLT_LVL_7 )
      {
         filter_type = KsVSEP_Fault_Filter_Initial.KeVSEP_FILT_25TO30;
      }
      else
      {
         //  Not a valid value for channel
      }
   }

   switch (filter_type)
   {
      case VSEP_FAULT_FILTER_7_5US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_7_5US;
         break;
      }
      case VSEP_FAULT_FILTER_15US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_15US;
         break;
      }
      case VSEP_FAULT_FILTER_34US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_34US;
         break;
      }
      case VSEP_FAULT_FILTER_46US:
      {
         filter_time = VSEP_FAULT_FILTER_TIME_46US;
         break;
      }
      default:
      {
         filter_time = 0;
         break;
      }
   }
   Filter_Time_Array[channel] = filter_time;
}
}
#endif


//=============================================================================
// VSEP_Clear_Device
//=============================================================================
void VSEP_Clear_Device(IO_Configuration_T in_configuration)
{
	Parameter_Not_Used( in_configuration );
}


/* FUNCTION: SPI_Port_Transfer_Vsep                                          */
/*===========================================================================*/
/* RETURN VALUE:                                                             */
/*   void                                                                    */
/*                                                                           */
/* INPUT PARAMETERS:                                                         */
/*   SPI_Message_Definition_T        Indicates the SPI message  to be transmitted.                    */
/*                                                                           */
/* EXTERNAL REFERENCES:                                                      */
/*   None.                                                                   */
/*                                                                           */
/* DEVIATIONS FROM STANDARDS:                                                */
/*   None.                                                                   */
/*                                                                           */
/* --------------------------------------------------------------------------*/
/* ABSTRACT:                                                                 */
/* --------------------------------------------------------------------------*/
/* This function transmits a message specified and received corresponding return message using SPI module 0.         */
/* Note: Module 1 and 2 are not required for the project                     */
/*===========================================================================*/
/*
transmit the corresponding message, input VSEP_MESSAGE
*/

void  VSEP_SPI_Port_Transfer(SPI_Message_Definition_T  const *def)
{
	uint8_t   index, transmint_length;
	uint16_t  transmit_size;
	uint8_t   index_transmint,idex_receive;
	bool      end;
	uint32_t cs;

	   cs = Enter_Critical_Section();

	for (index_transmint = 0,idex_receive =0; index_transmint < def->length_of_transmit_message; index_transmint++,idex_receive++) {
		//for word transfer algorithem
		if ((idex_receive<def->length_of_receive_message) && ((((uint16_t*)def->transmit_data)[0] & 0xF00) != 0x0F00) ) {
			if(index_transmint == def->length_of_transmit_message-1) {
				end = 1;
			} else {
				end = 0;
			}
			((uint16_t*)def->receive_data)[idex_receive] = DSPI_B_Exchange_Data1(
					 VSEP_CHIP_SELECT,
					 VSEP_CTAR_SELECT,
					 DSPI_CTAR_FMSZ_16,
					 ((uint16_t*)def->transmit_data)[index_transmint],
					 end);
		} else {
			if(index_transmint == def->length_of_transmit_message-1) {
				end = 1;
			} else {
				end = 0;
			}
			DSPI_B_Exchange_Data1(
					VSEP_CHIP_SELECT,
					VSEP_CTAR_SELECT,
					DSPI_CTAR_FMSZ_16,
					((uint16_t*)def->transmit_data)[index_transmint],
					end);
		}
	}

	Leave_Critical_Section(cs);
}


//=============================================================================
// VSEP_SPI_Immediate_Transfer
//=============================================================================
void VSEP_SPI_Immediate_Transfer(IO_Configuration_T in_configuration, VSEP_Message_T in_message)
{
	VSEP_PWM_Channel_T pwm_channel;

	switch (in_message) {
	case VSEP_MESSAGE_INIT:
	case VSEP_MESSAGE_VR:
	case VSEP_MESSAGE_FAULT:
	case VSEP_MESSAGE_MPIO_MODE:
	case VSEP_MESSAGE_LEDMODE:
	case VSEP_MESSAGE_DEPS:
	case VSEP_MESSAGE_PCH_MPIO:
	case VSEP_MESSAGE_EST_SELECT:
	case VSEP_MESSAGE_EST_FAULT:
	case VSEP_MESSAGE_SOH:
	case VSEP_MESSAGE_SOH_STATUS:
		VSEP_SPI_Port_Transfer(VSEP_MESSAGE[in_message]);
		break;
	case VSEP_MESSAGE_PWM:
		pwm_channel = VSEP_PWM_Get_Channel(in_configuration);
		if(pwm_channel != VSEP_PWM_CHANNEL_MAX)
			VSEP_SPI_Port_Transfer(VSEP_MESSAGE[VSEP_MESSAGE_PWM + pwm_channel]);
		break;
	default:
		break;
	}
}


void VSEP_Initialize_Device(void)
{
	uint16_t index=0;
	VSEP_Channel_Enabled = 0xFFFFFFFF;   

#ifdef  VSEP_CALIBRATION_ENABLE
	VSEP_INIT_TXD_Buffer_Initialize();
#endif

	VSEP_EST_Select_Initialize_Device();
	VSEP_Fault_Initialize();
	VSEP_MPIO_MODE_Initialize_Device();
	VSEP_PWM_Device_Initialize();
	VSEP_DISCRETE_Device_Initialize();
	VSEP_FAULT_EST_Initialize_Device(MTSA_CONFIG_GRADIENT_COUNT );
	VSEP_SPI_SCHEDULER_Initialize();
	VSEP_LEDMODE_Initialize_Device();
	VSEP_PULSE_VR_Initialize_Device();

	// Hardware Test uses its own method to initialize the VSEP
	// Send the Init message to the VSEP. This will setup all the faults/slews/est select information/
	// along with all the locked bit information.
	VSEP_SPI_Immediate_Transfer(VSEP_Set_Device_Index(0, VSEP_INDEX_0 ), VSEP_MESSAGE_INIT );
	// Need to check why redundant operation is needed, without it, no spark injection
	VSEP_SPI_Immediate_Transfer(VSEP_Set_Device_Index(0, VSEP_INDEX_0 ), VSEP_MESSAGE_INIT );
	VSEP_Disable_SOH();

	VSEP_EST_Select_Set_Mode(VSEP_INDEX_0,EST_MODE_SIMULTANEOUS_SINGLE_ENABLE); 
	VSEP_EST_Select_Set_Channel(VSEP_INDEX_0,EST_SELECT_CYLINDER_A);
}


