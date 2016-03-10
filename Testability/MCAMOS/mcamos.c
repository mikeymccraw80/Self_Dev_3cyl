//=============================================================================
//
//       COPYRIGHT, 2008, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            mcamos.c %
//
// created_by:       lz37cb %
//
// date_created:     Wed Jun 11 09:54:59 2008 %
//
// %derived_by:      tzwfxv %
//
// %date_modified:          %
//
// %version:         3 %
//
//=============================================================================
#include "reuse.h"
#include "dd_flexcan_transmit.h"
#include "mcamos.h"

#define MCAMOS_MEMORY_UPLOAD      0xFF
#define MCAMOS_MEMORY_DOWNLOAD    0x00
#define MCAMOS_MEMORY_EXECUTE     0xFF

#define MCAMOS_SIZE_OF_FRAME      0x08


typedef struct MCAMOS_Command_Tag
{
   uint8_t  Address[4];
   uint16_t Size;
   uint8_t  Dir;
   uint8_t  Exe;
} MCAMOS_Command_T;




static MCAMOS_Command_T     MCAMOS_command;
static uint16_t             MCAMOS_size;
static uint8_t *            pmemloc;
bool MCAMOS_enable = false;

/* declare reference, this API from canobd module */
extern bool Transmit_Message( uint32_t can_id, uint8_t *message_address );

/*=============================================================================
 * MCAMOS_Process_7EE_Message
 * @func  process the command message from tester
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void MCAMOS_Process_7EE_Message(uint8_t *pdata)
{
   uint32_t memloc;
   typedef void (*funptr_T)(void);
   funptr_T funptr;
   uint32_t idx;

   if(MCAMOS_enable)
   {
      pmemloc = (uint8_t *)&MCAMOS_command;
      for (idx = 0; idx < 8; idx++) 
      {
         *pmemloc = pdata[idx];
         pmemloc++;
      }

      memloc = MCAMOS_command.Address[0];
      memloc = (memloc<<8) | MCAMOS_command.Address[1];
      memloc = (memloc<<8) | MCAMOS_command.Address[2];
      memloc = (memloc<<8) | MCAMOS_command.Address[3];
      pmemloc = (uint8_t *)memloc;
      MCAMOS_size = MCAMOS_command.Size;

      if(MCAMOS_MEMORY_UPLOAD == MCAMOS_command.Dir)
      {
         MCAMOS_Upload_Data_By_Frame();
      }
      else if (MCAMOS_MEMORY_DOWNLOAD == MCAMOS_command.Dir) 
      {
         if ( (MCAMOS_size <=0) && (MCAMOS_MEMORY_EXECUTE == MCAMOS_command.Exe))
         {
            funptr = (funptr_T)(uint32_t *)pmemloc;
            funptr();
            /*((void(*)(void))(uint32_t *)pmemloc)();*/
         }
      }
      else
      {
         /* do nothing */
      }
   }
}

/*=============================================================================
 * MCAMOS_Process_7EF_Message
 * @func  process 7ef message, it can be send by both tester or ECM according to
 *        the direction defined in command, it is used to send data
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void MCAMOS_Process_7EF_Message(uint8_t *pdata)
{
   uint8_t bytecnt;
   uint8_t idx;

   if(MCAMOS_enable)
   {
      if(MCAMOS_MEMORY_DOWNLOAD == MCAMOS_command.Dir)
      {
         if(MCAMOS_size > 0)
         {
            bytecnt = (MCAMOS_size > MCAMOS_SIZE_OF_FRAME)?MCAMOS_SIZE_OF_FRAME:MCAMOS_size;
            for (idx = 0; idx < bytecnt; idx++) 
            {
               *pmemloc = pdata[idx];
               pmemloc++;
            }
            MCAMOS_size -= bytecnt;
         }
      }
      else if(MCAMOS_MEMORY_UPLOAD == MCAMOS_command.Dir)
      {
         MCAMOS_Upload_Data_By_Frame();
      }
   }
}

/*=============================================================================
 * MCAMOS_Upload_Data_By_Frame
 * @func  Upload data from ecm to tester using 7ef message
 * @parm  none
 * @rdesc none 
 *===========================================================================*/
void MCAMOS_Upload_Data_By_Frame(void)
{
   uint8_t tx_message[8]={0,0,0,0,0,0,0,0};
   uint8_t idx;
   uint8_t bytecnt;

   bytecnt = (MCAMOS_size > MCAMOS_SIZE_OF_FRAME)?MCAMOS_SIZE_OF_FRAME:MCAMOS_size;

   if (MCAMOS_size > 0) 
   {
      for( idx = 0; idx < bytecnt; idx++)
      {
         tx_message[idx] = *pmemloc;
         pmemloc++;
      }
      MCAMOS_size -= bytecnt;

      // FlexCAN_Transmit_Message( MCAMOS_MESSAGE_TRANSMIT_CONFIGURATION, MCAMOS_CANID_7EF, tx_message, 8);
      // Transmit_Message(MCAMOS_CANID_7EF, tx_message);
      HAL_CAN_Transmit_Message(MCAMOS_CANID_7EF, 8, tx_message);
   }

}

uint16_t MCAMOS_Get_Message_Size(void)
{
    return MCAMOS_size;
}
