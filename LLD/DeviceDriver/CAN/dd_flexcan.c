#include "dd_flexcan.h"

#define SECTION_FLEXCAN_A_REGISTER
#include "section.h"
FLEXCAN_T FlexCAN_A;
#define SECTION_END
#include "section.h"

#define SECTION_FLEXCAN_C_REGISTER
#include "section.h"
FLEXCAN_T FlexCAN_C;
#define SECTION_END
#include "section.h"

#define FLEXCAN_MSGOBJ_16_31_MASK             (0xFFFF0000U)
#define FLEXCAN_MSGOBJ_32_63_MASK             (0xFFFFFFFFU)
#define FLEXCAN_29BIT_MASK                    (0x1FFFFFFFU)


static const uint32_t FlexCAN_Bit_Rate[ ] =
{
   FLEXCAN_BAUD_RATE_100KBPS,
   FLEXCAN_BAUD_RATE_250KBPS,
   FLEXCAN_BAUD_RATE_500KBPS,
   FLEXCAN_BAUD_RATE_1MBPS
};



void FlexCAN_TX_CallBack ( uint32_t message_id          );
void FlexCAN_RX_CallBack (
   uint32_t in_message_id,
   uint8_t *in_data_buffer,
   uint8_t  in_data_length    );
//=============================================================================
// FlexCAN_Clear_Message_Buffers
//=============================================================================
void FlexCAN_Clear_Message_Buffers(
   FLEXCAN_T*          in_pFlexCAN,
   FlexCAN_Index_T     in_index   )
{
   uint8_t msg_obj;
   uint8_t msg_obj_max;
   if(FLEXCAN_DEVICE_A == in_index)
   {
      msg_obj_max = FLEXCAN_MSG_OBJ_MAX;
   }
   else
   {
      msg_obj_max = FLEXCAN_MSG_OBJ_MAX/2;
   }

   for (msg_obj = 0; msg_obj < msg_obj_max; msg_obj++)
   {   
      in_pFlexCAN->MSGBUF[msg_obj].U32[0] = 0;
      in_pFlexCAN->MSGBUF[msg_obj].U32[1] = 0;
      in_pFlexCAN->MSGBUF[msg_obj].U32[2] = 0;
      in_pFlexCAN->MSGBUF[msg_obj].U32[3] = 0;
   }
}
//=============================================================================
// FlexCAN_Initialize_Device
//=============================================================================
void FlexCAN_A_Initialize_Device(void )
{

   FLEXCAN_T* pFlexCAN;
   uint8_t msg_obj;
   uint8_t msg_obj_max;

  pFlexCAN = (FLEXCAN_T *)&FlexCAN_A;

   //Keep the module in disabled mode only untill all registers are configured
   pFlexCAN->MCR.U32   = (FLEXCAN_A_MCR_INIT.U32 | CAN_MCR_MDIS_MASK);

   pFlexCAN->IFRL.U32  = FLEXCAN_A_IFRL_INIT.U32;
   pFlexCAN->IMRL.U32 = FLEXCAN_A_IMRL_INIT.U32;;

   pFlexCAN->IFRH.U32  = FLEXCAN_A_IFRH_INIT.U32;
   pFlexCAN->IMRH.U32  = FLEXCAN_A_IMRH_INIT.U32;
  
   // Get the max msg objs used
   msg_obj_max = (uint8_t)(pFlexCAN->MCR.F.MAXMB + 1);

   //if MBFEN is set then initialise each individual Buff Mask
   if(pFlexCAN->MCR.F.MBFEN)
   {
      for(msg_obj = 0; msg_obj < msg_obj_max; msg_obj++)
      {
         pFlexCAN->RXIMR[msg_obj].U32 = FLEXCAN_A_RXIMR_INIT[msg_obj].U32;
      }
   }


      pFlexCAN->RXGMASK.U32  = FLEXCAN_A_RXGMASK_INIT.U32;
      pFlexCAN->RX14MASK.U32 = FLEXCAN_A_RX14MASK_INIT.U32;
      pFlexCAN->RX15MASK.U32 = FLEXCAN_A_RX15MASK_INIT.U32;
      pFlexCAN->CR.U32       = FLEXCAN_A_CR_INIT.U32;


   FlexCAN_Clear_Message_Buffers(pFlexCAN, FLEXCAN_DEVICE_A);

   //Enable the FlexCAN module
   pFlexCAN->MCR.F.MDIS   = false;
}

