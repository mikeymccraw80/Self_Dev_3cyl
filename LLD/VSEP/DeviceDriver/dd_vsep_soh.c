//=============================================================================
//
//       COPYRIGHT, 2007, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %full_filespec:            dd_vsep_soh.c~5:csrc:mt20u2#1 %
//
// created_by:       lz7r3l
//
// date_created:     Mon Jan 10 14:08:59 2005
//
// %derived_by:      wzmkk7 %
//
// %date_modified:   Fri Feb 16 11:37:24 2007 %
//
// %version:         5 %
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

#include "io_type.h"
#include "reuse.h"
#include "dd_vsep.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_txd.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_msg_config.h"
#include "dd_vsep_init_config.h"

/* global message buffer definition */
uint16_t VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_MAX];
uint16_t VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_MAX];
uint16_t VSEP_SOH_Status_Rxd[VSEP_SOH_STATUS_RXD_MESSAGE_MAX];

/* local variable definition */
uint16_t VSEP_SOH_Challenge_Rxd[VSEP_SOH_RXD_MESSAGE_MAX];
uint16_t VSEP_SOH_Challenge_Txd[VSEP_SOH_TXD_MESSAGE_MAX];
uint16_t VSEP_SOH_Response_Rxd[VSEP_SOH_RXD_MESSAGE_MAX];
uint16_t VSEP_SOH_Response_Txd[VSEP_SOH_TXD_MESSAGE_MAX];

///////////////////////////////////////////////////////////////////////////////
// VSEP PCH VSEP_SOH_Initialize_Device
///////////////////////////////////////////////////////////////////////////////
FAR_COS void VSEP_SOH_Initialize_Device( IO_Configuration_T in_configuration )
{
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_CHALLENGE );
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_NOT_USED );
}

///////////////////////////////////////////////////////////////////////////////
// VSEP_SOH_Get_Challenge
///////////////////////////////////////////////////////////////////////////////
FAR_COS uint32_t VSEP_SOH_Get_Challenge( IO_Configuration_T in_configuration  )
{
   uint32_t challenge;

   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_CHALLENGE );
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_NOT_USED  );

  VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH );

   challenge = VSEP_Msg_Get_Challenge( VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_CHALLENGE]);

   return challenge;
}

///////////////////////////////////////////////////////////////////////////////
// Update_VSEP_SOH_Status_Immediate	
// mz38cg: update SOH Status
///////////////////////////////////////////////////////////////////////////////
FAR_COS void Update_VSEP_SOH_Status_Immediate( IO_Configuration_T in_configuration  )
{
 
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH_STATUS );

}


///////////////////////////////////////////////////////////////////////////////
// VSEP_SOH_Set_SOHRSTEN_Request	
// mz38cg: set SOHRSTEN flag
///////////////////////////////////////////////////////////////////////////////
FAR_COS void VSEP_SOH_Set_SOHRSTEN_Request( IO_Configuration_T in_configuration, bool sohrsten  )
{
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_NOT_USED );
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_SETUP  );
   
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE] = VSEP_Msg_Set_SOHRSTEN( VSEP_INIT_TXD_INITIAL[VSEP_INIT_TXD_MESSAGE_EST_SELECT_INIT],  sohrsten );
   
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH );
}


FAR_COS void VSEP_SOH_DisableSOH_Request( IO_Configuration_T in_configuration  )
{
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_NOT_USED );
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_SETUP  );
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE] = VSEP_Msg_SOH_Set_CRDISARM( VSEP_INIT_TXD_INITIAL[VSEP_INIT_TXD_MESSAGE_EST_SELECT_INIT],  VSEP_SOH_DISABLE   );
   
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH );
}

///////////////////////////////////////////////////////////////////////////////
// VSEP_SOH_Set_Response
///////////////////////////////////////////////////////////////////////////////
FAR_COS void VSEP_SOH_Set_Response( IO_Configuration_T in_configuration, uint32_t response  )
{
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_NOT_USED  );
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_RESPONSE  );

   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE] = VSEP_Msg_Set_RESPONSE( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE], response );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH );
}

FAR_COS void VSEP_SOH_Set_DisableFSE_Request( IO_Configuration_T in_configuration, bool fse_disreq )
{
   VSEP_Index_T device = VSEP_Get_Device_Index( in_configuration );

   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_NOT_USED  );
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_RESPONSE  );

   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE] = VSEP_Msg_Set_FSE_DISABLE( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE], fse_disreq );
}

FAR_COS void VSEP_SOH_Set_Timeout_Fault( IO_Configuration_T in_configuration, bool cr_timeout )
{
   VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_CRTOCLR( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], cr_timeout );
}

