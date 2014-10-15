#ifndef V_IMMO_H
#define V_IMMO_H
/* ============================================================================ *\
 * v_immo.h
 * ============================================================================
 * Copyright 1999,2003 Delphi Technologies, Inc., All Rights Reserved
 * Delphi Confidential
 * ----------------------------------------------------------------------------
 * File Name:       v_immo.h-2:incl:mt20a#1
 * Revision:        2
 * Creation date:   Tuesday, July 16, 2002 3:12:51 PM
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
#include "reuse.h"
#include "types.h"


/* ============================================================================ *\
 * Other header files.
\* ============================================================================ */
#include "dd_tim.h"
#include "dd_port.h"
#include "dd_psvi.h"
#include "dd_config.h "
#include "dg_malf.h"
#include "io_eep.h"


/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported preprocessor #define macros.
\* ============================================================================ */
/*  none  */


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */
#if 0
typedef MicroSec_HighRes_Type    MicroSec_Immo;
#define Prec_MicroSec_Immo       ( Prec_MicroSec_HighRes_Type )
#define Min_MicroSec_Immo        ( Min_MicroSec_HighRes_Type )
#define Max_MicroSec_Immo        ( Max_MicroSec_HighRes_Type )

typedef MicroSec_TCNT_Type       	MicroSec_Immo_LowRes;
#define Prec_MicroSec_Immo_LowRes   ( Prec_MicroSec_TCNT_Type )
#define Min_MicroSec_Immo_LowRes    ( Min_MicroSec_TCNT_Type )
#define Max_MicroSec_Immo_LowRes    ( Max_MicroSec_TCNT_Type )
typedef uint8_t                  Immo_Pulse_Type;

typedef union
{
   struct {
      uint8_t  High_Byte;     /* MSB high byte of immo code */
      uint8_t  Low_Byte;      /* LSB high byte of immo code */
   }  Bytes;
   uint16_t    Word;

}  Immo_Code_TYPE;
#endif
/* ============================================================================ *\
 * Local preprocessor #define commands.
\* ============================================================================ */
/* Normal maximum time Between ECM Request and Immo Code */
//#define ImmoTimingT2a         ( FixDefConst (322000.0, MicroSec_Immo_LowRes))
/*
   Maximum time Between ECM Request and Immo Code
   only if immobilizer not detected after K_ImmoAutoDetect trial
*/
//#define ImmoTimingT2b         ( FixDefConst (177000.0, MicroSec_Immo_LowRes))
/* Time Between two Immo code */
//#define ImmoTimingT4          ( FixDefConst (2500, MicroSec_Immo_LowRes) )
/* Time Between immo code and ECM response */
//#define ImmoTimingT5          ( FixDefConst (1000, MicroSec_Immo) )
/* Pulse Width Of ECM Request/Response */
//#define ImmoTimingT8          ( FixDefConst (2000, MicroSec_Immo) )
/* Time Between two bytes of Immo Code */
//#define ImmoTimingT7          ( FixDefConst (500, MicroSec_Immo) )
/* Maximum Time For Bit One to toggle */
//#define BitOneTimeOut         ( FixDefConst (220, MicroSec_Immo) )
/* Min Time For Bit One to toggle */
//#define BitOneTiming          ( FixDefConst (200, MicroSec_Immo) )
/* Minimum Time For Bit One to toggle */
//#define BitOneMin             ( FixDefConst (180, MicroSec_Immo) )
/* Maximum Time For Bit Zero to toggle */
//#define BitZeroTimeOut        ( FixDefConst (120, MicroSec_Immo) )
/* Minimum Time For Bit Zero to toggle */
//#define BitZeroMin            ( FixDefConst (80, MicroSec_Immo) )
/* Min Time For Bit Zero to toggle */
//#define BitZeroTiming         ( FixDefConst (100, MicroSec_Immo) )


//#define FirstRequestTimeOut   ImmoTimingT2a
//#define SecondRequestTimeOut  ImmoTimingT4
//#define ShortenRequestTimeOut ImmoTimingT2b

/* Number of bytes in one rolling code frame */
//#define TotalBytesInOneFrame  3
/* Number of bits in one Rolling code byte */
//#define TotalBitInRollingByte 8
/* Last bits in rolling byte */
//#define LastBitInRollingByte  7

/* There are 2 types Of immobilizer request */
//#define RecordingRequest      3     /* for virgin ECM */
//#define VerifyRequest         2     /* for activated ECM */
/* There are 2 types Of immobilizer response message */
//#define OkResponse            4     /* for OK */
//#define NotOkResponse         5     /* for Not OK */
//#define IsResponsePulse(x)    ( ((x) == OkResponse)||((x) == NotOkResponse))

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */
//extern Immo_Code_TYPE ImmoCodeReceived;

/* ============================================================================ *\
 * Local INLINE functions and #define function-like macros.
\* ============================================================================ */
//#define GetImmoTimer()              ReadMainTimerHighRes()
//#define GetImmoTimerLowRes()        ConvertTo8us(GetImmoTimer())
//#define GetImmoLineState()          DD_GetDiscrete(DISCRETE_IN_IMMOCODE)
//#define SetImmoRequestLine()        DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, FALSE)
//#define ClearImmoRequestLine()      DD_SetDiscrete(DISCRETE_OUT_IMMOREQ, TRUE)
//#define ImmoCodeLineHigh            ((bitfield8_t) true)
//#define ImmoCodeLineLow             ((bitfield8_t) false)
//#define FixcodeReceived()           ImmoCodeReceived.Word

/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */

/* ============================================================================ *\
 * FUNCTION: ReadCodeFromImmobilizer
 * ============================================================================
 * RETURN VALUE:
 *   TRUE: Read Code Successfully
 *   FALSE: Encounter Timeout or Timing Error
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   ImmoCodeReceived
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function reads the code from the immobilizer ECU.
\* ============================================================================ */
//FCALL bool ReadCodeFromImmobilizer(MicroSec_Immo_LowRes ImmoCodeTimeOut);

/* ============================================================================ *\
 * FUNCTION: SendPulseToImmobilizer
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   NumberOfPulse
 *
 * EXTERNAL REFERENCES:
 *   All
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function sends request/response pulse to immobilizer ECU
\* ============================================================================ */
//FCALL void SendPulseToImmobilizer(Immo_Pulse_Type NumberOfPulse);
/* ============================================================================ *\
 * FUNCTION: Delay
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function wait for x milliseconds
\* ============================================================================ */
//extern void Delay( MicroSec_HighRes_Type microsec ) ;
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
 *
 * 01/30/08     LShoujun    ---
 * + Add delay function in immo module
\* ============================================================================ */

#endif /* V_IMMO_H */