//=============================================================================
// FlexCAN_Initialize_Device
//=============================================================================
void FlexCAN_C_Initialize_Device(void )
{

   FLEXCAN_T* pFlexCAN;
   uint8_t msg_obj;
   uint8_t msg_obj_max;

  pFlexCAN = (FLEXCAN_T *)&FlexCAN_C;

   //Keep the module in disabled mode only untill all registers are configured
   pFlexCAN->MCR.U32   = (FLEXCAN_C_MCR_INIT.U32 | CAN_MCR_MDIS_MASK);


   pFlexCAN->IFRL.U32  = FLEXCAN_C_IFRL_INIT.U32;
   pFlexCAN->IMRL.U32 = FLEXCAN_C_IMRL_INIT.U32;

   // Get the max msg objs used
   msg_obj_max = (uint8_t)(pFlexCAN->MCR.F.MAXMB + 1);

   //if MBFEN is set then initialise each individual Buff Mask
   if(pFlexCAN->MCR.F.MBFEN)
   {
      for(msg_obj = 0; msg_obj < msg_obj_max; msg_obj++)
      {
         pFlexCAN->RXIMR[msg_obj].U32 = FLEXCAN_C_RXIMR_INIT[msg_obj].U32;
      }
   }
      pFlexCAN->RXGMASK.U32  = FLEXCAN_C_RXGMASK_INIT.U32;
      pFlexCAN->RX14MASK.U32 = FLEXCAN_C_RX14MASK_INIT.U32;
      pFlexCAN->RX15MASK.U32 = FLEXCAN_C_RX15MASK_INIT.U32;
      pFlexCAN->CR.U32       = FLEXCAN_C_CR_INIT.U32;


   FlexCAN_Clear_Message_Buffers(pFlexCAN, FLEXCAN_DEVICE_C);

   //Enable the FlexCAN module
   pFlexCAN->MCR.F.MDIS   = false;
}



//=============================================================================
// FLEXCAN_Get_Msg_ID
//=============================================================================
uint32_t FLEXCAN_Get_Msg_ID(
    FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj)
{
   uint32_t  msg_id;
   if (FLEXCAN_MSGOBJ_ID_STD == in_pFlexCAN->MSGBUF[in_msgobj].F.CTRSTS.F.IDE)
   {
      msg_id = in_pFlexCAN->MSGBUF[in_msgobj].F.ID.U32 >> FLEXCAN_STD_ID_SHIFT;
   }
   else
   {
      msg_id = in_pFlexCAN->MSGBUF[in_msgobj].F.ID.U32;
   }
   return(msg_id);
}
//=============================================================================
// FLEXCAN_Set_Msg_ID
//=============================================================================
void FLEXCAN_Set_Msg_ID(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msg_obj,
   uint32_t in_message_id)
{
   uint32_t  msg_id;
   if (FLEXCAN_MSGOBJ_ID_STD == in_pFlexCAN->MSGBUF[in_msg_obj].F.CTRSTS.F.IDE)
   {
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.F.STD_EXT = in_message_id;
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.F.EXTENDED = 0;
   }
   else
   {
      in_pFlexCAN->MSGBUF[in_msg_obj].F.ID.U32 = in_message_id;
   }
}

//=============================================================================
//  FLEXCAN_Get_Free_Running_Timer
//============================================================================
uint16_t FLEXCAN_Get_Free_Running_Timer(
    FLEXCAN_T* in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T  in_msgobj)
{
   return ((uint16_t)(in_pFlexCAN->MSGBUF[in_msgobj].F.CTRSTS.F.TIME_STAMP));
}