FAR_COS void VSEP_SOH_Set_DisableFSE_Request_Immediate( IO_Configuration_T in_configuration, bool fse_disreq )
{
   VSEP_SOH_Set_DisableFSE_Request( in_configuration, fse_disreq );
   VSEP_SPI_Immediate_Transfer( in_configuration, VSEP_MESSAGE_SOH );
}
///////////////////////////////////////////////////////////////////////////////
// VSEP_SOH_Calculate_Response
//
// Equation:
//   ( ( ( Bits[0] & Bits[1] & Bits[2] & Bits[3] & Bits[4] ) & 0x01 ) ^ ( !( Bit[4] ^ Bit[5] ) & 0x01 ) ) | ( Bit[4:0] << 1 )
//
///////////////////////////////////////////////////////////////////////////////
uint32_t VSEP_SOH_Calculate_Response( uint32_t challenge )//not sure
{
   uint8_t response = (uint8_t)(( (uint8_t)challenge << 1 ) & 0x3F);
   uint8_t soh_algo_0 = 1;
   uint8_t soh_algo_1;
   uint8_t x;

   for( x = 0; x < 5; x++ )
   {
      if( !Extract_Bits( challenge, x, 1 ) )
      {
         soh_algo_0 = 0;
         break;
      }
   }

   soh_algo_1 = (uint8_t)(!( Extract_Bits( challenge, 5, 1 ) ^ Extract_Bits( challenge, 4, 1 ) ));

   response = (uint8_t)Insert_Bits( response, (soh_algo_0 ^ soh_algo_1), 0, 1 );
   
   return response;
}


//=============================================================================
// VSEP Calculate Response
//=============================================================================
void VSEP_Calculate_Response( SPI_HClient_T in_hclient )
{
   uint32_t device = (uint32_t)in_hclient;
   uint8_t challenge = VSEP_Msg_Get_Challenge( VSEP_SOH_Rxd[VSEP_SOH_RXD_MESSAGE_CHALLENGE]);

   uint8_t response = ( challenge << 1 ) & 0x3F;
   uint8_t soh_algo_0 = 1;
   uint8_t soh_algo_1 = 1;
   uint8_t x;

   if( VSEP_Msg_Get_SDOA( VSEP_SOH_Txd[ VSEP_SOH_TXD_MESSAGE_CTRL ] ) == 4 )
   {
      for( x = 0; x < 5; x++ )
      {
         if( !Extract_Bits( challenge, x, 1 ) )
         {
            soh_algo_0 = 0;
            break;
         }
      }

      soh_algo_1 = !((( challenge >> 5 ) & 0x01) ^ (( challenge >> 4 ) & 0x01));

      response = Insert_Bits( response, ((soh_algo_0 ^ soh_algo_1) & 0x01), 0, 1);

      for( x = 0; x < VSEP_SOH_RXD_MESSAGE_MAX; x++ )
      {
         VSEP_SOH_Challenge_Rxd[x] = VSEP_SOH_Rxd[x];
      }

      for( x = 0; x < VSEP_SOH_TXD_MESSAGE_MAX; x++ )
      {
         VSEP_SOH_Challenge_Txd[x] = VSEP_SOH_Txd[x];
      }

      VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE] = VSEP_Msg_Set_RESPONSE( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_RESPONSE], response );

      VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_NOT_USED  );
      VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_RESPONSE  );

   }
   else
   {
      for( x = 0; x < VSEP_SOH_RXD_MESSAGE_MAX; x++ )
      {
         VSEP_SOH_Response_Rxd[x] = VSEP_SOH_Rxd[x];
      }

      for( x = 0; x < VSEP_SOH_TXD_MESSAGE_MAX; x++ )
      {
         VSEP_SOH_Response_Txd[x] = VSEP_SOH_Txd[x];
      }

      VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDOA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_RXD_SDOA_CHALLENGE );
      VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL] = VSEP_Msg_Set_SDIA( VSEP_SOH_Txd[VSEP_SOH_TXD_MESSAGE_CTRL], VSEP_TXD_SDIA_NOT_USED  );

   }
}


///////////////////////////////////////////////////////////////////////////////
// VSEP_SeviceSOH for SOH disable
///////////////////////////////////////////////////////////////////////////////

void VSEP_SeviceSOH( void ) 
{
    uint32_t challenge;
    uint8_t response;
    challenge = VSEP_SOH_Get_Challenge(MTSA_CONFIG_VSEP_DEVICE_0);
    response = VSEP_SOH_Calculate_Response(challenge);
    VSEP_SOH_Set_Response(MTSA_CONFIG_VSEP_DEVICE_0,response);
}

///////////////////////////////////////////////////////////////////////////////
// VSEP_SeviceSOH
///////////////////////////////////////////////////////////////////////////////
FAR_COS void VSEP_Disable_SOH( void ) 
{

  uint16_t index = 0;

    HAL_GPIO_SET_FSE_Enable(true);

    VSEP_SOH_DisableSOH_Request(MTSA_CONFIG_VSEP_DEVICE_0);

    HAL_GPIO_SET_GEN_Enable(true);

    VSEP_SeviceSOH();

    VSEP_SOH_DisableSOH_Request(MTSA_CONFIG_VSEP_DEVICE_0);

    VSEP_SeviceSOH();
}
/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version for MT22p1 based on MT80       *
\*===========================================================================*/
