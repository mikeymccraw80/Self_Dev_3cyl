#ifndef HAL_H
#define HAL_H

#include "reuse.h"

//=============================================================================
// define
//=============================================================================
  typedef signed char        SHORTINT;
  typedef unsigned char      BYTE;
  typedef short signed int   INTEGER;
  typedef short unsigned int WORD;
  typedef long signed int    LONGINT;
  typedef long unsigned int  LONGWORD;
  typedef signed int         MEDINT;
  typedef unsigned int       MEDWORD;

/* range: [0, 255] */
typedef BYTE               T_COUNT_BYTE;
#define V_COUNT_BYTE(val)  (BYTE)(val)         /* no scaling is needed       */
#define S_COUNT_BYTE       0                   /* Count is integral          */

/* power-of-two range: [0, 1024) */
typedef WORD             T_MILLISECONDSb;
#define V_MILLISECONDSb(val)    (WORD)((val)*64)
#define S_MILLISECONDSb         6

typedef WORD            T_CRANK_ANGLE;
#define V_CRANK_ANGLE(val)     (uint16_t)((val)*64)
#define S_CRANK_ANGLE          6

/* power-of-two range: [-256, 256) */
typedef INTEGER T_ANGLEa;
#define V_ANGLEa(val)  (INTEGER)((val)*128)
#define S_ANGLEa 7

/* power-of-two range: [0, 8192) */
typedef WORD T_RPMa;
#define V_RPMa(val)  (WORD)((val)*8)
#define S_RPMa 3

/* End enumerations defined by the Airflow subsystem */
/* Enumerations defined by the hardware diagnostics */
typedef enum {
               CeINJ_FAILED,
               CeINJ_NORMAL
            } TeINJ_CIRCUIT_STATE;

typedef enum {
               CeEST_FAULTED,
               CeEST_NOMINAL
            } TeEST_CIRCUIT_STATE;
/* End enumerations defined by the hardware diagnostics */
typedef enum
  {
  CbFALSE,
  CbTRUE
  }TbBOOLEAN;

typedef enum
{
  CeSIMULTANEOUS,
  CeSEQUENTIAL
} TeFUEL_DELIVRY_MODE;

#endif 
