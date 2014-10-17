/* ============================================================================ *\
 * v_immo.c
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       v_immo.c-2:csrc:mt20a#1
 * Revision:        2
 * Creation date:   Tuesday, July 16, 2002 3:12:47 PM
 * Last changed:    %date_modified%
 * ----------------------------------------------------------------------------
 *
 * Description:
 *   This file contains the virtual I/O layer of immobilizer.
 *
 * Tracability info
 *   SW REF 264.15X - Coding standards
 *
 * Deviations from standards
 *   None.
 *
\* ============================================================================ */

/* ============================================================================ *\
 * Standard header files.
\* ============================================================================ */
#include "io_type.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "v_immo.h"

/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Local preprocessor #define macros.
\* ============================================================================ */

//#define InitializeTimer(x)       (TimeoutStart = (x) )
//#define CheckForTimeOut(x)       ( (GetImmoTimer() - TimeoutStart) < (x) )


/* ============================================================================ *\
 * Local type declarations.
\* ============================================================================ */
//typedef enum
//{
  //  ImmoInIdle,             /* Check line high - wait for end of idle */
  //  ImmoInWaitByte1,        /* Line is high, wait for byte 1 */
  //  ImmoInByte1,            /* Receive byte 1 */
 //   ImmoInWaitByte2,        /* Line is high, wait for byte 2 */
  //  ImmoInByte2,            /* Receive byte 2 */
  //  ImmoInWaitByte3,        /* Line is high, wait for byte 3 */
  //  ImmoInByte3,            /* Receive byte 3 */
  //  ImmoInDone,             /* Receive complete and succesful */
   // ImmoInError             /* Timeout or other failure */
//} ImmoInStateType;

    /* none */

/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Global variables.
\* ============================================================================ */
//uint8_t  ByteReceived[3];
//uint8_t  ByteReceiving;
//Immo_Code_TYPE ImmoCodeReceived;
//ImmoInStateType         LastImmoInStatus;
//ImmoInStateType         ImmoInStatus;
//static MicroSec_Immo    TimeoutStart;

/* ============================================================================ *\
 * Local variables.
\* ============================================================================ */
/* INLINE */



/* ============================================================================ *\
 * Local function prototypes.
\* ============================================================================ */


/* ============================================================================ *\
 * FUNCTION: ImmoIdleWait
 * ============================================================================
 * RETURN VALUE:
 *    false if timeout occurred
 *    true  if success
 *
 * PARAMETERS:
 *    starttime
 *    timeout
 *
 * EXTERNAL REFERENCES:
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function is called during immo line idling (HIGH),
 * i.e. when the ECM is waiting for starting bit (LOW).
 * It updates the start time and returns true, after the immo line to go LOW
 * within the timeout
 * If the immo line doesn't go low after timeout, it return false.
 *
\* ============================================================================ */
//static bool ImmoIdleWait( MicroSec_Immo timeout, MicroSec_Immo* starttime);

/* ============================================================================ *\
 * FUNCTION: ImmoIdleWaitLong
 * ============================================================================
 * RETURN VALUE:
 *    false if timeout occurred
 *    true  if success
 *
 * PARAMETERS:
 *    starttime
 *    timeout
 *
 * EXTERNAL REFERENCES:
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function is called during immo line idling (HIGH),
 * i.e. when the ECM is waiting for starting bit (LOW).
 * It updates the start time and returns true, after the immo line to go LOW
 * within the timeout
 * If the immo line doesn't go low after timeout, it return false.
 *
\* ============================================================================ */

//static bool ImmoIdleWaitLong( MicroSec_Immo_LowRes timeout, MicroSec_Immo* starttime);

/* ============================================================================ *\
 * FUNCTION: WaitForImmoLineChange
 * ============================================================================
 * RETURN VALUE:
 *    false if timeout occurred
 *    true  if success
 *
 * PARAMETERS:
 *    starttime
 *    timeout
 *
 * EXTERNAL REFERENCES:
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function is called during immo line reading,
 * i.e. when the ECM is expecting the line to toggle.
 * It updates the start time and returns true, if the immo line toggle
 * within the timeout
 * If the immo line doesn't toggle after timeout, it return false.
 *
\* ============================================================================ */
//static bool WaitForImmoLineChange(MicroSec_Immo timeout, MicroSec_Immo* starttime);