//=============================================================================
//  FLEXCAN_MSGOBJ_Write_Data
//============================================================================
void FLEXCAN_MSGOBJ_Write_Data(
   FLEXCAN_T *                  in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T       in_msgobj,
    uint8_t *              in_buffer,
   FlexCAN_MSGOBJ_Data_Length_T in_length)
{
   uint8_t data_index;
   for (data_index = 0; data_index < in_length; data_index++)
   {
      in_pFlexCAN->MSGBUF[in_msgobj].F.DATA.U8[data_index]= in_buffer[data_index];
   }
}
//=============================================================================
//  FLEXCAN_MSGOBJ_Get_Data
//============================================================================
void FLEXCAN_MSGOBJ_Get_Data(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T in_msgobj,
   uint8_t *              in_buffer,
   uint8_t                in_length)
{
   uint8_t data_index;               
   for (data_index = 0; data_index < in_length; data_index++)
   {
      in_buffer[data_index] = in_pFlexCAN->MSGBUF[in_msgobj].F.DATA.U8[data_index];
   }
}

//============================================================================
// FlexCAN_Transmit_Message
//============================================================================
bool FlexCAN_Transmit_Message(
  FLEXCAN_T *                  in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T        msg_obj,
   uint32_t in_message_id,
   uint8_t *in_data_buffer,
   uint8_t  in_data_length    )
{

   bool        request_honored = false;
   uint8_t  index;
 
      //Write Code field to make TX message buffer inactive
      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_TX_INACTIVE;

      //Write ID
      //tempoary for Standard ID only
      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.IDE  = FLEXCAN_MSGOBJ_ID_STD;
      FLEXCAN_Set_Msg_ID(in_pFlexCAN, msg_obj, in_message_id);

      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.LENGTH = in_data_length;
      FLEXCAN_MSGOBJ_Write_Data(in_pFlexCAN, msg_obj, in_data_buffer, in_data_length);

      //Write unused data bytes as 0
      for(index = in_data_length; index < FLEXCAN_DATA_MAX_BYTES; index++)
      {
         in_pFlexCAN->MSGBUF[msg_obj].F.DATA.U8[index] = 0;
      }

      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_TX_UNCONDITIONAL;

      request_honored = true;


   return ( request_honored );
}


//=============================================================================
//    FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable
//============================================================================
void FLEXCAN_MSGOBJ_INTERRUPT_Set_Enable(
   FLEXCAN_T *      in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T        in_msg_obj,
   bool in_enable )
{

  
      if( in_msg_obj < FLEXCAN_MSG_OBJ_32)
      {
         // Insert_Bits(old_value,value,position,width) 
        // in_pFlexCAN->IMRL.U32 = Insert_Bits(in_pFlexCAN->IMRL.U32,(uint32_t)in_enable,(uint32_t)in_msg_obj,(uint32_t)BIT_1);

	  in_pFlexCAN->IMRL.U32 |= in_enable<<in_msg_obj;
      }
      else
      {
         in_msg_obj   -= FLEXCAN_MSG_OBJ_32;
         // Insert_Bits(old_value,value,position,width)
       // in_pFlexCAN->IMRH.U32 = Insert_Bits(in_pFlexCAN->IMRH.U32,(uint32_t)in_enable,(uint32_t)in_msg_obj,BIT_1);
         in_pFlexCAN->IMRH.U32 |= in_enable<<in_msg_obj;
      }

}

//============================================================================
// FlexCAN_Receive_Interrupt
//============================================================================
void FlexCAN_Receive_Configure(
            FLEXCAN_T *      in_pFlexCAN,
           FlexCAN_MSGOBJ_INDEX_T        msg_obj,
           uint32_t in_message_id
          )
{

      //Write Code field to make TX message buffer inactive
      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_INACTIVE;

      //Write ID
      //tempoary for Standard ID only
      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.IDE  = FLEXCAN_MSGOBJ_ID_STD;
      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.RTR    = 0;
      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.SRR    = 0;

      FLEXCAN_Set_Msg_ID(
                    in_pFlexCAN,
                    msg_obj,
                    in_message_id);


      //Write Code field to make TX message buffer inactive
      in_pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_EMPTY;
}

//============================================================================
// FlexCAN_Receive_Interrupt
//============================================================================
void FlexCAN_Receive_Interrupt(
           FlexCAN_Index_T in_FlexCAN,
           FlexCAN_MSGOBJ_INDEX_T        msg_obj,
           uint32_t in_message_id,
           uint8_t *in_data_buffer
          )
{


   FLEXCAN_T            *pFlexCAN;
   uint8_t msg_obj_max;
   uint32_t* pInterrupt_Flag;

    FlexCAN_Msg_Code_T   message_code;
   volatile uint16_t    timer;
   uint8_t              index;
   uint8_t              data_length;
 

   if(FLEXCAN_DEVICE_A == in_FlexCAN)
   {
      msg_obj_max = FLEXCAN_MSG_OBJ_MAX;
	  pFlexCAN  =(FLEXCAN_T *)&FlexCAN_A;
   }
   else
   {
      msg_obj_max = FLEXCAN_MSG_OBJ_MAX/2;   //FlexCAN C has only 32 MB's      
   	 pFlexCAN  =(FLEXCAN_T *)&FlexCAN_C;
   }

   if( msg_obj < FLEXCAN_MSG_OBJ_32)
   {
         pInterrupt_Flag = (uint32_t *)&(pFlexCAN->IFRL.U32);
   }
   else
   {
         msg_obj   -= FLEXCAN_MSG_OBJ_32;
         pInterrupt_Flag = (uint32_t *)&(pFlexCAN->IFRH.U32);
   }



   //Read Control and Status Word to lock the Buffer
   message_code = (FlexCAN_Msg_Code_T)pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE;

   if ((message_code != FLEXCAN_MSGOBJ_RX_BUSY) &&
       (message_code != FLEXCAN_MSGOBJ_RX_OVERRUN))
   {
      // Read ID- Optional
      in_message_id = FLEXCAN_Get_Msg_ID(pFlexCAN, msg_obj);

      // Read DATA Fields
      data_length    = (uint8_t)pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.LENGTH;
      FLEXCAN_MSGOBJ_Get_Data(pFlexCAN, msg_obj, in_data_buffer, data_length);

      //Write unused data bytes as 0
      for(index = data_length; index < FLEXCAN_DATA_MAX_BYTES; index++)
      {
         in_data_buffer[index] = 0;
      }

      //Read Free Running Timer to release the lock
      timer = FLEXCAN_Get_Free_Running_Timer(pFlexCAN, msg_obj);

     // FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending
	  if( msg_obj < FLEXCAN_MSG_OBJ_32)
      {
         pFlexCAN->IFRL.U32 &= (1 << msg_obj);
      }
      else
      {
         msg_obj   -= FLEXCAN_MSG_OBJ_32;
         pFlexCAN->IFRH.U32 &= (1 << msg_obj);
      }

      //Make the message buffer available for next recieve
      pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_EMPTY;
      FlexCAN_RX_CallBack(in_message_id,in_data_buffer, FLEXCAN_DATA_MAX_BYTES);

   }
   else
   {
      //Buffer overflow happened.
      // FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending
	  if( msg_obj < FLEXCAN_MSG_OBJ_32)
      {
         pFlexCAN->IFRL.U32 &= (1 << msg_obj);
      }
      else
      {
         msg_obj   -= FLEXCAN_MSG_OBJ_32;
         pFlexCAN->IFRH.U32 &= (1 << msg_obj);
      }

      //Make the message buffer available for next recieve
      pFlexCAN->MSGBUF[msg_obj].F.CTRSTS.F.CODE = FLEXCAN_MSGOBJ_RX_EMPTY;
   }
}



//============================================================================
// FlexCAN_Process_Transmitted_Message
//============================================================================
void FlexCAN_Transmit_Interrupt(
     FLEXCAN_T *                  in_pFlexCAN,
   FlexCAN_MSGOBJ_INDEX_T        msg_obj)
{
   FlexCAN_Index_T         FlexCAN_index;
   uint32_t                msg_id;

   // Get the message id of the message object
   msg_id = FLEXCAN_Get_Msg_ID(in_pFlexCAN, msg_obj);

         // FLEXCAN_MSGOBJ_INTERRUPT_Clear_Pending 
   if( msg_obj < FLEXCAN_MSG_OBJ_32)
   {
         in_pFlexCAN->IFRL.U32 &= (1 << msg_obj);
   }
   else
   {
         msg_obj   -= FLEXCAN_MSG_OBJ_32;
         in_pFlexCAN->IFRH.U32 &= (1 << msg_obj);
   }
  FlexCAN_TX_CallBack(msg_id);
 
}