/* ============================================================================ *\
 * FUNCTION: GetImmoBit
 * ============================================================================
 * RETURN VALUE:
 *    false if timeout occurred
 *    true  if success
 *
 * PARAMETERS:
 *    starttime - reference start time
 *    rec_ok - is receve ok?
 *    bit_no - bit number
 *
 * EXTERNAL REFERENCES:
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function reads a "bit" from immo code line and determine whether
 * it is a bit "one" or bit "zero" or timing error.
 * It returns '1' if bit "one" is received.
 * It returns '0' if bit "zero" is received.
 * It changed the rec_ok to false if timing error is encountered.
 *
 \* ============================================================================ */
//static uint8_t GetImmoBit(MicroSec_Immo* starttime,bool* rec_ok, uint8_t bit_no);

/* ============================================================================ *\
 * FUNCTION: ImmoReceive
 * ============================================================================
 * RETURN VALUE:
 *    false if receive failure
 *    true  if success
 *
 * PARAMETERS:
 *    buffer
 *    timeout
 *
 * EXTERNAL REFERENCES:
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function gets the immo line code (8 bits), and store it into the buffer.
 * It returns true if it receive immo code correctly,
 * It returns false if failure encountered
 *
\* ============================================================================ */
//static bool ImmoReceive(uint8_t* buffer, MicroSec_Immo* starttime);

#if 0
FCALL void SendPulseToImmobilizer(Immo_Pulse_Type NumberOfPulse)
{

   if(IsResponsePulse(NumberOfPulse))
   {
      /* Delay for T5( 1ms ) if it is a response pulse */
      Delay(ImmoTimingT5);
   }

   while (NumberOfPulse)
   {
      /* Start With Low */
      ClearImmoRequestLine();

      /* Wait For 2ms second */
      Delay(ImmoTimingT8);

      /* Toggle output pin to High */
      SetImmoRequestLine();
      /* Wait For 2ms second */
      Delay(ImmoTimingT8);

      NumberOfPulse--;
   }
}

static bool ImmoIdleWait( MicroSec_Immo timeout, MicroSec_Immo* starttime)
{
   InitializeTimer(*starttime);
   do
   {
       RefreshCopModule();
       if ( GetImmoLineState() == ImmoCodeLineLow)
       {
           *starttime = GetImmoTimer();
       }
   }
   while ( CheckForTimeOut(timeout) && (TimeoutStart == *starttime) );

   return (bool)(TimeoutStart != *starttime);
}

static bool ImmoIdleWaitLong( MicroSec_Immo_LowRes timeout, uint16_t* starttime)
{

   MicroSec_Immo_LowRes timeoutstart;
   bool		is_timeout = false;	   
   MicroSec_Immo current_time = 0;
   MicroSec_Immo prev_time;	   	   
   uint16_t high_bits = 0;
   
   prev_time = *starttime;   
   timeoutstart = (MicroSec_Immo_LowRes) ConvertTo8us(*starttime);
   do
   {
      
      RefreshCopModule();
	   /* update current timer */
      current_time = GetImmoTimer();

	   /* check for timer overflow */
      if(current_time < prev_time)
	   {
         /* update the high bits for long timer */
         high_bits += TCNT_HIGH_COUNT;         
	   }

	   /* check for timeout */
      if(((ConvertTo8us(current_time) + high_bits) - timeoutstart) >  timeout)
   	{
   		is_timeout = true;
	   }
	   prev_time = current_time;

   } while ((is_timeout == false) && (GetImmoLineState() == ImmoCodeLineHigh));
   /* Exit the while loop if (i) timeout, or (ii) Line change to low */

   *starttime = GetImmoTimer();	

   return (bool)(is_timeout == false);
}


static bool WaitForImmoLineChange(MicroSec_Immo timeout, MicroSec_Immo* starttime)
{
   InitializeTimer(*starttime);
   if ( ImmoCodeLineHigh == GetImmoLineState())
   {
        /*  wait for line low */
        do
        {
            RefreshCopModule();
            if ( GetImmoLineState() == ImmoCodeLineLow )
            {
                *starttime = GetImmoTimer();
            }
        }
        while ( CheckForTimeOut(timeout) && (TimeoutStart == *starttime) );
   }
   else
   {
        /*  wait for line high */
        do
        {
            RefreshCopModule();
            if ( GetImmoLineState() == ImmoCodeLineHigh )
            {
                *starttime = GetImmoTimer();
            }
        }
        while ( CheckForTimeOut(timeout) && (TimeoutStart == *starttime) );
   }

   return (bool) ( (TimeoutStart != *starttime));

}


static uint8_t GetImmoBit(MicroSec_Immo* starttime, bool* rec_ok, uint8_t bit_no)
{
   uint8_t          received_bit = 0;
   MicroSec_Immo    ref_time;

   ref_time = *starttime;

   if ( (*rec_ok == false) || (WaitForImmoLineChange(BitOneTimeOut, starttime)) )  /* < 220us  */
   {
        /*  line changed within 22o microsec -> starttime was updated to time it toggled */
        if ( (*starttime - ref_time) > BitOneMin )         /* > 180us : Accept bit One */
        {
           /* width was 180 to 220 microsec -> 1 received. */
           received_bit = 1;
        }
        else if( (*starttime - ref_time) >= BitZeroMin )   /* > 80us, check for bit zero */
        {
            /*  first half was Ok - now check second half */
            ref_time = *starttime;
            if( WaitForImmoLineChange(BitZeroTimeOut, starttime) ) /* < 120us  */
            {
                /* second edge within 120 microsec -> check if within spec for a "0"  */
                if( (*starttime - ref_time) >= BitZeroMin)  /*  > 80us : Accept bit zero */
                {
                    /* Bit 'zero' received */
                    received_bit = 0;
                }
                else                          /* < 80us : timing error */
                {
                    *rec_ok = false;
                }
            }
            else  /* > 120us : timing error */
            {
                if ( (bit_no == 7) && ( GetImmoLineState() == ImmoCodeLineHigh ) )
                {
                    /*  there was no last edge because it is the last bit, the bit is 1 and the line is high */
                    received_bit = 0;
                    *starttime += BitZeroTiming;  /* Adjust the start time */
                }
                else
                {
                    *rec_ok = false;
                }
            }
         }
         else /* < 80us : timing error */
         {
            *rec_ok = false;
         }
      }
    else /* > 220us : timing error  (except last bit is high) */
    {
        if ( (bit_no == 7)&& ( GetImmoLineState() == ImmoCodeLineHigh ) )
        {
            /*  there was no last edge because it is the last bit, the bit is 1 and the line is high */
            received_bit = 1;
            *starttime += BitOneTiming;  /* Adjust the start time */
        }
        else
        {
            *rec_ok = false;
            received_bit = 0;
        }
    }

    return (received_bit);  /* bit : 0 or 1 */
}


static bool ImmoReceive(uint8_t* buffer, MicroSec_Immo* starttime)
{
   uint8_t      bits;
   bool         receive_ok = true;

   *buffer = 0;

   for (bits = 0; bits < 8 ; bits++)
   {
        *buffer = *buffer | (GetImmoBit(starttime, &receive_ok, bits) << bits);
   }

   return (receive_ok);
}
#endif
#if 0 
FCALL bool ReadCodeFromImmobilizer(MicroSec_Immo_LowRes ImmoCodeTimeOut)
{
   MicroSec_Immo LastEventTime;

   /* Initialize Received Code to 0 */
   ByteReceived[0] = 0;
   ByteReceived[1] = 0;
   ByteReceived[2] = 0;
   ImmoCodeReceived.Word = 0;


   ImmoInStatus = ImmoInIdle;


   while ( (ImmoInStatus != ImmoInError) && (ImmoInStatus != ImmoInDone) )
   {
        LastImmoInStatus = ImmoInStatus;
        switch ( ImmoInStatus)
        {
            case ImmoInIdle :
                if (ImmoCodeLineHigh == GetImmoLineState()   )
                {
                    ImmoInStatus = ImmoInWaitByte1;
                    LastEventTime = GetImmoTimer();
                }
                else
                {
                    ImmoInStatus = ImmoInError;
                }
                break;
            case ImmoInWaitByte1 :
                if ( ImmoIdleWaitLong(ImmoCodeTimeOut, &LastEventTime) )
                {
                    ImmoInStatus = ImmoInByte1;
                }
                else
                {
                    ImmoInStatus = ImmoInError;
                }
                break;
            case ImmoInByte1 :
                if ( ImmoReceive(&ByteReceived[0], &LastEventTime) )
                {
                    ImmoInStatus = ImmoInWaitByte2;
                }
                else
                {
                    ImmoInStatus = ImmoInError;
                }
                break;
            case ImmoInWaitByte2 :
                if ( ImmoIdleWait(ImmoTimingT7, &LastEventTime) )
                {
                    ImmoInStatus = ImmoInByte2;
                }
                else
                {
                    ImmoInStatus = ImmoInError;
                }
                break;
            case ImmoInByte2 :
                if ( ImmoReceive(&ByteReceived[1], &LastEventTime) )
                {
                    ImmoInStatus = ImmoInWaitByte3;
                }
                else
                {
                    ImmoInStatus = ImmoInError;
                }
                break;
            case ImmoInWaitByte3 :
                if ( ImmoIdleWait(ImmoTimingT7, &LastEventTime) )
                {
                    ImmoInStatus = ImmoInByte3;
                }
                else
                {
                    ImmoInStatus = ImmoInError;
                }
                break;
            case ImmoInByte3 :
                if ( ImmoReceive(&ByteReceived[2], &LastEventTime) )
                {
                    ImmoInStatus = ImmoInDone;
                }
                else
                {
                    ImmoInStatus = ImmoInError;
                }
                break;
            default:
                ImmoInStatus = ImmoInError;
                break;
        }
   }

   if(ImmoInStatus == ImmoInDone)
   {
      /* Rolling Code Decryption */
      ImmoCodeReceived.Bytes.High_Byte = ByteReceived[0] ^ ByteReceived[2];
      ImmoCodeReceived.Bytes.Low_Byte = ByteReceived[0] ^ ByteReceived[1];
   }

   return (bool)(ImmoInStatus == ImmoInDone);
}

#endif

/*-----------------------------------------------------------------------*/
/*  Delay() routine                                                      */
/*                                                                       */
/*  Description:  This function wait for x milliseconds                  */
/*                                                                       */
/*  Called every: no fixed interval                                      */
/*-----------------------------------------------------------------------*/

#if 0
void Delay( MicroSec_HighRes_Type microsec )
//void Delay( uint16_t microsec )
{
    MicroSec_HighRes_Type starttime ;
    //uint16_t starttime ;
    starttime = ReadMainTimerHighRes() ;
    while (( ReadMainTimerHighRes() - starttime ) < microsec )
    {
        /*  5 msec has not passed yet - toggle cop instead */
        Toggle_COP() ;
    }
}
#endif
/* ============================================================================ *\
 * File revision history (top to bottom, first revision to last revision
 * ============================================================================
 *
 * Date         user id     SCR       (description on following lines)
 * ----------   -------     ---
 * 14/05/03     tmhau      -
 * + Baseline - Created from MT20UE03.
 *
 * 18/07/03		 tmhau       140
 * + Change Main Timer (TCNT) Resolution from 8us to 1us
 *   - Add ImmoIdleWaitLong function for timeout greater than 65535ms.
 *
 * 12/03/07     LShoujun    mt20u2#78
 * + Integrate P2 old immo into dev10
 *   - Added compile configuration option of XeIMMOOLD_CONFIG
 *
 * 01/30/08     LShoujun    ---
 * + Add delay function in immo module
\* ============================================================================ */
